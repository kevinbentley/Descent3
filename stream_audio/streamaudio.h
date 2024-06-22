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

 * $Logfile: /DescentIII/Main/lib/streamaudio.h $
 * $Revision: 1.2 $
 * $Date: 2004/02/09 04:14:51 $
 * $Author: kevinb $
 *
 * Interface for streaming audio, compressed or not
 *
 * $Log: streamaudio.h,v $
 * Revision 1.2  2004/02/09 04:14:51  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:38  icculus
 * initial checkin
 *
 *
 * 30    10/25/99 6:00p Jeff
 * fixed adecode.h include for Linux
 *
 * 29    10/21/99 1:52p Kevin
 * Mac Merge!
 *
 * 28    9/30/99 4:35p Jeff
 * fixed linux typo
 *
 * 27    9/30/99 4:29p Jeff
 * Linux compile
 *
 * 26    7/28/99 3:04p Kevin
 * Macintosh!
 *
 * 25    5/17/99 1:50p Ardussi
 * changed to compile on Mac
 *
 * 24    5/13/99 5:04p Ardussi
 * changes for compiling on the Mac
 *
 * 23    5/10/99 9:22p Samir
 * added code to allow for certain streams to be specified to start on
 * next sound frame.
 *
 * 22    4/15/99 1:44a Jeff
 * changes for linux compile
 *
 * 21    4/10/99 5:09p Samir
 * beginning to add prioritization of sounds code.  currently non
 * functional, but allows me to change all calls to Play3dSound so that I
 * can test later.
 *
 * 20    3/04/99 6:38p Samir
 * Saved stream state per frame.
 *
 * 19    3/03/99 5:08p Samir
 * added slew of debug code: hopefully the library will be revamped after
 * OEM.
 *
 * 18    2/28/99 5:11p Nate
 * added playcount.
 *
 * 17    2/27/99 6:52p Samir
 * added function to get current loop count
 *
 * 16    2/26/99 5:26p Samir
 * fixes to streaming audio to reflect fix in direct sound mixer.
 *
 * 15    1/13/99 6:48a Jeff
 * made linux friendly with some #ifdef's
 *
 * 14    12/13/98 6:50p Samir
 * fixed problems with looping and next.switching sync.
 *
 * 13    12/11/98 3:27p Samir
 * add debug code.
 *
 * 12    12/10/98 7:12p Samir
 * fixed some bugs in file/playback buffer sequencing with new system.
 *
 * 11    12/10/98 10:11a Samir
 * newer streaming audio library.
 *
 * 8     11/20/98 5:20p Samir
 * correcting a lot of errors in AudioStream::Next
 *
 * 7     11/13/98 2:25p Samir
 * added 'next' stream processing.
 *
 * 7     11/13/98 10:48a Samir
 * added 'next' stream capability.
 *
 * 6     10/23/98 7:05p Samir
 * added pause and resume
 *
 * 5     8/10/98 5:54p Samir
 * added looping streams and soft measure stopping.
 *
 * 4     7/24/98 5:19p Samir
 * added osfarchive class,
 *
 * 3     7/09/98 8:36p Samir
 * fully implemented redo of Stream interface.
 *
 * 2     7/08/98 6:27p Samir
 * stream library integrated with highlevel sound system.
 *
 * 1     7/08/98 6:22p Samir
 * moved from man.
 *
 * 3     6/19/98 6:07p Jeff
 * added a function to return a handle to the sound
 *
 * 2     6/18/98 5:17p Jeff
 * Initial creation, support should be pretty much complete
 *
 * $NoKeywords: $
 */
#ifndef __STREAMAUDIO_H_
#define __STREAMAUDIO_H_

#include "adecode.h"

#include "ssl_lib.h"
#include "TaskSystem.h"

void *AudioStreamCB(void *user_data, int handle, int *size);
int ADecodeFileRead(void *data, void *buf, uint32_t qty);
int StreamPlay(const char *filename, float volume, int flags);
void StreamStop(int handle);
int StreamGetSoundHandle(int handle);

//////////////////////////////////////////////////////////////////////////////
class llsSystem;
struct CFILE;
//	stream file info
#define OSF_HDR_SIZE 128
#define OSF_TAG "OSF1"
#define OSF_HDR_TITLE_OFS 64
#define OSF_HDR_TITLE_LEN 32
//	stream type
#define OSF_DIGITAL_STRM 0
// compression type
#define OSF_DIGIRAW_STRM 0
#define OSF_DIGIACM_STRM 1
//	stream format
#define SAF_8BIT_MASK 0x00
#define SAF_16BIT_MASK 0x01
#define SAF_MONO_MASK 0x00
#define SAF_STEREO_MASK 0x10

#define SAF_8BIT_M (SAF_8BIT_MASK | SAF_MONO_MASK)     // 0x00
#define SAF_8BIT_S (SAF_8BIT_MASK | SAF_STEREO_MASK)   // 0x10
#define SAF_16BIT_M (SAF_16BIT_MASK | SAF_MONO_MASK)   // 0x01
#define SAF_16BIT_S (SAF_16BIT_MASK | SAF_STEREO_MASK) // 0x11
//////////////////////////////////////////////////////////////////////////////
struct tOSFDigiHdr // this struct belongs to OSF_DIGITAL_STRM
{
  uint32_t measure;
};
class OSFArchive {
  CFILE *m_fp;
  uint32_t m_length;    // file information stored such as length
  uint8_t m_type;     // stream type
  uint8_t m_comp;     // compression type
  uint8_t m_flags;    // format
  uint32_t m_rate;      // frequency
  bool m_writemode; // are we in write mode?
  union {
    tOSFDigiHdr digi;
  } m_hdr;
  char m_name[OSF_HDR_TITLE_LEN]; // title string length.
  int m_datastart;                // pointer to start of data.
public:
  OSFArchive();
  ~OSFArchive();
  bool Open(const char *filename, bool write = false);
  void Close();
  bool Opened() const { return m_fp ? true : false; };
  void Rewind();
  //	write out operations.
  bool SaveHeader(uint8_t type, uint8_t comp, uint8_t flags, uint32_t rate, uint32_t length, void *hdr, const char *name);
  bool WriteBlock(uint8_t *blk, int size);
  //	read in operations.
  int Read(uint8_t *blk, int size);
  //	get archive info.
  uint8_t StreamType() const { return m_type; };
  uint8_t StreamComp() const { return m_comp; };
  uint8_t StreamFormat() const { return m_flags; };
  uint32_t StreamRate() const { return m_rate; };
  uint32_t StreamLength() const { return m_length; };
  const char *StreamName() const { return (const char *)m_name; };
  //	get header info.
  const void *StreamHeader() const { return (void *)&m_hdr.digi; };
};
//////////////////////////////////////////////////////////////////////////////
//	streamaudio constants.
#define STRM_BUFCOUNT 4
#define STRM_BUFSIZE STREAM_BUFFER_SIZE
#define STRM_LIMIT 4
#define STRM_STOPPED 0x0
#define STRM_PLAYING 0x1
#define STRM_PAUSED 0x2
#define STRM_STOPPING 0x4
#define STRM_PENDING 0x8 // DAJ
#define STRM_INVALID 0xff
//	flags used to open stream.
#define STRM_OPNF_ONETIME 0x1
#define STRM_OPNF_GRADUAL 0x2
/*	This class will handle streams for the music system.
        Including allowing an interface to dynamically change the stream.
*/
#define STRM_BUFF_USED 0x1     // allocated buffer with data
#define STRM_BUFF_TERMINAL 0x2 // terminates on this buffer
#define STRM_BUFF_LOOPEND 0x4  // marks last buffer in measure
class AudioStream {
  OSFArchive m_archive;                   // audio stream archive object.
  AudioDecoder::IAudioDecoder *m_decoder; // audio codec object
  struct { // mixing buffers
    uint8_t *data;
    int nbytes; // number of bytes of valid data.
    int flags;
    int id;
  } m_buffer[STRM_BUFCOUNT];
  int m_bufsize;         // size of each buffer.
  float m_measure_timer; // timer for measure checking.
  float m_measure_time;  // amount of time per measure.
  float m_last_frametime;
  uint8_t m_sbufidx;   // stream position markers
  uint8_t m_fbufidx;   // file position markers
  uint8_t m_curbufidx; // current buffer in measure index
  uint8_t m_playcount;
  bool m_readahead;               // if stream is currently reading from disk
  bool m_readahead_finished_loop; // if a loop's readahead has finished
  int16_t m_nbufs;                  // number of buffers streamed so far.
  play_information m_playinfo;    // used by llsSystem
  float m_volume;                 // volume of stream.
  int16_t m_state, m_laststate;     // current state of stream playing
  int m_llshandle;                // internal sound handle.
  int m_flags;                    // stream playing options.
  int16_t m_streamindex;            // index into active stream table.
  int16_t m_loopcount;              // loop counter.
  int m_bytesleft;                // number of bytes left in file
  int m_curmeasure;               // current measure.
  int m_playbytesleft, m_playbytestotal;
  int m_curid;                  // stream's id #
  int *m_stopflag;              // location of stop flag used in stop function
  bool m_loop;                  // are we looping?
  bool m_stopnextmeasure;       // stop on next measure.
  bool m_start_on_frame;        // we will play this stream on the next ::Frame call.
  bool m_start_on_frame_looped; // the stream that will play on next frame is looped.
private:
  friend void *AudioStreamCB(void *user_data, int handle, int *size);
  friend int ADecodeFileRead(void *data, void *buf, uint32_t qty);
  void *StreamCallback(int *size);        // invoked by omsStreamCB.
  int ReadFileData(int buf, int len);     // reads in decompressed raw data.
  int ReadFileDirect(char *buf, int len); // reads in decompressed raw data.
  void UpdateData();                      // updates file buffers
  void End();                             // cleans up after a stop.
  void Reset();                           // resets to start of stream.
  bool OpenDigitalStream();               // opens and prepares a digital stream
  bool ReopenDigitalStream(uint8_t fbufidx, int nbufs);

private:
  //	attach a low level sound system to all streams.
  static llsSystem *m_ll_sndsys;
  //	list of all currently played streams
  static AudioStream *m_streams[STRM_LIMIT];
  static int m_thisid;
  // allocates a stream slot for a stream
  bool ActivateStream(AudioStream *stream);
  void DeactivateStream(AudioStream *stream);

public:
  //	sets the low-level sound object
  static void InitSystem(llsSystem *sndsys);
  //	shutdsown
  static void Shutdown();
  //	called by application to allow stream playback
  static void Frame();
  // called to pause all streams.
  static void PauseAll();
  static void ResumeAll();
public:
  AudioStream();
  ~AudioStream();
  // simple operations
  //	flags specify what type of stream you want.
  bool Open(const char *filename, int open_flags = 0);
  // specifies next stream to be opened when current one ends.
  void Close();
  // simple requests
  bool Play(bool start_on_frame = false); //	plays a stream
  void Stop(bool on_measure = false,
            int *stop_flag =
                NULL);       // causes a rewind to start of stream, if on_measure is true, stop occurs when measure ends
  void SetVolume(float vol); // sets volume
  float GetVolume();         // returns volume
                             // misc requests
  int GetLoopCount() const;  // 0 = infinite.
  void SetLoopCount(int loop_count); // sets the number of times this stream will loop (0 = infinite!)
  void SetFlags(int flags);          // sets flags for playback (STRM_OPNF_XXX)
  void Pause();                      // pauses a stream
  void Resume();                     // resumes a paused stream.
                                     // state.
  bool ReadAhead();                  // are we still reading from disk?
  bool ReadAheadFinishedLoop();      // has stream finished with its readahead of current loop?
  bool IsReady();                    // is this stopped stream ready to play?
  int State() const {                // returns current state
    return m_state;
  };
  // information
  int GetLength() const { return m_archive.StreamLength(); };
  int GetPos() const { return m_archive.StreamLength() - m_bytesleft; };
  int GetBufferSize() const { return m_bufsize; };
  int CurrentMeasure() const { // returns current measure.
    return m_curmeasure;
  };
  int TotalMeasures() const;   // total measure count
  int GetSoundHandle() const { // returns the sound library handle for this stream.
    return m_llshandle;
  };
  //	these functions are the 'simplified' stream interface from Jeff (most of this code is from Jeff)
  friend int StreamPlay(const char *filename, float volume, int flags);
  friend void StreamStop(int handle);
  friend int StreamGetSoundHandle(int handle);
};
#endif
