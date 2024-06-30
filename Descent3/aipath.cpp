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
*/

#include <array>

#include "aipath.h"
#include "gamepath.h"
#include "AIGoal.h"
#include "BOA.h"
#include "AIMain.h"
#include "object.h"
#include "objinfo.h"
#include "memory.h"
#include "doorway.h"
#include "aistruct.h"
#include "terrain.h"
#include "psrand.h"
#include "findintersection.h"

#define MAX_DYNAMIC_PATHS 50
#define MAX_NODES 50

std::array<ai_dynamic_path, MAX_DYNAMIC_PATHS> AIDynamicPath;
std::array<int, MAX_ROOMS> AIAltPath;
int AIAltPathNumNodes;

static void AIUpdatePathInfo(q_item **node_list, int start, int end) {
  int cur_room = end;
  int i;

  AIAltPathNumNodes = 0;

  //	mprintf(0, "start crash loop\n");
  while (cur_room != -1) {
    AIAltPath[AIAltPathNumNodes++] = cur_room;
    cur_room = node_list[cur_room]->parent;
  }
  //	mprintf(0, "end crash loop\n");

  // Reverse the list (so it is what we want)
  for (i = 0; i < (AIAltPathNumNodes >> 1); i++) {
    int temp;

    temp = AIAltPath[i];
    AIAltPath[i] = AIAltPath[AIAltPathNumNodes - i - 1];
    AIAltPath[AIAltPathNumNodes - i - 1] = temp;
  }
}

// Ok to use Highest_room_index offset stuff
bool AIFindAltPath(object *obj, int i, int j, float *dist) {
  i = BOA_INDEX(i);
  j = BOA_INDEX(j);

  pq PQPath;
  int counter;
  q_item *start_node = new q_item(i, -1, 0.0f);
  q_item *cur_node;
  bool f_found = false;

  q_item *node_list[MAX_ROOMS + 8];

  //	mprintf(0, "AI: Finding an alternate path from %d to %d\n", i, j);

  if (i == -1 || j == -1) {
    delete start_node;
    return false;
  }

  memset(node_list, 0, sizeof(q_item *) * (MAX_ROOMS + 8));

  PQPath.push(start_node);

  while ((cur_node = PQPath.pop())) {
    node_list[BOA_INDEX(cur_node->roomnum)] = cur_node;
    ASSERT(BOA_INDEX(cur_node->roomnum) >= 0 && BOA_INDEX(cur_node->roomnum) <= Highest_room_index + 8);

    if (cur_node->roomnum == j) {
      AIUpdatePathInfo(node_list, i, j);
      f_found = true;
      goto done;
    }

    int num_portals;
    bool f_room = true;
    int t_index;

    if (cur_node->roomnum <= Highest_room_index) {
      num_portals = Rooms[cur_node->roomnum].num_portals;
    } else {
      t_index = cur_node->roomnum - Highest_room_index - 1;
      num_portals = BOA_num_connect[t_index];
      f_room = false;
    }

    for (counter = 0; counter < num_portals; counter++) {
      int next_room;
      q_item *list_item;
      float new_cost;

      if (!BOA_PassablePortal(cur_node->roomnum, counter, false, false))
        continue;

      if (f_room)
        next_room = Rooms[cur_node->roomnum].portals[counter].croom;
      else
        next_room = BOA_connect[t_index][counter].roomnum;

      if (next_room <= Highest_room_index && Rooms[next_room].flags & RF_EXTERNAL) {
        int next_portal;
        next_portal = BOA_DetermineStartRoomPortal(BOA_INDEX(next_room), NULL, BOA_INDEX(cur_node->roomnum), NULL);

        int cell = GetTerrainCellFromPos(&Rooms[next_room].portals[next_portal].path_pnt);
        ASSERT(cell != -1); // DAJ -1FIX
        next_room = Highest_room_index + TERRAIN_REGION(cell) + 1;
      }

      if (next_room < 0 || next_room == BOA_NO_PATH)
        continue;

      if (BOA_LockedDoor(obj, next_room))
        continue;

      int next_portal = 0;

      if (BOA_INDEX(next_room) != BOA_INDEX(cur_node->roomnum)) {
        next_portal = BOA_DetermineStartRoomPortal(BOA_INDEX(next_room), NULL, BOA_INDEX(cur_node->roomnum), NULL,
                                                   false, false, NULL);
      }

      if (next_portal == -1)
        continue;

      if (BOA_cost_array[cur_node->roomnum][counter] >= 0.0f)
        new_cost = cur_node->cost +
                   (1.0f + 0.1f * ((float)ps_rand() - (float)D3_RAND_MAX / 2.0f) / ((float)D3_RAND_MAX / 2.0f)) *
                       (BOA_cost_array[cur_node->roomnum][counter] + BOA_cost_array[BOA_INDEX(next_room)][next_portal]);
      else
        continue;

      // new_cost = cur_node->cost + BOA_cost_array[cur_node->roomnum][counter];
      list_item = node_list[BOA_INDEX(next_room)];

      if (list_item != NULL && list_item->cost < new_cost)
        continue;

      if (list_item == NULL) {
        list_item = new q_item(BOA_INDEX(next_room), cur_node->roomnum, new_cost);
        ASSERT(BOA_INDEX(cur_node->roomnum) >= 0 && BOA_INDEX(cur_node->roomnum) <= Highest_room_index + 8);

        node_list[BOA_INDEX(next_room)] = list_item;
        ASSERT(BOA_INDEX(next_room) >= 0 && BOA_INDEX(next_room) <= Highest_room_index + 8);
        PQPath.push(list_item);
      } else {
        list_item->cost = new_cost;
        list_item->parent = cur_node->roomnum;
      }
    }
  }

  // Mark as an impossible path.

  //	mprintf(0, "Found an impossible path\n");

done:
  for (counter = 0; counter < MAX_ROOMS + 8; counter++) {
    if (node_list[counter])
      delete node_list[counter];
  }

  if (f_found && dist) {
    *dist = 0.0f;

    if (AIAltPathNumNodes > 1) {
      int x;

      for (x = 0; x < AIAltPathNumNodes - 1; x++) {
        int cur_room = AIAltPath[x];
        int next_room = AIAltPath[x + 1];

        int cur_portal = BOA_DetermineStartRoomPortal(cur_room, NULL, next_room, NULL);
        int next_portal = BOA_DetermineStartRoomPortal(next_room, NULL, cur_room, NULL);

        ASSERT(cur_portal != -1 && next_portal != -1);

        *dist += BOA_cost_array[cur_room][cur_portal] + BOA_cost_array[next_room][next_portal];
      }
    }
  }

  //	mprintf(0, "Done\n");
  return f_found;
}

bool AIPathGetCurrentNodePos(ai_path_info *aip, vector *pos, int *room) {
  int c_path = aip->cur_path;
  int c_node = aip->cur_node;

  int p_type = aip->path_type[c_path];
  int p_index = aip->path_id[c_path];

  if (p_type == AIP_DYNAMIC) {
    // chrishack -- add asserts

    *pos = AIDynamicPath[p_index].pos[c_node];
    if (room) {
      *room = AIDynamicPath[p_index].roomnum[c_node];
    }

    return true;
  } else if (p_type == AIP_STATIC) {
    // chrishack -- add asserts

    *pos = GamePaths[p_index].pathnodes[c_node].pos;
    if (room) {
      *room = GamePaths[p_index].pathnodes[c_node].roomnum;
    }

    return true;
  }

  return false;
}

// Chrishack -- need to add static path flag stuff
static bool AIPathMoveToNextNode(ai_path_info *aip) {
  int c_path = aip->cur_path;
  int c_node = aip->cur_node;

  int p_type = aip->path_type[c_path];
  int p_index = aip->path_id[c_path];

  c_node++;

  if (c_node <= aip->path_end_node[c_path]) {
    aip->cur_node++;
    return true;
  }

  c_path++;

  // We must want to check the next path
  if (c_path < aip->num_paths) {
    aip->cur_path++;
    aip->cur_node = aip->path_start_node[aip->cur_path];

    return true;
  }

  return false;
}

bool AIPathAtStart(ai_path_info *aip) {
  if (aip->cur_path == 0 && aip->cur_node == aip->path_start_node[0])
    return true;
  else
    return false;
}

bool AIPathAtEnd(ai_path_info *aip) {
  if (aip->cur_path == aip->num_paths - 1 && aip->cur_node == aip->path_end_node[aip->num_paths - 1])
    return true;
  else
    return false;
}

static void AIPathSetAtEnd(ai_path_info *aip) {
  aip->cur_path = aip->num_paths - 1;
  aip->cur_node = aip->path_end_node[aip->num_paths - 1];
}

void AIPathSetAtStart(ai_path_info *aip) {
  aip->cur_path = 0;
  aip->cur_node = aip->path_start_node[0];
}

static bool AIPathMoveToPrevNode(ai_path_info *aip) {
  int c_path = aip->cur_path;
  int c_node = aip->cur_node;

  c_node--;

  if (c_node >= 0) {
    aip->cur_node--;
    return true;
  }

  c_path--;

  // We must want to check the next path
  if (c_path > 0) {
    aip->cur_path--;

    if (aip->path_type[c_path] == AIP_DYNAMIC) {
      aip->cur_node = AIDynamicPath[aip->path_id[c_path]].num_nodes - 1;
    } else if (aip->path_type[c_path] == AIP_STATIC) {
      aip->cur_node = aip->path_end_node[c_path];
    }
    return true;
  }

  return false;
}

bool AIPathGetNextNodePos(ai_path_info *aip, vector *pos, int *room) {
  if (AIPathMoveToNextNode(aip)) {
    AIPathGetCurrentNodePos(aip, pos, room);
    AIPathMoveToPrevNode(aip);

    return true;
  }

  return false;
}

bool AIPathGetPrevNodePos(ai_path_info *aip, vector *pos, int *room) {
  if (AIPathMoveToPrevNode(aip)) {
    AIPathGetCurrentNodePos(aip, pos, room);
    AIPathMoveToNextNode(aip);

    return true;
  }

  return false;
}

static void AIPathComplete(object *obj) { GoalPathComplete(obj); }

void AIPathMoveTurnTowardsNode(object *obj, vector *mdir, bool *f_moved) {
  ai_path_info *aip = &obj->ai_info->path;
  goal *g_ptr = &obj->ai_info->goals[obj->ai_info->path.goal_index];

  bool f_too_far_from_end = false;

  //	game_path *p = &GamePaths[path_info->path_id];
  int n = aip->cur_node;
  int p = aip->cur_path;

  bool f_reverse = (g_ptr->flags & GF_PATH_MOVE_REVERSE_DIR) != 0;

  ai_frame *ai_info = obj->ai_info;

  vector cur_pos;

  AIPathGetCurrentNodePos(aip, &cur_pos);
  //	mprintf(0, "Cur pos = %f,%f,%f\n", XYZ(&cur_pos));

  //	mprintf(0, "1 R %d, Goal p %d, n %d\n", f_reverse, p, n);

  //	mprintf(0, "s %f, %f, %f\n", XYZ(&obj->pos));
  //	mprintf(0, "l %f, %f, %f\n", XYZ(&obj->last_pos));

  //	mprintf(0, "%d is at Node %d\n", OBJNUM(obj), n);

  bool f_force_complete_stopping = false;

  if (((!f_reverse && AIPathAtEnd(aip)) || (f_reverse && AIPathAtStart(aip))) &&
      (((goal *)(&obj->ai_info->goals[aip->goal_index]))->circle_distance == 0.0f) &&
      obj->movement_type == MT_PHYSICS) {
    f_too_far_from_end = !AIMoveTowardsPosition(obj, &cur_pos, 1.0, true, mdir, f_moved);
    if (!f_too_far_from_end) {
      f_force_complete_stopping = true;
    }
  } else {
    vector dir = cur_pos - obj->pos;

    if (obj->movement_type == MT_WALKING) {
      float dot = dir * obj->orient.uvec;
      dir -= dot * obj->orient.uvec;
    }
    vm_NormalizeVector(&dir);

    *mdir = dir;
    *f_moved = false;
    //		AIMoveTowardsDir(obj, &dir);
  }
  //	removed check if(f_reverse && (path_info->next_node < path_info->start_node))
  //	removed check {
  //	removed check	mprintf(0, "AI ERROR: Fixed a bad predefined path next_node to goal_node");
  //	removed check	path_info->next_node = path_info->start_node;
  //	removed check	Int3();
  //	removed check }
  // removed check
  //	removed check if(!(f_reverse) && path_info->next_node > path_info->end_node)
  //	removed check {
  //	removed check	mprintf(0, "AI ERROR: Fixed a bad predefined path next_node to goal_node");
  //	removed check	path_info->next_node = path_info->end_node;
  //	removed check	Int3();
  // removed check }

  bool f_pass_node;
  int last_n;
  int last_p;

pass_node:

  f_pass_node = false;
  last_n = n;
  last_p = p;

  if (obj->movement_type == MT_WALKING) {
    vector dir = cur_pos - obj->pos;

    if (obj->movement_type == MT_WALKING) {
      float dot = dir * obj->orient.uvec;
      dir -= dot * obj->orient.uvec;
    }
    float dist = vm_GetMagnitude(&dir);

    if (dist < 1.5f) {
      f_pass_node = true;
    }
  }

  if (f_force_complete_stopping) {
    f_pass_node = true;
  }

  if (!f_pass_node) {
    if (!f_reverse) {
      if (AIPathAtStart(aip)) {
        if (AIPathAtEnd(aip)) {
          if ((obj->pos - cur_pos) * (obj->last_pos - cur_pos) <= 0.0f && !f_too_far_from_end)
            f_pass_node = true;
        } else {
          vector next_pos;
          AIPathGetNextNodePos(aip, &next_pos, NULL);

          vector proj_line = obj->pos - cur_pos;
          vector line = next_pos - cur_pos;
          float proj = proj_line * line;

          if (proj >= 0.0f)
            f_pass_node = true;
        }
      } else {
        vector prev_pos;
        AIPathGetPrevNodePos(aip, &prev_pos, NULL);

        vector proj = obj->pos - prev_pos;
        vector line = cur_pos - prev_pos;
        float line_len = vm_NormalizeVector(&line);
        float proj_len = proj * line;

        if (proj_len >= line_len)
          f_pass_node = true;
      }
    } else {
      if (AIPathAtEnd(aip)) {
        if (AIPathAtStart(aip)) {
          if ((obj->pos - cur_pos) * (obj->last_pos - cur_pos) <= 0.0f && !f_too_far_from_end)
            f_pass_node = true;
        } else {
          vector prev_pos;
          AIPathGetPrevNodePos(aip, &prev_pos, NULL);

          vector proj_line = obj->pos - cur_pos;
          vector line = prev_pos - cur_pos;
          float proj = proj_line * line;

          if (proj >= 0.0f)
            f_pass_node = true;
        }
      } else {
        vector next_pos;
        AIPathGetNextNodePos(aip, &next_pos, NULL);

        vector proj = obj->pos - next_pos;
        vector line = cur_pos - next_pos;
        float line_len = vm_NormalizeVector(&line);
        float proj_len = proj * line;

        if (proj_len >= line_len)
          f_pass_node = true;
      }
    }
  }

  if (f_pass_node) {
    //		mprintf(0, "f_pass_node\n");

    if (((f_reverse) && AIPathAtStart(aip)) || ((!f_reverse) && AIPathAtEnd(aip))) {
      //			mprintf(0, "At end node: ");

      switch (g_ptr->flags & GFM_END_OF_PATH) {
      case GF_PATH_REVERSE_AT_END:
        //					mprintf(0, "End reverse dir\n");
        if (f_reverse)
          g_ptr->flags &= ~GF_PATH_MOVE_REVERSE_DIR;
        else
          g_ptr->flags |= GF_PATH_MOVE_REVERSE_DIR;
        return;
      case GF_PATH_CIRCLE_AT_END:
        //					mprintf(0, "End circle dir\n");
        if (f_reverse)
          AIPathSetAtEnd(aip);
        else
          AIPathSetAtStart(aip);
        return;
      default:
        //					mprintf(0, "End kill goal\n");
        AIPathComplete(obj);
        return;
      }
    } else {
      //			mprintf(0, "Passed node\n");
      if (g_ptr->flags & GF_PATH_MOVE_REVERSE_DIR)
        AIPathMoveToPrevNode(aip);
      else
        AIPathMoveToNextNode(aip);
    }

    AIPathGetCurrentNodePos(aip, &cur_pos);

    n = aip->cur_node;
    p = aip->cur_path;

    f_reverse = (g_ptr->flags & GF_PATH_MOVE_REVERSE_DIR) != 0;

    if (n != last_n || p != last_p)
      goto pass_node;
  }
}

static bool AIPathFreeDPathSlot(int slot) {
  ASSERT(AIDynamicPath[slot].use_count >= 0);
  ASSERT(slot >= 0 && slot < MAX_DYNAMIC_PATHS && AIDynamicPath[slot].use_count != 0);

  AIDynamicPath[slot].use_count--;

  if (!AIDynamicPath[slot].use_count) {
    AIDynamicPath[slot].num_nodes = 0;
    AIDynamicPath[slot].owner_handle = OBJECT_HANDLE_NONE;
  }

  return true;
}

static bool AIPathGetDPathSlot(int *slot, int handle) {
  int i;

  for (i = 0; i < MAX_DYNAMIC_PATHS; i++) {
    if (!AIDynamicPath[i].use_count) {
      AIDynamicPath[i].use_count++;
      *slot = i;
      AIDynamicPath[i].owner_handle = handle;
      return true;
    } else if (ObjGet(AIDynamicPath[i].owner_handle) == NULL && AIDynamicPath[i].use_count == 1) {
      AIPathFreeDPathSlot(i);

      AIDynamicPath[i].use_count++;
      *slot = i;
      AIDynamicPath[i].owner_handle = handle;
      return true;
    }
  }

  mprintf(0, "Out of dynamic paths");
  ASSERT(0); // -- get chris
  return false;
}

bool AIPathInitPath(ai_path_info *aip) {
  ASSERT(aip);

  aip->num_paths = 0;
  aip->cur_path = 0;
  aip->cur_node = 0;

  aip->goal_index = -1;
  aip->goal_uid = -1;

  return true;
}

bool AIPathFreePath(ai_path_info *aip) {
  int i;

  for (i = 0; i < aip->num_paths; i++) {
    if (aip->path_type[i] == AIP_DYNAMIC) {
      AIPathFreeDPathSlot(aip->path_id[i]);
    }
  }

  AIPathInitPath(aip);

  return true;
}

static bool AIPathAddDPath(ai_path_info *aip, int handle) {
  int slot;
  bool status;

  if (aip->num_paths >= MAX_JOINED_PATHS) {
    mprintf(0, "AI ERROR: Tried to join too many paths (Adding dpath)\n");
    return false;
  }

  status = AIPathGetDPathSlot(&slot, handle);

  if (status) {
    aip->path_id[aip->num_paths] = slot;
    aip->path_type[aip->num_paths] = AIP_DYNAMIC;

    aip->path_start_node[aip->num_paths] = 0;
    aip->path_end_node[aip->num_paths] = 0;

    aip->path_flags[aip->num_paths] = 0;

    aip->num_paths++;
  }

  return status;
}

static bool AIPathAddStaticPath(ai_path_info *aip, int path_id, int start_index, int end_index) {
  // chrishack -- validation code is needed

  if (aip->num_paths >= MAX_JOINED_PATHS) {
    mprintf(0, "AI ERROR: Tried to join too many paths (Adding spath)\n");
    return false;
  }

  aip->path_id[aip->num_paths] = path_id;
  aip->path_type[aip->num_paths] = AIP_STATIC;
  aip->path_start_node[aip->num_paths] = start_index;
  aip->path_end_node[aip->num_paths] = end_index;

  aip->num_paths++;

  return true;
}

static inline bool AIPathAddDPathNode(ai_path_info *aip, int *slot, int *cur_node, vector *pos, int room, int handle) {
  int status;

  if (*cur_node == MAX_NODES) {
    status = AIPathAddDPath(aip, handle);
    if (!status)
      Int3(); // chrishack -- out of dynamic paths

    AIDynamicPath[*slot].num_nodes = MAX_NODES;
    *cur_node = 0;
    *slot = aip->path_id[aip->num_paths - 1];
  }

  AIDynamicPath[*slot].pos[*cur_node] = *pos;
  AIDynamicPath[*slot].roomnum[(*cur_node)++] = room;

  aip->path_end_node[aip->num_paths - 1] = *cur_node - 1;

  return true;
}

static bool AIGenerateAltBNodePath(object *obj, vector *start_pos, int *start_room, vector *end_pos, int *end_room,
                                   ai_path_info *aip, int *slot, int *cur_node, int handle) {
  int x;
  vector *pos;
  bool f_path_exists = true;

  bn_list *bnlist = BNode_GetBNListPtr(*start_room);
  int last_node = BNode_FindDirLocalVisibleBNode(*start_room, start_pos, &obj->orient.fvec, obj->size);
  if (last_node == -1) {
    f_path_exists = false;
    goto done;
  }
  ASSERT(last_node >= 0);

  for (x = 0; x < AIAltPathNumNodes - 1 && f_path_exists; x++) {
    int cur_room = BOA_INDEX(AIAltPath[x]);
    int next_room = BOA_INDEX(AIAltPath[x + 1]);

    bnlist = BNode_GetBNListPtr(cur_room);
    ASSERT(bnlist);

    if (next_room != cur_room && next_room != BOA_NO_PATH) {
      int portal = BOA_DetermineStartRoomPortal(cur_room, NULL, next_room, NULL);
      if (portal == -1) {
        f_path_exists = false;
      } else {
        int bnode = -1;

        if (cur_room >= 0 && cur_room <= Highest_room_index) {
          bnode = Rooms[cur_room].portals[portal].bnode_index;
          ASSERT(bnode >= 0 && bnode < BNode_GetBNListPtr(cur_room)->num_nodes);
        } else {
          int croom = BOA_connect[cur_room - Highest_room_index - 1][portal].roomnum;
          int cportal = BOA_connect[cur_room - Highest_room_index - 1][portal].portal;

          int r = Rooms[croom].portals[cportal].croom;
          int p = Rooms[croom].portals[cportal].cportal;

          ASSERT(Rooms[r].used && (Rooms[r].flags & RF_EXTERNAL));
          bnode = Rooms[r].portals[p].bnode_index;
          //					ASSERT(bnode >= 0 && bnode < BNode_GetBNListPtr(r)->num_nodes);
        }

        // Add the last room...
        bool f_ok = BNode_FindPath(cur_room, last_node, bnode, obj->size);
        ASSERT(f_ok);
        ASSERT(BNode_PathNumNodes);

        int i;
        for (i = 0; i < BNode_PathNumNodes; i++) {
          pos = &bnlist->nodes[BNode_Path[i]].pos;
          AIPathAddDPathNode(aip, slot, cur_node, pos, cur_room, handle);
        }

        int portal = BOA_DetermineStartRoomPortal(next_room, NULL, cur_room, NULL);
        if (next_room <= Highest_room_index) {
          bnode = Rooms[next_room].portals[portal].bnode_index;
          ASSERT(bnode >= 0);
        } else {
          int croom = BOA_connect[next_room - Highest_room_index - 1][portal].roomnum;
          int cportal = BOA_connect[next_room - Highest_room_index - 1][portal].portal;

          int r = Rooms[croom].portals[cportal].croom;
          int p = Rooms[croom].portals[cportal].cportal;

          ASSERT(Rooms[r].used && (Rooms[r].flags & RF_EXTERNAL));
          bnode = Rooms[r].portals[p].bnode_index;
          //					ASSERT(bnode >= 0 && bnode < BNode_GetBNListPtr(r)->num_nodes);
        }

        last_node = bnode;
        ASSERT(last_node >= 0);
      }
    } else {
      if (next_room == BOA_NO_PATH) {
        f_path_exists = false;
      }
    }
  }

  if (f_path_exists) {
    int bnode;

    bn_list *bnlist = BNode_GetBNListPtr(*end_room);
    bnode = BNode_FindClosestLocalVisibleBNode(*end_room, end_pos, obj->size);
    if (bnode == -1) {
      f_path_exists = false;
      goto done;
    }

    // Add the last room...
    bool f_ok = BNode_FindPath(*end_room, last_node, bnode, obj->size);
    ASSERT(f_ok);
    ASSERT(BNode_PathNumNodes);
    int i;
    for (i = 0; i < BNode_PathNumNodes; i++) {
      pos = &bnlist->nodes[BNode_Path[i]].pos;
      AIPathAddDPathNode(aip, slot, cur_node, pos, *end_room, handle);
    }
  }

done:
  if (!f_path_exists)
    AIPathFreePath(aip);

  return f_path_exists;
}

static void AIGenerateAltBOAPath(vector *start_pos, vector *end_pos, ai_path_info *aip, int *slot, int *cur_node,
                                 int handle) {
  int x;
  vector *pos = NULL;

  for (x = 0; x < AIAltPathNumNodes - 1; x++) {
    int cur_room = AIAltPath[x];
    int next_room = AIAltPath[x + 1];

    int i;

    if (next_room >= 0 && next_room <= Highest_room_index) {
      if (cur_room > Highest_room_index) {
        i = BOA_DetermineStartRoomPortal(next_room, NULL, cur_room, NULL, false, false, NULL);
        ASSERT(i != -1);
        pos = &Rooms[next_room].portals[i].path_pnt;
      } else {
        for (i = 0; i < Rooms[next_room].num_portals; i++) {
          if (cur_room <= Highest_room_index && Rooms[next_room].portals[i].croom == cur_room) {
            pos = &Rooms[next_room].portals[i].path_pnt;
            break;
          }
        }
      }

      // Add the adjoining room's portal point
      ASSERT(i < Rooms[next_room].num_portals);
      AIPathAddDPathNode(aip, slot, cur_node, pos, next_room, handle);

      // Add its center point
      pos = &Rooms[next_room].path_pnt;
      AIPathAddDPathNode(aip, slot, cur_node, pos, next_room, handle);
    } else {
      if (BOA_INDEX(cur_room) <= Highest_room_index && cur_room != next_room) {
        int p_index = BOA_DetermineStartRoomPortal(cur_room, NULL, next_room, NULL);

        if (p_index >= 0) {
          pos = &Rooms[cur_room].portals[p_index].path_pnt;
          AIPathAddDPathNode(aip, slot, cur_node, pos, cur_room, handle);
        }
      }
    }
  }
}

//	if(ROOMNUM_OUTSIDE(next_room) && ROOMNUM_OUTSIDE(*end_room) && (TERRAIN_REGION(next_room) ==
// TERRAIN_REGION(*end_room) || 		TERRAIN_REGION(*end_room) == 0 || TERRAIN_REGION(next_room) == 0))
//	{
//		next_room = *end_room;
//	}

static bool AIGenerateBNodePath(object *obj, vector *start_pos, int *start_room, vector *end_pos, int *end_room,
                                ai_path_info *aip, int *slot, int *cur_node, int handle) {
  int next_room = BOA_INDEX(*start_room);
  bool f_path_exists = true;
  vector *pos;

  bn_list *bnlist; // = BNode_GetBNListPtr(*start_room);
  int last_node = BNode_FindDirLocalVisibleBNode(*start_room, start_pos, &obj->orient.fvec, obj->size);
  if (last_node == -1) {
    f_path_exists = false;
    goto done;
  }

  ASSERT(!(next_room >= 0 && next_room <= Highest_room_index && !Rooms[next_room].used));

  //	pos = &bnlist->nodes[last_node].pos;
  //	AIPathAddDPathNode(aip, slot, cur_node, pos, *start_room, handle);

  while ((BOA_INDEX(next_room) != BOA_GetNextRoom(next_room, *end_room)) && (next_room != BOA_NO_PATH) &&
         f_path_exists) {
    int cur_room;

    cur_room = next_room;
    next_room = BOA_GetNextRoom(next_room, *end_room);
    bnlist = BNode_GetBNListPtr(cur_room);
    ASSERT(bnlist);

    if (next_room != cur_room && next_room != BOA_NO_PATH) {
      int portal = BOA_DetermineStartRoomPortal(cur_room, NULL, next_room, NULL);
      if (portal == -1) {
        f_path_exists = false;
      } else {
        int bnode;

        if (cur_room <= Highest_room_index) {
          bnode = Rooms[cur_room].portals[portal].bnode_index;
          ASSERT(bnode >= 0 && bnode < BNode_GetBNListPtr(cur_room)->num_nodes);
        } else {
          int croom = BOA_connect[cur_room - Highest_room_index - 1][portal].roomnum;
          int cportal = BOA_connect[cur_room - Highest_room_index - 1][portal].portal;

          int r = Rooms[croom].portals[cportal].croom;
          int p = Rooms[croom].portals[cportal].cportal;

          ASSERT(Rooms[r].used && (Rooms[r].flags & RF_EXTERNAL));
          bnode = Rooms[r].portals[p].bnode_index;
          //					ASSERT(bnode >= 0 && bnode < BNode_GetBNListPtr(r)->num_nodes);
        }

        // Add the last room...
        bool f_ok = BNode_FindPath(cur_room, last_node, bnode, obj->size);
        ASSERT(f_ok);
        ASSERT(BNode_PathNumNodes);

        int i;
        for (i = 0; i < BNode_PathNumNodes; i++) {
          pos = &bnlist->nodes[BNode_Path[i]].pos;
          AIPathAddDPathNode(aip, slot, cur_node, pos, cur_room, handle);
        }

        int portal = BOA_DetermineStartRoomPortal(next_room, NULL, cur_room, NULL);
        if (portal < 0) {
          f_path_exists = false;
        } else {
          if (next_room <= Highest_room_index) {
            last_node = Rooms[next_room].portals[portal].bnode_index;
            ASSERT(last_node >= 0 && last_node < BNode_GetBNListPtr(next_room)->num_nodes);
          } else {
            int croom = BOA_connect[next_room - Highest_room_index - 1][portal].roomnum;
            int cportal = BOA_connect[next_room - Highest_room_index - 1][portal].portal;

            int r = Rooms[croom].portals[cportal].croom;
            int p = Rooms[croom].portals[cportal].cportal;

            ASSERT(Rooms[r].used && (Rooms[r].flags & RF_EXTERNAL));
            last_node = Rooms[r].portals[p].bnode_index;
            //					ASSERT(last_node >= 0 && last_node < BNode_GetBNListPtr(r)->num_nodes);
          }
        }
      }
    } else {
      if (next_room == BOA_NO_PATH) {
        f_path_exists = false;
      }
    }
  }

  if (f_path_exists) {
    int bnode;

    bn_list *bnlist = BNode_GetBNListPtr(*end_room);
    bnode = BNode_FindClosestLocalVisibleBNode(*end_room, end_pos, obj->size);
    if (bnode == -1) {
      f_path_exists = false;
      goto done;
    }

    // Add the last room...
    bool f_ok = BNode_FindPath(*end_room, last_node, bnode, obj->size);
    ASSERT(f_ok);
    ASSERT(BNode_PathNumNodes);
    int i;
    for (i = 0; i < BNode_PathNumNodes; i++) {
      pos = &bnlist->nodes[BNode_Path[i]].pos;
      AIPathAddDPathNode(aip, slot, cur_node, pos, *end_room, handle);
    }
  }

done:
  if (!f_path_exists)
    AIPathFreePath(aip);

  return f_path_exists;
}

static bool AIGenerateBOAPath(vector *start_pos, int *start_room, vector *end_pos, int *end_room, ai_path_info *aip,
                              int *slot, int *cur_node, int handle) {
  int next_room = *start_room;
  bool f_path_exists = true;
  vector *pos;

  ASSERT(ROOMNUM_OUTSIDE(next_room) || (next_room >= 0 && next_room <= Highest_room_index && Rooms[next_room].used));

  // Add in the center of the first room
  if (!ROOMNUM_OUTSIDE(next_room)) {
    pos = &Rooms[*start_room].path_pnt;
    AIPathAddDPathNode(aip, slot, cur_node, pos, *start_room, handle);
  }

  if (ROOMNUM_OUTSIDE(next_room) && ROOMNUM_OUTSIDE(*end_room) &&
      (TERRAIN_REGION(next_room) == TERRAIN_REGION(*end_room) || TERRAIN_REGION(*end_room) == 0 ||
       TERRAIN_REGION(next_room) == 0)) {
    next_room = *end_room;
  }

  while ((BOA_INDEX(next_room) != BOA_GetNextRoom(next_room, *end_room)) && (next_room != BOA_NO_PATH)) {
    int cur_room;

    cur_room = next_room;
    next_room = BOA_GetNextRoom(next_room, *end_room);

    if (next_room != cur_room && next_room != BOA_NO_PATH && BOA_INDEX(next_room) <= Highest_room_index) {
      int i;

      for (i = 0; i < Rooms[next_room].num_portals; i++) {
        if (Rooms[next_room].portals[i].croom == cur_room) {
          pos = &Rooms[next_room].portals[i].path_pnt;
          break;
        }

        if (Rooms[Rooms[next_room].portals[i].croom].flags & RF_EXTERNAL) {
          int cell = GetTerrainCellFromPos(&Rooms[next_room].portals[i].path_pnt);
          ASSERT(cell != -1); // DAJ -1FIX
          int region = TERRAIN_REGION(cell);

          if (Highest_room_index + region + 1 == BOA_INDEX(cur_room)) {
            pos = &Rooms[next_room].portals[i].path_pnt;
            break;
          }
        }
      }

      // Add the adjoining room's portal point
      ASSERT(i < Rooms[next_room].num_portals);
      AIPathAddDPathNode(aip, slot, cur_node, pos, next_room, handle);

      // Add its center point
      pos = &Rooms[next_room].path_pnt;
      AIPathAddDPathNode(aip, slot, cur_node, pos, next_room, handle);
    } else {
      if (next_room == BOA_NO_PATH) {
        f_path_exists = false;
      } else if (BOA_INDEX(cur_room) <= Highest_room_index && cur_room != next_room) {
        int p_index = BOA_DetermineStartRoomPortal(cur_room, NULL, next_room, NULL);

        if (p_index >= 0) {
          pos = &Rooms[cur_room].portals[p_index].path_pnt;
          AIPathAddDPathNode(aip, slot, cur_node, pos, cur_room, handle);
        }
      }
    }
  }

  return f_path_exists;
}

bool AIPathAllocPath(object *obj, ai_frame *ai_info, void *goal_ptr, int *start_room, vector *start_pos, int *end_room,
                     vector *end_pos, float rad, int flags, int handle, int ignore_obj) {
  bool status;
  bool f_path_exists = true;

  ai_path_info *aip = &ai_info->path;

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: In free path\n");
  }
#endif
  AIPathFreePath(aip);

  //	if(ai_info->awareness <= AWARE_NONE && !(ai_info->flags & AIF_PERSISTANT))  // chrishack -- scalar max_nodes in
  // path by awareness 		return false;

  aip->goal_index = (goal *)goal_ptr - ai_info->goals;
  aip->goal_uid = ((goal *)goal_ptr)->goal_uid;

  status = AIPathAddDPath(aip, handle);

  if (status) {
    int slot = aip->path_id[0];
    int cur_node = 0;

    // Account for closed doors
    if (BOA_GetNextRoom(*start_room, *end_room) != BOA_NO_PATH) {
      bool f_make_alt = false;
      bool f_bline_ok = false;
      int last_room;
      fvi_query fq;
      fvi_info hit_info;

      fq.p0 = start_pos;
      fq.startroom = *start_room;
      fq.p1 = end_pos;
      fq.rad = obj->size - .1f;
      if (fq.rad <= 0.0f)
        fq.rad = .1f;
      fq.thisobjnum = OBJNUM(obj);
      fq.ignore_obj_list = NULL;
      fq.flags = FQ_CHECK_OBJS | FQ_NO_RELINK | FQ_IGNORE_WEAPONS | FQ_IGNORE_POWERUPS;

      int fate = fvi_FindIntersection(&fq, &hit_info);

      if (fate == HIT_NONE ||
          ((fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) && hit_info.hit_object[0] == ignore_obj)) {
        f_make_alt = false;
        f_bline_ok = true;
      } else if (BOA_Array[BOA_INDEX(*start_room)][BOA_INDEX(*end_room)] & BOAF_TOO_SMALL_FOR_ROBOT) {
        f_make_alt = true;
      } else if (BOA_HasPossibleBlockage(*start_room, *end_room)) {
        int next_room = BOA_INDEX(*start_room);

        ASSERT(next_room >= 0 && next_room <= Highest_room_index + 8);

        do {
          if (next_room != BOA_INDEX(*start_room) && BOA_LockedDoor(obj, next_room)) {
            f_make_alt = true;
            break;
          }

          last_room = next_room;
          next_room = BOA_GetNextRoom(next_room, *end_room);

          if (BOA_INDEX(last_room) != BOA_INDEX(next_room) && next_room != BOA_NO_PATH) {
            if (BOA_DetermineStartRoomPortal(last_room, NULL, next_room, NULL) == -1) {
              f_make_alt = true;
              break;
            }
          }
        } while (BOA_INDEX(next_room) != BOA_INDEX(*start_room) && (BOA_INDEX(next_room) != BOA_INDEX(*end_room)) &&
                 (next_room != BOA_NO_PATH));
      }

    error_make_alt:

      if (f_make_alt) {
        f_path_exists = AIFindAltPath(obj, *start_room, *end_room);

        if (f_path_exists) {
          bool f_bnode_ok = BNode_allocated && BNode_verified &&
                            !((ROOMNUM_OUTSIDE(*start_room) && TERRAIN_REGION(*start_room) == 0) ||
                              (ROOMNUM_OUTSIDE(*end_room) && TERRAIN_REGION(*end_room) == 0)) &&
                            !(ROOMNUM_OUTSIDE(*start_room) && ROOMNUM_OUTSIDE(*end_room) &&
                              TERRAIN_REGION(*start_room) != TERRAIN_REGION(*end_room));

          if (f_bnode_ok)
            f_path_exists =
                AIGenerateAltBNodePath(obj, start_pos, start_room, end_pos, end_room, aip, &slot, &cur_node, handle);
          else
            AIGenerateAltBOAPath(start_pos, end_pos, aip, &slot, &cur_node, handle);

          if (!f_path_exists) {
            mprintf(0, "Warning Alt path from %d to %d failed.\n", *start_room, *end_room);
          }
        }
      } else if (!f_bline_ok) {
        bool f_bnode_ok = BNode_allocated && BNode_verified &&
                          !((ROOMNUM_OUTSIDE(*start_room) && TERRAIN_REGION(*start_room) == 0) ||
                            (ROOMNUM_OUTSIDE(*end_room) && TERRAIN_REGION(*end_room) == 0)) &&
                          !(ROOMNUM_OUTSIDE(*start_room) && ROOMNUM_OUTSIDE(*end_room) &&
                            TERRAIN_REGION(*start_room) != TERRAIN_REGION(*end_room));

        if (f_bnode_ok)
          f_path_exists =
              AIGenerateBNodePath(obj, start_pos, start_room, end_pos, end_room, aip, &slot, &cur_node, handle);
        else
          f_path_exists = AIGenerateBOAPath(start_pos, start_room, end_pos, end_room, aip, &slot, &cur_node, handle);

        if (!f_path_exists) {
          f_make_alt = true;
          goto error_make_alt;
        }
      }

      if (f_path_exists) {
        // Add the end point
        AIPathAddDPathNode(aip, &slot, &cur_node, end_pos, *end_room, handle);

        // Makes sure that the last dynamic path
        AIDynamicPath[slot].num_nodes = cur_node;
      }
    } else {
      f_path_exists = false;
      // if(!(0x80000000 & *start_room) || !(0x80000000 & *end_room))
      // mprintf(0, "No path available from %d to %d\n", *start_room, *end_room);

#ifdef _DEBUG
      if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
        mprintf(0, "AI Note: In free path\n");
      }
#endif

      AIPathFreePath(aip);
      return false;
    }
  } else {
    f_path_exists = false;
    mprintf(0, "No dynamic paths left\n");
  }

  if (!f_path_exists) {
#ifdef _DEBUG
    if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
      mprintf(0, "AI Note: In free path\n");
    }
#endif

    AIPathFreePath(aip);
    return false;
  }

  return true;
}

bool AIPathSetAsStaticPath(object *obj, void *goal_ptr, int path_id, int start_node, int end_node, int cur_node) {
  bool status;
  ai_frame *ai_info = obj->ai_info;
  ai_path_info *aip = &ai_info->path;

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: In free path\n");
  }
#endif
  AIPathFreePath(aip);

  aip->goal_index = (goal *)goal_ptr - ai_info->goals;
  aip->goal_uid = ((goal *)goal_ptr)->goal_uid;

  status = AIPathAddStaticPath(aip, path_id, start_node, end_node);

  if (status) {
    aip->cur_node = cur_node;
  }

  return status;
}

#ifdef _DEBUG

#include "hud.h"

int AIPath_test_end_room = 0;
vector AIPath_test_end_pos = {0, 0, 0};

bool MakeTestPath(int *start_room, vector *pos) {
  bool status;
  ai_frame ai_info;
  int count = 0;

  ai_info.awareness = AWARE_MOSTLY;

  AIPathInitPath(&ai_info.path);

  status = AIPathAllocPath(NULL, &ai_info, &ai_info.goals[0], start_room, pos, &AIPath_test_end_room,
                           &AIPath_test_end_pos, 0.0f, 0, 0);

  while (status) {
    vector pos;
    int room;

    status = AIPathGetCurrentNodePos(&ai_info.path, &pos, &room);

    if (status) {
      int id = FindObjectIDName("Shield");
      ObjCreate(OBJ_POWERUP, id, room, &pos, &Identity_matrix);
      count++;
    }

    status = AIPathMoveToNextNode(&ai_info.path);
  }

  AddHUDMessage("The test path has %d nodes.", count);

  //	#ifdef _DEBUG
  //	if(AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index)
  //	{
  //		mprintf(0, "AI Note: In free path\n");
  //	}
  //	#endif
  AIPathFreePath(&ai_info.path);

  return true;
}

#endif
