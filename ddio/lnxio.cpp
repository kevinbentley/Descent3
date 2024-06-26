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

 * $Logfile: /DescentIII/Main/ddio_lnx/lnxio.cpp $
 * $Revision: 1.6 $
 * $Date: 2004/02/25 00:04:06 $
 * $Author: ryan $
 *
 * Linux IO routines
 *
 * $Log: lnxio.cpp,v $
 * Revision 1.6  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.5  2000/05/29 05:20:13  icculus
 * Removed a real repetitive mprintf().
 *
 * Revision 1.4  2000/05/29 05:19:17  icculus
 * Serial behaviour is now correct (and the Rock'n'Ride works!). A
 * little more debugging code was added.
 *
 * Revision 1.3  2000/04/25 06:10:27  icculus
 * Added buttloads of debug information, and fixed some more glitches.
 *
 * Revision 1.2  2000/04/24 03:18:53  icculus
 * Serial port i/o code written, so I can ROCK'n'RIDE it!
 *
 * Revision 1.1.1.1  2000/04/18 00:00:33  icculus
 * initial checkin
 *
 *
 * 5     7/14/99 9:06p Jeff
 * added comment header
 *
 * $NoKeywords: $
 */

// ----------------------------------------------------------------------------
// Linux IO System Main Library Interface
// ----------------------------------------------------------------------------

#include <cstdarg>
#include <cstdio>

#ifdef MACOSX
#include <mach-o/dyld.h>
#endif

#ifdef WIN32
#include <windows.h>
#endif

#include "application.h"
#include "ddio.h"
#include "pserror.h"

bool DDIO_init = false;
oeLnxApplication *Lnx_app_obj = NULL;

// ----------------------------------------------------------------------------
//	Initialization and destruction functions
// ----------------------------------------------------------------------------

bool ddio_InternalInit(ddio_init_info *init_info) {
  mprintf(0, "DDIO: ddio_InternalInit() called.");
  Lnx_app_obj = (oeLnxApplication *)init_info->obj;
  DDIO_init = true;
  return true;
}

void ddio_InternalClose() {
  mprintf(0, "DDIO: ddio_InternalClose() called.");

  if (DDIO_init) {
    DDIO_init = false;
    Lnx_app_obj = NULL;
  } // if

  mprintf(0, "DDIO: ddio_InternalClose() returning.");
}

void ddio_DebugMessage(unsigned err, char *fmt, ...) {
  char buf[128];
  va_list arglist;

  va_start(arglist, fmt);
  std::vsnprintf(buf, sizeof(buf), fmt, arglist);
  va_end(arglist);

  mprintf(0, "%s\n", buf);
}

bool ddio_GetBinaryPath(char *exec_path, size_t len) {
#ifdef MACOSX
  if (exec_path == NULL || len == 0) {
   fprintf(stderr, "Invalid arguments\n");
   return false;
  }

  uint32_t size = (uint32_t)len;
  if (_NSGetExecutablePath(exec_path, &size) != 0) {
   fprintf(stderr, "Buffer too small; need size %u\n", size);
   return false;
  }
#elif defined(__LINUX__)
  if (realpath("/proc/self/exe", exec_path) == NULL) {
   perror("realpath");
   return false;
  }
#else
  if (GetModuleFileName(NULL, exec_path, len) == 0) {
  DWORD error = GetLastError();
  Error("GetModuleFileName failed!");
  return false;
  }
  exec_path[len - 1] = '\0';
  return true;

#endif
 exec_path[len - 1] = '\0';
 return true;
}
