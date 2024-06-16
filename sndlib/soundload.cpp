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


/*
 * $Logfile: /DescentIII/Main/sndlib/soundload.cpp $
 * $Revision: 59 $
 * $Date: 10/21/99 3:23p $
 * $Author: Kevin $
 *
 * Code to load sounds
 *
 * $Log: /DescentIII/Main/sndlib/soundload.cpp $
 *
 * 59    10/21/99 3:23p Kevin
 * Mac merge w/memory savings
 *
 * 58    5/11/99 12:10a Ardussi
 * changes to compile on Mac
 *
 * 57    5/08/99 3:30p Matt
 * Added weapon-hit-water sound.
 *
 * 56    4/30/99 3:28p Matt
 * Weapons now make a special sound when colliding with lava & volatile
 * surfaces, instead of the standard hit-wall sound.
 *
 * 55    4/29/99 3:50p Matt
 * Added hiss sound for volatile surface damage
 *
 * 54    4/29/99 1:10p Jeff
 * added sounds for inventory and countermeasure switch
 *
 * 53    4/14/99 1:46a Jeff
 * fixed case mismatched #includes
 *
 * 52    4/12/99 4:18p Jason
 * remap textures during sound remapping
 *
 * 51    4/11/99 5:03p Matt
 * Changed static sound remapping code to use simpler & more
 * space-efficient scheme.  Also deleted an unused entry in the static
 * sound list.
 *
 * 50    3/04/99 10:57a Matt
 * Added goal message notification sound
 *
 * 49    2/22/99 10:24p Matt
 * Added a static sound for debris explosion
 *
 * 48    2/18/99 4:48p Matt
 * Changed the default import volume for new sounds to 100%
 *
 * 47    2/18/99 2:49p Matt
 * Added goal complete sound
 *
 * 46    2/10/99 4:38p Matt
 * Misc. changes for table file parsing
 *
 * 45    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 44    1/13/99 6:55a Jeff
 * fixed #includes to work for linux
 *
 * 43    11/23/98 1:50p Jason
 * added thruster sounds
 *
 * 42    10/22/98 8:31p Chris
 * Sounds use GlobalAlloc and GlobalFree
 *
 * 41    10/21/98 4:53p Jeff
 * added some sounds to sounds array
 *
 * 40    10/20/98 2:09p Jeff
 * added 2 more sounds to static sounds
 *
 * 39    10/20/98 12:49p Matt
 * Removed obsolete sounds from static sound list.
 *
 * 38    10/19/98 7:19p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 37    10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 36    10/14/98 1:02p Jason
 * fixed FindSoundName issues
 *
 * 35    10/12/98 1:27p Jeff
 * all mem_free's do set the value to NULL after they are complete
 *
 * 34    9/21/98 8:19p Chris
 * Improved volatile and forcefield hits
 *
 * 33    9/18/98 1:27p Matt
 * Added afterburner release sound
 *
 * 32    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 31    7/24/98 5:22p Samir
 * took out WAV file stuff because low level sound libray needs this code.
 *
 * 30    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 29    6/17/98 4:39p Chris
 * Added the playing of 8bit samples with the 16 bit sound mixer
 *
 * 28    5/26/98 10:54p Chris
 * Ooops again
 *
 * 27    5/26/98 10:42p Chris
 * Fixed door sound paging
 *
 * 26    5/26/98 10:21p Chris
 * Added door sound paging
 *
 * 25    5/22/98 11:59a Chris
 * Fixed improper uses of FindSoundName and made the proper static sounds
 *
 * 24    5/17/98 4:08p Chris
 * Fixed bugs with initial sound loading.  :)
 *
 * 23    5/14/98 1:28p Chris
 * Improved sound loading stuff
 *
 * 22    5/14/98 11:49a Chris
 * Bettered the sound paging system
 *
 * 21    5/03/98 10:22p Matt
 * Added breaking glass sound
 *
 * 20    5/03/98 5:38p Chris
 * Added sounds to anim page
 *
 * 19    4/24/98 3:02p Chris
 * Removed GlobalAlloc and GlobalFree
 *
 * 18    4/22/98 5:38p Chris
 * Fixed problems with adding new sounds
 *
 * 17    4/22/98 11:55a Jeff
 * fixed stack overrun in ChangeSoundFileName
 *
 * 16    4/21/98 2:35p Chris
 * Made soundload use the standard mem_malloc stuff
 *
 * 15    4/06/98 5:13p Chris
 * Sounds page in at the beginning of a level
 *
 * 14    3/31/98 3:49p Jason
 * added memory lib
 *
 * 13    3/02/98 4:16p Chris
 * Added 14 new fields to the AI Settings Dialog/page.
 *
 * 12    2/23/98 5:03p Chris
 * Added the global alloc calls (deifned them to malloc and free when not
 * Win32)
 *
 * 11    2/16/98 4:55p Chris
 * Added default sounds for explosions
 *
 * 10    2/12/98 4:23p Chris
 * Fixed problem with sound dialog and allowing users to enter invalid
 * values
 *
 * 9     1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 8     12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 7     12/30/97 2:15p Chris
 * Adding further support for software 3d stuff
 *
 * 6     12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 5     12/19/97 4:09p Chris
 * New dynamically loading sounds
 *
 * 4     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 3     7/15/97 7:29p Chris
 * Added a sound for helicopter blades.
 *
 * 13    5/29/97 3:26p Chris
 *
 * 12    5/29/97 3:11p Chris
 * Fixed loadsound
 *
 * 11    5/22/97 3:29p Jason
 * made sounds loading faster
 *
 * 10    5/14/97 11:31p Jason
 * fixed annoying printf
 *
 * 9     5/14/97 12:31p Chris
 *
 * 8     5/13/97 10:31p Matt
 * Added hook for refueling sound
 *
 * $NoKeywords: $
 */

#include <cstring>

#include "pserror.h"
#include "ssl_lib.h"
#include "object.h"
#include "ddio.h"
#include "mem.h"
#include "soundload.h"
#include "weapon.h"
#include "ship.h"
#include "door.h"
#include "room.h"
#include "doorway.h"

#if defined(WIN32) || defined(__LINUX__)
#include "../manage/soundpage.h"
#include "../Descent3/sounds.h"
#endif

int Num_sounds = 0;
int Num_sound_files = 0;

const char *Static_sound_names[NUM_STATIC_SOUNDS] = {
    TBL_SOUND("Default"),                      // 0	SOUND_NONE_INDEX
    TBL_SOUND("Refuel"),                       // 1	SOUND_REFUELING
    TBL_SOUND("DefaultRobotExplode1"),         // 2	SOUND_ROBOT_EXPLODE_1
    TBL_SOUND("DefaultRobotExplode2"),         // 3	SOUND_ROBOT_EXPLODE_2
    TBL_SOUND("DefaultBuildingExplode"),       // 4	SOUND_BUILDING_EXPLODE
    TBL_SOUND("BreakingGlass"),                // 5	SOUND_BREAKING_GLASS
    TBL_SOUND("Tear01"),                       // 6	SOUND_MELEE_HIT_0
    TBL_SOUND("Tear02"),                       // 7	SOUND_MELEE_HIT_1
    TBL_SOUND("Afterburner"),                  // 8	SOUND_AFTERBURNER
    TBL_SOUND("Drop unknown "),                // 9	SOUND_ENERGY_DRAIN
    TBL_SOUND("Missle lock"),                  // 10	SOUND_MISSLE_LOCK
    TBL_SOUND("Powerup pickup"),               // 11	SOUND_POWERUP_PICKUP
    TBL_SOUND("You don't have it BEEP"),       // 12	SOUND_DO_NOT_HAVE_IT
    TBL_SOUND("Change primary weapon"),        // 13	SOUND_CHANGE_PRIMARY
    TBL_SOUND("Change secondary weapon"),      // 14	SOUND_CHANGE_SECONDARY
    TBL_SOUND("HitWall"),                      // 15	SOUND_PLAYER_HIT_WALL
    TBL_SOUND("AftrBrnrTail"),                 // 16	SOUND_AFTERBURNER_TAIL
    TBL_SOUND("Forcefield bounce"),            // 17	SOUND_FORCEFIELD_BOUNCE
    TBL_SOUND("Headlight1"),                   // 18	SOUND_HEADLIGHT
    TBL_SOUND("Cheater!"),                     // 19	SOUND_CHEATER
    TBL_SOUND("Energy Converter"),             // 20	SOUND_ENERGY_CONVERTER
    TBL_SOUND("CockpitSequenceTest1"),         // 21	SOUND_COCKPIT
    TBL_SOUND("Metallic Door Hit"),            // 22	SOUND_METALLIC_DOOR_HIT
    TBL_SOUND("Wall Fade ???"),                // 23	SOUND_WALL_FADE
    TBL_SOUND("Raindrop"),                     // 24	SOUND_RAINDROP
    TBL_SOUND("Lightning"),                    // 25	SOUND_LIGHTNING
    TBL_SOUND("HitEnergy"),                    // 26	SOUND_HIT_BY_ENERGY_WEAPON
    TBL_SOUND("HitMatter"),                    // 27	SOUND_HIT_BY_MATTER_WEAPON
    TBL_SOUND("HitConcussion"),                // 28	SOUND_HIT_BY_CONCUSSIVE_FORCE
    TBL_SOUND("HitFire"),                      // 29	SOUND_PLAYER_BURNING
    TBL_SOUND("Menu Slider Click"),            // 30	SOUND_MENU_SOUND_CLICK
    TBL_SOUND("Hostage pickup"),               // 31	SOUND_HOSTAGE_PICKUP
    TBL_SOUND("Briefstartup1"),                // 32	SOUND_BRIEF_STARTUP
    TBL_SOUND("BriefStatic"),                  // 33	SOUND_BRIEF_STATIC
    TBL_SOUND("Briefmonitoroff1"),             // 34	SOUND_BRIEF_MONITOROFF
    TBL_SOUND("Briefingrunning"),              // 35	SOUND_BRIEF_RUNNING
    TBL_SOUND("Briefbulb1"),                   // 36	SOUND_BRIEF_BULLB
    TBL_SOUND("Briefingtype"),                 // 37	SOUND_BRIEF_TYPE
    TBL_SOUND("ShpIdle"),                      // 38 SHIP_IDLE
    TBL_SOUND("ShpForwardThrust"),             // 39 SHIP_FORWARD_THRUST
    TBL_SOUND("ShpForwardThrRelease"),         // 40 SHIP_FORWARD_THRUST_RELEASE
    TBL_SOUND("GoalComplete"),                 // 41 SOUND_GOAL_COMPLETE
    TBL_SOUND("DebrisExplosion"),              // 42 SOUND_DEBRIS_EXPLODE
    TBL_SOUND("GameMessageNotify"),            // 43 SOUND_GAME_MESSAGE
    TBL_SOUND("Change countermeasure weapon"), // 44 SOUND_CHANGE_COUNTERMEASURE
    TBL_SOUND("Change inventory item"),        // 45 SOUND_CHANGE_INVENTORY
    TBL_SOUND("VolatileHiss"),                 // 46 SOUND_VOLATILE_HISS
    TBL_SOUND("WeaponHitLava"),                // 47 SOUND_WEAPON_HIT_LAVA
    TBL_SOUND("WeaponHitWater"),               // 48 SOUND_WEAPON_HIT_WATER
};

// Allocs a sound file for use, returns -1 if error, else index on success
int AllocSoundFile() {
  for (int i = 0; i < MAX_SOUND_FILES; i++) {
    if (SoundFiles[i].used == 0) {
      memset(&SoundFiles[i], 0, sizeof(sound_file_info));
      SoundFiles[i].used = 1;

      Num_sound_files++;
      return i;
    }
  }

  Int3(); // No sound files free!
  return -1;
}

// Frees sound index n
void FreeSoundFile(int n) {
  ASSERT(SoundFiles[n].used > 0);

  SoundFiles[n].used = 0;
  SoundFiles[n].name[0] = 0;
  if (SoundFiles[n].sample_8bit) {
    mem_free(SoundFiles[n].sample_8bit);
    SoundFiles[n].sample_8bit = NULL;
  }
  if (SoundFiles[n].sample_16bit) {
    mem_free(SoundFiles[n].sample_16bit);
    SoundFiles[n].sample_16bit = NULL;
  }
  Num_sound_files--;
}

// Gets next sound file from n that has actually been alloced
int GetNextSoundFile(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_SOUND_FILES);

  if (Num_sound_files == 0)
    return -1;

  for (i = n + 1; i < MAX_SOUND_FILES; i++)
    if (SoundFiles[i].used)
      return i;
  for (i = 0; i < n; i++)
    if (SoundFiles[i].used)
      return i;

  // this is the only one

  return n;
}

// Gets previous sound file from n that has actually been alloced
int GetPrevSoundFile(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_SOUND_FILES);

  if (Num_sound_files == 0)
    return -1;

  for (i = n - 1; i >= 0; i--) {
    if (SoundFiles[i].used)
      return i;
  }
  for (i = MAX_SOUND_FILES - 1; i > n; i--) {
    if (SoundFiles[i].used)
      return i;
  }

  // this is the only one
  return n;
}
// Searches thru all sounds for a specific name, returns -1 if not found
// or index of sound with name
int FindSoundFileName(char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_SOUND_FILES; i++)
    if (SoundFiles[i].used && !stricmp(name, SoundFiles[i].name))
      return i;

  return -1;
}

// gets the filename from a path, plus appends our .wav extension
void ChangeSoundFileName(const char *src, char *dest) {
  int limit;
  char path[256], ext[256], filename[256];

  limit = PAGENAME_LEN - 5;

  ddio_SplitPath(src, path, filename, ext);

  // Make sure we don't go over our name length limit
  strncpy(dest, filename, limit);

  strcat(dest, ".wav");
}

// Given a filename, loads the sound file.
int LoadSoundFile(const char *filename, float import_volume, bool f_get_data) {
  int sound_file_index;
  char extension[10];
  char name[90];
  int len;

  ChangeSoundFileName(filename, name);

  // See if the file was already loaded
  sound_file_index = FindSoundFileName(name);
  if (sound_file_index != -1)
    return sound_file_index;

  // Make room for the new sound
  sound_file_index = AllocSoundFile();
  if (sound_file_index == -1) {
    mprintf(0, "SOUND LOADER: No free sound file slots are available.\n", filename);
    Int3();
    return -1;
  }

  // Validate the extension length

  len = strlen(filename);
  if (len < 4) {
    mprintf(0, "SOUND LOADER: %s does not have a 3 charactor extension.\n", filename);
    Int3(); // Get chris
    goto error_state;
  }

  strcpy(SoundFiles[sound_file_index].name, name);

  // Load the file by its type (as defined by the extension)
  strncpy(extension, &filename[len - 3], 5);
  if (strnicmp("wav", extension, 3) == 0) {
    if (!SoundLoadWaveFile(filename, import_volume, sound_file_index, false, f_get_data)) {
      mprintf(0, "SOUND LOADER: Error loading %s.\n", filename);
      goto error_state;
    }
  } else {
    mprintf(0, "SOUND LOADER: %s in not a supported file type.\n", extension);
    goto error_state;
  }

  return sound_file_index;

error_state:
  if (SoundFiles[sound_file_index].used)
    FreeSoundFile(sound_file_index);
  return -1;
}

// Sets all sounds to unused
void InitSounds() {
  int i;

  for (i = 0; i < MAX_SOUNDS; i++) {
    Sounds[i].used = 0;
    Sounds[i].name[0] = 0;
    Sounds[i].flags = 0;
  }
  Num_sounds = 0;

  for (i = 0; i < MAX_SOUND_FILES; i++) {
    SoundFiles[i].name[0] = 0;
    SoundFiles[i].used = 0;
  }
  Num_sound_files = 0;
}

// Allocs a sound for use, returns -1 if error, else index on success
int AllocSound() {
  // Don't alloc sound 0, because 0 means something special (default/none)
  for (int i = 1; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used == 0) {
      memset(&Sounds[i], 0, sizeof(sound_info));

      Sounds[i].min_distance = 10.0;
      Sounds[i].max_distance = 256.0;
      Sounds[i].outer_cone_volume = 1.0;
      Sounds[i].inner_cone_angle = 360;
      Sounds[i].outer_cone_angle = 360;
      Sounds[i].import_volume = 1.0;

      Sounds[i].flags = SPF_LISTENER_UPDATE;

      Sounds[i].used = 1;
      Num_sounds++;
      return i;
    }
  }

  Int3(); // No sounds free!
  return -1;
}

// Frees sound index n
void FreeSound(int n) {
  ASSERT(Sounds[n].used > 0);

  Sounds[n].used = 0;
  Sounds[n].name[0] = 0;
  Sounds[n].flags = 0;
  Num_sounds--;
}

// Gets next sound from n that has actually been alloced
int GetNextSound(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_SOUNDS);

  if (Num_sounds == 0)
    return -1;

  for (i = n + 1; i < MAX_SOUNDS; i++)
    if (Sounds[i].used)
      return i;
  for (i = 0; i < n; i++)
    if (Sounds[i].used)
      return i;

  // this is the only one

  return n;
}

// Gets previous sound from n that has actually been alloced
int GetPrevSound(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_SOUNDS);

  if (Num_sounds == 0)
    return -1;

  for (i = n - 1; i >= 0; i--) {
    if (Sounds[i].used)
      return i;
  }
  for (i = MAX_SOUNDS - 1; i > n; i--) {
    if (Sounds[i].used)
      return i;
  }

  // this is the only one
  return n;
}
// Searches thru all sounds for a specific name, returns -1 if not found
// or index of sound with name
int FindSoundName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_SOUNDS; i++)
    if (Sounds[i].used && !stricmp(name, Sounds[i].name))
      return i;

  return -1;
}

// Given a filename, loads the sound.
int LoadSound(char *filename) {
  int sound_handle;

  sound_handle = mng_GetGuaranteedSoundPage(filename);

  return sound_handle;
}

void RemapSounds() {
  // Loop through the static sounds and move them to the correct slots
  for (int i = 0; i < NUM_STATIC_SOUNDS; i++) {

    int cur_index = FindSoundName(Static_sound_names[i]);

    if (cur_index == -1) {
      Int3(); // couldn't find statically-mapped sound
      continue;
    }

    if (cur_index != i) { // not in right slot

      if (Sounds[i].used) { // someone else in this slot, so swap
        sound_info tsound = Sounds[i];
        Sounds[i] = Sounds[cur_index];
        Sounds[cur_index] = tsound;
        RemapAllSoundObjects(i, MAX_SOUNDS);
        RemapAllSoundObjects(cur_index, i);
        RemapAllSoundObjects(MAX_SOUNDS, cur_index);
      } else { // slot is unused, so just take it
        Sounds[i] = Sounds[cur_index];
        Sounds[cur_index].used = 0;
        RemapAllSoundObjects(cur_index, i);
      }
    }
  }
}

// goes thru every entity that could possible have a sound index (ie objects, robots, etc)
// and changes the old index to the new index
void RemapAllSoundObjects(int old_index, int new_index) {
  int i, j, k;

  // Remaps weapon sounds
  for (i = 0; i < MAX_WEAPONS; i++) {

    if (Weapons[i].used) {
      for (j = 0; j < MAX_WEAPON_SOUNDS; j++) {
        if (Weapons[i].sounds[j] == old_index) {
          Weapons[i].sounds[j] = new_index;
        }
      }
    }
  }

  // Remaps all non-wb object sounds
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    for (j = 0; j < MAX_OBJ_SOUNDS; j++) {
      if (Object_info[i].sounds[j] == old_index) {
        Object_info[i].sounds[j] = new_index;
      }
    }
    if (Object_info[i].ai_info) {
      for (j = 0; j < MAX_AI_SOUNDS; j++) {
        if (Object_info[i].ai_info->sound[j] == old_index) {
          Object_info[i].ai_info->sound[j] = new_index;
        }
      }
    }
  }

  // Remaps weapon battery sounds contained by generic objects
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].static_wb) {
      for (j = 0; j < MAX_WBS_PER_OBJ; j++) {
        for (k = 0; k < MAX_WB_FIRING_MASKS; k++) {
          if (Object_info[i].static_wb[j].fm_fire_sound_index[k] == old_index) {
            Object_info[i].static_wb[j].fm_fire_sound_index[k] = new_index;
          }
        }
      }
    }
  }

  // Remaps anim sounds contained by generic objects
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].anim) {
      for (j = 0; j < NUM_MOVEMENT_CLASSES; j++) {
        for (k = 0; k < NUM_ANIMS_PER_CLASS; k++) {
          if (Object_info[i].anim[j].elem[k].anim_sound_index == old_index) {
            Object_info[i].anim[j].elem[k].anim_sound_index = new_index;
          }
        }
      }
    }
  }

  // Remaps weapons contained by Ships
  for (i = 0; i < MAX_SHIPS; i++) {
    for (j = 0; j < MAX_WBS_PER_OBJ; j++) {

      if (Ships[i].firing_sound[j] == old_index) {
        Ships[i].firing_sound[j] = new_index;
      }

      if (Ships[i].firing_release_sound[j] == old_index) {
        Ships[i].firing_release_sound[j] = new_index;
      }

      for (k = 0; k < MAX_WB_FIRING_MASKS; k++) {
        if (Ships[i].static_wb[j].fm_fire_sound_index[k] == old_index) {
          Ships[i].static_wb[j].fm_fire_sound_index[k] = new_index;
        }
      }
    }
  }

  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_DOOR) {
        door *door = &Doors[Rooms[i].doorway_data->doornum];

        if (door->open_sound == old_index)
          door->open_sound = new_index;
        if (door->close_sound == old_index)
          door->close_sound = new_index;
      }
    }
  }

  // Remaps textures
  for (i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used) {
      if (GameTextures[i].sound == old_index) {
        GameTextures[i].sound = new_index;
      }
    }
  }
}
