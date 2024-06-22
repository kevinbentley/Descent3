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

// ScriptSyncDialog.cpp : implementation file
//

#include "mfc_compatibility.h"
#include "editor.h"
#include "ScriptSyncDialog.h"
#include "ddio.h"
#include "cfile.h"
#include "psglob.h"
#include "gamefile.h"
#include "manage.h"
#include "ScriptCompilerAPI.h"
#include "mem.h"
#include "mono.h"
#include "textaux.h"
#include "appdatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool ManageFindFirst(char *buffer, char *wildcard);
bool ManageFindNext(char *buffer);
void ManageFindClose(void);

uint8_t DetermineScriptType(char *filename);

// returns true if the given .cpp file is has an out of date dll (or non-existant).  Working
//	dir MUST be set to data\scripts before calling this function
bool IsScriptOutofDate(char *name);
// returns true if the given .cpp/.dll file is out of sync (or non-existant).  Working directory
// doesn't necessarily have to be set to data\scripts.
bool IsScriptOutofSync(char *name);

/////////////////////////////////////////////////////////////////////////////
// CScriptSyncDialog dialog

CScriptSyncDialog::CScriptSyncDialog(CWnd *pParent /*=NULL*/) : CDialog(CScriptSyncDialog::IDD, pParent) {
  //{{AFX_DATA_INIT(CScriptSyncDialog)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CScriptSyncDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CScriptSyncDialog)
  DDX_Control(pDX, IDC_LIST, m_List);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptSyncDialog, CDialog)
//{{AFX_MSG_MAP(CScriptSyncDialog)
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptSyncDialog message handlers

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl() {}

CMyListCtrl::~CMyListCtrl() {}

BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
//{{AFX_MSG_MAP(CMyListCtrl)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

#define COLUMN_NAME 0
#define COLUMN_STATE 1

#define COLUMN_NAME_SIZE 0.49f
#define COLUMN_STATE_SIZE 0.49f

void CMyListCtrl::Initialize(void) {
  ModifyStyleEx(0, LVS_EX_FULLROWSELECT);

  RECT rect;
  GetWindowRect(&rect);
  int width = rect.right - rect.left;
  int ret;

  ret = InsertColumn(COLUMN_NAME, "Name", LVCFMT_LEFT, (int)(width * COLUMN_NAME_SIZE));
  ret = InsertColumn(COLUMN_STATE, "State", LVCFMT_LEFT, (int)(width * COLUMN_STATE_SIZE));
}

int CMyListCtrl::AddItem(char *name, int num) {
  int item_count = GetItemCount();

  int added = InsertItem(item_count, name);
  if (added == -1) {
    return -1;
  }

  bool ret = CMyListCtrl::SetItem(added, num);

  if (!ret) {
    DeleteItem(added);
    return -1;
  }

  // all went ok
  return added;
}

bool CMyListCtrl::GetItem(int item, char *name, char *state) {
  int item_count = GetItemCount();

  if (item >= item_count)
    return false;

  GetItemText(item, COLUMN_NAME, name, 256);
  GetItemText(item, COLUMN_STATE, state, 40);

  return true;
}

bool CMyListCtrl::SetItem(int item, int state) {
  char buffer[256];
  switch (state) {
  case STATE_COMPILED:
    strcpy(buffer, "Compiled");
    break;
  case STATE_OOD:
    strcpy(buffer, "Out of Date");
    break;
  case STATE_ERROOD:
    strcpy(buffer, "Error/Out of Date");
    break;
  case STATE_OOS:
    strcpy(buffer, "Out of Sync");
    break;
  case STATE_ERROOS:
    strcpy(buffer, "Error/Out of Sync");
    break;
  case STATE_MISSING:
    strcpy(buffer, "Missing");
    break;
  case STATE_NOCOMPILER:
    strcpy(buffer, "No Compiler");
    break;
  }

  return (CListCtrl::SetItem(item, COLUMN_STATE, LVIF_TEXT, buffer, 0, 0, 0, 0) != FALSE);
}

void CMyListCtrl::SelectItem(int index) {
  int item_count = GetItemCount();
  if (index < 0 || index >= item_count)
    return;

  LVITEM lv;
  lv.mask = LVIF_STATE;

  lv.iSubItem = 0;
  lv.stateMask = LVIS_SELECTED;
  lv.state = 0;

  for (int i = 0; i < item_count; i++) {
    lv.iItem = i;
    CListCtrl::SetItem(&lv);
  }

  lv.iItem = index;
  lv.state = 0xFFFFFFFF;
  CListCtrl::SetItem(&lv);
}

class tManageFindIn {
public:
  tManageFindIn() { searching = false; }

  bool searching;
  bool in_Gamefiles;
  int curr_index;
  char glob_string[PAGENAME_LEN];
};
tManageFindIn ManageFindInData;

bool ManageFindFirst(char *buffer, char *wildcard) {
  if (ManageFindInData.searching)
    ManageFindClose();

  ManageFindInData.searching = true;
  strcpy(ManageFindInData.glob_string, wildcard);
  ManageFindInData.curr_index = 0;
  ManageFindInData.in_Gamefiles = true;

  return ManageFindNext(buffer);
}

bool ManageFindNext(char *buffer) {
  if (!ManageFindInData.searching)
    return false;

  if (ManageFindInData.in_Gamefiles) {

    for (; ManageFindInData.curr_index < MAX_GAMEFILES; ManageFindInData.curr_index++) {
      if (Gamefiles[ManageFindInData.curr_index].used &&
          PSGlobMatch(ManageFindInData.glob_string, Gamefiles[ManageFindInData.curr_index].name, false, false)) {
        // match
        strcpy(buffer, Gamefiles[ManageFindInData.curr_index].name);
        ManageFindInData.curr_index++;
        return true;
      }
    }

    ManageFindInData.curr_index = 0;
    ManageFindInData.in_Gamefiles = false;
  }

  for (; ManageFindInData.curr_index < MAX_TRACKLOCKS; ManageFindInData.curr_index++) {
    if (GlobalTrackLocks[ManageFindInData.curr_index].used &&
        GlobalTrackLocks[ManageFindInData.curr_index].pagetype == PAGETYPE_GAMEFILE &&
        PSGlobMatch(ManageFindInData.glob_string, GlobalTrackLocks[ManageFindInData.curr_index].name, false, false)) {
      // match
      strcpy(buffer, GlobalTrackLocks[ManageFindInData.curr_index].name);
      ManageFindInData.curr_index++;
      return true;
    }
  }

  return false;
}

void ManageFindClose(void) { ManageFindInData.searching = false; }

/////////////////////////////////////////////////////////////////
BOOL CScriptSyncDialog::OnInitDialog() {
  CDialog::OnInitDialog();
  early_exit = false;
  first_paint = true;
  m_InStuff = false;
  m_Done = false;
  m_Index = 0;
  m_NumFiles = 0;
  m_HasCompiler = -1;
  m_Files = NULL;
  m_FillingIn = true;
  m_ErrorCount = 0;
  ddio_GetWorkingDir(old_dir, _MAX_PATH);
  ddio_SetWorkingDir(LocalScriptDir);
  m_List.Initialize();
  BuildList();

  return TRUE;
}

void CScriptSyncDialog::defer(void) {
  MSG msg;

  while (1) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        //	QUIT APP.
        early_exit = true;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      break;
    }
  }
}

void CScriptSyncDialog::BuildList(void) {
  char buffer[256];
  m_NumFiles = 0;
  m_Files = NULL;

  if (ManageFindFirst(buffer, "*.cpp")) {
    m_NumFiles++;
    while (ManageFindNext(buffer)) {
      m_NumFiles++;
    }
  }
  ManageFindClose();

  if (m_NumFiles == 0)
    return;

  m_Files = (tFileInfo *)mem_malloc(sizeof(tFileInfo) * m_NumFiles);
  m_NumFiles = 0;

  if (ManageFindFirst(buffer, "*.cpp")) {
    strcpy(m_Files[m_NumFiles].filename, buffer);
    m_NumFiles++;

    while (ManageFindNext(buffer)) {
      strcpy(m_Files[m_NumFiles].filename, buffer);
      m_NumFiles++;
    }
  }
  ManageFindClose();
}

CString SS_CompileOutputData;

void SS_CompileOutputCallback(char *str) { SS_CompileOutputData += str; }

void CScriptSyncDialog::DoStuff(void) {
  m_InStuff = true;
  defer();

  if (m_Index >= m_NumFiles) {
    if (m_FillingIn) {
      m_FillingIn = false;
      m_Index = 0;
    } else {
      m_Done = true;
      goto done;
    }
  }

  if (m_FillingIn) {
    char dllfilename[_MAX_PATH];

    ddio_SplitPath(m_Files[m_Index].filename, NULL, dllfilename, NULL);
    strcat(dllfilename, ".dll");

    if (!cfexist(dllfilename)) {
      m_Files[m_Index].state = STATE_MISSING;
    } else {
      if (IsScriptOutofSync(m_Files[m_Index].filename)) {
        m_Files[m_Index].state = STATE_OOS;
      } else if (IsScriptOutofDate(m_Files[m_Index].filename)) {
        m_Files[m_Index].state = STATE_OOD;
      } else
        m_Files[m_Index].state = STATE_COMPILED;
    }
    m_List.AddItem(m_Files[m_Index].filename, m_Files[m_Index].state);
    m_List.EnsureVisible(m_Index, false);
  } else {
    if (m_Files) {
      switch (m_Files[m_Index].state) {
      case STATE_COMPILED:
        break;
      case STATE_MISSING:
      case STATE_OOD:
      case STATE_OOS: {
        char Compiler_path[_MAX_PATH];
        int len = _MAX_PATH;

        // attempt to recompile the script
        // make sure there is a compiler defined
        if (m_HasCompiler == -1) {
          if (Database()->read("EditorCompiler", Compiler_path, &len)) {
            if (!cfexist(Compiler_path)) {
              m_HasCompiler = 0;
            } else {
              m_HasCompiler = 1;
            }
          } else {
            m_HasCompiler = 0;
          }
        }

        if (m_HasCompiler) {
          tCompilerInfo ci;
          char dllfilename[_MAX_PATH];
          SS_CompileOutputData = "";

          m_List.EnsureVisible(m_Index, false);
          m_List.SelectItem(m_Index);
          defer();

          ci.callback = SS_CompileOutputCallback;
          ci.script_type = DetermineScriptType(m_Files[m_Index].filename);
          strcpy(ci.source_filename, m_Files[m_Index].filename);
          ScriptCompile(&ci);

          ddio_SplitPath(m_Files[m_Index].filename, NULL, dllfilename, NULL);
          strcat(dllfilename, ".dll");
          if (!cfexist(dllfilename)) {
            m_Files[m_Index].state = STATE_MISSING;
          } else {
            if (IsScriptOutofSync(m_Files[m_Index].filename)) {
              m_Files[m_Index].state = STATE_ERROOS;
            } else if (IsScriptOutofDate(m_Files[m_Index].filename)) {
              m_Files[m_Index].state = STATE_ERROOD;
            } else
              m_Files[m_Index].state = STATE_COMPILED;
          }

          if (m_Files[m_Index].state == STATE_MISSING || m_Files[m_Index].state == STATE_ERROOD ||
              m_Files[m_Index].state == STATE_ERROOS) {
            m_ErrorCount++;
            char *string;
            string = mem_strdup(SS_CompileOutputData.GetBuffer(0));
            if (string) {
              char buffer[2048];
              const char *next_line;

              mprintf(0, "===========================================\n");
              next_line = textaux_CopyTextLine(string, buffer);
              while (next_line) {
                mprintf(0, "%s\n", buffer);
                next_line = textaux_CopyTextLine(next_line, buffer);
              }
              mprintf(0, "===========================================\n");
              mem_free(string);
            }
          }
        } else {
          m_Files[m_Index].state = STATE_NOCOMPILER;
        }

        m_List.SetItem(m_Index, m_Files[m_Index].state);

      } break;
      }
    }
  }

done:
  m_Index++;
  m_InStuff = false;
}

void CScriptSyncDialog::OnPaint() {
  CPaintDC dc(this); // device context for painting

  if (first_paint) {
    first_paint = false;
    SetTimer(0x12, 200, NULL);
  }
}

void CScriptSyncDialog::OnTimer(UINT nIDEvent) {
  defer();
  if (m_Done) {
    CDialog::OnOK();
  } else {
    if (!m_InStuff && nIDEvent == 0x12) {
      DoStuff();
    }
  }

  CDialog::OnTimer(nIDEvent);

  if (!m_Done)
    SetTimer(0x12, 50, NULL);
}

void CScriptSyncDialog::OnDestroy() {
  CDialog::OnDestroy();

  if (m_Files) {
    mem_free(m_Files);
  }
  ddio_SetWorkingDir(old_dir);
}
