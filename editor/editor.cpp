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

 * $Logfile: /DescentIII/Main/editor/editor.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:37 $
 * $Author: kevinb $
 *
 * The main editor MFC file.
 *
 * $Log: not supported by cvs2svn $
 *
 * 73    4/17/99 2:46p Matt
 * Implemented viewer properties dialog functions.
 *
 * 72    4/16/99 3:54p Nate
 * Added Viewer Properties Dialog
 *
 * 71    4/04/99 6:21p Matt
 * Added hack to pause the app and keep it paused.
 *
 * 69    3/15/99 5:38p Matt
 * Changed idle loop back to old way because Sean says the new code made
 * slewing chunky.
 *
 * 68    3/15/99 4:15p Matt
 * Changed the idle handler to not always return true.  Hopefully this
 * will keep the editor from eating up all the processor time when it's
 * not doing anything.
 *
 * 67    2/25/99 10:45p Matt
 * Don't redraw wireframe if view has rotated but not moved
 *
 * 66    2/21/99 6:38p Samir
 * mouse and key input better. buffered mouse.
 *
 * 65    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 64    1/27/99 10:35a Samir
 * suspend resume keys added.
 *
 * 63    1/20/99 10:50a Jason
 * added new terrain
 *
 * 62    1/19/99 6:53p Matt
 * Fixed a problem when the viewer was instantaneously moved from inside
 * to ourside or vise-versa.
 *
 * 61    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 60    1/07/99 12:27p Samir
 * took out parse command line info call.
 *
 * 59    12/23/98 3:35p Nate
 * Added DallasModelessDlgPtr data member
 *
 * 58    12/01/98 11:17p Matt
 * Added menu option to disable drawing objects in the wireframe view
 *
 * 57    11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 56    10/17/98 1:25p Sean
 * Made PrintToDlgItem work with long strings
 *
 * 55    10/16/98 1:02p Samir
 * no ddio_KeyFrame.
 *
 * 54    10/13/98 12:03p Kevin
 * Changed use of preprocessors for debug, etc.
 *
 * 53    9/22/98 1:55p Matt
 * Change the registry path to "Outrage\Descent3".
 *
 * 52    9/08/98 11:37a Samir
 * added key to toggle joystick slewing.
 *
 * 51    9/04/98 3:16p Samir
 * control whether to allow joystick slewing.
 *
 * 50    8/04/98 2:32p Chris
 * Improved attach code added more fixes to the AABB partial computation
 * patch
 *
 * 49    7/10/98 2:12p Jeff
 * added a flag for inventory information in objinfo
 *
 * 48    6/17/98 12:30p Samir
 * don't draw wireframe when moving an object.
 *
 * 47    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 46    6/10/98 12:20p Matt
 * Revamped system that controls what textures are displayed on the
 * texture tab.  Should work correctly now, and will now save the settings
 * to the registry.  Also, textures now default to no type set, not all
 * types set.
 *
 * 45    6/08/98 6:13p Matt
 * Update the wireframe view when the viewer has stopped slewing
 *
 * 44    5/20/98 6:59p Samir
 * added slew speed slider.
 *
 * 43    5/20/98 1:43p Matt
 * Shift-T now moves a placed building up and down.
 *
 * 42    2/25/98 6:11p Samir
 * Added functions to better deal with key flushing.
 *
 * 41    2/18/98 2:39a Matt
 * Don't update the wireframe view if the only change is that the viewer
 * moved
 *
 * 40    2/10/98 1:59p Chris
 * Improved the path system
 *
 * 39    2/05/98 2:58p Matt
 * Cleaned up slew code, and made view mode switch when slewing between
 * mine and terrain happen in editor, not slew.
 *
 * 38    1/28/98 5:07p Samir
 * Object modeless settings added.
 *
 * 37    12/01/97 5:32p Samir
 * Argh, more housekeeping for FileDialog function.
 *
 * 36    12/01/97 5:23p Samir
 * When initialdir is empty for FileDialog, then don't use it as a search
 * path.
 *
 * 35    12/01/97 5:17p Samir
 * New functions to open a file dialog.
 *
 * 34    11/13/97 6:16p Matt
 * Changed some vars (such as current_powerup) to initialize to 0 instead
 * of -1
 *
 * 33    10/27/97 5:45p Jason
 * added prelim networking stuff, just to get it started
 *
 * 32    10/16/97 2:31p Samir
 * Added keyboard handler to idle loop.
 *
 * 31    10/01/97 7:52p Matt
 * Added code for external rooms
 *
 * 30    9/29/97 12:09p Jason
 * added functionality to doorway system
 *
 * 29    9/23/97 3:04p Jason
 * added tmap2 rotation key (KEY_EQUAL)
 *
 * 28    9/17/97 11:40a Matt
 * Ripped out segment code
 *
 * 27    9/16/97 1:04p Samir
 * Added include of AppDatabase.h
 *
 * 26    9/09/97 6:07p Matt
 * If 't' key pressed when no placed room or group, do nothing
 *
 * 25    9/08/97 4:05p Samir
 * Fixed some warnings and took out extranneous includes to windows.h in
 * important headers.
 *
 * 24    9/06/97 3:15p Matt
 * Removed old trigger stuff from registry load/save
 * Added function PrintToDlgItem()
 *
 * 23    8/29/97 1:50p Samir
 * Added object moving mouse polling and registry entry for axis mode.
 *
 * 22    8/26/97 11:38a Samir
 * Added Editor_active global to determine whether editor is currently
 * active (useful for any window using the gr library.)
 *
 * 21    8/19/97 5:58p Samir
 * OLE additions
 *
 * 20    8/18/97 6:59p Matt
 * Implemented Place Room/Attach room system
 *
 * 19    8/13/97 9:55a Matt
 * Allow sliding & rotating textures with the mouse
 *
 * 18    8/12/97 7:06p Chris
 * Made AABB work in the editor.
 *
 * 17    8/12/97 5:26p Matt
 * Read/write new vars from/to registry
 *
 * 16    8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 15    8/01/97 11:59a Samir
 * Added a preference for debugging in fullscreen.
 *
 * 14    7/28/97 1:23p Jeff
 * Set default external editor to Notepad
 *
 * 13    7/28/97 10:51a Jeff
 * Changed cha *DefaultExternalEditor to what it should be called, char
 * Default_external_editor[256]
 *
 * 12    7/27/97 11:07p Matt
 * Save/load external editor string to/from registry.
 *
 * 11    7/25/97 6:17p Samir
 * When floating keypad values are loaded from database, mark keypad as
 * moved.
 *
 * 10    7/24/97 2:58p Matt
 * Added functions to load and save D3EditState variables from/to the
 * registry
 *
 * 9     7/22/97 7:07p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 8     7/21/97 1:18p Samir
 * You can now type stuff in keypads.
 *
 * 47    6/09/97 12:07p Samir
 * for edit boxes, don't automatically switch focus to main view.
 *
 * 46    6/04/97 3:08p Jason
 * changed backspace key to lshift+backspace
 *
 * 45    5/13/97 4:36p Samir
 * call main-frame's onidle function
 *
 * 44    4/02/97 5:20p Jason
 * made wireframe not update when player moves in the terrain view
 *
 * 43    4/02/97 3:25p Jason
 * got rid of WV_changed and made TV_changed update the textured view and
 * flag "World_changed"
 *
 * 42    4/02/97 11:16a Matt
 * Update the wireframe view when the viewer moves, because the viewer is
 * drawn as a sphere in that view
 *
 * 41    4/01/97 11:00p Matt
 * Changed editor to keep a viewer object (type camera) seperate from the
 * player object.  This camera, and not the player, is now moved by
 * slewing, the C key, etc.  When going into the game, the viewer position
 * & orientation are copied to the player.  When going back to the editor,
 * the player position is copied to the viewer, and the player object is
 * reset to its start location.
 *
 * 40    3/31/97 5:57p Matt
 * Revamped mine update flags
 *
 * 39    3/31/97 3:13p Jason
 * added ship,weapon,and sounds to d3edit and zeroed it out upon startup
 *
 * 38    3/24/97 12:13p Samir
 * Set initial trigger type.
 *
 * 37    3/20/97 4:57p Samir
 * Adding IsSelecting to editorSelectorManager if we are curring drawing a
 * selection box, say in the wireframe window.
 *
 * 36    3/20/97 4:22p Samir
 * Added Segment Sizing mode and side sizing.
 *
 * 35    3/20/97 2:56p Samir
 * Moved SelManager var to SelManager.cpp
 *
 * 34    3/20/97 12:06p Samir
 * Added Selection Box manager.
 *
 * 33    3/20/97 11:20a Samir
 * Accelerator keys should work when focus is in keypad.
 *
 * 32    3/13/97 5:12p Samir
 * Call WinApp::OnIdle also in our idle loop.
 *
 * 31    3/07/97 4:18p Jason
 * implemented terrain functionality in the editor
 *
 * 30    3/05/97 12:16p Jason
 * added code to support our new 3d doors
 *
 * 29    3/03/97 11:23a Matt
 * Set/clear MFC's modified flag every time through the loop, not just if
 * the mine was changed
 * Don't prompt user about discarding changes if the level hasn't been
 * changed
 *
 * 28    2/20/97 4:41p Samir
 * You can now use keypad functions even if input focus is in keypad
 * dialog.
 *
 * 27    2/20/97 4:30p Samir
 * Slewing works a lot better when input focus is in keypad or any other
 * window other than the texture window.
 *
 * 26    2/20/97 1:03p Samir
 * Control + slew key will not slew the mine.
 *
 * 25    2/18/97 12:46p Samir
 * Initialized current object type to powerup.
 *
 * 24    2/17/97 6:09p Samir
 * made initial powerup be the shield powerup.
 *
 * 23    2/13/97 12:16p Jason
 * changes for powerup remapping
 *
 * 22    2/12/97 3:07p Samir
 * pause and resume now flush keyboard queue to stop backspace from
 * Int3ing.
 *
 * 21    2/11/97 1:42p Samir
 * Added document variable and set modification flag.
 *
 * 20    2/11/97 10:31a Jason
 * changed keystate checking for backspace
 *
 * 19    2/05/97 11:45a Samir
 * Initialized D3windowed editor state
 *
 * 18    2/03/97 7:56p Matt
 * Calculate Frame_time in editor loop
 *
 * 17    1/31/97 12:06p Jason
 * added support for animations in Dialogs
 * Also added more powerup functionality
 *
 * 16    1/23/97 4:00p Samir
 * More D3EditState vars with respect to floating keypads.
 *
 * 15    1/21/97 12:48p Samir
 * Added InitEditorState to define D3EditState info
 *
 * 14    1/20/97 4:13p Samir
 * Added backspace debug key.
 *
 * $NoKeywords: $
 */

// editor.cpp : Defines the class behaviors for the application.
//

#include <cstdarg>
#include <cstdio>

#include "stdafx.h"
#include "editor.h"
#include "MainFrm.h"
#include "IpFrame.h" // OLE
#include "editorDoc.h"
#include "editorView.h"
#include "slew.h"
#include "object.h"
#include "descent.h"
#include "moveworld.h"
#include "d3edit.h"
#include "pserror.h"
#include "args.h"
#include "game.h"
#include "trigger.h"
#include "HTexture.h"
#include "HRoom.h"
#include "erooms.h"
#include "AppDatabase.h"

#include "TextureGrWnd.h"
#include "WireframeGrWnd.h"
#include "SelManager.h"
#include "ObjMoveManager.h"
#include "ViewerPropDlg.h"

#include "mono.h"
#include "ddio.h"

#include "boa.h"
#include "terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

d3edit_state D3EditState;
grSurface *Desktop_surf = NULL;
bool Editor_active = true;

//	ADDED FOR OLE SUPPORT
// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {949F57CE-189E-11D1-BD9B-00A0C96ED595}
static const CLSID clsid = {0x949f57ce, 0x189e, 0x11d1, {0xbd, 0x9b, 0x0, 0xa0, 0xc9, 0x6e, 0xd5, 0x95}};
//	ADDED FOR OLE SUPPORT

/////////////////////////////////////////////////////////////////////////////
// CEditorApp

BEGIN_MESSAGE_MAP(CEditorApp, CWinApp)
//{{AFX_MSG_MAP(CEditorApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
// Standard file based document commands
ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorApp construction

CEditorApp::CEditorApp() {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance

  textured_view = NULL;
  wireframe_view = NULL;
  main_view = NULL;
  main_doc = NULL;
  main_frame = NULL;
  m_Paused = FALSE;

  m_DallasModelessDlgPtr = NULL;
  m_ViewerPropDlgPtr = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEditorApp object

CEditorApp theApp;

// icecoldduke: these arent defined in code anywhere
#define MAX_TEXTURE_SHADES 32
uint8_t TexShadeTable8[MAX_TEXTURE_SHADES][256];
uint64_t TexShadeTable16[MAX_TEXTURE_SHADES][256];
uint8_t TexRevShadeTable8[MAX_TEXTURE_SHADES][256];
uint64_t TexRevShadeTable16[MAX_TEXTURE_SHADES][256];

/////////////////////////////////////////////////////////////////////////////
// CEditorApp initialization

BOOL CEditorApp::InitInstance() {
  //	ADDED BY SAMIR FOR OLE SUPPORT.
  // Initialize OLE libraries
  if (!AfxOleInit()) {
    AfxMessageBox(IDP_OLE_INIT_FAILED);
    return FALSE;
  }
  AfxEnableControlContainer();
  //	ADDED BY SAMIR FOR OLE SUPPORT.

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls(); // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif

  //	ADDED TO UPGRADE TO MFC 5.0
  //	This registry area is really just for the editor.  No game settings or UI specifics
  // except those strictly managed by MFC will be put here.
  // Change the registry key under which our settings are stored.
  // You should modify this string to be something appropriate
  // such as the name of your company or organization.
  SetRegistryKey(_T("Outrage\\Descent3\\editor\\mfc"));
  //	ADDED TO UPGRADE TO MFC 5.0

  LoadStdProfileSettings(); // Load standard INI file options (including MRU)

  // Initialize editor state
  InitEditorState();

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views.

  CSingleDocTemplate *pDocTemplate;
  pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CEditorDoc),
                                        RUNTIME_CLASS(CMainFrame), // main SDI frame window
                                        RUNTIME_CLASS(CEditorView));

  //	ADDED BY SAMIR FOR OLE SUPPORT.
  pDocTemplate->SetServerInfo(IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE, RUNTIME_CLASS(CInPlaceFrame));
  //	ADDED BY SAMIR FOR OLE SUPPORT.

  AddDocTemplate(pDocTemplate);

  //	ADDED BY SAMIR FOR OLE SUPPORT.
  // Connect the COleTemplateServer to the document template.
  //  The COleTemplateServer creates new documents on behalf
  //  of requesting OLE containers by using information
  //  specified in the document template.
  m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
  // Note: SDI applications register server objects only if /Embedding
  //   or /Automation is present on the command line.
  //	ADDED BY SAMIR FOR OLE SUPPORT.

  // Parse command line for standard shell commands, DDE, file open
  GatherArgs(m_lpCmdLine);

  CCommandLineInfo cmdInfo;
  //	ParseCommandLine(cmdInfo);

  //	ADDED BY SAMIR FOR OLE SUPPORT.
  // Check to see if launched as OLE server
  if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated) {
    // Register all OLE server (factories) as running.  This enables the
    //  OLE libraries to create objects from other applications.
    COleTemplateServer::RegisterAll();

    // Application was run with /Embedding or /Automation.  Don't show the
    //  main window in this case.
    return TRUE;
  }
  // When a server application is launched stand-alone, it is a good idea
  //  to update the system registry in case it has been damaged.
  m_server.UpdateRegistry(OAT_INPLACE_SERVER);
  //	ADDED BY SAMIR FOR OLE SUPPORT.

  // Dispatch commands specified on the command line
  if (!ProcessShellCommand(cmdInfo))
    return FALSE;

  //	ADDED TO UPGRADE TO MFC 5.0
  // The one and only window has been initialized, so show and update it.
  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();
  //	ADDED TO UPGRADE TO MFC 5.0

  // Enable rich edits
  AfxInitRichEdit();
  return TRUE;
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
  // No message handlers
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

// App command to run the dialog
void CEditorApp::OnAppAbout() {
  CAboutDlg aboutDlg;

  theApp.pause();
  aboutDlg.DoModal();
  theApp.resume();
}

/////////////////////////////////////////////////////////////////////////////
// CEditorApp commands

// this is bad place to put this
int Slew_limitations = 0;

BOOL CEditorApp::OnIdle(LONG lCount) {
  static bool Dirty_wireframe = 0;
  bool viewer_rotated = 0;
  int key;

  //	determine if we should process idle messages
  if (m_Paused)
    return TRUE;

  // do our own input and output!
  ddio_Frame();

  /////////////////////////////////////////////////////////////////////////////
  //	all mouse button/drag functions go in this big if statement.  this
  // ensures that there are no conflicts between mouse drag operations
  if (!SelManager.IsSelecting() && !ObjMoveManager.IsMoving()) {
    //	slide current texture
    if (KEY_STATE(KEY_Y)) { // slide with mouse
      int x, y, dx, dy;
      ddio_MouseGetState(&x, &y, &dx, &dy);

      if (KEY_STATE(KEY_LCTRL) || KEY_STATE(KEY_RCTRL))
        HTextureRotate(Curroomp, Curface, (float)dx * 50.0);
      else
        HTextureSlide(Curroomp, Curface, (float)dx / 2.0, (float)-dy / 2.0);
    }
    //	attaching rooms.
    else if (KEY_STATE(KEY_T)) {
      if ((Placed_room != -1) || (Placed_group != NULL)) {
        int x, y, dx, dy;
        ddio_MouseGetState(&x, &y, &dx, &dy);

        if (KEY_STATE(KEY_LCTRL) || KEY_STATE(KEY_RCTRL))
          Placed_room_attachpoint +=
              (Placed_room_orient.rvec * (float)dx / 20.0) + (Placed_room_orient.uvec * (float)dy / 20.0);
        else if ((Placed_baseroomp == NULL) &&
                 (KEY_STATE(KEY_LSHIFT) || KEY_STATE(KEY_RSHIFT))) // If on terrain, slide up/down
          Placed_room_attachpoint += (Placed_room_orient.fvec * (float)dx / 20.0);
        else {
          Placed_room_angle += (float)dx * 20.0;
          ComputePlacedRoomMatrix();
        }

        State_changed = 1;
      }
    } else {
      MoveWorld();
    }
  }

  // very temorary key handler
  // Slew the texture view
  bool was_outside = (OBJECT_OUTSIDE(Viewer_object) != 0);
  int slew_flags = SlewFrame(Viewer_object, Slew_limitations);

  if (slew_flags & SLEW_MOVE) {
    Viewer_moved = 1;

    if (OBJECT_OUTSIDE(Viewer_object) && !was_outside)
      SetViewMode(VM_TERRAIN);
    if (!OBJECT_OUTSIDE(Viewer_object) && was_outside)
      SetViewMode(VM_MINE);
  }

  if (slew_flags & SLEW_ROTATE)
    viewer_rotated = 1;

  // Update the viewer properties dialog
  if (Viewer_moved && theApp.m_ViewerPropDlgPtr)
    theApp.m_ViewerPropDlgPtr->UpdatePosition();
  if ((Viewer_moved || viewer_rotated) && theApp.m_ViewerPropDlgPtr)
    theApp.m_ViewerPropDlgPtr->UpdateOrientation();

  if (slew_flags & SLEW_KEY) {
    //	note that if a slew key was pressed, the main view is out of keyboard focus, set
    //	keyboard focus to the main_view.
    if (main_view && main_view != CWnd::GetFocus()) {
      mprintf(0, "Restoring focus to main view.\n");
      main_view->SetFocus();
    }
  } else if (KEY_STATE(KEY_LCTRL) || KEY_STATE(KEY_RCTRL)) {
    //	this is done to support CTRL-KEYPAD functions if input focus is not in main view
    if (main_view && main_view != CWnd::GetFocus()) {
      mprintf(0, "Restoring focus to main view.\n");
      main_view->SetFocus();
    }
  }
  /*else if (ddio_KeyInKey()) {
  //	this is done if you press any other key while in a keypad, to use wireframe stuff
          if (main_view && main_view != CWnd::GetFocus()) {
                  CRuntimeClass *wndtype = CWnd::GetFocus()->GetRuntimeClass();
                  if (strcmp(wndtype->m_lpszClassName, "CEdit")) {
                          mprintf(0,"Restoring focus to main view.\n");
                          main_view->SetFocus();
                  }
          }
  }
  */

  key = ddio_KeyInKey();

  // toggle joystick slewing
  if (key == (KEY_ALTED + KEY_J)) {
    D3EditState.joy_slewing = !D3EditState.joy_slewing;
    SlewControlInit();
  }

  // Check if something in the world has changed, and if so set global changed flag
  if (World_changed) {
    Mine_changed = 1;

    // Create room objects
    CreateRoomObjects();
  }

  // See if there's a new mine, and set/clear flags as appropriate
  if (New_mine) {
    World_changed = 1; // force redraws
    Mine_changed = 0;  // clear global changed flag
  }

  if (New_mine || World_changed) {
    ComputeAABB(false);
  }

  // for old code

  int suppress_wireframe_redraw = 0;

  if (TV_changed) {
    World_changed = 1;
    suppress_wireframe_redraw = 1;
  }

  // Redraw the textured view if the world changed or the viewer moved
  if (textured_view && (World_changed || State_changed || Viewer_moved || viewer_rotated || Object_moved)) {
    textured_view->Render();
    textured_view->InvalidateRect(NULL, FALSE);
  }

  // Keep track of whether viewer moved for next frame, since we only redraw the
  // wireframe after the viewer has stopped slewing
  Dirty_wireframe |= (Viewer_moved != 0);

  // Redraw the wireframe view if the world changed or the view was changed
  if (wireframe_view && !suppress_wireframe_redraw &&
      ((World_changed || State_changed || Edview_changed) ||
       (!Viewer_moved && !viewer_rotated && Dirty_wireframe && !(Editor_view_mode == VM_TERRAIN)))) {
    if (!Object_moved) {
      wireframe_view->Render();
      wireframe_view->InvalidateRect(NULL, FALSE);
      Dirty_wireframe = 0;
    }
  }

  // Check to stop slew.  (Why is this here?)
  if (ddio_KeyDownTime(KEY_PAD5) > 0)
    SlewStop(Viewer_object);

  // Check for debugger break
  if (KEY_STATE(KEY_BACKSP) > 0 && KEY_STATE(KEY_LSHIFT) > 0) {
    Int3();
    ddio_KeyFlush();
  }

  // What does this do?
  if (main_frame)
    main_frame->OnIdle();

  // Reset all flags
  World_changed = State_changed = Viewer_moved = Edview_changed = New_mine = TV_changed = 0;

  // Compute Frame_time
  CalcFrameTime();

  // Tell MFC whether or not our document has been changed
  if (main_doc)
    main_doc->SetModifiedFlag(Mine_changed);

  //	this is done to allow selection boxes in the main frame.
  SelManager.Defer();

  // this is done to allow object moving
  ObjMoveManager.Defer();

  // defer to MFC
  CWinApp::OnIdle(lCount);

  return TRUE;
}

// Save current editor settings to the registry
void SaveEditorSettings() {
  oeLnxAppDatabase Editor_database((oeLnxAppDatabase *)Database);
  bool res;
  int speed;

  res = Editor_database.lookup_record("editor");
  if (!res) {
    mprintf(0, "Can't get editor registry path\n");
    Int3();
    return;
  }

  Editor_database.write("texdlg_texture", D3EditState.texdlg_texture);
  Editor_database.write("current_obj_type", D3EditState.current_obj_type);
  Editor_database.write("current_powerup", D3EditState.current_powerup);
  Editor_database.write("current_door", D3EditState.current_door);
  Editor_database.write("current_robot", D3EditState.current_robot);
  Editor_database.write("current_ship", D3EditState.current_ship);
  Editor_database.write("current_sound", D3EditState.current_sound);
  Editor_database.write("current_weapon", D3EditState.current_weapon);
  Editor_database.write("current_path", D3EditState.current_path);
  Editor_database.write("current_node", D3EditState.current_node);
  Editor_database.write("current_megacell", D3EditState.current_megacell);
  Editor_database.write("current_clutter", D3EditState.current_clutter);
  Editor_database.write("current_building", D3EditState.current_building);
  Editor_database.write("texscr_visible", D3EditState.texscr_visible);
  Editor_database.write("texscr_x", D3EditState.texscr_x);
  Editor_database.write("texscr_y", D3EditState.texscr_y);
  Editor_database.write("texscr_w", D3EditState.texscr_w);
  Editor_database.write("texscr_h", D3EditState.texscr_h);
  Editor_database.write("wirescr_visible", D3EditState.wirescr_visible);
  Editor_database.write("wirescr_x", D3EditState.wirescr_x);
  Editor_database.write("wirescr_y", D3EditState.wirescr_y);
  Editor_database.write("wirescr_w", D3EditState.wirescr_w);
  Editor_database.write("wirescr_h", D3EditState.wirescr_h);
  Editor_database.write("keypad_visible", D3EditState.keypad_visible);
  Editor_database.write("keypad_current", D3EditState.keypad_current);
  Editor_database.write("float_keypad_x", D3EditState.float_keypad_x);
  Editor_database.write("float_keypad_y", D3EditState.float_keypad_y);
  Editor_database.write("float_keypad_w", D3EditState.float_keypad_w);
  Editor_database.write("float_keypad_h", D3EditState.float_keypad_h);
  Editor_database.write("objmodeless_x", D3EditState.objmodeless_x);
  Editor_database.write("objmodeless_y", D3EditState.objmodeless_y);
  Editor_database.write("objmodeless_on", D3EditState.objmodeless_on);
  Editor_database.write("tile_views", D3EditState.tile_views);
  Editor_database.write("game_render_mode", D3EditState.game_render_mode);
  Editor_database.write("terrain_dots", D3EditState.terrain_dots);
  Editor_database.write("terrain_flat_shade", D3EditState.terrain_flat_shade);
  Editor_database.write("randomize_megacell", D3EditState.randomize_megacell);
  Editor_database.write("box_selection_mode", D3EditState.box_selection_mode);
  Editor_database.write("object_move_mode", D3EditState.object_move_mode);
  Editor_database.write("fullscreen_debug", D3EditState.fullscreen_debug_state);
  Editor_database.write("object_move_axis", D3EditState.object_move_axis);
  Editor_database.write("texture_display_flags", D3EditState.texture_display_flags);

  speed = ((Slew_key_speed - 0.5) / 0.5);
  Editor_database.write("slew_key_speed", speed);
  Editor_database.write("joy_slewing", D3EditState.joy_slewing);
}

// Load editor settings from the registry
void LoadEditorSettings() {
  oeLnxAppDatabase Editor_database((oeLnxAppDatabase *)Database);
  bool res;
  int speed = (int)((Slew_key_speed - 0.5) / 0.5);

  res = Editor_database.lookup_record("editor");
  if (!res) {
    mprintf(0, "Can't get editor registry path\n");
    Int3();
    return;
  }

  Editor_database.read_int("texdlg_texture", &D3EditState.texdlg_texture);
  Editor_database.read_int("current_obj_type", &D3EditState.current_obj_type);
  Editor_database.read_int("current_powerup", &D3EditState.current_powerup);
  Editor_database.read_int("current_door", &D3EditState.current_door);
  Editor_database.read_int("current_robot", &D3EditState.current_robot);
  Editor_database.read_int("current_clutter", &D3EditState.current_clutter);
  Editor_database.read_int("current_building", &D3EditState.current_building);
  Editor_database.read_int("current_ship", &D3EditState.current_ship);
  Editor_database.read_int("current_sound", &D3EditState.current_sound);
  Editor_database.read_int("current_weapon", &D3EditState.current_weapon);
  Editor_database.read_int("current_path", &D3EditState.current_path);
  Editor_database.read_int("current_node", &D3EditState.current_node);
  Editor_database.read_int("current_megacell", &D3EditState.current_megacell);
  Editor_database.read("texscr_visible", &D3EditState.texscr_visible);
  Editor_database.read_int("texscr_x", &D3EditState.texscr_x);
  Editor_database.read_int("texscr_y", &D3EditState.texscr_y);
  Editor_database.read_int("texscr_w", &D3EditState.texscr_w);
  Editor_database.read_int("texscr_h", &D3EditState.texscr_h);
  Editor_database.read("wirescr_visible", &D3EditState.wirescr_visible);
  Editor_database.read_int("wirescr_x", &D3EditState.wirescr_x);
  Editor_database.read_int("wirescr_y", &D3EditState.wirescr_y);
  Editor_database.read_int("wirescr_w", &D3EditState.wirescr_w);
  Editor_database.read_int("wirescr_h", &D3EditState.wirescr_h);
  Editor_database.read("keypad_visible", &D3EditState.keypad_visible);
  Editor_database.read_int("keypad_current", &D3EditState.keypad_current);
  Editor_database.read_int("float_keypad_x", &D3EditState.float_keypad_x);
  Editor_database.read_int("float_keypad_y", &D3EditState.float_keypad_y);
  Editor_database.read_int("float_keypad_w", &D3EditState.float_keypad_w);
  Editor_database.read_int("float_keypad_h", &D3EditState.float_keypad_h);
  Editor_database.read_int("objmodeless_x", &D3EditState.objmodeless_x);
  Editor_database.read_int("objmodeless_y", &D3EditState.objmodeless_y);
  Editor_database.read("objmodeless_on", &D3EditState.objmodeless_on);
  Editor_database.read("tile_views", &D3EditState.tile_views);
  Editor_database.read_int("game_render_mode", &D3EditState.game_render_mode);
  Editor_database.read("terrain_dots", &D3EditState.terrain_dots);
  Editor_database.read("terrain_flat_shade", &D3EditState.terrain_flat_shade);
  Editor_database.read("randomize_megacell", &D3EditState.randomize_megacell);
  Editor_database.read_int("box_selection_mode", &D3EditState.box_selection_mode);
  Editor_database.read_int("object_move_mode", &D3EditState.object_move_mode);
  Editor_database.read("fullscreen_debug", &D3EditState.fullscreen_debug_state);
  Editor_database.read_int("object_move_axis", &D3EditState.object_move_axis);
  Editor_database.read_int("slew_key_speed", &speed);
  Editor_database.read_int("texture_display_flags", &D3EditState.texture_display_flags);
  Editor_database.read_int("joy_slewing", &D3EditState.joy_slewing);

  Slew_key_speed = ((float)speed * 0.5) + 0.5;

  //	Since we are loading in the values of the floating keypad's position, it has moved.
  //	If the values for the floating keypad position haven't been set, then don't specify
  //	the keypad as having moved. - Samir
  if (D3EditState.float_keypad_x != -1)
    D3EditState.float_keypad_moved = 1;
}

//	InitEditorState
//		loads in editor state values and sets them
void CEditorApp::InitEditorState() {
  float scr_aspect_x, scr_aspect_y;

  scr_aspect_x = ((float)GetSystemMetrics(SM_CXSCREEN)) / ((float)EDITOR_RESOLUTION_X);
  scr_aspect_y = ((float)GetSystemMetrics(SM_CYSCREEN)) / ((float)EDITOR_RESOLUTION_Y);

  // Initialize all variables to zero
  memset(&D3EditState, 0, sizeof(d3edit_state));

  // Initialize a bunch of non-zero variables in case there are no variables in the registry

  D3EditState.texscr_visible = 1;
  D3EditState.texscr_x = 0;
  D3EditState.texscr_y = 0;
  D3EditState.texscr_w = (int)(scr_aspect_x * ((float)TEXSCREEN_WIDTH));
  D3EditState.texscr_h = (int)(scr_aspect_y * ((float)TEXSCREEN_HEIGHT));

  D3EditState.wirescr_visible = 1;
  D3EditState.wirescr_x = 20;
  D3EditState.wirescr_y = 20;
  D3EditState.wirescr_w = (int)(scr_aspect_x * ((float)WIRESCREEN_WIDTH));
  D3EditState.wirescr_h = (int)(scr_aspect_y * ((float)WIRESCREEN_HEIGHT));

  D3EditState.keypad_visible = 1;
  D3EditState.keypad_current = TAB_TEXTURE_KEYPAD;

  D3EditState.float_keypad_moved = 0;
  D3EditState.float_keypad_x = -1;
  D3EditState.float_keypad_y = -1;
  D3EditState.float_keypad_w = -1;
  D3EditState.float_keypad_h = -1;

  D3EditState.objmodeless_x = GetSystemMetrics(SM_CXSCREEN) / 2;
  D3EditState.objmodeless_y = GetSystemMetrics(SM_CYSCREEN) / 2;
  D3EditState.objmodeless_on = false;

  D3EditState.tile_views = 1;

  D3EditState.current_obj_type = OBJ_POWERUP;
  D3EditState.current_powerup = 0;
  D3EditState.current_building = 0;
  D3EditState.current_clutter = 0;
  D3EditState.current_door = 0;

  D3EditState.current_room = -1;

  D3EditState.node_movement_inc = 1.0f;

  //	preferences
  D3EditState.game_render_mode = GM_WINDOWED;
  D3EditState.fullscreen_debug_state = false;
  D3EditState.object_move_axis = OBJMOVEAXIS_XY;
  D3EditState.texscale = 1.0;
  D3EditState.joy_slewing = true;
  D3EditState.objects_in_wireframe = true;

  Editor_active = true;
}

CDocument *CEditorApp::OpenDocumentFile(LPCTSTR lpszFileName) {
  // TODO: Add your specialized code here and/or call the base class
  if (main_doc)
    if (main_doc->GetPathName() == lpszFileName)
      if (Mine_changed) {
        //	we are trying to revert to on-disk level, so we should prompt the user if he wants
        //	this, and then if so to close the current document
        if (AfxMessageBox("This will discard all changes made to the level.\nDo you want to continue?", MB_YESNO) ==
            IDYES) {
          mprintf(0, "Restoring %s...\n", lpszFileName);
          main_doc->OnOpenDocument(lpszFileName);
        }
      }

  return CWinApp::OpenDocumentFile(lpszFileName);
}

//	pause and resume

void CEditorApp::pause() {
  m_Paused = TRUE;
  ddio_KeyFlush();
  ddio_Suspend();
}

bool Stay_paused = 0;

void CEditorApp::resume() {
  if (Stay_paused)
    return;

  m_Paused = FALSE;
  ddio_Resume();
  ddio_KeyFlush();
}

///////////////////////////////////////////////////////////////////////////////
//
//	Supplementary editor functions
//
///////////////////////////////////////////////////////////////////////////////

bool FileDialog(CWnd *wnd, BOOL open, LPCTSTR filter, char *pathname, char *initialdir, int dirlen);

// Function to print to an edit box
// Parameters:	dlg - the dialog that the edit box is in
//					id - the ID of the edit box
//					fmt - printf-style text & arguments
void PrintToDlgItem(CDialog *dlg, int id, char *fmt, ...) {
  std::va_list arglist;
  char str[3000];
  int len;
  CEdit *ebox;

  va_start(arglist, fmt);
  len = std::vsnprintf(str, 3000, fmt, arglist);
  va_end(arglist);
  ASSERT(len < 3000);

  ebox = (CEdit *)dlg->GetDlgItem(id);
  if (ebox == NULL) {
    Int3();
    return;
  }
  ebox->SetWindowText(str);
}

//	A quick way to use an openfiledialog/savefiledialog.
//		wnd = parent window
//		filter = a C string containing the extensions to look for in filenames when browsing (in MFC format)
//		pathname = buffer where full pathname will be stored of file opened/saved
//		initialdir = what directory to start browsing from.  will also contain the new browsing directory if
//						 user changed directories.
//		dirlen = max length of initialdir buffer including terminating null.
bool OpenFileDialog(CWnd *wnd, LPCTSTR filter, char *pathname, char *initialdir, int dirlen) {
  return FileDialog(wnd, TRUE, filter, pathname, initialdir, dirlen);
}

bool SaveFileDialog(CWnd *wnd, LPCTSTR filter, char *pathname, char *initialdir, int dirlen) {
  return FileDialog(wnd, FALSE, filter, pathname, initialdir, dirlen);
}

bool FileDialog(CWnd *wnd, BOOL open, LPCTSTR filter, char *pathname, char *initialdir, int dirlen) {
  CFileDialog *dlg;
  char saved_path[_MAX_PATH];
  char search_path[_MAX_PATH];

  theApp.pause();

  if (open)
    dlg = new CFileDialog(TRUE, 0, 0, OFN_FILEMUSTEXIST, filter, wnd);
  else
    dlg = new CFileDialog(FALSE, 0, 0, OFN_OVERWRITEPROMPT, filter, wnd);

  //	save current directory and set new directory.
  if (initialdir) {
    ASSERT(dirlen > 0);
    ddio_GetWorkingDir(saved_path, _MAX_PATH);
    if (initialdir[0]) {
      lstrcpy(search_path, initialdir);
      dlg->m_ofn.lpstrInitialDir = search_path;
    }
  }

  if (dlg->DoModal() == IDCANCEL) {
    if (initialdir)
      ddio_SetWorkingDir(saved_path);
    theApp.resume();
    delete dlg;
    return false;
  }

  //	we have a filename now.
  lstrcpy(pathname, dlg->GetPathName());

  //	restore old current directory and save current directory into initialdir.
  if (initialdir) {
    ddio_GetWorkingDir(initialdir, dirlen);
    ddio_SetWorkingDir(saved_path);
  }

  theApp.resume();

  delete dlg;
  return true;
}

int CALC_PIXELS_WITH_ASPECTX(int pixels) {
  float scr_aspect_x = ((float)GetSystemMetrics(SM_CXSCREEN)) / ((float)EDITOR_RESOLUTION_X);
  return (int)(scr_aspect_x * (float)(pixels));
}

int CALC_PIXELS_WITH_ASPECTY(int pixels) {
  float scr_aspect_y = ((float)GetSystemMetrics(SM_CYSCREEN)) / ((float)EDITOR_RESOLUTION_Y);
  return (int)(scr_aspect_y * (float)(pixels));
}

// Move the viewer object.  This should be called whenever the viewer object is moved
void MoveViewer(vector *pos, int roomnum, matrix *orient) {
  bool was_outside = (OBJECT_OUTSIDE(Viewer_object) != 0);

  ObjSetPos(Viewer_object, pos, roomnum, orient, false);

  if (OBJECT_OUTSIDE(Viewer_object) && !was_outside)
    SetViewMode(VM_TERRAIN);

  if (!OBJECT_OUTSIDE(Viewer_object) && was_outside)
    SetViewMode(VM_MINE);
}
