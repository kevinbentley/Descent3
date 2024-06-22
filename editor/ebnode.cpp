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

* $Logfile: /DescentIII/Main/editor/ebnode.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:57:37 $
* $Author: kevinb $
*
* BOA Helper Node functions
*
* $Log: not supported by cvs2svn $
 *
 * 35    10/24/99 7:27p Chris
 *
 * 34    10/24/99 7:22p Chris
 *
 * 33    10/24/99 5:19p Chris
 *
 * 32    9/03/99 10:02a Gwar
 * use special version of the verify graph function for NEWEDITOR (outputs
 * error info to a list dialog)
 *
 * 31    8/25/99 4:57p Gwar
 * added a way to select bnodes by clicking on them in the 3D views (for
 * NEWEDITOR)
 *
 * 30    8/20/99 4:26a Gwar
 * made EBNode_Draw use correct room number in NEWEDITOR
 *
 * 29    5/21/99 4:14p Chris
 * Improved verify
 *
 * 28    5/18/99 10:55p Chris
 * Improved the Bnode verification process
 *
 * 27    5/08/99 10:46p Chris
 * Default to not draw bnodes in the editor
 *
 * 26    5/06/99 5:18p Chris
 * Updated the BNode system - vastly improved error checking and verify
 *
 * 25    5/06/99 3:10p Chris
 * More mprintf in verify
 *
 * 23    5/02/99 11:30p Chris
 *
 * 22    5/02/99 8:20a Chris
 * Increased the min edge size
 *
 * 21    5/02/99 6:48a Chris
 * Got rid of zero length edges
 *
 * 20    5/02/99 6:16a Chris
 * Massive bnode error checking improvements
 *
 * 19    5/02/99 6:05a Chris
 *
 * 18    5/02/99 6:02a Chris
 *
 * 17    5/02/99 5:57a Chris
 *
 * 16    5/02/99 5:56a Chris
 *
 * 15    5/02/99 5:19a Chris
 * Vastly improved verify...
 *
 * 14    5/01/99 3:40p Chris
 * TOO_SMALL_FOR_ROBOT_PORTALS ARE THROWN OUT
 *
 * 13    4/29/99 10:16a Chris
 * Blocked portals where only being removed from the bnode list if they
 * where rendered!  (Oops)
 *
 * 12    4/29/99 1:59a Chris
 * Added the portal blockage support
 *
 * 11    4/28/99 9:17a Chris
 * Moving nodes now updates edge max_sizes
 *
 * 10    4/28/99 9:06a Chris
 * Improved the first pass of the BNodes
 *
 * 9     4/27/99 11:37p Chris
 * Improving the BNode system
 *
 * 8     4/27/99 3:01a Chris
 * Improving Bnode stuff
 *
 * 7     4/26/99 10:31p Chris
 * Improving the BNode system
 *
 * 6     4/26/99 11:11a Chris
 * Updated Bnode system
 *
 * 5     4/25/99 9:02p Chris
 * Improving the Bnode system
 *
 * 4     4/18/99 5:39a Chris
 * Vastly improved the path node system
 *
 * 3     4/15/99 5:49p Chris
 * Fixed a bug with rendering the BOAPath nodes
 *
 * 2     4/14/99 3:13p Chris
 * Beginning to add BoaNode stuff
*
* $NoKeywords: $
*/

#ifdef NEWEDITOR
#include "neweditor/stdafx.h"
#include "neweditor/NewEditor.h"
#endif

#include "bnode.h"
#include "room.h"
#include "mem.h"
#include "memory.h"
#include "vecmat.h"
#include "object.h"
#include "3d.h"
#include "ebnode.h"
#include "findintersection.h"
#include "pserror.h"
#include "terrain.h"
#include "boa.h"
#include "aimain.h"

char EBN_draw_type = EBDRAW_NONE;
#define EBN_MAX_NEXT_ROOMS 200

#define BNODE_VERY_CLOSE_DIST 5.0f

bool EBNode_VerifyGraph() {
  bool f_verified = true;
  int i;
  int j;
  int k;

  if (!BNode_allocated) {
    mprintf(0, "EBNode Verify: No BNodes for this level\n");
    return false;
  }

  MakeBOA();

  for (i = Highest_room_index + 1; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    bn_list *nlist;
    nlist = BNode_GetBNListPtr(i);
    int cur_region = i - Highest_room_index - 1;

    for (j = nlist->num_nodes - 1; j >= 0; j--) {
      int cell = GetTerrainRoomFromPos(&nlist->nodes[j].pos);
      if (cur_region != TERRAIN_REGION(cell)) {
        for (k = 0; k < nlist->nodes[j].num_edges; k++) {
          if (BOA_INDEX(nlist->nodes[j].edges[k].end_room) >= 0 &&
              BOA_INDEX(nlist->nodes[j].edges[k].end_room) <= Highest_room_index) {
            int r = nlist->nodes[j].edges[k].end_room;
            int p = nlist->nodes[j].edges[k].end_index;

            int x;
            for (x = 0; x < Rooms[r].num_portals; x++) {
              if (Rooms[r].portals[x].bnode_index == p) {
                int cr = Rooms[r].portals[x].croom;
                int cp = Rooms[r].portals[x].cportal;

                Rooms[cr].portals[cp].bnode_index = -1;
              }
            }
          }
        }

        EBNode_RemoveNode(i, j);
      }
    }
  }

  for (i = 0; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    bn_list *nlist;
    int j;
    int k;

    if (i >= 0 && i <= Highest_room_index && !Rooms[i].used)
      continue;

    if (i <= Highest_room_index && (Rooms[i].flags & RF_EXTERNAL))
      continue;

    nlist = BNode_GetBNListPtr(i);

    for (j = 0; j < nlist->num_nodes; j++) {
      for (k = 0; k < nlist->nodes[j].num_edges; k++) {
        if (nlist->nodes[j].edges[k].max_rad < 5.0f) {
          mprintf(0, "EBNode Verify: Removed a skinny edge.\n");
          EBNode_RemoveEdge(j, i, nlist->nodes[j].edges[k].end_index, nlist->nodes[j].edges[k].end_room);
          k--;
        }
      }
    }
  }

  // Bash invalid nodes
  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used) {
      room *rp = &Rooms[i];

      if (i <= Highest_room_index && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      for (j = 0; j < Rooms[i].num_portals; j++) {
        if (Rooms[i].portals[j].bnode_index >= 0 && Rooms[i].portals[j].bnode_index >= Rooms[i].bn_info.num_nodes) {
          mprintf(0, "EBNode: Bashed an invalid node\n");
          Rooms[i].portals[j].bnode_index = -1;
        } else if (Rooms[i].portals[j].bnode_index < 0) {
          room *rp = &Rooms[i];
          bool f_add = true;

          if (!((rp->portals[j].flags & PF_BLOCK) && !(rp->portals[j].flags & PF_BLOCK_REMOVABLE))) {
            f_add = false;
          }

          if ((rp->portals[j].flags & PF_RENDER_FACES) && !(rp->portals[j].flags & PF_RENDERED_FLYTHROUGH)) {
            if (!(GameTextures[rp->faces[rp->portals[j].portal_face].tmap].flags & (TF_BREAKABLE | TF_FORCEFIELD))) {
              f_add = false;
            }
          }

          if (rp->portals[j].flags & PF_TOO_SMALL_FOR_ROBOT) {
            f_add = false;
          }

          if (f_add) {
            vector pos;
            pos = rp->portals[j].path_pnt + rp->faces[rp->portals[j].portal_face].normal * 0.75f;
            rp->portals[j].bnode_index = EBNode_AddNode(i, &pos, false, false);
            mprintf(0, "EBNode Verify: Added a portal node\n");
          }
        }
      }
    }
  }

  int region;
  for (region = 0; region < BOA_num_terrain_regions; region++) {
    for (i = 0; i < BOA_num_connect[region]; i++) {
      int end_room = BOA_connect[region][i].roomnum;
      room *rp = &Rooms[end_room];
      int p = BOA_connect[region][i].portal;

      vector pos;
      pos = rp->portals[p].path_pnt - rp->faces[rp->portals[p].portal_face].normal * 0.75f;

      int external_room = rp->portals[p].croom;
      int external_portal = rp->portals[p].cportal;
      ASSERT(Rooms[external_room].flags & RF_EXTERNAL);

      if (Rooms[external_room].portals[external_portal].bnode_index < 0) {
        Rooms[external_room].portals[external_portal].bnode_index =
            EBNode_AddNode(Highest_room_index + region + 1, &pos, false, false);
        if (Rooms[end_room].portals[p].bnode_index >= 0)
          EBNode_AddEdge(Rooms[external_room].portals[external_portal].bnode_index, Highest_room_index + region + 1,
                         Rooms[end_room].portals[p].bnode_index, end_room);
      }
    }
  }

  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used) {
      room *rp = &Rooms[i];
      if (i <= Highest_room_index && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      for (j = 0; j < Rooms[i].num_portals; j++) {
        if ((Rooms[i].portals[j].flags & PF_BLOCK) && !(Rooms[i].portals[j].flags & PF_BLOCK_REMOVABLE)) {
          if (Rooms[i].portals[j].bnode_index >= 0) {
            mprintf(0, "EBNode Verify: Removed a node.\n");
            EBNode_RemoveNode(i, Rooms[i].portals[j].bnode_index);
          }
          continue;
        }

        if ((Rooms[i].portals[j].flags & PF_RENDER_FACES) && !(Rooms[i].portals[j].flags & PF_RENDERED_FLYTHROUGH)) {
          if (!(GameTextures[Rooms[i].faces[Rooms[i].portals[j].portal_face].tmap].flags &
                (TF_BREAKABLE | TF_FORCEFIELD))) {
            if (Rooms[i].portals[j].bnode_index >= 0) {
              mprintf(0, "EBNode Verify: Removed a node.\n");
              EBNode_RemoveNode(i, Rooms[i].portals[j].bnode_index);
            }
            continue;
          }
        }

        if (Rooms[i].portals[j].flags & PF_TOO_SMALL_FOR_ROBOT) {
          if (Rooms[i].portals[j].bnode_index >= 0) {
            mprintf(0, "EBNode Verify: Removed a node.\n");
            EBNode_RemoveNode(i, Rooms[i].portals[j].bnode_index);
          }
          continue;
        }

        if (Rooms[i].portals[j].bnode_index < 0) {
          if (Rooms[i].flags & RF_EXTERNAL) {
            int cr = rp->portals[j].croom;
            int ci = Rooms[cr].portals[rp->portals[j].cportal].bnode_index;

            if (Rooms[cr].flags & RF_EXTERNAL) {
              continue;
            }

            vector pos;
            pos = rp->portals[j].path_pnt + rp->faces[rp->portals[j].portal_face].normal * 0.75f;
            int roomnum = BOA_INDEX(GetTerrainRoomFromPos(&pos));

            int xxx;
            for (xxx = 0; xxx < BOA_num_connect[TERRAIN_REGION(roomnum)]; xxx++) {
              if (BOA_connect[TERRAIN_REGION(roomnum)][xxx].roomnum == cr &&
                  BOA_connect[TERRAIN_REGION(roomnum)][xxx].portal == rp->portals[j].cportal) {
                break;
              }
            }

            if (xxx >= BOA_num_connect[TERRAIN_REGION(roomnum)]) {
              mprintf(0, "EBNode Verify:  External room isn't in terrain region list\n");
              f_verified = false;
              continue;
            }

            rp->portals[j].bnode_index = EBNode_AddNode(roomnum, &pos, false, false);
            ASSERT(rp->portals[j].bnode_index >= 0);
            EBNode_AutoEdgeNode(rp->portals[j].bnode_index, roomnum);
            mprintf(0, "EBNode Verify: Added a node and autoedged it.\n");

            if (ci >= 0) {
              EBNode_AddEdge(rp->portals[j].bnode_index, roomnum, ci, cr);
            }
          } else {
            vector pos;
            pos = rp->portals[j].path_pnt + rp->faces[rp->portals[j].portal_face].normal * 0.75f;
            rp->portals[j].bnode_index = EBNode_AddNode(i, &pos, false, false);
            ASSERT(rp->portals[j].bnode_index >= 0);
            EBNode_AutoEdgeNode(rp->portals[j].bnode_index, i);
            mprintf(0, "EBNode Verify: Added a node and autoedged it.\n");

            int cr = rp->portals[j].croom;
            int ci = Rooms[cr].portals[rp->portals[j].cportal].bnode_index;

            if (ci < 0) {
              continue;
            }

            if (Rooms[cr].flags & RF_EXTERNAL) {
              vector pos;
              pos = rp->portals[j].path_pnt - rp->faces[rp->portals[j].portal_face].normal * 0.75f;
              int roomnum = BOA_INDEX(GetTerrainRoomFromPos(&pos));

              EBNode_AddEdge(rp->portals[j].bnode_index, i, ci, roomnum);
            } else {
              if (ci >= 0) {
                EBNode_AddEdge(rp->portals[j].bnode_index, i, ci, cr);
              }
            }
          }
        }
      }
    }
  }

  for (i = 0; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    bn_list *nlist;
    int j;
    int k;

    if (i >= 0 && i <= Highest_room_index && !Rooms[i].used)
      continue;

    if (i >= 0 && i <= Highest_room_index && (Rooms[i].flags & RF_EXTERNAL))
      continue;

    nlist = BNode_GetBNListPtr(i);

    for (j = 0; j < nlist->num_nodes; j++) {
      for (k = 0; k < nlist->nodes[j].num_edges; k++) {
        if (nlist->nodes[j].edges[k].max_rad < 5.0f) {
          mprintf(0, "EBNode Verify: Removed a skinny edge.\n");
          EBNode_RemoveEdge(j, i, nlist->nodes[j].edges[k].end_index, nlist->nodes[j].edges[k].end_room);
          k--;
        }
      }

      for (k = 0; k < nlist->nodes[j].num_edges; k++) {
        if (nlist->nodes[j].edges[k].end_room <= Highest_room_index && !Rooms[nlist->nodes[j].edges[k].end_room].used) {
          mprintf(0, "EBNode Verify: Removed a edge to a non-existant room. Room %d, node %d, edge %d\n", i, j, k);
          EBNode_RemoveEdge(j, i, nlist->nodes[j].edges[k].end_index, nlist->nodes[j].edges[k].end_room);
          k--;
        }
      }
    }
  }

  for (i = 0; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    bn_list *nlist;
    int j;
    int k;

    if (i >= 0 && i <= Highest_room_index && !Rooms[i].used)
      continue;

    if (i >= 0 && i <= Highest_room_index && (Rooms[i].flags & RF_EXTERNAL))
      continue;

    nlist = BNode_GetBNListPtr(i);

    for (j = 0; j < nlist->num_nodes; j++) {
      for (k = 0; k < nlist->nodes[j].num_edges; k++) {
        if (nlist->nodes[j].edges[k].max_rad < 5.0f) {
          mprintf(0, "Skinny Edge - from r%d n%d to r%d n%d\n", i, j, nlist->nodes[j].edges[k].end_room,
                  nlist->nodes[j].edges[k].end_index);
          f_verified = false;
        }
      }
    }
  }

  for (i = 0; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    if (i >= 0 && i <= Highest_room_index && !Rooms[i].used)
      continue;

    if (i >= 0 && i <= Highest_room_index && (Rooms[i].flags & RF_EXTERNAL))
      continue;

    bn_list *nlist = BNode_GetBNListPtr(i);
    ASSERT(nlist);

    for (j = 0; j < nlist->num_nodes; j++) {
      for (k = j + 1; k < nlist->num_nodes; k++) {
        if (!BNode_FindPath(i, j, k, 0.0f)) {
          mprintf(0, "BNODE ERROR: No path from %d to %d in room %d\n", j + 1, k + 1, i);
          f_verified = false;
        }
      }
    }
  }

  BNode_verified = f_verified;

  if (f_verified)
    mprintf(0, "EBNode:  VERIFY OK!\n");
  else
    mprintf(0, "EBNode:  VERIFY FAILED!\n");

  return f_verified;
}

void EBNode_ClearLevel() {
  int i, j;

  for (i = 0; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    if (i >= 0 && i <= Highest_room_index) {
      if (!Rooms[i].used) {
        continue;
      } else {
        int j;

        for (j = 0; j < Rooms[i].num_portals; j++) {
          Rooms[i].portals[j].bnode_index = -1;
        }
      }
    }

    bn_list *nlist;
    nlist = BNode_GetBNListPtr(i);

    ASSERT(nlist);

    for (j = nlist->num_nodes - 1; j >= 0; j--) {
      if (nlist->nodes[j].edges) {
        mem_free(nlist->nodes[j].edges);
      }
      nlist->nodes[j].edges = NULL;
      nlist->nodes[j].num_edges = 0;
    }

    if (nlist->nodes) {
      mem_free(nlist->nodes);
    }
    nlist->nodes = NULL;
    nlist->num_nodes = 0;
  }

  BNode_allocated = false;
  BNode_verified = false;
}

void RemapEdgeNodesEqualAndAbove(int croom, int sroom, int spnt) {
  int i;
  int j;

  bn_list *cnlist;
  cnlist = BNode_GetBNListPtr(croom);
  if (!cnlist)
    return;

  for (i = 0; i < cnlist->num_nodes; i++) {
    for (j = 0; j < cnlist->nodes[i].num_edges; j++) {
      if (cnlist->nodes[i].edges[j].end_room == sroom && cnlist->nodes[i].edges[j].end_index >= spnt) {
        // The assert is because all these edges should have been deleted!
        ASSERT(cnlist->nodes[i].edges[j].end_index != spnt);
        cnlist->nodes[i].edges[j].end_index--;
      }
    }
  }
}

void RemapPortalNodeIndices(int roomnum, int pnt) {
  int i;

  if (roomnum >= 0 && roomnum <= Highest_room_index) {
    ASSERT(Rooms[roomnum].used);

    for (i = 0; i < Rooms[roomnum].num_portals; i++) {
      if (Rooms[roomnum].portals[i].bnode_index == pnt) {
        Rooms[roomnum].portals[i].bnode_index = -1;
      } else if (Rooms[roomnum].portals[i].bnode_index > pnt) {
        Rooms[roomnum].portals[i].bnode_index--;
      }
    }
  } else {
    int region = BOA_INDEX(roomnum) - Highest_room_index - 1;

    for (i = 0; i < BOA_num_connect[region]; i++) {
      int r = BOA_connect[region][i].roomnum;
      int p = BOA_connect[region][i].portal;

      int cr = Rooms[r].portals[p].croom;
      int cp = Rooms[r].portals[p].cportal;

      vector pos = Rooms[cr].portals[cp].path_pnt + Rooms[cr].faces[Rooms[cr].portals[cp].portal_face].normal * 0.75f;
      int cell = GetTerrainRoomFromPos(&pos);

      if (region == TERRAIN_REGION(cell) && Rooms[cr].portals[cp].bnode_index == pnt) {
        Rooms[cr].portals[cp].bnode_index = -1;
      }
    }
  }
}

void EBNode_RemoveNode(int roomnum, int pnt) {
  int i;

  BNode_verified = false;

  bn_list *nlist;
  nlist = BNode_GetBNListPtr(roomnum);
  if (!nlist)
    return;

  ASSERT(pnt >= 0 && pnt < nlist->num_nodes);

  // Remove all connects to the world...
  for (i = nlist->nodes[pnt].num_edges - 1; i >= 0; i--) {
    EBNode_RemoveEdge(pnt, roomnum, nlist->nodes[pnt].edges[i].end_index, nlist->nodes[pnt].edges[i].end_room);
  }

  // Copy the nodes down the list
  for (i = pnt; i < nlist->num_nodes - 1; i++) {
    nlist->nodes[i] = nlist->nodes[i + 1];
  }

  nlist->num_nodes--;

  if (nlist->num_nodes == 0) {
    mem_free(nlist->nodes);
    nlist->nodes = NULL;
  } else {
    nlist->nodes = (bn_node *)mem_realloc(nlist->nodes, sizeof(bn_node) * nlist->num_nodes);
  }

  // Not super efficient, but works.  :)
  int next_rooms[1000];
  int num_next_rooms = AIMakeNextRoomList(roomnum, next_rooms, 1000);

  for (i = 0; i < num_next_rooms; i++) {
    RemapEdgeNodesEqualAndAbove(next_rooms[i], roomnum, pnt);
  }
  RemapEdgeNodesEqualAndAbove(roomnum, roomnum, pnt);
  RemapPortalNodeIndices(roomnum, pnt);
}

void EBNode_RemoveEdge(int spnt, int sroom, int epnt, int eroom, bool f_remove_reverse) {
  int i;

  BNode_verified = false;

  // Make sure there are no zero length paths
  if (sroom == eroom && spnt == epnt) {
    return;
  }

  bn_list *snlist;
  snlist = BNode_GetBNListPtr(sroom);
  bn_list *enlist;
  enlist = BNode_GetBNListPtr(eroom);

  if (!snlist)
    return;

  bool f_exists = false;
  int e_index;

  // Check to see if this edge already exists
  for (i = 0; i < snlist->nodes[spnt].num_edges; i++) {
    if (snlist->nodes[spnt].edges[i].end_index == epnt && snlist->nodes[spnt].edges[i].end_room == eroom) {
      e_index = i;
      f_exists = true;
      break;
    }
  }

  ASSERT(f_exists);

  // Copy the edges down the list
  for (i = e_index; i < snlist->nodes[spnt].num_edges - 1; i++) {
    snlist->nodes[spnt].edges[i] = snlist->nodes[spnt].edges[i + 1];
  }

  snlist->nodes[spnt].num_edges--;

  if (snlist->nodes[spnt].num_edges == 0) {
    mem_free(snlist->nodes[spnt].edges);
    snlist->nodes[spnt].edges = NULL;
  } else {
    snlist->nodes[spnt].edges =
        (bn_edge *)mem_realloc(snlist->nodes[spnt].edges, sizeof(bn_edge) * snlist->nodes[spnt].num_edges);
  }

  if (f_remove_reverse && enlist) {
    EBNode_RemoveEdge(epnt, eroom, spnt, sroom, false);
  }
}

int EBNode_AddNode(int roomnum, vector *pnt, bool f_from_editor, bool f_check_for_close_nodes) {
  bn_list *nlist;
  nlist = BNode_GetBNListPtr(roomnum);
  if (!nlist)
    return -1;

  BNode_verified = false;

  if (nlist->num_nodes >= MAX_BNODES_PER_ROOM) {
#ifndef NEWEDITOR
    OutrageMessageBox("Too many BOA Nodes for this room/region.\nGet Chris if you need more nodes.");
#else
    OutrageMessageBox("Too many BOA Nodes for this room/region.");
#endif
    return -1;
  }

  int i;
  bool f_really_close_neighbor = false;
  int new_node;

  if (f_check_for_close_nodes) {
    for (i = 0; i < nlist->num_nodes; i++) {
      float min_dist = 0.0f;

      if (f_check_for_close_nodes) {
        min_dist = BNODE_VERY_CLOSE_DIST;
      }

      if (vm_VectorDistance(&nlist->nodes[i].pos, pnt) <= min_dist) {
        f_really_close_neighbor = true;
        break;
      }
    }

    if (f_really_close_neighbor) {
      if (f_from_editor) {
#ifndef NEWEDITOR
        OutrageMessageBox(
            "This node is really close to another one and isn't needed.\nSee Chris if this is a problem.");
#else
        OutrageMessageBox("This node is really close to another one and isn't needed.");
#endif
      }

      return -1;
    }
  }
  // Makes sure that if there are no nodes, then the node pointer is NULL and that if
  // there are nodes that the node pointer isn't NULL
  ASSERT(!((nlist->num_nodes == 0) ^ (nlist->nodes == NULL)));

  new_node = nlist->num_nodes;
  nlist->num_nodes++;

  if (new_node != 0)
    nlist->nodes = (bn_node *)mem_realloc(nlist->nodes, sizeof(bn_node) * (nlist->num_nodes));
  else
    nlist->nodes = (bn_node *)mem_malloc(sizeof(bn_node));

  nlist->nodes[new_node].edges = NULL;
  nlist->nodes[new_node].num_edges = 0;
  nlist->nodes[new_node].pos = *pnt;

  return new_node;
}

int EBNode_InsertNodeOnEdge(int spnt, int sroom, int epnt, int eroom) {
  int i;

  BNode_verified = false;

  bn_list *snlist;
  snlist = BNode_GetBNListPtr(sroom);
  bn_list *enlist;
  enlist = BNode_GetBNListPtr(eroom);

  bool f_exists = false;
  int e_index;

  // Check to see if this edge already exists
  for (i = 0; i < snlist->nodes[spnt].num_edges; i++) {
    if (snlist->nodes[spnt].edges[i].end_index == epnt && snlist->nodes[spnt].edges[i].end_room == eroom) {
      e_index = i;
      f_exists = true;
      break;
    }
  }

  ASSERT(f_exists);

  vector new_pos = (snlist->nodes[spnt].pos + enlist->nodes[epnt].pos) / 2.0f;
  fvi_info hit_info;
  hit_info.hit_room = sroom;

  if (sroom != eroom) {
    fvi_query fq;
    int fate;

    // shoot a ray from the light position to the current vertex
    fq.p0 = &snlist->nodes[spnt].pos;
    fq.p1 = &enlist->nodes[epnt].pos;
    fq.startroom = (sroom > Highest_room_index && sroom <= Highest_room_index + 8)
                       ? GetTerrainRoomFromPos(&snlist->nodes[spnt].pos)
                       : sroom;

    fq.rad = 0.0f;
    fq.flags = FQ_IGNORE_RENDER_THROUGH_PORTALS;
    fq.thisobjnum = -1;
    fq.ignore_obj_list = NULL;

    fate = fvi_FindIntersection(&fq, &hit_info);

    if (fate != HIT_NONE) {
      OutrageMessageBox("You can only do this function if the 2 nodes can\nsee each other or are in the same room.\n");
      return -1;
    }
  }

  int n_index = EBNode_AddNode(hit_info.hit_room, &new_pos, false, false);
  EBNode_AddEdge(n_index, hit_info.hit_room, spnt, sroom);
  EBNode_AddEdge(n_index, hit_info.hit_room, epnt, eroom);

  EBNode_RemoveEdge(epnt, eroom, spnt, sroom);

  return n_index;
}

float EBNode_DetermineMaxSizeForEdge(int spnt, int sroom, int epnt, int eroom) {
  bn_list *snlist;
  snlist = BNode_GetBNListPtr(sroom);
  bn_list *enlist;
  enlist = BNode_GetBNListPtr(eroom);

  float size = 0.0f;
  fvi_info hit_info;
  fvi_query fq;
  int fate;

  // shoot a ray from the light position to the current vertex
  fq.flags = FQ_IGNORE_RENDER_THROUGH_PORTALS;
  fq.thisobjnum = -1;
  fq.ignore_obj_list = NULL;

  do {
    fq.p0 = &snlist->nodes[spnt].pos;
    fq.p1 = &enlist->nodes[epnt].pos;
    fq.startroom = (sroom > Highest_room_index && sroom <= Highest_room_index + 8)
                       ? GetTerrainRoomFromPos(&snlist->nodes[spnt].pos)
                       : sroom;
    fq.rad = size;

    fate = fvi_FindIntersection(&fq, &hit_info);

    if (fate == HIT_NONE) {
      fq.p0 = &enlist->nodes[epnt].pos;
      fq.p1 = &snlist->nodes[spnt].pos;
      fq.startroom = (eroom > Highest_room_index && eroom <= Highest_room_index + 8)
                         ? GetTerrainRoomFromPos(&enlist->nodes[epnt].pos)
                         : eroom;
      fq.rad = size;

      fate = fvi_FindIntersection(&fq, &hit_info);
    }

    if (fate == HIT_NONE) {
      size += 1.0f;
    }
  } while (fate == HIT_NONE && size < MAX_BNODE_SIZE + 1.0f);

  return (size - 1.0f);
}

void EBNode_AutoEdgeNode(int spnt, int sroom) {
  BNode_verified = false;

  bn_list *snlist;
  snlist = BNode_GetBNListPtr(sroom);

  int i;

  for (i = 0; i < snlist->num_nodes; i++) {
    if (i != spnt) {
      fvi_info hit_info;
      fvi_query fq;

      // check to make sure it is still in the room and valid
      fq.p0 = &snlist->nodes[spnt].pos;
      fq.p1 = &snlist->nodes[i].pos;
      fq.startroom = (sroom > Highest_room_index && sroom <= Highest_room_index + 8)
                         ? GetTerrainRoomFromPos(&snlist->nodes[spnt].pos)
                         : sroom;

      fq.rad = 3.0f;
      fq.flags = FQ_NO_RELINK;
      fq.thisobjnum = -1;
      fq.ignore_obj_list = NULL;

      if (fvi_FindIntersection(&fq, &hit_info) == HIT_NONE) {
        EBNode_AddEdge(spnt, sroom, i, sroom);
      }
    }
  }
}

void EBNode_AddEdge(int spnt, int sroom, int epnt, int eroom, bool f_add_reverse, float computed_max_rad) {
  int i;

  BNode_verified = false;

  // Make sure there are no zero length paths
  if (sroom == eroom && spnt == epnt) {
    return;
  }

  bn_list *snlist;
  snlist = BNode_GetBNListPtr(sroom);
  bn_list *enlist;
  enlist = BNode_GetBNListPtr(eroom);

  ASSERT(snlist && enlist);

  bool f_exists = false;

  // Check to see if this edge already exists
  for (i = 0; i < snlist->nodes[spnt].num_edges; i++) {
    if (snlist->nodes[spnt].edges[i].end_index == epnt && snlist->nodes[spnt].edges[i].end_room == eroom) {
      f_exists = true;
      break;
    }
  }

  if (!f_exists) {
    int new_edge;

    // Makes sure that if there are no edges, then the edge pointer is NULL and that if
    // there are edges that the edge pointer isn't NULL
    ASSERT(!((snlist->nodes[spnt].num_edges == 0) ^ (snlist->nodes[spnt].edges == NULL)));

    new_edge = snlist->nodes[spnt].num_edges;
    snlist->nodes[spnt].num_edges++;

    if (new_edge == 0) {
      snlist->nodes[spnt].edges = (bn_edge *)mem_malloc(sizeof(bn_edge));
    } else {
      snlist->nodes[spnt].edges =
          (bn_edge *)mem_realloc(snlist->nodes[spnt].edges, sizeof(bn_edge) * snlist->nodes[spnt].num_edges);
    }

    float cost = vm_VectorDistance(&snlist->nodes[spnt].pos, &enlist->nodes[epnt].pos);
    if (cost < 1.0f)
      cost = 1.0f;

    snlist->nodes[spnt].edges[new_edge].cost = (cost < 32767.0f) ? (int16_t)cost : (int16_t)32767;
    snlist->nodes[spnt].edges[new_edge].end_index = epnt;
    snlist->nodes[spnt].edges[new_edge].end_room = BOA_INDEX(eroom);
    snlist->nodes[spnt].edges[new_edge].flags = 0;

    if (f_add_reverse) {
      snlist->nodes[spnt].edges[new_edge].max_rad = EBNode_DetermineMaxSizeForEdge(spnt, sroom, epnt, eroom);
      EBNode_AddEdge(epnt, eroom, spnt, sroom, false, snlist->nodes[spnt].edges[new_edge].max_rad);
    } else {
      snlist->nodes[spnt].edges[new_edge].max_rad = computed_max_rad;
    }
  }
}

void EBNode_MakeDefaultIntraRoomNodes(int roomnum) {
  int i, j;

  room *rp = &Rooms[roomnum];

  // Adds the nodes from portals
  for (i = 0; i < rp->num_portals; i++) {
    vector pos;
    pos = rp->portals[i].path_pnt + rp->faces[rp->portals[i].portal_face].normal * 0.75f;
    rp->portals[i].bnode_index = i;

    EBNode_AddNode(roomnum, &pos, false, false);
  }

  // Adds a node for centerpoint of the room
  EBNode_AddNode(roomnum, &rp->path_pnt, false, false);

  // Add the edges
  for (i = 0; i < rp->bn_info.num_nodes; i++) {
    // Edges go both ways - always
    for (j = i + 1; j < rp->bn_info.num_nodes; j++) {
      // Check to see if the center is really close to this edge, if so - Dont make this edge
      if (i < rp->bn_info.num_nodes - 1 && j < rp->bn_info.num_nodes - 1) {
        vector vec = rp->portals[j].path_pnt - rp->portals[i].path_pnt;
        vector cvec = rp->path_pnt - rp->portals[i].path_pnt;

        float len = vm_NormalizeVector(&vec);
        float cproj = cvec * vec;

        if (len >= cproj && cproj >= 0.0f) {
          vector cxline = cproj * vec;
          vector dvec = rp->path_pnt - (rp->portals[i].path_pnt + cxline);

          if (vm_GetMagnitude(&dvec) < 3.0f) {
            continue;
          }
        }
      }

      fvi_info hit_info;
      fvi_query fq;

      // check to make sure it is still in the room and valid
      fq.p0 = &Rooms[roomnum].bn_info.nodes[i].pos;
      fq.p1 = &Rooms[roomnum].bn_info.nodes[j].pos;
      fq.startroom = (roomnum > Highest_room_index && roomnum <= Highest_room_index + 8)
                         ? GetTerrainRoomFromPos(&Rooms[roomnum].bn_info.nodes[i].pos)
                         : roomnum;

      fq.rad = 0.1f;
      fq.flags = FQ_SOLID_PORTALS | FQ_NO_RELINK;
      fq.thisobjnum = -1;
      fq.ignore_obj_list = NULL;

      if (fvi_FindIntersection(&fq, &hit_info) != HIT_NONE) {
        continue;
      }

      EBNode_AddEdge(i, roomnum, j, roomnum);
    }
  }
}

void EBNode_MakeDefaultInterRoomEdges(int roomnum) {
  int i;

  for (i = 0; i < Rooms[roomnum].num_portals; i++) {
    if (Rooms[roomnum].portals[i].cportal >= 0 && Rooms[roomnum].portals[i].croom > roomnum &&
        !(Rooms[Rooms[roomnum].portals[i].croom].flags & RF_EXTERNAL)) {
      if ((Rooms[roomnum].portals[i].flags & PF_RENDER_FACES) &&
          !(Rooms[roomnum].portals[i].flags & PF_RENDERED_FLYTHROUGH)) {
        if (!(GameTextures[Rooms[roomnum].faces[Rooms[roomnum].portals[i].portal_face].tmap].flags &
              (TF_BREAKABLE | TF_FORCEFIELD))) {
          continue;
        }
      }

      EBNode_AddEdge(i, roomnum, Rooms[roomnum].portals[i].cportal, Rooms[roomnum].portals[i].croom);
    }
  }
}

void EBNode_RemoveNodesAtUnopenablePortals(int roomnum) {
  int i;

  ASSERT(Rooms[roomnum].num_portals + 1 == Rooms[roomnum].bn_info.num_nodes);

  for (i = Rooms[roomnum].num_portals - 1; i >= 0; i--) {
    if ((Rooms[roomnum].portals[i].flags & PF_BLOCK) && !(Rooms[roomnum].portals[i].flags & PF_BLOCK_REMOVABLE)) {
      EBNode_RemoveNode(roomnum, i);
      continue;
    }

    if ((Rooms[roomnum].portals[i].flags & PF_RENDER_FACES) &&
        !(Rooms[roomnum].portals[i].flags & PF_RENDERED_FLYTHROUGH)) {
      if (!(GameTextures[Rooms[roomnum].faces[Rooms[roomnum].portals[i].portal_face].tmap].flags &
            (TF_BREAKABLE | TF_FORCEFIELD))) {
        EBNode_RemoveNode(roomnum, i);
        continue;
      }
    }

    if (Rooms[roomnum].portals[i].flags & PF_TOO_SMALL_FOR_ROBOT) {
      EBNode_RemoveNode(roomnum, i);
      continue;
    }
  }
}

// void EBNode_VerifyGraph()
//{
/*	int i;
        int j;
        int k;
        int l;

        for(i = 0; i <= Highest_room_index; i++)
        {
                if(Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL))
                {
                        room *rp = &Rooms[i];

                        for(j = 0; j < rp->bn_info.num_nodes; j++)
                        {
                                for(k = 0; k < rp->bn_info.nodes[j].num_edges; k++)
                                {
                                        ASSERT(!(rp->bn_info.nodes[j].edges[k].end_room == i &&
   rp->bn_info.nodes[j].edges[k].end_index == j));

                                        bool f_found = false;

                                        for(l = 0; l <
   Rooms[rp->bn_info.nodes[j].edges[k].end_room].bn_info.nodes[rp->bn_info.nodes[j].edges[k].end_index].num_edges; l++)
                                        {
                                                if(Rooms[rp->bn_info.nodes[j].edges[k].end_room].bn_info.nodes[rp->bn_info.nodes[j].edges[k].end_index].edges[l].end_room
   == i &&
                                                        Rooms[rp->bn_info.nodes[j].edges[k].end_room].bn_info.nodes[rp->bn_info.nodes[j].edges[k].end_index].edges[l].end_index
   == j)
                                                {
                                                        f_found = true;
                                                        break;
                                                }
                                        }

                                        ASSERT(f_found);

                                        for(l = 0; l < rp->bn_info.nodes[j].num_edges; l++)
                                        {
                                                if(l != k)
                                                {
                                                        ASSERT(!(rp->bn_info.nodes[j].edges[k].end_room ==
   rp->bn_info.nodes[j].edges[l].end_room && rp->bn_info.nodes[j].edges[k].end_index ==
   rp->bn_info.nodes[j].edges[l].end_index));
                                                }
                                        }
                                }
                        }
                }
        }
*/
//}

void EBNode_MakeDefaultTerrainNodes(int region) {
  int i, j;

  ASSERT(region >= 0 || region < BOA_num_terrain_regions);

  mprintf(0, "TR %d has %d nodes\n", region, BOA_num_connect[region]);

  // Adds the nodes from portals
  for (i = 0; i < BOA_num_connect[region]; i++) {
    int end_room = BOA_connect[region][i].roomnum;
    room *rp = &Rooms[end_room];
    int p = BOA_connect[region][i].portal;

    vector pos;
    pos = rp->portals[p].path_pnt - rp->faces[rp->portals[p].portal_face].normal * 0.75f;

    int external_room = rp->portals[p].croom;
    int external_portal = rp->portals[p].cportal;
    ASSERT(Rooms[external_room].flags & RF_EXTERNAL);
    Rooms[external_room].portals[external_portal].bnode_index = i;

    EBNode_AddNode(Highest_room_index + region + 1, &pos, false, false);
    EBNode_AddEdge(i, Highest_room_index + region + 1, p, end_room);
  }

  // Add the edges
  for (i = 0; i < BOA_num_connect[region]; i++) {
    // Edges go both ways - always
    for (j = i + 1; j < BOA_num_connect[region]; j++) {
      EBNode_AddEdge(i, Highest_room_index + region + 1, j, Highest_room_index + region + 1);
    }
  }
}

void EBNode_MakeFirstPass(void) {
  int i;

  if (BNode_allocated) {
    OutrageMessageBox("The BNode system is already made.\nUse the other functions to modify the graph.");
    return;
  }

  for (i = 0; i <= Highest_room_index; i++) {
    ASSERT(Rooms[i].bn_info.num_nodes == 0);

    if (Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL)) {
      EBNode_MakeDefaultIntraRoomNodes(i);
    }
  }

  for (i = 0; i < BOA_num_terrain_regions; i++) {
    ASSERT(BNode_terrain_list[i].num_nodes == 0);
    EBNode_MakeDefaultTerrainNodes(i);
  }

  // This function assumes that Node(X) goes to Portal(X)
  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL)) {
      EBNode_MakeDefaultInterRoomEdges(i);
    }
  }

  // This function assumes that Node(X) goes to Portal(X)
  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL)) {
      EBNode_RemoveNodesAtUnopenablePortals(i);
    }
  }

  for (i = 0; i <= Highest_room_index + BOA_num_terrain_regions; i++) {
    bn_list *nlist;
    int j;
    int k;

    if (i >= 0 && i <= Highest_room_index && !Rooms[i].used)
      continue;

    nlist = BNode_GetBNListPtr(i);

    for (j = 0; j < nlist->num_nodes; j++) {
      for (k = 0; k < nlist->nodes[j].num_edges; k++) {
        if (nlist->nodes[j].edges[k].max_rad < 5.0f) {
          EBNode_RemoveEdge(j, i, nlist->nodes[j].edges[k].end_index, nlist->nodes[j].edges[k].end_room);
          k--;
        }
      }
    }
  }

  BNode_allocated = true;
#ifndef NEWEDITOR
  EBNode_VerifyGraph();
#else
  bool ned_EBNode_VerifyGraph();
  ned_EBNode_VerifyGraph();
#endif
}

#ifndef NEWEDITOR
#include "editor/d3edit.h"
#else
#include "neweditor/globals.h"
#include "terrain.h"
#include "renderer.h"
#endif

#include "gr.h"
#include "epath.h"

void EBNode_DrawRoom(int room, grViewport *vp, vector *viewer_eye, matrix *viewer_orient, float zoom,
                     bool f_current_room = false) {
  int i, current_path_index = 0, t;
  g3Point rot_points[300];
  int sort_index[300];

  bn_list *bn_info = BNode_GetBNListPtr(room);

  for (i = 0; i < bn_info->num_nodes; i++) {
    //		int curnode=D3EditState.current_node;
    //
    g3_RotatePoint(&rot_points[0], &bn_info->nodes[i].pos);
    sort_index[0] = 0;

    for (t = 0; t < bn_info->nodes[i].num_edges; t++) {

      bn_list *ebn_info = BNode_GetBNListPtr(bn_info->nodes[i].edges[t].end_room);

      g3_RotatePoint(&rot_points[t + 1], &ebn_info->nodes[bn_info->nodes[i].edges[t].end_index].pos);
      sort_index[t + 1] = t + 1;
    }

    //		ddgr_color path_color = (current_path_index==D3EditState.current_path) ? GR_RGB(255,255,255) :
    //GR_RGB(36,99,238);
    ddgr_color path_color;

    if (f_current_room)
      path_color = GR_RGB(255, 0, 0);
    else
      path_color = GR_RGB(100, 0, 0);

    int x;
    g3Point p1 = rot_points[0];

    for (x = 0; x < bn_info->nodes[i].num_edges; x++) {
      g3Point p2 = rot_points[x + 1];
      g3_DrawLine(path_color, &p1, &p2);
    }

    for (t = 0; t < bn_info->nodes[i].num_edges + 1; t++) {
      for (int k = 0; k < bn_info->nodes[i].num_edges + 1; k++) {
        if (rot_points[k].p3_vec.z < rot_points[t].p3_vec.z) {
          g3Point temp;
          int tindex;

          memcpy(&temp, &rot_points[t], sizeof(g3Point));
          memcpy(&rot_points[t], &rot_points[k], sizeof(g3Point));
          memcpy(&rot_points[k], &temp, sizeof(g3Point));

          tindex = sort_index[t];
          sort_index[t] = sort_index[k];
          sort_index[k] = tindex;
        }
      }
    }
  }

  int color;
  float size;

  if (f_current_room) {
    color = GR_RGB(0, 128, 160);
    size = 0.7f;
  } else {
    color = GR_RGB(0, 64, 80);
    size = 0.5f;
  }

  for (i = 0; i < bn_info->num_nodes; i++) {
    g3_RotatePoint(&rot_points[0], &bn_info->nodes[i].pos);

#ifdef NEWEDITOR
    ddgr_color oldcolor;

    if (TSearch_on) {
      rend_SetPixel(GR_RGB(16, 255, 16), TSearch_x, TSearch_y);
      oldcolor = rend_GetPixel(TSearch_x, TSearch_y);
    }
#endif

    g3_DrawSphere(color, &rot_points[0], size);

#ifdef NEWEDITOR
    if (TSearch_on) {
      if (rend_GetPixel(TSearch_x, TSearch_y) != oldcolor) {
        TSearch_found_type = TSEARCH_FOUND_BNODE;
        TSearch_seg = room;
        TSearch_face = i;
      }
    }
#endif

    DrawNumber(i + 1, bn_info->nodes[i].pos, size * .5);
  }
}

void EBNode_ComputeEdgeCosts(int sroom, int spnt, int eroom, int epnt) {
  int i, j;
  bool f_found = false;

  bn_list *snlist;
  snlist = BNode_GetBNListPtr(sroom);
  bn_list *enlist;
  enlist = BNode_GetBNListPtr(eroom);

  for (i = 0; i < snlist->nodes[spnt].num_edges; i++) {
    for (j = 0; j < enlist->nodes[epnt].num_edges; j++) {
      if ((snlist->nodes[spnt].edges[i].end_index == epnt && snlist->nodes[spnt].edges[i].end_room == eroom) &&
          (enlist->nodes[epnt].edges[j].end_index == spnt && enlist->nodes[epnt].edges[j].end_room == sroom)) {
        f_found = true;

        float cost = vm_VectorDistance(&snlist->nodes[spnt].pos, &enlist->nodes[epnt].pos);
        if (cost < 1.0f)
          cost = 1.0f;

        int16_t scost = (cost < 32767.0f) ? (int16_t)cost : (int16_t)32767;

        snlist->nodes[spnt].edges[i].cost = scost;
        enlist->nodes[epnt].edges[j].cost = scost;

        snlist->nodes[spnt].edges[i].max_rad = enlist->nodes[epnt].edges[j].max_rad =
            EBNode_DetermineMaxSizeForEdge(spnt, sroom, epnt, eroom);
      }
    }
  }

  ASSERT(f_found == true); // If you get this -- Get Chris!!!!!!!
}

void EBNode_Move(bool f_offset, int roomnum, int pnt, vector *pos) {
  bn_list *nlist;
  nlist = BNode_GetBNListPtr(roomnum);

  int i;
  vector npos = *pos;

  if (f_offset) {
    npos += nlist->nodes[pnt].pos;

    fvi_info hit_info;
    fvi_query fq;

    // check to make sure it is still in the room and valid
    fq.p0 = &nlist->nodes[pnt].pos;
    fq.p1 = &npos;
    fq.startroom = (roomnum > Highest_room_index && roomnum <= Highest_room_index + 8)
                       ? GetTerrainRoomFromPos(&nlist->nodes[pnt].pos)
                       : roomnum;

    fq.rad = 0.25f;
    fq.flags =
        FQ_SOLID_PORTALS | FQ_NO_RELINK; // chrishack -- Might want to make FQ_IGNORE_MOVING_OBJECTS into a passed arg
    fq.thisobjnum = -1;
    fq.ignore_obj_list = NULL;

    fvi_FindIntersection(&fq, &hit_info);

    npos = hit_info.hit_pnt;
  }

  nlist->nodes[pnt].pos = npos;

  for (i = 0; i < nlist->nodes[pnt].num_edges; i++) {
    EBNode_ComputeEdgeCosts(roomnum, pnt, nlist->nodes[pnt].edges[i].end_room, nlist->nodes[pnt].edges[i].end_index);
    EBNode_ComputeEdgeCosts(nlist->nodes[pnt].edges[i].end_room, nlist->nodes[pnt].edges[i].end_index, roomnum, pnt);
  }
}

void EBNode_Draw(char draw_type, grViewport *vp, vector *viewer_eye, matrix *viewer_orient, float zoom) {
  int i;

#ifndef NEWEDITOR
  int roomnum = Viewer_object->roomnum;
#else
  int roomnum = ROOMNUM(Editor()->m_pLevelWnd->m_Prim.roomp);
#endif

  switch (draw_type) {
  case EBDRAW_NONE:
    break;
  case EBDRAW_ROOM_AND_NEXT_ROOMS: {
    int i;
    int next_rooms[1000];
    int num_next_rooms = AIMakeNextRoomList(roomnum, next_rooms, 1000);

    for (i = 0; i < num_next_rooms; i++) {
      EBNode_DrawRoom(next_rooms[i], vp, viewer_eye, viewer_orient, zoom, false);
    }
  }
  case EBDRAW_ROOM:
    EBNode_DrawRoom(roomnum, vp, viewer_eye, viewer_orient, zoom, true);
    break;
  case EBDRAW_LEVEL:
    for (i = 0; i <= Highest_room_index; i++) {
      if (Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL)) {
        EBNode_DrawRoom(i, vp, viewer_eye, viewer_orient, zoom, i == roomnum);
      }
    }
    for (i = 0; i < BOA_num_terrain_regions; i++) {
      EBNode_DrawRoom(Highest_room_index + i + 1, vp, viewer_eye, viewer_orient, zoom,
                      ROOMNUM_OUTSIDE(roomnum) && (i == TERRAIN_REGION(roomnum)));
    }
    break;
  }
}
