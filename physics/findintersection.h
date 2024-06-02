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

 * $Logfile: /DescentIII/Main/lib/findintersection.h $
 * $Revision: 51 $
 * $Date: 6/10/99 6:32p $
 * $Author: Chris $
 *
 * Find intersection header
 *
 * $Log: /DescentIII/Main/lib/findintersection.h $
 *
 * 51    6/10/99 6:32p Chris
 * New Editor Support
 *
 * 50    5/18/99 11:10a Matt
 * Added variable ceiling height.
 *
 * 49    4/20/99 8:14p Chris
 * Added support for object's that hit the ceiling and for making the
 * level always check for the ceiling (inside and outside the mine)
 *
 * 48    1/15/99 5:59p Chris
 *
 * 47    1/13/99 2:29a Chris
 * Massive AI, OSIRIS update
 *
 * 46    1/05/99 12:24p Chris
 * More OSIRIS improvements
 *
 * 45    1/01/99 4:10p Chris
 * Added some const parameters, improved ray cast object collide/rejection
 * code
 *
 * 44    11/23/98 11:07a Chris
 * Added another parameter to fvi_QuickDistObjectList
 *
 * 43    10/29/98 5:20p Chris
 * Player ships collide smaller now
 *
 * 42    10/22/98 10:25p Kevin
 * took out volatile
 *
 * 41    10/21/98 9:41p Chris
 * Improved walking code!
 *
 * 40    10/17/98 12:25p Chris
 * Fixed attached flares
 *
 * 39    10/16/98 8:33p Chris
 * Fixed attached flare problem
 *
 * 38    10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 37    10/16/98 1:07p Chris
 * Lowered the max hits to 2 for now (we don't even use the info anyhow)
 *
 * 36    8/03/98 3:59p Chris
 * Added support for FQ_IGNORE_WEAPONS, added .000001 attach code, fix a
 * bug in polymodel collision detection
 *
 * 35    7/23/98 12:46p Chris
 * Added a flag to ignore external rooms
 *
 * 34    7/02/98 2:51p Chris
 * Added a fast line to bbox function
 *
 * 33    6/15/98 7:01a Chris
 * Cleaned out DII stuff and added new PhysicsSim extern's
 *
 * 32    6/03/98 6:42p Chris
 * Added multipoint collision detection an Assert on invalid (infinite
 * endpoint).
 *
 * 31    5/22/98 4:44p Chris
 * Added better melee hit prediction
 *
 * 30    5/05/98 5:23p Chris
 * Faster external room collisions with FQ_EXTERNAL_ROOMS_AS_SPHERE
 *
 * 29    3/23/98 11:37a Chris
 * Added the f_lightmap_only parameter to fvi_QuickDistObjectList
 *
 * 28    3/23/98 11:18a Chris
 * Added int fvi_QuickDistObjectList(vector *pos, int init_room_index,
 * float rad, int16_t *object_index_list, int max_elements)
 *
 *
 * 27    3/17/98 11:33a Chris
 * Improved performance (AABB updates on poly-sphere collide)
 *
 * 26    3/16/98 12:50p Chris
 * Speed up?
 *
 * 25    3/16/98 9:43a Chris
 * Added FQ_NO_RELINK
 *
 * 24    2/19/98 6:17p Chris
 * Added some debug info
 *
 * 23    2/11/98 10:04p Chris
 * Added FQ_ONLY_DOOR_OBJ and fixed a bug with FQ_ONLY_PLAYER_OBJ
 *
 * 22    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 21    1/30/98 4:34p Jason
 * FROM CHRIS: Changed COL_CELL size to 1
 *
 * 20    1/20/98 11:35a Chris
 * Raised ceiling to MAX_TERRAIN_HEIGHT
 *
 * 19    1/19/98 5:05p Chris
 * Added ceiling collisions for players and powerups
 *
 * 18    12/16/97 6:11p Chris
 * Attempt to improve FVI for outside
 *
 * 17    10/28/97 5:46p Chris
 * Added a quick cell list function
 *
 * 16    10/28/97 12:20p Chris
 * Added support to ignore wall collisions
 *
 * 15    10/22/97 12:41p Chris
 * Incremental BBOX stuff and added support for subobject hit returned
 * from fvi
 *
 * 14    10/07/97 4:03p Chris
 * Added support for object backface checking
 *
 * 13    10/06/97 10:52a Jason
 * added "FQ_IGNORE_NON_LIGHTMAP_OBJECTS" flag
 *
 * 12    9/19/97 6:58p Chris
 * Fixed some bugs with the big object system and removed some annoying
 * mprintf's
 *
 * 11    9/19/97 1:01p Chris
 * Added better large object support
 *
 * 10    9/17/97 11:00a Chris
 * Removed dependance on segment.h
 *
 * 9     9/15/97 6:24p Chris
 * Added a second chance check if no rooms are initialy found
 *
 * 8     9/15/97 5:20a Chris
 * Added sphere2poly support.  Rearranged object collisions.
 *
 * 7     9/12/97 6:36p Chris
 * Added collision terrain segment support
 * Added some LARGE OBJECT collision support
 *
 * 6     9/11/97 3:08p Chris
 * Added support for weapons flying through holes in transparent textures.
 *
 * 5     9/11/97 12:43p Chris
 * Added new support for face_physics_info from room.h.  Also, changed how
 * we detect portals.  Also added recorded faces.
 *
 * 4     9/02/97 11:41a Chris
 * Added support the the quick face/room from distance function
 *
 * 3     8/18/97 1:53a Chris
 * Added fvi_Relink
 *
 * 2     8/04/97 5:35p Chris
 * Added support for back face collisions and new fvi code
 *
 * 10    6/11/97 10:43a Chris
 *
 * 9     6/10/97 5:34p Chris
 *
 * 8     5/13/97 5:52p Chris
 * Added ability to exit and enter mine.  Also did some
 * incremental improvements.
 *
 * 7     5/05/97 5:41a Chris
 * Added some better polygon collision code.  It is still rough though.
 *
 * 6     4/17/97 3:10p Chris
 * Added edge of world object delete.  Also did some incremental
 * improvements.
 *
 * 5     4/15/97 4:15p Chris
 *
 * 4     3/24/97 12:18p Chris
 *
 * 3     3/03/97 1:02p Chris
 *
 * 2     3/03/97 5:52a Chris
 * Pre-alpha 0.01 -- just a starting point that compiles
 *
 * 1     3/03/97 3:26a Chris
 *
 * $NoKeywords: $
 */

#ifndef _FVI_H
#define _FVI_H

#include "object.h"
#include "vecmat.h"
#include "terrain.h"
// #include "room.h"
#include "findintersection_external.h"

extern float Ceiling_height;

#define CEILING_HEIGHT (Ceiling_height)

#define PLAYER_SIZE_SCALAR 0.8f

extern bool FVI_always_check_ceiling;

// Big Object Info
#define CELLS_PER_COL_CELL 1
#define COL_TERRAIN_SIZE (TERRAIN_SIZE * (float)CELLS_PER_COL_CELL)

#define MIN_BIG_OBJ_RAD (COL_TERRAIN_SIZE)

// chrishack -- we could turn backface, on and off so that we
// can individually use backface checking on object and/or wall...  :)

#define MAX_FVI_SEGS 100

#define MAX_HITS 2

#define Q_RIGHT 0
#define Q_LEFT 1
#define Q_MIDDLE 2

static inline bool FastVectorBBox(const float *min, const float *max, const float *origin, const float *dir) {
  bool f_inside = true;
  char quad[3];
  int i;
  float max_t[3];
  float can_plane[3];
  int which_plane;
  float coord[3];

  for (i = 0; i < 3; i++) {
    if (origin[i] < min[i]) {
      quad[i] = Q_LEFT;
      can_plane[i] = min[i];
      f_inside = false;
    } else if (origin[i] > max[i]) {
      quad[i] = Q_RIGHT;
      can_plane[i] = max[i];
      f_inside = false;
    } else {
      quad[i] = Q_MIDDLE;
    }
  }

  if (f_inside) {
    return true;
  }

  for (i = 0; i < 3; i++) {
    if (quad[i] != Q_MIDDLE && dir[i] != 0.0f)
      max_t[i] = (can_plane[i] - origin[i]) / dir[i];
    else
      max_t[i] = -1.0f;
  }

  which_plane = 0;

  for (i = 0; i < 3; i++)
    if (max_t[which_plane] < max_t[i])
      which_plane = i;

  if (max_t[which_plane] < 0.0f)
    return false;

  for (i = 0; i < 3; i++) {
    if (which_plane != i) {
      coord[i] = origin[i] + max_t[which_plane] * dir[i];

      if ((quad[i] == Q_RIGHT && coord[i] < min[i]) || (quad[i] == Q_LEFT && coord[i] > max[i])) {
        return false;
      }
    } else {
      coord[i] = can_plane[i];
    }
  }

  return true;
}

// this data structure gets filled in by find_vector_intersection()
struct fvi_info {
  vector hit_pnt; // centerpoint when we hit
  int hit_room;   // what room hit_pnt is in
  float hit_dist; // distance of the hit

  int num_hits; // Number of recorded hits

  int hit_type[MAX_HITS];        // what sort of intersection
  vector hit_face_pnt[MAX_HITS]; // actual collision point (edge of rad)

  int hit_face_room[MAX_HITS];   // what room the hit face is in
  int hit_face[MAX_HITS];        // if hit wall, which face
  vector hit_wallnorm[MAX_HITS]; // if hit wall, ptr to its surface normal

  int hit_object[MAX_HITS];    // if object hit, which object
  int hit_subobject[MAX_HITS]; // if a POLY_2_SPHERE hit, then it has the poly involved

  int n_rooms;                // how many segs we went through
  int roomlist[MAX_FVI_SEGS]; // list of segs vector went through

  // BBox hit results
  matrix hit_orient;
  vector hit_rotvel;
  angle hit_turnroll;
  vector hit_velocity;
  float hit_time;

  vector hit_subobj_fvec;
  vector hit_subobj_uvec;
  vector hit_subobj_pos;
};

// this data contains the parms to fvi()
struct fvi_query {
  vector *p0, *p1;
  int startroom;
  float rad;
  int16_t thisobjnum;
  int *ignore_obj_list;
  int flags;

  // BBox stuff...
  matrix *o_orient;
  vector *o_rotvel;
  vector *o_rotthrust;
  vector *o_velocity;
  angle *o_turnroll;
  vector *o_thrust;
  float frametime;
};

// Find out if a vector intersects with anything.
// Fills in hit_data, an fvi_info structure (see above).
// Parms:
//  p0 & startseg 	describe the start of the vector
//  p1 					the end of the vector
//  rad 					the radius of the cylinder
//  thisobjnum 		used to prevent an object with colliding with itself
//  ingore_obj_list	NULL, or ptr to a list of objnums to ignore, terminated with -1
//  check_obj_flag	determines whether collisions with objects are checked
// Returns the hit_data->hit_type
extern int fvi_FindIntersection(fvi_query *fq, fvi_info *hit_data, bool no_subdivision = false);

// Face/Room list for some fvi call(s)
struct fvi_face_room_list {
  uint16_t face_index;
  uint16_t room_index;
};

#define MAX_RECORDED_FACES 200

// Recorded face list
extern fvi_face_room_list Fvi_recorded_faces[MAX_RECORDED_FACES];
extern int Fvi_num_recorded_faces;

// Generates a list of faces(with corresponding room numbers) within a given distance to a position.
// Return value is the number of faces in the list
extern int fvi_QuickDistFaceList(int init_room_index, vector *pos, float rad, fvi_face_room_list *quick_fr_list,
                                 int max_elements);
// Returns the number of cells that are approximately within the specified radius
extern int fvi_QuickDistCellList(int init_cell_index, vector *pos, float rad, int *quick_cell_list, int max_elements);

// Returns the number of objects that are approximately within the specified radius
int fvi_QuickDistObjectList(vector *pos, int init_roomnum, float rad, int16_t *object_index_list, int max_elements,
                            bool f_lightmap_only, bool f_only_players_and_ais = false,
                            bool f_include_non_collide_objects = false, bool f_stop_at_closed_doors = false);

// finds the uv coords of the given point on the given seg & side
// fills in u & v. if l is non-NULL fills it in also
// extern void fvi_FindHitpointUV(float *u,float *v,float *l, vector *pnt,segment *seg,int sidenum,int facenum);

// Returns true if the object is through any walls
extern int fvi_ObjectIntersectsWall(object *objp);

extern int FVI_counter;
extern int FVI_room_counter;

bool fvi_QuickRoomCheck(vector *pos, room *cur_room, bool try_again = false);

extern fvi_info *fvi_hit_data_ptr;
extern fvi_query *fvi_query_ptr;
extern float fvi_collision_dist;
extern int fvi_curobj;
extern int fvi_moveobj;

bool PolyCollideObject(object *obj);

bool BBoxPlaneIntersection(bool fast_exit, vector *collision_point, vector *collision_normal, object *obj,
                           vector *new_pos, int nv, vector **vertex_ptr_list, vector *face_normal, matrix *orient);

extern uint32_t check_point_to_face(vector *colp, vector *face_normal, int nv, vector **vertex_ptr_list);

extern int check_vector_to_sphere_1(vector *intp, float *col_dist, const vector *p0, const vector *p1,
                                    vector *sphere_pos, float sphere_rad, bool f_correcting, bool f_init_collisions);

extern int check_line_to_face(vector *newp, vector *colp, float *col_dist, vector *wall_norm, const vector *p0,
                              const vector *p1, vector *face_normal, vector **vertex_ptr_list, const int nv,
                              const float rad);
extern void InitFVI(void);

// Types of supported collisions
#ifdef NED_PHYSICS
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
