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

 * $Logfile: /DescentIII/Main/ddio_lnx/lnxfile.cpp $
 * $Revision: 1.5 $
 * $Date: 2004/12/05 09:02:45 $
 * $Author: ryan $
 *
 * Linux file routines
 *
 * $Log: lnxfile.cpp,v $
 * Revision 1.5  2004/12/05 09:02:45  ryan
 * Valgrind fix.
 *
 * Revision 1.4  2004/02/25 00:04:06  ryan
 * Removed loki_utils dependency and ported to MacOS X (runs, but incomplete).
 *
 * Revision 1.3  2001/01/11 11:41:57  icculus
 * Allow .dotfiles to be shown in file dialogs.
 *
 * Revision 1.2  2000/06/24 01:15:15  icculus
 * patched to compile.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:33  icculus
 * initial checkin
 *
 *
 * 13    10/02/99 2:59p Jeff
 * moved ddio_GetCDDrive to lnxcdrom.cpp
 *
 * 12    9/07/99 4:36p Jeff
 * fixed ddio_FindFileFirst/Next when a directory is returned
 *
 * 11    8/22/99 7:10p Jeff
 * fix directory lock function if the pid check returns an error, now
 * assume the pid is invalid
 *
 * 10    7/14/99 9:06p Jeff
 * added comment header
 *
 * $NoKeywords: $
 */

#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <dirent.h>
#include <fcntl.h>
#include <glob.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

#if MACOSX
#include <ctype.h>
#endif

#include "ddio.h"
#include "pserror.h"
#include "mem.h"

#define _MAX_DIR 256

//	---------------------------------------------------------------------------
//	File operations

//	retrieve the current working folder where file operation will occur.
void ddio_GetWorkingDir(char *path, int len) { getcwd(path, len); }

bool ddio_SetWorkingDir(const char *path) { return (chdir(path)) ? false : true; }

bool ddio_FileDiff(const std::filesystem::path &path1, const std::filesystem::path &path2) {
  struct stat abuf{}, bbuf{};

  if (stat(path1.u8string().c_str(), &abuf))
    Int3(); // error getting stat info

  if (stat(path2.u8string().c_str(), &bbuf))
    Int3(); // error getting stat info

  if ((abuf.st_size != bbuf.st_size) || (abuf.st_mtime != bbuf.st_mtime))
    return true;
  return false;
}

// get a file's length
int ddio_GetFileLength(FILE *filePtr) {
  int size = -1;
  if (filePtr) {
    int filedes = fileno(filePtr);
    struct stat info;

    fstat(filedes, &info);
    size = info.st_size;
  } else {
    mprintf(0, "Tried getting length of NULL fileptr!\n");
    Int3();
  }
  return size;
}

// Split a pathname into its component parts
void ddio_SplitPath(const char *srcPath, char *path, char *filename, char *ext) {
  int pathStart = -1;
  int pathEnd = -1;
  int fileStart = -1;
  int fileEnd = -1;
  int extStart = -1;
  int extEnd = -1;

  int totalLen = strlen(srcPath);

  // Check for an extension
  ///////////////////////////////////////
  int t = totalLen - 1;
  while ((srcPath[t] != '.') && (srcPath[t] != '/') && (t >= 0))
    t--;
  // see if we are at an extension
  if ((t >= 0) && (srcPath[t] == '.')) {
    // we have an extension
    extStart = t;
    extEnd = totalLen - 1;
    if (ext) {
      strncpy(ext, &(srcPath[extStart]), extEnd - extStart + 1);
      ext[extEnd - extStart + 1] = '\0';
    }
  } else {
    // no extension
    if (ext)
      ext[0] = '\0';
  }

  // Check for file name
  ////////////////////////////////////
  int temp = (extStart != -1) ? (extStart) : (totalLen - 1);
  while ((temp >= 0) && (srcPath[temp] != '/'))
    temp--;
  if (temp < 0)
    temp = 0;
  if (srcPath[temp] == '/') {
    // we have a file
    fileStart = temp + 1;
    if (extStart != -1)
      fileEnd = extStart - 1;
    else
      fileEnd = totalLen - 1;
    if (filename) {
      strncpy(filename, &(srcPath[fileStart]), fileEnd - fileStart + 1);
      filename[fileEnd - fileStart + 1] = '\0';
    }
    pathStart = 0;
    pathEnd = fileStart - 2;
    // Copy the rest into the path name
    if (path) {
      strncpy(path, &(srcPath[pathStart]), pathEnd - pathStart + 1);
      path[pathEnd - pathStart + 1] = 0;
    }
  } else {
    // only file, no path
    fileStart = 0;
    if (extStart != -1)
      fileEnd = extStart - 1;
    else
      fileEnd = totalLen - 1;

    if (filename) {
      strncpy(filename, &(srcPath[fileStart]), fileEnd - fileStart + 1);
      filename[fileEnd - fileStart + 1] = 0;
    }

    // Only file no path
    if (path) {
      path[0] = 0;
    }
  }
}

void ddio_CopyFileTime(const std::filesystem::path &dest, const std::filesystem::path &src) {
  struct stat abuf{};

  if (stat(src.u8string().c_str(), &abuf))
    Int3();

  struct utimbuf bbuf{};
  bbuf.actime = abuf.st_atime;
  bbuf.modtime = abuf.st_mtime;

  if (utime(dest.u8string().c_str(), &bbuf))
    Int3();
}

// deletes a file.  Returns 1 if successful, 0 on failure
int ddio_DeleteFile(const char *name) { return (!unlink(name)); }

// rcg06192000 extern "C" is my add, so nettest would link.
// extern "C"
//{
// Constructs a path in the local file system's syntax
// 	newPath: stores the constructed path
//  absolutePathHeader: absolute path on which the sub directories will be appended
//						(specified in local file system syntax)
//  takes a variable number of subdirectories which will be concatenated on to the path
//		the last argument in the list of sub dirs *MUST* be NULL to terminate the list
void ddio_MakePath(char *newPath, const char *absolutePathHeader, const char *subDir, ...) {
  const char delimiter = '/';
  va_list args;
  char *currentDir = NULL;
  int pathLength = 0;

  ASSERT(newPath);
  ASSERT(absolutePathHeader);
  ASSERT(subDir);

  if (newPath != absolutePathHeader) {
    strcpy(newPath, absolutePathHeader);
  }

  // Add the first sub directory
  pathLength = strlen(newPath);
  if (pathLength > 0 && newPath[pathLength - 1] != delimiter) {
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

//}

// These functions allow one to find a file
// You use FindFileStart by giving it a wildcard (like *.*, *.txt, u??.*, whatever).  It returns
// a filename in namebuf.
// Use FindNextFile to get the next file found with the wildcard given in FindFileStart.
// Use FindFileClose to end your search.
glob_t ffres = {0, NULL, 0};
int globindex = -1;
static int globerrfn(const char *path, int err) {
  mprintf(0, "Error accessing %s: %s .... \n", path, strerror(err));
  return 0;
}

#if MACOSX
int noglob_findnext(struct find_t *f);
struct find_t {
  DIR *dir;
  char pattern[_MAX_PATH];
  char name[_MAX_PATH];
};

static find_t finder;

int noglob_findfirst(char *filename, int x, struct find_t *f) {
  char *ptr;

  if (strlen(filename) >= sizeof(f->pattern))
    return (1);

  strcpy(f->pattern, filename);
  // FixFilePath(f->pattern);
  ptr = strrchr(f->pattern, '/');

  if (ptr == NULL) {
    ptr = filename;
    f->dir = opendir(".");
  } else {
    *ptr = '\0';
    f->dir = opendir(f->pattern);
    memmove(f->pattern, ptr + 1, strlen(ptr + 1) + 1);
  }

  return (noglob_findnext(f));
}

static int check_pattern_nocase(const char *x, const char *y) {
  if ((x == NULL) || (y == NULL))
    return (0); /* not a match. */

  while ((*x) && (*y)) {
    if (*x == '*') {
      x++;
      while (*y != '\0') {
        if (toupper((int)*x) == toupper((int)*y))
          break;
        y++;
      }
    }

    else if (*x == '?') {
      if (*y == '\0')
        return (0); /* anything but EOS is okay. */
    }

    else {
      if (toupper((int)*x) != toupper((int)*y))
        return (0); /* not a match. */
    }

    x++;
    y++;
  }

  return (*x == *y); /* it's a match (both should be EOS). */
}

int noglob_findnext(struct find_t *f) {
  struct dirent *dent;

  if (f->dir == NULL)
    return (1); /* no such dir or we're just done searching. */

  while ((dent = readdir(f->dir)) != NULL) {
    if (check_pattern_nocase(f->pattern, dent->d_name)) {
      if (strlen(dent->d_name) < sizeof(f->name)) {
        strcpy(f->name, dent->d_name);
        return (0); /* match. */
      }
    }
  }

  // closedir(f->dir);
  // f->dir = NULL;
  return (1); /* no match in whole directory. */
}
#endif

bool ddio_FindFileStart(const char *wildcard, char *namebuf) {
  ASSERT(wildcard);
  ASSERT(namebuf);
  if (globindex != -1)
    ddio_FindFileClose();

#if MACOSX
  if (noglob_findfirst((char *)wildcard, 0, &finder) == 0) {
    strcpy(namebuf, finder.name);
    return true;
  }
  return false;
#else
  int rc, flags;
  flags = GLOB_MARK | GLOB_TILDE;
  rc = glob(wildcard, flags, globerrfn, &ffres);
  if (rc == GLOB_NOSPACE) {
    mprintf(0, "Out of space during glob\n");
    globindex = -1;
    return false;
  }
  if (!ffres.gl_pathc) {
    globindex = -1;
    return false;
  }

  globindex = 0;

  // if the last character is a / then we are to return that last section (it is a directory and
  // ddio_splitpath can't handle that).
  int gllen = strlen(ffres.gl_pathv[0]);
  if (ffres.gl_pathv[0][gllen - 1] == '/') {
    // directory to return!
    char *ptr = &ffres.gl_pathv[0][gllen - 2];
    char *start = &ffres.gl_pathv[0][0];
    char *end = ptr;
    while (ptr >= start) {
      if (*ptr == '/') {
        // stop! it's the end of the directory
        break;
      }
      ptr--;
    }
    if (ptr < start)
      ptr = start;
    if (*ptr == '/')
      ptr++;

    start = namebuf;
    while (ptr <= end) {
      *start = *ptr;
      start++;
      ptr++;
    }
    *start = '\0';
  } else {
    // filename to return
    char ext[256];
    ddio_SplitPath(ffres.gl_pathv[0], NULL, namebuf, ext);
    strcat(namebuf, ext);
  }
  return true;
#endif
}

bool ddio_FindNextFile(char *namebuf) {
  ASSERT(namebuf);
#if MACOSX
  if (noglob_findnext(&finder) == 0) {
    strcpy(namebuf, finder.name);
    return true;
  }
  return false;
#else
  if (globindex == -1)
    return false;
  globindex++;
  if (globindex >= ffres.gl_pathc)
    return false;

  // if the last character is a / then we are to return that last section (it is a directory and
  // ddio_splitpath can't handle that).
  int gllen = strlen(ffres.gl_pathv[globindex]);
  if (ffres.gl_pathv[globindex][gllen - 1] == '/') {
    // directory to return!
    char *ptr = &ffres.gl_pathv[globindex][gllen - 2];
    char *start = &ffres.gl_pathv[globindex][0];
    char *end = ptr;
    while (ptr >= start) {
      if (*ptr == '/') {
        // stop! it's the end of the directory
        break;
      }
      ptr--;
    }
    if (ptr < start)
      ptr = start;
    if (*ptr == '/')
      ptr++;

    start = namebuf;
    while (ptr <= end) {
      *start = *ptr;
      start++;
      ptr++;
    }
    *start = '\0';
  } else {
    // filename to return
    char ext[256];
    ddio_SplitPath(ffres.gl_pathv[globindex], NULL, namebuf, ext);
    strcat(namebuf, ext);
  }

  return true;
#endif
}

void ddio_FindFileClose() {
#if MACOSX
  if (finder.dir != NULL) {
    closedir(finder.dir);
    finder.dir = NULL;
  }
#else
  if (globindex == -1)
    return;
  globindex = -1;
  globfree(&ffres);
#endif
}

//	 pass in a pathname (could be from ddio_SplitPath), root_path will have the drive name.
void ddio_GetRootFromPath(const char *srcPath, char *root_path) {
  assert(root_path);
  assert(srcPath);

  strcpy(root_path, "/");
}

//	retrieve root names, free up roots array (allocated with malloc) after use
int ddio_GetFileSysRoots(char **roots, int max_roots) {
  if (max_roots < 1)
    return 0;

  roots[0] = mem_strdup("/");
  return 1;
}

//	given a path, it cleans it up (if the path is /usr/lib/../src it would make it /usr/src)
//	srcPath is the original path
//	dest is the finished cleaned path.
//		dest should be at least _MAX_PATH in size
void ddio_CleanPath(char *dest, const char *srcPath) {
  // NOTE: we may want to use getcwd() here if we don't want symbolic links
  // but I think we do
  ////////////////////////////////////////////////////////////////////////

  strcpy(dest, srcPath);

  // break the path into directories
  char **directories;
  int dirs;
  int path_length;

  // make sure the path ends with a / for sanity
  path_length = strlen(dest);

  if (dest[path_length - 1] != '/') {
    dest[path_length] = '/';
    dest[path_length + 1] = '\0';
    path_length++;
  }

  // now divide the full path into seperate NULL terminated strings,counting the number
  // of directories in the process
  dirs = 0;
  char *strptr;
  if (dest[0] == '/')
    strptr = dest + 1; // skip first / of root dir
  else
    strptr = dest;

  while (*strptr != '\0') {
    if (*strptr == '/') {
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
      strcat(dest, "/");
    }
  }

  // now remove trailing / char
  path_length = strlen(dest);
  if ((path_length > 0) && (dest[path_length - 1] == '/'))
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

// Generates a temporary filename based on the prefix, and basedir
// Parameters:
//		basedir - directory to put the files
//		prefix - prefix for the temp filename
//		filename - buffer to hold generated filename (must be at least _MAX_PATH in length)
//
// Returns TRUE if successful, FALSE if an error
bool ddio_GetTempFileName(const char *basedir, const char *prefix, char *filename) {
  char old_workdir[_MAX_PATH];
  bool success = false;

  if (strlen(prefix) > 64)
    return false;

  ddio_GetWorkingDir(old_workdir, _MAX_PATH);

  if (!ddio_SetWorkingDir(basedir)) {
    return false; // invalid base directory
  }

  char randname[10];
  int index;
  int tries = 0;
  char rc;

  bool created = false;

  index = 0;

  while (!success && tries < 20) {
    // generate a bunch of random characters
    rc = (rand() % 128);
    if ((rc >= 'a' && rc <= 'z') || (rc >= 'A' && rc <= 'Z') || (rc >= '0' && rc <= '9')) {
      // valid character
      randname[index] = rc;
      index++;

      if (index == 10) {
        // we hit the size of our max, see if we generated a unique filename
        char t[_MAX_PATH];
        randname[9] = '\0';
        snprintf(t, sizeof(t), "%s%s.tmp", prefix, randname);

        // see if we can find this file
        FILE *fd = fopen(t, "rb");
        if (!fd) {
          // we found a good file!
          ddio_MakePath(filename, basedir, t, NULL);
          success = true;
          created = true;
        } else {
          // already taken
          fclose(fd);
          tries++;
          index = 0;
        }
      }
    } else {
      continue; // try again
    }
  }

  ddio_SetWorkingDir(old_workdir);
  return created;
}

bool ddio_CheckProcess(int pid) {
  if (kill(pid, 0) == -1) {
    if (errno != ESRCH) {
      /* some other error, log it */
      mprintf(0, "Error sending signal to PID for lock check (%d)\n", pid);
    }
    return false;
  } else {
    /* process exists */
    return true;
  }
}

int ddio_GetPID() {
  return getpid();
}
