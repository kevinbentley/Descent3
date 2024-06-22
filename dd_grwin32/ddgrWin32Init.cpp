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

 * $Logfile: /DescentIII/Main/ddgr_win32/ddgrWin32Init.cpp $
 * $Revision: 6 $
 * $Date: 11/01/98 1:58a $
 * $Author: Jeff $
 *
 *	DDGR v2.0 Win32 Implementation.
 *
 * $Log: /DescentIII/Main/ddgr_win32/ddgrWin32Init.cpp $
 *
 * 6     11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 5     3/18/98 8:03p Samir
 * if library aint initialized don't try to close!
 *
 * 4     12/23/97 6:16p Samir
 * Moved ddgr_Close to header.
 *
 * 3     9/12/97 4:13p Samir
 * Added some private data access functions and more DirectX
 * functionality.
 *
 * 2     6/16/97 4:46p Samir
 * OpenGL works in window too.
 *
 * 1     6/12/97 6:33p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstdio>

#include "ddgrWin32.h"
#include "ddgrWin32GDI.h"
#include "ddgrWin32DX.h"
#include "pserror.h"

#include <stdlib.h>
#include <string.h>

/*	DDGR_WIN32 Library
                v2.0			enhancements = concept of graphic subsystem when initializing.
                                                                                        removal of blting routines.
   reduced role in graphic implementation (video and bitmaps management)

                                                subsystems supported:
                                                                                        GDI32	(fullscreen/windowed)
*/
char *DDGR_subsystem_names[] = {"GDI32", // Standard Win32 GDI DIBs
                                "GDIX",  // GDI and DirectDraw for mode settings.
                                "DX",    // Direct X!
                                NULL};

int DDGR_subsystems[] = {DDGR_GDI_SUBSYSTEM, DDGR_GDIX_SUBSYSTEM, DDGR_DX_SUBSYSTEM, -1};

tDDGRInternalData DDGR_lib_data; // Library info.
// HACKS!!

static int DDGR_subsysid = 0;
static bool DDGR_fullscreen;

/*	Functions internal to the Init module
 */

/*	ddgr_Init
                app = application object.
                subsystem = subsystem name ('DirectDraw', 'GDI')
                fullscreen = whether it's full screen or windowed
*/
bool ddgr_Init(oeApplication *app, char *subsystem, bool fullscreen) {
  static bool first_time = true;
  int subsys_id;

  //	close old systems
  if (first_time) {
    atexit(ddgr_Close);
    first_time = false;
  } else if (LIB_DATA(init)) {
    ddgr_Close();
  }

  //	find subsystem id based off of subsystem requested.
  for (subsys_id = 0; DDGR_subsystems[subsys_id] != -1; subsys_id++) {
    if (strcmp(DDGR_subsystem_names[subsys_id], subsystem) == 0)
      break;
  }

  if (DDGR_subsystems[subsys_id] == -1)
    ddgr_FatalError("Subsystem %s not found during startup.", subsystem);

  LIB_DATA(subsystem) = DDGR_subsystems[subsys_id];

  //	Initialize that subsystem
  switch (DDGR_subsystems[subsys_id]) {
  case DDGR_GDI_SUBSYSTEM:
    ddgr_gdi_Init(fullscreen, false);
    break;
  case DDGR_GDIX_SUBSYSTEM:
    ddgr_gdi_Init(fullscreen, true);
    break;
  case DDGR_DX_SUBSYSTEM:
    ddgr_dx_Init();
    break;

  default:
    Int3();
  }

  LIB_DATA(init) = true;
  DDGR_subsysid = subsys_id;
  DDGR_fullscreen = fullscreen;

  return true;
}

void ddgr_Close() {
  if (!LIB_DATA(init))
    return;

  switch (LIB_DATA(subsystem)) {
  case DDGR_GDIX_SUBSYSTEM:
  case DDGR_GDI_SUBSYSTEM:
    ddgr_gdi_Close();
    break;
  case DDGR_DX_SUBSYSTEM:
    ddgr_dx_Close();
    break;
  default:
    Int3();
  }

  LIB_DATA(subsystem) = 0;
  LIB_DATA(init) = false;
}

void ddgr_GetSubsystem(char *name, bool *fullscreen) {
  strcpy(name, DDGR_subsystem_names[DDGR_subsysid]);
  *fullscreen = DDGR_fullscreen;
}

/*	DDGR Internal Error System
                This error system will display an error message when a fatal graphics problem occurs.
                To display error properly when video screen is in a special mode, we must close down all
                graphics and show this error.  We also handle multiple errors, so we keep a stack of
                error messages, and show them when we're finished.
*/

#define DDGR_MAX_ERRORS 10

static char *DDGR_error_msgs[DDGR_MAX_ERRORS];
static int DDGR_num_msgs = 0;

void ddgr_FatalError(const char *fmt, ...) {
  //	create our error list and flag a system error
  char buf[768];

  //	get subsystem name.
  int i;
  for (i = 0; DDGR_subsystems[i] != -1; i++) {
    if (DDGR_subsystems[i] == LIB_DATA(subsystem)) {
      break;
    }
  }

  //	create whole error message
  std::va_list arglist;

  va_start(arglist, fmt);
  std::vsnprintf(buf, 768, fmt, arglist);
  va_end(arglist);

  if (DDGR_subsystems[i] = !-1) {
    strcat(buf, "\n\nSubsystem:  ");
    strcat(buf, DDGR_subsystem_names[i]);
  }
  strcat(buf, "\n\nError stack:");
  for (i = 0; i < DDGR_num_msgs; i++) {
    strcat(buf, "\n");
    strcat(buf, DDGR_error_msgs[i]);
    delete[] DDGR_error_msgs[i];
  }

  Error(buf);
}

void ddgr_PushError(const char *fmt, ...) {
  std::va_list arglist;
  char buf[128];

  va_start(arglist, fmt);
  std::vsnprintf(buf, 128, fmt, arglist);
  va_end(arglist);

  DDGR_error_msgs[DDGR_num_msgs] = new char[strlen(buf) + 1];
  strcpy(DDGR_error_msgs[DDGR_num_msgs], buf);
  DDGR_num_msgs++;
}
