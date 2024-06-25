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

 * $Logfile: /DescentIII/main/AIGoal.cpp $
 * $Revision: 137 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * AI Goal Functions
 *
 * $Log: /DescentIII/main/AIGoal.cpp $
 *
 * 137   4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 136   3/20/00 12:02p Matt
 * Merge of Duane's post-1.3 changes.
 * Added check for bad wb index
 *
 * 135   10/23/99 2:43a Chris
 * Added the PutObjectOnObject AI Goal
 *
 * 134   10/21/99 2:17p Matt
 * Mac merge
 *
 * 133   10/08/99 4:31p Nate
 * Allow custom scripts to overide normal AI animation changes
 *
 * 132   7/27/99 4:16p Chris
 * Now dodge goals can get killed
 *
 * 131   5/23/99 12:34a Chris
 * Removed experimental code
 *
 * 130   5/22/99 3:36p Chris
 * Further bulletproof the path stuff
 *
 * 129   5/22/99 3:12p Chris
 *
 * 128   5/22/99 3:11p Chris
 * Fixed a bug in the wander code
 *
 * 127   5/21/99 7:46p Chris
 *
 * 126   5/21/99 7:22p Chris
 * Fixed bugs in wander code
 *
 * 125   5/20/99 1:15a Chris
 * Improved BNode Path Following for end points on the path.  Fixed bugs
 * with non-auto targetting
 *
 * 124   5/18/99 10:57a Chris
 * Various bug fixes
 *
 * 123   5/17/99 6:06p Chris
 * Adding robot debug code
 *
 * 122   5/09/99 8:11p Chris
 * Made the whole see/hear distintion work (mostly)
 *
 * 121   5/01/99 2:21a Chris
 * Use the GF_SPEED_XXX  stuff
 *
 * 120   4/28/99 5:33a Chris
 * Further improved the BNode system.  (It actually works inside and
 * outside now)
 *
 * 119   4/24/99 2:19a Chris
 * Fixed Tubbs and paths
 *
 * 118   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 117   4/20/99 8:55p Chris
 * Fixed problem with robots not being able to open locked doors that a
 * player has the key for.
 *
 * 116   4/18/99 5:38a Chris
 * Drastically improved the find_random_room function and added the
 * makenextroomlist function
 *
 * 115   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 114   4/09/99 10:33a Chris
 * Improvements to Freud
 *
 * 113   4/06/99 11:03p Chris
 * Added goal unique id's.  Improved FindRandomRoom (not so close to the
 * edge of the terrain)
 *
 * 112   4/06/99 11:18a Chris
 * Fixed a big bug in the attach system where object's properties where
 * not correctly reset after the attach
 *
 * 111   4/05/99 5:38p Chris
 * Fixed a bug where a wander_around goal could end up with a room 0 pos
 * 0,0,0 path when first init'ed
 *
 * 110   4/05/99 3:18p Chris
 * Patching wandering code
 *
 * 109   4/05/99 2:37p Chris
 * Stalkers are now wandering robots
 *
 * 108   3/31/99 12:50p Chris
 * Evader goal doesn't do avoid stuff for robots with a circle distance of
 * zero
 *
 * 107   3/30/99 4:32p Chris
 * Moved subtype to the main goal sturct (from goal_info).  Made move
 * relative object vec finishable.  (Like get behind player)
 *
 * 106   3/27/99 3:00p Chris
 * Fixed bug where high priority paths wouldn't reset the path if the
 * previously active path was a static path
 *
 * 105   3/27/99 12:29p Chris
 * Fixed problems with assigned lower priority goals that used paths (it
 * would confuse the bot because the .path field was getting updated for
 * the new goal even though it was lower priority)
 *
 * 104   3/23/99 11:51a Matt
 * Made wander code not crash if the room selected was an outside room
 * (from an inside wander)  I.e. two rooms in two different mines with
 * terrain between them.
 *
 * 103   3/22/99 5:47p Chris
 * Improved AI difficulties when a goal is being deleted and, in script, a
 * new goal uses that slot in middle of the delete code
 *
 * 102   3/22/99 10:58a Chris
 * Awareness code was tweaked.  Multisafe stuff added for objects.
 *
 * 101   3/17/99 5:23p Chris
 * Fixed problems with low-priority paths
 *
 * 100   3/17/99 12:25p Chris
 * Low priority paths
 *
 * 99    3/03/99 10:51a Chris
 * Got rid of goal_ptr
 *
 * 98    2/15/99 9:03p Chris
 * Added the base FOV off UVEC code and converted all the turrets
 *
 * 97    2/12/99 11:19a Chris
 * If a path doesn't exist, look for it next frame
 *
 * 96    2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 95    2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 94    2/02/99 3:52p Luke
 * Fixed a circular loop in the AINotify stuff
 *
 * 93    1/30/99 4:41p Luke
 * Make the guard goal work
 *
 * 92    1/26/99 2:51p Chris
 * AIG_WANDER improvements
 *
 * 91    1/25/99 8:16a Chris
 * Made sure the DALLAS is informed about code forced cleared goals that
 * have GUIDs.
 *
 * 90    1/25/99 7:43a Chris
 * Added the GUID (Goal Unique Id) and added the ability for weapon
 * batteries to always fire exactly forward.
 *
 * 89    1/24/99 8:17p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 88    1/22/99 6:53p Chris
 * Fixed LoadandBind Aux notify problems, fixed static path problems,
 * fixed AIF_FORCE_AWARE Problems, improved path code
 *
 * 87    1/20/99 1:01a Chris
 * Improved AI and OSIRIS intergration
 *
 * 86    1/18/99 8:07p Chris
 * Added the no-collide same flag (for flocks and nests)
 *
 * 85    1/18/99 9:05a Chris
 * Improved OSIRIS, AI, and ATTACH system, changed wiggle code, changed
 * attach code for rad attaches, and added the AIG_ATTACH_OBJ goal
 *
 * 84    1/15/99 5:54p Chris
 *
 * 83    1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 82    12/16/98 3:55p Chris
 * Improved the sickles
 *
 * 81    12/14/98 1:07p Chris
 * Allowed OSIRIS to change AI types
 *
 * 80    12/13/98 9:18p Chris
 * Improved influence values for in-code goals (10000 to 1.0).  Added
 * GF_ORIENT stuff.  :)
 *
 * 79    12/08/98 4:26p Chris
 * Fixed problems with same anim animations (both with .to of zero no
 * longer will do it)
 *
 * 78    12/03/98 5:45p Chris
 * I just added full code support for OSIRIS/DLL controlled goals,
 * enablers, and influence levels.  :)
 *
 * 77    12/03/98 12:24p Chris
 * Improved new anim code for instant updating
 *
 * 76    12/03/98 12:04p Chris
 * Added the instant mode switching for shared frame anims!
 *
 * 75    12/02/98 5:50p Chris
 * GoalDetermineTrackDist is more complete
 *
 * 74    12/01/98 6:17p Chris
 * Height bias is only for outside and GoalDetermineTrackDist is closer to
 * final
 *
 * 73    12/01/98 5:30p Chris
 *
 * 72    12/01/98 5:25p Chris
 * fixed switch statement for AIT_ init stuff
 *
 * 71    12/01/98 4:29p Chris
 * Checked in a massive amount of AI work.  Improved flocking code.  :)
 * (Still hacked lightly).  In addition, I am moving toward using the
 * composite dir.  :)
 *
 * 70    11/19/98 9:24p Chris
 *
 * 69    11/19/98 8:25p Chris
 * Starting to add generic team avoidance code
 *
 * 68    11/18/98 3:59p Chris
 * I added the avoid goal.  I also improved the AIs for Evader1 and
 * Evader2 by utilizing this goal when the target is well within the
 * circle distance.
 *
 * 67    11/11/98 6:31p Chris
 * AIF_DISABLE_FIRING and AIF_DISABLE_MELEE are now functional
 *
 * 66    11/06/98 11:39a Chris
 * Robots with flamethrowers and Omega cannons work in single player
 *
 * 65    10/22/98 7:55a Chris
 *
 * 64    10/22/98 7:07a Chris
 * Improved Evader2
 *
 * 63    10/21/98 7:33a Chris
 * Dead objects are not-targetable
 *
 * 62    10/20/98 11:58p Chris
 * AIGetToObj is not enabled when the target is NULL or OBJ_GHOST
 *
 * 61    10/13/98 1:08p Chris
 * Greatly improved the AI's use of paths.  Improved visability checking
 * algorithm.   Probably needs a second pass for further cleanup.
 *
 * 60    10/07/98 3:37p Chris
 * Improved the melee attack code
 *
 * 59    9/28/98 4:09p Chris
 * Added birth animations
 *
 * 58    9/17/98 11:11a Chris
 * Worked on goal system and improved integration with OSIRIS (better
 * EVT_AI_INIT event calling)
 *
 * 57    9/15/98 7:29p Chris
 * Improved OSIRIS and AI intergration
 *
 * 56    9/01/98 3:50p Chris
 *
 * 55    8/17/98 4:55p Chris
 * Added GF_FORCE_AWARENESS for goals
 *
 * 54    8/06/98 5:27p Chris
 * Fixed a bug when AIs regenerate their paths (they where not storing the
 * goal pos/room) with the AIGoalGetToPos goal.
 *
 * 53    6/29/98 5:34p Chris
 * Do general goal stuff before the currently active goal
 *
 * 52    6/29/98 5:03p Chris
 *
 * 51    6/29/98 4:36p Chris
 * Fixed a bug with melee robots
 *
 * 50    6/15/98 3:23p Chris
 * Single point walker update
 *
 * 49    5/22/98 6:45p Chris
 * Fixed a bug with flinching and melee attacks
 *
 * 48    5/22/98 6:22p Chris
 * Improved Dynamic path allocation
 *
 * 47    5/22/98 4:44p Chris
 * Added better melee hit prediction
 *
 * 46    5/20/98 10:19a Chris
 * Fixed some bugs with status_reg's and circle distance
 *
 * 45    5/18/98 12:40p Chris
 * Added a new flag (F_BLINE_IF_SEE_GOAL)
 *
 * 44    5/17/98 9:07p Chris
 * Fixed melee attacks.  Thanks to Ala.  :)
 *
 * 43    5/17/98 7:54p Chris
 * Correctly integrated the goal system and circle distance stuff.  Added
 * support for "target goals".
 *
 * 42    5/15/98 2:58p Chris
 * More on the big AI update
 *
 * 41    5/14/98 3:01p Chris
 * More new AI code
 *
 * 40    5/14/98 12:21p Chris
 * Updating AI system... Incomplete
 *
 * 39    5/12/98 3:46p Chris
 * Added some notify/goal system stuff and orientation to velocity
 *
 * 38    5/11/98 4:39p Chris
 * Improved AI system (goals have notifies and are more flexable).
 *
 * 37    5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 36    5/01/98 3:41p Chris
 *
 * 35    5/31/98 3:05p Chris
 * Allowed death anims (fixed problem with ctype union of CT_DEBRIS and
 * CT_AI)
 *
 * 34    4/30/98 11:31a Chris
 * Massive upgrades to the AI system
 *
 * 33    4/22/98 1:15p Chris
 * Incremental work on paths and goals
 *
 * 32    4/21/98 11:25a Chris
 * Improving GET_TO_OBJ goal
 *
 * 31    4/20/98 3:19p Chris
 * Added more goal/path support
 *
 * 30    4/20/98 12:27p Chris
 * Made AIG_GET_TO_OBJECT work.
 *
 * 29    4/19/98 9:56p Chris
 * AI system is integrated with OSIRIS.  Path system is integrated with
 * the AI system.  Bugs will ensue.
 *
 * 28    4/14/98 11:42a Chris
 * Added quirks and a better way of getting from idle to alert and from
 * alert to idle.
 *
 * 27    4/13/98 6:54p Chris
 * Improved the animation system.
 *
 * 26    4/13/98 2:20p Chris
 * IDLe works (kindof)
 *
 * 25    3/30/98 10:50a Chris
 * AI's will not go into fire if a flinch is lined up.
 *
 * 24    3/25/98 5:51p Chris
 * Added full model/body animations for weapon firing
 *
 * 23    3/25/98 11:02a Chris
 * version 1.0 of the new AI ranged firing code.
 *
 * 22    3/13/98 5:55p Chris
 * Fixed problems with animations
 *
 * 21    3/12/98 5:55p Chris
 * Updated flinch
 *
 * 20    3/12/98 5:51p Chris
 * Working on Bashing anim's to other anims
 *
 * 19    3/03/98 5:02p Chris
 * Added a status register to the ai_frame.  Also, I enabled a bunch of
 * the fields from the AI Dialog.  In addiition, I tweaked how melee
 * attacks work and animate.
 *
 * 18    2/16/98 12:52p Chris
 * Added some Flinch support
 *
 * 17    2/11/98 7:00p Chris
 * Removed priority (changed to influence) and added activation_level
 *
 * 16    2/02/98 8:14p Chris
 * Updated the AI system
 *
 * 15    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 14    1/14/98 7:57p Chris
 * Improving the awareness system
 *
 * 13    11/17/97 9:48p Chris
 * Added guarding
 *
 * 12    11/17/97 5:46p Chris
 * Added some support for a Theif-like robot
 *
 * 11    11/14/97 11:55p Chris
 * Dodge goals are semi-functional
 *
 * 10    9/02/97 3:28p Matt
 * Got rid of warnings
 *
 * 9     8/05/97 12:29p Chris
 *
 * 8     7/30/97 1:31p Chris
 * Made helicopters slightly more interesting.
 *
 * 7     7/29/97 12:20p Chris
 * Incremental improvements.  Fixed a memory bug.
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
 * $NoKeywords: $
 */

#include <stdlib.h>
#include "AIGoal.h"
#include "aistruct.h"
#include "aipath.h"
#include "object.h"
#include "game.h"
#include "terrain.h"
#include "objinfo.h"
#include "AIMain.h"
#include "room.h"
#include "psrand.h"
#include "BOA.h"
#include "findintersection.h"

extern int AI_unique_goal_id;

static void GoalInitWanderAround(object *obj, goal *goal_ptr);
static int GoalAllocSlot(object *obj, int level, float influence);

#define BASH_TO_ANIM_SCALER 10.0f
#define MAX_BASH_TO_FLINCH_TIME 2.5f

void GoalInitWanderAround(object *obj, goal *goal_ptr) {
  ai_frame *ai_info = obj->ai_info;
  int roomnum;
  vector pos;

  //	mprintf(0, "Wander around\n");

  goal *cur_goal = GoalGetCurrentGoal(obj);
  if (cur_goal != goal_ptr)
    return;

  if (!ROOMNUM_OUTSIDE(obj->roomnum)) {
    roomnum = AIFindRandomRoom(obj, ai_info, goal_ptr, obj->roomnum, -1, -1, true, false, NULL);
    if (!ROOMNUM_OUTSIDE(roomnum)) {
      pos = Rooms[roomnum].path_pnt;
    } else {
      ComputeTerrainSegmentCenter(&pos, CELLNUM(roomnum));
      pos.y += (ai_info->biased_flight_max + ai_info->biased_flight_min) / 2.0f;
    }
  } else {
    int tx = D3::RandomInt(56 / 2, TERRAIN_WIDTH - 56 / 2 - 1);
    int tz = D3::RandomInt(56 / 2, TERRAIN_DEPTH - 56 / 2 - 1);

    int cell = tx + TERRAIN_WIDTH * tz;
    roomnum = 0x80000000 | cell;
    ComputeTerrainSegmentCenter(&pos, cell);
    pos.y += (ai_info->biased_flight_max + ai_info->biased_flight_min) / 2.0f;
  }

  goal_ptr->g_info.pos = pos;
  goal_ptr->g_info.roomnum = roomnum;

  goal_ptr->next_path_time = Gametime + MIN_NEXT_PATH_INTERVAL + D3::RandomFloat();
  goal_ptr->flags |= GF_HAS_PATH;
}

void GoalClearGoal(object *obj, goal *cur_goal, int reason) {
  ai_frame *ai_info = obj->ai_info;
  bool f_continue = true;

  // Set the in clear flag so that we know if this goal is updated in script
  cur_goal->flags |= GF_IN_CLEAR;

  if (reason != AI_INVALID_INDEX) {
    int goal_index = (cur_goal - ai_info->goals);

    f_continue = AINotify(obj, reason, (void *)&goal_index);
  } else if (cur_goal->guid != -1 && reason != AI_INVALID_INDEX) {
    int goal_index = (cur_goal - ai_info->goals);
    AINotify(obj, AIN_GOAL_FAIL, (void *)&goal_index);
  }

  // Don't continue if this is a different goal
  if (!(cur_goal->flags & GF_IN_CLEAR))
    return;

  // Clear the in clear flag
  cur_goal->flags &= ~GF_IN_CLEAR;

  if ((reason == AIN_GOAL_COMPLETE) && (cur_goal->flags & GF_KEEP_AT_COMPLETION)) {
    if (cur_goal->type == AIG_WANDER_AROUND) {
      GoalInitWanderAround(obj, cur_goal);
    }
    return;
  }

  if ((cur_goal->flags & GF_NONFLUSHABLE) && (reason != AI_INVALID_INDEX))
    return;

  if (!f_continue)
    return;

  //	cur_goal->goal_type = AIG_NOT_USED;
  cur_goal->used = false;

  if (obj->ai_info->path.goal_uid == cur_goal->goal_uid) {
#ifdef _DEBUG
    if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
      mprintf(0, "AI Note: In free path\n");
    }
#endif
    AIPathFreePath(&ai_info->path);
  }

  //	for(i = 0; i < MAX_ENDERS_PER_GOAL; i++)
  //	{
  //		cur_goal->enders[i].ender_type = AIE_NOT_USED;
  //	}
}

#define MAX_NEAR_OBJ_SEARCH_DIST 200.0f

float GoalDetermineTrackDist(object *obj) {
  float dist = 0.0f;
  int i;

  for (i = 0; i < MAX_GOALS; i++) {
    goal *cur_goal = &obj->ai_info->goals[i];

    if (cur_goal->used && ISTRACKGOAL(cur_goal)) {
      if (cur_goal->flags & GF_RAMPED_INFLUENCE) {
        if (cur_goal->ramp_influence_dists[3] > dist) {
          // Get the maximum distance this goal has influence
          dist = cur_goal->ramp_influence_dists[3];
        }
      } else {
        // Influence isn't distnace based; so, check out to max dist
        dist = MAX_NEAR_OBJ_SEARCH_DIST;
      }
    }
  }

  if (dist > 0.0f)
    return dist + obj->size;
  else
    return 0.0f;
}

void GoalDoFrame(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  goal *cur_goal;
  int i;

  goal *cur_task_goal = GoalGetCurrentGoal(obj);
  if (ai_info->path.num_paths > 0 && (cur_task_goal == NULL || (cur_task_goal->goal_uid != ai_info->path.goal_uid))) {
#ifdef _DEBUG
    if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
      mprintf(0, "AI Note: In free path\n");
    }
#endif
    AIPathFreePath(&ai_info->path);
  }

  // Process all goals
  cur_goal = &ai_info->goals[0];
  for (i = 0; i < MAX_GOALS; i++) {
    if (cur_goal->used) {
      if ((cur_goal->flags & GF_CLEAR_IF_NOT_CURRENT_GOAL) && cur_goal != cur_task_goal) {
        GoalClearGoal(obj, cur_goal);
        continue;
      }

      // Does the
      if (cur_goal->flags & GF_OBJ_IS_TARGET) {
        cur_goal->g_info.handle = ai_info->target_handle;

        if (ai_info->status_reg & AISR_SEES_GOAL) {
          cur_goal->status_reg |= AISR_SEES_GOAL;
        } else {
          cur_goal->status_reg &= ~AISR_SEES_GOAL;
        }
      } else {
        // chrishack -- Currently, we can only see target based goals and position goals
        cur_goal->status_reg &= ~AISR_SEES_GOAL;
        if (POSGOAL(cur_goal) && cur_goal->g_info.roomnum == obj->roomnum) {
          cur_goal->status_reg |= AISR_SEES_GOAL;
        }
      }

      if (cur_goal->flags & GF_CIRCLE_OBJ) {
        int handle = cur_goal->g_info.handle;
        object *goal_obj = ObjGet(handle);

        if (cur_goal->flags & GF_OBJ_IS_TARGET) {
          cur_goal->dist_to_goal = ai_info->dist_to_target_actual;
        } else {
          if (goal_obj) {
            cur_goal->dist_to_goal = vm_VectorDistance(&obj->pos, &goal_obj->pos) - obj->size - goal_obj->size;
            if (cur_goal->dist_to_goal < 0.0f) {
              cur_goal->dist_to_goal = 0.0f;
            }
          }
        }

        if (goal_obj) {
          AIStatusCircleFrame(obj, goal_obj, cur_goal->dist_to_goal, cur_goal->circle_distance, &cur_goal->status_reg);
        } else {
          cur_goal->status_reg &= ~AISR_CIRCLE_DIST;
        }
      } else if (POSGOAL(cur_goal)) {
        float dist = vm_VectorDistance(&obj->pos, &cur_goal->g_info.pos);

        //				mprintf(0, "Dist is %f\n", dist);
        //				mprintf(0, "Dist %f, %f, %f\n", XYZ(&cur_goal->g_info.pos));
        //				mprintf(0, "Obj  %f, %f, %f\n", XYZ(&obj->pos));

        cur_goal->dist_to_goal = dist;
        AIStatusCircleFrame(obj, NULL, dist, cur_goal->circle_distance, &cur_goal->status_reg);
      }
    }

    cur_goal++;
  }

  // cur_task_goal might get cleared out above, so we should just recompute the current task goal
  cur_goal = GoalGetCurrentGoal(obj);

  if (cur_goal) {
    int handle = OBJECT_HANDLE_NONE;
    object *goal_obj = NULL;

    if (cur_goal->flags & GF_FORCE_AWARENESS) {
      if (obj->ai_info->awareness < AWARE_MOSTLY)
        obj->ai_info->awareness = AWARE_MOSTLY;
    }

    // Does the save and restore of path information for static paths (i.e. if the path_info is
    // taken away by a higher priority goal and then returned at a later time
    if (cur_goal->type == AIG_FOLLOW_PATH) {
      if (ai_info->path.goal_uid == cur_goal->goal_uid && ai_info->path.num_paths > 0) {
        cur_goal->g_info.static_path_info.cur_node = ai_info->path.cur_node;
        cur_goal->g_info.static_path_info.start_node = ai_info->path.path_start_node[0];
        cur_goal->g_info.static_path_info.end_node = ai_info->path.path_end_node[0];
      } else {
        AIPathSetAsStaticPath(obj, cur_goal, cur_goal->g_info.id, cur_goal->g_info.static_path_info.start_node,
                              cur_goal->g_info.static_path_info.end_node, cur_goal->g_info.static_path_info.cur_node);
      }
    }

    if (cur_goal->type == AIG_WANDER_AROUND) {
      if (!(cur_goal->flags & GF_HAS_PATH) || ai_info->path.num_paths == 0) {
        GoalInitWanderAround(obj, cur_goal);
      }
/*
      else if ((cur_goal->flags & GF_HAS_PATH) && ai_info->path.num_paths != 0) {
        vector *posp = &cur_goal->g_info.pos;
        float dist = vm_VectorDistance(
            &AIDynamicPath[ai_info->path.num_paths - 1].pos[ai_info->path.path_end_node[ai_info->path.num_paths - 1]],
            posp);

        if (dist > 5.0f) {
          mprintf(0, "In wander path case for obj %d - %s....\n", OBJNUM(obj), Object_info[obj->id].name);
          cur_goal->next_path_time = Gametime - 1.0f;
        }
      }
*/
    }

    if (OBJGOAL(cur_goal)) {
      handle = cur_goal->g_info.handle;
      goal_obj = ObjGet(handle);
    }

    // Automatically end
    if ((COMPLETEATOBJ(cur_goal)) && (goal_obj) && (cur_goal->status_reg & AISR_CIRCLE_DIST)) {
      GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
    } else if ((COMPLETEATPOS(cur_goal)) && (cur_goal->status_reg & AISR_CIRCLE_DIST)) {
      GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
    } else if ((Gametime > cur_goal->next_path_time || ai_info->path.num_paths == 0) &&
               (cur_goal->type != AIG_FOLLOW_PATH)) {
      bool f_make_path = false;
      int ignore_obj = -1;
      bool f_kill_goal = false;
      int kill_reason;

      vector *posp;
      int roomnum;

      if (OBJGOAL(cur_goal)) {
        if (goal_obj) {
          //				if(cur_goal->g_info.pos != goal_obj->pos)
          f_make_path = true;
          ignore_obj = OBJNUM(goal_obj);

          posp = &goal_obj->pos;
          roomnum = goal_obj->roomnum;

          float dist = vm_VectorDistance(
              &AIDynamicPath[ai_info->path.num_paths - 1].pos[ai_info->path.path_end_node[ai_info->path.num_paths - 1]],
              posp);

          if (dist < 5.0f && ai_info->path.num_paths != 0) {
            int obj_room = BOA_INDEX(obj->roomnum);
            int path_room = BOA_INDEX(AIDynamicPath[ai_info->path.cur_path].roomnum[ai_info->path.cur_node]);
            vector path_pos = AIDynamicPath[ai_info->path.cur_path].pos[ai_info->path.cur_node];

            if (obj_room != path_room) {
              fvi_query fq;
              fvi_info hit_info;

              fq.p0 = &obj->pos;
              fq.startroom = obj->roomnum;
              fq.p1 = &path_pos;
              fq.rad = obj->size / 4.0f;
              fq.thisobjnum = OBJNUM(obj);
              fq.ignore_obj_list = NULL;
              fq.flags = FQ_CHECK_OBJS | FQ_NO_RELINK | FQ_IGNORE_NON_LIGHTMAP_OBJECTS;

              if (fvi_FindIntersection(&fq, &hit_info) == HIT_NONE) {
                mprintf(0, "AI OBJ Path: No need to update the path for obj %d\n", OBJNUM(obj));
                f_make_path = false;
              }
            }
          }
        } else {
          kill_reason = AIN_GOAL_INVALID;
          f_kill_goal = true;
        }
      } else if (POSGOAL(cur_goal)) {
        f_make_path = true;

        posp = &cur_goal->g_info.pos;
        roomnum = cur_goal->g_info.roomnum;

        float dist = vm_VectorDistance(
            &AIDynamicPath[ai_info->path.num_paths - 1].pos[ai_info->path.path_end_node[ai_info->path.num_paths - 1]],
            posp);

        if (dist < 5.0f && ai_info->path.num_paths != 0) {
          int obj_room = BOA_INDEX(obj->roomnum);
          int path_room = BOA_INDEX(AIDynamicPath[ai_info->path.cur_path].roomnum[ai_info->path.cur_node]);
          vector path_pos = AIDynamicPath[ai_info->path.cur_path].pos[ai_info->path.cur_node];

          if (obj_room != path_room) {
            fvi_query fq;
            fvi_info hit_info;

            fq.p0 = &obj->pos;
            fq.startroom = obj->roomnum;
            fq.p1 = &path_pos;
            fq.rad = obj->size / 4.0f;
            fq.thisobjnum = OBJNUM(obj);
            fq.ignore_obj_list = NULL;
            fq.flags = FQ_CHECK_OBJS | FQ_NO_RELINK | FQ_IGNORE_NON_LIGHTMAP_OBJECTS;

            if (fvi_FindIntersection(&fq, &hit_info) == HIT_NONE) {
              mprintf(0, "AI POS Path: No need to update the path for obj %d\n", OBJNUM(obj));
              f_make_path = false;
            }
          }
        }
      }

      // If we are supposed to make it, do it.
      if (f_make_path) {
        AIPathAllocPath(obj, ai_info, cur_goal, &obj->roomnum, &obj->pos, &roomnum, posp, 0.0f, 0, obj->handle,
                        ignore_obj);
      }

      // Kill it or update the time
      if (f_kill_goal) {
        GoalClearGoal(obj, cur_goal, kill_reason);
      } else {
        //  Update time regardless of if we made the path (so dont don't do this every frame
        cur_goal->next_path_time = Gametime + MIN_NEXT_PATH_INTERVAL + D3::RandomFloat();
      }
    }
  }
}

void GoalPathComplete(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  goal *cur_goal = GoalGetCurrentGoal(obj);

  if (!cur_goal)
    return;

  if (COMPLETEATOBJ(cur_goal)) {
    int handle = cur_goal->g_info.handle;
    object *goal_obj = ObjGet(handle);

    if ((goal_obj) && (cur_goal->g_info.pos != goal_obj->pos)) {
      int ignore_obj = OBJNUM(goal_obj);

      if (AIPathAllocPath(obj, ai_info, cur_goal, &obj->roomnum, &obj->pos, &goal_obj->roomnum, &goal_obj->pos, 0.0f, 0,
                          obj->handle, ignore_obj)) {
        cur_goal->next_path_time = Gametime + MIN_NEXT_PATH_INTERVAL + D3::RandomFloat();
      }
    } else {
      GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
    }
  } else {
    GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
  }
}

void GoalClearAll(object *obj) {
  int i;
  ai_frame *ai_info = obj->ai_info;

  for (i = 0; i < MAX_GOALS; i++) {
    GoalClearGoal(obj, &ai_info->goals[i]);
  }
}

int GoalAllocSlot(object *obj, int level, float influence) {
  float lowest_influence_slot = -1.0;
  float lowest_influence = MAX_INFLUENCE + 1.0;
  int alloc_slot = AI_INVALID_INDEX;
  ai_frame *ai_info = obj->ai_info;
  int cur_slot;

  ASSERT((level >= 0 && level < NUM_ACTIVATION_LEVELS) || (level == ACTIVATION_BLEND_LEVEL));

  if (influence > MAX_INFLUENCE) {
    mprintf(0, "Goal added with too much influence -- bashing down\n");
    influence = MAX_INFLUENCE;
  } else if (influence < 0.0f) {
    mprintf(0, "Goal added with negative influence -- bashing to zero\n");
    influence = 0.0f;
  }

  if (level < NUM_ACTIVATION_LEVELS) {
    cur_slot = level;

    if (level < 0) {
      mprintf(0, "AI: Bashed an invalid activation level to zero\n");
      level = 0;
    }

    if (ai_info->goals[cur_slot].used) {
      if (!(ai_info->goals[cur_slot].flags & GF_NONFLUSHABLE))
        GoalClearGoal(obj, &ai_info->goals[cur_slot]);
      else
        cur_slot = AI_INVALID_INDEX;
    }
  } else {
    cur_slot = NUM_ACTIVATION_LEVELS;
    goal *cur_goal = &ai_info->goals[cur_slot];

    if (level != ACTIVATION_BLEND_LEVEL) {
      mprintf(0, "AI: Bashed an invalid activation blend level to blend level\n");
      level = ACTIVATION_BLEND_LEVEL;
    }

    while (cur_slot < MAX_GOALS && ai_info->goals[cur_slot].used == true) {

      if (!(cur_goal->used)) {
        lowest_influence_slot = cur_slot;
        lowest_influence = -1.0f;
      }

      if (cur_goal->influence < lowest_influence && !(cur_goal->flags & GF_NONFLUSHABLE)) {
        lowest_influence_slot = cur_slot;
        lowest_influence = cur_goal->influence;
      }

      cur_goal++;
      cur_slot++;
    }

    // If there are no free slots but the lowest influence goal has less than the new goal's
    // influence, kill the old goal
    if (cur_slot >= MAX_GOALS && lowest_influence < influence) {
      cur_slot = lowest_influence_slot;
      GoalClearGoal(obj, &ai_info->goals[cur_slot]);
    }
  }

  if (cur_slot < MAX_GOALS) {
    ai_info->goals[cur_slot].used = true;
  } else {
    cur_slot = AI_INVALID_INDEX;
  }

  return cur_slot;
}

// Adds a goal to the object
int GoalAddGoal(object *obj, uint32_t goal_type, void *arg_struct, int level, float influence, int f_goal, int guid,
                char subtype) {
  ai_frame *ai_info = obj->ai_info;
  int goal_index = AI_INVALID_INDEX;
  goal *goal_ptr = NULL;

  if (!(goal_type & (AIG_SET_ANIM | AIG_DO_MELEE_ANIM | AIG_FIRE_AT_OBJ))) {
    goal_index = GoalAllocSlot(obj, level, influence);
    if (goal_index == AI_INVALID_INDEX) {
      // mprintf(0, "WARNING: Object %d has too many goals\n", OBJNUM(obj));
      return AI_INVALID_INDEX;
    }

    goal_ptr = &ai_info->goals[goal_index];

    goal_ptr->type = goal_type;
    goal_ptr->influence = influence;
    goal_ptr->start_time = Gametime;
    goal_ptr->flags = f_goal;
    goal_ptr->status_reg = 0;
    goal_ptr->num_enablers = 0;
    goal_ptr->circle_distance = ai_info->circle_distance;
    goal_ptr->guid = guid;
    goal_ptr->creation_time = Gametime;
    goal_ptr->subtype = subtype;
    goal_ptr->goal_uid = AI_unique_goal_id++;
  }

  switch (goal_type) {
  case AIG_WANDER_AROUND: {
    goal_ptr->next_path_time = Gametime;
  } break;

  case AIG_SCRIPTED:
    goal_ptr->g_info.scripted_data_ptr = arg_struct;
    break;

  case AIG_DODGE_OBJ:
  case AIG_GET_AROUND_OBJ:
  case AIG_MOVE_RELATIVE_OBJ:
    goal_ptr->g_info.handle = *((int *)arg_struct);
    break;

  case AIG_MOVE_RELATIVE_OBJ_VEC:
    goal_ptr->g_info.handle = ((goal_info *)arg_struct)->handle;
    break;

  case AIG_GUARD_AREA:
    goal_ptr->g_info.roomnum = ((goal_info *)arg_struct)->roomnum;
    goal_ptr->g_info.pos = ((goal_info *)arg_struct)->pos;
    break;

  case AIG_PLACE_OBJ_ON_OBJ: {
    int handle = ((goal_info *)arg_struct)->handle;
    object *goal_obj = ObjGet(handle);

    goal_ptr->g_info.attach_info.flags = 0;

    if (goal_obj) {
      goal_ptr->g_info = *((goal_info *)arg_struct);
      goal_ptr->g_info.pos = goal_obj->pos;
      int ignore_obj = OBJNUM(goal_obj);

      if (AIPathAllocPath(obj, ai_info, &ai_info->goals[goal_index], &obj->roomnum, &obj->pos, &goal_obj->roomnum,
                          &goal_obj->pos, 0.0f, 0, obj->handle, ignore_obj)) {
        goal_ptr->next_path_time = Gametime + MIN_NEXT_PATH_INTERVAL + D3::RandomFloat();
      } else {
        goal_ptr->next_path_time = Gametime;
      }
    } else
      goal_ptr->g_info.handle = OBJECT_HANDLE_NONE;
  } break;

  case AIG_ATTACH_TO_OBJ: {
    int handle = ((goal_info *)arg_struct)->handle;
    object *goal_obj = ObjGet(handle);

    goal_ptr->g_info.attach_info.flags = 0;

    if (goal_obj) {
      goal_ptr->g_info = *((goal_info *)arg_struct);
      goal_ptr->g_info.pos = goal_obj->pos;
      int ignore_obj = OBJNUM(goal_obj);

      if (AIPathAllocPath(obj, ai_info, &ai_info->goals[goal_index], &obj->roomnum, &obj->pos, &goal_obj->roomnum,
                          &goal_obj->pos, 0.0f, 0, obj->handle, ignore_obj)) {
        goal_ptr->next_path_time = Gametime + MIN_NEXT_PATH_INTERVAL + D3::RandomFloat();
      } else {
        goal_ptr->next_path_time = Gametime;
      }
    } else
      goal_ptr->g_info.handle = OBJECT_HANDLE_NONE;
  } break;

  case AIG_GET_TO_OBJ: {
    int handle = *((int *)arg_struct);
    object *goal_obj = ObjGet(handle);

    if (goal_obj) {
      goal_ptr->g_info.handle = handle;
      goal_ptr->g_info.pos = goal_obj->pos;
    } else
      goal_ptr->g_info.handle = OBJECT_HANDLE_NONE;

    goal_ptr->next_path_time = Gametime;
  } break;

  case AIG_GET_TO_POS: {
    int roomnum = ((goal_info *)arg_struct)->roomnum;
    vector pos = ((goal_info *)arg_struct)->pos;

    goal_ptr->g_info.pos = pos;
    goal_ptr->g_info.roomnum = roomnum;

    goal_ptr->next_path_time = Gametime;
  } break;

  case AIG_FOLLOW_PATH: {
    path_information path_info = *((path_information *)arg_struct);

    goal_ptr->g_info.id = path_info.path_id;
    goal_ptr->g_info.static_path_info.cur_node = path_info.next_node;
    goal_ptr->g_info.static_path_info.start_node = path_info.start_node;
    goal_ptr->g_info.static_path_info.end_node = path_info.end_node;

    goal_ptr->next_path_time = Gametime;
  } break;

  case AIG_FIRE_AT_OBJ: {
    gi_fire *attack_info = (gi_fire *)arg_struct;
    if (attack_info->cur_wb > MAX_WBS_PER_OBJ) { // DAJ
      mprintf(2, "GoalAddGoal wb_index %d > MAX_WBS_PER_OBJ\n", attack_info->cur_wb);
      return 0;
    }
    if ((ai_info->animation_type == AS_ALERT && !(ai_info->next_animation_type == AS_FLINCH)) ||
        ai_info->animation_type == AS_RANGED_RECOIL) {
      ai_info->current_wb_firing = attack_info->cur_wb;
      obj->dynamic_wb[attack_info->cur_wb].wb_anim_mask = attack_info->cur_mask;

      obj->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;
      ai_info->next_animation_type = AS_RANGED_ATTACK;

      if (Object_info[obj->id].static_wb[attack_info->cur_wb].flags & (WBF_SPRAY | WBF_ON_OFF)) {
        ai_info->last_special_wb_firing = (char)attack_info->cur_wb;
      }

      return 0;
    } else if (ai_info->animation_type == AS_IDLE) {
      obj->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;
      ai_info->next_animation_type = AS_GOTO_ALERT_OFFSET + ai_info->movement_type;
    }
  } break;

  case AIG_DO_MELEE_ANIM: {
    gi_fire *attack_info = (gi_fire *)arg_struct;
    if ((ai_info->animation_type == AS_ALERT) || (ai_info->animation_type == AS_MELEE1 + 1) ||
        (ai_info->animation_type == AS_MELEE2 + 1)) {
      uint8_t m_num = attack_info->melee_number;
      char new_anim;

      if (m_num)
        new_anim = AS_MELEE1;
      else
        new_anim = AS_MELEE2;

      obj->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;
      ai_info->next_animation_type = new_anim;
      return 0;
    } else if (ai_info->animation_type == AS_IDLE) {
      obj->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;
      ai_info->next_animation_type = AS_GOTO_ALERT_OFFSET + ai_info->movement_type;
    }
  } break;

  case AIG_MELEE_TARGET:
    break;

  case AIG_SET_ANIM: {
    char new_anim = *((int *)arg_struct);
    polyobj_info *p_info = &obj->rtype.pobj_info;

    //			mprintf(0, "Anim Goal %d\n", new_anim);
    // Custom animations cannot be overriden
    if (ai_info->next_animation_type == AS_CUSTOM) {
      return -1;
    }

    if (new_anim >= 0 && new_anim < NUM_ANIMS_PER_CLASS) {
      if ((Object_info[obj->id].anim[ai_info->movement_type].elem[ai_info->animation_type].from ==
           Object_info[obj->id].anim[ai_info->movement_type].elem[new_anim].from) &&
          (Object_info[obj->id].anim[ai_info->movement_type].elem[ai_info->animation_type].to ==
           Object_info[obj->id].anim[ai_info->movement_type].elem[new_anim].to) &&
          (Object_info[obj->id].anim[ai_info->movement_type].elem[ai_info->animation_type].to) &&
          (Object_info[obj->id].anim[ai_info->movement_type].elem[new_anim].to)) {
        ai_info->next_animation_type = new_anim;
        AIUpdateAnim(obj);
        return 0;
      }
    }

    if (ai_info->animation_type == AS_ALERT) {
      if (new_anim == AS_FLINCH) // Get to flinch quickly
      {
        if (p_info->anim_end_frame != p_info->anim_start_frame) {
          float time_per_frame = p_info->anim_time / (p_info->anim_end_frame - p_info->anim_start_frame);
          float time_left = time_per_frame * (p_info->anim_end_frame - p_info->anim_frame);

          if (time_left > MAX_BASH_TO_FLINCH_TIME) {
            return -1;
          }
        }
        p_info->anim_time /= BASH_TO_ANIM_SCALER;
      } else if (new_anim == AS_TAUNT) {
        if (ai_info->next_animation_type != AI_INVALID_INDEX) {
          return -1;
        }
      } else if (new_anim == AS_IDLE) {
        new_anim = AS_GOTO_IDLE_OFFSET + ai_info->movement_type;

        if (Object_info[obj->id].anim[ai_info->movement_type].elem[new_anim].to == 0.0f) {
          return -1;
        }
      }

      obj->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;
      ai_info->next_animation_type = new_anim;
      return 0;
    } else if (ai_info->animation_type == AS_IDLE) {
      if ((new_anim == AS_ALERT) ||
          (new_anim == AS_QUIRK && Object_info[obj->id].anim[ai_info->movement_type].elem[new_anim].to != 0.0f)) {
        obj->rtype.pobj_info.anim_flags |= AIAF_NOTIFY;

        if (new_anim == AS_ALERT)
          ai_info->next_animation_type = AS_GOTO_ALERT_OFFSET + ai_info->movement_type;
        else
          ai_info->next_animation_type = new_anim;
      }
      return 0;
    } else if (ai_info->animation_type == AS_QUIRK || ai_info->animation_type == AS_BIRTH) {
      if (new_anim == AS_ALERT) {
        ai_info->next_animation_type = AS_GOTO_ALERT_OFFSET + ai_info->movement_type;
        return 0;
      }

      return -1;
    }
  } break;

  default:
    ASSERT(0);
    break;
  }

  // Do init. stuff
  if (goal_index != AI_INVALID_INDEX) {
    if (OBJGOAL(&ai_info->goals[goal_index])) {
      goal_ptr->flags |= GF_CIRCLE_OBJ;
    } else if (POSGOAL(&ai_info->goals[goal_index])) {
      goal_ptr->flags |= GF_CIRCLE_POS;
    }

    if (TARGETONLYGOAL(&ai_info->goals[goal_index])) {
      goal_ptr->flags |= GF_OBJ_IS_TARGET;
    }

    if (goal_ptr->flags & GF_OBJ_IS_TARGET) {
      goal_ptr->g_info.handle = ai_info->target_handle;
      if (ai_info->status_reg & AISR_CIRCLE_DIST) {
        goal_ptr->status_reg |= AISR_CIRCLE_DIST;
      } else {
        goal_ptr->status_reg &= ~AISR_CIRCLE_DIST;
      }

      goal_ptr->dist_to_goal = ai_info->dist_to_target_actual;
    }

    goal *cur_goal = GoalGetCurrentGoal(obj);
    if (cur_goal != NULL && cur_goal == goal_ptr) {
      if (cur_goal->flags & GF_FORCE_AWARENESS) {
        if (obj->ai_info->awareness < AWARE_MOSTLY)
          obj->ai_info->awareness = AWARE_MOSTLY;
      }
    }
  }

  return goal_index;
}

int GoalAddEnabler(object *obj, int goal_index, uint8_t enabler_type, void *arg_struct, float percent, float interval) {
  ai_frame *ai_info = obj->ai_info;
  goal_enabler *e_info;

  int enabler_index = ai_info->goals[goal_index].num_enablers;

  if (ai_info->goals[goal_index].num_enablers >= MAX_ENABLERS_PER_GOAL) {
    mprintf(0, "Object %d with goal %d has to many enablers\n", OBJNUM(obj), goal_index);
    return AI_INVALID_INDEX;
  }

  e_info = &ai_info->goals[goal_index].enabler[enabler_index];

  e_info->enabler_type = enabler_type;
  e_info->percent_enable = percent;
  e_info->check_interval = interval;
  e_info->last_check_time = Gametime;

  // Hmmm...  What about 2 seconds to be enabled????  I think it is possible --chrishack
  switch (enabler_type) {
  case (AIE_AI_STATUS_FLAG):
    e_info->flags = *((int *)arg_struct);
    break;
  case (AIE_NEAR):
  case (AIE_FAR):
    e_info->dist = *((float *)arg_struct);
    break;
  case (AIE_SCRIPTED):
    break;
  case (AIE_GT_AWARENESS):
  case (AIE_LTE_AWARENESS):
    e_info->awareness = *((float *)arg_struct);
    break;
  case (AIE_GT_LAST_SEE_TARGET_INTERVAL):
  case (AIE_LTE_LAST_SEE_TARGET_INTERVAL):
    e_info->time = *((float *)arg_struct);
    break;
  case (AIE_FEAR):
    e_info->float_value = *((float *)arg_struct);
    break;
  case (AIE_ANGRY):
    e_info->float_value = *((float *)arg_struct);
    break;
  case (AIE_CURIOUS):
    e_info->float_value = *((float *)arg_struct);
    break;
  case (AIE_FRUSTRATED):
    e_info->float_value = *((float *)arg_struct);
    break;
  case (AIE_DELAY_TIME):
    e_info->time = *((float *)arg_struct);
    break;
  case (AIE_CLEAR_TIME):
    e_info->time = *((float *)arg_struct);
    break;
  default:
    ASSERT(0);
    break;
  }

  ai_info->goals[goal_index].num_enablers++;

  return enabler_index;
}

void GoalInitTypeGoals(object *obj, int ai_type) {
  ai_frame *ai_info = obj->ai_info;
  float aware = AWARE_BARELY;
  float time = 25.0f;

  GoalClearAll(obj);

  // This goal has a proirity of 50.  Mabye I should split up intermediate goals
  // and long term goals.  -- Wander around within 2000 units of your starting
  // position (goal has priority of 100)  The AI type decides what to do with
  // a goal when it is done.
  switch (ai_type) {
  case AIT_STALKER: {
    int goal_room;

    goal_room = obj->roomnum;

    GoalAddGoal(obj, AIG_WANDER_AROUND, (void *)&goal_room, 1, 1.0f, GF_NONFLUSHABLE | GF_KEEP_AT_COMPLETION);
    //			GoalAddEnabler(obj, 1, AIE_GT_AWARENESS, (void *)&aware, 1.0, 0.0);
    //			GoalAddEnabler(obj, 1, AIE_LTE_LAST_SEE_TARGET_INTERVAL, (void *)&time, 1.0, 0.0);
  } break;

  case AIT_EVADER2: {
    goal_info g_info;

    g_info.roomnum = obj->roomnum;
    g_info.pos = obj->pos;

    GoalAddGoal(obj, AIG_GUARD_AREA, (void *)&g_info, 1, 1.0f, GF_NONFLUSHABLE);
    obj->ai_info->goals[1].circle_distance = obj->size * 2.0f;
    GoalAddEnabler(obj, 1, AIE_GT_AWARENESS, (void *)&aware, 1.0, 0.0);
    GoalAddEnabler(obj, 1, AIE_LTE_LAST_SEE_TARGET_INTERVAL, (void *)&time, 1.0, 0.0);

    int handle = OBJECT_HANDLE_NONE;

    int gi = GoalAddGoal(obj, AIG_GET_AROUND_OBJ, (void *)&handle, ACTIVATION_BLEND_LEVEL, 3.0f,
                         GF_NONFLUSHABLE | GF_OBJ_IS_TARGET);
    if (gi != -1) { // DAJ -1FIX
      float temp = ai_info->circle_distance;
      GoalAddEnabler(obj, gi, AIE_NEAR, (void *)&temp, 1.0, 0.0);
      ai_info->goals[gi].circle_distance = ai_info->circle_distance;
    }
  } break;

  case AIT_EVADER1: {
    goal_info g_info;
    g_info.handle = ai_info->target_handle;

    GoalAddGoal(obj, AIG_MOVE_RELATIVE_OBJ, (void *)&g_info, 1, 1.0f, GF_SPEED_ATTACK | GF_NONFLUSHABLE);
    GoalAddEnabler(obj, 1, AIE_GT_AWARENESS, (void *)&aware, 1.0, 0.0);
    GoalAddEnabler(obj, 1, AIE_LTE_LAST_SEE_TARGET_INTERVAL, (void *)&time, 1.0, 0.0);
    ai_info->goals[1].flags |= GF_OBJ_IS_TARGET;

    if (ai_info->circle_distance > 0.0f) {
      int handle = OBJECT_HANDLE_NONE;
      int gi = GoalAddGoal(obj, AIG_GET_AROUND_OBJ, (void *)&handle, ACTIVATION_BLEND_LEVEL, 3.0f,
                           GF_NONFLUSHABLE | GF_OBJ_IS_TARGET);
      if (gi != -1) { // DAJ -1FIX
        float temp = ai_info->circle_distance * 0.55f;
        GoalAddEnabler(obj, gi, AIE_NEAR, (void *)&temp, 1.0, 0.0);
        ai_info->goals[gi].circle_distance = ai_info->circle_distance * 0.55f;
      }
    }
  } break;

  case AIT_MELEE1: {
    goal_info g_info;
    int flags = AISR_MELEE;
    int m_goal;

    g_info.handle = ai_info->target_handle;

    GoalAddGoal(obj, AIG_MOVE_RELATIVE_OBJ, (void *)&g_info, 1, 1.0f,
                GF_NONFLUSHABLE | GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION);
    GoalAddEnabler(obj, 1, AIE_GT_AWARENESS, (void *)&aware, 1.0, 0.0);
    GoalAddEnabler(obj, 1, AIE_LTE_LAST_SEE_TARGET_INTERVAL, (void *)&time, 1.0, 0.0);

    GoalAddGoal(obj, AIG_GET_TO_OBJ, (void *)&ai_info->target_handle, 2, 1.0f,
                GF_SPEED_ATTACK | GF_NONFLUSHABLE | GF_OBJ_IS_TARGET | GF_USE_BLINE_IF_SEES_GOAL |
                    GF_KEEP_AT_COMPLETION);
    GoalAddEnabler(obj, 2, AIE_AI_STATUS_FLAG, (void *)&flags, 1.0, 0.0);
    ai_info->goals[2].circle_distance = -100.0f;
    GoalAddEnabler(obj, 2, AIE_GT_AWARENESS, (void *)&aware, 1.0, 0.0);
    GoalAddEnabler(obj, 2, AIE_LTE_LAST_SEE_TARGET_INTERVAL, (void *)&time, 1.0, 0.0);

    m_goal = GoalAddGoal(obj, AIG_MELEE_TARGET, NULL, ACTIVATION_BLEND_LEVEL, 1.0f, GF_NONFLUSHABLE);
    if (m_goal != -1) { // DAJ -1FIX
      ai_info->goals[m_goal].flags |= GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION;
      GoalAddEnabler(obj, m_goal, AIE_GT_AWARENESS, (void *)&aware, 1.0, 0.0);
      GoalAddEnabler(obj, m_goal, AIE_LTE_LAST_SEE_TARGET_INTERVAL, (void *)&time, 1.0, 0.0);
    }
  } break;

  case AIT_BIRD_FLOCK1: {
  } break;

  case AIT_HERD1: {
  } break;

  case AIT_STATIONARY_TURRET:
    break;

  case AIT_AIS:
    break;

  case AIT_FLYLANDER:
    break;

  default: {
    Int3();
  }
  }
}

bool GoalIsGoalEnabled(object *obj, int goal_index) {
  ai_frame *ai_info = obj->ai_info;
  goal *cur_goal = &ai_info->goals[goal_index];
  bool f_enabled = true;
  int i;
  goal_enabler *e_info = &cur_goal->enabler[0];

  ASSERT(goal_index >= 0 && goal_index < MAX_GOALS);

  if (OBJGOAL(cur_goal)) {
    object *gobj = NULL;

    if (cur_goal->flags & GF_OBJ_IS_TARGET) {
      gobj = ObjGet(obj->ai_info->target_handle);
    } else if (cur_goal->flags & (GF_OBJS_ARE_SPECIES | GF_OBJS_ARE_ENEMIES | GF_OBJS_ARE_FRIENDS)) {
      bool done = false;

      if (cur_goal->flags & (GF_OBJS_ARE_SPECIES | GF_OBJS_ARE_FRIENDS)) {
        // chrishack -- not done
      }
    } else {
      gobj = ObjGet(cur_goal->g_info.handle);
    }

    if (gobj == NULL && cur_goal->type == AIG_DODGE_OBJ)
      return true;

    if (!gobj || gobj->type == OBJ_GHOST || (gobj->flags & (OF_DYING | OF_DESTROYED)) ||
        (gobj->type == OBJ_PLAYER && Players[gobj->id].flags & (PLAYER_FLAGS_DEAD + PLAYER_FLAGS_DYING))) {
      return false;
    }
  }

  if (cur_goal->type == AIG_MELEE_TARGET) {
    if (ai_info->flags & AIF_DISABLE_MELEE) {
      return false;
    }
  }

  if (cur_goal->num_enablers == 0) {
    return true;
  }

  for (i = 0; i < cur_goal->num_enablers; i++) {
    // Hmmm...  What about 2 seconds to be enabled????  I think it is possible --chrishack
    switch (e_info->enabler_type) {
    case (AIE_AI_STATUS_FLAG):
      f_enabled = ((e_info->flags) & (ai_info->status_reg)) != 0;
      break;

    case (AIE_NEAR): {
      float a_dist = e_info->dist;
      f_enabled = (cur_goal->dist_to_goal <= a_dist) != 0;
    } break;
    case (AIE_FAR): {
      float a_dist = e_info->dist;
      f_enabled = (cur_goal->dist_to_goal >= a_dist) != 0;
    } break;
    case (AIE_SCRIPTED): {
      notify se_info;
      se_info.goal_num = goal_index;
      se_info.enabler_num = i;

      f_enabled = AINotify(obj, AIN_SCRIPTED_ENABLER, &se_info);
    } break;
    case (AIE_GT_AWARENESS): {
      f_enabled = (ai_info->awareness > e_info->awareness);
    } break;
    case (AIE_LTE_AWARENESS): {
      f_enabled = (ai_info->awareness <= e_info->awareness);
    } break;
    case (AIE_LTE_LAST_SEE_TARGET_INTERVAL): {
      f_enabled = (Gametime - ai_info->last_see_target_time <= e_info->time) ||
                  (Gametime - ai_info->last_hear_target_time <= e_info->time);
    } break;
    case (AIE_GT_LAST_SEE_TARGET_INTERVAL): {
      f_enabled = (Gametime - ai_info->last_see_target_time > e_info->time) ||
                  (Gametime - ai_info->last_hear_target_time > e_info->time);
    } break;
    case (AIE_FEAR): {
      f_enabled = e_info->float_value <= ai_info->cur_life_preservation;
    } break;
    case (AIE_ANGRY): {
      f_enabled = e_info->float_value <= ai_info->cur_agression;
    } break;
    case (AIE_CURIOUS): {
      f_enabled = e_info->float_value <= ai_info->cur_curiousity;
    } break;
    case (AIE_FRUSTRATED): {
      f_enabled = e_info->float_value <= ai_info->cur_frustration;
    } break;
    case (AIE_DELAY_TIME): {
      f_enabled = e_info->time < Gametime - cur_goal->creation_time;
    } break;
    case (AIE_CLEAR_TIME): {
      f_enabled = e_info->time >= Gametime - cur_goal->creation_time;
      if (!f_enabled) {
        GoalClearGoal(obj, cur_goal);
      }
    } break;
    default:
      ASSERT(0);
      break;
    }

    // We are currently and'ing enablers
    if (f_enabled == false)
      break;

    e_info++;
  }

  return f_enabled;
}

goal *GoalGetCurrentGoal(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  int i;
  goal *cur_goal = NULL;

  for (i = NUM_ACTIVATION_LEVELS - 1; i >= 0; i--) {
    if (ai_info->goals[i].used && GoalIsGoalEnabled(obj, i)) {
      cur_goal = &ai_info->goals[i];
      break;
    }
  }

  return cur_goal;
}
