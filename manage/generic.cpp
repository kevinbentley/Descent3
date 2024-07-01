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

 * $Logfile: /DescentIII/Main/manage/generic.cpp $
 * $Revision: 100 $
 * $Date: 9/06/01 10:32a $
 * $Author: Matt $
 *
 *
 * $Log: /DescentIII/Main/manage/generic.cpp $
 *
 * 100   9/06/01 10:32a Matt
 * Added code to fix problem poping add-on pages when the original pages
 * were in the extra.gam file.
 *
 * 99    4/19/00 5:27p Matt
 * From Duane for 1.4
 * Mac file extension change
 *
 * 98    10/26/99 3:30p Jeff
 * handle extra.gam addon tablefile
 *
 * 97    10/22/99 10:41p Jeff
 * correctly merged and handle this mac code merge stuff
 *
 * 96    10/22/99 6:04p Jeff
 * fixed bugs and compiler errors resulting from mac code merge
 *
 * 95    10/22/99 2:56p Kevin
 * Mac merge w/memory savings
 *
 * 94    9/18/99 8:49p Jeff
 * fixed bug with addon pages that have dependencies on other pages in the
 * addon tablefile
 *
 * 93    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 92    4/25/99 10:19p Matt
 * Fixed multiplayer and demo problems will killing an object from script,
 * and cleaned up the death code a bit in the process.
 *
 * 91    4/22/99 7:08p Matt
 * Reduced the number of object sounds from 3 to 2, since we were only
 * using two.
 *
 * 90    4/19/99 3:57p Matt
 * Took out guidebot velocity hack.
 *
 * 89    4/18/99 4:49p Matt
 * Took out code that hacked in ammo amounts for weapon powerups, and
 * added code to set the counts on the page and read and write to the
 * table file.
 *
 * 88    4/15/99 5:21p Jason
 * sped up table file loading
 *
 * 87    4/14/99 1:33a Jeff
 * fixed case mismatched #includes
 *
 * 86    4/10/99 5:56p Matt
 * Cleaned up object initialization code, including create object & load
 * object.
 *
 * 85    4/06/99 6:02p Matt
 * Added score system
 *
 * 84    3/29/99 11:20a Matt
 * Added more flexibility to death delays, and added fade away deaths.
 *
 * 83    3/27/99 2:15p Jason
 * took out bashing of hangturret
 *
 * 82    3/09/99 1:44p Kevin
 * Bashed the aiming point value for the hangturret.
 *
 * 81    3/04/99 4:47p Jason
 * temp fix (ie BAD HACK) for OEM table file woes
 *
 * 80    2/28/99 6:20p Matt
 * Added the ability to set death types for generic objects.
 *
 * 79    2/23/99 12:39p Jason
 * added more options for generic objects
 *
 * 78    2/23/99 11:02a Matt
 * Changed generic object spew info to use -1 for none
 *
 * 77    2/23/99 10:19a Matt
 * Temporary fix
 *
 * 76    2/16/99 12:38a Matt
 * Took out gunboy sound hack
 *
 * 75    2/02/99 8:44a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 74    1/21/99 11:16p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 73    1/13/99 7:04a Jeff
 * put #ifdef around #include <windows.h>
 *
 * 72    12/30/98 5:17p Jeff
 * changes made to handle script name override, to override the name of
 * the script to use in a module.
 *
 * 71    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 70    12/17/98 7:26p Jeff
 * new script system data
 *
 * 69    12/01/98 4:31p Chris
 *
 * 68    12/01/98 4:31p Chris
 * Checked in a massive amount of AI work.  Improved flocking code.  :)
 * (Still hacked lightly).  In addition, I am moving toward using the
 * composite dir.  :)
 *
 * 67    11/19/98 8:36p Chris
 * Tweaked
 *
 * 66    11/19/98 8:26p Chris
 * Starting to add generic team avoidance code
 *
 * 65    11/13/98 12:30p Jason
 * changes for weapons
 *
 * 64    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 63    11/05/98 7:54p Jason
 * changes for new manage system
 *
 * 62    11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 61    10/23/98 6:43p Matt
 * Kill the gunboy's sounds (for the demo).
 *
 * 60    10/12/98 11:38p Jeff
 * wrapped all the Object_info[].description whenever freed...trying to
 * find an obscure bug.  Added icon_name to manage page of Generic
 *
 * 59    10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 58    10/08/98 10:03p Jason
 * more filtered table file stuff
 *
 * 57    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 56    8/26/98 8:07p Jason
 * added directional lights to objects
 *
 * 55    8/25/98 3:42p Jason
 * fixed generic object problems
 *
 * 54    8/24/98 2:37p Jason
 * made table file more efficient with regards to invalid names
 *
 * 53    8/19/98 6:29p Chris
 *
 * 52    8/16/98 6:17p Chris
 * Added generic object spewing code
 *
 * 51    8/15/98 6:12p Chris
 * Added 13 new AI fields
 *
 * 50    8/14/98 4:56p Jeff
 * added quad fire mask for weapon battery
 *
 * 49    6/12/98 1:06p Jason
 * added smart loading from local table file
 *
 * 48    6/04/98 6:44p Jason
 * implemented smart FindGenericPage function
 *
 * 47    6/01/98 10:37a Matt
 * Added system to spew powerups when the player dies.  Still needs Jason
 * to deal with  mng_FindSpecificGenericPage().
 *
 * 46    5/18/98 8:06p Chris
 * Removed an unused AI value
 *
 * 45    5/07/98 1:41p Chris
 * Added hit_death_dot
 *
 * 44    5/03/98 5:38p Chris
 * Added sounds to anim page
 *
 * 43    4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 42    4/03/98 10:07a Chris
 * Added support for objects getting their size computed when the
 * polymodel is paged in the first time as an object
 *
 * 41    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 40    3/31/98 3:49p Jason
 * added memory lib
 *
 * 39    3/23/98 10:03a Chris
 * Added independant wb animations
 *
 * 38    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 37    3/11/98 4:59p Chris
 * Changed the ComputeDefualtSize function call
 *
 * 36    3/10/98 6:54p Chris
 * All start and end frame for ComputeDefaultSize
 *
 * 35    3/02/98 6:56p Chris
 * Changed melee_dist to melee_damage
 *
 * 34    3/02/98 6:43p Chris
 *
 * 33    3/02/98 4:16p Chris
 * Added 14 new fields to the AI Settings Dialog/page.
 *
 * 32    2/23/98 1:22p Jason
 * made FindSpecific* read from the local drive, not the net drive - when
 * starting the editor
 *
 * 31    2/06/98 2:15a Chris
 * Activated the max_velocity, max_delta_velocity, and max_turn_rate
 * fields for AI objects.
 *
 * 30    2/04/98 11:47a Jason
 * added dynamic description field to generic pages
 *
 * 29    1/29/98 3:29p Chris
 * Major update to the AI system.
 *
 * 28    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 27    1/15/98 6:22p Jason
 * added safety checks so the network won't copy over a primitive you have
 * held locally
 *
 * 26    1/05/98 3:55p Chris
 * Added explosion and ambient sounds
 *
 * 25    12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 24    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 23    11/25/97 1:16p Jason
 * added lod system for certain objects
 *
 * 22    11/17/97 10:47p Jason
 * fixed loading/saving of flicker_distance
 *
 * 21    11/05/97 12:22p Chris
 * Fixed size of wb_info in the page file
 *
 * 20    11/06/97 11:09a Jason
 * added extra assert to catch errors
 *
 * 19    10/28/97 12:23p Chris
 * We now save out more AI info
 *
 * 18    10/01/97 11:01a Chris
 * Added new support for additional physics items
 *
 * 17    9/24/97 6:18p Samir
 * Use script names instead of script id values to identify scripts.
 *
 * 16    9/17/97 10:59a Chris
 * Added a new way to compute radi
 *
 * 15    9/10/97 5:26p Jason
 * fixed stupid off by one bug
 *
 * 14    9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 13    9/10/97 11:44a Chris
 * Added support for weapon batteries
 *
 * 12    9/08/97 11:51a Chris
 * Extended the weapon system
 *
 * 11    9/05/97 1:29p Jason
 * revamped generic object lighting
 *
 * 10    9/04/97 5:49p Jason
 * made generic pages read/write pulse time for lighting
 *
 * 9     9/04/97 3:21p Jason
 * added pulse timing for lit objects
 *
 * 8     9/03/97 6:18p Jason
 * added code to support powerups/robots/etc that cast light
 *
 * 7     9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 6     8/13/97 4:54p Matt
 * Added destroyable flag & hitpoints
 *
 * 5     8/11/97 6:47p Matt
 * Fixed read/write size mismatches in generic page
 *
 * 4     8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 3     8/08/97 5:25p Matt
 * Type was writing as byte but reading as int
 *
 * 2     8/08/97 3:44p Jason
 * added code to support new generic page
 *
 * 1     8/08/97 1:29p Jason
 * file for object_info pages
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "genericpage.h"
#include "soundpage.h"
#include "weaponpage.h"
#include "mono.h"
#include "pserror.h"
#include "polymodel.h"
#include "ddio.h"
#include "robotfire.h"
#include "weapon.h"
#include "sounds.h"
#include "mem.h"
#include "args.h"

#define GENERICFILE_VERSION 27

// genericpage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define GENERICPAGE_COMMAND_NAME 1
#define GENERICPAGE_COMMAND_END 2
#define GENERICPAGE_COMMAND_IMAGE_NAME 3
#define GENERICPAGE_COMMAND_VERSION 4
#define GENERICPAGE_COMMAND_PHYS_MASS 5
#define GENERICPAGE_COMMAND_PHYS_DRAG 6
#define GENERICPAGE_COMMAND_SIZE 7
#define GENERICPAGE_COMMAND_ANIM_STATES 8
#define GENERICPAGE_COMMAND_FLAGS 9

#define GENERICPAGE_COMMAND_PHYS_FLAGS 10

// AI info
#define GENERICPAGE_COMMAND_AI_INFO 11
#define GENERICPAGE_COMMAND_TYPE 12
#define GENERICPAGE_COMMAND_SCORE 13
#define GENERICPAGE_COMMAND_SCRIPT 14
#define GENERICPAGE_COMMAND_SOUND_NAME 15

#define GENERICPAGE_COMMAND_HITPOINTS 16

#define GENERICPAGE_COMMAND_LIGHT_CAST 17

#define GENERICPAGE_COMMAND_WB_INFO 18
#define GENERICPAGE_COMMAND_WB_WEAPON 19
#define GENERICPAGE_COMMAND_SCRIPTNAME 20

#define GENERICPAGE_COMMAND_ROT_DRAG 21
#define GENERICPAGE_COMMAND_FULL_THRUST 22
#define GENERICPAGE_COMMAND_FULL_ROTTHRUST 23
#define GENERICPAGE_COMMAND_TURNROLL_RATE 24
#define GENERICPAGE_COMMAND_TURNROLL_RATIO 25
#define GENERICPAGE_COMMAND_WIGGLE_AMP 26
#define GENERICPAGE_COMMAND_WIGGLE_FREQ 27
#define GENERICPAGE_COMMAND_INT_VELOCITY 28
#define GENERICPAGE_COMMAND_INT_ROTVEL 29
#define GENERICPAGE_COMMAND_NUM_BOUNCES 30
#define GENERICPAGE_COMMAND_COEFF_REST 31

#define GENERICPAGE_COMMAND_FLICKER_DISTANCE 32

#define GENERICPAGE_COMMAND_LOD_MODELS 33

// Impact stuff
#define GENERICPAGE_COMMAND_IMPACT 34

#define GENERICPAGE_COMMAND_WB_FIRE_SOUND 35

#define GENERICPAGE_COMMAND_WB_FLAGS 36
#define GENERICPAGE_COMMAND_DESCRIPTION 37

#define GENERICPAGE_COMMAND_AI_SOUND_NAME 38
#define GENERICPAGE_COMMAND_LOD_DISTANCE 39
#define GENERICPAGE_COMMAND_ANIM_SOUND_NAME 40

#define GENERICPAGE_COMMAND_HIT_DIE_DOT 41
#define GENERICPAGE_COMMAND_WB_QUADMASK 42

#define GENERICPAGE_COMMAND_AI_INFO2 43

#define GENERICPAGE_COMMAND_DSPEW_INFO 44
#define GENERICPAGE_COMMAND_DIRECTION_DOT 45

#define GENERICPAGE_COMMAND_ICON_NAME 46

void mng_WriteLightingChunk(light_info *lighting_info, CFILE *outfile);
void mng_ReadLightingChunk(light_info *lighting_info, CFILE *infile);

extern bool Running_editor; // in init.cpp
extern char *TablefileNameOverride;

// Sets a page structure to default values
void mng_InitGenericPage(mngs_generic_page *genericpage) {
  int i;

  memset(genericpage, 0, sizeof(mngs_generic_page));
  strcpy(genericpage->image_name, "");

  strcpy(genericpage->med_image_name, "");
  strcpy(genericpage->lo_image_name, "");

  for (i = 0; i < MAX_OBJ_SOUNDS; i++)
    strcpy(genericpage->sound_name[i], "");

  for (i = 0; i < MAX_AI_SOUNDS; i++)
    strcpy(genericpage->ai_sound_name[i], "");

  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    strcpy(genericpage->dspew_name[i], "\0");
  }

  genericpage->objinfo_struct.description = NULL;
  genericpage->objinfo_struct.icon_name[0] = '\0';

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++)
    for (int j = 0; j < NUM_ANIMS_PER_CLASS; j++)
      strcpy(genericpage->anim_sound_name[i][j], "");

  genericpage->objinfo_struct.med_lod_distance = DEFAULT_MED_LOD_DISTANCE;
  genericpage->objinfo_struct.lo_lod_distance = DEFAULT_LO_LOD_DISTANCE;

  genericpage->objinfo_struct.phys_info.hit_die_dot = 1.0f;
  genericpage->objinfo_struct.respawn_scalar = 1.0f;

  genericpage->ai_info.curiousity = .5f;
  genericpage->ai_info.night_vision = .7f;
  genericpage->ai_info.fog_vision = .7f;
  genericpage->ai_info.lead_accuracy = 1.0f;
  genericpage->ai_info.lead_varience = 0.0f;
  genericpage->ai_info.fire_spread = 0.0f;
  genericpage->ai_info.fight_team = 0.15f;
  genericpage->ai_info.fight_same = 0.8f;
  genericpage->ai_info.agression = 0.5f;
  genericpage->ai_info.hearing = 1.0f;
  genericpage->ai_info.frustration = 0.5f;
  genericpage->ai_info.roaming = 0.5f;
  genericpage->ai_info.life_preservation = 0.0f;
  genericpage->objinfo_struct.module_name[0] = '\0';

  for (i = 0; i < MAX_DEATH_TYPES; i++) {
    genericpage->objinfo_struct.death_types[i].flags = 0;
    genericpage->objinfo_struct.death_types[i].delay_min = 0.0;
    genericpage->objinfo_struct.death_types[i].delay_max = 0.0;
    genericpage->objinfo_struct.death_probabilities[i] = 0;
  }
}

// Given an open file pointer and a generic_page struct, writes that generic page out
void mng_WriteGenericPage(CFILE *outfile, mngs_generic_page *genericpage) {
  int i, size;

  ASSERT(outfile != NULL);
  ASSERT(genericpage != NULL);
  ASSERT((strlen(genericpage->image_name)) > 2);

  cf_WriteByte(outfile, PAGETYPE_GENERIC);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_VERSION);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, GENERICFILE_VERSION);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_TYPE);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, genericpage->objinfo_struct.type);

  // Write the name
  cf_WriteByte(outfile, GENERICPAGE_COMMAND_NAME);
  cf_WriteByte(outfile, strlen(genericpage->objinfo_struct.name) + 1);
  cf_WriteString(outfile, genericpage->objinfo_struct.name);

  // Write the model name
  cf_WriteByte(outfile, GENERICPAGE_COMMAND_IMAGE_NAME);
  cf_WriteByte(outfile, strlen(genericpage->image_name) + 1);
  cf_WriteString(outfile, genericpage->image_name);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_IMPACT);
  cf_WriteByte(outfile, 3 * sizeof(float));
  cf_WriteFloat(outfile, genericpage->objinfo_struct.impact_size);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.impact_time);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.damage);

  // Write the LOD model names
  cf_WriteByte(outfile, GENERICPAGE_COMMAND_LOD_MODELS);
  size = strlen(genericpage->med_image_name) + 1;
  size += strlen(genericpage->lo_image_name) + 1;

  cf_WriteByte(outfile, size);
  cf_WriteString(outfile, genericpage->med_image_name);
  cf_WriteString(outfile, genericpage->lo_image_name);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_SCORE);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, genericpage->objinfo_struct.score);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_SCRIPTNAME);
  cf_WriteByte(outfile, strlen("") + 1); // genericpage->objinfo_struct.script_name
  cf_WriteString(outfile, "");

  if (genericpage->objinfo_struct.description != NULL) {
    cf_WriteByte(outfile, GENERICPAGE_COMMAND_DESCRIPTION);
    cf_WriteByte(outfile, strlen(genericpage->objinfo_struct.description) + 1);
    cf_WriteString(outfile, genericpage->objinfo_struct.description);
  }

  if (genericpage->objinfo_struct.icon_name[0] != '\0') {
    cf_WriteByte(outfile, GENERICPAGE_COMMAND_ICON_NAME);
    cf_WriteByte(outfile, strlen(genericpage->objinfo_struct.icon_name) + 1);
    cf_WriteString(outfile, genericpage->objinfo_struct.icon_name);
  }

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_LOD_DISTANCE);
  cf_WriteByte(outfile, 8);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.med_lod_distance);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lo_lod_distance);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_PHYS_MASS);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.mass);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_PHYS_DRAG);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.drag);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_SIZE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.size);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_LIGHT_CAST);
  cf_WriteByte(outfile, (10 * 4) + 2);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.light_distance);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.red_light1);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.green_light1);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.blue_light1);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.time_interval);

  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.red_light2);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.green_light2);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.blue_light2);
  cf_WriteInt(outfile, genericpage->objinfo_struct.lighting_info.flags);
  cf_WriteInt(outfile, genericpage->objinfo_struct.lighting_info.timebits);
  cf_WriteByte(outfile, genericpage->objinfo_struct.lighting_info.angle);
  cf_WriteByte(outfile, genericpage->objinfo_struct.lighting_info.lighting_render_type);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_FLICKER_DISTANCE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.flicker_distance);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_DIRECTION_DOT);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lighting_info.directional_dot);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_HITPOINTS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, genericpage->objinfo_struct.hit_points);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, genericpage->objinfo_struct.flags);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_PHYS_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, genericpage->objinfo_struct.phys_info.flags);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_ROT_DRAG);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.rotdrag);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_FULL_THRUST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.full_thrust);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_FULL_ROTTHRUST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.full_rotthrust);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_TURNROLL_RATE);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.max_turnroll_rate);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_TURNROLL_RATIO);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.turnroll_ratio);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_WIGGLE_AMP);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.wiggle_amplitude);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_WIGGLE_FREQ);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.wiggles_per_sec);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_INT_VELOCITY);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.velocity.z);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_INT_ROTVEL);
  cf_WriteByte(outfile, 12);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.rotvel.x);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.rotvel.y);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.rotvel.z);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_NUM_BOUNCES);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, genericpage->objinfo_struct.phys_info.num_bounces);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_COEFF_REST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.coeff_restitution);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_HIT_DIE_DOT);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.phys_info.hit_die_dot);

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_AI_INFO);
  cf_WriteByte(outfile, 76);

  cf_WriteInt(outfile, genericpage->ai_info.flags);
  cf_WriteByte(outfile, genericpage->ai_info.ai_class);
  cf_WriteByte(outfile, genericpage->ai_info.ai_type);
  cf_WriteByte(outfile, genericpage->ai_info.movement_type);
  cf_WriteByte(outfile, genericpage->ai_info.movement_subtype);
  cf_WriteFloat(outfile, genericpage->ai_info.fov);

  cf_WriteFloat(outfile, genericpage->ai_info.max_velocity);
  cf_WriteFloat(outfile, genericpage->ai_info.max_delta_velocity);
  cf_WriteFloat(outfile, genericpage->ai_info.max_turn_rate);

  cf_WriteFloat(outfile, genericpage->ai_info.avoid_friends_distance);

  // Makes sure there are no bugs as things are added and removed  -- ask chris
  genericpage->ai_info.notify_flags &= ~AI_NOTIFIES_ALWAYS_ON;
  cf_WriteInt(outfile, genericpage->ai_info.notify_flags);
  genericpage->ai_info.notify_flags |= AI_NOTIFIES_ALWAYS_ON;

  cf_WriteFloat(outfile, genericpage->ai_info.max_delta_turn_rate);
  cf_WriteFloat(outfile, genericpage->ai_info.circle_distance);
  cf_WriteFloat(outfile, genericpage->ai_info.attack_vel_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.dodge_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.dodge_vel_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.flee_vel_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_damage[0]);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_damage[1]);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_latency[0]);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_latency[1]);

  for (i = 0; i < MAX_OBJ_SOUNDS; i++) {
    cf_WriteByte(outfile, GENERICPAGE_COMMAND_SOUND_NAME);
    cf_WriteByte(outfile, strlen(genericpage->sound_name[i]) + 2); // 1 for sound index, 1 for null term
    cf_WriteByte(outfile, i);
    cf_WriteString(outfile, genericpage->sound_name[i]);
  }

  for (i = 0; i < MAX_AI_SOUNDS; i++) {
    cf_WriteByte(outfile, GENERICPAGE_COMMAND_AI_SOUND_NAME);
    cf_WriteByte(outfile, strlen(genericpage->ai_sound_name[i]) + 2); // 1 for sound index, 1 for null term
    cf_WriteByte(outfile, i);
    cf_WriteString(outfile, genericpage->ai_sound_name[i]);
  }

  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    cf_WriteByte(outfile, GENERICPAGE_COMMAND_DSPEW_INFO);
    cf_WriteByte(outfile, strlen(genericpage->dspew_name[i]) + 9); // 1 for null charactor
    cf_WriteByte(outfile, i);
    cf_WriteByte(outfile, genericpage->objinfo_struct.f_dspew);
    cf_WriteFloat(outfile, genericpage->objinfo_struct.dspew_percent[i]);
    cf_WriteShort(outfile, genericpage->objinfo_struct.dspew_number[i]);
    cf_WriteString(outfile, genericpage->dspew_name[i]);
  }

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_AI_INFO2);
  cf_WriteByte(outfile, 13 * sizeof(float));
  cf_WriteFloat(outfile, genericpage->ai_info.curiousity);
  cf_WriteFloat(outfile, genericpage->ai_info.night_vision);
  cf_WriteFloat(outfile, genericpage->ai_info.fog_vision);
  cf_WriteFloat(outfile, genericpage->ai_info.lead_accuracy);
  cf_WriteFloat(outfile, genericpage->ai_info.lead_varience);
  cf_WriteFloat(outfile, genericpage->ai_info.fire_spread);
  cf_WriteFloat(outfile, genericpage->ai_info.fight_team);
  cf_WriteFloat(outfile, genericpage->ai_info.fight_same);
  cf_WriteFloat(outfile, genericpage->ai_info.agression);
  cf_WriteFloat(outfile, genericpage->ai_info.hearing);
  cf_WriteFloat(outfile, genericpage->ai_info.frustration);
  cf_WriteFloat(outfile, genericpage->ai_info.roaming);
  cf_WriteFloat(outfile, genericpage->ai_info.life_preservation);

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    int j;
    cf_WriteByte(outfile, GENERICPAGE_COMMAND_ANIM_STATES);

    size = sizeof(anim_entry) * NUM_ANIMS_PER_CLASS;
    size++; // add a byte to tell which class this is for

    cf_WriteByte(outfile, size);

    cf_WriteByte(outfile, i);
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
      cf_WriteShort(outfile, genericpage->anim[i].elem[j].from);
      cf_WriteShort(outfile, genericpage->anim[i].elem[j].to);
      cf_WriteFloat(outfile, genericpage->anim[i].elem[j].spc);
    }
  }

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_WB_FLAGS);
  cf_WriteByte(outfile, sizeof(int) * MAX_WBS_PER_OBJ);
  for (i = 0; i < MAX_WBS_PER_OBJ; i++)
    cf_WriteByte(outfile, genericpage->static_wb[i].flags);

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    int j;

    cf_WriteByte(outfile, GENERICPAGE_COMMAND_WB_INFO);
    size = 202;

    cf_WriteByte(outfile, size);

    cf_WriteByte(outfile, i);
    for (j = 0; j < MAX_WB_GUNPOINTS; j++)
      cf_WriteShort(outfile, genericpage->static_wb[i].gp_weapon_index[j]);
    cf_WriteShort(outfile, genericpage->static_wb[i].aiming_gp_index);

    cf_WriteByte(outfile, genericpage->static_wb[i].num_masks);
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_WriteByte(outfile, genericpage->static_wb[i].gp_fire_masks[j]);
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_WriteFloat(outfile, genericpage->static_wb[i].gp_fire_wait[j]);

    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      cf_WriteFloat(outfile, genericpage->static_wb[i].anim_time[j]);
      cf_WriteFloat(outfile, genericpage->static_wb[i].anim_start_frame[j]);
      cf_WriteFloat(outfile, genericpage->static_wb[i].anim_fire_frame[j]);
      cf_WriteFloat(outfile, genericpage->static_wb[i].anim_end_frame[j]);
    }

    cf_WriteByte(outfile, genericpage->static_wb[i].aiming_flags);
    cf_WriteFloat(outfile, genericpage->static_wb[i].aiming_3d_dot);
    cf_WriteFloat(outfile, genericpage->static_wb[i].aiming_3d_dist);
    cf_WriteFloat(outfile, genericpage->static_wb[i].aiming_XZ_dot);
  }

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    int j;
    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      cf_WriteByte(outfile, GENERICPAGE_COMMAND_WB_WEAPON);
      size = strlen(genericpage->weapon_name[i][j]) + 1 + 2; // 1 for the null charactor and 2 for the 2 indices

      cf_WriteByte(outfile, size);

      cf_WriteByte(outfile, i);
      cf_WriteByte(outfile, j);
      cf_WriteString(outfile, genericpage->weapon_name[i][j]);
    }
  }

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_WB_QUADMASK);
  cf_WriteByte(outfile, MAX_WBS_PER_OBJ);
  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    cf_WriteByte(outfile, genericpage->static_wb[i].gp_quad_fire_mask);
  }

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    int j;
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      cf_WriteByte(outfile, GENERICPAGE_COMMAND_WB_FIRE_SOUND);
      size = strlen(genericpage->fire_sound_name[i][j]) + 1 + 2; // 1 for the null charactor and 2 for the 2 indices

      cf_WriteByte(outfile, size);

      cf_WriteByte(outfile, i);
      cf_WriteByte(outfile, j);
      cf_WriteString(outfile, genericpage->fire_sound_name[i][j]);
    }
  }

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    int j;
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
      cf_WriteByte(outfile, GENERICPAGE_COMMAND_ANIM_SOUND_NAME);
      size = strlen(genericpage->anim_sound_name[i][j]) + 1 + 2; // 1 for the null charactor and 2 for the 2 indices

      cf_WriteByte(outfile, size);

      cf_WriteByte(outfile, i);
      cf_WriteByte(outfile, j);
      cf_WriteString(outfile, genericpage->anim_sound_name[i][j]);
    }
  }

  cf_WriteByte(outfile, GENERICPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}

// Given an open file pointer and a generic_page struct, writes that generic page out
void mng_WriteNewGenericPage(CFILE *outfile, mngs_generic_page *genericpage) {
  int i, j;

  ASSERT(outfile != NULL);
  ASSERT(genericpage != NULL);
  ASSERT((strlen(genericpage->image_name)) > 2);

  int offset = StartManagePage(outfile, PAGETYPE_GENERIC);

  cf_WriteShort(outfile, GENERICFILE_VERSION);

  cf_WriteByte(outfile, genericpage->objinfo_struct.type);

  // Write out object name
  cf_WriteString(outfile, genericpage->objinfo_struct.name);

  // Write out model names
  cf_WriteString(outfile, genericpage->image_name);
  cf_WriteString(outfile, genericpage->med_image_name);
  cf_WriteString(outfile, genericpage->lo_image_name);

  // Write out impact data
  cf_WriteFloat(outfile, genericpage->objinfo_struct.impact_size);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.impact_time);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.damage);

  // Write score
  cf_WriteShort(outfile, genericpage->objinfo_struct.score);

  // Write ammo
  if (genericpage->objinfo_struct.type == OBJ_POWERUP)
    cf_WriteShort(outfile, genericpage->objinfo_struct.ammo_count);

  // Write script name
  cf_WriteString(outfile, ""); // genericpage->objinfo_struct.script_name

  // Write module name
  cf_WriteString(outfile, genericpage->objinfo_struct.module_name);

  // Write scriptname override
  cf_WriteString(outfile, genericpage->objinfo_struct.script_name_override);

  if (genericpage->objinfo_struct.description != NULL) {
    // Write description if there is one
    cf_WriteByte(outfile, 1);
    cf_WriteString(outfile, genericpage->objinfo_struct.description);
  } else
    cf_WriteByte(outfile, 0);

  // Write icon name
  cf_WriteString(outfile, genericpage->objinfo_struct.icon_name);

  // Write LOD distances
  cf_WriteFloat(outfile, genericpage->objinfo_struct.med_lod_distance);
  cf_WriteFloat(outfile, genericpage->objinfo_struct.lo_lod_distance);

  // Write physics stuff
  mng_WritePhysicsChunk(&genericpage->objinfo_struct.phys_info, outfile);

  // Write size
  cf_WriteFloat(outfile, genericpage->objinfo_struct.size);

  // Write light info
  mng_WriteLightingChunk(&genericpage->objinfo_struct.lighting_info, outfile);

  // Write hit points
  cf_WriteInt(outfile, genericpage->objinfo_struct.hit_points);

  // Write flags
  cf_WriteInt(outfile, genericpage->objinfo_struct.flags);

  // Write AI info
  cf_WriteInt(outfile, genericpage->ai_info.flags);
  cf_WriteByte(outfile, genericpage->ai_info.ai_class);
  cf_WriteByte(outfile, genericpage->ai_info.ai_type);
  cf_WriteByte(outfile, genericpage->ai_info.movement_type);
  cf_WriteByte(outfile, genericpage->ai_info.movement_subtype);
  cf_WriteFloat(outfile, genericpage->ai_info.fov);

  cf_WriteFloat(outfile, genericpage->ai_info.max_velocity);
  cf_WriteFloat(outfile, genericpage->ai_info.max_delta_velocity);
  cf_WriteFloat(outfile, genericpage->ai_info.max_turn_rate);

  // Makes sure there are no bugs as things are added and removed  -- ask chris
  genericpage->ai_info.notify_flags &= ~AI_NOTIFIES_ALWAYS_ON;
  cf_WriteInt(outfile, genericpage->ai_info.notify_flags);
  genericpage->ai_info.notify_flags |= AI_NOTIFIES_ALWAYS_ON;

  cf_WriteFloat(outfile, genericpage->ai_info.max_delta_turn_rate);
  cf_WriteFloat(outfile, genericpage->ai_info.circle_distance);
  cf_WriteFloat(outfile, genericpage->ai_info.attack_vel_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.dodge_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.dodge_vel_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.flee_vel_percent);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_damage[0]);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_damage[1]);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_latency[0]);
  cf_WriteFloat(outfile, genericpage->ai_info.melee_latency[1]);

  cf_WriteFloat(outfile, genericpage->ai_info.curiousity);
  cf_WriteFloat(outfile, genericpage->ai_info.night_vision);
  cf_WriteFloat(outfile, genericpage->ai_info.fog_vision);
  cf_WriteFloat(outfile, genericpage->ai_info.lead_accuracy);
  cf_WriteFloat(outfile, genericpage->ai_info.lead_varience);
  cf_WriteFloat(outfile, genericpage->ai_info.fire_spread);
  cf_WriteFloat(outfile, genericpage->ai_info.fight_team);
  cf_WriteFloat(outfile, genericpage->ai_info.fight_same);
  cf_WriteFloat(outfile, genericpage->ai_info.agression);
  cf_WriteFloat(outfile, genericpage->ai_info.hearing);
  cf_WriteFloat(outfile, genericpage->ai_info.frustration);
  cf_WriteFloat(outfile, genericpage->ai_info.roaming);
  cf_WriteFloat(outfile, genericpage->ai_info.life_preservation);
  cf_WriteFloat(outfile, genericpage->ai_info.avoid_friends_distance);

  cf_WriteFloat(outfile, genericpage->ai_info.biased_flight_importance);
  cf_WriteFloat(outfile, genericpage->ai_info.biased_flight_min);
  cf_WriteFloat(outfile, genericpage->ai_info.biased_flight_max);

  // Write out objects spewed
  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    cf_WriteByte(outfile, genericpage->objinfo_struct.f_dspew);
    cf_WriteFloat(outfile, genericpage->objinfo_struct.dspew_percent[i]);
    cf_WriteShort(outfile, genericpage->objinfo_struct.dspew_number[i]);
    cf_WriteString(outfile, genericpage->dspew_name[i]);
  }

  // Write out animation info
  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
      cf_WriteShort(outfile, genericpage->anim[i].elem[j].from);
      cf_WriteShort(outfile, genericpage->anim[i].elem[j].to);
      cf_WriteFloat(outfile, genericpage->anim[i].elem[j].spc);
    }
  }

  // Write out weapon batteries
  for (i = 0; i < MAX_WBS_PER_OBJ; i++)
    mng_WriteWeaponBatteryChunk(&genericpage->static_wb[i], outfile);

  // Write out weapon names
  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (j = 0; j < MAX_WB_GUNPOINTS; j++)
      cf_WriteString(outfile, genericpage->weapon_name[i][j]);
  }

  // Write out sounds
  for (i = 0; i < MAX_OBJ_SOUNDS; i++)
    cf_WriteString(outfile, genericpage->sound_name[i]);

  for (i = 0; i < MAX_AI_SOUNDS; i++)
    cf_WriteString(outfile, genericpage->ai_sound_name[i]);

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_WriteString(outfile, genericpage->fire_sound_name[i][j]);
  }

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++)
      cf_WriteString(outfile, genericpage->anim_sound_name[i][j]);
  }

  // Write out respawn scalar
  cf_WriteFloat(outfile, genericpage->objinfo_struct.respawn_scalar);

  // Write out death information
  cf_WriteShort(outfile, MAX_DEATH_TYPES);
  for (i = 0; i < MAX_DEATH_TYPES; i++) {
    cf_WriteInt(outfile, genericpage->objinfo_struct.death_types[i].flags);
    cf_WriteFloat(outfile, genericpage->objinfo_struct.death_types[i].delay_min);
    cf_WriteFloat(outfile, genericpage->objinfo_struct.death_types[i].delay_max);
    cf_WriteByte(outfile, genericpage->objinfo_struct.death_probabilities[i]);
  }

  EndManagePage(outfile, offset);
}

// Old delay types
#define OLD_DF_DELAY_NONE 0x0000000
#define OLD_DF_DELAY_MIN_MAX 0x0000001
#define OLD_DF_DELAY_FROM_ANIM 0x0000002
#define OLD_DF_DELAY_MASK 0x0000003
#define OLD_DF_DELAY_SHIFT 0

void GenericPageSetPowerupDefaultAmmo(object_info *ip) {
  // Default is zero
  ip->ammo_count = 0;

  // Set for specific types
  if (!stricmp(ip->name, "Vauss"))
    ip->ammo_count = 5000;
  if (!stricmp(ip->name, "Napalm"))
    ip->ammo_count = 500;
  if (!stricmp(ip->name, "MassDriver"))
    ip->ammo_count = 20;

  if (!stricmp(ip->name, "Frag"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "ImpactMortar"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "NapalmRocket"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "Cyclone"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "BlackShark"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "Concussion"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "Homing"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "Smart"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "Mega"))
    ip->ammo_count = 1;
  if (!stricmp(ip->name, "Guided"))
    ip->ammo_count = 1;

  if (!stricmp(ip->name, "4PackHoming"))
    ip->ammo_count = 4;
  if (!stricmp(ip->name, "4PackConc"))
    ip->ammo_count = 4;
  if (!stricmp(ip->name, "4PackFrag"))
    ip->ammo_count = 4;
  if (!stricmp(ip->name, "4PackGuided"))
    ip->ammo_count = 4;

  if (!stricmp(ip->name, "Vauss clip"))
    ip->ammo_count = 1250;
  if (!stricmp(ip->name, "MassDriverAmmo"))
    ip->ammo_count = 5;
  if (!stricmp(ip->name, "NapalmTank"))
    ip->ammo_count = 100;
}

// Reads a generic page from an open file.  Returns 0 on error.
int mng_ReadNewGenericPage(CFILE *infile, mngs_generic_page *genericpage) {
  int i, j;

  ASSERT(infile != NULL);
  mng_InitGenericPage(genericpage);

  int version = cf_ReadShort(infile);

  genericpage->objinfo_struct.type = cf_ReadByte(infile);

  // Read object name
  cf_ReadString(genericpage->objinfo_struct.name, PAGENAME_LEN, infile);

  // Read model names
  cf_ReadString(genericpage->image_name, PAGENAME_LEN, infile);
  cf_ReadString(genericpage->med_image_name, PAGENAME_LEN, infile);
  cf_ReadString(genericpage->lo_image_name, PAGENAME_LEN, infile);

  // Read out impact data
  genericpage->objinfo_struct.impact_size = cf_ReadFloat(infile);
  genericpage->objinfo_struct.impact_time = cf_ReadFloat(infile);
  genericpage->objinfo_struct.damage = cf_ReadFloat(infile);

  // Read score
  if (version >= 24)
    genericpage->objinfo_struct.score = cf_ReadShort(infile);
  else
    genericpage->objinfo_struct.score = cf_ReadByte(infile);

  // Read ammo
  if (genericpage->objinfo_struct.type == OBJ_POWERUP) {
    if (version >= 25)
      genericpage->objinfo_struct.ammo_count = cf_ReadShort(infile);
    else
      GenericPageSetPowerupDefaultAmmo(&genericpage->objinfo_struct);
  } else
    genericpage->objinfo_struct.ammo_count = 0;

  // Read script name
  char dummy[256];
  cf_ReadString(dummy, PAGENAME_LEN, infile); // genericpage->objinfo_struct.script_name

  if (version >= 18) {
    cf_ReadString(genericpage->objinfo_struct.module_name, MAX_MODULENAME_LEN, infile);
  } else {
    genericpage->objinfo_struct.module_name[0] = '\0';
  }

  if (version >= 19) {
    cf_ReadString(genericpage->objinfo_struct.script_name_override, PAGENAME_LEN, infile);
  } else {
    genericpage->objinfo_struct.script_name_override[0] = '\0';
  }

  int desc = cf_ReadByte(infile);
  if (desc) {
    // Read description if there is one
    char tempbuf[1024];

    cf_ReadString(tempbuf, 1024, infile);
    int slen = strlen(tempbuf) + 1;

    genericpage->objinfo_struct.description = (char *)mem_malloc(slen);
    ASSERT(genericpage->objinfo_struct.description);
    strcpy(genericpage->objinfo_struct.description, tempbuf);
  } else
    genericpage->objinfo_struct.description = NULL;

  // Read icon name
  cf_ReadString(genericpage->objinfo_struct.icon_name, PAGENAME_LEN, infile);

  // Read LOD distances
  genericpage->objinfo_struct.med_lod_distance = cf_ReadFloat(infile);
  genericpage->objinfo_struct.lo_lod_distance = cf_ReadFloat(infile);

  // Read physics stuff
  mng_ReadPhysicsChunk(&genericpage->objinfo_struct.phys_info, infile);

  // Write size
  genericpage->objinfo_struct.size = cf_ReadFloat(infile);

  // Write light info
  mng_ReadLightingChunk(&genericpage->objinfo_struct.lighting_info, infile);

  // Read hit points
  genericpage->objinfo_struct.hit_points = cf_ReadInt(infile);

  // Read flags
  genericpage->objinfo_struct.flags = cf_ReadInt(infile);

  // Write AI info
  genericpage->ai_info.flags = cf_ReadInt(infile);
  genericpage->ai_info.ai_class = cf_ReadByte(infile);
  genericpage->ai_info.ai_type = cf_ReadByte(infile);
  genericpage->ai_info.movement_type = cf_ReadByte(infile);
  genericpage->ai_info.movement_subtype = cf_ReadByte(infile);
  genericpage->ai_info.fov = cf_ReadFloat(infile);

  genericpage->ai_info.max_velocity = cf_ReadFloat(infile);
  genericpage->ai_info.max_delta_velocity = cf_ReadFloat(infile);
  genericpage->ai_info.max_turn_rate = cf_ReadFloat(infile);

  // Makes sure there are no bugs as things are added and removed  -- ask chris
  genericpage->ai_info.notify_flags &= ~AI_NOTIFIES_ALWAYS_ON;
  genericpage->ai_info.notify_flags = cf_ReadInt(infile);
  genericpage->ai_info.notify_flags |= AI_NOTIFIES_ALWAYS_ON;

  genericpage->ai_info.max_delta_turn_rate = cf_ReadFloat(infile);
  genericpage->ai_info.circle_distance = cf_ReadFloat(infile);
  genericpage->ai_info.attack_vel_percent = cf_ReadFloat(infile);
  genericpage->ai_info.dodge_percent = cf_ReadFloat(infile);
  genericpage->ai_info.dodge_vel_percent = cf_ReadFloat(infile);
  genericpage->ai_info.flee_vel_percent = cf_ReadFloat(infile);
  genericpage->ai_info.melee_damage[0] = cf_ReadFloat(infile);
  genericpage->ai_info.melee_damage[1] = cf_ReadFloat(infile);
  genericpage->ai_info.melee_latency[0] = cf_ReadFloat(infile);
  genericpage->ai_info.melee_latency[1] = cf_ReadFloat(infile);

  genericpage->ai_info.curiousity = cf_ReadFloat(infile);
  genericpage->ai_info.night_vision = cf_ReadFloat(infile);
  genericpage->ai_info.fog_vision = cf_ReadFloat(infile);
  genericpage->ai_info.lead_accuracy = cf_ReadFloat(infile);
  genericpage->ai_info.lead_varience = cf_ReadFloat(infile);
  genericpage->ai_info.fire_spread = cf_ReadFloat(infile);
  genericpage->ai_info.fight_team = cf_ReadFloat(infile);
  genericpage->ai_info.fight_same = cf_ReadFloat(infile);
  genericpage->ai_info.agression = cf_ReadFloat(infile);
  genericpage->ai_info.hearing = cf_ReadFloat(infile);
  genericpage->ai_info.frustration = cf_ReadFloat(infile);
  genericpage->ai_info.roaming = cf_ReadFloat(infile);
  genericpage->ai_info.life_preservation = cf_ReadFloat(infile);

  if (version >= 16) {
    genericpage->ai_info.avoid_friends_distance = cf_ReadFloat(infile);
  } else if ((genericpage->objinfo_struct.flags | OIF_USES_PHYSICS) && genericpage->ai_info.max_velocity > 0.0f) {
    genericpage->ai_info.flags |= AIF_AUTO_AVOID_FRIENDS;
    genericpage->ai_info.avoid_friends_distance = genericpage->ai_info.circle_distance / 10.f;
    if (genericpage->ai_info.avoid_friends_distance < 4.0f)
      genericpage->ai_info.avoid_friends_distance = 4.0f;
  } else {
    genericpage->ai_info.avoid_friends_distance = 4.0f;
  }

  if (version >= 17) {
    genericpage->ai_info.biased_flight_importance = cf_ReadFloat(infile);
    genericpage->ai_info.biased_flight_min = cf_ReadFloat(infile);
    genericpage->ai_info.biased_flight_max = cf_ReadFloat(infile);
  } else {
    genericpage->ai_info.biased_flight_importance = .5f;
    genericpage->ai_info.biased_flight_min = 10.0f;
    genericpage->ai_info.biased_flight_max = 50.0f;
  }

  // Write out objects spewed
  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    genericpage->objinfo_struct.f_dspew = cf_ReadByte(infile);
    genericpage->objinfo_struct.dspew_percent[i] = cf_ReadFloat(infile);
    genericpage->objinfo_struct.dspew_number[i] = cf_ReadShort(infile);

    // Read spew name
    cf_ReadString(genericpage->dspew_name[i], PAGENAME_LEN, infile);
  }

  // Read out animation info
  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
      if (version < 20) {
        genericpage->anim[i].elem[j].from = cf_ReadByte(infile);
        genericpage->anim[i].elem[j].to = cf_ReadByte(infile);
      } else {
        genericpage->anim[i].elem[j].from = cf_ReadShort(infile);
        genericpage->anim[i].elem[j].to = cf_ReadShort(infile);
      }
      genericpage->anim[i].elem[j].spc = cf_ReadFloat(infile);
    }
  }

  // read weapon batteries
  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    if (version >= 15)
      mng_ReadWeaponBatteryChunk(&genericpage->static_wb[i], infile, 2);
    else
      mng_ReadWeaponBatteryChunk(&genericpage->static_wb[i], infile, 1);
  }

  // read weapon names
  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (j = 0; j < MAX_WB_GUNPOINTS; j++)
      cf_ReadString(genericpage->weapon_name[i][j], PAGENAME_LEN, infile);
  }

  // read sounds
  ASSERT(MAX_OBJ_SOUNDS == 2);
  for (i = 0; i < MAX_OBJ_SOUNDS; i++)
    cf_ReadString(genericpage->sound_name[i], PAGENAME_LEN, infile);
  if (version < 26) { // used to be three sounds
    char temp_sound_name[PAGENAME_LEN];
    cf_ReadString(temp_sound_name, PAGENAME_LEN, infile);
  }

  for (i = 0; i < MAX_AI_SOUNDS; i++)
    cf_ReadString(genericpage->ai_sound_name[i], PAGENAME_LEN, infile);

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
      cf_ReadString(genericpage->fire_sound_name[i][j], PAGENAME_LEN, infile);
  }

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++)
      cf_ReadString(genericpage->anim_sound_name[i][j], PAGENAME_LEN, infile);
  }

  // Read respawn scalar
  if (version >= 21)
    genericpage->objinfo_struct.respawn_scalar = cf_ReadFloat(infile);
  else
    genericpage->objinfo_struct.respawn_scalar = 1.0;

  if (version >= 22) {
    int n_death_types = cf_ReadShort(infile);
    for (i = 0; i < n_death_types; i++) {
      int flags = cf_ReadInt(infile);
      if (version == 22) { // translate death flags
        Int3();            // this version no longer supported
      }

      genericpage->objinfo_struct.death_types[i].flags = flags;
      genericpage->objinfo_struct.death_types[i].delay_min = cf_ReadFloat(infile);
      genericpage->objinfo_struct.death_types[i].delay_max = cf_ReadFloat(infile);
      genericpage->objinfo_struct.death_probabilities[i] = cf_ReadByte(infile);

      // Fix up for changed flags
      if (version < 27) {
        if ((flags & OLD_DF_DELAY_MASK) != OLD_DF_DELAY_MIN_MAX) {
          genericpage->objinfo_struct.death_types[i].delay_min = 0.0;
          genericpage->objinfo_struct.death_types[i].delay_max = 0.0;
        }
        flags &= ~DF_UNUSED;
      }
    }
  }

  // Set score from hitpoints if old version
  if (version < 24) {
    if ((genericpage->objinfo_struct.type == OBJ_ROBOT) ||
        (genericpage->objinfo_struct.type == OBJ_BUILDING && (genericpage->objinfo_struct.flags & OIF_CONTROL_AI)))
      if (genericpage->objinfo_struct.flags & OIF_DESTROYABLE)
        genericpage->objinfo_struct.score = 3 * genericpage->objinfo_struct.hit_points;
  }

  ASSERT(genericpage->objinfo_struct.type != OBJ_NONE);

  return 1; // successfully read
}

// Reads a generic page from an open file.  Returns 0 on error.
int mng_ReadGenericPage(CFILE *infile, mngs_generic_page *genericpage) {
  int done = 0;
  char command;
  uint16_t len;
  int i, temp, version = 0, t;

  if (!Old_table_method)
    return mng_ReadNewGenericPage(infile, genericpage);

  ASSERT(infile != NULL);
  mng_InitGenericPage(genericpage);

  while (!done) {
    // Read in command byte then read in the length of that commands data

    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);

    switch (command) {
    case GENERICPAGE_COMMAND_END:
      done = 1;
      break;
    case GENERICPAGE_COMMAND_VERSION:
      version = cf_ReadByte(infile);
      break;
    case GENERICPAGE_COMMAND_TYPE:
      genericpage->objinfo_struct.type = cf_ReadByte(infile);
      break;
    case GENERICPAGE_COMMAND_SCORE:
      genericpage->objinfo_struct.score = cf_ReadByte(infile);
      break;
    case GENERICPAGE_COMMAND_SCRIPT: // Obsolete as of 09-24-97
      cf_ReadByte(infile);
      break;
    case GENERICPAGE_COMMAND_SCRIPTNAME: {
      char dummy[256];
      cf_ReadString(dummy, len + 1, infile); // genericpage->objinfo_struct.script_name
    } break;
    case GENERICPAGE_COMMAND_DESCRIPTION:
      genericpage->objinfo_struct.description = (char *)mem_malloc(len + 1);
      ASSERT(genericpage->objinfo_struct.description); // out of memory!
      cf_ReadString(genericpage->objinfo_struct.description, len + 1, infile);
      break;
    case GENERICPAGE_COMMAND_ICON_NAME:
      cf_ReadString(genericpage->objinfo_struct.icon_name, len + 1, infile);
      break;
    case GENERICPAGE_COMMAND_IMAGE_NAME: // the name of the generic model
      cf_ReadString(genericpage->image_name, len + 1, infile);
      break;
    case GENERICPAGE_COMMAND_LOD_MODELS: // the name of the lower res models
      cf_ReadString(genericpage->med_image_name, len + 1, infile);
      cf_ReadString(genericpage->lo_image_name, len + 1, infile);
      break;
    case GENERICPAGE_COMMAND_NAME:
      cf_ReadString(genericpage->objinfo_struct.name, len + 1, infile);
      break;
    case GENERICPAGE_COMMAND_SIZE:
      genericpage->objinfo_struct.size = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_LOD_DISTANCE:
      genericpage->objinfo_struct.med_lod_distance = cf_ReadFloat(infile);
      genericpage->objinfo_struct.lo_lod_distance = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_DSPEW_INFO: {
      int i = cf_ReadByte(infile);

      genericpage->objinfo_struct.f_dspew = cf_ReadByte(infile);
      genericpage->objinfo_struct.dspew_percent[i] = cf_ReadFloat(infile);
      genericpage->objinfo_struct.dspew_number[i] = cf_ReadShort(infile);
      cf_ReadString(genericpage->dspew_name[i], len - 7, infile);
    } break;

    case GENERICPAGE_COMMAND_WB_FLAGS: {
      for (int i = 0; i < MAX_WBS_PER_OBJ; i++)
        genericpage->static_wb[i].flags = cf_ReadByte(infile);
    } break;
    case GENERICPAGE_COMMAND_IMPACT:
      genericpage->objinfo_struct.impact_size = cf_ReadFloat(infile);
      genericpage->objinfo_struct.impact_time = cf_ReadFloat(infile);
      genericpage->objinfo_struct.damage = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_FLICKER_DISTANCE:
      genericpage->objinfo_struct.lighting_info.flicker_distance = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_DIRECTION_DOT:
      genericpage->objinfo_struct.lighting_info.directional_dot = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_AI_INFO2:
      genericpage->ai_info.curiousity = cf_ReadFloat(infile);
      genericpage->ai_info.night_vision = cf_ReadFloat(infile);
      genericpage->ai_info.fog_vision = cf_ReadFloat(infile);
      genericpage->ai_info.lead_accuracy = cf_ReadFloat(infile);
      genericpage->ai_info.lead_varience = cf_ReadFloat(infile);
      genericpage->ai_info.fire_spread = cf_ReadFloat(infile);
      genericpage->ai_info.fight_team = cf_ReadFloat(infile);
      genericpage->ai_info.fight_same = cf_ReadFloat(infile);
      genericpage->ai_info.agression = cf_ReadFloat(infile);
      genericpage->ai_info.hearing = cf_ReadFloat(infile);
      genericpage->ai_info.frustration = cf_ReadFloat(infile);
      genericpage->ai_info.roaming = cf_ReadFloat(infile);
      genericpage->ai_info.life_preservation = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_LIGHT_CAST:
      genericpage->objinfo_struct.lighting_info.light_distance = cf_ReadFloat(infile);

      genericpage->objinfo_struct.lighting_info.red_light1 = cf_ReadFloat(infile);
      genericpage->objinfo_struct.lighting_info.green_light1 = cf_ReadFloat(infile);
      genericpage->objinfo_struct.lighting_info.blue_light1 = cf_ReadFloat(infile);

      if (version >= 2)
        genericpage->objinfo_struct.lighting_info.time_interval = cf_ReadFloat(infile);

      if (version >= 3) {
        genericpage->objinfo_struct.lighting_info.red_light2 = cf_ReadFloat(infile);
        genericpage->objinfo_struct.lighting_info.green_light2 = cf_ReadFloat(infile);
        genericpage->objinfo_struct.lighting_info.blue_light2 = cf_ReadFloat(infile);

        genericpage->objinfo_struct.lighting_info.flags = cf_ReadInt(infile);
        genericpage->objinfo_struct.lighting_info.timebits = cf_ReadInt(infile);
        genericpage->objinfo_struct.lighting_info.angle = cf_ReadByte(infile);
      }
      if (version >= 5) {
        genericpage->objinfo_struct.lighting_info.lighting_render_type = cf_ReadByte(infile);
      } else
        genericpage->objinfo_struct.lighting_info.lighting_render_type = LRT_STATIC;

      break;
    case GENERICPAGE_COMMAND_HITPOINTS:
      genericpage->objinfo_struct.hit_points = cf_ReadInt(infile);
      break;
    case GENERICPAGE_COMMAND_PHYS_MASS:
      genericpage->objinfo_struct.phys_info.mass = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_PHYS_DRAG:
      genericpage->objinfo_struct.phys_info.drag = cf_ReadFloat(infile);
      break;
    case GENERICPAGE_COMMAND_ANIM_STATES:
      temp = cf_ReadByte(infile);
      {
        int j;

        for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
          if (version < 20) {
            genericpage->anim[temp].elem[j].from = cf_ReadByte(infile);
            genericpage->anim[temp].elem[j].to = cf_ReadByte(infile);
          } else {
            genericpage->anim[temp].elem[j].from = cf_ReadShort(infile);
            genericpage->anim[temp].elem[j].to = cf_ReadShort(infile);
          }

          if (version <= 3)
            genericpage->anim[temp].elem[j].spc = 1.0f;
          else
            genericpage->anim[temp].elem[j].spc = cf_ReadFloat(infile);
        }
      }
      break;
    case GENERICPAGE_COMMAND_FLAGS: {
      int t = cf_ReadInt(infile);
      genericpage->objinfo_struct.flags = t;
      break;
    }
    case GENERICPAGE_COMMAND_WB_INFO: {
      int i, j;
      i = cf_ReadByte(infile);

      if (version <= 7) {
        for (j = 0; j < MAX_WB_GUNPOINTS; j++)
          genericpage->static_wb[i].gp_weapon_index[j] = cf_ReadInt(infile);
        genericpage->static_wb[i].aiming_gp_index = cf_ReadInt(infile);
      } else {
        for (j = 0; j < MAX_WB_GUNPOINTS; j++)
          genericpage->static_wb[i].gp_weapon_index[j] = cf_ReadShort(infile);
        genericpage->static_wb[i].aiming_gp_index = cf_ReadShort(infile);
      }

      genericpage->static_wb[i].num_masks = cf_ReadByte(infile);
      for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
        genericpage->static_wb[i].gp_fire_masks[j] = cf_ReadByte(infile);
      for (j = 0; j < MAX_WB_FIRING_MASKS; j++)
        genericpage->static_wb[i].gp_fire_wait[j] = cf_ReadFloat(infile);

      for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
        if (version < 12) {
          genericpage->static_wb[i].anim_time[j] = 0.0f;
          genericpage->static_wb[i].anim_start_frame[j] = 0.0f;
          genericpage->static_wb[i].anim_fire_frame[j] = 0.0f;
          genericpage->static_wb[i].anim_end_frame[j] = 0.0f;
        } else {
          genericpage->static_wb[i].anim_time[j] = cf_ReadFloat(infile);
          genericpage->static_wb[i].anim_start_frame[j] = cf_ReadFloat(infile);
          genericpage->static_wb[i].anim_fire_frame[j] = cf_ReadFloat(infile);
          genericpage->static_wb[i].anim_end_frame[j] = cf_ReadFloat(infile);
        }
      }

      genericpage->static_wb[i].aiming_flags = cf_ReadByte(infile);
      genericpage->static_wb[i].aiming_3d_dot = cf_ReadFloat(infile);
      genericpage->static_wb[i].aiming_3d_dist = cf_ReadFloat(infile);
      genericpage->static_wb[i].aiming_XZ_dot = cf_ReadFloat(infile);
      break;
    }
    case GENERICPAGE_COMMAND_WB_QUADMASK: {
      for (int i = 0; i < MAX_WBS_PER_OBJ; i++) {
        genericpage->static_wb[i].gp_quad_fire_mask = cf_ReadByte(infile);
      }
      break;
    }
    case GENERICPAGE_COMMAND_WB_WEAPON: {
      int i, j;

      i = cf_ReadByte(infile);
      j = cf_ReadByte(infile);
      cf_ReadString(genericpage->weapon_name[i][j], len - 1, infile);
      break;
    }
    case GENERICPAGE_COMMAND_WB_FIRE_SOUND: {
      int i, j;

      i = cf_ReadByte(infile);
      j = cf_ReadByte(infile);
      cf_ReadString(genericpage->fire_sound_name[i][j], len - 1, infile);
      break;
    }
    case GENERICPAGE_COMMAND_ANIM_SOUND_NAME: {
      int i, j;

      i = cf_ReadByte(infile);
      j = cf_ReadByte(infile);
      cf_ReadString(genericpage->anim_sound_name[i][j], len - 1, infile);
      break;
    }
    case GENERICPAGE_COMMAND_SOUND_NAME: {
      int i;

      i = cf_ReadByte(infile);

      cf_ReadString(genericpage->sound_name[i], len, infile);

      break;
    }
    case GENERICPAGE_COMMAND_AI_SOUND_NAME: {
      int i;

      i = cf_ReadByte(infile);

      cf_ReadString(genericpage->ai_sound_name[i], len, infile);

      break;
    }
    case GENERICPAGE_COMMAND_AI_INFO:
      if (version <= 6) {
        genericpage->ai_info.flags = cf_ReadInt(infile);
      } else {
        // Makes sure there are no bugs as things are added and removed  -- ask chris
        genericpage->ai_info.notify_flags = AI_NOTIFIES_ALWAYS_ON;

        genericpage->ai_info.flags = cf_ReadInt(infile);
        genericpage->ai_info.ai_class = cf_ReadByte(infile);
        genericpage->ai_info.ai_type = cf_ReadByte(infile);
        if (version < 13)
          cf_ReadInt(infile);
        genericpage->ai_info.movement_type = cf_ReadByte(infile);
        genericpage->ai_info.movement_subtype = cf_ReadByte(infile);
        genericpage->ai_info.fov = cf_ReadFloat(infile);

        if (version >= 10) {
          genericpage->ai_info.max_velocity = cf_ReadFloat(infile);
          genericpage->ai_info.max_delta_velocity = cf_ReadFloat(infile);
          genericpage->ai_info.max_turn_rate = cf_ReadFloat(infile);

          // Makes sure there are no bugs as things are added and removed  -- ask chris
          genericpage->ai_info.notify_flags |= cf_ReadInt(infile);
        }

        if (version >= 11) {
          genericpage->ai_info.max_delta_turn_rate = cf_ReadFloat(infile);
          genericpage->ai_info.circle_distance = cf_ReadFloat(infile);
          genericpage->ai_info.attack_vel_percent = cf_ReadFloat(infile);
          genericpage->ai_info.dodge_percent = cf_ReadFloat(infile);
          genericpage->ai_info.dodge_vel_percent = cf_ReadFloat(infile);
          genericpage->ai_info.flee_vel_percent = cf_ReadFloat(infile);
          genericpage->ai_info.melee_damage[0] = cf_ReadFloat(infile);
          genericpage->ai_info.melee_damage[1] = cf_ReadFloat(infile);
          genericpage->ai_info.melee_latency[0] = cf_ReadFloat(infile);
          genericpage->ai_info.melee_latency[1] = cf_ReadFloat(infile);
        } else {
          genericpage->ai_info.max_delta_turn_rate = 16000.0;
          genericpage->ai_info.circle_distance = 10.0f;
          genericpage->ai_info.attack_vel_percent = 1.0f;
          genericpage->ai_info.dodge_percent = .4f;
          genericpage->ai_info.dodge_vel_percent = .5f;
          genericpage->ai_info.flee_vel_percent = 1.0f;
          genericpage->ai_info.melee_damage[0] = 9.0f;
          genericpage->ai_info.melee_damage[1] = 13.0f;
          genericpage->ai_info.melee_latency[0] = 3.1f;
          genericpage->ai_info.melee_latency[1] = 4.5f;
        }

        if (version >= 16) {
          genericpage->ai_info.avoid_friends_distance = cf_ReadFloat(infile);
        }
      }
      break;
    case GENERICPAGE_COMMAND_PHYS_FLAGS:
      genericpage->objinfo_struct.phys_info.flags = cf_ReadInt(infile);
      break;

    case GENERICPAGE_COMMAND_ROT_DRAG:
      genericpage->objinfo_struct.phys_info.rotdrag = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_FULL_THRUST:
      genericpage->objinfo_struct.phys_info.full_thrust = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_FULL_ROTTHRUST:
      genericpage->objinfo_struct.phys_info.full_rotthrust = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_TURNROLL_RATE:
      genericpage->objinfo_struct.phys_info.max_turnroll_rate = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_TURNROLL_RATIO:
      genericpage->objinfo_struct.phys_info.turnroll_ratio = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_WIGGLE_AMP:
      genericpage->objinfo_struct.phys_info.wiggle_amplitude = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_WIGGLE_FREQ:
      genericpage->objinfo_struct.phys_info.wiggles_per_sec = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_INT_VELOCITY:
      genericpage->objinfo_struct.phys_info.velocity.z = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_INT_ROTVEL:
      genericpage->objinfo_struct.phys_info.rotvel.x = cf_ReadFloat(infile);
      genericpage->objinfo_struct.phys_info.rotvel.y = cf_ReadFloat(infile);
      genericpage->objinfo_struct.phys_info.rotvel.z = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_NUM_BOUNCES:
      genericpage->objinfo_struct.phys_info.num_bounces = cf_ReadInt(infile);
      break;

    case GENERICPAGE_COMMAND_COEFF_REST:
      genericpage->objinfo_struct.phys_info.coeff_restitution = cf_ReadFloat(infile);
      break;

    case GENERICPAGE_COMMAND_HIT_DIE_DOT:
      genericpage->objinfo_struct.phys_info.hit_die_dot = cf_ReadFloat(infile);
      break;

    default:
      // Ignore the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }

  ASSERT(genericpage->objinfo_struct.type != OBJ_NONE);

  if (version < 16) {
    genericpage->ai_info.flags |= AIF_AUTO_AVOID_FRIENDS;
    genericpage->ai_info.avoid_friends_distance = genericpage->ai_info.circle_distance / 10.f;
    if (genericpage->ai_info.avoid_friends_distance < 4.0f)
      genericpage->ai_info.avoid_friends_distance = 4.0f;
  }

  if (!strnicmp("INVALID", genericpage->med_image_name, 7))
    strcpy(genericpage->med_image_name, "");
  if (!strnicmp("INVALID", genericpage->lo_image_name, 7))
    strcpy(genericpage->lo_image_name, "");

  for (i = 0; i < MAX_OBJ_SOUNDS; i++) {
    if (!strnicmp("INVALID", genericpage->sound_name[i], 7))
      strcpy(genericpage->sound_name[i], "");
  }

  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    if (!strnicmp("INVALID", genericpage->dspew_name[i], 7))
      strcpy(genericpage->dspew_name[i], "");
  }

  for (i = 0; i < MAX_AI_SOUNDS; i++) {
    if (!strnicmp("INVALID", genericpage->ai_sound_name[i], 7))
      strcpy(genericpage->ai_sound_name[i], "");
  }

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (t = 0; t < MAX_WB_FIRING_MASKS; t++) {
      if (!strnicmp("INVALID", genericpage->fire_sound_name[i][t], 7))
        strcpy(genericpage->fire_sound_name[i][t], "");
    }
  }

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    for (t = 0; t < NUM_ANIMS_PER_CLASS; t++) {
      if (!strnicmp("INVALID", genericpage->anim_sound_name[i][t], 7))
        strcpy(genericpage->anim_sound_name[i][t], "");
    }
  }
  return 1; // successfully read
}

// Reads in the generic named "name" into genericpage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificGenericPage(char *name, mngs_generic_page *genericpage, int offset) {
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
    mprintf(0, "Couldn't open table file to find generic!\n");
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

    // If not a generic page, just read it in and ignore it
    if (pagetype != PAGETYPE_GENERIC) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewGenericPage(infile, genericpage);

    if (!stricmp(name, genericpage->objinfo_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    } else {
      if (genericpage->objinfo_struct.description != NULL) {
        mem_free(genericpage->objinfo_struct.description);
        genericpage->objinfo_struct.description = NULL;
      }
      genericpage->objinfo_struct.icon_name[0] = '\0';
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

// Given a generic page, allocs a generic and calls AssignGenericPageTogeneric to actually
// load models and values. Rturns generic handle on success, -1 if fail
int mng_SetAndLoadGeneric(mngs_generic_page *genericpage, CFILE *infile) {
  int i, j, n;
  bool f_anim = false;
  bool f_weapons = false;
  bool f_ai = false;

  f_ai = (genericpage->objinfo_struct.flags & OIF_CONTROL_AI) ? true : false;

  if (f_ai) {
    f_weapons = f_anim = true;
  } else {
    if (genericpage->objinfo_struct.type == OBJ_ROBOT || genericpage->objinfo_struct.type == OBJ_BUILDING) {
      f_anim = true;
    } else if (genericpage->objinfo_struct.type == OBJ_POWERUP) {
      if (f_ai) {
        f_anim = true;
      } else {
        for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
          for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
            if (genericpage->anim[i].elem[j].to != 0 || genericpage->anim[i].elem[j].from != 0) {
              f_anim = true;
              break;
            }
          }
        }
      }
    } else if (genericpage->objinfo_struct.type == OBJ_CLUTTER) {
      if (f_ai) {
        f_anim = true;
      } else {
        for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
          for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
            if (genericpage->anim[i].elem[j].to != 0 || genericpage->anim[i].elem[j].from != 0) {
              f_anim = true;
              break;
            }
          }
        }
      }
    }

    for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
      for (j = 0; j < genericpage->static_wb[i].num_masks; j++) {
        if (genericpage->static_wb[i].gp_fire_masks[j] != 0) {
          f_weapons = true;
          break;
        }
      }
    }
  }

  if (Running_editor) {
    f_ai = f_weapons = f_anim = true;
  }

  n = AllocObjectID(genericpage->objinfo_struct.type, f_anim, f_weapons, f_ai);
  if (n < 0)
    return -1;
  if (!mng_AssignGenericPageToObjInfo(genericpage, n, infile))
    return -1;

  return n;
}

// Given a genericpage and a generic handle, attempts to make generic n correspond to
// to the genericpage.
// Returns 1 on success, 0 otherwise
int mng_AssignGenericPageToObjInfo(mngs_generic_page *genericpage, int n, CFILE *infile) {
  object_info *objinfopointer = &Object_info[n];
  int img_handle;
  int i, j;

  // copy our values
  //	memcpy (objinfopointer,&genericpage->objinfo_struct,sizeof(*objinfopointer));
  memcpy(objinfopointer, &genericpage->objinfo_struct,
         sizeof(*objinfopointer) - sizeof(anim_elem *) - sizeof(otype_wb_info *) - sizeof(t_ai_info *));
  strcpy(objinfopointer->name, genericpage->objinfo_struct.name);
  if (objinfopointer->anim)
    memcpy(objinfopointer->anim, &genericpage->anim, sizeof(genericpage->anim));

  if (objinfopointer->static_wb)
    memcpy(objinfopointer->static_wb, &genericpage->static_wb, sizeof(genericpage->static_wb));

  if (objinfopointer->ai_info)
    memcpy(objinfopointer->ai_info, &genericpage->ai_info, sizeof(genericpage->ai_info));

  objinfopointer->multi_allowed = 1;

  // since the description pointer was just copied over, no need to malloc mem, copy and then free old, just move ptr
  genericpage->objinfo_struct.description = NULL;

  strcpy(objinfopointer->icon_name, genericpage->objinfo_struct.icon_name);
  // First see if our image differs from the one on the net
  // If it is, make a copy
  // If its a release version, don't do any of this

#ifndef RELEASE
  if (Network_up) {
    UpdatePrimitive(LocalModelsDir / genericpage->image_name, NetModelsDir / genericpage->image_name,
                    genericpage->image_name, PAGETYPE_GENERIC, objinfopointer->name);

    if (stricmp(genericpage->med_image_name, "INVALID NAME") != 0 && genericpage->med_image_name[0] != 0) {
      UpdatePrimitive(LocalModelsDir / genericpage->med_image_name, NetModelsDir / genericpage->med_image_name,
                      genericpage->med_image_name, PAGETYPE_GENERIC, objinfopointer->name);
    }

    if (stricmp(genericpage->lo_image_name, "INVALID NAME") != 0 && genericpage->lo_image_name[0] != 0) {
      UpdatePrimitive(LocalModelsDir / genericpage->lo_image_name, NetModelsDir / genericpage->lo_image_name,
                      genericpage->lo_image_name, PAGETYPE_GENERIC, objinfopointer->name);
    }
  }
#endif

  // Try and load our generic model from the disk

  img_handle = LoadPolyModel(genericpage->image_name, 1);

  if (img_handle < 0) {
    mprintf(0, "Couldn't load file '%s' in AssignGenericPage...\n", genericpage->image_name);
    objinfopointer->render_handle = -1;
    return 0;
  } else
    objinfopointer->render_handle = img_handle;

  if (stricmp(genericpage->med_image_name, "INVALID NAME") && genericpage->med_image_name[0] != 0) {
    img_handle = LoadPolyModel(genericpage->med_image_name, 1);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load file '%s' in AssignGenericPage...\n", genericpage->med_image_name);
      objinfopointer->med_render_handle = -1;
      return 0;
    } else
      objinfopointer->med_render_handle = img_handle;
  } else
    objinfopointer->med_render_handle = -1;

  if (stricmp(genericpage->lo_image_name, "INVALID NAME") && genericpage->lo_image_name[0] != 0) {
    img_handle = LoadPolyModel(genericpage->lo_image_name, 1);

    if (img_handle < 0) {
      mprintf(0, "Couldn't load file '%s' in AssignGenericPage...\n", genericpage->lo_image_name);
      objinfopointer->lo_render_handle = -1;
      return 0;
    } else
      objinfopointer->lo_render_handle = img_handle;
  } else
    objinfopointer->lo_render_handle = -1;

  // Try and load the various sounds
  for (i = 0; i < MAX_OBJ_SOUNDS; i++) {
    if (stricmp(genericpage->sound_name[i], "INVALID NAME") && genericpage->sound_name[i][0] != 0) {
      int sound_handle = mng_GetGuaranteedSoundPage(genericpage->sound_name[i]);

      if (sound_handle < 0) {
        mprintf(0, "Couldn't load sound file '%s' in AssignPowPage %s...\n", genericpage->sound_name[i],
                genericpage->objinfo_struct.name);
        objinfopointer->sounds[i] = SOUND_NONE_INDEX;
      } else
        objinfopointer->sounds[i] = sound_handle;
    } else
      objinfopointer->sounds[i] = SOUND_NONE_INDEX;
  }

  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    if (genericpage->dspew_name[i][0] != '\0') {
      int obj_handle = mng_GetGuaranteedGenericPage(genericpage->dspew_name[i], infile);

      if (obj_handle < 0) {
        objinfopointer->dspew[i] = 0;
        objinfopointer->dspew_number[i] = 0;
        objinfopointer->dspew_percent[i] = 0.0f;
      } else {
        objinfopointer->dspew[i] = obj_handle;
      }
    } else {
      objinfopointer->dspew[i] = -1;
      objinfopointer->dspew_number[i] = 0;
      objinfopointer->dspew_percent[i] = 0.0f;
    }
  }

  // Try and load the various sounds
  if (objinfopointer->ai_info) {
    for (i = 0; i < MAX_AI_SOUNDS; i++) {
      if (stricmp(genericpage->ai_sound_name[i], "INVALID NAME") && genericpage->ai_sound_name[i][0] != 0) {
        int sound_handle = mng_GetGuaranteedSoundPage(genericpage->ai_sound_name[i]);

        if (sound_handle < 0) {
          mprintf(0, "Couldn't load ai sound file '%s' in AssignPowPage %s...\n", genericpage->ai_sound_name[i],
                  genericpage->objinfo_struct.name);
          objinfopointer->ai_info->sound[i] = SOUND_NONE_INDEX;
        } else
          objinfopointer->ai_info->sound[i] = sound_handle;
      } else
        objinfopointer->ai_info->sound[i] = SOUND_NONE_INDEX;
    }
  }

  // Try and load the various weapons
  if (objinfopointer->static_wb) {
    for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
      for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
        if (genericpage->weapon_name[i][j][0] != '\0') {
          int weapon_handle = mng_GetGuaranteedWeaponPage(genericpage->weapon_name[i][j]);

          if (weapon_handle < 0) {
            mprintf(0, "Couldn't load weapon file '%s' in AssignPowPage %s...\n", genericpage->weapon_name[i][j],
                    genericpage->objinfo_struct.name);
            objinfopointer->static_wb[i].gp_weapon_index[j] = LASER_INDEX;
          } else
            objinfopointer->static_wb[i].gp_weapon_index[j] = weapon_handle;
        } else
          objinfopointer->static_wb[i].gp_weapon_index[j] = LASER_INDEX;
      }
    }

    // Try and load the various wb sounds
    for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
      for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
        if (genericpage->fire_sound_name[i][j][0] != '\0') {
          int fire_sound_handle = mng_GetGuaranteedSoundPage(genericpage->fire_sound_name[i][j]);

          if (fire_sound_handle < 0) {
            mprintf(0, "Couldn't load fire sound file '%s' in AssignPowPage %s...\n",
                    genericpage->fire_sound_name[i][j], genericpage->objinfo_struct.name);
            objinfopointer->static_wb[i].fm_fire_sound_index[j] = SOUND_NONE_INDEX;
          } else
            objinfopointer->static_wb[i].fm_fire_sound_index[j] = fire_sound_handle;
        } else
          objinfopointer->static_wb[i].fm_fire_sound_index[j] = SOUND_NONE_INDEX;
      }
    }
  }

  // Try and load the various wb sounds
  if (objinfopointer->anim) {
    for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
      for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
        if (stricmp(genericpage->anim_sound_name[i][j], "INVALID NAME") && genericpage->anim_sound_name[i][j][0] != 0) {
          int anim_sound_handle = mng_GetGuaranteedSoundPage(genericpage->anim_sound_name[i][j]);

          if (anim_sound_handle < 0) {
            mprintf(0, "Couldn't load anim sound file '%s' in AssignPowPage %s...\n",
                    genericpage->anim_sound_name[i][j], genericpage->objinfo_struct.name);
            objinfopointer->anim[i].elem[j].anim_sound_index = SOUND_NONE_INDEX;
          } else
            objinfopointer->anim[i].elem[j].anim_sound_index = anim_sound_handle;
        } else
          objinfopointer->anim[i].elem[j].anim_sound_index = SOUND_NONE_INDEX;
      }
    }
  }

  //	objinfopointer->size=(ComputeDefaultSize(objinfopointer->render_handle, &objinfopointer->size_offset, 0, 0));

  return 1;
}

// Copies values from a generic into a generic_page
void mng_AssignObjInfoToGenericPage(int n, mngs_generic_page *genericpage) {
  object_info *objinfopointer = &Object_info[n];
  int i, j;

  // Assign the  values
  memcpy(&genericpage->objinfo_struct, objinfopointer, sizeof(*objinfopointer));
  strcpy(genericpage->objinfo_struct.name, objinfopointer->name);

  if (objinfopointer->anim)
    memcpy(&genericpage->anim, objinfopointer->anim, sizeof(genericpage->anim));

  if (objinfopointer->static_wb)
    memcpy(&genericpage->static_wb, objinfopointer->static_wb, sizeof(genericpage->static_wb));

  if (objinfopointer->ai_info)
    memcpy(&genericpage->ai_info, objinfopointer->ai_info, sizeof(genericpage->ai_info));

  if (objinfopointer->description != NULL) {
    int len = strlen(objinfopointer->description);
    genericpage->objinfo_struct.description = (char *)mem_malloc(len + 1);
    ASSERT(genericpage->objinfo_struct.description);
    strcpy(genericpage->objinfo_struct.description, objinfopointer->description);
  } else
    genericpage->objinfo_struct.description = NULL;

  strcpy(genericpage->objinfo_struct.icon_name, objinfopointer->icon_name);

  if (objinfopointer->render_handle != -1)
    strcpy(genericpage->image_name, Poly_models[objinfopointer->render_handle].name);
  else
    strcpy(genericpage->image_name, "");

  if (objinfopointer->med_render_handle != -1)
    strcpy(genericpage->med_image_name, Poly_models[objinfopointer->med_render_handle].name);
  else
    strcpy(genericpage->med_image_name, "");

  if (objinfopointer->lo_render_handle != -1)
    strcpy(genericpage->lo_image_name, Poly_models[objinfopointer->lo_render_handle].name);
  else
    strcpy(genericpage->lo_image_name, "");

  for (i = 0; i < MAX_OBJ_SOUNDS; i++) {
    if (objinfopointer->sounds[i] != SOUND_NONE_INDEX)
      strcpy(genericpage->sound_name[i], Sounds[objinfopointer->sounds[i]].name);
    else
      strcpy(genericpage->sound_name[i], "");
  }

  for (i = 0; i < MAX_DSPEW_TYPES; i++) {
    if ((objinfopointer->dspew[i] != -1) && Object_info[objinfopointer->dspew[i]].type != OBJ_NONE)
      strcpy(genericpage->dspew_name[i], Object_info[objinfopointer->dspew[i]].name);
    else
      strcpy(genericpage->dspew_name[i], "\0");
  }

  for (i = 0; i < MAX_AI_SOUNDS; i++) {
    if (objinfopointer->ai_info && objinfopointer->ai_info->sound[i] != SOUND_NONE_INDEX)
      strcpy(genericpage->ai_sound_name[i], Sounds[objinfopointer->ai_info->sound[i]].name);
    else
      strcpy(genericpage->ai_sound_name[i], "");
  }

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
      if (objinfopointer->static_wb && objinfopointer->static_wb[i].fm_fire_sound_index[j] >= 0)
        strcpy(genericpage->fire_sound_name[i][j], Sounds[objinfopointer->static_wb[i].fm_fire_sound_index[j]].name);
      else
        strcpy(genericpage->fire_sound_name[i][j], "");
    }
  }

  for (i = 0; i < NUM_MOVEMENT_CLASSES; i++) {
    for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
      if (objinfopointer->anim && objinfopointer->anim[i].elem[j].anim_sound_index >= 0)
        strcpy(genericpage->anim_sound_name[i][j], Sounds[objinfopointer->anim[i].elem[j].anim_sound_index].name);
      else
        strcpy(genericpage->anim_sound_name[i][j], "");
    }
  }

  for (i = 0; i < MAX_WBS_PER_OBJ; i++) {
    for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
      if (objinfopointer->static_wb && objinfopointer->static_wb[i].gp_weapon_index[j] >= 0)
        strcpy(genericpage->weapon_name[i][j], Weapons[objinfopointer->static_wb[i].gp_weapon_index[j]].name);
      else
        strcpy(genericpage->weapon_name[i][j], "Laser");
    }
  }
}

// Loads a generic found in the net table file.  It then allocs a generic and
// then calls SetAndLoadgeneric to actually load in any images/models associated
// with it
void mng_LoadNetGenericPage(CFILE *infile, bool overlay) {
  mngs_generic_page genericpage;
  memset(&genericpage, 0, sizeof(mngs_generic_page));

  if (mng_ReadNewGenericPage(infile, &genericpage)) {
    int n = FindObjectIDName(genericpage.objinfo_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING GENERIC %s\n", genericpage.objinfo_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_GENERIC, genericpage.objinfo_struct.name, 0);
        mng_AssignGenericPageToObjInfo(&genericpage, n);
      }
      return; // A weapon has already loaded this generic
    }

    int ret = mng_SetAndLoadGeneric(&genericpage, infile);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load genericpage named %s!\n", genericpage.objinfo_struct.name);
}

// Reads a generic page from a local table file.  It then allocs a generic and
// loads any images/models associated with that generic
void mng_LoadLocalGenericPage(CFILE *infile) {
  mngs_generic_page genericpage;
  int ok = 0;
  memset(&genericpage, 0, sizeof(mngs_generic_page));

  if (mng_ReadNewGenericPage(infile, &genericpage)) {
    // Check to see if this is a local copy that is supposed
    // to go over a network copy (supersede the net copy)

    int i = FindObjectIDName(genericpage.objinfo_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;

      strcpy(pl.name, genericpage.objinfo_struct.name);
      pl.pagetype = PAGETYPE_GENERIC;

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
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_GENERIC &&
              !stricmp(addon->Addon_tracklocks[tidx].name, genericpage.objinfo_struct.name)) {
            // found it!!
            mprintf(0, "GenericPage: %s previously loaded\n", genericpage.objinfo_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_GENERIC, genericpage.objinfo_struct.name, 0);
        mng_AssignGenericPageToObjInfo(&genericpage, i);

        // For addon data
        if (Loading_addon_table != -1) {
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
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_GENERIC &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, genericpage.objinfo_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_GENERIC, genericpage.objinfo_struct.name, overlay);
        }
      }
    } else {
      // This is a local generic that has never been checked in
      if ((i = mng_SetAndLoadGeneric(&genericpage)) < 0)
        ok = 0;
      else
        ok = 1;

      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_GENERIC, genericpage.objinfo_struct.name, 0);
    }

    ASSERT(ok == 1);

    if (Loading_addon_table == -1)
      mng_AllocTrackLock(genericpage.objinfo_struct.name, PAGETYPE_GENERIC);
  } else

    mprintf(0, "Could not load genericpage named %s!\n", genericpage.objinfo_struct.name);
}

// First searches through the object index to see if the object is already
// loaded.  If not, searches in the table file and loads it.
// Returns index of object found, -1 if not
int mng_GetGuaranteedGenericPage(char *name, CFILE *infile) {
  int i;
  mngs_generic_page page;

  // See if its in memory
  i = FindObjectIDName(name);
  if (i != -1)
    return i;

  // Not in memory.  Load it from the table file.  Start searching from the
  // current spot in the open table file
  int ret = mng_FindSpecificGenericPage(name, &page, infile ? infile->position : 0);

  if (!ret)
    return -1;

  // We've found it in the table file, now load it.
  ret = mng_SetAndLoadGeneric(&page);
  ASSERT(ret >= 0);

  if (Loading_addon_table != -1) {
    // we're loading addon table pages, this will not overlay anything
    mng_PushAddonPage(PAGETYPE_GENERIC, page.objinfo_struct.name, 0);
  }

  return ret;
}
