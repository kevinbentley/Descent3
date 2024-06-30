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

 * $Logfile: /DescentIII/main/AIMain.h $
 * $Revision: 41 $
 * $Date: 5/17/99 6:06p $
 * $Author: Chris $
 *
 * General AI functions for use in Descent III
 *
 * $Log: /DescentIII/main/AIMain.h $
 *
 * 41    5/17/99 6:06p Chris
 * Adding robot debug code
 *
 * 40    5/08/99 4:42p Chris
 *
 * 39    5/08/99 4:12p Chris
 * Added AI hearing noises... version 1
 *
 * 38    5/01/99 2:21a Chris
 * Use the GF_SPEED_XXX  stuff
 *
 * 37    4/18/99 5:38a Chris
 * Drastically improved the find_random_room function and added the
 * makenextroomlist function
 *
 * 36    3/12/99 12:16p Chris
 * Blending primary and blend goals!!!!!!  Awesome.
 *
 * 35    2/28/99 11:30p Chris
 * FindObjOfType and OSIRIS controllable deaths
 *
 * 34    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 33    1/29/99 5:10p Chris
 * Added an optional parent handle check for FindObjOfType
 *
 * 32    1/20/99 1:01a Chris
 * Improved AI and OSIRIS intergration
 *
 * 31    1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 30    12/15/98 6:05p Chris
 * Improved the path system
 *
 * 29    12/15/98 4:34p Chris
 *
 * 28    12/03/98 12:24p Chris
 * Improved new anim code for instant updating
 *
 * 27    12/01/98 4:31p Chris
 * Checked in a massive amount of AI work.  Improved flocking code.  :)
 * (Still hacked lightly).  In addition, I am moving toward using the
 * composite dir.  :)
 *
 * 26    10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 25    10/13/98 1:08p Chris
 * Greatly improved the AI's use of paths.  Improved visability checking
 * algorithm.   Probably needs a second pass for further cleanup.
 *
 * 24    10/06/98 6:19p Chris
 * Improved OSIRIS/AI intergration
 *
 * 23    9/28/98 4:09p Chris
 * Added birth animations
 *
 * 22    9/14/98 12:16p Chris
 * Vastly improved the multiplayer code
 *
 * 21    8/19/98 12:10p Chris
 * Improved coop behavior
 *
 * 20    8/10/98 12:16p Chris
 * Added AI_NumHostileAlert
 *
 * 19    6/30/98 6:36p Chris
 * Added rev .1 of multiplayer animations - BTW  It is totally not done.
 *
 * 18    5/17/98 7:54p Chris
 * Correctly integrated the goal system and circle distance stuff.  Added
 * support for "target goals".
 *
 * 17    5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 16    4/30/98 11:31a Chris
 * Massive upgrades to the AI system
 *
 * 15    4/16/98 2:56p Chris
 * Updated buddy support and intergrated scripting and AI
 *
 * 14    4/07/98 4:25p Chris
 * Added support for buddy bot
 *
 * 13    3/31/98 4:23p Chris
 * Added a new AIpath system
 *
 * 12    3/10/98 12:51p Chris
 * Added a truely D2 style homing missile
 *
 * 11    2/06/98 5:51p Chris
 * Added the ability turn robots on and off
 *
 * 10    1/29/98 3:29p Chris
 * Major update to the AI system.
 *
 * 9     11/14/97 11:55p Chris
 * Dodge goals are semi-functional
 *
 * 8     11/12/97 5:47p Chris
 * Incremental improvements
 *
 * 7     11/12/97 10:43a Chris
 * Incremental
 *
 * 6     8/05/97 12:17p Chris
 *
 * 5     7/15/97 7:29p Chris
 * Added a sound for helicopter blades.
 *
 * 4     7/15/97 5:35p Chris
 * New AI code
 *
 * 3     7/15/97 4:59p Chris
 * added support for AI and animations
 *
 * $NoKeywords: $
 */

#ifndef AIMAIN_H_
#define AIMAIN_H_

#include "object.h"
#include "player.h"

#define AI_SOUND_SHORT_DIST 60.0f

extern int AI_NumRendered;
extern std::array<int, MAX_OBJECTS> AI_RenderedList;

extern int AI_NumHostileAlert; // A rough number of alert/hostile robots
                               // that have seen the player recently
#ifdef _DEBUG
extern bool AI_debug_robot_do;
extern int AI_debug_robot_index;
#endif

// Is my buddy in the level? (no if the handle is invalid)
extern int Buddy_handle[MAX_PLAYERS];

bool AINotify(object *obj, uint8_t notify_type, void *info = NULL);
void AIDoFrame(object *obj);
void AIFrameAll(void);
bool AIInit(object *obj, uint8_t ai_class, uint8_t ai_type, uint8_t ai_movement);
void AIInitAll(void);
void AIPowerSwitch(object *obj, bool f_on);
void AITurnTowardsDir(object *obj, /*velocity *new_vel,*/ vector *goal_dir /*, bool remain_level*/, float turn_rate);
void AIMoveTowardsDir(object *obj, vector *dir, float scale = 1.0f);
bool AIMoveTowardsPosition(object *obj, /*velocity *new_vel,*/ vector *pos, float scale, bool stop_at_end_point,
                           vector *mdir, bool *f_moved);
void AITurnTowardsPosition(object *obj, /*velocity *new_vel,*/ vector *pos /*, bool remain_level*/);
bool AIFindHidePos(object *hide_obj, object *view_obj, vector *hpos, int *hroom, float max_hide_time = 3.0f);
int AIFindRoomWithFlag(object *obj, int flag);
object *AIFindObjOfType(object *obj, int type, int id, bool f_ignore_init_room, int parent_handle = OBJECT_HANDLE_NONE);
float AIFindDist(vector *s_pos, int s_roomnum, vector *e_pos, int e_roomnum, int flags);
bool AIStatusCircleFrame(object *obj, object *g_obj, float dist, float c_dist, int *status_reg);
bool AIObjEnemy(object *obj, object *target);
bool AISetTarget(object *obj, int handle);
void AIDestroyObj(object *obj);
bool AIObjFriend(object *obj, object *target);
void AIUpdateAnim(object *obj);
bool AITurnTowardsMatrix(object *obj, float turn_rate, matrix *g_orient);
int AIFindRandomRoom(object *obj, ai_frame *ai_info, goal *goal_ptr, int avoid_room, int min_depth, int max_depth,
                     bool f_check_path, bool f_cur_room_ok, int *depth);
int AIMakeNextRoomList(int roomnum, int *next_rooms, int max_rooms);

#endif
