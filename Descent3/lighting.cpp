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

 * $Logfile: /DescentIII/Main/lighting.cpp $
 * $Revision: 109 $
 * $Date: 10/02/01 12:34p $
 * $Author: Matt $
 * $NoKeywords: $
 */

#include "3d.h"
#include "texture.h"
#include "gametexture.h"
#include "lighting.h"
#include "lightmap.h"
#include "descent.h"
#include "game.h"
#include "room.h"
#include <string.h>
#include <stdlib.h>
#include "findintersection.h"
#include "lightmap_info.h"
#include "polymodel.h"
#include "special_face.h"
#include "mem.h"
#include "config.h"
#include "dedicated_server.h"
#include "objinfo.h"
#include "Macros.h"

#include <algorithm>

#define NUM_DYNAMIC_CLASSES 7
#define MAX_DYNAMIC_FACES 2000
#define MAX_DYNAMIC_CELLS 1500
#define MAX_VOLUME_OBJECTS 500

// How much memory set aside for dynamic lightmaps
// Currently 3 megs

int DYNAMIC_LIGHTMAP_MEMORY = 1000000;
#define MAX_DYNAMIC_LIGHTMAPS 2000

struct volume_object {
  int objnum;
  int handle;
};

float Specular_tables[3][MAX_SPECULAR_INCREMENTS];

static uint16_t *Dynamic_lightmap_memory = NULL;
static float Light_component_scalar[32];
float Ubyte_to_float[256];

static uint8_t Lmi_spoken_for[MAX_LIGHTMAP_INFOS / 8];

static dynamic_lightmap *Dynamic_lightmaps;
static dynamic_face Dynamic_face_list[MAX_DYNAMIC_FACES];
static uint16_t Specular_face_list[MAX_DYNAMIC_FACES];
static volume_object Dynamic_volume_object_list[MAX_VOLUME_OBJECTS];
static dynamic_cell Dynamic_cell_list[MAX_DYNAMIC_CELLS];
static int Specular_maps[NUM_DYNAMIC_CLASSES];

static uint16_t Edges_to_blend[MAX_DYNAMIC_LIGHTMAPS];
static int Num_edges_to_blend = 0;

static int Num_specular_faces = 0;
static int Num_dynamic_faces = 0;
static int Num_dynamic_lightmaps = 0;
static int Cur_dynamic_mem_ptr = 0;
static int Num_volume_objects = 0;
static int Num_dynamic_cells = 0;
static int Num_destroyed_lights_this_frame = 0;

#define MAX_DESTROYED_LIGHTS_PER_FRAME 20
static int Destroyed_light_rooms_this_frame[MAX_DESTROYED_LIGHTS_PER_FRAME];
static int Destroyed_light_faces_this_frame[MAX_DESTROYED_LIGHTS_PER_FRAME];

static void FreeLighting();
static int GetFreeDynamicLightmap(int w, int h);
static void BlendLightingEdges(lightmap_info *lmi_ptr);
static void ApplyLightingToExternalRoom(vector *pos, int roomnum, float light_dist, float red_scale, float green_scale,
                                        float blue_scale, vector *light_direction, float dot_range);
static void StartLightingInstance(vector *pos, matrix *orient);
static void DoneLightingInstance();
static void ApplyLightingToSubmodel(object *obj, poly_model *pm, bsp_info *sm, float light_dist, float red_scale,
                                    float green_scale, float blue_scale, float dot_range);
static void ApplyVolumeLightToObject(vector *pos, object *obj, float light_dist, float red_scale, float green_scale,
                                     float blue_scale, vector *light_direction, float dot_range);
static void ApplyLightingToObjects(vector *pos, int roomnum, float light_dist, float red_scale, float green_scale,
                                   float blue_scale, vector *light_direction, float dot_range);

// Frees memory used by dynamic light structures
void FreeLighting() {
  if (Dynamic_lightmap_memory)
    mem_free(Dynamic_lightmap_memory);
  if (Dynamic_lightmaps)
    mem_free(Dynamic_lightmaps);
}

// Sets up our dynamic lighting maps
// and tables
void InitDynamicLighting() {
  int i, cl, size;

  mprintf(0, "Initting dynamic lighting.\n");

  memset(Lmi_spoken_for, 0, MAX_LIGHTMAP_INFOS / 8);

  for (i = 0; i < 16; i++)
    Light_component_scalar[i] = i / 15.0;
  for (i = 16; i < 32; i++)
    Light_component_scalar[i] = 1.0;

  for (cl = 0, size = 128; size >= 2; size >>= 1, cl++) {
    Specular_maps[cl] = lm_AllocLightmap(size, size);
    ASSERT(Specular_maps[cl] != BAD_LM_INDEX);
  }

  // Init our dynamic memory
  if (Mem_low_memory_mode) {
    // Just use 1 meg if in low mem mode
    DYNAMIC_LIGHTMAP_MEMORY = 500000;
  }

  Dynamic_lightmap_memory = (uint16_t *)mem_malloc(DYNAMIC_LIGHTMAP_MEMORY);

  // Init our records list
  Dynamic_lightmaps = (dynamic_lightmap *)mem_malloc(sizeof(dynamic_lightmap) * MAX_DYNAMIC_LIGHTMAPS);
  ASSERT(Dynamic_lightmaps);

  for (i = 0; i < MAX_DYNAMIC_LIGHTMAPS; i++) {
    memset(&Dynamic_lightmaps[i], 0, sizeof(dynamic_lightmap));
  }

  // Setup uint8_t to float
  for (i = 0; i < 256; i++)
    Ubyte_to_float[i] = (float)i / 255.0;

  // Setup specular tables
  mprintf(0, "Building specular tables.\n");

  for (i = 0; i < MAX_SPECULAR_INCREMENTS; i++) {
    float val = (float)i / (float)(MAX_SPECULAR_INCREMENTS - 1);

    // Metal
    Specular_tables[0][i] = (val * val * val * val * val * val);

    // Plastic
    Specular_tables[1][i] = (val * val * val * val * val * val * val * val * val * val * val * val * val * val);

    // Marble
    Specular_tables[2][i] = (val * val * val * val);
  }

  atexit(FreeLighting);
}

// Given a float, returns the index into the Ubyte_float_table that this number
// corresponds to
uint8_t Float_to_ubyte(float fnum) {
  int i;

  if (fnum < 0 || fnum > 1.0) {
    mprintf(0, "ERROR: Trying to get value in Float_to_ubyte that is %f!\n", fnum);
    return 0;
  }

  for (i = 0; i < 256; i++) {
    if (fnum < Ubyte_to_float[i])
      return i;
  }

  return 255;
}

// Returns an index into the Dynamic_lightmaps array.  Index returned is marked as unused
int GetFreeDynamicLightmap(int w, int h) {
  int total = w * h * 2;

  if (Num_dynamic_lightmaps == MAX_DYNAMIC_LIGHTMAPS)
    return -1;

  if (total + Cur_dynamic_mem_ptr > DYNAMIC_LIGHTMAP_MEMORY) {
    mprintf(0, "Ran out of lightmap memory (%d)\n", DYNAMIC_LIGHTMAP_MEMORY);
    return -1;
  }

  int n = Num_dynamic_lightmaps++;
  ASSERT(Dynamic_lightmaps[n].used == 0);

  Dynamic_lightmaps[n].used = 1;
  Dynamic_lightmaps[n].mem_ptr = &Dynamic_lightmap_memory[Cur_dynamic_mem_ptr / 2];
  ASSERT(Dynamic_lightmaps[n].mem_ptr);

  Cur_dynamic_mem_ptr += total;

  return n;
}

// Makes all the edges of dynamic lighting blend into the body of the lightmap
void BlendLightingEdges(lightmap_info *lmi_ptr) {
  int lmi_handle = lmi_ptr - LightmapInfo;
  int h = lmi_h(lmi_handle);
  int w = lmi_w(lmi_handle);
  int lm_handle = lmi_ptr->lm_handle;
  uint16_t *dest_data = (uint16_t *)lm_data(lm_handle);
  uint16_t *src_data = dest_data;
  int dest_x = lmi_ptr->x1 - 1;
  int dest_y = lmi_ptr->y1 - 1;
  int i;

  ASSERT(dest_data);
  if (!dest_data)
    return;

  ASSERT(dest_x >= 0 && dest_y >= 0);
  ASSERT(dest_x + w < 127);
  ASSERT(dest_y + h < 127);

  for (i = 0; i < h; i++) {
    // Left edge
    dest_data[((dest_y + 1 + i) * 128) + dest_x] = src_data[((dest_y + 1 + i) * 128) + dest_x + 1];
    // Right edge
    dest_data[((dest_y + 1 + i) * 128) + dest_x + w + 1] = src_data[((dest_y + 1 + i) * 128) + dest_x + w];
  }

  for (i = 0; i < w; i++) {
    // Top edge
    dest_data[(dest_y * 128) + (dest_x + i + 1)] = src_data[((dest_y + 1) * 128) + (dest_x + i + 1)];
    // Bottom edge
    dest_data[((dest_y + 1 + h) * 128) + (dest_x + i + 1)] = src_data[((dest_y + h) * 128) + (dest_x + i + 1)];
  }

  // Now copy the corners
  // Upper left
  dest_data[(dest_y * 128) + (dest_x)] = src_data[((dest_y + 1) * 128) + (dest_x + 1)];
  // Upper right
  dest_data[(dest_y * 128) + (dest_x + w + 1)] = src_data[((dest_y + 1) * 128) + (dest_x + w)];
  // Lower left
  dest_data[((dest_y + h + 1) * 128) + (dest_x)] = src_data[((dest_y + h) * 128) + (dest_x + 1)];
  // Lower right
  dest_data[((dest_y + h + 1) * 128) + (dest_x + w + 1)] = src_data[((dest_y + h) * 128) + (dest_x + w)];
}

// Does lighting for the passed in external room
void ApplyLightingToExternalRoom(vector *pos, int roomnum, float light_dist, float red_scale, float green_scale,
                                 float blue_scale, vector *light_direction, float dot_range) {
  int i, lm_handle, t;
  uint16_t *dest_data;
  vector rad;
  room *rp = &Rooms[roomnum];
  vector Light_min_xyz;
  vector Light_max_xyz;
  uint16_t lmilist[MAX_DYNAMIC_FACES];
  int num_spoken_for = 0;

  int red_limit = 31;
  int green_limit = 31;
  int blue_limit = 31;

  rad.x = light_dist;
  rad.y = light_dist;
  rad.z = light_dist;

  Light_min_xyz = *pos - rad;
  Light_max_xyz = *pos + rad;

  // Now the Light_position is in the submodels frame of reference
  for (i = 0; i < rp->num_faces; i++) {
    face *fp = &rp->faces[i];

    // check to see if this face is within reach
    if (Light_max_xyz.y < fp->min_xyz.y || fp->max_xyz.y < Light_min_xyz.y || Light_max_xyz.x < fp->min_xyz.x ||
        fp->max_xyz.x < Light_min_xyz.x || Light_max_xyz.z < fp->min_xyz.z || fp->max_xyz.z < Light_min_xyz.z)
      continue;

    // Make sure face was rendered
    if (fp->renderframe != ((FrameCount - 1) % 256))
      continue;

    if (Num_dynamic_faces >= MAX_DYNAMIC_FACES) {
      mprintf(0, "Too many dynamic faces!\n");
      return;
    }

    // Make sure there already is a lightmap for this face
    if (!(fp->flags & FF_LIGHTMAP))
      continue;

    if (Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))
      continue;

    int xres = lmi_w(fp->lmi_handle);
    int yres = lmi_h(fp->lmi_handle);

    lightmap_info *lmi_ptr = &LightmapInfo[fp->lmi_handle];
    // Lightmap width and height
    int lmw = lm_w(lmi_ptr->lm_handle);

    // Check for backfaces
    vector subvec = *pos - lmi_ptr->upper_left;
    float dist_from_plane = fabs(vm_DotProduct(&subvec, &lmi_ptr->normal));

    if (dist_from_plane > light_dist)
      continue;

    if (light_direction) {
      // If this is a directional light, check for backfaces
      vector norm_vec = *pos - rp->verts[fp->face_verts[0]];

      if ((norm_vec * lmi_ptr->normal) < 0) {
        // Backface, skip this light
        continue;
      }
      // Test to see if all vertices are behind the light object, if so then bail
      int in_front = 0; //
      for (t = 0; t < fp->num_verts && in_front == 0; t++) {
        norm_vec = rp->verts[fp->face_verts[t]] - *pos;
        if (norm_vec * *light_direction > 0)
          in_front = 1;
      }

      if (!in_front) // This face is completely behind, so bail!
        continue;
    }

    // Compute face matrix
    matrix facematrix;
    vector fvec = -lmi_ptr->normal;
    vm_VectorToMatrix(&facematrix, &fvec, NULL, NULL);

    // Get upper left vector of face
    vector base_vector = lmi_ptr->upper_left;

    // Get the area of effect for this light
    float area_of_effect = (1.0 - (dist_from_plane / light_dist)) * light_dist;
    vector touch_vector = *pos - (lmi_ptr->normal * dist_from_plane);

    subvec = touch_vector - base_vector;
    float rdist = vm_DotProduct(&subvec, &facematrix.rvec);
    float udist = -vm_DotProduct(&subvec, &facematrix.uvec);
    int x_add = 1 + ((area_of_effect + (lmi_ptr->xspacing / 2)) / lmi_ptr->xspacing);
    int y_add = 1 + ((area_of_effect + (lmi_ptr->yspacing / 2)) / lmi_ptr->yspacing);

    // Get the rectangle of the lightmap that we want to light
    int start_x = (rdist / lmi_ptr->xspacing) - x_add;
    int start_y = (udist / lmi_ptr->yspacing) - y_add;
    int end_x = (rdist / lmi_ptr->xspacing) + x_add + .5;
    int end_y = (udist / lmi_ptr->yspacing) + y_add + .5;

    if (end_x < 0 || end_y < 0 || start_x >= (xres) || start_y >= (yres))
      continue;

    if (start_x < 0)
      start_x = 0;
    if (start_y < 0)
      start_y = 0;
    if (end_x > xres)
      end_x = xres;
    if (end_y > yres)
      end_y = yres;

    int width = end_x - start_x;
    int height = end_y - start_y;

    if (width == 0)
      width++;
    if (height == 0)
      height++;

    ASSERT(width > 0);
    ASSERT(height > 0);

    if (lmi_ptr->dynamic != BAD_LM_INDEX) // already lit, so just adjust, not start over
    {
      lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
      dest_data = (uint16_t *)lm_data(lm_handle);

      if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
      if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

      if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
      if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;

      GameLightmaps[lm_handle].flags |= (LF_CHANGED | LF_LIMITS);

      if (!(Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))) {
        lmilist[num_spoken_for] = fp->lmi_handle;
        Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
        num_spoken_for++;
      }
    } else // Start a new dynamic lightmap
    {
      // First find a suitable dynamic lightmap to work with
      int dynamic_handle = GetFreeDynamicLightmap(xres, yres);

      if (dynamic_handle < 0) {
        mprintf(0, "No free dynamic maps!\n");
        return; // None free!
      }

      // Now copy our source data to our dest data so we have a base to work with
      uint16_t *src_data;

      src_data = (uint16_t *)lm_data(LightmapInfo[fp->lmi_handle].lm_handle);
      dest_data = Dynamic_lightmaps[dynamic_handle].mem_ptr;

      for (int y = 0, index = 0; y < yres; y++) {
        for (int x = 0; x < xres; x++, index++) {
          dest_data[index] = src_data[((lmi_ptr->y1 + y) * lmw) + lmi_ptr->x1 + x];
        }
      }

      dest_data = src_data;
      lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;

      // Mark it as changed
      lmi_ptr->dynamic = dynamic_handle;

      if (!(GameLightmaps[lm_handle].flags & LF_LIMITS)) {
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
      } else {
        if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
          GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
        if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
          GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

        if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
          GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
        if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
          GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
      }

      GameLightmaps[lm_handle].flags |= (LF_LIMITS | LF_CHANGED);

      Dynamic_face_list[Num_dynamic_faces].lmi_handle = fp->lmi_handle;
      Num_dynamic_faces++;

      lmilist[num_spoken_for] = fp->lmi_handle;
      Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
      num_spoken_for++;

      // Setup edge blending
      Edges_to_blend[Num_edges_to_blend++] = fp->lmi_handle;
    }

    vector element_vec;

    base_vector -= (start_y * (facematrix.uvec * lmi_ptr->yspacing));
    base_vector += (start_x * (facematrix.rvec * lmi_ptr->xspacing));

    base_vector -= ((facematrix.uvec / 2) * lmi_ptr->yspacing);
    base_vector += ((facematrix.rvec / 2) * lmi_ptr->xspacing);

    // Go through and change each element of this lightmap
    // SLOW!

    int texel_num = ((start_y + lmi_ptr->y1) * lmw) + start_x + lmi_ptr->x1;
    for (int y = 0; y < height; y++, base_vector -= (facematrix.uvec * lmi_ptr->yspacing), texel_num += lmw) {
      element_vec = base_vector;

      for (int x = 0; x < width; x++, element_vec += (facematrix.rvec * lmi_ptr->xspacing)) {
        int lightmap_texel_num = texel_num + x;

        uint16_t lightmap_texel = dest_data[lightmap_texel_num];

        if (!(lightmap_texel & OPAQUE_FLAG))
          continue;

        float dist = vm_VectorDistanceQuick(&element_vec, pos);
        float scalar = 1.0 - (dist / light_dist);

        if (light_direction) {
          vector lsubvec = element_vec - *pos;
          vm_NormalizeVectorFast(&lsubvec);
          float dp = vm_DotProduct(&lsubvec, light_direction);
          if (dp < dot_range) {
            continue;
          } else {

            float add_scale = (dp - dot_range) / (1.0 - dot_range);
            scalar *= add_scale;
          }
        }

        if (scalar <= 0)
          continue;

        int r = (lightmap_texel >> 10) & 0x1f;
        int g = (lightmap_texel >> 5) & 0x1f;
        int b = lightmap_texel & 0x1f;

        if (red_scale < 0) {
          // we are subtracting light
          r = std::max<float>(0, r + (scalar * red_scale * 31));
        } else {
          if (r < red_limit)
            r = std::min<float>(red_limit, r + (scalar * red_scale * 31));
        }

        if (green_scale < 0) {
          // we are subtracting light
          g = std::max<float>(0, g + (scalar * green_scale * 31));
        } else {
          if (g < green_limit)
            g = std::min<float>(green_limit, g + (scalar * green_scale * 31));
        }

        if (blue_scale < 0) {
          // we are subtracting light
          b = std::max<float>(0, b + (scalar * blue_scale * 31));
        } else {
          if (b < blue_limit)
            b = std::min<float>(blue_limit, b + (scalar * blue_scale * 31));
        }

        lightmap_texel = OPAQUE_FLAG | (r << 10) | (g << 5) | b;

        dest_data[lightmap_texel_num] = lightmap_texel;
      }
    }
  }

  for (i = 0; i < num_spoken_for; i++) {
    int index = lmilist[i];
    Lmi_spoken_for[index / 8] = 0;
  }
}

struct light_instance_context {
  vector p;
  vector dir;
} Light_instance_stack[MAX_SUBOBJECTS];

int Light_instance_depth = 0;
uint8_t Use_light_direction = 0;

vector Light_position;
vector Light_direction;

// instance at specified point with specified orientation
void StartLightingInstance(vector *pos, matrix *orient) {
  vector tempv;

  ASSERT(Light_instance_depth < MAX_SUBOBJECTS);

  Light_instance_stack[Light_instance_depth].p = Light_position;
  if (Use_light_direction)
    Light_instance_stack[Light_instance_depth].dir = Light_direction;
  Light_instance_depth++;

  // Step 1: subtract position from light position
  tempv = Light_position - *pos;
  // step 2: rotate view vector through object matrix

  Light_position = tempv * *orient;

  // Rotate the light direction through this matrix
  if (Use_light_direction) {
    tempv = Light_direction;
    Light_direction = tempv * *orient;
  }
}

// pops the old context
void DoneLightingInstance() {
  Light_instance_depth--;

  ASSERT(Light_instance_depth >= 0);

  Light_position = Light_instance_stack[Light_instance_depth].p;
  if (Use_light_direction)
    Light_direction = Light_instance_stack[Light_instance_depth].dir;
}

// Applies lighting to a submodel and all its children
void ApplyLightingToSubmodel(object *obj, poly_model *pm, bsp_info *sm, float light_dist, float red_scale,
                             float green_scale, float blue_scale, float dot_range) {
  matrix mat;
  vector Light_min_xyz;
  vector Light_max_xyz;
  vector rad;
  int i, t;
  int subnum = sm - pm->submodel;
  int lm_handle;
  uint16_t *dest_data;
  uint16_t lmilist[MAX_DYNAMIC_FACES];
  int num_spoken_for = 0;

  int red_limit = 31;
  int green_limit = 31;
  int blue_limit = 31;

  if (IsNonRenderableSubmodel(pm, subnum))
    return; // Don't do shells, frontfaces, etc

  // Start instance stuff
  vector temp_vec = sm->mod_pos + sm->offset;
  vm_AnglesToMatrix(&mat, sm->angs.p, sm->angs.h, sm->angs.b);
  StartLightingInstance(&temp_vec, &mat);

  rad.x = light_dist;
  rad.y = light_dist;
  rad.z = light_dist;

  vector light_pos = Light_position;
  vector light_dir = Light_direction;

  Light_min_xyz = light_pos - rad;
  Light_max_xyz = light_pos + rad;

  // Now the Light_position is in the submodels frame of reference
  for (i = 0; i < sm->num_faces; i++) {
    // check to see if this face is within reach
    if (Light_max_xyz.y < sm->face_min[i].y || sm->face_max[i].y < Light_min_xyz.y ||
        Light_max_xyz.x < sm->face_min[i].x || sm->face_max[i].x < Light_min_xyz.x ||
        Light_max_xyz.z < sm->face_min[i].z || sm->face_max[i].z < Light_min_xyz.z)
      continue;

    // Ok, now we know that this light touches this face
    if (Num_dynamic_faces >= MAX_DYNAMIC_FACES) {
      mprintf(0, "Too many dynamic faces!\n");
      DoneLightingInstance();
      return;
    }

    lightmap_object_face *fp = &obj->lm_object.lightmap_faces[subnum][i];

    if (Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))
      continue;

    int xres = lmi_w(fp->lmi_handle);
    int yres = lmi_h(fp->lmi_handle);

    lightmap_info *lmi_ptr = &LightmapInfo[fp->lmi_handle];
    // Lightmap width and height
    int lmw = lm_w(lmi_ptr->lm_handle);

    // Check for backfaces
    // Get upper left vector of face
    vector base_vector = lmi_ptr->upper_left;
    vector subvec = light_pos - lmi_ptr->upper_left;
    float dist_from_plane = fabs(vm_DotProduct(&subvec, &lmi_ptr->normal));

    if (dist_from_plane > light_dist)
      continue;

    if (Use_light_direction) {
      // If this is a directional light, check for backfaces
      vector norm_vec = light_pos - base_vector;

      if ((norm_vec * lmi_ptr->normal) < 0) {
        // Backface, skip this face
        continue;
      }

      // Test to see if all vertices are behind the light object, if so then bail
      polyface *poly_fp = &sm->faces[i];
      int in_front = 0; //
      for (t = 0; t < fp->num_verts && in_front == 0; t++) {
        norm_vec = sm->verts[poly_fp->vertnums[t]] - light_pos;
        if (norm_vec * light_dir > 0)
          in_front = 1;
      }

      if (!in_front) // This face is completely behind, so bail!
        continue;
    }

    // Compute face matrix
    matrix facematrix;
    vector fvec = -lmi_ptr->normal;
    vm_VectorToMatrix(&facematrix, &fvec, NULL, NULL);

    // Get the area of effect for this light
    float area_of_effect = (1.0 - (dist_from_plane / light_dist)) * light_dist;
    vector touch_vector = light_pos - (lmi_ptr->normal * dist_from_plane);

    subvec = touch_vector - base_vector;
    float rdist = vm_DotProduct(&subvec, &facematrix.rvec);
    float udist = -vm_DotProduct(&subvec, &facematrix.uvec);
    int x_add = 1 + ((area_of_effect + (lmi_ptr->xspacing / 2)) / lmi_ptr->xspacing);
    int y_add = 1 + ((area_of_effect + (lmi_ptr->yspacing / 2)) / lmi_ptr->yspacing);

    // Get the rectangle of the lightmap that we want to light
    int start_x = (rdist / lmi_ptr->xspacing) - x_add;
    int start_y = (udist / lmi_ptr->yspacing) - y_add;
    int end_x = (rdist / lmi_ptr->xspacing) + x_add + .5;
    int end_y = (udist / lmi_ptr->yspacing) + y_add + .5;

    if (end_x < 0 || end_y < 0 || start_x >= (xres) || start_y >= (yres))
      continue;

    if (start_x < 0)
      start_x = 0;
    if (start_y < 0)
      start_y = 0;
    if (end_x > xres)
      end_x = xres;
    if (end_y > yres)
      end_y = yres;

    int width = end_x - start_x;
    int height = end_y - start_y;

    if (width == 0)
      width++;
    if (height == 0)
      height++;

    ASSERT(width > 0);
    ASSERT(height > 0);

    if (lmi_ptr->dynamic != BAD_LM_INDEX) // already lit, so just adjust, not start over
    {
      lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
      dest_data = (uint16_t *)lm_data(lm_handle);

      if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
      if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

      if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
      if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;

      GameLightmaps[lm_handle].flags |= (LF_CHANGED | LF_LIMITS);

      if (!(Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))) {
        lmilist[num_spoken_for] = fp->lmi_handle;
        Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
        num_spoken_for++;
      }
    } else // Start a new dynamic lightmap
    {
      // First find a suitable dynamic lightmap to work with
      int dynamic_handle = GetFreeDynamicLightmap(xres, yres);

      if (dynamic_handle < 0) {
        mprintf(0, "No free dynamic maps!\n");
        DoneLightingInstance();

        return; // None free!
      }

      // Now copy our source data to our dest data so we have a base to work with
      uint16_t *src_data;

      src_data = (uint16_t *)lm_data(LightmapInfo[fp->lmi_handle].lm_handle);
      dest_data = Dynamic_lightmaps[dynamic_handle].mem_ptr;

      for (int y = 0, index = 0; y < yres; y++) {
        for (int x = 0; x < xres; x++, index++) {
          dest_data[index] = src_data[((lmi_ptr->y1 + y) * lmw) + lmi_ptr->x1 + x];
        }
      }

      dest_data = src_data;
      lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;

      // Mark it as changed
      lmi_ptr->dynamic = dynamic_handle;

      if (!(GameLightmaps[lm_handle].flags & LF_LIMITS)) {
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
      } else {
        if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
          GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
        if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
          GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

        if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
          GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
        if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
          GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
      }

      GameLightmaps[lm_handle].flags |= (LF_LIMITS | LF_CHANGED);

      Dynamic_face_list[Num_dynamic_faces].lmi_handle = fp->lmi_handle;
      Num_dynamic_faces++;

      lmilist[num_spoken_for] = fp->lmi_handle;
      Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
      num_spoken_for++;

      // Setup edge blending
      Edges_to_blend[Num_edges_to_blend++] = fp->lmi_handle;
    }

    vector element_vec;

    base_vector -= (start_y * (facematrix.uvec * lmi_ptr->yspacing));
    base_vector += (start_x * (facematrix.rvec * lmi_ptr->xspacing));

    base_vector -= ((facematrix.uvec / 2) * lmi_ptr->yspacing);
    base_vector += ((facematrix.rvec / 2) * lmi_ptr->xspacing);

    // Go through and change each element of this lightmap
    // SLOW!

    int texel_num = ((start_y + lmi_ptr->y1) * lmw) + start_x + lmi_ptr->x1;
    for (int y = 0; y < height; y++, base_vector -= (facematrix.uvec * lmi_ptr->yspacing), texel_num += lmw) {
      element_vec = base_vector;

      for (int x = 0; x < width; x++, element_vec += (facematrix.rvec * lmi_ptr->xspacing)) {
        int lightmap_texel_num = texel_num + x;

        uint16_t lightmap_texel = dest_data[lightmap_texel_num];

        if (!(lightmap_texel & OPAQUE_FLAG))
          continue;

        float dist = vm_VectorDistanceQuick(&element_vec, &light_pos);
        float scalar = 1.0 - (dist / light_dist);

        if (Use_light_direction) {
          vector lsubvec = element_vec - light_pos;
          vm_NormalizeVectorFast(&lsubvec);
          float dp = vm_DotProduct(&lsubvec, &light_dir);
          if (dp < dot_range) {
            continue;
          } else {

            float add_scale = (dp - dot_range) / (1.0 - dot_range);
            scalar *= add_scale;
          }
        }

        if (scalar <= 0)
          continue;

        int r = (lightmap_texel >> 10) & 0x1f;
        int g = (lightmap_texel >> 5) & 0x1f;
        int b = lightmap_texel & 0x1f;

        if (red_scale < 0) {
          r = std::max<float>(0, r + (scalar * red_scale * 31));
        } else {
          if (r < red_limit)
            r = std::min<float>(red_limit, r + (scalar * red_scale * 31));
        }

        if (green_scale < 0) {
          g = std::max<float>(0, g + (scalar * green_scale * 31));
        } else {
          if (g < green_limit)
            g = std::min<float>(green_limit, g + (scalar * green_scale * 31));
        }

        if (blue_scale < 0) {
          b = std::max<float>(0, b + (scalar * blue_scale * 31));
        } else {
          if (b < blue_limit)
            b = std::min<float>(blue_limit, b + (scalar * blue_scale * 31));
        }

        lightmap_texel = OPAQUE_FLAG | (r << 10) | (g << 5) | b;

        dest_data[lightmap_texel_num] = lightmap_texel;
      }
    }
  }

  for (i = 0; i < num_spoken_for; i++) {
    int index = lmilist[i];
    Lmi_spoken_for[index / 8] = 0;
  }

  for (i = 0; i < sm->num_children; i++)
    ApplyLightingToSubmodel(obj, pm, &pm->submodel[sm->children[i]], light_dist, red_scale, green_scale, blue_scale,
                            dot_range);

  DoneLightingInstance();
}
/*
// Test to see if this wall should show specular lighting from this light source
void ApplySpecularLightingToWall (room *rp,face *fp,vector *pos,float light_dist,float dist_from_plane,float
red_scale,float green_scale,float blue_scale)
{
        special_face *sf=&SpecialFaces[fp->special_handle];

        if (!(sf->flags))
        {
                // Reset this face
                Specular_face_list[Num_specular_faces++]=fp->special_handle;
                sf->flags=1;
                sf->strength=0;
        }

        float norm=std::min(1.0,(light_dist/dist_from_plane)*2.0);
        float strength=((red_scale*.33)+(green_scale*.33)+(blue_scale*.33))*light_dist;

        if (strength>sf->strength)
        {
                sf->strength=strength;
                sf->lightdist=light_dist;
                sf->lightpos=*pos;
                sf->color=GR_RGB16(norm*red_scale*255,norm*green_scale*255,norm*blue_scale*255);
        }

}*/

// Applys dynamic volumetric lighting to an object
void ApplyVolumeLightToObject(vector *pos, object *obj, float light_dist, float red_scale, float green_scale,
                              float blue_scale, vector *light_direction, float dot_range) {
  vector subvec = *pos - obj->pos;
  float mag = vm_GetMagnitudeFast(&subvec);

  float scalar = mag / light_dist;
  if (scalar > 1)
    scalar = 1;

  scalar = 1 - scalar;

  if (light_direction) {
    // Do a directional light
    vector dir_vec = obj->pos - *pos;
    float mag = vm_NormalizeVectorFast(&dir_vec);
    float dp = dir_vec * *light_direction;

    if (mag > 1.0) {
      if (dp < dot_range)
        return;
      else {
        float add_scale = (dp - dot_range) / (1.0 - dot_range);
        scalar *= add_scale;
      }
    }
  }

  ASSERT(obj->effect_info != NULL);

  if (!obj->effect_info->dynamic_this_frame) {
    if (Num_volume_objects < MAX_VOLUME_OBJECTS) {
      Dynamic_volume_object_list[Num_volume_objects].handle = obj->handle;
      Dynamic_volume_object_list[Num_volume_objects++].objnum = OBJNUM(obj);
      obj->effect_info->spec_mag = -100000;

      obj->effect_info->dynamic_this_frame = 1;
    }
  }

  // See if this specular light source is greater than our current one
  if ((light_dist - mag) > obj->effect_info->spec_mag && Detail_settings.Specular_lighting &&
      !(Object_info[obj->id].lighting_info.flags & OLF_NO_SPECULARITY)) {
    // mprintf(0,"Setting specular!\n");
    obj->effect_info->type_flags |= EF_SPECULAR;
    obj->effect_info->spec_mag = light_dist - mag;
    obj->effect_info->spec_pos = *pos;
    obj->effect_info->spec_r = red_scale;
    obj->effect_info->spec_g = green_scale;
    obj->effect_info->spec_b = blue_scale;
  }

  if (obj->effect_info->type_flags & EF_VOLUME_LIT) {
    obj->effect_info->dynamic_red = std::min<float>(1, obj->effect_info->dynamic_red + (scalar * red_scale));
    obj->effect_info->dynamic_green = std::min<float>(1, obj->effect_info->dynamic_green + (scalar * green_scale));
    obj->effect_info->dynamic_blue = std::min<float>(1, obj->effect_info->dynamic_blue + (scalar * blue_scale));
  }
}

// Applies lighting to all objects in a certain distance
void ApplyLightingToObjects(vector *pos, int roomnum, float light_dist, float red_scale, float green_scale,
                            float blue_scale, vector *light_direction, float dot_range) {
  int16_t objlist[MAX_DYNAMIC_FACES];
  int num_objects, i;
  float normalized_time[MAX_SUBOBJECTS];

  num_objects = fvi_QuickDistObjectList(pos, roomnum, light_dist, objlist, MAX_DYNAMIC_FACES, false, false, true);

  for (i = 0; i < num_objects; i++) {
    object *obj = &Objects[objlist[i]];

    if (obj->type == OBJ_ROOM) {
      ApplyLightingToExternalRoom(pos, obj->id, light_dist, red_scale, green_scale, blue_scale, light_direction,
                                  dot_range);
      continue;
    }

    if (obj->renderframe != ((FrameCount - 1) % 65536)) {
      if (obj != Viewer_object)
        continue;
    }

    if (obj->lm_object.used == 0) {
      if (obj->effect_info && ((obj->effect_info->type_flags & EF_VOLUME_LIT) ||
                               obj->lighting_render_type == LRT_GOURAUD || obj->type == OBJ_POWERUP)) {
        ApplyVolumeLightToObject(pos, obj, light_dist, red_scale, green_scale, blue_scale, light_direction, dot_range);
        continue;
      } else
        continue;
    }

    int model_num = obj->rtype.pobj_info.model_num;
    poly_model *pm = &Poly_models[model_num];

    // Set our light position
    Light_position = *pos;

    // Set up light direction if this is a directional light
    if (light_direction) {
      Light_direction = *light_direction;
      Use_light_direction = 1;
    } else
      Use_light_direction = 0;

    StartLightingInstance(&obj->pos, &obj->orient);

    // Now, get the lights position in the objects submodel space
    SetNormalizedTimeObj(obj, normalized_time);
    SetModelAnglesAndPos(pm, normalized_time);

    for (int t = 0; t < pm->n_models; t++) {
      bsp_info *sm = &pm->submodel[t];
      if (sm->parent == -1)
        ApplyLightingToSubmodel(obj, pm, sm, light_dist, red_scale, green_scale, blue_scale, dot_range);
    }

    DoneLightingInstance();
    ASSERT(Light_instance_depth == 0);
  }
}

// Applys dynamic lightmap changes to rooms and room objects.  If light direction is non-null, we are applying a
// directional light
void ApplyLightingToRooms(vector *pos, int roomnum, float light_dist, float red_scale, float green_scale,
                          float blue_scale, vector *light_direction, float dot_range) {
  fvi_face_room_list facelist[MAX_DYNAMIC_FACES];
  uint16_t lmilist[MAX_DYNAMIC_FACES];
  int num_spoken_for = 0;

  int num_faces, i, t, lm_handle;
  uint16_t *dest_data;
  int faces_misreported = 0;

  if (Dedicated_server)
    return;

  ApplyLightingToObjects(pos, roomnum, light_dist, red_scale, green_scale, blue_scale, light_direction, dot_range);

  num_faces = fvi_QuickDistFaceList(roomnum, pos, light_dist, facelist, MAX_DYNAMIC_FACES);

#ifdef _DEBUG
  if (num_faces == MAX_DYNAMIC_FACES) {
    mprintf(0, "Dynamic light from 1 object is touching %d faces! dist=%f\n", MAX_DYNAMIC_FACES, light_dist);
  }
#endif

  if (num_faces < 1)
    return;

  int red_limit = 31;
  int green_limit = 31;
  int blue_limit = 31;

  for (i = 0; i < num_faces; i++) {
    room *rp = &Rooms[facelist[i].room_index];
    face *fp = &rp->faces[facelist[i].face_index];

    ASSERT(Rooms[facelist[i].room_index].used);
    ASSERT(facelist[i].face_index < Rooms[facelist[i].room_index].num_faces);

    // Make sure face was rendered
    if (fp->renderframe != ((FrameCount - 1) % 256))
      continue;

    if (Num_dynamic_faces >= MAX_DYNAMIC_FACES) {
      mprintf(0, "Too many dynamic faces!\n");
      return;
    }

    // Make sure there already is a lightmap for this face
    if (!(fp->flags & FF_LIGHTMAP))
      continue;

    if (Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))
      continue;

    int xres = lmi_w(fp->lmi_handle);
    int yres = lmi_h(fp->lmi_handle);

    lightmap_info *lmi_ptr = &LightmapInfo[fp->lmi_handle];
    // Lightmap width and height
    int lmw = lm_w(lmi_ptr->lm_handle);

    // Check for backfaces
    vector subvec = *pos - lmi_ptr->upper_left;
    float dist_from_plane = fabs(vm_DotProduct(&subvec, &lmi_ptr->normal));

    if (dist_from_plane > light_dist)
      continue;

    if (light_direction) {
      // If this is a directional light, check for backfaces
      vector norm_vec = *pos - rp->verts[fp->face_verts[0]];

      if ((norm_vec * lmi_ptr->normal) < 0) {
        // Backface, skip this light
        continue;
      }
      // Test to see if all vertices are behind the light object, if so then bail
      int in_front = 0; //
      for (t = 0; t < fp->num_verts && in_front == 0; t++) {
        norm_vec = rp->verts[fp->face_verts[t]] - *pos;
        if (norm_vec * *light_direction > 0)
          in_front = 1;
      }

      if (!in_front) // This face is completely behind, so bail!
        continue;
    }

    /*// Check for specular lighting changes on this face
    if (Detail_settings.Specular_lighting && fp->special_handle!=BAD_SPECIAL_FACE_INDEX)
    {
            ApplySpecularLightingToWall(rp,fp,pos,light_dist,dist_from_plane,red_scale,green_scale,blue_scale);
    }*/

    // Compute face matrix
    matrix facematrix;
    vector fvec = -lmi_ptr->normal;
    vm_VectorToMatrix(&facematrix, &fvec, NULL, NULL);

    // Get upper left vector of face
    vector base_vector = lmi_ptr->upper_left;

    // Get the area of effect for this light
    float area_of_effect = (1.0 - (dist_from_plane / light_dist)) * light_dist;
    vector touch_vector = *pos - (lmi_ptr->normal * dist_from_plane);

    subvec = touch_vector - base_vector;
    float rdist = vm_DotProduct(&subvec, &facematrix.rvec);
    float udist = -vm_DotProduct(&subvec, &facematrix.uvec);
    int x_add = 1 + ((area_of_effect + (lmi_ptr->xspacing / 2)) / lmi_ptr->xspacing);
    int y_add = 1 + ((area_of_effect + (lmi_ptr->yspacing / 2)) / lmi_ptr->yspacing);

    // Get the rectangle of the lightmap that we want to light
    int start_x = (rdist / lmi_ptr->xspacing) - x_add;
    int start_y = (udist / lmi_ptr->yspacing) - y_add;
    int end_x = (rdist / lmi_ptr->xspacing) + x_add + .5;
    int end_y = (udist / lmi_ptr->yspacing) + y_add + .5;

    if (end_x < 0 || end_y < 0 || start_x >= (xres) || start_y >= (yres))
      continue;

    if (start_x < 0)
      start_x = 0;
    if (start_y < 0)
      start_y = 0;
    if (end_x > xres)
      end_x = xres;
    if (end_y > yres)
      end_y = yres;

    int width = end_x - start_x;
    int height = end_y - start_y;

    if (width == 0)
      width++;
    if (height == 0)
      height++;

    ASSERT(width > 0);
    ASSERT(height > 0);

    if (lmi_ptr->dynamic != BAD_LM_INDEX) // already lit, so just adjust, not start over
    {
      lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
      dest_data = (uint16_t *)lm_data(lm_handle);

      if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
      if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

      if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
      if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;

      GameLightmaps[lm_handle].flags |= (LF_CHANGED | LF_LIMITS);

      if (!(Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))) {
        lmilist[num_spoken_for] = fp->lmi_handle;
        Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
        num_spoken_for++;
      }
    } else // Start a new dynamic lightmap
    {
      // First find a suitable dynamic lightmap to work with
      int dynamic_handle = GetFreeDynamicLightmap(xres, yres);

      if (dynamic_handle < 0) {
        mprintf(0, "No free dynamic maps!\n");
        return; // None free!
      }

      // Now copy our source data to our dest data so we have a base to work with
      uint16_t *src_data;

      src_data = (uint16_t *)lm_data(LightmapInfo[fp->lmi_handle].lm_handle);
      dest_data = Dynamic_lightmaps[dynamic_handle].mem_ptr;

      for (int y = 0, index = 0; y < yres; y++) {
        for (int x = 0; x < xres; x++, index++) {
          dest_data[index] = src_data[((lmi_ptr->y1 + y) * lmw) + lmi_ptr->x1 + x];
        }
      }

      dest_data = src_data;
      lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;

      // Mark it as changed
      lmi_ptr->dynamic = dynamic_handle;

      if (!(GameLightmaps[lm_handle].flags & LF_LIMITS)) {
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
      } else {
        if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
          GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
        if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
          GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

        if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
          GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
        if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
          GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
      }

      GameLightmaps[lm_handle].flags |= (LF_LIMITS | LF_CHANGED);

      Dynamic_face_list[Num_dynamic_faces].lmi_handle = fp->lmi_handle;
      Num_dynamic_faces++;

      lmilist[num_spoken_for] = fp->lmi_handle;
      Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
      num_spoken_for++;

      // Setup edge blending
      Edges_to_blend[Num_edges_to_blend++] = fp->lmi_handle;
    }

    vector element_vec;

    base_vector -= (start_y * (facematrix.uvec * lmi_ptr->yspacing));
    base_vector += (start_x * (facematrix.rvec * lmi_ptr->xspacing));

    base_vector -= ((facematrix.uvec / 2) * lmi_ptr->yspacing);
    base_vector += ((facematrix.rvec / 2) * lmi_ptr->xspacing);

    // Go through and change each element of this lightmap
    // SLOW!

    int texel_num = ((start_y + lmi_ptr->y1) * lmw) + start_x + lmi_ptr->x1;
    for (int y = 0; y < height; y++, base_vector -= (facematrix.uvec * lmi_ptr->yspacing), texel_num += lmw) {
      element_vec = base_vector;

      for (int x = 0; x < width; x++, element_vec += (facematrix.rvec * lmi_ptr->xspacing)) {
        int lightmap_texel_num = texel_num + x;

        uint16_t lightmap_texel = dest_data[lightmap_texel_num];

        if (!(lightmap_texel & OPAQUE_FLAG))
          continue;

        float dist = vm_VectorDistanceQuick(&element_vec, pos);
        float scalar = 1.0 - (dist / light_dist);

        if (light_direction) {
          vector lsubvec = element_vec - *pos;
          vm_NormalizeVectorFast(&lsubvec);
          float dp = vm_DotProduct(&lsubvec, light_direction);
          if (dp < dot_range) {
            continue;
          } else {

            float add_scale = (dp - dot_range) / (1.0 - dot_range);
            scalar *= add_scale;
          }
        }

        if (scalar <= 0)
          continue;

        int r = (lightmap_texel >> 10) & 0x1f;
        int g = (lightmap_texel >> 5) & 0x1f;
        int b = lightmap_texel & 0x1f;

        if (red_scale < 0) {
          // we are subtracting light
          r = std::max<float>(0, r + (scalar * red_scale * 31));
        } else {
          // we are adding light
          if (r < red_limit)
            r = std::min<float>(red_limit, r + (scalar * red_scale * 31));
        }

        if (green_scale < 0) {
          // we are subtracting light
          g = std::max<float>(0, g + (scalar * green_scale * 31));
        } else {
          // we are adding light
          if (g < green_limit)
            g = std::min<float>(green_limit, g + (scalar * green_scale * 31));
        }

        if (blue_scale < 0) {
          // we are subtracting light
          b = std::max<float>(0, b + (scalar * blue_scale * 31));
        } else {
          if (b < blue_limit)
            b = std::min<float>(blue_limit, b + (scalar * blue_scale * 31));
        }

        lightmap_texel = OPAQUE_FLAG | (r << 10) | (g << 5) | b;

        dest_data[lightmap_texel_num] = lightmap_texel;
      }
    }
  }

  for (i = 0; i < num_spoken_for; i++) {
    int index = lmilist[i];
    Lmi_spoken_for[index / 8] = 0;
  }
}

// Blends all the edges that need blending for this frame
void BlendAllLightingEdges() {
  for (int i = 0; i < Num_edges_to_blend; i++) {
    if (LightmapInfo[Edges_to_blend[i]].used < 1)
      continue; // this face was killed last frame.  This can happen with objects
    BlendLightingEdges(&LightmapInfo[Edges_to_blend[i]]);
  }
}

// Clears the used flag for the dynamic lightmaps and restores colors on the terrain
void ClearDynamicLightmaps() {
  int i;

  // First clear dynamic lightmap list
  for (i = 0; i < Num_dynamic_lightmaps; i++)
    Dynamic_lightmaps[i].used = 0;

  // Reset volume lights
  for (i = 0; i < Num_volume_objects; i++) {
    object *obj = &Objects[Dynamic_volume_object_list[i].objnum];
    if (obj->type == OBJ_NONE || obj->handle != Dynamic_volume_object_list[i].handle)
      continue; // object was destroyed this frame

    obj->effect_info->type_flags &= ~EF_SPECULAR;
    obj->effect_info->dynamic_this_frame = 0;
    obj->effect_info->dynamic_red = 0;
    obj->effect_info->dynamic_green = 0;
    obj->effect_info->dynamic_blue = 0;
  }

  Num_volume_objects = 0;

  // Reset specular faces
  for (i = 0; i < Num_specular_faces; i++) {
    int n = Specular_face_list[i];
    SpecialFaces[n].flags = 0;
    // LightmapInfo[n].spec_map=-1;
  }

  Num_specular_faces = 0;

  // Clear diffuse faces
  for (i = 0; i < Num_dynamic_faces; i++) {
    if (LightmapInfo[Dynamic_face_list[i].lmi_handle].used == 0)
      continue; // this face was killed last frame.  This can happen with objects

    int dynamic_handle = LightmapInfo[Dynamic_face_list[i].lmi_handle].dynamic;
    int lmi_handle = Dynamic_face_list[i].lmi_handle;
    int lm_handle = LightmapInfo[lmi_handle].lm_handle;
    lightmap_info *lmi_ptr = &LightmapInfo[lmi_handle];

    uint16_t *src_data = Dynamic_lightmaps[dynamic_handle].mem_ptr;
    uint16_t *dest_data = (uint16_t *)lm_data(lm_handle);

    int lmw = lm_w(lm_handle);

    dest_data += (lmi_ptr->y1 * lmw);

    for (int y = 0; y < lmi_ptr->height; y++, dest_data += lmw) {
      for (int x = 0; x < lmi_ptr->width; x++) {
        dest_data[lmi_ptr->x1 + x] = src_data[y * lmi_ptr->width + x];
      }
    }

    GameLightmaps[lm_handle].flags |= (LF_LIMITS | LF_CHANGED);
    LightmapInfo[lmi_handle].dynamic = BAD_LMI_INDEX;
  }

  Num_dynamic_faces = 0;

  // Now do terrain

  for (i = 0; i < Num_dynamic_cells; i++) {
    int cellnum = Dynamic_cell_list[i].cellnum;
    Terrain_seg[cellnum].flags &= ~TF_DYNAMIC;
    Terrain_seg[cellnum].r = Dynamic_cell_list[i].r;
    Terrain_seg[cellnum].g = Dynamic_cell_list[i].g;
    Terrain_seg[cellnum].b = Dynamic_cell_list[i].b;

    int seg_x = cellnum % TERRAIN_WIDTH;
    int seg_z = cellnum / TERRAIN_WIDTH;

    int subx = seg_x % 128;
    int subz = 127 - (seg_z % 128);

    int whichmap = ((seg_z / 128) * 2) + (seg_x / 128);
    whichmap = TerrainLightmaps[whichmap];

    uint16_t color = OPAQUE_FLAG | GR_RGB16(Terrain_seg[cellnum].r, Terrain_seg[cellnum].g, Terrain_seg[cellnum].b);
    uint16_t *data = lm_data(whichmap);

    data[subz * 128 + subx] = color;

    GameLightmaps[whichmap].flags |= (LF_LIMITS | LF_CHANGED);
  }

  Num_dynamic_cells = 0;

  Num_dynamic_lightmaps = 0;
  Cur_dynamic_mem_ptr = 0;

  BlendAllLightingEdges();
  Num_edges_to_blend = 0;
}

// Changes the terrain shading to approximate lighting
void ApplyLightingToTerrain(vector *pos, int cellnum, float light_dist, float red_scale, float green_scale,
                            float blue_scale, vector *light_direction, float dot_range) {
  int celllist[MAX_DYNAMIC_CELLS];
  int num_cells, i;

  if (Dedicated_server)
    return;

  ApplyLightingToObjects(pos, MAKE_ROOMNUM(cellnum), light_dist, red_scale, green_scale, blue_scale, light_direction,
                         dot_range);

  num_cells = fvi_QuickDistCellList(cellnum, pos, light_dist, celllist, MAX_DYNAMIC_CELLS);

  if (num_cells < 1)
    return;

  if (num_cells == MAX_DYNAMIC_CELLS) {
    mprintf(0, "One object has hit %d terrain cells in lighting!\n", MAX_DYNAMIC_CELLS);
  }

  int red_limit = 255;
  int green_limit = 255;
  int blue_limit = 255;

  for (i = 0; i < num_cells; i++) {
    int cellnum = celllist[i];
    terrain_segment *tseg = &Terrain_seg[cellnum];

    int seg_x = cellnum % TERRAIN_WIDTH;
    int seg_z = cellnum / TERRAIN_WIDTH;

    int subx = seg_x % 128;
    int subz = 127 - (seg_z % 128);

    int whichmap = ((seg_z / 128) * 2) + (seg_x / 128);
    whichmap = TerrainLightmaps[whichmap];

    // Make sure face was rendered
    // if (tseg->renderframe!=((FrameCount-1)%256))
    //	continue;

    if (Num_dynamic_cells >= MAX_DYNAMIC_CELLS) {
      mprintf(0, "Too many dynamic cells!\n");
      return;
    }

    // Check for backfaces
    vector tpos;

    tpos.x = (seg_x * TERRAIN_SIZE) + (TERRAIN_SIZE / 2);
    tpos.z = (seg_z * TERRAIN_SIZE) + (TERRAIN_SIZE / 2);
    tpos.y = tseg->y;

    vector subvec = *pos - tpos;

    float dist = vm_GetMagnitudeFast(&subvec);
    float scalar = 1.0 - (dist / light_dist);

    if (light_direction) {
      vector lsubvec = -subvec;
      lsubvec /= dist;
      float dp = vm_DotProduct(&lsubvec, light_direction);
      if (dp < dot_range) {
        continue;
      } else {
        float add_scale = (dp - dot_range) / (1.0 - dot_range);
        scalar *= add_scale;
      }
    }

    if (scalar <= 0)
      continue;

    // Add a new face to our list
    if (!(tseg->flags & TF_DYNAMIC)) {
      Dynamic_cell_list[Num_dynamic_cells].cellnum = cellnum;
      Dynamic_cell_list[Num_dynamic_cells].r = tseg->r;
      Dynamic_cell_list[Num_dynamic_cells].g = tseg->g;
      Dynamic_cell_list[Num_dynamic_cells].b = tseg->b;
      tseg->flags |= TF_DYNAMIC;
      Num_dynamic_cells++;

      if (GameLightmaps[whichmap].flags & LF_LIMITS) {
        if (subx < GameLightmaps[whichmap].cx1)
          GameLightmaps[whichmap].cx1 = subx;
        if (subx > GameLightmaps[whichmap].cx2)
          GameLightmaps[whichmap].cx2 = subx;

        if (subz < GameLightmaps[whichmap].cy1)
          GameLightmaps[whichmap].cy1 = subz;
        if (subz > GameLightmaps[whichmap].cy2)
          GameLightmaps[whichmap].cy2 = subz;

      } else {
        GameLightmaps[whichmap].cx1 = subx;
        GameLightmaps[whichmap].cx2 = subx + 1;
        GameLightmaps[whichmap].cy1 = subz;
        GameLightmaps[whichmap].cy2 = subz + 1;
        GameLightmaps[whichmap].flags |= (LF_LIMITS | LF_CHANGED);
      }
    }

    int r = tseg->r;
    int g = tseg->g;
    int b = tseg->b;

    if (red_scale < 0) {
      // we are subtracting light
      tseg->r = std::max<float>(0, r + (scalar * red_scale * 255));
    } else {
      if (r < red_limit)
        tseg->r = std::min<float>(red_limit, r + (scalar * red_scale * 255));
    }

    if (green_scale < 0) {
      // we are subtracting light
      tseg->g = std::max<float>(0, g + (scalar * green_scale * 255));
    } else {
      if (g < green_limit)
        tseg->g = std::min<float>(green_limit, g + (scalar * green_scale * 255));
    }

    if (blue_scale < 0) {
      // we are subtracting light
      tseg->b = std::max<float>(0, b + (scalar * blue_scale * 255));
    } else {
      if (b < blue_limit)
        tseg->b = std::min<float>(blue_limit, b + (scalar * blue_scale * 255));
    }

    uint16_t color = OPAQUE_FLAG | GR_RGB16(tseg->r, tseg->g, tseg->b);
    uint16_t *data = lm_data(whichmap);

    ASSERT(data);

    data[subz * 128 + subx] = color;
  }
}

// TODO: MTS: Unused?
// Sets pulse parameters for an entire room
void SetRoomPulse(room *rp, uint8_t pulse_time, uint8_t pulse_offset) {
  ASSERT(rp->used);

  rp->pulse_time = pulse_time;
  rp->pulse_offset = pulse_offset;
}

// TODO: MTS: Unused?
// Returns the total number of bytes needed for volume lighting in this room
int GetVolumeSizeOfRoom(room *rp, int *w, int *h, int *d) {
  int width = ((rp->max_xyz.x - rp->min_xyz.x) / VOLUME_SPACING) + 1;
  int height = ((rp->max_xyz.y - rp->min_xyz.y) / VOLUME_SPACING) + 1;
  int depth = ((rp->max_xyz.z - rp->min_xyz.z) / VOLUME_SPACING) + 1;

  if (w)
    *w = width;
  if (h)
    *h = height;
  if (d)
    *d = depth;

  return (width * height * depth);
}

/*
// Returns a lightmap that can be applied for specular lighting
int GetSpecularLightmapForFace (vector *pos,room *rp,face *fp)
{
        int xres=lmi_w(fp->lmi_handle);
        int yres=lmi_h(fp->lmi_handle);
        lightmap_info *lmi_ptr=&LightmapInfo[fp->lmi_handle];

        matrix facematrix;
        vector fvec=-lmi_ptr->normal;
        vm_VectorToMatrix(&facematrix,&fvec,NULL,NULL);

        // Get upper left vector of face
        vector base_vector=lmi_ptr->upper_left;

        int square_res=GameLightmaps[lmi_ptr->lm_handle].square_res;

        //if (square_res>=128)
                //return -1;

        //square_res*=2;
        //xres*=2;
        //yres*=2;
        float xspacing=(float)lmi_ptr->xspacing;
        float yspacing=(float)lmi_ptr->yspacing;

        int cl=GetLightmapClass (square_res);
        int lm_handle;

        uint16_t *dest_data;
        uint16_t *src_data=(uint16_t *)lm_data(lmi_ptr->lm_handle);

        if (lmi_ptr->spec_map==-1)
        {
                // Get a new specular map and clear it
                int dynamic_handle=FindFreeDynamicLightmap (cl);

                if (dynamic_handle<0)
                {
                        mprintf(0,"No free specular maps for class %d!\n",cl);
                        return-1;		// None free!
                }

                Dynamic_lightmaps[cl][dynamic_handle].used=1;
                int dynamic_lmi_handle=Dynamic_lightmaps[cl][dynamic_handle].lmi_handle;
                lm_handle=LightmapInfo[dynamic_lmi_handle].lm_handle;

                lmi_ptr->spec_map=lm_handle;
                dest_data=(uint16_t *)lm_data(lm_handle);

                memset (dest_data,0,xres*yres*2);

                Specular_face_list[Num_specular_faces]=fp->lmi_handle;
                Num_specular_faces++;
        }
        else
        {
                return 1;// already done for this face
        }

        GameLightmaps[lm_handle].flags|=LF_CHANGED;

        vector element_vec;

        // Choose material
        int material_type=0;

        if (GameTextures[fp->tmap].flags & TF_PLASTIC)
                material_type=1;
        else if (GameTextures[fp->tmap].flags & TF_MARBLE)
                material_type=2;

        // Go through and change each element of this lightmap
        // SLOW!

        int texel_num=0;

        int num=SpecialFaces[fp->special_handle].num;

        for (int y=0;y<yres;y++,base_vector-=(facematrix.uvec*yspacing),texel_num+=xres)
        {
                element_vec=base_vector;

                for (int x=0;x<xres;x++,element_vec+=(facematrix.rvec*xspacing))
                {
                        int lightmap_texel_num=texel_num+x;

                        uint16_t lightmap_texel=src_data[lightmap_texel_num];

                        if (! (lightmap_texel & OPAQUE_FLAG))
                                continue;

                        float rscale,gscale,bscale;

                        rscale=Light_component_scalar [(lightmap_texel>>10 & 0x1f)];
                        gscale=Light_component_scalar [(lightmap_texel>>5 & 0x1f)];
                        bscale=Light_component_scalar [(lightmap_texel & 0x1f)];

                        for (int i=0;i<num;i++)
                        {
                                if (SpecialFaces[fp->special_handle].spec_instance[i].bright_color==0)
                                        continue;

                                lightmap_texel=dest_data[lightmap_texel_num];

                                int old_r=lightmap_texel>>10 & 0x1f;
                                int old_g=lightmap_texel>>5 & 0x1f;
                                int old_b=lightmap_texel & 0x1f;

                                vector subvec=*pos-element_vec;
                                vm_NormalizeVectorFast (&subvec);

                                vector
incident_norm=element_vec-SpecialFaces[fp->special_handle].spec_instance[i].bright_center; vm_NormalizeVectorFast
(&incident_norm);

                                float d=incident_norm * fp->normal;
                                vector upvec=d * fp->normal;
                                incident_norm-=(2*upvec);

                                float dotp=subvec * incident_norm;

                                if (dotp<0)
                                        continue;
                                if (dotp>1)
                                        dotp=1;

                                if (dotp>0)
                                {
                                        int index=((float)(MAX_SPECULAR_INCREMENTS-1)*dotp);
                                        float val=Specular_tables[material_type][index];

                                        uint16_t color=SpecialFaces[fp->special_handle].spec_instance[i].bright_color;
                                        int r=color >> 10 & 0x1f;
                                        int g=color >> 5 & 0x1f;
                                        int b=color & 0x1f;

                                        r*=val*rscale;
                                        g*=val*gscale;
                                        b*=val*bscale;

                                        r=std::min(31,old_r+r);
                                        g=std::min(31,old_g+g);
                                        b=std::min(31,old_b+b);


                                        dest_data[lightmap_texel_num]=OPAQUE_FLAG|(r<<10)|(g<<5)|(b);
                                }
                        }
                }
        }

        return lm_handle;
}*/

/*
// Returns a lightmap that can be applied for specular lighting
int GetSpecularLightmapForFace (vector *pos,room *rp,face *fp)
{

        int xres=lmi_w(fp->lmi_handle);
        int yres=lmi_h(fp->lmi_handle);
        lightmap_info *lmi_ptr=&LightmapInfo[fp->lmi_handle];
        vector center=SpecialFaces[fp->special_handle].center;

        matrix facematrix;
        vector fvec=-lmi_ptr->normal;
        vm_VectorToMatrix(&facematrix,&fvec,NULL,NULL);

        // Get upper left vector of face
        vector base_vector=lmi_ptr->upper_left;

        int start_x=fp->x1;
        int start_y=fp->y1;
        int end_x=fp->x1+fp->lw;
        int end_y=fp->y1+fp->lh;

        int width=end_x-start_x;
        int height=end_y-start_y;

        if (width==0)
                width++;
        if (height==0)
                height++;

        ASSERT (width>0);
        ASSERT (height>0);

        int square_res=GameLightmaps[lmi_ptr->lm_handle].square_res;
        int cl=GetLightmapClass (square_res);
        int lm_handle;

        uint16_t *dest_data;
        uint16_t *src_data=(uint16_t *)lm_data(lmi_ptr->lm_handle);

        if (lmi_ptr->spec_map==-1)
        {
                // Get a new specular map and clear it
                int dynamic_handle=FindFreeDynamicLightmap (cl);

                if (dynamic_handle<0)
                {
                        mprintf(0,"No free specular maps for class %d!\n",cl);
                        return-1;		// None free!
                }

                Dynamic_lightmaps[cl][dynamic_handle].used=1;
                int dynamic_lmi_handle=Dynamic_lightmaps[cl][dynamic_handle].lmi_handle;
                lm_handle=LightmapInfo[dynamic_lmi_handle].lm_handle;

                lmi_ptr->spec_map=lm_handle;
                dest_data=(uint16_t *)lm_data(lm_handle);

                memset (dest_data,0,xres*yres*2);

                Specular_face_list[Num_specular_faces]=fp->lmi_handle;
                Num_specular_faces++;
        }
        else
        {
                lm_handle=lmi_ptr->spec_map;
                dest_data=(uint16_t *)lm_data(lm_handle);
        }


        GameLightmaps[lm_handle].flags|=LF_CHANGED;

        // Rotate the base_vector, the eyepoint, face normal and the lightsource into the Z plane
        vector tempvec,eye_pos,light_pos[4];
        vector norm;

        base_vector-=center;

        vm_MatrixMulVector (&tempvec,&base_vector,&facematrix);
        base_vector=tempvec;

        tempvec=*pos-center;
        vm_MatrixMulVector (&eye_pos,&tempvec,&facematrix);

        for (int i=0;i<4;i++)
        {
                if (SpecialFaces[fp->special_handle].spec_instance[i].bright_color!=0)
                {
                        tempvec=SpecialFaces[fp->special_handle].spec_instance[i].bright_center-center;
                        vm_MatrixMulVector (&light_pos[i],&tempvec,&facematrix);
                }
        }

        vm_MatrixMulVector (&norm,&fp->normal,&facematrix);

        // Move to offset
        vector element_vec;

        base_vector.y-=(start_y*lmi_ptr->yspacing);
        base_vector.x+=(start_x*lmi_ptr->xspacing);

        // Move to center of texel
        base_vector.y-=(lmi_ptr->yspacing/2);
        base_vector.x+=(lmi_ptr->xspacing/2);

        // Choose material
        int material_type=0;

        if (GameTextures[fp->tmap].flags & TF_PLASTIC)
                material_type=1;
        else if (GameTextures[fp->tmap].flags & TF_MARBLE)
                material_type=2;

        // Go through and change each element of this lightmap
        // SLOW!

        int texel_num=start_y*xres+start_x;
        int num=SpecialFaces[fp->special_handle].num;

        for (int y=0;y<height;y++,base_vector.y-=lmi_ptr->yspacing,texel_num+=xres)
        {
                element_vec=base_vector;

                for (int x=0;x<width;x++,element_vec.x+=lmi_ptr->xspacing)
                {
                        int lightmap_texel_num=texel_num+x;

                        if (SpecialFaces[fp->special_handle].normal_map[lightmap_texel_num*3+2]==128)
                                continue;
                        else
                        {
                                norm.x=Normal_table[SpecialFaces[fp->special_handle].normal_map[lightmap_texel_num*3+0]];
                                norm.y=Normal_table[SpecialFaces[fp->special_handle].normal_map[lightmap_texel_num*3+1]];
                                norm.z=Normal_table[SpecialFaces[fp->special_handle].normal_map[lightmap_texel_num*3+2]];
                        }

                        uint16_t lightmap_texel=src_data[lightmap_texel_num];

                        if (! (lightmap_texel & OPAQUE_FLAG))
                                continue;

                        float base_r=(lightmap_texel>>10 & 0x1f)>15?1:0;
                        float base_g=(lightmap_texel>>5 & 0x1f)>15?1:0;
                        float base_b=(lightmap_texel & 0x1f)>15?1:0;


                        for (int i=0;i<num;i++)
                        {
                                if (SpecialFaces[fp->special_handle].spec_instance[i].bright_color==0)
                                        continue;

                                lightmap_texel=dest_data[lightmap_texel_num];

                                int old_r=lightmap_texel>>10 & 0x1f;
                                int old_g=lightmap_texel>>5 & 0x1f;
                                int old_b=lightmap_texel & 0x1f;

                                vector subvec=eye_pos-element_vec;
                                vm_NormalizeVectorFast (&subvec);

                                vector incident_norm=element_vec-light_pos[i];
                                vm_NormalizeVectorFast (&incident_norm);

                                float d=incident_norm * norm;
                                vector upvec=d * norm;
                                incident_norm-=(2*upvec);

                                float dotp=subvec * incident_norm;

//				if (rp-Rooms==0 && fp-rp->faces==5 && (x==width/2) && (y==height/2))
//					mprintf(0,"dotp=%f\n",dotp);


                                if (dotp<0)
                                        continue;
                                if (dotp>1)
                                        dotp=1;

                                if (dotp>0)
                                {
                                        int index=((float)(MAX_SPECULAR_INCREMENTS-1)*dotp);
                                        float val=Specular_tables[material_type][index];

                                        uint16_t color=SpecialFaces[fp->special_handle].spec_instance[i].bright_color;
                                        int r=color >> 10 & 0x1f;
                                        int g=color >> 5 & 0x1f;
                                        int b=color & 0x1f;

                                        r*=val*base_r;
                                        g*=val*base_g;
                                        b*=val*base_b;

                                        r=std::min(31,old_r+r);
                                        g=std::min(31,old_g+g);
                                        b=std::min(31,old_b+b);


                                        dest_data[lightmap_texel_num]=OPAQUE_FLAG|(r<<10)|(g<<5)|(b);
                                }
                        }
                }
        }

        return lm_handle;
}*/

#define DESTROYABLE_IGNORE_LIMIT .2f

// Kills the lighting that a face casts and dampens all the faces that light influences
void DestroyLight(int roomnum, int facenum) {
  vector vecs[MAX_VERTS_PER_FACE], center;
  room *destroy_rp = &Rooms[roomnum];
  face *destroy_fp = &destroy_rp->faces[facenum];
  float r, g, b;
  fvi_face_room_list facelist[MAX_DYNAMIC_FACES];
  int num_faces, i;
  uint16_t lmilist[MAX_DYNAMIC_FACES];
  int num_spoken_for = 0;

  if (Dedicated_server)
    return;

  float mul = ((float)destroy_fp->light_multiple) / 4.0;

  r = GameTextures[destroy_fp->tmap].r * mul;
  g = GameTextures[destroy_fp->tmap].g * mul;
  b = GameTextures[destroy_fp->tmap].b * mul;

  // Get highest component
  float rmax = std::max({r, g, b});

  // Get the normalized color that this face emits
  float red_scale = r / rmax;
  float green_scale = g / rmax;
  float blue_scale = b / rmax;

  // red_scale/=30;
  // green_scale/=30;
  // blue_scale/=30;

  mprintf(0, "r=%f g=%f b=%f\n", red_scale, green_scale, blue_scale);

  // Get center and area of light face
  for (i = 0; i < destroy_fp->num_verts; i++)
    vecs[i] = destroy_rp->verts[destroy_fp->face_verts[i]];

  float area = vm_GetCentroid(&center, vecs, destroy_fp->num_verts);

  // Get the sphere of influence of this light
  float power = rmax * area;
  float temp_ignore = DESTROYABLE_IGNORE_LIMIT / power;
  float express = 1.0 / temp_ignore;
  express /= 3.14f;
  express -= area;
  float sphere_dist = sqrt(express);

  //	ApplyLightingToObjects (pos,roomnum,light_dist,red_scale,green_scale,blue_scale,light_direction,dot_range);

  num_faces = fvi_QuickDistFaceList(roomnum, &center, sphere_dist, facelist, MAX_DYNAMIC_FACES);

  for (i = 0; i < num_faces; i++) {
    room *rp = &Rooms[facelist[i].room_index];
    face *fp = &rp->faces[facelist[i].face_index];

    ASSERT(Rooms[facelist[i].room_index].used);
    ASSERT(facelist[i].face_index < Rooms[facelist[i].room_index].num_faces);

    // Make sure there already is a lightmap for this face
    if (!(fp->flags & FF_LIGHTMAP))
      continue;

    if (GameTextures[fp->tmap].flags & TF_LIGHT)
      continue;

    if (Lmi_spoken_for[fp->lmi_handle / 8] & (1 << (fp->lmi_handle % 8)))
      continue;

    int xres = lmi_w(fp->lmi_handle);
    int yres = lmi_h(fp->lmi_handle);

    lightmap_info *lmi_ptr = &LightmapInfo[fp->lmi_handle];

    int lmw = lm_w(lmi_ptr->lm_handle);

    vector subvec = center - lmi_ptr->upper_left;
    float dist_from_plane = vm_DotProduct(&subvec, &lmi_ptr->normal);

    // Check for backfaces
    if (dist_from_plane < 0)
      continue;

    dist_from_plane = fabs(dist_from_plane);

    if (dist_from_plane > sphere_dist)
      continue;

    // Compute face matrix
    matrix facematrix;
    vector fvec = -lmi_ptr->normal;
    vm_VectorToMatrix(&facematrix, &fvec, NULL, NULL);

    // Get upper left vector of face
    vector base_vector = lmi_ptr->upper_left;

    // Get the area of effect for this light
    float area_of_effect = (1.0 - (dist_from_plane / sphere_dist)) * sphere_dist;
    vector touch_vector = center - (lmi_ptr->normal * dist_from_plane);

    subvec = touch_vector - base_vector;
    float rdist = vm_DotProduct(&subvec, &facematrix.rvec);
    float udist = -vm_DotProduct(&subvec, &facematrix.uvec);
    int x_add = 1 + ((area_of_effect + (lmi_ptr->xspacing / 2)) / lmi_ptr->xspacing);
    int y_add = 1 + ((area_of_effect + (lmi_ptr->yspacing / 2)) / lmi_ptr->yspacing);

    // Get the rectangle of the lightmap that we want to light
    int start_x = (rdist / lmi_ptr->xspacing) - x_add;
    int start_y = (udist / lmi_ptr->yspacing) - y_add;
    int end_x = (rdist / lmi_ptr->xspacing) + x_add + .5;
    int end_y = (udist / lmi_ptr->yspacing) + y_add + .5;

    if (end_x < 0 || end_y < 0 || start_x >= (xres) || start_y >= (yres))
      continue;

    if (start_x < 0)
      start_x = 0;
    if (start_y < 0)
      start_y = 0;
    if (end_x > xres)
      end_x = xres;
    if (end_y > yres)
      end_y = yres;

    end_x++;
    end_y++;

    if (end_x > xres)
      end_x = xres;
    if (end_y > yres)
      end_y = yres;

    int width = end_x - start_x;
    int height = end_y - start_y;

    if (width == 0)
      width++;
    if (height == 0)
      height++;

    ASSERT(width > 0);
    ASSERT(height > 0);

    // Now copy our source data to our dest data so we have a base to work with
    uint16_t *dest_data;

    dest_data = (uint16_t *)lm_data(LightmapInfo[fp->lmi_handle].lm_handle);
    int lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;

    if (!(GameLightmaps[lm_handle].flags & LF_LIMITS)) {
      GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
      GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;
      GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
      GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
    } else {
      if (start_x + lmi_ptr->x1 < GameLightmaps[lm_handle].cx1)
        GameLightmaps[lm_handle].cx1 = start_x + lmi_ptr->x1;
      if (start_x + lmi_ptr->x1 + width > GameLightmaps[lm_handle].cx2)
        GameLightmaps[lm_handle].cx2 = start_x + width + lmi_ptr->x1;

      if (start_y + lmi_ptr->y1 < GameLightmaps[lm_handle].cy1)
        GameLightmaps[lm_handle].cy1 = start_y + lmi_ptr->y1;
      if (lmi_ptr->y1 + start_y + height > GameLightmaps[lm_handle].cy2)
        GameLightmaps[lm_handle].cy2 = start_y + height + lmi_ptr->y1;
    }

    GameLightmaps[lm_handle].flags |= (LF_LIMITS | LF_CHANGED);

    lmilist[num_spoken_for] = fp->lmi_handle;
    Lmi_spoken_for[fp->lmi_handle / 8] |= (1 << (fp->lmi_handle % 8));
    num_spoken_for++;

    vector element_vec;

    base_vector -= (start_y * (facematrix.uvec * lmi_ptr->yspacing));
    base_vector += (start_x * (facematrix.rvec * lmi_ptr->xspacing));

    base_vector -= ((facematrix.uvec / 2) * lmi_ptr->yspacing);
    base_vector += ((facematrix.rvec / 2) * lmi_ptr->xspacing);

    // Go through and change each element of this lightmap
    // SLOW!

    int texel_num = ((start_y + lmi_ptr->y1) * lmw) + start_x + lmi_ptr->x1;
    for (int y = 0; y < height; y++, base_vector -= (facematrix.uvec * lmi_ptr->yspacing), texel_num += lmw) {
      element_vec = base_vector;

      for (int x = 0; x < width; x++, element_vec += (facematrix.rvec * lmi_ptr->xspacing)) {
        int lightmap_texel_num = texel_num + x;

        uint16_t lightmap_texel = dest_data[lightmap_texel_num];

        if (!(lightmap_texel & OPAQUE_FLAG))
          continue;

        float dist = vm_VectorDistanceQuick(&element_vec, &center);
        float scalar = 1.0 - (dist / sphere_dist);

        if (scalar <= 0)
          continue;

        int r = (lightmap_texel >> 10) & 0x1f;
        int g = (lightmap_texel >> 5) & 0x1f;
        int b = lightmap_texel & 0x1f;

        if (r > 0)
          r = std::max<float>(0, r - (scalar * red_scale * 31));

        if (g > 0)
          g = std::max<float>(0, g - (scalar * green_scale * 31));

        if (b > 0)
          b = std::max<float>(0, b - (scalar * blue_scale * 31));

        lightmap_texel = OPAQUE_FLAG | (r << 10) | (g << 5) | b;

        dest_data[lightmap_texel_num] = lightmap_texel;
      }
    }

    BlendLightingEdges(lmi_ptr);
  }

  for (i = 0; i < num_spoken_for; i++) {
    int index = lmilist[i];
    Lmi_spoken_for[index / 8] = 0;
  }
}

// TODO: MTS: unused?
// Adds to our list of destroyable lights that got destroyed this frame
void AddToDestroyableLightList(int roomnum, int facenum) {
  if (Num_destroyed_lights_this_frame >= MAX_DESTROYED_LIGHTS_PER_FRAME) {
    mprintf(0, "Ran out of destroyable light slots!\n");
    return;
  }

  mprintf(0, "Destroying light.  Room=%d face=%d\n", roomnum, facenum);

  Destroyed_light_rooms_this_frame[Num_destroyed_lights_this_frame] = roomnum;
  Destroyed_light_faces_this_frame[Num_destroyed_lights_this_frame++] = facenum;
}

// Goes through our destroyable light list and actually kills all the lights
void DoDestroyedLightsForFrame() {
  int i;
  for (i = 0; i < Num_destroyed_lights_this_frame; i++) {
    int roomnum = Destroyed_light_rooms_this_frame[i];
    int facenum = Destroyed_light_faces_this_frame[i];
    DestroyLight(roomnum, facenum);
  }

  Num_destroyed_lights_this_frame = 0;
}
