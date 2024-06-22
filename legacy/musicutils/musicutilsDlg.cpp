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

// musicutilsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "musicutils.h"
#include "musicutilsDlg.h"
#include "RawCvtDlg.h"
#include "PlaySongDlg.h"
#include "InsSongDlg.h"
#include "RoomLinkDlg.h"
#include "TrueFalseDlg.h"

#include "musicplay.h"

#include "pserror.h"
#include "application.h"
#include "streamaudio.h"
#include "ddio.h"
#include "macros.h"
#include "inffile.h"
#include "mem.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool Dedicated_server = false;

//	OMF INF FILE READ

#define OMFCMD_NUM 12
#define OMFCMD_INTRO 0
#define OMFCMD_BKG 1
#define OMFCMD_COMBAT 2
#define OMFCMD_ENDCOMBAT 5
#define OMFCMD_LOOPING 10
#define OMFCMD_ATTACHROOM 11

const char *OMFCommands[OMFCMD_NUM] = {"intro", "scene", "combat", "danger", "death",   "endcombat",
                                       "q2",    "q2",    "q2",     "q2",     "looping", "attachroom"};

int OMFLex(const char *command) {
  for (int i = 0; i < OMFCMD_NUM; i++)
    if (strcmp(OMFCommands[i], command) == 0)
      return i;

  return INFFILE_ERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {
public:
  CAboutDlg();

  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicutilsDlg dialog

CMusicutilsDlg::CMusicutilsDlg(CWnd *pParent /*=NULL*/) : CDialog(CMusicutilsDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CMusicutilsDlg)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicutilsDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CMusicutilsDlg)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

// returns if save modified was canceled
bool CMusicutilsDlg::SaveModified() {
  if (m_modified) {
    int res = AfxMessageBox("Do you wish to save the current theme?", MB_YESNOCANCEL);

    if (res == IDYES) {
      OnFileSave();
    } else if (res == IDCANCEL)
      return false;
  }

  return true;
}

BEGIN_MESSAGE_MAP(CMusicutilsDlg, CDialog)
//{{AFX_MSG_MAP(CMusicutilsDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_COMMAND(IDC_TOOLS_MAKESTREAM, OnToolsMakeStream)
ON_WM_DESTROY()
ON_COMMAND(IDC_FILE_QUIT, OnFileQuit)
ON_COMMAND(IDC_TOOLS_PLAYSONG, OnToolsPlaySong)
ON_COMMAND(IDC_FILE_NEW, OnFileNew)
ON_NOTIFY(TVN_KEYDOWN, IDC_THEME_TREE, OnKeydownThemeTree)
ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
ON_COMMAND(ID_FILE_SAVE, OnFileSave)
ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
ON_NOTIFY(NM_RETURN, IDC_THEME_TREE, OnReturnThemeTree)
ON_NOTIFY(NM_DBLCLK, IDC_THEME_TREE, OnDblclkThemeTree)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicutilsDlg message handlers

BOOL CMusicutilsDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu *pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL) {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty()) {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);  // Set big icon
  SetIcon(m_hIcon, FALSE); // Set small icon

  hBkgLeaf = NULL;
  hCombatLeaf = NULL;
  hDangerLeaf = NULL;
  hIntroLeaf = NULL;
  hEndCombatLeaf = NULL;

  // TODO: Add extra initialization here
  tWin32AppInfo appinfo;
  appinfo.hwnd = m_hWnd;
  appinfo.hinst = Editor()->m_hInstance;
  appinfo.flags = OEAPP_WINDOWED;

  MusicUtils = (oeApplication *)new oeWin32Application(&appinfo);

#ifdef _DEBUG
  error_Init(true, false, "MusicUtils");
#else
  error_Init(false, false);
#endif

  //	initialize sound systems
  MusicPlayInit(MusicUtils);

  //	initialize tree control based off on new tree.
  m_modified = false;
  NewTheme();

  //	set focus to tree control
  GetDlgItem(IDC_THEME_TREE)->SetFocus();

  mem_Init();

  return FALSE; // return TRUE  unless you set the focus to a control
}

void CMusicutilsDlg::OnDestroy() {
  FreeTree();

  MusicPlayClose();
  delete MusicUtils;
  MusicUtils = NULL;

  CDialog::OnDestroy();
}

void CMusicutilsDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  } else {
    CDialog::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMusicutilsDlg::OnPaint() {
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMusicutilsDlg::OnQueryDragIcon() { return (HCURSOR)m_hIcon; }

void CMusicutilsDlg::OnOK() {
  //	do nothing! (prevents pressing enter causing app to quit!)
}

void CMusicutilsDlg::OnCancel() {
  if (SaveModified()) {
    CDialog::OnCancel();
  }
}

BOOL CMusicutilsDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  // MASSIVE HACK TO PREVENT IDOK FROM BEING PASSED TO DIALOG (BY ENTER KEY)
  //	SEND ENTER KEY TO TREE CONTROL.
  //	There must be a better way to do this!.

  if (wParam != IDOK)
    return CDialog::OnCommand(wParam, lParam);
  else {
    GetDlgItem(IDC_THEME_TREE)->SendMessage(WM_KEYDOWN, VK_RETURN, 0);
    GetDlgItem(IDC_THEME_TREE)->SendMessage(WM_KEYUP, VK_RETURN, 0);
    return FALSE;
  }
}

///////////////////////////////////////////////////////////////////////////////
//	Menu Command handlers

void CMusicutilsDlg::OnFileNew() {
  if (SaveModified())
    NewTheme();
}

void CMusicutilsDlg::OnFileQuit() { OnCancel(); }

void CMusicutilsDlg::OnFileOpen() {
  CFileDialog opendlg(TRUE, "omf", NULL, OFN_PATHMUSTEXIST, "Outrage Music Files(*.omf)|*.omf||", this);

  if (!SaveModified())
    return;

  if (opendlg.DoModal() == IDOK) {
    OpenThemeFile(opendlg.GetPathName());
  }
}

void CMusicutilsDlg::OnFileSave() {
  if (m_themefilename.IsEmpty())
    OnFileSaveas();
  else
    SaveThemeFile();
}

void CMusicutilsDlg::OnFileSaveas() {
  CFileDialog savedlg(FALSE, "omf", (LPCTSTR)m_themefilename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                      "Outrage Music Files(*.omf)|*.omf||", this);

  if (savedlg.DoModal() == IDOK) {
    m_themefilename = savedlg.GetPathName();
    SaveThemeFile();
  }
}

void CMusicutilsDlg::OpenThemeFile(const CString &filename) {
#define CLEAR_PATHLIST                                                                                                 \
  for (iter = 0; iter < 16; curpath[iter++][0] = 0)                                                                    \
    ;                                                                                                                  \
  iter = 0

  mprintf(0, "Opening music theme file...\n");

  InfFile inf;
  char operand[INFFILE_LINELEN];     // operand
  char curpath[16][INFFILE_LINELEN]; // stores complete path of song.
  int iter;
  tSongItem *cursong = NULL;
  int curcmdtype;

  //	open file
  if (!inf.Open((LPCTSTR)filename, "[theme file]", OMFLex)) {
    AfxMessageBox("Unable to open theme file.");
    return;
  }

  //	create new theme.
  NewTheme();
  m_themefilename = filename;
  CLEAR_PATHLIST;
  iter = 0;
  curcmdtype = -1;

  //	check if valid cockpit file
  while (inf.ReadLine()) {
    int cmd;

    while ((cmd = inf.ParseLine(operand, INFFILE_LINELEN)) > INFFILE_ERROR) {
      tSongItem song;

      // reset all song properties (song) used just in InsertSong
      song.repeat = false;
      song.roomlink = -1;

      switch (cmd) {
      case OMFCMD_INTRO:
        song.strSongPath = curpath[0];
        cursong = InsertSong(hIntroLeaf, &song);
        curcmdtype = cmd;
        CLEAR_PATHLIST;
        break;

      case OMFCMD_BKG:
        song.strSongPath = curpath[0];
        cursong = InsertSong(hBkgLeaf, &song);
        curcmdtype = cmd;
        CLEAR_PATHLIST;
        break;

      case OMFCMD_COMBAT:
        song.strSongPath = curpath[0];
        cursong = InsertSong(hCombatLeaf, &song);
        curcmdtype = cmd;
        CLEAR_PATHLIST;
        break;

      case OMFCMD_ENDCOMBAT:
        song.strSongPath = curpath[0];
        cursong = InsertSong(hEndCombatLeaf, &song);
        curcmdtype = cmd;
        CLEAR_PATHLIST;
        break;

      case OMFCMD_LOOPING:
        if (strcmp(operand, "true") == 0)
          cursong->repeat = true;
        else if (strcmp(operand, "false") == 0)
          cursong->repeat = false;
        else {
          cmd = INFFILE_ERROR;
          goto force_error;
        }
        SetSongProperty(SONGPROP_REPEAT, cursong);
        break;

      case OMFCMD_ATTACHROOM:
        if (curcmdtype == OMFCMD_BKG) {
          cursong->roomlink = atoi(operand);
          SetSongProperty(SONGPROP_ROOMLINK, cursong);
        }
        break;

      case INFFILE_SYMBOL:
        if (iter == 16)
          Int3();
        strcpy(curpath[iter++], operand);
        break;
      }
    }

  force_error:
    if (cmd == INFFILE_ERROR)
      mprintf(0, "Error in music file %s line %d.\n", filename, inf.line());
  }

  inf.Close();

  m_modified = false;
}

void CMusicutilsDlg::SaveThemeFile() {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);
  tSongItem *song;
  HTREEITEM hTreeItem;
  char filename[PSFILENAME_LEN], ext[PSFILENAME_LEN];
  int iter;

  mprintf(0, "Saving music theme file...\n");

  //	okay, we need to extract each tree item and create the necessary 'code' for
  //	musical theme file.
  //	create header
  CString codestr;
  CString tempstr;

  codestr = "[theme file]\n\n@ Outrage Music File Theme\n@ " + m_themename + "\n@\n";
  codestr += "@ All #zz??????? symbols are generated by Outrage Music Utilities\n@ they should not be modified.\n\n";

  //	do intro music.
  codestr += "@ intro music\n";
  iter = 0;
  hTreeItem = tree->GetChildItem(hIntroLeaf);

  while (hTreeItem) {
    song = GetSongFromTreeItem(hTreeItem);
    if (song) {
      ddio_SplitPath((LPCTSTR)song->strSongPath, NULL, filename, ext);
      tempstr.Format("#zzint%d=%s\n", iter, (LPCTSTR)song->strSongPath);
      codestr += (tempstr + "intro=") + filename;
      codestr += ext;
    }
    hTreeItem = tree->GetNextItem(hTreeItem, TVGN_NEXT);
    codestr += "\n";
  }

  //	do background
  codestr += "\n@ background music\n";
  iter = 0;
  hTreeItem = tree->GetChildItem(hBkgLeaf);

  while (hTreeItem) {
    song = GetSongFromTreeItem(hTreeItem);
    if (song) {
      ddio_SplitPath((LPCTSTR)song->strSongPath, NULL, filename, ext);
      tempstr.Format("#zzbkg%d=%s\n", iter, (LPCTSTR)song->strSongPath);
      codestr += (tempstr + "scene=") + filename;
      codestr += ext;
      if (song->repeat)
        codestr += ", looping=true";
      if (song->roomlink > -1) {
        tempstr.Format(", attachroom=%d", song->roomlink);
        codestr += tempstr;
      }
    }
    hTreeItem = tree->GetNextItem(hTreeItem, TVGN_NEXT);
    codestr += "\n";
  }

  //	do combat
  codestr += "\n@ combat music\n";
  iter = 0;
  hTreeItem = tree->GetChildItem(hCombatLeaf);

  while (hTreeItem) {
    song = GetSongFromTreeItem(hTreeItem);
    if (song) {
      ddio_SplitPath((LPCTSTR)song->strSongPath, NULL, filename, ext);
      tempstr.Format("#zzcmb%d=%s\n", iter, (LPCTSTR)song->strSongPath);
      codestr += (tempstr + "combat=") + filename;
      codestr += ext;
      if (song->repeat)
        codestr += ", looping=true";
    }
    hTreeItem = tree->GetNextItem(hTreeItem, TVGN_NEXT);
    codestr += "\n";
  }

  //	do danger
  codestr += "\n@ danger music\n";
  iter = 0;
  hTreeItem = tree->GetChildItem(hDangerLeaf);

  while (hTreeItem) {
    song = GetSongFromTreeItem(hTreeItem);
    if (song) {
      ddio_SplitPath((LPCTSTR)song->strSongPath, NULL, filename, ext);
      tempstr.Format("#zzdgr%d=%s\n", iter, (LPCTSTR)song->strSongPath);
      codestr += (tempstr + "danger=") + filename;
      codestr += ext;
      if (song->repeat)
        codestr += ", looping=true";
    }
    hTreeItem = tree->GetNextItem(hTreeItem, TVGN_NEXT);
    codestr += "\n";
  }

  //	do end combat
  codestr += "\n@ end combat music\n";
  iter = 0;
  hTreeItem = tree->GetChildItem(hEndCombatLeaf);

  while (hTreeItem) {
    song = GetSongFromTreeItem(hTreeItem);
    if (song) {
      ddio_SplitPath((LPCTSTR)song->strSongPath, NULL, filename, ext);
      tempstr.Format("#zzecm%d=%s\n", iter, (LPCTSTR)song->strSongPath);
      codestr += (tempstr + "endcombat=") + filename;
      codestr += ext;
    }
    hTreeItem = tree->GetNextItem(hTreeItem, TVGN_NEXT);
    codestr += "\n";
  }

  //	save out file
  FILE *fp = fopen((LPCTSTR)m_themefilename, "wt");
  if (fp) {
    if (fputs((LPCSTR)codestr, fp) == EOF) {
      fclose(fp);
      AfxMessageBox("Unable to save theme file. Check disk space.");
      return;
    }

    fclose(fp);
    m_modified = false;
  } else {
    AfxMessageBox("Unable to save theme file. Check disk space.");
  }
}

//////////////////////////////////////////////////////////////////////////////
//	These are Music tools

//	Stream converter.   Esentially choose a 'raw' file to convert to an
//	outrage stream format (osf)

void CMusicutilsDlg::OnToolsMakeStream() {
  CFileDialog opendlg(TRUE, "raw", NULL, OFN_PATHMUSTEXIST, "Raw files(*.raw)|*.raw||", this);
  CString srcfilestr;
  CString destfilestr;

  //	get filename to convert (RAW file)
  if (opendlg.DoModal() != IDOK) {
    AfxMessageBox("Stream conversion action canceled.");
    return;
  }

  srcfilestr = opendlg.GetPathName();
  destfilestr = srcfilestr.Left(srcfilestr.Find('.'));

  //	do conversion dialog.
  CRawCvtDlg compdlg;
  CFileDialog savedlg(FALSE, "osf", (LPCTSTR)destfilestr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                      "Outrage Stream Files(*.osf)|*.osf||", this);

  compdlg.m_Resolution = 1;
  compdlg.m_Frequency = 1;
  compdlg.m_Channels = 0;
  compdlg.m_VolScale = "0.97";
  compdlg.m_Xforms = 7;

  if (compdlg.DoModal() != IDOK)
    goto strconv_err;

  //	okay prompt for save location
  if (savedlg.DoModal() == IDOK) {
    OSFArchive osf;
    uint8_t strmtype = 0, strmcomp = 0, strmfmt = 0, xforms;
    uint32_t rate;

    // determine stream type.
    strmtype = OSF_DIGITAL_STRM;
    strmcomp = (compdlg.m_Resolution == 1) ? OSF_DIGIACM_STRM : OSF_DIGIRAW_STRM;
    strmfmt |= ((compdlg.m_Channels == 1) ? SAF_STEREO_MASK : SAF_MONO_MASK);
    strmfmt |= ((compdlg.m_Resolution == 1) ? SAF_16BIT_MASK : SAF_8BIT_MASK);
    rate = (compdlg.m_Frequency == 2) ? 44100 : (compdlg.m_Frequency == 1) ? 22050 : 11025;
    xforms = (uint8_t)compdlg.m_Xforms;

    //	start file write.
    destfilestr = savedlg.GetPathName();
    if (!osf.Open((LPCTSTR)destfilestr, true)) {
      AfxMessageBox("Unable to open file to write out stream.");
      goto strconv_err;
    }

    // first compress audio file if it's the proper format, otherwise just copy into larger file.
    //		note that 16-bit is the only supported format, damn interplay.
    if (strmtype == OSF_DIGITAL_STRM) {
      if (!SaveDigitalStream(&osf, srcfilestr, strmcomp, strmfmt, rate, (LPCTSTR)compdlg.m_StreamName, xforms,
                             compdlg.m_MeasureSize)) {
        osf.Close();
        AfxMessageBox("Unable to open or save stream data.");
        goto strconv_err;
      }
    } else {
      Int3();
    }

    osf.Close();
  }

  return;

strconv_err:
  AfxMessageBox("Stream conversion action canceled.");
}

//	Plays a song
void CMusicutilsDlg::OnToolsPlaySong() {
  CFileDialog opendlg(TRUE, "osf", NULL, OFN_PATHMUSTEXIST, "Outrage Stream Files(*.osf)|*.osf||", this);

  //	get filename to play
  if (opendlg.DoModal() != IDOK) {
    return;
  }

  CPlaySongDlg playdlg;

  playdlg.m_StreamName = opendlg.GetPathName();
  playdlg.DoModal();
}

#define FILEBUFFER_LENGTH (64 * 1024)
static uint8_t StaticFileBuffer[FILEBUFFER_LENGTH];

bool CMusicutilsDlg::SaveDigitalStream(OSFArchive *osf, const CString &rawfilename, uint8_t compression, uint8_t format,
                                       uint32_t samples, const CString &realname, uint8_t xforms, int measure) {
  FILE *fpin = NULL;
  int i;
  uint32_t filelen;
  int nblocks;

  if (compression == OSF_DIGIACM_STRM) {
    //	prepare to execute audcomp process.
    PROCESS_INFORMATION proc_info;
    STARTUPINFO si;
    CString cmdline;
    LPTSTR cmdbuffer;

    int chan = (format & SAF_STEREO_MASK) ? 2 : 1;
    int rate = (int)samples;
    int cmpfmt = (rate == 22050) ? 4 : (rate == 44100) ? 8 : 1;

    cmdline.Format("f:\\tools\\audcomp.exe %s _zztemp.acm /l:%d /c:%d /f:%d /r:%d", (LPCTSTR)rawfilename, xforms, chan,
                   cmpfmt, rate);
    cmdbuffer = cmdline.GetBuffer(256);

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;

    if (!CreateProcess(NULL, cmdbuffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &proc_info)) {
      AfxMessageBox("Failed to start audio compression tool f:\tools\audcomp.exe");
      return false;
    }

    WaitForInputIdle(proc_info.hProcess, INFINITE);

    while (WaitForSingleObject(proc_info.hProcess, 0) != WAIT_OBJECT_0) {
    }

    CloseHandle(proc_info.hThread);
    CloseHandle(proc_info.hProcess);

    //	okay, we should have a file called _zztemp.acm.  lets copy this directly to our output file.

    fpin = fopen("_zztemp.acm", "rb");
    if (!fpin) {
      AfxMessageBox("Compression failed due to error in the compress utility.");
      return false;
    }
  } else {
    //	raw (uncompressed) data.
    fpin = fopen((LPCTSTR)rawfilename, "rb");
    if (!fpin)
      return false;
  }

  //	start writing out data.
  tOSFDigiHdr digihdr;

  ASSERT(fpin);

  filelen = (uint32_t)_filelength(fileno(fpin));
  nblocks = filelen / FILEBUFFER_LENGTH;

  //	write out data.
  for (i = 0; i < nblocks; i++) {
    if (!fread(StaticFileBuffer, FILEBUFFER_LENGTH, 1, fpin)) {
      fclose(fpin);
      return false;
    }
    if (!osf->WriteBlock(StaticFileBuffer, FILEBUFFER_LENGTH)) {
      fclose(fpin);
      return false;
    }
  }

  if (filelen % FILEBUFFER_LENGTH) {
    if (!fread(StaticFileBuffer, filelen % FILEBUFFER_LENGTH, 1, fpin)) {
      fclose(fpin);
      return false;
    }
    if (!osf->WriteBlock(StaticFileBuffer, filelen % FILEBUFFER_LENGTH)) {
      fclose(fpin);
      return false;
    }
  }

  digihdr.measure = measure;

  //	save header info
  if (!osf->SaveHeader(OSF_DIGITAL_STRM, compression, format, samples, filelen, &digihdr, (LPCTSTR)realname)) {
    AfxMessageBox("Failed to write out OSF header info.");
    fclose(fpin);
    return false;
  }

  //	close
  fclose(fpin);

  if (compression == OSF_DIGIACM_STRM) {
    remove("_zztemp.acm");
  }
  return true;
}

void CMusicutilsDlg::GetStreamInfo(const CString &filename, CString &realname) {
  OSFArchive archive;

  if (archive.Open((LPCTSTR)filename)) {
    realname = archive.StreamName();
    archive.Close();
  } else {
    realname = "Error reading stream.";
  }
}

//////////////////////////////////////////////////////////////////////////////
//	TREE CONTROL

void CMusicutilsDlg::OnReturnThemeTree(NMHDR *pNMHDR, LRESULT *pResult) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(pNMHDR->idFrom);
  HTREEITEM hSelectedItem = tree->GetSelectedItem();

  DoTreeItem(hSelectedItem);

  *pResult = 0;
}

void CMusicutilsDlg::OnDblclkThemeTree(NMHDR *pNMHDR, LRESULT *pResult) {
  // TODO: Add your control notification handler code here
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(pNMHDR->idFrom);
  HTREEITEM hSelectedItem = tree->GetSelectedItem();

  DoTreeItem(hSelectedItem);

  *pResult = 0;
}

//	Tree control key handler
void CMusicutilsDlg::OnKeydownThemeTree(NMHDR *pNMHDR, LRESULT *pResult) {
  TV_KEYDOWN *pTVKeyDown = (TV_KEYDOWN *)pNMHDR;
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(pTVKeyDown->hdr.idFrom);
  HTREEITEM hSelectedItem = tree->GetSelectedItem();

  switch (pTVKeyDown->wVKey) {
  case VK_INSERT:
    if (hSelectedItem == hBkgLeaf || hSelectedItem == hCombatLeaf || hSelectedItem == hDangerLeaf ||
        hSelectedItem == hIntroLeaf || hSelectedItem == hEndCombatLeaf)
      InsertTreeItem(hSelectedItem);
    break;

  case VK_DELETE:
    FreeTreeItem(hSelectedItem);
    break;

  case VK_SPACE:
    tree->Expand(hSelectedItem, TVE_TOGGLE);
    break;
  }

  *pResult = 0;
}

//	creates a new theme, resetting the tree control, etc.
void CMusicutilsDlg::NewTheme() {
  //	do tree control stuff
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);

  FreeTree();
  hIntroLeaf = InsertLeaf(TVI_ROOT, "Intro", LEAFTYPE_CATEGORY);
  hBkgLeaf = InsertLeaf(TVI_ROOT, "Background", LEAFTYPE_CATEGORY);
  hCombatLeaf = InsertLeaf(TVI_ROOT, "Combat", LEAFTYPE_CATEGORY);
  hDangerLeaf = InsertLeaf(TVI_ROOT, "Danger", LEAFTYPE_CATEGORY);
  hEndCombatLeaf = InsertLeaf(TVI_ROOT, "End Combat", LEAFTYPE_CATEGORY);

  m_themefilename.Empty();
  m_modified = false;
}

void CMusicutilsDlg::FreeTree() {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);

  //	delete all items
  FreeTreeItems(hEndCombatLeaf);
  FreeTreeItems(hIntroLeaf);
  FreeTreeItems(hBkgLeaf);
  FreeTreeItems(hCombatLeaf);
  FreeTreeItems(hDangerLeaf);
  hBkgLeaf = NULL;
  hCombatLeaf = NULL;
  hDangerLeaf = NULL;
  hIntroLeaf = NULL;
  hEndCombatLeaf = NULL;
}

//	frees all daya for a tree leaf (and all children.)
void CMusicutilsDlg::FreeTreeItems(HTREEITEM hLeaf) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);

  if (hLeaf) {
    HTREEITEM hItem = tree->GetChildItem(hLeaf);
    HTREEITEM hOldItem;
    while (hItem) {
      hOldItem = hItem;
      hItem = FreeTreeItem(hOldItem);
    }

    tree->DeleteItem(hLeaf);
  }
}

#define TXT_LINKLEVEL "Attach to level room = "
#define TXT_REPEAT "Looping = "

//	inserts an item into the tree.
void CMusicutilsDlg::InsertTreeItem(HTREEITEM hParentItem) {
  CInsSongDlg insdlg;

  // only allow insertions at root leafs.
  if (insdlg.DoModal() != IDOK)
    return;

  tSongItem song;
  song.strSongPath = insdlg.m_SongPath;
  song.repeat = false;
  song.roomlink = -1;
  InsertSong(hParentItem, &song);

  m_modified = true;
}

HTREEITEM CMusicutilsDlg::FreeTreeItem(HTREEITEM hItem) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);
  LPARAM param;
  HTREEITEM hNextItem = NULL;

  // only allow us to delete a song (not a property)
  param = GetLeafParam(hItem);
  if (param > 0) {
    // delete all children too.
    tSongItem *song = (tSongItem *)param;
    if (song->hTI_repeat)
      tree->DeleteItem(song->hTI_repeat);
    if (song->hTI_lvllink)
      tree->DeleteItem(song->hTI_lvllink);
    delete song;

    hNextItem = tree->GetNextItem(hItem, TVGN_NEXT);
    tree->DeleteItem(hItem);
  }

  m_modified = true;

  return hNextItem;
}

//	does editing function on tree item.
void CMusicutilsDlg::DoTreeItem(HTREEITEM hItem) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);
  tSongItem *song;
  LPARAM param;

  //	get tree item info.  if a song, then expand, if a property, do property.
  param = GetLeafParam(hItem);
  song = GetSongFromTreeItem(hItem);

  switch (param) {
  case LEAFTYPE_PROPERTY:
    //	check if item matches any item inside the song structure (except for hTreeItem)
    if (hItem == song->hTI_lvllink) {
      CRoomLinkDlg dlg;
      dlg.m_Room = song->roomlink;
      if (dlg.DoModal() == IDOK) {
        if (dlg.m_RoomCheck)
          song->roomlink = dlg.m_Room;
        else
          song->roomlink = -1;
        SetSongProperty(SONGPROP_ROOMLINK, song);
      }
    } else if (hItem == song->hTI_repeat) {
      TrueFalseDlg dlg;
      dlg.m_IsFalse = song->repeat ? 0 : 1;
      if (dlg.DoModal() == IDOK) {
        if (dlg.m_IsFalse)
          song->repeat = false;
        else
          song->repeat = true;
        SetSongProperty(SONGPROP_REPEAT, song);
      }
    }
    break;

  case LEAFTYPE_CATEGORY:
    tree->Expand(hItem, TVE_TOGGLE);
    break;

  case LEAFTYPE_INVALID:
    Int3();
    break;

  default:
    //	this MUST be a song name
    {
      CInsSongDlg insdlg;

      insdlg.m_SongPath = song->strSongPath;
      if (insdlg.DoModal() == IDOK) {
        song->strSongPath = insdlg.m_SongPath;
        SetSongProperty(SONGPROP_FILE, song);
      }
    }
  }
}

// inserts a song into the designated tree.
CMusicutilsDlg::tSongItem *CMusicutilsDlg::InsertSong(HTREEITEM hTree, const tSongItem *songitm) {
  tSongItem *song = new tSongItem;
  CString tempstr;
  CString strSong;

  ASSERT(hTree == hIntroLeaf || hTree == hBkgLeaf || hTree == hCombatLeaf || hTree == hDangerLeaf ||
         hTree == hEndCombatLeaf);

  song->strSongPath = songitm->strSongPath;

  //	grab information from stream file
  GetStreamInfo(song->strSongPath, strSong);

  strSong += "  (";
  strSong += (song->strSongPath + ")");

  song->hTreeItem = InsertLeaf(hTree, strSong.GetBuffer(_MAX_PATH + 64), (LPARAM)song);

  song->hTI_repeat = NULL;
  if (hTree != hIntroLeaf && hTree != hEndCombatLeaf) {
    tempstr.Format("%s%s", TXT_REPEAT, songitm->repeat ? "true" : "false");
    song->hTI_repeat = InsertLeaf(song->hTreeItem, (LPCTSTR)tempstr, LEAFTYPE_PROPERTY);
    song->repeat = songitm->repeat;
  }

  song->hTI_lvllink = NULL;
  song->roomlink = songitm->roomlink;
  if (hTree == hBkgLeaf) {
    // add sub items to background song leaf
    tempstr.Format("%s%d", TXT_LINKLEVEL, song->roomlink);
    song->hTI_lvllink = InsertLeaf(song->hTreeItem, (LPCTSTR)tempstr, LEAFTYPE_PROPERTY);
  } else if (hTree == hCombatLeaf) {

  } else if (hTree == hDangerLeaf) {
  }

  return song;
}

//	Handy utilities to insert, retreive information from a leaf on the tree control.
HTREEITEM CMusicutilsDlg::InsertLeaf(HTREEITEM hParent, const char *text, LPARAM param) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);

  return tree->InsertItem(TVIF_TEXT | TVIF_PARAM, text, 0, 0, 0, 0, param, hParent, TVI_LAST);
}

LPARAM CMusicutilsDlg::GetLeafParam(HTREEITEM hItem) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);
  TV_ITEM tv_item;

  tv_item.hItem = hItem;
  tv_item.mask = TVIF_PARAM;

  return tree->GetItem(&tv_item) ? tv_item.lParam : LEAFTYPE_INVALID;
}

CMusicutilsDlg::tSongItem *CMusicutilsDlg::GetSongFromTreeItem(HTREEITEM hLeaf) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);
  LPARAM param;

  //	get song object.  if a property, the song object exists above this leaf.
  param = GetLeafParam(hLeaf);
  if (param == LEAFTYPE_PROPERTY) {
    param = GetLeafParam(tree->GetParentItem(hLeaf));
    ASSERT(param > 0);
  } else if (param == LEAFTYPE_CATEGORY) {
    param = 0;
  }
  return (tSongItem *)param;
}

void CMusicutilsDlg::SetSongProperty(tSongProp property, tSongItem *song) {
  CTreeCtrl *tree = (CTreeCtrl *)GetDlgItem(IDC_THEME_TREE);
  tSongItem *real_song;
  CString tempstr;
  HTREEITEM hItem = NULL;

  switch (property) {
  case SONGPROP_REPEAT:
    real_song = GetSongFromTreeItem(song->hTI_repeat);
    hItem = song->hTI_repeat;
    real_song->repeat = song->repeat;
    tempstr.Format("%s%s", TXT_REPEAT, real_song->repeat ? "true" : "false");
    break;
  case SONGPROP_ROOMLINK:
    real_song = GetSongFromTreeItem(song->hTI_lvllink);
    hItem = song->hTI_lvllink;
    real_song->roomlink = song->roomlink;
    tempstr.Format("%s%d", TXT_LINKLEVEL, real_song->roomlink);
    break;
  case SONGPROP_FILE:
    real_song = GetSongFromTreeItem(song->hTreeItem);
    hItem = song->hTreeItem;
    real_song->strSongPath = song->strSongPath;
    GetStreamInfo(real_song->strSongPath, tempstr); //	grab information from stream file
    tempstr += ("  (" + real_song->strSongPath + ")");
    break;
  default:
    Int3();
  }

  if (!hItem)
    return;

  tree->SetItemText(hItem, (LPCTSTR)tempstr);
  m_modified = true;
}
