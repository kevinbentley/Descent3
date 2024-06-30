/*
 * $Logfile: /DescentIII/Main/Lib/PHYSICS.H $
 * $Revision: 15 $
 * $Date: 4/14/99 3:59a $
 * $Author: Jeff $
 *
 * Descent III Physics Header
 *
 * $Log: /DescentIII/Main/Lib/PHYSICS.H $
 *
 * 15    4/14/99 3:59a Jeff
 * fixed case mismatches in #includes
 *
 * 14    1/10/99 6:45a Jeff
 * Changes made to get linux version to compile
 *
 * 13    12/21/98 1:39p Chris
 * Matcens can hurt (or not hurt) players that are close to them
 *
 * 12    11/10/98 5:17p Jeff
 * peppered in some more forcefeedback effects
 *
 * 11    10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 10    10/15/98 3:26p Chris
 * Fixed known ground plane issues and used PhysCalcGround everywhere
 *
 * 9     8/27/98 6:23p Jeff
 * changed autoleveling in config so it is a slider...had to convert
 * global from bool->uint8_t.  Added fast headlight and mirrored surfaces to
 * config menu
 *
 * 8     6/15/98 7:01a Chris
 * Cleaned out DII stuff and added new PhysicsSim extern's
 *
 * 7     5/01/98 4:27p Chris
 * Added externals for terrain and room autoleveling
 *
 * 6     4/16/98 6:50p Chris
 *
 * 5     2/19/98 6:17p Chris
 * Added some debug info
 *
 * 4     1/20/98 5:27p Chris
 * Added physics support for the vis. system
 *
 * 3     10/28/97 12:23p Chris
 * Added a walking sim
 *
 * 2     9/11/97 12:43p Chris
 * Added new support for face_physics_info from room.h.  Also, changed how
 * we detect portals.  Also added recorded faces.
 *
 * 6     3/27/97 10:50a Chris
 * Added bounce constant (PHYSICS_BOUNCE_UNLIMITED) for objects that can
 * bounce forever
 *
 * 5     3/15/97 1:29p Chris
 *
 * $NoKeywords: $
 */

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "vecmat.h"
#include "findintersection.h"
#include "object.h"
#include "viseffect.h"

extern int Physics_normal_counter;
extern int Physics_normal_looping_counter;
extern int Physics_walking_counter;
extern int Physics_walking_looping_counter;
extern int Physics_vis_counter;

// The current strength of the world's gravity
extern float Gravity_strength;

#define PHYSICS_UNLIMITED_BOUNCE -1

#ifdef _DEBUG
extern int Physics_player_verbose;
#endif

extern uint8_t Default_player_terrain_leveling;
extern uint8_t Default_player_room_leveling;

bool PhysicsDoSimRot(object *obj, float frame_time, matrix *orient, vector *rotforce, vector *rotvel, angle *turn_roll);
void PhysicsDoSimLinear(const object &obj, const vector &pos, const vector &force, vector &velocity,
                        vector &movementVec, vector &movementPos, float simTime, int count);

extern int Physics_NumLinked;
extern std::array<int, MAX_OBJECTS> PhysicsLinkList;

// Simulate a physics object for this frame
void do_physics_sim(object *obj);

// Quick sim for vis stuff
void do_vis_physics_sim(vis_effect *vis);

// Simulate a physics object for this frame
void do_walking_sim(object *obj);

// Applies an instantaneous force on an object, resulting in an instantaneous
// change in velocity.
void phys_apply_force(object *obj, vector *force_vec, int16_t weapon_index = -1);
void phys_apply_rot(object *obj, vector *force_vec);

// this routine will set the thrust for an object to a value that will
//(hopefully) maintain the object's current velocity
void set_thrust_from_velocity(object *obj);

// Determines the point and normal of the ground point
bool PhysCalcGround(vector *ground_point, vector *ground_normal, object *obj, int ground_num);

// Linked objects arbitrary linking for things like weapons (unlike attached objects)
void DoPhysLinkedFrame(object *obj);

#endif
