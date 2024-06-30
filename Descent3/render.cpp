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

 * $Logfile: /DescentIII/Main/render.cpp $
 * $Revision: 325 $
 * $Date: 9/10/01 5:16p $
 * $Author: Matt $
 *
 *  Code to render the mine
 *
 * $Log: /DescentIII/Main/render.cpp $
 *
 * $NoKeywords: $
 */
#include "render.h"
#include <stdlib.h>
#include <string.h>
#include "descent.h"
#include "3d.h"
#include "mono.h"
#include "gametexture.h"
#include "texture.h"
#include "vclip.h"
#include "program.h"
#include "game.h"
#include "renderobject.h"
#include "door.h"
#include "terrain.h"
#include "renderer.h"
#include "room.h"
#include "lighting.h"
#include "lightmap.h"
#include "limits.h"
#include "lightmap_info.h"
#include "viseffect.h"
#include "weapon.h"
#include "fireball.h"
#include "scorch.h"
#include "findintersection.h"
#include "special_face.h"
#include "BOA.h"
#include "config.h"
#include "gameloop.h"
#include "doorway.h"
#include "TelComAutoMap.h"
#include "postrender.h"
#include "mem.h"
#include "Macros.h"
#include "psrand.h"
#include "player.h"
#include "args.h"
#ifdef EDITOR
#include "editor\d3edit.h"
#endif

#include <algorithm>

// #define KATMAI

// Katmai enhanced rotate only in a release build, because not
// everyone has the intel compiler!
#if (defined(RELEASE) && defined(KATMAI))
// Katmai version -- Rotates all the points in a room
void RotateRoomPoints(room *rp, vector4 *world_vecs);
#endif


static int Faces_rendered = 0;
extern float GetFPS();
extern uint8_t Outline_release_mode;
// 3d point for each vertex for use during rendering a room
uint8_t Room_clips[MAX_VERTS_PER_ROOM]; // used for face culling
// default face reflectivity
float Face_reflectivity = 0.5;
// the position of the viewer - valid while a frame is being rendered
static vector Viewer_eye;
static matrix Viewer_orient;
int Viewer_roomnum;
int Flag_automap, Called_from_terrain;
// Fog zone variables
float Fog_zone_start = FLT_MAX, Fog_zone_end = FLT_MAX;
int Must_render_terrain;
int Global_buffer_index;
int No_render_windows_hack = -1;
#define WALL_PULSE_INCREMENT .01
// Variables for various debugging features
#if (defined(_DEBUG) || defined(NEWEDITOR) || defined(EDITOR))
// If true, draw white outline for each polygon
int Render_portals = 0;
uint8_t Outline_mode = 0;
uint8_t Shell_render_flag = 0;
bool Outline_alpha = 0;
bool Outline_lightmaps = 0;
bool Render_floating_triggers = 0;
bool Use_software_zbuffer = 0;
bool Lighting_on = 1;
bool Render_all_external_rooms = 0;
bool In_editor_mode = 0;
bool Render_one_room_only = 0;
bool Render_inside_only = 0;
#else
#define In_editor_mode 0
#define Outline_lightmaps 0
#define Outline_alpha 0
#define Render_floating_triggers 0
#define Use_software_zbuffer 0
#define Render_all_external_rooms 0
#define Render_portals 0
#define Render_one_room_only 0
#define Render_inside_only 0
#define Shell_render_flag 0
#endif

#ifndef RELEASE
int Mine_depth;
#endif
#ifndef EDITOR
#define Search_lightmaps 0
#else  // ifndef EDITOR
// Vars for find_seg_side_face()
static int Search_lightmaps = 0; // true if searching for a lightmap
int found_lightmap;
#endif // ifndef EDITOR
bool Vsync_enabled = true;
// Prototypes
void RenderRoomObjects(room *rp);
// The current window width & height (valid while rendering)
static int Render_width, Render_height;
int Clear_window_color = -1;
int Clear_window = 2; // 1 = Clear whole background window, 2 = clear view portals into rest of world, 0 = no clear
#define MAX_RENDER_ROOMS 100
char Rooms_visited[MAX_ROOMS + MAX_PALETTE_ROOMS];
int Facing_visited[MAX_ROOMS + MAX_PALETTE_ROOMS];
// For keeping track of portal recursion
uint8_t Room_depth_list[MAX_ROOMS + MAX_PALETTE_ROOMS];
int16_t Render_list[MAX_RENDER_ROOMS];
int16_t External_room_list[MAX_ROOMS];
int N_external_rooms;
// For rendering specular faces
#define MAX_SPECULAR_FACES 2500
int16_t Specular_faces[MAX_SPECULAR_FACES];
int Num_specular_faces_to_render = 0;
int Num_real_specular_faces_to_render = 0; // Non-invisible specular faces
struct smooth_spec_vert {
  float r, g, b;
  int used;
};
smooth_spec_vert Smooth_verts[MAX_VERTS_PER_ROOM];
// For scorch rendering
uint16_t Scorches_to_render[MAX_FACES_PER_ROOM];
int Num_scorches_to_render = 0;
// For rendering volumetric fog
#define MAX_FOGGED_ROOMS_PER_FRAME 8
fog_portal_data Fog_portal_data[MAX_FOGGED_ROOMS_PER_FRAME];
int Num_fogged_rooms_this_frame = 0;
float Room_light_val = 0;
int Room_fog_plane_check = 0;
float Room_fog_distance = 0;
float Room_fog_eye_distance = 0;
vector Room_fog_plane, Room_fog_portal_vert;
int16_t Fog_faces[MAX_FACES_PER_ROOM];
int Num_fog_faces_to_render = 0;
#define MAX_EXTERNAL_ROOMS 100
vector External_room_corners[MAX_EXTERNAL_ROOMS][8];
uint8_t External_room_codes[MAX_EXTERNAL_ROOMS];
uint8_t External_room_project_net[MAX_EXTERNAL_ROOMS];
// For light glows
#define MAX_LIGHT_GLOWS 100
#define LGF_USED 1
#define LGF_INCREASING 2
#define LGF_FAST 4
struct light_glow {
  int16_t roomnum;
  int16_t facenum;
  float size;
  vector center;
  float scalar;
  uint8_t flags;
};
light_glow LightGlows[MAX_LIGHT_GLOWS];
light_glow LightGlowsThisFrame[MAX_LIGHT_GLOWS];
int FastCoronas = 0;
int Num_glows = 0, Num_glows_this_frame = 0;
// For sorting our textures in state limited environments
state_limited_element State_elements[MAX_STATE_ELEMENTS];
// For terrain portals
int Terrain_portal_left, Terrain_portal_right, Terrain_portal_top, Terrain_portal_bottom;
// For deformation effect
vector Global_alter_vec = {19, -19, 19};
// For detail stuff (mirrors, specular,etc)
bool Render_mirror_for_room = false;
int Mirror_room;
int Num_mirrored_rooms;
int16_t Mirrored_room_list[MAX_ROOMS];
uint8_t Mirrored_room_checked[MAX_ROOMS];
int16_t Mirror_rooms[MAX_ROOMS];
int Num_mirror_rooms = 0;
//
//  UTILITY FUNCS
//
// Determines if a face renders
// Parameters:	rp - pointer to room that contains the face
//					fp - pointer to the face in question
static inline bool FaceIsRenderable(room *rp, face *fp) {
  // Check for a floating trigger, which doesn't get rendered
  if ((fp->flags & FF_FLOATING_TRIG) && (!In_editor_mode || !Render_floating_triggers))
    return 0;
  // Check for face that's part of a portal
  if (fp->portal_num != -1) {
    if (rp->portals[fp->portal_num].flags & PF_RENDER_FACES)
      return 1;
    if (rp->flags & RF_FOG && !In_editor_mode)
      return 1;
    return 0;
  }

  // Nothing special, so face renders
  return 1;
}
// Flags for GetFaceAlpha()
#define FA_CONSTANT 1    // face has a constant alpha for the whole face
#define FA_VERTEX 2      // face has different alpha per vertex
#define FA_TRANSPARENT 4 // face has transparency (i.e. per pixel 1-bit alpha)
// Determines if a face draws with alpha blending
// Parameters:	fp - pointer to the face in question
//					bm_handle - the handle for the bitmap for this frame, or -1 if don't care about
// transparence Returns:		bitmask describing the alpha blending for the face
// the return bits are the ATF_ flags in renderer.h
static inline int GetFaceAlpha(face *fp, int bm_handle) {
  int ret = AT_ALWAYS;
  if (GameTextures[fp->tmap].flags & TF_SATURATE) {
    ret = AT_SATURATE_TEXTURE;
  } else {
    // Check the face's texture for an alpha value
    if (GameTextures[fp->tmap].alpha < 1.0)
      ret |= ATF_CONSTANT;

    // Check for transparency
    if (GameBitmaps[bm_handle].format != BITMAP_FORMAT_4444 && GameTextures[fp->tmap].flags & TF_TMAP2)
      ret |= ATF_TEXTURE;
  }
  return ret;
}
// Determine if you should render through a portal
// Parameters:	rp - the room the portal is in
//					pp - the portal we're checking
// Returns:		true if you should render the room to which the portal connects
static inline bool RenderPastPortal(room *rp, portal *pp) {
  // If we don't render the portal's faces, then we see through it
  if (!(pp->flags & PF_RENDER_FACES))
    return 1;
  if (!UseHardware) // Don't render alpha stuff in software
    return 0;
  // Check if the face's texture has transparency
  face *fp = &rp->faces[pp->portal_face];
  if (GameTextures[fp->tmap].flags & TF_PROCEDURAL)
    return 1;
  int bm_handle = GetTextureBitmap(fp->tmap, 0);
  if (GetFaceAlpha(fp, bm_handle))
    return 1; // Face has alpha or transparency, so we can see through it
  else
    return 0; // Not transparent, so no render past
}

// used during rendering as count of items in render_list[]
int N_render_rooms;
int first_terminal_room;
#define round(a) (int((a) + 0.5f))

#ifdef EDITOR
#define CROSS_WIDTH 8.0
#define CROSS_HEIGHT 8.0
#define CURFACE_COLOR GR_RGB(255, 255, 0)
#define CUREDGE_COLOR GR_RGB(0, 255, 0)
#define MARKEDFACE_COLOR GR_RGB(0, 255, 255)
#define MARKEDEDGE_COLOR GR_RGB(0, 150, 150)
#define PLACED_COLOR GR_RGB(255, 0, 255)
// Draw outline for current edge & vertex
void OutlineCurrentFace(room *rp, int facenum, int edgenum, int vertnum, ddgr_color face_color, ddgr_color edge_color) {
  face *fp = &rp->faces[facenum];
  g3Point p0, p1;
  uint8_t c0, c1;
  int v;
  for (v = 0; v < fp->num_verts; v++) {
    c0 = g3_RotatePoint(&p0, &rp->verts[fp->face_verts[v]]);
    c1 = g3_RotatePoint(&p1, &rp->verts[fp->face_verts[(v + 1) % fp->num_verts]]);
    if (!(c0 & c1)) { // both not off screen?
      // Draw current edge in green
      g3_DrawLine((v == edgenum) ? edge_color : face_color, &p0, &p1);
    }
    if ((v == vertnum) && (c0 == 0)) {
      // Draw a little cross at the current vert
      g3_ProjectPoint(&p0); // make sure projected
      rend_SetFlatColor(edge_color);
      rend_DrawLine(p0.p3_sx - CROSS_WIDTH, p0.p3_sy, p0.p3_sx, p0.p3_sy - CROSS_HEIGHT);
      rend_DrawLine(p0.p3_sx, p0.p3_sy - CROSS_HEIGHT, p0.p3_sx + CROSS_WIDTH, p0.p3_sy);
      rend_DrawLine(p0.p3_sx + CROSS_WIDTH, p0.p3_sy, p0.p3_sx, p0.p3_sy + CROSS_HEIGHT);
      rend_DrawLine(p0.p3_sx, p0.p3_sy + CROSS_HEIGHT, p0.p3_sx - CROSS_WIDTH, p0.p3_sy);
    }
  }
  // Draw upper left cross
  if (Outline_lightmaps && (rp->faces[facenum].flags & FF_LIGHTMAP)) {
    ASSERT(rp->faces[facenum].lmi_handle != BAD_LMI_INDEX);

    p0.p3_flags = 0;
    c0 = g3_RotatePoint(&p0, &LightmapInfo[rp->faces[facenum].lmi_handle].upper_left);
    if (!c0) {
      // Draw a little cross at the current vert
      g3_ProjectPoint(&p0); // make sure projected
      rend_SetFlatColor(GR_RGB(255, 0, 0));
      rend_DrawLine(p0.p3_sx - CROSS_WIDTH, p0.p3_sy, p0.p3_sx, p0.p3_sy - CROSS_HEIGHT);
      rend_DrawLine(p0.p3_sx, p0.p3_sy - CROSS_HEIGHT, p0.p3_sx + CROSS_WIDTH, p0.p3_sy);
      rend_DrawLine(p0.p3_sx + CROSS_WIDTH, p0.p3_sy, p0.p3_sx, p0.p3_sy + CROSS_HEIGHT);
      rend_DrawLine(p0.p3_sx, p0.p3_sy + CROSS_HEIGHT, p0.p3_sx - CROSS_WIDTH, p0.p3_sy);
    }
  }
}

//	Draw a room rotated and placed in space
static void DrawPlacedRoomFace(room *rp, vector *rotpoint, matrix *rotmat, vector *placepoint, int facenum, int color) {
  face *fp = &rp->faces[facenum];

  g3Point p0, p1;
  uint8_t c0, c1;
  int v;
  for (v = 0; v < fp->num_verts; v++) {
    vector tv;

    tv = (rp->verts[fp->face_verts[v]] - *rotpoint) * *rotmat + *placepoint;
    c0 = g3_RotatePoint(&p0, &tv);

    tv = (rp->verts[fp->face_verts[(v + 1) % fp->num_verts]] - *rotpoint) * *rotmat + *placepoint;
    c1 = g3_RotatePoint(&p1, &tv);

    if (!(c0 & c1)) // both not off screen?
      g3_DrawLine(color, &p0, &p1);
  }
}
#endif // ifdef EDITOR

struct clip_wnd {
  float left, top, right, bot;
};

static inline int clip2d(g3Point *pnt, clip_wnd *wnd) {
  int ret = 0;
  if (pnt->p3_codes & CC_BEHIND)
    return CC_BEHIND;

  if (pnt->p3_sx < wnd->left)
    ret |= CC_OFF_LEFT;
  if (pnt->p3_sx > wnd->right)
    ret |= CC_OFF_RIGHT;
  if (pnt->p3_sy < wnd->top)
    ret |= CC_OFF_TOP;
  if (pnt->p3_sy > wnd->bot)
    ret |= CC_OFF_BOT;
  return ret;
}

// Returns true if a line intersects another line
static inline bool LineIntersectsLine(g3Point *ls, g3Point *le, float x1, float y1, float x2, float y2) {
  float num, denom;
  num = ((ls->p3_sy - y1) * (x2 - x1)) - ((ls->p3_sx - x1) * (y2 - y1));
  denom = ((le->p3_sx - ls->p3_sx) * (y2 - y1)) - ((le->p3_sy - ls->p3_sy) * (x2 - x1));
  float r = num / denom;
  if (r >= 0.0 && r <= 1.0)
    return true;
  num = ((ls->p3_sy - y1) * (le->p3_sx - ls->p3_sx)) - ((ls->p3_sx - x1) * (le->p3_sy - ls->p3_sy));
  denom = ((le->p3_sx - ls->p3_sx) * (y2 - y1)) - ((le->p3_sy - ls->p3_sy) * (x2 - x1));
  float s = num / denom;
  if (s >= 0.0 && s <= 1.0)
    return true;
  return false;
}
// Returns true if a face intersects the passed in portal in any way
static inline bool FaceIntersectsPortal(room *rp, face *fp, clip_wnd *wnd) {
  g3Codes cc;
  int i;

  cc.cc_or = 0;
  cc.cc_and = 0xff;
  for (i = 0; i < fp->num_verts; i++) {
    cc.cc_or |= Room_clips[fp->face_verts[i]];
    cc.cc_and &= Room_clips[fp->face_verts[i]];
  }
  if (cc.cc_and)
    return false; // completely outside
  if (!cc.cc_or)
    return true; // completely inside

  // Now we must do a check
  for (i = 0; i < fp->num_verts; i++) {
    g3Point *p1 = &World_point_buffer[rp->wpb_index + fp->face_verts[i]];
    g3Point *p2 = &World_point_buffer[rp->wpb_index + fp->face_verts[(i + 1) % fp->num_verts]];
    if (LineIntersectsLine(p1, p2, wnd->left, wnd->top, wnd->right, wnd->top))
      return true;
    if (LineIntersectsLine(p1, p2, wnd->right, wnd->top, wnd->right, wnd->bot))
      return true;
    if (LineIntersectsLine(p1, p2, wnd->right, wnd->bot, wnd->left, wnd->bot))
      return true;
    if (LineIntersectsLine(p1, p2, wnd->left, wnd->bot, wnd->left, wnd->top))
      return true;
  }
  return false;
}
// Sets the status of a glow light
void SetGlowStatus(int roomnum, int facenum, vector *center, float size, int fast) {
  int i;
  int first = 1;
  int first_free = -1;
  int done = 0;
  int count = 0;
  int found = 0;
  for (i = 0; i < MAX_LIGHT_GLOWS && !done; i++) {
    if (count >= Num_glows) {
      if (first_free == -1)
        first_free = i;
      done = 1;
      continue;
    }
    if (LightGlows[i].flags & LGF_USED) {
      count++;
      if (LightGlows[i].roomnum == roomnum && LightGlows[i].facenum == facenum) {
        found = 1;
        LightGlows[i].flags |= LGF_INCREASING;
        done = 1;
      }
    } else {
      if (first) {
        first_free = i;
        first = 0;
      }
    }
  }
  if (!found) // couldn't find it - is it a new one?
  {
    if (first_free == -1) // no free slots
      return;
    LightGlows[first_free].flags = LGF_USED | LGF_INCREASING;
    if (fast)
      LightGlows[first_free].flags |= LGF_FAST;
    LightGlows[first_free].roomnum = roomnum;
    LightGlows[first_free].facenum = facenum;
    LightGlows[first_free].scalar = 0;
    LightGlows[first_free].size = size;
    LightGlows[first_free].center = *center;
    Num_glows++;
  }
}
// Takes a min,max vector and makes a surrounding cube from it
void MakePointsFromMinMax(vector *corners, vector *minp, vector *maxp) {
  corners[0].x = minp->x;
  corners[0].y = maxp->y;
  corners[0].z = minp->z;
  corners[1].x = maxp->x;
  corners[1].y = maxp->y;
  corners[1].z = minp->z;
  corners[2].x = maxp->x;
  corners[2].y = minp->y;
  corners[2].z = minp->z;
  corners[3].x = minp->x;
  corners[3].y = minp->y;
  corners[3].z = minp->z;
  corners[4].x = minp->x;
  corners[4].y = maxp->y;
  corners[4].z = maxp->z;
  corners[5].x = maxp->x;
  corners[5].y = maxp->y;
  corners[5].z = maxp->z;
  corners[6].x = maxp->x;
  corners[6].y = minp->y;
  corners[6].z = maxp->z;
  corners[7].x = minp->x;
  corners[7].y = minp->y;
  corners[7].z = maxp->z;
}

// Rotates all the points in a room
void RotateRoomPoints(room *rp, vector *world_vecs) {
  int i;
  // Jig the vertices a bit if being deformed
  if (Viewer_object->effect_info && (Viewer_object->effect_info->type_flags & EF_DEFORM)) {
    for (i = 0; i < rp->num_verts; i++) {
      vector vec = world_vecs[i];
      float val = ((ps_rand() % 1000) - 500.0) / 500.0;
      val *= Viewer_object->effect_info->deform_time;
      vec += Global_alter_vec * (Viewer_object->effect_info->deform_range * val);

      g3_RotatePoint(&World_point_buffer[rp->wpb_index + i], &vec);
      g3_ProjectPoint(&World_point_buffer[rp->wpb_index + i]);
    }
  } else {
    for (i = 0; i < rp->num_verts; i++) {
      g3_RotatePoint(&World_point_buffer[rp->wpb_index + i], &world_vecs[i]);
      g3_ProjectPoint(&World_point_buffer[rp->wpb_index + i]);
    }
  }
}

// Given a vector, reflects that vector off of a mirror vector
// Useful for specular and other reflective surfaces
void ReflectRay(vector *dest, vector *src, vector *mirror_norm) {
  *dest = *src;
  float d = *dest * *mirror_norm;
  vector upvec = d * *mirror_norm;
  *dest -= (2.0f * upvec);
}

// This is needed for small view cameras
// It clears the facing array so that it is recomputed
void ResetFacings() { memset(Facing_visited, 0, sizeof(int) * (Highest_room_index + 1)); }

// Marks all the faces facing us as drawable
void MarkFacingFaces(int roomnum, vector *world_verts) {
  room *rp = &Rooms[roomnum];
  face *fp;
  vector tvec;
  if (Facing_visited[roomnum] == FrameCount)
    return;
  Facing_visited[roomnum] = FrameCount;

  fp = &rp->faces[0];
  // Go through and mark all non facing faces
  if (Render_mirror_for_room) {
    room *mirror_rp = &Rooms[Mirror_room];
    face *mirror_fp = &mirror_rp->faces[mirror_rp->mirror_face];
    for (int t = 0; t < rp->num_faces; t++, fp++) {
      vector incident_norm;
      ReflectRay(&incident_norm, &fp->normal, &mirror_fp->normal);

      tvec = Viewer_eye - world_verts[fp->face_verts[0]];
      if ((tvec * incident_norm) <= 0)
        fp->flags |= FF_NOT_FACING;
    }
  } else {
    for (int i = 0; i < rp->num_faces; i++, fp++) {
      tvec = Viewer_eye - world_verts[fp->face_verts[0]];
      if ((tvec * fp->normal) <= 0)
        fp->flags |= FF_NOT_FACING;
    }
  }
}

// Returns true if the external room is visible from the passed in portal
int ExternalRoomVisibleFromPortal(int index, clip_wnd *wnd) {
  int i;
  uint8_t code = 0xff;
  g3Point pnt;
  // This is a stupid hack to prevent really large buildings from popping in and out of view
  if (External_room_project_net[index])
    return 1;
  for (i = 0; i < 8; i++) {
    pnt.p3_sx = External_room_corners[index][i].x;
    pnt.p3_sy = External_room_corners[index][i].y;
    pnt.p3_codes = 0;
    code &= clip2d(&pnt, wnd);
  }
  if (code)
    return 0; // building can't be seen from this portal
  return 1;
}

// Checks to see what faces intersect the passed in portal
void MarkFacesForRendering(int roomnum, clip_wnd *wnd) {
  room *rp = &Rooms[roomnum];
  int i;
  MarkFacingFaces(roomnum, rp->verts);

  // Rotate all the points in this room
  if (rp->wpb_index == -1) {
    rp->wpb_index = Global_buffer_index;

    // Katmai enhanced rotate only in a release build, because not
    // everyone has the intel compiler!
#if (defined(RELEASE) && defined(KATMAI))
    if (Katmai)
      RotateRoomPoints(rp, rp->verts4);
    else
#endif
      RotateRoomPoints(rp, rp->verts);

    Global_buffer_index += rp->num_verts;
  }
  if (rp->flags & RF_DOOR) {
    for (i = 0; i < rp->num_faces; i++)
      rp->faces[i].flags |= FF_VISIBLE;
  } else {
    // If this room contains a mirror, just mark all faces as visible
    // Else go through and figure out which ones are visible from the current portal
    if (rp->mirror_face == -1 || !Detail_settings.Mirrored_surfaces) {
      // Do pointer dereferencing instead of array lookup for speed reasons
      g3Point *pnt = &World_point_buffer[rp->wpb_index];
      for (i = 0; i < rp->num_verts; i++, pnt++) {
        Room_clips[i] = clip2d(pnt, wnd);
      }
      face *fp = &rp->faces[0];
      for (i = 0; i < rp->num_faces; i++, fp++) {
        if (fp->flags & (FF_NOT_FACING | FF_VISIBLE))
          continue; // this face is a backface

        if (FaceIntersectsPortal(rp, fp, wnd))
          fp->flags |= FF_VISIBLE;
      }
    } else {
      if (rp->flags & RF_MIRROR_VISIBLE) // If this room is already mirror, just return
        return;
      g3Point *pnt = &World_point_buffer[rp->wpb_index];
      for (i = 0; i < rp->num_verts; i++, pnt++) {
        Room_clips[i] = clip2d(pnt, wnd);
      }
      int done = 0;
      face *fp;
      for (i = 0; i < rp->num_mirror_faces && !done; i++) {
        fp = &rp->faces[rp->mirror_faces_list[i]];
        if (FaceIntersectsPortal(rp, fp, wnd)) {
          rp->flags |= RF_MIRROR_VISIBLE;
          Mirror_rooms[Num_mirror_rooms++] = roomnum;
          done = 1;
        }
      }

      if (rp->flags & RF_MIRROR_VISIBLE) // Mirror is visible, just mark all faces as visible
      {
        fp = &rp->faces[0];
        for (i = 0; i < rp->num_faces; i++, fp++) {
          fp->flags |= FF_VISIBLE;
        }
      } else {
        fp = &rp->faces[0];
        for (i = 0; i < rp->num_faces; i++, fp++) {
          if (fp->flags & (FF_NOT_FACING | FF_VISIBLE))
            continue; // this face is a backface

          if (FaceIntersectsPortal(rp, fp, wnd))
            fp->flags |= FF_VISIBLE;
        }
      }
    }
  }

  // Mark objects for rendering
  int objnum;
  for (objnum = rp->objects; (objnum != -1); objnum = Objects[objnum].next) {
    object *obj = &Objects[objnum];
    uint8_t anded = 0xff;
    g3Point pnts[8];
    vector vecs[8];
    uint8_t code;
    if (rp->flags & RF_DOOR) // Render all objects in a door room
    {
      obj->flags |= OF_SAFE_TO_RENDER;
      continue;
    }
    if (rp->flags & RF_MIRROR_VISIBLE) // Render all objects if this mirror is visible
    {
      obj->flags |= OF_SAFE_TO_RENDER;
      continue;
    }

    MakePointsFromMinMax(vecs, &obj->min_xyz, &obj->max_xyz);
    for (i = 0; i < 8; i++) {
      g3_RotatePoint(&pnts[i], &vecs[i]);
      g3_ProjectPoint(&pnts[i]);
      code = clip2d(&pnts[i], wnd);
      anded &= code;
      if (pnts[i].p3_codes & CC_BEHIND)
        anded = 0;
    }

    if (!anded) {
      // Object is visible
      obj->flags |= OF_SAFE_TO_RENDER;
    }
  }
}
// Prerotates all external room points and caches them
void RotateAllExternalRooms() {
  // Build the external room list if needed
  if (N_external_rooms == -1) {
    // Set up our z wall
    float zclip = (Detail_settings.Terrain_render_distance) * Matrix_scale.z;
    g3_SetFarClipZ(zclip);
    N_external_rooms = 0;

    int i;
    for (i = 0; i <= Highest_room_index; i++) {
      if ((Rooms[i].flags & RF_EXTERNAL) && Rooms[i].used) {
        External_room_list[N_external_rooms++] = i;
      }
    }
    ASSERT(N_external_rooms < MAX_EXTERNAL_ROOMS); // Get Jason if hit this
    // Rotate all the points
    vector corners[8];
    for (i = 0; i < N_external_rooms; i++) {
      int roomnum = External_room_list[i];
      room *rp = &Rooms[roomnum];
      MakePointsFromMinMax(corners, &rp->min_xyz, &rp->max_xyz);

      uint8_t andbyte = 0xff;
      g3Point pnt;
      External_room_codes[i] = 0xff;
      External_room_project_net[i] = 0;
      bool behind = 0;
      bool infront = 0;
      for (int t = 0; t < 8; t++) {
        g3_RotatePoint(&pnt, &corners[t]);
        External_room_codes[i] &= pnt.p3_codes;
        if (pnt.p3_codes & CC_BEHIND)
          behind = true;
        else
          infront = true;
        pnt.p3_codes &= ~CC_BEHIND;
        g3_ProjectPoint(&pnt);
        External_room_corners[i][t].x = pnt.p3_sx;
        External_room_corners[i][t].y = pnt.p3_sy;
      }
      if (infront && behind) {
        External_room_codes[i] = 0;
        External_room_project_net[i] = 1;
      } else {
        if (behind) {
          External_room_codes[i] = CC_BEHIND;
        }
      }
    }
  }
}

void CheckFogPortalExtents(int roomnum, int portalnum) {
  room *rp = &Rooms[roomnum];
  ASSERT(rp->flags & RF_FOG);

  int i, found_room = -1;
  for (i = 0; i < Num_fogged_rooms_this_frame; ++i) {
    if (Fog_portal_data[i].roomnum != roomnum)
      continue;

    found_room = i;
    break;
  }

  if (found_room == -1) {
    // Couldn't find this room in our list, so make a new one
    if (Num_fogged_rooms_this_frame >= MAX_FOGGED_ROOMS_PER_FRAME) {
      mprintf(0, "Too many fogged rooms in view cone!\n");
      return;
    }

    found_room = Num_fogged_rooms_this_frame++;
    Fog_portal_data[found_room].close_face = NULL;
    Fog_portal_data[found_room].close_dist = 10000000.0f;
    Fog_portal_data[found_room].roomnum = roomnum;
  }

  // get the portal face
  int fn = rp->portals[portalnum].portal_face;
  face *fp = &rp->faces[fn];

  // calculate the plane equation for the portal
  vector *vec = &rp->verts[fp->face_verts[0]];
  float distance = -vm_DotProduct(&fp->normal, vec);

  // calculate the distance from the camera to the portal
  distance = vm_DotProduct(&fp->normal, &Viewer_eye) + distance;
  if (distance < Fog_portal_data[found_room].close_dist) {
    // this portal is closer to the camera than the previous
    Fog_portal_data[found_room].close_dist = distance;
    Fog_portal_data[found_room].close_face = fp;
  }
}

g3Point Combined_portal_points[MAX_VERTS_PER_FACE * 5];
void BuildRoomListSub(int start_room_num, clip_wnd *wnd, int depth) {
  room *rp = &Rooms[start_room_num];
  int i, t;
  if (Render_portals) {
    rend_SetTextureType(TT_FLAT);
    rend_SetAlphaType(AT_CONSTANT);
    rend_SetAlphaValue(255);
    rend_SetFlatColor(GR_RGB(255, 255, 255));

    rend_DrawLine(wnd->left, wnd->top, wnd->right, wnd->top);
    rend_DrawLine(wnd->right, wnd->top, wnd->right, wnd->bot);
    rend_DrawLine(wnd->right, wnd->bot, wnd->left, wnd->bot);
    rend_DrawLine(wnd->left, wnd->bot, wnd->left, wnd->top);
  }
  if (!Rooms_visited[start_room_num]) {
    Render_list[N_render_rooms++] = start_room_num;
  }

  ASSERT(N_render_rooms < MAX_RENDER_ROOMS);
#ifndef RELEASE
  Mine_depth++;
#endif
  Rooms_visited[start_room_num] = 1;
  Room_depth_list[start_room_num] = depth;
  // If this room is a closed (non-seethrough) door, don't check any of its portals,
  //...UNLESS this is the first room we're looking at (meaning the viewer is in this room)
  if ((rp->flags & RF_DOOR) && (DoorwayGetPosition(rp) == 0.0) &&
      !(Doors[rp->doorway_data->doornum].flags & DF_SEETHROUGH))
    if (depth != 0)
      return;

  // Check all the portals for this room
  for (t = 0; t < rp->num_portals; t++) {
    portal *pp = &rp->portals[t];
    int croom = pp->croom;
    ASSERT(croom >= 0);

    // If we are an external room portalizing into another external room, then skip!
    if ((rp->flags & RF_EXTERNAL) && (Rooms[croom].flags & RF_EXTERNAL))
      continue;

    // Check if we can see through this portal, and if not, skip it
    if (!RenderPastPortal(rp, pp))
      continue;

    // If this portal has been visited, skip it
    if (Room_depth_list[croom] < Room_depth_list[start_room_num])
      continue;

    // Deal with external portals differently
    int external_door_hack = 0;
    if (rp->flags & RF_EXTERNAL && Rooms[croom].flags & RF_DOOR)
      external_door_hack = 1;

    // Get pointer to this portal's face
    face *fp = &rp->faces[pp->portal_face];

    // See if portal is facing toward us
    if (!external_door_hack && !(pp->flags & PF_COMBINED)) {
      vector check_v = Viewer_eye - rp->verts[fp->face_verts[0]];
      if (check_v * fp->normal <= 0) {
        // not facing us
        continue;
      }
    }

    g3Codes cc;
    cc.cc_or = 0;
    cc.cc_and = 0xff;
    int nv = fp->num_verts;

    // Code the face points
    // If this is a combined portal, then do that
    if ((pp->flags & PF_COMBINED) && !(Rooms[croom].flags & RF_FOG)) {
      // If this isn't the portal-combine master, then skip it
      if (pp->combine_master != t)
        continue;
      int num_points = 0;
      for (i = 0; i < rp->num_portals; i++) {
        if (((rp->portals[i].flags & PF_COMBINED) == 0) || rp->portals[i].combine_master != t)
          continue;

        int k;

        face *this_fp = &rp->faces[rp->portals[i].portal_face];
        vector check_v;
        check_v = Viewer_eye - rp->verts[this_fp->face_verts[0]];
        if (check_v * this_fp->normal <= 0) // not facing us
          continue;

        g3Codes combine_cc;
        combine_cc.cc_or = 0;
        combine_cc.cc_and = 0xff;
        ASSERT((num_points + this_fp->num_verts) < (MAX_VERTS_PER_FACE * 5));

        // First we must rotate and clip this polygon
        for (k = 0; k < this_fp->num_verts; k++) {
          uint8_t c = g3_RotatePoint(&Combined_portal_points[num_points + k], &rp->verts[this_fp->face_verts[k]]);
          combine_cc.cc_or |= c;
          combine_cc.cc_and &= c;
        }
        if (combine_cc.cc_and) {
          continue; // clipped away!
        } else if (combine_cc.cc_or) {
          g3Point *pointlist[MAX_VERTS_PER_FACE];
          for (k = 0; k < this_fp->num_verts; k++) {
            pointlist[k] = &Combined_portal_points[num_points + k];
            ASSERT(!(pointlist[k]->p3_flags & PF_TEMP_POINT));
          }

          // If portal not all on screen, must clip it
          int combine_nv = this_fp->num_verts;
          g3Point **pl = g3_ClipPolygon(pointlist, &combine_nv, &combine_cc);
          if (combine_cc.cc_and) {
            g3_FreeTempPoints(pl, combine_nv);
          } else {
            // save the clipped points
            g3Point temp_points[MAX_VERTS_PER_FACE];
            for (k = 0; k < combine_nv; k++) {
              temp_points[k] = *pl[k];
              temp_points[k].p3_flags &= ~PF_TEMP_POINT;
            }

            // release the temp points
            g3_FreeTempPoints(pl, combine_nv);

            // put the points back in the buffer
            // NOTE: we have to do it like this because pl points to
            // Combined_portal_points pointers
            for (k = 0; k < combine_nv; k++) {
              Combined_portal_points[k + num_points] = temp_points[k];
            }

            num_points += combine_nv;
          }
        } else {
          // No clipping needed, face is fully on screen
          num_points += this_fp->num_verts;
        }
      }
      if (num_points == 0)
        continue;

      // Now, figure out a min/max for these points
      g3Point four_points[4];
      for (i = 0; i < num_points; i++) {
        g3_ProjectPoint(&Combined_portal_points[i]);
      }
      int left = 0, top = 0, right = 0, bottom = 0;
      clip_wnd combine_wnd;
      combine_wnd.right = combine_wnd.bot = 0.0;
      combine_wnd.left = Render_width;
      combine_wnd.top = Render_height;
      // make new clip window
      for (i = 0; i < num_points; i++) {
        float x = Combined_portal_points[i].p3_sx, y = Combined_portal_points[i].p3_sy;
        if (x < combine_wnd.left) {
          combine_wnd.left = x;
          left = i;
        }
        if (x > combine_wnd.right) {
          combine_wnd.right = x;
          right = i;
        }
        if (y < combine_wnd.top) {
          combine_wnd.top = y;
          top = i;
        }
        if (y > combine_wnd.bot) {
          combine_wnd.bot = y;
          bottom = i;
        }
      }
      // Now harvest these points
      four_points[0] = Combined_portal_points[left];
      four_points[1] = Combined_portal_points[top];
      four_points[2] = Combined_portal_points[right];
      four_points[3] = Combined_portal_points[bottom];
      for (i = 0; i < 4; i++) {
        Combined_portal_points[i] = four_points[i];
        Combined_portal_points[i].p3_flags &= ~(PF_PROJECTED | PF_TEMP_POINT);
        uint8_t c = Combined_portal_points[i].p3_codes;
        cc.cc_and &= c;
        cc.cc_or |= c;
      }
      nv = 4;
    } else {
      for (i = 0; i < nv; i++) {
        g3_RotatePoint(&Combined_portal_points[i], &rp->verts[fp->face_verts[i]]);

        uint8_t c = Combined_portal_points[i].p3_codes;
        cc.cc_and &= c;
        cc.cc_or |= c;
      }
    }
    // If points are on screen, see if they're in the clip window
    if (cc.cc_and == 0 || external_door_hack) {
      bool clipped = 0;
      g3Point *pointlist[MAX_VERTS_PER_FACE], **pl = pointlist;
      for (i = 0; i < nv; i++)
        pointlist[i] = &Combined_portal_points[i];
      // If portal not all on screen, must clip it
      if (cc.cc_or) {
        pl = g3_ClipPolygon(pl, &nv, &cc);
        clipped = 1;
      }
      cc.cc_and = 0xff;
      for (i = 0; i < nv; i++) {
        g3_ProjectPoint(pl[i]);
        cc.cc_and &= clip2d(pl[i], wnd);
      }
      // Make sure it didn't get clipped away
      if (cc.cc_and == 0 || external_door_hack) {
        clip_wnd new_wnd;
        new_wnd.right = new_wnd.bot = 0.0;
        new_wnd.left = Render_width;
        new_wnd.top = Render_height;
        // make new clip window
        for (i = 0; i < nv; i++) {
          float x = pl[i]->p3_sx, y = pl[i]->p3_sy;
          if (x < new_wnd.left)
            new_wnd.left = x;
          if (x > new_wnd.right)
            new_wnd.right = x;
          if (y < new_wnd.top)
            new_wnd.top = y;
          if (y > new_wnd.bot)
            new_wnd.bot = y;
        }
        // If this room is fogged, see if this portal is closest
        if (Rooms[croom].flags & RF_FOG) {
          CheckFogPortalExtents(croom, pp->cportal);
        }
        // Combine the two windows
        new_wnd.left = std::max(wnd->left, new_wnd.left);
        new_wnd.right = std::min(wnd->right, new_wnd.right);
        new_wnd.top = std::max(wnd->top, new_wnd.top);
        new_wnd.bot = std::min(wnd->bot, new_wnd.bot);
        if (clipped) { // Free up temp points
          g3_FreeTempPoints(pl, nv);
          clipped = 0;
        }
        if (Rooms[croom].flags & RF_EXTERNAL) {
          if (!Called_from_terrain) {
            Must_render_terrain = 1;
            RotateAllExternalRooms();
            // For this external portal, we must check to see what external
            // rooms are visible from here
            for (i = 0; i < N_external_rooms; i++) {
              if (External_room_codes[i]) {
                continue;
              }
              if (External_room_list[i] != croom) {
                // If this portal has been visited, skip it
                if (Room_depth_list[External_room_list[i]] < Room_depth_list[start_room_num]) {
                  continue;
                }
                if (!ExternalRoomVisibleFromPortal(i, &new_wnd)) {
                  continue;
                }
              }
              MarkFacesForRendering(External_room_list[i], &new_wnd);
              BuildRoomListSub(External_room_list[i], &new_wnd, depth + 1);
              Room_depth_list[External_room_list[i]] = 255;
            }
            // Combine the two windows
            Terrain_portal_left = std::min<float>(new_wnd.left, Terrain_portal_left);
            Terrain_portal_right = std::max<float>(new_wnd.right, Terrain_portal_right);
            Terrain_portal_top = std::min<float>(new_wnd.top, Terrain_portal_top);
            Terrain_portal_bottom = std::max<float>(new_wnd.bot, Terrain_portal_bottom);
          }
        } else {
          MarkFacesForRendering(croom, &new_wnd);
          BuildRoomListSub(croom, &new_wnd, depth + 1);
          Room_depth_list[croom] = 255;
        }
      }
      if (clipped) // Free up temp points
        g3_FreeTempPoints(pl, nv);
    }
  }
}
// compare function for room z sort
float Room_z_depth[MAX_ROOMS + MAX_PALETTE_ROOMS];
static int Room_z_sort_func(const int16_t *a, const int16_t *b) {
  float az, bz;
  az = Room_z_depth[*a];
  bz = Room_z_depth[*b];
  if (az < bz)
    return 1;
  else if (az > bz)
    return -1;
  else
    return 0;
}
// build a list of rooms to be rendered
// fills in Render_list & N_render_rooms
void BuildRoomList(int start_room_num) {
  clip_wnd wnd;
  room *rp = &Rooms[start_room_num];
  int i;
  // For now, render all connected rooms
  for (i = 0; i <= Highest_room_index; i++) {
    Rooms_visited[i] = 0;
    Room_depth_list[i] = 255;
    Rooms[i].wpb_index = -1;
  }
#ifdef EDITOR
  Rooms_visited[start_room_num] = 0; // take care of rooms in the room palette
  Room_depth_list[start_room_num] = 0;
#endif
  N_external_rooms = -1;
  N_render_rooms = 0;
  Global_buffer_index = 0;
  // Mark all the faces in our start room as renderable
  for (i = 0; i < rp->num_faces; i++)
    rp->faces[i].flags |= FF_VISIBLE;

  MarkFacingFaces(start_room_num, rp->verts);
  // Enable mirror if there is one
  if (rp->mirror_face != -1 && Detail_settings.Mirrored_surfaces &&
      !(rp->faces[rp->mirror_face].flags & FF_NOT_FACING)) {
    rp->flags |= RF_MIRROR_VISIBLE;
    Mirror_rooms[Num_mirror_rooms++] = start_room_num;
  }

  // Get our points rotated, and update the global point list
  rp->wpb_index = Global_buffer_index;

  // Katmai enhanced rotate only in a release build, because not
  // everyone has the intel compiler!
#if (defined(RELEASE) && defined(KATMAI))
  if (Katmai)

    RotateRoomPoints(rp, rp->verts4);
  else
#endif
    RotateRoomPoints(rp, rp->verts);

  Global_buffer_index += rp->num_verts;

  // Mark all objects in this room as visible
  for (int objnum = rp->objects; (objnum != -1); objnum = Objects[objnum].next)
    Objects[objnum].flags |= OF_SAFE_TO_RENDER;

  // Initial clip window is whole screen
  wnd.left = wnd.top = 0.0;
  wnd.right = Render_width;
  wnd.bot = Render_height;
  BuildRoomListSub(start_room_num, &wnd, 0);
// mprintf(0,"N_render_rooms = %d ",N_render_rooms);
#ifdef EDITOR
  // Add all external rooms to render list if that flag set
  if (Editor_view_mode == VM_MINE && In_editor_mode) {
    if (Render_all_external_rooms) {
      int i;
      room *rp;
      for (i = 0, rp = std::data(Rooms); i <= Highest_room_index; i++, rp++) {
        if (rp->used && (rp->flags & RF_EXTERNAL)) {
          for (int t = 0; t < rp->num_faces; t++)
            rp->faces[t].flags |= FF_VISIBLE;
          MarkFacingFaces(i, rp->verts);

          if (!Rooms_visited[i])
            Render_list[N_render_rooms++] = i;
          Rooms_visited[i] = 1;
        }
      }
    }
  }
#endif
}
#ifdef EDITOR
// Returns 1 if x,y is inside the given polygon, else 0
int point_in_poly(int nv, g3Point *p, float x, float y) {
  int i, j, c = 0;
  for (i = 0, j = nv - 1; i < nv; j = i++) {
    if ((((p[i].p3_sy <= y) && (y < p[j].p3_sy)) || ((p[j].p3_sy <= y) && (y < p[i].p3_sy))) &&
        (x < (p[j].p3_sx - p[i].p3_sx) * (y - p[i].p3_sy) / (p[j].p3_sy - p[i].p3_sy) + p[i].p3_sx))
      c = !c;
  }

  return c;
}
/*
// Only called if editor active.
// Used to determine which face was clicked on.
void CheckFace(room *rp,int facenum, int nv, int bm,g3Point **pointlist)
{
        ddgr_color oldcolor;
        //draw search pixel in bright green
        rend_SetPixel(GR_RGB(0,255,10),search_x,search_y);
        oldcolor = rend_GetPixel(search_x,search_y);			//will be different in 15/16-bit color
        // Based on distance, draw in perspective or linear
        // This is gonna be ripped out
        rend_SetTextureType (TT_LINEAR_SPECIAL);
        for (int i=0;i<nv;i++)
        {
                g3Point *t;
                t=pointlist[i];
                if (t[i].p3_vec.z<35)
                        rend_SetTextureType (TT_PERSPECTIVE_SPECIAL);
        }
        g3_DrawPoly(nv,pointlist,bm);
        if (rend_GetPixel(search_x,search_y) != oldcolor) {
                found_room = ROOMNUM(rp);
                found_face = facenum;
        }
}
*/
#endif
#ifdef EDITOR
#define STEPSIZE .01f
#define STEPSIZE_MIN .1f
void RenderFloatingTrig(room *rp, face *fp) {
  if (!Render_floating_triggers)
    return;
  vector leftvec, rightvec;
  vector left, right;
  vector left_step, right_step;
  int n_steps, i, j;
  g3Point p3;
  float stepsize;
  left = rp->verts[fp->face_verts[0]];
  right = rp->verts[fp->face_verts[1]];
  g3_RotatePoint(&p3, &left);
  stepsize = STEPSIZE * p3.p3_z;
  if (stepsize < STEPSIZE_MIN)
    stepsize = STEPSIZE_MIN;
  leftvec = rp->verts[fp->face_verts[3]] - rp->verts[fp->face_verts[0]];
  rightvec = rp->verts[fp->face_verts[2]] - rp->verts[fp->face_verts[1]];
  n_steps = (vm_GetMagnitude(&leftvec) / stepsize + 0.5) + 1;
  left_step = leftvec / n_steps;
  right_step = rightvec / n_steps;
  for (i = 0; i < n_steps; i++) {
    vector p;
    g3Point p3;
    vector crossvec, cross_step;
    int n_crosssteps;

    crossvec = right - left;
    n_crosssteps = (vm_GetMagnitude(&crossvec) / stepsize + 0.5) + 1;
    cross_step = crossvec / n_steps;
    p = left;
    for (j = 0; j < n_crosssteps; j++) {
      if (g3_RotatePoint(&p3, &p) == 0) { // on screen
        g3_ProjectPoint(&p3);
        rend_SetPixel(GR_RGB(255, 100, 100), p3.p3_sx, p3.p3_sy);
      }
      p += cross_step;
    }
    left += left_step;
    right += right_step;
  }
}
#endif // ifdef EDITOR
void RenderSpecularFaces(room *rp) {
  ASSERT(Num_specular_faces_to_render > 0);
  int i, vn;
  g3Point *pointlist[MAX_VERTS_PER_FACE];
  g3Point pointbuffer[MAX_VERTS_PER_FACE];
  rend_SetWrapType(WT_CLAMP);
  rend_SetOverlayType(OT_NONE);
  rend_SetTextureType(TT_PERSPECTIVE);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetAlphaValue(255);

  for (i = 0; i < Num_specular_faces_to_render; i++) {
    face *fp = &rp->faces[Specular_faces[i]];
    int lm_handle = LightmapInfo[fp->lmi_handle].spec_map;
    ASSERT(lm_handle != -1);
    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[vn] = p;
      p->p3_uvl.u = fp->face_uvls[vn].u2;
      p->p3_uvl.v = fp->face_uvls[vn].v2;

      p->p3_flags |= PF_UV;
    }

    int save_w = lm_w(lm_handle);
    int save_h = lm_h(lm_handle);
    GameLightmaps[lm_handle].width = lm_w(LightmapInfo[fp->lmi_handle].lm_handle);
    GameLightmaps[lm_handle].height = lm_h(LightmapInfo[fp->lmi_handle].lm_handle);
    g3_DrawPoly(fp->num_verts, pointlist, lm_handle, MAP_TYPE_LIGHTMAP);
    GameLightmaps[lm_handle].width = save_w;
    GameLightmaps[lm_handle].height = save_h;
  }
  rend_SetWrapType(WT_WRAP);
}

float Specular_scalars[4][4] = {{1.0f}, {1.0f, .66f}, {1.0f, .66f, .33f}, {1.0f, .66f, .33f, .25f}};
void RenderSpecularFacesFlat(room *rp) {
  static int first = 1;
  static float lm_red[32], lm_green[32], lm_blue[32];
  int num_smooth_faces = 0;
  int num_smooth_used = 0;
  uint16_t smooth_faces[MAX_FACES_PER_ROOM];
  uint16_t smooth_used[MAX_VERTS_PER_ROOM];
  int i;
  ASSERT(Num_specular_faces_to_render > 0);
  if (!UseHardware)
    return;
  if (Num_real_specular_faces_to_render == 0) {
    for (i = 0; i < Num_specular_faces_to_render; i++) {
      face *fp = &rp->faces[Specular_faces[i]];
      fp->flags &= ~FF_SPEC_INVISIBLE;
    }
    return;
  }
  if (first) {
    first = 0;
    int i;
    for (i = 0; i < 32; i++) {
      lm_red[i] = (float)i / 31.0;
      lm_green[i] = (float)i / 31.0;
      lm_blue[i] = (float)i / 31.0;
    }
    for (i = 0; i < MAX_VERTS_PER_ROOM; i++) {
      Smooth_verts[i].used = 0;
    }
  }

  int t, vn;
  g3Point *pointlist[MAX_VERTS_PER_FACE];
  g3Point pointbuffer[MAX_VERTS_PER_FACE];
  rend_SetOverlayType(OT_NONE);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);
  rend_SetAlphaType(AT_SPECULAR);
  rend_SetZBufferWriteMask(0);

  for (i = 0; i < Num_specular_faces_to_render; i++) {
    face *fp = &rp->faces[Specular_faces[i]];

    int material_type = 0;
    if (GameTextures[fp->tmap].flags & TF_PLASTIC)
      material_type = 1;
    else if (GameTextures[fp->tmap].flags & TF_MARBLE)
      material_type = 2;
    int bm_handle = GetTextureBitmap(fp->tmap, 0);
    if ((fp->flags & FF_DESTROYED) && (GameTextures[fp->tmap].flags & TF_DESTROYABLE))
      bm_handle = GetTextureBitmap(GameTextures[fp->tmap].destroy_handle, 0);
    if (bm_format(bm_handle) != BITMAP_FORMAT_4444)
      continue;

    int lm_handle;
    uint16_t *data;
    int w, h;

    if (fp->lmi_handle == 65535) {
      // this face shouldn't be rendered during the specular pass...skip it
      continue;
    }

    lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
    data = (uint16_t *)lm_data(lm_handle);
    w = lm_w(lm_handle);
    h = lm_h(lm_handle);

    for (vn = 0; vn < fp->num_verts; vn++) {

      float rv = 0, gv = 0, bv = 0;
      float scalar = 0;
      float u, v;
      int int_u, int_v;
      uint16_t texel;
      int r, g, b;
      float vr, vg, vb;

      u = fp->face_uvls[vn].u2 * w;
      v = fp->face_uvls[vn].v2 * h;
      int_u = u;
      int_v = v;
      texel = data[int_v * w + int_u];
      r = (texel >> 10) & 0x1f;
      g = (texel >> 5) & 0x1f;
      b = (texel) & 0x1f;
      vr = lm_red[r];
      vg = lm_green[g];
      vb = lm_blue[b];

      vector subvec = Viewer_eye - rp->verts[fp->face_verts[vn]];
      vm_NormalizeVectorFast(&subvec);
      if (!(rp->flags & RF_EXTERNAL)) {
        int limit = SpecialFaces[fp->special_handle].num;
        int spec_index = limit - 1;
        /*if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR)
        {
                limit/=2;
        }*/

        for (t = 0; t < limit; t++) {
          uint16_t color;
          vector incident_norm;
          float spec_scalar;

          // Use regular static lighting
          color = SpecialFaces[fp->special_handle].spec_instance[t].bright_color;
          if (color == 0)
            continue;
          incident_norm =
              rp->verts[fp->face_verts[vn]] - SpecialFaces[fp->special_handle].spec_instance[t].bright_center;
          spec_scalar = Specular_scalars[spec_index][t];

          vm_NormalizeVectorFast(&incident_norm);
          float d;
          vector upvec;
          if ((GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) &&
              (SpecialFaces[fp->special_handle].flags & SFF_SPEC_SMOOTH)) {
            d = incident_norm * SpecialFaces[fp->special_handle].vertnorms[vn];
            upvec = d * SpecialFaces[fp->special_handle].vertnorms[vn];
          } else {
            d = incident_norm * fp->normal;
            upvec = d * fp->normal;
          }
          incident_norm -= (2 * upvec);
          float dotp = subvec * incident_norm;
          if (dotp > 1)
            dotp = 1;

          if (dotp > 0) {
            int index = ((float)(MAX_SPECULAR_INCREMENTS - 1) * dotp);
            scalar = Specular_tables[material_type][index] * spec_scalar;

            float cr = (float)((color >> 10) & 0x1f) / 31.0;
            float cg = (float)((color >> 5) & 0x1f) / 31.0;
            float cb = (float)(color & 0x1f) / 31.0;
            rv = std::min<float>(1.0, (rv + (scalar * cr)));
            gv = std::min<float>(1.0, (gv + (scalar * cg)));
            bv = std::min<float>(1.0, (bv + (scalar * cb)));
          }
        }
      } else {
        vector incident_norm = rp->verts[fp->face_verts[vn]] - Terrain_sky.satellite_vectors[0];
        vm_NormalizeVectorFast(&incident_norm);

        float d = incident_norm * fp->normal;
        vector upvec = d * fp->normal;
        incident_norm -= (2 * upvec);
        float dotp = subvec * incident_norm;
        if (dotp > 1)
          dotp = 1;

        if (dotp > 0) {
          int index = ((float)(MAX_SPECULAR_INCREMENTS - 1) * dotp);
          scalar = Specular_tables[material_type][index];
          rv = scalar;
          gv = scalar;
          bv = scalar;
        }
      }
      // Finally, brighten these value up a bit
      if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) {
        rv = rv * vr;
        gv = gv * vg;
        bv = bv * vb;
        if (Smooth_verts[fp->face_verts[vn]].used == 0) {
          Smooth_verts[fp->face_verts[vn]].used = 1;
          Smooth_verts[fp->face_verts[vn]].r = rv;
          Smooth_verts[fp->face_verts[vn]].g = gv;
          Smooth_verts[fp->face_verts[vn]].b = bv;
          smooth_used[num_smooth_used++] = fp->face_verts[vn];
        } else {
          Smooth_verts[fp->face_verts[vn]].r += rv;
          Smooth_verts[fp->face_verts[vn]].g += gv;
          Smooth_verts[fp->face_verts[vn]].b += bv;
        }
      } else {
        rv = std::min(1.0, rv * vr * 4.0);
        gv = std::min(1.0, gv * vg * 4.0);
        bv = std::min(1.0, bv * vb * 4.0);
        pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
        g3Point *p = &pointbuffer[vn];
        pointlist[vn] = p;
        p->p3_uvl.u = fp->face_uvls[vn].u;
        p->p3_uvl.v = fp->face_uvls[vn].v;
        p->p3_a = 1.0;
        p->p3_r = rv;
        p->p3_g = gv;
        p->p3_b = bv;
        p->p3_flags |= PF_RGBA | PF_UV;
      }
    }
    if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) {
      smooth_faces[num_smooth_faces] = fp - rp->faces;
      num_smooth_faces++;
    } else {
      if (fp->flags & FF_TRIANGULATED)
        g3_SetTriangulationTest(1);

      g3_DrawPoly(fp->num_verts, pointlist, bm_handle);

      if (fp->flags & FF_TRIANGULATED)
        g3_SetTriangulationTest(0);
    }
  }
  // Now draw smooth specular faces
  for (i = 0; i < num_smooth_faces; i++) {
    face *fp = &rp->faces[smooth_faces[i]];
    if (fp->flags & FF_SPEC_INVISIBLE) {
      fp->flags &= ~(FF_SPEC_INVISIBLE);
      continue;
    }
    int bm_handle = GetTextureBitmap(fp->tmap, 0);
    if ((fp->flags & FF_DESTROYED) && (GameTextures[fp->tmap].flags & TF_DESTROYABLE))
      bm_handle = GetTextureBitmap(GameTextures[fp->tmap].destroy_handle, 0);
    if (bm_format(bm_handle) != BITMAP_FORMAT_4444)
      continue;
    float reflect = GameTextures[fp->tmap].reflectivity * 1.5;
    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[vn] = p;
      p->p3_uvl.u = fp->face_uvls[vn].u;
      p->p3_uvl.v = fp->face_uvls[vn].v;
      p->p3_a = 1.0;
      p->p3_r = std::min<float>(1.0, Smooth_verts[fp->face_verts[vn]].r * reflect);
      p->p3_g = std::min<float>(1.0, Smooth_verts[fp->face_verts[vn]].g * reflect);
      p->p3_b = std::min<float>(1.0, Smooth_verts[fp->face_verts[vn]].b * reflect);
      p->p3_flags |= PF_RGBA | PF_UV;
    }

    if (fp->flags & FF_TRIANGULATED)
      g3_SetTriangulationTest(1);

    g3_DrawPoly(fp->num_verts, pointlist, bm_handle);

    if (fp->flags & FF_TRIANGULATED)
      g3_SetTriangulationTest(0);
  }
  for (i = 0; i < num_smooth_used; i++) {
    Smooth_verts[smooth_used[i]].used = 0;
  }
  rend_SetZBufferWriteMask(1);
}

// Adds a specular face to draw after the mine has been drawn
void UpdateSpecularFace(room *rp, face *fp) {
  /*if (!(rp->flags & RF_EXTERNAL)
  {
          int handle=GetSpecularLightmapForFace (&Viewer_eye,rp,fp);
          if (handle<0)
                  return;
  }*/
  if (Renderer_type == RENDERER_OPENGL)
    return;
  int n = Num_specular_faces_to_render;
  if (n >= MAX_SPECULAR_FACES)
    return;
  Specular_faces[n] = fp - rp->faces;
  Num_specular_faces_to_render++;
  if (!(fp->flags & FF_SPEC_INVISIBLE))
    Num_real_specular_faces_to_render++;
}

#if _DEBUG
bool Fog_disabled = 0;
#else
#define Fog_disabled 0
#endif

// Adds a specular face to draw after the mine has been drawn
void UpdateFogFace(room *rp, face *fp) {
  if (Fog_disabled || !Detail_settings.Fog_enabled)
    return;
  Fog_faces[Num_fog_faces_to_render++] = fp - rp->faces;
}

// Render a fog layer on top of a face
void RenderFogFaces(room *rp) {
  int vn;
  float eye_distance;
  g3Point *pointlist[MAX_VERTS_PER_FACE];
  g3Point pointbuffer[MAX_VERTS_PER_FACE];
  rend_SetOverlayType(OT_NONE);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetAlphaType(AT_VERTEX);
  rend_SetAlphaValue(255);
  rend_SetZBufferWriteMask(0);
  rend_SetCoplanarPolygonOffset(1);

  rend_SetFlatColor(GR_RGB((int)(rp->fog_r * 255.0), (int)(rp->fog_g * 255.0), (int)(rp->fog_b * 255.0)));
  for (int i = 0; i < Num_fog_faces_to_render; i++) {
    face *fp = &rp->faces[Fog_faces[i]];
    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[vn] = p;

      float mag = 0;

      if (Room_fog_plane_check == 0) {
        // Outside of the room
        vector *vec = &rp->verts[fp->face_verts[vn]];
        // Now we must generate the split point. This is simply
        // an equation in the form Origin + t*Direction

        float dist = (*vec * Room_fog_plane) + Room_fog_distance;

        vector subvec = *vec - Viewer_eye;
        float t = Room_fog_eye_distance / (Room_fog_eye_distance - dist);
        vector portal_point = Viewer_eye + (t * subvec);

        eye_distance = -(vm_DotProduct(&Viewer_orient.fvec, &portal_point));
        mag = vm_DotProduct(&Viewer_orient.fvec, vec) + eye_distance;
      } else if (Room_fog_plane_check == 1) {
        // In the room, distance from
        vector *vec = &rp->verts[fp->face_verts[vn]];
        mag = vm_DotProduct(&Room_fog_plane, vec) + Room_fog_distance;
      }
      float scalar = mag / rp->fog_depth;
      if (scalar > 1)
        scalar = 1;
      if (scalar < 0)
        scalar = 0;
      p->p3_a = scalar * Room_light_val;

      p->p3_flags |= PF_RGBA;
    }
    if (fp->flags & FF_TRIANGULATED)
      g3_SetTriangulationTest(1);
    g3_DrawPoly(fp->num_verts, pointlist, 0);
    if (fp->flags & FF_TRIANGULATED)
      g3_SetTriangulationTest(0);
  }

  rend_SetCoplanarPolygonOffset(0);
  rend_SetZBufferWriteMask(1);
}
// MATT!  Change this function to sort by state once you change the scorch system!
void RenderScorchesForRoom(room *rp) {
  int i;
  if (!Detail_settings.Scorches_enabled)
    return;
  // Set alpha, transparency, & lighting for this face
  rend_SetAlphaType(AT_LIGHTMAP_BLEND);
  rend_SetAlphaValue(255);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetZBias(-.5);
  rend_SetZBufferWriteMask(0);

  // Select texture type
  rend_SetTextureType(TT_LINEAR);

  for (i = 0; i < Num_scorches_to_render; i++) {
    DrawScorches(ROOMNUM(rp), Scorches_to_render[i]);
  }
  // Reset rendering states
  rend_SetZBias(0);
  rend_SetZBufferWriteMask(1);
}
// Draw the specified face
// Parameters:	rp - pointer to the room the face is un
//				facenum - which face in the specified room
void RenderLightmapFace(room *rp, int facenum) {
  int vn, drawn = 0;
  face *fp = &rp->faces[facenum];
  g3Point *pointlist[MAX_VERTS_PER_FACE];
  g3Point pointbuffer[MAX_VERTS_PER_FACE];
  uint8_t face_code = 255;
  if (NoLightmaps)
    return;
  if (fp->lmi_handle == BAD_LMI_INDEX)
    return;
  if (!(fp->flags & FF_LIGHTMAP))
    return;
  // check for render windows hack
  if (No_render_windows_hack == 1) {
    if (fp->portal_num != -1)
      return;
  }
  if (GameTextures[fp->tmap].flags & TF_SATURATE)
    return;
#ifdef EDITOR
  if (In_editor_mode && !Lighting_on)
    return;
#endif
  int lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
  // Setup saturation if needed
  if (GameTextures[fp->tmap].flags & TF_SATURATE_LIGHTMAP)
    rend_SetAlphaType(AT_LIGHTMAP_BLEND_SATURATE);
  // Our lightmaps aren't square, but our destination texture surfaces are
  // Use these scalars to get them into the correct coordinates
  float xscalar = (float)GameLightmaps[lm_handle].width / (float)GameLightmaps[lm_handle].square_res;
  float yscalar = (float)GameLightmaps[lm_handle].height / (float)GameLightmaps[lm_handle].square_res;
  if (!Render_mirror_for_room) {
    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[vn] = p;
      p->p3_uvl.u = fp->face_uvls[vn].u2 * xscalar;
      p->p3_uvl.v = fp->face_uvls[vn].v2 * yscalar;

      p->p3_flags |= PF_UV + PF_L + PF_RGBA; // has uv and l set
      p->p3_uvl.l = 1.0;

      face_code &= p->p3_codes;
    }
  } else {
    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[(fp->num_verts - 1) - vn] = p;
      p->p3_uvl.u = fp->face_uvls[vn].u2 * xscalar;
      p->p3_uvl.v = fp->face_uvls[vn].v2 * yscalar;

      p->p3_flags |= PF_UV + PF_L + PF_RGBA; // has uv and l set
      p->p3_uvl.l = 1.0;

      face_code &= p->p3_codes;
    }
  }

  if (face_code) // This entire face is off the scren
    return;
  rend_SetAlphaValue(GameTextures[fp->tmap].alpha * 255);
  if (fp->flags & FF_TRIANGULATED)
    g3_SetTriangulationTest(1);
  // Draw the damn thing
  drawn = g3_DrawPoly(fp->num_verts, pointlist, lm_handle, MAP_TYPE_LIGHTMAP);
  if (fp->flags & FF_TRIANGULATED)
    g3_SetTriangulationTest(0);
  // Restore if using saturated blending
  if (GameTextures[fp->tmap].flags & TF_SATURATE_LIGHTMAP)
    rend_SetAlphaType(AT_LIGHTMAP_BLEND);
}
// Draw the specified face
// Parameters:	rp - pointer to the room the face is un
//				facenum - which face in the specified room
void RenderFace(room *rp, int facenum) {
  int vn, drawn = 0;
  face *fp = &rp->faces[facenum];
  g3Point *pointlist[MAX_VERTS_PER_FACE];
  g3Point pointbuffer[MAX_VERTS_PER_FACE];
  int bm_handle;
  float uchange = 0, vchange = 0;
  texture_type tt;
  uint8_t do_triangle_test = 0;
  g3Codes face_cc;
  static int first = 1;
  static float lm_red[32], lm_green[32], lm_blue[32];
  bool spec_face = 0;
  face_cc.cc_and = 0xff;
  face_cc.cc_or = 0;
#ifdef EDITOR
  if (fp->flags & FF_FLOATING_TRIG) {
    RenderFloatingTrig(rp, fp);
    return;
  }
#endif
  // Clear triangulation flag
  fp->flags &= ~FF_TRIANGULATED;
  // check for render windows hack
  if (No_render_windows_hack == 1) {
    if (fp->portal_num != -1)
      return;
  }
  if (rp->flags & RF_TRIANGULATE)
    do_triangle_test = 1;
  if (!Render_mirror_for_room && Detail_settings.Specular_lighting && (GameTextures[fp->tmap].flags & TF_SPECULAR) &&
      ((fp->special_handle != BAD_SPECIAL_FACE_INDEX) || (rp->flags & RF_EXTERNAL)))
    spec_face = 1;
  // Figure out if there is any texture sliding
  if (GameTextures[fp->tmap].slide_u != 0) {
    int int_time = Gametime / GameTextures[fp->tmap].slide_u;
    float norm_time = Gametime - (int_time * GameTextures[fp->tmap].slide_u);
    norm_time /= GameTextures[fp->tmap].slide_u;
    uchange = norm_time;
  }
  if (GameTextures[fp->tmap].slide_v != 0) {
    int int_time = Gametime / GameTextures[fp->tmap].slide_v;
    float norm_time = Gametime - (int_time * GameTextures[fp->tmap].slide_v);
    norm_time /= GameTextures[fp->tmap].slide_v;
    vchange = norm_time;
  }
  // Build list of points and UVLs for this face
  if (Render_mirror_for_room) // If mirror room, order the vertices counter clockwise
  {
    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[(fp->num_verts - 1) - vn] = p;
      p->p3_uvl.u = fp->face_uvls[vn].u;
      p->p3_uvl.v = fp->face_uvls[vn].v;
      p->p3_uvl.u2 = fp->face_uvls[vn].u2;
      p->p3_uvl.v2 = fp->face_uvls[vn].v2;

      p->p3_flags |= PF_UV + PF_L + PF_UV2; // has uv and l set
#ifndef RELEASE
      if ((fp->flags & FF_LIGHTMAP) && UseHardware)
        p->p3_uvl.l = Room_light_val;
      else
        p->p3_uvl.l = 1.0;
#else
      p->p3_uvl.l = Room_light_val;
#endif

      // do texture sliding
      p->p3_uvl.u += uchange;
      p->p3_uvl.v += vchange;
      face_cc.cc_and &= p->p3_codes;
      face_cc.cc_or |= p->p3_codes;
    }
  } else {

    for (vn = 0; vn < fp->num_verts; vn++) {
      pointbuffer[vn] = World_point_buffer[rp->wpb_index + fp->face_verts[vn]];
      g3Point *p = &pointbuffer[vn];
      pointlist[vn] = p;
      p->p3_uvl.u = fp->face_uvls[vn].u;
      p->p3_uvl.v = fp->face_uvls[vn].v;
      p->p3_uvl.u2 = fp->face_uvls[vn].u2;
      p->p3_uvl.v2 = fp->face_uvls[vn].v2;

      p->p3_flags |= PF_UV + PF_L + PF_UV2; // has uv and l set
#ifndef RELEASE
      if ((fp->flags & FF_LIGHTMAP) && UseHardware)
        p->p3_uvl.l = Room_light_val;
      else
        p->p3_uvl.l = 1.0;
#else
      p->p3_uvl.l = Room_light_val;
#endif

      // do texture sliding
      p->p3_uvl.u += uchange;
      p->p3_uvl.v += vchange;
      face_cc.cc_and &= p->p3_codes;
      face_cc.cc_or |= p->p3_codes;
    }
  }
  if (face_cc.cc_and) // This entire face is off the screen
  {
    if (spec_face && GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) {
      fp->flags |= FF_SPEC_INVISIBLE;
      UpdateSpecularFace(rp, fp);
    }
    return;
  }
  // Do stupid gouraud shading for lightmap
  if (NoLightmaps) {
    if (first) {
      first = 0;
      for (int i = 0; i < 32; i++) {
        lm_red[i] = (float)i / 31.0;
        lm_green[i] = (float)i / 31.0;
        lm_blue[i] = (float)i / 31.0;
      }
    }

    if (fp->flags & FF_LIGHTMAP) {
      int lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
      uint16_t *data = (uint16_t *)lm_data(lm_handle);
      int w = lm_w(lm_handle);
      int h = lm_h(lm_handle);

      for (int i = 0; i < fp->num_verts; i++) {
        float u = fp->face_uvls[i].u2 * (w - 1);
        float v = fp->face_uvls[i].v2 * (h - 1);
        g3Point *p = &pointbuffer[i];
        int int_u = u;
        int int_v = v;
        uint16_t texel = data[int_v * w + int_u];
        int r = (texel >> 10) & 0x1f;
        int g = (texel >> 5) & 0x1f;
        int b = (texel) & 0x1f;
        p->p3_r = p->p3_l * lm_red[r];
        p->p3_g = p->p3_l * lm_green[g];
        p->p3_b = p->p3_l * lm_blue[b];
        p->p3_flags |= PF_RGBA;
      }
    } else {
      for (int i = 0; i < fp->num_verts; i++) {
        g3Point *p = &pointbuffer[i];
        p->p3_r = p->p3_l;
        p->p3_g = p->p3_l;
        p->p3_b = p->p3_l;
        p->p3_flags |= PF_RGBA;
      }
    }
  }
  // Get bitmap handle
  if ((fp->flags & FF_DESTROYED) && (GameTextures[fp->tmap].flags & TF_DESTROYABLE)) {
    bm_handle = GetTextureBitmap(GameTextures[fp->tmap].destroy_handle, 0);
    ASSERT(bm_handle != -1);
  } else
    bm_handle = GetTextureBitmap(fp->tmap, 0);
// If searching,
#ifdef EDITOR
  ddgr_color oldcolor;
  if (TSearch_on) {
    rend_SetPixel(GR_RGB(16, 255, 16), TSearch_x, TSearch_y);
    oldcolor = rend_GetPixel(TSearch_x, TSearch_y);
  }
#endif
  // Set alpha, transparency, & lighting for this face
  rend_SetAlphaType(GetFaceAlpha(fp, bm_handle));

  // If this is a mirror face, and mirrors are turned off, then just make opaque
  if (!Detail_settings.Mirrored_surfaces && rp->mirror_face != -1 && rp->faces[rp->mirror_face].tmap == fp->tmap)
    rend_SetAlphaValue(255);
  else if (Render_mirror_for_room && rp->mirror_face != -1 && fp->tmap == rp->faces[rp->mirror_face].tmap &&
           rp != &Rooms[Mirror_room])
    rend_SetAlphaValue(255); // This prevents mirrors from rendering each other
  else
    rend_SetAlphaValue(GameTextures[fp->tmap].alpha * 255);
  if (!UseHardware)
    rend_SetLighting(Lighting_on ? LS_GOURAUD : LS_NONE);
  else
    rend_SetLighting(LS_GOURAUD);
  if (!NoLightmaps)
    rend_SetColorModel(CM_MONO);
  else
    rend_SetColorModel(CM_RGB);
  // Set lighting map
  if ((fp->flags & FF_LIGHTMAP) && (!StateLimited || UseMultitexture)) {
    if (GameTextures[fp->tmap].flags & TF_SATURATE)
      rend_SetOverlayType(OT_NONE);
    else
      rend_SetOverlayType(OT_BLEND);
    rend_SetOverlayMap(LightmapInfo[fp->lmi_handle].lm_handle);
  } else
    rend_SetOverlayType(OT_NONE);
  // Select texture type
  if (!UseHardware) {
    tt = TT_LINEAR;                        // default to linear
    for (vn = 0; vn < fp->num_verts; vn++) // select perspective if close
      if (pointlist[vn]->p3_vec.z < 35) {
        tt = TT_PERSPECTIVE;
        break;
      }
    rend_SetTextureType(tt);
  } else
    rend_SetTextureType(TT_PERSPECTIVE);
  if (face_cc.cc_or) // Possible triangulate this face cuz its off screen somewhat
  {
    if (Room_light_val < 1.0)
      do_triangle_test = 1;
    if (Detail_settings.Fog_enabled && (rp->flags & RF_FOG))
      do_triangle_test = 1;
    if (spec_face)
      do_triangle_test = 1;
  }
  if (do_triangle_test) {
    fp->flags |= FF_TRIANGULATED;
    g3_SetTriangulationTest(1);
  }
  // Do special fog stuff for portal faces
  if (rp->flags & RF_FOG && !In_editor_mode) {
    if (fp->portal_num != -1 && !(rp->portals[fp->portal_num].flags & PF_RENDER_FACES)) {
      drawn = 1;
      goto draw_fog;
    }
  }
  // Draw the damn thing
  drawn = g3_DrawPoly(fp->num_verts, pointlist, bm_handle, MAP_TYPE_BITMAP, &face_cc);
#ifdef EDITOR
  if (TSearch_on) {
    if (rend_GetPixel(TSearch_x, TSearch_y) != oldcolor) {
      TSearch_found_type = TSEARCH_FOUND_MINE;
      TSearch_seg = rp - std::data(Rooms);
      TSearch_face = facenum;
    }
  }
#endif

  // Do light saturation
  if (!Render_mirror_for_room && Rendering_main_view && drawn && fp->portal_num == -1 &&
      ((fp->flags & FF_CORONA) || FastCoronas) && (fp->flags & FF_LIGHTMAP) && UseHardware &&
      (GameTextures[fp->tmap].flags & TF_LIGHT)) {
    if (Num_glows_this_frame < MAX_LIGHT_GLOWS && Detail_settings.Coronas_enabled) {
      LightGlowsThisFrame[Num_glows_this_frame].roomnum = rp - std::data(Rooms);
      LightGlowsThisFrame[Num_glows_this_frame].facenum = facenum;
      Num_glows_this_frame++;
    }
  }
  // Draw a specular face
  if (!Render_mirror_for_room && spec_face) {
    if (drawn)
      UpdateSpecularFace(rp, fp);
    else {
      if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) {
        fp->flags |= FF_SPEC_INVISIBLE;
        UpdateSpecularFace(rp, fp);
      }
    }
  }

  // Draw scorches, if any
  if (drawn && fp->flags & FF_SCORCHED && !Render_mirror_for_room) {
    if (!StateLimited)
      DrawScorches(ROOMNUM(rp), facenum);
    else {
      Scorches_to_render[Num_scorches_to_render] = facenum;
      Num_scorches_to_render++;
    }
  }

draw_fog:
  if (!Render_mirror_for_room && !In_editor_mode && drawn && (rp->flags & RF_FOG) && UseHardware) {
    UpdateFogFace(rp, fp);
  }

  if (do_triangle_test)
    g3_SetTriangulationTest(0);
  // Mark it as rendered
  if (drawn)
    fp->renderframe = FrameCount % 256;
// if (Render_mirror_for_room && (GameTextures[fp->tmap].flags & TF_ALPHA))
// rend_SetZBufferWriteMask (1);
#ifdef EDITOR
  if (OUTLINE_ON(OM_MINE)) // Outline the face
  {
    rend_SetTextureType(TT_FLAT);
    rend_SetAlphaType(AT_ALWAYS);
    rend_SetFlatColor(GR_RGB(255, 255, 255));

    if (UseHardware) {
      rend_SetZBias(-.1f);
      for (int i = 0; i < fp->num_verts; i++) {
        g3_DrawSpecialLine(pointlist[i], pointlist[(i + 1) % fp->num_verts]);
      }
      rend_SetZBias(0);
    } else {
      for (int i = 0; i < fp->num_verts; i++) {
        g3_DrawLine(GR_RGB(255, 255, 255), pointlist[i], pointlist[(i + 1) % fp->num_verts]);
      }
    }
    if ((fp->flags & FF_HAS_TRIGGER) && (fp->num_verts > 3)) {
      g3_DrawLine(CUREDGE_COLOR, pointlist[0], pointlist[2]);
      g3_DrawLine(CUREDGE_COLOR, pointlist[1], pointlist[3]);
    }
    if (fp->special_handle != BAD_SPECIAL_FACE_INDEX) {
      g3Point p1, p2;
      vector verts[MAX_VERTS_PER_FACE];
      vector center, end;
      for (int t = 0; t < fp->num_verts; t++)
        verts[t] = rp->verts[fp->face_verts[t]];
      vm_GetCentroid(&center, verts, fp->num_verts);
      vector subvec = SpecialFaces[fp->special_handle].spec_instance[0].bright_center - center;
      vm_NormalizeVectorFast(&subvec);
      end = center + subvec;
      g3_RotatePoint(&p1, &center);
      g3_RotatePoint(&p2, &end);
      g3_DrawLine(GR_RGB(255, 255, 255), &p1, &p2);
      /*for (t=0;t<fp->num_verts;t++)
      {
              end=rp->verts[fp->face_verts[t]]+SpecialFaces[fp->special_handle].vertnorms[t];
              g3_RotatePoint (&p1,&rp->verts[fp->face_verts[t]]);
              g3_RotatePoint (&p2,&end);
              g3_DrawLine(GR_RGB(255,255,255),&p1,&p2);
      }*/
    }
  }
  if (Outline_lightmaps) {
    rend_SetTextureType(TT_FLAT);
    rend_SetAlphaType(AT_ALWAYS);
    if (fp == &Curroomp->faces[Curface] && (fp->flags & FF_LIGHTMAP)) {
      ASSERT(fp->lmi_handle != BAD_LMI_INDEX);

      lightmap_info *lmi = &LightmapInfo[fp->lmi_handle];
      uint16_t *src_data = (uint16_t *)lm_data(lmi->lm_handle);
      matrix facematrix;
      vector fvec = -lmi->normal;
      vm_VectorToMatrix(&facematrix, &fvec, NULL, NULL);
      vector rvec = facematrix.rvec * lmi->xspacing;
      vector uvec = facematrix.uvec * lmi->yspacing;
      vm_TransposeMatrix(&facematrix);
      int w = lm_w(lmi->lm_handle);
      int h = lm_h(lmi->lm_handle);
      for (int i = 0; i < w * h; i++) {
        int t;
        g3Point epoints[20];
        vector evec[20];
        int y = i / w;
        int x = i % w;
        evec[0] = lmi->upper_left - (y * uvec) + (x * rvec);
        g3_RotatePoint(&epoints[0], &evec[0]);
        pointlist[0] = &epoints[0];
        evec[1] = lmi->upper_left - (y * uvec) + ((x + 1) * rvec);
        g3_RotatePoint(&epoints[1], &evec[1]);
        pointlist[1] = &epoints[1];
        evec[2] = lmi->upper_left - ((y + 1) * uvec) + ((x + 1) * rvec);
        g3_RotatePoint(&epoints[2], &evec[2]);
        pointlist[2] = &epoints[2];
        evec[3] = lmi->upper_left - ((y + 1) * uvec) + (x * rvec);
        g3_RotatePoint(&epoints[3], &evec[3]);
        pointlist[3] = &epoints[3];

        if (!(src_data[y * w + x] & OPAQUE_FLAG)) {
          for (t = 0; t < 4; t++)
            g3_DrawLine(GR_RGB(255, 0, 255), pointlist[t], pointlist[(t + 1) % 4]);
        } else {
          for (t = 0; t < 4; t++)
            g3_DrawLine(GR_RGB(255, 255, 255), pointlist[t], pointlist[(t + 1) % 4]);
        }
        // Draw interpolated normals
        /*if (fp->special_handle!=BAD_SPECIAL_FACE_INDEX && SpecialFaces[fp->special_handle].normal_map!=NULL)
        {
                vector norm,from,to,temp;
                g3Point p1,p2;
                vm_MakeZero (&from);
                norm.x=Normal_table[SpecialFaces[fp->special_handle].normal_map[i*3+0]];
                norm.y=Normal_table[SpecialFaces[fp->special_handle].normal_map[i*3+1]];
                norm.z=Normal_table[SpecialFaces[fp->special_handle].normal_map[i*3+2]];
                vm_MatrixMulVector (&temp,&norm,&facematrix);
                norm=temp;
                for (t=0;t<4;t++)
                        from+=evec[t];
                from/=4;
                to=from+norm;
                g3_RotatePoint (&p1,&from);
                g3_RotatePoint (&p2,&to);
                g3_DrawLine(GR_RGB(255,255,255),&p1,&p2);
        }*/

        if (Search_lightmaps) {
          for (t = 0; t < 4; t++)
            g3_ProjectPoint(&epoints[t]);

          if (point_in_poly(4, epoints, TSearch_x, TSearch_y)) {
            found_lightmap = i;
            TSearch_found_type = TSEARCH_FOUND_MINE;
            TSearch_seg = ROOMNUM(rp);
            TSearch_face = facenum;
          }
        }
      }
    }
  }
#endif
}
static float face_depth[MAX_FACES_PER_ROOM];
// compare function for room face sort
static int room_face_sort_func(const int16_t *a, const int16_t *b) {
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
// Sorts the faces of a room before rendering.  Used for rendering in the editor.
// Parameters:	rp	- pointer to the room to be rendered
void RenderRoomSorted(room *rp) {
  int vn, fn, i, rcount;
  int render_order[MAX_FACES_PER_ROOM];
  ASSERT(rp->num_faces <= MAX_FACES_PER_ROOM);
  // Rotate all the points
  if (rp->wpb_index == -1) {
    rp->wpb_index = Global_buffer_index;
    // Katmai enhanced rotate only in a release build, because not
    // everyone has the intel compiler!
#if (defined(RELEASE) && defined(KATMAI))
    if (Katmai)
      RotateRoomPoints(rp, rp->verts4);
    else
#endif
      RotateRoomPoints(rp, rp->verts);

    Global_buffer_index += rp->num_verts;
  }
  // Build list of visible (non-backfacing) faces, & compute average face depths
  for (fn = rcount = 0; fn < rp->num_faces; fn++) {
    face *fp = &rp->faces[fn];

    if ((!(fp->flags & FF_VISIBLE)) || ((fp->flags & FF_NOT_FACING))) {
      fp->flags &= ~(FF_NOT_FACING | FF_VISIBLE);
      continue; // this guy shouldn't be rendered
    }
    // Clear visibility flags
    fp->flags &= ~(FF_VISIBLE | FF_NOT_FACING);

    if (!FaceIsRenderable(rp, fp))
      continue; // skip this face
#ifdef EDITOR
    if (In_editor_mode) {
      if ((Shell_render_flag & SRF_NO_NON_SHELL) && (fp->flags & FF_NOT_SHELL))
        continue;
      if ((Shell_render_flag & SRF_NO_SHELL) && !(fp->flags & FF_NOT_SHELL))
        continue;
    }
#endif
    face_depth[fn] = 0;
    for (vn = 0; vn < fp->num_verts; vn++)
      face_depth[fn] += World_point_buffer[rp->wpb_index + fp->face_verts[vn]].p3_z;
    face_depth[fn] /= fp->num_verts;
    // initialize order list
    render_order[rcount] = fn;
    rcount++;
  }
  // Sort the faces
  qsort(render_order, rcount, sizeof(*render_order), (int (*)(const void *, const void *))room_face_sort_func);
  // Render the faces
  for (i = rcount - 1; i >= 0; i--)
    RenderFace(rp, render_order[i]);
}

// Sets up fog if this room is fogged
void SetupRoomFog(room *rp, vector *eye, matrix *orient, int viewer_room) {
  if ((rp->flags & RF_FOG) == 0)
    return;

  if (!Detail_settings.Fog_enabled) {
    // fog is disabled
    Room_fog_plane_check = -1;
    return;
  }

  if (viewer_room == (rp - std::data(Rooms))) {
    // viewer is in the room
    vector *vec = eye;
    Room_fog_plane_check = 1;
    Room_fog_distance = -vm_DotProduct(&orient->fvec, vec);
    Room_fog_plane = orient->fvec;
    return;
  }

  // find the 'fogroom' number (we should have put it in here if we will render the room)
  int found_room = -1;
  for (int i = 0; i < Num_fogged_rooms_this_frame && found_room == -1; i++) {
    if (Fog_portal_data[i].roomnum == rp - std::data(Rooms)) {
      found_room = i;
      break;
    }
  }

  if (found_room == -1 || Fog_portal_data[found_room].close_face == NULL) {
    // we won't be rendering this room
    Room_fog_plane_check = -1;
    return;
  }

  // Use the closest face
  face *close_face = Fog_portal_data[found_room].close_face;
  Room_fog_plane_check = 0;
  Room_fog_plane = close_face->normal;
  Room_fog_portal_vert = rp->verts[close_face->face_verts[0]];
  Room_fog_distance = -vm_DotProduct(&Room_fog_plane, &Room_fog_portal_vert);
  Room_fog_eye_distance = (*eye * Room_fog_plane) + Room_fog_distance;
}

// Renders the faces in a room without worrying about sorting.  Used in the game when Z-buffering is active
void RenderRoomUnsorted(room *rp) {
  int fn;
  int rcount = 0;
  ASSERT(rp->num_faces <= MAX_FACES_PER_ROOM);

  // Rotate points in this room if need be
  if (rp->wpb_index == -1) {
    rp->wpb_index = Global_buffer_index;

// Katmai enhanced rotate only in a release build, because not
// everyone has the intel compiler!
#if (defined(RELEASE) && defined(KATMAI))
    if (Katmai) {
      RotateRoomPoints(rp, rp->verts4);
    } else
#endif
    {
      RotateRoomPoints(rp, rp->verts);
    }

    Global_buffer_index += rp->num_verts;
  }

  // Sort portal faces if this is a fogged room
  if (rp->flags & RF_FOG) {
    SetupRoomFog(rp, &Viewer_eye, &Viewer_orient, Viewer_roomnum);
  }

  // Check for visible (non-backfacing) faces, & render
  for (fn = 0; fn < rp->num_faces; fn++) {
    face *fp = &rp->faces[fn];
    int fogged_portal = 0;

    if (!(fp->flags & FF_VISIBLE) || (fp->flags & FF_NOT_FACING)) {
      if (GameTextures[fp->tmap].flags & TF_SMOOTH_SPECULAR) {
        if (!Render_mirror_for_room && Detail_settings.Specular_lighting &&
            (GameTextures[fp->tmap].flags & TF_SPECULAR) &&
            ((fp->special_handle != BAD_SPECIAL_FACE_INDEX) || (rp->flags & RF_EXTERNAL))) {
          fp->flags |= FF_SPEC_INVISIBLE;
          UpdateSpecularFace(rp, fp);
        }
      }
      fp->flags &= ~(FF_NOT_FACING | FF_VISIBLE);
      continue; // this guy shouldn't be rendered
    }

    // Clear visibility flags
    if (Render_mirror_for_room == false) {
      fp->flags &= ~(FF_VISIBLE | FF_NOT_FACING);
    } else {
      if (rp == &Rooms[Mirror_room]) {
        if (rp->faces[fn].tmap == rp->faces[rp->mirror_face].tmap)
          continue; // Don't render the mirror face if rendering the mirror
      }
    }

    if (!FaceIsRenderable(rp, fp))
      continue; // skip this face

#ifdef EDITOR
    if (In_editor_mode) {
      if ((Shell_render_flag & SRF_NO_NON_SHELL) && (fp->flags & FF_NOT_SHELL))
        continue;
      if ((Shell_render_flag & SRF_NO_SHELL) && !(fp->flags & FF_NOT_SHELL))
        continue;
    }
#endif

    if (fp->portal_num != -1 && !(rp->portals[fp->portal_num].flags & PF_RENDER_FACES) && (rp->flags & RF_FOG)) {
      fogged_portal = 1;
    }

    if (Render_mirror_for_room == false && (fogged_portal || (GetFaceAlpha(fp, -1) & (ATF_CONSTANT + ATF_VERTEX)))) {
      // Place alpha faces into our postrender list
      if (Num_postrenders < MAX_POSTRENDERS) {
        face_depth[fn] = 0.0f;
        for (int vn = 0; vn < fp->num_verts; vn++) {
          face_depth[fn] += World_point_buffer[rp->wpb_index + fp->face_verts[vn]].p3_z;
        }
        Postrender_list[Num_postrenders].type = PRT_WALL;
        Postrender_list[Num_postrenders].roomnum = rp - std::data(Rooms);
        Postrender_list[Num_postrenders].facenum = fn;
        Postrender_list[Num_postrenders++].z = face_depth[fn] /= fp->num_verts;
        ;
      }
    } else {
      if (!StateLimited) {
        RenderFace(rp, fn);
      } else {
        // setup order list
        State_elements[rcount].facenum = fn;
        if (fp->flags & FF_LIGHTMAP)
          State_elements[rcount].sort_key = (LightmapInfo[fp->lmi_handle].lm_handle * MAX_TEXTURES) + fp->tmap;
        else
          State_elements[rcount].sort_key = fp->tmap;
        rcount++;
      }
    }
  }

  if (StateLimited) {
    // Sort the faces
    SortStates(State_elements, rcount);

    // Render the faces
    int i;
    for (i = rcount - 1; i >= 0; i--) {
      RenderFace(rp, State_elements[i].facenum);
    }

    if (!UseMultitexture) {
      // Since we're state limited, we have to render lightmap faces completely separate
      // Now render lightmap faces
      rend_SetAlphaType(AT_LIGHTMAP_BLEND);
      rend_SetLighting(LS_GOURAUD);
      rend_SetColorModel(CM_MONO);
      rend_SetOverlayType(OT_NONE);
      rend_SetTextureType(TT_PERSPECTIVE);
      rend_SetWrapType(WT_CLAMP);
      rend_SetMipState(0);
      for (i = rcount - 1; i >= 0; i--) {
        RenderLightmapFace(rp, State_elements[i].facenum);
      }
      rend_SetWrapType(WT_WRAP);
      rend_SetMipState(1);
    }
  }
}

// Figures out a scalar value to apply to all vertices in the room
void ComputeRoomPulseLight(room *rp) {
  if (rp->pulse_time == 0 || In_editor_mode)
    Room_light_val = 1.0;
  else {
    float ptime = rp->pulse_time * WALL_PULSE_INCREMENT;
    float add_time = rp->pulse_offset * WALL_PULSE_INCREMENT;

    int int_time = (int)((Gametime + add_time) / (ptime * 2));
    float left_time = (Gametime + add_time) - (int_time * ptime * 2);
    float norm_time = left_time / (ptime);
    if (norm_time > 1)
      Room_light_val = 1 - (norm_time - 1.0);
    else
      Room_light_val = norm_time;
  }
  if (!In_editor_mode) {
    if (rp->flags & RF_STROBE) {
      int val = (Gametime * 10) + (rp - std::data(Rooms));
      if (val % 2)
        Room_light_val = 0;
    }
    if (rp->flags & RF_FLICKER) {
      ps_srand((Gametime * 1000) + (rp - std::data(Rooms)));
      if (ps_rand() % 2)
        Room_light_val = 0;
    }
  }
}


#define CORONA_DIST_CUTOFF 5.0f
// Draws a glow around a light
void RenderSingleLightGlow(int index) {
  int bm_handle;
  room *rp = &Rooms[LightGlows[index].roomnum];
  face *fp = &rp->faces[LightGlows[index].facenum];
  texture *texp = &GameTextures[fp->tmap];
  bm_handle = Fireballs[DEFAULT_CORONA_INDEX + texp->corona_type].bm_handle;

  // Get size of light
  float size = LightGlows[index].size;
  vector center = LightGlows[index].center;

  // Get alpha of light
  vector tvec = Viewer_eye - rp->verts[fp->face_verts[0]];
  vm_NormalizeVectorFast(&tvec);
  float facing_scalar = (tvec * fp->normal) * 2;
  if (facing_scalar < 0)
    return;
  tvec = center - Viewer_eye;

  float dist = vm_GetMagnitudeFast(&tvec);
  if (dist < (size * CORONA_DIST_CUTOFF))
    return;
  if (dist < (size * (CORONA_DIST_CUTOFF + 15))) {
    float dist_scalar = ((dist - (size * CORONA_DIST_CUTOFF)) / (size * 15));
    facing_scalar *= dist_scalar;
  }

  facing_scalar *= LightGlows[index].scalar;
  facing_scalar = std::min<float>(facing_scalar, 1.0);
  // Take into effect pulsing
  ComputeRoomPulseLight(rp);
  facing_scalar *= Room_light_val;
  rend_SetAlphaValue(facing_scalar * .4 * 255);

  float maxc = std::max({texp->r, texp->g, texp->b});
  float r, g, b;
  if (maxc > 1.0) {
    r = texp->r / maxc;
    g = texp->g / maxc;
    b = texp->b / maxc;
  } else {
    r = texp->r;
    g = texp->g;
    b = texp->b;
  }
  if (LightGlows[index].flags & LGF_FAST) {
    rend_SetZBufferWriteMask(0);
    rend_SetZBias((-size / 2));
  } else {
    rend_SetZBufferState(0);
  }
  ddgr_color color = GR_RGB(r * 255, g * 255, b * 255);
  g3_DrawBitmap(&center, size, (size * bm_h(bm_handle, 0)) / bm_w(bm_handle, 0), bm_handle, color);
  if (LightGlows[index].flags & LGF_FAST) {
    rend_SetZBufferWriteMask(1);
    rend_SetZBias(0);
  } else {
    rend_SetZBufferState(1);
  }
}
// Draws a glow around a light
void RenderSingleLightGlow2(int index) {
  static int first = 1;
  static int normal_handle, star_handle;
  int bm_handle;
  room *rp = &Rooms[LightGlows[index].roomnum];
  face *fp = &rp->faces[LightGlows[index].facenum];
  texture *texp = &GameTextures[fp->tmap];

  if (first) {
    int texhandle = FindTextureName("LongCorona");
    if (texhandle == -1)
      star_handle = 0;
    else
      star_handle = GetTextureBitmap(texhandle, 0);
    first = 0;
  }
  rend_SetAlphaValue(.4 * 255);
  float maxc = std::max({texp->r, texp->g, texp->b});
  float r, g, b;
  if (maxc > 1.0) {
    r = texp->r / maxc;
    g = texp->g / maxc;
    b = texp->b / maxc;
  } else {
    r = texp->r;
    g = texp->g;
    b = texp->b;
  }
  rend_SetLighting(LS_GOURAUD);

  // Get size of light
  float size = LightGlows[index].size;
  vector center = LightGlows[index].center;
  vector corona_pos = center + (fp->normal * size);
  bm_handle = star_handle;
  matrix mat, rot_mat;
  vector fvec, uvec, temp_vec, rvec;
  temp_vec = -fp->normal;

  vm_VectorToMatrix(&mat, NULL, &temp_vec, NULL);

  // Rotate view vector into billboard space
  fvec = Viewer_eye - corona_pos;
  vm_NormalizeVectorFast(&fvec);
  temp_vec = fvec * mat;
  fvec = temp_vec;
  vm_NormalizeVectorFast(&fvec);
  rvec.x = fvec.z;
  rvec.y = 0;
  rvec.z = -fvec.x;
  uvec.y = 1;
  uvec.x = 0;
  uvec.z = 0;
  vm_VectorToMatrix(&rot_mat, NULL, &uvec, &rvec);
  vm_TransposeMatrix(&mat);
  temp_vec = rot_mat.rvec * mat;
  rot_mat.rvec = temp_vec;
  temp_vec = rot_mat.uvec * mat;
  rot_mat.uvec = temp_vec;
  temp_vec = rot_mat.fvec * mat;
  rot_mat.fvec = temp_vec;
  vector world_vecs[4];
  g3Point pnts[4], *pntlist[4];
  world_vecs[0] = corona_pos - (size * rot_mat.rvec);
  world_vecs[0] += (size * rot_mat.uvec);
  world_vecs[1] = corona_pos + (size * rot_mat.rvec);
  world_vecs[1] += (size * rot_mat.uvec);
  world_vecs[2] = corona_pos + (size * rot_mat.rvec);
  world_vecs[2] -= (size * rot_mat.uvec);
  world_vecs[3] = corona_pos - (size * rot_mat.rvec);
  world_vecs[3] -= (size * rot_mat.uvec);
  for (int i = 0; i < 4; i++) {
    g3_RotatePoint(&pnts[i], &world_vecs[i]);
    pnts[i].p3_flags |= PF_UV | PF_RGBA;
    pnts[i].p3_r = r;
    pnts[i].p3_g = g;
    pnts[i].p3_b = b;
    pntlist[i] = &pnts[i];
  }
  pnts[0].p3_u = 0;
  pnts[0].p3_v = 0;
  pnts[1].p3_u = 1;
  pnts[1].p3_v = 0;
  pnts[2].p3_u = 1;
  pnts[2].p3_v = 1;
  pnts[3].p3_u = 0;
  pnts[3].p3_v = 1;
  g3_DrawPoly(4, pntlist, bm_handle);
  rend_SetZBufferWriteMask(1);
}
// Figures out if we can see the center of a light face and adds it to our globa list
void CheckLightGlowsForRoom(room *rp) {
  int i;
  for (i = 0; i < Num_glows_this_frame; i++) {
    // For each light, see if we can cast a vector to it
    face *fp = &rp->faces[LightGlowsThisFrame[i].facenum];
    vector verts[MAX_VERTS_PER_FACE];
    vector center;
    for (int t = 0; t < fp->num_verts; t++)
      verts[t] = rp->verts[fp->face_verts[t]];
    float size = sqrt(vm_GetCentroid(&center, verts, fp->num_verts));
    size *= 2;
    center += (fp->normal / 4);
    if (vm_VectorDistanceQuick(&center, &Viewer_eye) < (size * CORONA_DIST_CUTOFF))
      continue;
    // Check if we can see this light
    fvi_info hit_info;
    fvi_query fq;
    // shoot a ray from the light position to the current vertex
    if (FastCoronas) {
      if (rp->flags & RF_EXTERNAL) {
        SetGlowStatus(rp - std::data(Rooms), LightGlowsThisFrame[i].facenum, &center, size, FastCoronas);
        continue;
      }
      vector subvec = Viewer_eye - center;
      vm_NormalizeVectorFast(&subvec);
      subvec *= size;
      subvec += center;
      fq.p0 = &center;
      fq.p1 = &subvec;
      fq.startroom = rp - std::data(Rooms);
    } else {
      fq.p0 = &Viewer_eye;
      fq.p1 = &center;
      fq.startroom = Viewer_object->roomnum;
    }

    fq.rad = 0.0f;
    fq.flags = FQ_CHECK_OBJS | FQ_NO_RELINK | FQ_IGNORE_WEAPONS | FQ_ROBOTS_AS_SPHERE | FQ_PLAYERS_AS_SPHERE;
    fq.thisobjnum = -1;
    fq.ignore_obj_list = NULL;
    int fate = fvi_FindIntersection(&fq, &hit_info);
    if (fate != HIT_NONE)
      continue;
    SetGlowStatus(rp - std::data(Rooms), LightGlowsThisFrame[i].facenum, &center, size, FastCoronas);
  }
}
// Called before a frame starts to render - sets all of our light glows to decreasing
void PreUpdateAllLightGlows() {
  int i, count;
  for (i = 0, count = 0; i < MAX_LIGHT_GLOWS && count < Num_glows; i++) {
    if (LightGlows[i].flags & LGF_USED) {
      count++;
      LightGlows[i].flags &= ~LGF_INCREASING;
    }
  }
}
// Called after a frame has been rendered - slowly morphs our light glows into nothing
void PostUpdateAllLightGlows() {
  int i, count;
  for (i = 0, count = 0; i < MAX_LIGHT_GLOWS && count < Num_glows; i++) {
    if (LightGlows[i].flags & LGF_USED) {
      count++;
      if (LightGlows[i].flags & LGF_INCREASING) {
        LightGlows[i].scalar += (Frametime * 4);
        if (LightGlows[i].scalar > 1)
          LightGlows[i].scalar = 1;
      } else {
        LightGlows[i].scalar -= (Frametime * 4);
        if (LightGlows[i].scalar < 0) {
          LightGlows[i].scalar = 0;
          LightGlows[i].flags &= ~LGF_USED;
          Num_glows--;
          count--;
        }
      }
    }
  }

  ASSERT(Num_glows >= 0);
}
// Recursive function that mirrored rooms use
void BuildMirroredRoomListSub(int start_room_num, clip_wnd *wnd) {
  room *rp = &Rooms[start_room_num];
  g3Point portal_points[MAX_VERTS_PER_FACE];
  int i, t;
  if (!Mirrored_room_checked[start_room_num]) {
    Mirrored_room_list[Num_mirrored_rooms++] = start_room_num;
  }
  Mirrored_room_checked[start_room_num] = 1;

  // If this room is a closed (non-seethrough) door, don't check any of its portals,
  //...UNLESS this is the first room we're looking at (meaning the viewer is in this room)
  if ((rp->flags & RF_DOOR) && (DoorwayGetPosition(rp) == 0.0) &&
      !(Doors[rp->doorway_data->doornum].flags & DF_SEETHROUGH))
    return;
  room *mirror_rp = &Rooms[Mirror_room];
  vector *mirror_vec = &mirror_rp->verts[mirror_rp->faces[mirror_rp->mirror_face].face_verts[0]];
  face *mirror_fp = &mirror_rp->faces[mirror_rp->mirror_face];
  vector *mirror_norm = &mirror_fp->normal;
  // This is how far the mirror face is from the normalized plane
  float mirror_dist =
      -(mirror_vec->x * mirror_norm->x + mirror_vec->y * mirror_norm->y + mirror_vec->z * mirror_norm->z);
  // Check all the portals for this room
  for (t = 0; t < rp->num_portals; t++) {
    portal *pp = &rp->portals[t];
    int croom = pp->croom;
    ASSERT(croom >= 0);
    // If we are an external room portalizing into another external room, then skip!
    if ((rp->flags & RF_EXTERNAL) && (Rooms[croom].flags & RF_EXTERNAL))
      continue;
    // Check if we can see through this portal, and if not, skip it
    if (!RenderPastPortal(rp, pp))
      continue;
    // If this portal has been visited, skip it
    if (Mirrored_room_checked[croom])
      continue;
    // Deal with external portals differently
    int external_door_hack = 0;
    if (rp->flags & RF_EXTERNAL && Rooms[croom].flags & RF_DOOR)
      external_door_hack = 1;
    // Get pointer to this portal's face
    face *fp = &rp->faces[pp->portal_face];
    // See if portal is facing toward us
    if (!external_door_hack) {
      vector temp_vec;
      vector *vec = &rp->verts[fp->face_verts[0]];
      float dist_from_mirror =
          vec->x * mirror_norm->x + vec->y * mirror_norm->y + vec->z * mirror_norm->z + mirror_dist;
      // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
      temp_vec = *vec - (*mirror_norm * (dist_from_mirror * 2));
      vector incident_norm;
      ReflectRay(&incident_norm, &fp->normal, &mirror_fp->normal);

      vector tvec = Viewer_eye - temp_vec;
      if ((tvec * incident_norm) <= 0)
        continue; // not facing
    }

    g3Codes cc;
    cc.cc_or = 0;
    cc.cc_and = 0xff;
    int nv = fp->num_verts;
    // Code the face points
    for (i = 0; i < nv; i++) {
      vector temp_vec;
      vector *vec = &rp->verts[fp->face_verts[i]];
      float dist_from_mirror =
          vec->x * mirror_norm->x + vec->y * mirror_norm->y + vec->z * mirror_norm->z + mirror_dist;
      // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
      temp_vec = *vec - (*mirror_norm * (dist_from_mirror * 2));
      g3_RotatePoint(&portal_points[i], &temp_vec);

      uint8_t c = portal_points[i].p3_codes;
      cc.cc_and &= c;
      cc.cc_or |= c;
    }
    // If points are on screen, see if they're in the clip window
    if (cc.cc_and == 0 || external_door_hack) {
      bool clipped = 0;
      g3Point *pointlist[MAX_VERTS_PER_FACE], **pl = pointlist;
      for (i = 0; i < nv; i++)
        pointlist[i] = &portal_points[i];
      // If portal not all on screen, must clip it
      if (cc.cc_or) {
        pl = g3_ClipPolygon(pl, &nv, &cc);
        clipped = 1;
      }
      cc.cc_and = 0xff;
      for (i = 0; i < nv; i++) {
        g3_ProjectPoint(pl[i]);
        cc.cc_and &= clip2d(pl[i], wnd);
      }
      // Make sure it didn't get clipped away
      if (cc.cc_and == 0 || external_door_hack) {
        clip_wnd new_wnd;
        new_wnd.right = new_wnd.bot = 0.0;
        new_wnd.left = Render_width;
        new_wnd.top = Render_height;
        // make new clip window
        for (i = 0; i < nv; i++) {
          float x = pl[i]->p3_sx, y = pl[i]->p3_sy;
          if (x < new_wnd.left)
            new_wnd.left = x;
          if (x > new_wnd.right)
            new_wnd.right = x;
          if (y < new_wnd.top)
            new_wnd.top = y;
          if (y > new_wnd.bot)
            new_wnd.bot = y;
        }

        // Combine the two windows
        new_wnd.left = std::max(wnd->left, new_wnd.left);
        new_wnd.right = std::min(wnd->right, new_wnd.right);
        new_wnd.top = std::max(wnd->top, new_wnd.top);
        new_wnd.bot = std::min(wnd->bot, new_wnd.bot);
        if (clipped) { // Free up temp points
          g3_FreeTempPoints(pl, nv);
          clipped = 0;
        }
        BuildMirroredRoomListSub(croom, &new_wnd);
      }
      if (clipped) // Free up temp points
        g3_FreeTempPoints(pl, nv);
    }
  }
}
// Goes through and builds a list of rooms that can be seen from a mirror
void BuildMirroredRoomList() {
  room *rp = &Rooms[Mirror_room];
  clip_wnd wnd;
  Num_mirrored_rooms = 0;
  memset(Mirrored_room_checked, 0, MAX_ROOMS);
  Mirrored_room_checked[Mirror_room] = 1;
  Mirrored_room_list[Num_mirrored_rooms++] = Mirror_room;

  // Initial clip window is whole screen
  wnd.left = wnd.top = 0.0;
  wnd.right = Render_width;
  wnd.bot = Render_height;
  g3Point portal_points[MAX_VERTS_PER_FACE], temp_points[MAX_VERTS_PER_FACE * 2];
  g3Point *pointlist[MAX_VERTS_PER_FACE * 2], **pl = pointlist;
  room *mirror_rp = &Rooms[Mirror_room];
  vector *mirror_vec = &mirror_rp->verts[mirror_rp->faces[mirror_rp->mirror_face].face_verts[0]];
  face *mirror_fp = &mirror_rp->faces[mirror_rp->mirror_face];
  vector *mirror_norm = &mirror_fp->normal;
  // This is how far the mirror face is from the normalized plane
  float mirror_dist =
      -(mirror_vec->x * mirror_norm->x + mirror_vec->y * mirror_norm->y + mirror_vec->z * mirror_norm->z);
  int total_points = 0;
  for (int t = 0; t < rp->num_mirror_faces; t++) {
    face *fp = &rp->faces[rp->mirror_faces_list[t]];
    int i;
    ASSERT(total_points + fp->num_verts <= MAX_VERTS_PER_FACE * 2);
    g3Codes cc;
    cc.cc_and = 0xff;
    cc.cc_or = 0;
    int nv = fp->num_verts;
    int clipped = 0;

    for (i = 0; i < fp->num_verts; i++) {
      vector temp_vec;
      vector *vec = &rp->verts[fp->face_verts[i]];
      float dist_from_mirror =
          vec->x * mirror_norm->x + vec->y * mirror_norm->y + vec->z * mirror_norm->z + mirror_dist;
      // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
      temp_vec = *vec - (*mirror_norm * (dist_from_mirror * 2));
      g3_RotatePoint(&portal_points[i], &temp_vec);
      cc.cc_and &= portal_points[i].p3_codes;
      cc.cc_or |= portal_points[i].p3_codes;
      pointlist[i] = &portal_points[i];
    }

    // Clipped away
    if (cc.cc_and)
      continue;
    if (cc.cc_or) {
      // Must clip
      pl = g3_ClipPolygon(pl, &nv, &cc);

      if (cc.cc_and) {
        g3_FreeTempPoints(pl, nv);
        continue;
      } else {
        for (i = 0; i < nv; i++) {
          temp_points[i + total_points] = *pl[i];
          temp_points[i + total_points].p3_flags &= ~PF_TEMP_POINT;
        }
        g3_FreeTempPoints(pl, nv);
      }
    } else {
      for (i = 0; i < nv; i++) {
        temp_points[i + total_points] = *pl[i];
      }
    }

    for (i = 0; i < nv; i++)
      g3_ProjectPoint(&temp_points[total_points + i]);

    total_points += nv;
  }
  // make new clip window
  clip_wnd new_wnd;
  new_wnd.right = new_wnd.bot = 0.0;
  new_wnd.left = Render_width;
  new_wnd.top = Render_height;
  for (int i = 0; i < total_points; i++) {
    float x = temp_points[i].p3_sx, y = temp_points[i].p3_sy;

    if (x < new_wnd.left)
      new_wnd.left = x;
    if (x > new_wnd.right)
      new_wnd.right = x;
    if (y < new_wnd.top)
      new_wnd.top = y;
    if (y > new_wnd.bot)
      new_wnd.bot = y;
  }
  new_wnd.left = std::max(wnd.left, new_wnd.left);
  new_wnd.right = std::min(wnd.right, new_wnd.right);
  new_wnd.top = std::max(wnd.top, new_wnd.top);
  new_wnd.bot = std::min(wnd.bot, new_wnd.bot);
  /*rend_SetTextureType (TT_FLAT);
  rend_SetAlphaType (AT_CONSTANT);
  rend_SetAlphaValue (255);
  rend_SetFlatColor (GR_RGB(255,255,255));

  rend_DrawLine (new_wnd.left,new_wnd.top,new_wnd.right,new_wnd.top);
  rend_DrawLine (new_wnd.right,new_wnd.top,new_wnd.right,new_wnd.bot);
  rend_DrawLine (new_wnd.right,new_wnd.bot,new_wnd.left,new_wnd.bot);
  rend_DrawLine (new_wnd.left,new_wnd.bot,new_wnd.left,new_wnd.top);*/

  BuildMirroredRoomListSub(Mirror_room, &new_wnd);
}
vector mirror_dest_vecs[MAX_VERTS_PER_ROOM];
g3Point mirror_save_points[MAX_VERTS_PER_ROOM];
// Renders a mirror flipped about the mirrored plane
void RenderMirroredRoom(room *rp) {
  int i;
#if (defined(RELEASE) && defined(KATMAI))
  vector4 kat_vecs[MAX_VERTS_PER_ROOM];
#endif
  uint16_t save_flags[MAX_FACES_PER_ROOM];
  bool restore_index = true;
  int save_index = Global_buffer_index;

  // Save old rotated points
  if (rp->wpb_index == -1) {
    restore_index = false;
    rp->wpb_index = Global_buffer_index;
  } else {
    for (i = 0; i < rp->num_verts; i++)
      mirror_save_points[i] = World_point_buffer[rp->wpb_index + i];
  }

  // Find facing faces for this mirror
  face *fp = &rp->faces[0];
  for (i = 0; i < rp->num_faces; i++, fp++) {
    save_flags[i] = fp->flags;
    fp->flags &= ~FF_NOT_FACING;
    fp->flags |= FF_VISIBLE;
  }
  room *mirror_rp = &Rooms[Mirror_room];
  vector *mirror_vec = &mirror_rp->verts[mirror_rp->faces[mirror_rp->mirror_face].face_verts[0]];
  face *mirror_fp = &mirror_rp->faces[mirror_rp->mirror_face];
  vector *norm = &mirror_fp->normal;
  // This is how far the mirror face is from the normalized plane
  float mirror_dist = -(mirror_vec->x * norm->x + mirror_vec->y * norm->y + mirror_vec->z * norm->z);

  for (i = 0; i < rp->num_verts; i++) {
    vector *vec = &rp->verts[i];
    float dist_from_mirror = vec->x * norm->x + vec->y * norm->y + vec->z * norm->z + mirror_dist;
    // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
    mirror_dest_vecs[i] = *vec - (*norm * (dist_from_mirror * 2));
#if (defined(RELEASE) && defined(KATMAI))
    if (Katmai) {
      kat_vecs[i].x = mirror_dest_vecs[i].x;
      kat_vecs[i].y = mirror_dest_vecs[i].y;
      kat_vecs[i].z = mirror_dest_vecs[i].z;
    }
#endif
  }
  // Rotate our mirror points
  vector revnorm = -*norm;
  g3_SetCustomClipPlane(1, mirror_vec, &revnorm);

  // Katmai enhanced rotate only in a release build, because not
  // everyone has the intel compiler!
#if (defined(RELEASE) && defined(KATMAI))
  if (Katmai)
    RotateRoomPoints(rp, kat_vecs);
  else
#endif
    RotateRoomPoints(rp, mirror_dest_vecs);

  // Mark facing faces
  int save_frame = Facing_visited[rp - std::data(Rooms)];
  Facing_visited[rp - std::data(Rooms)] = 0;

  MarkFacingFaces(rp - std::data(Rooms), mirror_dest_vecs);
  Facing_visited[rp - std::data(Rooms)] = save_frame;
  // Render the mirror room
  rend_SetColorModel(CM_MONO);
  rend_SetLighting(LS_GOURAUD);
  rend_SetWrapType(WT_WRAP);
  RenderRoomUnsorted(rp);
  if (restore_index == false) {
    rp->wpb_index = -1;
  } else {
    for (i = 0; i < rp->num_verts; i++)
      World_point_buffer[rp->wpb_index + i] = mirror_save_points[i];
  }
  fp = &rp->faces[0];
  for (i = 0; i < rp->num_faces; i++, fp++)
    fp->flags = save_flags[i];

  RenderRoomObjects(rp);
  rp->last_render_time = Gametime;
  g3_SetCustomClipPlane(0, NULL, NULL);
}
// Renders a specific room.  If pos_offset is not NULL, adds that offset to each of the
// rooms vertices
void RenderRoom(room *rp) {
  Num_glows_this_frame = 0;

  // Set up rendering states
  rend_SetColorModel(CM_MONO);
  rend_SetLighting(LS_GOURAUD);
  rend_SetWrapType(WT_WRAP);
  if (rp->used == 0) {
    Int3(); // Trying to draw a room that isn't in use!
    return;
  }

  // Figure out pulse lighting for room
  ComputeRoomPulseLight(rp);

  // Mark it visible for automap
  AutomapVisMap[rp - std::data(Rooms)] = 1;

#ifdef EDITOR
  if (!UseHardware) {
    RenderRoomSorted(rp);
  } else
#endif
  {
    // NOTE LINK TO ABOVE ELSE
    RenderRoomUnsorted(rp);
  }

  rp->last_render_time = Gametime;
  rp->flags &= ~RF_MIRROR_VISIBLE;

  CheckLightGlowsForRoom(rp);

  if (Num_scorches_to_render > 0) {
    RenderScorchesForRoom(rp);
    Num_scorches_to_render = 0;
  }

  if (Num_specular_faces_to_render > 0) {
    RenderSpecularFacesFlat(rp);
    Num_specular_faces_to_render = 0;
    Num_real_specular_faces_to_render = 0;
  }

  if (Num_fog_faces_to_render > 0) {
    RenderFogFaces(rp);
    Num_fog_faces_to_render = 0;
  }
}

#define MAX_OBJECTS_PER_ROOM 2000
struct obj_sort_item {
  int vis_effect;
  int objnum;
  float dist;
};
obj_sort_item obj_sort_list[MAX_OBJECTS_PER_ROOM];
// Compare function for room face sort
static int obj_sort_func(const obj_sort_item *a, const obj_sort_item *b) {
  if (a->dist < b->dist)
    return -1;
  else if (a->dist > b->dist)
    return 1;
  else
    return 0;
}
static inline void IsRoomDynamicValid(room *rp, int x, int y, int z, float *r, float *g, float *b) {
  int w = rp->volume_width;
  int h = rp->volume_height;
  int d = rp->volume_depth;

  uint8_t color = rp->volume_lights[(z * w * h) + (y * w) + x];

  *r = (float)((color >> 5) / 7.0);
  *g = (float)((color >> 2) & 0x07) / 7.0;
  *b = (float)((float)(color & 0x03) / 3.0);
}
// Gets the dynamic light value for this position
void GetRoomDynamicScalar(vector *pos, room *rp, float *r, float *g, float *b) {
  float front_values_r[10];
  float back_values_r[10];
  float front_values_g[10];
  float back_values_g[10];
  float front_values_b[10];
  float back_values_b[10];
  if (!rp->volume_lights) {
    *r = 1;
    *g = 1;
    *b = 1;
    return;
  }
  float fl_x = (pos->x - rp->min_xyz.x) / VOLUME_SPACING;
  float fl_y = (pos->y - rp->min_xyz.y) / VOLUME_SPACING;
  float fl_z = (pos->z - rp->min_xyz.z) / VOLUME_SPACING;
  fl_x = std::max<float>(fl_x, 0);
  fl_y = std::max<float>(fl_y, 0);
  fl_z = std::max<float>(fl_z, 0);
  fl_x = std::min<float>(fl_x, rp->volume_width - 1);
  fl_y = std::min<float>(fl_y, rp->volume_height - 1);
  fl_z = std::min<float>(fl_z, rp->volume_depth - 1);
  int int_x = fl_x;
  int int_y = fl_y;
  int int_z = fl_z;
  fl_x -= int_x;
  fl_y -= int_y;
  fl_z -= int_z;
  int next_x = int_x + 1;
  int next_y = int_y + 1;
  int next_z = int_z + 1;
  next_x = std::min(rp->volume_width - 1, next_x);
  next_y = std::min(rp->volume_height - 1, next_y);
  next_z = std::min(rp->volume_depth - 1, next_z);

  float left_norm_r, left_norm_g, left_norm_b;
  float right_norm_r, right_norm_g, right_norm_b;
  float front_norm_r, front_norm_g, front_norm_b;
  float back_norm_r, back_norm_g, back_norm_b;

  IsRoomDynamicValid(rp, int_x, int_y, int_z, &front_values_r[0], &front_values_g[0], &front_values_b[0]);
  IsRoomDynamicValid(rp, int_x, next_y, int_z, &front_values_r[1], &front_values_g[1], &front_values_b[1]);
  IsRoomDynamicValid(rp, next_x, next_y, int_z, &front_values_r[2], &front_values_g[2], &front_values_b[2]);
  IsRoomDynamicValid(rp, next_x, int_y, int_z, &front_values_r[3], &front_values_g[3], &front_values_b[3]);
  IsRoomDynamicValid(rp, int_x, int_y, next_z, &back_values_r[0], &back_values_g[0], &back_values_b[0]);
  IsRoomDynamicValid(rp, int_x, next_y, next_z, &back_values_r[1], &back_values_g[1], &back_values_b[1]);
  IsRoomDynamicValid(rp, next_x, next_y, next_z, &back_values_r[2], &back_values_g[2], &back_values_b[2]);
  IsRoomDynamicValid(rp, next_x, int_y, next_z, &back_values_r[3], &back_values_g[3], &back_values_b[3]);
  // Do front edge
  int left_out = 0;
  int right_out = 0;
  // Left edge
  left_norm_r = ((1 - fl_y) * front_values_r[0]) + (fl_y * front_values_r[1]);
  left_norm_g = ((1 - fl_y) * front_values_g[0]) + (fl_y * front_values_g[1]);
  left_norm_b = ((1 - fl_y) * front_values_b[0]) + (fl_y * front_values_b[1]);

  // Right edge
  right_norm_r = ((1 - fl_y) * front_values_r[3]) + (fl_y * front_values_r[2]);
  right_norm_g = ((1 - fl_y) * front_values_g[3]) + (fl_y * front_values_g[2]);
  right_norm_b = ((1 - fl_y) * front_values_b[3]) + (fl_y * front_values_b[2]);
  // Figure out front edge
  front_norm_r = ((1 - fl_x) * left_norm_r) + (fl_x * right_norm_r);
  front_norm_g = ((1 - fl_x) * left_norm_g) + (fl_x * right_norm_g);
  front_norm_b = ((1 - fl_x) * left_norm_b) + (fl_x * right_norm_b);

  // Do back edge
  left_norm_r = ((1 - fl_y) * back_values_r[0]) + (fl_y * back_values_r[1]);
  left_norm_g = ((1 - fl_y) * back_values_g[0]) + (fl_y * back_values_g[1]);
  left_norm_b = ((1 - fl_y) * back_values_b[0]) + (fl_y * back_values_b[1]);

  right_norm_r = ((1 - fl_y) * back_values_r[3]) + (fl_y * back_values_r[2]);
  right_norm_g = ((1 - fl_y) * back_values_g[3]) + (fl_y * back_values_g[2]);
  right_norm_b = ((1 - fl_y) * back_values_b[3]) + (fl_y * back_values_b[2]);
  back_norm_r = ((1 - fl_x) * left_norm_r) + (fl_x * right_norm_r);
  back_norm_g = ((1 - fl_x) * left_norm_g) + (fl_x * right_norm_g);
  back_norm_b = ((1 - fl_x) * left_norm_b) + (fl_x * right_norm_b);
  *r = ((1 - fl_z) * front_norm_r) + (fl_z * back_norm_r);
  *g = ((1 - fl_z) * front_norm_g) + (fl_z * back_norm_g);
  *b = ((1 - fl_z) * front_norm_b) + (fl_z * back_norm_b);
  // Factor in flickering
  ComputeRoomPulseLight(rp);
  (*r) *= Room_light_val;
  (*g) *= Room_light_val;
  (*b) *= Room_light_val;
}
uint8_t Trick_type = 0;
// Render the objects and viseffects in a room.  Do a simple sort
void RenderRoomObjects(room *rp) {
  int n_objs = 0, objnum, i, visnum;
  float zdist;
  if (!Render_mirror_for_room && UseHardware)
    return; // This function only works for mirrors now

  // Add objects to sort list
  for (objnum = rp->objects; (objnum != -1) && (n_objs < MAX_OBJECTS_PER_ROOM); objnum = Objects[objnum].next) {
    ASSERT(objnum != Objects[objnum].next);
    object *obj = &Objects[objnum];

    if (obj->render_type == RT_NONE)
      continue;
    if (obj == Viewer_object && !Render_mirror_for_room)
      continue;
    float size = obj->size;
    // Special case weapons with streamers
    if (obj->type == OBJ_WEAPON && (Weapons[obj->id].flags & WF_STREAMER))
      size = Weapons[obj->id].phys_info.velocity.z;
    // Check if object is trivially rejected
    bool isVisible = IsPointVisible(&obj->pos, size, &zdist) ? true : false;
    if (Render_mirror_for_room || (obj->type == OBJ_WEAPON && Weapons[obj->id].flags & WF_ELECTRICAL) || isVisible) {
      obj_sort_list[n_objs].vis_effect = 0;
      obj_sort_list[n_objs].objnum = objnum;
      obj_sort_list[n_objs].dist = zdist;
      n_objs++;
    }
  }
  // Add vis effects to sort list
  for (visnum = rp->vis_effects; (visnum != -1) && (n_objs < MAX_OBJECTS_PER_ROOM); visnum = VisEffects[visnum].next) {
    ASSERT(visnum != VisEffects[visnum].next);
    if (VisEffects[visnum].type == VIS_NONE || VisEffects[visnum].flags & VF_DEAD)
      continue;

    bool pointIsVisible = IsPointVisible(&VisEffects[visnum].pos, VisEffects[visnum].size, &zdist) ? true : false;
    if (Render_mirror_for_room || pointIsVisible) {
      obj_sort_list[n_objs].vis_effect = 1;
      obj_sort_list[n_objs].objnum = visnum;
      obj_sort_list[n_objs].dist = zdist;
      n_objs++;
    }
  }
  ASSERT(objnum == -1); // if not -1, ran out of space in render_order[]
  ASSERT(visnum == -1); // if not -1, ran out of space in render_order[]
  // Sort the objects
  qsort(obj_sort_list, n_objs, sizeof(*obj_sort_list), (int (*)(const void *, const void *))obj_sort_func);
#ifdef _DEBUG
  bool save_polymodel_outline_mode = Polymodel_outline_mode;
  Polymodel_outline_mode = OUTLINE_ON(OM_OBJECTS);
#endif
  // Render the objects
  if (UseHardware && Render_mirror_for_room) {
    // Render the mirror stuff if present
    room *mirror_rp = &Rooms[Mirror_room];
    vector *mirror_vec = &mirror_rp->verts[mirror_rp->faces[mirror_rp->mirror_face].face_verts[0]];
    face *mirror_fp = &mirror_rp->faces[mirror_rp->mirror_face];
    vector *norm = &mirror_fp->normal;
    // This is how far the mirror face is from the normalized plane
    float mirror_dist = -(mirror_vec->x * norm->x + mirror_vec->y * norm->y + mirror_vec->z * norm->z);
    // Setup mirror matrix

    vector negz_vec = {0, 0, -1};

    matrix mirror_matrix, inv_mirror_matrix, dest_matrix, negz_matrix;
    vm_VectorToMatrix(&mirror_matrix, norm, NULL, NULL);
    inv_mirror_matrix = mirror_matrix;
    vm_TransposeMatrix(&inv_mirror_matrix);
    vm_VectorToMatrix(&negz_matrix, &negz_vec, NULL, NULL);
    negz_matrix.rvec *= -1;

    for (i = n_objs - 1; i >= 0; i--) {
      objnum = obj_sort_list[i].objnum;
      if (obj_sort_list[i].vis_effect) {
        vis_effect *vis = &VisEffects[objnum];
        vector save_vec = vis->pos;
        vector save_end_vec = vis->end_pos;
        vector *vec = &vis->pos;
        vector *end_vec = &vis->end_pos;
        float dist_from_mirror = vec->x * norm->x + vec->y * norm->y + vec->z * norm->z + mirror_dist;
        // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
        vis->pos = *vec - (*norm * (dist_from_mirror * 2));
        dist_from_mirror = end_vec->x * norm->x + end_vec->y * norm->y + end_vec->z * norm->z + mirror_dist;
        // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
        vis->end_pos = *end_vec - (*norm * (dist_from_mirror * 2));

        DrawVisEffect(vis);
        vis->pos = save_vec;
        vis->end_pos = save_end_vec;
      } else {
        object *objp = &Objects[objnum];

        vector save_vec = objp->pos;
        matrix save_orient = objp->orient;
        matrix temp_mat;

        vector *vec = &objp->pos;
        float dist_from_mirror = vec->x * norm->x + vec->y * norm->y + vec->z * norm->z + mirror_dist;
        // dest_vecs contains the point on the other side of the mirror (ie the reflected point)
        objp->pos = *vec - (*norm * (dist_from_mirror * 2));
        // Check for rear view
        if (objp == Viewer_object && Viewer_object == Player_object &&
            (Players[Player_num].flags & PLAYER_FLAGS_REARVIEW)) {
          objp->orient.fvec = -objp->orient.fvec;
          objp->orient.rvec = -objp->orient.rvec;
        }
        // Get new orientation
        temp_mat = mirror_matrix * negz_matrix * inv_mirror_matrix;
        dest_matrix.rvec = objp->orient.rvec * temp_mat;
        dest_matrix.uvec = objp->orient.uvec * temp_mat;
        dest_matrix.fvec = objp->orient.fvec * temp_mat;
        objp->orient = dest_matrix;
        bool save_render = false;
        if (objp->flags & OF_SAFE_TO_RENDER)
          save_render = true;
        objp->flags |= OF_SAFE_TO_RENDER;

        RenderObject(objp);
        if (save_render)
          objp->flags |= OF_SAFE_TO_RENDER;
        else
          objp->flags &= ~OF_SAFE_TO_RENDER;
        objp->pos = save_vec;
        objp->orient = save_orient;
      }
    }
    return;
  }
  for (i = n_objs - 1; i >= 0; i--) {
    objnum = obj_sort_list[i].objnum;
    if (obj_sort_list[i].vis_effect) {
      DrawVisEffect(&VisEffects[objnum]);
    } else {
      object *objp = &Objects[objnum];
      if (objp == Viewer_object)
        continue;
      RenderObject(objp);
    }
  }
#ifdef _DEBUG
  Polymodel_outline_mode = save_polymodel_outline_mode;
#endif
}
// Either renders the objects in a room, or stuffs them into our postrender list
void CheckToRenderMineObjects(int roomnum) {

  if (UseHardware) {
    int index;
    float zdist;
    if (Render_mirror_for_room)
      return;
    for (index = Rooms[roomnum].objects; index != -1; index = Objects[index].next) {
      object *obj = &Objects[index];
      if (Objects[index].render_type == RT_NONE)
        continue;
      if (obj == Viewer_object)
        continue;
      // Don't draw piggybacked objects
      if (Viewer_object->type == OBJ_OBSERVER && index == Players[Viewer_object->id].piggy_objnum)
        continue;
      float size = Objects[index].size;
      // Special case weapons with streamers
      if (Objects[index].type == OBJ_WEAPON && (Weapons[Objects[index].id].flags & WF_STREAMER))
        size = Weapons[Objects[index].id].phys_info.velocity.z;
      // Check if object is trivially rejected
      int visible = IsPointVisible(&obj->pos, size, &zdist); // calculate zdist
      if ((obj->type == OBJ_WEAPON && Weapons[obj->id].flags & WF_ELECTRICAL) || visible) {
        if (Num_postrenders < MAX_POSTRENDERS) {
          Postrender_list[Num_postrenders].type = PRT_OBJECT;
          Postrender_list[Num_postrenders].z = zdist;
          Postrender_list[Num_postrenders++].objnum = index;
        }
      }
    }
    // Now do viseffects
    for (index = Rooms[roomnum].vis_effects; index != -1; index = VisEffects[index].next) {
      if (VisEffects[index].type == VIS_NONE || VisEffects[index].flags & VF_DEAD)
        continue;

      if (IsPointVisible(&VisEffects[index].pos, VisEffects[index].size, &zdist)) {
        if (Num_postrenders < MAX_POSTRENDERS) {
          Postrender_list[Num_postrenders].type = PRT_VISEFFECT;
          Postrender_list[Num_postrenders].z = zdist;
          Postrender_list[Num_postrenders++].visnum = index;
        }
      }
    }
  } else
    RenderRoomObjects(&Rooms[roomnum]);
}
// Renders all the mirrored rooms for this frame
void RenderMirrorRooms() {
  int i;
  if (!UseHardware || !Detail_settings.Mirrored_surfaces)
    return;
  if (Num_mirror_rooms == 0)
    return;
  for (i = 0; i < Num_mirror_rooms; i++) {
    room *rp = &Rooms[Mirror_rooms[i]];
    // Reset mirrors
    Render_mirror_for_room = false;
    bool do_mirror_face = false;
    rp->flags &= ~RF_MIRROR_VISIBLE;
    // Make sure its really ok to render this mirrored room
    if (rp->mirror_face != -1)
      do_mirror_face = true;
    if (rp->mirror_face >= rp->num_faces)
      do_mirror_face = false;
    if (do_mirror_face) {
      if (!(GameTextures[rp->faces[rp->mirror_face].tmap].flags & TF_ALPHA))
        do_mirror_face = false;
    }
    if (do_mirror_face) {
      int on_screen = 0;
      // See if any of the faces that share the mirror texture are on the screen
      for (int k = 0; k < rp->num_mirror_faces && on_screen == 0; k++) {
        face *fp = &rp->faces[rp->mirror_faces_list[k]];

        // See if this face is on screen
        int anded = 0xff;
        g3Point pnt;
        for (int t = 0; t < fp->num_verts; t++)
          anded &= g3_RotatePoint(&pnt, &rp->verts[fp->face_verts[t]]);
        if (!anded)
          on_screen = 1;
      }
      if (!on_screen)
        do_mirror_face = false;
    }
    if (do_mirror_face) // This room has a mirror...render it first
    {
      Render_mirror_for_room = true;
      Mirror_room = rp - std::data(Rooms);

      BuildMirroredRoomList();
      for (int t = Num_mirrored_rooms - 1; t >= 0; t--)
        RenderMirroredRoom(&Rooms[Mirrored_room_list[t]]);
      Render_mirror_for_room = false;
    }
  }
  // Do z buffer trick
  rend_ClearZBuffer();
  rend_SetZBufferWriteMask(1);
  rend_SetZBufferState(1);
  // Draw mirror faces now
  for (i = 0; i < Num_mirror_rooms; i++) {
    room *rp = &Rooms[Mirror_rooms[i]];
    face *fp = &rp->faces[rp->mirror_face];
    g3Point save_points[MAX_VERTS_PER_FACE];
    int save_index;

    // Now do the same for all faces in this room that share that texture of the mirror
    for (int k = 0; k < rp->num_faces; k++) {
      face *this_fp = &rp->faces[k];
      if (this_fp->tmap == fp->tmap) {
        int t;

        save_index = rp->wpb_index;
        for (t = 0; t < fp->num_verts; t++)
          save_points[t] = World_point_buffer[fp->face_verts[t]];
        DrawPostrenderFace(Mirror_rooms[i], rp->mirror_face, false);

        rp->wpb_index = save_index;
        for (t = 0; t < fp->num_verts; t++)
          World_point_buffer[fp->face_verts[t]] = save_points[t];
      }
    }
  }
}
//	Renders a room in just outline form
void RenderRoomOutline(room *rp) {
  int fn;
  ddgr_color back_line_color, face_line_color;
  back_line_color = GR_RGB(100, 100, 100);
  face_line_color = GR_RGB(255, 255, 255);
  for (fn = 0; fn < rp->num_faces; fn++) {
    face *fp = &rp->faces[fn];
    g3Point p0, p1;
    uint8_t c0, c1;
    int v;
    ddgr_color color;
    for (v = 0; v < fp->num_verts; v++) {
      c0 = g3_RotatePoint(&p0, &rp->verts[fp->face_verts[v]]);
      c1 = g3_RotatePoint(&p1, &rp->verts[fp->face_verts[(v + 1) % fp->num_verts]]);
      if ((!(fp->flags & FF_VISIBLE)) || ((fp->flags & FF_NOT_FACING))) {
        // wouldn't normally be rendered
        color = back_line_color;
      } else {
        color = face_line_color;
      }
      if (!(c0 & c1)) { // both not off screen?
        // Draw current edge in green
        g3_DrawLine(color, &p0, &p1);
      }
    }
  }
}
// Draws the mine, starting at a the specified room
// The rendering surface must be set up, and g3_StartFrame() must have been called
// Parameters:	viewer_roomnum - what room the viewer is in
//					flag_automap - if true, flag segments as visited when rendered
//					called_from_terrain - set if calling this routine from the terrain renderer
void RenderMine(int viewer_roomnum, int flag_automap, int called_from_terrain) {
#ifdef EDITOR
  In_editor_mode = (GetFunctionMode() == EDITOR_MODE);
#endif
  // check to see if we should render windows
  if (No_render_windows_hack == -1) {
    if (FindArg("-NoRenderWindows"))
      No_render_windows_hack = 1;
    else
      No_render_windows_hack = 0;
  }
  // Get the viewer eye so functions down the line can look at it
  g3_GetViewPosition(&Viewer_eye);
  g3_GetUnscaledMatrix(&Viewer_orient);
  // set these globals so functions down the line can look at them
  Viewer_roomnum = viewer_roomnum;
  Flag_automap = flag_automap;
  Called_from_terrain = called_from_terrain;
  // Assume no terrain
  Must_render_terrain = 0;

  // Get the width & height of the render window
  rend_GetProjectionParameters(&Render_width, &Render_height);
  if (!Called_from_terrain) {
    Terrain_portal_top = Render_height;
    Terrain_portal_bottom = 0;
    Terrain_portal_right = 0;
    Terrain_portal_left = Render_width;
  }
  // Build the list of visible rooms
  BuildRoomList(viewer_roomnum); // fills in Render_list & N_render_segs

  // If we determined that the terrain is visible, render it
  if (Must_render_terrain && !Called_from_terrain && !(In_editor_mode && Render_inside_only)) {
    RenderTerrain(1, Terrain_portal_left, Terrain_portal_top, Terrain_portal_right, Terrain_portal_bottom);
    // Mark all room points to be rerotated due to terrain trashing our point list
    for (int i = 0; i <= Highest_room_index; i++) {
      Rooms[i].wpb_index = -1;
      Global_buffer_index = 0;
    }
    // Setup fog if needed
    g3_SetFarClipZ(VisibleTerrainZ);

    if ((Terrain_sky.flags & TF_FOG) && (UseHardware || (!UseHardware && Lighting_on))) {
      rend_SetZValues(0, VisibleTerrainZ);
      rend_SetFogState(1);
      rend_SetFogBorders(VisibleTerrainZ * .85, VisibleTerrainZ);
      rend_SetFogColor(Terrain_sky.fog_color);
    } else
      rend_SetZValues(0, 5000);
  }

  // First render mirrored rooms
  RenderMirrorRooms();

  Num_mirror_rooms = 0;

  // Render the list of rooms
  for (int nn = N_render_rooms - 1; nn >= 0; nn--) {
    int roomnum;
    roomnum = Render_list[nn];
#ifdef _DEBUG
    if (In_editor_mode && Render_one_room_only && (roomnum != viewer_roomnum))
      continue;
#endif
    if (roomnum != -1) {
      ASSERT(Rooms_visited[roomnum] != 255);
      if (Outline_release_mode & 1) {
        RenderRoomOutline(&Rooms[roomnum]);
      }
      RenderRoom(&Rooms[roomnum]);
      Rooms_visited[roomnum] = (char)255;
      // Stuff objects into our postrender list
      CheckToRenderMineObjects(roomnum);
    }
  }
  rend_SetOverlayType(OT_NONE); // turn off lightmap blending
  if (Must_render_terrain && !Called_from_terrain)
    rend_SetFogState(0);

#ifdef EDITOR
  if (OUTLINE_ON(OM_MINE)) {
    OutlineCurrentFace(Curroomp, Curface, Curedge, Curvert, CURFACE_COLOR, CUREDGE_COLOR);
    if (Markedroomp)
      OutlineCurrentFace(Markedroomp, Markedface, Markededge, Markedvert, MARKEDFACE_COLOR, MARKEDEDGE_COLOR);
    if (Placed_room != -1)
      DrawPlacedRoomFace(&Rooms[Placed_room], &Placed_room_origin, &Placed_room_rotmat, &Placed_room_attachpoint,
                         Placed_room_face, PLACED_COLOR);
  }
#endif
}
// Simply sets the number of glows to zero
void ResetLightGlows() {
  Num_glows = 0;
  for (int i = 0; i < MAX_LIGHT_GLOWS; i++) {
    LightGlows[i].flags = 0;
  }
}
// Renders all the lights glows for this frame
void RenderLightGlows() {
  if (!UseHardware)
    return;
  // Render all the glows for this mine
  rend_SetColorModel(CM_RGB);
  rend_SetLighting(LS_GOURAUD);
  rend_SetTextureType(TT_LINEAR);
  rend_SetAlphaType(AT_SATURATE_TEXTURE);
  rend_SetOverlayType(OT_NONE);
  rend_SetFogState(0);
  int count = 0;

  for (int i = 0; i < MAX_LIGHT_GLOWS && count < Num_glows; i++) {
    if (LightGlows[i].flags & LGF_USED) {
      RenderSingleLightGlow(i);
      count++;
    }
  }

  rend_SetZBufferWriteMask(1);
  rend_SetZBufferState(1);
}

/*
// Sets fogzone start and end points
void SetFogZoneStart(float z)
{
        Fog_zone_start=z;
}
void SetFogZoneEnd (float z)
{
        Fog_zone_end=z;
}
g3Point SolidFogPoints[128],AlphaFogPoints[128];
// Adds a point to the fog zone face
void FogClipPoints (g3Point *on_pnt,g3Point *off_pnt,g3Point *dest,float zval,int ending)
{
        float z_on,z_off;
        float k;
        g3Point *tmp=dest;
        tmp->p3_flags=0;
        z_on=on_pnt->p3_z;
        z_off=off_pnt->p3_z;
        k = 1.0-((z_off-zval) / (z_off-z_on));
        tmp->p3_z = on_pnt->p3_z + ((off_pnt->p3_z-on_pnt->p3_z) * k);

        tmp->p3_x = on_pnt->p3_x + ((off_pnt->p3_x-on_pnt->p3_x) * k);
        tmp->p3_y = on_pnt->p3_y + ((off_pnt->p3_y-on_pnt->p3_y) * k);
        if (on_pnt->p3_flags & PF_UV) {
                tmp->p3_u = on_pnt->p3_u + ((off_pnt->p3_u-on_pnt->p3_u) * k);
                tmp->p3_v = on_pnt->p3_v + ((off_pnt->p3_v-on_pnt->p3_v) * k);
                tmp->p3_flags |= PF_UV;
        }
        if (on_pnt->p3_flags & PF_UV2) {
                tmp->p3_u2 = on_pnt->p3_u2 + ((off_pnt->p3_u2-on_pnt->p3_u2) * k);
                tmp->p3_v2 = on_pnt->p3_v2 + ((off_pnt->p3_v2-on_pnt->p3_v2) * k);
                tmp->p3_flags |= PF_UV2;
        }
        if (on_pnt->p3_flags & PF_L) {
                tmp->p3_l = on_pnt->p3_l + ((off_pnt->p3_l-on_pnt->p3_l) * k);
                tmp->p3_flags |= PF_L;
        }
        if (on_pnt->p3_flags & PF_RGBA) {
                tmp->p3_r = on_pnt->p3_r + ((off_pnt->p3_r-on_pnt->p3_r) * k);
                tmp->p3_g = on_pnt->p3_g + ((off_pnt->p3_g-on_pnt->p3_g) * k);
                tmp->p3_b = on_pnt->p3_b + ((off_pnt->p3_b-on_pnt->p3_b) * k);
                tmp->p3_flags |= PF_RGBA;
        }
        if (ending)
                tmp->p3_a = 0.0;
        else
                tmp->p3_a = 1.0;
        g3_CodePoint(tmp);
}
*/

#define STATE_PUSH(val)                                                                                                \
  {                                                                                                                    \
    state_stack[state_stack_counter] = val;                                                                            \
    state_stack_counter++;                                                                                             \
    ASSERT(state_stack_counter < 2000);                                                                                \
  }
#define STATE_POP()                                                                                                    \
  {                                                                                                                    \
    state_stack_counter--;                                                                                             \
    pop_val = state_stack[state_stack_counter];                                                                        \
  }
// Sorts our texture states using the quicksort algorithm
void SortStates(state_limited_element *state_array, int cellcount) {
  state_limited_element v, t;
  int pop_val;
  int i, j;
  int l, r;
  l = 0;
  r = cellcount - 1;
  uint16_t state_stack_counter = 0;
  uint16_t state_stack[2000];

  while (1) {
    while (r > l) {
      i = l - 1;
      j = r;
      v = state_array[r];
      while (1) {
        while (state_array[++i].sort_key < v.sort_key)
          ;
        while (state_array[--j].sort_key > v.sort_key)
          ;
        if (i >= j)
          break;
        t = state_array[i];
        state_array[i] = state_array[j];
        state_array[j] = t;
      }
      t = state_array[i];
      state_array[i] = state_array[r];
      state_array[r] = t;

      if (i - l > r - i) {
        STATE_PUSH(l);
        STATE_PUSH(i - 1);
        l = i + 1;
      } else {
        STATE_PUSH(i + 1);
        STATE_PUSH(r);
        r = i - 1;
      }
    }
    if (!state_stack_counter)
      break;
    STATE_POP();
    r = pop_val;
    STATE_POP();
    l = pop_val;
  }
}
// Builds a list of mirror faces for each room and allocs memory accordingly
void ConsolidateMineMirrors() {
  int i, t;
  mprintf(0, "Consolidating mine mirrors!\n");
  for (i = 0; i < MAX_ROOMS; i++) {
    room *rp = &Rooms[i];
    if (!rp->used)
      continue;
    if (rp->mirror_faces_list) {
      mem_free(rp->mirror_faces_list);
      rp->mirror_faces_list = NULL;
      rp->num_mirror_faces = 0;
    }
    if (rp->mirror_face == -1)
      continue;
    // Count the number of faces that have the same texture as the mirror face
    int num_mirror_faces = 0;
    for (t = 0; t < rp->num_faces; t++) {
      face *fp = &rp->faces[t];
      if (fp->tmap == rp->faces[rp->mirror_face].tmap)
        num_mirror_faces++;
    }
    if (num_mirror_faces == 0) {
      // No faces found?  Weird.
      rp->mirror_face = 0;
      continue;
    }
    rp->mirror_faces_list = (uint16_t *)mem_malloc(num_mirror_faces * sizeof(uint16_t));
    ASSERT(rp->mirror_faces_list);
    rp->num_mirror_faces = num_mirror_faces;
    // Now go through and fill in our list
    int count = 0;
    for (t = 0; t < rp->num_faces; t++) {
      face *fp = &rp->faces[t];
      if (fp->tmap == rp->faces[rp->mirror_face].tmap)
        rp->mirror_faces_list[count++] = t;
    }
  }
}

/*
// Takes a face and adds the appropriate vertices for drawing in the fog zone
// Returns number of points in new polygon
// New polygon points are in FogPoints array
int FogBlendFace (g3Point **src,int nv,int *num_solid,int *num_alpha)
{
        int alpha_nv=0,solid_nv=0,temp_nv=0;
        g3Point temp_buf[128],temp_pnt;
        float fog_zone_range=Fog_zone_end-Fog_zone_start;
        int i;

        for (i=0;i<nv;i++)
        {
                int next=(i+1)%nv;
                int prev=i-1;
                if (prev<0)
                        prev=nv-1;
                g3Point *thispnt=src[i];
                g3Point *nextpnt=src[next];
                g3Point *prevpnt=src[prev];
                if (thispnt->p3_z>Fog_zone_end)
                {
                        if (prevpnt->p3_z<Fog_zone_end)
                        {
                                FogClipPoints (prevpnt,thispnt,&temp_buf[temp_nv],Fog_zone_end,1);
                                temp_nv++;
                        }
                        if (nextpnt->p3_z<Fog_zone_end)
                        {
                                FogClipPoints (nextpnt,thispnt,&temp_buf[temp_nv],Fog_zone_end,1);
                                temp_nv++;
                        }
                }
                else
                {
                        temp_buf[temp_nv]=*thispnt;
                        temp_buf[temp_nv].p3_a=0;
                        temp_nv++;
                }
        }
        // At this stage all vertices are clipped to be nearer that Fog_zone_end
        nv=temp_nv;
        for (i=0;i<nv;i++)
        {
                int next=(i+1)%nv;
                int prev=i-1;
                if (prev<0)
                        prev=nv-1;
                g3Point *thispnt=&temp_buf[i];
                g3Point *nextpnt=&temp_buf[next];
                g3Point *prevpnt=&temp_buf[prev];
                if (thispnt->p3_z>Fog_zone_start)
                {
                        if (prevpnt->p3_z<Fog_zone_start)
                        {
                                FogClipPoints (prevpnt,thispnt,&temp_pnt,Fog_zone_start,0);
                                SolidFogPoints[solid_nv]=temp_pnt;
                                solid_nv++;
                                AlphaFogPoints[alpha_nv]=temp_pnt;
                                alpha_nv++;
                        }
                        // Add this point to the list
                        //---------------------------
                        float alpha=1.0-((thispnt->p3_z-Fog_zone_start)/fog_zone_range);
                        if (alpha<0)
                                alpha=0;
                        ASSERT (alpha<=1.0);
                        AlphaFogPoints[alpha_nv]=*thispnt;
                        AlphaFogPoints[alpha_nv].p3_a=alpha;
                        alpha_nv++;
                        //------------------------------
                        if (nextpnt->p3_z<Fog_zone_start)
                        {
                                FogClipPoints (nextpnt,thispnt,&temp_pnt,Fog_zone_start,0);
                                SolidFogPoints[solid_nv]=temp_pnt;
                                solid_nv++;
                                AlphaFogPoints[alpha_nv]=temp_pnt;
                                alpha_nv++;

                        }
                }
                else
                {
                        SolidFogPoints[solid_nv]=*thispnt;
                        SolidFogPoints[solid_nv].p3_a=1.0;
                        solid_nv++;
                }
        }
        *num_alpha=alpha_nv;
        *num_solid=solid_nv;
        return (solid_nv>0);
}
*/

// RenderBlankScreen
//	Renders a blank screen, to be used for UI callbacks to prevent Hall of mirrors with mouse cursor
void RenderBlankScreen(void) { rend_ClearScreen(GR_BLACK); }
#ifdef EDITOR
// Finds what room & face is visible at a given screen x & y
// Everything must be set up just like for RenderMineRoom(), and presumably is the same as
// for the last frame rendered (though it doesn't have to be)
// Parameters:	x,y - the screen coordinates
//					start_roomnum - where to start rendering
//					roomnum,facenum - these are filled in with the found values
//					if room<0, then an object was found, and the object number is -room-1
// Returns:		1 if found a room, else 0
/*int FindRoomFace(int16_t x,int16_t y,int start_roomnum,int *roomnum,int *facenum)
{
        //Init search mode
        search_mode = -1;
        search_x = x; search_y = y;
        found_room = INT_MAX;
        //Render and search
        RenderMine(start_roomnum,0,0);
        //Turn search off
        search_mode = 0;
        //Set return values
        *roomnum = found_room;
        *facenum = found_face;
        return (found_room != INT_MAX);
}*/
// finds what room,face,lumel is visible at a given screen x & y
// Everything must be set up just like for RenderMineRoom(), and presumably is the same as
// for the last frame rendered (though it doesn't have to be)
// Parameters:	x,y - the screen coordinates
//					start_roomnum - where to start rendering
//					roomnum,facenum,lumel_num - these are filled in with the found values
// Returns:		1 if found a room, else 0
/*int FindLightmapFace(int16_t x,int16_t y,int start_roomnum,int *roomnum,int *facenum,int *lumel_num)
{
        Search_lightmaps=1;
        search_x = x; search_y = y;
        found_room = INT_MAX;
        //Get the width & height of the render window
        rend_GetProjectionParameters(&Render_width,&Render_height);
        RenderMine(start_roomnum,0,0);
        Search_lightmaps=0;
        *roomnum = found_room;
        *facenum = found_face;
        *lumel_num=found_lightmap;
        return (found_room != INT_MAX);
}*/
#endif
