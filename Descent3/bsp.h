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

 * $Logfile: /DescentIII/Main/bsp.h $
 * $Revision: 13 $
 * $Date: 4/19/00 5:30p $
 * $Author: Matt $
 *
 * Header for bsp.cpp
 *
 * $Log: /DescentIII/Main/bsp.h $
 *
 * 13    4/19/00 5:30p Matt
 * From Duane for 1.4
 * Added extern
 *
 * 12    4/14/99 3:56a Jeff
 * fixed case mismatch in #includes
 *
 * 11    9/22/98 12:01p Matt
 * Added SourceSafe headers
 *
 */

#ifndef BSP_H
#define BSP_H

#include "list.h"
#include "vecmat.h"
#include "cfile.h"

#define BSP_IN_FRONT 1
#define BSP_BEHIND 2
#define BSP_ON_PLANE 3
#define BSP_SPANNING 4
#define BSP_COINCIDENT 5

#define BSP_EPSILON .00005f

#define BSP_NODE 0
#define BSP_EMPTY_LEAF 1
#define BSP_SOLID_LEAF 2

struct bspplane {
  float a, b, c, d;
  uint8_t used;
};

struct bsppolygon {
  vector *verts;
  int nv;
  bspplane plane;

  int16_t roomnum;
  int16_t facenum;
  int8_t subnum;

  int color;

};

struct bspnode {
  uint8_t type;
  bspplane plane;
  uint16_t node_facenum;
  uint16_t node_roomnum;
  int8_t node_subnum;

  bspnode *front;
  bspnode *back;

  listnode *polylist;
  int num_polys;
};

struct bsptree {
  listnode *vertlist;
  listnode *polylist;
  bspnode *root;
};

// Builds a bsp tree for the indoor rooms
void BuildBSPTree();

// Runs a ray through the bsp tree
// Returns true if a ray is occludes
int BSPRayOccluded(vector *start, vector *end, bspnode *node);
int BSPReportStatus(vector *start, bspnode *node);

// Walks the BSP tree and frees up any nodes/polygons that we might be using
void DestroyBSPTree(bsptree *tree);

// Saves and BSP node to an open file and recurses with the nodes children
void SaveBSPNode(CFILE *outfile, bspnode *node);

// Loads a bsp node from an open file and recurses with its children
void LoadBSPNode(CFILE *infile, bspnode **node);

// Initializes some variables for the indoor bsp tree
void InitDefaultBSP();

// Destroy indoor bsp tree
void DestroyDefaultBSPTree();

// Builds a bsp tree for a single room
void BuildSingleBSPTree(int roomnum);

// Reports the current mine's checksum
int BSPGetMineChecksum();

extern bsptree MineBSP;
extern int BSPChecksum;
extern uint8_t BSP_initted;

#endif
