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

 * $Logfile: /DescentIII/Main/Lib/Win/win32app.h $
 * $Revision: 15 $
 * $Date: 5/02/99 3:06p $
 * $Author: Samir $
 *
 *	Application object for Win32
 *
 * $Log: /DescentIII/Main/Lib/Win/win32app.h $
 *
 * 15    5/02/99 3:06p Samir
 * added handling for power management messages.
 *
 * 14    4/27/99 2:06p Samir
 * added function to get system info.
 *
 * 13    4/06/99 8:30p Samir
 * organized defer code so delay procedure doesn't stall on idle.
 *
 * 12    10/16/98 11:07a Samir
 * new OS version check stuff.
 *
 * 11    10/08/98 7:26p Samir
 * changed the prototype for the defer handler callback.
 *
 * 10    6/29/98 6:45p Samir
 * callback system repaired.
 *
 * 9     3/23/98 8:04p Samir
 * defer handler now returns a bool.
 *
 * 8     2/23/98 5:07p Samir
 * Modified init somewhat.
 *
 * 7     2/23/98 4:30p Samir
 * added init function to oeApplication.
 *
 * 6     11/17/97 4:57p Samir
 * Fixed up winapp data structures.
 *
 * 5     10/16/97 2:30p Samir
 * Added Idle processing.
 *
 * 4     9/16/97 1:04p Samir
 * Added delay function.
 *
 * 3     8/01/97 7:30p Samir
 * Better messaging support and NT support.
 *
 * 2     7/28/97 3:46p Samir
 * Added Topmost window optional support and NT detection.
 *
 * 2     6/11/97 2:39p Samir
 * Added destructors.
 *
 * 1     6/10/97 4:54p Samir
 * Win32 Application object conversion from old osWinObject.
 *
 * $NoKeywords: $
 */

#ifndef WIN32APP_H
#define WIN32APP_H

#include <array>
#include <cstdint>

#include "application.h"

/*	Basic Application Win32 data types, to prevent include of windows.h */
typedef uintptr_t   HWnd;
typedef uintptr_t   HInstance;
typedef uintptr_t   WParam;
typedef intptr_t    LParam;
typedef intptr_t    LResult;

//	This structure is used to retrieve and set
struct tWin32AppInfo {
  unsigned flags;                 // Application Flags
  HWnd hwnd;                      // Window Handle
  HInstance hinst;                // Window Instance
  int wnd_x, wnd_y, wnd_w, wnd_h; // Window dimensions
};

enum tWin32OS { NoWin32, Win9x, WinNT, WinCE };

/*	Win32 Application Object
                This object entails initialization and cleanup of all operating system
                elements, as well as data that libraries may need to initialize their
                systems.

        The Win32 Application object creates the application window and housekeeps
        the window and instance handle for the application.

        We also allow the option of setting these handles from outside the Application object.


tOEWin32MsgCallback:
        Callbacks return a 0 if we don't want to call the default action for the message, otherwise return 1
        Callbacks are executed in the Window's message procedure, so the calling program need not manually run
        the handler (although, I give you a function to do just that, if you can't depend on the WndProc).
        NOTE: the callbacks are executed in the window's root procedure and not in the inherited WndProc function.
        This means, that callbacks have priority over the application defined WndProc.

        General priority of message handling.
                Outrage Window Procedure:
                        takes care of window creation, destruction and system menus.
                        if message's window not registered then
                                calls Win32 Window Procedure
                        else
                                runs OEWin32MsgCallbacks for that message
                                if OEWin32MsgCallback functions return 0 then
                                        leave Outrage Window Procedure

                                calls oeWin32Application->WndProc hierarchy which
                                        optionally calls Win32 Window Procedure.
                        endif
*/

typedef int (*tOEWin32MsgCallback)(HWnd, unsigned, WParam, LParam);

class oeWin32Application : public oeApplication {
#if defined(OEAPP_INTERNAL_MODULE)
public:
#else
private:
#endif
  bool m_WasCreated; // Tells us if this app created the window handle or not.

  struct MessageFunction { // assign functions to messages.
    unsigned msg;
    tOEWin32MsgCallback fn;
  };
  std::array<MessageFunction, 64> m_MsgFn;

  bool m_NTFlag; // Are we in NT?

  void (*m_DeferFunc)(bool); // function to call when deffering to OS (OnIdle for instance)

  char m_WndName[64]; // name of window.

  static bool os_initialized; // is the OS check initialized?
  static bool first_time;     // first time init?

private:
  int defer_block(); // real defer code.

public:
  //	Creates the window handle
  oeWin32Application(const char *name, unsigned flags, HInstance hinst);

  //	Create object with a premade window handle/instance
  //	we just give it the window handle, instance handle and flags
  oeWin32Application(tWin32AppInfo *appinfo);

  virtual ~oeWin32Application();

  //	initializes the object
  virtual void init();

  //	Function to retrieve information from object through a platform defined structure.
  virtual void get_info(void *appinfo);

  virtual int flags(void) const;

  //	defer returns some flags.   essentially this function defers program control to OS.
  virtual unsigned defer();

  //	set a function to run when deferring to OS.
  virtual void set_defer_handler(void (*func)(bool));

  //	delays app for a certain amount of time
  virtual void delay(float secs);

  //	Sizes the displayable region of the app (the window)
  void set_sizepos(int x, int y, int w, int h);

  //	returns -1 if we pass to default window handler.
  virtual LResult WndProc(HWnd hwnd, unsigned msg, WParam wParam, LParam lParam);

  //	These functions allow you to add message handlers.
  bool add_handler(unsigned msg, tOEWin32MsgCallback fn);

  // These functions remove a handler
  bool remove_handler(unsigned msg, tOEWin32MsgCallback fn);

  // Run handler for message (added by add_handler)
  bool run_handler(HWnd wnd, unsigned msg, WParam wParam, LParam lParam);

  //	clears handler list
  void clear_handlers();

  //	tells us if we're in NT
  bool NT() const { return m_NTFlag; }

  // retreive full version information
  static tWin32OS version(int *major, int *minor, int *build = NULL, char *desc = NULL);

  // detect if application can handle what we want of it.
  static bool GetSystemSpecs(const char *fname);

public:
  HWnd m_hWnd; // handles created by the system
  HInstance m_hInstance;
  unsigned m_Flags;
  int m_X, m_Y, m_W, m_H; // window dimensions.

private:
  void os_init(); // initializes OS components.
};

// system mouse info.
extern int16_t w32_msewhl_delta; // value of mouse wheel delta for frame

#endif
