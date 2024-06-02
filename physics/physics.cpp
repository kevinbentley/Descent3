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

#include <stdlib.h>
#include <memory.h>

#include <limits>

#include "object.h"
#include "physics.h"
#include "collide.h"
#include "findintersection.h"
#include "vecmat.h"
#include "game.h"
#include "terrain.h"
#include "descent.h"
#include "weapon.h"
#include "polymodel.h"
#include "fireball.h"
#include "damage.h"
#include "gameevent.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "viseffect.h"
#include "multi.h"
#include "attach.h"
#include "D3ForceFeedback.h"
#include "player.h"
#include "demofile.h"
#include "vibeinterface.h"

// Global variables for physics system
uint8_t Default_player_terrain_leveling = 0;
uint8_t Default_player_room_leveling = 0;

// Maximum iterations thru the simulation loop NOTE: It is assumed that the player loops >= non-player loops
#define MAX_PLAYER_SIM_LOOPS 9
#define MAX_NON_PLAYER_SIM_LOOPS 5

#define CEILING_POWERUP_DELTA 30.0f

#define WIGGLE_FALLOFF_TIME 2.0

int Physics_normal_counter;
int Physics_normal_looping_counter;
int Physics_walking_counter;
int Physics_walking_looping_counter;
int Physics_vis_counter;

#ifdef _DEBUG
// This will allow us to debug physics in a better way.
struct sim_loop_info {
  vector start_pos;
  physics_info phys_info; // At beginnning of loop
  fvi_info hit_info;      // Hit information returned by FVI
};

sim_loop_info sim_loop_record[MAX_PLAYER_SIM_LOOPS];
#endif

#ifdef _DEBUG
int Physics_player_verbose = 0;
#endif

#define PHYSICS_GROUND_TOLERANCE 0.0001f
#define DAMP_ANG 1.0f // chrishack -- this is probably too tight and should be an int not a float
#define MAX_OBJECT_VEL 100000.0f
int Physics_cheat_flag = 0;
extern char BounceCheat;

int PhysicsLinkList[MAX_OBJECTS];
int Physics_NumLinked = 0;

// Current strength of gravity
float Gravity_strength = -32.2f; // Meters/second^2

void DoPhysLinkedFrame(object *obj) {
  object *parent = ObjGet(obj->mtype.obj_link_info.parent_handle);
  matrix new_orient;
  vector new_pos;

  if (parent && parent->type != OBJ_GHOST && parent->type != OBJ_DUMMY) {
    poly_model *pm;
    vector pnt;
    vector fvec;
    vector uvec;
    matrix m;
    int mn; // submodel number
    float normalized_time[MAX_SUBOBJECTS];

    pm = &Poly_models[parent->rtype.pobj_info.model_num];
    ASSERT(pm->used);

    SetNormalizedTimeObj(parent, normalized_time);

    SetModelAnglesAndPos(pm, normalized_time);

    pnt = obj->mtype.obj_link_info.pos;
    fvec = obj->mtype.obj_link_info.fvec;
    uvec = obj->mtype.obj_link_info.uvec;

    mn = obj->mtype.obj_link_info.sobj_index;

    if (mn < 0 || mn >= pm->n_models) {
      mprintf(0, "Caught physics link bug!\n");
      SetObjectDeadFlag(obj);
      return;
    }

    // Instance up the tree for this gun
    while (mn != -1) {
      vector tpnt;

      vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
      vm_TransposeMatrix(&m);

      tpnt = pnt * m;
      fvec = fvec * m;
      uvec = uvec * m;

      pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

      mn = pm->submodel[mn].parent;
    }

    // now instance for the entire object
    m = parent->orient;
    vm_TransposeMatrix(&m);

    new_pos = pnt * m;
    fvec = fvec * m;
    uvec = uvec * m;

    vm_VectorToMatrix(&new_orient, &fvec, &uvec, NULL);

    new_pos += parent->pos;

    ObjSetPos(obj, &new_pos, parent->roomnum, &new_orient, false);
  } else {
    SetObjectDeadFlag(obj);
  }
}

bool PhysCalcGround(vector *ground_point, vector *ground_normal, object *obj, int ground_num) {
  poly_model *pm;
  vector pnt;
  vector normal;
  matrix m;
  int mn; // submodel number
  float normalized_time[MAX_SUBOBJECTS];
  bool f_good_gp = true;

  if (obj->render_type != RT_POLYOBJ && obj->type != OBJ_PLAYER) {
    // mprintf(0,"Object type %d is not a polyobj!\n",obj->type);

    if (ground_point)
      *ground_point = obj->pos;
    if (ground_normal)
      *ground_normal = obj->orient.fvec;

    return false;
  }

  pm = &Poly_models[obj->rtype.pobj_info.model_num];

  if (pm->n_ground == 0) {
    mprintf(0, "WARNING: Object with no weapons is firing.\n", ground_num);

    if (ground_point)
      *ground_point = obj->pos;
    if (ground_normal)
      *ground_normal = obj->orient.fvec;

    return false;
  }

  SetNormalizedTimeObj(obj, normalized_time);

  SetModelAnglesAndPos(pm, normalized_time);

  if (ground_num < 0 || ground_num >= pm->n_ground) {
    mprintf(0, "WARNING: Bashing ground num %d to 0.\n", ground_num);
    ground_num = 0;
    f_good_gp = false;
  }

  pnt = pm->ground_slots[ground_num].pnt;
  normal = pm->ground_slots[ground_num].norm;
  mn = pm->ground_slots[ground_num].parent;

  // Instance up the tree for this ground
  while (mn != -1) {
    vector tpnt;

    vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
    vm_TransposeMatrix(&m);

    tpnt = pnt * m;
    normal = normal * m;

    pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

    mn = pm->submodel[mn].parent;
  }

  m = obj->orient;
  vm_TransposeMatrix(&m);

  if (ground_point)
    *ground_point = pnt * m;
  if (ground_normal)
    *ground_normal = normal * m;

  if (ground_point)
    *ground_point += obj->pos;

  return f_good_gp;
}

// Applies rotational thrust over at delta time
void PhysicsApplyConstRotForce(object &objp, const vector &rotforce, vector &rotvel, float deltaTime) {
  const double drag = objp.mtype.phys_info.rotdrag;
  const double mass = objp.mtype.phys_info.mass;

  if (mass < std::numeric_limits<double>::epsilon() || drag < std::numeric_limits<double>::epsilon()) {
    // Invalid mass/drag
    rotvel += rotforce * deltaTime;
    return;
  }

  // Standard angular motion with a linear air drag (drag is proportional to angular velocity)
  const double oneOverDrag = 1.0 / drag;
  const double rotForceOverDrag[3] = {double(rotforce.x) * oneOverDrag, double(rotforce.y) * oneOverDrag,
                                      double(rotforce.z) * oneOverDrag};
  const double dragOverMass = drag / mass;
  const double expDoMDt = exp(-dragOverMass * double(deltaTime));

  double newRotVel[3];
  newRotVel[0] = (double(rotvel.x) - rotForceOverDrag[0]) * expDoMDt + rotForceOverDrag[0];
  newRotVel[1] = (double(rotvel.y) - rotForceOverDrag[1]) * expDoMDt + rotForceOverDrag[1];
  newRotVel[2] = (double(rotvel.z) - rotForceOverDrag[2]) * expDoMDt + rotForceOverDrag[2];

  // set the new rotational velocity
  rotvel.x = static_cast<float>(newRotVel[0]);
  rotvel.y = static_cast<float>(newRotVel[1]);
  rotvel.z = static_cast<float>(newRotVel[2]);
}

// Applies a linear force over time.  --Like gravity or thrust
void PhysicsApplyConstantForce(const object &objp, vector &newPos, vector &newVel, vector &movementVec,
                               const vector &force, float deltaTime) {
  const vector &pos = objp.pos;
  const vector &vel = objp.mtype.phys_info.velocity;
  const double drag = static_cast<double>(objp.mtype.phys_info.drag);
  const double mass = static_cast<double>(objp.mtype.phys_info.mass);

  if (mass < std::numeric_limits<double>::epsilon() || drag < std::numeric_limits<double>::epsilon()) {
    // No Mass/Drag
    movementVec = (vel * deltaTime) + (force * (0.5f * deltaTime * deltaTime));
    newPos = pos + movementVec;
    newVel = vel + force * deltaTime;
    return;
  }

  // Standard motion with a linear air drag (drag is proportional to velocity)
  const double dt = static_cast<double>(deltaTime);
  const double oneOverDrag = 1.0 / drag;
  const double massOverDrag = mass / drag;
  const double forceOverDrag[3] = {force.x * oneOverDrag, force.y * oneOverDrag, force.z * oneOverDrag};
  const double objVel[3] = {static_cast<double>(vel.x), static_cast<double>(vel.y), static_cast<double>(vel.z)};
  const double expDoMDt = exp((-1.0 / massOverDrag) * dt);

  newPos.x = static_cast<float>(static_cast<double>(pos.x) + forceOverDrag[0] * dt +
                                massOverDrag * (objVel[0] - forceOverDrag[0]) * (1.0 - expDoMDt));
  newPos.y = static_cast<float>(static_cast<double>(pos.y) + forceOverDrag[1] * dt +
                                massOverDrag * (objVel[1] - forceOverDrag[1]) * (1.0 - expDoMDt));
  newPos.z = static_cast<float>(static_cast<double>(pos.z) + forceOverDrag[2] * dt +
                                massOverDrag * (objVel[2] - forceOverDrag[2]) * (1.0 - expDoMDt));
  movementVec = newPos - pos;
  newVel.x = static_cast<float>((objVel[0] - forceOverDrag[0]) * expDoMDt + forceOverDrag[0]);
  newVel.y = static_cast<float>((objVel[1] - forceOverDrag[1]) * expDoMDt + forceOverDrag[1]);
  newVel.z = static_cast<float>((objVel[2] - forceOverDrag[2]) * expDoMDt + forceOverDrag[2]);
}

// Banks an object as it turns (we counteract this and then reapply it when we
// actually do the turn -- cool)
void set_object_turnroll(object *obj, vector *rotvel, angle *turnroll) {
  float desired_bank;
  angle desired_bank_angle;

  desired_bank = -(rotvel->y) * obj->mtype.phys_info.turnroll_ratio;

  // If desired bank > 32000, we will rotate the ship in weird ways.  Should limit turn-roll to 32000 if this
  // ever occurs.  BTW  This is where the limiter should be placed.
  if (fabs(desired_bank) > 32000.0) {
    if (desired_bank < 0.0)
      desired_bank = -32000.0f;
    else
      desired_bank = 32000.0f;
  }

  if (desired_bank > -1.0) // accounts for -.9999 this is rounded to 0 in a float to int conversion
    desired_bank_angle = desired_bank;
  else
    desired_bank_angle = 65535 + desired_bank;

  if (*turnroll != desired_bank_angle) {
    int delta_ang;
    int max_roll;

    max_roll = obj->mtype.phys_info.max_turnroll_rate * Frametime;

    if (*turnroll > 32000)
      delta_ang = desired_bank - (*turnroll - 65535);
    else
      delta_ang = desired_bank - *turnroll;

    if (labs(delta_ang) > max_roll)
      if (delta_ang > 0)
        *turnroll += max_roll;
      else
        *turnroll -= max_roll;
    else
      *turnroll = desired_bank_angle;
  } else
    *turnroll = desired_bank_angle;
}

// Maximum number of objects that we already hit.
#define MAX_IGNORE_OBJS 100

// When leveling non-player objects - how many angles per sec. do they correct with.
#define MAX_LEVEL_ANGLES_PER_SEC 30000.0f

// Base scaler for pitch scaling of autoleveling
#define MAX_AUTOLEVEL_TILT_ANGLE 11000

// Multiplier for newbie autoleveling scaling of tilt angle
#define NEWBIE_AUTOLEVEL_TILT_ANGLE_SCALAR 1.25f

// How long a newbie sits there before the pitch leveling kicks in
#define NEWBIE_PITCH_LEVEL_TIME 1.5f

#define BANK_AUTOLEVEL_SPEED_SCALAR 2.0

// Rotational simulator the updates orient, rotvel, and turnroll
// (using these original values + frametime + rotthrust)
bool PhysicsDoSimRot(object *obj, float frame_time, matrix *orient, vector *rotthrust, vector *rotvel,
                     angle *turnroll) {
  angvec tangles;
  matrix rotmat;
  physics_info *pi;
  bool f_leveling = false;
  float max_tilt_angle = 0;
  bool f_newbie_leveling = false;

  if (frame_time <= 0.0)
    return false; // chrishack

  pi = &obj->mtype.phys_info;

  if (obj == Player_object && obj->control_type != CT_AI) {
    max_tilt_angle = MAX_AUTOLEVEL_TILT_ANGLE;

    if (OBJECT_OUTSIDE(obj)) {
      if (Default_player_terrain_leveling) {
        f_leveling = true;
        if (Default_player_terrain_leveling > 1) {
          max_tilt_angle *= NEWBIE_AUTOLEVEL_TILT_ANGLE_SCALAR;
          f_newbie_leveling = true;
        }
      }
    } else {
      if (Default_player_room_leveling) {
        f_leveling = true;
        if (Default_player_room_leveling > 1) {
          max_tilt_angle *= NEWBIE_AUTOLEVEL_TILT_ANGLE_SCALAR;
          f_newbie_leveling = true;
        }
      }
    }
  } else {
    if (pi->flags & PF_LEVELING)
      f_leveling = true;
  }

  // Fixed rate rotaters
  if (obj->mtype.phys_info.flags & PF_FIXED_ROT_VELOCITY) {
    tangles.p = (int16_t)(rotvel->x * frame_time);
    tangles.h = (int16_t)(rotvel->y * frame_time);
    tangles.b = (int16_t)(rotvel->z * frame_time);

    vm_AnglesToMatrix(&rotmat, tangles.p, tangles.h, tangles.b);
    *orient = *orient * rotmat; // ObjSetOrient below

    vm_Orthogonalize(orient); // Rest done after call

    return true;
  }

  //	if(!(f_leveling) && fabs(rotthrust->x) < .000001 && fabs(rotthrust->y) < .000001 && fabs(rotthrust->z) <
  //.000001)
  //	{
  //		if(!(fabs(rotvel->x) > .000001 || fabs(rotvel->y) > .000001 || fabs(rotvel->z) > .000001 || *turnroll !=
  // 0))
  //		{
  //			return false;
  //		}
  //	}

  // now rotate object
  // unrotate object for bank caused by turn
  if (*turnroll != 0) {
    tangles.p = tangles.h = 0;
    tangles.b = -(*turnroll);
    vm_AnglesToMatrix(&rotmat, tangles.p, tangles.h, tangles.b);
    // Apply rotation matrix to the orientation matrix
    *orient = *orient * rotmat; // ObjSetOrient is below
  }

  // Auto-leveling
  if ((f_leveling) && (obj->type != OBJ_PLAYER)) {
    if (fabs(rotthrust->z) < 100.0f) {
      if ((fabs(rotvel->z) < 1500.0f) /*&& (pi->turnroll <= 10 || pi->turnroll >= 65535 - 10)*/) {
        angvec ang;
        vector fvec;
        int bound;

        // f_leveling = true;
        // pi->turnroll = 0;

        // extract angles from a matrix
        vm_ExtractAnglesFromMatrix(&ang, orient);

        if ((pi->flags & PF_TURNROLL) && *turnroll) {
          bound = *turnroll;
          if (bound > 32768) {
            bound = 65535 - bound;
          }
        } else {
          bound = 10;
        }

        if (ang.b > bound && ang.b < 65535 - bound) // About 1 degree
        {
          float scale;

          // Scale on pitch
          if (ang.p < 32768) {
            scale = abs(16834 - (int)ang.p) / 16384.0f;
          } else {
            scale = abs(49152 - (int)ang.p) / 16384.0f;
          }

          //					mprintf(0, "scale %f, ", scale);

          if (ang.b < 32768) {
            float al_rate = scale * MAX_LEVEL_ANGLES_PER_SEC * (1.0f - (abs(16834 - (int)ang.b) / 16384.0f));

            if (al_rate < scale * 5000.0f) {
              al_rate = scale * 5000.0f;
            }

            al_rate *= frame_time;

            if (al_rate > ang.b)
              al_rate = ang.b;

            //						mprintf(0, "L al_rate %f\n", al_rate);

            ang.b -= al_rate;

          } else {
            float al_rate = scale * MAX_LEVEL_ANGLES_PER_SEC * (1.0f - (abs(16384 - ((int)ang.b - 32768)) / 16384.0f));

            if (al_rate < scale * 5000.0f) {
              al_rate = scale * 5000.0f;
            }

            al_rate *= frame_time;

            if (al_rate > 65535 - ang.b)
              al_rate = 65535 - ang.b;

            //						mprintf(0, "G al_rate %f\n", al_rate);

            ang.b += al_rate;
          }

          fvec = orient->fvec;

          vm_AnglesToMatrix(orient, ang.p, ang.h, ang.b);
        }
      }
    }
  } else if ((f_leveling) && (obj->type == OBJ_PLAYER)) {
    bool f_pitch_leveled = false;
    bool f_player_fired_recently = false;
    int i;

    for (i = 0; i < 21; i++) {
      if (obj->dynamic_wb[i].last_fire_time + NEWBIE_PITCH_LEVEL_TIME > Gametime) {
        f_player_fired_recently = true;
        f_newbie_leveling = false;
        break;
      }
    }

    if (!f_player_fired_recently && f_newbie_leveling &&
        (Players[obj->id].last_thrust_time + NEWBIE_PITCH_LEVEL_TIME < Gametime)) {
      if (1) {
        angvec ang;
        int bound;

        // f_leveling = true;
        // pi->turnroll = 0;

        // extract angles from a matrix
        vm_ExtractAnglesFromMatrix(&ang, orient);

        bound = 750;

        // About 1 degree -- front or back
        if ((ang.p > bound) && (ang.p < 65535 - bound) && // Forward
            abs(ang.p - 32768) > bound)                   // Backward
        {
          float scale;
          f_pitch_leveled = true;

          if (obj->orient.uvec.y < 0.0f) {
            ang.p += 16384;
          }

          scale = 1.05f - fabs(obj->orient.uvec.y);
          //					scale *= scale;

          if (scale > 1.0)
            scale = 1.0;

          if (ang.p < 16834) {
            //						float temp_scale = (1.04f - ((16834 - ang.p)/16834.0f));
            //						scale = temp_scale * temp_scale;
            rotthrust->x -= scale * obj->mtype.phys_info.full_rotthrust;
            //						mprintf(0, "1 scale %f\n", scale);
          } else if (ang.p < 32768) {
            //						float temp_scale = (1.04f - ((ang.p - 16834)/16834.0f));
            //						scale = temp_scale * temp_scale;
            rotthrust->x += scale * obj->mtype.phys_info.full_rotthrust;
            //						mprintf(0, "2 scale %f\n", scale);
          } else if (ang.p < 49152) {
            //						float temp_scale = (1.04f - ((49152 - ang.p)/16834.0f));
            //						scale = temp_scale * temp_scale;
            rotthrust->x -= scale * obj->mtype.phys_info.full_rotthrust;
            //						mprintf(0, "3 scale %f\n", scale);
          } else {
            //						float temp_scale = (1.04f - ((ang.p - 49152)/16834.0f));
            //						scale = temp_scale * temp_scale;
            rotthrust->x += scale * obj->mtype.phys_info.full_rotthrust;
            //						mprintf(0, "4 scale %f\n", scale);
          }
        }
      }
    }

    if (!f_pitch_leveled && fabs(rotthrust->z) < 100.0f) {
      if (1) ///*&& (pi->turnroll <= 10 || pi->turnroll >= 65535 - 10)*/)
      {
        angvec ang;
        int bound;

        // f_leveling = true;
        // pi->turnroll = 0;

        // extract angles from a matrix
        vm_ExtractAnglesFromMatrix(&ang, orient);

        if ((ang.p < 32768 && (abs((int)ang.p - (int)16834) > max_tilt_angle)) ||
            (ang.p >= 32768 && (abs((int)ang.p - (int)49152) > max_tilt_angle))) {

          if ((pi->flags & PF_TURNROLL) && *turnroll) {
            bound = *turnroll;
            if (bound > 32768) {
              bound = 65535 - bound;
            }
          } else {
            bound = 10;
          }

          if (ang.b > bound && ang.b < 65535 - bound) // About 1 degree
          {
            float scale;
            //						vector level_rotthrust = Zero_vector;

            // Scale on pitch
            if (ang.p < 32768) {
              scale = (abs(16834 - (int)ang.p) - max_tilt_angle) / (16384.0f - max_tilt_angle);
            } else {
              scale = (abs(49152 - (int)ang.p) - max_tilt_angle) / (16384.0f - max_tilt_angle);
            }

            //					mprintf(0, "scale %f, ", scale);

            if (ang.b < 32768) {
              float temp_scale;
              //							if(temp_scale * temp_scale > .05)

              if (ang.b > 28672) {
                temp_scale = (1.04f - ((28672 - 16834) / 16384.0f));
              } else {
                temp_scale = (1.04f - (abs(16834 - (int)ang.b) / 16384.0f));
              }

              temp_scale *= temp_scale;
              scale *= temp_scale;
              if (f_player_fired_recently)
                scale *= .25f;

              rotthrust->z -= scale * BANK_AUTOLEVEL_SPEED_SCALAR * obj->mtype.phys_info.full_rotthrust;
            } else {
              float temp_scale;

              if (ang.b < 36864) {
                temp_scale = (1.04f - ((49152 - 36864) / 16384.0f));
              } else {
                temp_scale = (1.04f - (abs(49152 - (int)ang.b) / 16384.0f));
              }

              temp_scale *= temp_scale;
              scale *= temp_scale;
              if (f_player_fired_recently)
                scale *= .25f;

              rotthrust->z += scale * BANK_AUTOLEVEL_SPEED_SCALAR * obj->mtype.phys_info.full_rotthrust;
            }

            //						PhysicsApplyConstRotForce(*obj, level_rotthrust, *rotvel,
            // frame_time);
          }
        }
      }
    }
  }

  if (pi->rotdrag > 0.0f) {
    if (!(pi->flags & PF_USES_THRUST)) {
      *rotthrust = Zero_vector;
    }

    PhysicsApplyConstRotForce(*obj, *rotthrust, *rotvel, frame_time);
  }

  // Apply rotation to the "un-rollbanked" object
  tangles.p = (int16_t)(rotvel->x * frame_time); // Casting to int16_t is required for aarch64 to avoid FCVTZU instruction which strips the negative sign
  tangles.h = (int16_t)(rotvel->y * frame_time);
  tangles.b = (int16_t)(rotvel->z * frame_time);

  vm_AnglesToMatrix(&rotmat, tangles.p, tangles.h, tangles.b);
  *orient = *orient * rotmat; // ObjSetOrient is below

  // Determine the new turnroll from this amount of turning
  if (pi->flags & PF_TURNROLL) {
    set_object_turnroll(obj, rotvel, turnroll);
  }

  // re-rotate object for bank caused by turn
  if (*turnroll != 0) {
    tangles.p = tangles.h = 0;
    tangles.b = *turnroll;
    vm_AnglesToMatrix(&rotmat, tangles.p, tangles.h, tangles.b);
    *orient = *orient * rotmat; // ObjSetOrient is below
  }
/*
  mprintf(0, " a %f, %f, %f,\n%f, %f, %f,\n%f %f %f\n\n",
          XYZ(&obj->orient.fvec),
          XYZ(&obj->orient.rvec),
          XYZ(&obj->orient.uvec));
*/
  // Make sure the new orientation is valid
  vm_Orthogonalize(orient);

  return true;
}

void PhysicsDoSimLinear(const object &obj, const vector &pos, const vector &force, vector &velocity,
                        vector &movementVec, vector &movementPos, float simTime, int count) {
  // Determine velocity
  if (obj.mtype.phys_info.flags & PF_FIXED_VELOCITY) {
    movementVec = velocity * simTime;
    movementPos = pos + movementVec;
    return;
  }

  // Help so that we do not loss velocity when sliding (still framerate dependent -- fix with force stuff)
  //	if (!(count == 0 || (count > 0 && (~obj->mtype.phys_info.flags & (PF_BOUNCE | PF_GRAVITY)))))
  //		return;

  vector forceToUse = force;
  if (!ROOMNUM_OUTSIDE(obj.roomnum) && !(obj.mtype.phys_info.flags & PF_LOCK_MASK) &&
      Rooms[obj.roomnum].wind != Zero_vector && count == 0 && obj.mtype.phys_info.drag > 0.0f &&
      !(obj.type == OBJ_POWERUP && Level_powerups_ignore_wind)) {
    // Factor in outside wind
    const vector &wind = Rooms[obj.roomnum].wind;
    vector deltaForce = wind * obj.mtype.phys_info.drag * 16.0f;
    forceToUse += deltaForce;
  }

  PhysicsApplyConstantForce(obj, movementPos, velocity, movementVec, forceToUse, simTime);

#ifdef _DEBUG
  if (Physics_player_verbose && obj.type == OBJ_PLAYER) {
    mprintf(0, "Player Velocity = %f(%f)\n", vm_GetMagnitude(&velocity), vm_GetMagnitude(&movementVec) / simTime);
  }
#endif
}

//	-----------------------------------------------------------------------------------------------------------
// Simulate a physics object for this frame
void do_physics_sim(object *obj) {
  // Since we might not call FVI, set this here
  Fvi_num_recorded_faces = 0;

  int n_ignore_objs = 0;                    // The number of ignored objects
  int ignore_obj_list[MAX_IGNORE_OBJS + 1]; // List of ignored objects

  int fate;            // Collision type for response code
  vector movement_vec; // Movement in this frame
  vector movement_pos; // End point of the movement

  int count = 0; // Simulation loop counter
  int sim_loop_limit = (obj->type == OBJ_PLAYER) ? MAX_PLAYER_SIM_LOOPS : MAX_NON_PLAYER_SIM_LOOPS;

  int objnum = OBJNUM(obj); // Simulated object's index
  fvi_info hit_info;        // Hit information
  fvi_query fq;             // Movement query

  float sim_time_remaining = Frametime;     // Amount of simulation time remaining (current iteration)
  float old_sim_time_remaining = Frametime; // Amount of simulation time remaining (previous iteration)

  vector init_pos = obj->pos;   // Initial position
  int init_room = obj->roomnum; // Initial room

  vector start_pos; // Values at the start of current simulation loop
  vector start_vel;
  matrix start_orient;
  vector start_rotvel;
  angle start_turnroll;
  int start_room;

  float moved_time;                         // How long objected moved before hit something
  physics_info *pi = &obj->mtype.phys_info; // Simulated object's physics information

  int bounced = 0; // Did the object bounce?

  vector total_force; // Constant force acting on an object

  bool f_continue_sim;            // Should we run another simulation loop
  bool f_start_fvi_record = true; // Records the rooms that are passed thru

  bool f_turn_gravity_on = false;

  // Assert conditions
  ASSERT(obj->type != OBJ_NONE);
  ASSERT(obj->movement_type == MT_PHYSICS);
  ASSERT(!(obj->mtype.phys_info.flags & PF_USES_THRUST) || obj->mtype.phys_info.drag != 0.0);

  DebugBlockPrint("P ");

  ASSERT(_finite(obj->mtype.phys_info.velocity.x) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.y) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.z) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.

#ifdef _DEBUG
  if (!Game_do_flying_sim) {
    return;
  }
#endif

  // Make powerups above the ceiling fall with gravity
  if (obj->type == OBJ_POWERUP && ROOMNUM_OUTSIDE(obj->roomnum) &&
      obj->pos.y > (CEILING_HEIGHT - obj->size - CEILING_POWERUP_DELTA) && !(obj->mtype.phys_info.flags & PF_GRAVITY)) {
    obj->mtype.phys_info.flags |= PF_GRAVITY;
    obj->flags |= OF_TEMP_GRAVITY;
  } else if (obj->flags & OF_TEMP_GRAVITY) {
    obj->mtype.phys_info.flags &= ~PF_GRAVITY;
  }

  // Instant bail cases
  if ((obj->flags & (OF_DEAD | OF_ATTACHED)) || (Frametime <= 0.0) || (obj->type == OBJ_DUMMY)) {
    return;
  }

  if (obj->type == OBJ_PLAYER &&
      (obj->mtype.phys_info.thrust != Zero_vector || obj->mtype.phys_info.rotthrust != Zero_vector)) {
    Players[obj->id].last_thrust_time = Gametime;
  }

  //	mprintf(0, "%d Over terrain = %d\n", obj - Objects, obj->flags & OF_OVER_TERRAIN);

  // If the object wiggles
  if ((obj->mtype.phys_info.flags & PF_WIGGLE) && (Demo_flags != DF_PLAYBACK)) {
    float swiggle;
    vector w_pos;

    if (vm_GetMagnitude(&obj->mtype.phys_info.thrust) < .1) {
      obj->mtype.phys_info.last_still_time -= Frametime / WIGGLE_FALLOFF_TIME;
    } else {
      obj->mtype.phys_info.last_still_time += Frametime / WIGGLE_FALLOFF_TIME;
    }

    if (obj->mtype.phys_info.last_still_time < 0.0)
      obj->mtype.phys_info.last_still_time = 0.0;
    else if (obj->mtype.phys_info.last_still_time > 1.0)
      obj->mtype.phys_info.last_still_time = 1.0;

    // Ship always keeps 10% of its wiggle
    //		if(obj->mtype.phys_info.last_still_time < 1.0)
    {
      float scaler = 1.0f - obj->mtype.phys_info.last_still_time;
      if (scaler < .1f)
        scaler = .1f;

      swiggle = obj->mtype.phys_info.wiggle_amplitude * (scaler) *
                (FixSin((angle)((int)(Gametime * obj->mtype.phys_info.wiggles_per_sec * 65535) % 65535)) -
                 FixSin((angle)((int)((Gametime - Frametime) * obj->mtype.phys_info.wiggles_per_sec * 65535) % 65535)));
      w_pos = obj->pos + obj->orient.uvec * (swiggle);

      fq.p0 = &obj->pos;
      fq.startroom = obj->roomnum;
      fq.p1 = &w_pos;
      fq.rad = obj->size;
      fq.thisobjnum = objnum;
      fq.ignore_obj_list = NULL;
      fq.flags = FQ_CHECK_OBJS | FQ_RECORD | FQ_IGNORE_POWERUPS;
      fq.flags |= FQ_NEW_RECORD_LIST;
      fq.flags |= FQ_CHECK_CEILING;

      // Need for weapons to go thru transparent areas of a texture
      if (obj->type == OBJ_WEAPON)
        fq.flags |= FQ_TRANSPOINT;

      if (obj->flags & OF_NO_OBJECT_COLLISIONS)
        fq.flags &= ~FQ_CHECK_OBJS;

      fate = fvi_FindIntersection(&fq, &hit_info);

      // Only wiggle on a non-hit case
      if (fate == HIT_NONE) {

        ASSERT(hit_info.hit_room != -1);

        f_start_fvi_record = false;

        // update object's position and segment number
        ObjSetPos(obj, &hit_info.hit_pnt, hit_info.hit_room, NULL, false);
      }
    }
  }

  // If the object is effected by gravity (normal, lighter than air, and anti-gravity)
  if (obj->mtype.phys_info.flags & PF_GRAVITY) {
    total_force.x = total_force.z = 0.0;
    total_force.y = Gravity_strength * obj->mtype.phys_info.mass;
  } else if (obj->mtype.phys_info.flags & PF_REVERSE_GRAVITY) {
    total_force.x = total_force.z = 0.0;
    total_force.y = -Gravity_strength * obj->mtype.phys_info.mass;
  } else {
    total_force.x = total_force.y = total_force.z = 0.0;
  }

  obj->flags &= (~OF_STOPPED_THIS_FRAME);

  // Do rotation velocity/accel stuff
  bool f_rotated = false;

  if (!(fabs(pi->velocity.x) > .000001 || fabs(pi->velocity.y) > .000001 || fabs(pi->velocity.z) > .000001 ||
        fabs(pi->thrust.x) > .000001 || fabs(pi->thrust.y) > .000001 || fabs(pi->thrust.z) > .000001 ||
        fabs(pi->rotvel.x) > .000001 || fabs(pi->rotvel.y) > .000001 || fabs(pi->rotvel.z) > .000001 ||
        fabs(pi->rotthrust.x) > .000001 || fabs(pi->rotthrust.y) > .000001 || fabs(pi->rotthrust.z) > .000001 ||
        (obj->mtype.phys_info.flags & PF_GRAVITY) ||
        ((!ROOMNUM_OUTSIDE(obj->roomnum)) && Rooms[obj->roomnum].wind != Zero_vector) ||
        (obj->mtype.phys_info.flags & PF_WIGGLE) ||
        ((obj->ai_info != NULL) && ((obj->ai_info->flags & AIF_REPORT_NEW_ORIENT) != 0)))) {
    if ((obj->flags & OF_MOVED_THIS_FRAME)) {
      obj->flags &= (~OF_MOVED_THIS_FRAME);
      obj->flags |= OF_STOPPED_THIS_FRAME;
    }

    return;
  }

  if (obj->ai_info)
    obj->ai_info->flags &= ~AIF_REPORT_NEW_ORIENT;

  obj->flags |= OF_MOVED_THIS_FRAME;

  // This assumes that the thrust does not change within a frame.  If it does, account for it
  // there... like missiles bouncing off a wall and changing heading. --chrishack
  if (obj->mtype.phys_info.drag != 0.0) {
    if (obj->mtype.phys_info.flags & PF_USES_THRUST) {
      total_force += obj->mtype.phys_info.thrust;
    }
  }

  //	mprintf(0, "PHYSICS: Current obj: %d, %9.2fx %9.2fy %9.2fz\n", OBJNUM(obj), XYZ(&obj->pos));
  // mprintf(2,1,0,"x %9.2f\ny %9.2f\nz %9.2f", XYZ(&obj->mtype.phys_info.velocity));
  // mprintf(0, "PHYSICS: Current velocity (%f, %f, %f)\n", XYZ(&obj->mtype.phys_info.velocity));

  Physics_normal_counter++;

  // Simulate movement until we are done (i.e. Frametime has passed or object is done moving)
  do {
    // Values at start of sim loop
    start_pos = obj->pos;
    start_vel = obj->mtype.phys_info.velocity;
    start_orient = obj->orient;
    start_rotvel = obj->mtype.phys_info.rotvel;
    start_turnroll = obj->mtype.phys_info.turnroll;
    start_room = obj->roomnum;

    matrix end_orient = start_orient;
    vector end_rotvel = start_rotvel;
    angle end_turnroll = start_turnroll;
    vector end_vel = start_vel;

#ifdef _DEBUG
    // This records the sim.
    sim_loop_record[count].phys_info = obj->mtype.phys_info;
#endif

    // Initailly assume that this is the last sim cycle
    f_continue_sim = false;

    // Determines forces
    if (count > 0) {
      // If the object is effected by gravity (normal, lighter than air, and anti-gravity)
      if (obj->mtype.phys_info.flags & PF_GRAVITY) {
        total_force.x = total_force.z = 0.0;
        total_force.y = Gravity_strength * obj->mtype.phys_info.mass;
      } else if (obj->mtype.phys_info.flags & PF_REVERSE_GRAVITY) {
        total_force.x = total_force.z = 0.0;
        total_force.y = -Gravity_strength * obj->mtype.phys_info.mass;
      } else if (!(obj->mtype.phys_info.flags & PF_BOUNCE)) {
        // Player ship
      } else {
        total_force.x = total_force.y = total_force.z = 0.0;
      }
    }

    // Compute rotational information
    // Chrishack -- replace OBJ_CLUTTER with a BBOX_HIT_TYPE
    bool f_set_orient;

    if ((f_rotated == false && count == 0) || obj->type == OBJ_CLUTTER) {
      f_rotated = true;
      f_set_orient = true;
      PhysicsDoSimRot(obj, sim_time_remaining, &end_orient, &obj->mtype.phys_info.rotthrust, &end_rotvel,
                      &end_turnroll);

      /*			vector init_pos = obj->pos + obj->wall_sphere_offset;*/
      ObjSetOrient(obj, &end_orient);
      /*			vector new_pos =  obj->pos + obj->wall_sphere_offset;

                              if(obj->wall_sphere_offset != Zero_vector && obj->type == OBJ_ROBOT &&
         !(obj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS))
                              {
                                      fq.p0						= &init_pos;
                                      fq.startroom  			= obj->roomnum;
                                      fq.p1						= &new_pos;
                                      fq.rad		  			=
         Poly_models[obj->rtype.pobj_info.model_num].wall_size; fq.thisobjnum 			= objnum;
                                      fq.ignore_obj_list	= NULL;
                                      fq.flags					= 0;

                                      fate = fvi_FindIntersection(&fq,&hit_info);

                                      // Only wiggle on a non-hit case
                                      if(fate != HIT_NONE)
                                      {
                                              end_orient = start_orient;
                                              ObjSetOrient(obj, &start_orient);
                                      }
                              }*/
    } else {
      f_set_orient = false;
    }

    // Updates the thrust vector to the orientation for homing weapons
    if ((obj->type == OBJ_WEAPON) && (pi->flags & PF_USES_THRUST) && (pi->flags & PF_HOMING)) {
      pi->thrust = end_orient.fvec * pi->full_thrust;
      movement_vec = obj->mtype.phys_info.velocity * Frametime;
      movement_pos = obj->pos + movement_vec;
    }

    PhysicsDoSimLinear(*obj, obj->pos, total_force, end_vel, movement_vec, movement_pos, sim_time_remaining, count);

    // Only do velocity until we've reached our destination position
    // This is useful for multiplayer
    if (obj->mtype.phys_info.flags & PF_DESTINATION_POS) {
      vector sub1 = obj->pos - obj->mtype.phys_info.dest_pos;
      vector sub2 = movement_pos - obj->mtype.phys_info.dest_pos;

      if (vm_DotProduct(&sub1, &sub2) <= 0) {
        obj->mtype.phys_info.flags &= ~PF_DESTINATION_POS;
        vm_MakeZero(&obj->mtype.phys_info.velocity);
        vm_MakeZero(&movement_vec);
        movement_pos = obj->pos;
        goto end_of_sim;
      }

      if ((vm_VectorDistanceQuick(&obj->mtype.phys_info.dest_pos, &obj->pos)) < 1) {
        vm_MakeZero(&obj->mtype.phys_info.velocity);
        obj->mtype.phys_info.flags &= ~PF_DESTINATION_POS;
        goto end_of_sim;
      }
    }

    // We are done, as there is no collision response with PF_NO_COLLIDE
    if (obj->mtype.phys_info.flags & PF_NO_COLLIDE) {
      obj->mtype.phys_info.rotvel = end_rotvel;
      obj->mtype.phys_info.turnroll = end_turnroll;
      obj->mtype.phys_info.velocity = end_vel;

      //			ObjSetOrient(obj,&end_orient);
      ObjSetPos(obj, &movement_pos, obj->roomnum, NULL, false);

      ObjSetAABB(obj);
      obj->last_pos = init_pos;

      goto end_of_sim;
    }

    // If we are stationary, we are done :)  -- breaks on high framerates (Gravity)
    //		if(vm_GetMagnitude(&movement_vec) < 0.00001)
    //		if(vm_GetMagnitude(&start_vel) < 0.00001)
    //		if(vm_GetMagnitude(&end_vel) < 0.00001)
    //		if(vm_GetMagnitude(&obj->mtype.phys_info.thrust) < 0.00001)
    //		if(vm_GetMagnitude(&obj->mtype.phys_info.rotthrust) < .0001)
    //		if(vm_GetMagnitude(&start_rotvel) < .0001)
    //		if(vm_GetMagnitude(&end_rotvel) < .0001)
    //		{
    //			mprintf(0, "At rest\n");
    //			goto end_of_sim;
    //		}

    //		mprintf(0, "PHYSICS: Try to move to (%f, %f, %f)\n", movement_pos.x, movement_pos.y, movement_pos.z);

    Physics_normal_looping_counter++;

    // Cap ignore list -- (Objects we already hit this frame)
    ignore_obj_list[n_ignore_objs] = -1;

    vector temp_vel = obj->mtype.phys_info.velocity;
    obj->mtype.phys_info.velocity = (movement_pos - start_pos) / sim_time_remaining;

    fq.p0 = &obj->pos;
    fq.startroom = obj->roomnum;
    fq.p1 = &movement_pos;
    fq.rad = obj->size;
    fq.thisobjnum = objnum;
    fq.ignore_obj_list = ignore_obj_list;
    fq.flags = FQ_CHECK_OBJS | FQ_RECORD;
    if (f_start_fvi_record)
      fq.flags |= FQ_NEW_RECORD_LIST;

    fq.o_orient = &start_orient;
    fq.o_rotvel = &start_rotvel;
    fq.o_rotthrust = &obj->mtype.phys_info.rotthrust;
    fq.o_turnroll = &start_turnroll;
    fq.o_velocity = &start_vel;
    fq.o_thrust = &total_force;

    f_start_fvi_record = false;

    // Need for weapons to go thru transparent areas of a texture
    if (obj->type == OBJ_WEAPON)
      fq.flags |= FQ_TRANSPOINT;

    // Added a ceiling for players and powerups
    if (obj->type == OBJ_POWERUP || (obj->type == OBJ_PLAYER && obj->control_type != CT_AI) ||
        obj->type == OBJ_OBSERVER || (obj == Players[Player_object->id].guided_obj) ||
        (obj->flags & OF_FORCE_CEILING_CHECK))
      fq.flags |= FQ_CHECK_CEILING;

    if ((obj->type == OBJ_WEAPON) && (obj->ctype.laser_info.hit_status != WPC_NOT_USED))
      fq.flags |= FQ_IGNORE_WALLS;

    if (obj->flags & OF_NO_OBJECT_COLLISIONS)
      fq.flags &= ~FQ_CHECK_OBJS;

    if (IS_GENERIC(obj->type) && (Object_info[obj->id].flags & OIF_IGNORE_FORCEFIELDS_AND_GLASS))
      fq.flags |= FQ_IGNORE_RENDER_THROUGH_PORTALS;

    // Initially assume that we fully move
    hit_info.hit_turnroll = end_turnroll;
    hit_info.hit_orient = end_orient;
    hit_info.hit_rotvel = end_rotvel;
    hit_info.hit_velocity = end_vel;
    hit_info.hit_time = sim_time_remaining;

    if (obj->type == OBJ_PLAYER) {
      fq.flags |= FQ_MULTI_POINT;
    }

    fate = fvi_FindIntersection(&fq, &hit_info);

    if (fate != HIT_NONE) {
      if (obj->type == OBJ_PLAYER && hit_info.num_hits > 1) {
        vector n = Zero_vector;
        int i;

        for (i = 0; i < hit_info.num_hits; i++) {
          n += hit_info.hit_wallnorm[i];
        }

        hit_info.hit_wallnorm[0] = n;
      }
      vm_NormalizeVector(&hit_info.hit_wallnorm[0]);
    }
/*
    if (obj == Player_object && fate != HIT_NONE) {
      mprintf(0, "Hit type %d, obj %d\n", fate, hit_info.hit_object[0]);
      if (fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) {
        mprintf(0, "Hit object type %d, id %d\n",
                Objects[hit_info.hit_object[0]].type,
                Objects[hit_info.hit_object[0]].id);
      }
    }
*/
    obj->mtype.phys_info.velocity = temp_vel;

    // Accounts for precomputed hit rays
    if ((obj->type == OBJ_WEAPON) && (obj->ctype.laser_info.hit_status == WPC_HIT_WALL)) {
      vector to_hit_pnt, to_fvi_pos;

      if (fate == HIT_NONE) {
        to_hit_pnt = obj->ctype.laser_info.hit_pnt - obj->pos;
        to_fvi_pos = obj->ctype.laser_info.hit_pnt - hit_info.hit_pnt;
      } else {
        to_hit_pnt = obj->ctype.laser_info.hit_wall_pnt - obj->pos;
        to_fvi_pos = obj->ctype.laser_info.hit_wall_pnt - hit_info.hit_face_pnt[0];
      }

      if ((to_hit_pnt * to_fvi_pos) <= 0.0f) {
        fate = hit_info.hit_type[0] = HIT_WALL;

        hit_info.hit_pnt = obj->ctype.laser_info.hit_pnt;
        hit_info.hit_face_pnt[0] = obj->ctype.laser_info.hit_wall_pnt;
        hit_info.hit_room = obj->ctype.laser_info.hit_room;
        hit_info.hit_face_room[0] = obj->ctype.laser_info.hit_pnt_room;
        hit_info.hit_wallnorm[0] = obj->ctype.laser_info.hit_wall_normal;
        hit_info.hit_face[0] = obj->ctype.laser_info.hit_face;

        obj->ctype.laser_info.hit_status = WPC_NOT_USED;
      }
    }

    // chrishack -- move all FVI ASSERT to here!
    ASSERT(fate != HIT_WALL || (fate == HIT_WALL && hit_info.hit_face[0] > -1));
    ASSERT(hit_info.hit_pnt.x > -100000000.0);
    ASSERT(hit_info.hit_pnt.y > -100000000.0);
    ASSERT(hit_info.hit_pnt.z > -100000000.0);
    ASSERT(hit_info.hit_pnt.x < 100000000.0);
    ASSERT(hit_info.hit_pnt.y < 100000000.0);
    ASSERT(hit_info.hit_pnt.z < 100000000.0);
    ASSERT(!(fate != HIT_OUT_OF_TERRAIN_BOUNDS && hit_info.hit_room == -1));

#ifdef _DEBUG
    sim_loop_record[count].start_pos = obj->pos;
    sim_loop_record[count].hit_info = hit_info;

    if (fate != HIT_NONE) {
      if (Physics_player_verbose) {
        objnum = ObjCreate(OBJ_DEBUG_LINE, 1, hit_info.hit_room, &hit_info.hit_face_pnt[0], NULL);
        if (objnum >= 0) { // DAJ -1FIX
          Objects[objnum].rtype.line_info.end_pos = hit_info.hit_face_pnt[0] + hit_info.hit_wallnorm[0];
          Objects[objnum].size = vm_VectorDistance(&Player_object->pos, &hit_info.hit_pnt);
          ObjSetAABB(&Objects[objnum]);

          Objects[objnum].flags |= OF_USES_LIFELEFT;
          Objects[objnum].lifeleft = 10.0f;
          Objects[objnum].lifetime = 10.0f;
        }
        if (obj == Player_object) {
          mprintf(0, "Fate = %d for player - ", fate);
          if (fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) {
            if (Objects[hit_info.hit_object[0]].flags & OF_BIG_OBJECT) {
              mprintf(0, "Big object\n");
            } else {
              mprintf(0, "Small object\n");
            }
          } else {
            mprintf(0, "non-object\n");
          }
        }
      }
    }
#endif

    if (f_set_orient) {
      obj->mtype.phys_info.turnroll = hit_info.hit_turnroll;
      obj->mtype.phys_info.rotvel = hit_info.hit_rotvel;
      //			ObjSetOrient(obj, &hit_info.hit_orient);

      f_set_orient = false;
    }

    obj->mtype.phys_info.velocity = hit_info.hit_velocity;

    // Instant bails for collision response
    if (obj->type == OBJ_PLAYER &&
        ((fate == HIT_OUT_OF_TERRAIN_BOUNDS) ||
         (ROOMNUM_OUTSIDE(hit_info.hit_room) && GetTerrainCellFromPos(&hit_info.hit_pnt) == -1))) {
      ObjSetPos(obj, &init_pos, init_room, NULL, false);
      obj->last_pos = init_pos;

      return;
    } else if (fate == HIT_OUT_OF_TERRAIN_BOUNDS) {
      SetObjectDeadFlag(obj);
      obj->last_pos = init_pos;

      return;
    }

    // This is so the collide code knows that last collision position if there are multiple collisions
    obj->last_pos = obj->pos;

    // update object's position and segment number
    ObjSetPos(obj, &hit_info.hit_pnt, hit_info.hit_room, NULL, false);

    // Calulate amount of sim time left
    if (fate == HIT_NONE) {
      moved_time = old_sim_time_remaining = sim_time_remaining;
      sim_time_remaining = 0.0;
      f_continue_sim = false;
    } else {
      vm_NormalizeVector(&hit_info.hit_wallnorm[0]);

      vector moved_vec_n;
      float attempted_dist, actual_dist;

      // Save results of this simulation
      old_sim_time_remaining = sim_time_remaining;
      moved_vec_n = obj->pos - start_pos; // chrishack -- use this copy
      if (moved_vec_n != Zero_vector) {
        actual_dist = vm_NormalizeVector(&moved_vec_n);
      } else {
        actual_dist = 0.0f;
      }

      // chrishack -- potentially bad -- outside to inside stuff
      // We where sitting in a wall -- invalid starting point
      // moved backwards
      if (fate == HIT_WALL && moved_vec_n * movement_vec < -0.000001 && actual_dist != 0.0) {
/*
        mprintf(0, "Obj %d Flew backwards!\n", OBJNUM(obj));
        mprintf(0, "PHYSICS NOTE: (%f, %f, %f) to (%f, %f, %f)\n",
                XYZ(&start_pos),
                XYZ(&obj->pos)); // don't change position or sim_time_remaining
*/
        ObjSetPos(obj, &start_pos, start_room, NULL, false);

        moved_time = 0.0;
      } else {
        // Compute more results of this simulation
        attempted_dist = vm_GetMagnitude(&movement_vec);
        sim_time_remaining = sim_time_remaining * ((attempted_dist - actual_dist) / attempted_dist);
        moved_time = old_sim_time_remaining - sim_time_remaining;

        // chrishack -- we have no time left (plus some)  This can happen if FVI corrects a near tangental
        // movement by adding the radius - thus, we move a little too far.
        if (sim_time_remaining < 0.0) {
          sim_time_remaining = 0.0;
          moved_time = old_sim_time_remaining;
        }

        // chrishack -- negative simulation time pasted for this sim frame
        if (sim_time_remaining > old_sim_time_remaining) {
/*
          mprintf(0,"PHYSICS WARNING: Bogus sim_time_remaining = %15.13f, old = %15.13f\n""
                    "Attempted d = %15.13f, actual = %15.13f\n",
                  sim_time_remaining,
                  old_sim_time_remaining,
                  attempted_dist,
                  actual_dist);
           Int3();
*/
          sim_time_remaining = old_sim_time_remaining;
          moved_time = 0.0;
          f_continue_sim = false;
        }
      }

      //		// Get the collision speed as a linear interp.
      //		if(old_sim_time_remaining > 0.0f)
      //		{
      // Get the collision speed as a linear interp.
      if (fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT || fate == HIT_TERRAIN || fate == HIT_WALL) {
        if (moved_time > 0.0001f) {
          obj->mtype.phys_info.velocity = (hit_info.hit_pnt - start_pos) / moved_time;
        } else {
          // mprintf(0, "Moved time is ZERO\n");  -- Add this back -- chrishack
          ASSERT(old_sim_time_remaining > 0.0f);
          obj->mtype.phys_info.velocity = start_vel;
        }
      } else {
        if (old_sim_time_remaining > 0.0) {
          obj->mtype.phys_info.velocity = obj->mtype.phys_info.velocity * (moved_time / old_sim_time_remaining) +
                                          start_vel * (sim_time_remaining / old_sim_time_remaining);
        }
      }
    }

    bounced = 0;

    // Collision response code
    switch (fate) {
    case HIT_NONE:
      if (obj->type == OBJ_WEAPON && (obj->mtype.phys_info.flags & (PF_GRAVITY | PF_WIND))) {
        if (obj->mtype.phys_info.velocity != Zero_vector)
          vm_VectorToMatrix(&obj->orient, &obj->mtype.phys_info.velocity, &obj->orient.uvec, NULL);
      }
      f_continue_sim = false;
      break;
    case HIT_WALL: // Finally unified, still needs some work, but it certainly better like this  :)
    case HIT_TERRAIN: {
      bool f_volatile_lava; // either volatile or lava
      bool f_forcefield;
      float ff_bounce_factor = 2.0f;

      // Check if volatile
      int tmap;
      if (!ROOMNUM_OUTSIDE(hit_info.hit_face_room[0])) // Make sure we've hit a wall, and not terrain
      {
        tmap = Rooms[hit_info.hit_face_room[0]].faces[hit_info.hit_face[0]].tmap;
      } else {
        tmap = Terrain_tex_seg[Terrain_seg[CELLNUM(hit_info.hit_face_room[0])].texseg_index].tex_index;
      }
      f_volatile_lava = (GameTextures[tmap].flags & (TF_VOLATILE + TF_LAVA)) != 0;
      f_forcefield = (GameTextures[tmap].flags & TF_FORCEFIELD) != 0;

      if (f_forcefield) {
        int i;

        for (i = 0; i < MAX_FORCE_FIELD_BOUNCE_TEXTURES; i++) {
          if (tmap == force_field_bounce_texture[i]) {
            ff_bounce_factor = force_field_bounce_multiplier[i];
            break;
          }
        }
      }

      //				if(obj->type != OBJ_CLUTTER)
      {
        vector moved_v;
        float hit_speed, wall_part;
        float hit_dot = 1.0;

        float luke_test;

        if (obj->type == OBJ_PLAYER) {
          luke_test = vm_GetMagnitude(&obj->mtype.phys_info.velocity);
        }

        // Find hit speed
        moved_v = obj->pos - start_pos; // chrishack -- We already computed this!!!!!!!
        wall_part = moved_v * hit_info.hit_wallnorm[0];

        if (obj->mtype.phys_info.hit_die_dot > 0.0) {
          vector m_normal = start_pos - obj->pos;
          vm_NormalizeVector(&m_normal);
          hit_dot = m_normal * hit_info.hit_wallnorm[0];
        }

        hit_speed = -(wall_part / moved_time);

        // Process wall hit
        bool hit_wall = collide_object_with_wall(obj, hit_speed, hit_info.hit_face_room[0], hit_info.hit_face[0],
                                                 &hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0], hit_dot);

        if (!(obj->flags & OF_DEAD)) {
          // Check for not really hitting the wall (because it was glass & broke)
          if (!hit_wall) {
            f_continue_sim = true;
            break;
          }

          if (obj->type == OBJ_WEAPON && ((obj->mtype.phys_info.flags & PF_BOUNCE) || f_forcefield))
            obj->mtype.phys_info.flags &= (~PF_NO_COLLIDE_PARENT);

          // Slide object along wall

          // We're constrained by wall, so subtract wall part from the velocity vector
          wall_part = hit_info.hit_wallnorm[0] * obj->mtype.phys_info.velocity;

          if (!f_forcefield && !f_volatile_lava && (obj->mtype.phys_info.num_bounces <= 0) &&
              (obj->mtype.phys_info.flags & PF_STICK)) {
            obj->movement_type = MT_NONE;

            if (!ROOMNUM_OUTSIDE(hit_info.hit_face_room[0])) {
              if (GameTextures[Rooms[hit_info.hit_face_room[0]].faces[hit_info.hit_face[0]].tmap].flags &
                  (TF_VOLATILE | TF_LAVA)) {
                SetObjectDeadFlag(obj);
              }
            } else {
              if (GameTextures[Terrain_tex_seg[Terrain_seg[CELLNUM(hit_info.hit_room)].texseg_index].tex_index].flags &
                  (TF_VOLATILE | TF_LAVA)) {
                SetObjectDeadFlag(obj);
              }
            }

            if (!ROOMNUM_OUTSIDE(hit_info.hit_face_room[0]) &&
                (Rooms[hit_info.hit_face_room[0]].faces[hit_info.hit_face[0]].portal_num >= 0)) {
              obj->flags |= OF_STUCK_ON_PORTAL;
              obj->mtype.phys_info.stuck_room = hit_info.hit_face_room[0];
              obj->mtype.phys_info.stuck_portal =
                  Rooms[hit_info.hit_face_room[0]].faces[hit_info.hit_face[0]].portal_num;
            }

            vm_MakeZero(&obj->mtype.phys_info.velocity);
            obj->last_pos = init_pos;
            goto end_of_sim;
          } else if (f_volatile_lava || f_forcefield || (obj->mtype.phys_info.flags & PF_BOUNCE)) {
            wall_part *= 2.0; // Subtract out wall part twice to achieve bounce
            bounced = 1;      // this object bounced

            if (f_forcefield) {
              if (obj->type == OBJ_PLAYER)
                wall_part *= ff_bounce_factor; // player bounce twice as much -- chrishack try without this too.
            }

            // New bounceness code
            if (!f_forcefield && (obj->mtype.phys_info.flags & PF_BOUNCE) &&
                (obj->mtype.phys_info.num_bounces != PHYSICS_UNLIMITED_BOUNCE)) {
              if (obj->mtype.phys_info.num_bounces == 0) {
                if (obj->type != OBJ_PLAYER && (obj->flags & OF_DYING)) {
                  ASSERT((obj->control_type == CT_DYING) || (obj->control_type == CT_DYING_AND_AI));
                  DestroyObject(obj, 50.0, obj->ctype.dying_info.death_flags);
                } else {
                  if (obj->type != OBJ_PLAYER)
                    SetObjectDeadFlag(obj);
                  else
                    mprintf(0, "Got a ship that was set for bounce!!! BAD!!!\n");
                }
              }
              obj->mtype.phys_info.num_bounces--;
            }

            {
              float v_mag = vm_GetMagnitude(&obj->mtype.phys_info.velocity);

              if (obj->type == OBJ_CLUTTER && hit_info.hit_wallnorm[0].y > .4 &&
                  (obj->mtype.phys_info.velocity * hit_info.hit_wallnorm[0] > -2.0f)) {

                if (obj->mtype.phys_info.flags & PF_GRAVITY) {
                  f_turn_gravity_on = true;
                  obj->mtype.phys_info.flags &= (~(PF_GRAVITY | PF_BOUNCE));
                  obj->mtype.phys_info.drag *= 300.0f;
                }

                if (v_mag < 1.8f) {
                  obj->mtype.phys_info.velocity = Zero_vector;
                  obj->mtype.phys_info.rotvel = Zero_vector;
                  goto skip_sim;
                } else {
                  goto slide_sim;
                }
              }

              if (!f_forcefield && !(f_volatile_lava && obj->type == OBJ_PLAYER))
                bump_obj_against_fixed(obj, &hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0]);
              else
                obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0] * (wall_part * -1.0f);
            }

            //						if(!f_forcefield && !(f_volatile && obj->type == OBJ_PLAYER))
            //						{
            //							if(obj->mtype.phys_info.coeff_restitution != 1.0f)
            //								obj->mtype.phys_info.velocity -=
            //(obj->mtype.phys_info.velocity * (1.0f
            //- obj->mtype.phys_info.coeff_restitution));
            //						}

            //						if(!f_forcefield && !(f_volatile && obj->type == OBJ_PLAYER))
            //							bump_obj_against_fixed(obj, &hit_info.hit_face_pnt[0],
            //&hit_info.hit_wallnorm[0]);
            //
            //						if(hit_info.hit_wallnorm[0].y > .4 &&
            //(vm_GetMagnitude(&obj->mtype.phys_info.velocity) < .001f
            //|| obj->mtype.phys_info.velocity * hit_info.hit_wallnorm[0] <= 0.0f))
            //						{
            //							mprintf(0, "At Rest!\n");
            //							obj->movement_type = MT_NONE;
            //							obj->mtype.phys_info.velocity = Zero_vector;
            //							f_continue_sim = false;
            //						}

            // mprintf(0, "(%f, %f, %f) after bounce\n", XYZ(&obj->mtype.phys_info.velocity));
            // mprintf(0, "p (%f, %f, %f) after bounce\n", XYZ(&obj->pos));
          } else {
          slide_sim:

            float wall_force;

            wall_force = total_force * hit_info.hit_wallnorm[0];

            if (obj->type != OBJ_CLUTTER)
              total_force +=
                  hit_info.hit_wallnorm[0] * (wall_force * -1.001); // 1.001 so that we are not quite tangential
            else
              total_force +=
                  hit_info.hit_wallnorm[0] * (wall_force * -1.0001); // 1.001 so that we are not quite tangential

            // Update velocity from wall hit.
            if (obj->type != OBJ_CLUTTER)
              obj->mtype.phys_info.velocity +=
                  hit_info.hit_wallnorm[0] * (wall_part * -1.001); // 1.001 so that we are not quite tangential
            else
              obj->mtype.phys_info.velocity +=
                  hit_info.hit_wallnorm[0] * (wall_part * -1.0001); // 1.001 so that we are not quite tangential

            if ((obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER || (obj->type == OBJ_BUILDING && obj->ai_info)) &&
                sim_time_remaining == old_sim_time_remaining) {
              obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0];
            }

            if (obj->type == OBJ_PLAYER) {
              float real_vel;

              real_vel = vm_NormalizeVector(&obj->mtype.phys_info.velocity);
              obj->mtype.phys_info.velocity *= ((real_vel + luke_test) / 2);
              // obj->mtype.phys_info.velocity *= (luke_test);
            } else if (obj->type == OBJ_CLUTTER && !(obj->mtype.phys_info.flags & PF_LOCK_MASK)) {
              // Do rolling rotvel hack
              obj->mtype.phys_info.rotvel = Zero_vector;

              if (obj->mtype.phys_info.velocity != Zero_vector) {
                vector axis;
                float speed = vm_GetMagnitude(&obj->mtype.phys_info.velocity);

                vm_CrossProduct(&axis, &obj->mtype.phys_info.velocity, &hit_info.hit_wallnorm[0]);
                vm_NormalizeVector(&axis);

                axis = axis * obj->orient;

                float scale = speed * 65535.0f / (2.0f * PI * obj->size);

                obj->mtype.phys_info.rotvel = axis * -scale;
              }
            }
          }

        skip_sim:

          // mprintf(0, "PHYSICS: Wall normal (%f, %f, %f)\n", XYZ(&hit_info.hit_wallnorm[0]));
          // mprintf(0, "PHYSICS: Bounded velocity (%f, %f, %f)\n", XYZ(&obj->mtype.phys_info.velocity));

          // This only happens if the new velocity is set from hitting a forcefield.
          if (!(fabs(obj->mtype.phys_info.velocity.x) < MAX_OBJECT_VEL &&
                fabs(obj->mtype.phys_info.velocity.y) < MAX_OBJECT_VEL &&
                fabs(obj->mtype.phys_info.velocity.z) < MAX_OBJECT_VEL)) {
            float mag = vm_NormalizeVector(&obj->mtype.phys_info.velocity);

            mprintf(0, "PHYSICS:  Bashing vel for Obj %d of type %d with %f velocity", objnum, obj->type, mag);
            obj->mtype.phys_info.velocity *= MAX_OBJECT_VEL * 0.1f;
          }

          // Weapons should face their new heading.  This is so missiles are pointing in the correct direct.
          if (obj->type == OBJ_WEAPON && (bounced || (obj->mtype.phys_info.flags & (PF_GRAVITY | PF_WIND))))
            if (obj->mtype.phys_info.velocity != Zero_vector)
              vm_VectorToMatrix(&obj->orient, &obj->mtype.phys_info.velocity, &obj->orient.uvec, NULL);
        }
      }
      // else
      //{
      /*				vector r1 = hit_info.hit_face_pnt[0] - obj->pos;
                                      vector w1;
                                      vector n1;
                                      float temp1;

                                      float j;

                                      matrix o_t1 = obj->orient;
                                      vm_TransposeMatrix(&o_t1);
                                      vector cmp1 = obj->mtype.phys_info.rotvel * o_t1;
                                      ConvertEulerToAxisAmount(&cmp1, &n1, &temp1);

                                      n1 *= temp1;

                                      if(temp1 != 0.0f)
                                      {
                                              vm_CrossProduct(&w1, &n1, &r1);
                                      }
                                      else
                                      {
                                              w1 = Zero_vector;
                                      }

                                      vector p1 = obj->mtype.phys_info.velocity + w1; // *((2.0f*(float)PI)/65535.0f);

                                      if(p1.y < 0.0)
                                      {
      //					if(p1.y == 0.0)
      //						mprintf(0, "AT REST: p1 (%f, %f, %f)\n", XYZ(&p1));
      //					else
      //						mprintf(0, "SHIT: p1 (%f, %f, %f)\n", XYZ(&p1));
      //
      //					p1.y = -.0001f;
      //					}


                                              float v_rel;

                                              float m1 = obj->mtype.phys_info.mass;

                                              v_rel = hit_info.hit_wallnorm[0] * (p1);

                                              float e = .1f;

                                              vector c1;
                                              vector cc1;
                                              float cv1;

                                              float i1 = (m1/12.0)*(2.0f * pow(obj->size*2.0, 2));

                                              vm_CrossProduct(&c1, &r1, &hit_info.hit_wallnorm[0]);

                                              c1 = c1/i1;

                                              vm_CrossProduct(&cc1, &c1, &r1);

                                              cv1 = (hit_info.hit_wallnorm[0])*c1;

                                              j = (-(1.0f + e))*v_rel;
                                              j /= (1/m1 + cv1);

                                              obj->mtype.phys_info.velocity += ((j*(hit_info.hit_wallnorm[0]))/m1);

                                              vector jcn = j * (hit_info.hit_wallnorm[0]);

                                              vm_CrossProduct(&c1, &r1, &jcn);

                                              n1 = (c1)/i1;

                                              temp1 = vm_NormalizeVector(&n1);

                                              vector txx1;

                                              ConvertAxisAmountToEuler(&n1, &temp1, &txx1);

                                              obj->mtype.phys_info.rotvel += (txx1*obj->orient);
                                      }
                                      else
                                      {
                                              obj->mtype.phys_info.velocity.y = .001f;
                                              obj->mtype.phys_info.rotvel = Zero_vector;
                                      }*/

      //				}

      f_continue_sim = true;

    } break;

    case HIT_CEILING: {
      vector moved_v;
      float wall_part;

      float luke_test;

      if (obj->type == OBJ_PLAYER) {
        luke_test = vm_GetMagnitude(&obj->mtype.phys_info.velocity);
      }

      // Find hit speed
      moved_v = obj->pos - start_pos; // chrishack -- We already computed this!!!!!!!
      wall_part = moved_v * hit_info.hit_wallnorm[0];

      // We're constrained by wall, so subtract wall part from the velocity vector
      wall_part = hit_info.hit_wallnorm[0] * obj->mtype.phys_info.velocity;

      if (obj->mtype.phys_info.flags & PF_BOUNCE) {
        wall_part *= 2.0; // Subtract out wall part twice to achieve bounce

        obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0] * (wall_part * -1.0f);

        if (obj->mtype.phys_info.coeff_restitution != 1.0f)
          obj->mtype.phys_info.velocity -=
              (obj->mtype.phys_info.velocity * (1.0f - obj->mtype.phys_info.coeff_restitution));
      } else {
        float wall_force;

        wall_force = total_force * hit_info.hit_wallnorm[0];
        total_force += hit_info.hit_wallnorm[0] * (wall_force * -1.001); // 1.001 so that we are not quite tangential

        // Update velocity from wall hit.
        obj->mtype.phys_info.velocity +=
            hit_info.hit_wallnorm[0] * (wall_part * -1.001); // 1.001 so that we are not quite tangential
        if (obj->type == OBJ_PLAYER) {
          float real_vel;

          real_vel = vm_NormalizeVector(&obj->mtype.phys_info.velocity);
          obj->mtype.phys_info.velocity *= ((real_vel + luke_test) / 2.0f);
          // obj->mtype.phys_info.velocity *= (luke_test);
        }
      }

      // This only happens if the new velocity is set from hitting a forcefield.
      ASSERT(fabs(obj->mtype.phys_info.velocity.x) < MAX_OBJECT_VEL &&
             fabs(obj->mtype.phys_info.velocity.y) < MAX_OBJECT_VEL &&
             fabs(obj->mtype.phys_info.velocity.z) < MAX_OBJECT_VEL);

      // Weapons should face their new heading.  This is so missiles are pointing in the correct direct.
      if (obj->type == OBJ_WEAPON && (bounced || (obj->mtype.phys_info.flags & (PF_GRAVITY | PF_WIND))))
        vm_VectorToMatrix(&obj->orient, &obj->mtype.phys_info.velocity, &obj->orient.uvec, NULL);

      f_continue_sim = true;
    } break;

    case HIT_OBJECT:
    case HIT_SPHERE_2_POLY_OBJECT: {
      vector old_force; // -- chrishack

      // Mark the hit object so that on the following sim frames, in this game frame, ignore this object.
      ASSERT(hit_info.hit_object[0] != -1); // chrishack move this ASSERT fvi stuff above

      // chrishack -- we should have this point from FVI!!!!!!!!!!!
      //	Calculcate the hit point between the two objects.
      // old_vel = obj->mtype.phys_info.velocity;
      old_force = obj->mtype.phys_info.thrust;

      obj->mtype.phys_info.thrust = total_force;

      //				hit_info.hit_wallnorm[0] *= -1.0f;

      //				mprintf(0, "hit dist %f\n", hit_info.hit_dist);

      collide_two_objects(obj, &Objects[hit_info.hit_object[0]], &hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0],
                          &hit_info);
      if (obj->movement_type == MT_OBJ_LINKED)
        goto end_of_sim;

      total_force = obj->mtype.phys_info.thrust;

      obj->mtype.phys_info.thrust = old_force;

      if ((obj->type != OBJ_POWERUP && Objects[hit_info.hit_object[0]].type != OBJ_POWERUP) &&
          (obj->type == OBJ_CLUTTER || obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER ||
           (obj->type == OBJ_BUILDING && obj->ai_info)) &&
          sim_time_remaining == old_sim_time_remaining &&
          (Objects[hit_info.hit_object[0]].movement_type == MT_NONE ||
           (Objects[hit_info.hit_object[0]].mtype.phys_info.velocity == Zero_vector &&
            (Objects[hit_info.hit_object[0]].mtype.phys_info.flags & PF_LOCK_MASK)))) {
        obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0];
      }

      // mprintf(0, "OBJ %d t %d hit %d\n", OBJNUM(obj), obj->type, hit_info.hit_object[0]);

      // Let object continue its movement if collide_two_objects does not mark it as dead
      //				if ( !(obj->flags&OF_DEAD)  )
      //				{
      //
      //					// chrishack -- check this later -- what is the old_vel stuff?
      //					if ((obj->mtype.phys_info.flags & PF_PERSISTENT) ||
      //						 (old_vel == obj->mtype.phys_info.velocity))
      //					{
      //						ignore_obj_list[n_ignore_objs++] = hit_info.hit_object[0];
      //					}
      //				}

      // Let object continue its movement if collide_two_objects does not mark it as dead
      if (!(obj->flags & OF_DEAD)) {
        if ((obj->mtype.phys_info.flags & PF_PERSISTENT) ||
            (Objects[hit_info.hit_object[0]].mtype.phys_info.flags & PF_PERSISTENT)) {
          if (n_ignore_objs < MAX_IGNORE_OBJS) {
            ignore_obj_list[n_ignore_objs++] = hit_info.hit_object[0];
            count--;
            if (count < -1)
              count = -1;
          }

          if (obj->type == OBJ_WEAPON && (obj->mtype.phys_info.flags & PF_PERSISTENT))
            obj->ctype.laser_info.last_hit_handle = Objects[hit_info.hit_object[0]].handle;

          if (Objects[hit_info.hit_object[0]].type == OBJ_WEAPON &&
              (Objects[hit_info.hit_object[0]].mtype.phys_info.flags & PF_PERSISTENT))
            Objects[hit_info.hit_object[0]].ctype.laser_info.last_hit_handle = obj->handle;
        } else if (Objects[hit_info.hit_object[0]].type == OBJ_POWERUP || obj->type == OBJ_POWERUP ||
                   Objects[hit_info.hit_object[0]].type == OBJ_MARKER || obj->type == OBJ_MARKER) {
          if (n_ignore_objs < MAX_IGNORE_OBJS)
            ignore_obj_list[n_ignore_objs++] = hit_info.hit_object[0];

          count--;
          if (count < -1)
            count = -1;
        }

        f_continue_sim = true;

        //					if((obj->type == OBJ_CLUTTER)&&(Objects[hit_info.hit_object[0]].type ==
        // OBJ_CLUTTER))
        //					{
        //						f_continue_sim = false;
        //					}
      } else {
        f_continue_sim = false;
      }
    } break;

    case HIT_BAD_P0:
      mprintf(0, "PHYSICS ERROR: Bad p0 in physics!!!\n");
      Int3(); // Unexpected collision type: start point not in specified segment.
      break;

    default:
      mprintf(0, "PHYSICS ERROR: Unknown and unhandled hit type returned from FVI\n");
      Int3();
      break;
    }

    // Increment the simulation loop counter
    count++;

  } while ((f_continue_sim) && (!(obj->flags & OF_DEAD)) && (sim_time_remaining > 0.0f) && (count < sim_loop_limit));

  // Special stuff should we do if we hit the simulation loop limit
  //	If retry count is getting large, then we might be trying to do something bad.
  // NOTE: These numbers limit the max collisions an object can have in a single frame
  if (count >= sim_loop_limit) {
    if (obj->type == OBJ_PLAYER) {
      mprintf(0, "PHYSICS NOTE: Too many collisions for player!\n");
      obj->mtype.phys_info.velocity = Zero_vector;
    } else {
/*
      mprintf(0, "PHYSICS NOTE: Too many collisions for non-player object %d (%d to %d)!\n",
              objnum,
              init_room,
              obj->roomnum);
      obj->flags |= OF_DEAD;
      obj->mtype.phys_info.velocity /= 2.0f;
      obj->mtype.phys_info.rotvel /= 2.0f;
*/
    }

    // ObjSetPos(obj,&init_pos, init_room);
    // obj->last_pos = init_pos;
  }

end_of_sim:

  if (f_turn_gravity_on) {
    obj->mtype.phys_info.flags |= (PF_GRAVITY | PF_BOUNCE);
    obj->mtype.phys_info.drag /= 300.0f;
  }

  AttachUpdateSubObjects(obj);

  ASSERT(_finite(obj->mtype.phys_info.velocity.x) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.y) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.z) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.

  obj->last_pos = init_pos;
  return;
}

int PhysCastWalkRay(object *obj, vector *p0, vector *p1, vector *hitpnt, int *start_roomnum = NULL,
                    int *end_roomnum = NULL, vector *hit_normal = NULL) {
  int fate;

  fvi_info hit_info;
  fvi_query fq;

  fq.p0 = p0;
  fq.p1 = p1;

  if (start_roomnum)
    fq.startroom = *start_roomnum;
  else
    fq.startroom = obj->roomnum;

  fq.rad = 0.0f;
  fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
             FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
  if (!end_roomnum)
    fq.flags |= FQ_NO_RELINK;

  fq.thisobjnum = OBJNUM(obj);
  fq.ignore_obj_list = NULL;

  fate = fvi_FindIntersection(&fq, &hit_info);
  if (end_roomnum)
    *end_roomnum = hit_info.hit_room;
  if (hit_normal)
    *hit_normal = hit_info.hit_wallnorm[0];

  if (fate == HIT_WALL) {
    if (GameTextures[Rooms[hit_info.hit_face_room[0]].faces[hit_info.hit_face[0]].tmap].flags &
        (TF_VOLATILE | TF_FORCEFIELD | TF_LAVA)) {
      return HIT_NONE;
    }
  }

  *hitpnt = hit_info.hit_pnt;
  return fate;
}

// void PhysComputeGroundPosOrient(object *obj, vector *pos, matrix *orient)
//{
//	vector pnt[3];
//	vector tpnt = obj->pos;
//	matrix tmatrix = obj->orient;
//	poly_model *pm=&Poly_models[obj->rtype.pobj_info.model_num];
//	int num_gps = (pm->n_ground == 5)?3:1;
//	int i;
//
//	obj->pos = *pos;
//	obj->orient = *orient;
//
//	for(i = 0; i < num_gps; i++)
//	{
//		PhysCalcGround(&pnt[i], NULL, obj, i);
//	}
//
//	obj->pos = tpnt;
//	obj->orient = tmatrix;
//
//	if(num_gps == 3 && ROOMNUM_OUTSIDE(obj->roomnum))
//	{
//		float diff[3];
//		vector gp[3];
//
//		for(i = 0; i < 3; i++)
//		{
//			gp[i] = pnt[i];
//			gp[i].y = GetTerrainGroundPoint(&gp[i]);
//		}
//
//		for(i = 0; i < 3; i++)
//		{
//			diff[i] = gp[i].y - pnt[i].y;
//		}
//
//		float biggest_diff = diff[0];
//		for(i = 1; i < 3; i++)
//		{
//			if(fabs(diff[i]) > fabs(biggest_diff))
//			{
//				biggest_diff = diff[i];
//			}
//		}
//
//		vector uvec;
//		vm_GetPerp(&uvec, &gp[0], &gp[1], &gp[2]);
//		vm_NormalizeVector(&uvec);
//
//		float dot = orient->fvec * uvec;
//		vector fvec = orient->fvec;
//		fvec -= (uvec * dot);
//		vm_NormalizeVector(&fvec);
//
//		vm_VectorToMatrix(orient, &fvec, &uvec, NULL);
//		pos->y += biggest_diff;
//	}
//	else
//	{  // Alignd to Y-axis
//		float diff = GetTerrainGroundPoint(&pnt[0]) - pnt[0].y;
//
//		pos->y += diff;
//
//		angvec a;
//		vm_ExtractAnglesFromMatrix(&a, orient);
//		vm_AnglesToMatrix(orient, 0.0f, a.h, 0.0f);
//	}
//}

void PhysCalPntOnCPntPlane(object *obj, vector *s_pnt, vector *d_pnt, float *dist) {
  vector tpnt = *s_pnt - obj->pos;
  *dist = obj->orient.uvec * tpnt;

  *d_pnt = *s_pnt + ((-(*dist)) * obj->orient.uvec);
}

bool PhysComputeWalkerPosOrient(object *obj, vector *pos, matrix *orient) {
  vector pnt[3];
  vector tpnt = obj->pos;
  matrix tmatrix = obj->orient;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  int num_gps = (pm->n_ground == 5) ? 3 : 1;
  int i;

  bool f_ok = true;

  obj->pos = *pos;
  obj->orient = *orient;

  for (i = 0; i < num_gps; i++) {
    PhysCalcGround(&pnt[i], NULL, obj, i);
  }

  obj->pos = tpnt;
  obj->orient = tmatrix;

  if (num_gps == 3) {
    vector pp[3];
    float pdist[3];
    int proom[3];
    vector hp[3];

    for (i = 0; i < 3; i++)
      PhysCalPntOnCPntPlane(obj, &pnt[i], &pp[i], &pdist[i]);

    // Moves the points to valid locations in the mine and determines the points' room numbers
    for (i = 0; i < 3; i++) {
      vector x;
      vector norm;

      int fate = PhysCastWalkRay(obj, &obj->pos, &pp[i], &x, NULL, &proom[i], &norm);
      if (fate != HIT_NONE) {
        if (norm * obj->orient.uvec < 0.4717f) {
          return false;
        }

        pp[i] = x;
      }
    }

    int num_ave = 0;
    vector ave_diff = Zero_vector;

    for (i = 0; i < 3; i++) {
      int fate;
      vector foot_pnt = pp[i] + obj->orient.uvec * -(obj->size * 1.5f);
      vector norm;

      fate = PhysCastWalkRay(obj, &pp[i], &foot_pnt, &hp[i], &proom[i], NULL, &norm);

      if (fate != HIT_NONE) {
        if (norm * obj->orient.uvec < 0.4717f) {
          return false;
        }

        ave_diff += hp[i] - pnt[i];
        num_ave++;
      } else {
        f_ok = false;
      }
    }

    if (num_ave > 0) {
      ave_diff /= num_ave;
    } else
      ave_diff = Zero_vector;

    vector uvec;
    vm_GetPerp(&uvec, &hp[0], &hp[1], &hp[2]);
    vm_NormalizeVector(&uvec);

    //		if(uvec.y < 0.0)
    //			uvec *= -1.0f;

    float dot = orient->fvec * uvec;
    vector fvec = orient->fvec;
    fvec -= (uvec * dot);
    vm_NormalizeVector(&fvec);

    vm_VectorToMatrix(orient, &fvec, &uvec, NULL);
    *pos += ave_diff;
  } else { // Alignd to Y-axis
    int fate;
    vector hp;
    vector foot_pnt = obj->pos;
    foot_pnt.y -= obj->size * 3.0f;

    fate = PhysCastWalkRay(obj, &obj->pos, &foot_pnt, &hp);

    if (fate == HIT_NONE) {
      mprintf(0, "Walking object %d should be falling\n", OBJNUM(obj));
      //			SetObjectDeadFlag(obj);
      f_ok = false;
    } else {
      float diff = hp.y - pnt[0].y;

      pos->y += diff;

      angvec a;
      vm_ExtractAnglesFromMatrix(&a, orient);
      vm_AnglesToMatrix(orient, 0.0f, a.h, 0.0f);
    }
  }

  return f_ok;
}

bool IsNodeValid(int cell, float min_vert_dot) {
  if (TerrainNormals[MAX_TERRAIN_LOD - 1][cell].normal1.y >= min_vert_dot &&
      TerrainNormals[MAX_TERRAIN_LOD - 1][cell].normal2.y >= min_vert_dot)
    return true;
  else
    return false;
}

bool PhysValidateGroundPath(object *obj, vector *s, int sroom, vector *e, int eroom, float rad, float min_vert_dot) {
  if (ROOMNUM_OUTSIDE(sroom)) {
    int x1, x2, y1, y2, x, y, delta_y, delta_x, change_x, change_y, length, cur_node, error_term, i;

    int new_x, new_y;
    int counter;
    int delta_ter_check = rad / TERRAIN_SIZE + 1;

    // Determine the start end end nodes
    x1 = CELLNUM(sroom) % TERRAIN_WIDTH;
    y1 = CELLNUM(sroom) / TERRAIN_WIDTH;

    x2 = CELLNUM(eroom) % TERRAIN_WIDTH;
    y2 = CELLNUM(eroom) / TERRAIN_WIDTH;

    x = x1;
    y = y1;

    // How many nodes did I move?
    delta_x = x2 - x1;
    delta_y = y2 - y1;

    // Check the current node
    if (!IsNodeValid(CELLNUM(sroom), min_vert_dot)) {
      return false;
    }

    if (delta_x == 0 && delta_y == 0)
      return true;

    // check the end node
    cur_node = y1 * TERRAIN_DEPTH + x2;
    if (!IsNodeValid(cur_node, min_vert_dot)) {
      return false;
    }

    // Do a Breshenham line algorithm
    if (delta_x < 0) {
      change_x = -1;
      delta_x = -delta_x;
    } else {
      change_x = 1;
    }

    if (delta_y < 0) {
      change_y = -1;
      delta_y = -delta_y;
    } else {
      change_y = 1;
    }

    error_term = 0;
    i = 1;

    if (delta_x < delta_y) {
      length = delta_y + 1;

      while (i < length) {
        y += change_y;
        error_term += delta_x;

        if (error_term >= delta_y) {
          x += change_x;
          error_term -= delta_y;
        }

        if (y >= TERRAIN_DEPTH || y < 0 || x < 0 || x >= TERRAIN_WIDTH) {
          return false;
        }

        for (counter = -delta_ter_check; counter <= delta_ter_check; counter++) {
          new_x = x + counter;

          if (new_x < 0) {
            counter = -x;
            new_x = 0;
          }

          if (new_x >= TERRAIN_WIDTH)
            break;

          // Check the current node for collisions -- chrishack -- This can be made iterative
          cur_node = y * TERRAIN_DEPTH + new_x;
          if (!IsNodeValid(cur_node, min_vert_dot)) {
            return false;
          }
        }

        i++;
      }

    } else {
      length = delta_x + 1;

      while (i < length) {
        x += change_x;
        error_term += delta_y;

        if (error_term >= delta_x) {
          y += change_y;
          error_term -= delta_x;
        }

        if (y >= TERRAIN_DEPTH || y < 0 || x < 0 || x >= TERRAIN_WIDTH) {
          return false;
        }

        for (counter = -delta_ter_check; counter <= delta_ter_check; counter++) {
          new_y = y + counter;

          if (new_y < 0) {
            counter = -y;
            new_y = 0;
          }
          if (new_y >= TERRAIN_DEPTH)
            break;

          // Check the current node for collisions -- chrishack -- This can be made iterative
          cur_node = new_y * TERRAIN_DEPTH + x;
          if (!IsNodeValid(cur_node, min_vert_dot)) {
            return false;
          }
        }

        i++;
      }
    }

    return true;
  } else {
    return true;
  }
}

//	-----------------------------------------------------------------------------------------------------------
// Simulate a physics object for this frame
void do_walking_sim(object *obj) {
  // Since we might not call FVI, set this here
  Fvi_num_recorded_faces = 0;

  int n_ignore_objs = 0;                    // The number of ignored objects
  int ignore_obj_list[MAX_IGNORE_OBJS + 1]; // List of ignored objects

  int fate;            // Collision type for response code
  vector movement_vec; // Movement in this frame
  vector movement_pos; // End point of the movement

  int count = 0; // Simulation loop counter
  int sim_loop_limit = (obj->type == OBJ_PLAYER) ? MAX_PLAYER_SIM_LOOPS : MAX_NON_PLAYER_SIM_LOOPS;

  int objnum = OBJNUM(obj); // Simulated object's index
  fvi_info hit_info;        // Hit information
  fvi_query fq;             // Movement query

  float sim_time_remaining = Frametime;     // Amount of simulation time remaining (current iteration)
  float old_sim_time_remaining = Frametime; // Amount of simulation time remaining (previous iteration)

  vector init_pos = obj->pos;   // Initial position
  int init_room = obj->roomnum; // Initial room

  vector start_pos = obj->pos; // Values at the start of current simulation loop
  vector start_vel = obj->mtype.phys_info.velocity;
  int start_room = obj->roomnum;

  float moved_time;                         // How long objected moved before hit something
  physics_info *pi = &obj->mtype.phys_info; // Simulated object's physics information

  int bounced = 0; // Did the object bounce?

  vector total_force = Zero_vector; // Constant force acting on an object

  bool f_continue_sim;            // Should we run another simulation loop
  bool f_start_fvi_record = true; // Records the rooms that are passed thru

  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];

  // Assert conditions
  ASSERT(obj->type != OBJ_NONE);
  ASSERT(obj->movement_type == MT_WALKING);
  ASSERT(!(obj->mtype.phys_info.flags & PF_USES_THRUST) || obj->mtype.phys_info.drag != 0.0);
  ASSERT(_finite(obj->mtype.phys_info.velocity.x) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.y) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.z) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.

  DebugBlockPrint("PW");

#ifdef _DEBUG
  if (!Game_do_walking_sim) {
    return;
  }
#endif

  // Instant bail cases
  if ((obj->flags & (OF_DEAD | OF_ATTACHED)) || (Frametime <= 0.0) || (obj->type == OBJ_DUMMY)) {
    return;
  }

  obj->flags &= (~OF_STOPPED_THIS_FRAME);

  // Do rotation velocity/accel stuff
  bool f_rotated = false;

  if (!(fabs(pi->velocity.x) > .000001 || fabs(pi->velocity.y) > .000001 || fabs(pi->velocity.z) > .000001 ||
        fabs(pi->thrust.x) > .000001 || fabs(pi->thrust.y) > .000001 || fabs(pi->thrust.z) > .000001 ||
        fabs(pi->rotvel.x) > .000001 || fabs(pi->rotvel.y) > .000001 || fabs(pi->rotvel.z) > .000001 ||
        fabs(pi->rotthrust.x) > .000001 || fabs(pi->rotthrust.y) > .000001 || fabs(pi->rotthrust.z) > .000001 ||
        (obj->mtype.phys_info.flags & PF_GRAVITY) ||
        ((!ROOMNUM_OUTSIDE(obj->roomnum)) && Rooms[obj->roomnum].wind != Zero_vector) ||
        (obj->mtype.phys_info.flags & PF_WIGGLE) ||
        ((obj->ai_info != NULL) && ((obj->ai_info->flags & AIF_REPORT_NEW_ORIENT) != 0)))) {
    if ((obj->flags & OF_MOVED_THIS_FRAME)) {
      obj->flags &= (~OF_MOVED_THIS_FRAME);
      obj->flags |= OF_STOPPED_THIS_FRAME;
    }

    return;
  }

  if (obj->ai_info) {
    if (obj->ai_info->flags & AIF_REPORT_NEW_ORIENT) {
      if (pm->n_ground == 5) {
        vector pos = obj->pos;
        matrix orient = obj->orient;

        if (PhysComputeWalkerPosOrient(obj, &pos, &orient) &&
            ((!obj->ai_info) || (orient.uvec * obj->orient.uvec > .7101 && orient.fvec * obj->orient.fvec > .7101 &&
                                 orient.rvec * obj->orient.rvec > .7101)))
          ObjSetPos(obj, &pos, obj->roomnum, &orient, false);
        else
          ObjSetOrient(obj, &obj->ai_info->saved_orient);
      }
      obj->ai_info->flags &= ~AIF_REPORT_NEW_ORIENT;
    }
  }
  obj->flags |= OF_MOVED_THIS_FRAME;

  // This assumes that the thrust does not change within a frame.  If it does, account for it
  // there... like missiles bouncing off a wall and changing heading. --chrishack
  if (obj->mtype.phys_info.drag != 0.0) {
    if (obj->mtype.phys_info.flags & PF_USES_THRUST) {
      total_force = obj->mtype.phys_info.thrust;
    }
  }

  //	mprintf(0, "PHYSICS: Current obj: %d, %9.2fx %9.2fy %9.2fz\n", OBJNUM(obj), XYZ(&obj->pos));
  // mprintf(2,1,0,"x %9.2f\ny %9.2f\nz %9.2f", XYZ(&obj->mtype.phys_info.velocity));
  // mprintf(0, "PHYSICS: Current velocity (%f, %f, %f)\n", XYZ(&obj->mtype.phys_info.velocity));

  Physics_normal_counter++;

  // Simulate movement until we are done (i.e. Frametime has passed or object is done moving)
  do {
    obj->mtype.phys_info.rotvel = Zero_vector;

#ifdef _DEBUG
    // This records the sim.
    sim_loop_record[count].phys_info = obj->mtype.phys_info;
#endif

    // Remove transient portions of the velocity
    vector t = (obj->mtype.phys_info.velocity * obj->orient.uvec) * obj->orient.uvec;
    obj->mtype.phys_info.velocity -= t;

    // Initailly assume that this is the last sim cycle
    f_continue_sim = false;

    // Determines forces
    if (count > 0) {
      total_force.x = total_force.y = total_force.z = 0.0;
    }

    {
      movement_vec = pi->velocity * Frametime;
      movement_pos = obj->pos + movement_vec;
      vector footstep = movement_pos;
      int new_room;

      if (ROOMNUM_OUTSIDE(obj->roomnum)) {
        new_room = GetTerrainRoomFromPos(&footstep);
      } else {
        new_room = obj->roomnum;
      }

      bool f_step;

      if (PhysValidateGroundPath(obj, &obj->pos, obj->roomnum, &footstep, new_room, obj->size, 0.6f)) {
        f_step = true;

        // Determine endpos
        matrix norient;
        norient = obj->orient;
        if (PhysComputeWalkerPosOrient(obj, &footstep, &norient)) {
          if (norient.uvec * obj->orient.uvec > .7101 && norient.fvec * obj->orient.fvec > .7101 &&
              norient.rvec * obj->orient.rvec > .7101) {
            ObjSetOrient(obj, &norient);

            movement_vec = footstep - obj->pos;
            movement_pos = footstep;

            fq.p0 = &obj->pos;
            fq.startroom = obj->roomnum;
            fq.p1 = &footstep;
            fq.rad = obj->size;
            fq.thisobjnum = objnum;
            fq.ignore_obj_list = NULL;
            fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_WEAPONS | FQ_IGNORE_POWERUPS | FQ_IGNORE_TERRAIN;

            if (obj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS) {
              fq.rad = 0.0f;
            } else if (!ROOMNUM_OUTSIDE(obj->roomnum)) {
              poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
              int num_gps = (pm->n_ground == 5) ? 3 : 1;

              if (num_gps == 3)
                fq.rad *= 0.2f;
              else
                fq.rad *= 0.45f;
            }

            if (obj->flags & OF_NO_OBJECT_COLLISIONS)
              fq.flags &= ~FQ_CHECK_OBJS;

            fate = fvi_FindIntersection(&fq, &hit_info);

            norient = obj->orient;
            if (PhysComputeWalkerPosOrient(obj, &hit_info.hit_pnt, &norient)) {
              ObjSetPos(obj, &hit_info.hit_pnt, hit_info.hit_room, &norient, false);
            } else {
              f_step = false;
            }
          } else {
            f_step = false;
            movement_vec = Zero_vector;
          }
        } else {
          f_step = false;
          movement_vec = Zero_vector;
        }
      } else {
        f_step = false;
      }

      if (!f_step) {
        pi->velocity = Zero_vector;
        break;
      }

      // If we are stationary, we are done :)
      if (fabs(movement_vec.x) < 0.0000001 && fabs(movement_vec.y) < 0.0000001 && fabs(movement_vec.z) < 0.0000001)
        break;
    }

    Physics_walking_looping_counter++;

    // Instant bails for collision response
    if (obj->type == OBJ_PLAYER &&
        ((fate == HIT_OUT_OF_TERRAIN_BOUNDS) ||
         (ROOMNUM_OUTSIDE(hit_info.hit_room) && GetTerrainCellFromPos(&hit_info.hit_pnt) == -1))) {
      ObjSetPos(obj, &init_pos, init_room, NULL, false);
      obj->last_pos = init_pos;

      goto end_of_sim;
    } else if (fate == HIT_OUT_OF_TERRAIN_BOUNDS) {
      mprintf(0, "PHYSICS NOTE: Walker exited terrain\n");
      SetObjectDeadFlag(obj);
      obj->last_pos = init_pos;

      goto end_of_sim;
    }

    // Calulate amount of sim time left
    if (fate == HIT_NONE) {
      moved_time = old_sim_time_remaining = sim_time_remaining;
      sim_time_remaining = 0.0;
      f_continue_sim = false;
    } else {
      vector moved_vec_n;
      float attempted_dist, actual_dist;

      // Save results of this simulation
      old_sim_time_remaining = sim_time_remaining;
      moved_vec_n = obj->pos - start_pos; // chrishack -- use this copy
      if (moved_vec_n != Zero_vector) {
        actual_dist = vm_NormalizeVector(&moved_vec_n);
      } else {
        actual_dist = 0.0f;
      }

      // chrishack -- potentially bad -- outside to inside stuff
      // We where sitting in a wall -- invalid starting point
      // moved backwards
      if (fate == HIT_WALL && moved_vec_n * movement_vec < -0.000001 && actual_dist != 0.0) {

        mprintf(0, "Obj %d Walked backwards!\n", OBJNUM(obj));
/*
        mprintf(0, "PHYSICS NOTE: (%f, %f, %f) to (%f, %f, %f)\n",
                XYZ(&start_pos),
                XYZ(&obj->pos))); // don't change position or sim_time_remaining
*/

        ObjSetPos(obj, &start_pos, start_room, NULL, false);

        moved_time = 0.0;
      } else {
        // Compute more results of this simulation
        attempted_dist = vm_GetMagnitude(&movement_vec);
        sim_time_remaining = sim_time_remaining * ((attempted_dist - actual_dist) / attempted_dist);
        moved_time = old_sim_time_remaining - sim_time_remaining;

        // chrishack -- we have no time left (plus some)  This can happen if FVI corrects a near tangental
        // movement by adding the radius - thus, we move a little too far.
        if (sim_time_remaining < 0.0) {
          sim_time_remaining = 0.0;
          moved_time = old_sim_time_remaining;
        }

        // chrishack -- negative simulation time pasted for this sim frame
        if (sim_time_remaining > old_sim_time_remaining) {
          mprintf(0,
                   "PHYSICS WARNING: Bogus sim_time_remaining = %15.13f, old = %15.13f\nAttempted d = %15.13f, actual "
                   "= %15.13f\n",
                   sim_time_remaining, old_sim_time_remaining, attempted_dist, actual_dist);
          // Int3();
          sim_time_remaining = old_sim_time_remaining;
          moved_time = 0.0;
          f_continue_sim = false;
        }
      }
    }

    // Get the collision speed as a linear interp.
    if (old_sim_time_remaining > 0.0) {
      obj->mtype.phys_info.velocity = obj->mtype.phys_info.velocity * (moved_time / old_sim_time_remaining) +
                                      start_vel * (sim_time_remaining / old_sim_time_remaining);
    }

    // Collision response code
    switch (fate) {
    case HIT_NONE:
      f_continue_sim = false;
      break;
    case HIT_WALL: // Finally unified, still needs some work, but it certainly better like this  :)
    case HIT_TERRAIN: {
      //				if(obj->type != OBJ_CLUTTER)
      {
        vector moved_v;
        float hit_speed, wall_part;
        float hit_dot = 1.0;

        float luke_test;

        if (obj->type == OBJ_PLAYER || OBJ_CLUTTER) {
          luke_test = vm_GetMagnitude(&obj->mtype.phys_info.velocity);
        }

        // Find hit speed
        moved_v = obj->pos - start_pos; // chrishack -- We already computed this!!!!!!!
        wall_part = moved_v * hit_info.hit_wallnorm[0];

        if (obj->mtype.phys_info.hit_die_dot > 0.0) {
          vector m_normal = start_pos - obj->pos;
          vm_NormalizeVector(&m_normal);
          hit_dot = m_normal * hit_info.hit_wallnorm[0];
        }

        hit_speed = -(wall_part / moved_time);

        // We hit a wall  (weapons cannot scrap)
        if ((wall_part != 0.0 && moved_time > 0.0 && (hit_speed > 0.0)) || obj->type == OBJ_WEAPON)
          collide_object_with_wall(obj, hit_speed, hit_info.hit_face_room[0], hit_info.hit_face[0],
                                   &hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0], hit_dot);
        else // We hit a wall and are moving parallel to it
          collide_object_with_wall(obj, hit_speed, hit_info.hit_face_room[0], hit_info.hit_face[0],
                                   &hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0], hit_dot);
        //					scrape_object_on_wall(obj, hit_info.hit_face_room, hit_info.hit_face,
        //&hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0] );

        if (!(obj->flags & OF_DEAD)) {
          bool f_forcefield = false; // bounce off a forcefield

          if (obj->type == OBJ_WEAPON && (obj->mtype.phys_info.flags & PF_BOUNCE))
            obj->mtype.phys_info.flags &= (~PF_NO_COLLIDE_PARENT);

          // Slide object along wall

          // We're constrained by wall, so subtract wall part from the velocity vector
          wall_part = hit_info.hit_wallnorm[0] * obj->mtype.phys_info.velocity;

          if ((obj->mtype.phys_info.num_bounces <= 0) && (obj->mtype.phys_info.flags & PF_STICK)) {
            obj->movement_type = MT_NONE;
            vm_MakeZero(&obj->mtype.phys_info.velocity);
            obj->last_pos = init_pos;
            goto end_of_sim;
          } else if (f_forcefield || (obj->mtype.phys_info.flags & PF_BOUNCE)) {
            wall_part *= 2.0; // Subtract out wall part twice to achieve bounce

            if (f_forcefield) {
              if (obj->type == OBJ_PLAYER)
                wall_part *= 2; // player bounce twice as much -- chrishack try without this too.
            }

            bounced = 1; // this object bounced
            // mprintf(0, "(%f, %f, %f) before bounce\n", XYZ(&obj->mtype.phys_info.velocity));
            obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0] * (wall_part * -1.0f);

            if (obj->mtype.phys_info.coeff_restitution != 1.0f)
              obj->mtype.phys_info.velocity -=
                  (obj->mtype.phys_info.velocity * (1.0f - obj->mtype.phys_info.coeff_restitution));

            // mprintf(0, "(%f, %f, %f) after bounce\n", XYZ(&obj->mtype.phys_info.velocity));
            // mprintf(0, "p (%f, %f, %f) after bounce\n", XYZ(&obj->pos));
          } else {
            float wall_force;

            wall_force = total_force * hit_info.hit_wallnorm[0];
            total_force +=
                hit_info.hit_wallnorm[0] * (wall_force * -1.001); // 1.001 so that we are not quite tangential

            // Update velocity from wall hit.
            obj->mtype.phys_info.velocity +=
                hit_info.hit_wallnorm[0] * (wall_part * -1.001); // 1.001 so that we are not quite tangential

            if ((obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER || OBJ_CLUTTER ||
                 (obj->type == OBJ_BUILDING && obj->ai_info)) &&
                sim_time_remaining == old_sim_time_remaining) {
              obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0];
            }

            if (obj->type == OBJ_PLAYER || OBJ_CLUTTER) {
              float real_vel;

              real_vel = vm_NormalizeVector(&obj->mtype.phys_info.velocity);
              obj->mtype.phys_info.velocity *= ((real_vel + luke_test) / 2);
              // obj->mtype.phys_info.velocity *= (luke_test);
            }
          }

          // mprintf(0, "PHYSICS: Wall normal (%f, %f, %f)\n", XYZ(&hit_info.hit_wallnorm[0]));
          // mprintf(0, "PHYSICS: Bounded velocity (%f, %f, %f)\n", XYZ(&obj->mtype.phys_info.velocity));

          // This only happens if the new velocity is set from hitting a forcefield.
          if (!(fabs(obj->mtype.phys_info.velocity.x) < MAX_OBJECT_VEL &&
                fabs(obj->mtype.phys_info.velocity.y) < MAX_OBJECT_VEL &&
                fabs(obj->mtype.phys_info.velocity.z) < MAX_OBJECT_VEL)) {
            float mag = vm_NormalizeVector(&obj->mtype.phys_info.velocity);

            mprintf(0, "PHYSICS:  Bashing vel for Obj %d of type %d with %f velocity", objnum, obj->type, mag);
            obj->mtype.phys_info.velocity *= MAX_OBJECT_VEL * 0.1f;
          }

          // Weapons should face their new heading.  This is so missiles are pointing in the correct direct.
          if (obj->type == OBJ_WEAPON && (bounced || (obj->mtype.phys_info.flags & (PF_GRAVITY | PF_WIND))))
            if (obj->mtype.phys_info.velocity != Zero_vector)
              vm_VectorToMatrix(&obj->orient, &obj->mtype.phys_info.velocity, &obj->orient.uvec, NULL);
        }
      }
      // else
      //{
      /*				vector r1 = hit_info.hit_face_pnt[0] - obj->pos;
                                      vector w1;
                                      vector n1;
                                      float temp1;

                                      float j;

                                      matrix o_t1 = obj->orient;
                                      vm_TransposeMatrix(&o_t1);
                                      vector cmp1 = obj->mtype.phys_info.rotvel * o_t1;
                                      ConvertEulerToAxisAmount(&cmp1, &n1, &temp1);

                                      n1 *= temp1;

                                      if(temp1 != 0.0f)
                                      {
                                              vm_CrossProduct(&w1, &n1, &r1);
                                      }
                                      else
                                      {
                                              w1 = Zero_vector;
                                      }

                                      vector p1 = obj->mtype.phys_info.velocity + w1; // *((2.0f*(float)PI)/65535.0f);

                                      if(p1.y < 0.0)
                                      {
      //					if(p1.y == 0.0)
      //						mprintf(0, "AT REST: p1 (%f, %f, %f)\n", XYZ(&p1));
      //					else
      //						mprintf(0, "SHIT: p1 (%f, %f, %f)\n", XYZ(&p1));
      //
      //					p1.y = -.0001f;
      //					}


                                              float v_rel;

                                              float m1 = obj->mtype.phys_info.mass;

                                              v_rel = hit_info.hit_wallnorm[0] * (p1);

                                              float e = .1f;

                                              vector c1;
                                              vector cc1;
                                              float cv1;

                                              float i1 = (m1/12.0)*(2.0f * pow(obj->size*2.0, 2));

                                              vm_CrossProduct(&c1, &r1, &hit_info.hit_wallnorm[0]);

                                              c1 = c1/i1;

                                              vm_CrossProduct(&cc1, &c1, &r1);

                                              cv1 = (hit_info.hit_wallnorm[0])*c1;

                                              j = (-(1.0f + e))*v_rel;
                                              j /= (1/m1 + cv1);

                                              obj->mtype.phys_info.velocity += ((j*(hit_info.hit_wallnorm[0]))/m1);

                                              vector jcn = j * (hit_info.hit_wallnorm[0]);

                                              vm_CrossProduct(&c1, &r1, &jcn);

                                              n1 = (c1)/i1;

                                              temp1 = vm_NormalizeVector(&n1);

                                              vector txx1;

                                              ConvertAxisAmountToEuler(&n1, &temp1, &txx1);

                                              obj->mtype.phys_info.rotvel += (txx1*obj->orient);
                                      }
                                      else
                                      {
                                              obj->mtype.phys_info.velocity.y = .001f;
                                              obj->mtype.phys_info.rotvel = Zero_vector;
                                      }*/

      //				}

      f_continue_sim = true;

    } break;

    case HIT_OBJECT:
    case HIT_SPHERE_2_POLY_OBJECT: {
      vector old_force; // -- chrishack

      // Mark the hit object so that on the following sim frames, in this game frame, ignore this object.
      ASSERT(hit_info.hit_object[0] != -1); // chrishack move this ASSERT fvi stuff above

      // chrishack -- we should have this point from FVI!!!!!!!!!!!
      //	Calculcate the hit point between the two objects.
      // old_vel = obj->mtype.phys_info.velocity;
      old_force = obj->mtype.phys_info.thrust;

      obj->mtype.phys_info.thrust = total_force;

      //				hit_info.hit_wallnorm[0] *= -1.0f;

      collide_two_objects(obj, &Objects[hit_info.hit_object[0]], &hit_info.hit_face_pnt[0], &hit_info.hit_wallnorm[0],
                          &hit_info);
      if (obj->movement_type == MT_OBJ_LINKED)
        goto end_of_sim;

      total_force = obj->mtype.phys_info.thrust;

      obj->mtype.phys_info.thrust = old_force;

      if ((obj->type == OBJ_ROBOT || obj->type == OBJ_PLAYER || OBJ_CLUTTER ||
           (obj->type == OBJ_BUILDING && obj->ai_info)) &&
          sim_time_remaining == old_sim_time_remaining && Objects[hit_info.hit_object[0]].movement_type == MT_NONE) {
        obj->mtype.phys_info.velocity += hit_info.hit_wallnorm[0];
      }

      // mprintf(0, "OBJ %d t %d hit %d\n", OBJNUM(obj), obj->type, hit_info.hit_object[0]);

      // Let object continue its movement if collide_two_objects does not mark it as dead
      //				if ( !(obj->flags&OF_DEAD)  )
      //				{
      //
      //					// chrishack -- check this later -- what is the old_vel stuff?
      //					if ((obj->mtype.phys_info.flags & PF_PERSISTENT) ||
      //						 (old_vel == obj->mtype.phys_info.velocity))
      //					{
      //						ignore_obj_list[n_ignore_objs++] = hit_info.hit_object[0];
      //					}
      //				}
      // Let object continue its movement if collide_two_objects does not mark it as dead
      if (!(obj->flags & OF_DEAD)) {
        if ((obj->mtype.phys_info.flags & PF_PERSISTENT) ||
            (Objects[hit_info.hit_object[0]].mtype.phys_info.flags & PF_PERSISTENT)) {
          if (n_ignore_objs < MAX_IGNORE_OBJS)
            ignore_obj_list[n_ignore_objs++] = hit_info.hit_object[0];
        } else if (Objects[hit_info.hit_object[0]].type == OBJ_POWERUP || obj->type == OBJ_POWERUP ||
                   Objects[hit_info.hit_object[0]].type == OBJ_MARKER || obj->type == OBJ_MARKER) {
          if (n_ignore_objs < MAX_IGNORE_OBJS)
            ignore_obj_list[n_ignore_objs++] = hit_info.hit_object[0];

          count--;
          if (count < -1)
            count = -1;
        }

        f_continue_sim = true;
      } else {
        f_continue_sim = false;
      }
    } break;

    case HIT_BAD_P0:
      mprintf(0, "PHYSICS ERROR: Bad p0 in physics!!!\n");
      Int3(); // Unexpected collision type: start point not in specified segment.
      break;

    default:
      mprintf(0, "PHYSICS ERROR: Unknown and unhandled hit type returned from FVI\n");
      Int3();
      break;
    }

    // Increment the simulation loop counter
    count++;

  } while ((f_continue_sim) && (!(obj->flags & OF_DEAD)) && (sim_time_remaining > 0.0f) && (count < sim_loop_limit));

  // Special stuff should we do if we hit the simulation loop limit
  //	If retry count is getting large, then we might be trying to do something bad.
  // NOTE: These numbers limit the max collisions an object can have in a single frame
  if (count >= sim_loop_limit) {
    if (obj->type == OBJ_PLAYER) {
      mprintf(0, "PHYSICS NOTE: Too many collisions for player!\n");
    } else {
      /*
      mprintf(0, "PHYSICS NOTE: Too many collisions for non-player object %d (%d to %d)!\n",
              objnum,
              init_room,
              obj->roomnum));
      obj->flags |= OF_DEAD;
      obj->mtype.phys_info.velocity /= 2.0f;
      obj->mtype.phys_info.rotvel /= 2.0f;
      */
    }

    // ObjSetPos(obj,&init_pos, init_room);
    // obj->last_pos = init_pos;
  }

end_of_sim:
  AttachUpdateSubObjects(obj);

  ASSERT(_finite(obj->mtype.phys_info.velocity.x) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.y) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.
  ASSERT(_finite(obj->mtype.phys_info.velocity.z) != 0); // Caller wants to go to infinity!  -- Not FVI's fault.

  obj->last_pos = init_pos;
  return;
}

//	-----------------------------------------------------------------------------------------------------------
// Simulate a physics object for this frame
void do_vis_physics_sim(vis_effect *vis) {
  if (Frametime <= 0.0f)
    return;

  vector total_force;
  vector old_pos = vis->pos;

#ifdef _DEBUG
  if (!Game_do_vis_sim) {
    return;
  }
#endif

  DebugBlockPrint("V ");

  if (vis->flags & VF_DEAD) {
    DebugBlockPrint("DV");
    return;
  }

  if (fabsf(vis->velocity.x) < 0.000001f && fabsf(vis->velocity.y) < 0.000001f && fabsf(vis->velocity.z) < 0.000001f &&
      !(vis->phys_flags & PF_GRAVITY)) {
    DebugBlockPrint("DV");
    return;
  }

  // Determine velocity
  if (vis->phys_flags & PF_FIXED_VELOCITY) {
    vis->pos += vis->velocity * Frametime;
  } else {
    if (vis->mass > 0.0f && vis->drag > 0.0f) {
      // If the object is effected by gravity (normal, lighter than air, and anti-gravity)
      if (vis->phys_flags & PF_GRAVITY) {
        total_force.x = total_force.z = 0.0f;
        total_force.y = Gravity_strength * vis->mass;
      } else if (vis->phys_flags & PF_REVERSE_GRAVITY) {
        total_force.x = total_force.z = 0.0f;
        total_force.y = -Gravity_strength * vis->mass;
      } else {
        total_force.x = total_force.y = total_force.z = 0.0f;
      }

      // Note: The math here is done in 64bit floats because we will run into precision problems with 32bit
      const double forceOverDrag[3] = {total_force.x / vis->drag, total_force.y / vis->drag, total_force.z / vis->drag};
      const double frameTime = Frametime;
      const double massOverDrag = vis->mass / vis->drag;
      const double dragOverMass = vis->drag / vis->mass;
      const double expDoMFt = exp(-dragOverMass * frameTime);

      double visNewPos[3];
      visNewPos[0] = double(vis->pos.x) + forceOverDrag[0] * frameTime +
                     massOverDrag * (double(vis->velocity.x) - forceOverDrag[0]) * (1.0 - expDoMFt);
      visNewPos[1] = double(vis->pos.y) + forceOverDrag[1] * frameTime +
                     massOverDrag * (double(vis->velocity.y) - forceOverDrag[1]) * (1.0 - expDoMFt);
      visNewPos[2] = double(vis->pos.z) + forceOverDrag[2] * frameTime +
                     massOverDrag * (double(vis->velocity.z) - forceOverDrag[2]) * (1.0 - expDoMFt);

      double visNewVel[3];
      visNewVel[0] = (double(vis->velocity.x) - forceOverDrag[0]) * expDoMFt + forceOverDrag[0];
      visNewVel[1] = (double(vis->velocity.y) - forceOverDrag[1]) * expDoMFt + forceOverDrag[1];
      visNewVel[2] = (double(vis->velocity.z) - forceOverDrag[2]) * expDoMFt + forceOverDrag[2];

      vis->pos.x = float(visNewPos[0]);
      vis->pos.y = float(visNewPos[1]);
      vis->pos.z = float(visNewPos[2]);
      vis->velocity.x = float(visNewVel[0]);
      vis->velocity.y = float(visNewVel[1]);
      vis->velocity.z = float(visNewVel[2]);
    } else {
      vector delta_velocity = {0.0f, 0.0f, 0.0f};

      if (vis->phys_flags & PF_GRAVITY) {
        delta_velocity.y += Gravity_strength * Frametime;
      } else if (vis->phys_flags & PF_REVERSE_GRAVITY) {
        delta_velocity.y -= Gravity_strength * Frametime;
      }

      vis->pos += (vis->velocity * Frametime) + (0.5f * delta_velocity * Frametime);
      vis->velocity += delta_velocity;
    }
  }

  if (vis->phys_flags & PF_NO_COLLIDE) {
    DebugBlockPrint("DV");
    return;
  }

  Physics_vis_counter++;

  // Do FVI call to check for death & update room
  fvi_query fq;
  fvi_info hit_info;
  int fate;

  if (ROOMNUM_OUTSIDE(vis->roomnum)) {
    ASSERT(CELLNUM(vis->roomnum) <= TERRAIN_WIDTH * TERRAIN_DEPTH);
    ASSERT(CELLNUM(vis->roomnum) >= 0);
  } else {
    ASSERT(vis->roomnum >= 0 && vis->roomnum <= Highest_room_index && Rooms[vis->roomnum].used);
  }

  fq.p0 = &old_pos;
  fq.startroom = vis->roomnum;
  fq.p1 = &vis->pos;
  fq.rad = 0.0f;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;
  fq.flags = FQ_CHECK_OBJS | FQ_ONLY_DOOR_OBJ | FQ_IGNORE_WALLS;

  fate = fvi_FindIntersection(&fq, &hit_info);

  if (fate == HIT_NONE && hit_info.hit_room != -1) {
    if (hit_info.hit_room != vis->roomnum) {
      VisEffectRelink(vis - VisEffects, hit_info.hit_room);
    }

    if (ROOMNUM_OUTSIDE(hit_info.hit_room)) {
      ASSERT(CELLNUM(hit_info.hit_room) <= TERRAIN_WIDTH * TERRAIN_DEPTH);
      ASSERT(CELLNUM(hit_info.hit_room) >= 0);
    } else {
      ASSERT(hit_info.hit_room >= 0 && hit_info.hit_room <= Highest_room_index && Rooms[hit_info.hit_room].used);
    }
  } else {
    VisEffectDelete(vis - VisEffects);
  }

  DebugBlockPrint("DV");
}

void phys_apply_force(object *obj, vector *force_vec, int16_t weapon_index) {
  if (obj->mtype.phys_info.mass == 0.0)
    return;

  if (obj->movement_type != MT_PHYSICS && obj->movement_type != MT_WALKING)
    return;

  if (obj->mtype.phys_info.flags & PF_LOCK_MASK) // Not done!
    return;

  if ((Game_mode & GM_MULTI) &&
      ((obj->type == OBJ_PLAYER && obj->id != Player_num) ||
       ((obj->type != OBJ_PLAYER && obj->type != OBJ_POWERUP) && Netgame.local_role != LR_SERVER)))
    return;

  // Do Force Feedback for the hit
  if (obj->id == Player_num) {
    // we need to convert collision_normal from world space to local space
    vector local_norm;
    float scale = 0, magnitude = 0;

    // compute how much force to do
    magnitude = vm_GetMagnitude(force_vec);
    if (magnitude) {
      scale = magnitude / 2500.0f;
      if (scale < 0.0f)
        scale = 0.0f;
      if (scale > 1.0f)
        scale = 1.0f;

      vm_MatrixMulVector(&local_norm, force_vec, &obj->orient);
      local_norm *= -1.0f;

      ForceEffectsPlay(FORCE_TEST_FORCE, &scale, &local_norm);
    }

    if (weapon_index != -1) {
      mprintf(0, "Force from weapon\n");
    }

    // mprintf(0,"Force: Magnitude = %f   Scale = %1.3f\n",magnitude,scale);

    VIBE_DoForce(force_vec);
  }
  //------------------------------

  // Add in acceleration due to force
  obj->mtype.phys_info.velocity += (*force_vec / obj->mtype.phys_info.mass);
}
/*
//	----------------------------------------------------------------
//	Do *dest = *delta unless:
//				*delta is pretty small
//		and	they are of different signs.

void physics_set_rotvel_and_saturate(float *dest, float delta)
{
        if ((delta ^ *dest) < 0) {
                if (abs(delta) < F1_0/8) {
                        // mprintf(0, "D");
                        *dest = delta/4;
                } else
                        // mprintf(0, "d");
                        *dest = delta;
        } else {
                // mprintf(0, "!");
                *dest = delta;
        }
}

//	------------------------------------------------------------------------------------------------------
//	Note: This is the old ai_turn_towards_vector code.
//	phys_apply_rot used to call ai_turn_towards_vector until I fixed it, which broke phys_apply_rot.

void physics_turn_towards_vector(vector *goal_vector, object *obj, float rate)
{
        vms_angvec	dest_angles, cur_angles;
        float			delta_p, delta_h;
        vector	*rotvel_ptr = &obj->mtype.phys_info.rotvel;

        // Make this object turn towards the goal_vector.  Changes orientation, doesn't change direction of movement.
        // If no one moves, will be facing goal_vector in 1 second.

        //	Detect null vector.
        if ((goal_vector->x == 0) && (goal_vector->y == 0) && (goal_vector->z == 0))
                return;

        //	Make morph objects turn more slowly.
        if (obj->control_type == CT_MORPH)
                rate *= 2;

        vm_extract_angles_vector(&dest_angles, goal_vector);
        vm_extract_angles_vector(&cur_angles, &obj->orient.fvec);

        delta_p = (dest_angles.p - cur_angles.p);
        delta_h = (dest_angles.h - cur_angles.h);

        if (delta_p > F1_0/2) delta_p = dest_angles.p - cur_angles.p - F1_0;
        if (delta_p < -F1_0/2) delta_p = dest_angles.p - cur_angles.p + F1_0;
        if (delta_h > F1_0/2) delta_h = dest_angles.h - cur_angles.h - F1_0;
        if (delta_h < -F1_0/2) delta_h = dest_angles.h - cur_angles.h + F1_0;

        delta_p = fixdiv(delta_p, rate);
        delta_h = fixdiv(delta_h, rate);

        if (abs(delta_p) < F1_0/16) delta_p *= 4;
        if (abs(delta_h) < F1_0/16) delta_h *= 4;

        physics_set_rotvel_and_saturate(&rotvel_ptr->x, delta_p);
        physics_set_rotvel_and_saturate(&rotvel_ptr->y, delta_h);
        rotvel_ptr->z = 0;
}
*/
//	-----------------------------------------------------------------------------
//	Applies an instantaneous whack on an object, resulting in an instantaneous
//	change in orientation.

void phys_apply_rot(object *obj, vector *force_vec) {
/*
  float rate, vecmag;

  if (obj->movement_type != MT_PHYSICS)
    return;

  vecmag = vm_VectorMagnitude(force_vec);

  if (vecmag < F1_0 / 256)
    rate = 4 * F1_0;
  else if (vecmag < obj->mtype.phys_info.mass >> 14)
    rate = 4 * F1_0;
  else {
    rate = fixdiv(obj->mtype.phys_info.mass, vecmag);

    if (obj->type == OBJ_ROBOT) {
      if (rate < F1_0 / 4)
        rate = F1_0 / 4;
      //	Changed by mk, 10/24/95, claw guys should not slow down when attacking!
      if (!Robot_info[obj->id].thief && !Robot_info[obj->id].attack_type) {
        if (obj->ctype.ai_info.SKIP_AI_COUNT * Frametime < 3 * F1_0 / 4) {
          float tval = fixdiv(F1_0, 8 * Frametime);
          int addval;
          addval = f2i(tval);
          if ((rand() * 2) < (tval & 0xffff))
            addval++;
          obj->ctype.ai_info.SKIP_AI_COUNT += addval;
          // -- mk: too much stuff making hard to see my debug messages...
          mprintf(0, "Frametime = %7.3f, addval = %i\n", f2fl(Frametime), addval);
        }
      }
    } else {
      if (rate < F1_0 / 2)
        rate = F1_0 / 2;
    }
  }

  // Turn amount inversely proportional to mass.  Third parameter is seconds to do 360 turn.
  physics_turn_towards_vector(force_vec, obj, rate);
*/
}
/*
//this routine will set the thrust for an object to a value that will
//(hopefully) maintain the object's current velocity

void set_thrust_from_velocity(object *obj)
{
        Int3();
//	float k;
//
//	ASSERT(obj->movement_type == MT_PHYSICS);
//
//	k = fixmuldiv(obj->mtype.phys_info.mass,obj->mtype.phys_info.drag,(f1_0-obj->mtype.phys_info.drag));
//
//	vm_vec_copy_scale(&obj->mtype.phys_info.thrust,&obj->mtype.phys_info.velocity,k);
//
}
*/

// Checks if an object is on the ground (we might do more in this function at a latter date) --chrishack
int check_obj_on_ground(object *obj, fvi_info *hit_info_ptr) {
  vector ground;
  fvi_query fq;

  ASSERT(obj->size - 2 * PHYSICS_GROUND_TOLERANCE > 0.0f);

  ground = obj->pos;
  // This should account for an object that touches more than one face.  (To find the real ground).
  ground.y -= (obj->size + 3 * PHYSICS_GROUND_TOLERANCE);

  fq.p0 = &obj->pos;
  fq.startroom = obj->roomnum;
  fq.p1 = &ground;
  fq.rad = obj->size - 2 * PHYSICS_GROUND_TOLERANCE;
  fq.thisobjnum = OBJNUM(obj);
  fq.ignore_obj_list = NULL;
  fq.flags = FQ_CHECK_OBJS;

  if (obj->flags & OF_NO_OBJECT_COLLISIONS)
    fq.flags &= ~FQ_CHECK_OBJS;

  return fvi_FindIntersection(&fq, hit_info_ptr);
}
