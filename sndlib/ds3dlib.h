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

 * $Logfile: /DescentIII/Main/lib/ds3dlib.h $
 * $Revision: 49 $
 * $Date: 8/23/99 5:29p $
 * $Author: Samir $
 *
 * Low-level library for 3d sound
 *
 * $Log: /DescentIII/Main/lib/ds3dlib.h $
 *
 * 49    8/23/99 5:29p Samir
 * incremental EAX 2.0 checkin
 *
 * 48    5/03/99 3:12a Samir
 * fixed up aureal so it works (a little slow though...)
 *
 * 47    4/29/99 3:01p Samir
 * added code for direct sound mixers only (and function for Aureal
 * really) that will use direct sound looping for simple loops.
 *
 * 46    4/27/99 2:10p Samir
 * added code to set the desired sound card given the descriptive name of
 * a sound card.
 *
 * 45    4/23/99 7:51p Samir
 * looping fixes for directsound.
 *
 * 44    4/22/99 10:33p Samir
 * modifications so that DirectSound mixers use one thread for all looping
 * and streaming sounds.   It worked without crashing for about twenty
 * minutes of playing from level 1 to level 2 of D3.  We'll see.
 *
 * 43    4/13/99 4:09p Samir
 * more priority stuff.
 *
 * 42    4/12/99 7:14p Samir
 * prioritization code added.
 *
 * 41    4/10/99 5:08p Samir
 * took out obsolete data from play_information structure that should save
 * around 70 bytes per instance.
 *
 * 40    4/09/99 12:03p Samir
 * took out windows.h again, this time made HWND a void pointer, and
 * checked under both editor and main projects.
 *
 * 39    4/07/99 12:38a 3dsmax
 * Misc changes to allow editor build, as per Samir's phone instructions.
 * Will this break the game build?  Who knows?  (Matt, ChrisP)
 *
 * 38    4/06/99 8:29p Samir
 * added error check system.
 *
 * 37    3/29/99 11:01a Samir
 * added ability to change 3d environment.
 *
 * 36    3/17/99 4:20p Samir
 * added functions to pause and resume individual sounds.
 *
 * 35    2/19/99 5:21p Kevin
 * Fixed some connection DLLs and a Direct Sound bug with threads.
 *
 * 34    1/14/99 6:10p Samir
 * added DirectSound buffer duplication code.
 *
 * 33    1/11/99 5:51p Samir
 * reverb on the buffer level.
 *
 * 32    1/08/99 6:31p Samir
 * added reverb
 *
 * 31    1/08/99 11:36a Samir
 * implemented basic Aureal 2.0 support.
 *
 * 30    12/23/98 11:49a Samir
 * reorganized code so it works with different APIs.
 *
 * 29    7/08/98 12:09p Samir
 * use C RTL for thread creation.
 *
 * 28    7/06/98 1:48p Samir
 * added A3d support.
 *
 * 27    6/29/98 4:15p Chris
 * Streaming audio works
 *
 * 26    6/29/98 9:29a Chris
 * Added some support for Direct Sound 3d
 *
 * 25    6/25/98 11:28a Chris
 * Added some DS3d support
 *
 * 24    6/24/98 6:43p Chris
 * Furthered the endless work on the sound system
 *
 * 23    6/24/98 4:39p Chris
 * Improved the multiple mixer support
 *
 * 22    6/24/98 11:31a Chris
 * Fixed an ordering bug
 *
 * 21    6/24/98 11:14a Chris
 * Added more support and bug fixes
 *
 * 20    6/24/98 1:07a Chris
 * Intermediate checkin
 *
 * 19    6/23/98 6:00p Chris
 * DirectSound 16 mixer is active with 8 bit samples
 *
 * 18    6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 17    6/19/98 3:09p Chris
 * Improved IsSoundPlaying
 *
 * 16    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 15    6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 14    2/26/98 5:11p Chris
 * Removed a unused data element from the llsoundlib
 *
 * 13    2/26/98 3:08p Chris
 * More NT stuff
 *
 * 12    2/25/98 3:19p Jeff
 * more NT fixes
 *
 * 11    2/25/98 2:47p Jeff
 * CHRIS:  Added some NT support for sound code.  It is pretty hokey right
 * now.
 *
 * 10    2/25/98 12:13p Chris
 * NT support?  Not sure...  I do not have the Editor in NT.
 *
 * 9     2/15/98 7:12p Chris
 * More improvements to the sound lib
 *
 * 8     1/23/98 4:21p Chris
 * Changed the low-level sound code from multimedia timers to a thread
 * that sleeps();
 *
 * 7     1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 6     12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 5     12/22/97 6:19p Chris
 * Working on new mixer functionality
 *
 * 4     12/19/97 4:08p Chris
 * New dynamically loading sounds
 *
 * 3     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 2     11/21/97 1:10p Chris
 * Incremental Improvements
 *
 * 18    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 17    5/22/97 5:15p Chris
 *
 * 16    4/29/97 7:26a Chris
 * Improved the sound code.  It is healthy.
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
 * 12    4/01/97 10:00a Chris
 *
 * 11    3/17/97 5:12p Chris
 * Allowed new sound code to be demo'ed.
 *
 * 10    3/14/97 12:10p Chris
 * Made a nice C++ abstract type for the low-level.  It should make the
 * MacMan very joyful.  :)
 *
 * 9     2/07/97 5:48p Matt
 * Renamed vector.h to vecmat.h to fix DevStudio problem
 *
 * $NoKeywords: $
 */

#ifndef __ds3dlib_h__
#define __ds3dlib_h__

#include <windows.h>
// #include <mmsystem.h>		// Multi-media system support
// #include "dsound.h"			// Direct sound header file

#include "ssl_lib.h" // Shared sound header (between high and low-levels)
#include "vecmat.h"

#ifndef DS3DLIB_INTERNAL_H
typedef void *LPDIRECTSOUND;
typedef void *LPDIRECTSOUNDBUFFER;
typedef void *LPDIRECTSOUND3DLISTENER;
typedef void *LPDIRECTSOUND3DBUFFER;
typedef void *LPDIRECTSOUNDCAPTURE;
typedef void *LPDIRECTSOUNDCAPTUREBUFFER;
typedef void *LPDIRECTSOUNDNOTIFY;
// typedef void *HWND;
class sound_buffer_info;
struct tPSBInfo;
#endif

// Sound cache list
class sound_buffer_cache {
public:
  class sound_buffer_info *m_sound_cache; // List of all sounds current sounds
  uint16_t m_max_sounds_played;     // Maximum sounds played at any given moment
  uint16_t m_cur_sounds_played;     // Current number of sounds playing
  unsigned m_loop_method;                 // what method do we do looping sounds (direct sound only)

public:
  sound_buffer_info *FindSoundBuffer(int sound_index);
};

class emulated_listener {
public:
  matrix orient;
  vector position;
  vector velocity;
};

// Sound library object

// Commonly passed arguments:
//	sound_index  -- index of a particular sample in the SoundArray
//	sound_uid    -- unique id of a particular sound being played
// sound_slot   -- "channel" that a sample is being played on (derivable from sound_uid)

class win_llsSystem : public llsSystem {
private:
  // Windows and Direct Sound information
  LPDIRECTSOUND m_lp_ds; // pointer to direct sound object
  void *m_hwnd_main;     // Handle to main window -- needed for direct sound

  // For DS3D
  LPDIRECTSOUND3DLISTENER m_lp_listener;

  // For 3d sounds and non-3D mixers
  emulated_listener m_emulated_listener;

  // For DS and DS3d mixers
  void LoopStartStreaming(sound_buffer_info *sb, int buffer_type, float volume, float pan, pos_state *cur_pos);
  void DSStartStreaming(sound_buffer_info *sb, float volume, float pan);

  friend void __cdecl LoopStreamTimer(void *user_ptr);

  // Creates a sound buffer
  HRESULT CreateDSBuffer(int buffer_type, LPDIRECTSOUNDBUFFER *lp_lp_dsb, LPDIRECTSOUND3DBUFFER *lp_lp_dsb_3d,
                      DWORD sound_bytes, DWORD frequency, bool f_is_stereo, bool f_is_16_bit);

  // Finds a free slot for a new sound, slot_uid is an SBID_xxx value.
#ifdef _DEBUG
  int16_t FindFreeSoundSlot(int sound_index, float volume, int priority);
#else
  int16_t FindFreeSoundSlot(float volume, int priority);
#endif

  // updates a directsound buffer
  void update_directsound_sb(sound_buffer_info *sb, bool update_looping = false);

  // used to clean up direct sound buffer stuff
  void cleanup_directsound_looping_sb(sound_buffer_info *sb);

  // Makes a unique sound id from a sound slot number
  inline int MakeUniqueId(int sound_slot);
  // Validates and converts a unique sound id to a sound slot number
  inline int ValidateUniqueId(int sound_uid);

  friend void StreamMixer(char *ptr, int len);
  friend void StreamFill(int start_byte, int num_bytes);
  friend void __cdecl StreamTimer(void *user_ptr);

  bool StartDSCleaner(void);
  friend void __cdecl DSCleanerThread(void *user_ptr);

  bool StartStreaming(void);

private:
  // Total samples played since start of library
  uint16_t m_total_sounds_played; // Used for unique ids and for stats

  // Sound library status
  uint8_t m_f_sound_lib_init;   // Flag is set if sound library is initialized	-- cmphack
  uint8_t m_f_sound_lib_status; // Paused or running							--
                                      // cmphack

  // May not need some of these
  int m_primary_frequency; // Set to the primary buffers frequency -- cmphack
  int m_primary_alignment;
  int m_current_frequency; //                   					-- cmphack

  uint8_t m_primary_bit_depth; // 16 or 8 bits per sample				-- cmphack
  char m_sound_quality;

  // muted looped sound system
  int64_t m_timer_last_frametime;
  float m_cache_stress_timer;

// clean interface
#ifdef DS3DLIB_INTERNAL_H // following data is available to internal functions
public:
#else
private:
#endif
  bool CreateSoundBuffer(sound_buffer_info *sb, bool f_is_stereo, int size = -1, bool dynamic = false);
  bool LoadSoundBuffer(sound_buffer_info *sb);
  bool PlaySoundBuffer(sound_buffer_info *sb, tPSBInfo *psb);
  bool DuplicateSoundBuffer(sound_buffer_info *sb);

  bool m_in_sound_frame;
  bool m_pending_actions; // are there sound events pending (outside of of start/end)
  char m_mixer_type;

  // Public functions
public:
  // Initializes the object, but does not activate the sound library
  win_llsSystem(void);
  // Destructor -- calls the cleanup code.
  ~win_llsSystem(void);

  // Starts the sound library
  virtual int InitSoundLib(char mixer_type, uint8_t max_sounds_played);

  // Cleans up after the Sound Library
  virtual void DestroySoundLib(void);

public: // only for win32 instances
  int SetSoundPos(int sound_uid, int pos);
  int GetSoundPos(int sound_uid);

public:
  // reserve sound slots., returns an ID to this slot.

  virtual void SetSoundCard(const char *name);

  virtual void SetListener(pos_state *cur_pos);
  virtual int PlaySound3d(play_information *play_info, int sound_index, pos_state *cur_pos, float master_volume,
                          bool f_looped, float reverb = 0.5f); //, uint16_t frequency)
  virtual void AdjustSound(int sound_uid, float f_volume, float f_pan, uint16_t frequency);
  virtual void AdjustSound(int sound_uid, pos_state *cur_pos, float adjusted_volume, float reverb = 0.5f);

  // Sample cache and list of samples
  class sound_buffer_cache m_sound_mixer; // Lists all stored samples (playing, cached, or unused)

  // Plays a 2d sound
  virtual int PlaySound2d(play_information *play_info, int sound_index, float volume, float pan, bool f_looped = false);
  virtual int PlayStream(play_information *play_info);
  virtual void StopAllSounds(void);

  virtual bool SetSoundQuality(char quality);
  virtual char GetSoundQuality(void);

  virtual bool SetSoundMixer(char mixer_type);
  virtual char GetSoundMixer(void);

  // Checks if a sound is playing
  virtual bool IsSoundInstancePlaying(int sound_uid);
  virtual int IsSoundPlaying(int sound_index);

  // Locks and unlocks sounds (used when changing play_info data)
  virtual bool LockSound(int sound_uid);
  virtual bool UnlockSound(int sound_uid);

  // Stops 2d and 3d sounds
  virtual void StopSound(int sound_uid, uint8_t f_immediately = SKT_STOP_IMMEDIATELY);

  // Pause all sounds/resume all sounds
  virtual void PauseSounds(void);
  virtual void ResumeSounds(void);
  virtual void PauseSound(int sound_uid);
  virtual void ResumeSound(int sound_uid);

  // Loads the actual sound data into memory
  virtual bool CheckAndForceSoundDataAlloc(int sound_file_index);

  // Begin sound frame
  virtual void SoundStartFrame(void);

  // End sound frame
  virtual void SoundEndFrame(void);

  // environmental sound interface
  // volume modifier (0-1), damping(0-1), 1 = complete, 0 = none
  //	decay 0.1 to 100 seconds, how long it takes for a sound to die.
  virtual bool SetGlobalReverbProperties(float volume, float damping, float decay);

  // set special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void SetEnvironmentValues(const t3dEnvironmentValues *env);

  // get special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void GetEnvironmentValues(t3dEnvironmentValues *env);

  // enable special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void SetEnvironmentToggles(const t3dEnvironmentToggles *env);

  // get states of special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  virtual void GetEnvironmentToggles(t3dEnvironmentToggles *env);

protected:
  virtual void CheckForErrors(); // part of sound system error handler.

  /////////////////////////////////////////////////////////////////////////////////
public:
  // set auxillary 3d sound properties
  virtual bool SoundPropertySupport() const;

  // sound obstruction from 0 to 1.0 (1.0  = fully obstructed)
  virtual void SetSoundProperties(int sound_uid, float obstruction);
};

#endif
