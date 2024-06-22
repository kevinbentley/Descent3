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

* $Logfile: /DescentIII/Main/editor/ScriptLevelInterface.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:57:38 $
* $Author: kevinb $
*
* ScriptLevelInterface.cpp : implementation file
*
* $Log: not supported by cvs2svn $
 *
 * 24    5/11/99 12:13p Jason
 * added checks for messed up gamefiles
 *
 * 23    2/25/99 12:34p Jeff
 * don't display message that someone has a file checked out during mass
 * compile
 *
 * 22    2/24/99 9:39p Jeff
 * only sync scripts when needed
 *
 * 21    2/23/99 11:52p Jeff
 * new script dll sync dialog
 *
 * 20    2/21/99 8:04p Jeff
 * better handling of out-of-sync scripts
 *
 * 19    2/18/99 8:29p Nate
 * commented out some manage code
 *
 * 18    2/18/99 10:58a Jeff
 * added a 'find in files' for gamefiles manage system
 *
 * 17    2/17/99 6:54p Jeff
 * added check box for auto check in/out scripts with levels...fix
 * checksum mprintf bug
 *
 * 16    2/09/99 4:43p Jeff
 * fixed resource leak
 *
 * 15    2/01/99 11:55a Jeff
 * automatically check in/out .msg and .str files
 *
 * 14    1/13/99 5:01p Jeff
 * don't auto-checkin dll if the .cpp doesn't get checked in for a new
 * file
 *
 * 13    1/11/99 3:34p Jeff
 * added checks for when going editor->game to see if scripts are out of
 * date, if so give the option of breaking out.  Add some options to mass
 * script compiler, along with a toolbar shortcut.
 *
 * 12    1/05/99 4:54p Jeff
 * save the last script edited and set the on init
 *
 * 11    1/05/99 4:33p Jeff
 * when "Display non checkout files" is checked, display the .cpp files in
 * the directory...not just whats in the table file
 *
 * 10    12/21/98 6:41p Jeff
 * auto-compile, check in and check back out for when new scripts are
 * created. (yes must be said to the data update)
 *
 * 9     12/20/98 9:57p Jeff
 * added ability to display scripts not checked out.  don't display
 * message on checkin/out
 *
 * 8     12/18/98 12:11p Jeff
 * created a function to determine a script's type and hooked it in
 *
 * 7     12/18/98 12:11p Jeff
 * added mass script compile dialog
 *
 * 6     12/18/98 10:40a Jeff
 * save out settings to registry
 *
 * 5     12/13/98 7:50p Jeff
 * automatically add new DLLs that aren't in the manage
 * system...implemented create new script function, even though it's still
 * in infancy.
 *
 * 4     12/13/98 3:10a Jeff
 * fixed some bugs.  Automatically check in/out/etc .dll when operating
 * with .cpp.  Hooked in compiler and compiler configuration.  Very
 * complete.
 *
 * 3     12/11/98 10:34p Jeff
 * Updated the script/level interface, all manage system integration is
 * complete.  External Script Editor loading is setup too.
 *
 * 2     12/11/98 5:50p Jeff
 * implemented and added changes regarding Level&Scripting manage system
 * and compiler interface
*
* $NoKeywords: $
*/

// ScriptLevelInterface.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "ScriptLevelInterface.h"
#include "CreateNewScriptDlg.h"
#include "VirtualCompilerConfig.h"
#include "ScriptMassCompile.h"
#include "gamefile.h"
#include "gamefilepage.h"
#include "descent.h"
#include "mono.h"
#include "ddio.h"
#include "pserror.h"
#include "manage.h"
#include "mem.h"
#include "ScriptCompilerAPI.h"
#include "windatabase.h"
#include "Descent.h"
#include "ScriptSyncDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool AddNewGameFile(char *fullpath, char *directory);
bool DeleteGamefile(char *tempbuffer);
bool CheckInGamefile(char *tempbuffer, bool giveok);
bool CheckOutGamefile(char *tempbuffer, bool show_ok_confirmation, bool report_who_has_locked = true);

char LastScriptSelected[256];
bool Scripts_need_sync = true;

/////////////////////////////////////////////////////////////////////////////
// CScriptLevelInterface dialog

CScriptLevelInterface::CScriptLevelInterface(CWnd *pParent /*=NULL*/) : CDialog(CScriptLevelInterface::IDD, pParent) {
  //{{AFX_DATA_INIT(CScriptLevelInterface)
  m_ViewType = -1;
  m_ScriptType = 0;
  m_ShowNonCheckedOut = FALSE;
  m_AutoCheckScripts = FALSE;
  //}}AFX_DATA_INIT

  InCritical = false;
}

void CScriptLevelInterface::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CScriptLevelInterface)
  DDX_Control(pDX, IDC_LIST_AVAILABLE, m_ListAvailable);
  DDX_Control(pDX, IDC_LIST_CHECKEDOUT, m_ListCheckedOut);
  DDX_Control(pDX, IDC_SELECTED_SCRIPT, m_ScriptToCompile);
  DDX_Radio(pDX, IDC_RADIO_LEVELS, m_ViewType);
  DDX_Radio(pDX, IDC_SCRIPTGAME, m_ScriptType);
  DDX_Check(pDX, IDC_LIST_NONCHECKED_OUT, m_ShowNonCheckedOut);
  DDX_Check(pDX, IDC_AUTOCHECKSCRIPTS, m_AutoCheckScripts);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptLevelInterface, CDialog)
//{{AFX_MSG_MAP(CScriptLevelInterface)
ON_BN_CLICKED(IDC_CHECKOUT, OnCheckout)
ON_BN_CLICKED(IDC_CHECKIN, OnCheckin)
ON_BN_CLICKED(IDC_UNDOCHECKOUT, OnUndocheckout)
ON_BN_CLICKED(IDC_RADIO_SCRIPTS, OnRadioScripts)
ON_BN_CLICKED(IDC_RADIO_LEVELS, OnRadioLevels)
ON_BN_CLICKED(IDC_COMPILE, OnCompile)
ON_BN_CLICKED(IDC_EDITSCRIPT, OnEditscript)
ON_CBN_CLOSEUP(IDC_SELECTED_SCRIPT, OnCloseupSelectedScript)
ON_BN_CLICKED(IDC_ADDNEW, OnAddnew)
ON_BN_CLICKED(IDC_DELETE, OnDelete)
ON_BN_CLICKED(IDC_CREATESCRIPT, OnCreatescript)
ON_WM_CLOSE()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_CONFIGCOMPILER, OnConfigcompiler)
ON_BN_CLICKED(IDC_MASSCOMPILE, OnMasscompile)
ON_CBN_SELCHANGE(IDC_SELECTED_SCRIPT, OnSelchangeSelectedScript)
ON_BN_CLICKED(IDC_LIST_NONCHECKED_OUT, OnListNoncheckedOut)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptLevelInterface message handlers

void CScriptLevelInterface::SetStatus(char *str) {
  CWnd *wnd = (CWnd *)GetDlgItem(IDC_STATUS);
  wnd->SetWindowText(str);
  App()->defer();
}

void CScriptLevelInterface::OnCheckout() {
  UpdateData(true);
  InCritical = true;
  SetStatus("Checking out files");
  if (m_ViewType == 0) {
    // we're working with levels & level scripts
    if (CheckOutLevels())
      UpdateDialog();
  } else {
    // we're working with game scripts
    if (CheckOutScripts())
      UpdateDialog();
  }
  InCritical = false;
  SetStatus("Ready");
  Scripts_need_sync = true;
}

void CScriptLevelInterface::OnCheckin() {
  UpdateData(true);
  InCritical = true;
  SetStatus("Checking in files");
  if (m_ViewType == 0) {
    // we're working with levels & level scripts
    if (CheckInLevels())
      UpdateDialog();
  } else {
    // we're working with game scripts
    if (CheckInScripts())
      UpdateDialog();
  }
  InCritical = false;
  SetStatus("Ready");
}

void CScriptLevelInterface::OnUndocheckout() {
  UpdateData(true);
  InCritical = true;
  SetStatus("Undoing Checkout on files");
  if (m_ViewType == 0) {
    // we're working with levels & level scripts
    if (UndoCheckOutLevels())
      UpdateDialog();
  } else {
    // we're working with game scripts
    if (UndoCheckOutScripts())
      UpdateDialog();
  }
  InCritical = false;
  SetStatus("Ready");
  Scripts_need_sync = true;
}

void CScriptLevelInterface::OnRadioScripts() { UpdateDialog(); }

void CScriptLevelInterface::OnRadioLevels() { UpdateDialog(); }

CEdit *CompileOutputWindow;
CString CompileOutputData;

void CompileOutputCallback(char *str) {
  CompileOutputData += str;
  CompileOutputWindow->SetWindowText(CompileOutputData);
}

void CScriptLevelInterface::OnCompile() {
  UpdateData(true);

  SetStatus("Compiling...");

  bool dll_exist = true;

  char buffer[_MAX_PATH], filename[_MAX_PATH];
  m_ScriptToCompile.GetLBText(m_ScriptToCompile.GetCurSel(), buffer);
  ddio_SplitPath(buffer, NULL, filename, NULL);
  strcat(filename, ".dll");
  if (!cfexist(filename)) {
    // there isn't a dll yet...lets make sure one isn't in the manage system
    bool found;
    int i;

    found = false;
    for (i = 0; i < MAX_GAMEFILES; i++) {
      if (Gamefiles[i].used && (!stricmp(filename, Gamefiles[i].name))) {
        found = true;
        break;
      }
    }

    if (!found) {
      // ok there wasn't one in the gamefiles make sure there isn't a tracklocked
      if (mng_FindTrackLock(filename, PAGETYPE_GAMEFILE) == -1) {
        // there isn't one in the track lock...this is our first compile!
        dll_exist = false;
      }
    }
  }

  tCompilerInfo ci;
  ci.callback = CompileOutputCallback;
  ci.script_type = (m_ScriptType == 0) ? ST_GAME : ST_LEVEL;
  strcpy(ci.source_filename, buffer);
  CompileOutputWindow = (CEdit *)GetDlgItem(IDC_COMPILER_OUTPUT);
  CompileOutputData = "";

  ScriptCompile(&ci);

  SetStatus("Ready");
  CompileOutputData = ""; // no need for this to hang around

  if (!dll_exist && cfexist(filename)) {
    // yeah! we created a dll, ask the user if they want to put it into the manage system
    if (Network_up) {
      sprintf(buffer,
              "Congratulations! It looks like a dll was successfully created. I\ndon't see the DLL in the manage "
              "system, so\nwould you like me to add it into the manage system for you?(HIGHLY recommended)");
      if (MessageBox(buffer, "Congratulations", MB_YESNO) == IDYES) {
        ddio_MakePath(buffer, LocalScriptDir, filename, NULL);
        if (!cfexist(buffer)) {
          sprintf(buffer,
                  "I can't seem to find %s in your data\\scripts directory...Sorry,\nbut I can't automatically add it "
                  "for you.\nYou'll have to manually add %s into the manage system.",
                  filename, filename);
          MessageBox(buffer, "Uh Oh!", MB_OK);
        } else {
          if (AddNewGameFile(buffer, "scripts")) {
            sprintf(buffer,
                    "%s has been added into the manage system.  Don't forget to check it in to make sure it stays in "
                    "the\nmanage system!",
                    filename);
            MessageBox(buffer, "Success", MB_OK);
          } else {
            sprintf(buffer,
                    "There was a problem adding %s\ninto the manage system. You'll have\nto do it automatically.",
                    filename);
            MessageBox(buffer, "Error", MB_OK);
          }
        }
      }
    } else {
      sprintf(buffer, "Doh! Congratulations! You compiled the DLL successfully.  However,\nI don't see it in the "
                      "manage system.  I'd offer to add it\nautomatically for you, but you said NO to the\ndata "
                      "update.  You'll have to add it manually.");
      MessageBox(buffer, "Doh!", MB_OK);
    }
  }
}

void CScriptLevelInterface::OnEditscript() {
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_SELECTED_SCRIPT);
  if (!combo)
    return;

  char tempbuf[_MAX_PATH], fullpath[_MAX_PATH];

  int index = combo->GetCurSel();
  combo->GetLBText(index, tempbuf);

  if (m_ShowNonCheckedOut && (mng_FindTrackLock(tempbuf, PAGETYPE_GAMEFILE) == -1)) {
    // display a warning that this file is not checked out
    MessageBox("This file is NOT checked out, you'll lose all changes on your\nnext data update!", "Warning", MB_OK);
  }

  ddio_MakePath(fullpath, LocalScriptDir, tempbuf, NULL);
  if (!cfexist(fullpath)) {
    sprintf(tempbuf, "Weird, I couldn't find %s to open...", fullpath);
    MessageBox(tempbuf, "Error", MB_OK);
    return;
  }

  SHELLEXECUTEINFO sei;

  sei.cbSize = sizeof(sei);
  sei.fMask = SEE_MASK_NOCLOSEPROCESS;
  sei.hwnd = m_hWnd;
  sei.lpVerb = "open";
  sei.lpFile = fullpath;
  sei.lpParameters = NULL;
  sei.lpDirectory = LocalScriptDir;
  sei.nShow = SW_NORMAL;

  // int res = (int)ShellExecute(m_hWnd,"open",fullpath,NULL,LocalScriptDir,0);
  int res;

  ShellExecuteEx(&sei);
  res = (int)sei.hInstApp;

  if (res <= 32) {
    char buffer[256];
    switch (res) {
    case 0:
      strcpy(buffer, "The operating system is out of memory or resources.");
      break;
    case ERROR_FILE_NOT_FOUND:
      strcpy(buffer, "The specified file was not found.");
      break;
    case ERROR_PATH_NOT_FOUND:
      strcpy(buffer, "The specified path was not found.");
      break;
    case ERROR_BAD_FORMAT:
      strcpy(buffer, "The .exe file is invalid (non-Win32� .exe or error in .exe image).");
      break;
    case SE_ERR_ACCESSDENIED:
      strcpy(buffer, "The operating system denied access to the specified file.");
      break;
    case SE_ERR_ASSOCINCOMPLETE:
      strcpy(buffer, "The file name association is incomplete or invalid.");
      break;
    case SE_ERR_DDEBUSY:
      strcpy(buffer, "The DDE transaction could not be completed because other DDE transactions were being processed.");
      break;
    case SE_ERR_DDEFAIL:
      strcpy(buffer, "The DDE transaction failed.");
      break;
    case SE_ERR_DDETIMEOUT:
      strcpy(buffer, "The DDE transaction could not be completed because the request timed out.");
      break;
    case SE_ERR_DLLNOTFOUND:
      strcpy(buffer, "The specified dynamic-link library was not found.");
      break;
    // case SE_ERR_FNF:
    //	strcpy(buffer,"The specified file was not found.");
    //	break;
    case SE_ERR_NOASSOC:
      strcpy(buffer, "There is no application associated with the given file name extension.\nGet Jeff and he'll fix "
                     "this problem for you quickly and easily.");
      break;
    case SE_ERR_OOM:
      strcpy(buffer, "There was not enough memory to complete the operation.");
      break;
    // case SE_ERR_PNF:
    //	strcpy(buffer,"The specified path was not found.");
    //	break;
    case SE_ERR_SHARE:
      strcpy(buffer, "A sharing violation occurred.");
      break;
    default:
      strcpy(buffer, "An unknown error occurred");
      break;
    }
    MessageBox(buffer, "Error", MB_OK);
  }

  Scripts_need_sync = true;
}

void CScriptLevelInterface::OnCloseupSelectedScript() {
  UpdateData(true);

  SetStatus("Determining script type...");

  char buffer[_MAX_PATH];
  int currsel = m_ScriptToCompile.GetCurSel();
  if (currsel >= 0) {
    m_ScriptToCompile.GetLBText(currsel, buffer);

    strcpy(LastScriptSelected, buffer);

    uint8_t type = DetermineScriptType(buffer);

    switch (type) {
    case ST_GAME:
      m_ScriptType = 0;
      break;
    case ST_LEVEL:
      m_ScriptType = 1;
      break;
    }

    UpdateData(false);
  }

  SetStatus("Ready");
}

void CScriptLevelInterface::OnSelchangeSelectedScript() { OnCloseupSelectedScript(); }

void CScriptLevelInterface::UpdateAvailableWithLevels() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_AVAILABLE);
  if (!list)
    return;

  list->ResetContent();

  SetStatus("Updating available levels");

  char buffer[_MAX_PATH];
  int length;

  for (int i = 0; i < MAX_GAMEFILES; i++) {
    if (Gamefiles[i].used) {
      // we're only adding .d3l's to this list
      length = strlen(Gamefiles[i].name);
      if (!stricmp(&Gamefiles[i].name[length - 4], ".d3l") &&
          (mng_FindTrackLock(Gamefiles[i].name, PAGETYPE_GAMEFILE) == -1)) {
        strcpy(buffer, Gamefiles[i].name);
        buffer[length - 4] = '\0';
        list->AddString(buffer);
      }
    }
  }

  SetStatus("Ready");
}

void CScriptLevelInterface::UpdateAvailableWithScripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_AVAILABLE);
  if (!list)
    return;

  list->ResetContent();

  SetStatus("Updating available scripts");

  char buffer[_MAX_PATH];
  int length;

  for (int i = 0; i < MAX_GAMEFILES; i++) {
    if (Gamefiles[i].used) {
      // we're only adding .d3l's to this list
      length = strlen(Gamefiles[i].name);
      if (!stricmp(&Gamefiles[i].name[length - 4], ".cpp") &&
          (mng_FindTrackLock(Gamefiles[i].name, PAGETYPE_GAMEFILE) == -1)) {
        strcpy(buffer, Gamefiles[i].name);
        buffer[length - 4] = '\0';
        list->AddString(buffer);
      }
    }
  }

  SetStatus("Ready");
}

void CScriptLevelInterface::UpdateCheckedOutWithLevels() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  if (!list)
    return;

  list->ResetContent();

  SetStatus("Updating checked out levels");

  char buffer[_MAX_PATH];
  int length;

  for (int i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_GAMEFILE) {

      length = strlen(GlobalTrackLocks[i].name);
      if (!stricmp(&GlobalTrackLocks[i].name[length - 4], ".d3l")) {
        strcpy(buffer, GlobalTrackLocks[i].name);
        buffer[length - 4] = '\0';
        list->AddString(buffer);
      }
    }
  }

  SetStatus("Ready");
}

void CScriptLevelInterface::UpdateCheckedOutWithScripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  if (!list)
    return;

  list->ResetContent();

  SetStatus("Updating checked out scripts");

  char buffer[_MAX_PATH];
  int length;

  for (int i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_GAMEFILE) {

      length = strlen(GlobalTrackLocks[i].name);
      if (!stricmp(&GlobalTrackLocks[i].name[length - 4], ".cpp")) {
        strcpy(buffer, GlobalTrackLocks[i].name);
        buffer[length - 4] = '\0';
        list->AddString(buffer);
      }
    }
  }

  SetStatus("Ready");
}

void CScriptLevelInterface::UpdateScriptListWithLevels() {
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_SELECTED_SCRIPT);
  if (!combo)
    return;

  combo->ResetContent();

  SetStatus("Updating script list of level scripts");

  char buffer[_MAX_PATH];
  int length, i;

  if (m_ShowNonCheckedOut) {
    char olddir[_MAX_PATH];
    ddio_GetWorkingDir(olddir, _MAX_PATH);
    ddio_SetWorkingDir(LocalScriptDir);

    for (i = 0; i < MAX_GAMEFILES; i++) {
      if (Gamefiles[i].used) {
        // look for d3l's
        length = strlen(Gamefiles[i].name);

        if (length > 4 && !stricmp(&Gamefiles[i].name[length - 4], ".d3l")) {
          strcpy(buffer, Gamefiles[i].name);
          buffer[length - 4] = '\0';
          strcat(buffer, ".cpp");

          // ok we have a d3l, look to see if there is a script available for it
          char temp[_MAX_PATH];
          if (ddio_FindFileStart(buffer, temp)) {
            combo->AddString(buffer);
          }
          ddio_FindFileClose();
          /*
          for ( int j=0; j<MAX_GAMEFILES;j++){
                  if(!stricmp(Gamefiles[j].name,buffer)){
                          //we found a corresponding script
                          combo->AddString(buffer);
                          break;
                  }
          }
          */
        }
      }
    }

    ddio_SetWorkingDir(olddir);
  } else {

    for (i = 0; i < MAX_TRACKLOCKS; i++) {
      if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_GAMEFILE) {

        // look for checked out d3l's
        length = strlen(GlobalTrackLocks[i].name);

        if (length > 4 && !stricmp(&GlobalTrackLocks[i].name[length - 4], ".d3l")) {
          strcpy(buffer, GlobalTrackLocks[i].name);
          buffer[length - 4] = '\0';
          strcat(buffer, ".cpp");

          // ok we have a checked out d3l, look to see if there is a script available for it
          for (int j = 0; j < MAX_TRACKLOCKS; j++) {
            if (!stricmp(GlobalTrackLocks[j].name, buffer)) {
              // we found a corresponding script...
              combo->AddString(buffer);
              break;
            }
          }
        }
      }
    }
  }

  if (LastScriptSelected[0] != '\0' && cfexist(LastScriptSelected))
    combo->SetCurSel(combo->FindStringExact(0, LastScriptSelected));
  else
    combo->SetCurSel(0);

  SetStatus("Ready");
}

void CScriptLevelInterface::UpdateScriptListWithScripts() {
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_SELECTED_SCRIPT);
  if (!combo)
    return;

  combo->ResetContent();

  SetStatus("Updating script list with scripts");

  char buffer[_MAX_PATH];
  int length, i;

  if (m_ShowNonCheckedOut) {
    char olddir[_MAX_PATH];
    ddio_GetWorkingDir(olddir, _MAX_PATH);
    ddio_SetWorkingDir(LocalScriptDir);

    if (ddio_FindFileStart("*.cpp", buffer)) {
      combo->AddString(buffer);
      while (ddio_FindNextFile(buffer)) {
        combo->AddString(buffer);
      }
    }
    ddio_FindFileClose();

    ddio_SetWorkingDir(olddir);

    /*
    for (i=0;i<MAX_GAMEFILES;i++){
            if(Gamefiles[i].used){

                    //look for cpp's
                    length = strlen(Gamefiles[i].name);

                    if(length>4 && !stricmp(&Gamefiles[i].name[length-4],".cpp")){
                            strcpy(buffer,Gamefiles[i].name);
                            combo->AddString(buffer);
                    }
            }
    }
    */

  } else {

    for (i = 0; i < MAX_TRACKLOCKS; i++) {
      if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == PAGETYPE_GAMEFILE) {

        // look for checked out cpp's
        length = strlen(GlobalTrackLocks[i].name);

        if (length > 4 && !stricmp(&GlobalTrackLocks[i].name[length - 4], ".cpp")) {
          strcpy(buffer, GlobalTrackLocks[i].name);
          combo->AddString(buffer);
        }
      }
    }
  }

  if (LastScriptSelected[0] != '\0' && cfexist(LastScriptSelected))
    combo->SetCurSel(combo->FindStringExact(0, LastScriptSelected));
  else
    combo->SetCurSel(0);

  SetStatus("Ready");
}

void CScriptLevelInterface::UpdateDialog() {
  UpdateData(true);

  CWnd *stat1, *stat2;
  stat1 = (CWnd *)GetDlgItem(IDC_AVAILABLE_GRP);
  stat2 = (CWnd *)GetDlgItem(IDC_CHECKEDOUT_GRP);

  if (m_ViewType == 0) {
    // we're working with levels & level scripts
    UpdateAvailableWithLevels();
    UpdateCheckedOutWithLevels();
    UpdateScriptListWithLevels();
    stat1->SetWindowText("Levels Available");
    stat2->SetWindowText("Levels CheckedOut");
  } else {
    // we're working with game scripts
    UpdateAvailableWithScripts();
    UpdateCheckedOutWithScripts();
    UpdateScriptListWithScripts();
    stat1->SetWindowText("Scripts Available");
    stat2->SetWindowText("Scripts CheckedOut");
  }
}

BOOL CScriptLevelInterface::OnInitDialog() {
  CDialog::OnInitDialog();
  int value;
  bool bvalue;

  // restore settings
  if (Database()->read_int("EditorScriptViewType", &value)) {
    m_ViewType = value;
  } else {
    m_ViewType = 0;
  }

  if (Database()->read_int("EditorScriptType", &value)) {
    m_ScriptType = value;
  } else {
    m_ScriptType = 0;
  }

  if (Database()->read("EditorScriptShowNonCheckedOut", &bvalue)) {
    m_ShowNonCheckedOut = bvalue;
  } else {
    m_ShowNonCheckedOut = 0;
  }

  if (Database()->read("EditorAutoCheckScriptsWithLevels", &bvalue)) {
    m_AutoCheckScripts = bvalue;
  } else {
    m_AutoCheckScripts = 0;
  }

  value = 256;
  if (!Database()->read("EditorLastScript", LastScriptSelected, &value)) {
    LastScriptSelected[0] = '\0';
  }

  UpdateData(false);
  UpdateDialog();

  SetStatus("Ready");

  return TRUE;
}

void CScriptLevelInterface::OnAddnew() {
  InCritical = true;
  SetStatus("Adding new files");

  if (m_ViewType == 0) {
    // we're working with levels & level scripts
    if (AddNewLevel())
      UpdateDialog();
  } else {
    // we're working with game scripts
    if (AddNewScript())
      UpdateDialog();
  }
  InCritical = false;
  SetStatus("Ready");
  Scripts_need_sync = true;
}

void CScriptLevelInterface::OnDelete() {
  UpdateData(true);
  InCritical = true;
  SetStatus("Deleting files");

  if (m_ViewType == 0) {
    if (DeleteLevel())
      UpdateDialog();
  } else {
    if (DeleteScript())
      UpdateDialog();
  }

  InCritical = false;
  SetStatus("Ready");
}

void CScriptLevelInterface::OnCreatescript() {
  CCreateNewScriptDlg dlg;

  if (dlg.DoModal()) {
    int i;
    char filename[_MAX_PATH];
    strcpy(filename, dlg.m_Filename.GetBuffer(0));

    // see if we should add this to the manage system
    for (i = 0; i < MAX_GAMEFILES; i++) {
      if (Gamefiles[i].used && (!stricmp(Gamefiles[i].name, filename))) {
        // ok we found the file...no need to add it
        break;
      }
    }

    bool on_network = false;

    if (i < MAX_GAMEFILES || (mng_FindTrackLock(filename, PAGETYPE_GAMEFILE) != -1)) {
      char buffer[_MAX_PATH];
      sprintf(buffer,
              "Just so you know, %s\nalready exists in the manage system, do you still want\nto create a new file of "
              "the same name?",
              filename);
      on_network = true;
      if (MessageBox(buffer, "Warning", MB_YESNO) != IDYES)
        return;
    }

    if (!ScriptCreateEmptyScript(filename, (dlg.m_ScriptType == 0) ? ST_LEVEL : ST_GAME)) {
      MessageBox("Unable to create file", "Error", MB_OK);
      return;
    }

    bool added_to_network = false;

    // we never found the file in the manage system
    if (!on_network) {
      if (Network_up) {
        char buffer[_MAX_PATH + 100];
        sprintf(buffer, "Do you want to add\n%s\nto the network?", filename);

        if (cfexist(filename) && MessageBox(buffer, "Add to Data", MB_YESNO) == IDYES) {
          ddio_MakePath(buffer, LocalScriptDir, filename, NULL);
          AddNewGameFile(buffer, "scripts");
          UpdateDialog();
          added_to_network = true;
        }
      } else {
        // doh! they didn't say yes
        char buffer[_MAX_PATH];
        sprintf(buffer, "I would ask you if you wanted to add the new\nscript to the manage system, but\nsince you "
                        "said no to the data update, you'll have\nto add it manually");
        MessageBox(buffer, "Doh!", MB_OK);
      }

      // now auto-compile the DLL
      SetStatus("Initial Compile");
      tCompilerInfo ci;
      ci.callback = CompileOutputCallback;
      ci.script_type = (dlg.m_ScriptType == 0) ? ST_LEVEL : ST_GAME;
      strcpy(ci.source_filename, filename);
      CompileOutputWindow = (CEdit *)GetDlgItem(IDC_COMPILER_OUTPUT);
      CompileOutputData = "";
      ScriptCompile(&ci);

      if (Network_up) {
        SetStatus("Adding compiled script to manage system");
        char dllname[_MAX_PATH], buffer[_MAX_PATH];
        ddio_SplitPath(filename, NULL, dllname, NULL);
        strcat(dllname, ".dll");
        if (cfexist(dllname) && added_to_network) {
          ddio_MakePath(buffer, LocalScriptDir, dllname, NULL);
          AddNewGameFile(buffer, "scripts");
          UpdateDialog();
        }

        SetStatus("Auto-Checking in");

      try_again:
        if (!mng_MakeLocker())
          goto try_again;

        bool sscr = CheckInGamefile(filename, false);
        bool cscr = CheckInGamefile(dllname, false);

        SetStatus("Auto-Checking out");
        if (sscr)
          CheckOutGamefile(filename, false);
        if (cscr)
          CheckOutGamefile(dllname, false);

        mng_EraseLocker();
      }
    }
  }

  SetStatus("Ready");
}

void CScriptLevelInterface::OnConfigcompiler() {
  CVirtualCompilerConfig dlg;

  SetStatus("Configuring Compiler");
  dlg.DoModal();
  SetStatus("Ready");
}

void CScriptLevelInterface::OnClose() {
  if (InCritical)
    return;

  CDialog::OnClose();
}

void CScriptLevelInterface::OnDestroy() { CDialog::OnDestroy(); }

void CScriptLevelInterface::OnOK() {
  UpdateData(true);

  // write out settings
  Database()->write("EditorScriptViewType", m_ViewType);
  Database()->write("EditorScriptType", m_ScriptType);
  Database()->write("EditorScriptShowNonCheckedOut", m_ShowNonCheckedOut);
  Database()->write("EditorLastScript", LastScriptSelected, strlen(LastScriptSelected) + 1);
  Database()->write("EditorAutoCheckScriptsWithLevels", m_AutoCheckScripts);

  CDialog::OnOK();
}

void CScriptLevelInterface::OnMasscompile() {
  CScriptMassCompile dlg;
  SetStatus("Mass compiling scripts...");
  dlg.DoModal();
  UpdateDialog();
  SetStatus("Ready");
}

void CScriptLevelInterface::OnListNoncheckedOut() { UpdateDialog(); }

// ======================File Checkin/Checkout Functions======================
bool CScriptLevelInterface::AddNewLevel(void) {
  char filename[255];

  if (!Network_up) {
    OutrageMessageBox("You need to say Yes on the initial data update, in order to\nadd files\n");
    return false;
  }

  // Get the filename of the representing image
  CString filter = "Descent III Levels (*.d3l)|*.d3l||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_files_dir, sizeof(Current_files_dir)))
    return false;

  return AddNewGameFile(filename, "levels");
}

bool CScriptLevelInterface::AddNewScript(void) {
  char filename[255];

  if (!Network_up) {
    OutrageMessageBox("You need to say Yes on the initial data update, in order to\nadd files\n");
    return false;
  }

  // Get the filename of the representing image
  CString filter = "Descent III Script Source (*.cpp)|*.cpp|Descent III Compiled Script (*.dll)|*.dll||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_files_dir, sizeof(Current_files_dir)))
    return false;

  return AddNewGameFile(filename, "scripts");
}

bool DeleteGamefile(char *tempbuffer) {
  int tl;
  mngs_Pagelock pl;
  bool removed = false;

  // verify that we have it locked
  if ((tl = mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE)) == -1) {
    OutrageMessageBox("%s is not yours to delete. Hmmm. Get Jeff", tempbuffer);
    Int3();
    return false;
  }

  strcpy(pl.name, tempbuffer);
  pl.pagetype = PAGETYPE_GAMEFILE;

  // Check to see if this is a local gamefile only.  If so, only delete it locally
  if (mng_CheckIfPageOwned(&pl, TableUser) != 1) {
    mng_FreeTrackLock(tl);
    if (!mng_DeletePage(tempbuffer, PAGETYPE_GAMEFILE, 1)) {
      mprintf(0, ErrorString);
      Int3();
    } else {
      removed = true;
    }
  } else { // if its network, delete it from both the net and local drives
    mng_FreeTrackLock(tl);
    mng_DeletePage(tempbuffer, PAGETYPE_GAMEFILE, 1);
    mng_DeletePage(tempbuffer, PAGETYPE_GAMEFILE, 0);
    mng_DeletePagelock(tempbuffer, PAGETYPE_GAMEFILE);
    removed = true;
  }

  if (removed) {
    for (int gf = 0; gf < MAX_GAMEFILES; gf++) {
      if (Gamefiles[gf].used && (!stricmp(tempbuffer, Gamefiles[gf].name))) {
        FreeGamefile(gf);
        break;
      }
    }
  }

  return true;
}

bool AddNewGameFile(char *fullpath, char *directory) {
  char cur_name[100];
  char pathname[100], name[100], extension[100];
  int gamefile_handle;

  if (!Network_up) {
    return false;
  }

  //	Okay, we selected a file. Lets do what needs to be done here.
  ddio_SplitPath(fullpath, pathname, name, extension);
  sprintf(cur_name, "%s%s", name, extension);

  if ((FindGamefileName(cur_name)) != -1) {
    OutrageMessageBox("There is already a file with that name.  Rename the file and then try to add it.");
    return false;
  }

  gamefile_handle = AllocGamefile();

  strcpy(Gamefiles[gamefile_handle].name, cur_name);
  strcpy(Gamefiles[gamefile_handle].dir_name, directory);

  // Finally, save a local copy of the model/anim and alloc a tracklock
  mprintf(0, "Making a copy of this file locally...\n");

  char destname[100];
  ddio_MakePath(destname, LocalD3Dir, "data", directory, Gamefiles[gamefile_handle].name, NULL);
  if (stricmp(destname, fullpath)) // only copy if they are different
    cf_CopyFile(destname, fullpath);

  mng_AllocTrackLock(cur_name, PAGETYPE_GAMEFILE);
  return true;
}

bool CheckInGamefile(char *tempbuffer, bool show_ok_confirmation) {
  mngs_Pagelock temp_pl;
  int r, n;

  for (n = 0; n < MAX_GAMEFILES; n++) {
    if (Gamefiles[n].used && (!stricmp(Gamefiles[n].name, tempbuffer))) {
      break;
    }
  }

  if (n == MAX_GAMEFILES)
    return false;

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
      AfxMessageBox(ErrorString, MB_OK);
      return false;
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

        // Delete it from local pagefile if its there
        int dret = mng_DeletePage(Gamefiles[n].name, PAGETYPE_GAMEFILE, 1);
        ASSERT(dret == 1);

        // Free the tracklock
        int p = mng_FindTrackLock(Gamefiles[n].name, PAGETYPE_GAMEFILE);
        ASSERT(p != -1);
        mng_FreeTrackLock(p);

        if (show_ok_confirmation)
          OutrageMessageBox("%s checked in.", tempbuffer);

        // Make sure its checked in
        if (cf_Diff(destname, srcname)) {
          ASSERT(1);                      // Get Jason! File didn't check in correctly!
          cf_CopyFile(destname, srcname); // Do this so we can trace whats happening
        }
      }
    }
  }
  return true;
}

bool CheckOutGamefile(char *tempbuffer, bool show_ok_confirmation, bool report_who_has_locked) {
  int n;
  mngs_Pagelock temp_pl;
  mngs_gamefile_page gamefilepage;
  int r;

  for (n = 0; n < MAX_GAMEFILES; n++) {
    if (Gamefiles[n].used && (!stricmp(Gamefiles[n].name, tempbuffer))) {
      break;
    }
  }

  if (n == MAX_GAMEFILES)
    return false;

  // Make sure it can be locked
  strcpy(temp_pl.name, Gamefiles[n].name);
  temp_pl.pagetype = PAGETYPE_GAMEFILE;

  r = mng_CheckIfPageLocked(&temp_pl);
  if (r == 2) {
    int answer;
    answer = OutrageMessageBox(MBOX_YESNO, "This page is not even in the table file, or the database maybe corrupt.  "
                                           "Override to 'Unlocked'? (Select NO if you don't know what you're doing)");
    if (answer == IDYES) {
      strcpy(temp_pl.holder, "UNLOCKED");
      if (!mng_ReplacePagelock(temp_pl.name, &temp_pl))
        AfxMessageBox(ErrorString, MB_OK);
    }
  } else if (r < 0)
    OutrageMessageBox(ErrorString);
  else if (r == 1) {
    if (report_who_has_locked)
      OutrageMessageBox(InfoString);
  } else {

    // Everything is ok.  Tell the network we're locking it and get a copy to
    // our local drive
    strcpy(temp_pl.holder, TableUser);

    // Search thru the net pagefile and get a new copy in RAM in case anyone
    // changed it since we started the editor
    if (mng_FindSpecificGamefilePage(temp_pl.name, &gamefilepage, 0)) {
      if (mng_AssignGamefilePageToGamefile(&gamefilepage, n)) {
        if (!mng_ReplacePage(Gamefiles[n].name, Gamefiles[n].name, n, PAGETYPE_GAMEFILE, 1)) {
          OutrageMessageBox("There was problem writing that page(%s) locally!", tempbuffer);
          return false;
        } else {

          if (!mng_ReplacePagelock(temp_pl.name, &temp_pl)) {
            AfxMessageBox(ErrorString, MB_OK);
            return false;
          }
        }

        if (show_ok_confirmation)
          OutrageMessageBox("%s locked.", tempbuffer);
      } else
        OutrageMessageBox("There was a problem loading this gamefile(%s).  You might encounter problems in dealing "
                          "with it.  Good luck!",
                          tempbuffer);

      mng_AllocTrackLock(Gamefiles[n].name, PAGETYPE_GAMEFILE);
    } else
      OutrageMessageBox("Couldn't find that gamefile(%s) in the table file!", tempbuffer);
  }

  return true;
}

bool UndoCheckOutGamefile(char *tempbuffer) {
  int tl, n;
  mngs_Pagelock pl;
  mngs_gamefile_page gamefilepage;

  for (n = 0; n < MAX_GAMEFILES; n++) {
    if (Gamefiles[n].used && (!stricmp(Gamefiles[n].name, tempbuffer))) {
      break;
    }
  }

  if (n == MAX_GAMEFILES)
    return false;

  // Should have this item locked
  if ((tl = mng_FindTrackLock(Gamefiles[n].name, PAGETYPE_GAMEFILE)) == -1)
    return false;

  // Make sure its to be deleted
  if (OutrageMessageBox(MBOX_YESNO,
                        "Are you sure you want to undo your lock on %s and lose any changes you may have made?",
                        tempbuffer) != IDYES)
    return false;

  strcpy(pl.name, Gamefiles[n].name);
  pl.pagetype = PAGETYPE_GAMEFILE;

  mng_FreeTrackLock(tl);

  // Delete local page
  if (!mng_DeletePage(Gamefiles[n].name, PAGETYPE_GAMEFILE, 1)) {
    mprintf(0, ErrorString);
    Int3();
  }

  // Get old data from net
  if (!mng_FindSpecificGamefilePage(pl.name, &gamefilepage, 0)) {
    Int3();
    return false;
  }

  if (!mng_AssignGamefilePageToGamefile(&gamefilepage, n)) {
    Int3();
    return false;
  }

  return true;
}

bool CScriptLevelInterface::DeleteLevel() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char buffer[_MAX_PATH + 200];
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".d3l");

    // this item is checked...we wish to delete
    sprintf(buffer, "Are you sure you want to delete the level\n%s?", tempbuffer);
    if (MessageBox(buffer, "Friendly Warning", MB_YESNO) == IDYES) {
      // go ahead and delete the sucker!
      char t[256];
      sprintf(t, "Deleting: %s", tempbuffer);
      SetStatus(t);
      if (DeleteGamefile(tempbuffer))
        changed = true;
    }

    bool script_also;
    script_also = false;

    // ok the level has been deleted, see if there is a corresponding .cpp file
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".cpp");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // removed also...
        sprintf(buffer, "A possible level script (%s) was found, do you want\nto remove this also?", tempbuffer);
        if (m_AutoCheckScripts || MessageBox(buffer, "Friendly Warning", MB_YESNO) == IDYES) {
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Deleting: %s", tempbuffer);
          SetStatus(t);

          if (DeleteGamefile(tempbuffer)) {
            changed = true;
            script_also = true;
          }
        }
        break;
      }
    }

    // ok, now see if there was a DLL too
    if (script_also) {
      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".dll");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // removed also...
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Deleting: %s", tempbuffer);
          SetStatus(t);

          if (DeleteGamefile(tempbuffer))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".msg");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // removed also...
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Deleting: %s", tempbuffer);
          SetStatus(t);

          if (DeleteGamefile(tempbuffer))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".str");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // removed also...
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Deleting: %s", tempbuffer);
          SetStatus(t);

          if (DeleteGamefile(tempbuffer))
            changed = true;
          break;
        }
      }
    }
  }

  mng_EraseLocker();
  mem_free(index_map);

  return changed;
}

bool CScriptLevelInterface::DeleteScript() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char buffer[_MAX_PATH + 200];
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".cpp");

    // this item is checked...we wish to delete
    sprintf(buffer, "Are you sure you want to delete script source file\n%s?", tempbuffer);
    if (MessageBox(buffer, "Friendly Warning", MB_YESNO) == IDYES) {
      // go ahead and delete the sucker!
      char t[256];
      sprintf(t, "Deleting: %s", tempbuffer);
      SetStatus(t);

      if (DeleteGamefile(tempbuffer))
        changed = true;
    }

    // ok, now see if there was a DLL too
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".dll");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // removed also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "Deleting: %s", tempbuffer);
        SetStatus(t);

        if (DeleteGamefile(tempbuffer))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".msg");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // removed also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "Deleting: %s", tempbuffer);
        SetStatus(t);

        if (DeleteGamefile(tempbuffer))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".str");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // removed also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "Deleting: %s", tempbuffer);
        SetStatus(t);

        if (DeleteGamefile(tempbuffer))
          changed = true;
        break;
      }
    }
  }

  mng_EraseLocker();
  mem_free(index_map);

  return changed;
}

bool CScriptLevelInterface::CheckInScripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".cpp");

    char t[256];
    sprintf(t, "Checking In: %s", tempbuffer);
    SetStatus(t);

    // this item is checked...we wish to checkin
    if (CheckInGamefile(tempbuffer, false))
      changed = true;

    // ok, now see if there was a DLL too
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".dll");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // checked in also...
        char t[256];
        sprintf(t, "Checking In: %s", tempbuffer);
        SetStatus(t);

        if (CheckInGamefile(tempbuffer, false))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".msg");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // checked in also...
        char t[256];
        sprintf(t, "Checking In: %s", tempbuffer);
        SetStatus(t);

        if (CheckInGamefile(tempbuffer, false))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".str");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // checked in also...
        char t[256];
        sprintf(t, "Checking In: %s", tempbuffer);
        SetStatus(t);

        if (CheckInGamefile(tempbuffer, false))
          changed = true;
        break;
      }
    }
  }

  mng_EraseLocker();

  return changed;
}

bool CScriptLevelInterface::CheckInLevels() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char buffer[_MAX_PATH + 200];
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".d3l");

    char t[256];
    sprintf(t, "Checking In: %s", tempbuffer);
    SetStatus(t);

    // go ahead and check in
    if (CheckInGamefile(tempbuffer, false))
      changed = true;

    bool script_also;
    script_also = false;

    // ok the level has been checked in, see if there is a corresponding .cpp file
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".cpp");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // checked in also...
        sprintf(buffer,
                "A possible level script (%s) was found, do you want\nto check this in also? (HIGHLY recommended)",
                tempbuffer);
        if (m_AutoCheckScripts || MessageBox(buffer, "Friendly Warning", MB_YESNO) == IDYES) {
          char t[256];
          sprintf(t, "Checking In: %s", tempbuffer);
          SetStatus(t);

          if (CheckInGamefile(tempbuffer, false)) {
            changed = true;
            script_also = true;
          }
        }
        break;
      }
    }

    // ok, now see if there was a DLL too
    if (script_also) {
      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".dll");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // checked in also...
          char t[256];
          sprintf(t, "Checking In: %s", tempbuffer);
          SetStatus(t);

          if (CheckInGamefile(tempbuffer, false))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".msg");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // checked in also...
          char t[256];
          sprintf(t, "Checking In: %s", tempbuffer);
          SetStatus(t);

          if (CheckInGamefile(tempbuffer, false))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".str");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // checked in also...
          char t[256];
          sprintf(t, "Checking In: %s", tempbuffer);
          SetStatus(t);

          if (CheckInGamefile(tempbuffer, false))
            changed = true;
          break;
        }
      }
    }
  }

  mng_EraseLocker();
  mem_free(index_map);

  return changed;
}

bool CScriptLevelInterface::CheckOutScripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_AVAILABLE);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".cpp");

    char t[256];
    sprintf(t, "Checking Out: %s", tempbuffer);
    SetStatus(t);

    // this item is checked...we wish to checkin
    if (CheckOutGamefile(tempbuffer, false))
      changed = true;

    // ok, now see if there was a DLL too
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".dll");
    for (j = 0; j < MAX_GAMEFILES; j++) {
      if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
          (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
        // ok, we found a possibly matching script...ask if they want that
        // checked out also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "Checking Out: %s", tempbuffer);
        SetStatus(t);

        if (CheckOutGamefile(tempbuffer, false))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".msg");
    for (j = 0; j < MAX_GAMEFILES; j++) {
      if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
          (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
        // ok, we found a possibly matching script...ask if they want that
        // checked out also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "Checking Out: %s", tempbuffer);
        SetStatus(t);

        if (CheckOutGamefile(tempbuffer, false))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".str");
    for (j = 0; j < MAX_GAMEFILES; j++) {
      if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
          (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
        // ok, we found a possibly matching script...ask if they want that
        // checked out also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "Checking Out: %s", tempbuffer);
        SetStatus(t);

        if (CheckOutGamefile(tempbuffer, false))
          changed = true;
        break;
      }
    }
  }

  mng_EraseLocker();
  mem_free(index_map);

  return changed;
}

bool CScriptLevelInterface::CheckOutLevels() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_AVAILABLE);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char buffer[_MAX_PATH + 200];
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".d3l");

    char t[256];
    sprintf(t, "Checking Out: %s", tempbuffer);
    SetStatus(t);

    // this item is checked...we wish to checkin
    if (CheckOutGamefile(tempbuffer, false))
      changed = true;

    bool script_also;
    script_also = false;

    // ok the level has been checked in, see if there is a corresponding .cpp file
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".cpp");
    for (j = 0; j < MAX_GAMEFILES; j++) {
      if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
          (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
        // ok, we found a possibly matching script...ask if they want that
        // checked out also...
        sprintf(buffer,
                "A possible level script (%s) was found, do you want\nto check this out also? (HIGHLY recommended)",
                tempbuffer);
        if (m_AutoCheckScripts || MessageBox(buffer, "Friendly Warning", MB_YESNO) == IDYES) {
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Checking Out: %s", tempbuffer);
          SetStatus(t);

          if (CheckOutGamefile(tempbuffer, false)) {
            changed = true;
            script_also = true;
          }
        }
        break;
      }
    }

    // ok, now see if there was a DLL too
    if (script_also) {
      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".dll");
      for (j = 0; j < MAX_GAMEFILES; j++) {
        if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
            (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
          // ok, we found a possibly matching script...ask if they want that
          // checked out also...
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Checking Out: %s", tempbuffer);
          SetStatus(t);

          if (CheckOutGamefile(tempbuffer, false))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".msg");
      for (j = 0; j < MAX_GAMEFILES; j++) {
        if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
            (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
          // ok, we found a possibly matching script...ask if they want that
          // checked out also...
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Checking Out: %s", tempbuffer);
          SetStatus(t);

          if (CheckOutGamefile(tempbuffer, false))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".str");
      for (j = 0; j < MAX_GAMEFILES; j++) {
        if ((Gamefiles[j].used) && (!stricmp(Gamefiles[j].name, tempbuffer)) &&
            (mng_FindTrackLock(tempbuffer, PAGETYPE_GAMEFILE) == -1)) {
          // ok, we found a possibly matching script...ask if they want that
          // checked out also...
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "Checking Out: %s", tempbuffer);
          SetStatus(t);

          if (CheckOutGamefile(tempbuffer, false))
            changed = true;
          break;
        }
      }
    }
  }

  mng_EraseLocker();
  mem_free(index_map);

  return changed;
}

bool CScriptLevelInterface::UndoCheckOutScripts() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".cpp");

    char t[256];
    sprintf(t, "UndoCheck Out: %s", tempbuffer);
    SetStatus(t);

    // this item is checked...we wish to checkin
    if (UndoCheckOutGamefile(tempbuffer))
      changed = true;

    // ok, now see if there was a DLL too
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".dll");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // undone also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "UndoCheck Out: %s", tempbuffer);
        SetStatus(t);

        if (UndoCheckOutGamefile(tempbuffer))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".msg");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // undone also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "UndoCheck Out: %s", tempbuffer);
        SetStatus(t);

        if (UndoCheckOutGamefile(tempbuffer))
          changed = true;
        break;
      }
    }

    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".str");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // undone also...
        // go ahead and delete the sucker!
        char t[256];
        sprintf(t, "UndoCheck Out: %s", tempbuffer);
        SetStatus(t);

        if (UndoCheckOutGamefile(tempbuffer))
          changed = true;
        break;
      }
    }
  }

  mng_EraseLocker();

  return changed;
}

bool CScriptLevelInterface::UndoCheckOutLevels() {
  CCheckListBox *list = (CCheckListBox *)GetDlgItem(IDC_LIST_CHECKEDOUT);
  int listbox_size = list->GetCount();
  int list_size = 0;
  int i;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      list_size++;
    }
  }

  if (list_size == 0)
    return false;
  int *index_map = (int *)mem_malloc(list_size * sizeof(int));
  if (!index_map)
    return false;

  int index = 0;
  for (i = 0; i < listbox_size; i++) {
    if (list->GetCheck(i)) {
      index_map[index] = i;
      index++;
    }
  }

  if (!mng_MakeLocker()) {
    mem_free(index_map);
    return false;
  }

  int j;
  bool changed = false;
  char buffer[_MAX_PATH + 200];
  char tempbuffer[_MAX_PATH];
  char savename[_MAX_PATH];

  for (i = 0; i < list_size; i++) {
    index = index_map[i];

    list->GetText(index, tempbuffer);
    strcpy(savename, tempbuffer);
    strcat(tempbuffer, ".d3l");

    char t[256];
    sprintf(t, "UndoCheck Out: %s", tempbuffer);
    SetStatus(t);

    // go ahead and check in
    if (UndoCheckOutGamefile(tempbuffer))
      changed = true;

    bool script_also;
    script_also = false;

    // ok the level has been checked in, see if there is a corresponding .cpp file
    strcpy(tempbuffer, savename);
    strcat(tempbuffer, ".cpp");
    for (j = 0; j < MAX_TRACKLOCKS; j++) {
      if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
          (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
        // ok, we found a possibly matching script...ask if they want that
        // checked in also...
        sprintf(
            buffer,
            "A possible level script (%s) was found, do you want\nto undo this check out also? (HIGHLY recommended)",
            tempbuffer);
        if (m_AutoCheckScripts || MessageBox(buffer, "Friendly Warning", MB_YESNO) == IDYES) {
          // go ahead and delete the sucker!
          char t[256];
          sprintf(t, "UndoCheck Out: %s", tempbuffer);
          SetStatus(t);

          if (UndoCheckOutGamefile(tempbuffer)) {
            changed = true;
            script_also = true;
          }
        }
        break;
      }
    }

    // ok, now see if there was a DLL too
    if (script_also) {
      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".dll");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // undone also...
          // go ahead and undo the sucker!
          char t[256];
          sprintf(t, "UndoCheck Out: %s", tempbuffer);
          SetStatus(t);

          if (UndoCheckOutGamefile(tempbuffer))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".msg");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // undone also...
          // go ahead and undo the sucker!
          char t[256];
          sprintf(t, "UndoCheck Out: %s", tempbuffer);
          SetStatus(t);

          if (UndoCheckOutGamefile(tempbuffer))
            changed = true;
          break;
        }
      }

      strcpy(tempbuffer, savename);
      strcat(tempbuffer, ".str");
      for (j = 0; j < MAX_TRACKLOCKS; j++) {
        if ((GlobalTrackLocks[j].used) && (GlobalTrackLocks[j].pagetype == PAGETYPE_GAMEFILE) &&
            (!stricmp(GlobalTrackLocks[j].name, tempbuffer))) {
          // ok, we found a possibly matching script...ask if they want that
          // undone also...
          // go ahead and undo the sucker!
          char t[256];
          sprintf(t, "UndoCheck Out: %s", tempbuffer);
          SetStatus(t);

          if (UndoCheckOutGamefile(tempbuffer))
            changed = true;
          break;
        }
      }
    }
  }

  mng_EraseLocker();
  mem_free(index_map);

  return changed;
}
// returns true if the given .cpp file is has an out of date dll (or non-existant).  Working
//	dir MUST be set to data\scripts before calling this function
bool IsScriptOutofDate(char *name) {
  bool out_of_date = false;

  HANDLE hFindFilecpp = INVALID_HANDLE_VALUE, hFindFiledll = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATA FindFileDatacpp, FindFileDatadll;
  char fname[_MAX_PATH], ext[_MAX_EXT];

  hFindFilecpp = FindFirstFile(name, &FindFileDatacpp);
  if (hFindFilecpp != INVALID_HANDLE_VALUE) {
    ddio_SplitPath(FindFileDatacpp.cFileName, NULL, fname, ext);
    strcat(fname, ".dll");

    hFindFiledll = FindFirstFile(fname, &FindFileDatadll);
    if (hFindFiledll == INVALID_HANDLE_VALUE ||
        CompareFileTime(&FindFileDatadll.ftLastWriteTime, &FindFileDatacpp.ftLastWriteTime) < 0) {
      // out of date
      out_of_date = true;
    }
    if (hFindFiledll != INVALID_HANDLE_VALUE)
      FindClose(hFindFiledll);
    hFindFiledll = INVALID_HANDLE_VALUE;
  } else {
    char error[_MAX_PATH];
    sprintf(error, "'%s' not found", name);
    AfxMessageBox(error);
    out_of_date = true;
  }
  if (hFindFilecpp != INVALID_HANDLE_VALUE)
    FindClose(hFindFilecpp);
  hFindFilecpp = INVALID_HANDLE_VALUE;

  return out_of_date;
}

#include "module.h"
#include "osiris_share.h"
extern tOSIRISModuleInit Osiris_module_init;
typedef char(DLLFUNCCALL *InitializeDLL_fp)(tOSIRISModuleInit *function_list);
typedef void(DLLFUNCCALL *ShutdownDLL_fp)(void);

// returns true if the given .cpp/.dll file is out of sync (or non-existant).  Working directory
// doesn't necessarily have to be set to data\scripts.
bool IsScriptOutofSync(char *name) {
  bool out_of_sync = false;
  InitializeDLL_fp initdll;
  ShutdownDLL_fp shutdowndll;
  module mod;

  char filename[_MAX_PATH], ext[_MAX_EXT];
  char path[_MAX_PATH];

  ddio_SplitPath(name, NULL, filename, ext);

  Osiris_module_init.string_count = 0;
  Osiris_module_init.string_table = NULL;
  Osiris_module_init.module_is_static = false;
  Osiris_module_init.module_identifier = 0;
  Osiris_module_init.script_identifier = filename;

  strcat(filename, ".dll");
  ddio_MakePath(path, LocalScriptDir, filename, NULL);
  mprintf(0, "	Checking %s...", filename);

  if (mod_LoadModule(&mod, path)) {
    initdll = (InitializeDLL_fp)mod_GetSymbol(&mod, "InitializeDLL", 4);
    if (initdll) {
      if (!initdll(&Osiris_module_init)) {
        // dll does not initialize...out of synce
        out_of_sync = true;
        mprintf(0, "OUT OF SYNC!\n");
      } else {
        mprintf(0, "Not Out of Sync\n");
        shutdowndll = (ShutdownDLL_fp)mod_GetSymbol(&mod, "ShutdownDLL", 0);
        if (shutdowndll) {
          shutdowndll();
        }
      }
    } else {
      // unable to load
      mprintf(0, "UNABLE TO GET INITIALIZEDLL\n");
    }

    mod_FreeModule(&mod);
  } else {
    mprintf(0, "MODULE NOT FOUND\n");
  }

  return out_of_sync;
}

// Returns true if there are out of date script files (only checks those in manage system)
int AreScriptsOutofDate(void) {
  if (Scripts_need_sync) {
    CScriptSyncDialog dlg;
    dlg.DoModal();
    Scripts_need_sync = false;
    return dlg.m_ErrorCount;
  }
  return 0;

  /*
  int count = 0;
  char old_dir[_MAX_PATH];

  ddio_GetWorkingDir(old_dir,_MAX_PATH);

  // First check for out-of-sync scripts (attempt load aigame and generic)
  mprintf(0,"Checking for out of sync scripts...\n");
  if(IsScriptOutofSync("aigame.dll")||IsScriptOutofSync("generic.dll"))
  {
          OutrageMessageBox(MBOX_OK,"WARNING! You have out of sync scripts...you MUST recompile your scripts!!!!!");
  }


  mprintf(0,"Checking for out of date scripts...");
  ddio_SetWorkingDir(LocalScriptDir);

  for (int i=0;i<MAX_GAMEFILES;i++){
          if (Gamefiles[i].used){
                  //we're only adding .d3l's to this list
                  int length = strlen(Gamefiles[i].name);
                  if(!stricmp(&Gamefiles[i].name[length-4],".cpp") && IsScriptOutofDate(Gamefiles[i].name)){
                          count++;
                  }
          }
  }

  ddio_SetWorkingDir(old_dir);

  mprintf(0,"Found %d OOD scripts\n",count);
  return count;
  */
}

/*
#include "psglob.h"
class tFindInManage
{
public:
        tFindInManage() {searching = false;}

        bool searching;
        bool in_Gamefiles;
        int curr_index;
        char glob_string[PAGENAME_LEN];
};
tFindInManage FindInManageData;

bool FindManageFirst(char *buffer,char *wildcard);
bool FindManageNext(char *buffer);
void FindManageClose(void);


bool FindManageFirst(char *buffer,char *wildcard)
{
        if(FindInManageData.searching)
                FindManageClose();

        FindInManageData.searching = true;
        strcpy(FindInManageData.glob_string,wildcard);
        FindInManageData.curr_index = 0;
        FindInManageData.in_Gamefiles = true;

        return FindManageNext(buffer);
}

bool FindManageNext(char *buffer)
{
        if(!FindInManageData.searching)
                return false;

        if(FindInManageData.in_Gamefiles)
        {

                for(;FindInManageData.curr_index<MAX_GAMEFILES;FindInManageData.curr_index++)
                {
                        if(Gamefiles[FindInManageData.curr_index].used &&
                                PSGlobMatch(FindInManageData.glob_string,Gamefiles[FindInManageData.curr_index].name,false,false))
                        {
                                //match
                                strcpy(buffer,Gamefiles[FindInManageData.curr_index].name);
                                FindInManageData.curr_index++;
                                return true;
                        }
                }

                FindInManageData.curr_index = 0;
                FindInManageData.in_Gamefiles = false;
        }

        for(;FindInManageData.curr_index<MAX_TRACKLOCKS;FindInManageData.curr_index++)
        {
                if(GlobalTrackLocks[FindInManageData.curr_index].used &&
GlobalTrackLocks[FindInManageData.curr_index].pagetype==PAGETYPE_GAMEFILE &&
                        PSGlobMatch(FindInManageData.glob_string,GlobalTrackLocks[FindInManageData.curr_index].name,false,false))
                {
                        //match
                        strcpy(buffer,GlobalTrackLocks[FindInManageData.curr_index].name);
                        FindInManageData.curr_index++;
                        return true;
                }
        }

        return false;
}

void FindManageClose(void)
{
        FindInManageData.searching = false;
}
*/
