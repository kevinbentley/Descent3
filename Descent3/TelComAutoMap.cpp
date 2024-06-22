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

 * $Logfile: /DescentIII/main/TelComAutoMap.cpp $
 * $Revision: 37 $
 * $Date: 7/20/99 4:59p $
 * $Author: Samir $
 *
 * TelCom Automap
 *
 * $Log: /DescentIII/main/TelComAutoMap.cpp $
 *
 * 37    7/20/99 4:59p Samir
 * automap key will close automap.
 *
 * 36    5/13/99 3:42p Ardussi
 * changes for compiling on the Mac
 *
 * 35    4/24/99 6:46p Jeff
 * added functions for theif so he can steal things other than weapons
 *
 * 34    4/24/99 5:45p Matt
 * Made the marker message use a localizable string.
 *
 * 33    4/24/99 1:54a Matt
 * Changed to use briefing font for labels at bottom, and HUD font for
 * name at top.
 *
 * 32    4/14/99 11:44a Jason
 * fixes for secret rooms
 *
 * 31    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 30    4/11/99 2:24p Kevin
 * made AM_rotated_points dynamically allocated so it's only used if you
 * go into the automap. Should help dedicated servers quite a bit.
 *
 * 29    4/02/99 5:42p Jason
 * display level info name instead of current level name.  Confused?
 * Yeah, so am I.
 *
 * 28    4/01/99 5:58p Jason
 * automap now tells you exactly where you haven't gone yet...dunno if
 * this is a good thing.  If enough people bitch then I will change it.
 *
 * 27    3/31/99 5:29p Jeff
 * new way of key processesing...can capture printscreen now
 *
 * 26    3/29/99 7:30p Jason
 * added fading doors
 *
 * 25    2/25/99 11:02p Jeff
 * fixed automap rendering
 *
 * 24    2/24/99 6:23p Samir
 * poll controls if in automap, not suspend and resume per frame.
 *
 * 23    2/22/99 3:37p Jason
 * fixed markers in telcom
 *
 * 22    2/15/99 5:32p Jason
 * made ship blink in automap
 *
 * 21    2/01/99 4:35p Jeff
 * tab exits the automap
 *
 * 20    1/29/99 7:13p Jeff
 * localization
 *
 * 19    1/29/99 11:29a Jason
 * added misc bug fixes/features
 *
 * 18    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 17    12/23/98 3:08p Jason
 * added new player ship
 *
 * 16    12/16/98 4:17p Jason
 * draw external rooms no matter what
 *
 * 15    12/15/98 4:39p Jason
 * added some more telcom functions
 *
 * 14    12/14/98 11:57a Jason
 * changes for visibile automap
 *
 * 13    12/14/98 11:06a Jason
 * changes for 1.1
 *
 * 12    12/11/98 11:37a Jason
 *
 * 11    12/09/98 2:52p Jason
 * fixed automap problem on terrain
 *
 * 10    12/09/98 2:36p Jeff
 * added function to enable/disable telcom system keys and disabled most
 * system keys while in Automap
 *
 * 9     12/09/98 1:09p Jason
 * second draft of automap
 *
 * 8     12/07/98 5:37p Jason
 * first pass at automap
 *
 * 7     8/28/98 12:57p Jeff
 * added sounds and some key functionality
 *
 * 6     8/27/98 2:51p Jeff
 * New TelCom finally checked in
 *
 * 5     7/28/98 12:02p Jeff
 * got file prepared for Matt to implement Automap
 *
 * 4     7/11/98 9:16p Jeff
 * moved automatically drawing monitor overlay graphics from update() to a
 * function of it's own, that way the TelCom API can be avoided if needed
 *
 * 3     6/16/98 10:54a Jeff
 *
 * 2     5/18/98 2:23p Jeff
 * Automap displays stand-in art right now
 *
 * $NoKeywords: $
 */

#include "TelComAutoMap.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cfile.h"
#include "pserror.h"
#include "ddio.h"
#include "bitmap.h"
#include "room.h"

#include "TelCom.h"
#include "TelComEffects.h"
#include "renderer.h"
#include "game.h"
#include "mem.h"
#include "stringtable.h"
#include "lightmap_info.h"
#include "lightmap.h"
#include "controls.h"
#include "terrain.h"
#include "config.h"
#include "gameloop.h"
#include "multi.h"
#include "fireball.h"
#include "gamesequence.h"
#include "Mission.h"
#include "polymodel.h"
#include "player.h"
#include "marker.h"
#include "hlsoundlib.h"

// Variables needed for automap
static vector AM_view_pos = {0, 0, 0};
static matrix AM_view_orient;
static tTelComInfo *AM_tcs;
static int AM_ship_model_handle = -1;

uint8_t AutomapVisMap[MAX_ROOMS];

static float AM_heading;
static float AM_pitch;

int AM_terrain = 0, AM_realign = 0, AM_center_on_player = 0, AM_current_marker;

static int Num_AM_rooms;
static uint16_t AM_room_list[MAX_ROOMS];
static uint8_t AM_rooms_seen[MAX_ROOMS];
static g3Point *AM_rotated_points = NULL; //[MAX_VERTS_PER_ROOM];

static void TCAMCallback(void);

static uint8_t *Small_faces[MAX_ROOMS];

// clears out the list of visible rooms that we've seen
void AutomapClearVisMap() { memset(AutomapVisMap, 0, MAX_ROOMS); }

void ClassifyAMFaces() {
  int i = 0;
  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used) {
      Small_faces[i] = (uint8_t *)mem_malloc(Rooms[i].num_faces);
      ASSERT(Small_faces[i]);

      memset(Small_faces[i], 0, Rooms[i].num_faces);

      room *rp = &Rooms[i];

      for (int t = 0; t < rp->num_faces; t++) {
        face *fp = &rp->faces[t];

        vector verts[MAX_VERTS_PER_FACE];
        vector center;
        for (int k = 0; k < fp->num_verts; k++)
          verts[k] = rp->verts[fp->face_verts[k]];

        float size = vm_GetCentroidFast(&center, verts, fp->num_verts);

        if (size < 120)
          Small_faces[i][t] = 1;
        if (size < 60)
          Small_faces[i][t] = 2;
      }
    }
  }
}

void FreeAMFaces() {
  for (int i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used) {
      mem_free(Small_faces[i]);
      Small_faces[i] = NULL;
    }
  }
}

// Returns the camera position to the player
void TCAMCenterOnPlayer() {

  vm_MakeZero(&AM_view_pos);
  vm_MakeIdentity(&AM_view_orient);

  matrix newmat;
  angvec heading;
  AM_view_pos = Viewer_object->pos - (Viewer_object->orient.fvec * 10);
  vm_ExtractAnglesFromMatrix(&heading, &Player_object->orient);

  vm_AnglesToMatrix(&newmat, 0, heading.h, 0);
  AM_view_orient = newmat;

  AM_heading = heading.h;
  AM_pitch = heading.p;
}

// This is the function called by TelCom
//  return true if TelCom should exit to TelCom Main Menu
//  return false if you should exit out of TelCom completly
//  mmonitor = main monitor class
//  lmonitor = local monitor class (the monitor at the top of the screen)
bool TelComAutoMap(tTelComInfo *tcs) {
  bool done = false;

  if (!AM_rotated_points) {
    AM_rotated_points = (g3Point *)mem_malloc(sizeof(g3Point) * MAX_VERTS_PER_ROOM);
  }
  AM_tcs = tcs;
  AM_current_marker = -1;
  TelComEnableSystemKey(TCSYS_MAXKEYS, false); // disable all telcom system keys
  TelComEnableSystemKey(TCSYS_F1, true);       // enable F1 and enter, those are all we may need in automap
  TelComEnableSystemKey(TCSYS_F2, true);       // enable F2 and enter, those are all we may need in automap
  TelComEnableSystemKey(TCSYS_F3, true);       // enable F3 and enter, those are all we may need in automap
  TelComEnableSystemKey(TCSYS_1, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_2, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_3, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_4, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_5, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_6, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_7, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_8, true);        // enable marker key
  TelComEnableSystemKey(TCSYS_ENTER, true);    // processing other keys is a waste of cpu
  TelComEnableSystemKey(TCSYS_PRINTSCRN, true);

  // Classify faces
  ClassifyAMFaces();

  // Load ship model
  AM_ship_model_handle = LoadPolyModel("automapship.oof", 0);

  // Setup intial pos/orient
  TCAMCenterOnPlayer();
  if (OBJECT_OUTSIDE(Viewer_object)) {
    AM_terrain = 1;
  }

  TelcomStartScreen(0);

  // setup general background, plain color
  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;

  /*//load up the "fake automap" <----Start Remove---->
  TCBMPDESC bmpdesc;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  bmpdesc.caps=TCBD_XY;
  bmpdesc.x = 0; bmpdesc.y = 0;
  strcpy(bmpdesc.filename,"TCMap.ogf");
  //							 <----End Remove  ---->*/

  // setup text for the top monitor "Automap"
  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_STATIC;
  textdesc.font = BBRIEF_FONT_INDEX;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_FONT;
  textdesc.textbox.left = 65;
  textdesc.textbox.right = 380;
  textdesc.textbox.top = 2;
  textdesc.textbox.bottom = 50;
  textdesc.color = GR_RGB(255, 255, 255);

  // Setup Main Monitor
  // CreateBitmapEffect(&bmpdesc,MONITOR_MAIN,0);
  CreateBackgroundEffect(&backg, MONITOR_MAIN, 0); //<---- Replace above line with this line to get a background

  // Setup Location Monitor (small window at top)
  CreateBackgroundEffect(&backg, MONITOR_TOP, 0);
  CreateTextEffect(&textdesc, TXT_TCAUTOMAP, MONITOR_TOP, 0);
  TelcomEndScreen();
  TelcomRenderSetScreen(0);
  TelcomRenderSetCallback(TCAMCallback);

  ResumeControls(); // need to do because we're most likely coming from game.

  while (!done) {
    ct_packet automap_key;

    Sound_system.BeginSoundFrame(Telcom_called_from_game);

    if (Telcom_system.state != TCS_POWERON || tcs->current_status != TS_MAP) {
      // we're done with the loop
      done = true;
    }

    // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
    TelComHandleAllEvents(tcs);

    TelcomRenderScreen();
    App()->defer();
    if (KEY_STATE(KEY_ESC)) {
      AM_tcs->state = TCS_POWEROFF;
    }
    //		if(KEY_STATE(KEY_TAB)){
    //			AM_tcs->state = TCS_POWEROFF;
    //		}

    //	read controls
    Controller->get_packet(ctfAUTOMAP_KEY, &automap_key);
    if (automap_key.value > 0.0f) {
      AM_tcs->state = TCS_POWEROFF;
    }

    Sound_system.EndSoundFrame();
  }

  SuspendControls();

  DestroyAllScreens();
  TelcomRenderSetScreen(DUMMY_SCREEN);
  TelcomRenderSetCallback(NULL);

  FreeAMFaces();

  if (AM_ship_model_handle != -1) {
    FreePolyModel(AM_ship_model_handle);
  }

  TelComEnableSystemKey(TCSYS_MAXKEYS, true); // re-enable all telcom keys
  TelComEnableSystemKey(TCSYS_F1, false);     // disable the T key, not needed outside of automap
  if (AM_rotated_points) {
    mem_free(AM_rotated_points);
    AM_rotated_points = NULL;
  }
  return true;
}

// Builds a list of rooms to draw for the automap
void TCAMBuildRoomList(int startroom) {
  memset(AM_rooms_seen, 0, MAX_ROOMS);
  Num_AM_rooms = 0;

  if (startroom > 0) {
    AM_room_list[Num_AM_rooms++] = startroom;
    AM_rooms_seen[startroom] = 1;
  }

  int i = 0;
  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && !AM_rooms_seen[i] && (AutomapVisMap[i] == 1 || (Rooms[i].flags & RF_EXTERNAL))) {
      AM_room_list[Num_AM_rooms++] = i;
      AM_rooms_seen[i] = 1;
    }
  }
}

// Takes a min,max vector and makes a surrounding cube from it
void MakePointsFromMinMax(vector *corners, vector *minp, vector *maxp);
// Returns true if the external room is in the view cone
// Else returns false
bool IsRoomVisible(room *rp, float *nearz) {
  g3Point pnt;
  uint8_t ccode;

  vector corners[8];

  MakePointsFromMinMax(corners, &rp->min_xyz, &rp->max_xyz);

  *nearz = 90000000;
  uint8_t andbyte = 0xff;
  for (int t = 0; t < 8; t++) {
    g3_RotatePoint(&pnt, &corners[t]);

    if (pnt.p3_z < *nearz)
      *nearz = pnt.p3_z;

    ccode = g3_CodePoint(&pnt);
    if (!ccode)
      return true;
    andbyte &= ccode;
  }

  if (andbyte)
    return false;

  return true;
}

void TCAMRenderRoom(int roomnum) {
  ASSERT(Rooms[roomnum].used);
  room *rp = &Rooms[roomnum];
  static int first = 1;
  static float lm_red[32], lm_green[32], lm_blue[32];
  float nearz;
  int i;

  if (first) {
    first = 0;
    for (int i = 0; i < 32; i++) {
      lm_red[i] = ((float)i / 31.0);
      lm_green[i] = ((float)i / 31.0);
      lm_blue[i] = ((float)i / 31.0);
    }
  }

  if ((rp->flags & RF_EXTERNAL) && !AM_terrain)
    return;

  if (!IsRoomVisible(rp, &nearz))
    return;

  // rotate all the points for this room
  for (i = 0; i < rp->num_verts; i++) {
    g3_RotatePoint(&AM_rotated_points[i], &rp->verts[i]);
    g3_ProjectPoint(&AM_rotated_points[i]);
  }

  for (i = 0; i < rp->num_faces; i++) {
    g3Point *pointlist[MAX_VERTS_PER_FACE];
    g3Point pointbuffer[MAX_VERTS_PER_FACE];

    face *fp = &rp->faces[i];

    // See if this face is backfaced
    vector subvec = rp->verts[fp->face_verts[0]] - AM_view_pos;
    if (subvec * fp->normal > 0)
      continue; // backfaced

    int black_face = 0, wacky_face = 0;

    if (fp->portal_num != -1) {
      if (!AutomapVisMap[rp->portals[fp->portal_num].croom]) {
        // Don't give away secret rooms
        if (Rooms[rp->portals[fp->portal_num].croom].flags & RF_SECRET)
          black_face = 1;
        else
          wacky_face = 1;
      } else
        continue;
    }

    if (nearz > 600) {
      if (Small_faces[roomnum][i] != 0)
        continue;
    } else if (nearz > 300) {
      if (Small_faces[roomnum][i] == 2)
        continue;
    }

    // Color this face from the lightmaps
    if (!black_face && !wacky_face && (fp->flags & FF_LIGHTMAP)) {
      int lm_handle = LightmapInfo[fp->lmi_handle].lm_handle;
      uint16_t *data = (uint16_t *)lm_data(lm_handle);
      int w = lm_w(lm_handle);
      int h = lm_h(lm_handle);

      for (int t = 0; t < fp->num_verts; t++) {
        pointbuffer[t] = AM_rotated_points[fp->face_verts[t]];
        g3Point *p = &pointbuffer[t];
        pointlist[t] = p;

        float u = fp->face_uvls[t].u2 * w;
        float v = fp->face_uvls[t].v2 * h;

        int int_u = u;
        int int_v = v;

        uint16_t texel = data[int_v * w + int_u];

        int r = (texel >> 10) & 0x1f;
        int g = (texel >> 5) & 0x1f;
        int b = (texel) & 0x1f;

        p->p3_r = lm_red[r];
        p->p3_g = lm_green[g];
        p->p3_b = lm_blue[b];
        p->p3_a = 1.0;
        p->p3_flags |= PF_RGBA;
      }

      g3_DrawPoly(fp->num_verts, pointlist, 0);
    } else {
      for (int t = 0; t < fp->num_verts; t++) {
        pointbuffer[t] = AM_rotated_points[fp->face_verts[t]];
        g3Point *p = &pointbuffer[t];
        pointlist[t] = p;

        p->p3_flags |= PF_RGBA;
        p->p3_r = 0.0;
        p->p3_g = 0.0;
        p->p3_b = 0.0;
        p->p3_a = 1.0;

        if (wacky_face) {
          float curtime = timer_GetTime();
          int val = curtime;
          float fval = curtime - val;
          p->p3_r = fval;
          p->p3_g = fval;
          p->p3_b = fval;
          p->p3_a = 1.0;
        }
      }
      g3_DrawPoly(fp->num_verts, pointlist, 0);
    }
  }
}

#define AM_TRANSLATION_SCALAR 200.0f
#define AM_ROTATIONAL_SCALAR 90

// Reads the controls for the automap, and adjusts viewpoint accordingly
void TCAMReadControls() {
  Frametime = last_frametime;
  int save_mode = Game_interface_mode;
  game_controls controls;

  controls.toggle_slide = 0;
  controls.toggle_bank = 0;
  Game_interface_mode = GAME_INTERFACE;

  PollControls();
  DoMovement(&controls);

  // Do translational movement
  AM_view_pos += (controls.forward_thrust * last_frametime * AM_TRANSLATION_SCALAR) * AM_view_orient.fvec;
  AM_view_pos += (controls.vertical_thrust * last_frametime * AM_TRANSLATION_SCALAR) * AM_view_orient.uvec;
  AM_view_pos += (controls.sideways_thrust * last_frametime * AM_TRANSLATION_SCALAR) * AM_view_orient.rvec;

  // Do rotational movement

  matrix newmat;
  float norm = ((65536 / 360) * AM_ROTATIONAL_SCALAR) * last_frametime;

  AM_pitch += (norm * controls.pitch_thrust);
  AM_heading += (norm * controls.heading_thrust);

  if (AM_pitch < 0)
    AM_pitch += 65536;
  if (AM_pitch >= 65536)
    AM_pitch -= 65536;

  if (AM_heading < 0)
    AM_heading += 65536;
  if (AM_heading >= 65536)
    AM_heading -= 65536;

  vm_AnglesToMatrix(&newmat, (uint16_t)AM_pitch, (uint16_t)AM_heading, 0);
  AM_view_orient = newmat;

  vm_Orthogonalize(&AM_view_orient);
  Game_interface_mode = save_mode;
}

// Renders the low-res terrain for the automap
void TCAMRenderTerrain() {
  int nt;
  int render_width, render_height;
  float w2, h2;

  int save_check = Terrain_occlusion_checksum;
  int save_pix = Detail_settings.Pixel_error;
  float save_dist = Detail_settings.Terrain_render_distance;

  Detail_settings.Pixel_error = 31;
  Detail_settings.Terrain_render_distance = 300 * TERRAIN_SIZE;
  Terrain_occlusion_checksum = -1;

  // Get the size of the current render window
  rend_GetProjectionParameters(&render_width, &render_height);
  w2 = ((float)render_width - 1) / 2.0;
  h2 = ((float)render_height - 1) / 2.0;

  // Set up vars for (psuedo-)clipping window
  Check_terrain_portal = 0;

  Clip_scale_left = 0;
  Clip_scale_right = render_width - 1;
  Clip_scale_top = 0;
  Clip_scale_bot = render_height - 1;

  Terrain_from_mine = 0;

  VisibleTerrainZ = (Detail_settings.Terrain_render_distance) * Matrix_scale.z;

  // Set up our z wall
  g3_SetFarClipZ(VisibleTerrainZ);

  vector viewer_eye;
  matrix viewer_orient;
  // Get scaled matrix
  g3_GetViewPosition(&viewer_eye);
  g3_GetViewMatrix(&viewer_orient);

  // Get all of the cells visible to us
  nt = GetVisibleTerrain(&viewer_eye, &viewer_orient);

  // And display!
  if (nt > 0)
    DisplayTerrainList(nt, 1);

  Detail_settings.Pixel_error = save_pix;
  Detail_settings.Terrain_render_distance = save_dist;
  Terrain_occlusion_checksum = save_check;
}

#define AM_BLINK_TIME .25f

// Draws all the relevant objects for automap
void TCAMDrawObjects() {
  int i;
  int drawit = (timer_GetTime() * 4);
  drawit = (drawit % 2);

  if (Game_mode & GM_MULTI) {
    for (i = 0; i < MAX_PLAYERS; i++) {
      if (i == Player_num) {
        object *obj = &Objects[Players[Player_num].objnum];
        if (AM_ship_model_handle != -1 && drawit)
          DrawPolygonModel(&obj->pos, &obj->orient, AM_ship_model_handle, NULL, 0, 1, 1, 1);
      } else if (NetPlayers[i].flags & NPF_CONNECTED) {
        object *obj = &Objects[Players[i].objnum];
        if ((obj->type == OBJ_PLAYER && obj->render_type == RT_POLYOBJ) || obj->type == OBJ_OBSERVER)
          DrawColoredDisk(&Objects[Players[i].objnum].pos, 1, 1, .5f, 1.0, .3f, 3.0);
      }
    }
  } else {
    object *obj = &Objects[Players[Player_num].objnum];

    if (AM_ship_model_handle != -1 && drawit)
      DrawPolygonModel(&obj->pos, &obj->orient, AM_ship_model_handle, NULL, 0, 1, 1, 1);
  }

  float norm = timer_GetTime();
  int int_norm = norm;
  norm -= int_norm;
  for (i = 0; i <= Highest_object_index; i++) {
    object *obj = &Objects[i];

    if (obj->type == OBJ_MARKER && obj->parent_handle == Player_object->handle) {
      float size = 2.5 + (norm * 2.5);
      float r = 1.0;
      float g = 0;
      float b = 1.0;

      if (AM_current_marker != -1) {
        int index = 0;

        if (Game_mode & GM_MULTI)
          index = obj->id - (Player_num * 2);
        else
          index = obj->id;

        if (AM_current_marker == index) {
          size = 9.0 + (norm * 9.0);
          r = 0;
          g = 1.0;
          b = 1.0;
        }
      }

      DrawColoredDisk(&obj->pos, r, g, b, 1.0, .3f, size);
    }
  }
}

#include "hud.h"

void TCAMDrawMenu() {
  char str[255];
  g3Point *pntlist[4], points[4];
  grtext_SetFont(BRIEFING_FONT);
  int fontheight = grfont_GetHeight(BRIEFING_FONT);

  points[0].p3_sx = AM_tcs->Monitor_coords[MONITOR_MAIN].left;
  points[0].p3_sy = AM_tcs->Monitor_coords[MONITOR_MAIN].bottom - (fontheight * 3);

  points[1].p3_sx = AM_tcs->Monitor_coords[MONITOR_MAIN].right;
  points[1].p3_sy = AM_tcs->Monitor_coords[MONITOR_MAIN].bottom - (fontheight * 3);

  points[2].p3_sx = AM_tcs->Monitor_coords[MONITOR_MAIN].right;
  points[2].p3_sy = AM_tcs->Monitor_coords[MONITOR_MAIN].bottom;

  points[3].p3_sx = AM_tcs->Monitor_coords[MONITOR_MAIN].left;
  points[3].p3_sy = AM_tcs->Monitor_coords[MONITOR_MAIN].bottom;

  for (int i = 0; i < 4; i++) {
    points[i].p3_z = 0;
    points[i].p3_flags = PF_PROJECTED;
    pntlist[i] = &points[i];
  }

  rend_SetZBufferState(0);
  rend_SetTextureType(TT_FLAT);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetLighting(LS_NONE);
  rend_SetFlatColor(GR_BLACK);
  rend_SetAlphaValue(192);
  rend_DrawPolygon2D(0, pntlist, 4);

  grtext_SetAlpha(250);
  grtext_SetColor(GR_RGB(255, 255, 255));

  snprintf(str, sizeof(str), TXT_TCAM_TERRAIN, AM_terrain ? TXT_STRING_OFF : TXT_STRING_ON);
  grtext_CenteredPrintf(0, AM_tcs->Monitor_coords[MONITOR_MAIN].bottom - (fontheight * 3) + (fontheight / 2), str);
  snprintf(str, sizeof(str), "%s", TXT_TCAM_INSTRUCTIONS);
  grtext_CenteredPrintf(0, AM_tcs->Monitor_coords[MONITOR_MAIN].bottom - (fontheight * 2) + (fontheight / 2), str);

  // Use HUD font for part that overlays the 3D
  fontheight = grfont_GetHeight(HUD_FONT);
  grtext_SetFont(HUD_FONT);
  grtext_SetColor(HUD_COLOR);

  snprintf(str, sizeof(str), "%s", Level_info.name);
  grtext_CenteredPrintf(0, AM_tcs->Monitor_coords[MONITOR_MAIN].top + (fontheight / 2), str);

  if (AM_current_marker != -1) {
    int markernum = (Game_mode & GM_MULTI) ? (Player_num * 2 + AM_current_marker) : AM_current_marker;
    snprintf(str, sizeof(str), TXT_VIEW_MARKER, AM_current_marker + 1);
    strncat(str, ": ", sizeof(str) - strlen(str) - 1);
    strncat(str, MarkerMessages[markernum], sizeof(str) - strlen(str) - 1);
    grtext_CenteredPrintf(0, AM_tcs->Monitor_coords[MONITOR_MAIN].top + (fontheight / 2) + fontheight, str);
  }

  grtext_Flush();
}

// The callback function that the telcom calls every frame
void TCAMCallback(void) {
  StartFrame(Telcom_system.Monitor_coords[MONITOR_MAIN].left, Telcom_system.Monitor_coords[MONITOR_MAIN].top,
             Telcom_system.Monitor_coords[MONITOR_MAIN].right, Telcom_system.Monitor_coords[MONITOR_MAIN].bottom);

  // Start a 3d frame
  g3_StartFrame(&AM_view_pos, &AM_view_orient, Render_zoom);

  if (AM_center_on_player) {
    TCAMCenterOnPlayer();
    AM_center_on_player = 0;
  }

  if (AM_realign) {
    AM_pitch = 0;
    AM_realign = 0;
  }

  rend_SetFiltering(1);
  rend_SetAlphaType(AT_VERTEX);
  rend_SetTextureType(TT_FLAT);
  rend_SetLighting(LS_GOURAUD);
  rend_SetColorModel(CM_RGB);
  rend_SetOverlayType(OT_NONE);
  rend_SetZBufferState(1);

  if (AM_terrain)
    rend_SetZValues(0, VisibleTerrainZ);

  TCAMBuildRoomList(Viewer_object->roomnum);
  // Render all rooms in view
  for (int i = 0; i < Num_AM_rooms; i++) {
    TCAMRenderRoom(AM_room_list[i]);
  }

  // Render terrain
  if (AM_terrain)
    TCAMRenderTerrain();

  g3_EndFrame();

  rend_SetFiltering(1);

  TCAMDrawObjects();
  EndFrame();

  rend_SetFiltering(0);

  TCAMDrawMenu();

  TCAMReadControls();
}
