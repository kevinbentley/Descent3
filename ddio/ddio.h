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

 * $Logfile: /DescentIII/Main/Lib/ddio.h $
 * $Revision: 30 $
 * $Date: 7/12/99 6:44p $
 * $Author: Jeff $
 *
 * Device Dependent IO system header
 *
 * $Log: /DescentIII/Main/Lib/ddio.h $
 *
 * 30    7/12/99 6:44p Jeff
 * added directory lock file API functions
 *
 * 29    4/24/99 5:41p Samir
 * moved key to ascii, ascii to key to the ddio_common library.
 *
 * 28    4/22/99 2:03a Jeff
 * pass ddio_init_info through to keyboard handlers
 *
 * 27    4/01/99 11:26a Samir
 * ddio_MouseGetCaps returns the button mask containing valid buttons.
 *
 * 26    3/23/99 9:05p Samir
 * implemented mouse z axis (for Win32, mouse wheel.) and added functions
 * to get binding text values.
 *
 * 25    2/21/99 6:38p Samir
 * mouse and key input better. buffered mouse.
 *
 * 24    2/16/99 5:24p Kevin
 * Converted timer to use 64bit int.
 *
 * 23    2/05/99 1:16p Samir
 * reset low level keys when flushing keyboard in the high level.  added a
 * function to the low level to reset the status of a key, called from
 * high level key flush.
 *
 * 22    2/04/99 11:19a Kevin
 * Added function to find a CD drive letter based on it's volume name
 *
 * 21    1/25/99 6:47p Samir
 * allow slow keyboard
 *
 * 20    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 19    12/08/98 12:17p Jeff
 * added 3 functions (similar to ddio_FindFiles) for finding directories
 * in a path
 *
 * 18    11/19/98 5:40p Kevin
 * Demo system
 *
 * 17    10/21/98 12:02p Samir
 * properly update odd keys when they are released throug
 * ddio_KeyGetDownTime.
 *
 * 16    10/20/98 12:58a Jeff
 * added a way to force a lo-resolution timer
 *
 * 15    10/16/98 11:55a Kevin
 * Made dlls loadable in a hog
 *
 * 14    8/19/98 2:18p Jeff
 * changed ddio_CleanPath
 *
 * 13    8/15/98 3:42p Matt
 * Added new function, ddio_GetFullPath()
 *
 * 12    7/29/98 5:38p Jeff
 * added ddio functions to get parent path, and to clean a path name into
 * the real path
 *
 * 11    7/28/98 6:05p Jeff
 * added functions to get root directories (aka drives in windows/dos)
 *
 * 10    7/28/98 5:05p Samir
 * added drive retrieval functions for Jeff.
 *
 * 9     7/01/98 4:55p Samir
 * new simplified mouse system.
 *
 * 8     6/29/98 6:46p Samir
 * MouseInit no longer takes in required number of mouse buttons.
 *
 * 7     3/19/98 3:18p Samir
 * enforce constant char* arguments when needed.  done in CFILE and bitmap
 * libraries as well as ddio.
 *
 * 6     2/25/98 6:11p Samir
 * Added functions to better deal with key flushing.
 *
 * 5     1/02/98 12:52p Samir
 * Added function to translate keycode to ascii values.
 *
 * 4     10/16/97 2:29p Samir
 * Changed DirectInput Keyboard to FOREGROUND
 *
 * 3     8/15/97 6:31p Samir
 * Added findfile functions.
 *
 * 2     7/28/97 2:54p Samir
 * Temp fix for absolute mouse position return values (Uses GetCursorPos.)
 * Added Show and Hide cursor too.
 *
 * 1     6/23/97 9:25p Samir
 * added because source safe sucks
 *
 * 26    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 25    5/12/97 1:21p Samir
 * Commented out timer hook function calls.
 *
 * 24    5/08/97 1:55p Samir
 * Moved a bunch of functions to ddio_common.h
 *
 * 23    5/06/97 4:23p Samir
 * Ha ha. Jeremy's fault....
 *
 * 22    5/6/97 4:24 PM Jeremy
 * fixed a bug in ddio_MakePath
 *
 * 21    5/6/97 3:05 PM Jeremy
 * added prototype for ddio_makepath
 *
 * 20    5/6/97 12:06 PM Jeremy
 * changed comments to reflect convention for split path to be in local
 * file system syntax
 *
 * 19    5/6/97 11:45 AM Jeremy
 * changed  split path to only look for path, filename, extension instead
 * of including directory name as well, added prototypes for save/restore
 * working dir and changed conventions for relative/absolute nature of
 * directory calls
 *
 * 18    4/25/97 6:17p Jason
 * added ddio_Deletefile function
 *
 * 17    4/16/97 11:32a Samir
 * Added z axis support.
 *
 * 16    4/03/97 4:34p Jason
 * added CopyFileTime to the cfile, ddio libs
 *
 * 15    3/20/97 11:08a Samir
 * Added function to peek for keys in queue without removing them.
 *
 * 14    3/14/97 6:54 PM Jeremy
 * added prototypes of ddio_FileDiff, ddio_GetFileLength, ddio_SplitPath
 *
 * 13    3/13/97 11:09a Samir
 * Moved file stuff from gameos to ddio library
 *
 * 12    1/30/97 6:08p Samir
 * Reflect new osObject type instead of gameos_object
 *
 * 11    1/23/97 2:23p Samir
 * Added some more keyboard constants
 *
 * 10    1/20/97 3:48p Samir
 * RCS check in
 *
 * $NoKeywords: $
 */

// ----------------------------------------------------------------------------
// Device Dependent IO System Main Library Interface - functions here are located
//	in the ddio_??? system where ??? is the os.
// ----------------------------------------------------------------------------

#ifndef DDIO_H
#define DDIO_H

#include <cstdio>
#include <cstdint>
#include <filesystem>

#include "chrono_timer.h"
#include "ddio_common.h"
#include "pstypes.h"

// ----------------------------------------------------------------------------
//	Initialization and destruction functions
// ----------------------------------------------------------------------------

//	preemptive = 1 for thread based IO.  Initializes the IO system
bool ddio_InternalInit(ddio_init_info *init_info);
void ddio_InternalClose();

// ----------------------------------------------------------------------------
//	Keyboard Interface
// ----------------------------------------------------------------------------

// used by ddio system to initialize machine specific key code.
bool ddio_InternalKeyInit(ddio_init_info *init_info);
void ddio_InternalKeyClose();

// handled internally if keyboard system needs additional processing per frame
void ddio_InternalKeyFrame();
void ddio_InternalKeySuspend();
void ddio_InternalKeyResume();

// returns if key is up or down
bool ddio_InternalKeyState(uint8_t key);

// returns internal key down time
float ddio_InternalKeyDownTime(uint8_t key);

// flush a key internally
void ddio_InternalResetKey(uint8_t key);

// ----------------------------------------------------------------------------
//	Device Dependent Timer Interface
// ----------------------------------------------------------------------------

#define timer_Init D3::ChronoTimer::Initialize
#define timer_GetTime D3::ChronoTimer::GetTime
#define timer_GetMSTime D3::ChronoTimer::GetTimeMS

// ----------------------------------------------------------------------------
//	Device Dependent Mouse Interface
// ----------------------------------------------------------------------------

#define MOUSE_LB 1 // mouse button masks
#define MOUSE_RB 2
#define MOUSE_CB 4
#define MOUSE_B4 8
#define MOUSE_B5 16
#define MOUSE_B6 32
#define MOUSE_B7 64
#define MOUSE_B8 128

#define N_MSEBTNS 8

//	initializes mouse.
bool ddio_MouseInit();
void ddio_MouseClose();

// get device caps
int ddio_MouseGetCaps(int *btn, int *axis);

// use these extensions to set exclusive or standard mouse modes
#define MOUSE_STANDARD_MODE 1  // uses absolute coordinates and simple buttons
#define MOUSE_EXCLUSIVE_MODE 2 // uses relative coordinates and advanced button information
void ddio_MouseMode(int mode);

//	resets position of mouse to center, resets virtual coord system to equal screen coordinate system
void ddio_MouseReset();

// resets mouse queue and button info only.
void ddio_MouseQueueFlush();

// handled internally if mouse system needs additional processing per frame
void ddio_InternalMouseFrame();

// used to prevent mouse input from being registered
void ddio_InternalMouseSuspend();
void ddio_InternalMouseResume();

//	returns absolute position of mouse, button state and mouse deltas.
/*	x, y = absolute mouse position
        dx, dy = mouse deltas since last call
        return value is mouse button mask.   values not needed should pass NULL pointers.
*/
int ddio_MouseGetState(int *x, int *y, int *dx, int *dy, int *z = NULL, int *dz = NULL);

// gets a mouse button event, returns false if none.
bool ddio_MouseGetEvent(int *btn, bool *state);

// returns string to binding.
const char *ddio_MouseGetBtnText(int btn);
const char *ddio_MouseGetAxisText(int axis);

// return mouse button down time.
float ddio_MouseBtnDownTime(int btn);

// return mouse button down time
int ddio_MouseBtnDownCount(int btn);

// return mouse button up count
int ddio_MouseBtnUpCount(int btn);

//	set bounds for system polling of coordinates
void ddio_MouseSetLimits(int left, int top, int right, int bottom, int zmin = 0, int zmax = 0);
void ddio_MouseGetLimits(int *left, int *top, int *right, int *bottom, int *zmin = 0, int *zmax = 0);

// virtual coordinate system for mouse (match to video resolution set for optimal mouse usage.
void ddio_MouseSetVCoords(int width, int height);

//	---------------------------------------------------------------------------
//	File Operations
//	---------------------------------------------------------------------------

// Gets the full path of the executable file
bool ddio_GetBinaryPath(char *exec_path, size_t len);

// deletes a file.  Returns 1 if successful, 0 on failure
//	This pathname is *RELATIVE* not fully qualified
int ddio_DeleteFile(const char *name);

//	retrieve the current working folder where file operation will occur.
//	Note ---> The path in Get/Set working directory is in the *LOCAL* file system's syntax
//	This pathname is relative *OR* fully qualified
void ddio_GetWorkingDir(char *path, int len);
bool ddio_SetWorkingDir(const char *path);

//  get a file length of a FILE
int ddio_GetFileLength(FILE *filePtr);

//	check if two files are different
//	This pathname is *RELATIVE* not fully qualified
bool ddio_FileDiff(const std::filesystem::path &path1, const std::filesystem::path &path2);

//	copies one files timestamp to another
void ddio_CopyFileTime(const std::filesystem::path &dest, const std::filesystem::path &src);

// Split a pathname into its component parts
//	The path in splitpath is in the *LOCAL* file system's syntax
void ddio_SplitPath(const char *srcPath, char *path, char *filename, char *ext);

//	 pass in a pathname (could be from ddio_SplitPath), root_path will have the drive name.
void ddio_GetRootFromPath(const char *srcPath, char *root_path);

//	retrieve root names, free up roots array (allocated with malloc) after use
int ddio_GetFileSysRoots(char **roots, int max_roots);

// Constructs a path in the local file system's syntax
// 	builtPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//	subdir:	the first subdirectory
//  takes a variable number of additional subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void ddio_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...);

//	These functions allow one to find a file
//		You use FindFileStart by giving it a wildcard (like *.*, *.txt, u??.*, whatever).  It returns
//		a filename in namebuf.
//		Use FindNextFile to get the next file found with the wildcard given in FindFileStart.
//		Use FindFileClose to end your search.
bool ddio_FindFileStart(const char *wildcard, char *namebuf);
bool ddio_FindNextFile(char *namebuf);
void ddio_FindFileClose();

//	given a path (with no filename), it will return the parent path
//	srcPath is the source given path
//	dest is where the parent path will be placed
//	returns true on success
//		dest should be at least _MAX_PATH in length
bool ddio_GetParentPath(char *dest, const char *srcPath);

//	given a path, it cleans it up (if the path is c:\windows\..\dos it would make it c:\dos)
//	srcPath is the original path
//	dest is the finished cleaned path.
//		dest should be at least _MAX_PATH in size
void ddio_CleanPath(char *dest, const char *srcPath);

// Finds a full path from a relative path
// Parameters:	full_path - filled in with the fully-specified path.  Buffer must be at least _MAX_PATH bytes long
//					rel_path - a path specification, either relative or absolute
// Returns TRUE if successful, FALSE if an error
bool ddio_GetFullPath(char *full_path, const char *rel_path);

// Generates a temporary filename based on the prefix, and basedir
// Parameters:
//		basedir - directory to put the files
//		prefix - prefix for the temp filename
//		filename - buffer to hold generated filename (must be at least _MAX_PATH in length)
//
// Returns TRUE if successful, FALSE if an error
bool ddio_GetTempFileName(const char *basedir, const char *prefix, char *filename);

/**
 * Check process existence by PID
 * @param pid PID of requested process
 * @return true if process exists, false otherwise
 */
bool ddio_CheckProcess(int pid);

/**
 * Get PID of current process
 * @return
 */
int ddio_GetPID();

/**
 * Creates a lock file in the specified directory. Before creation function
 * checks if lockfile already created by another process.
 * @param dir Directory for which the lock file should be created in
 * @return true if lock file successfully created, false otherwise (unable to
 * create, lock file already created by another process etc).
 */
bool ddio_CreateLockFile(const std::filesystem::path& dir);

/**
 * Deletes a lock file (for the current process) in the specified directory
 * @param dir Directory for which the lock file should be deleted from
 * @return true if lock file successfully deleted, false otherwise
 */
bool ddio_DeleteLockFile(const std::filesystem::path& dir);

#endif