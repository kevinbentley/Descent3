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

// briefinglocalizerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "briefinglocalizer.h"
#include "briefinglocalizerDlg.h"

#if defined(__LINUX__) || defined(ANDROID)
#include "linux_fix.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TITLE_TAG "$title \""
#define TITLE_TAG_LENGTH strlen(TITLE_TAG)

#define TEXT_START_TAG "$text"
#define TEXT_START_TAG_LEN strlen(TEXT_START_TAG)

#define TEXT_SHOW_TAG "show"
#define TEXT_SHOW_TAG_LEN strlen(TEXT_SHOW_TAG)

#define TEXT_END_TAG "$endtext"
#define TEXT_END_TAG_TAG_LEN strlen(TEXT_END_TAG)

#define FIND_NEXT_LINE(a, b)                                                                                           \
  do {                                                                                                                 \
    while (((b[a] == 0x0a) || (b[a] == 0x0d)) && (a < (b).GetLength()))                                                \
      a++;                                                                                                             \
  } while (0)
// a = (b).FindOneOf("\x0a\x0d"); if(a!=-1)
/////////////////////////////////////////////////////////////////////////////
// CBriefinglocalizerDlg dialog

CBriefinglocalizerDlg::CBriefinglocalizerDlg(CWnd *pParent /*=NULL*/) : CDialog(CBriefinglocalizerDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CBriefinglocalizerDlg)
  m_Title = _T("");
  m_Text = _T("");
  //}}AFX_DATA_INIT
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_FileChanged = false;
  m_CurTextLeft = 0;
  m_CurTextRight = 0;
  m_BigStringTextLower.Empty();
  m_BigTextString.Empty();
}

void CBriefinglocalizerDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CBriefinglocalizerDlg)
  DDX_Control(pDX, IDC_TEXT, m_RichText);
  DDX_Text(pDX, IDC_TITLE, m_Title);
  DDX_Text(pDX, IDC_TEXT, m_Text);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBriefinglocalizerDlg, CDialog)
//{{AFX_MSG_MAP(CBriefinglocalizerDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_NEXT, OnNext)
ON_BN_CLICKED(IDC_PREV, OnPrev)
ON_BN_CLICKED(IDC_QUIT, OnQuit)
ON_BN_CLICKED(IDC_SAVE, OnSave)
ON_EN_KILLFOCUS(IDC_TITLE, OnKillfocusTitle)
ON_EN_CHANGE(IDC_TEXT, OnChangeText)
ON_EN_CHANGE(IDC_TITLE, OnChangeTitle)
ON_NOTIFY(NM_KILLFOCUS, IDC_TEXT, OnKillfocusText)
ON_NOTIFY(EN_KILLFOCUS, IDC_TEXT, OnKillfocusText)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBriefinglocalizerDlg message handlers

BOOL CBriefinglocalizerDlg::OnInitDialog() {
  static char sztemppath[_MAX_PATH * 2] = ".";
  static char sztempfile[_MAX_PATH * 2] = "tempfile.tmp";
  char path[_MAX_PATH * 2];
  char drive[10];
  CString savepath;
  CString DefaultPath;

  CDialog::OnInitDialog();

  m_RichText.SetEventMask(ENM_CHANGE);

  SetIcon(m_hIcon, TRUE);  // Set big icon
  SetIcon(m_hIcon, FALSE); // Set small icon

  CFileDialog *fd;

  DefaultPath = AfxGetApp()->GetProfileString("Defaults", "LastDir", "");

  static char szFilter[] = "Descent 3 Briefing (*.br?)|*.br?|All Files (*.*)|*.*||";

  _chdir(DefaultPath);
  fd = new CFileDialog(true, ".brf", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilter);
  if (fd->DoModal() == IDCANCEL) {
    delete fd;
    CDialog::OnCancel();
    return FALSE;
  }

  GetTempPath(_MAX_PATH * 2, sztemppath);

  m_RealFileName = fd->GetPathName();

  _splitpath(m_RealFileName, drive, path, NULL, NULL);

  savepath = drive;
  savepath += path;

  AfxGetApp()->WriteProfileString("Defaults", "LastDir", savepath);

  GetTempFileName(sztemppath, "d3brf", 0x42, sztempfile);

  m_TempFileName = sztempfile;

  delete fd;
  fd = NULL;
  FILE *infile;
  struct _stat buf;
  int result = _stat(m_RealFileName, &buf);
  if (result != 0) {
    AfxMessageBox("Error: Cannot determine file size!", MB_OK | MB_ICONSTOP);
    goto do_error;
  }
  infile = fopen(m_RealFileName, "rt");
  if (infile) {
    CString newtitle;

    newtitle.Format("Outrage Briefing file localizer -- %s", m_RealFileName);
    SetWindowText(newtitle);

    char *szbuf;
    szbuf = (char *)malloc(buf.st_size);
    fread(szbuf, buf.st_size, 1, infile);
    fclose(infile);
    m_BigTextString = szbuf;
    m_BigStringTextLower = m_BigTextString;

    m_BigStringTextLower.MakeLower();

    delete szbuf;

    m_TitleLeft = m_BigStringTextLower.Find(TITLE_TAG);
    if (m_TitleLeft != -1) {
      m_TitleRight = m_BigStringTextLower.Find("\"", m_TitleLeft + TITLE_TAG_LENGTH);
      m_Title = m_BigTextString.Mid(TITLE_TAG_LENGTH + m_TitleLeft, (m_TitleRight - (m_TitleLeft + TITLE_TAG_LENGTH)));
    } else {
      AfxMessageBox("Warning: There is no title in this briefing file!", MB_OK);
      GetDlgItem(IDC_TITLE)->EnableWindow(false);
    }

    // Now I need to find the first text item!
    m_CurTextLeft = m_BigStringTextLower.Find(TEXT_START_TAG);
    if (m_CurTextLeft != -1) {
      m_CurTextLeft = m_BigStringTextLower.Find(TEXT_SHOW_TAG, m_CurTextLeft);
      if (m_CurTextLeft != -1) {
        m_CurTextRight = m_BigStringTextLower.Find(TEXT_END_TAG, m_CurTextLeft + TEXT_SHOW_TAG_LEN);
        m_CurTextLeft += TEXT_SHOW_TAG_LEN;
        FIND_NEXT_LINE(m_CurTextLeft, m_BigTextString);
        m_Text = m_BigTextString.Mid(m_CurTextLeft, (m_CurTextRight - (m_CurTextLeft)-1));
      }
    } else {
      AfxMessageBox("Warning: There is no text in this briefing file!", MB_OK);
      GetDlgItem(IDC_NEXT)->EnableWindow(false);
      GetDlgItem(IDC_PREV)->EnableWindow(false);
      GetDlgItem(IDC_TEXT)->EnableWindow(false);
    }

    m_CurrentText = 1;

    // Disable the previous button
    GetDlgItem(IDC_PREV)->EnableWindow(false);

    UpdateData(false);

    return TRUE; // return TRUE  unless you set the focus to a control
  }
do_error:

  AfxMessageBox("Error: Cannot open specified file!", MB_OK | MB_ICONSTOP);
  CDialog::OnCancel();
  return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBriefinglocalizerDlg::OnPaint() {
  if (IsIconic()) {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  } else {
    CDialog::OnPaint();
  }
}

HCURSOR CBriefinglocalizerDlg::OnQueryDragIcon() { return (HCURSOR)m_hIcon; }

void CBriefinglocalizerDlg::OnNext() {
  // Get the text out of the dialog...
  UpdateData(true);

  CString left, right;

  left = m_BigTextString.Left(m_CurTextLeft);
  right = m_BigTextString.Right(m_BigTextString.GetLength() - m_CurTextRight);

  m_BigTextString = left + m_Text + "\n" + right;
  m_BigStringTextLower = m_BigTextString;
  m_BigStringTextLower.MakeLower();

  m_CurTextRight = m_CurTextLeft + m_Text.GetLength();

  int saveleft = m_CurTextLeft;
  // Now I need to find the next text item!
  m_CurTextLeft = m_BigStringTextLower.Find(TEXT_START_TAG, m_CurTextRight);
  if (m_CurTextLeft != -1) {
    m_CurTextLeft = m_BigStringTextLower.Find(TEXT_SHOW_TAG, m_CurTextLeft);
    if (m_CurTextLeft != -1) {
      m_CurTextRight = m_BigStringTextLower.Find(TEXT_END_TAG, m_CurTextLeft + TEXT_SHOW_TAG_LEN);
      m_CurTextLeft += TEXT_SHOW_TAG_LEN;
      FIND_NEXT_LINE(m_CurTextLeft, m_BigTextString);
      m_Text = m_BigTextString.Mid(m_CurTextLeft, (m_CurTextRight - (m_CurTextLeft)-1));
      GetDlgItem(IDC_PREV)->EnableWindow(true);
      m_CurrentText++;
    }
  } else {
    m_CurTextLeft = saveleft;
    GetDlgItem(IDC_NEXT)->EnableWindow(false);
  }
  UpdateData(false);
}

void CBriefinglocalizerDlg::OnPrev() {
  UpdateData(true);

  CString left, right;

  left = m_BigTextString.Left(m_CurTextLeft);
  right = m_BigTextString.Right(m_BigTextString.GetLength() - m_CurTextRight);

  m_BigTextString = left + m_Text + "\n" + right;
  m_BigStringTextLower = m_BigTextString;
  m_BigStringTextLower.MakeLower();

  m_CurTextRight = 0;
  m_CurTextLeft = 0;

  m_CurrentText--;

  int count = 0;
  // Rewind to the previous item
  while (count != m_CurrentText) {
    m_CurTextLeft = m_BigStringTextLower.Find(TEXT_START_TAG, m_CurTextRight);
    if (m_CurTextLeft != -1) {
      m_CurTextLeft = m_BigStringTextLower.Find(TEXT_SHOW_TAG, m_CurTextLeft);
      if (m_CurTextLeft != -1) {
        m_CurTextRight = m_BigStringTextLower.Find(TEXT_END_TAG, m_CurTextLeft + TEXT_SHOW_TAG_LEN);
        m_CurTextLeft += TEXT_SHOW_TAG_LEN;
        FIND_NEXT_LINE(m_CurTextLeft, m_BigTextString);
      }
    }
    count++;
  }

  m_Text = m_BigTextString.Mid(m_CurTextLeft, (m_CurTextRight - (m_CurTextLeft)));

  GetDlgItem(IDC_NEXT)->EnableWindow(true);
  if (m_CurrentText <= 1) {
    // Disable the previous button
    GetDlgItem(IDC_PREV)->EnableWindow(false);
  }
  UpdateData(false);
}

void CBriefinglocalizerDlg::OnQuit() {
  // See if the file has changed since it was last saved
  if (m_FileChanged) {
    int res = AfxMessageBox("Briefing has changed, would you like to save your changes?", MB_YESNOCANCEL);
    switch (res) {
    case IDYES:
      // Prompt to save if it has
      OnSave();
      break;
    case IDNO:
      break;
    case IDCANCEL:
      return;
    default:
      return;
    }
  }
  CDialog::OnCancel();
}

void CBriefinglocalizerDlg::OnSave() {
  // Update the big string
  CString testfile;
  FILE *outfile;
  testfile = m_RealFileName; // + ".test";
  outfile = fopen(testfile, "wt");
  if (outfile) {
    fwrite(LPCSTR(m_BigTextString), m_BigTextString.GetLength(), 1, outfile);
    m_FileChanged = false;
    fclose(outfile);
  } else {
    AfxMessageBox("Error: Unable to write to file!", MB_OK);
  }
}

void CBriefinglocalizerDlg::OnKillfocusTitle() {
  CString oldtitle = m_Title;
  UpdateData(true);

  int titlelendelta = m_Title.GetLength() - oldtitle.GetLength();
  int titleleft = 0;
  int titleright = 0;
  CString left, right;

  titleleft = m_BigStringTextLower.Find(TITLE_TAG);
  if (titleleft != -1) {
    titleright = m_BigStringTextLower.Find("\"", titleleft + TITLE_TAG_LENGTH);
    left = m_BigTextString.Left(titleleft + TITLE_TAG_LENGTH);
    right = m_BigTextString.Right(m_BigTextString.GetLength() - (titleright + 1));
    m_BigTextString = left + m_Title + "\"" + right;
    m_BigStringTextLower = m_BigTextString;
    m_BigStringTextLower.MakeLower();
    m_CurTextLeft += titlelendelta;
    m_CurTextRight += titlelendelta;
  }
}

void CBriefinglocalizerDlg::OnCancel() {
  // do nothing... we want to use OnQuit()
  // CDialog::OnCancel();
}

void CBriefinglocalizerDlg::OnChangeText() {
  m_FileChanged = true;
  UpdateData(true);

  CString left, right;

  left = m_BigTextString.Left(m_CurTextLeft);
  right = m_BigTextString.Right(m_BigTextString.GetLength() - m_CurTextRight);

  m_BigTextString = left + m_Text + "\n" + right;
  m_BigStringTextLower = m_BigTextString;
  m_BigStringTextLower.MakeLower();
  m_CurTextRight = m_CurTextLeft + m_Text.GetLength();
}

void CBriefinglocalizerDlg::OnChangeTitle() { m_FileChanged = true; }

void CBriefinglocalizerDlg::OnKillfocusText(NMHDR *pNMHDR, LRESULT *pResult) {
  UpdateData(true);

  CString left, right;

  left = m_BigTextString.Left(m_CurTextLeft);
  right = m_BigTextString.Right(m_BigTextString.GetLength() - m_CurTextRight);

  m_BigTextString = left + m_Text + "\n" + right;
  m_BigStringTextLower = m_BigTextString;
  m_BigStringTextLower.MakeLower();
  m_CurTextRight = m_CurTextLeft + m_Text.GetLength();

  *pResult = 0;
}
