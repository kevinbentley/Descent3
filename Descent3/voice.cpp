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

 * $Logfile: /DescentIII/Main/voice.cpp $
 * $Revision: 11 $
 * $Date: 5/13/99 3:42p $
 * $Author: Ardussi $
 *
 * implementation file for voice system
 *
 * $Log: /DescentIII/Main/voice.cpp $
 *
 * 11    5/13/99 3:42p Ardussi
 * changes for compiling on the Mac
 *
 * 10    2/10/99 4:45p Jeff
 * table file parser stuff
 *
 * 9     9/28/98 4:36p Jeff
 * shortcircuit the voices for the demo
 *
 * 8     7/24/98 5:19p Samir
 * took out old stream code.
 *
 * 7     7/13/98 6:07p Jeff
 * handled not removing non-powerup voices on a queue clean up
 *
 * 6     7/09/98 8:35p Samir
 * Changed StreamStop.
 *
 * 5     6/19/98 6:04p Jeff
 * added voice queue
 *
 * 4     6/18/98 5:18p Jeff
 * Use new streamaudio system
 *
 * 3     6/17/98 8:08p Jeff
 * removed DoVoiceFrame
 *
 * 2     6/08/98 3:55p Jeff
 * rough initial creation
 *
 * $NoKeywords: $
 */
#include "voice.h"
#include "streamaudio.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include <stdlib.h>
#include <string.h>

#define MOTHERLOAD_STRING "Cheater!"
#define MOTHERLOAD_FLAGS VF_POWERUP | VF_PLAYTABLE

struct tVoice {
  int handle;
  int flags;
  int chandle;
  bool inuse;
};

bool PlayPowerupVoice;
bool PlayVoices;

#define QUEUE_SIZE 3

class VoiceQueue {
public:
  VoiceQueue();
  ~VoiceQueue();
  void AddVoice(char *fn, int flg);
  bool GetNextVoice(char *fn, int *flg);
  void Clear(bool onlypowerups = false);

private:
  char filenames[QUEUE_SIZE][_MAX_PATH];
  int flags[QUEUE_SIZE];
  uint8_t currvoice;
  uint8_t pos;
  char motherloadat;
  bool inuse[QUEUE_SIZE];
  bool full;
};

tVoice CurrentVoiceHandle;
VoiceQueue vq;

static void StartVoice(char *filename, int flags);
static void StopVoice(void);

bool InitVoices(void) {
  mprintf(0, "Voice System: Init\n");
  CurrentVoiceHandle.handle = -1;
  CurrentVoiceHandle.flags = 0;
  CurrentVoiceHandle.chandle = -1;
  CurrentVoiceHandle.inuse = false;
  vq.Clear();

  atexit(CloseVoices);
  return true;
}

void CloseVoices(void) {
  mprintf(0, "Voice System: Shutdown\n");
  StopVoice();
}

// MTS: unused
void PlayVoice(char *filename, int flags) {
#ifdef DEMO
  return;
#endif
  if ((!PlayPowerupVoice) && (flags & VF_POWERUP) && (!(flags & VF_FORCE)))
    return;
  if ((CurrentVoiceHandle.inuse) && (flags & VF_INTERUPT)) {
    StopVoice();
    vq.Clear();
  }
  vq.AddVoice(filename, flags);
}

void StartVoice(char *filename, int flags) {
#ifdef DEMO
  return;
#endif
  if ((!PlayVoices) && (!(flags & VF_FORCE)))
    return;

  if (flags & VF_PLAYTABLE) {
    CurrentVoiceHandle.flags = flags;
    CurrentVoiceHandle.inuse = true;
    CurrentVoiceHandle.chandle = -1;
    int index = FindSoundName(IGNORE_TABLE(filename));
    CurrentVoiceHandle.handle = Sound_system.Play2dSound(index);
    return;
  }

  bool compressed = (flags & VF_COMPRESSED) ? true : false;
  bool bit8 = (flags & VF_8BIT) ? true : false;
  bool stereo = (flags & VF_STEREO) ? true : false;

  int vf = 0;

  //	if(bit8){
  //		if(stereo)
  //			vf = SAF_8BIT_S;
  //		else
  //			vf = SAF_8BIT_M;
  //	}else{
  //		if(stereo)
  //			vf = SAF_16BIT_S;
  //		else
  //			vf = SAF_16BIT_M;
  //	}
  //	if(compressed)
  //		vf |= SAF_COMPRESSED;

  CurrentVoiceHandle.chandle = StreamPlay(filename, (MAX_GAME_VOLUME / 2.0), vf);
  if (CurrentVoiceHandle.chandle != -1)
    CurrentVoiceHandle.handle = StreamGetSoundHandle(CurrentVoiceHandle.chandle);

  CurrentVoiceHandle.flags = flags;
  CurrentVoiceHandle.inuse = true;
}

void StopVoice(void) {
  if (CurrentVoiceHandle.inuse) {
    if (CurrentVoiceHandle.flags & VF_PLAYTABLE) {
      if (CurrentVoiceHandle.handle != -1)
        Sound_system.StopSoundImmediate(CurrentVoiceHandle.handle);
    } else {
      if (CurrentVoiceHandle.chandle != -1)
        StreamStop(CurrentVoiceHandle.chandle);
    }
  }
  CurrentVoiceHandle.handle = -1;
  CurrentVoiceHandle.flags = 0;
  CurrentVoiceHandle.chandle = -1;
  CurrentVoiceHandle.inuse = false;
}

void UpdateVoices(void) {
  char filename[_MAX_PATH];
  int flags;

  if (!CurrentVoiceHandle.inuse) {
    // see if we have something waiting
    if (vq.GetNextVoice(filename, &flags)) {
      mprintf(0, "Playing queued voice %s\n", filename);
      StartVoice(filename, flags);
      return;
    }
    return;
  }

  // according to the handle, the current voice is inuse, lets make sure
  if (Sound_system.IsSoundPlaying(CurrentVoiceHandle.handle))
    return; // it is

  // it isn't, so stop it and play the next voice in the queue if any
  StopVoice();
  if (vq.GetNextVoice(filename, &flags)) {
    mprintf(0, "Playing queued voice %s\n", filename);
    StartVoice(filename, flags);
  }
}

//////////////////////
// Voice Queue Implementation

VoiceQueue::VoiceQueue() {
  currvoice = pos = 0;
  motherloadat = -1;
  full = false;
  for (int i = 0; i < QUEUE_SIZE; i++)
    inuse[i] = false;
}

VoiceQueue::~VoiceQueue() { Clear(); }

void VoiceQueue::AddVoice(char *fn, int flg) {
  if (motherloadat != -1)
    return;
  if (full) {
    // since the queue is full, remove everything and add just the "mother load" voice
    Clear(true);
    strcpy(filenames[pos], MOTHERLOAD_STRING);
    flags[pos] = MOTHERLOAD_FLAGS;
    motherloadat = pos;
    inuse[pos] = true;
    return;
  }

  // the queue isn't full yet, so add it in
  int nextpos = (pos + 1) % QUEUE_SIZE;
  if ((nextpos == currvoice + 1) && (inuse[nextpos])) {
    // this really shouldn't be since it was reported that the queue isn't full
    mprintf(0, "Voice Queue full, missed full bool (this shouldn't happen)\n");
    // since the queue is full, remove everything and add just the "mother load" voice
    Clear();
    pos = 1;
    strcpy(filenames[pos], MOTHERLOAD_STRING);
    flags[pos] = MOTHERLOAD_FLAGS;
    motherloadat = pos;
    inuse[pos] = true;
    return;
  }
  pos = nextpos;
  strcpy(filenames[pos], fn);
  flags[pos] = flg;
  inuse[pos] = true;
  for (int i = 0; i < QUEUE_SIZE; i++) {
    // check to see if the queue is full now
    if (inuse[i] == false)
      return;
  }
  // queue is full
  full = true;
}

bool VoiceQueue::GetNextVoice(char *fn, int *flg) {
  int p = (++currvoice) % QUEUE_SIZE;
  if (!inuse[p])
    return false;
  inuse[p] = false;
  strcpy(fn, filenames[p]);
  *flg = flags[p];
  currvoice = p;
  if (currvoice == motherloadat)
    motherloadat = -1;
  full = false;
  return true;
}

void VoiceQueue::Clear(bool onlypowerups) {
  int i;

  for (i = 0; i < QUEUE_SIZE; i++) {
    if ((!onlypowerups) || (flags[i] & VF_POWERUP))
      inuse[i] = false;
  }
  if (onlypowerups) {
    // we need to adjust all the buffers so what is left (non-powerup voices) are pushed to the
    // front
    int realp = 0;
    for (i = 0; i < QUEUE_SIZE; i++) {
      if (inuse[i] && (i != realp)) {
        // we'll need to move this guy
        inuse[i] = false;
        inuse[realp] = true;
        flags[realp] = flags[i];
        strcpy(filenames[realp], filenames[i]);
        // adjust pointers so they are pointing to the newly moved pointers
        if (motherloadat == i)
          motherloadat = realp;
        if (currvoice == i)
          currvoice = realp;
        if (pos == i)
          pos = realp;
        realp++;
      } // endif
    }   // end for
    if (realp == QUEUE_SIZE) {
      // we're still full :(
      full = true;
      mprintf(0, "Voice Warning: Buffer still full after clean (All Non-powerups voices in queue?)\n");
    }
  } else {
    motherloadat = -1;
    full = false;
    currvoice = pos = 0;
  }
}
