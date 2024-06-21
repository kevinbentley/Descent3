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

 * $Logfile: /DescentIII/Main/lib/debug.h $
 * $Revision: 23 $
 * $Date: 4/19/00 5:20p $
 * $Author: Matt $
 *
 *	Debug functions
 *
 * $Log: /DescentIII/Main/lib/debug.h $
 *
 * 23    4/19/00 5:20p Matt
 * From Duane for 1.4
 * Mac debug_break changes
 *
 * 22    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 21    7/28/99 3:25p Kevin
 * Macintosh!
 *
 * 20    4/17/99 7:50p Jeff
 * kill keyboard thread before int3 in linux (else it locks up)...temp
 * hack until I replace ddio key
 *
 * 19    4/12/99 7:14p Samir
 * added multiple pages per mono window.
 *
 * 18    1/13/99 6:47a Jeff
 * fixed debug_break() for linux
 *
 * 17    1/09/99 1:11a Jeff
 * put in #ifdef around some windows specific code
 *
 * 16    1/05/99 4:28p Kevin
 * Moved exception handling code to windebug.cpp
 *
 * 15    10/18/98 8:52p Matt
 * Revamped debug/error system.
 *
 * 14    10/13/98 12:03p Kevin
 * Changed use of preprocessors for debug, etc.
 *
 * 13    10/12/98 10:20a Samir
 * added parameter to debug init.
 *
 * 12    6/23/98 2:40p Matt
 * Added Yes/No/Cancel type to OutrageMessageBox() and
 * Debug_MesssageBox(), and changed return value from a bool to an
 * integer.
 *
 * 11    5/12/98 11:45a Samir
 * added logfile.
 *
 * 10    4/08/98 7:19p Samir
 * Added runtime debugging option.
 *
 * 9     4/07/98 9:20p Samir
 * Changes to debug stuff.
 *
 * 8     4/03/98 5:15p Samir
 * Implemented simple debug message filtering.
 *
 * 7     3/20/98 2:43p Samir
 * Some better Int3 support.
 *
 * 6     3/10/98 5:16p Samir
 * Got debug callbacks working when you hit an Int3.
 *
 * 5     1/29/98 12:24p Samir
 * Added logfile support.
 *
 * 4     1/28/98 11:17a Samir
 * Added debugbreak stuff.
 *
 * 3     10/13/97 2:41p Samir
 * Debug breaks now are macros to work depending on the operating system.
 *
 * 2     9/04/97 12:00p Matt
 * Changed Debug_MessageBox() to return bool instead of int, since it was
 * already being used that way.
 *
 * 1     6/10/97 4:54p Samir
 * Took headers from gameos.h and isolated them.
 *
 * $NoKeywords: $
 */
#ifndef DEBUG_H
#define DEBUG_H

//	---------------------------------------------------------------------------
//	Debug system is a member of the 'platform' library.
//	---------------------------------------------------------------------------
//	---------------------------------------------------------------------------
//	Constants
//	---------------------------------------------------------------------------
#ifndef IDOK
#define IDOK 1
#endif
#ifndef IDCANCEL
#define IDCANCEL 2
#endif
#ifndef IDABORT
#define IDABORT 3
#endif
#ifndef IDRETRY
#define IDRETRY 4
#endif
#ifndef IDIGNORE
#define IDIGNORE 5
#endif
#ifndef IDYES
#define IDYES 6
#endif
#ifndef IDNO
#define IDNO 7
#endif
// #define DEBUG_LEVEL 0		//DAJ
#if defined(WIN32) || defined(__LINUX__) || defined(ANDROID)
constexpr const int OSMBOX_OK = 1;
constexpr const int OSMBOX_YESNO = 2;
constexpr const int OSMBOX_YESNOCANCEL = 3;
constexpr const int OSMBOX_ABORTRETRYIGNORE = 4;
constexpr const int OSMBOX_OKCANCEL = 5;
#else
#define OSMBOX_OK 1
#define OSMBOX_YESNO 2
#define OSMBOX_YESNOCANCEL 3
#define OSMBOX_ABORTRETRYIGNORE 4
#define OSMBOX_OKCANCEL 5
#endif
//	---------------------------------------------------------------------------
//	Functions
//	---------------------------------------------------------------------------
extern bool Debug_break;

// if we are running under a debugger, then pass true
bool Debug_Init(bool debugger, bool mono_debug);
// Does a messagebox with a stack dump
// Messagebox shows topstring, then stack dump, then bottomstring
// Return types are the same as the Windows return values
int Debug_ErrorBox(int type, const char *topstring, const char *title, const char *bottomstring);
// displays a message box
// Returns the same values as the Win32 MessageBox() function
int Debug_MessageBox(int type, const char *title, const char *str);

// these functions deal with debug spew support
bool Debug_Logfile(const char *filename);
void Debug_LogWrite(const char *str);
void Debug_ConsolePrintf(int n, const char *format, ...);
void Debug_ConsolePrintfAt(int n, int row, int col, const char *format, ...);

// DEBUGGING MACROS
// Break into the debugger, if this feature was enabled in Debug_init()
#if !defined(RELEASE)
#include "debugbreak.h"
#if defined(WIN32)
#elif defined(__LINUX__) || defined(ANDROID)
void ddio_InternalKeyClose();
#else
#define debug_break()
#endif
#else
#define debug_break()
#endif
#if defined(WIN32)
// We forward declare PEXCEPTION_POINTERS so that the function
// prototype doesn't needlessly require windows.h.
typedef struct _EXCEPTION_POINTERS EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
int __cdecl RecordExceptionInfo(PEXCEPTION_POINTERS data, const char *Message);
#endif
#endif
