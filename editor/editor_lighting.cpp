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

 * $Logfile: /DescentIII/Main/editor/editor_lighting.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 * $NoKeywords: $
 */

#include <algorithm>
#include <windows.h>
#include "3d.h"
#include "texture.h"
#include "gametexture.h"
#include "erooms.h"
#include "editor_lighting.h"
#include "descent.h"
#include "room.h"
#include "lightmap.h"
#include "polymodel.h"
#include <string.h>
#include <stdlib.h>
#include "terrain.h"
#include "radiosity.h"
#include "lighting.h"
#include "findintersection.h"
#include "lightmap_info.h"
#include "object_lighting.h"
#include "d3edit.h"
#include "ddio.h"
#include "bsp.h"
#include "winapp.h"
#include "windatabase.h"
#include "program.h"
#include "loadlevel.h"
#include "special_face.h"
#include "boa.h"
#include "mem.h"

struct spec_vertex {
  float x, y;
};

int AllowCombining = 1;
float GlobalMultiplier = 1.0;

rad_surface *Light_surfaces = NULL;

vector ScratchCenters[MAX_LIGHTMAP_INFOS];
vector ScratchRVecs[MAX_LIGHTMAP_INFOS];
vector ScratchUVecs[MAX_LIGHTMAP_INFOS];

float Room_multiplier[MAX_ROOMS + MAX_PALETTE_ROOMS];
float Room_ambience_r[MAX_ROOMS + MAX_PALETTE_ROOMS], Room_ambience_g[MAX_ROOMS + MAX_PALETTE_ROOMS],
    Room_ambience_b[MAX_ROOMS + MAX_PALETTE_ROOMS];

uint8_t *TerrainLightSpeedup[MAX_SATELLITES];

int LightSpacing = LIGHTMAP_SPACING;
int BestFit = 0;
int Square_surfaces = 0;
int Lightmaps_for_rad = 0;

// Ambient values for terrain
float Ambient_red = 0.0f, Ambient_green = 0.0f, Ambient_blue = 0.0f;

void DoTerrainDynamicTable();

uint8_t *Lightmap_mask = NULL;
static uint8_t *Lmi_spoken_for;
int Squeeze_lightmap_handle = -1;

int FindEmptyMaskSpot(int w, int h, int *dest_x, int *dest_y) {
  int cur_x = 0, cur_y = 0;
  int i, t;

  for (cur_y = 0; cur_y < 128; cur_y++) {
    if (cur_y + h > 128)
      return 0;
    for (cur_x = 0; cur_x < 128; cur_x++) {
      if (cur_x + w > 128)
        continue;

      int hit_mask = 0;
      for (i = 0; i < h && !hit_mask; i++) {
        for (t = 0; t < w && !hit_mask; t++) {
          if (Lightmap_mask[((cur_y + i) * 128) + cur_x + t])
            hit_mask = 1;
        }
      }
      if (hit_mask == 0) {
        // Hurray! We found an empty spot
        *dest_x = cur_x;
        *dest_y = cur_y;
        return 1;
      }
    }
  }

  return 0;
}

void CopySqueezeBodyAndEdges(uint16_t *dest_data, uint16_t *src_data, int w, int h, int dest_x, int dest_y) {
  int i, t;

  ASSERT(w + dest_x <= 126);
  ASSERT(h + dest_y <= 126);
  ASSERT(dest_x >= 0 && dest_y >= 0);

  // First copy the main body
  for (i = 0; i < h; i++) {
    for (t = 0; t < w; t++) {
      dest_data[((dest_y + 1 + i) * 128) + (dest_x + 1 + t)] = src_data[(w * i) + t];
      Lightmap_mask[((dest_y + i + 1) * 128) + dest_x + 1 + t] = 1;
    }
  }

  // Now copy the edges
  // Left edge
  for (i = 0; i < h; i++) {
    dest_data[((dest_y + 1 + i) * 128) + (dest_x + 0)] = src_data[(w * i) + 0];
    Lightmap_mask[((dest_y + i + 1) * 128) + dest_x + 0] = 1;
  }
  // Right edge
  for (i = 0; i < h; i++) {
    dest_data[((dest_y + 1 + i) * 128) + (dest_x + w + 1)] = src_data[(w * i) + (w - 1)];
    Lightmap_mask[((dest_y + i + 1) * 128) + dest_x + w + 1] = 1;
  }
  // Top edge
  for (i = 0; i < w; i++) {
    dest_data[(dest_y * 128) + (dest_x + i + 1)] = src_data[i];
    Lightmap_mask[(dest_y * 128) + (dest_x + i + 1)] = 1;
  }
  // Bottom edge
  for (i = 0; i < w; i++) {
    dest_data[((dest_y + 1 + h) * 128) + (dest_x + i + 1)] = src_data[(w * (h - 1)) + i];
    Lightmap_mask[((dest_y + 1 + h) * 128) + (dest_x + i + 1)] = 1;
  }

  // Now copy the corners
  // Upper left
  dest_data[(dest_y * 128) + (dest_x)] = src_data[0];
  Lightmap_mask[(dest_y * 128) + (dest_x)] = 1;
  // Upper right
  dest_data[(dest_y * 128) + (dest_x + w + 1)] = src_data[w - 1];
  Lightmap_mask[(dest_y * 128) + (dest_x + w + 1)] = 1;
  // Lower left
  dest_data[((dest_y + h + 1) * 128) + (dest_x)] = src_data[w * (h - 1)];
  Lightmap_mask[((dest_y + h + 1) * 128) + (dest_x)] = 1;
  // Lower right
  dest_data[((dest_y + h + 1) * 128) + (dest_x + w + 1)] = src_data[(w * (h - 1)) + (w - 1)];
  Lightmap_mask[((dest_y + h + 1) * 128) + (dest_x + w + 1)] = 1;
}

void CopySqueezeDataForRooms(int roomnum, int facenum, uint16_t *dest_data, int dest_x, int dest_y) {
  room *rp = &Rooms[roomnum];
  lightmap_info *lmi_ptr = &LightmapInfo[rp->faces[facenum].lmi_handle];
  uint16_t *src_data = (uint16_t *)lm_data(lmi_ptr->lm_handle);

  int w = lmi_ptr->width;
  int h = lmi_ptr->height;

  // Copy over the actual lightmap data
  CopySqueezeBodyAndEdges(dest_data, src_data, w, h, dest_x, dest_y);

  // Now alter all face uvs that have this lightmap info
  float dest_u = (float)(dest_x + 1) / 128.0;
  float dest_v = (float)(dest_y + 1) / 128.0;

  float u_scalar = (float)w / 128.0;
  float v_scalar = (float)h / 128.0;

  for (int t = roomnum; t <= Highest_room_index; t++) {
    room *this_rp = &Rooms[t];
    if (!this_rp->used)
      continue;

    for (int j = 0; j < this_rp->num_faces; j++) {

      if (!(this_rp->faces[j].flags & FF_LIGHTMAP))
        continue;

      if (this_rp->faces[j].lmi_handle == BAD_LMI_INDEX)
        continue;

      if (Lmi_spoken_for[this_rp->faces[j].lmi_handle])
        continue;
      if (this_rp->faces[j].lmi_handle == rp->faces[facenum].lmi_handle) {
        lmi_ptr->x1 = dest_x + 1;
        lmi_ptr->y1 = dest_y + 1;

        // We have to alter our uvs for this face to reflect our change
        face *fp = &this_rp->faces[j];
        for (int k = 0; k < fp->num_verts; k++) {
          fp->face_uvls[k].u2 *= u_scalar;
          fp->face_uvls[k].u2 += dest_u;

          fp->face_uvls[k].v2 *= v_scalar;
          fp->face_uvls[k].v2 += dest_v;
        }
      }
    }
  }

  ASSERT(rp->faces[facenum].lmi_handle != BAD_LMI_INDEX);

  Lmi_spoken_for[rp->faces[facenum].lmi_handle] = 1;

  // Free our old lightmap
  GameLightmaps[lmi_ptr->lm_handle].used = 1;
  lm_FreeLightmap(lmi_ptr->lm_handle);

  lmi_ptr->lm_handle = Squeeze_lightmap_handle;
  GameLightmaps[Squeeze_lightmap_handle].used++;
}

void CopySqueezeDataForObject(object *obj, int subnum, int facenum, uint16_t *dest_data, int dest_x, int dest_y) {
  lightmap_object_face *fp = &obj->lm_object.lightmap_faces[subnum][facenum];
  lightmap_info *lmi_ptr = &LightmapInfo[fp->lmi_handle];
  uint16_t *src_data = (uint16_t *)lm_data(lmi_ptr->lm_handle);
  int t, k;

  int w = lmi_ptr->width;
  int h = lmi_ptr->height;

  // Copy over the actual lightmap data
  CopySqueezeBodyAndEdges(dest_data, src_data, w, h, dest_x, dest_y);

  // Now alter all face uvs that have this lightmap info
  float dest_u = (float)(dest_x + 1) / 128.0;
  float dest_v = (float)(dest_y + 1) / 128.0;

  float u_scalar = (float)w / 128.0;
  float v_scalar = (float)h / 128.0;

  for (int objnum = obj - Objects; objnum != -1; objnum = Objects[objnum].next) {
    object *this_obj = &Objects[objnum];

    if (this_obj->lighting_render_type != LRT_LIGHTMAPS)
      continue;
    if (!this_obj->lm_object.used)
      continue;

    for (t = 0; t < this_obj->lm_object.num_models; t++) {
      if (IsNonRenderableSubmodel(&Poly_models[this_obj->rtype.pobj_info.model_num], t))
        continue;

      for (k = 0; k < this_obj->lm_object.num_faces[t]; k++) {
        lightmap_object_face *this_fp = &this_obj->lm_object.lightmap_faces[t][k];
        int lmi_handle = this_fp->lmi_handle;
        if (lmi_handle == BAD_LMI_INDEX)
          continue;
        if (Lmi_spoken_for[lmi_handle])
          continue;

        if (lmi_handle == fp->lmi_handle) {
          lmi_ptr->x1 = dest_x + 1;
          lmi_ptr->y1 = dest_y + 1;

          // We have to alter our uvs for this face to reflect our change
          for (int j = 0; j < this_fp->num_verts; j++) {
            this_fp->u2[j] *= u_scalar;
            this_fp->u2[j] += dest_u;

            this_fp->v2[j] *= v_scalar;
            this_fp->v2[j] += dest_v;
          }
        }
      }
    }
  }

  ASSERT(fp->lmi_handle != BAD_LMI_INDEX);
  Lmi_spoken_for[fp->lmi_handle] = 1;

  // Free our old lightmap
  GameLightmaps[lmi_ptr->lm_handle].used = 1;
  lm_FreeLightmap(lmi_ptr->lm_handle);

  lmi_ptr->lm_handle = Squeeze_lightmap_handle;
  GameLightmaps[Squeeze_lightmap_handle].used++;
}

// Simply clears flags for combine portals
void ClearCombinePortals(int terrain) {
  for (int i = 0; i <= Highest_room_index; i++) {
    room *rp = &Rooms[i];

    if (!rp->used)
      continue;

    if (terrain && !(rp->flags & RF_EXTERNAL))
      continue;

    if (!terrain && (rp->flags & RF_EXTERNAL))
      continue;

    for (int t = 0; t < rp->num_portals; t++) {
      portal *portal_a = &rp->portals[t];
      portal_a->flags &= ~PF_COMBINED;
    }
  }
}

// For rendering...combines all portals if they are on the same plane
void CheckCombinePortals(int terrain) {
  ClearCombinePortals(terrain);

  int combine_count = 0;
  mprintf(0, "Combining portals...");

  for (int i = 0; i <= Highest_room_index; i++) {
    room *rp = &Rooms[i];

    if (!rp->used)
      continue;

    if (terrain && !(rp->flags & RF_EXTERNAL))
      continue;

    if (!terrain && (rp->flags & RF_EXTERNAL))
      continue;

    for (int t = 0; t < rp->num_portals; t++) {
      portal *portal_a = &rp->portals[t];
      face *face_a = &rp->faces[portal_a->portal_face];

      if (portal_a->flags & PF_COMBINED)
        continue;

      // Don't combine if face is breakable
      if (GameTextures[face_a->tmap].flags & TF_BREAKABLE)
        continue;

      float dist_a = vm_DotProduct(&rp->verts[face_a->face_verts[0]], &face_a->normal);

      for (int k = 0; k < rp->num_portals; k++) {
        portal *portal_b = &rp->portals[k];
        face *face_b = &rp->faces[portal_b->portal_face];

        if (portal_b->flags & PF_COMBINED)
          continue;

        // Don't combine if one portal is render-faces and the other is not
        if ((portal_a->flags & PF_RENDER_FACES) != (portal_b->flags & PF_RENDER_FACES))
          continue;

        // Don't combine if face is breakable
        if (GameTextures[face_b->tmap].flags & TF_BREAKABLE)
          continue;

        if (t == k)
          continue;

        // Check to see if the portals connect to the same room
        if (portal_a->croom != portal_b->croom)
          continue;

        /*// Check to see if they share a normal
        float dp=vm_DotProduct (&face_a->normal,&face_b->normal);

        if (dp < .95f)
                continue;


        // Check to see if the distances are same
        float dist_b=vm_DotProduct (&rp->verts[face_b->face_verts[0]],&face_b->normal);

        if (fabs(dist_b-dist_a)>.5)
                continue;

        int match=0;
        // Test to see if any points at all can touch
        for (int x=0; x<face_a->num_verts && !match; x++ )
        {
                for (int y=0; y<face_b->num_verts && !match; y++ )
                {
                        if (PointsAreSame(&rp->verts[face_a->face_verts[x]],&rp->verts[face_b->face_verts[y]]))
                                match=1;
                }
        }

        if (match==0)
                continue;

        //Check to see if the portals connect to the same room
        if (portal_a->croom != portal_b->croom)
                continue;

        // Hurray! These portals can be combined*/
        portal_a->flags |= PF_COMBINED;
        portal_b->flags |= PF_COMBINED;

        portal_a->combine_master = t;
        portal_b->combine_master = t;
        combine_count++;
      }
    }
  }

  mprintf(0, "%d portals combined.\n", combine_count);
}

// Squeezes all the lightmaps down into as few 128x128s as possible
void SqueezeLightmaps(int external, int target_roomnum) {
  int i, t, k;
  mprintf(0, "Squeezing %s lightmaps, please wait...\n", external ? "external" : "internal");

  Lmi_spoken_for = (uint8_t *)mem_malloc(MAX_LIGHTMAP_INFOS);
  Lightmap_mask = (uint8_t *)mem_malloc(128 * 128);
  Squeeze_lightmap_handle = -1;

  ASSERT(Lightmap_mask);
  ASSERT(Lmi_spoken_for);
  memset(Lmi_spoken_for, 0, MAX_LIGHTMAP_INFOS);
  memset(Lightmap_mask, 0, 128 * 128);

  // Go through all the rooms and sqeeze them one by one
  for (i = 0; i <= Highest_room_index; i++) {
    room *rp = &Rooms[i];
    if (!rp->used)
      continue;
    if (rp->flags & RF_NO_LIGHT)
      continue;

    if (external) {
      if (!(rp->flags & RF_EXTERNAL))
        continue;
    } else {
      if ((rp->flags & RF_EXTERNAL))
        continue;

      if (target_roomnum != -1 && target_roomnum != i)
        continue;
    }

    // Go through each face
    for (t = 0; t < rp->num_faces; t++) {
      face *fp = &rp->faces[t];
      int lmi_handle = fp->lmi_handle;

      if (!(fp->flags & FF_LIGHTMAP))
        continue;

      if (lmi_handle == BAD_LMI_INDEX)
        continue;
      if (Lmi_spoken_for[lmi_handle])
        continue;

      lightmap_info *lmi = &LightmapInfo[lmi_handle];

      int dest_x, dest_y;
      int src_w = lmi->width;
      int src_h = lmi->height;

      if (Squeeze_lightmap_handle == -1) {
        memset(Lightmap_mask, 0, 128 * 128);
        Squeeze_lightmap_handle = lm_AllocLightmap(128, 128);
        uint16_t *fill_data = (uint16_t *)lm_data(Squeeze_lightmap_handle);
        memset(fill_data, 0, 128 * 128 * 2);
      }

      if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
        // Cool, found a spot
        CopySqueezeDataForRooms(i, t, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
      } else {
        // Can't find an empty slot, so search through all the other remaining faces
        for (k = t; k < rp->num_faces; k++) {
          face *fp = &rp->faces[k];
          int lmi_handle = fp->lmi_handle;

          if (!(fp->flags & FF_LIGHTMAP))
            continue;
          if (lmi_handle == BAD_LMI_INDEX)
            continue;
          if (Lmi_spoken_for[lmi_handle])
            continue;

          lightmap_info *lmi = &LightmapInfo[lmi_handle];

          int src_w = lmi->width;
          int src_h = lmi->height;

          if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
            CopySqueezeDataForRooms(i, k, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
          }
        }

        // Now, allocate a new lightmap and start over
        ASSERT(Squeeze_lightmap_handle != -1);
        ASSERT(GameLightmaps[Squeeze_lightmap_handle].used != 1);
        GameLightmaps[Squeeze_lightmap_handle].used--;

        memset(Lightmap_mask, 0, 128 * 128);
        Squeeze_lightmap_handle = lm_AllocLightmap(128, 128);
        uint16_t *fill_data = (uint16_t *)lm_data(Squeeze_lightmap_handle);
        memset(fill_data, 0, 128 * 128 * 2);

        ASSERT(Lmi_spoken_for[lmi_handle] == 0);

        if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
          CopySqueezeDataForRooms(i, t, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
        } else {
          Int3(); // Get Jason, how did this happen????
        }
      }
    }

    // Now search through all the objects in this room
    for (k = rp->objects; k != -1; k = Objects[k].next) {
      object *obj = &Objects[k];
      if (obj->lighting_render_type != LRT_LIGHTMAPS)
        continue;
      if (!obj->lm_object.used)
        continue;

      for (t = 0; t < obj->lm_object.num_models; t++) {
        if (IsNonRenderableSubmodel(&Poly_models[obj->rtype.pobj_info.model_num], t))
          continue;

        for (int j = 0; j < obj->lm_object.num_faces[t]; j++) {
          lightmap_object_face *fp = &obj->lm_object.lightmap_faces[t][j];
          int lmi_handle = fp->lmi_handle;
          if (lmi_handle == BAD_LMI_INDEX)
            continue;
          if (Lmi_spoken_for[lmi_handle])
            continue;

          lightmap_info *lmi = &LightmapInfo[lmi_handle];

          int dest_x, dest_y;
          int src_w = lmi->width;
          int src_h = lmi->height;

          if (Squeeze_lightmap_handle == -1) {
            memset(Lightmap_mask, 0, 128 * 128);
            Squeeze_lightmap_handle = lm_AllocLightmap(128, 128);
            uint16_t *fill_data = (uint16_t *)lm_data(Squeeze_lightmap_handle);
            memset(fill_data, 0, 128 * 128 * 2);
          }

          if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
            // Cool, found a spot
            CopySqueezeDataForObject(obj, t, j, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
          } else {
            // Can't find an empty slot, so search through all the other remaining faces
            for (int a = rp->objects; a != -1; a = Objects[a].next) {
              object *obj = &Objects[a];
              if (obj->lighting_render_type != LRT_LIGHTMAPS)
                continue;
              if (!obj->lm_object.used)
                continue;

              for (int b = 0; b < obj->lm_object.num_models; b++) {
                if (IsNonRenderableSubmodel(&Poly_models[obj->rtype.pobj_info.model_num], b))
                  continue;

                for (int c = 0; c < obj->lm_object.num_faces[b]; c++) {
                  lightmap_object_face *fp = &obj->lm_object.lightmap_faces[b][c];
                  int lmi_handle = fp->lmi_handle;
                  if (lmi_handle == BAD_LMI_INDEX)
                    continue;
                  if (Lmi_spoken_for[lmi_handle])
                    continue;

                  lightmap_info *lmi = &LightmapInfo[lmi_handle];

                  int src_w = lmi->width;
                  int src_h = lmi->height;

                  if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
                    CopySqueezeDataForObject(obj, b, c, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
                  }
                }
              }
            }

            // Now, allocate a new lightmap and start over
            ASSERT(Squeeze_lightmap_handle != -1);
            ASSERT(GameLightmaps[Squeeze_lightmap_handle].used != 1);
            GameLightmaps[Squeeze_lightmap_handle].used--;

            memset(Lightmap_mask, 0, 128 * 128);
            Squeeze_lightmap_handle = lm_AllocLightmap(128, 128);
            uint16_t *fill_data = (uint16_t *)lm_data(Squeeze_lightmap_handle);
            memset(fill_data, 0, 128 * 128 * 2);

            ASSERT(Lmi_spoken_for[lmi_handle] == 0);

            if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
              CopySqueezeDataForObject(obj, t, j, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
            } else {
              Int3(); // Get Jason, how did this happen????
            }
          }
        }
      }
    }
  }

  if (Squeeze_lightmap_handle != -1) {
    ASSERT(GameLightmaps[Squeeze_lightmap_handle].used != 1);
    GameLightmaps[Squeeze_lightmap_handle].used--;
  }

  // Squeeze all terrain object lightmaps now
  if (external) {

    Squeeze_lightmap_handle = -1;
    for (i = 0; i <= Highest_object_index; i++) {
      object *obj = &Objects[i];

      if (obj->type == OBJ_ROOM)
        continue;
      if (obj->lighting_render_type != LRT_LIGHTMAPS)
        continue;
      if (!obj->lm_object.used)
        continue;
      if (!OBJECT_OUTSIDE(obj))
        continue;

      for (t = 0; t < obj->lm_object.num_models; t++) {
        if (IsNonRenderableSubmodel(&Poly_models[obj->rtype.pobj_info.model_num], t))
          continue;
        for (k = 0; k < obj->lm_object.num_faces[t]; k++) {
          lightmap_object_face *fp = &obj->lm_object.lightmap_faces[t][k];
          int lmi_handle = fp->lmi_handle;
          if (lmi_handle == BAD_LMI_INDEX)
            continue;
          if (Lmi_spoken_for[lmi_handle])
            continue;

          lightmap_info *lmi = &LightmapInfo[lmi_handle];

          int dest_x, dest_y;
          int src_w = lmi->width;
          int src_h = lmi->height;

          if (Squeeze_lightmap_handle == -1) {
            memset(Lightmap_mask, 0, 128 * 128);
            Squeeze_lightmap_handle = lm_AllocLightmap(128, 128);
            uint16_t *fill_data = (uint16_t *)lm_data(Squeeze_lightmap_handle);
            memset(fill_data, 0, 128 * 128 * 2);
          }

          if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
            // Cool, found a spot
            CopySqueezeDataForObject(obj, t, k, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
          } else {
            // Search through the remaining objects on the terrain
            for (int a = i; a <= Highest_object_index; a++) {
              object *obj = &Objects[a];

              if (!obj->lm_object.used)
                continue;
              if (!OBJECT_OUTSIDE(obj))
                continue;

              for (int b = 0; b < obj->lm_object.num_models; b++) {
                if (IsNonRenderableSubmodel(&Poly_models[obj->rtype.pobj_info.model_num], b))
                  continue;
                for (int c = 0; c < obj->lm_object.num_faces[b]; c++) {
                  lightmap_object_face *fp = &obj->lm_object.lightmap_faces[b][c];
                  int lmi_handle = fp->lmi_handle;
                  if (lmi_handle == BAD_LMI_INDEX)
                    continue;
                  if (Lmi_spoken_for[lmi_handle])
                    continue;

                  lightmap_info *lmi = &LightmapInfo[lmi_handle];

                  int src_w = lmi->width;
                  int src_h = lmi->height;

                  if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
                    CopySqueezeDataForObject(obj, b, c, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
                  }
                }
              }
            }

            // Now, allocate a new lightmap and start over
            ASSERT(Squeeze_lightmap_handle != -1);
            ASSERT(GameLightmaps[Squeeze_lightmap_handle].used != 1);
            GameLightmaps[Squeeze_lightmap_handle].used--;

            memset(Lightmap_mask, 0, 128 * 128);
            Squeeze_lightmap_handle = lm_AllocLightmap(128, 128);
            uint16_t *fill_data = (uint16_t *)lm_data(Squeeze_lightmap_handle);
            memset(fill_data, 0, 128 * 128 * 2);

            ASSERT(Lmi_spoken_for[lmi_handle] == 0);

            if (FindEmptyMaskSpot(src_w + 2, src_h + 2, &dest_x, &dest_y)) {
              CopySqueezeDataForObject(obj, t, k, lm_data(Squeeze_lightmap_handle), dest_x, dest_y);
            } else {
              Int3(); // Get Jason, how did this happen????
            }
          }
        }
      }
    }

    if (Squeeze_lightmap_handle != -1) {
      ASSERT(GameLightmaps[Squeeze_lightmap_handle].used != 1);
      GameLightmaps[Squeeze_lightmap_handle].used--;
    }
  }

  mem_free(Lightmap_mask);
  mem_free(Lmi_spoken_for);
  mprintf(0, "Done squeezing lightmaps.\n");
}

void ComputeSurfaceRes(rad_surface *surf, room *rp, int facenum) {
  int i;
  float left = 1.1f, right = -1, top = 1.1f, bottom = -1;
  face *fp = &rp->faces[facenum];
  int lw = lmi_w(fp->lmi_handle);
  int lh = lmi_h(fp->lmi_handle);

  for (i = 0; i < fp->num_verts; i++) {
    if (fp->face_uvls[i].u2 < left)
      left = fp->face_uvls[i].u2;
    if (fp->face_uvls[i].u2 > right)
      right = fp->face_uvls[i].u2;
    if (fp->face_uvls[i].v2 < top)
      top = fp->face_uvls[i].v2;
    if (fp->face_uvls[i].v2 > bottom)
      bottom = fp->face_uvls[i].v2;
  }

  float left_result = (left * lw) + .0001;
  float right_result = (right * lw) + .0001;
  float top_result = (top * lh) + .0001;
  float bottom_result = (bottom * lh) + .0001;

  surf->x1 = floor(left_result);
  surf->x2 = floor(right_result);

  surf->y1 = floor(top_result);
  surf->y2 = floor(bottom_result);

  surf->xresolution = (surf->x2 - surf->x1);
  surf->yresolution = (surf->y2 - surf->y1);

  // Adjust for a accuracy errors
  if (((right_result) - (float)surf->x2) > .005)
    surf->xresolution++;

  if (((bottom_result) - (float)surf->y2) > .005)
    surf->yresolution++;

  if (((top_result) - (float)surf->y1) > .99)
    surf->y1++;

  if (((left_result) - (float)surf->x1) > .99)
    surf->x1++;

  ASSERT((surf->x1 + surf->xresolution) <= lw);
  ASSERT((surf->y1 + surf->yresolution) <= lh);
}

// Take the computed volume spectra of a room and save it in the room struct
void AssignVolumeSpectraToRoom(int roomnum) {
  ASSERT(Rooms[roomnum].used);
  ASSERT(!(Rooms[roomnum].flags & RF_EXTERNAL));
  ASSERT(!(Rooms[roomnum].flags & RF_NO_LIGHT));

  room *rp = &Rooms[roomnum];

  int i, t, j;
  int w = rp->volume_width;
  int h = rp->volume_height;
  int d = rp->volume_depth;

  for (i = 0; i < d; i++) {
    for (t = 0; t < h; t++) {
      for (j = 0; j < w; j++) {
        spectra *this_spectra = &Volume_elements[roomnum][(i * w * h) + (t * w) + j].color;

        if (this_spectra->r < 0) {
          Int3(); // Shouldn't hit this
          rp->volume_lights[(i * w * h) + (t * w) + j] = INVISIBLE_VOLUME_ELEMENT;
        } else {
          float rmax = GetMaxColor(this_spectra);

          if (rmax > 1.0 && rmax > 0.0) {
            this_spectra->r /= rmax;
            this_spectra->g /= rmax;
            this_spectra->b /= rmax;
          }

          int r = (this_spectra->r * 7);
          r <<= 5;
          int g = (this_spectra->g * 7);
          g <<= 2;
          int b = (this_spectra->b * 3);

          uint8_t volume_color = r | g | b;

          if (!UseVolumeLights)
            rp->volume_lights[(i * w * h) + (t * w) + j] = 255;
          else
            rp->volume_lights[(i * w * h) + (t * w) + j] = volume_color;
        }
      }
    }
  }
}

// Returns 0 if there are bad faces in this level
int CheckForBadFaces(int roomnum) {
  int i, t;

  for (i = 0; i <= Highest_room_index; i++) {
    if (roomnum != -1 && i != roomnum)
      continue;

    room *rp = &Rooms[i];
    if (!rp->used)
      continue;

    for (t = 0; t < rp->num_faces; t++) {
      if (rp->faces[t].num_verts < 3)
        return 0; // Bad face detected!
    }
  }

  return 1;
}

// Calculates radiosity and sets lightmaps for indoor faces only
void DoRadiosityForRooms() {
  int i, t, j;
  int facecount = 0;
  int surface_index = 0;
  int max_index;
  int save_after_bsp = 0;

  if (!CheckForBadFaces(-1)) {
    OutrageMessageBox("You have bad faces in your level.  Please do a Verify Level.");
    return;
  }

  MakeBOAVisTable(1);

  if (UseBSP) {
    // if ((MessageBox(NULL,"Do you wish to save the level after BSP construction?","Question",MB_YESNO))==IDYES)
    // save_after_bsp=1;
  }

  BuildBSPTree();

  if (save_after_bsp) {
    char filename[_MAX_PATH];
    ddio_MakePath(filename, Base_directory, "BSPSave.D3L", NULL);

    // Save the level to
    SaveLevel(filename);
  }

  mprintf(0, "Setting up...\n");

  Lightmaps_for_rad = 0;

  if (UseVolumeLights)
    Do_volume_lighting = 1;

  ClearAllVolumeLights();
  ClearAllRoomLightmaps(0);
  ClearAllObjectLightmaps(0);
  ComputeAllRoomLightmapUVs(0);

  // Figure out memory for volume lights
  int vw, vh, vd;
  for (int roomnum = 0; roomnum < MAX_ROOMS; roomnum++) {
    Volume_elements[roomnum] = NULL;

    if (Rooms[roomnum].used && !(Rooms[roomnum].flags & RF_EXTERNAL) && !(Rooms[roomnum].flags & RF_NO_LIGHT)) {
      int num_bytes = GetVolumeSizeOfRoom(&Rooms[roomnum], &vw, &vh, &vd);

      Rooms[roomnum].volume_width = vw;
      Rooms[roomnum].volume_height = vh;
      Rooms[roomnum].volume_depth = vd;

      Rooms[roomnum].volume_lights = (uint8_t *)mem_malloc(vw * vh * vd);
      ASSERT(Rooms[roomnum].volume_lights);

      Volume_elements[roomnum] = (volume_element *)mem_malloc((vw * vh * vd) * sizeof(volume_element));
      ASSERT(Volume_elements[roomnum]);

      // Now go through and find all the valid spectra points
      float cur_z = Rooms[roomnum].min_xyz.z + .1;

      for (i = 0; i < vd; i++, cur_z += VOLUME_SPACING) {
        float cur_y = Rooms[roomnum].min_xyz.y + .1;
        for (t = 0; t < vh; t++, cur_y += VOLUME_SPACING) {
          float cur_x = Rooms[roomnum].min_xyz.x + .1;
          for (j = 0; j < vw; j++, cur_x += VOLUME_SPACING) {
            vector dest_vec;
            dest_vec.x = cur_x;
            dest_vec.y = cur_y;
            dest_vec.z = cur_z;

            Volume_elements[roomnum][(i * vw * vh) + (t * vw) + j].pos = dest_vec;

            if (FindPointRoom(&dest_vec) != roomnum) {
              Volume_elements[roomnum][(i * vw * vh) + (t * vw) + j].color.r = 0;
              Volume_elements[roomnum][(i * vw * vh) + (t * vw) + j].flags = VEF_REVERSE_SHOOT;
            } else {
              Volume_elements[roomnum][(i * vw * vh) + (t * vw) + j].color.r = 0;
              Volume_elements[roomnum][(i * vw * vh) + (t * vw) + j].flags = 0;
            }
          }
        }
      }
    }
  }

  // First count how many faces we'll need
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL) && !(Rooms[i].flags & RF_NO_LIGHT)) {
      facecount += Rooms[i].num_faces;
    }
  }

  // Setup specular lighting
  Calculate_specular_lighting = 1;
  SetupSpecularLighting(0);

  // Do objects
  facecount += GetTotalObjectFaces(0);
  // Do satellites
  facecount += Terrain_sky.num_satellites;

  // Allocate enough memory to hold all surfaces

  Light_surfaces = (rad_surface *)mem_malloc(facecount * sizeof(rad_surface));
  ASSERT(Light_surfaces != NULL);

  // Set initial surface properties
  max_index = surface_index = 0;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if ((Rooms[i].flags & RF_EXTERNAL) || (Rooms[i].flags & RF_NO_LIGHT))
        continue;

      for (t = 0; t < Rooms[i].num_faces; t++, surface_index++, max_index++) {

        ComputeSurfaceRes(&Light_surfaces[surface_index], &Rooms[i], t);

        if (Rooms[i].faces[t].num_verts) {
          Light_surfaces[surface_index].verts = (vector *)mem_malloc(Rooms[i].faces[t].num_verts * sizeof(vector));
          ASSERT(Light_surfaces[surface_index].verts != NULL);
        } else {
          Light_surfaces[surface_index].verts = NULL;
          mprintf(0, "Room=%d Face %d has no verts!\n", i, t);
        }

        if (Light_surfaces[surface_index].xresolution * Light_surfaces[surface_index].yresolution) {
          Light_surfaces[surface_index].elements =
              (rad_element *)mem_malloc(Light_surfaces[surface_index].xresolution *
                                        Light_surfaces[surface_index].yresolution * sizeof(rad_element));
          ASSERT(Light_surfaces[surface_index].elements != NULL);
        } else {
          Light_surfaces[surface_index].elements = NULL;
          mprintf(0, "Room=%d Face %d is slivered!\n", i, t);
        }

        Light_surfaces[surface_index].flags = 0;

        if (Rooms[i].faces[t].portal_num != -1 &&
            (((Rooms[i].portals[Rooms[i].faces[t].portal_num].flags & PF_RENDER_FACES) == 0) ||
             ((Rooms[i].portals[Rooms[i].faces[t].portal_num].flags & PF_RENDER_FACES) &&
              (GameTextures[Rooms[i].faces[t].tmap].flags & TF_TMAP2))))

        {
          Light_surfaces[surface_index].surface_type = ST_PORTAL;
          Light_surfaces[surface_index].emittance.r = 0;
          Light_surfaces[surface_index].emittance.g = 0;
          Light_surfaces[surface_index].emittance.b = 0;
        } else {
          if (Rooms[i].faces[t].light_multiple > 200)
            Rooms[i].faces[t].light_multiple = 4;

          float mul = ((float)Rooms[i].faces[t].light_multiple) / 4.0;
          mul *= GlobalMultiplier * Room_multiplier[i];

          Light_surfaces[surface_index].emittance.r = (float)GameTextures[Rooms[i].faces[t].tmap].r * mul;
          Light_surfaces[surface_index].emittance.g = (float)GameTextures[Rooms[i].faces[t].tmap].g * mul;
          Light_surfaces[surface_index].emittance.b = (float)GameTextures[Rooms[i].faces[t].tmap].b * mul;
          Light_surfaces[surface_index].surface_type = ST_ROOM;

          if ((GetMaxColor(&Light_surfaces[surface_index].emittance)) > .005)
            Light_surfaces[surface_index].flags |= SF_LIGHTSOURCE;
        }

        Light_surfaces[surface_index].normal = LightmapInfo[Rooms[i].faces[t].lmi_handle].normal;
        Light_surfaces[surface_index].roomnum = i;
        Light_surfaces[surface_index].facenum = t;

        if (Rooms[i].flags & RF_TOUCHES_TERRAIN)
          Light_surfaces[surface_index].flags |= SF_TOUCHES_TERRAIN;

        for (int k = 0; k < Rooms[i].num_portals; k++) {
          if (Rooms[i].portals[k].croom == -1 || (Rooms[Rooms[i].portals[k].croom].flags & RF_EXTERNAL))
            Light_surfaces[surface_index].flags |= SF_TOUCHES_TERRAIN;
        }

        Light_surfaces[surface_index].reflectivity = GameTextures[Rooms[i].faces[t].tmap].reflectivity;

        // Set the vertices for each element
        BuildElementListForRoomFace(i, t, &Light_surfaces[surface_index]);

        int xres = Light_surfaces[surface_index].xresolution;
        int yres = Light_surfaces[surface_index].yresolution;
      }
    }
  }

  // Setup satellites
  for (i = 0; i < Terrain_sky.num_satellites; i++, surface_index++) {
    Light_surfaces[surface_index].verts = (vector *)mem_malloc(sizeof(vector) * 3);
    ASSERT(Light_surfaces[surface_index].verts != NULL);

    Light_surfaces[surface_index].elements = (rad_element *)mem_malloc(sizeof(rad_element));
    ASSERT(Light_surfaces[surface_index].elements != NULL);

    Light_surfaces[surface_index].elements[0].verts = (vector *)mem_malloc(sizeof(vector) * 3);
    ASSERT(Light_surfaces[surface_index].elements[0].verts);

    Light_surfaces[surface_index].surface_type = ST_SATELLITE;
    Light_surfaces[surface_index].emittance.r = Terrain_sky.satellite_r[i];
    Light_surfaces[surface_index].emittance.g = Terrain_sky.satellite_g[i];
    Light_surfaces[surface_index].emittance.b = Terrain_sky.satellite_b[i];

    Light_surfaces[surface_index].roomnum = i;
    Light_surfaces[surface_index].facenum = 0;

    Light_surfaces[surface_index].reflectivity = 0;
    Light_surfaces[surface_index].xresolution = 1;
    Light_surfaces[surface_index].yresolution = 1;

    vm_MakeZero(&Light_surfaces[surface_index].normal);

    Light_surfaces[surface_index].verts[0] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surface_index].verts[1] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surface_index].verts[2] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surface_index].num_verts = 3;

    Light_surfaces[surface_index].elements[0].verts[0] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surface_index].elements[0].verts[1] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surface_index].elements[0].verts[2] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surface_index].elements[0].num_verts = 3;

    Light_surfaces[surface_index].elements[0].flags = 0;
  }

  // Setup Objects
  ComputeSurfacesForObjects(surface_index, 0);

  mprintf(0, "This radiosity run is using %d lightmaps.\n", Lightmaps_for_rad);
  mprintf(0, "Solving radiosity equation (press tilde key to stop)...\n");
  if (D3EditState.hemicube_radiosity)
    DoRadiosityRun(SM_HEMICUBE, Light_surfaces, facecount);
  else
    DoRadiosityRun(SM_RAYCAST, Light_surfaces, facecount);
  mprintf(0, "Done solving radiosity - cleaning up...\n");

  surface_index = 0;

  // Assign lightap properties
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if ((Rooms[i].flags & RF_EXTERNAL) || (Rooms[i].flags & RF_NO_LIGHT))
        continue;

      for (t = 0; t < Rooms[i].num_faces; t++, surface_index++) {
        AssignRoomSurfaceToLightmap(i, t, &Light_surfaces[surface_index]);
      }

      AssignVolumeSpectraToRoom(i);
      mem_free(Volume_elements[i]);
    }
  }

  surface_index += Terrain_sky.num_satellites;

  AssignLightmapsToObjectSurfaces(surface_index, 0);

  BlurLightmapInfos(LMI_ROOM);
  BlurLightmapInfos(LMI_ROOM_OBJECT);

  ShadeLightmapInfoEdges(LMI_ROOM);
  ShadeLightmapInfoEdges(LMI_ROOM_OBJECT);

  // Free our memory

  for (i = 0; i < facecount; i++) {
    if (Light_surfaces[i].verts)
      mem_free(Light_surfaces[i].verts);
    for (t = 0; t < Light_surfaces[i].xresolution * Light_surfaces[i].yresolution; t++)
      if (Light_surfaces[i].elements[t].num_verts > 0)
        mem_free(Light_surfaces[i].elements[t].verts);

    if (Light_surfaces[i].elements)
      mem_free(Light_surfaces[i].elements);
    Light_surfaces[i].elements = NULL;
  }
  mem_free(Light_surfaces);
  Light_surfaces = NULL;
  Do_volume_lighting = 0;

  // Free specular lighting stuff
  CleanupSpecularLighting(0);
  Calculate_specular_lighting = 0;

  // Figure out combined portals
  CheckCombinePortals(0);

  // Finally, squeeze the lightmaps
  SqueezeLightmaps(0, -1);

  char filename[_MAX_PATH + 1];
  ddio_MakePath(filename, Base_directory, "LightSave.D3L", NULL);

  // Save the level to disk
  SaveLevel(filename);

  OutrageMessageBox("Mine radiosity complete!");
}

// Calculates radiosity and sets lightmaps for indoor faces only
void DoRadiosityForCurrentRoom(room *rp) {
  int t;
  int facecount = 0;
  int surface_index = 0;
  int max_index;

  if (!CheckForBadFaces(rp - Rooms)) {
    OutrageMessageBox("You have bad faces in your level.  Please do a Verify Level.");
    return;
  }

  mprintf(0, "Setting up...\n");

  ASSERT(rp != NULL);
  ASSERT(rp->used);

  if (rp->flags & RF_EXTERNAL) {
    OutrageMessageBox("You cannot run single room radiosity on external rooms!");
    return;
  }

  if (rp->flags & RF_NO_LIGHT) {
    OutrageMessageBox("You cannot run single room radiosity on a room marked not to light!");
    return;
  }

  // Build bsp tree
  BuildSingleBSPTree(rp - Rooms);

  ClearRoomLightmaps(rp - Rooms);
  for (t = 0; t <= Highest_object_index; t++) {
    if (Objects[t].type != OBJ_NONE && (Objects[t].roomnum == rp - Rooms))
      ClearObjectLightmaps(&Objects[t]);
  }

  // Build lightmap uvs
  for (t = 0; t < rp->num_faces; t++) {
    vector verts[MAX_VERTS_PER_FACE * 5];
    int room_list[2], face_list[2];
    for (int k = 0; k < rp->faces[t].num_verts; k++)
      verts[k] = rp->verts[rp->faces[t].face_verts[k]];

    room_list[0] = rp - Rooms;
    face_list[0] = t;

    BuildLightmapUVs(room_list, face_list, 1, verts, rp->faces[t].num_verts, 0);
  }

  // First count how many faces we'll need
  facecount += rp->num_faces;

  // Do objects
  facecount += GetTotalObjectFacesForSingleRoom(rp - Rooms);

  // Allocate enough memory to hold all surfaces

  Light_surfaces = (rad_surface *)mem_malloc(facecount * sizeof(rad_surface));
  ASSERT(Light_surfaces != NULL);

  // Set initial surface properties
  max_index = surface_index = 0;

  for (t = 0; t < rp->num_faces; t++, surface_index++, max_index++) {
    ComputeSurfaceRes(&Light_surfaces[surface_index], rp, t);

    if (rp->faces[t].num_verts) {
      Light_surfaces[surface_index].verts = (vector *)mem_malloc(rp->faces[t].num_verts * sizeof(vector));
      ASSERT(Light_surfaces[surface_index].verts != NULL);
    } else {
      Light_surfaces[surface_index].verts = NULL;
      mprintf(0, "Room=%d Face %d has no verts!\n", rp - Rooms, t);
    }

    if (Light_surfaces[surface_index].xresolution * Light_surfaces[surface_index].yresolution) {
      Light_surfaces[surface_index].elements = (rad_element *)mem_malloc(
          Light_surfaces[surface_index].xresolution * Light_surfaces[surface_index].yresolution * sizeof(rad_element));
      ASSERT(Light_surfaces[surface_index].elements != NULL);
    } else {
      Light_surfaces[surface_index].elements = NULL;
      mprintf(0, "Room=%d Face %d is slivered!\n", rp - Rooms, t);
    }

    if (rp->faces[t].portal_num != -1 && (((rp->portals[rp->faces[t].portal_num].flags & PF_RENDER_FACES) == 0) ||
                                          ((rp->portals[rp->faces[t].portal_num].flags & PF_RENDER_FACES) &&
                                           (GameTextures[rp->faces[t].tmap].flags & TF_TMAP2)))) {
      Light_surfaces[surface_index].surface_type = ST_PORTAL;
      Light_surfaces[surface_index].emittance.r = 0;
      Light_surfaces[surface_index].emittance.g = 0;
      Light_surfaces[surface_index].emittance.b = 0;
    } else {
      float mul = ((float)rp->faces[t].light_multiple) / 4.0;
      mul *= GlobalMultiplier * Room_multiplier[rp - Rooms];
      Light_surfaces[surface_index].emittance.r = (float)GameTextures[rp->faces[t].tmap].r * mul;
      Light_surfaces[surface_index].emittance.g = (float)GameTextures[rp->faces[t].tmap].g * mul;
      Light_surfaces[surface_index].emittance.b = (float)GameTextures[rp->faces[t].tmap].b * mul;
      Light_surfaces[surface_index].surface_type = ST_ROOM;
    }

    Light_surfaces[surface_index].normal = rp->faces[t].normal;
    Light_surfaces[surface_index].roomnum = ROOMNUM(rp);
    Light_surfaces[surface_index].facenum = t;

    Light_surfaces[surface_index].reflectivity = GameTextures[rp->faces[t].tmap].reflectivity;

    // Set the vertices for each element
    BuildElementListForRoomFace(rp - Rooms, t, &Light_surfaces[surface_index]);

    int xres = Light_surfaces[surface_index].xresolution;
    int yres = Light_surfaces[surface_index].yresolution;
  }

  // Setup Objects
  ComputeSurfacesForObjectsForSingleRoom(surface_index, rp - Rooms);

  mprintf(0, "Solving radiosity equation (press tilde key to stop)...\n");
  if (D3EditState.hemicube_radiosity)
    DoRadiosityRun(SM_HEMICUBE, Light_surfaces, facecount);
  else
    DoRadiosityRun(SM_RAYCAST, Light_surfaces, facecount);
  mprintf(0, "Done solving radiosity - cleaning up...\n");

  surface_index = 0;

  // Assign lightap properties
  for (t = 0; t < rp->num_faces; t++, surface_index++) {
    AssignRoomSurfaceToLightmap(rp - Rooms, t, &Light_surfaces[surface_index]);
  }

  AssignLightmapsToObjectSurfacesForSingleRoom(surface_index, rp - Rooms);

  // BlurLightmapInfos (LMI_ROOM);
  // BlurLightmapInfos (LMI_ROOM_OBJECT);

  // ShadeLightmapInfoEdges (LMI_ROOM);
  // ShadeLightmapInfoEdges (LMI_ROOM_OBJECT);

  // Free our memory

  for (int i = 0; i < facecount; i++) {
    mem_free(Light_surfaces[i].verts);
    for (t = 0; t < Light_surfaces[i].xresolution * Light_surfaces[i].yresolution; t++)
      if (Light_surfaces[i].elements[t].num_verts > 0)
        mem_free(Light_surfaces[i].elements[t].verts);

    mem_free(Light_surfaces[i].elements);
    Light_surfaces[i].elements = NULL;
  }
  mem_free(Light_surfaces);
  Light_surfaces = NULL;

  // Finally, squeeze the lightmaps
  SqueezeLightmaps(0, rp - Rooms);

  OutrageMessageBox("Room radiosity complete!");
}

// Allocates and sets a lightmap based on the surface elements given
void AssignRoomSurfaceToLightmap(int roomnum, int facenum, rad_surface *sp) {
  face *fp = &Rooms[roomnum].faces[facenum];
  room *rp = &Rooms[roomnum];

  int i, t, lmi_handle;
  int xres, yres;
  int lw, lh;
  int x1 = sp->x1;
  int y1 = sp->y1;
  int use_lightmap = 1;

  xres = sp->xresolution;
  yres = sp->yresolution;

  ASSERT(fp->lmi_handle != BAD_LMI_INDEX);
  lmi_handle = fp->lmi_handle;

  lw = lmi_w(lmi_handle);
  lh = lmi_h(lmi_handle);

  ASSERT((xres + x1) <= lw);
  ASSERT((yres + y1) <= lh);

  ASSERT(lw >= 2);
  ASSERT(lh >= 2);

  uint16_t *dest_data = lm_data(LightmapInfo[lmi_handle].lm_handle);

  // Set face pointer
  if (GameTextures[fp->tmap].flags & TF_ALPHA)
    use_lightmap = 0;
  if (GameTextures[fp->tmap].flags & (TF_FORCE_LIGHTMAP | TF_SATURATE_LIGHTMAP))
    use_lightmap = 1;

  if (use_lightmap)
    fp->flags |= FF_LIGHTMAP;

  for (i = 0; i < yres; i++) {
    for (t = 0; t < xres; t++) {
      if (!(sp->elements[i * xres + t].flags & EF_IGNORE)) {
        ddgr_color color = GR_16_TO_COLOR(dest_data[(i + y1) * lw + (t + x1)]);
        int red = GR_COLOR_RED(color);
        int green = GR_COLOR_GREEN(color);
        int blue = GR_COLOR_BLUE(color);

        float fr, fg, fb;

        if (!(dest_data[(i + y1) * lw + (t + x1)] & OPAQUE_FLAG)) {
          red = green = blue = 0;
        }

        fr = std::min(1.0f, sp->elements[i * xres + t].exitance.r + Ambient_red + Room_ambience_r[roomnum]);
        fg = std::min(1.0f, sp->elements[i * xres + t].exitance.g + Ambient_green + Room_ambience_g[roomnum]);
        fb = std::min(1.0f, sp->elements[i * xres + t].exitance.b + Ambient_blue + Room_ambience_b[roomnum]);

        fr = (fr * 255) + .5;
        fg = (fg * 255) + .5;
        fb = (fb * 255) + .5;

        red += (int)fr;
        green += (int)fg;
        blue += (int)fb;

        if (dest_data[(i + y1) * lw + (t + x1)] & OPAQUE_FLAG) {

          red /= 2;
          green /= 2;
          blue /= 2;
        }

        red = std::min(red, 255);
        green = std::min(green, 255);
        blue = std::min(blue, 255);

        uint16_t texel = OPAQUE_FLAG | GR_RGB16(red, green, blue);

        dest_data[(i + y1) * lw + (t + x1)] = texel;
      }
    }
  }
}

// Important - vertnum is the index into the face_verts[] array in the face structure,
// not an index into the verts[] array of the room structure
void BuildElementListForRoomFace(int roomnum, int facenum, rad_surface *surf) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE * 5];
  vector rot_vert;
  vector vert;
  int i, t;
  int xres, yres;
  int lmi_handle;
  int x1 = surf->x1;
  int y1 = surf->y1;

  xres = surf->xresolution;
  yres = surf->yresolution;

  ASSERT(Rooms[roomnum].used);
  ASSERT(Rooms[roomnum].faces[facenum].num_verts >= 3);
  ASSERT(Rooms[roomnum].faces[facenum].lmi_handle != BAD_LMI_INDEX);

  lmi_handle = Rooms[roomnum].faces[facenum].lmi_handle;
  avg_vert = ScratchCenters[lmi_handle];

  // Make the orientation matrix
  // Reverse the normal because we're looking "at" the face, not from it
  fvec = -LightmapInfo[lmi_handle].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    vert = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find a base vector
  vector base_vector;
  vector xdiff, ydiff;

  vm_MakeZero(&xdiff);
  vm_MakeZero(&ydiff);

  // Rotate our upper left point into our 2d space
  vert = LightmapInfo[lmi_handle].upper_left - avg_vert;
  vm_MatrixMulVector(&base_vector, &vert, &trans_matrix);

  xdiff.x = LightmapInfo[lmi_handle].xspacing;
  ydiff.y = LightmapInfo[lmi_handle].yspacing;

  vm_TransposeMatrix(&trans_matrix);

  for (i = 0; i < yres; i++) {
    for (t = 0; t < xres; t++) {
      int element_index = i * xres + t;
      vector clip_verts[4];

      rad_element *ep = &surf->elements[element_index];

      // Allocate some free space
      clip_verts[0] = base_vector + (xdiff * (t + x1)) - (ydiff * (i + y1));
      clip_verts[1] = base_vector + (xdiff * (t + x1 + 1)) - (ydiff * (i + y1));
      clip_verts[2] = base_vector + (xdiff * (t + x1 + 1)) - (ydiff * (i + y1 + 1));
      clip_verts[3] = base_vector + (xdiff * (t + x1)) - (ydiff * (i + y1 + 1));
      ClipSurfaceElement(verts, ep, clip_verts, Rooms[roomnum].faces[facenum].num_verts);

      for (int k = 0; k < ep->num_verts; k++) {
        vm_MatrixMulVector(&rot_vert, &ep->verts[k], &trans_matrix);
        ep->verts[k] = rot_vert + avg_vert;
      }
    }
  }

  if (Square_surfaces) {
    surf->verts[0] = base_vector;
    surf->verts[1] = base_vector + (xdiff * xres);
    surf->verts[2] = base_vector + (xdiff * xres) - (ydiff * yres);
    surf->verts[3] = base_vector - (ydiff * yres);

    for (int k = 0; k < 4; k++) {
      vm_MatrixMulVector(&rot_vert, &surf->verts[k], &trans_matrix);
      surf->verts[k] = rot_vert + avg_vert;
    }
    surf->num_verts = 4;
  } else {

    surf->num_verts = Rooms[roomnum].faces[facenum].num_verts;
    for (int k = 0; k < surf->num_verts; k++) {
      surf->verts[k] = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[k]];
    }
  }
}

vector *rad_ClipTop, *rad_ClipBottom, *rad_ClipLeft, *rad_ClipRight;
rad_point GlobalTempRadPoint;

void SetRadClipLines(vector *tp, vector *rp, vector *bp, vector *lp) {
  rad_ClipTop = tp;
  rad_ClipRight = rp;
  rad_ClipBottom = bp;
  rad_ClipLeft = lp;
}

uint8_t CodeRadPoint(rad_point *rp) {
  uint8_t code = 0;
  if (rp->pos.x < rad_ClipLeft->x)
    code |= CC_OFF_LEFT;
  if (rp->pos.x > rad_ClipRight->x)
    code |= CC_OFF_RIGHT;
  if (rp->pos.y < rad_ClipBottom->y)
    code |= CC_OFF_BOT;
  if (rp->pos.y > rad_ClipTop->y)
    code |= CC_OFF_TOP;
  rp->code = code;

  return code;
}

void ClipSurfaceElement(vector *surf_verts, rad_element *ep, vector *clip_verts, int nv) {
  rad_point src_verts[50];
  rad_point dest_verts[50];
  rad_point *slist, *dlist;
  uint8_t and = 0xff;
  uint8_t or = 0;
  int i;

  ASSERT(nv < 50);

  ep->flags = 0;

  SetRadClipLines(&clip_verts[0], &clip_verts[1], &clip_verts[2], &clip_verts[3]);

  for (i = 0; i < nv; i++) {
    src_verts[i].pos = surf_verts[i];
    src_verts[i].code = CodeRadPoint(&src_verts[i]);
  }

  for (i = 0; i < nv; i++) {
    and &= src_verts[i].code;
    or |= src_verts[i].code;
  }

  if (and) {
    // This element is not even in the face, ignore it
    ep->flags |= EF_IGNORE;
    ep->num_verts = 0;
    return;
  }

  int pnv = nv, nnv;
  slist = src_verts;
  dlist = dest_verts;

  nnv = ClipRadPointList(&slist, &dlist, &pnv, or);

  ep->num_verts = nnv;

  if (ep->num_verts == 0)
    ep->flags |= EF_IGNORE;
  else {
    ep->verts = (vector *)mem_malloc(sizeof(vector) * nnv);
    ASSERT(ep->verts);

    for (i = 0; i < nnv; i++) {
      ep->verts[i] = dlist[i].pos;
    }
  }
}

// Takes a points and clips all its viewpoints so they fit into the view frustum
// Puts the new clipped list in dest
// Returns number of points in clipped polygon

int ClipRadPointList(rad_point **src, rad_point **dest, int *nv, int code) {
  int plane, num = 0;
  rad_point **save_src = src, *t;
  rad_point **save_dest = dest;

  for (plane = 1; plane < 16; plane <<= 1) {
    if (plane & code) // Is this point off this plane?
    {

      *nv = ClipRadToPlane(plane, *src, *dest, *nv);
      if (*nv == 0)
        return 0;
      ASSERT(*nv >= 3);

      t = *dest;
      *dest = *src;
      *src = t;
      num++;
    }
  }

  t = *dest;
  *dest = *src;
  *src = t;

  return (*nv);
}

// Clips to a specific plane, putting resulting points in dest and returning number of points in dest
int ClipRadToPlane(int plane, rad_point *src, rad_point *dest, int nv) {
  int i, num = 0, limit = nv - 1, ppoint, npoint;

  ASSERT(nv >= 3);

  for (i = 0; i < nv; i++) {
    if (i == limit)
      npoint = 0;
    else
      npoint = i + 1;

    if (i == 0)
      ppoint = limit;
    else
      ppoint = i - 1;

    // mprintf(0,"checking point %d ",i);
    if (src[i].code & plane) // off this plane?
    {

      if (!(src[ppoint].code & plane)) // prev point on?
      {
        // mprintf(0,"pVertex %d off %d plane.\n",i,plane);
        ClipRadEdge(plane, &src[ppoint], &src[i]);

        memcpy(&dest[num], &GlobalTempRadPoint, sizeof(rad_point));
        num++;
      }

      if (!(src[npoint].code & plane)) // next point on?
      {

        // mprintf(0,"nVertex %d off %d plane.\n",i,plane);
        ClipRadEdge(plane, &src[npoint], &src[i]);

        memcpy(&dest[num], &GlobalTempRadPoint, sizeof(rad_point));
        num++;
      }

    } else // This point is on
    {

      // mprintf(0,"is on\n");
      memcpy(&dest[num], &src[i], sizeof(rad_point));
      num++;
    }
  }
  return (num);
}

// Takes two points and a plane, and clips.
void ClipRadEdge(int plane_flag, rad_point *on_pnt, rad_point *off_pnt) {
  if (plane_flag & CC_OFF_TOP) {
    float percent_on = 1.0 - ((off_pnt->pos.y - rad_ClipTop->y) / (off_pnt->pos.y - on_pnt->pos.y));
    GlobalTempRadPoint.pos = on_pnt->pos + ((off_pnt->pos - on_pnt->pos) * percent_on);
  }

  if (plane_flag & CC_OFF_RIGHT) {
    float percent_on = 1.0 - ((off_pnt->pos.x - rad_ClipRight->x) / (off_pnt->pos.x - on_pnt->pos.x));
    GlobalTempRadPoint.pos = on_pnt->pos + ((off_pnt->pos - on_pnt->pos) * percent_on);
  }

  if (plane_flag & CC_OFF_LEFT) {
    float percent_on = 1.0 - ((off_pnt->pos.x - rad_ClipLeft->x) / (off_pnt->pos.x - on_pnt->pos.x));
    GlobalTempRadPoint.pos = on_pnt->pos + ((off_pnt->pos - on_pnt->pos) * percent_on);
  }

  if (plane_flag & CC_OFF_BOT) {
    float percent_on = 1.0 - ((off_pnt->pos.y - rad_ClipBottom->y) / (off_pnt->pos.y - on_pnt->pos.y));
    GlobalTempRadPoint.pos = on_pnt->pos + ((off_pnt->pos - on_pnt->pos) * percent_on);
  }

  CodeRadPoint(&GlobalTempRadPoint);
}

// Adds color spectrums together
void AddSpectra(spectra *dest, spectra *a, spectra *b) {
  dest->r = a->r + b->r;
  dest->g = a->g + b->g;
  dest->b = a->b + b->b;
}

// Returns 1 if a src vector can hit dest vector unobstructed, else 0
int ShootRayForTerrainLight(vector *src, vector *dest, int cellnum) {
  fvi_info hit_info;
  fvi_query fq;
  vector temp_dest = *dest;

  if (temp_dest.y >= MAX_TERRAIN_HEIGHT * 3) {
    float mag;
    float ydiff;
    vector ray = temp_dest - *src;

    mag = vm_GetMagnitude(&ray);
    ray /= mag;

    ydiff = ((MAX_TERRAIN_HEIGHT * 3) - src->y) / ray.y;

    temp_dest = *src + (ray * ydiff);
  }

  // shoot a ray from the light position to the current vertex
  fq.p0 = src;
  fq.p1 = &temp_dest;
  fq.startroom = MAKE_ROOMNUM(cellnum);

  fq.rad = 0.0f;
  fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_NON_LIGHTMAP_OBJECTS | FQ_OBJ_BACKFACE | FQ_NO_RELINK |
             FQ_IGNORE_RENDER_THROUGH_PORTALS;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;

  int fate = fvi_FindIntersection(&fq, &hit_info);

  if (fate == HIT_OUT_OF_TERRAIN_BOUNDS || fate == HIT_NONE)
    return 1;

  return 0;
}

#define AREA_X (TERRAIN_WIDTH - 1)
#define AREA_Z (TERRAIN_DEPTH - 1)
// #define AREA_X	128
// #define AREA_Z	128

// Puts a 3d grid of points on the terrain and sets a bit indicating if a light source
// can reach that point.  This is used for the dynamic lighting of objects on the terrain
void DoTerrainDynamicTable() {
  int i, t, k, j, maxrays;
  int raynum = 0;
  int key;

  maxrays = AREA_X * AREA_Z * 8 * Terrain_sky.num_satellites;

  mprintf(0, "Calculating dynamic light table for %d points...\n", maxrays);
  mprintf(0, "Press tilde key to abort!\n");

  memset(Terrain_dynamic_table, 0, (TERRAIN_DEPTH * TERRAIN_WIDTH));

  for (i = 0; i < AREA_Z; i++) {
    //	ddio_KeyFrame();
    while ((key = ddio_KeyInKey()) != 0) {
      if (key == KEY_LAPOSTRO) {
        for (; i < AREA_Z; i++) {
          for (t = 0; t < AREA_X; t++) {
            int tseg = i * TERRAIN_WIDTH + t;
            Terrain_dynamic_table[tseg] = 255;
          }
        }

        return;
      }
    }

    for (t = 0; t < AREA_X; t++) {
      int tseg = i * TERRAIN_WIDTH + t;
      vector gp;

      gp.x = (t * TERRAIN_SIZE);
      gp.z = (i * TERRAIN_SIZE);

      gp.y = Terrain_seg[tseg].y;

      for (k = 0; k < 8; k++) {
        vector pos;

        pos.x = gp.x;
        pos.z = gp.z;
        pos.y = k * (MAX_TERRAIN_HEIGHT / 8);

        for (j = 0; j < Terrain_sky.num_satellites; j++) {
          raynum++;
          mprintf_at(2, 4, 0, "Ray=%d      ", raynum);

          if (gp.y > pos.y)
            continue;

          int answer;
          answer = ShootRayForTerrainLight(&pos, &Terrain_sky.satellite_vectors[j], tseg);
          if (!answer)
            continue;

          Terrain_dynamic_table[tseg] |= (1 << k);
          j = Terrain_sky.num_satellites;
        }
      }
    }
  }
}

void ComputeTerrainSpeedTable() {
  int i, t, j, raynum = 0;

  mprintf(0, "Precomputing terrain speed table...(%d rays)\n", AREA_X * AREA_Z);
  for (i = 0; i < AREA_Z; i++) {
    for (t = 0; t < AREA_X; t++) {
      int tseg = i * TERRAIN_WIDTH + t;
      vector pos;

      pos.x = (t * TERRAIN_SIZE);
      pos.z = (i * TERRAIN_SIZE);
      pos.y = (Terrain_seg[tseg].y) + .001;

      raynum++;
      if ((raynum % 1000) == 0)
        mprintf_at(2, 4, 0, "Ray=%d      ", raynum);

      for (j = 0; j < Terrain_sky.num_satellites; j++)
        TerrainLightSpeedup[j][tseg] = ShootRayForTerrainLight(&pos, &Terrain_sky.satellite_vectors[j], tseg);
    }
  }
}

float GetMaxColor(spectra *sp);

// Calculates radiosity for the outdoor surfaces
void DoRadiosityForTerrain() {
  int i, t, raynum = 0;
  int extra_surfaces = 0, total_surfaces = 0;
  int surf_index = 0;
  spectra *terrain_sums[2];
  int room_surf_start, obj_surf_start;

  int do_dynamic = 0;
  int lit = 0;

  // First make sure there is even a light source
  for (i = 0; i < Terrain_sky.num_satellites; i++) {
    int tmap = Terrain_sky.satellite_texture[i];
    if (Terrain_sky.satellite_r[i] > 0 || Terrain_sky.satellite_g[i] > 0 || Terrain_sky.satellite_b[i] > 0)
      lit = 1;
  }

  if (!lit) {
    OutrageMessageBox("No moons/suns cast light so there is no point in running terrain radiosity!");
    return;
  }

  for (i = 0; i < Terrain_sky.num_satellites; i++) {
    TerrainLightSpeedup[i] = (uint8_t *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH);
    ASSERT(TerrainLightSpeedup[i]);
  }

  if ((MessageBox(NULL,
                  "Do you wish to calculate dynamic terrain lighting when radiosity is completed? (Note: Dynamic "
                  "lighting takes a long time)",
                  "Question", MB_YESNO)) == IDYES)
    do_dynamic = 1;

  if (!Ignore_terrain)
    ComputeTerrainSpeedTable();

  extra_surfaces += Terrain_sky.num_satellites;
  extra_surfaces += GetTotalObjectFaces(1);

  // Get our external rooms ready
  ClearAllRoomLightmaps(1);
  ComputeAllRoomLightmapUVs(1);

  // count how many faces we'll need
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used && (Rooms[i].flags & RF_EXTERNAL))
      extra_surfaces += Rooms[i].num_faces;
  }

  if (!Ignore_terrain)
    total_surfaces = ((AREA_X) * (AREA_Z) * 2);
  total_surfaces += extra_surfaces;

  // Get our object lightmaps ready
  ClearAllObjectLightmaps(1);

  // Allocate memory
  terrain_sums[0] = (spectra *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH * sizeof(spectra));
  terrain_sums[1] = (spectra *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH * sizeof(spectra));
  ASSERT(terrain_sums[0] && terrain_sums[1]);

  Light_surfaces = (rad_surface *)mem_malloc(total_surfaces * sizeof(rad_surface));
  ASSERT(Light_surfaces != NULL);

  // Setup radiosity surfaces
  if (!Ignore_terrain) {
    for (i = 0; i < (AREA_X) * (AREA_Z); i++, surf_index += 2) {
      vector a, b, c;
      int x, z;

      x = i % AREA_X;
      z = i / AREA_Z;

      int seg = z * TERRAIN_WIDTH + x;

      // Do common stuff (for both triangles)
      for (x = 0; x < 2; x++) {
        Light_surfaces[i * 2 + x].surface_type = ST_TERRAIN;
        Light_surfaces[i * 2 + x].emittance.r =
            (float)GameTextures[Terrain_tex_seg[Terrain_seg[seg].texseg_index].tex_index].r;
        Light_surfaces[i * 2 + x].emittance.g =
            (float)GameTextures[Terrain_tex_seg[Terrain_seg[seg].texseg_index].tex_index].g;
        Light_surfaces[i * 2 + x].emittance.b =
            (float)GameTextures[Terrain_tex_seg[Terrain_seg[seg].texseg_index].tex_index].b;

        Light_surfaces[i * 2 + x].roomnum = MAKE_ROOMNUM(seg);
        Light_surfaces[i * 2 + x].facenum = x;

        Light_surfaces[i * 2 + x].reflectivity =
            GameTextures[Terrain_tex_seg[Terrain_seg[seg].texseg_index].tex_index].reflectivity;
        Light_surfaces[i * 2 + x].xresolution = 1;
        Light_surfaces[i * 2 + x].yresolution = 1;
      }

      // Do upper left triangle
      Light_surfaces[i * 2].elements = (rad_element *)mem_malloc(sizeof(rad_element));
      ASSERT(Light_surfaces[i * 2].elements != NULL);

      Light_surfaces[i * 2].elements[0].verts = (vector *)mem_malloc(sizeof(vector) * 3);
      ASSERT(Light_surfaces[i * 2].elements[0].verts);

      Light_surfaces[i * 2].verts = (vector *)mem_malloc(sizeof(vector) * 3);
      ASSERT(Light_surfaces[i * 2].verts != NULL);

      Light_surfaces[i * 2].normal = TerrainNormals[MAX_TERRAIN_LOD - 1][seg].normal1;

      z = i / (AREA_X);
      x = i % (AREA_X);

      a.x = x * TERRAIN_SIZE;
      a.y = Terrain_seg[(z * TERRAIN_WIDTH) + (x)].y;
      a.z = z * TERRAIN_SIZE;

      b.x = x * TERRAIN_SIZE;
      b.y = Terrain_seg[((z + 1) * TERRAIN_WIDTH) + (x)].y;
      b.z = (z + 1) * TERRAIN_SIZE;

      c.x = (x + 1) * TERRAIN_SIZE;
      c.y = Terrain_seg[((z + 1) * TERRAIN_WIDTH) + (x + 1)].y;
      c.z = (z + 1) * TERRAIN_SIZE;

      Light_surfaces[i * 2].verts[0] = a;
      Light_surfaces[i * 2].verts[1] = b;
      Light_surfaces[i * 2].verts[2] = c;
      Light_surfaces[i * 2].num_verts = 3;

      Light_surfaces[i * 2].elements[0].verts[0] = a;
      Light_surfaces[i * 2].elements[0].verts[1] = b;
      Light_surfaces[i * 2].elements[0].verts[2] = c;
      Light_surfaces[i * 2].elements[0].num_verts = 3;

      Light_surfaces[i * 2].elements[0].flags = 0;

      // Now do lower right

      Light_surfaces[i * 2 + 1].elements = (rad_element *)mem_malloc(sizeof(rad_element));
      ASSERT(Light_surfaces[i * 2 + 1].elements != NULL);

      Light_surfaces[i * 2 + 1].elements[0].verts = (vector *)mem_malloc(sizeof(vector) * 3);
      ASSERT(Light_surfaces[i * 2 + 1].elements[0].verts);

      Light_surfaces[i * 2 + 1].verts = (vector *)mem_malloc(sizeof(vector) * 3);
      ASSERT(Light_surfaces[i * 2 + 1].verts != NULL);

      Light_surfaces[i * 2 + 1].normal = TerrainNormals[MAX_TERRAIN_LOD - 1][seg].normal2;

      z = i / (AREA_X);
      x = i % (AREA_X);

      a.x = x * TERRAIN_SIZE;
      a.y = Terrain_seg[(z * TERRAIN_WIDTH) + (x)].y;
      a.z = z * TERRAIN_SIZE;

      b.x = (x + 1) * TERRAIN_SIZE;
      b.y = Terrain_seg[((z + 1) * TERRAIN_WIDTH) + (x + 1)].y;
      b.z = (z + 1) * TERRAIN_SIZE;

      c.x = (x + 1) * TERRAIN_SIZE;
      c.y = Terrain_seg[(z * TERRAIN_WIDTH) + (x + 1)].y;
      c.z = z * TERRAIN_SIZE;

      Light_surfaces[i * 2 + 1].verts[0] = a;
      Light_surfaces[i * 2 + 1].verts[1] = b;
      Light_surfaces[i * 2 + 1].verts[2] = c;
      Light_surfaces[i * 2 + 1].num_verts = 3;

      Light_surfaces[i * 2 + 1].elements[0].verts[0] = a;
      Light_surfaces[i * 2 + 1].elements[0].verts[1] = b;
      Light_surfaces[i * 2 + 1].elements[0].verts[2] = c;
      Light_surfaces[i * 2 + 1].elements[0].num_verts = 3;

      Light_surfaces[i * 2 + 1].elements[0].flags = 0;
    }
  }

  // Setup satellites
  for (i = 0; i < Terrain_sky.num_satellites; i++, surf_index++) {
    Light_surfaces[surf_index].verts = (vector *)mem_malloc(sizeof(vector) * 3);
    ASSERT(Light_surfaces[surf_index].verts != NULL);

    Light_surfaces[surf_index].elements = (rad_element *)mem_malloc(sizeof(rad_element));
    ASSERT(Light_surfaces[surf_index].elements != NULL);

    Light_surfaces[surf_index].elements[0].verts = (vector *)mem_malloc(sizeof(vector) * 3);
    ASSERT(Light_surfaces[surf_index].elements[0].verts);

    Light_surfaces[surf_index].surface_type = ST_SATELLITE;
    Light_surfaces[surf_index].emittance.r = Terrain_sky.satellite_r[i];
    Light_surfaces[surf_index].emittance.g = Terrain_sky.satellite_g[i];
    Light_surfaces[surf_index].emittance.b = Terrain_sky.satellite_b[i];

    Light_surfaces[surf_index].roomnum = i;
    Light_surfaces[surf_index].facenum = 0;

    Light_surfaces[surf_index].reflectivity = 0;
    Light_surfaces[surf_index].xresolution = 1;
    Light_surfaces[surf_index].yresolution = 1;

    vm_MakeZero(&Light_surfaces[surf_index].normal);

    Light_surfaces[surf_index].verts[0] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surf_index].verts[1] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surf_index].verts[2] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surf_index].num_verts = 3;

    Light_surfaces[surf_index].elements[0].verts[0] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surf_index].elements[0].verts[1] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surf_index].elements[0].verts[2] = Terrain_sky.satellite_vectors[i];
    Light_surfaces[surf_index].elements[0].num_verts = 3;

    Light_surfaces[surf_index].elements[0].flags = 0;
  }

  // Setup external rooms

  room_surf_start = surf_index;
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (!(Rooms[i].flags & RF_EXTERNAL))
        continue;

      for (t = 0; t < Rooms[i].num_faces; t++, surf_index++) {

        ComputeSurfaceRes(&Light_surfaces[surf_index], &Rooms[i], t);

        Light_surfaces[surf_index].verts = (vector *)mem_malloc(Rooms[i].faces[t].num_verts * sizeof(vector));
        ASSERT(Light_surfaces[surf_index].verts != NULL);

        Light_surfaces[surf_index].elements = (rad_element *)mem_malloc(
            Light_surfaces[surf_index].xresolution * Light_surfaces[surf_index].yresolution * sizeof(rad_element));
        ASSERT(Light_surfaces[surf_index].elements != NULL);

        if (Rooms[i].faces[t].portal_num != -1 &&
            !(Rooms[i].portals[Rooms[i].faces[t].portal_num].flags & PF_RENDER_FACES))

        {
          Light_surfaces[surf_index].surface_type = ST_PORTAL;
          Light_surfaces[surf_index].emittance.r = 0;
          Light_surfaces[surf_index].emittance.g = 0;
          Light_surfaces[surf_index].emittance.b = 0;
        } else {
          float mul = ((float)Rooms[i].faces[t].light_multiple) / 4.0;
          mul *= GlobalMultiplier * Room_multiplier[i];

          Light_surfaces[surf_index].emittance.r = (float)GameTextures[Rooms[i].faces[t].tmap].r * mul;
          Light_surfaces[surf_index].emittance.g = (float)GameTextures[Rooms[i].faces[t].tmap].g * mul;
          Light_surfaces[surf_index].emittance.b = (float)GameTextures[Rooms[i].faces[t].tmap].b * mul;
          Light_surfaces[surf_index].surface_type = ST_EXTERNAL_ROOM;

          // if ((GetMaxColor (&Light_surfaces[surf_index].emittance))>.005)
          //	Light_surfaces[surf_index].flags|=SF_LIGHTSOURCE;
        }

        Light_surfaces[surf_index].normal = LightmapInfo[Rooms[i].faces[t].lmi_handle].normal;
        Light_surfaces[surf_index].roomnum = i;
        Light_surfaces[surf_index].facenum = t;

        Light_surfaces[surf_index].reflectivity = GameTextures[Rooms[i].faces[t].tmap].reflectivity;

        // Set the vertices for each element
        BuildElementListForRoomFace(i, t, &Light_surfaces[surf_index]);

        int xres = Light_surfaces[surf_index].xresolution;
        int yres = Light_surfaces[surf_index].yresolution;
      }
    }
  }

  // Setup objects
  obj_surf_start = surf_index;
  ComputeSurfacesForObjects(surf_index, 1);

  mprintf(0, "Solving radiosity equation (press tilde key to stop)...\n");

  if (D3EditState.hemicube_radiosity)
    DoRadiosityRun(SM_SWITCH_AFTER_SATELLITES, Light_surfaces, total_surfaces);
  else
    DoRadiosityRun(SM_RAYCAST, Light_surfaces, total_surfaces);

  // Figure out lighting by averaging the two triangles per terrain cell

  if (!Ignore_terrain) {
    for (i = 0; i < AREA_X * AREA_Z; i++) {
      // Add in ambient terrain light
      terrain_sums[0][i].r = std::min(1.0f, Light_surfaces[i * 2].elements[0].exitance.r + Ambient_red);
      terrain_sums[0][i].g = std::min(1.0f, Light_surfaces[i * 2].elements[0].exitance.g + Ambient_green);
      terrain_sums[0][i].b = std::min(1.0f, Light_surfaces[i * 2].elements[0].exitance.b + Ambient_blue);

      terrain_sums[1][i].r = std::min(1.0f, Light_surfaces[i * 2 + 1].elements[0].exitance.r + Ambient_red);
      terrain_sums[1][i].g = std::min(1.0f, Light_surfaces[i * 2 + 1].elements[0].exitance.g + Ambient_green);
      terrain_sums[1][i].b = std::min(1.0f, Light_surfaces[i * 2 + 1].elements[0].exitance.b + Ambient_blue);
    }

    for (i = 0; i < (AREA_X) * (AREA_Z); i++) {
      int x, z;
      spectra total;
      int num_items = 0;
      int seg;

      memset(&total, 0, sizeof(spectra));

      x = i % (AREA_X);
      z = i / (AREA_Z);

      seg = z * TERRAIN_WIDTH + x;

      if (x != 0) {
        AddSpectra(&total, &total, &terrain_sums[1][z * (AREA_X) + (x - 1)]);
        num_items++;
      }

      AddSpectra(&total, &total, &terrain_sums[0][z * (AREA_X) + x]);
      AddSpectra(&total, &total, &terrain_sums[1][z * (AREA_X) + x]);

      num_items += 2;

      if (x != 0) {
        if (z != 0) {
          AddSpectra(&total, &total, &terrain_sums[0][(z - 1) * (AREA_X) + (x - 1)]);
          AddSpectra(&total, &total, &terrain_sums[1][(z - 1) * (AREA_X) + (x - 1)]);
          num_items += 2;
        }
      }

      if (z != 0) {

        AddSpectra(&total, &total, &terrain_sums[0][(z - 1) * (AREA_X) + x]);
        num_items++;
      }

      total.r /= num_items;
      total.g /= num_items;
      total.b /= num_items;

      if (total.r > 1.0)
        total.r = 1.0;
      if (total.g > 1.0)
        total.g = 1.0;
      if (total.b > 1.0)
        total.b = 1.0;

      Terrain_seg[seg].l = Float_to_ubyte(GetMaxColor(&total));

      Terrain_seg[seg].r = Float_to_ubyte(total.r);
      Terrain_seg[seg].g = Float_to_ubyte(total.g);
      Terrain_seg[seg].b = Float_to_ubyte(total.b);
    }
  }

  // Assign lightmaps to external rooms
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (!(Rooms[i].flags & RF_EXTERNAL))
        continue;

      for (t = 0; t < Rooms[i].num_faces; t++, room_surf_start++) {
        AssignRoomSurfaceToLightmap(i, t, &Light_surfaces[room_surf_start]);
      }
    }
  }

  // Now assign lightmaps to objects
  AssignLightmapsToObjectSurfaces(obj_surf_start, 1);

  // Shade room/object lightmaps

  BlurLightmapInfos(LMI_EXTERNAL_ROOM);
  BlurLightmapInfos(LMI_TERRAIN_OBJECT);

  ShadeLightmapInfoEdges(LMI_EXTERNAL_ROOM);
  ShadeLightmapInfoEdges(LMI_TERRAIN_OBJECT);

  // Free memory

  for (i = 0; i < total_surfaces; i++) {
    mem_free(Light_surfaces[i].verts);
    for (int t = 0; t < Light_surfaces[i].xresolution * Light_surfaces[i].yresolution; t++)
      if (Light_surfaces[i].elements[t].num_verts > 0)
        mem_free(Light_surfaces[i].elements[t].verts);
    mem_free(Light_surfaces[i].elements);
  }

  mem_free(Light_surfaces);
  mem_free(terrain_sums[0]);
  mem_free(terrain_sums[1]);

  for (i = 0; i < Terrain_sky.num_satellites; i++)
    mem_free(TerrainLightSpeedup[i]);

  UpdateTerrainLightmaps();
  SqueezeLightmaps(1, -1);
  // Figure out combined portals
  CheckCombinePortals(1);

  if (do_dynamic)
    DoTerrainDynamicTable();

  OutrageMessageBox(
      "Terrain radiosity complete!\nIt is recommended you save the level so you won't have to rerun this operation.");
}
/*
void DoRadiosityForTerrain ()
{
        int i,t,j,maxrays;
        int raynum=0;
        spectra *exitance;
        int lit=0;
        int do_dynamic=0;

        if ((MessageBox(NULL,"Do you wish to calculate dynamic terrain lighting when radiosity is completed? (Note:
Dynamic lighting takes a long time)","Question",MB_YESNO))==IDYES) do_dynamic=1;

        // First make sure there is even a light source
        for (i=0;i<Terrain_sky.num_satellites;i++)
        {
                int tmap=Terrain_sky.satellite_texture[i];
                if (GameTextures[tmap].r>0 || GameTextures[tmap].g || GameTextures[tmap].b)
                        lit=1;
        }

        if (!lit)
        {
                OutrageMessageBox ("No moons/suns cast light so there is no point in running terrain radiosity!");
                return;
        }

        maxrays=(TERRAIN_DEPTH-1)*(TERRAIN_WIDTH-1)*Terrain_sky.num_satellites;

        mprintf(0,"Calculating terrain radiosity for %d points! (be patient!)\n",maxrays);

        // Malloc some memory
        exitance=(spectra *)mem_malloc (TERRAIN_DEPTH*TERRAIN_WIDTH*sizeof(spectra));
        ASSERT (exitance!=NULL);

        for (i=0;i<TERRAIN_DEPTH*TERRAIN_WIDTH;i++)
        {
                exitance[i].r=0;
                exitance[i].g=0;
                exitance[i].b=0;
        }

        // Now shoot a ray from every triangle on the terrain to every moon/sun in the
        // sky, tallying the results
        for (i=0;i<TERRAIN_DEPTH-1;i++)
        {
                for (t=0;t<TERRAIN_WIDTH-1;t++)
                {
                        int tseg=i*TERRAIN_WIDTH+t;
                        vector pos1,pos2;

                        pos1.x=(t*TERRAIN_SIZE)+(TERRAIN_SIZE/3);
                        pos1.z=(i*TERRAIN_SIZE)+(TERRAIN_SIZE * .66);
                        pos1.y=GetTerrainGroundPoint (&pos1);
                        pos1+=((TerrainNormals[MAX_TERRAIN_LOD-1][tseg].normal1)/16);

                        pos2.x=(t*TERRAIN_SIZE)+(TERRAIN_SIZE * .66);
                        pos2.z=(i*TERRAIN_SIZE)+(TERRAIN_SIZE/3);
                        pos2.y=GetTerrainGroundPoint (&pos2);
                        pos2+=((TerrainNormals[MAX_TERRAIN_LOD-1][tseg].normal2)/16);

                        for (j=0;j<Terrain_sky.num_satellites;j++)
                        {
                                raynum++;
                                mprintf_at(2,4,0,"Ray=%d      ",raynum);

                                int answer1,answer2;
                                answer1=ShootRayForTerrainLight (&pos1,&Terrain_sky.satellite_vectors[j],tseg);
                                answer2=ShootRayForTerrainLight (&pos2,&Terrain_sky.satellite_vectors[j],tseg);

                                if (answer1==0 && answer2==0)
                                        continue;

                                float r=exitance[tseg].r;
                                float g=exitance[tseg].g;
                                float b=exitance[tseg].b;
                                int tmap=Terrain_sky.satellite_texture[j];

                                float light1,light2,light_avg;
                                vector tnorm1=TerrainNormals[MAX_TERRAIN_LOD-1][tseg].normal1;
                                vector tnorm2=TerrainNormals[MAX_TERRAIN_LOD-1][tseg].normal2;

                                vector normal;

                                vm_GetNormalizedDir (&normal,&Terrain_sky.satellite_vectors[j],&pos1);
                                light1=answer1*(vm_DotProduct (&normal,&tnorm1));
                                if (light1<0)
                                        light1=0;

                                vm_GetNormalizedDir (&normal,&Terrain_sky.satellite_vectors[j],&pos2);
                                light2=answer2*(vm_DotProduct (&normal,&tnorm2));
                                if (light2<0)
                                        light2=0;

                                light_avg=(light1+light2)/2;

                                r+=(light_avg*GameTextures[tmap].r);
                                g+=(light_avg*GameTextures[tmap].g);
                                b+=(light_avg*GameTextures[tmap].b);

                                exitance[tseg].r=r;
                                exitance[tseg].g=g;
                                exitance[tseg].b=b;
                        }
                }
        }

        // Clip to 1.0
        for (i=0;i<TERRAIN_DEPTH*TERRAIN_WIDTH;i++)
        {
                exitance[i].r=std::min(exitance[i].r,1.0f);
                exitance[i].g=std::min(exitance[i].g,1.0f);
                exitance[i].b=std::min(exitance[i].b,1.0f);
        }


        // Now average the surrounding cells to get a 'smooth' shadow effect
        for (i=0;i<TERRAIN_DEPTH;i++)
        {
                for (t=0;t<TERRAIN_WIDTH;t++)
                {
                        int tseg=i*TERRAIN_WIDTH+t;
                        spectra total={0,0,0};
                        int num=0;

                        AddSpectra (&total,&total,&exitance[tseg]);
                        num++;

                        if (i!=0)
                        {
                                AddSpectra (&total,&total,&exitance[(i-1)*TERRAIN_WIDTH+t]);
                                num++;
                                if (t!=0)
                                {
                                        AddSpectra (&total,&total,&exitance[(i-1)*TERRAIN_WIDTH+(t-1)]);
                                        num++;
                                }

                        }
                        if (t!=0)
                        {
                                AddSpectra (&total,&total,&exitance[i*TERRAIN_WIDTH+(t-1)]);
                                num++;
                        }

                        total.r/=num;
                        total.g/=num;
                        total.b/=num;

                        Terrain_seg[tseg].r=total.r*255;
                        Terrain_seg[tseg].g=total.g*255;
                        Terrain_seg[tseg].b=total.b*255;
                        Terrain_seg[tseg].l=((total.r+total.g+total.b)*255)/3;
                }
        }

        free (exitance);

        if (do_dynamic)
                DoTerrainDynamicTable();

        UpdateTerrainLightmaps();
        OutrageMessageBox ("Terrain radiosity complete!\nIt is recommended you save the level so you won't have to rerun
this operation.");

}*/

void BuildLightmapUVs(int *room_list, int *face_list, int count, vector *lightmap_poly, int nv, int external) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE * 5];
  vector facevert;
  vector rot_vert;
  int i, t;
  int lmi_handle;

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  for (i = 0; i < nv; i++)
    avg_vert += lightmap_poly[i];

  avg_vert /= nv;

  // Make the orientation matrix
  // Reverse the normal because we're looking "at" the face, not from it
  fvec = -Rooms[room_list[0]].faces[face_list[0]].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < nv; i++) {
    vector vert = lightmap_poly[i];

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find left most point
  int leftmost_point = -1;
  float leftmost_x = 900000.00f; // a big number

  for (i = 0; i < nv; i++) {
    if (verts[i].x < leftmost_x) {
      leftmost_point = i;
      leftmost_x = verts[i].x;
    }
  }

  ASSERT(leftmost_point != -1);

  // Find top most point
  int topmost_point = -1;
  float topmost_y = -900000.0f; // a big number

  for (i = 0; i < nv; i++) {
    if (verts[i].y > topmost_y) {
      topmost_point = i;
      topmost_y = verts[i].y;
    }
  }

  ASSERT(topmost_point != -1);

  // Find right most point
  int rightmost_point = -1;
  float rightmost_x = -900000.00f; // a big number

  for (i = 0; i < nv; i++) {
    if (verts[i].x > rightmost_x) {
      rightmost_point = i;
      rightmost_x = verts[i].x;
    }
  }

  ASSERT(rightmost_point != -1);

  // Find bottom most point
  int bottommost_point = -1;
  float bottommost_y = 900000.0f; // a big number

  for (i = 0; i < nv; i++) {
    if (verts[i].y < bottommost_y) {
      bottommost_point = i;
      bottommost_y = verts[i].y;
    }
  }

  ASSERT(bottommost_point != -1);

  // now set the base vertex, which is where we base uv 0,0 on

  vector base_vector;

  base_vector.x = verts[leftmost_point].x;
  base_vector.y = verts[topmost_point].y;
  base_vector.z = 0;

  // Figure out lightmap resolution
  float xdiff = verts[rightmost_point].x - verts[leftmost_point].x;
  float ydiff = verts[topmost_point].y - verts[bottommost_point].y;
  float max_diff = (float)std::max(xdiff, ydiff);

  int lightmap_x_res = -1, lightmap_y_res = -1;
  float xspacing = LightSpacing;
  float yspacing = LightSpacing;
  float spacing = LightSpacing;
  int res, done_spacing = 0;
  int xspace_int, yspace_int;

  // If the default spacing would make us go over our lightmap resolution
  // limit, then increase the spacing and try again
  while (!done_spacing) {
    res = (xdiff / xspacing);
    if (((xdiff / xspacing) - res) > 0)
      res++;

    res++;

    if (res > 126)
      xspacing += 1;
    else
      done_spacing = 1;
  }

  // Set a mininum, at least
  if (res < 2)
    res = 2;

  lightmap_x_res = res;

  done_spacing = 0;
  while (!done_spacing) {
    res = (ydiff / yspacing);
    if (((ydiff / yspacing) - res) > 0)
      res++;

    res++;

    if (res > 126)
      yspacing += 1;
    else
      done_spacing = 1;
  }

  // Set a mininum, at least
  if (res < 2)
    res = 2;

  lightmap_y_res = res;

  /*// Find power of 2 number
  for (i=0;i<=7;i++)
  {
          int low_num=1<i;
          int hi_num=2<<i;
          if (res<=hi_num && res>low_num)
          {
                  lightmap_res=hi_num;
                  break;
          }
  }*/

  if (external)
    lmi_handle = AllocLightmapInfo(lightmap_x_res, lightmap_y_res, LMI_EXTERNAL_ROOM);
  else
    lmi_handle = AllocLightmapInfo(lightmap_x_res, lightmap_y_res, LMI_ROOM);

  ASSERT(lmi_handle != BAD_LMI_INDEX);
  ASSERT(lmi_handle >= 0 && lmi_handle <= MAX_LIGHTMAP_INFOS);
  Lightmaps_for_rad++;

  // Now do best fit spacing
  if (BestFit) {
    xspace_int = (xdiff / lightmap_x_res);
    if ((xdiff - (lightmap_x_res * xspace_int)) > 0)
      xspace_int++;

    yspace_int = (ydiff / lightmap_y_res);
    if ((ydiff - (lightmap_y_res * yspace_int)) > 0)
      yspace_int++;
  } else {
    xspace_int = xspacing;
    yspace_int = yspacing;
  }

  // Figure out lightmap uvs

  // Rotate all the face points
  for (i = 0; i < count; i++) {
    Rooms[room_list[i]].faces[face_list[i]].lmi_handle = lmi_handle;

    for (t = 0; t < Rooms[room_list[i]].faces[face_list[i]].num_verts; t++) {
      room *rp = &Rooms[room_list[i]];
      face *fp = &rp->faces[face_list[i]];
      vector vert = rp->verts[fp->face_verts[t]];

      vert -= avg_vert;
      vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

      facevert = rot_vert;

      // Find uv2s for this vertex
      fp->face_uvls[t].u2 = (facevert.x - verts[leftmost_point].x) / (float)(lightmap_x_res * xspace_int);
      fp->face_uvls[t].v2 = fabs((verts[topmost_point].y - facevert.y)) / (float)(lightmap_y_res * yspace_int);

      if (fp->face_uvls[t].u2 < 0)
        fp->face_uvls[t].u2 = 0;
      if (fp->face_uvls[t].v2 < 0)
        fp->face_uvls[t].v2 = 0;

      ASSERT(fp->face_uvls[t].u2 >= 0 && fp->face_uvls[t].u2 <= 1.0);
      ASSERT(fp->face_uvls[t].v2 >= 0 && fp->face_uvls[t].v2 <= 1.0);
    }
  }

  // Find upper left corner
  vm_TransposeMatrix(&trans_matrix);
  vm_MatrixMulVector(&rot_vert, &base_vector, &trans_matrix);
  LightmapInfo[lmi_handle].upper_left = rot_vert + avg_vert;

  LightmapInfo[lmi_handle].xspacing = xspace_int;
  LightmapInfo[lmi_handle].yspacing = yspace_int;
  LightmapInfo[lmi_handle].normal = Rooms[room_list[0]].faces[face_list[0]].normal;
  ScratchCenters[lmi_handle] = avg_vert;
}

#define MAX_COMBINES 50
#define LM_ADJACENT_FACE_THRESHOLD .999
uint8_t *RoomsAlreadyCombined[MAX_ROOMS];

/*
// Returns number of verts in dest if face a can be safely combined with face b
// Returns 0 if not
int CombineLightFaces( vector *dest_verts,vector *averts, int nva, vector *norma,vector *bverts, int nvb,vector
*normb,int aroom,int broom)
{
        int starta, startb, i;
        vector va;
        float dp;

        dp=vm_DotProduct (normb,norma);

        if (dp < LM_ADJACENT_FACE_THRESHOLD)
                return 0;

        ASSERT (nva > 2 );
        ASSERT (nvb > 2 );

        // Go through each vertex and get a match

        for (starta=0; starta<nva; starta++ )
        {
                int nexta=(starta+1)%nva;

                for (startb=0; startb<nvb; startb++ )
                {
                        int nextb=(startb+1)%nvb;

                        if ((PointsAreSame (&averts[starta],&bverts[nextb])) &&
                                  (PointsAreSame(&averts[nexta],&bverts[startb])))
                        {
                                //MATCH!!!!!!!!

                                int dnv = 0;

                                for (i=1; i<nva; i++ )
                                {
                                        ASSERT(dnv < MAX_VERTS_PER_FACE*5);
                                        dest_verts[dnv] = averts[(starta+i)%nva];
                                        va = dest_verts[dnv];
                                        dnv++;
                                }

                                if ( (PointsAreSame(&va,&bverts[(startb+2)%nvb])))
                                        mprintf(0, "WARNING!!! Faces were combined that caused the loss of a
vertex!\n");

                                for (i=1; i<nvb; i++ )
                                {
                                        ASSERT(dnv < MAX_VERTS_PER_FACE*5 );
                                        if ( (i==1) && (PointsAreSame(&va,&bverts[(startb+i+1)%nvb])))
                                                continue;
                                        else if ( (i==2) && (PointsAreSame(&va,&bverts[(startb+i)%nvb])))
                                                continue;
                                        else
                                        {
                                                dest_verts[dnv] = bverts[(startb+i)%nvb];
                                                dnv++;

                                        }
                                }
                                ASSERT( dnv > 2 );

                                return dnv;
                        }
                }
        }

         Now check for tjoint faces
        for (starta=0; starta<nva; starta++)
        {
                int nexta=(starta+1)%nva;

                for (startb=0; startb<nvb; startb++)
                {
                        vector line_a=averts[nexta]-averts[starta];



                }
        }

        // If these two faces are in the same room and are on the same plane
        // then we should combine them by default

        if (aroom!=-1 && aroom==broom)
        {
                int dnv = 0;
                int match=0;

                // Test to see if any points at all can touch

                for (i=0; i<nva && !match; i++ )
                {
                        for (int t=0; t<nvb && !match; t++ )
                        {
                                if (PointsAreSame(&averts[i],&bverts[t]))
                                        match=1;
                        }
                }

                if (!match)
                        return 0;

                // At least one point is the same, so combine them!
                for (i=0; i<nva; i++ )
                {
                        dest_verts[dnv] = averts[i];
                        dnv++;
                        ASSERT(dnv < MAX_VERTS_PER_FACE * 5);
                }

                for (i=0; i<nvb; i++ )
                {
                        dest_verts[dnv] = bverts[i];
                        dnv++;
                        ASSERT(dnv < MAX_VERTS_PER_FACE * 5);
                }

                return dnv;
        }

        return 0;
}*/

// Returns number of verts in dest if face a can be safely combined with face b
// Returns 0 if not
int CombineLightFaces(vector *dest_verts, vector *averts, int nva, vector *norma, vector *bverts, int nvb,
                      vector *normb, int aroom, int broom) {
  int i;

  float dp;

  dp = vm_DotProduct(normb, norma);

  if (dp < LM_ADJACENT_FACE_THRESHOLD)
    return 0;

  ASSERT(nva > 2);
  ASSERT(nvb > 2);

  // Go through each vertex and get a match

  // If these two faces are in the same room and are on the same plane
  // then we should combine them by default

  if (1 || (aroom != -1 && aroom == broom)) {
    int dnv = 0;
    int match = 0;

    // Don't go over our point limit
    if ((nva + nvb) >= (MAX_VERTS_PER_FACE * 5))
      return 0;

    // Test to see if any points at all can touch

    for (i = 0; i < nva && !match; i++) {
      for (int t = 0; t < nvb && !match; t++) {
        if (PointsAreSame(&averts[i], &bverts[t]))
          match = 1;
      }
    }

    if (!match)
      return 0;

    // At least one point is the same, so combine them!
    for (i = 0; i < nva; i++) {
      dest_verts[dnv] = averts[i];
      dnv++;
      ASSERT(dnv < MAX_VERTS_PER_FACE * 5);
    }

    for (i = 0; i < nvb; i++) {
      dest_verts[dnv] = bverts[i];
      dnv++;
      ASSERT(dnv < MAX_VERTS_PER_FACE * 5);
    }

    return dnv;
  }

  return 0;
}

// Given a roomnumber and a face, goes through the entire mine and checks to see
// if this face can share a lightmap with any other face
int TestLightAdjacency(int roomnum, int facenum, int external) {

  int i, t, k;
  room *arp = &Rooms[roomnum];
  face *afp = &arp->faces[facenum];

  vector averts[MAX_VERTS_PER_FACE * 5];
  vector bverts[MAX_VERTS_PER_FACE * 5];
  vector dest_verts[MAX_VERTS_PER_FACE * 5];

  int face_combine_list[MAX_COMBINES];
  int room_combine_list[MAX_COMBINES];

  ASSERT(roomnum >= 0 && roomnum < MAX_ROOMS);

  if (!AllowCombining)
    return 0;

  // if (GameTextures[afp->tmap].r>0 || GameTextures[afp->tmap].g>0 || GameTextures[afp->tmap].b>0)
  //	return 0;

  // Don't combine portals!
  if (afp->portal_num != -1)
    return 0;

  // Setup our 'base' face

  int anv = afp->num_verts;
  int total_faces = 1;

  room_combine_list[0] = roomnum;
  face_combine_list[0] = facenum;

  for (i = 0; i < afp->num_verts; i++)
    averts[i] = arp->verts[afp->face_verts[i]];

StartOver:

  // Go through each room and find an adjacent face
  for (i = roomnum; i < MAX_ROOMS; i++) {
    if (!Rooms[i].used)
      continue;

    if (Rooms[i].flags & RF_NO_LIGHT)
      continue;

    if (external && !(Rooms[i].flags & RF_EXTERNAL))
      continue;

    if (!external && (Rooms[i].flags & RF_EXTERNAL))
      continue;

    /*if (i!=roomnum) // Only combine faces in the same room
            continue;*/

    for (t = 0; t < Rooms[i].num_faces; t++) {
      if (total_faces >= MAX_COMBINES - 1)
        continue;

      if (&Rooms[i] == arp && t == facenum)
        continue; // don't do self

      // Don't do if already spoken fore
      if (RoomsAlreadyCombined[i][t])
        continue;

      room *brp = &Rooms[i];
      face *bfp = &brp->faces[t];

      // Don't do combine light sources
      // if (GameTextures[bfp->tmap].r>0 || GameTextures[bfp->tmap].g>0 || GameTextures[bfp->tmap].b>0)
      //	continue;
      // Don't combine portals!
      if (bfp->portal_num != -1)
        continue;

      for (k = 0; k < bfp->num_verts; k++)
        bverts[k] = brp->verts[bfp->face_verts[k]];

      int nv =
          CombineLightFaces(dest_verts, averts, anv, &afp->normal, bverts, bfp->num_verts, &bfp->normal, roomnum, i);

      // We have a combine!  Mark this face in the appropriate list
      // And update our new polygon
      if (nv > 0) {
        room_combine_list[total_faces] = i;
        face_combine_list[total_faces] = t;
        total_faces++;

        RoomsAlreadyCombined[roomnum][facenum] = 1;
        RoomsAlreadyCombined[i][t] = 1;
        for (k = 0; k < nv; k++)
          averts[k] = dest_verts[k];

        anv = nv;

        goto StartOver;
      }
    }
  }

  // Now build 1 lightmap to be shared across all the faces that were combined
  if (total_faces > 1) {
    BuildLightmapUVs(room_combine_list, face_combine_list, total_faces, averts, anv, external);
  }

  return 1;
}

// Computes the the mines UVs
// Faces can now share one lightmap, so this routine goes through and tries to
// combine as many faces as it can into one lightmap
void ComputeAllRoomLightmapUVs(int external) {
  int i, t, k;
  int not_combined = 0;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      if (external && !(Rooms[i].flags & RF_EXTERNAL))
        continue;

      if (!external && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      RoomsAlreadyCombined[i] = (uint8_t *)mem_malloc(Rooms[i].num_faces);
      ASSERT(RoomsAlreadyCombined[i]);
      for (k = 0; k < Rooms[i].num_faces; k++)
        RoomsAlreadyCombined[i][k] = 0;
    }
  }

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      if (external && !(Rooms[i].flags & RF_EXTERNAL))
        continue;

      if (!external && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      for (t = 0; t < Rooms[i].num_faces; t++) {
        if (*(RoomsAlreadyCombined[i] + t) == 0)
          TestLightAdjacency(i, t, external);
      }
    }
  }

  // Now build lightmaps for any faces that couldn't be combined
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      if (external && !(Rooms[i].flags & RF_EXTERNAL))
        continue;

      if (!external && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      for (t = 0; t < Rooms[i].num_faces; t++) {
        if (!RoomsAlreadyCombined[i][t]) {
          vector verts[MAX_VERTS_PER_FACE * 5];
          int room_list[2], face_list[2];
          for (k = 0; k < Rooms[i].faces[t].num_verts; k++)
            verts[k] = Rooms[i].verts[Rooms[i].faces[t].face_verts[k]];

          room_list[0] = i;
          face_list[0] = t;

          BuildLightmapUVs(room_list, face_list, 1, verts, Rooms[i].faces[t].num_verts, external);
          not_combined++;
        }
      }
    }
  }

  mprintf(0, "%d faces couldn't be combined!\n", not_combined);

  // Free memory
  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      if (external && !(Rooms[i].flags & RF_EXTERNAL))
        continue;

      if (!external && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      mem_free(RoomsAlreadyCombined[i]);
    }
  }
}

//	Returns number preceding val modulo modulus.
//	prevmod(3,4) = 2
//	prevmod(0,4) = 3
int SpecularPrevIndex(int val, int modulus) {
  if (val > 0)
    return val - 1;
  else
    return modulus - 1;
}

//	Returns number succeeding val modulo modulus.
//	succmod(3,4) = 0
//	succmod(0,4) = 1
int SpecularNextIndex(int val, int modulus) {
  if (val < modulus - 1)
    return val + 1;
  else
    return 0;
}

// Gets the left top, left bottom, right top, and right bottom indices.  Also finds
// lowest y index.
void GetSpecularVertexOrdering(spec_vertex *verts, int nv, int *vlt, int *vlb, int *vrt, int *vrb, int *bottom_y_ind) {
  int i;
  float min_y, max_y;
  int min_y_ind;
  int original_vrt;
  float min_x;

  // Scan all vertices, set min_y_ind to vertex with smallest y coordinate.
  min_y = verts[0].y;
  max_y = min_y;
  min_y_ind = 0;
  min_x = verts[0].x;
  *bottom_y_ind = 0;

  for (i = 1; i < nv; i++) {
    if (verts[i].y < min_y) {
      min_y = verts[i].y;
      min_y_ind = i;
      min_x = verts[i].x;
    } else if (verts[i].y == min_y) {
      if (verts[i].x < min_x) {
        min_y_ind = i;
        min_x = verts[i].x;
      }
    }
    if (verts[i].y > max_y) {
      max_y = verts[i].y;
      *bottom_y_ind = i;
    }
  }

  // Set "vertex left top", etc. based on vertex with topmost y coordinate
  *vlt = min_y_ind;
  *vrt = *vlt;
  *vlb = SpecularPrevIndex(*vlt, nv);
  *vrb = SpecularNextIndex(*vrt, nv);

  // If right edge is horizontal, then advance along polygon bound until it no longer is or until all
  // vertices have been examined.
  // (Left edge cannot be horizontal, because *vlt is set to leftmost point with highest y coordinate.)

  original_vrt = *vrt;

  while (verts[*vrt].y == verts[*vrb].y) {
    if (SpecularNextIndex(*vrt, nv) == original_vrt)
      break;

    *vrt = SpecularNextIndex(*vrt, nv);
    *vrb = SpecularNextIndex(*vrt, nv);
  }
}

/*
// Creates a map that contains all the interpolated normals for a particular face
// Used in specular mapping
void CreateNormalMapForFace (room *rp,face *fp)
{
        int w=lmi_w(fp->lmi_handle);
        int h=lmi_h(fp->lmi_handle);
        special_face *sfp=&SpecialFaces[fp->special_handle];
        spec_vertex spec_verts[MAX_VERTS_PER_FACE];
        vector vertnorms[MAX_VERTS_PER_FACE];
        int vlt,vlb,vrt,vrb,max_y_vertex,top_y,bottom_y,height;
        int no_height=0,no_width=0,no_right=0,no_left=0;
        lightmap_info *lmi_ptr=&LightmapInfo[fp->lmi_handle];
        uint16_t *src_data=lm_data(lmi_ptr->lm_handle);

        matrix facematrix;
        vector fvec=-lmi_ptr->normal;
        vm_VectorToMatrix(&facematrix,&fvec,NULL,NULL);

        sfp->normal_map=(uint8_t *)mem_malloc (w*h*3);
        ASSERT (sfp->normal_map);

        for (int i=0;i<(w*h);i++)
        {
                sfp->normal_map[i*3+0]=0;
                sfp->normal_map[i*3+1]=0;
                sfp->normal_map[i*3+2]=128;
        }

        for (i=0;i<fp->num_verts;i++)
        {
                vm_MatrixMulVector (&vertnorms[i],&sfp->vertnorms[i],&facematrix);
                spec_verts[i].x=fp->face_uvls[i].u2;
                spec_verts[i].y=fp->face_uvls[i].v2;
        }

        GetSpecularVertexOrdering(spec_verts,fp->num_verts,&vlt,&vlb,&vrt,&vrb,&max_y_vertex);

        top_y=spec_verts[vlt].y*h;
        bottom_y=spec_verts[max_y_vertex].y*h;

        height = bottom_y-top_y;
   if(height == 0)
                no_height=1;

        // Setup left interpolant
        int left_height=((spec_verts[vlb].y-spec_verts[vlt].y)*(float)h);

        float left_x=spec_verts[vlt].x*w;
        float delta_left_x=((spec_verts[vlb].x-spec_verts[vlt].x)*w)/left_height;
        vector left_vnorm=vertnorms[vlt];
        vector delta_left_vnorm=(vertnorms[vlb]-vertnorms[vlt])/left_height;
        int next_break_left = spec_verts[vlb].y*h;

        // Setup right interpolant

        int right_height=((spec_verts[vrb].y-spec_verts[vrt].y)*(float)h);

        float right_x=spec_verts[vrt].x*w;
        float delta_right_x=((spec_verts[vrb].x-spec_verts[vrt].x)*w)/right_height;
        vector right_vnorm=vertnorms[vrt];
        vector delta_right_vnorm=(vertnorms[vrb]-vertnorms[vrt])/right_height;
        int next_break_right = spec_verts[vrb].y*h;

        // Do the loop
        for (int y=top_y;y<=bottom_y;y++)
        {
                if (y==next_break_left && !no_height)
                {
                        while (y == (int)(spec_verts[vlb].y*h))
                        {
                                vlt = vlb;
                                vlb = SpecularPrevIndex(vlb,fp->num_verts);
                        }

                        // Setup left interpolant
                        left_height=((spec_verts[vlb].y-spec_verts[vlt].y)*(float)h);
                        left_x=spec_verts[vlt].x*w;
                        delta_left_x=((spec_verts[vlb].x-spec_verts[vlt].x)*w)/left_height;
                        left_vnorm=vertnorms[vlt];
                        delta_left_vnorm=(vertnorms[vlb]-vertnorms[vlt])/left_height;
                        next_break_left = spec_verts[vlb].y*h;

                }

                if (y==next_break_right && !no_height)
                {
                        while (y == (int)(spec_verts[vrb].y*h))
                        {
                                vrt = vrb;
                                vrb = SpecularNextIndex(vrb,fp->num_verts);
                        }
                        right_height=((spec_verts[vrb].y-spec_verts[vrt].y)*(float)h);
                        right_x=spec_verts[vrt].x*w;
                        delta_right_x=((spec_verts[vrb].x-spec_verts[vrt].x)*w)/right_height;
                        right_vnorm=vertnorms[vrt];
                        delta_right_vnorm=(vertnorms[vrb]-vertnorms[vrt])/right_height;
                        next_break_right = spec_verts[vrb].y*h;
                }

                int width=(right_x-left_x)+1;

                vector delta_vnorm=(right_vnorm-left_vnorm)/width;
                vector vnorm=left_vnorm;

                for (i=left_x;i<(left_x+width);i++)
                {
                        int offset=y*w+i;

                        if (!(src_data[offset] & OPAQUE_FLAG))
                                continue;

                        sfp->normal_map[(offset*3)+0]=((vnorm.x+1.0)/2.0)*255.0;
                        sfp->normal_map[(offset*3)+1]=((vnorm.y+1.0)/2.0)*255.0;
                        sfp->normal_map[(offset*3)+2]=((vnorm.z+1.0)/2.0)*255.0;
                        vnorm+=delta_vnorm;
                }

                // Update our interpolants
                left_x += delta_left_x;
                right_x += delta_right_x;
                right_vnorm+=delta_right_vnorm;
                left_vnorm+=delta_left_vnorm;
        }
}*/

// Frees memory for specular lighting
void CleanupSpecularLighting(int external) {
  int i, t;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      if ((Rooms[i].flags & RF_EXTERNAL) && !external)
        continue;

      if (!(Rooms[i].flags & RF_EXTERNAL) && external)
        continue;

      room *rp = &Rooms[i];

      for (t = 0; t < 4; t++) {
        mem_free(Room_strongest_value[i][t]);
      }

      for (t = 0; t < rp->num_faces; t++) {
        face *fp = &rp->faces[t];
        if (GameTextures[fp->tmap].flags & TF_SPECULAR) {
          ASSERT(fp->special_handle != BAD_SPECIAL_FACE_INDEX);
          int j, k, l;

          if (SpecialFaces[fp->special_handle].spec_instance[0].bright_color == 0) {
            // This face didn't get enough light, either free it up or
            // find another face that shares a lightmap and just use that
            // faces values

            int found = 0;
            float strongest_light = 0;
            face *best_face;

            for (l = 0; l < fp->num_verts; l++) {
              int vert_to_check = fp->face_verts[l];
              for (j = 0; j < rp->num_faces; j++) {
                face *this_fp = &rp->faces[j];

                if (this_fp == fp)
                  continue; // don't do self
                if (this_fp->lmi_handle != fp->lmi_handle)
                  continue; // only do faces that have same lightmaps

                if (this_fp->special_handle == BAD_SPECIAL_FACE_INDEX)
                  continue; // Only do specmaps

                if (SpecialFaces[this_fp->special_handle].spec_instance[0].bright_color == 0)
                  continue; // Don't do dark ones

                if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR)
                  continue; // Don't do smooth shades

                for (k = 0; k < this_fp->num_verts; k++) {
                  if (vert_to_check == this_fp->face_verts[k]) {
                    // We have a match, so see if this face is brighter
                    // than all the others
                    int color = SpecialFaces[this_fp->special_handle].spec_instance[0].bright_color;
                    int r = (color >> 10) & 0x1f;
                    int g = (color >> 5) & 0x1f;
                    int b = (color & 0x1f);
                    float sr = (float)r / 31.0;
                    float sg = (float)g / 31.0;
                    float sb = (float)b / 31.0;

                    float mono_color = (sr * .3) + (sg * .59) + (sb * .11);
                    if (mono_color > strongest_light) {
                      strongest_light = mono_color;
                      found = 1;
                      best_face = this_fp;
                    }
                  }
                }
              }
            }
            // If after all that searching we couldn't find a good light, free it!
            if (!found) {
              FreeSpecialFace(fp->special_handle);
              fp->special_handle = BAD_SPECIAL_FACE_INDEX;
            } else {
              for (int z = 0; z < 4; z++)
                SpecialFaces[fp->special_handle].spec_instance[z] =
                    SpecialFaces[best_face->special_handle].spec_instance[z];
            }
          }
        }
      }
    }
  }
}

// Sets up memory usage for specular lighting
void SetupSpecularLighting(int external) {
  int i, t;
  ClearAllRoomSpecmaps(external);

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (Rooms[i].flags & RF_NO_LIGHT)
        continue;

      if ((Rooms[i].flags & RF_EXTERNAL) && !external)
        continue;

      if (!(Rooms[i].flags & RF_EXTERNAL) && external)
        continue;

      room *rp = &Rooms[i];

      // Calculate vertex normals for this room
      vector *vertnorms = (vector *)mem_malloc(sizeof(vector) * rp->num_verts);
      ASSERT(vertnorms);
      for (t = 0; t < rp->num_verts; t++) {
        int total = 0;
        vector normal;
        vm_MakeZero(&normal);

        for (int k = 0; k < rp->num_faces; k++) {
          face *fp = &rp->faces[k];
          for (int j = 0; j < fp->num_verts; j++) {
            if (fp->face_verts[j] == t) {
              total++;
              normal += fp->normal;
            }
          }
        }

        if (total != 0)
          normal /= total;

        vertnorms[t] = normal;
      }

      for (t = 0; t < 4; t++) {
        Room_strongest_value[i][t] = (float *)mem_malloc(sizeof(float) * rp->num_faces);
        ASSERT(Room_strongest_value[i][t]);
        memset(Room_strongest_value[i][t], 0, sizeof(float) * rp->num_faces);
      }

      for (t = 0; t < rp->num_faces; t++) {
        face *fp = &rp->faces[t];
        if (GameTextures[fp->tmap].flags & TF_SPECULAR) {
          ASSERT(fp->special_handle == BAD_SPECIAL_FACE_INDEX);

          int n;
          if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR)
            n = AllocSpecialFace(SFT_SPECULAR, 4, true, fp->num_verts);
          else
            n = AllocSpecialFace(SFT_SPECULAR, 4);

          fp->special_handle = n;

          for (int k = 0; k < 4; k++) {
            SpecialFaces[n].spec_instance[k].bright_color = 0;
            vm_MakeZero(&SpecialFaces[n].spec_instance[k].bright_center);
          }

          // Get vertex normals for this punk
          if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) {
            for (k = 0; k < fp->num_verts; k++) {
              SpecialFaces[n].vertnorms[k] = vertnorms[fp->face_verts[k]];
            }
          }
        }
      }
      mem_free(vertnorms);
    }
  }
}

// Computes the the mines UVs
// Faces can now share one lightmap, so this routine goes through and tries to
// combine as many faces as it can into one lightmap
// Only works on one room
/*void ComputeSingleRoomLightmapUVs (int roomnum)
{
        int t,k;
        int not_combined=0;

        RoomsAlreadyCombined[roomnum]=(uint8_t *)mem_malloc (Rooms[roomnum].num_faces);
        ASSERT (RoomsAlreadyCombined[roomnum]);
        for (k=0;k<Rooms[roomnum].num_faces;k++)
                RoomsAlreadyCombined[roomnum][k]=0;


        for (t=0;t<Rooms[roomnum].num_faces;t++)
        {
                if (*(RoomsAlreadyCombined[roomnum]+t)==0)
                        TestLightAdjacency (roomnum,t,0);
        }

        for (t=0;t<Rooms[roomnum].num_faces;t++)
        {
                if (!RoomsAlreadyCombined[roomnum][t])
                {
                        vector verts[MAX_VERTS_PER_FACE];
                        int room_list[2],face_list[2];
                        for (k=0;k<Rooms[roomnum].faces[t].num_verts;k++)
                                verts[k]=Rooms[roomnum].verts[Rooms[roomnum].faces[t].face_verts[k]];

                        room_list[0]=i;
                        face_list[0]=t;

                        BuildLightmapUVs (room_list,face_list,1,verts,Rooms[roomnum].faces[t].num_verts,external);
                        not_combined++;
                }
        }

        mprintf(0,"%d faces couldn't be combined!\n",not_combined);

        // Free memory
        free (RoomsAlreadyCombined[roomnum]);
}*/
