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
 */

// SelectRangeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "SelectRangeDialog.h"
#include "terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectRangeDialog dialog

SelectRangeDialog::SelectRangeDialog(CWnd *pParent /*=NULL*/) : CDialog(SelectRangeDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(SelectRangeDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void SelectRangeDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(SelectRangeDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SelectRangeDialog, CDialog)
//{{AFX_MSG_MAP(SelectRangeDialog)
ON_EN_KILLFOCUS(IDC_LOWER_BOUND_EDIT, OnKillfocusLowerBoundEdit)
ON_EN_KILLFOCUS(IDC_UPPER_BOUND_EDIT, OnKillfocusUpperBoundEdit)
ON_BN_CLICKED(IDC_SELECT_SLOPE_CHECK, OnSelectSlopeCheck)
ON_EN_KILLFOCUS(IDC_SLOPE_EDIT, OnKillfocusSlopeEdit)
ON_BN_CLICKED(IDC_INVERSE_CHECK, OnInverseCheck)
ON_BN_CLICKED(IDC_TEXTURE_GRID_CHECK, OnTextureGridCheck)
ON_BN_CLICKED(IDC_RANDOM_CHECK, OnRandomCheck)
ON_BN_CLICKED(IDC_SELECT_CUR_TEXTURE_CHECK, OnSelectCurTextureCheck)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectRangeDialog message handlers

void SelectRangeDialog::OnKillfocusLowerBoundEdit() {
  CEdit *ebox;
  char str[20];
  int num;

  ebox = (CEdit *)GetDlgItem(IDC_LOWER_BOUND_EDIT);
  ebox->GetWindowText(str, 20);

  num = atoi(str);
  if (num < 0)
    num = 0;
  if (num > 255)
    num = 255;

  LowerBound = num;
}

void SelectRangeDialog::OnKillfocusUpperBoundEdit() {
  CEdit *ebox;
  char str[20];
  int num;

  ebox = (CEdit *)GetDlgItem(IDC_UPPER_BOUND_EDIT);
  ebox->GetWindowText(str, 20);

  num = atoi(str);
  if (num < 0)
    num = 0;
  if (num > 255)
    num = 255;

  UpperBound = num;
}

void SelectRangeDialog::OnOK() {
  OnKillfocusUpperBoundEdit();
  OnKillfocusLowerBoundEdit();
  OnKillfocusSlopeEdit();

  int use_slope = IsDlgButtonChecked(IDC_SELECT_SLOPE_CHECK);
  int inverted = IsDlgButtonChecked(IDC_INVERSE_CHECK);
  int texgrid = IsDlgButtonChecked(IDC_TEXTURE_GRID_CHECK);
  int random = IsDlgButtonChecked(IDC_RANDOM_CHECK);
  int cur_texture = IsDlgButtonChecked(IDC_SELECT_CUR_TEXTURE_CHECK);

  if (UpperBound < LowerBound) {
    OutrageMessageBox("Lower bound must be less than upper bound!");
  } else {
    for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++)
      TerrainSelected[i] = 0;
    Num_terrain_selected = 0;
    for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_DEPTH; i++) {
      int selected = 1;

      if (!(Terrain_seg[i].ypos >= LowerBound && Terrain_seg[i].ypos <= UpperBound))
        selected = 0;

      if (use_slope) {
        int x = i % TERRAIN_WIDTH;
        int z = i / TERRAIN_WIDTH;

        if (x != (TERRAIN_WIDTH - 1)) {
          if (!((abs(Terrain_seg[i].ypos - Terrain_seg[z * TERRAIN_WIDTH + (x + 1)].ypos)) >= SlopeAngle))
            selected = 0;

          if (z != (TERRAIN_DEPTH - 1)) {
            if (!((abs(Terrain_seg[i].ypos - Terrain_seg[(z + 1) * TERRAIN_WIDTH + (x + 1)].ypos)) >= SlopeAngle))
              selected = 0;
          }
        }

        if (z != (TERRAIN_DEPTH - 1)) {
          if (!((abs(Terrain_seg[i].ypos - Terrain_seg[(z + 1) * TERRAIN_WIDTH + (x)].ypos)) >= SlopeAngle))
            selected = 0;
        }
      }

      if (random) {
        if (rand() > (RAND_MAX / 2))
          selected = 0;
      }

      if (texgrid) {
        int x = i % TERRAIN_WIDTH;
        int z = i / TERRAIN_WIDTH;

        if (x % (1 << (MAX_TERRAIN_LOD - 1)))
          selected = 0;

        if (z % (1 << (MAX_TERRAIN_LOD - 1)))
          selected = 0;
      }

      if (cur_texture) {
        if (Terrain_tex_seg[Terrain_seg[i].texseg_index].tex_index != D3EditState.texdlg_texture)
          selected = 0;
      }

      if (inverted)
        selected = !selected;

      if (selected) {
        TerrainSelected[i] = 1;
        Num_terrain_selected++;
      }
    }
  }

  CDialog::OnOK();
}

void SelectRangeDialog::OnCancel() {
  // TODO: Add extra cleanup here

  CDialog::OnCancel();
}

void SelectRangeDialog::OnSelectSlopeCheck() {
  int c = IsDlgButtonChecked(IDC_SELECT_SLOPE_CHECK);

  CButton *bbox = (CButton *)GetDlgItem(IDC_SLOPE_EDIT);
  bbox->EnableWindow(c);
}

void SelectRangeDialog::OnKillfocusSlopeEdit() {
  CEdit *ebox;
  char str[20];
  int num;

  ebox = (CEdit *)GetDlgItem(IDC_SLOPE_EDIT);
  ebox->GetWindowText(str, 20);

  num = atoi(str);
  if (num < 0)
    num = 0;
  if (num > 255)
    num = 255;

  SlopeAngle = num;
}

void SelectRangeDialog::OnInverseCheck() {}

void SelectRangeDialog::OnTextureGridCheck() {
  // TODO: Add your control notification handler code here
}

void SelectRangeDialog::OnRandomCheck() {
  // TODO: Add your control notification handler code here
}

void SelectRangeDialog::OnSelectCurTextureCheck() {
  // TODO: Add your control notification handler code here
}
