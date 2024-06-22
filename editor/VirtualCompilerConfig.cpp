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

// VirtualCompilerConfig.cpp : implementation file
//

#include "stdafx.h"
#include "editor.h"
#include "windatabase.h"
#include "VirtualCompilerConfig.h"
#include "Descent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVirtualCompilerConfig dialog

CVirtualCompilerConfig::CVirtualCompilerConfig(CWnd *pParent /*=NULL*/)
    : CDialog(CVirtualCompilerConfig::IDD, pParent) {
  //{{AFX_DATA_INIT(CVirtualCompilerConfig)
  m_Compiler = _T("");
  m_DebugType = 0;
  m_WarningLevel = 0;
  //}}AFX_DATA_INIT
}

void CVirtualCompilerConfig::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CVirtualCompilerConfig)
  DDX_Text(pDX, IDC_COMPILER, m_Compiler);
  DDX_Radio(pDX, IDC_OPTIMIZE, m_DebugType);
  DDX_Radio(pDX, IDC_WARN_NONE, m_WarningLevel);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVirtualCompilerConfig, CDialog)
//{{AFX_MSG_MAP(CVirtualCompilerConfig)
ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualCompilerConfig message handlers

void CVirtualCompilerConfig::OnBrowse() {
  UpdateData(true);

  char filename[255];

  // Get the filename of the representing image
  CString filter = "Descent III Virtual Compiler (*.exe)|*.exe||";

  if (!OpenFileDialog(this, (LPCTSTR)filter, filename, Current_files_dir, sizeof(Current_files_dir)))
    return;

  m_Compiler = filename;

  UpdateData(false);
}

BOOL CVirtualCompilerConfig::OnInitDialog() {
  CDialog::OnInitDialog();
  char buffer[_MAX_PATH];
  int len = _MAX_PATH;

  if (Database()->read("EditorCompiler", buffer, &len)) {
    m_Compiler = buffer;
  } else {
    m_Compiler = "";
  }

  if (Database()->read_int("EditorVCWarningLevel", &len)) {
    m_WarningLevel = len;
  } else {
    m_WarningLevel = 0;
  }

  if (Database()->read_int("EditorVCDebugLevel", &len)) {
    m_DebugType = len;
  } else {
    m_DebugType = 0;
  }

  UpdateData(false);

  return TRUE;
}

void CVirtualCompilerConfig::OnOK() {
  char buffer[_MAX_PATH];
  UpdateData(true);

  strcpy(buffer, m_Compiler.GetBuffer(0));
  Database()->write("EditorCompiler", buffer, strlen(buffer) + 1);

  Database()->write("EditorVCWarningLevel", m_WarningLevel);
  Database()->write("EditorVCDebugLevel", m_DebugType);
  CDialog::OnOK();
}
