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

 * $Logfile: /DescentIII/Main/ship.cpp $
 * $Revision: 19 $
 * $Date: 5/13/99 3:42p $
 * $Author: Ardussi $
 *
 * $Log: /DescentIII/Main/ship.cpp $
 *
 * 19    5/13/99 3:42p Ardussi
 * changes for compiling on the Mac
 *
 * 18    5/12/99 1:57p Jason
 * fixed yet more buggy/ugly code
 *
 * 17    4/11/99 4:46p Matt
 * Small fixes
 *
 * 16    4/11/99 3:04p Matt
 * Reduced the max number of player ships from 30 to 5.
 * Re-wrote the static ship name code to be more space efficient.
 * Took default ship name (the one used to find the ship)  out of string
 * table.
 *
 * 15    2/17/99 10:32a Matt
 * Init physics hit_die_dot for new items
 *
 * 14    10/08/98 10:28p Jason
 * more demo changes for ship
 *
 * 13    10/02/98 1:47p Jason
 * added lod player ships
 *
 * 12    8/07/98 2:43p Jeff
 * flags gets cleared and initialized correctly
 *
 * 11    7/31/98 5:23p Jason
 * added ship armor scalars
 *
 * 10    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 9     4/30/98 11:32a Chris
 * ClearWB  to WBClear
 *
 * 8     4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 7     2/17/98 8:12p Matt
 * Added looping & release sounds for player weapons
 *
 * 6     11/04/97 6:18p Chris
 * Added support so that the player ship uses the robot's firing dialog.
 *
 * 5     10/21/97 11:57a Jason
 * added ability to set dying model for player ship
 *
 * 4     10/20/97 4:46p Jason
 * changes for explosions
 *
 * 3     9/09/97 7:02p Jason
 * don't reload the models during the remap phase
 *
 * 2     8/06/97 12:40p Jason
 * fixed some potentially serious memory problems
 *
 * 6     4/07/97 3:17p Chris
 * Incremental improvement
 *
 * 5     4/07/97 3:13p Chris
 *
 * 4     4/02/97 5:21p Jason
 * added the ability for pages to free the models that they point to
 *
 * 3     4/02/97 4:04p Jason
 * made ships remap properly
 *
 * 2     3/31/97 4:34p Jason
 * added player ship page
 *
 * 1     3/31/97 12:21p Jason
 *
 * $NoKeywords: $
 */

#include "ship.h"
#include "pstypes.h"
#include "pserror.h"
#include "object.h"
#include "3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "polymodel.h"
#include "player.h"
#include "robotfire.h"

#define DEFAULT_SHIP_SIZE 4.0

std::array<ship, MAX_SHIPS> Ships;
int Num_ships = 0;

// There are no static ships
char *Static_ship_names[1];
#define NUM_STATIC_SHIPS 0

#define SHIP_PYRO_ID 0
#define SHIP_PHOENIX_ID 1
#define SHIP_MAGNUM_ID 2

const char *AllowedShips[MAX_SHIPS] = {"Pyro-GL", "Phoenix", "Magnum-AHT"};

// Sets all ships to unused
void InitShips() {
  for (int i = 0; i < MAX_SHIPS; i++) {
    memset(&Ships[i], 0, sizeof(ship));
  }
  Num_ships = 0;
}

// Allocs a ship for use, returns -1 if error, else index on success
int AllocShip() {
  for (int i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used == 0) {
      memset(&Ships[i], 0, sizeof(ship));
      Ships[i].used = 1;
      Ships[i].size = DEFAULT_SHIP_SIZE;
      Ships[i].dying_model_handle = -1;
      Ships[i].med_render_handle = -1;
      Ships[i].lo_render_handle = -1;
      Ships[i].med_lod_distance = DEFAULT_MED_LOD_DISTANCE;
      Ships[i].lo_lod_distance = DEFAULT_LO_LOD_DISTANCE;
      Ships[i].model_handle = -1;
      Ships[i].armor_scalar = 1.0;
      Ships[i].flags = 0;

      Ships[i].phys_info.hit_die_dot = -1; //-1 mean doesn't apply

      // Make sure the weapon battery info is cleared for a new object
      WBClearInfo(Ships[i].static_wb);

      for (int w = 0; w < MAX_PLAYER_WEAPONS; w++) {
        Ships[i].firing_sound[w] = -1;
        //				Ships[i].release_sound[w] = -1;
      }

      Num_ships++;
      return i;
    }
  }

  Int3(); // No ships free!
  return -1;
}

// Frees ship index n
void FreeShip(int n) {
  ASSERT(Ships[n].used > 0);

  Ships[n].used = 0;
  Ships[n].name[0] = 0;
  Num_ships--;
}

// Gets next ship from n that has actually been alloced
int GetNextShip(int n) {
  int i;

  if (Num_ships == 0)
    return -1;

  if ((n < 0) || (n >= MAX_SHIPS))
    n = -1;

  for (i = n + 1; i < MAX_SHIPS; i++)
    if (Ships[i].used)
      return i;
  for (i = 0; i < n; i++)
    if (Ships[i].used)
      return i;

  // this is the only one

  return n;
}

// Gets previous ship from n that has actually been alloced
int GetPrevShip(int n) {
  int i;

  if (Num_ships == 0)
    return -1;

  if ((n < 0) || (n >= MAX_SHIPS))
    n = MAX_SHIPS;

  for (i = n - 1; i >= 0; i--) {
    if (Ships[i].used)
      return i;
  }
  for (i = MAX_SHIPS - 1; i > n; i--) {
    if (Ships[i].used)
      return i;
  }

  // this is the only one
  return n;
}
// Searches thru all ships for a specific name, returns -1 if not found
// or index of ship with name
int FindShipName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_SHIPS; i++)
    if (Ships[i].used && !stricmp(name, Ships[i].name))
      return i;

  return -1;
}

int LoadShipImage(const char *filename) {
  int img_handle;

  img_handle = LoadPolyModel(filename, 1);

  return img_handle;
}

// Given a ship handle, returns an index to that ships model
int GetShipImage(int handle) {
  ASSERT(Ships[handle].used > 0);

  return (Ships[handle].model_handle);
}

// This is a very confusing function.  It takes all the ships that we have loaded
// and remaps then into their proper places (if they are static).
void RemapShips() {
  int i;

  // Loop through the static ships and move them to the correct slots
  for (i = 0; i < NUM_STATIC_SHIPS; i++) {

    int cur_index = FindShipName(Static_ship_names[i]);

    if (cur_index == -1) {
      Int3(); // couldn't find statically-mapped ship
      continue;
    }

    if (cur_index != i) { // not in right slot

      if (Ships[i].used) { // someone else in this slot, so swap
        ship tship = Ships[i];
        Ships[i] = Ships[cur_index];
        Ships[cur_index] = tship;
        RemapAllShipObjects(i, MAX_SHIPS);
        RemapAllShipObjects(cur_index, i);
        RemapAllShipObjects(MAX_SHIPS, cur_index);
      } else { // slot is unused, so just take it
        Ships[i] = Ships[cur_index];
        Ships[cur_index].used = 0;
        RemapAllShipObjects(cur_index, i);
      }
    }
  }

  // Now, if any ships are polygon models and those models don't have correct
  // textures, attempt to reload the model texture list
  for (i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used) {
      ASSERT(Ships[i].model_handle != -1);
      // LoadPolyModel (Poly_models[Ships[i].model_handle].name);
    }
  }
}

// goes thru every entity that could possible have a ship index
// and changes the old index to the new index
void RemapAllShipObjects(int old_index, int new_index) {
  for (int i = 0; i < MAX_OBJECTS; i++) {
    if (Objects[i].type == OBJ_PLAYER) {
      if (Players[Objects[i].id].ship_index == old_index)
        Players[Objects[i].id].ship_index = new_index;
    }
  }
}
