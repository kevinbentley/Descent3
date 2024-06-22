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

 * $Logfile: /DescentIII/Main/editor/editor.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:37 $
 * $Author: kevinb $
 *
 * CEditorApp main MFC header
 *
 * $Log: not supported by cvs2svn $
 *
 * 12    4/16/99 3:54p Nate
 * Added Viewer Properties Dialog
 *
 * 11    1/19/99 6:53p Matt
 * Fixed a problem when the viewer was instantaneously moved from inside
 * to ourside or vise-versa.
 *
 * 10    12/23/98 4:00p Nate
 * Added DallasModelessDlgPtr data member
 *
 * 9     7/10/98 2:12p Jeff
 * added a flag for inventory information in objinfo
 *
 * 8     12/01/97 5:24p Samir
 * Make initialdir and dirlen have predefined values of 0.
 *
 * 7     12/01/97 5:17p Samir
 * New functions to open a file dialog.
 *
 * 6     9/06/97 3:06p Matt
 * Removed old trigger stuff from registry load/save
 * Added function PrintToDlgItem()
 *
 * 5     8/26/97 11:38a Samir
 * Added Editor_active global to determine whether editor is currently
 * active (useful for any window using the gr library.)
 *
 * 4     8/19/97 5:58p Samir
 * OLE additions
 *
 * 3     8/01/97 2:36p Jeff
 *
 * 2     7/24/97 2:58p Matt
 * Added functions to load and save D3EditState variables from/to the
 * registry
 *
 * 13    6/30/97 3:55p Jeff
 * Add object properties dialog
 *
 * 12    5/13/97 4:36p Samir
 * call main-frame's onidle function
 *
 * 11    2/20/97 2:52p Samir
 * Added main_view public var.
 *
 * 10    2/12/97 3:07p Samir
 * pause and resume now flush keyboard queue to stop backspace from
 * Int3ing.
 *
 * 9     2/11/97 1:42p Samir
 * Added document variable and set modification flag.
 *
 * 8     1/21/97 12:48p Samir
 * Added InitEditorState to define D3EditState info
 *
 * $NoKeywords: $
 */

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" // main symbols

#include "d3edit.h" // d3 editor header

class CTextureGrWnd;
class CWireframeGrWnd;
class CEditorView;
class CEditorDoc;
class CMainFrame;
class CDallasMainDlg;
class CViewerPropDlg;

/////////////////////////////////////////////////////////////////////////////
// CEditorApp:
// See editor.cpp for the implementation of this class
//

class CEditorApp* Editor();

class CEditorApp : public CWinApp {
private:
  CEditorApp();
  friend CEditorApp* Editor();
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEditorApp)
public:
  virtual BOOL InitInstance();
  virtual BOOL OnIdle(LONG lCount);
  virtual CDocument *OpenDocumentFile(LPCTSTR lpszFileName);
  //}}AFX_VIRTUAL

  // Implementation
  //	ADDED BY SAMIR FOR OLE SUPPORT
  COleTemplateServer m_server;
  // Server object for document creation
  //	ADDED BY SAMIR FOR OLE SUPPORT

  //{{AFX_MSG(CEditorApp)
  afx_msg void OnAppAbout();
  // NOTE - the ClassWizard will add and remove member functions here.
  //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  CTextureGrWnd *textured_view; // GrWnd views for editor
  CWireframeGrWnd *wireframe_view;
  CEditorDoc *main_doc;   // main doc object.
  CEditorView *main_view; // main view
  CMainFrame *main_frame; // the application's main_frame

  CDallasMainDlg *m_DallasModelessDlgPtr; // modeless dialog for Dallas
  CViewerPropDlg *m_ViewerPropDlgPtr;     // modeless viewer properties dialog

  void pause();
  void resume();

  BOOL paused() const { return m_Paused; };

private:
  void InitEditorState();

private:
  BOOL m_Paused;
};

extern CEditorApp theApp;
extern bool Editor_active; // this is false if we are running the game.

/////////////////////////////////////////////////////////////////////////////

// Load editor settings from the registry
void LoadEditorSettings();

// Save current editor settings to the registry
void SaveEditorSettings();

// Function to print to an edit box
// Parameters:	dlg - the dialog that the edit box is in
//					id - the ID of the edit box
//					fmt - printf-style text & arguments
void PrintToDlgItem(CDialog *dlg, int id, char *fmt, ...);

//	A quick way to use an openfiledialog/savefiledialog.
//		wnd = parent window
//		filter = a C string containing the extensions to look for in filenames when browsing (in MFC format)
//		pathname = buffer where full pathname will be stored of file opened/saved
//		initialdir = what directory to start browsing from.  will also contain the new browsing directory if
//						 user changed directories.
//		dirlen = max length of initialdir buffer including terminating null.
bool OpenFileDialog(CWnd *wnd, LPCTSTR filter, char *pathname, char *initialdir = NULL, int dirlen = 0);
bool SaveFileDialog(CWnd *wnd, LPCTSTR filter, char *pathname, char *initialdir = NULL, int dirlen = 0);

// Move the viewer object.  This should be called whenever the viewer object is moved
void MoveViewer(vector *pos, int roomnum, matrix *orient);
