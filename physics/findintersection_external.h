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

 * $Logfile: /DescentIII/main/lib/findintersection_external.h $
 * $Revision: 6 $
 * $Date: 4/18/99 5:42a $
 * $Author: Chris $
 *
 * Description goes here
 *
 * $Log: /DescentIII/main/lib/findintersection_external.h $
 *
 * 6     4/18/99 5:42a Chris
 * Added the FQ_IGNORE_RENDER_THROUGH_PORTALS flag
 *
 * 5     4/05/99 3:58p Chris
 * Made the FQ_ flags easier to read
 *
 * 4     3/27/99 3:25p Chris
 * Added comment headers
 *
 * $NoKeywords: $
 */

#ifndef FINDINTERSECTION_EXTERNAL_H_
#define FINDINTERSECTION_EXTERNAL_H_

// return values for find_vector_intersection()
#define HIT_NONE 0                  // we hit nothing
#define HIT_WALL 1                  // we hit a wall
#define HIT_OBJECT 2                // we hit an object
#define HIT_TERRAIN 3               // we hit the terrain
#define HIT_BAD_P0 4                // start point not is specified segment
#define HIT_OUT_OF_TERRAIN_BOUNDS 5 // End point is outside of the terrain
#define HIT_BACKFACE 6              // We hit the backface of a wall...
#define HIT_SPHERE_2_POLY_OBJECT 7  // Hit a sphere to a real polygon
#define HIT_CEILING 8               // Object hit the ceiling
#define HIT_CORNER_WALL 9
#define HIT_EDGE_WALL 10
#define HIT_FACE_WALL 11

// flags for fvi query
#define FQ_CHECK_OBJS 1                         // check against objects?
#define FQ_OBJ_BACKFACE (1 << 1)                // Hit the backfaces of polyobjs
#define FQ_TRANSPOINT (1 << 2)                  // go through trans wall if hit point is transparent
#define FQ_IGNORE_POWERUPS (1 << 3)             // ignore powerups
#define FQ_BACKFACE (1 << 4)                    // Check for collisions with backfaces, usually they are ignored
#define FQ_SOLID_PORTALS (1 << 5)               // Makes connectivity disappear for FVI
#define FQ_RECORD (1 << 6)                      // Records faces that should be recorded
#define FQ_NEW_RECORD_LIST (1 << 7)             // Records faces that should be recorded
#define FQ_IGNORE_MOVING_OBJECTS (1 << 8)       // Ignores all objects that move
#define FQ_IGNORE_NON_LIGHTMAP_OBJECTS (1 << 9) // Ignores all objects that are not associated with lightmaps
#define FQ_ONLY_PLAYER_OBJ (1 << 10)            // Ignores all objects besides the player
#define FQ_IGNORE_WALLS (1 << 11)               // Ignores all walls (it will still hit OBJ_ROOMS)
#define FQ_CHECK_CEILING (1 << 12)              // Checks if object hits the imaginary ceiling
#define FQ_ONLY_DOOR_OBJ (1 << 13)              // Ignores all objects, except doors
#define FQ_NO_RELINK (1 << 14)                  // Does not determine the hitseg
#define FQ_EXTERNAL_ROOMS_AS_SPHERE (1 << 15)   // Hmmm....
#define FQ_MULTI_POINT (1 << 16)                // Enable Multi-point collision
#define FQ_LIGHTING (1 << 17)                   // Lighting only optimizations
#define FQ_COMPUTE_MOVEMENT_TIME (1 << 18)
#define FQ_IGNORE_EXTERNAL_ROOMS (1 << 19)
#define FQ_IGNORE_WEAPONS (1 << 20)
#define FQ_IGNORE_TERRAIN (1 << 21)
#define FQ_PLAYERS_AS_SPHERE (1 << 22)
#define FQ_ROBOTS_AS_SPHERE (1 << 23)
#define FQ_IGNORE_CLUTTER_COLLISIONS (1 << 24)
#define FQ_IGNORE_RENDER_THROUGH_PORTALS (1 << 25)

#endif
