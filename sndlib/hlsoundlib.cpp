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

 * $Logfile: /DescentIII/Main/sndlib/hlsoundlib.cpp $
 * $Revision: 116 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * High level sound library for Descent 3
 *
 * $Log: /DescentIII/Main/sndlib/hlsoundlib.cpp $
 *
 * 116   4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 115   3/20/00 12:30p Matt
 * Merge of Duane's post-1.3 changes.
 * Optimizations.
 * A bunch of 3D sound code ifdef'd out for Mac.
 *
 * 114   2/09/00 4:59p Jason
 * fixed access violation in VerifyUniqueID
 *
 * 113   10/22/99 10:40p Jeff
 * commented out an mprintf put in by mac merge
 *
 * 112   10/21/99 3:27p Kevin
 * Mac merge!
 *
 * 111   8/23/99 5:29p Samir
 * incremental EAX 2.0 checkin
 *
 * 110   8/19/99 7:10p Jeff
 * hooked in linux sound lib
 *
 * 109   8/13/99 2:00p Samir
 * more aureal and geometry fixes.
 *
 * 108   8/11/99 3:12p Samir
 * fixes for aureal support.
 *
 * 107   7/28/99 2:05p Kevin
 * Macintosh Changes
 *
 * 106   5/07/99 1:32p Jeff
 * kill a sound if the object is ghosted (aka OBJ_DUMMY)
 *
 * 105   4/27/99 2:10p Samir
 * added code to set the desired sound card given the descriptive name of
 * a sound card.
 *
 * 104   4/23/99 7:50p Samir
 * looping fixes for directsound.
 *
 * 103   4/14/99 1:46a Jeff
 * fixed case mismatched #includes
 *
 * 102   4/12/99 7:14p Samir
 * prioritization code added.
 *
 * 101   4/10/99 5:09p Samir
 * beginning to add prioritization of sounds code.  currently non
 * functional, but allows me to change all calls to Play3dSound so that I
 * can test later.
 *
 * 100   4/06/99 8:31p Samir
 * moved free memory code to low level library.
 *
 * 99    4/03/99 6:24p Nate
 * ? Fixed a editor sound crash ?
 *
 * 98    4/01/99 4:28p Samir
 * hardware geometry integration if it's available.
 *
 * 97    4/01/99 11:57a Chris
 * Made the holy cow messed print the name of the sound that couldn't be
 * played
 *
 * 96    3/03/99 5:07p Samir
 * music volume will shutoff music if 0, restart if greater only after a
 * change in vollume.
 *
 * 95    3/03/99 5:44a Chris
 * Sound is based on the viewer_object
 *
 * 94    2/24/99 12:27p Chris
 * Fixed problems with GB finding robots/room he couldn't get to.  Fixed
 * problems with forcefields(sound prop. and path finding).  Fixed
 * problems with small portals.
 *
 * 93    2/21/99 5:48p Matt
 * Added SetVolumeObject()
 *
 * 92    2/16/99 3:38p Chris
 * FIXED:  Ship sounds being all messed up.  :)  (3d dist = 0) So, use the
 * rvec...  So, sounds could get muffled
 *
 * 91    2/14/99 3:27p Chris
 * FIxed a load/save bug... hehe
 *
 * 90    2/12/99 2:10p Chris
 *
 * 89    2/12/99 1:54p Sean
 *
 * 88    2/12/99 1:33p Sean
 *
 * 87    2/12/99 1:18p Sean
 *
 * 86    2/12/99 1:10p Sean
 * Encapsulated the last_portal code
 *
 * 85    2/12/99 11:22a Chris
 * Updated what BOA uses for BOA_cost_array.  It is not just the distance
 * from the center of the room to the center of the portal.  It was this +
 * the dist to the next room's center.  The reason for this change was it
 * makes it easier to compute the exact BOA_DIST for sounds.  This is
 * because the two distances are seperated (so from the start pos, we do a
 * vm_Vect dist from the start point to the portal)...  Hmmm....
 *
 * 84    2/09/99 12:40p Chris
 * More aipath stuff has been merged with the new BOA
 *
 * 83    2/09/99 9:59a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 82    1/30/99 3:44p Chris
 * Added support for time-offset'ed 3d sounds (like start at 1.2 seconds
 * into the sound)
 *
 * 81    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 80    1/26/99 5:16p Matt
 * Added StopObjectSound()
 *
 * 79    1/12/99 4:04p Samir
 * added environmental audio on a per room basis.
 *
 * 78    1/08/99 6:31p Samir
 * added reverb
 *
 * 77    12/22/98 11:08a Chris
 * Improved algorithm for 3d sounds
 *
 * 76    12/02/98 4:34p Samir
 * made high level playstream set a variable needed to call low level
 * stream playback.
 *
 * 75    11/16/98 4:29p Chris
 * Added pause new flag to the high level system
 *
 * 74    11/10/98 1:52p Jason
 * added dedicated server support
 *
 * 73    10/23/98 7:05p Samir
 * added pause and resume
 *
 * 72    10/22/98 8:31p Chris
 * Sounds use GlobalAlloc and GlobalFree
 *
 * 71    10/22/98 9:22a Chris
 * Fixes problems with hl-uids only being valid for the first 256 sounds
 *
 * 70    10/20/98 2:53a Kevin
 * gunboy crap
 *
 * 69    10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 68    10/17/98 12:46p Kevin
 * Beta 4 fixes
 *
 * 67    10/14/98 5:12p Samir
 * added a null SOUND_MIXER.
 *
 * 66    10/12/98 1:27p Jeff
 * all mem_free's do set the value to NULL after they are complete
 *
 * 65    10/02/98 3:39p Chris
 * Fixed a bug in Stopallsounds (it always acted like you where in the
 * game)
 *
 * 64    9/14/98 6:28p Jason
 * first pass at getting dedicated server working
 *
 * 63    9/11/98 3:08p Chris
 * Enabled the production sound
 *
 * 62    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 61    8/26/98 1:48a Chris
 * Fixed odd non-stopping sounds when ESC out of the game - etc.
 *
 * 60    8/18/98 12:18p Chris
 * Added f_in_game
 *
 * 59    7/09/98 8:34p Samir
 * added argument to callback for streams.
 *
 * 58    7/09/98 11:32a Samir
 * close stream system after init check in KillSoundLib.
 *
 * 57    7/08/98 6:27p Samir
 * stream library integrated with highlevel sound system.
 *
 * 56    6/29/98 10:44p Chris
 *
 * 55    6/29/98 10:44p Chris
 * Added support for SIF_ONCE_PER_OBJ
 *
 * 54    6/29/98 10:12a Chris
 * Further improved the sound system
 *
 * 53    6/29/98 9:29a Chris
 * Added some support for Direct Sound 3d
 *
 * 52    6/24/98 12:09p Chris
 * Update
 *
 * 51    6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 50    6/19/98 3:09p Chris
 * Improved IsSoundPlaying
 *
 * 49    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 48    6/17/98 4:39p Chris
 * Added the playing of 8bit samples with the 16 bit sound mixer
 *
 * 47    6/16/98 4:46p Chris
 * Revision 2 of the stream audio stuff
 *
 * 46    6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 45    5/14/98 7:32p Samir
 * Removed an ASSert and replaced with a mprintf
 *
 * 44    5/04/98 6:31p Craig
 * Added more bug checking
 *
 * 43    4/24/98 3:02p Chris
 * Removed GlobalAlloc and GlobalFree
 *
 * 42    4/23/98 12:00p Jeff
 * Fixed the GlobalFree problem
 *
 * 41    4/22/98 6:19p Chris
 * Fixed a lockup bug
 *
 * 40    4/22/98 4:31p Chris
 * Added DebugBlockPrint
 *
 * 39    4/06/98 3:43p Jason
 * Removed an ASSERT and make it an if-block
 *
 * 38    3/20/98 4:03p Chris
 * Made non-looping non-audible 3d sounds not play.
 *
 * 37    3/20/98 3:06p Chris
 * Removed some mprintf's
 *
 * 36    3/20/98 2:59p Chris
 * Added a wall hit sound for the player and added support for a base
 * volume for 3d sounds
 *
 * 35    2/27/98 5:31p Chris
 * Changed how master_volume is set.
 *
 * 34    2/23/98 6:32p Chris
 * Added support for a hlsoundlib unique id.  This is what all the public
 * functions use.  Also, looping sounds are now correctly turned off and
 * on.
 *
 * 33    2/23/98 5:03p Chris
 * Added the global alloc calls (deifned them to malloc and free when not
 * Win32)
 *
 * 32    2/17/98 1:17p Chris
 *
 * 31    2/17/98 1:11p Chris
 * Bails on invalid sound indices
 *
 * 30    2/16/98 4:34a Chris
 *
 * 29    2/16/98 4:23a Chris
 *
 * 28    2/16/98 3:54a Chris
 *
 * 27    2/16/98 3:20a Luke
 *
 * 26    2/16/98 2:47a Chris
 * Fixed problems with 3d looping sounds
 *
 * 25    2/15/98 8:13p Luke
 *
 * 24    2/15/98 7:12p Chris
 * More improvements to the sound lib
 *
 * 23    2/15/98 6:41p Chris
 * Added Update2dSound
 *
 * 22    2/13/98 5:15p Chris
 * Fixed multiple problems with looping sounds not being able to be
 * stopped
 *
 * 21    2/04/98 6:10p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 20    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 19    1/14/98 7:56p Chris
 * Fixed bugs dealing with llsound system being full.
 *
 * 18    1/14/98 5:40p Chris
 * Fixed problem of the hlsound system crashing when the llsound lib
 * filled up.
 *
 * 17    1/13/98 5:08p Chris
 * Increased sound object limit
 *
 * 16    1/08/98 1:11p Chris
 * Forgot to OR SND_OUTSIDE of some sounds
 *
 * 15    1/06/98 2:12p Chris
 * Added muffled sounds v.1 and made 3d sounds keep their roomnum.
 *
 * 14    1/05/98 4:36p Chris
 * Added working ambient sounds to objects.
 *
 * 13    1/05/98 3:58p Chris
 * Further improvements to the high level sound lib
 *
 * 12    1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 11    12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 10    12/30/97 2:15p Chris
 * Adding further support for software 3d stuff
 *
 * 9     12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 8     12/12/97 11:43a Chris
 * Added support to toggle sndlib on/off
 *
 * 7     12/11/97 1:33p Chris
 * Added support for fixed 3d position updating sounds.
 *
 * 6     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 5     11/21/97 1:10p Chris
 * Incremental Improvements
 *
 * 4     11/21/97 12:33p Chris
 * Fixed memory leak when -nosound was added.
 *
 * 3     11/07/97 5:43p Jason
 * added -nosound command switch
 *
 * 2     7/16/97 5:15p Chris
 * Fixed use of updating 3d sounds
 *
 * 23    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 22    5/22/97 5:15p Chris
 *
 * 21    5/15/97 1:59a Chris
 *
 * 20    4/29/97 8:03a Chris
 * Improved the sound code.  High-level sound now
 * fully uses the flags in the sound page and it
 * resulted in a simpilier coding interface  :)
 *
 * 19    4/28/97 11:21a Chris
 * Incremental improvements is the sound system
 *
 * 18    4/24/97 3:41a Chris
 * Improved 3d sound support.  :)
 *
 * 17    4/23/97 5:38p Chris
 * Updated some 3d sound code
 *
 * 16    4/03/97 8:37p Chris
 * Added the Main_OS object pass in the sound library
 * initialization code.
 *
 * 15    4/01/97 9:32a Chris
 * Getting sounds to work with the paging system.
 *
 * 14    3/27/97 11:44a Chris
 * On a re-initialize, I now make sure that the old initializaton is
 * cleared out
 *
 * 13    3/21/97 7:02 PM Jeremy
 * changed a "== SIF_UNUSED" to "= SIF_UNUSED" in StopAllSounds as it was
 * not really doing an assignment as intended.
 *
 * 12    3/21/97 4:06 PM Jeremy
 * changed name of low level mac sound header
 *
 * 11    3/14/97 5:22 PM Jeremy
 * unincluded malloc.h, changed #include of <pserror.h> to "pserror.h"
 * since it's not an ANSI header, but one of ours.
 *
 * 10    3/14/97 12:17p Chris
 * Abstract type for the low level sound lib
 *
 * 9     2/07/97 5:48p Matt
 * Renamed vector.h to vecmat.h to fix DevStudio problem
 *
 * $NoKeywords: $
 */
// High level sound object.  This code is 100% machine independant and
// completely encapsulates the lowel-level machine-dependant sound code.

#include <cstring>

#include "hlsoundlib.h"
#include "ssl_lib.h"
#include "mono.h"
#include "pserror.h"
#include "vecmat.h"
#include "args.h"
#include "sounds.h"
#include "game.h"
#include "room.h"
#include "BOA.h"
#include "streamaudio.h"
#include "doorway.h"
#include "dedicated_server.h"
#include "sndrender.h"
#include "voice.h"
#include "descent.h"

#include "sdlsound.h"

hlsSystem Sound_system;
char Sound_quality = SQT_NORMAL;
char Sound_mixer = SOUND_MIXER_SOFTWARE_16;
char Sound_card_name[256] = "";
struct tEnvAudioPresets {
  float volume;
  float decay;
  float damping;
}
EnvAudio_Presets[N_ENVAUDIO_PRESETS] = {
    {0.0F, 0.0F, 0.0F}, // Use for reverb off.
    {0.25F, 0.1F, 0.0F},      {0.417F, 0.4F, 0.666F},  {0.653F, 1.499F, 0.166F}, {0.208F, 0.478F, 0.0F},
    {0.5F, 2.309F, 0.888F},   {0.403F, 4.279F, 0.5F},  {0.5F, 3.961F, 0.5F},     {0.5F, 2.886F, 1.304F},
    {0.361F, 7.284F, 0.332F}, {0.5F, 10.0F, 0.3F},     {0.153F, 0.259F, 2.0F},   {0.361F, 1.493F, 0.0F},
    {0.444F, 2.697F, 0.638F}, {0.25F, 1.752F, 0.776F}, {0.111F, 3.145F, 0.472F}, {0.111F, 2.767F, 0.224F},
    {0.194F, 7.841F, 0.472F}, {1.0F, 1.499F, 0.5F},    {0.097F, 2.767F, 0.224F}, {0.208F, 1.652F, 1.5F},
    {0.652F, 2.886F, 0.25F},  {1.0F, 1.499F, 0.0F},    {0.875F, 8.392F, 1.388F}, {0.139F, 17.234F, 0.666F},
    {0.486F, 7.563F, 0.806F}};

//////////////////////////////////////////////////////////////////////////////
hlsSystem::hlsSystem() {
  m_f_hls_system_init = 0;
  m_ll_sound_ptr = NULL;
  m_sounds_played = 0;
  m_master_volume = 1.0;
  m_pause_new = false;
  n_lls_sounds = MAX_SOUNDS_MIXED;
}
bool hlsSystem::IsActive(void) {
  if (m_f_hls_system_init)
    return true;
  return false;
}
void hlsSystem::SetLLSoundQuantity(int n_sounds) {
  if (n_sounds > MAX_SOUNDS_MIXED) {
    n_sounds = MAX_SOUNDS_MIXED;
  }
  n_lls_sounds = n_sounds;
  mprintf(1, "SNDLIB: Allow %d sounds to be mixed.\n", n_sounds);
  if (m_f_hls_system_init) {
    InitSoundLib(NULL, Sound_mixer, Sound_quality, false);
  }
}
int hlsSystem::GetLLSoundQuantity() { return n_lls_sounds; }
// Start and clean-up after the sound library
int hlsSystem::InitSoundLib(oeApplication *sos, char mixer_type, char quality, bool f_kill_sound_list) {
  int status;
  // Turn off sound if desired
  if ((FindArg("-nosound")) || Dedicated_server) {
    m_ll_sound_ptr = NULL;
    return 0;
  }
  if (m_f_hls_system_init) {
    KillSoundLib(f_kill_sound_list);
  }

  // Create and initialize the low-level sound library
  if (m_ll_sound_ptr == NULL)
    m_ll_sound_ptr = new lnxsound;
  ASSERT(m_ll_sound_ptr);
  if (m_ll_sound_ptr == NULL)
    return 0;
  if (Sound_card_name[0]) {
    m_ll_sound_ptr->SetSoundCard(Sound_card_name);
  } else {
    m_ll_sound_ptr->SetSoundCard(NULL);
  }
  status = m_ll_sound_ptr->InitSoundLib(mixer_type, sos, n_lls_sounds);
  // Initialize the high-level sound library
  // Set the flag to initialized if all was o.k.
  if (status) {
    m_f_hls_system_init = 1;
    SetSoundQuality(quality);
    Sound_quality = GetSoundQuality();
    Sound_mixer = GetSoundMixer();

    // invoke high level stream system
    AudioStream::InitSystem(this->m_ll_sound_ptr);
    //	set current environment
    m_cur_environment = ENVAUD_PRESET_NONE;
  }
  // All done
  return status;
}
// Kills the sound library
void hlsSystem::KillSoundLib(bool f_kill_sound_list) {
  int i;
  if (m_f_hls_system_init) {
    mprintf(1, "m_sounds_played %d\n", m_sounds_played);
    // clean up stream system
    AudioStream::Shutdown();
    for (i = 0; i < MAX_SOUND_OBJECTS; i++) {
      m_sound_objects[i].m_obj_type_flags = SIF_UNUSED;
      m_sound_objects[i].m_hlsound_uid = -1;
    }
    m_ll_sound_ptr->DestroySoundLib();
    m_f_hls_system_init = 0;
  }
  if (m_ll_sound_ptr) {
    delete m_ll_sound_ptr;
    m_ll_sound_ptr = NULL;
  }
  // This is independant of the actual sound_lib status.  It happened because sounds
  // use the manage system.
  // moved this from beginning of function because won't the data freed here screw up streaming/looping sounds?
  // before the sound library is closed?
  if (f_kill_sound_list) {
    for (int i = 0; i < MAX_SOUND_FILES; i++) {
      SoundLoadFree(i);
    }
  }
}
// Pause and Resume the library
// Pauses all sounds
void hlsSystem::PauseSounds(bool f_all_pause) {
  if (!m_f_hls_system_init)
    return;
  m_pause_new = f_all_pause;
  AudioStream::PauseAll();
  m_ll_sound_ptr->PauseSounds();
}
// Resumes all sounds
void hlsSystem::ResumeSounds() {
  if (!m_f_hls_system_init)
    return;
  m_pause_new = false;
  m_ll_sound_ptr->ResumeSounds();
  AudioStream::ResumeAll();
}
// int hlsSystem::SetSoundPos(int sound_uid, int pos)
//{
//	if(!m_f_hls_system_init) return -1;
//
//	return m_ll_sound_ptr->SetSoundPos(sound_uid, pos);
//	return -1;
//}
// int hlsSystem::GetSoundPos(int sound_uid)
//{
//	if(!m_f_hls_system_init) return -1;
//
//	return m_ll_sound_ptr->GetSoundPos(sound_uid);
//	return -1;
//}
// Stops all sound from playing
void hlsSystem::StopAllSounds() {
  int i;
  if (!m_f_hls_system_init)
    return;
  for (i = 0; i < MAX_SOUND_OBJECTS; i++) {
    m_sound_objects[i].m_obj_type_flags = SIF_UNUSED;
    m_sound_objects[i].m_hlsound_uid = -1;
  }
  m_ll_sound_ptr->StopAllSounds();
  BeginSoundFrame(false);
  EndSoundFrame();

  SoundRenderReset();

  mprintf(0, "Stopped all sounds\n");
}
// Code for the beginning and ending of a frame of action
// Begin_sound_frame(listener pos/orient/velocity)
// SyncSounds
// Do sound pos updates -- IF VOLUME IS LOW AND NOT FOREVER (or looping), THEN STOP SOUND
// compute echo / reverb
// indirect/direct path sounds

#include "findintersection.h"

void hlsSystem::BeginSoundFrame(bool f_in_game) {
  bool hwsound_support;   // if this is true, sound_render_system is being used
  int16_t *sound_room_list; // these values are only meant for sound render system
  int i, n, counter = 0;
  pos_state listener_pos;
  const int num_samples_this_frame = (int)(Frametime * 22050);
  if (!m_f_hls_system_init)
    return;
  //	determine if we're using hardware for sound support.
  m_ll_sound_ptr->SoundStartFrame();
  // non game sound frame, this, just updates currently playing sounds.
  // placed here to leave early and ensure any further processing involves game only.
  if (!f_in_game) {
    sound_room_list = NULL;
    for (i = 0, counter = 0; i < MAX_SOUND_OBJECTS; i++) {
      if (m_sound_objects[i].m_obj_type_flags && m_sound_objects[i].m_sound_uid != -1) {
        counter++;
        ASSERT(m_sound_objects[i].m_sound_uid > -1);
        if (!m_ll_sound_ptr->IsSoundInstancePlaying(m_sound_objects[i].m_sound_uid)) {
          StopSound(i); // stop any sounds playing.
        }
      }
    }

    goto end_beginsoundframe; // this will handle any remaining processing
  }
  //	FROM HERE ON, WE ASSUME WE'RE IN GAME.
  hwsound_support = (sound_render_start_frame());
  //	define current environment of the listener.
  listener_pos.velocity = &Viewer_object->mtype.phys_info.velocity;
  listener_pos.position = &Viewer_object->pos;
  listener_pos.orient = &Viewer_object->orient;
  listener_pos.roomnum = Viewer_object->roomnum;
  m_ll_sound_ptr->SetListener(&listener_pos);
  // do environmental audio int current room.
  if (!OBJECT_OUTSIDE(Viewer_object)) {
    n = Rooms[Viewer_object->roomnum].env_reverb;
    if (n >= 0) {
      if (m_cur_environment != n) {
        ASSERT(n < N_ENVAUDIO_PRESETS);
        m_ll_sound_ptr->SetGlobalReverbProperties(EnvAudio_Presets[n].volume, EnvAudio_Presets[n].damping,
                                                  EnvAudio_Presets[n].decay);
        m_cur_environment = n;
      }
    }
  } else {
    if (m_cur_environment != ENVAUD_PRESET_MOUNTAINS) {
      n = ENVAUD_PRESET_MOUNTAINS;
      m_ll_sound_ptr->SetGlobalReverbProperties(EnvAudio_Presets[n].volume, EnvAudio_Presets[n].damping,
                                                EnvAudio_Presets[n].decay);
      m_cur_environment = n;
    }
  }
  // render all rooms within a certain range from player (traverse rooms through portals)
  sound_room_list = hwsound_support ? sound_render_audible_rooms(&listener_pos) : NULL;
  //	SoundQ_process();
  // if sound object is outside listener's cone of audibility, emulate the sound.
  //	if sound is audible, then determine its playback properties.
  //
  for (i = 0, counter = 0; i < MAX_SOUND_OBJECTS; i++) {
    if (m_sound_objects[i].m_obj_type_flags) {
      counter++;
      //			oldvolume = m_sound_objects[i].volume;
      //			oldpan = m_sound_objects[i].pan;
      //			mprintf(0, "SO %d playing: uid %d\n", i, m_sound_objects[i].m_sound_uid);
      // Handle high-level only sounds
      if (m_sound_objects[i].m_obj_type_flags & SIF_TOO_FAR) {
        if (m_sound_objects[i].m_obj_type_flags & SIF_LOOPING) {
          //					while(m_sound_objects[i].play_info.m_samples_played >=
          // Sounds[m_sound_objects[i].m_sound_index].loop_end)
          //					{
          //						m_sound_objects[i].play_info.m_samples_played -=
          //(Sounds[m_sound_objects[i].m_sound_index].loop_end - Sounds[m_sound_objects[i].m_sound_index].loop_start);
          //					}
        } else {
          // Advance sound pointer and see if sound is done
          m_sound_objects[i].play_info.m_samples_played += num_samples_this_frame;

          if (m_sound_objects[i].play_info.m_samples_played >=
              SoundFiles[Sounds[m_sound_objects[i].m_sound_index].sample_index].sample_length) {
            StopSound(i);
            continue;
          }
        }
        if (m_sound_objects[i].m_obj_type_flags & SIF_OBJ_UPDATE) {
          // If object not alive, kill its sound
          object *obj_sound = ObjGet(m_sound_objects[i].m_link_info.object_handle);
          if (!obj_sound || obj_sound->type == OBJ_DUMMY) {
            StopSound(i);
            continue; // Go on to next sound...
          }
        }
        // determine new properties of sound if it's still playing, its volume, other properties.
        if (Emulate3dSound(i)) {
          //	sound is audible now.
          if (m_sound_objects[i].m_sound_uid != -1) {
            m_sound_objects[i].m_obj_type_flags &= (~SIF_TOO_FAR);
          } else {
            // mprintf(0, "LLSound full 3\n");
          }
        }
        continue;
      }
      ASSERT(m_sound_objects[i].m_sound_uid > -1);
      if (!m_ll_sound_ptr->IsSoundInstancePlaying(m_sound_objects[i].m_sound_uid)) {
        StopSound(i);
        continue; // Go on to next sound...
      }
      if ((Sounds[m_sound_objects[i].m_sound_index].flags & SPF_LISTENER_UPDATE) &&
          !(m_sound_objects[i].m_obj_type_flags & SIF_NO_3D_EFFECTS)) {
        if (m_sound_objects[i].m_obj_type_flags & SIF_OBJ_UPDATE) {
          object *obj_sound = ObjGet(m_sound_objects[i].m_link_info.object_handle);
          if (!obj_sound || obj_sound->type == OBJ_DUMMY) {
            StopSound(i);
            continue; // Go on to next sound...
          }
        }
        if ((m_sound_objects[i].m_obj_type_flags & (SIF_PLAYING_3D | SIF_OBJ_UPDATE))) {
          bool f_audible;
          vector virtual_pos;
          vector virtual_vel;
          float adjusted_volume;
          f_audible = ComputePlayInfo(i, &virtual_pos, &virtual_vel, &adjusted_volume);
          if (!f_audible) {
            m_ll_sound_ptr->StopSound(m_sound_objects[i].m_sound_uid, SKT_STOP_IMMEDIATELY);
            m_sound_objects[i].m_sound_uid = 0;
            m_sound_objects[i].m_obj_type_flags |= SIF_TOO_FAR;
          } else {
            matrix orient = Identity_matrix;
            pos_state cur_pos;
            cur_pos.velocity = &virtual_vel;
            cur_pos.position = &virtual_pos;
            cur_pos.orient = &orient;
            m_ll_sound_ptr->AdjustSound(m_sound_objects[i].m_sound_uid, &cur_pos, adjusted_volume);

            // handle additional 3d sound support
            sound_object *so = &m_sound_objects[i];
            if (m_ll_sound_ptr->SoundPropertySupport() && (so->m_obj_type_flags & SIF_OBJ_UPDATE)) {
              float obstruction = 0.0f;
              object *game_obj;

              // sound must be in same room as listener
              // if so, then use FVI to determine obstruction properties.
              // and then set the obstruction properties.
              if (OBJECT_OUTSIDE(Viewer_object))
                continue;
              game_obj = ObjGet(so->m_link_info.object_handle);

              if (game_obj && game_obj->roomnum == Viewer_object->roomnum) {
                //	inside and same room?   go for it.
                fvi_info hit_data;
                fvi_query fq;

                //	mprintf(0, "Obstruction test.\n");

                hit_data.hit_type[0] = HIT_WALL;
                fq.p1 = &Viewer_object->pos;
                fq.p0 = &game_obj->pos;
                fq.startroom = game_obj->roomnum;
                fq.rad = .5;
                fq.thisobjnum = so->m_link_info.object_handle & HANDLE_OBJNUM_MASK;
                fq.ignore_obj_list = NULL;
                fq.flags = 0;
                fvi_FindIntersection(&fq, &hit_data);

                if (hit_data.hit_type[0] == HIT_WALL) {
                  obstruction = 1.0f;
                }
                m_ll_sound_ptr->SetSoundProperties(so->m_sound_uid, obstruction);
              } else {
                m_ll_sound_ptr->SetSoundProperties(so->m_sound_uid, 0.0f);
              }
            }
          }
        }
      }
    }
  }
  // mprintf(0, "BeginSoundFrame: used sound_objects %d\n", counter);
end_beginsoundframe:
  AudioStream::Frame();
  mprintf_at(3, 1, 0, "HNS: %04d", counter);
}

// Plays the deffered 3d stuff
void hlsSystem::EndSoundFrame() {
  if (!m_f_hls_system_init)
    return;
  sound_render_end_frame();
  m_ll_sound_ptr->SoundEndFrame();
}
// Allows for changes in a currently playing sound
int hlsSystem::Update2dSound(int hlsound_uid, float volume, float pan) {
  int sound_obj_index;

  if (!m_f_hls_system_init)
    return -1;
  if (volume < 0.0f)
    volume = 0.0f;
  else if (volume > 1.0f)
    volume = 1.0f;
  if (pan < -1.0f)
    pan = -1.0f;
  else if (pan > 1.0f)
    pan = 1.0f;
  if (!m_f_hls_system_init)
    return -1;
  sound_obj_index = ValidateUniqueId(hlsound_uid);
  if (sound_obj_index == -1)
    return -1;
  m_ll_sound_ptr->AdjustSound(m_sound_objects[sound_obj_index].m_sound_uid, volume, pan, 22050);
  return hlsound_uid;
}
bool hlsSystem::ComputePlayInfo(int sound_obj_index, vector *virtual_pos, vector *virtual_vel, float *adjusted_volume) {
  int sound_index;

  int sound_seg;
  int ear_seg;
  vector sound_pos;
  m_sound_objects[sound_obj_index].play_info.sample_skip_interval = 0;
  vector dir_to_sound;
  float dist = 0;
  if (m_master_volume <= 0.0)
    return false;

  *adjusted_volume = (m_master_volume * m_sound_objects[sound_obj_index].volume_3d);
  if (*adjusted_volume <= 0.0) {
    *adjusted_volume = 0.0;
    return false;
  }

  sound_index = m_sound_objects[sound_obj_index].m_sound_index;
  ASSERT(sound_index >= 0 && sound_index < MAX_SOUNDS);

  if ((Sounds[m_sound_objects[sound_obj_index].m_sound_index].flags & SPF_LISTENER_UPDATE) &&
      !(m_sound_objects[sound_obj_index].m_obj_type_flags & SIF_NO_3D_EFFECTS) &&
      (m_sound_objects[sound_obj_index].m_obj_type_flags & SIF_OBJ_UPDATE)) { // this is an updating object sound
    object *objp = ObjGet(m_sound_objects[sound_obj_index].m_link_info.object_handle);
    if (!objp || objp->type == OBJ_DUMMY) { // Couldn't find object for given handle
      // Int3();			// get Chris//removed for outside testers
      return false;
    }
    if (objp->movement_type == MT_PHYSICS || objp->movement_type == MT_WALKING)
      *virtual_vel = objp->mtype.phys_info.velocity;
    else
      *virtual_vel = Zero_vector;

    sound_pos = objp->pos;
    sound_seg = objp->roomnum;
  } else {
    *virtual_vel = Zero_vector;
    sound_pos = m_sound_objects[sound_obj_index].m_link_info.pos_info.pos;
    sound_seg = m_sound_objects[sound_obj_index].m_link_info.pos_info.segnum;
  }

  // sound_seg == -1 (which just means that the roomnum/segnum hasn't been
  // initialized to a proper value yet )causes crashes when BOA_INDEX()
  // calls TERRAIN_REGION() with that value. (By pure luck on 32bit platforms
  // the overflow and truncation will likely use an address that doesn't crash,
  // but it's still invalid). At least one case that could cause this was fixed,
  // if there are others, the ASSERT should tell us about it
  // (and if assertions are disabled, return false to handle this gracefully)
  ASSERT(sound_seg != -1 && "invalid (unset) roomnum/segnum!");
  if (sound_seg == -1)
    return false;

  sound_seg = BOA_INDEX(sound_seg);
  ear_seg = BOA_INDEX(Viewer_object->roomnum);
  if (!BOA_IsSoundAudible(sound_seg, ear_seg))
    return false;

  if (sound_seg != ear_seg && !(sound_seg == Highest_room_index + 1 && ear_seg > Highest_room_index) &&
      !(ear_seg == Highest_room_index + 1 && sound_seg > Highest_room_index)) {
    int cur_room = sound_seg;
    int last_room;

    do {
      last_room = cur_room;

      if (cur_room <= Highest_room_index && (Rooms[cur_room].flags & RF_DOOR) && (cur_room != sound_seg)) {
        float door_position = DoorwayGetPosition(&Rooms[cur_room]);
        // Closed doors antenuate a lot
        if (door_position == 0.0) {
          m_sound_objects[sound_obj_index].play_info.sample_skip_interval = 4;
          *adjusted_volume *= 0.2f;
        } else {
          *adjusted_volume *= (0.6f + (0.4 * door_position));
        }
      }
      cur_room = BOA_NEXT_ROOM(cur_room, ear_seg);
      int last_portal;
      if (BOA_INDEX(last_room) == BOA_INDEX(cur_room) || cur_room == BOA_NO_PATH)
        return false;
      if (BOA_INDEX(last_room) != BOA_INDEX(cur_room)) {
        last_portal = BOA_DetermineStartRoomPortal(last_room, NULL, cur_room, NULL);
        if (last_portal == -1) {
          return false;
        }
      }
      if (last_room == sound_seg) {
        if (cur_room == ear_seg) {
          dir_to_sound = sound_pos - Viewer_object->pos;
          dist = vm_NormalizeVector(&dir_to_sound);
        } else if ((cur_room != last_room) && (cur_room != BOA_NO_PATH)) {
          int this_portal = BOA_DetermineStartRoomPortal(cur_room, NULL, last_room, NULL);
          dist = BOA_cost_array[cur_room][this_portal];

          if (last_room > Highest_room_index) {
            vector pnt = Rooms[cur_room].portals[this_portal].path_pnt;
            dist += vm_VectorDistance(&sound_pos, &pnt);
          } else {
            dist += vm_VectorDistance(&sound_pos, &Rooms[last_room].portals[last_portal].path_pnt);
          }
        }
      } else if (cur_room == ear_seg) {
        dist += BOA_cost_array[last_room][last_portal];

        if (last_room > Highest_room_index) {
          int this_portal = BOA_DetermineStartRoomPortal(cur_room, NULL, last_room, NULL);
          vector pnt = Rooms[cur_room].portals[this_portal].path_pnt;
          dist += vm_VectorDistance(&Viewer_object->pos, &pnt);
        } else {
          dist += vm_VectorDistance(&Viewer_object->pos, &Rooms[last_room].portals[last_portal].path_pnt);
        }
      } else if ((cur_room != last_room) && (cur_room != BOA_NO_PATH)) {
        int this_portal = BOA_DetermineStartRoomPortal(cur_room, NULL, last_room, NULL);
        dist += BOA_cost_array[last_room][last_portal] + BOA_cost_array[cur_room][this_portal];
      }
    } while ((cur_room != ear_seg) && (cur_room != last_room) && (cur_room != BOA_NO_PATH));
    if (cur_room == BOA_NO_PATH) {
      *adjusted_volume = 0.0;
    } else if ((last_room != ear_seg) && (last_room != sound_seg)) {
      dir_to_sound = Rooms[last_room].path_pnt - Viewer_object->pos;
      vm_NormalizeVector(&dir_to_sound);
    }
  } else
  {
    dir_to_sound = sound_pos - Viewer_object->pos;
    dist = vm_NormalizeVector(&dir_to_sound);
  }
  if (dist >= Sounds[sound_index].max_distance)
    return false;

  if (*adjusted_volume <= 0.0) {
    *adjusted_volume = 0.0;
    return false;
  }
  if (dist == 0.0f) {
    dir_to_sound = Viewer_object->orient.fvec;
  }
  if ((m_sound_objects[sound_obj_index].play_info.sample_skip_interval == 0) && (*adjusted_volume > 0.0f) &&
      (dir_to_sound * Viewer_object->orient.fvec < -.5))
    m_sound_objects[sound_obj_index].play_info.sample_skip_interval = 1;
  *virtual_pos = Viewer_object->pos + (dir_to_sound * dist);
  return true;
}
bool hlsSystem::Emulate3dSound(int sound_obj_index) {
  bool f_audible;
  vector virtual_pos;
  vector virtual_vel;
  float adjusted_volume;
  f_audible = ComputePlayInfo(sound_obj_index, &virtual_pos, &virtual_vel, &adjusted_volume);

  if (f_audible) {
    pos_state cur_pos;
    matrix orient = Identity_matrix;
    cur_pos.velocity = &virtual_vel;
    cur_pos.position = &virtual_pos;
    cur_pos.orient = &orient;
    m_sound_objects[sound_obj_index].m_sound_uid = m_ll_sound_ptr->PlaySound3d(
        &m_sound_objects[sound_obj_index].play_info, m_sound_objects[sound_obj_index].m_sound_index, &cur_pos,
        adjusted_volume, (m_sound_objects[sound_obj_index].m_obj_type_flags & SIF_LOOPING) != 0);
    if (m_sound_objects[sound_obj_index].m_sound_uid == -1)
      f_audible = false;
  } else {
    m_sound_objects[sound_obj_index].m_sound_uid =
        0; // This is a dummy value -- it just cannot be -1 (that would mean that the low level sound system is full)
  }
  return f_audible;
}
// Functions that play a 3d sound -- includes the 2d emulation of 3d sound
int hlsSystem::Play3dSound(int sound_index, pos_state *cur_pos, float volume, int flags, float offset) {
  return Play3dSound(sound_index, SND_PRIORITY_NORMAL, cur_pos, volume, flags, offset);
}
// Functions that play a 3d sound -- includes the 2d emulation of 3d sound
int hlsSystem::Play3dSound(int sound_index, object *cur_obj, float volume, int flags, float offset) {
  return Play3dSound(sound_index, SND_PRIORITY_NORMAL, cur_obj, volume, flags, offset);
}
int hlsSystem::Play3dSound(int sound_index, int priority, pos_state *cur_pos, float volume, int flags, float offset) {
  if (!m_f_hls_system_init)
    return -1;
  return Play3dSound(sound_index, cur_pos, NULL, priority, volume, flags, offset);
}
// Functions that play a 3d sound -- includes the 2d emulation of 3d sound
int hlsSystem::Play3dSound(int sound_index, int priority, object *cur_obj, float volume, int flags, float offset) {
  pos_state cur_pos;
  if (!m_f_hls_system_init)
    return -1;
  cur_pos.position = &cur_obj->pos;
  cur_pos.orient = &cur_obj->orient;
  cur_pos.velocity = &cur_obj->mtype.phys_info.velocity;
  cur_pos.roomnum = cur_obj->roomnum;
  return Play3dSound(sound_index, &cur_pos, cur_obj, priority, volume, flags, offset);
}
// Functions that play a 3d sound -- includes the 2d emulation of 3d sound
int hlsSystem::Play3dSound(int sound_index, pos_state *cur_pos, object *cur_obj, int priority, float volume, int flags,
                           float offset) {
  int i;
  int sound_uid;
  int sound_obj_index;
  bool f_audible;
  if (!m_f_hls_system_init)
    return -1;
  if (sound_index == SOUND_NONE_INDEX)
    return -1;
  if (sound_index < 0)
    return -1;
  if (sound_index >= MAX_SOUNDS || Sounds[sound_index].used == 0)
    return -1;
  // if the position doesn't belong to any valid room or cell,
  // all this would fail anyway (in Emulate3dSound() -> ComputePlayInfo()),
  // so might as well give up now; furthermore, this prevents m_sound_objects[i]
  // from remaining in an half-initialized state below (esp. for looping sounds
  // where StopSound() wouldn't be called after Emulate3dSound() returns false)
  if (cur_pos->roomnum == -1)
    return -1;
  // initialize sound.
  Sound_system.CheckAndForceSoundDataAlloc(sound_index);
  int sample_offset = offset * 22050.0f;
  if (sample_offset >= SoundFiles[Sounds[sound_index].sample_index].np_sample_length)
    return -1;
  // Handles exclusive sounds
  if (Sounds[sound_index].flags & SPF_PLAYS_EXCLUSIVELY) {
    sound_uid = m_ll_sound_ptr->IsSoundPlaying(sound_index);
    if (sound_uid != -1)
      return -1;
  }
  // Handles play once sounds
  if (Sounds[sound_index].flags & SPF_PLAYS_ONCE) {
    for (sound_obj_index = 0; sound_obj_index < MAX_SOUND_OBJECTS; sound_obj_index++) {
      if ((m_sound_objects[sound_obj_index].m_sound_index == sound_index) &&
          ((sound_uid = m_sound_objects[sound_obj_index].m_sound_uid) != -1)) {
        StopSound(sound_obj_index);
      }
    }
  }
  // Handles play once per object
  if ((Sounds[sound_index].flags & SPF_ONCE_PER_OBJ) && cur_obj) {
    for (sound_obj_index = 0; sound_obj_index < MAX_SOUND_OBJECTS; sound_obj_index++) {
      if ((m_sound_objects[sound_obj_index].m_sound_index == sound_index) &&
          ((sound_uid = m_sound_objects[sound_obj_index].m_sound_uid) != -1)) {
        if (m_sound_objects[sound_obj_index].m_obj_type_flags & SIF_OBJ_UPDATE) {
          if (m_sound_objects[sound_obj_index].m_link_info.object_handle == cur_obj->handle) {
            return -1;
          }
        }
      }
    }
  }
  // find free sound slot.
  for (i = 0; i < MAX_SOUND_OBJECTS; i++) {
    if (m_sound_objects[i].m_obj_type_flags == SIF_UNUSED)
      break; //
  }
  // no free slots? hmmm....
  if (i >= MAX_SOUND_OBJECTS) {
    mprintf(2, "HLSOUNDLIB HOLY COW: Over %d sounds trying to play(beyond max) - %s\n", MAX_SOUND_OBJECTS,
             Sounds[sound_index].name);
    //		Int3();
    return -1;
  }
  // Set the current sound
  m_sound_objects[i].m_sound_index = sound_index;
  // Insert the passed flags
  m_sound_objects[i].m_obj_type_flags = flags;
  // Determine if the sound is linked to the object
  if ((cur_obj != NULL) && (Sounds[sound_index].flags & SPF_LISTENER_UPDATE) &&
      (Sounds[sound_index].flags & SPF_OBJ_UPDATE)) {
    m_sound_objects[i].m_obj_type_flags |= SIF_OBJ_UPDATE;
    m_sound_objects[i].m_link_info.object_handle = cur_obj->handle;
  } else {
    m_sound_objects[i].m_link_info.pos_info.pos = *cur_pos->position;
    m_sound_objects[i].m_link_info.pos_info.orient = *cur_pos->orient;
    m_sound_objects[i].m_link_info.pos_info.segnum = cur_pos->roomnum;
    // NOTE: Velocity is zero for all non object-linked sounds
  }
  m_sound_objects[i].volume_3d = volume;
  //	m_sound_objects[i].m_sound_uid = m_ll_sound_ptr->PlaySound3d(sound_index, cur_pos, 22050);
  // Increment the total number of sounds played
  m_sounds_played++;
  // Initialize the play information to nice values
  memset(&m_sound_objects[i].play_info, 0, sizeof(play_information));
  m_sound_objects[i].play_info.samples_per_22khz_sample = 1.0;
  m_sound_objects[i].play_info.sample_skip_interval = 0;
  m_sound_objects[i].play_info.priority = priority; // Set sound's priority rating
  m_sound_objects[i].m_hlsound_uid = MakeUniqueId(i);
  if (Sounds[sound_index].flags & SPF_LOOPED)
    m_sound_objects[i].m_obj_type_flags |= SIF_LOOPING;
  if (!m_pause_new) {
    f_audible = Emulate3dSound(i);
    if ((!f_audible) && (!(m_sound_objects[i].m_obj_type_flags & SIF_LOOPING))) {
      StopSound(i, SKT_STOP_IMMEDIATELY);
      return -1;
    }
  } else {
    f_audible = false;
    m_sound_objects[i].m_sound_uid = -1;
  }
  if (m_sound_objects[i].m_sound_uid == -1) {
    m_sound_objects[i].m_obj_type_flags |= SIF_TOO_FAR;
    // mprintf(0, "LLSound full 2\n");
  } else if (!f_audible) {
    m_sound_objects[i].m_obj_type_flags |= SIF_TOO_FAR;
  }
  m_sound_objects[i].m_obj_type_flags |= SIF_PLAYING_3D;
  if (m_pause_new) {
    PauseSounds(true);
  }

  return m_sound_objects[i].m_hlsound_uid;
}
// General purpose 2d sound play function
int hlsSystem::Play2dSound(int sound_index, float volume, float pan, uint16_t frequency) {
  return hlsSystem::Play2dSound(sound_index, SND_PRIORITY_NORMAL, volume, pan, frequency);
}
int hlsSystem::Play2dSound(int sound_index, int priority, float volume, float pan, uint16_t frequency) {
  int i = 0;
  int sound_uid;
  int sound_obj_index;
  if (!m_f_hls_system_init)
    return -1;
  if (sound_index == SOUND_NONE_INDEX)
    return -1;
  if (m_pause_new)
    return -1;
  if (sound_index < 0) {
    return -1;
  }
  Sound_system.CheckAndForceSoundDataAlloc(sound_index);
  // Handles exclusive sounds
  if (Sounds[sound_index].flags & SPF_PLAYS_EXCLUSIVELY) {
    sound_uid = m_ll_sound_ptr->IsSoundPlaying(sound_index);
    if (sound_uid != -1)
      return -1;
  }
  // Handles play once sounds
  if (Sounds[sound_index].flags & SPF_PLAYS_ONCE) {
    for (sound_obj_index = 0; sound_obj_index < MAX_SOUND_OBJECTS; sound_obj_index++) {
      if ((m_sound_objects[sound_obj_index].m_sound_index == sound_index) &&
          ((sound_uid = m_sound_objects[sound_obj_index].m_sound_uid) != -1)) {
        StopSound(sound_obj_index);
      }
    }
  }
  for (i = 0; i < MAX_SOUND_OBJECTS; i++) {
    if (m_sound_objects[i].m_obj_type_flags == SIF_UNUSED)
      break;
  }
  //	mprintf(0, "HL %d\n", i);
  //	ASSERT(i < MAX_SOUND_OBJECTS);
  if (i >= MAX_SOUND_OBJECTS) {
    mprintf(3, "Play2DSound: Max Sounds Objects used\n");
    //		Int3();
    return -1;
  }
  // Increment the total number of sounds played
  m_sounds_played++;
  // Initialize the play information to nice values
  memset(&m_sound_objects[i].play_info, 0, sizeof(play_information));
  m_sound_objects[i].play_info.samples_per_22khz_sample = 1.0;
  m_sound_objects[i].m_hlsound_uid = MakeUniqueId(i);
  m_sound_objects[i].play_info.priority = SND_PRIORITY_NORMAL;
  //	static_skip++;
  //	if (static_skip > 2)
  //		static_skip = 0;
  //
  //	m_sound_objects[i].play_info.sample_skip_interval = static_skip;
  //
  //	if(m_sound_objects[i].play_info.sample_skip_interval == 0)
  //		mprintf(0, "22.5k\n");
  //	else if (m_sound_objects[i].play_info.sample_skip_interval == 1)
  //		mprintf(0, "11.25k\n");
  //	else
  //		mprintf(0, "5.75k\n");
  m_sound_objects[i].m_sound_index = sound_index;
  m_sound_objects[i].m_sound_uid =
      m_ll_sound_ptr->PlaySound2d(&m_sound_objects[i].play_info, sound_index, volume * m_master_volume, pan,
                                  (Sounds[sound_index].flags & SPF_LOOPED));
  // ASSERT(m_sound_objects[i].m_sound_uid != -1);
  if (m_sound_objects[i].m_sound_uid == -1) {
    m_sound_objects[i].m_obj_type_flags = SIF_UNUSED;
    m_sound_objects[i].m_hlsound_uid = -1;
    mprintf(1, "Play2DSound: $%d Unplayed\n", i);
    return -1;
  }

  m_sound_objects[i].m_obj_type_flags |= SIF_PLAYING_2D;

  if (Sounds[m_sound_objects[i].m_sound_index].flags & SPF_LOOPED)
    m_sound_objects[i].m_obj_type_flags |= SIF_LOOPING;
  return m_sound_objects[i].m_hlsound_uid;
}
int hlsSystem::PlayStream(int unique_handle, void *data, int size, int stream_format, float volume,
                          void *stream_callback(void *user_data, int handle, int *size)) {
  int i = 0;
  ASSERT(stream_format == SIF_STREAMING_8_M || stream_format == SIF_STREAMING_16_M ||
         stream_format == SIF_STREAMING_8_S || stream_format == SIF_STREAMING_16_S);
  if (!m_f_hls_system_init)
    return -1;
  if (data == NULL || size <= 0)
    return -1;
  for (i = 0; i < MAX_SOUND_OBJECTS; i++) {
    if (m_sound_objects[i].m_obj_type_flags == SIF_UNUSED)
      break;
  }
  if (i >= MAX_SOUND_OBJECTS) {
    mprintf(2, "PlayStream:Max Sounds Objects\n");
    //		Int3();
    return -1;
  }
  // Increment the total number of sounds played
  m_sounds_played++;
  // Initialize the play information to nice values
  memset(&m_sound_objects[i].play_info, 0, sizeof(play_information));
  m_sound_objects[i].play_info.samples_per_22khz_sample = 1.0;
  m_sound_objects[i].play_info.left_volume = m_sound_objects[i].play_info.right_volume = volume * m_master_volume;
  m_sound_objects[i].play_info.m_stream_cback = stream_callback;
  m_sound_objects[i].play_info.m_stream_data = data;
  m_sound_objects[i].play_info.m_stream_format = stream_format;
  m_sound_objects[i].play_info.m_stream_size = size;
  m_sound_objects[i].play_info.m_stream_handle = unique_handle;
  m_sound_objects[i].play_info.m_stream_bufsize = size;
  m_sound_objects[i].m_hlsound_uid = MakeUniqueId(i);
  m_sound_objects[i].m_sound_index = -1;

  m_sound_objects[i].m_sound_uid = m_ll_sound_ptr->PlayStream(&m_sound_objects[i].play_info);
  // ASSERT(m_sound_objects[i].m_sound_uid != -1);
  if (m_sound_objects[i].m_sound_uid == -1) {
    m_sound_objects[i].m_obj_type_flags = SIF_UNUSED;
    m_sound_objects[i].m_hlsound_uid = -1;
    mprintf(2, "LLSound full 1\n");
    return -1;
  }

  m_sound_objects[i].m_obj_type_flags |= SIF_PLAYING_2D | stream_format;
  if (m_pause_new) {
    PauseSounds(true);
  }
  return m_sound_objects[i].m_hlsound_uid;
}
// Stop a looping sound and plays end snipit
void hlsSystem::StopSoundLooping(int hlsound_uid) {
  int sound_object_index;
  if (m_f_hls_system_init < 1)
    return; // DAJ -1FIX
  sound_object_index = ValidateUniqueId(hlsound_uid);
  if (sound_object_index == -1)
    return;
  StopSound(sound_object_index, SKT_STOP_AFTER_LOOP);
}
void hlsSystem::StopSoundImmediate(int hlsound_uid) {
  int sound_object_index;
  if (m_f_hls_system_init < 1)
    return; // DAJ -1FIX
  sound_object_index = ValidateUniqueId(hlsound_uid);
  if (sound_object_index == -1)
    return;
  StopSound(sound_object_index, SKT_STOP_IMMEDIATELY);
}
// Forcefully ends a sound
void hlsSystem::StopSound(int sound_obj_index, uint8_t f_stop_priority) {
  if (!m_f_hls_system_init)
    return;
  m_sound_objects[sound_obj_index].m_obj_type_flags &= (~SIF_LOOPING);

  if (m_sound_objects[sound_obj_index].m_sound_uid != -1) {
    mprintf(1, "stopSound %d \n", m_sound_objects[sound_obj_index].m_sound_uid);
    m_ll_sound_ptr->StopSound(m_sound_objects[sound_obj_index].m_sound_uid, f_stop_priority);
  }
  if (f_stop_priority == SKT_STOP_IMMEDIATELY || m_sound_objects[sound_obj_index].m_sound_uid == -1) {
    m_sound_objects[sound_obj_index].m_obj_type_flags = SIF_UNUSED;
    m_sound_objects[sound_obj_index].m_hlsound_uid = -1;
  }
}
// Stops all sounds attached to an object
void hlsSystem::StopObjectSound(int objhandle) {
  int i;
  for (i = 0; i < MAX_SOUND_OBJECTS; i++)
    if (m_sound_objects[i].m_obj_type_flags & SIF_OBJ_UPDATE)
      if (m_sound_objects[i].m_link_info.object_handle == objhandle)
        StopSound(i, SKT_STOP_IMMEDIATELY);
}
// Set the volume for all the sounds attached to an object
void hlsSystem::SetVolumeObject(int objhandle, float volume) {
  for (int i = 0; i < MAX_SOUND_OBJECTS; i++)
    if (m_sound_objects[i].m_obj_type_flags & SIF_OBJ_UPDATE)
      if (m_sound_objects[i].m_link_info.object_handle == objhandle)
        m_sound_objects[i].volume_3d = volume;
}
// Queued sound functions
// Adds a sound to a queue
void hlsSystem::Add2dSoundQueued(int q_num, int sound_index, float volume, float pan, uint16_t frequency) {
  if (!m_f_hls_system_init)
    return;
}
// Cleans a queue (if sound is playing it will finish normally)
void hlsSystem::KillQueue(int q_num) {
  if (!m_f_hls_system_init)
    return;
}
// Kills all sound queues
void hlsSystem::KillAllQueues() {
  if (!m_f_hls_system_init)
    return;
}
// Midi play stuff
void hlsSystem::PlayMidi() {
  if (!m_f_hls_system_init)
    return;
}
void hlsSystem::StopMidi() {
  if (!m_f_hls_system_init)
    return;
}
void hlsSystem::PauseMidi() {
  if (!m_f_hls_system_init)
    return;
}
void hlsSystem::ResumeMidi() {
  if (!m_f_hls_system_init)
    return;
}
void hlsSystem::SetMidiVolume() {
  if (!m_f_hls_system_init)
    return;
}
void hlsSystem::GetMidiVolume() {
  if (!m_f_hls_system_init)
    return;
}
// Sets the master volume
void hlsSystem::SetMasterVolume(float volume) {
  extern void StreamVolume(float master_volume);
  ASSERT(volume >= 0.0 && volume <= 1.0);

  if (volume == 0) {
    StopAllSounds();
    CloseVoices();
    KillSoundLib(true);
    m_master_volume = 0;
  } else {
    if (m_master_volume == 0) {
      InitSoundLib(Descent, Sound_mixer, Sound_quality, false);
      InitVoices();
    }
  }
  m_master_volume = volume;
  StreamVolume(m_master_volume);
}

// Gets the master volume
float hlsSystem::GetMasterVolume(void) { return m_master_volume; }
inline int hlsSystem::MakeUniqueId(int sound_obj_index) { return ((((int)m_sounds_played) << 12) + sound_obj_index); }
inline int hlsSystem::ValidateUniqueId(int hl_sound_uid) {
  ASSERT(MAX_SOUND_OBJECTS <= 0x0FFF);
  int index = hl_sound_uid & 0x0FFF;
  if (index < 0 || index >= MAX_SOUND_OBJECTS)
    return -1;

  if (hl_sound_uid == m_sound_objects[index].m_hlsound_uid) {
    return index;
  } else {
    return -1;
  }
}
bool hlsSystem::CheckAndForceSoundDataAlloc(int sound_index) {
  if (!m_f_hls_system_init)
    return false;
  return m_ll_sound_ptr->CheckAndForceSoundDataAlloc(sound_index);
}
bool hlsSystem::IsSoundPlaying(int hlsound_uid) {
  int hl_index;
  if (!m_f_hls_system_init)
    return false;
  hl_index = ValidateUniqueId(hlsound_uid);
  if (hl_index != -1) {
    return m_ll_sound_ptr->IsSoundInstancePlaying(m_sound_objects[hl_index].m_sound_uid);
  }
  return false;
}
bool hlsSystem::SetSoundQuality(char quality) {
  if (!m_f_hls_system_init)
    return false;
  m_ll_sound_ptr->SetSoundQuality(quality);
  Sound_quality = m_ll_sound_ptr->GetSoundQuality();
  return true;
}
char hlsSystem::GetSoundQuality(void) {
  if (!m_f_hls_system_init)
    return -1;
  return (Sound_quality = m_ll_sound_ptr->GetSoundQuality());
}
bool hlsSystem::SetSoundMixer(char mixer) {
  if (!m_f_hls_system_init)
    return false;
  m_ll_sound_ptr->SetSoundMixer(mixer);
  Sound_mixer = m_ll_sound_ptr->GetSoundMixer();
  return true;
}
char hlsSystem::GetSoundMixer(void) {
  if (!m_f_hls_system_init)
    return SOUND_MIXER_NONE;
  return (Sound_mixer = m_ll_sound_ptr->GetSoundMixer());
}
