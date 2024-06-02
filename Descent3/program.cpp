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

 * $Logfile: /DescentIII/Main/program.cpp $
 * $Revision: 8 $
 * $Date: 5/13/99 3:41p $
 * $Author: Ardussi $
 *
 * program state info
 *
 * $Log: /DescentIII/Main/program.cpp $
 *
 * 8     5/13/99 3:41p Ardussi
 * changes for compiling on the Mac
 *
 * 7     4/15/99 1:42a Jeff
 * changes for linux compile
 *
 * 6     4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 5     10/18/98 9:12p Matt
 * Use new symbolic constant for the program name.
 *
 * 4     10/12/98 1:45p Samir
 * added version key to database.
 *
 * 3     10/08/98 7:30p Samir
 * changed version numbers.
 *
 * 2     10/02/98 12:30p Samir
 * added version information for beta/demo.
 *
 * 3     2/04/97 5:07p Samir
 * Added windowed state to determine if we run in a window
 *
 * 2     2/04/97 2:30p Samir
 * Changed program_state to program_version.
 *
 * 1     2/03/97 4:42p Samir
 * Program version control
 *
 * $NoKeywords: $
 */

#include "program.h"
#include "pserror.h"
#include "descent.h"

#include "appdatabase.h"
#if defined(WIN32)
#include "windatabase.h"
#elif defined(__LINUX__)
#include "lnxdatabase.h"
#endif

program_version Program_version;

//	Initializes the current program state

void ProgramVersion(int version_type, uint8_t major, uint8_t minor, uint8_t build) {
#if defined(WIN32) // I'm sorry.  Samir
  oeWin32AppDatabase dbase((oeWin32AppDatabase *)Database);
#elif defined(__LINUX__)
  oeLnxAppDatabase dbase((oeLnxAppDatabase *)Database);
#else
  oeAppDatabase dbase(Database); // this will fail without an operating system equiv
#endif

  Program_version.version_type = version_type;
  Program_version.major = major;
  Program_version.minor = minor;
  Program_version.build = build;

  PROGRAM(beta) = 0;
  PROGRAM(demo) = 0;

  if (version_type & BETA_VERSION)
    PROGRAM(beta) = 1;
  if (version_type & DEMO_VERSION)
    PROGRAM(demo) = 1;

  switch (version_type & (~0xf000)) {
  case DEVELOPMENT_VERSION:
    PROGRAM(debug) = 1;
    PROGRAM(editor) = 0;
    PROGRAM(release) = 0;
    PROGRAM(windowed) = 0;
    break;

  case RELEASE_VERSION:
    PROGRAM(debug) = 0;
    PROGRAM(editor) = 0;
    PROGRAM(release) = 0;
    PROGRAM(windowed) = 0;
    break;

  default:
    Int3(); // NO NO NO
  }

  if (dbase.lookup_record("Version")) {
    dbase.write("Major", Program_version.major);
    dbase.write("Minor", Program_version.minor);
    dbase.write("Build", Program_version.build);
  } else {
    Error("Unable to find version key for %s", PRODUCT_NAME);
  }
}
