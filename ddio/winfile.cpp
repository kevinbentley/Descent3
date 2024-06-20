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

 * $Logfile: /DescentIII/Main/ddio_win/winfile.cpp $
 * $Revision: 27 $
 * $Date: 10/22/99 1:23p $
 * $Author: Kevin $
 *
 * File operations not covered properly in ANSI C
 *
 * $Log: /DescentIII/Main/ddio_win/winfile.cpp $
 *
 * 27    10/22/99 1:23p Kevin
 * Made ddio_GetCDDrive return null if the cd isn't found
 *
 * 26    7/12/99 6:44p Jeff
 * added directory lock file API functions
 *
 * 25    6/24/99 2:04p Kevin
 * Fixed bug with 2 CD rom drives & ddio_GetCDDrive
 *
 * 24    3/19/99 1:53p Kevin
 * Fixed a bug with ddio_GetCDDrive
 *
 * 23    2/09/99 4:46p Jeff
 * removed int3 in CopyFileTime
 *
 * 22    2/04/99 11:19a Kevin
 * Added function to find a CD drive letter based on it's volume name
 *
 * 21    12/08/98 12:17p Jeff
 * added 3 functions (similar to ddio_FindFiles) for finding directories
 * in a path
 *
 * 20    11/19/98 5:40p Kevin
 * Demo system
 *
 * 19    10/16/98 11:55a Kevin
 * Made dlls loadable in a hog
 *
 * 18    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 17    8/19/98 2:18p Jeff
 * changed ddio_CleanPath
 *
 * 16    8/16/98 2:04p Matt
 * Fixed super-stupid bug
 *
 * 15    8/15/98 3:42p Matt
 * Added new function, ddio_GetFullPath()
 *
 * 14    7/29/98 5:38p Jeff
 * added ddio functions to get parent path, and to clean a path name into
 * the real path
 *
 * 13    7/28/98 6:05p Jeff
 * added functions to get root directories (aka drives in windows/dos)
 *
 * 12    6/01/98 10:34a Matt
 * If can't copy file time, wait half a second and try again.
 *
 * 11    5/26/98 7:35p Jason
 * took out filetime int 3
 *
 * 10    4/06/98 1:24p Samir
 * support NULL arguments to ddio_SpltPath.
 *
 * 9     3/19/98 3:18p Samir
 * enforce constant char* arguments when needed.  done in CFILE and bitmap
 * libraries as well as ddio.
 *
 * 8     2/20/98 3:37p Jason
 * fixed error message to print out before subsequent file operations
 * happen
 *
 * 7     2/17/98 9:40p Jason
 * print out error number for copy file time
 *
 * 6     2/16/98 11:08a Jason
 * fixed copyfiletime bug
 *
 * 5     2/16/98 1:48a Matt
 * Added some additional error checking
 *
 * 4     9/10/97 12:06p Samir
 * FIxed FindFile functions.
 *
 * 3     8/15/97 6:31p Samir
 * Added findfile functions.
 *
 * 2     7/17/97 3:00p Jason
 * took out int3 on copy file time
 *
 * 10    6/11/97 2:39p Samir
 * Fixed bools
 *
 * 9     5/06/97 4:27p Samir
 * Added ddio_MakePath
 *
 * 8     5/06/97 12:35p Samir
 * Impllemented DirectoryExists and Save/Restore Working paths.
 *
 * 7     4/25/97 6:16p Jason
 * added ddio_Deletefile function
 *
 * 6     4/03/97 4:34p Jason
 * added CopyFileTime to the cfile, ddio libs
 *
 * 5     3/14/97 6:52p Samir
 * Fixed jeremy bugs.
 *
 * 4     3/14/97 6:53 PM Jeremy
 * added implementation of ddio_GetFileLength, ddio_SplitPath
 *
 * 3     3/14/97 6:38p Samir
 * Added ddio_FileDiff
 *
 * 2     3/13/97 11:09a Samir
 * Moved file stuff from gameos to ddio library
 *
 * 1     3/13/97 11:01a Samir
 * Moved from gameos library
 *
 * $NoKeywords: $
 */

#include "ddio.h"
#include "ddio_win.h"
#include "pserror.h"
#include "mem.h"
#include <stdarg.h>
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

//	---------------------------------------------------------------------------
//	File operations

//	creates a directory or folder on disk
bool ddio_CreateDir(const char *path) { return (CreateDirectory(path, NULL)) ? true : false; }

//	destroys a directory
bool ddio_RemoveDir(const char *path) { return (RemoveDirectory(path)) ? true : false; }

//	retrieve the current working folder where file operation will occur.
void ddio_GetWorkingDir(char *path, int len) { GetCurrentDirectory(len, path); }

bool ddio_SetWorkingDir(const char *path) { return (SetCurrentDirectory(path)) ? true : false; }

bool ddio_FileDiff(const char *path1, const char *path2) {
  struct _stat abuf, bbuf;

  if (_stat(path1, &abuf))
    Int3(); // error getting stat info

  if (_stat(path2, &bbuf))
    Int3(); // error getting stat info

  if ((abuf.st_size != bbuf.st_size) || (abuf.st_mtime != bbuf.st_mtime))
    return true;

  return false;
}

// get a file's length
int ddio_GetFileLength(FILE *filePtr) { return (filelength(fileno(filePtr))); }

// Split a pathname into its component parts
void ddio_SplitPath(const char *srcPath, char *path, char *filename, char *ext) {
  char drivename[_MAX_DRIVE], dirname[_MAX_DIR];

  _splitpath(srcPath, drivename, dirname, filename, ext);

  if (path)
    sprintf(path, "%s%s", drivename, dirname);
}

void ddio_CopyFileTime(char *destname, const char *srcname) {
  HANDLE desthandle, srchandle;
  FILETIME a, b, c;
  bool first_time = 1;

try_again:;

  desthandle = CreateFile(destname, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  srchandle = CreateFile(srcname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (desthandle == INVALID_HANDLE_VALUE || srchandle == INVALID_HANDLE_VALUE) {
    mprintf(0, "Couldn't copy file time for %s! Error=%d\n", destname, GetLastError());

    if (desthandle != INVALID_HANDLE_VALUE)
      CloseHandle(desthandle);

    if (srchandle != INVALID_HANDLE_VALUE)
      CloseHandle(srchandle);

    if (first_time) {
      first_time = 0;
      Sleep(500);
      goto try_again;
    }

    // JEFF: This Int3 has become really annoying...all we do is blow by it anyway
    // removed for sanity.
    //@@Int3();	//Let Matt know if you hit this!
    return;
  }

  GetFileTime(srchandle, &a, &b, &c);
  SetFileTime(desthandle, &a, &b, &c);

  CloseHandle(desthandle);
  CloseHandle(srchandle);
}

// deletes a file.  Returns 1 if successful, 0 on failure
int ddio_DeleteFile(const char *name) { return (DeleteFile(name)); }

// Save/Restore the current working directory

static char SavedWorkingDir[_MAX_DIR];

void ddio_SaveWorkingDir(void) { GetCurrentDirectory(_MAX_DIR, SavedWorkingDir); }

void ddio_RestoreWorkingDir(void) { SetCurrentDirectory(SavedWorkingDir); }

// 	Checks if a directory exists (returns 1 if it does, 0 if not)
//	This pathname is *RELATIVE* not fully qualified
bool ddio_DirExists(const char *path) {
  BOOL res;

  ddio_SaveWorkingDir();
  res = SetCurrentDirectory(path);
  ddio_RestoreWorkingDir();

  return (res) ? true : false;
}

// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void ddio_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...) {
  const char delimiter = '\\';
  va_list args;
  char *currentDir = NULL;
  int pathLength = 0;

  assert(newPath);
  assert(absolutePathHeader);
  assert(subDir);

  if (newPath != absolutePathHeader) {
    strcpy(newPath, absolutePathHeader);
  }

  // Add the first sub directory
  pathLength = strlen(newPath);
  if (newPath[pathLength - 1] != delimiter) {
    newPath[pathLength] = delimiter; // add the delimiter
    newPath[pathLength + 1] = 0;     // terminate the string
  }
  strcat(newPath, subDir);

  // Add the additional subdirectories
  va_start(args, subDir);
  while ((currentDir = va_arg(args, char *)) != NULL) {
    pathLength = strlen(newPath);
    if (newPath[pathLength - 1] != delimiter) {
      newPath[pathLength] = delimiter; // add the delimiter
      newPath[pathLength + 1] = 0;     // terminate the string
    }
    strcat(newPath, currentDir);
  }
  va_end(args);
}

bool ddio_GetTempFileName(const char *basedir, const char *prefix, char *filename) {

  if (!GetTempFileName(basedir, prefix, 0, filename))
    return false;
  else
    return true;
}

//	These functions allow one to find a file
//		You use FindFileStart by giving it a wildcard (like *.*, *.txt, u??.*, whatever).  It returns
//		a filename in namebuf.
//		Use FindNextFile to get the next file found with the wildcard given in FindFileStart.
//		Use FindFileClose to end your search.
static HANDLE hFindFile = INVALID_HANDLE_VALUE;
static WIN32_FIND_DATA FindFileData;

bool ddio_FindFileStart(const char *wildcard, char *namebuf) {
  if (hFindFile != INVALID_HANDLE_VALUE)
    ddio_FindFileClose();

  hFindFile = FindFirstFile(wildcard, &FindFileData);
  if (hFindFile != INVALID_HANDLE_VALUE) {
    strcpy(namebuf, FindFileData.cFileName);
    return true;
  } else {
    namebuf[0] = 0;
    return false;
  }
}

bool ddio_FindNextFile(char *namebuf) {

  if (!hFindFile)
    return false;

  if (FindNextFile(hFindFile, &FindFileData)) {
    strcpy(namebuf, FindFileData.cFileName);
    return true;
  } else {
    namebuf[0] = 0;
    return false;
  }
}

void ddio_FindFileClose() {
  if (hFindFile != INVALID_HANDLE_VALUE)
    FindClose(hFindFile);
  hFindFile = INVALID_HANDLE_VALUE;
}

//	 pass in a pathname (could be from ddio_SplitPath), root_path will have the drive name.
void ddio_GetRootFromPath(const char *srcPath, char *root_path) {
  assert(root_path);
  assert(srcPath);

  // the first char should be drive letter, second char should be a :
  if ((isalpha(srcPath[0])) && (srcPath[1] == ':')) {
    // everything is ok
    strncpy(root_path, srcPath, 2);
    root_path[2] = '\0';
  } else {
    // invalid path (no root)
    root_path[0] = '\0';
  }
}

//	retrieve root names, free up roots array (allocated with malloc) after use
int ddio_GetFileSysRoots(char **roots, int max_roots) {
  char buffer[100];

  int ret = GetLogicalDriveStrings(100, buffer);
  if (ret == 0) {
    // there was an error
    return 0;
  }

  if (ret > 100) {
    // we didn't have enough space
    return 0;
  }

  int count = 0;
  bool done = false;
  char *strptr = buffer;
  char *string;
  int strsize;
  while ((count < max_roots) && (!done)) {
    if (*strptr != 0) {
      strsize = strlen(strptr);
      string = roots[count] = (char *)mem_malloc(strsize);
      if (!string)
        break;
      // remove the trailing \ from windows
      strncpy(string, strptr, strsize - 1);
      string[strsize - 1] = '\0';

      strptr += (strsize + 1);

      count++;
    } else
      done = true;
  }
  return count;
}

//	given a path, it cleans it up (if the path is c:\windows\..\dos it would make it c:\dos)
//	srcPath is the original path
//	dest is the finished cleaned path.
//		dest should be at least _MAX_PATH in size
void ddio_CleanPath(char *dest, const char *srcPath) {
  strcpy(dest, srcPath);

  // break the path into directories
  char **directories;
  int dirs;
  int path_length;

  // make sure the path ends with a \ for sanity
  path_length = strlen(dest);

  if (dest[path_length - 1] != '\\') {
    dest[path_length] = '\\';
    dest[path_length + 1] = '\0';
    path_length++;
  }

  // now divide the full path into seperate NULL terminated strings,counting the number
  // of directories in the process
  dirs = 0;
  char *strptr = dest;
  while (*strptr != '\0') {
    if (*strptr == '\\') {
      *strptr = '\0';
      dirs++;
    }
    strptr++;
  }

  // check to make sure we have a directory, if we don't then return the original path given
  if (dirs == 0) {
    strcpy(dest, srcPath);
    return;
  }

  // allocate the memory needed for the seperate strings of each directory
  directories = (char **)mem_malloc(sizeof(char *) * dirs);
  if (!directories) {
    strcpy(dest, srcPath);
    return;
  }

  // now get all the directories, and place into the individual strings
  strptr = dest;
  int count = 0;
  while (count < dirs) {
    directories[count] = mem_strdup(strptr);
    strptr += strlen(strptr) + 1;
    count++;
  }

  // now the fun part, figure out the correct order of the directories
  int *dir_order;

  dir_order = (int *)mem_malloc(sizeof(int) * dirs);
  if (!dir_order) {
    strcpy(dest, srcPath);
    return;
  }

  for (count = 0; count < dirs; count++)
    dir_order[count] = -1; // a -1 means the end of the sequence

  // now build the order based on the indicies
  int curr_index = 0;
  for (count = 0; count < dirs; count++) {

    if (!stricmp(directories[count], "..")) {
      // we have to back up a directory
      curr_index--; // back up
      if (curr_index < 0)
        curr_index = 0;           // can't go further than root
      dir_order[curr_index] = -1; // invalidate current slot
    } else if (stricmp(directories[count], ".")) {
      // we have a normal directory, add it's index
      dir_order[curr_index] = count;
      curr_index++;
    }
  }

  // now rebuild the correct path for use, when we hit -1, we're done
  dest[0] = '\0';
  for (count = 0; count < dirs; count++) {
    if (dir_order[count] == -1)
      break;
    else {
      strcat(dest, directories[dir_order[count]]);
      strcat(dest, "\\");
    }
  }

  // now remove trailing \ char
  path_length = strlen(dest);
  if ((path_length > 0) && (dest[path_length - 1] == '\\'))
    dest[path_length - 1] = '\0';

  // free up all the allocated memory and we're done
  for (count = 0; count < dirs; count++) {
    if (directories[count])
      mem_free(directories[count]);
  }
  if (directories)
    mem_free(directories);
  if (dir_order)
    mem_free(dir_order);
}

//	given a path (with no filename), it will return the parent path
//	srcPath is the source given path
//	dest is where the parent path will be placed
//	returns true on success
//		dest should be at least _MAX_PATH in length
bool ddio_GetParentPath(char *dest, const char *srcPath) {
  assert(srcPath);
  assert(dest);

#define PARENT_DELIM ".."
  int spath_len = strlen(srcPath);
  char *temp;

  temp = (char *)mem_malloc(spath_len + strlen(PARENT_DELIM) + 3);
  if (!temp) {
    return false;
  }

  ddio_MakePath(temp, srcPath, PARENT_DELIM, NULL);
  ddio_CleanPath(dest, temp);
  mem_free(temp);
  return true;
}

// Finds a full path from a relative path
// Parameters:	full_path - filled in with the fully-specified path.  Buffer must be at least _MAX_PATH bytes long
//					rel_path - a path specification, either relative or absolute
// Returns TRUE if successful, FALSE if an error
bool ddio_GetFullPath(char *full_path, const char *rel_path) {
  char old_path[_MAX_PATH];

  ddio_GetWorkingDir(old_path, sizeof(old_path)); // save old directory

  if (!ddio_SetWorkingDir(rel_path)) // try switching to new directory
    return 0;                        // couldn't switch, so return error

  ddio_GetWorkingDir(full_path, _MAX_PATH); // get path from the OS

  ddio_SetWorkingDir(old_path); // now restore old path

  return 1;
}

// Give a volume label to look for, and if it's found returns a path
// If it isn't found, return NULL (used to return "")
const char *ddio_GetCDDrive(const char *vol) {

#define MAX_FSTYPE_LEN 30
  static char drivepath[10];
  DWORD volflags;
  int i;
  char volume[_MAX_PATH];
  char fsname[MAX_FSTYPE_LEN] = "";
  DWORD serial;
  DWORD component;

  strcpy(drivepath, "c:\\");

  for (i = 1; i <= 26; i++) {
    if (DRIVE_CDROM == GetDriveType(drivepath)) {
      // Get the drive volume name
      volume[0] = 0;
      if (!GetVolumeInformation(drivepath, volume, _MAX_PATH, &serial, &component, &volflags, fsname, MAX_FSTYPE_LEN)) {
        mprintf(0, "Call to GetVolumeInformation() failed. Last error = %d\n", GetLastError());
      }

      if (stricmp(volume, vol) == 0) {
        return drivepath;
      }
    }
    drivepath[0]++;
  }
  drivepath[0] = 0;
  return NULL; // drivepath;
}

bool ddio_CheckProcess(int pid) {
  HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
  if (proc) {
    DWORD obj_ret = WaitForSingleObject(proc, 0);
    CloseHandle(proc);
    if (obj_ret == WAIT_TIMEOUT) {
      // this process exists still
      return true;
    }
  }
  return false;
}

int ddio_GetPID() {
  return GetCurrentProcessId();
}
