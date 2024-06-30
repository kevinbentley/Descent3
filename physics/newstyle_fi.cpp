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
*/

#include "pserror.h"
#include "pstypes.h"
#include "vecmat.h"
#include "polymodel.h"
#include "findintersection.h"
#include "game.h"

#include <stdlib.h>
#include <string.h>
#ifndef NED_PHYSICS
#include "multi.h"
#endif

extern matrix View_matrix;
extern vector View_position;

static vector Original_pos;
static matrix Original_orient;

static vector fvi_move_fvec;
static vector fvi_move_uvec;
static bool fvi_do_orient;

static bool Fvi_f_normal;

#define MAX_INSTANCE_DEPTH 30

struct instance_context {
  matrix m;
  vector p;
  vector p0;
  vector p1;
  vector fvec;
  vector uvec;
};
static struct instance_context instance_stack[MAX_INSTANCE_DEPTH];

static int instance_depth = 0;

static inline void ns_compute_movement_AABB(void);
static inline bool ns_movement_manual_AABB(vector *min_xyz, vector *max_xyz);
static void CollideSubmodelFacesUnsorted(poly_model *pm, bsp_info *sm);

/// instance at specified point with specified orientation.
/// if matrix==NULL, don't modify matrix.  This will be like doing an offset.
static void newstyle_StartInstanceMatrix(vector *pos, matrix *orient);
/// instance at specified point with specified orientation.
/// if angles==NULL, don't modify matrix.  This will be like doing an offset.
static void newstyle_StartInstanceAngles(vector *pos, angvec *angles);

/// pops the old context
static void newstyle_DoneInstance();
static void CollideSubmodel(poly_model *pm, bsp_info *sm, uint32_t f_render_sub);
static void CollidePolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, uint32_t f_render_sub);

static void BuildModelAngleMatrix(matrix *mat, angle ang, vector *axis) {
  float x, y, z;
  float s, c, t;

  x = axis->x;
  y = axis->y;
  z = axis->z;

  s = (float)FixSin(ang);
  c = (float)FixCos(ang);
  t = 1.0f - c;

  mat->rvec.x = t * x * x + c;
  mat->rvec.y = t * x * y + s * z;
  mat->rvec.z = t * x * z - s * y;

  mat->uvec.x = t * x * y - s * z;
  mat->uvec.y = t * y * y + c;
  mat->uvec.z = t * y * z + s * x;

  mat->fvec.x = t * x * z + s * y;
  mat->fvec.y = t * y * z - s * x;
  mat->fvec.z = t * z * z + c;
}

////rotates a point. returns codes.  does not check if already rotated
// static inline void collide_RotatePoint(g3Point *dest,vector *src)
//{
// vector tempv;
//
//	tempv = *src - View_position;
//
//	dest->p3_vec = tempv * View_matrix;
//
//}

float fvi_hit_param;
bool fvi_check_param;

static vector ns_min_xyz;
static vector ns_max_xyz;

inline void ns_compute_movement_AABB(void) {
  vector delta_movement = *fvi_query_ptr->p1 - *fvi_query_ptr->p0;
  vector offset_vec;

  offset_vec.x = fvi_query_ptr->rad;
  offset_vec.y = fvi_query_ptr->rad;
  offset_vec.z = fvi_query_ptr->rad;

  ns_min_xyz = ns_max_xyz = *fvi_query_ptr->p0;

  ns_min_xyz -= offset_vec;
  ns_max_xyz += offset_vec;

  if (delta_movement.x > 0.0f)
    ns_max_xyz.x += delta_movement.x;
  else
    ns_min_xyz.x += delta_movement.x;

  if (delta_movement.y > 0.0f)
    ns_max_xyz.y += delta_movement.y;
  else
    ns_min_xyz.y += delta_movement.y;

  if (delta_movement.z > 0.0f)
    ns_max_xyz.z += delta_movement.z;
  else
    ns_min_xyz.z += delta_movement.z;
}

inline bool ns_movement_manual_AABB(vector *min_xyz, vector *max_xyz) {
  bool overlap = true;

  if (max_xyz->y < ns_min_xyz.y || ns_max_xyz.y < min_xyz->y || max_xyz->x < ns_min_xyz.x ||
      ns_max_xyz.x < min_xyz->x || max_xyz->z < ns_min_xyz.z || ns_max_xyz.z < min_xyz->z)
    overlap = false;

  return overlap;
}

// collide with a submodel
// Parameters:	nv - the number of verts in the poly
//					pointlist - a pointer to a list of pointers to points
//					bm - the bitmap handle if texturing.  ignored if flat shading

static void CollideSubmodelFacesUnsorted(poly_model *pm, bsp_info *sm) {
  int i;
  int j;
  vector colp;
  vector newp;
  float col_dist; // distance to hit point
  vector *vertex_list[32];
  vector wall_norm;
  int face_hit_type;

  // (For this reference frame)
  ns_compute_movement_AABB();

  if (ns_movement_manual_AABB(&sm->min, &sm->max)) {

    for (i = 0; i < sm->num_faces; i++) {
      if (ns_movement_manual_AABB(&sm->face_min[i], &sm->face_max[i])) {
        polyface *fp = &sm->faces[i];

        if ((GameTextures[pm->textures[fp->texnum]].flags & (TF_FLY_THRU | TF_PASS_THRU)) == 0) {
          ASSERT(fp->nverts <= 32);

          for (j = 0; j < fp->nverts; j++) {
            vertex_list[j] = &sm->verts[fp->vertnums[j]];
          }

          face_hit_type = check_line_to_face(&newp, &colp, &col_dist, &wall_norm, fvi_query_ptr->p0, fvi_query_ptr->p1,
                                             &fp->normal, vertex_list, fp->nverts, fvi_query_ptr->rad);
          if ((fvi_query_ptr->flags & FQ_OBJ_BACKFACE) && (!face_hit_type)) {
            vector face_normal = fp->normal;
            int count;

            face_normal *= -1.0f;
            for (count = 0; count < fp->nverts; count++) {
              vertex_list[fp->nverts - count - 1] = &sm->verts[fp->vertnums[count]];
            }

            face_hit_type =
                check_line_to_face(&newp, &colp, &col_dist, &wall_norm, fvi_query_ptr->p0, fvi_query_ptr->p1,
                                   &face_normal, vertex_list, fp->nverts, fvi_query_ptr->rad);
          }

          if (face_hit_type) {
            if (col_dist < fvi_collision_dist) {
              vector x;

              fvi_check_param = true;
              x = *fvi_query_ptr->p1 - *fvi_query_ptr->p0;
              vm_NormalizeVector(&x);

              fvi_hit_param = (newp - *fvi_query_ptr->p0) * x;

              if (!(fvi_hit_param > -10000000.0 && fvi_hit_param < 10000000.0)) {
                mprintf(0, "FVI Warning: fvi_hit_param seems yucky!\n");
              }

              fvi_collision_dist = col_dist;
              fvi_hit_data_ptr->num_hits = 1;

              fvi_hit_data_ptr->hit_object[0] = fvi_curobj;
              fvi_hit_data_ptr->hit_subobject[0] = sm - pm->submodel;
              fvi_hit_data_ptr->hit_type[0] = HIT_SPHERE_2_POLY_OBJECT;
              fvi_hit_data_ptr->hit_wallnorm[0] = wall_norm;
              fvi_hit_data_ptr->hit_face_pnt[0] = colp;
              fvi_hit_data_ptr->hit_face[0] = i;

              Fvi_f_normal = true;

              if (fvi_do_orient) {
                fvi_hit_data_ptr->hit_subobj_fvec = fvi_move_fvec;
                fvi_hit_data_ptr->hit_subobj_uvec = fvi_move_uvec;
                fvi_hit_data_ptr->hit_subobj_pos = newp;
              }
            }
          }
        }
      }
    }
  }
}

// instance at specified point with specified orientation
// if matrix==NULL, don't modify matrix.  This will be like doing an offset
void newstyle_StartInstanceMatrix(vector *pos, matrix *orient) {
  vector tempv, temp0, temp1;
  matrix tempm, tempm2;

  ASSERT(instance_depth < MAX_INSTANCE_DEPTH);

  instance_stack[instance_depth].m = View_matrix;
  instance_stack[instance_depth].p = View_position;
  instance_stack[instance_depth].p0 = *fvi_query_ptr->p0;
  instance_stack[instance_depth].p1 = *fvi_query_ptr->p1;
  if (fvi_do_orient) {
    instance_stack[instance_depth].fvec = fvi_move_fvec;
    instance_stack[instance_depth].uvec = fvi_move_uvec;
  }
  instance_depth++;

  // step 1: subtract object position from view position

  tempv = View_position - *pos;
  temp0 = *fvi_query_ptr->p0 - *pos;
  temp1 = *fvi_query_ptr->p1 - *pos;

  if (orient) {
    // step 2: rotate view vector through object matrix

    View_position = tempv * *orient;
    *fvi_query_ptr->p0 = temp0 * *orient;
    *fvi_query_ptr->p1 = temp1 * *orient;

    if (fvi_do_orient) {
      fvi_move_fvec = fvi_move_fvec * *orient;
      fvi_move_uvec = fvi_move_uvec * *orient;
    }

    // step 3: rotate object matrix through view_matrix (vm = ob * vm)

    tempm2 = ~*orient;

    tempm = tempm2 * View_matrix;

    View_matrix = tempm;
  }
}

// instance at specified point with specified orientation
// if angles==NULL, don't modify matrix.  This will be like doing an offset
static void newstyle_StartInstanceAngles(vector *pos, angvec *angles) {
  matrix tm;

  if (angles == NULL) {
    newstyle_StartInstanceMatrix(pos, NULL);
    return;
  }

  vm_AnglesToMatrix(&tm, angles->p, angles->h, angles->b);

  newstyle_StartInstanceMatrix(pos, &tm);
}

// pops the old context
static void newstyle_DoneInstance() {
  instance_depth--;

  ASSERT(instance_depth >= 0);

  View_position = instance_stack[instance_depth].p;
  View_matrix = instance_stack[instance_depth].m;

  *fvi_query_ptr->p0 = instance_stack[instance_depth].p0;
  *fvi_query_ptr->p1 = instance_stack[instance_depth].p1;
  if (fvi_do_orient) {
    fvi_move_fvec = instance_stack[instance_depth].fvec;
    fvi_move_uvec = instance_stack[instance_depth].uvec;
  }
}

void CollideSubmodel(poly_model *pm, bsp_info *sm, uint32_t f_render_sub) {
  // Don't collide with door housings (That is the 'room' portion of the door)
  if ((sm->flags & SOF_SHELL) || (sm->flags & SOF_FRONTFACE))
    return;

  StartPolyModelPosInstance(&sm->mod_pos);
  vector temp_vec = sm->mod_pos + sm->offset;
  newstyle_StartInstanceAngles(&temp_vec, &sm->angs);

  // Check my bit to see if I get collided with.  :)
  if (f_render_sub & (0x00000001 << (sm - pm->submodel)))
    CollideSubmodelFacesUnsorted(pm, sm);

  for (int i = 0; i < sm->num_children; i++) {
    CollideSubmodel(pm, &pm->submodel[sm->children[i]], f_render_sub);
  }

  newstyle_DoneInstance();
  DonePolyModelPosInstance();
}

void CollidePolygonModel(vector *pos, matrix *orient, int model_num, float *normalized_time, uint32_t f_render_sub) {
  poly_model *po;

  ASSERT(Poly_models[model_num].used);
  ASSERT(Poly_models[model_num].new_style);

  fvi_check_param = false;

  po = &Poly_models[model_num];

  newstyle_StartInstanceMatrix(pos, orient);

  SetModelAnglesAndPos(po, normalized_time);

  for (int i = 0; i < po->n_models; i++) {
    bsp_info *sm = &po->submodel[i];
    if (sm->parent == -1)
      CollideSubmodel(po, sm, f_render_sub);
  }

  newstyle_DoneInstance();
}

#define MULTI_ADD_SPHERE_MIN 1.4f
#define MULTI_ADD_SPHERE_MAX 2.5f

bool PolyCollideObject(object *obj) {
#ifndef NED_PHYSICS
  float normalized_time[MAX_SUBOBJECTS];
#endif
  vector temp_pos = Original_pos = View_position;
  matrix temp_orient = Original_orient = View_matrix;
  bool f_use_big_sphere = false;
  float addition;

  ASSERT(obj >= std::data(Objects) && obj <= &Objects[Highest_object_index]);

#ifndef NED_PHYSICS
  if ((Game_mode & GM_MULTI) && !(Netgame.flags & NF_USE_ACC_WEAP) && Objects[fvi_moveobj].type == OBJ_WEAPON &&
      obj->type == OBJ_PLAYER)
    f_use_big_sphere = true;
#endif

  fvi_do_orient = (Objects[fvi_moveobj].type == OBJ_WEAPON);

#ifndef NED_PHYSICS
  if (f_use_big_sphere) {
    addition = fvi_query_ptr->rad;

    if (addition < MULTI_ADD_SPHERE_MIN) {
      addition = MULTI_ADD_SPHERE_MIN;
      if (Objects[fvi_moveobj].mtype.phys_info.flags & PF_NEVER_USE_BIG_SPHERE)
        addition /= 2;
    } else if (addition > MULTI_ADD_SPHERE_MAX)
      addition = MULTI_ADD_SPHERE_MAX;

    fvi_query_ptr->rad += addition;
  }
#endif

  if (fvi_do_orient) {
    fvi_move_fvec = Objects[fvi_moveobj].orient.fvec;
    fvi_move_uvec = Objects[fvi_moveobj].orient.uvec;
  }

  Fvi_f_normal = false;

  View_position = obj->pos;
  View_matrix = obj->orient;

  ASSERT(obj->flags & OF_POLYGON_OBJECT);

#ifndef NED_PHYSICS
  if (obj->type == OBJ_PLAYER || obj->type == OBJ_ROBOT || obj->type == OBJ_DEBRIS || obj->type == OBJ_DOOR ||
      obj->type == OBJ_BUILDING || obj->type == OBJ_CLUTTER || obj->type == OBJ_BUILDING) {
    SetNormalizedTimeObj(obj, normalized_time);
    CollidePolygonModel(&obj->pos, &obj->orient, obj->rtype.pobj_info.model_num, normalized_time,
                        obj->rtype.pobj_info.subobj_flags);
  } else {
    CollidePolygonModel(&obj->pos, &obj->orient, obj->rtype.pobj_info.model_num, NULL,
                        obj->rtype.pobj_info.subobj_flags);
  }
#else
  CollidePolygonModel(&obj->pos, &obj->orient, obj->rtype.pobj_info.model_num, NULL, obj->rtype.pobj_info.subobj_flags);
#endif

  View_position = temp_pos;
  View_matrix = temp_orient;

  // Converts everything into world coordinates from submodel space
  if (fvi_check_param) {
    vector pnt = fvi_hit_data_ptr->hit_face_pnt[0];
    int mn = fvi_hit_data_ptr->hit_subobject[0];
    matrix m;
    poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];

    while (mn != -1) {
      vector tpnt;

      vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
      vm_TransposeMatrix(&m);

      tpnt = pnt * m;
      fvi_hit_data_ptr->hit_wallnorm[0] = fvi_hit_data_ptr->hit_wallnorm[0] * m;

      pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

      mn = pm->submodel[mn].parent;
    }

    fvi_hit_data_ptr->hit_face_pnt[0] = pnt;

    m = obj->orient;
    vm_TransposeMatrix(&m);

    fvi_hit_data_ptr->hit_wallnorm[0] = fvi_hit_data_ptr->hit_wallnorm[0] * m;

    // now instance for the entire object
    fvi_hit_data_ptr->hit_face_pnt[0] = fvi_hit_data_ptr->hit_face_pnt[0] * m;
    fvi_hit_data_ptr->hit_face_pnt[0] += obj->pos;

    // Now get the hit point
    vector x = *fvi_query_ptr->p1 - *fvi_query_ptr->p0;
    vm_NormalizeVector(&x);

    fvi_hit_data_ptr->hit_pnt = *fvi_query_ptr->p0 + x * fvi_hit_param;
  }

  if (f_use_big_sphere) {
    fvi_query_ptr->rad -= addition;
  }

  return Fvi_f_normal;
}
