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

 * $Logfile: /DescentIII/main/ObjInit.cpp $
 * $Revision: 170 $
 * $Date: 4/19/00 5:18p $
 * $Author: Matt $
 *
 * Functions to initialize objects
 *
 * $Log: /DescentIII/main/ObjInit.cpp $
 *
 * 170   4/19/00 5:18p Matt
 * From Duane for 1.4
 * Added check for ai_info
 *
 * 169   3/20/00 12:18p Matt
 * Merge of Duane's post-1.3 changes.
 * msize change (Mac only)
 *
 * 168   2/22/00 10:00a Matt
 * Fixed Jason's typo
 *
 * 167   2/19/00 6:44p Jason
 * Fixed out of bounds weapon problem
 *
 * 166   10/24/99 9:33a Chris
 * Cleaned a little more Mac code
 *
 * 165   10/22/99 10:59p Matt
 * Added check for anim data before renferencing it.
 *
 * 164   10/22/99 11:30a Matt
 * Mac merge
 *
 * 163   7/28/99 5:18p Kevin
 * Mac merge fixes
 *
 * 162   7/28/99 3:50p Kevin
 * Mac!
 *
 * 161   5/20/99 7:54p 3dsmax
 * added better memory support changing ships
 *
 * 160   5/19/99 3:54p Jeff
 * error is scripts are being bound to an object more than once
 *
 * 159   5/08/99 6:20p Jason
 * fixed framerate wiggle problem
 *
 * 158   4/28/99 5:09p Jason
 * fixed some bugs with latest build
 *
 * 157   4/27/99 4:44p Jason
 * fixed moving buildings not getting lit
 *
 * 156   4/22/99 8:29p Kevin
 * made psrand.h come after stdlib.h
 *
 * 155   4/21/99 1:23p Chris
 * Added the check ceiling checkbox for generic objects
 *
 * 154   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 153   4/20/99 3:33p Matt
 * ObjInit() was bashing creation time after setting it.
 *
 * 152   4/20/99 2:44p Matt
 * Deal with initializing a generic object whose ID isn't defined.  This
 * can happen if an object is deleted and the level in memory uses that
 * object.
 *
 * 151   4/20/99 12:24p Matt
 * Re-revised the ObjInit() system.  ObjInit() again does all the
 * initialization stuff, but now it's passed a lot more information so
 * those fields can be set before the rest of the initialization takes
 * place.
 *
 * 150   4/18/99 5:33p Jason
 * fixed object multiplayer problem
 *
 * 149   4/18/99 4:50p Matt
 * Took out code that hacked in ammo amounts for weapon powerups, and
 * added code to set the counts on the page and read and write to the
 * table file.
 *
 * 148   4/15/99 1:42a Jeff
 * changes for linux compile
 *
 * 147   4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 146   4/12/99 6:11p Jason
 * fix clutter objects so that they are volume lit as well
 *
 * 145   4/12/99 3:53p Matt
 * Page in polymodel for markers so model size is right.
 *
 * 144   4/10/99 5:56p Matt
 * Cleaned up object initialization code, including create object & load
 * object.
 *
 * 143   4/08/99 6:38p Matt
 * Improved message.
 *
 * 142   4/08/99 6:15p Matt
 * Deal with generic objects that have changed type.
 *
 * 141   4/05/99 10:54a Matt
 * Added auto-waypoint system
 *
 * 140   3/02/99 4:54p Matt
 * Took out assert
 *
 * 139   3/02/99 12:22p Matt
 * Revisions to weapon & ammo powerups.  Not fully tested.
 *
 * 138   2/25/99 11:01a Matt
 * Added new explosion system.
 *
 * 137   2/22/99 2:04p Jason
 * added different damages for players and generics
 *
 * 136   2/21/99 4:20p Matt
 * Added SoundSource objects (and reformatted parts of the object header
 * files).
 *
 * 135   2/15/99 6:10p Chris
 *
 * 134   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 133   2/04/99 2:05p Matt
 * Added blastable doors
 *
 * 132   2/02/99 8:43a Chris
 * I made buildings with AI work correctly (ie really big robots should be
 * buildings)
 * anim to and from states are now shorts instead of bytes
 *
 * 131   1/28/99 11:32a Jason
 * added marker cameras
 *
 * 130   1/27/99 6:08p Jason
 * first pass at markers
 *
 * 129   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 128   1/13/99 6:38a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 127   1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 126   1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 125   10/29/98 6:15p Chris
 * Made a minimum rotdrag for robots
 *
 * 124   10/22/98 5:36p Chris
 * Fixed ObjGet bugs
 *
 * 123   10/19/98 7:18p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 122   10/15/98 6:46p Chris
 * Added custom size for weapons
 *
 * 121   10/13/98 5:48p Jeff
 * CHRISHACK -- multiplayer ship hack for attach points -- DEMO SAFE
 *
 * 120   10/13/98 3:58p Kevin
 * changed free to mem_free
 *
 * 119   10/11/98 10:53p Matt
 * Fixed some zero-length malloc()s
 *
 * 118   10/11/98 2:40p Matt
 * Added some error checking to ObjInitGeneric()
 *
 * 117   10/09/98 3:32p Kevin
 * New memory library
 *
 * 116   10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 115   10/02/98 1:47p Jason
 * added lod player ships
 *
 * 114   9/28/98 4:09p Chris
 * Added birth animations
 *
 * 113   9/22/98 3:55p Samir
 * ifdef out stuff for non-debug version.
 *
 * 112   8/26/98 12:09p Jason
 * made object reinitialization not undo lightmaps
 *
 * 111   8/25/98 4:40p Samir
 * small sequencing prob,
 *
 * 110   8/25/98 3:44p Sean
 * moved control intitalization of player to after polymodel is paged in.
 *
 * 109   8/18/98 12:48p Jason
 * made debris objects have volume lighting
 *
 * 108   8/12/98 6:37p Jeff
 * removed init stuff for OBJ_DUMMY
 *
 * 107   8/03/98 4:29p Chris
 * Added additional support for the attach system
 *
 * 106   8/03/98 4:29p Jason
 * took out presets for ship physics flags
 *
 * 105   7/28/98 12:29p Jason
 * added rotational velocity to multiplayer position packets
 *
 * 104   7/20/98 2:06p Chris
 * Added the precomputation of some weapons (fixed speed weapons).  This
 * algorithm can be expanded to include some missiles with some minor
 * work.
 *
 * 103   7/07/98 7:34p Jeff
 * created object type, OBJ_DUMMY
 *
 * 102   7/06/98 12:22p Keneta
 * Fixed a bug with dynamically allocated weapon batteries
 *
 * 101   7/02/98 2:47p Chris
 * Dynamic weapon info is now dynamically allocated
 *
 * 100   6/12/98 4:07p Jason
 * added dynamic volume lighting to objects
 *
 * 99    6/11/98 12:48p Jason
 * added better spewing weapons
 *
 * 98    5/21/98 12:34p Jason
 * made particles drop differently
 *
 * 97    5/19/98 4:42a Chris
 * Added shockwave's -- enjoy.  :)
 *
 * 96    5/15/98 5:41p Jason
 * implemented volume lighting system
 *
 * 95    5/14/98 12:56p Jason
 * changes to help lower memory usage
 *
 * 94    5/12/98 11:58a Chris
 * Offset animation's for generic objects
 *
 * 93    5/11/98 4:40p Chris
 * AI info is now a malloc'ed pointer
 *
 * 92    5/07/98 2:22p Chris
 * Hit die dot
 *
 * 91    5/04/98 3:51p Matt
 * Finished (for now) with breaking glass.
 *
 * 90    5/04/98 12:28p Matt
 * Added shard objects
 *
 * 89    5/01/98 3:38p Chris
 * Leveling defaults off
 *
 * 88    5/30/98 10:16p Chris
 * Fixed some bad spelling
 *
 * 87    4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 86    4/22/98 3:25p Jason
 * changes for multiplayer debugging
 *
 * 85    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 84    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 83    4/16/98 2:56p Chris
 * Updated buddy support and intergrated scripting and AI
 *
 * 82    4/15/98 8:38p Jason
 * fixed some multiplayer issues
 *
 * 81    4/15/98 12:56p Chris
 * Updated parent_handle support and added buddy bot support
 *
 * 80    4/03/98 11:27a Chris
 * Doubled the size of powerups
 *
 * 79    4/03/98 10:07a Chris
 * Added support for objects getting their size computed when the
 * polymodel is paged in the first time as an object
 *
 * 78    4/02/98 6:38p Jason
 * page in low-res models with generic objects
 *
 * 77    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 76    3/31/98 6:11p Jason
 * took out auto ship selection
 *
 * 75    3/30/98 6:58p Matt
 * When reinitializing an object, don't bash its custom script.
 *
 * 74    3/30/98 6:20p Matt
 * Renamed ResetObject() to be ObjReInitAll()
 *
 * 73    3/20/98 5:51p Jason
 * more changes for multiplayer
 *
 * 72    3/19/98 7:15p Jason
 * more changes for multiplayer
 *
 * 71    3/13/98 5:55p Chris
 * Added the new collision spheres
 *
 * 70    3/11/98 4:59p Chris
 * Changed the ComputeDefualtSize function call
 *
 * 69    3/09/98 10:49a Chris
 * Worked on the homing code
 *
 * 68    2/25/98 2:06p Jason
 * fixed objinit player to give you different ships in the correct order
 *
 * 67    2/25/98 12:32p Jason
 * added a new player ship for multiplayer games
 *
 * 66    2/23/98 4:52p Chris
 * Removed size hack
 *
 * 65    2/17/98 8:17p Jeff
 * hacked a player ship size in for the milestone
 *
 * 64    2/17/98 8:16p Jeff
 * Call compute default size for player ships
 *
 * 63    2/16/98 4:41p Jason
 * took out starhawk ship (again!)
 *
 * 62    2/16/98 2:47a Chris
 * Massive improvements to the animation system and the AI
 *
 * 61    2/11/98 6:58p Matt
 * Changed the way cameras are rendered, so they show up on the terrain as
 * well.
 *
 * 60    2/10/98 7:02p Jason
 * fixed lighting render type for rooms
 *
 * 59    2/09/98 7:28p Matt
 * Added a rendering type for external room so we could check against
 * render type == RT_NONE
 *
 * 58    2/03/98 1:06p Jason
 * tidied up some multiplayer loose ends
 *
 * 57    1/30/98 12:13p Jason
 * give weapons lifetime
 *
 * 56    1/29/98 5:49p Matt
 * Changed old camera object type to be viewer object (for editor), and
 * now camera objects will just be for game cameras.
 *
 * 55    1/29/98 3:29p Chris
 * Major update to the AI system.
 *
 * 54    1/28/98 12:00p Jason
 * more changes for multiplayer
 *
 * 53    1/23/98 6:25p Jason
 * Got spray weapons working
 *
 * 52    1/23/98 11:21a Jason
 * incremental multiplayer checkin
 *
 * 51    1/20/98 4:12p Samir
 * New script housekeeping system.
 *
 * 50    1/18/98 9:05p Matt
 * Changed a comment, and deleted some unused code
 *
 * 49    1/10/98 2:24p Jason
 * better multiplayer code checked in
 *
 * 48    12/08/97 6:18p Jason
 * more tweaks for destroyable buildings
 *
 * 47    12/05/97 6:38p Chris
 * Fixed bug with impact_size initialization
 *
 * 46    12/01/97 9:54a Chris
 * Added support for concussive forces, generalized robot collisions to
 * generic collisions
 *
 * 45    11/04/97 6:18p Chris
 * Added support so that the player ship uses the robot's firing dialog.
 *
 * 44    10/28/97 12:21p Chris
 * Unified AIInit
 *
 * 43    10/23/97 11:34p Chris
 * Fixed problems with idle animations
 *
 * 42    10/23/97 5:36p Jason
 * added splinter objects (probably temporary)
 *
 * 41    10/21/97 11:57a Jason
 * added ability to set dying model for player ship
 *
 * 40    10/20/97 6:10p Jason
 * added of_polygon_object flag to debris stuff
 *
 * 39    10/20/97 6:02p Jason
 * fixed dumb objweapon bug
 *
 * 38    10/20/97 5:54p Jason
 * added polygon_object flag
 *
 * 37    10/20/97 4:59p Jason
 * made player ships render with gouraud shading
 *
 * 36    10/20/97 4:46p Jason
 * changes for explosions
 *
 * 35    10/17/97 5:09p Jason
 * added more fireball stuff
 *
 * 34    10/05/97 5:31a Chris
 * Make AI init match ai_init_all in aimain.cpp
 *
 * 33    10/03/97 5:18p Chris
 * Added OBJ_LINE as a new type
 *
 * 32    10/03/97 4:43p Chris
 * added debug fvi call and object type line
 *
 * 31    10/01/97 7:51p Matt
 * Added code for external rooms
 *
 * 30    10/01/97 12:39p Chris
 * Added support for new physics values in generic objects
 *
 * 29    9/30/97 6:40p Jason
 * got lightmap stuff sort of working with objects
 *
 * 28    9/30/97 1:15p Matt
 * Made player objects other than player 0 have physics and control types
 * of none
 *
 * 27    9/24/97 6:18p Samir
 * Use script names instead of script id values to identify scripts.
 *
 * 26    9/22/97 6:18p Matt
 * Removed include of stub.h
 *
 * 25    9/19/97 9:37p Chris
 * Attempted to fix door collisions -- almost there, but not quite
 *
 * 24    9/15/97 5:21a Chris
 * Fixed the weapon fixed rotate initialization
 *
 * 23    9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 22    9/10/97 3:58p Samir
 * Initialize custom script handle to -1
 *
 * 21    9/05/97 1:29p Jason
 * revamped generic object lighting
 *
 * 20    9/04/97 3:21p Jason
 * added pulse timing for lit objects
 *
 * 19    9/03/97 6:17p Jason
 * added code to support powerups/robots/etc that cast light
 *
 * 18    9/03/97 3:54p Jason
 * got objects to cast light
 *
 * 17    9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 16    8/21/97 5:56p Samir
 * Took out script specific stuff from ObjInit and moved to ObjScript
 *
 * 15    8/18/97 1:42a Chris
 * Fixed the flags = 0 bug.  Remove an ASSERT that broke the debris code.
 * Until the debris creation is changed, the assert will have to remain
 * removed.
 *
 * 14    8/13/97 4:54p Matt
 * Added destroyable flag & hitpoints
 *
 * 13    8/12/97 5:29p Matt
 * Added support for clutter & building types
 *
 * 12    8/12/97 3:23p Samir
 * Added code to initialize scripts for objects.
 *
 * 11    8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 10    8/07/97 4:47p Chris
 * Massively expanded the weapon system.  Not done yet.
 *
 * 9     8/06/97 4:33p Chris
 * Expanded the weapons page
 *
 * 8     8/06/97 1:35p Matt
 * Changes for new generic object_info struct which replace robot-specific
 * structure
 *
 * 7     7/28/97 1:14p Chris
 * Added support for sub-object visability.  Plus, debris.
 *
 * 6     7/15/97 7:29p Chris
 * Added a sound for helicopter blades.
 *
 * 5     7/15/97 5:35p Chris
 * New AI code
 *
 * 4     7/15/97 4:59p Chris
 * added support for AI and animations
 *
 * 10    6/30/97 5:23p Chris
 *
 * 9     6/25/97 9:28p Chris
 * Added code to allow for robots that are unmovable and/or with/without
 * AI.
 *
 * 8     5/15/97 6:09p Chris
 *
 * 7     4/24/97 5:42p Jason
 * got fireball vclips working
 *
 * 6     4/16/97 11:50a Jason
 * finally got weapons to fire
 *
 * 5     4/15/97 6:32p Chris
 * Added some temporary stuff to get weapons firing.
 *
 * 4     4/15/97 2:28p Jason
 * trying to get weapon firing working...it won't due to a (i think)
 * physics bug.  Checked in so Chris can have a look.
 *
 *
 * 3     4/08/97 2:00a Chris
 * Made powerups always bouncy and have unlimitted
 * bounce.  This will change as time goes on.
 *
 * 2     4/04/97 2:57p Matt
 * Added code to initialize all the type-specific data for an object from
 * the page for that object type.  This means that we need to pass less
 * info to ObjCreate(), and that we save less info in the level save file.
 * It also makes it easy to reset all the objects when an object page has
 * changed.
 *
 * 1     4/04/97 10:01a Matt
 *
 * $NoKeywords: $
 */
#include "objinit.h"
#include "player.h"
#include "ship.h"
#include "pserror.h"
#include "PHYSICS.H"
#include "weapon.h"
#include "AIMain.h"
#include "fireball.h"
#include "objinfo.h"
#include "Mission.h"
#include "robotfire.h"
#include "door.h"
#include "vclip.h"
#include "polymodel.h"
#include "robot.h"
#include "sounds.h"
#include "mem.h"
#include "marker.h"
// #include <malloc.h>
#include <stdlib.h>
#include "psrand.h"
// Allocate and initialize an effect_info struct for an object
void ObjCreateEffectInfo(object *objp) {
  if (objp->effect_info)
    mem_free(objp->effect_info);

  objp->effect_info = (effect_info_s *)mem_malloc(sizeof(effect_info_s));
  memset(objp->effect_info, 0, sizeof(effect_info_s));
  ASSERT(objp->effect_info);
  objp->effect_info->sound_handle = SOUND_NONE_INDEX;
}
void ObjSetRenderPolyobj(object *objp, int model_num, int dying_model_num = -1);
#define NUM_PLAYER_ATTACH_POINTS 3
// Initialize the polygon object information for an object
void ObjSetRenderPolyobj(object *objp, int model_num, int dying_model_num) {
  objp->render_type = RT_POLYOBJ;
  objp->flags |= OF_POLYGON_OBJECT;
  polyobj_info *p_info = &objp->rtype.pobj_info;
  p_info->model_num = model_num;
  p_info->dying_model_num = dying_model_num;
  p_info->anim_frame = 0.0f;
  p_info->tmap_override = -1;
  p_info->subobj_flags = 0xFFFFFFFF;
  p_info->multi_turret_info.num_turrets = 0;
  p_info->multi_turret_info.keyframes = NULL;
  p_info->multi_turret_info.last_keyframes = NULL;
  // Initialize attach slots
  if (model_num != -1) {
    poly_model *pm = GetPolymodelPointer(model_num); // get also pages in
    if (objp->attach_children != NULL) {
      mem_free(objp->attach_children);
      objp->attach_children = NULL;
    }
    if ((objp->attach_children == NULL) && pm->n_attach) {
      objp->attach_children = (int *)mem_malloc(sizeof(int) * pm->n_attach);
      if (objp->type == OBJ_PLAYER)
        ASSERT(pm->n_attach >= NUM_PLAYER_ATTACH_POINTS);
      for (int i = 0; i < pm->n_attach; i++)
        objp->attach_children[i] = OBJECT_HANDLE_NONE;
    }
  }
}
// Initialize a player object
// Returns 1 if ok, 0 if error
int ObjInitPlayer(object *objp) {
  ship *ship;
  int ret = 1;
  ASSERT(objp->type == OBJ_PLAYER);
  objp->shields = INITIAL_SHIELDS;
  ship = &Ships[Players[objp->id].ship_index];
  if (!ship->used) { // this ship doesn't exist
    int new_ship;
    Int3();
    ret = 0;
    new_ship = GetNextShip(0);
    ASSERT(new_ship != -1);
    Players[objp->id].ship_index = new_ship;
    ship = &Ships[Players[objp->id].ship_index];
  }
  // Set up render info
  ObjSetRenderPolyobj(objp, ship->model_handle, ship->dying_model_handle);
  ASSERT(Poly_models[ship->model_handle].n_attach >= 3);
  objp->lighting_render_type = LRT_GOURAUD;
  objp->lm_object.used = 0;
  // Page in those models
  PageInPolymodel(ship->model_handle, OBJ_PLAYER, &ship->size);
  if (ship->dying_model_handle >= 0)
    PageInPolymodel(ship->dying_model_handle);
  if (ship->lo_render_handle >= 0)
    PageInPolymodel(ship->lo_render_handle);
  if (ship->med_render_handle >= 0)
    PageInPolymodel(ship->med_render_handle);
  // Set size
  objp->size = ship->size;
  // Set up control info.  The player flies, other players do nothing
  // MUST be after paging in polymodel cause SetObjectControlType does some
  // stuff with the object's polymodel.
  if (objp->id == Player_num) {
    SetObjectControlType(objp, CT_FLYING);
    objp->movement_type = MT_PHYSICS;
    objp->mtype.phys_info = ship->phys_info;
    Player_object = objp;
  } else {
    SetObjectControlType(objp, CT_NONE);
    objp->movement_type = MT_NONE;
    objp->mtype.phys_info = ship->phys_info;
    objp->mtype.phys_info.flags = PF_FIXED_VELOCITY;
  }
  // Set up physics info
  // These are always set for a player
  objp->mtype.phys_info.num_bounces = PHYSICS_UNLIMITED_BOUNCE;
  if (objp->dynamic_wb == NULL) {
    objp->dynamic_wb = (dynamic_wb_info *)mem_malloc(sizeof(dynamic_wb_info) * MAX_WBS_PER_OBJ);
  }
  WBClearInfo(objp);
  // Set a few misc things
  Players[objp->id].team = objp->id % 2;
  ObjCreateEffectInfo(objp);
  objp->effect_info->type_flags = EF_VOLUME_LIT;

  return ret;
}
// Initialize a generic object (robot, powerup, building, etc.)
// Returns 1 if ok, 0 if error
int ObjInitGeneric(object *objp, bool reinit) {
  object_info *obj_info;
  int ret = 1;
  float r_val = (float)ps_rand() / (float)D3_RAND_MAX;
  if ((objp->id < 0) || (objp->id >= MAX_OBJECT_IDS)) {
    Int3();
    return 0;
  }
  obj_info = &Object_info[objp->id];
  // Deal with deleted type
  if (obj_info->type == OBJ_NONE) {
    int i;
    for (i = 0, obj_info = std::data(Object_info); i < MAX_OBJECT_IDS; i++, obj_info++) { // find other object of same type
      if (obj_info->type == objp->type)
        break;
    }
    ASSERT(i < MAX_OBJECT_IDS); // There should (in real life) always be at least one of each type
#ifdef EDITOR
    if (GetFunctionMode() == EDITOR_MODE)
      OutrageMessageBox("Object %d (\"%s\") had ID %d which no longer exists.  Changing to %d, \"%s\".", OBJNUM(objp),
                        objp->name ? objp->name : "<no name>", objp->id, i, obj_info->name);
#endif
  }
  if (obj_info->type != objp->type) {
#ifdef EDITOR
    if (GetFunctionMode() == EDITOR_MODE)
      OutrageMessageBox("Object %d (\"%s\"), type name \"%s\", changed from type %s to %s", OBJNUM(objp),
                        objp->name ? objp->name : "<no name>", obj_info->name, Object_type_names[objp->type],
                        Object_type_names[obj_info->type]);
#endif
    objp->type = obj_info->type;
  }
  // Set size & shields
  objp->shields = obj_info->hit_points;
  // Set impact stuff for non-weapons
  objp->impact_size = obj_info->impact_size;
  objp->impact_time = obj_info->impact_time;
  objp->impact_player_damage = obj_info->damage;
  objp->impact_generic_damage = obj_info->damage;
  objp->impact_force = obj_info->damage * 50.0;
  // Set flags
  if (obj_info->flags & OIF_DESTROYABLE)
    objp->flags |= OF_DESTROYABLE;
  if (obj_info->flags & OIF_AI_SCRIPTED_DEATH)
    objp->flags |= OF_AI_DO_DEATH;
  if (obj_info->flags & OIF_DO_CEILING_CHECK)
    objp->flags |= OF_FORCE_CEILING_CHECK;
  // Set up movement info
  if (obj_info->flags & OIF_USES_PHYSICS) {
    objp->movement_type = MT_PHYSICS;
    // Setup some physics things
    objp->mtype.phys_info = obj_info->phys_info; // Set the initial velocity
    // Warn about initial velocity & rotvel
    if (obj_info->phys_info.velocity.z > 0.0)
      Int3(); // Warning: This object has an initial velocity.  This is not supported.
              // If your object does not need an initial velocity, set it to zero on
              // the page.  If you do need an initial velocity, someone will have to
              // add code to deal with it, perhaps here or perhaps at level start.
  } else
    objp->movement_type = MT_NONE;

  // Set up render info
  ObjSetRenderPolyobj(objp, obj_info->render_handle);
  PageInPolymodel(obj_info->render_handle, objp->type, &obj_info->size);
  objp->size = obj_info->size;

  // Page in low-res models
  if (obj_info->lo_render_handle != -1)
    PageInPolymodel(obj_info->lo_render_handle);
  if (obj_info->med_render_handle != -1)
    PageInPolymodel(obj_info->med_render_handle);

  // Set anim frame
  if (Object_info[objp->id].anim) {
    objp->rtype.pobj_info.anim_frame =
        ((1.0f - r_val) * (float)Object_info[objp->id].anim[MC_STANDING].elem[AS_ALERT].from) +
        (r_val * (float)Object_info[objp->id].anim[MC_STANDING].elem[AS_ALERT].to);
  } else {
    objp->rtype.pobj_info.anim_frame = 0.0f;
  }

  // Set up control info (must be after wb stuff)
  if (obj_info->ai_info && obj_info->flags & OIF_CONTROL_AI) // DAJ 12/18/99 added check for ai_info
  {
    SetObjectControlType(objp, CT_AI);
    AIInit(objp, obj_info->ai_info->ai_class, obj_info->ai_info->ai_type, obj_info->ai_info->movement_type);
  } else
    SetObjectControlType(objp, CT_NONE);
  if (objp->control_type == CT_AI) {
    poly_model *pm = &Poly_models[objp->rtype.pobj_info.model_num];
    int num_wbs = pm->num_wbs;

    if ((objp->dynamic_wb != NULL) && ((uint32_t)num_wbs != mem_size(objp->dynamic_wb) / sizeof(dynamic_wb_info)))
    {
      mem_free(objp->dynamic_wb);
      objp->dynamic_wb = NULL;
    }
    if ((objp->dynamic_wb == NULL) && num_wbs) {
      objp->dynamic_wb = (dynamic_wb_info *)mem_malloc(sizeof(dynamic_wb_info) * num_wbs);
    }
    // Setup the weapon batteries (must be after polymodel stuff)
    WBClearInfo(objp);
  }
  objp->lighting_render_type = obj_info->lighting_info.lighting_render_type;
  if (!reinit)
    objp->lm_object.used = 0;
  // Allocate effect memory
  ObjCreateEffectInfo(objp);

  if (objp->type != OBJ_POWERUP)
    objp->effect_info->type_flags = EF_VOLUME_LIT;
  if (objp->movement_type == MT_PHYSICS) {
    if (objp->mtype.phys_info.rotdrag < 60.0f)
      objp->mtype.phys_info.rotdrag = 60.0; // CHRISHACK - MAKES SURE ROBOTS DONT SPIN FOREVER
  }

  // Set ammo amounts for powerups
  if (objp->type == OBJ_POWERUP) {
    if (objp->control_type == CT_NONE) { // some powerups have AI; don't mess with them
      SetObjectControlType(objp, CT_POWERUP);
      objp->ctype.powerup_info.count = obj_info->ammo_count;
    }
  }
  // Clear wiggle flag to supersede those pesky designer errors!
  objp->mtype.phys_info.flags &= ~PF_WIGGLE;
  return ret;
}
int ObjInitDebris(object *objp) {
  ASSERT(objp->type == OBJ_DEBRIS);
  objp->movement_type = MT_PHYSICS;
  SetObjectControlType(objp, CT_DEBRIS);
  objp->lifeleft = DEBRIS_LIFE;
  objp->flags |= OF_USES_LIFELEFT;
  objp->ctype.debris_info.death_flags = 0;
  // Set up render info
  ObjSetRenderPolyobj(objp, -1);
  objp->lighting_render_type = LRT_GOURAUD;
  objp->lm_object.used = 0;
  // Allocate effect memory
  ObjCreateEffectInfo(objp);

  objp->effect_info->type_flags = EF_VOLUME_LIT;

  return 1;
}
int ObjInitShard(object *objp) {
  ASSERT(objp->type == OBJ_SHARD);
  objp->movement_type = MT_PHYSICS;
  SetObjectControlType(objp, CT_NONE);
  objp->lifeleft = DEBRIS_LIFE * 5;
  objp->flags |= OF_USES_LIFELEFT;
  // Set physics info
  objp->mtype.phys_info.flags = PF_GRAVITY + PF_BOUNCE;
  objp->mtype.phys_info.mass = 1.0;
  objp->mtype.phys_info.drag = 0.0001f;
  objp->mtype.phys_info.coeff_restitution = 0.3f;
  objp->mtype.phys_info.num_bounces = 0;

  // Set up render info
  objp->render_type = RT_SHARD;
  return 1;
}
#ifdef _DEBUG
int ObjInitLine(object *objp) {
  ASSERT(objp->type == OBJ_DEBUG_LINE);
  objp->movement_type = MT_NONE;
  SetObjectControlType(objp, CT_NONE);
  objp->render_type = RT_LINE;
  return 1;
}
#endif
// Initialize a camera
// Returns 1 if ok, 0 if error
int ObjInitCamera(object *objp) {
  // Set size & shields
  objp->size = 0.5;
  objp->shields = 0;
  // Set up various info
  SetObjectControlType(objp, CT_NONE);
  objp->movement_type = MT_NONE;
  objp->lm_object.used = 0;
#ifdef EDITOR
  objp->render_type = RT_EDITOR_SPHERE; // draw cameras as spheres in the editor
  objp->rtype.sphere_color = GR_RGB(255, 255, 0);
#else
  objp->render_type = RT_NONE;
#endif
  return 1;
}
// Initialize a sound object
// Returns 1 if ok, 0 if error
int ObjInitSoundSource(object *objp) {
  // Set size & shields
  objp->size = 0.5;
  objp->shields = 0;
  // Set up various info
  SetObjectControlType(objp, CT_SOUNDSOURCE);
  objp->movement_type = MT_NONE;
  objp->lm_object.used = 0;
#ifdef EDITOR
  objp->render_type = RT_EDITOR_SPHERE; // draw cameras as spheres in the editor
  objp->rtype.sphere_color = GR_RGB(0, 255, 0);
#else
  objp->render_type = RT_NONE;
#endif
  return 1;
}
// Initialize a waypoint object
// Returns 1 if ok, 0 if error
int ObjInitWaypoint(object *objp) {
  // Set size & shields
  objp->size = 0.5;
  objp->shields = 0;
  // Set up various info
  SetObjectControlType(objp, CT_NONE);
  objp->movement_type = MT_NONE;
  objp->lm_object.used = 0;
#ifdef EDITOR
  objp->render_type = RT_EDITOR_SPHERE; // draw cameras as spheres in the editor
  objp->rtype.sphere_color = GR_RGB(255, 130, 33);
#else
  objp->render_type = RT_NONE;
#endif
  return 1;
}
// Initialize an editor viewer object
// Returns 1 if ok, 0 if error
int ObjInitViewer(object *objp) {
  // Set size & shields
  objp->size = 5.0;
  objp->shields = 0;
  // Set up various info
  SetObjectControlType(objp, CT_NONE);
  objp->movement_type = MT_NONE;
  objp->render_type = RT_NONE;
  objp->lm_object.used = 0;
  return 1;
}
// Initialize a weapon
// Returns 1 if ok, 0 if error
int ObjInitWeapon(object *objp) {
  weapon *weap;
  int ret = 1;
  ASSERT(objp->type == OBJ_WEAPON);

  if (objp->id < 0 || objp->id >= MAX_WEAPONS)
    return 0;

  weap = &Weapons[objp->id];
  ASSERT(weap->used > 0);
  // Set up shields
  objp->shields = 0;
  // Set up control info
  SetObjectControlType(objp, CT_WEAPON);
  // Not tracking anything
  objp->ctype.laser_info.track_handle = OBJECT_HANDLE_NONE;
  // Set up physics info
  objp->movement_type = MT_PHYSICS;
  objp->mtype.phys_info.mass = weap->phys_info.mass;
  objp->mtype.phys_info.drag = weap->phys_info.drag;
  objp->mtype.phys_info.rotdrag = weap->phys_info.rotdrag;
  objp->mtype.phys_info.flags = weap->phys_info.flags;

  objp->mtype.phys_info.full_rotthrust = weap->phys_info.full_rotthrust;
  objp->mtype.phys_info.full_thrust = weap->phys_info.full_thrust;
  objp->mtype.phys_info.rotvel = weap->phys_info.rotvel;
  // objp->mtype.phys_info.rot_thrust = weap->phys_info.full_rot_thrust;
  objp->mtype.phys_info.wiggle_amplitude = weap->phys_info.wiggle_amplitude;
  objp->mtype.phys_info.wiggles_per_sec = weap->phys_info.wiggles_per_sec;
  objp->mtype.phys_info.num_bounces = weap->phys_info.num_bounces;
  objp->mtype.phys_info.coeff_restitution = weap->phys_info.coeff_restitution;
  objp->lifeleft = weap->life_time;
  objp->lifetime = weap->life_time;
  objp->ctype.laser_info.thrust_left = weap->thrust_time;
  objp->ctype.laser_info.last_drop_time = 0;
  objp->mtype.phys_info.hit_die_dot = weap->phys_info.hit_die_dot;
  // Set impact stuff
  objp->impact_size = weap->impact_size;
  objp->impact_time = weap->impact_time;
  objp->impact_player_damage = weap->impact_player_damage;
  objp->impact_generic_damage = weap->impact_generic_damage;
  objp->impact_force = weap->impact_force;
  // Set up a few flags
  objp->mtype.phys_info.flags |= PF_NO_COLLIDE_PARENT;
  objp->flags |= OF_USES_LIFELEFT;
  // Set up rendering info
  objp->render_type = RT_WEAPON;

  if (!((weap->flags & WF_IMAGE_BITMAP) || (weap->flags & WF_IMAGE_VCLIP))) {
    objp->rtype.pobj_info.model_num = weap->fire_image_handle;
    objp->rtype.pobj_info.dying_model_num = -1;
    PageInPolymodel(weap->fire_image_handle, OBJ_WEAPON, &weap->size);

    objp->rtype.pobj_info.subobj_flags = 0xFFFFFFFF;
    objp->flags |= OF_POLYGON_OBJECT;
  } else if (weap->flags & WF_IMAGE_VCLIP) {
    PageInVClip(weap->fire_image_handle);
  }

  objp->size = weap->size;
  objp->ctype.laser_info.hit_status = WPC_NOT_USED;
  if (weap->flags & WF_CUSTOM_SIZE) {
    objp->size = weap->custom_size;
  }
  objp->lighting_render_type = LRT_STATIC;
  objp->lm_object.used = 0;

  return ret;
}
int ObjInitFireball(object *objp) {
  int ret = 1;
  ASSERT(objp->type == OBJ_FIREBALL);
  // Set size & shields
  objp->shields = 0;
  objp->size = 0;
  // Set up control info
  SetObjectControlType(objp, CT_EXPLOSION);
  // Set up physics info
  objp->movement_type = MT_NONE;
  objp->mtype.phys_info.num_bounces = PHYSICS_UNLIMITED_BOUNCE;

  // Set up render info
  objp->render_type = RT_FIREBALL;
  objp->size = Fireballs[objp->id].size;
  objp->flags |= OF_USES_LIFELEFT;
  objp->lifeleft = Fireballs[objp->id].total_life;
  objp->lighting_render_type = LRT_STATIC;
  objp->lm_object.used = 0;
  return ret;
}
int ObjInitMarker(object *objp) {
  int ret = 1;
  static int first = 1;
  static int polynum = -1;
  ASSERT(objp->type == OBJ_MARKER);
  // Set size & shields
  objp->shields = 100;
  objp->size = 2.0;
  // Set up control info
  SetObjectControlType(objp, CT_NONE);
  objp->movement_type = MT_NONE;
  ObjSetRenderPolyobj(objp, Marker_polynum);
  PageInPolymodel(Marker_polynum, OBJ_MARKER, &objp->size);
  objp->lm_object.used = 0;
  objp->lighting_render_type = LRT_STATIC;
  return ret;
}
int ObjInitDoor(object *objp, bool reinit) {
  // Set up movement info
  objp->movement_type = MT_NONE;
  SetObjectControlType(objp, CT_NONE);
  // Set up render info
  ObjSetRenderPolyobj(objp, GetDoorImage(objp->id));
  PageInPolymodel(objp->rtype.pobj_info.model_num);
  ComputeDefaultSize(OBJ_DOOR, objp->rtype.pobj_info.model_num, &objp->size);
  objp->lighting_render_type = LRT_LIGHTMAPS;
  // Set shields
  if (Doors[objp->id].flags & DF_BLASTABLE) {
    objp->flags |= OF_DESTROYABLE;
    objp->shields = Doors[objp->id].hit_points;
  }
  if (!reinit)
    objp->lm_object.used = 0;

  return 1;
}
int ObjInitRoom(object *objp) {
  // Set up movement info
  objp->movement_type = MT_NONE;
  SetObjectControlType(objp, CT_NONE);
  // Set up render info
  objp->render_type = RT_ROOM; // rendering handled as special case
  // I have no idea about this stuff
  objp->lighting_render_type = LRT_STATIC;
  objp->lm_object.used = 0;
  objp->flags |= OF_POLYGON_OBJECT;

  return 1;
}
// Set all the type-specific info for this object
// Returns 1 if ok, 0 if error
int ObjInitTypeSpecific(object *objp, bool reinitializing) {
  switch (objp->type) {
  case OBJ_CLUTTER:
  case OBJ_BUILDING:
  case OBJ_ROBOT:
  case OBJ_POWERUP:
    return ObjInitGeneric(objp, reinitializing);
    break;
  case OBJ_SHOCKWAVE:
    return 1;
    break;
  case OBJ_PLAYER:
    return ObjInitPlayer(objp);
    break;
  case OBJ_CAMERA:
    return ObjInitCamera(objp);
    break;
  case OBJ_MARKER:
    return ObjInitMarker(objp);
    break;
  case OBJ_VIEWER:
    return ObjInitViewer(objp);
    break;
  case OBJ_WEAPON:
    return ObjInitWeapon(objp);
    break;
  case OBJ_FIREBALL:
    return ObjInitFireball(objp);
    break;
  case OBJ_DOOR:
    return ObjInitDoor(objp, reinitializing);
    break;
  case OBJ_ROOM:
    return ObjInitRoom(objp);
    break;
  case OBJ_DEBRIS:
    return ObjInitDebris(objp);
    break;
  case OBJ_SHARD:
    return ObjInitShard(objp);
    break;
  case OBJ_SOUNDSOURCE:
    return ObjInitSoundSource(objp);
    break;
  case OBJ_WAYPOINT:
    return ObjInitWaypoint(objp);
    break;
  case OBJ_SPLINTER:
    return 1;
    break;
#ifdef _DEBUG
  case OBJ_DEBUG_LINE:
    return ObjInitLine(objp);
    break;
#endif
    break;
  default:
    Int3();
    return 0;
  }
}
// Initializes a new object.  All fields not passed in set to defaults.
// Returns 1 if ok, 0 if error
int ObjInit(object *objp, int type, int id, int handle, vector *pos, float creation_time, int parent_handle) {
  // Zero out object structure to keep weird bugs from happening in uninitialized fields.
  // I hate doing this because it seems sloppy, but it's probably better to do it
  memset(objp, 0, sizeof(object));
  // Set the stuff that's passed in
  objp->type = type;
  objp->id = id;
  objp->handle = handle;
  objp->pos = objp->last_pos = *pos;
  objp->parent_handle = parent_handle;
  objp->creation_time = creation_time;
  objp->osiris_script = NULL;
  // Initialize some general stuff
  objp->roomnum = -1;
  objp->orient = Identity_matrix;
  objp->next = objp->prev = -1;
  objp->dummy_type = OBJ_NONE;
  objp->flags = 0;
  objp->size = 0;
  objp->change_flags = 0;
  objp->generic_nonvis_flags = 0;
  objp->generic_sent_nonvis = 0;
  objp->name = NULL;
  objp->custom_default_script_name = NULL;
  objp->custom_default_module_name = NULL;
  objp->contains_type = -1;
  objp->lifeleft = 0;
  objp->effect_info = NULL;
  objp->ai_info = NULL;
  objp->dynamic_wb = NULL;
  objp->attach_children = NULL;
  // Now initialize the type-specific data
  return ObjInitTypeSpecific(objp, 0);
}
// Re-copies data to each object from the appropriate page for that object type.
// Called after an object page has changed.
void ObjReInitAll() {
  int objnum;
  object *objp;
  for (objnum = 0, objp = std::data(Objects); objnum <= Highest_object_index; objnum++, objp++)
    if (objp->type != OBJ_NONE)
      ObjInitTypeSpecific(objp, 1);
}
