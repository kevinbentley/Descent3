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

 * $Logfile: /DescentIII/Main/lib/collide.h $
 * $Revision: 15 $
 * $Date: 6/10/99 6:41p $
 * $Author: Chris $
 *
 * Descent III collide code
 *
 * $Log: /DescentIII/Main/lib/collide.h $
 *
 * 15    6/10/99 6:41p Chris
 * Added ned_physics support
 *
 * 14    4/23/99 9:22p Matt
 * Changed weapons to keep going after breaking glass.
 *
 * 13    4/14/99 3:59a Jeff
 * fixed case mismatches in #includes
 *
 * 12    1/29/99 5:09p Chris
 * Made changes for ROCKS
 *
 * 11    1/01/99 4:10p Chris
 * Added some const parameters, improved ray cast object collide/rejection
 * code
 *
 * 10    10/09/98 7:47p Chris
 * Added ObjSetDeadFlag
 *
 * 9     6/15/98 7:01a Chris
 * Cleaned out DII stuff and added new PhysicsSim extern's
 *
 * 8     5/07/98 2:22p Chris
 * Hit die dot
 *
 * 7     5/05/98 3:42p Chris
 * Code cleanup and fixed the collide_XXX_with_wall code.  The wall_normal
 * was know by fvi; so, it is passed to the function (instead of
 * generating it again)
 *
 * 6     2/05/98 2:02p Chris
 * Fixed the hitseg and hitwall in collide_object_with_wall and
 * scrape_object_with_wall
 *
 * 5     10/21/97 4:15p Chris
 * Incremental integration of the fvi/physics/collide code
 *
 * 4     10/20/97 11:55a Chris
 * Added some support for the new collide system.
 *
 * 3     9/17/97 10:59a Chris
 * Added a new way to compute radi
 *
 * 2     9/15/97 5:17a Chris
 * Removed the Explosion Vclips since they do not play correctly in
 * Hardware
 * Added support for building collisons.
 * working on SPhere to non-moving sphere collisions
 *
 * 5     3/15/97 1:29p Chris
 *
 * $NoKeywords: $
 */

#ifndef _COLLIDE_H
#define _COLLIDE_H

#include "object.h"
#include "vecmat.h"
#include "findintersection.h"

extern uint8_t CollisionResult[MAX_OBJECT_TYPES][MAX_OBJECT_TYPES];
extern uint8_t CollisionRayResult[MAX_OBJECT_TYPES];

void CollideInit();
void collide_two_objects(object *A, object *B, vector *collision_point, vector *collision_normal,
                         fvi_info *hit_info = NULL);
extern void apply_damage_to_player(object *player, object *killer, float damage);

// Process a collision between an object and a wall
// Returns true if the object hits the wall, and false if should keep going though the wall (for breakable glass)
bool collide_object_with_wall(object *A, float hitspeed, int hitseg, int hitwall, vector *hitpt, vector *wall_normal,
                              float hit_dot);

extern int apply_damage_to_robot(object *robot, float damage, int killer_objnum);

extern int Immaterial;

extern void collide_player_and_weapon(object *player, object *weapon, vector *collision_point);
extern void collide_player_and_materialization_center(object *objp);
extern void collide_robot_and_materialization_center(object *objp);

extern void scrape_object_on_wall(object *obj, int hitseg, int hitwall, vector *hitpt, vector *wall_normal);
extern int maybe_detonate_weapon(object *obj0p, object *obj, vector *pos);

extern void collide_player_and_nasty_robot(object *player, object *robot, vector *collision_point);

extern void net_destroy_controlcen(object *controlcen);
extern void collide_player_and_powerup(object *player, object *powerup, vector *collision_point);
// extern int check_effect_blowup(segment *seg,int side,vector *pnt, object *blower, int force_blowup_flag);
extern void apply_damage_to_controlcen(object *controlcen, float damage, int16_t who);
extern void bump_one_object(object *obj0, vector *hit_dir, float damage);

extern void FindHitpointUV(float *u, float *v, vector *point, room *rp, int facenum);

void ConvertEulerToAxisAmount(vector *e, vector *n, float *w);
void ConvertAxisAmountToEuler(vector *n, float *w, vector *e);

void bump_obj_against_fixed(object *obj, vector *collision_point, vector *collision_normal);

#ifndef NED_PHYSICS
#define RESULT_NOTHING 0
#define RESULT_CHECK_SPHERE_SPHERE 1
#define RESULT_CHECK_SPHERE_POLY 2
#define RESULT_CHECK_POLY_SPHERE 3
#define RESULT_CHECK_BBOX_POLY 4
#define RESULT_CHECK_POLY_BBOX 5
#define RESULT_CHECK_BBOX_BBOX 6
#define RESULT_CHECK_BBOX_SPHERE 7
#define RESULT_CHECK_SPHERE_BBOX 8
#define RESULT_CHECK_SPHERE_ROOM 9
#define RESULT_CHECK_BBOX_ROOM 10
#endif

#endif
