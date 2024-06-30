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

 * $Logfile: /DescentIII/main/ship.h $
 * $Revision: 26 $
 * $Date: 8/29/01 4:27p $
 * $Author: Matt $
 *
 * Header for player ship page
 *
 * $Log: /DescentIII/main/ship.h $
 *
 * 26    8/29/01 4:27p Matt
 * Increased MAX_SHIPS from 10 to 30
 *
 * 25    2/04/00 9:52a Matt
 * Increased MAX_SHIPS from 5 to 10
 *
 * 24    5/13/99 12:29p Jeff
 * made AllowedShips an extern
 *
 * 23    5/12/99 1:58p Jason
 * fixed yet more buggy/ugly code
 *
 * 22    4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 21    4/11/99 3:04p Matt
 * Reduced the max number of player ships from 30 to 5.
 * Re-wrote the static ship name code to be more space efficient.
 * Took default ship name (the one used to find the ship)  out of string
 * table.
 *
 * 20    11/03/98 6:16p Chris
 * Starting to make on/off and spray weapons accessable to robots
 *
 * 19    10/13/98 12:56p Matt
 * Finished (hopefully) with the ammo system.  Added support for napalm
 * fuel.
 *
 * 18    10/12/98 3:02p Jeff
 * moved DEFAULT_SHIP #define into ship.h
 *
 * 17    10/02/98 1:47p Jason
 * added lod player ships
 *
 * 16    9/10/98 11:53a Jason
 * added hud config filename to ship page
 *
 * 15    8/07/98 2:43p Jeff
 * flags gets cleared and initialized correctly
 *
 * 14    8/06/98 10:59a Jason
 * added zoom weapons
 *
 * 13    7/31/98 5:23p Jason
 * added ship armor scalars
 *
 * 12    6/29/98 3:08p Jason
 * added on/off weapons
 *
 * 11    6/16/98 10:54a Jeff
 *
 * 10    6/01/98 10:37a Matt
 * Added system to spew powerups when the player dies.  Still needs Jason
 * to deal with  mng_FindSpecificGenericPage().
 *
 * 9     5/25/98 8:17p Matt
 * Moved MAX_PLAYER_WEAPONS fromw weapon.h to player.h, so that the latter
 * doesn't need to include the former, drastically speeding build times
 * when weapon.h is changed.
 *
 * 8     3/19/98 1:02p Samir
 * Added field for cockpit filename.
 *
 * 7     2/17/98 8:19p Matt
 * Added looping & release sounds for player weapons
 *
 * 6     11/12/97 1:13p Jason
 * added weapons that can ramp up
 *
 * 5     11/04/97 6:18p Chris
 * Added support so that the player ship uses the robot's firing dialog.
 *
 * 4     10/21/97 11:57a Jason
 * added ability to set dying model for player ship
 *
 * 3     9/03/97 4:37p Mark
 * upped max_ship count
 *
 * 2     7/24/97 5:26p Matt
 * Added SourceSafe header
 *
 * $NoKeywords: $
 */

#ifndef SHIP_H
#define SHIP_H

#include <array>

#include "pstypes.h"
#include "manage.h"
#include "object.h"
#include "robotfirestruct.h"
#include "player.h"

#define MAX_SHIPS 30

// #ifdef DEMO //Demo2 will use GL
// #define DEFAULT_SHIP "Pyro-SE"
// #else
#define DEFAULT_SHIP "Pyro-GL"
// #endif

// Ship fire flags
#define SFF_FUSION 1 // fires like fusion
#define SFF_ZOOM 4   // Zooms in
#define SFF_TENTHS 8 // Ammo displays in tenths

// Default ship IDs
#define SHIP_PYRO_ID 0
#define SHIP_PHOENIX_ID 1
#define SHIP_MAGNUM_ID 2

#define MAX_DEFAULT_SHIPS 3

// Ship flags
#define SF_DEFAULT_ALLOW 1 // Allowed by default

struct ship {
  char name[PAGENAME_LEN];
  float size;
  physics_info phys_info; // the physics data for this obj type.
  int model_handle;       //  a polygon model
  int dying_model_handle; // Dying polygon model

  int med_render_handle; // handle for med res version of this object
  int lo_render_handle;  // handle for lo res version of this object

  float med_lod_distance;
  float lo_lod_distance;

  otype_wb_info static_wb[MAX_PLAYER_WEAPONS];
  uint8_t fire_flags[MAX_PLAYER_WEAPONS]; // how a particular weapon fires
  int max_ammo[MAX_PLAYER_WEAPONS];

  int firing_sound[MAX_PLAYER_WEAPONS];         // sound the weapon makes while button held down
  int firing_release_sound[MAX_PLAYER_WEAPONS]; // sound the weapon makes when the button is released

  int spew_powerup[MAX_PLAYER_WEAPONS]; // which powerup to spew for each weapon

  char cockpit_name[PAGENAME_LEN];    // name of cockpit.inf file
  char hud_config_name[PAGENAME_LEN]; // name of hud configuration file

  float armor_scalar;

  int flags;
  uint8_t used;
};

extern int Num_ships;
extern std::array<ship, MAX_SHIPS> Ships;

extern const char *AllowedShips[];

// Sets all ships to unused
void InitShips();

// Allocs a ship for use, returns -1 if error, else index on success
int AllocShip();

// Frees ship index n
void FreeShip(int n);

// Gets next ship from n that has actually been alloced
int GetNextShip(int n);

// Gets previous ship from n that has actually been alloced
int GetPrevShip(int n);

// Searches thru all ships for a specific name, returns -1 if not found
// or index of ship with name
int FindShipName(const char *name);

// Given a filename, loads either the model or vclip found in that file.  If type
// is not NULL, sets it to 1 if file is model, otherwise sets it to zero
int LoadShipImage(const char *filename);

// Given a ship handle, returns that ships image for framenum
int GetShipImage(int handle);

// This is a very confusing function.  It takes all the ships that we have loaded
// and remaps then into their proper places (if they are static).
void RemapShips();

// goes thru every entity that could possible have a ship index (ie objects, ships, etc)
// and changes the old index to the new index
void RemapAllShipObjects(int old_index, int new_index);

#endif
