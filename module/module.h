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

 * $Logfile: /DescentIII/Main/lib/module.h $
 * $Revision: 12 $
 * $Date: 7/14/99 6:43p $
 * $Author: Jeff $
 *
 * Header for Dynamic Loadable Modules
 *
 * $Log: /DescentIII/Main/lib/module.h $
 *
 * 12    7/14/99 6:43p Jeff
 * don't load modules globally by default
 *
 * 11    7/13/99 5:40p Jeff
 * fixes for Linux compile
 *
 * 10    6/25/99 4:58p Jeff
 * default module load as global
 *
 * 9     5/10/99 10:53p Ardussi
 * changes to compile on Mac
 *
 * 8     4/19/99 3:57a Jeff
 * changed define for Linux in order for multiplayer games to compile
 *
 * 7     4/15/99 2:57a Jeff
 * added missing defines for linux
 *
 * 6     1/11/99 12:53p Jeff
 * added a function that given a module name it will make sure it has an
 * extension.  Made Osiris friendly with modules with no extension
 *
 * 5     1/04/99 12:24p Jeff
 * updated...added compiler friendly define for dll functions that return
 * a pointer
 *
 * 4     11/13/98 6:36p Jeff
 * created dmfc_dll (a DLL version of DMFC) and converted current mods to
 * use it
 *
 * 3     7/06/98 10:45a Jeff
 * Made Linux friendly
 *
 * 2     6/05/98 2:15p Jeff
 * Initial creation
 *
 * 1     6/05/98 2:14p Jeff
 *
 * $NoKeywords: $
 */

#ifndef __DLMODULE_H_
#define __DLMODULE_H_

#include <cstdint>

#ifdef __cplusplus
#define CPPEXTERN extern "C"
#else
#define CPPEXTERN extern
#endif

#ifdef _MSC_VER // MSVC Build
# define STDCALL __stdcall
# define STDCALLPTR *STDCALL
#else // Non-MS compilers
# if defined(__i386__) || defined(_X86_) || defined(__THW_INTEL__)
#  define STDCALL __attribute__((stdcall))
# else
#  define STDCALL
# endif
# define STDCALLPTR STDCALL *
#endif

# define DLLFUNCCALL STDCALL
# define DLLFUNCCALLPTR STDCALLPTR

#ifdef WIN32
//=========================Windows Definition============================
#include "windows.h"

#define MODPROCADDRESS FARPROC
#define DLLFUNCEXPORT __declspec(dllexport)
#define DLLFUNCIMPORT __declspec(dllimport)
#define DLLEXPORT CPPEXTERN DLLFUNCEXPORT
struct module {
  HINSTANCE handle; // handle to the DLL
};
//=======================================================================
#elif defined(__LINUX__)
//==========================Linux Definitions============================

#define MODPROCADDRESS void *
#define DLLFUNCEXPORT __attribute__((visibility("default")))
#define DLLFUNCIMPORT
#define DLLEXPORT CPPEXTERN DLLFUNCEXPORT

struct module {
  void *handle; // handle to the DLL
};
//=======================================================================
#endif

// Mod error codes
#define MODERR_NOERROR 0       // There was no error
#define MODERR_INVALIDMOD 1    // This is not a valid module
#define MODERR_MODNOTFOUND 2   // The module couldn't be found
#define MODERR_MODINITFAIL 3   // The module initialization routine failed
#define MODERR_NOMOD 4         // The value you past in for the module isn't a module, or nothing has been loaded
#define MODERR_INVALIDHANDLE 5 // The module handle passed in is NULL
#define MODERR_OTHER 255       // Some other error occured

// Flags
#define MODF_LAZY 0x001   // Symbol resolution on demand
#define MODF_NOW 0x002    // Resolve all symbols before returning
#define MODF_GLOBAL 0x200 //

//	Returns the real name of the module.  If a given file has an extension, it will
//	just return that filename.  If the given file has no given extension, the
//	system specific extension is concatted and returned.
void mod_GetRealModuleName(const char *modfilename, char *realmodfilename);

// Loads a dynamic module into memory for use.  If no extension is given, the default
//	system specific extension is used.
// Returns true on success, false otherwise
bool mod_LoadModule(module *handle, const char *modfilename, int flags = MODF_LAZY);

// Frees a previously loaded module from memory, it can no longer be used
// Returns true on success, false otherwise
bool mod_FreeModule(module *handle);

// Returns a pointer to a function within a loaded module.  If it returns NULL there was an error.  Check
// mod_GetLastError to see if there was an error symstr is the name of the function you want to get the symbol for (Do
// NOT give any pre/suffix to this name) parmbytes is the size (in bytes) of the parameter list the function should have
MODPROCADDRESS mod_GetSymbol(module *handle, const char *symstr, uint8_t parmbytes);

// Returns an error code to what the last error was.  When this function is called the last error is cleared, so by
// calling this function it not only returns the last error, but it removes it, so if you were to call this function
// again, it would return no error
int mod_GetLastError(void);

#endif
