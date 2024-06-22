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

 * $Logfile: /DescentIII/Main/win32/windata.cpp $
 * $Revision: 8 $
 * $Date: 4/24/99 5:47p $
 * $Author: Samir $
 *
 * Windows registry functions
 *
 * $Log: /DescentIII/Main/win32/windata.cpp $
 *
 * 8     4/24/99 5:47p Samir
 * added functions to set current win32 resource dll or exe.
 *
 * 7     2/15/99 1:22p Kevin
 * Changes for GameGauge
 *
 * 6     9/22/98 1:55p Matt
 * Change the registry path to "Outrage\Descent3".
 *
 * 5     11/16/97 2:32p Matt
 * Allow writing of registry string variables with an empty string as the
 * value
 *
 * 4     7/24/97 3:06p Matt
 * Added functions to read & write bools & variable-length integers, and
 * fixed a few small bugs.
 *
 * 3     7/22/97 7:07p Matt
 * Changed registry path from Software\Parallax Software\Outrage
 * Entertainment to just Software\Outrage Entertainment
 *
 * 6     6/11/97 1:10p Samir
 * Fixup of database.
 *
 * 5     5/13/97 11:25a Samir
 * Create_record now sets that record as the default.
 *
 * 4     5/08/97 1:58p Samir
 * When initializing database, check if there is an outrage entry in the
 * registry.
 *
 * 3     3/14/97 6:10 PM Jeremy
 * added get_user_name to osWinDatabase
 *
 * 2     3/03/97 4:36p Samir
 * removed instance of pserror.h.  this lib shouldn't need it.
 *
 * 1     3/03/97 4:28p Samir
 *
 * $NoKeywords: $
 */

#include "windatabase.h"

#include <windows.h>
#include <assert.h>

#include "mono.h"
#include "pserror.h"

//	Construction and destruction.

oeAppDatabase* Database()
{
  static oeWin32AppDatabase* instance = nullptr;
  if(instance == nullptr)
    instance = new oeWin32AppDatabase();
  return instance;
}

static_assert(sizeof(char) == sizeof(BYTE), "assumed size is incorrect!");
static_assert(sizeof(DWORD) == sizeof(size_t), "assumed size is incorrect!");

oeWin32AppDatabase::oeWin32AppDatabase() {
  bool res;

  hCurKey = 0;
  m_regkey.hBaseKey = HKEY_CURRENT_USER;

  //	create outrage entertainment key
  lstrcpy(m_regkey.path, "SOFTWARE\\Outrage");
  res = lookup_record(m_regkey.path);
  if (!res) {
    res = create_record(m_regkey.path);
    if (!res) {
      mprintf(1, "Unable to create registry directory.\n");
    }
  }
}

oeWin32AppDatabase::~oeWin32AppDatabase() {
  if (hCurKey) {
    RegCloseKey(hCurKey);
  }
}

//	Record functions
//		these are actual folders of information

//	creates an empty classification or structure where you can store information
bool oeWin32AppDatabase::create_record(const char *pathname) {
  HKEY hkey;
  DWORD disp;

  assert(m_regkey.hBaseKey);

  if(LSTATUS lres = RegCreateKeyEx(m_regkey.hBaseKey, pathname, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hCurKey, &disp);
    lres != ERROR_SUCCESS) {
    hCurKey = 0;
    mprintf(1, "Unable to create key %s (%x)\n", pathname, lres);
    return false;
  }

  return true;
}

//	set current database focus to a particular record
bool oeWin32AppDatabase::lookup_record(const char *pathname) {
  assert(m_regkey.hBaseKey);

  if (hCurKey) {
    RegCloseKey(hCurKey);
  }

  if(LSTATUS lres = RegOpenKeyEx(m_regkey.hBaseKey, pathname, 0, KEY_READ | KEY_WRITE | KEY_EXECUTE, hCurKey);
    lres != ERROR_SUCCESS) {
    hCurKey = 0;
    mprintf(1, "Unable to open key %s (%x)\n", pathname, lres);
    return false;
  }

  return true;
}

//	read either a string from the current record
bool oeWin32AppDatabase::read(const char *label, char *entry, int *entrylen) {
  DWORD type;

  assert(m_regkey.hBaseKey);
  assert(label != NULL);
  assert(entry != NULL);
  assert(entrylen != NULL);

  if(LSTATUS lres = RegQueryValueEx(hCurKey, label, NULL, &type, (LPBYTE)entry, (LPDWORD)entrylen);
    lres != ERROR_SUCCESS) {
    mprintf(1, "Unable to query str key %s (%x)\n", label, lres);
    return false;
  }
  assert(type != REG_DWORD);
  return true;
}

// read a variable-sized integer from the current record
bool oeWin32AppDatabase::read(const char *label, void *entry, int wordsize) {
  DWORD len = 4;
  DWORD type;
  int t;

  assert(m_regkey.hBaseKey);
  assert(label != NULL);
  assert(entry != NULL);

  if (LSTATUS lres = RegQueryValueEx(hCurKey, label, NULL, &type, (LPBYTE)&t, &len);
      lres != ERROR_SUCCESS) {
    mprintf(1, "Unable to query int key %s (%x)\n", label, lres);
    return false;
  }

  assert(len == 4);
  assert(type == REG_DWORD);

  switch (wordsize) {
  case 1:
    *static_cast<char *>(entry) = (char)t;
    break;
  case 2:
    *static_cast<int16_t *>(entry) = (int16_t)t;
    break;
  case 4:
    *static_cast<int *>(entry) = (int)t;
    break;
  default:
    Int3();
    break; // invalid word size
  }

  return true;
}

bool oeWin32AppDatabase::read(const char *label, bool *entry) {
  int t;

  if (read(label, &t, sizeof(t))) {
    *entry = (t != 0);
    return 1;
  } else
    return 0;
}

//	write either an integer or string to a record.
bool oeWin32AppDatabase::write(const char *label, const char *entry, int entrylen) {
  assert(m_regkey.hBaseKey);
  assert(label != NULL);
  assert(entry != NULL);
  //	assert(entrylen > 0);

  if(LSTATUS lres = RegSetValueEx(hCurKey, label, 0, REG_SZ, (LPBYTE)entry, entrylen);
      lres != ERROR_SUCCESS) {
    mprintf(1, "Unable to write str key %s (%x)\n", label, lres);
    return false;
  }
  return true;
}

bool oeWin32AppDatabase::write(const char *label, int entry) {
  assert(m_regkey.hBaseKey);
  assert(label != NULL);

  if(LSTATUS lres = RegSetValueEx(hCurKey, label, 0, REG_DWORD, (LPBYTE)&entry, sizeof(int));
      lres != ERROR_SUCCESS) {
    mprintf(1, "Unable to write int key %s (%x)\n", label, lres);
    return false;
  }

  return true;
}

// get the current user's name from the os
void oeWin32AppDatabase::get_user_name(char *buffer, size_t *size) {
  GetUserName(buffer, reinterpret_cast<LPDWORD>(size));
}

/////////////////////////////////////////////////////////////////////////////////
// pass name of dll which contains desired language
// NULL library is the default resource DLL

static HINSTANCE hThisResourceModule = NULL;

bool win32_SetResourceDLL(const char *libname) {
  if (hThisResourceModule) {
    FreeLibrary(hThisResourceModule);
    hThisResourceModule = NULL;
  }

  if (libname) {
    hThisResourceModule = LoadLibrary(libname);
  }

  return (hThisResourceModule) ? true : false;
}

// returns a string from the current resource
bool win32_GetStringResource(int txt_id, char *buffer, int buflen) {
  if (LoadString(hThisResourceModule, txt_id, buffer, buflen)) {
    buffer[buflen - 1] = '\0';
    return true;
  }
  strncpy(buffer, "!!!ERROR MISSING DLL STRING!!!", buflen - 1);
  buffer[buflen - 1] = '\0';
  return false;
}
