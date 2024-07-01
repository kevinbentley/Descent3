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

 * $Logfile: /DescentIII/Main/manage/shippage.cpp $
 * $Revision: 46 $
 * $Date: 10/22/01 12:41p $
 * $Author: Matt $
 *
 * $Log: /DescentIII/Main/manage/shippage.cpp $
 *
 * 46    10/22/01 12:41p Matt
 * After loading a ship model to check for errors, unload it so it can get
 * loaded again later after the textures have been read in.
 *
 * 45    10/08/01 4:20p Matt
 * Added system to check for errors when reading in add-on data.
 *
 * 44    9/06/01 10:32a Matt
 * Added code to fix problem poping add-on pages when the original pages
 * were in the extra.gam file.
 *
 * 43    4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 42    10/26/99 3:30p Jeff
 * handle extra.gam addon tablefile
 *
 * 41    10/20/99 6:27p Jeff
 * sped up addon page popping (by saving page offsets)
 *
 * 40    10/20/99 1:30p Jeff
 * fixed fusion recharge hack
 *
 * 39    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 38    7/27/99 1:14p Jason
 * fixed fusion firing time
 *
 * 37    5/14/99 11:56a Jeff
 * fixed copy/paste bug (Jason)
 *
 * 36    4/14/99 1:33a Jeff
 * fixed case mismatched #includes
 *
 * 35    3/04/99 4:47p Jason
 * temp fix (ie BAD HACK) for OEM table file woes
 *
 * 34    1/13/99 7:05a Jeff
 * put #ifdef around #include <windows.h>
 *
 * 33    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 32    11/13/98 12:30p Jason
 * changes for weapons
 *
 * 31    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 30    11/05/98 7:55p Jason
 * changes for new manage system
 *
 * 29    11/03/98 6:16p Chris
 * Starting to make on/off and spray weapons accessable to robots
 *
 * 28    11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 27    10/13/98 12:56p Matt
 * Finished (hopefully) with the ammo system.  Added support for napalm
 * fuel.
 *
 * 26    10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 25    10/02/98 1:47p Jason
 * added lod player ships
 *
 * 24    10/01/98 11:51a Matt
 * When loading or saving the player ship page, check for spew powerups
 * that aren't powerups & fix them.
 *
 * 23    9/21/98 8:19p Chris
 * Improved volatile and forcefield hits
 *
 * 22    9/10/98 11:53a Jason
 * added hud config filename to ship page
 *
 * 21    8/24/98 2:37p Jason
 * made table file more efficient with regards to invalid names
 *
 * 20    8/14/98 5:25p Jeff
 * fixed stupid bug setting wrong varible (nothing dangerous)
 *
 * 19    8/14/98 4:56p Jeff
 * added quad fire mask for weapon battery
 *
 * 18    8/07/98 2:06p Jason
 * now saves flags field
 *
 * 17    7/31/98 5:23p Jason
 * added ship armor scalars
 *
 * 16    6/01/98 10:37a Matt
 * Added system to spew powerups when the player dies.  Still needs Jason
 * to deal with  mng_FindSpecificGenericPage().
 *
 * 15    5/04/98 6:08p Jason
 * sped up predictive pagefile loading
 *
 * 14    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 13    3/19/98 1:07p Jason
 * added cockpit name
 *
 * 12    2/23/98 1:22p Jason
 * made FindSpecific* read from the local drive, not the net drive - when
 * starting the editor
 *
 * 11    2/17/98 8:12p Matt
 * Added looping & release sounds for player weapons
 *
 * 10    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 9     1/15/98 6:22p Jason
 * added safety checks so the network won't copy over a primitive you have
 * held locally
 *
 * 8     12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 7     11/12/97 5:35p Jason
 * made energy/ammo usage work with weapon batteries
 *
 * 6     11/12/97 1:13p Jason
 * added weapons that can ramp up
 *
 * 5     11/05/97 12:22p Chris
 * Fixed size of wb_info in the page file
 *
 * 4     11/05/97 10:45a Chris
 * Now init's the ship struct to zero (and fills in some values) before
 * reading.
 *
 * 3     11/04/97 6:18p Chris
 * Added support so that the player ship uses the robot's firing dialog.
 *
 * 2     10/21/97 11:57a Jason
 * added ability to set dying model for player ship
 *
 * 8     5/08/97 12:41p Jason
 * made manage system work with device dependant path names
 *
 * 7     4/25/97 6:16p Jason
 * added switcheroo function
 *
 * 6     4/09/97 9:57p Chris
 * Added more ability to customize ships/objects.
 *
 * 5     4/08/97 1:16a Chris
 * Fixed the bug with initial values for some items being random.  It also
 * fixed a intermitent bug that was caused because the used flag was
 * random... we wanted it to be 1 (non-zero), but it was random so there
 * was a chance it could be zero(1 in 2^(sizeof(used_flag)))
 *
 * 4     4/07/97 3:13p Chris
 *
 * 3     4/04/97 2:44p Matt
 * Changed object pages to store physics info in a physics_info structure.
 *
 * 2     3/31/97 4:34p Jason
 * added player ship page
 *
 * 1     3/31/97 12:10p Jason
 * Page file for player ship management
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "ship.h"
#include "shippage.h"
#include "mono.h"
#include "pserror.h"
#include "polymodel.h"
#include "ddio.h"
#include "robotfire.h"
#include "weaponpage.h"
#include "soundload.h"
#include "sounds.h"
#include "soundpage.h"
#include "genericpage.h"
#include "args.h"

// shippage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define SHIPPAGE_COMMAND_NAME 1
#define SHIPPAGE_COMMAND_END 2
#define SHIPPAGE_COMMAND_IMAGE_NAME 3
#define SHIPPAGE_COMMAND_VERSION 4
#define SHIPPAGE_COMMAND_MASS 5
#define SHIPPAGE_COMMAND_DRAG 6
#define SHIPPAGE_COMMAND_SIZE 7
#define SHIPPAGE_COMMAND_WIGGLE_AMPLITUDE 8
#define SHIPPAGE_COMMAND_THRUST 9
#define SHIPPAGE_COMMAND_ROTTHRUST 10
#define SHIPPAGE_COMMAND_TURNROLLRATE 11
#define SHIPPAGE_COMMAND_ROTDRAG 12
#define SHIPPAGE_COMMAND_PHYSICS_FLAGS 13
#define SHIPPAGE_COMMAND_WIGGLE_PER_SEC 14
#define SHIPPAGE_COMMAND_TURNROLL_RATIO 15
#define SHIPPAGE_COMMAND_DYING_IMAGE_NAME 16
#define SHIPPAGE_COMMAND_WB_INFO 17
#define SHIPPAGE_COMMAND_WB_WEAPON 18
#define SHIPPAGE_COMMAND_FIRE_FLAGS 19
#define SHIPPAGE_COMMAND_RESOURCE_USAGE 20
#define SHIPPAGE_COMMAND_WB_FIRE_SOUND 21
#define SHIPPAGE_COMMAND_WB_FLAGS 22
#define SHIPPAGE_COMMAND_FIRING_SOUND 23
#define SHIPPAGE_COMMAND_RELEASE_SOUND 24
#define SHIPPAGE_COMMAND_COCKPIT_NAME 25
#define SHIPPAGE_COMMAND_SPEW_POWERUP 26
#define SHIPPAGE_COMMAND_ARMOR_SCALAR 27
#define SHIPPAGE_COMMAND_FLAGS 28
#define SHIPPAGE_COMMAND_WB_QUADMASK 29
#define SHIPPAGE_COMMAND_HUD_NAME 30
#define SHIPPAGE_COMMAND_LOD_MODELS 31
#define SHIPPAGE_COMMAND_LOD_DISTANCE 32
#define SHIPPAGE_COMMAND_MAX_AMMO 33

#define SHIPPAGE_VERSION 6

extern char *TablefileNameOverride;

// Given an open file pointer and a ship_page struct, writes that ship page out
void mng_WriteShipPage(CFILE *outfile, mngs_ship_page *shippage) {
  int i;
  int j;
  int size;

  ASSERT(outfile != NULL);
  ASSERT(shippage != NULL);

  cf_WriteByte(outfile, PAGETYPE_SHIP);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_VERSION);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, SHIPPAGE_VERSION);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_NAME); // write out ship name
  cf_WriteByte(outfile, PAGENAME_LEN);
  for (i = 0; i < PAGENAME_LEN; i++)
    cf_WriteByte(outfile, shippage->ship_struct.name[i]);

  // Write out cockpit name
  cf_WriteByte(outfile, SHIPPAGE_COMMAND_COCKPIT_NAME); // write out ship name
  cf_WriteByte(outfile, strlen(shippage->ship_struct.cockpit_name) + 1);
  cf_WriteString(outfile, shippage->ship_struct.cockpit_name);

  // Write out hud config name
  cf_WriteByte(outfile, SHIPPAGE_COMMAND_HUD_NAME); // write out ship name
  cf_WriteByte(outfile, strlen(shippage->ship_struct.hud_config_name) + 1);
  cf_WriteString(outfile, shippage->ship_struct.hud_config_name);

  // Write out its models name
  cf_WriteByte(outfile, SHIPPAGE_COMMAND_IMAGE_NAME); // get ready to write out name
  cf_WriteByte(outfile, PAGENAME_LEN);
  for (i = 0; i < PAGENAME_LEN; i++)
    cf_WriteByte(outfile, shippage->image_name[i]);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_DYING_IMAGE_NAME); // get ready to write out name
  cf_WriteByte(outfile, strlen(shippage->dying_image_name) + 1);
  cf_WriteString(outfile, shippage->dying_image_name);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_MASS);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.mass);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_DRAG);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.drag);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.size);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_WIGGLE_AMPLITUDE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.wiggle_amplitude);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_THRUST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.full_thrust);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_ROTTHRUST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.full_rotthrust);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_TURNROLLRATE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.max_turnroll_rate);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_ROTDRAG);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.rotdrag);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_WIGGLE_PER_SEC);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.wiggles_per_sec);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_TURNROLL_RATIO);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.phys_info.turnroll_ratio);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_PHYSICS_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, shippage->ship_struct.phys_info.flags);

  // Write the LOD model names
  cf_WriteByte(outfile, SHIPPAGE_COMMAND_LOD_MODELS);
  size = strlen(shippage->med_image_name) + 1;
  size += strlen(shippage->lo_image_name) + 1;

  cf_WriteByte(outfile, size);
  cf_WriteString(outfile, shippage->med_image_name);
  cf_WriteString(outfile, shippage->lo_image_name);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_LOD_DISTANCE);
  cf_WriteByte(outfile, 8);
  cf_WriteFloat(outfile, shippage->ship_struct.med_lod_distance);
  cf_WriteFloat(outfile, shippage->ship_struct.lo_lod_distance);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_ARMOR_SCALAR);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, shippage->ship_struct.armor_scalar);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, shippage->ship_struct.flags);

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    int j;
    int size;

    cf_WriteByte(outfile, SHIPPAGE_COMMAND_WB_INFO);
    size = sizeof(otype_wb_info);
    size++; // add a byte for the wb index

    cf_WriteByte(outfile, size);

    cf_WriteByte(outfile, i);
    for (j = 0; j < MAX_WB_GUNPOINTS; j++)
      cf_WriteShort(outfile, shippage->ship_struct.static_wb[i].gp_weapon_index[j]);
    cf_WriteShort(outfile, shippage->ship_struct.static_wb[i].aiming_gp_index);

    cf_WriteByte(outfile, shippage->ship_struct.static_wb[i].num_masks);
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_WriteByte(outfile, shippage->ship_struct.static_wb[i].gp_fire_masks[j]);
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_WriteFloat(outfile, shippage->ship_struct.static_wb[i].gp_fire_wait[j]);

    cf_WriteByte(outfile, shippage->ship_struct.static_wb[i].aiming_flags);
    cf_WriteFloat(outfile, shippage->ship_struct.static_wb[i].aiming_3d_dot);
    cf_WriteFloat(outfile, shippage->ship_struct.static_wb[i].aiming_3d_dist);
    cf_WriteFloat(outfile, shippage->ship_struct.static_wb[i].aiming_XZ_dot);
  }

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_WB_FLAGS);
  cf_WriteByte(outfile, MAX_PLAYER_WEAPONS);
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++)
    cf_WriteByte(outfile, shippage->ship_struct.static_wb[i].flags);

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_WB_QUADMASK);
  cf_WriteByte(outfile, MAX_PLAYER_WEAPONS);
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++)
    cf_WriteByte(outfile, shippage->ship_struct.static_wb[i].gp_quad_fire_mask);

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      cf_WriteByte(outfile, SHIPPAGE_COMMAND_WB_WEAPON);
      size = strlen(shippage->weapon_name[i][j]) + 1 + 2; // 1 for the null charactor and 2 for the 2 indices

      cf_WriteByte(outfile, size);

      cf_WriteByte(outfile, i);
      cf_WriteByte(outfile, j);
      cf_WriteString(outfile, shippage->weapon_name[i][j]);
    }
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      cf_WriteByte(outfile, SHIPPAGE_COMMAND_WB_FIRE_SOUND);
      size = strlen(shippage->fire_sound_name[i][j]) + 1 + 2; // 1 for the null charactor and 2 for the 2 indices

      cf_WriteByte(outfile, size);

      cf_WriteByte(outfile, i);
      cf_WriteByte(outfile, j);
      cf_WriteString(outfile, shippage->fire_sound_name[i][j]);
    }
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    cf_WriteByte(outfile, SHIPPAGE_COMMAND_FIRE_FLAGS);
    cf_WriteByte(outfile, 2);

    cf_WriteByte(outfile, i);
    cf_WriteByte(outfile, shippage->ship_struct.fire_flags[i]);
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    cf_WriteByte(outfile, SHIPPAGE_COMMAND_RESOURCE_USAGE);
    cf_WriteByte(outfile, 9);

    cf_WriteByte(outfile, i);
    cf_WriteFloat(outfile, shippage->ship_struct.static_wb[i].energy_usage);
    cf_WriteFloat(outfile, shippage->ship_struct.static_wb[i].ammo_usage);
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    if (shippage->firing_sound_name[i][0] != 0) {
      cf_WriteByte(outfile, SHIPPAGE_COMMAND_FIRING_SOUND);
      size = strlen(shippage->firing_sound_name[i]) + 1 + 1; // 1 for the null charactor and 1 for the index
      cf_WriteByte(outfile, size);
      cf_WriteByte(outfile, i);
      cf_WriteString(outfile, shippage->firing_sound_name[i]);
    }
  }
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    if (shippage->release_sound_name[i][0] != 0) {
      cf_WriteByte(outfile, SHIPPAGE_COMMAND_RELEASE_SOUND);
      size = strlen(shippage->release_sound_name[i]) + 1 + 1; // 1 for the null charactor and 1 for the index
      cf_WriteByte(outfile, size);
      cf_WriteByte(outfile, i);
      cf_WriteString(outfile, shippage->release_sound_name[i]);
    }
  }
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    if (shippage->spew_powerup_name[i][0] != 0) {
      cf_WriteByte(outfile, SHIPPAGE_COMMAND_SPEW_POWERUP);
      size = strlen(shippage->spew_powerup_name[i]) + 1 + 1; // 1 for the null charactor and 1 for the index
      cf_WriteByte(outfile, size);
      cf_WriteByte(outfile, i);
      cf_WriteString(outfile, shippage->spew_powerup_name[i]);
    }
  }
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    cf_WriteByte(outfile, SHIPPAGE_COMMAND_MAX_AMMO);
    cf_WriteByte(outfile, 5);

    cf_WriteByte(outfile, i);
    cf_WriteInt(outfile, shippage->ship_struct.max_ammo[i]);
  }

  cf_WriteByte(outfile, SHIPPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}

// Given an open file pointer and a ship_page struct, writes that ship page out
void mng_WriteNewShipPage(CFILE *outfile, mngs_ship_page *shippage) {
  int i;

  ASSERT(outfile != NULL);
  ASSERT(shippage != NULL);

  int offset = StartManagePage(outfile, PAGETYPE_SHIP);

  cf_WriteShort(outfile, SHIPPAGE_VERSION);

  cf_WriteString(outfile, shippage->ship_struct.name);

  cf_WriteString(outfile, shippage->ship_struct.cockpit_name);

  cf_WriteString(outfile, shippage->ship_struct.hud_config_name);

  // Write out its models name
  cf_WriteString(outfile, shippage->image_name);
  cf_WriteString(outfile, shippage->dying_image_name);
  cf_WriteString(outfile, shippage->med_image_name);
  cf_WriteString(outfile, shippage->lo_image_name);

  // Write out lod distance
  cf_WriteFloat(outfile, shippage->ship_struct.med_lod_distance);
  cf_WriteFloat(outfile, shippage->ship_struct.lo_lod_distance);

  mng_WritePhysicsChunk(&shippage->ship_struct.phys_info, outfile);

  cf_WriteFloat(outfile, shippage->ship_struct.size);
  cf_WriteFloat(outfile, shippage->ship_struct.armor_scalar);
  cf_WriteInt(outfile, shippage->ship_struct.flags);

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    int j;

    cf_WriteByte(outfile, shippage->ship_struct.fire_flags[i]);
    cf_WriteString(outfile, shippage->firing_sound_name[i]);
    cf_WriteString(outfile, shippage->release_sound_name[i]);
    cf_WriteString(outfile, shippage->spew_powerup_name[i]);
    cf_WriteInt(outfile, shippage->ship_struct.max_ammo[i]);

    mng_WriteWeaponBatteryChunk(&shippage->ship_struct.static_wb[i], outfile);

    for (j = 0; j < MAX_WB_GUNPOINTS; j++)
      cf_WriteString(outfile, shippage->fire_sound_name[i][j]);

    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_WriteString(outfile, shippage->weapon_name[i][j]);
  }

  EndManagePage(outfile, offset);
}

// Reads a ship page from an open file.  Returns 0 on error.
int mng_ReadNewShipPage(CFILE *infile, mngs_ship_page *shippage) {
  int i, j;

  ASSERT(infile != NULL);

  // Defaults
  memset(shippage, 0, sizeof(mngs_ship_page));

  int version = cf_ReadShort(infile);

  // Read In misc names
  cf_ReadString(shippage->ship_struct.name, PAGENAME_LEN, infile);
  cf_ReadString(shippage->ship_struct.cockpit_name, PAGENAME_LEN, infile);
  cf_ReadString(shippage->ship_struct.hud_config_name, PAGENAME_LEN, infile);

  // Read in model names
  cf_ReadString(shippage->image_name, PAGENAME_LEN, infile);
  cf_ReadString(shippage->dying_image_name, PAGENAME_LEN, infile);
  cf_ReadString(shippage->med_image_name, PAGENAME_LEN, infile);
  cf_ReadString(shippage->lo_image_name, PAGENAME_LEN, infile);

  // read lod distance
  shippage->ship_struct.med_lod_distance = cf_ReadFloat(infile);
  shippage->ship_struct.lo_lod_distance = cf_ReadFloat(infile);

  // Read physics
  mng_ReadPhysicsChunk(&shippage->ship_struct.phys_info, infile);

  shippage->ship_struct.size = cf_ReadFloat(infile);
  shippage->ship_struct.armor_scalar = cf_ReadFloat(infile);
  shippage->ship_struct.flags = cf_ReadInt(infile);

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    shippage->ship_struct.fire_flags[i] = cf_ReadByte(infile);
    cf_ReadString(shippage->firing_sound_name[i], PAGENAME_LEN, infile);
    cf_ReadString(shippage->release_sound_name[i], PAGENAME_LEN, infile);
    cf_ReadString(shippage->spew_powerup_name[i], PAGENAME_LEN, infile);
    shippage->ship_struct.max_ammo[i] = cf_ReadInt(infile);

    if (version >= 6)
      mng_ReadWeaponBatteryChunk(&shippage->ship_struct.static_wb[i], infile, 2);
    else
      mng_ReadWeaponBatteryChunk(&shippage->ship_struct.static_wb[i], infile, 1);

    for (j = 0; j < MAX_WB_GUNPOINTS; j++)
      cf_ReadString(shippage->fire_sound_name[i][j], PAGENAME_LEN, infile);

    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_ReadString(shippage->weapon_name[i][j], PAGENAME_LEN, infile);
  }

  // Mark the newly filled structure as used
  shippage->ship_struct.used = 1;

  // Bash Fusion recharge times for the ships
  if (!stricmp(shippage->ship_struct.name, "Pyro-GL")) {
    // Pyro-GL
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      shippage->ship_struct.static_wb[FUSION_INDEX].gp_fire_wait[j] = 0.66f;
  } else if (!stricmp(shippage->ship_struct.name, "Phoenix")) {
    // Phoenix
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      shippage->ship_struct.static_wb[FUSION_INDEX].gp_fire_wait[j] = 0.792f;
  } else if (!stricmp(shippage->ship_struct.name, "Magnum-AHT")) {
    // Magnum
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      shippage->ship_struct.static_wb[FUSION_INDEX].gp_fire_wait[j] = 1.122f;
  } else {
    // Other
  }

  return 1; // successfully read
}

// Reads a ship page from an open file.  Returns 0 on error.
int mng_ReadShipPage(CFILE *infile, mngs_ship_page *shippage) {
  int done = 0;
  char command;
  uint8_t len;
  int i;
  int version = 0;

  if (!Old_table_method)
    return mng_ReadNewShipPage(infile, shippage);

  strcpy(shippage->dying_image_name, "");
  ASSERT(infile != NULL);

  // Defaults
  memset(shippage, 0, sizeof(mngs_ship_page));
  shippage->ship_struct.armor_scalar = 1.0;

  strcpy(shippage->med_image_name, "");
  strcpy(shippage->lo_image_name, "");

  shippage->ship_struct.med_lod_distance = DEFAULT_MED_LOD_DISTANCE;
  shippage->ship_struct.lo_lod_distance = DEFAULT_LO_LOD_DISTANCE;

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    shippage->ship_struct.static_wb[i].aiming_3d_dist = 1.0;
    shippage->ship_struct.static_wb[i].num_masks = 1;
    shippage->ship_struct.fire_flags[i] = 0;
    shippage->firing_sound_name[i][0] = 0;
    shippage->release_sound_name[i][0] = 0;
    shippage->spew_powerup_name[i][0] = 0;
    shippage->ship_struct.max_ammo[i] = 0;
  }

  while (!done) {
    // Read in command byte then read in the length of that commands data

    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);

    switch (command) {
    case SHIPPAGE_COMMAND_END:
      done = 1;
      break;
    case SHIPPAGE_COMMAND_VERSION:
      version = cf_ReadByte(infile);
      break;
    case SHIPPAGE_COMMAND_IMAGE_NAME: // the name of the ship model
      for (i = 0; i < PAGENAME_LEN; i++)
        shippage->image_name[i] = cf_ReadByte(infile);
      break;
    case SHIPPAGE_COMMAND_DYING_IMAGE_NAME:
      cf_ReadString(shippage->dying_image_name, PAGENAME_LEN, infile);
      break;
    case SHIPPAGE_COMMAND_LOD_MODELS: // the name of the lower res models
      cf_ReadString(shippage->med_image_name, len + 1, infile);
      cf_ReadString(shippage->lo_image_name, len + 1, infile);
      break;
    case SHIPPAGE_COMMAND_LOD_DISTANCE:
      shippage->ship_struct.med_lod_distance = cf_ReadFloat(infile);
      shippage->ship_struct.lo_lod_distance = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_COCKPIT_NAME:
      cf_ReadString(shippage->ship_struct.cockpit_name, PAGENAME_LEN, infile);
      break;
    case SHIPPAGE_COMMAND_HUD_NAME:
      cf_ReadString(shippage->ship_struct.hud_config_name, PAGENAME_LEN, infile);
      break;
    case SHIPPAGE_COMMAND_NAME:
      for (i = 0; i < PAGENAME_LEN; i++)
        shippage->ship_struct.name[i] = cf_ReadByte(infile);
      break;
    case SHIPPAGE_COMMAND_SIZE:
      shippage->ship_struct.size = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_ARMOR_SCALAR:
      shippage->ship_struct.armor_scalar = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_MASS:
      shippage->ship_struct.phys_info.mass = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_DRAG:
      shippage->ship_struct.phys_info.drag = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_WIGGLE_AMPLITUDE:
      shippage->ship_struct.phys_info.wiggle_amplitude = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_THRUST:
      shippage->ship_struct.phys_info.full_thrust = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_ROTTHRUST:
      shippage->ship_struct.phys_info.full_rotthrust = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_TURNROLLRATE:
      shippage->ship_struct.phys_info.max_turnroll_rate = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_ROTDRAG:
      shippage->ship_struct.phys_info.rotdrag = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_WIGGLE_PER_SEC:
      shippage->ship_struct.phys_info.wiggles_per_sec = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_TURNROLL_RATIO:
      shippage->ship_struct.phys_info.turnroll_ratio = cf_ReadFloat(infile);
      break;
    case SHIPPAGE_COMMAND_PHYSICS_FLAGS:
      shippage->ship_struct.phys_info.flags = cf_ReadInt(infile);
      break;
    case SHIPPAGE_COMMAND_FLAGS:
      shippage->ship_struct.flags = cf_ReadInt(infile);
      break;
    case SHIPPAGE_COMMAND_WB_FLAGS: {
      for (int i = 0; i < MAX_PLAYER_WEAPONS; i++)
        shippage->ship_struct.static_wb[i].flags = cf_ReadByte(infile);
    } break;
    case SHIPPAGE_COMMAND_WB_QUADMASK: {
      for (int i = 0; i < MAX_PLAYER_WEAPONS; i++)
        shippage->ship_struct.static_wb[i].gp_quad_fire_mask = cf_ReadByte(infile);
    } break;
    case SHIPPAGE_COMMAND_WB_INFO: {
      int i, j;
      i = cf_ReadByte(infile);

      if (version < 1) {
        for (j = 0; j < MAX_WB_GUNPOINTS; j++)
          shippage->ship_struct.static_wb[i].gp_weapon_index[j] = cf_ReadInt(infile);
        shippage->ship_struct.static_wb[i].aiming_gp_index = cf_ReadInt(infile);
      } else {
        for (j = 0; j < MAX_WB_GUNPOINTS; j++)
          shippage->ship_struct.static_wb[i].gp_weapon_index[j] = cf_ReadShort(infile);
        shippage->ship_struct.static_wb[i].aiming_gp_index = cf_ReadShort(infile);
      }
      shippage->ship_struct.static_wb[i].num_masks = cf_ReadByte(infile);
      for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
        shippage->ship_struct.static_wb[i].gp_fire_masks[j] = cf_ReadByte(infile);
      for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
        shippage->ship_struct.static_wb[i].gp_fire_wait[j] = cf_ReadFloat(infile);

      shippage->ship_struct.static_wb[i].aiming_flags = cf_ReadByte(infile);
      shippage->ship_struct.static_wb[i].aiming_3d_dot = cf_ReadFloat(infile);
      shippage->ship_struct.static_wb[i].aiming_3d_dist = cf_ReadFloat(infile);
      shippage->ship_struct.static_wb[i].aiming_XZ_dot = cf_ReadFloat(infile);
      break;
    }

    case SHIPPAGE_COMMAND_WB_WEAPON: {
      int i, j;

      i = cf_ReadByte(infile);
      j = cf_ReadByte(infile);
      cf_ReadString(shippage->weapon_name[i][j], len - 1, infile);
      break;
    }
    case SHIPPAGE_COMMAND_WB_FIRE_SOUND: {
      int i, j;

      i = cf_ReadByte(infile);
      j = cf_ReadByte(infile);
      cf_ReadString(shippage->fire_sound_name[i][j], len - 1, infile);
      break;
    }
    case SHIPPAGE_COMMAND_FIRING_SOUND: {
      int i = cf_ReadByte(infile);
      cf_ReadString(shippage->firing_sound_name[i], len, infile);
      break;
    }
    case SHIPPAGE_COMMAND_RELEASE_SOUND: {
      int i = cf_ReadByte(infile);
      cf_ReadString(shippage->release_sound_name[i], len, infile);
      break;
    }
    case SHIPPAGE_COMMAND_SPEW_POWERUP: {
      int i = cf_ReadByte(infile);
      cf_ReadString(shippage->spew_powerup_name[i], len, infile);
      break;
    }
    case SHIPPAGE_COMMAND_FIRE_FLAGS: {
      uint8_t slot;

      slot = cf_ReadByte(infile);
      shippage->ship_struct.fire_flags[slot] = cf_ReadByte(infile);
      break;
    }
    case SHIPPAGE_COMMAND_MAX_AMMO: {
      uint8_t slot;

      slot = cf_ReadByte(infile);
      shippage->ship_struct.max_ammo[slot] = cf_ReadInt(infile);
      break;
    }
    case SHIPPAGE_COMMAND_RESOURCE_USAGE: {
      uint8_t slot;

      slot = cf_ReadByte(infile);
      shippage->ship_struct.static_wb[slot].energy_usage = cf_ReadFloat(infile);
      shippage->ship_struct.static_wb[slot].ammo_usage = cf_ReadFloat(infile);
      break;
    }
    default:
      // Ignore the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }

  for (int xxx = 0; xxx < MAX_WBS_PER_OBJ; xxx++) {
    if ((version < 5) && (shippage->ship_struct.fire_flags[xxx] & 2)) {
      shippage->ship_struct.static_wb[xxx].flags |= WBF_ON_OFF;
    }
  }

  shippage->ship_struct.phys_info.num_bounces = -1;
  shippage->ship_struct.phys_info.coeff_restitution = 1.0f;

  // Mark the newly filled structure as used
  shippage->ship_struct.used = 1;

  return 1; // successfully read
}

// Reads in the ship named "name" into shippage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificShipPage(char *name, mngs_ship_page *shippage, int offset) {
  CFILE *infile;
  uint8_t pagetype;
  int done = 0, found = 0;
  int first_try = 1;
  std::filesystem::path tablename;

  if (Loading_locals) {
    infile = cfopen(LocalTableFilename, "rb");
  } else if (Loading_addon_table != -1) {
    infile = cfopen(AddOnDataTables[Loading_addon_table].AddOnTableFilename, "rb");
  } else {
    if (Network_up && Starting_editor) {
      int farg = FindArg("-filter");

      if (farg)
        tablename = GameArgs[farg + 1];
      else
        tablename = LocalTableDir / NET_TABLE;

      infile = cfopen(tablename, "rb");
    } else {
      infile = NULL;
      if (TablefileNameOverride) {
        infile = cfopen(TablefileNameOverride, "rb");
      }

      if (!infile)
        infile = cfopen(TableFilename, "rb");
    }
  }

  if (!infile) {
    mprintf(0, "Couldn't open table file to find ship!\n");
    Int3();
    return 0;
  }

try_again:;

  if (offset)
    cfseek(infile, offset, SEEK_SET);

  // Read in the entire page file until we find the page we want
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);

    // If not a ship page, just read it in and ignore it
    if (pagetype != PAGETYPE_SHIP) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewShipPage(infile, shippage);

    if (!stricmp(name, shippage->ship_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    }
  }

  cfclose(infile);

  if (!found && first_try) {
    done = first_try = 0;
    infile = cfopen("extra.gam", "rb");
    if (infile)
      goto try_again;
  }

  return found; // successful!
}

// Given a ship page, allocs a ship and calls AssignShipPageToShip to actually
// load models and values. Rturns ship handle on success, -1 if fail
int mng_SetAndLoadShip(mngs_ship_page *shippage, CFILE *infile) {
  int n;

  n = AllocShip();
  if (n < 0)
    return -1;
  if (!mng_AssignShipPageToShip(shippage, n, infile))
    return -1;

  return n;
}

// Given a shippage and a ship handle, attempts to make ship n correspond to
// to the shippage.
// Returns 1 on success, 0 otherwise
int mng_AssignShipPageToShip(mngs_ship_page *shippage, int n, CFILE *infile) {
  ship *shippointer = &Ships[n];
  int img_handle;
  int i, j;

  // copy our values
  memcpy(shippointer, &shippage->ship_struct, sizeof(ship));
  strcpy(shippointer->name, shippage->ship_struct.name);

  // First see if our image differs from the one on the net
  // If it is, make a copy
  // If its a release version, don't do any of this

#ifndef RELEASE
  if (Network_up) {
    UpdatePrimitive(LocalModelsDir / shippage->image_name, NetModelsDir / shippage->image_name, shippage->image_name,
                    PAGETYPE_SHIP, shippointer->name);

    if (stricmp("INVALID IMAGE NAME", shippage->dying_image_name) != 0 && shippage->dying_image_name[0] != 0) {
      UpdatePrimitive(LocalModelsDir / shippage->dying_image_name, NetModelsDir / shippage->dying_image_name,
                      shippage->dying_image_name, PAGETYPE_SHIP, shippointer->name);
    }

    if (shippage->med_image_name[0] != 0) {
      UpdatePrimitive(LocalModelsDir / shippage->med_image_name, NetModelsDir / shippage->med_image_name,
                      shippage->med_image_name, PAGETYPE_SHIP, shippointer->name);
    }

    if (shippage->lo_image_name[0] != 0) {
      UpdatePrimitive(LocalModelsDir / shippage->lo_image_name, NetModelsDir / shippage->lo_image_name,
                      shippage->lo_image_name, PAGETYPE_SHIP, shippointer->name);
    }
  }
#endif

  // Try and load our ship model from the disk

  img_handle = LoadPolyModel(shippage->image_name, 1);

  if (img_handle < 0) {
    mprintf(0, "Couldn't load file '%s' in AssignShipPage...\n", shippage->image_name);
    shippointer->model_handle = -1;
    return 0;
  } else
    shippointer->model_handle = img_handle;

  if (stricmp("INVALID IMAGE NAME", shippage->dying_image_name) && shippage->dying_image_name[0] != 0) {
    img_handle = LoadPolyModel(shippage->dying_image_name, 1);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load file '%s' in AssignShipPage...\n", shippage->dying_image_name);
      shippointer->dying_model_handle = -1;
      return 0;
    } else
      shippointer->dying_model_handle = img_handle;
  } else
    shippointer->dying_model_handle = -1;

  // Load lo-res stuff
  if (shippage->med_image_name[0] != 0) {
    img_handle = LoadPolyModel(shippage->med_image_name, 1);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load file '%s' in AssignShipPage...\n", shippage->med_image_name);
      shippointer->med_render_handle = -1;
      return 0;
    } else
      shippointer->med_render_handle = img_handle;
  } else
    shippointer->med_render_handle = -1;

  if (shippage->lo_image_name[0] != 0) {
    img_handle = LoadPolyModel(shippage->lo_image_name, 1);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load file '%s' in AssignGenericPage...\n", shippage->lo_image_name);
      shippointer->lo_render_handle = -1;
      return 0;
    } else
      shippointer->lo_render_handle = img_handle;
  } else
    shippointer->lo_render_handle = -1;

  // Try and load the various weapons
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      if (shippage->weapon_name[i][j][0] != '\0') {
        int weapon_handle = mng_GetGuaranteedWeaponPage(shippage->weapon_name[i][j], infile);

        if (weapon_handle < 0) {
          mprintf(0, "Couldn't load weapon file '%s' in AssignPowPage %s...\n", shippage->weapon_name[i][j],
                  shippage->ship_struct.name);
          shippointer->static_wb[i].gp_weapon_index[j] = LASER_INDEX;
        } else
          shippointer->static_wb[i].gp_weapon_index[j] = weapon_handle;
      } else
        shippointer->static_wb[i].gp_weapon_index[j] = LASER_INDEX;
    }
  }

  // Try and load the various weapons
  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      if (shippage->fire_sound_name[i][j][0] != '\0') {
        int fire_sound_handle = mng_GetGuaranteedSoundPage(shippage->fire_sound_name[i][j], infile);

        if (fire_sound_handle < 0) {
          mprintf(0, "Couldn't load fire_sound file '%s' in AssignPowPage %s...\n", shippage->fire_sound_name[i][j],
                  shippage->ship_struct.name);
          shippointer->static_wb[i].fm_fire_sound_index[j] = SOUND_NONE_INDEX;
        } else
          shippointer->static_wb[i].fm_fire_sound_index[j] = fire_sound_handle;
      } else
        shippointer->static_wb[i].fm_fire_sound_index[j] = SOUND_NONE_INDEX;
    }
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    if (shippage->firing_sound_name[i][0] != 0) {
      int sound_handle = mng_GetGuaranteedSoundPage(shippage->firing_sound_name[i], infile);

      if (sound_handle < 0) {
        mprintf(0, "Couldn't load firing_sound file '%s' in AssignPowPage %s...\n", shippage->firing_sound_name[i],
                shippage->ship_struct.name);
        shippointer->firing_sound[i] = SOUND_NONE_INDEX;
      } else
        shippointer->firing_sound[i] = sound_handle;
    } else
      shippointer->firing_sound[i] = -1;

    if (shippage->release_sound_name[i][0] != 0) {
      int sound_handle = mng_GetGuaranteedSoundPage(shippage->release_sound_name[i], infile);

      if (sound_handle < 0) {
        mprintf(0, "Couldn't load firing_sound file '%s' in AssignPowPage %s...\n", shippage->release_sound_name[i],
                shippage->ship_struct.name);
        shippointer->firing_release_sound[i] = SOUND_NONE_INDEX;
      } else
        shippointer->firing_release_sound[i] = sound_handle;
    } else
      shippointer->firing_release_sound[i] = -1;

    if (shippage->spew_powerup_name[i][0] != 0) {
      shippointer->spew_powerup[i] = mng_GetGuaranteedGenericPage(shippage->spew_powerup_name[i], infile);
      if (shippointer->spew_powerup[i] > -1 &&
          Object_info[shippointer->spew_powerup[i]].type != OBJ_POWERUP) { // DAJ -1FIX
        mprintf(1, "Spew powerup is not a powerup!  Setting to none.\n");
        shippointer->spew_powerup[i] = -1;
      }
    } else
      shippointer->spew_powerup[i] = -1;
  }

  return 1;
}

// Copies values from a ship into a ship_page
void mng_AssignShipToShipPage(int n, mngs_ship_page *shippage) {
  ship *shippointer = &Ships[n];
  int i, j;

  // Assign the  values
  memcpy(&shippage->ship_struct, shippointer, sizeof(ship));

  strcpy(shippage->ship_struct.name, shippointer->name);

  if (shippointer->model_handle != -1)
    strcpy(shippage->image_name, Poly_models[shippointer->model_handle].name);
  else
    strcpy(shippage->image_name, "");

  if (shippointer->dying_model_handle != -1)
    strcpy(shippage->dying_image_name, Poly_models[shippointer->dying_model_handle].name);
  else
    strcpy(shippage->dying_image_name, "");

  if (shippointer->med_render_handle != -1)
    strcpy(shippage->med_image_name, Poly_models[shippointer->med_render_handle].name);
  else
    strcpy(shippage->med_image_name, "");

  if (shippointer->lo_render_handle != -1)
    strcpy(shippage->lo_image_name, Poly_models[shippointer->lo_render_handle].name);
  else
    strcpy(shippage->lo_image_name, "");

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      if (shippointer->static_wb[i].gp_weapon_index[j] >= 0)
        strcpy(shippage->weapon_name[i][j], Weapons[shippointer->static_wb[i].gp_weapon_index[j]].name);
      else
        strcpy(shippage->weapon_name[i][j], "Laser");
    }
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      if (shippointer->static_wb[i].fm_fire_sound_index[j] >= 0)
        strcpy(shippage->fire_sound_name[i][j], Sounds[shippointer->static_wb[i].fm_fire_sound_index[j]].name);
      else
        strcpy(shippage->fire_sound_name[i][j], "");
    }
  }

  for (i = 0; i < MAX_PLAYER_WEAPONS; i++) {

    if (shippointer->firing_sound[i] != -1)
      strcpy(shippage->firing_sound_name[i], Sounds[shippointer->firing_sound[i]].name);
    else
      shippage->firing_sound_name[i][0] = 0;

    if (shippointer->firing_release_sound[i] != -1)
      strcpy(shippage->release_sound_name[i], Sounds[shippointer->firing_release_sound[i]].name);
    else
      shippage->release_sound_name[i][0] = 0;

    if (shippointer->spew_powerup[i] != -1) {
      if (Object_info[shippointer->spew_powerup[i]].type != OBJ_POWERUP) {
        mprintf(1, "Spew powerup is not a powerup!  Setting to none.\n");
        shippage->spew_powerup_name[i][0] = 0;
      } else
        strcpy(shippage->spew_powerup_name[i], Object_info[shippointer->spew_powerup[i]].name);
    } else
      shippage->spew_powerup_name[i][0] = 0;
  }
}

// Loads a ship found in the net table file.  It then allocs a ship and
// then calls SetAndLoadShip to actually load in any images/models associated
// with it
void mng_LoadNetShipPage(CFILE *infile, bool overlay) {
  mngs_ship_page shippage;
  // Have to zero out all fields that are not in the page (some physics fields), else we
  // end up with random values for initial velocity and the such...  :)
  memset(&shippage, 0, sizeof(mngs_ship_page));

  if (mng_ReadNewShipPage(infile, &shippage)) {
    int n = FindShipName(shippage.ship_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING SHIP %s\n", shippage.ship_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_SHIP, shippage.ship_struct.name, 0);
        mng_AssignShipPageToShip(&shippage, n);
      }
      return;
    }
    int ret = mng_SetAndLoadShip(&shippage, infile);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load shippage named %s!\n", shippage.ship_struct.name);
}

// Reads a ship page from a local table file.  It then allocs a ship and
// loads any images/models associated with that ship
void mng_LoadLocalShipPage(CFILE *infile) {
  mngs_ship_page shippage;
  int ok = 0;
  // Have to zero out all fields that are not in the page (some physics fields), else we
  // end up with random values for initial velocity and the such...  :)
  memset(&shippage, 0, sizeof(mngs_ship_page));

  if (mng_ReadNewShipPage(infile, &shippage)) {
    // Check to see if this is a local copy that is supposed
    // to go over a network copy (supersede the net copy)

    int i = FindShipName(shippage.ship_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;

      strcpy(pl.name, shippage.ship_struct.name);
      pl.pagetype = PAGETYPE_SHIP;

      /*if (Network_up && Stand_alone==0)
      {
              int locked=mng_CheckIfPageOwned(&pl,TableUser);
              if (locked!=1)
                      Int3(); // Your local vs net copies of the lock file do not match
      }*/
      ok = 1;
      bool need_to_load_page = true;

      if (Loading_addon_table != -1) {
        AddOnTablefile *addon;
        int tidx;

        // see if we really need to load this page
        // check to see if we already have loaded this page (because it was
        // a dependancy of another)
        addon = &AddOnDataTables[Loading_addon_table];
        for (tidx = 0; tidx < addon->Num_addon_tracklocks; tidx++) {
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_SHIP &&
              !stricmp(addon->Addon_tracklocks[tidx].name, shippage.ship_struct.name)) {
            // found it!!
            mprintf(0, "ShipPage: %s previously loaded\n", shippage.ship_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_SHIP, shippage.ship_struct.name, 0);
        mng_AssignShipPageToShip(&shippage, i);

        // For addon data
        if (ok && Loading_addon_table != -1) {
          // this is an overlay of some sort..see which we are overlaying
          int overlay = 1;
          int addidx, tidx;
          bool found = false;
          for (addidx = Num_addon_tables - 1; addidx >= 0; addidx--) {
            if (addidx == Loading_addon_table)
              continue;
            AddOnTablefile *addon = &AddOnDataTables[addidx];

            // look for the page in this table file
            for (tidx = 0; tidx < addon->Num_addon_tracklocks; tidx++) {
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_SHIP &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, shippage.ship_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_SHIP, shippage.ship_struct.name, overlay);
        }
      }
    } else {
      // This is a local ship that has never been checked in
      if ((i = mng_SetAndLoadShip(&shippage, infile)) < 0)
        ok = 0;
      else
        ok = 1;

      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_SHIP, shippage.ship_struct.name, 0);
    }

    ASSERT(ok == 1);

    if (Loading_addon_table == -1)
      mng_AllocTrackLock(shippage.ship_struct.name, PAGETYPE_SHIP);

    if (i != -1) {
      poly_model *pm = GetPolymodelPointer(Ships[i].model_handle); // page in the model
      if (pm->n_attach < 3) {                                      // check for enough attach points
        DataError("Model <%s> for ship <%s> has %d attach points (must have at least 3)\n", pm->name, Ships[i].name,
                  pm->n_attach);
      }
      FreePolymodelData(
          Ships[i].model_handle); // Unload the data so it will get loaded later after the textures are in memory
    }
  } else

    mprintf(0, "Could not load shippage named %s!\n", shippage.ship_struct.name);
}
