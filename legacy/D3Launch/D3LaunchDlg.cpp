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

 * $Logfile: /DescentIII/Main/D3Launch/D3LaunchDlg.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:56:51 $
 * $Author: kevinb $
 *
 *
 *
 * $Log: not supported by cvs2svn $
 *
 * 78    10/18/99 5:40p Jeff
 * passthru any command line arguments into Descent 3
 *
 * 77    8/20/99 9:55a Nate
 * D3 OEM General now starts Ereg
 *
 * 76    6/10/99 6:28p Nate
 * Added files for Setup button fix
 *
 * 75    6/09/99 2:46p Nate
 * Minor changes for different builds
 *
 * 74    5/23/99 11:44a Nate
 * Added change to make sure the DDraw dll gets freed when launcher exits.
 *
 * 73    5/23/99 1:21a Nate
 * Made FindFast Disabling default to "always"
 *
 * 72    5/22/99 12:28a Samir
 * findfast user interface and detection code added to launcher.
 *
 * 71    5/20/99 2:28p Nate
 * Changed GLSetup CD path
 *
 * 70    5/20/99 12:53p Nate
 * Added GLSetup window, EAX mixer support, and CHFlight+Mouseman Mode
 * options
 *
 * 69    5/07/99 11:23a Nate
 * Added support for a launcher config file
 *
 * 68    4/27/99 10:41p Nate
 * Added profanity filter prompt
 *
 * 67    4/25/99 1:55p Nate
 * Removed Auto-Update prompt for D3 release
 *
 * 66    4/21/99 7:17p Nate
 * Added "-nolightmaps" switch for LOW_DETAIL setting
 *
 * 65    4/19/99 11:26p Nate
 * Added OpenGL warning message
 *
 * 64    4/15/99 12:03p Nate
 * Added "Descent 3 Demo 2" build type
 *
 * 63    4/08/99 1:13p Nate
 * Added Pentium III detection
 *
 * 62    4/07/99 3:27p Nate
 * Added reselection of old palette when done drawing launcher background
 *
 * 61    3/29/99 3:14p Nate
 * Added OEM_GENERIC
 *
 * 60    3/19/99 10:18a Nate
 * Added OEM_GENERIC compile type
 *
 * 59    3/12/99 3:29p Nate
 * Added more multi-language support
 *
 * 58    3/02/99 5:45p Nate
 * Lots of little changes/fixes
 *
 * 57    2/28/99 5:29p Nate
 * Added Auto-Update prompt
 *
 * 56    2/26/99 12:50p Nate
 * Changed OEM_Voodoo3 names
 *
 * 55    2/24/99 8:37p Nate
 * Various little dialog changes, added "Install Drivers" dialog
 *
 * 54    2/24/99 1:46p Nate
 * Added multi-language support
 *
 * 53    2/22/99 4:11p Nate
 * Added NO_MESSAGE checking to button strings
 *
 * 52    2/17/99 2:23p Nate
 * Added some OEM changes
 *
 * 51    2/15/99 1:41p Nate
 * Added DirectX installation through DirectSetup
 *
 * 50    2/10/99 1:56p Nate
 * Added code for DirectX 6.1 Installation
 *
 * 49    2/05/99 3:51p Nate
 * Added conditional compilation directives for OEM support
 *
 * 48    1/15/99 2:11p Nate
 * Updated the tournament info prompt.
 *
 * 47    1/14/99 11:06a Nate
 * Added tournament prompt dialog.
 *
 * 46    12/14/98 10:11a Nate
 * Added the whacking of gamma related environment variables (for Kevin)
 *
 * 45    11/30/98 3:01p Nate
 * The dedicated server can now be run without a video card selected.
 *
 * 44    11/09/98 1:35p Nate
 * Made the error message for launching the main executable more helpful.
 *
 * 43    11/06/98 4:56p Nate
 * User can now select highlighted button by pressing Enter.
 *
 * 42    11/05/98 2:16p Nate
 * Added keyboard support
 *
 * 41    10/30/98 12:09p Nate
 * Fixed clicking on light problem.
 *
 * 40    10/18/98 6:09p Nate
 *
 * 39    10/18/98 5:53p Nate
 *
 * 38    10/15/98 7:30p Nate
 *
 * 37    10/15/98 11:31a Nate
 * Added Launcher Sound toggling
 *
 * 36    10/13/98 3:03p Nate
 * More fixes and changes.
 *
 * 35    10/12/98 8:17p Nate
 * Added -lowmem command line switch for kevin
 *
 * 34    10/10/98 2:33p Nate
 * More fixes.
 *
 * 33    10/08/98 6:23p Nate
 * Fixed a few bugs.
 *
 * 32    10/02/98 7:08p Nate
 * Added animation button
 *
 * 31    10/01/98 3:51p Nate
 * Changed some file names and paths.
 *
 * 30    9/30/98 5:16p Nate
 * Added Icon to "Demo Only" message box
 *
 * 29    9/30/98 2:01p Nate
 * Added "Not available in Demo" message boxes.
 *
 * 28    9/29/98 2:23p Nate
 * Pressing play now launches descent3.exe
 *
 * 27    9/25/98 6:58p Nate
 * User cannot "Play" now unless he has selected a PreferredRenderer other
 * than "None"
 *
 * 26    9/23/98 3:30p Nate
 * Added "demo" conditional compilation
 *
 * 25    9/22/98 3:33p Nate
 * Added conditional compiling to help system (can toggle between HTML and
 * standard windows help)
 *
 * 24    9/22/98 11:33a Nate
 * Added support for logo button text.
 *
 * 23    9/21/98 5:40p Nate
 * Incorporated the new HTML help system
 *
 * 22    9/18/98 5:19p Nate
 * Enabled the help buttons for the Setup tabs.
 *
 * 21    9/17/98 5:59p Nate
 * "README.TXT file not found" error is now handled by the launcher rather
 * than notepad
 *
 * 20    9/17/98 2:09p Nate
 * Added StraightToSetup messages.
 *
 * 19    9/16/98 3:23p Nate
 * Added straight to setup processing
 *
 * 18    9/14/98 3:47p Nate
 * Added deletion of memDC's after use.
 *
 * 17    9/13/98 2:40p Nate
 * Added re-selecting of default bitmaps and palettes for the device
 * contexts.
 *
 * 16    9/10/98 5:17p Nate
 * Added text message capability to bitmap buttons
 *
 * 15    9/09/98 1:10p Nate
 * Now reads in the Uninstall application DisplayName from registry.
 *
 * 14    9/09/98 12:24p Nate
 * Added Uninstall functionality.
 *
 * 13    9/08/98 11:05a Nate
 * The background bitmap is now drawn in OnEraseBkgnd() rather than in
 * OnPaint() - this eliminates the gray background flicker on startup
 *
 * 12    9/04/98 10:18a Nate
 * Made it so light won't flicker for a certain time after startup.
 *
 * 11    9/03/98 6:57p Nate
 * Fixed StretchBlt() problem by doing some 256 color conversions
 *
 * 10    9/02/98 6:42p Nate
 * Added improved sound support.
 *
 * 9     9/01/98 7:15p Nate
 * Major Revision #2
 *
 * 8     8/31/98 6:44p Nate
 * Major Revision
 *
 * 7     8/25/98 6:15p Nate
 * Added the Message of the Day to the Auto Update Dialog
 *
 * 6     8/24/98 7:06p Nate
 * Added new AutoUpdate features, and fixed display glitches
 *
 * 5     8/17/98 10:35a Nate
 * Added Keyboard Type page to Setup
 *
 * 4     8/12/98 9:21a Nate
 * Fixed "gray-button-background" flicker
 *
 * 3     8/10/98 10:44a Nate
 * Added Language selection support
 *
 * 2     8/05/98 11:54a Nate
 * Initial Version
 *
 * $NoKeywords: $
 */

// D3LaunchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "afxext.h"
#include "D3Launch.h"
#include "D3LaunchDlg.h"
#include "UpdateDlg.h"
#include "DirectXTab.h"
#include "JoystickTab.h"
#include "VideoTab.h"
#include "AudioTab.h"
#include "SpeedTab.h"
#include "NetworkTab.h"
#include "KeyboardTab.h"
#include "DriversDlg.h"
#include "3D_detect.h"
#include "OS_Config.h"
#include "LaunchNames.h"
#include "GLSetupDlg.h"
#include "FindFastDlg.h"
#include "SetupPropSheet.h"

#include "dsetup.h"

#include <stdlib.h>
#include <time.h>
#include <direct.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Globals
CString szTitle;
CD3LaunchDlg *pLaunchDlg;

UINT light_off_time;  // Counts the number of msecs light has been off
UINT startup_time;    // Counts msecs from startup
UINT anim_frame_time; // Counts msecs between animation frames

bool mouse_moved;     // flag to indicate if mouse has been moved
POINT last_mouse_pos; // records the last mouse position

// Store the proper IDs for the bitmap buttons here:
static UINT ButtonIDs[NUM_BITMAP_BUTTONS] = {
    IDC_BTN_PLAY,      IDC_BTN_SETUP,   IDC_BTN_UPDATE, IDC_BTN_README, IDC_BTN_DIRECTX,
    IDC_BTN_UNINSTALL, IDC_BTN_WEBPAGE, IDC_BTN_PXO,    ID_HELP,
    IDC_BTN_QUIT // NOTE: Make this the last one (it uses different sounds)
};

// Store the proper string IDs for the bitmap buttons here:
// NOTE: Use NO_MESSAGE if no message is desired
#define NO_MESSAGE 0
static UINT ButtonStringIDs[NUM_BITMAP_BUTTONS] = {IDS_D3LAUNCHDLG_PLAY_BTN,
                                                   IDS_D3LAUNCHDLG_SETUP_BTN,
                                                   IDS_D3LAUNCHDLG_UPDATE_BTN,
                                                   IDS_D3LAUNCHDLG_README_BTN,
                                                   IDS_D3LAUNCHDLG_DIRECTX_BTN,
                                                   IDS_D3LAUNCHDLG_UNINSTALL_BTN,
                                                   IDS_D3LAUNCHDLG_WEBPAGE_BTN,
                                                   IDS_D3LAUNCHDLG_PXO_BTN,
                                                   NO_MESSAGE,
                                                   NO_MESSAGE};

// Store the proper text alignments for the bitmap buttons here:
static UINT ButtonOrientations[NUM_BITMAP_BUTTONS] = {
    LEFT_ORIENTED_BTN,  LEFT_ORIENTED_BTN, LEFT_ORIENTED_BTN, RIGHT_ORIENTED_BTN, RIGHT_ORIENTED_BTN,
    RIGHT_ORIENTED_BTN, TOP_ORIENTED_BTN,  TOP_ORIENTED_BTN,  LEFT_ORIENTED_BTN,  LEFT_ORIENTED_BTN};

/////////////////////////////////////////////////////////////////////////////
// CD3LaunchDlg dialog

CD3LaunchDlg::CD3LaunchDlg(CWnd *pParent /*=NULL*/) : CDialog(CD3LaunchDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CD3LaunchDlg)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD3LaunchDlg::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CD3LaunchDlg)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CD3LaunchDlg, CDialog)
//{{AFX_MSG_MAP(CD3LaunchDlg)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_CREATE()
ON_BN_CLICKED(IDC_BTN_QUIT, OnBtnQuit)
ON_BN_CLICKED(IDC_BTN_SETUP, OnBtnSetup)
ON_BN_CLICKED(IDC_BTN_WEBPAGE, OnBtnWebpage)
ON_BN_CLICKED(IDC_BTN_README, OnBtnReadme)
ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
ON_WM_TIMER()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDC_BTN_PXO, OnBtnPxo)
ON_BN_CLICKED(IDC_BTN_UNINSTALL, OnBtnUninstall)
ON_BN_CLICKED(IDC_BTN_LIGHT, OnBtnLight)
ON_BN_CLICKED(IDC_BTN_DIRECTX, OnBtnDirectx)
ON_WM_QUERYNEWPALETTE()
ON_WM_PALETTECHANGED()
ON_MESSAGE(WM_STRAIGHT_TO_SETUP, OnStraightToSetup)
ON_WM_HELPINFO()
ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD3LaunchDlg message handlers

BOOL CD3LaunchDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);  // Set big icon
  SetIcon(m_hIcon, FALSE); // Set small icon

  // TODO: Add extra initialization here
  int j;

  pLaunchDlg = this;

  srand((unsigned)time(NULL));

  m_timerID = SetTimer(MOUSE_TIMER_ID, MAIN_TIMER_DELAY, NULL);

  // Dim all System Menu options we don't want
  CMenu *sysmenu = GetSystemMenu(FALSE);
  if (sysmenu != NULL) {
    sysmenu->EnableMenuItem(0, MF_BYPOSITION | MF_GRAYED);
    sysmenu->EnableMenuItem(2, MF_BYPOSITION | MF_GRAYED);
    sysmenu->EnableMenuItem(4, MF_BYPOSITION | MF_GRAYED);
  }

  CBitmap *dlgBmap;

  dlgBmap = &(Editor()->m_bkBmap);

  RECT rectClient;
  dlgBmap->GetObject(sizeof(BITMAP), &m_bmInfo);
  GetClientRect(&rectClient);

  // Calculate the bitmap dimension modifiers
  DlgWidthModifier = double(rectClient.right) / double(m_bmInfo.bmWidth);
  DlgHeightModifier = double(rectClient.bottom) / double(m_bmInfo.bmHeight);

  char msg1[256];
  sprintf(msg1, "WidthMod=%f, HeightMod=%f\n", DlgWidthModifier, DlgHeightModifier);
  OutputDebugString(msg1);

  // If they are close to being one, just make them one
  if (DlgWidthModifier > 0.99 && DlgWidthModifier < 1.01)
    DlgWidthModifier = 1.0;
  if (DlgHeightModifier > 0.99 && DlgHeightModifier < 1.01)
    DlgHeightModifier = 1.0;

  // Calculate the size and position of the background bitmap
  m_size.cx = int32_t(m_bmInfo.bmWidth * DlgWidthModifier);
  m_size.cy = int32_t(m_bmInfo.bmHeight * DlgHeightModifier);

  m_pt.x = 0;
  m_pt.y = 0;

  // CClientDC dc(this);

  // VERIFY( m_dcMem.CreateCompatibleDC(&dc));
  // m_dcMem.SelectObject(dlgBmap);

  // Setup the "pushable" bitmap buttons
  for (j = 0; j < NUM_BITMAP_BUTTONS; j++) {
    m_Buttons[j].Setup(ButtonIDs[j], this, ButtonOrientations[j]);
    if (ButtonStringIDs[j] != NO_MESSAGE)
      m_Buttons[j].SetText(ButtonStringIDs[j]);

    // if(ButtonIDs[j]==IDC_BTN_UNINSTALL)
    //	m_Buttons[j].EnableWindow(FALSE);
  }

  // Setup the blinking light bitmap button
  m_Light.Setup(IDC_BTN_LIGHT, this);
  m_Light.IgnoreDisabled(TRUE);
  m_Light.Light(TRUE);

  // Setup the blinking light bitmap button
  m_Anim.AnimSetup(IDC_ANIM_BUTTON, this, NUM_ANIM_FRAMES);
  anim_frame_time = 0;

  // Uncomment this if you don't want the animation to show up
  // m_Anim.ShowWindow(SW_HIDE);

#ifdef USE_MULTI_LANGUAGES
  // Set the language
  int lang_type = os_config_read_uint(szSectionName, "LanguageType", LANGUAGE_ENGLISH);
  SetLanguageDLL(lang_type);
  RefreshDialog();

  // Copy over the appropriate help files
  if (Editor()->m_straight_to_setup)
    CopyHelpFiles(TRUE);
  else
    CopyHelpFiles(FALSE);
#endif

  // See if DirectDraw is installed on the system
  CString dd_msg, dd_title;
  dd_msg.LoadString(IDS_D3LAUNCHDLG_NODD);
  dd_title.LoadString(IDS_D3LAUNCHDLG_NODDT);

  Dd_dll_handle = LoadLibrary("ddraw.dll");
  if (!Dd_dll_handle) {
    MessageBox(dd_msg, dd_title, MB_OK | MB_ICONEXCLAMATION);
  }

#if (!defined(DEMO) && !defined(DEMO2) && !defined(OEM_VOODOO3) && !defined(OEM_KATMAI))
  // Startup the registration app
  if (EregEnabled) {
    Register(TRUE);
  }
#endif

  // Play the startup sound!!!!
  PlaySound("StartupSnd", FALSE, FALSE, FALSE);

  // Start the startup time counter
  startup_time = 0;

  // the mouse hasn't moved yet...
  mouse_moved = FALSE;
  ::GetCursorPos(&last_mouse_pos);

  // if we should be going straight to the Setup, do it now!
  if (Editor()->m_straight_to_setup) {
    PostMessage(WM_STRAIGHT_TO_SETUP);
  }

  return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD3LaunchDlg::OnPaint() {
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
    CPaintDC dc(this); // device context for painting

    /* NOTE: The following is now done in OnEraseBkgnd()
    // Create a memory DC compatible with the paint DC
    CDC memDC;
    CRect crect;
    GetClientRect(&crect);

    memDC.CreateCompatibleDC( &dc );
    CBitmap *bitmap=&(Editor()->m_bkBmap);
    CPalette *palette=&(Editor()->m_palette);

    memDC.SelectObject( bitmap );	// Select and realize the palette
    if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && palette->m_hObject != NULL )	{
            dc.SelectPalette( palette, FALSE );
            dc.RealizePalette();
    }
    dc.StretchBlt(0,0,m_size.cx,m_size.cy,&memDC,0,0,m_bmInfo.bmWidth,m_bmInfo.bmHeight,SRCCOPY);
    */

    // Do not call CDialog::OnPaint() for painting mesages
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD3LaunchDlg::OnQueryDragIcon() { return (HCURSOR)m_hIcon; }

int CD3LaunchDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CDialog::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO: Add your specialized creation code here

  // set the window title
  SetWindowText(szTitle);

  return 0;
}

void CD3LaunchDlg::OnBtnQuit() {
  // Play quit button pressed (shutdown) sound
  PlaySound("NormalBtnPressedSnd", TRUE, TRUE);

  // TODO: Add your control notification handler code here
  EndDialog(0);
}

void CD3LaunchDlg::OnBtnSetup() {
  // TODO: Add your control notification handler code here
  CSetupPropSheet sheet("Setup");

  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

#if (defined(DEMO) || defined(DEMO2))
  // Show the Interplay tournament prompt if necessary
  DisplayTournamentPrompt();
#endif

  if (os_config_read_uint(szSectionName, "ProfanityPrevention", 9999) == 9999) {
    CString title, msg;
    title.Format(IDS_PROFANITY_TITLE);
    msg.Format(IDS_PROFANITY_MSG);
    if (MessageBox(msg, title, MB_YESNO | MB_ICONQUESTION) == IDYES)
      os_config_write_uint(NULL, "ProfanityPrevention", 1);
    else
      os_config_write_uint(NULL, "ProfanityPrevention", 0);
  }

  // Display Setup Window
  CString setup_title;
  setup_title.LoadString(IDS_D3LAUNCHDLG_SETUP);
  sheet.Construct(setup_title);

  CDirectXTab directXtab;
  CVideoTab videotab;
  CAudioTab audiotab;
  CJoystickTab joytab;
  CSpeedTab speedtab;
  CNetworkTab networktab;
  CKeyboardTab keyboardtab;

  // Turn off the HELP and APPLY buttons
  // sheet.m_psh.dwFlags &= (~PSH_HASHELP);
  sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
  // directXtab.m_psp.dwFlags &= (~PSP_HASHELP);
  // videotab.m_psp.dwFlags &= (~PSP_HASHELP);
  // audiotab.m_psp.dwFlags &= (~PSP_HASHELP);
  // joytab.m_psp.dwFlags &= (~PSP_HASHELP);
  // speedtab.m_psp.dwFlags &= (~PSP_HASHELP);
  // networktab.m_psp.dwFlags &= (~PSP_HASHELP);
  // keyboardtab.m_psp.dwFlags &= (~PSP_HASHELP);

  sheet.AddPage(&directXtab);
  sheet.AddPage(&videotab);
  sheet.AddPage(&audiotab);
  sheet.AddPage(&joytab);
  sheet.AddPage(&speedtab);
  sheet.AddPage(&networktab);
  sheet.AddPage(&keyboardtab);

  if (sheet.DoModal() == IDOK) {
    if (Editor()->m_straight_to_setup) {
      os_config_write_uint(szSectionName, "StraightToSetup", 0);
      Editor()->m_straight_to_setup = 0;
    }
    if (DetailLevelConfigured)
      os_config_write_uint(szSectionName, "DetailLevelConfigured", 1);
#ifdef USE_MULTI_LANGUAGES
    if (NewLanguageSelected) {
      int lang_type = os_config_read_uint(szSectionName, "LanguageType", LANGUAGE_ENGLISH);
      SetLanguageDLL(lang_type);
      RefreshDialog();

      // Copy over the appropriate help files
      CopyHelpFiles(TRUE);
    }
#endif

    // Get the currently selected renderer type
    RendererType renderer_id = (RendererType)os_config_read_uint(NULL, "PreferredRenderer", RENDERER_NONE);

    // If they detected renderers, set vsync for jason
    if (RenderersDetected) {
      int vsync_enabled;

      if (renderer_id == RENDERER_DIRECT3D)
        vsync_enabled = 1;
      else
        vsync_enabled = 0;

      os_config_write_uint(NULL, "RS_vsync", vsync_enabled);
      RenderersDetected = FALSE;
    }

    // Display the openGL warning message
    if (renderer_id == RENDERER_OPENGL) {
      if (os_config_read_uint(NULL, "OpenGLWarningShown", 0) == 0) {
        CString title, msg;
        title.Format(IDS_OPENGL_WARNING_TITLE);
        msg.Format(IDS_OPENGL_WARNING_MSG);
        MessageBox(msg, title, MB_OK | MB_ICONINFORMATION);
        os_config_write_uint(NULL, "OpenGLWarningShown", 1);
      }
    }
  }

  DetailLevelConfigured = FALSE;
  NewLanguageSelected = FALSE;
}

void CD3LaunchDlg::OnBtnWebpage() {
  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

  // TODO: Add your control notification handler code here
  url_launch("http://www.outrage.com/");
}

void CD3LaunchDlg::OnBtnReadme() {
  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

#if (defined(DEMO) || defined(DEMO2) || defined(OEM_GENERIC) || defined(OEM_VOODOO3) || defined(OEM_KATMAI))
  // Make sure readme.txt file exist
  if (_access("readme.txt", 0x00) == -1) { // does new executable exist?
    CString readme_msg, readme_title;
    readme_title.LoadString(IDS_D3LAUNCHDLG_FILE_NOT_FOUND);
    readme_msg.LoadString(IDS_D3LAUNCHDLG_RM_ERR);
    MessageBox(readme_msg, readme_title, MB_OK | MB_ICONEXCLAMATION);
    return;
  }

  // TODO: Add your control notification handler code here
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  memset(&si, 0, sizeof(STARTUPINFO));
  si.cb = sizeof(si);

  BOOL ret = CreateProcess(NULL,                      // pointer to name of executable module
                           "notepad readme.txt",      // pointer to command line string
                           NULL,                      // pointer to process security attributes
                           NULL,                      // pointer to thread security attributes
                           FALSE,                     // handle inheritance flag
                           CREATE_DEFAULT_ERROR_MODE, // creation flags
                           NULL,                      // pointer to new environment block
                           NULL,                      // pointer to current directory name
                           &si,                       // pointer to STARTUPINFO
                           &pi                        // pointer to PROCESS_INFORMATION
  );

  if (!ret) {
    char *lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR)&lpMsgBuf, 0, NULL);

    // Display the string.
    CString readme_msg;
    readme_msg.LoadString(IDS_D3LAUNCHDLG_RM_ERR);
    MessageBox(lpMsgBuf, readme_msg, MB_OK | MB_ICONEXCLAMATION);

    // Free the buffer.
    LocalFree(lpMsgBuf);
  }
#else
  // TODO: Add your control notification handler code here
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  memset(&si, 0, sizeof(STARTUPINFO));
  si.cb = sizeof(si);

  BOOL ret = CreateProcess(NULL,                      // pointer to name of executable module
                           README_VIEWER_FNAME,       // pointer to command line string
                           NULL,                      // pointer to process security attributes
                           NULL,                      // pointer to thread security attributes
                           FALSE,                     // handle inheritance flag
                           CREATE_DEFAULT_ERROR_MODE, // creation flags
                           NULL,                      // pointer to new environment block
                           NULL,                      // pointer to current directory name
                           &si,                       // pointer to STARTUPINFO
                           &pi                        // pointer to PROCESS_INFORMATION
  );

  if (!ret) {
    char *lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR)&lpMsgBuf, 0, NULL);

    // Display the string.
    CString readme_msg;
    readme_msg.LoadString(IDS_D3LAUNCHDLG_RM_ERR);
    MessageBox(lpMsgBuf, readme_msg, MB_OK | MB_ICONEXCLAMATION);

    // Free the buffer.
    LocalFree(lpMsgBuf);
  }
#endif
}

#define MAX_CMD_LINE_LEN 1024
void CD3LaunchDlg::OnBtnPlay() {
  CString msg, title, low_mem_switch, no_lightmaps_switch, chflight_switch, mouseman_switch;
  bool dedicated_switch_set;

  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, TRUE);

  // Check the command line to see if it's being run as dedicated server
  char *command_line;
  char command_line_temp[MAX_CMD_LINE_LEN + 1];
  command_line = os_config_read_string(szSectionName, "CmdLineOptions", "");
  strncpy(command_line_temp, command_line, MAX_CMD_LINE_LEN);
  command_line_temp[MAX_CMD_LINE_LEN] = '\0';
  StringToLower(command_line_temp);
  if (strstr(command_line_temp, "-dedicated ") == NULL)
    dedicated_switch_set = FALSE;
  else
    dedicated_switch_set = TRUE;

  // Display message explaining that user must configure system
  if (Editor()->m_straight_to_setup) {
    msg.LoadString(IDS_D3LAUNCHDLG_PLAY_WARNING_MSG);
    title.LoadString(IDS_AUDIOTAB_WARNING);
    if (MessageBox(msg, title, MB_YESNO | MB_ICONWARNING) != IDYES)
      return;
  }

  // Display the message stating that user has not configured detail level
  if (os_config_read_uint(NULL, "DetailLevelConfigured", 0) == 0) {
    msg.LoadString(IDS_D3LAUNCHDLG_SPD_MSG);
    title.LoadString(IDS_D3LAUNCHDLG_SPD_TITLE);
    MessageBox(msg, title, MB_OK | MB_ICONWARNING);
    return;
  }

  // Display message if user has not selected a rendering device
  if (!dedicated_switch_set && os_config_read_uint(NULL, "PreferredRenderer", RENDERER_NONE) == RENDERER_NONE) {
    msg.LoadString(IDS_D3LAUNCHDLG_NO_RENDERER_MSG);
    title.LoadString(IDS_D3LAUNCHDLG_NO_RENDERER_TITLE);
    MessageBox(msg, title, MB_OK | MB_ICONWARNING);
    return;
  }

  // Display message if user does not have at least DirectX 3.0 installed
  if (GetDirectXVersion() < 3) {
    CString title, msg;
    title.LoadString(IDS_D3LAUNCHDLG_DXVERSION_TITLE);
    msg.LoadString(IDS_D3LAUNCHDLG_DXVERSION_MSG);
    MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
    return;
  }

  // Display the low memory message
  MEMORYSTATUS ms;
  GlobalMemoryStatus(&ms);
  low_mem_switch = "";
  if ((ms.dwAvailPageFile + ms.dwTotalPhys) < (80 * 1024 * 1024)) {
    CString title, msg;
    title.LoadString(IDS_D3LAUNCHDLG_NOMEM_TITLE);
    msg.LoadString(IDS_D3LAUNCHDLG_NOMEM_MSG);
    if (MessageBox(msg, title, MB_YESNO | MB_ICONWARNING) != IDYES)
      return;
    low_mem_switch = "-lowmem";
  }

#if (defined(OEM_VOODOO3) || defined(OEM_KATMAI))
  // Display the update recommendation message
  if (os_config_read_uint(NULL, "UpdatePromptShown", 0) == 0) {
    os_config_write_uint(NULL, "UpdatePromptShown", 1);
    msg.LoadString(IDS_D3LAUNCHDLG_UPDPRMT_MSG);
    title.LoadString(IDS_D3LAUNCHDLG_UPDPRMT_TITLE);
    if (MessageBox(msg, title, MB_YESNO | MB_ICONQUESTION) == IDYES) {
      OnBtnUpdate();
      return;
    }
  }
#endif

  // display findfast dialog if needed.
  HWND ffhwnd = ::FindWindow("Find Fast Indexer", NULL);

  if (ffhwnd) {
    CFindFastDlg findfastdlg;
    uint32_t disable_ffast = os_config_read_uint(szSectionName, "FindFastDisable", 1);
    uint32_t show_ffast_dlg = os_config_read_uint(szSectionName, "ShowFindFastDlg", 1);

    if (show_ffast_dlg || !disable_ffast) {
      int iDisableFF;
      findfastdlg.m_AlwaysTerminateFF = disable_ffast ? TRUE : FALSE;
      iDisableFF = findfastdlg.DoModal();
      if (iDisableFF == IDOK) {
        os_config_write_uint(szSectionName, "FindFastDisable", findfastdlg.m_AlwaysTerminateFF ? 1 : 0);
        disable_ffast = 1;
      } else {
        os_config_write_uint(szSectionName, "FindFastDisable", 0);
        disable_ffast = 0;
      }
      os_config_write_uint(szSectionName, "ShowFindFastDlg", 0);
    }

    if (disable_ffast) {
      // Find fast was found
      int num_shutdown_checks = 0;
      ::SendMessage(ffhwnd, WM_COMMAND, 0xe141, 0);
      do {
        Sleep(100);
        ffhwnd = ::FindWindow("Find Fast Indexer", NULL);
        num_shutdown_checks++;
      } while (ffhwnd != NULL && num_shutdown_checks < 10);

      // If FindFast is still running, display warning prompt
      if (ffhwnd != NULL) {
        msg.LoadString(IDS_FINDFAST_MSG);
        title.LoadString(IDS_FINDFAST_TITLE);
        if (MessageBox(msg, title, MB_YESNO | MB_ICONWARNING) != IDYES)
          return;
      }
    }
  }

  // Read any option command line switches specified by user in Setup/Misc
  char *cmd_line_options;
  cmd_line_options = os_config_read_string(szSectionName, "CmdLineOptions", "");

  // Get rid of any gamma related environment variables
  SetEnvironmentVariable("SST_RGAMMA", NULL);
  SetEnvironmentVariable("SST_GGAMMA", NULL);
  SetEnvironmentVariable("SST_BGAMMA", NULL);
  SetEnvironmentVariable("SST_GAMMA", NULL);

  SetEnvironmentVariable("SSTV2_RGAMMA", NULL);
  SetEnvironmentVariable("SSTV2_GGAMMA", NULL);
  SetEnvironmentVariable("SSTV2_BGAMMA", NULL);
  SetEnvironmentVariable("SSTV2_GAMMA", NULL);

  // Don't use lightmaps if using lowest detail setting
  if (os_config_read_uint(NULL, "PredefDetailSetting", MEDIUM_DETAIL) == LOW_DETAIL) {
    no_lightmaps_switch = "-nolightmaps";
  } else {
    no_lightmaps_switch = "";
  }

  // Set the Flightstick Pro Mode Switch if necessary
  if (os_config_read_uint(szSectionName, "EnableCHFlight", 0)) {
    chflight_switch = "-chpro";
  } else {
    chflight_switch = "";
  }

  // Set the Mouseman Mode Switch if necessary
  if (os_config_read_uint(szSectionName, "EnableMouseman", 0)) {
    mouseman_switch = "-mouseman";
  } else {
    mouseman_switch = "";
  }

  // TODO: Add your control notification handler code here
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  CString ExecFile, CommandLine;

  ExecFile = GAME_EXECUTABLE_FNAME;

  // Get the command line arguments of the launcher and just pass
  // them through to Descent 3.  We have to becareful not to pass
  // the launcher.exe name over (as it maybe too long, if the path is,
  // for the argument system).  There is no easy way to get this filename
  // out, that is guaranteed.  As the user might have a ' ' in their path
  // to the launcher, or they might actually (*gasp*) rename the launcher.
  // Or the might be running it from the root directory, so we can't look
  // for a directory.  Just a number of problems.  So, what we'll do is
  // look for the first - or + (that follows a space), we'll assume that
  // the first command line argument will start with a - or a +.  This
  // method will fail if they install Descent 3 into a directory that has
  // a space in the path, followed by a + or a -.  But that won't cause us too much
  // trouble, as just the rest of that path will get passed in as a command line
  // argument.
  int first_arg, launch_length;
  CString launch_command;
  launch_command = GetCommandLine();

  launch_length = launch_command.GetLength();
  first_arg = launch_command.Find(" -", 0);
  if (first_arg == -1)
    first_arg = launch_command.Find(" +", 0);
  if (first_arg == -1) {
    launch_command = "";
  } else {
    launch_command = launch_command.Right(launch_length - first_arg - 1);
  }

  CommandLine.Format("%s %s %s %s %s %s %s %s", ExecFile, GAME_EXECUTABLE_SWITCH, low_mem_switch.GetBuffer(0),
                     cmd_line_options, no_lightmaps_switch.GetBuffer(0), chflight_switch.GetBuffer(0),
                     mouseman_switch.GetBuffer(0), launch_command.GetBuffer(0));

  memset(&si, 0, sizeof(STARTUPINFO));
  si.cb = sizeof(si);

  BOOL ret = CreateProcess(ExecFile.GetBuffer(0),     // pointer to name of executable module
                           CommandLine.GetBuffer(0),  // pointer to command line string
                           NULL,                      // pointer to process security attributes
                           NULL,                      // pointer to thread security attributes
                           FALSE,                     // handle inheritance flag
                           CREATE_DEFAULT_ERROR_MODE, // creation flags
                           NULL,                      // pointer to new environment block
                           NULL,                      // pointer to current directory name
                           &si,                       // pointer to STARTUPINFO
                           &pi                        // pointer to PROCESS_INFORMATION
  );

  if (ret) {
    // If it executed correctly, exit this program
    EndDialog(0);
  } else {
    char *lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR)&lpMsgBuf, 0, NULL);

    // Display the string
    CString launch_msg, error_msg;
    error_msg.Format(IDS_D3LAUNCHDLG_LAUNCH_ERRMSG, GAME_EXECUTABLE_FNAME);
    error_msg += lpMsgBuf;
    launch_msg.LoadString(IDS_D3LAUNCHDLG_LNCH_ERR);
    MessageBox(error_msg, launch_msg, MB_OK | MB_ICONEXCLAMATION);

    // Free the buffer.
    LocalFree(lpMsgBuf);
  }
}

// Checks if the mouse is currently over a button
bool CD3LaunchDlg::MouseOverButton(CButton *button) {
  RECT btn_rect;
  POINT point;

  // Check if launcher has focus first
  if (GetActiveWindow() != this)
    return FALSE;

  // Is the button disabled?
  if (!button->IsWindowEnabled())
    return FALSE;

  ::GetCursorPos(&point);
  button->GetWindowRect(&btn_rect);

  // Check left and right button borders
  if (point.x < btn_rect.left || point.x > btn_rect.right)
    return FALSE;

  // Check left and right button borders
  if (point.y < btn_rect.top || point.y > btn_rect.bottom)
    return FALSE;

  // Mouse is over button
  return TRUE;
}

// Plays a sound (OPTIONAL: only if the this window is active)
void CD3LaunchDlg::PlaySound(LPSTR lpName, bool OnlyPlayIfActiveWnd, bool WaitUntilDone,
                             bool WaitForStartup /*=TRUE*/) {
  if (!LauncherSoundEnabled)
    return;

  if (WaitForStartup && startup_time < STARTUP_DELAY_TIME)
    return;

  if (!OnlyPlayIfActiveWnd || GetActiveWindow() == this)
    PlayResource(lpName, WaitUntilDone);
}

// Invalidates the button's window so that it is redrawn
void CD3LaunchDlg::RedrawButton(CButton *button) {
  /*
  RECT btn_rect;

  button->GetWindowRect(&btn_rect);
  button->ScreenToClient(&btn_rect);
  button->InvalidateRect(&btn_rect,FALSE);
  */
  button->Invalidate(FALSE);
}

// Hides or Un-Hides a button (depending on value of mHide)
void CD3LaunchDlg::HideButton(CBitmapButtonEx *button, bool mHide) {
  RECT btn_rect;

  button->Hide(mHide);

  if (mHide) {
    button->GetWindowRect(&btn_rect);
    ScreenToClient(&btn_rect);
    InvalidateRect(&btn_rect, FALSE);
  } else
    RedrawButton(button);
}

// Processes launcher's timing events
void CD3LaunchDlg::OnTimer(UINT nIDEvent) {
  // TODO: Add your message handler code here and/or call default
  if (nIDEvent == m_timerID) {

    // See if the mouse has been moved since last time
    POINT curr_mouse_pos;
    ::GetCursorPos(&curr_mouse_pos);
    if (curr_mouse_pos.x != last_mouse_pos.x || curr_mouse_pos.y != last_mouse_pos.y) {
      mouse_moved = TRUE;
      last_mouse_pos.x = curr_mouse_pos.x;
      last_mouse_pos.y = curr_mouse_pos.y;
    }

    // Increment the startup time counter if necessary
    if (startup_time < STARTUP_DELAY_TIME)
      startup_time += MAIN_TIMER_DELAY;

    // Check if mouse is over any of the bitmap buttons
    for (int j = 0; j < NUM_BITMAP_BUTTONS; j++) {

      // If button is hidden, don't bother checking
      if (m_Buttons[j].IsHidden())
        continue;

      if (mouse_moved && MouseOverButton(&m_Buttons[j])) {
        if (!m_Buttons[j].IsLit()) {
          m_Buttons[j].Light(TRUE);
          RedrawButton(&m_Buttons[j]);

          // only play sound if button doesn't already have focus
          if (GetFocus() != &m_Buttons[j]) {

            // play "mouse is over button" sound
            if (j == NUM_BITMAP_BUTTONS - 1)
              PlaySound("PowerBtnLitSnd", TRUE, FALSE);
            else
              PlaySound("NormalBtnLitSnd", TRUE, FALSE);
          }
        }

        // Set the button to have focus
        m_Buttons[j].SetFocus();
        mouse_moved = FALSE;

      } else if (m_Buttons[j].IsLit()) {
        m_Buttons[j].Light(FALSE);
        RedrawButton(&m_Buttons[j]);
      }
    }

    // Check if the light bitmap button should flicker
    if (m_Light.IsLit()) {
      if ((startup_time >= STARTUP_DELAY_TIME) && (rand() % LIGHT_FLICKER_OFF_ODDS) == 0) {
        m_Light.Light(FALSE);
        RedrawButton(&m_Light);

        // Set light off time to nothing
        light_off_time = 0;

        // Play light flicker sound
        PlaySound("BulbFlickerSnd", TRUE, FALSE);
      }
    } else {
      // If light has been off enough time, turn it back on
      light_off_time += MAIN_TIMER_DELAY;
      if (light_off_time >= MAX_LIGHT_OFF_TIME) {
        m_Light.Light(TRUE);
        RedrawButton(&m_Light);
      }
    }

    // Increment the animation frame time counter
    anim_frame_time += MAIN_TIMER_DELAY;

    // Check if the animation bitmap should display the next frame
    if (anim_frame_time >= MAX_ANIM_FRAME_TIME) {
      m_Anim.DoNextAnimFrame();
      RedrawButton(&m_Anim);
      anim_frame_time = 0;
    }
  }

  CDialog::OnTimer(nIDEvent);
}

void CD3LaunchDlg::OnLButtonDown(UINT nFlags, CPoint point) {
  // TODO: Add your message handler code here and/or call default

  CDialog::OnLButtonDown(nFlags, point);

  // fake windows into thinking your clicking on the caption,
  // lets you drag the window by clicking anywhere on the dialog
  PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

void CD3LaunchDlg::OnBtnUpdate() {
  // TODO: Add your control notification handler code here
  int nResponse;
  CUpdateDlg dlg;

  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

  nResponse = dlg.DoModal();

  if (nResponse == IDOK) {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with OK
  } else if (nResponse == IDCANCEL) {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with Cancel
  } else if (nResponse == IDSHUTDOWN) {
    // This is only returned from the UpdateDlg when a Launcher update
    // is supposed to take place. hence, the entire launcher must shutdown
    EndDialog(0);
  }
}

BOOL CD3LaunchDlg::PreCreateWindow(CREATESTRUCT &cs) {
  // TODO: Add your specialized code here and/or call the base class

  return CDialog::PreCreateWindow(cs);
}

// Sets the new language resource DLL
bool CD3LaunchDlg::SetLanguageDLL(int lang_type) {
  // If a DLL is currently loaded, free it
  if (Editor()->m_hResInst != NULL) {
    FreeLibrary(Editor()->m_hResInst);
    Editor()->m_hResInst = NULL;
  }

  switch (lang_type) {
  case LANGUAGE_ENGLISH:
    AfxSetResourceHandle(Editor()->m_hDefResInst);
    return TRUE;
  case LANGUAGE_FRENCH:
    Editor()->m_hResInst = LoadLibrary(FRENCH_RESOURCE_DLL);
    break;
  case LANGUAGE_GERMAN:
    Editor()->m_hResInst = LoadLibrary(GERMAN_RESOURCE_DLL);
    break;
  case LANGUAGE_ITALIAN:
    Editor()->m_hResInst = LoadLibrary(ITALIAN_RESOURCE_DLL);
    break;
  case LANGUAGE_SPANISH:
    Editor()->m_hResInst = LoadLibrary(SPANISH_RESOURCE_DLL);
    break;
  }

  if (Editor()->m_hResInst != NULL) {
    AfxSetResourceHandle(Editor()->m_hResInst);
    return TRUE;
  }

  AfxSetResourceHandle(Editor()->m_hDefResInst);
  return FALSE;
}

// This function can be called after a new resource DLL has
// been loaded in to update the dialog with a new title, etc.
void CD3LaunchDlg::RefreshDialog(void) {
  int j;

  // set the window title
  SetLauncherTitleString();
  SetWindowText(szTitle);

  // Redraw the launcher bitmap images for new language
  for (j = 0; j < NUM_BITMAP_BUTTONS; j++) {
    if (ButtonStringIDs[j] != NO_MESSAGE)
      m_Buttons[j].SetText(ButtonStringIDs[j]);
    RedrawButton(&m_Buttons[j]);
  }
}

// This function is called whenever the dialog's background needs to
// be erased. It simply returns saying that the dialog's background has already
// been erased (after drawing the bitmap over the background).
// This is necessary to prevent the "gray-dialog-background"
// flicker during window updates
BOOL CD3LaunchDlg::OnEraseBkgnd(CDC *pDC) {
  // TODO: Add your message handler code here and/or call default
  CDC memDC;
  CBitmap *old_bitmap = NULL;
  CPalette *old_palette = NULL;
  CRect crect;
  GetClientRect(&crect);

  CBitmap *bitmap = &(Editor()->m_bkBmap);
  CPalette *palette = &(Editor()->m_palette);

  // Select and realize the palette
  if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && palette->m_hObject != NULL) {
    old_palette = pDC->SelectPalette(palette, FALSE);
    pDC->RealizePalette();
  }

  memDC.CreateCompatibleDC(pDC);
  old_bitmap = memDC.SelectObject(bitmap);

  pDC->StretchBlt(0, 0, m_size.cx, m_size.cy, &memDC, 0, 0, m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);

  if (old_bitmap != NULL)
    memDC.SelectObject(old_bitmap);

  if (old_palette != NULL)
    pDC->SelectPalette(old_palette, FALSE);

  if (memDC.DeleteDC() == 0)
    OutputDebugString("DeleteDC() failed!\n");

  // return CDialog::OnEraseBkgnd(pDC);
  return 1;
}

BOOL CD3LaunchDlg::DestroyWindow() {
  // TODO: Add your specialized code here and/or call the base class
  if (Dd_dll_handle != NULL) {
    FreeLibrary(Dd_dll_handle);
    Dd_dll_handle = NULL;
  }

  return CDialog::DestroyWindow();
}

void CD3LaunchDlg::OnBtnPxo() {
  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

  // TODO: Add your control notification handler code here
  url_launch("http://www.parallaxonline.com/");
}

void CD3LaunchDlg::OnBtnUninstall() {
  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

  // TODO: Add your control notification handler code here
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  char reg_command_line[1024];
  char app_name[1024];
  char *temp_str;

  // Grab the uninstall path
  temp_str = os_config_read_string_ex(UNINSTALL_PATH, "UninstallString", NULL);
  if (!temp_str) {
    CString msg, title;
    msg.LoadString(IDS_D3LAUNCHDLG_NO_UNINSTALL);
    title.LoadString(IDS_D3LAUNCHDLG_COULDNT_UNINSTALL);
    MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
    return;
  }
  strcpy(reg_command_line, temp_str);

  // Grab the application display name
  temp_str = os_config_read_string_ex(UNINSTALL_PATH, "DisplayName", NULL);
  if (!temp_str) {
    CString msg, title;
    msg.LoadString(IDS_D3LAUNCHDLG_NO_UNINSTALL);
    title.LoadString(IDS_D3LAUNCHDLG_COULDNT_UNINSTALL);
    MessageBox(msg, title, MB_OK | MB_ICONEXCLAMATION);
    return;
  }
  strcpy(app_name, temp_str);

  // display the "are you sure" prompt
  CString warning_prompt, warning_title;
  warning_prompt.Format(IDS_D3LAUNCHDLG_WARNING_PROMPT, app_name);
  warning_title.LoadString(IDS_D3LAUNCHDLG_WARNING_TITLE);
  int warning_ret = MessageBox(warning_prompt, warning_title, MB_OKCANCEL | MB_ICONQUESTION);
  if (warning_ret == IDCANCEL) {
    return;
  }

  // Launch the uninstaller
  char command_line[1024];
  strcpy(command_line, reg_command_line);
  strcat(command_line, " -y"); // Default to Yes.

  memset(&si, 0, sizeof(STARTUPINFO));
  si.cb = sizeof(si);

  BOOL ret = CreateProcess(NULL,                      // pointer to name of executable module
                           command_line,              // pointer to command line string
                           NULL,                      // pointer to process security attributes
                           NULL,                      // pointer to thread security attributes
                           FALSE,                     // handle inheritance flag
                           CREATE_DEFAULT_ERROR_MODE, // creation flags
                           NULL,                      // pointer to new environment block
                           NULL,                      // pointer to current directory name
                           &si,                       // pointer to STARTUPINFO
                           &pi                        // pointer to PROCESS_INFORMATION
  );

  if (ret) {
    // If it executed correctly, exit this program
    EndDialog(0);

  } else {
    char *lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR)&lpMsgBuf, 0, NULL);

    // Display the string.
    CString error_title;
    error_title.LoadString(IDS_D3LAUNCHDLG_UNINSTALL_ERROR);
    MessageBox(lpMsgBuf, error_title);

    // Free the buffer.
    LocalFree(lpMsgBuf);
  }
}

void CD3LaunchDlg::OnBtnLight() {
  // Play light flicker sound
  PlaySound("BulbFlickerSnd", TRUE, FALSE);

  // TODO: Add your control notification handler code here
}

// Locates the user's CD-ROM drive
int CD3LaunchDlg::find_cd_drive(char *subdir) {
  char oldpath[_MAX_PATH];
  char volume[256];
  int i;
  int cdrom_drive = -1;

  GetCurrentDirectory(_MAX_PATH, oldpath);

  for (i = 0; i < 26; i++) {
    char path[] = "d:\\";

    path[0] = (char)('A' + i);
    if (GetDriveType(path) == DRIVE_CDROM) {
      cdrom_drive = -3;
      GetVolumeInformation(path, volume, 256, NULL, NULL, NULL, NULL, 0);
      if (!stricmp(volume, CD1_VOLUME_NAME) || !stricmp(volume, CD2_VOLUME_NAME)) {
        if (!_chdir(path)) {
          if (subdir == NULL || !_chdir(subdir)) {
            cdrom_drive = i;
            break;
          }
        }
      }
    }
  }

  SetCurrentDirectory(oldpath);
  return cdrom_drive;
}

// return cd drive number (if found).  Return < 0 if no cd drive located
int CD3LaunchDlg::launcher_get_CD_path(char *path, int prompt_for_cd, char *subdir) {
  int cd_drive_num = -1;

  // locate the cd-rom
  path[0] = 0;
  while (1) {
    int msgbox_choice;
    cd_drive_num = find_cd_drive(subdir);

    if (cd_drive_num >= 0) {
      break;
    }

    if (!prompt_for_cd) {
      cd_drive_num = -1;
      break;
    }

    // ask if they want to try again
    CString msg, title;
    msg.LoadString(IDS_D3LAUNCH_NO_CD);
    title.LoadString(IDS_D3LAUNCH_CD_ERROR);
    msgbox_choice = MessageBox(msg, title, MB_OKCANCEL | MB_ICONWARNING);
    if (msgbox_choice == IDCANCEL) {
      return -1;
    }
  }

  return cd_drive_num;
}

void CD3LaunchDlg::OnBtnDirectx() {
  // Play button pressed sound
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

#if (defined(DEMO) || defined(DEMO2))
  CString demo_msg, demo_title;
  demo_msg.LoadString(IDS_D3LAUNCHDLG_DEMO_ONLY_MSG);
  demo_title.LoadString(IDS_D3LAUNCHDLG_DEMO_ONLY_TITLE);
  MessageBox(demo_msg, demo_title, MB_OK | MB_ICONEXCLAMATION);
  return;
#endif

  CDriversDlg dlg;
  if (dlg.DoModal() == IDCANCEL)
    return;

  switch (dlg.m_Selection) {
  case INSTALL_DIRECTX:
    InstallDirectX();
    break;
  case INSTALL_GLSETUP:
    RunOpenGLSetup();
    break;
  }
}

typedef int(CALLBACK *LPFN_DIRECTXSETUP)(HWND, LPSTR, DWORD);

void CD3LaunchDlg::InstallDirectX() {
  OSVERSIONINFO ver;
  char CD_path[_MAX_PATH];
  char DLL_path[_MAX_PATH];
  int cd_drive_num;

  // check if running under NT
  ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&ver);
  if (ver.dwPlatformId == VER_PLATFORM_WIN32_NT) {
    CString msg, title;
    msg.LoadString(IDS_DIRECTXTAB_NTMSG);
    title.LoadString(IDS_DIRECTXTAB_NTNOTICE);
    MessageBox(msg, title);
    return;
  }

  cd_drive_num = launcher_get_CD_path(CD_path, 1, "\\directx6");
  if (cd_drive_num < 0) {
    return;
  }

  char original_path[_MAX_PATH];
  _getcwd(original_path, _MAX_PATH - 1);

  sprintf(CD_path, "%c:\\", 'a' + cd_drive_num);
  strcat(CD_path, "directx6");
  _chdir(CD_path);

  HINSTANCE dsetup_dll_handle = NULL;
  LPFN_DIRECTXSETUP pfn_DirectXSetup = NULL;

  // Check for the DirectXSetup dll, and open it
  strcpy(DLL_path, CD_path);
  strcat(DLL_path, "\\dsetup.dll");
  dsetup_dll_handle = LoadLibrary(DLL_path);
  if (dsetup_dll_handle == NULL) {
    CString msg, title;
    msg.Format(IDS_D3LAUNCHDLG_DSETUP_ERR_MSG1);
    title.Format(IDS_D3LAUNCHDLG_DSETUP_ERR_TITLE);
    MessageBox(msg, title);
    SetCurrentDirectory(original_path);
    return;
  }

  // Get the DirectXSetup function
  pfn_DirectXSetup = (LPFN_DIRECTXSETUP)GetProcAddress(dsetup_dll_handle, "DirectXSetupA");
  if (pfn_DirectXSetup == NULL) {
    CString msg, title;
    msg.Format(IDS_D3LAUNCHDLG_DSETUP_ERR_MSG2);
    title.Format(IDS_D3LAUNCHDLG_DSETUP_ERR_TITLE);
    MessageBox(msg, title);
    FreeLibrary(dsetup_dll_handle);
    dsetup_dll_handle = NULL;
    SetCurrentDirectory(original_path);
    return;
  }

  int rc = pfn_DirectXSetup(this->m_hWnd, CD_path, DSETUP_DIRECTX);

  CString err_msg, err_title;
  err_title.Format(IDS_D3LAUNCHDLG_DXERR_TITLE);
  switch (rc) {
  case DSETUPERR_SUCCESS:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_SUCCESS);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_SUCCESS_RESTART:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_SUCCESS_RESTART);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_BADSOURCESIZE:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_BADSOURCESIZE);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_BADSOURCETIME:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_BADSOURCETIME);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_BADWINDOWSVERSION:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_BADWINDOWSVERSION);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_CANTFINDDIR:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_CANTFINDDIR);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_CANTFINDINF:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_CANTFINDINF);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_INTERNAL:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_INTERNAL);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_NOCOPY:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_NOCOPY);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_NOTPREINSTALLEDONNT:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_NOTPREINSTALLEDONNT);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_OUTOFDISKSPACE:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_OUTOFDISKSPACE);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_SOURCEFILENOTFOUND:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_SOURCEFILENOTFOUND);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_UNKNOWNOS:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_UNKNOWNOS);
    MessageBox(err_msg, err_title);
    break;
  case DSETUPERR_USERHITCANCEL:
    err_msg.Format(IDS_D3LAUNCHDLG_DXERR_USERHITCANCEL);
    MessageBox(err_msg, err_title);
    break;
  };

  FreeLibrary(dsetup_dll_handle);
  dsetup_dll_handle = NULL;

  SetCurrentDirectory(original_path);
}

void CD3LaunchDlg::RunOpenGLSetup() {
  // display the opengl setup dialog
  CGLSetupDlg dlg;

  if (dlg.DoModal() == IDCANCEL)
    return;

  // run the install program
  char CD_path[_MAX_PATH];
  int cd_drive_num;

  cd_drive_num = launcher_get_CD_path(CD_path, 1, "\\GLSetup");
  if (cd_drive_num < 0) {
    return;
  }

  char original_path[_MAX_PATH];
  _getcwd(original_path, _MAX_PATH - 1);

  sprintf(CD_path, "%c:\\", 'a' + cd_drive_num);
  strcat(CD_path, "GLSetup");
  _chdir(CD_path);

  // ok, now run GLSetup
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  memset(&si, 0, sizeof(STARTUPINFO));
  si.cb = sizeof(si);

  BOOL ret = CreateProcess("glsetup.exe",             // pointer to name of executable module
                           NULL,                      // pointer to command line string
                           NULL,                      // pointer to process security attributes
                           NULL,                      // pointer to thread security attributes
                           FALSE,                     // handle inheritance flag
                           CREATE_DEFAULT_ERROR_MODE, // creation flags
                           NULL,                      // pointer to new environment block
                           NULL,                      // pointer to current directory name
                           &si,                       // pointer to STARTUPINFO
                           &pi                        // pointer to PROCESS_INFORMATION
  );

  if (!ret) {
    char *lpMsgBuf;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR)&lpMsgBuf, 0, NULL);

    // Display the string.
    CString err_title;
    err_title.LoadString(IDS_GLSETUP_ERROR);
    MessageBox(lpMsgBuf, err_title);

    // Free the buffer.
    LocalFree(lpMsgBuf);
  }

  SetCurrentDirectory(original_path);
}

BOOL CD3LaunchDlg::OnQueryNewPalette() {
  OutputDebugString("OnQueryNewPalette() called.\n");

  int j;
  Invalidate(TRUE);
  for (j = 0; j < NUM_BITMAP_BUTTONS; j++)
    m_Buttons[j].Invalidate(TRUE);
  return TRUE;
}

void CD3LaunchDlg::OnPaletteChanged(CWnd *pFocusWnd) {
  if (pFocusWnd == this) {
    OutputDebugString("OnPaletteChanged() called for this window.\n");
    return;
  }
  OutputDebugString("OnPaletteChanged() called.\n");

  // Redraw (and realize palettes for) the dialog bitmap and buttons
  int j;
  Invalidate(TRUE);
  for (j = 0; j < NUM_BITMAP_BUTTONS; j++)
    m_Buttons[j].Invalidate(TRUE);
}

LONG CD3LaunchDlg::OnStraightToSetup(UINT, LONG) {
  CString msg, title;

  // Display message explaining that user must configure system
  msg.LoadString(IDS_D3LAUNCHDLG_STRAIGHTTOSETUP_MSG);
  title.LoadString(IDS_D3LAUNCHDLG_STRAIGHTTOSETUP_TITLE);
  MessageBox(msg, title, MB_OK | MB_ICONINFORMATION);

  // Startup the setup dialog so user can configure system settings
  OnBtnSetup();

  return 0;
}

BOOL CD3LaunchDlg::OnHelpInfo(HELPINFO *pHelpInfo) {
  // TODO: Add your message handler code here and/or call default
#ifdef USE_HTML_HELP_SYSTEM
  CWaitCursor wc;
  help_launch(MAIN_MENU_HELP);
  return 1;
#else
  return CDialog::OnHelpInfo(pHelpInfo);
#endif
}

// Display the html help file
afx_msg LRESULT CD3LaunchDlg::OnCommandHelp(WPARAM wParam, LPARAM lParam) {
  PlaySound("NormalBtnPressedSnd", TRUE, FALSE);

#ifdef USE_HTML_HELP_SYSTEM
  help_launch(MAIN_MENU_HELP);
  return 1;
#else
  return CDialog::OnCommandHelp(wParam, lParam);
#endif
}

// Major HACK to allow user to select an option via the Enter button
void CD3LaunchDlg::OnOK() {
  // TODO: Add extra validation here
  CButton *selected_button;
  int ctrl_id;
  HWND hwnd;

  // Get the currently highlighted/focused button
  selected_button = (CButton *)GetFocus();
  if (selected_button == NULL)
    return;

  // Make the button look like it's been clicked
  selected_button->SetState(true);
  Sleep(80);
  selected_button->SetState(false);

  // Trick main window into thinking that button has been clicked
  ctrl_id = selected_button->GetDlgCtrlID();
  hwnd = selected_button->m_hWnd;
  PostMessage(WM_COMMAND, (BN_CLICKED << 16) + ctrl_id, (LPARAM)hwnd);

  // CDialog::OnOK();
}

#define TOURNAMENT_URL "http://www.interplay.com/descent3/ftourney.html"

// Displays tournament contest web link prompt
void CD3LaunchDlg::DisplayTournamentPrompt(void) {
  int rc, already_displayed;
  CString msg, title;

  // If the prompt has already been displayed, exit
  already_displayed = os_config_read_uint(szSectionName, "TournamentPromptDisplayed", 0);
  if (already_displayed)
    return;

  // Check the system date, if it is after July 1, 1999, exit
  SYSTEMTIME sys_time;
  GetSystemTime(&sys_time);
  if (sys_time.wYear > 1999)
    return;
  if (sys_time.wYear == 1999 && sys_time.wMonth > 7)
    return;
  if (sys_time.wYear == 1999 && sys_time.wMonth == 7 && sys_time.wDay > 1)
    return;
  // msg.Format("year=%d\nmonth=%d\nday=%d",sys_time.wYear,sys_time.wMonth,sys_time.wDay);

  msg.Format(IDS_D3LAUNCHDLG_CONTEST_MSG, TOURNAMENT_URL);
  title.Format(IDS_D3LAUNCHDLG_CONTEST_TITLE);

  // Display the tournament contest web link prompt
  rc = MessageBox(msg, title, MB_YESNO | MB_ICONQUESTION);

  // Store flag in registry so we don't display this message again
  os_config_write_uint(szSectionName, "TournamentPromptDisplayed", 1);

  // If user selected "Yes", then display the web page
  if (rc == IDYES)
    url_launch(TOURNAMENT_URL);
}
