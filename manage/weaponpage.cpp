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

 * $Logfile: /DescentIII/Main/manage/weaponpage.cpp $
 * $Revision: 71 $
 * $Date: 10/08/01 4:20p $
 * $Author: Matt $
 *
 * For loading/saving of weapon types
 *
 * $Log: /DescentIII/Main/manage/weaponpage.cpp $
 *
 * 71    10/08/01 4:20p Matt
 * Added system to check for errors when reading in add-on data.
 *
 * 69    9/06/01 10:32a Matt
 * Added code to fix problem poping add-on pages when the original pages
 * were in the extra.gam file.
 *
 * 68    10/26/99 4:26p Jeff
 * handle extra.gam
 *
 * 67    10/26/99 3:31p Jeff
 * handle extra.gam addon tablefile
 *
 * 66    9/18/99 8:49p Jeff
 * fixed bug with addon pages that have dependencies on other pages in the
 * addon tablefile
 *
 * 65    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 64    7/22/99 4:38p Jason
 * made EMD time out faster to help balance it out
 *
 * 63    4/14/99 1:34a Jeff
 * fixed case mismatched #includes
 *
 * 62    4/12/99 12:49p Jeff
 * added recoil_force to weapon's page
 *
 * 61    3/08/99 7:48p Jeff
 * oem hack for napalm barrel
 *
 * 60    3/04/99 4:47p Jason
 * temp fix (ie BAD HACK) for OEM table file woes
 *
 * 59    3/04/99 1:47p Jason
 * fixed some manage problems
 *
 * 58    2/22/99 2:03p Jason
 * added different damages for players and generics
 *
 * 57    1/13/99 7:05a Jeff
 * put #ifdef around #include <windows.h>
 *
 * 56    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 55    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 54    11/05/98 7:55p Jason
 * changes for new manage system
 *
 * 53    11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 52    10/15/98 6:46p Chris
 * Added custom size for weapons
 *
 * 51    10/09/98 2:55p Jason
 * fixed bug with my last rev
 *
 * 50    10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 49    10/08/98 10:03p Jason
 * more filtered table file stuff
 *
 * 48    9/18/98 3:58p Jason
 * change weapon reordering to do countermeasure weapons after generics
 *
 * 47    9/01/98 4:41p Matt
 * Removed obsolete fields in the weapon structure
 *
 * 46    8/24/98 2:37p Jason
 * made table file more efficient with regards to invalid names
 *
 * 45    8/06/98 1:00p Chris
 * Added new homing flags
 *
 * 44    7/30/98 11:09a Jason
 * added weapons that freeze and deform terrain
 *
 * 43    7/28/98 12:29p Jason
 * chagned text string
 *
 * 42    7/01/98 12:11p Jason
 * added countermeasures
 *
 * 41    6/26/98 5:26p Sean
 * fixed some remaining weapons issues
 *
 * 40    6/22/98 6:26p Jason
 * added gravity field effect for weapons
 *
 * 39    6/19/98 12:04p Jason
 *
 * 38    6/12/98 1:06p Jason
 * added smart loading from local table file
 *
 * 37    5/25/98 8:36p Matt
 * Added code to set different sizes for different weapon scorch marks.
 * Also, don't leave scorch marks on lights.
 *
 * 36    5/25/98 6:39p Jason
 * got icons working for weapons
 *
 * 35    5/25/98 4:16p Jason
 * added more verbose mprintfs
 *
 * 34    5/22/98 12:34p Matt
 * Added scorch mark/bullet hole system.
 *
 * 33    5/19/98 5:09a Chris
 * Initial values are better
 *
 * 32    5/19/98 5:02a Chris
 * More adjustments
 *
 * 31    5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 30    5/13/98 6:35p Chris
 * Fixed problems with hit die dot
 *
 * 29    5/07/98 1:41p Chris
 * Added hit_death_dot
 *
 * 28    5/04/98 6:08p Jason
 * sped up predictive pagefile loading
 *
 * 27    4/07/98 3:31p Jason
 * got particle effects working with weapons
 *
 * 26    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 25    2/23/98 1:22p Jason
 * made FindSpecific* read from the local drive, not the net drive - when
 * starting the editor
 *
 * 24    2/16/98 11:42a Jason
 * added better error checking for checking out files
 *
 * 23    2/11/98 3:52p Jason
 *
 * 22    2/11/98 2:04p Jason
 * got spawning weapons working
 *
 * 21    2/05/98 6:29p Jason
 * added user settable explode time/size
 *
 * 20    2/04/98 9:28p Jason
 * added some new weapons effects
 *
 * 19    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 18    1/15/98 6:22p Jason
 * added safety checks so the network won't copy over a primitive you have
 * held locally
 *
 * 17    12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 16    12/11/97 11:55a Jason
 * better error checking for dependant weapon pages
 *
 * 15    12/04/97 6:59p Jason
 * fixed stupid off-by-one bug in cf_ReadString
 *
 * 14    12/04/97 12:15p Jason
 * gave designers the ability to set their own weapon-to-wall hit vclips
 *
 * 13    12/03/97 11:54a Jason
 * added designer-settable smoketrails
 *
 * 12    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 11    11/14/97 9:55p Jason
 * took out size fix because we changed out minds
 *
 * 10    11/14/97 9:31p Jason
 * automatically adjust size of weapon polymodels
 *
 * 9     10/30/97 5:00p Jason
 * Made weapons use generic lighting code
 *
 * 8     10/20/97 4:46p Jason
 * changes for explosions
 *
 * 7     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 6     9/10/97 11:44a Chris
 * Added major functionality for wb info
 * FIXED a big remapping bug
 *
 * 5     9/03/97 3:54p Jason
 * got objects to cast light
 *
 * 4     8/08/97 11:44a Jason
 * got rid of annoying sound loading of a blank string
 *
 * 3     8/07/97 5:27p Chris
 * Expanded the weapon system
 *
 * 2     8/06/97 4:34p Chris
 * Expanded the weapons page
 *
 * 14    5/15/97 6:24p Mark
 * fixed small bugs with sound loading invalid names
 *
 * 13    5/08/97 12:41p Jason
 * made manage system work with device dependant path names
 *
 * 12    4/28/97 6:46p Jason
 * made ships have multiple gun points
 *
 * 11    4/25/97 6:16p Jason
 * added switcheroo function
 *
 * 10    4/25/97 2:18p Jason
 * added fire_delay functionality
 *
 * 9     4/24/97 5:42p Jason
 * got fireball vclips working
 *
 * 8     4/23/97 3:04p Jason
 * added more stuff to weapon pages
 *
 * 7     4/16/97 11:50a Jason
 * finally got weapons to fire
 *
 * 6     4/14/97 5:09p Jason
 * fixed dumb bug with weapon flags
 *
 * 5     4/14/97 4:35p Jason
 * added thrust field to page file
 *
 * 4     4/14/97 1:50p Jason
 * first pass at getting weapons to fire
 *
 * 3     4/08/97 2:25a Chris
 * Fixed a problem with uninitialized data.  In addition it
 * fixed a problem with the .used flag that would happen
 * 1 out of 2^(sizeof(used_flag)) times (it would be zero
 * when it was supposed to be non-zero)
 *
 * 2     3/31/97 4:35p Jason
 * added weapon page functionality
 *
 * 1     3/31/97 3:40p Jason
 * weaponpage implementation file
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "weapon.h"
#include "weaponpage.h"
#include "mono.h"
#include "pserror.h"
#include "vclip.h"
#include "polymodel.h"
#include "soundpage.h"
#include "soundload.h"
#include "ddio.h"
#include "gametexture.h"
#include "texpage.h"
#include "sounds.h"
#include "genericpage.h"
#include "args.h"

// weaponpage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define WEAPONPAGE_COMMAND_NAME 1
#define WEAPONPAGE_COMMAND_END 2
#define WEAPONPAGE_COMMAND_HUD_IMAGE_NAME 3
#define WEAPONPAGE_COMMAND_VERSION 4
#define WEAPONPAGE_COMMAND_MASS 5
#define WEAPONPAGE_COMMAND_DRAG 6
#define WEAPONPAGE_COMMAND_FLAGS 7
#define WEAPONPAGE_COMMAND_FIRE_IMAGE_NAME 8
// #define WEAPONPAGE_COMMAND_THRUST				9	// not used anymore
#define WEAPONPAGE_COMMAND_FULL_THRUST 10
#define WEAPONPAGE_COMMAND_SOUND_NAME 11
#define WEAPONPAGE_COMMAND_AMMO_USAGE 12
#define WEAPONPAGE_COMMAND_ENERGY_USAGE 13
// #define WEAPONPAGE_COMMAND_EXPLODE_NAME		14	// exploding vclip name (not used anymore)
#define WEAPONPAGE_COMMAND_FIRE_DELAY 15
#define WEAPONPAGE_COMMAND_NUM_SHOTS 16
#define WEAPONPAGE_COMMAND_PHYS_FLAGS 17
#define WEAPONPAGE_COMMAND_SIZE 18
#define WEAPONPAGE_COMMAND_IMPACT_SIZE 19
#define WEAPONPAGE_COMMAND_FLASH_SIZE 20
#define WEAPONPAGE_COMMAND_ROT_DRAG 21
#define WEAPONPAGE_COMMAND_FULL_ROT_THRUST 22
#define WEAPONPAGE_COMMAND_MAX_BOUNCES 23
#define WEAPONPAGE_COMMAND_INIT_VELOCITY 24
#define WEAPONPAGE_COMMAND_INIT_ROT_VEL_X 25
#define WEAPONPAGE_COMMAND_INIT_ROT_VEL_Y 26
#define WEAPONPAGE_COMMAND_INIT_ROT_VEL_Z 27
#define WEAPONPAGE_COMMAND_LIFE_TIME 28
#define WEAPONPAGE_COMMAND_THRUST_TIME 29
#define WEAPONPAGE_COMMAND_WIGGLE_AMP 30
#define WEAPONPAGE_COMMAND_WIGGLE_FREQ 31
#define WEAPONPAGE_COMMAND_COEFF_RESTITUTION 32
#define WEAPONPAGE_COMMAND_LIGHT_CAST 33
#define WEAPONPAGE_COMMAND_DAMAGE 34
#define WEAPONPAGE_COMMAND_BETTER_LIGHT_CAST 35
#define WEAPONPAGE_COMMAND_IMPACT_TIME 36
#define WEAPONPAGE_COMMAND_SMOKE_NAME 37
#define WEAPONPAGE_COMMAND_EXPLOSION_NAME 38 // Wall hit vclip
#define WEAPONPAGE_COMMAND_ALPHA 39
#define WEAPONPAGE_COMMAND_EXPLODE_TIME 40
#define WEAPONPAGE_COMMAND_EXPLODE_SIZE 41
#define WEAPONPAGE_COMMAND_SPAWN_COUNT 42
#define WEAPONPAGE_COMMAND_SPAWN_NAME 43
#define WEAPONPAGE_COMMAND_FIRE_IMAGE_NULL 44
#define WEAPONPAGE_COMMAND_HUD_IMAGE_NULL 45
#define WEAPONPAGE_COMMAND_NAME_NULL 46
#define WEAPONPAGE_COMMAND_PARTICLE_NAME 47
#define WEAPONPAGE_COMMAND_PARTICLE_DATA 48
#define WEAPONPAGE_COMMAND_HIT_DIE_DOT 49
#define WEAPONPAGE_COMMAND_IMPACT_FORCE 50
#define WEAPONPAGE_COMMAND_IMPACT_DAMAGE 51
#define WEAPONPAGE_COMMAND_SCORCH_NAME 52
#define WEAPONPAGE_COMMAND_ICON_NAME 53
#define WEAPONPAGE_COMMAND_SCORCH_SIZE 54
#define WEAPONPAGE_COMMAND_ALT_SPAWN_NAME 55
#define WEAPONPAGE_COMMAND_ALT_CHANCE 56
#define WEAPONPAGE_COMMAND_GRAVITY_FIELD 57
#define WEAPONPAGE_COMMAND_ROBOT_SPAWN_NAME 58
#define WEAPONPAGE_COMMAND_TERRAIN_DAMAGE 59
#define WEAPONPAGE_COMMAND_HOMING_FOV 60
#define WEAPONPAGE_COMMAND_CUSTOM_SIZE 61

#define WEAPONPAGE_VERSION 8

void mng_WriteLightingChunk(light_info *lighting_info, CFILE *outfile);
void mng_ReadLightingChunk(light_info *lighting_info, CFILE *infile);

extern char *TablefileNameOverride;

// Sets a page structure to default values
void mng_InitWeaponPage(mngs_weapon_page *weaponpage) {
  int i;

  memset(weaponpage, 0, sizeof(mngs_weapon_page));
  strcpy(weaponpage->hud_image_name, "");
  strcpy(weaponpage->fire_image_name, "");
  strcpy(weaponpage->explode_image_name, "");
  strcpy(weaponpage->spawn_name, "");
  strcpy(weaponpage->alternate_spawn_name, "");
  strcpy(weaponpage->robot_spawn_name, "");
  strcpy(weaponpage->smoke_image_name, "");
  strcpy(weaponpage->scorch_image_name, "");
  strcpy(weaponpage->icon_name, "");
  strcpy(weaponpage->particle_name, "");

  weaponpage->weapon_struct.alpha = 1.0;
  weaponpage->weapon_struct.alternate_chance = 0;
  weaponpage->weapon_struct.explode_time = 1.0;
  weaponpage->weapon_struct.explode_size = 1.0;
  weaponpage->weapon_struct.particle_count = 0;
  weaponpage->weapon_struct.scorch_size = 1.0;
  weaponpage->weapon_struct.terrain_damage_size = 0;
  weaponpage->weapon_struct.terrain_damage_depth = 0;
  weaponpage->weapon_struct.homing_fov = 0.4f;
  weaponpage->weapon_struct.custom_size = 0.0f;
  weaponpage->weapon_struct.recoil_force = 0.0f;

  weaponpage->weapon_struct.phys_info.hit_die_dot = 1.0f;

  for (i = 0; i < MAX_WEAPON_SOUNDS; i++)
    strcpy(weaponpage->sound_name[i], "");
}

// Given an open file pointer and a weapon_page struct, writes that weapon page out
void mng_WriteWeaponPage(CFILE *outfile, mngs_weapon_page *weaponpage) {
  int i;

  ASSERT(outfile != NULL);
  ASSERT(weaponpage != NULL);

  cf_WriteByte(outfile, PAGETYPE_WEAPON);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_VERSION);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, WEAPONPAGE_VERSION);

  if ((strlen(weaponpage->weapon_struct.name)) < 2)
    Int3(); // Get Jason, right now

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_NAME_NULL); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->weapon_struct.name)) + 1);
  cf_WriteString(outfile, weaponpage->weapon_struct.name);

  // Write out its image name
  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_EXPLOSION_NAME); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->explode_image_name)) + 1);
  cf_WriteString(outfile, weaponpage->explode_image_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_PARTICLE_NAME); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->particle_name)) + 1);
  cf_WriteString(outfile, weaponpage->particle_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_PARTICLE_DATA);
  cf_WriteByte(outfile, 9);
  cf_WriteByte(outfile, weaponpage->weapon_struct.particle_count);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.particle_life);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.particle_size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SPAWN_NAME); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->spawn_name)) + 1);
  cf_WriteString(outfile, weaponpage->spawn_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SPAWN_COUNT);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, weaponpage->weapon_struct.spawn_count);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_ROBOT_SPAWN_NAME); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->robot_spawn_name)) + 1);
  cf_WriteString(outfile, weaponpage->robot_spawn_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_ALT_SPAWN_NAME); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->alternate_spawn_name)) + 1);
  cf_WriteString(outfile, weaponpage->alternate_spawn_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_ALT_CHANCE);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, weaponpage->weapon_struct.alternate_chance);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_HUD_IMAGE_NULL); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->hud_image_name)) + 1);
  cf_WriteString(outfile, weaponpage->hud_image_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_FIRE_IMAGE_NULL); // get ready to write out name
  cf_WriteByte(outfile, (strlen(weaponpage->fire_image_name)) + 1);
  cf_WriteString(outfile, weaponpage->fire_image_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_HOMING_FOV);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.homing_fov);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_CUSTOM_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.custom_size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_GRAVITY_FIELD);
  cf_WriteByte(outfile, 8);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.gravity_time);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.gravity_size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_MASS);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.mass);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_DRAG);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.drag);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_FULL_THRUST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.full_thrust);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, weaponpage->weapon_struct.flags);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_PHYS_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, weaponpage->weapon_struct.phys_info.flags);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_TERRAIN_DAMAGE);
  cf_WriteByte(outfile, 5);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.terrain_damage_size);
  cf_WriteByte(outfile, weaponpage->weapon_struct.terrain_damage_depth);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_ALPHA);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.alpha);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_EXPLODE_TIME);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.explode_time);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_EXPLODE_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.explode_size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_DAMAGE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.player_damage);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_IMPACT_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_IMPACT_TIME);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_time);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_IMPACT_DAMAGE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_player_damage);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_IMPACT_FORCE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_force);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_ROT_DRAG);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.rotdrag);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_FULL_ROT_THRUST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.full_rotthrust);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_MAX_BOUNCES);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, weaponpage->weapon_struct.phys_info.num_bounces);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_INIT_VELOCITY);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.velocity.z);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_INIT_ROT_VEL_X);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.rotvel.x);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_INIT_ROT_VEL_Y);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.rotvel.y);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_INIT_ROT_VEL_Z);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.rotvel.z);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_LIFE_TIME);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.life_time);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_THRUST_TIME);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.thrust_time);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_WIGGLE_AMP);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.wiggle_amplitude);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_WIGGLE_FREQ);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.wiggles_per_sec);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_COEFF_RESTITUTION);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.coeff_restitution);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_HIT_DIE_DOT);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.phys_info.hit_die_dot);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_BETTER_LIGHT_CAST);
  cf_WriteByte(outfile, (10 * 4) + 2);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.light_distance);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.red_light1);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.green_light1);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.blue_light1);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.time_interval);

  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.red_light2);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.green_light2);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.lighting_info.blue_light2);
  cf_WriteInt(outfile, weaponpage->weapon_struct.lighting_info.flags);
  cf_WriteInt(outfile, weaponpage->weapon_struct.lighting_info.timebits);
  cf_WriteByte(outfile, weaponpage->weapon_struct.lighting_info.angle);
  cf_WriteByte(outfile, weaponpage->weapon_struct.lighting_info.lighting_render_type);

  // Write out its sounds name

  for (i = 0; i < MAX_WEAPON_SOUNDS; i++) {
    cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SOUND_NAME);
    cf_WriteByte(outfile, strlen(weaponpage->sound_name[i]) + 2); // 1 for sound index, 1 for null term
    cf_WriteByte(outfile, i);
    cf_WriteString(outfile, weaponpage->sound_name[i]);
  }

  // Write smoke name
  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SMOKE_NAME);
  cf_WriteByte(outfile, strlen(weaponpage->smoke_image_name) + 1); // 1 for null term
  cf_WriteString(outfile, weaponpage->smoke_image_name);

  // Write scorch name
  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SCORCH_NAME);
  cf_WriteByte(outfile, strlen(weaponpage->scorch_image_name) + 1); // 1 for null term
  cf_WriteString(outfile, weaponpage->scorch_image_name);

  // Write icon name
  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_ICON_NAME);
  cf_WriteByte(outfile, strlen(weaponpage->icon_name) + 1); // 1 for null term
  cf_WriteString(outfile, weaponpage->icon_name);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_SCORCH_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.scorch_size);

  cf_WriteByte(outfile, WEAPONPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}

// Given an open file pointer and a weapon_page struct, writes that weapon page out
void mng_WriteNewWeaponPage(CFILE *outfile, mngs_weapon_page *weaponpage) {
  int i;

  ASSERT(outfile != NULL);
  ASSERT(weaponpage != NULL);

  int offset = StartManagePage(outfile, PAGETYPE_WEAPON);

  cf_WriteShort(outfile, WEAPONPAGE_VERSION);

  if ((strlen(weaponpage->weapon_struct.name)) < 2)
    Int3(); // Get Jason, right now

  cf_WriteString(outfile, weaponpage->weapon_struct.name);

  // Write hud image name
  cf_WriteString(outfile, weaponpage->hud_image_name);

  // Write fire image
  cf_WriteString(outfile, weaponpage->fire_image_name);

  // Write out particle data
  cf_WriteString(outfile, weaponpage->particle_name);

  cf_WriteByte(outfile, weaponpage->weapon_struct.particle_count);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.particle_life);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.particle_size);

  // Write flags
  cf_WriteInt(outfile, weaponpage->weapon_struct.flags);

  // Write spawn data
  cf_WriteString(outfile, weaponpage->spawn_name);
  cf_WriteByte(outfile, weaponpage->weapon_struct.spawn_count);

  cf_WriteString(outfile, weaponpage->robot_spawn_name);

  cf_WriteString(outfile, weaponpage->alternate_spawn_name);

  cf_WriteByte(outfile, weaponpage->weapon_struct.alternate_chance);

  // Write gravity stuff
  cf_WriteFloat(outfile, weaponpage->weapon_struct.gravity_time);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.gravity_size);

  // Write misc stuff
  cf_WriteFloat(outfile, weaponpage->weapon_struct.homing_fov);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.custom_size);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.size);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.thrust_time);

  // Write physics stuff
  mng_WritePhysicsChunk(&weaponpage->weapon_struct.phys_info, outfile);

  // Write terrain damage
  cf_WriteFloat(outfile, weaponpage->weapon_struct.terrain_damage_size);
  cf_WriteByte(outfile, weaponpage->weapon_struct.terrain_damage_depth);

  // Write alpha
  cf_WriteFloat(outfile, weaponpage->weapon_struct.alpha);

  // Write explosion data
  cf_WriteString(outfile, weaponpage->explode_image_name);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.explode_time);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.explode_size);

  // Write damage data
  cf_WriteFloat(outfile, weaponpage->weapon_struct.player_damage);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.generic_damage);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_size);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_time);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_player_damage);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_generic_damage);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.impact_force);

  // Write lifetime
  cf_WriteFloat(outfile, weaponpage->weapon_struct.life_time);

  // Write lighting
  mng_WriteLightingChunk(&weaponpage->weapon_struct.lighting_info, outfile);

  // Write recoil force
  cf_WriteFloat(outfile, weaponpage->weapon_struct.recoil_force);

  // Write out its sounds name
  for (i = 0; i < MAX_WEAPON_SOUNDS; i++)
    cf_WriteString(outfile, weaponpage->sound_name[i]);

  // Write smoke name
  cf_WriteString(outfile, weaponpage->smoke_image_name);

  // Write scorch data
  cf_WriteString(outfile, weaponpage->scorch_image_name);
  cf_WriteFloat(outfile, weaponpage->weapon_struct.scorch_size);

  // Write icon name
  cf_WriteString(outfile, weaponpage->icon_name);

  EndManagePage(outfile, offset);
}

#ifdef OEM
void DoOEMNapalmBarrelHack(mngs_weapon_page *weaponpage) {
  if (!strcmp(weaponpage->weapon_struct.name, "NapalmBarrelPart2")) {
    mprintf(0, "BASHING NAPALMBARRELPART2!!!!!!\n");
    weaponpage->weapon_struct.flags |= (WF_SATURATE | WF_NO_ROTATE | WF_CUSTOM_SIZE | WF_NAPALM);
    weaponpage->weapon_struct.custom_size = 6.0f;
    weaponpage->weapon_struct.phys_info.mass = 0.6f;
    weaponpage->weapon_struct.phys_info.drag = 0.01f;
    weaponpage->weapon_struct.phys_info.rotdrag = 0.001f;

    weaponpage->weapon_struct.phys_info.velocity.x = 0;
    weaponpage->weapon_struct.phys_info.velocity.y = 0;
    weaponpage->weapon_struct.phys_info.velocity.z = 50.0f;

  } else {
    mprintf(0, "BASHING NAPALMBARREL!!!!!!\n");
    weaponpage->weapon_struct.flags |= (WF_INVISIBLE | WF_CUSTOM_SIZE | WF_NAPALM);
    weaponpage->weapon_struct.custom_size = 1.0f;
    weaponpage->weapon_struct.phys_info.flags |= PF_USES_PARENT_VELOCITY;

    weaponpage->weapon_struct.phys_info.velocity.x = 0;
    weaponpage->weapon_struct.phys_info.velocity.y = 0;
    weaponpage->weapon_struct.phys_info.velocity.z = 110.0f;
  }
}
#endif

// Given an open file pointer and a weapon_page struct, reads a weapon page
int mng_ReadNewWeaponPage(CFILE *infile, mngs_weapon_page *weaponpage) {
  int i;

  mng_InitWeaponPage(weaponpage);

  int version = cf_ReadShort(infile);

  cf_ReadString(weaponpage->weapon_struct.name, PAGENAME_LEN, infile);

  // Read hud image name
  cf_ReadString(weaponpage->hud_image_name, PAGENAME_LEN, infile);

  // Read fire image
  cf_ReadString(weaponpage->fire_image_name, PAGENAME_LEN, infile);

  // Read particle data
  cf_ReadString(weaponpage->particle_name, PAGENAME_LEN, infile);

  weaponpage->weapon_struct.particle_count = cf_ReadByte(infile);
  weaponpage->weapon_struct.particle_life = cf_ReadFloat(infile);
  weaponpage->weapon_struct.particle_size = cf_ReadFloat(infile);

  // Read flags
  weaponpage->weapon_struct.flags = cf_ReadInt(infile);

  // Read spawn data
  cf_ReadString(weaponpage->spawn_name, PAGENAME_LEN, infile);
  weaponpage->weapon_struct.spawn_count = cf_ReadByte(infile);

  cf_ReadString(weaponpage->robot_spawn_name, PAGENAME_LEN, infile);
  cf_ReadString(weaponpage->alternate_spawn_name, PAGENAME_LEN, infile);

  weaponpage->weapon_struct.alternate_chance = cf_ReadByte(infile);

  // Read gravity stuff
  weaponpage->weapon_struct.gravity_time = cf_ReadFloat(infile);
  weaponpage->weapon_struct.gravity_size = cf_ReadFloat(infile);

  // Read size and homing data
  weaponpage->weapon_struct.homing_fov = cf_ReadFloat(infile);
  weaponpage->weapon_struct.custom_size = cf_ReadFloat(infile);
  weaponpage->weapon_struct.size = cf_ReadFloat(infile);
  weaponpage->weapon_struct.thrust_time = cf_ReadFloat(infile);

  // Read physics info
  mng_ReadPhysicsChunk(&weaponpage->weapon_struct.phys_info, infile);

  // Read terrain damage
  weaponpage->weapon_struct.terrain_damage_size = cf_ReadFloat(infile);
  weaponpage->weapon_struct.terrain_damage_depth = cf_ReadByte(infile);

  // Read alpha
  weaponpage->weapon_struct.alpha = cf_ReadFloat(infile);

  // Read explosion data
  cf_ReadString(weaponpage->explode_image_name, PAGENAME_LEN, infile);
  weaponpage->weapon_struct.explode_time = cf_ReadFloat(infile);
  weaponpage->weapon_struct.explode_size = cf_ReadFloat(infile);

  // Read damage data
  weaponpage->weapon_struct.player_damage = cf_ReadFloat(infile);

  if (version >= 7)
    weaponpage->weapon_struct.generic_damage = cf_ReadFloat(infile);
  else
    weaponpage->weapon_struct.generic_damage = weaponpage->weapon_struct.player_damage;

  weaponpage->weapon_struct.impact_size = cf_ReadFloat(infile);
  weaponpage->weapon_struct.impact_time = cf_ReadFloat(infile);
  weaponpage->weapon_struct.impact_player_damage = cf_ReadFloat(infile);

  if (version >= 7)
    weaponpage->weapon_struct.impact_generic_damage = cf_ReadFloat(infile);
  else
    weaponpage->weapon_struct.impact_generic_damage = weaponpage->weapon_struct.impact_player_damage;

  weaponpage->weapon_struct.impact_force = cf_ReadFloat(infile);

  // Read lifetime
  weaponpage->weapon_struct.life_time = cf_ReadFloat(infile);

  // read lighting
  mng_ReadLightingChunk(&weaponpage->weapon_struct.lighting_info, infile);

  // read recoil force
  if (version >= 8)
    weaponpage->weapon_struct.recoil_force = cf_ReadFloat(infile);
  else
    weaponpage->weapon_struct.recoil_force = 0.0f;

  // Read its sound names
  for (i = 0; i < MAX_WEAPON_SOUNDS; i++)
    cf_ReadString(weaponpage->sound_name[i], PAGENAME_LEN, infile);

  // Read smoke name
  cf_ReadString(weaponpage->smoke_image_name, PAGENAME_LEN, infile);

  // Read scorch data
  cf_ReadString(weaponpage->scorch_image_name, PAGENAME_LEN, infile);
  weaponpage->weapon_struct.scorch_size = cf_ReadFloat(infile);

  // Read icon name
  cf_ReadString(weaponpage->icon_name, PAGENAME_LEN, infile);

  weaponpage->weapon_struct.used = 1;

#ifdef OEM
  if (!strcmp(weaponpage->weapon_struct.name, "NapalmBarrelPart2") ||
      !strcmp(weaponpage->weapon_struct.name, "NapalmBarrel")) {
    // Do OEM hack
    DoOEMNapalmBarrelHack(weaponpage);
  }
#endif

  if (!stricmp(weaponpage->weapon_struct.name, "EMDBlob")) {
    weaponpage->weapon_struct.life_time = 1.7f;
  }

  return 1; // successfully read
}

// Reads a weapon page from an open file.  Returns 0 on error.
int mng_ReadWeaponPage(CFILE *infile, mngs_weapon_page *weaponpage) {
  int done = 0;
  char command;
  uint8_t len;
  int i, t;
  int version = 0;

  if (!Old_table_method)
    return mng_ReadNewWeaponPage(infile, weaponpage);

  ASSERT(infile != NULL);

  mng_InitWeaponPage(weaponpage);

  while (!done) {
    // Read in command byte then read in the length of that commands data

    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);

    switch (command) {
    case WEAPONPAGE_COMMAND_END:
      done = 1;
      break;
    case WEAPONPAGE_COMMAND_VERSION:
      version = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_HUD_IMAGE_NAME: // the name of the weapon model
      for (i = 0; i < PAGENAME_LEN; i++)
        weaponpage->hud_image_name[i] = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_FIRE_IMAGE_NAME: // the name of the weapon model
      for (i = 0; i < PAGENAME_LEN; i++)
        weaponpage->fire_image_name[i] = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_NAME_NULL:
      cf_ReadString(weaponpage->weapon_struct.name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_FIRE_IMAGE_NULL:
      cf_ReadString(weaponpage->fire_image_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_HUD_IMAGE_NULL:
      cf_ReadString(weaponpage->hud_image_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_SPAWN_NAME:
      cf_ReadString(weaponpage->spawn_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_SPAWN_COUNT:
      weaponpage->weapon_struct.spawn_count = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_ALT_SPAWN_NAME:
      cf_ReadString(weaponpage->alternate_spawn_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_ROBOT_SPAWN_NAME:
      cf_ReadString(weaponpage->robot_spawn_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_ALT_CHANCE:
      weaponpage->weapon_struct.alternate_chance = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_NAME:
      for (i = 0; i < PAGENAME_LEN; i++)
        weaponpage->weapon_struct.name[i] = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_EXPLOSION_NAME:
      cf_ReadString(weaponpage->explode_image_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_PARTICLE_NAME:
      cf_ReadString(weaponpage->particle_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_FLAGS:
      weaponpage->weapon_struct.flags = cf_ReadInt(infile);
      break;
    case WEAPONPAGE_COMMAND_MASS:
      weaponpage->weapon_struct.phys_info.mass = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_HOMING_FOV:
      weaponpage->weapon_struct.homing_fov = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_CUSTOM_SIZE:
      weaponpage->weapon_struct.custom_size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_GRAVITY_FIELD:
      weaponpage->weapon_struct.gravity_time = cf_ReadFloat(infile);
      weaponpage->weapon_struct.gravity_size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_FULL_THRUST:
      weaponpage->weapon_struct.phys_info.full_thrust = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_DRAG:
      weaponpage->weapon_struct.phys_info.drag = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_TERRAIN_DAMAGE:
      weaponpage->weapon_struct.terrain_damage_size = cf_ReadFloat(infile);
      weaponpage->weapon_struct.terrain_damage_depth = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_SOUND_NAME:
      t = cf_ReadByte(infile);
      cf_ReadString(weaponpage->sound_name[t], len, infile);
      break;
    case WEAPONPAGE_COMMAND_PHYS_FLAGS:
      weaponpage->weapon_struct.phys_info.flags = cf_ReadInt(infile);
      break;
    case WEAPONPAGE_COMMAND_SIZE:
      weaponpage->weapon_struct.size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_ALPHA:
      weaponpage->weapon_struct.alpha = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_EXPLODE_TIME:
      weaponpage->weapon_struct.explode_time = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_EXPLODE_SIZE:
      weaponpage->weapon_struct.explode_size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_PARTICLE_DATA:
      weaponpage->weapon_struct.particle_count = cf_ReadByte(infile);
      weaponpage->weapon_struct.particle_life = cf_ReadFloat(infile);
      weaponpage->weapon_struct.particle_size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_DAMAGE:
      weaponpage->weapon_struct.player_damage = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_IMPACT_SIZE:
      weaponpage->weapon_struct.impact_size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_IMPACT_TIME:
      weaponpage->weapon_struct.impact_time = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_IMPACT_DAMAGE:
      weaponpage->weapon_struct.impact_player_damage = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_IMPACT_FORCE:
      weaponpage->weapon_struct.impact_force = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_ROT_DRAG:
      weaponpage->weapon_struct.phys_info.rotdrag = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_FULL_ROT_THRUST:
      weaponpage->weapon_struct.phys_info.full_rotthrust = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_MAX_BOUNCES:
      weaponpage->weapon_struct.phys_info.num_bounces = cf_ReadInt(infile);
      break;
    case WEAPONPAGE_COMMAND_INIT_VELOCITY:
      weaponpage->weapon_struct.phys_info.velocity.z = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_INIT_ROT_VEL_X:
      weaponpage->weapon_struct.phys_info.rotvel.x = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_INIT_ROT_VEL_Y:
      weaponpage->weapon_struct.phys_info.rotvel.y = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_INIT_ROT_VEL_Z:
      weaponpage->weapon_struct.phys_info.rotvel.z = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_LIFE_TIME:
      weaponpage->weapon_struct.life_time = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_THRUST_TIME:
      weaponpage->weapon_struct.thrust_time = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_WIGGLE_AMP:
      weaponpage->weapon_struct.phys_info.wiggle_amplitude = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_WIGGLE_FREQ:
      weaponpage->weapon_struct.phys_info.wiggles_per_sec = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_COEFF_RESTITUTION:
      weaponpage->weapon_struct.phys_info.coeff_restitution = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_HIT_DIE_DOT:
      weaponpage->weapon_struct.phys_info.hit_die_dot = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_LIGHT_CAST:
      weaponpage->weapon_struct.lighting_info.light_distance = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.red_light1 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.green_light1 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.blue_light1 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.timebits = 0xFFFFFFFF;
      break;
    case WEAPONPAGE_COMMAND_BETTER_LIGHT_CAST:
      weaponpage->weapon_struct.lighting_info.light_distance = cf_ReadFloat(infile);

      weaponpage->weapon_struct.lighting_info.red_light1 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.green_light1 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.blue_light1 = cf_ReadFloat(infile);

      weaponpage->weapon_struct.lighting_info.time_interval = cf_ReadFloat(infile);

      weaponpage->weapon_struct.lighting_info.red_light2 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.green_light2 = cf_ReadFloat(infile);
      weaponpage->weapon_struct.lighting_info.blue_light2 = cf_ReadFloat(infile);

      weaponpage->weapon_struct.lighting_info.flags = cf_ReadInt(infile);
      weaponpage->weapon_struct.lighting_info.timebits = cf_ReadInt(infile);
      weaponpage->weapon_struct.lighting_info.angle = cf_ReadByte(infile);
      weaponpage->weapon_struct.lighting_info.lighting_render_type = cf_ReadByte(infile);
      break;
    case WEAPONPAGE_COMMAND_SMOKE_NAME:
      cf_ReadString(weaponpage->smoke_image_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_SCORCH_NAME:
      cf_ReadString(weaponpage->scorch_image_name, len + 1, infile);
      break;
    case WEAPONPAGE_COMMAND_SCORCH_SIZE:
      weaponpage->weapon_struct.scorch_size = cf_ReadFloat(infile);
      break;
    case WEAPONPAGE_COMMAND_ICON_NAME:
      cf_ReadString(weaponpage->icon_name, len + 1, infile);
      break;
    default:
      // Ignore the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }

  if (version < 2) {
    weaponpage->weapon_struct.impact_player_damage = weaponpage->weapon_struct.player_damage;
    weaponpage->weapon_struct.impact_force = weaponpage->weapon_struct.player_damage * 100.0f;
    if (weaponpage->weapon_struct.impact_size > 0.0) {
      weaponpage->weapon_struct.impact_time = weaponpage->weapon_struct.explode_time;
      weaponpage->weapon_struct.impact_size = weaponpage->weapon_struct.explode_size * 1.5;
    }
  }

  // Clear out old strings
  if (!strnicmp("INVALID", weaponpage->explode_image_name, 7))
    strcpy(weaponpage->explode_image_name, "");
  if (!strnicmp("INVALID", weaponpage->smoke_image_name, 7))
    strcpy(weaponpage->smoke_image_name, "");
  if (!strnicmp("INVALID", weaponpage->scorch_image_name, 7))
    strcpy(weaponpage->scorch_image_name, "");
  if (!strnicmp("INVALID", weaponpage->icon_name, 7))
    strcpy(weaponpage->icon_name, "");
  if (!strnicmp("INVALID", weaponpage->spawn_name, 7))
    strcpy(weaponpage->spawn_name, "");
  if (!strnicmp("INVALID", weaponpage->alternate_spawn_name, 7))
    strcpy(weaponpage->alternate_spawn_name, "");
  if (!strnicmp("INVALID", weaponpage->robot_spawn_name, 7))
    strcpy(weaponpage->robot_spawn_name, "");
  if (!strnicmp("INVALID", weaponpage->particle_name, 7))
    strcpy(weaponpage->particle_name, "");

  for (i = 0; i < MAX_WEAPON_SOUNDS; i++) {
    if (!strnicmp("INVALID", weaponpage->sound_name[i], 7))
      strcpy(weaponpage->sound_name[i], "");
  }

  // This is a valid new page
  weaponpage->weapon_struct.used = 1;

  return 1; // successfully read
}

// Reads in the weapon named "name" into weaponpage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificWeaponPage(char *name, mngs_weapon_page *weaponpage) {
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
    mprintf(0, "Couldn't open table file to find weapon!\n");
    Int3();
    return 0;
  }

try_again:;

  // Read in the entire page file until we find the page we want
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);

    // If not a weapon page, just read it in and ignore it
    if (pagetype != PAGETYPE_WEAPON) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewWeaponPage(infile, weaponpage);

    if (!stricmp(name, weaponpage->weapon_struct.name)) {
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

// Reads in the weapon named "name" into weaponpage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificWeaponPage(char *name, mngs_weapon_page *weaponpage, int offset) {
  CFILE *infile;
  uint8_t pagetype;
  int done = 0, found = 0;

  if (Loading_locals) {
    infile = cfopen(LocalTableFilename, "rb");
  } else if (Loading_addon_table != -1) {
    infile = cfopen(AddOnDataTables[Loading_addon_table].AddOnTableFilename, "rb");
  } else {
    if (Network_up && Starting_editor) {
      std::filesystem::path tablename;

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
    mprintf(0, "Couldn't open table file to find weapon!\n");
    Int3();
    return 0;
  }

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

    // If not a weapon page, just read it in and ignore it
    if (pagetype != PAGETYPE_WEAPON) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewWeaponPage(infile, weaponpage);

    if (!stricmp(name, weaponpage->weapon_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    }
  }

  cfclose(infile);

  return found; // successful!
}

const char *Weapon_error = NULL;
const char *Weapon_error_filename = NULL;

// First searches through the weapon index to see if the weapon is already
// loaded.  If not, searches in the table file and loads it.
// Returns index of weapon found, -1 if not
int mng_GetGuaranteedWeaponPage(char *name, CFILE *infile) {
  int i;
  mngs_weapon_page weaponpage;

  // See if its in memory
  i = FindWeaponName(name);
  if (i != -1)
    return i;

  // Not in memory.  Load it from the table file.  Start searching from the
  // current spot in the open table file

  int ret = mng_FindSpecificWeaponPage(name, &weaponpage, infile ? infile->position : 0);

  if (!ret)
    return -1;

  // We've found it in the table file, now load it.
  ret = mng_SetAndLoadWeapon(&weaponpage, infile);
  // ASSERT (ret>=0);
  if (ret < 0)
    DataError("Error loading weapon <%s>: %s, file <%s>\n", weaponpage.weapon_struct.name, Weapon_error,
              Weapon_error_filename);

  if (Loading_addon_table != -1) {
    // we're loading addon table pages, this will not overlay anything
    mng_PushAddonPage(PAGETYPE_WEAPON, weaponpage.weapon_struct.name, 0);
  }

  return ret;
}

// Given a weapon page, allocs a weapon and calls AssignWeaponPageToWeapon to actually
// load models and values. Rturns weapon handle on success, -1 if fail
int mng_SetAndLoadWeapon(mngs_weapon_page *weaponpage, CFILE *infile) {
  int n;

  Weapon_error = Weapon_error_filename = "";

  n = AllocWeapon();
  if (n < 0) {
    Weapon_error = "No free weapon slots";
    return -1;
  }
  if (!mng_AssignWeaponPageToWeapon(weaponpage, n, infile))
    return -1;

  return n;
}

// Given a weaponpage and a weapon handle, attempts to make weapon n correspond to
// to the weaponpage.
// Returns 1 on success, 0 otherwise
int mng_AssignWeaponPageToWeapon(mngs_weapon_page *weaponpage, int n, CFILE *infile) {
  weapon *weaponpointer = &Weapons[n];
  int img_handle, i, sound_handle;

  // copy our values
  memcpy(weaponpointer, &weaponpage->weapon_struct, sizeof(weapon));
  strcpy(weaponpointer->name, weaponpage->weapon_struct.name);

  // First see if our image differs from the one on the net
  // If it is, make a copy
  // If its a release version, don't do any of this

#ifndef RELEASE
  if (Network_up) {
    std::filesystem::path str = LocalManageGraphicsDir;
    std::filesystem::path netstr = ManageGraphicsDir;

    UpdatePrimitive(str / weaponpage->hud_image_name, netstr / weaponpage->hud_image_name, weaponpage->hud_image_name,
                    PAGETYPE_WEAPON, weaponpointer->name);

    // Now copy the discharge image, depending on whether or not its a model
    if (!((weaponpage->weapon_struct.flags & WF_IMAGE_BITMAP) || (weaponpage->weapon_struct.flags & WF_IMAGE_VCLIP))) {
      str = LocalModelsDir;
      netstr = NetModelsDir;
    }

    UpdatePrimitive(str / weaponpage->fire_image_name, netstr / weaponpage->fire_image_name,
                    weaponpage->fire_image_name, PAGETYPE_WEAPON, weaponpointer->name);
  }
#endif

  // Try and load our weapon model from the disk

  if (weaponpointer->flags & WF_HUD_ANIMATED)
    img_handle = AllocLoadVClip(weaponpage->hud_image_name, NOT_TEXTURE, 0);
  else
    img_handle = bm_AllocLoadFileBitmap(weaponpage->hud_image_name, 0);

  if (img_handle < 0) {
    mprintf(0, "Couldn't load bitmap '%s' in AssignWeaponPage...\n", weaponpage->hud_image_name);
    weaponpointer->hud_image_handle = -1;
    Weapon_error = "Can't load HUD image";
    Weapon_error_filename = weaponpage->hud_image_name;
    return 0;
  } else
    weaponpointer->hud_image_handle = img_handle;

  if (weaponpointer->flags & WF_IMAGE_BITMAP)
    img_handle = bm_AllocLoadFileBitmap(weaponpage->fire_image_name, 0);
  else if (weaponpointer->flags & WF_IMAGE_VCLIP)
    img_handle = AllocLoadVClip(weaponpage->fire_image_name, NOT_TEXTURE, 0);
  else
    img_handle = LoadPolyModel(weaponpage->fire_image_name, 1);

  if (img_handle < 0) {
    mprintf(0, "Couldn't load bitmap/model '%s' in AssignWeaponPage...\n", weaponpage->fire_image_name);
    weaponpointer->fire_image_handle = -1;
    Weapon_error = "Can't load fire image";
    Weapon_error_filename = weaponpage->fire_image_name;
    return 0;
  } else {
    weaponpointer->fire_image_handle = img_handle;

    /*// Fix size
    if (!(weaponpointer->flags & WF_IMAGE_BITMAP))
    {
            if (Poly_models[img_handle].new_style && Poly_models[img_handle].flags & PMF_TIMED)
            {
                    weaponpointer->size=ComputeDefaultSize(img_handle);
            }
    }*/
  }

  if (stricmp(weaponpage->explode_image_name, "INVALID NAME") && weaponpage->explode_image_name[0] != 0) {
    img_handle = mng_GetGuaranteedTexturePage(weaponpage->explode_image_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load bitmap/model '%s' in AssignWeaponPage...\n", weaponpage->explode_image_name);
      weaponpointer->explode_image_handle = -1;
    } else
      weaponpointer->explode_image_handle = img_handle;
  } else
    weaponpointer->explode_image_handle = -1;

  // Try to load particle texture
  if (stricmp(weaponpage->particle_name, "INVALID NAME") && weaponpage->particle_name[0] != 0) {
    img_handle = mng_GetGuaranteedTexturePage(weaponpage->particle_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load bitmap/model '%s' in AssignWeaponPage...\n", weaponpage->particle_name);
      weaponpointer->particle_handle = -1;
    } else
      weaponpointer->particle_handle = img_handle;
  } else
    weaponpointer->particle_handle = -1;

  // Try to load spawn weapons
  if (stricmp(weaponpage->spawn_name, "INVALID NAME") && weaponpage->spawn_name[0] != 0) {
    img_handle = mng_GetGuaranteedWeaponPage(weaponpage->spawn_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load spawn weapon '%s' in AssignWeaponPage...\n", weaponpage->spawn_name);
      weaponpointer->spawn_handle = -1;
    } else
      weaponpointer->spawn_handle = img_handle;
  } else
    weaponpointer->spawn_handle = -1;

  if (stricmp(weaponpage->alternate_spawn_name, "INVALID NAME") && weaponpage->alternate_spawn_name[0] != 0) {
    img_handle = mng_GetGuaranteedWeaponPage(weaponpage->alternate_spawn_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load alternate spawn weapon '%s' in AssignWeaponPage...\n",
              weaponpage->alternate_spawn_name);
      weaponpointer->alternate_spawn_handle = -1;
    } else
      weaponpointer->alternate_spawn_handle = img_handle;
  } else
    weaponpointer->alternate_spawn_handle = -1;

  // Try to load robot spawn
  if (stricmp(weaponpage->robot_spawn_name, "INVALID NAME") && weaponpage->robot_spawn_name[0] != 0) {
    img_handle = mng_GetGuaranteedGenericPage(weaponpage->robot_spawn_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load robot spawn weapon '%s' in AssignWeaponPage...\n", weaponpage->robot_spawn_name);
      weaponpointer->robot_spawn_handle = -1;
    } else
      weaponpointer->robot_spawn_handle = img_handle;
  } else
    weaponpointer->robot_spawn_handle = -1;

  // Try to load smoke
  if (stricmp(weaponpage->smoke_image_name, "INVALID NAME") && weaponpage->smoke_image_name[0] != 0) {
    img_handle = mng_GetGuaranteedTexturePage(weaponpage->smoke_image_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load smoke trail file '%s' in AssignWeaponPage...\n", weaponpage->smoke_image_name);
      weaponpointer->flags &= ~WF_SMOKE;
      weaponpointer->smoke_handle = -1;

    } else
      weaponpointer->smoke_handle = img_handle;
  } else {
    weaponpointer->flags &= ~WF_SMOKE;
    weaponpointer->smoke_handle = -1;
  }

  // Try to load scorch
  if (stricmp(weaponpage->scorch_image_name, "INVALID NAME") && weaponpage->scorch_image_name[0] != 0) {
    img_handle = mng_GetGuaranteedTexturePage(weaponpage->scorch_image_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load scorch file '%s' in AssignWeaponPage...\n", weaponpage->scorch_image_name);
      weaponpointer->scorch_handle = -1;

    } else
      weaponpointer->scorch_handle = img_handle;
  } else {
    weaponpointer->scorch_handle = -1;
  }

  // Try to load icone
  if (stricmp(weaponpage->icon_name, "INVALID NAME") && weaponpage->icon_name[0] != 0) {
    img_handle = mng_GetGuaranteedTexturePage(weaponpage->icon_name, infile);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load icon file '%s' in AssignWeaponPage...\n", weaponpage->icon_name);
      weaponpointer->icon_handle = -1;

    } else
      weaponpointer->icon_handle = img_handle;
  } else {
    weaponpointer->icon_handle = -1;
  }

  // Try and load the various sounds
  for (i = 0; i < MAX_WEAPON_SOUNDS; i++) {
    if (stricmp(weaponpage->sound_name[i], "INVALID NAME") && (strlen(weaponpage->sound_name[i]) > 3)) {
      sound_handle = mng_GetGuaranteedSoundPage(weaponpage->sound_name[i]);

      if (sound_handle < 0) {
        mprintf(0, "Couldn't load sound file '%s' in AssignWeaponPage.  Weapon=%s\n", weaponpage->sound_name[i],
                weaponpage->weapon_struct.name);
        weaponpointer->sounds[i] = SOUND_NONE_INDEX;
      } else
        weaponpointer->sounds[i] = sound_handle;
    } else
      weaponpointer->sounds[i] = SOUND_NONE_INDEX;
  }

  return 1;
}

// Copies values from a weapon into a weapon_page
void mng_AssignWeaponToWeaponPage(int n, mngs_weapon_page *weaponpage) {
  weapon *weaponpointer = &Weapons[n];
  int i;

  // Assign the  values
  memcpy(&weaponpage->weapon_struct, weaponpointer, sizeof(weapon));

  strcpy(weaponpage->weapon_struct.name, weaponpointer->name);

  if (weaponpointer->hud_image_handle != -1) {
    if (weaponpointer->flags & WF_HUD_ANIMATED)
      strcpy(weaponpage->hud_image_name, GameVClips[weaponpointer->hud_image_handle].name);
    else
      strcpy(weaponpage->hud_image_name, GameBitmaps[weaponpointer->hud_image_handle].name);
  } else
    strcpy(weaponpage->hud_image_name, "");

  if (weaponpointer->fire_image_handle != -1) {
    if (weaponpointer->flags & WF_IMAGE_BITMAP)
      strcpy(weaponpage->fire_image_name, GameBitmaps[weaponpointer->fire_image_handle].name);
    else if (weaponpointer->flags & WF_IMAGE_VCLIP)
      strcpy(weaponpage->fire_image_name, GameVClips[weaponpointer->fire_image_handle].name);
    else
      strcpy(weaponpage->fire_image_name, Poly_models[weaponpointer->fire_image_handle].name);
  } else
    strcpy(weaponpage->fire_image_name, "");

  // do explosion name

  if (weaponpointer->explode_image_handle != -1)
    strcpy(weaponpage->explode_image_name, GameTextures[weaponpointer->explode_image_handle].name);
  else
    strcpy(weaponpage->explode_image_name, "");

  // Do particle name
  if (weaponpointer->particle_handle != -1)
    strcpy(weaponpage->particle_name, GameTextures[weaponpointer->particle_handle].name);
  else
    strcpy(weaponpage->particle_name, "");

  // Do spawn name
  if (weaponpointer->spawn_handle != -1)
    strcpy(weaponpage->spawn_name, Weapons[weaponpointer->spawn_handle].name);
  else
    strcpy(weaponpage->spawn_name, "");

  // Do spawn name
  if (weaponpointer->alternate_spawn_handle != -1)
    strcpy(weaponpage->alternate_spawn_name, Weapons[weaponpointer->alternate_spawn_handle].name);
  else
    strcpy(weaponpage->alternate_spawn_name, "");

  // Do robot spawn name
  if (weaponpointer->robot_spawn_handle != -1)
    strcpy(weaponpage->robot_spawn_name, Object_info[weaponpointer->robot_spawn_handle].name);
  else
    strcpy(weaponpage->robot_spawn_name, "");

  if ((weaponpointer->flags & WF_SMOKE) && weaponpointer->smoke_handle >= 0 &&
      GameTextures[weaponpointer->smoke_handle].used) {
    strcpy(weaponpage->smoke_image_name, GameTextures[weaponpointer->smoke_handle].name);
  } else
    strcpy(weaponpage->smoke_image_name, "");

  if (weaponpointer->scorch_handle >= 0 && GameTextures[weaponpointer->scorch_handle].used) {
    strcpy(weaponpage->scorch_image_name, GameTextures[weaponpointer->scorch_handle].name);
  } else
    strcpy(weaponpage->scorch_image_name, "");

  if (weaponpointer->icon_handle >= 0 && GameTextures[weaponpointer->icon_handle].used) {
    strcpy(weaponpage->icon_name, GameTextures[weaponpointer->icon_handle].name);
  } else
    strcpy(weaponpage->icon_name, "");

  for (i = 0; i < MAX_WEAPON_SOUNDS; i++) {
    if (weaponpointer->sounds[i] != SOUND_NONE_INDEX)
      strcpy(weaponpage->sound_name[i], Sounds[weaponpointer->sounds[i]].name);
    else
      strcpy(weaponpage->sound_name[i], "");
  }
}

// Loads a weapon found in the net table file.  It then allocs a weapon and
// then calls SetAndLoadWeapon to actually load in any images/models associated
// with it
void mng_LoadNetWeaponPage(CFILE *infile, bool overlay) {
  mngs_weapon_page weaponpage;
  memset(&weaponpage, 0, sizeof(mngs_weapon_page));

  if (mng_ReadNewWeaponPage(infile, &weaponpage)) {
    int n = FindWeaponName(weaponpage.weapon_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING WEAPON %s\n", weaponpage.weapon_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_WEAPON, weaponpage.weapon_struct.name, 0);
        mng_AssignWeaponPageToWeapon(&weaponpage, n);
      }
      // mprintf(0,"Found weapon dependency! You probably should reorder the netpages.\n");
      return;
    }

    int ret = mng_SetAndLoadWeapon(&weaponpage, infile);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load weaponpage named %s!\n", weaponpage.weapon_struct.name);
}

// Reads a weapon page from a local table file.  It then allocs a weapon and
// loads any images/models associated with that weapon
void mng_LoadLocalWeaponPage(CFILE *infile) {
  mngs_weapon_page weaponpage;
  int ok = 0;
  memset(&weaponpage, 0, sizeof(mngs_weapon_page));

  if (mng_ReadNewWeaponPage(infile, &weaponpage)) {
    // Check to see if this is a local copy that is supposed
    // to go over a network copy (supersede the net copy)

    int i = FindWeaponName(weaponpage.weapon_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;

      strcpy(pl.name, weaponpage.weapon_struct.name);
      pl.pagetype = PAGETYPE_WEAPON;

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
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_WEAPON &&
              !stricmp(addon->Addon_tracklocks[tidx].name, weaponpage.weapon_struct.name)) {
            // found it!!
            mprintf(0, "WeaponPage: %s previously loaded\n", weaponpage.weapon_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_WEAPON, weaponpage.weapon_struct.name, 0);
        mng_AssignWeaponPageToWeapon(&weaponpage, i);

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
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_WEAPON &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, weaponpage.weapon_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_WEAPON, weaponpage.weapon_struct.name, overlay);
        }
      }
    } else {
      // This is a local weapon that has never been checked in
      if ((i = mng_SetAndLoadWeapon(&weaponpage, infile)) < 0)
        ok = 0;
      else
        ok = 1;

      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_WEAPON, weaponpage.weapon_struct.name, 0);
    }

    // ASSERT (ok==1);
    if (ok != 1)
      DataError("Error loading weapon <%s>: %s, file <%s>\n", weaponpage.weapon_struct.name, Weapon_error,
                Weapon_error_filename);

    if (Loading_addon_table == -1)
      mng_AllocTrackLock(weaponpage.weapon_struct.name, PAGETYPE_WEAPON);
  } else

    mprintf(0, "Could not load weaponpage named %s!\n", weaponpage.weapon_struct.name);
}
