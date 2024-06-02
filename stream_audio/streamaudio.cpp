/*
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/Main/streamaudio/streamaudio.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2000/04/18 00:00:49 $
 * $Author: icculus $
 *
 * Interface for streaming audio, compressed or not
 *
 * $Log: streamaudio.cpp,v $
 * Revision 1.1.1.1  2000/04/18 00:00:49  icculus
 * initial checkin
 *
 *
 * 44    9/29/99 5:13p Jeff
 * Linux now has real stream audio
 *
 * 43    7/28/99 2:04p Kevin
 * Macintosh Changes
 *
 * 41    5/17/99 1:56p Ardussi
 * changed to compile on Mac
 *
 * 40    5/10/99 9:22p Samir
 * added code to allow for certain streams to be specified to start on
 * next sound frame.
 *
 * 39    4/29/99 3:03p Samir
 * took out mprintfs and if we're opening an opened stream, close it and
 * continue.
 *
 * 38    4/17/99 5:58a Jeff
 * Changes for linux
 *
 * 37    4/14/99 1:48a Jeff
 * fixed case mismatched #includes
 *
 * 36    4/10/99 5:09p Samir
 * beginning to add prioritization of sounds code.  currently non
 * functional, but allows me to change all calls to Play3dSound so that I
 * can test later.
 *
 * 35    3/22/99 5:12p Samir
 * on shutdown, CLOSE any open streams.
 *
 * 34    3/17/99 4:22p Samir
 * made pause and resume for streams work.
 *
 * 33    3/09/99 6:40p Jeff
 * put try/catch around StreamPlay
 *
 * 32    3/04/99 6:38p Samir
 * Saved stream state per frame.
 *
 * 31    3/03/99 5:08p Samir
 * added slew of debug code: hopefully the library will be revamped after
 * OEM.
 *
 * 30    3/01/99 8:11p Samir
 * fixed bug when audio stream was playing while sound system shutdown.
 *
 * 29    2/28/99 6:35p Samir
 * fixed streaming bugs for very small samples.
 *
 * 28    2/28/99 5:11p Nate
 * added playcount.
 *
 * 27    2/27/99 6:52p Samir
 * added function to get current loop count
 *
 * 26    2/26/99 8:34p Samir
 * may have fixed problem with really small streams.
 *
 * 25    2/26/99 5:31p Samir
 *
 * 24    2/25/99 9:20p Kevin
 * Semi fix for music in DS
 *
 * 23    2/17/99 8:35p Samir
 * use m_streamdone to determine whether play should reset the stream or
 * not.
 *
 * 22    12/13/98 6:50p Samir
 * fixed problems with looping and next.switching sync.
 *
 * 21    12/11/98 5:25p Samir
 * took out debug messages.
 *
 * 20    12/11/98 5:20p Samir
 * perhaps prevent unused buffers from playing.
 *
 * 19    12/11/98 3:27p Samir
 * add debug code.
 *
 * 18    12/10/98 7:12p Samir
 * fixed some bugs in file/playback buffer sequencing with new system.
 *
 * 17    12/10/98 10:11a Samir
 * newer streaming audio library.
 *
 * 11    11/20/98 5:20p Samir
 * correcting a lot of errors in AudioStream::Next
 *
 * 10    11/13/98 4:03p Nate
 * took out volume stuff from high level sound lib
 *
 * 9     11/13/98 2:25p Samir
 * added 'next' stream processing.
 *
 * 9     11/13/98 10:48a Samir
 * added 'next' stream capability.
 *
 * 8     10/23/98 7:04p Samir
 *
 * 7     10/23/98 6:45p Matt
 * Scale the streaming audio volume by the master volume.
 *
 * 6     8/10/98 5:54p Samir
 * added looping streams and soft measure stopping.
 *
 * 5     7/30/98 4:35p Dan
 * more error checking.
 *
 * 4     7/30/98 10:57a Sean
 * if no sound, then don't do anything.
 *
 * 3     7/24/98 5:18p Samir
 * use OSFArchive for stream file operations now.
 *
 * 2     7/09/98 8:36p Samir
 * fully implemented redo of Stream interface.
 *
 * 1     7/09/98 6:48p Samir
 *
 * MOVED FROM MAIN PROJECT
 *
 * 10    6/29/98 4:15p Chris
 * Streaming audio works
 *
 * 9     6/24/98 5:00p Jeff
 * set filehandle to null on close, short circuit read data if file handle
 * is NULL
 *
 * 8     6/24/98 4:41p Jeff
 * will kill the stream is the sound is killed
 *
 *
 * $NoKeywords: $
 */
#include "streamaudio.h"

#include <cstdlib>
#include <cstring>

#include "pserror.h"
#include "mem.h"
#include "Macros.h"
#include "ddio.h"

// #include "samirlog.h"
#define LOGFILE(_s)
//	this stream is for everyone (used by the StreamPlay interface)
static AudioStream User_audio_stream;
llsSystem *AudioStream::m_ll_sndsys = NULL;
AudioStream *AudioStream::m_streams[STRM_LIMIT];
int AudioStream::m_thisid = -1;
#define SAMPLES_PER_STREAM_SHORT_BUF 22050
#define SAMPLES_PER_STREAM_BUF 44100
//	sets the low-level sound object
void AudioStream::InitSystem(llsSystem *sndsys) {
  int i;
  AudioStream::m_ll_sndsys = sndsys;
  //	reserve sound slots for streams, they should never get replaced, and always should be played.
  for (i = 0; i < STRM_LIMIT; i++) {
    AudioStream::m_streams[i] = NULL;
  }
}
//	shutdsown
void AudioStream::Shutdown() {
  if (AudioStream::m_ll_sndsys) {
    int i;
    // stop all streams.
    for (i = 0; i < STRM_LIMIT; i++) {
      if (AudioStream::m_streams[i]) {
        AudioStream::m_streams[i]->Close();
        AudioStream::m_streams[i] = NULL;
      }
    }
    AudioStream::m_ll_sndsys = NULL;
  }
}
// allocates a stream slot for a stream
bool AudioStream::ActivateStream(AudioStream *stream) {
  int i;
  for (i = 0; i < STRM_LIMIT; i++) {
    if (AudioStream::m_streams[i] == NULL) {
      AudioStream::m_streams[i] = stream;
      stream->m_streamindex = i;
      return true;
    }
  }
  mprintf(0, "STRMAUD: AudioStream queue filled!\n");
  return false;
}
void AudioStream::DeactivateStream(AudioStream *stream) {
  if (stream->m_streamindex > -1) {
    AudioStream::m_streams[stream->m_streamindex] = NULL;
    stream->m_streamindex = -1;
  }
}
//	called by application to allow stream playback
void AudioStream::Frame() {
  int t;
  float time = timer_GetTime();
  if (!m_ll_sndsys)
    return;
  for (t = 0; t < STRM_LIMIT; t++) {
    if (AudioStream::m_streams[t]) {
      AudioStream *strm = AudioStream::m_streams[t];
      if (strm->m_laststate != strm->m_state) {
        LOGFILE((_logfp, "STRM[%d]:frame_state=%d\n", strm->m_curid, strm->m_state));
      }
      if (strm->m_state == STRM_PLAYING) {
        // see if the sound is still playing if it isn't then kill it (also if no more loops)
        strm->m_measure_timer += (time - strm->m_last_frametime);
        if (strm->m_measure_timer >= strm->m_measure_time) {
          strm->m_curmeasure++;
        }
        strm->m_last_frametime = time;
        if (strm->m_state == STRM_PLAYING)
          strm->UpdateData();
      } else if (strm->m_state == STRM_STOPPING) {
        if (!AudioStream::m_ll_sndsys->IsSoundInstancePlaying(strm->m_llshandle)) {
          strm->Stop();
          //	mprintf(0, "STRM[%d]: Stopped!\n", strm->m_curid);
          LOGFILE((_logfp, "STRM[%d]: Stopped!\n", strm->m_curid));
          if (CHECK_FLAG(strm->m_flags, STRM_OPNF_ONETIME)) {
            strm->Close();
          }
          strm->m_readahead = false;
        }
      } else if (strm->m_state == STRM_INVALID) {
        strm->DeactivateStream(strm);
      } else if (strm->m_start_on_frame) {
        strm->m_llshandle = m_ll_sndsys->PlayStream(&strm->m_playinfo);
        if (strm->m_llshandle > -1) {
          // for one buffer samples, prepare to stop now so that the one and only one buffer gets called.
          //	looped one buffer samples dont do this though...
          if (strm->m_nbufs == 1 && !strm->m_start_on_frame_looped) {
            strm->m_state = STRM_STOPPING;
          } else {
            strm->m_state = STRM_PLAYING;
          }
        }
        strm->m_start_on_frame = false;
        strm->m_start_on_frame_looped = false;
      }
      strm->m_laststate = strm->m_state;
    }
  }
}
// called to pause all streams.
void AudioStream::PauseAll() {
  int t;
  for (t = 0; t < STRM_LIMIT; t++) {
    if (AudioStream::m_streams[t]) {
      AudioStream::m_streams[t]->Pause();
    }
  }
}
void AudioStream::ResumeAll() {
  int t;
  for (t = 0; t < STRM_LIMIT; t++) {
    if (AudioStream::m_streams[t]) {
      AudioStream::m_streams[t]->Resume();
    }
  }
}
//	AudioStream object Interface
//		allows dynamic playing of streams
AudioStream::AudioStream() {
  m_decoder = NULL; // audio decomp object
  m_llshandle = -1; // snd system handle
  m_sbufidx = 0;    // stream position markers for synching.
  m_fbufidx = 0;
  m_flags = 0;
  m_state = STRM_INVALID;
  m_streamindex = -1;
  m_curmeasure = -1;
  m_stopnextmeasure = false;
  m_stopflag = NULL;
  m_bytesleft = 0;
  m_readahead_finished_loop = false;
  m_playcount = 0;
  m_curid = -1;
  m_nbufs = 0;
  m_start_on_frame = false;
}
AudioStream::~AudioStream() { AudioStream::Close(); }
// sets flags for playback (STRM_OPNF_XXX)
void AudioStream::SetFlags(int flags) { m_flags = flags; }
void AudioStream::SetLoopCount(int loop_count) {
  // if loop_count = 0, then m_loopcount= -1, infinite;
  // if loop_count = 1, then m_loopcount=0, no looping, etc.
  m_loopcount = loop_count - 1;
}
int AudioStream::GetLoopCount() const {
  // if loop_count = 0, then m_loopcount= -1, infinite;
  // if loop_count = 1, then m_loopcount=0, no looping, etc.
  return m_loopcount + 1;
}
void AudioStream::SetVolume(float vol) {
  m_volume = vol;
  if (m_ll_sndsys) {
    if (m_llshandle < 0)
      return;
    m_ll_sndsys->AdjustSound(m_llshandle, vol, 0.0f, m_playinfo.samples_per_22khz_sample * 22050);
  }
}
float AudioStream::GetVolume() { return m_volume; }
//	flags specify what type of stream it is.
bool AudioStream::Open(const char *filename, int open_flags) {
  // don't open a stream that's already open, or bogus filename
  if (m_state != STRM_INVALID) {
    AudioStream::Close();
    //	Int3();
    //	return false;
  }
  if (m_archive.Opened() || !filename)
    return false;
  if (!m_ll_sndsys)
    return false;
  m_state = STRM_INVALID;
  m_streamindex = -1;
  m_flags = open_flags;
  m_curmeasure = 0;
  m_volume = 1.0f;
  m_bufsize = SAMPLES_PER_STREAM_BUF * 4;
  m_measure_timer = 0.0f;
  m_measure_time = 0.0f;
  m_last_frametime = 0.0f;
  m_readahead_finished_loop = false;
  m_curid = -1;
  m_nbufs = 0;
  m_start_on_frame = m_start_on_frame_looped = false;
  //	open up stream file
  if (m_archive.Open(filename)) {
    int i;
    int nbufs;
    ASSERT(m_archive.StreamType() == OSF_DIGITAL_STRM);
    m_thisid++;
    m_curid = m_thisid;

    for (i = 0; i < STRM_BUFCOUNT; i++) {
      m_buffer[i].flags = 0;
      m_buffer[i].nbytes = 0;
      m_buffer[i].data = NULL;
      m_buffer[i].id = -1; // marks stream buffer to be allocated.
    }
    // gradual streams don't readahead yet.
    nbufs = CHECK_FLAG(m_flags, STRM_OPNF_GRADUAL) ? 1 : STRM_BUFCOUNT;

    if (!AudioStream::ReopenDigitalStream(0, nbufs)) {
      return false;
    }
    AudioStream::SetLoopCount(1);
    m_laststate = m_state;
    m_state = STRM_STOPPED;
    return true;
  }
  return false;
}
//	deallocates all stream buffers and decoder.
void AudioStream::Close() {
  int i;
  if (m_archive.Opened()) {
    // stop the stream, close the archive, close the decoder.
    AudioStream::Stop();
    m_archive.Close();
    m_curid = -1;
    // free streaming buffers and decoder if we need to.
    for (i = 0; i < STRM_BUFCOUNT; i++) {
      if (m_buffer[i].data) {
        mem_free(m_buffer[i].data);
        m_buffer[i].data = NULL;
        m_buffer[i].nbytes = 0;
        m_buffer[i].flags = 0;
        m_buffer[i].id = -1;
      }
    }

    if (m_decoder) {
      delete m_decoder;
      m_decoder = NULL;
    }
  }
  m_playcount = 0;
  m_nbufs = 0;
  m_state = STRM_INVALID;
}
// has stream finished with its readahead of current loop?
bool AudioStream::ReadAheadFinishedLoop() {
  if (m_readahead_finished_loop) {
    m_readahead_finished_loop = false;
    return true;
  }
  return false;
}
// are we still reading from disk?
bool AudioStream::ReadAhead() { return m_readahead; }
bool AudioStream::IsReady() {
  if (m_state == STRM_STOPPED) {
    if (!m_readahead || m_fbufidx == (STRM_BUFCOUNT - 1)) {
      return true;
    }
  }
  return false;
}
//////////////////////////////////////////////////////////////////////////////
bool AudioStream::ReopenDigitalStream(uint8_t fbufidx, int nbufs) {
  const tOSFDigiHdr *digihdr = (const tOSFDigiHdr *)m_archive.StreamHeader();

  m_bytesleft = m_archive.StreamLength();
  m_readahead = false;

  // free current decoder.
  if (m_decoder) {
    delete m_decoder;
    m_decoder = NULL;
  }

  // instatiate decompression facility or use raw source data
  uint32_t sample_count = 0;
  uint32_t channels = 0;
  if (m_archive.StreamComp() == OSF_DIGIACM_STRM) {
    uint32_t sample_rate;
    m_decoder = AudioDecoder::CreateDecoder(ADecodeFileRead, this, channels, sample_rate, sample_count);
    if (!m_decoder) {
      delete m_decoder;
      m_decoder = NULL;
      return false;
    }
  } else {
    return false;
  }

  //	convert bufsize to true bufsize (bufsize = samples per measure for now.)
  int bytesize, granularity;
  switch (m_archive.StreamFormat()) {
  case SAF_8BIT_M:
    granularity = 1;
    break;
  case SAF_8BIT_S:
    granularity = 2;
    bytesize = digihdr->measure << 1;
    break;
  case SAF_16BIT_M:
    granularity = 2;
    bytesize = digihdr->measure << 1;
    break;
  case SAF_16BIT_S:
    granularity = 4;
    bytesize = digihdr->measure << 2;
    break;
  }

  //	bufsize is bytes per measure.  now scale according to memory requirements.
  //	clear out buffer list
  if (channels == 0 || channels > 2) {
    // weird, faulty osf
    mprintf(0, "STRM[%d]: Illegal OSF (no channels?): %d.\n", m_curid, channels);
    LOGFILE((_logfp, "STRM[%d]: Illegal OSF (no channels?): %d.\n", m_curid, channels));
    return false;
  }

  int32_t bytes_per_buf = (SAMPLES_PER_STREAM_BUF * granularity);
  int32_t filelen = (sample_count / channels) * granularity;
  int nbuffers = filelen / bytes_per_buf;
  if (nbuffers >= 0 && nbuffers <= 1) {
    if (filelen > 0) {
      bytes_per_buf = (SAMPLES_PER_STREAM_SHORT_BUF * granularity);
      nbuffers = filelen / bytes_per_buf;
      if (nbuffers == 0)
        nbuffers = 1;
    } else {
      mprintf(0, "STRM[%d]: Bad stream length %d\n", m_curid, filelen);
      LOGFILE((_logfp, "STRM[%d]: Bad stream length %d\n", m_curid, filelen));
      return false;
    }
  }
  m_playbytestotal = filelen;
  m_playbytesleft = filelen;
  m_fbufidx = fbufidx;
  m_sbufidx = 0;
  // Get the file size, and figure out an ideal buffer size
  // so our looping sounds don't have an odd silence in the middle
  m_measure_time = (digihdr->measure / 22050.0f);
  m_bufsize = (filelen / nbuffers);
  // figure out if we still need to be 4-byte aligned.
  granularity = granularity >> 1;
  if (granularity) {
    if (m_bufsize % 4) {
      m_bufsize = m_bufsize + (4 - (m_bufsize % 4));
      if (m_bufsize % 4) {
        Int3();
      }
    }
  }
  // mprintf(0,"STRM[%d]: Using buffer size of %d\n",m_curid, m_bufsize);
  LOGFILE((_logfp, "STRM[%d]: Using buffer size of %d\n", m_curid, m_bufsize));
  // mark stream as not done.
  m_readahead = true;
  m_readahead_finished_loop = false;
  if (!nbufs) {
    // dont set m_readahead, because readahead only told this function whether it was going to do
    // the read of buffers now, or let UpdateData do it later.
    return true;
  }
  // fill buffers.
  nbufs--;
  while (!CHECK_FLAG(m_buffer[m_fbufidx].flags, STRM_BUFF_USED) && nbufs >= 0 && m_readahead) {
    // if our stream's current id does not match the streaming buffer's id, then we need to reallocate
    // the stream buffer with the new memory size
    if (m_buffer[m_fbufidx].id != (int)m_curid) {
      if (m_buffer[m_fbufidx].data) {
        mem_free(m_buffer[m_fbufidx].data);
      }
      m_buffer[m_fbufidx].data = (uint8_t *)mem_malloc(m_bufsize);
    }
    m_buffer[m_fbufidx].nbytes = AudioStream::ReadFileData(m_fbufidx, m_bufsize);
    m_buffer[m_fbufidx].flags = 0;
    m_buffer[m_fbufidx].flags |= STRM_BUFF_USED;
    m_buffer[m_fbufidx].id = m_thisid;
    m_playbytesleft -= m_buffer[m_fbufidx].nbytes;
    //		mprintf(0, "[%d]:pbytesleft=%d\n", m_curid, m_playbytesleft);
    LOGFILE((_logfp, "[%d]:pbytesleft=%d\n", m_curid, m_playbytesleft));
    if (m_playbytesleft <= (m_bufsize / 4)) {
      //	mprintf(0, "STRM[%d]: ", m_curid);
      if (m_buffer[m_fbufidx].nbytes == 0) {
        memset(m_buffer[m_fbufidx].data, 0, 4);
        m_buffer[m_fbufidx].nbytes = 4;
        mprintf(0, "making empty buffer and");
      }
      //	mprintf(0, "TERMINAL buffer.\n");
      LOGFILE((_logfp, "STRM[%d] TERMINAL buffer. ", m_curid));
      m_buffer[m_fbufidx].flags |= STRM_BUFF_TERMINAL;
      m_readahead = false;
      m_readahead_finished_loop = true;
    }
    m_nbufs++;
    //@@		if (m_buffer[m_fbufidx].nbytes < m_bufsize || m_bytesleft == 0) {
    //@@			if (m_buffer[m_fbufidx].nbytes == 0) {
    //@@				memset(m_buffer[m_fbufidx].data, 0, 4);
    //@@				m_buffer[m_fbufidx].nbytes = 4;
    //@@			}
    //@@			m_buffer[m_fbufidx].flags |= STRM_BUFF_TERMINAL;
    //@@			m_readahead = false;
    //@@			m_readahead_finished_loop = true;
    //@@		}
    m_fbufidx = (m_fbufidx + 1) % STRM_BUFCOUNT;
  }
  // readjust file buffer index down so that it matches the CURRENT file index, not the next one.
  if (m_fbufidx == 0)
    m_fbufidx = STRM_BUFCOUNT - 1;
  else
    m_fbufidx--;
  return true;
}
///////////////////////////////////////////////////////////////////////////////
//	plays a stream
bool AudioStream::Play(bool start_on_frame) {
  //	call low level stream manager. - samir
  int sflag = SIF_STREAMING_16_M, i;
  bool looped = false;
  if (m_state == STRM_INVALID) {
#ifdef WIN32
    Int3();
#endif
    return false;
  }
  //	play stream if there's room to.
  if (!ActivateStream(this))
    return false;
  switch (m_archive.StreamFormat()) {
  case SAF_8BIT_M:
    sflag = SIF_STREAMING_8_M;
    break;
  case SAF_8BIT_S:
    sflag = SIF_STREAMING_8_S;
    break;
  case SAF_16BIT_M:
    sflag = SIF_STREAMING_16_M;
    break;
  case SAF_16BIT_S:
    sflag = SIF_STREAMING_16_S;
    break;
  default:
    Int3();
    return false;
  }
  // reset soft stopping.
  m_stopnextmeasure = false;
  m_curmeasure = 0;
  m_stopflag = NULL;
  if (m_state != STRM_STOPPED) {
    AudioStream::Stop();
  }
  if (m_playcount > 0) {
    AudioStream::Reset();
  }
  m_playcount++;
  m_measure_timer = 0.0f;
  m_last_frametime = timer_GetTime();
  //	check for terminal and if loopcount != 0 then specify terminal as looping
  if (m_loopcount != 0) {
    for (i = 0; i < STRM_BUFCOUNT; i++) {
      if (CHECK_FLAG(m_buffer[i].flags, STRM_BUFF_USED)) {
        if (CHECK_FLAG(m_buffer[i].flags, STRM_BUFF_TERMINAL)) {
          if (m_loopcount == -1) {
            m_buffer[m_fbufidx].flags |= STRM_BUFF_LOOPEND;
            looped = true;
            AudioStream::Reset();
          } else if (m_loopcount > 0) {
            m_buffer[m_fbufidx].flags |= STRM_BUFF_LOOPEND;
            looped = true;
            AudioStream::Reset();
            m_loopcount--;
          }
          m_readahead_finished_loop = true;
        }
      }
    }
  }
  //	if (m_curid == 3) Int3();
  // invoke low level sound system.
  memset(&m_playinfo, 0, sizeof(m_playinfo));
  m_playinfo.samples_per_22khz_sample = 1.0;
  m_playinfo.sample_skip_interval = 0;
  m_playinfo.m_stream_cback = AudioStreamCB;
  m_playinfo.m_stream_data = m_buffer[m_sbufidx].data;
  m_playinfo.m_stream_format = sflag;
  m_playinfo.m_stream_size = m_buffer[m_sbufidx].nbytes;
  m_playinfo.m_stream_handle = m_streamindex;
  m_playinfo.m_stream_bufsize = m_bufsize;
  m_playinfo.user_data = this;
  m_playinfo.left_volume = m_playinfo.right_volume = m_volume;
  m_playinfo.priority = SND_PRIORITY_CRITICAL; // this stream must play.
  m_start_on_frame = start_on_frame;
  m_start_on_frame_looped = looped;
  if (!m_start_on_frame) {
    m_llshandle = m_ll_sndsys->PlayStream(&m_playinfo);
    if (m_llshandle > -1) {
      // for one buffer samples, prepare to stop now so that the one and only one buffer gets called.
      //	looped one buffer samples dont do this though...
      if (m_nbufs == 1 && !looped) {
        m_state = STRM_STOPPING;
      } else {
        m_state = STRM_PLAYING;
      }
      return true;
    } else {
      mprintf(0, "STRMAUD:Eh? this should be reserved??\n");
      Int3();
    }
  }
  return true;
}
// pauses a stream
void AudioStream::Pause() {
  if (m_state != STRM_PLAYING) {
    return;
  }
  m_state = STRM_PAUSED;
  m_ll_sndsys->PauseSound(m_llshandle);
  //	mprintf(0, "Paused stream (%d)\n", m_llshandle);
}
// pauses a stream
void AudioStream::Resume() {
  if (m_state != STRM_PAUSED) {
    return;
  }
  m_ll_sndsys->ResumeSound(m_llshandle);
  m_state = STRM_PLAYING;
  //	mprintf(0, "Resumed stream (%d)\n", m_llshandle);
}
// causes a rewind to start of stream, if on_measure is true, stop occurs when measure ends
void AudioStream::Stop(bool on_measure, int *stop_flag) {
  if (!m_ll_sndsys) {
    return;
  }
  m_start_on_frame = false;
  if (m_state == STRM_INVALID) {
    if (stop_flag) {
      *stop_flag = true;
    }
    return;
  }
  if (m_state != STRM_STOPPED) {
    if (!on_measure) {
      if (m_state == STRM_PLAYING || m_state == STRM_PAUSED || m_state == STRM_STOPPING) {
        m_ll_sndsys->StopSound(m_llshandle, SKT_STOP_IMMEDIATELY);
        m_state = STRM_STOPPED;
        m_readahead = m_readahead_finished_loop = true;
        DeactivateStream(this);
        m_llshandle = -1;
        m_curmeasure = 0;
      }
    } else {
      //	handle soft stopping.
      m_stopflag = stop_flag;
      if (m_stopflag) {
        *m_stopflag = false;
      }
      m_stopnextmeasure = on_measure;
    }
  } else {
    DeactivateStream(this);
    m_llshandle = -1;
    m_curmeasure = 0;
    if (m_stopflag) {
      *m_stopflag = true;
    }
  }
}
// performs a clean stop and play when switching to next stream
void AudioStream::Reset() {
  m_archive.Rewind();
  m_bytesleft = m_archive.StreamLength();
  m_curmeasure = 0;
  m_readahead = true;
  m_playbytesleft = m_playbytestotal;
  if (m_decoder) {
    delete m_decoder;

    uint32_t channels;
    uint32_t sample_rate;
    uint32_t sample_count;
    m_decoder = AudioDecoder::CreateDecoder(ADecodeFileRead, this, channels, sample_rate, sample_count);
  }
}
//////////////////////////////////////////////////////////////////////////////
// invoked by AudioStreamCB.
#pragma optimize("", off)
void *AudioStream::StreamCallback(int *size) {
  uint8_t nextbuffer = (m_sbufidx + 1) % STRM_BUFCOUNT;
  void *data = NULL;
  // we're not done yet.
  // adjust sound buffer to the next buffer
  if (m_state == STRM_STOPPING || m_state == STRM_STOPPED) {
    if (m_state == STRM_STOPPED) {
      //		mprintf(0, "STRM[%d]: Callback entered while stopping! Force stop.\n", m_curid);
      LOGFILE((_logfp, "STRM[%d]: Callback entered while stopping! Force stop.\n", m_curid));
    } else {
      //	mprintf(0, "STRM[%d]: Stopping softly\n", m_curid);
      LOGFILE((_logfp, "STRM[%d]: Stopping softly\n", m_curid));
      //	if (m_curid == 3) Int3();
    }
    // mark played buffer as unused.
    m_buffer[m_sbufidx].flags = 0;
    m_buffer[m_sbufidx].nbytes = 0;
    *size = 0;
    return NULL;
  }
  if (!CHECK_FLAG(m_buffer[nextbuffer].flags, STRM_BUFF_USED)) {
    //	mprintf(0, "STRM[%d]: Playing onetime buffer?\n",m_curid);
    LOGFILE((_logfp, "STRM[%d]: Playing onetime buffer?\n", m_curid));
    m_state = STRM_STOPPED;
    *size = 0;
    return NULL;
    //@@		mprintf(0, "STRMAUD: Repeating last buffer.\n");
    //@@		data = (void *)m_buffer[m_sbufidx].data;
    //@@		*size = m_buffer[m_sbufidx].nbytes;
    //@@		return data;
  }
  // mark played buffer as unused.
  m_buffer[m_sbufidx].flags = 0;
  m_buffer[m_sbufidx].nbytes = 0;
  m_sbufidx = nextbuffer;
  //	ASSERT(CHECK_FLAG(m_buffer[m_sbufidx].flags, STRM_BUFF_USED));
  //	mprintf(0,"%c",m_sbufidx+'A');
  //	increment measure count if we've entered a new measure.
  //	if stop measure has been flagged, don't return new valid data.
  //	make sure and lock mutex, because we're modifying these contents when the caller could
  //	do the same.
  // if we reached the last buffer in an opened stream, and we're not switching prepare to stop
  //	if we are switching, release the switch lock and continue
  //	otherwise just continue.
  data = (void *)m_buffer[m_sbufidx].data;
  *size = m_buffer[m_sbufidx].nbytes;
  //	ASSERT((*size) > 0);
  if (CHECK_FLAG(m_buffer[m_sbufidx].flags, STRM_BUFF_TERMINAL)) {
    //	mprintf(0, "STRMAUD: reached end of stream (%d bytes).\n", (*size));
    if (!CHECK_FLAG(m_buffer[m_sbufidx].flags, STRM_BUFF_LOOPEND)) {
      m_state = STRM_STOPPING;
    }
    if (m_stopnextmeasure) {
      m_state = STRM_STOPPING;
    }
    //	mprintf(0, "STRM[%d]: Start stopping softly\n", m_curid);
    LOGFILE((_logfp, "STRM[%d]: Start stopping softly\n", m_curid));
    //	*done = true;
  }
  if ((*size) == 0) {
    //	*done = true;
    //	mprintf(0, "STRM[%d]: Used buffer has 0 bytes!\n", m_curid);
    LOGFILE((_logfp, "STRM[%d]: Used buffer has 0 bytes!\n", m_curid));
    m_state = STRM_STOPPING;
    data = NULL;
  }
  return data;
}
#pragma optimize("", on)
// reads in decompressed raw data.
int AudioStream::ReadFileData(int buf, int len) {
  if (!m_archive.Opened())
    return 0;

  if (m_decoder) {
    // We have a compressed stream
    return m_decoder->Read(m_buffer[buf].data, len);
  }

  // We have a non-compressed stream
  if (len > m_bytesleft) {
    len = m_bytesleft;
    m_bytesleft = 0;
  } else {
    m_bytesleft -= len;
  }

  return m_archive.Read(m_buffer[buf].data, len);
}
// TURN OFF OPTIMIZATIONS HERE.  Placement of instructions is VERY IMPORTANT here.  synched with StreamCallback,
//	which also has optimizations off.
#pragma optimize("", off)
// updates file buffers
void AudioStream::UpdateData() {
  int nextbuffer = ((m_fbufidx + 1) % STRM_BUFCOUNT);
  //	check if are on a measure boundary for current stream.  if so, then check if we have a next request pending
  if (CHECK_FLAG(m_buffer[nextbuffer].flags, STRM_BUFF_USED)) {
    return;
  }
  // quit out if we can.
  if (nextbuffer == m_sbufidx) {
    return;
  }
  // do read!
  //	READ DATA INTO BUFFER.  UPDATE BYTES LEFT PER MEASURE, ETC.
  if (m_readahead) {
    // ok update the next buffer with data
    m_fbufidx = nextbuffer;
    //	mprintf(0,"%c",m_fbufidx+'a');
    // if our stream's current id does not match the streaming buffer's id, then we need to reallocate
    // the stream buffer with the new memory size
    if (m_buffer[m_fbufidx].id != (int)m_curid) {
      if (m_buffer[m_fbufidx].data) {
        mem_free(m_buffer[m_fbufidx].data);
      }
      m_buffer[m_fbufidx].data = (uint8_t *)mem_malloc(m_bufsize);
    }
    m_buffer[m_fbufidx].nbytes = AudioStream::ReadFileData(m_fbufidx, m_bufsize);
    m_buffer[m_fbufidx].flags = 0;
    m_buffer[m_fbufidx].flags |= STRM_BUFF_USED;
    m_buffer[m_fbufidx].id = (int)m_curid;
    m_playbytesleft -= m_buffer[m_fbufidx].nbytes;
    //		mprintf(0, "[%d]:pbytesleft=%d\n", m_curid, m_playbytesleft);
    LOGFILE((_logfp, "[%d]:pbytesleft=%d\n", m_curid, m_playbytesleft));
    if (m_playbytesleft <= (m_bufsize / 4)) {
      //	mprintf(0, "STRM[%d]: ", m_curid);
      if (m_buffer[m_fbufidx].nbytes == 0) {
        memset(m_buffer[m_fbufidx].data, 0, 4);
        m_buffer[m_fbufidx].nbytes = 4;
        mprintf(0, "making empty buffer and");
      }
      //	mprintf(0, "TERMINAL buffer.\n");
      LOGFILE((_logfp, "STRM[%d]: TERMINAL buffer.\n", m_curid));
      m_buffer[m_fbufidx].flags |= STRM_BUFF_TERMINAL;
      m_readahead = false;
      m_readahead_finished_loop = true;
    }
    // looping?
    if (CHECK_FLAG(m_buffer[m_fbufidx].flags, STRM_BUFF_TERMINAL)) {
      if (m_loopcount == -1) {
        m_buffer[m_fbufidx].flags |= STRM_BUFF_LOOPEND;
        AudioStream::Reset();
      } else if (m_loopcount > 0) {
        m_buffer[m_fbufidx].flags |= STRM_BUFF_LOOPEND;
        AudioStream::Reset();
        m_loopcount--;
      }
      m_readahead_finished_loop = true;
    }
  }
}

#pragma optimize("", on)
///////////////////////////////////////////////////////////////////////////////
//	decoder
int ADecodeFileRead(void *data, void *buf, unsigned qty) {
  AudioStream *stream = (AudioStream *)data;
  int iqty = (int)qty;

  if (iqty > stream->m_bytesleft) {
    iqty = stream->m_bytesleft;
    stream->m_bytesleft = 0;
  } else {
    stream->m_bytesleft -= iqty;
  }

  return stream->m_archive.Read((uint8_t *)buf, iqty);
}

//	Router for stream callbacks.
//		Invoked by sound system
void *AudioStreamCB(void *user_data, int handle, int *size) {
  AudioStream *stream = (AudioStream *)user_data;
  ASSERT(stream);
  ASSERT(stream->m_streamindex == handle);
  return stream->StreamCallback(size);
}
static float Stream_volume = 1.0f;
static float Stream_master_volume = 1.0f;
void StreamVolume(float master_volume) {
  Stream_master_volume = master_volume;
  User_audio_stream.SetVolume(Stream_volume * master_volume);
}
//	these functions are the 'simplified' stream interface from Jeff (most of this code is from Jeff)
int StreamPlay(const char *filename, float volume, int flags) {
  int retval = -1;
  try {
    flags = 0;
    User_audio_stream.Close();
    User_audio_stream.Open(filename, STRM_OPNF_ONETIME);
    Stream_volume = volume;
    User_audio_stream.SetVolume(Stream_volume * Stream_master_volume);
    User_audio_stream.Play(true); // start this stream on the next frame.
    retval = User_audio_stream.m_streamindex;
  } catch (...) {
    return -1;
  }
  return retval;
}
void StreamStop(int handle) {
  if (handle > -1) {
    if (AudioStream::m_streams[handle])
      AudioStream::m_streams[handle]->Stop();
  }
  User_audio_stream.Close();
}
int StreamGetSoundHandle(int handle) {
  if (handle > -1) {
    if (AudioStream::m_streams[handle])
      return AudioStream::m_streams[handle]->GetSoundHandle();
    else
      return -1;
  }
  return -1;
}
