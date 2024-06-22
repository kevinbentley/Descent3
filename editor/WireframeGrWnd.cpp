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

 * $Logfile: /DescentIII/Main/editor/WireframeGrWnd.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * Wireframe view of mine
 *
 * $Log: not supported by cvs2svn $
 *
 * 29    4/03/99 5:22p Matt
 * Don't render wireframe when editor rendering disabled
 *
 * 28    2/05/99 3:49p Jason
 * added more types to color coded topographical window
 *
 * 27    2/05/99 3:37p Jason
 * added/fixed features for the designers
 *
 * 26    2/03/99 1:11p Matt
 * Changed the paletted room current faces to be stored in a seperate
 * array, instead of in the room structure.
 *
 * 25    1/20/99 10:50a Jason
 * added new terrain
 *
 * 24    1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 23    10/04/98 1:25p Matt
 *
 * 22    9/23/98 12:30p Jason
 * fixed memory overwrite bug
 *
 * 21    5/20/98 3:48p Matt
 * Added suport for variable-depth face selection in wireframe view.
 *
 * 20    5/01/98 3:51p Jason
 * sped up terrain rendering by precaching all megacell lod bitmaps
 *
 * 19    4/23/98 6:53p Jason
 * changed wireframe map to work with new bitmap changes
 *
 * 18    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 17    2/05/98 3:18p Matt
 * Renamed GetSegmentFromPoint() to GetCellFromPoint()
 *
 * 16    2/05/98 2:57p Matt
 * Changed code to use ObjSetPos()
 *
 * 15    2/04/98 6:23p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 14    12/03/97 6:21p Jason
 * made selections undoable
 *
 * 13    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 12    10/03/97 3:39p Matt
 * Added seperate sets of wireframe view variables for mine & room views
 *
 * 11    9/17/97 11:34a Matt
 * Ripped out segment code
 *
 * 10    9/08/97 4:13p Jason
 * added colored lighting for the terrain
 *
 * 9     9/06/97 3:21p Matt
 * Reset cur portal when room changes
 *
 * 8     9/04/97 4:39p Matt
 * Added includes needed as a result of removing includes from d3edit.h
 *
 * 7     8/29/97 5:14p Matt
 * Switched segment selection function to do rooms instead
 *
 * 6     8/21/97 3:45p Matt
 * Reset curedge & curvert when changing curroom & curface
 *
 * 5     8/06/97 11:43a Jason
 * made lightmaps work correctly in the terrain
 *
 * 4     7/29/97 12:18p Matt
 * Made wireframe search work for rooms & faces
 *
 * 3     7/22/97 7:08p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 32    6/19/97 11:32a Jason
 * fixed bug where you could draw into the topo map even if you weren't
 * viewing terrain
 *
 * 31    6/12/97 12:43p Jason
 * fixed simple bug where bottom-right edges were being included in
 * terrain selection
 *
 * 30    6/11/97 2:11p Jason
 * made magnification actually zoom into the texture you're looking at
 *
 * 29    5/22/97 5:16p Jason
 * added "drawing" on the topo map
 *
 * 28    5/21/97 3:39p Jason
 * added terrain editing stuff
 *
 * 27    5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 26    5/15/97 4:37p Jason
 * fixed some terrain bugs
 *
 * 25    5/15/97 3:27a Jason
 * implemented terrain magnification
 *
 * 24    4/11/97 4:20p Jason
 * now draws the player on the wireframe terrain window
 *
 * 23    4/10/97 4:39p Jason
 * Made selection manager stuff work with terrain topographical map
 *
 * 22    3/31/97 5:58p Matt
 * Revamped mine update flags
 *
 * 21    3/20/97 5:54p Matt
 * Made box selection code ignore very small boxes so normal mouse clicks
 * would work
 *
 * 20    3/20/97 5:01p Matt
 * Added new select-from-box code
 *
 * 19    3/20/97 3:02p Samir
 * Implemented Selection Manager in Wireframe window.
 *
 * 18    3/20/97 11:55a Jason
 * changes for terrain editing/drawing
 *
 * 17    3/02/97 4:25p Matt
 * Added shift-click to select/deselect segments in the wireframe window
 *
 * 16    2/28/97 2:21p Samir
 * You can drag a box within the wireframe window.
 *
 * 15    2/27/97 4:26p Matt
 * Fixed curseg selection status messages
 *
 * 14    2/19/97 5:37p Matt
 * Added code to set curseg from clicking in wireframe window
 *
 * 13    1/30/97 6:26p Samir
 * Minor change to drawing caption text
 *
 * 12    1/23/97 4:56p Samir
 * Handles saving screen positions of windows and tileability.
 *
 * 11    1/21/97 12:43p Samir
 * Floatable-resizable view
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "editor.h"
#include "WireframeGrWnd.h"
#include "3d.h"
#include "gametexture.h"
#include "drawworld.h"
#include "moveworld.h"
#include "selectedroom.h"
#include "terrain.h"
#include "texture.h"
#include "bitmap.h"
#include "erooms.h"

#include <assert.h>
#include "gr.h"
#include "mono.h"
#include "macros.h"
#include "ddio.h"
#include "SelManager.h"
#include "room.h"
#include "lighting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWireframeGrWnd

CWireframeGrWnd::CWireframeGrWnd() : CGrWnd("WireframeScreen") {
  m_Movable = FALSE;
  m_x1 = m_y1 = 0;
  m_y2 = TERRAIN_DEPTH;
  m_x2 = TERRAIN_WIDTH;
}

CWireframeGrWnd::~CWireframeGrWnd() {}

void DrawIntoTopoMap(int x, int y);

void CWireframeGrWnd::GetHighlightedRect(int *left, int *top, int *right, int *bottom) {
  *left = m_HighlightedRect.left;
  *top = m_HighlightedRect.top;
  *right = m_HighlightedRect.right;
  *bottom = m_HighlightedRect.bottom;
}

BEGIN_MESSAGE_MAP(CWireframeGrWnd, CWnd)
//{{AFX_MSG_MAP(CWireframeGrWnd)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_SIZE()
ON_WM_PAINT()
ON_WM_MOVE()
ON_WM_SYSCOMMAND()
ON_WM_NCACTIVATE()
ON_WM_NCPAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//??extern void RenderWireFrame (grViewport *my_viewport);
//??extern void RenderTexFrame (grViewport *);

extern bool Disable_editor_rendering;

void CWireframeGrWnd::Render() {
  //	Don't do a thing if these objects aren't created yet
  if (!m_grScreen)
    return;
  if (!m_grViewport)
    return;

  if (Disable_editor_rendering)
    return;

  if (Editor_view_mode == VM_TERRAIN)
    DrawTerrainWorld(m_grViewport, &Wireframe_view->target, &Wireframe_view->orient, Wireframe_view->dist);
  else
    DrawWorld(m_grViewport, &Wireframe_view->target, &Wireframe_view->orient, Wireframe_view->dist, 0,
              Wireframe_view->rad);
}

/////////////////////////////////////////////////////////////////////////////
// CWireframeGrWnd message handlers

BOOL CWireframeGrWnd::Create(RECT &rect, BOOL movable, CWnd *pParent) {
  RECT new_rect;
  DWORD dwstyle;

  dwstyle = (movable ? GRWND_STYLE : GRWND_STATIC_STYLE);

  ::CopyRect(&new_rect, &rect);
  ::AdjustWindowRect(&new_rect, dwstyle, FALSE);

  //	We want this window to start at rect.left, rect.top.
  if (new_rect.left < rect.left) {
    int offx;
    offx = rect.left - new_rect.left;
    new_rect.left += offx;
    new_rect.right += offx;
  }
  if (new_rect.top < rect.top) {
    int offy;
    offy = rect.top - new_rect.top;
    new_rect.top += offy;
    new_rect.bottom += offy;
  }

  ::CopyRect(&rect, &new_rect);

  m_grCreated = TRUE;
  m_Movable = movable;

  lstrcpy(m_Name, "Wireframe");

  return CWnd::Create(NULL, m_Name, dwstyle, rect, pParent, IDC_WIREFRAME_WND);
}

int CWireframeGrWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CGrWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  Editor()->wireframe_view = this;
  return 0;
}

void CWireframeGrWnd::OnDestroy() {
  CGrWnd::OnDestroy();
  Editor()->wireframe_view = NULL;
}

void CWireframeGrWnd::OnSize(UINT nType, int cx, int cy) {
  CGrWnd::OnSize(nType, cx, cy);

  // TODO: Add your message handler code here
  if (m_Movable) { // Don't change these values if this is a static window
    D3EditState.wirescr_w = cx;
    D3EditState.wirescr_h = cy;
  }
}

void CWireframeGrWnd::OnPaint() {
  CPaintDC dc(this); // device context for painting

  //	Draw what's on the screen back page to the desktop
  m_grScreen->flip();
  draw_tile_caption(&dc);
}

void CWireframeGrWnd::OnMove(int x, int y) {
  CGrWnd::OnMove(x, y);

  //	must do this because actual (left,top) of window should be from title bar, not client
  if (m_Movable) { // Don't change these values if we aren't movable
    RECT rect;
    GetWindowRect(&rect);
    GetParent()->ScreenToClient(&rect);
    D3EditState.wirescr_x = rect.left;
    D3EditState.wirescr_y = rect.top;
  }
}

// Given an x,y mouse point, returns the terrain cell number at that point
int CWireframeGrWnd::GetCellFromPoint(int x, int y) {
  int width = m_grViewport->width();
  int height = m_grViewport->height();

  float xstep = (float)(m_x2 - m_x1) / (float)width;
  float ystep = (float)(abs(m_y2 - m_y1)) / (float)height;

  int destx = xstep * x;
  int desty = ystep * y;

  destx += m_x1;
  desty += m_y1;

  desty = (TERRAIN_DEPTH - 1) - desty; // flip due to origin difference

  return (desty * TERRAIN_WIDTH + destx);
}

void CWireframeGrWnd::OnSysCommand(UINT nID, LPARAM lParam) {
  // TODO: Add your message handler code here and/or call default

  switch (nID) {
  case SC_CLOSE:
    D3EditState.wirescr_visible = 0;
    break;
  }

  CWnd::OnSysCommand(nID, lParam);
}

BOOL CWireframeGrWnd::OnNcActivate(BOOL bActive) { return CGrWnd::OnNcActivate(bActive); }

void CWireframeGrWnd::OnNcPaint() { CGrWnd::OnNcPaint(); }

void CWireframeGrWnd::draw_tile_caption(CDC *dc) {
  if (!m_Movable) {
    dc->SetBkMode(TRANSPARENT);
    dc->SetTextColor(RGB(192, 192, 192));
    if (Editor_view_mode == VM_TERRAIN)
      dc->TextOut(10, 10, "Topographical", lstrlen("Topographical"));
    else
      dc->TextOut(10, 10, m_Name, lstrlen(m_Name));
  }
}

//	These functions handle special mouse operations within the wireframe window
void EndWireframeSel(editorSelectorManager *esm);

void CWireframeGrWnd::OnLButtonDown(UINT nFlags, CPoint point) {
  if (Editor_view_mode == VM_TERRAIN) {
    if (KEY_STATE(KEY_LCTRL)) {
      int cellnum = GetCellFromPoint(point.x, point.y);
      vector pos;

      ComputeTerrainSegmentCenter(&pos, cellnum);
      ObjSetPos(Viewer_object, &pos, MAKE_ROOMNUM(cellnum), NULL, false);

      State_changed = 1;
    } else if (KEY_STATE(KEY_LSHIFT)) {
      int seg = GetCellFromPoint(point.x, point.y);

      Terrain_tex_seg[Terrain_seg[seg].texseg_index].tex_index = D3EditState.texdlg_texture;
      World_changed = 1;

    } else
      SelManager.StartSelection(this, EndWireframeSel, point.x, point.y);

  } else // mine or room mode
  {
    int found_segnum, found_facenum;
    int find_mode = FM_CLOSEST;

    // See if we're clicking on the current face
    found_segnum = ROOMNUM(Curroomp);
    found_facenum = Curface;
    if (WireframeFindRoomFace(m_grViewport, point.x, point.y, &found_segnum, &found_facenum, FM_SPECIFIC)) {
      find_mode = FM_NEXT;
    }

  find_again:;

    if (WireframeFindRoomFace(m_grViewport, point.x, point.y, &found_segnum, &found_facenum, find_mode)) {
      if (KEY_STATE(KEY_LSHIFT) || KEY_STATE(KEY_RSHIFT)) { // ctrl + click means toggle select state
        int newstate;
        newstate = ToggleRoomSelectedState(found_segnum);
        State_changed = 1;
        EditorStatus("Room %d %s", found_segnum, newstate ? "selected" : "deselected");
      } else {
        if (Editor_view_mode == VM_ROOM) {
          ASSERT(found_segnum == D3EditState.current_room);
          Current_faces[D3EditState.current_room - FIRST_PALETTE_ROOM] = found_facenum;
          EditorStatus("Current face set to %d", found_facenum);
        } else {
          Curroomp = &Rooms[found_segnum];
          Curface = found_facenum;
          Curedge = Curvert = 0;
          Curportal = -1;
          EditorStatus("Current room:face set to %d:%d", ROOMNUM(Curroomp), Curface);
        }
        State_changed = 1;
      }
    } else if (find_mode == FM_NEXT) {
      find_mode = FM_CLOSEST;
      goto find_again;
    }

    //	no more dragging, but something is highlighted.
    //	so we will redraw world if mouse is pressed

    SelManager.StartSelection(this, EndWireframeSel, point.x, point.y);
  }

  CWnd::OnLButtonDown(nFlags, point);
}

void CWireframeGrWnd::OnMouseMove(UINT nFlags, CPoint point) {
  if (Editor_view_mode == VM_TERRAIN)
    DrawIntoTopoMap(point.x, point.y);
  CWnd::OnMouseMove(nFlags, point);
}

void CWireframeGrWnd::OnLButtonUp(UINT nFlags, CPoint point) { CWnd::OnLButtonUp(nFlags, point); }

// How big a box needs to be before we recognize it
#define MIN_BOX_SIZE 3

void EndWireframeSel(editorSelectorManager *esm) {
  int left, top, right, bot;
  int n;

  esm->GetSelectedRect(&left, &top, &right, &bot);

  if ((right - left < MIN_BOX_SIZE) || (bot - top < MIN_BOX_SIZE))
    return;

  if (Editor_view_mode == VM_TERRAIN) {
    int i;

    if (!(KEY_STATE(KEY_RALT))) {
      for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++)
        TerrainSelected[i] = 0;
      Num_terrain_selected = 0;
    }

    RECT rect;
    int x1, y1, x2, y2;
    esm->m_OwnerWnd->GetWindowRect(&rect);
    esm->m_OwnerWnd->ScreenToClient(&rect);
    Editor()->wireframe_view->GetMagCoords(&x1, &y1, &x2, &y2);

    float xstep = (float)(x2 - x1) / (float)rect.right;
    float ystep = (float)(abs(y2 - y1)) / (float)rect.bottom;

    left *= xstep;
    right *= xstep;
    top *= ystep;
    bot *= ystep;

    left += x1;
    right += x1;
    top += y1;
    bot += y1;

    // We switch top and bottom due to the fact that our origin is in the bottom
    // left instead of the top left
    bot = (TERRAIN_DEPTH - 1) - bot;
    top = (TERRAIN_DEPTH - 1) - top;

    int t;
    int state = 1;
    if (KEY_STATE(KEY_RALT))
      state = 0;

    for (i = bot; i <= top; i++) {
      for (t = left; t <= right; t++) {
        if (!state) {
          if (TerrainSelected[i * TERRAIN_WIDTH + t])
            Num_terrain_selected--;
          TerrainSelected[i * TERRAIN_WIDTH + t] = 0;
        } else {
          TerrainSelected[i * TERRAIN_WIDTH + t] = 1;
          Num_terrain_selected++;
        }
      }
    }

    if (KEY_STATE(KEY_LALT)) {

      Editor()->wireframe_view->SetMagCoords(left, (TERRAIN_DEPTH - 1) - top, right, (TERRAIN_DEPTH - 1) - bot);
    }

    World_changed = 1;
  } else {
    if (!(KEY_STATE(KEY_LCTRL) || KEY_STATE(KEY_RCTRL))) // ctrl + select means add to list
      ClearRoomSelectedList();

    n = SelectRoomsInBox(NULL, left, top, right, bot);
    EditorStatus("%d rooms selected", n);
  }

  esm->EndSelection();
}

void CWireframeGrWnd::DrawPlayerOnTerrain() {
  static int lastx = -1, lastz = -1;
  static uint16_t last_color;

  int seg = GetTerrainCellFromPos(&Viewer_object->pos);
  if (seg < 0)
    return;

  int x = seg % TERRAIN_WIDTH;
  int z = seg / TERRAIN_WIDTH;

  //	x-=(m_x1);
  //	z-=m_y1;

  z = (TERRAIN_DEPTH - 1) - z;

  RECT rect;

  GetWindowRect(&rect);
  ScreenToClient(&rect);

  float xstep = (float)(m_x2 - m_x1) / (float)(rect.right - rect.left);
  float ystep = (float)(abs(m_y2 - m_y1)) / (float)(rect.bottom - rect.top);

  m_grViewport->lock();

  x = (float)x / xstep;
  z = (float)z / ystep;

  if (x < 0 || x > rect.right)
    goto getout;
  if (z < 0 || z > rect.bottom)
    goto getout;

  if (lastx != -1 && lastx < (rect.right - rect.left) && lastz < (rect.bottom - rect.top))
    m_grViewport->setpixel(last_color, lastx, lastz);

  lastx = x;
  lastz = z;
  last_color = m_grViewport->getpixel(lastx, lastz);

  m_grViewport->setpixel(GR_RGB(255, 255, 255), x, z);

getout:
  m_grViewport->unlock();
  m_grScreen->flip();
}

void DrawPlayerOnWireframe() {
  if (Editor()->wireframe_view)
    Editor()->wireframe_view->DrawPlayerOnTerrain();
}

void CWireframeGrWnd::GetMagCoords(int *x1, int *y1, int *x2, int *y2) {
  *x1 = m_x1;
  *x2 = m_x2;
  *y1 = m_y1;
  *y2 = m_y2;
}
void CWireframeGrWnd::SetMagCoords(int x1, int y1, int x2, int y2) {
  m_x1 = x1;
  m_x2 = x2;
  m_y1 = y1;
  m_y2 = y2;
}

// Redraws only one terrain cell in the wireframe view
void CWireframeGrWnd::DrawTerrainCell(int seg) {
  grSurface *cur_surf;
  uint16_t *destptr;
  int lightval;
  int i, t, x, y;
  int segx = seg % TERRAIN_WIDTH;
  int segz = seg / TERRAIN_WIDTH;

  cur_surf = m_grViewport->lock();
  destptr = (uint16_t *)cur_surf->data();
  int rowsize = cur_surf->rowsize() / 2;
  int x1, y1, x2, y2;

  Editor()->wireframe_view->GetMagCoords(&x1, &y1, &x2, &y2);

  fix xstep = IntToFix(x2 - x1) / cur_surf->width();
  fix ystep = IntToFix(abs(y2 - y1)) / cur_surf->height();

  float cellwidth = 1.0 / FixToFloat(xstep);
  float cellheight = 1.0 / FixToFloat(ystep);

  int ystart = cellheight * (((TERRAIN_DEPTH - 1) - segz) - y1);
  int xstart = cellwidth * (segx - x1);

  cellheight = ceil(cellheight);
  cellwidth = ceil(cellwidth);

  x = segx;
  y = segz; // flip due to origin difference
  uint16_t fadepixel = 0;

  int bm_handle = GameTextures[Terrain_tex_seg[Terrain_seg[(y * TERRAIN_WIDTH + x)].texseg_index].tex_index].bm_handle;
  lightval = Ubyte_to_float[Terrain_seg[y * TERRAIN_WIDTH + x].l] * (MAX_TEXTURE_SHADES - 1);

  uint16_t pix;

  pix = *bm_data(bm_handle, 0);
  // fadepixel=(TexShadeTable16[lightval][pix>>8])+TexShadeTable8[lightval][pix & 0xFF];

  if (TerrainSelected[y * TERRAIN_WIDTH + x]) {
    int red = ((fadepixel >> 10) & 0x1f) << 3;
    int green = ((fadepixel >> 5) & 0x1f) << 3;
    int blue = (fadepixel & 0x1f) << 3;

    red <<= 2;
    green <<= 2;
    blue <<= 2;

    red = std::min(255, red);
    green = std::min(255, green);
    blue = std::min(255, blue);

    fadepixel = GR_RGB16(red, green, blue);
  }

  for (i = 0; i < (int)cellheight; i++)
    for (t = 0; t < (int)cellwidth; t++) {

      destptr[(i + ystart) * rowsize + t + xstart] = fadepixel;
    }
  m_grViewport->unlock();
}
/*

// draws a topographical representation of our terrain in the wireframe window
void CWireframeGrWnd::DrawTerrainWorld(grViewport *vp,vector *view_target,matrix *view_orient,float view_dist)
{
        grSurface *cur_surf;
        uint16_t *destptr;
        int lightval;
        int i,t;

        cur_surf=vp->lock();
        destptr=(uint16_t*)cur_surf->data();
        int rowsize=cur_surf->rowsize()/2;
        int x1,y1,x2,y2;

        Editor()->wireframe_view->GetMagCoords (&x1,&y1,&x2,&y2);

        fix xstep=IntToFix(x2-x1)/cur_surf->width();
        fix ystep=IntToFix(abs(y2-y1))/cur_surf->height();
        fix u=IntToFix (x1);
        fix v=IntToFix (y1);

        for (i=0;i<cur_surf->height();i++,v+=ystep,u=IntToFix(x1))
                for (t=0;t<cur_surf->width();t++,u+=xstep)
                {
                        int x,y;
                        x=FixToInt (u);
                        y=FixToInt (v);

                        y=(TERRAIN_DEPTH-1)-y;	// flip due to origin difference

                        uint16_t fadepixel;

                        int bm_handle=GameTextures[Terrain_seg[y*TERRAIN_WIDTH+x].tex_index].bm_handle;
                        lightval=(Terrain_seg[y*TERRAIN_WIDTH+x].light)*(MAX_TEXTURE_SHADES-1);

                        uint16_t pix;

                        pix=*bm_data(bm_handle,0);
                        fadepixel=(TexShadeTable16[lightval][pix>>8])+TexShadeTable8[lightval][pix & 0xFF];


                        if (TerrainSelected[y*TERRAIN_WIDTH+x])
                        {
                                int red=(fadepixel>>11)<<3;
                                int green=((fadepixel >> 5)&0x3f)<<2;
                                int blue=(fadepixel & 0x1f)<<3;

                                red<<=2;
                                green<<=2;
                                blue<<=2;

                                red=std::min(255,red);
                                green=std::min(255,green);
                                blue=std::min(255,blue);



                                fadepixel=GR_RGB16(red,green,blue);
                        }


                        destptr[i*rowsize+t]=fadepixel;
                }
        vp->unlock();

}*/

// draws a topographical representation of our terrain in the wireframe window
void CWireframeGrWnd::DrawTerrainWorld(grViewport *vp, vector *view_target, matrix *view_orient, float view_dist) {
  grSurface *cur_surf;
  uint16_t *destptr;
  float lightval;
  int i, t;

  cur_surf = vp->lock();
  destptr = (uint16_t *)cur_surf->data();
  int rowsize = cur_surf->rowsize() / 2;
  int x1, y1, x2, y2;

  Editor()->wireframe_view->GetMagCoords(&x1, &y1, &x2, &y2);

  fix xstep = IntToFix(x2 - x1) / cur_surf->width();
  fix ystep = IntToFix(abs(y2 - y1)) / cur_surf->height();
  fix u = IntToFix(x1);
  fix v = IntToFix(y1);

  fix subx, suby;

  for (i = 0; i < cur_surf->height(); i++, v += ystep, u = IntToFix(x1))
    for (t = 0; t < cur_surf->width(); t++, u += xstep) {
      int x, y;
      x = FixToInt(u);
      y = FixToInt(v);

      y = (TERRAIN_DEPTH - 1) - y; // flip due to origin difference

      uint16_t fadepixel;

      int bm_handle =
          GameTextures[Terrain_tex_seg[Terrain_seg[y * TERRAIN_WIDTH + x].texseg_index].tex_index].bm_handle;
      lightval = Ubyte_to_float[(Terrain_seg[y * TERRAIN_WIDTH + x].l)];

      uint16_t pix;
      uint16_t *data = bm_data(bm_handle, 0);
      int w = bm_w(bm_handle, 0);

      subx = (u & 0xFFFF) * w;
      suby = (v & 0xFFFF) * bm_h(bm_handle, 0);
      subx >>= 16;
      suby >>= 16;

      pix = data[suby * w + subx];
      ddgr_color pix32 = GR_16_TO_COLOR(pix);

      int pred = (GR_COLOR_RED(pix32) * lightval);
      int pgreen = (GR_COLOR_GREEN(pix32) * lightval);
      int pblue = (GR_COLOR_BLUE(pix32) * lightval);

      fadepixel = GR_RGB16(pred, pgreen, pblue);

      if (TerrainSelected[y * TERRAIN_WIDTH + x]) {
        int red = ((fadepixel >> 10) & 0x1f) << 3;
        int green = ((fadepixel >> 5) & 0x1f) << 3;
        int blue = (fadepixel & 0x1f) << 3;

        red <<= 2;
        green <<= 2;
        blue <<= 2;

        red = std::min(255, red);
        green = std::min(255, green);
        blue = std::min(255, blue);

        fadepixel = GR_RGB16(red, green, blue);
      }

      if (Terrain_seg[y * TERRAIN_WIDTH + x].objects != -1) {
        object *obj = &Objects[Terrain_seg[y * TERRAIN_WIDTH + x].objects];

        if (obj->type == OBJ_ROBOT)
          fadepixel = GR_RGB16(255, 0, 0);
        else if (obj->type == OBJ_POWERUP)
          fadepixel = GR_RGB16(0, 128, 255);
        else if (obj->type == OBJ_PLAYER || obj->type == OBJ_GHOST)
          fadepixel = GR_RGB16(0, 255, 0);
        else if (obj->type == OBJ_CLUTTER)
          fadepixel = GR_RGB16(255, 0, 255);
      }

      destptr[i * rowsize + t] = fadepixel;
    }
  vp->unlock();
}

void CWireframeGrWnd::OnRButtonDown(UINT nFlags, CPoint point) {
  if (Editor_view_mode == VM_TERRAIN) {
    m_x1 = 0;
    m_y1 = 0;
    m_x2 = TERRAIN_WIDTH;
    m_y2 = TERRAIN_DEPTH;

    State_changed = 1;
  }
  CWnd::OnRButtonDown(nFlags, point);
}

// Lets the user draw free hand into the topographical map
void DrawIntoTopoMap(int x, int y) {
  int i, t, segx, segz;

  if (KEY_STATE(KEY_LSHIFT)) {
    int seg = Editor()->wireframe_view->GetCellFromPoint(x, y);
    if (seg < 0 || seg >= TERRAIN_WIDTH * TERRAIN_DEPTH)
      Int3(); // get Jason

    for (i = -1; i <= 1; i++) {
      for (t = -1; t <= 1; t++) {
        segx = seg % TERRAIN_WIDTH;
        segz = seg / TERRAIN_WIDTH;

        if ((segz + i) < 0 || segz + i >= TERRAIN_DEPTH)
          continue;
        if ((segx + t) < 0 || segx + t >= TERRAIN_WIDTH)
          continue;

        segz += i;
        segx += t;

        Terrain_tex_seg[Terrain_seg[(segz * TERRAIN_WIDTH) + segx].texseg_index].tex_index = D3EditState.texdlg_texture;
        Editor()->wireframe_view->DrawTerrainCell((segz * TERRAIN_WIDTH) + segx);
      }
    }
    Editor()->wireframe_view->Invalidate();
  }
}
