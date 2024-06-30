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

 * $Logfile: /DescentIII/Main/model/newstyle.cpp $
 * $Revision: 122 $
 * $Date: 3/20/00 12:28p $
 * $Author: Matt $
 *
 * Polygon model code
 *
 * $Log: /DescentIII/Main/model/newstyle.cpp $
 *
 * 122   3/20/00 12:28p Matt
 * Merge of Duane's post-1.3 changes.
 * Check for NULL pointer.
 *
 * 121   7/08/99 5:47p Jason
 * changes for new bumpmapping system in 1.1 update patch
 *
 * 120   6/08/99 1:00p Jason
 * changes for bumpmapping
 *
 * 119   5/18/99 10:31a Jason
 * polymodel stuff wasn't getting paged in before drawing
 *
 * 118   5/14/99 2:03p Jason
 * added polymodel errors to catch bugs
 *
 * 117   5/14/99 12:02a Jason
 * more speedups for g3_DrawPoly
 *
 * 116   5/13/99 8:33p Matt
 * Consolidated Mac & Windows code.
 *
 * 115   5/13/99 5:07p Ardussi
 * changes for compiling on the Mac
 *
 * 114   5/04/99 4:34p Jason
 * changes for bumpmapping
 *
 * 113   4/22/99 8:29p Kevin
 * made psrand.h come after stdlib.h
 *
 * 112   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 111   4/16/99 5:32p Jason
 * fixed smooth specularity with objects
 *
 * 110   4/14/99 1:36a Jeff
 * fixed case mismatched #includes
 *
 * 109   4/09/99 12:06p Jason
 * made model setup code faster
 *
 * 108   3/31/99 12:26p Jason
 * fixed some issues related to non wbuffer cards
 *
 * 107   3/24/99 10:22a Matt
 * Fixed null-pointer bug
 *
 */

#include "pserror.h"
#include "pstypes.h"

#include "3d.h"
#include "vecmat.h"
#include "grdefs.h"
#include "polymodel.h"
#include "gametexture.h"
#include "byteswap.h"
#include "renderer.h"
#include "lighting.h"
#include "game.h"
#include "render.h"
#include "fireball.h"
#include "lightmap_info.h"
#include "lightmap.h"
#include "lighting.h"
#include "findintersection.h"

#include <stdlib.h>
#include <string.h>

#include "psrand.h"

static float face_depth[MAX_POLYGON_VECS];
static uint8_t triangulated_faces[MAX_FACES_PER_ROOM];

static uint8_t FacingPass = 0;
static int Multicolor_texture = -1;

static vector Fog_plane;
static float Fog_distance, Fog_eye_distance;
static vector Fog_view_pos, Specular_view_pos, Bump_view_pos;
static matrix Unscaled_bumpmap_matrix;

static int ModelFaceSortFunc(const int16_t *a, const int16_t *b);
static inline void RenderSubmodelFace(poly_model *pm, bsp_info *sm, int facenum);
static inline void RenderSubmodelLightmapFace(poly_model *pm, bsp_info *sm, int facenum);
static inline void RenderSubmodelFaceFogged(poly_model *pm, bsp_info *sm, int facenum);
static inline void RenderSubmodelFaceSpecular(poly_model *pm, bsp_info *sm, int facenum);

/// Draws a glowing cone of light.
static void DrawGlowEffect(vector *pos, float r, float g, float b, vector *norm, float size);

/// Draws a glowing cone of light that represents thrusters
static void DrawThrusterEffect(vector *pos, float r, float g, float b, vector *norm, float size, float length);

static void RenderSubmodelFacesSorted(poly_model *pm, bsp_info *sm);
static void RenderSubmodelFacesUnsorted(poly_model *pm, bsp_info *sm);

/// Rotates all of the points of a submodel, plus supplies color info.
static void RotateModelPoints(poly_model *pm, bsp_info *sm);

static float ComputeDefaultSizeFunc(int handle, float *size_ptr, vector *offset_ptr, bool f_use_all_frames);

int ModelFaceSortFunc(const int16_t *a, const int16_t *b) {
  float az, bz;

  az = face_depth[*a];
  bz = face_depth[*b];

  if (az < bz)
    return -1;
  else if (az > bz)
    return 1;
  else
    return 0;
}

#ifdef _DEBUG
static void model_draw_outline(int nverts, g3Point **pointlist) {
  int i;

  for (i = 0; i < nverts - 1; i++)
    g3_DrawLine(GR_RGB(255, 255, 255), pointlist[i], pointlist[i + 1]);

  g3_DrawLine(GR_RGB(255, 255, 255), pointlist[i], pointlist[0]);
}

static void DrawSubmodelFaceOutline(int nv, g3Point **pointlist) {
  int i;
  g3Point tpnt[64];
  g3Point *tpnt_list[64];

  ASSERT(nv < 64);

  for (i = 0; i < nv; i++) {
    tpnt[i] = *pointlist[i];
    tpnt_list[i] = &tpnt[i];
  }

  for (i = 0; i < nv - 1; i++)
    g3_DrawLine(GR_RGB(255, 255, 0), tpnt_list[i], tpnt_list[i + 1]);
  g3_DrawLine(GR_RGB(255, 255, 0), tpnt_list[i], tpnt_list[0]);
}
#endif

#define CROSS_WIDTH 8.0
int Lightmap_debug_subnum = -1;
int Lightmap_debug_facenum = -1;
int Lightmap_debug_model = -1;

inline void RenderSubmodelFace(poly_model *pm, bsp_info *sm, int facenum) {

  g3Point *pointlist[100];
  int bm_handle;
  int smooth = 0;
  polyface *fp = &sm->faces[facenum];
  int modelnum = sm - pm->submodel;
  texture *texp = NULL;
  int t;
  int custom = 0;
  g3Codes face_cc;
  int triface = 0;

  face_cc.cc_and = 0xff;
  face_cc.cc_or = 0;

  triangulated_faces[facenum] = 0;

  if (sm->flags & SOF_CUSTOM)
    custom = 1;

  // Setup texturing
  if (fp->texnum != -1)
    texp = &GameTextures[pm->textures[fp->texnum]];

  if (texp && custom && Polymodel_use_effect && (Polymodel_effect.type & PEF_CUSTOM_TEXTURE))
    texp = &GameTextures[Polymodel_effect.custom_texture];

  // Set radiosity lightmaps if needed
  if (Polymodel_light_type == POLYMODEL_LIGHTING_LIGHTMAP) {
    rend_SetOverlayMap(
        LightmapInfo[Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].lmi_handle].lm_handle);
  }

  // Do bump mapping
  if ((Polymodel_effect.type & PEF_BUMPMAPPED) && texp && texp->bumpmap != -1 &&
      Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD) {
    rend_SetOverlayType(OT_NONE);
    rend_SetBumpmapReadyState(1, texp->bumpmap);
    if ((GameTextures[fp->texnum].flags & TF_SMOOTH_SPECULAR))
      smooth = 1;
  }

  float uchange = 0, vchange = 0;

  // Figure out if there is any texture sliding
  if (texp && texp->slide_u != 0) {
    int int_time = Gametime / texp->slide_u;
    float norm_time = Gametime - (int_time * texp->slide_u);
    norm_time /= texp->slide_u;

    uchange = norm_time;
  }

  if (texp && texp->slide_v != 0) {
    int int_time = Gametime / texp->slide_v;
    float norm_time = Gametime - (int_time * texp->slide_v);
    norm_time /= texp->slide_v;
    vchange = norm_time;
  }

  ASSERT(fp->nverts < 100);

  // Setup the points for this face
  for (t = 0; t < fp->nverts; t++) {
    g3Point *p = &Robot_points[fp->vertnums[t]];
    pointlist[t] = p;

    if (texp) {
      p->p3_uvl.u = fp->u[t] + uchange;
      p->p3_uvl.v = fp->v[t] + vchange;
      p->p3_uvl.a = sm->alpha[fp->vertnums[t]];
      p->p3_flags |= PF_UV + PF_RGBA + PF_L;

      // Assign bump mapping coords
      if ((Polymodel_effect.type & PEF_BUMPMAPPED) && texp->bumpmap != -1 &&
          Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD) {
        p->p3_flags |= PF_UV2;

        vector vert = sm->verts[fp->vertnums[t]];

        vector vertnorm;

        if (smooth)
          vertnorm = sm->vertnorms[fp->vertnums[t]];
        else
          vertnorm = fp->normal;

        vector subvec = Bump_view_pos - vert;
        vm_NormalizeVectorFast(&subvec);

        vector incident_norm = vert - Polymodel_bump_pos;
        vm_NormalizeVectorFast(&incident_norm);

        float d = incident_norm * vertnorm;
        vector upvec = d * vertnorm;
        incident_norm -= (2 * upvec);

        float dotp = (subvec * incident_norm);

        if (dotp < 0)
          dotp = 0;
        if (dotp > 1)
          dotp = 1;

        float val = dotp * .5;

        p->p3_uvl.u2 = val;
        p->p3_uvl.v2 = val;
      }
    }

    if (Polymodel_light_type == POLYMODEL_LIGHTING_LIGHTMAP) {
      p->p3_flags |= PF_UV2;
      p->p3_uvl.u2 = Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].u2[t];
      p->p3_uvl.v2 = Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].v2[t];
    }

    face_cc.cc_or |= p->p3_codes;
    face_cc.cc_and &= p->p3_codes;
  }

  if (face_cc.cc_or && Polymodel_use_effect &&
      (Polymodel_effect.type & (PEF_FOGGED_MODEL | PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES))) {
    triface = 1;
    triangulated_faces[facenum] = 1;
  }

  // If there is a texture, set it up
  if (texp) {
    bm_handle = GetTextureBitmap(texp - std::data(GameTextures), 0);

    rend_SetTextureType(TT_LINEAR);
    if (Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD)
      rend_SetLighting(LS_GOURAUD);

    // If this is a light texture, make the texture full bright
    if (texp->flags & TF_LIGHT) {
      rend_SetLighting(LS_FLAT_GOURAUD);
      rend_SetFlatColor(GR_RGB(255, 255, 255));
    }

    // Setup custom color if there is one
    if (Polymodel_use_effect && (Polymodel_effect.type & PEF_CUSTOM_COLOR) &&
        (texp - std::data(GameTextures)) == Multicolor_texture) {
      int r, g, b;

      rend_SetLighting(LS_FLAT_GOURAUD);

      r = GR_COLOR_RED(Polymodel_effect.custom_color);
      g = GR_COLOR_GREEN(Polymodel_effect.custom_color);
      b = GR_COLOR_BLUE(Polymodel_effect.custom_color);

      if (Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD) {
        if (Polymodel_use_effect && Polymodel_effect.type & PEF_COLOR) {
          r = Polymodel_effect.r * (float)r * Polylighting_static_red;
          g = Polymodel_effect.g * (float)g * Polylighting_static_green;
          b = Polymodel_effect.b * (float)b * Polylighting_static_blue;
        } else {
          r = (float)r * Polylighting_static_red;
          g = (float)g * Polylighting_static_green;
          b = (float)b * Polylighting_static_blue;
        }
      }

      rend_SetFlatColor(GR_RGB(r, g, b));
    }

    if (Polymodel_use_effect && (Polymodel_effect.type & PEF_ALPHA))
      rend_SetAlphaValue(texp->alpha * Polymodel_effect.alpha * 255);
    else
      rend_SetAlphaValue(texp->alpha * 255);

    if (texp->flags & TF_SATURATE)
      rend_SetAlphaType(AT_SATURATE_CONSTANT_VERTEX);
    else {
      if ((texp->flags & TF_ALPHA) || (Polymodel_use_effect && (Polymodel_effect.type & PEF_ALPHA)))
        rend_SetAlphaType(ATF_CONSTANT + ATF_VERTEX);
      else
        rend_SetAlphaType(ATF_TEXTURE + ATF_VERTEX);
    }
  } else {
    rend_SetAlphaType(ATF_CONSTANT + ATF_VERTEX);
    if (Polymodel_use_effect && (Polymodel_effect.type & PEF_ALPHA))
      rend_SetAlphaValue(Polymodel_effect.alpha * 255);
    else
      rend_SetAlphaValue(255);

    rend_SetLighting(LS_NONE);
    rend_SetTextureType(TT_FLAT);

    int r, g, b;

    r = GR_COLOR_RED(fp->color);
    g = GR_COLOR_GREEN(fp->color);
    b = GR_COLOR_BLUE(fp->color);

    if (Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD) {
      if (Polymodel_use_effect && Polymodel_effect.type & PEF_COLOR) {
        r = Polymodel_effect.r * (float)r * Polylighting_static_red;
        g = Polymodel_effect.g * (float)g * Polylighting_static_green;
        b = Polymodel_effect.b * (float)b * Polylighting_static_blue;
      } else {
        r = (float)r * Polylighting_static_red;
        g = (float)g * Polylighting_static_green;
        b = (float)b * Polylighting_static_blue;
      }
    }

    rend_SetFlatColor(GR_RGB(r, g, b));

    bm_handle = 0;
  }

  if (triface)
    g3_SetTriangulationTest(1);

  g3_DrawPoly(fp->nverts, pointlist, bm_handle, MAP_TYPE_BITMAP, &face_cc);

  if (triface)
    g3_SetTriangulationTest(0);

  if (texp && (Polymodel_effect.type & PEF_BUMPMAPPED) && texp->bumpmap != -1 &&
      Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD) {
    rend_SetBumpmapReadyState(0, 0);
  }

#ifdef _DEBUG
  if (Polymodel_outline_mode)
    DrawSubmodelFaceOutline(fp->nverts, pointlist);

    /*	if (Lightmap_debug_model==(pm-Poly_models) && Polymodel_light_type==POLYMODEL_LIGHTING_LIGHTMAP &&
       Lightmap_debug_subnum==modelnum && Lightmap_debug_facenum==facenum)
            {

                    int lmi_handle=Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].lmi_handle;
                    lightmap_object_face *lfp=&Polylighting_lightmap_object->lightmap_faces[modelnum][facenum];
                    lightmap_info *lmi_ptr=&LightmapInfo[lmi_handle];
                    int w=lmi_w (lmi_handle);
                    int h=lmi_h (lmi_handle);
                    vector rvec=lfp->rvec*lmi_ptr->xspacing;
                    vector uvec=lfp->uvec*lmi_ptr->yspacing;
                    uint16_t *src_data=(uint16_t *)lm_data(lmi_ptr->lm_handle);

                    for (int i=0;i<w*h;i++)
                    {
                            int t;
                            g3Point epoints[20];
                            vector evec[20];
                            int y=i/w;
                            int x=i%w;

                            evec[0]=lmi_ptr->upper_left-(y*uvec)+(x*rvec);
                            g3_RotatePoint(&epoints[0],&evec[0]);
                            pointlist[0] = &epoints[0];

                            evec[1]=lmi_ptr->upper_left-(y*uvec)+((x+1)*rvec);
                            g3_RotatePoint(&epoints[1],&evec[1]);
                            pointlist[1] = &epoints[1];

                            evec[2]=lmi_ptr->upper_left-((y+1)*uvec)+((x+1)*rvec);
                            g3_RotatePoint(&epoints[2],&evec[2]);
                            pointlist[2] = &epoints[2];

                            evec[3]=lmi_ptr->upper_left-((y+1)*uvec)+(x*rvec);
                            g3_RotatePoint(&epoints[3],&evec[3]);
                            pointlist[3] = &epoints[3];

                            if (!(src_data[y*w+x] & OPAQUE_FLAG))
                            {
                                    for (t=0;t<4;t++)
                                            g3_DrawLine(GR_RGB(255,0,255),pointlist[t],pointlist[(t+1)%4]);
                            }
                            else
                            {
                                    for (t=0;t<4;t++)
                                            g3_DrawLine(GR_RGB(255,255,255),pointlist[t],pointlist[(t+1)%4]);
                            }
                    }

                    // Draw red cross where upper left is
                    uint8_t c0;
                    g3Point p0;
                    p0.p3_flags=0;
                    c0 = g3_RotatePoint(&p0,&LightmapInfo[lmi_handle].upper_left);

                    if (! c0)
                    {

                            //Draw a little cross at the current vert
                            g3_ProjectPoint(&p0);	  //make sure projected
                            rend_SetFlatColor(GR_RGB(255,0,0));
                            rend_DrawLine(p0.p3_sx-CROSS_WIDTH,p0.p3_sy,p0.p3_sx,p0.p3_sy-CROSS_WIDTH);
                            rend_DrawLine(p0.p3_sx,p0.p3_sy-CROSS_WIDTH,p0.p3_sx+CROSS_WIDTH,p0.p3_sy);
                            rend_DrawLine(p0.p3_sx+CROSS_WIDTH,p0.p3_sy,p0.p3_sx,p0.p3_sy+CROSS_WIDTH);
                            rend_DrawLine(p0.p3_sx,p0.p3_sy+CROSS_WIDTH,p0.p3_sx-CROSS_WIDTH,p0.p3_sy);
                    }

            }*/

#endif
}

inline void RenderSubmodelLightmapFace(poly_model *pm, bsp_info *sm, int facenum) {
  g3Point *pointlist[100];

  polyface *fp = &sm->faces[facenum];
  int modelnum = sm - pm->submodel;
  int t;

  int lm_handle = LightmapInfo[Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].lmi_handle].lm_handle;
  float xscalar = (float)GameLightmaps[lm_handle].width / (float)GameLightmaps[lm_handle].square_res;
  float yscalar = (float)GameLightmaps[lm_handle].height / (float)GameLightmaps[lm_handle].square_res;

  ASSERT(fp->nverts < 100);

  // Setup the points for this face
  for (t = 0; t < fp->nverts; t++) {
    g3Point *p = &Robot_points[fp->vertnums[t]];
    pointlist[t] = p;

    p->p3_uvl.u = Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].u2[t] * xscalar;
    p->p3_uvl.v = Polylighting_lightmap_object->lightmap_faces[modelnum][facenum].v2[t] * yscalar;
    p->p3_uvl.l = 1.0;

    p->p3_flags |= PF_UV2 + PF_RGBA + PF_L;
  }

  if (triangulated_faces[facenum])
    g3_SetTriangulationTest(1);

  g3_DrawPoly(fp->nverts, pointlist, lm_handle, MAP_TYPE_LIGHTMAP);

  if (triangulated_faces[facenum])
    g3_SetTriangulationTest(0);
}

inline void RenderSubmodelFaceFogged(poly_model *pm, bsp_info *sm, int facenum) {
  g3Point *pointlist[100];
  polyface *fp = &sm->faces[facenum];
  int modelnum = sm - pm->submodel;
  int t;

  for (t = 0; t < fp->nverts; t++) {
    g3Point *p = &Robot_points[fp->vertnums[t]];
    pointlist[t] = p;

    float mag;

    if (Polymodel_effect.fog_plane_check == 1) {
      mag = vm_DotProduct(&Fog_plane, &sm->verts[fp->vertnums[t]]) + Fog_distance;
    } else {
      vector *vec = &sm->verts[fp->vertnums[t]];

      // Now we must generate the split point. This is simply
      // an equation in the form Origin + t*Direction

      float dist = (*vec * Polymodel_fog_plane) + Fog_distance;

      vector subvec = *vec - Fog_view_pos;

      float t = Fog_eye_distance / (Fog_eye_distance - dist);
      vector portal_point = Fog_view_pos + (t * subvec);

      float eye_distance = -(vm_DotProduct(&Fog_plane, &portal_point));
      mag = vm_DotProduct(&Fog_plane, vec) + eye_distance;
    }

    float scalar = mag / Polymodel_effect.fog_depth;

    if (scalar > 1)
      scalar = 1;
    if (scalar < 0)
      scalar = 0;
    p->p3_a = scalar;

    p->p3_flags |= PF_RGBA;
  }

  if (triangulated_faces[facenum])
    g3_SetTriangulationTest(1);

  g3_DrawPoly(fp->nverts, pointlist, 0);

  if (triangulated_faces[facenum])
    g3_SetTriangulationTest(0);
}

inline void RenderSubmodelFaceSpecular(poly_model *pm, bsp_info *sm, int facenum) {
  g3Point *pointlist[100];
  polyface *fp = &sm->faces[facenum];
  int modelnum = sm - pm->submodel;
  int t;
  bool smooth = 0;

  if ((Polymodel_effect.type & PEF_SPECULAR_FACES) && (GameTextures[fp->texnum].flags & TF_SMOOTH_SPECULAR))
    smooth = 1;

  for (t = 0; t < fp->nverts; t++) {
    g3Point *p = &Robot_points[fp->vertnums[t]];
    vector vert = sm->verts[fp->vertnums[t]];

    vector vertnorm;

    if (smooth)
      vertnorm = sm->vertnorms[fp->vertnums[t]];
    else
      vertnorm = fp->normal;

    pointlist[t] = p;

    p->p3_flags |= PF_RGBA;
    p->p3_a = 0.0;

    vector subvec = Specular_view_pos - vert;
    vm_NormalizeVectorFast(&subvec);

    vector incident_norm = vert - Polymodel_specular_pos;
    vm_NormalizeVectorFast(&incident_norm);

    float d = incident_norm * vertnorm;
    vector upvec = d * vertnorm;
    incident_norm -= (2 * upvec);

    float dotp = subvec * incident_norm;

    if (dotp < 0)
      continue;
    if (dotp > 1)
      dotp = 1;

    if (dotp > 0) {
      int index = ((float)(MAX_SPECULAR_INCREMENTS - 1) * dotp);
      float val = Specular_tables[2][index];

      p->p3_a = val * Polymodel_effect.spec_scalar;
    }
  }

  if (triangulated_faces[facenum])
    g3_SetTriangulationTest(1);

  g3_DrawPoly(fp->nverts, pointlist, 0);

  if (triangulated_faces[facenum])
    g3_SetTriangulationTest(0);
}

#define MAX_PARTS 100

// Draws a glowing cone of light that represents thrusters
void DrawThrusterEffect(vector *pos, float r, float g, float b, vector *norm, float size, float length) {
  vector cur_pos = *pos;
  float cur_length = 0;
  vector glow_pos[MAX_PARTS];
  float glow_size[MAX_PARTS];
  int total_parts = 0;

  if (length < .1)
    return;

  int num_divs = length * 3;
  if (num_divs > MAX_PARTS)
    num_divs = MAX_PARTS;

  float size_change = size / num_divs;
  float pos_change = length / num_divs;

  if (!UseHardware)
    return; // No software stuff here!

  rend_SetZBufferWriteMask(0);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetAlphaValue(.3 * 255);

  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);

  ddgr_color color = GR_RGB(r * 255, g * 255, b * 255);
  int bm_handle = Fireballs[GRADIENT_BALL_INDEX].bm_handle;
  int t;

  // We must draw the small ones first, but we're starting the iteration from the
  // large one.  Consequently, we must store our variables so we can draw in reverse order
  for (t = 0; t < num_divs && size > .05; t++) {
    glow_pos[t] = cur_pos;
    glow_size[t] = size;

    size -= size_change;
    cur_pos += ((*norm) * pos_change);

    total_parts++;
  }

  for (t = total_parts - 1; t >= 0; t--) {
    rend_SetZBias(-glow_size[t]);
    g3_DrawBitmap(&glow_pos[t], glow_size[t], (glow_size[t] * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle,
                  color);
  }
  rend_SetZBias(0.0);
  rend_SetZBufferWriteMask(1);
}

// Draws a glowing cone of light
void DrawGlowEffect(vector *pos, float r, float g, float b, vector *norm, float size) {
  if (!UseHardware)
    return; // No software stuff here!

  if (Polymodel_use_effect && Polymodel_effect.type & PEF_NO_GLOWS)
    return;

  rend_SetZBufferWriteMask(0);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetAlphaValue(.8 * 255);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);

  ddgr_color color = GR_RGB(r * 255, g * 255, b * 255);
  int bm_handle = Fireballs[GRADIENT_BALL_INDEX].bm_handle;

  rend_SetZBias(-size);
  g3_DrawBitmap(pos, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle, color);

  rend_SetZBias(0.0);
  rend_SetZBufferWriteMask(1);
}

void RenderSubmodelFacesSorted(poly_model *pm, bsp_info *sm) {
  int i, t;

  int rcount;
  int model_render_order[MAX_POLYGON_VECS];
  int modelnum = sm - pm->submodel;

  ASSERT(sm->nverts < MAX_POLYGON_VECS);

  // Build list of visible (non-backfacing) faces, & compute average face depths
  for (i = rcount = 0; i < sm->num_faces; i++) {
    polyface *fp = &sm->faces[i];

    // check for visible face
    if (g3_CheckNormalFacing(&sm->verts[fp->vertnums[0]], &fp->normal)) {
      face_depth[i] = 0;
      for (t = 0; t < fp->nverts; t++)
        face_depth[i] += Robot_points[fp->vertnums[t]].p3_z;

      face_depth[i] /= fp->nverts;

      // initialize order list
      model_render_order[rcount] = i;

      rcount++;

      ASSERT(rcount < MAX_POLYGON_VECS);
    }
  }

  // Sort the faces
  qsort(model_render_order, rcount, sizeof(*model_render_order),
        (int (*)(const void *, const void *))ModelFaceSortFunc);

  for (i = rcount - 1; i >= 0; i--) {
    int facenum = model_render_order[i];

    RenderSubmodelFace(pm, sm, facenum);
  }
}
void RenderSubmodelFacesUnsorted(poly_model *pm, bsp_info *sm) {
  int i;
  int modelnum = sm - pm->submodel;
  int16_t alpha_faces[MAX_FACES_PER_ROOM], num_alpha_faces = 0;
  int rcount = 0;
  vector view_pos;

  g3_GetViewPosition(&view_pos);
  g3_GetUnscaledMatrix(&Unscaled_bumpmap_matrix);

  Specular_view_pos = view_pos;
  Bump_view_pos = view_pos;

  if (modelnum < 0 || modelnum >= pm->n_models) {
    Error("Got bad model number %d from polymodel %s!", modelnum, pm->name);
    return;
  }

  if (sm->flags & SOF_CUSTOM)
    rend_SetZBias(-.5);

  for (i = 0; i < sm->num_faces; i++) {
    vector tempv;
    polyface *fp = &sm->faces[i];
    texture *texp;

    // Check to see if this face even faces us!
    tempv = view_pos - sm->verts[fp->vertnums[0]];
    if ((tempv * fp->normal) < 0)
      continue;

    if (fp->texnum != -1) {
      texp = &GameTextures[pm->textures[fp->texnum]];

      if (texp->flags & TF_ALPHA || texp->flags & TF_SATURATE) {
        alpha_faces[num_alpha_faces++] = i;
        continue;
      }
    }

    if (StateLimited) {
      State_elements[rcount].facenum = i;
      State_elements[rcount].sort_key = pm->textures[fp->texnum];
      rcount++;
    } else
      RenderSubmodelFace(pm, sm, i);
  }

  if (StateLimited) {
    SortStates(State_elements, rcount);
    for (i = rcount - 1; i >= 0; i--) {
      int facenum = State_elements[i].facenum;
      RenderSubmodelFace(pm, sm, facenum);
    }

    if (!NoLightmaps) {
      if (!UseMultitexture && Polymodel_light_type == POLYMODEL_LIGHTING_LIGHTMAP) {
        rend_SetAlphaType(AT_LIGHTMAP_BLEND);
        rend_SetLighting(LS_GOURAUD);
        rend_SetColorModel(CM_MONO);
        rend_SetOverlayType(OT_NONE);
        rend_SetTextureType(TT_PERSPECTIVE);
        rend_SetWrapType(WT_CLAMP);
        rend_SetMipState(0);

        for (i = rcount - 1; i >= 0; i--) {
          int facenum = State_elements[i].facenum;
          RenderSubmodelLightmapFace(pm, sm, facenum);
        }

        rend_SetWrapType(WT_WRAP);
        rend_SetMipState(1);
      }
    }
  }

  // Now render all alpha faces
  // rend_SetZBufferWriteMask (0);
  for (i = 0; i < num_alpha_faces; i++)
    RenderSubmodelFace(pm, sm, alpha_faces[i]);
  // rend_SetZBufferWriteMask (1);

  if (sm->flags & SOF_CUSTOM)
    rend_SetZBias(0);

  // Draw specular faces if needed
  if (Polymodel_use_effect && Polymodel_effect.type & (PEF_SPECULAR_MODEL | PEF_SPECULAR_FACES)) {
    rend_SetOverlayType(OT_NONE);
    rend_SetTextureType(TT_FLAT);
    rend_SetLighting(LS_NONE);
    rend_SetColorModel(CM_MONO);
    rend_SetAlphaType(AT_SATURATE_VERTEX);
    rend_SetAlphaValue(255);
    rend_SetZBufferWriteMask(0);

    rend_SetFlatColor(GR_RGB((int)(Polymodel_effect.spec_r * 255.0), (int)(Polymodel_effect.spec_g * 255.0),
                             (int)(Polymodel_effect.spec_b * 255.0)));

    for (i = 0; i < sm->num_faces; i++) {
      polyface *fp = &sm->faces[i];

      if (!g3_CheckNormalFacing(&sm->verts[fp->vertnums[0]], &fp->normal))
        continue;

      /*	vector subvec=sm->verts[fp->vertnums[0]]-Polymodel_specular_pos;
              if ((fp->normal * subvec)> 0)
                      continue;*/

      if ((Polymodel_effect.type & PEF_SPECULAR_MODEL) ||
          (fp->texnum != -1 && GameTextures[pm->textures[fp->texnum]].flags & TF_SPECULAR))
        RenderSubmodelFaceSpecular(pm, sm, i);
    }

    rend_SetZBufferWriteMask(1);
  }

  // Draw fog if need be
  if (Polymodel_use_effect && Polymodel_effect.type & PEF_FOGGED_MODEL) {
    matrix mat;

    g3_GetUnscaledMatrix(&mat);
    g3_GetViewPosition(&Fog_view_pos);
    Fog_plane = mat.fvec;

    if (Polymodel_effect.fog_plane_check == 1)
      Fog_distance = -(vm_DotProduct(&Fog_plane, &Fog_view_pos));
    else {
      Fog_distance = -(vm_DotProduct(&Polymodel_fog_plane, &Polymodel_fog_portal_vert));
      Fog_eye_distance = (Fog_view_pos * Polymodel_fog_plane) + Fog_distance;
    }

    rend_SetOverlayType(OT_NONE);
    rend_SetTextureType(TT_FLAT);
    rend_SetLighting(LS_NONE);
    rend_SetColorModel(CM_MONO);
    rend_SetAlphaType(AT_VERTEX);
    rend_SetAlphaValue(255);
    rend_SetZBufferWriteMask(0);
    rend_SetCoplanarPolygonOffset(1);
    rend_SetFlatColor(GR_RGB((int)(Polymodel_effect.fog_r * 255.0), (int)(Polymodel_effect.fog_g * 255.0),
                             (int)(Polymodel_effect.fog_b * 255.0)));

    for (i = 0; i < sm->num_faces; i++) {
      polyface *fp = &sm->faces[i];

      if (!g3_CheckNormalFacing(&sm->verts[fp->vertnums[0]], &fp->normal))
        continue;

      RenderSubmodelFaceFogged(pm, sm, i);
    }

    rend_SetCoplanarPolygonOffset(0);
    rend_SetZBufferWriteMask(1);
  }
}

// Rotates all of the points of a submodel, plus supplies color info
void RotateModelPoints(poly_model *pm, bsp_info *sm) {

  // Figure out lighting
  if (Polymodel_light_type == POLYMODEL_LIGHTING_STATIC) {
    if ((Polymodel_use_effect && (Polymodel_effect.type & PEF_DEFORM)) || (sm->flags & SOF_JITTER)) {
      for (int i = 0; i < sm->nverts; i++) {
        vector vec = sm->verts[i];

        float val = ((ps_rand() % 1000) - 500.0) / 500.0;
        vec *= 1.0 + (Polymodel_effect.deform_range * val);

        g3_RotatePoint(&Robot_points[i], &vec);
      }
    } else {
      for (int i = 0; i < sm->nverts; i++)
        g3_RotatePoint(&Robot_points[i], &sm->verts[i]);
    }
  } else if (Polymodel_light_type == POLYMODEL_LIGHTING_LIGHTMAP) {
    if ((Polymodel_use_effect && (Polymodel_effect.type & PEF_DEFORM)) || (sm->flags & SOF_JITTER)) {
      for (int i = 0; i < sm->nverts; i++) {
        vector vec = sm->verts[i];
        float val = ((ps_rand() % 1000) - 500.0) / 500.0;
        vec *= 1.0 + (Polymodel_effect.deform_range * val);

        g3_RotatePoint(&Robot_points[i], &vec);

        Robot_points[i].p3_r = 1.0;
        Robot_points[i].p3_g = 1.0;
        Robot_points[i].p3_b = 1.0;
      }
    } else {
      for (int i = 0; i < sm->nverts; i++) {
        g3_RotatePoint(&Robot_points[i], &sm->verts[i]);
        Robot_points[i].p3_r = 1.0;
        Robot_points[i].p3_g = 1.0;
        Robot_points[i].p3_b = 1.0;
      }
    }
  } else if (Polymodel_light_type == POLYMODEL_LIGHTING_GOURAUD) {
    if (Polymodel_use_effect && Polymodel_effect.type & PEF_COLOR) {
      if ((Polymodel_use_effect && (Polymodel_effect.type & PEF_DEFORM)) || (sm->flags & SOF_JITTER)) {
        for (int i = 0; i < sm->nverts; i++) {
          vector vec = sm->verts[i];
          float val = ((ps_rand() % 1000) - 500.0) / 500.0;
          vec *= 1.0 + (Polymodel_effect.deform_range * val);

          g3_RotatePoint(&Robot_points[i], &vec);

          vector normvec = sm->vertnorms[i];
          val = (-vm_DotProduct(Polymodel_light_direction, &normvec) + 1.0) / 2;

          Robot_points[i].p3_r = Polymodel_effect.r * val * Polylighting_static_red;
          Robot_points[i].p3_g = Polymodel_effect.g * val * Polylighting_static_green;
          Robot_points[i].p3_b = Polymodel_effect.b * val * Polylighting_static_blue;
        }
      } else {
        if ((Polymodel_use_effect && (Polymodel_effect.type & PEF_DEFORM)) || (sm->flags & SOF_JITTER)) {
          for (int i = 0; i < sm->nverts; i++) {
            vector vec = sm->verts[i];
            float val = ((ps_rand() % 1000) - 500.0) / 500.0;
            vec *= 1.0 + (Polymodel_effect.deform_range * val);

            g3_RotatePoint(&Robot_points[i], &vec);

            vector normvec = sm->vertnorms[i];
            val = (-vm_DotProduct(Polymodel_light_direction, &normvec) + 1.0) / 2;

            Robot_points[i].p3_r = Polymodel_effect.r * val * Polylighting_static_red;
            Robot_points[i].p3_g = Polymodel_effect.g * val * Polylighting_static_green;
            Robot_points[i].p3_b = Polymodel_effect.b * val * Polylighting_static_blue;
          }
        } else {
          for (int i = 0; i < sm->nverts; i++) {
            g3_RotatePoint(&Robot_points[i], &sm->verts[i]);
            vector normvec = sm->vertnorms[i];
            float val = (-vm_DotProduct(Polymodel_light_direction, &normvec) + 1.0) / 2;

            Robot_points[i].p3_r = Polymodel_effect.r * val * Polylighting_static_red;
            Robot_points[i].p3_g = Polymodel_effect.g * val * Polylighting_static_green;
            Robot_points[i].p3_b = Polymodel_effect.b * val * Polylighting_static_blue;
          }
        }
      }
    } else {
      if ((Polymodel_use_effect && (Polymodel_effect.type & PEF_DEFORM)) || (sm->flags & SOF_JITTER)) {
        for (int i = 0; i < sm->nverts; i++) {
          vector vec = sm->verts[i];
          float val = ((ps_rand() % 1000) - 500.0) / 500.0;
          vec *= 1.0 + (Polymodel_effect.deform_range * val);

          g3_RotatePoint(&Robot_points[i], &vec);
          vector normvec = sm->vertnorms[i];
          val = (-vm_DotProduct(Polymodel_light_direction, &normvec) + 1.0) / 2;

          Robot_points[i].p3_r = val * Polylighting_static_red;
          Robot_points[i].p3_g = val * Polylighting_static_green;
          Robot_points[i].p3_b = val * Polylighting_static_blue;
        }
      } else {
        for (int i = 0; i < sm->nverts; i++) {
          g3_RotatePoint(&Robot_points[i], &sm->verts[i]);
          vector normvec = sm->vertnorms[i];
          float val = (-vm_DotProduct(Polymodel_light_direction, &normvec) + 1.0) / 2;

          Robot_points[i].p3_r = val * Polylighting_static_red;
          Robot_points[i].p3_g = val * Polylighting_static_green;
          Robot_points[i].p3_b = val * Polylighting_static_blue;
        }
      }
    }
  }

#ifndef RELEASE
  if (!UseHardware) {
    for (int i = 0; i < sm->nverts; i++)
      Robot_points[i].p3_l = Robot_points[i].p3_g;
    rend_SetColorModel(CM_MONO);
  }
#endif
}

void RenderSubmodel(poly_model *pm, bsp_info *sm, uint32_t f_render_sub) {
  int i;
  matrix lightmatrix;

  // Don't render door housings
  if (IsNonRenderableSubmodel(pm, sm - pm->submodel))
    return;

  if (Polymodel_light_type != POLYMODEL_LIGHTING_LIGHTMAP) {
    // Turn off bumpmapping if not needed
    rend_SetBumpmapReadyState(0, 0);
  } else {
    if (!StateLimited || UseMultitexture)
      rend_SetOverlayType(OT_BLEND);
  }

  if (Multicolor_texture == -1 && Polymodel_use_effect && (Polymodel_effect.type & PEF_CUSTOM_COLOR))
    Multicolor_texture = FindTextureName("MultiColor");

  rend_SetColorModel(CM_RGB);
  StartPolyModelPosInstance(&sm->mod_pos);
  vector temp_vec = sm->mod_pos + sm->offset;
  g3_StartInstanceAngles(&temp_vec, &sm->angs);

  vm_AnglesToMatrix(&lightmatrix, sm->angs.p, sm->angs.h, sm->angs.b);
  StartLightInstance(&temp_vec, &lightmatrix);

  // Check my bit to see if I get drawn
  if (f_render_sub & (0x00000001 << (sm - pm->submodel))) {
    if (sm->flags & SOF_CUSTOM) {
      if (!(Polymodel_effect.type & PEF_CUSTOM_TEXTURE))
        goto pop_lighting;
    }

    // Check to draw glow faces
    if (sm->flags & (SOF_GLOW | SOF_THRUSTER)) {
      if (!FacingPass)
        goto pop_lighting;

      vector zero_pos = {0, 0, 0};
      rend_SetOverlayType(OT_NONE);

      if (Polymodel_use_effect && Polymodel_effect.type & PEF_GLOW_SCALAR) {
        if (Polymodel_effect.type & PEF_CUSTOM_GLOW)
          DrawThrusterEffect(&zero_pos, Polymodel_effect.glow_r, Polymodel_effect.glow_g, Polymodel_effect.glow_b,
                             &sm->glow_info->normal, sm->glow_info->glow_size * Polymodel_effect.glow_size_scalar,
                             3 * Polymodel_effect.glow_length_scalar);
        else
          DrawThrusterEffect(&zero_pos, sm->glow_info->glow_r, sm->glow_info->glow_g, sm->glow_info->glow_b,
                             &sm->glow_info->normal, sm->glow_info->glow_size * Polymodel_effect.glow_size_scalar,
                             3 * Polymodel_effect.glow_length_scalar);
      } else {
        if (Polymodel_use_effect && Polymodel_effect.type & PEF_CUSTOM_GLOW)
          DrawGlowEffect(&zero_pos, Polymodel_effect.glow_r, Polymodel_effect.glow_g, Polymodel_effect.glow_b,
                         &sm->glow_info->normal, sm->glow_info->glow_size);
        else
          DrawGlowEffect(&zero_pos, sm->glow_info->glow_r, sm->glow_info->glow_g, sm->glow_info->glow_b,
                         &sm->glow_info->normal, sm->glow_info->glow_size);
      }

      goto pop_lighting;
    } else if (sm->flags & SOF_FACING) {
      if (!FacingPass)
        goto pop_lighting;

      vector pos;
      rend_SetLighting(LS_NONE);
      rend_SetColorModel(CM_MONO);
      rend_SetOverlayType(OT_NONE);

      int bm_handle = GetTextureBitmap(pm->textures[sm->faces[0].texnum], 0);
      rend_SetAlphaValue(GameTextures[pm->textures[sm->faces[0].texnum]].alpha * 255);

      vm_MakeZero(&pos);

      if (GameTextures[pm->textures[sm->faces[0].texnum]].flags & TF_SATURATE)
        rend_SetAlphaType(AT_SATURATE_TEXTURE);
      else
        rend_SetAlphaType(ATF_CONSTANT + ATF_TEXTURE);

      rend_SetZBufferWriteMask(0);
      g3_DrawBitmap(&pos, sm->rad, (sm->rad * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle);
      rend_SetZBufferWriteMask(1);

      goto pop_lighting;
    } else {
      if (FacingPass)
        goto pop_lighting;
    }

    RotateModelPoints(pm, sm);

    if (!UseHardware)
      RenderSubmodelFacesSorted(pm, sm);
    else
      RenderSubmodelFacesUnsorted(pm, sm);
  }

pop_lighting:

  for (i = 0; i < sm->num_children; i++) {
    RenderSubmodel(pm, &pm->submodel[sm->children[i]], f_render_sub);
  }

  g3_DoneInstance();
  DonePolyModelPosInstance();
  DoneLightInstance();
}

int RenderPolygonModel(poly_model *pm, uint32_t f_render_sub) {
  ASSERT(pm->new_style == 1);
  int i = 0;

  rend_SetAlphaType(ATF_CONSTANT + ATF_VERTEX);
  rend_SetWrapType(WT_WRAP);

  FacingPass = 0;
  for (i = 0; i < pm->n_models; i++) {
    bsp_info *sm = &pm->submodel[i];
    if (sm->parent == -1)
      RenderSubmodel(pm, sm, f_render_sub);
  }

  // Now render any facing submodels
  if (pm->flags & PMF_FACING) {
    // Don't render if we have it set for no glows
    FacingPass = 1;
    rend_SetOverlayType(OT_NONE);
    for (i = 0; i < pm->n_models; i++) {
      bsp_info *sm = &pm->submodel[i];
      if (sm->parent == -1)
        RenderSubmodel(pm, sm, f_render_sub);
    }
  }

  FacingPass = 0;

  return 1;
}

float ComputeDefaultSizeFunc(int handle, float *size_ptr, vector *offset_ptr, bool f_use_all_frames) {
  poly_model *pm;
  matrix m;
  float normalized_time[MAX_SUBOBJECTS];
  int model_index, sm_vert_index, frame_index;
  float cur_dist;
  float size = 0.0;
  int start_frame = 0;
  int end_frame = 0;

  vector geometric_center = Zero_vector;

  // Chris: Come see me when you are ready to deal with the paging problem - JL
  pm = GetPolymodelPointer(handle);

  ASSERT(start_frame <= end_frame);
  ASSERT(end_frame <= pm->frame_max);

  if (f_use_all_frames) {
    end_frame = pm->frame_max;
  }

  if (offset_ptr) {
    vector min_xyz;
    vector max_xyz;
    bool first_pnt = true;

    for (frame_index = start_frame; frame_index <= end_frame; frame_index++) {
      // Because size changes with animation, we need the worst case point -- so, check every keyframe
      // NOTE:  This code does not currently account for all $turret and $rotate positions

      SetNormalizedTimeAnim(frame_index, normalized_time, pm);

      SetModelAnglesAndPos(pm, normalized_time);

      for (model_index = 0; model_index < pm->n_models; model_index++) {
        bsp_info *sm = &pm->submodel[model_index];

        // For every vertex
        for (sm_vert_index = 0; sm_vert_index < sm->nverts; sm_vert_index++) {
          vector pnt;
          int mn;

          // Get the point and its current sub-object
          pnt = sm->verts[sm_vert_index];
          mn = model_index;

          // Instance up the tree
          while (mn != -1) {
            vector tpnt;

            vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
            vm_TransposeMatrix(&m);

            tpnt = pnt * m;

            pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

            mn = pm->submodel[mn].parent;
          }

          //				Maybe use for other code -- Accounts for world coordinates
          //				m = obj->orient;
          //				vm_TransposeMatrix(&m);
          //
          //				pnt = pnt * m;
          //
          //				*gun_point += obj->pos;

          // Find the min_xyz and max_xyz
          if (first_pnt) {
            first_pnt = false;
            min_xyz = max_xyz = pnt;
          } else {
            if (pnt.x < min_xyz.x)
              min_xyz.x = pnt.x;
            else if (pnt.x > max_xyz.x)
              max_xyz.x = pnt.x;

            if (pnt.y < min_xyz.y)
              min_xyz.y = pnt.y;
            else if (pnt.y > max_xyz.y)
              max_xyz.y = pnt.y;

            if (pnt.z < min_xyz.z)
              min_xyz.z = pnt.z;
            else if (pnt.z > max_xyz.z)
              max_xyz.z = pnt.z;
          }
        }
      }
    }

    geometric_center = (max_xyz + min_xyz) / 2.0;
    *offset_ptr = geometric_center;
  }

  for (frame_index = start_frame; frame_index <= end_frame; frame_index++) {
    // Because size changes with animation, we need the worst case point -- so, check every keyframe
    // NOTE:  This code does not currently account for all $turret and $rotate positions

    SetNormalizedTimeAnim(frame_index, normalized_time, pm);

    SetModelAnglesAndPos(pm, normalized_time);

    for (model_index = 0; model_index < pm->n_models; model_index++) {
      bsp_info *sm = &pm->submodel[model_index];

      // For every vertex
      for (sm_vert_index = 0; sm_vert_index < sm->nverts; sm_vert_index++) {
        vector pnt;
        int mn;

        // Get the point and its current sub-object
        pnt = sm->verts[sm_vert_index];
        mn = model_index;

        // Instance up the tree
        while (mn != -1) {
          vector tpnt;

          vm_AnglesToMatrix(&m, pm->submodel[mn].angs.p, pm->submodel[mn].angs.h, pm->submodel[mn].angs.b);
          vm_TransposeMatrix(&m);

          tpnt = pnt * m;

          pnt = tpnt + pm->submodel[mn].offset + pm->submodel[mn].mod_pos;

          mn = pm->submodel[mn].parent;
        }

        //				Maybe use for other code -- Accounts for world coordinates
        //				m = obj->orient;
        //				vm_TransposeMatrix(&m);
        //
        //				pnt = pnt * m;
        //
        //				*gun_point += obj->pos;

        cur_dist = vm_VectorDistance(&geometric_center, &pnt);
        if (cur_dist > size)
          size = cur_dist;
      }
    }
  }

  // This is a arbitary value.  It allows for some turret and rotations to be caught
  size = size + 0.01f;

  if (size_ptr) // DAJ
    *size_ptr = size;

  return size;
}

float ComputeDefaultSize(int type, int handle, float *size_ptr) {
  float size = ComputeDefaultSizeFunc(handle, size_ptr, NULL, true);

  if (type != OBJ_WEAPON && type != OBJ_DEBRIS && type != OBJ_POWERUP) {
    ComputeDefaultSizeFunc(handle, &Poly_models[handle].wall_size, &Poly_models[handle].wall_size_offset, false);
    ComputeDefaultSizeFunc(handle, &Poly_models[handle].anim_size, &Poly_models[handle].anim_size_offset, true);

    if (type == OBJ_PLAYER) {
      Poly_models[handle].anim_size *= PLAYER_SIZE_SCALAR;
      Poly_models[handle].anim_size_offset = Zero_vector;
    }
  } else {
    if (type == OBJ_POWERUP) {
      size *= 2.0f;
      *size_ptr *= 2.0f;
    }

    Poly_models[handle].wall_size = size;
    Poly_models[handle].wall_size_offset = Zero_vector;

    Poly_models[handle].anim_size = size;
    Poly_models[handle].anim_size_offset = Zero_vector;
  }

  Poly_models[handle].flags |= PMF_SIZE_COMPUTED;

  return size;
}
