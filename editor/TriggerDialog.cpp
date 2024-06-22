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

 * $Logfile: /DescentIII/Main/editor/TriggerDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * Trigger keypad dialog.
 *
 * $Log: not supported by cvs2svn $
 *
 * 31    6/15/99 5:33p Matt
 * Fixed small stupid bug.
 *
 * 30    4/03/99 7:55p Matt
 * Use new keypad update system instead of timer to update.
 *
 * 29    4/03/99 3:41p Kevin
 * Put in code for "Edit Script" button
 *
 * 28    3/30/99 4:11p Matt
 * Set world changed flag when trigger deleted.
 *
 * 27    3/27/99 7:10p Matt
 * Strip leading & trailing spaces before check for duplicate names.
 *
 * 26    3/23/99 5:52p Matt
 * Added clutter activators for triggers
 *
 * 25    3/22/99 6:59p Matt
 * Fixed stupid bug:  was assigning UVs to floating trigger face before
 * computing normal.
 *
 * 24    3/01/99 10:39a Matt
 * Strip leading and trailing spaces from object, trigger, and room names
 * on level load and when the names are entered.
 *
 * 23    2/28/99 10:40p Matt
 * Check for name already in use when entering a name.
 *
 * 22    2/11/99 8:30p Matt
 *
 * 21    2/02/99 11:54p Luke
 * Fixed small bug (MattT on Luke's machine)
 *
 * 20    1/21/99 11:34a Matt
 * Got rid of portal triggers.  Since we don't have multi-face portals, a
 * face trigger works fine for a portal.  Also fixed a few editor/trigger
 * bugs.
 *
 * 19    1/15/99 10:51a Matt
 * Disable rename button if no current trigger
 *
 * 18    1/14/99 11:06a Matt
 * Added names to triggers
 *
 * 17    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 16    10/13/98 3:23p Matt
 * Fixed a problem with the add portal trigger button being enabled when
 * there was already a trigger on the portal's face.  Also, fixed and
 * added some asserts.
 *
 * 15    9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 14    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 13    2/04/98 6:23p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 12    1/23/98 5:54p Samir
 * Added new style script support to triggers.
 *
 * 11    1/20/98 4:12p Samir
 * New script housekeeping system.
 *
 * 10    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 9     9/24/97 6:18p Samir
 * Use script names instead of script id values to identify scripts.
 *
 * 8     9/24/97 2:58p Samir
 * New ScriptSelect.
 *
 * 7     9/15/97 11:51a Matt
 * Disable 'select by number' if no triggers
 *
 * 6     9/15/97 11:38a Matt
 * Added better trigger selection functions
 *
 * 5     9/14/97 11:07p Matt
 * Use new InputNumber() function
 *
 * 4     9/12/97 3:59p Matt
 * Lots of changes to trigger dialog
 *
 * 3     9/08/97 10:01a Matt
 * Ripped out old trigger code
 *
 * $NoKeywords: $
 */

#include <stdlib.h>

#include "stdafx.h"
#include "editor.h"
#include "TriggerDialog.h"
#include "trigger.h"
#include "EditLineDialog.h"
#include "render.h"
#include "trigger.h"
#include "HView.h"
#include "FindIntersection.h"
#include "erooms.h"
//@@#include "d3x.h"

#include "DallasMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int Current_trigger = -1; // current editing trigger

/////////////////////////////////////////////////////////////////////////////
// CTriggerDialog dialog

CTriggerDialog::CTriggerDialog(CWnd *pParent /*=NULL*/) : CKeypadDialog(CTriggerDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CTriggerDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CTriggerDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CTriggerDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTriggerDialog, CDialog)
//{{AFX_MSG_MAP(CTriggerDialog)
ON_WM_SIZE()
ON_WM_VSCROLL()
ON_WM_HSCROLL()
ON_WM_PAINT()
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_TRIG_ADD_TO_CURFACE, OnTrigAddToCurface)
ON_BN_CLICKED(IDC_TRIG_GOTO, OnTrigGoto)
ON_BN_CLICKED(IDC_TRIG_DELETE, OnTrigDelete)
ON_BN_CLICKED(IDC_TRIG_ADD_TO_CURPORTAL, OnTrigAddToCurportal)
ON_BN_CLICKED(IDC_TRIG_ADD_FLOATING, OnTrigAddFloating)
ON_BN_CLICKED(IDC_TRIG_RENDER_FLOATING, OnTrigRenderFloating)
ON_BN_CLICKED(IDC_TRIG_ACTIV_PLAYER, OnTrigActivPlayer)
ON_BN_CLICKED(IDC_TRIG_ACTIV_PLAYER_WEAPONS, OnTrigActivPlayerWeapons)
ON_BN_CLICKED(IDC_TRIG_ACTIV_ROBOT_WEAPONS, OnTrigActivRobotWeapons)
ON_BN_CLICKED(IDC_TRIG_ACTIV_ROBOTS, OnTrigActivRobots)
ON_BN_CLICKED(IDC_TRIG_FLOAT_NARROWER, OnTrigFloatNarrower)
ON_BN_CLICKED(IDC_TRIG_FLOAT_SHORTER, OnTrigFloatShorter)
ON_BN_CLICKED(IDC_TRIG_FLOAT_TALLER, OnTrigFloatTaller)
ON_BN_CLICKED(IDC_TRIG_FLOAT_WIDER, OnTrigFloatWider)
ON_BN_CLICKED(IDC_TRIG_ONESHOT, OnTrigOneShot)
ON_BN_CLICKED(IDC_TRIG_NEXT_PORTAL, OnTrigNextPortal)
ON_BN_CLICKED(IDC_TRIG_NEXT_IN_MINE, OnTrigNextInMine)
ON_BN_CLICKED(IDC_TRIG_NEXT_IN_ROOM, OnTrigNextInRoom)
ON_BN_CLICKED(IDC_TRIG_PREV_IN_MINE, OnTrigPrevInMine)
ON_BN_CLICKED(IDC_TRIG_PREV_IN_ROOM, OnTrigPrevInRoom)
ON_BN_CLICKED(IDC_TRIG_EDIT_NAME, OnTrigEditName)
ON_BN_CLICKED(IDC_TRIG_EDIT_SCRIPT, OnTrigEditScript)
ON_BN_CLICKED(IDC_TRIG_ACTIV_CLUTTER, OnTrigActivClutter)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriggerDialog message handlers

void CTriggerDialog::OnSize(UINT nType, int cx, int cy) {
  CKeypadDialog::OnSize(nType, cx, cy);

  //	make sure we can see a few items in the combo box when we drop it down.
  RECT rect;

  CComboBox *box = (CComboBox *)GetDlgItem(IDC_TRIGGERTYPE);
  if (box) {
    box->GetClientRect(&rect);
    box->SetWindowPos(NULL, 0, 0, rect.right - rect.left, box->GetItemHeight(0) * 10, SWP_NOMOVE | SWP_NOZORDER);
  }
}

void CTriggerDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  // TODO: Add your message handler code here and/or call default

  CKeypadDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTriggerDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  // TODO: Add your message handler code here and/or call default

  CKeypadDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

trigger *FindTrigger(int roomnum, int facenum);

int FindNextTrigInRoom(int roomnum, int start) {
  if ((start == -1) || (Triggers[start].roomnum != roomnum))
    start = 0;
  else
    start++;

  for (int i = 0; i < Num_triggers; i++) {
    int n = (start + i) % Num_triggers;

    if (Triggers[n].roomnum == roomnum)
      return n;
  }

  // Couldn't find one
  return -1;
}

int FindPrevTrigInRoom(int roomnum, int start) {
  if (Triggers[start].roomnum != roomnum)
    start = 0;
  else
    start--;

  for (int i = Num_triggers; i > 0; i--) {
    int n = (start + i) % Num_triggers;

    if (Triggers[n].roomnum == roomnum)
      return n;
  }

  // Couldn't find one
  return -1;
}

void CTriggerDialog::UpdateDialog() {
  bool portal = 0, floating = 0;
  static int last_curroom = -1, last_curface = -1, last_curportal = -1;

  if (Current_trigger >= Num_triggers)
    Current_trigger--;

  // If current room/face/portal change, select current trigger from current room/face/portal
  if ((ROOMNUM(Curroomp) != last_curroom) || (Curface != last_curface)) {
    if (Curroomp->faces[Curface].flags & FF_HAS_TRIGGER)
      Current_trigger = (FindTrigger(ROOMNUM(Curroomp), Curface) - Triggers);
  } else if ((Curportal != -1) && (Curportal != last_curportal))
    if (Curroomp->portals[Curportal].flags & FF_HAS_TRIGGER)
      Current_trigger = (FindTrigger(ROOMNUM(Curroomp), Curroomp->portals[Curportal].portal_face) - Triggers);
  last_curroom = ROOMNUM(Curroomp);
  last_curface = Curface, last_curportal = Curportal;

  // Enable/Disable some buttons, etc.
  ((CButton *)GetDlgItem(IDC_TRIG_NEXT_IN_MINE))->EnableWindow(Num_triggers > 1);
  ((CButton *)GetDlgItem(IDC_TRIG_PREV_IN_MINE))->EnableWindow(Num_triggers > 1);
  ((CButton *)GetDlgItem(IDC_TRIG_GOTO))->EnableWindow(Num_triggers > 0);
  ((CButton *)GetDlgItem(IDC_TRIG_DELETE))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_EDIT_SCRIPT))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_EDIT_NAME))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ADD_TO_CURFACE))->EnableWindow(!(Curroomp->faces[Curface].flags & FF_HAS_TRIGGER));
  ((CButton *)GetDlgItem(IDC_TRIG_ADD_TO_CURPORTAL))
      ->EnableWindow((Curportal != -1) &&
                     !(Curroomp->faces[Curroomp->portals[Curportal].portal_face].flags & FF_HAS_TRIGGER) &&
                     !(Curroomp->faces[Curroomp->portals[Curportal].portal_face].flags & FF_HAS_TRIGGER));
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_NUM))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_TYPE))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_ROOM))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_FACE))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_FACE))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_TRIG_PORTAL))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ACTIVATORS))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER_WEAPONS))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOT_WEAPONS))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOTS))->EnableWindow(Current_trigger != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_ONESHOT))->EnableWindow(Current_trigger != -1);

  int n = FindNextTrigInRoom(ROOMNUM(Curroomp), Current_trigger);
  ((CButton *)GetDlgItem(IDC_TRIG_NEXT_IN_ROOM))->EnableWindow((n != -1) && (n != Current_trigger));
  ((CButton *)GetDlgItem(IDC_TRIG_PREV_IN_ROOM))->EnableWindow((n != -1) && (n != Current_trigger));

  // Update current trigger info
  if (Current_trigger > -1) {
    trigger *tp = &Triggers[Current_trigger];
    room *rp = &Rooms[tp->roomnum];
    face *fp = &rp->faces[tp->facenum];

    portal = (fp->portal_num != -1);
    floating = ((fp->flags & FF_FLOATING_TRIG) != 0);
    ASSERT(!(portal && floating)); // Shouldn't be both portal and floating

    PrintToDlgItem(this, IDC_TRIG_CURRENT_NAME, "Name:\t %s", tp->name[0] ? tp->name : "<none>");
    PrintToDlgItem(this, IDC_TRIG_CURRENT_NUM, "Number:\t %d", Current_trigger);
    PrintToDlgItem(this, IDC_TRIG_CURRENT_TYPE, "Type:\t %s", portal ? "PORTAL" : (floating ? "FLOATING" : "FACE"));
    PrintToDlgItem(this, IDC_TRIG_CURRENT_ROOM, "Room:\t%d", tp->roomnum);
    PrintToDlgItem(this, IDC_TRIG_CURRENT_FACE, "Face:\t%d", tp->facenum);
    PrintToDlgItem(this, IDC_TRIG_CURRENT_TRIG_PORTAL, (portal) ? "Portal:\t%d" : "", fp->portal_num);

    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER))->SetCheck(tp->activator & AF_PLAYER);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER_WEAPONS))->SetCheck(tp->activator & AF_PLAYER_WEAPON);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOT_WEAPONS))->SetCheck(tp->activator & AF_ROBOT_WEAPON);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOTS))->SetCheck(tp->activator & AF_ROBOT);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_CLUTTER))->SetCheck(tp->activator & AF_CLUTTER);

    ((CButton *)GetDlgItem(IDC_TRIG_ONESHOT))->SetCheck(tp->flags & TF_ONESHOT);
  } else {
    PrintToDlgItem(this, IDC_TRIG_CURRENT_NAME, "Name:");
    PrintToDlgItem(this, IDC_TRIG_CURRENT_NUM, "Number:");
    PrintToDlgItem(this, IDC_TRIG_CURRENT_TYPE, "Type:");
    PrintToDlgItem(this, IDC_TRIG_CURRENT_ROOM, "Room:");
    PrintToDlgItem(this, IDC_TRIG_CURRENT_FACE, "Face:");
    PrintToDlgItem(this, IDC_TRIG_CURRENT_TRIG_PORTAL, "");

    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER))->SetCheck(0);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER_WEAPONS))->SetCheck(0);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOT_WEAPONS))->SetCheck(0);
    ((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOTS))->SetCheck(0);

    ((CButton *)GetDlgItem(IDC_TRIG_ONESHOT))->SetCheck(0);
  }

  // Enable/disable floating trig items
  ((CButton *)GetDlgItem(IDC_TRIG_FLOAT_BORDER))->EnableWindow(floating);
  ((CButton *)GetDlgItem(IDC_TRIG_FLOAT_WIDER))->EnableWindow(floating);
  ((CButton *)GetDlgItem(IDC_TRIG_FLOAT_NARROWER))->EnableWindow(floating);
  ((CButton *)GetDlgItem(IDC_TRIG_FLOAT_TALLER))->EnableWindow(floating);
  ((CButton *)GetDlgItem(IDC_TRIG_FLOAT_SHORTER))->EnableWindow(floating);

  // Enable/disable the portal items
  ((CButton *)GetDlgItem(IDC_TRIG_CURRENT_PORTAL))->EnableWindow(Curportal != -1);
  ((CButton *)GetDlgItem(IDC_TRIG_NEXT_PORTAL))
      ->EnableWindow(((Curportal == -1) && (Curroomp->num_portals > 0)) || (Curroomp->num_portals > 1));

  // Update the portal number
  if (Curportal != -1)
    PrintToDlgItem(this, IDC_TRIG_CURRENT_PORTAL, "Current Portal:\t%d", Curportal);
  else
    PrintToDlgItem(this, IDC_TRIG_CURRENT_PORTAL, "Current Portal:");
}

void CTriggerDialog::OnPaint() {
  CPaintDC dc(this); // device context for painting

  UpdateDialog();
}

BOOL CTriggerDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  // Check current trigger
  if (Current_trigger >= Num_triggers)
    Current_trigger = Num_triggers - 1;

  // Update global checkboxes
  (((CButton *)GetDlgItem(IDC_TRIG_RENDER_FLOATING))->SetCheck(Render_floating_triggers));

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CTriggerDialog::OnOK() {
  CWnd *focus = CWnd::GetFocus();
  if (focus)
    focus->GetNextWindow()->SetFocus();
}

BOOL CTriggerDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  WinHelp(HID_TRIGGERTAB, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CTriggerDialog::OnTrigAddToCurface() {
  ASSERT(!(Curroomp->faces[Curface].flags & FF_HAS_TRIGGER));

  char name[TRIG_NAME_LEN + 1] = "";

  if (!InputString(name, sizeof(name), "Trigger Name", "Enter a name for this trigger"))
    return;

  int activator = (Curroomp->faces[Curface].portal_num != -1) ? AF_PLAYER : AF_PLAYER_WEAPON;

  Current_trigger = AddTrigger(name, ROOMNUM(Curroomp), Curface, activator, NULL);
  UpdateDialog();
}

void SetCurroomFromTrigger() {
  if (ROOMNUM(Curroomp) != Triggers[Current_trigger].roomnum) {

    Curroomp = &Rooms[Triggers[Current_trigger].roomnum];

    Curface = Curedge = Curvert = 0;
    Curportal = -1;
  }

  Curface = Triggers[Current_trigger].facenum;

  if (Curroomp->faces[Curface].portal_num != -1)
    Curportal = Curroomp->faces[Curface].portal_num;

  State_changed = 1;
}

void CTriggerDialog::OnTrigGoto() {
  int n;

  if (InputNumber(&n, "Select Trigger", "Enter trigger number to select", this)) {

    if (n >= Num_triggers) {
      OutrageMessageBox("Invalid trigger number.");
      return;
    }

    Current_trigger = n;

    SetCurroomFromTrigger();

    UpdateDialog();
  }
}

void CTriggerDialog::OnTrigDelete() {
  ASSERT(Current_trigger != -1);

  if (OutrageMessageBox(MBOX_YESNO, "Are you sure you want to delete the current trigger?") != IDYES)
    return;

  trigger *tp = &Triggers[Current_trigger];
  room *rp = &Rooms[tp->roomnum];
  int facenum = tp->facenum;

  // Delete the trigger
  DeleteTrigger(Current_trigger);

  // Delete face if this was a floating trigger
  if (rp->faces[facenum].flags & FF_FLOATING_TRIG) {
    DeleteRoomFace(rp, facenum);
    if (Curface == facenum)
      Curface = (facenum + 1) % rp->num_faces;
  }

  if (Current_trigger == Num_triggers)
    Current_trigger--;

  UpdateDialog();

  World_changed = 1;
}

void CTriggerDialog::OnTrigAddToCurportal() {
  ASSERT(Curportal != -1);
  ASSERT(!(Curroomp->faces[Curroomp->portals[Curportal].portal_face].flags & FF_HAS_TRIGGER));

  char name[TRIG_NAME_LEN + 1] = "";

  if (!InputString(name, sizeof(name), "Trigger Name", "Enter a name for this trigger"))
    return;

  Current_trigger = AddTrigger(name, ROOMNUM(Curroomp), Curroomp->portals[Curportal].portal_face, AF_PLAYER, NULL);
  UpdateDialog();
}

void CTriggerDialog::UpdateKeypad(int mask) {
  if (mask & (KUF_CURROOM_CHANGED + KUF_CURFACE_CHANGED + KUF_CURPORTAL_CHANGED))
    UpdateDialog();
}

#include "erooms.h"

#define TRIG_PLACE_DIST 5.0
#define TRIG_DEFAULT_SIZE 10.0

void CTriggerDialog::OnTrigAddFloating() {
  int facenum, vertnum;
  room *rp;
  face *fp;
  vector center;
  fvi_query fq;
  fvi_info hit_info;
  int fate;

  if (OBJECT_OUTSIDE(Viewer_object)) {
    OutrageMessageBox("Sorry, this operation does not yet work in the terrain.");
    return;
  }

  char name[TRIG_NAME_LEN + 1] = "";

  if (!InputString(name, sizeof(name), "Trigger Name", "Enter a name for this trigger"))
    return;

  // Get center point of new face
  center = Viewer_object->pos + (Viewer_object->orient.fvec * TRIG_PLACE_DIST);

  // Make sure the viewer in in the mine
  if (Viewer_object->flags & OF_OUTSIDE_MINE)
    goto bad_place;

  // Check if position ok
  fq.p0 = &Viewer_object->pos;
  fq.startroom = Viewer_object->roomnum;
  fq.p1 = &center;
  fq.rad = 0;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;
  fq.flags = 0;
  fate = fvi_FindIntersection(&fq, &hit_info);

  // Bail if there's something in the way, or if the center point is outside
  if ((fate != HIT_NONE) || ROOMNUM_OUTSIDE(hit_info.hit_room)) {

  bad_place:;
    OutrageMessageBox("You cannot place a floating trigger here.");
    return;
  }

  // Get pointer to room the trigger is in
  rp = &Rooms[hit_info.hit_room];

  // Create a new face & new verts
  facenum = RoomAddFaces(rp, 1);
  vertnum = RoomAddVertices(rp, 4);
  fp = &rp->faces[facenum];
  InitRoomFace(fp, 4);

  // Set the vertices for the new face
  rp->verts[vertnum] =
      center - (Viewer_object->orient.rvec * TRIG_DEFAULT_SIZE) + (Viewer_object->orient.uvec * TRIG_DEFAULT_SIZE);
  rp->verts[vertnum + 1] =
      center + (Viewer_object->orient.rvec * TRIG_DEFAULT_SIZE) + (Viewer_object->orient.uvec * TRIG_DEFAULT_SIZE);
  rp->verts[vertnum + 2] =
      center + (Viewer_object->orient.rvec * TRIG_DEFAULT_SIZE) - (Viewer_object->orient.uvec * TRIG_DEFAULT_SIZE);
  rp->verts[vertnum + 3] =
      center - (Viewer_object->orient.rvec * TRIG_DEFAULT_SIZE) - (Viewer_object->orient.uvec * TRIG_DEFAULT_SIZE);

  // Set vertnums for new face
  for (int i = 0; i < 4; i++)
    fp->face_verts[i] = vertnum + i;

  // Assign UVs and normal to new face
  if (!ComputeFaceNormal(rp, facenum))
    Int3(); // Get Matt
  AssignDefaultUVsToRoomFace(rp, facenum);

  // Set floating trig flag
  fp->flags |= FF_FLOATING_TRIG;

  // Add the trigger for the new face
  Current_trigger = AddTrigger(name, ROOMNUM(rp), facenum, AF_PLAYER, NULL);

  // Set the current room:face to the new face
  SetCurroomFromTrigger();

  // We're done
  UpdateDialog();
}

void CTriggerDialog::OnTrigRenderFloating() {
  Render_floating_triggers = (((CButton *)GetDlgItem(IDC_TRIG_RENDER_FLOATING))->GetCheck() != 0);
  State_changed = 1;
}

void CTriggerDialog::OnTrigActivPlayer() {
  trigger *tp = &Triggers[Current_trigger];

  if (((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER))->GetCheck())
    tp->activator |= AF_PLAYER;
  else
    tp->activator &= ~AF_PLAYER;

  World_changed = 1;
}

void CTriggerDialog::OnTrigActivPlayerWeapons() {
  trigger *tp = &Triggers[Current_trigger];

  if (((CButton *)GetDlgItem(IDC_TRIG_ACTIV_PLAYER_WEAPONS))->GetCheck())
    tp->activator |= AF_PLAYER_WEAPON;
  else
    tp->activator &= ~AF_PLAYER_WEAPON;

  World_changed = 1;
}

void CTriggerDialog::OnTrigActivRobotWeapons() {
  trigger *tp = &Triggers[Current_trigger];

  if (((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOT_WEAPONS))->GetCheck())
    tp->activator |= AF_ROBOT_WEAPON;
  else
    tp->activator &= ~AF_ROBOT_WEAPON;

  World_changed = 1;
}

void CTriggerDialog::OnTrigActivRobots() {
  trigger *tp = &Triggers[Current_trigger];

  if (((CButton *)GetDlgItem(IDC_TRIG_ACTIV_ROBOTS))->GetCheck())
    tp->activator |= AF_ROBOT;
  else
    tp->activator &= ~AF_ROBOT;

  World_changed = 1;
}

void ScaleFloatingTrigEdge(int roomnum, int facenum, int v0, int v1, float delta) {
  room *rp = &Rooms[roomnum];
  face *fp = &rp->faces[facenum];
  vector *vv0, *vv1;
  vector deltav;
  float mag;

  // Get pointers to verts
  vv0 = &rp->verts[fp->face_verts[v0]];
  vv1 = &rp->verts[fp->face_verts[v1]];

  // Get delta vec
  deltav = *vv1 - *vv0;
  mag = vm_NormalizeVector(&deltav);

  // Check for min size
  if (mag <= delta)
    return;

  // Now add
  *vv0 -= deltav * delta;
  *vv1 += deltav * delta;
}

#define SCALE_DELTA 1.0

void CTriggerDialog::OnTrigFloatNarrower() {
  ASSERT(Current_trigger != -1);

  trigger *tp = &Triggers[Current_trigger];

  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 0, 1, -SCALE_DELTA);
  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 2, 3, -SCALE_DELTA);

  World_changed = 1;
}

void CTriggerDialog::OnTrigFloatShorter() {
  ASSERT(Current_trigger != -1);

  trigger *tp = &Triggers[Current_trigger];

  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 1, 2, -SCALE_DELTA);
  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 3, 0, -SCALE_DELTA);

  World_changed = 1;
}

void CTriggerDialog::OnTrigFloatTaller() {
  ASSERT(Current_trigger != -1);

  trigger *tp = &Triggers[Current_trigger];

  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 1, 2, SCALE_DELTA);
  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 3, 0, SCALE_DELTA);

  World_changed = 1;
}

void CTriggerDialog::OnTrigFloatWider() {
  ASSERT(Current_trigger != -1);

  trigger *tp = &Triggers[Current_trigger];

  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 0, 1, SCALE_DELTA);
  ScaleFloatingTrigEdge(tp->roomnum, tp->facenum, 2, 3, SCALE_DELTA);

  World_changed = 1;
}

void CTriggerDialog::OnTrigOneShot() {
  trigger *tp = &Triggers[Current_trigger];

  if (((CButton *)GetDlgItem(IDC_TRIG_ONESHOT))->GetCheck())
    tp->flags |= TF_ONESHOT;
  else
    tp->flags &= ~TF_ONESHOT;

  World_changed = 1;
}

void CTriggerDialog::OnTrigNextPortal() {
  if (Curroomp->num_portals) {
    Curportal = (Curportal + 1) % Curroomp->num_portals;
    State_changed = 1;
    UpdateDialog();
  }
}

void CTriggerDialog::OnTrigNextInMine() {
  ASSERT(Current_trigger != -1);

  Current_trigger = (Current_trigger + 1) % Num_triggers;

  SetCurroomFromTrigger();

  UpdateDialog();
}

void CTriggerDialog::OnTrigNextInRoom() {
  int n = FindNextTrigInRoom(ROOMNUM(Curroomp), Current_trigger);

  ASSERT(n != -1);

  Current_trigger = n;

  SetCurroomFromTrigger();
}

void CTriggerDialog::OnTrigPrevInMine() {
  ASSERT(Current_trigger != -1);

  if (--Current_trigger < 0)
    Current_trigger += Num_triggers;

  SetCurroomFromTrigger();

  UpdateDialog();
}

void CTriggerDialog::OnTrigPrevInRoom() {
  int n = FindPrevTrigInRoom(ROOMNUM(Curroomp), Current_trigger);

  ASSERT(n != -1);

  Current_trigger = n;

  SetCurroomFromTrigger();
}

#include "osiris_predefs.h"
extern bool StripLeadingTrailingSpaces(char *s);

void CTriggerDialog::OnTrigEditName() {
  ASSERT(Current_trigger != -1);

  trigger *tp = &Triggers[Current_trigger];

  char name[TRIG_NAME_LEN + 1];

  strcpy(name, tp->name);

try_again:;
  if (!InputString(name, sizeof(name), "Trigger Name", "Enter a new name:"))
    return;

  if (StripLeadingTrailingSpaces(name))
    EditorMessageBox("Note: Leading and/or trailing spaces have been removed from this name (\"%s\")", name);

  int n = osipf_FindTriggerName(name);
  if ((n != -1) && (n != Current_trigger)) {
    EditorMessageBox("Trigger %d already has this name.", n);
    goto try_again;
  }

  strcpy(tp->name, name);

  UpdateDialog();
}

void CTriggerDialog::OnTrigEditScript() {

  mprintf(0, "Edit script for trigger %d\n", Current_trigger);

  // Make sure Dallas is open
  if (Editor()->m_DallasModelessDlgPtr == NULL) {
    Editor()->m_DallasModelessDlgPtr = new CDallasMainDlg;
    Editor()->m_DallasModelessDlgPtr->Create(IDD_DALLAS_MAIN_DIALOG, this);
    Editor()->m_DallasModelessDlgPtr->ShowWindow(SW_SHOW);
  } else
    Editor()->m_DallasModelessDlgPtr->ShowWindow(SW_RESTORE);

  // make sure a trigger was selected
  if (Current_trigger == -1)
    return;

  // Tell Dallas to add a new script with this trigger as the owner
  Editor()->m_DallasModelessDlgPtr->m_ScriptOwnerType = TRIGGER_TYPE;
  Editor()->m_DallasModelessDlgPtr->m_ScriptOwnerHandle = Current_trigger;
  Editor()->m_DallasModelessDlgPtr->PostMessage(WM_HIGHLIGHT_SCRIPTS);
}

void CTriggerDialog::OnTrigActivClutter() {
  trigger *tp = &Triggers[Current_trigger];

  if (((CButton *)GetDlgItem(IDC_TRIG_ACTIV_CLUTTER))->GetCheck())
    tp->activator |= AF_CLUTTER;
  else
    tp->activator &= ~AF_CLUTTER;

  World_changed = 1;
}
