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

 * $Logfile: /DescentIII/Main/editor/ObjectDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Object keypad dialog
 *
 * $Log: not supported by cvs2svn $
 *
 * 46    5/08/99 1:39a Matt
 * Added a function to delete all objects of a certain type, and support
 * for placing and attaching groups to the terrain.
 *
 * 45    4/05/99 3:34p Matt
 * Cleaned up player start flags
 *
 * 44    4/02/99 12:58p Chris
 * Change object now preserves names
 *
 * 43    3/27/99 12:52p Chris
 * The editor object placement code now allows objects to be pushed into
 * wall (when a toggle box is checked)
 *
 * 42    2/18/99 2:09p Luke
 * Checking in for Matt
 *
 * 41    2/05/99 1:25p Matt
 * Show more info on the status line when an object is selected
 *
 * 40    2/03/99 1:58a Matt
 * Fixed small bug
 *
 * 39    2/03/99 1:20a Matt
 * Made the object combo box on the object tab sort, and replaced the
 * listbox of pictures with a big picture of the current item.
 *
 * 38    1/27/99 11:03a Samir
 * added rotate 90 button to object dialog.
 *
 * 37    1/19/99 6:53p Matt
 * Fixed a problem when the viewer was instantaneously moved from inside
 * to ourside or vise-versa.
 *
 * 36    1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 35    10/22/98 11:01a Chris
 * Added object regrounding
 *
 * 34    10/08/98 7:17p Chris
 * Added object swap types
 *
 * 33    8/24/98 12:24p Jason
 * added waypoints and player start position flags
 *
 * 32    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 31    5/18/98 2:56p Matt
 * Added code to readjust all ground object (for after the terrain has
 * moved).
 *
 * 30    5/06/98 4:02p Sean
 *
 * 29    5/06/98 1:55p Sean
 *
 * 28    5/06/98 1:49p Sean
 * fixed dumb bug with my last rev
 *
 * 27    5/06/98 12:34p Jason
 * Added next object in terrain stuff
 *
 * 26    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 25    3/30/98 6:20p Matt
 * Renamed ResetObject() to be ObjReInitAll()
 *
 * 24    2/24/98 11:19a Samir
 * objects should look better in listbox.
 *
 * 23    2/05/98 11:25a Samir
 * Maybe this will work to fix ListNextItem problems.
 *
 * 22    1/30/98 6:05p Matt
 * Got Next Object in object keypad working, and made a routine to set the
 * current editor object.
 *
 * 21    1/18/98 9:07p Matt
 * New parms for ResetObjects()
 *
 * 20    1/07/98 6:39p Jason
 * Fixed player object number stuff
 *
 * 19    12/19/97 11:26a Samir
 * Oops.
 *
 * 18    12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 17    12/01/97 3:20p Samir
 * No Int3 when trying to place objects outside the mine.
 *
 * 16    9/17/97 1:26p Samir
 * BIG SEGMENT RIPOUT
 *
 * 15    9/15/97 11:55a Samir
 * Fixed playership adding.
 *
 * 14    9/02/97 3:02p Samir
 * fixed bug.  accidentally set wrong variable for axis movement.
 *
 * 13    8/29/97 2:49p Samir
 * Added new object movement features.
 *
 * 12    8/25/97 7:39p Samir
 * Using new GrListBox from old editorPictListBox
 *
 * 11    8/18/97 12:09p Matt
 * Fixed a stupid bug, and added some error checking and handling
 *
 * 10    8/13/97 9:50a Matt
 * Changed highlighted object to draw with magenta box around it
 *
 * 9     8/12/97 10:57p Matt
 * Made object page work for the generic object  types (robot, powerup,
 * building, clutter)
 *
 * 8     8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 7     8/06/97 11:11a Mark
 * Took out Int3 for 'untested' draw code in DrawItem. - Samir
 *
 * 6     7/24/97 7:18p Matt
 * Cleaned up code that draws robots & powerups
 *
 * 5     7/24/97 6:11p Matt
 * Created symbolic constant for default zoom, and used it every place
 * that specifies zoom
 *
 * 4     7/24/97 4:21p Matt
 * On object keypad, only list this object types the the designer can
 * place
 *
 * 3     7/24/97 2:54p Matt
 * Got rid of some member variables that kept track of current robot,
 * powerup, & object type, and used variables in D3EditState instead.
 *
 * 2     7/22/97 7:08p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 35    6/04/97 11:56a Samir
 * Added PowerupProp Dialog.
 *
 * 34    6/03/97 4:55p Mark
 *
 * 34	6/03/97	4:50p	Jeff
 *	added Context Sensitive Help
 *
 * 33    5/01/97 12:33p Jason
 * added reset objects function
 *
 * 32    5/01/97 11:16a Samir
 * No Int3  in Object type selection
 *
 * 26    4/02/97 6:25p Samir
 * Fixed screwup with decrease heading function.
 *
 * 25    4/02/97 12:22p Samir
 * Fixed object box scroll problems by keeping an array of item starts for
 * each obj_type and fixed problem of placing a bad robot (door) when
 * first placing objects.
 *
 * 14    3/13/97 6:17p Jason
 * changed door/polymodel prototype
 *
 * 13    3/03/97 5:56p Jason
 * changed function name to be more generic
 * GetPowerupBitmap -> GetPowerupImage
 *
 * 12    2/26/97 3:35p Mark
 *
 * 11    2/25/97 4:35p Samir
 * Selecting from combo box sets pictoral list box selection.
 *
 * 10    2/21/97 6:25p Samir
 * Object palette works (shitty scaling of powerups.)
 *
 * 9     2/20/97 4:26p Mark
 *
 * 8     2/19/97 5:26p Samir
 * When setting focus on objID listbox, update its contents.
 *
 * 7     2/19/97 2:16p Samir
 * Added RunKeypadFunction handler.
 *
 * 6     2/18/97 12:47p Samir
 * Able to select object types and ids from keypad.
 *
 * 5     2/17/97 6:19p Samir
 * Added place object and move left,right,for, back functionality.
 *
 * 4     1/27/97 11:38a Samir
 * Added horizontal scrolling of keypad modeless dialog.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "editor.h"
#include "ObjectDialog.h"
#include "ObjMoveManager.h"

#include "HObject.h"
#include "polymodel.h"

#include "object.h"
#include "ship.h"
#include "objinfo.h"
#include "multi.h"
#include "objinit.h"
#include "room.h"
#include "d3edit.h"
#include "physics.h"
#include "door.h"
#include "mem.h"

#include "PowerupPropDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

// List of object types & names for the editor
int edit_object_types[] = {OBJ_ROBOT, OBJ_POWERUP, OBJ_BUILDING, OBJ_CLUTTER, OBJ_PLAYER};
char *edit_objtype_names[] = {"Robot", "Powerup", "Building", "Clutter", "Player ship"};

int Swap_source_id = -1;
int Swap_dest_id = -1;
int Reground_id = -1;

bool f_allow_objects_to_be_pushed_through_walls = false;

void DrawItemModel(grHardwareSurface *surf, int model_num);

#define NUM_EDIT_OBJTYPES (sizeof(edit_object_types) / sizeof(*edit_object_types))

/////////////////////////////////////////////////////////////////////////////
// CObjectDialog dialog

CObjectDialog::CObjectDialog(CWnd *pParent /*=NULL*/) : CKeypadDialog(CObjectDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CObjectDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CObjectDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CObjectDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

void CObjectDialog::UpdateIDList() { InitObjIDComboBox((CComboBox *)GetDlgItem(IDC_COMBO_OBJID)); }

void CObjectDialog::PlaceObject() { OnObjectPlaceObject(); }

void CObjectDialog::DeleteObject() { OnObjPadDelobj(); }

BEGIN_MESSAGE_MAP(CObjectDialog, CDialog)
//{{AFX_MSG_MAP(CObjectDialog)
ON_WM_SIZE()
ON_WM_VSCROLL()
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_OBJPAD_PLACEOBJ, OnObjectPlaceObject)
ON_CBN_SELCHANGE(IDC_COMBO_OBJTYPE, OnSelchangeComboObjType)
ON_CBN_SELCHANGE(IDC_COMBO_OBJID, OnSelchangeComboObjID)
ON_BN_CLICKED(IDC_OBJ_DELOBJ, OnObjPadDelobj)
ON_BN_CLICKED(IDC_OBJPAD_NEXTOBJ, OnObjpadNextobj)
ON_CBN_SETFOCUS(IDC_COMBO_OBJID, OnSetfocusComboObjID)
ON_BN_CLICKED(IDC_OBJECTPAD_GROUP, OnObjectpadGroup)
ON_BN_CLICKED(IDC_OBJ_CONT_PREVIEW, OnObjContPreview)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_OBJPAD_FLAGOBJMULTI, OnObjpadFlagobjmulti)
ON_BN_CLICKED(IDC_OBJPAD_FLIPOBJ, OnObjpadFlipobj)
ON_BN_CLICKED(IDC_OBJPAD_SETDEFAULT, OnObjpadSetdefault)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_RESET_OBJECTS, OnResetObjects)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_OBJPAD_PROPERTIES, OnObjpadProperties)
ON_CBN_SELCHANGE(IDC_COORDSYS_SELECT, OnSelChangeCoordSysSelect)
ON_BN_CLICKED(IDC_OBJMOVEX, OnObjmoveX)
ON_BN_CLICKED(IDC_OBJMOVEY, OnObjmoveY)
ON_BN_CLICKED(IDC_OBJMOVEXY, OnObjmoveXY)
ON_BN_CLICKED(IDC_OBJMOVEZ, OnObjmoveZ)
ON_BN_CLICKED(IDC_OBJMOVEP, OnObjmoveP)
ON_BN_CLICKED(IDC_OBJMOVEH, OnObjmoveH)
ON_BN_CLICKED(IDC_OBJMOVEB, OnObjmoveB)
ON_BN_CLICKED(IDC_OBJMOVEPH, OnObjmovePH)
ON_BN_CLICKED(IDC_OBJPAD_RESET_ALL_OBJ_HEIGHTS, OnObjpadResetAllObjHeights)
ON_BN_CLICKED(IDC_OBJPAD_RESET_CUROBJ_HEIGHT, OnObjpadResetCurobjHeight)
ON_BN_CLICKED(IDC_PREV_START_POSITON, OnPrevStartPositon)
ON_BN_CLICKED(IDC_NEXT_START_POS, OnNextStartPos)
ON_BN_CLICKED(IDC_JUMP_TO_START_POS, OnJumpToStartPos)
ON_BN_CLICKED(IDC_RED_CHECK, OnRedCheck)
ON_BN_CLICKED(IDC_BLUE_CHECK, OnBlueCheck)
ON_BN_CLICKED(IDC_GREEN_CHECK, OnGreenCheck)
ON_BN_CLICKED(IDC_YELLOW_CHECK, OnYellowCheck)
ON_CBN_SELENDOK(IDC_SWAP_SOURCE_COMBO, OnSelendokSwapSourceCombo)
ON_CBN_SELENDOK(IDC_SWAP_DEST_COMBO, OnSelendokSwapDestCombo)
ON_BN_CLICKED(IDC_OBJECT_SWAP_BUTTON, OnObjectSwapButton)
ON_CBN_SELENDOK(IDC_REGROUND_COMBO, OnSelendokRegroundCombo)
ON_BN_CLICKED(IDC_REGROUND_BUTTON, OnRegroundButton)
ON_BN_CLICKED(IDC_OBJ_ROT90, OnObjRot90)
ON_BN_CLICKED(IDC_OBJECT_PUSHTHROUGHWALLS, OnObjectPushthroughwalls)
ON_BN_CLICKED(IDC_OBJPAD_DELETEALL, OnObjpadDeleteAll)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Current player isn't saved, so just keep it locally
int current_player = 0;

// Sets the current index of the given type
void SetCurrentIndex(int index) {
  switch (D3EditState.current_obj_type) {
  case OBJ_ROBOT:
    D3EditState.current_robot = index;
    break;
  case OBJ_POWERUP:
    D3EditState.current_powerup = index;
    break;
  case OBJ_CLUTTER:
    D3EditState.current_clutter = index;
    break;
  case OBJ_BUILDING:
    D3EditState.current_building = index;
    break;
  case OBJ_PLAYER:
    current_player = index;
    break;
  default:
    Int3();
  }
}

// Returns the current index of the given type
int GetCurrentIndex() {
  int type = D3EditState.current_obj_type;
  int current;

  switch (type) {
  case OBJ_ROBOT:
    current = D3EditState.current_robot;
    break;
  case OBJ_POWERUP:
    current = D3EditState.current_powerup;
    break;
  case OBJ_CLUTTER:
    current = D3EditState.current_clutter;
    break;
  case OBJ_BUILDING:
    current = D3EditState.current_building;
    break;
  case OBJ_PLAYER:
    return current_player;
    break;
  default:
    Int3();
  }

  if (Object_info[current].type != type) { // current is of wrong type
    current = GetObjectID(type);           //...so get a new current
    SetCurrentIndex(current);
  }

  return current;
}

/////////////////////////////////////////////////////////////////////////////
// CObjectDialog message handlers

void CObjectDialog::InitObjIDComboBox(CComboBox *box) {
  int i, first, n;

  box->ResetContent();

  // Add names of object IDs of current object type
  switch (D3EditState.current_obj_type) {
  case OBJ_ROBOT:
  case OBJ_POWERUP:
  case OBJ_CLUTTER:
  case OBJ_BUILDING:
    first = GetObjectID(D3EditState.current_obj_type);

    if (first == -1)
      break;

    if (GetCurrentIndex() == -1)
      SetCurrentIndex(first);

    n = first;
    do {
      int index = box->AddString(Object_info[n].name);
      box->SetItemData(index, n);

      if (n == GetCurrentIndex())
        box->SetCurSel(index);

      n = GetNextObjectID(n);
    } while (n != first);

    break;

  case OBJ_PLAYER:
    for (i = 0; i < MAX_SHIPS; i++) {
      if (Ships[i].used) {
        int index = box->AddString(Ships[i].name);
        box->SetItemData(index, i);
        if (i == D3EditState.current_ship)
          box->SetCurSel(index);
      }
    }
    break;
  }
}

void CObjectDialog::InitObjTypeComboBox(CComboBox *box) {
  box->ResetContent();

  for (int i = 0; i < NUM_EDIT_OBJTYPES; i++) {
    if (box->AddString(edit_objtype_names[i]) < 0)
      Int3();
    if (edit_object_types[i] == D3EditState.current_obj_type)
      box->SetCurSel(i);
  }
}

BOOL CObjectDialog::OnInitDialog() {
  CComboBox *box;
  int current;

  CDialog::OnInitDialog();

  // Init types combo box
  InitObjTypeComboBox((CComboBox *)GetDlgItem(IDC_COMBO_OBJTYPE));

  // Init IDs combo box
  InitObjIDComboBox((CComboBox *)GetDlgItem(IDC_COMBO_OBJID));

  // Get index of current item
  current = GetCurrentIndex();
  ASSERT(current != -1);

  //	set selection in object movement combobox and move axis.
  box = (CComboBox *)GetDlgItem(IDC_COORDSYS_SELECT);
  if (D3EditState.object_move_mode == REL_OBJECT)
    box->SelectString(-1, "Local");
  else if (D3EditState.object_move_mode == REL_VIEWER)
    box->SelectString(-1, "Viewer");
  else {
    D3EditState.object_move_mode = REL_OBJECT;
    box->SelectString(-1, "Local");
  }

  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);

  CButton *btn = NULL;

  switch (D3EditState.object_move_axis) {
  case OBJMOVEAXIS_X:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEX);
    break;
  case OBJMOVEAXIS_Y:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEY);
    break;
  case OBJMOVEAXIS_Z:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEZ);
    break;
  case OBJMOVEAXIS_XY:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEXY);
    break;
  case OBJMOVEAXIS_P:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEP);
    break;
  case OBJMOVEAXIS_H:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEH);
    break;
  case OBJMOVEAXIS_B:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEB);
    break;
  case OBJMOVEAXIS_PH:
    btn = (CButton *)GetDlgItem(IDC_OBJMOVEPH);
    break;

  default:
    Int3(); // THIS SHOULD NEVER HAPPEN - samir
  }

  btn->SetCheck(1);

  m_current_start_pos = 0;
  UpdateDialog();

  //	Done.
  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CObjectDialog::OnDestroy() { CDialog::OnDestroy(); }

void CObjectDialog::OnSize(UINT nType, int cx, int cy) { CKeypadDialog::OnSize(nType, cx, cy); }

void CObjectDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  CKeypadDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CObjectDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  CKeypadDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CObjectDialog::OnPaint() {
  CPaintDC dc(this); // device context for painting

  if (!m_Active)
    return;

  UpdateIDList(); // this is here to update the object ids in case of any changes

  ASSERT(GetCurrentIndex() != -1);

  // Draw picture of current item
  DrawPicture(GetDlgItem(IDC_OBJ_PALETTE));
}

void CObjectDialog::OnLButtonDown(UINT nFlags, CPoint point) { CDialog::OnLButtonDown(nFlags, point); }

void CObjectDialog::UpdateDialog() {
  CEdit *box;
  char str[255];
  int cur = m_current_start_pos;
  int i;

  sprintf(str, "Current start position: %d", cur);
  box = (CEdit *)GetDlgItem(IDC_START_POS_TEXT);
  box->SetWindowText(str);

  CheckDlgButton(IDC_RED_CHECK, Players[cur].startpos_flags & PSPF_RED);
  CheckDlgButton(IDC_BLUE_CHECK, Players[cur].startpos_flags & PSPF_BLUE);
  CheckDlgButton(IDC_GREEN_CHECK, Players[cur].startpos_flags & PSPF_GREEN);
  CheckDlgButton(IDC_YELLOW_CHECK, Players[cur].startpos_flags & PSPF_YELLOW);

  SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_RESETCONTENT, 0, 0);
  SendDlgItemMessage(IDC_REGROUND_COMBO, CB_RESETCONTENT, 0, 0);

  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE) {
      SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[i].name);
      SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[i].name);
      SendDlgItemMessage(IDC_REGROUND_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Object_info[i].name);
    }
  }

  if (Swap_source_id >= 0 && Swap_source_id < MAX_OBJECT_IDS && Object_info[Swap_source_id].type != OBJ_NONE)
    SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Object_info[Swap_source_id].name);
  else
    SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "None");

  if (Swap_dest_id >= 0 && Swap_dest_id < MAX_OBJECT_IDS && Object_info[Swap_dest_id].type != OBJ_NONE)
    SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Object_info[Swap_dest_id].name);
  else
    SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "None");

  if (Reground_id >= 0 && Reground_id < MAX_OBJECT_IDS && Object_info[Reground_id].type != OBJ_NONE)
    SendDlgItemMessage(IDC_REGROUND_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Object_info[Reground_id].name);
  else
    SendDlgItemMessage(IDC_REGROUND_COMBO, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR) "None");
}

void CObjectDialog::DrawPicture(CWnd *wnd) {
  RECT box_rect;
  int width, height, model_num;
  grHardwareSurface hw_surf;

  if (!Editor_active)
    return;

  //	initialize graphic objects
  wnd->GetClientRect(&box_rect);

  width = box_rect.right - box_rect.left;
  height = box_rect.bottom - box_rect.top;

  Desktop_surf->attach_to_window((unsigned)wnd->m_hWnd);

  hw_surf.create(width, height, BPP_16);

  switch (D3EditState.current_obj_type) {
  case OBJ_CLUTTER:
  case OBJ_BUILDING:
  case OBJ_POWERUP:
  case OBJ_ROBOT:
    model_num = GetObjectImage(GetCurrentIndex());
    break;
  case OBJ_PLAYER:
    model_num = GetShipImage(GetCurrentIndex());
    break;
  default:
    Int3();
  }

  DrawItemModel(&hw_surf, model_num);
}

//	Keypad functions!

void CObjectDialog::OnObjmoveX() {
  D3EditState.object_move_axis = OBJMOVEAXIS_X;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmoveY() {
  D3EditState.object_move_axis = OBJMOVEAXIS_Y;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmoveXY() {
  D3EditState.object_move_axis = OBJMOVEAXIS_XY;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmoveZ() {
  D3EditState.object_move_axis = OBJMOVEAXIS_Z;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmoveP() {
  D3EditState.object_move_axis = OBJMOVEAXIS_P;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmoveH() {
  D3EditState.object_move_axis = OBJMOVEAXIS_H;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmoveB() {
  D3EditState.object_move_axis = OBJMOVEAXIS_B;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

void CObjectDialog::OnObjmovePH() {
  D3EditState.object_move_axis = OBJMOVEAXIS_PH;
  ObjMoveManager.SetMoveAxis(D3EditState.object_move_axis);
}

int CObjectDialog::GetFreePlayerIndex() {
  uint8_t slots[MAX_NET_PLAYERS];

  memset(slots, 0, MAX_NET_PLAYERS);

  for (int i = 0; i <= Highest_object_index; i++) {
    if (Objects[i].type == OBJ_PLAYER) {
      // Get Jason if these asserts fail
      ASSERT(slots[Objects[i].id] == 0);
      ASSERT(Objects[i].id < MAX_NET_PLAYERS);

      slots[Objects[i].id] = 1;
    }
  }

  for (i = 0; i < MAX_NET_PLAYERS; i++) {
    if (slots[i] == 0) {
      mprintf(0, "Making new ship with id of %d...\n", i);
      return i;
    }
  }

  return -1;
}

void CObjectDialog::OnObjectPlaceObject() {
  int objid = -1;

  if (D3EditState.current_obj_type == OBJ_PLAYER) {
    objid = GetFreePlayerIndex();
    if (objid == -1) {
      mprintf(0, "No more player slots!  You already have %d players in this level!\n", MAX_NET_PLAYERS);
      return;
    }

  } else
    objid = GetCurrentIndex();

  ASSERT(objid > -1);

  if (!HObjectPlace(D3EditState.current_obj_type, objid)) {
    mprintf(0, "Attempt to place object outside mine failed!\n");
  }
}

void CObjectDialog::OnSelchangeComboObjType() {
  //	make sure to save the old item start value.
  int old_obj_type = D3EditState.current_obj_type;

  D3EditState.current_obj_type = edit_object_types[((CComboBox *)GetDlgItem(IDC_COMBO_OBJTYPE))->GetCurSel()];
  InitObjIDComboBox((CComboBox *)GetDlgItem(IDC_COMBO_OBJID));
  ASSERT(GetCurrentIndex() != -1);

  // Draw picture of current item
  DrawPicture(GetDlgItem(IDC_OBJ_PALETTE));
}

void CObjectDialog::OnSelchangeComboObjID() {
  CComboBox *box = (CComboBox *)GetDlgItem(IDC_COMBO_OBJID);

  switch (D3EditState.current_obj_type) {
  case OBJ_ROBOT:
  case OBJ_POWERUP:
  case OBJ_BUILDING:
  case OBJ_CLUTTER: {
    int id = box->GetItemData(box->GetCurSel());
    ASSERT(Object_info[id].type == D3EditState.current_obj_type);
    SetCurrentIndex(id);
    break;
  }

  case OBJ_PLAYER: {
    char text[32];
    int i, j;
    box->GetLBText(box->GetCurSel(), text);
    j = 0;
    for (i = 0; i < MAX_SHIPS; i++)
      if (Ships[i].used && (stricmp(text, Ships[i].name) == 0)) {
        j++;
        break;
      }

    ASSERT(i < MAX_SHIPS);
    SetCurrentIndex(i);
    break;
  }
  }

  // Draw picture of current item
  DrawPicture(GetDlgItem(IDC_OBJ_PALETTE));
}

void CObjectDialog::OnObjPadDelobj() { HObjectDelete(); }

// Set the current object
void SelectObject(int objnum) {
  char *type_name, *obj_name;
  char *id_name = NULL;

  ASSERT(objnum != -1);

  Cur_object_index = objnum;

  object *objp = &Objects[objnum];
  type_name = Object_type_names[objp->type];
  obj_name = objp->name ? objp->name : "<none>";

  if (IS_GENERIC(objp->type))
    id_name = Object_info[objp->id].name;
  else if (objp->type == OBJ_DOOR)
    id_name = Doors[objp->id].name;

  if (id_name)
    EditorStatus("Object %d selected. Type = %s:%s,  Name = %s", objnum, type_name, id_name, obj_name);
  else
    EditorStatus("Object %d selected. Type = %s,  Name = %s", objnum, type_name, obj_name);

  State_changed = 1;
}

void CObjectDialog::OnObjpadNextobj() {
  int next;

  // If on the terrain, advance to the next object
  if (Editor_view_mode == VM_TERRAIN && OBJECT_OUTSIDE(&Objects[Cur_object_index])) {
    next = -1;
    int done = 0;
    for (int i = Cur_object_index + 1; i <= Highest_object_index && !done; i++) {
      object *obj = &Objects[i];

      if (obj->type != OBJ_NONE && OBJECT_OUTSIDE(obj) && obj->type != OBJ_ROOM) {
        next = i;
        done = 1;
      }
    }

    if (!done) {
      // Start counting from zero
      for (int i = 0; i <= Cur_object_index && !done; i++) {
        object *obj = &Objects[i];

        if (obj->type != OBJ_NONE && OBJECT_OUTSIDE(obj) && obj->type != OBJ_ROOM) {
          next = i;
          done = 1;
        }
      }

      if (next == -1) {
        EditorStatus("There are no other objects on the terrain");
        return;
      }
    }

    SelectObject(next);
    return;
  }

  if (Objects[Cur_object_index].roomnum != ROOMNUM(Curroomp)) {
    next = Curroomp->objects;
    if (next == -1) {
      EditorStatus("There are no objects in the current room");
      return;
    }
  } else {
    next = Objects[Cur_object_index].next;
    if (next == -1) {
      next = Curroomp->objects;
      if (next == Cur_object_index) {
        EditorStatus("There are no other objects in this room");
        return;
      }
    }
  }

  SelectObject(next);
}

void CObjectDialog::OnSetfocusComboObjID() { InitObjIDComboBox((CComboBox *)GetDlgItem(IDC_COMBO_OBJID)); }

void CObjectDialog::OnObjectpadGroup() {
  // TODO: Add your control notification handler code here
}

void CObjectDialog::OnObjContPreview() {
  // TODO: Add your control notification handler code here
}

void CObjectDialog::OnObjpadFlagobjmulti() {
  // TODO: Add your control notification handler code here
}

void CObjectDialog::OnObjpadFlipobj() {
  // TODO: Add your control notification handler code here
  HObjectFlip();
}

void CObjectDialog::OnObjpadSetdefault() {
  // TODO: Add your control notification handler code here
  HObjectSetDefault();
}

void CObjectDialog::OnResetObjects() {
  ObjReInitAll();
  OutrageMessageBox("All objects reset!");
}

BOOL CObjectDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  WinHelp(HID_OBJECTTAB, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

//	This function will allow you to edit individual properties for the current selected object.

void CObjectDialog::OnObjpadProperties() {
  if (Cur_object_index == -1) {
    OutrageMessageBox("Must select an object before editing it's properties.");
    return;
  }

  Editor()->pause();

  switch (Objects[Cur_object_index].type) {
  case OBJ_POWERUP: {
    CPowerupPropDialog dlg;
    dlg.DoModal();
    break;
  }
  }

  Editor()->resume();
}

/////////////////////////////////////////////////////////////////////
//	New Object Movement Control implementation

void CObjectDialog::OnSelChangeCoordSysSelect() {
  CComboBox *cbox = (CComboBox *)GetDlgItem(IDC_COORDSYS_SELECT);
  char seltext[8];

  cbox->GetLBText(cbox->GetCurSel(), seltext);

  if (stricmp(seltext, "local") == 0) {
    D3EditState.object_move_mode = REL_OBJECT;
  } else if (stricmp(seltext, "viewer") == 0) {
    D3EditState.object_move_mode = REL_VIEWER;
  } else if (stricmp(seltext, "world") == 0) {
    D3EditState.object_move_mode = REL_VIEWER;
  }
}

void DrawItemModel(grHardwareSurface *surf, int model_num) {
  vector zero_vector = {0, 0, 0};
  vector view_pos = {0, 0, 0};
  matrix id_matrix, rot_matrix;

  poly_model *pm = GetPolymodelPointer(model_num);

  // Calculate viewer position
  vector maxs = pm->maxs, mins = pm->mins;
  view_pos.x = -(mins.x + maxs.x) / 2;
  view_pos.y = (mins.y + maxs.y) / 2;
  maxs.x += view_pos.x;
  maxs.y -= view_pos.y;
  maxs.z = 0;
  view_pos.z = -2.5 * vm_GetMagnitude(&maxs);

  // Set viewer and object orientations
  vm_MakeIdentity(&id_matrix);
  vm_AnglesToMatrix(&rot_matrix, 0, 32768, 0);

  // Set up surface & vuewport
  surf->clear();
  grViewport *vport = new grViewport(surf);
  vport->clear();

  // Draw to our surface
  StartEditorFrame(vport, &view_pos, &id_matrix, D3_DEFAULT_ZOOM);
  DrawPolygonModel(&zero_vector, &rot_matrix, model_num, NULL, 0, 1.0, 1.0, 1.0);
  EndEditorFrame();

  // Copy to the screen
  Desktop_surf->blt(0, 0, surf);

  // Delete our viewport
  delete vport;
}

void CObjectDialog::OnObjpadResetCurobjHeight() {
  if (Cur_object_index == -1) {
    OutrageMessageBox("You must have a current object for this operation.");
    return;
  }

  object *objp = &Objects[Cur_object_index];

  // Make sure object is outside
  if (!OBJECT_OUTSIDE(objp)) {
    OutrageMessageBox("The object must be on the terrain this operation.");
    return;
  }

  // Make sure object has a ground plane
  if (!((objp->render_type == RT_POLYOBJ) && ((GetPolymodelPointer(objp->rtype.pobj_info.model_num))->n_ground))) {
    OutrageMessageBox("The object must have a ground plane for this operation.");
    return;
  }

  ResetGroundObject(objp);
}

void CObjectDialog::OnObjpadResetAllObjHeights() {
  object *objp;
  int i;
  int n_moved = 0;

  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++) {

    // Make sure object is outside
    if (!OBJECT_OUTSIDE(objp))
      continue;

    // Make sure object has a ground plane
    if (!((objp->render_type == RT_POLYOBJ) && ((GetPolymodelPointer(objp->rtype.pobj_info.model_num))->n_ground)))
      continue;

    // Do it
    ResetGroundObject(objp);
    n_moved++;
  }

  EditorStatus("%d objects adjusted.", n_moved);
}

void CObjectDialog::OnPrevStartPositon() {
  if (m_current_start_pos == 0)
    m_current_start_pos = MAX_PLAYERS - 1;
  else
    m_current_start_pos--;

  UpdateDialog();
}

void CObjectDialog::OnNextStartPos() {
  m_current_start_pos++;

  if (m_current_start_pos >= MAX_PLAYERS)
    m_current_start_pos = 0;

  UpdateDialog();
}

void CObjectDialog::OnJumpToStartPos() {
  char str[255];
  int found_obj = -1;
  int highest = -1;
  for (int i = 0; i <= Highest_object_index && found_obj == -1; i++) {
    if (Objects[i].type == OBJ_PLAYER) {
      if (Objects[i].id > highest)
        highest = Objects[i].id;

      if (Objects[i].id == m_current_start_pos) {
        found_obj = i;
      }
    }
  }

  if (found_obj == -1) {
    sprintf(str, "There was no player defined for this start position. The highest numbered player is #%d.", highest);
    OutrageMessageBox(str);
  } else {
    MoveViewer(&Objects[found_obj].pos, Objects[found_obj].roomnum, &Objects[found_obj].orient);
    TV_changed = 1;
  }
}

void CObjectDialog::OnRedCheck() {
  int cur = m_current_start_pos;

  int c = IsDlgButtonChecked(IDC_RED_CHECK);

  if (c)
    Players[cur].startpos_flags |= PSPF_RED;
  else
    Players[cur].startpos_flags &= ~PSPF_RED;
}

void CObjectDialog::OnBlueCheck() {
  int cur = m_current_start_pos;

  int c = IsDlgButtonChecked(IDC_BLUE_CHECK);

  if (c)
    Players[cur].startpos_flags |= PSPF_BLUE;
  else
    Players[cur].startpos_flags &= ~PSPF_BLUE;
}

void CObjectDialog::OnGreenCheck() {
  int cur = m_current_start_pos;

  int c = IsDlgButtonChecked(IDC_GREEN_CHECK);

  if (c)
    Players[cur].startpos_flags |= PSPF_GREEN;
  else
    Players[cur].startpos_flags &= ~PSPF_GREEN;
}

void CObjectDialog::OnYellowCheck() {
  int cur = m_current_start_pos;

  int c = IsDlgButtonChecked(IDC_YELLOW_CHECK);

  if (c)
    Players[cur].startpos_flags |= PSPF_YELLOW;
  else
    Players[cur].startpos_flags &= ~PSPF_YELLOW;
}

void CObjectDialog::OnSelendokSwapSourceCombo() {
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Swap_source_id = FindObjectIDName(name);

  UpdateDialog();
}

void CObjectDialog::OnSelendokSwapDestCombo() {
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Swap_dest_id = FindObjectIDName(name);

  UpdateDialog();
}

void CObjectDialog::OnObjectSwapButton() {
  int i;
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SWAP_SOURCE_COMBO, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);
  int s_id = FindObjectIDName(name);

  cur = SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SWAP_DEST_COMBO, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);
  int d_id = FindObjectIDName(name);

  if (s_id >= 0 && d_id >= 0) {
    for (i = 0; i <= Highest_object_index; i++) {
      if (Objects[i].type == OBJ_ROBOT || Objects[i].type == OBJ_CLUTTER || Objects[i].type == OBJ_POWERUP ||
          Objects[i].type == OBJ_BUILDING) {
        if (Objects[i].id == s_id) {
          vector pos = Objects[i].pos;
          matrix orient = Objects[i].orient;
          int room = Objects[i].roomnum;
          int parent = Objects[i].parent_handle;

          char temp_name[256];
          temp_name[0] = '\0';

          if (Objects[i].name) {
            strcpy(temp_name, Objects[i].name);
          }

          ObjDelete(i);
          int o_index = ObjCreate(Object_info[d_id].type, d_id, room, &pos, &orient, parent);

          if (temp_name[0] != '\0') {
            Objects[o_index].name = (char *)mem_malloc(strlen(temp_name) + 1);
            strcpy(Objects[o_index].name, temp_name);
          }
        }
      }
    }
  }

  World_changed = 1;

  UpdateDialog();
}

void CObjectDialog::OnSelendokRegroundCombo() {
  int cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_REGROUND_COMBO, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_REGROUND_COMBO, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  Reground_id = FindObjectIDName(name);

  UpdateDialog();
}

void CObjectDialog::OnRegroundButton() {
  if (Reground_id >= 0 && Object_info[Reground_id].type != OBJ_NONE) {
    int i;
    for (i = 0; i <= Highest_object_index; i++) {
      vector gp;
      object *obj = &Objects[i];

      if (obj->type == OBJ_ROBOT || obj->type == OBJ_CLUTTER || obj->type == OBJ_POWERUP || obj->type == OBJ_BUILDING) {
        if (obj->id == Reground_id && PhysCalcGround(&gp, NULL, &Objects[i], 0)) {
          fvi_info hit_info;
          fvi_query fq;
          int fate;
          vector start = obj->pos + obj->size * 0.8f * obj->orient.uvec;
          vector end = obj->pos - obj->size * 2.0f * obj->orient.uvec;

          fq.p0 = &start;
          fq.p1 = &end;
          fq.startroom = obj->roomnum;

          fq.rad = 0.0f;
          fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS;
          fq.thisobjnum = OBJNUM(obj);
          fq.ignore_obj_list = NULL;

          fate = fvi_FindIntersection(&fq, &hit_info);

          if (fate != HIT_NONE) {
            float ps;
            float pr;
            float diff;

            ps = (gp - obj->pos) * obj->orient.uvec;
            pr = (hit_info.hit_pnt - obj->pos) * obj->orient.uvec;

            if (ps != pr) {
              diff = ps - pr;
              obj->pos -= diff * obj->orient.uvec;
              ObjSetPos(obj, &obj->pos, obj->roomnum, NULL, false);

              World_changed = 1;
            }
          }
        }
      }
    }
  }

  UpdateDialog();
}

extern bool RotateObject(int objnum, angle p, angle h, angle b);

void CObjectDialog::OnObjRot90() {
  angle p = 0, b = 0, h = 0;

  switch (D3EditState.object_move_axis) {
  case OBJMOVEAXIS_P:
    p = 0x4000;
    break;
  case OBJMOVEAXIS_H:
    h = 0x4000;
    break;
  case OBJMOVEAXIS_B:
    b = 0x4000;
    break;
  case OBJMOVEAXIS_PH:
    p = 0x4000;
    h = 0x4000;
    break;

  default:
    return;
  }

  RotateObject(Cur_object_index, p, h, b);
}

void CObjectDialog::OnObjectPushthroughwalls() {
  if (f_allow_objects_to_be_pushed_through_walls)
    f_allow_objects_to_be_pushed_through_walls = false;
  else
    f_allow_objects_to_be_pushed_through_walls = true;
}

void CObjectDialog::OnObjpadDeleteAll() {
  if (Cur_object_index == -1)
    return;

  object *objp = &Objects[Cur_object_index];

  if (objp->type == OBJ_PLAYER) {
    OutrageMessageBox("You cannot use this function on player objects.");
    return;
  }

  int type = objp->type, id = objp->id;

  if (type == OBJ_DOOR) {
    if (OutrageMessageBox(MBOX_YESNO,
                          "It's very, very bad to delete a door object.  Are you sure you want to delete all instances "
                          "of the \"%s\" door?",
                          Doors[id].name) != IDYES)
      return;
  } else { // Not a door
    char *objid_name;
    if (IS_GENERIC(type))
      objid_name = Object_info[id].name;
    else
      objid_name = "<unknown>";
    if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete all %s objects of type \"%s\" in the mine?",
                          Object_type_names[type], objid_name) != IDYES)
      return;
  }

  int count = 0;
  for (int objnum = 0; objnum <= Highest_object_index; objnum++) {
    if ((Objects[objnum].type == type) && (Objects[objnum].id == id)) {
      ObjDelete(objnum);
      count++;
    }
  }

  EditorStatus("%d objects deleted.", count);
  World_changed = 1;
}
