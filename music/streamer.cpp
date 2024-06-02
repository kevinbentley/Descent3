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

 * $Logfile: /DescentIII/Main/music/streamer.cpp $
 * $Revision: 10 $
 * $Date: 4/01/99 4:50p $
 * $Author: Matt $
 *
 * Stream interface with sequencer.
 *
 * $Log: /DescentIII/Main/music/streamer.cpp $
 *
 * 10    4/01/99 4:50p Matt
 * Took out Warning() function, chaning those calls to mprintf()
 *
 * 9     2/26/99 5:26p Samir
 * fixes to streaming audio to reflect fix in direct sound mixer.
 *
 * 8     12/10/98 10:12a Samir
 * uses newer streaming audio library
 *
 * 7     12/07/98 11:45a Samir
 * hacks to get music system mostly working in DS_8.  Will change this
 * system so it's a lot cleaner after music demo.
 *
 * 6     12/03/98 12:48p Samir
 * speed up sequencer so that gap between samples isn't too big.
 *
 * 5     11/20/98 5:21p Samir
 * added SEND_STRM_NEXT
 *
 * 4     11/13/98 2:27p Samir
 * new music system.
 *
 * 3     8/10/98 5:53p Samir
 * improved switching between streams and basic background/combat music.
 *
 * 2     7/28/98 5:43p Samir
 * reorg of music system.
 *
 * 1     7/28/98 12:47p Samir
 * moved and revamped from sequencer.cpp
 *
 * $NoKeywords: $
 */

#include "music.h"
#include "streamaudio.h"
#include "pserror.h"

oms_stream::oms_stream() {}

oms_stream::~oms_stream() {}

// processes a stream's events.
void oms_stream::Process(float frmtime) {
  oms_q_evt evt, evt2 = {}; // event for use

  if (m_timer > 0.0f)
    m_timer -= frmtime;

  // invalidate current process result.
  m_valid_result = false;

  if (!processCommand())
    return;

  //	process queue events.
  if (!m_q.recv(&evt))
    return;

  switch (evt.cmd) {
  case OMS_STRM_LOAD:
    processQLoad((const char *)evt.parm.p);
    break;

  case OMS_STRM_FADEOUT:
    //	reset timer for fadeout to 0 volume
    STREAM_COMMANDI(OMS_STRM_FADEOUT);
    STREAM_TIMER(evt.parm.f);
    break;

  case OMS_STRM_FADEIN:
    //	fade in to volume m_maxvol
    STREAM_COMMANDI(OMS_STRM_FADEIN);
    STREAM_TIMER(evt.parm.f);
    break;

  case OMS_STRM_STOP:
    STREAM_COMMANDI(OMS_STRM_STOP);
    m_stream.Stop();
    break;

  case OMS_STRM_FREE:
    STREAM_COMMANDI(OMS_STRM_FREE);
    m_stream.Close();
    break;

  case OMS_STRM_PLAY:
    //	process queue events.
    if (!m_q.recv(&evt2)) {
      Int3();
    }
    STREAM_COMMANDI(OMS_STRM_PLAY, evt2.parm.i);
    m_stream.SetLoopCount(evt2.parm.i);
    m_stream.SetVolume(evt.parm.f);
    m_stream.Play();
    break;

  case OMS_STRM_SWITCH:
    STREAM_COMMANDP(OMS_STRM_SWITCH, evt.parm.p);
    m_stream.Stop(true, &m_data.i);
    mprintf(0, "%d-%d ", m_data.i, m_stream.State());
    break;

  case OMS_STRM_NEXT:
    //		m_stream.Next((const char *)evt.parm.p);
    if (!m_q.recv(&evt2)) {
      Int3();
    }
    m_data.f = evt2.parm.f;
    if (!m_q.recv(&evt2)) {
      Int3();
    }
    m_data2.i = evt2.parm.i;
    if (!m_q.recv(&evt2)) {
      Int3();
    }
    STREAM_COMMANDP(OMS_STRM_NEXT, evt2.parm.p);
    *(bool *)(evt2.parm.p) = true;
    break;
  }
}

// sends an event to the stream.
void oms_stream::Send(oms_q_evt *evt) { m_q.send(*evt); }

// reset stream.
void oms_stream::Reset(OutrageMusicSeq *seq) {
  m_timer = 0.0f;
  m_timer_init = 0.0f;
  m_maxvol = 1.0f;
  m_status.cmd = OMS_STRM_FREE;
  m_seq = seq;
  m_q.flush();
  m_stream.Close();
}

// volume.
void oms_stream::SetVolume(float vol) {
  m_maxvol = vol;
  m_stream.SetVolume(vol);
}

// processes current command on stream, return false to end processing.
bool oms_stream::processCommand() {
  switch (m_status.cmd) {
  case OMS_STRM_FADEIN:
    // timed fadein to dest volume
    if (m_timer <= 0.0f) {
      m_stream.SetVolume(m_maxvol);
      STREAM_COMMANDI(OMS_STRM_PLAY);
    } else {
      m_stream.SetVolume(m_maxvol * (m_timer_init - m_timer) / m_timer_init);
    }
    return false;

  case OMS_STRM_FADEOUT:
    // timed fadeout to dest volume
    if (m_timer <= 0.0f) {
      m_stream.SetVolume(0.0f);
      STREAM_COMMANDI(OMS_STRM_PLAY);
    } else {
      m_stream.SetVolume(m_maxvol * m_timer / m_timer_init);
    }
    return false;

  case OMS_STRM_SWITCH:
    // if current measure is greater than initial measure at switch, then we will stop
    // this stream and send a play command to the current dominant stream.
    //	mprintf(0, "%d-%d ",m_data.i, m_stream.State());
    if (m_data.i || m_stream.State() == STRM_STOPPED || m_stream.State() == STRM_INVALID) {
      bool *still_playing = (bool *)m_status.parm.p;
      *still_playing = false;
      if (m_status.cmd != OMS_STRM_STOP) {
        STREAM_COMMANDI(OMS_STRM_STOP);
        m_valid_result = true;
        m_result.cmd = OMS_STRM_STOP;
      }
    }
    return false;

  case OMS_STRM_PLAY:
    //	check if stream is still playing.  if not, then set current stream status and signal
    // a normal song end.
    if (m_stream.State() == STRM_STOPPED) {
      if (m_status.cmd != OMS_STRM_STOP) {
        STREAM_COMMANDI(OMS_STRM_STOP);
        m_valid_result = true;
        m_result.cmd = OMS_STRM_STOP;
        return false;
      }
    }
    break;

  case OMS_STRM_NEXT:
    //		if (m_stream.HasNextStarted()) {
    //			*(bool *)(m_status.parm.p) = false;
    //			m_stream.SetLoopCount(m_data2.i);
    //			m_stream.SetVolume(m_data.f);
    //			STREAM_COMMANDI(OMS_STRM_PLAY, m_data2.i);
    //			return false;
    //		}
    //		else {
    //			*(bool *)(m_status.parm.p) = true;
    //		}
    break;
  }

  return true;
}

// processes load song q event.
void oms_stream::processQLoad(const char *fname) {
  m_stream.Close();

  if (m_stream.Open(fname)) {
    STREAM_COMMANDP(OMS_STRM_LOAD, (void *)fname);
    m_data.p = (void *)fname;
  } else {
    mprintf(0, "OMS: Couldn't load song %s.\n", fname);

    STREAM_COMMANDI(OMS_STRM_FREE);
    m_valid_result = true;
    m_result.cmd = OMS_EVT_SONGENDED;
    m_result.parm.p = (void *)fname;
  }
}

//	THESE FUNCTIONS SEND EVENTS TO THE STREAM EASILY

void oms_stream::SEND_STRM_LOAD(const char *fname) {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_LOAD;
  evt.parm.p = (void *)fname;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_FADEOUT(float time) {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_FADEOUT;
  evt.parm.f = time;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_FADEIN(float time) {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_FADEIN;
  evt.parm.f = time;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_STOP() {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_STOP;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_PLAY(float vol, uint8_t count) {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_PLAY;
  evt.parm.f = vol;
  m_q.send(evt);
  evt.cmd = OMS_STRM_PARM;
  evt.parm.i = (int)count;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_FREE() {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_FREE;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_SWITCH(bool *switch_flag) {
  oms_q_evt evt;
  evt.cmd = OMS_STRM_SWITCH;
  evt.parm.p = (void *)switch_flag;
  m_q.send(evt);
}

void oms_stream::SEND_STRM_NEXT(const char *fname, float vol, uint8_t count, bool *switch_flag) {
  oms_q_evt evt;

  evt.cmd = OMS_STRM_NEXT;
  evt.parm.p = (void *)fname;
  m_q.send(evt);
  evt.cmd = OMS_STRM_PARM;
  evt.parm.f = vol;
  m_q.send(evt);
  evt.cmd = OMS_STRM_PARM;
  evt.parm.i = (int)count;
  m_q.send(evt);
  evt.cmd = OMS_STRM_PARM;
  evt.parm.p = (void *)switch_flag;
  m_q.send(evt);
}
