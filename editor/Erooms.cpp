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

 * $Logfile: /DescentIII/Main/editor/Erooms.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Functions to create, delete, etc. rooms
 *
 * $Log: not supported by cvs2svn $
 *
 * 167   10/14/99 4:21p Matt
 * Added code to remove duplicate faces from a room.
 *
 * 166   9/30/99 5:02p Matt
 * Automatically normalize face UV values when a level is verified.
 *
 * 165   9/07/99 4:36p Gwar
 * disabled deletion of only the face verts of a face in DeleteRoomFace
 * (it now deletes all unused verts, like before)
 *
 * 164   8/30/99 1:50p Gwar
 * stupid me forgot a semicolon
 *
 * 163   8/30/99 1:23p Gwar
 * In DeleteRoomFace, added a way to delete only verts that were in the
 * deleted face
 *
 * 162   8/17/99 6:11p Gwar
 * handle NEWEDITOR texture management in CopyRoom
 *
 * 161   8/15/99 3:10a Gwar
 * decrement Curface in DeleteRoomFace if Curface is the last face in the
 * room
 *
 * 160   8/13/99 4:52p Gwar
 * fixed a stupid bug from my last checkin
 *
 * 159   8/13/99 4:43p Gwar
 * decrement Markedface in DeleteRoomFace if Markedface is the last face
 * in the room
 *
 * 158   7/17/99 1:36a Gwar
 * fixed a string formatting bug in a call to OutrageMessageBox
 *
 * 157   7/14/99 9:07a Gwar
 * added a parameter to AllocLoadRoom
 *
 * 156   7/06/99 10:22a Gwar
 * removed and #ifdef NEWEDITOR for this build...
 *
 * 155   7/04/99 4:55p Gwar
 * changes for texture management in NEWEDITOR
 *
 * 154   7/03/99 5:50p Gwar
 * minor changes for NEWEDITOR
 *
 * 153   7/02/99 2:17p Gwar
 * added a parameter to AllocLoadRoom to disable centering on origin
 *
 * 152   5/05/99 5:03a Gwar
 * renamed ned_GameTextures array to GameTextures in new editor to make
 * game code happy; 3D texture view still does not display textures
 *
 * 151   5/05/99 3:02a Gwar
 * added a parameter to DeleteRoomFace (by permission)
 *
 * 150   4/30/99 2:21p Jason
 * changes to verify level completeness
 *
 * 149   4/27/99 3:36p Jason
 * fixed terrain occlusion bug
 *
 * 148   4/26/99 11:11a Chris
 * Updated Bnode system
 *
 * 147   4/25/99 10:16p Matt
 * Added soundsource check to verify mine.
 *
 * 146   4/25/99 9:02p Chris
 * Improving the Bnode system
 *
 * 145   4/21/99 10:20p Matt
 * Don't compute shells for external rooms in mine verify.
 *
 * 144   4/21/99 5:15a Gwar
 * added support for paletted rooms (ORFs) into new editor
 *
 * 143   4/20/99 8:19p Matt
 * Added an assert.
 *
 * 142   4/15/99 3:10p Matt
 * Took out Int3() in FindSharedEdge(), and took out some mrpintf()s in
 * the shell calculation.
 *
 * 141   4/12/99 10:43a Jason
 * checked in so code would compile
 *
 * 140   4/10/99 5:38p Matt
 * Commented out some code that wouldn't compile.
 *
 * 139   4/08/99 5:46p Jason
 * added texture finding option
 *
 * 138   4/08/99 3:15p Matt
 * Don't compute a shell for external rooms.
 *
 * 137   4/08/99 12:45p Jason
 * don't count lights or non renderable portal faces in the level
 *
 * 136   4/07/99 2:22p Jason
 * warned designers if they have over 60 128s in their level
 *
 * 135   4/07/99 12:43p Jason
 * added texture counting to verify level
 *
 * 134   4/07/99 11:24a Jason
 * verify level now checks terrain occlusion and boa
 *
 * 133   4/06/99 5:10p Matt
 * Base room shell on all portals in the room, not just the first one.
 *
 * 132   4/05/99 11:17a Matt
 * Added code to list all the objects in the levels.
 *
 * 131   4/01/99 9:42a Matt
 * Added code to compute room shells, and made verify level do it.
 *
 * 130   3/31/99 11:34a Matt
 * Got rid of unused forcefield checkbox on room tab
 *
 * 129   3/31/99 11:33a Matt
 * Make note of non-planar faces that are portals.
 *
 * 128   3/30/99 7:57p Matt
 * Added prototype and moved a function to be inline in the header.
 *
 * 127   3/30/99 7:20p Matt
 * Deleted PointsAreColinear(), since it was never used and worked the
 * wrong way.
 *
 * 126   3/29/99 6:45p Matt
 * Changed concavity tolerance from 0.005 to 0.05.
 * Added verify code to check for concave faces and degenerate faces.
 * Added code to fix degenerate faces.
 *
 * 125   3/24/99 5:53p Jason
 * added per room ambience settings
 *
 * 124   3/23/99 1:41p Jason
 * fixed concave normal bug
 *
 * 123   3/11/99 5:12p Matt
 * Added some error messages for the new verify level checks
 *
 * 122   3/11/99 4:58p Matt
 * Fixed extra-stupid malloc bug
 *
 * 121   3/11/99 3:20p Matt
 * Added checks for T-joints and mismatched portals to verify level.
 *
 * 120   2/19/99 1:24p Matt
 * Moved ComputerCenterRoomOnFace() from editor to main
 *
 * 119   2/18/99 12:32p Jason
 * added room multiplier
 *
 * 118   2/11/99 1:44p Matt
 * Fix up triggers when deleting a face
 *
 * 117   2/03/99 1:10p Matt
 * Changed the paletted room current faces to be stored in a seperate
 * array, instead of in the room structure.
 *
 * 116   1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 115   1/25/99 7:39p Luke
 * Added comment to tell me when ROOMFILE_VERSION changes (so I can change
 * RoomView)
 *
 * 114   1/21/99 11:34a Matt
 * Got rid of portal triggers.  Since we don't have multi-face portals, a
 * face trigger works fine for a portal.  Also fixed a few editor/trigger
 * bugs.
 *
 * 113   12/22/98 2:03p Matt
 * Added room names, and made rooms not compress so that room numbers are
 * suitable for persistant uses.
 *
 * 112   12/09/98 3:12p Jason
 * save/load light multiples with faces
 *
 * 111   12/07/98 12:00p Sean
 * Adjusted co-planar epsilon
 *
 * 110   11/17/98 5:58p Sean
 * Changed concavity tolerance from 0.0001 to 0.0005 (MattT on Sean's
 * machine)
 *
 * 109   11/03/98 6:20p Matt
 * Changed the concavity check to not be dependent on the length of the
 * edges being checked.
 *
 * 108   11/02/98 6:15p Chris
 * Room AABBs get saved with the level and the sort_face and dec_sort_face
 * list s have been removed
 *
 * 107   11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 106   10/08/98 8:16p Matt
 * Made AssignDefaultUVsToRoom() call AssignDefaultUVsToRoomFace()
 *
 * 105   10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 104   10/07/98 12:48p Matt
 * Added some extra error checking to prevent doubly-formed portals.
 *
 * 103   10/03/98 8:05p Matt
 * Changed the way CheckIfFaceIsPlanar() works (& renamed it to
 * FaceIsPlanar()) and added planar check to VerifyMine() & VerifyRoom()
 *
 * 102   9/29/98 4:00p Matt
 * Fix selected room list when compressing the mine.
 *
 * 101   9/28/98 10:55a Jason
 * fixed some bugs that VC6 caught
 *
 * 100   9/24/98 5:00p Matt
 * Improved error checking for running out of rooms.
 *
 * 99    9/14/98 12:18p Matt
 * Took out mprintf() that was slowing down room importing.
 *
 * 98    9/10/98 6:37p Matt
 * Increased concavity check tolerance (from 0.002 to 0.003) to fix
 * problem forming smooth bridge on Dan's level 9.
 *
 * 97    9/09/98 9:10p Matt
 * In verify & fix functions, don't process non-used rooms.
 *
 * 96    9/08/98 6:12p Matt
 * Added code to check for and fix duplicate and unused points.
 *
 * 95    9/08/98 12:54p Matt
 * Changed CONCAVITY_TOLERANCE from 0.0000000001 to 0.002 to fix a problem
 * Sean was having joining faces.
 *
 * 94    9/08/98 12:53p Matt
 * Added duplicate point check to level verify
 *
 * 93    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 92    9/03/98 1:23p Matt
 * Made AddVertToFace() compute alpha, u2, & v2 values for the new point.
 *
 * 91    9/02/98 5:56p Matt
 * Changed comment
 *
 * 90    9/02/98 4:20p Matt
 * Cleaned up some linking code now that we don't have multi-face portals.
 *
 * 89    9/02/98 2:28p Matt
 * New function to add a vertex to a face.
 *
 * 88    9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 87    8/31/98 4:37p Matt
 * Added improved room & mine error checking.
 *
 * 86    8/14/98 4:46p Matt
 * Fix doorways when compressing the mine
 *
 * 85    8/11/98 12:46p Matt
 * Temporary fix for forming portals between faces with different numbers
 * of vertices.
 *
 * 84    7/21/98 4:25p Chris
 * Fixed a bug with the new AABB stuff
 *
 * 83    7/21/98 2:14p Chris
 * Some FVI speedups - not done
 *
 * 82    7/17/98 9:56a Chris
 * Intermediate checkin
 *
 * 81    7/16/98 8:29p Chris
 * Partial implementation of the new collide code
 *
 * 80    6/26/98 12:30p Matt
 * In PointsAreSame(), check for the middle point being the same as either
 * of the end points.
 *
 * 79    6/25/98 7:15p Matt
 * Added code to check for errors in portal linkage
 *
 * 78    6/19/98 12:22p Jason
 * fixed special faces bug
 *
 * 77    6/08/98 12:27p Matt
 * Added function to copy from one face to another the flags that should
 * be inherited.
 *
 * 76    6/02/98 6:03p Jason
 * added specular lightmaps
 *
 * 75    5/25/98 3:46p Jason
 * added better light glows
 *
 * 74    5/22/98 3:28p Jason
 * added specular lighting
 *
 * 73    5/04/98 12:27p Matt
 * Fixed misspelling
 *
 * 72    4/27/98 6:41p Matt
 * Cleaned up epsilons some more, and moved some code here from hroom.cpp.
 *
 * 71    4/21/98 4:05p Jason
 * made copyface take into accound light multiples
 *
 * 70    4/21/98 2:44p Matt
 * Added code to check a level, but haven't finished or made it available
 * yet.
 *
 * 69    4/16/98 3:33p Matt
 * Cleaned up epsilon values, again.
 *
 * 68    4/16/98 12:59p Matt
 * Changed point-to-edge epsilon, and took out Int3s's
 *
 * 67    4/16/98 10:41a Matt
 * Added FindSharedEdgeAcrossRooms()
 *
 * 66    4/15/98 4:57p Matt
 * Fixed massive stupidity in the way I computed if a point was outside an
 * edge for polygon:polygon clipping.
 *
 * 65    4/02/98 12:23p Jason
 * trimmed some fat from our structures
 *
 * 64    3/31/98 3:49p Jason
 * added memory lib
 *
 * 63    3/18/98 4:31p Chris
 * Speed up fvi and fixed some bugs
 *
 * 62    3/16/98 5:50p Chris
 * Added sorted face lists for fvi
 *
 * 61    2/24/98 1:54p Jason
 * added much stricter concavity testing
 *
 * 60    2/23/98 4:25p Jason
 * got rid of stupid compiler warning
 *
 * 59    2/22/98 3:02p Jason
 * changed concavity tolerance in CheckIfFaceIsPlanar
 *
 * 58    2/19/98 2:20p Jason
 * fixed lightmap combining to eliminate tjoint problems
 *
 * 57    2/16/98 1:07p Matt
 * Changed assert to int3
 *
 * 56    2/12/98 9:10p Matt
 * Adjusted epsilon when clipping rooms.
 *
 * 55    2/11/98 4:03p Matt
 * When loading a room, center it at the origin
 *
 * 54    2/11/98 12:38p Matt
 * Fixed small bug in DeleteRoomVert()
 *
 * 53    2/10/98 3:50p Jason
 * added pulsing walls
 *
 * 52    2/08/98 6:03p Matt
 * When copying a face, don't copy the has_trigger flag
 *
 * 51    1/20/98 4:05p Matt
 * Move BuildListOfPortalVerts() from roomkeypaddialog.cpp to erooms.cpp
 *
 * 50    1/16/98 11:53a Matt
 * Relaxed low-precision normal check, and added mprintfs with info on
 * problem normals
 *
 * 49    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 48    1/12/98 5:05p Luke
 * Code was using wrong constant when searching palette rooms (MattT on
 * Luke's machine)
 *
 * 47    12/30/97 3:33p Jason
 * fixed stupid variable bug
 *
 * 46    11/24/97 1:30a Jason
 * first attempt at adding shadows
 *
 * 45    11/17/97 7:37p Sean
 * Increased point edge epsilon (Matt on Sean's machine)
 *
 * 44    11/11/97 6:45p Matt
 * Adjusted epsilon value for edge clip
 *
 * 43    11/04/97 7:30p Matt
 * Dealt with yet more precision problems in room clip
 *
 * 42    10/30/97 6:31p Jason
 * fixed potential lightmap bugs
 *
 * 41    10/29/97 12:36p Matt
 * Dealt with some precision problems in clipper
 *
 * 40    10/13/97 5:08p Matt
 * Moved ComputeRoomBoundingSphere() & CreateRoomObjects() from editor to
 * main
 *
 *
 * 39    10/01/97 7:51p Matt
 * Added code for external rooms
 *
 * 38    9/24/97 3:20p Matt
 * Added ComputeRoomMinMax()
 *
 * 37    9/19/97 2:52p Jason
 * changes to fix lightmap seam problem
 *
 * 36    9/17/97 11:52a Samir
 * BIG SEGMENT RIPOUT
 *
 * 35    9/16/97 4:27p Matt
 * Got rid of static_light & changed fields in the room struct
 *
 * 34    9/15/97 2:21p Matt
 * Remap triggers when compress mine.  (Also deleted some segment engine
 * code.)
 *
 * 33    9/15/97 11:03a Jason
 * fixed bug with alpha
 *
 * 32    9/12/97 2:27p Matt
 * Added code to delete any unused vertices when deleting a face
 *
 * 31    9/10/97 3:02p Matt
 * Moved GetIJ() from erooms.cpp to room.cpp
 *
 * 30    9/09/97 10:25a Matt
 * Clip alpha values when clipping edge
 *
 * 29    9/03/97 2:00p Jason
 * made LIGHTMAP_SPACING #define for controlling spacing of lightmap
 * elements
 *
 * 28    9/02/97 5:17p Jason
 * changes for dynamic lighting
 *
 * 27    9/02/97 2:28p Matt
 * Changed PointOutsideEdge() to the more generally-useful
 * CheckPointAgainstEdge()
 * Made CopyFace() clear the portal number
 *
 * 26    9/02/97 11:47a Jason
 * Got alpha per vertex working
 *
 * 25    9/02/97 11:01a Matt
 * Moved assert()
 *
 * 24    8/29/97 5:44p Matt
 * Moved a couple functions from hroom.cpp, and added a couple more useful
 * functions.
 *
 * 23    8/28/97 12:31p Jason
 * added hi-res lightmaps for radiosity
 *
 * 22    8/22/97 1:02p Matt
 * Got CompressMine() working for rooms
 *
 * 21    8/21/97 5:56p Matt
 * Added a bunch of useful functions, and make CheckFaceConcavity() more
 * generally useful.
 *
 * 20    8/18/97 11:47a Sean
 * FROM JASON: Recompute normals on LoadRoom
 *
 * 19    8/04/97 6:46p Jason
 * added code for a lightmap system
 *
 * 18    8/01/97 6:11p Matt
 * Added several functions that I needed for attach room code
 *
 * 17    8/01/97 4:41p Jason
 * made FixConcaveFaces reset all room normals as an extra precaution
 *
 * 16    8/01/97 12:50p Jason
 * added code to support scaling of rooms/faces/edges
 *
 * 15    7/31/97 3:31p Jason
 * added functions to rotate portal rooms
 *
 * 14    7/29/97 1:54p Matt
 * Added some generally useful room/face functions
 *
 * 13    7/21/97 12:14p Matt
 * Fixed stupid bug in concavity check
 *
 * 12    7/18/97 5:36p Jason
 * save changed paletted rooms on exit
 *
 * 11    7/18/97 4:37p Matt
 * Added function CheckFaceConcavity()
 *
 *
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstdio>

#include <string.h>

#ifndef NEWEDITOR
#include "d3edit.h"
#else
#include "..\neweditor\stdafx.h"
#include "..\neweditor\neweditor.h"
#include "..\neweditor\globals.h"
#include "..\neweditor\ned_geometry.h"
#endif

#include "erooms.h"
#include "room.h"
#include "gametexture.h"
#include "terrain.h"
#include "special_face.h"
#include "lighting.h"
#include "trigger.h"
#include "mem.h"
#include "doorway.h"

#ifndef NEWEDITOR
#include "editor_lighting.h"
#endif

#include "boa.h"
#include "bnode.h"

// List of current faces for the palette rooms
int Current_faces[MAX_PALETTE_ROOMS];

// Returns a free room number, & marks it no longer free.  Returns -1 if none free.
// If palette_room is true, allocate out of the part of the array for the room palette
int GetFreeRoom(bool palette_room) {
  int roomnum;
  int start, end;

  int old_hri = Highest_room_index;

  if (palette_room) {
    start = FIRST_PALETTE_ROOM;
    end = start + MAX_PALETTE_ROOMS;
  } else {
    start = 0;
    end = MAX_ROOMS;
  }

  for (roomnum = start; roomnum < end; roomnum++)
    if (!Rooms[roomnum].used)
      break;

  if (roomnum == end) // couldn't find a free room
    return -1;

  if (!palette_room) {
    if (roomnum > Highest_room_index)
      Highest_room_index = roomnum;
  } else
    Current_faces[roomnum - FIRST_PALETTE_ROOM] = 0;

  BNode_RemapTerrainRooms(old_hri, Highest_room_index);

  return roomnum;
}

// Allocates a room & initializes it.
// Memory is allocated for faces & verts arrays, but the elements are *not* initialized
// The number of portals is set to zero.
// If palette_room is true, allocate out of the part of the array for the room palette
// Returns:  pointer to new room, or NULL if no free rooms
room *CreateNewRoom(int nverts, int nfaces, bool palette_room) {
  int roomnum;
  room *rp;

  // Get a free room
  roomnum = GetFreeRoom(palette_room);

  if (roomnum == -1)
    return NULL;

  rp = &Rooms[roomnum];

  // Initalize room, allocating memory
  InitRoom(rp, nverts, nfaces, 0);

  return rp;
}

// Find the uv associated with a face vertex
// This routine works by projecting the face on to its own normals plane
// and just treating the face like a 2d surface

// Important - vertnum is the index into the face_verts[] array in the face structure,
// not an index into the verts[] array of the room structure
void GetUVLForRoomPoint(int roomnum, int facenum, int vertnum, roomUVL *uvl) {
  matrix face_matrix, trans_matrix;
  vector fvec;
  vector avg_vert;
  vector verts[MAX_VERTS_PER_FACE];
  vector rot_vert;

  ASSERT(Rooms[roomnum].used);
  ASSERT(Rooms[roomnum].faces[facenum].num_verts >= 3);

  // find the center point of this face
  vm_MakeZero(&avg_vert);
  for (int i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++)
    avg_vert += Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

  avg_vert /= i;

  // Make the orientation matrix
  // Reverse the normal because we're looking "at" the face, not from it
  fvec = -Rooms[roomnum].faces[facenum].normal;

  vm_VectorToMatrix(&face_matrix, &fvec, NULL, NULL);
  // Make the transformation matrix

  angvec avec;
  vm_ExtractAnglesFromMatrix(&avec, &face_matrix);
  vm_AnglesToMatrix(&trans_matrix, avec.p, avec.h, avec.b);

  // Rotate all the points
  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    vector vert = Rooms[roomnum].verts[Rooms[roomnum].faces[facenum].face_verts[i]];

    vert -= avg_vert;
    vm_MatrixMulVector(&rot_vert, &vert, &trans_matrix);

    verts[i] = rot_vert;
  }

  // Find left most point
  int leftmost_point = -1;
  float leftmost_x = 900000.00f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].x < leftmost_x) {
      leftmost_point = i;
      leftmost_x = verts[i].x;
    }
  }

  ASSERT(leftmost_point != -1);

  // Find top most point
  int topmost_point = -1;
  float topmost_y = -900000.0f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].y > topmost_y) {
      topmost_point = i;
      topmost_y = verts[i].y;
    }
  }

  ASSERT(topmost_point != -1);

  // Find right most point
  int rightmost_point = -1;
  float rightmost_x = -900000.00f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].x > rightmost_x) {
      rightmost_point = i;
      rightmost_x = verts[i].x;
    }
  }

  ASSERT(rightmost_point != -1);

  // Find bottom most point
  int bottommost_point = -1;
  float bottommost_y = 900000.0f; // a big number

  for (i = 0; i < Rooms[roomnum].faces[facenum].num_verts; i++) {
    if (verts[i].y < bottommost_y) {
      bottommost_point = i;
      bottommost_y = verts[i].y;
    }
  }

  ASSERT(bottommost_point != -1);

  // now set the base vertex, which is where we base uv 0,0 on

  vector base_vector;

  base_vector.x = verts[leftmost_point].x;
  base_vector.y = verts[topmost_point].y;
  base_vector.z = 0;

  // now actually find the uv of our specified point

  uvl->u = (verts[vertnum].x - base_vector.x) / 20.0;
  uvl->v = (base_vector.y - verts[vertnum].y) / 20.0;
}

#define DEFAULT_ALPHA 255

// Goes through each face of the passed room and sets the default uvs
void AssignDefaultUVsToRoom(room *rp) {
  ASSERT(rp->used >= 1);

  for (int i = 0; i < rp->num_faces; i++)
    AssignDefaultUVsToRoomFace(rp, i);
}

// Sets the default UVS for a room face
void AssignDefaultUVsToRoomFace(room *rp, int facenum) {
  ASSERT(rp->used >= 1);
  ASSERT(facenum < rp->num_faces);

  int t;

  for (t = 0; t < rp->faces[facenum].num_verts; t++) {
    GetUVLForRoomPoint(ROOMNUM(rp), facenum, t, &rp->faces[facenum].face_uvls[t]);
    rp->faces[facenum].face_uvls[t].alpha = DEFAULT_ALPHA;
  }
}

// Searches thru all rooms for a specific name, returns -1 if not found
// or index of room with name
int FindRoomName(char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = FIRST_PALETTE_ROOM; i < FIRST_PALETTE_ROOM + MAX_PALETTE_ROOMS; i++)
    if (Rooms[i].used && Rooms[i].name && !stricmp(name, Rooms[i].name))
      return i;

  return -1;
}

#define ROOM_HEADER_CHUNK 0
#define ROOM_VERTEX_CHUNK 1
#define ROOM_FACES_CHUNK 2
#define ROOM_END_CHUNK 3
#define ROOM_TEXTURE_CHUNK 4
#define ROOM_NEW_HEADER_CHUNK 5

#define ROOMFILE_VERSION 4 // Please tell Luke if you change this (and why) -- THANKS!!

// saves a room in our ORF (Outrage room file) format
void SaveRoom(int n, char *filename) {
  CFILE *outfile;
  int headsize, savepos, vertsize, facesize, texsize;
  int highest_index = 0;
  int16_t Room_to_texture[MAX_TEXTURES];
  int t, found_it = 0;

  // Make sure its in use!
  ASSERT(Rooms[n].used);

  outfile = (CFILE *)cfopen(filename, "wb");
  if (!outfile) {
    mprintf(0, "Couldn't save room %s!\n", filename);
    Int3();
    return;
  }

  // write out header info
  cf_WriteInt(outfile, ROOM_NEW_HEADER_CHUNK);
  headsize = cftell(outfile);
  cf_WriteInt(outfile, -1);

  cf_WriteInt(outfile, ROOMFILE_VERSION);
  cf_WriteInt(outfile, Rooms[n].num_verts);
  cf_WriteInt(outfile, Rooms[n].num_faces);

  savepos = cftell(outfile);
  cfseek(outfile, headsize, SEEK_SET);
  cf_WriteInt(outfile, (savepos - headsize) - 4);
  cfseek(outfile, savepos, SEEK_SET);

  // write out vertex info
  cf_WriteInt(outfile, ROOM_VERTEX_CHUNK);
  vertsize = cftell(outfile);
  cf_WriteInt(outfile, -1);

  for (int i = 0; i < Rooms[n].num_verts; i++) {
    cf_WriteFloat(outfile, Rooms[n].verts[i].x);
    cf_WriteFloat(outfile, Rooms[n].verts[i].y);
    cf_WriteFloat(outfile, Rooms[n].verts[i].z);
  }

  savepos = cftell(outfile);
  cfseek(outfile, vertsize, SEEK_SET);
  cf_WriteInt(outfile, (savepos - vertsize) - 4);
  cfseek(outfile, savepos, SEEK_SET);

  // figure out correct texture ordering
  for (i = 0; i < Rooms[n].num_faces; i++) {
    int16_t index = Rooms[n].faces[i].tmap;

    for (found_it = 0, t = 0; t < highest_index; t++) {
      if (Room_to_texture[t] == index) {
        // This texture is already there
        found_it = 1;
        break;
      }
    }
    if (found_it == 0) {
      // Add this index to our list of textures
      Room_to_texture[highest_index] = index;
      highest_index++;
      ASSERT(highest_index < MAX_TEXTURES);
    }
  }

  // write out texture info
  cf_WriteInt(outfile, ROOM_TEXTURE_CHUNK);
  texsize = cftell(outfile);
  cf_WriteInt(outfile, -1);

  // Write out how many different textures there are and then write their names
  cf_WriteInt(outfile, highest_index);

  for (i = 0; i < highest_index; i++) {
    int index = Room_to_texture[i];
    cf_WriteString(outfile, GameTextures[index].used ? GameTextures[index].name : "");
  }

  savepos = cftell(outfile);
  cfseek(outfile, texsize, SEEK_SET);
  cf_WriteInt(outfile, (savepos - texsize) - 4);
  cfseek(outfile, savepos, SEEK_SET);

  // write out face info
  cf_WriteInt(outfile, ROOM_FACES_CHUNK);
  facesize = cftell(outfile);
  cf_WriteInt(outfile, -1);

  for (i = 0; i < Rooms[n].num_faces; i++) {
    cf_WriteByte(outfile, Rooms[n].faces[i].light_multiple);
    cf_WriteInt(outfile, Rooms[n].faces[i].num_verts);

    cf_WriteFloat(outfile, Rooms[n].faces[i].normal.x);
    cf_WriteFloat(outfile, Rooms[n].faces[i].normal.y);
    cf_WriteFloat(outfile, Rooms[n].faces[i].normal.z);

    // Search through our texture list and write out that index
    for (t = 0; t < highest_index; t++) {
      if (Rooms[n].faces[i].tmap == Room_to_texture[t]) {
        cf_WriteShort(outfile, t);
        t = highest_index; // stupid way to break out
      }
    }

    for (t = 0; t < Rooms[n].faces[i].num_verts; t++) {
      cf_WriteShort(outfile, Rooms[n].faces[i].face_verts[t]);
      cf_WriteFloat(outfile, Rooms[n].faces[i].face_uvls[t].u);
      cf_WriteFloat(outfile, Rooms[n].faces[i].face_uvls[t].v);
      cf_WriteFloat(outfile, 0);
      cf_WriteFloat(outfile, 0);
      cf_WriteFloat(outfile, 0);
      cf_WriteFloat(outfile, 0);
      cf_WriteFloat(outfile, Ubyte_to_float[Rooms[n].faces[i].face_uvls[t].alpha]);
    }
  }

  savepos = cftell(outfile);
  cfseek(outfile, facesize, SEEK_SET);
  cf_WriteInt(outfile, (savepos - facesize) - 4);
  cfseek(outfile, savepos, SEEK_SET);

  cf_WriteInt(outfile, ROOM_END_CHUNK);
  cf_WriteInt(outfile, 4);

  cfclose(outfile);

  mprintf(0, "Room file %s saved.\n", filename);
}

// Allocates a room and then tries to load it
// Returns index into Rooms[] array on success
// -1 on fail
int AllocLoadRoom(char *filename, bool bCenter, bool palette_room) {
  CFILE *infile;
  int done = 0, initted = 0;
  int command, len, room_num = -1, i;
  room *rp;
  char texture_names[MAX_TEXTURES][PAGENAME_LEN];
  int highest_index;
  int16_t tex_index;
  int room_version = 0;

  infile = (CFILE *)cfopen(filename, "rb");
  if (!infile) {
    Int3(); // hey, couldn't load this room!
    return -1;
  }

  while (!done) {
    command = cf_ReadInt(infile);
    len = cf_ReadInt(infile);

    switch (command) {
    // Read room header stuff
    case ROOM_HEADER_CHUNK:
    case ROOM_NEW_HEADER_CHUNK:
      int num_verts, num_faces;

      if (command == ROOM_NEW_HEADER_CHUNK)
        room_version = cf_ReadInt(infile);
      num_verts = cf_ReadInt(infile);
      num_faces = cf_ReadInt(infile);

      // room_num=AllocRoom (num_verts,num_faces);
      rp = CreateNewRoom(num_verts, num_faces, palette_room);

      if (rp == NULL) {
        done = 1;
        continue;
      }

      initted = 1;
      break;

    case ROOM_VERTEX_CHUNK:
      if (!initted) {
        Int3(); // bad format info, get jason
        done = 1;
        break;
      }
      for (i = 0; i < rp->num_verts; i++) {
        rp->verts[i].x = cf_ReadFloat(infile);
        rp->verts[i].y = cf_ReadFloat(infile);
        rp->verts[i].z = cf_ReadFloat(infile);
      }
      break;
    case ROOM_TEXTURE_CHUNK:
      if (!initted) {
        Int3(); // bad format info, get jason
        done = 1;
        break;
      }
      highest_index = cf_ReadInt(infile);
      for (i = 0; i < highest_index; i++)
        cf_ReadString(texture_names[i], PAGENAME_LEN, infile); // get old name

      break;

    case ROOM_FACES_CHUNK:
      if (!initted) {
        Int3(); // bad format info, get jason
        done = 1;
        break;
      }

      for (i = 0; i < rp->num_faces; i++) {
        uint8_t light_multiple = 4;
        if (room_version >= 4)
          light_multiple = cf_ReadByte(infile);

        int nverts = cf_ReadInt(infile);

        // rp->faces[i].num_verts=cf_ReadInt (infile);
        // rp->faces[i].face_verts=(int16_t *)mem_malloc (sizeof(int16_t)*rp->faces[i].num_verts);
        // rp->faces[i].face_uvls=(g3UVL *)mem_malloc (sizeof(g3UVL)*rp->faces[i].num_verts);

        InitRoomFace(&rp->faces[i], nverts);

        ASSERT(rp->faces[i].face_verts);
        ASSERT(rp->faces[i].face_uvls);

        rp->faces[i].normal.x = cf_ReadFloat(infile);
        rp->faces[i].normal.y = cf_ReadFloat(infile);
        rp->faces[i].normal.z = cf_ReadFloat(infile);
        rp->faces[i].light_multiple = light_multiple;

        tex_index = cf_ReadShort(infile);
        tex_index = FindTextureName(texture_names[tex_index]);

        if (tex_index == -1) // If this texture doesn't exist, bash to error texture
          rp->faces[i].tmap = 0;
        else
          rp->faces[i].tmap = tex_index;

        for (int t = 0; t < rp->faces[i].num_verts; t++) {
          rp->faces[i].face_verts[t] = cf_ReadShort(infile);
          rp->faces[i].face_uvls[t].u = cf_ReadFloat(infile);
          rp->faces[i].face_uvls[t].v = cf_ReadFloat(infile);
          cf_ReadFloat(infile);
          cf_ReadFloat(infile);
          cf_ReadFloat(infile);
          cf_ReadFloat(infile);
          if (room_version >= 1)
            rp->faces[i].face_uvls[t].alpha = Float_to_ubyte(cf_ReadFloat(infile));

          if (room_version <= 1)
            rp->faces[i].face_uvls[t].alpha = 255;
        }
      }
      break;
    case ROOM_END_CHUNK:
      done = 1;
      break;
    default:
      // skip the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }

  cfclose(infile);

  if (!ResetRoomFaceNormals(rp))
    OutrageMessageBox("Warning:  This room has faces with bad normals.\n\n"
                      "It is recommended that you fix this room before using it.");

  // Center the room
  if (bCenter) {
    vector center;
#ifndef NEWEDITOR
    ComputeRoomCenter(&center, rp);
#else
    ComputeRoomBoundingSphere(&center, rp);
#endif
    for (int v = 0; v < rp->num_verts; v++)
      rp->verts[v] -= center;
  }

  // We're done
  return ROOMNUM(rp);
}

// Gets next palette room (from n) that has actually been alloced
int GetNextRoom(int n) {
  int i;

  ASSERT((n == -1) || ((n >= FIRST_PALETTE_ROOM) && n < FIRST_PALETTE_ROOM + MAX_PALETTE_ROOMS));

  if (n == -1) // start at beginning
    n = FIRST_PALETTE_ROOM - 1;

  for (i = n + 1; i < FIRST_PALETTE_ROOM + MAX_PALETTE_ROOMS; i++)
    if (Rooms[i].used)
      return i;

  for (i = FIRST_PALETTE_ROOM; i <= n; i++)
    if (Rooms[i].used)
      return i;

  // no room found

  return -1;
}

void GetIJ(const vector *normal, int *ii, int *jj);

// How much slack to give to give the concavity test
#define CONCAVITY_TOLERANCE 0.05

// Deterimines whether a face is concave or convex
// Parameters:	num_verts - the number of vertices in the face to be tested
//					face_verts - list of vertex numbers in this face
//					normal - the surface normal of this face
//					verts - array of vertices into which face_verts elements index
// Returns:		If the face is concave, returns the number of the vertex that makes the concavity.
//					If the face is convex, returns -1
// NOTE: A face could have multiple concavities, and this will only find the one with the
// lowest-numbered vertex
int CheckFaceConcavity(int num_verts, int16_t *face_verts, vector *normal, vector *verts) {
  int ii, jj;
  float i0, j0, i1, j1;
  float *v0, *v1;
  int vn;

  // Get the vertices for projection
  GetIJ(normal, &ii, &jj);

  // Get vector from last vertex to first vertex
  v0 = (float *)&verts[face_verts[num_verts - 1]];
  v1 = (float *)&verts[face_verts[0]];
  i1 = v1[ii] - v0[ii];
  j1 = v1[jj] - v0[jj];

  // Go through each vert and check for concavity
  for (vn = 0; vn < num_verts; vn++) {
    float dot;

    // Copy previous vertex & edge values
    v0 = v1;
    i0 = i1;
    j0 = j1;

    // Compute new values
    v1 = (float *)&verts[face_verts[(vn + 1) % num_verts]];
    i1 = v1[ii] - v0[ii];
    j1 = v1[jj] - v0[jj];

    // Now we have two vectors, <i0,j0> and <i1,j1>.  Let's see if we have a concavity
    dot = (-j0 * i1) + (i0 * j1);
    dot /= sqrt(i0 * i0 + j0 * j0) * sqrt(i1 * i1 + j1 * j1);

    if (dot > CONCAVITY_TOLERANCE) { // we have a concavity!
      // mprintf(0,"Concavity check dot = %f\n",dot);
      return vn; //..so return this vertex number
    }
  }

  // No concavity found
  return -1;
}

// Recompute the surface normals for all the faces in a room
// Parameters:	rp - pointer to the room
// Returns:		true if normals computed ok, false if some normals were bad
bool ResetRoomFaceNormals(room *rp) {
  int bad_normals = 0;

  for (int i = 0; i < rp->num_faces; i++)
    if (!ComputeFaceNormal(rp, i))
      bad_normals++;

  if (bad_normals > 0) {
    mprintf(1, "Warning: Room %d has %d bad or low-precision normals\n", ROOMNUM(rp), bad_normals);
    return 0;
  } else
    return 1;
}

// Copies the contents of one face to another.  Sets the portal num in the new face to -1.
// Parameters:	dfp - pointer to the destination face.  This face should be uninitialized.
//					sfp - pointer to the source face
void CopyFace(face *dfp, face *sfp) {
  InitRoomFace(dfp, sfp->num_verts);

  dfp->flags = sfp->flags;
  dfp->portal_num = -1;
  dfp->normal = sfp->normal;
  dfp->tmap = sfp->tmap;
  dfp->light_multiple = sfp->light_multiple;

  // Clear the flags that we don't want transferred over
  dfp->flags &= ~FF_LIGHTMAP;
  dfp->flags &= ~FF_HAS_TRIGGER;

  // Copy vertices and uvls
  for (int i = 0; i < sfp->num_verts; i++) {
    dfp->face_verts[i] = sfp->face_verts[i];
    dfp->face_uvls[i] = sfp->face_uvls[i];
  }
}

// Checks to see if a face is planar.
// See if all the points are within a certain distance of an average point
// Returns 1 if face is planar, 0 if not
bool FaceIsPlanar(int nv, int16_t *face_verts, vector *normal, vector *verts) {
  // Triangles are always planar
  if (nv == 3)
    return 1;

  // Get average distance from origin for points on this face
  float average_d = 0;
  for (int v = 0; v < nv; v++)
    average_d += verts[face_verts[v]] * *normal;
  average_d /= nv;

  // Look for points too far from the average
  float d;
  for (v = 0; v < nv; v++) {
    d = verts[face_verts[v]] * *normal;
    if (fabs(d - average_d) > POINT_TO_PLANE_EPSILON)
      return 0;
  }

  // Didn't find anything wrong, so face is planar
  return 1;
}

// Fixes all the concave/nonplanar faces of facelist of room rp
void FixConcaveFaces(room *rp, int *facelist, int facecount) {
  int i, t, k;
  face *newfaces;

  for (i = 0; i < facecount; i++) {
    // If this face is concave, build a triangle strip out of the concave face
    if (!FaceIsPlanar(rp, facelist[i])) {
      int concave_verts[MAX_VERTS_PER_FACE];

      int old_num_faces = rp->num_faces;
      int concave_count = rp->faces[facelist[i]].num_verts;
      int old_tmap = rp->faces[facelist[i]].tmap;
      int num_new_faces = concave_count - 3;
      ASSERT(num_new_faces > 0);

      mprintf(0, "Creating %d new faces from face %d!\n", num_new_faces, facelist[i]);

      // copy the concave vert indices for later use
      for (t = 0; t < concave_count; t++)
        concave_verts[t] = rp->faces[facelist[i]].face_verts[t];

      // Allocate memory for our new faces
      int nfaces = rp->num_faces + num_new_faces;

      newfaces = (face *)mem_malloc(nfaces * sizeof(face));
      ASSERT(newfaces != NULL);

      // Copy all the faces into our new array
      for (t = 0; t < rp->num_faces; t++) {

        if (t != facelist[i]) {
          int nverts = rp->faces[t].num_verts;

          newfaces[t].face_verts = (int16_t *)mem_malloc(nverts * sizeof(int16_t));
          ASSERT(newfaces[t].face_verts != NULL);
          newfaces[t].face_uvls = (roomUVL *)mem_malloc(nverts * sizeof(roomUVL));
          ASSERT(newfaces[t].face_uvls != NULL);

          newfaces[t].normal = rp->faces[t].normal;
          newfaces[t].tmap = rp->faces[t].tmap;
          newfaces[t].flags = rp->faces[t].flags;
          newfaces[t].portal_num = rp->faces[t].portal_num;
          newfaces[t].num_verts = rp->faces[t].num_verts;
          newfaces[t].special_handle = BAD_SPECIAL_FACE_INDEX;

          for (k = 0; k < nverts; k++) {
            newfaces[t].face_verts[k] = rp->faces[t].face_verts[k];
            newfaces[t].face_uvls[k] = rp->faces[t].face_uvls[k];
          }
        } else // special case the concave face into a triangle
        {
          int nverts = 3;

          newfaces[t].face_verts = (int16_t *)mem_malloc(nverts * sizeof(int16_t));
          ASSERT(newfaces[t].face_verts != NULL);
          newfaces[t].face_uvls = (roomUVL *)mem_malloc(nverts * sizeof(roomUVL));
          ASSERT(newfaces[t].face_uvls != NULL);

          newfaces[t].tmap = rp->faces[t].tmap;
          newfaces[t].flags = rp->faces[t].flags;
          newfaces[t].portal_num = rp->faces[t].portal_num;
          newfaces[t].num_verts = 3;
          newfaces[t].special_handle = BAD_SPECIAL_FACE_INDEX;

          for (k = 0; k < nverts; k++) {
            newfaces[t].face_verts[k] = rp->faces[t].face_verts[k];
            newfaces[t].face_uvls[k] = rp->faces[t].face_uvls[k];
          }

          // Get new normal
          if (!ComputeFaceNormal(rp, t))
            Int3(); // Bad normal: get Matt or Jason, or ignore.

          newfaces[t].normal = rp->faces[t].normal;
        }
      }

      // Free up the old list of faces
      mem_free(rp->faces);
      rp->faces = newfaces;
      rp->num_faces = nfaces;

      if (rp->num_bbf_regions) {
        for (i = 0; i < rp->num_bbf_regions; i++) {
          mem_free(rp->bbf_list[i]);
        }
        mem_free(rp->bbf_list);
        mem_free(rp->num_bbf);
        mem_free(rp->bbf_list_min_xyz);
        mem_free(rp->bbf_list_max_xyz);
        mem_free(rp->bbf_list_sector);
        rp->num_bbf_regions = 0;
      }

      // Now build the remaining triangles of our concave face
      for (t = 0; t < num_new_faces; t++)
        InitRoomFace(&rp->faces[old_num_faces + t], 3);

      for (t = 0; t < concave_count - 3; t++) {
        rp->faces[old_num_faces + t].face_verts[0] = concave_verts[0];
        rp->faces[old_num_faces + t].face_verts[1] = concave_verts[2 + t];
        rp->faces[old_num_faces + t].face_verts[2] = concave_verts[3 + t];
        rp->faces[old_num_faces + t].tmap = old_tmap;

        if (!ComputeFaceNormal(rp, old_num_faces + t))
          Int3(); // Bad normal: get Matt or Jason, or ignore.

        AssignDefaultUVsToRoomFace(rp, old_num_faces + t);
      }
    }
  }

  if (!ResetRoomFaceNormals(rp))
    Int3(); // Get Matt or Jason
}

// Changes the number of verts in a face.  Frees and reallocates the face_verts & face_uvls arrays.
// Leaves all other fields the same
void ReInitRoomFace(face *fp, int nverts) {
  ASSERT(nverts != 0);

  fp->num_verts = nverts;

  mem_free(fp->face_verts);
  mem_free(fp->face_uvls);

  fp->face_verts = (int16_t *)mem_malloc(nverts * sizeof(*fp->face_verts));
  ASSERT(fp->face_verts != NULL);
  fp->face_uvls = (roomUVL *)mem_malloc(nverts * sizeof(*fp->face_uvls));
  ASSERT(fp->face_uvls != NULL);
}

// Determines if two points are close enough together to be considered the same
// Parameters:	v0,v1 - the two points
// Returns:		true if the points are the same or very close; else false
bool PointsAreSame(vector *v0, vector *v1) {
  float d = vm_VectorDistance(v0, v1);

  return (d < POINT_TO_POINT_EPSILON);
}

// Check to see if a point is in, in front of, or behind a plane
// Parameters:	checkpoint - the point to check
//					planepoint,normal - the plane we're checking against
// Returns:		0 if on the plane, -1 if behind, 1 if in front
int CheckPointToPlane(vector *checkpoint, vector *planepoint, vector *normal) {
  float d = (*checkpoint - *planepoint) * *normal;

  if (d < -POINT_TO_PLANE_EPSILON)
    return -1;
  else if (d > POINT_TO_PLANE_EPSILON)
    return 1;
  else
    return 0;
}

// Check to see if all the points on a face are in front of a plane
// Parameters:	rp,facenum - the face to check
//					planepoint,normal - define the plane we're checking against
// Returns:		the number of the first point found on the back of the plane, or -1 of all on front
int CheckFaceToPlane(room *rp, int facenum, vector *planepoint, vector *normal) {
  face *fp = &rp->faces[facenum];

  for (int i = 0; i < fp->num_verts; i++)
    if (CheckPointToPlane(&rp->verts[fp->face_verts[i]], planepoint, normal) < 0)
      return i;

  return -1; // no points found behind the plane
}

// Create space for additional vertices in a room.
// Allocates a new array of vertices, copies from the old list, and frees the old list
// The new vertices are at the end of the list, so none of the old vertices change number
// Parameters:	rp - the room
//					n_new_verts - how many vertices are being added to the room
// Returns:		the number of the first new vertex
int RoomAddVertices(room *rp, int num_new_verts) {
  if (num_new_verts == 0)
    return 0;

  vector *newverts = (vector *)mem_malloc((rp->num_verts + num_new_verts) * sizeof(*newverts));

  ASSERT(newverts != NULL);

  for (int i = 0; i < rp->num_verts; i++) {
    newverts[i] = rp->verts[i];
  }

  mem_free(rp->verts);

  rp->verts = newverts;

  rp->num_verts += num_new_verts;

  return (rp->num_verts - num_new_verts);
}

// Create space for additional faces in a room.
// Allocates a new faces array, copies from the old list, and frees the old list
// The new faces are at the end of the list, so none of the old faces change number
// Parameters:	rp - the room
//					num_new_faces - how many faces are being added to the room
// Returns:		the number of the first new face
int RoomAddFaces(room *rp, int num_new_faces) {
  int i;

  if (num_new_faces == 0)
    return 0;

  face *newfaces = (face *)mem_malloc((rp->num_faces + num_new_faces) * sizeof(*newfaces));

  ASSERT(newfaces != NULL);

  for (i = 0; i < rp->num_faces; i++)
    newfaces[i] = rp->faces[i];

  mem_free(rp->faces);

  rp->faces = newfaces;
  rp->num_faces += num_new_faces;

  if (rp->num_bbf_regions) {
    for (i = 0; i < rp->num_bbf_regions; i++) {
      mem_free(rp->bbf_list[i]);
    }
    mem_free(rp->bbf_list);
    mem_free(rp->num_bbf);
    mem_free(rp->bbf_list_min_xyz);
    mem_free(rp->bbf_list_max_xyz);
    mem_free(rp->bbf_list_sector);

    rp->num_bbf_regions = 0;
  }

  return (rp->num_faces - num_new_faces);
}

// Check if a point is inside, outside, or on an edge of a polygon
// Parameters:	checkv - the point to be checked
//					v1,v0 - the edge to check against. Two sequential verts in a clockwise polygon.
//					normal - the surface normal of the polygon
// Returns:	 1 if the point in inside the edge
//				 0 if the point is on the edge
//				-1 if the point is outside the edge
int CheckPointAgainstEdge(vector *checkv, vector *v0, vector *v1, vector *normal) {
  int ii, jj;
  float edge_i, edge_j, check_i, check_j;
  float *vv0, *vv1, *checkvv;
  float edge_mag, dot;

  // Get the vertices for projection
  GetIJ(normal, &ii, &jj);

  // Get pointers to elements of our vectors
  vv0 = (float *)v0;
  vv1 = (float *)v1;
  checkvv = (float *)checkv;

  // Get 2d vector for edge
  edge_i = vv1[ii] - vv0[ii];
  edge_j = vv1[jj] - vv0[jj];
  edge_mag = sqrt(edge_i * edge_i + edge_j * edge_j);

  // Get 2d vector for check point
  check_i = checkvv[ii] - vv0[ii];
  check_j = checkvv[jj] - vv0[jj];

  // Now do the dot product to see if the check point is on the front
  dot = ((-edge_j * check_i) + (edge_i * check_j)) / edge_mag;

  // Check dot value and return appropriate code
  if (dot > POINT_TO_EDGE_EPSILON)
    return -1;
  else if (dot < -POINT_TO_EDGE_EPSILON)
    return 1;
  else
    return 0;
}

// Clips on edge of a polygon against another edge
// Parameters:	normal - defines the plane in which these edgs lie
//					v0,v1 - the edge to be clipped
//					v2,v3 - is the edge clipped against
//					newv - filled in with the intersection point
void ClipEdge(vector *normal, vertex *v0, vertex *v1, vector *v2, vector *v3, vertex *newv) {
  float *vv0, *vv1, *vv2, *vv3;
  float k;
  int ii, jj;

  // Get the vertices for projection
  GetIJ(normal, &ii, &jj);

  // Get pointers to elements of our vectors
  vv0 = (float *)&v0->vec;
  vv1 = (float *)&v1->vec;
  vv2 = (float *)v2;
  vv3 = (float *)v3;

  k = ((vv2[jj] - vv0[jj]) * (vv3[ii] - vv2[ii]) - (vv2[ii] - vv0[ii]) * (vv3[jj] - vv2[jj])) /
      ((vv1[jj] - vv0[jj]) * (vv3[ii] - vv2[ii]) - (vv1[ii] - vv0[ii]) * (vv3[jj] - vv2[jj]));

  // Deal w/ precision problems
  if (k < 0.0) {
    ASSERT((vm_VectorDistance(&v1->vec, &v0->vec) * -k) < POINT_TO_EDGE_EPSILON);
    k = 0.0;
  }
  if (k > 1.0) {
    ASSERT((vm_VectorDistance(&v1->vec, &v0->vec) * (k - 1.0)) < POINT_TO_EDGE_EPSILON);
    k = 1.0;
  }

  // Check for valid values of k
  ASSERT((k >= 0) && (k <= 1.0));

  newv->vec = v0->vec + (v1->vec - v0->vec) * k;

  newv->uvl.u = v0->uvl.u + (v1->uvl.u - v0->uvl.u) * k;
  newv->uvl.v = v0->uvl.v + (v1->uvl.v - v0->uvl.v) * k;
  newv->uvl.alpha = v0->uvl.alpha + ((v1->uvl.alpha - v0->uvl.alpha) * k);
}

// Finds a shared edge, if one exists, between two faces in the same room
// Parameters:	fp0,fp1 - pointers to the two faces
//					vn0,vn1 - filled in with the vertex numbers of the edge.  These vert numbers are
//									relative to their own faces.  The shared edge is
//verts <vn0,vn0+1> on 									face 0, and <vn1+1,vn1> on face 1 Returns:		true if a shared edge was found, else
// false
bool FindSharedEdge(face *fp0, face *fp1, int *vn0, int *vn1) {
  int i, j, a0, b0, a1, b1;

  // Go through each edge in first face
  for (i = 0; i < fp0->num_verts; i++) {

    // Get edge verts - <a0,b0> is edge on first face
    a0 = fp0->face_verts[i];
    b0 = fp0->face_verts[(i + 1) % fp0->num_verts];

    // Check against second face
    for (j = 0; j < fp1->num_verts; j++) {

      // Get edge verts - <a1,b1> is edge on second face
      a1 = fp1->face_verts[j];
      b1 = fp1->face_verts[(j + 1) % fp1->num_verts];

      //@@if ((a0==a1) && (b0==b1))
      //@@	Int3();							//If you hit this, you probably have a duplicate
      //or overlapping face

      if ((a0 == b1) && (b0 == a1)) { // found match!
        *vn0 = i;
        *vn1 = j;
        return 1;
      }
    }
  }

  // Didn't find an edge, so return error
  return 0;
}

// Finds a shared edge, if one exists, between two faces in different rooms
// Parameters:	rp0,rp1 - pointers to the two rooms
//					face0,face1 - the face numbers in rp0 & rp1, respectively
//					vn0,vn1 - filled in with the vertex numbers of the edge.  These vert numbers are
//									relative to their own faces.  The shared edge is
//verts <vn0,vn0+1> on 									face 0, and <vn1+1,vn1> on face 1 Returns:		true if a shared edge was found, else
// false
bool FindSharedEdgeAcrossRooms(room *rp0, int face0, room *rp1, int face1, int *vn0, int *vn1) {
  int i, j;
  vector *va0, *vb0, *va1, *vb1;
  face *fp0, *fp1;

  // Get pointers to the two faces
  fp0 = &rp0->faces[face0];
  fp1 = &rp1->faces[face1];

  // Go through each edge in first face
  for (i = 0; i < fp0->num_verts; i++) {

    // Get edge verts - <va0,vb0> is edge on first face
    va0 = &rp0->verts[fp0->face_verts[i]];
    vb0 = &rp0->verts[fp0->face_verts[(i + 1) % fp0->num_verts]];

    // Check against second face
    for (j = 0; j < fp1->num_verts; j++) {

      // Get edge verts - <va1,vb1> is edge on second face
      va1 = &rp1->verts[fp1->face_verts[j]];
      vb1 = &rp1->verts[fp1->face_verts[(j + 1) % fp1->num_verts]];

      if (PointsAreSame(va0, va1) && PointsAreSame(vb0, vb1)) // this shouldn't happen
        Int3();

      if (PointsAreSame(va0, vb1) && PointsAreSame(vb0, va1)) { // found match!
        *vn0 = i;
        *vn1 = j;
        return 1;
      }
    }
  }

  // Didn't find an edge, so return error
  return 0;
}

// Delete a vertex from a room.  Assumes the vertex is unused.
// Parameters:	rp - pointer to room
//					vertnum - the vertex to delete
void DeleteRoomVert(room *rp, int vertnum) {
  int f, v;
  face *fp;
  vector *newverts;

  // Remap vertices in faces
  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
    for (v = 0; v < fp->num_verts; v++)
      if (fp->face_verts[v] == vertnum)
        Int3(); // THIS IS VERY BAD!  DELETING A VERTEX STILL IN USE!
      else if (fp->face_verts[v] > vertnum)
        fp->face_verts[v]--;

  // malloc new list
  newverts = (vector *)mem_malloc(sizeof(*newverts) * (rp->num_verts - 1));
  ASSERT(newverts != NULL);

  // Copy verts to new list
  for (v = 0; v < vertnum; v++) {
    newverts[v] = rp->verts[v];
  }

  for (; v < rp->num_verts - 1; v++) {
    newverts[v] = rp->verts[v + 1];
  }

  // Delete old list
  mem_free(rp->verts);

  // Use new list
  rp->verts = newverts;

  // Update count
  rp->num_verts--;
}

// Check the vertices in a room & remove unused ones
// Parameters:	rp - the room to check
// Returns: the number of vertices removed
int DeleteUnusedRoomVerts(room *rp) {
  bool vert_used[MAX_VERTS_PER_ROOM];
  int f, v;
  face *fp;
  int n_deleted = 0;
  ;

  // Init all the flags to unused
  for (v = 0; v < rp->num_verts; v++)
    vert_used[v] = 0;

  // Go through all the faces & flag the used verts
  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
    for (v = 0; v < fp->num_verts; v++)
      vert_used[fp->face_verts[v]] = 1;

  // Now delete the unused verts
  for (v = rp->num_verts - 1; v >= 0; v--)
    if (!vert_used[v]) {
      DeleteRoomVert(rp, v);
      n_deleted++;
    }

  // Done
  return n_deleted;
}

// Delete a face from a room
// Parameters:	rp - the room the face is in
//					facenum - the face to be deleted
void DeleteRoomFace(room *rp, int facenum, bool delete_unused_verts) {
  int p, f, i, t;
  face *newfaces;

  // Check for trigger on this face
  if (rp->faces[facenum].flags & FF_HAS_TRIGGER)
    DeleteTrigger(ROOMNUM(rp), facenum);

  // Adjust face numbers in portals
  for (p = 0; p < rp->num_portals; p++) {
    portal *pp = &rp->portals[p];
    ASSERT(pp->portal_face != facenum);
    if (pp->portal_face > facenum)
      pp->portal_face--;
  }

  // Adjust face numbers in triggers
  for (t = 0; t < Num_triggers; t++) {
    trigger *tp = &Triggers[t];
    if (tp->roomnum == ROOMNUM(rp)) {
      ASSERT(tp->facenum != facenum);
      if (tp->facenum > facenum)
        tp->facenum--;
    }
  }

  // Allocate new face list
  newfaces = (face *)mem_malloc(sizeof(*newfaces) * (rp->num_faces - 1));
  ASSERT(newfaces != NULL);

  // Copy faces over
  for (f = 0; f < facenum; f++)
    newfaces[f] = rp->faces[f];
  for (f++; f < rp->num_faces; f++)
    newfaces[f - 1] = rp->faces[f];

#ifdef NEWEDITOR
  // Decrement texture usage
  if (ROOMNUM(rp) < MAX_ROOMS) {
    LevelTexDecrementTexture(rp->faces[facenum].tmap);
    //@@RoomTexDecrementTexture(rp->faces[facenum].tmap,m_Textures_in_use,false);
  } else {
    // TODO: for room tab, replace second line with first
    ned_MarkTextureInUse(rp->faces[facenum].tmap, false);
    //@@RoomTexDecrementTexture(rp->faces[facenum].tmap,m_Textures_in_use);
  }
#endif

  // Free deleted face memeory
  FreeRoomFace(&rp->faces[facenum]);

  // Free old face list
  mem_free(rp->faces);

  // Use new face list
  rp->faces = newfaces;
  rp->num_faces--;

  // Adjust the current and marked faces if necessary
#ifdef NEWEDITOR
  if (Editor()->m_pLevelWnd != NULL)
#endif
    if (rp == Curroomp) {
      if (Curface == rp->num_faces)
        Curface = rp->num_faces - 1;
      else if (Curface > rp->num_faces)
        Int3(); // this shouldn't be
      if (Markedface == rp->num_faces)
        Markedface = rp->num_faces - 1;
      else if (Markedface > rp->num_faces)
        Int3(); // this shouldn't be
    }

  if (rp->num_bbf_regions) {
    for (i = 0; i < rp->num_bbf_regions; i++) {
      mem_free(rp->bbf_list[i]);
    }
    mem_free(rp->bbf_list);
    mem_free(rp->num_bbf);
    mem_free(rp->bbf_list_min_xyz);
    mem_free(rp->bbf_list_max_xyz);
    mem_free(rp->bbf_list_sector);

    rp->num_bbf_regions = 0;
  }

  // Get rid of any now-unused verts
  if (delete_unused_verts)
    DeleteUnusedRoomVerts(rp);
}

// Deletes a portal from a room.  Does not delete this portal this connects to
// Parameters:	rp - the room the portal is in
//					portalnum - the portal to be deleted
void DeleteRoomPortal(room *rp, int portalnum) {
  portal *pp = &rp->portals[portalnum];
  face *fp = &rp->faces[pp->portal_face];
  portal *newportals;

  // Clear the portal field of the portal's face
  ASSERT(fp->portal_num == portalnum);
  fp->portal_num = -1;

  // Renumber all portals that come after this one
  for (int p = portalnum + 1; p < rp->num_portals; p++) {
    portal *tp = &rp->portals[p];

    // Renumber the face in this portal
    ASSERT(rp->faces[tp->portal_face].portal_num == p);
    rp->faces[tp->portal_face].portal_num--;

    // Renumber the link back to this portal
    if (tp->croom != -1)
      Rooms[tp->croom].portals[tp->cportal].cportal--;
  }

  // Alloc new portal list
  if (rp->num_portals == 1)
    newportals = NULL;
  else {
    newportals = (portal *)mem_malloc(sizeof(*newportals) * (rp->num_portals - 1));
    ASSERT(newportals != NULL);
  }

  // Copy portals over
  for (p = 0; p < portalnum; p++)
    newportals[p] = rp->portals[p];
  for (p++; p < rp->num_portals; p++)
    newportals[p - 1] = rp->portals[p];

  // Free old portal list
  mem_free(rp->portals);

  // Use the new list
  rp->portals = newportals;
  rp->num_portals--;
}

#if 0
//Remove holes in the room list
void CompressRooms(void)
{
	int		hole,t,high_room;

	t = Highest_room_index;
	high_room=Highest_room_index;


	for (hole=0; hole < t; hole++)
		if (! Rooms[hole].used) {

			// found an unused t which is a hole if a used t follows (not necessarily immediately) it.
			while (! Rooms[t].used)
				t--;

			if (t > hole) {
				room *rp;
				int objnum;

				// Ok, hole is the index of a hole, t is the index of a t which follows it.
				// Copy t into hole, update pointers to it, update Curroomp, Markedroomp if necessary.
				Rooms[hole] = Rooms[t];
				Rooms[t].used = 0;

				if (Curroomp == &Rooms[t])
					Curroomp = &Rooms[hole];

				if (Markedroomp == &Rooms[t])
					Markedroomp = &Rooms[hole];

				//Fix connections
				rp = &Rooms[hole];
				for (int p=0;p<rp->num_portals;p++) {
					portal *pp = &rp->portals[p];

					if (pp->croom == -1) {			//a terrain connection
						for (int l=0;l<MAX_LINK_TILES;l++)
							if (Link_tile[l].terrain_seg != -1)
								if (Link_tile[l].mine_seg == t) {
									Link_tile[l].mine_seg = hole;
									break;
								}
						ASSERT(l < MAX_LINK_TILES);
					}
					else {
						ASSERT(Rooms[pp->croom].portals[pp->cportal].croom == t);
						Rooms[pp->croom].portals[pp->cportal].croom = hole;
					}
				}

				//Update object room pointers
				for (objnum = rp->objects; objnum != -1; objnum = Objects[objnum].next) {
					ASSERT(Objects[objnum].roomnum == t);
					Objects[objnum].roomnum = hole;
				}

				//Fix triggers
				for (p=0;p<Num_triggers;p++)
					if (Triggers[p].roomnum == t)
						Triggers[p].roomnum = hole;

				//Fix selected list
				for (int i=0;i<N_selected_rooms;i++)
					if (Selected_rooms[i] == t)
						Selected_rooms[i] = hole;

				t--;
			}	// end if (t > hole)
		}	// end if

	while (! Rooms[Highest_room_index].used)
		Highest_room_index--;
}

// Compress mine by getting rid of holes the the room array
void CompressMine()
{
	//if (Do_duplicate_vertex_check) {
	//	med_combine_duplicate_vertices(Vertex_active);
	//	Do_duplicate_vertex_check = 0;
	//}

	CompressRooms();
}
#endif

// Copies the contents of one face to another.
// Parameters:	dfp - pointer to the destination face.  This face should be uninitialized.
//					sfp - pointer to the source face
void CopyPortal(face *dfp, face *sfp) {
  InitRoomFace(dfp, sfp->num_verts);

  dfp->flags = sfp->flags;
  dfp->portal_num = sfp->portal_num;
  dfp->normal = sfp->normal;
  dfp->tmap = sfp->tmap;

  for (int i = 0; i < sfp->num_verts; i++) {
    dfp->face_verts[i] = sfp->face_verts[i];
    dfp->face_uvls[i] = sfp->face_uvls[i];
  }
}

// Copies the data from one room into another
// Note: Portals are not copied, and the new room will have zero portals
// Parameters:	destp - the destination room of the copy
//					srcp - the source room for the copy
void CopyRoom(room *destp, room *srcp) {
  // Initialize the new room
  InitRoom(destp, srcp->num_verts, srcp->num_faces, 0);

  // Copy over the faces
  for (int i = 0; i < destp->num_faces; i++) {
    CopyFace(&destp->faces[i], &srcp->faces[i]);
#ifdef NEWEDITOR
    LevelTexIncrementTexture(srcp->faces[i].tmap);
#endif
  }

  // Copy over the verts
  for (i = 0; i < destp->num_verts; i++)
    destp->verts[i] = srcp->verts[i];

  // Copy doorway info
  if (srcp->doorway_data) {
    destp->doorway_data = (doorway *)mem_malloc(sizeof(*destp->doorway_data));
    *destp->doorway_data = *srcp->doorway_data;
  }

  // Copy over the rest of the data
  destp->flags = srcp->flags;

  // Copy over room lighting
  Room_multiplier[destp - Rooms] = Room_multiplier[srcp - Rooms];
  Room_ambience_r[destp - Rooms] = Room_ambience_r[srcp - Rooms];
  Room_ambience_g[destp - Rooms] = Room_ambience_g[srcp - Rooms];
  Room_ambience_b[destp - Rooms] = Room_ambience_b[srcp - Rooms];
}

// Adds a new portal for this room.  Returns the portal number.
// Initializes the flags
int AddPortal(room *rp) {
  portal *newlist;
  int i;

  newlist = (portal *)mem_malloc(sizeof(*newlist) * (rp->num_portals + 1));

  // Copy from old list to new list, and free old list
  if (rp->num_portals) {

    for (i = 0; i < rp->num_portals; i++)
      newlist[i] = rp->portals[i];

    mem_free(rp->portals);
  }

  // Point at new list
  rp->portals = newlist;

  // Init flags
  rp->portals[rp->num_portals].flags = 0;
  rp->portals[rp->num_portals].bnode_index = -1;

  return rp->num_portals++;
}

// Links two rooms, creating portals in each room
// Parameters:	roomlist - pointer to the array of rooms
//					room0,face0 - the room & face numbers of the first room
//					room1,face1 - the room & face numbers of the second room
void LinkRooms(room *roomlist, int room0, int face0, int room1, int face1) {
  room *rp0, *rp1;
  int pn0, pn1;
  int nv0, nv1;

  // Set some vars
  rp0 = &roomlist[room0];
  rp1 = &roomlist[room1];
  nv0 = rp0->faces[face0].num_verts;
  nv1 = rp1->faces[face1].num_verts;

  // Make sure no portals already
  ASSERT(rp0->faces[face0].portal_num == -1);
  ASSERT(rp1->faces[face1].portal_num == -1);

  // Check for match
  if (nv0 != nv1)
    Int3(); // You must get Matt if you hit this!

  // Create portals
  pn0 = AddPortal(rp0);
  pn1 = AddPortal(rp1);

  // Link portals
  rp0->portals[pn0].croom = room1;
  rp0->portals[pn0].cportal = pn1;
  rp1->portals[pn1].croom = room0;
  rp1->portals[pn1].cportal = pn0;

  // Add faces to portals
  rp0->portals[pn0].portal_face = face0;
  rp1->portals[pn1].portal_face = face1;

  // Mark faces as being part of portals
  rp0->faces[face0].portal_num = pn0;
  rp1->faces[face1].portal_num = pn1;
}

// Finds the min and max x,y,z values of the vertices in a room
// Parameters:	min,max - filled in with the minimum and maximum x,y, & z values, respectively
//					rp = the room
void ComputeRoomMinMax(vector *min, vector *max, room *rp) {
  min->x = min->y = min->z = FLT_MAX;
  max->x = max->y = max->z = -FLT_MAX;

  for (int i = 0; i < rp->num_verts; i++) {
    if (rp->verts[i].x > max->x)
      max->x = rp->verts[i].x;
    if (rp->verts[i].y > max->y)
      max->y = rp->verts[i].y;
    if (rp->verts[i].z > max->z)
      max->z = rp->verts[i].z;

    if (rp->verts[i].x < min->x)
      min->x = rp->verts[i].x;
    if (rp->verts[i].y < min->y)
      min->y = rp->verts[i].y;
    if (rp->verts[i].z < min->z)
      min->z = rp->verts[i].z;
  }
}

// Builds a list of all the vertices in a room that are part of a portal
// Parameters:	rp - the room to check
//					list - filled in with the list of vert numbers.  List should be
//MAX_VERTS_PER_ROOM big Returns:		the number of verts in the list
int BuildListOfPortalVerts(room *rp, int *list) {
  int i, t, j;
  int count = 0;

  for (i = 0; i < rp->num_portals; i++) {
    face *fp = &rp->faces[rp->portals[i].portal_face];

    for (t = 0; t < fp->num_verts; t++) {
      int v = fp->face_verts[t];

      for (j = 0; j < count; j++)
        if (list[j] == v)
          break;

      if (j == count)
        list[count++] = v;
    }
  }

  return count;
}

#define BUF_LEN 100000

char error_buf[BUF_LEN];
int error_buf_offset;

// Log an error in the room check process
void CheckError(const char *str, ...) {
  std::va_list arglist;
  int nchars;

  va_start(arglist, str);
  nchars = std::vsnprintf(error_buf + error_buf_offset, BUF_LEN - error_buf_offset, str, arglist);
  va_end(arglist);

  error_buf_offset += strlen(error_buf + error_buf_offset);

  if (error_buf_offset >= BUF_LEN)
    OutrageMessageBox("There has been a text buffer overflow in CheckError().");
}

// Checks the normals in a room
// Returns the number of bad normals
int CheckNormals(room *rp) {
  int errors = 0;

  for (int f = 0; f < rp->num_faces; f++)
    if (!ComputeFaceNormal(rp, f)) {
      CheckError("Room %3d face %3d has a bad or low-precision normal\n", ROOMNUM(rp), f);
      errors++;
    }

  return errors;
}

// Checks for concave faces
// Returns the number of concave faces
int CheckConcaveFaces(room *rp) {
  int f;
  face *fp;
  int errors = 0;

  // Go through all the faces
  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {

    int vert = CheckFaceConcavity(fp->num_verts, fp->face_verts, &fp->normal, rp->verts);
    if (vert != -1) {
      CheckError("Room %3d face %3d is concave at vertex %d\n", ROOMNUM(rp), f, vert);
      errors++;
    }
  }

  return errors;
}

int CheckDegenerateFaces(room *rp) {
  int errors = 0;
  int f, v;
  face *fp;

  // Go through all the faces
  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
    for (v = 0; v < fp->num_verts; v++)
      if (fp->face_verts[v] == fp->face_verts[(v + 2) % fp->num_verts]) {
        CheckError("Room %3d face %3d is degenerate\n", ROOMNUM(rp), f);
        errors++;
        break;
      }
  }

  return errors;
}

// Make sure the two faces of a portal match
// Returns true if the portal is ok
bool CheckPortal(room *rp0, int p0) {
  int i, j, p1;
  room *rp1;
  portal *pp0, *pp1;
  face *fp0, *fp1;

  // Get info
  pp0 = &rp0->portals[p0];
  rp1 = &Rooms[pp0->croom];
  p1 = pp0->cportal;
  pp1 = &rp1->portals[p1];
  fp0 = &rp0->faces[pp0->portal_face];
  fp1 = &rp1->faces[pp1->portal_face];

  // Make sure faces have the same number of verts
  if (fp0->num_verts != fp1->num_verts) {
    CheckError("Room %d portal %d has a different number of vertices (%d) than room %d portal %d (%d)\n", ROOMNUM(rp0),
               p0, fp0->num_verts, ROOMNUM(rp1), p1, fp1->num_verts);
    return 0;
  }

  // Find one point in common
  for (i = 0; i < fp0->num_verts; i++) {
    for (j = 0; j < fp1->num_verts; j++)
      if (PointsAreSame(&rp0->verts[fp0->face_verts[i]], &rp1->verts[fp1->face_verts[j]]))
        break;
    if (j < fp1->num_verts)
      break;
  }
  if (i >= fp0->num_verts) {
    CheckError("Cannot find a single matching point between room %d portal %d and room %d portal %d\n", ROOMNUM(rp0),
               p0, ROOMNUM(rp1), p1);
    return 0;
  }

  vector *v0, *v1, *prev0, *prev1;
  int n;

  // Trace through verts in faces, making sure they match
  prev0 = &rp0->verts[fp0->face_verts[i]];
  prev1 = &rp1->verts[fp1->face_verts[j]];
  for (n = 1; n < fp0->num_verts; n++) {

    v0 = &rp0->verts[fp0->face_verts[(i + n) % fp0->num_verts]];
    v1 = &rp1->verts[fp1->face_verts[(j - n + fp1->num_verts) % fp1->num_verts]];

    if (!PointsAreSame(v0, v1)) {
      CheckError("Vertex %d in room %d portal %d does not match vertex %d in room %d portal %d\n",
                 (i + n) % fp0->num_verts, ROOMNUM(rp0), p0, (j - n + fp1->num_verts) % fp1->num_verts, ROOMNUM(rp1),
                 p1);
      return 0;
    }
  }

  return 1;
}

extern void DumpTextToClipboard(char *text);

// Checks for bad portal connections
// Returns the number of bad portals
int CheckPortals(room *rp) {
  portal *pp;
  int p;
  int r = ROOMNUM(rp);
  int errors = 0;

  for (p = 0, pp = rp->portals; p < rp->num_portals; pp++, p++) {

    // Make sure the connecting portal points back to this portal
    if ((Rooms[pp->croom].portals[pp->cportal].croom != r) || (Rooms[pp->croom].portals[pp->cportal].cportal != p)) {
      CheckError("Room %d, portal %d points at room %d portal %d, but the latter points at room %d portal %d\n", r, p,
                 pp->croom, pp->cportal, Rooms[pp->croom].portals[pp->cportal].croom,
                 Rooms[pp->croom].portals[pp->cportal].cportal);
      errors++;
    }

    // Check to make sure the face in this portal points back to it
    if (rp->faces[pp->portal_face].portal_num != p) {
      CheckError("Room %d portal %d contains face %d, but that face points at portal %d\n", r, p, pp->portal_face,
                 rp->faces[pp->portal_face].portal_num);
      errors++;
    }
  }

  return errors;
}

// Checks if the given face is a duplicate of another face
// Returns the face number of which this is a duplicate, or -1 if not a duplicate
int CheckForDuplicateFace(room *rp, int facenum) {
  face *fp0 = &rp->faces[facenum];
  int r = ROOMNUM(rp);

  for (int j = 0; j < facenum; j++) {
    face *fp1 = &rp->faces[j];

    if (fp0->num_verts == fp1->num_verts)
      for (int v = 0; v < fp1->num_verts; v++) // look for a shared vert
        if (fp1->face_verts[v] == fp0->face_verts[0]) {
          for (int t = 0; t < fp0->num_verts; t++)
            if (fp0->face_verts[t] != fp1->face_verts[(v + t) % fp1->num_verts])
              break;
          if (t == fp0->num_verts) {
            return j;
          }
          break;
        }
  }

  // Didn't find a duplicate
  return -1;
}

// Removes all the duplicate faces in a room
void RemoveDuplicateFaces(room *rp) {
  int r = ROOMNUM(rp);
  int removed = 0;

  for (int i = 0; i < rp->num_faces; i++) {
    int dup = CheckForDuplicateFace(rp, i);

    if (dup != -1) {
      DeleteRoomFace(rp, i);
      mprintf(0, "Removed face %d (duplicate of face %d) from room %d\n", i, dup, r);
      removed++;
      i--;
    }
  }

  if (removed) {
    OutrageMessageBox("%d duplicate faces have been removed from room %d.", removed, r);
    World_changed = 1;
  } else
    OutrageMessageBox("There are no duplicate faces in room %d.", r);
}

// Checks for duplicate faces
// Returns the number of duplicate faces
int CheckDuplicateFaces(room *rp) {
  int r = ROOMNUM(rp);
  int errors = 0;

  for (int i = 0; i < rp->num_faces; i++) {
    int dup = CheckForDuplicateFace(rp, i);

    if (dup != -1) {
      CheckError("Room %d: face %d is the same as face %d\n", r, i, dup);
      errors++;
    }
  }

  return errors;
}

// Checks for non-planar faces
// Returns the number of non-planar faces
int CheckNonPlanarFaces(room *rp) {
  int r = ROOMNUM(rp);
  int errors = 0;

  for (int f = 0; f < rp->num_faces; f++)
    if (!FaceIsPlanar(rp, f)) {
      if (rp->faces[f].portal_num != -1)
        CheckError("Room %d: face %d is not planar.  FACE IS PORTAL!\n", r, f);
      else
        CheckError("Room %d: face %d is not planar\n", r, f);
      errors++;
    }

  return errors;
}

// Checks for duplicate points
// Returns the number of duplicate points
int CheckDuplicatePoints(room *rp) {
  int r = ROOMNUM(rp);
  int errors = 0;

  for (int i = 0; i < rp->num_verts; i++)
    for (int j = 0; j < i; j++)
      if (PointsAreSame(&rp->verts[i], &rp->verts[j])) {
        float d = vm_VectorDistance(&rp->verts[i], &rp->verts[j]);
        CheckError("Room %d: vert %3d is the same as vert %3d (d=%.2f)\n", r, i, j, d);
        errors++;
      }

  return errors;
}

// Find any unused points in a room
int CheckUnusedPoints(room *rp) {
  int r = ROOMNUM(rp);
  int errors = 0;
  bool vert_used[MAX_VERTS_PER_ROOM];
  int f, v;
  face *fp;

  // Init all the flags to unused
  for (v = 0; v < rp->num_verts; v++)
    vert_used[v] = 0;

  // Go through all the faces & flag the used verts
  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
    for (v = 0; v < fp->num_verts; v++)
      vert_used[fp->face_verts[v]] = 1;

  // Now delete the unused verts
  for (v = 0; v < rp->num_verts; v++)
    if (!vert_used[v]) {
      CheckError("Room %d: point %d is unused\n", r, v);
      errors++;
    }

  // Done
  return errors;
}

// Checks for duplicate points in faces
// Returns the number of duplicate face points
int CheckDuplicateFacePoints(room *rp) {
  int r = ROOMNUM(rp);
  int f, v, errors = 0;
  face *fp;

  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
    for (v = 0; v < fp->num_verts; v++)
      if (fp->face_verts[v] == fp->face_verts[(v + 1) % fp->num_verts]) {
        CheckError("Room %d, face %d: vert #%d (%d) is the same as #%d\n", r, f, (v + 1) % fp->num_verts,
                   fp->face_verts[v], v);
        errors++;
      }

  return errors;
}

// Returns true if faces match exactly, else false
int CheckPortalFaces(room *rp0, int facenum0, room *rp1, int facenum1) {
  face *fp0 = &rp0->faces[facenum0];
  face *fp1 = &rp1->faces[facenum1];
  vector *v0, *v1, *prev_v0, *prev_v1;
  int n, i, j, prev_vn0, prev_vn1;
  int points_added = 0;

  // First, find one point in common
  for (i = 0; i < fp0->num_verts; i++) {
    for (j = 0; j < fp1->num_verts; j++)
      if (PointsAreSame(&rp0->verts[fp0->face_verts[i]], &rp1->verts[fp1->face_verts[j]]))
        break;
    if (j < fp1->num_verts)
      break;
  }
  if (i >= fp0->num_verts)
    return 0;

  prev_vn0 = fp0->face_verts[i];
  prev_vn1 = fp1->face_verts[j];
  prev_v0 = &rp0->verts[prev_vn0];
  prev_v1 = &rp1->verts[prev_vn1];

  if (fp0->num_verts != fp1->num_verts) {
    CheckError("Room %d: portal face %d does not match %d:%d\n", ROOMNUM(rp0), facenum0, ROOMNUM(rp1), facenum1);
    return 0;
  }

  // Trace through faces, adding points where needed
  for (n = 1; n < fp0->num_verts; n++) {
    int vn0, vn1;

    vn0 = fp0->face_verts[(i + n) % fp0->num_verts];
    vn1 = fp1->face_verts[(j - n + fp1->num_verts) % fp1->num_verts];

    v0 = &rp0->verts[vn0];
    v1 = &rp1->verts[vn1];

    if (!PointsAreSame(v0, v1)) { // Points are at least very close.
      CheckError("Room %d: portal face %d does not match %d:%d\n", ROOMNUM(rp0), facenum0, ROOMNUM(rp1), facenum1);
      return 0;
    }

    prev_vn0 = vn0;
    prev_vn1 = vn1;

    prev_v0 = v0;
    prev_v1 = v1;
  }

  return 1; // no errors found, so faces ok
}

int CheckRoomPortalFaces(room *rp) {
  int errors = 0;

  for (int p = 0; p < rp->num_portals; p++) {
    portal *pp = &rp->portals[p];
    if (!CheckPortalFaces(rp, pp->portal_face, &Rooms[pp->croom], Rooms[pp->croom].portals[pp->cportal].portal_face))
      errors++;
  }

  return errors;
}

// Find t-joints in this room
int FindTJoints(room *rp) {
  int f, f2, v, v2;
  face *fp, *fp2;
  int tjoints = 0;
  int points_added = 0;

  // Now search for and fix t-joints
  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
    for (v = 0; v < fp->num_verts; v++) {
      int vv0 = fp->face_verts[v], vv1 = fp->face_verts[(v + 1) % fp->num_verts];
      for (f2 = 0, fp2 = rp->faces; f2 < rp->num_faces; f2++, fp2++) {
        if (f2 != f) {
          for (v2 = 0; v2 < fp2->num_verts; v2++) {
            int tt0 = fp2->face_verts[v2], tt1 = fp2->face_verts[(v2 + 1) % fp2->num_verts];

            if ((vv0 == tt1) && (vv1 == tt0))
              break; // found one, so stop
          }
          if (v2 < fp2->num_verts)
            break;
        }
      }
      if (f2 == rp->num_faces) { // didn't find a match

        // Look for vert on this edge
        for (f2 = 0, fp2 = rp->faces; f2 < rp->num_faces; f2++, fp2++) {
          if (f2 != f) {
            for (v2 = 0; v2 < fp2->num_verts; v2++) {
              int tt0 = fp2->face_verts[v2], tt1 = fp2->face_verts[(v2 + 1) % fp2->num_verts];

              if (vv0 == tt1) { // one point maches; check if next is on the edge
                if (CheckPointToPlane(&rp->verts[tt0], &rp->verts[vv0], &fp->normal) == 0) {
                  if (CheckPointAgainstEdge(&rp->verts[tt0], &rp->verts[vv0], &rp->verts[vv1], &fp->normal) == 0) {
                    // make sure the new point is actually between the two edge points
                    float edge_len = vm_VectorDistance(&rp->verts[vv1], &rp->verts[vv0]);
                    float d0 = vm_VectorDistance(&rp->verts[tt0], &rp->verts[vv0]);
                    float d1 = vm_VectorDistance(&rp->verts[tt0], &rp->verts[vv1]);
                    if ((d0 < edge_len) && (d1 < edge_len)) {
                      CheckError("Room %d: face %d edge %d has a T-joint\n", ROOMNUM(rp), f, v);
                      tjoints++;
                      goto next_face;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  next_face:;
  }

  return tjoints;
}

// Counts the number of unique textures in a level, plus gives names of textures used
void CountUniqueTextures() {
  uint16_t *texture_tracking = (uint16_t *)mem_malloc(MAX_TEXTURES * 2);
  ASSERT(texture_tracking);
  memset(texture_tracking, 0, MAX_TEXTURES * 2);

  for (int i = 0; i <= Highest_room_index; i++) {
    room *rp = &Rooms[i];
    if (rp->used == 0)
      continue;

    for (int t = 0; t < rp->num_faces; t++) {
      face *fp = &rp->faces[t];

      if (fp->portal_num != -1) {
        if (!(rp->portals[fp->portal_num].flags & PF_RENDER_FACES))
          continue;
      }

      if (fp->tmap != -1 && !(GameTextures[fp->tmap].flags & (TF_PROCEDURAL | TF_TEXTURE_64 | TF_TEXTURE_32))) {
        texture_tracking[fp->tmap]++;
      }
    }
  }

  // Now count totals
  int total = 0, total_with_lights = 0;
  for (i = 0; i < MAX_TEXTURES; i++) {
    if (texture_tracking[i]) {
      if (!(GameTextures[i].flags & TF_LIGHT)) {
        total++;
        total_with_lights++;
      } else
        total_with_lights++;
    }
  }

  CheckError("There are %d unique 128x128 textures (excluding lights) in this level:\n", total);
  CheckError("There are %d unique 128x128 textures (including lights) in this level:\n", total_with_lights);

  if (total > 60)
    CheckError("ERROR: YOU HAVE MORE THAT 60 128x128 TEXTURES...YOU *MUST* FIX THIS!\n");

  for (i = 0; i < MAX_TEXTURES; i++) {
    if (texture_tracking[i] && !(GameTextures[i].flags & TF_LIGHT)) {
      CheckError("%d : %s %s bmp=%s\n", texture_tracking[i], GameTextures[i].name,
                 (GameTextures[i].flags & TF_ANIMATED) ? "(Animated)" : "",
                 (GameTextures[i].flags & TF_ANIMATED) ? "" : GameBitmaps[GameTextures[i].bm_handle].name);
    }
  }

  for (i = 0; i < MAX_TEXTURES; i++) {
    if (texture_tracking[i] && (GameTextures[i].flags & TF_LIGHT)) {
      CheckError("%d : %s %s %s bmp=%s\n", texture_tracking[i], GameTextures[i].name,
                 (GameTextures[i].flags & TF_ANIMATED) ? "(Animated)" : "",
                 (GameTextures[i].flags & TF_LIGHT) ? "(Light)" : "",
                 (GameTextures[i].flags & TF_ANIMATED) ? "" : GameBitmaps[GameTextures[i].bm_handle].name);
    }
  }

  mem_free(texture_tracking);
}

// Returns the number of soundsource objects that don't have a sound attached
int CheckSoundsourceObjects() {
  int objnum, total = 0, named = 0, quiet = 0, quiet_unnamed = 0;
  object *objp;

  for (objnum = 0, objp = Objects; objnum <= Highest_object_index; objnum++, objp++) {
    if (objp->type == OBJ_SOUNDSOURCE) {
      ASSERT(objp->control_type == CT_SOUNDSOURCE);
      total++;
      if (objp->name)
        named++;
      if (objp->ctype.soundsource_info.sound_index == -1) {
        CheckError("Soundsource object %d (\"%s\") has no sound specified.\n", objnum,
                   objp->name ? objp->name : "<no name>");
        quiet++;
        if (!objp->name)
          quiet_unnamed++;
      }
    }
  }

  CheckError(
      "This level has %d soundsource objects; %d have names, %d don't have sounds, and %d have no sounds & no name.\n",
      total, named, quiet, quiet_unnamed);

  return quiet;
}

int BOAGetMineChecksum();

// Get rid of large whole parts of face UV coordinates
void NormalizeFaceUVs() {
  int r;
  room *rp;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      int f;
      face *fp;

      for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
        float base_u = floor(fp->face_uvls[0].u);
        float base_v = floor(fp->face_uvls[0].v);

        for (int v = 0; v < fp->num_verts; v++) {
          fp->face_uvls[v].u -= base_u;
          fp->face_uvls[v].v -= base_v;
        }
      }
    }
  }
}

// Test the mine for validity
void VerifyMine() {
  int r;
  room *rp;
  int errors = 0, bad_normals = 0, concave_faces = 0, degenerate_faces = 0, bad_portals = 0, duplicate_faces = 0,
      duplicate_points = 0, duplicate_face_points = 0, unused_points = 0, nonplanar_faces = 0, mismatched_portals = 0,
      tjoints = 0, bad_shells = 0, quiet_soundsource_objects = 0;

  error_buf_offset = 0;

  // Normalize all the UV coordinates in the level
  NormalizeFaceUVs();

  // Check normals, portals, & duplicate faces
  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++)
    if (rp->used) {

      bad_normals += CheckNormals(rp);
      errors += bad_normals;

      concave_faces += CheckConcaveFaces(rp);
      errors += concave_faces;

      degenerate_faces += CheckDegenerateFaces(rp);
      errors += degenerate_faces;

      bad_portals += CheckPortals(rp);
      errors += bad_portals;

      duplicate_faces += CheckDuplicateFaces(rp);
      errors += duplicate_faces;

      nonplanar_faces += CheckNonPlanarFaces(rp);
      errors += nonplanar_faces;

      duplicate_points += CheckDuplicatePoints(rp);
      errors += duplicate_points;

      duplicate_face_points += CheckDuplicateFacePoints(rp);
      errors += duplicate_face_points;

      unused_points += CheckUnusedPoints(rp);
      errors += unused_points;

      mismatched_portals += CheckRoomPortalFaces(rp);
      errors += mismatched_portals;

      tjoints += FindTJoints(rp);
      errors += tjoints;

      if ((rp->num_portals > 0) && !(rp->flags & RF_EXTERNAL)) {
        int shell_errors = ComputeRoomShell(rp);
        if (shell_errors) {
          bad_shells++;
          errors++;
        }
      }
    }

  quiet_soundsource_objects = CheckSoundsourceObjects();
  errors += quiet_soundsource_objects;

  CountUniqueTextures();

  bool terrain_occluded = false;
  bool boa_ran = false;
  bool terrain_volume = false;

  if (Terrain_occlusion_checksum == (Terrain_checksum + 1))
    terrain_occluded = true;
  else
    errors = 1;

  if (BOAGetMineChecksum() == BOA_vis_checksum)
    boa_ran = true;
  else
    errors = true;

  // Check to see if dynamic terrain lighting is calculated
  for (int i = 0; i < TERRAIN_DEPTH * TERRAIN_WIDTH && !terrain_volume; i++) {
    if (Terrain_dynamic_table[i] != 255)
      terrain_volume = true;
  }

  if (!terrain_volume)
    errors = true;

  // Show message if errors
  if (errors) {
    mprintf(0, "Error buf size = %d\n", strlen(error_buf));
    DumpTextToClipboard(error_buf);
    OutrageMessageBox("Mine check results:\n"
                      "\n"
                      "  Bad portals:\t\t%d\n"
                      "  Bad Normals:\t\t%d\n"
                      "  Concave faces:\t\t%d\n"
                      "  Degenerate faces:\t\t%d\n"
                      "  Duplicate faces:\t\t%d\n"
                      "  Non-planar faces:\t\t%d\n"
                      "  Duplicate points:\t\t%d\n"
                      "  Duplicate face points:\t%d\n"
                      "  Unused points:\t\t%d\n"
                      "  Unmatched portals:\t\t%d\n"
                      "  T-Joints:\t\t\t%d\n"
                      "  Bad shells:\t\t%d\n"
                      "  Quiet soundsource objs:\t%d\n"
                      "  Terrain occlusion:\t\t%s\n"
                      "  BOA:\t\t\t%s\n"
                      "  Terrain volume lighting:\t\t\t%s\n"
                      "\n"
                      "\n"
                      "For detailed info, see clipboard.",
                      bad_portals, bad_normals, concave_faces, degenerate_faces, duplicate_faces, nonplanar_faces,
                      duplicate_points, duplicate_face_points, unused_points, mismatched_portals, tjoints, bad_shells,
                      quiet_soundsource_objects, terrain_occluded ? "Valid" : "NOT VALID",
                      boa_ran ? "Valid" : "NOT VALID", terrain_volume ? "Valid" : "NOT VALID");
  } else {
    OutrageMessageBox("Mine has no errors, but check clipboard for texture counts.");
  }
}

// Does CheckMine() stuff on one room only
void VerifyRoom(room *rp) {
  int errors, bad_normals, concave_faces, duplicate_faces, duplicate_points, duplicate_face_points, unused_points,
      nonplanar_faces;

  // Reset error buffer
  error_buf_offset = 0;

  errors = bad_normals = CheckNormals(rp);

  concave_faces = CheckConcaveFaces(rp);
  errors += concave_faces;

  duplicate_faces = CheckDuplicateFaces(rp);
  errors += duplicate_faces;

  nonplanar_faces = CheckNonPlanarFaces(rp);
  errors += nonplanar_faces;

  duplicate_points = CheckDuplicatePoints(rp);
  errors += duplicate_points;

  duplicate_face_points = CheckDuplicateFacePoints(rp);
  errors += duplicate_face_points;

  unused_points = CheckUnusedPoints(rp);
  errors += unused_points;

  // Show message if errors
  if (errors) {
    DumpTextToClipboard(error_buf);
    OutrageMessageBox("Room check results:\n"
                      "\n"
                      "  Bad Normals:\t\t%d\n"
                      "  Concave faces:\t\t%d\n"
                      "  Duplicate faces:\t\t%d\n"
                      "  Non-planar faces:\t\t%d\n"
                      "  Duplicate points:\t\t%d\n"
                      "  Duplicate face points:\t%d\n"
                      "  Unused points:\t\t%d\n"
                      "\n"
                      "\n"
                      "For detailed info, see clipboard.",
                      bad_normals, concave_faces, duplicate_faces, nonplanar_faces, duplicate_points,
                      duplicate_face_points, unused_points);
  } else
    OutrageMessageBox("Room has no errors.");
}

// Copy the flags from one face to another derrived from the first (by clipping or splitting)
// Only those flags which are safe to copy are copied
// Parameters:	dfp - pointer to the destination face
//					sfp - pointer to the source face
void CopyFaceFlags(face *dfp, face *sfp) {
  dfp->flags = 0;

  //@@if (sfp->flags & FF_FORCEFIELD)
  //@@	dfp->flags |= FF_FORCEFIELD;

  if (sfp->flags & FF_GOALFACE)
    dfp->flags |= FF_GOALFACE;
}

// Inserts a vertex into a face
// Parameters:	rp - the room for this face
//					facenum - the face to which to add the vertex
//					new_v - the number of the vertex to add
//					after_v - the new vert is added *after* this vert (index into face verts)
void AddVertToFace(room *rp, int facenum, int new_v, int after_v) {
  face *fp = &rp->faces[facenum];
  int old_verts[MAX_VERTS_PER_FACE];
  roomUVL old_uvls[MAX_VERTS_PER_FACE];
  int t;

  // Make copy of old verts
  for (t = 0; t < fp->num_verts; t++) {
    old_verts[t] = fp->face_verts[t];
    old_uvls[t] = fp->face_uvls[t];
  }

  // Allocate for new verts
  ReInitRoomFace(fp, fp->num_verts + 1);

  // Copy old verts
  for (t = 0; t <= after_v; t++) {
    fp->face_verts[t] = old_verts[t];
    fp->face_uvls[t] = old_uvls[t];
  }

  // Insert new vert
  fp->face_verts[t++] = new_v;

  // Copy rest of new verts
  for (; t < fp->num_verts; t++) {
    fp->face_verts[t] = old_verts[t - 1];
    fp->face_uvls[t] = old_uvls[t - 1];
  }

  // Compute the uv values for the new vert
  vector *v0 = &rp->verts[fp->face_verts[after_v]], *v1 = &rp->verts[fp->face_verts[(after_v + 2) % fp->num_verts]],
         *vn = &rp->verts[fp->face_verts[after_v + 1]];
  roomUVL *uv0 = &fp->face_uvls[after_v], *uv1 = &fp->face_uvls[(after_v + 2) % fp->num_verts];

  float k = vm_VectorDistance(vn, v0) / vm_VectorDistance(v1, v0);

  fp->face_uvls[after_v + 1].u = uv0->u + k * (uv1->u - uv0->u);
  fp->face_uvls[after_v + 1].v = uv0->v + k * (uv1->v - uv0->v);
  fp->face_uvls[after_v + 1].u2 = uv0->u2 + k * (uv1->u2 - uv0->u2);
  fp->face_uvls[after_v + 1].v2 = uv0->v2 + k * (uv1->v2 - uv0->v2);
  fp->face_uvls[after_v + 1].alpha = uv0->alpha + k * (uv1->alpha - uv0->alpha);
}

// Removes the duplicate points in a room
// Returns the number removed
int RemoveDuplicatePoints(room *rp) {
  face *fp;
  int f, v;
  int n_fixed = 0;

  for (int i = 0; i < rp->num_verts; i++)
    for (int j = 0; j < i; j++)
      if (PointsAreSame(&rp->verts[i], &rp->verts[j])) {

        // Replace the higher-numbered point with the lower-numbered in all the faces in this room
        for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
          for (v = 0; v < fp->num_verts; v++)
            if (fp->face_verts[v] == i)
              fp->face_verts[v] = j;

        // Delete the now-unused vert
        DeleteRoomVert(rp, i);

        n_fixed++;

        i--;   // back up, since the point we're checking is now gone
        break; // don't keep checking for duplicates
      }

  return n_fixed;
}

// Remove duplicate points in faces
// Returns the number of duplicate face points removed
int RemoveDuplicateFacePoints(room *rp) {
  int r = ROOMNUM(rp);
  int f, v, n_fixed = 0;
  face *fp;

  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
    for (v = 0; v < fp->num_verts; v++)
      if (fp->face_verts[v] == fp->face_verts[(v + 1) % fp->num_verts]) {
        int new_verts[MAX_VERTS_PER_FACE];
        roomUVL new_uvls[MAX_VERTS_PER_FACE];

        for (int t = 0; t < v; t++) {
          new_verts[t] = fp->face_verts[t];
          new_uvls[t] = fp->face_uvls[t];
        }
        for (; t < fp->num_verts - 1; t++) {
          new_verts[t] = fp->face_verts[t + 1];
          new_uvls[t] = fp->face_uvls[t + 1];
        }

        ReInitRoomFace(fp, fp->num_verts - 1);

        for (t = 0; t < fp->num_verts; t++) {
          fp->face_verts[t] = new_verts[t];
          fp->face_uvls[t] = new_uvls[t];
        }

        n_fixed++;
        f--;
        fp--; // recheck this face
        break;
      }

  return n_fixed;
}

// Removes all the duplicate points in a level
void RemoveAllDuplicateAndUnusedPoints() {
  int r;
  room *rp;
  int n_unused = 0, n_duplicate = 0, n_duplicate_face = 0;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++)
    if (rp->used) {
      n_unused += DeleteUnusedRoomVerts(rp);
      n_duplicate += RemoveDuplicatePoints(rp);
      n_duplicate_face += RemoveDuplicateFacePoints(rp);
    }

  OutrageMessageBox("  %d Unused points deleted\n"
                    "  %d Duplicate points deleted\n"
                    "  %d Duplicate face points deleted\n",
                    n_unused, n_duplicate, n_duplicate_face);

  if (n_unused || n_duplicate || n_duplicate_face)
    World_changed = 1;
}

// Returns the number fixed
void FixDegenerateFaces() {
  int fixed = 0, deleted = 0;
  int r, f, v;
  face *fp;
  room *rp;

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
        bool face_fixed = 0;
      recheck_face:;
        if (fp->num_verts < 3) {
          DeleteRoomFace(rp, f);
          deleted++;
          face_fixed = 0; // deleted overrides fixed
          f--;
          fp = &rp->faces[f];
        } else {
          for (v = 0; v < fp->num_verts; v++) {
            if (fp->face_verts[v] == fp->face_verts[(v + 2) % fp->num_verts]) {
              int16_t tverts[MAX_VERTS_PER_FACE];
              roomUVL tuvls[MAX_VERTS_PER_FACE];

              for (int i = 0; i < fp->num_verts - 2; i++) {
                tverts[i] = fp->face_verts[(v + 2 + i) % fp->num_verts];
                tuvls[i] = fp->face_uvls[(v + 2 + i) % fp->num_verts];
              }
              for (i = 0; i < fp->num_verts - 2; i++) {
                fp->face_verts[i] = tverts[i];
                fp->face_uvls[i] = tuvls[i];
              }
              fp->num_verts -= 2;
              face_fixed = 1;
              goto recheck_face;
            }
          }
        }
        if (face_fixed)
          fixed++;
      }
    }
  }

  OutrageMessageBox("%d Degenerate faces fixed\n%d Degenerate faces deleted", fixed, deleted);

  if (fixed || deleted)
    World_changed = 1;
}

// Finda a face that connects to the specified face
// Starts looking at startface
// Returns the attached facenum, or -1 if found none
int FindConnectedFace(room *rp, int facenum, int edgenum, int startface) {
  face *fp0 = &rp->faces[facenum], *fp1;
  int a0, b0, a1, b1;
  int f;

  // Get edge verts - <a0,b0> is edge on first face
  a0 = fp0->face_verts[edgenum];
  b0 = fp0->face_verts[(edgenum + 1) % fp0->num_verts];

  for (f = startface, fp1 = &rp->faces[startface]; f < rp->num_faces; f++, fp1++) {

    if (f == facenum)
      continue;

    for (int e = 0; e < fp1->num_verts; e++) {

      // Get edge verts - <a1,b1> is edge on second face
      a1 = fp1->face_verts[e];
      b1 = fp1->face_verts[(e + 1) % fp1->num_verts];

      //@@if ((a0==a1) && (b0==b1))
      //@@	Int3();							//If you hit this, you probably have a duplicate
      //or overlapping face

      if ((a0 == b1) && (b0 == a1)) { // found match!
        return f;
      }
    }
  }

  return -1; // no match
}

// Shell flags
#define SHELL_NONE 0
#define SHELL_UNCHECKED 1
#define SHELL_CLOSED 2
#define SHELL_ERROR 3

// Finds the shell for the specified room.  If the shell is found with no errors, sets
// the non-shell flag for those faces not in the shell.  If there are errors finding the
// shell, all faces have the non-shell flag cleared.
// Assumes all portals are part of the shell and starts checking from those faces
// Returns the number of shell errors (unconnected edges) in the room.
// Writes errors to the error buffer
int ComputeRoomShell(room *rp) {
  uint8_t shell_flags[MAX_FACES_PER_ROOM];
  bool done = 0;
  int errors = 0;
  int f;

  for (f = 0; f < rp->num_faces; f++)
    shell_flags[f] = SHELL_NONE;

  // Start with the portal faces
  ASSERT(rp->num_portals > 0);
  for (int p = 0; p < rp->num_portals; p++)
    shell_flags[rp->portals[p].portal_face] = SHELL_UNCHECKED;

  // Check all the unchecked faces
  while (!done) {

    for (f = 0; f < rp->num_faces; f++) {

      if (shell_flags[f] == SHELL_UNCHECKED) {
        face *fp = &rp->faces[f];

        for (int e = 0; e < fp->num_verts; e++) {

          int t = FindConnectedFace(rp, f, e, 0);

          if (t != -1) {
            int t2;

            // See if any additional faces
            t2 = FindConnectedFace(rp, f, e, t + 1);
            if (t2 != -1) {
              // mprintf(0,"Room %d face %d: Found second connection for edge %d (face %d)\n",ROOMNUM(rp),f,e,t);
              // CheckError("Room %d face %d: Found second connection for edge %d (face %d)\n",ROOMNUM(rp),f,e,t);
            } else { // No double-edge, so add connected face

              if (shell_flags[t] == SHELL_NONE)
                shell_flags[t] = SHELL_UNCHECKED;
            }
          } else {
            // mprintf(0,"Room %d face %d: No connection for edge %d\n",ROOMNUM(rp),f,e);
            CheckError("Room %d face %d: No connection for edge %d\n", ROOMNUM(rp), f, e);
            shell_flags[f] = SHELL_ERROR;
            errors++;
          }
        }

        if (shell_flags[f] == SHELL_UNCHECKED)
          shell_flags[f] = SHELL_CLOSED;

        break;
      }
    }

    done = (f == rp->num_faces);
  }

  // Clear flags
  for (f = 0; f < rp->num_faces; f++) {
    ASSERT(shell_flags[f] != SHELL_UNCHECKED);
    rp->faces[f].flags &= ~FF_NOT_SHELL;
  }

  // If no errors, set flags for room
  if (errors == 0) {
    for (f = 0; f < rp->num_faces; f++) {
      if (shell_flags[f] == SHELL_NONE)
        rp->faces[f].flags |= FF_NOT_SHELL;
    }
  }

  return errors;
}

// Finds shells for all rooms.
// Returns the number of rooms with bad shells
int ComputeAllRoomShells() {
  int r, bad_shells = 0;
  room *rp;

  error_buf_offset = 0;

  mprintf(0, "Computing room shells...");

  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used && (rp->num_portals > 0) && !(rp->flags & RF_EXTERNAL)) {
      int errors = ComputeRoomShell(rp);
      if (errors)
        bad_shells++;
    }
  }

  mprintf(0, "Done\n");

  mprintf(0, "Error buf size = %d\n", strlen(error_buf));

  DumpTextToClipboard(error_buf);

  return bad_shells;
}

#include "objinfo.h"
#include "mission.h"

void ListObjectsInLevel(int *object_counts) {
  int i;
  object *objp;

  for (i = 0; i < MAX_OBJECT_IDS; i++)
    object_counts[i] = 0;

  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++) {
    if (IS_GENERIC(objp->type))
      object_counts[objp->id]++;
  }

  CheckError("\n  Robots:\n");
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (object_counts[i] && (Object_info[i].type == OBJ_ROBOT))
      CheckError("    %2d\t%s\n", object_counts[i], Object_info[i].name);
  }

  CheckError("\n  Powerups:\n");
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (object_counts[i] && (Object_info[i].type == OBJ_POWERUP))
      CheckError("    %2d\t%s\n", object_counts[i], Object_info[i].name);
  }

  CheckError("\n  Buildings:\n");
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (object_counts[i] && (Object_info[i].type == OBJ_BUILDING))
      CheckError("    %2d\t%s\n", object_counts[i], Object_info[i].name);
  }

  CheckError("\n  Clutter:\n");
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (object_counts[i] && (Object_info[i].type == OBJ_CLUTTER))
      CheckError("    %2d\t%s\n", object_counts[i], Object_info[i].name);
  }
}

#include "loadlevel.h"

extern bool Disable_editor_rendering;

#define NUM_LEVELS 15

void ListObjectsInAllLevels() {
  int object_counts[NUM_LEVELS + 1][MAX_OBJECT_IDS];
  char levelname[25];
  int i, l;

  error_buf_offset = 0;

  // Clear totals
  for (i = 0; i < MAX_OBJECT_IDS; i++)
    object_counts[0][i] = 0;

  // Get totals for each level
  for (l = 1; l < NUM_LEVELS + 1; l++) {

    sprintf(levelname, "Level%d.d3l", l);

    LoadLevel(levelname);

    CheckError("\n\nLevel: %s\n", levelname);

    ListObjectsInLevel(&object_counts[l][0]);

    // Accumulate totals
    for (i = 0; i < MAX_OBJECT_IDS; i++)
      object_counts[0][i] += object_counts[l][i];
  }

  // Print headers
  CheckError("\n\nName\tType\tTotal");
  for (l = 1; l < NUM_LEVELS + 1; l++)
    CheckError("\t%d", l + 1);

  // Print table
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE) {
      CheckError("\n%s\t%c", Object_info[i].name, Object_type_names[Object_info[i].type][0]);
      for (int l = 0; l < NUM_LEVELS + 1; l++) {
        CheckError("\t%d", object_counts[l][i]);
      }
    }
  }

  DumpTextToClipboard(error_buf);
}
