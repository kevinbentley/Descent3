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

 * $Logfile: /DescentIII/Main/linux/lnxcon.cpp $
 * $Revision: 1.2 $
 * $Date: 2004/02/25 00:04:06 $
 * $Author: ryan $
 *
 * <insert description of file here>
 *
 * $Log: lnxcon.cpp,v $
 * Revision 1.2  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.1.1.1  2000/04/18 00:00:39  icculus
 * initial checkin
 *
 *
 * 7     7/19/99 12:54p Jeff
 * created lnxcon_raw.cpp so ncurses is now only used for SVGALib, cuts
 * down on redraw
 *
 * 6     6/24/99 4:43p Jeff
 * removed ncurses dependency
 *
 * 5     4/22/99 2:04a Jeff
 * support for null console
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
#include <cstdio>
#include <cctype>

#include "application.h"
#include "AppConsole.h"

enum {
  Console_null,
  Console_raw,
  Console_total,
} Console_mode;

typedef bool (*Input_fp)(char *buf, int buflen);
typedef void (*Defer_fp)();
typedef bool (*Create_fp)();
typedef void (*Destroy_fp)();
typedef void (*Puts_fp)(int window, const char *str);

struct Console_Commands {
  Create_fp con_Create;
  Destroy_fp con_Destroy;
  Defer_fp con_Defer;
  Input_fp con_Input;
  Puts_fp con_Puts;
};

////////////////////////////////////////////////
// NULL driver functions
bool con_null_Input(char *buf, int buflen);
void con_null_Defer();
bool con_null_Create();
void con_null_Destroy();
void con_null_Puts(int window, const char *str);

////////////////////////////////////////////////
// raw driver functions
bool con_raw_Input(char *buf, int buflen);
void con_raw_Defer();
bool con_raw_Create();
void con_raw_Destroy();
void con_raw_Puts(int window, const char *str);

Console_Commands commands[Console_total] = {
    {
        con_null_Create,
        con_null_Destroy,
        con_null_Defer,
        con_null_Input,
        con_null_Puts,
    },
    {
        con_raw_Create,
        con_raw_Destroy,
        con_raw_Defer,
        con_raw_Input,
        con_raw_Puts,
    },
};

//////////////////////////////////////////////////
// Global Variables
bool Con_init = false; // Console has been initialized

#ifdef mem_malloc
#undef mem_malloc
#endif
#ifdef mem_free
#undef mem_free
#endif
#define mem_malloc(x) malloc(x)
#define mem_free(x) free(x)

//////////////////////////////////////////////////
// Functions

void con_Printf(const char *fmt, ...) {
  if (!Con_init) // console hasn't been initialized yet, int16_t circuit
    return;

  char buf[CON_MAX_STRINGLEN];
  va_list args;

  //	filter out messages
  va_start(args, fmt);
  std::vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);

  //	filter out unprintable characters
  char *p, *fp, filter_buf[CON_MAX_STRINGLEN];
  p = buf;
  fp = filter_buf;

  while (*p) {
    if (*p == 0x01) {
      // this is a color, skip the next 3
      p += 4;
    } else {
      if (isalnum(*p) || ispunct(*p) || (*p == ' ') || (*p == '\n') || (*p == '\r') || (*p == '\b')) {
        *fp = *p;
        fp++;
      }
      p++;
    }
  }
  *fp = '\0';

  commands[Console_mode].con_Puts(0, filter_buf);
}

bool con_Input(char *buf, int buflen) {
  if (!Con_init) { // the console hasn't been initialized yet
    *buf = '\0';
    return false;
  }
  return commands[Console_mode].con_Input(buf, buflen);
}

void con_Defer() {
  if (!Con_init) {
    // the console hasn't been initialized yet
    return;
  }
  commands[Console_mode].con_Defer();
}

bool con_Create(int flags) {
  // determine what type of console to open up
  if (flags & APPFLAG_USESERVICE) {
    // use the NULL driver!
    Console_mode = Console_null;
  } else {
    // use stdout driver
    Console_mode = Console_raw;
  }
  Con_init = commands[Console_mode].con_Create();
  return Con_init;
}

void con_Destroy() { commands[Console_mode].con_Destroy(); }
