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

 * $Logfile: /DescentIII/Main/lib/CFILE.H $
 * $Revision: 16 $
 * $Date: 10/18/99 1:27p $
 * $Author: Kevin $
 *
 * Functions for reading & writing files.  Includes code to read from libraries.
 *
 * $Log: /DescentIII/Main/lib/CFILE.H $
 *
 * 16    10/18/99 1:27p Kevin
 * Added cf_IsFileInHog
 *
 * 15    9/14/99 7:49p Jeff
 * added cf_OpenFileInLibrary() to force a file to be opened from a
 * specific library.  Added a way to get a crc of a file given it's CFILE
 * *.
 *
 * 14    5/20/99 5:32p Matt
 * Store a lib handle, instead of a lib pointer, in the cfile struct.
 * This will keep us from using a pointer to lib that's already been
 * closed.
 *
 * 13    3/22/99 6:26p Matt
 * Cleaned up error handling in cfile and editor level loads.
 *
 * 12    1/07/99 10:51p Jeff
 * added psglob and support to do find in files for hog files
 *
 * 11    11/16/98 3:49p Jason
 * changes for manage system
 *
 * 10    11/11/98 2:58p Jeff
 * added cf_ClearAllSearchPaths() function
 *
 * 9     10/22/98 10:48a Matt
 * Added code to keep the library file open all the time, which will
 * hopefully speed up file loads.
 *
 * 8     8/14/98 6:31p Matt
 * Changed comment
 *
 * 7     7/28/98 12:27p Kevin
 * Added CRC function
 *
 * 6     7/09/98 8:33p Samir
 * Added cf_Rewind.
 *
 * 5     3/19/98 3:18p Samir
 * enforce constant char* arguments when needed.  done in CFILE and bitmap
 * libraries as well as ddio.
 *
 * 4     2/26/98 11:01a Jason
 * added cf_ChangeFileAttributes function
 *
 * 3     2/15/98 7:44p Matt
 * Added groovy try/catch/throw error checking for cfile functions
 *
 * 2     12/17/97 4:09p Jason
 * fixed compiler warning
 *
 * 11    5/23/97 2:27p Matt
 * Text file newlines now handled internally.
 * Don't look in libs for files opened for writing.
 * Changed error message to print out errno.
 *
 * 10    4/03/97 4:34p Jason
 * added CopyFileTime to the cfile, ddio libs
 *
 * 9     3/03/97 6:21p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */

#ifndef CFILE_H
#define CFILE_H

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <vector>

#include "pstypes.h"

struct library;

// The structure for a CFILE
struct CFILE {
  char *name;          // pointer to filename
  FILE *file;          // the file itself (on disk) or the HOG
  int32_t lib_handle;  // the handle of the library, or -1
  uint32_t size;       // length of this file
  uint32_t lib_offset; // offset into HOG of start of file, or 0 if on disk
  uint32_t position;   // current position in file
  uint32_t flags;      // see values below
};

// Defines for cfile_error
enum CFileError {
  CFE_READING = 1,
  CFE_WRITING,
};

// The structure thrown by a cfile error
struct cfile_error {
  int read_write;  // reading or writing?  See defines.
  const char *msg; // the error message
  CFILE *file;     // the file that got the error
};

// Flags for CFILE struct
enum CFileFlags {
  CFF_TEXT = 1, // if this bit set, file is text
  CFF_WRITING,  // if bit set, file opened for writing
};

// return values for cfexist()
enum CFileExitStatus {
  CFES_NOT_FOUND = 0,
  CFES_ON_DISK,
  CFES_IN_LIBRARY,
};

// See if a file is in a hog
bool cf_IsFileInHog(const std::filesystem::path& filename, const std::filesystem::path& hogname);

// Opens a HOG file.  Future calls to cfopen(), etc. will look in this HOG.
// Parameters:  libname - the path & filename of the HOG file
// NOTE:	libname must be valid for the entire execution of the program.  Therefore, it should either
//			be a fully-specified path name, or the current directory must not change.
// Returns: 0 if error, else library handle that can be used to close the library
int cf_OpenLibrary(const std::filesystem::path& libname);

// Closes a library file.
// Parameters:  handle: the handle returned by cf_OpenLibrary()
void cf_CloseLibrary(int handle);

#ifdef __LINUX__
// Maps fixed case file name to actual case on disk
// Parameters:  directory: optional directory to search within (can be NULL)
//              filename: the fixed case name to map to reality
//              new_filename: buffer to store mapped name, must be at least _MAX_PATH bytes
// Returns: false if error, true if translated
bool cf_FindRealFileNameCaseInsenstive(const std::filesystem::path &directory, const std::filesystem::path &fname, char *new_filename);
#endif

/**
 * Add directory path into paths to look in for files. If ext_list is empty,
 * look in this directory for all files. Otherwise, the directory will only
 * be searched for files that match one of the listed extensions.
 * @param path directory to add; should be existing and resolvable directory.
 * @param ext_list list of extensions, which only searched on that directory.
 * @return
 * false: path is not a real directory;
 * true: path was successfully added.
 */
bool cf_SetSearchPath(const std::filesystem::path& path, const std::vector<std::filesystem::path>& ext_list = {});

// Removes all search paths that have been added by cf_SetSearchPath
void cf_ClearAllSearchPaths();

// Opens a file for reading or writing
// If a path is specified, will try to open the file only in that path.
// If no path is specified, will look through search directories and library files.
// Parameters:	filename - the name if the file, with or without a path
//					mode - the standard C mode string
// Returns:		the CFile handle, or NULL if file not opened
CFILE *cfopen(const std::filesystem::path& filename, const char *mode);

// Opens a file for reading in a library, given the library id.
// Works just like cfopen, except it assumes "rb" mode and forces the file to be
// opened from the given library.  Returns the CFILE handle or NULL if file
// couldn't be found or open.
CFILE *cf_OpenFileInLibrary(const std::filesystem::path& filename, int libhandle);

// Returns the length of the specified file
// Parameters: cfp - the file pointer returned by cfopen()
uint32_t cfilelength(CFILE *cfp);

// Closes an open CFILE.
// Parameters:  cfile - the file pointer returned by cfopen()
void cfclose(CFILE *cfp);

// Just like stdio fgetc(), except works on a CFILE
// Returns a char or EOF
int cfgetc(CFILE *cfp);

// Just like stdio fseek(), except works on a CFILE
int cfseek(CFILE *cfp, long offset, int where);

// Just like stdio ftell(), except works on a CFILE
long cftell(CFILE *cfp);

// Returns true if at EOF
int cfeof(CFILE *cfp);

// Tells if the file exists
// Returns non-zero if file exists.  Also tells if the file is on disk
//	or in a hog -  See return values in cfile.h
int cfexist(const std::filesystem::path& filename);

// Reads the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO READ STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes read.
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int cf_ReadBytes(uint8_t *buf, int count, CFILE *cfp);

// The following functions read numeric vales from a CFILE.  All values are
// stored in the file in Intel (little-endian) format.  These functions
// will convert to big-endian if required.
// These funtions will throw an exception of if the value cannot be read,
// so do not call these if you don't require the data to be present.

// Read and return an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int32_t cf_ReadInt(CFILE *cfp);

// Read and return a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int16_t cf_ReadShort(CFILE *cfp);

// Read and return a byte (8 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
int8_t cf_ReadByte(CFILE *cfp);

// Read and return a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
float cf_ReadFloat(CFILE *cfp);

// Read and return a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on read
double cf_ReadDouble(CFILE *cfp);

// Reads a string from a CFILE.  If the file is type binary, this
// function reads until a NULL or EOF is found.  If the file is text,
// the function reads until a newline or EOF is found.  The string is always
// written to the destination buffer null-terminated, without the newline.
// Parameters:  buf - where the string is written
//					n - the maximum string length, including the terminating 0
//					cfp - the CFILE pointer
// Returns the number of bytes in the string, before the terminator
// Does not generate an exception on EOF
int cf_ReadString(char *buf, size_t n, CFILE *cfp);

// Writes the specified number of bytes from a file into the buffer
// DO NOT USE THIS TO WRITE STRUCTURES.  This function is for byte
// data, such as a string or a bitmap of 8-bit pixels.
// Returns the number of bytes written.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
int cf_WriteBytes(const uint8_t *buf, int count, CFILE *cfp);

// Writes a null-terminated string to a file.  If the file is type binary,
// the string is terminated in the file with a null.  If the file is type
// text, the string is terminated with a newline.
// Parameters:	buf - pointer to the string
//					cfp = the CFILE pointer
// Returns the number of bytes written
// Throws an exception of type (cfile_error *) if the OS returns an error on write
int cf_WriteString(CFILE *cfp, const char *buf);

// Just like stdio fprintf(), except works on a CFILE
int cfprintf(CFILE *cfp, const char *format, ...);

// The following functions write numeric vales to a CFILE.  All values are
// stored to the file in Intel (little-endian) format.
// All these throw an exception if there's an error on write.

// Write an integer (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void cf_WriteInt(CFILE *cfp, int32_t i);

// Write a int16_t (16 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void cf_WriteShort(CFILE *cfp, int16_t s);

// Write a byte (8 bits).  If the byte is a newline & the file is a text file, writes a CR/LF pair.
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void cf_WriteByte(CFILE *cfp, int8_t b);

// Write a float (32 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void cf_WriteFloat(CFILE *cfp, float f);

// Write a double (64 bits)
// Throws an exception of type (cfile_error *) if the OS returns an error on write
void cf_WriteDouble(CFILE *cfp, double d);

// Copies a file.  Returns TRUE if copied ok.  Returns FALSE if error opening either file.
// Throws an exception of type (cfile_error *) if the OS returns an error on read or write
// If copytime is nonzero, copies the filetime info as well
bool cf_CopyFile(const std::filesystem::path &dest, const std::filesystem::path &src, int copytime = 0);

// Checks to see if two files are different.
// Returns TRUE if the files are different, or FALSE if they are the same.
bool cf_Diff(const std::filesystem::path &a, const std::filesystem::path &b);

// Copies the file time from one file to another
void cf_CopyFileTime(const std::filesystem::path &dest, const std::filesystem::path &src);

// Changes a files attributes (ie read/write only)
void cf_ChangeFileAttributes(const char *name, int attr);

// rewinds cfile position
void cf_Rewind(CFILE *fp);

// Calculates a 32 bit CRC
uint32_t cf_GetfileCRC(const std::filesystem::path& src);
uint32_t cf_CalculateFileCRC(CFILE *fp); // same as cf_GetfileCRC, except works with CFILE pointers

// the following cf_LibraryFind function are similar to the ddio_Find functions as they look
// for files that match the wildcard passed in, however, this is to be used for hog files.
bool cf_LibraryFindFirst(int handle, const char *wildcard, char *buffer);
bool cf_LibraryFindNext(char *buffer);
void cf_LibraryFindClose();

#endif
