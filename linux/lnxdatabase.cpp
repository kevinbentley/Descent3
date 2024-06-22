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

 * $Logfile: /DescentIII/Main/linux/lnxdata.cpp $
 * $Revision: 1.3 $
 * $Date: 2004/03/21 17:11:39 $
 * $Author: kevinb $
 *
 * Linux database routines
 *
 * $Log: lnxdata.cpp,v $
 * Revision 1.3  2004/03/21 17:11:39  kevinb
 * Fixes so linux will compile again. Tested with gcc-2.96
 *
 * Revision 1.2  2000/04/28 20:19:05  icculus
 * Writes "registry" to prefpath instead of current directory.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:39  icculus
 * initial checkin
 *
 *
 * 9     7/14/99 9:09p Jeff
 * added comment header
 *
 * $NoKeywords: $
 */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>

#include "appdatabase.h"
#include "lnxdatabase.h"
#include "pserror.h"
#include "mono.h"
#include "pserror.h"
#include "registry.h"
#include "loki_utils.h"

#define REGISTRY_FILENAME ".Descent3Registry"

// Construction and destruction.

oeAppDatabase* Database()
{
  static oeLnxAppDatabase* instance = nullptr;
  if(instance == nullptr)
    instance = new oeLnxAppDatabase();
  return instance;
}

oeLnxAppDatabase::oeLnxAppDatabase() {
  // Open up the database file, for reading, read in all data and keep it in memory
  // then close the database

  char *prefPath = (char *)loki_getprefpath();
  size_t fileLen = strlen(prefPath) + strlen(REGISTRY_FILENAME) + 2;
  char fileName[fileLen];
  snprintf(fileName, fileLen, "%s/%s", prefPath, REGISTRY_FILENAME);

  database = new CRegistry(fileName);
  database->Import();
  create_record("Version");
}

oeLnxAppDatabase::~oeLnxAppDatabase() {
  if (database) {
    database->Export();
    delete database;
    return;
  }

  mprintf(0, "Can't Export Database Since It's Not There!\n");
}

CRegistry *oeLnxAppDatabase::GetSystemRegistry() { return database; }

// Record functions
// these are actual folders of information

// creates an empty classification or structure where you can store information
bool oeLnxAppDatabase::create_record(const char *pathname) {
  ASSERT(pathname != NULL);
  if (database) {
    database->CreateKey((char *)pathname);
    return true;
  }
  mprintf(0, "Can't CreateKey because database NULL\n");
  return false;
}

// set current database focus to a particular record
bool oeLnxAppDatabase::lookup_record(const char *pathname) {
  ASSERT(pathname);
  if (database) {
    return database->LookupKey((char *)pathname);
  }
  mprintf(0, "Can't lookup key because database NULL\n");
  return false;
}

// read either a string from the current record
bool oeLnxAppDatabase::read(const char *label, char *entry, int *entrylen) {
  ASSERT(label);
  ASSERT(entry);
  ASSERT(entrylen);
  if (!database) {
    mprintf(0, "Can't read record because database NULL\n");
    return false;
  }

  // See if it exists
  int size = database->GetDataSize((char *)label);
  if (size > 0)
    *entrylen = size - 1; //-1 because of NULL
  else
    return false;

  // ok it exists, no look it up
  database->LookupRecord((char *)label, entry);
  return true;
}

// read a variable-sized integer from the current record
bool oeLnxAppDatabase::read(const char *label, void *entry, int wordsize) {
  ASSERT(label);
  ASSERT(entry);
  if (!database) {
    mprintf(0, "Can't read record because Database NULL\n");
    return false;
  }

  int size = database->GetDataSize((char *)label);
  if (size == 0)
    return false;

  // ok so it does exist
  int data;
  database->LookupRecord((char *)label, &data);

  switch (wordsize) {
  case 1:
    *((uint8_t *)entry) = (uint8_t)data;
    break;
  case 2:
    *((uint16_t *)entry) = (uint16_t)data;
    break;
  case 4:
    *((uint32_t *)entry) = (uint32_t)data;
    break;
  default:
    mprintf(0, "Unable to read key %s, unsupported size", label);
    return false;
    break;
  }
  return true;
}

bool oeLnxAppDatabase::read(const char *label, bool *entry) {
  bool data;
  if (!read(label, &data, sizeof(bool)))
    return false;

  *entry = (data != 0) ? true : false;
  return true;
}

// write either an integer or string to a record.
bool oeLnxAppDatabase::write(const char *label, const char *entry, int entrylen) {
  ASSERT(label);
  ASSERT(entry);
  if (!database) {
    mprintf(0, "Can't write record because database NULL\n");
    return false;
  }

  return database->CreateRecord((char *)label, REGT_STRING, (void *)entry);
}

bool oeLnxAppDatabase::write(const char *label, int entry) {
  ASSERT(label);
  if (!database) {
    mprintf(0, "Can't write record because database NULL\n");
    return false;
  }
  return database->CreateRecord((char *)label, REGT_DWORD, &entry);
}

// get the current user's name from the os
void oeLnxAppDatabase::get_user_name(char *buffer, size_t *size) {
  struct passwd *pwuid = getpwuid(geteuid());

  if ((pwuid != NULL) && (pwuid->pw_name != NULL)) {
    strncpy(buffer, pwuid->pw_name, (*size) - 1);
    buffer[(*size) - 1] = '\0';
    *size = strlen(buffer);
  } else {
    strncpy(buffer, "Unknown", (*size) - 1);
    buffer[(*size) - 1] = '\0';
    *size = strlen(buffer);
  }
}
