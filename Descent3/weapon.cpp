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

 * $Logfile: /DescentIII/main/weapon.cpp $
 * $Revision: 91 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * $Log: /DescentIII/main/weapon.cpp $
 *
 * 91    4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 90    11/03/99 6:29p Chris
 * Improved the auto-selection code for dual fire secondary weapons
 *
 * 89    10/21/99 9:30p Jeff
 * B.A. Macintosh code merge
 *
 * 88    5/20/99 9:56p Jeff
 * AddWeaponToPlayer checks for max ammo when adding it
 *
 * 87    5/17/99 12:20p Samir
 * don't print out any poweup weapon pickup messages in AddWeaponToPlayer.
 *
 * 86    5/08/99 6:18p Chris
 * Fixed up no hearing cases
 *
 * 85    5/08/99 4:12p Chris
 * Added AI hearing noises... version 1
 *
 * 84    4/14/99 4:19a Jeff
 * more case mismatch fixes in #includes
 *
 * 83    4/12/99 12:49p Jeff
 * added recoil_force to weapon's page
 *
 * 82    3/31/99 10:27a Samir
 * code to reset auto select states when ship is initializiaed and code to
 * save and load these states from disk.
 *
 * 81    3/05/99 12:19p Matt
 * Delete now-unused function AddWeaponAmmoToPlayer()
 *
 * 80    3/03/99 5:08p Samir
 * AddWeaponAmmoToPlayer added.
 *
 * 79    2/25/99 1:29p Jason
 * fixed zoom problem
 *
 * 78    2/20/99 7:06p Matt
 * Changed a few HUD messages
 *
 * 77    2/10/99 3:48p Jason
 * table filter changes
 *
 * 76    1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 75    12/15/98 11:51a Samir
 * fixed bugs with autoselect weapons when they're supposed to be skipped.
 *
 * 74    12/04/98 5:13p Jason
 * took out extra mprintfs
 *
 * 73    10/22/98 2:41p Samir
 * fixed autoselection for good.
 *
 * 72    10/21/98 11:52p Samir
 * print different message if autoselecting a recently acquired weapon.
 *
 * 71    10/21/98 12:19p Samir
 * fixed small bug in SwitchPlayerWeapon for skipped weapons.
 *
 * 70    10/21/98 11:14a Samir
 * autoselect bug when selecting into a higher class without ammo/energy
 * fixed.
 *
 * 69    10/19/98 11:31p Samir
 * cycle up instead of down.
 *
 * 68    10/19/98 11:27p Samir
 * fixed weapon cycling (switchplayerweapon)
 *
 * 67    10/07/98 9:46p Samir
 * fixed small bug in SwitchPlayerWeapon
 *
 * 66    10/07/98 9:36p Samir
 * added a function to switch a player's weapon to another in the given
 * weapon class.
 *
 * 65    10/07/98 5:23p Jeff
 * samir fixed an autoselect bug
 *
 * 64    10/07/98 4:13p Samir
 * cleaned up weapon selection code.
 *
 * 63    9/30/98 4:31p Samir
 * added functions to handle weapon select list.
 *
 * 62    7/31/98 5:17p Samir
 * fixed weapon selection bug because secondaries weren't working properly
 * and removed guided missile from autoselect list.
 *
 * 61    7/30/98 11:09a Jason
 * added weapons that freeze and deform terrain
 *
 * 60    7/01/98 12:12p Jason
 * added countermeasures
 *
 * 59    6/22/98 6:26p Jason
 * added gravity field effect for weapons
 *
 * 58    6/19/98 12:04p Jason
 *
 * 57    6/17/98 3:27p Jeff
 * Changes made for localization
 *
 * 56    6/16/98 10:54a Jeff
 *
 * 55    5/27/98 7:12p Samir
 * yet another silly weapon selection(primary) bug fixed due to hasty
 * checking in.
 *
 * 54    5/27/98 6:02p Samir
 * foolishly, I don't check for primary weapon ammo when selecting
 * weapons.
 *
 * 53    5/26/98 10:48p Samir
 * weapon selection FIXED!
 *
 * 52    5/26/98 5:06p Samir
 * changed name of weapon indices and added function to get weapon's icon
 * image.
 *
 * 51    5/25/98 6:39p Jason
 * got icons working for weapons
 *
 * 50    5/22/98 6:25p Samir
 * fixed 'Rocker' bug.
 *
 * 49    5/22/98 11:59a Chris
 * Fixed improper uses of FindSoundName and made the proper static sounds
 *
 * 48    5/14/98 12:56p Jason
 * changes to help lower memory usage
 *
 * 47    4/24/98 5:32p Samir
 * added reset reticle when setting a new weapon.
 *
 * 46    4/24/98 8:02a Samir
 * added a int16_t weapon name array.
 *
 * 45    4/22/98 1:08p Chris
 * Fixed auto-firing of weapons after auto-selection
 *
 * 44    4/08/98 12:16p Samir
 * Weapon selection should be improved.
 *
 * 43    4/07/98 3:31p Jason
 * got particle effects working with weapons
 *
 * 42    4/06/98 4:53p Jason
 * got pageable polymodels working correctly with editor
 *
 * 41    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 40    3/23/98 3:52p Jason
 * added weapon names
 *
 * 39    3/17/98 2:40p Samir
 * reorg of hud/gauge system.
 *
 * 38    2/26/98 6:00p Jason
 * fixed a bug where a OBJ_GHOST object (ie a dead player) could try to
 * select a new weapon
 *
 * 37    2/17/98 11:33p Matt
 * Use new function to stop player firing activity when switching weapons
 *
 * 36    2/17/98 5:04p Samir
 * Fixed selection of secondary weapons.
 *
 * 35    2/17/98 4:06p Jason
 * Fixed DrawAlphaBlendedScreen not zbuffering correctly
 *
 * 34    2/17/98 3:47p Matt
 * Revamped weapon system and got sounds for spray and fusion weapons
 * working.  Still need to implements getting continuous & cutoff sounds
 * from player ship.
 *
 * 33    2/15/98 1:18a Jason
 * fixed zbuffer problem
 *
 * 32    2/14/98 10:48p Jason
 * got preferred rendering working
 *
 * 31    2/11/98 2:04p Jason
 * got spawning weapons working
 *
 * 30    2/05/98 7:06p Jason
 * fixed weapon naming bug
 *
 * 29    2/05/98 6:53p Jason
 * added new weapon slot
 *
 * 28    2/05/98 6:29p Jason
 * added user settable explode time/size
 *
 * 27    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 26    2/02/98 4:07p Jason
 * added a couple of  weapons
 *
 * 25    1/29/98 6:06p Jason
 * added new weapons
 *
 * 24    1/28/98 3:18p Jason
 * Made AddWeaponToPlayer take a playernum
 *
 *
 * 23    1/26/98 11:01a Jason
 * incremental checkin for multiplayer
 *
 * 22    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 21    12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 20    11/14/97 6:57p Samir
 * Maybe fixed selection of weapons <-> auto selection dependencies.
 *
 * 19    11/14/97 5:47p Mark
 * Fixed some weapon selection hokeyness.
 *
 * 18    11/12/97 6:01p Samir
 * Added omega and guided names to weapon list.
 *
 * 17    11/12/97 1:13p Jason
 * added weapons that can ramp up
 *
 * 16    11/11/97 1:28p Samir
 * Weapon selection should change hud, I think.
 *
 * 15    11/05/97 12:21p Chris
 * Added weapon remap for player ship weapon batteries
 *
 * 14    11/04/97 5:52p Jason
 * added DrawAplhaBlendedScreen function
 *
 * 13    10/30/97 4:02p Matt
 * Added the flare
 *
 * 12    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 11    9/16/97 3:03p Samir
 * fixed autoselection of weapons when you don't have enough energy.
 *
 * 10    9/15/97 3:37p Samir
 * Updated some more names for weapons.
 *
 * 9     9/10/97 11:45a Chris
 * FIXED a major remapping bug
 * Added support for weapon batteries
 *
 * 8     9/10/97 10:12a Samir
 * Added weapon name text.
 *
 * 7     9/08/97 5:12p Samir
 * Fixed weapon selection
 *
 * 6     9/05/97 12:25p Samir
 * Added autoselection of weapons.
 *
 * 5     9/04/97 3:59p Samir
 * Added code to switch weapons.
 *
 * 4     8/07/97 3:28p Jason
 * Assign -1 as the default sound for weapons
 *
 * 3     8/07/97 1:01p Mark
 * fixed a dumb bug
 *
 * 2     8/07/97 12:53p Mark
 * FROM JASON: Made oof readable as discharge files
 *
 * 7     4/28/97 6:46p Jason
 * made ships have multiple gun points
 *
 * 6     4/25/97 3:59p Jason
 * fixed a bug that my last checkin caused
 *
 * 5     4/25/97 3:31p Jason
 * implemented better memory management for vclips and bitmaps
 *
 * 4     4/17/97 2:54p Jason
 * added clueless weapon picker upper
 *
 * 3     4/14/97 1:50p Jason
 * first pass at getting weapons to fire
 *
 * 2     3/31/97 4:35p Jason
 * added weapon page functionality
 *
 * 1     3/31/97 4:13p Jason
 * weapons implementation file
 *

*
* $NoKeywords: $
*/

#include "weapon.h"
#include "pstypes.h"
#include "pserror.h"
#include "object.h"
#include "3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "bitmap.h"
#include "vclip.h"
#include "game.h"
#include "polymodel.h"
#include "player.h"
#include "hud.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "objinfo.h"
#include "gametexture.h"
#include "ship.h"
#include "gauges.h"
#include "sounds.h"
#include "stringtable.h"
#include "Macros.h"
#include "cfile.h"
#include "AIMain.h"

#include <algorithm>

// #include "samirlog.h"
#define LOGFILE(_s)

std::array<weapon, MAX_WEAPONS> Weapons;
int Num_weapons = 0;

const char *Static_weapon_names[] = {
    //	Primary weapons
    "Laser",
    "Vauss",
    "Microwave",
    "Plasma",
    "Fusion",
    "Super Laser",
    "Mass Driver",
    "Napalm",
    "EMD Gun",
    "Omega",
    //	Secondary weapons
    "Concussion",
    "Homing",
    "Impact Mortar",
    "Smart",
    "Mega",
    "Frag",
    "Guided",
    "Napalm Rocket",
    "Cyclone",
    "Black Shark",
    // The flares
    "Yellow Flare",
};

int Static_weapon_names_msg[] = {
    //	Primary weapons
    TXI_WPN_LASER,
    TXI_WPN_VAUSS,
    TXI_WPN_MICROWAVE,
    TXI_WPN_PLASMA,
    TXI_WPN_FUSION,
    TXI_WPN_SUPLASER,
    TXI_WPN_MASSDRIVER,
    TXI_WPN_NAPALM,
    TXI_WPN_EMDGUN,
    TXI_WPN_OMEGA,
    //	Secondary weapons
    TXI_WPN_CONCUSSION,
    TXI_WPN_HOMING,
    TXI_WPN_IMPACT,
    TXI_WPN_SMART,
    TXI_WPN_MEGA,
    TXI_WPN_FRAG,
    TXI_WPN_GUIDED,
    TXI_WPN_NAPALMR,
    TXI_WPN_CYCLONE,
    TXI_WPN_BLACKSHARK,
    // The flares
    TXI_WPN_YELL_FLARE,
};

int Static_weapon_ckpt_names[][2] = {
    //	Primary weapons
    {TXI_WPNC_LASER_1, TXI_WPNC_LASER_2},
    {TXI_WPNC_VAUSS_1, TXI_WPNC_VAUSS_2},
    {TXI_WPNC_MICRO_1, TXI_WPNC_MICRO_2},
    {TXI_WPNC_PLASMA_1, TXI_WPNC_PLASMA_2},
    {TXI_WPNC_FUSION_1, TXI_WPNC_FUSION_2},
    {TXI_WPNC_SUPLAS_1, TXI_WPNC_SUPLAS_2},
    {TXI_WPNC_MASSD_1, TXI_WPNC_MASSD_2},
    {TXI_WPNC_NAPALM_1, TXI_WPNC_NAPALM_2},
    {TXI_WPNC_EMD_1, TXI_WPNC_EMD_2},
    {TXI_WPNC_OMEGA_1, TXI_WPNC_OMEGA_2},
    //	Secondary weapons
    {TXI_WPNC_CONC_1, TXI_WPNC_CONC_2},
    {TXI_WPNC_HOMING_1, TXI_WPNC_HOMING_2},
    {TXI_WPNC_IMPACT_1, TXI_WPNC_IMPACT_2},
    {TXI_WPNC_SMART_1, TXI_WPNC_SMART_2},
    {TXI_WPNC_MEGA_1, TXI_WPNC_MEGA_2},
    {TXI_WPNC_FRAG_1, TXI_WPNC_FRAG_2},
    {TXI_WPNC_GUID_1, TXI_WPNC_GUID_2},
    {TXI_WPNC_NAPALMR_1, TXI_WPNC_NAPALMR_2},
    {TXI_WPNC_CYCLONE_1, TXI_WPNC_CYCLONE_2},
    {TXI_WPNC_BLKSHRK_1, TXI_WPNC_BLKSHRK_2},
    // The flares
    {TXI_WPNC_YELFLARE_1, TXI_WPNC_YELFLARE_2},
};

// Sets all weapons to unused
void InitWeapons() {
  for (int i = 0; i < MAX_WEAPONS; i++) {
    Weapons[i].used = 0;
    Weapons[i].name[0] = 0;
  }
  Num_weapons = 0;
}

// Allocs a weapon for use, returns -1 if error, else index on success
int AllocWeapon() {
  for (int i = MAX_STATIC_WEAPONS; i < MAX_WEAPONS; i++) {
    if (Weapons[i].used == 0) {
      memset(&Weapons[i], 0, sizeof(weapon));
      for (int t = 0; t < MAX_WEAPON_SOUNDS; t++)
        Weapons[i].sounds[t] = SOUND_NONE_INDEX;
      Weapons[i].alpha = 1.0;
      Weapons[i].spawn_handle = -1;
      Weapons[i].alternate_spawn_handle = -1;
      Weapons[i].icon_handle = -1;
      Weapons[i].scorch_handle = -1;
      Weapons[i].gravity_size = 1;
      Weapons[i].gravity_time = 1;
      Weapons[i].explode_size = 1;
      Weapons[i].explode_time = 1;
      Weapons[i].particle_count = 0;
      Weapons[i].particle_size = 1;
      Weapons[i].particle_life = 0;
      Weapons[i].particle_handle = -1;
      Weapons[i].robot_spawn_handle = -1;
      Weapons[i].alternate_chance = 0;
      Weapons[i].terrain_damage_size = 0;
      Weapons[i].terrain_damage_depth = 0;
      Weapons[i].used = 1;
      Weapons[i].recoil_force = 0.0f;
      Num_weapons++;
      return i;
    }
  }

  Int3(); // No weapons free!
  return -1;
}

// Frees weapon index n and all associated images
void FreeWeapon(int n) {
  ASSERT(Weapons[n].used > 0);

  Weapons[n].used = 0;
  Weapons[n].name[0] = 0;
  Num_weapons--;
}

// Gets next weapon from n that has actually been alloced
int GetNextWeapon(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_WEAPONS);

  if (Num_weapons == 0)
    return -1;

  for (i = n + 1; i < MAX_WEAPONS; i++)
    if (Weapons[i].used)
      return i;
  for (i = 0; i < n; i++)
    if (Weapons[i].used)
      return i;

  // this is the only one

  return n;
}

// Gets previous weapon from n that has actually been alloced
int GetPrevWeapon(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_WEAPONS);

  if (Num_weapons == 0)
    return -1;

  for (i = n - 1; i >= 0; i--) {
    if (Weapons[i].used)
      return i;
  }
  for (i = MAX_WEAPONS - 1; i > n; i--) {
    if (Weapons[i].used)
      return i;
  }

  // this is the only one
  return n;
}
// Searches thru all weapons for a specific name, returns -1 if not found
// or index of weapon with name
int FindWeaponName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_WEAPONS; i++)
    if (Weapons[i].used && !stricmp(name, Weapons[i].name))
      return i;

  return -1;
}

// Given a weapon handle, returns that weapons bitmap
// If the weapon is animated, returns framenum mod num_of_frames in the animation
// Also figures in gametime
int GetWeaponHudImage(int handle, int framenum) {
  if (Weapons[handle].flags & WF_HUD_ANIMATED) {
    float cur_frametime;
    int int_frame;

    vclip *vc = &GameVClips[Weapons[handle].hud_image_handle];
    ASSERT(vc->used);

    cur_frametime = Gametime / vc->frame_time;
    int_frame = cur_frametime;
    int_frame += framenum;

    return (vc->frames[int_frame % vc->num_frames]);
  } else
    return (Weapons[handle].hud_image_handle);
}

// Given a filename, loads either the bitmap or vclip found in that file.  If type
// is not NULL, sets it to 1 if file is animation, otherwise sets it to zero
int LoadWeaponHudImage(char *filename, int *type) {
  int anim = 0, bm_handle;
  char extension[10];

  int len = strlen(filename);

  if (len < 4)
    return -1;

  strncpy(extension, &filename[len - 3], 5);

  if ((!strnicmp("oaf", extension, 3)) || (!strnicmp("ifl", extension, 3)) || (!strnicmp("abm", extension, 3)))
    anim = 1;

  if (type != NULL)
    *type = anim;

  if (anim)
    bm_handle = AllocLoadVClip(IGNORE_TABLE(filename), NOT_TEXTURE, 0);
  else
    bm_handle = bm_AllocLoadFileBitmap(IGNORE_TABLE(filename), 0);

  return bm_handle;
}

// Given a weapon handle, returns that weapons discharge bitmap
int GetWeaponFireImage(int handle, int frame) {
  if (Weapons[handle].flags & WF_IMAGE_VCLIP) {
    float cur_frametime;
    int int_frame;

    PageInVClip(Weapons[handle].fire_image_handle);

    vclip *vc = &GameVClips[Weapons[handle].fire_image_handle];
    ASSERT(vc->used >= 1);

    cur_frametime = Gametime / vc->frame_time;
    int_frame = cur_frametime;
    int_frame += frame;
    return (vc->frames[int_frame % vc->num_frames]);
  } else
    return (Weapons[handle].fire_image_handle);
}

// Given a filename, loads either the bitmap or model found in that file.  If type
// is not NULL, sets it to 1 if file is model, otherwise sets it to zero
int LoadWeaponFireImage(char *filename, int *type, int *anim, int pageable) {
  int model = 0, bm_handle;
  int is_vclip = 0;
  char extension[10];

  int len = strlen(filename);

  if (len < 4)
    return -1;

  strncpy(extension, &filename[len - 3], 5);

  if ((!strnicmp("pof", extension, 3)) || (!strnicmp("oof", extension, 3)))
    model = 1;

  if (type != NULL)
    *type = model;
  if (anim != NULL)
    *anim = is_vclip;

  if (model)
    bm_handle = LoadPolyModel(IGNORE_TABLE(filename), 0);
  else {
    bm_handle = LoadTextureImage(IGNORE_TABLE(filename), anim, NOT_TEXTURE, 0);
  }

  return bm_handle;
}

// Given a weapon name, assigns that weapon to a specific index into
// the Weapons array.  Returns -1 if the named weapon is not found, 0 if the weapon
// is already in its place, or 1 if successfully moved
int MatchWeaponToIndex(char *name, int dest_index) {

  ASSERT(dest_index >= 0 && dest_index < MAX_WEAPONS);

  int cur_index = FindWeaponName(name);
  int new_index;

  if (cur_index == -1) {
    // The weapon we are trying to find is not loaded or doesn't exist
    Int3(); // Get Jason or Matt
    return -1;
  }

  if (cur_index == dest_index)
    return 0; // hurray, we're already matched up!

  if (Weapons[dest_index].used) {
    // This weapon is currently in use.  Copy the present data
    // into a new weapon and then assign our desired weapon to that index

    new_index = AllocWeapon();
    if (new_index >= 0) // DAJ -1FIX
      memcpy(&Weapons[new_index], &Weapons[dest_index], sizeof(weapon));

    // Now copy our new info over and free the old one
    memcpy(&Weapons[dest_index], &Weapons[cur_index], sizeof(weapon));
    FreeWeapon(cur_index);
  } else {
    // This slot is unused, so just take it

    Weapons[dest_index].used = 1;
    Num_weapons++;

    memcpy(&Weapons[dest_index], &Weapons[cur_index], sizeof(weapon));
    FreeWeapon(cur_index);
    return 0;
  }

  return new_index; // we made it!
}

// Moves a weapon from a given index into a new one (above MAX_STATIC_WEAPONS)
// returns new index
int MoveWeaponFromIndex(int index) {
  ASSERT(index >= 0 && index < MAX_STATIC_WEAPONS);
  ASSERT(Weapons[index].used);

  int new_index = AllocWeapon();
  memcpy(&Weapons[new_index], &Weapons[index], sizeof(weapon));
  FreeWeapon(index);

  return new_index;
}

// This is a very confusing function.  It takes all the weapons that we have loaded
// and remaps then into their proper places (if they are static).
void RemapWeapons() {
  int limit = sizeof(Static_weapon_names) / sizeof(void *);
  int i;

  for (i = 0; i < MAX_STATIC_WEAPONS; i++) {
    if (Weapons[i].used) {
      int match = -1;
      for (int t = 0; t < limit; t++)
        if (!stricmp(Weapons[i].name, Static_weapon_names[t])) {
          match = t;
          break;
        }

      if (match == -1) // this weapon is not supposed to be in the static area
      {
        int new_index;

        new_index = MoveWeaponFromIndex(i);
        RemapAllWeaponObjects(i, new_index);
      } else // this weapon is a static weapon, make sure its in its place
      {
        if (i != match) // its not where it belongs, move it
        {
          int new_index;

          new_index = MatchWeaponToIndex(Weapons[i].name, match);

          if (new_index != 0)
            RemapAllWeaponObjects(match, new_index);
          RemapAllWeaponObjects(i, match);
        }
      }
    }
  }

  for (i = MAX_STATIC_WEAPONS; i < MAX_WEAPONS; i++) {
    if (Weapons[i].used) {
      int match = -1;
      for (int t = 0; t < limit; t++)
        if (!stricmp(Weapons[i].name, Static_weapon_names[t])) {
          match = t;
          break;
        }

      if (match != -1) // this is a static weapon that isn't supposed to be in the free area
      {

        int new_index;
        new_index = MatchWeaponToIndex(Weapons[i].name, match);
        if (new_index != 0)
          RemapAllWeaponObjects(match, new_index);
        RemapAllWeaponObjects(i, match);
      }
    }
  }
}

// goes thru every entity that could possible have a weapon index (ie objects, weapons, etc)
// and changes the old index to the new index
void RemapAllWeaponObjects(int old_index, int new_index) {
  int i, j, k;

  // Remaps flying weapons
  for (i = 0; i < MAX_OBJECTS; i++) {

    if (Objects[i].type == OBJ_WEAPON) {
      if (Objects[i].id == old_index) {
        Objects[i].id = new_index;
      }
    }
  }

  // Remaps weapons contained by generic objects
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].static_wb) {
      for (j = 0; j < MAX_WBS_PER_OBJ; j++) {
        for (k = 0; k < MAX_WB_GUNPOINTS; k++) {
          if (Object_info[i].static_wb[j].gp_weapon_index[k] == old_index) {
            Object_info[i].static_wb[j].gp_weapon_index[k] = new_index;
          }
        }
      }
    }
  }

  // Remaps weapons contained by Ships
  for (i = 0; i < MAX_SHIPS; i++) {
    for (j = 0; j < MAX_WBS_PER_OBJ; j++) {
      for (k = 0; k < MAX_WB_FIRING_MASKS; k++) {
        if (Ships[i].static_wb[j].gp_weapon_index[k] == old_index) {
          Ships[i].static_wb[j].gp_weapon_index[k] = new_index;
        }
      }
    }
  }

  // Do spawns
  for (i = 0; i < MAX_WEAPONS; i++) {
    if (!Weapons[i].used)
      continue;

    if (Weapons[i].spawn_handle == old_index)
      Weapons[i].spawn_handle = new_index;
    if (Weapons[i].alternate_spawn_handle == old_index)
      Weapons[i].alternate_spawn_handle = new_index;
  }
}

bool IsWeaponSecondary(int index) {
  if (index < SECONDARY_INDEX)
    return false;
  else
    return true;
}

///////////////////////////////////////////////////////////////////////////
//	Weapon acquirement

//	unconditionally adds a weapon and ammo to a player.
int AddWeaponToPlayer(int slot, int weap_index, int ammo) {
  bool select_new = false;

  LOGFILE((_logfp, "Adding weapon(%d,ammo=%d) to player.\n", weap_index, ammo));

  Players[slot].weapon_flags |= HAS_FLAG(weap_index);

  ship *ship = &Ships[Players[slot].ship_index];
  otype_wb_info *wb = &ship->static_wb[weap_index];
  ASSERT(wb != NULL);

  // if secondary or primary that uses ammo, then use the ammo
  if ((weap_index >= SECONDARY_INDEX) || wb->ammo_usage) {
    // figure out much ammo to add
    int added = std::min(ship->max_ammo[weap_index] - Players[slot].weapon_ammo[weap_index], ammo);

    // now add it
    Players[slot].weapon_ammo[weap_index] += (uint16_t)added;
  }

  if (slot == Player_num) {
    if (weap_index < SECONDARY_INDEX)
      select_new = AutoSelectWeapon(PW_PRIMARY, weap_index);
    else
      select_new = AutoSelectWeapon(PW_SECONDARY, weap_index);

    // this should be done in multisafe code now.
    // if (!select_new) {
    //	AddHUDMessage ("%s!",TXT(Static_weapon_names_msg[weap_index]));
    //}
  }

  return 1;
}

///////////////////////////////////////////////////////////////////////////
//	Weapon selection

//	Note that we allocate five keys per category of weapon (primary, secondary)
//	We essentially select the weapon in slot passed.

#define NUM_PRIMARY_SLOTS 5
#define NUM_SECONDARY_SLOTS 5

//	This is NOT a mask of weapons available to the player.  This is a mask of what CLASS of
//	weapon this slot is currently in.  The code below checks this mask to see if it should
//	select the higher class weapon in that slot when switching to that slot.
static uint16_t Weapon_slot_mask = 0;

void SelectPrimaryWeapon(int slot);
void SelectSecondaryWeapon(int slot);
void SetPrimaryWeapon(int index, int slot);
void SetSecondaryWeapon(int index, int slot);

static inline bool is_weapon_available(unsigned player_weapon_flags, int new_weapon, uint16_t ammo = 0xffff) {
  return ((player_weapon_flags & HAS_FLAG(new_weapon)) && ammo > 0) ? true : false;
}

// used for sequencing
void ResetWeaponSelectStates(uint16_t new_state) { Weapon_slot_mask = new_state; }

void SaveWeaponSelectStates(CFILE *fp) { cf_WriteShort(fp, Weapon_slot_mask); }

void LoadWeaponSelectStates(CFILE *fp) {
  uint16_t state = (uint16_t)cf_ReadShort(fp);
  ResetWeaponSelectStates(state);
}

void SelectWeapon(int slot) {
  if (Player_object->type != OBJ_PLAYER)
    return; // This can happen when a player is dead and tries to select a weapon

  if (slot < NUM_PRIMARY_SLOTS)
    SelectPrimaryWeapon(slot);
  else
    SelectSecondaryWeapon(slot);
}

//	slot ranges 0-4
void SelectPrimaryWeapon(int slot) {
  // get slot of currently selected weapon
  int oldslot;
  int nw_low, nw_high;
  unsigned avail_flags;
  player *plr = &Players[Player_num];

  avail_flags = plr->weapon_flags;
  oldslot = plr->weapon[PW_PRIMARY].index % NUM_PRIMARY_SLOTS;

  //	do selection.  if we are selecting the same slot of weapon, then we select to the next
  //	level of weapon.  when going from highest level, go to lowest
  if (oldslot == slot) {
    uint16_t nw_low = (plr->weapon[PW_PRIMARY].index + NUM_PRIMARY_SLOTS) % MAX_PRIMARY_WEAPONS;

    if (is_weapon_available(avail_flags, nw_low)) {
      // toggle class of weapon in specified slot (save for selection)
      SetPrimaryWeapon(nw_low, slot);
    } else {
      AddHUDMessage(TXT_WPNNOTAVAIL);
      Sound_system.Play2dSound(SOUND_DO_NOT_HAVE_IT);

      ain_hear hear;
      hear.f_directly_player = true;
      hear.hostile_level = 0.1f;
      hear.curiosity_level = 0.5f;
      hear.max_dist = AI_SOUND_SHORT_DIST;
      AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);
    }

    return;
  } else {
    //	we are selecting a new weapon slot.
    nw_low = slot % NUM_PRIMARY_SLOTS;
    nw_high = nw_low + NUM_PRIMARY_SLOTS;

    if (Weapon_slot_mask & (1 << slot)) {
      // we think we have a higher class of weapon.
      if (is_weapon_available(avail_flags, nw_high)) {
        // if this slot had the higher class of weapon then check if we still have the higher class weapon.
        // toggle class of weapon in specified slot (save for selection)
        SetPrimaryWeapon(nw_high, slot);
      } else if (is_weapon_available(avail_flags, nw_low)) {
        // check if we have the lower class.
        // toggle class of weapon in specified slot (save for selection)
        SetPrimaryWeapon(nw_low, slot);
      } else {
        AddHUDMessage(TXT_WPNNOTAVAIL);
        Sound_system.Play2dSound(SOUND_DO_NOT_HAVE_IT);

        ain_hear hear;
        hear.f_directly_player = true;
        hear.hostile_level = 0.1f;
        hear.curiosity_level = 0.5f;
        hear.max_dist = AI_SOUND_SHORT_DIST;
        AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);
      }
    } else {
      //	if this is a lower class of weapon, make sure this slot is flagged as having the lower version
      if (is_weapon_available(avail_flags, nw_low)) {
        // if this slot had the higher class of weapon then check if we still have the higher class weapon.
        // toggle class of weapon in specified slot (save for selection)
        SetPrimaryWeapon(nw_low, slot);
      } else if (is_weapon_available(avail_flags, nw_high)) {
        // check if we have the lower class.
        // toggle class of weapon in specified slot (save for selection)
        SetPrimaryWeapon(nw_high, slot);
      } else {
        AddHUDMessage(TXT_WPNNOTAVAIL);
        Sound_system.Play2dSound(SOUND_DO_NOT_HAVE_IT);

        ain_hear hear;
        hear.f_directly_player = true;
        hear.hostile_level = 0.1f;
        hear.curiosity_level = 0.5f;
        hear.max_dist = AI_SOUND_SHORT_DIST;
        AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);
      }
    }
  }
}

// slot ranges 5-9
void SelectSecondaryWeapon(int slot) {
  // get slot of currently selected weapon
  int oldslot;
  int nw_low, nw_high;
  unsigned avail_flags;
  player *plr = &Players[Player_num];

  avail_flags = plr->weapon_flags;
  oldslot = (plr->weapon[PW_SECONDARY].index % NUM_SECONDARY_SLOTS) + NUM_PRIMARY_SLOTS;

  //	do selection.  if we are selecting the same slot of weapon, then we select to the next
  //	level of weapon.  when going from highest level, go to lowest
  if (oldslot == slot) {
    nw_low = SECONDARY_INDEX + ((plr->weapon[PW_SECONDARY].index + NUM_SECONDARY_SLOTS) % MAX_SECONDARY_WEAPONS);

    if (is_weapon_available(avail_flags, nw_low, plr->weapon_ammo[nw_low])) {
      // toggle class of weapon in specified slot (save for selection)
      SetSecondaryWeapon(nw_low, slot);
    } else {
      AddHUDMessage(TXT_WPNNOTAVAIL);
      Sound_system.Play2dSound(SOUND_DO_NOT_HAVE_IT);

      ain_hear hear;
      hear.f_directly_player = true;
      hear.hostile_level = 0.1f;
      hear.curiosity_level = 0.5f;
      hear.max_dist = AI_SOUND_SHORT_DIST;
      AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);
    }
    return;
  }

  //	we are selecting a new weapon slot.
  nw_low = (slot % NUM_SECONDARY_SLOTS) + SECONDARY_INDEX;
  nw_high = nw_low + NUM_SECONDARY_SLOTS;

  if (Weapon_slot_mask & (1 << slot)) {
    // we think we have a higher class of weapon.
    if (is_weapon_available(avail_flags, nw_high, plr->weapon_ammo[nw_high])) {
      // if this slot had the higher class of weapon then check if we still have the higher class weapon.
      SetSecondaryWeapon(nw_high, slot);
    } else if (is_weapon_available(avail_flags, nw_low, plr->weapon_ammo[nw_low])) {
      SetSecondaryWeapon(nw_low, slot);
    } else {
      AddHUDMessage(TXT_WPNNOTAVAIL);
      Sound_system.Play2dSound(SOUND_DO_NOT_HAVE_IT);

      ain_hear hear;
      hear.f_directly_player = true;
      hear.hostile_level = 0.1f;
      hear.curiosity_level = 0.5f;
      hear.max_dist = AI_SOUND_SHORT_DIST;
      AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);
    }
  } else {
    //	if this is a lower class of weapon, make sure this slot is flagged as having the lower version
    if (is_weapon_available(avail_flags, nw_low, plr->weapon_ammo[nw_low])) {
      // if this slot had the higher class of weapon then check if we still have the higher class weapon.
      SetSecondaryWeapon(nw_low, slot);
    } else if (is_weapon_available(avail_flags, nw_high, plr->weapon_ammo[nw_high])) {
      // check if we have the lower class.
      SetSecondaryWeapon(nw_high, slot);
    } else {
      AddHUDMessage(TXT_WPNNOTAVAIL);
      Sound_system.Play2dSound(SOUND_DO_NOT_HAVE_IT);

      ain_hear hear;
      hear.f_directly_player = true;
      hear.hostile_level = 0.1f;
      hear.curiosity_level = 0.5f;
      hear.max_dist = AI_SOUND_SHORT_DIST;
      AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);
    }
  }
}

void SetPrimaryWeapon(int index, int slot) {
  dynamic_wb_info *p_dwb = &Player_object->dynamic_wb[index];

  if (index < NUM_PRIMARY_SLOTS)
    Weapon_slot_mask &= ~(1 << slot);
  else
    Weapon_slot_mask |= (1 << slot);

  if (index != Players[Player_num].weapon[PW_PRIMARY].index) {
    ClearPlayerFiring(Player_object, PW_PRIMARY);
    Players[Player_num].weapon[PW_PRIMARY].index = index;

    AddHUDMessage(TXT_WPNSELECT, TXT(Static_weapon_names_msg[index]));
    //	SetGaugeModified(GGF_PRIMARYLOAD, true);
    Sound_system.Play2dSound(SOUND_CHANGE_PRIMARY);

    ain_hear hear;
    hear.f_directly_player = true;
    hear.hostile_level = 0.2f;
    hear.curiosity_level = 0.5f;
    hear.max_dist = AI_SOUND_SHORT_DIST;
    AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);

    // Stop any firing activity
    p_dwb->last_fire_time = Gametime;
    //	resets reticle to current weapon.
    ResetReticle();
  }
}

void SetSecondaryWeapon(int index, int slot) {
  dynamic_wb_info *p_dwb = &Player_object->dynamic_wb[index];

  if (index < (NUM_SECONDARY_SLOTS + SECONDARY_INDEX))
    Weapon_slot_mask &= ~(1 << slot);
  else
    Weapon_slot_mask |= (1 << slot);

  // Stop any firing activity
  ClearPlayerFiring(Player_object, PW_SECONDARY);

  if (index != Players[Player_num].weapon[PW_SECONDARY].index) {
    Players[Player_num].weapon[PW_SECONDARY].index = index;

    AddHUDMessage(TXT_WPNSELECT, TXT(Static_weapon_names_msg[index]));
    //	SetGaugeModified(GGF_SECONDARYLOAD, true);
    Sound_system.Play2dSound(SOUND_CHANGE_SECONDARY);

    ain_hear hear;
    hear.f_directly_player = true;
    hear.hostile_level = 0.1f;
    hear.curiosity_level = 0.3f;
    hear.max_dist = AI_SOUND_SHORT_DIST;
    AINotify(&Objects[Players[Player_num].objnum], AIN_HEAR_NOISE, (void *)&hear);

    // Stop any firing activity
    ClearPlayerFiring(Player_object, PW_SECONDARY);
    p_dwb->last_fire_time = Gametime;
    //	resets reticle to current weapon.
    ResetReticle();
  }
}

///////////////////////////////////////////////////////////////////////////
//	Weapon AUTO selection

const uint16_t SELLIST_START = 0x7ffe, SELLIST_END = 0x7fff;

static uint16_t PrimaryWpnSelectList[] = {SELLIST_START, LASER_INDEX,  VAUSS_INDEX,       MICROWAVE_INDEX,
                                        PLASMA_INDEX,  FUSION_INDEX, SUPER_LASER_INDEX, MASSDRIVER_INDEX,
                                        NAPALM_INDEX,  EMD_INDEX,    OMEGA_INDEX,       SELLIST_END};

static uint16_t SecondaryWpnSelectList[] = {
    SELLIST_START, CONCUSSION_INDEX,           HOMING_INDEX,       IMPACTMORTAR_INDEX, SMART_INDEX,      MEGA_INDEX,
    FRAG_INDEX,    GUIDED_INDEX + WPNSEL_SKIP, NAPALMROCKET_INDEX, CYCLONE_INDEX,      BLACKSHARK_INDEX, SELLIST_END};

uint16_t GetAutoSelectPrimaryWpnIdx(int slot) {
  int i = -1;

  while (PrimaryWpnSelectList[i + 1] != SELLIST_END) {
    if (slot == i)
      return PrimaryWpnSelectList[i + 1];
    i++;
  }

  return WPNSEL_INVALID;
}

uint16_t GetAutoSelectSecondaryWpnIdx(int slot) {
  int i = -1;

  while (SecondaryWpnSelectList[i + 1] != SELLIST_END) {
    if (slot == i)
      return SecondaryWpnSelectList[i + 1];
    i++;
  }

  return WPNSEL_INVALID;
}

void SetAutoSelectPrimaryWpnIdx(int slot, uint16_t idx) {
  if (slot < 0 || slot >= MAX_PRIMARY_WEAPONS)
    Int3();

  PrimaryWpnSelectList[slot + 1] = idx;
}

void SetAutoSelectSecondaryWpnIdx(int slot, uint16_t idx) {
  if (slot < 0 || slot >= MAX_SECONDARY_WEAPONS)
    Int3();

  SecondaryWpnSelectList[slot + 1] = idx;
}

const uint16_t IWPNSEL_SKIP = (uint16_t) ((~WPNSEL_SKIP) & 0xFFFF);

#define WPNINDEX(_index) (sel_list[(_index)] & IWPNSEL_SKIP)

// automatically switches weapon up to next level in autoselect order to this value. and type.
int SwitchPlayerWeapon(int weapon_type) {
  player *plr;
  ship *ship;
  int new_index;
  void (*setwpnfunc)(int, int); // Call either primary or secondary set weapon function
  uint16_t *sel_list;
  int plr_wpn_index;

  plr = &Players[Player_num];
  ship = &Ships[plr->ship_index];
  plr_wpn_index = plr->weapon[weapon_type].index;

  setwpnfunc = (weapon_type == PW_SECONDARY) ? SetSecondaryWeapon : SetPrimaryWeapon;
  sel_list = (weapon_type == PW_SECONDARY) ? SecondaryWpnSelectList : PrimaryWpnSelectList;

  new_index = 0;
  while (WPNINDEX(new_index) != plr_wpn_index && WPNINDEX(new_index) != SELLIST_END)
    new_index++;

  if (WPNINDEX(new_index) == SELLIST_END) {
    Int3();        // every weapon should be in list that's in the game. bad
    new_index = 1; // 1st item after SELLIST_START
  }

  // select weapon if we can. find a weapon we can select, if we go back to start, return.
  //	THIS CODE IS SIMILAR BUT NOT THE SAME AS THE AUTO SELECT CODE.
  int old_index = new_index;
  new_index++;

  while (old_index != new_index) {
    if (WPNINDEX(new_index) == SELLIST_END) {
      new_index = 0;
    } else if (WPNINDEX(new_index) == SELLIST_START) {
      new_index++;
    } else {
      uint16_t wpn_index = WPNINDEX(new_index);
      otype_wb_info *wb = &ship->static_wb[wpn_index];
      int slot = (weapon_type == PW_SECONDARY)
                     ? (((wpn_index - SECONDARY_INDEX) % NUM_SECONDARY_SLOTS) + NUM_PRIMARY_SLOTS)
                     : (wpn_index % NUM_PRIMARY_SLOTS);

      // mprintf(0, "wpn_index = %d\n", wpn_index);

      if ((Players[Player_num].weapon_flags & HAS_FLAG(wpn_index)) && !(sel_list[new_index] & WPNSEL_SKIP)) {

        if (wpn_index >= SECONDARY_INDEX && wb->ammo_usage && (wb->ammo_usage <= plr->weapon_ammo[wpn_index])) {
          //	we've found a weapon to select to that uses ammo!
          (*setwpnfunc)(wpn_index, slot);
          LOGFILE((_logfp, "ammo wpn: switch to new index %d\n", wpn_index));
          break;
        } else if (wpn_index < SECONDARY_INDEX && wb->ammo_usage && plr->weapon_ammo[wpn_index]) {
          //	we've found a weapon to select to that uses ammo!
          (*setwpnfunc)(wpn_index, slot);
          LOGFILE((_logfp, "ammo wpn: switch to new index %d\n", wpn_index));
          break;
        } else if (!wb->ammo_usage && (plr->energy >= wb->energy_usage)) {
          //	we've found an energy weapon to select to!
          (*setwpnfunc)(wpn_index, slot);
          LOGFILE((_logfp, "energy wpn:switch to new index %d\n", wpn_index));
          break;
        }
      }

      new_index++;
      // mprintf(0, "new_index = %d\n", new_index);
    }
  }

  return sel_list[new_index] & (~WPNSEL_SKIP);
}

//	Auto selects a weapon, usually the next best weapon.
//	step_up = true if we're going to next higher in order.
//	step_up = false if we're going to next lower in order.
bool AutoSelectWeapon(int weapon_type, int new_wpn) {
  player *plr;
  ship *ship;
  uint16_t *sel_list; // a weapon selection list
  int weapon_index; // the current weapon index
  int list_index;   // index into a selection list
  int list_initial; // initial index in list.
  int slot;
  bool sel_new_wpn = false;

  void (*setwpnfunc)(int, int); // Call either primary or secondary set weapon function

  LOGFILE((_logfp, "Entering AutoSelect\n"));

  ASSERT((weapon_type == PW_PRIMARY) || (weapon_type == PW_SECONDARY));
  plr = &Players[Player_num];
  weapon_index = plr->weapon[weapon_type].index;
  ship = &Ships[plr->ship_index];

  //	choose primary or secondary list and select function
  sel_list = (weapon_type == PW_SECONDARY) ? SecondaryWpnSelectList : PrimaryWpnSelectList;
  setwpnfunc = (weapon_type == PW_SECONDARY) ? SetSecondaryWeapon : SetPrimaryWeapon;

  list_index = 0;
  list_initial = 0;
  while (WPNINDEX(list_index) != SELLIST_END) {
    if (WPNINDEX(list_index) == weapon_index)
      list_initial = list_index;
    list_index++;
  }

  list_index--;

  //	this code takes care of selecting a GIVEN new weapon over the existing.
  if (new_wpn > -1) {
    while (WPNINDEX(list_index) != SELLIST_START && WPNINDEX(list_index) != new_wpn)
      list_index--;
    if (!(sel_list[list_index] & WPNSEL_SKIP)) {
      if (list_initial >= list_index) {
        uint16_t index = WPNINDEX(list_initial);
        otype_wb_info *wb = &ship->static_wb[index];
        if (index >= SECONDARY_INDEX && wb->ammo_usage && (wb->ammo_usage <= plr->weapon_ammo[index])) {
          LOGFILE((_logfp, "keep current ammo weapon...(ind=%d)\n", list_index));
          return sel_new_wpn; // the current weapon supercedes the new weapon, (or is the same) so return
        } else if (index < SECONDARY_INDEX && wb->ammo_usage && plr->weapon_ammo[index]) {
          LOGFILE((_logfp, "keep current ammo weapon...(ind=%d)\n", list_index));
          return sel_new_wpn; // the current weapon supercedes the new weapon, (or is the same) so return
        } else if (!wb->ammo_usage && (plr->energy >= wb->energy_usage)) {
          LOGFILE((_logfp, "keep current energy weapon...(ind=%d)\n", list_index));
          return sel_new_wpn; // the current weapon supercedes the new weapon, (or is the same) so return
        }
        LOGFILE((_logfp, "tried to keep current weapon, but no ammo!...(ind=%d)\n", list_index));
      }
    } else {
      LOGFILE((_logfp, "tried to autoselect skipped weapon, will not do...(ind=%d)\n", list_index));
      return sel_new_wpn;
    }
  }

  while (1) {
    uint16_t index = sel_list[list_index];
    otype_wb_info *wb = &ship->static_wb[index];

    if (index == SELLIST_START) {
      break;
    } else {
      //	we have a real weapon coming up, lets see if we have it, and if we do, then do we have
      //	ammo
      if (!(index & WPNSEL_SKIP)) {
        if (plr->weapon_flags & HAS_FLAG(index)) {
          slot = (weapon_type == PW_SECONDARY) ? (((index - SECONDARY_INDEX) % NUM_SECONDARY_SLOTS) + NUM_PRIMARY_SLOTS)
                                               : (index % NUM_PRIMARY_SLOTS);
          if (new_wpn == -1) {
            //	if no new weapon, then select to next best weapon that can be used
            if (index >= SECONDARY_INDEX && wb->ammo_usage && (wb->ammo_usage <= plr->weapon_ammo[index])) {
              //	we've found a weapon to select to that uses ammo!
              LOGFILE((_logfp, "ammo wpn: auto select to new index %d\n", index));
              (*setwpnfunc)(index, slot);
              break;
            } else if (index <= SECONDARY_INDEX && wb->ammo_usage && plr->weapon_ammo[index]) {
              //	we've found a weapon to select to that uses ammo!
              LOGFILE((_logfp, "ammo wpn: auto select to new index %d\n", index));
              (*setwpnfunc)(index, slot);
              break;
            } else if (!wb->ammo_usage && (plr->energy >= wb->energy_usage)) {
              //	we've found an energy weapon to select to!
              LOGFILE((_logfp, "energy wpn: auto select to new index %d\n", index));
              (*setwpnfunc)(index, slot);
              break;
            }
          } else {
            if (index < SECONDARY_INDEX || !wb->ammo_usage ||
                (index >= SECONDARY_INDEX && wb->ammo_usage && (wb->ammo_usage <= plr->weapon_ammo[index]))) {
              //	if new weapon, then always select that weapon (already assumes that new weapon is better.)
              LOGFILE((_logfp, "auto select to new index with new weapon!! %d\n", index));
              (*setwpnfunc)(index, slot);
              sel_new_wpn = true;
              break;
            }
          }
        }
      }
    }

    list_index--;
  }

  return sel_new_wpn;
}

// Draws an alpha blended polygon over the entire 3d rendering scene
// The r,g,b floats specify the color
void DrawAlphaBlendedScreen(float r, float g, float b, float alpha) {
  g3Point *pntlist[4], points[4];
  ddgr_color color;
  int i;

  color = GR_RGB(r * 255, g * 255, b * 255);

  // Set our four corners to cover the screen
  points[0].p3_sx = 0;
  points[0].p3_sy = 0;
  points[1].p3_sx = Game_window_w;
  points[1].p3_sy = 0;
  points[2].p3_sx = Game_window_w;
  points[2].p3_sy = Game_window_h;
  points[3].p3_sx = 0;
  points[3].p3_sy = Game_window_h;

  for (i = 0; i < 4; i++) {
    points[i].p3_z = 0;
    points[i].p3_flags = PF_PROJECTED;
    pntlist[i] = &points[i];
  }

  rend_SetZBufferState(0);
  rend_SetTextureType(TT_FLAT);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetAlphaValue(alpha * 255);
  rend_SetLighting(LS_NONE);
  rend_SetFlatColor(color);

  rend_DrawPolygon2D(0, pntlist, 4);
  rend_SetZBufferState(1);
}

// Retreives the weapon in the weapon array based off of an 'index' from 0-19 (non-mapped
//	primary and secondaries)
weapon *GetWeaponFromIndex(int player, int index) {
  ship *ship = &Ships[Players[player].ship_index];
  otype_wb_info *wb = &ship->static_wb[index];
  object *pobj = &Objects[Players[player].objnum];
  poly_model *pm = &Poly_models[pobj->rtype.pobj_info.model_num];
  dynamic_wb_info *dyn_wb = &pobj->dynamic_wb[index];
  int cur_m_bit;

  for (cur_m_bit = 0; cur_m_bit < pm->poly_wb[0].num_gps; cur_m_bit++) {
    if (wb->gp_fire_masks[dyn_wb->cur_firing_mask] & (0x01 << cur_m_bit)) {
      return &Weapons[wb->gp_weapon_index[cur_m_bit]];
    }
  }

  return NULL;
}
