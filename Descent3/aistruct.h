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

 * $Logfile: /DescentIII/main/aistruct.h $
 * $Revision: 112 $
 * $Date: 10/23/99 2:43a $
 * $Author: Chris $
 *
 * This header is for AI structures
 *
 * $Log: /DescentIII/main/aistruct.h $
 *
 * 112   10/23/99 2:43a Chris
 * Added the PutObjectOnObject AI Goal
 *
 * 111   5/09/99 8:11p Chris
 * Made the whole see/hear distintion work (mostly)
 *
 * 110   5/08/99 4:12p Chris
 * Added AI hearing noises... version 1
 *
 * 109   4/10/99 6:39p Matt
 * Only save the designer-editable AI data in the Object_info array,
 * instead of the whole ai_frame structure.  This saves 3200 bytes per
 * Object_info entry, which is about 2 MB overall.
 *
 * 108   4/09/99 10:33a Chris
 * Improvements to Freud
 *
 * 107   4/08/99 3:35p Chris
 * Improved the Fear factor in Freud
 *
 * 106   4/06/99 11:05p Chris
 * Goal unique id's
 *
 * 105   4/02/99 10:18a Chris
 * We can now mess with the Object_info anim stuff
 *
 * 104   3/30/99 4:32p Chris
 * Moved subtype to the main goal sturct (from goal_info).  Made move
 * relative object vec finishable.  (Like get behind player)
 *
 * 103   3/27/99 12:29p Chris
 * Fixed problems with assigned lower priority goals that used paths (it
 * would confuse the bot because the .path field was getting updated for
 * the new goal even though it was lower priority)
 *
 * 102   3/22/99 10:58a Chris
 * Awareness code was tweaked.  Multisafe stuff added for objects.
 *
 * 101   3/17/99 5:23p Chris
 * Fixed problems with low-priority paths
 *
 * 100   3/03/99 7:20p Jeff
 * save/restore some ai path information
 *
 * 99    3/03/99 10:51a Chris
 * Got rid of goal_ptr
 *
 * 98    2/17/99 1:21a Chris
 * Updated the AI movement algorithm, fixed many bugs, added the
 * last_dodge_dir vector so that robots can dodge the vauss and the like
 *
 * 97    2/15/99 9:03p Chris
 * Added the base FOV off UVEC code and converted all the turrets
 *
 * 96    2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 95    1/25/99 7:43a Chris
 * Added the GUID (Goal Unique Id) and added the ability for weapon
 * batteries to always fire exactly forward.
 *
 * 94    1/24/99 8:17p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 93    1/22/99 6:53p Chris
 * Fixed LoadandBind Aux notify problems, fixed static path problems,
 * fixed AIF_FORCE_AWARE Problems, improved path code
 *
 * 92    1/18/99 9:05a Chris
 * Improved OSIRIS, AI, and ATTACH system, changed wiggle code, changed
 * attach code for rad attaches, and added the AIG_ATTACH_OBJ goal
 *
 * 91    1/15/99 5:58p Chris
 *
 * 90    1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 89    12/28/98 3:28p Chris
 * Added aistruct_external.h
 *
 * 88    12/16/98 3:55p Chris
 * Improved the sickles
 *
 * 87    12/14/98 12:03a Chris
 * Turning and orientation are done in one (minus a few hacks) spot
 *
 * 86    12/13/98 9:18p Chris
 * Improved influence values for in-code goals (10000 to 1.0).  Added
 * GF_ORIENT stuff.  :)
 *
 * 85    12/11/98 1:57p Chris
 * Improved wall walking code
 *
 * 84    12/03/98 5:45p Chris
 * I just added full code support for OSIRIS/DLL controlled goals,
 * enablers, and influence levels.  :)
 *
 * 83    12/03/98 12:04p Chris
 * Further de-hacked flocking and other major AI systems
 *
 * 82    12/02/98 5:51p Chris
 * Added the start of scripted goals and scripted influence
 *
 * 81    12/01/98 6:04p Chris
 * Made the goal flags look like a short (as the data element is a short)
 *
 * 80    12/01/98 4:31p Chris
 * Checked in a massive amount of AI work.  Improved flocking code.  :)
 * (Still hacked lightly).  In addition, I am moving toward using the
 * composite dir.  :)
 *
 * 79    11/19/98 8:26p Chris
 * Starting to add generic team avoidance code
 *
 * 78    11/18/98 3:59p Chris
 * I added the avoid goal.  I also improved the AIs for Evader1 and
 * Evader2 by utilizing this goal when the target is well within the
 * circle distance.
 *
 * 77    11/11/98 6:31p Chris
 * AIF_DISABLE_FIRING and AIF_DISABLE_MELEE are now functional
 *
 * 76    11/06/98 11:39a Chris
 * Robots with flamethrowers and Omega cannons work in single player
 *
 * 75    10/14/98 6:55p Chris
 * Added turret change direction sounds and level goal ability to toggle
 * auto level end
 *
 * 74    10/13/98 1:08p Chris
 * Greatly improved the AI's use of paths.  Improved visability checking
 * algorithm.   Probably needs a second pass for further cleanup.
 *
 * 73    10/09/98 7:47p Chris
 * Added ObjSetDeadFlag
 *
 * 72    9/16/98 4:31p Chris
 * Added target by distance
 *
 * 71    8/19/98 6:24p Chris
 * Added more unused water support
 *
 * 70    8/17/98 4:56p Chris
 * Added a new goal flag
 *
 * 69    8/15/98 6:11p Chris
 * Added 13 new fields.  AI fire spread works.
 *
 * 68    7/28/98 5:04p Chris
 * Added some new multiplayer support (for dodging and targetting)
 *
 * 67    7/24/98 6:06p Chris
 * Initial robot leading code  -- needs multiple wb support
 *
 * 66    7/01/98 4:35p Chris
 * More multiplayer sync issues
 *
 * 65    7/01/98 10:58a Chris
 * Working on multiplayer AI stuff
 *
 * 64    6/30/98 6:36p Chris
 * Added rev .1 of multiplayer animations - BTW  It is totally not done.
 *
 * 63    6/26/98 2:52p Chris
 * AI now reports when it updates its orientation
 *
 * 62    5/26/98 9:34a Chris
 * Added XZ distances for circle dist.  :)
 *
 * 61    5/18/98 8:06p Chris
 * Made melee attacks closer to what I want in terms of functionality
 *
 * 60    5/18/98 12:40p Chris
 * Added a new flag (F_BLINE_IF_SEE_GOAL)
 *
 * 59    5/17/98 9:07p Chris
 * Fixed melee attacks.  Thanks to Ala.  :)
 *
 * 58    5/17/98 7:54p Chris
 * Correctly integrated the goal system and circle distance stuff.  Added
 * support for "target goals".
 *
 * 57    5/15/98 2:58p Chris
 * More on the big AI update
 *
 * 56    5/14/98 3:01p Chris
 * More new AI code
 *
 * 55    5/14/98 12:21p Chris
 * Updating AI system... Incomplete
 *
 * 54    5/12/98 3:51p Chris
 * Oops
 *
 * 53    5/12/98 3:46p Chris
 * Added some notify/goal system stuff and orientation to velocity
 *
 * 52    5/11/98 4:39p Chris
 * Improved AI system (goals have notifies and are more flexable).
 *
 * 51    5/07/98 6:01p Chris
 * More AI/OSIRIS stuff...
 *
 * 50    5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 49    5/03/98 7:02p Chris
 * Improved sound support for AI system
 *
 * 48    5/03/98 6:03p Chris
 * Added sound support to the animation system
 *
 * 47    5/01/98 3:41p Chris
 *
 * 46    5/31/98 3:05p Chris
 * Allowed death anims (fixed problem with ctype union of CT_DEBRIS and
 * CT_AI)
 *
 * 45    4/30/98 11:31a Chris
 * Massive upgrades to the AI system
 *
 * 44    4/22/98 9:43p Chris
 * More AI improvements
 *
 * 43    4/21/98 11:25a Chris
 * Improving GET_TO_OBJ goal
 *
 * 42    4/19/98 9:56p Chris
 * AI system is integrated with OSIRIS.  Path system is integrated with
 * the AI system.  Bugs will ensue.
 *
 * 41    4/16/98 2:56p Chris
 * Updated buddy support and intergrated scripting and AI
 *
 * 40    4/13/98 7:38p Chris
 * Added more support for a 'real' AI.
 *
 * 39    3/31/98 4:23p Chris
 * Added a new AIpath system
 *
 * 38    3/25/98 11:02a Chris
 * version 1.0 of the new AI ranged firing code.
 *
 * 37    3/23/98 10:03a Chris
 * Added independant wb animations
 *
 * 36    3/17/98 12:14p Chris
 * Fixed bug with bumping player causing awareness
 *
 * 35    3/17/98 11:27a Chris
 * Added object bump notifies for AI
 *
 * 34    3/03/98 5:02p Chris
 * Added a status register to the ai_frame.  Also, I enabled a bunch of
 * the fields from the AI Dialog.  In addiition, I tweaked how melee
 * attacks work and animate.
 *
 * 33    3/02/98 6:56p Chris
 * Changed melee_dist to melee_damage
 *
 * 32    3/02/98 4:16p Chris
 * Added 14 new fields to the AI Settings Dialog/page.
 *
 * 31    2/27/98 7:23p Chris
 * Started to add new AI fields -- no way near complete
 *
 * 30    2/16/98 11:19p Chris
 * Added support for melee robots
 *
 * 29    2/16/98 1:05p Chris
 * Added some Flinch support
 *
 * 28    2/16/98 2:47a Chris
 * Massive improvements to the animation system and the AI
 *
 * 27    2/11/98 7:00p Chris
 * Removed priority (changed to influence) and added activation_level
 *
 * 26    2/10/98 4:45p Chris
 * Incremental changes:  Made a new node_orient heuristic.  Removed some
 * bad fields from the ai_info struct.
 *
 * 25    2/10/98 12:14a Chris
 * Improving the awareness system.  Re-enabled super dodging.  Added the
 * auto-fluctuate speed flag (allows some diversity).  Enabled FOV
 * information.
 *
 * 24    2/06/98 5:51p Chris
 * Added the ability turn robots on and off
 *
 * 23    2/06/98 4:19p Chris
 * Added a boat load of path stuff
 *
 * 22    2/06/98 2:15a Chris
 * Activated the max_velocity, max_delta_velocity, and max_turn_rate
 * fields for AI objects.
 *
 * 21    2/02/98 8:15p Chris
 * Updated the AI system
 *
 * 20    1/30/98 2:19p Chris
 * More improvements (target vis stuff and setting of the AIN_ALWAYS_ON is
 * now done correctly)
 *
 * 19    1/29/98 3:29p Chris
 * Major update to the AI system.
 *
 * 18    1/20/98 4:40p Chris
 * Fixed some visability stuff.
 *
 * 17    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 16    1/14/98 7:57p Chris
 * Improving the awareness system
 *
 * 15    11/17/97 5:59p Chris
 * Allowed some thief stuff
 *
 * 14    11/14/97 11:55p Chris
 * Dodge goals are semi-functional
 *
 * 13    11/12/97 5:47p Chris
 * Incremental improvements
 *
 * 12    10/28/97 12:25p Chris
 * Added support for initial class, type, and movement types.  Starting to
 * flush out the AI structure
 *
 * 11    10/05/97 5:29a Chris
 * Fixed problems at ubytes cause when setting then to -1 (made them
 * chars)
 *
 * 10    9/18/97 1:26p Matt
 * Moved next_movement from object struct to ai_frame
 *
 * 9     8/05/97 12:17p Chris
 *
 * 8     7/30/97 1:31p Chris
 * Made helicopters slightly more interesting.
 *
 * 7     7/29/97 12:20p Chris
 * Incremental improvements.  Fixed a memory bug.
 *
 * 6     7/28/97 1:19p Chris
 * Expanding the AI system
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

#ifndef AISTRUCT_H_
#define AISTRUCT_H_

#include <array>

#include "pstypes.h"
#include "vecmat.h"
#include "aistruct_external.h"
#include "room.h"

//-------------------------------------------------
// GLOBAL Info and Constants for AI
//-------------------------------------------------

#define AI_INVALID_INDEX -1

// AI system state.

#define AISTAT_ENABLED 1
#define AISTAT_DISABLED 2

extern char AI_Status;

// Last know player info -- might make it a [MAX_PLAYERS]

extern vector ai_lkplayer_pos;
extern vector ai_lkplayer_velocity;
extern float ai_lkplayer_time;

#define MAX_AI_INIT_CLASSES 3
extern const char *const Ai_class_strings[MAX_AI_INIT_CLASSES];

#define MAX_AI_INIT_TYPES 9
extern const char *const Ai_type_strings[MAX_AI_INIT_TYPES];

#define MAX_AI_INIT_MOVEMENT_TYPES 4
extern const char *const Ai_movement_type_strings[MAX_AI_INIT_MOVEMENT_TYPES];

#define MAX_AI_INIT_MOVEMENT_SUBTYPES 7
extern const char *const Ai_movement_subtype_flying_strings[MAX_AI_INIT_MOVEMENT_SUBTYPES];
extern const char *const Ai_movement_subtype_walking_strings[MAX_AI_INIT_MOVEMENT_SUBTYPES];

extern float AI_last_time_room_noise_alert_time[MAX_ROOMS + 8];

//-------------------------------------------------
// AI Class, Type, and Action indices
//-------------------------------------------------

// AI Class -- make sure to update MAX_AI_CLASSES if you add a new class

#define AIC_STATIC 0
#define AIC_PURE_PATH 1
#define AIC_AIS_FULL 2
// #define AIC_DYNAMIC				3
// #define AIC_AIS_MOVEMENT			4
// #define AIC_AIS_FIRING			5

// AI Action -- What is it doing?

#define AID_SLEEPING 0
#define AID_ATTACKING_OBJ 1
#define AID_WANDERING 2
#define AID_NOT_THINKING 3
#define AID_CHASE_OBJECT 4
#define AID_RUN_FROM_OBJECT 5
#define AID_HIDE 6
#define AID_FOLLOW_PATH 7
#define AID_OPEN_DOOR 8

//-------------------------------------------------
// Notification structures
//-------------------------------------------------

struct ain_see {
  bool f_use_fov;
  float max_dist;
};

struct ain_hear {
  bool f_directly_player;
  float max_dist;
  float hostile_level; // 0 - 1
  float curiosity_level;
};

//-------------------------------------------------
// Path Structures
//-------------------------------------------------

#define MAX_JOINED_PATHS 5

// Allow for linked paths

#define AIP_STATIC 0
#define AIP_DYNAMIC 1
#define AIP_MOVE_LIST 2

struct ai_path_info {
  uint16_t cur_path;
  uint16_t cur_node;

  uint16_t num_paths;

  int goal_uid; // which goal generated this path
  int goal_index;

  // Used by all paths
  uint8_t path_id[MAX_JOINED_PATHS];
  uint8_t path_type[MAX_JOINED_PATHS];

  // Used for static game paths
  uint16_t path_start_node[MAX_JOINED_PATHS];
  uint16_t path_end_node[MAX_JOINED_PATHS];
  uint16_t path_flags[MAX_JOINED_PATHS];
};

// Used for predefined move lists (off of normal static paths)
struct ai_move_path {
  vector pos;
  matrix orient;

  int16_t path_id;
};

struct path_information {
  int path_id;
  int start_node;
  int next_node;
  int end_node;
};

// Goal Ender Structure

struct goal_enabler {
  char enabler_type;

  union {
    float float_value;
    float time;
    char movement_type;
    int flags; // Flags that enable/disable this goal
    float dist;
    int awareness;
  };

  float percent_enable;
  float check_interval;
  float last_check_time;

  char bool_next_enabler_op;

};

//-------------------------------------------------
// Goal Structures
//-------------------------------------------------

// MAX of 32 goal types unless the bitfield is made wider.

// I wonder if goals can be classified.  If so, we could reserve X goal for class a, and Y goal slots for class b
// plus it would make sure the our slots do not fill up in bad or degenerate ways.

struct gi_fire {
  int16_t cur_wb;       // for ranged attack
  uint8_t cur_mask;     // for ranged attack
  uint8_t melee_number; // this could be union'ed but it makes this struct word aligned
};

struct g_steer {
  float min_dist;
  float max_dist;
  float max_strength;
};

struct g_floats {
  float fp1;
  float fp2;
  float fp3;
};

struct g_wander_extra {
  int avoid_handle;
  char min_rooms;
  char max_rooms;
  char flags;
  char mine_index; // Used for if this object accidently goes on to the terrain
};

#define GAF_ALIGNED 0x01
#define GAF_SPHERE 0x02
#define GAF_TEMP_CLEAR_AUTOLEVEL 0x04
#define GAF_TEMP_CLEAR_ROBOT_COLLISIONS 0x08
#define GAF_TEMP_POINT_COLLIDE_WALLS 0x10

struct g_attach {
  float rad;
  int16_t flags;
  char parent_ap;
  char child_ap;
};

struct g_static_path {
  int16_t start_node;
  int16_t end_node;
  int16_t cur_node;
};

struct goal_info {
  union {
    int handle;
    int roomnum;
    int f_actions;
    int id; // Type of CUSTOM -- Id determines which one it was
            // Also used as the Path ID for static path followers
  };

  union {
    float time;
    vector vec;
    vector pos;
    g_floats fs; // goal floats or a vector
  };

  union {
    g_steer dist_info;
    g_attach attach_info;
    g_wander_extra wander_extra_info;
    g_static_path static_path_info;
    void *scripted_data_ptr;
  };

};

// Goal structure
struct goal {
  uint32_t type;
  char subtype;
  uint8_t activation_level;
  float creation_time;

  float min_influence;
  union {
    float influence;
    float max_influence;
  };

  float ramp_influence_dists[4]; // Sorted by distance

  goal_info g_info;

  char num_enablers;
  goal_enabler enabler[MAX_ENABLERS_PER_GOAL];

  float circle_distance;
  int status_reg;

  float start_time;
  float next_path_time; // used of goals with paths associated with them

  float dist_to_goal;

  vector vec_to_target;
  float next_check_see_target_time;
  vector last_see_target_pos;
  float last_see_target_time;
  float next_target_update_time;

  int flags;
  int guid; // Designer assigned

  int goal_uid; // used by the AI system for paths

  vector set_fvec;
  vector set_uvec;

  bool used;
};

#define OBJGOAL(x)                                                                                                     \
  (((goal *)x)->type & (AIG_GET_AWAY_FROM_OBJ | AIG_HIDE_FROM_OBJ | AIG_GET_TO_OBJ | AIG_ATTACH_TO_OBJ |               \
                        AIG_FIRE_AT_OBJ | AIG_MELEE_TARGET | AIG_GUARD_OBJ | AIG_DODGE_OBJ | AIG_MOVE_AROUND_OBJ |     \
                        AIG_MOVE_RELATIVE_OBJ_VEC | AIG_MOVE_RELATIVE_OBJ | AIG_GET_AROUND_OBJ | AIG_AVOID_OBJ |       \
                        AIG_COHESION_OBJ | AIG_ALIGN_OBJ | AIG_PLACE_OBJ_ON_OBJ))
#define COMPLETEATOBJ(x) (((goal *)x)->type & (AIG_GET_TO_OBJ))
#define POSGOAL(x) (((goal *)x)->type & (AIG_WANDER_AROUND | AIG_GUARD_AREA | AIG_GET_TO_POS | AIG_GET_AROUND_POS))
#define TARGETONLYGOAL(x) (((goal *)x)->type & (AIG_MELEE_TARGET))
#define COMPLETEATPOS(x) (((goal *)x)->type & (AIG_WANDER_AROUND | AIG_GET_TO_POS))

struct notify {
  union {
    int obj_handle;
    int goal_num;
  };

  union {
    vector pos;
    int movement_type;
    int anim_type;
    int attack_num;
    int enabler_num;
  };

  float time;
};

struct ain_weapon_hit_info {
  int parent_handle;
  int weapon_handle;
  int hit_face;
  int hit_subobject;
  float hit_damage;
  vector hit_pnt;
};

//-------------------------------------------------
// AI awareness scale
//-------------------------------------------------

//-------------------------------------------------
// AI Sounds
//-------------------------------------------------

#define MAX_AI_SOUNDS 5

#define AI_MEM_DEPTH 5

struct [[gnu::packed]] ai_mem {
  // Computed at end of memory frame
  float shields = 0.0f;
  int16_t num_enemies = 0;
  int16_t num_friends = 0;

  // Incremented during the memory frame
  int16_t num_times_hit = 0;
  int16_t num_enemy_shots_fired = 0;
  int16_t num_hit_enemy = 0;
  int16_t num_enemy_shots_dodged = 0;
};

//-------------------------------------------------
// AI tracking information
//-------------------------------------------------

//-------------------------------------------------
// AI framework per robot
//-------------------------------------------------

struct ai_frame {
  char ai_class; // Static, DLL, Soar, Flock, and other will be here -- chrishack
  char ai_type;  // Used for some coded types

  ai_path_info path;

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

  int sound[MAX_AI_SOUNDS]; // AI sounds,
  float last_sound_time[MAX_AI_SOUNDS];
  int16_t last_played_sound_index;

  char movement_type;
  char movement_subtype;

  char animation_type;
  char next_animation_type;

  char next_movement; // For queueing actions  :)
  char current_wb_firing;
  char last_special_wb_firing;

  goal goals[MAX_GOALS];

  // Standard memory
  int target_handle;
  float next_target_update_time;

  float dist_to_target_actual;
  float dist_to_target_perceived;
  vector vec_to_target_actual;
  vector vec_to_target_perceived;

  float next_check_see_target_time;
  vector last_see_target_pos;
  float last_see_target_time;
  float last_hear_target_time;

  // int rand_val;
  // float next_rand_time;

  float weapon_speed;

  float next_melee_time;
  float last_render_time; // Last time I was rendered -- BAD IN MULTIPLAYER -- chrisnote
  float next_flinch_time; // Next valid time to flinch

  int status_reg;

  int flags;
  int notify_flags; // Agent is only notified of some event types

  // Normalized movement and facing information
  vector movement_dir;
  vector rot_thrust_vector;

  float fov;

  int anim_sound_handle; // Goes with Animation sounds which can loop -- not for AI sounds

  float avoid_friends_distance;

  float frustration;
  float curiousity;
  float life_preservation;
  float agression;

  // Current emotional levels
  float cur_frustration;
  float cur_curiousity;
  float cur_life_preservation;
  float cur_agression;

  // X Second memory
  float mem_time_till_next_update;
  std::array<ai_mem, AI_MEM_DEPTH> memory;

  float fire_spread;
  float night_vision;
  float fog_vision;
  float lead_accuracy;
  float lead_varience;
  float fight_team;
  float fight_same;
  float hearing;
  float roaming;
  float leadership;
  float coop_same;
  float coop_team;

  float biased_flight_importance;
  float biased_flight_min;
  float biased_flight_max;

  vector last_dodge_dir;
  float dodge_till_time;

  float awareness;

  matrix saved_orient;

};

// Etern'ed functions that depend of aistruct stuff

#include "object_external.h"
#include "room.h"

#define MAX_DYNAMIC_PATHS 50
#define MAX_NODES 50

class ai_dynamic_path {
public:
  ai_dynamic_path() {
    num_nodes = 0;
    use_count = 0;
    owner_handle = OBJECT_HANDLE_NONE;
  };

  std::array<vector, MAX_NODES> pos;
  std::array<int, MAX_NODES> roomnum;

  int16_t num_nodes;
  int16_t use_count;

  int owner_handle;
};

extern std::array<ai_dynamic_path, MAX_DYNAMIC_PATHS> AIDynamicPath;
extern std::array<int, MAX_ROOMS> AIAltPath;
extern int AIAltPathNumNodes;

#endif
