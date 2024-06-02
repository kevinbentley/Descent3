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

 * $Logfile: /DescentIII/main/osiris_predefs.cpp $
 * $Revision: 128 $
 * $Date: 4/13/00 2:31p $
 * $Author: Matt $
 *
 * implementation code for osiris predefined functions
 *
 * $Log: /DescentIII/main/osiris_predefs.cpp $
 *
 * 128   4/13/00 2:31p Matt
 * Don't allow scripts to kill the guidebot.
 *
 * 127   11/05/99 4:28p Jay
 * Made sure the wb is a valid index
 *
 * 126   11/04/99 3:08p Jeff
 * fixed uint16_t check with -1 bug
 *
 * 125   11/03/99 10:20a Chris
 * Added the ability to find out if a room is volatile
 *
 * 124   11/02/99 12:16p Chris
 * More Merc code - added support for ignore_obj_lists for the Osiris
 * RayCast function
 *
 * 123   10/27/99 4:19p 3dsmax
 * added cloak flag for object value get
 *
 * 122   10/23/99 2:43a Chris
 * Added the PutObjectOnObject AI Goal
 *
 * 121   10/22/99 11:31a Matt
 * Mac merge
 *
 * 120   10/20/99 5:40p Chris
 * Added the Red Guidebot
 *
 * 119   10/19/99 10:18p 3dsmax
 * error check object name retreival.
 *
 * 118   10/16/99 9:56p Jeff
 * added a way to strip all players of all weapons and energy
 *
 * 117   10/16/99 8:46p Jeff
 * player value function to strip a player of weapons and energy
 *
 * 116   10/12/99 12:44p Jeff
 * added obj_value things for negative light and virus infection
 *
 * 115   9/13/99 12:26p Samir
 * added AIG_GUARD_AREA to add goal, since it exits in AIGoal.cpp already.
 *
 * 114   9/10/99 11:03a Samir
 * added command to get object's name from Obj_Value.
 *
 * 113   5/23/99 5:50p Chris
 * Fixed problems with msafe send on over non-changed information
 *
 * 112   5/23/99 12:33a Chris
 * Cannot change the control type of dying objects
 *
 * 111   5/21/99 7:29a Chris
 * More tweaking...
 *
 * 110   5/20/99 1:16a Chris
 * Fixed the AIV_I_TARGET_HANDLE set function
 *
 * 109   5/19/99 3:25p Jason
 * fixed wrong ordering of InitObjectScripts and MultiSendObject
 *
 * 108   5/12/99 8:03p Jason
 * fixed bug where multiplayer and demo code was playing a sound before an
 * object was even created
 *
 * 107   5/12/99 6:18a Chris
 * GetNearby objects doesn't return dead or RT_NONE objects
 *
 * 106   5/10/99 8:21a Chris
 * FindNearby...  ignores dead objects (OF_DEAD)
 *
 * 105   5/10/99 12:23a Chris
 * Fixed another hearing/seeing case.  :)  Buddy bot now is in the player
 * ship at respawn
 *
 * 104   5/07/99 1:32p Jeff
 * made osipf for sounds multisafe
 *
 * 103   5/06/99 4:54p Matt
 * Fixed array bounds error.
 *
 * 102   5/05/99 4:56p Chris
 * Added the RType powerup for the GB
 *
 * 101   5/04/99 2:51a Chris
 * Fixed bug with fire sounds in Obj_WBValue
 *
 * 100   4/29/99 7:15p Jeff
 * added initial velocity parameter to Obj_Create
 *
 * 99    4/29/99 4:50p Chris
 * Fixed matcen and Osiris created objects so thier ambient sounds play
 *
 * 98    4/29/99 3:25p Chris
 * Added support to find out if an object has wbs
 *
 * 97    4/28/99 2:26a Jeff
 * fixed places in code where only checking OBJ_PLAYER, added OBJ_GHOST
 * and OBJ_OBSERVER where applicable
 *
 * 96    4/27/99 4:43a Jeff
 * changed to call msafe functions for guidebot name commands
 *
 * 95    4/26/99 5:53p Jason
 * make sure no objects are being created from script that are flagged
 * with lightmaps
 *
 * 94    4/26/99 4:28a Jeff
 * added multisafe functions to check a player's weapons, and add/remove
 * weapons from a player
 *
 * 93    4/25/99 10:38p Matt
 * Made the Osiris kill object function work on players.
 *
 * 92    4/25/99 10:19p Matt
 * Fixed multiplayer and demo problems will killing an object from script,
 * and cleaned up the death code a bit in the process.
 *
 * 91    4/24/99 6:46p Jeff
 * added functions for theif so he can steal things other than weapons
 *
 * 90    4/24/99 2:19a Chris
 * Added another parameter to FollowPathSimple
 *
 * 89    4/24/99 12:09a Jeff
 * added path value functions
 *
 * 88    4/22/99 10:25p Chris
 * Corrected the mprintf for Player_Value
 *
 * 87    4/22/99 5:46p Jason
 * made weapons work in multiplayer
 *
 * 86    4/21/99 3:01p Matt
 * Added a new type for dying objects that have AI, instead of keeping a
 * flag in the dying info.
 *
 * 85    4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 84    4/20/99 8:56p Chris
 * Fixed problem with robots not being able to open locked doors that a
 * player has the key for.
 *
 * 83    4/20/99 7:29p Jeff
 * handle set/get guidebot name
 *
 * 82    4/18/99 7:27a Chris
 * Added AIAF_IMMEDIATE to force non-tiling and instant anim loop changes
 *
 * 81    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 80    4/12/99 6:15p Samir
 * Sound priorities pass 1
 *
 * 79    4/03/99 1:13a Jeff
 * added multisafe/dallas actions to set an object on fire
 *
 * 78    4/02/99 10:13p Jeff
 * made ship permissions multi safe
 *
 * 77    4/02/99 11:23a Matt
 * Made KillObject not take a death_info struct, but rather the death info
 * as individual parameters.  Moved death_info into objinfo.h, since it's
 * only used for generic objects.  Took out fade-away death hack, now that
 * fade-away deaths can be explicitely set.
 *
 * 76    4/02/99 10:18a Chris
 * We can now mess with the Object_info anim stuff
 *
 * 75    3/30/99 7:25p Chris
 * Fixed the bug where dead objects would get a valid type
 *
 * 74    3/30/99 4:32p Chris
 * Moved subtype to the main goal sturct (from goal_info).  Made move
 * relative object vec finishable.  (Like get behind player)
 *
 * 73    3/29/99 11:53a Chris
 * Corrected a objnum to obj ref problem in RayCast()
 *
 * 72    3/27/99 12:53p Chris
 * Added new enabler types
 *
 * 71    3/23/99 5:53p Matt
 * Fixed bug in physics set flags code
 *
 * 70    3/22/99 10:59a Chris
 * Awareness code was tweaked.  Multisafe stuff added for objects.
 *
 * 69    3/17/99 11:47a Jeff
 * exported function to get what language we are using
 *
 * 68    3/16/99 11:26a Chris
 * Buddy is now smarter -- gets to trigger level goals
 *
 * 67    3/10/99 1:33p Chris
 * Fixes for multi-line gb messages
 *
 * 66    3/03/99 3:01a Chris
 * Exported the difficulty stuff to OSIRIS
 *
 * 65    3/03/99 12:49a Chris
 *
 * 64    3/03/99 12:13a Chris
 *
 * 63    3/03/99 12:12a Chris
 *
 * 62    3/03/99 12:11a Chris
 * one more AI path check function
 *
 * 61    3/03/99 12:07a Chris
 * Added the two new OSIRIS predefs for AI path finding
 *
 * 60    3/01/99 8:13p Chris
 * major hack so that goal text can be displayed
 *
 * 59    3/01/99 8:05p Chris
 * Fixed bugs with the Level goal value functions
 *
 * 58    3/01/99 7:20p Chris
 * Fixed dist problems with finding nearby objects
 *
 * 57    2/28/99 11:30p Chris
 * FindObjOfType and OSIRIS controllable deaths
 *
 * 56    2/25/99 5:43p Chris
 * Massive improvement to BOA and AI (again)
 *
 * 55    2/22/99 8:21p Chris
 *
 * 54    2/22/99 5:59p Chris
 * Level Goals are now in OSIRIS.  :)
 *
 * 53    2/21/99 5:51p Chris
 * FIxed a bug with OBJV_C_TYPE (It should have been OBJV_I_TYPE).  Added
 * Obj_FindType()
 *
 * 52    2/20/99 5:08p Chris
 *
 * 51    2/18/99 4:27p Jeff
 * added lookup functions for matcen, paths, level goals
 *
 * 50    2/13/99 3:14p Dan
 * Check for no AI info for object in osipf_ObjectCustomAnim()
 *
 * 49    2/12/99 6:56p Chris
 *
 * 48    2/12/99 6:44p Chris
 *
 * 47    2/11/99 2:56a Jeff
 * improvements to introcam
 *
 * 45    2/10/99 4:45p Jeff
 * table file parser stuff
 *
 * 44    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 43    2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 42    2/08/99 3:06a Jeff
 * created a function to switch a player between ai and flying control
 * types (not exported to osiris...instead used in multisafe)
 *
 * 41    2/06/99 12:55p Chris
 * Converted the path stuff to base-1
 *
 * 40    2/03/99 1:51a Jeff
 * added predefs for ship permissions
 *
 * 39    2/03/99 12:43a Chris
 * Added Obj_GetGroundPos
 *
 * 38    1/29/99 5:10p Chris
 * Added an optional parent handle check for FindObjOfType
 *
 * 37    1/26/99 2:51p Chris
 * AIG_WANDER improvements
 *
 * 36    1/26/99 9:31a Chris
 * Obj_Value now correctly return OBJ_NONE when doing a TYPE check on an
 * invalid objref
 *
 * 35    1/25/99 6:13p Matt
 * When doing a radius attach to a powerup, cut the radius ratio in half,
 * since powerups use double their actual radius.
 *
 * 34    1/25/99 8:38a Chris
 * The the GUID to AI_FollowPathSimple
 *
 * 33    1/25/99 7:43a Chris
 * Added the GUID (Goal Unique Id) and added the ability for weapon
 * batteries to always fire exactly forward.
 *
 * 32    1/24/99 11:39p Chris
 * Added AIG_FOLLOW_PATH to AI_AddGoal for OSIRIS
 *
 * 31    1/24/99 8:17p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 30    1/24/99 6:36p Matt
 * Made AIGoalFollowPathSimple() use slot 3 instead of slot 0 (with
 * ChrisP)
 *
 * 29    1/23/99 4:48p Matt
 * Fixed a pair of small bugs
 *
 * 28    1/22/99 6:53p Chris
 * Fixed LoadandBind Aux notify problems, fixed static path problems,
 * fixed AIF_FORCE_AWARE Problems, improved path code
 *
 * 27    1/22/99 4:47p Jeff
 *
 * 26    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 25    1/21/99 3:56p Nate
 * Changed osipf_FindObjectName() so that it returns a handle
 *
 * 24    1/20/99 4:16p Jeff
 * added ai notify child events and predefs to get ids of sound, room,
 * trigger, object names
 *
 * 23    1/20/99 1:01a Chris
 * Improved AI and OSIRIS intergration
 *
 * 22    1/18/99 2:46p Matt
 * Combined flags & flags2 fields in object struct
 *
 * 21    1/18/99 9:05a Chris
 * Improved OSIRIS, AI, and ATTACH system, changed wiggle code, changed
 * attach code for rad attaches, and added the AIG_ATTACH_OBJ goal
 *
 * 20    1/15/99 5:59p Chris
 *
 * 19    1/13/99 5:20p Jeff
 * added 4 new file operation predefs
 *
 * 18    1/13/99 3:29a Chris
 * oops, forgot to include sounds.h
 *
 * 17    1/13/99 3:25a Chris
 * Added Obj_Burning and Obj_IsEffect to OSIRIS
 *
 * 16    1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 15    1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 14    1/05/99 12:24p Chris
 * More OSIRIS improvements
 *
 * 13    1/05/99 11:34a Jeff
 * fixed bugs in mission_flagget/set (needed to decrement flag before
 * using)
 *
 * 12    1/04/99 6:43p Jeff
 * added support to get/set mission flag values
 *
 * 11    1/04/99 12:42p Chris
 * Updated OSIRIS with "xxxx_external.h" files and Obj_Value, and
 * Matcen_XXX functions
 *
 * 10    12/30/98 3:46p Chris
 * Incremental AI changes
 *
 * 9     12/23/98 12:10p Chris
 * Added Gametime and Frametime to OSIRIS
 *
 * 8     12/22/98 4:51p Chris
 * Added a ObjCreate predefined function
 *
 * 7     12/22/98 2:46p Chris
 * Added the AIValue predefined function
 *
 * 6     12/21/98 5:30p Samir
 * predef for determining if object is being rendered.
 *
 * 5     12/18/98 4:01p Samir
 * implemented controls functions.
 *
 * 4     12/17/98 6:44p Samir
 * added control manipulation predefs.
 *
 * 3     12/17/98 5:43p Jeff
 * created timer system for osiris and save restore events
 *
 * 2     12/16/98 10:14p Jeff
 * created osiris predefined function file
 *
 * $NoKeywords: $
 */
#include <stdarg.h>
#include "osiris_predefs.h"
#include "object.h"
#include "mono.h"
#include "trigger.h"
#include "pstypes.h"
#include "pserror.h"
#include "hlsoundlib.h"
#include "gamepath.h"
#include "AIGoal.h"
#include "AIMain.h"
#include "soundload.h"
#include "room.h"
#include "objinfo.h"
#include "weapon.h"
#include "game.h"
#include "terrain.h"
#include "attach.h"
#include "matcen.h"
#include "findintersection.h"
#include "controls.h"
#include "controller.h"
#include "ship.h"
#include "Mission.h"
#include "osiris_share.h"
#include "multisafe.h"
#include "sounds.h"
#include "polymodel.h"
#include "multi.h"
#include "viseffect.h"
#include "physics.h"
#include "levelgoal.h"
#include "BOA.h"
#include "marker.h"
#include "damage.h"
#include "aipath.h"
#include "difficulty.h"
#include "localization.h"
#include "psrand.h"
#include "demofile.h"

int *hack_ilist = NULL;
int hack_list[100];

//	osipf_CallObjectEvent
//	Sends an event to an object.  Returns true if the default action should
//	continue to process.
bool osipf_CallObjectEvent(int objhandle, int event, tOSIRISEventInfo *ei) {
  object *objp = ObjGet(objhandle);
  if (!objp)
    return false;

  return Osiris_CallEvent(objp, event, ei);
}

//	osipf_CallTriggerEvent
//	Sends an event to a trigger.  Returns true if the default action should
//	continue to process.
bool osipf_CallTriggerEvent(int trignum, int event, tOSIRISEventInfo *ei) {
  if (trignum < 0 || trignum >= Num_triggers)
    return false;

  return Osiris_CallTriggerEvent(trignum, event, ei);
}

/*

*Get/Set Object Position
*Kill object
*Get Object max shields
*Get Object energy max
*Check to see if player has weapon
*Add weapon to a player
*Add weapon ammo
*Get weapon ammo
*Get/Set Player flags
*Is doorway openable
*play sound 2d/3d
*stop sound
*adjust 2d sound
*pickup powerup?
*end level
*timer events
*explode object
*start/stop spew
*get object type
*get object radius
*is object alive
*create pop-up view
*start end level sequence
*add type/id to inventory
*remove from inventory
*get inventory count
*use inventory item
*check for inventory item
*get player room
*set/get lighting effect distance
*set/get room wind
*get object fvec,rvec,uvec
*get/set object velocity
*get/set object parent
*enable WB
*get object anim frame
*play voice/stream
*add counter measure
*get counter measure count
*set portal render
*change face texture
*set object lighting effect parms
*ghost/unghost object
*set/get quad firing
*add player way point
*/

// searches through GamePath index and returns index of path matching name
// returns -1 if not found
int osipf_AIGetPathID(char *string) {
  //	extract string reference
  return FindGamePathName(string);
}

int osipf_AIGoalFollowPathSimple(int objhandle, int path_id, int guid, int flags, int slot) {
  object *obj = ObjGet(objhandle);
  path_information path_info;

  if (!obj) {
    mprintf(0, "Illegal object passed to AIGoalFollowPathSimple\n");
    return -1;
  }

  if (path_id == -1) {
    mprintf(0, "Illegal Path Id Passed To AIGoalFollowPathSimple\n");
    Int3();
    return -1;
  }

  if (obj->control_type != CT_AI) {
    mprintf(0, "Illegal Object CT Passed To AIGoalFollowPathSimple\n");
    Int3();
    return -1;
  }

  path_info.path_id = path_id;

  if (flags & GF_PATH_MOVE_REVERSE_DIR)
    path_info.next_node = GamePaths[path_id].num_nodes - 1;
  else
    path_info.next_node = 0;

  path_info.start_node = 0;
  path_info.end_node = GamePaths[path_id].num_nodes - 1;

  return GoalAddGoal(obj, AIG_FOLLOW_PATH, (void *)&path_info, slot, 1.0f, flags, guid);
}

int osipf_AIPowerSwitch(int objhandle, uint8_t f_power_on) {
  object *obj = ObjGet(objhandle);
  if (!obj) {
    mprintf(0, "Illegal Object passed to AIPowerSwitch\n");
    return -1;
  }

  if (f_power_on)
    AIPowerSwitch(obj, true);
  else
    AIPowerSwitch(obj, false);

  return 0;
}

// Touches a sound file so it loads into memory
void osipf_SoundTouch(char *str) {
  int id = FindSoundName(IGNORE_TABLE(str));

  if (id == -1) {
    mprintf(0, "Sound %s was not found. Unable to touch.\n", str);
    Int3();
  } else
    Sound_system.CheckAndForceSoundDataAlloc(id);
}

// Gets room values
void osipf_RoomValue(int roomnum, char op, char vtype, void *ptr, int index) {
  if (roomnum < 0 || roomnum > Highest_room_index || !Rooms[roomnum].used) {
    if (vtype == RMV_C_USED)
      *(char *)ptr = 0;
    else
      mprintf(0, "RoomValue: Illegal Room Passed\n");

    return;
  }

  room *rp = &Rooms[roomnum];

  switch (vtype) {
  case RMV_I_FLAGS:
    if (op == VF_GET)
      *(int *)ptr = rp->flags;
    else if (op == VF_SET)
      rp->flags = *(int *)ptr;
    else if (op == VF_SET_FLAGS)
      rp->flags |= *(int *)ptr;
    else if (op == VF_CLEAR_FLAGS)
      rp->flags &= ~(*(int *)ptr);
    break;
  case RMV_V_WIND:
    if (op == VF_SET)
      rp->wind = *(vector *)ptr;
    else if (op == VF_GET)
      *(vector *)ptr = rp->wind;
    break;
  case RMV_C_USED:
    if (op == VF_GET)
      *(char *)ptr = (rp->used != 0);
    break;

  case RMV_I_NUM_PATH_PNTS:
    if (op == VF_GET)
      *(int *)ptr = 1; // chrishack -- might change if the multi point intraroom points are added
    break;
  case RMSV_V_PATH_PNT:
    if (op == VF_SET)
      rp->path_pnt = *(vector *)ptr;
    else if (op == VF_GET)
      *(vector *)ptr = rp->path_pnt;
    break;

  case RMV_I_NUM_FACES:
    if (op == VF_GET)
      *(int *)ptr = rp->num_faces;
    break;
  case RMSV_I_FACE_TEXTURE_ID:
    if (op == VF_SET)
      rp->faces[index].tmap = *(int *)ptr;
    else if (op == VF_GET)
      *(int *)ptr = rp->faces[index].tmap;
    break;
  case RMSV_I_FACE_FLAGS:
    if (op == VF_GET)
      *(int *)ptr = rp->faces[index].flags;
    else if (op == VF_SET)
      rp->faces[index].flags = *(int *)ptr;
    else if (op == VF_SET_FLAGS)
      rp->faces[index].flags |= *(int *)ptr;
    else if (op == VF_CLEAR_FLAGS)
      rp->faces[index].flags &= ~(*(int *)ptr);
    break;
  case RMSV_V_FACE_NORMAL:
    if (op == VF_GET)
      *(vector *)ptr = rp->faces[index].normal;
    break;
  case RMSV_V_FACE_CENTER_PNT:
    if (op == VF_GET) {
      int i;

      if (index < 0 || index >= rp->num_faces || rp->faces[index].num_verts <= 0) {
        *(vector *)ptr = rp->path_pnt;
      } else {
        *(vector *)ptr = Zero_vector;

        for (i = 0; i < rp->faces[index].num_verts; i++) {
          *(vector *)ptr += rp->verts[rp->faces[index].face_verts[i]];
        }

        *(vector *)ptr /= rp->faces[index].num_verts;
      }
    }
    break;
  case RMV_I_NUM_PORTALS:
    if (op == VF_GET)
      *(int *)ptr = rp->num_portals;
    break;
  case RMSV_V_PORTAL_PATH_PNT:
    if (op == VF_SET)
      rp->portals[index].path_pnt = *(vector *)ptr; // chrishack -- make sure save game accounts for this
    else if (op == VF_GET)
      *(vector *)ptr = rp->portals[index].path_pnt;
    break;
  case RMSV_I_PORTAL_CONNECT_ROOM:
    if (op == VF_GET)
      *(int *)ptr = rp->portals[index].croom;
    break;
  case RMSV_I_PORTAL_CONNECT_PORTAL:
    if (op == VF_GET)
      *(int *)ptr = rp->portals[index].cportal;
    break;
  case RMSV_I_PORTAL_FACE:
    if (op == VF_GET)
      *(int *)ptr = rp->portals[index].portal_face;
    break;
  case RMV_F_DAMAGE:
    if (op == VF_GET)
      *(float *)ptr = rp->damage;
    break;
  }
}

void osipf_PlayerValue(int obj_handle, char op, char vhandle, void *ptr, int index) {
  object *objp;
  int id;
  bool extract_info = true;

  if (vhandle == PLYV_I_STRIP_WEAPONS) {
    // check to see if ptr is a -1, if so, don't extract info
    if ((*(int *)ptr) == -1)
      extract_info = false;
  }

  if (extract_info) {
    objp = ObjGet(obj_handle);

    if (!objp || (!(objp->type == OBJ_PLAYER || objp->type == OBJ_GHOST || objp->type == OBJ_OBSERVER))) {
      mprintf(0, "Player Value: Illegal Object Passed\n");
      return;
    }

    id = objp->id;
  }

  switch (vhandle) {
  case PLYV_I_FLAGS: {
    if (op == VF_GET) {
      *(int *)ptr = Players[id].flags;
    }
  } break;
  case PLYV_F_ENERGY:
    if (op == VF_GET)
      *(float *)ptr = Players[id].energy;
    else if (op == VF_SET)
      Players[id].energy = *(float *)ptr;
    break;
  case PLYV_F_MOVEMENT_SCALAR:
    if (op == VF_GET)
      *(float *)ptr = Players[id].movement_scalar;
    else if (op == VF_SET)
      Players[id].movement_scalar = *(float *)ptr;
    break;
  case PLYV_F_RECHARGE_SCALAR:
    if (op == VF_GET)
      *(float *)ptr = Players[id].weapon_recharge_scalar;
    else if (op == VF_SET)
      Players[id].weapon_recharge_scalar = *(float *)ptr;
    break;
  case PLYV_F_WSPEED_SCALAR:
    if (op == VF_GET)
      *(float *)ptr = Players[id].weapon_speed_scalar;
    else if (op == VF_SET)
      Players[id].weapon_speed_scalar = *(float *)ptr;
    break;
  case PLYV_F_DAMAGE_SCALAR:
    if (op == VF_GET)
      *(float *)ptr = Players[id].damage_scalar;
    else if (op == VF_SET)
      Players[id].damage_scalar = *(float *)ptr;
    break;
  case PLYV_F_ARMOR_SCALAR:
    if (op == VF_GET)
      *(float *)ptr = Players[id].armor_scalar;
    else if (op == VF_SET)
      Players[id].armor_scalar = *(float *)ptr;
    break;
  case PLYV_I_BUDDY_HANDLE:
    if (op == VF_GET)
      *(int *)ptr = Buddy_handle[id];
    break;
  case PLYSV_I_WEAPON:
    if (op == VF_GET) {
      msafe_struct mstruct;
      mstruct.objhandle = obj_handle;
      mstruct.index = index;
      msafe_GetValue(MSAFE_WEAPON_CHECK, &mstruct);

      if (!mstruct.state) {
        *(int *)ptr = 0;
      } else {
        if (index >= SECONDARY_INDEX)
          *(int *)ptr = mstruct.count;
        else
          *(int *)ptr = 1;
      }
    } else if (op == VF_SET) {
      int amount = *(int *)ptr;
      msafe_struct mstruct;
      mstruct.objhandle = obj_handle;
      mstruct.index = index;
      mstruct.state = (index >= SECONDARY_INDEX) ? 0 : 1;
      mstruct.count = amount;
      msafe_CallFunction(MSAFE_WEAPON_ADD, &mstruct);
    }
    break;

  case PLYV_CS_GUIDEBOTNAME: {
    if (op == VF_GET) {
      char *dest = (char *)ptr;
      ASSERT(dest);
      msafe_struct mstruct;
      mstruct.objhandle = obj_handle;
      msafe_GetValue(MSAFE_MISC_GUIDEBOT_NAME, &mstruct);
      strcpy(dest, mstruct.name);
    } else {
      char *src = (char *)ptr;
      ASSERT(src);
      msafe_struct mstruct;
      mstruct.objhandle = obj_handle;
      strcpy(mstruct.name, src);
      msafe_CallFunction(MSAFE_MISC_GUIDEBOT_NAME, &mstruct);
    }

  } break;

  case PLYSV_US_WEAPON_POWERUP_ID: {
    if (op == VF_GET)
      *(uint16_t *)ptr = Ships[Players[id].ship_index].spew_powerup[index];
  } break;
  case PLYSV_I_WEAPON_AMMO:
    if (op == VF_GET)
      if (index >= 0 && index < 10) {
        *(int *)ptr = Players[id].weapon_ammo[index];
      }
    break;
  case PLYV_B_THIEF_PLAYERHASITEM:
    // note this is multiplayer friendly
    if (op == VF_GET) {
      bool ret = ThiefPlayerHasItem(obj_handle, index);
      *((bool *)ptr) = ret;
    } else {
      Int3();
    }
    break;
  case PLYV_I_THIEF_STEALPLAYERITEM:
    // note this is multiplayer friendly
    if (op == VF_SET) {
      ThiefStealItem(obj_handle, index);
    } else {
      Int3();
    }
    break;
  case PLYV_I_STRIP_WEAPONS:
    if (op == VF_SET) {
      if ((*(int *)ptr) == -1) {
        MultiSendStripPlayer(-1);
      } else {
        MultiSendStripPlayer(id);
      }
    }
    break;
    //		case PLYSV_F_ACCESSORY:
    //			if(op == VF_GET)
    //				*(float *)ptr = Players[id]
    //			else if(op == VF_SET)
    //		break;
  }
}

extern void AIUpdateAnim(object *obj);

void osipf_ObjectCustomAnim(int handle, float start, float end, float time, char flags, int sound_handle,
                            char next_anim_type) {
  object *objp = ObjGet(handle);

  if (!objp) {
    mprintf(0, "AIValue: Illegal Object Passed\n");
    return;
  }

  objp->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;

  objp->rtype.pobj_info.custom_anim_info.anim_start_frame = start;
  objp->rtype.pobj_info.custom_anim_info.anim_end_frame = end;
  objp->rtype.pobj_info.custom_anim_info.anim_time = time;
  objp->rtype.pobj_info.custom_anim_info.flags = flags;
  objp->rtype.pobj_info.custom_anim_info.anim_sound_index = sound_handle;
  objp->rtype.pobj_info.custom_anim_info.next_anim_type = next_anim_type;

  if (objp->ai_info)
    objp->ai_info->next_animation_type = AS_CUSTOM;
  else
    mprintf(0, "ERROR: Changing animation for non-AI object.\n");

  if (flags & AIAF_IMMEDIATE) {
    AIUpdateAnim(objp);
  }
}

// searches for an object id given it's name
int osipf_ObjectFindID(const char *name) { return FindObjectIDName(IGNORE_TABLE(name)); }

// searches for an object id given it's name
int osipf_ObjectFindType(const char *name) {
  int id = FindObjectIDName(IGNORE_TABLE(name));

  if (id >= 0) {
    return Object_info[id].type;
  }

  return OBJ_NONE;
}

// searches through the weapons for a name and returns the id
int osipf_WeaponFindID(const char *name) { return FindWeaponName(IGNORE_TABLE(name)); }

// returns how long an object has lived
float osipf_ObjectGetTimeLived(int objhandle) {
  object *objp = ObjGet(objhandle);

  if (!objp) {
    mprintf(0, "Illegal object passed to ObjectGetTimeLived\n");
    return 0;
  }

  return (Gametime - objp->creation_time);
}

void osipf_AIValue(int objhandle, char op, char vtype, void *ptr) {
  object *objp = ObjGet(objhandle);

  if (!objp) {
    mprintf(0, "AIValue: Illegal Object Passed\n");
    return;
  }

  if ((objp->control_type != CT_AI) && (objp->control_type != CT_DYING_AND_AI)) {
    mprintf(0, "AIValue: Illegal Object CT Passed\n");
    return;
  }

  ai_frame *ai_info = objp->ai_info;

  switch (vtype) {
  case AIV_F_MAX_SPEED:
    if (op == VF_SET) {
      ai_info->max_velocity = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->max_velocity;
    }
    break;
  case AIV_F_MAX_DELTA_SPEED:
    if (op == VF_SET) {
      ai_info->max_delta_velocity = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->max_delta_velocity;
    }
    break;
  case AIV_F_MAX_TURN_RATE:
    if (op == VF_SET) {
      ai_info->max_turn_rate = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->max_turn_rate;
    }
    break;
  case AIV_F_MAX_DELTA_TURN_RATE:
    if (op == VF_SET) {
      ai_info->max_delta_turn_rate = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->max_delta_turn_rate;
    }
    break;
  case AIV_F_ATTACK_VEL_PERCENT:
    if (op == VF_SET) {
      ai_info->attack_vel_percent = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->attack_vel_percent;
    }
    break;
  case AIV_F_FLEE_VEL_PERCENT:
    if (op == VF_SET) {
      ai_info->flee_vel_percent = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->flee_vel_percent;
    }
    break;
  case AIV_F_DODGE_VEL_PERCENT:
    if (op == VF_SET) {
      ai_info->dodge_vel_percent = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->dodge_vel_percent;
    }
    break;
  case AIV_F_CIRCLE_DIST:
    if (op == VF_SET) {
      ai_info->circle_distance = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->circle_distance;
    }
    break;
  case AIV_F_DODGE_PERCENT:
    if (op == VF_SET) {
      ai_info->dodge_percent = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->dodge_percent;
    }
    break;
  case AIV_F_MELEE_DAMAGE1:
    if (op == VF_SET) {
      ai_info->melee_damage[0] = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->melee_damage[0];
    }
    break;
  case AIV_F_MELEE_DAMAGE2:
    if (op == VF_SET) {
      ai_info->melee_damage[1] = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->melee_damage[1];
    }
    break;
  case AIV_F_MELEE_LATENCY1:
    if (op == VF_SET) {
      ai_info->melee_latency[0] = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->melee_latency[0];
    }
    break;
  case AIV_F_MELEE_LATENCY2:
    if (op == VF_SET) {
      ai_info->melee_latency[1] = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->melee_latency[1];
    }
    break;
  case AIV_C_MOVEMENT_TYPE:
    if (op == VF_SET) {
      ai_info->movement_type = *((char *)ptr);
    } else {
      *((char *)ptr) = ai_info->movement_type;
    }
    break;
  case AIV_C_MOVEMENT_SUBTYPE:
    if (op == VF_SET) {
      ai_info->movement_subtype = *((char *)ptr);
    } else {
      *((char *)ptr) = ai_info->movement_subtype;
    }
    break;
  case AIV_C_ANIMATION_TYPE:
    if (op == VF_SET) {
      ai_info->animation_type = *((char *)ptr);
    } else {
      *((char *)ptr) = ai_info->animation_type;
    }
    break;
  case AIV_C_NEXT_ANIMATION_TYPE:
    if (op == VF_SET) {
      ai_info->next_animation_type = *((char *)ptr);
    } else {
      *((char *)ptr) = ai_info->next_animation_type;
    }
    break;
  case AIV_C_NEXT_MOVEMENT:
    if (op == VF_SET) {
      ai_info->next_movement = *((char *)ptr);
    } else {
      *((char *)ptr) = ai_info->next_movement;
    }
    break;
  case AIV_C_CURRENT_WB_FIRING:
    if (op == VF_SET) {
      ai_info->current_wb_firing = *((char *)ptr);
    } else {
      *((char *)ptr) = ai_info->current_wb_firing;
    }
    break;
  case AIV_I_TARGET_HANDLE:
    if (op == VF_SET) {
      AISetTarget(objp, *((int *)ptr));
    } else {
      *((int *)ptr) = ai_info->target_handle;
    }
    break;
  case AIV_F_NEXT_TARGET_UPDATE_TIME:
    if (op == VF_SET) {
      ai_info->next_target_update_time = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->next_target_update_time;
    }
    break;
  case AIV_F_DIST_TO_TARGET:
    if (op == VF_SET) {
      ai_info->dist_to_target_actual = ai_info->dist_to_target_perceived = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->dist_to_target_perceived;
    }
    break;
  case AIV_V_VEC_TO_TARGET:
    if (op == VF_SET) {
      ai_info->vec_to_target_actual = ai_info->vec_to_target_perceived = *((vector *)ptr);
    } else {
      *((vector *)ptr) = ai_info->vec_to_target_perceived;
    }
    break;
  case AIV_F_NEXT_CHECK_SEE_TARGET_TIME:
    if (op == VF_SET) {
      ai_info->next_check_see_target_time = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->next_check_see_target_time;
    }
    break;
  case AIV_V_LAST_SEE_TARGET_POS:
    if (op == VF_SET) {
      ai_info->last_see_target_pos = *((vector *)ptr);
    } else {
      *((vector *)ptr) = ai_info->last_see_target_pos;
    }
    break;
  case AIV_F_LAST_SEE_TARGET_TIME:
    if (op == VF_SET) {
      ai_info->last_see_target_time = *((float *)ptr);
      if (ai_info->last_see_target_time == Gametime) {
        AINotify(objp, AIN_SEE_TARGET, ObjGet(ai_info->target_handle));
      }
    } else {
      *((float *)ptr) = ai_info->last_see_target_time;
    }
    break;
  case AIV_F_LAST_HEAR_TARGET_TIME:
    if (op == VF_SET) {
      ai_info->last_hear_target_time = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->last_hear_target_time;
    }
    break;
  case AIV_F_WEAPON_SPEED:
    if (op == VF_SET) {
      ai_info->weapon_speed = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->weapon_speed;
    }
    break;
  case AIV_F_NEXT_MELEE_TIME:
    if (op == VF_SET) {
      ai_info->next_melee_time = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->next_melee_time;
    }
    break;
  case AIV_F_LAST_RENDER_TIME:
    if (op == VF_SET) {
      ai_info->last_render_time = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->last_render_time;
    }
    break;
  case AIV_F_NEXT_FLINCH_TIME:
    if (op == VF_SET) {
      ai_info->next_flinch_time = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->next_flinch_time;
    }
    break;
  case AIV_V_MOVEMENT_DIR:
    if (op == VF_SET) {
      ai_info->movement_dir = *((vector *)ptr);
    } else {
      *((vector *)ptr) = ai_info->movement_dir;
    }
    break;
  case AIV_V_ROT_THRUST_VECTOR:
    if (op == VF_SET) {
      ai_info->rot_thrust_vector = *((vector *)ptr);
    } else {
      *((vector *)ptr) = ai_info->rot_thrust_vector;
    }
    break;
  case AIV_F_FOV:
    if (op == VF_SET) {
      ai_info->fov = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->fov;
    }
    break;
  case AIV_F_AVOID_FRIENDS_DIST:
    if (op == VF_SET) {
      ai_info->avoid_friends_distance = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->avoid_friends_distance;
    }
    break;
  case AIV_F_FRUSTRATION:
    if (op == VF_SET) {
      ai_info->frustration = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->frustration;
    }
    break;
  case AIV_F_CURIOUSITY:
    if (op == VF_SET) {
      ai_info->curiousity = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->curiousity;
    }
    break;
  case AIV_F_FIRE_SPREAD:
    if (op == VF_SET) {
      ai_info->fire_spread = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->fire_spread;
    }
    break;
  case AIV_F_AGRESSION:
    if (op == VF_SET) {
      ai_info->agression = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->agression;
    }
    break;
  case AIV_F_NIGHT_VISION:
    if (op == VF_SET) {
      ai_info->night_vision = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->night_vision;
    }
    break;
  case AIV_F_FOG_VISION:
    if (op == VF_SET) {
      ai_info->fog_vision = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->fog_vision;
    }
    break;
  case AIV_F_LEAD_ACCURACY:
    if (op == VF_SET) {
      ai_info->lead_accuracy = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->lead_accuracy;
    }
    break;
  case AIV_F_LEAD_VARIENCE:
    if (op == VF_SET) {
      ai_info->lead_varience = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->lead_varience;
    }
    break;
  case AIV_F_FIGHT_TEAM:
    if (op == VF_SET) {
      ai_info->fight_team = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->fight_team;
    }
    break;
  case AIV_F_FIGHT_SAME:
    if (op == VF_SET) {
      ai_info->fight_same = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->fight_same;
    }
    break;
  case AIV_F_HEARING:
    if (op == VF_SET) {
      ai_info->hearing = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->hearing;
    }
    break;
  case AIV_F_ROAMING:
    if (op == VF_SET) {
      ai_info->roaming = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->roaming;
    }
    break;
  case AIV_F_LIFE_PRESERVATION:
    if (op == VF_SET) {
      ai_info->life_preservation = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->life_preservation;
    }
    break;
  case AIV_F_BIASED_FLIGHT_IMPORTANCE:
    if (op == VF_SET) {
      ai_info->biased_flight_importance = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->biased_flight_importance;
    }
    break;
  case AIV_F_BIASED_FLIGHT_MIN:
    if (op == VF_SET) {
      ai_info->biased_flight_min = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->biased_flight_min;
    }
    break;
  case AIV_F_BIASED_FLIGHT_MAX:
    if (op == VF_SET) {
      ai_info->biased_flight_max = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->biased_flight_max;
    }
    break;
  case AIV_F_AWARENESS:
    if (op == VF_SET) {
      ai_info->awareness = *((float *)ptr);
    } else {
      *((float *)ptr) = ai_info->awareness;
    }
    break;
  case AIV_I_FLAGS:
    if (op == VF_GET) {
      *((int *)ptr) = ai_info->flags;
    } else if (op == VF_SET) {
      ai_info->flags = *((int *)ptr);
    } else if (op == VF_SET_FLAGS) {
      ai_info->flags |= *((int *)ptr);
    } else if (op == VF_CLEAR_FLAGS) {
      ai_info->flags &= ~(*((int *)ptr));
    }
    break;
  case AIV_I_STATUS_REG:
    if (op == VF_GET) {
      *((int *)ptr) = ai_info->status_reg;
    } else if (op == VF_SET) {
      ai_info->status_reg = *((int *)ptr);
    } else if (op == VF_SET_FLAGS) {
      ai_info->status_reg |= *((int *)ptr);
    } else if (op == VF_CLEAR_FLAGS) {
      ai_info->status_reg &= ~(*((int *)ptr));
    }
    break;
  }
}

void osipf_ObjectValue(int handle, char op, char var_handle, void *ptr, int index) {
  object *obj = ObjGet(handle);
  if (!obj) {
    if (op == VF_GET && var_handle == OBJV_I_TYPE)
      *(int *)ptr = (int)OBJ_NONE;

    return;
  }

  msafe_struct m;
  m.objhandle = obj->handle;

  switch (var_handle) {
  case OBJV_PI_HACK_FVI_IGNORE_LIST: {
    if (op == VF_SET) {
      if (ptr != NULL) {
        int count = 0;

        do {
          hack_list[count] = ((int *)ptr)[count];
          count++;
        } while (hack_list[count - 1] != -1);

        hack_ilist = hack_list;
      } else {
        hack_ilist = NULL;
      }
    }
  } break;
  case OBJV_F_ROTDRAG:
    if (op == VF_SET) {
      m.rot_drag = *(float *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_ROTDRAG, &m);
    } else if (op == VF_GET)
      *(float *)ptr = obj->mtype.phys_info.rotdrag;
    break;
  case OBJV_F_SHIELDS:
    if (op == VF_SET) {
      m.shields = *(float *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_SHIELDS, &m);
    } else if (op == VF_GET)
      *(float *)ptr = obj->shields;
    break;
  case OBJV_I_TYPE:
    if (op == VF_SET) {
      m.type = *(int *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_TYPE, &m);
    } else if (op == VF_GET)
      (*(int *)ptr) = obj->type;
    break;
  case OBJV_US_ID:
    if (op == VF_SET) {
      m.id = *(uint16_t *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_ID, &m);
    } else if (op == VF_GET)
      (*(uint16_t *)ptr) = obj->id;
    break;
  case OBJV_V_POS:
    if (op == VF_SET) {
      ObjSetPos(obj, (vector *)ptr, obj->roomnum, NULL, true);
      obj->flags |= OF_MOVED_THIS_FRAME;
      obj->flags &= ~OF_STOPPED_THIS_FRAME;
    } else if (op == VF_GET)
      *(vector *)ptr = obj->pos;
    break;
  case OBJV_M_ORIENT:
    if (op == VF_SET) {
      ObjSetPos(obj, &obj->pos, obj->roomnum, (matrix *)ptr, true);
      obj->flags |= OF_MOVED_THIS_FRAME;
      obj->flags &= ~OF_STOPPED_THIS_FRAME;
    } else if (op == VF_GET)
      *(matrix *)ptr = obj->orient;
    break;
  case OBJV_I_ROOMNUM:
    if (op == VF_SET) {
      ObjSetPos(obj, &obj->pos, *(int *)ptr, NULL, false);
      obj->flags |= OF_MOVED_THIS_FRAME;
      obj->flags &= ~OF_STOPPED_THIS_FRAME;
    } else if (op == VF_GET)
      *(int *)ptr = obj->roomnum;
    break;
  case OBJV_V_VELOCITY:
    if (op == VF_SET)
      obj->mtype.phys_info.velocity = *(vector *)ptr;
    else if (op == VF_GET)
      *(vector *)ptr = obj->mtype.phys_info.velocity;
    break;
  case OBJV_V_ROTVELOCITY:
    if (op == VF_SET)
      obj->mtype.phys_info.rotvel = *(vector *)ptr;
    else if (op == VF_GET)
      *(vector *)ptr = obj->mtype.phys_info.rotvel;
    break;
    break;
  case OBJV_V_THRUST:
    if (op == VF_SET)
      obj->mtype.phys_info.thrust = *(vector *)ptr;
    else if (op == VF_GET)
      *(vector *)ptr = obj->mtype.phys_info.thrust;
    break;
    break;
  case OBJV_V_ROTTHRUST:
    if (op == VF_SET)
      obj->mtype.phys_info.rotthrust = *(vector *)ptr;
    else if (op == VF_GET)
      (*(vector *)ptr) = obj->mtype.phys_info.rotthrust;
    break;
    break;
  case OBJV_I_FLAGS: {
    int result = obj->flags;

    if (op == VF_GET)
      (*(int *)ptr) = obj->flags;
    else if (op == VF_SET)
      result = (*(int *)ptr);
    else if (op == VF_SET_FLAGS)
      result |= (*(int *)ptr);
    else if (op == VF_CLEAR_FLAGS)
      result &= ~(*(int *)ptr);

    if (op != VF_GET) {
      m.flags = result;
      msafe_CallFunction(MSAFE_OBJECT_FLAGS, &m);
    }
  } break;
  case OBJV_F_SIZE:
    if (op == VF_GET)
      *(float *)ptr = obj->size;
    break;
  case OBJV_S_NAME:
    if (op == VF_GET) {
      if (obj->name) {
        strcpy((char *)ptr, obj->name);
      } else {
        *((char *)ptr) = 0;
      }
    }
    break;
  case OBJV_C_CONTROL_TYPE:
    if (op == VF_SET) {
      m.control_type = *(char *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_CONTROL_TYPE, &m);
    } else if (op == VF_GET)
      *(char *)ptr = obj->control_type;
    break;
  case OBJV_C_MOVEMENT_TYPE:
    if (op == VF_SET) {
      m.movement_type = *(char *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_MOVEMENT_TYPE, &m);
    } else if (op == VF_GET)
      *(char *)ptr = obj->movement_type;
    break;
  case OBJV_F_CREATION_TIME:
    if (op == VF_SET) {
      m.creation_time = *(float *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_CREATION_TIME, &m);
    } else if (op == VF_GET)
      *(float *)ptr = obj->creation_time;
    break;
  case OBJV_I_PHYSICS_FLAGS: {
    int result = obj->mtype.phys_info.flags;

    if (op == VF_GET)
      (*(int *)ptr) = obj->mtype.phys_info.flags;
    else if (op == VF_SET)
      result = (*(int *)ptr);
    else if (op == VF_SET_FLAGS)
      result |= (*(int *)ptr);
    else if (op == VF_CLEAR_FLAGS)
      result &= ~(*(int *)ptr);

    if (op != VF_GET) {
      m.physics_flags = result;
      msafe_CallFunction(MSAFE_OBJECT_PHYSICS_FLAGS, &m);
    }
  } break;
  case OBJV_I_PARENT_HANDLE:
    if (op == VF_SET) {
      m.ithandle = *(int *)ptr;
      msafe_CallFunction(MSAFE_OBJECT_PARENT, &m);
    } else if (op == VF_GET)
      (*(int *)ptr) = obj->parent_handle;
    break;
  case OBJV_F_ANIM_FRAME:
    if (op == VF_GET)
      *(float *)ptr = obj->rtype.pobj_info.anim_frame;
    break;
  case OBJV_F_MAX_SHIELDS:
    if (op == VF_GET) {
      if (obj->type == OBJ_PLAYER || obj->type == OBJ_GHOST || obj->type == OBJ_OBSERVER)
        *(float *)ptr = 200.0f;
      else // chrishack -- make sure it is a generic object
        *(float *)ptr = Object_info[obj->id].hit_points;
    }
    break;
  case OBJV_PC_MARKER_MESSAGE:
    if (op == VF_GET) {
      if (obj->type == OBJ_MARKER) {
        strcpy((char *)ptr, MarkerMessages[obj->id]);
      } else {
        ((char *)ptr)[0] = '\0';
      }
    }
    break;
  case OBJSV_F_ANIM_START:
    if (obj->control_type != CT_AI)
      return;

    if (op == VF_GET)
      (*(float *)ptr) = Object_info[obj->id].anim[obj->ai_info->movement_type].elem[index].from;
    else if (op == VF_SET)
      Object_info[obj->id].anim[obj->ai_info->movement_type].elem[index].from = (*(float *)ptr);
    break;
  case OBJSV_F_ANIM_END:
    if (obj->control_type != CT_AI)
      return;

    if (op == VF_GET)
      (*(float *)ptr) = Object_info[obj->id].anim[obj->ai_info->movement_type].elem[index].to;
    else if (op == VF_SET)
      Object_info[obj->id].anim[obj->ai_info->movement_type].elem[index].to = (*(float *)ptr);
    break;
  case OBJSV_F_ANIM_TIME:
    if (obj->control_type != CT_AI)
      return;

    if (op == VF_GET)
      (*(float *)ptr) = Object_info[obj->id].anim[obj->ai_info->movement_type].elem[index].spc;
    else if (op == VF_SET)
      Object_info[obj->id].anim[obj->ai_info->movement_type].elem[index].spc = (*(float *)ptr);
    break;

  case OBJV_C_VIRUS_INFECTED: {
    // the object show signs of virus infection
    if (!obj->effect_info)
      return;

    if (op == VF_GET) {
      (*(char *)ptr) = (obj->effect_info->type_flags & EF_VIRUS_INFECTED) ? 1 : 0;
    } else if (op == VF_SET) {
      bool enable = (*(char *)ptr) ? true : false;

      if (enable) {
        obj->effect_info->type_flags |= EF_VIRUS_INFECTED;
      } else {
        obj->effect_info->type_flags &= ~EF_VIRUS_INFECTED;
      }
    }
  } break;

  case OBJV_C_IS_CLOAKED:
    if (op == VF_GET) {
      if (!obj->effect_info) {
        (*(char *)ptr) = 0;
      } else {
        (*(char *)ptr) = (obj->effect_info->type_flags & EF_CLOAKED) ? 1 : 0;
      }
    }
    break;

  case OBJV_C_NEGATIVE_LIGHT: {
    // the object casts negative light
    if (!obj->effect_info)
      return;

    if (op == VF_GET) {
      (*(char *)ptr) = (obj->effect_info->type_flags & EF_NEGATIVE_LIGHT) ? 1 : 0;
    } else if (op == VF_SET) {
      bool enable = (*(char *)ptr) ? true : false;

      if (enable) {
        obj->effect_info->type_flags |= EF_NEGATIVE_LIGHT;
      } else {
        obj->effect_info->type_flags &= ~EF_NEGATIVE_LIGHT;
      }
    }

  } break;
  }
}

uint8_t osipf_AITurnTowardsVectors(int objhandle, vector *fvec, vector *uvec) {
  object *objp = ObjGet(objhandle);

  if (!objp) {
    mprintf(0, "AITurnTowardsVectors: Illegal Object Passed\n");
    return 0;
  }

  if (objp->control_type != CT_AI) {
    mprintf(0, "AITurnTowardsVectors: Illegal Object CT Passed\n");
    return 0;
  }

  matrix g_orient;
  vm_VectorToMatrix(&g_orient, fvec, uvec, NULL);

  return AITurnTowardsMatrix(objp, objp->ai_info->max_turn_rate, &g_orient);
}

void osipf_AISetType(int objhandle, int type) {
  object *objp = ObjGet(objhandle);

  if (!objp) {
    mprintf(0, "AISetType: Illegal Object Passed\n");
    return;
  }

  if (objp->control_type != CT_AI) {
    mprintf(0, "AISetType: Illegal Object CT Passed\n");
    return;
  }

  if (type < 0 || type >= MAX_AI_INIT_TYPES)
    return;

  GoalInitTypeGoals(objp, type);
}

vector osipf_AIFindHidePos(int hideobjhandle, int viewobjhandle, float time, int *hide_room) {
  object *hide_obj = ObjGet(hideobjhandle);
  object *view_obj = ObjGet(viewobjhandle);

  vector hpos;
  int hroom;

  if (hide_obj == NULL) {
    mprintf(0, "Illegal Hide Object Passed To AIFindHidePos\n");
    *hide_room = -1;
    return Zero_vector;
  }

  if (hide_obj->control_type != CT_AI) {
    mprintf(0, "Illegal Object CT Passed To AIFindHidePos\n");
    *hide_room = -1;
    return Zero_vector;
  }

  if (view_obj == NULL) {
    mprintf(0, "Illegal View Object Passed To AIFindHidePos\n");
    *hide_room = hide_obj->roomnum;
    return hide_obj->pos;
  }

  if (time <= 0.0) {
    mprintf(0, "AIFindHidePos: Illegal Time Passed bashing to 1sec\n");
    time = 1.0f;
  } else if (time > 15.0) {
    mprintf(0, "AIFindHidePos: Illegal Time Passed bashing to 15sec\n");
    time = 15.0f;
  }

  // Returns the hide object's pos/room if it cannot find a valid hide position
  AIFindHidePos(hide_obj, view_obj, &hpos, &hroom, time);

  *hide_room = hroom;
  return hpos;
}

int osipf_AIGoalAddEnabler(int objhandle, int goal_index, int enabler_type, float percent, float interval, void *ptr) {
  object *obj;

  obj = ObjGet(objhandle);

  if (obj == NULL || obj->ai_info == NULL) {
    mprintf(0, "Illegal object passed to AIGoalAddEnabler\n");
    return -1;
  }

  if (!ptr)
    return -1;

  return GoalAddEnabler(obj, goal_index, enabler_type, ptr, percent, interval);
}

int osipf_AIGoalAdd(int objhandle, int goal_type, int level, float influence, int guid, int flags, ...) {
  object *obj;
  goal_info g_info;
  va_list marker;

  obj = ObjGet(objhandle);
  if (obj == NULL || obj->ai_info == NULL) {
    mprintf(0, "Illegal object passed to AIGoalAdd\n");
    return -1;
  }

  switch (goal_type) {
  case AIG_GET_AWAY_FROM_OBJ:
  case AIG_GET_TO_OBJ:
  case AIG_GUARD_OBJ:
  case AIG_DODGE_OBJ:
  case AIG_MOVE_AROUND_OBJ:
  case AIG_MOVE_RELATIVE_OBJ:
  case AIG_GET_AROUND_OBJ: {
    // Pop Goal Local Variables
    va_start(marker, flags);
    int objref = va_arg(marker, int);
    va_end(marker);

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&objref, level, influence, flags, guid);
  } break;

  case AIG_FOLLOW_PATH: {
    path_information path_info;

    va_start(marker, flags);
    path_info.path_id = va_arg(marker, int);
    path_info.start_node = va_arg(marker, int) - 1;
    path_info.end_node = va_arg(marker, int) - 1;
    path_info.next_node = va_arg(marker, int) - 1;
    va_end(marker);

    if (path_info.path_id >= 0 && path_info.end_node < 0) {
      path_info.end_node = GamePaths[path_info.path_id].num_nodes - 1;
    }

    return GoalAddGoal(obj, AIG_FOLLOW_PATH, (void *)&path_info, level, influence, flags, guid);
  } break;

  case AIG_ATTACH_TO_OBJ:
  case AIG_PLACE_OBJ_ON_OBJ: {
    goal_info g_info;
    g_info.attach_info.flags = 0;

    // Pop Goal Local Variables
    va_start(marker, flags);
    g_info.handle = va_arg(marker, int);
    g_info.attach_info.parent_ap = va_arg(marker, int);
    g_info.attach_info.child_ap = va_arg(marker, int);
    g_info.attach_info.rad = va_arg(marker, double);

    object *objp = ObjGet(g_info.handle);
    if (objp && (objp->type == OBJ_POWERUP))
      g_info.attach_info.rad /= 2;

    if (va_arg(marker, int) != 0)
      g_info.attach_info.flags = GAF_ALIGNED;
    if (va_arg(marker, int) != 0)
      g_info.attach_info.flags |= GAF_SPHERE;
    va_end(marker);

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&g_info, level, influence, flags, guid);
  } break;

  case AIG_FIRE_AT_OBJ: {
    // Pop Goal Local Variables
    va_start(marker, flags);
    int i = va_arg(marker, int);
    va_end(marker);

    gi_fire attack_info;

    attack_info.cur_wb = i;
    attack_info.cur_mask = obj->dynamic_wb[i].cur_firing_mask;

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&attack_info, level, influence, flags, guid);
  } break;

  case AIG_MOVE_RELATIVE_OBJ_VEC: {
    va_start(marker, flags);
    // Pop Goal Local Variables
    int objref = va_arg(marker, int);
    int i_value = va_arg(marker, int);
    va_end(marker);

    g_info.handle = objref;

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&g_info, level, influence, flags, guid, i_value);
  } break;

  case AIG_HIDE_FROM_OBJ: {
    // Pop Goal Local Variables
    va_start(marker, flags);
    int objref = va_arg(marker, int);
    int f_value = va_arg(marker, int);
    va_end(marker);

    g_info.handle = objref;
    g_info.time = f_value;

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&g_info, level, influence, flags, guid);
  } break;

  case AIG_GUARD_AREA:
  case AIG_GET_TO_POS: {
    // Pop Goal Local Variables
    va_start(marker, flags);
    vector *pos = va_arg(marker, vector *);
    int roomnum = va_arg(marker, int);
    va_end(marker);

    g_info.pos = (*pos);
    g_info.roomnum = roomnum;

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&g_info, level, influence, flags, guid);
  } break;

  case AIG_MELEE_TARGET: {
    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)NULL, level, influence, flags, guid);
  } break;

  case AIG_SET_ANIM:          // Animation index
  case AIG_DO_MELEE_ANIM:     // Which melee attack
  case AIG_USE_MOVEMENT_TYPE: // MT_INDEX
  case AIG_SCRIPTED: {
    // Pop Goal Local Variables
    va_start(marker, flags);
    int i_value = va_arg(marker, int);
    va_end(marker);

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&i_value, level, influence, flags, guid);
  } break;

  case AIG_WANDER_AROUND: // Initial room
  {
    // Pop Goal Local Variables
    va_start(marker, flags);
    int i_value = va_arg(marker, int);
    int j_value = va_arg(marker, int);
    va_end(marker);

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)&i_value, level, influence, flags, guid);
  } break;

  case AIG_FACE_DIR: // MT_INDEX
  {
    // Pop Goal Local Variables
    va_start(marker, flags);
    vector *v_value = va_arg(marker, vector *);
    va_end(marker);

    // Do the actual goal and return;
    return GoalAddGoal(obj, goal_type, (void *)v_value, level, influence, flags, guid);
  } break;

  default:
    mprintf(0, "AIGoalAdd Error: Get chris - goal %d is not available of scripting\n", goal_type);
  }

  return -1;
}

void osipf_AIGoalClear(int objhandle, int goal_index) {
  object *obj = ObjGet(objhandle);

  if (obj == NULL) {
    mprintf(0, "Invalid Object Passed To AIGoalClear\n");
    return;
  }

  if (obj->control_type != CT_AI) {
    mprintf(0, "AIGoalClear: Illegal Object CT Passed\n");
    return;
  }

  if (goal_index < 0) {
    GoalClearAll(obj);
  } else if (goal_index < MAX_GOALS) {
    GoalClearGoal(obj, &obj->ai_info->goals[goal_index]);
  }
}

int osipf_AIFindObjOfType(int objhandle, int type, int id, bool f_ignore_init_room, int parent_handle) {
  object *obj = ObjGet(objhandle);
  object *f_obj;

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To AIFindObjOfType\n");
    return OBJECT_HANDLE_NONE;
  }

  if ((f_obj = AIFindObjOfType(obj, type, id, f_ignore_init_room, parent_handle)))
    return f_obj->handle;

  return OBJECT_HANDLE_NONE;
}

int osipf_ObjMakeListOfType(int objhandle, int type, int id, bool f_ignore_init_room, int parent_handle,
                            int max_recorded, int *handles) {
  object *obj = ObjGet(objhandle);

  int num_recorded = 0;
  int i;

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To Obj_MakeListOfType\n");
    return OBJECT_HANDLE_NONE;
  }

  for (i = 0; i <= Highest_object_index; i++) {
    if (Objects[i].type == type) {
      if (Objects[i].type == OBJ_NONE)
        continue;

      if (&Objects[i] == obj)
        continue;

      if (f_ignore_init_room && Objects[i].roomnum == obj->roomnum)
        continue;

      if (parent_handle != OBJECT_HANDLE_NONE && Objects[i].parent_handle != parent_handle)
        continue;

      if (id != -1 && Objects[i].id != id)
        continue;

      handles[num_recorded++] = Objects[i].handle;

      if (num_recorded >= max_recorded)
        break;
    }
  }

  return num_recorded;
}

vector osipf_AIGetRoomPathPoint(int roomnum) {
  if (ROOMNUM_OUTSIDE(roomnum)) {
    int cell = CELLNUM(roomnum);

    if (cell >= TERRAIN_DEPTH * TERRAIN_WIDTH) {
      return Zero_vector;
    } else {
      vector pos;

      ComputeTerrainSegmentCenter(&pos, cell);
      pos.y += 15.0f + ((float)ps_rand() / (float)D3_RAND_MAX) * 20; // between 15 and 35

      return pos;
    }
  } else if (roomnum <= Highest_room_index && Rooms[roomnum].used) {
    return Rooms[roomnum].path_pnt;
  }

  return Zero_vector;
}

int osipf_AIFindEnergyCenter(int objhandle) {
  object *obj = ObjGet(objhandle);

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To AIFindEnergyCenter\n");
    return -1;
  }

  // returns the roomnum of the closest room with that flag
  return AIFindRoomWithFlag(obj, RF_FUELCEN);
}

float osipf_AIGetDistToObj(int objhandle, int otherobjhandle) {
  object *obj = ObjGet(objhandle);
  object *fobj = ObjGet(otherobjhandle);

  float dist;

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To AIGetDistToObj\n");
    return 0;
  }

  if (fobj == NULL) {
    mprintf(0, "Illegal Find Object Passed To AIGetDistToObj\n");
    return 0;
  }

  BOA_ComputeMinDist(obj->roomnum, fobj->roomnum, 0.0f, &dist, NULL);

  return dist;
}

int osipf_AISetGoalFlags(int objhandle, int goal_handle, int flags, uint8_t f_enable) {
  object *obj = ObjGet(objhandle);

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To AISetGoalFlags\n");
    return 0;
  }

  if (obj->control_type != CT_AI) {
    mprintf(0, "Non-AI Object Passed To AISetGoalFlags\n");
    return 0;
  }

  ai_frame *ai_info = obj->ai_info;

  if (goal_handle >= 0 && goal_handle < MAX_GOALS && ai_info->goals[goal_handle].used != 0) {
    if (f_enable)
      ai_info->goals[goal_handle].flags |= flags;
    else
      ai_info->goals[goal_handle].flags &= ~flags;
  }

  return (ai_info->goals[goal_handle].flags);
}

void osipf_AISetGoalCircleDist(int objhandle, int goal_handle, float dist) {
  object *obj = ObjGet(objhandle);

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To AISetGoalCircleDist\n");
    return;
  }

  if (obj->control_type != CT_AI) {
    mprintf(0, "Non-AI Object Passed To AISetGoalCircleDist\n");
    return;
  }

  ai_frame *ai_info = obj->ai_info;

  if (goal_handle >= 0 && goal_handle < MAX_GOALS && ai_info->goals[goal_handle].used != 0) {
    ai_info->goals[goal_handle].circle_distance = dist;
  }
}

void osipf_GetGunPos(int objhandle, int gun_number, vector *gun_pnt, vector *gun_normal) {
  object *obj = ObjGet(objhandle);

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To AIGetGunPosition\n");
    *gun_pnt = Zero_vector;
    *gun_normal = Zero_vector;
    return;
  }

  WeaponCalcGun(gun_pnt, gun_normal, obj, gun_number);
}

void osipf_GetGroundPos(int objhandle, int ground_number, vector *ground_pnt, vector *ground_normal) {
  object *obj = ObjGet(objhandle);

  if (obj == NULL) {
    mprintf(0, "Illegal Object Passed To Obj_GetGroundPos\n");
    *ground_pnt = Zero_vector;
    *ground_normal = Zero_vector;
    return;
  }

  PhysCalcGround(ground_pnt, ground_normal, obj, ground_number);
}

uint8_t osipf_IsRoomValid(int roomnum) {
  if (roomnum == -1.0) {
    return 0;
  } else if (ROOMNUM_OUTSIDE(roomnum)) {
    int cell = CELLNUM(roomnum);

    if ((CELLNUM(cell) < 0) || (cell >= TERRAIN_WIDTH * TERRAIN_DEPTH)) {
      return 0;
    } else {
      return 1;
    }
  } else {
    if (roomnum < 0 || roomnum > Highest_room_index || Rooms[roomnum].used == 0) {
      return 0;
    } else {
      return 2;
    }
  }

  return 0;
}

int osipf_GetAttachParent(int childhandle) {
  object *child = ObjGet(childhandle);

  if ((child) && (child->flags & OF_ATTACHED)) {
    return (child->attach_parent_handle);
  }

  return (OBJECT_HANDLE_NONE);
}

int osipf_GetNumAttachSlots(int objhandle) {
  object *parent = ObjGet(objhandle);

  if ((parent) && (parent->flags & OF_POLYGON_OBJECT)) {
    poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
    return (parent_pm->n_attach);
  }

  return 0;
}

int osipf_GetAttachChildHandle(int objhandle, char attachpoint) {
  object *parent = ObjGet(objhandle);
  char parent_ap = attachpoint;

  if ((parent) && (parent->flags & OF_POLYGON_OBJECT)) {
    poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
    if (parent_ap >= 0 && parent_ap < parent_pm->n_attach) {
      return (parent->attach_children[parent_ap]);
    }
  }

  return (OBJECT_HANDLE_NONE);
}

int osipf_AttachObjectAP(int parenthandle, char parent_ap, int childhandle, char child_ap, uint8_t f_use_aligned) {
  object *parent = ObjGet(parenthandle);
  object *child = ObjGet(childhandle);

  if ((parent) && (parent->flags & OF_POLYGON_OBJECT) && (child) && (child->flags & OF_POLYGON_OBJECT)) {
    return AttachObject(parent, parent_ap, child, child_ap, (bool)(f_use_aligned != 0));
  }

  return 0;
}

int osipf_AttachObjectRad(int parenthandle, char parent_ap, int childhandle, float percent_rad) {
  object *parent = ObjGet(parenthandle);
  object *child = ObjGet(childhandle);

  if ((parent) && (parent->flags & OF_POLYGON_OBJECT) && (child) && (child->flags & OF_POLYGON_OBJECT)) {
    return AttachObject(parent, parent_ap, child, percent_rad);
  }

  return 0;
}

void osipf_UnattachFromParent(int objhandle) {
  object *child = ObjGet(objhandle);

  if ((child) && (child->flags & OF_POLYGON_OBJECT)) {
    UnattachFromParent(child);
  }
}

void osipf_UnattachChild(int objhandle, char parent_ap) {
  object *parent = ObjGet(objhandle);

  if ((parent) && (parent->flags & OF_POLYGON_OBJECT)) {
    UnattachChild(parent, parent_ap);
  }
}

void osipf_UnattachChildren(int objhandle) {
  object *parent = ObjGet(objhandle);

  if ((parent) && (parent->flags & OF_POLYGON_OBJECT)) {
    UnattachChildren(parent);
  }
}

void osipf_MatcenValue(int matcen_id, char op, char var_handle, void *ptr, int index) {
  if (matcen_id < 0 || matcen_id >= Num_matcens || !Matcen[matcen_id])
    return;
  switch (var_handle) {
  case MTNV_C_ATTACH_TYPE:
    if (op == VF_GET)
      (*(char *)ptr) = Matcen[matcen_id]->GetAttachType();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetAttachType(*(char *)ptr);
    break;
  case MTNV_C_CONTROL_TYPE:
    if (op == VF_GET)
      (*(char *)ptr) = Matcen[matcen_id]->GetControlType();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetControlType(*(char *)ptr);
    break;
  case MTNV_I_ATTACH:
    if (op == VF_GET)
      (*(int *)ptr) = Matcen[matcen_id]->GetAttach();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetAttach(*(int *)ptr);
    break;
  case MTNV_V_CREATE_POINT:
    if (op == VF_GET)
      Matcen[matcen_id]->GetCreatePnt((vector *)ptr);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetCreatePnt((vector *)ptr);
    break;
  case MTNV_I_CREATE_ROOM:
    if (op == VF_GET)
      (*(int *)ptr) = Matcen[matcen_id]->GetCreateRoom();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetCreateRoom(*(int *)ptr);
    break;
  case MTNV_PC_NAME:
    if (op == VF_GET)
      Matcen[matcen_id]->GetName((char *)ptr);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetName((char *)ptr);
    break;
  case MTNV_I_MAX_PROD:
    if (op == VF_GET)
      (*(int *)ptr) = Matcen[matcen_id]->GetMaxProd();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetMaxProd(*(int *)ptr);
    break;
  case MTNV_F_PROD_MULTIPLIER:
    if (op == VF_GET)
      (*(float *)ptr) = Matcen[matcen_id]->GetProdMultiplier();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetProdMultiplier(*(float *)ptr);
    break;
  case MTNV_I_STATUS:
    if (op == VF_GET)
      (*(int *)ptr) = Matcen[matcen_id]->GetStatus();
    else if (op == VF_SET_FLAGS)
      Matcen[matcen_id]->SetStatus(*(int *)ptr, true);
    else if (op == VF_CLEAR_FLAGS)
      Matcen[matcen_id]->SetStatus(*(int *)ptr, false);
    else if (op == VF_SET) {
      int status = Matcen[matcen_id]->GetStatus();
      int diff_flags = (*(int *)ptr) ^ status;
      int clear_flags = status & diff_flags;
      int set_flags = (~(status)) & diff_flags;

      if (set_flags)
        Matcen[matcen_id]->SetStatus(set_flags, true);
      if (clear_flags)
        Matcen[matcen_id]->SetStatus(clear_flags, false);
    }
    break;
  case MTNV_C_CREATION_EFFECT:
    if (op == VF_GET)
      (*(char *)ptr) = Matcen[matcen_id]->GetCreationEffect();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetCreationEffect(*(char *)ptr);
    break;
  case MTNV_I_MAX_ALIVE_CHILDREN:
    if (op == VF_GET)
      (*(int *)ptr) = Matcen[matcen_id]->GetMaxAliveChildren();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetMaxAliveChildren(*(int *)ptr);
    break;
  case MTNV_F_PRE_PROD_TIME:
    if (op == VF_GET)
      (*(float *)ptr) = Matcen[matcen_id]->GetPreProdTime();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetPreProdTime(*(float *)ptr);
    break;
  case MTNV_F_POST_PROD_TIME:
    if (op == VF_GET)
      (*(float *)ptr) = Matcen[matcen_id]->GetPostProdTime();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetPostProdTime(*(float *)ptr);
    break;
  case MTNSV_I_SOUND:
    if (op == VF_GET)
      (*(int *)ptr) = Matcen[matcen_id]->GetSound(index);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetSound(index, (*(int *)ptr));
    break;
  case MTNV_S_CREATION_TEXTURE:
    if (op == VF_GET)
      (*(int16_t *)ptr) = Matcen[matcen_id]->GetCreationTexture();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetCreationTexture(*(int16_t *)ptr);
    break;

  case MTNV_C_NUM_SPAWN_PTS:
    if (op == VF_GET)
      (*(char *)ptr) = Matcen[matcen_id]->GetNumSpawnPnts();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetNumSpawnPnts(*(char *)ptr);
    break;
  case MTNSV_I_SPAWN_POINT:
    if (op == VF_GET)
      Matcen[matcen_id]->SetSpawnPnt(index, *(int *)ptr);
    else if (op == VF_SET)
      (*(int *)ptr) = Matcen[matcen_id]->GetSpawnPnt(index);
    break;

  case MTNV_C_NUM_PROD_TYPES:
    if (op == VF_GET)
      (*(char *)ptr) = Matcen[matcen_id]->GetNumProdTypes();
    else if (op == VF_SET)
      Matcen[matcen_id]->SetNumSpawnPnts(*(char *)ptr);
    break;
  case MTNSV_I_PROD_ITEM_ID:
    if (op == VF_GET)
      Matcen[matcen_id]->GetProdInfo(index, (int *)ptr, NULL, NULL, NULL);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetProdInfo(index, (int *)ptr, NULL, NULL, NULL);
    break;
  case MTNSV_I_PROD_ITEM_PRIORITY:
    if (op == VF_GET)
      Matcen[matcen_id]->GetProdInfo(index, NULL, (int *)ptr, NULL, NULL);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetProdInfo(index, NULL, (int *)ptr, NULL, NULL);
    break;
  case MTNSV_F_PROD_ITEM_TIME:
    if (op == VF_GET)
      Matcen[matcen_id]->GetProdInfo(index, NULL, NULL, (float *)ptr, NULL);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetProdInfo(index, NULL, NULL, (float *)ptr, NULL);
    break;
  case MTNSV_I_PROD_ITEM_MAX_PROD:
    if (op == VF_GET)
      Matcen[matcen_id]->GetProdInfo(index, NULL, NULL, NULL, (int *)ptr);
    else if (op == VF_SET)
      Matcen[matcen_id]->SetProdInfo(index, NULL, NULL, NULL, (int *)ptr);
    break;
  }
}

void osipf_MatcenReset(int matcen_id) {
  if (matcen_id >= 0 && matcen_id < Num_matcens && Matcen[matcen_id]) {
    Matcen[matcen_id]->Reset();
  }
}

int osipf_MatcenCreate(char *str) {
  bool name_changed;

  char name[MAX_MATCEN_NAME_LEN];
  strncpy(name, str, MAX_MATCEN_NAME_LEN - 1);
  name[MAX_MATCEN_NAME_LEN - 1] = '\0';

  return CreateMatcen(name, &name_changed);
}

void osipf_MatcenCopy(int md_id, int ms_id) {
  if (md_id >= 0 && md_id < Num_matcens && Matcen[md_id]) {
    if (ms_id >= 0 && ms_id < Num_matcens && Matcen[ms_id]) {
      char name[MAX_MATCEN_NAME_LEN];
      Matcen[md_id]->GetName(name);

      *Matcen[md_id] = *Matcen[ms_id];
      Matcen[md_id]->SetName(name);
      Matcen[md_id]->Reset();
    }
  }
}

int osipf_MatcenFindId(char *str) {
  char name[MAX_MATCEN_NAME_LEN];
  strncpy(name, str, MAX_MATCEN_NAME_LEN - 1);
  name[MAX_MATCEN_NAME_LEN - 1] = '\0';

  return FindMatcenIndex(name);
}

int osipf_RayCast(int objhandle, vector *p0, vector *p1, int start_roomnum, float rad, int flags, ray_info *ri) {
  int fate;
  int ignore_obj_list[100];

  int *ilist = hack_ilist;
  object *obj = ObjGet(objhandle);
  if (!obj && objhandle != OBJECT_HANDLE_NONE) {
    mprintf(0, "Invalid object passed to RayCast\n");
    return 0;
  }

  fvi_info hit_info;
  fvi_query fq;

  fq.p0 = p0;
  fq.p1 = p1;

  fq.startroom = start_roomnum;

  fq.rad = rad;
  fq.flags = flags;

  if (obj)
    fq.thisobjnum = OBJNUM(obj);
  else
    fq.thisobjnum = -1;

  if (ilist) {
    int num_items = 0;
    int count = 0;

    while (ilist[count] != -1) {
      object *iobj = ObjGet(ilist[count]);
      if (iobj) {
        ignore_obj_list[num_items++] = OBJNUM(iobj);
      }

      count++;
    }

    ignore_obj_list[num_items] = -1;
    fq.ignore_obj_list = ignore_obj_list;
  } else {
    fq.ignore_obj_list = NULL;
  }

  fate = fvi_FindIntersection(&fq, &hit_info);

  ri->hit_point = hit_info.hit_pnt;
  ri->hit_room = hit_info.hit_room;
  ri->fate = fate;

  if (fate == HIT_SPHERE_2_POLY_OBJECT || fate == HIT_OBJECT) {
    ri->hit_object = Objects[hit_info.hit_object[0]].handle;
  }
  ri->hit_subobject = hit_info.hit_subobject[0];

  ri->hit_face = hit_info.hit_face[0];
  ri->hit_face_pnt = hit_info.hit_face_pnt[0];
  ri->hit_face_room = hit_info.hit_face_room[0];
  ri->hit_wallnorm = hit_info.hit_wallnorm[0];

  return fate;
}

// Reads the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO READ STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes read.
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int osipf_CFReadBytes(uint8_t *buffer, int count, CFILE *cfp) { return cf_ReadBytes(buffer, count, cfp); }

// The following functions read numeric vales from a CFILE.  All values are
// stored in the file in Intel (little-endian) format.  These functions
// will convert to big-endian if required.
// These funtions will throw an exception of if the value cannot be read,
// so do not call these if you don't require the data to be present.

// Read and return an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int osipf_CFReadInt(CFILE *cfp) { return cf_ReadInt(cfp); }

// Read and return a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int16_t osipf_CFReadShort(CFILE *cfp) { return cf_ReadShort(cfp); }

// Read and return a byte (8 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int8_t osipf_CFReadByte(CFILE *cfp) { return cf_ReadByte(cfp); }

// Read and return a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
float osipf_CFReadFloat(CFILE *cfp) { return cf_ReadFloat(cfp); }

// Read and return a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
double osipf_CFReadDouble(CFILE *cfp) { return cf_ReadDouble(cfp); }

// Reads a string from a CFILE.  If the file is type binary, this
// function reads until a NULL or EOF is found.  If the file is text,
// the function reads until a newline or EOF is found.  The string is always
// written to the destination buffer null-terminated, without the newline.
// Parameters:  buf - where the string is written
//					n - the maximum string length, including the terminating 0
//					cfp - the CFILE pointer
// Returns the number of bytes in the string, before the terminator
// Does not generate an exception on EOF
int osipf_CFReadString(char *buf, size_t n, CFILE *cfp) { return cf_ReadString(buf, n, cfp); }

// Writes the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO WRITE STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes written.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
int osipf_CFWriteBytes(const uint8_t *buf, int count, CFILE *cfp) { return cf_WriteBytes(buf, count, cfp); }

// Writes a null-terminated string to a file.  If the file is type binary,
// the string is terminated in the file with a null.  If the file is type
// text, the string is terminated with a newline.
// Parameters:	buf - pointer to the string
//					cfp = the CFILE pointer
// Returns the number of bytes written
// Throws an exception of type (cfile_error *) if the OS returns an error on write
int osipf_CFWriteString(const char *buf, CFILE *cfp) { return cf_WriteString(cfp, buf); }

// The following functions write numeric vales to a CFILE.  All values are
// stored to the file in Intel (little-endian) format.
// All these throw an exception if there's an error on write.

// Write an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void osipf_CFWriteInt(int i, CFILE *cfp) { cf_WriteInt(cfp, i); }

// Write a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void osipf_CFWriteShort(int16_t s, CFILE *cfp) { cf_WriteShort(cfp, s); }

// Write a byte (8 bits).  If the byte is a newline & the file is a text file, writes a CR/LF pair.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void osipf_CFWriteByte(int8_t b, CFILE *cfp) { cf_WriteByte(cfp, b); }

// Write a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void osipf_CFWriteFloat(float f, CFILE *cfp) { cf_WriteFloat(cfp, f); }

// Write a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void osipf_CFWriteDouble(double d, CFILE *cfp) { cf_WriteDouble(cfp, d); }

// CONTROLLER predefs

//	enables or disables controls specified.
void osipf_SetAllControls(bool enabled) {
  int i;

  for (i = 0; i < NUM_CONTROLLER_FUNCTIONS; i++) {
    Controller->enable_function(i, enabled);
  }
}

// enable or disable specified function
void osipf_SetControls(int fn, bool enabled) {
  if (Controller) {
    Controller->enable_function(fn, enabled);
  }
}

//	display messages using a primative dialog
void osipf_OpenMessageWindow(const char *title, ...) {
  Int3(); // ummm, this is a blank function, should we ever be calling it?
}

int osipf_ObjCreate(uint8_t type, uint16_t id, int roomnum, vector *pos, const matrix *orient, int parent_handle,
                    vector *initial_velocity) {
  object *obj;
  int objnum;

  if (id == 65535) // since it is a uint16_t, this is == -1
    return OBJECT_HANDLE_NONE;

  if (((roomnum >= 0) && (roomnum <= Highest_room_index) && (Rooms[roomnum].used)) || (ROOMNUM_OUTSIDE(roomnum))) {
    if (IS_GENERIC(type)) {
      // Make sure the scripts aren't creating objects that have lightmaps!
      ASSERT(Object_info[id].lighting_info.lighting_render_type != LRT_LIGHTMAPS);
    }

    objnum = ObjCreate(type, id, roomnum, pos, orient, parent_handle);

    if (objnum == -1) {
      return OBJECT_HANDLE_NONE;
    }

    obj = &Objects[objnum];

    // if there was an initial velocity, set it
    if (initial_velocity) {
      ASSERT(obj->movement_type == MT_PHYSICS);
      obj->mtype.phys_info.velocity = *initial_velocity;
    }

    if (Game_mode & GM_MULTI) {
      // ASSERT (Netgame.local_role==LR_SERVER);
      if (Netgame.local_role == LR_SERVER) {
        MultiSendObject(obj, 0);
      }
    }

    InitObjectScripts(obj);

    if (IS_GENERIC(obj->type)) {
      int ambient_sound = Object_info[obj->id].sounds[GSI_AMBIENT];
      if (ambient_sound != SOUND_NONE_INDEX) {
        Sound_system.Play3dSound(ambient_sound, SND_PRIORITY_LOWEST, obj);
        if (Game_mode & GM_MULTI)
          MultiPlay3dSound(ambient_sound, objnum, SND_PRIORITY_LOW);
        if (Demo_flags == DF_RECORDING)
          DemoWrite3DSound(ambient_sound, objnum, SND_PRIORITY_LOW);
      }
    }
  } else {
    return OBJECT_HANDLE_NONE;
  }

  return obj->handle;
}

// OBJECT Properties.
bool osipf_IsObjectVisible(object *obj) {
  if (obj->renderframe != ((FrameCount - 1) % 65536)) {
    return false;
  }

  return true;
}

float osipf_GameTime(void) { return Gametime; }

float osipf_FrameTime(void) { return Frametime; }

void osipf_ObjWBValue(int obj_handle, char wb_index, char op, char vtype, void *ptr, char g_index) {
  object *objp = ObjGet(obj_handle);

  if (!objp) {
    mprintf(0, "Obj_WBValue: Illegal Object Passed\n");
    return;
  }

  if (objp->control_type != CT_AI && objp->type != OBJ_PLAYER && objp->type != OBJ_OBSERVER) {
    mprintf(0, "Obj_WBValue: Illegal Object CT Passed\n");
    return;
  }

  dynamic_wb_info *p_dwb = &objp->dynamic_wb[wb_index];
  otype_wb_info *static_wb;
  poly_model *pm = &Poly_models[objp->rtype.pobj_info.model_num];

  if (objp->type == OBJ_PLAYER || objp->type == OBJ_OBSERVER) {
    ship *ship = &Ships[Players[objp->id].ship_index];
    static_wb = &ship->static_wb[wb_index];
  } else {
    object_info *obj_info = &Object_info[objp->id];
    static_wb = &obj_info->static_wb[wb_index];
  }

  if (objp->type == OBJ_BUILDING && (wb_index < 0 || wb_index > pm->num_wbs)) {
    return;
  }

  switch (vtype) {
  case WBV_C_NUM_WBS: {
    if (op == VF_GET) {
      *(char *)ptr = pm->num_wbs;
    }
  } break;
  case WBV_F_ANIM_FRAME:
    if (op == VF_GET) {
      int anim_type = static_wb->flags & WBF_ANIM_MASKS;

      if (anim_type == WBF_ANIM_LOCAL) {
        *((float *)ptr) = p_dwb->wb_anim_frame;
      } else {
        *((float *)ptr) = objp->rtype.pobj_info.anim_frame;
      }
    }
    break;

  case WBV_F_LAST_FIRE_TIME:
    if (op == VF_SET) {
      p_dwb->last_fire_time = *((float *)ptr);
    } else if (op == VF_GET) {
      *((float *)ptr) = p_dwb->last_fire_time;
    }
    break;

  case WBV_I_DYNAMIC_FLAGS:
    if (op == VF_SET) {
      p_dwb->flags = *((int *)ptr);
    } else if (op == VF_GET) {
      *((int *)ptr) = p_dwb->flags;
    } else if (op == VF_SET_FLAGS) {
      p_dwb->flags |= *((int *)ptr);
    } else if (op == VF_CLEAR_FLAGS) {
      p_dwb->flags &= ~(*((int *)ptr));
    }
    break;

  case WBV_C_NUM_GUNPTS:
    if (op == VF_GET) {
      if (objp->type == OBJ_PLAYER || objp->type == OBJ_OBSERVER) {
        *((char *)ptr) = 8;
      } else {
        *((char *)ptr) = pm->poly_wb[wb_index].num_gps;
      }
    }
    break;
  case WBSV_US_GUNPT_WEAPON_ID:
    if (op == VF_SET) {
      static_wb->gp_weapon_index[g_index] = *((uint16_t *)ptr);
    } else if (op == VF_GET) {
      *((uint16_t *)ptr) = static_wb->gp_weapon_index[g_index];
    }
    break;
  case WBSV_V_GUNPT_POS:
    if (op == VF_GET) {
      if (objp->type == OBJ_PLAYER || objp->type == OBJ_OBSERVER)
        WeaponCalcGun(((vector *)ptr), NULL, objp, pm->poly_wb[0].gp_index[g_index]);
      else
        WeaponCalcGun(((vector *)ptr), NULL, objp, pm->poly_wb[wb_index].gp_index[g_index]);
    }
    break;

  case WBV_C_NUM_MASKS:
    if (op == VF_SET) {
      static_wb->num_masks = *((char *)ptr);
    } else if (op == VF_GET) {
      *((char *)ptr) = static_wb->num_masks;
    }
    break;
  case WBSV_C_MASK:
    if (op == VF_SET) {
      static_wb->gp_fire_masks[g_index] = *((char *)ptr);
    } else if (op == VF_GET) {
      *((char *)ptr) = static_wb->gp_fire_masks[g_index];
    } else if (op == VF_SET_FLAGS) {
      static_wb->gp_fire_masks[g_index] |= *((char *)ptr);
    } else if (op == VF_CLEAR_FLAGS) {
      static_wb->gp_fire_masks[g_index] &= ~(*((char *)ptr));
    }
    break;
  case WBSV_I_FIRE_SOUND:
    if (op == VF_SET) {
      static_wb->fm_fire_sound_index[g_index] = (*((int *)ptr));
    } else if (op == VF_GET) {
      (*((int *)ptr)) = static_wb->fm_fire_sound_index[g_index];
    }
    break;
  case WBSV_F_LATENCY:
    if (op == VF_SET) {
      static_wb->gp_fire_wait[g_index] = (*((float *)ptr));
    } else if (op == VF_GET) {
      (*((float *)ptr)) = static_wb->gp_fire_wait[g_index];
    }
    break;
  case WBSV_F_ANIM_TIME:
    if (op == VF_SET) {
      static_wb->anim_time[g_index] = (*((float *)ptr));
    } else if (op == VF_GET) {
      (*((float *)ptr)) = static_wb->anim_time[g_index];
    }
    break;
  case WBSV_F_ANIM_START:
    if (op == VF_SET) {
      static_wb->anim_start_frame[g_index] = (*((float *)ptr));
    } else if (op == VF_GET) {
      (*((float *)ptr)) = static_wb->anim_start_frame[g_index];
    }
    break;
  case WBSV_F_ANIM_FIRE:
    if (op == VF_SET) {
      static_wb->anim_fire_frame[g_index] = (*((float *)ptr));
    } else if (op == VF_GET) {
      (*((float *)ptr)) = static_wb->anim_fire_frame[g_index];
    }
    break;
  case WBSV_F_ANIM_END:
    if (op == VF_SET) {
      static_wb->anim_end_frame[g_index] = (*((float *)ptr));
    } else if (op == VF_GET) {
      (*((float *)ptr)) = static_wb->anim_end_frame[g_index];
    }
    break;
  }
}

// Sets/Clears mission flags
//	flag is which mission flag to set/clear (1-32)
//	value is 0 to clear, or 1 to set
void osipf_MissionFlagSet(int flag, uint8_t value) {
  if (flag < 1 && flag > 32) {
    mprintf(0, "Invalid flag passed to osipf_MissionFlagSet(%d)\n", flag);
    return;
  }

  flag--;
  uint32_t bit = 0x01;
  bit = bit << flag;

  if (!value) {
    Current_mission.game_state_flags &= ~bit;
  } else {
    Current_mission.game_state_flags |= bit;
  }
}

// Gets a mission flag
//	flag is what mission flag to get.  Returns 1 if set, 0 if not.
int osipf_MissionFlagGet(int flag) {
  if (flag < 1 && flag > 32) {
    mprintf(0, "Invalid flag passed to osipf_MissionFlagGet(%d)\n", flag);
    return 0;
  }

  flag--;
  uint32_t bit = 0x01;
  bit = bit << flag;

  if (Current_mission.game_state_flags & bit)
    return 1;

  return 0;
}

void osipf_PlayerAddHudMessage(int handle, const char *str) {
  msafe_struct mo;

  mo.objhandle = mo.id = handle;
  mo.color = GR_RGB(0, 255, 0);
  strncpy(mo.message, str, MSAFE_MESSAGE_LENGTH - 1);
  mo.message[MSAFE_MESSAGE_LENGTH - 1] = '\0';

  msafe_CallFunction(MSAFE_MISC_HUD_MESSAGE, &mo);
}

void osipf_ObjGhost(int handle, bool f_ghost) {
  object *obj = ObjGet(handle);
  if (obj) {
    // BLACKPYROHACK - Chrishack for Mercenary
    if (!(Game_mode & GM_MULTI)) {
      if (obj->handle == Buddy_handle[0]) {
        if (stricmp(Ships[Players[Player_object->id].ship_index].name, "Black Pyro") == 0) {
          obj->id = ROBOT_GUIDEBOTRED;
          PageInPolymodel(Object_info[ROBOT_GUIDEBOTRED].render_handle, Object_info[ROBOT_GUIDEBOTRED].type,
                          &Object_info[ROBOT_GUIDEBOTRED].size);
          obj->rtype.pobj_info.model_num = Object_info[ROBOT_GUIDEBOTRED].render_handle;
        } else {
          obj->id = ROBOT_GUIDEBOT;
          obj->rtype.pobj_info.model_num = Object_info[ROBOT_GUIDEBOT].render_handle;
        }
      }
    }

    msafe_struct mo;
    mo.objhandle = obj->handle;

    if (f_ghost)
      msafe_CallFunction(MSAFE_OBJECT_GHOST, &mo);
    else
      msafe_CallFunction(MSAFE_OBJECT_UNGHOST, &mo);
  }
}

void osipf_ObjBurning(int handle, float time, float damage_per_second) {
  object *obj = ObjGet(handle);
  if (obj && obj->effect_info) {
    if (time > 0.0) {
      obj->effect_info->type_flags |= EF_NAPALMED;

      obj->effect_info->damage_time = time;
      obj->effect_info->damage_per_second = damage_per_second;

      obj->effect_info->last_damage_time = 0;

      obj->effect_info->damage_handle = obj->handle;

      if (obj->effect_info->sound_handle == SOUND_NONE_INDEX)
        obj->effect_info->sound_handle = Sound_system.Play3dSound(SOUND_PLAYER_BURNING, SND_PRIORITY_HIGHEST, obj);
    } else {
      obj->effect_info->type_flags &= (~EF_NAPALMED);
      obj->effect_info->last_damage_time = 0;
      Sound_system.StopSoundLooping(obj->effect_info->sound_handle);
      obj->effect_info->sound_handle = SOUND_NONE_INDEX;
    }
  }
}

bool osipf_ObjIsEffect(int handle, int type_flag) {
  object *obj = ObjGet(handle);
  return (obj && obj->effect_info && (obj->effect_info->type_flags & type_flag));
}

void *osipf_CFopen(const char *filename, const char *mode) { return cfopen(filename, mode); }

void osipf_CFclose(CFILE *file) { cfclose(file); }

int osipf_CFtell(CFILE *file) { return cftell(file); }

uint8_t osipf_CFeof(CFILE *file) { return (cfeof(file) != 0) ? 1 : 0; }

void osipf_SoundStop(int s_handle, bool f_immediately) {
  // JEFF - sorry, this can't be  made multiplayer friendly
  /*
  if(f_immediately)
          Sound_system.StopSoundImmediate(s_handle);
  else
          Sound_system.StopSoundLooping(s_handle);
  */
}

int osipf_SoundPlay2d(int obj_handle, int s_id, float volume) {
  msafe_struct mstruct;
  mstruct.index = s_id;

  if (obj_handle != OBJECT_HANDLE_NONE) {
    mstruct.state = 1;
    mstruct.objhandle = obj_handle;
  } else {
    mstruct.state = 0;
  }

  mstruct.volume = volume;

  msafe_CallFunction(MSAFE_SOUND_2D, &mstruct);
  return mstruct.sound_handle;
  /*
  //chrishack -- use handle for who hears the sound
  return Sound_system.Play2dSound(s_id, SND_PRIORITY_HIGHEST, volume);
  */
}

int osipf_SoundPlay3d(int obj_handle, int s_id, float volume) {
  msafe_struct mstruct;
  mstruct.objhandle = obj_handle;
  mstruct.index = s_id;

  msafe_CallFunction(MSAFE_SOUND_OBJECT, &mstruct);
  return mstruct.sound_handle;
  /*
  object *obj = ObjGet(obj_handle);

  if(obj)
  {
          return Sound_system.Play3dSound(s_id, SND_PRIORITY_HIGHEST,obj, volume);
  }

  return -1;
  */
}

int osipf_SoundFindId(const char *s_name) { return FindSoundName(IGNORE_TABLE(s_name)); }

bool osipf_AIIsObjFriend(int obj_handle, int it_handle) {
  object *me = ObjGet(obj_handle);
  object *it = ObjGet(it_handle);

  if (me && it)
    return AIObjFriend(me, it);

  return false;
}

bool osipf_AIIsObjEnemy(int obj_handle, int it_handle) {
  object *me = ObjGet(obj_handle);
  object *it = ObjGet(it_handle);

  if (me && it)
    return AIObjEnemy(me, it);

  return false;
}

void osipf_AIGoalValue(int obj_handle, char g_index, char op, char vtype, void *ptr, char index) {
  object *obj = ObjGet(obj_handle);
  if (!obj)
    return;

  ai_frame *ai_info = obj->ai_info;
  if (!ai_info)
    return;

  if (g_index < 0 || g_index >= MAX_GOALS)
    return;

  goal *g_ptr = &ai_info->goals[g_index];

  if (!g_ptr->used || vtype == AIGV_B_USED) {
    if (vtype == AIGV_B_USED && op == VF_GET)
      *(bool *)ptr = g_ptr->used;

    return;
  }

  switch (vtype) {
  case AIGV_I_TYPE: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->type;
    else if (op == VF_SET)
      g_ptr->type = *(int *)ptr;
  } break;
  case AIGV_C_ACTIVATION_LEVEL: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->activation_level;
    else if (op == VF_SET)
      g_ptr->activation_level = *(char *)ptr;
  } break;
  case AIGV_F_MIN_INFLUENCE: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->min_influence;
    else if (op == VF_SET)
      g_ptr->min_influence = *(float *)ptr;
  } break;
  case AIGV_F_MAX_INFLUENCE: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->max_influence;
    else if (op == VF_SET)
      g_ptr->max_influence = *(float *)ptr;
  } break;

  case AIGSV_F_INFLUENCE_DIST: // 0 - 3
  {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->ramp_influence_dists[index];
    else if (op == VF_SET)
      g_ptr->ramp_influence_dists[index] = *(float *)ptr;
  } break;

  case AIGV_I_HANDLE: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->g_info.handle;
    else if (op == VF_SET)
      g_ptr->g_info.handle = *(int *)ptr;
  } break;
  case AIGV_I_ROOMNUM: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->g_info.roomnum;
    else if (op == VF_SET)
      g_ptr->g_info.roomnum = *(int *)ptr;
  } break;
  case AIGV_I_F_ACTIONS: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->g_info.f_actions;
    else if (op == VF_SET)
      g_ptr->g_info.f_actions = *(int *)ptr;
  } break;
  case AIGV_I_ID: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->g_info.id;
    else if (op == VF_SET)
      g_ptr->g_info.id = *(int *)ptr;
  } break;
  case AIGV_C_SUBTYPE: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->subtype;
    else if (op == VF_SET)
      g_ptr->subtype = *(char *)ptr;
  } break;
  case AIGV_F_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->g_info.time;
    else if (op == VF_SET)
      g_ptr->g_info.time = *(float *)ptr;
  } break;
  case AIGV_V_VEC: {
    if (op == VF_GET)
      *(vector *)ptr = g_ptr->g_info.vec;
    else if (op == VF_SET)
      g_ptr->g_info.vec = *(vector *)ptr;
  } break;
  case AIGV_V_POS: {
    if (op == VF_GET)
      *(vector *)ptr = g_ptr->g_info.pos;
    else if (op == VF_SET)
      g_ptr->g_info.pos = *(vector *)ptr;
  } break;
  case AIGV_F_STEER_MIN_DIST: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->g_info.dist_info.min_dist;
    else if (op == VF_SET)
      g_ptr->g_info.dist_info.min_dist = *(float *)ptr;
  } break;
  case AIGV_F_STEER_MAX_DIST: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->g_info.dist_info.max_dist;
    else if (op == VF_SET)
      g_ptr->g_info.dist_info.max_dist = *(float *)ptr;
  } break;
  case AIGV_F_STEER_MAX_STRENGTH: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->g_info.dist_info.max_strength;
    else if (op == VF_SET)
      g_ptr->g_info.dist_info.max_strength = *(float *)ptr;
  } break;
  case AIGV_B_ATTACH_F_ALIGNED: {
    if (op == VF_GET)
      *(bool *)ptr = (g_ptr->g_info.attach_info.flags & GAF_ALIGNED) != 0;
  } break;
  case AIGV_B_ATTACH_F_SPHERE: {
    if (op == VF_GET)
      *(bool *)ptr = (g_ptr->g_info.attach_info.flags & GAF_SPHERE) != 0;
  } break;
  case AIGV_F_ATTACH_RAD: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->g_info.attach_info.rad;
  } break;
  case AIGV_C_ATTACH_CHILD_AP: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->g_info.attach_info.child_ap;
  } break;
  case AIGV_C_ATTACH_PARENT_AP: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->g_info.attach_info.parent_ap;
  } break;
  case AIGV_I_WANDER_AVOID_HANDLE: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->g_info.wander_extra_info.avoid_handle;
    else if (op == VF_SET)
      g_ptr->g_info.wander_extra_info.avoid_handle = *(int *)ptr;
  } break;
  case AIGV_C_WANDER_MIN_ROOMS: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->g_info.wander_extra_info.min_rooms;
    else if (op == VF_SET)
      g_ptr->g_info.wander_extra_info.min_rooms = *(char *)ptr;
  } break;
  case AIGV_C_WANDER_MAX_ROOMS: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->g_info.wander_extra_info.max_rooms;
    else if (op == VF_SET)
      g_ptr->g_info.wander_extra_info.max_rooms = *(char *)ptr;
  } break;
  case AIGV_C_WANDER_FLAGS: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->g_info.wander_extra_info.flags;
    else if (op == VF_SET)
      g_ptr->g_info.wander_extra_info.flags = *(char *)ptr;
    else if (op == VF_SET_FLAGS)
      g_ptr->g_info.wander_extra_info.flags |= *(char *)ptr;
    else if (op == VF_CLEAR_FLAGS)
      g_ptr->g_info.wander_extra_info.flags &= ~(*(char *)ptr);
  } break;
  case AIGV_C_WANDER_MINE_INDEX: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->g_info.wander_extra_info.mine_index;
    else if (op == VF_SET)
      g_ptr->g_info.wander_extra_info.mine_index = *(char *)ptr;
  } break;
  case AIGV_F_CIRCLE_DIST: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->circle_distance;
    else if (op == VF_SET)
      g_ptr->circle_distance = *(float *)ptr;
  } break;
  case AIGV_I_STATUS_REG: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->status_reg;
    else if (op == VF_SET)
      g_ptr->status_reg = *(int *)ptr;
    else if (op == VF_SET_FLAGS)
      g_ptr->status_reg |= *(int *)ptr;
    else if (op == VF_CLEAR_FLAGS)
      g_ptr->status_reg &= ~(*(int *)ptr);
  } break;
  case AIGV_F_START_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->start_time;
    else if (op == VF_SET)
      g_ptr->start_time = *(float *)ptr;
  } break;
  case AIGV_F_NEXT_PATH_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->next_path_time;
    else if (op == VF_SET)
      g_ptr->next_path_time = *(float *)ptr;
  } break;
  case AIGV_F_DIST_TO_GOAL: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->dist_to_goal;
    else if (op == VF_SET)
      g_ptr->dist_to_goal = *(float *)ptr;
  } break;
  case AIGV_I_SCRIPTED_DATA_PTR: {
	if(op == VF_GET)
	    *(void **)ptr = g_ptr->g_info.scripted_data_ptr;
	else if(op == VF_SET)
	    g_ptr->g_info.scripted_data_ptr = *((void **)ptr);
  } break;
  case AIGV_V_VEC_TO_TARGET: {
    if (op == VF_GET)
      *(vector *)ptr = g_ptr->vec_to_target;
    else if (op == VF_SET)
      g_ptr->vec_to_target = *(vector *)ptr;
  } break;
  case AIGV_F_NEXT_CHECK_SEE_TARGET_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->next_check_see_target_time;
    else if (op == VF_SET)
      g_ptr->next_check_see_target_time = *(float *)ptr;
  } break;
  case AIGV_V_LAST_SEE_TARGET_POS: {
    if (op == VF_GET)
      *(vector *)ptr = g_ptr->last_see_target_pos;
    else if (op == VF_SET)
      g_ptr->last_see_target_pos = *(vector *)ptr;
  } break;
  case AIGV_F_LAST_SEE_TARGET_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->last_see_target_time;
    else if (op == VF_SET)
      g_ptr->last_see_target_time = *(float *)ptr;
  } break;
  case AIGV_F_NEXT_TARGET_UPDATE_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->next_target_update_time;
    else if (op == VF_SET)
      g_ptr->next_target_update_time = *(float *)ptr;
  } break;
  case AIGV_I_FLAGS: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->flags;
    else if (op == VF_SET)
      g_ptr->flags = *(int *)ptr;
    else if (op == VF_SET_FLAGS)
      g_ptr->flags |= *(int *)ptr;
    else if (op == VF_CLEAR_FLAGS)
      g_ptr->flags &= ~(*(int *)ptr);
  } break;

  case AIGV_C_NUM_ENABLERS: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->num_enablers;
    else if (op == VF_SET)
      g_ptr->num_enablers = *(char *)ptr;
  } break;
  case AIGV_V_ORIENT_FVEC: {
    if (op == VF_GET)
      *(vector *)ptr = g_ptr->set_fvec;
    else if (op == VF_SET)
      g_ptr->set_fvec = *(vector *)ptr;
  } break;
  case AIGV_V_ORIENT_UVEC: {
    if (op == VF_GET)
      *(vector *)ptr = g_ptr->set_uvec;
    else if (op == VF_SET)
      g_ptr->set_uvec = *(vector *)ptr;
  } break;
  case AIGSV_C_ENABLER_TYPE: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->enabler[index].enabler_type;
    else if (op == VF_SET)
      g_ptr->enabler[index].enabler_type = *(char *)ptr;
  } break;
  case AIGSV_F_ENABLER_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->enabler[index].time;
    else if (op == VF_SET)
      g_ptr->enabler[index].time = *(float *)ptr;
  } break;
  case AIGSV_C_ENABLER_MTYPE: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->enabler[index].movement_type;
    else if (op == VF_SET)
      g_ptr->enabler[index].movement_type = *(char *)ptr;
  } break;
  case AIGSV_F_ENABLER_FLOAT_VALUE: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->enabler[index].float_value;
    else if (op == VF_SET)
      g_ptr->enabler[index].float_value = *(float *)ptr;
  } break;
  case AIGSV_I_ENABLER_FLAGS: {
    if (op == VF_GET)
      *(int *)ptr = g_ptr->enabler[index].flags;
    else if (op == VF_SET)
      g_ptr->enabler[index].flags = *(int *)ptr;
    else if (op == VF_SET_FLAGS)
      g_ptr->enabler[index].flags |= *(int *)ptr;
    else if (op == VF_CLEAR_FLAGS)
      g_ptr->enabler[index].flags &= ~(*(int *)ptr);
  } break;
  case AIGSV_F_ENABLER_DIST: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->enabler[index].dist;
    else if (op == VF_SET)
      g_ptr->enabler[index].dist = *(float *)ptr;
  } break;
  case AIGSV_F_ENABLER_PERCENT: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->enabler[index].percent_enable;
    else if (op == VF_SET)
      g_ptr->enabler[index].percent_enable = *(float *)ptr;
  } break;
  case AIGSV_F_ENABLER_CHECK_INTERVAL: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->enabler[index].check_interval;
    else if (op == VF_SET)
      g_ptr->enabler[index].check_interval = *(float *)ptr;
  } break;
  case AIGSV_F_ENABLER_LAST_CHECK_TIME: {
    if (op == VF_GET)
      *(float *)ptr = g_ptr->enabler[index].last_check_time;
    else if (op == VF_SET)
      g_ptr->enabler[index].last_check_time = *(float *)ptr;
  } break;
  case AIGSV_C_ENABLER_NEXT_ENABLER_OP: {
    if (op == VF_GET)
      *(char *)ptr = g_ptr->enabler[index].bool_next_enabler_op;
    else if (op == VF_SET)
      g_ptr->enabler[index].bool_next_enabler_op = *(char *)ptr;
  } break;
  }
}

int osipf_AIGetNearbyObjs(vector *pos, int init_roomnum, float rad, int *object_handle_list, int max_elements,
                          bool f_lightmap_only, bool f_only_players_and_ais, bool f_include_non_collide_objects,
                          bool f_stop_at_closed_doors) {
  int16_t *s_list;
  int num_close;
  int i;
  int count = 0;

  s_list = (int16_t *)mem_malloc(sizeof(int16_t) * max_elements);

  num_close = fvi_QuickDistObjectList(pos, init_roomnum, rad, s_list, max_elements, f_lightmap_only,
                                      f_only_players_and_ais, f_include_non_collide_objects, f_stop_at_closed_doors);
  ASSERT(num_close <= max_elements);
  for (i = 0; i < num_close; i++) {
    if (!(Objects[s_list[i]].flags & OF_DEAD) && Objects[s_list[i]].render_type != RT_NONE) {
      object_handle_list[count++] = Objects[s_list[i]].handle;
    }
  }

  mem_free(s_list);

  return count;
}

char osipf_AIGetCurGoalIndex(int obj_handle) {
  object *obj = ObjGet(obj_handle);

  if (obj && obj->ai_info) {
    goal *cur_goal = GoalGetCurrentGoal(obj);
    if (cur_goal) {
      return (cur_goal - obj->ai_info->goals);
    }
  }

  return -1;
}

int osipf_FindSoundName(const char *name) { return FindSoundName(IGNORE_TABLE(name)); }

int osipf_FindRoomName(const char *name) {
  for (int i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && Rooms[i].name) {
      if (!stricmp(name, Rooms[i].name))
        return i;
    }
  }
  return -1;
}

int osipf_FindTriggerName(const char *name) {
  for (int i = 0; i < Num_triggers; i++) {
    if (Triggers[i].name) {
      if (!stricmp(name, Triggers[i].name))
        return i;
    }
  }
  return -1;
}

int osipf_FindObjectName(const char *name) {
  for (int i = 0; i < MAX_OBJECTS; i++) {
    if (Objects[i].type != OBJ_NONE && Objects[i].name != NULL) {
      if (!stricmp(name, Objects[i].name))
        return Objects[i].handle;
    }
  }
  return OBJECT_HANDLE_NONE;
}

int osipf_GetTriggerRoom(int trigger_id) {
  if (trigger_id < 0 || trigger_id >= Num_triggers)
    return -1;

  return Triggers[trigger_id].roomnum;
}

int osipf_GetTriggerFace(int trigger_id) {
  if (trigger_id < 0 || trigger_id >= Num_triggers)
    return -1;

  return Triggers[trigger_id].facenum;
}

int osipf_FindDoorName(const char *name) {
  for (int i = 0; i <= MAX_OBJECTS; i++) {
    if (Objects[i].type == OBJ_DOOR && Objects[i].name && !stricmp(Objects[i].name, name)) {
      return Objects[i].handle;
    }
  }
  return OBJECT_HANDLE_NONE;
}

int osipf_FindTextureName(const char *name) { return FindTextureName(IGNORE_TABLE(name)); }

int osipf_FindMatcenName(const char *name) { return FindMatcenIndex(name); }

int osipf_FindPathName(const char *name) { return FindGamePathName(name); }

int osipf_FindLevelGoalName(const char *name) { return Level_goals.GoalFindId(name); }

void osipf_CreateRandomSparks(int num_sparks, vector *pos, int roomnum, int which_index, float force_scalar) {
  CreateRandomSparks(num_sparks, pos, roomnum, which_index, force_scalar);
}

// disable/enable ship
void osipf_EnableShip(char *ship_name, bool enable) {
  msafe_struct ms;
  strcpy(ms.name, ship_name);
  ms.state = enable;
  msafe_CallFunction(MSAFE_MISC_ENABLE_SHIP, &ms);
}

// is ship enabled
bool osipf_IsShipEnabled(char *ship_name) {
  msafe_struct ms;
  strcpy(ms.name, ship_name);
  msafe_GetValue(MSAFE_MISC_ENABLE_SHIP, &ms);
  return (bool)(ms.state != 0);
}

// turns the given player into AI mode or back to regular control mode
void osipf_SetPlayerControlMode(int pnum, bool set_to_ai) {
  ASSERT(pnum >= 0 && pnum < MAX_PLAYERS);
  if (pnum < 0 || pnum >= MAX_PLAYERS)
    return;

  if (set_to_ai) {
    if (pnum != Player_num)
      return; // only change it for ourselves

    PlayerSetControlToAI(pnum);
  } else {
    ResetPlayerControlType(pnum);
  }
}

// gets information about a path point
// pass NULL for parameters not needed.
//	pathid: path number
//	point: which path point
// returns true if operation was successful
bool osipf_PathGetInformation(int pathid, int point, vector *pos, int *room, matrix *orient) {
  if (pathid < 0 || pathid >= MAX_GAME_PATHS)
    return false;

  if (!GamePaths[pathid].used)
    return false;

  if (point < 0 || point >= GamePaths[pathid].num_nodes)
    return false;

  if (pos) {
    pos->x = GamePaths[pathid].pathnodes[point].pos.x;
    pos->y = GamePaths[pathid].pathnodes[point].pos.y;
    pos->z = GamePaths[pathid].pathnodes[point].pos.z;
  }

  if (room) {
    *room = GamePaths[pathid].pathnodes[point].roomnum;
  }

  if (orient) {
    vm_VectorToMatrix(orient, &GamePaths[pathid].pathnodes[point].fvec, &GamePaths[pathid].pathnodes[point].uvec, NULL);
  }

  return true;
}

void osipf_LGoalValue(char op, char vtype, void *ptr, int g_index, int i_index) {
  switch (vtype) {
  case LGV_I_STATUS: {
    if (op == VF_GET)
      Level_goals.LGStatus(LO_GET_SPECIFIED, (int *)ptr);
    else if (op == VF_SET_FLAGS)
      Level_goals.LGStatus(LO_SET_SPECIFIED, (int *)ptr);
    else if (op == VF_CLEAR_FLAGS)
      Level_goals.LGStatus(LO_CLEAR_SPECIFIED, (int *)ptr);
    else if (op == VF_SET) {
      int status;
      Level_goals.LGStatus(LO_GET_SPECIFIED, &status);

      int diff_flags = (*(int *)ptr) ^ status;
      int clear_flags = status & diff_flags;
      int set_flags = (~(status)) & diff_flags;

      if (clear_flags)
        Level_goals.LGStatus(LO_CLEAR_SPECIFIED, &clear_flags);
      if (set_flags)
        Level_goals.LGStatus(LO_SET_SPECIFIED, &set_flags);
    }
  } break;
  case LGV_I_NUM_ACTIVE_PRIMARIES: {
    if (op == VF_GET)
      *((int *)ptr) = Level_goals.GetNumActivePrimaryGoals();
  } break;
  case LGSV_I_ACTIVE_PRIMARY_GOAL: {
    if (op == VF_GET)
      *((int *)ptr) = Level_goals.GetActivePrimaryGoal(g_index);
  } break;
  case LGV_I_NUM_ACTIVE_SECONDARIES: {
    if (op == VF_GET)
      *((int *)ptr) = Level_goals.GetNumActiveSecondaryGoals();
  } break;
  case LGSV_I_ACTIVE_SECONDARY_GOAL: {
    if (op == VF_GET)
      *((int *)ptr) = Level_goals.GetActiveSecondaryGoal(g_index);
  } break;
  case LGV_I_NUM_GOALS: {
    if (op == VF_GET)
      *((int *)ptr) = Level_goals.GetNumGoals();
  } break;
  case LGSV_PC_GOAL_NAME: {
    if (op == VF_GET) {
      Level_goals.GoalGetName(g_index, (char *)ptr, 256); // chrishack - major demo hack
    } else if (op == VF_SET) {
      Level_goals.GoalSetName(g_index, (char *)ptr);
    }
  } break;
  case LGSV_PC_LOCATION_NAME: {
    if (op == VF_GET) {
      Level_goals.GoalGetItemName(g_index, (char *)ptr, 256); // chrishack - major demo hack
    } else if (op == VF_SET) {
      Level_goals.GoalSetItemName(g_index, (char *)ptr);
    }
  } break;
  case LGSV_PC_DESCRIPTION: {
    if (op == VF_GET) {
      Level_goals.GoalGetDesc(g_index, (char *)ptr, 256); // chrishack - major demo hack
    } else if (op == VF_SET) {
      Level_goals.GoalSetDesc(g_index, (char *)ptr);
    }
  } break;
  case LGSV_PC_COMPLETION_MESSAGE: {
    if (op == VF_GET) {
      Level_goals.GoalGetCompletionMessage(g_index, (char *)ptr, 256);
    } else if (op == VF_SET) {
      Level_goals.GoalSetCompletionMessage(g_index, (char *)ptr);
    }
  } break;
  case LGSV_I_PRIORITY: {
    if (op == VF_GET) {
      Level_goals.GoalPriority(g_index, LO_GET_SPECIFIED, (int *)&ptr);
    } else if (op == VF_SET) {
      Level_goals.GoalPriority(g_index, LO_SET_SPECIFIED, (int *)&ptr);
    }
  } break;
  case LGSV_C_GOAL_LIST: {
    if (op == VF_GET) {
      Level_goals.GoalGoalList(g_index, LO_GET_SPECIFIED, (char *)ptr);
    } else if (op == VF_SET) {
      Level_goals.GoalGoalList(g_index, LO_SET_SPECIFIED, (char *)ptr);
    }
  } break;
  case LGSV_I_STATUS: {
    if (op == VF_GET)
      Level_goals.GoalStatus(g_index, LO_GET_SPECIFIED, (int *)ptr);
    else if (op == VF_SET_FLAGS)
      Level_goals.GoalStatus(g_index, LO_SET_SPECIFIED, (int *)ptr);
    else if (op == VF_CLEAR_FLAGS)
      Level_goals.GoalStatus(g_index, LO_CLEAR_SPECIFIED, (int *)ptr);
    else if (op == VF_SET) {
      int status;
      Level_goals.GoalStatus(g_index, LO_GET_SPECIFIED, &status);

      int diff_flags = (*(int *)ptr) ^ status;
      int clear_flags = status & diff_flags;
      int set_flags = (~(status)) & diff_flags;

      if (clear_flags)
        Level_goals.GoalStatus(g_index, LO_CLEAR_SPECIFIED, &clear_flags);
      if (set_flags)
        Level_goals.GoalStatus(g_index, LO_SET_SPECIFIED, &set_flags);
    }
  } break;
  case LGSV_I_NUM_ITEMS: {
    if (op == VF_GET) {
      *((int *)ptr) = Level_goals.GoalGetNumItems(g_index);
    }
  } break;
  case LGSSV_C_ITEM_TYPE: {
    if (op == VF_GET) {
      Level_goals.GoalItemInfo(g_index, i_index, LO_GET_SPECIFIED, (char *)ptr, NULL, NULL);
    } else if (op == VF_SET) {
      Level_goals.GoalItemInfo(g_index, i_index, LO_SET_SPECIFIED, (char *)ptr, NULL, NULL);
    }
  } break;
  case LGSSV_I_ITEM_HANDLE: {
    if (op == VF_GET) {
      Level_goals.GoalItemInfo(g_index, i_index, LO_GET_SPECIFIED, NULL, (int *)ptr, NULL);
    } else if (op == VF_SET) {
      Level_goals.GoalItemInfo(g_index, i_index, LO_SET_SPECIFIED, NULL, (int *)ptr, NULL);
    }
  } break;
  case LGSSV_B_ITEM_DONE: {
    if (op == VF_GET) {
      Level_goals.GoalItemInfo(g_index, i_index, LO_GET_SPECIFIED, NULL, NULL, (bool *)ptr);
    } else if (op == VF_SET) {
      Level_goals.GoalItemInfo(g_index, i_index, LO_SET_SPECIFIED, NULL, NULL, (bool *)ptr);
    }
  } break;
  }
}

void osipf_ObjKill(int handle, int killer_handle, float damage, int flags, float min_time, float max_time) {
  object *obj = ObjGet(handle);
  object *killer = ObjGet(killer_handle);

  if (obj == NULL)
    return;

  if (obj->type == OBJ_PLAYER || obj->type == OBJ_GHOST || obj->type == OBJ_OBSERVER) {
    if (obj->type != OBJ_PLAYER) {
      Int3();
    }

    KillPlayer(obj, killer, damage, -1);
  } else if (IS_GENERIC(obj->type) || (obj->type == OBJ_DOOR)) {

    if (IS_GUIDEBOT(obj)) // Don't allow killing of the guidebot
      return;

    if (flags == -1) // no flags, so use default death
      KillObject(obj, killer, damage);
    else {
      float delay_time = min_time + (max_time - min_time) * ps_rand() / D3_RAND_MAX;
      KillObject(obj, killer, damage, flags, delay_time);
    }
  }
}

bool osipf_AIIsDestReachable(int handle, int room) {
  object *obj = ObjGet(handle);

  if (!obj)
    return false;

  return AIFindAltPath(obj, obj->roomnum, room);
}

bool osipf_AIIsObjReachable(int handle, int target_handle) {
  object *obj = ObjGet(handle);
  object *target = ObjGet(target_handle);

  if (!obj)
    return false;

  if (!target)
    return false;

  return AIFindAltPath(obj, obj->roomnum, target->roomnum);
}

char osipf_GameGetDiffLevel(void) { return DIFF_LEVEL; }

int osipf_GetLanguageSetting(void) {
  /*
  0:LANGUAGE_ENGLISH
  1:LANGUAGE_GERMAN
  2:LANGUAGE_SPANISH
  3:LANGUAGE_ITALIAN
  4:LANGUAGE_FRENCH
  */
  return Localization_GetLanguage();
}

// Sets/Gets information about a path.
// If you change is PV_ALL (or any of it's individual components), pass in a pointer to an
// osiris_path_node_info struct.  For the others, you must pass in an appropriate pointer
// (i.e. an int* for PV_I_NUMNODES).  You can only set PV_ALL components.
//	for PV_I_NUMNODES, path_id MUST be specified, node_id is ignored
//	for PV_I_NUMPATHS, path_id and node_id are ignored
//	for PV_CS_NAME, path_id MUST be specified, node_id is ignored
//	for PV_ALL components, path_id and node_id MUST be valid.
void osipf_PathValue(int path_id, int node_id, char op, int changes, void *ptr) {
  if (changes & PV_I_NUMPATHS) {
    *((int *)ptr) = Num_game_paths;
    return;
  }

  if (path_id < 0 || path_id >= Num_game_paths) {
    mprintf(0, "Invalid Path\n");
    Int3();
    return;
  }

  game_path *cpath = &GamePaths[path_id];

  ASSERT(cpath->used);
  if (!cpath->used)
    return;

  if (op == VF_GET) {
    if (changes & PV_ALL) {
      if (node_id < 0 || node_id >= cpath->num_nodes) {
        mprintf(0, "Invalid node on path\n");
        Int3();
        return;
      }

      node *cnode = &cpath->pathnodes[node_id];
      osiris_path_node_info *pni = (osiris_path_node_info *)ptr;

      if (changes & PV_POS) {
        pni->pos = cnode->pos;
      }
      if (changes & PV_ROOMNUM) {
        pni->roomnum = cnode->roomnum;
      }
      if (changes & PV_FLAGS) {
        pni->flags = cnode->flags;
      }
      if (changes & PV_FVEC) {
        pni->fvec = cnode->fvec;
      }
      if (changes & PV_UVEC) {
        pni->uvec = cnode->uvec;
      }

      changes &= ~PV_ALL;
      ASSERT(changes == 0); // no other changes allowed!!!!
      return;
    }

    if (changes == PV_I_NUMNODES) {
      *((int *)ptr) = cpath->num_nodes;
      return;
    }

    if (changes == PV_CS_NAME) {
      strcpy((char *)ptr, cpath->name);
      return;
    }

  } else if (op == VF_SET) {
    if (changes & PV_ALL) {
      if (node_id < 0 || node_id >= cpath->num_nodes) {
        mprintf(0, "Invalid node on path\n");
        Int3();
        return;
      }

      node *cnode = &cpath->pathnodes[node_id];
      osiris_path_node_info *pni = (osiris_path_node_info *)ptr;

      if (changes & PV_POS) {
        cnode->pos = pni->pos;
      }
      if (changes & PV_ROOMNUM) {
        cnode->roomnum = pni->roomnum;
      }
      if (changes & PV_FLAGS) {
        cnode->flags = pni->flags;
      }
      if (changes & PV_FVEC) {
        cnode->fvec = pni->fvec;
      }
      if (changes & PV_UVEC) {
        cnode->uvec = pni->uvec;
      }

      changes &= ~PV_ALL;
      ASSERT(changes == 0); // no other changes allowed!!!!
      return;
    }

  } else {
    Int3();
  }
}
