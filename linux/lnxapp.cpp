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

 * $Logfile: /DescentIII/Main/linux/lnxapp.cpp $
 * $Revision: 1.3 $
 * $Date: 2004/02/25 00:04:06 $
 * $Author: ryan $
 *
 * Linux application routines
 *
 * $Log: lnxapp.cpp,v $
 * Revision 1.3  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.2  2000/04/28 20:18:27  icculus
 * Replaced X stuff with SDL stuff.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:39  icculus
 * initial checkin
 *
 *
 * 25    10/19/99 8:35p Jeff
 * added a couple functions for Window OpenGL
 *
 * 24    10/17/99 3:55p Jeff
 *
 * 23    10/15/99 12:14p Jeff
 * dyna load pthread library
 *
 * 22    9/24/99 8:26p Jeff
 * better cleanup (including restoring the mouse) in case of a crash or
 * error exit
 *
 * 21    9/09/99 4:35p Jeff
 * dynamically load the Outrage Xlib extension library (for DGA).  Init
 * DGA if needed for Mouse control
 *
 * 20    9/07/99 4:37p Jeff
 *
 * 19    9/06/99 9:22p Jeff
 * set initial window position to 0,0
 *
 * 18    9/05/99 9:44p Jeff
 * handle window option flag
 *
 * 17    7/15/99 11:37a Jeff
 * turn on/off autorepeat
 *
 * 16    7/14/99 9:09p Jeff
 * added comment header
 *
 * $NoKeywords: $
 */
#include "lnxapp.h"

#include <cstdlib>
#include <cctype>
#include <sys/time.h>
#include <term.h>
#include <termios.h>

#include "application.h"

#ifdef buttons // termios.h defines buttons, but SDL's headers use that symbol.
#undef buttons
#endif

static struct termios Linux_initial_terminal_settings;

oeApplication* App()
{
  static oeLnxApplication* instance = nullptr;
  if(instance == nullptr)
    instance = new oeLnxApplication();
  return instance;
}


bool con_Create(int flags);
void con_Destroy();
void con_Defer();

void Sleep(int millis) {
  struct timeval tv{};
  tv.tv_sec = 0;
  tv.tv_usec = millis * 1000;
  select(0, nullptr, nullptr, nullptr, &tv);
}

char *strupr(char *string) {
  while (string && *string) {
    *string = toupper(*string);
    string++;
  }
  return string;
}

static uint32_t LinuxAppFlags = 0;
// static Display *LinuxAppDisplay=NULL;
static bool LinuxAppSetAtExit = false;
static bool LinuxAppDontCallShutdown = false;

void LnxAppShutdown() {
  if (LinuxAppDontCallShutdown)
    return;
  LinuxAppDontCallShutdown = true;
  if (LinuxAppFlags & OEAPP_CONSOLE) {
    con_Destroy();
    tcsetattr(0, TCSANOW, &Linux_initial_terminal_settings);
  }
}

//	Creates the application object
oeLnxApplication::oeLnxApplication() {
  m_AppActive = true;

  if (!LinuxAppSetAtExit) {
    LinuxAppSetAtExit = true;
    atexit(LnxAppShutdown);
  }
}

void oeLnxApplication::setFlags(int f) {
  oeApplication::setFlags(f);

  if (f & OEAPP_CONSOLE) {
    tcgetattr(0, &Linux_initial_terminal_settings);
    con_Create(f);
  }
  LinuxAppFlags = f;
}

//	Destructor
oeLnxApplication::~oeLnxApplication() { LnxAppShutdown(); }

void oeLnxApplication::init() {
}


//	defer returns some flags.   essentially this function defers program control to OS.
unsigned oeLnxApplication::defer() {
  bool res = 0;

  if (m_DeferFunc) {
    res = 1;
    (*m_DeferFunc)(true);
  }

  con_Defer();

  return res;
}

//	set a function to run when deferring to OS.
void oeLnxApplication::set_defer_handler(void (*func)(bool)) { m_DeferFunc = func; }

//	delays app for a certain amount of time
void oeLnxApplication::delay(float secs) {
  int msecs = (int)(secs * 1000.0f);
  Sleep(msecs);
}

void oeLnxApplication::moveWindow()
{
  // unused?
  //SDL_SetWindowPosition
}

const char *oeLnxApplication::get_window_name(void) { return "Descent 3"; }

void oeLnxApplication::clear_window(void) {
}
