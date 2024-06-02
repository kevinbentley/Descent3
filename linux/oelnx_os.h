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

 * $Logfile: /DescentIII/Main/lib/linux/oelnx_os.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:58:13 $
 * $Author: kevinb $
 *
 *
 * $Log: oelnx_os.h,v $
 * Revision 1.1.1.1  2003/08/26 03:58:13  kevinb
 * initial 1.5 import
 *
 *
 * 1     1/07/99 11:14p Jeff
 *
 * 3     5/15/97 1:48 AM Jeremy
 * added define of ASSERT macro to call debugger function, implemented
 * more parts of osMacDatabase in header, redefined max-filename,
 * directory-name lengths to be correct size
 *
 * 2     5/9/97 7:15 PM Jeremy
 * redefinition of object database class and #defines of some constants
 * from the dos world
 *
 * 1     2/26/97 6:57 PM Jeremy
 * Mac OS Specific header/initialization/debug/database stuff
 *
 * $NoKeywords: $
 */

#ifndef OEMAC_OS_H
#define OEMAC_OS_H

#define ASSERT(x)                                                                                                      \
  do {                                                                                                                 \
    if (!(x))                                                                                                          \
      debug_break();                                                                                                   \
  } while (0)

// ANSI Headers
#include <string.h>

// Macintosh Headers
#include <Files.h>

class osMacObject : public osObject {
protected:
  virtual void os_init(void); // mac os specific initialization

public:
  osMacObject(void);
  virtual ~osMacObject(void); // mac os specific shutdown

  //	parent_os is the osObject that is the parent of this new object.
  //	info is a device dependent structure passed in using device independent parms.
  virtual void init(osObject *parent_os, void *info);
  virtual bool create(osObject *parent_os, void *info);

  //	returns a packet with a code telling us either to quit or that we are in some
  //	sort of idle state, which means we perform tasks like a game.
  virtual gameos_packet *defer(void); // defers game operation to OS.

  virtual void get_info(void *info, int size_str);
};

/* osDatabase
        to get info about the application from an OS managed database (or a custom info file)
*/

class osMacDatabase : public osDatabase {
public:
  osMacDatabase();
  virtual ~osMacDatabase();

  virtual bool init();

  //	creates an empty classification or structure where you can store information
  virtual bool create_record(const char *pathname);

  //	set current database focus to a particular record
  virtual bool lookup_record(const char *pathname);

  //	read either an integer or string from the current record
  virtual bool read(const char *label, char *entry, int *entrylen);
  virtual bool read(const char *label, int *entry);

  //	write either an integer or string to a record.
  virtual bool write(const char *label, char *entry, int entrylen);
  virtual bool write(const char *label, int *entry);

  // get the current user's name from the os
  virtual void get_user_name(char *buffer, size_t *size);

protected:
  // Additional Macintosh Functions, return true if successful
  virtual bool FillOutPrefsInfo(void);
  virtual bool InitPrefsFile(void);

  enum { kMacDatabaseResourceType = 'DatB' };
  virtual bool WriteDataToResourceFork(const char *label, void *entry, int entrylen);
  virtual bool ReadDataFromResourceFork(const char *label, void *entry, int *entrylen);

protected:
  bool mInitted;

  OSType mAppSignature;

  // Prefs information
  Str255 mPrefsFileName;
  Str255 mPrefsFolderName;
  OSType mPrefsFileType;
  FSSpec mPrefsFileSpec;
  int16_t mPrefsFileRefNum;
};

/*******************************************
 Utility functions specific to the Mac OS
*******************************************/

int stricmp(const char *s1, const char *s2);
int strnicmp(const char *s1, const char *s2, int n);

/*******************************************
 Constants/#defines functions specific to the Mac OS
*******************************************/
#define _MAX_DIR 32
#define _MAX_FNAME 32

// fakeouts from windows/intel
#define _MAX_EXT 4
#define _MAX_DRIVE 4

// Boolean values
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#endif
