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

 * $Logfile: /DescentIII/Main/editor/WorldObjectsDoorDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * WorldObjectsDoorDialog.cpp : implementation file
 *
 * $Log: not supported by cvs2svn $
 *
 * 26    2/04/99 2:05p Matt
 * Added blastable doors
 *
 * 25    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 24    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 23    12/21/98 5:27p Jeff
 * added osiris module information to door page.  Fixed up dialogs for
 * objects and doors for script interface (added a browse button)
 *
 * 22    11/06/98 12:34p Jason
 * more speedups for manage system
 *
 * 21    10/14/98 12:08p Jason
 * fixed some long standing name problems
 *
 * 20    10/08/98 4:24p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 19    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 18    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 17    5/22/98 8:50p Matt
 * Added sounds for doors
 *
 * 16    4/17/98 1:53p Matt
 * Reinitialize all objects when leaving the editor dialogs for generic
 * objects (robots, powerps), doors, and player ships.
 *
 * 15    4/06/98 4:53p Jason
 * got pageable polymodels working correctly with editor
 *
 * 14    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 13    2/02/98 7:07p Matt
 * Added support for doors that can be seen through even when closed
 *
 * 12    1/25/98 5:17p Matt
 * Changed the door dialog to be more like the generic dialog
 *
 * 11    1/23/98 5:39p Matt
 * Added validity checking for door models.
 *
 * 10    12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 9     12/01/97 6:06p Samir
 * Implemented new FileDialog tracker system.
 *
 * 8     10/06/97 3:24p Jason
 * fixed checkin problem
 *
 * 7     10/06/97 1:01p Jason
 * made doors work with scripts (sort of)
 *
 * 6     9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 5     8/08/97 2:25p Matt
 * Took out error messages which are now handled by mng_MakeLocker()
 *
 * 4     8/07/97 12:42p Jason
 * fixed potential memory problem
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
#include "WorldObjectsDoorDialog.h"
#include "manage.h"
#include "doorpage.h"
#include "mono.h"
#include "vclip.h"
#include "polymodel.h"
#include "door.h"
#include "ddio.h"
#include "EditLineDialog.h"
#include "objinit.h"
#include "soundload.h"
#include "mem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldObjectsDoorDialog dialog

CWorldObjectsDoorDialog::CWorldObjectsDoorDialog(CWnd *pParent /*=NULL*/)
    : CDialog(CWorldObjectsDoorDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWorldObjectsDoorDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CWorldObjectsDoorDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWorldObjectsDoorDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldObjectsDoorDialog, CDialog)
//{{AFX_MSG_MAP(CWorldObjectsDoorDialog)
ON_BN_CLICKED(IDC_ADD_DOOR, OnAddDoor)
ON_BN_CLICKED(IDC_CHECKIN_DOOR, OnCheckinDoor)
ON_EN_KILLFOCUS(IDC_CLOSE_TIME, OnKillfocusCloseTime)
ON_BN_CLICKED(IDC_DELETE_DOOR, OnDeleteDoor)
ON_BN_CLICKED(IDC_DOOR_NEXT, OnDoorNext)
ON_EN_KILLFOCUS(IDC_DOOR_OPEN_TIME, OnKillfocusDoorOpenTime)
ON_BN_CLICKED(IDC_DOOR_PREV, OnDoorPrev)
ON_EN_KILLFOCUS(IDC_DOOR_STAYS_OPEN, OnKillfocusDoorStaysOpen)
ON_BN_CLICKED(IDC_DOORS_OUT, OnDoorsOut)
ON_BN_CLICKED(IDC_LOAD_DOOR_MODEL, OnLoadDoorModel)
ON_BN_CLICKED(IDC_LOCK_DOOR, OnLockDoor)
ON_WM_TIMER()
ON_CBN_SELENDOK(IDC_DOOR_PULLDOWN, OnSelendokDoorPulldown)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_DOOR_CHANGE_NAME, OnDoorChangeName)
ON_BN_CLICKED(IDC_TRANSPARENCY, OnTransparency)
ON_WM_DESTROY()
ON_CBN_SELENDOK(IDC_DOOR_CLOSE_SOUND, OnSelendokDoorCloseSound)
ON_CBN_SELENDOK(IDC_DOOR_OPEN_SOUND, OnSelendokDoorOpenSound)
ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
ON_EN_KILLFOCUS(IDC_SCRIPTNAME, OnKillfocusScriptname)
ON_BN_CLICKED(IDC_DOOR_BLASTABLE, OnDoorBlastable)
ON_EN_KILLFOCUS(IDC_DOOR_HITPOINTS_EDIT, OnKillfocusDoorHitpointsEdit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldObjectsDoorDialog message handlers

#include "room.h"

// Makes sure a door model is ok. If not ok, brings up messagebox to tell the user
// Parameter:	handle - the handle for the polymodel
// Returns:		true if ok, else false
bool VerifyDoorModel(int handle) {
  poly_model *pm = GetPolymodelPointer(handle);
  int s;
  bool found_frontface = 0, found_shell = 0;

  for (s = 0; s < pm->n_models; s++) {
    bsp_info *sm = &pm->submodel[s];

    if (sm->flags & SOF_FRONTFACE) {

      if (sm->num_faces != 1) {
        OutrageMessageBox("Invalid door model: Frontface has %d faces; must have 1.", sm->num_faces);
        return 0;
      }

      if (sm->num_children != 0) {
        OutrageMessageBox("Invalid door model: Frontface cannot have submodels.");
        return 0;
      }

      found_frontface = 1;
    }

    if (sm->flags & SOF_SHELL) {

      if (sm->num_children != 0) {
        OutrageMessageBox("Invalid door model: Shell cannot have submodels.");
        return 0;
      }

      // check polygons in the shell.  we do this by copying the poly face into a room
      room check_room;
      face check_face;

      check_room.verts = sm->verts;
      check_room.faces = &check_face;

      for (int f = 0; f < sm->num_faces; f++) {
        polyface *polyface = &sm->faces[f];

        // copy polygon face into the room face
        check_face.num_verts = polyface->nverts;
        check_face.face_verts = polyface->vertnums;

        if (!ComputeFaceNormal(&check_room, 0)) {
          OutrageMessageBox("Invalid door model: Face %d in shell has bad normal.", f);
          return 0;
        }
      }

      found_shell = 1;
    }
  }

  if (!found_frontface) {
    OutrageMessageBox("Invalid door model: Missing Frontface.");
    return 0;
  }

  if (!found_shell) {
    OutrageMessageBox("Invalid door model: Missing Shell.");
    return 0;
  }

  return 1;
}

void CWorldObjectsDoorDialog::OnAddDoor() {
  char filename[256], pathname[256], dir[256], ext[32];
  char cur_name[100];
  int img_handle;
  int door_handle;
  int c = 1, finding_name = 1;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCSTR)filter, pathname, Current_model_dir, sizeof(Current_model_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadDoorImage(pathname, 0);
  ddio_SplitPath(pathname, dir, filename, ext);

  if (!VerifyDoorModel(img_handle)) {
    FreePolyModel(img_handle);
    return;
  }

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that model file.");
    return;
  }

  // Alloc a door and give a name not already taken by some other door

  door_handle = AllocDoor();

  while (finding_name) {
    if (c == 1)
      sprintf(cur_name, "%s", filename);
    else
      sprintf(cur_name, "%s%d", filename, c);
    if (FindDoorName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(Doors[door_handle].name, cur_name);

  Doors[door_handle].model_handle = img_handle;

  // Finally, save a local copy of the model/anim and alloc a tracklock
  mprintf(0, "Making a copy of this model locally...\n");

  std::filesystem::path destname = LocalModelsDir / Poly_models[Doors[door_handle].model_handle].name;
  cf_CopyFile(destname, pathname);

  mng_AllocTrackLock(cur_name, PAGETYPE_DOOR);

  D3EditState.current_door = door_handle;

  UpdateDialog();
}

#define NULL_NAME "<none>"

void CWorldObjectsDoorDialog::UpdateDialog() {
  CEdit *ebox;
  CButton *bbox;
  int n = D3EditState.current_door;
  char str[50];

  if (Num_doors < 1) {
    bbox = (CButton *)GetDlgItem(IDC_DOOR_NEXT);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_DOOR_PREV);
    bbox->EnableWindow(FALSE);

    return;
  } else {
    bbox = (CButton *)GetDlgItem(IDC_DOOR_NEXT);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_DOOR_PREV);
    bbox->EnableWindow(TRUE);
  }

  if (!Doors[n].used)
    n = D3EditState.current_door = GetNextDoor(n);

  //	ebox=(CEdit *) GetDlgItem (IDC_DOOR_NAME_EDIT);
  //	ebox->SetWindowText (Doors[n].name);

  bbox = (CButton *)GetDlgItem(IDC_TRANSPARENCY);
  bbox->SetCheck(Doors[n].flags & DF_SEETHROUGH);

  bool blastable = ((Doors[n].flags & DF_BLASTABLE) != 0);
  bbox = (CButton *)GetDlgItem(IDC_DOOR_BLASTABLE);
  bbox->SetCheck(blastable);

  ebox = (CEdit *)GetDlgItem(IDC_DOOR_MODEL_NAME_EDIT);
  ebox->SetWindowText(Poly_models[Doors[n].model_handle].name);

  ebox = (CEdit *)GetDlgItem(IDC_DOOR_OPEN_TIME);
  sprintf(str, "%f", Doors[n].total_open_time);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_DOOR_STAYS_OPEN);
  sprintf(str, "%f", Doors[n].total_time_open);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_CLOSE_TIME);
  sprintf(str, "%f", Doors[n].total_close_time);
  ebox->SetWindowText(str);

  // Update hitpoint editing controls
  GetDlgItem(IDC_DOOR_HITPOINTS_TEXT)->EnableWindow(blastable);
  ebox = (CEdit *)GetDlgItem(IDC_DOOR_HITPOINTS_EDIT);
  sprintf(str, "%d", Doors[n].hit_points);
  ebox->SetWindowText(str);
  ebox->EnableWindow(blastable);

  bbox = (CButton *)GetDlgItem(IDC_CHECKIN_DOOR);
  if (mng_FindTrackLock(Doors[n].name, PAGETYPE_DOOR) == -1) {
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_DOOR);
    bbox->EnableWindow(TRUE);
  } else {
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_DOOR);
    bbox->EnableWindow(FALSE);
  }

  SendDlgItemMessage(IDC_DOOR_PULLDOWN, CB_RESETCONTENT, 0, 0);

  for (int i = 0; i < MAX_DOORS; i++) {
    if (Doors[i].used)
      SendDlgItemMessage(IDC_DOOR_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Doors[i].name);
  }
  SendDlgItemMessage(IDC_DOOR_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Doors[n].name);

  // Update script
  ebox = (CEdit *)GetDlgItem(IDC_SCRIPTNAME);

  if (!Doors[n].module_name[0])
    ebox->SetWindowText("null");
  else
    ebox->SetWindowText(Doors[n].module_name);

  // Update sounds lists
  SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  for (int i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
  }
  if (Doors[n].open_sound == -1)
    SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  else
    SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Sounds[Doors[n].open_sound].name);

  SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  for (int i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
  }
  if (Doors[n].close_sound == -1)
    SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)NULL_NAME);
  else
    SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Sounds[Doors[n].close_sound].name);

  UpdateDoorView();
}

#define NUM_ANIM_FRAMES 30

void CWorldObjectsDoorDialog::UpdateDoorView(void) {
  int n = D3EditState.current_door;
  CWnd *doorwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  static int frame = 0, spin_frame = 0;
  static int last_door = -1;
  static int last_model_handle = -1;
  static int door_dir = 0;

  if (Num_doors < 1)
    return;

  if (door_dir == 0) {
    frame++;
    if (frame == NUM_ANIM_FRAMES) {
      frame = NUM_ANIM_FRAMES - 1;
      door_dir = 1;
    }
  } else {
    frame--;
    if (frame == -1) {
      frame = 0;
      door_dir = 0;
    }
  }

  doorwnd = GetDlgItem(IDC_DOORVIEW);
  doorwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  if (last_door != n || last_model_handle != Doors[n].model_handle) {
    Desktop_surf->clear(rect.left, rect.top, w, h);
    last_door = n;
    last_model_handle = Doors[n].model_handle;
  }

  bm_handle = GetDoorImage(n);

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

  m_DoorSurf.create(128, 128, BPP_16);
  grViewport *vport = new grViewport(&m_DoorSurf);
  StartEditorFrame(vport, &view_vector, &id_matrix, D3_DEFAULT_ZOOM);
  DrawPolygonModel(&zero_vector, &rot_matrix, bm_handle, norm_angles, 0, 1.0, 1.0, 1.0);
  EndEditorFrame();

  x = rect.left + ((rect.right - rect.left) / 2) - m_DoorSurf.width() / 2;
  y = rect.top + ((rect.bottom - rect.top) / 2) - m_DoorSurf.height() / 2;
  Desktop_surf->blt(x, y, &m_DoorSurf);

  delete vport;
  m_DoorSurf.free();
}

void CWorldObjectsDoorDialog::OnCheckinDoor() {
  int n = D3EditState.current_door;
  mngs_Pagelock temp_pl;
  int r;

  if (Num_doors < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure we own this door
  strcpy(temp_pl.name, Doors[n].name);
  temp_pl.pagetype = PAGETYPE_DOOR;

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

      if (!mng_ReplacePage(Doors[n].name, Doors[n].name, n, PAGETYPE_DOOR, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this door anim/model to the network for all
        std::filesystem::path srcname = LocalModelsDir / Poly_models[Doors[n].model_handle].name;
        std::filesystem::path destname = NetModelsDir / Poly_models[Doors[n].model_handle].name;

        cf_CopyFile(destname, srcname);

        OutrageMessageBox("Door checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Doors[n].name, PAGETYPE_DOOR, 1);

        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Doors[n].name, PAGETYPE_DOOR);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }

  mng_EraseLocker();
}

void CWorldObjectsDoorDialog::OnKillfocusCloseTime() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_door;

  ebox = (CEdit *)GetDlgItem(IDC_CLOSE_TIME);
  ebox->GetWindowText(str, 20);

  Doors[n].total_close_time = atof(str);
}

void CWorldObjectsDoorDialog::OnDeleteDoor() {
  int answer, tl;
  mngs_Pagelock pl;
  int n = D3EditState.current_door;

  if (Num_doors < 1)
    return;

  // Check to see if we even have it locked
  if ((tl = mng_FindTrackLock(Doors[n].name, PAGETYPE_DOOR)) == -1) {
    OutrageMessageBox("This door is not yours to delete.  Lock first.");
    return;
  }

  // Make sure its to be deleted
  answer = MessageBox("Are you sure you want to delete this door?", Doors[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Doors[n].name);
  pl.pagetype = PAGETYPE_DOOR;

  // Check to see if this is a local door only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(Doors[n].name, PAGETYPE_DOOR, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else // if its network, delete it from both the net and local drives
  {

    mng_FreeTrackLock(tl);
    mng_DeletePage(Doors[n].name, PAGETYPE_DOOR, 1);
    mng_DeletePage(Doors[n].name, PAGETYPE_DOOR, 0);

    mng_DeletePagelock(Doors[n].name, PAGETYPE_DOOR);
  }

  // Advance to the next door
  D3EditState.current_door = GetNextDoor(n);

  FreePolyModel(Doors[n].model_handle);
  FreeDoor(n);
  mng_EraseLocker();

  OutrageMessageBox("Door deleted.");
  UpdateDialog();
}

// Gets a name from the user, making sure it's unique
// Returns true if got new name, false if cancelled.
// the data in buf not changed if cancel is pressed
bool InputDoorName(char *buf, int len, char *title, char *prompt, CWnd *wnd) {
  char *tempbuf = (char *)mem_malloc(len);

  strcpy(tempbuf, buf);

try_again:

  if (!InputString(tempbuf, len, title, prompt, wnd)) {
    mem_free(tempbuf);
    return 0;
  }

  if (FindDoorName(tempbuf) != -1) {
    OutrageMessageBox("The name you specified is already in use.  Enter another name.");
    goto try_again;
  }

  strcpy(buf, tempbuf);
  mem_free(tempbuf);

  return 1;
}

void CWorldObjectsDoorDialog::OnDoorChangeName() {
  int n = D3EditState.current_door;
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this door locked, if not reset name and bail
  int p = mng_FindTrackLock(Doors[n].name, PAGETYPE_DOOR);
  if (p == -1) {
    OutrageMessageBox("You must lock this door if you wish to change its name.");
    return;
  }

  // Get new name
  strcpy(name, Doors[n].name);
  if (!InputDoorName(name, sizeof(name), "Door name", "Enter a new name for this door:", this))
    return;

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Doors[n].name);
  pl.pagetype = PAGETYPE_DOOR;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Doors[n].name, name, PAGETYPE_DOOR);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Doors[n].name);
    strcpy(Doors[n].name, name);
    mng_ReplacePage(oldname, Doors[n].name, n, PAGETYPE_DOOR, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Doors[n].name, name);
  UpdateDialog();
  mng_EraseLocker();
}

void CWorldObjectsDoorDialog::OnDoorNext() {
  D3EditState.current_door = GetNextDoor(D3EditState.current_door);
  UpdateDialog();
}

void CWorldObjectsDoorDialog::OnKillfocusDoorOpenTime() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_door;

  ebox = (CEdit *)GetDlgItem(IDC_DOOR_OPEN_TIME);
  ebox->GetWindowText(str, 20);

  Doors[n].total_open_time = atof(str);
}

void CWorldObjectsDoorDialog::OnDoorPrev() {
  D3EditState.current_door = GetPrevDoor(D3EditState.current_door);
  UpdateDialog();
}

void CWorldObjectsDoorDialog::OnKillfocusDoorStaysOpen() {
  // TODO: Add your control notification handler code here
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_door;

  ebox = (CEdit *)GetDlgItem(IDC_DOOR_STAYS_OPEN);
  ebox->GetWindowText(str, 20);

  Doors[n].total_time_open = atof(str);
}

void CWorldObjectsDoorDialog::OnDoorsOut() {
  char str[10000];
  int total = 0;

  mng_DisplayLockList(TableUser);

  sprintf(str, "User %s has these doors held locally:\n\n", TableUser);
  for (int i = 0; i < MAX_TRACKLOCKS; i++) {

    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_DOOR) {
      char temp[90];

      sprintf(temp, "%s", GlobalTrackLocks[i].name);
      strcat(str, temp);
      strcat(str, "\n");
      total++;
    }
  }

  if (total != 0) {
    // Display that string
    MessageBox(str, "Doors", MB_OK);
  }
}

void CWorldObjectsDoorDialog::OnLoadDoorModel() {
  char filename[255];
  int img_handle;
  int door_handle;
  int c = 1, finding_name = 1;
  int model = 0;

  // Get the filename of the representing image

  CString filter = "Descent III files (*.pof,*.oof)|*.pof;*.oof||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_model_dir, sizeof(Current_model_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  img_handle = LoadDoorImage(filename, 0);

  if (img_handle < 0) {
    OutrageMessageBox("Couldn't open that animation/model file.");
    return;
  }

  door_handle = D3EditState.current_door;

  Doors[door_handle].model_handle = img_handle;

  // Finally, save a local copy of the model
  std::filesystem::path curname = LocalModelsDir / Poly_models[Doors[door_handle].model_handle].name;
  cf_CopyFile(curname, filename);

  UpdateDialog();
}

void CWorldObjectsDoorDialog::OnLockDoor() {
  int n = D3EditState.current_door;
  mngs_Pagelock temp_pl;
  mngs_door_page doorpage;
  int r;

  if (Num_doors < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, Doors[n].name);
  temp_pl.pagetype = PAGETYPE_DOOR;

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
      if (mng_FindSpecificDoorPage(temp_pl.name, &doorpage)) {
        if (mng_AssignDoorPageToDoor(&doorpage, n)) {
          if (!mng_ReplacePage(Doors[n].name, Doors[n].name, n, PAGETYPE_DOOR, 1)) {
            OutrageMessageBox("There was problem writing that page locally!");
            mng_EraseLocker();
            return;
          }
          OutrageMessageBox("Door locked.");
        } else
          OutrageMessageBox(
              "There was a problem loading this door.  You might encounter problems in dealing with it.  Good luck!");

        mng_AllocTrackLock(Doors[n].name, PAGETYPE_DOOR);

        UpdateDialog();
      } else
        OutrageMessageBox("Couldn't find that door in the table file!");
    }
  }
  mng_EraseLocker();
}

BOOL CWorldObjectsDoorDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  CWnd::SetTimer(1, 50, NULL);

  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorldObjectsDoorDialog::OnTimer(UINT nIDEvent) {
  UpdateDoorView();

  CDialog::OnTimer(nIDEvent);
}

// When closing, save all our checked out doors locally so we know
// what stuff to flag as "checked out" the next time we start up
void CWorldObjectsDoorDialog::SaveDoorsOnClose() {
  int i, t;

  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_DOOR) {
      t = FindDoorName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);
      mng_ReplacePage(Doors[t].name, Doors[t].name, t, PAGETYPE_DOOR, 1);
    }
  }
}

BOOL CWorldObjectsDoorDialog::DestroyWindow() {
  SaveDoorsOnClose();
  return CDialog::DestroyWindow();
}

void CWorldObjectsDoorDialog::OnSelendokDoorPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_DOOR_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_DOOR_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindDoorName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted door list, but probably nothing.");
    UpdateDialog();
  }

  D3EditState.current_door = i;
  UpdateDialog();
}

BOOL CWorldObjectsDoorDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  WinHelp(HID_DOORSDLG, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CWorldObjectsDoorDialog::OnTransparency() {
  int n = D3EditState.current_door;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_TRANSPARENCY);

  if (btn->GetCheck())
    Doors[n].flags |= DF_SEETHROUGH;
  else
    Doors[n].flags &= ~DF_SEETHROUGH;
}

void CWorldObjectsDoorDialog::OnDestroy() {
  CDialog::OnDestroy();

  ObjReInitAll();
}

void CWorldObjectsDoorDialog::OnSelendokDoorOpenSound() {
  int cur;
  char name[200];
  int n = D3EditState.current_door;

  cur = SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_DOOR_OPEN_SOUND, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Doors[n].open_sound = FindSoundName(name);
}

void CWorldObjectsDoorDialog::OnSelendokDoorCloseSound() {
  int cur;
  char name[200];
  int n = D3EditState.current_door;

  cur = SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_DOOR_CLOSE_SOUND, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Doors[n].close_sound = FindSoundName(name);
}

void CWorldObjectsDoorDialog::OnBrowse() {
  CString filter = "D3 Compiled Scripts (*.dll)|*.dll||";

  char filename[_MAX_PATH];
  char pathname[_MAX_PATH], name[_MAX_PATH];
  strcpy(pathname, LocalScriptDir);

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, pathname, sizeof(pathname)))
    return;

  ddio_SplitPath(filename, NULL, name, NULL);
  sprintf(filename, "%s.dll", name);

  int n = D3EditState.current_door;

  strcpy(Doors[n].module_name, filename);

  UpdateDialog();
}

void CWorldObjectsDoorDialog::OnKillfocusScriptname() {
  char str[MAX_MODULENAME_LEN];

  ((CEdit *)GetDlgItem(IDC_SCRIPTNAME))->GetWindowText(str, MAX_MODULENAME_LEN);

  strcpy(Doors[D3EditState.current_door].module_name, str);
  UpdateDialog();
}

void CWorldObjectsDoorDialog::OnDoorBlastable() {
  int n = D3EditState.current_door;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_DOOR_BLASTABLE);

  if (btn->GetCheck())
    Doors[n].flags |= DF_BLASTABLE;
  else
    Doors[n].flags &= ~DF_BLASTABLE;

  UpdateDialog();
}

void CWorldObjectsDoorDialog::OnKillfocusDoorHitpointsEdit() {
  char str[256];

  int n = D3EditState.current_door;
  CEdit *ebox = (CEdit *)GetDlgItem(IDC_DOOR_HITPOINTS_EDIT);

  ebox->GetWindowText(str, sizeof(str));

  Doors[n].hit_points = atoi(str);

  UpdateDialog();
}
