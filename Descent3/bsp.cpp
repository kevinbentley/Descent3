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

 * $Logfile: /DescentIII/main/bsp.cpp $
 * $Revision: 32 $
 * $Date: 4/19/00 10:18a $
 * $Author: Matt $
 *
 * Some more of BSP tree code, I presume.
 *
 * $Log: /DescentIII/main/bsp.cpp $
 *
 * 32    4/19/00 10:18a Matt
 * Added check for BSP tree initialized before freeing it.
 *
 * 31    4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 30    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 29    9/22/98 12:01p Matt
 * Added SourceSafe headers
 *
 */

#include "bsp.h"
#include "room.h"
#include "mem.h"
#include "polymodel.h"
#include <stdlib.h>
#include "object.h"
#include "psrand.h"

#define BSP_TREE_VERSION 10003

bsptree MineBSP;
uint8_t BSP_initted = 0;
static int ConvexSubspaces = 0, ConvexPolys = 0;
static int Solids = 0, Empty = 0;

int BSPChecksum = -1;
static uint8_t UseBSP = 0;

// Goes through all the valid points in the indoor engine and returns a unique
// checksum
int BSPGetMineChecksum() {
  int i, t, k;
  float total = 0;
  int checksum;

  for (i = 0; i <= Highest_room_index; i++) {
    room *rp = &Rooms[i];

    if (!Rooms[i].used)
      continue;

    if (Rooms[i].flags & RF_EXTERNAL)
      continue;

    for (t = 0; t < rp->num_faces; t++) {
      face *fp = &rp->faces[t];

      for (k = 0; k < fp->num_verts; k++) {
        total += rp->verts[fp->face_verts[k]].x;
        total += rp->verts[fp->face_verts[k]].y;
        total += rp->verts[fp->face_verts[k]].z;
      }
    }
  }

  for (t = 0; t <= Highest_object_index; t++) {
    object *obj = &Objects[t];
    vector vert;

    if (obj->type == OBJ_NONE)
      continue;

    if (OBJECT_OUTSIDE(obj))
      continue;

    if (obj->lighting_render_type == LRT_LIGHTMAPS) {
      poly_model *po = &Poly_models[obj->rtype.pobj_info.model_num];
      if (!po->new_style)
        continue;

      for (k = 0; k < po->n_models; k++) {
        bsp_info *sm = &po->submodel[k];

        if (IsNonRenderableSubmodel(po, k))
          continue;

        for (int j = 0; j < sm->num_faces; j++) {
          for (int x = 0; x < sm->faces[j].nverts; x++) {
            GetObjectPointInWorld(&vert, obj, k, sm->faces[j].vertnums[x]);
            total += vert.x;
            total += vert.y;
            total += vert.z;
          }
        }
      }
    }
  }

  checksum = total * BSP_TREE_VERSION;

  return checksum;
}

// Allocates memory for a bspnode
// Returns pointer to node
bspnode *NewBSPNode(void) {
  bspnode *node;

  if ((node = (bspnode *)mem_malloc(sizeof(bspnode))) == NULL) {
    return NULL;
  }

  /* Initialize the node, set its variables to zero */

  node->type = BSP_NODE;
  node->polylist = NULL;
  node->num_polys = 0;
  node->node_facenum = 0;
  node->node_roomnum = 0;
  node->node_subnum = 0;

  node->plane.a = 0.0;
  node->plane.b = 0.0;
  node->plane.c = 0.0;
  node->plane.d = 0.0;
  node->front = NULL;
  node->back = NULL;

  return node;
}

// Allocates memory for a polygon
// Returns pointer to polygon
bsppolygon *NewPolygon(int roomnum, int facenum, int numverts) {
  bsppolygon *newpoly;
  vector *verts;

  newpoly = (bsppolygon *)mem_malloc(sizeof(bsppolygon));

  if (newpoly == NULL) {
    mprintf(0, "NewPolygon: Couldn't allocate polygon\n");
    return NULL;
  }

  verts = (vector *)mem_malloc(sizeof(vector) * numverts);
  ASSERT(verts != NULL);

  newpoly->nv = numverts;
  newpoly->verts = verts;

  newpoly->roomnum = roomnum;
  newpoly->facenum = facenum;
  newpoly->color = ps_rand() * ps_rand();

  return newpoly;
}

// Saves and BSP node to an open file and recurses with the nodes children
void SaveBSPNode(CFILE *outfile, bspnode *node) {
  if (node->type == BSP_SOLID_LEAF) {
    cf_WriteByte(outfile, BSP_SOLID_LEAF);
  } else if (node->type == BSP_EMPTY_LEAF) {
    cf_WriteByte(outfile, BSP_EMPTY_LEAF);
  } else {
    ASSERT(node->front);
    ASSERT(node->back);

    cf_WriteByte(outfile, BSP_NODE);

    // Write out this planes node
    cf_WriteFloat(outfile, node->plane.a);
    cf_WriteFloat(outfile, node->plane.b);
    cf_WriteFloat(outfile, node->plane.c);
    cf_WriteFloat(outfile, node->plane.d);
    cf_WriteShort(outfile, node->node_roomnum);
    cf_WriteShort(outfile, node->node_facenum);
    cf_WriteByte(outfile, node->node_subnum);

    // Write out its children
    SaveBSPNode(outfile, node->front);
    SaveBSPNode(outfile, node->back);
  }
}

// Loads a bsp node from an open file and recurses with its children
void LoadBSPNode(CFILE *infile, bspnode **node) {
  // Get the node type
  uint8_t type = cf_ReadByte(infile);

  // Allocate the node and set its type
  *node = NewBSPNode();
  ASSERT(*node);
  bspnode *localnode = *node;

  localnode->type = type;

  if (type == BSP_EMPTY_LEAF || type == BSP_SOLID_LEAF)
    return;

  // Load the nodes plane
  localnode->plane.a = cf_ReadFloat(infile);
  localnode->plane.b = cf_ReadFloat(infile);
  localnode->plane.c = cf_ReadFloat(infile);
  localnode->plane.d = cf_ReadFloat(infile);
  localnode->node_roomnum = cf_ReadShort(infile);
  localnode->node_facenum = cf_ReadShort(infile);
  localnode->node_subnum = cf_ReadByte(infile);

  // Recurse to get the children
  LoadBSPNode(infile, &localnode->front);
  LoadBSPNode(infile, &localnode->back);
}

// Frees up a polygon and all the vertices associated with it
void FreePolygon(bsppolygon *poly) {
  ASSERT(poly != NULL);
  ASSERT(poly->nv > 2);

  if (poly->nv > 0) {
    mem_free(poly->verts);
  }

  mem_free(poly);
}

// Calculates the plane equation for a given polygon
void CalculatePolygonPlane(bsppolygon *poly) {
  ASSERT(poly->nv >= 3);

  vector *vec = &poly->verts[0];

  poly->plane.d = -(vec->x * poly->plane.a + vec->y * poly->plane.b + vec->z * poly->plane.c);
}

// Classifies whether or not a point is in front,behind, or on a plane
int ClassifyVector(bspplane *plane, vector *vec) {
  float dist;

  dist = vec->x * plane->a + vec->y * plane->b + vec->z * plane->c + plane->d;

  if (dist > BSP_EPSILON)
    return BSP_IN_FRONT;
  else if (dist < -BSP_EPSILON)
    return BSP_BEHIND;

  return BSP_ON_PLANE;
}

// Classifies whether or not a polygon is behind,in front, or straddles a plane
int ClassifyPolygon(bspplane *plane, bsppolygon *poly) {
  int numfront, numback, numon;
  int i;
  int nv = poly->nv;

  ASSERT(nv >= 3);

  numfront = numback = numon = 0;

  for (i = 0; i < nv; i++) {
    int fate;
    vector *vec = &poly->verts[i];

    fate = ClassifyVector(plane, vec);

    switch (fate) {
    case BSP_IN_FRONT:
      numfront++;
      break;
    case BSP_BEHIND:
      numback++;
      break;
    case BSP_ON_PLANE:
      numfront++;
      numback++;
      numon++;
      break;
    }
  }

  if (numon == nv) {
    return BSP_COINCIDENT;
  } else if (numfront == nv) {
    return BSP_IN_FRONT;
  } else if (numback == nv) {
    return BSP_BEHIND;
  }

  // The polygon straddles the plane
  return BSP_SPANNING;
}

// Tries to split a polygon across a plane
int SplitPolygon(bspplane *plane, bsppolygon *testpoly, bsppolygon **frontpoly, bsppolygon **backpoly) {
  float dists[256], t;
  int numvert, numfront, numback, i, codes[256] = {};
  vector *frontvert[256], *backvert[256], *polyvert[256];
  vector *vertptr1, *vertptr2;
  vector delta, *newvert[256];
  int num_new_verts = 0;

  /* Set up the function. Set all counters, variables, lists etc to
   * zero or NULL, which provides a fall back result, should nothing
   * be changed, and simply means that particular result is to be
   * ignored
   */

  numvert = testpoly->nv;
  numfront = numback = 0;

  /* Now, we shall classify each vertex in the polygon, with both
   * a plane distance, and a classification code. This is done here,
   * as the results are often re-used, which saves time.
   */

  for (i = 0; i < numvert; i++) {
    vertptr1 = &testpoly->verts[i];
    polyvert[i] = vertptr1;
    codes[i] = ClassifyVector(plane, vertptr1);
    dists[i] = plane->a * vertptr1->x + plane->b * vertptr1->y + plane->c * vertptr1->z + plane->d;
  }

  /* We must duplicate the first entry in the numvert+1 slot, so that
   * we can use wraparound to easily check things
   */

  codes[numvert] = codes[0];
  dists[numvert] = dists[0];

  /* Now, the actual splitting work. We must work through each vertex
   * of the polygon, examining it with regard to the plane
   * Where the classification codes differ, we have to split
   */

  for (i = 0; i < numvert; i++) {
    vertptr1 = polyvert[i];

    /* A point is found to be on the plane. This counts for
     * both polygons, as often a vertex may lie along a plane,
     * but will not be splitting it
     */

    if (codes[i] == BSP_ON_PLANE) {
      frontvert[numfront++] = vertptr1;
      backvert[numback++] = vertptr1;
    } else if (codes[i] == BSP_IN_FRONT) {
      /* Simple cases of point being in front or behind
       * the plane. Just insert them to the appropriate
       * lists.
       */
      frontvert[numfront++] = vertptr1;
    } else if (codes[i] == BSP_BEHIND) {
      backvert[numback++] = vertptr1;
    }

    /* If we're on the plane, or, the next point is the same
     * side of the plane as this point, go to the next vertex
     */

    if ((codes[i] == BSP_ON_PLANE) || (codes[i] == codes[i + 1]))
      continue;

    /* Now, we need to generate a split point. This is just
     * standard ray-plane intersection stuff. Now this is where
     * pre-calculating the distances etc comes in handy, as
     * we're using them a lot...
     */

    vertptr2 = polyvert[(i + 1) % numvert];
    t = dists[i] / (dists[i] - dists[i + 1]);
    newvert[num_new_verts] = (vector *)mem_malloc(sizeof(vector));

    /* Now we must generate the split point. This is simply
     * an equation in the form Origin + t*Direction
     */

    delta = *vertptr2 - *vertptr1;
    *newvert[num_new_verts] = *vertptr1 + (t * delta);

    /*		vector tempvec=*newvert[num_new_verts]-*vertptr1;
                    float mag=vm_GetMagnitude(&tempvec);
                    if (mag<=BSP_EPSILON)
                            Int3();		*/

    frontvert[numfront++] = newvert[num_new_verts];
    backvert[numback++] = newvert[num_new_verts];
    num_new_verts++;
  }

  /* Now, we must construct the polygons, given the vertex lists
   * If the number of vertices is invalid, we don't do anything ...
   */

  ASSERT(numfront >= 3);
  ASSERT(numback >= 3);

  (*frontpoly) = NewPolygon(testpoly->roomnum, testpoly->facenum, numfront);
  (*backpoly) = NewPolygon(testpoly->roomnum, testpoly->facenum, numback);

  for (i = 0; i < numfront; i++) {
    bsppolygon *temppoly = *frontpoly;
    temppoly->verts[i] = *frontvert[i];
    temppoly->plane = testpoly->plane;
    temppoly->facenum = testpoly->facenum;
    temppoly->roomnum = testpoly->roomnum;
    temppoly->subnum = testpoly->subnum;
  }

  for (i = 0; i < numback; i++) {
    bsppolygon *temppoly = *backpoly;
    temppoly->verts[i] = *backvert[i];
    temppoly->plane = testpoly->plane;
    temppoly->facenum = testpoly->facenum;
    temppoly->roomnum = testpoly->roomnum;
    temppoly->subnum = testpoly->subnum;
  }

  for (i = 0; i < num_new_verts; i++)
    mem_free(newvert[i]);

  return 1;
}

char Twirly[] = {'|', '/', '-', '\\'};
uint8_t Plane_twirl = 0;
uint8_t Node_twirl = 0;

// Selects the best plane to partition with, returning the pointer to polygon to split with
bsppolygon *SelectPlane(listnode **polylist) {
  listnode *outer, *inner;
  bsppolygon *outerpoly, *innerpoly, *bestpoly;
  int splits, front, back, planar, result, balance;
  float score, bestscore;
  float g_kbalance = 1.0;
  float g_ksplit = 0.0;
  float g_kplanar = 0.0;
  int checked = 0;

  bestscore = 9999999.0;
  bestpoly = NULL;

  /*	Iterate through every polygon, checking its plane against all
   * the other polygons. But don't check it against itself
   */

  mprintf_at(2, 4, 0, "Plane = %c", Twirly[(Plane_twirl++) % 4]);

  for (outer = *polylist; outer != NULL; outer = outer->next) {
    outerpoly = (bsppolygon *)outer->data;
    splits = front = back = planar = 0;
    score = 0.0;

    if (outerpoly->plane.used)
      continue;

    // Only check 300 times
    if (checked >= 300)
      return bestpoly;

    for (inner = *polylist; inner != NULL; inner = inner->next) {
      innerpoly = (bsppolygon *)inner->data;
      if (innerpoly != outerpoly) {
        result = ClassifyPolygon(&outerpoly->plane, innerpoly);
        switch (result) {
        case BSP_SPANNING:
          splits++;
          break;
        case BSP_IN_FRONT:
          front++;
          break;
        case BSP_BEHIND:
          back++;
          break;
        case BSP_COINCIDENT:
          planar++;
          break;
        }
      }
    }

    /* Calculate the score. If we have a "perfect" tree, ie
     * it has either no splits, or is perfectly balanced,
     * return the plane to the caller
     */

    balance = abs(front - back);
    score = g_kbalance * balance + g_ksplit * splits + g_kplanar * planar;

    checked++;

    if (score < 0.005)
      return outerpoly;

    if (score < bestscore) {
      bestscore = score;
      bestpoly = outerpoly;
    }
  }

  return bestpoly;
}

// This is the routine that recursively builds the bsptree
int BuildBSPNode(bspnode *tree, listnode **polylist, int numpolys) {
  bsppolygon *partition_poly;
  listnode *lnode = *polylist;
  listnode *next;
  bspnode *frontnode, *backnode;
  listnode *frontlist = NULL, *backlist = NULL;
  bspplane partition_plane;
  int numfront = 0, numback = 0, numsplits = 0;

  ASSERT(numpolys > 0);
  partition_poly = SelectPlane(polylist);

  mprintf_at(2, 5, 0, "Node = %c", Twirly[(Node_twirl++) % 4]);

  if (partition_poly == NULL) {
    // We hit a leaf!  Fill in the appropriate leaf stuff

    /*vector center;
    int total=0;

    vm_MakeZero (&center);

    for (int i=0;i<numpolys;i++)
    {
            bsppolygon *poly=(bsppolygon *)GetListItem (polylist,i);
            ASSERT (poly!=NULL);
            AddListItem (&tree->polylist,poly);
            tree->num_polys++;
            vector polycenter;

            ConvexPolys++;
            vm_MakeZero (&polycenter);

            // Find out if this is a solid or empty leaf
            // This routine may cause some problems because of convex subspace
            for (int t=0;t<poly->nv;t++)
            {
                    polycenter+=poly->verts[t];

            }

            polycenter/=poly->nv;
            center+=polycenter;

    }

    center/=numpolys;
    int ins=0,outs=0;

    for (i=0;i<numpolys;i++)
    {
            bsppolygon *thispoly=(bsppolygon *)GetListItem (polylist,i);
            int fate=ClassifyVector (&thispoly->plane,&center);

            if (fate==BSP_IN_FRONT || fate==BSP_ON_PLANE)
            {
                    outs++;
            }
            else
                    ins++;

    }

    if (ins==numpolys)
    {
            tree->type=BSP_SOLID_LEAF;
            Solids++;
    }
    else if (outs==numpolys)
    {
            tree->type=BSP_EMPTY_LEAF;
            Empty++;
    }
    else
    {
            mprintf(0,"Ins/outs don't match! ins=%d outs=%d np=%d\n",ins,outs,numpolys);

            for (i=0;i<numpolys;i++)
            {
                    bsppolygon *thispoly=(bsppolygon *)GetListItem (polylist,i);
                    mprintf(0,"Poly %d: Room=%d facenum=%d\n",i,thispoly->roomnum,thispoly->facenum);
            }

            if (ins>outs)
            {
                    tree->type=BSP_SOLID_LEAF;
                    Solids++;
            }
            else
            {
                    tree->type=BSP_EMPTY_LEAF;
                    Empty++;
            }

    }*/

    tree->type = BSP_EMPTY_LEAF;

    ConvexSubspaces++;
    return 1;
  }

  // We need to process this node and classify all child polygons
  tree->node_facenum = partition_poly->facenum;
  tree->node_roomnum = partition_poly->roomnum;
  tree->node_subnum = partition_poly->subnum;

  partition_poly->plane.used = 1;
  tree->plane = partition_poly->plane;
  partition_plane = partition_poly->plane;

  frontlist = backlist = NULL;

  for (lnode = *polylist; lnode != NULL; lnode = next) {
    next = lnode->next;

    bsppolygon *testpoly = (bsppolygon *)lnode->data;
    int fate = ClassifyPolygon(&partition_plane, testpoly);

    if (fate == BSP_IN_FRONT) {
      AddListItem(&frontlist, testpoly);
      numfront++;
    } else if (fate == BSP_BEHIND) {
      AddListItem(&backlist, testpoly);
      numback++;
    } else if (fate == BSP_COINCIDENT) {
      // Test to see if this plane is exactly the same as the partition plane
      // If so, remove it from the list.  If its facing the other way, send it down the back list
      float dot = testpoly->plane.a * partition_plane.a + testpoly->plane.b * partition_plane.b +
                  testpoly->plane.c * partition_plane.c;

      if (dot > -BSP_EPSILON) {
        // Send down front list and deactivate this plane
        AddListItem(&frontlist, testpoly);
        numfront++;
        // testpoly->plane.used=1;
      } else {
        AddListItem(&frontlist, testpoly);
        // testpoly->plane.used=1;
        numfront++;
      }
    } else {
      // Must split this polygon
      ASSERT(fate == BSP_SPANNING);
      bsppolygon *frontpoly, *backpoly;

      numsplits++;

      SplitPolygon(&partition_plane, testpoly, &frontpoly, &backpoly);

      numfront++;
      numback++;
      AddListItem(&frontlist, frontpoly);
      AddListItem(&backlist, backpoly);

      RemoveListItem(polylist, testpoly);
      FreePolygon(testpoly);
    }
  }

  // mprintf(0,"BuildBSPNode: Incoming=%d numfront=%d numback=%d splits=%d\n",numpolys,numfront,numback,numsplits);

  if (frontlist != NULL) {
    if ((frontnode = NewBSPNode()) == NULL) {
      mprintf(0, "BuildBSPNode: Error, can't allocate front node\n");
      return 0;
    }

    if (!BuildBSPNode((bspnode *)frontnode, &frontlist, numfront)) {
      mprintf(0, "BuildBSPNode: Error building front node\n");
      return 0;
    }

    tree->front = frontnode;
    DestroyList(&frontlist);
  } else {
    if ((frontnode = NewBSPNode()) == NULL) {
      mprintf(0, "BuildBSPNode: Error, can't allocate front node\n");
      return 0;
    }
    frontnode->type = BSP_EMPTY_LEAF;
    tree->front = frontnode;
  }

  if (backlist != NULL) {
    if ((backnode = NewBSPNode()) == NULL) {
      mprintf(0, "BuildBSPNode: Error, can't allocate front node\n");
      return 0;
    }

    if (!BuildBSPNode((bspnode *)backnode, &backlist, numback)) {
      mprintf(0, "BuildBSPNode: Error building back node\n");
      return 0;
    }

    tree->back = backnode;
    DestroyList(&backlist);
  } else {
    if ((backnode = NewBSPNode()) == NULL) {
      mprintf(0, "BuildBSPNode: Error, can't allocate front node\n");
      return 0;
    }

    backnode->type = BSP_SOLID_LEAF;
    tree->back = backnode;
  }

  return 1;
}

// Releases memory for a bspnode.  This function calls itself recursively
void DestroyBSPNode(bspnode *node) {
  if (node->type == BSP_NODE) {
    if (node->front)
      DestroyBSPNode(node->front);
    if (node->back)
      DestroyBSPNode(node->back);
  }

  int np = CountListItems(&node->polylist);

  for (int i = 0; i < np; i++) {
    bsppolygon *poly = (bsppolygon *)GetListItem(&node->polylist, i);
    FreePolygon(poly);
  }
  if (np > 0)
    DestroyList(&node->polylist);

  mem_free(node);
}

// Walks the BSP tree and frees up any nodes/polygons that we might be using
void DestroyBSPTree(bsptree *tree) {
  if (BSP_initted == 0)
    return;

  mprintf(0, "Destroying bsptree!\n");
  DestroyBSPNode(tree->root);
  BSP_initted = 0;
}

// Destroys the mines BSP tree at shutdown
void DestroyDefaultBSPTree() { DestroyBSPTree(&MineBSP); }

// Given an object, a submodel, and a vertex number, calculates the world position
// of that point
void GetObjectPointInWorld(vector *dest, object *obj, int subnum, int vertnum);

// Builds a bsp tree for the indoor rooms
void BuildBSPTree() {
  int i, t, k, j, x;
  int numpolys = 0;
  int check;

  if (!UseBSP)
    return;

  // Check to see if we even need to build a new tree
  check = BSPGetMineChecksum();

  if (check == BSPChecksum) {
    mprintf(0, "BSP tree already built!\n");
    return; // The BSP tree has already been built for this mine
  }

  BSPChecksum = check;

  // Free up any BSP trees that we might have lying around
  InitDefaultBSP();

  MineBSP.root = NewBSPNode();
  ASSERT(MineBSP.root);

  mprintf(0, "Building BSP Tree...\n");

  mprintf(0, "Adding polygons to tree\n");

  // Go through the whole mine and add each polygon to the possible BSP
  // partition list.  Don't include portals...
  for (i = 0; i <= Highest_room_index; i++) {
    bsppolygon *newpoly;

    if (Rooms[i].used == 0 || (Rooms[i].flags & RF_EXTERNAL))
      continue;

    room *rp = &Rooms[i];

    for (t = rp->objects; (t != -1); t = Objects[t].next) {
      object *obj = &Objects[t];

      if (obj->type == OBJ_NONE)
        continue;

      if (OBJECT_OUTSIDE(obj))
        continue;

      if (obj->lighting_render_type == LRT_LIGHTMAPS) {
        poly_model *po = &Poly_models[obj->rtype.pobj_info.model_num];

        if (!po->new_style)
          continue;

        for (k = 0; k < po->n_models; k++) {
          bsp_info *sm = &po->submodel[k];

          if (IsNonRenderableSubmodel(po, k))
            continue;

          for (j = 0; j < sm->num_faces; j++) {
            vector world_verts[64];

            newpoly = NewPolygon(i, t, sm->faces[j].nverts);
            if (!newpoly) {
              mprintf(0, "Couldn't get a new polygon!\n");
              Int3();
              return;
            }

            ASSERT(sm->faces[j].nverts < 64);
            for (x = 0; x < sm->faces[j].nverts; x++)
              GetObjectPointInWorld(&world_verts[x], obj, k, sm->faces[j].vertnums[x]);

            vector norm;

            vm_GetNormal(&norm, &world_verts[0], &world_verts[1], &world_verts[2]);

            // Add the vertices to this poly
            for (x = 0; x < sm->faces[j].nverts; x++)
              newpoly->verts[x] = world_verts[x];

            newpoly->plane.a = norm.x;
            newpoly->plane.b = norm.y;
            newpoly->plane.c = norm.z;

            CalculatePolygonPlane(newpoly);

            // Add it to our bsp list
            AddListItem(&MineBSP.polylist, newpoly);

            newpoly->plane.used = 0;
            numpolys++;

            newpoly->roomnum = t;
            newpoly->facenum = j;
            newpoly->subnum = k;
          }
        }
      }
    }

    for (t = 0; t < Rooms[i].num_faces; t++) {

      // Don't include portals in BSP calculation
      // Unless they go outside
      if (Rooms[i].faces[t].portal_num != -1) {
        if (Rooms[i].portals[Rooms[i].faces[t].portal_num].croom >= 0)
          continue;
      }

      // Construct a new polygon
      newpoly = NewPolygon(i, t, Rooms[i].faces[t].num_verts);
      if (!newpoly) {
        mprintf(0, "Couldn't get a new polygon!\n");
        Int3();
        return;
      }

      // Add the vertices to this poly
      for (k = 0; k < Rooms[i].faces[t].num_verts; k++)
        newpoly->verts[k] = Rooms[i].verts[Rooms[i].faces[t].face_verts[k]];

      newpoly->plane.a = Rooms[i].faces[t].normal.x;
      newpoly->plane.b = Rooms[i].faces[t].normal.y;
      newpoly->plane.c = Rooms[i].faces[t].normal.z;

      CalculatePolygonPlane(newpoly);

      // Add it to our bsp list
      AddListItem(&MineBSP.polylist, newpoly);

      newpoly->plane.used = 0;

      newpoly->roomnum = i;
      newpoly->facenum = t;
      newpoly->subnum = -1;

      numpolys++;
    }
  }

  ConvexSubspaces = 0;
  ConvexPolys = 0;
  Solids = 0;
  Empty = 0;

  mprintf(0, "%d polygons added, starting node building...\n", numpolys);

  // Build the BSP tree!
  BuildBSPNode(MineBSP.root, &MineBSP.polylist, numpolys);
  DestroyList(&MineBSP.polylist);

  // Print some stats
  mprintf(0, "Total number of convex subspaces=%d\n", ConvexSubspaces);
  mprintf(0, "Total number of convex polys=%d\n", ConvexPolys);
  mprintf(0, "Solid=%d Empty=%d\n", Solids, Empty);
}

// Builds a bsp tree for a single room
void BuildSingleBSPTree(int roomnum) {
  int i, t, k, j, x;
  int numpolys = 0;

  if (!UseBSP)
    return;

  // Free up any BSP trees that we might have lying around
  InitDefaultBSP();

  MineBSP.root = NewBSPNode();
  ASSERT(MineBSP.root);

  mprintf(0, "Building BSP Tree...\n");

  // Go through the whole mine and add each polygon to the possible BSP
  // partition list.  Don't include portals...

  i = roomnum;
  bsppolygon *newpoly;

  for (t = 0; t <= Highest_object_index; t++) {
    object *obj = &Objects[t];

    if (obj->type == OBJ_NONE)
      continue;

    if (OBJECT_OUTSIDE(obj))
      continue;
    if (obj->roomnum != i)
      continue;

    if (obj->lighting_render_type == LRT_LIGHTMAPS) {
      poly_model *po = &Poly_models[obj->rtype.pobj_info.model_num];
      if (!po->new_style)
        continue;

      for (k = 0; k < po->n_models; k++) {
        bsp_info *sm = &po->submodel[k];

        if (IsNonRenderableSubmodel(po, k))
          continue;

        for (j = 0; j < sm->num_faces; j++) {
          vector world_verts[64];
          newpoly = NewPolygon(i, t, sm->faces[j].nverts);
          if (!newpoly) {
            mprintf(0, "Couldn't get a new polygon!\n");
            Int3();
            return;
          }

          for (x = 0; x < sm->faces[j].nverts; x++)
            GetObjectPointInWorld(&world_verts[x], obj, k, sm->faces[j].vertnums[x]);

          vector norm;

          vm_GetNormal(&norm, &world_verts[0], &world_verts[1], &world_verts[2]);

          // Add the vertices to this poly
          for (x = 0; x < sm->faces[j].nverts; x++)
            newpoly->verts[x] = world_verts[x];

          newpoly->plane.a = norm.x;
          newpoly->plane.b = norm.y;
          newpoly->plane.c = norm.z;

          CalculatePolygonPlane(newpoly);

          // Add it to our bsp list
          AddListItem(&MineBSP.polylist, newpoly);

          newpoly->plane.used = 0;
          numpolys++;
        }
      }
    }
  }

  for (t = 0; t < Rooms[i].num_faces; t++) {
    // Don't include portals in BSP calculation
    if (Rooms[i].faces[t].portal_num != -1)
      continue;

    // Construct a new polygon
    newpoly = NewPolygon(i, t, Rooms[i].faces[t].num_verts);
    if (!newpoly) {
      mprintf(0, "Couldn't get a new polygon!\n");
      Int3();
      return;
    }
    // Add the vertices to this poly
    for (k = 0; k < Rooms[i].faces[t].num_verts; k++)
      newpoly->verts[k] = Rooms[i].verts[Rooms[i].faces[t].face_verts[k]];

    newpoly->plane.a = Rooms[i].faces[t].normal.x;
    newpoly->plane.b = Rooms[i].faces[t].normal.y;
    newpoly->plane.c = Rooms[i].faces[t].normal.z;

    CalculatePolygonPlane(newpoly);

    // Add it to our bsp list
    AddListItem(&MineBSP.polylist, newpoly);

    newpoly->plane.used = 0;
    numpolys++;
  }

  ConvexSubspaces = 0;
  ConvexPolys = 0;
  Solids = 0;
  Empty = 0;

  // Build the BSP tree!
  BuildBSPNode(MineBSP.root, &MineBSP.polylist, numpolys);
  DestroyList(&MineBSP.polylist);

  // Print some stats
  mprintf(0, "Total number of convex subspaces=%d\n", ConvexSubspaces);
  mprintf(0, "Total number of convex polys=%d\n", ConvexPolys);
  mprintf(0, "Solid=%d Empty=%d\n", Solids, Empty);

  BSPChecksum = -1;
}

// Returns true if the point is inside the min,max
static inline int BSPInMinMax(vector *pos, vector *min_xyz, vector *max_xyz) {
  if (pos->x < min_xyz->x || pos->y < min_xyz->y || pos->z < min_xyz->z || pos->x > max_xyz->x || pos->y > max_xyz->y ||
      pos->z > max_xyz->z)
    return 0;

  return 1;
}
// see if a point in inside a face by projecting into 2d
extern uint32_t check_point_to_face(vector *colp, vector *face_normal, int nv, vector **vertex_ptr_list);

// Returns true if passed in point collides with a nodes polygon
static inline int BSPPointInPolygon(vector *pos, bspnode *node) {
  if (node->node_subnum < 0) // Room face
  {
    room *rp = &Rooms[node->node_roomnum];
    face *fp = &rp->faces[node->node_facenum];
    if (!(BSPInMinMax(pos, &fp->min_xyz, &fp->max_xyz)))
      return 0;

    // Test to see if this point in inside the polygon
    vector verts[MAX_VERTS_PER_FACE], *vertp[MAX_VERTS_PER_FACE];
    for (int i = 0; i < fp->num_verts; i++) {
      verts[i] = rp->verts[fp->face_verts[i]];
      vertp[i] = &verts[i];
    }

    if ((check_point_to_face(pos, &fp->normal, fp->num_verts, vertp)))
      return 0;

    return 1;
  } else // Object face
  {
    object *obj = &Objects[node->node_roomnum];

    if (!(BSPInMinMax(pos, &obj->min_xyz, &obj->max_xyz)))
      return 0;

    // Test to see if this point in inside the polygon
    vector verts[MAX_VERTS_PER_FACE], *vertp[MAX_VERTS_PER_FACE];
    vector norm;
    poly_model *po = &Poly_models[obj->rtype.pobj_info.model_num];
    bsp_info *sm = &po->submodel[node->node_subnum];

    for (int i = 0; i < sm->faces[node->node_facenum].nverts; i++) {
      GetObjectPointInWorld(&verts[i], obj, node->node_subnum, sm->faces[node->node_facenum].vertnums[i]);
      vertp[i] = &verts[i];
    }

    norm.x = node->plane.a;
    norm.y = node->plane.b;
    norm.z = node->plane.c;

    if ((check_point_to_face(pos, &norm, sm->faces[node->node_facenum].nverts, vertp)))
      return 0;

    return 1;
  }

  return 0;
}

// Runs a ray through the bsp tree
// Returns true if a ray is occludes
#define MAX_RAY_STACK 1000
#define PUSH_BSP_RAY(s, e, n)                                                                                          \
  {                                                                                                                    \
    stack_start[si] = s;                                                                                               \
    stack_end[si] = e;                                                                                                 \
    stack_node[si] = n;                                                                                                \
    si++;                                                                                                              \
    ASSERT(si < MAX_RAY_STACK);                                                                                        \
  }
#define POP_BSP_RAY()                                                                                                  \
  {                                                                                                                    \
    si--;                                                                                                              \
    start = stack_start[si];                                                                                           \
    end = stack_end[si];                                                                                               \
    node = stack_node[si];                                                                                             \
  }

vector stack_start[MAX_RAY_STACK], stack_end[MAX_RAY_STACK];
bspnode *stack_node[MAX_RAY_STACK];
static int si;

int BSPRayOccluded(vector *line_start, vector *line_end, bspnode *start_node) {
  si = 0;
  vector start, end;
  bspnode *node;

  PUSH_BSP_RAY(*line_start, *line_end, start_node);

  while (si > 0) {
    POP_BSP_RAY();
    while (node->type == BSP_NODE) {
      float dist1 = node->plane.a * start.x + node->plane.b * start.y + node->plane.c * start.z + node->plane.d;
      float dist2 = node->plane.a * end.x + node->plane.b * end.y + node->plane.c * end.z + node->plane.d;

      if (dist1 >= 0 && dist2 >= 0) {
        node = (bspnode *)node->front;
      } else if (dist1 < 0 && dist2 < 0) {
        node = (bspnode *)node->back;
      } else {
        vector mid, delta;
        float t;

        // Generate split point
        t = dist1 / (dist1 - dist2);
        delta = end - start;
        mid = start + (t * delta);
        if (BSPPointInPolygon(&mid, node))
          return 1;

        // vm_NormalizeVectorFast (&delta);

        vector mid1 = mid; //-(delta*BSP_EPSILON);
        vector mid2 = mid; //+(delta*BSP_EPSILON);

        if (dist1 >= 0.0) {
          PUSH_BSP_RAY(mid1, end, (bspnode *)node->back);
          PUSH_BSP_RAY(start, mid2, (bspnode *)node->front);
        } else {
          PUSH_BSP_RAY(mid2, end, (bspnode *)node->front);
          PUSH_BSP_RAY(start, mid1, (bspnode *)node->back);
        }

        goto break_out;
      }
    }
  break_out:;
  }

  return 0;
}

// Initializes some variables for the indoor bsp tree
void InitDefaultBSP() {
  if (BSP_initted) {
    DestroyBSPTree(&MineBSP);
  } else {
    atexit(DestroyDefaultBSPTree);
  }

  MineBSP.polylist = NULL;
  MineBSP.vertlist = NULL;

  BSP_initted = 1;
}
