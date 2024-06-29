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

 * $Logfile: /DescentIII/Main/misc/error.cpp $
 * $Revision: 26 $
 * $Date: 10/09/01 5:40p $
 * $Author: Matt $
 *
 * Error-handling functions
 *
 * $Log: /DescentIII/Main/misc/error.cpp $
 *
 * 26    10/09/01 5:40p Matt
 * Made -nocrashbox work in release build.
 *
 * 25    9/15/01 1:46p Kevin
 * Added -nocrashbox to suppress crash dialog box
 *
 * 24    4/19/00 5:23p Matt
 * From Duane for 1.4
 * Changed to Mac error exit message
 *
 * 23    5/05/99 5:22p Samir
 * exit(0) instead of exit(1) and other stuff to see why error isn't
 * exiting in release?
 *
 * 22    4/14/99 1:35a Jeff
 * fixed case mismatched #includes
 *
 * 21    4/01/99 4:50p Matt
 * Took out Warning() function, chaning those calls to mprintf()
 *
 * 20    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 19    2/15/99 1:22p Kevin
 * Changes for GameGauge
 *
 * 18    1/10/99 6:47a Jeff
 * Changes made to get linux version to compile
 *
 * 17    11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 16    10/18/98 8:52p Matt
 * Revamped debug/error system.
 *
 */

#include <cstdarg>
#include <cstdio>

#include <stdlib.h>
#include <string.h>

#include "mono.h"
#include "pserror.h"
#include "debug.h"
#include "application.h"

#define MAX_MSG_LEN 2000

void Default_dbgbrk_callback();

//	Debug break chain handlers
void (*DebugBreak_callback_stop)() = NULL;
void (*DebugBreak_callback_resume)() = NULL;

//	library initialized flag
static bool Error_initialized = false;

//	message that is printed out when error occurs
static char Exit_message[MAX_MSG_LEN];
static char App_title[32];
static char Exit_title_str[64];

//	error message output function
void error_Spew();

//////////////////////////////////////////////////////////////////////////////

//	initializes error handler.
bool error_Init(bool debugger, bool mono_debug, const char *app_title) {
  Debug_Init(debugger, mono_debug);

  Error_initialized = true;
  Exit_message[0] = 0;

  strncpy(App_title, app_title, sizeof(App_title) - 1);
  App_title[sizeof(App_title) - 1] = 0;

  strncpy(Exit_title_str, app_title, sizeof(Exit_title_str) - 1);
  Exit_title_str[sizeof(Exit_title_str) - 1] = 0;

  atexit(error_Spew);

  return true;
}

int no_debug_dialog = 0;

//	exits the application and prints out a standard error message
void Error(const char *fmt, ...) {
  std::va_list arglist;
  int exit_msg_len;

  strcpy(Exit_message, "Error: ");

  va_start(arglist, fmt);
  exit_msg_len = strlen(Exit_message);
  std::vsnprintf(Exit_message + exit_msg_len, MAX_MSG_LEN - exit_msg_len, fmt, arglist);
  va_end(arglist);

  snprintf(Exit_title_str, sizeof(Exit_title_str), "%s Error", App_title);
  mprintf(0, "%s\n", Exit_message);

#ifdef _DEBUG
  int answer;

  if (DebugBreak_callback_stop)
    (*DebugBreak_callback_stop)();

  if (Debug_break)
    answer = Debug_ErrorBox(OSMBOX_ABORTRETRYIGNORE, Exit_title_str, Exit_message, "Press RETRY to debug.");
  else if (!no_debug_dialog)
    answer = Debug_ErrorBox(OSMBOX_OKCANCEL, Exit_title_str, Exit_message,
                            "Press OK to exit, CANCEL to ignore this error and continue.");

  if (no_debug_dialog)
    answer = IDOK;

  switch (answer) {
  case IDRETRY:
    debug_break(); // Step Out of this function to see where Error() was called
    // fall into ignore/cancel case
  case IDIGNORE:
  case IDCANCEL:
    if (DebugBreak_callback_resume)
      (*DebugBreak_callback_resume)();
    return;
  case IDOK:
  case IDABORT:
    break; // do nothing, and exit below
  }

  // Clear the message, since we don't need to see it again when we exit
  Exit_message[0] = 0;

#else
  if (!Error_initialized)
    error_Spew();
#endif

  // Clear the DEBUG_BREAK() callbacks
  SetDebugBreakHandlers(NULL, NULL);

  // Leave the program
  exit(0);
}

// Brings up an error message for an int3
void Int3MessageBox(const char *file, int line) {
#ifndef RELEASE
  char title[128], message[500];
  int answer;

  snprintf(title, sizeof(title), "%s Debug Break", App_title);
  snprintf(message, sizeof(message), "Int3 in %s at line %d.", file, line);

  if (DebugBreak_callback_stop)
    (*DebugBreak_callback_stop)();

  answer = Debug_ErrorBox(OSMBOX_YESNO, title, message, "It's probably safe to continue.  Continue?");

  if (answer == IDNO) {
    SetDebugBreakHandlers(NULL, NULL);
    exit(1);
  }

  if (DebugBreak_callback_resume)
    (*DebugBreak_callback_resume)();
#endif
}

//	prints out an assertion error
void AssertionFailed(const char *expstr, const char *file, int line) {
#ifndef RELEASE
  char title[128], message[500];
  int answer;

  snprintf(title, sizeof(title), "%s Assertion Failed", App_title);
  snprintf(message, sizeof(message), "Assertion failed: (%s)\n\nFile %s at line %d.", expstr, file, line);

  if (DebugBreak_callback_stop)
    (*DebugBreak_callback_stop)();

  answer = Debug_ErrorBox(OSMBOX_YESNO, title, message, "Continue?");

  if (answer == IDNO) {
    SetDebugBreakHandlers(NULL, NULL);
    exit(1);
  }

  if (DebugBreak_callback_resume)
    (*DebugBreak_callback_resume)();
#endif // #ifndef RELEASE
}

//	error message output function
void error_Spew() {
  if (Exit_message[0] && !no_debug_dialog)
    Debug_MessageBox(OSMBOX_OK, Exit_title_str, Exit_message);
}

//////////////////////////////////////////////////////////////////////////////
//	MESSAGE BOX SYSTEM

char Messagebox_title[80] = "Message";

// Sets the title for future OutrageMessageBox() dialogs
void SetMessageBoxTitle(const char *title) { strncpy(Messagebox_title, title, sizeof(Messagebox_title)); }

#define BUF_LEN 1024

// Pops up a dialog box to display a message
void OutrageMessageBox(const char *str, ...) {
  char buf[BUF_LEN];
  std::va_list arglist;
  int nchars;

  va_start(arglist, str);
  nchars = std::vsnprintf(buf, BUF_LEN, str, arglist);
  va_end(arglist);

  if (nchars >= BUF_LEN)
    Debug_MessageBox(OSMBOX_OK, Messagebox_title,
                     "The dialog that follows this one overflowed its text buffer.  The program may crash.");

  Debug_MessageBox(OSMBOX_OK, Messagebox_title, buf);
}

int OutrageMessageBox(int type, const char *str, ...) {
  char buf[BUF_LEN];
  std::va_list arglist;
  int os_flags = 0;
  int nchars;

  va_start(arglist, str);
  nchars = std::vsnprintf(buf, BUF_LEN, str, arglist);
  va_end(arglist);

  if (type == MBOX_OK)
    os_flags = OSMBOX_OK;
  else if (type == MBOX_YESNO)
    os_flags = OSMBOX_YESNO;
  else if (type == MBOX_YESNOCANCEL)
    os_flags = OSMBOX_YESNOCANCEL;
  else if (type == MBOX_ABORTRETRYIGNORE)
    os_flags = OSMBOX_ABORTRETRYIGNORE;
  else
    Int3();

  if (nchars >= BUF_LEN)
    Debug_MessageBox(OSMBOX_OK, Messagebox_title,
                     "The dialog that follows this one overflowed its text buffer.  The program may crash.");

  return Debug_MessageBox(os_flags, Messagebox_title, buf);
}