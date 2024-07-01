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

 * $Logfile: /DescentIII/Main/editor/WorldObjectsPlayerDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * WorldObjectsPlayerDialog.cpp : implementation file
 *
 * $Log: not supported by cvs2svn $
 *
 * 31    4/21/99 4:39p Jason
 * fixed ship model loading
 *
 * 30    11/06/98 12:34p Jason
 * more speedups for manage system
 *
 * 29    10/15/98 11:06a Jason
 * fixed stupid checkin bug
 *
 * 28    10/14/98 12:09p Jason
 * fixed some long standing name problems
 *
 * 27    10/02/98 1:47p Jason
 * added lod player ships
 *
 * 26    8/20/98 11:53a Samir
 * fixed filename make when choosing a cockpit inf file.
 *
 * 25    8/07/98 2:43p Jeff
 * added allow by default
 *
 * 24    7/31/98 5:23p Jason
 * added ship armor scalars
 *
 * 23    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 22    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 21    4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 20    4/17/98 1:53p Matt
 * Reinitialize all objects when leaving the editor dialogs for generic
 * objects (robots, powerps), doors, and player ships.
 *
 * 19    4/06/98 1:33p Samir
 * Added interface to get cockpit inf filename and store in page.
 *
 * 18    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 17    3/12/98 6:51p Chris
 * Added a check
 *
 * 16    2/25/98 12:23p Jason
 * ask users if they want to delete WB info when changing the model
 *
 * 15    2/06/98 6:29p Jason
 * fixed broken checkin
 *
 * 14    2/06/98 6:18p Jason
 * fixed model mixup bug
 *
 * 13    12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 12    12/01/97 6:06p Samir
 * Implemented new FileDialog tracker system.
 *
 * 11    11/04/97 6:18p Chris
 * Added support so that the player ship uses the robot's firing dialog.
 *
 * 10    11/02/97 4:27p Matt
 * Made physics dialog copy data back into original struct, instead of
 * having the caller do it.
 *
 * 9     10/21/97 11:57a Jason
 * added ability to set dying model for player ship
 *
 * 8     10/06/97 3:24p Jason
 * fixed checkin problem
 *
 * 7     9/02/97 3:28p Matt
 * Got rid of warnings
 *
 * 6     8/13/97 11:25a Matt
 * Made player ship dialog use standard physics dialog
 *
 * 5     8/08/97 2:25p Matt
 * Took out error messages which are now handled by mng_MakeLocker()
 *
 * 4     8/06/97 12:40p Jason
 * fixed some potentially serious memory problems
 *
 * 3     7/24/97 6:11p Matt
 * Created symbolic constant for default zoom, and used it every place
 * that specifies zoom
 *
 * $NoKeywords: $
 */

#include <filesystem>

#include "mfc_compatibility.h"
#include "editor.h"
#include "WorldObjectsPlayerDialog.h"
#include "shippage.h"
#include "ship.h"
#include "manage.h"
#include "polymodel.h"
#include "PhysicsDlg.h"
#include "PlayerWeaponsDialog.h"
#include "robotfire.h"
#include "ddio.h"
#include "polymodel.h"
#include "objinit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldObjectsPlayerDialog dialog

CWorldObjectsPlayerDialog::CWorldObjectsPlayerDialog(CWnd *pParent /*=NULL*/)
    : CDialog(CWorldObjectsPlayerDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWorldObjectsPlayerDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CWorldObjectsPlayerDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWorldObjectsPlayerDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldObjectsPlayerDialog, CDialog)
//{{AFX_MSG_MAP(CWorldObjectsPlayerDialog)
ON_BN_CLICKED(IDC_ADD_PSHIP, OnAddPship)
ON_BN_CLICKED(IDC_PSHIP_CHECKIN, OnPshipCheckin)
ON_BN_CLICKED(IDC_PSHIP_DELETE, OnPshipDelete)
ON_BN_CLICKED(IDC_PSHIP_LOAD_MODEL, OnPshipLoadModel)
ON_BN_CLICKED(IDC_PSHIP_LOCK, OnPshipLock)
ON_EN_KILLFOCUS(IDC_PSHIP_NAME_EDIT, OnKillfocusPshipNameEdit)
ON_BN_CLICKED(IDC_PSHIP_NEXT, OnPshipNext)
ON_BN_CLICKED(IDC_PSHIP_PREV, OnPshipPrev)
ON_BN_CLICKED(IDC_PSHIPS_OUT, OnPshipsOut)
ON_CBN_SELENDOK(IDC_PSHIP_PULLDOWN, OnSelendokPshipPulldown)
ON_WM_TIMER()
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_PSHIP_EDIT_PHYSICS, OnPshipEditPhysics)
ON_BN_CLICKED(IDC_PSHIP_DYING_MODEL, OnPshipDyingModel)
ON_BN_CLICKED(IDC_NULL_DYING, OnNullDying)
ON_BN_CLICKED(IDC_EDIT_WEAPONS, OnEditWeapons)
ON_BN_CLICKED(IDC_PSHIP_COCKPIT, OnPshipCockpit)
ON_EN_KILLFOCUS(IDC_PSHIP_COCKPIT_EDIT, OnKillfocusPshipCockpitEdit)
ON_WM_DESTROY()
ON_EN_KILLFOCUS(IDC_SHIP_ARMOR_EDIT, OnKillfocusShipArmorEdit)
ON_BN_CLICKED(IDC_DEFAULTALLOW, OnDefaultallow)
ON_BN_CLICKED(IDC_HIRES_RADIO, OnHiresRadio)
ON_BN_CLICKED(IDC_MEDRES_RADIO, OnMedresRadio)
ON_BN_CLICKED(IDC_LORES_RADIO, OnLoresRadio)
ON_BN_CLICKED(IDC_NOLOD, OnNolod)
ON_EN_KILLFOCUS(IDC_LOD_DISTANCE_EDIT, OnKillfocusLodDistanceEdit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldObjectsPlayerDialog message handlers

void CWorldObjectsPlayerDialog::OnAddPship() {
  char filename[256], dir[256], fname[256], ext[32];
  char cur_name[100];
  int img_handle;
  int ship_handle;
  int c = 1, finding_name = 1;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_model_dir, sizeof(Current_model_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadShipImage(filename);

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that model file.");
    return;
  }

  // Alloc a ship and give a name not already taken by some other ship

  ship_handle = AllocShip();

  while (finding_name) {
    if (c == 1)
      sprintf(cur_name, "%s", fname);
    else
      sprintf(cur_name, "%s%d", fname, c);
    if (FindShipName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(Ships[ship_handle].name, cur_name);

  Ships[ship_handle].model_handle = img_handle;

  // Finally, save a local copy of the model/anim and alloc a tracklock
  mprintf(0, "Making a copy of this model locally...\n");

  std::filesystem::path destname = LocalModelsDir / Poly_models[Ships[ship_handle].model_handle].name;
  cf_CopyFile(destname, filename);

  mng_AllocTrackLock(cur_name, PAGETYPE_SHIP);

  D3EditState.current_ship = ship_handle;

  RemapShips();

  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnPshipCheckin() {
  int n = D3EditState.current_ship;
  mngs_Pagelock temp_pl;
  int r;

  if (Num_ships < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure we own this ship
  strcpy(temp_pl.name, Ships[n].name);
  temp_pl.pagetype = PAGETYPE_SHIP;

  r = mng_CheckIfPageOwned(&temp_pl, TableUser);
  if (r < 0)
    OutrageMessageBox(ErrorString);
  else if (r == 0)
    OutrageMessageBox(InfoString);
  else {
    // Change the pagelock state to UNLOCKED
    strcpy(temp_pl.holder, "UNLOCKED");
    if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
      MessageBox(ErrorString, "Error!");
      mng_EraseLocker();
      return;
    } else {
      // Now actually replace the copy on the net with our local one

      if (!mng_ReplacePage(Ships[n].name, Ships[n].name, n, PAGETYPE_SHIP, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this ship anim/model to the network for all
        std::filesystem::path srcname = LocalModelsDir / Poly_models[Ships[n].model_handle].name;
        std::filesystem::path destname = NetModelsDir / Poly_models[Ships[n].model_handle].name;

        cf_CopyFile(destname, srcname);

        if (Ships[n].dying_model_handle != -1) {
          srcname = LocalModelsDir / Poly_models[Ships[n].dying_model_handle].name;
          destname = NetModelsDir / Poly_models[Ships[n].dying_model_handle].name;

          cf_CopyFile(destname, srcname);
        }

        if (Ships[n].med_render_handle != -1) {
          srcname = LocalModelsDir / Poly_models[Ships[n].med_render_handle].name;
          destname = NetModelsDir / Poly_models[Ships[n].med_render_handle].name;

          cf_CopyFile(destname, srcname);
        }

        if (Ships[n].lo_render_handle != -1) {
          srcname = LocalModelsDir / Poly_models[Ships[n].lo_render_handle].name;
          destname = NetModelsDir / Poly_models[Ships[n].lo_render_handle].name;

          cf_CopyFile(destname, srcname);
        }

        if (Ships[n].cockpit_name[0]) {
          srcname = LocalMiscDir / Ships[n].cockpit_name;
          destname = NetMiscDir / Ships[n].cockpit_name;

          cf_CopyFile(destname, srcname);
        }

        OutrageMessageBox("Ship checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Ships[n].name, PAGETYPE_SHIP, 1);
        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Ships[n].name, PAGETYPE_SHIP);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }

  mng_EraseLocker();
}

void CWorldObjectsPlayerDialog::OnPshipDelete() {
  int answer, tl;
  mngs_Pagelock pl;
  int n = D3EditState.current_ship;

  if (Num_ships < 1)
    return;

  // Check to see if we even have it locked
  if ((tl = mng_FindTrackLock(Ships[n].name, PAGETYPE_SHIP)) == -1) {
    OutrageMessageBox("This ship is not yours to delete.  Lock first.");
    return;
  }

  // Make sure its to be deleted
  answer = MessageBox("Are you sure you want to delete this ship?", Ships[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Ships[n].name);
  pl.pagetype = PAGETYPE_SHIP;

  // Check to see if this is a local ship only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(Ships[n].name, PAGETYPE_SHIP, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else // if its network, delete it from both the net and local drives
  {

    mng_FreeTrackLock(tl);

    mng_DeletePage(Ships[n].name, PAGETYPE_SHIP, 0);
    mng_DeletePage(Ships[n].name, PAGETYPE_SHIP, 1);

    mng_DeletePagelock(Ships[n].name, PAGETYPE_SHIP);
  }

  // Advance to the next ship
  D3EditState.current_ship = GetNextShip(n);

  FreePolyModel(Ships[n].model_handle);
  if (Ships[n].dying_model_handle != -1)
    FreePolyModel(Ships[n].dying_model_handle);

  FreeShip(n);

  mng_EraseLocker();

  OutrageMessageBox("Ship deleted.");

  RemapShips();

  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnPshipLoadModel() {
  char filename[255];
  int img_handle;
  int ship_handle;
  int c = 1, finding_name = 1;
  int model = 0;

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_model_dir, sizeof(Current_model_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadPolyModel(filename, 0);

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that animation/model file.");
    return;
  }

  ship_handle = D3EditState.current_ship;

  // Get rid of the old one possibly
  if (m_lod == 0) {
    ChangeOldModelsForObjects(Ships[ship_handle].model_handle, img_handle);
    FreePolyModel(Ships[ship_handle].model_handle);
    Ships[ship_handle].model_handle = img_handle;
  } else if (m_lod == 1) {
    if (Ships[ship_handle].med_render_handle != -1)
      FreePolyModel(Ships[ship_handle].med_render_handle);

    Ships[ship_handle].med_render_handle = img_handle;
  } else {
    if (Ships[ship_handle].lo_render_handle != -1)
      FreePolyModel(Ships[ship_handle].lo_render_handle);

    Ships[ship_handle].lo_render_handle = img_handle;
  }

  // A new model might induce a new weapon stucture
  if (OutrageMessageBox(MBOX_YESNO, "Would you like to clear the weapon battery info?") == IDYES) {
    WBClearInfo(Ships[ship_handle].static_wb);
  }

  // Finally, save a local copy of the model
  std::filesystem::path curname = LocalModelsDir / Poly_models[img_handle].name;
  cf_CopyFile(curname, filename);

  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnPshipLock() {
  int n = D3EditState.current_ship;
  mngs_Pagelock temp_pl;
  mngs_ship_page shippage;
  int r;

  if (Num_ships < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, Ships[n].name);
  temp_pl.pagetype = PAGETYPE_SHIP;

  r = mng_CheckIfPageLocked(&temp_pl);
  if (r == 2) {
    int answer;
    answer = OutrageMessageBox(MBOX_YESNO, "This page is not even in the table file, or the database maybe corrupt.  "
                                           "Override to 'Unlocked'? (Select NO if you don't know what you're doing)");
    if (answer == IDYES) {
      strcpy(temp_pl.holder, "UNLOCKED");
      if (!mng_ReplacePagelock(temp_pl.name, &temp_pl))
        MessageBox(ErrorString, "Error!");
    }

  } else if (r < 0)
    OutrageMessageBox(ErrorString);
  else if (r == 1)
    OutrageMessageBox(InfoString);
  else {

    // Everything is ok.  Tell the network we're locking it and get a copy to
    // our local drive

    strcpy(temp_pl.holder, TableUser);
    if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
      MessageBox(ErrorString, "Error!");
      mng_EraseLocker();
      return;
    } else {
      // Search thru the net pagefile and get a new copy in RAM in case anyone
      // changed it since we started the editor
      if (mng_FindSpecificShipPage(temp_pl.name, &shippage)) {
        if (mng_AssignShipPageToShip(&shippage, n)) {
          if (!mng_ReplacePage(Ships[n].name, Ships[n].name, n, PAGETYPE_SHIP, 1)) {
            OutrageMessageBox("There was problem writing that page locally!");
            mng_EraseLocker();
            return;
          }

          OutrageMessageBox("Ship locked.");
        } else
          OutrageMessageBox(
              "There was a problem loading this ship.  You might encounter problems in dealing with it.  Good luck!");

        mng_AllocTrackLock(Ships[n].name, PAGETYPE_SHIP);
        UpdateDialog();
      } else
        OutrageMessageBox("Couldn't find that ship in the table file!");
    }
  }
  mng_EraseLocker();
}

void CWorldObjectsPlayerDialog::OnKillfocusPshipNameEdit() {
  CEdit *ebox;
  int n = D3EditState.current_ship;
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this ship locked, if not reset name and bail
  int p = mng_FindTrackLock(Ships[n].name, PAGETYPE_SHIP);
  if (p == -1) {
    OutrageMessageBox("You must lock this ship if you wish to change its name.");
    CEdit *ebox = (CEdit *)GetDlgItem(IDC_PSHIP_NAME_EDIT);
    ebox->SetWindowText(Ships[n].name);
    return;
  }

  // Get the new name
  ebox = (CEdit *)GetDlgItem(IDC_PSHIP_NAME_EDIT);
  ebox->GetWindowText(name, PAGENAME_LEN);

  // Check to see if there is already a ship with this name.  If so, reset and bail
  if (FindShipName(name) != -1) {
    OutrageMessageBox("There already is a ship with that name...choose another name.");

    CEdit *ebox = (CEdit *)GetDlgItem(IDC_PSHIP_NAME_EDIT);
    ebox->SetWindowText(Ships[n].name);
    return;
  }

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Ships[n].name);
  pl.pagetype = PAGETYPE_SHIP;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Ships[n].name, name, PAGETYPE_SHIP);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Ships[n].name);
    strcpy(Ships[n].name, name);

    mng_ReplacePage(oldname, Ships[n].name, n, PAGETYPE_SHIP, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Ships[n].name, name);
  mng_EraseLocker();

  RemapShips();
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnPshipNext() {
  D3EditState.current_ship = GetNextShip(D3EditState.current_ship);
  m_lod = 0;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnPshipPrev() {
  D3EditState.current_ship = GetPrevShip(D3EditState.current_ship);
  m_lod = 0;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnPshipsOut() {
  char str[10000];
  int total = 0;

  mng_DisplayLockList(TableUser);

  sprintf(str, "User %s has these ships held locally:\n\n", TableUser);
  for (int i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_SHIP) {
      char temp[90];

      sprintf(temp, "%s", GlobalTrackLocks[i].name);
      strcat(str, temp);
      strcat(str, "\n");
      total++;
    }
  }

  if (total != 0) {
    // Display that string
    MessageBox(str, "Ships", MB_OK);
  }
}

void CWorldObjectsPlayerDialog::OnSelendokPshipPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_PSHIP_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_PSHIP_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindShipName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted ship list, but probably nothing.");
    UpdateDialog();
  }

  D3EditState.current_ship = i;
  UpdateDialog();
}

// When closing, save all our checked out ships locally so we know
// what stuff to flag as "checked out" the next time we start up
void CWorldObjectsPlayerDialog::SaveShipsOnClose() {
  int i, t;

  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_SHIP) {
      t = FindShipName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);

      mng_ReplacePage(Ships[t].name, Ships[t].name, t, PAGETYPE_SHIP, 1);
    }
  }
}

BOOL CWorldObjectsPlayerDialog::DestroyWindow() {

  SaveShipsOnClose();
  return CDialog::DestroyWindow();
}

BOOL CWorldObjectsPlayerDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  CWnd::SetTimer(1, 50, NULL);

  m_lod = 0;

  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorldObjectsPlayerDialog::OnTimer(UINT nIDEvent) {

  UpdateShipView();
  CDialog::OnTimer(nIDEvent);
}

void CWorldObjectsPlayerDialog::UpdateDialog() {
  CEdit *ebox;
  CButton *bbox;
  //	CStatic *stext;
  int n = D3EditState.current_ship;
  char str[50];
  char txt[50];

  if (Num_ships < 1) {
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_NEXT);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_PREV);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_COCKPIT);
    bbox->EnableWindow(FALSE);
    return;
  } else {
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_NEXT);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_PREV);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_COCKPIT);
    bbox->EnableWindow(TRUE);
  }

  if (!Ships[n].used)
    n = D3EditState.current_ship = GetNextShip(n);

  ebox = (CEdit *)GetDlgItem(IDC_PSHIP_NAME_EDIT);
  ebox->SetWindowText(Ships[n].name);

  ebox = (CEdit *)GetDlgItem(IDC_PSHIP_MODEL_NAME_EDIT);

  if (m_lod == 0)
    ebox->SetWindowText(Poly_models[Ships[n].model_handle].name);
  else if (m_lod == 1) {
    if (Ships[n].med_render_handle == -1)
      ebox->SetWindowText("No model defined");
    else
      ebox->SetWindowText(Poly_models[Ships[n].med_render_handle].name);
  } else {
    if (Ships[n].lo_render_handle == -1)
      ebox->SetWindowText("No model defined");
    else
      ebox->SetWindowText(Poly_models[Ships[n].lo_render_handle].name);
  }

  // Do LOD distance edit box
  ebox = (CEdit *)GetDlgItem(IDC_LOD_DISTANCE_EDIT);

  if (m_lod == 0)
    ebox->SetWindowText("0");
  else if (m_lod == 1) {
    sprintf(txt, "%f", Ships[n].med_lod_distance);
    ebox->SetWindowText(txt);
  } else {
    sprintf(txt, "%f", Ships[n].lo_lod_distance);
    ebox->SetWindowText(txt);
  }

  ebox = (CEdit *)GetDlgItem(IDC_PSHIP_DYING_MODEL_NAME_EDIT);
  if (Ships[n].dying_model_handle == -1)
    ebox->SetWindowText("<none>");
  else
    ebox->SetWindowText(Poly_models[Ships[n].dying_model_handle].name);

  ebox = (CEdit *)GetDlgItem(IDC_PSHIP_COCKPIT_EDIT);
  ebox->SetWindowText(Ships[n].cockpit_name);

  ebox = (CEdit *)GetDlgItem(IDC_SHIP_ARMOR_EDIT);
  sprintf(str, "%f", Ships[n].armor_scalar);
  ebox->SetWindowText(str);

  bbox = (CButton *)GetDlgItem(IDC_PSHIP_CHECKIN);
  if (mng_FindTrackLock(Ships[n].name, PAGETYPE_SHIP) == -1) {
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_LOCK);
    bbox->EnableWindow(TRUE);
  } else {
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_PSHIP_LOCK);
    bbox->EnableWindow(FALSE);
  }

  bbox = (CButton *)GetDlgItem(IDC_DEFAULTALLOW);
  if (Ships[n].flags & SF_DEFAULT_ALLOW)
    bbox->SetCheck(1);
  else
    bbox->SetCheck(0);

  SendDlgItemMessage(IDC_PSHIP_PULLDOWN, CB_RESETCONTENT, 0, 0);

  for (int i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used)
      SendDlgItemMessage(IDC_PSHIP_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Ships[i].name);
  }
  SendDlgItemMessage(IDC_PSHIP_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Ships[n].name);

  ebox = (CEdit *)GetDlgItem(IDC_NOLOD);
  if (m_lod == 0)
    ebox->EnableWindow(FALSE);
  else if (m_lod == 1) {
    if (Ships[n].med_render_handle == -1)
      ebox->EnableWindow(FALSE);
    else
      ebox->EnableWindow(TRUE);
  } else {
    if (Ships[n].lo_render_handle == -1)
      ebox->EnableWindow(FALSE);
    else
      ebox->EnableWindow(TRUE);
  }

  bbox = (CButton *)GetDlgItem(IDC_HIRES_RADIO);
  bbox->SetCheck(m_lod == 0);

  bbox = (CButton *)GetDlgItem(IDC_MEDRES_RADIO);
  bbox->SetCheck(m_lod == 1);

  bbox = (CButton *)GetDlgItem(IDC_LORES_RADIO);
  bbox->SetCheck(m_lod == 2);

  UpdateShipView();
}

#define NUM_ANIM_FRAMES 30

void CWorldObjectsPlayerDialog::UpdateShipView(void) {
  int n = D3EditState.current_ship;
  CWnd *shipwnd;
  RECT rect;
  int x, y, bm_handle, w, h, render_handle;
  static int frame = 0, spin_frame = 0;
  static int last_ship = -1;
  static int last_model_handle = -1;
  static int ship_dir = 0;

  if (Num_ships < 1)
    return;

  if (ship_dir == 0) {
    frame++;
    if (frame == NUM_ANIM_FRAMES) {
      frame = NUM_ANIM_FRAMES - 1;
      ship_dir = 1;
    }
  } else {
    frame--;
    if (frame == -1) {
      frame = 0;
      ship_dir = 0;
    }
  }

  shipwnd = GetDlgItem(IDC_SHIPVIEW);
  shipwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  if (m_lod == 0)
    render_handle = Ships[n].model_handle;
  else if (m_lod == 1)
    render_handle = Ships[n].med_render_handle;
  else
    render_handle = Ships[n].lo_render_handle;

  if (last_ship != n || last_model_handle != render_handle) {
    Desktop_surf->clear(rect.left, rect.top, w, h);
    last_ship = n;
    last_model_handle = Ships[n].model_handle;
  }

  bm_handle = render_handle;

  if (bm_handle == -1)
    return;

  vector zero_vector;
  vector view_vector = {0, 0, -20};
  matrix id_matrix, rot_matrix;
  poly_model *pm = GetPolymodelPointer(bm_handle);

  vm_MakeZero(&zero_vector);
  vm_MakeIdentity(&id_matrix);

  float norm_angles[30];

  for (int i = 0; i < 30; i++)
    norm_angles[i] = (float)frame / (float)NUM_ANIM_FRAMES;

  spin_frame++;

  vm_AnglesToMatrix(&rot_matrix, 0, spin_frame * 400, 0);

  m_ShipSurf.create(128, 128, BPP_16);
  grViewport *vport = new grViewport(&m_ShipSurf);
  StartEditorFrame(vport, &view_vector, &id_matrix, D3_DEFAULT_ZOOM);
  DrawPolygonModel(&zero_vector, &rot_matrix, bm_handle, norm_angles, 0, 1.0, 1.0, 1.0);
  EndEditorFrame();

  x = rect.left + ((rect.right - rect.left) / 2) - m_ShipSurf.width() / 2;
  y = rect.top + ((rect.bottom - rect.top) / 2) - m_ShipSurf.height() / 2;
  Desktop_surf->blt(x, y, &m_ShipSurf);

  delete vport;
  m_ShipSurf.free();
}

BOOL CWorldObjectsPlayerDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  WinHelp(HID_PLAYERSHIPSDLG, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CWorldObjectsPlayerDialog::OnPshipEditPhysics() {
  int n = D3EditState.current_ship;

  CPhysicsDlg dlg(&Ships[n].phys_info);

  dlg.DoModal();
}

void CWorldObjectsPlayerDialog::OnPshipDyingModel() {
  char filename[_MAX_PATH];
  int img_handle;
  int ship_handle;
  int c = 1, finding_name = 1;
  int model = 0;

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_model_dir, sizeof(Current_model_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadShipImage(filename);

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that animation/model file.");
    return;
  }

  ship_handle = D3EditState.current_ship;

  Ships[ship_handle].dying_model_handle = img_handle;

  // Finally, save a local copy of the model

  std::filesystem::path curname = LocalModelsDir / Poly_models[Ships[ship_handle].dying_model_handle].name;
  cf_CopyFile(curname, filename);

  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnNullDying() {
  int n = D3EditState.current_ship;
  Ships[n].dying_model_handle = -1;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnEditWeapons() {
  PlayerWeaponsDialog dlg(D3EditState.current_ship);

  dlg.DoModal();
  //	if (dlg.DoModal() == IDOK)
  //		dlg.GetData();
}

void CWorldObjectsPlayerDialog::OnPshipCockpit() {
  char filename[_MAX_PATH];
  char curname[_MAX_PATH];
  char ext[32];

  // Get the filename of the representing image

  CString filter = "Descent III files (*.inf)|*.inf||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, NULL, 0))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  ddio_SplitPath(filename, NULL, curname, ext);
  sprintf(Ships[D3EditState.current_ship].cockpit_name, "%s%s", curname, ext);

  // Finally, save a local copy of the inf file.
  sprintf(curname, "%s\\%s", LocalMiscDir.u8string().c_str(), Ships[D3EditState.current_ship].cockpit_name);
  cf_CopyFile(curname, filename);

  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnKillfocusPshipCockpitEdit() {
  CEdit *ebox;
  char name[PAGENAME_LEN];

  // Get the new name
  ebox = (CEdit *)GetDlgItem(IDC_PSHIP_COCKPIT_EDIT);
  ebox->GetWindowText(name, PAGENAME_LEN);

  strcpy(Ships[D3EditState.current_ship].cockpit_name, name);
}

void CWorldObjectsPlayerDialog::OnDestroy() {
  CDialog::OnDestroy();

  ObjReInitAll();
}

void CWorldObjectsPlayerDialog::OnKillfocusShipArmorEdit() {
  CEdit *ebox;
  char name[PAGENAME_LEN];

  // Get the new name
  ebox = (CEdit *)GetDlgItem(IDC_SHIP_ARMOR_EDIT);

  ebox->GetWindowText(name, PAGENAME_LEN);
  float val = atof(name);

  if (val < .05)
    val = .05f;
  if (val > 10)
    val = 10;

  Ships[D3EditState.current_ship].armor_scalar = val;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnDefaultallow() {
  CButton *bbox;

  bbox = (CButton *)GetDlgItem(IDC_DEFAULTALLOW);

  if (bbox->GetCheck())
    Ships[D3EditState.current_ship].flags |= SF_DEFAULT_ALLOW;
  else
    Ships[D3EditState.current_ship].flags &= ~SF_DEFAULT_ALLOW;
}

void CWorldObjectsPlayerDialog::OnHiresRadio() {
  m_lod = 0;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnMedresRadio() {
  m_lod = 1;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnLoresRadio() {
  m_lod = 2;
  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnNolod() {
  int n = D3EditState.current_ship;

  if (m_lod == 0) {
    MessageBox("You must have a hi-res model.");
    return;
  }

  else if (m_lod == 1) {
    FreePolyModel(Ships[n].med_render_handle);
    Ships[n].med_render_handle = -1;

  } else {
    FreePolyModel(Ships[n].lo_render_handle);
    Ships[n].lo_render_handle = -1;
  }

  UpdateDialog();
}

void CWorldObjectsPlayerDialog::OnKillfocusLodDistanceEdit() {
  CEdit *ebox;
  char str[255];
  float dist;
  int n = D3EditState.current_ship;

  ebox = (CEdit *)GetDlgItem(IDC_LOD_DISTANCE_EDIT);
  ebox->GetWindowText(str, 180);
  dist = atof(str);

  if (dist < 0)
    return;

  if (m_lod == 1) {
    Ships[n].med_lod_distance = dist;
  } else if (m_lod == 2) {
    Ships[n].lo_lod_distance = dist;
  }

  UpdateDialog();
}
