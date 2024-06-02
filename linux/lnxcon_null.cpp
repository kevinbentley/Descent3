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

 * $Logfile: /DescentIII/Main/linux/lnxcon_null.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2000/04/18 00:00:39 $
 * $Author: icculus $
 *
 * <insert description of file here>
 *
 * $Log: lnxcon_null.cpp,v $
 * Revision 1.1.1.1  2000/04/18 00:00:39  icculus
 * initial checkin
 *
 *
 * 1     4/22/99 2:04a Jeff
 *
 * 4     4/19/99 4:52p Jeff
 * removed useless calls to curses lib for keyboard setup
 *
 * 3     4/19/99 3:58a Jeff
 * got console working again (keyboard based off ddio)
 *
 * 2     4/14/99 1:59a Jeff
 * fixed case mismatched #includes
 *
 * 1     1/12/99 3:42a Jeff
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstring>
#include <cstdio>

#include "mono.h"


// put some data up on the screen
void con_null_Puts(int window, const char *str);

void con_null_Printf(const char *fmt, ...) {
  char buffer[1024];
  va_list args;
  va_start(args, fmt);
  std::vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  con_null_Puts(0, buffer);
}

bool con_null_Input(char *buf, int buflen) { return false; }

void con_null_Defer(void) {}

bool con_null_Create(void) {
  printf("Descent 3 Dedicated Server\n");
  printf("Running in quiet mode.\n");
  printf("To Administer, you must telnet in to the dedicated server.\n");
  return true;
}

void con_null_Destroy(void) {}

// put some data up on the screen
void con_null_Puts(int window, const char *str) { mprintf(0, str); }
