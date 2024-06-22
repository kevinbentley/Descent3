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

* $Logfile: /DescentIII/Main/editor/OrphanRemoveDlg.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:57:38 $
* $Author: kevinb $
*
* Orphan file delete
*
* $Log: not supported by cvs2svn $
 *
 * 4     4/09/99 3:46p Jeff
 * handle new texture sound names
 *
 * 3     3/19/99 10:34a Jeff
 * enable/disable controls when thinking
 *
 * 2     3/18/99 8:41p Jeff
 * created orphan hunter dialog
*
* $NoKeywords: $
*/

// OrphanRemoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "OrphanRemoveDlg.h"
#include "manage.h"
#include "doorpage.h"
#include "gamefilepage.h"
#include "genericpage.h"
#include "shippage.h"
#include "soundpage.h"
#include "texpage.h"
#include "weaponpage.h"
#include "ddio.h"
#include "mem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrphanRemoveDlg dialog

COrphanRemoveDlg::COrphanRemoveDlg(CWnd *pParent /*=NULL*/) : CDialog(COrphanRemoveDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(COrphanRemoveDlg)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void COrphanRemoveDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(COrphanRemoveDlg)
  DDX_Control(pDX, IDC_LIST, m_List);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COrphanRemoveDlg, CDialog)
//{{AFX_MSG_MAP(COrphanRemoveDlg)
ON_CBN_SELCHANGE(IDC_DIRECTORY, OnSelchangeDirectory)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrphanRemoveDlg message handlers

bool HasFilesCheckedOut(void) {
  int i;
  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used) {
      return true;
    }
  }
  return false;
}

bool IsFileInGameFile(char *filename) {
  int i;

  for (i = 0; i < MAX_GAMEFILES; i++) {
    if (Gamefiles[i].used) {
      if (!stricmp(Gamefiles[i].name, filename)) {
        return true;
      }
    }
  }
  return false;
}

bool IsFileInDoorPage(char *filename) {
  mngs_door_page doorpage;
  int i;

  for (i = 0; i < MAX_DOORS; i++) {
    if (Doors[i].used) {
      mng_AssignDoorToDoorPage(i, &doorpage);
      if (!stricmp(doorpage.close_sound_name, filename))
        return true;
      if (!stricmp(doorpage.image_name, filename))
        return true;
      if (!stricmp(doorpage.open_sound_name, filename))
        return true;
    }
  }
  return false;
}

bool IsFileInGenericPage(char *filename) {
  mngs_generic_page genericpage;
  int i;
  int j, x;

  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE) {
      mng_AssignObjInfoToGenericPage(i, &genericpage);

      if (!stricmp(filename, genericpage.image_name))
        return true;
      if (!stricmp(filename, genericpage.med_image_name))
        return true;
      if (!stricmp(filename, genericpage.lo_image_name))
        return true;
      for (j = 0; j < MAX_OBJ_SOUNDS; j++) {
        if (!stricmp(filename, genericpage.sound_name[j]))
          return true;
      }
      for (j = 0; j < MAX_AI_SOUNDS; j++) {
        if (!stricmp(filename, genericpage.ai_sound_name[j]))
          return true;
      }
      for (x = 0; x < MAX_WBS_PER_OBJ; x++) {
        for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
          if (!stricmp(filename, genericpage.fire_sound_name[x][j]))
            return true;
        }
        for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
          if (!stricmp(filename, genericpage.weapon_name[x][j]))
            return true;
        }
      }

      for (x = 0; x < NUM_MOVEMENT_CLASSES; x++)
        for (j = 0; j < NUM_ANIMS_PER_CLASS; j++) {
          if (!stricmp(filename, genericpage.anim_sound_name[x][j]))
            return true;
        }
      for (j = 0; j < MAX_DSPEW_TYPES; j++) {
        if (!stricmp(filename, genericpage.dspew_name[j]))
          return true;
      }

      if (genericpage.objinfo_struct.description) {
        mem_free(genericpage.objinfo_struct.description);
      }
    }
  }
  return false;
}

bool IsFileInShipPage(char *filename) {
  mngs_ship_page shippage;
  int i;
  int j;
  int x;

  for (i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used) {
      mng_AssignShipToShipPage(i, &shippage);

      if (!stricmp(filename, shippage.image_name))
        return true;
      if (!stricmp(filename, shippage.dying_image_name))
        return true;
      if (!stricmp(filename, shippage.med_image_name))
        return true;
      if (!stricmp(filename, shippage.lo_image_name))
        return true;
      for (j = 0; j < MAX_PLAYER_WEAPONS; j++) {
        for (x = 0; x < MAX_WB_GUNPOINTS; x++) {
          if (!stricmp(filename, shippage.weapon_name[j][x]))
            return true;
        }
        for (x = 0; x < MAX_WB_FIRING_MASKS; x++) {
          if (!stricmp(filename, shippage.fire_sound_name[j][x]))
            return true;
        }
        if (!stricmp(filename, shippage.firing_sound_name[j]))
          return true;
        if (!stricmp(filename, shippage.release_sound_name[j]))
          return true;
        if (!stricmp(filename, shippage.spew_powerup_name[j]))
          return true;
      }
    }
  }

  return false;
}

bool IsFileInSoundPage(char *filename) {
  mngs_sound_page soundpage;
  int i;

  for (i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used) {
      mng_AssignSoundToSoundPage(i, &soundpage);
      if (!stricmp(filename, soundpage.raw_name))
        return true;
    }
  }

  return false;
}

bool IsFileInTexturePage(char *filename) {
  mngs_texture_page texpage;
  int i;

  for (i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used) {
      mng_AssignTextureToTexPage(i, &texpage);

      if (!stricmp(filename, texpage.bitmap_name))
        return true;

      if (!stricmp(filename, texpage.destroy_name))
        return true;

      if (!stricmp(filename, texpage.sound_name))
        return true;
    }
  }
  return false;
}

bool IsFileInWeaponPage(char *filename) {
  mngs_weapon_page weappage;
  int i, j;

  for (i = 0; i < MAX_WEAPONS; i++) {
    if (Weapons[i].used) {
      mng_AssignWeaponToWeaponPage(i, &weappage);

      if (!stricmp(filename, weappage.hud_image_name))
        return true;
      if (!stricmp(filename, weappage.fire_image_name))
        return true;
      if (!stricmp(filename, weappage.explode_image_name))
        return true;
      if (!stricmp(filename, weappage.smoke_image_name))
        return true;
      if (!stricmp(filename, weappage.scorch_image_name))
        return true;
      if (!stricmp(filename, weappage.icon_name))
        return true;
      if (!stricmp(filename, weappage.spawn_name))
        return true;
      if (!stricmp(filename, weappage.alternate_spawn_name))
        return true;
      if (!stricmp(filename, weappage.particle_name))
        return true;
      if (!stricmp(filename, weappage.robot_spawn_name))
        return true;
      for (j = 0; j < MAX_WEAPON_SOUNDS; j++) {
        if (!stricmp(filename, weappage.sound_name[j]))
          return true;
      }
    }
  }

  return false;
}

void COrphanRemoveDlg::Enable(bool enable) {
  CWnd *wnd;

  wnd = (CWnd *)GetDlgItem(IDOK);
  wnd->EnableWindow(enable);

  wnd = (CWnd *)GetDlgItem(IDCANCEL);
  wnd->EnableWindow(enable);

  wnd = (CWnd *)GetDlgItem(IDC_DIRECTORY);
  wnd->EnableWindow(enable);
}

void COrphanRemoveDlg::SetStatus(char *status) {
  CWnd *stat = (CWnd *)GetDlgItem(IDC_STATUS);
  stat->SetWindowText(status);
  App()->defer();
}

void COrphanRemoveDlg::OnOK() {
  if (HasFilesCheckedOut()) {
    OutrageMessageBox("You can't have any files checked out file doing this operation");
    return;
  }

  if (MessageBox("Are you sure you want to remove the orphans permanently?", NULL, MB_YESNO) != IDYES)
    return;
  SetStatus("Deleting Files");

  char directory[_MAX_PATH];
  CString dir;
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_DIRECTORY);
  int sel = combo->GetCurSel();
  if (sel == -1)
    return;
  combo->GetLBText(sel, dir);

  ddio_MakePath(directory, LocalD3Dir, "data", dir.GetBuffer(0), NULL);
  char fullpath[_MAX_PATH];

  int size = m_List.GetCount();
  for (int i = 0; i < size; i++) {
    if (m_List.GetCheck(i)) {
      // it's checked...delete!
      m_List.GetText(i, dir);
      ddio_MakePath(fullpath, directory, dir.GetBuffer(0), NULL);
      ddio_DeleteFile(fullpath);
    }
  }

  SetStatus("Ready...");

  OnSelchangeDirectory();
}

char *orphan_ignore[] = {
    ".",           "..",           "dallasfuncs.cpp", "osiris_common.h", "osiris_import.h", "osiris_vector.h",
    "anarchy.str", "coop.str",     "ctf.str",         "entropy.str",     "dmfc.str",        "d3.str",
    "hoard.str",   "dp_modem.str", "dp_serial.str",   "hyper.str",       "ipxclient.str",   "lanclient.str",
    "monster.str", "mtclient.str", "tanarchy.str"};
int num_orphan_ignore = sizeof(orphan_ignore) / sizeof(char *);

bool IsFileUsed(char *filename) {
  bool found = false;

  for (int i = 0; i < num_orphan_ignore; i++) {
    if (!stricmp(filename, orphan_ignore[i])) {
      found = true;
      goto done;
    }
  }

  if (!found)
    found = IsFileInGameFile(filename);
  if (!found)
    found = IsFileInWeaponPage(filename);
  if (!found)
    found = IsFileInSoundPage(filename);
  if (!found)
    found = IsFileInShipPage(filename);
  if (!found)
    found = IsFileInDoorPage(filename);
  if (!found)
    found = IsFileInTexturePage(filename);
  if (!found)
    found = IsFileInGenericPage(filename);

done:
  App()->defer();

  return found;
}

int filelen(char *filename, char *dir) {
  char path[_MAX_PATH];
  ddio_MakePath(path, dir, filename, NULL);
  CFILE *cf = cfopen(filename, "rb");
  if (!cf)
    return 0;

  int len = cfilelength(cf);
  cfclose(cf);
  return len;
}

bool isdirectory(char *filename, char *basepath) {
  char fullpath[_MAX_PATH];
  ddio_MakePath(fullpath, basepath, filename, NULL);
  char olddir[_MAX_PATH];

  ddio_GetWorkingDir(olddir, _MAX_PATH);
  if (ddio_SetWorkingDir(fullpath)) {
    ddio_SetWorkingDir(olddir);
    return true;
  }
  return false;
}

void COrphanRemoveDlg::OnSelchangeDirectory() {
  CString dir;
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_DIRECTORY);
  int sel = combo->GetCurSel();
  if (sel == -1)
    return;

  SetStatus("Updating File List");

  Enable(false);

  combo->GetLBText(sel, dir);
  m_List.ResetContent();

  char fullpath[_MAX_PATH];
  ddio_MakePath(fullpath, LocalD3Dir, "data", dir.GetBuffer(0), NULL);
  char oldpath[_MAX_PATH];
  ddio_GetWorkingDir(oldpath, _MAX_PATH);
  ddio_SetWorkingDir(fullpath);

  char filename[_MAX_PATH];
  int num_files = 0;
  int total_filesize = 0;
  CWnd *stats = (CWnd *)GetDlgItem(IDC_STATS);
  char data[256];

  sprintf(data, "Num Files: %d\r\nSize: %dK", 0, 0);
  stats->SetWindowText(data);

  if (ddio_FindFileStart("*.*", filename)) {
    if (!isdirectory(filename, fullpath) && !IsFileUsed(filename)) {
      m_List.AddString(filename);
      num_files++;
      total_filesize += filelen(filename, fullpath);
      sprintf(data, "Num Files: %d\r\nSize: %dK", num_files, total_filesize / 1024);
      stats->SetWindowText(data);
    }

    while (ddio_FindNextFile(filename)) {
      if (!isdirectory(filename, fullpath) && !IsFileUsed(filename)) {
        m_List.AddString(filename);
        num_files++;
        total_filesize += filelen(filename, fullpath);
        sprintf(data, "Num Files: %d\r\nSize: %dK", num_files, total_filesize / 1024);
        stats->SetWindowText(data);
      }
    }
  }
  ddio_FindFileClose();

  ddio_SetWorkingDir(oldpath);

  // select all
  for (int i = 0; i < num_files; i++) {
    m_List.SetCheck(i, 1);
    m_List.SetSel(i, TRUE);
  }

  SetStatus("Ready...");

  Enable(true);
}

extern char *DirectoryNames[];
extern int NumDirectoryNames;

BOOL COrphanRemoveDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_DIRECTORY);

  for (int i = 0; i < NumDirectoryNames; i++) {
    combo->AddString(DirectoryNames[i]);
  }

  Enable(true);

  SetStatus("Ready...");

  return TRUE;
}

void COrphanRemoveDlg::OnCancel() { CDialog::OnCancel(); }
