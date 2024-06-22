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

// musicutils.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "musicutils.h"
#include "musicutilsDlg.h"
#include "musicplay.h"

#include "application.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusicutilsApp

BEGIN_MESSAGE_MAP(CMusicutilsApp, CWinApp)
//{{AFX_MSG_MAP(CMusicutilsApp)
//}}AFX_MSG_MAP
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicutilsApp construction

CMusicutilsApp::CMusicutilsApp() {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMusicutilsApp object

CMusicutilsApp theApp;
oeApplication *MusicUtils = NULL;

/////////////////////////////////////////////////////////////////////////////
// CMusicutilsApp initialization

BOOL CMusicutilsApp::InitInstance() {
  AfxEnableControlContainer();

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls(); // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif

  CMusicutilsDlg dlg;
  m_pMainWnd = &dlg;
  int nResponse = dlg.DoModal();
  if (nResponse == IDOK) {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with OK
  } else if (nResponse == IDCANCEL) {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with Cancel
  }

  // Since the dialog has been closed, return FALSE so that we exit the
  //  application, rather than start the application's message pump.
  return FALSE;
}

BOOL CMusicutilsApp::OnIdle(LONG lCount) {
  // TODO: Add your specialized code here and/or call the base class

  MusicPlayFrame();

  return CWinApp::OnIdle(lCount);
}

//	Tools play song.
