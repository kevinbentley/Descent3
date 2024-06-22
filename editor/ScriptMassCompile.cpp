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

* $Logfile: /DescentIII/Main/editor/ScriptMassCompile.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:57:39 $
* $Author: kevinb $
*
* Implementation of mass script compile dialog
*
* $Log: not supported by cvs2svn $
 *
 * 9     4/03/99 1:36a Jeff
 * added no-check out option for mass compiler
 *
 * 8     2/25/99 12:34p Jeff
 * don't display message if someone has a file checked out during mass
 * compile
 *
 * 7     2/21/99 8:05p Jeff
 * better handling of out-of-sync scripts
 *
 * 6     1/11/99 3:34p Jeff
 * added checks for when going editor->game to see if scripts are out of
 * date, if so give the option of breaking out.  Add some options to mass
 * script compiler, along with a toolbar shortcut.
 *
 * 5     12/30/98 4:39p Jeff
 * selectable to what scripts to display (checked out, non-checked out or
 * both)
 *
 * 4     12/20/98 9:57p Jeff
 * finished mass compile dialog
 *
 * 3     12/18/98 12:36p Jeff
 * created a function to determine a script's type and hooked it in
 *
 * 2     12/18/98 12:11p Jeff
 * added mass script compile dialog
*
* $NoKeywords: $
*/

// ScriptMassCompile.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "ScriptMassCompile.h"
#include "cfile.h"
#include "gamefile.h"
#include "gamefilepage.h"
#include "windatabase.h"
#include "Descent.h"
#include "mono.h"
#include "ddio.h"
#include "ScriptCompilerAPI.h"
#include <string.h>
#include <stdarg.h>
#include "mem.h"
#include "pserror.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptMassCompile dialog
CString MassScriptEditContent;
CEdit *MassScriptEdit;
void writeline(char *format, ...);

CScriptMassCompile::CScriptMassCompile(CWnd *pParent /*=NULL*/) : CDialog(CScriptMassCompile::IDD, pParent) {
  //{{AFX_DATA_INIT(CScriptMassCompile)
  m_AutoCheckIn = FALSE;
  m_DisplayType = 2;
  m_NoCheckout = FALSE;
  //}}AFX_DATA_INIT
}

void CScriptMassCompile::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CScriptMassCompile)
  DDX_Control(pDX, IDC_LIST, m_ScriptList);
  DDX_Check(pDX, IDC_AUTOCHECKIN, m_AutoCheckIn);
  DDX_Radio(pDX, IDC_LOCKED, m_DisplayType);
  DDX_Check(pDX, IDC_NOCHECKOUT, m_NoCheckout);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptMassCompile, CDialog)
//{{AFX_MSG_MAP(CScriptMassCompile)
ON_BN_CLICKED(IDC_BUILD, OnBuild)
ON_BN_CLICKED(IDC_LOCKED, OnLocked)
ON_BN_CLICKED(IDC_NOTLOCKED, OnNotlocked)
ON_BN_CLICKED(IDC_BOTH, OnBoth)
ON_BN_CLICKED(IDC_SELECTALL, OnSelectall)
ON_BN_CLICKED(IDC_OODSCRIPTS, OnOodscripts)
ON_BN_CLICKED(IDC_OOSSCRIPTS, OnOosscripts)
ON_BN_CLICKED(IDC_NOCHECKOUT, OnNocheckout)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptMassCompile message handlers

void CScriptMassCompile::OnBuild() {
  UpdateData(true);

  MassScriptEditContent = "";
  writeline("Starting Mass Build.");

  int i, list_size, listbox_size, index;
  int *index_map = NULL;
  CCheckListBox *list;
  char tempbuffer[_MAX_PATH];
  CWnd *wnd;

  list = (CCheckListBox *)GetDlgItem(IDC_LIST);
  listbox_size = list->GetCount();
  list_size = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return;
  index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return;

  index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  wnd = (CWnd *)GetDlgItem(IDC_FILENAME);
  bool ret1, ret2, ret3, ret4;

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    SetStepText(1, "-Not Done-");
    SetStepText(2, "-Not Done-");
    SetStepText(3, "-Not Done-");
    SetStepText(4, "-Not Done-");

    list->GetText(index, tempbuffer);
    wnd->SetWindowText(tempbuffer);
    writeline("------------------------------- %s --------------------------", tempbuffer);
    App()->defer();

    ret1 = Step1(tempbuffer);
    App()->defer();

    ret2 = Step2(tempbuffer);
    App()->defer();

    ret3 = Step3(tempbuffer, ret2);
    App()->defer();

    if (ret1) {
      ret4 = Step4(tempbuffer);
      App()->defer();
    } else {
      SetStepText(4, "Skipping due to results of Step 1");
      writeline("Step 4: Skipped due to result of Step 1 (maybe already checked out)");
      ret4 = true;
    }
  }

  OutrageMessageBox("Mass Compile Complete");

  mem_free(index_map);
}

void CScriptMassCompile::OnOK() {
  UpdateData(true);
  Database()->write("EditorScriptAutoCheckin", m_AutoCheckIn);
  CDialog::OnOK();
}

void writeline(char *format, ...) {
  char buffer[2048];
  va_list marker;
  va_start(marker, format);
  std::vsprintf(buffer, format, marker);
  va_end(marker);

  MassScriptEditContent += buffer;
  MassScriptEditContent += "\r\n";

  MassScriptEdit->SetWindowText(MassScriptEditContent.GetBuffer(0));
  App()->defer();

  int total_lines = MassScriptEdit->GetLineCount();
  int curr_index = MassScriptEdit->GetFirstVisibleLine();
  if ((total_lines - curr_index) > 16) {
    // we need to scroll down a line
    MassScriptEdit->LineScroll((total_lines - curr_index) - 16);
  }
}

uint8_t DetermineScriptType(char *filename) {
  CFILE *file;
  file = cfopen(filename, "rt");
  if (!file) {
    return 255;
  }

  char buffer[4096];
  bool done = false;
  uint8_t script_type = ST_GAME;

  cf_ReadString(buffer, 4096, file);
  while (!(cfeof(file) || done)) {
    if (strstr(buffer, "GetTriggerScriptID")) {
      // we found it!
      script_type = ST_LEVEL;
      done = true;
    }

    cf_ReadString(buffer, 4096, file);
  }

  cfclose(file);

  return script_type;
}

void CScriptMassCompile::BuildList(void) {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST);
  if (!list)
    return;

  list->ResetContent();

  char buffer[_MAX_PATH];
  int length;

  for (int i = 0; i < MAX_GAMEFILES; i++) {
    if (Gamefiles[i].used) {
      // we're only adding .cpp's to this list
      length = strlen(Gamefiles[i].name);
      if (length > 4 && !stricmp(&Gamefiles[i].name[length - 4], ".cpp")) {
        switch (m_DisplayType) {
        case 0: // checked out only
        {
          if (mng_FindTrackLock(Gamefiles[i].name, PAGETYPE_GAMEFILE) != -1) {
            strcpy(buffer, Gamefiles[i].name);
            buffer[length - 4] = '\0';
            list->AddString(buffer);
          }
        } break;
        case 1: // non-check out only
        {
          if (mng_FindTrackLock(Gamefiles[i].name, PAGETYPE_GAMEFILE) == -1) {
            strcpy(buffer, Gamefiles[i].name);
            buffer[length - 4] = '\0';
            list->AddString(buffer);
          }
        } break;
        case 2: // both
        {
          strcpy(buffer, Gamefiles[i].name);
          buffer[length - 4] = '\0';
          list->AddString(buffer);
        } break;
        };
      }
    }
  }
}

BOOL CScriptMassCompile::OnInitDialog() {
  CDialog::OnInitDialog();

  bool bval;
  if (Database()->read("EditorScriptAutoCheckin", &bval))
    m_AutoCheckIn = bval;
  else
    m_AutoCheckIn = true;
  UpdateData(false);

  MassScriptEditContent = "";
  MassScriptEdit = (CEdit *)GetDlgItem(IDC_OUTPUT);
  writeline("System Initialized.");

  if (!Network_up) {
    writeline("WARNING: You did not say yes to the data update, therefore, your work will not be saved for the scripts "
              "that you don't currently have checked out.");
  }
  writeline("----------------------------------------------------------------------------------------------------------"
            "--------------------------------------");

  BuildList();

  return TRUE;
}

void CScriptMassCompile::SetStepText(int step, char *format, ...) {
  if (step < 1 || step > 4)
    return;

  char buffer[1024];
  va_list marker;
  va_start(marker, format);
  std::vsprintf(buffer, format, marker);
  va_end(marker);

  CWnd *wnd;
  int msg_to;

  switch (step) {
  case 1:
    wnd = (CWnd *)GetDlgItem(IDC_STEP1);
    msg_to = IDC_STEP1;
    break;
  case 2:
    wnd = (CWnd *)GetDlgItem(IDC_STEP2);
    msg_to = IDC_STEP2;
    break;
  case 3:
    wnd = (CWnd *)GetDlgItem(IDC_STEP3);
    msg_to = IDC_STEP3;
    break;
  case 4:
    wnd = (CWnd *)GetDlgItem(IDC_STEP4);
    msg_to = IDC_STEP4;
    break;
  };
  wnd->SetWindowText(buffer);
  SendDlgItemMessage(msg_to, WM_PAINT, 0, 0);
  App()->defer();
}

// return true if the file was checked out for this step
bool CheckOutGamefile(char *tempbuffer, bool show_ok_confirmation, bool report_who_has_locked);
bool CScriptMassCompile::Step1(char *filename) {
  if (!Network_up) {
    SetStepText(1, "Skipping, Network 'Down'");
    writeline("Step 1: Skipping, Due to the NO on data update");
    return false;
  }

  if (m_NoCheckout) {
    SetStepText(1, "Skipping, 'no checkout' option checked");
    writeline("Step 1: Skipping, 'no checkout' option checked");
    return false;
  }

  char source_filename[_MAX_PATH], compiled_filename[_MAX_PATH];

  // make the locker
  if (!mng_MakeLocker()) {
    SetStepText(1, "Unable to create locker, can't check out");
    writeline("Step 1: Can't make locker file, skipping check out");
    return false;
  }

  // make real filenames
  strcpy(source_filename, filename);
  strcpy(compiled_filename, filename);
  strcat(source_filename, ".cpp");
  strcat(compiled_filename, ".dll");

  bool found_script = false, found_compiled = false;
  int i;

  // make sure the compiled script is in the gamefiles
  for (i = 0; i < MAX_GAMEFILES; i++) {
    if (Gamefiles[i].used) {
      if (!found_script && !stricmp(Gamefiles[i].name, source_filename))
        found_script = true;
      if (!found_compiled && !stricmp(Gamefiles[i].name, compiled_filename))
        found_compiled = true;
    }
    if (found_script && found_compiled)
      break;
  }

  if (!found_script) {
    // ummm, this shouldn't happen
    MessageBox("Hmmm, I couldn't find the source file for the script in the manage system...this isn't good", "Uh oh");
    SetStepText(1, "File Not Found");
    writeline("Step 1: Couldn't find source script in manage system");
    mng_EraseLocker();
    return false;
  }

  bool ntco_script = true, ntco_compiled = true;
  if (!found_compiled)
    ntco_compiled = false;

  // see if we have these checked out
  if (mng_FindTrackLock(source_filename, PAGETYPE_GAMEFILE) != -1)
    ntco_script = false;

  if (ntco_compiled && mng_FindTrackLock(compiled_filename, PAGETYPE_GAMEFILE) != -1)
    ntco_compiled = false;

  // ok, we know what files we need to check out
  bool sret = false, cret = false;

  if (ntco_script) {
    writeline("Step 1: Checking out %s", source_filename);
    sret = CheckOutGamefile(source_filename, false, false);
    if (!sret)
      writeline("Step 1: Unable to check out %s", source_filename);
  }

  if (ntco_compiled) {
    writeline("Step 1: Checking out %s", compiled_filename);
    cret = CheckOutGamefile(compiled_filename, false, false);
    if (!cret)
      writeline("Step 1: Unable to check out %s", compiled_filename);
  }

  if ((ntco_script || ntco_compiled)) {
    if (((!ntco_script) || sret) && ((!ntco_compiled) || cret)) {
      SetStepText(1, "Files checked out");
      writeline("Step 1: Success");
    } else {
      SetStepText(1, "Error checking files out");
      writeline("Step 1: Errors have occurred");
    }
  } else {
    SetStepText(1, "No files needed to be checked out");
    writeline("Step 1: Success");
  }

  mng_EraseLocker();
  return (sret || cret);
}

// return true if it's a level script
bool CScriptMassCompile::Step2(char *filename) {
  char source_filename[_MAX_PATH];
  strcpy(source_filename, filename);
  strcat(source_filename, ".cpp");

  if (DetermineScriptType(source_filename) == ST_LEVEL) {
    writeline("Step 2: Determined to be a level script");
    SetStepText(2, "Level Script");
    return true;
  } else {
    writeline("Step 2: Determined to be a game script");
    SetStepText(2, "Game Script");
    return false;
  }

  return false;
}

void masscompilercallback(char *str) {
  MassScriptEditContent += str;

  MassScriptEdit->SetWindowText(MassScriptEditContent.GetBuffer(0));

  int total_lines = MassScriptEdit->GetLineCount();
  int curr_index = MassScriptEdit->GetFirstVisibleLine();
  if ((total_lines - curr_index) > 16) {
    // we need to scroll down a line
    MassScriptEdit->LineScroll((total_lines - curr_index) - 16);
  }

  App()->defer();
}

bool CScriptMassCompile::Step3(char *filename, bool islevel) {
  tCompilerInfo ci;
  ci.callback = masscompilercallback;
  ci.script_type = (islevel) ? ST_LEVEL : ST_GAME;
  strcpy(ci.source_filename, filename);
  strcat(ci.source_filename, ".cpp");

  char compiled_filename[_MAX_PATH], full_path[_MAX_PATH];
  strcpy(compiled_filename, filename);
  strcat(compiled_filename, ".dll");
  ddio_MakePath(full_path, LocalScriptDir, compiled_filename, NULL);
  if (cfexist(full_path)) {
    ddio_DeleteFile(full_path);
  }

  writeline("===START COMPILE===");
  ScriptCompile(&ci);
  writeline("");
  writeline("===END COMPILE===");

  bool ret;
  if (cfexist(full_path)) {
    writeline("Step 3: DLL Created");
    SetStepText(3, "DLL Created");
    ret = true;
  } else {
    writeline("Step 3: DLL Not Created");
    SetStepText(3, "DLL NOT Created");
    ret = false;
  }

  return ret;
}

bool CheckInGamefile(char *tempbuffer, bool giveok);
bool AddNewGameFile(char *fullpath, char *directory);
bool CScriptMassCompile::Step4(char *filename) {
  if (!Network_up) {
    SetStepText(4, "Skipping, Network 'Down'");
    writeline("Step 4: Skipping, Due to the NO on data update");
    return false;
  }

  if (!m_AutoCheckIn) {
    SetStepText(4, "Skipping, Auto Checkin box not set");
    writeline("Step 4: Skipping, Auto Checkin box not set");
    return false;
  }

  char source_filename[_MAX_PATH], compiled_filename[_MAX_PATH];

  // make the locker
  if (!mng_MakeLocker()) {
    SetStepText(4, "Unable to create locker, can't check in");
    writeline("Step 4: Can't make locker file, skipping check in");
    return false;
  }

  // make real filenames
  strcpy(source_filename, filename);
  strcpy(compiled_filename, filename);
  strcat(source_filename, ".cpp");
  strcat(compiled_filename, ".dll");

  bool ntci_source = false, ntci_compiled = false;
  int i;

  for (i = 0; i < MAX_GAMEFILES; i++) {
    if (Gamefiles[i].used) {
      if (!ntci_source && !stricmp(Gamefiles[i].name, source_filename) &&
          (mng_FindTrackLock(source_filename, PAGETYPE_GAMEFILE) != -1)) {
        ntci_source = true;
      }
      if (!ntci_compiled && !stricmp(Gamefiles[i].name, compiled_filename) &&
          (mng_FindTrackLock(source_filename, PAGETYPE_GAMEFILE) != -1)) {
        ntci_compiled = true;
      }
    }
    if (ntci_source && ntci_compiled)
      break;
  }

  if (!ntci_source && !ntci_compiled) {
    SetStepText(4, "Skipping, files not checked out");
    writeline("Step 4: Skipping because both source and compiled are not checked out or not in the manage system");
    mng_EraseLocker();
    return false;
  }

  // check to make sure the compiled version exists
  if (!cfexist(compiled_filename)) {
    writeline("Step 4: %s does not exist...possibly due to compilation errors", compiled_filename);
    writeline("Step 4: Aborting check in");
    SetStepText(4, "Aborted");
    mng_EraseLocker();
    return false;
  }

  // see if we need to add the compiled version to manage system
  if (!ntci_compiled) {
    int j;
    for (j = 0; j < MAX_GAMEFILES; j++) {
      if (Gamefiles[j].used) {
        if (!stricmp(Gamefiles[j].name, compiled_filename))
          break;
      }
    }
    if (j >= MAX_GAMEFILES) {
      // compiled file doesn't exist, we'll need to add it
      writeline("Step 4: Attempting to add %s to manage system", compiled_filename);
      char fullpath[_MAX_PATH];
      ddio_MakePath(fullpath, LocalScriptDir, compiled_filename, NULL);
      bool ret = AddNewGameFile(fullpath, "scripts");
      if (!ret) {
        writeline("Step 4: Unable to add %s to manage system", compiled_filename);
        writeline("Step 4: Aborting");
        SetStepText(4, "Aborted");
        mng_EraseLocker();
        return false;
      } else
        ntci_compiled = true;
    }
  }

  // we have at least 1 file to check in
  bool sret = true, cret = true;

  if (ntci_source) {
    sret = CheckInGamefile(source_filename, false);
    if (!sret) {
      writeline("Step 4: Unable to check in source file");
    }
  }

  if (ntci_compiled) {
    cret = CheckInGamefile(compiled_filename, false);
    if (!cret) {
      writeline("Step 4: Unable to check in compiled file");
    }
  }

  if (!sret || !cret) {
    SetStepText(4, "There were errors checking in files");
    writeline("Step 4: Errors had occurred");
  } else {
    SetStepText(4, "Success");
    writeline("Step 4: Success");
  }

  mng_EraseLocker();
  return (sret || cret);
}

void CScriptMassCompile::OnLocked() {
  UpdateData(true);
  BuildList();
}

void CScriptMassCompile::OnNotlocked() {
  UpdateData(true);
  BuildList();
}

void CScriptMassCompile::OnBoth() {
  UpdateData(true);
  BuildList();
}

void CScriptMassCompile::OnSelectall() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST);
  if (!list)
    return;

  int count = list->GetCount();
  for (int i = 0; i < count; i++) {
    list->SetCheck(i, 1);
    list->SetSel(i, TRUE);
  }
}

bool IsScriptOutofDate(char *name);
void CScriptMassCompile::OnOodscripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST);
  if (!list)
    return;

  char old_dir[_MAX_PATH];
  ddio_GetWorkingDir(old_dir, _MAX_PATH);
  ddio_SetWorkingDir(LocalScriptDir);

  char filename[_MAX_PATH];
  int count = list->GetCount();
  for (int i = 0; i < count; i++) {
    list->GetText(i, filename);
    strcat(filename, ".cpp");

    if (IsScriptOutofDate(filename)) {
      list->SetCheck(i, 1);
      list->SetSel(i, TRUE);
    } else {
      list->SetCheck(i, 0);
      list->SetSel(i, FALSE);
    }
  }

  ddio_SetWorkingDir(old_dir);
}
bool IsScriptOutofSync(char *name);
void CScriptMassCompile::OnOosscripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST);
  if (!list)
    return;

  char filename[_MAX_PATH];
  int count = list->GetCount();
  for (int i = 0; i < count; i++) {
    list->GetText(i, filename);
    strcat(filename, ".cpp");

    if (IsScriptOutofSync(filename)) {
      list->SetCheck(i, 1);
      list->SetSel(i, TRUE);
    } else {
      list->SetCheck(i, 0);
      list->SetSel(i, FALSE);
    }
  }
}

void CScriptMassCompile::OnNocheckout() {
  // TODO: Add your control notification handler code here
}
