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

// MegacellDialog.cpp : implementation file
//

#include  <filesystem>

#include "stdafx.h"
#include "editor.h"
#include "MegacellDialog.h"
#include "WorldTexturesDialog.h"
#include "megapage.h"
#include "megacell.h"
#include "manage.h"
#include "gametexture.h"
#include "vclip.h"
#include "texpage.h"
#include "bitmap.h"
#include "ddio.h"
#include "mem.h"
#include "EditLineDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static megacell m_CopyMegacell;

/////////////////////////////////////////////////////////////////////////////
// CMegacellDialog dialog

CMegacellDialog::CMegacellDialog(CWnd *pParent /*=NULL*/) : CDialog(CMegacellDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CMegacellDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

  m_TexStart = 0;
  m_TexListPos = 0;
  m_RedrawListbox = 0;
  m_TexPageLen = 0;
  m_CheckForTextureList = 0;
  m_CheckX = m_CheckY = 0;
  memset(&m_CopyMegacell, 0, sizeof(megacell));
}

void CMegacellDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CMegacellDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMegacellDialog, CDialog)
//{{AFX_MSG_MAP(CMegacellDialog)
ON_BN_CLICKED(IDC_NEW_MEGACELL, OnNewMegacell)
ON_BN_CLICKED(IDC_LOCK_MEGACELL, OnLockMegacell)
ON_BN_CLICKED(IDC_CHECKIN_MEGACELL, OnCheckinMegacell)
ON_BN_CLICKED(IDC_DELETE_MEGACELL, OnDeleteMegacell)
ON_BN_CLICKED(IDC_NEXT_MEGACELL, OnNextMegacell)
ON_BN_CLICKED(IDC_PREVIOUS_MEGACELL, OnPreviousMegacell)
ON_CBN_SELENDOK(IDC_MEGACELL_PULLDOWN, OnSelendokMegacellPulldown)
ON_BN_CLICKED(IDC_MEGACELLS_OUT, OnMegacellsOut)
ON_EN_KILLFOCUS(IDC_MEGACELL_NAME_EDIT, OnKillfocusMegacellNameEdit)
ON_EN_KILLFOCUS(IDC_MEGA_WIDTH_EDIT, OnKillfocusMegaWidthEdit)
ON_EN_KILLFOCUS(IDC_MEGA_HEIGHT_EDIT, OnKillfocusMegaHeightEdit)
ON_WM_LBUTTONDOWN()
ON_WM_VSCROLL()
ON_WM_PAINT()
ON_BN_CLICKED(IDC_REMAP_MEGACELL, OnRemapMegacell)
ON_BN_CLICKED(IDC_ROTATE_MEGACELL, OnRotateMegacell)
ON_BN_CLICKED(IDC_COPY_MEGACELL, OnCopyMegacell)
ON_BN_CLICKED(IDC_PASTE_MEGACELL, OnPasteMegacell)
ON_BN_CLICKED(IDC_IMPORT_TINY, OnImportTiny)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_IMPORT_SKY, OnImportSky)
ON_BN_CLICKED(IDC_IMPORT_SKY_BAND, OnImportSkyBand)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMegacellDialog message handlers

void CMegacellDialog::OnNewMegacell() {
  char filename[255];
  char cur_name[100];
  int cell_handle;
  int c = 1, finding_name = 1;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  // Get megacell name

  CEditLineDialog dlg("Enter megacell name", this);
  int ret = dlg.DoModal();

  if (ret == IDCANCEL)
    return;

  strcpy(filename, (char *)dlg.GetText());

  // Alloc a megacell and give a name not already taken by some other cell

  cell_handle = AllocMegacell();

  while (finding_name) {
    sprintf(cur_name, "%s%d", filename, c);
    if (FindMegacellName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(Megacells[cell_handle].name, cur_name);

  mng_AllocTrackLock(cur_name, PAGETYPE_MEGACELL);

  D3EditState.current_megacell = cell_handle;

  UpdateDialog();
}

void CMegacellDialog::OnLockMegacell() {
  int n = D3EditState.current_megacell;
  mngs_Pagelock temp_pl;
  mngs_megacell_page megacellpage;
  int r;

  if (Num_megacells < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, Megacells[n].name);
  temp_pl.pagetype = PAGETYPE_MEGACELL;

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
      if (mng_FindSpecificMegacellPage(temp_pl.name, &megacellpage, 0)) {
        if (mng_AssignMegacellPageToMegacell(&megacellpage, n)) {

          if (!mng_ReplacePage(Megacells[n].name, Megacells[n].name, n, PAGETYPE_MEGACELL, 1)) {
            OutrageMessageBox("There was problem writing that page locally!");
            mng_EraseLocker();
            return;
          }
          OutrageMessageBox("Megacell locked.");

        } else
          OutrageMessageBox("There was a problem loading this megacell.  You might encounter problems in dealing with "
                            "it.  Good luck!");

        mng_AllocTrackLock(Megacells[n].name, PAGETYPE_MEGACELL);
        UpdateDialog();
      } else
        OutrageMessageBox("Couldn't find that megacell in the table file!");
    }
  }
  mng_EraseLocker();
}

void CMegacellDialog::OnCheckinMegacell() {
  int n = D3EditState.current_megacell;
  mngs_Pagelock temp_pl;
  int r;
  int i;

  if (Num_megacells < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure we own this megacell
  strcpy(temp_pl.name, Megacells[n].name);
  temp_pl.pagetype = PAGETYPE_MEGACELL;

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

      int answer = MessageBox("Do you wish to check in all the textures associated with this megacell (if any)?",
                              Megacells[n].name, MB_YESNO);

      if (answer == IDYES) {
        // Check in all these textures
        for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++) {
          int mx = i % MAX_MEGACELL_WIDTH;
          int my = i / MAX_MEGACELL_WIDTH;

          if (mx >= Megacells[n].width || my >= Megacells[n].height)
            continue;

          int index = Megacells[n].texture_handles[i];
          if (!GameTextures[index].used || index == 0)
            continue;
          int tl;
          if ((tl = mng_FindTrackLock(GameTextures[index].name, PAGETYPE_TEXTURE)) != -1)
            CheckinTexture(index, tl);
        }
      }

      if (!mng_ReplacePage(Megacells[n].name, Megacells[n].name, n, PAGETYPE_MEGACELL, 0))
        OutrageMessageBox(ErrorString);
      else {
        OutrageMessageBox("Megacell checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Megacells[n].name, PAGETYPE_MEGACELL, 1);
        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }
}

extern int TlockState;
extern int AutoChecking;

void CMegacellDialog::OnDeleteMegacell() {
  int answer, tl;
  mngs_Pagelock pl;
  CWorldTexturesDialog texdlg;

  int n = D3EditState.current_megacell;
  int i;

  if (Num_megacells < 1)
    return;

  // Check to see if we even have it locked
  if ((tl = mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL)) == -1) {
    OutrageMessageBox("This megacell is not yours to delete.  Lock first.");
    return;
  }

  // Make sure its to be deleted
  answer = MessageBox("Are you sure you want to delete this megacell?", Megacells[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  answer =
      MessageBox("Do you wish to delete all the textures associated with this megacell?", Megacells[n].name, MB_YESNO);

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Megacells[n].name);
  pl.pagetype = PAGETYPE_MEGACELL;

  // Check to see if this is a local megacell only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(Megacells[n].name, PAGETYPE_MEGACELL, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else // if its network, delete it from both the net and local drives
  {

    mng_FreeTrackLock(tl);

    mng_DeletePage(Megacells[n].name, PAGETYPE_MEGACELL, 0);
    mng_DeletePage(Megacells[n].name, PAGETYPE_MEGACELL, 1);

    mng_DeletePagelock(Megacells[n].name, PAGETYPE_MEGACELL);
  }

  // Advance to the next megacell
  D3EditState.current_megacell = GetNextMegacell(n);

  // Now delete those textures if need be
  if (answer == IDYES) {
    uint8_t can_delete[MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT];

    memset(can_delete, 0, MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT);

    for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++) {
      int mx = i % MAX_MEGACELL_WIDTH;
      int my = i / MAX_MEGACELL_WIDTH;

      if (mx >= Megacells[n].width || my >= Megacells[n].height)
        continue;

      int index = Megacells[n].texture_handles[i];

      if (index == 0 || index == 1)
        continue;

      int tl;

      tl = mng_FindTrackLock(GameTextures[index].name, PAGETYPE_TEXTURE);

      if (tl == -1) {
        // We need to lock this texture
        AutoChecking = 2;
        D3EditState.texdlg_texture = index;
        texdlg.OnLock();
        if (!TlockState)
          continue;
        tl = mng_FindTrackLock(GameTextures[index].name, PAGETYPE_TEXTURE);
        can_delete[i] = 1;
      } else {
        can_delete[i] = 1;
      }
    }

    int num_to_delete = 0;
    char *texnames[MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT];
    uint16_t texindices[MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT];

    for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++) {
      texnames[i] = (char *)mem_malloc(PAGENAME_LEN);
      ASSERT(texnames[i]);
      if (!can_delete[i])
        continue;

      int index = Megacells[n].texture_handles[i];

      int duplicate = 0;
      for (int k = 0; k < num_to_delete && !duplicate; k++) {
        if (texindices[k] == index)
          duplicate = 1;
      }

      if (duplicate)
        continue;

      strcpy(texnames[num_to_delete], GameTextures[index].name);
      texindices[num_to_delete] = index;
      num_to_delete++;
    }

    mng_DeleteTexPageSeries(texnames, num_to_delete, 0);
    mng_DeleteTexPageSeries(texnames, num_to_delete, 1);
    mng_DeletePagelockSeries(texnames, num_to_delete, PAGETYPE_TEXTURE);

    // Now free all pagelocks and textures
    for (i = 0; i < num_to_delete; i++) {
      tl = mng_FindTrackLock(GameTextures[texindices[i]].name, PAGETYPE_TEXTURE);

      if (tl != -1)
        mng_FreeTrackLock(tl);

      if (GameTextures[texindices[i]].flags & TF_ANIMATED)
        FreeVClip(GameTextures[texindices[i]].bm_handle);
      else
        bm_FreeBitmap(GameTextures[texindices[i]].bm_handle);

      FreeTexture(texindices[i]);
    }

    for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++)
      mem_free(texnames[i]);
  }

  AutoChecking = 0;
  FreeMegacell(n);
  mng_EraseLocker();

  OutrageMessageBox("Megacell deleted.");

  UpdateDialog();
}

void CMegacellDialog::OnNextMegacell() {
  D3EditState.current_megacell = GetNextMegacell(D3EditState.current_megacell);
  UpdateDialog();
}

void CMegacellDialog::OnPreviousMegacell() {
  D3EditState.current_megacell = GetPrevMegacell(D3EditState.current_megacell);
  UpdateDialog();
}

void CMegacellDialog::OnSelendokMegacellPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_MEGACELL_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_MEGACELL_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindMegacellName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted megacell list, but probably nothing.");
    UpdateDialog();
  }

  D3EditState.current_megacell = i;
  UpdateDialog();
}

void CMegacellDialog::OnMegacellsOut() {}

void CMegacellDialog::OnKillfocusMegacellNameEdit() {
  CEdit *ebox;
  int n = D3EditState.current_megacell;
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this megacell locked, if not reset name and bail
  int p = mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL);
  if (p == -1) {
    OutrageMessageBox("You must lock this megacell if you wish to change its name.");
    CEdit *ebox = (CEdit *)GetDlgItem(IDC_MEGACELL_NAME_EDIT);
    ebox->SetWindowText(Megacells[n].name);
    return;
  }

  // Get the new name
  ebox = (CEdit *)GetDlgItem(IDC_MEGACELL_NAME_EDIT);
  ebox->GetWindowText(name, PAGENAME_LEN);

  // Check to see if there is already a cell with this name.  If so, reset and bail
  if (FindMegacellName(name) != -1) {
    OutrageMessageBox("There already is a cell with that name...choose another name.");

    CEdit *ebox = (CEdit *)GetDlgItem(IDC_MEGACELL_NAME_EDIT);
    ebox->SetWindowText(Megacells[n].name);
    return;
  }

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Megacells[n].name);
  pl.pagetype = PAGETYPE_MEGACELL;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Megacells[n].name, name, PAGETYPE_MEGACELL);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Megacells[n].name);
    strcpy(Megacells[n].name, name);

    mng_ReplacePage(oldname, Megacells[n].name, n, PAGETYPE_MEGACELL, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Megacells[n].name, name);
  mng_EraseLocker();

  UpdateDialog();
}

void CMegacellDialog::OnKillfocusMegaWidthEdit() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.current_megacell;
  int width;

  ebox = (CEdit *)GetDlgItem(IDC_MEGA_WIDTH_EDIT);
  ebox->GetWindowText(name, 20);

  width = atoi(name);

  if (width < 0)
    width = 2;
  if (width > 8)
    width = 8;
  Megacells[n].width = width;

  UpdateDialog();
}

void CMegacellDialog::OnKillfocusMegaHeightEdit() {
  CEdit *ebox;
  char name[20];
  int n = D3EditState.current_megacell;
  int height;

  ebox = (CEdit *)GetDlgItem(IDC_MEGA_HEIGHT_EDIT);
  ebox->GetWindowText(name, 20);

  height = atoi(name);

  if (height < 0)
    height = 2;
  if (height > 8)
    height = 8;
  Megacells[n].height = height;

  UpdateDialog();
}

BOOL CMegacellDialog::DestroyWindow() {
  SaveMegacellsOnClose();

  return CDialog::DestroyWindow();
}

BOOL CMegacellDialog::OnInitDialog() {
  static int first_time = 1;
  CDialog::OnInitDialog();

  mngs_megacell_page megacellpage;

  // Remap all megacells
  if (Network_up && first_time) {
    for (int i = 0; i < MAX_MEGACELLS; i++) {
      if (Megacells[i].used) {
        if (Megacells[i].texture_handles[0] > 0)
          continue;

        if (mng_FindSpecificMegacellPage(Megacells[i].name, &megacellpage, 1)) {
          if (!mng_AssignMegacellPageToMegacell(&megacellpage, i))
            Int3(); // Get Jason
        } else if (mng_FindSpecificMegacellPage(Megacells[i].name, &megacellpage, 0)) {
          if (!mng_AssignMegacellPageToMegacell(&megacellpage, i))
            Int3(); // Get Jason
        }
      }
    }
  }

  first_time = 0;
  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CMegacellDialog::SaveMegacellsOnClose() {
  int i, t;
  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_TEXTURE) {
      t = FindTextureName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);

      mng_ReplacePage(GameTextures[t].name, GameTextures[t].name, t, PAGETYPE_TEXTURE, 1);
    }

    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_MEGACELL) {
      t = FindMegacellName(GlobalTrackLocks[i].name);

      mng_DeletePage(Megacells[t].name, PAGETYPE_MEGACELL, 1);
      ASSERT(t != -1);

      mng_ReplacePage(Megacells[t].name, Megacells[t].name, t, PAGETYPE_MEGACELL, 1);
    }
  }
}

void CMegacellDialog::OnLButtonDown(UINT nFlags, CPoint point) {
  m_CheckForTextureList = 1;
  m_CheckX = point.x;
  m_CheckY = point.y;

  CDialog::OnLButtonDown(nFlags, point);

  UpdateDialog();

  CDialog::OnLButtonDown(nFlags, point);
}
void CMegacellDialog::UpdateDialog() {
  CEdit *ebox;
  CButton *bbox;
  int n = D3EditState.current_megacell;
  char str[50];

  UpdateTextureView();

  if (Num_megacells < 1) {
    bbox = (CButton *)GetDlgItem(IDC_NEXT_MEGACELL);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_PREVIOUS_MEGACELL);
    bbox->EnableWindow(FALSE);

    m_CheckForTextureList = 0;

    return;
  } else {
    bbox = (CButton *)GetDlgItem(IDC_NEXT_MEGACELL);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_PREVIOUS_MEGACELL);
    bbox->EnableWindow(TRUE);
  }

  if (!Megacells[n].used)
    n = D3EditState.current_megacell = GetNextMegacell(n);

  ebox = (CEdit *)GetDlgItem(IDC_MEGACELL_NAME_EDIT);
  ebox->SetWindowText(Megacells[n].name);

  ebox = (CEdit *)GetDlgItem(IDC_MEGA_WIDTH_EDIT);
  sprintf(str, "%d", Megacells[n].width);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_MEGA_HEIGHT_EDIT);
  sprintf(str, "%d", Megacells[n].height);
  ebox->SetWindowText(str);

  bbox = (CButton *)GetDlgItem(IDC_CHECKIN_MEGACELL);
  if (mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL) == -1) {
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_MEGACELL);
    bbox->EnableWindow(TRUE);
  } else {
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_MEGACELL);
    bbox->EnableWindow(FALSE);
  }

  SendDlgItemMessage(IDC_MEGACELL_PULLDOWN, CB_RESETCONTENT, 0, 0);

  for (int i = 0; i < MAX_MEGACELLS; i++) {
    if (Megacells[i].used)
      SendDlgItemMessage(IDC_MEGACELL_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Megacells[i].name);
  }
  SendDlgItemMessage(IDC_MEGACELL_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Megacells[n].name);

  UpdateMegacellView();
}

#define TEXTURES_PER_ROW 4

void CMegacellDialog::UpdateTextureView() {
  int n = D3EditState.texdlg_texture;
  CWnd *texwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  int update_listbox = 1;

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  if (1 || update_listbox) {

    texwnd = GetDlgItem(IDC_TEXTURE_LISTBOX);
    texwnd->GetWindowRect(&rect);
    ScreenToClient(&rect);
    w = rect.right - rect.left;
    h = rect.bottom - rect.top;

    int texwidth = (w - 1) / 4;
    int texheight = (h - 1) / 8;

    Desktop_surf->clear(rect.left, rect.top, w, h);

    int texnum = m_TexStart;
    int count = 0, done = 0;

    while (!done) {
      m_TextureSurf.create(texwidth, texheight, BPP_16);

      bm_handle = GetTextureBitmap(texnum, 0);
      m_TextureSurf.load(bm_handle);

      x = 1 + rect.left + ((count % TEXTURES_PER_ROW) * texwidth);
      y = 1 + rect.top + ((count / TEXTURES_PER_ROW) * texheight);

      if (m_CheckForTextureList) {

        if (m_CheckX >= x && m_CheckX <= (x + texwidth) && m_CheckY >= y && m_CheckY <= (y + texheight)) {
          m_CheckForTextureList = 0;
          D3EditState.texdlg_texture = texnum;
          m_TextureSurf.free();
          Desktop_surf->attach_to_window((unsigned)NULL);
          UpdateDialog();
          return;
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
      m_TextureSurf.free();
      count++;
      if (count == TEXTURES_PER_ROW * 8)
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

  Desktop_surf->attach_to_window((unsigned)NULL);
}

void CMegacellDialog::TextureListUp(int rows) {
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

void CMegacellDialog::TextureListDown(int rows) {
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

void CMegacellDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
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

void CMegacellDialog::UpdateMegacellView() {
  int n = D3EditState.current_megacell;
  CWnd *texwnd;
  RECT rect;
  int x, y, bm_handle, w, h;
  int megawidth = Megacells[n].width;
  int megaheight = Megacells[n].height;
  int i, t;

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  texwnd = GetDlgItem(IDC_MEGACELL_VIEW);
  texwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);
  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  int texwidth = w / megawidth;
  int texheight = h / megaheight;

  // Don't have to clear if we're overwriting the whole area!
  // if (megawidth<8 || megaheight<8)
  //	Desktop_surf->clear(rect.left,rect.top,w,h);

  for (i = 0; i < megaheight; i++) {
    for (t = 0; t < megawidth; t++) {
      m_TextureSurf.create(texwidth, texheight, BPP_16);

      bm_handle = GetTextureBitmap(Megacells[n].texture_handles[i * MAX_MEGACELL_WIDTH + t], 0);
      m_TextureSurf.load(bm_handle);

      x = 1 + rect.left + (t * texwidth);
      y = 1 + rect.top + (i * texheight);

      if (m_CheckForTextureList) {

        if (m_CheckX >= x && m_CheckX <= (x + texwidth) && m_CheckY >= y && m_CheckY <= (y + texheight)) {
          m_CheckForTextureList = 0;
          Megacells[n].texture_handles[i * MAX_MEGACELL_WIDTH + t] = D3EditState.texdlg_texture;
          m_TextureSurf.free();
          Desktop_surf->attach_to_window((unsigned)NULL);
          UpdateDialog();
          return;
        }
      }

      // Draw a separation line on the right and bottom side
      {
        grViewport *vport = new grViewport(&m_TextureSurf);

        int x = 0, y = 0;

        vport->lock();
        vport->line(GR_RGB(0, 0, 0), 0, vport->height() - 1, vport->width() - 1, vport->height() - 1);
        vport->line(GR_RGB(0, 0, 0), vport->width() - 1, 0, vport->width() - 1, vport->height() - 1);

        vport->unlock();
        delete vport;
      }

      Desktop_surf->blt(x, y, &m_TextureSurf);

      m_TextureSurf.free();
    }
  }

  m_CheckForTextureList = 0;
  Desktop_surf->attach_to_window((unsigned)NULL);
}

void CMegacellDialog::OnPaint() {
  CPaintDC dc(this); // device context for painting

  UpdateDialog();
  // Do not call CDialog::OnPaint() for painting messages
}

void CMegacellDialog::OnRemapMegacell() {
  int n = D3EditState.current_megacell;
  mngs_megacell_page megacellpage;

  if (mng_FindSpecificMegacellPage(Megacells[n].name, &megacellpage, 1)) {
    if (!mng_AssignMegacellPageToMegacell(&megacellpage, n))
      Int3(); // Get Jason
  } else if (mng_FindSpecificMegacellPage(Megacells[n].name, &megacellpage, 0)) {
    if (!mng_AssignMegacellPageToMegacell(&megacellpage, n))
      Int3(); // Get Jason
  } else
    OutrageMessageBox("This megacell was not found in the local table file.");

  UpdateDialog();
}

void CMegacellDialog::OnRotateMegacell() {
  int n = D3EditState.current_megacell;
  int buffer[MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT];
  int i;

  if (!Megacells[n].used)
    return;

  for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++)
    buffer[i] = 0;

  int oldwidth = Megacells[n].width;
  int oldheight = Megacells[n].height;

  for (i = 0; i < MAX_MEGACELL_HEIGHT; i++) {
    for (int t = 0; t < MAX_MEGACELL_WIDTH; t++) {
      buffer[((MAX_MEGACELL_HEIGHT - 1) - t) * MAX_MEGACELL_WIDTH + i] =
          Megacells[n].texture_handles[i * MAX_MEGACELL_WIDTH + t];
    }
  }

  for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++)
    Megacells[n].texture_handles[i] = buffer[i];

  Megacells[n].width = oldheight;
  Megacells[n].height = oldwidth;

  UpdateDialog();
}

void CMegacellDialog::OnCopyMegacell() {
  int n = D3EditState.current_megacell;
  int i;

  if (!Megacells[n].used)
    return;

  m_CopyMegacell.width = Megacells[n].width;
  m_CopyMegacell.height = Megacells[n].height;

  for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++)
    m_CopyMegacell.texture_handles[i] = Megacells[n].texture_handles[i];

  mprintf(0, "Megacell copied.\n");
}

void CMegacellDialog::OnPasteMegacell() {
  int n = D3EditState.current_megacell;
  int i;

  if (!Megacells[n].used)
    return;

  Megacells[n].width = m_CopyMegacell.width;
  Megacells[n].height = m_CopyMegacell.height;

  for (i = 0; i < MAX_MEGACELL_WIDTH * MAX_MEGACELL_HEIGHT; i++)
    Megacells[n].texture_handles[i] = m_CopyMegacell.texture_handles[i];

  UpdateDialog();
}

void CMegacellDialog::CheckinTexture(int n, int tracklock_num) {
  mngs_Pagelock temp_pl;
  int r;

  if (!GameTextures[n].used) {
    mprintf(0, "Whoa, trying to save non-used texture %s!\n", GameTextures[n].name);
    return;
  }

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

          fname = LocalManageGraphicsDir /  GameBitmaps[GameTextures[n].bm_handle].name;
          bm_SaveFileBitmap(fname, GameTextures[n].bm_handle);
        }

        mprintf(0, "%s texture checked in.\n", GameTextures[n].name);
        int dret = mng_DeletePage(GameTextures[n].name, PAGETYPE_TEXTURE, 1);

        ASSERT(dret == 1);

        mng_FreeTrackLock(tracklock_num);
      }
    }
  }
}

void CMegacellDialog::OnImportTiny() {
  char filename[255];
  int n = D3EditState.current_megacell;
  int megawidth = Megacells[n].width;
  int megaheight = Megacells[n].height;
  int src_handle;
  int count = 0;
  int i, t;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  if (Num_megacells < 1) {
    OutrageMessageBox("You must first create a megacell before using this feature.");
    return;
  }

  if ((mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL)) == -1) {
    OutrageMessageBox("You must have this megacell locked before you can import!");
    return;
  }

  CString filter = "Descent III files (*.tga,*.bbm,*.lbm,*.ogf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  src_handle = bm_AllocLoadFileBitmap(filename, 0);

  if (src_handle < 0) {
    OutrageMessageBox("Couldn't read that bitmap!");
    return;
  }

  int w = bm_w(src_handle, 0);
  int h = bm_h(src_handle, 0);

  float width_per_cell = (float)w / (float)megawidth;
  float height_per_cell = (float)h / (float)megaheight;

  for (i = 0; i < megaheight; i++) {
    for (t = 0; t < megawidth; t++) {
      float startx = width_per_cell * t;
      float starty = height_per_cell * i;

      float u = startx;
      float v = starty;

      float du = width_per_cell / 32.0;
      float dv = height_per_cell / 32.0;

      int bm_handle = bm_AllocBitmap(32, 32, 0);

      ASSERT(bm_handle >= 0);

      uint16_t *dest_data = bm_data(bm_handle, 0);
      uint16_t *src_data = bm_data(src_handle, 0);

      for (int ty = 0; ty < 32; ty++, u = startx, v += dv) {
        for (int tx = 0; tx < 32; tx++, u += du) {
          int cu = u;
          int cv = v;

          uint16_t pix = src_data[cv * w + cu];
          dest_data[ty * 32 + tx] = pix;
        }
      }

      // Alloc a texture and assign it this bitmap handle
      int tex_handle;
      tex_handle = AllocTexture();
      ASSERT(tex_handle > 0);

      GameTextures[tex_handle].flags &= ~(TF_TEXTURE_TYPES);
      GameTextures[tex_handle].flags |= TF_TEXTURE_32;
      GameTextures[tex_handle].flags |= TF_TERRAIN;

      GameTextures[tex_handle].bm_handle = bm_handle;
      Megacells[n].texture_handles[i * MAX_MEGACELL_WIDTH + t] = tex_handle;

      // Find a unique name for this texture

      int finding_name = 1;
      char cur_name[255];

      while (finding_name) {
        sprintf(cur_name, "%s%d", Megacells[n].name, count);
        if (FindTextureName(cur_name) != -1)
          count++;
        else
          finding_name = 0;
      }
      strcpy(GameTextures[tex_handle].name, cur_name);
      bm_ChangeEndName(Megacells[n].name, filename);
      strcpy(GameBitmaps[bm_handle].name, filename);

      // Save this textures image locally
      sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
        GameBitmaps[GameTextures[tex_handle].bm_handle].name);
      mprintf(0, "Saving bitmap %s from megacell!\n", GameBitmaps[bm_handle].name);
      bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);

      // Allocate a track lock for this texture
      mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);
    }
  }

  bm_FreeBitmap(src_handle);

  UpdateDialog();
}

BOOL CMegacellDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
  WinHelp(HID_MEGACELLDLG, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

#define SKY_TEXTURE_SIZE 128
void CMegacellDialog::OnImportSky() {
  char filename[255];
  int n = D3EditState.current_megacell;
  int megawidth = Megacells[n].width;
  int megaheight = Megacells[n].height;
  int src_handle;
  int count = 0;
  int i, t;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  if (Num_megacells < 1) {
    OutrageMessageBox("You must first create a megacell before using this feature.");
    return;
  }

  if (megawidth != 2 || megaheight != 2) {
    OutrageMessageBox("All sky dome megacells must be 2x2 in dimensions!");
    return;
  }

  if ((mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL)) == -1) {
    OutrageMessageBox("You must have this megacell locked before you can import!");
    return;
  }

  CString filter = "Descent III files (*.tga,*.bbm,*.lbm,*.ogf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  src_handle = bm_AllocLoadFileBitmap(filename, 0);

  if (src_handle < 0) {
    OutrageMessageBox("Couldn't read that bitmap!");
    return;
  }

  int w = bm_w(src_handle, 0);
  int h = bm_h(src_handle, 0);

  float width_per_cell = (float)w / (float)megawidth;
  float height_per_cell = (float)h / (float)megaheight;

  for (i = 0; i < megaheight; i++) {
    for (t = 0; t < megawidth; t++) {
      float startx = width_per_cell * t;
      float starty = height_per_cell * i;

      float u = startx;
      float v = starty;

      float du = width_per_cell / (float)SKY_TEXTURE_SIZE;
      float dv = height_per_cell / (float)SKY_TEXTURE_SIZE;

      int bm_handle = bm_AllocBitmap(SKY_TEXTURE_SIZE, SKY_TEXTURE_SIZE, 0);

      ASSERT(bm_handle >= 0);

      uint16_t *dest_data = bm_data(bm_handle, 0);
      uint16_t *src_data = bm_data(src_handle, 0);

      for (int ty = 0; ty < SKY_TEXTURE_SIZE; ty++, u = startx, v += dv) {
        for (int tx = 0; tx < SKY_TEXTURE_SIZE; tx++, u += du) {
          int cu = u;
          int cv = v;

          uint16_t pix = src_data[cv * w + cu];
          dest_data[ty * SKY_TEXTURE_SIZE + tx] = pix;
        }
      }

      // Alloc a texture and assign it this bitmap handle
      int tex_handle;
      tex_handle = AllocTexture();
      ASSERT(tex_handle > 0);

      GameTextures[tex_handle].flags |= TF_TERRAIN;

      GameTextures[tex_handle].bm_handle = bm_handle;
      Megacells[n].texture_handles[i * MAX_MEGACELL_WIDTH + t] = tex_handle;

      // Find a unique name for this texture

      int finding_name = 1;
      char cur_name[255];

      while (finding_name) {
        sprintf(cur_name, "%s%d", Megacells[n].name, count);
        if (FindTextureName(cur_name) != -1)
          count++;
        else
          finding_name = 0;
      }
      strcpy(GameTextures[tex_handle].name, cur_name);
      bm_ChangeEndName(Megacells[n].name, filename);
      strcpy(GameBitmaps[bm_handle].name, filename);

      // Save this textures image locally
      sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
        GameBitmaps[GameTextures[tex_handle].bm_handle].name);
      mprintf(0, "Saving bitmap %s from megacell!\n", GameBitmaps[bm_handle].name);
      bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);

      // Allocate a track lock for this texture
      mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);
    }
  }

  bm_FreeBitmap(src_handle);

  UpdateDialog();
}

#define SKY_BAND_SIZE 64
void CMegacellDialog::OnImportSkyBand() {
  char filename[255];
  int n = D3EditState.current_megacell;
  int megawidth = Megacells[n].width;
  int megaheight = Megacells[n].height;
  int src_handle;
  int count = 0;
  int t;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  if (Num_megacells < 1) {
    OutrageMessageBox("You must first create a megacell before using this feature.");
    return;
  }

  if (megawidth != 8 || megaheight != 2) {
    OutrageMessageBox("All sky band megacells must be 8x2 in dimensions!");
    return;
  }

  if ((mng_FindTrackLock(Megacells[n].name, PAGETYPE_MEGACELL)) == -1) {
    OutrageMessageBox("You must have this megacell locked before you can import!");
    return;
  }

  CString filter = "Descent III files (*.tga,*.bbm,*.lbm,*.ogf,*.pcx)|*.pcx;*.tga;*.bbm;*.lbm;*.ogf;||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_bitmap_dir, sizeof(Current_bitmap_dir)))
    return;

  //	Okay, we selected a file. Lets do what needs to be done here.
  src_handle = bm_AllocLoadFileBitmap(filename, 0);

  if (src_handle < 0) {
    OutrageMessageBox("Couldn't read that bitmap!");
    return;
  }

  int w = bm_w(src_handle, 0);
  int h = bm_h(src_handle, 0);

  float width_per_cell = (float)w / (float)16;
  float height_per_cell = (float)h / (float)1;

  for (t = 0; t < 16; t++) {
    float startx = width_per_cell * t;
    float starty = 0;

    float u = startx;
    float v = starty;

    float du = width_per_cell / (float)SKY_BAND_SIZE;
    float dv = height_per_cell / (float)SKY_BAND_SIZE;

    int bm_handle = bm_AllocBitmap(SKY_BAND_SIZE, SKY_BAND_SIZE, 0);

    ASSERT(bm_handle >= 0);

    uint16_t *dest_data = bm_data(bm_handle, 0);
    uint16_t *src_data = bm_data(src_handle, 0);

    for (int ty = 0; ty < SKY_BAND_SIZE; ty++, u = startx, v += dv) {
      for (int tx = 0; tx < SKY_BAND_SIZE; tx++, u += du) {
        int cu = u;
        int cv = v;

        uint16_t pix = src_data[cv * w + cu];
        dest_data[ty * SKY_BAND_SIZE + tx] = pix;
      }
    }

    // Alloc a texture and assign it this bitmap handle
    int tex_handle;
    tex_handle = AllocTexture();
    ASSERT(tex_handle > 0);

    GameTextures[tex_handle].flags &= ~(TF_TEXTURE_TYPES);
    GameTextures[tex_handle].flags |= (TF_TERRAIN | TF_TEXTURE_64);
    GameTextures[tex_handle].bm_handle = bm_handle;

    int row = t / MAX_MEGACELL_WIDTH;
    int column = t % MAX_MEGACELL_WIDTH;

    Megacells[n].texture_handles[row * MAX_MEGACELL_WIDTH + column] = tex_handle;

    // Find a unique name for this texture

    int finding_name = 1;
    char cur_name[255];

    while (finding_name) {
      sprintf(cur_name, "%s%d", Megacells[n].name, count);
      if (FindTextureName(cur_name) != -1)
        count++;
      else
        finding_name = 0;
    }
    strcpy(GameTextures[tex_handle].name, cur_name);
    bm_ChangeEndName(Megacells[n].name, filename);
    strcpy(GameBitmaps[bm_handle].name, filename);

    // Save this textures image locally
    sprintf(filename, "%s\\%s", LocalManageGraphicsDir.u8string().c_str(),
      GameBitmaps[GameTextures[tex_handle].bm_handle].name);
    mprintf(0, "Saving bitmap %s from megacell!\n", GameBitmaps[bm_handle].name);
    bm_SaveFileBitmap(filename, GameTextures[tex_handle].bm_handle);

    // Allocate a track lock for this texture
    mng_AllocTrackLock(cur_name, PAGETYPE_TEXTURE);
  }

  bm_FreeBitmap(src_handle);

  UpdateDialog();
}
