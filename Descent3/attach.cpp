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



#include "attach.h"
#include "terrain.h"
#include "multi.h"
#include "game.h"
#include "demofile.h"
#include "polymodel.h"
#include "objinfo.h"

/*	// Determines the necessary orientation and position of the moving object
        f_use_uvec = true;
        AttachPointPos(goal_obj, goal_ap, true, &goal_pos, true, &goal_fvec, &f_use_uvec, &goal_uvec);
        goal_fvec *= -1.0f;

        // Determines the initial attach fvec of the moving object
        AttachPointPos(start_obj, start_ap, false, NULL, true, &start_fvec);

        float dot = start_fvec * goal_fvec;
        ASSERT(dot >= -1.1f && dot <= 1.1f);

        // Bounds checking to save us from floating point round-off
        if(dot > 1.0f)
                dot = 1.0f;
        if(dot < -1.0f)
                dot = -1.0f;

        //	If the dot is 1.0 we are are already perfectly aligned!
        if(dot != 1.0f)
        {
                // if it is -1.0, then we are perfectly unaligned
                if(dot != -1.0f)
                {
                        vm_CrossProduct(&rot_vec, &start_fvec, &goal_fvec);
                        vm_NormalizeVector(&rot_vec);

                        //	returns the angle between two normalized vectors and a forward vector
//			rot_angle = (vm_DeltaAngVecNorm(&start_fvec, &goal_fvec, &rot_vec)/65535.0f) * (2.0f * PI);
                        rot_angle = acos(dot);
                }
                else
                {
                        vector random_vector;
                        float dot;

                        do
                        {
                                vm_MakeRandomVector(&random_vector);
                                vm_NormalizeVector(&random_vector);

                                dot = random_vector * goal_fvec;
                        }
                        while(dot >= 1.0f || dot <= -1.0f);

                        vm_CrossProduct(&rot_vec, &random_vector, &goal_fvec);
                        vm_NormalizeVector(&rot_vec);

                        rot_angle = PI;
                }

                ConvertAxisAmountMatrix(&rot_vec, rot_angle, &rot_mat);
                vm_TransposeMatrix(&rot_mat);
                start_obj->orient *= rot_mat;
        }

        // Determines the offset of the start object's ap position (now that it is correctly aligned
        // with the fvec)
        f_use_uvec = true;
        vector temp;
        AttachPointPos(start_obj, start_ap, true, &start_pos, true, &temp, &f_use_uvec, &start_uvec);

        start_obj->pos += (goal_pos - start_pos);

        // If we have UVEC's then align them!
        if(f_use_uvec)
        {
                float dot = start_uvec * goal_uvec;
                ASSERT(dot >= -1.1f && dot <= 1.1f);

                // Bounds checking to save us from floating point round-off
                if(dot > 1.0f)
                        dot = 1.0f;
                if(dot < -1.0f)
                        dot = -1.0f;

                //	If the dot is 1.0 we are are already perfectly aligned!
                if(dot != 1.0f)
                {
                        // if it is -1.0, then we are perfectly unaligned
                        if(dot != -1.0f)
                        {
                                vm_CrossProduct(&rot_vec, &start_uvec, &goal_uvec);
                                vm_NormalizeVector(&rot_vec);

//				rot_angle = (vm_DeltaAngVecNorm(&start_uvec, &goal_uvec, &rot_vec)/65535.0f) * (2.0f *
PI); rot_angle = acos(dot);
                        }
                        else
                        {
                                vector random_vector;
                                float dot;

                                do
                                {
                                        vm_MakeRandomVector(&random_vector);
                                        vm_NormalizeVector(&random_vector);

                                        dot = random_vector * goal_uvec;
                                }
                                while(dot >= 1.0f || dot <= -1.0f);

                                vm_CrossProduct(&rot_vec, &random_vector, &goal_uvec);
                                vm_NormalizeVector(&rot_vec);

                                rot_angle = PI;
                        }

                        ConvertAxisAmountMatrix(&rot_vec, rot_angle, &rot_mat);
                        vm_TransposeMatrix(&rot_mat);
                        start_obj->orient *= rot_mat;
                }
        }
*/

// Finds the position of a attach point on an object
// The uvec is optional as most attaching objects don't need at complete orientation set (only an fvec)
static bool AttachPointPos(object *obj, char ap, bool f_compute_pos, vector *attach_pos, bool f_compute_fvec,
                           vector *attach_fvec, bool *f_computed_uvec = NULL, vector *attach_uvec = NULL);

static void ConvertAxisAmountMatrix(vector *n, float w, matrix *rotmat);

// Adds and subtracts from mass from connections and disconnections
static void AttachPropagateMass(object *child, bool f_attach = true);

static void ProprogateUltimateAttachParent(object *parent, int ultimate_handle);

// Finds the position of a attach point on an object
// The uvec is optional as most attaching objects don't need at complete orientation set (only an fvec)
bool AttachPointPos(object *obj, char ap, bool f_compute_pos, vector *attach_pos, bool f_compute_fvec,
                    vector *attach_fvec, bool *f_computed_uvec, vector *attach_uvec) {
  poly_model *pm;
  vector pnt;
  vector normal;
  vector uvec;
  matrix m;
  int mn; // submodel number
  float normalized_time[MAX_SUBOBJECTS];

  pm = &Poly_models[obj->rtype.pobj_info.model_num];

  if (ap < 0 || ap >= pm->n_attach) {
    mprintf(0, "WARNING: No ap %d on object %d.\n", ap, OBJNUM(obj));
    return false;
  }

  SetNormalizedTimeObj(obj, normalized_time);
  SetModelAnglesAndPos(pm, normalized_time);

  if (f_compute_pos)
    pnt = pm->attach_slots[ap].pnt;

  if (f_compute_fvec) {
    normal = pm->attach_slots[ap].norm;
    //	mprintf(0, "Original fvec is %f long.\n", vm_GetMagnitude(&normal));
  }

  if (pm->attach_slots[ap].f_uvec && attach_uvec && f_computed_uvec) {
    *f_computed_uvec = true;
    uvec = pm->attach_slots[ap].uvec;

    //	mprintf(0, "Original uvec is %f long.\n", vm_GetMagnitude(&uvec));
  } else if (f_computed_uvec) {
    *f_computed_uvec = false;
  }

  mn = pm->attach_slots[ap].parent;

  // Instance up the tree for this gun
  while (mn != -1) {
    vector tpnt;

    vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
    vm_TransposeMatrix(&m);

    if (f_compute_pos)
      tpnt = pnt * m;

    if (f_compute_fvec)
      normal = normal * m;

    if (f_computed_uvec && *f_computed_uvec) {
      uvec = uvec * m;
    }

    if (f_compute_pos)
      pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

    mn = pm->submodel[mn].parent;
  }

  // now instance for the entire object
  m = obj->orient;
  vm_TransposeMatrix(&m);

  if (f_compute_pos)
    *attach_pos = pnt * m;

  if (f_compute_fvec) {
    *attach_fvec = normal * m;
    //	mprintf(0, "Rotated fvec is %f long.\n", vm_GetMagnitude(attach_fvec));
  }

  if (f_computed_uvec && *f_computed_uvec) {
    *attach_uvec = uvec * m;
    //	mprintf(0, "Rotated uvec is %f long.\n", vm_GetMagnitude(attach_uvec));
  }

  if (f_compute_pos)
    *attach_pos += obj->pos;

  return true;
}

void ConvertAxisAmountMatrix(vector *n, float w, matrix *rotmat) {
  float s;
  float c;
  float t;

  //	float scale = *w/.0001f;
  // float w_n = .0001f;
  // vector s_result;

  if (w == 0.0f) {
    matrix temp = IDENTITY_MATRIX;

    *rotmat = temp;
    return;
  }

  s = sin(w);
  c = cos(w);
  t = 1.0f - c;

  const float sx = s * n->x;
  const float sy = s * n->y;
  const float sz = s * n->z;
  const float txy = t * n->x * n->y;
  const float txz = t * n->x * n->z;
  const float tyz = t * n->y * n->z;
  const float txx = t * n->x * n->x;
  const float tyy = t * n->y * n->y;
  const float tzz = t * n->z * n->z;

  rotmat->rvec.x = txx + c;
  rotmat->rvec.y = txy - sz;
  rotmat->rvec.z = txz + sy;
  rotmat->uvec.x = txy + sz;
  rotmat->uvec.y = tyy + c;
  rotmat->uvec.z = tyz - sx;
  rotmat->fvec.x = txz - sy;
  rotmat->fvec.y = tyz + sx;
  rotmat->fvec.z = tzz + c;
}

bool AttachDoPosOrientRad(object *parent, char p_ap, object *child, float rad_percent, vector *pos) {
  vector attach_pos;
  vector attach_fvec;

  if (AttachPointPos(parent, p_ap, true, &attach_pos, true, &attach_fvec)) {
    vector child_ap_pos = child->pos - attach_fvec * (rad_percent * child->size);

    *pos = (child_ap_pos - attach_pos) + parent->pos;
    return true;
  } else {
    return false;
  }
}

bool AttachDoPosOrient(object *parent, char parent_ap, object *child, char child_ap, bool f_parent, bool f_move_obj,
                       vector *pos, matrix *orient, bool f_dropping_off) {
  vector goal_fvec;
  vector goal_uvec;
  vector goal_pos;

  bool f_use_uvec = true;

  vector start_fvec;
  vector start_uvec;
  vector start_pos;

  object *goal_obj;
  object *start_obj;

  matrix rot_mat;

  char goal_ap;
  char start_ap;

  if (f_parent) {
    goal_obj = child;
    goal_ap = child_ap;

    start_obj = parent;
    start_ap = parent_ap;
  } else {
    goal_obj = parent;
    goal_ap = parent_ap;

    start_obj = child;
    start_ap = child_ap;
  }

  vector saved_pos = start_obj->pos;
  matrix saved_orient = start_obj->orient;

  f_use_uvec = true;
  AttachPointPos(goal_obj, goal_ap, true, &goal_pos, true, &goal_fvec, &f_use_uvec, &goal_uvec);
  goal_fvec *= -1.0f;

  f_use_uvec = true;
  if (f_dropping_off) {
    object *attached_obj = ObjGet(start_obj->attach_children[0]);
    ASSERT(attached_obj);
    AttachPointPos(attached_obj, start_ap, true, &start_pos, true, &start_fvec, &f_use_uvec, &start_uvec);
  } else {
    AttachPointPos(start_obj, start_ap, true, &start_pos, true, &start_fvec, &f_use_uvec, &start_uvec);
  }

  vm_NormalizeVector(&start_fvec);
  vm_NormalizeVector(&start_uvec);
  vm_NormalizeVector(&goal_fvec);
  vm_NormalizeVector(&goal_uvec);

  matrix start_m;
  matrix goal_m;

  vm_VectorToMatrix(&start_m, &start_fvec, &start_uvec, NULL);
  vm_VectorToMatrix(&goal_m, &goal_fvec, &goal_uvec, NULL);

  matrix sot;
  matrix srt;

  sot = start_obj->orient;
  vm_TransposeMatrix(&sot);

  srt = sot * start_m;
  vm_TransposeMatrix(&srt);

  rot_mat = sot * goal_m * srt;

  start_obj->orient *= rot_mat;
  vm_Orthogonalize(&start_obj->orient);

  if (f_dropping_off) {
    object *attached_obj = ObjGet(start_obj->attach_children[0]);
    ASSERT(attached_obj);
    AttachPointPos(attached_obj, start_ap, true, &start_pos, false, NULL, NULL, NULL);
  } else {
    AttachPointPos(start_obj, start_ap, true, &start_pos, false, NULL, NULL, NULL);
  }
  start_obj->pos += (goal_pos - start_pos);

  if (pos)
    *pos = start_obj->pos;

  if (orient)
    *orient = start_obj->orient;

  if (f_move_obj) {
    int room = goal_obj->roomnum;
    if (room != -1) {
      if (ROOMNUM_OUTSIDE(room)) {
        room = GetTerrainRoomFromPos(&start_obj->pos);
        if (room == -1) {
          SetObjectDeadFlag(start_obj);
          return false;
        }
      }

      ObjSetPos(start_obj, &start_obj->pos, room, &start_obj->orient, false);

      return true;
    } else {
      SetObjectDeadFlag(start_obj);
      return false;
    }
  } else {
    start_obj->pos = saved_pos;
    start_obj->orient = saved_orient;
  }

  return true;
}

// Adds and subtracts from mass from connections and disconnections
void AttachPropagateMass(object *child, bool f_attach) {
  object *new_parent;

  if (!child)
    return;

  do {
    new_parent = ObjGet(child->attach_parent_handle);
    ASSERT(new_parent);
    if (!new_parent) {
      return;
    }

    float mass;

    mass = Object_info[child->id].phys_info.mass;

    if (mass < 0.0f)
      mass = 0.0f;

    ASSERT(new_parent->mtype.phys_info.mass >= 0.0f && mass >= 0.0f);

    if (f_attach)
      new_parent->mtype.phys_info.mass += mass;
    else
      new_parent->mtype.phys_info.mass -= mass;

    if (new_parent->mtype.phys_info.mass < 0.0f) {
      new_parent->mtype.phys_info.mass = 0.0f;
    }

    child = new_parent;

    ASSERT(new_parent->mtype.phys_info.mass >= 0.0f);
  } while (child->flags & OF_ATTACHED);
}

static inline void ComputeUltimateAttachParent(object *child) {
  object *cur_obj = child;

  do {
    child->attach_ultimate_handle = cur_obj->attach_parent_handle;
    cur_obj = ObjGet(child->attach_ultimate_handle);
    ASSERT(cur_obj);

  } while (cur_obj->flags & OF_ATTACHED);
}

void ProprogateUltimateAttachParent(object *parent, int ultimate_handle) {
  int i;

  ASSERT(parent);
  ASSERT(ultimate_handle != OBJECT_HANDLE_NONE);

  poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];

  if (!parent->attach_children)
    return;

  for (i = 0; i < parent_pm->n_attach; i++) {
    object *child;

    if ((child = ObjGet(parent->attach_children[i])) != NULL) {
      child->attach_ultimate_handle = ultimate_handle;
      ProprogateUltimateAttachParent(child, ultimate_handle);
    }
  }
}

// Attaches 2 objects via attach points on each.  The f_used_aligned allows for an aligned connection.
// NOTE: The child always moves to the parent
bool AttachObject(object *parent, char parent_ap, object *child, char child_ap, bool f_use_aligned) {
  ASSERT(parent);
  ASSERT(child);

  poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
  poly_model *child_pm = &Poly_models[child->rtype.pobj_info.model_num];

  if (parent_ap < 0 || parent_ap >= parent_pm->n_attach) {
    mprintf(0, "ATTACH: Parent AP invalid\n");
    return false;
  }

  if (child->flags & OF_ATTACHED) {
    mprintf(0, "ATTACH: Child already attached to someone\n");
    return false;
  }

  if (child_ap >= 0 && child_ap < child_pm->n_attach) {
    if (AttachDoPosOrient(parent, parent_ap, child, child_ap, false)) {
      child->flags |= OF_ATTACHED;
      child->attach_type = AT_ALIGNED;
      child->attach_index = child_ap;
      child->attach_parent_handle = parent->handle;

      parent->attach_children[parent_ap] = child->handle;
      ComputeUltimateAttachParent(child);
      ProprogateUltimateAttachParent(child, child->attach_ultimate_handle);

      AttachPropagateMass(child);

      AttachUpdateSubObjects(child);
      if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
        MultiSendAttach(parent, parent_ap, child, child_ap, f_use_aligned);
      }
      if (Demo_flags == DF_RECORDING) {
        DemoWriteAttachObj(parent, parent_ap, child, child_ap, f_use_aligned);
      }

      return true;
    }

    mprintf(0, "ATTACH: AP attach failed\n");
    return false;
  }

  mprintf(0, "ATTACH: Child AP (%d) - child only has %d attach points\n", child_ap, child_pm->n_attach);
  return false;
}

// Attaches a child object to a parent object by a percent of the radius of the child.
// NOTE: The child always moves to the parent and not the reverse
bool AttachObject(object *parent, char parent_ap, object *child, float percent_rad) {
  ASSERT(parent);
  ASSERT(child);

  poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
  poly_model *child_pm = &Poly_models[parent->rtype.pobj_info.model_num];

  if (parent_ap < 0 || parent_ap >= parent_pm->n_attach) {
    mprintf(0, "ATTACH: Parent AP invalid\n");
    return false;
  }

  if (child->flags & OF_ATTACHED) {
    mprintf(0, "ATTACH: Child already attached to someone\n");
    return false;
  }

  if (percent_rad >= 0.0f) {
    vector attach_pos;
    vector attach_fvec;

    if (AttachPointPos(parent, parent_ap, true, &attach_pos, true, &attach_fvec)) {
      child->flags |= OF_ATTACHED;
      child->attach_type = AT_RAD;
      child->attach_dist = percent_rad * child->size;
      child->attach_parent_handle = parent->handle;

      parent->attach_children[parent_ap] = child->handle;
      ComputeUltimateAttachParent(child);
      ProprogateUltimateAttachParent(child, child->attach_ultimate_handle);

      AttachPropagateMass(child);

      vector new_child_pos = attach_pos + attach_fvec * child->attach_dist;

      int room = parent->roomnum;
      if (ROOMNUM_OUTSIDE(room))
        room = GetTerrainRoomFromPos(&new_child_pos);

      ObjSetPos(child, &new_child_pos, room, NULL, false);

      AttachUpdateSubObjects(child);
      if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
        MultiSendAttachRad(parent, parent_ap, child, percent_rad);
      }
      if (Demo_flags == DF_RECORDING) {
        DemoWriteAttachObjRad(parent, parent_ap, child, percent_rad);
      }

      return true;
    }

    mprintf(0, "ATTACH: RAD attach failed\n");
    return false;
  }

  mprintf(0, "ATTACH: Child percent rad is invalid\n");
  return false;
}

// Updates the position of all the subobjects off the ultimate attach parent
void AttachUpdateSubObjects(object *parent) {
  poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
  int i;

#ifdef _DEBUG
  if (!Game_update_attach)
    return;
#endif

  if (parent->attach_children == NULL)
    return;

  for (i = 0; i < parent_pm->n_attach; i++) {
    object *child;

    if ((child = ObjGet(parent->attach_children[i])) != NULL) {
      ASSERT(child->flags & OF_ATTACHED);

      child->mtype.phys_info.velocity = parent->mtype.phys_info.velocity;
      child->mtype.phys_info.rotvel = parent->mtype.phys_info.rotvel;

      switch (child->attach_type) {
      case AT_UNALIGNED:
        AttachDoPosOrient(parent, i, child, child->attach_index, false);
        break;
      case AT_ALIGNED:
        AttachDoPosOrient(parent, i, child, child->attach_index, false);
        break;
      case AT_RAD: {
        vector attach_pos;
        vector attach_fvec;

        if (AttachPointPos(parent, i, true, &attach_pos, true, &attach_fvec)) {
          vector new_child_pos = attach_pos + attach_fvec * child->attach_dist;

          int room = parent->roomnum;
          if (ROOMNUM_OUTSIDE(room))
            room = GetTerrainRoomFromPos(&new_child_pos);

          ObjSetPos(child, &new_child_pos, room, NULL, false);
        } else {
          Int3(); // Get chris
        }
      } break;
      default:
        Int3(); // Non-supported attach type - Get Chris
      }

      AttachUpdateSubObjects(child);
    }
  }
}

// Unattaches an object from its parent
bool UnattachFromParent(object *child) {
  if (!(child->flags & OF_ATTACHED))
    return false;

  AttachPropagateMass(child, false);

  object *parent = ObjGet(child->attach_parent_handle);
  ASSERT(parent);

  poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
  int i;

  for (i = 0; i < parent_pm->n_attach; i++) {
    if (parent->attach_children[i] == child->handle) {
      parent->attach_children[i] = OBJECT_HANDLE_NONE;
      break;
    }
  }

  //	ASSERT(i < parent_pm->n_attach);  // Didn't find its parent?  Get chris!

  child->flags &= ~OF_ATTACHED;
  child->attach_parent_handle = OBJECT_HANDLE_NONE;
  child->attach_ultimate_handle = OBJECT_HANDLE_NONE;

  ProprogateUltimateAttachParent(child, child->handle);
  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
    MultiSendUnattach(child);
  }
  if (Demo_flags == DF_RECORDING) {
    DemoWriteUnattachObj(child);
  }

  return true;
}

// Unattaches a child from an attach point
bool UnattachChild(object *parent, char parent_ap) {
  object *child;

  if ((child = ObjGet(parent->attach_children[parent_ap])) != NULL) {
    return UnattachFromParent(child);
  }

  return false;
}

// Unattaches all children from a parent object
bool UnattachChildren(object *parent) {
  poly_model *parent_pm = &Poly_models[parent->rtype.pobj_info.model_num];
  int i;

  if (!parent->attach_children)
    return false;

  for (i = 0; i < parent_pm->n_attach; i++) {
    object *child;

    if ((child = ObjGet(parent->attach_children[i])) != NULL) {
      UnattachFromParent(child);
    }
  }

  return true;
}
