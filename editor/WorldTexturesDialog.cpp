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

 * $Logfile: /DescentIII/Main/editor/WorldTexturesDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:40 $
 * $Author: kevinb $
 *
 * Implementation funcs for textures dialog
 *
 * $Log: not supported by cvs2svn $
 *
 * 61    4/21/99 12:23p Matt
 * Added checkbox for breakable textures
 *
 * 60    4/12/99 3:04p Jason
 * changes for low memory
 *
 * 59    4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 58    4/01/99 5:14p Matt
 * Made ambient sound combo update when the sound is changed, and added a
 * "select" button to bring up the Dallas sound selection dialog.
 *
 * 57    3/10/99 7:12p Jason
 * added smooth specular shading for curved surfaces
 *
 * 56    2/20/99 2:17p Matt
 * Added texture sounds
 *
 * 55    1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 54    1/27/99 3:39p Mark
 * fixed 256 problem
 *
 * 53    1/26/99 4:04p Jason
 * added some more texture flags
 *
 * 52    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 51    12/23/98 4:59p Jason
 * some new texture features added
 *
 * 50    12/18/98 5:25p Jason
 * added specularity to mine walls
 *
 * 49    12/17/98 5:38p Jason
 * added 4444 texture format support
 *
 * 48    11/11/98 12:29p Jason
 * fixed texture panel redrawing
 *
 * 47    11/09/98 11:47a Jason
 * working on multiple checkins
 *
 * 46    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 45    11/05/98 7:54p Jason
 * changes for new manage system
 *
 * 44    10/29/98 6:01p Jason
 * added multiple coronas
 *
 * 43    10/14/98 12:09p Jason
 * fixed some long standing name problems
 *
 * 42    10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 41    10/07/98 5:03p Jason
 * more options for textures
 *
 * 40    8/24/98 5:20p Keneta
 * fixed bug in assigning texture slot to a texture with a previously
 * repeated name.
 *
 * 39    8/13/98 11:57a Jason
 * added water procedurals
 *
 * 38    7/15/98 12:39p Jason
 * fixed bug with new textures
 *
 * 37    7/07/98 4:13p Jason
 * checkin for procedurals
 *
 * 36    7/06/98 12:55p Jason
 * added first pass at procedurals
 *
 * 35    7/01/98 3:09p Luke
 * added assert
 *
 * 34    7/01/98 2:42p Jason
 * fixed bug with unused texture
 *
 * 33    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 32    6/10/98 12:21p Matt
 * Revamped system that controls what textures are displayed on the
 * texture tab.  Should work correctly now, and will now save the settings
 * to the registry.  Also, textures now default to no type set, not all
 * types set.
 *
 * 31    6/03/98 3:46p Jason
 * made megacell system more robust
 *
 * 30    6/02/98 6:04p Jason
 * added specular lightmaps
 *
 * 29    5/26/98 5:08p Matt
 * Don't put a '1' at the end of new texture names unless the name is
 * already in use without the '1'.
 *
 * 28    5/20/98 5:44p Jason
 * incremental checkin for bumpmapping
 *
 * 27    5/19/98 3:19p Jason
 * cleaned up some texture flags
 *
 * 26    4/15/98 3:28p Jason
 * changed glow stuff to work with new system
 *
 * 25    4/15/98 12:22p Jason
 * lots of miscellaneous stuff pertaining to lighting and vis effects
 *
 * 24    4/06/98 4:42p Jason
 * added texture alpha change
 *
 * 23    3/17/98 4:33p Jason
 * Added size changing to bitmaps/textures
 *
 * 22    3/02/98 6:47p Jason
 * added texture lighting swatch
 *
 * 21    2/23/98 1:00p Jason
 * added saving of textures as tgas
 *
 * 20    2/19/98 1:52p Jason
 * added emergency override to unlock function
 *
 * 19    2/10/98 11:20a Jason
 * fixed a couple of strange bugs
 *
 * 18    2/09/98 3:38p Jason
 * changed tex size problem in LoadBitmap function
 *
 * 17    2/03/98 3:15p Jason
 * added the ability to specify saturation textures for models
 *
 * 16    1/13/98 3:09p Jason
 * added glow effect for engines
 *
 * 15    12/02/97 5:31p Samir
 * New file dialog interface implemented.
 *
 * 14    11/21/97 2:01p Jason
 * made light textures on model render that model face fully bright
 *
 * 13    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 12    9/26/97 12:09p Jason
 * tweaked animation on destroyed texture
 *
 * 11    9/25/97 4:30p Jason
 * got destroyable textures working
 *
 * 10    9/25/97 2:58p Jason
 * fixed locker file bug
 *
 * 9     9/09/97 6:08p Matt
 * Changes to texture dialog:
 *   Added done button
 *   Added 'change name' button & removed edit box
 *   Removed pass through checkbox
 *
 * 8     9/03/97 12:19p Jason
 * made deletion ask for lock
 *
 * 7     8/19/97 1:57a Jason
 * made rgb lighting take floats
 *
 * 6     8/12/97 1:10a Jason
 * added code to support radiosity lighting
 *
 * 5     8/08/97 2:25p Matt
 * Took out error messages which are now handled by mng_MakeLocker()
 *
 * 4     8/08/97 12:58p Jason
 * got texture sliding and pingponging working
 *
 * 3     8/05/97 4:28p Chris
 * Added the fly thru and fly back flags
 *
 * 2     8/04/97 3:28p Jason
 * added alpha blending per texture
 *
 * 54    6/24/97 1:15p Jason
 *
 * 53    6/06/97 3:57p Jason
 * implemented changes for small textures and automatic tmap2 recognition
 *
 * 52    6/03/97 5:26p Mark
 *
 * 52	6/03/97	5:17p	Jeff
 *	Added Context Sensitive Help
 * 51    5/30/97 5:46p Jason
 * added colored light functionality on a vertex level
 *
 * 50    5/23/97 7:07p Matt
 * Added code, data, & dialogs to keep track of what a texture is used for
 * (mine, terrain, object) so we can display in the texture dialog only
 * the ones we're interested in.
 *
 * $NoKeywords: $
 */

#include <algorithm>

#include "mfc_compatibility.h"
#include "editor.h"
#include "WorldTexturesDialog.h"
#include "bitmap.h"
#include "gametexture.h"
#include "manage.h"
#include "texpage.h"
#include "pserror.h"
#include "mono.h"
#include "vclip.h"
#include "macros.h"
#include "texture.h"
#include "EditLineDialog.h"
#include "ddio.h"
#include "polymodel.h"
#include "bumpmap.h"
#include "ProceduralDialog.h"
#include "WaterProceduralDialog.h"
#include "mem.h"
#include "ManageCheckin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEXTURES_PER_ROW 12

/////////////////////////////////////////////////////////////////////////////
// CWorldTexturesDialog dialog

CWorldTexturesDialog::CWorldTexturesDialog(CWnd *pParent /*=NULL*/) : CDialog(CWorldTexturesDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWorldTexturesDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

  m_bumpmap = 0;
  m_TexStart = 0;
  m_TexListPos = 0;
  m_RedrawListbox = 0;
  m_TexPageLen = 0;
  m_CheckForTextureList = 0;
  m_CheckX = m_CheckY = 0;
}

void CWorldTexturesDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWorldTexturesDialog)
  DDX_Control(pDX, IDC_TEXTURE_AMBIENT_SOUND_PULLDOWN, m_ambient_sound_combo);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldTexturesDialog, CDialog)
//{{AFX_MSG_MAP(CWorldTexturesDialog)
ON_BN_CLICKED(IDC_WTEXDLG_ADDNEW, OnWtexdlgAddnew)
ON_WM_PAINT()
ON_BN_CLICKED(IDC_NEXT, OnNext)
ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
ON_CBN_SELENDOK(IDC_TEX_LIST, OnSelendokTexList)
ON_BN_CLICKED(IDC_LOCK, OnLock)
ON_BN_CLICKED(IDC_CHECKIN, OnCheckin)
ON_BN_CLICKED(IDC_RCS_STATUS, OnRcsStatus)
ON_BN_CLICKED(IDC_DELETE, OnDelete)
ON_BN_CLICKED(IDC_VOLATILE, OnVolatile)
ON_BN_CLICKED(IDC_WATER, OnWater)
ON_BN_CLICKED(IDC_FORCEFIELD, OnForcefield)
ON_BN_CLICKED(IDC_CHECK_ANIMATE, OnCheckAnimate)
ON_BN_CLICKED(IDC_LOAD_BITMAP, OnLoadBitmap)
ON_BN_CLICKED(IDC_CHECK_DESTROY, OnCheckDestroy)
ON_EN_KILLFOCUS(IDC_REFLECT, OnKillfocusReflect)
ON_EN_KILLFOCUS(IDC_SLIDEU, OnKillfocusSlideu)
ON_EN_KILLFOCUS(IDC_SLIDEV, OnKillfocusSlidev)
ON_EN_KILLFOCUS(IDC_DAMAGE, OnKillfocusDamage)
ON_EN_KILLFOCUS(IDC_TEX_NUM, OnKillfocusTexNum)
ON_WM_TIMER()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_TEXTURE_CURRENT, OnTextureCurrent)
ON_WM_VSCROLL()
ON_BN_CLICKED(IDC_MINE_TEXTURE, OnMineTexture)
ON_BN_CLICKED(IDC_OBJECT_TEXTURE, OnObjectTexture)
ON_BN_CLICKED(IDC_TERRAIN_TEXTURE, OnTerrainTexture)
ON_EN_KILLFOCUS(IDC_BLUE_LIGHTING, OnKillfocusBlueLighting)
ON_EN_KILLFOCUS(IDC_GREEN_LIGHTING, OnKillfocusGreenLighting)
ON_EN_KILLFOCUS(IDC_RED_LIGHTING, OnKillfocusRedLighting)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_ADD_NEW_SMALL, OnAddNewSmall)
ON_BN_CLICKED(IDC_ADD_NEW_TINY, OnAddNewTiny)
ON_EN_KILLFOCUS(IDC_ALPHA_EDIT, OnKillfocusAlphaEdit)
ON_BN_CLICKED(IDC_TEXTURE_FLY_THRU_CHECK, OnTextureFlyThruCheck)
ON_BN_CLICKED(IDC_PING_PONG, OnPingPong)
ON_BN_CLICKED(IDC_TEXTURE_CHANGE_NAME, OnTextureChangeName)
ON_CBN_SELENDOK(IDC_DESTROY_PULLDOWN, OnSelendokDestroyPulldown)
ON_BN_CLICKED(IDC_SATURATE, OnSaturate)
ON_BN_CLICKED(IDC_OVERRIDE, OnOverride)
ON_BN_CLICKED(IDC_SAVE_AS_TGA, OnSaveAsTga)
ON_BN_CLICKED(IDC_CONVERT_TO_NORMAL, OnConvertToNormal)
ON_BN_CLICKED(IDC_CONVERT_TO_SMALL, OnConvertToSmall)
ON_BN_CLICKED(IDC_CONVERT_TO_TINY, OnConvertToTiny)
ON_EN_KILLFOCUS(IDC_SPEED_EDIT, OnKillfocusSpeedEdit)
ON_BN_CLICKED(IDC_IMPORT_BUMP, OnImportBump)
ON_BN_CLICKED(IDC_GENERATE_OMNI, OnGenerateOmni)
ON_BN_CLICKED(IDC_SRC_BUMP, OnSrcBump)
ON_BN_CLICKED(IDC_BUMP1, OnBump1)
ON_BN_CLICKED(IDC_BUMP2, OnBump2)
ON_BN_CLICKED(IDC_BUMP3, OnBump3)
ON_BN_CLICKED(IDC_BUMP4, OnBump4)
ON_BN_CLICKED(IDC_METAL_CHECK, OnMetalCheck)
ON_BN_CLICKED(IDC_MARBLE_CHECK, OnMarbleCheck)
ON_BN_CLICKED(IDC_PLASTIC_CHECK, OnPlasticCheck)
ON_BN_CLICKED(IDC_EFFECT_TEXTURE, OnEffectTexture)
ON_BN_CLICKED(IDC_HUD_COCKPIT_TEXTURE, OnHudCockpitTexture)
ON_BN_CLICKED(IDC_LIGHT_TEXTURE, OnLightTexture)
ON_BN_CLICKED(IDC_PROCEDURAL_CHECK, OnProceduralCheck)
ON_BN_CLICKED(IDC_PROCEDURAL_BUTTON, OnProceduralButton)
ON_BN_CLICKED(IDC_WATER_PROCEDURAL_CHECK, OnWaterProceduralCheck)
ON_BN_CLICKED(IDC_FORCE_LIGHTMAPS, OnForceLightmaps)
ON_BN_CLICKED(IDC_CORONA_A, OnCoronaA)
ON_BN_CLICKED(IDC_CORONA_B, OnCoronaB)
ON_BN_CLICKED(IDC_CORONA_C, OnCoronaC)
ON_BN_CLICKED(IDC_CORONA_D, OnCoronaD)
ON_BN_CLICKED(IDC_MULTICHECKTEX, OnMultichecktex)
ON_BN_CLICKED(IDC_IMPORT_4444, OnImport4444)
ON_BN_CLICKED(IDC_SATURATE_LIGHTMAP, OnSaturateLightmap)
ON_BN_CLICKED(IDC_ADD_NEW_HUGE, OnAddNewHuge)
ON_BN_CLICKED(IDC_LAVA_CHECKBOX, OnLavaCheckbox)
ON_BN_CLICKED(IDC_RUBBLE_CHECKBOX, OnRubbleCheckbox)
ON_CBN_SELENDOK(IDC_TEXTURE_AMBIENT_SOUND_PULLDOWN, OnSelendokTextureAmbientSoundPulldown)
ON_EN_KILLFOCUS(IDC_TEXTURE_AMBIENT_SOUND_VOLUME, OnKillfocusTextureAmbientSoundVolume)
ON_BN_CLICKED(IDC_SMOOTH_SPEC_CHECK, OnSmoothSpecCheck)
ON_BN_CLICKED(IDC_AMBIENT_SOUND_SELECT, OnAmbientSoundSelect)
ON_BN_CLICKED(IDC_CHECK_BREAKABLE, OnCheckBreakable)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldTexturesDialog message handlers

bool InputTextureName(char *buf, int len, char *title, char *prompt, CWnd *wnd);

void CWorldTexturesDialog::OnWtexdlgAddnew() {
  char filename[255], dir[255], fname[128], ext[32];
  char cur_name[100];
  int bm_handle, tex_handle;
  int anim = 0, c;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  int alt_format = IsDlgButtonChecked(IDC_IMPORT_4444);
  int format = 0;

  if (alt_format) {
    int answer = MessageBox("Are you sure you wish to import this texture with a 4444 format?", "Question", MB_YESNO);
    if (answer == IDNO)
      return;

    format = BITMAP_FORMAT_4444;
  }

  CString filter =
      "Descent III files "
      "(*.itl,*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl;*.itl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  if (!strnicmp(ext, "ITL", 3)) {
    LoadITLFile(filename, NORMAL_TEXTURE);
    UpdateDialog();
    return;
  }

  bm_handle = LoadTextureImage(filename, &anim, NORMAL_TEXTURE, 0, 0, format);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  tex_handle = AllocTexture();

  strcpy(cur_name, fname);         // Start with the filename
  char *t = strchr(cur_name, '.'); // Strip the extention
  if (!t)
    t = cur_name + strlen(cur_name);
  *t = 0;
  c = 0;
  do { // Make sure the name not already in use
    if (FindTextureName(cur_name) == -1)
      break;

    *t = 0;
    sprintf(cur_name, "%s%d", cur_name, ++c);
  } while (1);
  cur_name[0] = toupper(cur_name[0]); // make first char uppercase

  // Get the name from the user
  if (!InputTextureName(cur_name, sizeof(cur_name), "Texture name", "Enter a name for your texture:", this)) {
    FreeTexture(tex_handle);
    return;
  }

  strcpy(GameTextures[tex_handle].name, cur_name);

  if (anim)
    GameTextures[tex_handle].flags |= TF_ANIMATED;
  else
    GameTextures[tex_handle].flags &= ~TF_ANIMATED;

  GameTextures[tex_handle].bm_handle = bm_handle;

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[tex_handle].bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameVClips[GameTextures[tex_handle].bm_handle].name);
    SaveVClip(filename, GameTextures[tex_handle].bm_handle);
  }

  CheckIfTextureIsTmap2(tex_handle);

  mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);

  D3EditState.texdlg_texture = tex_handle;

  UpdateDialog();
}

void CWorldTexturesDialog::OnPaint() {
  CPaintDC dc(this); // device context for painting

  // TODO: Add your message handler code here

  // Do not call CDialog::OnPaint() for painting messages
  m_RedrawListbox = 1;
  UpdateDialog();
}

void CWorldTexturesDialog::OnNext() {
  D3EditState.texdlg_texture = GetNextTexture(D3EditState.texdlg_texture);

  UpdateDialog();
}

void CWorldTexturesDialog::OnPrevious() {

  D3EditState.texdlg_texture = GetPreviousTexture(D3EditState.texdlg_texture);

  UpdateDialog();
}

// Redraw the dialog based on our current texture
void CWorldTexturesDialog::UpdateDialog(void) {
  CEdit *ebox;
  CButton *bbox;
  int n = D3EditState.texdlg_texture;
  int last_texture = -1;
  char str[50];
  int i;

  if (GameTextures[n].used == 0) {
    n = 0;
    D3EditState.texdlg_texture = 0;
  }

  ebox = (CEdit *)GetDlgItem(IDC_TEX_NUM);
  sprintf(str, "%d", n);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_BITMAP_NAME);
  if (GameTextures[n].flags & TF_ANIMATED)
    ebox->SetWindowText(GameVClips[GameTextures[n].bm_handle].name);
  else
    ebox->SetWindowText(GameBitmaps[GameTextures[n].bm_handle].name);

  SendDlgItemMessage(IDC_DESTROY_PULLDOWN, CB_RESETCONTENT, 0, 0);
  for (i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      SendDlgItemMessage(IDC_DESTROY_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
  }

  ebox = (CEdit *)GetDlgItem(IDC_DESTROY_PULLDOWN);

  if (GameTextures[n].flags & TF_DESTROYABLE)
    SendDlgItemMessage(IDC_DESTROY_PULLDOWN, CB_SELECTSTRING, 0,
                       (LPARAM)(LPCTSTR)GameTextures[GameTextures[n].destroy_handle].name);
  else
    ebox->SetWindowText("NOT DESTROYABLE");

  ebox = (CEdit *)GetDlgItem(IDC_REFLECT);
  sprintf(str, "%f", GameTextures[n].reflectivity);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_ALPHA_EDIT);
  sprintf(str, "%f", GameTextures[n].alpha);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SPEED_EDIT);
  sprintf(str, "%f", GameTextures[n].speed);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_TEXTURE_WIDTH);
  if (GameTextures[n].flags & TF_ANIMATED)
    sprintf(str, "Width: %d", bm_w(GameVClips[GameTextures[n].bm_handle].frames[0], 0));
  else
    sprintf(str, "Width: %d", bm_w(GameTextures[n].bm_handle, 0));

  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_TEXTURE_HEIGHT);
  if (GameTextures[n].flags & TF_ANIMATED)
    sprintf(str, "Height: %d", bm_h(GameVClips[GameTextures[n].bm_handle].frames[0], 0));
  else
    sprintf(str, "Height: %d", bm_h(GameTextures[n].bm_handle, 0));
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_RED_LIGHTING);
  sprintf(str, "%f", GameTextures[n].r);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_GREEN_LIGHTING);
  sprintf(str, "%f", GameTextures[n].g);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_BLUE_LIGHTING);
  sprintf(str, "%f", GameTextures[n].b);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_DAMAGE);
  itoa(GameTextures[n].damage, str, 10);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SLIDEU);
  sprintf(str, "%f", GameTextures[n].slide_u);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SLIDEV);
  sprintf(str, "%f", GameTextures[n].slide_v);
  ebox->SetWindowText(str);

  // Update combo
  if (n != last_texture)
    m_ambient_sound_combo.SetSelected(GameTextures[n].sound);

  ebox = (CEdit *)GetDlgItem(IDC_TEXTURE_AMBIENT_SOUND_VOLUME);
  sprintf(str, "%.1f", GameTextures[n].sound_volume);
  ebox->SetWindowText(str);

  SendDlgItemMessage(IDC_PALETTIZED_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "Running in 16bit mode");

  SendDlgItemMessage(IDC_TEX_LIST, CB_RESETCONTENT, 0, 0);
  for (i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      SendDlgItemMessage(IDC_TEX_LIST, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[i].name);
  }
  SendDlgItemMessage(IDC_TEX_LIST, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)GameTextures[n].name);

  bbox = (CButton *)GetDlgItem(IDC_CHECKIN);
  if (mng_FindTrackLock(GameTextures[n].name, PAGETYPE_TEXTURE) == -1) {
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK);
    bbox->EnableWindow(TRUE);
  } else {
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK);
    bbox->EnableWindow(FALSE);
  }

  bbox = (CButton *)GetDlgItem(IDC_CHECK_ANIMATE);
  bbox->EnableWindow(FALSE);

  // Prevent some schmo from locking the sample texture
  if (!stricmp(GameTextures[n].name, "SAMPLE TEXTURE")) {
    bbox = (CButton *)GetDlgItem(IDC_LOCK);
    bbox->EnableWindow(FALSE);
  }

  if (GameTextures[n].r > 0 || GameTextures[n].g > 0 || GameTextures[n].b > 0)
    GameTextures[n].flags |= TF_LIGHT;
  else
    GameTextures[n].flags &= ~TF_LIGHT;

  // Do the damn bitmask stuff

  CheckDlgButton(IDC_VOLATILE, GameTextures[n].flags & TF_VOLATILE ? 1 : 0);
  CheckDlgButton(IDC_WATER, GameTextures[n].flags & TF_WATER ? 1 : 0);
  CheckDlgButton(IDC_LAVA_CHECKBOX, GameTextures[n].flags & TF_LAVA ? 1 : 0);
  CheckDlgButton(IDC_RUBBLE_CHECKBOX, GameTextures[n].flags & TF_RUBBLE ? 1 : 0);
  CheckDlgButton(IDC_SMOOTH_SPEC_CHECK, GameTextures[n].flags & TF_SMOOTH_SPECULAR ? 1 : 0);
  CheckDlgButton(IDC_FORCEFIELD, GameTextures[n].flags & TF_FORCEFIELD ? 1 : 0);
  CheckDlgButton(IDC_CHECK_ANIMATE, GameTextures[n].flags & TF_ANIMATED ? 1 : 0);
  CheckDlgButton(IDC_CHECK_TMAP2, GameTextures[n].flags & TF_TMAP2 ? 1 : 0);
  CheckDlgButton(IDC_CHECK_DESTROY, GameTextures[n].flags & TF_DESTROYABLE ? 1 : 0);
  CheckDlgButton(IDC_CHECK_BREAKABLE, GameTextures[n].flags & TF_BREAKABLE ? 1 : 0);
  CheckDlgButton(IDC_4444_CHECK, GameBitmaps[GetTextureBitmap(n, 0)].format == BITMAP_FORMAT_4444 ? 1 : 0);

  // Do coronas
  CheckDlgButton(IDC_CORONA_A, GameTextures[n].corona_type == 0);
  CheckDlgButton(IDC_CORONA_B, GameTextures[n].corona_type == 1);
  CheckDlgButton(IDC_CORONA_C, GameTextures[n].corona_type == 2);
  CheckDlgButton(IDC_CORONA_D, GameTextures[n].corona_type == 3);

  CheckDlgButton(IDC_LIGHT_CHECK, GameTextures[n].flags & TF_LIGHT ? 1 : 0);
  CheckDlgButton(IDC_MINE_TEXTURE, GameTextures[n].flags & TF_MINE ? 1 : 0);
  CheckDlgButton(IDC_TERRAIN_TEXTURE, GameTextures[n].flags & TF_TERRAIN ? 1 : 0);
  CheckDlgButton(IDC_OBJECT_TEXTURE, GameTextures[n].flags & TF_OBJECT ? 1 : 0);
  CheckDlgButton(IDC_EFFECT_TEXTURE, GameTextures[n].flags & TF_EFFECT ? 1 : 0);
  CheckDlgButton(IDC_HUD_COCKPIT_TEXTURE, GameTextures[n].flags & TF_HUD_COCKPIT ? 1 : 0);
  CheckDlgButton(IDC_LIGHT_TEXTURE, GameTextures[n].flags & TF_LIGHT ? 1 : 0);
  CheckDlgButton(IDC_PROCEDURAL_CHECK, GameTextures[n].flags & TF_PROCEDURAL ? 1 : 0);
  CheckDlgButton(IDC_WATER_PROCEDURAL_CHECK, GameTextures[n].flags & TF_WATER_PROCEDURAL ? 1 : 0);
  CheckDlgButton(IDC_FORCE_LIGHTMAPS, GameTextures[n].flags & TF_FORCE_LIGHTMAP ? 1 : 0);
  CheckDlgButton(IDC_SATURATE_LIGHTMAP, GameTextures[n].flags & TF_SATURATE_LIGHTMAP ? 1 : 0);

  CheckDlgButton(IDC_METAL_CHECK, GameTextures[n].flags & TF_METAL ? 1 : 0);
  CheckDlgButton(IDC_MARBLE_CHECK, GameTextures[n].flags & TF_MARBLE ? 1 : 0);
  CheckDlgButton(IDC_PLASTIC_CHECK, GameTextures[n].flags & TF_PLASTIC ? 1 : 0);

  CheckDlgButton(IDC_TEXTURE_FLY_THRU_CHECK, GameTextures[n].flags & TF_FLY_THRU ? 1 : 0);

  CheckDlgButton(IDC_PING_PONG, GameTextures[n].flags & TF_PING_PONG ? 1 : 0);
  CheckDlgButton(IDC_SATURATE, GameTextures[n].flags & TF_SATURATE ? 1 : 0);

  CheckDlgButton(IDC_SRC_BUMP, m_bumpmap == 0 ? 1 : 0);
  CheckDlgButton(IDC_BUMP1, m_bumpmap == 1 ? 1 : 0);
  CheckDlgButton(IDC_BUMP2, m_bumpmap == 2 ? 1 : 0);
  CheckDlgButton(IDC_BUMP3, m_bumpmap == 3 ? 1 : 0);
  CheckDlgButton(IDC_BUMP4, m_bumpmap == 4 ? 1 : 0);

  if (GameTextures[n].flags & TF_ANIMATED)
    CheckDlgButton(IDC_CHECK_MIPPED, 0);
  else {
    if (bm_mipped(GameTextures[n].bm_handle))
      CheckDlgButton(IDC_CHECK_MIPPED, 1);
    else
      CheckDlgButton(IDC_CHECK_MIPPED, 0);
  }

  bbox = (CButton *)GetDlgItem(IDC_PROCEDURAL_BUTTON);
  if (GameTextures[n].flags & TF_PROCEDURAL)
    bbox->EnableWindow(TRUE);
  else
    bbox->EnableWindow(FALSE);

  bbox = (CButton *)GetDlgItem(IDC_WATER_PROCEDURAL_CHECK);
  if (GameTextures[n].flags & TF_PROCEDURAL)
    bbox->EnableWindow(TRUE);
  else
    bbox->EnableWindow(FALSE);

  UpdateTextureViews(1);

  last_texture = n;
}

void CWorldTexturesDialog::UpdateTextureViews(int frame) {
  //	Display texture in IDC_TEXTUREVIEW
  int n = D3EditState.texdlg_texture;
  int freebitmap = 0;

  if (!GameTextures[n].used) {
    n = GetNextTexture(n);
    D3EditState.texdlg_texture = n;
    return;
  }

  CWnd *texwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  static int last_frame = 0;
  static int last_texture = -1;
  static int last_tex_count = -1;
  int update_listbox = 0;

  DrawSwatch(IDC_TEXTURE_SWATCH, GameTextures[n].r, GameTextures[n].g, GameTextures[n].b);

  if (last_texture == n && last_tex_count == Num_textures && m_RedrawListbox == 0)
    update_listbox = 0;
  else {
    m_RedrawListbox = 0;
    update_listbox = 1;
    last_texture = n;
    last_tex_count = Num_textures;
  }

  if (!GameTextures[m_TexStart].used)
    m_TexStart = GetNextTexture(m_TexStart);

  frame = last_frame++;

  texwnd = GetDlgItem(IDC_TEXTUREVIEW);
  texwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  // Desktop_surf->clear(rect.left,rect.top,w,h);

  bm_handle = GetTextureBitmap(n, frame);

  if (GameTextures[n].flags & TF_TEXTURE_256 && bm_w(bm_handle, 0) == 256) {
    // Downsize this bitmap to make it fit on screen
    int temp_bm = bm_AllocBitmap(128, 128, (128 * 128 * 2) / 3);
    GameBitmaps[temp_bm].format = GameBitmaps[bm_handle].format;
    if (GameBitmaps[bm_handle].flags & BF_MIPMAPPED)
      GameBitmaps[temp_bm].flags |= BF_MIPMAPPED;
    bm_ScaleBitmapToBitmap(temp_bm, bm_handle);
    bm_handle = temp_bm;
    freebitmap = 1;
  }

  m_TextureSurf.create(bm_w(bm_handle, 0), bm_h(bm_handle, 0), bm_bpp(bm_handle));
  m_TextureSurf.load(bm_handle);

  x = rect.left + ((rect.right - rect.left) / 2) - m_TextureSurf.width() / 2;
  y = rect.top + ((rect.bottom - rect.top) / 2) - m_TextureSurf.height() / 2;

  Desktop_surf->blt(x, y, &m_TextureSurf);
  m_TextureSurf.free();
  if (freebitmap)
    bm_FreeBitmap(bm_handle);

  //	Display texture in IDC_DESTROYVIEW

  if (GameTextures[n].flags & TF_DESTROYABLE && GameTextures[n].destroy_handle >= 0) {
    CWnd *texwnd;
    RECT rect;
    int x, y, bm_handle;

    texwnd = GetDlgItem(IDC_DESTROYVIEW);
    texwnd->GetWindowRect(&rect);
    ScreenToClient(&rect);

    bm_handle = GetTextureBitmap(GameTextures[n].destroy_handle, frame);
    m_TextureSurf.create(bm_w(bm_handle, 0), bm_h(bm_handle, 0), bm_bpp(bm_handle));
    m_TextureSurf.load(bm_handle);

    x = rect.left + ((rect.right - rect.left) / 2) - m_TextureSurf.width() / 2;
    y = rect.top + ((rect.bottom - rect.top) / 2) - m_TextureSurf.height() / 2;

    Desktop_surf->blt(x, y, &m_TextureSurf);
    m_TextureSurf.free();
  } else {
    CWnd *texwnd;
    RECT rect;

    texwnd = GetDlgItem(IDC_DESTROYVIEW);
    texwnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    w = rect.right - rect.left;
    h = rect.bottom - rect.top;

    Desktop_surf->clear(rect.left, rect.top, w, h);
  }

  /*// Display bumpmaps
  if ((GameTextures[n].src_bumpmap!=-1 && m_bumpmap==0) || (GameTextures[n].bumpmaps[m_bumpmap-1]!=-1))
  {
          CWnd *texwnd;
          RECT rect;
          int x, y, bm_handle;
          uint16_t *src_data,*dest_data;
          int bump_handle;

          if (m_bumpmap==0)
                  bump_handle=GameTextures[n].src_bumpmap;
          else
                  bump_handle=GameTextures[n].bumpmaps[m_bumpmap-1];

          ASSERT (bump_handle>=0);

          texwnd = GetDlgItem(IDC_BUMPVIEW);
          texwnd->GetWindowRect(&rect);
          ScreenToClient(&rect);

          bm_handle=bm_AllocBitmap (BUMP_WIDTH,BUMP_HEIGHT,0);
          ASSERT (bm_handle>=0);

          src_data=(uint16_t *)bump_data(bump_handle);
          dest_data=(uint16_t *)bm_data(bm_handle,0);

          memcpy (dest_data,src_data,BUMP_WIDTH*BUMP_HEIGHT*2);

          bm_ChangeSize (bm_handle,128,128);

          m_TextureSurf.create(bm_w(bm_handle,0), bm_h(bm_handle,0), bm_bpp(bm_handle));
          m_TextureSurf.load(bm_handle);

          x = rect.left + ((rect.right-rect.left)/2) - m_TextureSurf.width()/2;
          y = rect.top + ((rect.bottom-rect.top)/2) - m_TextureSurf.height()/2;

          Desktop_surf->blt(x, y, &m_TextureSurf);
          m_TextureSurf.free();
          bm_FreeBitmap (bm_handle);
  }
  else*/
  {
    CWnd *texwnd;
    RECT rect;

    texwnd = GetDlgItem(IDC_BUMPVIEW);
    texwnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    w = rect.right - rect.left;
    h = rect.bottom - rect.top;

    Desktop_surf->clear(rect.left, rect.top, w, h);
  }

  // Now do that listbox

  if (update_listbox) {
    //	resume updating this damned 'listbox'
    texwnd = GetDlgItem(IDC_TEXTURE_LISTBOX);
    texwnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    w = rect.right - rect.left;
    h = rect.bottom - rect.top;

    Desktop_surf->clear(rect.left, rect.top, w, h);

    int texnum = m_TexStart;
    int count = 0, done = 0;

    while (!done) {
      m_TextureSurf.create(32, 32, BPP_16);

      bm_handle = GetTextureBitmap(texnum, 0);

      if (bm_handle >= 0) {
        m_TextureSurf.load(bm_handle);

        x = 4 + rect.left + ((count % TEXTURES_PER_ROW) * 40);
        y = 4 + rect.top + ((count / TEXTURES_PER_ROW) * 40);

        if (m_CheckForTextureList) {

          if (m_CheckX >= x && m_CheckX <= (x + 40) && m_CheckY >= y && m_CheckY <= (y + 40)) {
            m_CheckForTextureList = 0;
            D3EditState.texdlg_texture = texnum;
            m_TextureSurf.free();
            Desktop_surf->attach_to_window((unsigned)NULL);
            UpdateDialog();
            return;
          }
        }
      }

      if (texnum == n) // draw a white box if this is the current texture
      {
        grViewport *vport = new grViewport(&m_TextureSurf);

        int x = 0, y = 0;

        vport->lock();
        vport->line(GR_RGB(255, 255, 255), x, y, x + vport->width() - 1, y);
        vport->line(GR_RGB(255, 255, 255), x + vport->width() - 1, y, x + vport->width() - 1, y + vport->height() - 1);
        vport->line(GR_RGB(255, 255, 255), x + vport->width() - 1, y + vport->height() - 1, x, y + vport->height() - 1);
        vport->line(GR_RGB(255, 255, 255), x, y + vport->height() - 1, x, y);
        vport->unlock();

        delete vport;
      }

      Desktop_surf->blt(x, y, &m_TextureSurf);

      texnum = GetNextTexture(texnum);
      ASSERT(GameTextures[texnum].used);
      m_TextureSurf.free();
      count++;
      if (count == TEXTURES_PER_ROW * 9)
        done = 1;
      if (texnum <= m_TexStart)
        done = 1;
    }

    //	must define the vertical scroll bar dimensions
    CScrollBar *bar = (CScrollBar *)GetDlgItem(IDC_TEXLIST_VERT);
    SCROLLINFO si;

    m_TexPageLen = (count / TEXTURES_PER_ROW) + ((count % TEXTURES_PER_ROW) ? 1 : 0);
    m_TexListPos = bar->GetScrollPos();
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    si.nMin = 0;
    si.nMax = (Num_textures / TEXTURES_PER_ROW) + ((Num_textures % TEXTURES_PER_ROW) ? 1 : 0) - 1;
    si.nPos = m_TexListPos;
    si.nPage = m_TexPageLen;
    bar->SetScrollInfo(&si);
    bar->ShowScrollBar(TRUE);
  }

  m_CheckForTextureList = 0;
  Desktop_surf->attach_to_window((unsigned)NULL);
}

void CWorldTexturesDialog::OnSelendokTexList() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_TEX_LIST, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_TEX_LIST, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindTextureName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted texture list, but probably nothing.");
    UpdateDialog();
  }

  D3EditState.texdlg_texture = i;
  UpdateDialog();
}

int TlockState = 0;
int AutoChecking = 0;

void CWorldTexturesDialog::OnLock() {
  int n = D3EditState.texdlg_texture;
  mngs_Pagelock temp_pl;
  mngs_texture_page texpage;
  int r;

  if (AutoChecking != 2 && !mng_MakeLocker()) {
    TlockState = 0;
    return;
  }

  strcpy(temp_pl.name, GameTextures[n].name);
  temp_pl.pagetype = PAGETYPE_TEXTURE;

  r = mng_CheckIfPageLocked(&temp_pl);
  if (r == 2) {
    int answer;
    answer = OutrageMessageBox(MBOX_YESNO, "This page is not even in the table file, or the database maybe corrupt.  "
                                           "Override to 'Unlocked'? (Select NO if you don't know what you're doing)");
    if (answer == IDYES) {
      strcpy(temp_pl.holder, "UNLOCKED");
      if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
        MessageBox(ErrorString, "Error!");
        if (AutoChecking != 2)
          mng_EraseLocker();
        return;
      }
    }
  } else if (r < 0) {
    OutrageMessageBox(ErrorString);
    TlockState = 0;

    if (AutoChecking != 2)
      mng_EraseLocker();

    return;

  } else if (r == 1) {
    OutrageMessageBox(InfoString);
    TlockState = 0;

    if (AutoChecking != 2)
      mng_EraseLocker();
    return;

  } else {

    // Everything is ok.  Tell the network we're locking it and get a copy to
    // our local drive

    strcpy(temp_pl.holder, TableUser);
    if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
      MessageBox(ErrorString, "Error!");
      if (AutoChecking != 2)
        mng_EraseLocker();

      TlockState = 0;
      return;
    } else {
      if (mng_FindSpecificTexPage(temp_pl.name, &texpage)) {
        if (mng_AssignTexPageToTexture(&texpage, n)) {
          if (!mng_ReplacePage(GameTextures[n].name, GameTextures[n].name, n, PAGETYPE_TEXTURE, 1)) {
            OutrageMessageBox("There was problem writing that page locally!");

            if (AutoChecking != 2)
              mng_EraseLocker();

            TlockState = 0;
            return;
          }
          if (!AutoChecking)
            OutrageMessageBox("Texture locked.");
        } else
          OutrageMessageBox("There was a problem loading this texture.  You might encounter problems in dealing with "
                            "it.  Good luck!");

        mng_AllocTrackLock(GameTextures[n].name, PAGETYPE_TEXTURE);

        if (AutoChecking != 2)
          UpdateDialog();
        TlockState = 1;
      } else
        OutrageMessageBox("Couldn't find that texture in the table file!");
    }
  }

  if (AutoChecking != 2)
    mng_EraseLocker();
}

void CWorldTexturesDialog::OnCheckin() {
  int n = D3EditState.texdlg_texture;
  mngs_Pagelock temp_pl;
  int r;

  if (!(GameTextures[n].flags & TF_TEXTURE_TYPES)) {
    OutrageMessageBox(
        "You need to select what type of texture this is before checking it in (ie robot, mine, terrain, etc).");
    return;
  }

  if (!mng_MakeLocker())
    return;

  strcpy(temp_pl.name, GameTextures[n].name);
  temp_pl.pagetype = PAGETYPE_TEXTURE;

  r = mng_CheckIfPageOwned(&temp_pl, TableUser);
  if (r < 0)
    OutrageMessageBox(ErrorString);
  else if (r == 0)
    OutrageMessageBox(InfoString);
  else {
    strcpy(temp_pl.holder, "UNLOCKED");
    if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
      OutrageMessageBox(ErrorString, "Error!");
      mng_EraseLocker();
      return;
    } else {
      if (!mng_ReplacePage(GameTextures[n].name, GameTextures[n].name, n, PAGETYPE_TEXTURE, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this textures bitmap to the network for all

        std::filesystem::path fname;

        if (GameTextures[n].flags & TF_ANIMATED) {
          fname = ManageGraphicsDir / GameVClips[GameTextures[n].bm_handle].name;
          SaveVClip(fname, GameTextures[n].bm_handle);

          fname = LocalManageGraphicsDir / GameVClips[GameTextures[n].bm_handle].name;
          SaveVClip(fname, GameTextures[n].bm_handle);
        } else {
          fname = ManageGraphicsDir / GameBitmaps[GameTextures[n].bm_handle].name;
          bm_SaveFileBitmap(fname, GameTextures[n].bm_handle);

          fname = LocalManageGraphicsDir / GameBitmaps[GameTextures[n].bm_handle].name;
          bm_SaveFileBitmap(fname, GameTextures[n].bm_handle);
        }

        if (!AutoChecking)
          OutrageMessageBox("Texture checked in.");
        int dret = mng_DeletePage(GameTextures[n].name, PAGETYPE_TEXTURE, 1);
        ASSERT(dret == 1);
        mng_EraseLocker();

        int p = mng_FindTrackLock(GameTextures[n].name, PAGETYPE_TEXTURE);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }
  mng_EraseLocker();
}

void CWorldTexturesDialog::OnRcsStatus() {
  char str[10000];
  int total = 0;

  mng_DisplayLockList(TableUser);

  sprintf(str, "User %s has these textures held locally:\n\n", TableUser);
  for (int i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_TEXTURE) {
      char temp[90];

      sprintf(temp, "%s", GlobalTrackLocks[i].name);
      strcat(str, temp);
      strcat(str, "\n");
      total++;
    }
  }

  if (total != 0) {
    // Display that string
    MessageBox(str, "Textures", MB_OK);
  }
}

void CWorldTexturesDialog::SaveTexturesOnClose() {
  int i, t;

  // When closing, save all our textures locally

  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_TEXTURE) {
      t = FindTextureName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);

      mng_ReplacePage(GameTextures[t].name, GameTextures[t].name, t, PAGETYPE_TEXTURE, 1);

      std::filesystem::path fname;

      if (GameTextures[t].flags & TF_ANIMATED) {
        fname = LocalManageGraphicsDir / GameVClips[GameTextures[t].bm_handle].name;
        SaveVClip(fname, GameTextures[t].bm_handle);
      } else {
        fname = LocalManageGraphicsDir / GameBitmaps[GameTextures[t].bm_handle].name;
        bm_SaveFileBitmap(fname, GameTextures[t].bm_handle);
      }
    }
  }
}

BOOL CWorldTexturesDialog::DestroyWindow() {

  CWnd::KillTimer(1);
  SaveTexturesOnClose();

  return CDialog::DestroyWindow();
}

void CWorldTexturesDialog::OnDelete() {
  int answer, tl;
  mngs_Pagelock pl;
  int n = D3EditState.texdlg_texture;

  if ((tl = mng_FindTrackLock(GameTextures[n].name, PAGETYPE_TEXTURE)) == -1) {
    // OutrageMessageBox ("This texture is not yours to delete.  Lock first.");
    answer = MessageBox("This texture is not locked...do you wish to lock it so you can delete it?",
                        GameTextures[n].name, MB_YESNO);
    if (answer == IDNO)
      return;

    AutoChecking = 1;
    TlockState = 0;

    OnLock();
    if (!TlockState) {
      OutrageMessageBox("Couldn't lock that texture to delete it!");
      AutoChecking = 0;
      return;
    }
    AutoChecking = 0;
    tl = mng_FindTrackLock(GameTextures[n].name, PAGETYPE_TEXTURE);
    ASSERT(tl != -1);

    // return;
  }
  answer = MessageBox("Are you sure you want to delete this texture?", GameTextures[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (!mng_MakeLocker())
    return;

  strncpy(pl.name, GameTextures[n].name, 30);
  pl.pagetype = PAGETYPE_TEXTURE;
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(GameTextures[n].name, PAGETYPE_TEXTURE, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else {
    mng_FreeTrackLock(tl);
    mng_DeletePage(GameTextures[n].name, PAGETYPE_TEXTURE, 0);
    mng_DeletePage(GameTextures[n].name, PAGETYPE_TEXTURE, 1);

    mng_DeletePagelock(GameTextures[n].name, PAGETYPE_TEXTURE);
  }

  if (GameTextures[n].flags & TF_ANIMATED)
    FreeVClip(GameTextures[n].bm_handle);
  else
    bm_FreeBitmap(GameTextures[n].bm_handle);

  FreeTexture(n);
  mng_EraseLocker();

  MessageBox("Texture deleted.");
  D3EditState.texdlg_texture = GetNextTexture(n);
  if (D3EditState.texdlg_texture == n)
    mprintf(0, "Wrapped!\n");

  UpdateDialog();
}

// The following functions harvest the checkbuttons

void CWorldTexturesDialog::OnVolatile() {
  int c = IsDlgButtonChecked(IDC_VOLATILE);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_VOLATILE;
  else
    GameTextures[n].flags &= ~TF_VOLATILE;
}

void CWorldTexturesDialog::OnWater() {
  int c = IsDlgButtonChecked(IDC_WATER);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_WATER;
  else
    GameTextures[n].flags &= ~TF_WATER;
}

void CWorldTexturesDialog::OnForcefield() {
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_FORCEFIELD);

  if (c)
    GameTextures[n].flags |= TF_FORCEFIELD;
  else
    GameTextures[n].flags &= ~TF_FORCEFIELD;
}

void CWorldTexturesDialog::OnCheckAnimate() {
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_CHECK_ANIMATE);

  if (c)
    GameTextures[n].flags |= TF_ANIMATED;
  else
    GameTextures[n].flags &= ~TF_ANIMATED;
}

void CWorldTexturesDialog::OnLoadBitmap() {
  char filename[255];
  int bm_handle;
  int anim = 0;
  int n = D3EditState.texdlg_texture;
  int tex_size = NORMAL_TEXTURE;

  CString filter =
      "Descent III files (*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  if (GameTextures[n].flags & TF_TEXTURE_64)
    tex_size = SMALL_TEXTURE;
  else if (GameTextures[n].flags & TF_TEXTURE_32)
    tex_size = TINY_TEXTURE;
  else if (GameTextures[n].flags & TF_TEXTURE_256)
    tex_size = HUGE_TEXTURE;

  int format = GameBitmaps[GetTextureBitmap(n, 0)].format;

  bm_handle = LoadTextureImage(filename, &anim, tex_size, 0, 0, format);

  if (bm_handle < 0) {
    OutrageMessageBox("Could not load that bitmap...restoring previous bitmap.");
    return;
  }

  GameTextures[n].bm_handle = bm_handle;

  if (anim)
    GameTextures[n].flags |= TF_ANIMATED;
  else
    GameTextures[n].flags &= ~TF_ANIMATED;

  mprintf(0, "Making a copy of this bitmap locally...\n");

  if (anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameVClips[GameTextures[n].bm_handle].name);
    SaveVClip(filename, GameTextures[n].bm_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[n].bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[n].bm_handle);
  }

  CheckIfTextureIsTmap2(n);
  UpdateDialog();
}

void CWorldTexturesDialog::OnCheckDestroy() {
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_CHECK_DESTROY);

  if (c) {
    GameTextures[n].flags |= TF_DESTROYABLE;
    GameTextures[n].destroy_handle = n;
  } else
    GameTextures[n].flags &= ~TF_DESTROYABLE;

  UpdateDialog();
}

void CWorldTexturesDialog::OnKillfocusReflect() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_REFLECT);
  ebox->GetWindowText(name, 20);

  GameTextures[n].reflectivity = atof(name);

  if (GameTextures[n].reflectivity > 1)
    GameTextures[n].reflectivity = 1.0f;
  if (GameTextures[n].reflectivity < 0)
    GameTextures[n].reflectivity = 0.0f;
}

void CWorldTexturesDialog::OnKillfocusSlideu() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_SLIDEU);
  ebox->GetWindowText(name, 20);

  GameTextures[n].slide_u = atof(name);
}

void CWorldTexturesDialog::OnKillfocusSlidev() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_SLIDEV);
  ebox->GetWindowText(name, 20);

  GameTextures[n].slide_v = atof(name);
}

void CWorldTexturesDialog::OnKillfocusDamage() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_DAMAGE);
  ebox->GetWindowText(name, 20);

  GameTextures[n].damage = atoi(name);
}

void CWorldTexturesDialog::OnKillfocusTexNum() {
  CEdit *ebox;
  char name[20];
  int n;

  ebox = (CEdit *)GetDlgItem(IDC_TEX_NUM);
  ebox->GetWindowText(name, 20);

  n = atoi(name);

  if (!GameTextures[n].used) {
    int a = MessageBox("That is not a valid texture number...show anyway? (may cause a crash)", "WARNING", MB_YESNO);
    if (a == IDNO) {
      char str[30];
      sprintf(str, "%d", D3EditState.texdlg_texture);
      ebox->SetWindowText(str);
      return;
    }
  }

  D3EditState.texdlg_texture = n;
  UpdateDialog();
}

BOOL CWorldTexturesDialog::OnInitDialog() {
  CDialog::OnInitDialog();
  CWnd::SetTimer(1, 100, NULL);

  int n = D3EditState.texdlg_texture;
  m_ambient_sound_combo.Init(GameTextures[n].sound);

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorldTexturesDialog::OnTimer(UINT nIDEvent) {

  int n = D3EditState.texdlg_texture;

  if (GameTextures[n].flags & TF_ANIMATED ||
      ((GameTextures[n].flags & TF_DESTROYABLE) && (GameTextures[GameTextures[n].destroy_handle].flags & TF_ANIMATED)))
    UpdateTextureViews(1);

  CDialog::OnTimer(nIDEvent);
}

void CWorldTexturesDialog::OnLButtonDown(UINT nFlags, CPoint point) {
  // TODO: Add your message handler code here and/or call default

  m_CheckForTextureList = 1;
  m_CheckX = point.x;
  m_CheckY = point.y;

  CDialog::OnLButtonDown(nFlags, point);

  m_RedrawListbox = 1;
  UpdateDialog();
}

void CWorldTexturesDialog::TextureListUp(int rows) {
  int old = m_TexStart;
  int done = 0, count = 0;

  while ((count < (TEXTURES_PER_ROW * rows)) && !done) {

    m_TexStart = GetPreviousTexture(m_TexStart);

    if (old <= m_TexStart) {
      m_TexStart = old;
      done = 1;
    } else
      count++;
  }

  m_RedrawListbox = 1;
  UpdateDialog();
}

void CWorldTexturesDialog::TextureListDown(int rows) {
  int old = m_TexStart;
  int done = 0, count = 0;

  while ((count < (TEXTURES_PER_ROW * rows)) && !done) {
    m_TexStart = GetNextTexture(m_TexStart);
    if (old >= m_TexStart) {
      m_TexStart = old;
      done = 1;
    } else
      count++;
  }

  m_RedrawListbox = 1;
  UpdateDialog();
}

void CWorldTexturesDialog::OnTextureCurrent() {

  // m_TexStart=D3EditState.texdlg_texture/TEXTURES_PER_ROW;
  // m_RedrawListbox=1;

  // UpdateDialog();
}

void CWorldTexturesDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  // TODO: Add your message handler code here and/or call default
  //	pScrollBar is one of the scroll bars in the dialog.  to determine which one, get
  //	its id. (Note that for a window's scrollbar, this object is invalid)
  int id = -1, min, max;
  int new_pos = 0;

  if (pScrollBar) {
    id = pScrollBar->GetDlgCtrlID();
    pScrollBar->GetScrollRange(&min, &max);
  }

  switch (id) {
  case IDC_TEXLIST_VERT:
    //	vertically scroll the texture list box
    switch (nSBCode) {
    case SB_LINEDOWN:
      new_pos = m_TexListPos + 1;
      break;
    case SB_LINEUP:
      new_pos = m_TexListPos - 1;
      break;
    case SB_THUMBPOSITION:
      new_pos = nPos;
      break;
    case SB_THUMBTRACK:
      new_pos = nPos;
      break;
    case SB_PAGEDOWN:
      new_pos = m_TexListPos + m_TexPageLen;
      break;
    case SB_PAGEUP:
      new_pos = m_TexListPos - m_TexPageLen;
      break;
    default:
      new_pos = m_TexListPos;
    }

    if (new_pos < 0)
      new_pos = 0;
    if (new_pos > (max - m_TexPageLen))
      new_pos = (max - m_TexPageLen) + 1;
    if (new_pos != m_TexListPos) {
      //	ok, new_pos will be an index into the listbox, NOT the texture list.
      //	so we will get the number of texture rows we went up or down and change
      //	tex_start accordingly.
      mprintf(0, "scroll new_pos = %d.  original_pos = %d\n", new_pos, m_TexListPos);
      if (new_pos < m_TexListPos)
        TextureListUp(abs(m_TexListPos - new_pos));
      if (new_pos > m_TexListPos)
        TextureListDown(abs(new_pos - m_TexListPos));

      m_TexListPos = new_pos;

      SCROLLINFO si;

      si.cbSize = sizeof(si);
      si.fMask = SIF_POS;
      si.nPos = m_TexListPos;
      pScrollBar->SetScrollInfo(&si);
    }
    break;

  default:
    Int3(); // WHAT THE FUCK!!
  }

  CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

// Opens a ITL text file and individually adds each on of those bitmaps as a texture
int CWorldTexturesDialog::LoadITLFile(char *filename, int type) {
  CFILE *infile;
  char name[PAGENAME_LEN];
  uint32_t i, done = 0, total = 0;
  char cur_name[100];
  int tex_handle, tex_list[200];
  int c = 1, finding_name = 1;

  ASSERT(filename != NULL);

  infile = (CFILE *)cfopen(filename, "rt");
  if (!infile) {
    mprintf(0, "Couldn't load ITL file %s!\n", filename);
    return -1;
  }

  mprintf(0, "Loading ITL file %s\n", name);

  while (!done) {
    char curline[200];
    char texname[200];

    if (cfeof(infile)) {
      done = 1;
      continue;
    }

    // Read a line and parse it
    cf_ReadString(curline, 200, infile);

    if (curline[0] == ';' || curline[1] == ';' || curline[0] == ' ' || curline[1] == ' ' || curline[0] == '\n')
      continue;
    else {
      int lastslash = -1;
      char bmname[200];

      strcpy(texname, curline);

      for (i = 0; i < strlen(curline); i++)
        if (curline[i] == '\\')
          lastslash = i;

      if (lastslash == -1) {
        for (i = 0; i < strlen(filename); i++)
          if (filename[i] == '\\')
            lastslash = i;

        ASSERT(lastslash != -1);

        strcpy(bmname, filename);
        bmname[lastslash + 1] = 0;
        strcat(bmname, curline);
      } else
        strcpy(bmname, curline);

      // Try and load this file

      int bm = LoadTextureImage(bmname, 0, type, 0);
      if (bm <= 0) {
        mprintf(0, "Error loading frame %d of ITL file %s!\n", total, filename);
        goto Here;
      }

      tex_handle = AllocTexture();
      GameTextures[tex_handle].bm_handle = bm;

      finding_name = 1;
      c = 1;

      while (finding_name) {
        if (c == 1)
          sprintf(cur_name, "%s", texname);
        else
          sprintf(cur_name, "%s%d", texname, c);

        if (FindTextureName(cur_name) != -1)
          c++;
        else
          finding_name = 0;
      }

      strcpy(GameTextures[tex_handle].name, cur_name);

      GameTextures[tex_handle].flags &= ~TF_ANIMATED;

      if (type == SMALL_TEXTURE)
        GameTextures[tex_handle].flags |= TF_TEXTURE_64;
      else if (type == TINY_TEXTURE)
        GameTextures[tex_handle].flags |= TF_TEXTURE_32;
      else if (type == HUGE_TEXTURE)
        GameTextures[tex_handle].flags |= TF_TEXTURE_256;

      GameTextures[tex_handle].bm_handle = bm;
      mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);

      tex_list[total] = tex_handle;

      total++;
    }
  }

Here:

  cfclose(infile);

  mprintf(0, "Making a copy of these textures locally...\n");

  for (i = 0; i < total; i++) {
    tex_handle = tex_list[i];

    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[tex_handle].bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);
  }

  return 1;
}

void CWorldTexturesDialog::OnMineTexture() {
  int c = IsDlgButtonChecked(IDC_MINE_TEXTURE);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_MINE;
  else
    GameTextures[n].flags &= ~TF_MINE;
}

void CWorldTexturesDialog::OnObjectTexture() {
  int c = IsDlgButtonChecked(IDC_OBJECT_TEXTURE);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_OBJECT;
  else
    GameTextures[n].flags &= ~TF_OBJECT;
}

void CWorldTexturesDialog::OnTerrainTexture() {
  int c = IsDlgButtonChecked(IDC_TERRAIN_TEXTURE);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_TERRAIN;
  else
    GameTextures[n].flags &= ~TF_TERRAIN;
}

void CWorldTexturesDialog::OnKillfocusBlueLighting() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_BLUE_LIGHTING);
  ebox->GetWindowText(name, 20);

  GameTextures[n].b = atof(name);
  UpdateDialog();
}

void CWorldTexturesDialog::OnKillfocusGreenLighting() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_GREEN_LIGHTING);
  ebox->GetWindowText(name, 20);

  GameTextures[n].g = atof(name);
  UpdateDialog();
}

void CWorldTexturesDialog::OnKillfocusRedLighting() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_RED_LIGHTING);
  ebox->GetWindowText(name, 20);

  GameTextures[n].r = atof(name);
  UpdateDialog();
}

BOOL CWorldTexturesDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  WinHelp(HID_TEXTURESDLG, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CWorldTexturesDialog::OnAddNewSmall() {
  char filename[255], dir[255], fname[128], ext[32];
  char cur_name[100];
  int bm_handle, tex_handle;
  int c = 1, finding_name = 1;
  int anim = 0;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  int alt_format = IsDlgButtonChecked(IDC_IMPORT_4444);
  int format = 0;

  if (alt_format) {
    int answer = MessageBox("Are you sure you wish to import this texture with a 4444 format?", "Question", MB_YESNO);
    if (answer == IDNO)
      return;

    format = BITMAP_FORMAT_4444;
  }

  CString filter =
      "Descent III files "
      "(*.itl,*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl;*.itl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  if (!strnicmp(ext, "ITL", 3)) {
    LoadITLFile(filename, SMALL_TEXTURE);
    UpdateDialog();
    return;
  }

  bm_handle = LoadTextureImage(filename, &anim, SMALL_TEXTURE, 0, 0, format);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  tex_handle = AllocTexture();

  while (finding_name) {
    if (c == 1)
      sprintf(cur_name, "%s", fname);
    else
      sprintf(cur_name, "%s%d", fname, c);

    if (FindTextureName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(GameTextures[tex_handle].name, cur_name);

  if (anim)
    GameTextures[tex_handle].flags |= TF_ANIMATED;
  else
    GameTextures[tex_handle].flags &= ~TF_ANIMATED;

  GameTextures[tex_handle].flags |= TF_TEXTURE_64;

  GameTextures[tex_handle].bm_handle = bm_handle;

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[tex_handle].bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameVClips[GameTextures[tex_handle].bm_handle].name);
    SaveVClip(filename, GameTextures[tex_handle].bm_handle);
  }

  CheckIfTextureIsTmap2(tex_handle);

  mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);

  D3EditState.texdlg_texture = tex_handle;

  UpdateDialog();
}

void CWorldTexturesDialog::OnAddNewTiny() {
  char filename[255], dir[255], fname[128], ext[32];
  char cur_name[100];
  int bm_handle, tex_handle;
  int c = 1, finding_name = 1;
  int anim = 0;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  int alt_format = IsDlgButtonChecked(IDC_IMPORT_4444);
  int format = 0;

  if (alt_format) {
    int answer = MessageBox("Are you sure you wish to import this texture with a 4444 format?", "Question", MB_YESNO);
    if (answer == IDNO)
      return;

    format = BITMAP_FORMAT_4444;
  }

  CString filter =
      "Descent III files "
      "(*.itl,*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl;*.itl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  if (!strnicmp(ext, "ITL", 3)) {
    LoadITLFile(filename, TINY_TEXTURE);
    UpdateDialog();
    return;
  }

  bm_handle = LoadTextureImage(filename, &anim, TINY_TEXTURE, 0, 0, format);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  tex_handle = AllocTexture();

  while (finding_name) {
    if (c == 1)
      sprintf(cur_name, "%s", fname);
    else
      sprintf(cur_name, "%s%d", fname, c);
    if (FindTextureName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(GameTextures[tex_handle].name, cur_name);

  if (anim)
    GameTextures[tex_handle].flags |= TF_ANIMATED;
  else
    GameTextures[tex_handle].flags &= ~TF_ANIMATED;

  GameTextures[tex_handle].flags |= TF_TEXTURE_32;

  GameTextures[tex_handle].bm_handle = bm_handle;

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[tex_handle].bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameVClips[GameTextures[tex_handle].bm_handle].name);
    SaveVClip(filename, GameTextures[tex_handle].bm_handle);
  }

  CheckIfTextureIsTmap2(tex_handle);

  mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);

  D3EditState.texdlg_texture = tex_handle;

  UpdateDialog();
}

void CWorldTexturesDialog::OnKillfocusAlphaEdit() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_ALPHA_EDIT);
  ebox->GetWindowText(name, 20);

  GameTextures[n].alpha = atof(name);

  if (GameTextures[n].alpha < .9999)
    GameTextures[n].flags |= TF_ALPHA;
  else
    GameTextures[n].flags &= ~TF_ALPHA;

  UpdateDialog();
}

void CWorldTexturesDialog::OnTextureFlyThruCheck() {
  // TODO: Add your control notification handler code here
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_TEXTURE_FLY_THRU_CHECK);

  if (c)
    GameTextures[n].flags |= TF_FLY_THRU;
  else
    GameTextures[n].flags &= ~TF_FLY_THRU;
}

void CWorldTexturesDialog::OnPingPong() {
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_PING_PONG);

  if (c)
    GameTextures[n].flags |= TF_PING_PONG;
  else
    GameTextures[n].flags &= ~TF_PING_PONG;
}

// Gets a name from the user, making sure it's unique
// Returns true if got new name, false if cancelled.
// the data in buf not changed if cancel is pressed
bool InputTextureName(char *buf, int len, char *title, char *prompt, CWnd *wnd) {
  char *tempbuf = (char *)mem_malloc(len);

  strcpy(tempbuf, buf);

try_again:

  if (!InputString(tempbuf, len, title, prompt, wnd)) {
    mem_free(tempbuf);
    return 0;
  }

  if (FindTextureName(tempbuf) != -1) {
    OutrageMessageBox("The name you specified is already in use.  Enter another name.");
    goto try_again;
  }

  strcpy(buf, tempbuf);
  mem_free(tempbuf);

  return 1;
}

void CWorldTexturesDialog::OnTextureChangeName() {
  int n = D3EditState.texdlg_texture;
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this texture locked, if not reset name and bail
  int p = mng_FindTrackLock(GameTextures[n].name, PAGETYPE_TEXTURE);
  if (p == -1) {
    OutrageMessageBox("You must lock this texture if you wish to change its name.");
    return;
  }

  // Get new name
  strcpy(name, GameTextures[n].name);
  if (!InputTextureName(name, sizeof(name), "Texture name", "Enter a new name for this texture:", this))
    return;

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, GameTextures[n].name);
  pl.pagetype = PAGETYPE_TEXTURE;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(GameTextures[n].name, name, PAGETYPE_TEXTURE);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, GameTextures[n].name);
    strcpy(GameTextures[n].name, name);
    mng_ReplacePage(oldname, GameTextures[n].name, n, PAGETYPE_TEXTURE, 1);

  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(GameTextures[n].name, name);
  UpdateDialog();
  mng_EraseLocker();
}

void CWorldTexturesDialog::OnSelendokDestroyPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_DESTROY_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_DESTROY_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindTextureName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted texture list, but probably nothing.");
    UpdateDialog();
  }

  GameTextures[D3EditState.texdlg_texture].destroy_handle = i;
  UpdateDialog();
}

void CWorldTexturesDialog::OnSaturate() {
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_SATURATE);

  if (c)
    GameTextures[n].flags |= TF_SATURATE;
  else
    GameTextures[n].flags &= ~TF_SATURATE;
}

void CWorldTexturesDialog::OnOverride() {
  int n = D3EditState.texdlg_texture;
  mngs_Pagelock temp_pl;

  strcpy(temp_pl.name, GameTextures[n].name);
  temp_pl.pagetype = PAGETYPE_TEXTURE;

  mng_OverrideToUnlocked(&temp_pl);
}

void CWorldTexturesDialog::OnSaveAsTga() {
  int n = D3EditState.texdlg_texture;

  if (GameTextures[n].flags & TF_ANIMATED) {
    OutrageMessageBox("You cannot save an animated texture!");
    return;
  }

  CString filter = "TGA files (*.tga)|*.tga||";
  char filename[255];
  if (!SaveFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  if (!strchr(filename, '.'))
    strcat(filename, ".tga");

  // FIXME: Save as PNG
  // bm_SaveBitmapTGA (filename,GameTextures[n].bm_handle);
  OutrageMessageBox("TGA saved!");
}

void CWorldTexturesDialog::DrawSwatch(int handle, float r, float g, float b) {
  CWnd *texwnd;
  RECT rect;
  int w, h;
  float rmax = std::max(r, g);
  rmax = std::max(rmax, b);

  if (rmax >= .001) {
    r /= rmax;
    g /= rmax;
    b /= rmax;
  }

  texwnd = GetDlgItem(handle);
  texwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  ddgr_color color = GR_RGB(r * 255, g * 255, b * 255);

  Desktop_surf->clear(rect.left, rect.top, w, h, color);

  Desktop_surf->attach_to_window(NULL);
}

void CWorldTexturesDialog::ChangeSize(int w, int h) {
  int n = D3EditState.texdlg_texture;
  char str[255];

  sprintf(str, "Are you sure you wish to change this texture to %d x %d?", w, h);

  int answer = MessageBox(str, GameTextures[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (GameTextures[n].flags & TF_ANIMATED) {
    vclip *vc = &GameVClips[GameTextures[n].bm_handle];
    for (int i = 0; i < vc->num_frames; i++)
      bm_ChangeSize(vc->frames[i], w, h);
  } else {
    bm_ChangeSize(GameTextures[n].bm_handle, w, h);
  }

  GameTextures[n].flags &= ~(TF_TEXTURE_32 | TF_TEXTURE_64 | TF_TEXTURE_256);
  if (w == 64)
    GameTextures[n].flags |= TF_TEXTURE_64;
  else if (w == 32)
    GameTextures[n].flags |= TF_TEXTURE_32;

  mprintf(0, "Texture changed to %d x %d!\n", w, h);

  UpdateDialog();
}

void CWorldTexturesDialog::OnConvertToNormal() { ChangeSize(128, 128); }

void CWorldTexturesDialog::OnConvertToSmall() { ChangeSize(64, 64); }

void CWorldTexturesDialog::OnConvertToTiny() { ChangeSize(32, 32); }

void CWorldTexturesDialog::OnKillfocusSpeedEdit() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.texdlg_texture;

  ebox = (CEdit *)GetDlgItem(IDC_SPEED_EDIT);
  ebox->GetWindowText(name, 20);

  GameTextures[n].speed = atof(name);
  UpdateDialog();
}

void CWorldTexturesDialog::OnImportBump() {
  /*char filename[255];
  int bm_handle;
  int n=D3EditState.texdlg_texture;


  CString filter = "Descent III files (*.tga,*.ogf,*.pcx)|*.pcx;*.tga;*.ogf;||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
          return;

  bm_handle=bm_AllocLoadFileBitmap (filename,0);

  if (bm_handle<0)
  {
          OutrageMessageBox ("Could not load that bumpmap!");
          return;
  }

  if (bm_w(bm_handle,0)!=BUMP_WIDTH || bm_h(bm_handle,0)!=BUMP_HEIGHT)
  {
          OutrageMessageBox ("Bumpmaps must be 32x32 in size!");
          return;
  }

  if (GameTextures[n].bumpmap!=-1)
  {
          bump_FreeBumpmap (GameTextures[n].bumpmap);
          GameTextures[n].src_bumpmap=-1;
  }

  int src_bump=bump_AllocBumpmap ();
  ASSERT (src_bump>=0);

  // Do the memcopy from the bitmap to the bumpmap
  uint16_t *src_data,*dest_data;
  src_data=(uint16_t *)bm_data(bm_handle,0);
  dest_data=(uint16_t *)bump_data(src_bump);

  memcpy (dest_data,src_data,BUMP_WIDTH*BUMP_HEIGHT*2);

  GameTextures[n].src_bumpmap=src_bump;

  mprintf(0,"Making a copy of this bumpmap locally...\n");

  sprintf (filename,"%s\\%s",LocalManageGraphicsDir,GameBitmaps[bm_handle].name);
  bm_SaveFileBitmap (filename,bm_handle);

  // Free useless bitmap
  bm_FreeBitmap(bm_handle);

  UpdateDialog ();*/
}

void CWorldTexturesDialog::OnGenerateOmni() {
  int n = D3EditState.texdlg_texture;

  if (GameTextures[n].bumpmap == -1) {
    OutrageMessageBox("You first need to import a source bumpmap!");
    return;
  }

  BuildTextureBumpmaps(n);

  OutrageMessageBox("Bumpmaps built!");
}

void CWorldTexturesDialog::OnSrcBump() {
  m_bumpmap = 0;
  UpdateDialog();
}

void CWorldTexturesDialog::OnBump1() {
  m_bumpmap = 1;
  UpdateDialog();
}

void CWorldTexturesDialog::OnBump2() {
  m_bumpmap = 2;
  UpdateDialog();
}

void CWorldTexturesDialog::OnBump3() {
  m_bumpmap = 3;
  UpdateDialog();
}

void CWorldTexturesDialog::OnBump4() {
  m_bumpmap = 4;
  UpdateDialog();
}

void CWorldTexturesDialog::OnMetalCheck() {
  int c = IsDlgButtonChecked(IDC_METAL_CHECK);
  int n = D3EditState.texdlg_texture;

  GameTextures[n].flags &= ~(TF_SPECULAR);

  if (c)
    GameTextures[n].flags |= TF_METAL;
  else
    GameTextures[n].flags &= ~TF_METAL;

  UpdateDialog();
}

void CWorldTexturesDialog::OnMarbleCheck() {
  int c = IsDlgButtonChecked(IDC_MARBLE_CHECK);
  int n = D3EditState.texdlg_texture;

  GameTextures[n].flags &= ~(TF_SPECULAR);

  if (c)
    GameTextures[n].flags |= TF_MARBLE;
  else
    GameTextures[n].flags &= ~TF_MARBLE;

  UpdateDialog();
}

void CWorldTexturesDialog::OnPlasticCheck() {
  int c = IsDlgButtonChecked(IDC_PLASTIC_CHECK);
  int n = D3EditState.texdlg_texture;

  GameTextures[n].flags &= ~(TF_SPECULAR);

  if (c)
    GameTextures[n].flags |= TF_PLASTIC;
  else
    GameTextures[n].flags &= ~TF_PLASTIC;

  UpdateDialog();
}

void CWorldTexturesDialog::OnEffectTexture() {
  int c = IsDlgButtonChecked(IDC_EFFECT_TEXTURE);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_EFFECT;
  else
    GameTextures[n].flags &= ~TF_EFFECT;
}

void CWorldTexturesDialog::OnHudCockpitTexture() {
  int c = IsDlgButtonChecked(IDC_HUD_COCKPIT_TEXTURE);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_HUD_COCKPIT;
  else
    GameTextures[n].flags &= ~TF_HUD_COCKPIT;
}

void CWorldTexturesDialog::OnLightTexture() {
  int n = D3EditState.texdlg_texture;

  OutrageMessageBox("You cannot change this setting.  Change the RGB values instead.");

  CheckDlgButton(IDC_LIGHT_TEXTURE, GameTextures[n].flags & TF_LIGHT ? 1 : 0);
}

void CWorldTexturesDialog::OnProceduralCheck() {
  int c = IsDlgButtonChecked(IDC_PROCEDURAL_CHECK);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_PROCEDURAL;
  else
    GameTextures[n].flags &= ~TF_PROCEDURAL;

  UpdateDialog();
}

void CWorldTexturesDialog::OnProceduralButton() {
  int n = D3EditState.texdlg_texture;

  if (GameTextures[n].used == 0)
    return;

  if (GameTextures[n].flags & TF_WATER_PROCEDURAL) {
    CWaterProceduralDialog dlg;
    dlg.DoModal();
  } else {
    CProceduralDialog dlg;
    dlg.DoModal();
  }

  UpdateDialog();
}

void CWorldTexturesDialog::OnWaterProceduralCheck() {
  int c = IsDlgButtonChecked(IDC_WATER_PROCEDURAL_CHECK);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_WATER_PROCEDURAL;
  else
    GameTextures[n].flags &= ~TF_WATER_PROCEDURAL;

  UpdateDialog();
}

void CWorldTexturesDialog::OnForceLightmaps() {
  int c = IsDlgButtonChecked(IDC_FORCE_LIGHTMAPS);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_FORCE_LIGHTMAP;
  else
    GameTextures[n].flags &= ~TF_FORCE_LIGHTMAP;

  UpdateDialog();
}

void CWorldTexturesDialog::OnCoronaA() {
  int n = D3EditState.texdlg_texture;

  GameTextures[n].corona_type = 0;
  UpdateDialog();
}

void CWorldTexturesDialog::OnCoronaB() {
  int n = D3EditState.texdlg_texture;

  GameTextures[n].corona_type = 1;
  UpdateDialog();
}

void CWorldTexturesDialog::OnCoronaC() {
  int n = D3EditState.texdlg_texture;

  GameTextures[n].corona_type = 2;
  UpdateDialog();
}

void CWorldTexturesDialog::OnCoronaD() {
  int n = D3EditState.texdlg_texture;

  GameTextures[n].corona_type = 3;
  UpdateDialog();
}

void CWorldTexturesDialog::OnMultichecktex() {
  // CManageCheckin dlg;

  // dlg.DoModal();
  UpdateDialog();
}

void CWorldTexturesDialog::OnImport4444() {
  // TODO: Add your control notification handler code here
}

void CWorldTexturesDialog::OnSaturateLightmap() {
  int c = IsDlgButtonChecked(IDC_SATURATE_LIGHTMAP);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_SATURATE_LIGHTMAP;
  else
    GameTextures[n].flags &= ~TF_SATURATE_LIGHTMAP;

  UpdateDialog();
}

void CWorldTexturesDialog::OnAddNewHuge() {
  char filename[255], dir[255], fname[128], ext[32];
  char cur_name[100];
  int bm_handle, tex_handle;
  int c = 1, finding_name = 1;
  int anim = 0;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  int answer = MessageBox("256x256 textures are for SKIES ONLY.  If you are caught using them for any other purpose "
                          "you will be killed!  Are you sure this is what you want to do?",
                          "WARNING!", MB_YESNO);
  if (answer == IDNO)
    return;

  int alt_format = IsDlgButtonChecked(IDC_IMPORT_4444);
  int format = 0;

  if (alt_format) {
    answer = MessageBox("Are you sure you wish to import this texture with a 4444 format?", "Question", MB_YESNO);
    if (answer == IDNO)
      return;

    format = BITMAP_FORMAT_4444;
  }

  CString filter =
      "Descent III files "
      "(*.itl,*.tga,*.bbm,*.lbm,*.ogf,*.oaf,*.ilf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;*.oaf;*.ifl;*.itl||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  if (!strnicmp(ext, "ITL", 3)) {
    LoadITLFile(filename, HUGE_TEXTURE);
    UpdateDialog();
    return;
  }

  bm_handle = LoadTextureImage(filename, &anim, HUGE_TEXTURE, 0, 0, format);

  if (bm_handle < 0) {
    OutrageMessageBox("Couldn't open that bitmap/anim file.");
    return;
  }

  tex_handle = AllocTexture();

  while (finding_name) {
    if (c == 1)
      sprintf(cur_name, "%s", fname);
    else
      sprintf(cur_name, "%s%d", fname, c);
    if (FindTextureName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(GameTextures[tex_handle].name, cur_name);

  if (anim)
    GameTextures[tex_handle].flags |= TF_ANIMATED;
  else
    GameTextures[tex_handle].flags &= ~TF_ANIMATED;

  GameTextures[tex_handle].flags |= TF_TEXTURE_256;

  GameTextures[tex_handle].bm_handle = bm_handle;

  mprintf(0, "Making a copy of this bitmap/anim locally...\n");

  if (!anim) {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[tex_handle].bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);
  } else {
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameVClips[GameTextures[tex_handle].bm_handle].name);
    SaveVClip(filename, GameTextures[tex_handle].bm_handle);
  }

  CheckIfTextureIsTmap2(tex_handle);

  mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);

  D3EditState.texdlg_texture = tex_handle;

  UpdateDialog();
}

void CWorldTexturesDialog::OnLavaCheckbox() {
  int c = IsDlgButtonChecked(IDC_LAVA_CHECKBOX);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_LAVA;
  else
    GameTextures[n].flags &= ~TF_LAVA;
}

void CWorldTexturesDialog::OnRubbleCheckbox() {
  int c = IsDlgButtonChecked(IDC_RUBBLE_CHECKBOX);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_RUBBLE;
  else
    GameTextures[n].flags &= ~TF_RUBBLE;
}

void CWorldTexturesDialog::OnSelendokTextureAmbientSoundPulldown() {
  int n = D3EditState.texdlg_texture;

  GameTextures[n].sound = m_ambient_sound_combo.GetSelected();
}

void CWorldTexturesDialog::OnKillfocusTextureAmbientSoundVolume() {
  char str[256];

  ((CEdit *)GetDlgItem(IDC_TEXTURE_AMBIENT_SOUND_VOLUME))->GetWindowText(str, sizeof(str));

  float volume = atof(str);

  if ((volume > 100) || (volume < 0))
    OutrageMessageBox("Volume must be between 0 and 100");
  else {
    int n = D3EditState.texdlg_texture;
    GameTextures[n].sound_volume = volume;
  }
}

void CWorldTexturesDialog::OnSmoothSpecCheck() {
  // TODO: Add your control notification handler code here
  int c = IsDlgButtonChecked(IDC_SMOOTH_SPEC_CHECK);
  int n = D3EditState.texdlg_texture;

  if (c)
    GameTextures[n].flags |= TF_SMOOTH_SPECULAR;
  else
    GameTextures[n].flags &= ~TF_SMOOTH_SPECULAR;
}

#include "soundload.h"
#include "DallasSoundDlg.h"

void CWorldTexturesDialog::OnAmbientSoundSelect() {
  CDallasSoundDlg dlg;

  int selected = m_ambient_sound_combo.GetSelected();
  if (selected != -1)
    dlg.m_SoundName = Sounds[selected].name;

  if (dlg.DoModal() == IDCANCEL)
    return;

  m_ambient_sound_combo.SetSelected(dlg.m_SoundIndex);
}

void CWorldTexturesDialog::OnCheckBreakable() {
  int n = D3EditState.texdlg_texture;
  int c = IsDlgButtonChecked(IDC_CHECK_BREAKABLE);

  if (c)
    GameTextures[n].flags |= TF_BREAKABLE;
  else
    GameTextures[n].flags &= ~TF_BREAKABLE;

  UpdateDialog();
}
