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

 * $Logfile: /DescentIII/Main/editor/ViewerPropDlg.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:39 $
 * $Author: kevinb $
 *
 * Viewer Properties Dialog Implementation
 *
 * $Log: not supported by cvs2svn $
 *
 * 3     4/17/99 2:46p Matt
 * Implemented viewer properties dialog functions.
 *
 * 2     4/16/99 3:53p Nate
 * Initial version
 *
 * $NoKeywords: $
 */

// ViewerPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "ViewerPropDlg.h"
#include "object.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerPropDlg dialog

CViewerPropDlg::CViewerPropDlg(CWnd *pParent /*=NULL*/) : CDialog(CViewerPropDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CViewerPropDlg)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CViewerPropDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CViewerPropDlg)
  DDX_Control(pDX, IDC_ZPOS_EDIT, m_ZPosEdit);
  DDX_Control(pDX, IDC_YPOS_EDIT, m_YPosEdit);
  DDX_Control(pDX, IDC_XPOS_EDIT, m_XPosEdit);
  DDX_Control(pDX, IDC_ZMOVE_CHECK, m_ZMoveCheck);
  DDX_Control(pDX, IDC_YMOVE_CHECK, m_YMoveCheck);
  DDX_Control(pDX, IDC_XMOVE_CHECK, m_XMoveCheck);
  DDX_Control(pDX, IDC_PITCH_EDIT, m_PitchEdit);
  DDX_Control(pDX, IDC_HEADING_EDIT, m_HeadingEdit);
  DDX_Control(pDX, IDC_BANK_EDIT, m_BankEdit);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CViewerPropDlg, CDialog)
//{{AFX_MSG_MAP(CViewerPropDlg)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_ALIGN_UPYPOS_BUTTON, OnAlignUpWithYposButton)
ON_BN_CLICKED(IDC_ALIGN_XNEG_BUTTON, OnAlignXnegButton)
ON_BN_CLICKED(IDC_ALIGN_XPOS_BUTTON, OnAlignXposButton)
ON_BN_CLICKED(IDC_ALIGN_YNEG_BUTTON, OnAlignYnegButton)
ON_BN_CLICKED(IDC_ALIGN_YPOS_BUTTON, OnAlignYposButton)
ON_BN_CLICKED(IDC_ALIGN_ZNEG_BUTTON, OnAlignZnegButton)
ON_BN_CLICKED(IDC_ALIGN_ZPOS_BUTTON, OnAlignZposButton)
ON_BN_CLICKED(IDC_ORIENT_COMMIT_BUTTON, OnOrientCommitButton)
ON_BN_CLICKED(IDC_POS_COMMIT_BUTTON, OnPosCommitButton)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_XMOVE_CHECK, OnXMoveCheck)
ON_BN_CLICKED(IDC_YMOVE_CHECK, OnYMoveCheck)
ON_BN_CLICKED(IDC_ZMOVE_CHECK, OnZMoveCheck)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerPropDlg message handlers

BOOL CViewerPropDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  // Set Defaults
  m_XMoveCheck.SetCheck(1);
  m_YMoveCheck.SetCheck(1);
  m_ZMoveCheck.SetCheck(1);

  UpdatePosition();
  UpdateOrientation();

  ((CButton *)GetDlgItem(IDC_POS_COMMIT_BUTTON))->EnableWindow(0);

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewerPropDlg::PostNcDestroy() {
  // Set the pointer back to null so rest of app knows Viewer Prog dlg has shut down
  Editor()->m_ViewerPropDlgPtr = NULL;

  // Delete the viewer prop instance
  delete this;
}

void CViewerPropDlg::OnClose() {
  // Shut it all down
  DestroyWindow();
}

extern int Slew_limitations;

void CViewerPropDlg::OnDestroy() {
  CDialog::OnDestroy();

  Slew_limitations = 0;
}

void CViewerPropDlg::OnAlignUpWithYposButton() {
  matrix *m = &Viewer_object->orient;

  m->rvec.y = m->fvec.y = m->uvec.x = m->uvec.z = 0;
  m->uvec.y = 1.0;

  vm_Orthogonalize(m);

  Viewer_moved = 1;
}

void CViewerPropDlg::OnAlignXnegButton() {
  matrix *m = &Viewer_object->orient;

  m->fvec.x = -1.0;
  m->fvec.y = m->fvec.z = 0;
  m->uvec.y = 1.0;
  m->uvec.x = m->uvec.z = 0;
  m->rvec.z = 1.0;
  m->rvec.x = m->rvec.y = 0;

  Viewer_moved = 1;
}

void CViewerPropDlg::OnAlignXposButton() {
  matrix *m = &Viewer_object->orient;

  m->fvec.x = 1.0;
  m->fvec.y = m->fvec.z = 0;
  m->uvec.y = 1.0;
  m->uvec.x = m->uvec.z = 0;
  m->rvec.z = -1.0;
  m->rvec.x = m->rvec.y = 0;

  Viewer_moved = 1;
}

void CViewerPropDlg::OnAlignYnegButton() {
  matrix *m = &Viewer_object->orient;

  m->fvec.y = -1.0;
  m->fvec.x = m->fvec.z = 0;
  m->uvec.z = 1.0;
  m->uvec.x = m->uvec.y = 0;
  m->rvec.x = 1.0;
  m->rvec.y = m->rvec.z = 0;

  Viewer_moved = 1;
}

void CViewerPropDlg::OnAlignYposButton() {
  matrix *m = &Viewer_object->orient;

  m->fvec.y = 1.0;
  m->fvec.x = m->fvec.z = 0;
  m->uvec.z = -1.0;
  m->uvec.x = m->uvec.y = 0;
  m->rvec.x = 1.0;
  m->rvec.y = m->rvec.z = 0;

  Viewer_moved = 1;
}

void CViewerPropDlg::OnAlignZnegButton() {
  matrix *m = &Viewer_object->orient;

  m->fvec.z = -1.0;
  m->fvec.x = m->fvec.y = 0;
  m->uvec.y = 1.0;
  m->uvec.x = m->uvec.z = 0;
  m->rvec.x = -1.0;
  m->rvec.y = m->rvec.z = 0;

  Viewer_moved = 1;
}

void CViewerPropDlg::OnAlignZposButton() {
  matrix *m = &Viewer_object->orient;

  m->fvec.z = 1.0;
  m->fvec.x = m->fvec.y = 0;
  m->uvec.y = 1.0;
  m->uvec.x = m->uvec.z = 0;
  m->rvec.x = 1.0;
  m->rvec.y = m->rvec.z = 0;

  Viewer_moved = 1;
}

void CViewerPropDlg::OnOrientCommitButton() {
  angle p, b, h;
  char buf[10];

  m_PitchEdit.GetWindowText(buf, sizeof(buf));
  p = atof(buf) * 65536 / 360;

  m_HeadingEdit.GetWindowText(buf, sizeof(buf));
  h = atof(buf) * 65536 / 360;

  m_BankEdit.GetWindowText(buf, sizeof(buf));
  b = atof(buf) * 65536 / 360;

  mprintf(0, "Agngles %x %x %x\n", p, h, b);

  vm_AnglesToMatrix(&Viewer_object->orient, p, h, b);

  State_changed = Viewer_moved = 1;
}

#include "findintersection.h"

void CViewerPropDlg::OnPosCommitButton() {
  vector pos;
  char buf[10];

  m_XPosEdit.GetWindowText(buf, sizeof(buf));
  pos.x = atof(buf);

  m_YPosEdit.GetWindowText(buf, sizeof(buf));
  pos.y = atof(buf);

  m_ZPosEdit.GetWindowText(buf, sizeof(buf));
  pos.z = atof(buf);
}

void CViewerPropDlg::UpdateOrientation() {
  char buf[10];
  angvec angs;

  vm_ExtractAnglesFromMatrix(&angs, &Viewer_object->orient);

  sprintf(buf, "%d", (int)angs.p * 360 / 65536);
  m_PitchEdit.SetWindowText(buf);

  sprintf(buf, "%d", (int)angs.h * 360 / 65536);
  m_HeadingEdit.SetWindowText(buf);

  sprintf(buf, "%d", (int)angs.b * 360 / 65536);
  m_BankEdit.SetWindowText(buf);
}

void CViewerPropDlg::UpdatePosition() {
  char buf[10];

  sprintf(buf, "%.2f", Viewer_object->pos.x);
  m_XPosEdit.SetWindowText(buf);

  sprintf(buf, "%.2f", Viewer_object->pos.y);
  m_YPosEdit.SetWindowText(buf);

  sprintf(buf, "%.2f", Viewer_object->pos.z);
  m_ZPosEdit.SetWindowText(buf);
}

void CViewerPropDlg::OnXMoveCheck() {
  if (m_XMoveCheck.GetCheck())
    Slew_limitations &= ~1;
  else
    Slew_limitations |= 1;
}

void CViewerPropDlg::OnYMoveCheck() {
  if (m_YMoveCheck.GetCheck())
    Slew_limitations &= ~2;
  else
    Slew_limitations |= 2;
}

void CViewerPropDlg::OnZMoveCheck() {
  if (m_ZMoveCheck.GetCheck())
    Slew_limitations &= ~4;
  else
    Slew_limitations |= 4;
}
