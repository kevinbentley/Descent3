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

// AmbientSoundPattern.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "AmbientSoundPattern.h"
#include "AmbientSoundElement.h"
#include "EditLineDialog.h"
#include "ambient.h"
#include "ssl_lib.h"
#include "pserror.h"
#include "gamefilepage.h"
#include "ddio.h"
#include "mem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmbientSoundPattern dialog

CAmbientSoundPattern::CAmbientSoundPattern(CWnd *pParent /*=NULL*/) : CDialog(CAmbientSoundPattern::IDD, pParent) {
  //{{AFX_DATA_INIT(CAmbientSoundPattern)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CAmbientSoundPattern::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAmbientSoundPattern)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAmbientSoundPattern, CDialog)
//{{AFX_MSG_MAP(CAmbientSoundPattern)
ON_CBN_SELENDOK(IDC_ASP_LIST, OnSelendokASPList)
ON_BN_CLICKED(IDC_ASP_CHECK_IN, OnASPCheckIn)
ON_BN_CLICKED(IDC_ASP_DELETE, OnASPDelete)
ON_BN_CLICKED(IDC_ASP_EDIT_ELEMENT, OnASPEditElement)
ON_BN_CLICKED(IDC_ASP_LOCK, OnASPLock)
ON_BN_CLICKED(IDC_ASP_NEW, OnASPNew)
ON_BN_CLICKED(IDC_ASP_NEW_ELEMENT, OnASPNewElement)
ON_BN_CLICKED(IDC_ASP_RENAME, OnASPRename)
ON_LBN_SELCHANGE(IDC_ASP_ELEMENT_LIST, OnSelchangeASPElementList)
ON_BN_CLICKED(IDC_ASP_DELETE_ELEMENT, OnASPDeleteElement)
ON_BN_CLICKED(IDC_ASP_UNDO_LOCK, OnASPUndoLock)
ON_EN_KILLFOCUS(IDC_ASP_MAX_DELAY, OnKillfocusASPMaxDelay)
ON_EN_KILLFOCUS(IDC_ASP_MIN_DELAY, OnKillfocusASPMinDelay)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmbientSoundPattern message handlers

BOOL CAmbientSoundPattern::OnInitDialog() {
  CDialog::OnInitDialog();

  m_current_asp = m_current_element = -1;

  m_locked = (mng_FindTrackLock(AMBIENT_FILE_NAME, PAGETYPE_GAMEFILE) != -1);

  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CAmbientSoundPattern::UpdateDialog() {
  int i;

  // Build the ambient sound list
  CComboBox *asplist = (CComboBox *)GetDlgItem(IDC_ASP_LIST);
  asplist->ResetContent();
  for (i = 0; i < Num_ambient_sound_patterns; i++)
    if (Ambient_sound_patterns[i].name[0]) {
      asplist->AddString(Ambient_sound_patterns[i].name);
      if (m_current_asp == -1)
        m_current_asp = i;
    }
  if (m_current_asp != -1)
    asplist->SelectString(-1, Ambient_sound_patterns[m_current_asp].name);

  // Write out elements for current ASP
  CListBox *aselist = (CListBox *)GetDlgItem(IDC_ASP_ELEMENT_LIST);
  char tbuf[100];
  asp *asp = &Ambient_sound_patterns[m_current_asp];
  aselist->ResetContent();
  for (i = 0; i < asp->num_sounds; i++) {
    ase *ase = &asp->sounds[i];
    sprintf(tbuf, "%s:   vol=%.2f,%.2f   prob=%d", Sounds[ase->handle].name, ase->min_volume, ase->max_volume,
            ase->probability);
    aselist->AddString(tbuf);
  }

  // Write out the delay values
  CEdit *ebox = (CEdit *)GetDlgItem(IDC_ASP_MIN_DELAY);
  char buf[20];
  sprintf(buf, "%.1f", asp->min_delay);
  ebox->SetWindowText(buf);

  ebox = (CEdit *)GetDlgItem(IDC_ASP_MAX_DELAY);
  sprintf(buf, "%.1f", asp->max_delay);
  ebox->SetWindowText(buf);

  // Select current element
  if (aselist->GetCount() > 0)
    aselist->SetCurSel(m_current_element);

  // Enable/disable editing buttons
  ((CButton *)GetDlgItem(IDC_ASP_DELETE))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_EDIT_ELEMENT))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_NEW))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_NEW_ELEMENT))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_RENAME))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_DELETE_ELEMENT))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_MIN_DELAY))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_MAX_DELAY))->EnableWindow(m_locked);

  // Enable/disable locking buttons
  ((CButton *)GetDlgItem(IDC_ASP_CHECK_IN))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_UNDO_LOCK))->EnableWindow(m_locked);
  ((CButton *)GetDlgItem(IDC_ASP_LOCK))->EnableWindow(!m_locked);
}

void CAmbientSoundPattern::OnSelendokASPList() {
  char name[200];

  CComboBox *asplist = (CComboBox *)GetDlgItem(IDC_ASP_LIST);

  asplist->GetLBText(asplist->GetCurSel(), name);
  m_current_asp = FindAmbientSoundPattern(name);

  if (Ambient_sound_patterns[m_current_asp].num_sounds)
    m_current_element = 0;
  else
    m_current_element = -1;

  UpdateDialog();
}

void CAmbientSoundPattern::OnASPRename() {
  if (!InputString(Ambient_sound_patterns[m_current_asp].name, sizeof(Ambient_sound_patterns[m_current_asp].name),
                   "Ambient Sound Pattern", "Enter a new name"))
    return;

  UpdateDialog();
}

void CAmbientSoundPattern::OnSelchangeASPElementList() {
  CListBox *lb = (CListBox *)GetDlgItem(IDC_ASP_ELEMENT_LIST);

  m_current_element = lb->GetCurSel();
}

void CAmbientSoundPattern::OnASPDelete() {
  if (OutrageMessageBox(MBOX_YESNO, "Do you really want to delete the ambient sound pattern '%s'?",
                        AmbientSoundPatternName(m_current_asp)) == IDYES) {
    asp *asp = &Ambient_sound_patterns[m_current_asp];

    asp->name[0] = 0; // null string for name
    mem_free(asp->sounds);
    asp->num_sounds = 0;
    m_current_asp = -1;

    UpdateDialog();
  }
}

void CAmbientSoundPattern::OnASPNew() {
  asp *asp = &Ambient_sound_patterns[Num_ambient_sound_patterns];

  if (InputString(asp->name, sizeof(asp->name), "Ambient Sound Pattern", "Enter a name for your new pattern"))
    if (asp->name[0]) {
      asp->num_sounds = 0;
      asp->min_delay = asp->max_delay = 0.0;
      m_current_asp = Num_ambient_sound_patterns++;
      UpdateDialog();
    }
}

void CAmbientSoundPattern::OnASPNewElement() {
  asp *asp = &Ambient_sound_patterns[m_current_asp];
  ase new_element;

  new_element.handle = -1;
  new_element.min_volume = new_element.max_volume = 1.0;
  new_element.probability = 50;

  CAmbientSoundElement dlg(&new_element);

  Editor()->pause();
  dlg.DoModal();
  Editor()->resume();

  if (new_element.handle != -1) {

    ase *new_sounds = (ase *)mem_malloc(sizeof(*new_sounds) * (asp->num_sounds + 1));

    for (int s = 0; s < asp->num_sounds; s++)
      new_sounds[s] = asp->sounds[s];

    mem_free(asp->sounds);

    asp->sounds = new_sounds;
    asp->sounds[s] = new_element;

    asp->num_sounds++;

    m_current_element = s;

    UpdateDialog();
  }
}

void CAmbientSoundPattern::OnASPEditElement() {
  if (m_current_element > -1) {
    CAmbientSoundElement dlg(&Ambient_sound_patterns[m_current_asp].sounds[m_current_element]);

    Editor()->pause();
    dlg.DoModal();
    Editor()->resume();

    UpdateDialog();
  }
}

void CAmbientSoundPattern::OnASPDeleteElement() {
  asp *asp = &Ambient_sound_patterns[m_current_asp];
  ase *new_sounds;

  if (m_current_element > -1) {
    if (OutrageMessageBox(MBOX_YESNO, "Do you really want to delete sound '%s' from pattern '%s'?",
                          Sounds[asp->sounds[m_current_element].handle].name, asp->name) == IDYES) {
      new_sounds = (ase *)mem_malloc(sizeof(*new_sounds) * (asp->num_sounds - 1));

      for (int s = 0; s < m_current_element; s++)
        new_sounds[s] = asp->sounds[s];

      for (; s < asp->num_sounds - 1; s++)
        new_sounds[s] = asp->sounds[s + 1];

      mem_free(asp->sounds);

      asp->sounds = new_sounds;

      asp->num_sounds--;

      UpdateDialog();
    }
  }
}

void CAmbientSoundPattern::OnKillfocusASPMinDelay() {
  asp *asp = &Ambient_sound_patterns[m_current_asp];

  CEdit *ebox;
  char buf[20];

  ebox = (CEdit *)GetDlgItem(IDC_ASP_MIN_DELAY);
  ebox->GetWindowText(buf, sizeof(buf));

  asp->min_delay = atof(buf);

  UpdateDialog();
}

void CAmbientSoundPattern::OnKillfocusASPMaxDelay() {
  asp *asp = &Ambient_sound_patterns[m_current_asp];

  CEdit *ebox;
  char buf[20];

  ebox = (CEdit *)GetDlgItem(IDC_ASP_MAX_DELAY);
  ebox->GetWindowText(buf, sizeof(buf));

  asp->max_delay = atof(buf);

  UpdateDialog();
}

void CAmbientSoundPattern::OnCancel() {
  // Re-read old data
  ReadAmbientData();

  CDialog::OnCancel();
}

void CAmbientSoundPattern::OnOK() {
  // Verify probabilities
  for (int p = 0; p < Num_ambient_sound_patterns; p++) {
    asp *asp = &Ambient_sound_patterns[p];
    if (asp->num_sounds) {
      int prob = 0;

      for (int s = 0; s < asp->num_sounds; s++)
        prob += asp->sounds[s].probability;

      if (prob != 100) {
        OutrageMessageBox("Error:  the probabilities for pattern '%s' don't add up to 100.", asp->name);
        return;
      }
    }
  }

  // Update the data
  WriteAmbientData();

  CDialog::OnOK();
}

void CAmbientSoundPattern::OnASPLock() {
  int n;
  mngs_Pagelock temp_pl;
  mngs_gamefile_page gamefilepage;
  int r;

  // Find where it is in the list
  n = FindGamefileName(AMBIENT_FILE_NAME);

  if (n == -1) {
    Int3(); // Get Matt or Jason - AMBIENT file name is no longer in the table file!
    return;
  }

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, AMBIENT_FILE_NAME);
  temp_pl.pagetype = PAGETYPE_GAMEFILE;

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

    // Search thru the net pagefile and get a new copy in RAM in case anyone
    // changed it since we started the editor
    if (mng_FindSpecificGamefilePage(temp_pl.name, &gamefilepage, 0)) {

      if (mng_AssignGamefilePageToGamefile(&gamefilepage, n)) {
        if (!mng_ReplacePage(Gamefiles[n].name, Gamefiles[n].name, n, PAGETYPE_GAMEFILE, 1)) {
          OutrageMessageBox("There was problem writing that page locally!");
          mng_EraseLocker();
          return;
        } else {

          if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
            MessageBox(ErrorString, "Error!");
            mng_EraseLocker();
            return;
          }
        }
        OutrageMessageBox("Gamefile locked.");
      } else
        OutrageMessageBox(
            "There was a problem loading this gamefile.  You might encounter problems in dealing with it.  Good luck!");

      mng_AllocTrackLock(Gamefiles[n].name, PAGETYPE_GAMEFILE);
      UpdateDialog();
    } else
      OutrageMessageBox("Couldn't find that gamefile in the table file!");
  }

  mng_EraseLocker();

  // Read the data again in case we just got a newer file
  ReadAmbientData();

  m_locked = 1;

  UpdateDialog();
}

void CAmbientSoundPattern::OnASPCheckIn() {
  // Write the updated data to the file
  WriteAmbientData();

  // Find where it is in the files index
  int n = FindGamefileName(AMBIENT_FILE_NAME);

  if (n == -1) {
    Int3(); // Get Matt or Jason - AMBIENT file name is no longer in the table file!
    return;
  }

  mngs_Pagelock temp_pl;
  int r;

  // Lock the network table file
  if (!mng_MakeLocker())
    return;

  // Make sure we own this gamefile
  strcpy(temp_pl.name, Gamefiles[n].name);
  temp_pl.pagetype = PAGETYPE_GAMEFILE;

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

      if (!mng_ReplacePage(Gamefiles[n].name, Gamefiles[n].name, n, PAGETYPE_GAMEFILE, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this gamefile file to the network for all

        char destname[100], srcname[100];

        ddio_MakePath(srcname, LocalD3Dir, "data", Gamefiles[n].dir_name, Gamefiles[n].name, NULL);
        ddio_MakePath(destname, NetD3Dir, "data", Gamefiles[n].dir_name, Gamefiles[n].name, NULL);

        cf_CopyFile(destname, srcname);

        OutrageMessageBox("File checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Gamefiles[n].name, PAGETYPE_GAMEFILE, 1);
        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Gamefiles[n].name, PAGETYPE_GAMEFILE);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
      }
    }
  }

  m_locked = 0;
  UpdateDialog();
}

void CAmbientSoundPattern::OnASPUndoLock() {
  int tl;
  mngs_Pagelock pl;
  mngs_gamefile_page page;

  // Should have this item locked
  if ((tl = mng_FindTrackLock(AMBIENT_FILE_NAME, PAGETYPE_GAMEFILE)) == -1)
    return;

  if (OutrageMessageBox(MBOX_YESNO,
                        "Are you sure you want to undo your lock and lose any changes you may have made?") != IDYES)
    return;

  if (!mng_MakeLocker())
    return;

  // Find where it is in the files index
  int n = FindGamefileName(AMBIENT_FILE_NAME);

  if (n == -1) {
    Int3(); // Get Matt or Jason - AMBIENT file name is no longer in the table file!
    return;
  }

  strcpy(pl.name, AMBIENT_FILE_NAME);
  pl.pagetype = PAGETYPE_GAMEFILE;

  mng_FreeTrackLock(tl);

  // Delete local page
  if (!mng_DeletePage(AMBIENT_FILE_NAME, PAGETYPE_GAMEFILE, 1)) {
    mprintf(0, ErrorString);
    Int3();
  }

  // Get old data from net
  if (!mng_FindSpecificGamefilePage(pl.name, &page))
    Int3();

  // Copy old get into our local array
  if (!mng_AssignGamefilePageToGamefile(&page, n))
    Int3();

  // We're done
  mng_EraseLocker();

  // Re-read old data
  ReadAmbientData();

  m_current_asp = -1;
  m_locked = 0;

  UpdateDialog();
}
