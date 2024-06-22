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

 * $Logfile: /DescentIII/Main/editor/editorDoc.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:37 $
 * $Author: kevinb $
 *
 * Editor Document (Level/Mission)
 *
 * $Log: not supported by cvs2svn $
 *
 * 13    4/09/99 11:59a Samir
 * lock keypad updates out if loading level.
 *
 * 12    3/22/99 6:26p Matt
 * Cleaned up error handling in cfile and editor level loads.
 *
 * 11    3/11/99 10:51a Nate
 * Added deletion of "Untitled" Dallas files when doing a New from editor
 *
 * 10    2/02/99 3:43p Josh
 *
 * 9     2/01/99 2:41p Nate
 * Added Dallas handling to New, Open, and Save
 *
 * 8     9/02/98 4:08p Matt
 * Don't reset the active texture when creating a new "document"
 *
 * 7     2/18/98 2:02p Samir
 * Fixed editor open and new/close problems.
 *
 * 6     2/17/98 8:38p Samir
 * Commented out OleDocuement code.
 *
 * 5     1/29/98 2:15p Samir
 * Implemented ObjectListModeless and Toolbar button.
 *
 * 4     11/06/97 2:48p Matt
 * Check for error when saving, and put up large message box
 *
 * 3     10/16/97 2:32p Samir
 * Fixed up some timing problems.
 *
 * 2     8/19/97 5:58p Samir
 * OLE additions
 *
 * 3     2/11/97 1:42p Samir
 * Moved file opening and closing to editorDoc where it should be.
 *
 * $NoKeywords: $
 */

// editorDoc.cpp : implementation of the CEditorDoc class
//

#include "stdafx.h"
#include "editor.h"
#include "SrvrItem.h" // ADDED FOR OLE SUPPORT
#include "editorDoc.h"
#include "ObjectListDialog.h"
#include "keypaddialog.h"
#include "MainFrm.h"

#include <string.h>

#include "d3edit.h"
#include "mono.h"
#include "game.h"
#include "HFile.h"
#include "cfile.h"
#include "ddio.h"
#include "manage.h"
#include "DallasMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Function to copy a Dallas script file
int CopyScriptFile(char *old_file, char *new_file) {
  char old_fullpath[_MAX_PATH];
  char new_fullpath[_MAX_PATH];

  ddio_MakePath(old_fullpath, LocalScriptDir, old_file, NULL);
  ddio_MakePath(new_fullpath, LocalScriptDir, new_file, NULL);

  return (cf_CopyFile(new_fullpath, old_fullpath));
}

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc

IMPLEMENT_DYNCREATE(CEditorDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CEditorDoc, COleServerDoc)
//{{AFX_MSG_MAP(CEditorDoc)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc construction/destruction

CEditorDoc::CEditorDoc() {
  // Use OLE compound files
  EnableCompoundFile();
}

CEditorDoc::~CEditorDoc() {}

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc server implementation

COleServerItem *CEditorDoc::OnGetEmbeddedItem() {
  // OnGetEmbeddedItem is called by the framework to get the COleServerItem
  //  that is associated with the document.  It is only called when necessary.

  CEditorSrvrItem *pItem = new CEditorSrvrItem(this);
  ASSERT_VALID(pItem);
  return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc serialization

void CEditorDoc::Serialize(CArchive &ar) {
  if (ar.IsStoring()) {
    // TODO: add storing code here
  } else {
    // TODO: add loading code here
  }
}

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc diagnostics

#ifdef _DEBUG
void CEditorDoc::AssertValid() const { COleServerDoc::AssertValid(); }

void CEditorDoc::Dump(CDumpContext &dc) const { COleServerDoc::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc commands

BOOL CEditorDoc::OnNewDocument() {
  // If Dallas is running, don't create a new document
  if (Editor()->m_DallasModelessDlgPtr != NULL) {
    OutrageMessageBox("The Dallas Script Editor is open!\n\n"
                      "You must close down Dallas before creating a New Level...");
    return FALSE;
  }

  if (!COleServerDoc::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  //	Reinitialize Editor State.
  mprintf(0, "Creating new level...\n");
  //	D3EditState.texdlg_texture = 0;

  //	Create new mine
  CreateNewMine();
  SetModifiedFlag(FALSE);
  Editor()->main_doc = this;

  // Remove any "Untitled" dallas script files
  char fullpath[_MAX_PATH];
  ddio_MakePath(fullpath, LocalScriptDir, "Untitled.cpp", NULL);
  ddio_DeleteFile(fullpath);
  ddio_MakePath(fullpath, LocalScriptDir, "Untitled.dll", NULL);
  ddio_DeleteFile(fullpath);
  ddio_MakePath(fullpath, LocalScriptDir, "Untitled.msg", NULL);
  ddio_DeleteFile(fullpath);

  return TRUE;
}

BOOL CEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) {
  BOOL opened;

  // If Dallas is running, don't open the document
  if (Editor()->m_DallasModelessDlgPtr != NULL) {
    OutrageMessageBox("The Dallas Script Editor is open!\n\n"
                      "You must close down Dallas before loading a new level...");
    return FALSE;
  }

  //	if (!COleServerDoc::OnOpenDocument(lpszPathName))
  //		return FALSE;

  // TODO: Add your specialized creation code here
  //	does the level always load correctly?
  mprintf(0, "Opening level %s...\n", lpszPathName);

  Editor()->pause();
  CKeypadDialog::Deactivate();
  opened = EditorLoadLevel((char *)lpszPathName);
  CKeypadDialog::Activate();
  Editor()->resume();

  if (!opened) {
    SetModifiedFlag(TRUE); // say that the old level was trashed
    return FALSE;
  }

  if (D3EditState.objmodeless_on)
    Editor()->main_frame->m_ObjModeless->Refresh();

  SetModifiedFlag(FALSE);
  Editor()->main_doc = this;

  return true;
}

BOOL CEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) {
  // TODO: Add your specialized code here and/or call the base class
  char filename[256];
  BOOL retval;

  strcpy(filename, lpszPathName);
  if (strchr(filename, '.') == 0)
    strcat(filename, ".d3l"); // check for extension

  mprintf(0, "Saving level %s...\n", lpszPathName);
  retval = (BOOL)EditorSaveLevel((char *)lpszPathName);

  if (retval)
    SetModifiedFlag(FALSE);
  else
    OutrageMessageBox("Error saving level -- Level not saved.\n\n"
                      "If you get this error trying to save a file you loaded from the network, "
                      "here's a workaround you can use to save your file:\n\n"
                      "  1. Use File/Save As to save the file with a temporary name.\n"
                      "  2. Use File/New to clear out the level.\n"
                      "  3. Load the level from the temporary file.\n"
                      "  4. Use File/Save As to save with the real name.\n\n"
                      "Matt & Samir are working on this problem.");

  // If the Save was successfull, handle the Dallas coordination
  if (retval) {

    // If Dallas is up, change its filenames
    if (Editor()->m_DallasModelessDlgPtr != NULL) {
      Editor()->m_DallasModelessDlgPtr->SetAllFilenamesToThis((char *)lpszPathName);
    }

    // Copy Dallas files (if doing a 'Save As')
    char old_filename[_MAX_PATH + 1];
    char new_filename[_MAX_PATH + 1];

    CString old_level_fname, new_level_fname;
    old_level_fname = GetPathName();
    new_level_fname = (char *)lpszPathName;

    if (old_level_fname.IsEmpty())
      strcpy(old_filename, "Untitled");
    else
      ddio_SplitPath(old_level_fname.GetBuffer(0), NULL, old_filename, NULL);

    if (new_level_fname.IsEmpty())
      strcpy(new_filename, "Untitled");
    else
      ddio_SplitPath(new_level_fname.GetBuffer(0), NULL, new_filename, NULL);

    // Make sure names are different (ie 'Save As')
    if (stricmp(old_filename, new_filename) != 0) {
      CString old_file, new_file;

      old_file.Format("%s.cpp", old_filename);
      new_file.Format("%s.cpp", new_filename);
      CopyScriptFile(old_file.GetBuffer(0), new_file.GetBuffer(0));

      old_file.Format("%s.msg", old_filename);
      new_file.Format("%s.msg", new_filename);
      CopyScriptFile(old_file.GetBuffer(0), new_file.GetBuffer(0));

      old_file.Format("%s.dll", old_filename);
      new_file.Format("%s.dll", new_filename);
      CopyScriptFile(old_file.GetBuffer(0), new_file.GetBuffer(0));
    }
  }

  return retval;
}

void CEditorDoc::OnCloseDocument() {
  // TODO: Add your specialized code here and/or call the base class
  COleServerDoc::OnCloseDocument();
  mprintf(0, "Closing current level...\n");

  Editor()->main_doc = NULL;
}

BOOL CEditorDoc::SaveModified() {
  BOOL return_val; // tells system what to do (save, no, etc)

  return_val = COleServerDoc::SaveModified();

  return return_val;
}
