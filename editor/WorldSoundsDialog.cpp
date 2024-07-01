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

 * $Logfile: /DescentIII/Main/editor/WorldSoundsDialog.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:40 $
 * $Author: kevinb $
 *
 *	Sound page dialog
 *
 * $Log: not supported by cvs2svn $
 *
 * 29    4/21/99 5:55p Jason
 * added override button to sound page
 *
 * 28    2/23/99 11:26a Matt
 * Cleaned up sounds dialog
 *
 * 27    11/06/98 12:34p Jason
 * more speedups for manage system
 *
 * 26    10/22/98 8:31p Chris
 * Sounds use GlobalAlloc and GlobalFree
 *
 * 25    10/19/98 1:21p Chris
 * Improve the volume import scaling code
 *
 * 24    10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 23    10/14/98 12:09p Jason
 * fixed some long standing name problems
 *
 * 22    9/21/98 8:18p Chris
 * Removed annoying mprints
 *
 * 21    6/29/98 10:35p Chris
 * Added support for once per object
 *
 * 20    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 19    6/19/98 3:03p Chris
 * Made CheckAndForceSoundDataAlloc a SoundSystem function - useful for
 * multiple mixers.  Added IsSoundPlaying to the high level sound lib.
 *
 * 18    4/22/98 5:38p Chris
 * Fixed problems with adding new sounds
 *
 * 17    2/15/98 7:43p Luke
 *
 * 16    2/12/98 6:07p Chris
 * Fixed a problem with addsound
 *
 * 15    2/12/98 4:55p Chris
 * More validation checks for sounds
 *
 * 14    2/12/98 4:44p Chris
 * Fixed a bunch of bugs in the dialog
 *
 * 13    2/12/98 4:20p Chris
 * Fixed problem with sound dialog and allowing users to enter invalid
 * values
 *
 * 12    2/06/98 3:22a Chris
 * Added a stop sounds button.  Made delete sound first stop the currently
 * playing sounds.
 *
 * 11    12/31/97 2:58a Chris
 * Another major revision to the SoundLib.  This cleaned up the code after
 * removing the direct sound secondary buffers.
 *
 * 10    12/30/97 2:07p Chris
 * Adding further support for software 3d stuff
 *
 * 9     12/29/97 4:50p Chris
 * Added SPF_NO_UPDATE
 *
 * 8     12/22/97 6:19p Chris
 * Moved weapon battery firing sound off the projectile (weapon) and into
 * the weapon battery.
 *
 * 7     12/18/97 12:26p Chris
 * Incremental new lib improvements
 *
 * 6     12/10/97 4:47p Chris
 * Revision 1.0 of new sound library (no hardware -- uses primary buffer
 * streaming)
 *
 * 5     12/02/97 5:31p Samir
 * New file dialog interface implemented.
 *
 * 4     9/08/97 4:05p Samir
 * Fixed some warnings and took out extranneous includes to windows.h in
 * important headers.
 *
 * $NoKeywords: $
 */

// WorldSoundsDialog.cpp : implementation file
//

#include <filesystem>

#include "stdafx.h"

#include "pserror.h"
#include "editor.h"
#include "WorldSoundsDialog.h"
#include "soundload.h"
#include "soundpage.h"
#include "manage.h"
#include "hlsoundlib.h"
#include "ddio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorldSoundsDialog dialog

CWorldSoundsDialog::CWorldSoundsDialog(CWnd *pParent /*=NULL*/) : CDialog(CWorldSoundsDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CWorldSoundsDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CWorldSoundsDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CWorldSoundsDialog)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldSoundsDialog, CDialog)
//{{AFX_MSG_MAP(CWorldSoundsDialog)
ON_BN_CLICKED(IDC_ADD_SOUND, OnAddSound)
ON_BN_CLICKED(IDC_CHECKIN_SOUND, OnCheckinSound)
ON_BN_CLICKED(IDC_DELETE_SOUND, OnDeleteSound)
ON_BN_CLICKED(IDC_LOCK_SOUND, OnLockSound)
ON_BN_CLICKED(IDC_LOAD_SOUND, OnLoadSound)
ON_BN_CLICKED(IDC_NEXT_SOUND, OnNextSound)
ON_BN_CLICKED(IDC_PREV_SOUND, OnPrevSound)
ON_EN_KILLFOCUS(IDC_SOUND_NAME_EDIT, OnKillfocusSoundNameEdit)
ON_CBN_SELENDOK(IDC_SOUND_PULLDOWN, OnSelendokSoundPulldown)
ON_BN_CLICKED(IDC_PLAYSOUND, OnPlaysound)
ON_EN_KILLFOCUS(IDC_SOUNDINNERCONEANGLE_EDIT, OnKillfocusSoundinnerconeangleEdit)
ON_EN_KILLFOCUS(IDC_SOUNDLOOPEND_EDIT, OnKillfocusSoundloopendEdit)
ON_EN_KILLFOCUS(IDC_SOUNDLOOPSTART_EDIT, OnKillfocusSoundloopstartEdit)
ON_EN_KILLFOCUS(IDC_SOUNDMAXDIST_EDIT, OnKillfocusSoundmaxdistEdit)
ON_EN_KILLFOCUS(IDC_SOUNDMINDIST_EDIT, OnKillfocusSoundmindistEdit)
ON_EN_KILLFOCUS(IDC_SOUNDOUTERCONEANGLE_EDIT, OnKillfocusSoundouterconeangleEdit)
ON_EN_KILLFOCUS(IDC_SOUNDOUTERCONEVOL_EDIT, OnKillfocusSoundouterconevolEdit)
ON_BN_CLICKED(IDC_SOUNDHALLEFFECT_CHECK, OnSoundhalleffectCheck)
ON_BN_CLICKED(IDC_LOOPING_CHECK, OnLoopingCheck)
ON_BN_CLICKED(IDC_SOUNDBACKWARD_RADIO, OnSoundbackwardRadio)
ON_BN_CLICKED(IDC_SOUNDDOWNWARD_RADIO, OnSounddownwardRadio)
ON_BN_CLICKED(IDC_SOUNDEXCLUSIVE_CHECK, OnSoundexclusiveCheck)
ON_BN_CLICKED(IDC_SOUNDFOREVER_CHECK, OnSoundforeverCheck)
ON_BN_CLICKED(IDC_SOUNDFORWARD_RADIO, OnSoundforwardRadio)
ON_BN_CLICKED(IDC_SOUNDOBJATTACH_RADIO, OnSoundobjattachRadio)
ON_BN_CLICKED(IDC_SOUNDOBJECT_RADIO, OnSoundobjectRadio)
ON_BN_CLICKED(IDC_SOUNDONCE_CHECK, OnSoundonceCheck)
ON_BN_CLICKED(IDC_SOUNDPOSATTACH_RADIO, OnSoundposattachRadio)
ON_BN_CLICKED(IDC_SOUNDTURRET1_RADIO, OnSoundturret1Radio)
ON_BN_CLICKED(IDC_SOUNDTURRET2_RADIO, OnSoundturret2Radio)
ON_BN_CLICKED(IDC_SOUNDTURRET3_RADIO, OnSoundturret3Radio)
ON_BN_CLICKED(IDC_SOUNDUPWARD_RADIO, OnSoundupwardRadio)
ON_WM_HELPINFO()
ON_BN_CLICKED(IDC_SOUND_NO_UPDATE, OnSoundNoUpdate)
ON_BN_CLICKED(IDC_KILLSOUNDS, OnKillsounds)
ON_BN_CLICKED(IDC_SOUND_ONCE_PER_OBJ_CHECK, OnSoundOncePerObjCheck)
ON_EN_KILLFOCUS(IDC_SOUND_IMPORT_VOLUME_EDIT, OnKillfocusSoundImportVolumeEdit)
ON_BN_CLICKED(IDC_SOUND_CHANGE_NAME, OnSoundChangeName)
ON_BN_CLICKED(IDC_OVERRIDE, OnOverride)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldSoundsDialog message handlers

void CWorldSoundsDialog::OnAddSound() {
  char filename[256], dir[256], fname[128], ext[32];
  char cur_name[100];
  int raw_handle;
  int sound_handle;
  int c = 1, finding_name = 1;

  if (!Network_up) {
    OutrageMessageBox("Sorry babe, the network is down.  This action is a no-no.\n");
    return;
  }

  // Get the filename of the representing image

  CString filter = "Descent III files (*.wav)|*.wav||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_sounds_dir, sizeof(Current_sounds_dir)))
    return;

  ddio_SplitPath(filename, dir, fname, ext);

  //	Okay, we selected a file. Lets do what needs to be done here.
  raw_handle = LoadSoundFile(filename, 1.0f, true);

  if (raw_handle < 0) {
    OutrageMessageBox("Invalid sound file.");
    return;
  }

  // Alloc a sound and give a name not already taken by some other sound

  sound_handle = AllocSound();

  while (finding_name) {
    if (c == 1)
      sprintf(cur_name, "%s", fname);
    else
      sprintf(cur_name, "%s%d", fname, c);
    if (FindSoundName(cur_name) != -1)
      c++;
    else
      finding_name = 0;
  }

  strcpy(Sounds[sound_handle].name, cur_name);

  Sounds[sound_handle].sample_index = raw_handle;

  // Finally, save a local copy of the .wav and alloc a tracklock
  mprintf(0, "Making a copy of this sound locally...\n");

  std::filesystem::path destname = LocalSoundsDir / SoundFiles[Sounds[sound_handle].sample_index].name;
  cf_CopyFile(destname, filename);

  mng_AllocTrackLock(cur_name, PAGETYPE_SOUND);

  D3EditState.current_sound = sound_handle;

  RemapSounds();

  Sound_system.CheckAndForceSoundDataAlloc(D3EditState.current_sound);
  Sounds[sound_handle].loop_end = SoundFiles[Sounds[sound_handle].sample_index].np_sample_length - 1;

  UpdateDialog();
}

void CWorldSoundsDialog::OnCheckinSound() {
  int n = D3EditState.current_sound;
  mngs_Pagelock temp_pl;
  int r;

  if (Num_sounds < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure we own this sound
  strcpy(temp_pl.name, Sounds[n].name);
  temp_pl.pagetype = PAGETYPE_SOUND;

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

      if (!mng_ReplacePage(Sounds[n].name, Sounds[n].name, n, PAGETYPE_SOUND, 0))
        OutrageMessageBox(ErrorString);
      else {
        // Save this sound raw to the network for all

        std::filesystem::path srcname = LocalSoundsDir / SoundFiles[Sounds[n].sample_index].name;
        std::filesystem::path destname = NetSoundsDir / SoundFiles[Sounds[n].sample_index].name;

        cf_CopyFile(destname, srcname);

        OutrageMessageBox("Sound checked in.");

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Sounds[n].name, PAGETYPE_SOUND, 1);
        ASSERT(dret == 1);
        mng_EraseLocker();

        // Free the tracklock
        int p = mng_FindTrackLock(Sounds[n].name, PAGETYPE_SOUND);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);
        UpdateDialog();
      }
    }
  }
}

void CWorldSoundsDialog::OnDeleteSound() {
  int answer, tl;
  mngs_Pagelock pl;
  int n = D3EditState.current_sound;

  if (Num_sounds < 1)
    return;

  Sound_system.BeginSoundFrame();
  Sound_system.StopAllSounds();
  Sound_system.EndSoundFrame();

  // Check to see if we even have it locked
  if ((tl = mng_FindTrackLock(Sounds[n].name, PAGETYPE_SOUND)) == -1) {
    OutrageMessageBox("This sound is not yours to delete.  Lock first.");
    return;
  }

  // Make sure its to be deleted
  answer = MessageBox("Are you sure you want to delete this sound?", Sounds[n].name, MB_YESNO);
  if (answer == IDNO)
    return;

  if (!mng_MakeLocker())
    return;

  strcpy(pl.name, Sounds[n].name);
  pl.pagetype = PAGETYPE_SOUND;

  // Check to see if this is a local sound only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(Sounds[n].name, PAGETYPE_SOUND, 1)) {
      mprintf(0, ErrorString);
      Int3();
    }
  } else // if its network, delete it from both the net and local drives
  {

    mng_FreeTrackLock(tl);
    mng_DeletePage(Sounds[n].name, PAGETYPE_SOUND, 1);
    mng_DeletePage(Sounds[n].name, PAGETYPE_SOUND, 0);

    mng_DeletePagelock(Sounds[n].name, PAGETYPE_SOUND);
  }

  // Advance to the next sound
  D3EditState.current_sound = GetNextSound(n);

  FreeSound(n);
  mng_EraseLocker();

  OutrageMessageBox("Sound deleted.");

  RemapSounds();

  UpdateDialog();
}

void CWorldSoundsDialog::OnLockSound() {
  int n = D3EditState.current_sound;
  mngs_Pagelock temp_pl;
  mngs_sound_page soundpage;
  int r;

  if (Num_sounds < 1)
    return;

  if (!mng_MakeLocker())
    return;

  // Make sure it can be locked
  strcpy(temp_pl.name, Sounds[n].name);
  temp_pl.pagetype = PAGETYPE_SOUND;

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
      if (mng_FindSpecificSoundPage(temp_pl.name, &soundpage)) {
        if (mng_AssignSoundPageToSound(&soundpage, n)) {
          if (!mng_ReplacePage(Sounds[n].name, Sounds[n].name, n, PAGETYPE_SOUND, 1)) {
            OutrageMessageBox("There was problem writing that page locally!");
            mng_EraseLocker();
            return;
          }
          OutrageMessageBox("Sound locked.");

        } else
          OutrageMessageBox(
              "There was a problem loading this sound.  You might encounter problems in dealing with it.  Good luck!");

        mng_AllocTrackLock(Sounds[n].name, PAGETYPE_SOUND);
        UpdateDialog();
      } else
        OutrageMessageBox("Couldn't find that sound in the table file!");
    }
  }
  mng_EraseLocker();
}

void CWorldSoundsDialog::OnLoadSound() {
  char filename[255];
  int raw_handle;
  int sound_handle;
  int c = 1, finding_name = 1;

  // Get the filename of the representing image

  CString filter = "Descent III files (*.wav)|*.wav||";

  if (!OpenFileDialog(this, (LPCSTR)filter, filename, Current_sounds_dir, sizeof(Current_sounds_dir)))
    return;

  sound_handle = D3EditState.current_sound;

  //	Okay, we selected a file. Lets do what needs to be done here.
  raw_handle = LoadSoundFile(filename, Sounds[sound_handle].import_volume, true);

  if (raw_handle < 0) {
    OutrageMessageBox("Invalid sound file.");
    return;
  }

  Sounds[sound_handle].sample_index = raw_handle;

  // Finally, save a local copy of the raw

  std::filesystem::path  curname = LocalSoundsDir / SoundFiles[Sounds[sound_handle].sample_index].name;
  cf_CopyFile(curname, filename);

  UpdateDialog();
}

void CWorldSoundsDialog::OnNextSound() {
  D3EditState.current_sound = GetNextSound(D3EditState.current_sound);
  UpdateDialog();
}

void CWorldSoundsDialog::OnPrevSound() {
  D3EditState.current_sound = GetPrevSound(D3EditState.current_sound);
  UpdateDialog();
}

void CWorldSoundsDialog::OnKillfocusSoundNameEdit() {
  CEdit *ebox;
  int n = D3EditState.current_sound;
  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this sound locked, if not reset name and bail
  int p = mng_FindTrackLock(Sounds[n].name, PAGETYPE_SOUND);
  if (p == -1) {
    OutrageMessageBox("You must lock this sound if you wish to change its name.");
    CEdit *ebox = (CEdit *)GetDlgItem(IDC_SOUND_NAME_EDIT);
    ebox->SetWindowText(Sounds[n].name);
    return;
  }

  // Get the new name
  ebox = (CEdit *)GetDlgItem(IDC_SOUND_NAME_EDIT);
  ebox->GetWindowText(name, PAGENAME_LEN);

  // Check to see if there is already a sound with this name.  If so, reset and bail
  if (FindSoundName(name) != -1) {
    OutrageMessageBox("There already is a sound with that name...choose another name.");

    CEdit *ebox = (CEdit *)GetDlgItem(IDC_SOUND_NAME_EDIT);
    ebox->SetWindowText(Sounds[n].name);
    return;
  }

  if (!mng_MakeLocker())
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Sounds[n].name);
  pl.pagetype = PAGETYPE_SOUND;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Sounds[n].name, name, PAGETYPE_SOUND);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Sounds[n].name);
    strcpy(Sounds[n].name, name);

    mng_ReplacePage(oldname, Sounds[n].name, n, PAGETYPE_SOUND, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Sounds[n].name, name);
  mng_EraseLocker();

  RemapSounds();
  UpdateDialog();
}

void CWorldSoundsDialog::OnSelendokSoundPulldown() {
  int i, cur;
  char name[200];

  cur = SendDlgItemMessage(IDC_SOUND_PULLDOWN, CB_GETCURSEL, 0, 0);
  SendDlgItemMessage(IDC_SOUND_PULLDOWN, CB_GETLBTEXT, cur, (LPARAM)(LPCTSTR)name);

  i = FindSoundName(name);

  if (i == -1) {
    mprintf(0, "Possible corrupted sound list, but probably nothing.");
    UpdateDialog();
  }

  D3EditState.current_sound = i;
  UpdateDialog();
}

void CWorldSoundsDialog::UpdateDialog() {
  CEdit *ebox;
  CStatic *sbox;
  CButton *bbox;
  int n = D3EditState.current_sound;
  char str[50];
  int radio_index[4];
  int i;

  int total_hardware_memory = 0;
  int total_memory = 0;

  Sound_system.CheckAndForceSoundDataAlloc(D3EditState.current_sound);

  for (i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      total_memory += SoundFiles[Sounds[i].sample_index].sample_length * 2;
  }

  if (Num_sounds < 1) {
    bbox = (CButton *)GetDlgItem(IDC_NEXT_SOUND);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_PREV_SOUND);
    bbox->EnableWindow(FALSE);

    return;
  } else {
    bbox = (CButton *)GetDlgItem(IDC_NEXT_SOUND);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_PREV_SOUND);
    bbox->EnableWindow(TRUE);
  }

  if (!Sounds[n].used)
    n = D3EditState.current_sound = GetNextSound(n);

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDMAXDIST_EDIT);
  sprintf(str, "%f", Sounds[n].max_distance);
  ebox->SetWindowText(str);

  sbox = (CStatic *)GetDlgItem(IDC_SOUND_MEMORY_STATIC);
  sprintf(str, "%d, %d H, %d Total", SoundFiles[Sounds[n].sample_index].sample_length / 512,
          total_hardware_memory / 1024, total_memory / 1024);
  sbox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDMINDIST_EDIT);
  sprintf(str, "%f", Sounds[n].min_distance);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDINNERCONEANGLE_EDIT);
  sprintf(str, "%d", Sounds[n].inner_cone_angle);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDOUTERCONEANGLE_EDIT);
  sprintf(str, "%d", Sounds[n].outer_cone_angle);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDOUTERCONEVOL_EDIT);
  sprintf(str, "%f", Sounds[n].outer_cone_volume * 100);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDLOOPSTART_EDIT);
  sprintf(str, "%d", Sounds[n].loop_start);
  ebox->SetWindowText(str);

  if (Sounds[n].loop_end >= SoundFiles[Sounds[n].sample_index].np_sample_length) {
    Sounds[n].loop_end = SoundFiles[Sounds[n].sample_index].np_sample_length - 1;
  }

  if (Sounds[n].loop_start > Sounds[n].loop_end) {
    Sounds[n].loop_start = 0;
  }

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDLOOPEND_EDIT);
  sprintf(str, "%d", Sounds[n].loop_end);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_SOUND_IMPORT_VOLUME_EDIT);
  sprintf(str, "%f", Sounds[n].import_volume * 100.0f);
  ebox->SetWindowText(str);

  ebox = (CEdit *)GetDlgItem(IDC_RAW_NAME_EDIT);
  ebox->SetWindowText(SoundFiles[Sounds[n].sample_index].name);

  bbox = (CButton *)GetDlgItem(IDC_SOUNDHALLEFFECT_CHECK);
  bbox->SetCheck(!(Sounds[n].flags & SPF_FIXED_FREQ));

  bbox = (CButton *)GetDlgItem(IDC_SOUNDFOREVER_CHECK);
  bbox->SetCheck(Sounds[n].flags & SPF_FOREVER);

  bbox = (CButton *)GetDlgItem(IDC_SOUND_ONCE_PER_OBJ_CHECK);
  bbox->SetCheck(Sounds[n].flags & SPF_ONCE_PER_OBJ);

  bbox = (CButton *)GetDlgItem(IDC_SOUNDEXCLUSIVE_CHECK);
  bbox->SetCheck(Sounds[n].flags & SPF_PLAYS_EXCLUSIVELY);

  bbox = (CButton *)GetDlgItem(IDC_SOUND_NO_UPDATE);
  bbox->SetCheck(Sounds[n].flags & SPF_LISTENER_UPDATE);

  bbox = (CButton *)GetDlgItem(IDC_SOUNDONCE_CHECK);
  bbox->SetCheck(Sounds[n].flags & SPF_PLAYS_ONCE);

  bbox = (CButton *)GetDlgItem(IDC_LOOPING_CHECK);
  bbox->SetCheck(Sounds[n].flags & SPF_LOOPED);

  if (Sounds[n].flags & SPF_OBJ_UPDATE) {
    bbox = (CButton *)GetDlgItem(IDC_SOUNDOBJATTACH_RADIO);
    bbox->SetCheck(1);
    bbox = (CButton *)GetDlgItem(IDC_SOUNDPOSATTACH_RADIO);
    bbox->SetCheck(0);
  } else {
    bbox = (CButton *)GetDlgItem(IDC_SOUNDPOSATTACH_RADIO);
    bbox->SetCheck(1);
    bbox = (CButton *)GetDlgItem(IDC_SOUNDOBJATTACH_RADIO);
    bbox->SetCheck(0);
  }

  memset(radio_index, 0, 4 * sizeof(int));
  switch (SPFT_CONE_LINK_MASK & Sounds[n].flags) {
  case SPFT_CONE_LINK_OBJECT:
    radio_index[0] = 1;
    break;
  case SPFT_CONE_LINK_TURRET1:
    radio_index[1] = 1;
    break;
  case SPFT_CONE_LINK_TURRET2:
    radio_index[2] = 1;
    break;
  case SPFT_CONE_LINK_TURRET3:
    radio_index[3] = 1;
    break;
  }
  bbox = (CButton *)GetDlgItem(IDC_SOUNDOBJECT_RADIO);
  bbox->SetCheck(radio_index[0]);
  bbox = (CButton *)GetDlgItem(IDC_SOUNDTURRET1_RADIO);
  bbox->SetCheck(radio_index[1]);
  bbox = (CButton *)GetDlgItem(IDC_SOUNDTURRET2_RADIO);
  bbox->SetCheck(radio_index[2]);
  bbox = (CButton *)GetDlgItem(IDC_SOUNDTURRET3_RADIO);
  bbox->SetCheck(radio_index[3]);

  memset(radio_index, 0, 4 * sizeof(int));
  switch (SPFT_CONE_DIR_MASK & Sounds[n].flags) {
  case SPFT_CONE_DIR_FORWARD:
    radio_index[0] = 1;
    break;
  case SPFT_CONE_DIR_BACKWARD:
    radio_index[1] = 1;
    break;
  case SPFT_CONE_DIR_UPWARD:
    radio_index[2] = 1;
    break;
  case SPFT_CONE_DIR_DOWNWARD:
    radio_index[3] = 1;
    break;
  }
  bbox = (CButton *)GetDlgItem(IDC_SOUNDFORWARD_RADIO);
  bbox->SetCheck(radio_index[0]);
  bbox = (CButton *)GetDlgItem(IDC_SOUNDBACKWARD_RADIO);
  bbox->SetCheck(radio_index[1]);
  bbox = (CButton *)GetDlgItem(IDC_SOUNDUPWARD_RADIO);
  bbox->SetCheck(radio_index[2]);
  bbox = (CButton *)GetDlgItem(IDC_SOUNDDOWNWARD_RADIO);
  bbox->SetCheck(radio_index[3]);

  bbox = (CButton *)GetDlgItem(IDC_CHECKIN_SOUND);
  if (mng_FindTrackLock(Sounds[n].name, PAGETYPE_SOUND) == -1) {
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_SOUND);
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_SOUND_CHANGE_NAME);
    bbox->EnableWindow(FALSE);
  } else {
    bbox->EnableWindow(TRUE);
    bbox = (CButton *)GetDlgItem(IDC_LOCK_SOUND);
    bbox->EnableWindow(FALSE);
    bbox = (CButton *)GetDlgItem(IDC_SOUND_CHANGE_NAME);
    bbox->EnableWindow(TRUE);
  }

  SendDlgItemMessage(IDC_SOUND_PULLDOWN, CB_RESETCONTENT, 0, 0);

  for (i = 0; i < MAX_SOUNDS; i++) {
    if (Sounds[i].used)
      SendDlgItemMessage(IDC_SOUND_PULLDOWN, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)Sounds[i].name);
  }
  SendDlgItemMessage(IDC_SOUND_PULLDOWN, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)Sounds[n].name);
}

void CWorldSoundsDialog::SaveSoundsOnClose() {
  int i, t;

  if (!Network_up)
    return; // don't save a damn thing if the network is down

  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used == 1 && GlobalTrackLocks[i].pagetype == PAGETYPE_SOUND) {
      t = FindSoundName(GlobalTrackLocks[i].name);
      ASSERT(t != -1);

      mng_ReplacePage(Sounds[t].name, Sounds[t].name, t, PAGETYPE_SOUND, 1);
    }
  }
}

BOOL CWorldSoundsDialog::DestroyWindow() {
  SaveSoundsOnClose();
  return CDialog::DestroyWindow();
}

BOOL CWorldSoundsDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  UpdateDialog();

  return TRUE; // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorldSoundsDialog::OnPlaysound() {
  int n = D3EditState.current_sound;

  if (Num_sounds < 1)
    return;

  Sound_system.BeginSoundFrame();
  Sound_system.Play2dSound(n);
  Sound_system.EndSoundFrame();
}

void CWorldSoundsDialog::OnKillfocusSoundinnerconeangleEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDINNERCONEANGLE_EDIT);
  ebox->GetWindowText(str, 20);

  Sounds[n].inner_cone_angle = atoi(str);
}

void CWorldSoundsDialog::OnKillfocusSoundloopendEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDLOOPEND_EDIT);
  ebox->GetWindowText(str, 20);

  sscanf(str, "%d", &Sounds[n].loop_end);
  if (Sounds[n].loop_end < Sounds[n].loop_start)
    Sounds[n].loop_end = Sounds[n].loop_start;
  if (Sounds[n].loop_end >= SoundFiles[Sounds[n].sample_index].np_sample_length)
    Sounds[n].loop_end = SoundFiles[Sounds[n].sample_index].np_sample_length - 1;

  if (Sounds[n].loop_end < 0)
    Sounds[n].loop_end = 0;

  UpdateDialog();
}

void CWorldSoundsDialog::OnKillfocusSoundloopstartEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDLOOPSTART_EDIT);
  ebox->GetWindowText(str, 20);

  sscanf(str, "%d", &Sounds[n].loop_start);
  if (Sounds[n].loop_start > Sounds[n].loop_end)
    Sounds[n].loop_start = Sounds[n].loop_end;
  if (Sounds[n].loop_start >= SoundFiles[Sounds[n].sample_index].np_sample_length)
    Sounds[n].loop_start = SoundFiles[Sounds[n].sample_index].np_sample_length - 1;

  if (Sounds[n].loop_start < 0)
    Sounds[n].loop_start = 0;

  UpdateDialog();
}

void CWorldSoundsDialog::OnKillfocusSoundmaxdistEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDMAXDIST_EDIT);
  ebox->GetWindowText(str, 20);

  Sounds[n].max_distance = atof(str);
}

void CWorldSoundsDialog::OnKillfocusSoundmindistEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDMINDIST_EDIT);
  ebox->GetWindowText(str, 20);

  Sounds[n].min_distance = atof(str);
}

void CWorldSoundsDialog::OnKillfocusSoundouterconeangleEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDOUTERCONEANGLE_EDIT);
  ebox->GetWindowText(str, 20);

  Sounds[n].outer_cone_angle = atoi(str);
}

void CWorldSoundsDialog::OnKillfocusSoundouterconevolEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUNDOUTERCONEVOL_EDIT);
  ebox->GetWindowText(str, 20);

  Sounds[n].outer_cone_volume = atof(str) / 100.0;
}

void CWorldSoundsDialog::OnSoundhalleffectCheck() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_SOUNDHALLEFFECT_CHECK);

  if (btn->GetCheck())
    Sounds[n].flags &= ~SPF_FIXED_FREQ;
  else
    Sounds[n].flags |= SPF_FIXED_FREQ;
}

void CWorldSoundsDialog::OnLoopingCheck() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_LOOPING_CHECK);

  if (btn->GetCheck())
    Sounds[n].flags |= SPF_LOOPED;
  else
    Sounds[n].flags &= ~SPF_LOOPED;
}

void CWorldSoundsDialog::OnSoundbackwardRadio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_DIR_MASK;
  Sounds[n].flags |= SPFT_CONE_DIR_BACKWARD;
}

void CWorldSoundsDialog::OnSounddownwardRadio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_DIR_MASK;
  Sounds[n].flags |= SPFT_CONE_DIR_DOWNWARD;
}

void CWorldSoundsDialog::OnSoundexclusiveCheck() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_SOUNDEXCLUSIVE_CHECK);

  if (btn->GetCheck())
    Sounds[n].flags |= SPF_PLAYS_EXCLUSIVELY;
  else
    Sounds[n].flags &= ~SPF_PLAYS_EXCLUSIVELY;
}

void CWorldSoundsDialog::OnSoundforeverCheck() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_SOUNDFOREVER_CHECK);

  if (btn->GetCheck())
    Sounds[n].flags |= SPF_FOREVER;
  else
    Sounds[n].flags &= ~SPF_FOREVER;
}

void CWorldSoundsDialog::OnSoundforwardRadio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_DIR_MASK;
  Sounds[n].flags |= SPFT_CONE_DIR_FORWARD;
}

void CWorldSoundsDialog::OnSoundobjattachRadio() {
  int n = D3EditState.current_sound;
  Sounds[n].flags |= SPF_OBJ_UPDATE;
}

void CWorldSoundsDialog::OnSoundobjectRadio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_LINK_MASK;
  Sounds[n].flags |= SPFT_CONE_LINK_OBJECT;
}

void CWorldSoundsDialog::OnSoundonceCheck() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_SOUNDONCE_CHECK);

  if (btn->GetCheck())
    Sounds[n].flags |= SPF_PLAYS_ONCE;
  else
    Sounds[n].flags &= ~SPF_PLAYS_ONCE;
}

void CWorldSoundsDialog::OnSoundposattachRadio() {
  int n = D3EditState.current_sound;
  Sounds[n].flags &= ~SPF_OBJ_UPDATE;
}

void CWorldSoundsDialog::OnSoundturret1Radio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_LINK_MASK;
  Sounds[n].flags |= SPFT_CONE_LINK_TURRET1;
}

void CWorldSoundsDialog::OnSoundturret2Radio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_LINK_MASK;
  Sounds[n].flags |= SPFT_CONE_LINK_TURRET2;
}

void CWorldSoundsDialog::OnSoundturret3Radio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_LINK_MASK;
  Sounds[n].flags |= SPFT_CONE_LINK_TURRET3;
}

void CWorldSoundsDialog::OnSoundupwardRadio() {
  int n = D3EditState.current_sound;

  Sounds[n].flags &= ~SPFT_CONE_DIR_MASK;
  Sounds[n].flags |= SPFT_CONE_DIR_UPWARD;
}

BOOL CWorldSoundsDialog::OnHelpInfo(HELPINFO *pHelpInfo) {
  WinHelp(HID_SOUNDSDLG, HELP_CONTEXT);
  return TRUE;
  // return CDialog::OnHelpInfo(pHelpInfo);
}

void CWorldSoundsDialog::OnSoundNoUpdate() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_SOUND_NO_UPDATE);

  if (btn->GetCheck())
    Sounds[n].flags |= SPF_LISTENER_UPDATE;
  else
    Sounds[n].flags &= ~SPF_LISTENER_UPDATE;
}

void CWorldSoundsDialog::OnKillsounds() {
  Sound_system.BeginSoundFrame();
  Sound_system.StopAllSounds();
  Sound_system.EndSoundFrame();
}

void CWorldSoundsDialog::OnSoundOncePerObjCheck() {
  int n = D3EditState.current_sound;
  CButton *btn;

  btn = (CButton *)GetDlgItem(IDC_SOUND_ONCE_PER_OBJ_CHECK);

  if (btn->GetCheck())
    Sounds[n].flags |= SPF_ONCE_PER_OBJ;
  else
    Sounds[n].flags &= ~SPF_ONCE_PER_OBJ;
}

void CWorldSoundsDialog::OnKillfocusSoundImportVolumeEdit() {
  CEdit *ebox;
  char str[20];
  int n = D3EditState.current_sound;

  ebox = (CEdit *)GetDlgItem(IDC_SOUND_IMPORT_VOLUME_EDIT);
  ebox->GetWindowText(str, 20);

  sscanf(str, "%f", &Sounds[n].import_volume);
  Sounds[n].import_volume /= 100.0f;

  if (Sounds[n].import_volume < 0.01f)
    Sounds[n].import_volume = 0.01f;
  if (Sounds[n].import_volume > 1.0f)
    Sounds[n].import_volume = 1.0f;

  int j = Sounds[n].sample_index;
  if (j >= 0 && SoundFiles[j].used) {
    if (SoundFiles[j].sample_16bit) {
      GlobalFree(SoundFiles[j].sample_16bit);
      SoundFiles[j].sample_16bit = NULL;
    }

    if (SoundFiles[j].sample_8bit) {
      GlobalFree(SoundFiles[j].sample_8bit);
      SoundFiles[j].sample_8bit = NULL;
    }
  }

  UpdateDialog();
}

#include "mem.h"
#include "EditLineDialog.h"

// Gets a name from the user, making sure it's unique
// Returns true if got new name, false if cancelled.
// the data in buf not changed if cancel is pressed
bool InputSoundName(char *buf, int len, char *title, char *prompt, CWnd *wnd) {
  if (len > (PAGENAME_LEN - 1))
    len = PAGENAME_LEN - 1;

  char *tempbuf = (char *)mem_malloc(len);

  strncpy(tempbuf, buf, len - 1);
  tempbuf[len - 1] = '\0';

try_again:

  if (!InputString(tempbuf, len, title, prompt, wnd)) {
    mem_free(tempbuf);
    return 0;
  }

  if (FindSoundName(tempbuf) != -1) {
    OutrageMessageBox("The name you specified is already in use.  Enter another name.");
    goto try_again;
  }

  strcpy(buf, tempbuf);
  mem_free(tempbuf);

  return 1;
}

void CWorldSoundsDialog::OnSoundChangeName() {
  int n = D3EditState.current_sound;

  char name[PAGENAME_LEN];
  mngs_Pagelock pl;

  // Make sure we have this ship locked, if not reset name and bail
  int p = mng_FindTrackLock(Sounds[n].name, PAGETYPE_SOUND);
  if (p == -1) {
    OutrageMessageBox("You must lock this sound if you wish to change its name.");
    return;
  }

  if (!mng_MakeLocker())
    return;

  // Get new name
  strcpy(name, Sounds[n].name);
  if (!InputSoundName(name, sizeof(name), "Sound name", "Enter a new name for this sound:", this))
    return;

  // Check to see if this page exists on the network.  If so, we have to
  // rename it so we can prevent havoc
  strcpy(pl.name, Sounds[n].name);
  pl.pagetype = PAGETYPE_SOUND;

  int ret = mng_CheckIfPageOwned(&pl, TableUser);
  if (ret < 0)
    OutrageMessageBox(ErrorString);
  else if (ret == 1)
    mng_RenamePage(Sounds[n].name, name, PAGETYPE_SOUND);
  else if (ret == 2) {
    // This page has never been checked in, replace only local copy

    char oldname[PAGENAME_LEN];
    strcpy(oldname, Sounds[n].name);
    strcpy(Sounds[n].name, name);

    mng_ReplacePage(oldname, Sounds[n].name, n, PAGETYPE_SOUND, 1);
  } else if (ret == 0) {
    OutrageMessageBox("You don't own this page.  Get Jason now!");
    mng_FreeTrackLock(p);
    return;
  }

  // Finally, copy our new name to the appropriate arrays
  strcpy(GlobalTrackLocks[p].name, name);
  strcpy(Sounds[n].name, name);
  mng_EraseLocker();

  UpdateDialog();
}

void CWorldSoundsDialog::OnOverride() {
  int n = D3EditState.current_sound;
  mngs_Pagelock temp_pl;

  strcpy(temp_pl.name, Sounds[n].name);
  temp_pl.pagetype = PAGETYPE_SOUND;

  mng_OverrideToUnlocked(&temp_pl);
}
