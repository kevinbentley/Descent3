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

 * $Logfile: /DescentIII/main/PilotPicsAPI.cpp $
 * $Revision: 9 $
 * $Date: 10/21/99 9:28p $
 * $Author: Jeff $
 *
 * API implementation for Pilot Pictures
 *
 * $Log: /DescentIII/main/PilotPicsAPI.cpp $
 *
 * 9     10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 8     4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 7     3/30/99 4:26a Jeff
 * reset variable when closing down system
 *
 * 6     3/29/99 7:19p Jeff
 * increased buffer for importing pilot pics
 *
 * 5     2/05/99 7:04p Jeff
 * table file parsing macros put in
 *
 * 4     1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 3     11/24/98 5:16p Jeff
 * fixed bugs in the api during initial testing
 *
 * 2     11/23/98 6:30p Jeff
 * initial creation
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"
#include "player.h"
#include "pilot.h"
#include "cfile.h"
#include "mono.h"
#include "ddio.h"
#include "manage.h"
#include "PilotPicsAPI.h"
#include "mem.h"

#include <algorithm>

#define PILOTPIC_DATABASE_HOG "PPics.Hog"
#define PILOTPIC_DATABASE_INDEX "PPics.idx"

static CFILE *PilotPic_database_index_handle = NULL;
static int PilotPic_database_hog_handle = 0;
static int PilotPic_find_offset;
static char PilotPic_find_name[PILOT_STRING_SIZE];
static bool PilotPic_init = false;

// -----------------------------------------------
// PPic_BuildDatabase
//	Purpose:
//		Builds up some databases for fast access
//	based off the index file.
// -----------------------------------------------
static bool PPic_BuildDatabases(void);
// -----------------------------------------------
// PPic_FreeDatabase
//	Purpose:
//		Frees up memory associated with the databases
// -----------------------------------------------
static void PPic_FreeDatabase(void);
// -------------------------------------------------
// PPic_JumpToPilot
//	Purpose:
//		Returns an offset into the file to where the
//	the first pilot that matches pilot_name is. -1
//	is returned if no match
// --------------------------------------------------
static int PPic_JumpToPilot(char *pilot_name);
// -------------------------------------
// PPic_GetIndexFromID
//	Purpose:
//		Returns the file index into the Pilot_id_to_offset
//	list for the given id, -1 if not found.
// -------------------------------------
static int PPic_GetIndexFromID(int id);
// -------------------------------------
// PPic_GetOffsetByID
//	Purpose:
//		Returns the file offset of the given pilot id. -1 if not found
// -------------------------------------
static int PPic_GetOffsetByID(uint16_t pilot_id);

//===========================================================================

// ---------------------------------------------------------
// PPic_InitDatabase
//	Purpose:
//		Initializes the database for the pictures.  Call before
//	any other Pilot Picture function
// ---------------------------------------------------------
bool PPic_InitDatabase(void) {
  if (PilotPic_init) {
    mprintf(0, "PPIC: InitDatabase already called\n");
    return true;
  }

  // attempt to open the hog database
  // --------------------------------
  PilotPic_database_hog_handle = cf_OpenLibrary(PILOTPIC_DATABASE_HOG);

  if (PilotPic_database_hog_handle == 0) {
    // there was an error opening the hog database
    // -----------------------------------------
    mprintf(0, "PPIC: Error opening %s database\n", PILOTPIC_DATABASE_HOG);
    PilotPic_database_index_handle = NULL;
    return false;
  }

  // attempt to open the pilotpicture database index
  // -----------------------------------------------
  PilotPic_database_index_handle = cfopen(PILOTPIC_DATABASE_INDEX, "rb");

  if (PilotPic_database_index_handle == NULL) {
    // there was an error opening the database index
    // ---------------------------------------------
    mprintf(0, "PPIC: Error opening database index '%s'\n", PILOTPIC_DATABASE_INDEX);
    cf_CloseLibrary(PilotPic_database_hog_handle);
    PilotPic_database_hog_handle = 0;
    return false;
  }

  // when we get to this point, all of our files have been opened successfully, so to
  // make searching, etc fast, we'll build some databases in memory, for quick lookup
  // ---------------------------------------------------------------------------------
  if (!PPic_BuildDatabases()) {
    // there was an error building the databases
    // -----------------------------------------
    mprintf(0, "PPIC: Error building databases\n");
    cfclose(PilotPic_database_index_handle);
    PilotPic_database_index_handle = NULL;
    cf_CloseLibrary(PilotPic_database_hog_handle);
    PilotPic_database_hog_handle = 0;
    return false;
  }

  PilotPic_init = true;

  atexit(PPic_CloseDatabase);

  return true;
}

// ---------------------------------------------------------
// PPic_CloseDatabase
//	Purpose:
//		Closes down the picture database.
// ---------------------------------------------------------
void PPic_CloseDatabase(void) {
  if (!PilotPic_init)
    return;

  // close up the database
  PPic_FreeDatabase();

  // close up files
  if (PilotPic_database_index_handle) {
    cfclose(PilotPic_database_index_handle);
    PilotPic_database_index_handle = NULL;
  }

  if (PilotPic_database_hog_handle) {
    cf_CloseLibrary(PilotPic_database_hog_handle);
    PilotPic_database_hog_handle = 0;
  }

  PilotPic_init = false;
}

// ---------------------------------------------------------
// PPic_QueryPilot
//	Purpose:
//		Given a pilot callsign it will search the database
//	and return the number of pilots that match the name
// ---------------------------------------------------------
uint16_t PPic_QueryPilot(char *pilot_name) {
  if (!PilotPic_init)
    return 0;

  int letter_offset = PPic_JumpToPilot(pilot_name);
  if (letter_offset == -1)
    return 0;

  int count = 0;
  bool done = false;
  char name_buffer[PILOT_STRING_SIZE];
  CFILE *file = PilotPic_database_index_handle;

  // now read through the pilots until we don't get a match anymore
  while (!done) {
    // first read in the pilot name
    uint8_t name_size;
    name_size = cf_ReadByte(file);

    if (cfeof(file)) {
      done = true;
      continue;
    }
    cf_ReadBytes((uint8_t *)name_buffer, name_size, file);
    name_buffer[name_size] = '\0';

    // next read in pilot_id
    uint16_t pilot_id;
    pilot_id = (uint16_t)cf_ReadShort(file);

    // next read past the bitmap name
    uint8_t bmp_size;
    bmp_size = cf_ReadByte(file);
    cfseek(file, bmp_size, SEEK_CUR);

    if (stricmp(name_buffer, pilot_name)) {
      // we're done
      done = true;
    } else
      count++;

    if (cfeof(file))
      done = true;
  }

  return count;
}

// ---------------------------------------------------------
// PPic_FindFirst
//	Purpose:
//		Given a pilot callsign it will return the first pilot
//	that matches the search.  Returns true on success, false
//	if it couldn't find any pilots matching.  It returns
//	the pilot id.
// ----------------------------------------------------------
bool PPic_FindFirst(char *pilot_name, uint16_t *pilot_id) {
  if (!PilotPic_init)
    return false;

  *pilot_id = 65535;

  int letter_offset = PPic_JumpToPilot(pilot_name);
  if (letter_offset == -1)
    return false;

  strcpy(PilotPic_find_name, pilot_name);

  char name_buffer[PILOT_STRING_SIZE];
  CFILE *file = PilotPic_database_index_handle;

  // first read in the pilot name
  uint8_t name_size;
  name_size = cf_ReadByte(file);
  if (cfeof(file)) {
    return false;
  }
  cf_ReadBytes((uint8_t *)name_buffer, name_size, file);
  name_buffer[name_size] = '\0';

  // next read in pilot_id
  uint16_t pid;
  pid = (uint16_t)cf_ReadShort(file);

  // next read past the bitmap name
  uint8_t bmp_size;
  bmp_size = cf_ReadByte(file);
  cfseek(file, bmp_size, SEEK_CUR);

  if (stricmp(name_buffer, pilot_name)) {
    return false; // weird
  }

  *pilot_id = pid;
  PilotPic_find_offset = cftell(file);

  return true;
}

// ----------------------------------------------------------
// PPic_FindNext
//	Purpose:
//		Call repeatedly until false is returned to get information
//	about all the pilots that match pilot_name passed into
//	an initial call to PPic_FindFirst().  It returns the
//	pilot id.
// ----------------------------------------------------------
bool PPic_FindNext(uint16_t *pilot_id) {
  if (!PilotPic_init)
    return false;

  *pilot_id = 65535;

  char name_buffer[PILOT_STRING_SIZE];
  CFILE *file = PilotPic_database_index_handle;

  cfseek(file, PilotPic_find_offset, SEEK_SET);
  if (cfeof(file)) {
    return false;
  }

  // first read in the pilot name
  uint8_t name_size;
  name_size = cf_ReadByte(file);
  if (cfeof(file)) {
    return false;
  }
  cf_ReadBytes((uint8_t *)name_buffer, name_size, file);
  name_buffer[name_size] = '\0';

  // next read in pilot_id
  uint16_t pid;
  pid = (uint16_t)cf_ReadShort(file);

  // next read past the bitmap name
  uint8_t bmp_size;
  bmp_size = cf_ReadByte(file);
  cfseek(file, bmp_size, SEEK_CUR);

  if (stricmp(name_buffer, PilotPic_find_name)) {
    return false; // we're done
  }

  *pilot_id = pid;
  PilotPic_find_offset = cftell(file);

  return true;
}

// ----------------------------------------------------------
// PPic_FindClose
//	Purpose:
//		Stops a PPic_FindFirst/PPic_FindNext session
// ----------------------------------------------------------
void PPic_FindClose(void) {
  PilotPic_find_offset = 0;
  PilotPic_find_name[0] = 0;
}

// ----------------------------------------------------------
// PPic_GetPilot
//	Purpose:
//		Given a pilot id, it will return the pilot name of
//	the pilot name.  Returns false if it's an invalid pilot id.
// ----------------------------------------------------------
bool PPic_GetPilot(uint16_t pilot_id, char *pilot_name, int buffersize) {
  if (!PilotPic_init)
    return false;

  int oldoffset = cftell(PilotPic_database_index_handle);

  int offset = PPic_GetOffsetByID(pilot_id);
  if (offset == -1)
    return false;

  // jump to the offset
  // ------------------
  cfseek(PilotPic_database_index_handle, offset, SEEK_SET);
  if (cfeof(PilotPic_database_index_handle)) {
    cfseek(PilotPic_database_index_handle, oldoffset, SEEK_SET);
    return false;
  }

  // read in the pilot name
  // ----------------------
  uint8_t name_size;
  name_size = cf_ReadByte(PilotPic_database_index_handle);
  if (cfeof(PilotPic_database_index_handle)) {
    cfseek(PilotPic_database_index_handle, oldoffset, SEEK_SET);
    return false;
  }
  int toread = std::min<int>(name_size, buffersize - 1);
  cf_ReadBytes((uint8_t *)pilot_name, toread, PilotPic_database_index_handle);
  pilot_name[toread] = '\0';

  cfseek(PilotPic_database_index_handle, oldoffset, SEEK_SET);
  return true;
}

// ----------------------------------------------------------
// PPic_GetBitmapHandle
//	Purpose:
//		Given a pilot id, it will return a handle to the
//	bitmap for the pilot.  MAKE SURE YOU FREE THE BITMAP WITH
//	bm_FreeBitmap().  Returns -1 if it was an illegal pilot id.
//	Returns BAD_BITMAP_HANDLE if it couldn't open the bitmap.
// ----------------------------------------------------------
int PPic_GetBitmapHandle(uint16_t pilot_id) {
  if (!PilotPic_init)
    return -1;

  int oldoffset = cftell(PilotPic_database_index_handle);

  int offset = PPic_GetOffsetByID(pilot_id);
  if (offset == -1)
    return -1;

  // jump to the offset
  // ------------------
  cfseek(PilotPic_database_index_handle, offset, SEEK_SET);
  if (cfeof(PilotPic_database_index_handle)) {
    cfseek(PilotPic_database_index_handle, oldoffset, SEEK_SET);
    return -1;
  }

  // read in the pilot name
  // ----------------------
  uint8_t name_size;
  char name_buffer[PILOT_STRING_SIZE];
  name_size = cf_ReadByte(PilotPic_database_index_handle);
  if (cfeof(PilotPic_database_index_handle)) {
    cfseek(PilotPic_database_index_handle, oldoffset, SEEK_SET);
    return -1;
  }
  cf_ReadBytes((uint8_t *)name_buffer, name_size, PilotPic_database_index_handle);
  name_buffer[name_size] = '\0';

  // next read in pilot_id
  uint16_t pid;
  pid = (uint16_t)cf_ReadShort(PilotPic_database_index_handle);

  // next read past the bitmap name
  uint8_t bmp_size;
  char bitmap_name[_MAX_PATH];
  bmp_size = cf_ReadByte(PilotPic_database_index_handle);
  cf_ReadBytes((uint8_t *)bitmap_name, bmp_size, PilotPic_database_index_handle);
  bitmap_name[bmp_size] = '\0';

  cfseek(PilotPic_database_index_handle, oldoffset, SEEK_SET);

  int bm_handle = bm_AllocLoadFileBitmap(IGNORE_TABLE(bitmap_name), 0);
  if (bm_handle <= BAD_BITMAP_HANDLE)
    return BAD_BITMAP_HANDLE;

  return bm_handle;
}

// ===============================================================================

// this maps a pilot_id to an index file offset
struct tPilotPicIdOffset {
  int offset;
  uint16_t id;
};
tPilotPicIdOffset *Pilot_id_to_offset = NULL;
uint16_t *Sorted_Pilot_id_to_offset = NULL;
int PilotPic_count = 0;

// this maps the alphabet to an index file offset (first pilot_name that begins with the letter)
int Alphabet_to_offset[27];

// -----------------------------------------------
// PPic_BuildDatabase
//	Purpose:
//		Builds up some databases for fast access
//	based off the index file.
// -----------------------------------------------
bool PPic_BuildDatabases(void) {
  CFILE *file = PilotPic_database_index_handle;
  if (!file)
    return false;

  // first rewind to the beginning and find out how many pilots we have
  // -------------------------------------------------------------------
  cf_Rewind(file);

  PilotPic_count = cf_ReadInt(file);
  if (PilotPic_count < 0) {
    // hmm a negative!
    mprintf(0, "PPIC: Invalid number of pilot pictures (%d)\n", PilotPic_count);
    Int3();
    PilotPic_count = 0;
    cf_Rewind(file);
    return false;
  }
  if (PilotPic_count > 65535) {
    // too many!!!!
    mprintf(0, "PPIC: Invalid number of pilot pictures (%d)\n", PilotPic_count);
    Int3();
    PilotPic_count = 0;
    cf_Rewind(file);
    return false;
  }

  // allocate all the memory we're going to need
  // -------------------------------------------
  Pilot_id_to_offset = (tPilotPicIdOffset *)mem_malloc(sizeof(tPilotPicIdOffset) * PilotPic_count);
  Sorted_Pilot_id_to_offset = (uint16_t *)mem_malloc(sizeof(uint16_t) * PilotPic_count);
  if (!Pilot_id_to_offset) {
    // out of memory!!!
    mprintf(0, "PPIC: Out of memory allocating index database\n");
    Int3();
    PilotPic_count = 0;
    cf_Rewind(file);
    return false;
  }

  // now it is time to go through the index file and build the databases
  // -------------------------------------------------------------------
  int count;
  char name_buffer[256];

  for (count = 0; count < 27; count++)
    Alphabet_to_offset[count] = -1;

  for (count = 0; count < PilotPic_count; count++) {

    // get the current file position, we'll need it
    int file_pos;
    file_pos = cftell(file);

    // first read in the pilot name
    uint8_t name_size;
    name_size = cf_ReadByte(file);
    cf_ReadBytes((uint8_t *)name_buffer, name_size, file);
    name_buffer[name_size] = '\0';
    if (name_size >= PILOT_STRING_SIZE) {
      mprintf(0, "PPIC: Too big: (%s)%d %d", name_buffer, count, name_size);
    }

    // next read in pilot_id
    uint16_t pilot_id;
    pilot_id = (uint16_t)cf_ReadShort(file);

    // next read past the bitmap name
    uint8_t bmp_size;
    bmp_size = cf_ReadByte(file);
    cfseek(file, bmp_size, SEEK_CUR);

    // add the info to the database
    Pilot_id_to_offset[count].offset = file_pos;
    Pilot_id_to_offset[count].id = pilot_id;

    char let_pos;
    if (isalpha(name_buffer[0])) {
      let_pos = toupper(name_buffer[0]) - 'A';
    } else {
      let_pos = 26; // not alpha letter
    }

    if (Alphabet_to_offset[let_pos] == -1) {
      Alphabet_to_offset[let_pos] = file_pos;
    }
  }

  // now sort the pilot ids
  int i, t, j;

  for (i = 0; i < PilotPic_count; i++) {
    Sorted_Pilot_id_to_offset[i] = i;
  }

  for (i = 1; i <= PilotPic_count - 1; i++) {
    t = Sorted_Pilot_id_to_offset[i];
    // Shift elements down until
    // insertion point found.
    for (j = i - 1; j >= 0 && (Pilot_id_to_offset[Sorted_Pilot_id_to_offset[j]].id < Pilot_id_to_offset[t].id); j--) {
      Sorted_Pilot_id_to_offset[j + 1] = Sorted_Pilot_id_to_offset[j];
    }
    // insert
    Sorted_Pilot_id_to_offset[j + 1] = t;
  }

  cf_Rewind(file);
  return true;
}

// -----------------------------------------------
// PPic_FreeDatabase
//	Purpose:
//		Frees up memory associated with the databases
// ------------------------------------------------
void PPic_FreeDatabase(void) {

  for (int i = 0; i < 27; i++)
    Alphabet_to_offset[i] = -1;

  if (Pilot_id_to_offset) {
    mem_free(Pilot_id_to_offset);
    Pilot_id_to_offset = NULL;
  }
  if (Sorted_Pilot_id_to_offset) {
    mem_free(Sorted_Pilot_id_to_offset);
    Sorted_Pilot_id_to_offset = NULL;
  }

  PilotPic_count = 0;
}

// -------------------------------------------------
// PPic_JumpToPilot
//	Purpose:
//		Returns an offset into the file to where the
//	the first pilot that matches pilot_name is. -1
//	is returned if no match
// --------------------------------------------------
int PPic_JumpToPilot(char *pilot_name) {
  int lett_offset;
  int let_pos;

  if (isalpha(pilot_name[0])) {
    let_pos = toupper(pilot_name[0]) - 'A';
  } else {
    let_pos = 26;
  }

  lett_offset = Alphabet_to_offset[let_pos];
  if (lett_offset == -1) {
    // no pilot names begin with this letter
    return -1;
  }

  CFILE *file = PilotPic_database_index_handle;

  // jump to that position of the file
  cfseek(file, lett_offset, SEEK_SET);

  // now try to find the pilot
  bool done = false;
  int file_pos;
  char name_buffer[PILOT_STRING_SIZE];

  while (!done) {

    // save the file position
    file_pos = cftell(file);

    // first read in the pilot name
    uint8_t name_size;
    name_size = cf_ReadByte(file);
    if (cfeof(file)) {
      done = true;
      continue;
    }
    cf_ReadBytes((uint8_t *)name_buffer, name_size, file);
    name_buffer[name_size] = '\0';

    // next read in pilot_id
    uint16_t pilot_id;
    pilot_id = (uint16_t)cf_ReadShort(file);

    // next read past the bitmap name
    uint8_t bmp_size;
    bmp_size = cf_ReadByte(file);
    cfseek(file, bmp_size, SEEK_CUR);

    int strcmpret = stricmp(name_buffer, pilot_name);

    switch (strcmpret) {
    case 0:
      // we found a match
      cfseek(file, file_pos, SEEK_SET);
      return file_pos;
    default:
      if ((let_pos == 25) && !isalpha(name_buffer[0])) {
        // we're searching the z's and moved to let_pos 26
        return -1;
      }

      if (strcmpret > 0) {
        // we can stop reading/searching
        return -1;
      }
    }

    if (cfeof(file))
      done = true;
  }

  return -1;
}

// -------------------------------------
// PPic_GetOffsetByID
//	Purpose:
//		Returns the file offset of the given pilot id. -1 if not found
// -------------------------------------
int PPic_GetOffsetByID(uint16_t pilot_id) {
  int index = PPic_GetIndexFromID(pilot_id);
  if (index == -1)
    return -1;
  return Pilot_id_to_offset[index].offset;
}

// -------------------------------------
// PPic_GetIndexFromID
//	Purpose:
//		Returns the file index into the Pilot_id_to_offset
//	list for the given id, -1 if not found.
// -------------------------------------
int PPic_GetIndexFromID(int id) {
  // do a binary search for the id,return -1 if not found
  int min = 0, max = PilotPic_count - 1;
  int index_to_check;
  int sort_index, sorted_val;

  while (1) {
    index_to_check = (min + max) / 2;
    sort_index = Sorted_Pilot_id_to_offset[index_to_check];
    sorted_val = Pilot_id_to_offset[sort_index].id;

    if (sorted_val == id) {
      // found it!
      return sort_index;
    }

    if (min >= max) // exhausted search
      break;

    if (sorted_val > id) // search key after check key
      min = index_to_check + 1;
    else // search key before check key
      max = index_to_check - 1;
  }
  return -1;
}
