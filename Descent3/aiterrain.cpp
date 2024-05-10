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

 * $Logfile: /DescentIII/main/aiterrain.cpp $
 * $Revision: 7 $
 * $Date: 2/04/98 6:09p $
 * $Author: Matt $
 *
 * Terrain specific AI stuff
 *
 * $Log: /DescentIII/main/aiterrain.cpp $
 *
 * 7     2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 6     8/20/97 3:16p Chris
 * Working on the edge of terrain problems
 *
 * 5     7/31/97 3:12p Chris
 * Fixed a problem with the new iterator based radius checker
 *
 * 4     7/30/97 1:31p Chris
 * Made helicopters slightly more interesting.
 *
 * 3     7/29/97 12:20p Chris
 * Incremental improvements.  Fixed a memory bug.
 *
 * 2     7/28/97 1:19p Chris
 * Expanding the AI system
 *
 * $NoKeywords: $
 */

#include "vecmat.h"
#include "terrain.h"
#include "pstypes.h"
#include "findintersection.h"
#include "aiterrain.h"
#include <string.h>

#define AI_MAX_SEGS_CHECKED 200

static int ai_num_segs_checked = 0;
static uint8_t ai_terrain_check_list[((TERRAIN_WIDTH * TERRAIN_DEPTH) >> 3) + 1];
static int ai_segs_checked[AI_MAX_SEGS_CHECKED];
#ifdef _DEBUG
static int ai_num_checks_since_init = 0;
#endif

static float ai_rad;
static ground_information *ai_ground_info_ptr;

static void ait_terrain_clean();
static void ai_check_terrain_node(int cur_node, int f_check_local_nodes);

void ait_Init() {
  ai_num_segs_checked = 0;
  memset(ai_terrain_check_list, 0, ((TERRAIN_WIDTH * TERRAIN_DEPTH) >> 3) + 1);

#ifdef _DEBUG
  ai_num_checks_since_init = 0;
#endif
}

void ait_terrain_clean() {
  int i;

  assert(ai_num_segs_checked >= 0 && ai_num_segs_checked <= AI_MAX_SEGS_CHECKED);

  for (i = 0; i < ai_num_segs_checked; i++) {
    ASSERT((CELLNUM(ai_segs_checked[i]) >= 0) && (CELLNUM(ai_segs_checked[i]) < TERRAIN_WIDTH * TERRAIN_DEPTH));
    ai_terrain_check_list[CELLNUM(ai_segs_checked[i]) >> 3] = 0;
  }

  // #ifdef _DEBUG
  //	for(i = 0; i < ((TERRAIN_WIDTH*TERRAIN_DEPTH)>>3)+1; i++)
  //	{
  //		ASSERT(ai_terrain_check_list[i] == 0);
  //	}
  // #endif

  ai_num_segs_checked = 0;
}

void ai_check_terrain_node(int cur_node, int f_check_local_nodes) {
  int check_x, check_y;
  int new_node;
  int xcounter, ycounter;
  int xstart, xend;
  int ystart, yend;
  int f_ignore_terrain_in_this_node = 0;

  // Chrishack -- Note

  ASSERT(cur_node >= 0 && cur_node < TERRAIN_WIDTH * TERRAIN_DEPTH);
  ASSERT((ai_terrain_check_list[cur_node >> 3] & (0x00000001 << (cur_node % 8))) == 0);

  // Mark the current node as visited
  ai_terrain_check_list[cur_node >> 3] |= 0x00000001 << (cur_node % 8);
  ai_segs_checked[ai_num_segs_checked] = MAKE_ROOMNUM(cur_node);
  ai_num_segs_checked++;
  ASSERT(ai_num_segs_checked < AI_MAX_SEGS_CHECKED);

  if (Terrain_seg[cur_node].y > ai_ground_info_ptr->highest_y)
    ai_ground_info_ptr->highest_y = Terrain_seg[cur_node].y;

  if (Terrain_seg[cur_node].y < ai_ground_info_ptr->lowest_y)
    ai_ground_info_ptr->lowest_y = Terrain_seg[cur_node].y;

  // check local nodes for any collision type, but no recursion for them :)
  if (f_check_local_nodes) {
    int next_y_delta;
    // Check worst-case collisions.  This includes all nodes within a radius edge of the current node
    check_x = ai_rad / TERRAIN_SIZE + 1;
    check_y = ai_rad / TERRAIN_SIZE + 1;

    xstart = cur_node % TERRAIN_WIDTH - check_x;
    xend = cur_node % TERRAIN_WIDTH + check_x;
    ystart = cur_node / TERRAIN_WIDTH - check_y;
    yend = cur_node / TERRAIN_WIDTH + check_y;

    if (xstart < 0)
      xstart = 0;
    if (xend >= TERRAIN_WIDTH)
      xend = TERRAIN_WIDTH - 1;
    if (ystart < 0)
      ystart = 0;
    if (yend >= TERRAIN_DEPTH)
      yend = TERRAIN_DEPTH - 1;

    // This should be a faster interative why to do a square with center at original position
    new_node = TERRAIN_WIDTH * ystart + xstart;
    next_y_delta = TERRAIN_WIDTH - (xend - xstart) - 1;

    for (ycounter = ystart; ycounter <= yend; ycounter++) {
      for (xcounter = xstart; xcounter <= xend; xcounter++) {
        if ((ai_terrain_check_list[new_node >> 3] & (0x00000001 << (new_node % 8))) == 0)
          ai_check_terrain_node(new_node, 0);
        new_node += 1;
      }

      new_node += next_y_delta;
    }
  }

  return;
}

// MTS: unused?
// Returns true if the new point is on the terrain and false if the path results in leaving the terrain
bool ait_GetGroundInfo(ground_information *ground_info, vector *p0, vector *p1, float rad, angle fov) {
  int start_node, end_node;
  int x1, x2, y1, y2, x, y, delta_y, delta_x, change_x, change_y, length, cur_node, error_term, i;

  // Clean up the last call.  This will make the info available till the next call.  Maybe
  // useful at a later date.  Plus, we have multiple exits so, this nice spot so that
  // we need only one call.  :)
  ait_terrain_clean();

#ifdef _DEBUG
  ai_num_checks_since_init++;
#endif

  ai_ground_info_ptr = ground_info;
  ai_rad = rad;

  start_node = GetTerrainCellFromPos(p0);
  end_node = GetTerrainCellFromPos(p1);

  if (start_node == -1)
    return false;

  if (end_node == -1) {
    float delta = 1.0;
    vector movement = *p1 - *p0;

    if (p1->x < (0.5f * TERRAIN_SIZE)) {
      delta = (p0->x - (0.5f * TERRAIN_SIZE)) / (-movement.x);
    } else if (p1->x > (float)(TERRAIN_WIDTH * TERRAIN_SIZE) - (0.5f * TERRAIN_SIZE)) {
      delta = ((float)(TERRAIN_WIDTH * TERRAIN_SIZE) - (0.5f * TERRAIN_SIZE) - p0->x) / (movement.x);
    }

    if (p1->z < (0.5f * TERRAIN_SIZE)) {
      if ((p0->z - (0.5f * TERRAIN_SIZE)) / (-movement.z) < delta)
        delta = (p0->z - (0.5f * TERRAIN_SIZE)) / (-movement.z);
    } else if (p1->z > (float)(TERRAIN_DEPTH * TERRAIN_SIZE) - (0.5f * TERRAIN_SIZE)) {
      if (((float)(TERRAIN_WIDTH * TERRAIN_SIZE) - (0.5f * TERRAIN_SIZE) - p0->z) / (movement.z) < delta)
        delta = ((float)(TERRAIN_WIDTH * TERRAIN_SIZE) - (0.5f * TERRAIN_SIZE) - p0->z) / (movement.z);
    }

    *p1 = *p0 + delta * movement;

    end_node = GetTerrainCellFromPos(p1);
    ASSERT(end_node != -1);
  }

  ai_ground_info_ptr->highest_y = Terrain_seg[start_node].y;
  ai_ground_info_ptr->lowest_y = Terrain_seg[start_node].y;

  // Determine the start end end nodes
  x1 = start_node % TERRAIN_WIDTH;
  y1 = start_node / TERRAIN_WIDTH;

  x2 = end_node % TERRAIN_WIDTH;
  y2 = end_node / TERRAIN_WIDTH;

  x = x1;
  y = y1;

  // How many nodes did I move?
  delta_x = x2 - x1;
  delta_y = y2 - y1;

  // check the current node for collsions (if we are done, return)
  ASSERT((ai_terrain_check_list[start_node >> 3] & (0x00000001 << (start_node % 8))) == 0);
  ai_check_terrain_node(start_node, 1);
  if (delta_x == 0 && delta_y == 0)
    return true;

  // Do a Breshenham line algorithm
  if (delta_x < 0) {
    change_x = -1;
    delta_x = -delta_x;

  } else {
    change_x = 1;
  }

  if (delta_y < 0) {
    change_y = -1;
    delta_y = -delta_y;

  } else {
    change_y = 1;
  }

  error_term = 0;
  i = 1;

  if (delta_x < delta_y) {
    length = delta_y + 1;

    while (i < length) {
      y += change_y;
      error_term += delta_x;

      if (error_term >= delta_y) {
        x += change_x;
        error_term -= delta_y;
      }

      if (y >= TERRAIN_DEPTH || y < 0 || x < 0 || x >= TERRAIN_WIDTH) {
        return false;
      }

      // Check the current node for collisions
      cur_node = y * TERRAIN_WIDTH + x;
      if ((ai_terrain_check_list[cur_node >> 3] & (0x00000001 << (cur_node % 8))) == 0)
        ai_check_terrain_node(cur_node, 1);

      i++;
    }

  } else {
    length = delta_x + 1;

    while (i < length) {
      x += change_x;
      error_term += delta_y;

      if (error_term >= delta_x) {
        y += change_y;
        error_term -= delta_x;
      }

      if (y >= TERRAIN_DEPTH || y < 0 || x < 0 || x >= TERRAIN_WIDTH) {
        return false;
      }

      // Check the current node for collisions
      cur_node = y * TERRAIN_WIDTH + x;
      if ((ai_terrain_check_list[cur_node >> 3] & (0x00000001 << (cur_node % 8))) == 0)
        ai_check_terrain_node(cur_node, 1);

      i++;
    }
  }

  ASSERT(x == x2 && y == y2);

  return true;
}
