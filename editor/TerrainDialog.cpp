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

 * $Logfile: /DescentIII/Main/editor/TerrainDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * Terrain dialog implementaion
 *
 * $Log: not supported by cvs2svn $
 *
 * 75    4/29/99 3:49p Matt
 * Fixed compiler warning
 *
 * 74    4/27/99 3:38p Jason
 * fixed occlusion bug
 *
 * 73    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 72    2/26/99 3:32p Jason
 * made satellites clip properly
 *
 * 71    2/21/99 12:28p Matt
 * Added terrain sound system
 *
 * 70    1/24/99 5:44p Jason
 * added more selection choice for terrain
 *
 * 69    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 68    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 67    1/21/99 12:31a Jason
 * fixed stack bug
 *
 * 66    1/20/99 10:50a Jason
 * added new terrain
 *
 * 65    1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 64    1/05/99 4:14p Matt
 * Fixed compile warning
 *
 * 63    11/18/98 4:30p Jason
 * added some functionality to terrain fog
 *
 * 62    11/11/98 11:42a Jason
 * added sunlight damage
 *
 * 61    10/14/98 2:48p Kevin
 * Changed memory code to comply with mem lib
 *
 * 60    10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 59    9/29/98 12:53p Jason
 * added "force visiblity" for Luke
 *
 * 58    8/19/98 2:19p Jeff
 * moved detail globals to a struct
 *
 * 57    8/13/98 1:13p Jason
 * fixed terrain distance bug
 *
 * 56    7/20/98 12:04p Jason
 * added per level satellite lighting
 *
 * 55    6/04/98 6:45p Jason
 * made objects use the terrain occlusion system
 *
 * 54    6/04/98 6:16p Jason
 * added terrain occlusion system
 *
 * 53    5/19/98 3:19p Jason
 * cleaned up some texture flags
 *
 * 52    5/01/98 3:51p Jason
 * sped up terrain rendering by precaching all megacell lod bitmaps
 *
 * 51    4/29/98 5:00p Matt
 * Fixed stupid bug
 *
 * 50    4/29/98 3:58p Matt
 * Made the drop terrain function take a desired height, instead of always
 * moving the terrain to zero.
 *
 * 49    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 48    4/01/98 11:25a Jeff
 * Added an editor bool to skip Terrain object rendering
 *
 * 47    3/30/98 5:43p Jason
 * fixed pcx exporting
 *
 * 46    3/30/98 3:29p Jason
 * added the ability to save a pcx version of the terrain
 *
 * 45    3/23/98 6:06p Matt
 * Added code to "drop" the terrain so the lowest point has y==0, and to
 * move the buildings, objects, & paths with it.
 *
 * 44    3/06/98 6:15p Jason
 * Give message if no cells selected in smooth terrain
 *
 * 43    3/06/98 6:13p Jason
 * Made terrain smoothing work on selected cells only
 *
 * 42    2/17/98 4:17p Jason
 * fixed satellite placement
 *
 * 41    1/26/98 2:16p Jason
 * allowed toggle of visibility to multiple cells
 *
 * 40    1/16/98 8:06p Jason
 * added selectable halos and atmosphere blends to satellites
 *
 * 39    1/10/98 2:23p Jason
 * fixed terrain checksum problem
 *
 * 38    1/07/98 4:19p Jason
 * added dome to terrain sky
 *
 * 37    12/30/97 5:45p Jason
 * added toggleable fog
 *
 * 36    12/17/97 5:26p Jason
 * added support for selectable wraparound sky
 *
 * 35    12/11/97 1:41p Jason
 * added terrain smoothing
 *
 * 34    12/02/97 5:31p Samir
 * New file dialog interface implemented.
 *
 * 33    12/01/97 10:52a Jason
 * separated satellite and star rendering flags
 *
 * 32    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 31    10/06/97 12:16p Jason
 * Ripped out old mine/terrain connection code, plus added ability to move
 * satellites
 *
 * 30    10/02/97 6:10p Jason
 * made invisible cells not be LODable
 *
 * 29    10/02/97 2:45p Jason
 * got invisible terrain cells working
 *
 * 28    9/25/97 5:02p Jason
 * fixed bug caused by last rev where pixelerror and terraindistance would
 * be displayed
 *
 * 27    9/23/97 2:29p Jason
 * did terrain editing enhancements
 *
 * 26    9/17/97 1:01p Matt
 * Ripped out segment code
 *
 * 25    9/17/97 11:50a Jason
 * ripped out segment engine
 *
 * 24    9/15/97 5:54p Jason
 * delete room portals when deleting rooms connected to terrain
 *
 * 23    9/05/97 6:18p Jason
 * made pixel error setable to 0
 *
 * 22    9/02/97 10:47a Jason
 * use separate variables for game and editor LOD engine status
 *
 * 21    8/26/97 4:36p Jason
 * added terrain radiosity
 *
 * 20    8/25/97 12:04p Samir
 * Added scrolling capabilities for dialog.
 *
 * 19    8/22/97 10:17a Matt
 * When adding a room to the terrain, set the current face to be the one
 * opposite the portal face.
 *
 * $NoKeywords: $
 */

#include <algorithm>

#include "stdafx.h"
#include "editor.h"
#include "TerrainDialog.h"
#include "terrain.h"
#include "gametexture.h"
#include "bitmap.h"
#include "texture.h"
#include "group.h"
#include "editor/d3edit.h"
#include "room.h"
#include "erooms.h"
#include "roomuvs.h"
#include "SelectRangeDialog.h"
#include "findintersection.h"
#include "config.h"
#include "mem.h"
#include "gr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTerrainDialog dialog

CTerrainDialog::CTerrainDialog(CWnd *pParent /*=NULL*/) : CKeypadDialog(CTerrainDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CTerrainDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

  cc_mode = CC_MODE_SKY;
}

void CTerrainDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTerrainDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTerrainDialog, CDialog)
//{{AFX_MSG_MAP(CTerrainDialog)
ON_WM_SIZE()
ON_BN_CLICKED(IDC_TERRPAD_MOVE_UP, OnTerrpadMoveUp)
ON_BN_CLICKED(IDC_TERRPAD_MOVE_DOWN, OnTerrpadMoveDown)
ON_BN_CLICKED(IDC_TERRPAD_IMPORT, OnTerrpadImport)
ON_BN_CLICKED(IDC_TERRPAD_RENORMALIZE, OnTerrpadRenormalize)
ON_BN_CLICKED(IDC_TERRPAD_RAISE10, OnTerrpadRaise10)
ON_BN_CLICKED(IDC_TERRPAD_LOWER10, OnTerrpadLower10)
ON_BN_CLICKED(IDC_SKY_TEXTURE, OnSkyTexture)
ON_BN_CLICKED(IDC_TERRPAD_SELECT_NONE, OnTerrpadSelectNone)
ON_BN_CLICKED(IDC_TERRPAD_ROT_TEXTURE, OnTerrpadRotTexture)
ON_BN_CLICKED(IDC_SKY_NEARER, OnSkyNearer)
ON_BN_CLICKED(IDC_SKY_FARTHER, OnSkyFarther)
ON_BN_CLICKED(IDC_STARS_CHECK, OnStarsCheck)
ON_BN_CLICKED(IDC_FAST_TERRAIN_CHECK, OnFastTerrainCheck)
ON_BN_CLICKED(IDC_TERRPAD_FILL_AREA, OnTerrpadFillArea)
ON_BN_CLICKED(IDC_TERRPAD_REDO_TOPMAP, OnTerrpadRedoTopmap)
ON_BN_CLICKED(IDC_TERRPAD_MAKE_MAX, OnTerrpadMakeMax)
ON_BN_CLICKED(IDC_TERRPAD_MAKE_MIN, OnTerrpadMakeMin)
ON_BN_CLICKED(IDC_TERRPAD_MAKE_ZERO, OnTerrpadMakeZero)
ON_BN_CLICKED(IDC_TERRPAD_PYRAMID, OnTerrpadPyramid)
ON_BN_CLICKED(IDC_TERRPAD_HILL, OnTerrpadHill)
ON_BN_CLICKED(IDC_TERRPAD_PANCAKES, OnTerrpadPancakes)
ON_BN_CLICKED(IDC_TERR_MOVE_MOON, OnTerrMoveMoon)
ON_BN_CLICKED(IDC_TERR_RANDOMIZE_SKY, OnTerrRandomizeSky)
ON_WM_PAINT()
ON_BN_CLICKED(IDC_TERR_MORE_MOONS, OnTerrMoreMoons)
ON_BN_CLICKED(IDC_TERR_LESS_MOONS, OnTerrLessMoons)
ON_BN_CLICKED(IDC_TERR_NEXT_MOON, OnTerrNextMoon)
ON_BN_CLICKED(IDC_TERR_PREV_MOON, OnTerrPrevMoon)
ON_BN_CLICKED(IDC_SHOW_TERRAIN, OnShowTerrain)
ON_BN_CLICKED(IDC_FLAT_SHADE_TERRAIN_CHECK, OnFlatShadeTerrainCheck)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_TERR_SELECT_ALL, OnTerrSelectAll)
ON_BN_CLICKED(IDC_TERRAIN_2D, OnTerrain2d)
ON_BN_CLICKED(IDC_TEXTURE_SKY, OnTextureSky)
ON_EN_KILLFOCUS(IDC_SKY_RED_EDIT, OnKillfocusSkyRedEdit)
ON_EN_KILLFOCUS(IDC_SKY_GREEN_EDIT, OnKillfocusSkyGreenEdit)
ON_EN_KILLFOCUS(IDC_SKY_BLUE_EDIT, OnKillfocusSkyBlueEdit)
ON_BN_CLICKED(IDC_NO_LOD_ENGINE, OnNoLodEngine)
ON_EN_KILLFOCUS(IDC_FOG_DISTANCE_EDIT, OnKillfocusFogDistanceEdit)
ON_EN_KILLFOCUS(IDC_PIXEL_ERROR_EDIT, OnKillfocusPixelErrorEdit)
ON_BN_CLICKED(IDC_TERRPAD_SELECTRANGE, OnTerrpadSelectrange)
ON_WM_VSCROLL()
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_SKY_RADIO, OnSkyRadio)
ON_BN_CLICKED(IDC_HORIZON_RADIO, OnHorizonRadio)
ON_BN_CLICKED(IDC_FOG_RADIO, OnFogRadio)
ON_BN_CLICKED(IDC_TOGGLE_VISIBILITY, OnToggleVisibility)
ON_BN_CLICKED(IDC_SHOW_INVISIBLE, OnShowInvisible)
ON_BN_CLICKED(IDC_TERR_MOVE_MOON_AWAY, OnTerrMoveMoonAway)
ON_BN_CLICKED(IDC_MOVE_SAT_UP, OnMoveSatUp)
ON_BN_CLICKED(IDC_MOVE_SAT_DOWN, OnMoveSatDown)
ON_BN_CLICKED(IDC_MOVE_SAT_LEFT, OnMoveSatLeft)
ON_BN_CLICKED(IDC_MOVE_SAT_RIGHT, OnMoveSatRight)
ON_BN_CLICKED(IDC_SATELLITE_CHECK, OnSatelliteCheck)
ON_BN_CLICKED(IDC_SMOOTH_TERRAIN, OnSmoothTerrain)
ON_BN_CLICKED(IDC_USE_FOG, OnUseFog)
ON_BN_CLICKED(IDC_USE_HALO, OnUseHalo)
ON_BN_CLICKED(IDC_USE_ATMOSPHERE, OnUseAtmosphere)
ON_BN_CLICKED(IDC_DROP_TERRAIN, OnDropTerrain)
ON_BN_CLICKED(IDC_SAVE_AS_PCX, OnSaveAsPcx)
ON_BN_CLICKED(IDC_NO_EXT_ROOMS_OBJS, OnNoExtRoomsObjs)
ON_BN_CLICKED(IDC_TERRAIN_OCCLUSION, OnTerrainOcclusion)
ON_BN_CLICKED(IDC_SATELLITE_RADIO, OnSatelliteRadio)
ON_BN_CLICKED(IDC_FORCE_VISIBLE, OnForceVisible)
ON_EN_KILLFOCUS(IDC_DAMAGE_PER_SEC_EDIT, OnKillfocusDamagePerSecEdit)
ON_EN_KILLFOCUS(IDC_FOG_SCALAR_EDIT, OnKillfocusFogScalarEdit)
ON_BN_CLICKED(IDC_ROTATE_STARS, OnRotateStars)
ON_BN_CLICKED(IDC_ROTATE_SKY, OnRotateSky)
ON_EN_KILLFOCUS(IDC_ROTATE_SPEED_EDIT, OnKillfocusRotateSpeedEdit)
ON_BN_CLICKED(IDC_TILE_MORE, OnTileMore)
ON_BN_CLICKED(IDC_TILE_LESS, OnTileLess)
ON_BN_CLICKED(IDC_TERR_SOUND, OnTerrSound)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTerrainDialog message handlers

void CTerrainDialog::OnSize(UINT nType, int cx, int cy) {
  CKeypadDialog::OnSize(nType, cx, cy);

  Current_satellite = 0;
  cc_mode = CC_MODE_SKY;
}

void CTerrainDialog::DrawSwatch(int handle, int r, int g, int b) {
  CWnd *texwnd;
  RECT rect;
  int w, h;

  texwnd = GetDlgItem(handle);
  texwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  ddgr_color color = GR_RGB(r, g, b);

  Desktop_surf->clear(rect.left, rect.top, w, h, color);

  Desktop_surf->attach_to_window(NULL);
}

void CTerrainDialog::UpdateDialog() {
  CButton *bbox;
  char str[20];
  CEdit *ebox;

  if (!m_Active)
    return;

  ebox = (CEdit *)GetDlgItem(IDC_DAMAGE_PER_SEC_EDIT);
  sprintf(str, "%f", Terrain_sky.damage_per_second);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_FOG_SCALAR_EDIT);
  sprintf(str, "%f", Terrain_sky.fog_scalar);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_FOG_DISTANCE_EDIT);
  sprintf(str, "%f", Detail_settings.Terrain_render_distance / TERRAIN_SIZE);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_PIXEL_ERROR_EDIT);
  sprintf(str, "%f", Detail_settings.Pixel_error);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_NUM_MOONS_STATIC);
  sprintf(str, "Num of sats:%d", Terrain_sky.num_satellites);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_CUR_MOON_STATIC);
  sprintf(str, "Current sat:%d", Current_satellite);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_ROTATE_SPEED_EDIT);
  sprintf(str, "%f", Terrain_sky.rotate_rate);
  ebox->SetWindowText(str);

  CheckDlgButton(IDC_TEXTURE_SKY, Terrain_sky.textured ? 1 : 0);
  CheckDlgButton(IDC_STARS_CHECK, Terrain_sky.flags & TF_STARS ? 1 : 0);
  CheckDlgButton(IDC_ROTATE_STARS, Terrain_sky.flags & TF_ROTATE_STARS ? 1 : 0);
  CheckDlgButton(IDC_ROTATE_SKY, Terrain_sky.flags & TF_ROTATE_SKY ? 1 : 0);
  CheckDlgButton(IDC_SATELLITE_CHECK, Terrain_sky.flags & TF_SATELLITES ? 1 : 0);
  CheckDlgButton(IDC_USE_FOG, Terrain_sky.flags & TF_FOG ? 1 : 0);
  CheckDlgButton(IDC_USE_HALO, Terrain_sky.satellite_flags[Current_satellite] & TSF_HALO ? 1 : 0);
  CheckDlgButton(IDC_USE_ATMOSPHERE, Terrain_sky.satellite_flags[Current_satellite] & TSF_ATMOSPHERE ? 1 : 0);

  CheckDlgButton(IDC_FAST_TERRAIN_CHECK, Fast_terrain ? 1 : 0);
  CheckDlgButton(IDC_SHOW_TERRAIN, D3EditState.terrain_dots ? 1 : 0);
  CheckDlgButton(IDC_FLAT_SHADE_TERRAIN_CHECK, D3EditState.terrain_flat_shade ? 1 : 0);
  CheckDlgButton(IDC_NO_LOD_ENGINE, Editor_LOD_engine_off ? 1 : 0);
  CheckDlgButton(IDC_NO_EXT_ROOMS_OBJS, Terrain_render_ext_room_objs ? 0 : 1);

  bbox = (CButton *)GetDlgItem(IDC_SKY_RADIO);
  bbox->SetCheck(cc_mode == CC_MODE_SKY);

  bbox = (CButton *)GetDlgItem(IDC_HORIZON_RADIO);
  bbox->SetCheck(cc_mode == CC_MODE_HORIZON);

  bbox = (CButton *)GetDlgItem(IDC_FOG_RADIO);
  bbox->SetCheck(cc_mode == CC_MODE_FOG);

  bbox = (CButton *)GetDlgItem(IDC_SATELLITE_RADIO);
  bbox->SetCheck(cc_mode == CC_MODE_SAT);

  // Draw swatches
  DrawSwatch(IDC_SKY_SWATCH, GR_COLOR_RED(Terrain_sky.sky_color), GR_COLOR_GREEN(Terrain_sky.sky_color),
             GR_COLOR_BLUE(Terrain_sky.sky_color));
  DrawSwatch(IDC_HORIZON_SWATCH, GR_COLOR_RED(Terrain_sky.horizon_color), GR_COLOR_GREEN(Terrain_sky.horizon_color),
             GR_COLOR_BLUE(Terrain_sky.horizon_color));
  DrawSwatch(IDC_FOG_SWATCH, GR_COLOR_RED(Terrain_sky.fog_color), GR_COLOR_GREEN(Terrain_sky.fog_color),
             GR_COLOR_BLUE(Terrain_sky.fog_color));

  // Draw satellite swatch
  float maxc = std::max(Terrain_sky.satellite_r[Current_satellite], Terrain_sky.satellite_g[Current_satellite]);
  maxc = std::max(Terrain_sky.satellite_b[Current_satellite], maxc);

  float r, g, b;

  if (maxc > 1.0) {
    r = Terrain_sky.satellite_r[Current_satellite] / maxc;
    g = Terrain_sky.satellite_g[Current_satellite] / maxc;
    b = Terrain_sky.satellite_b[Current_satellite] / maxc;
  } else {
    r = Terrain_sky.satellite_r[Current_satellite];
    g = Terrain_sky.satellite_g[Current_satellite];
    b = Terrain_sky.satellite_b[Current_satellite];
  }

  r *= 255.0;
  g *= 255.0;
  b *= 255.0;

  DrawSwatch(IDC_SATELLITE_SWATCH, r, g, b);

  if (cc_mode != CC_MODE_SAT) {
    int r, g, b;

    if (cc_mode == CC_MODE_SKY) {
      r = GR_COLOR_RED(Terrain_sky.sky_color);
      g = GR_COLOR_GREEN(Terrain_sky.sky_color);
      b = GR_COLOR_BLUE(Terrain_sky.sky_color);
    } else if (cc_mode == CC_MODE_HORIZON) {
      r = GR_COLOR_RED(Terrain_sky.horizon_color);
      g = GR_COLOR_GREEN(Terrain_sky.horizon_color);
      b = GR_COLOR_BLUE(Terrain_sky.horizon_color);
    } else {
      r = GR_COLOR_RED(Terrain_sky.fog_color);
      g = GR_COLOR_GREEN(Terrain_sky.fog_color);
      b = GR_COLOR_BLUE(Terrain_sky.fog_color);
    }

    ebox = (CEdit *)GetDlgItem(IDC_SKY_RED_EDIT);
    sprintf(str, "%d", r);
    ebox->SetWindowText(str);

    ebox = (CEdit *)GetDlgItem(IDC_SKY_GREEN_EDIT);
    sprintf(str, "%d", g);
    ebox->SetWindowText(str);

    ebox = (CEdit *)GetDlgItem(IDC_SKY_BLUE_EDIT);
    sprintf(str, "%d", b);
    ebox->SetWindowText(str);
  } else {

    ebox = (CEdit *)GetDlgItem(IDC_SKY_RED_EDIT);
    sprintf(str, "%f", Terrain_sky.satellite_r[Current_satellite]);
    ebox->SetWindowText(str);

    ebox = (CEdit *)GetDlgItem(IDC_SKY_GREEN_EDIT);
    sprintf(str, "%f", Terrain_sky.satellite_g[Current_satellite]);
    ebox->SetWindowText(str);

    ebox = (CEdit *)GetDlgItem(IDC_SKY_BLUE_EDIT);
    sprintf(str, "%f", Terrain_sky.satellite_b[Current_satellite]);
    ebox->SetWindowText(str);
  }
}

void CTerrainDialog::OnTerrpadMoveUp() {
  int i;

  for (i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
    if (TerrainSelected[i]) {
      int cury = Terrain_seg[i].ypos;
      if (cury <= 254) {
        Terrain_seg[i].ypos++;
        Terrain_seg[i].y += (float)(TERRAIN_HEIGHT_INCREMENT);
        TV_changed++;
      }
    }
  }
}

void CTerrainDialog::OnTerrpadMoveDown() {
  for (int i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
    if (TerrainSelected[i]) {
      int cury = Terrain_seg[i].ypos;
      if (cury > 0) {
        Terrain_seg[i].ypos--;
        Terrain_seg[i].y -= (float)(TERRAIN_HEIGHT_INCREMENT);
        TV_changed++;
      }
    }
  }
}

void CTerrainDialog::RunKeypadFunction(int code) {
  switch (code) {
  case VK_ADD:
    OnTerrpadMoveDown();
    break;
  case VK_SUBTRACT:
    OnTerrpadMoveUp();
    break;
  }
}

void CTerrainDialog::OnTerrpadImport() {
  char filename[255];

  CString filter = "PCX files (*.pcx)|*.pcx||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  LoadPCXTerrain(filename);
}

void CTerrainDialog::OnTerrpadRenormalize() {
  mprintf(0, "Building terrain normals...this might take a couple of seconds.\n");

  Terrain_checksum = -1;
  BuildMinMaxTerrain();
  BuildTerrainNormals();
  State_changed = 1;
}

void CTerrainDialog::OnTerrpadRaise10() {
  for (int i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
    if (TerrainSelected[i]) {
      int cury = Terrain_seg[i].ypos;
      if (cury < 255 - 10) {
        Terrain_seg[i].ypos += 10;
        Terrain_seg[i].y += (float)(10 * (TERRAIN_HEIGHT_INCREMENT));
        TV_changed++;
      }
    }
  }
}

void CTerrainDialog::OnTerrpadLower10() {

  for (int i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
    if (TerrainSelected[i]) {
      int cury = Terrain_seg[i].ypos;
      if (cury > 9) {
        Terrain_seg[i].ypos -= 10;
        Terrain_seg[i].y -= (float)(10 * (TERRAIN_HEIGHT_INCREMENT));
        TV_changed++;
      }
    }
  }
}

void CTerrainDialog::OnSkyTexture() { TV_changed = 1; }

void CTerrainDialog::OnTerrpadSelectNone() {
  for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++)
    TerrainSelected[i] = 0;
  Num_terrain_selected = 0;
  World_changed = 1;
}

void CTerrainDialog::OnTerrpadRotTexture() {
  int i;
  uint8_t touched[TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH];
  memset(touched, 0, TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH);

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (!touched[Terrain_seg[i].texseg_index]) {
        int val = Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation & 0x0F;
        val++;
        val %= 4;
        Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation &= ~0x0F;
        Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation |= val;
        touched[Terrain_seg[i].texseg_index] = 1;
      }
    }
  }

  World_changed = 1;
  TV_changed = 1;
}

void CTerrainDialog::OnSkyNearer() {

  if (Terrain_sky.radius > 500) {

    SetupSky(Terrain_sky.radius - 500, Terrain_sky.flags);
    TV_changed = 1;
  }
}

void CTerrainDialog::OnSkyFarther() {
  SetupSky(Terrain_sky.radius + 500, Terrain_sky.flags);
  TV_changed = 1;
}

void CTerrainDialog::OnStarsCheck() {
  int c = IsDlgButtonChecked(IDC_STARS_CHECK);

  if (c)
    Terrain_sky.flags |= TF_STARS;
  else
    Terrain_sky.flags &= ~TF_STARS;

  TV_changed = 1;
}

void CTerrainDialog::OnFastTerrainCheck() {
  int c = IsDlgButtonChecked(IDC_FAST_TERRAIN_CHECK);

  if (c)
    Fast_terrain = 1;
  else
    Fast_terrain = 0;

  TV_changed = 1;
}

void CTerrainDialog::OnTerrpadFillArea() {
  int i;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++)
    if (TerrainSelected[i])
      Terrain_tex_seg[Terrain_seg[i].texseg_index].tex_index = D3EditState.texdlg_texture;

  World_changed = 1;
}

void CTerrainDialog::OnTerrpadRedoTopmap() { World_changed = 1; }

void CTerrainDialog::OnTerrpadMakeMax() {
  int max_so_far = 0, i;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (Terrain_seg[i].ypos > max_so_far)
        max_so_far = Terrain_seg[i].ypos;
    }
  }

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      Terrain_seg[i].ypos = max_so_far;
      Terrain_seg[i].y = max_so_far * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  World_changed = 1;
}

void CTerrainDialog::OnTerrpadMakeMin() {
  int min_so_far = 9999, i;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (Terrain_seg[i].ypos < min_so_far)
        min_so_far = Terrain_seg[i].ypos;
    }
  }

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      Terrain_seg[i].ypos = min_so_far;
      Terrain_seg[i].y = min_so_far * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  World_changed = 1;
}

void CTerrainDialog::OnTerrpadMakeZero() {
  int i;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      Terrain_seg[i].ypos = 0;
      Terrain_seg[i].y = 0;
    }
  }

  World_changed = 1;
}

// Makes a pyramid out of the selected region
void CTerrainDialog::OnTerrpadPyramid() {
  int left = TERRAIN_WIDTH, right = 0;
  int top = TERRAIN_DEPTH, bottom = 0;

  int i, t, x, y;
  int max_so_far = 0;
  int min_so_far = 999;

  // First find highest/lowest point
  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (Terrain_seg[i].ypos > max_so_far)
        max_so_far = Terrain_seg[i].ypos;
      if (Terrain_seg[i].ypos < min_so_far)
        min_so_far = Terrain_seg[i].ypos;
    }
  }

  // Now get dimensions of selection
  for (i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
    if (TerrainSelected[i]) {
      x = i % TERRAIN_WIDTH;
      y = i / TERRAIN_WIDTH;

      if (x > right)
        right = x;
      if (x < left)
        left = x;

      if (y > bottom)
        bottom = y;

      if (y < top)
        top = y;
    }
  }

  int width = (right - left);
  int height = (bottom - top);

  int hdiff = max_so_far - min_so_far;

  if (hdiff == 0) {
    MessageBox("The area you selected is flat.  Pull a point up to the desired height and then retry this operation.");
    return;
  }

  fix xstep = IntToFix(hdiff) / (width / 2);
  fix ystep = IntToFix(hdiff) / (height / 2);

  // upper left
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((top + i) * TERRAIN_WIDTH) + (t + left);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  // upper right
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((top + i) * TERRAIN_WIDTH) + (right - t);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  // lower left
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((bottom - i) * TERRAIN_WIDTH) + (left + t);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  // lower right
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((bottom - i) * TERRAIN_WIDTH) + (right - t);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  World_changed = 1;
}

void CTerrainDialog::OnTerrpadHill() {}

void CTerrainDialog::OnTerrpadPancakes() {
  int left = TERRAIN_WIDTH, right = 0;
  int top = TERRAIN_DEPTH, bottom = 0;

  int i, t, x, y;
  int max_so_far = 0;
  int min_so_far = 999;

  // First find highest/lowest point
  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (Terrain_seg[i].ypos > max_so_far)
        max_so_far = Terrain_seg[i].ypos;
      if (Terrain_seg[i].ypos < min_so_far)
        min_so_far = Terrain_seg[i].ypos;
    }
  }

  // Now get dimensions of selection
  for (i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH; i++) {
    if (TerrainSelected[i]) {
      x = i % TERRAIN_WIDTH;
      y = i / TERRAIN_WIDTH;

      if (x > right)
        right = x;
      if (x < left)
        left = x;

      if (y > bottom)
        bottom = y;

      if (y < top)
        top = y;
    }
  }

  int width = (right - left);
  int height = (bottom - top);

  int hdiff = max_so_far - min_so_far;

  if (hdiff == 0) {
    MessageBox("The area you selected is flat.  Pull a point up to the desired height and then retry this operation.");
    return;
  }

  fix xstep = IntToFix(hdiff) / (width / 2);
  fix ystep = IntToFix(hdiff) / (height / 2);

  // upper left
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((top + i) * TERRAIN_WIDTH) + (t + left);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  // upper right
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((top + i) * TERRAIN_WIDTH) + (right - t);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  // lower left
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((bottom - i) * TERRAIN_WIDTH) + (left + t);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  // lower right
  for (i = 0; i <= (height / 2); i++) {
    for (t = 0; t <= (width / 2); t++) {

      int xa, ya, a;

      xa = FixToInt(xstep * t);
      ya = FixToInt(ystep * i);

      a = std::max(xa, ya);

      int seg = ((bottom - i) * TERRAIN_WIDTH) + (right - t);

      Terrain_seg[seg].ypos = min_so_far + a;
      Terrain_seg[seg].y = (min_so_far + a) * (TERRAIN_HEIGHT_INCREMENT);
    }
  }

  World_changed = 1;
}

void CTerrainDialog::OnTerrMoveMoon() {
  int n = Current_satellite;

  Terrain_sky.satellite_size[n] *= 1.1f;

  TV_changed = 1;
}

void CTerrainDialog::OnTerrRandomizeSky() {
  SetupSky(Terrain_sky.radius, Terrain_sky.flags, 1);
  TV_changed = 1;
}

void CTerrainDialog::OnPaint() {
  CPaintDC dc(this); // device context for painting

  UpdateDialog();

  // Do not call CDialog::OnPaint() for painting messages
}

void CTerrainDialog::OnTerrMoreMoons() {
  if (Terrain_sky.num_satellites < 5)
    Terrain_sky.num_satellites++;

  TV_changed = 1;

  UpdateDialog();
}

void CTerrainDialog::OnTerrLessMoons() {
  if (Terrain_sky.num_satellites > 0)
    Terrain_sky.num_satellites--;

  TV_changed = 1;

  UpdateDialog();
}

void CTerrainDialog::OnTerrNextMoon() {
  Current_satellite++;

  Current_satellite %= 5;

  UpdateDialog();
}

void CTerrainDialog::OnTerrPrevMoon() {
  Current_satellite--;
  if (Current_satellite < 0)
    Current_satellite = 4;

  UpdateDialog();
}

void CTerrainDialog::OnShowTerrain() {
  int c = IsDlgButtonChecked(IDC_SHOW_TERRAIN);

  D3EditState.terrain_dots = (c != 0);

  State_changed = 1;
}

void CTerrainDialog::OnFlatShadeTerrainCheck() {
  int c = IsDlgButtonChecked(IDC_FLAT_SHADE_TERRAIN_CHECK);

  D3EditState.terrain_flat_shade = (c != 0);

  if (c) {
    Terrain_texture_distance = 0;
    Detail_settings.Terrain_render_distance = DEFAULT_VISIBLE_TERRAIN_DISTANCE * 2;
  } else {
    Terrain_texture_distance = 9999999;
    Detail_settings.Terrain_render_distance = DEFAULT_VISIBLE_TERRAIN_DISTANCE;
  }

  State_changed = 1;
}

BOOL CTerrainDialog::OnHelpInfo(HELPINFO *pHelpInfo) {

  WinHelp(HID_TERRAINTAB, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CTerrainDialog::OnTerrSelectAll() {

  int i;

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++)
    TerrainSelected[i] = 1;

  Num_terrain_selected = TERRAIN_WIDTH * TERRAIN_DEPTH;
  World_changed = 1;
}

void CTerrainDialog::OnTerrain2d() {
  int c = IsDlgButtonChecked(IDC_TERRAIN_2D);

  if (c) {
    Flat_terrain = 1;
  } else {
    Flat_terrain = 0;
  }

  State_changed = 1;
}

void CTerrainDialog::SetCurrentMoon(int n) {
  Current_satellite = n;
  UpdateDialog();
}

void CTerrainDialog::OnTextureSky() {
  int c = IsDlgButtonChecked(IDC_TEXTURE_SKY);
  Terrain_sky.textured = c;

  World_changed = 1;
}

void CTerrainDialog::OnKillfocusSkyRedEdit() {
  CEdit *ebox;
  char str[20];
  int r, g, b, nr;
  float fv;

  if (cc_mode == CC_MODE_SKY) {
    r = GR_COLOR_RED(Terrain_sky.sky_color);
    g = GR_COLOR_GREEN(Terrain_sky.sky_color);
    b = GR_COLOR_BLUE(Terrain_sky.sky_color);
  } else if (cc_mode == CC_MODE_HORIZON) {
    r = GR_COLOR_RED(Terrain_sky.horizon_color);
    g = GR_COLOR_GREEN(Terrain_sky.horizon_color);
    b = GR_COLOR_BLUE(Terrain_sky.horizon_color);
  } else {
    r = GR_COLOR_RED(Terrain_sky.fog_color);
    g = GR_COLOR_GREEN(Terrain_sky.fog_color);
    b = GR_COLOR_BLUE(Terrain_sky.fog_color);
  }

  ebox = (CEdit *)GetDlgItem(IDC_SKY_RED_EDIT);
  ebox->GetWindowText(str, 20);

  if (cc_mode != CC_MODE_SAT) {
    nr = atoi(str);
    if (nr < 0)
      nr = 0;
    if (nr > 255)
      nr = 255;

    if (cc_mode == CC_MODE_SKY)
      Terrain_sky.sky_color = GR_RGB(nr, g, b);
    else if (cc_mode == CC_MODE_HORIZON)
      Terrain_sky.horizon_color = GR_RGB(nr, g, b);
    else
      Terrain_sky.fog_color = GR_RGB(nr, g, b);
  } else {
    fv = atof(str);
    if (fv < 0)
      fv = 0;

    Terrain_sky.satellite_r[Current_satellite] = fv;
  }

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnKillfocusSkyGreenEdit() {
  CEdit *ebox;
  char str[20];
  int r, g, b, nr;
  float fv;

  if (cc_mode == CC_MODE_SKY) {
    r = GR_COLOR_RED(Terrain_sky.sky_color);
    g = GR_COLOR_GREEN(Terrain_sky.sky_color);
    b = GR_COLOR_BLUE(Terrain_sky.sky_color);
  } else if (cc_mode == CC_MODE_HORIZON) {
    r = GR_COLOR_RED(Terrain_sky.horizon_color);
    g = GR_COLOR_GREEN(Terrain_sky.horizon_color);
    b = GR_COLOR_BLUE(Terrain_sky.horizon_color);
  } else {
    r = GR_COLOR_RED(Terrain_sky.fog_color);
    g = GR_COLOR_GREEN(Terrain_sky.fog_color);
    b = GR_COLOR_BLUE(Terrain_sky.fog_color);
  }

  ebox = (CEdit *)GetDlgItem(IDC_SKY_GREEN_EDIT);
  ebox->GetWindowText(str, 20);

  if (cc_mode != CC_MODE_SAT) {
    nr = atoi(str);
    if (nr < 0)
      nr = 0;
    if (nr > 255)
      nr = 255;

    if (cc_mode == CC_MODE_SKY)
      Terrain_sky.sky_color = GR_RGB(r, nr, b);
    else if (cc_mode == CC_MODE_HORIZON)
      Terrain_sky.horizon_color = GR_RGB(r, nr, b);
    else
      Terrain_sky.fog_color = GR_RGB(r, nr, b);
  } else {
    fv = atof(str);
    if (fv < 0)
      fv = 0;

    Terrain_sky.satellite_g[Current_satellite] = fv;
  }

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnKillfocusSkyBlueEdit() {
  CEdit *ebox;
  char str[20];
  int r, g, b, nr;
  float fv;

  if (cc_mode == CC_MODE_SKY) {
    r = GR_COLOR_RED(Terrain_sky.sky_color);
    g = GR_COLOR_GREEN(Terrain_sky.sky_color);
    b = GR_COLOR_BLUE(Terrain_sky.sky_color);
  } else if (cc_mode == CC_MODE_HORIZON) {
    r = GR_COLOR_RED(Terrain_sky.horizon_color);
    g = GR_COLOR_GREEN(Terrain_sky.horizon_color);
    b = GR_COLOR_BLUE(Terrain_sky.horizon_color);
  } else {
    r = GR_COLOR_RED(Terrain_sky.fog_color);
    g = GR_COLOR_GREEN(Terrain_sky.fog_color);
    b = GR_COLOR_BLUE(Terrain_sky.fog_color);
  }

  ebox = (CEdit *)GetDlgItem(IDC_SKY_BLUE_EDIT);
  ebox->GetWindowText(str, 20);

  if (cc_mode != CC_MODE_SAT) {
    nr = atoi(str);
    if (nr < 0)
      nr = 0;
    if (nr > 255)
      nr = 255;

    if (cc_mode == CC_MODE_SKY)
      Terrain_sky.sky_color = GR_RGB(r, g, nr);
    else if (cc_mode == CC_MODE_HORIZON)
      Terrain_sky.horizon_color = GR_RGB(r, g, nr);
    else
      Terrain_sky.fog_color = GR_RGB(r, g, nr);
  } else {
    fv = atof(str);
    if (fv < 0)
      fv = 0;

    Terrain_sky.satellite_b[Current_satellite] = fv;
  }

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnNoLodEngine() {

  int c = IsDlgButtonChecked(IDC_NO_LOD_ENGINE);

  Editor_LOD_engine_off = c;

  State_changed = 1;
}

void CTerrainDialog::OnKillfocusFogDistanceEdit() {
  CEdit *ebox;
  char str[20];
  float predist;
  float dist;

  ebox = (CEdit *)GetDlgItem(IDC_FOG_DISTANCE_EDIT);
  ebox->GetWindowText(str, 20);

  predist = atof(str);

  if (predist < 20)
    predist = 20;
  if (predist > 200)
    predist = 200;

  dist = predist * TERRAIN_SIZE;

  Detail_settings.Terrain_render_distance = dist;

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnKillfocusPixelErrorEdit() {
  CEdit *ebox;
  char str[20];
  float err;

  ebox = (CEdit *)GetDlgItem(IDC_PIXEL_ERROR_EDIT);
  ebox->GetWindowText(str, 20);

  err = atof(str);
  if (err < 0)
    err = 0;
  if (err > 64)
    err = 64;

  Detail_settings.Pixel_error = err;

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnTerrpadSelectrange() {
  SelectRangeDialog dlg;

  Editor()->pause();
  dlg.DoModal();
  World_changed = 1;
  Editor()->resume();
}

//	These functions allow the terrain keypad to scroll!!

void CTerrainDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  // TODO: Add your message handler code here and/or call default

  CKeypadDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTerrainDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  // TODO: Add your message handler code here and/or call default

  CKeypadDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTerrainDialog::OnSkyRadio() {

  cc_mode = CC_MODE_SKY;
  UpdateDialog();
}

void CTerrainDialog::OnHorizonRadio() {

  cc_mode = CC_MODE_HORIZON;
  UpdateDialog();
}

void CTerrainDialog::OnFogRadio() {
  cc_mode = CC_MODE_FOG;
  UpdateDialog();
}

void CTerrainDialog::OnToggleVisibility() {

  for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      int c = Terrain_seg[i].flags & TF_INVISIBLE;

      if (c)
        Terrain_seg[i].flags &= ~TF_INVISIBLE;
      else
        Terrain_seg[i].flags |= TF_INVISIBLE;

      World_changed = 1;
    }
  }

  if (World_changed)
    GenerateLODDeltas();
}

void CTerrainDialog::OnShowInvisible() {
  int c = IsDlgButtonChecked(IDC_SHOW_INVISIBLE);

  Show_invisible_terrain = c;

  State_changed = 1;
}

void CTerrainDialog::OnTerrMoveMoonAway() {
  int n = Current_satellite;

  Terrain_sky.satellite_size[n] *= .9f;

  TV_changed = 1;
}

void CTerrainDialog::MoveSat(int pitch, int heading) {
  int n = Current_satellite;
  matrix rot_matrix, orient;
  vm_AnglesToMatrix(&rot_matrix, pitch, heading, 0); // move up a little

  orient = rot_matrix;

  vector sat_vec = Terrain_sky.satellite_vectors[n] - Viewer_object->pos;
  float mag = vm_GetMagnitude(&sat_vec);
  vector rot_vec;

  vm_NormalizeVector(&sat_vec);
  vm_MatrixMulVector(&rot_vec, &sat_vec, &orient);

  Terrain_sky.satellite_vectors[n] = Viewer_object->pos + (rot_vec * mag);
}

void CTerrainDialog::OnMoveSatUp() {
  MoveSat(1500, 0);
  TV_changed = 1;
}

void CTerrainDialog::OnMoveSatDown() {
  MoveSat(64000, 0);
  TV_changed = 1;
}

void CTerrainDialog::OnMoveSatLeft() {
  MoveSat(0, 64000);
  TV_changed = 1;
}

void CTerrainDialog::OnMoveSatRight() {
  MoveSat(0, 1500);
  TV_changed = 1;
}

void CTerrainDialog::OnSatelliteCheck() {
  int c = IsDlgButtonChecked(IDC_SATELLITE_CHECK);

  if (c)
    Terrain_sky.flags |= TF_SATELLITES;
  else
    Terrain_sky.flags &= ~TF_SATELLITES;

  TV_changed = 1;
}

void CTerrainDialog::OnSmoothTerrain() {
  uint8_t *src_data;
  int y, x;

  if (Num_terrain_selected == 0) {
    OutrageMessageBox("This operation works on selected cells.  You have no cells selected!");
    return;
  }

  if ((MessageBox("Are you sure you wish to smooth the terrain?  This operation cannot be undone.", "Question",
                  MB_YESNO)) == IDNO)
    return;

  src_data = (uint8_t *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH);
  ASSERT(src_data); // Ran out of memory!

  for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++)
    src_data[i] = Terrain_seg[i].ypos;

  int w = TERRAIN_WIDTH;
  int h = TERRAIN_DEPTH;

  for (y = 0; y < h; y++) {
    for (x = 0; x < w; x++) {
      if (!TerrainSelected[y * w + x])
        continue;

      int total = 0;
      int num = 0;

      total += src_data[y * w + x];
      num++;

      // Left edge
      if (x != 0) {

        total += src_data[y * w + (x - 1)];
        num++;

        if (y != 0) {
          total += src_data[(y - 1) * w + (x - 1)];
          num++;
        }

        if (y != h - 1) {
          total += src_data[(y + 1) * w + (x - 1)];
          num++;
        }
      }

      // Right edge
      if (x != (w - 1)) {
        total += src_data[(y)*w + (x + 1)];
        num++;

        if (y != 0) {
          total += src_data[(y - 1) * w + (x + 1)];
          num++;
        }

        if (y != h - 1) {
          total += src_data[(y + 1) * w + (x + 1)];
          num++;
        }
      }

      // Center
      if (y != 0) {
        total += src_data[(y - 1) * w + (x)];
        num++;
      }

      if (y != h - 1) {
        total += src_data[(y + 1) * w + (x)];
        num++;
      }

      if (num > 0) {
        total /= num;
        Terrain_seg[y * w + x].ypos = total;
      }
    }
  }

  mem_free(src_data);
  BuildMinMaxTerrain();
  OutrageMessageBox("Terrain smoothed!");
  World_changed = 1;
}

void CTerrainDialog::OnUseFog() {
  int c = IsDlgButtonChecked(IDC_USE_FOG);

  if (c)
    Terrain_sky.flags |= TF_FOG;
  else
    Terrain_sky.flags &= ~TF_FOG;

  World_changed = 1;
}

void CTerrainDialog::OnUseHalo() {
  int n = Current_satellite;
  int c = IsDlgButtonChecked(IDC_USE_HALO);

  if (c)
    Terrain_sky.satellite_flags[n] |= TSF_HALO;
  else
    Terrain_sky.satellite_flags[n] &= ~TSF_HALO;

  World_changed = 1;
}

void CTerrainDialog::OnUseAtmosphere() {
  int n = Current_satellite;
  int c = IsDlgButtonChecked(IDC_USE_ATMOSPHERE);

  if (c)
    Terrain_sky.satellite_flags[n] |= TSF_ATMOSPHERE;
  else
    Terrain_sky.satellite_flags[n] &= ~TSF_ATMOSPHERE;

  World_changed = 1;
}

#include "gamepath.h"
#include "EditLineDialog.h"

void CTerrainDialog::OnDropTerrain() {
  int desired_height, lowest_height, highest_height, delta_height;
  int x, y;

  // Find lowest & highest terrain values
  for (x = 0, lowest_height = INT_MAX, highest_height = 0; x < TERRAIN_WIDTH; x++)
    for (y = 0; y < TERRAIN_DEPTH; y++) {
      if (Terrain_seg[x * TERRAIN_WIDTH + y].ypos < lowest_height)
        lowest_height = Terrain_seg[x * TERRAIN_WIDTH + y].ypos;
      if (Terrain_seg[x * TERRAIN_WIDTH + y].ypos > highest_height)
        highest_height = Terrain_seg[x * TERRAIN_WIDTH + y].ypos;
    }

  // Get desired terrain level
get_height:;
  if (!InputNumber(&desired_height, "Raise/Lower Terrain", "Enter the desired height for the lowest terrain point:"))
    return;

  // Check valid values
  if ((desired_height < 0) || (desired_height > 255)) {
    OutrageMessageBox("Invalid value: the height must be between 0 and 255, inclusive.");
    goto get_height;
  }
  if (((highest_height - lowest_height) + desired_height) > 255) {
    OutrageMessageBox("The delta height of the terrain is %d, so you cannot set the lowest point above %d.",
                      highest_height - lowest_height, 255 - (highest_height - lowest_height));
    goto get_height;
  }

  // Compute delta
  delta_height = desired_height - lowest_height;

  // Now lower the terrain
  for (x = 0; x < TERRAIN_WIDTH; x++)
    for (y = 0; y < TERRAIN_DEPTH; y++)
      Terrain_seg[x * TERRAIN_WIDTH + y].ypos += delta_height;

  // Update stuff
  BuildMinMaxTerrain();

  // How much we move by
  float delta_y = delta_height * TERRAIN_HEIGHT_INCREMENT;

  int r, v, o, p, n;
  room *rp;

  // Drop all the rooms
  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++)
    if (rp->used)
      for (v = 0; v < rp->num_verts; v++)
        rp->verts[v].y += delta_y;

  // Drop all the objects
  for (o = 0; o <= Highest_object_index; o++)
    if (Objects[o].type != OBJ_NONE) {
      vector new_pos = Objects[o].pos;
      new_pos.y += delta_y;
      ObjSetPos(&Objects[o], &new_pos, Objects[o].roomnum, NULL, false);
    }

  // Drop all the paths
  for (p = 0; p < Num_game_paths; p++)
    for (n = 0; n < GamePaths[p].num_nodes; n++)
      GamePaths[p].pathnodes[n].pos.y += delta_y;

  // Done
  EditorStatus("Terrain moved by by %d to %d", delta_height, desired_height);
  World_changed = 1;
}

void CTerrainDialog::OnSaveAsPcx() {

  char filename[255];

  CString filter = "PCX files (*.pcx)|*.pcx||";

  if (!SaveFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  CFILE *outfile;

  outfile = (CFILE *)cfopen(filename, "wb");
  if (!outfile) {
    OutrageMessageBox("Couldn't open that filename to save to!");
    return;
  }

  // Header info
  cf_WriteByte(outfile, 10);
  cf_WriteByte(outfile, 5);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, 8);

  // Dimensions of image
  cf_WriteShort(outfile, 0);
  cf_WriteShort(outfile, 0);
  cf_WriteShort(outfile, 255);
  cf_WriteShort(outfile, 255);

  // Display adapter dimensions (bash to 256)
  cf_WriteShort(outfile, 256);
  cf_WriteShort(outfile, 256);

  for (int i = 0; i < 48; i++)
    cf_WriteByte(outfile, 0);

  cf_WriteByte(outfile, 0);
  cf_WriteByte(outfile, 1);
  cf_WriteShort(outfile, 256);
  cf_WriteShort(outfile, 2);

  for (i = 0; i < 58; i++)
    cf_WriteByte(outfile, 0);

  for (i = 0; i < TERRAIN_DEPTH; i++) {
    for (int t = 0; t < TERRAIN_WIDTH; t++) {
      uint8_t val = Terrain_seg[(((TERRAIN_DEPTH - 1) - i) * TERRAIN_WIDTH) + t].ypos;
      uint8_t runlen = 0xc1;

      cf_WriteByte(outfile, runlen);
      cf_WriteByte(outfile, val);
    }
  }

  cf_WriteByte(outfile, 12);
  for (i = 0; i < 256; i++) {
    cf_WriteByte(outfile, i);
    cf_WriteByte(outfile, i);
    cf_WriteByte(outfile, i);
  }

  cfclose(outfile);
  OutrageMessageBox("PCX exported!\n");
}

void CTerrainDialog::OnNoExtRoomsObjs() {
  if (IsDlgButtonChecked(IDC_NO_EXT_ROOMS_OBJS)) {
    Terrain_render_ext_room_objs = false;
  } else {
    Terrain_render_ext_room_objs = true;
  }
}

#define FILL_COLOR 1
static uint8_t *Terrain_heights, *Terrain_fill;

#define PUSH_FILL(x)                                                                                                   \
  {                                                                                                                    \
    fill_stack[stack_count] = x;                                                                                       \
    Terrain_fill[x] = 1;                                                                                               \
    stack_count++;                                                                                                     \
    ASSERT(stack_count < 65536);                                                                                       \
  }
#define POP_FILL()                                                                                                     \
  {                                                                                                                    \
    stack_count--;                                                                                                     \
    cell = fill_stack[stack_count];                                                                                    \
  }

void FillTerrainHeights(int cell) {
  terrain_segment *tseg = &Terrain_seg[cell];
  uint16_t fill_stack[65536];
  int stack_count = 0;

  ASSERT(cell >= 0 && cell < TERRAIN_WIDTH * TERRAIN_DEPTH);

  memset(Terrain_fill, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);

  PUSH_FILL(cell);

  while (stack_count > 0) {
    POP_FILL();
    if (Terrain_heights[cell] == 0) {
      int x = cell % 256;
      int z = cell / 256;

      Terrain_heights[cell] = FILL_COLOR;

      if (x != 0 && Terrain_fill[cell - 1] == 0)
        PUSH_FILL(cell - 1);
      if (x != TERRAIN_WIDTH - 1 && Terrain_fill[cell + 1] == 0)
        PUSH_FILL(cell + 1);
      if (z != 0 && Terrain_fill[cell - TERRAIN_WIDTH] == 0)
        PUSH_FILL(cell - TERRAIN_WIDTH);
      if (z != TERRAIN_DEPTH - 1 && Terrain_fill[cell + TERRAIN_WIDTH] == 0)
        PUSH_FILL(cell + TERRAIN_DEPTH);
    }
  }
}

void CTerrainDialog::OnTerrainOcclusion() {
  // TODO: Add your control notification handler code here
  if (Terrain_occlusion_checksum == (Terrain_checksum + 1)) {
    OutrageMessageBox("The occlusion map is already calculated for this terrain.");
    // return;
  }

  if ((MessageBox("Are you sure you wish to calculate terrain occlusion?", "Question", MB_YESNO)) == IDNO)
    return;

  mprintf(0, "Now doing occlusion tests...\n");

  int count = 0;
  int occlude_count = 0;
  uint8_t *touch_buffer[256];

  for (int i = 0; i < 256; i++) {
    memset(Terrain_occlusion_map[i], 0, 32);
    touch_buffer[i] = (uint8_t *)mem_malloc(256);
    ASSERT(touch_buffer[i]);
    memset(touch_buffer[i], 255, 256);
  }

  uint8_t *save_buffer;

  // Build a height map so we can flood fill
  Terrain_heights = (uint8_t *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH);
  Terrain_fill = (uint8_t *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH);
  save_buffer = (uint8_t *)mem_malloc(TERRAIN_WIDTH * TERRAIN_DEPTH);

  ASSERT(Terrain_heights);
  ASSERT(save_buffer);
  ASSERT(Terrain_fill);

  memset(save_buffer, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);
  memset(Terrain_fill, 0, TERRAIN_WIDTH * TERRAIN_DEPTH);

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (Terrain_seg[i].ypos == 255)
      save_buffer[i] = 255;
  }

  for (i = 0; i < OCCLUSION_SIZE; i++) {
    for (int t = 0; t < OCCLUSION_SIZE; t++) {
      int src_occlusion_index = i * OCCLUSION_SIZE + t;
      int start_x = t * OCCLUSION_SIZE;
      int start_z = i * OCCLUSION_SIZE;
      int k, j;
      int dest_x, dest_z;

      for (dest_z = 0; dest_z < OCCLUSION_SIZE; dest_z++) {
        for (dest_x = 0; dest_x < OCCLUSION_SIZE; dest_x++) {
          int end_z = dest_z * OCCLUSION_SIZE;
          int end_x = dest_x * OCCLUSION_SIZE;
          int dest_occlusion_index = dest_z * OCCLUSION_SIZE + dest_x;

          mprintf_at(2, 5, 0, "Count=%7d", count++);

          if (dest_occlusion_index == src_occlusion_index) {
            // This is us!
            int occ_byte = dest_occlusion_index / 8;
            int occ_bit = dest_occlusion_index % 8;

            Terrain_occlusion_map[src_occlusion_index][occ_byte] |= (1 << occ_bit);
            touch_buffer[src_occlusion_index][dest_occlusion_index] = 1;
            continue;
          }

          if (touch_buffer[dest_occlusion_index][src_occlusion_index] != 255) {
            // this one has already been computed
            int hit = touch_buffer[dest_occlusion_index][src_occlusion_index];

            int dest_occ_byte = dest_occlusion_index / 8;
            int dest_occ_bit = dest_occlusion_index % 8;

            if (hit)
              Terrain_occlusion_map[src_occlusion_index][dest_occ_byte] |= (1 << dest_occ_bit);
            else
              Terrain_occlusion_map[src_occlusion_index][dest_occ_byte] &= ~(1 << dest_occ_bit);

            touch_buffer[src_occlusion_index][dest_occlusion_index] = hit;
            continue;
          }

          // See if this ray is close enough
          vector src_vec, dest_vec;

          src_vec.x = start_x;
          src_vec.y = 0;
          src_vec.z = start_z;

          dest_vec.x = end_x;
          dest_vec.y = 0;
          dest_vec.z = end_z;

          // vector subvec=dest_vec-src_vec;

          // Set our heights to max
          memset(Terrain_heights, 255, TERRAIN_WIDTH * TERRAIN_DEPTH);

          // Now carve out a path from the src to the dest
          int x_major = 1;
          if (abs(end_z - start_z) > abs(end_x - start_x))
            x_major = 0;

          // We're iterating over the x axis
          if (x_major) {
            int x_add = 1;
            int limit = end_x - start_x;
            if (limit < 0) {
              x_add = -1;
              limit = -limit;
            }

            int cur_x = start_x;
            float cur_z = start_z;
            float delta_z = (float)(end_z - start_z) / (float)limit;

            for (j = 0; j < limit; j++, cur_x += x_add, cur_z += delta_z) {
              for (int z = 0; z < OCCLUSION_SIZE; z++) {
                for (int x = 0; x < OCCLUSION_SIZE; x++) {
                  int index = (cur_z + z) * TERRAIN_WIDTH;
                  index += (cur_x + x);

                  Terrain_heights[index] = 0;
                }
              }
            }
          } else // iterate over z axis
          {
            int z_add = 1;
            int limit = end_z - start_z;
            if (limit < 0) {
              z_add = -1;
              limit = -limit;
            }

            int cur_z = start_z;
            float cur_x = start_x;
            float delta_x = (float)(end_x - start_x) / (float)limit;

            for (j = 0; j < limit; j++, cur_z += z_add, cur_x += delta_x) {
              for (int z = 0; z < OCCLUSION_SIZE; z++) {
                for (int x = 0; x < OCCLUSION_SIZE; x++) {
                  int index = (cur_z + z) * TERRAIN_WIDTH;
                  index += (cur_x + x);

                  Terrain_heights[index] = 0;
                }
              }
            }
          }

          // Ok, we have a carved path
          // Now put back in all the max values from our original map
          for (k = 0; k < TERRAIN_WIDTH * TERRAIN_DEPTH; k++) {
            if (save_buffer[k] == 255)
              Terrain_heights[k] = 255;
          }

          // Set our src block to zero
          for (k = 0; k < OCCLUSION_SIZE; k++) {
            for (j = 0; j < OCCLUSION_SIZE; j++) {
              Terrain_heights[((start_z + k) * TERRAIN_WIDTH) + start_x + j] = 0;
            }
          }

          // Fill that valley
          FillTerrainHeights((start_z * TERRAIN_WIDTH) + start_x);

          // Check to see if we hit our destination
          int seen = 0;
          for (int z = 0; z < OCCLUSION_SIZE && !seen; z++) {
            for (int x = 0; x < OCCLUSION_SIZE && !seen; x++) {
              int index = (end_z + z) * TERRAIN_WIDTH;
              index += (end_x + x);

              if (Terrain_heights[index] == 1)
                seen = 1;
            }
          }

          touch_buffer[src_occlusion_index][dest_occlusion_index] = seen;
          if (seen) {
            int occ_byte = dest_occlusion_index / 8;
            int occ_bit = dest_occlusion_index % 8;
            Terrain_occlusion_map[src_occlusion_index][occ_byte] |= (1 << occ_bit);
          } else {
            int occ_byte = dest_occlusion_index / 8;
            int occ_bit = dest_occlusion_index % 8;
            Terrain_occlusion_map[src_occlusion_index][occ_byte] &= ~(1 << occ_bit);

            occlude_count++;
          }
        }
      }
    }
  }

  mem_free(Terrain_heights);
  mem_free(Terrain_fill);
  mem_free(save_buffer);

  for (i = 0; i < 256; i++)
    mem_free(touch_buffer[i]);

  Terrain_occlusion_checksum = Terrain_checksum + 1;

  mprintf(0, "%d cells were occluded.\n", occlude_count);
  OutrageMessageBox("Occlusion checking complete. Remember to save!");
}

void CTerrainDialog::OnSatelliteRadio() {
  cc_mode = CC_MODE_SAT;
  UpdateDialog();
}

void CTerrainDialog::OnForceVisible() {
  for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      int c = Terrain_seg[i].flags & TF_INVISIBLE;

      if (c) {
        Terrain_seg[i].flags &= ~TF_INVISIBLE;
        World_changed = 1;
      }
    }
  }

  if (World_changed)
    GenerateLODDeltas();
}

void CTerrainDialog::OnKillfocusDamagePerSecEdit() {
  CEdit *ebox;
  char str[20];
  float err;

  ebox = (CEdit *)GetDlgItem(IDC_DAMAGE_PER_SEC_EDIT);
  ebox->GetWindowText(str, 20);

  err = atof(str);
  if (err < 0)
    err = 0;
  if (err > 200)
    err = 200;

  Terrain_sky.damage_per_second = err;

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnKillfocusFogScalarEdit() {
  CEdit *ebox;
  char str[20];
  float err;

  ebox = (CEdit *)GetDlgItem(IDC_FOG_SCALAR_EDIT);
  ebox->GetWindowText(str, 20);

  err = atof(str);
  if (err < .2)
    err = .2f;
  if (err > 1.0)
    err = 1.0;

  Terrain_sky.fog_scalar = err;

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnRotateStars() {
  int c = IsDlgButtonChecked(IDC_ROTATE_STARS);

  if (c)
    Terrain_sky.flags |= TF_ROTATE_STARS;
  else
    Terrain_sky.flags &= ~TF_ROTATE_STARS;

  TV_changed = 1;
}

void CTerrainDialog::OnRotateSky() {
  int c = IsDlgButtonChecked(IDC_ROTATE_SKY);

  if (c)
    Terrain_sky.flags |= TF_ROTATE_SKY;
  else
    Terrain_sky.flags &= ~TF_ROTATE_SKY;

  TV_changed = 1;
}

void CTerrainDialog::OnKillfocusRotateSpeedEdit() {
  CEdit *ebox;
  char str[20];
  float err;

  ebox = (CEdit *)GetDlgItem(IDC_ROTATE_SPEED_EDIT);
  ebox->GetWindowText(str, 20);

  err = atof(str);
  if (err < 0)
    err = 0;
  if (err > 180)
    err = 180;

  Terrain_sky.rotate_rate = err;

  World_changed = 1;
  UpdateDialog();
}

void CTerrainDialog::OnTileMore() {
  int i;
  uint8_t touched[TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH];
  memset(touched, 0, TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH);

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (!touched[Terrain_seg[i].texseg_index]) {
        int val = Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation >> 4;
        if (val < 8)
          val++;

        val <<= 4;

        Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation &= ~0xF0;
        Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation |= val;
        touched[Terrain_seg[i].texseg_index] = 1;
      }
    }
  }

  World_changed = 1;
  TV_changed = 1;
}

void CTerrainDialog::OnTileLess() {
  int i;
  uint8_t touched[TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH];
  memset(touched, 0, TERRAIN_TEX_WIDTH * TERRAIN_TEX_DEPTH);

  for (i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
    if (TerrainSelected[i]) {
      if (!touched[Terrain_seg[i].texseg_index]) {
        int val = Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation >> 4;
        if (val > 1)
          val--;

        val <<= 4;

        Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation &= ~0xF0;
        Terrain_tex_seg[Terrain_seg[i].texseg_index].rotation |= val;
        touched[Terrain_seg[i].texseg_index] = 1;
      }
    }
  }

  World_changed = 1;
  TV_changed = 1;
}

#include "TerrainSoundDialog.h"

void CTerrainDialog::OnTerrSound() {
  CTerrainSoundDialog dlg;

  dlg.DoModal();
}
