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

 * $Logfile: /DescentIII/Main/music/sequencer.cpp $
 * $Revision: 35 $
 * $Date: 4/09/99 12:04p $
 * $Author: Samir $
 *
 * Event driven music system
 *
 * $Log: /DescentIII/Main/music/sequencer.cpp $
 *
 * 35    4/09/99 12:04p Samir
 * take out error messages (mprintfs) for stream load failures.
 *
 * 34    4/01/99 4:50p Matt
 * Took out Warning() function, chaning those calls to mprintf()
 *
 * 33    3/18/99 10:13a Samir
 * msuic update.
 *
 * 32    3/03/99 5:08p Samir
 * added slew of debug code: hopefully the library will be revamped after
 * OEM.
 *
 * 31    3/03/99 3:43a Samir
 * moved mprintfs for debugging.
 *
 * 30    3/02/99 1:18p Samir
 * fixes to prevent bad filenames from crashing system.
 *
 * 29    3/01/99 5:01a Samir
 * fixed bug when no pending or active song, it would still try to start a
 * pending song.
 *
 * 28    2/28/99 6:35p Samir
 * fixed streaming bugs for very small samples.
 *
 * 27    2/27/99 8:23p Samir
 * fixes to music system to act nicely to sudden and frequent region
 * changes.
 *
 * 26    2/27/99 6:51p Samir
 * added code for music tester to display current stream and loop/region.
 *
 * 25    2/27/99 5:13p Nate
 * Samir: fixes
 *
 * 24    2/27/99 4:37p Samir
 * return name of loop currently playing.
 *
 * 23    2/26/99 5:26p Samir
 * fixes to streaming audio to reflect fix in direct sound mixer.
 *
 * 22    2/22/99 3:23p Luke
 * upped size of music buffers
 *
 * 21    2/16/99 12:09p Samir
 * immediate switches open new stream object.
 *
 * 20    1/28/99 2:22p Samir
 * simplified music system for D3.
 *
 * 19    12/13/98 6:51p Samir
 * enhancements.
 *
 * 18    12/11/98 6:05p Samir
 * fixed looping bug (didn't set loop count!)
 *
 * 17    12/11/98 4:02p Samir
 * clean theme changes.
 *
 * 16    12/10/98 10:12a Samir
 * uses newer streaming audio library
 *
 * 15    12/07/98 11:45a Samir
 * hacks to get music system mostly working in DS_8.  Will change this
 * system so it's a lot cleaner after music demo.
 *
 * 14    12/03/98 12:48p Samir
 * speed up sequencer so that gap between samples isn't too big.
 *
 * 13    11/20/98 5:20p Samir
 * added a bunch of high level scripting commands.
 *
 * 12    11/16/98 4:15p Samir
 * fadeouts.
 *
 * 11    11/13/98 2:27p Samir
 * new music system.
 *
 * 10    8/10/98 5:53p Samir
 * improved switching between streams and basic background/combat music.
 *
 * 9     7/30/98 7:33p Jeff
 * fixed bug passing NULL to reset.
 *
 * 8     7/28/98 5:43p Samir
 * reorg of music system.
 *
 * 7     7/24/98 5:20p Samir
 * first real music checkin.
 *
 * 6     7/08/98 6:26p Samir
 * took out obsolete code.
 *
 * 5     2/15/98 7:12p Chris
 * More improvements to the sound lib
 *
 * 4     1/05/98 3:54p Chris
 * Added ambient and explosion sounds
 *
 * 3     12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 2     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 3     5/29/97 3:58p Samir
 * Works with some very small pauses.
 *
 * 2     5/23/97 4:34p Samir
 *
 * $NoKeywords: $
 */

#include "music.h"
#include "musiclib.h"
#include "pserror.h"
#include "streamaudio.h"
#include "mem.h"
#include <string.h>
#include <stdlib.h>

// #include "samirlog.h"
#define LOGFILE(_s)

OutrageMusicSeq::OutrageMusicSeq() {
  m_sequencer_run = false;
  m_sequencer_init = false;
  m_str_buffer = NULL;
  m_ins_buffer = NULL;
  m_curregion = -1;
  m_pending_song = m_active_song = m_playing_song = NULL;
}

OutrageMusicSeq::~OutrageMusicSeq() { OutrageMusicSeq::Shutdown(); }

//	takes a OMS theme file.
bool OutrageMusicSeq::Init(const char *theme_file) {
  // reset streams
  m_dominant_strm = 0;
  m_timer = 0.0f;

  if (theme_file[0] == 0) {
    return false;
  }

  Stop();

  // initialize memory buffers
  m_ins_buffer = (music_ins *)mem_malloc(sizeof(music_ins) * MAX_MUSIC_INSTRUCTIONS);
  m_str_buffer = (char *)mem_malloc(MAX_MUSIC_STRLEN);
  m_ins_curptr = m_ins_buffer;
  m_str_curptr = m_str_buffer;
  m_str_curptr[0] = 0;

  //	initialize music lists
  m_music_list.free();
  m_tracklist.init(64);
  m_pending_song = m_active_song = m_playing_song = NULL;
  m_output_q.flush();
  m_curregion = -1;

  OutrageMusicSeq::SetVolume(1.0f);
  m_sequencer_init = true;

  return LoadTheme(theme_file);
}

void OutrageMusicSeq::Shutdown() {
  if (!m_sequencer_init)
    return;

  Stop();

  // free music lists.
  FreeList();
  m_tracklist.free();

  // free allocated buffers
  mem_free(m_ins_buffer);
  mem_free(m_str_buffer);

  // free streams
  for (int i = 0; i < OMS_NUM_STRM; i++)
    m_strm[i].Reset(this);

  m_playing_song = NULL;
  m_sequencer_init = false;
}

//	starts the sequencer (usually at the beginning of a level)
void OutrageMusicSeq::Start() {
  if (IsSequencerRunning() || !m_sequencer_init)
    return;

  int i;

  m_sequencer_run = true;
  m_dominant_strm = 0;

  m_timer = 0.0f;

  for (i = 0; i < N_MUSIC_REGS; i++) {
    m_registers[i] = 0;
  }

  mprintf(0, "Music system on.\n");
}

//	stops the sequencer, flushes events
void OutrageMusicSeq::Stop() {
  if (!IsSequencerRunning())
    return;

  int i;

  mprintf(0, "Music system off.\n");
  m_sequencer_run = false;

  for (i = 0; i < OMS_NUM_STRM; i++) {
    m_strm[i].Reset(this);
  }
}

//	set volume of sequencer
void OutrageMusicSeq::SetVolume(float vol) {
  int i;

  ASSERT(vol >= 0.0f && vol <= 1.0f);
  m_mastervol = vol;

  for (i = 0; i < OMS_NUM_STRM; i++)
    m_strm[i].SetVolume(m_mastervol);
}

#define START_PENDING_SONG()                                                                                           \
  do {                                                                                                                 \
    ASSERT(m_pending_song);                                                                                            \
    if (m_active_song) {                                                                                               \
      m_pending_song->strm = m_active_song->strm;                                                                      \
    }                                                                                                                  \
    m_active_song = m_pending_song;                                                                                    \
    if (m_active_song) {                                                                                               \
      m_active_song->stream_idle = false;                                                                              \
      m_active_song->request_stop = false;                                                                             \
    }                                                                                                                  \
    m_pending_song = NULL;                                                                                             \
  } while (0)

//	runs a frame of input.
void OutrageMusicSeq::Frame(float frame_time) {
  bool start_pending_song = false;
  int i;

  // run check.
  if (!m_sequencer_run)
    return;

  // close all streams that aren't the dominant one and have stopped playing
  for (i = 0; i < OMS_NUM_STRM; i++) {
    if ((&m_strm[i]) != (&m_strm[m_dominant_strm])) {
      if (m_strm[i].m_stream.State() == STRM_STOPPED) {
        m_strm[i].m_stream.Close();
      }
    }
  }

  // determine when to start song if a song is pending.
  if (!m_active_song && m_pending_song) {
    start_pending_song = true;
  }

  if (m_pending_song) {
    if (m_pending_song->immediate_switch == true) {
      start_pending_song = true;
    } else if (m_active_song) {
      if (m_active_song->stream_idle) {
        // this will transfer the current song's steam to the pending one, so the
        // ExecScript function can manage these streams.
        start_pending_song = true;
      } else if (!m_active_song->request_stop) {
        m_active_song->request_stop = true;
      }
    }
  }

  if (start_pending_song) {
    mprintf(0, "MUSIC:Starting pending song.\n");
    LOGFILE((_logfp, "MUSIC:Starting pending song.\n"));
    START_PENDING_SONG();
  }

  // execute song code
  ExecScript(m_active_song);

  //	process streams, starting at dominant stream.
  //	this is vital to ensure that the dominant stream's commands are executed before any
  //	other streams.
  //	i = m_dominant_strm;
  //	do
  //	{
  //		m_strm[i].Process(frame_time);
  //		i++;
  //		if (i == OMS_NUM_STRM) i = 0;
  //	}
  //	while (i != m_dominant_strm);

  m_timer += frame_time;
}

// music kernal.
void OutrageMusicSeq::ExecScript(music_stream *strm) {
  if (!strm)
    return;

// get command
next_ins:
  music_ins *cur_ins = &strm->ins[strm->ip];
  uint8_t cmd = cur_ins->cmd;
  tMusicVal val = cur_ins->opr.num;
  char *str = cur_ins->opr.str;
  const char *name;

  // goto next instruction.
  strm->ip++;

  //	mprintf(0, "%d ", cmd);
  AudioStream *stream = &strm->strm->m_stream;

  // execute opcodes.
  //	if (strm->last_ip != strm->ip) {
  //		LOGFILE((_logfp, "ins=%d\n", cmd));
  //	}
  strm->last_ip = strm->ip;

  switch (cmd) {
  case OMFCMD_PLAY:
    name = m_tracklist.get(strm->ln_reg);
    if (name) {
      // close this song's stream.
      bool err = false;

      strm->old_strm = strm->strm;

      strm->error = false;

      if (strm->immediate_switch) {
        // we start playing the current stream immediately.
        stream->Close();
        m_dominant_strm = DOMINANT_STRM_ADJUST();
        //	mprintf(0, "MUSIC: Starting stream with %s on channel %d.\n", name, m_dominant_strm);
        LOGFILE((_logfp, "MUSIC: Starting stream with %s on channel %d.\n", name, m_dominant_strm));
        strm->strm = &m_strm[m_dominant_strm];
        stream = &strm->strm->m_stream;
        err = stream->Open(name);
      } else {
        m_dominant_strm = DOMINANT_STRM_ADJUST();
        //	mprintf(0, "MUSIC: Preparing stream with %s on channel %d.\n", name, m_dominant_strm);
        LOGFILE((_logfp, "MUSIC: Preparing stream with %s on channel %d.\n", name, m_dominant_strm));
        strm->strm = &m_strm[m_dominant_strm];
        stream = &strm->strm->m_stream;
        err = stream->Open(name);
        //	stream->Open(name, STRM_OPNF_GRADUAL);
      }

      // skip instructions until error is cleared.
      if (!err) {
        //	mprintf(0, "MUSIC: Error opening stream %s on channel %d.\n", name, m_dominant_strm);
        LOGFILE((_logfp, "MUSIC: Error opening stream %s on channel %d.\n", name, m_dominant_strm));
        strm->error = true;
      }

      stream->SetLoopCount(strm->p_reg);
      stream->SetVolume(m_mastervol);
      strm->stream_idle = false;
    } else {
      mprintf(0, "OMS: Stream was not found in track list.\n");
    }

    strm->pending_loop_name = name;
    break;

  case OMFCMD_MPLAY:
    if (strm->immediate_switch || strm->error) {
      strm->immediate_switch = false;
    } else if (!stream->IsReady()) {
      strm->ip--;
      break;
    } else if (strm->old_strm) {
      if (strm->old_strm->m_stream.State() != STRM_STOPPED && strm->old_strm->m_stream.State() != STRM_INVALID) {
        strm->ip--;
        break;
      }
    }
    strm->loop_name = strm->pending_loop_name;
    m_playing_song = strm;

    if (!strm->error) {
      strm->error = !(stream->Play());
    }

    if (!strm->error) {
      //	mprintf(0, "MUSIC: playing %s.\n", strm->loop_name);
      LOGFILE((_logfp, "MUSIC: playing %s.\n", strm->loop_name));
      LOGFILE((_logfp, "MUSIC: state of played stream is %d.\n", strm->loop_name, stream->State()));
    } else {
      //	mprintf(0, "MUSIC: Error playing %s.\n", strm->loop_name);
      LOGFILE((_logfp, "MUSIC: Error playing %s.\n", strm->loop_name));
    }
    break;

  case OMFCMD_WAIT:
    Int3(); // flaky, shouldn't be used anymore.
    strm->ip--;
    if (val == 1) {
      if (strm->strm->m_valid_result && strm->strm->m_result.cmd == OMS_STRM_STOP) {
        // wait till stream has finished to continue.
        strm->ip++;
      }
    }
    break;

  case OMFCMD_LCMP:
    strm->c_reg = val;
    break;

  case OMFCMD_LLPT:
    strm->ln_reg = str;
    break;

  case OMFCMD_LPLC:
    strm->p_reg = val;
    break;

  case OMFCMD_SETI:
    strm->i_reg = val;
    break;

  case OMFCMD_INCI:
    strm->i_reg++;
    break;

  case OMFCMD_IFI:
    strm->ifi_block = (strm->i_reg == val) ? true : false;
    if (!strm->ifi_block) {
      // skip ifi block.
      while (strm->ins[strm->ip].cmd != OMFCMD_ENDIFI)
        strm->ip++;
      strm->ip++;
    }
    break;

  case OMFCMD_ENDIFI:
    strm->ifi_block = false;
    break;

  case OMFCMD_COMPARE: {
    tMusicVal reg1 = strm->c_reg;
    tMusicVal reg2 = m_registers[val];
    strm->b_reg = (reg2 - reg1);
    break;
  }

  case OMFCMD_GOTO:
    // simply set IP.
    strm->ip = val;
    break;

  case OMFCMD_BLT:
    if (strm->b_reg < 0) {
      strm->ip = val;
    }
    break;

  case OMFCMD_BGT:
    if (strm->b_reg > 0) {
      strm->ip = val;
    }
    break;

  case OMFCMD_BEQ:
    if (strm->b_reg == 0) {
      strm->ip = val;
    }
    break;

  case OMFCMD_BNIF:
    if (stream->ReadAheadFinishedLoop() || strm->error) {
      oms_q_evt evt;
      evt.cmd = OMS_EVT_LOOPENDING;
      evt.parm.i = strm->type;
      m_output_q.send(evt);
      if (!strm->error) {
        strm->ip--; // repeat this instruction again
      }
    } else if (!strm->request_stop) {
      if (stream->ReadAhead()) {
        strm->ip = val;
      } else if (stream->State() != STRM_STOPPING && stream->State() != STRM_STOPPED) {
        strm->ip = val;
      }
    } else {
      stream->Stop(true); // soft stop on end of stream.
      if (strm->request_stop) {
        strm->stream_idle = true;
        strm->request_stop = false;
        mprintf(0, "MUSIC: Processed stop request.\n");
        LOGFILE((_logfp, "MUSIC: Processed stop request.\n"));
      }
    }
    break;

  case OMFCMD_ENDSECTION: {
    strm->ip--;
    if (stream->State() == STRM_STOPPED) {
      oms_q_evt evt;
      strm->ip++;
      evt.cmd = OMS_EVT_SONGENDED;
      evt.parm.i = strm->type;
      m_output_q.send(evt);
      strm->stream_idle = true;
      m_active_song = NULL;
      m_playing_song = NULL;
    }
    break;
  }
  }

  // okay, ifi_block is only really useful to determine if we're going to execute consecutive instructions
  // note that even if we turn off ifi_block, this doesn't stop instructions from running inside the ifi_block
  // but it does stop consecutive instructions.
  // the actual decision to run the instructions in an ifi_block depends on the initial check.
  if (cmd != OMFCMD_ENDSECTION && cmd != OMFCMD_PLAY && cmd != OMFCMD_MPLAY && cmd < OMFCMD_BRANCHING) {
    goto next_ins;
  } else {
    strm->ifi_block = false;
  }
}

// start a song, stopping the old either cleanly (on measure) or abruptly.
void OutrageMusicSeq::StartSong(int song, bool clean_switch) {
  if (m_curregion >= 0) {
    m_pending_song = GetSong(m_curregion, (int16_t)song);
  } else {
    m_pending_song = NULL;
  }

  if (m_pending_song) {
    m_pending_song->request_stop = false;
    m_pending_song->immediate_switch = !clean_switch;
    m_pending_song->strm = &m_strm[m_dominant_strm];
  }
}

// stops song, cold.
void OutrageMusicSeq::StopSong() {
  if (m_active_song) {
    m_active_song = NULL;
    m_playing_song = NULL;
  }
  m_strm[m_dominant_strm].m_stream.Close();
}

//	pauses
void OutrageMusicSeq::Pause() {
  int i;

  for (i = 0; i < OMS_NUM_STRM; i++) {
    m_strm[i].m_stream.Pause();
  }
}

void OutrageMusicSeq::Resume() {
  int i;

  for (i = 0; i < OMS_NUM_STRM; i++) {
    m_strm[i].m_stream.Resume();
  }
}

// get and set user defined (theme file) parameters
void OutrageMusicSeq::SetRegister(int parm, tMusicVal val) {
  ASSERT(parm >= 0 && parm < N_MUSIC_REGS);
  m_registers[parm] = val;
}

tMusicVal OutrageMusicSeq::GetRegister(int parm) {
  ASSERT(parm >= 0 && parm < N_MUSIC_REGS);
  return m_registers[parm];
}

// memory management
OutrageMusicSeq::music_ins *OutrageMusicSeq::alloc_and_copy_ins(int len, const music_ins *ins) {
  // copy instructions to static buffer and return a pointer to it
  if ((m_ins_curptr + len) > (m_ins_buffer + MAX_MUSIC_INSTRUCTIONS)) {
    Int3();
    return NULL;
  } else {
    memcpy(m_ins_curptr, ins, len * sizeof(music_ins));
    m_ins_curptr += len;
    return (m_ins_curptr - len);
  }
}

char *OutrageMusicSeq::alloc_and_copy_str(const char *str) {
  // copy string to static buffer and return a pointer to it
  int slen = strlen(str) + 1;
  if ((m_str_curptr + slen) > (m_str_buffer + MAX_MUSIC_STRLEN)) {
    Int3();
    return NULL;
  } else {
    strcpy(m_str_curptr, str);
    m_str_curptr += slen;
    return (m_str_curptr - slen);
  }
}

//	Music list management
OutrageMusicSeq::music_stream *OutrageMusicSeq::AddToList(int16_t region, int16_t theme_type, int len,
                                                          const music_ins *ins) {
  tListNode<music_stream> *node = new tListNode<OutrageMusicSeq::music_stream>;

  // create list item
  node->t.region = region;
  node->t.type = theme_type;
  node->t.ins = alloc_and_copy_ins(len, ins);
  if (!node->t.ins) {
    delete node;
    return NULL;
  }

  // link it in.
  m_music_list.link(node);

  return &node->t;
}

void OutrageMusicSeq::FreeList() {
  tListNode<music_stream> *node;

  while ((node = m_music_list.start())) {
    node = m_music_list.unlink();
    delete[] node;
  }

  m_music_list.free();
}

OutrageMusicSeq::music_stream *OutrageMusicSeq::GetSong(int16_t region, int16_t theme_type) {
  tListNode<music_stream> *node = m_music_list.start();
  music_stream *strm = NULL;
  int i;

  for (i = 0; i < m_music_list.length(); node = m_music_list.next(), i++) {
    if (region == node->t.region) {
      if (theme_type == node->t.type) {
        strm = &node->t;
      }

      if (strm) {
        strm->request_stop = false;
        strm->immediate_switch = false;
        strm->ip = 0;
        strm->b_reg = 0;
        strm->c_reg = 0;
        strm->ln_reg = 0;
        strm->p_reg = 0;
        strm->i_reg = 0;
        strm->ifi_block = false;
        strm->stream_idle = true;
        strm->strm = NULL;
        strm->old_strm = NULL;
        strm->loop_name = NULL;
        strm->pending_loop_name = NULL;
        strm->last_ip = -1;
        strm->error = false;
        break;
      }
    }
  }

  return strm;
}

//@@void OutrageMusicSeq::seqSilence()
//@@{
//@@//	silence all streams.
//@@	int init_strm = m_dominant_strm;
//@@	do
//@@	{
//@@	// request switch to dominant stream when measure is complete.
//@@		m_strm[m_dominant_strm].SEND_STRM_FADEOUT(4.0f);
//@@		m_strm[m_dominant_strm].SEND_STRM_STOP();
//@@		m_strm[m_dominant_strm].SEND_STRM_FREE();
//@@		m_dominant_strm = DOMINANT_STRM_ADJUST();
//@@	}
//@@	while (init_strm != m_dominant_strm);
//@@}

void OutrageMusicSeq::SetCurrentRegion(int16_t region) { m_curregion = region; }

int16_t OutrageMusicSeq::GetCurrentRegion() const { return m_curregion; }

// get current loop playing
const char *OutrageMusicSeq::GetCurrentLoopName(int *count) {
  if (m_playing_song) {
    *count = m_playing_song->strm->m_stream.GetLoopCount();
    return m_playing_song->loop_name;
  }

  *count = 0;
  return NULL;
}

// gets current region PLAYING, not PENDING like above.
int16_t OutrageMusicSeq::GetPlayingRegion() const {
  if (m_playing_song) {
    return m_playing_song->region;
  }

  return -1;
}
