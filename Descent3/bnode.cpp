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

 * $Logfile: /DescentIII/Main/bnode.cpp $
 * $Revision: 23 $
 * $Date: 10/21/99 2:36p $
 * $Author: Matt $
 *
 * BOA Helper Node functions
 *
 * $Log: /DescentIII/Main/bnode.cpp $
 *
 * 23    10/21/99 2:36p Matt
 * Mac merge
 *
 * 22    10/08/99 4:27p Chris
 * Removed a needless ASSERT
 *
 * 21    5/20/99 8:09p Chris
 * Patched up the bnode crashes
 *
 * 20    5/19/99 2:40p Chris
 *
 * 19    5/13/99 4:23p Matt
 * Fixed, hopefully, a problem remapping nodes.
 *
 * 18    5/10/99 10:07p Ardussi
 * changes to compile on Mac
 *
 * 17    5/09/99 11:43p Chris
 * Fixed a bug with no generating a random node (worst case for the
 * terrain)
 *
 * 16    5/09/99 5:24p Chris
 * Maxed the bnode distance to the AI_SEE distance
 *
 * 15    5/06/99 5:18p Chris
 * Updated the BNode system - vastly improved error checking and verify
 *
 * 14    5/02/99 6:16a Chris
 * Massive bnode error checking improvements
 *
 * 13    5/01/99 4:06p Jeff
 * fixed #include for linux
 *
 * 12    4/28/99 8:27a Chris
 *
 * 11    4/28/99 5:33a Chris
 * Further improved the BNode system.  (It actually works inside and
 * outside now)
 *
 * 10    4/27/99 11:37p Chris
 * Improving the BNode system
 *
 * 9     4/27/99 3:01a Chris
 * Improving Bnode stuff
 *
 * 8     4/26/99 11:11a Chris
 * Updated Bnode system
 *
 * 7     4/25/99 8:57p Chris
 * Improving the Bnode system
 *
 * 6     4/18/99 4:35p Matt
 * Changed BNode_FreeRoom() to take a room pointer instead of a room
 * number, since it was being called for rooms in the scrap buffer, which
 * weren't in the room list.  Also added code to InitRoom() to init the
 * bnode data.
 *
 * 5     4/18/99 6:50a Chris
 *
 * 4     4/18/99 5:39a Chris
 * Vastly improved the path node system
 *
 * 3     4/15/99 5:48p Chris
 * Fixed a bug with rendering the BOAPath nodes
 *
 * 2     4/14/99 3:12p Chris
 * Beginning to add BoaNode stuff
 *
 * $NoKeywords: $
 */


#include "memory.h"
#include "bnode.h"
#include "room.h"
#include "mem.h"
#include "vecmat.h"
#include "terrain.h"
#include "room.h"
#include "findintersection.h"
#include "BOA.h"
#include "psrand.h"

static bn_list BNode_terrain_list[8];
bool BNode_allocated = false;
bool BNode_verified = false;

//--  Priority Queue
class pq_item {
public:
  pq_item(int node_index, int parent_node, float n_cost) {
    node = node_index;
    p_node = parent_node;
    cost = n_cost;
    next = NULL;
  }

  int node;
  int p_node;
  float cost;

  pq_item *next;
};

class bpq {
  pq_item *q_head;

public:
  bpq() { q_head = NULL; }

  void push(pq_item *new_node) {
    new_node->next = q_head;
    q_head = new_node;
  }

  pq_item *pop() {
    pq_item *cur_item = q_head;
    pq_item *prev_item = NULL;
    pq_item *best_item = q_head;
    pq_item *best_prev_item = NULL;

    if (q_head == NULL)
      return NULL;

    while (cur_item != NULL) {
      if (cur_item->cost < best_item->cost) {

        best_prev_item = prev_item;
        best_item = cur_item;
      }

      prev_item = cur_item;
      cur_item = cur_item->next;
    }

    // Actually remove this item from the list
    if (best_item == q_head) {
      q_head = best_item->next;
    } else {
      best_prev_item->next = best_item->next;
    }

    return best_item;
  }
};

static float BNode_QuickDist(vector *pos1, vector *pos2);
static void BNode_UpdatePathInfo(pq_item **node_list, int start, int end);

float BNode_QuickDist(vector *pos1, vector *pos2) {
  return fabs(pos1->x - pos2->x) + fabs(pos1->y - pos2->y) + fabs(pos1->z - pos2->z);
}

int BNode_Path[MAX_BNODES_PER_ROOM];
int BNode_PathNumNodes;

void BNode_UpdatePathInfo(pq_item **node_list, int start, int end) {
  int cur_node = end;
  int i;

  BNode_PathNumNodes = 0;

  //	mprintf(0, "start crash loop\n");
  while (cur_node != -1) {
    BNode_Path[BNode_PathNumNodes++] = cur_node;
    cur_node = node_list[cur_node]->p_node;
  }
  //	mprintf(0, "end crash loop\n");

  // Reverse the list (so it is what we want)
  for (i = 0; i < (BNode_PathNumNodes >> 1); i++) {
    int temp;

    temp = BNode_Path[i];
    BNode_Path[i] = BNode_Path[BNode_PathNumNodes - i - 1];
    BNode_Path[BNode_PathNumNodes - i - 1] = temp;
  }

  /*	for(i = 0; i < BNode_PathNumNodes; i++)
          {
                  mprintf(0, "Node %d\n", BNode_Path[i]);
          }
  */
}

// Ok to use Highest_room_index offset stuff
bool BNode_FindPath(int start_room, int i, int j, float rad) {
  bpq PQPath;
  int counter;
  pq_item *start_node = new pq_item(i, -1, 0.0f);
  pq_item *cur_node;
  bool f_found = false;

  //	mprintf(0, "++++++++++\nFind path from %d to %d in room %d\n", i, j, start_room);

  start_room = BOA_INDEX(start_room);

  pq_item **node_list;
  bn_list *bnlist = BNode_GetBNListPtr(start_room);

  ASSERT(bnlist);
  ASSERT(i >= 0 && i < bnlist->num_nodes && j >= 0 && j < bnlist->num_nodes);

  node_list = (pq_item **)mem_malloc(bnlist->num_nodes * sizeof(pq_item *));
  memset(node_list, 0, bnlist->num_nodes * sizeof(pq_item *));

  PQPath.push(start_node);

  while ((cur_node = PQPath.pop())) {
    node_list[cur_node->node] = cur_node;

    if (cur_node->node == j) {
      BNode_UpdatePathInfo(node_list, i, j);
      f_found = true;
      goto done;
    }

    int num_edges;

    num_edges = bnlist->nodes[cur_node->node].num_edges;

    for (counter = 0; counter < num_edges; counter++) {
      int next_node;
      pq_item *list_item;
      float new_cost;

      //			if(!BOA_PassablePortal(cur_node->roomnum, counter, false, false))
      //				continue;

      if ((next_node = bnlist->nodes[cur_node->node].edges[counter].end_room != start_room))
        continue;

      next_node = bnlist->nodes[cur_node->node].edges[counter].end_index;

      ASSERT(bnlist->nodes[cur_node->node].edges[counter].cost > 0);
      new_cost = cur_node->cost + bnlist->nodes[cur_node->node].edges[counter].cost;

      list_item = node_list[next_node];

      if (list_item != NULL && list_item->cost < new_cost)
        continue;

      if (list_item == NULL) {
        list_item = new pq_item(next_node, cur_node->node, new_cost);

        node_list[next_node] = list_item;
        PQPath.push(list_item);
      } else {
        list_item->cost = new_cost;
        list_item->p_node = cur_node->node;
      }
    }
  }

done:
  for (counter = 0; counter < bnlist->num_nodes; counter++) {
    if (node_list[counter])
      delete node_list[counter];
  }

  mem_free(node_list); // DAJ LEAKFIX
  return f_found;
}

// TODO: MTS: Unused?
int BNode_GenerateBestPathThroughRoom(int sroom, int spnt, int croom, int eroom, int eportal, int max_nodes,
                                      vector *pos_list) {
  return -1;
}

static char BNode_vis[MAX_BNODES_PER_ROOM];
#define VIS_NO_CHECK 2
#define VIS_OK 1
#define VIS_NO 2

int BNode_FindDirLocalVisibleBNode(int roomnum, vector *pos, vector *fvec, float rad) {
  int i;
  float best_dot = -1.01f;
  float closest_dist = 800.0f;
  int closest_node = -1;
  bool f_retry = false;

  float min_bn_rad = rad / 4.0f;
  if (min_bn_rad > MAX_BNODE_SIZE) {
    min_bn_rad = MAX_BNODE_SIZE;
  }

  bn_list *bnlist = BNode_GetBNListPtr(roomnum);

retry:

  for (i = 0; i < bnlist->num_nodes; i++) {
    vector to = bnlist->nodes[i].pos - *pos;
    float dist = vm_NormalizeVector(&to);

    if (dist < closest_dist) {
      float dot = *fvec * to;

      if (dot > 0.0f || f_retry) {
        float node_size = 0.0f;

        /*				if(!f_retry)
                                        {
                                                for(j = 0; j < bnlist->nodes[i].num_edges; j++)
                                                {
                                                        if(bnlist->nodes[i].edges[j].max_rad > node_size)
                                                        {
                                                                node_size = bnlist->nodes[i].edges[j].max_rad;
                                                        }
                                                }
                                        }
        */
        if (!f_retry || (f_retry && BNode_vis[i] == VIS_NO_CHECK)) {
          fvi_query fq;
          fvi_info hit_info;

          fq.p0 = pos;
          fq.startroom = (roomnum > Highest_room_index && roomnum <= Highest_room_index + 8)
                             ? GetTerrainRoomFromPos(pos)
                             : roomnum;
          fq.p1 = &bnlist->nodes[i].pos;
          fq.rad = min_bn_rad;
          fq.thisobjnum = -1;
          fq.ignore_obj_list = NULL;
          fq.flags = FQ_CHECK_OBJS | FQ_NO_RELINK | FQ_IGNORE_NON_LIGHTMAP_OBJECTS;

          if (fvi_FindIntersection(&fq, &hit_info) == HIT_NONE) {
            BNode_vis[i] = VIS_OK;
            best_dot = dot;
            closest_node = i;
          } else {
            if (!f_retry) {
              BNode_vis[i] = VIS_NO;
            } else {
              if (BNode_vis[i] == VIS_OK) {
                closest_node = i;
              }
            }
          }
        } else {
          if (f_retry && BNode_vis[i] == VIS_OK) {
            closest_node = i;
          }
        }
      } else {
        BNode_vis[i] = VIS_NO_CHECK;
      }
    } else {
      BNode_vis[i] = VIS_NO_CHECK;
    }
  }

  if (closest_node == -1 && !f_retry) {
    f_retry = true;
    goto retry;
  }

  ASSERT(bnlist->num_nodes > 0);
  if (closest_node == -1 && bnlist->num_nodes > 0) {
    closest_node = ps_rand() % bnlist->num_nodes;
  }

  ASSERT(closest_node != -1);

  return closest_node;
}

int BNode_FindClosestLocalVisibleBNode(int roomnum, vector *pos, float rad) {
  int i, j;
  float closest_dist = 800.0f;
  int closest_node = -1;
  bool f_retry = false;

  float min_bn_rad = rad / 4.0f;
  if (min_bn_rad > MAX_BNODE_SIZE) {
    min_bn_rad = MAX_BNODE_SIZE;
  }

  bn_list *bnlist = BNode_GetBNListPtr(roomnum);

retry:

  for (i = 0; i < bnlist->num_nodes; i++) {
    float dist = BNode_QuickDist(&bnlist->nodes[i].pos, pos);

    if (dist < closest_dist) {
      float node_size = 0.0f;

      if (!f_retry) {
        for (j = 0; j < bnlist->nodes[i].num_edges; j++) {
          if (bnlist->nodes[i].edges[j].max_rad > node_size) {
            node_size = bnlist->nodes[i].edges[j].max_rad;
          }
        }
      }

      if (f_retry || node_size >= min_bn_rad) {
        fvi_query fq;
        fvi_info hit_info;

        if (!f_retry) {
          fq.p0 = pos;
          fq.startroom = (roomnum > Highest_room_index && roomnum <= Highest_room_index + 8)
                             ? GetTerrainRoomFromPos(pos)
                             : roomnum;
          fq.p1 = &bnlist->nodes[i].pos;
          fq.rad = min_bn_rad;
          fq.thisobjnum = -1;
          fq.ignore_obj_list = NULL;
          fq.flags = 0;
        }

        if (f_retry || fvi_FindIntersection(&fq, &hit_info) == HIT_NONE) {
          closest_dist = dist;
          closest_node = i;
        }
      }
    }
  }

  if (closest_node == -1 && !f_retry) {
    f_retry = true;
    goto retry;
  }

  ASSERT(bnlist->num_nodes > 0);
  if (closest_node == -1 && bnlist->num_nodes > 0) {
    closest_node = ps_rand() % bnlist->num_nodes;
  }

  ASSERT(closest_node != -1);

  return closest_node;
}

bn_list *BNode_GetBNListPtr(int roomnum, bool f_in_load_level) {
  if (roomnum == -1) {
    return NULL;
  } else if (roomnum >= 0 && roomnum <= Highest_room_index) {
    //		if(!f_in_load_level)
    //		{
    //			ASSERT(!(Rooms[roomnum].flags & RF_EXTERNAL));
    //		}

    if (!Rooms[roomnum].used) {
      return NULL;
    }

    room *rp = &Rooms[roomnum];
    return &rp->bn_info;
  } else if (ROOMNUM_OUTSIDE(roomnum)) {
    return &BNode_terrain_list[TERRAIN_REGION(roomnum)];
  } else if (roomnum <= Highest_room_index + 8) {
    return &BNode_terrain_list[roomnum - Highest_room_index - 1];
  }

  return NULL;
}

void BNode_ClearBNodeInfo(void) {
  int i, j;

  for (i = 0; i < 8; i++) {
    if (BNode_allocated) {
      for (j = 0; j < BNode_terrain_list[i].num_nodes; j++) {
        if (BNode_terrain_list[i].nodes[j].num_edges) {
          mem_free(BNode_terrain_list[i].nodes[j].edges);
        }
      }
      mem_free(BNode_terrain_list[i].nodes);
    }

    BNode_terrain_list[i].num_nodes = 0;
    BNode_terrain_list[i].nodes = NULL;
  }

  BNode_allocated = false;
  BNode_verified = false;
}

// Unused?
bool BNode_MakeSubPath(int16_t sroom, int16_t spnt, int16_t eroom, int16_t epnt, int flags, float size, int16_t *roomlist,
                       int16_t *pnts, int max_elements) {
  return false;
}

void BNode_FreeRoom(room *rp) {
  int i;

  for (i = 0; i < rp->bn_info.num_nodes; i++) {
    if (rp->bn_info.nodes[i].num_edges) {
      mem_free(rp->bn_info.nodes[i].edges);
    }
  }

  if (rp->bn_info.num_nodes) {
    mem_free(rp->bn_info.nodes);
    rp->bn_info.nodes = NULL;
    rp->bn_info.num_nodes = 0;
  }
}

void BNode_RemapTerrainRooms(int old_hri, int new_hri) {
  int delta = new_hri - old_hri;
  int i;

  if (!BNode_allocated)
    return;

  if (delta == 0)
    return;

  if (new_hri < 0)
    return;

  ASSERT(delta <= 1);

  for (i = 0; i <= new_hri + BOA_num_terrain_regions; i++) {

    if ((i <= new_hri && Rooms[i].used) || (i > new_hri)) {
      int j;
      int k;

      // Skip external rooms
      if ((i <= new_hri) && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      bn_list *bnlist = BNode_GetBNListPtr(i);
      ASSERT(bnlist);

      for (j = 0; j < bnlist->num_nodes; j++) {
        for (k = 0; k < bnlist->nodes[j].num_edges; k++) {
          if (bnlist->nodes[j].edges[k].end_room >= new_hri) {
            bnlist->nodes[j].edges[k].end_room += delta;
          }
        }
      }
    }
  }
}
