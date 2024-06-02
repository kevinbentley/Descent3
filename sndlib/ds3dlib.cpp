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

 * $Logfile: /DescentIII/Main/dd_sndlib/Ds3dlib.cpp $
 * $Revision: 149 $
 * $Date: 9/27/99 5:38p $
 * $Author: Samir $
 *
 * DirectSound(2d and 3d) implementation of the Descent III low-level sound interface
 *
 * $Log: /DescentIII/Main/dd_sndlib/Ds3dlib.cpp $
 *
 * 149   9/27/99 5:38p Samir
 * EAX 2.0->1.0 compatibility checkin.
 *
 * 148   8/23/99 5:29p Samir
 * incremental EAX 2.0 checkin
 *
 * 147   8/13/99 2:00p Samir
 * more aureal and geometry fixes.
 *
 * 146   5/23/99 12:48a Samir
 * decreased rolloff factor of 3d sounds under 3d sound mixers from 0.75
 * to 0.5
 *
 * 145   5/20/99 6:23p Kevin
 * minor speed up of software mixer and fix for memory debugging
 *
 * 144   5/20/99 1:00a Samir
 * changes in ordering of EAX and NONE mixers.
 *
 * 143   5/09/99 7:09p Samir
 * fixed sound card selection (enumeration) problems.
 *
 * 142   5/07/99 5:39p Samir
 * better error checking for CheckAndForceDataAlloc for PageInSound.
 *
 * 141   5/03/99 3:12a Samir
 * fixed up aureal so it works (a little slow though...)
 *
 * 140   5/01/99 10:25p Jeff
 * (samir) fixed crash bug when alt-tabbing,inserting cds,etc
 *
 * 139   4/29/99 4:36p Kevin
 * fixed a problem with low quality sounds & the optimizd software mixer
 *
 * 138   4/29/99 3:01p Samir
 * added code for direct sound mixers only (and function for Aureal
 * really) that will use direct sound looping for simple loops.
 *
 * 137   4/27/99 7:08p Kevin
 * optimized software mixer!
 *
 * 136   4/27/99 6:21p Samir
 * if callback gets a NULL guid, just return, assume that the sound device
 * is the default?
 *
 * 135   4/27/99 5:19p Samir
 * mprintf change.
 *
 * 134   4/27/99 2:10p Samir
 * added code to set the desired sound card given the descriptive name of
 * a sound card.
 *
 * 133   4/25/99 9:52p Samir
 * fixed looping sequencing bug with thread for direct sound mixers.
 * SSF_PLAY_LOOPING must be set before any buffer filling occurs,
 * otherwise bad things happen with very small loops....
 *
 * 132   4/23/99 7:51p Samir
 * looping fixes for directsound
 *
 * 131   4/22/99 10:33p Samir
 * modifications so that DirectSound mixers use one thread for all looping
 * and streaming sounds.   It worked without crashing for about twenty
 * minutes of playing from level 1 to level 2 of D3.  We'll see.
 *
 * 130   4/18/99 5:37p Kevin
 * Very simple optimization for the software mixer
 *
 * 129   4/13/99 4:15p Jason
 * took out register keyword because it was hurting performance
 *
 * 128   4/13/99 4:09p Samir
 * more priority stuff.
 *
 *
 * 126   4/12/99 7:14p Samir
 * prioritization code added.
 *
 * 125   4/10/99 5:08p Samir
 * took out obsolete data from play_information structure that should save
 * around 70 bytes per instance.
 *
 * 124   4/09/99 5:00p Kevin
 * put the memset in -- memset should be doing at least 32 bit copies,
 * which is FAR better than a for loop.
 *
 * 123   4/09/99 12:03p Samir
 * took out windows.h again, this time made HWND a void pointer, and
 * checked under both editor and main projects.
 *
 * 122   4/06/99 8:29p Samir
 * added error check system.
 *
 * 121   3/29/99 11:00a Samir
 * added system to support different 3d sound options.
 *
 * 120   3/17/99 4:20p Samir
 * added functions to pause and resume individual sounds.
 *
 * 119   3/04/99 1:23p Kevin
 * Fixed Poping sound!!!
 *
 * 118   3/03/99 6:53p Matt
 * Fixed compile warning
 *
 * 117   3/03/99 3:12p Chris
 * Fixed volume problems
 *
 * 116   3/01/99 8:12p Samir
 * pause sounds when switching sound quality!
 *
 * 115   2/25/99 4:50p Kevin
 * Semi-hack to fix the problem with music looping and stuttering in DS
 *
 * 114   2/24/99 3:15p Kevin
 * OEM menu changes, and bug fixes for the save/load system
 *
 * 113   2/22/99 6:28p Kevin
 * Fixed a bug that was introduced (?) when the thread problem was fixed.
 *
 * 112   2/20/99 1:14a Kevin
 * Fixed another bug
 *
 * 111   2/19/99 10:45p Kevin
 * Fixed bug I just introduced...
 *
 * 110   2/19/99 5:21p Kevin
 * Fixed some connection DLLs and a Direct Sound bug with threads.
 *
 * 109   2/11/99 3:30p Doug
 * error checking in PlaySoundBuffer.
 *
 * 108   2/04/99 9:46a Kevin
 * OEM version changes
 *
 * 107   1/14/99 6:10p Samir
 * added DirectSound buffer duplication code.
 *
 * 106   1/11/99 5:51p Samir
 * reverb on the buffer level.
 *
 * 105   1/08/99 6:31p Samir
 * added reverb
 *
 * 104   1/08/99 11:36a Samir
 * implemented basic Aureal 2.0 support.
 *
 * 103   1/08/99 10:32a Chris
 *
 * 102   12/23/98 11:49a Samir
 * reorganized code so it works with different APIs.
 *
 * 101   12/11/98 5:21p Samir
 * (chris) fixed problem with software streaming audio.
 *
 * 100   12/10/98 3:16p Chris
 * added mprintfs for later use
 *
 * 99    12/10/98 2:18p Chris
 * Added more asserts to the streaming code
 *
 * 98    11/13/98 4:55p Nate
 * don't do dedicated server check in lowlevel.
 *
 * 97    11/13/98 12:17p Chris
 *
 * 96    11/12/98 12:15p Chris
 * Fixed a bug with streaming mixers
 *
 * 95    10/30/98 1:20p Chris
 * Fixed a m_unique_id bug where it was being used before it was being
 * assigned
 *
 *
 * $NoKeywords: $
 */

#include "ds3dlib_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include "cfile.h"
#include "pserror.h"
#include "mono.h"
#include "soundload.h"
#include "mem.h"
#include "winapp.h"
#include "auddev.h"
#include "Macros.h"
#include "ddio.h"

// Hacked window handle -- chrishack
static oeApplication* SoundApp = nullptr;
static void* GameWindowHandle = nullptr;
#define MIN_SOUND_MIX_VOLUME 0.0
#define MAX_WRITE_AHEAD .04 // Seconds to write ahead of the play position (in seconds)

// write position

#define IS_3D_MIXER(_type) ((_type) >= SOUND_MIXER_DS3D_16 && (_type) != SOUND_MIXER_NONE)

win_llsSystem *ll_sound_ptr;
emulated_listener *g_emulated_listener = NULL; // silly hack (Samir)
int16_t Global_DS_alloced_sounds = 0;

int *Fast_mixer = NULL;
int Fast_mixer_len = 0;

#define VOLUME_FIX_BITS 1024

// Streaming primary buffer information
DSSTREAM m_sb_info;
char m_sound_device_name[256] = ""; // set by set sound card

// Loads a sound buffer with data
HRESULT LoadSoundData(LPDIRECTSOUNDBUFFER lp_dsb, char *sound_data_ptr, DWORD total_bytes);

///////////////////////////////////////////////////////////////////////////////

static t3dEnvironmentValues Env3dValues;
static t3dEnvironmentToggles Env3dToggles;

#define ENV3DTOG_DOPPLER true
#define ENV3DTOG_GEOMETRY true

#define ENV3DVAL_DOPPLER_DEFAULT 0.5f
#define ENV3DVAL_ROLLOFF_DEFAULT 0.5f

///////////////////////////////////////////////////////////////////////////////

win_llsSystem::win_llsSystem(void) : llsSystem() {
  m_lp_ds = NULL;
  m_f_sound_lib_init = 0;
  m_hwnd_main = NULL;
  m_mixer_type = -1;
  m_sound_quality = SQT_NORMAL;
  m_cache_stress_timer = 0.0f;
  ll_sound_ptr = NULL;
  m_timer_last_frametime = -1;
  memset(&Env3dValues, 0, sizeof(Env3dValues));
  memset(&Env3dToggles, 0, sizeof(Env3dToggles));
  SetError(SSL_OK);
}

win_llsSystem::~win_llsSystem(void) {
  DestroySoundLib();
  SetSoundCard(NULL);
}

inline void opti_8m_mix(uint8_t *cur_sample_8bit, const int num_write, int &samples_played, int *mixer_buffer16,
                        const float l_volume, const float r_volume) {
  int i;
  int *mb = mixer_buffer16;

  const int fix_rvol = r_volume * VOLUME_FIX_BITS;
  const int fix_lvol = l_volume * VOLUME_FIX_BITS;

  for (i = 0; i < (num_write << 1); i += 2) {
    int sample;
    int l_sample;
    int r_sample;

    sample = (((*cur_sample_8bit)) - 128) << 8;
    cur_sample_8bit++;

    l_sample = *mb + (sample * fix_lvol);
    r_sample = *(mb + 1) + (sample * fix_rvol);

    *mb = l_sample;
    mb++;
    *mb = r_sample;
    mb++;
  }
  samples_played += (i / 2);
}

inline void opti_8s_mix(uint8_t *cur_sample_8bit, const int num_write, int &samples_played, int *mixer_buffer16,
                        const float l_volume, const float r_volume) {
  int i;
  int *mb = mixer_buffer16;

  const int fix_rvol = r_volume * VOLUME_FIX_BITS;
  const int fix_lvol = l_volume * VOLUME_FIX_BITS;

  for (i = 0; i < (num_write << 1); i += 2) {
    int lsample;
    int rsample;
    int l_sample;
    int r_sample;

    lsample = (((*cur_sample_8bit)) - 128) << 8;
    cur_sample_8bit++;
    rsample = (((*cur_sample_8bit)) - 128) << 8;
    cur_sample_8bit++;

    l_sample = *mb + (lsample * fix_lvol);
    r_sample = *(mb + 1) + (rsample * fix_rvol);

    *mb = l_sample;
    mb++;
    *mb = r_sample;
    mb++;
  }
  samples_played += (i / 2);
}

inline void opti_16m_mix(int16_t *cur_sample_16bit, const int num_write, int &samples_played, int *mixer_buffer16,
                         const float l_volume, const float r_volume) {
  int i;
  int *mb = mixer_buffer16;

  const int fix_rvol = r_volume * VOLUME_FIX_BITS;
  const int fix_lvol = l_volume * VOLUME_FIX_BITS;

  for (i = 0; i < (num_write << 1); i += 2) {
    int sample;
    int l_sample;
    int r_sample;

    sample = *cur_sample_16bit;
    cur_sample_16bit++;

    l_sample = *mb + (sample * fix_lvol);
    r_sample = *(mb + 1) + (sample * fix_rvol);

    *mb = l_sample;
    mb++;
    *mb = r_sample;
    mb++;
  }
  samples_played += (i / 2);
}

inline void opti_16s_mix(int16_t *cur_sample_16bit, const int num_write, int &samples_played, int *mixer_buffer16,
                         const float l_volume, const float r_volume) {
  int i;
  int *mb = mixer_buffer16;

  const int fix_rvol = r_volume * VOLUME_FIX_BITS;
  const int fix_lvol = l_volume * VOLUME_FIX_BITS;

  for (i = 0; i < (num_write << 1); i += 2) {
    int lsample;
    int rsample;
    int l_sample;
    int r_sample;

    lsample = *cur_sample_16bit;
    cur_sample_16bit++;
    rsample = *cur_sample_16bit;
    cur_sample_16bit++;

    l_sample = *mb + (lsample * fix_lvol);
    r_sample = *(mb + 1) + (rsample * fix_rvol);

    *mb = l_sample;
    mb++;
    *mb = r_sample;
    mb++;
  }
  samples_played += (i / 2);
}

////////////////////////////////////////////////////////////////////////////////////

#define MAX_DS_PAN 1000.0f

int GamePanToDsPan(float pan) {
  int ds_pan;
  ds_pan = (int)(pan * MAX_DS_PAN);

  if (ds_pan > MAX_DS_PAN)
    ds_pan = MAX_DS_PAN;
  if (ds_pan < -MAX_DS_PAN)
    ds_pan = -MAX_DS_PAN;

  // mprintf(0, "P %f %d\n", pan, ds_pan);
  return ds_pan;
}

int GameVolumeToDsAttenuation(float volume) {
  float fvol;

  if (volume <= 0.0f) {
    fvol = 2000.0f;
  } else {
    fvol = logf(volume) / logf(10.0f);
    fvol *= 2000.0;
  }

  if (volume <= 0.01f) {
    fvol = DSBVOLUME_MIN;
  }

  // mprintf(0, "V %f %f\n", volume, fvol);
  return (int)fvol;
}

////////////////////////////////////////////////////////////////////////////////////

inline char *get_sound_info(sound_buffer_info *sb, int *length, bool *f16bit) {
  if (sb->m_sound_index < 0) {
    if (sb->s) {
      *f16bit = sb->s->f_sample_16bit;
    }
    return NULL;
  }
  if (SoundFiles[Sounds[sb->m_sound_index].sample_index].sample_8bit) {
    *length = SoundFiles[Sounds[sb->m_sound_index].sample_index].np_sample_length;
    *f16bit = false;
    return (char *)SoundFiles[Sounds[sb->m_sound_index].sample_index].sample_8bit;
  } else {
    ASSERT(SoundFiles[Sounds[sb->m_sound_index].sample_index].sample_16bit);
    *f16bit = true;
    *length = SoundFiles[Sounds[sb->m_sound_index].sample_index].np_sample_length * 2;
    return (char *)SoundFiles[Sounds[sb->m_sound_index].sample_index].sample_16bit;
  }
}

//////////////////////////////////////////////////////////////////////////////////
#define SB_STATUS_PLAYING 0x1
#define SB_STATUS_INVALID 0x2

inline int sb_get_status(sound_buffer_info *sb) {
  int retflags = 0;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    LPDIRECTSOUNDBUFFER sound_ptr = sb->m_sound_buffer;
    unsigned long status;

    if (sound_ptr) {
      sound_ptr->GetStatus(&status);
      if (status & DSBSTATUS_PLAYING)
        retflags |= SB_STATUS_PLAYING;
    } else {
      retflags |= SB_STATUS_INVALID;
    }
  }

  return retflags;
}

inline void sb_adjust_properties_3d(sound_buffer_info *sb, float f_volume, pos_state *pos, float reverb) {
  if (!ll_sound_ptr->m_in_sound_frame)
    ll_sound_ptr->m_pending_actions = true;

  sb->m_volume = f_volume;

  if (IS_3D_MIXER(sb->m_mixer_type)) {
    LPDIRECTSOUNDBUFFER lp_dsb = sb->m_sound_buffer;
    LPDIRECTSOUND3DBUFFER lpDSB3D = sb->m_sound_buffer_3d;

    lp_dsb->SetVolume(GameVolumeToDsAttenuation(f_volume));

    ASSERT(lpDSB3D != NULL);

    if (sb->m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
      lpDSB3D->SetMinDistance(30.0f, DS3D_IMMEDIATE);
    } else {
      lpDSB3D->SetMinDistance(Sounds[sb->m_sound_index].min_distance, DS3D_IMMEDIATE);
    }
    lpDSB3D->SetMaxDistance(Sounds[sb->m_sound_index].max_distance, DS3D_IMMEDIATE);
    lpDSB3D->SetConeOrientation(pos->orient->fvec.x, pos->orient->fvec.y, pos->orient->fvec.z, DS3D_IMMEDIATE);
    lpDSB3D->SetPosition(pos->position->x, pos->position->y, pos->position->z, DS3D_IMMEDIATE);
    lpDSB3D->SetVelocity(pos->velocity->x, pos->velocity->y, pos->velocity->z, DS3D_IMMEDIATE);

    //	if (sb->m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
    //		EAX_SetBufferReverbMix(lpDSB3D, reverb);
    //	}
  } else {
    mprintf(0, "m_mixer_type = %d\n", sb->m_mixer_type);
    Int3();
  }
}

inline void sb_adjust_properties_2d(sound_buffer_info *sb, float f_volume, float f_pan, uint16_t frequency) {
  if (!ll_sound_ptr->m_in_sound_frame)
    ll_sound_ptr->m_pending_actions = true;

  sb->m_volume = f_volume;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    LPDIRECTSOUNDBUFFER lpdsb;

    ASSERT(f_pan >= -1.0f && f_pan <= 1.0f);
    ASSERT(f_volume >= 0.0f && f_volume <= 1.0f);

    lpdsb = sb->m_sound_buffer;
    if (lpdsb == NULL)
      return;

    //	mprintf(0, "Sound UID %d is now at %d volume,%d pan\n", sound_uid, volume, pan);

    lpdsb->SetVolume(GameVolumeToDsAttenuation(f_volume));
    lpdsb->SetPan(GamePanToDsPan(f_pan)); // chrishack pan is off
    lpdsb->SetFrequency(frequency);
  }
}

// functions for different APIs
int sb_get_current_position(sound_buffer_info *sb, uint32_t *writep) {
  DWORD playp, wp;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    if (sb->m_sound_buffer && sb->m_sound_buffer->GetCurrentPosition(&playp, &wp) == DS_OK) {
      *writep = (uint32_t)wp;
    } else {
      playp = (DWORD)(-1);
      *writep = (uint32_t)(-1);
    }
  }

  return (uint32_t)playp;
}

inline void sb_set_current_position(sound_buffer_info *sb, uint32_t pos) {
  if (!ll_sound_ptr->m_in_sound_frame)
    ll_sound_ptr->m_pending_actions = true;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    sb->m_sound_buffer->SetCurrentPosition((DWORD)pos);
  }
}

void sb_free_buffer(sound_buffer_info *sb) {
  if (!ll_sound_ptr->m_in_sound_frame)
    ll_sound_ptr->m_pending_actions = true;
  if (!sb->m_sound_buffer)
    return;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    if (sb->m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
      EAX_FreeSource(sb->m_lpksps);
    }

    if (sb->m_sound_buffer) {
      sb->m_sound_buffer->Release();
      sb->m_sound_buffer = NULL;
    }
    if (sb->m_sound_buffer_3d) {
      sb->m_sound_buffer_3d->Release();
      sb->m_sound_buffer_3d = NULL;
    }
  }
}

void sb_stop_buffer(sound_buffer_info *sb) {
  if (!ll_sound_ptr->m_in_sound_frame)
    ll_sound_ptr->m_pending_actions = true;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    sb->m_sound_buffer->Stop();
  }
}

bool sb_lock_buffer(sound_buffer_info *sb, uint32_t dwWriteCursor, uint32_t dwWriteBytes, void **lplpvAudioPtr1,
                    uint32_t *lpdwAudioBytes1, void **lplpvAudioPtr2, uint32_t *lpdwAudioBytes2) {
  DWORD len1, len2;

  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
  TryLockAgainLabel:
    switch (sb->m_sound_buffer->Lock(dwWriteCursor, dwWriteBytes, lplpvAudioPtr1, &len1, lplpvAudioPtr2, &len2, 0)) {
    case DS_OK:
      *lpdwAudioBytes1 = len1;
      *lpdwAudioBytes2 = len2;
      return true;

    case DSERR_BUFFERLOST:
      if (sb->m_sound_buffer->Restore() == DS_OK)
        goto TryLockAgainLabel;
    }

    return false;
  }

  return false;
}

bool sb_unlock_buffer(sound_buffer_info *sb, void *ptr1, uint32_t len1, void *ptr2, uint32_t len2) {
  if (sb->m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    sb->m_sound_buffer->Unlock(ptr1, len1, ptr2, len2);
    return true;
  }

  return false;
}

bool sb_load_buffer(sound_buffer_info *sb, void *sample_data, int length) {
  if (!ll_sound_ptr->m_in_sound_frame)
    ll_sound_ptr->m_pending_actions = true;

  if (LoadSoundData(sb->m_sound_buffer, (char *)sample_data, length) != DS_OK) {
      Int3();
      sb->m_status = SSF_UNUSED;
      return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////

// The actual mixer code that sum's the sounds on each channel and does all the actual
// mixing and effects (writes data to the locked primary buffer)
void StreamMixer(char *ptr, int len) {
  int i;
  int16_t *mixer_buffer16 = (int16_t *)ptr;
  int current_slot = 0;
  bool f_loop;
  bool f_mono;

  const int buff_len = len / ll_sound_ptr->m_primary_alignment;

  // this code will assure that this function will not be called when  sound system is in error mode.
  if (ll_sound_ptr->m_lib_error_code != SSL_OK) {
    return;
  }

  ASSERT(len <= m_sb_info.BufferSize);
  ASSERT(ptr && len >= 0);

  ASSERT((len % ll_sound_ptr->m_primary_alignment) == 0);

  // memset((char *)ptr, 0, len);

  // This memset is hopefully temporary
  memset(Fast_mixer, 0, Fast_mixer_len * sizeof(int));
  int *fast_mix_ptr = Fast_mixer;

  // Mix the sound slots
  while (current_slot < ll_sound_ptr->m_sound_mixer.m_max_sounds_played) {
    sound_buffer_info *cur_buf = &ll_sound_ptr->m_sound_mixer.m_sound_cache[current_slot];
    int num_samples = buff_len;
    // mixer_buffer16 = (int16_t *) ptr;
    fast_mix_ptr = Fast_mixer;
    f_mono = true;

    // Find slots with sounds in them
    if ((cur_buf->m_status != SSF_UNUSED) && !(cur_buf->m_status & SSF_PAUSED)) {
      float l_volume = cur_buf->play_info->left_volume;
      float r_volume = cur_buf->play_info->right_volume;
      int skip_interval = cur_buf->play_info->sample_skip_interval;
      int samples_played = cur_buf->play_info->m_samples_played;
      int16_t *sample_16bit;
      uint8_t *sample_8bit;
      int np_sample_length;
      int sample_length;
      int loop_start;
      int loop_end;

      if (cur_buf->m_status & SSF_PLAY_STREAMING) {
        switch (cur_buf->play_info->m_stream_format) {
        case SIF_STREAMING_16_M:
          sample_16bit = (int16_t *)cur_buf->play_info->m_stream_data;
          sample_8bit = NULL;
          np_sample_length = sample_length = cur_buf->play_info->m_stream_size / 2;
          break;
        case SIF_STREAMING_8_M:
          sample_16bit = NULL;
          sample_8bit = (uint8_t *)cur_buf->play_info->m_stream_data;
          np_sample_length = sample_length = cur_buf->play_info->m_stream_size;
          break;
        case SIF_STREAMING_16_S:
          sample_16bit = (int16_t *)cur_buf->play_info->m_stream_data;
          sample_8bit = NULL;
          np_sample_length = sample_length = cur_buf->play_info->m_stream_size / 4;
          f_mono = false;
          break;
        case SIF_STREAMING_8_S:
          sample_16bit = NULL;
          sample_8bit = (uint8_t *)cur_buf->play_info->m_stream_data;
          np_sample_length = sample_length = cur_buf->play_info->m_stream_size / 2;
          f_mono = false;
          break;
        default:
          Int3();
          break;
        }
        loop_start = 0;
        loop_end = np_sample_length - 1;
      } else {
        int sound_index = cur_buf->m_sound_index;
        int sample_index = Sounds[sound_index].sample_index;
        sound_file_info *snd_file = &SoundFiles[sample_index];
        sample_16bit = snd_file->sample_16bit;
        sample_8bit = snd_file->sample_8bit;
        np_sample_length = snd_file->np_sample_length;
        sample_length = snd_file->sample_length;
        loop_start = Sounds[sound_index].loop_start;
        loop_end = Sounds[sound_index].loop_end;
        if (!sample_16bit && !sample_8bit) {
          mprintf(0, "sound file %s didn't have data for samples.\n", snd_file->name);
        }
      }

      // cleanly continue if this happens, and inform a logfile, if it does. error handling
      //	ASSERT(sample_16bit || sample_8bit);
      if (!sample_16bit && !sample_8bit) {
        sound_file_info *snd_file = &SoundFiles[Sounds[cur_buf->m_sound_index].sample_index];
        ll_sound_ptr->SetError(SSL_ERROR_SAMPLE_NODATA);
        ll_sound_ptr->ErrorText("ASSERT(sample_16bit || sample_8bit)\nNo data found for sound file: %s",
                                snd_file->name);
        cur_buf->m_status = SSF_UNUSED;
        goto error_bail;
      }

      ASSERT(np_sample_length <= sample_length);
      ASSERT(samples_played >= 0 || samples_played <= sample_length);

      int num_write;

    error_trap:

      // We have not looped -- yet
      f_loop = false;

      // Verify the volume levels are o.k.
      ASSERT(l_volume >= 0.0 && l_volume <= 1.0);
      ASSERT(r_volume >= 0.0 && r_volume <= 1.0);

    looping: // Will go to this label to do the next iteration of a looping sample

      if (cur_buf->m_status &
          (SSF_PLAY_LOOPING | SSF_PLAY_STREAMING)) // Looping sample's process is broken up into linear pieces
      {
        if (f_loop) {
          ASSERT(num_write >= 0);

          num_samples -= num_write;
          ASSERT(num_samples > 0);

          fast_mix_ptr += (num_write * 2);
          // mixer_buffer16 += num_write << 1;  // update to the new start position
          // (2x because of left and right channels)

          samples_played = loop_start;
        }

        if (cur_buf->m_status & SSF_PLAY_LOOPING) // Looping sample's process is broken up into linear pieces
        {
          ASSERT(loop_end < sample_length);
          if (loop_end < samples_played) {
            // CHRISHACK -- Fuck milestone.  Fix later.  Code below is a major hack (but it works).  :)

            if (loop_end != loop_start) {
              while (loop_end < samples_played) {
                // Int3();
                samples_played -= loop_end - loop_start;
              }

              ASSERT(samples_played >= 0);
            } else {
              cur_buf->m_status &= ~SSF_PLAY_LOOPING;
              cur_buf->m_status |= SSF_PLAY_NORMAL;
            }

            goto error_trap;
          }
        }
        // The number of samples to write to the primary buffer
        num_write = ((num_samples) < (loop_end - samples_played + 1)) ? (num_samples) : (loop_end - samples_played + 1);
        ASSERT(num_write >= 0 && num_write <= num_samples);

        if (num_write < num_samples)
          f_loop = true;
        else
          f_loop = false;

        if (num_write <= 0) {
          num_write = 0;
          mprintf(0, "d");
          goto stream_done;
        }
      } else {
        // The number of samples to write to the primary buffer
        num_write =
            ((num_samples) < (np_sample_length - samples_played)) ? (num_samples) : (np_sample_length - samples_played);
        if (!(num_write > 0 && num_write <= num_samples)) {
          num_write = 0;
          goto done;
        }

        // Optimization for silent sounds
        if (l_volume <= MIN_SOUND_MIX_VOLUME && r_volume <= MIN_SOUND_MIX_VOLUME) {
          cur_buf->play_info->m_samples_played += num_write;
          goto done;
        }
      }

      if (!(num_write > 0 && num_write <= num_samples)) // this was an assert
      {
        num_write = 0;
        mprintf(0, "D");
        goto done;
      }

      // Mix at 16 bits per sample
      if (skip_interval == 0) {
        int16_t *cur_sample_16bit = sample_16bit;
        uint8_t *cur_sample_8bit = sample_8bit;

        if (f_mono) {
          if (sample_8bit) {
            cur_sample_8bit += samples_played;
            opti_8m_mix(cur_sample_8bit, num_write, samples_played, fast_mix_ptr, l_volume, r_volume);
          } else {
            cur_sample_16bit += samples_played;
            opti_16m_mix(cur_sample_16bit, num_write, samples_played, fast_mix_ptr, l_volume, r_volume);
          }
        } else {
          if (sample_8bit) {
            cur_sample_8bit += (samples_played << 1);
            opti_8s_mix(cur_sample_8bit, num_write, samples_played, fast_mix_ptr, l_volume, r_volume);
          } else {
            cur_sample_16bit += (samples_played << 1);
            opti_16s_mix(cur_sample_16bit, num_write, samples_played, fast_mix_ptr, l_volume, r_volume);
          }
        }
      } else
      // Account for lower-sampling rate
      {
        if (skip_interval == 1) {
          const int fix_rvol = r_volume * VOLUME_FIX_BITS;
          const int fix_lvol = l_volume * VOLUME_FIX_BITS;

          for (i = 0; i < (num_write << 1); i += 2) {
            int sample;

            if (sample_16bit) {
              if (samples_played & 0x0001) {
                sample = ((int)sample_16bit[samples_played ^ 0x0001] + (int)sample_16bit[samples_played + 1]) >> 1;
              } else
                sample = sample_16bit[samples_played];
            } else {
              if (samples_played & 0x0001) {
                // Notes: (<<7) is from a (<<8) - (>>1)
                // Notes: (-256) is from (-128) + (-128)
                sample = ((int)sample_8bit[samples_played ^ 0x0001] + (int)sample_8bit[samples_played + 1] - 256) << 7;
              } else
                sample = (((int)sample_8bit[samples_played]) - (int)128) << 8;
            }

            samples_played++;

            ASSERT(i >= 0 && (i + 1 < num_samples * 2));

            int l_sample = fast_mix_ptr[i] + (sample * fix_lvol);
            int r_sample = fast_mix_ptr[i + 1] + (sample * fix_rvol);

            fast_mix_ptr[i] = l_sample;
            fast_mix_ptr[i + 1] = r_sample;
          }
        } else {
          const int fix_rvol = r_volume * VOLUME_FIX_BITS;
          const int fix_lvol = l_volume * VOLUME_FIX_BITS;
          for (i = 0; i < (num_write << 1); i += 2) {
            int sample;
            const int mod_pos = samples_played % 4;

            if (sample_16bit) {
              switch (mod_pos) {
              case 0:
                sample = sample_16bit[samples_played];
                break;
              case 1:
                sample = (sample_16bit[samples_played - 1] * 3 + sample_16bit[samples_played + 3]) >> 2;
                break;
              case 2:
                sample = (sample_16bit[samples_played - 2] + sample_16bit[samples_played + 2]) >> 1;
                break;
              case 3:
                sample = (sample_16bit[samples_played - 3] + sample_16bit[samples_played + 1] * 3) >> 2;
                break;
              }
            } else {
              switch (mod_pos) {
              case 0:
                sample = ((((int)sample_8bit[samples_played]) - 128) << 8);
                break;
              case 1:
                sample = (((((int)sample_8bit[samples_played - 1]) - 128) << 8) * 3 +
                          ((((int)sample_8bit[samples_played + 3]) - 128) << 8)) >>
                         2;
                break;
              case 2:
                sample = (((((int)sample_8bit[samples_played - 2]) - 128) << 8) +
                          ((((int)sample_8bit[samples_played + 2]) - 128) << 8)) >>
                         1;
                break;
              case 3:
                sample = (((((int)sample_8bit[samples_played - 3]) - 128) << 8) +
                          ((((int)sample_8bit[samples_played + 1]) - 128) << 8) * 3) >>
                         2;
                break;
              }
            }

            samples_played++;

            ASSERT(i >= 0 && (i + 1 < num_samples * 2));

            int l_sample = fast_mix_ptr[i] + (sample * fix_lvol);
            int r_sample = fast_mix_ptr[i + 1] + (sample * fix_rvol);

            fast_mix_ptr[i] = l_sample;
            fast_mix_ptr[i + 1] = r_sample;
          }
        }
      }

    stream_done:

      cur_buf->play_info->m_samples_played = samples_played;

      if (cur_buf->m_status & SSF_PLAY_STREAMING) {
        if (f_loop) {
          if (cur_buf->play_info->m_stream_cback && cur_buf->play_info->m_stream_data) {
            cur_buf->play_info->m_stream_data = (*cur_buf->play_info->m_stream_cback)(
                cur_buf->play_info->user_data, cur_buf->play_info->m_stream_handle, &cur_buf->play_info->m_stream_size);
//            cur_buf->s->current_position = (char*)cur_buf->play_info->m_stream_data;
//            mprintf(0, "%x %d\n", cur_buf->play_info->m_stream_data, cur_buf->play_info->m_stream_size));
            ASSERT(!(cur_buf->play_info->m_stream_data && cur_buf->play_info->m_stream_size <= 0));
/*
            mprintf(0, "Data %X, length %d\n",
                    cur_buf->play_info->m_stream_data,
                    cur_buf->play_info->m_stream_size);
*/

            if (cur_buf->play_info->m_stream_data) {
              switch (cur_buf->play_info->m_stream_format) {
              case SIF_STREAMING_16_M:
                sample_16bit = (int16_t *)cur_buf->play_info->m_stream_data;
                loop_end = sample_length = np_sample_length = cur_buf->play_info->m_stream_size / 2;
                break;
              case SIF_STREAMING_8_M:
                sample_8bit = (uint8_t *)cur_buf->play_info->m_stream_data;
                loop_end = sample_length = np_sample_length = cur_buf->play_info->m_stream_size;
                break;
              case SIF_STREAMING_16_S:
                sample_16bit = (int16_t *)cur_buf->play_info->m_stream_data;
                loop_end = sample_length = np_sample_length = cur_buf->play_info->m_stream_size / 4;
                break;
              case SIF_STREAMING_8_S:
                sample_8bit = (uint8_t *)cur_buf->play_info->m_stream_data;
                loop_end = sample_length = np_sample_length = cur_buf->play_info->m_stream_size / 2;
                break;
              default:
                Int3();
                break;
              }
              loop_end -= 1;
            } else {
              mprintf(0, "SE: Data is NULL\n");
              cur_buf->m_status &= ~SSF_PLAY_STREAMING;
              f_loop = false;
            }
          } else {
            mprintf(0, "SE: Callback/data is NULL\n");
            cur_buf->m_status &= ~SSF_PLAY_STREAMING;
            f_loop = false;
          }
        }
      }

      if (f_loop)
        goto looping;

    done:

      if (cur_buf->play_info->m_samples_played >= (np_sample_length) &&
          !(cur_buf->m_status & (SSF_PLAY_LOOPING | SSF_PLAY_STREAMING))) {
        ll_sound_ptr->StopSound(cur_buf->m_unique_id);
      }
    }

  error_bail:
    current_slot++;
  }

  for (int a = 0; a < (buff_len * 2); a++) {
    Fast_mixer[a] = Fast_mixer[a] / VOLUME_FIX_BITS;

    if (Fast_mixer[a] > 32767)
      Fast_mixer[a] = 32767;
    if (Fast_mixer[a] < -32767)
      Fast_mixer[a] = -32767;

    mixer_buffer16[a] = Fast_mixer[a];

    Fast_mixer[a + 1] = Fast_mixer[a + 1] / VOLUME_FIX_BITS;

    if (Fast_mixer[a + 1] > 32767)
      Fast_mixer[a + 1] = 32767;
    if (Fast_mixer[a + 1] < -32767)
      Fast_mixer[a + 1] = -32767;

    mixer_buffer16[a + 1] = Fast_mixer[a + 1];

    a++;
  }
  // mprintf(0," -%d- ",a);
}

// Locks the primary buffer and fills in the new data
void StreamFill(int start_byte, int num_bytes) {
  char *ptr1;
  char *ptr2;
  int len1, len2;

  if ((num_bytes % ll_sound_ptr->m_primary_alignment) != 0) {
    ll_sound_ptr->SetError(SSL_ERROR_STREAMMIXER);
    ll_sound_ptr->ErrorText("ASSERT((len % ll_sound_ptr->m_primary_alignment) == 0)\nLen:%d PrA:%d", num_bytes,
                            ll_sound_ptr->m_primary_alignment);
    return;
  }
  ASSERT((num_bytes % ll_sound_ptr->m_primary_alignment) == 0);
  ASSERT((start_byte % ll_sound_ptr->m_primary_alignment) == 0);

  start_byte = (start_byte % m_sb_info.BufferSize);

TryLockAgainLabel:

  switch (m_sb_info.m_lp_looping_buffer->Lock(start_byte, num_bytes, (void **)&ptr1, (DWORD *)&len1, (void **)&ptr2,
                                              (DWORD *)&len2, 0)) {
    ASSERT((len1 % ll_sound_ptr->m_primary_alignment) == 0);
    ASSERT((len2 % ll_sound_ptr->m_primary_alignment) == 0);

  // The pointers are to the lock areas of the primary buffer.  There are two because locked region
  // might be a discontinuous chunk (wrapped around the end of the buffer i.e. 'LLLLBBBBBBLLLLL'
  // L is for Locked and B is unlocked buffer.
  case DS_OK:
    StreamMixer(ptr1, len1);
    if (ptr2)
      StreamMixer(ptr2, len2);

    m_sb_info.m_lp_looping_buffer->Unlock(ptr1, len1, ptr2, len2);

    m_sb_info.NextWritePos = (start_byte + num_bytes) % m_sb_info.BufferSize;
    break;

  case DSERR_BUFFERLOST:
    if (m_sb_info.m_lp_primary_buffer->Restore() == DS_OK && m_sb_info.m_lp_looping_buffer->Restore() == DS_OK)
      goto TryLockAgainLabel;
    break;
  }
}

// A peroidic mixer that uses the primary buffer as a stream buffer
void __cdecl StreamTimer(void *user_ptr) {
  int playp, writep;
  int try_count = 0;
  DSSTREAM *sb_info = (DSSTREAM *)user_ptr;
  DWORD result;

  m_sb_info.m_lp_primary_buffer->Restore();
  m_sb_info.m_lp_primary_buffer->Play(0, 0, DSBPLAY_LOOPING);

  while (!sb_info->thread_request_kill) {
    try_count = 0;

  TryAgain:
    try_count++;

    //		hresult = m_sb_info.m_lp_primary_buffer->GetStatus(&stat_result);
    //
    //		if(hresult != DS_OK || !(stat_result & DSBSTATUS_LOOPING))
    //		{
    //			m_sb_info.m_lp_primary_buffer->Restore();
    m_sb_info.m_lp_primary_buffer->Restore();
    m_sb_info.m_lp_primary_buffer->Play(0, 0, DSBPLAY_LOOPING);
    //		}

    result = sb_info->m_lp_looping_buffer->GetCurrentPosition((DWORD *)&playp, (DWORD *)&writep);

    // mprintf(0, "(%d,%d)\n", playp, writep);

    // If primary buffer was stopped from playing
    if (writep == playp) {
      sb_info->NextWritePos = -1;

      if ((try_count == 1) &&
          (m_sb_info.m_lp_primary_buffer->Restore() == DS_OK && m_sb_info.m_lp_looping_buffer->Restore() == DS_OK)) {
        if ((try_count == 1) && (m_sb_info.m_lp_looping_buffer->Play(0, 0, DSBPLAY_LOOPING) == DS_OK)) {
          goto TryAgain;
        }
      }

      goto done;
    }

    // Insert mixer code
    {
      int num_write_bytes;

      if (sb_info->NextWritePos < 0)
        sb_info->NextWritePos = writep;

      // Debugging code (not sure what would happen if we hit these without an Int3()) -- Skipping noise
      if (sb_info->LastPlayPos < sb_info->NextWritePos) {

        if (playp >= sb_info->NextWritePos || playp < sb_info->LastPlayPos) {
          if (!sb_info->m_f_secondary_looping)
            goto done;
          playp = sb_info->NextWritePos - 4;
          num_write_bytes = 4 * (int)(22050 * DSPB_TICK_INTERVAL);
        } else {
          // Determine how much we can write out.
          num_write_bytes = (sb_info->MaxWriteBytes + playp) - sb_info->NextWritePos;
        }
      } else {
        if (playp >= sb_info->NextWritePos && playp < sb_info->LastPlayPos) {
          if (!sb_info->m_f_secondary_looping)
            goto done;

          playp = sb_info->NextWritePos - 4;
          num_write_bytes = 4 * (int)(22050 * DSPB_TICK_INTERVAL);
        } else {
          // Determine how much we can write out.
          if (playp < sb_info->NextWritePos)
            num_write_bytes = (sb_info->MaxWriteBytes + playp) - sb_info->NextWritePos;
          else
            num_write_bytes = sb_info->MaxWriteBytes - (sb_info->NextWritePos + (sb_info->BufferSize - playp));
        }
      }

      num_write_bytes &= (0xFFFFFFFF & (~(ll_sound_ptr->m_primary_alignment)));

      if (num_write_bytes > 0) {
        // ASSERT(num_write_bytes < sb_info->BufferSize);
        if (num_write_bytes >= sb_info->BufferSize) {
          num_write_bytes = sb_info->BufferSize / 2;
        }

        StreamFill(sb_info->NextWritePos, num_write_bytes);
      }
    }

    sb_info->LastPlayPos = playp;

  done:
    Sleep(DSPB_TICK_MILLISECONDS);
  }

  sb_info->thread_alive = false;
}

// Begins the whole streaming process
bool win_llsSystem::StartStreaming(void) {
  DSBCAPS dsbcaps;

  dsbcaps.dwSize = sizeof(DSBCAPS);
  m_sb_info.m_lp_looping_buffer->GetCaps(&dsbcaps);

  m_sb_info.m_f_secondary_looping = (m_sb_info.m_lp_looping_buffer != m_sb_info.m_lp_primary_buffer);

  m_sb_info.BufferSize = dsbcaps.dwBufferBytes;

  m_sb_info.MaxWriteSamples = m_primary_frequency * MAX_WRITE_AHEAD;
  m_sb_info.MaxWriteBytes = m_sb_info.MaxWriteSamples * m_primary_alignment;

  m_sb_info.NextWritePos = -1;
  m_sb_info.LastPlayPos = 0;

  StreamFill(0, dsbcaps.dwBufferBytes);

  m_sb_info.thread_request_kill = false;
  m_sb_info.thread_alive = true;

  // Start mixing thread.
  m_sb_info.thread_handle = _beginthread(StreamTimer, 16384, (void *)&m_sb_info);
  if (m_sb_info.thread_handle == -1) {
    m_sb_info.thread_alive = false;
    mprintf(0, "Thread failed\n");
    Int3();
    return false;
  }

  if (m_sb_info.m_f_secondary_looping) {
    if (!SetThreadPriority((HANDLE)m_sb_info.thread_handle, THREAD_PRIORITY_HIGHEST))
      Int3();
  } else {
    if (!SetThreadPriority((HANDLE)m_sb_info.thread_handle, THREAD_PRIORITY_TIME_CRITICAL))
      Int3();
  }

  return true;
}

// Creates a 2d, 3d, or Primary direct sound buffer
HRESULT win_llsSystem::CreateDSBuffer(int buffer_type, LPDIRECTSOUNDBUFFER *lp_lp_dsb, LPDIRECTSOUND3DBUFFER *lp_lp_dsb_3d,
                                   DWORD sound_bytes, DWORD frequency, bool f_is_stereo, bool f_is_16_bit) {
  DSBUFFERDESC dsbd;
  tWAVEFORMATEX fmt;
  HRESULT result = DS_OK;

  ASSERT(m_lp_ds != NULL && sound_bytes >= 0);
  ASSERT(frequency == 44100 || frequency == 22050 || frequency == 11025);
  if (!m_f_sound_lib_init)
    return 0;

  if (lp_lp_dsb) {
    *lp_lp_dsb = NULL;
  }
  if (lp_lp_dsb_3d) {
    *lp_lp_dsb_3d = NULL;
  }

  // Setup the wave format
  fmt.nChannels = (f_is_stereo) ? 2 : 1;
  fmt.wBitsPerSample = (f_is_16_bit) ? 16 : 8;
  fmt.nSamplesPerSec = ((DWORD)frequency);
  fmt.nBlockAlign = fmt.nChannels * (fmt.wBitsPerSample >> 3);
  fmt.nAvgBytesPerSec = ((DWORD)fmt.nSamplesPerSec) * ((DWORD)fmt.nBlockAlign);
  fmt.wFormatTag = WAVE_FORMAT_PCM;

  // Setup the secondary direct sound buffer
  memset(&dsbd, 0, sizeof(dsbd));
  dsbd.lpwfxFormat = (LPWAVEFORMATEX)&fmt;
  dsbd.dwSize = sizeof(DSBUFFERDESC);
  dsbd.dwBufferBytes = sound_bytes;

  if (m_mixer_type == SOUND_MIXER_SOFTWARE_16) {
    dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2;

    ASSERT(buffer_type == SBT_PRIMARY);

    m_primary_frequency = m_current_frequency = frequency;
    m_primary_bit_depth = fmt.wBitsPerSample;
    m_primary_alignment = fmt.nBlockAlign;

    dsbd.lpwfxFormat = NULL;
    dsbd.dwBufferBytes = 0;
    dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_GETCURRENTPOSITION2;
  } else if (m_mixer_type == SOUND_MIXER_DS_16 || m_mixer_type == SOUND_MIXER_DS_8) {
    // There are three buffer types that we should consider.
    switch (buffer_type) {
    case SBT_2D:
      dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
      break;
    case SBT_PRIMARY:
      dsbd.lpwfxFormat = NULL;
      dsbd.dwBufferBytes = 0;
      dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
      break;
    default:
      ASSERT(0); // Invalid type of buffer
    }
  } else if (IS_3D_MIXER(m_mixer_type)) {
    // There are three buffer types that we should consider.
    switch (buffer_type) {
    case SBT_2D:
      dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
      break;
    case SBT_3D:
      dsbd.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME;
      break;
    case SBT_PRIMARY:
      dsbd.lpwfxFormat = NULL;
      dsbd.dwBufferBytes = 0;
      dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME;
      break;
    default:
      ASSERT(0); // Invalid type of buffer
    }
  } else {
    mprintf(0, "DS3DLIB: Unsupported function for mixer specfied in CreateDSBuffer (%d,%d)\n", m_mixer_type, buffer_type);
    Int3(); // Get Samir!!!
    return DSERR_UNSUPPORTED;
  }

  // Create the buffer
  result = m_lp_ds->CreateSoundBuffer(&dsbd, lp_lp_dsb, 0);
  ///	ASSERT(result == DS_OK);

  if (result == DS_OK && buffer_type == SBT_PRIMARY) {
    // Creative EAX Init
    if (m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
      if (!EAX_SetPrimaryBuffer()) {
        mprintf(0, "CreateDSBuffer: EAX Init failed.\n");
        result = DSERR_UNSUPPORTED;
        goto ds_error;
      }
    }

    // Succeeded. Set primary buffer to desired format.
    result = (*lp_lp_dsb)->SetFormat(&fmt);
  }

  if (result != DS_OK) {
    mprintf(0, "DS3DLIB: Failed to init sound buffer of type %d for mixer %d.\n", buffer_type, m_mixer_type);
    goto ds_error;
  }

  // call get format to make sure we're okay.
  if (buffer_type == SBT_PRIMARY) {
  }

  // do 3d sound support stuff.
  if (IS_3D_MIXER(m_mixer_type)) {
    // a 3d buffer needs a 3d interface pointer
    if (buffer_type == SBT_3D) {
      ASSERT(lp_lp_dsb_3d != NULL);
      result = (*lp_lp_dsb)->QueryInterface(IID_IDirectSound3DBuffer, (void **)lp_lp_dsb_3d);
      if (result != DS_OK) {
        goto ds_error;
      }

      //	ASSERT(result == DS_OK);
    } else if (buffer_type == SBT_PRIMARY) {
      if ((result = (*lp_lp_dsb)->QueryInterface(IID_IDirectSound3DListener, (void **)&m_lp_listener)) == S_OK) {
        m_lp_listener->SetRolloffFactor(ENV3DVAL_ROLLOFF_DEFAULT, DS3D_IMMEDIATE);
      }
    }
  }

ds_error:
  if (result != DS_OK) {
    mprintf(0, "DS3DLIB:result=%x\n", result);
    if (lp_lp_dsb_3d && (*lp_lp_dsb_3d)) {
      (*lp_lp_dsb_3d)->Release();
      *lp_lp_dsb_3d = NULL;
    }

    if (lp_lp_dsb && (*lp_lp_dsb)) {
      (*lp_lp_dsb)->Release();
      *lp_lp_dsb = NULL;
    }
  }

  return (long)result;
}

// Internal function to enumerate sound devices
BOOL CALLBACK LLEnumCallback(LPGUID lp_guid, LPCSTR lpstr_description, LPCSTR lpstr_module, LPVOID lp_Context) {
  GUID FAR *lp_ret_guid = (GUID FAR *)lp_Context;

  if (m_sound_device_name[0]) {
    if (strcmp(lpstr_description, m_sound_device_name) == 0) {
      mprintf(0, "Using sound card:%s-%s\n", lpstr_description, lpstr_module);
      if (lp_guid) {
        memmove(lp_ret_guid, lp_guid, sizeof(GUID));
      }
      return FALSE;
    }
  }

  return TRUE;
}

void win_llsSystem::SetSoundCard(const char *name) {
  if (name) {
    strcpy(m_sound_device_name, name);
  } else {
    m_sound_device_name[0] = 0;
  }
}

// Initializes the sound library
int win_llsSystem::InitSoundLib(char mixer_type, oeApplication *sos, uint8_t MaxSoundsPlayed) // add playlist info
{
  GUID card_guid, zero_card_guid;
  GUID *pguid = NULL;
  DSCAPS dscaps;
  HRESULT hresult;
  bool f16bit;
  bool retval = true;

  // reset error system.
  SetError(SSL_OK);
  SoundApp = sos;

  if (sos != nullptr) {
    oeWin32Application *obj = dynamic_cast<oeWin32Application*>(sos);
    ASSERT(obj != nullptr);


    // If the the library if already init'ed, then return o.k.
    if (m_f_sound_lib_init)
      return 1;

    GameWindowHandle = (void *)obj->m_hWnd;
  } else {
    ASSERT(GameWindowHandle != nullptr);
  }

  ll_sound_ptr = this;
  m_timer_last_frametime = -1;
  m_cache_stress_timer = 0.0f;
  m_in_sound_frame = false;
  m_pending_actions = false;

  //////////////////////////////////////////////////////////////////////////////
  // chrishack -- Need to enumerate sound devices for now
  // Attempt to enumerate the sound device
  // if(DirectSoundEnumerate(&LLEnumCallback, NULL) != DS_OK) return 0;

  // Setup the game handle
  m_hwnd_main = GameWindowHandle;

  // Check for invalid values and NULL pointers
  ASSERT(m_hwnd_main != NULL);
  ASSERT(Sounds != NULL);
  ASSERT(SoundFiles != NULL);
  ASSERT(MaxSoundsPlayed > 0);

  memset(&m_sb_info, 0, sizeof(DSSTREAM));

  // Currently restart total sounds played count (for unique ids and stats)
  m_total_sounds_played = 0;

  // Setup the sound mixer object
  m_sound_mixer.m_cur_sounds_played = 0;
  m_sound_mixer.m_max_sounds_played = MaxSoundsPlayed;
  m_sound_mixer.m_sound_cache = new sound_buffer_info[MaxSoundsPlayed];
  m_mixer_type = SOUND_MIXER_NONE;

  if (m_sound_mixer.m_sound_cache == NULL) {
    Int3();
    goto error_sub;
  }

  // Create the Direct Sound Interface
  //	determine GUID for sound card which was chosen in the launcher...
  ZeroMemory(&card_guid, sizeof(GUID));
  ZeroMemory(&zero_card_guid, sizeof(GUID));
  hresult = DirectSoundEnumerate(LLEnumCallback, &card_guid);
  if (hresult == DS_OK) {
    if (memcmp(&card_guid, &zero_card_guid, sizeof(GUID)) != 0) {
      pguid = &card_guid;
    }
  }

  if (mixer_type != SOUND_MIXER_NONE) {
    if (mixer_type == SOUND_MIXER_CREATIVE_EAX) {
      if (!EAX_Create(pguid, &m_lp_ds)) {
        mprintf(0, "Sound NT: Error EAX\n");
        retval = false;
        goto error_sub;
      }
    } else {
      hresult = DirectSoundCreate(pguid, &m_lp_ds, NULL);
      if (hresult != DS_OK) {
        retval = false;
        goto error_sub;
      }
    }

    ASSERT(m_lp_ds != NULL);

    // determine if we're using a crappy card
    dscaps.dwSize = sizeof(DSCAPS);
    m_lp_ds->GetCaps(&dscaps);
    if (dscaps.dwFlags & DSCAPS_EMULDRIVER) {
      mixer_type = SOUND_MIXER_DS_8;
      mprintf(0, "SOUND INIT(1):  We are in NT or have a crappy sound card\n");
    }

    m_sound_mixer.m_loop_method = DSLOOP_STREAM_METHOD;
  }

  if (mixer_type != SOUND_MIXER_NONE) {
    m_f_sound_lib_init = 1;
  }

//	This section initializes the primary buffer
// software mixer try.
retry_mixer_init:
  if (mixer_type == SOUND_MIXER_SOFTWARE_16) {
    // test different conditions to see if we really can play sound in software
    hresult = m_lp_ds->SetCooperativeLevel((HWND)m_hwnd_main, DSSCL_WRITEPRIMARY);
    if (hresult != DS_OK) {
      mprintf(0, "SOUND INIT(2):  SCL: WritePrimary failed. Attempting DS 8 init.\n");
      mixer_type = SOUND_MIXER_DS_8;
      goto retry_mixer_init;
    }

    // Creates a primary buffer and makes sure we are at the specified frequency, bit depth, and that we
    // can to 3d stuff too :)
    m_mixer_type = SOUND_MIXER_SOFTWARE_16;
    f16bit = true;
    hresult = CreateDSBuffer(SBT_PRIMARY, &m_sb_info.m_lp_primary_buffer, NULL, 0,
                             22050,   // frequency
                             true,    // stereo
                             f16bit); // 16-bit
    if (hresult != DS_OK) {
      if (m_sb_info.m_lp_primary_buffer) {
        m_sb_info.m_lp_primary_buffer->Release();
        m_sb_info.m_lp_primary_buffer = NULL;
      }
      mprintf(0, "SOUND INIT(3): Cannot create primary buffer.\n");
      mixer_type = SOUND_MIXER_DS_8;
      goto retry_mixer_init;
    } else {
      // Determine if we are running NT or have a shitty Win95 sound card
      DSBCAPS dsbcaps;

      ASSERT(m_sb_info.m_lp_primary_buffer);

      dsbcaps.dwSize = sizeof(DSBCAPS);
      m_sb_info.m_lp_primary_buffer->GetCaps(&dsbcaps);

      // Let's allocate our array of ints for our optimized software mixer!
      if (!Fast_mixer) {
        Fast_mixer = (int *)mem_malloc(dsbcaps.dwBufferBytes * sizeof(int));
        Fast_mixer_len = dsbcaps.dwBufferBytes;
        mprintf(0, "Using %d ints for fast software mixer\n", dsbcaps.dwBufferBytes);
      }

      // Is you want to see the caps, here is where -- mprintf all you want
      if (!(dsbcaps.dwFlags & DSBCAPS_LOCHARDWARE)) {
        mprintf(0, "SOUND INIT(4):  Primary is not in hardware\n");
        m_sb_info.m_lp_primary_buffer->Release();
        m_sb_info.m_lp_primary_buffer = NULL;
        mixer_type = SOUND_MIXER_DS_8;
        goto retry_mixer_init;
      }
    }

    // looping buffer is the same as the primary buffer for software mixers.
    m_sb_info.m_lp_looping_buffer = m_sb_info.m_lp_primary_buffer;

    // Start the primary and have it always play.
    m_f_sound_lib_init = StartStreaming();
    if (!m_f_sound_lib_init) {
      mprintf(0, "SOUND INIT(5):  Something went wrong in StartStreaming\n");
      m_sb_info.m_lp_primary_buffer->Release();
      m_sb_info.m_lp_primary_buffer = NULL;
      mixer_type = SOUND_MIXER_DS_8;
      goto retry_mixer_init;
    }

  } else if (mixer_type == SOUND_MIXER_NONE) {
    m_mixer_type = mixer_type;
    m_f_sound_lib_init = 0;
  } else {
    // This is for DirectSound Internal Mixers.  We let DirectSound do its magic.
    m_mixer_type = mixer_type;
    hresult = m_lp_ds->SetCooperativeLevel((HWND)m_hwnd_main, DSSCL_PRIORITY);
    if (hresult != DS_OK) {
      mprintf(0, "Sound NT: Error 1\n");
      retval = false;
      goto error_sub;
    }

    // start primary buffer
    f16bit = (mixer_type == SOUND_MIXER_DS_16 || mixer_type == SOUND_MIXER_DS3D_16 ||
              mixer_type == SOUND_MIXER_CREATIVE_EAX);
    hresult = CreateDSBuffer(SBT_PRIMARY, &m_sb_info.m_lp_primary_buffer, NULL, 0,
                             22050,   // frequency
                             true,    // stereo
                             f16bit); // 8 or 16 bit
    if (hresult != DS_OK) {
      mprintf(0, "Sound NT: Error 2\n");
      if (m_sb_info.m_lp_primary_buffer) {
        m_sb_info.m_lp_primary_buffer->Release();
        m_sb_info.m_lp_primary_buffer = NULL;
      }
      retval = false;
      goto error_sub;
    }

    m_sb_info.m_lp_primary_buffer->Play(0, 0, DSBPLAY_LOOPING);
  }

  //	buffered method doesn't use threads at all.
  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16 && m_mixer_type != SOUND_MIXER_NONE &&
      m_sound_mixer.m_loop_method != DSLOOP_BUFFER_METHOD) {
    // start looping thread, failure results in a 'clean exit'
    if (!sb_loop_thread_init(this)) {
      retval = false;
      if (m_sb_info.m_lp_primary_buffer) {
        m_sb_info.m_lp_primary_buffer->Release();
        m_sb_info.m_lp_primary_buffer = NULL;
      }
      goto error_sub;
    }
  }

  mprintf(0, "Sound mixer: ");
  retval = true;

  switch (m_mixer_type) {
  case SOUND_MIXER_SOFTWARE_16:
    mprintf(0, "Software 16\n");
    break;
  case SOUND_MIXER_DS_8:
    mprintf(0, "DS 8\n");
    break;
  case SOUND_MIXER_DS_16:
    mprintf(0, "DS 16\n");
    break;
  case SOUND_MIXER_DS3D_16:
    mprintf(0, "DS3D 16\n");
    break;
  case SOUND_MIXER_CREATIVE_EAX:
    mprintf(0, "Creative EAX\n");
    break;
  case SOUND_MIXER_NONE:
    mprintf(0, "None\n");
    break;
  default:
    mprintf(0, "LLSound ERROR: Unsupported mixer");
    Int3();
    retval = false;
    break;
  }

  // set 3d environment settings
  t3dEnvironmentToggles env_toggles;
  t3dEnvironmentValues env_values;

  memset(&Env3dValues, 0, sizeof(Env3dValues));
  memset(&Env3dToggles, 0, sizeof(Env3dToggles));

  env_toggles.flags = 0; // get supported features
  GetEnvironmentToggles(&env_toggles);

  env_values.flags = 0; // set up values and toggles to be set
  env_toggles.flags = env_toggles.supported;

  // we may want to check this with configured options later -- samir
  if (CHECK_FLAG(env_toggles.supported, ENV3DVALF_DOPPLER) && ENV3DTOG_DOPPLER) {
    env_values.flags |= ENV3DVALF_DOPPLER;
    env_values.doppler_scalar = ENV3DVAL_DOPPLER_DEFAULT;
    env_toggles.doppler = true;
  }
  if (CHECK_FLAG(env_toggles.supported, ENV3DVALF_GEOMETRY) && ENV3DTOG_GEOMETRY) {
    env_toggles.geometry = true;
  }
  SetEnvironmentToggles(&env_toggles);
  SetEnvironmentValues(&env_values);

  /////////////////////////////////////////////////////////////////////////////
  g_emulated_listener = &m_emulated_listener;

error_sub:
  if (retval == false) {
    // Only gets here if there was an error
  if (m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
      EAX_Destroy();
    } else if (m_lp_ds) {
      m_lp_ds->Release();
    }
    m_lp_ds = NULL;
    mprintf(0, "Sound Warning: Didn't initialize sound library.\n");
    if (m_sound_mixer.m_sound_cache != NULL)
      delete[] m_sound_mixer.m_sound_cache;
    m_f_sound_lib_init = 0;
    m_mixer_type = SOUND_MIXER_NONE;
  }

  Global_DS_alloced_sounds = 0;

  return (m_f_sound_lib_init);
}

// Cleans up after the sound library is done being used
void win_llsSystem::DestroySoundLib(void) {
  bool f_all_done = false;

  if (!m_f_sound_lib_init)
    return;

  mprintf(0, "Start of sound system close\n");

  //	kill sound geometry object if any.
  if (m_geometry) {
    m_geometry->Shutdown();
    m_geometry = NULL;
  }

  StopAllSounds();

  // Wait till they are all done
  mprintf(0, "Waiting for sounds to stop\n");
  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    while (!f_all_done) {
      f_all_done = true;
      int i;

      for (i = 0; i < m_sound_mixer.m_max_sounds_played; i++) {
        sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[i];
        if (sb->s && sb->s->kill_me && !(sb->m_status & (SSF_BUFFERED_LOOP + SSF_BUFFERED_STRM))) {
          cleanup_directsound_looping_sb(&m_sound_mixer.m_sound_cache[i]);
        } else if (sb->m_status & (SSF_PLAY_LOOPING | SSF_PLAY_STREAMING)) {
          // this should block until the sound is truly free, so we don't need to do a 'all done'
          StopSound(m_sound_mixer.m_sound_cache[i].m_unique_id, SKT_HOLD_UNTIL_STOP);
          //	f_all_done = false;
        }
      }
    }

    //	buffered method doesn't use threads at all.
    if (m_sound_mixer.m_loop_method != DSLOOP_BUFFER_METHOD) {
      sb_loop_thread_kill();
    }
  }
  mprintf(0, "All sounds stopped\n");

  if (m_mixer_type == SOUND_MIXER_SOFTWARE_16) {
    // Kill thread goes here
    if (m_sb_info.thread_handle) {
      m_sb_info.thread_request_kill = true;
      while (m_sb_info.thread_alive) {
      }
    }

    if (m_mixer_type == SOUND_MIXER_SOFTWARE_16) {
      m_sb_info.m_lp_looping_buffer->Stop();
      m_sb_info.m_lp_looping_buffer->Release();
    }
  }

  // free audio device;
  if (m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
    EAX_Destroy();
  } else if (m_lp_ds) {
    m_lp_ds->Release();
  }

  m_lp_ds = NULL;
  m_sb_info.m_lp_looping_buffer = NULL;

  mprintf(0, "End of sound system close\n");

  if (m_sound_mixer.m_sound_cache != NULL)
    delete[] m_sound_mixer.m_sound_cache;

  m_f_sound_lib_init = false;
  g_emulated_listener = NULL;
  m_mixer_type = -1;
  ll_sound_ptr = NULL;
  if (Fast_mixer) {
    mem_free(Fast_mixer);
    Fast_mixer = NULL;
    Fast_mixer_len = 0;
  }
}

// used to clean up direct sound buffer stuff
void win_llsSystem::cleanup_directsound_looping_sb(sound_buffer_info *sb) {
  if (!sb->s)
    return;
  if (!sb->s->kill_me)
    return;

  //	should occur when kill_me set, sb_stop_buffer(&ll_sound_ptr->m_sound_mixer.m_sound_cache[i]);
  sb_free_buffer(sb);

  sb->m_sound_buffer = NULL;
  sb->s->playing = 0;

  void *p = (void *)sb->s;
  sb->s = NULL;
  sb->m_status = SSF_UNUSED;
  mem_free(p);
}

// cleans up a sound -replaces a lot of repeated code whenever we cleanup sounds.
void win_llsSystem::update_directsound_sb(sound_buffer_info *sb, bool update_looping) {
  if (m_mixer_type == SOUND_MIXER_SOFTWARE_16 || m_mixer_type == SOUND_MIXER_NONE) {
    return;
  }

  // take care of any streamed threaded method looping sounds that are done.
  // orphan streaming structure, clean it up! (sound buffer is NULL yet sb->s is valid
  if (sb->s && (((sb->m_status & (SSF_BUFFERED_LOOP + SSF_BUFFERED_STRM)) && !sb->m_sound_buffer) || sb->s->kill_me)) {
    cleanup_directsound_looping_sb(sb);
  } else if (sb->m_status && !(sb->m_status & SSF_PAUSED)) {
    //	non playing sounds should be stopped always
    int status = sb_get_status(sb);

    if (update_looping) {
      if (status & SB_STATUS_PLAYING) {
        if ((sb->m_status & (SSF_PLAY_STREAMING + SSF_BUFFERED_STRM)) == (SSF_PLAY_STREAMING + SSF_BUFFERED_STRM)) {
          sb_stream_buffered_update(sb);
        }
      } else {
        if ((sb->m_status & (SSF_PLAY_LOOPING + SSF_BUFFERED_LOOP)) == (SSF_PLAY_LOOPING + SSF_BUFFERED_LOOP)) {
          sb_buffered_loop_step(this, sb);
          status = sb_get_status(sb); // get new status for following checks.
        }
      }
    }
    if (!(status & SB_STATUS_PLAYING)) {
      StopSound(sb->m_unique_id);
    } else if (status & SB_STATUS_INVALID) {
      StopSound(sb->m_unique_id);
    }
  }
}

// Stops the sound from playing  -- f_immediately is used for looping samples -- i.e. so we can
// play the end of loop snipit
void win_llsSystem::StopSound(int sound_uid, uint8_t f_immediately) {
  int current_slot;
  sound_buffer_info *sb;

  if (!m_f_sound_lib_init)
    return;

  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return;

  sb = &m_sound_mixer.m_sound_cache[current_slot];

  if (sb->m_status == SSF_UNUSED)
    return;

  //	update sound count.
  m_sound_mixer.m_cur_sounds_played--;

  if (f_immediately == SKT_STOP_AFTER_LOOP) {
    sb->m_status &= ~SSF_PLAY_LOOPING;
    sb->m_status |= SSF_PLAY_NORMAL;
    if (m_mixer_type != SOUND_MIXER_SOFTWARE_16 && (sb->m_status & SSF_BUFFERED_LOOP)) {
      sb_buffered_loop_step(this, sb, DSBUFLOOP_FINISH_STEP);
    }
    return;
  }

  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    if (sb->s && !(sb->m_status & (SSF_BUFFERED_LOOP + SSF_BUFFERED_STRM))) {
      sb_loop_element_kill(sb);
      if (f_immediately == SKT_HOLD_UNTIL_STOP) {
        sb_loop_element_wait_until_dead(sb);
        cleanup_directsound_looping_sb(sb);
      }
      return;
    } else if (sb->m_sound_buffer) // this works for buffered loops too.
    {
      if (sb->m_status & (SSF_BUFFERED_LOOP + SSF_BUFFERED_STRM)) {
        if (sb->m_status & SSF_PLAY_STREAMING) {
          sb_stream_element_kill(sb);
        }

        void *p = (void *)sb->s;
        if (p) {
          mem_free(p);
          sb->s = NULL;
        }
      }
      GetSoundPos(sb->m_unique_id);
      sb_stop_buffer(sb);
      sb_free_buffer(sb);

      if (SoundFiles[Sounds[sb->m_sound_index].sample_index].use_count > 0) {
        SoundFiles[Sounds[sb->m_sound_index].sample_index].use_count--;
        // DUPSND	if (SoundFiles[Sounds[sb->m_sound_index].sample_index].use_count == 0) {
        // DUPSND		Global_DS_alloced_sounds--;
        // DUPSND	}
      }
      Global_DS_alloced_sounds--;
    }
    m_sound_mixer.m_sound_cache[current_slot].m_sound_buffer = NULL;
  }

  //	mprintf(0, "SL cleaning slot %d\n", current_slot);
  m_sound_mixer.m_sound_cache[current_slot].m_status = SSF_UNUSED;
}

// Copies sound data from the external sound data block to an individual sound buffer
HRESULT LoadSoundData(LPDIRECTSOUNDBUFFER lp_dsb, char *sound_data_ptr, DWORD total_bytes) {
  LPVOID ptr1, ptr2;
  DWORD len1, len2;
  HRESULT result;

  ASSERT(lp_dsb != NULL && sound_data_ptr != NULL && total_bytes > 0);

TryLockAgainLabel:
  result = lp_dsb->Lock(0, total_bytes, &ptr1, &len1, &ptr2, &len2, 0);

  switch (result) {
  case DS_OK:
    memcpy(ptr1, sound_data_ptr, len1);
    if (ptr2)
      memcpy(ptr2, sound_data_ptr + len1, len2);
    lp_dsb->Unlock(ptr1, len1, ptr2, len2);
    break;
  case DSERR_BUFFERLOST:
    result = lp_dsb->Restore();
    if (result == DS_OK)
      goto TryLockAgainLabel;
    break;
  }

  return (long)result;
}

// Determines if a sound will play.  Takes into account maximum allowable
// sounds.
// Also put prioritization code in here
//		ignore reserved slots

#ifdef _DEBUG
int16_t win_llsSystem::FindFreeSoundSlot(int sound_index, float volume, int priority)
#else
int16_t win_llsSystem::FindFreeSoundSlot(float volume, int priority)
#endif
{
  int current_slot;
  sound_buffer_info *sb;

  //	stop any left over sounds for Direct Sound.
  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
      sb = &m_sound_mixer.m_sound_cache[current_slot];
      update_directsound_sb(sb);
    }
  }

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    sb = &m_sound_mixer.m_sound_cache[current_slot];
    if (sb->m_status == SSF_UNUSED) {
      if (!((m_mixer_type == SOUND_MIXER_DS_8 || m_mixer_type == SOUND_MIXER_DS_16 ||
             m_mixer_type == SOUND_MIXER_DS3D_16 ||
             m_mixer_type == SOUND_MIXER_CREATIVE_EAX) &&
            sb->s))
        return current_slot;
    }
  }

  // no more slots? take priority into account.
  // throw out lowest priority sound slot (must be lower than or equal to new sound priority)
  float weighted_priority = (priority * 2.0f) * volume;
  if (current_slot == m_sound_mixer.m_max_sounds_played) {
    int throw_out_slot = -1, equiv_priority_slot = -1;
    float weighted_priorityA, weighted_priorityB;
    for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
      sb = &m_sound_mixer.m_sound_cache[current_slot];
      if (!(sb->m_status & (SSF_PLAY_LOOPING + SSF_PLAY_STREAMING))) {
        weighted_priorityA = sb->play_info->priority * 2.0f * sb->m_volume;
        if (weighted_priorityA < weighted_priority) {
          if (throw_out_slot == -1) {
            throw_out_slot = current_slot;
          } else {
            play_information *play_info2 = m_sound_mixer.m_sound_cache[throw_out_slot].play_info;
            weighted_priorityB = play_info2->priority * 2.0f * sb->m_volume;
            if (weighted_priorityB > weighted_priorityA) {
              throw_out_slot = current_slot;
            }
          }
        }

        else if (equiv_priority_slot == -1 && weighted_priorityA == weighted_priority) {
          equiv_priority_slot = current_slot;
        }
      }
    }

    // if no slot found to stop, look for a slot with priority == new priority
    if (throw_out_slot == -1) {
      throw_out_slot = equiv_priority_slot;
    }
    if (throw_out_slot > -1) {
      sb = &m_sound_mixer.m_sound_cache[throw_out_slot];
      win_llsSystem::StopSound(sb->m_unique_id, SKT_HOLD_UNTIL_STOP);
/*
      mprintf(0, "DDSNDLIB: Replace sound (p:%d) with sound (p:%d) in slot %d\n",
              sb->play_info->priority,
              priority,
              throw_out_slot));
*/
      return throw_out_slot;
    }
  }

#ifdef _DEBUG
  if (sound_index > -1) {
    mprintf(0, "DDSNDLIB: Sound %s with priority (%d) too low.\n", Sounds[sound_index].name, priority);
  } else {
    mprintf(0, "DDSNDLIB: Sound unknown with priority (%d) too low.\n", priority);
  }
#endif

  return -1;
}

int win_llsSystem::PlaySound2d(play_information *play_info, int sound_index, float f_volume, float f_pan,
                               bool f_looped) {
  sound_buffer_info *sb = NULL;
  int16_t sound_slot;

  if (!m_f_sound_lib_init) {
    return -1;
  }

  // calculate volume and pan
  f_volume = (f_volume < 0.0f) ? 0.0f : (f_volume > 1.0f) ? 1.0f : f_volume;
  play_info->left_volume = play_info->right_volume = f_volume;

  f_pan = (f_pan < -1.0f) ? -1.0f : (f_pan > 1.0f) ? 1.0f : f_pan;
  if (f_pan < 0.0) {
    play_info->right_volume += f_volume * f_pan;
  } else {
    play_info->left_volume -= f_volume * f_pan;
  }

  // do common processing.
  if (SoundFiles[Sounds[sound_index].sample_index].used == 0) {
    mprintf(0, "Tryed to play %d sound, it DNE.\n", sound_index);
    return -1;
  }
#ifdef _DEBUG
  sound_slot = FindFreeSoundSlot(sound_index, f_volume, play_info->priority);
#else
  sound_slot = FindFreeSoundSlot(f_volume, play_info->priority);
#endif
  if (sound_slot < 0) {
    // do prioritization code here.
    return -1;
  }
  sb = &m_sound_mixer.m_sound_cache[sound_slot];
  m_total_sounds_played++;
  sb->play_info = play_info;
  sb->m_unique_id = MakeUniqueId(sound_slot);
  sb->m_buffer_type = SBT_2D;
  sb->m_sound_index = sound_index;
  sb->m_status = SSF_UNUSED;

  ASSERT(sb->m_unique_id != -1);

  // play 2d sound
  if (m_mixer_type == SOUND_MIXER_SOFTWARE_16) {
    sb->m_status = (f_looped) ? SSF_PLAY_LOOPING : SSF_PLAY_NORMAL;
    return sb->m_unique_id;
  }

  if (f_looped) {
    LoopStartStreaming(sb, SBT_2D, f_volume, f_pan, NULL);
    if (sb->m_snd_obj == NULL) {
      sb->m_status = SSF_UNUSED;
      Int3();
      return -1;
    }
  } else {
    tPSBInfo psb;

    if (SoundFiles[Sounds[sound_index].sample_index].use_count > 0) {
      if (DuplicateSoundBuffer(sb)) {
        goto play_sound;
      }
    }
    if (!CreateSoundBuffer(sb, false)) {
      return -1;
    }
    if (!LoadSoundBuffer(sb)) {
      sb_free_buffer(sb);
      return -1;
    }

  play_sound:
    sb->m_status = SSF_PLAY_NORMAL;

    psb.volume = f_volume;
    psb.pan = f_pan;
    psb.freq = 22050;
    psb.looping = false;
    if (!PlaySoundBuffer(sb, &psb)) {
      sb_free_buffer(sb);
      return -1;
    }
  }

  m_sound_mixer.m_cur_sounds_played++;

  return sb->m_unique_id;
}

void win_llsSystem::LoopStartStreaming(sound_buffer_info *sb, int buffer_type, float volume, float pan,
                                       pos_state *cur_pos) {
  //	unsigned long thread_handle;
  int sound_length, buffer_size;
  int determined_method;
  bool f_sample_16bit;
  char *sample_ptr;
  tPSBInfo psb;
  DSLOOPSTREAM *s;

  // setup looping buffer. must clear out before assigning to sound buffer for thread security.
  s = (DSLOOPSTREAM *)mem_malloc(sizeof(DSLOOPSTREAM));
  if (s == NULL) {
    sb->s = NULL;
    return;
  }
  memset((void *)s, 0, sizeof(DSLOOPSTREAM));
  sb->s = s;

  sample_ptr = get_sound_info(sb, &sound_length, &f_sample_16bit);
  sb->s->f_sample_16bit = f_sample_16bit;
  sb->m_buffer_type = buffer_type;

  if (m_sound_mixer.m_loop_method == DSLOOP_SMART_METHOD) {
    int loop_startb, loop_endb;
    bool b;
    if (sb_get_loop_info(sb, &loop_startb, &loop_endb, &b)) {
      if (SoundFiles[Sounds[sb->m_sound_index].sample_index].np_sample_length == (loop_endb - loop_startb + 1)) {
        determined_method = DSLOOP_BUFFER_METHOD;
      } else {
        determined_method = DSLOOP_STREAM_METHOD;
      }
    } else { // wtf?
      return;
    }
  } else {
    determined_method = m_sound_mixer.m_loop_method;
  }

  switch (determined_method) {
  case DSLOOP_BUFFER_METHOD:
    sound_length = 0;
    sb->s->loop_step = -1;
    while (!sound_length && sb->s->loop_step < 2) {
      sample_ptr = sb_get_loop_step_info(sb, sb->s->loop_step, f_sample_16bit, &sound_length);
      sb->s->loop_step++;
    }
    if (!sound_length && sb->s->loop_step == 2) {
      //	hmm, weird loop.  no sample?
      return;
    }
    sb->s->loop_step--; // return to proper step.
    sb->s->loop_timer = 0.0f;
    sb->s->bytes_left = sound_length;
    buffer_size = sound_length;
    sb->m_status = SSF_PLAY_LOOPING | SSF_BUFFERED_LOOP;
    //		mprintf(0, "DDSNDLIB: Starting buffered loop %d (step %d).\n", sb->m_unique_id, sb->s->loop_step);
    break;
  default:
    buffer_size = STREAM_BUFFER_SIZE;
    sb->m_status = SSF_PLAY_LOOPING; // must go before buffer is initialized!!!!!!
  }

  sb->sample_data = sample_ptr;

  // allocate buffer for playback
  if (!CreateSoundBuffer(sb, false, buffer_size, (sb->m_status & SSF_BUFFERED_LOOP) ? false : true)) {
    return;
  }

  // remind sb system and play.
  if (determined_method == DSLOOP_BUFFER_METHOD) {
    psb.looping = (sb->s->loop_step == 0) ? true : false;
    if (!sb_load_buffer(sb, sb->sample_data, sound_length))
      return;
  } else if (sb_loop_element_init(sb, sample_ptr, sound_length, STREAM_BUFFER_SIZE)) {
    psb.looping = true;
  } else {
    sb->s->playing = 0;
    return;
  }

  if (buffer_type == SBT_3D) {
    psb.cur_pos = cur_pos;
  } else {
    ASSERT(buffer_type == SBT_2D);
    psb.pan = pan;
  }
  psb.volume = volume;
  psb.freq = 22050;

  PlaySoundBuffer(sb, &psb);

  // must be at end to initiate thread management.
  sb->s->playing = 1;
}

void win_llsSystem::DSStartStreaming(sound_buffer_info *sb, float volume, float pan) {
  tPSBInfo psb;
  int sound_length;
  int stream_buflength;
  int determined_method;
  char *sample_ptr;
  bool f_stereo;

  sb->s = (DSLOOPSTREAM *)mem_malloc(sizeof(DSLOOPSTREAM));
  ASSERT(sb->s);
  if (sb->s == NULL)
    return;

  memset((void *)sb->s, 0, sizeof(DSLOOPSTREAM));

  sample_ptr = (char *)sb->play_info->m_stream_data;
  sound_length = sb->play_info->m_stream_size;
  stream_buflength = sb->play_info->m_stream_bufsize;

  switch (sb->play_info->m_stream_format) {
  case SIF_STREAMING_16_M:
    sb->s->f_sample_16bit = true;
    f_stereo = false;
    break;

  case SIF_STREAMING_8_M:
    sb->s->f_sample_16bit = false;
    f_stereo = false;
    break;

  case SIF_STREAMING_16_S:
    sb->s->f_sample_16bit = true;
    f_stereo = true;
    break;

  case SIF_STREAMING_8_S:
    sb->s->f_sample_16bit = false;
    f_stereo = true;
    break;

  default:
    ASSERT(0);
    break;
  }

  ASSERT(sb->m_buffer_type == SBT_2D);
  sb->m_sound_index = -1;

  // determine how we will stream this data
  determined_method = m_sound_mixer.m_loop_method;
  switch (determined_method) {
  case DSLOOP_BUFFER_METHOD:
    sb->m_status = SSF_PLAY_STREAMING | SSF_BUFFERED_STRM;
    break;
  default:
    sb->m_status = SSF_PLAY_STREAMING; // must go before buffer is initialized!!!!!!
    break;
  }

  if (!CreateSoundBuffer(sb, f_stereo, stream_buflength, true)) {
    mem_free((void *)sb->s);
    sb->s = NULL;
    return;
  }

  // set wave event or do thread streamed method
  if (sb_stream_element_init(sb, sample_ptr, sound_length, stream_buflength)) {
    psb.pan = pan;
    psb.volume = volume;
    psb.freq = 22050;
    psb.looping = true;

    PlaySoundBuffer(sb, &psb);

    // must be at end to initiate thread management.
    sb->s->playing = 1;
  }
}

int win_llsSystem::PlayStream(play_information *play_info) {
  int16_t sound_slot;
  DWORD ds_flags = 0;

  ASSERT(play_info != NULL);

  float volume = (play_info->left_volume > play_info->right_volume) ? play_info->left_volume : play_info->right_volume;

  if (!m_f_sound_lib_init)
    return -1;

#ifdef _DEBUG
  sound_slot = FindFreeSoundSlot(-1, volume, play_info->priority);
#else
  sound_slot = FindFreeSoundSlot(volume, play_info->priority);
#endif
  // Out of sound slots
  if (sound_slot < 0) {
    return -1;
  }

  //	mprintf(0, "TS(%d)Playing sound index %d at %d volume,%d pan\n", TotalSoundsPlayed, sound_index, volume, pan);

  m_total_sounds_played++;
  m_sound_mixer.m_sound_cache[sound_slot].play_info = play_info;

  m_sound_mixer.m_sound_cache[sound_slot].m_unique_id = MakeUniqueId(sound_slot);
  ASSERT(m_sound_mixer.m_sound_cache[sound_slot].m_unique_id != -1);

  m_sound_mixer.m_sound_cache[sound_slot].m_buffer_type = SBT_2D;

  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    float volume;
    float pan;
    LPDIRECTSOUNDBUFFER sound_ptr;

    if (play_info->left_volume > play_info->right_volume) {
      volume = play_info->left_volume;
      pan = -1.0f + (play_info->right_volume / play_info->left_volume);
    } else {
      volume = play_info->right_volume;
      pan = 1.0f - (play_info->left_volume / play_info->right_volume);
    }

    DSStartStreaming(&m_sound_mixer.m_sound_cache[sound_slot], volume, pan);
    sound_ptr = m_sound_mixer.m_sound_cache[sound_slot].m_sound_buffer;
    if (sound_ptr == NULL) {
      m_sound_mixer.m_sound_cache[sound_slot].m_sound_buffer = NULL;
      return -1;
    }
  } else {
    m_sound_mixer.m_sound_cache[sound_slot].m_status = SSF_PLAY_STREAMING;
  }

  m_sound_mixer.m_cur_sounds_played++;

  return (m_sound_mixer.m_sound_cache[sound_slot].m_unique_id);
}

// Checks a Unique Sound ID and determines if that sound is still playing
bool win_llsSystem::IsSoundInstancePlaying(int sound_uid) {
  int current_slot;

  if (!m_f_sound_lib_init)
    return false;

  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return false;

  //	mprintf(0, "Checking slot %d of UID %d\n", current_slot, sound_uid);

  if (m_sound_mixer.m_sound_cache[current_slot].m_status != SSF_UNUSED) {
    return true;
  }

  return false;
}

// Is this sound placing on any "channel"
int win_llsSystem::IsSoundPlaying(int sound_index) {
  int current_slot;

  if (!m_f_sound_lib_init)
    return -1;

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    if ((m_sound_mixer.m_sound_cache[current_slot].m_status != SSF_UNUSED) &&
        (m_sound_mixer.m_sound_cache[current_slot].m_sound_index == sound_index)) {
      return m_sound_mixer.m_sound_cache[current_slot].m_unique_id;
    }
  }

  return -1;
}

// This function limits the number of sounds cached to 255(8bits) and 256 bit is for invalid channel
// The purpose is to create unique signatures for each sound played (and allow for
// the slot_number to be quickly determined)
inline int win_llsSystem::MakeUniqueId(int sound_slot) { return ((((int)m_total_sounds_played) << 8) + sound_slot); }

inline int win_llsSystem::ValidateUniqueId(int sound_uid) {
  if (sound_uid == m_sound_mixer.m_sound_cache[sound_uid & 0x00FF].m_unique_id) {
    return sound_uid & 0x00FF;
  } else {
    return -1;
  }
}

void win_llsSystem::PauseSounds() {
  int current_slot;

  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {

    for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
      sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];
      update_directsound_sb(sb);

      /*	if((sb->m_status != SSF_UNUSED) &&
                      ((sb->m_status & SSF_PAUSED) == 0))
              {
                      int status = sb_get_status(sb);

                      if(!(status & SB_STATUS_PLAYING)) {
                              ll_sound_ptr->StopSound(sb->m_unique_id);
                      }
                      else if (status & SB_STATUS_INVALID) {
                              ll_sound_ptr->StopSound(sb->m_unique_id);
                      }
              }
      */
    }
  }

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];
    if (sb->m_status != SSF_UNUSED && !(sb->m_status & SSF_PAUSED)) {
      sb->m_status |= SSF_PAUSED;
      if (m_mixer_type != SOUND_MIXER_SOFTWARE_16 && (sb->m_sound_buffer)) {
        sb_stop_buffer(sb);
      }
    }
  }
}

void win_llsSystem::ResumeSounds() {
  int current_slot;

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];

    if (sb->m_status != SSF_UNUSED && (sb->m_status & SSF_PAUSED)) {
      if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
        PlaySoundBuffer(sb, NULL);
      }

      m_sound_mixer.m_sound_cache[current_slot].m_status &= (~SSF_PAUSED);
    }
  }
}

void win_llsSystem::PauseSound(int sound_uid) {
  int current_slot;

  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {

    for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
      sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];

      if (sb->m_unique_id == sound_uid) {
        update_directsound_sb(sb);

        /*	if((sb->m_status != SSF_UNUSED) && ((sb->m_status & SSF_PAUSED) == 0))
                {
                        int status = sb_get_status(sb);

                        if(!(status & SB_STATUS_PLAYING)) {
                                ll_sound_ptr->StopSound(sb->m_unique_id);
                        }
                        else if (status & SB_STATUS_INVALID) {
                                ll_sound_ptr->StopSound(sb->m_unique_id);
                        }
                }
        */
        break;
      }
    }
  }

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];
    if (sb->m_unique_id == sound_uid) {
      if (sb->m_status != SSF_UNUSED && !(sb->m_status & SSF_PAUSED)) {
        sb->m_status |= SSF_PAUSED;
        if (m_mixer_type != SOUND_MIXER_SOFTWARE_16 && (sb->m_sound_buffer)) {
          sb_stop_buffer(sb);
        }
      }
      break;
    }
  }
}

void win_llsSystem::ResumeSound(int sound_uid) {
  int current_slot;

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    if (sound_uid == m_sound_mixer.m_sound_cache[current_slot].m_unique_id) {
      if (m_sound_mixer.m_sound_cache[current_slot].m_status != SSF_UNUSED &&
          (m_sound_mixer.m_sound_cache[current_slot].m_status & SSF_PAUSED)) {
        if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
          PlaySoundBuffer(&m_sound_mixer.m_sound_cache[current_slot], NULL);
        }

        m_sound_mixer.m_sound_cache[current_slot].m_status &= (~SSF_PAUSED);
        break;
      }
    }
  }
}

void win_llsSystem::StopAllSounds() {
  int current_slot;

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    if (m_sound_mixer.m_sound_cache[current_slot].m_status != SSF_UNUSED) {
      StopSound(m_sound_mixer.m_sound_cache[current_slot].m_unique_id);
    }
  }
}

// Begin sound frame
void win_llsSystem::SoundStartFrame(void) {
  float frame_time;
  int current_slot;
  int i;

  if (m_timer_last_frametime == -1) {
    frame_time = 0.0f;
  } else {
    frame_time = (timer_GetMSTime() - m_timer_last_frametime) / 1000.0f;
  }
  m_timer_last_frametime = timer_GetMSTime();

  //	perform necessary functions if sound events are pending for frame, this doesn't have to do anything
  // if the mixer doesn't require such actions.  Aureal does though.
  if (m_pending_actions) {
    mprintf(0, "pending actions\n");
  }

  // start mixer dependant frame
  m_in_sound_frame = true;
  m_pending_actions = false;

  // cleanup sound cache.
  //	mprintf(0, "StartCleanup\n");
  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    for (i = 0; i < m_sound_mixer.m_max_sounds_played; i++) {
      sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[i];
      update_directsound_sb(sb, true);
    }
  }
  //	mprintf(0, "EndCleanup\n");

  int counter = 0, loop_counter = 0, stream_counter = 0, buf_loop_counter = 0;

#ifdef _DEBUG
  int n_p5 = 0, n_p4 = 0, n_p3 = 0, n_p2 = 0, n_p1 = 0, n_p0 = 0;
#endif

  for (current_slot = 0; current_slot < m_sound_mixer.m_max_sounds_played; current_slot++) {
    sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];
    if (sb->m_status != SSF_UNUSED) {
      counter++;
      if (sb->m_status & SSF_PLAY_LOOPING) {
        if (sb->m_status & SSF_BUFFERED_LOOP)
          buf_loop_counter++;
        loop_counter++;
      }
      if (sb->m_status & SSF_PLAY_STREAMING)
        stream_counter++;

#ifdef _DEBUG
      if (sb->play_info->priority == SND_PRIORITY_CRITICAL)
        n_p5++;
      else if (sb->play_info->priority == SND_PRIORITY_HIGHEST)
        n_p4++;
      else if (sb->play_info->priority == SND_PRIORITY_HIGH)
        n_p3++;
      else if (sb->play_info->priority == SND_PRIORITY_NORMAL)
        n_p2++;
      else if (sb->play_info->priority == SND_PRIORITY_LOW)
        n_p1++;
      else if (sb->play_info->priority == SND_PRIORITY_LOWEST)
        n_p0++;
#endif
    }
  }

  // update cache stress timer.
  if (counter < (m_sound_mixer.m_max_sounds_played * 3 / 4)) {
    m_cache_stress_timer += frame_time;
  } else {
    m_cache_stress_timer = 0.0f;
  }

#ifdef _DEBUG
  mprintf_at(3, 2, 0, "LNS: %02d/%02d", counter, m_sound_mixer.m_max_sounds_played);
  mprintf_at(3, 3, 1, "Lp: %02d", loop_counter);
  mprintf_at(3, 4, 1, "St: %02d", stream_counter);
  mprintf_at(3, 5, 0, " Ot: %02d", counter - loop_counter - stream_counter);

  if (m_sound_mixer.m_loop_method != DSLOOP_STREAM_METHOD && m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    mprintf_at(3, 3, 10, "Bf: %02d", buf_loop_counter);
  }

  mprintf_at(3, 2, 20, "P5:%02d P4:%02d P3:%02d", n_p5, n_p4, n_p3);
  mprintf_at(3, 3, 20, "P2:%02d P1:%02d P0:%02d", n_p2, n_p1, n_p0);
#endif
}

// End sound frame
void win_llsSystem::SoundEndFrame(void) {
  CheckForErrors(); // handles errors.

  m_in_sound_frame = false;
}

bool win_llsSystem::LockSound(int sound_uid) { return false; }

bool win_llsSystem::UnlockSound(int sound_uid) { return false; }

// True means it was already loaded, false means that it was not
bool win_llsSystem::CheckAndForceSoundDataAlloc(int sound_index) {
  int result;
  int sound_file_index = Sounds[sound_index].sample_index;

  ASSERT(sound_file_index >= 0 && sound_file_index < MAX_SOUND_FILES);

  if (sound_file_index < 0 || sound_file_index >= MAX_SOUND_FILES) {
    return false;
  }

  // Check if the sample data is already loaded
  if (SoundFiles[sound_file_index].sample_16bit != NULL || SoundFiles[sound_file_index].sample_8bit != NULL)
    return true;

  // If not, get the sound data
  result = SoundLoadWaveFile(SoundFiles[sound_file_index].name, Sounds[sound_index].import_volume, sound_file_index,
                             (m_sound_quality == SQT_HIGH), true);

  // Why would it load once (table load time) and not now?
  if (!result)
    return false;

  mprintf(0, "Sound %s loaded.\n", SoundFiles[sound_file_index].name);

  return true;
}

bool win_llsSystem::SetSoundQuality(char quality) {
  int i;

  if (quality == m_sound_quality)
    return true;

  //	 pause any sounds that may be playing
  win_llsSystem::PauseSounds();

  if (quality == SQT_NORMAL) {
    m_sound_quality = SQT_NORMAL;
  } else {
    m_sound_quality = SQT_HIGH;
  }

  for (i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used != 0) {
      int j = Sounds[i].sample_index;

      if (SoundFiles[j].sample_8bit && m_sound_quality == SQT_HIGH) {
        GlobalFree(SoundFiles[j].sample_8bit);
        SoundFiles[j].sample_8bit = NULL;

        CheckAndForceSoundDataAlloc(i);
      }
      if (SoundFiles[j].sample_16bit && m_sound_quality == SQT_NORMAL) {
        int count;

        ASSERT(SoundFiles[j].sample_8bit == NULL);
        SoundFiles[j].sample_8bit = (uint8_t *)GlobalAlloc(0, SoundFiles[j].sample_length);

        // NOTE:  Interesting note on sound conversion:  16 bit sounds are signed (0 biase).  8 bit sounds are unsigned
        // (+128 biase).
        for (count = 0; count < (int)SoundFiles[j].sample_length; count++) {
          SoundFiles[j].sample_8bit[count] = (uint8_t)((((int)SoundFiles[j].sample_16bit[count]) + 32767) >> 8);
        }

        GlobalFree(SoundFiles[j].sample_16bit);
        SoundFiles[j].sample_16bit = NULL;
      }
    }
  }

  win_llsSystem::ResumeSounds();

  return true;
}

char win_llsSystem::GetSoundQuality(void) { return m_sound_quality; }

bool win_llsSystem::SetSoundMixer(char mixer_type) {
  if (mixer_type == m_mixer_type)
    return true;
  else {
    // Chris note:  This is not the best way to do this.  All the currently playing
    // sounds are lost.  This shouldn't happen.  A real solutions has to take in account
    // for three things:  Normal sounds, looping sounds, and streaming audio.
    DestroySoundLib();
    InitSoundLib(mixer_type, SoundApp, m_sound_mixer.m_max_sounds_played);
    SetSoundQuality(m_sound_quality);
  }
  return true;
}

char win_llsSystem::GetSoundMixer(void) { return m_mixer_type; }

void win_llsSystem::SetListener(pos_state *cur_pos) {
  if (!m_f_sound_lib_init)
    return;

  m_emulated_listener.orient = *cur_pos->orient;
  m_emulated_listener.position = *cur_pos->position;
  m_emulated_listener.velocity = *cur_pos->velocity;

  if (IS_3D_MIXER(m_mixer_type)) {
    m_lp_listener->SetOrientation(cur_pos->orient->fvec.x, cur_pos->orient->fvec.y, cur_pos->orient->fvec.z,
                                  cur_pos->orient->uvec.x, cur_pos->orient->uvec.y, cur_pos->orient->uvec.z,
                                  DS3D_DEFERRED);
    m_lp_listener->SetPosition(cur_pos->position->x, cur_pos->position->y, cur_pos->position->z, DS3D_DEFERRED);
    m_lp_listener->SetVelocity(cur_pos->velocity->x, cur_pos->velocity->y, cur_pos->velocity->z, DS3D_DEFERRED);
    m_lp_listener->CommitDeferredSettings();
  }
}

// AdjustSound2d -- adjusts the volume, pan, and freq. of a sound
void win_llsSystem::AdjustSound(int sound_uid, float f_volume, float f_pan, uint16_t frequency) {
  int current_slot;

  if (!m_f_sound_lib_init)
    return;

  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return;
  if (m_sound_mixer.m_sound_cache[current_slot].m_status == SSF_UNUSED)
    return;

  sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];
  play_information *play_info = sb->play_info;

  play_info->left_volume = play_info->right_volume = f_volume;
  if (f_pan < 0.0)
    play_info->right_volume += f_volume * f_pan;
  else
    play_info->left_volume -= f_volume * f_pan;

  sb_adjust_properties_2d(&m_sound_mixer.m_sound_cache[current_slot], f_volume, f_pan, frequency);

  return;
}

void win_llsSystem::AdjustSound(int sound_uid, pos_state *cur_pos, float adjusted_volume, float reverb) {
  if (!m_f_sound_lib_init)
    return;

  LPDIRECTSOUNDBUFFER lp_dsb;
  // LPDIRECTSOUND3DBUFFER lpDSB3D;
  int current_slot;

  if (!m_f_sound_lib_init)
    return;

  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return;
  if (m_sound_mixer.m_sound_cache[current_slot].m_status == SSF_UNUSED)
    return;

  //	sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];

  if (IS_3D_MIXER(m_mixer_type)) {
    int sound_index = m_sound_mixer.m_sound_cache[current_slot].m_sound_index;
    lp_dsb = m_sound_mixer.m_sound_cache[current_slot].m_sound_buffer;
    if (lp_dsb == NULL)
      return;

    sb_adjust_properties_3d(&m_sound_mixer.m_sound_cache[current_slot], adjusted_volume, cur_pos, reverb);
  } else {
    // We need to determine the pan and volume
    float volume;

    volume = adjusted_volume;

    float dist;
    vector dir_to_sound = *cur_pos->position - m_emulated_listener.position;
    float pan;

    dist = vm_NormalizeVector(&dir_to_sound);
    if (dist < .1f) {
      dir_to_sound = m_emulated_listener.orient.fvec;
    }

    if (dist >= Sounds[m_sound_mixer.m_sound_cache[current_slot].m_sound_index].max_distance) {
      volume = 0.0f;
    } else if (dist > Sounds[m_sound_mixer.m_sound_cache[current_slot].m_sound_index].min_distance) {
      volume *= (1.0 - ((dist - Sounds[m_sound_mixer.m_sound_cache[current_slot].m_sound_index].min_distance) /
                        (Sounds[m_sound_mixer.m_sound_cache[current_slot].m_sound_index].max_distance -
                         Sounds[m_sound_mixer.m_sound_cache[current_slot].m_sound_index].min_distance)));
    }

    pan = (dir_to_sound * m_emulated_listener.orient.rvec);

    if (volume < 0.0f)
      volume = 0.0f;
    else if (volume > 1.0f)
      volume = 1.0f;

    if (pan < -1.0f)
      pan = -1.0f;
    else if (pan > 1.0f)
      pan = 1.0f;

    AdjustSound(m_sound_mixer.m_sound_cache[current_slot].m_unique_id, volume, pan, 22050);
  }

  return;
}

int win_llsSystem::PlaySound3d(play_information *play_info, int sound_index, pos_state *cur_pos, float adjusted_volume,
                               bool f_looped, float reverb) {
  int16_t sound_slot;
  DWORD ds_flags = 0;
  float volume;

  volume = adjusted_volume; // Adjust base volume by sent volume, let 3d stuff do the rest

  if (!m_f_sound_lib_init)
    return -1;

  ASSERT(Sounds[sound_index].used != 0);
  if (Sounds[sound_index].used == 0)
    return -1;

  if (!IS_3D_MIXER(m_mixer_type)) {
    float dist;
    vector dir_to_sound = *cur_pos->position - m_emulated_listener.position;
    float pan;

    dist = vm_NormalizeVector(&dir_to_sound);
    if (dist < .1f) {
      dir_to_sound = m_emulated_listener.orient.fvec;
    }

    if (dist >= Sounds[sound_index].max_distance) {
      return -1;
    } else if (dist > Sounds[sound_index].min_distance) {
      volume *= (1.0 - ((dist - Sounds[sound_index].min_distance) /
                        (Sounds[sound_index].max_distance - Sounds[sound_index].min_distance)));
    }

    pan = (dir_to_sound * m_emulated_listener.orient.rvec);

    if (volume < 0.0f)
      volume = 0.0f;
    else if (volume > 1.0f)
      volume = 1.0f;

    if (pan < -1.0f)
      pan = -1.0f;
    else if (pan > 1.0f)
      pan = 1.0f;

    return PlaySound2d(play_info, sound_index, volume, pan, f_looped);
  }

// Out of sound slots
#ifdef _DEBUG
  sound_slot = FindFreeSoundSlot(sound_index, volume, play_info->priority);
#else
  sound_slot = FindFreeSoundSlot(volume, play_info->priority);
#endif

  if (sound_slot < 0) {
    return -1;
  }

  m_sound_mixer.m_sound_cache[sound_slot].play_info = play_info;
  m_total_sounds_played++;
  m_sound_mixer.m_sound_cache[sound_slot].m_unique_id = MakeUniqueId(sound_slot);
  ASSERT(m_sound_mixer.m_sound_cache[sound_slot].m_unique_id != -1);

  // 3-D!!
  sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[sound_slot];

  sb->m_buffer_type = SBT_3D;
  sb->m_sound_index = sound_index;

  if (f_looped) {
    LoopStartStreaming(sb, SBT_3D, adjusted_volume, 0.0, cur_pos);
    if (sb->m_snd_obj == NULL) {
      sb->m_sound_buffer = NULL;
      Int3();
      return -1;
    }
  } else {
    tPSBInfo psb;

    if (SoundFiles[Sounds[sound_index].sample_index].use_count > 0) {
      if (DuplicateSoundBuffer(sb)) {
        goto play_sound;
      }
    }
    if (!CreateSoundBuffer(sb, false)) {
      return -1;
    }
    if (!LoadSoundBuffer(sb)) {
      sb_free_buffer(sb);
      return -1;
    }

  play_sound:
    sb->m_status = SSF_PLAY_NORMAL;

    psb.cur_pos = cur_pos;
    psb.volume = volume;
    psb.freq = 22050;
    psb.reverb = reverb;
    psb.looping = false;
    if (!PlaySoundBuffer(sb, &psb)) {
      sb_free_buffer(sb);
      return -1;
    }
/*
    mprintf(0, "SL Play sound on slot %d, TP = %d UI = %X\n",
            sound_slot,
            TotalSoundsPlayed,
            m_sound_mixer.m_sound_cache[sound_slot].m_unique_id);
*/
  }

  m_sound_mixer.m_cur_sounds_played++;

  return (sb->m_unique_id);
}

// These work in samples to make things easier in the long run
int win_llsSystem::SetSoundPos(int sound_uid, int pos) {
  int current_slot;

  if (pos <= 0)
    return 1;

  if (!m_f_sound_lib_init)
    return -1;
  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return -1;
  if (m_sound_mixer.m_sound_cache[current_slot].m_status == SSF_UNUSED)
    return -1;

  m_sound_mixer.m_sound_cache[current_slot].play_info->m_samples_played = pos;

  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];

    if (sb->stereo) {
      pos *= 2;
    }

    if (sb->bps == 16) {
      pos *= 2;
    }

    sb_set_current_position(sb, pos);
  }

  return 1;
}

// These work in samples to make things easier in the long run
int win_llsSystem::GetSoundPos(int sound_uid) {
  int current_slot;
  uint32_t temp, pos;

  if (!m_f_sound_lib_init)
    return -1;
  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return -1;
  if (m_sound_mixer.m_sound_cache[current_slot].m_status == SSF_UNUSED)
    return -1;

  if (m_mixer_type != SOUND_MIXER_SOFTWARE_16) {
    sound_buffer_info *sb = &m_sound_mixer.m_sound_cache[current_slot];

    temp = sb_get_current_position(sb, &pos);

    if (sb->stereo) {
      pos /= 2;
    }
    if (sb->bps == 16) {
      pos /= 2;
    }

    // Updates the readable data
    m_sound_mixer.m_sound_cache[current_slot].play_info->m_samples_played = pos;

    return pos;
  } else {
    return m_sound_mixer.m_sound_cache[current_slot].play_info->m_samples_played;
  }

  return -1;
}

////////////////////////////////////////////////////////////////////////////////
bool win_llsSystem::CreateSoundBuffer(sound_buffer_info *sb, bool f_is_stereo, int size, bool dynamic) {
  // do buffer creation
  int buftype = sb->m_buffer_type;
  bool f_sample_16bit;
  int sound_length;

  get_sound_info(sb, &sound_length, &f_sample_16bit);

  if (size != -1) {
    sound_length = size;
  }

  switch (m_mixer_type) {
  case SOUND_MIXER_SOFTWARE_16:
    Int3();
    break;
  default:
    CreateDSBuffer(buftype, &sb->m_sound_buffer, &sb->m_sound_buffer_3d, sound_length, 22050, f_is_stereo,
                   f_sample_16bit);

    sb->m_lpksps = NULL;
    if (m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
      EAX_InitSource(sb->m_sound_buffer_3d, &sb->m_lpksps);
    }

    if (!sb->m_sound_buffer) {
      Int3();
      sb->m_status = SSF_UNUSED;
      return false;
    }
  }

  sb->m_mixer_type = m_mixer_type;
  sb->bps = f_sample_16bit ? 16 : 8;
  sb->stereo = f_is_stereo;

  if (sb->m_sound_index > -1) {
    SoundFiles[Sounds[sb->m_sound_index].sample_index].use_count++;
    //	Global_DS_alloced_sounds++;
  }

  return true;
}

bool win_llsSystem::LoadSoundBuffer(sound_buffer_info *sb) {
  // play 2d sound
  int buftype = sb->m_buffer_type;
  bool f_sample_16bit;
  char *sample_ptr;
  int sound_length;

  // get pointer
  sample_ptr = get_sound_info(sb, &sound_length, &f_sample_16bit);
  sb->sample_data = sample_ptr;
  sb->sample_length = (int)sound_length;

  // do buffer creation
  switch (m_mixer_type) {
  case SOUND_MIXER_SOFTWARE_16:
    Int3();
    break;
  default:
    if (LoadSoundData(sb->m_sound_buffer, sample_ptr, sound_length) != DS_OK) {
      Int3();
      sb->m_status = SSF_UNUSED;
      return false;
    }
  }

  return true;
}

bool win_llsSystem::PlaySoundBuffer(sound_buffer_info *sb, tPSBInfo *psb) {
  bool f_looping;

  if (!m_f_sound_lib_init)
    return false;
  if (!m_in_sound_frame)
    m_pending_actions = true;

TryPlayAgainLabel:
  if (psb) {
    if (sb->m_buffer_type == SBT_2D) {
      AdjustSound(sb->m_unique_id, psb->volume, psb->pan, psb->freq);
    } else if (sb->m_buffer_type == SBT_3D) {
      AdjustSound(sb->m_unique_id, psb->cur_pos, psb->volume, psb->reverb);
    }

    SetSoundPos(sb->m_unique_id, sb->play_info->m_samples_played);

    f_looping = psb->looping;
  } else {
    f_looping = ((sb->m_status & SSF_PLAY_LOOPING) || sb->s) ? true : false;
    if (f_looping && m_sound_mixer.m_loop_method == DSLOOP_BUFFER_METHOD && sb->s->loop_step != 0 &&
        (sb->m_status & SSF_BUFFERED_LOOP)) {
      f_looping = false;
    }
  }

  switch (m_mixer_type) {
  case SOUND_MIXER_SOFTWARE_16:
    Int3();
    break;

  default: {
    LPDIRECTSOUNDBUFFER sound_ptr = sb->m_sound_buffer;
    DWORD ds_flags = f_looping ? DSBPLAY_LOOPING : 0;

    ASSERT(sound_ptr);

    if (sound_ptr->Play(0, 0, ds_flags) == DSERR_BUFFERLOST) {
      if (LoadSoundData(sound_ptr, sb->sample_data, sb->sample_length) == DS_OK) {
        goto TryPlayAgainLabel;
      }

      sb->m_status = SSF_UNUSED;

      // Some type of error -- we cannot play the sound? -- get chris
      Int3();
      return false;
    }
  }
  }

  return true;
}

bool win_llsSystem::DuplicateSoundBuffer(sound_buffer_info *sb) {
  return false; // for now, let's not do this.
/*
  sound_buffer_info *source_sb = m_sound_mixer.FindSoundBuffer(sb->m_sound_index);

  ASSERT(m_mixer_type != SOUND_MIXER_SOFTWARE_16);

  if (!source_sb) {
    Int3();
    return false;
  }

  //	we have a source sound buffer.  let's use it.
  if (m_mixer_type == SOUND_MIXER_AUREAL) {
    sb->m_snd_obj = A3D_DuplicateSource(source_sb->m_snd_obj);
    if (!sb->m_snd_obj) {
      return false;
    }
  } else {
    HRESULT hr;
    hr = m_lp_ds->DuplicateSoundBuffer(source_sb->m_sound_buffer, &sb->m_sound_buffer);
    if (FAILED(hr)) {
      mprintf(0, "DDSNDLIB: Failed to duplicate sound buffer (%x)\n", hr);
      return false;
    }

    if (IS_3D_MIXER(m_mixer_type)) {
      // a 3d buffer needs a 3d interface pointer
      if (sb->m_buffer_type == SBT_3D) {
        hr = sb->m_sound_buffer->QueryInterface(IID_IDirectSound3DBuffer, (void **)&sb->m_sound_buffer_3d);
        if (FAILED(hr)) {
          mprintf(0, "DDSNDLIB: Failed to acquire 3d interface from duplicate buffer (%x)\n", hr);
          return false;
        }
      }
    }
  }

  sb->m_mixer_type = source_sb->m_mixer_type;
  sb->bps = source_sb->bps;
  sb->stereo = source_sb->stereo;
  sb->sample_data = source_sb->sample_data;
  sb->sample_length = source_sb->sample_length;

  // mprintf(0, "Duplicated!!\n");
  SoundFiles[Sounds[sb->m_sound_index].sample_index].use_count++;

  return true;
  */
}

// environmental sound interface
// volume modifier (0-1), damping(0-1), 1 = complete, 0 = none
//	decay 0.1 to 100 seconds, how long it takes for a sound to die.
bool win_llsSystem::SetGlobalReverbProperties(float volume, float damping, float decay) {
  if (m_mixer_type == SOUND_MIXER_CREATIVE_EAX) {
    return EAX_SetEnvironmentalReverb(volume, damping, decay);
  }

  return false;
}

sound_buffer_info *sound_buffer_cache::FindSoundBuffer(int sound_index) {
  int i;

  // is there's no use count for this soudn, then there should be no available buffer.
  if (SoundFiles[Sounds[sound_index].sample_index].use_count == 0) {
    return NULL;
  }

  // returns a sound buffer with the 'sound_index' if it is still active.
  // we can use the sound buffer to create duplicates.
  for (i = 0; i < m_max_sounds_played; i++) {
    sound_buffer_info *sb = &m_sound_cache[i];

    if (sb->m_status != SSF_UNUSED) {
      if (sb->m_sound_index == sound_index) {
        return sb;
      }
    }
  }

  return NULL;
}

// set special parameters for the 3d environment.
// of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
void win_llsSystem::SetEnvironmentValues(const t3dEnvironmentValues *env) {
  if (CHECK_FLAG(env->flags, ENV3DVALF_DOPPLER)) {
    Env3dValues.doppler_scalar = env->doppler_scalar;
  }
}

// get special parameters for the 3d environment.
// of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
void win_llsSystem::GetEnvironmentValues(t3dEnvironmentValues *env) {
  if (CHECK_FLAG(env->flags, ENV3DVALF_DOPPLER)) {
    env->doppler_scalar = Env3dValues.doppler_scalar;
  }
}

// enable special parameters for the 3d environment.
// of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
void win_llsSystem::SetEnvironmentToggles(const t3dEnvironmentToggles *env) {
  t3dEnvironmentValues values;

  if (CHECK_FLAG(env->flags, ENV3DVALF_DOPPLER)) {
    // set toggle then set doppler again.
    Env3dToggles.doppler = env->doppler;
    values.flags = ENV3DVALF_DOPPLER;
    values.doppler_scalar = Env3dValues.doppler_scalar;
    SetEnvironmentValues(&Env3dValues);
  }
  if (CHECK_FLAG(env->flags, ENV3DVALF_GEOMETRY)) {
    // initialize geometry object if available and true.
    if (m_geometry) {
      delete m_geometry;
    }
    m_geometry = NULL;
    Env3dToggles.geometry = m_geometry ? true : false;
  }
}

// get states of special parameters for the 3d environment.
// of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
void win_llsSystem::GetEnvironmentToggles(t3dEnvironmentToggles *env) {
  if (CHECK_FLAG(env->flags, ENV3DVALF_DOPPLER)) {
    env->doppler = Env3dToggles.doppler;
  }

  env->supported = 0;
}

// Sound System Error Handler.
void win_llsSystem::CheckForErrors() {
  // if a fatal error occurred, quit and display an error
  // non fatal errors should be put inside a logfile, or just mprinted out.
  switch (m_lib_error_code) {
  case SSL_ERROR_SAMPLE_NODATA:
    Error("%s\nSample had no data.", m_error_text);
    break;

  case SSL_ERROR_STREAMMIXER:
    Error("%s\nMixer alignment check failed.", m_error_text);
    break;

  case SSL_ERROR_GENERIC:
    Error("%s\nGeneric error.", m_error_text);
    break;
  }

  // must call!
  llsSystem::CheckForErrors();

  // add our default error string.
  char buf[8];
  sprintf(buf, "mix:%d\n", m_mixer_type);
  strcat(m_error_text, buf);
}

/////////////////////////////////////////////////////////////////////////////////////
// set auxillary 3d sound properties
bool win_llsSystem::SoundPropertySupport() const {
  switch (m_mixer_type) {
  case SOUND_MIXER_CREATIVE_EAX:
    if (EAX_Caps() & EAXF_SOURCE_OBSTRUCTION) {
      return true;
    }
    break;
  }

  return false;
}

// sound obstruction from 0 to 1.0 (1.0  = fully obstructed)
void win_llsSystem::SetSoundProperties(int sound_uid, float obstruction) {
  sound_buffer_info *sb;
  int current_slot;

  if (!m_f_sound_lib_init)
    return;

  if ((current_slot = ValidateUniqueId(sound_uid)) == -1)
    return;

  sb = &m_sound_mixer.m_sound_cache[current_slot];

  switch (m_mixer_type) {
  case SOUND_MIXER_CREATIVE_EAX:
    EAX_SetSourceProperties(sb->m_lpksps, obstruction);
    break;
  }
}
