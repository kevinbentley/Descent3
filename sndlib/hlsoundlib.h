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

 * $Logfile: /DescentIII/Main/lib/hlsoundlib.h $
 * $Revision: 47 $
 * $Date: 3/20/00 12:26p $
 * $Author: Matt $
 *
 * Descent III Device-independant sound library
 *
 * $Log: /DescentIII/Main/lib/hlsoundlib.h $
 *
 * 47    3/20/00 12:26p Matt
 * Merge of Duane's post-1.3 changes.
 * Lower MAX_SOUND_OBJECTS for Mac (Mac only)
 *
 * 46    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 45    5/10/99 10:53p Ardussi
 * changes to compile on Mac
 *
 * 44    4/27/99 2:10p Samir
 * added code to set the desired sound card given the descriptive name of
 * a sound card.
 *
 * 43    4/12/99 7:14p Samir
 * prioritization code added.
 *
 * 42    4/11/99 2:17p Chris
 * Made max sounds 3000 DAMN!
 *
 * 41    4/10/99 5:09p Samir
 * beginning to add prioritization of sounds code.  currently non
 * functional, but allows me to change all calls to Play3dSound so that I
 * can test later.
 *
 * 40    4/01/99 6:37p Chris
 *
 * 39    4/01/99 6:37p Chris
 * Increased max sound objects
 *
 * 38    4/01/99 4:28p Samir
 * hardware geometry integration if it's available.
 *
 * 37    2/21/99 5:48p Matt
 * Added SetVolumeObject()
 *
 * 36    1/30/99 3:44p Chris
 * Added support for time-offset'ed 3d sounds (like start at 1.2 seconds
 * into the sound)
 *
 * 35    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 34    1/26/99 5:16p Matt
 * Added StopObjectSound()
 *
 * 33    1/12/99 4:04p Samir
 * added environmental audio on a per room basis.
 *
 * 32    1/08/99 6:31p Samir
 * added reverb
 *
 * 31    1/08/99 5:37p Samir
 * reverb values per room.
 *
 * 30    11/16/98 4:29p Chris
 * Added pause new flag to the high level system
 *
 * 29    11/13/98 2:27p Samir
 * moved music stuff to d3music.h
 *
 * 28    10/16/98 5:42p Chris
 *
 * 27    8/18/98 12:17p Chris
 * f_in_game for begin sound frame (to do 3d processing)
 *
 * 26    8/10/98 5:52p Samir
 * added tension levels for music.
 *
 * 25    7/28/98 5:41p Samir
 * change some music system protos.
 *
 * 24    7/24/98 5:26p Samir
 * added some D3 music functions.
 *
 * 23    7/09/98 8:34p Samir
 * added argument to callback for streams.
 *
 * 22    6/29/98 9:29a Chris
 * Added some support for Direct Sound 3d
 *
 * 21    6/24/98 12:09p Chris
 * Update
 *
 * 20    6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 19    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 18    6/17/98 7:04p Chris
 * Added support for 8bit stream data to be played by our 16bit sound
 * mixer
 *
 * 17    6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 16    3/20/98 2:59p Chris
 * Added a wall hit sound for the player and added support for a base
 * volume for 3d sounds
 *
 * 15    2/27/98 5:31p Chris
 * Changed how master_volume is set.
 *
 * 14    2/23/98 6:32p Chris
 * Added support for a hlsoundlib unique id.  This is what all the public
 * functions use.  Also, looping sounds are now correctly turned off and
 * on.
 *
 * 13    2/15/98 6:41p Chris
 * Added Update2dSound
 *
 * 12    2/13/98 5:15p Chris
 * Fixed multiple problems with looping sounds not being able to be
 * stopped
 *
 * 11    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 10    1/13/98 5:08p Chris
 * Increased sound object limit
 *
 * 9     1/06/98 2:12p Chris
 * Added muffled sounds v.1 and made 3d sounds keep their roomnum.
 *
 * 8     1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 7     12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 6     12/30/97 2:15p Chris
 * Adding further support for software 3d stuff
 *
 * 5     12/12/97 11:43a Chris
 * Added support to toggle sndlib on/off
 *
 * 4     12/11/97 12:58p Chris
 * Added support for fixed 3d position updating sounds.
 *
 * 3     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 2     11/21/97 1:10p Chris
 * Incremental Improvements
 *
 * 20    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 19    5/22/97 6:18p Chris
 *
 * 18    5/22/97 5:15p Chris
 *
 * 17    5/15/97 1:59a Chris
 *
 * 16    4/29/97 8:03a Chris
 * Improved the sound code.  High-level sound now
 * fully uses the flags in the sound page and it
 * resulted in a simpilier coding interface  :)
 *
 * 15    4/28/97 11:21a Chris
 * Incremental improvements is the sound system
 *
 * 14    4/24/97 3:25a Chris
 * // Added some more support for 3d sounds
 *
 * 13    4/03/97 8:37p Chris
 * Added the Main_OS object pass in the sound library
 * initialization code.
 *
 * 12    3/15/97 1:34p Chris
 *
 * $NoKeywords: $
 */

#ifndef __HLSOUNDLIB_H__
#define __HLSOUNDLIB_H__

#include "ssl_lib.h"
#include "object.h"

//////////////////////////////////////////////////////////////////////////

#define MAX_SOUNDS_MIXED 40
#define MIN_SOUNDS_MIXED 20
#define MAX_SOUND_OBJECTS 3000

extern char Sound_quality;
extern char Sound_mixer;
extern char Sound_card_name[];

class sound_object {
public:
  sound_object() { m_obj_type_flags = SIF_UNUSED; }

public:
  uint32_t m_obj_type_flags;
  int m_sound_uid;
  int m_sound_index;
  int m_hlsound_uid;

  play_information play_info;

  float volume_3d; // Used so that 3d sounds can have a base volume (for 2d this is in play_information)

  union {
    struct {
      int segnum; // Use physics' bit-bit stuff (inside/outside)
      vector pos;
      matrix orient; // only need pitch and heading -- not roll (sound cones are symetrical)
    } pos_info;

    int object_handle;
  } m_link_info;
};

class hlsSystem {
  int m_f_hls_system_init;

  class sound_object m_sound_objects[MAX_SOUND_OBJECTS];

  float m_master_volume;
  int m_sounds_played;

  bool m_pause_new;
  uint8_t m_cur_environment; // current environment being played.
  int n_lls_sounds;        // number of sounds that we want the low level mixer to mix.

  bool Emulate3dSound(int sound_obj_index);
  bool ComputePlayInfo(int sound_obj_index, vector *virtual_pos, vector *virtual_vel, float *adjusted_volume);

  inline int MakeUniqueId(int sound_obj_index);
  inline int ValidateUniqueId(int hl_sound_uid);

  // Forcefully ends a sound
  void StopSound(int sound_obj_index, uint8_t f_immediately = SKT_STOP_IMMEDIATELY);

private:
  int Play3dSound(int sound_index, pos_state *cur_pos, object *cur_obj, int priority, float volume, int flags,
                  float offset = 0.0);

public:
  // Include a lowel-level sound system
  class llsSystem *m_ll_sound_ptr;

  hlsSystem(); // {m_f_hls_system_init = 0; m_sounds_played=0; m_master_volume = 1.0; m_pause_new = false;}
  ~hlsSystem() { KillSoundLib(true); }

  bool IsActive(void);

  // Start and clean-up after the sound library
  int InitSoundLib(char mixer_type, char quality, bool f_kill_sound_lib = false);
  void KillSoundLib(bool f_kill_sound_list);
  void SetLLSoundQuantity(int n_sounds);
  int GetLLSoundQuantity();

  bool SetLLevelType(); // These are

  // Pause and Resume the library
  void PauseSounds(bool f_all_sounds = false);
  void ResumeSounds();
  void StopAllSounds();

  // Code for the beginning and ending of a frame of action

  // Begin_sound_frame(listener pos/orient/velocity)
  // SyncSounds
  // Do sound pos updates -- IF VOLUME IS LOW AND NOT FOREVER, THEN STOP SOUND
  // compute echo / reverb
  // indirect/direct path sounds
  void BeginSoundFrame(bool f_in_game = true);

  // Plays the deffered 3d stuff
  void EndSoundFrame();

  // Functions that play a sound

  // 3d functions (we use the sound flags in the page to determine all the cool stuff)
  // Functions that play a 3d sound -- includes the 2d emulation of 3d sound
  int Play3dSound(int sound_index, pos_state *cur_pos, float volume = MAX_GAME_VOLUME, int flags = 0,
                  float offset = 0.0);
  int Play3dSound(int sound_index, object *cur_obj, float volume = MAX_GAME_VOLUME, int flags = 0, float offset = 0.0);

  int Play3dSound(int sound_index, int priority, pos_state *cur_pos, float volume = MAX_GAME_VOLUME, int flags = 0,
                  float offset = 0.0);
  int Play3dSound(int sound_index, int priority, object *cur_obj, float volume = MAX_GAME_VOLUME, int flags = 0,
                  float offset = 0.0);

  int PlayStream(int unique_handle, void *data, int size, int stream_format, float volume,
                 void *stream_callback(void *user_data, int handle, int *size) = NULL);

  // 2d functions
  int Play2dSound(int sound_index, float volume = MAX_GAME_VOLUME / 2, float pan = 0.0,
                  uint16_t frequency = 22050);

  int Play2dSound(int sound_index, int priority, float volume = MAX_GAME_VOLUME / 2, float pan = 0.0,
                  uint16_t frequency = 22050);

  int Update2dSound(int hlsound_uid, float volume, float pan);

  // Do nice looping stop stuff
  void StopSoundLooping(int hlsound_uid);
  void StopSoundImmediate(int hlsound_uid);

  // Stop all sounds attached to an object
  void StopObjectSound(int objhandle);

  // Set the volume for all the sounds attached to an object
  void SetVolumeObject(int objhandle, float volume);

  // Master volume controls for sound effects
  void SetMasterVolume(float volume);
  float GetMasterVolume();

  // Queued sound functions
  void Add2dSoundQueued(int q_num, int sound_index, float volume, float pan, uint16_t frequency);
  void KillQueue(int q_num = 0);
  void KillAllQueues();

  bool CheckAndForceSoundDataAlloc(int sound_file_index);
  bool SetSoundQuality(char quality);
  char GetSoundQuality(void);
  bool SetSoundMixer(char mixer_type);
  char GetSoundMixer(void);

  bool IsSoundPlaying(int hlsound_uid);

  // Midi play stuff
  void SetMidiVolume();
  void GetMidiVolume();
  void PlayMidi();
  void StopMidi();
  void PauseMidi();
  void ResumeMidi();
};

extern hlsSystem Sound_system;

//////////////////////////////////////////////////////////////////////////
//	ENVIRONMENTAL REVERB PRESETS

#define N_ENVAUDIO_PRESETS 26

#define ENVAUD_PRESET_NONE 0
#define ENVAUD_PRESET_PADDEDCELL 1
#define ENVAUD_PRESET_ROOM 2
#define ENVAUD_PRESET_BATHROOM 3
#define ENVAUD_PRESET_LIVINGROOM 4
#define ENVAUD_PRESET_STONEROOM 5
#define ENVAUD_PRESET_AUDITORIUM 6
#define ENVAUD_PRESET_CONCERTHALL 7
#define ENVAUD_PRESET_CAVE 8
#define ENVAUD_PRESET_ARENA 9
#define ENVAUD_PRESET_HANGAR 10
#define ENVAUD_PRESET_CARPETEDHALLWAY 11
#define ENVAUD_PRESET_HALLWAY 12
#define ENVAUD_PRESET_STONECORRIDOR 13
#define ENVAUD_PRESET_ALLEY 14
#define ENVAUD_PRESET_FOREST 15
#define ENVAUD_PRESET_CITY 16
#define ENVAUD_PRESET_MOUNTAINS 17
#define ENVAUD_PRESET_QUARRY 18
#define ENVAUD_PRESET_PLAIN 19
#define ENVAUD_PRESET_PARKINGLOT 20
#define ENVAUD_PRESET_SEWERPIPE 21
#define ENVAUD_PRESET_UNDERWATER 22
#define ENVAUD_PRESET_DRUGGED 23
#define ENVAUD_PRESET_DIZZY 24
#define ENVAUD_PRESET_PSYCHOTIC 25

#endif
