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

 * $Logfile: /DescentIII/Main/objinfo.h $
 * $Revision: 83 $
 * $Date: 9/13/01 2:31p $
 * $Author: Matt $
 *
 * Structure information about different kinds of objects
 *
 * $Log: /DescentIII/Main/objinfo.h $
 *
 * 83    9/13/01 2:31p Matt
 * Increased MAX_OBJECT_IDS from 810 to 910, and made the value the same
 * for the PC and Mac.
 *
 * 82    3/20/00 12:18p Matt
 * Merge of Duane's post-1.3 changes.
 * Lower MAX_OBJECT_IDS for Mac (Mac only)
 *
 * 81    10/28/99 12:44p 3dsmax
 * Increased the number of Object IDs
 *
 * 80    10/26/99 10:32a Jeff
 * no red guidebot in non-Windows versions
 *
 * 79    10/22/99 11:30a Matt
 * Mac merge
 *
 * 78    10/20/99 5:40p Chris
 * Added the Red Guidebot
 *
 * 77    10/08/99 4:29p Chris
 *
 * 76    10/08/99 4:24p 3dsmax
 * upped number of objids (don't know who did this)
 *
 * 75    5/17/99 10:15p Matt
 * Added system for having ambient objects that get deleted at low detail
 * levels.
 *
 * 74    5/09/99 1:13p Matt
 * Made ChaffChunk a static object.
 *
 * 73    5/09/99 2:01a Matt
 * Increased max object IDs from 600 to 650.
 *
 * 72    5/06/99 1:04a Gwar
 * adding object support to new editor -- place objects with right-click
 * in orthogonal views (still needs many bug fixes :)
 *
 * 71    5/01/99 3:49a Chris
 * Added the "No scale movement properties by diff level" checkbox
 *
 * 70    4/30/99 11:54p Jeff
 * put max_object_ids back up to 600 for now
 *
 * 69    4/30/99 12:56p Kevin
 * Lowered values for MAX_SOUNDS, MAX_ROOMS, MAX_TEXTURES and MAX_OBJIDS.
 * Talk to me before changing any of these again.
 *
 * 68    4/28/99 5:06a Chris
 * Added the no-scale damage by diff checkbox
 *
 * 67    4/22/99 7:08p Matt
 * Reduced the number of object sounds from 3 to 2, since we were only
 * using two.
 *
 * 66    4/22/99 4:13p Matt
 * Deleted sounds array from the object struct, since it was never used.
 *
 * 65    4/22/99 11:33a Chris
 * Added the ability of some generic objects to be able to go through
 * forcefields and glass
 *
 * 64    4/21/99 2:50p Matt
 * Killed function LoadObjectImage(), since it was only used in one file
 * and only did a call to LoadPolygonModel()
 *
 * 63    4/21/99 1:23p Chris
 * Added the check ceiling checkbox for generic objects
 *
 * 62    4/18/99 4:50p Matt
 * Took out code that hacked in ammo amounts for weapon powerups, and
 * added code to set the counts on the page and read and write to the
 * table file.
 *
 * 61    4/15/99 1:41a Jeff
 * changes for linux compile
 *
 * 60    4/14/99 10:31p Jeff
 * fixed name of ai_info struct to t_ai_info
 *
 * 59    4/10/99 6:39p Matt
 * Only save the designer-editable AI data in the Object_info array,
 * instead of the whole ai_frame structure.  This saves 3200 bytes per
 * Object_info entry, which is about 2 MB overall.
 *
 * 58    4/02/99 11:23a Matt
 * Made KillObject not take a death_info struct, but rather the death info
 * as individual parameters.  Moved death_info into objinfo.h, since it's
 * only used for generic objects.  Took out fade-away death hack, now that
 * fade-away deaths can be explicitely set.
 *
 * 57    3/31/99 3:59p Chris
 * made the MC_ stuff externalized to OSIRIS.
 *
 * 56    3/10/99 7:14p Jason
 * upped max object id limit to 600
 *
 * 55    2/28/99 6:20p Matt
 * Added the ability to set death types for generic objects.
 *
 * 54    2/23/99 12:39p Jason
 * added more options for generic objects
 *
 * 53    2/22/99 11:24p Matt
 * Deleted static debris objects, since they were never used
 *
 * 52    2/02/99 8:43a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 51    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 50    1/19/99 4:22p Matt
 * Added the ability for objects to have their own lighting info,
 * different from the default lighting for that type of object.
 *
 * 49    1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 48    1/06/99 5:06p Chris
 * Improving OSIRIS/game intergration - improved support for custom
 * animations
 *
 * 47    12/30/98 5:17p Jeff
 * changes made to handle script name override, to override the name of
 * the script to use in a module.
 *
 * 46    12/18/98 6:00p Jeff
 * added support for door scripts in new osiris
 *
 * 45    12/16/98 11:27a Jeff
 * added new osiris fields
 *
 * 44    9/28/98 6:23p Chris
 * Changed multi_anim to custom_anim
 *
 * 43    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 42    8/31/98 1:35p Keneta
 * Made some use count unsigned shorts
 *
 * 41    8/31/98 10:41a Keneta
 * increase max_object_ids
 *
 * 40    8/26/98 8:07p Jason
 * added directional lights to objects
 *
 * 39    8/16/98 6:17p Chris
 * Added generic object spewing code
 *
 * 38    8/13/98 11:55a Jeff
 * added 2 flags for inventory information
 *
 * 37    7/10/98 2:12p Jeff
 * added a flag for inventory information in objinfo
 *
 * 36    5/03/98 5:38p Chris
 * Added sounds to anim page
 *
 * 35    4/30/98 12:22p Jason
 * did some lo-res model optimizations
 *
 * 34    4/24/98 7:09p Jeff
 * Added a flag for a non-useable inventory item
 *
 * 33    4/16/98 2:56p Chris
 * Updated buddy support and intergrated scripting and AI
 *
 * 32    4/13/98 2:21p Chris
 * Fixed some collision problems dealing with AABBs and Polymodel paging
 * in.
 *
 * 31    4/06/98 4:53p Jason
 * got pageable polymodels working correctly with editor
 *
 * 30    3/25/98 11:02a Chris
 * version 1.0 of the new AI ranged firing code.
 *
 * 29    3/12/98 6:22p Jeff
 * added an atexit call to free up any memory allocated in objinfos
 *
 * 28    2/20/98 5:50p Jeff
 * Changed it so that whether an inventory item was selected was placed in
 * the objinfo flags
 *
 * 27    2/20/98 4:55p Jeff
 * Added inven_selectable field to determine if an object can be selected
 * in the inventory
 *
 * 26    2/16/98 2:47a Chris
 * Massive improvements to the animation system and the AI
 *
 * 25    2/06/98 6:18p Jason
 * fixed model mixup bug
 *
 * 24    2/03/98 6:15p Jeff
 * Added fields for inventory description and icon name
 *
 * 23    1/29/98 3:29p Chris
 * Major update to the AI system.
 *
 * 22    1/05/98 3:54p Chris
 * Added ambient and explosion sounds
 *
 * 21    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 20    11/25/97 12:28p Chris
 * Starting to add support for concussive blast damage
 *
 * 19    11/25/97 12:29p Jason
 * added LOD levels for certain objects
 *
 * 18    11/06/97 6:18p Jason
 * added support for lights that flicker a little bit
 *
 * 17    10/29/97 12:36p Jason
 * added some features to object lighting
 *
 * 16    10/28/97 12:22p Chris
 * now use the ai_frame struct to store ai information in the generic
 * objects
 *
 * 15    9/24/97 6:18p Samir
 * Use script names instead of script id values to identify scripts.
 *
 * 14    9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 13    9/08/97 11:51a Chris
 * Added support for entering seconds-per-cycle animation information
 *
 * 12    9/05/97 1:29p Jason
 * revamped generic object lighting
 *
 * 11    9/04/97 3:21p Jason
 * added pulse timing for lit objects
 *
 * 10    9/04/97 12:11p Jason
 * added flickering generic objects
 *
 * 9     9/03/97 6:17p Jason
 * added code to support powerups/robots/etc that cast light
 *
 * 8     9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 7     8/22/97 3:03a Chris
 *
 * 6     8/13/97 4:54p Matt
 * Added destroyable flag & hitpoints
 *
 * 5     8/11/97 6:48p Matt
 * Rewrote static object remap system
 *
 * 4     8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 3     8/08/97 11:54a Matt
 * Added constants from robot.h, and prototypes for the generic object
 * functions.
 *
 * 2     8/06/97 2:21p Matt
 *
 * 1     8/06/97 2:20p Matt
 * Generic object info for robots, powerups, etc.
 *
 * $NoKeywords: $
 */

#ifndef _OBJINFO_H
#define _OBJINFO_H

#include "object.h"
#include "manage.h"
#include "DeathInfo.h"

#ifdef NEWEDITOR
#include "..\neweditor\ned_Object.h"
#include "..\neweditor\ned_Tablefile.h"
#endif

// max sizes for inventory information in the objinfo
#define MAX_INVEN_DESC_SIZE 180
#define MAX_INVEN_ICON_SIZE 30

// How many object ids in the array
#define MAX_OBJECT_IDS 910

// How many different sounds each object can make
#define MAX_OBJ_SOUNDS 2

// Object info flags
#define OIF_CONTROL_AI 0x01         // this object uses AI
#define OIF_USES_PHYSICS 0x02       // this object uses physics
#define OIF_DESTROYABLE 0x04        // this object can be destroyed
#define OIF_INVEN_SELECTABLE 0x08   // this object can be selected in the inventory
#define OIF_INVEN_NONUSEABLE 0x10   // this object can not be used by pressing ENTER during the game
#define OIF_INVEN_TYPE_MISSION 0x20 // this object is for Mission objectives
#define OIF_INVEN_NOREMOVE 0x40     // this object should NOT be removed from the inventory when used
#define OIF_INVEN_VISWHENUSED 0x80  // this object will not have it contol type, movement type and render types
#define OIF_AI_SCRIPTED_DEATH 0x100
#define OIF_DO_CEILING_CHECK 0x200
#define OIF_IGNORE_FORCEFIELDS_AND_GLASS 0x400
#define OIF_NO_DIFF_SCALE_DAMAGE 0x800
#define OIF_NO_DIFF_SCALE_MOVE 0x1000
#define OIF_AMBIENT_OBJECT (1 << 13) // this object is just for show, & can be removed to improve performance

// This next numbers define the distance at which LOD popping occurs in models
#define DEFAULT_MED_LOD_DISTANCE 75.0f
#define DEFAULT_LO_LOD_DISTANCE 120.0f

// The number of ids of each type in the list
extern int Num_object_ids[];

extern const char * const Movement_class_names[];
extern const char * const Anim_state_names[];

// These defines must correspond to the Static_object_names array
#define GENOBJ_GUIDEBOT 0 // NOTE: This must match ROBOT_GUIDEBOT
#define GENOBJ_CHAFFCHUNK 1
#define GENOBJ_GUIDEBOTRED 2 // NOTE: This must match ROBOT_GUIDEBOTRED

#define IS_GUIDEBOT(x)                                                                                                 \
  (((object *)x)->type == OBJ_ROBOT &&                                                                                 \
   ((((object *)x)->id == ROBOT_GUIDEBOTRED) || (((object *)x)->id == ROBOT_GUIDEBOT)))

// Animation constants
#define NUM_MOVEMENT_CLASSES 5
#define NUM_ANIMS_PER_CLASS 24

// Info for an animation state
struct anim_entry {
  int16_t from, to;
  float spc;
  int anim_sound_index;
  uint8_t used;
};

struct anim_elem {
  std::array<anim_entry, NUM_ANIMS_PER_CLASS> elem;
};

#define MAX_DSPEW_TYPES 2
#define DSF_ONLY_IF_PLAYER_HAS_OBJ_1 1
#define DSF_ONLY_IF_NO_1 2

// How many different deaths each object can have
#define MAX_DEATH_TYPES 4

// Death info for an object type
struct death_info {
  uint32_t flags;      // death flags
  float delay_min; // if delay, min amount
  float delay_max; // if delay, max amount
};

// AI info for this object
// This is the subset of ai_frame data that the user can edit for an object type
struct t_ai_info {
  char ai_class;
  char ai_type;

  float max_velocity;
  float max_delta_velocity;
  float max_turn_rate;
  float max_delta_turn_rate;

  float attack_vel_percent;
  float flee_vel_percent;
  float dodge_vel_percent;

  float circle_distance;
  float dodge_percent;

  float melee_damage[2];
  float melee_latency[2];

  int sound[MAX_AI_SOUNDS];

  char movement_type;
  char movement_subtype;

  int flags;
  int notify_flags;

  float fov;

  float avoid_friends_distance;

  float frustration;
  float curiousity;
  float life_preservation;
  float agression;

  float fire_spread;
  float night_vision;
  float fog_vision;
  float lead_accuracy;
  float lead_varience;
  float fight_team;
  float fight_same;
  float hearing;
  float roaming;

  float biased_flight_importance;
  float biased_flight_min;
  float biased_flight_max;
};

#ifndef NEWEDITOR

// Info for robots, powerups, debris, etc.
struct object_info {
  char name[PAGENAME_LEN]; // the name on the page

  int type;   // what type of object this is
  float size; // size
  int flags;  // misc flags.  See above.

  //	int	render_type;			//set RT_ defines in object.h
  int render_handle;     // handle for bitmap/polygon model(hi-res)
  int med_render_handle; // handle for med res version of this object
  int lo_render_handle;  // handle for lo res version of this object

  float med_lod_distance; // The distance at which the med-res model takes over
  float lo_lod_distance;  // The distance at which the lo-res model takes over

  int score; // how many points you get for killing/picking up

  int hit_points; // if destroyable, the hit points
  float damage;
  float impact_size;
  float impact_time;

  int ammo_count; // if a powerup, how much ammo it has

  char *description;                   // used for inventory
  char icon_name[MAX_INVEN_ICON_SIZE]; // used for inventory

  int16_t sounds[MAX_OBJ_SOUNDS]; // list of sound handles
  int16_t dspew[MAX_DSPEW_TYPES];
  float dspew_percent[MAX_DSPEW_TYPES];
  int16_t dspew_number[MAX_DSPEW_TYPES];
  uint8_t f_dspew;

  // Valid for physics objects only
  physics_info phys_info; // the physics data for this obj type

  // Valid for lighting of objects
  light_info lighting_info;

  // for multiplayer respawning
  float respawn_scalar;

  bool multi_allowed;

  // OSIRIS information
  char module_name[MAX_MODULENAME_LEN];
  char script_name_override[PAGENAME_LEN];

  // Death information
  death_info death_types[MAX_DEATH_TYPES];    // the ways this object can die
  uint8_t death_probabilities[MAX_DEATH_TYPES]; // how likely each death is, from 0-100 (percent)

  // Valid for AI objects only
  t_ai_info *ai_info; // the AI info for this obj type

  // Valid for polygon models with weapons
  otype_wb_info *static_wb;
  //	otype_wb_info static_wb[MAX_WBS_PER_OBJ];

  // Valid for polygon model objects only
  anim_elem *anim; // which anim states are active
  //	anim_elem		anim[NUM_MOVEMENT_CLASSES];	// which anim states are active

};

// The big array of object info
extern std::array<object_info, MAX_OBJECT_IDS> Object_info;

#endif

// Sets all objects to unused
void InitObjectInfo();

// Frees up all objects (any memory allocated, and resets them) automatic atexit
void FreeObjectInfo(void);

// Allocs a object for use, returns -1 if error, else index on success
// int AllocObjectID(int type, int flags);
int AllocObjectID(int type, bool f_anim, bool f_weapons, bool f_ai);

// Frees object index n
void FreeObjectID(int n);

// Find an object with the given type.  Returns -1 if none found.
int GetObjectID(int type);

// Gets next object from n of the same type as n
int GetNextObjectID(int n);

// Gets previous object from n that has the same type
int GetPrevObjectID(int n);

// Searches thru all object ids for a specific name
// Returns the found id, or -1 if not found
int FindObjectIDName(const char *name);

// Given an object handle, returns an index to that object's model
int GetObjectImage(int handle);

// Given an object, renders the representation of this object
void DrawObject(object *obj);

// Moves an object from a given index into a new one (above MAX_STATIC_IDS)
// returns new index
int MoveObjectFromIndex(int index);

// Remap all the static object ids (objects that must have a specific index) into their assigned slots.
void RemapStaticIDs();

void ChangeOldModelsForObjects(int old_handle, int new_handle);

#endif
