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

 * $Logfile: /DescentIII/main/bnode.h $
 * $Revision: 13 $
 * $Date: 5/06/99 5:18p $
 * $Author: Chris $
 *
 * BOA Helper Node structs and externs
 *
 * $Log: /DescentIII/main/bnode.h $
 *
 * 13    5/06/99 5:18p Chris
 * Updated the BNode system - vastly improved error checking and verify
 *
 * 12    5/03/99 12:56a 3dsmax
 * Knocked MAX_BNODES_PER_ROOM down to 127 after reading the comment about
 * a byte count in the portal struct.
 *
 * 11    5/03/99 12:50a 3dsmax
 * Changed MAX_BNODES_PER_ROOM from 100 to 200 for Luke. (MattT)
 *
 * 10    4/29/99 1:59a Chris
 * Added the portal blockage support
 *
 * 9     4/28/99 5:33a Chris
 * Further improved the BNode system.  (It actually works inside and
 * outside now)
 *
 * 8     4/27/99 3:01a Chris
 * Improving Bnode stuff
 *
 * 7     4/26/99 11:11a Chris
 * Updated Bnode system
 *
 * 6     4/25/99 9:02p Chris
 * Improving the Bnode system
 *
 * 5     4/18/99 4:35p Matt
 * Changed BNode_FreeRoom() to take a room pointer instead of a room
 * number, since it was being called for rooms in the scrap buffer, which
 * weren't in the room list.  Also added code to InitRoom() to init the
 * bnode data.
 *
 * 4     4/18/99 5:39a Chris
 * Vastly improved the path node system
 *
 * 3     4/15/99 5:48p Chris
 * Fixed a bug with rendering the BOAPath nodes
 *
 * 2     4/14/99 3:13p Chris
 * Beginning to add BoaNode stuff
 *
 * $NoKeywords: $
 */

#ifndef BNODE_H_
#define BNODE_H_

#include "vecmat_external.h"

#define MAX_BNODE_SIZE 20.0f
// Not bigger than 127 - char bnode - in portal struct
#define MAX_BNODES_PER_ROOM 127

struct bn_edge {
  int16_t end_room;
  char end_index;

  int16_t flags;
  int16_t cost;

  float max_rad;
};

struct bn_node {
  vector pos;
  int num_edges;
  bn_edge *edges;
};

struct bn_list {
  int num_nodes;
  bn_node *nodes;
};

struct room;

extern void BNode_FreeRoom(room *rp);
extern void BNode_ClearBNodeInfo(void);

bn_list *BNode_GetBNListPtr(int roomnum, bool f_in_load_level = false);

extern bn_list BNode_terrain_list[8];
extern bool BNode_allocated;
extern bool BNode_verified;
void BNode_RemapTerrainRooms(int old_hri, int new_hri);

extern int BNode_Path[MAX_BNODES_PER_ROOM];
extern int BNode_PathNumNodes;
extern bool BNode_FindPath(int start_room, int i, int j, float rad);
extern int BNode_FindDirLocalVisibleBNode(int roomnum, vector *pos, vector *fvec, float rad);
extern int BNode_FindClosestLocalVisibleBNode(int roomnum, vector *pos, float rad);

#endif
