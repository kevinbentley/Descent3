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

 * $Logfile: /DescentIII/main/door.cpp $
 * $Revision: 12 $
 * $Date: 2/04/99 2:05p $
 * $Author: Matt $
 *
 * doorway and side info.
 *
 * $Log: /DescentIII/main/door.cpp $
 *
 * 12    2/04/99 2:05p Matt
 * Added blastable doors
 *
 * 11    1/29/99 12:47p Matt
 * Rewrote the doorway system
 *
 * 10    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 9     4/06/98 4:53p Jason
 * got pageable polymodels working correctly with editor
 *
 * 8     4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 7     2/02/98 7:07p Matt
 * Added support for doors that can be seen through even when closed
 *
 * 6     10/06/97 1:01p Jason
 * made doors work with scripts (sort of)
 *
 * 5     9/17/97 11:16a Matt
 * Ripped out segment code
 *
 * 4     9/12/97 5:38p Jason
 * got doors working
 *
 * 3     9/09/97 7:02p Jason
 * don't reload the models during the remap phase
 *
 * 2     8/07/97 12:42p Jason
 * fixed potential memory problem
 *
 * 18    5/23/97 5:46p Matt
 * Added SetMatrixBasedOnSide() functionality to ExtractMatrixFromSeg().
 *
 * 17    4/02/97 5:21p Jason
 * added the ability for pages to free the models that they point to
 *
 * 16    3/18/97 5:22p Jason
 * took out dumb mprintf
 *
 * 15    3/14/97 5:54p Jason
 * made positional interpolation work with 3d doors
 *
 * 14    3/13/97 6:23p Jason
 * fixed a door bug
 *
 * 13    3/13/97 6:13p Jason
 * got poly doors working
 *
 * 12    3/12/97 2:15p Samir
 * Removed global references to doorways.
 *
 * 11    3/12/97 12:40p Samir
 * Adding doorway open code
 *
 * 10    3/10/97 4:07p Samir
 * We now almost nevert render the texture in a door segment
 *
 * 9     3/07/97 2:19p Jason
 * added DrawDoorSegment function
 *
 * 8     3/05/97 3:10p Jason
 * added more door functionality
 *
 * 7     3/05/97 3:03p Jason
 * added blinking messages
 *
 * 6     3/05/97 2:27p Samir
 *
 * 5     3/05/97 12:16p Jason
 * added code to support our new 3d doors
 *
 * 4     2/27/97 5:09p Samir
 * Key flags defined in door code.
 *
 * 3     2/26/97 4:25p Samir
 * Call GetDoorFlags to get door info.
 *
 * 2     2/25/97 4:35p Samir
 * Added SIDE_FLAGS macro.
 *
 * $NoKeywords: $
 */

#include <string.h>

#include "door.h"
#include "pserror.h"
#include "polymodel.h"
#include "game.h"
#include "doorway.h"

//	---------------------------------------------------------------------------
//	Globals

std::array<door, MAX_DOORS> Doors; // door info.
int Num_doors = 0;

//	---------------------------------------------------------------------------
//	Prototypes

//	---------------------------------------------------------------------------
//	Functions

// Sets all doors to unused
void InitDoors() {
  for (int i = 0; i < MAX_DOORS; i++) {
    memset(&Doors[i], 0, sizeof(door));
    Doors[i].model_handle = -1;
    // Doors[i].script_name[0] = 0;
  }
  Num_doors = 0;
}

// Allocs a door for use, returns -1 if error, else index on success
int AllocDoor() {
  for (int i = 0; i < MAX_DOORS; i++) {
    if (Doors[i].used == 0) {
      Doors[i].used = 1;
      // Doors[i].script_name[0] = 0;
      Doors[i].flags = 0;
      Doors[i].hit_points = 0.0;
      Num_doors++;
      return i;
    }
  }

  Int3(); // No doors free!
  return -1;
}

// Frees door index n
void FreeDoor(int n) {
  ASSERT(Doors[n].used > 0);

  Doors[n].used = 0;
  Doors[n].name[0] = 0;
  Num_doors--;
}

// Gets next door from n that has actually been alloced
int GetNextDoor(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_DOORS);

  if (Num_doors == 0)
    return -1;

  for (i = n + 1; i < MAX_DOORS; i++)
    if (Doors[i].used)
      return i;
  for (i = 0; i < n; i++)
    if (Doors[i].used)
      return i;

  // this is the only one

  return n;
}

// Gets previous door from n that has actually been alloced
int GetPrevDoor(int n) {
  int i;

  ASSERT(n >= 0 && n < MAX_DOORS);

  if (Num_doors == 0)
    return -1;

  for (i = n - 1; i >= 0; i--) {
    if (Doors[i].used)
      return i;
  }
  for (i = MAX_DOORS - 1; i > n; i--) {
    if (Doors[i].used)
      return i;
  }

  // this is the only one
  return n;
}
// Searches thru all doors for a specific name, returns -1 if not found
// or index of door with name
int FindDoorName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_DOORS; i++)
    if (Doors[i].used && !stricmp(name, Doors[i].name))
      return i;

  return -1;
}

// Given a filename, loads the model found in that file

int LoadDoorImage(const char *filename, int pageable) {
  int img_handle;

  img_handle = LoadPolyModel(filename, pageable);

  return img_handle;
}

// Given a door handle, returns an index to that doors model
int GetDoorImage(int handle) {
  ASSERT(Doors[handle].used > 0);

  return (Doors[handle].model_handle);
}

void RemapDoors() {
  // Now, if any doors are polygon models and those models don't have correct
  // textures, attempt to reload the model texture list

  for (int i = 0; i < MAX_DOORS; i++) {
    if (Doors[i].used) {
      ASSERT(Doors[i].model_handle != -1);
      // LoadPolyModel (Poly_models[Doors[i].model_handle].name);
    }
  }
}
