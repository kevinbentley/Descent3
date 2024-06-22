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

 * $Logfile: /DescentIII/Main/lib/appdatabase.h $
 * $Revision: 6 $
 * $Date: 5/13/99 5:04p $
 * $Author: Ardussi $
 *
 *	Application Database
 *
 * $Log: /DescentIII/Main/lib/appdatabase.h $
 *
 * 6     5/13/99 5:04p Ardussi
 * changes for compiling on the Mac
 *
 * 5     5/10/99 10:53p Ardussi
 * changes to compile on Mac
 *
 * 4     4/15/99 1:44a Jeff
 * changes for linux compile
 *
 * 3     7/24/97 3:06p Matt
 * Added functions to read & write bools & variable-length integers, and
 * fixed a few small bugs.
 *
 * 2     6/11/97 1:09p Samir
 * Virtual destructors.
 *
 * 1     6/10/97 4:55p Samir
 * Old osDatabase code merged into AppDatabase.
 *
 * $NoKeywords: $
 */

#ifndef APPDATABASE
#define APPDATABASE

#include "pstypes.h"

/* oeAppDatabase
        to get info about the application from a managed database (or a custom info file)
        Again, this class should be the parent of a platform specific class like osWinDatabase, for instance.
*/

class oeAppDatabase* Database();

class oeAppDatabase {
protected:
  oeAppDatabase() = default;
public:
  oeAppDatabase(oeAppDatabase&) = delete;
  virtual ~oeAppDatabase() = default;

  //	creates an empty classification or structure where you can store information
  virtual bool create_record(const char *pathname) = 0;

  //	set current database focus to a particular record
  virtual bool lookup_record(const char *pathname) = 0;

  //	read either an integer or string from the current record
  virtual bool read(const char *label, char *entry, int *entrylen) = 0;
  virtual bool read(const char *label, void *entry, int wordsize) = 0; // read an variable-sized integer
  virtual bool read(const char *label, bool *entry) = 0;

  //	write either an integer or string to a record.
  virtual bool write(const char *label, const char *entry, int entrylen) = 0;
  virtual bool write(const char *label, int entry) = 0;

  // get the current user's name.
  virtual void get_user_name(char *buffer, size_t *size) = 0;
};

// JCA: moved these from the Win32Database

// Handy macro to read an int without having to specify the wordsize
#define read_int(label, varp) read(label, varp, sizeof(*varp))

// Macro to write a string
#define write_string(label, varp) write(label, varp, strlen(varp))

#endif
