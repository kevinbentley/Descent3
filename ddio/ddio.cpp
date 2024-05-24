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

 * $Logfile: /DescentIII/Main/ddio_common/ddio.cpp $
 * $Revision: 18 $
 * $Date: 10/21/99 9:27p $
 * $Author: Jeff $
 *
 * Common DDIO Initialization
 *
 * $Log: /DescentIII/Main/ddio_common/ddio.cpp $
 *
 * 18    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 17    8/11/99 3:09p Samir
 * win32 as well calls ddioInternalJoyFrame.
 *
 * 16    7/28/99 5:18p Kevin
 * Mac merge fixes
 *
 * 15    7/28/99 3:33p Kevin
 * Mac!
 *
 * 14    4/22/99 1:56a Jeff
 * pass in ddio_init_info to keyboard handlers
 *
 * 13    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 12    2/21/99 6:38p Samir
 * mouse and key input better. buffered mouse.
 *
 * 11    1/25/99 6:47p Samir
 * allow slow keyboard
 *
 * 10    10/20/98 12:58a Jeff
 * added a way to force a lo-resolution timer
 *
 * 9     10/16/98 1:03p Samir
 * fixed timer issue when closing ddio, should not close timer.
 *
 * 8     6/30/98 4:20p Samir
 * added ddio_Close as standalone.   ddio_Init will no longer close
 * itself.
 *
 * 7     6/29/98 6:46p Samir
 * MouseInit no longer takes in required number of mouse buttons.
 *
 * 6     12/09/97 2:08p Samir
 * Non preemptive keyboard as of now?
 *
 * 5     10/23/97 2:58p Samir
 * Took out extranneous messages.
 *
 * 4     10/17/97 5:18p Samir
 * ddio_Init now does mouse opening and closing, where it should be.
 *
 * 3     10/17/97 5:03p Samir
 * Default to preemptive keyboard handler (not under NT).
 *
 * 2     10/16/97 2:28p Samir
 * move keyboard init into ddio_init and added preemptive select for
 * keyboard.
 *
 * 2     5/12/97 1:21p Samir
 * Commented out timer hook function calls.
 *
 * 1     5/08/97 1:54p Samir
 * Created skeletal initialization functions.
 *
 * $NoKeywords: $
 */
#include "ddio.h"
#include "descent.h"
#include "joystick.h"
#include "pserror.h"
#include <stdlib.h>
static bool DDIO_initialized = false;
// ----------------------------------------------------------------------------
//	Common initialization
// ----------------------------------------------------------------------------
//	Initializes DDIO system
bool ddio_Init(ddio_init_info *init_info) {
  static bool first_time = true;
  bool res;
  ASSERT(!DDIO_initialized);
  if (first_time) {
    atexit(ddio_Close);
  }
  mprintf(0, "DDIO system initializing...\n");
  res = ddio_InternalInit(init_info);
  if (res) {
    if (first_time) { // initialize once and only once.
      timer_Init();
    }
    if (!ddio_KeyInit(init_info))
      Error("Failed to initialize keyboard system.");
    ddio_MouseInit();
  }
  first_time = false;
  DDIO_initialized = true;
  joy_Init(init_info->joy_emulation);
  return res;
}
void ddio_Close() {
  if (DDIO_initialized) {
    joy_Close();
    ddio_MouseClose();
    ddio_KeyClose();
    ddio_InternalClose();
    mprintf(0, "DDIO system closed.\n");
    DDIO_initialized = false;
  }
}
void ddio_Suspend() {
  ddio_InternalKeySuspend();
  ddio_InternalMouseSuspend();
}
void ddio_Resume() {
  ddio_InternalKeyResume();
  ddio_InternalMouseResume();
}
// handles buffered input from devices once per frame.
void ddio_Frame() {
  ddio_InternalKeyFrame();
  ddio_InternalMouseFrame();
  ddio_InternalJoyFrame();
}

/**
 * Tries to find a relative path inside each of the starting_dirs.
 *
 * @param relative_path A relative path that we’ll hopefully find in
 *                      starting_dir. You don’t have to get the capitalization
 *                      of relative_path correct, even on macOS and Linux.
 *
 * @param starting_dirs Places to look for relative_path. The capitalization of
 *                      the starting_dirs must be correct, or else this
 *                      function will fail on case-sensitive filesystems. By
 *                      default, starting_dirs is {} which means “use
 *                      Base_directories as the starting_dirs”.
 *
 * @return An absolute path that’s inside starting_dir.
 */
std::filesystem::path ddio_FindRealPath(std::filesystem::path relative_path, std::vector<std::filesystem::path> starting_dirs) {
  ASSERT(("realative_path should be a relative path.", relative_path.is_relative()));
  if (starting_dirs.empty()) {
    starting_dirs = Base_directories;
  }

  std::filesystem::path return_value;
  for (auto starting_dir : starting_dirs) {
    ASSERT(("starting_dir should be an absolute path.", starting_dir.is_absolute()));
    return_value = ddio_FindRealPathImplementation(relative_path, starting_dir);
    ASSERT(("return_value should be an absolute path.", return_value.is_absolute()));
    if (std::filesystem::exists(return_value)) {
      return return_value;
    }
  }
  return return_value;
}
