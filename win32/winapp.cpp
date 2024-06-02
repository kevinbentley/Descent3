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

 * $Logfile: /DescentIII/Main/win32/winapp.cpp $
 * $Revision: 36 $
 * $Date: 5/20/99 9:11p $
 * $Author: Samir $
 *
 *	Win32 Application Object.  Encapsulates some app info for libraries
 *
 * $Log: /DescentIII/Main/win32/winapp.cpp $
 *
 * 36    5/20/99 9:11p Samir
 * delay function now blocks if application is idle.
 *
 * 35    5/11/99 12:43a Kevin
 * included shellapi.h for extracticon
 *
 * 34    5/10/99 11:56a Samir
 * implemented commandline for mouseman (with a fix that prevented
 * mouseman from working in game due to button enumeration errors).
 *
 * 33    5/09/99 11:05a Kevin
 * Extract icon from launcher and use that as the app icon (task bar, etc)
 *
 * 32    5/02/99 3:06p Samir
 * added handling for power management messages.
 *
 * 31    4/27/99 2:06p Samir
 * added function to get system info.
 *
 * 30    4/24/99 5:44p Samir
 * delay will sleep once to defer to OS.
 *
 * 29    4/06/99 8:30p Samir
 * organized defer code so delay procedure doesn't stall on idle.
 *
 * 28    2/09/99 1:31a Jeff
 * do call WaitMessage() while in idle loop...need to process network and
 * multiplayer during multiplayer games...WaitMessage() doesn't guarantee
 * that.
 *
 * 27    11/30/98 5:45p Samir
 * console apps don't get forced into the foreground.
 *
 * 26    10/23/98 12:36a Jeff
 * took out inline assembly check of MMX which caused some freaky
 * optimization problem which fucked up OS detection in os_init in release
 * builds.
 *
 * 25    10/22/98 10:45p Samir
 * blanking window in release build.
 *
 * 24    10/22/98 4:28p Samir
 * only force window into foreground if a release version.
 *
 * 23    10/21/98 11:08a Samir
 * weird cases when app is not in foreground though the application object
 * believes it is.  force into foreground.
 *
 * 22    10/16/98 5:35p Kevin
 * use WM_ACTIVATEAPP instead of WM_ACTIVATE
 *
 * 21    10/16/98 11:07a Samir
 * new OS version check stuff.
 *
 * 20    10/08/98 7:26p Samir
 * changed the prototype for the defer handler callback.
 *
 * 19    9/28/98 11:02a Kevin
 * added Networking defer, and fixed some UI issues
 *
 * 18    9/16/98 6:38p Samir
 * added minimize box
 *
 * 17    9/16/98 5:02p Samir
 * reimplemented X style console.
 *
 * 16    9/14/98 4:03p Samir
 * added console support.
 *
 * 15    6/29/98 6:45p Samir
 * fixed WinCallbacks properly.
 *
 * 14    3/23/98 8:04p Samir
 * defer handler now returns a bool.
 *
 * 13    2/26/98 1:00p Samir
 * Added application activation functions.
 *
 * 12    2/23/98 5:07p Samir
 * Modified init somewhat.
 *
 * 11    2/23/98 4:30p Samir
 * added init function to oeApplication.
 *
 * 10    1/27/98 2:59p Samir
 * Fixed some potential crashes.
 *
 * 9     12/03/97 7:37p Samir
 * Added some system key support to MainWndProc.
 *
 * 8     11/17/97 4:56p Samir
 * Fixed initialization of winapp data structures.
 *
 * 7     10/16/97 2:30p Samir
 * Added Idle processing.
 *
 * 6     9/16/97 1:04p Samir
 * Added delay function.
 *
 * 5     8/26/97 12:32p Samir
 * Fixed F10 problem (having to do with system menu).  This should be an
 * option per application instead of all applications, so I should move
 * this code somewhere else, perhaps. (WM_SYSCOMMAND)
 *
 * 4     8/01/97 7:30p Samir
 * Better messaging support and NT support.
 *
 * 3     7/28/97 3:46p Samir
 * Added Topmost window optional support and NT detection.
 *
 * 2     6/11/97 1:09p Samir
 * Fixed up window creation.
 *
 * 1     6/10/97 4:53p Samir
 * New application class.  Ported code from old osObject.
 *
 * $NoKeywords: $
 */

#define OEAPP_INTERNAL_MODULE
#include "winapp.h"

#include <cstdio>
#include <cstdlib>

#include <windows.h>
#include <shellapi.h>
#include <mmsystem.h>

#include "appconsole.h"
#include "mono.h"
#include "networking.h"


// taken from winuser.h
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x20a
#endif

/* Main Windows Procedure for this OS object
 */
const int MAX_WIN32APPS = 4;

static struct tAppNodes {
  HWND hWnd;
  oeWin32Application *app;
} Win32_AppObjects[MAX_WIN32APPS];

// system mouse info.
int16_t w32_msewhl_delta = 0; // -val = up, pos val = down, 0 = no change.
bool w32_mouseman_hack = false;
const uint32_t kWindowStyle_Windowed = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
const uint32_t kWindowStyle_FullScreen = WS_POPUP | WS_SYSMENU;
const uint32_t kWindowStyle_Console = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;

/*	Win32 Application Object
                This object entails initialization and cleanup of all operating system
                elements, as well as data that libraries may need to initialize their
                systems.

        The Win32 Application object creates the application window and housekeeps
        the window and instance handle for the application.

        We also allow the option of setting these handles from outside the Application object.
*/
extern LRESULT WINAPI MyConProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern void con_Defer();

bool oeWin32Application::os_initialized = false;
bool oeWin32Application::first_time = true;

//	this is the app's window proc.
LRESULT WINAPI MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//	Creates the window handle and instance
oeWin32Application::oeWin32Application(const char *name, unsigned flags, HInstance hinst) : oeApplication(), m_MsgFn{} {
  WNDCLASS wc;
  RECT rect;

  if (oeWin32Application::first_time) {
    int i;
    for (i = 0; i < MAX_WIN32APPS; i++) {
      Win32_AppObjects[i].hWnd = NULL;
      Win32_AppObjects[i].app = NULL;
    }
    oeWin32Application::first_time = false;
  }

  HICON dicon = ExtractIcon((HINSTANCE)hinst, "descent 3.exe", 0);
  wc.hCursor = NULL;
  wc.hIcon = dicon;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = (LPCSTR)name;
  wc.hInstance = (HINSTANCE)hinst;
  wc.style = CS_DBLCLKS;
  wc.lpfnWndProc = (flags & OEAPP_CONSOLE) ? (WNDPROC)MyConProc : (WNDPROC)(MyWndProc);
  wc.cbWndExtra = 0;
  wc.cbClsExtra = 0;

#ifdef RELEASE
  wc.hbrBackground =
      (flags & OEAPP_CONSOLE) ? (HBRUSH)GetStockObject(WHITE_BRUSH) : (HBRUSH)GetStockObject(BLACK_BRUSH);
#else
  wc.hbrBackground =
      (flags & OEAPP_CONSOLE) ? (HBRUSH)GetStockObject(WHITE_BRUSH) : (HBRUSH)GetStockObject(HOLLOW_BRUSH);
#endif

  if (!RegisterClass(&wc)) {
    mprintf(0, "Failure to register window class (err:%x).\n", GetLastError());
    return;
  }

  if (flags & OEAPP_CONSOLE) {
    m_X = CW_USEDEFAULT;
    m_Y = CW_USEDEFAULT;
    m_W = 640;
    m_H = 480;
  } else {
    //	initialize main window and display it.
#ifdef RELEASE
    SetRect(&rect, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#else
    SetRect(&rect, 0, 0, 640, 480);
#endif

    int cx = 0;
    int cy = 0;

    if (flags & OEAPP_WINDOWED) {
      // adjust the window size to take the menu into account
      uint32_t extendedStyle = (flags & OEAPP_TOPMOST) ? WS_EX_TOPMOST : 0;
      AdjustWindowRectEx(&rect, kWindowStyle_Windowed & ~WS_OVERLAPPED, FALSE, extendedStyle);
#ifdef RELEASE
      cx = CW_USEDEFAULT;
      cy = CW_USEDEFAULT;
#else
      cx = 0;
      cy = 0;
#endif
    }

    m_X = cx;
    m_Y = cy;
    m_W = rect.right - rect.left - 1;
    m_H = rect.bottom - rect.top - 1;
  }

  m_hInstance = hinst;
  m_Flags = flags;
  strcpy(m_WndName, name);

  os_init();

  m_hWnd = NULL;
  m_WasCreated = true;
  m_DeferFunc = NULL;
  w32_mouseman_hack = false;
}

//	Create object with a premade window handle/instance
oeWin32Application::oeWin32Application(tWin32AppInfo *appinfo) : oeApplication() {
  RECT rect;

  //	store handles
  m_hWnd = appinfo->hwnd;
  m_hInstance = appinfo->hinst;
  m_Flags = appinfo->flags;

  //	returns the dimensions of the window
  GetWindowRect((HWND)m_hWnd, &rect);
  appinfo->wnd_x = m_X = rect.left;
  appinfo->wnd_y = m_Y = rect.bottom;
  appinfo->wnd_w = m_W = rect.right - rect.left - 1;
  appinfo->wnd_h = m_H = rect.bottom - rect.top - 1;

  m_WasCreated = false;

  os_init();

  clear_handlers();

  m_DeferFunc = NULL;
  w32_mouseman_hack = false;
}

oeWin32Application::~oeWin32Application() {
  HWND hwnd = (HWND)m_hWnd;
  HINSTANCE hinst = (HINSTANCE)m_hInstance;
  char str[32];

  // I guess we should destroy this window, here, now.
  GetClassName(hwnd, str, sizeof(str));

  if (m_WasCreated) {
    // do this only if we created the window, not just initializing the window
    if (hwnd) {
      DestroyWindow(hwnd);
    }

    UnregisterClass(str, hinst);
  }
}

//	initializes the object
void oeWin32Application::init() {
  DWORD style, winstyle;

  if (!m_WasCreated)
    return;

  if (m_Flags & OEAPP_CONSOLE) {
    style = 0;
    winstyle = kWindowStyle_Console;
  } else {
    style = (m_Flags & OEAPP_TOPMOST) ? WS_EX_TOPMOST : 0;
    if (m_Flags & OEAPP_WINDOWED) {
      winstyle = kWindowStyle_Windowed;
    } else {
      winstyle = kWindowStyle_FullScreen;
    }
  }

  m_hWnd = (HWnd)CreateWindowEx(style, (LPCSTR)m_WndName, (LPCSTR)m_WndName, winstyle, m_X, m_Y, m_W, m_H, NULL, NULL,
                                (HINSTANCE)m_hInstance, (LPVOID)this);

  if (m_hWnd == NULL) {
    DWORD err = GetLastError();
    mprintf(0, "Failed to create game window (err: %x)\n", err);
    return;
  }

  ShowWindow((HWND)m_hWnd, SW_SHOWNORMAL);
  UpdateWindow((HWND)m_hWnd);
}

//	Function to retrieve information from object through a platform defined structure.
void oeWin32Application::get_info(void *info) {
  tWin32AppInfo *appinfo = (tWin32AppInfo *)info;

  appinfo->hwnd = m_hWnd;
  appinfo->hinst = m_hInstance;
  appinfo->flags = m_Flags;
  appinfo->wnd_x = m_X;
  appinfo->wnd_y = m_Y;
  appinfo->wnd_w = m_W;
  appinfo->wnd_h = m_H;
}

//	Function to get the flags
int oeWin32Application::flags(void) const { return m_Flags; }

void oeWin32Application::set_sizepos(int x, int y, int w, int h) {
  if (!m_hWnd)
    return;

  m_X = x;
  m_Y = y;
  m_W = w;
  m_H = h;

  MoveWindow((HWND)m_hWnd, x, y, w, h, TRUE);
}

// real defer code.
#define DEFER_PROCESS_ACTIVE 1     // process is still active
#define DEFER_PROCESS_INPUT_IDLE 2 // process input from os not pending.

int oeWin32Application::defer_block() {
  MSG msg;

  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT) {
      // QUIT APP.
      exit(1);
    } else if (msg.message == WM_MOVE) {
      mprintf(0, "move msg\n");
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    return DEFER_PROCESS_ACTIVE;
  } else {
    // IDLE PROCESSING
    if (m_DeferFunc) {
      (*m_DeferFunc)(this->active());
    }

    if (this->active()) {
#ifndef _DEBUG
      if (GetForegroundWindow() != (HWND)this->m_hWnd && !(m_Flags & OEAPP_CONSOLE)) {
        mprintf(0, "forcing this window into the foreground.\n");
        SetForegroundWindow((HWND)this->m_hWnd);
      }
#endif
      return (DEFER_PROCESS_ACTIVE + DEFER_PROCESS_INPUT_IDLE);
    } else {
      return (DEFER_PROCESS_INPUT_IDLE);
    }
  }

  DebugBreak();
  return (0);
}

//	defer returns some flags.   essentially this function defers program control to OS.
unsigned oeWin32Application::defer() {
  int result;

  con_Defer();

  // system mouse info.
  w32_msewhl_delta = 0;

  do {
    result = defer_block();
  } while ((result == DEFER_PROCESS_ACTIVE) || (result == DEFER_PROCESS_INPUT_IDLE));

  return 0;
}

//	set a function to run when deferring to OS.
void oeWin32Application::set_defer_handler(void (*func)(bool)) { m_DeferFunc = func; }

// initializes OS components.
void oeWin32Application::os_init() {
  tWin32OS os;
  int major, minor, build;

  os = oeWin32Application::version(&major, &minor, &build);

  /*	We only need to do this once */
  if (!os_initialized) {
    //	Are we NT for 95.
    if (os == NoWin32) {
      MessageBox(NULL, "This application will only run under Win32 systems.", "Outrage Error", MB_OK);
      exit(1);
    }

#ifdef _DEBUG
    if (os == Win9x) {
      mprintf(0, "Win9x system\n");
    } else if (os == WinNT) {
      mprintf(0, "WinNT %d.%d.%d system\n", major, minor, build);
    } else {
      mprintf(0, "Win32 non-standard operating system\n");
    }
#endif

    os_initialized = true;
  }

  m_NTFlag = (os == WinNT) ? true : false;
}

// retreive full version information
tWin32OS oeWin32Application::version(int *major, int *minor, int *build, char *strinfo) {
  OSVERSIONINFO osinfo;
  tWin32OS os;

  osinfo.dwOSVersionInfoSize = sizeof(osinfo);

  if (!GetVersionEx(&osinfo)) {
    return NoWin32;
  }

  switch (osinfo.dwPlatformId) {
  case VER_PLATFORM_WIN32_WINDOWS:
    os = Win9x;
    if (build) {
      *build = LOWORD(osinfo.dwBuildNumber);
    }
    break;

  case VER_PLATFORM_WIN32_NT:
    os = WinNT;
    if (build) {
      *build = osinfo.dwBuildNumber;
    }
    break;

    //@@	case VER_PLATFORM_WIN32_CE:
    //@@		os = WinCE;
    //@@		if (build) {
    //@@			*build = osinfo.dwBuildNumber;
    //@@		}
    //@@		break;

  default:
    os = NoWin32;
    if (*build) {
      *build = osinfo.dwBuildNumber;
    }
  }

  *major = (int)osinfo.dwMajorVersion;
  *minor = (int)osinfo.dwMinorVersion;

  if (strinfo) {
    strcpy(strinfo, osinfo.szCSDVersion);
  }

  return os;
}

//	This Window Procedure is called from the global WindowProc.
LResult oeWin32Application::WndProc(HWnd hwnd, unsigned msg, WParam wParam, LParam lParam) {
  switch (msg) {
  case WM_ACTIVATEAPP:
    m_AppActive = wParam ? true : false;
    //	mprintf(0, "WM_ACTIVATEAPP (%u,%l)\n", wParam, lParam);
    break;
  }

  return DefWindowProc((HWND)hwnd, (UINT)msg, (WPARAM)wParam, (LPARAM)lParam);
}

//	These functions allow you to add message handlers.
bool oeWin32Application::add_handler(unsigned msg, tOEWin32MsgCallback fn) {
  //	search for redundant callbacks.
  for (const MessageFunction &rMsgFn : m_MsgFn)
    if (rMsgFn.msg == msg && rMsgFn.fn == fn)
      return true;

  for (MessageFunction &rMsgFn : m_MsgFn) {
    if (rMsgFn.fn == nullptr) {
      rMsgFn.msg = msg;
      rMsgFn.fn = fn;
      return true;
    }
  }

  DebugBreak(); // We have reached the max number of message functions!

  return false;
}

// These functions remove a handler
bool oeWin32Application::remove_handler(unsigned msg, tOEWin32MsgCallback fn) {
  if (!fn)
    DebugBreak();

  for (MessageFunction &rMsgFn : m_MsgFn) {
    if (msg == rMsgFn.msg && rMsgFn.fn == fn) {
      rMsgFn.fn = nullptr;
      return true;
    }
  }

  return false;
}

// Run handler for message (added by add_handler)
bool oeWin32Application::run_handler(HWnd wnd, unsigned msg, WParam wParam, LParam lParam) {
  //	run user-defined message handlers
  // the guess here is that any callback that returns a 0, will not want to handle the window's WndProc function.
  for (const MessageFunction &rMsgFn : m_MsgFn)
    if (msg == rMsgFn.msg && rMsgFn.fn)
      if (!(*rMsgFn.fn)(wnd, msg, wParam, lParam))
        return false;

  return true;
}

void oeWin32Application::clear_handlers() {
  for (MessageFunction &rMsgFn : m_MsgFn)
    rMsgFn.fn = nullptr;
}

void oeWin32Application::delay(float secs) {
  int result;
  DWORD msecs = (DWORD)(secs * 1000.0);
  DWORD time_start;

  w32_msewhl_delta = 0;

  time_start = timeGetTime();
  Sleep(0);
  while (timeGetTime() < (time_start + msecs)) {
    this->defer_block();
  }

  // block if messages are still pending (for task switching too, this call will not return until messages are clear
  do {
    result = this->defer_block();
  } while (result == DEFER_PROCESS_ACTIVE || result == DEFER_PROCESS_INPUT_IDLE);
}

LRESULT WINAPI MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  int i = -1;
  bool force_default = false;

  for (i = 0; i < MAX_WIN32APPS; i++)
    if (Win32_AppObjects[i].hWnd == hWnd)
      break;

  if (i == MAX_WIN32APPS)
    i = -1;

  switch (msg) {
    LPCREATESTRUCT lpCreateStruct;
  case WM_CREATE:
    // here we store the this pointer to the app object this instance belongs to.
    lpCreateStruct = (LPCREATESTRUCT)lParam;
    for (i = 0; i < MAX_WIN32APPS; i++)
      if (Win32_AppObjects[i].hWnd == NULL)
        break;
    if (i == MAX_WIN32APPS)
      debug_break();
    Win32_AppObjects[i].hWnd = hWnd;
    Win32_AppObjects[i].app = (oeWin32Application *)lpCreateStruct->lpCreateParams;

    Win32_AppObjects[i].app->clear_handlers();

    force_default = true;
    break;

  case WM_DESTROY:
    //	get window handle and clear it.
    if (i == MAX_WIN32APPS)
      debug_break();
    Win32_AppObjects[i].hWnd = NULL;
    Win32_AppObjects[i].app = NULL;
    i = -1;
    break;

  case WM_SYSCOMMAND: {
    // bypass screen saver and system menu.
    uint32_t maskedWParam = wParam & 0xFFF0;
    if (maskedWParam == SC_SCREENSAVE || maskedWParam == SC_MONITORPOWER)
      return 0;
    if (maskedWParam == SC_KEYMENU)
      return 0;

    // handle the close button
    if (maskedWParam == SC_CLOSE) {
      exit(1);
      return 0;
    }
  } break;

  case WM_SYSKEYDOWN:
  case WM_SYSKEYUP:
    if (lParam & 0x20000000)
      return 0;
    break;

  case WM_POWERBROADCAST: // Won't allow OS to suspend operation for now.
    mprintf(0, "WM_POWERBROADCAST=%u,%d\n", wParam, lParam);
    if (wParam == PBT_APMQUERYSUSPEND) {
      return BROADCAST_QUERY_DENY;
    }
    break;

  case WM_MOUSEWHEEL:
  case 0xcc41:
    if (w32_mouseman_hack) {
      if (msg != 0xcc41) {
        w32_msewhl_delta = HIWORD(wParam);
      } else {
        w32_msewhl_delta = (int16_t)(wParam);
      }
    } else if (msg == WM_MOUSEWHEEL) {
      w32_msewhl_delta = HIWORD(wParam);
    }
    break;
  }

  oeWin32Application *winapp = Win32_AppObjects[i].app;

  //	if this window not on list, then run default window proc.
  if (i == -1 || winapp == NULL || force_default)
    return DefWindowProc(hWnd, msg, wParam, lParam);

  if (!winapp->run_handler((HWnd)hWnd, (unsigned)msg, (WParam)wParam, (LParam)lParam))
    return 0;

  // run user defined window procedure.
  return (LRESULT)winapp->WndProc((HWnd)hWnd, (unsigned)msg, (WParam)wParam, (LParam)lParam);
}

// detect if application can handle what we want of it.
bool oeWin32Application::GetSystemSpecs(const char *fname) {
  FILE *fp = fopen(fname, "wt");
  tWin32OS os;
  int maj, min, build;
  char desc[256];

  if (!fp)
    return false;

  os = oeWin32Application::version(&maj, &min, &build, desc);

  fprintf(0, "OS: %s %d.%d.%d %s\n",
          (os == Win9x)   ? "Win9x"
          : (os == WinNT) ? "WinNT"
          : (os == WinCE) ? "WinCE"
                          : "Non standard Win32",
          maj, min, build, desc);

  // get system memory info
  MEMORYSTATUS mem_stat;

  mem_stat.dwLength = sizeof(MEMORYSTATUS);
  GlobalMemoryStatus(&mem_stat);

  fprintf(fp, "Memory:\n");
  fprintf(fp, "\tLoad:\t\t\t%u\n\tTotalPhys:\t\t%u\n\tAvailPhys:\t\t%u\nPageFile:\t\t%u\n",
          (unsigned)mem_stat.dwMemoryLoad, (unsigned)mem_stat.dwTotalPhys, (unsigned)mem_stat.dwAvailPhys,
          (unsigned)mem_stat.dwTotalPageFile);
  fprintf(fp, "\tPageFileFree:\t%u\n\tVirtual:\t\t%u\n\tVirtualFree:\t%u\n", (unsigned)mem_stat.dwAvailPageFile,
          (unsigned)mem_stat.dwTotalVirtual, (unsigned)mem_stat.dwAvailVirtual);

  fclose(fp);

  return true;
}
