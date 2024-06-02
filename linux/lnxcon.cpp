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
#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>

#include "lnxapp.h"
#include "appconsole.h"
#include <unistd.h>

#include "linux/dyna_curses.h"

//////////////////////////////////////////////////
// Defines
#define CON_MAX_STRINGLEN 768

#define CON_MAINWND 0x01
#define CON_INPUTWND 0x02

enum { Console_normal, Console_null, Console_raw } Console_mode;

////////////////////////////////////////////////
// NULL driver functions
void con_null_Printf(const char *fmt, ...);
bool con_null_Input(char *buf, int buflen);
void con_null_Defer(void);
bool con_null_Create(void);
void con_null_Destroy(void);
void con_null_Puts(int window, const char *str);

////////////////////////////////////////////////
// raw driver functions
void con_raw_Printf(const char *fmt, ...);
bool con_raw_Input(char *buf, int buflen);
void con_raw_Defer(void);
bool con_raw_Create(void);
void con_raw_Destroy(void);
void con_raw_Puts(int window, const char *str);

//////////////////////////////////////////////////
// Global Variables
char *Con_read_buf = NULL;                 // The next buffer of text from user input
char *Con_inp_buf = NULL, Con_inp_pos = 0; // Currently updating input buffer of text (and it's position)
char Con_last_command[CON_MAX_STRINGLEN];  // The last command entered by the user
int Con_cols = 0, Con_rows = 0;            // The size of the main window (input window is (1 row, Con_cols))
bool Con_newline = false;
bool Con_init = false;                                      // Console has been initialized
WINDOW *Con_main_wnd_ptr = NULL, *Con_input_wnd_ptr = NULL; // Window handles for the subwindows

#ifdef mem_malloc
#undef mem_malloc
#endif
#ifdef mem_free
#undef mem_free
#endif
#define mem_malloc(x) malloc(x)
#define mem_free(x) free(x)

//////////////////////////////////////////////////
// Prototypes
void con_Update(int windows); // Refreshes a window
void con_Defer(void);         // Performs the actions for the frame
void con_DoKeyboard(void);    // Handles any keyboard input
void con_Puts(int window, const char *str);
//////////////////////////////////////////////////
// Functions
void con_Update(int windows) {
  if (!Con_init) // console hasn't been initialized yet, int16_t circuit
    return;

  if (Console_mode == Console_null || Console_mode == Console_raw) {
    return;
  }

  if (windows & CON_MAINWND) // update the main window
    wnoutrefresh(Con_main_wnd_ptr);
  if (windows & CON_INPUTWND) { // update the input data window
    // clear the line
    wclear(Con_input_wnd_ptr);

    mvwprintw(Con_input_wnd_ptr, 0, 0, "%s", Con_inp_buf);
    touchwin(Con_input_wnd_ptr);
    wnoutrefresh(Con_input_wnd_ptr);
    leaveok(Con_input_wnd_ptr, false);
  }
  // update the screen
  doupdate();

  int len = strlen(Con_inp_buf);
  mvwin(Con_input_wnd_ptr, Con_rows, len);
  move(Con_rows, len);
}

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

  switch (Console_mode) {
  case Console_null:
    con_null_Puts(0, filter_buf);
    break;
  case Console_raw:
    con_raw_Puts(0, filter_buf);
    break;
  case Console_normal:
    con_Puts(CON_MAINWND, filter_buf);
    break;
  default:
    break;
  }
}

bool con_Input(char *buf, int buflen) {
  if (!Con_init) { // the console hasn't been initialized yet
    *buf = '\0';
    return false;
  }

  if (Console_mode == Console_null) {
    *buf = '\0';
    return false;
  }

  if (Console_mode == Console_raw) {
    return con_raw_Input(buf, buflen);
  }

  if (!Con_read_buf) { // there is no read buffer...yipes
    *buf = '\0';
    return false;
  }

  if (Con_read_buf[0]) {
    // we have a new buffer of input...send it away
    strncpy(buf, Con_read_buf, buflen - 1);
    buf[buflen - 1] = 0;
    Con_read_buf[0] = 0;
    return true;
  }

  return false;
}

void con_Defer(void) {
  if (!Con_init) // the console hasn't been initialized yet
  {
    return;
  }

  if (Console_mode == Console_null) {
    con_null_Defer();
    return;
  }

  if (Console_mode == Console_raw) {
    con_raw_Defer();
    return;
  }

  // handle any keyboard input
  con_DoKeyboard();
}

bool con_Create(int flags) {
  // determine what type of console to open up
  if (flags & APPFLAG_USESERVICE) {
    // use the NULL driver!
    Console_mode = Console_null;
  } else {
    if (flags & APPFLAG_USESVGA) {
      // use the regular ncurses driver
      Console_mode = Console_normal;
    } else {
      // use stdout driver
      Console_mode = Console_raw;
    }
  }

  if (Console_mode == Console_null) {
    Con_init = con_null_Create();
    return Con_init;
  }

  if (Console_mode == Console_raw) {
    Con_init = con_raw_Create();
    return Con_init;
  }

  if (!LoadCursesLib(true)) {
    fprintf(stderr, "LoadLib: Unable to load ncurses lib\n");
    exit(-1);
  } else {
    fprintf(stderr, "LoadLib: Loaded ncurses lib\n");
  }

  // start up the curses library
  initscr();

  Con_cols = COLS;
  Con_rows = LINES - 1; // one less, since the bottom window takes up one row

  // create the sub windows
  Con_main_wnd_ptr = newwin(Con_rows, Con_cols, 0, 0);
  Con_input_wnd_ptr = newwin(1, Con_cols, Con_rows, 0);

  if (!Con_main_wnd_ptr || !Con_input_wnd_ptr) {
    // error creating subdirectories.
    return false;
  }

  // clear the subwindows to make them nice
  wclear(Con_main_wnd_ptr);
  wclear(Con_input_wnd_ptr);
  wrefresh(Con_main_wnd_ptr);
  wrefresh(Con_input_wnd_ptr);
  scrollok(Con_main_wnd_ptr, true);
  leaveok(Con_input_wnd_ptr, true);
  leaveok(Con_main_wnd_ptr, true);

  // allocate any memory needed for buffers
  Con_inp_buf = (char *)mem_malloc(sizeof(char) * (Con_cols + 4));
  Con_read_buf = (char *)mem_malloc(sizeof(char) * (Con_cols + 4));
  if (!Con_inp_buf || !Con_read_buf) {
    // error allocating memory
    return false;
  }
  memset(Con_inp_buf, 0, sizeof(char) * (Con_cols + 4));
  memset(Con_read_buf, 0, sizeof(char) * (Con_cols + 4));
  Con_last_command[0] = '\0';

  // setup the keyboard for use
  //! crmode();
  //! keypad(stdscr,TRUE);
  //! noecho();
  //! cbreak();
  // nodelay(stdscr,true);

  Con_inp_pos = 0;
  Con_init = true;

  move(0, 0);
  con_Update(CON_INPUTWND);
  con_Update(CON_MAINWND);

  return true;
}

void con_Destroy(void) {
  if (Console_mode == Console_null) {
    con_null_Destroy();
    return;
  }
  if (Console_mode == Console_raw) {
    con_raw_Destroy();
    return;
  }

  // reset the keyboard
  //! echo();
  //! nocbreak();

  // delete the sub windows
  if (Con_main_wnd_ptr)
    delwin(Con_main_wnd_ptr);
  Con_main_wnd_ptr = NULL;
  if (Con_input_wnd_ptr)
    delwin(Con_input_wnd_ptr);
  Con_input_wnd_ptr = NULL;

  // free any allocated memory
  if (Con_inp_buf) {
    mem_free(Con_inp_buf);
    Con_inp_buf = NULL;
  }

  if (Con_read_buf) {
    mem_free(Con_read_buf);
    Con_read_buf = NULL;
  }
  Con_cols = Con_rows = 0;

  // shutdown curses
  endwin();

  LoadCursesLib(false);
}

// put some data up on the screen
void con_Puts(int window, const char *str) {
  if (Console_mode == Console_null) {
    con_null_Puts(window, str);
    return;
  }
  if (Console_mode == Console_raw) {
    con_raw_Puts(window, str);
    return;
  }

  int string_len = strlen(str);
  if (!string_len)
    return;

  if (window & CON_MAINWND) {
    // add the string to the main window
    if (Con_main_wnd_ptr) {
      wprintw(Con_main_wnd_ptr, str);
    }
  }

  if (window & CON_INPUTWND) {
    // add the string to the input window

    // fill in the buffer
    if (Con_input_wnd_ptr)
      wprintw(Con_input_wnd_ptr, str);
  }

  con_Update(window);
}

// HACK!!! this shouldn't be dependant...oh well
int ddio_KeyInKey();
int ddio_KeyToAscii(int code);

void con_DoKeyboard(void) {
  int keypressed = ddio_KeyInKey();

  while (keypressed != 0) {
    // we got a key...handle it
    switch (keypressed) {
    case 0xCB: // KEY_LEFT:       // Left arrow
      Con_inp_pos = std::max(Con_inp_pos - 1, 0);
      con_Update(CON_INPUTWND);
      break;

    case 0xCD: // KEY_RIGHT:      // Right arrow
    {
      int len = strlen(Con_inp_buf);
      Con_inp_pos = std::min(Con_inp_pos + 1, len);
      con_Update(CON_INPUTWND);
    } break;

    case 0xC8: // KEY_UP:			// Up arrow
      // Replace the current buffer that is being typed with the last completed command (if there was one)
      if (Con_last_command[0] != 0) {
        memset(Con_inp_buf, 0, Con_cols + 4);
        strcpy(Con_inp_buf, Con_last_command);

        Con_inp_pos = strlen(Con_last_command);

        con_Update(CON_INPUTWND);
      }
      break;

    case 0xD3: // KEY_DELETE:     // Delete
    {
      // Move all the characters that followed the
      // deleted character (on the same line) one
      // space back (to the left) in the matrix.
      for (int x = Con_inp_pos; x < Con_cols; x++)
        Con_inp_buf[x] = Con_inp_buf[x + 1];

      con_Update(CON_INPUTWND);
    } break;
    case 0x0E: // KEY_BACKSP:
    {
      // Move the caret back one space, and then
      // process this like the DEL key.
      if (Con_inp_pos > 0) {
        Con_inp_pos--;

        for (int x = Con_inp_pos; x < Con_cols; x++)
          Con_inp_buf[x] = Con_inp_buf[x + 1];

        con_Update(CON_INPUTWND);
      }
    } break;
    case 0x1C: // KEY_ENTER:
    {
      // Go to the beginning of the next line.
      // The bottom line wraps around to the top.
      strcpy(Con_read_buf, Con_inp_buf);
      strcat(Con_inp_buf, "\n");

      // add the string to the buffer
      con_Puts(CON_MAINWND, Con_inp_buf);

      // only save the buffer if there is text in the buffer
      char *p = Con_read_buf;
      while (*p) {
        if (isalnum(*p)) {
          strcpy(Con_last_command, Con_read_buf);
          break;
        }
        p++;
      }

      memset(Con_inp_buf, 0, Con_cols + 4);
      Con_inp_pos = 0;
      con_Update(CON_INPUTWND);
    } break;
    case 0x01: // KEY_ESC:        // Escape
    {
      memset(Con_inp_buf, 0, Con_cols + 4);
      Con_inp_pos = 0;
      con_Update(CON_INPUTWND);
    } break;
    default:
      if (Con_inp_pos < (Con_cols - 2)) {
        // Add the character to the text buffer.
        uint8_t str[2];
        str[0] = ddio_KeyToAscii(keypressed);
        str[1] = 0;
        if (str[0] != 255) {
          Con_inp_buf[Con_inp_pos] = str[0];
          Con_inp_buf[Con_inp_pos + 1] = '\0';
          con_Update(CON_INPUTWND);
          Con_inp_pos++;
        }
      }
    }

    keypressed = ddio_KeyInKey();
  }
}
