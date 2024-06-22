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

 * $Logfile: /DescentIII/Main/lib/polymodel_external.h $
 * $Revision: 7 $
 * $Date: 10/02/01 8:56a $
 * $Author: Matt $
 *
 * Polymodel defines, flags and structs (anything that could be exported to a DLL)
 *
 * $Log: /DescentIII/Main/lib/polymodel_external.h $
 *
 * 7     10/02/01 8:56a Matt
 * Increased MAX_POLY_MODELS from 1000 to 1200
 *
 * 6     7/08/99 5:47p Jason
 * changes for new bumpmapping system in 1.1 update patch
 *
 * 5     6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 4     4/20/99 1:02p 3dsmax
 * fixed polymodel loimt
 *
 * 3     4/08/99 11:45a Jason
 * greatly sped up the time it takes to get model anges/positions by
 * precalculation
 *
 * 2     1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * $NoKeywords: $
 */

#ifndef __POLYMODEL_EXTERNAL_H_
#define __POLYMODEL_EXTERNAL_H_

#include "vecmat_external.h"
#include "pstypes.h"
#include "grdefs.h"
#include "manage_external.h"

#define MAX_POLY_MODELS 1200

#define MAX_MODEL_TEXTURES 35
#define MAX_POLYGON_VECS 2500
#define MAX_DETAIL_LEVELS 3
#define MAX_PROP_LEN 256
#define MAX_NAME_LEN 32

#define MAX_GROUND_PLANES_PER_MODEL 10
#define MAX_GUNS_PER_MODEL 64
#define MAX_SUBOBJECTS 30
#define MAX_POINTS_PER_SUBOBJECT 300

// Subobject flags
#define SOF_ROTATE 0x01    // This subobject is a rotator
#define SOF_TURRET 0x02    // This subobject is a turret that tracks
#define SOF_SHELL 0x04     // This subobject is a door housing
#define SOF_FRONTFACE 0x08 // This subobject contains the front face for the door
#define SOF_MONITOR1 0x010 // This subobject contains it's first monitor
#define SOF_MONITOR2 0x020 // This subobject contains it's second monitor
#define SOF_MONITOR3 0x040 // This subobject contains it's third monitor
#define SOF_MONITOR4 0x080 // This subobject contains it's fourth monitor
#define SOF_MONITOR5 0x0100
#define SOF_MONITOR6 0x0200
#define SOF_MONITOR7 0x0400
#define SOF_MONITOR8 0x0800
#define SOF_FACING 0x01000       // This subobject always faces you
#define SOF_VIEWER 0x02000       // This subobject is marked as a 'viewer'.
#define SOF_LAYER 0x04000        // This subobject is marked as part of possible secondary model rendering.
#define SOF_WB 0x08000           // This subobject is part of a weapon battery
#define SOF_GLOW 0x0200000       // This subobject glows
#define SOF_CUSTOM 0x0400000     // This subobject has textures/colors that are customizable
#define SOF_THRUSTER 0x0800000   // This is a thruster subobject
#define SOF_JITTER 0x01000000    // This object jitters by itself
#define SOF_HEADLIGHT 0x02000000 // This suboject is a headlight

// gun bank
struct w_bank {
  int parent;
  vector pnt;
  vector norm;
};

// attach bank
struct a_bank {
  int parent;
  vector pnt;
  vector norm;
  vector uvec;
  bool f_uvec;
};

struct lightmap_object_face {
  uint8_t num_verts;
  uint16_t lmi_handle;
  vector rvec, uvec;
  float *u2, *v2;
};

struct lightmap_object {
  uint8_t num_models;

  int16_t num_faces[MAX_SUBOBJECTS];
  lightmap_object_face *lightmap_faces[MAX_SUBOBJECTS];
  uint8_t used;

};

struct polyface {
  int8_t nverts;
  int16_t *vertnums;
  float *u;
  float *v;

  // float *u2,*v2;						// For lightmaps only

  ddgr_color color;
  int16_t texnum;

  vector normal;
};

// glow info
struct glowinfo {
  float glow_r, glow_g, glow_b, glow_size, glow_length;
  vector center, normal;
};

// bsp information
struct bsp_info {
  char name[PAGENAME_LEN]; // name of the subsystem.  Probably displayed on HUD
  int movement_type;       //-1 if no movement, otherwise rotational or positional movement -- subobjects only
  int movement_axis;       // which axis this subobject moves or rotates on.
  int tree_offset;         // offset of tree data (children included) into the model_data
  int data_offset;         // offset of data into the model_data
  vector offset;           // 3d offset from parent object
  vector norm;             // norm for sep plane
  float d;                 // norm d for sep plane
  vector pnt;              // point for sep plane
  vector geometric_center; // geometric center of this subobject.  In the same Frame Of
                           // Reference as all other vertices in this submodel. (Relative to pivot point)
  float rad;               // radius for each submodel

  vector *verts; // vertices for the submodel (NEWSTYLE)
  vector *vertnorms;
  float *alpha;
  polyface *faces; // faces for the submodel (NEWSTYLE)
  vector *face_min;
  vector *face_max;

  int16_t *vertnum_memory;
  float *u_memory;
  float *v_memory;

  int nverts;
  int num_faces; // amount of faces (NEWSTYLE);

  int8_t children[MAX_SUBOBJECTS]; // children of this submodel
  int parent;                     // what is parent for each submodel
  uint8_t num_children;

  vector min;
  vector max;
  int blown_off; // If set, this subobject is blown off. Stuffed by model_set_instance

  angvec angs;
  matrix mod_matrix; // The angles from parent.  Stuffed by model_set_instance
  vector mod_pos;    // The modified position of this object.  Used for positional interpolation

  vector *keyframe_axis; // the axis of rotation for each keyframe
  int *keyframe_angles;  // The destination angles for each key frame
  vector *keyframe_pos;
  matrix *keyframe_matrix; // the combined rotation matrices up to frame n
  uint16_t *tick_pos_remap;  // For looking up keyframes fast
  uint16_t *tick_ang_remap;  // For looking up keyframes fast
  int *rot_start_time;
  int *pos_start_time;

  int num_key_angles;
  int num_key_pos;

  int flags; // see SOF_FLAGS above

  int rot_track_min, rot_track_max;
  int pos_track_min, pos_track_max;

  float rps;            // if SOF_ROTATE or SOF_TURRET is set, this is the rotations per second
  float fov;            // Half the normalized angle that this turret is allowed to turn (amount in each direction)
  float think_interval; // How quickly a turret updates which way it should move

  float normalized_angle;

  glowinfo *glow_info;
};

#define PMF_LIGHTMAP_RES 1
#define PMF_TIMED 2          // Uses new timed animation
#define PMF_ALPHA 4          // Has alpha per vertex qualities
#define PMF_FACING 8         // Has a submodel that is always facing
#define PMF_NOT_RESIDENT 16  // This polymodel is not in memory
#define PMF_SIZE_COMPUTED 32 // This polymodel's size is computed

// used to describe a polygon model
struct poly_model {
  uint16_t used;

  int flags;       // PMF_flags, see above
  uint8_t new_style; // if 1, then this polymodel is in the new outrage format (oof)
  int id;          // what the polygon model number is.  (Index in Poly_models)
  int version;
  char name[PAGENAME_LEN];

  int n_models;
  int model_data_size;
  uint8_t *model_data;

  vector mins, maxs; // min,max for whole model
  vector view_pos;   // viewing position.  Default to {0,0,0}.

  float wall_size;
  vector wall_size_offset;

  float anim_size;
  vector anim_size_offset;

  float rad;
  int n_textures;
  int16_t textures[MAX_MODEL_TEXTURES]; // a list of bitmap indices

  bsp_info *submodel; // an array of size n_models of submodel info.
  int num_key_angles;
  int num_key_pos;
  int max_keys; // the greater number of num_key_pos or num_key_angles

  int frame_min, frame_max; // For TIMED polymodels, the min/max frames

  int n_guns;
  w_bank *gun_slots; // array of gun banks

  int n_ground;
  w_bank *ground_slots; // array of ground planes

  int n_attach;
  a_bank *attach_slots;

  int num_wbs;
  poly_wb_info *poly_wb; // array of weapon batteries

  int *render_order; // internal use

};

// Which kind of lighting model for this polymodel
enum polymodel_light_type {
  POLYMODEL_LIGHTING_STATIC,
  POLYMODEL_LIGHTING_GOURAUD,
  POLYMODEL_LIGHTING_LIGHTMAP,
};

// polymodel effects stuff
// Effect flags:
#define PEF_ALPHA 1
#define PEF_DEFORM 2
#define PEF_COLOR 4
#define PEF_MED_RES 8
#define PEF_LO_RES 16
#define PEF_FOG 32
#define PEF_CUSTOM_COLOR 64
#define PEF_CUSTOM_TEXTURE 128
#define PEF_FOGGED_MODEL 256
#define PEF_SPECULAR_MODEL 512
#define PEF_SPECULAR_FACES 1024
#define PEF_GLOW_SCALAR 2048
#define PEF_THRUSTER_SCALAR 4096
#define PEF_DRAW_HEADLIGHTS 8192
#define PEF_NO_GLOWS (8192 << 1)
#define PEF_CUSTOM_GLOW (8192 << 2)
#define PEF_BUMPMAPPED (8192 << 3)

struct polymodel_effect {
  int type;
  float alpha;
  float deform_range;
  float r, g, b;
  float fog_r, fog_g, fog_b;
  int custom_texture;
  int custom_color;

  float spec_r, spec_g, spec_b;
  vector spec_light_pos;
  float spec_scalar;

  vector bump_light_pos;
  float bump_scalar;

  float fog_depth;
  float fog_eye_distance;
  float fog_distance;
  vector fog_plane, fog_portal_vert;
  int fog_plane_check;

  float glow_length_scalar;
  float glow_size_scalar;

  float glow_r, glow_g, glow_b;

};

#endif
