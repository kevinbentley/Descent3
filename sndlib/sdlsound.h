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
*/

#ifndef __LINUX_DD_SOUND_H_
#define __LINUX_DD_SOUND_H_

#include <SDL_audio.h>

#include "ssl_lib.h"
#include "mixer.h"

class sound_buffer_info;

void lnxsound_SetError(int code);
void lnxsound_ErrorText(const char *fmt, ...);
inline void sb_adjust_properties_2d(sound_buffer_info *sb, float f_volume, float f_pan, uint16_t frequency);

class emulated_listener {
public:
  matrix orient;
  vector position;
  vector velocity;
};

class lnxsound : public llsSystem {
  // Public functions
public:
  lnxsound();
  ~lnxsound();

  // may be called before init (must be to be valid, the card passed here will be initialized in InitSoundLib)
  void SetSoundCard(const char *name) override;
  void PauseSound(int sound_uid) override;
  void ResumeSound(int sound_uid) override;
  // set special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  void SetEnvironmentValues(const t3dEnvironmentValues *env) override;

  // get special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  void GetEnvironmentValues(t3dEnvironmentValues *env) override;

  // enable special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  void SetEnvironmentToggles(const t3dEnvironmentToggles *env) override;

  // get states of special parameters for the 3d environment.
  // of strcuture passed, you must set the appropriate 'flags' value for values you wish to modify
  void GetEnvironmentToggles(t3dEnvironmentToggles *env) override;

  // Starts the sound library, maybe have it send back some information -- 3d support?
  int InitSoundLib(char mixer_type, uint8_t max_sounds_played) override;
  // Cleans up after the Sound Library
  void DestroySoundLib() override;

  // Locks and unlocks sounds (used when changing play_info data)
  bool LockSound(int sound_uid) override;
  bool UnlockSound(int sound_uid) override;

  bool SetSoundQuality(char quality) override;
  char GetSoundQuality() override;
  bool SetSoundMixer(char mixer_type) override;
  char GetSoundMixer() override;

  // Plays a 2d sound
  int PlaySound2d(play_information *play_info, int sound_index, float volume, float pan, bool f_looped) override;
  int PlayStream(play_information *play_info) override;

  void SetListener(pos_state *cur_pos) override;
  int PlaySound3d(play_information *play_info, int sound_index, pos_state *cur_pos, float master_volume,
                          bool f_looped, float reverb = 0.5f) override;
  void AdjustSound(int sound_uid, float f_volume, float f_pan, uint16_t frequency) override;
  void AdjustSound(int sound_uid, pos_state *cur_pos, float adjusted_volume, float reverb = 0.5f) override;

  void StopAllSounds() override;

  // Checks if a sound is playing (removes finished sound);
  bool IsSoundInstancePlaying(int sound_uid) override;
  int IsSoundPlaying(int sound_index) override;

  //	virtual void AdjustSound(int sound_uid, play_information *play_info) = 0;

  // Stops 2d and 3d sounds
  void StopSound(int sound_uid, uint8_t f_immediately = SKT_STOP_IMMEDIATELY) override;

  // Pause all sounds/resume all sounds
  void PauseSounds() override;
  void ResumeSounds() override;
  bool CheckAndForceSoundDataAlloc(int sound_file_index) override;

  // Begin sound frame
  void SoundStartFrame() override;

  // End sound frame
  void SoundEndFrame() override;

  // returns the error string.
  virtual const char *GetErrorStr() const;

  // environmental sound interface
  // volume modifier (0-1), damping(0-1), 1 = complete, 0 = none
  //	decay 0.1 to 100 seconds, how long it takes for a sound to die.
  bool SetGlobalReverbProperties(float volume, float damping, float decay) override;

  bool GetDeviceSettings(SDL_AudioDeviceID *sound_device, uint32_t *freq, uint32_t *bit_depth,
                                 uint32_t *channels) const;

  friend void lnxsound_SetError(int code);
  friend void lnxsound_ErrorText(const char *fmt, ...);
  friend inline void sb_adjust_properties_2d(sound_buffer_info *sb, float f_volume, float f_pan, uint16_t frequency);

protected:
#ifdef _DEBUG
  int16_t FindFreeSoundSlot(int sound_index, float volume, int priority);
#else
  int16_t FindFreeSoundSlot(float volume, int priority);
#endif
  // This function limits the number of sounds cached to 255(8bits) and 256 bit is for invalid channel
  // The purpose is to create unique signatures for each sound played (and allow for
  // the slot_number to be quickly determined)
  inline int MakeUniqueId(int sound_slot) const;
  static inline int ValidateUniqueId(int sound_uid);

  // Sound System Error Handler.
  void CheckForErrors() override;

  void StartStreaming();
  void EndStreaming();

  int m_primary_frequency; // Set to the primary buffers frequency -- cmphack
  int m_primary_alignment;

  SDL_AudioDeviceID sound_device;
  bool in_at_exit;
  bool m_in_sound_frame;
  bool m_pending_actions;
  char m_sound_quality;
  float m_cache_stress_timer;
  float m_timer_last_frametime;

  int m_total_sounds_played;
  int m_cur_sounds_played;

  emulated_listener m_emulated_listener;

  // Sam 6/29 - Added support for SDL
  software_mixer m_mixer;
};

#endif
