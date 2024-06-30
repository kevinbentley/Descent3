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

 * $Logfile: /DescentIII/Main/object.h $
 * $Revision: 174 $
 * $Date: 10/22/99 2:06p $
 * $Author: Matt $
 *
 * Header for object.c
 *
 * $Log: /DescentIII/Main/object.h $
 *
 * 174   10/22/99 2:06p Matt
 * Mac merge
 *
 * 173   9/18/99 9:24p Jeff
 * object position history code (needed for motion blur effect)
 *
 * 172   5/22/99 1:54a Matt
 * Got rid of debug code mistakenly checked in.
 *
 * 171   5/21/99 3:43a Matt
 *
 * 170   2/23/99 12:39p Jason
 * added more options for generic objects
 *
 * 169   2/21/99 4:20p Matt
 * Added SoundSource objects (and reformatted parts of the object header
 * files).
 *
 * 168   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 167   2/08/99 5:26p Jeff
 * removed all calls to MultiSendRemoveObject, incorportated into
 * SetObjectDeadFlag.  Fixes sequencing issues in multiplayer
 *
 * 166   2/05/99 3:00p Jason
 * fixed some framerate problems
 *
 * 165   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 164   1/21/99 3:34p Jason
 * added liquid code
 *
 * 163   1/19/99 4:22p Matt
 * Added the ability for objects to have their own lighting info,
 * different from the default lighting for that type of object.
 *
 * 162   1/18/99 2:46p Matt
 * Combined flags & flags2 fields in object struct
 *
 * 161   1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 160   1/13/99 6:38a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 159   1/13/99 3:25a Chris
 * Added Obj_Burning and Obj_IsEffect to OSIRIS
 *
 * 158   1/13/99 12:12a Jeff
 * changed the name of the obj_link_info struct to object_link_info
 * (because the instance is named the same).  Allows it to compile under
 * GCC
 *
 * 157   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 156   1/08/99 12:02p Chris
 *
 * 155   1/06/99 5:06p Chris
 * Improving OSIRIS/game intergration - improved support for custom
 * animations
 *
 * 154   1/04/99 12:42p Chris
 * Updated OSIRIS with "xxxx_external.h" files and Obj_Value, and
 * Matcen_XXX functions
 *
 * 153   12/21/98 11:30p Matt
 * Added names for objects
 *
 * 152   12/21/98 6:01p Matt
 * Changed the object handle bit allocation to handle object numbers up to
 * 2047.
 * Increased MAX_OBJECTS to 1500.
 *
 * 151   12/18/98 6:00p Jeff
 * added support for door scripts in new osiris
 *
 * 150   12/16/98 11:27a Jeff
 * added new osiris fields
 *
 * 149   12/10/98 7:09p Jason
 * added cloak fade
 *
 * 148   12/10/98 12:27p Jason
 * added cooler specular mapping for objects
 *
 * 147   11/03/98 6:16p Chris
 * Starting to make on/off and spray weapons accessable to robots
 *
 * 146   10/20/98 10:27p Chris
 *
 * 145   10/19/98 11:46p Jason
 * changes for multiplayer debug layer
 *
 * 144   10/19/98 7:18p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 143   10/19/98 3:14p Chris
 * Version .05 of locked axes
 *
 * 142   10/17/98 12:26p Chris
 * Fixed attached flares
 *
 * 141   10/16/98 5:25p Chris
 * Fixed sticky code
 *
 * 140   10/16/98 4:18p Chris
 * Fixed the 'flare thing'
 *
 * 139   10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 138   10/15/98 6:46p Chris
 * Added custom size for weapons
 *
 * 137   10/15/98 10:46a Chris
 * Made powerups fall to below the ceiling height
 *
 * 136   10/13/98 11:30a Matt
 * Added parens around a macro value
 *
 * 135   10/12/98 7:09p Matt
 * Removed some obsolete stuff
 *
 * 134   10/06/98 11:27a Jason
 * added new death type for robots
 *
 * 133   9/28/98 6:23p Chris
 * Changed multi_anim to custom_anim
 *
 * 132   9/22/98 12:40p Matt
 * Cleaned up the object per-frame processing code.
 *
 * 131   8/18/98 12:57a Samir
 * added ObjUnlink call.
 *
 * 130   8/12/98 6:37p Jeff
 * added functions to ghost an object (make it's type to OBJ_DUMMY) and
 * unghost
 *
 * 129   8/12/98 12:04p Chris
 * Attach system version .5 (still needs more work to be multiplayer
 * friendly)
 *
 * 128   8/07/98 8:25p Chris
 * Improved the attach system
 *
 * 127   8/03/98 3:59p Chris
 * Added support for FQ_IGNORE_WEAPONS, added .000001 attach code, fix a
 * bug in polymodel collision detection
 *
 * 126   7/31/98 11:52a Chris
 * Weapons can be persistent.  Added ability for objects to be manually
 * set for no object collisions.
 *
 * 125   7/30/98 11:09a Jason
 * added weapons that freeze and deform terrain
 *
 * 124   7/22/98 3:16p Jason
 * added observer mode
 *
 * 123   7/20/98 2:48p Chris
 * Removed hit_time (not neccessary)
 *
 * 122   7/20/98 2:06p Chris
 * Added the precomputation of some weapons (fixed speed weapons).  This
 * algorithm can be expanded to include some missiles with some minor
 * work.
 *
 * 121   7/19/98 9:44p Chris
 * Greatly improved homing performance
 *
 * 120   7/09/98 7:50p Jeff
 * added ObjGetUltimateParent to find out the original parent of an
 * object, traces the family tree
 *
 * 119   7/09/98 11:34a Chris
 * Turrets are interpolated.
 *
 * 118   7/08/98 11:38a Chris
 * Improved the turret info passing in multiplayer
 *
 * 117   7/07/98 7:34p Jeff
 * created object type, OBJ_DUMMY
 *
 * 116   7/07/98 3:26p Chris
 * Added changes for turret updates
 *
 * 115   7/06/98 5:36p Kevin
 * Variable parameter passing
 *
 * 114   7/02/98 2:47p Chris
 * Dynamic weapon info is now dynamically allocated
 *
 * 113   7/01/98 6:36p Chris
 * Added more multiplayer support
 *
 * 112   7/01/98 4:35p Chris
 * More multiplayer sync issues
 *
 * 111   7/01/98 2:02p Chris
 * Added the sound for animations
 *
 * 110   6/30/98 4:28p Chris
 * Checked in some missing commas
 *
 * 109   6/26/98 2:04p Jason
 * fixed some graphical problems with the omega
 *
 * 108   6/12/98 4:07p Jason
 * added dynamic volume lighting to objects
 *
 * 107   6/11/98 12:48p Jason
 * added better spewing weapons
 *
 * 106   5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 105   5/15/98 5:41p Jason
 * implemented volume lighting system
 *
 * 104   5/14/98 12:56p Jason
 * changes to help lower memory usage
 *
 * 103   5/11/98 4:40p Chris
 * AI info is now a malloc'ed pointer
 *
 * 102   5/08/98 1:16p Jason
 * added PF_DESTINATION_POS flag for interpolating multiplayer positions
 *
 * 101   5/07/98 1:41p Chris
 * Added hit_death_dot
 *
 * 100   5/04/98 12:30p Matt
 * ObjCreate() now takes object id as a uint16_t
 *
 * 99    5/04/98 12:28p Matt
 * Added shard objects
 *
 * 98    5/01/98 3:41p Chris
 *
 * 97    5/31/98 3:08p Chris
 * Allowed for death animations
 *
 * 96    5/30/98 10:16p Chris
 * Fixed some bad spelling
 *
 * 95    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 94    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 93    4/15/98 12:56p Chris
 * Updated parent_handle support and added buddy bot support
 *
 * 92    4/13/98 4:19p Chris
 * Added PF_IGNORE_CONCUSSIVE_FORCES
 *
 * 91    4/10/98 12:41p Jason
 * sped up lighting a little
 *
 * 90    4/09/98 2:23p Jason
 * added guided/afterburner stuff
 *
 * 89    4/09/98 12:05p Chris
 * Added parenting for all object types.  :)
 *
 * 88    4/08/98 6:02p Luke
 *
 * 87    4/08/98 3:47p Chris
 * Moved stuff around so that the object flags can stay 16 bits
 *
 * 86    4/08/98 2:53p Chris
 * Added flags for move this frame and stop this frame
 *
 * 85    3/31/98 4:23p Chris
 * Added a new AIpath system
 *
 * 84    3/20/98 9:34p Jason
 * added SetObjectDeadFlag inlined function
 *
 * 83    3/16/98 3:47p Jason
 * got rid of circular dependencies for objects and polymodels
 *
 * 82    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 81    3/12/98 7:30p Chris
 * Added ObjSetOrient
 *
 * 80    3/09/98 4:54p Jason
 * don't render objects that can't been seen through a portal
 *
 * 79    3/09/98 8:12a Chris
 * Added the start of the homing code
 *
 * 78    3/06/98 2:15p Chris
 * Changed target_object to target_handle
 *
 * 77    2/20/98 1:46p Chris
 * JASON:  Made dynamic lighting only occur if the object is rendered
 *
 * 76    2/19/98 11:21a Chris
 * Made ROOMNUM_OUTSIDE return a bool
 *
 * 75    2/18/98 1:39p Jason
 * more changes for lighting
 *
 * 74    2/17/98 5:54p Luke
 *
 * 73    2/16/98 2:49p Chris
 * Made the MAX_SUBOBJECTS determine the number of normalized_time values
 * to be processed.  No longer a 'literal' problem.
 *
 * 72    2/16/98 2:47a Chris
 * Massive improvements to the animation system and the AI
 *
 * 71    2/11/98 6:58p Matt
 * Changed the way cameras are rendered, so they show up on the terrain as
 * well.
 *
 * 70    2/11/98 7:01p Chris
 * Started to add the new anim stuff
 *
 * 69    2/09/98 7:28p Matt
 * Added a rendering type for external room so we could check against
 * render type == RT_NONE
 *
 * 68    2/06/98 2:57a Chris
 * Added point_collide_with_walls and ignore_robot_collisions
 *
 * 67    2/05/98 3:00p Matt
 * Made ObjSetPos() take optional orienation.  Got rid of unlink & relink
 * funcs from header.
 *
 * 66    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 65    2/03/98 11:17a Samir
 * Added macro to get handle from an object.
 *
 * 64    1/29/98 5:49p Matt
 * Changed old camera object type to be viewer object (for editor), and
 * now camera objects will just be for game cameras.
 *
 * 63    1/29/98 10:07a Matt
 * Added a constant that defines an invalid object handle
 *
 * 62    1/27/98 12:24p Samir
 * Added GetObjectPointInWorld.
 *
 * 61    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 60    1/20/98 4:12p Samir
 * New script housekeeping system.
 *
 * 59    1/19/98 2:44p Samir
 * Use one script per object and started parameter passing support.
 *
 * 58    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 57    1/07/98 3:32p Chris
 * Ship's wiggle falloff is computed via last thrust time.
 *
 * 56    1/05/98 3:54p Chris
 * Added ambient and explosion sounds
 *
 * 55    12/08/97 5:22p Jason
 * added code for destroyable buildings that leave their base object
 * around
 *
 * 54    12/03/97 5:53p Jason
 * worked on cooler explosion effects
 *
 * 53    12/03/97 4:31p Chris
 * Added the initial shockwave structure
 *
 * 52    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 51    11/12/97 5:47p Chris
 * re-ordered the object structure so that Soar people can get to known
 * data elements without having to worry about other stuff.
 *
 * 50    10/29/97 10:35a Chris
 * Added the no collide/relink flag to physics -- Dangerous ask Chris how
 * to use correctly
 *
 * 49    10/24/97 2:30p Jason
 * more changes for explosions
 *
 * 48    10/23/97 6:14p Jason
 * tweaks for splinter objects
 *
 * 47    10/23/97 5:36p Jason
 * added splinter objects (probably temporary)
 *
 * 46    10/23/97 2:06p Chris
 * Added physics structural support for walkers/flyers with reduced
 * physics
 *
 * 45    10/22/97 4:19p Jason
 * added lifetime field to object structure
 *
 * 44    10/20/97 5:54p Jason
 * added polygon_object flag
 *
 * 43    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 42    10/15/97 5:07p Chris
 * Added a gravity mask define
 *
 * 41    10/14/97 6:53p Chris
 * Added the initial SOAR support
 *
 * 40    10/03/97 5:11p Chris
 * Wrong MAX_OBJECT_TYPES fixed
 *
 * 39    10/03/97 4:43p Chris
 * added debug fvi call and object type line
 *
 * 38    10/02/97 1:04p Jason
 * implemented FreeAllObjects
 *
 * 37    10/01/97 7:00p Jason
 * did more work on object lightmaps
 *
 * 36    10/01/97 6:15p Matt
 * Added object type for rooms, and changed object id to a short
 *
 * 35    10/01/97 10:59a Chris
 *
 * 34    9/30/97 6:40p Jason
 * got lightmap stuff sort of working with objects
 *
 * 33    9/24/97 6:18p Samir
 * Use script names instead of script id values to identify scripts.
 *
 * 32    9/22/97 6:20p Matt
 * Removed some obsolete render type constants
 *
 * 31    9/19/97 6:58p Chris
 * Fixed some bugs with the big object system and removed some annoying
 * mprintf's
 *
 * 30    9/19/97 1:01p Chris
 * Better big object support
 *
 * 29    9/18/97 1:27p Matt
 * Cleaned up object struct
 *
 * 28    9/17/97 12:02p Jason
 * put back segnum field in object struct (for the terrain)
 *
 * 27    9/17/97 11:16a Matt
 * Ripped out segment code
 *
 * 26    9/15/97 5:21a Chris
 * Added sphere2poly support
 *
 * 25    9/12/97 6:36p Chris
 * Added collision terrain segment support
 * Added some LARGE OBJECT collision support
 *
 * 24    9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 23    9/10/97 5:17p Jason
 * more lighting improvements
 *
 * 22    9/05/97 1:29p Jason
 * revamped generic object lighting
 *
 * 21    9/04/97 3:21p Jason
 * added pulse timing for lit objects
 *
 * 20    9/03/97 6:17p Jason
 * added code to support powerups/robots/etc that cast light
 *
 * 19    9/03/97 3:54p Jason
 * got objects to cast light
 *
 * 18    9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 17    8/13/97 4:53p Matt
 * Added OF_DESTROYABLE flag
 *
 * 16    8/12/97 3:56p Matt
 * Added new object type: OBJ_BUILDING
 *
 * 15    8/12/97 1:13p Chris
 * Added AABBs.
 *
 * 14    8/11/97 9:57p Samir
 * Added scripts to objects.
 *
 * 13    8/07/97 4:44p Chris
 * Massively expanded the weapon system.  Not done yet.
 *
 * 12    8/06/97 4:32p Chris
 * Expanded the weapons page
 *
 * 11    8/04/97 4:09p Matt
 * Added ObjSetPos() that takes the new room number
 *
 * 10    7/29/97 10:27a Jason
 * added RenderOBject abstraction layer
 *
 * 9     7/28/97 1:14p Chris
 * Added support for sub-object visability.  Plus, debris.
 *
 * 8     7/15/97 5:32p Jason
 * got simple static lighting working with objects
 *
 * 7     7/15/97 4:59p Chris
 *
 * 6     7/15/97 4:59p Chris
 * added support for AI and animations
 *
 * 23    6/30/97 5:03p Chris
 * Added new AI stuff.
 *
 * 22    6/27/97 7:18p Matt
 * Added OBJNUM() macro
 *
 * 21    5/22/97 5:15p Chris
 *
 * 20    5/16/97 2:17p Samir
 * ResetPlayerObject added.
 *
 * 19    5/14/97 3:41p Chris
 *
 * 18    5/09/97 5:34p Samir
 * Added object scripting to object structure.
 *
 * 17    4/24/97 5:42p Jason
 * got fireball vclips working
 *
 * 16    4/14/97 3:48p Jason
 * changed RT_LASER to RT_WEAPON
 *
 * 15    4/09/97 9:57p Chris
 * Added more ability to customize ships/objects.
 *
 * 14    4/07/97 3:13p Chris
 *
 * 13    4/04/97 2:57p Matt
 * Added code to initialize all the type-specific data for an object from
 * the page for that object type.  This means that we need to pass less
 * info to ObjCreate(), and that we save less info in the level save file.
 * It also makes it easy to reset all the objects when an object page has
 * changed.
 *
 * 12    3/27/97 10:45a Chris
 * Set player mass and drag info
 *
 * 11    3/21/97 5:02p Jason
 * change short to int in segnum field of object struct
 *
 * 10    3/20/97 5:45p Jason
 * made object work with and render on terrain
 *
 * 9     3/20/97 12:17p Jason
 * added terrain flag to object flags
 *
 * 8     3/14/97 12:18p Chris
 * Tweak physics and remove braking for now.
 *
 * 7     2/13/97 12:16p Jason
 * changes for powerup remapping
 *
 * 6     2/11/97 6:51p Matt
 * Ripped out some old stuff & renamed a function
 *
 * 5     2/07/97 5:48p Matt
 * Renamed vector.h to vecmat.h to fix DevStudio problem
 *
 * $NoKeywords: $
 */

#ifndef _OBJECT_H
#define _OBJECT_H

#include "pstypes.h"
#include "pserror.h"
#include "object_external_struct.h"
#include "object_external.h"

/*
 *		CONSTANTS
 */

// Object handle stuff.
// The handle is comprised of the object number in the low 10 bits, and a count in the high 22 bits.
#define HANDLE_OBJNUM_MASK 0x7ff     // to mask off the object number part of the handle
#define HANDLE_COUNT_MASK 0xfffff800 // to maks off the count part of the handle
#define HANDLE_COUNT_INCREMENT 0x800 // what gets added to the handle to increment it

// See object external for OBJ_ types

// Lighting render types
#define LRT_STATIC 0
#define LRT_GOURAUD 1
#define LRT_LIGHTMAPS 2

extern std::array<const char*, MAX_OBJECT_TYPES> Object_type_names;

// stuctures for different kinds of weapon simulation (for precompution)

#define WPC_NOT_USED 0
#define WPC_NO_COLLISIONS 1
#define WPC_HIT_WALL 2

#define FMA_VALID 1
#define FMA_CURRENT 2
#define FMA_LOOPING 4
#define FMA_USE_SPEED 8
#define FMA_HAS_AI 16

#define FMT_NEW_DATA 1
#define FMT_UPDATING 2

// object light info flags
#define OLF_FLICKERING 1
#define OLF_TIMEBITS 2
#define OLF_PULSE 4
#define OLF_PULSE_TO_SECOND 8
#define OLF_FLICKER_SLIGHTLY 16
#define OLF_DIRECTIONAL 32    // Directional light - casts light in a cone
#define OLF_NO_SPECULARITY 64 // Object does not have specular light cast on it

// OSIRIS defines
#define MAX_MODULENAME_LEN 32

// How long an object name can be
#define OBJ_NAME_LEN 19 // max length for object name

/*
 *		VARIABLES
 */

extern std::array<object, MAX_OBJECTS> Objects;
extern int Highest_object_index; // highest objnum

extern object *Player_object; // the object that is the player
extern object *Viewer_object; // which object we are seeing from

#define MAX_BIG_OBJECTS 350
extern int Num_big_objects;
extern std::array<int16_t, MAX_BIG_OBJECTS> BigObjectList; // DAJ_MR utb int

// Compute the object number from an object pointer
#define OBJNUM(objp) (objp - std::data(Objects))
#define OBJHANDLE(objp) ((objp) ? (objp)->handle : 0)

/*
 *		FUNCTIONS
 */

// Set the dead flag for an object
static inline void SetObjectDeadFlag(object *obj, bool tell_clients_to_remove = false, bool play_sound_on_clients = false);
static inline void SetObjectDeadFlag(object *obj, bool tell_clients_to_remove, bool play_sound_on_clients) {
  int objnum = OBJNUM(obj);
  ASSERT(objnum != -1);
  ASSERT(objnum != 0);
  ASSERT(obj->type != OBJ_NONE);
  ASSERT(obj != Player_object);

  obj->flags |= OF_DEAD;

  if (tell_clients_to_remove) {
    if (play_sound_on_clients) {
      obj->flags |= OF_SEND_MULTI_REMOVE_ON_DEATHWS;
    } else {
      obj->flags |= OF_SEND_MULTI_REMOVE_ON_DEATH;
    }
  }
}

void SetObjectControlType(object *obj, int control_type);

// do whatever setup needs to be done
void InitObjects(void);

// links an object into a room's list of objects.
// takes object number and room number
void ObjLink(int objnum, int roomnum);

// reverses ObjLink.
void ObjUnlink(int objnum);

// Sets the AABB for the object
void ObjSetAABB(object *obj);

// initialize a new object.  adds to the list for the given room
// returns the object number
int ObjCreate(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient,
              int parent_handle = OBJECT_HANDLE_NONE);

// remove object from the world
void ObjDelete(int objnum);

// Resets the handles for all the objects.  Called by the editor to init a new level.
void ResetObjectList();

// Builds the free object list by scanning the list of free objects & adding unused ones to the list
// Also sets Highest_object_index
void ResetFreeObjects();

// Frees all the objects that are currently in use
void FreeAllObjects();

// Deletes all objects that have been marked for death.
void ObjDeleteDead();

// Process all objects for the current frame
void ObjDoFrameAll();

// set viewer object to next object in array
void ObjGotoNextViewer();

// move an object for the current frame
void ObjMoveOne(object *obj);

// Sets the position of an object.  This should be called whenever an object moves.
// Parameters:	obj - the object being moved
//					pos - the new position
//					roomnum - the correct roomnum for pos.  No error checking is done.
//					orient - if this is not null, the object's orientation is set to this.
void ObjSetPos(object *obj, vector *pos, int roomnum, matrix *orient, bool f_update_attached_children);
void ObjSetOrient(object *obj, const matrix *orient);

// delete objects, such as weapons & explosions, that shouldn't stay between levels
// if clear_all is set, clear even proximity bombs
void ClearTransientObjects(int clear_all);

// Remaps all static powerups,sounds,etc to their appropriate indices
void RemapEverything();

void BigObjAdd(int objnum);
void InitBigObjects(void);

// Creates the player object in the center of the given room
void CreatePlayerObject(int roomnum);

// Retruns a pointer to an object given its handle.  Returns NULL if object no longer exists.
object *ObjGet(int handle);

//	returns a vertex of an object in WORLD coordinates.
void GetObjectPointInWorld(vector *dest, object *obj, int subnum, int vertnum);

// These functions are for setting and getting an objects animation information
// (used in multiplayer games and the like)
bool ObjGetAnimUpdate(uint16_t objnum, custom_anim *multi_anim_info);
void ObjSetAnimUpdate(uint16_t objnum, custom_anim *multi_anim_info);

void ObjGetTurretUpdate(uint16_t objnum, multi_turret *multi_turret_info);
void ObjSetTurretUpdate(uint16_t objnum, multi_turret *multi_turret_info);

// Returns the original parent for the given object.  Returns self if it has no parent
object *ObjGetUltimateParent(object *child);

// Sets an object to a type OBJ_DUMMY (saves its old type) so it won't be renderered, etc, but still alive
void ObjGhostObject(int objnum);

// Restores a ghosted object back to it's old type
void ObjUnGhostObject(int objnum);

/////////////////////////////////
// Position history information
// ---Not to be externalized---
// Used for motion blur
/////////////////////////////////
#define MAX_OBJECT_POS_HISTORY (MAX_OBJECTS / 2)
#define MAX_POSITION_HISTORY 3
struct tPosHistory {
  vector pos[MAX_POSITION_HISTORY];
};
extern std::array<tPosHistory, MAX_OBJECT_POS_HISTORY> Object_position_samples;
extern uint8_t Object_position_head;
extern std::array<int16_t, MAX_OBJECTS> Object_map_position_history;
extern std::array<float, MAX_POSITION_HISTORY> Last_position_history_update; // last gametime the positions were updated
void ObjInitPositionHistory(object *obj);
void ObjFreePositionHistory(object *obj);
void ObjResetPositionHistory(void);
void ObjReInitPositionHistory(void);
#endif
