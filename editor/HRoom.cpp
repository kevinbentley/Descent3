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

 * $Logfile: /DescentIII/Main/editor/HRoom.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Code to implement room functions
 *
 * $Log: not supported by cvs2svn $
 *
 * 106   9/15/99 1:56p Matt
 * Added the option to allow rooms or groups placed on the terrain to
 * either align with the terrain or with gravity.
 *
 * 105   9/07/99 12:10p Matt
 * Added a function to propagate a texture to all adjacent coplanar faces
 * in a room.
 *
 * 104   8/30/99 1:00p Gwar
 * use the "true" center of faces for determining attach points in room
 * connecting functions
 *
 * 103   8/19/99 6:57p Gwar
 * call ned_FindSharedEdge in CombineFaces to see if we can't combine
 * because of a flipped normal
 *
 * 102   8/17/99 7:11p Gwar
 *
 * 101   8/17/99 12:08p Gwar
 * don't set World_changed in functions that can be called from palette
 * rooms
 *
 * 100   8/12/99 12:08a Gwar
 * NEWEDITOR: texture, door and object memory management; and call SetPrim
 * when changing Curroomp, which now force unmarks everything in current
 * room view
 *
 * 99    7/04/99 4:55p Gwar
 * changes for texture management in NEWEDITOR
 *
 * 98    5/08/99 6:39p Matt
 * Added a function to delete a face and all faces connected to it.
 *
 * 97    5/04/99 12:32p Matt
 * Fixed stupid bug and stupider bug.
 *
 * 96    4/30/99 6:52p Matt
 * Added a function to merge an object's geometry into a room.
 *
 * 95    4/28/99 12:51a Matt
 * Added some funtions to edit face geometry.
 *
 * 94    4/25/99 2:38p Gwar
 * brought in HRoom.cpp and RoomUVs.cpp, and several misc game functions
 * were added to globals.cpp to make it possible
 *
 * 93    4/19/99 12:10a Matt
 * Added a menu item to delete a vertex from a face.
 *
 * 92    4/18/99 11:26p Matt
 * Restored point-to-plane check to FixCracks().  This check is necessary
 * because the point-to-edge check assumes that the points are all in the
 * same plane, and will not work if they are not.
 *
 * 91    4/07/99 4:39p Matt
 * In link to new external room, copy the textures from the old faces to
 * the new faces.
 *
 * 90    4/07/99 1:50p Matt
 * Took point-in-plane check out of fix level cracks, because it prevented
 * tjoints from being fixed for some non-planar faces.
 *
 * 89    4/06/99 3:48p Matt
 * Allow combining of rooms with rendered portals.
 *
 * 88    4/06/99 10:23a Matt
 *
 * 87    4/01/99 2:55p Matt
 * Fixed triangulate face code to deal with colinear points
 *
 * 86    4/01/99 1:25p Matt
 * Fixed bug in MatchPortalFaces when checking for match and a colinear
 * point was found.
 *
 * 85    3/31/99 12:58p Matt
 * Added snap-point-to-face
 *
 * 84    3/30/99 8:03p Matt
 * Deleted commented-out code
 *
 * 83    3/30/99 8:01p Matt
 * Took out normals-are-same check when combining adjacent faces.  It was
 * the wrong way to check the faces (the right way (in the D3 editor, that
 * is) is to check for point in the plane) and we were only using it as a
 * first-pass check anyway.
 *
 * 82    3/30/99 6:25p Matt
 * Use new error system for combine faces function.
 *
 * 81    3/29/99 6:46p Matt
 * When combining faces, use FaceIsPlanar() so the face will pass mine
 * verification.
 *
 * 80    3/27/99 5:01p Matt
 * Fixed stupid bug in build bridge code, that assigned UVs to all faces
 * instead of one face, causing an Int3 sometimes for faces that hadn't
 * yet had normals computed.
 *
 * 79    3/27/99 4:45p Matt
 * Fixed a surprising fundamental flaw in the polygon clip code.
 *
 * 78    3/23/99 5:12p Matt
 * Added function to combine rooms.
 *
 * 77    2/27/99 3:47p Mark
 * Place room on terrain was improperly clearing out the placed door.
 * (MattT on Mark's machine)
 *
 * 76    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 75    1/21/99 11:34a Matt
 * Got rid of portal triggers.  Since we don't have multi-face portals, a
 * face trigger works fine for a portal.  Also fixed a few editor/trigger
 * bugs.
 *
 * 74    12/23/98 6:32p Matt
 * Changed, slightly, the process of creating a new face
 *
 * 73    12/23/98 10:53a Matt
 * Added functions to create a face
 *
 * 72    10/07/98 12:48p Matt
 * Added some extra error checking to prevent doubly-formed portals.
 *
 * 71    10/03/98 8:31p Matt
 * Added Join Rooms Exact function.
 *
 * 70    9/25/98 5:25p Matt
 * Don't try to fix cracks in unused rooms.
 *
 * 69    9/24/98 5:00p Matt
 * Improved error checking for running out of rooms.
 *
 * 68    9/16/98 10:02a Matt
 * Fixed serval bugs, in JoinAllOverlappingFaces() and MatchPortalFaces().
 *
 * 67    9/11/98 4:46p Matt
 * Don't allow combining of portal faces, pending code to do the combine
 * correctly.
 *
 * 66    9/10/98 6:38p Matt
 * Deal with error joining faces after smooth bridge.
 *
 * 65    9/09/98 4:07p Matt
 * Added Smooth Bridge function
 *
 * 64    9/08/98 3:25p Matt
 * Changed an error message.
 *
 * 63    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 62    9/07/98 10:58p Matt
 * Added snap point to point.
 *
 * 61    9/07/98 8:14p Matt
 * Don't delete colinear points (& thus form t-joints) when combining
 * faces, and deal properly with combining faces that share multiple
 * edges.
 *
 * 60    9/04/98 3:34p Matt
 * Added groovy vertex snap code
 *
 * 59    9/04/98 12:29p Matt
 * Added marked edge & vertex in the editor
 *
 * 58    9/04/98 11:34a Matt
 * Fixed small bug in portal matching code, that caused one point on the
 * portals not to be set exactly the same.
 *
 * 57    9/03/98 5:29p Matt
 * Added code to fix cracks in levels.
 *
 * 56    9/02/98 5:57p Matt
 * Added code to make faces match exactly when forming a portal.  This
 * should get rid of all remaining cracking problems.
 *
 * 55    9/02/98 4:07p Matt
 * Fixed one kind of cracking:  after clip, make sure old points that
 * more-or-less line up are exactly the same.
 *
 * 54    9/02/98 2:29p Matt
 * Added code to prevent t-joints from being formed when joining rooms
 *
 * 53    9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 52    8/28/98 6:21p Matt
 * Added a function to flip a face.
 *
 * 51    8/24/98 3:02p Matt
 * Gave the user the option, when joining rooms, of extruding straight out
 * or toward the center of the base face.
 *
 * 50    7/01/98 7:53p Matt
 * Added code to allow forcing of join even when the two rooms stick
 * through each other.
 *
 * 49    6/25/98 7:15p Matt
 * Added a function to delete a pair of portals.
 *
 * 48    6/23/98 2:45p Matt
 * Added option when propagating to all faces in a room to only do so to
 * ones with the same texture.
 *
 * 47    6/08/98 12:28p Matt
 * Added a function to triangulate a face
 *
 * 46    5/22/98 4:47p Matt
 * Added menu item to propagate a texture to all the faces in a room.
 *
 * 45    4/27/98 6:41p Matt
 * Added code to join all adjacent faces between two rooms
 *
 * 44    4/17/98 6:25p Matt
 * In CheckFaceToPlane(), store the distance in a variable so it can be
 * looked at in the debugger.
 *
 * 43    4/17/98 6:23p Matt
 * Added code to make sure that the two faces of a portal have the same
 * number of vertices, but commented it out for now.  See the note in the
 * code.
 *
 * 42    4/16/98 11:50a Matt
 * Made snap code work for placed groups.
 *
 * 41    4/07/98 4:19p Matt
 * Fixed (I hope) a problem joining faces that matched perfectly.
 *
 * 40    4/02/98 12:23p Jason
 * trimmed some fat from our structures
 *
 * 39    4/01/98 5:55p Matt
 * Partially re-wrote JoinRooms() to allow creation of adjacent portals.
 *
 * 38    2/18/98 2:26a Matt
 * Fixed typo
 *
 * 37    2/16/98 2:53p Matt
 * Deal with small floating-point precision problem.
 *
 * 36    2/16/98 1:27p Matt
 * Added function to snap the placed room to a vertex/edge on the base
 * room/face
 *
 * 35    2/11/98 12:38p Matt
 * Added epsilon to point-to-plane check
 *
 * 34    2/08/98 6:02p Matt
 * Use groovy new vm_MatrixMulTMatrix() function
 *
 * 33    2/04/98 6:23p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 32    1/30/98 1:27p Matt
 * Orthogonalize after computing rotation matrix for placed rooms (fixed
 * probem of bad matrix making rooms bigger).
 *
 * 31    1/21/98 12:40p Matt
 * When attaching a room to the ground, delete the room's attach face
 *
 * 30    1/21/98 12:32p Matt
 * Revamped viewer system
 *
 * 29    1/20/98 4:43p Matt
 * Fixed up the bridge and join functions
 *
 * 28    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 27    11/17/97 7:39p Sean
 * Changed join epsilon, and took out a return from a bogus error message
 * (Matt on Sean's machine)
 *
 * 26    11/06/97 6:47p Sean
 * FROM JASON: Changed <Highest_room_index to <=
 *
 * 25    11/05/97 7:13p Matt
 * Added join rooms function
 *
 * 24    10/03/97 3:38p Matt
 * Added place and attach code for rooms on the terrain
 *
 * 23    10/01/97 7:51p Matt
 * Added code for external rooms
 *
 * 22    9/29/97 12:09p Jason
 * added functionality to doorway system
 *
 * 21    9/26/97 6:01p Matt
 * Fixed delete room code so that Curroomp is never NULL
 *
 * 20    9/24/97 3:22p Matt
 * Added Drop Room function
 *
 * 19    9/15/97 5:56p Matt
 * Changed message (& fixed handling) when user tries to delete a room
 * attached to the terrain.
 *
 * 18    9/12/97 9:01p Craig
 * Fixed orientation of door object (Matt on Craig's machine)
 *
 * 17    9/12/97 5:38p Jason
 * got doors working
 *
 * 16    9/11/97 5:38p Jason
 * initial door coding for room engine
 *
 * 15    9/06/97 3:18p Matt
 * Use LinkRoomsSimple() when adding, attaching, & bridging
 * Reset Curportal when switch rooms
 *
 * 14    9/04/97 4:39p Matt
 * Added includes needed as a result of removing includes from d3edit.h
 *
 * 13    9/02/97 2:26p Matt
 * Made ComputePlacedRoomMatrix() deal w/ placed rooms or groups
 * Made polygon clipper deal with points on the the edge of the clip
 * polygon
 *
 * 12    8/29/97 5:43p Matt
 * Moved some funcs to erooms.cpp, and fixed some stuff for selected rooms
 *
 * 11    8/27/97 10:30a Matt
 * Fixed bogosity assigning UVs to faces in add room
 *
 * 10    8/22/97 9:30a Matt
 * When adding a room, make the new room the current room, and make the
 * face opposite the connection the current one.  That way you can add
 * several times in a row to create a long tunnel.
 *
 * 9     8/21/97 6:01p Matt
 * Added combine faces & delete room functions
 *
 * 8     8/19/97 1:01p Matt
 * Added error check for facing not overlapping when attaching rooms
 *
 * 7     8/18/97 6:59p Matt
 * Implemented Place Room/Attach room system
 *
 * 6     8/05/97 10:47a Matt
 * Added some error checking, and fixed a bug
 *
 * 5     8/04/97 7:38p Matt
 * Don't add a room if there's already a room at the face
 *
 * 4     8/04/97 12:46p Matt
 * Added BuildBridge() and SetMarkedRoom()
 *
 *
 * 3     8/01/97 6:15p Matt
 * Added code to attach rooms
 *
 * 2     7/22/97 10:33a Matt
 * Added AddRoom()
 *
 * 1     7/21/97 4:48p Matt
 *
 * $NoKeywords: $
 */

#include <stdlib.h>

#include "HRoom.h"

#ifndef NEWEDITOR
#include "d3edit.h"
#else
#include "..\neweditor\globals.h"
#include "..\neweditor\ned_geometry.h"
#endif

#include "erooms.h"
#include "RoomUVs.h"
#include "HView.h"
#include "SelectedRoom.h"
#include "group.h"
#include "door.h"
#include "doorway.h"
#include "terrain.h"
#include "HTexture.h"
#include "trigger.h"

// Make the Marked room/face the current room/face
void SetMarkedRoom() {
  Markedroomp = Curroomp;
  Markedface = Curface;
  Markededge = Curedge;
  Markedvert = Curvert;

  State_changed = 1;

  EditorStatus("Marked room:face set to %d:%d", ROOMNUM(Markedroomp), Markedface);
}

// Select next face on current room
void SelectNextFace() {
  if (++Curface >= Curroomp->num_faces)
    Curface = 0;
  State_changed = 1;
}

// Select previous face on current room
void SelectPrevFace() {
  if (--Curface < 0)
    Curface = Curroomp->num_faces - 1;
  State_changed = 1;
}

#define DEFAULT_ROOM_LENGTH 20.0

// Adds a room at the current room/face.  The room is created by extuding out from the current face
void AddRoom() {
  room *rp;
  face *cfp;
  int cnv, nfaces;
  vector room_delta;
  int i;

  // Get values from current room & face
  cfp = &Curroomp->faces[Curface]; // pointer to current face
  cnv = cfp->num_verts;            // number of verts in current face

  // Check for portal already here
  if (cfp->portal_num != -1) {
    OutrageMessageBox("Can't add room: There is already a connection at the current room:face.");
    return;
  }

  // Get values for new room
  nfaces = cnv + 2;

  // Get a pointer to our room
  rp = CreateNewRoom(cnv * 2, nfaces, 0);
  if (rp == NULL) {
    OutrageMessageBox("Cannot add room: No free rooms.");
    return;
  }

  // Compute delta vector
  room_delta = cfp->normal * -DEFAULT_ROOM_LENGTH;

  // Set the vertices for the room
  for (i = 0; i < cnv; i++) {
    rp->verts[i] = Curroomp->verts[cfp->face_verts[cnv - 1 - i]];
    rp->verts[cnv + i] = rp->verts[i] + room_delta;
  }

  // Set the faces for the room
  InitRoomFace(&rp->faces[0], cnv);
  for (i = 0; i < cnv; i++)
    rp->faces[0].face_verts[i] = i;

  InitRoomFace(&rp->faces[1], cnv);
  for (i = 0; i < cnv; i++)
    rp->faces[1].face_verts[i] = cnv * 2 - 1 - i;

  for (i = 0; i < nfaces - 2; i++) {
    InitRoomFace(&rp->faces[i + 2], 4);
    rp->faces[i + 2].face_verts[0] = i;
    rp->faces[i + 2].face_verts[1] = i + cnv;
    rp->faces[i + 2].face_verts[2] = ((i + 1) % cnv) + cnv;
    rp->faces[i + 2].face_verts[3] = (i + 1) % cnv;
  }

#ifndef NEWEDITOR
  // Set normals & textures for each face
  for (i = 0; i < nfaces; i++) {
    if (!ComputeFaceNormal(rp, i))
      Int3(); // Bad!  Get Matt!

    // Assign arbitrary texture map
    rp->faces[i].tmap = i + 1;
  }
#else
  int texnum = Editor_state.GetCurrentTexture();

  // Set normals & textures for each face
  for (i = 0; i < nfaces; i++) {
    if (!ComputeFaceNormal(rp, i))
      Int3(); // Bad!  Get Matt!

    // Apply texture
    HTextureApplyToRoomFace(rp, i, texnum);
  }
#endif

  // Set UVs for all the faces
  AssignDefaultUVsToRoom(rp);

  // Form the portals between the rooms
  LinkRoomsSimple(Rooms, ROOMNUM(Curroomp), Curface, ROOMNUM(rp), 0);

  // Make the new room the current room
#ifndef NEWEDITOR
  Curroomp = rp;
  Curface = 1;
  Curedge = Curvert = 0;
  Curportal = -1;
#else
  Editor()->m_pLevelWnd->SetPrim(rp, 1, -1, 0, 0);
#endif

  // Set the flag
  World_changed = 1;
}

// Computes the orientation matrix for the placed room
void ComputePlacedRoomMatrix() {
  room *placedroomp;
  int placedface;
  matrix srcmat;
  vector t;

  if (Placed_room != -1) {
    placedroomp = &Rooms[Placed_room];
    placedface = Placed_room_face;
  } else {
    ASSERT(Placed_group != NULL);
    placedroomp = &Placed_group->rooms[Placed_group->attachroom];
    placedface = Placed_group->attachface;
  }

  // Compute source and destination matrices
  t = -placedroomp->faces[placedface].normal;
  vm_VectorToMatrix(&srcmat, &t, NULL, NULL);
  vm_VectorAngleToMatrix(&Placed_room_orient, &Placed_room_orient.fvec, Placed_room_angle);

  mprintf(0, "srcmat: %f %f %f\n", vm_GetMagnitude(&srcmat.fvec), vm_GetMagnitude(&srcmat.rvec),
          vm_GetMagnitude(&srcmat.uvec));
  mprintf(0, "orient: %f %f %f\n", vm_GetMagnitude(&Placed_room_orient.fvec), vm_GetMagnitude(&Placed_room_orient.rvec),
          vm_GetMagnitude(&Placed_room_orient.uvec));

  // Make sure the matrices are ok
  vm_Orthogonalize(&srcmat);
  vm_Orthogonalize(&Placed_room_orient);

  // Compute matrix to rotate src -> dest
  vm_MatrixMulTMatrix(&Placed_room_rotmat, &srcmat, &Placed_room_orient);

  mprintf(0, "rotmat: %f %f %f\n", vm_GetMagnitude(&Placed_room_rotmat.fvec), vm_GetMagnitude(&Placed_room_rotmat.rvec),
          vm_GetMagnitude(&Placed_room_rotmat.uvec));

  // Make sure the matrix is ok
  vm_Orthogonalize(&Placed_room_rotmat);
}

// Place a room for orientation before attachment
// Parameters:	baseroomp - pointer to the room in the mine to which the new room will be attached
//					baseface - the face on baseroomp to attach to
//					placed_room - the number of the room to be attached
//					placed_room_face the face on placed_room that's attached
void PlaceRoom(room *baseroomp, int baseface, int placed_room, int placed_room_face, int placed_room_door) {
  // Clear the placed group if one exists
  Placed_group = NULL;

  ASSERT(baseroomp->faces[baseface].portal_num == -1);

  room *placedroomp = &Rooms[placed_room];

  // Set globals
  Placed_room = placed_room;
  Placed_room_face = placed_room_face;
  Placed_room_orient.fvec = baseroomp->faces[baseface].normal;
  Placed_room_angle = 0;
  Placed_baseroomp = baseroomp;
  Placed_baseface = baseface;
  Placed_door = placed_room_door;

  // Compute attach points on each face
#ifndef NEWEDITOR
  ComputeCenterPointOnFace(&Placed_room_attachpoint, baseroomp, baseface);
  ComputeCenterPointOnFace(&Placed_room_origin, placedroomp, placed_room_face);
#else
  ComputeFaceBoundingCircle(&Placed_room_attachpoint, baseroomp, baseface);
  ComputeFaceBoundingCircle(&Placed_room_origin, placedroomp, placed_room_face);
#endif

  // Compute initial orientation matrix
  ComputePlacedRoomMatrix();

  // Set the flag
  State_changed = 1;
}

// Lined up a placed room.  Moves the placed room so the closest vert to basevert lines up exactly,
// and the edge from basevert to basevert+1 lines up with the corresponding edge on the placed room.
void SnapRoom(int basevert) {
  vector basecenter, attcenter;
  room *baseroomp, *attroomp;
  face *bfp, *afp;
  vector *bvp;
  int baseface, attface;
  vector baseedge, attedge;

  // Get values for the attach room
  if (Placed_room != -1) {
    attroomp = &Rooms[Placed_room];
    attface = Placed_room_face;
  } else {
    ASSERT(Placed_group != NULL);
    attroomp = &Placed_group->rooms[Placed_group->attachroom];
    attface = Placed_group->attachface;
  }

  // Set some vars
  baseroomp = Placed_baseroomp;
  baseface = Placed_baseface;
  attcenter = Placed_room_origin;
  basecenter = Placed_room_attachpoint;
  bfp = &baseroomp->faces[baseface];
  afp = &attroomp->faces[attface];
  bvp = &baseroomp->verts[bfp->face_verts[basevert]];

  // Find matching vert in attach face
  float closest_dist = FLT_MAX;
  int closest_v;
  for (int v = 0; v < afp->num_verts; v++) {
    vector rotvert;
    float dist;

    rotvert = ((attroomp->verts[afp->face_verts[v]] - attcenter) * Placed_room_rotmat) + basecenter;
    dist = vm_VectorDistance(bvp, &rotvert);

    if (dist < closest_dist) {
      closest_dist = dist;
      closest_v = v;
    }
  }

  // Compute edge vector in base room
  vm_GetNormalizedDir(&baseedge, &baseroomp->verts[bfp->face_verts[(basevert + 1) % bfp->num_verts]], bvp);

  // Compute edge vector in attach room
  vector v0 = ((attroomp->verts[afp->face_verts[closest_v]] - attcenter) * Placed_room_rotmat) + basecenter;
  vector v1 = ((attroomp->verts[afp->face_verts[(closest_v + afp->num_verts - 1) % afp->num_verts]] - attcenter) *
               Placed_room_rotmat) +
              basecenter;
  vm_GetNormalizedDir(&attedge, &v1, &v0);

  // Get angle between two edge vectors
  double dot = baseedge * attedge;
  if (dot > 1.0)
    dot = 1.0;
  double ac = acos(dot);
  float delta_ang = 32768.0 * ac / PI;

  // Get sign of angle
  vector checkv;
  vm_CrossProduct(&checkv, &baseedge, &attedge);
  if ((bfp->normal * checkv) > 0)
    delta_ang = -delta_ang;

  // Update placed room angle
  Placed_room_angle += delta_ang;
  while (Placed_room_angle < 0)
    Placed_room_angle += 65536;

  // Regenerate matrix
  ComputePlacedRoomMatrix();

  // Move the room to line up the points
  v0 = ((attroomp->verts[afp->face_verts[closest_v]] - attcenter) * Placed_room_rotmat) + basecenter;
  Placed_room_attachpoint += *bvp - v0;

  // Update view
  State_changed = 1;
}

// Attach an already-placed room
void AttachRoom() {
  vector basecenter, attcenter;
  room *baseroomp, *attroomp, *newroomp;
  int baseface, attface;

  ASSERT(Placed_room != -1);

  // Set some vars
  baseroomp = Placed_baseroomp;
  baseface = Placed_baseface;
  attroomp = &Rooms[Placed_room];
  attface = Placed_room_face;
  attcenter = Placed_room_origin;
  basecenter = Placed_room_attachpoint;

  // Get the new room
  newroomp = CreateNewRoom(attroomp->num_verts, attroomp->num_faces, 0);
  if (newroomp == NULL) {
    OutrageMessageBox("Cannot attach room: No free rooms.");
    return;
  }

  // Rotate verts, copying into new room
  for (int i = 0; i < attroomp->num_verts; i++)
    newroomp->verts[i] = ((attroomp->verts[i] - attcenter) * Placed_room_rotmat) + basecenter;

  // Copy faces to new room
  for (i = 0; i < attroomp->num_faces; i++) {
    CopyFace(&newroomp->faces[i], &attroomp->faces[i]);
#ifdef NEWEDITOR
    LevelTexIncrementTexture(attroomp->faces[i].tmap);
#endif
  }

  // Recompute normals for the faces
  if (!ResetRoomFaceNormals(newroomp))
    Int3(); // Get Matt

  // Copy other values for this room
  newroomp->flags = attroomp->flags;
  newroomp->num_portals = 0;

  // Check for terrain or mine room
  if (baseroomp == NULL) { // a terrain room

    // Flag this as an external room
    newroomp->flags |= RF_EXTERNAL;

    // Delete the attach face, which should now be facing the ground
    DeleteRoomFace(newroomp, attface);
  } else { // a mine room

    // Clip the connecting faces against each other
    if (!ClipFacePair(newroomp, attface, baseroomp, baseface)) {
      OutrageMessageBox("Error making portal -- faces probably don't overlap.");
      FreeRoom(newroomp);
      return;
    }

    // Make the two faces match exactly
    MatchPortalFaces(baseroomp, baseface, newroomp, attface);

    // Create the portals between the rooms
    LinkRoomsSimple(Rooms, ROOMNUM(baseroomp), baseface, ROOMNUM(newroomp), attface);

    // If there is a door, place it!
    if (Placed_door != -1) {
      vector room_center;
      matrix orient = ~Placed_room_rotmat;
      vector doorcenter = {0, 0, 0};

      FreeRoom(&Rooms[Placed_room]);

      room_center = ((doorcenter - attcenter) * Placed_room_rotmat) + basecenter;

      ObjCreate(OBJ_DOOR, Placed_door, newroomp - Rooms, &room_center, &orient);

      doorway *dp = DoorwayAdd(newroomp, Placed_door);

#ifdef NEWEDITOR
      LevelDoorIncrementDoorway(Placed_door);
#endif

      Placed_door = -1;
    }
  }

  // Un-place the now-attached room
  Placed_room = -1;

  // Flag the world as changed
  World_changed = 1;
}

// structure for keeping track of vertices inserted in edges (from clipping)
struct edge_insert {
  int v0, v1; // the edge that got the new vert
  int new_v;  // the new vertex
};

// List of vertices inserted in edges.  Used only during clipping.
edge_insert Edge_inserts[MAX_VERTS_PER_FACE];
int Num_edge_inserts;

// Add an insert to the edge list
void AddEdgeInsert(int v0, int v1, int new_v) {
  Edge_inserts[Num_edge_inserts].v0 = v0;
  Edge_inserts[Num_edge_inserts].v1 = v1;
  Edge_inserts[Num_edge_inserts].new_v = new_v;
  Num_edge_inserts++;
}

// Clip a polygon against one edge of another polygon
// Fills inbuf and maybe outbuf with new polygons, and writes any new verts to the vertices array
// Parameters:	nv - the number of verts in the polygon to be clipped
//					vertnums - pointer to list of vertex numbers in the polygon
//					vertices - list of vertices referred to in vertnums
//					v0,v1 - the edge we're clipping against
//					normal - the surface normal of the polygon
//					inbuf - the clipped polygon is written to this buffer
//					inv - the number of verts in inbuf is written here
//					outbuf - the new polygon created by the part of the input polygon that was
//clipped away 					onv - the number of verys in outbuf 					num_vertices - pointer to the number of verts in the vertices array
void ClipAgainstEdge(int nv, int16_t *vertnums, vertex *vertices, int *num_vertices, vector *v0, vector *v1,
                     vector *normal, int16_t *inbuf, int *inv, int16_t *outbuf, int *onv) {
  int i, prev, next, check;
  int16_t *ip = inbuf, *op = outbuf;
  vertex *curv, *prevv, *nextv;
  int inside_points = 0, outside_points = 0; // real inside/outside points, distinct from edge points

  for (i = 0, prev = nv - 1, next = 1; i < nv; i++) {

    curv = &vertices[vertnums[i]];

    // Find out where point lies
    check = CheckPointAgainstEdge(&curv->vec, v0, v1, normal);
    if (check == 0) { // Current vertex is on edge

      // Add to both inside & outside lists
      *op++ = vertnums[i];
      *ip++ = vertnums[i];
    } else if (check == -1) { // Current vertex is outside
      int check2;

      prevv = &vertices[vertnums[prev]];
      nextv = &vertices[vertnums[next]];

      // Clip edge w/ previous vertex
      check2 = CheckPointAgainstEdge(&prevv->vec, v0, v1, normal);
      if (check2 == 1) { // prev inside, so clip
        ClipEdge(normal, prevv, curv, v0, v1, &vertices[*num_vertices]);
        AddEdgeInsert(vertnums[prev], vertnums[i], *num_vertices);
        *op++ = *ip++ = (*num_vertices)++;
      }

      // Add current vertex to outside polygon
      *op++ = vertnums[i];
      outside_points++;

      // Clip edge w/ next vertex
      check2 = CheckPointAgainstEdge(&nextv->vec, v0, v1, normal);
      if (check2 == 1) { // next inside, so clip
        ClipEdge(normal, curv, nextv, v0, v1, &vertices[*num_vertices]);
        AddEdgeInsert(vertnums[i], vertnums[next], *num_vertices);
        *op++ = *ip++ = (*num_vertices)++;
      }
    } else { // Current vertex is inside
      ASSERT(check == 1);

      // Add current vertex to inside polygon
      *ip++ = vertnums[i];
      inside_points++;
    }

    prev = i;
    if (++next == nv)
      next = 0;
  }

  // Set number of verts for return.  If no real inside or outside points, then don't count edge points
  *inv = inside_points ? (ip - inbuf) : 0;
  *onv = outside_points ? (op - outbuf) : 0;
}

// Adds a new vertex to all instances of a given edge
void AddVertToAllEdges(room *rp, int v0, int v1, int new_v) {
  face *fp;
  int f, v;

  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
    for (v = 0; v < fp->num_verts; v++) {
      if (((fp->face_verts[v] == v0) && (fp->face_verts[(v + 1) % fp->num_verts] == v1)) ||
          ((fp->face_verts[v] == v1) && (fp->face_verts[(v + 1) % fp->num_verts] == v0)))
        AddVertToFace(rp, f, new_v, v);
    }
  }
}

// Adds a new point to all instances of a given edge
// First adds the point to the room (or finds it there), then calls AddVertToAllEdges()
void AddPointToAllEdges(room *rp, int v0, int v1, vector *new_v) {
  int newvertnum = RoomAddVertices(rp, 1);

  rp->verts[newvertnum] = *new_v;

  AddVertToAllEdges(rp, v0, v1, newvertnum);
}

// Clips a face against another.  Produces one polygon that is the intersection of the two input
// faces, and zero or more extra polygons, which are parts of the input face outside the clipping face.
// The input face is replaced by the clipped face, and new faces (formed by the parts of the input
// face outside the clip-against face) are added to the end of the room's facelist.
// This routine assumes that part or all of the being-clipped face is inside the clip-against face
// Parameters:	arp - the room with the face that is being changed
//					afacenum - the face being changed
//					brp - the room with the face we're clipping against
//					bfacenum - the face we're clipping against
// Returns:		true if the clip was ok, false if there was an error
bool ClipFace(room *arp, int afacenum, room *brp, int bfacenum) {
  face *afp = &arp->faces[afacenum];
  face *bfp = &brp->faces[bfacenum];
  int edgenum;
  int16_t vbuf0[MAX_VERTS_PER_FACE], vbuf1[MAX_VERTS_PER_FACE];
  int16_t newface_verts[MAX_VERTS_PER_FACE][MAX_VERTS_PER_FACE];
  int newface_nvs[MAX_VERTS_PER_FACE];
  vertex newverts[MAX_VERTS_PER_FACE];
  int newvertnums[MAX_VERTS_PER_FACE];
  int num_newverts;
  int num_newfaces = 0;
  int16_t *src, *dest;
  int nv;
  int i;

  // Init some stuff
  nv = afp->num_verts;
  src = vbuf0;
  dest = vbuf1;

  Num_edge_inserts = 0;

  // copy our vertices into one buffer
  for (i = 0; i < nv; i++) {
    newverts[i].vec = arp->verts[afp->face_verts[i]];
    newverts[i].uvl = afp->face_uvls[i];
    newvertnums[i] = afp->face_verts[i];
    src[i] = i;
  }
  num_newverts = nv;

  // Clip our polygon against each edge
  for (edgenum = 0; edgenum < bfp->num_verts; edgenum++) {
    vector *v0, *v1;
    int16_t *outbuf = newface_verts[num_newfaces];
    int *onv = &newface_nvs[num_newfaces];

    v0 = &brp->verts[bfp->face_verts[(bfp->num_verts - edgenum) % bfp->num_verts]];
    v1 = &brp->verts[bfp->face_verts[bfp->num_verts - edgenum - 1]];

    ClipAgainstEdge(nv, src, newverts, &num_newverts, v0, v1, &afp->normal, dest, &nv, outbuf, onv);

    if (nv <= 2) // no new face -- faces must not overlap
      return 0;

    src = dest;
    dest = (src == vbuf0) ? vbuf1 : vbuf0;

    if (newface_nvs[num_newfaces]) // is there a new face?
      num_newfaces++;              //..yes, increment counter
  }

  // Now we have the clipped face and the other new faces
  // Replace the old face, and add the new faces
  int first_new_vert, first_new_face;
  face *fp;

  // Allocate space for the new verts
  first_new_vert = RoomAddVertices(arp, num_newverts - afp->num_verts);

  // Copy new vertices into room & get real vert numbers
  for (i = 0; i < num_newverts - afp->num_verts; i++) {
    arp->verts[first_new_vert + i] = newverts[afp->num_verts + i].vec;
    newvertnums[afp->num_verts + i] = first_new_vert + i;
  }

  // Replace the input face with the clipped face
  ReInitRoomFace(afp, nv);
  for (i = 0; i < nv; i++) {
    afp->face_verts[i] = newvertnums[src[i]];
    afp->face_uvls[i] = newverts[src[i]].uvl;
  }
  if (!ComputeFaceNormal(arp, afacenum))
    Int3(); // Get Matt

  // Allocate space for the new faces
  first_new_face = RoomAddFaces(arp, num_newfaces);

  // Copy data for new faces (the outside faces)
  for (i = 0; i < num_newfaces; i++) {
    fp = &arp->faces[first_new_face + i];
    InitRoomFace(fp, newface_nvs[i]);
    for (int j = 0; j < newface_nvs[i]; j++) {
      fp->face_verts[j] = newvertnums[newface_verts[i][j]];
      fp->face_uvls[j] = newverts[newface_verts[i][j]].uvl;
    }
    if (!ComputeFaceNormal(arp, first_new_face + i))
      Int3(); // Get Matt
#ifndef NEWEDITOR
    fp->tmap = arp->faces[afacenum].tmap;
#else
    // Apply texture
    HTextureApplyToRoomFace(arp, first_new_face + i, arp->faces[afacenum].tmap);
#endif
    CopyFaceFlags(fp, &arp->faces[afacenum]);
  }

  // Add new verts to edges
  for (i = 0; i < Num_edge_inserts; i++) {
    int v0, v1, new_v;
    v0 = newvertnums[Edge_inserts[i].v0];
    v1 = newvertnums[Edge_inserts[i].v1];
    new_v = newvertnums[Edge_inserts[i].new_v];

    AddVertToAllEdges(arp, v0, v1, new_v);
  }

  // Done!
  return 1;
}

// Adds a point to a face
// Parameters:	rp,facenum - the face we're adding the point to
//					vertindex - the position in the face's vertex list at which to add the point
//					vp - the point to add
void AddPointToFace(room *rp, int facenum, int vertindex, vector *vp) {
  face *fp = &rp->faces[facenum];
  int old_verts[MAX_VERTS_PER_FACE];
  roomUVL old_uvls[MAX_VERTS_PER_FACE];
  int t;

  // Add the new point to the room
  int newvertnum = RoomAddVertices(rp, 1);
  rp->verts[newvertnum] = *vp;

  // Make copy of old verts
  for (t = 0; t < fp->num_verts; t++) {
    old_verts[t] = fp->face_verts[t];
    old_uvls[t] = fp->face_uvls[t];
  }

  // Allocate for new verts
  ReInitRoomFace(fp, fp->num_verts + 1);

  // Copy old verts
  for (t = 0; t < vertindex; t++) {
    fp->face_verts[t] = old_verts[t];
    fp->face_uvls[t] = old_uvls[t];
  }
  fp->face_verts[t++] = newvertnum;
  // fp0->face_uvls[t] = ??
  for (; t < fp->num_verts; t++) {
    fp->face_verts[t] = old_verts[t - 1];
    fp->face_uvls[t] = old_uvls[t - 1];
  }
}

// Deletes a point from a face
// Parameters:	rp,facenum - the face we're deleting the point from
//					vertindex - the vertex to delete
void DeletePointFromFace(room *rp, int facenum, int vertindex) {
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
  ReInitRoomFace(fp, fp->num_verts - 1);

  // Copy old verts
  for (t = 0; t < vertindex; t++) {
    fp->face_verts[t] = old_verts[t];
    fp->face_uvls[t] = old_uvls[t];
  }
  for (; t < fp->num_verts; t++) {
    fp->face_verts[t] = old_verts[t + 1];
    fp->face_uvls[t] = old_uvls[t + 1];
  }

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

// Takes two faces which are going to be made into a portal and makes them match exactly
// Alternatively, checks if the two faces can be matched
// After this function the two faces will have exactly the same vertices
// Parameters:	rp0,facenum0 - one of the faces
//					rp1,facenum1 - the other face
//					check_only - if set, doesn't change anything; just checks the faces
// Returns the number of points added to the faces
// If just_checking set, returns true if faces match, else false
int MatchPortalFaces(room *rp0, int facenum0, room *rp1, int facenum1, bool check_only) {
  face *fp0 = &rp0->faces[facenum0];
  face *fp1 = &rp1->faces[facenum1];
  vector *v0, *v1, *prev_v0, *prev_v1;
  int n0, n1, i, j, prev_vn0, prev_vn1, max_nv;
  int points_added = 0;

check_faces:;

  // First, find one point in common
  for (i = 0; i < fp0->num_verts; i++) {
    for (j = 0; j < fp1->num_verts; j++)
      if (PointsAreSame(&rp0->verts[fp0->face_verts[i]], &rp1->verts[fp1->face_verts[j]]))
        break;
    if (j < fp1->num_verts)
      break;
  }
  if (i >= fp0->num_verts) {
    if (!check_only)
      Int3(); // Counldn't find common point!  This is very bad.  Get Matt.
    return 0; // no match
  }

  prev_vn0 = fp0->face_verts[i];
  prev_vn1 = fp1->face_verts[j];
  prev_v0 = &rp0->verts[prev_vn0];
  prev_v1 = &rp1->verts[prev_vn1];

  // Make starting points identical
  if (!check_only)
    *prev_v0 = *prev_v1;

  // Use the larger number of vert
  max_nv = __max(fp0->num_verts, fp1->num_verts);

  // Trace through faces, adding points where needed
  for (n0 = n1 = 1; n0 < max_nv && n1 < max_nv; n0++, n1++) {
    int vn0, vn1;

  recheck:;

    vn0 = fp0->face_verts[(i + n0) % fp0->num_verts];
    vn1 = fp1->face_verts[(j - n1 + fp1->num_verts) % fp1->num_verts];

    v0 = &rp0->verts[vn0];
    v1 = &rp1->verts[vn1];

    if (PointsAreSame(v0, v1)) { // Points are at least very close.
      if (!check_only)
        *v0 = *v1; // Make the points identical
    } else {       // The points are not the same, so we check for an extra (colinear) point

      float d0, d1;

      // One of these points should lie along the edge of the other. Find which is which
      d0 = vm_VectorDistance(v0, prev_v0);
      d1 = vm_VectorDistance(v1, prev_v1);

      if (d0 > d1) { // Point 1 is presumably on the edge prev_v0 -> v0

        // Make sure the point is actually on the edge
        if (CheckPointAgainstEdge(v1, prev_v0, v0, &fp0->normal)) {
          if (check_only)
            return 0;
          Int3(); // point isn't on edge!  Bad!  Get Matt!
        } else {
          if (!check_only) {

            // Add the point
            AddPointToAllEdges(rp0, prev_vn0, vn0, v1);
            points_added++;
          } else {
            n1++; // skip edge point & resume checking
            goto recheck;
          }
        }
      } else { // Point 0 is presumably on the edge prev_v1 -> v1

        // Make sure the point is actually on the edge
        if (CheckPointAgainstEdge(v0, prev_v1, v1, &fp1->normal)) {
          if (check_only)
            return 0;
          Int3(); // point isn't on edge!  Bad!  Get Matt!
        } else {

          if (!check_only) {
            // Add the point
            AddPointToAllEdges(rp1, prev_vn1, vn1, v0);
            points_added++;
          } else {
            n0++; // skip edge point & resume checking
            goto recheck;
          }
        }
      }

      // Start check again
      if (!check_only)
        goto check_faces;
    }

    prev_vn0 = vn0;
    prev_vn1 = vn1;

    prev_v0 = v0;
    prev_v1 = v1;
  }

  if (check_only)
    return 1; // no errors found, so faces ok

  ASSERT(fp0->num_verts == fp1->num_verts); // Get Matt!

  return points_added;
}

// Clips a pair of faces against each other.
// Produces one polygon in each face that is the intersection of the two input faces,
// and zero or more extra polygons, which are parts of the input faces outside the clipping faces.
// The input faces are replaced by the clipped faces, and new faces (formed by the parts of the input
// face outside the clip-against face) are added to the end of the room's facelist.
// This routine assumes that part or all of the being-clipped face is inside the clip-against face
// Parameters:	rp0,face0 - the first room:face
//					rp1,face1 - the second room:face
// Returns:		true if the clip was ok, false if there was an error
bool ClipFacePair(room *rp0, int face0, room *rp1, int face1) {
  // Clip each face aginst the other
  return (ClipFace(rp0, face0, rp1, face1) && ClipFace(rp1, face1, rp0, face0));
}

// Creates a new bridge room connecting two rooms
// Parameters:	attroomp,attface - one end of the new room
//					baseroom,baseface - the other end of the new room
// The new room is created by extruding from attroom/attface
void BuildBridge(room *attroomp, int attface, room *baseroomp, int baseface) {
  room *newroomp;
  face *afp, *bfp;
  int nv, nfaces;
  vector delta_vec, bc, ac;
  vector *basevert; // a vertex on the base face
  int i;
  float cos, dist;

  // Check that the two faces don't already have portals
  if (attroomp->faces[attface].portal_num != -1) {
    OutrageMessageBox("Cannot build bridge: There is already a portal at %d:%d", ROOMNUM(attroomp), attface);
    return;
  }
  if (baseroomp->faces[baseface].portal_num != -1) {
    OutrageMessageBox("Cannot build bridge: There is already a portal at %d:%d", ROOMNUM(baseroomp), baseface);
    return;
  }

  // Get values from current room & face
  afp = &attroomp->faces[attface];   // pointer to attach face
  bfp = &baseroomp->faces[baseface]; // pointer to base face
  nv = afp->num_verts;               // number of verts in attach face
  nfaces = nv + 2;                   // number of faces in new room

  // Make sure all points on each face are on the front of the other face
  vector tnorm = -afp->normal;
  int t = CheckFaceToPlane(baseroomp, baseface, &attroomp->verts[afp->face_verts[0]], &tnorm);
  if (t != -1) {
    OutrageMessageBox("Can't build bridge: Vertex %d on %d:%d is behind %d:%d", t, ROOMNUM(baseroomp), baseface,
                      ROOMNUM(attroomp), attface);
    return;
  }
  tnorm = -bfp->normal;
  t = CheckFaceToPlane(attroomp, attface, &baseroomp->verts[bfp->face_verts[0]], &tnorm);
  if (t != -1) {
    OutrageMessageBox("Can't build bridge: Vertex %d on %d:%d is behind %d:%d", t, ROOMNUM(attroomp), attface,
                      ROOMNUM(baseroomp), baseface);
    return;
  }

  // Compute normalized vector from attach face to base face
#ifndef NEWEDITOR
  ComputeCenterPointOnFace(&bc, baseroomp, baseface);
  ComputeCenterPointOnFace(&ac, attroomp, attface);
#else
  ComputeFaceBoundingCircle(&bc, baseroomp, baseface);
  ComputeFaceBoundingCircle(&ac, attroomp, attface);
#endif
  dist = vm_GetNormalizedDir(&delta_vec, &bc, &ac);

  // Compute the cosine of the angle between our vector and the normal of the base face
  cos = delta_vec * bfp->normal;

  // Get a pointer to a vertex on the base face
  basevert = &baseroomp->verts[bfp->face_verts[0]];

  // Get a pointer to our room
  newroomp = CreateNewRoom(nv * 2, nfaces, 0);
  if (newroomp == NULL) {
    OutrageMessageBox("Cannot build bridge: No free rooms.");
    return;
  }

  // Create new vertices in the plane of the base face
  for (i = 0; i < nv; i++) {
    float dist;

    // Copy from att face to new room
    newroomp->verts[i] = attroomp->verts[afp->face_verts[nv - 1 - i]];

    // Get distance from base face to this vertex
    dist = ((*basevert - newroomp->verts[i]) * bfp->normal) / cos;

    // Get the new vert
    newroomp->verts[nv + i] = newroomp->verts[i] + (delta_vec * dist);
  }

  // Set the faces for the room
  InitRoomFace(&newroomp->faces[0], nv);
  for (i = 0; i < nv; i++)
    newroomp->faces[0].face_verts[i] = i;

  InitRoomFace(&newroomp->faces[1], nv);
  for (i = 0; i < nv; i++)
    newroomp->faces[1].face_verts[i] = nv * 2 - 1 - i;

  for (i = 0; i < nfaces - 2; i++) {
    InitRoomFace(&newroomp->faces[i + 2], 4);
    newroomp->faces[i + 2].face_verts[0] = i;
    newroomp->faces[i + 2].face_verts[1] = i + nv;
    newroomp->faces[i + 2].face_verts[2] = ((i + 1) % nv) + nv;
    newroomp->faces[i + 2].face_verts[3] = (i + 1) % nv;
  }

  // Set normals
  if (!ResetRoomFaceNormals(newroomp))
    Int3(); // Get Matt

    // Set textures
#ifndef NEWEDITOR
  for (i = 0; i < nfaces; i++)
    newroomp->faces[i].tmap = i + 1;
#else
  int texnum = Editor_state.GetCurrentTexture();
  // Apply texture
  for (i = 0; i < nfaces; i++)
    HTextureApplyToRoomFace(newroomp, i, texnum);
#endif

  // Assign UVs
  AssignDefaultUVsToRoom(newroomp);

  // Connect the new room to the attach room
  LinkRoomsSimple(Rooms, ROOMNUM(attroomp), attface, ROOMNUM(newroomp), 0);

  // Clip the connecting faces against each other
  t = ClipFacePair(newroomp, 1, baseroomp, baseface);
  ASSERT(t != 0);

  // Make the two faces match exactly
  MatchPortalFaces(baseroomp, baseface, newroomp, 1);

  // Connect the new room to the base room
  LinkRoomsSimple(Rooms, ROOMNUM(baseroomp), baseface, ROOMNUM(newroomp), 1);

  // Set Changed flag
  World_changed = 1;
}

#define JOIN_EPSILON 0.01

// Connects two rooms by changing the shape of one room to attach to the other
// Pretty similar to BuildBridge(), but doesn't create a new room
// Parameters:	attroomp,attface - one end of the new room
//					baseroom,baseface - the other end of the new room
void JoinRooms(room *attroomp, int attface, room *baseroomp, int baseface) {
  face *afp, *bfp;
  int nv, nfaces, t;
  vector delta_vec;
  vector *basevert; // a vertex on the base face
  int i;
  float cos;
  vector save_verts[MAX_VERTS_PER_FACE]; // save verts for face in case we bail

  // Check that the two faces don't already have portals
  if (attroomp->faces[attface].portal_num != -1) {
    OutrageMessageBox("Cannot join: There is already a portal at %d:%d", ROOMNUM(attroomp), attface);
    return;
  }
  if (baseroomp->faces[baseface].portal_num != -1) {
    OutrageMessageBox("Cannot join: There is already a portal at %d:%d", ROOMNUM(baseroomp), baseface);
    return;
  }

  // Get values from current room & face
  afp = &attroomp->faces[attface];   // pointer to attach face
  bfp = &baseroomp->faces[baseface]; // pointer to base face
  nv = afp->num_verts;               // number of verts in attach face
  nfaces = nv + 2;                   // number of faces in new room

  // Get a pointer to a vertex on the base face
  basevert = &baseroomp->verts[bfp->face_verts[0]];

  // Make sure all points on the attach face are on the front of the base face
  // We could probably take this check out and catch the problem when we're moving the points
  vector tnorm = -bfp->normal;
  t = CheckFaceToPlane(attroomp, attface, basevert, &tnorm);
  if (t != -1) {
    if (OutrageMessageBox(
            MBOX_YESNO,
            "One or more points on the attach face are behind the base face.\nDo you still want to join?") != IDYES) {
      EditorStatus("Join aborted.");
      return;
    }
  }

  // Make a list of all verts in the attach room that are in a portal
  int portal_list[MAX_VERTS_PER_ROOM];
  int num_portal_verts;
  num_portal_verts = BuildListOfPortalVerts(attroomp, portal_list);

  // Save old verts
  for (i = 0; i < nv; i++)
    save_verts[i] = attroomp->verts[afp->face_verts[i]];

  int answer = OutrageMessageBox(MBOX_YESNO, "Do you want to connect to the center of the base face?\n\n"
                                             "Answer NO to extrude straight from the current face.");

  // Compute normalized vector from attach face to base face.
  // This is the direction in which we will move the attach face
  if (answer == IDYES) { // extrude toward the center of the base face
    vector bc, ac;
#ifndef NEWEDITOR
    ComputeCenterPointOnFace(&bc, baseroomp, baseface);
    ComputeCenterPointOnFace(&ac, attroomp, attface);
#else
    ComputeFaceBoundingCircle(&bc, baseroomp, baseface);
    ComputeFaceBoundingCircle(&ac, attroomp, attface);
#endif
    vm_GetNormalizedDir(&delta_vec, &bc, &ac);
  } else { // extrude straight from attach face
    delta_vec = afp->normal;
  }

  // Compute the cosine of the angle between our vector and the normal of the base face
  cos = delta_vec * bfp->normal;

  // If cos is zero, two center points are the same, so no move
  if (fabs(cos) < JOIN_EPSILON)
    goto no_move_points;

  // Move the verts on the attach face to lie in the plane as the base face
  for (i = 0; i < nv; i++) {
    vector *vp = &attroomp->verts[afp->face_verts[i]];
    float dist;

    // Get distance from base face to this vertex
    dist = ((*basevert - *vp) * bfp->normal) / cos;

    // If we're moving the point, make sure it's not part of a portal
    if (fabs(dist) > POINT_TO_PLANE_EPSILON) {

      // Look through list of portal verts for this vert
      for (t = 0; t < num_portal_verts; t++)
        if (portal_list[t] == afp->face_verts[i]) { // Vert is in a portal.  Abort!
          OutrageMessageBox("Can't form joint because vertex %d on %d:%d is shared with a portal.\n\nTry doing the "
                            "join the other way, or using the Bridge function.",
                            i, ROOMNUM(attroomp), attface);
          goto abort_join;
        }

      // Move the vert
      *vp += (delta_vec * dist);
    }
  }

  // Recompute the normals in the room
  if (!ResetRoomFaceNormals(attroomp))
    Int3(); // Get Matt

  // What about the uvs for the faces that changed?

no_move_points:;

  // Clip the connecting faces against each other
  if (!ClipFacePair(attroomp, attface, baseroomp, baseface)) {
    OutrageMessageBox("Error making portal -- faces probably don't overlap.");

  abort_join:;

    // Restore old verts
    for (i = 0; i < nv; i++)
      attroomp->verts[afp->face_verts[i]] = save_verts[i];

    // Recompute the normals in the room
    if (!ResetRoomFaceNormals(attroomp))
      Int3(); // Get Matt

    return;
  }

  // Make the two faces match exactly
  MatchPortalFaces(baseroomp, baseface, attroomp, attface);

  // Create the portals between the rooms
  LinkRoomsSimple(Rooms, ROOMNUM(baseroomp), baseface, ROOMNUM(attroomp), attface);

  // Set Changed flag
  World_changed = 1;
}

// Connects two rooms if they already match up exactly
// Parameters:	attroomp,attface - one end of the new room
//					baseroom,baseface - the other end of the new room
void JoinRoomsExact(room *attroomp, int attface, room *baseroomp, int baseface) {
  // Check that the two faces don't already have portals
  if (attroomp->faces[attface].portal_num != -1) {
    OutrageMessageBox("Cannot join: There is already a portal at %d:%d", ROOMNUM(attroomp), attface);
    return;
  }
  if (baseroomp->faces[baseface].portal_num != -1) {
    OutrageMessageBox("Cannot join: There is already a portal at %d:%d", ROOMNUM(baseroomp), baseface);
    return;
  }

  // Check if we can do an exact match
  if (!MatchPortalFaces(baseroomp, baseface, attroomp, attface, 1)) {
    OutrageMessageBox("Cannot do exact join: These faces do not match");
    return;
  }

  // Make the two faces match exactly
  MatchPortalFaces(baseroomp, baseface, attroomp, attface);

  // Create the portals between the rooms
  LinkRoomsSimple(Rooms, ROOMNUM(baseroomp), baseface, ROOMNUM(attroomp), attface);

  // Set Changed flag
  World_changed = 1;
}

bool FaceIsPlanar(int nv, int16_t *face_verts, vector *normal, vector *verts);

// Combine two faces, if they can be combined
// Parameters:	rp - the room the faces are in
//					face0,face1 - the two faces
// Returns:		true if the faces were combined, else false
// Note: The UV coordinates of the new face are derrived from face0
bool CombineFaces(room *rp, int face0, int face1) {
  face *fp0 = &rp->faces[face0], *fp1 = &rp->faces[face1];
  int nv0 = fp0->num_verts, nv1 = fp1->num_verts;
  int v0, v1;
  int16_t vertlist[MAX_VERTS_PER_FACE];
  roomUVL uvllist[MAX_VERTS_PER_FACE];
  int i, nv;
  int first0, first1, n0, n1;

  ASSERT(face0 != face1);

  // Check for portals
  if ((fp0->portal_num != -1) || (fp1->portal_num != -1)) {
#ifndef NEWEDITOR
    SetErrorMessage(
        "You cannot combine portal faces.\n\nMattT will add this functionality if you need it.  Bug him about it.");
#else
    SetErrorMessage("You cannot combine portal faces.");
#endif
    return 0;
  }

  // Make sure faces share an edge
  if (!FindSharedEdge(fp0, fp1, &v0, &v1)) {
#ifdef NEWEDITOR
    if (ned_FindSharedEdge(fp0, fp1, &v0, &v1))
      SetErrorMessage("The face normals point in opposite directions.");
    else
#endif
      SetErrorMessage("The faces do not share an edge.");
    return 0;
  }

  // Get indices for first & last points in each face.  One shared point is copied with each face.
  first0 = v0 + 1;
  n0 = nv0 - 1;
  first1 = v1 + 1;
  n1 = nv1 - 1;

  // See if faces share additional edges
  while (1) { // check forward on face0, backward on face1
    int check0 = (first0 + 1) % nv0, check1 = (first1 + n1 - 1) % nv1;

    if (fp0->face_verts[check0] != fp1->face_verts[check1])
      break;

    first0++;
    n0--;
    n1--;
  }
  while (1) { // check forward on face1, backward on face0
    int check1 = (first1 + 1) % nv1, check0 = (first0 + n0 - 1) % nv0;

    if (fp0->face_verts[check0] != fp1->face_verts[check1])
      break;

    first1++;
    n1--;
    n0--;
  }

  // Build list of verts for new face
  nv = 0;
  for (i = 0; i < n0; i++) { // Add points from first face
    vertlist[nv] = fp0->face_verts[(first0 + i) % nv0];
    uvllist[nv] = fp0->face_uvls[(first0 + i) % nv0];
    nv++;
  }
  for (i = 0; i < n1; i++) { // Add points from second face
    vertlist[nv] = fp1->face_verts[(first1 + i) % nv1];
    uvllist[nv] = fp1->face_uvls[(first1 + i) % nv1];
    nv++;
  }

  // Calculate new normal
  vector new_normal;
  ComputeNormal(&new_normal, nv, vertlist, rp->verts);

  // Check if new face is planar
  if (!FaceIsPlanar(nv, vertlist, &new_normal, rp->verts)) {
    SetErrorMessage("The new face would not be planar.");
    return 0;
  }

  // Check if new face is convex
  int t;
  if ((t = CheckFaceConcavity(nv, vertlist, &new_normal, rp->verts)) != -1) {
    SetErrorMessage("The new face would be concave (at vertex %d).", vertlist[t]);
    return 0;
  }

  // Reset face0 for new verts
  ReInitRoomFace(fp0, nv);

  // Copy into new face
  for (i = 0; i < nv; i++) {
    fp0->face_verts[i] = vertlist[i];
    fp0->face_uvls[i] = uvllist[i];
  }

  // Set new normal
  fp0->normal = new_normal;

  // Reassign uvls in face
  AssignUVsToFace(rp, face0, &fp0->face_uvls[0], &fp0->face_uvls[1], 0, 1);

  // Delete the old face
  DeleteRoomFace(rp, face1);

  // Set flag
  World_changed = 1;

  // Everything's ok
  return 1;
}

// Deletes the given room from the mine
void DeleteRoomFromMine(room *rp) {
  int i, p;

  // See if this room is linked to the terrain
  for (p = 0; p < rp->num_portals; p++) {
    portal *pp = &rp->portals[p];
    if (pp->croom == -1) {
      OutrageMessageBox("You can't delete a room that attaches to the terrain.  Detach the room before deleting.");
      return;
    }
  }

  // Check if player or viewer object in this room
  for (i = rp->objects; i != -1; i = Objects[i].next) {

    // Is this the player object?
    if (i == OBJNUM(Player_object)) {
      OutrageMessageBox("You can't delete the room with the player in it.");
      return;
    }

#ifndef NEWEDITOR
    // Is this the viewer object?
    if (i == OBJNUM(Viewer_object)) { // Try to find another viewer
      int objnum = FindNextViewerObject(Viewer_object->id + 1, -1);
      if (objnum == OBJNUM(Viewer_object)) {
        OutrageMessageBox("You can't delete the room with the only viewer in it.");
        return;
      } else
        SelectNextViewer();
    }
#endif
  }

  //	count the number of rooms used. if only one, don't delete it.
  for (i = 0; i <= Highest_room_index; i++)
    if (Rooms[i].used && (i != ROOMNUM(rp)))
      break;
  if (i > Highest_room_index) {
    OutrageMessageBox("You can't delete the only room in the mine.");
    return;
  }

  // If this is current room, set new current room
  if (rp == Curroomp) {
    room *newroomp = NULL;

    // Look for connected room
    for (p = 0; p < rp->num_portals; p++)
      if (rp->portals[p].croom != -1) {
        newroomp = &Rooms[rp->portals[0].croom];
        break;
      }

    // If didn't find connected room, look for any room
    if (newroomp == NULL) {
      for (i = 0; i <= Highest_room_index; i++) {
        if (Rooms[i].used && (i != ROOMNUM(rp))) {
          newroomp = &Rooms[i];
          break;
        }
      }
    }

    ASSERT(newroomp != NULL);

#ifndef NEWEDITOR
    Curroomp = newroomp;
    Curface = Curedge = Curvert = 0;
    Curportal = -1;
#else
    Editor()->m_pLevelWnd->SetPrim(newroomp, 0, -1, 0, 0);
#endif

    EditorStatus("Current room set to %d.", ROOMNUM(Curroomp));
  }

  // Delete connections
  while (rp->num_portals) {
    portal *pp = &rp->portals[0];
    ASSERT(pp->croom != -1);
    DeleteRoomPortal(&Rooms[pp->croom], pp->cportal);
    DeleteRoomPortal(rp, 0);
  }

  // If this is marked room, clear marked room
  if (Markedroomp == rp)
    Markedroomp = NULL;

  // Free the objects in this room
  for (i = rp->objects; i != -1; i = Objects[i].next) {
#ifdef NEWEDITOR
    if (IS_GENERIC(Objects[i].type))
      LevelObjDecrementObject(Objects[i].id);
    else if (Objects[i].type == OBJ_DOOR) {
      ASSERT(rp->flags & RF_DOOR);
      LevelDoorDecrementDoorway(Objects[i].id);
    }
#endif
    ObjDelete(i);
  }

#ifdef NEWEDITOR
  // Unmark the textures in this room
  for (i = 0; i < rp->num_faces; i++)
    LevelTexDecrementTexture(rp->faces[i].tmap);
#endif

  // Delete any triggers in this room
  face *fp;
  for (i = 0, fp = rp->faces; i < rp->num_faces; fp++, i++)
    if (fp->flags & FF_HAS_TRIGGER)
      DeleteTrigger(ROOMNUM(rp), i);

  // Remove this room from the selected list (if there)
  RemoveRoomFromSelectedList(ROOMNUM(rp));

  // Free up the room
  FreeRoom(rp);
}

#define DROP_ROOM_OFFSET 20.0

// Places a room a short distance from the specified room & face
// The new room is not attached to anything
// Parameters:	baseroomp,baseface - the new room is dropped off of this face
//					droproom_num - the room to be dropped
void DropRoom(room *baseroomp, int baseface, int droproom_num) {
  int roomnum;
  room *newroomp;
  vector oldcenter, facecenter, newcenter, offset;
  float rad;

  // Create a new room
  roomnum = GetFreeRoom(0);
  if (roomnum == -1) {
    OutrageMessageBox("Cannot drop room: No free rooms.");
    return;
  }
  newroomp = &Rooms[roomnum];

  // Copy data to new room
  CopyRoom(newroomp, &Rooms[droproom_num]);

  // Compute offset
  rad = ComputeRoomBoundingSphere(&oldcenter, newroomp);
#ifndef NEWEDITOR
  ComputeCenterPointOnFace(&facecenter, baseroomp, baseface);
#else
  ComputeFaceBoundingCircle(&facecenter, baseroomp, baseface);
#endif
  newcenter = facecenter - (baseroomp->faces[baseface].normal * (rad + DROP_ROOM_OFFSET));
  offset = newcenter - oldcenter;

  // Add in offset to all the points
  for (int i = 0; i < newroomp->num_verts; i++)
    newroomp->verts[i] += offset;

    // Set current room to new room
#ifndef NEWEDITOR
  Curroomp = newroomp;
  Curface = Curedge = Curvert = 0;
  Curportal = -1;
#else
  Editor()->m_pLevelWnd->SetPrim(newroomp, 0, -1, 0, 0);
#endif

  // We're done
  World_changed = 1;
}

// Place a room on the terrain for orientation before attachment
// Parameters:	cellnum - the cell where the room is being placed
//					placed_room - the number of the room to be attached
//					placed_room_face the face on placed_room that's attached
void PlaceExternalRoom(int cellnum, int placed_room, int placed_room_face, bool align_to_terrain) {
  room *placedroomp = &Rooms[placed_room];

  // Clear the placed group if one exists
  Placed_group = NULL;

  // Clear the placed door if one exists
  if (Placed_door != -1) {
    ASSERT(Placed_room != -1);
    FreeRoom(&Rooms[Placed_room]);
    Placed_door = Placed_door = -1;
  }

  // Set globals
  Placed_room = placed_room;
  Placed_room_face = placed_room_face;
  Placed_room_angle = 0;
  Placed_baseroomp = NULL;

  if (align_to_terrain)
    Placed_room_orient.fvec = TerrainNormals[MAX_TERRAIN_LOD - 1][cellnum].normal1;
  else
    Placed_room_orient.fvec = Identity_matrix.uvec;

  // Compute attach point on terrain
  ComputeTerrainSegmentCenter(&Placed_room_attachpoint, cellnum);

  // Compute attach points on each face
#ifndef NEWEDITOR
  ComputeCenterPointOnFace(&Placed_room_origin, placedroomp, placed_room_face);
#else
  ComputeFaceBoundingCircle(&Placed_room_origin, placedroomp, placed_room_face);
#endif

  // Compute initial orientation matrix
  ComputePlacedRoomMatrix();

  // Set the flag
  State_changed = 1;
}

// Find all the matching faces between two rooms and join them
// Returns the number of new portals created
int JoinAllMatchingFaces(room *rp0, room *rp1) {
  face *fp0, *fp1;
  int f0, f1;
  int join_count = 0;

  // Check each face in room 0 against each in room 1
  for (f0 = 0, fp0 = rp0->faces; f0 < rp0->num_faces; f0++, fp0++) {

    // Check if face 0 is already part of portal
    if (fp0->portal_num != -1)
      continue;

    // Check current face against all faces in room 1
    for (f1 = 0, fp1 = rp1->faces; f1 < rp1->num_faces; f1++, fp1++) {

      // Check if face 1 is already part of portal
      if (fp1->portal_num != -1)
        continue;

      // First check if faces have same number of verts
      // This used to check if the normals were the same, but I decided that was bad. -MT, 3/30/99
      if ((fp0->num_verts == fp1->num_verts)) {
        int i, j, n;

        // Find one point in common
        for (i = 0; i < fp0->num_verts; i++) {
          for (j = 0; j < fp1->num_verts; j++)
            if (PointsAreSame(&rp0->verts[fp0->face_verts[i]], &rp1->verts[fp1->face_verts[j]]))
              break;
          if (j < fp1->num_verts)
            break;
        }
        if (i >= fp0->num_verts) // Couldn't find a match
          continue;              //..so go on to next face

        // Trace through verts in faces, making sure they match
        for (n = 1; n < fp0->num_verts; n++) {
          vector *v0, *v1;

          v0 = &rp0->verts[fp0->face_verts[(i + n) % fp0->num_verts]];
          v1 = &rp1->verts[fp1->face_verts[(j - n + fp1->num_verts) % fp1->num_verts]];

          if (!PointsAreSame(v0, v1)) // Found mismatch
            break;

          *v0 = *v1; // make points *exactly* the same
        }
        if (n < fp0->num_verts) // Found a mismatch
          continue;             //..so go on to next face

        // Found extact match, so join
        LinkRoomsSimple(Rooms, ROOMNUM(rp0), f0, ROOMNUM(rp1), f1);

        // Increment count
        join_count++;
      }
    }
  }

  return join_count;
}

// Find all the overlapping faces between two rooms and join them
// Returns the number of new portals created
int JoinAllOverlappingFaces(room *rp0, room *rp1) {
  face *fp0, *fp1;
  int f0, f1;
  int join_count = 0;

  // Check each face in room 0 against each in room 1
  for (f0 = 0, fp0 = rp0->faces; f0 < rp0->num_faces; f0++, fp0++) {

    // Check if face 0 is already part of portal
    if (fp0->portal_num != -1)
      continue;

    // Check current face against all faces in room 1
    for (f1 = 0, fp1 = rp1->faces; f1 < rp1->num_faces; f1++, fp1++) {

      // Check if face 1 is already part of portal
      if (fp1->portal_num != -1)
        continue;

      // This used to check if normals the same, but I decided that was bad. -MT, 3/30/99
      {
        int i;
        vector *planepoint, *norm;

        // Normals are same, so check if points are all in the same plane
        planepoint = &rp1->verts[fp1->face_verts[0]];
        norm = &fp1->normal;
        for (i = 0; i < fp0->num_verts; i++)
          if (CheckPointToPlane(&rp0->verts[fp0->face_verts[i]], planepoint, norm))
            break;
        if (i < fp0->num_verts)
          continue;

        planepoint = &rp0->verts[fp0->face_verts[0]];
        norm = &fp0->normal;
        for (i = 0; i < fp1->num_verts; i++)
          if (CheckPointToPlane(&rp1->verts[fp1->face_verts[i]], planepoint, norm))
            break;
        if (i < fp1->num_verts)
          continue;

        // Clip the connecting faces against each other
        if (ClipFacePair(rp0, f0, rp1, f1)) {

          // Make the two faces match exactly
          MatchPortalFaces(rp0, f0, rp1, f1);

          // Create the portals between the rooms
          LinkRoomsSimple(Rooms, ROOMNUM(rp0), f0, ROOMNUM(rp1), f1);

          // Reset face pointer, which may have been changed by the clip
          fp0 = &rp0->faces[f0];

          // Increment count
          join_count++;

          // Stop checking this face, since we've formed a portal for it
          break;
        } else { // it's kind of bad if the clip fails, but we have to live with it

          // Reset face pointers, which may have been changed by the clip
          fp0 = &rp0->faces[f0];
          fp1 = &rp1->faces[f1];
        }
      }
    }
  }

  return join_count;
}

// Find all the adjacent faces between two rooms and join them
void JoinAllAdjacentFaces(room *rp0, room *rp1) {
  int join_count;
  int answer;

  answer = OutrageMessageBox(MBOX_YESNOCANCEL, "Do you want to include non-matching faces?\n\n"
                                               "Selecting YES means faces will be joined if they overlap.\n"
                                               "Selecting NO means faces much match exactly.");

  if (answer == IDCANCEL)
    return;

  if (answer == IDYES)
    join_count = JoinAllOverlappingFaces(rp0, rp1);
  else
    join_count = JoinAllMatchingFaces(rp0, rp1);

  World_changed = 1;

  OutrageMessageBox("%d new portals created.\n", join_count);
}

int FindNeighbor(room *rp, int facenum, int edgenum) {
  face *fp = &rp->faces[facenum];
  int v0, v1, f, v;

  v0 = fp->face_verts[edgenum];
  v1 = fp->face_verts[(edgenum + 1) % fp->num_verts];

  for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++)
    for (v = 0; v < fp->num_verts; v++)
      if ((fp->face_verts[v] == v1) && (fp->face_verts[(v + 1) % fp->num_verts] == v0))
        return f;

  return -1;
}

void PropagateFromFace(room *rp, int facenum, uint8_t *face_flags, bool matching_faces_only) {
  face *fp = &rp->faces[facenum];

  face_flags[facenum] = 1;

  for (int v = 0; v < fp->num_verts; v++) {
    int t;

    t = FindNeighbor(rp, facenum, v);

    if ((t != -1) && !face_flags[t])
      if (!matching_faces_only || (rp->faces[t].tmap == fp->tmap)) {
        HTexturePropagateToFace(rp, t, rp, facenum);
        PropagateFromFace(rp, t, face_flags, matching_faces_only);
      }
  }
}

// Propagate a texture from one face to all the faces in the room
// If matching_faces_only is set, only propagate if the face has the same texture
void PropagateToAllFaces(room *rp, int facenum, bool matching_faces_only) {
  uint8_t face_flags[MAX_FACES_PER_ROOM];

  // Clear flags
  for (int i = 0; i < rp->num_faces; i++)
    face_flags[i] = 0;

  // Start recursive function
  PropagateFromFace(rp, facenum, face_flags, matching_faces_only);

  // Set flag
  World_changed = 1;
}

// Splits a face unto triangles, by fanning
// Parameters:	rp,facenum - the face to triangulate
//					vertnum - the vert that is the base of the fan
void TriangulateFace(room *rp, int facenum, int vertnum) {
  face *fp = &rp->faces[facenum], *nfp;
  int num_new_faces, first_new_face, i;

  if (fp->num_verts == 3) {
    OutrageMessageBox("Face %d has three verts and cannot be split.", facenum);
    return;
  }

  if (fp->portal_num != -1) {
    OutrageMessageBox("You cannot split a face that's part of a portal.");
    return;
  }

  if (fp->flags & (FF_HAS_TRIGGER + FF_FLOATING_TRIG)) {
    OutrageMessageBox("You cannot split a face that has a trigger.");
    return;
  }

  // Add new faces
  num_new_faces = fp->num_verts - 2;
  first_new_face = RoomAddFaces(rp, num_new_faces);

  // Reset pointer to our old face
  fp = &rp->faces[facenum];

  // Set up each face
  for (i = 0, nfp = &rp->faces[first_new_face]; i < num_new_faces; i++, nfp++) {
    InitRoomFace(nfp, 3);

    // Set verts & uvls for this face
    nfp->face_verts[0] = fp->face_verts[vertnum];
    nfp->face_uvls[0] = fp->face_uvls[vertnum];
    for (int v = 1; v < 3; v++) {
      nfp->face_verts[v] = fp->face_verts[(vertnum + i + v) % fp->num_verts];
      nfp->face_uvls[v] = fp->face_uvls[(vertnum + i + v) % fp->num_verts];
    }

    // Copy other data for this face
    CopyFaceFlags(nfp, fp);
#ifndef NEWEDITOR
    nfp->tmap = fp->tmap;
#else
    // Apply texture
    HTextureApplyToRoomFace(rp, first_new_face + i, nfp->tmap);
#endif
    nfp->light_multiple = fp->light_multiple;

    // Compute the normal for this face
    ComputeFaceNormal(rp, first_new_face + i);
  }

  // Delete original face
  DeleteRoomFace(rp, facenum);

  // Check for degenerate faces (caused by colinear points) and merge with adjacent faces
  first_new_face--; // original face deleted, causing shift
  bool ok;
  do { // Check first face
    ok = ComputeFaceNormal(rp, first_new_face);
    if (!ok) {
      face *fp = &rp->faces[first_new_face];
      ASSERT(first_new_face < rp->num_faces - 1);
      AddVertToFace(rp, first_new_face, rp->faces[first_new_face + 1].face_verts[2], fp->num_verts - 1);
      rp->faces[first_new_face].face_uvls[rp->faces[first_new_face].num_verts - 1] =
          rp->faces[first_new_face + 1].face_uvls[2];
      DeleteRoomFace(rp, first_new_face + 1);
      num_new_faces--;
    }
  } while (!ok);
  do { // Check last face
    ok = ComputeFaceNormal(rp, rp->num_faces - 1);
    if (!ok) {
      face *fp = &rp->faces[rp->num_faces - 2];
      ASSERT(first_new_face < rp->num_faces - 1);
      AddVertToFace(rp, rp->num_faces - 1, rp->faces[rp->num_faces - 2].face_verts[1], 0);
      rp->faces[rp->num_faces - 1].face_uvls[1] = rp->faces[rp->num_faces - 2].face_uvls[1];
      DeleteRoomFace(rp, rp->num_faces - 2);
      num_new_faces--;
    }
  } while (!ok);

  // We're done
  EditorStatus("Face %d replace by %d new faces", facenum, num_new_faces);
#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

// Deletes the connection between two rooms.  Deletes both portals.
void DeletePortalPair(room *rp, int portalnum) {
  int roomnum = ROOMNUM(rp);
  portal *pp = &rp->portals[portalnum];
  int croom = pp->croom, cportal = pp->cportal;

  // Make sure the connecting portal points back to this portal
  if ((Rooms[croom].portals[cportal].croom != roomnum) || (Rooms[croom].portals[cportal].cportal != portalnum)) {
    OutrageMessageBox("Cannot delete this portal: the connecting portal does not point back at it.\n");
    return;
  }

  // Check all the faces in this portal to make sure they point back to the portal
  if (rp->faces[pp->portal_face].portal_num != portalnum) {
    OutrageMessageBox("Cannot delete this portal: its face does not point back at it.");
    return;
  }

  DeleteRoomPortal(rp, portalnum);
  DeleteRoomPortal(&Rooms[croom], cportal);

  EditorStatus("Deleted room %d portal %d and room %d portal %d", roomnum, portalnum, croom, cportal);

  World_changed = 1;
}

// Flips a face
void FlipFace(room *rp, int facenum) {
  face *fp = &rp->faces[facenum];

  ASSERT(fp->portal_num == -1);

  for (int i = 0; i < fp->num_verts / 2; i++) {
    int v = fp->face_verts[i];
    fp->face_verts[i] = fp->face_verts[fp->num_verts - 1 - i];
    fp->face_verts[fp->num_verts - 1 - i] = v;

    roomUVL uvl = fp->face_uvls[i];
    fp->face_uvls[i] = fp->face_uvls[fp->num_verts - 1 - i];
    fp->face_uvls[fp->num_verts - 1 - i] = uvl;
  }

  // Get new normal
  if (!ComputeFaceNormal(rp, facenum))
    Int3(); // Bad!  Get Matt!

#ifndef NEWEDITOR
  World_changed = 1;
  EditorStatus("Room %d face %d flipped.", ROOMNUM(rp), facenum);
#else
  if (ROOMNUM(rp) < MAX_ROOMS)
    EditorStatus("Room %d face %d flipped.", ROOMNUM(rp), facenum);
  else
    EditorStatus("Face %d flipped.", facenum);
#endif
}

// Attempt to fix the cracks in a level
void FixCracks() {
  int r, p, f, f2, v, v2;
  room *rp;
  face *fp, *fp2;
  int possible_tjoints = 0, tjoints_fixed = 0;
  int points_added = 0;
  int points_are_same_count = 0;

  if (OutrageMessageBox(MBOX_YESNO, "This function is somewhat dangerous.\n\n"
                                    "You should be sure to save your level beforehand, and you should check the "
                                    "results very carefully afterwards.\n\n"
                                    "Continue?") != IDYES)
    return;

  // First fix gaps at portals
  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (p = 0; p < rp->num_portals; p++) {
        portal *pp = &rp->portals[p];
        points_added +=
            MatchPortalFaces(rp, pp->portal_face, &Rooms[pp->croom], Rooms[pp->croom].portals[pp->cportal].portal_face);
      }
    }
  }

  // Now search for and fix t-joints
  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used)
      for (f = 0, fp = rp->faces; f < rp->num_faces; f++, fp++) {
        // if (fp->portal_num == -1)
        { // don't check portal faces
        recheck_face:;
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
              // mprintf(0,"Couldn't find shared edge for %d:%d edge %d\n",r,f,v);
              possible_tjoints++;

              // Look for vert on this edge
              for (f2 = 0, fp2 = rp->faces; f2 < rp->num_faces; f2++, fp2++) {
                if (f2 != f) {
                  for (v2 = 0; v2 < fp2->num_verts; v2++) {
                    int tt0 = fp2->face_verts[v2], tt1 = fp2->face_verts[(v2 + 1) % fp2->num_verts];

                    if (vv0 == tt1) { // one point maches; check if next is on the edge
                      // if (PointsAreColinear(&rp->verts[vv0],&rp->verts[tt0],&rp->verts[vv1])) {

                      if (PointsAreSame(&rp->verts[tt0], &rp->verts[vv0]))
                        points_are_same_count++;
                      if (PointsAreSame(&rp->verts[tt0], &rp->verts[vv1]))
                        points_are_same_count++;

                      if (CheckPointToPlane(&rp->verts[tt0], &rp->verts[vv0], &fp->normal) == 0) {
                        if (CheckPointAgainstEdge(&rp->verts[tt0], &rp->verts[vv0], &rp->verts[vv1], &fp->normal) ==
                            0) {
                          // make sure the new point is actually between the two edge points
                          float edge_len = vm_VectorDistance(&rp->verts[vv1], &rp->verts[vv0]);
                          float d0 = vm_VectorDistance(&rp->verts[tt0], &rp->verts[vv0]);
                          float d1 = vm_VectorDistance(&rp->verts[tt0], &rp->verts[vv1]);
                          if ((d0 < edge_len) && (d1 < edge_len)) {
                            mprintf(0, "Adding %d to edge %d of %d:%d (from face %d)\n", tt0, v, r, f, f2);
                            AddVertToFace(rp, f, tt0, v);
                            tjoints_fixed++;
                            goto recheck_face;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
  }

  // Fix portals again because points may have been added when fixing t-joints
  for (r = 0, rp = Rooms; r <= Highest_room_index; r++, rp++) {
    if (rp->used) {
      for (p = 0; p < rp->num_portals; p++) {
        portal *pp = &rp->portals[p];
        points_added +=
            MatchPortalFaces(rp, pp->portal_face, &Rooms[pp->croom], Rooms[pp->croom].portals[pp->cportal].portal_face);
      }
    }
  }

  mprintf(0, "%d possible t-joints\n", possible_tjoints);
  mprintf(0, "points_are_same_count = %d\n", points_are_same_count);

  OutrageMessageBox("Level fix results:\n\n"
                    "    %d points added to portals\n"
                    "    %d T-joints fixed",
                    points_added, tjoints_fixed);

  World_changed = 1;
}

// Variables for undoing a snap
int Snap_roomnum = -1;
int Snap_vertnum;
vector Snap_old_point, Snap_new_point;

// Moves a vertex to lie on a specified edge
void SnapPointToEdge(room *rp, int vertnum, vector *v0, vector *v1) {
  vector *vp = &rp->verts[vertnum];
  vector edge_vec, edge_normal;
  float d;

  // Save info for undo
  Snap_roomnum = ROOMNUM(rp);
  Snap_vertnum = vertnum;
  Snap_old_point = *vp;

  // Calculate new point
  edge_normal = edge_vec = *v1 - *v0;
  vm_NormalizeVector(&edge_normal);
  d = vm_DistToPlane(vp, &edge_normal, v0);
  *vp = *v0 + edge_normal * d;

  // Set the point
  Snap_new_point = *vp;

  // Done
  EditorStatus("Room %d point %d snapped.", Snap_roomnum, Snap_vertnum);
  World_changed = 1;
}

// Moves a vertex to be conincident with another vertex
void SnapPointToPoint(room *rp, int vertnum, room *snapto_rp, int snapto_vertnum) {
  vector *vp = &rp->verts[vertnum];

  // Save info for undo
  Snap_roomnum = ROOMNUM(rp);
  Snap_vertnum = vertnum;
  Snap_old_point = *vp;

  *vp = snapto_rp->verts[snapto_vertnum];

  // Set the point
  Snap_new_point = *vp;

  // Done
  EditorStatus("Room %d point %d snapped.", Snap_roomnum, Snap_vertnum);
  World_changed = 1;
}

// Moves a vertex to lie on a specified plane
void SnapPointToFace(room *rp, int vertnum, vector *v0, vector *normal) {
  vector *vp = &rp->verts[vertnum];
  float d;

  // Save info for undo
  Snap_roomnum = ROOMNUM(rp);
  Snap_vertnum = vertnum;
  Snap_old_point = *vp;

  // Calculate new point
  d = vm_DistToPlane(vp, normal, v0);
  *vp -= *normal * d;

  // Set the point
  Snap_new_point = *vp;

  // Done
  EditorStatus("Room %d point %d snapped.", Snap_roomnum, Snap_vertnum);
  World_changed = 1;
}

// Undoes the most recently-performed snap
void UndoSnap() {
  if (Snap_roomnum == -1)
    return;

  if ((Snap_roomnum <= Highest_room_index) && Rooms[Snap_roomnum].used) {
    vector *vp = &Rooms[Snap_roomnum].verts[Snap_vertnum];

    if ((vp->x == Snap_new_point.x) && (vp->y == Snap_new_point.y) && (vp->z == Snap_new_point.z)) {
      *vp = Snap_old_point;
      World_changed = 1;
      return;
    }
  }

  OutrageMessageBox("Cannot Undo: The snapped point has changed since the snap.");
  Snap_roomnum = -1;
}

// Gets the angle between two vectors in the range 0..1
// Parameters:	base - the start of both vectors
//					v0,v1 - the end points of the two vectors
//					normal - the surface normal of the face these verts lie in
// Returns the cosine of the angle between <base,v0> and <base,v1>
float GetAngle(vector *base, vector *v0, vector *v1, vector *normal) {
  vector edge0, edge1, cross;
  float dot;

  vm_GetNormalizedDir(&edge0, v0, base);
  vm_GetNormalizedDir(&edge1, v1, base);

  dot = edge0 * edge1;
  cross = edge0 ^ edge1;

  if (cross * *normal > 0)
    return 0.25 - dot / 4.0;
  else
    return 0.75 + dot / 4.0;
}

// Connects two rooms in a pleasing way
void BuildSmoothBridge(room *rp0, int facenum0, room *rp1, int facenum1) {
  room *rp;
  int nv0, nv1, nverts, nfaces;
  int i;
  vector tverts[MAX_VERTS_PER_FACE];

  // Get values from current faces
  face *fp0 = &rp0->faces[facenum0];
  face *fp1 = &rp1->faces[facenum1];
  nv0 = fp0->num_verts;
  nv1 = fp1->num_verts;

  // Check for portal already here
  if (fp0->portal_num != -1) {
    OutrageMessageBox("Cannot build bridge: There is already a connection at %d:%d.", ROOMNUM(rp0), facenum0);
    return;
  }
  if (fp1->portal_num != -1) {
    OutrageMessageBox("Cannot build bridge: There is already a connection at %d:%d.", ROOMNUM(rp1), facenum1);
    return;
  }

  // Get values for new room
  nverts = nv0 + nv1;
  nfaces = nverts + 2;

  // Get a pointer to our room
  rp = CreateNewRoom(nverts, nfaces);
  if (rp == NULL) {
    OutrageMessageBox("Cannot build bridge: No free rooms.");
    return;
  }

  // Set the vertices for the room
  for (i = 0; i < nv0; i++)
    rp->verts[i] = rp0->verts[fp0->face_verts[i]];
  for (i = 0; i < nv1; i++)
    rp->verts[nv0 + i] = rp1->verts[fp1->face_verts[nv1 - 1 - i]];

  // Create the connecting faces

  // Compute normalized vector from attach face to base face
  vector c0, c1, delta_vec;
#ifndef NEWEDITOR
  ComputeCenterPointOnFace(&c0, rp0, facenum0);
  ComputeCenterPointOnFace(&c1, rp1, facenum1);
#else
  ComputeFaceBoundingCircle(&c0, rp0, facenum0);
  ComputeFaceBoundingCircle(&c1, rp1, facenum1);
#endif
  vm_GetNormalizedDir(&delta_vec, &c1, &c0);

  // Compute the cosine of the angle between our vector and the normal of the base face
  float cos = delta_vec * fp1->normal;

  // Get a pointer to a vertex on face1
  vector *vp = &rp->verts[nv0];

  // Project the verts from end face0 into end face1
  for (i = 0; i < nv0; i++) {

    // Get distance from base face to this vertex
    float dist = ((*vp - rp->verts[i]) * fp1->normal) / cos;

    // Get the new vert
    tverts[i] = rp->verts[i] + (delta_vec * dist);
  }

  // Find closest face0 point to point 0 of face1
  int smallest_i = -1;
  float smallest_angle = 1.0;
  vector tnorm = -fp1->normal;
  for (i = 0; i < nv0; i++) {
    float angle = GetAngle(&c1, &rp->verts[nv0], &tverts[i], &tnorm);
    if (angle > 0.5)
      angle = 1.0 - angle; // we want closest in either direction
    if (angle < smallest_angle) {
      smallest_i = i;
      smallest_angle = angle;
    }
  }
  ASSERT(smallest_i != -1);

  // Generate new faces
  int prev1 = 0, // set up the previous edge
      prev0 = smallest_i;
  for (i = 0; i < nverts; i++) {
    float angle0, angle1;

    face *fp = &rp->faces[i];

    InitRoomFace(fp, 3);

    fp->face_verts[0] = nv0 + prev1;
    fp->face_verts[1] = prev0;

    if (i == nverts - 1) { // special case for last edge
      if ((rp->faces[0].face_verts[0] != fp->face_verts[0]) && (rp->faces[0].face_verts[0] != fp->face_verts[1]))
        fp->face_verts[2] = rp->faces[0].face_verts[0];
      else {
        ASSERT((rp->faces[0].face_verts[1] != fp->face_verts[0]) && (rp->faces[0].face_verts[0] != fp->face_verts[1]));
        fp->face_verts[2] = rp->faces[0].face_verts[1];
      }
      break;
    }

    // Pick point for third vert
    angle1 = GetAngle(&c1, &rp->verts[nv0 + prev1], &rp->verts[nv0 + (prev1 + 1) % nv1], &tnorm);
    angle0 = GetAngle(&c1, &rp->verts[nv0 + prev1], &tverts[(prev0 + 1) % nv0], &tnorm);

    if (angle1 < angle0) {
      prev1 = (prev1 + 1) % nv1;
      fp->face_verts[2] = nv0 + prev1;
    } else
      prev0 = fp->face_verts[2] = (prev0 + 1) % nv0;
  }

  // Set the two end faces for the room
  InitRoomFace(&rp->faces[nfaces - 2], fp0->num_verts);
  for (i = 0; i < fp0->num_verts; i++)
    rp->faces[nfaces - 2].face_verts[i] = nv0 - 1 - i;

  InitRoomFace(&rp->faces[nfaces - 1], fp1->num_verts);
  for (i = 0; i < fp1->num_verts; i++)
    rp->faces[nfaces - 1].face_verts[i] = fp0->num_verts + i;

  // Set normals & textures for each face
  for (i = 0; i < nfaces; i++) {
    if (!ComputeFaceNormal(rp, i))
      Int3(); // Bad!  Get Matt!
  }

  // Attempt to combine faces
  for (i = 0; i < nfaces - 2; i++) {
    int t = (i + 1) % (nfaces - 2);

    // Try compbining the faces
    if (CombineFaces(rp, i, t)) {
      i--; // check this face again
      nfaces--;
    }
  }

  // Set textures for each face
#ifndef NEWEDITOR
  for (i = 0; i < nfaces; i++)
    rp->faces[i].tmap = i + 1;
#else
  int texnum = Editor_state.GetCurrentTexture();
  for (i = 0; i < nfaces; i++) {
    // Apply texture
    HTextureApplyToRoomFace(rp, i, texnum);
  }
#endif

  // Set UVs for all the faces
  AssignDefaultUVsToRoom(rp);

  // Form the portals between the rooms
  LinkRoomsSimple(Rooms, ROOMNUM(rp0), facenum0, ROOMNUM(rp), nfaces - 2);
  LinkRoomsSimple(Rooms, ROOMNUM(rp1), facenum1, ROOMNUM(rp), nfaces - 1);

  // Make the new room the current room
#ifndef NEWEDITOR
  Curroomp = rp;
  Curface = nfaces - 2;
  Curedge = Curvert = 0;
  Curportal = -1;
#else
  Editor()->m_pLevelWnd->SetPrim(rp, nfaces - 2, -1, 0, 0);
#endif

  // Set the flag
  World_changed = 1;
}

int16_t New_face_verts[MAX_VERTS_PER_FACE];
int New_face_num_verts = -1;
room *New_face_roomp;

void AddNewFaceVert() {
  if (Curroomp != New_face_roomp) {
    OutrageMessageBox("All points in the new face must be in the same room");
    return;
  }

  if (New_face_num_verts == -1) {
    OutrageMessageBox("You must start a new face before adding to it");
    return;
  }

  New_face_verts[New_face_num_verts++] = Curroomp->faces[Curface].face_verts[Curvert];

  EditorStatus("Added %d as vert #%d in new face", Curroomp->faces[Curface].face_verts[Curvert], New_face_num_verts);
}

void StartNewFace() {
  New_face_roomp = Curroomp;
  New_face_num_verts = 0;

  AddNewFaceVert();

  EditorStatus("Starting new face with vertex %d", Curroomp->faces[Curface].face_verts[Curvert]);
}

void EndNewFace() {
  AddNewFaceVert();

  if (New_face_num_verts == -1) {
    OutrageMessageBox("You must start a new face before ending it");
    return;
  }

  if (New_face_num_verts < 3) {
    OutrageMessageBox("A face must have at least three vertices");
    return;
  }

  int facenum;

  facenum = RoomAddFaces(Curroomp, 1);

  face *fp = &Curroomp->faces[facenum];

  InitRoomFace(fp, New_face_num_verts);

  for (int i = 0; i < New_face_num_verts; i++)
    fp->face_verts[i] = New_face_verts[i];

#ifndef NEWEDITOR
  fp->tmap = 0;
#else
  int texnum = Editor_state.GetCurrentTexture();
  // Apply texture
  HTextureApplyToRoomFace(Curroomp, facenum, texnum);
#endif

  ComputeFaceNormal(Curroomp, facenum);
  AssignDefaultUVsToRoomFace(Curroomp, facenum);

  EditorStatus("New face %d created", facenum);

  New_face_num_verts = -1;

  World_changed = 1;
}

void ObjRelink(int objnum, int newroomnum);
int RemoveDuplicatePoints(room *rp);
trigger *FindTrigger(int roomnum, int facenum);

// Combine the two rooms. base_rp stays, att_rp goes away
// Returns true if combine sucessful, false if can't join
bool CombineRooms(room *base_rp, room *att_rp) {
  int i;
  face *fp;
  bool connected = 0, rendered_portals = 0;

  // Make sure these rooms share a portal
  for (i = 0; i < base_rp->num_portals; i++) {
    if (base_rp->portals[i].croom == ROOMNUM(att_rp)) {
      connected = 1;
      if ((base_rp->faces[base_rp->portals[i].portal_face].flags & FF_HAS_TRIGGER) ||
          (att_rp->faces[att_rp->portals[base_rp->portals[i].cportal].portal_face].flags & FF_HAS_TRIGGER)) {
        OutrageMessageBox("Cannot combine rooms: a portal connecting them has a trigger.");
        return 0;
      }
      if ((base_rp->portals[i].flags & PF_RENDER_FACES) ||
          (att_rp->portals[base_rp->portals[i].cportal].flags & PF_RENDER_FACES)) {
        rendered_portals = 1;
      }
    }
  }

  if (!connected) {
    OutrageMessageBox("Cannot combine rooms: the rooms are not connected.");
    return 0;
  }

  if (rendered_portals) {
    if (OutrageMessageBox(
            MBOX_YESNO,
            "One or more of the portals connecting these rooms has the Render Faces flag set.  "
            "The rendered face will remain in the room after combine.\n\nDo you still want to combine?") != IDYES)
      return 0;
  }

  // Check for doors
  if (base_rp->doorway_data || att_rp->doorway_data) {
    OutrageMessageBox("Cannot combine rooms: one room is a door.");
    return 0;
  }

  // Allocate new verts & faces
  int first_new_vert = RoomAddVertices(base_rp, att_rp->num_verts);
  int first_new_face = RoomAddFaces(base_rp, att_rp->num_faces);

  // Copy verts to base room
  for (i = 0; i < att_rp->num_verts; i++)
    base_rp->verts[first_new_vert + i] = att_rp->verts[i];

  // Copy faces to base room
  for (i = 0, fp = &base_rp->faces[first_new_face]; i < att_rp->num_faces; fp++, i++) {

    // Copy the face
    CopyFace(fp, &att_rp->faces[i]);
    fp->flags = att_rp->faces[i].flags;

    // Update the vertices
    for (int v = 0; v < fp->num_verts; v++)
      fp->face_verts[v] += first_new_vert;

    // Move triggers from attach to base room
    if (att_rp->faces[i].flags & FF_HAS_TRIGGER) {
      trigger *tp = FindTrigger(ROOMNUM(att_rp), i);
      tp->roomnum = ROOMNUM(base_rp);
      tp->facenum += first_new_face;
    }
  }

  // Deal with attach room's portals
  for (i = 0; i < att_rp->num_portals; i++) {
    int facenum, croom, cface, flags, cflags;

    facenum = att_rp->portals[i].portal_face + first_new_face;
    flags = att_rp->portals[i].flags;
    croom = att_rp->portals[i].croom;
    cface = Rooms[croom].portals[att_rp->portals[i].cportal].portal_face;
    cflags = Rooms[croom].portals[att_rp->portals[i].cportal].flags;

    // Delete old portal from attach room
    DeletePortalPair(att_rp, i);

    // If this portal attaches to the base room, mark the portal faces for deletion
    if (croom == ROOMNUM(base_rp)) {
      if (!(flags & PF_RENDER_FACES))
        base_rp->faces[facenum].tmap = -1; //-1 means to delete the face
      if (!(cflags & PF_RENDER_FACES))
        base_rp->faces[cface].tmap = -1; //-1 means to delete the face
    } else {                             // Attaches to third room, so make attachment to base room
      LinkRooms(Rooms, ROOMNUM(base_rp), facenum, croom, cface);
      portal *pp = &base_rp->portals[base_rp->num_portals - 1];
      pp->flags |= (flags & (PF_RENDER_FACES + PF_RENDERED_FLYTHROUGH));
      Rooms[pp->croom].portals[pp->cportal].flags |= (cflags * (PF_RENDER_FACES + PF_RENDERED_FLYTHROUGH));
    }

    i--; // adjust for new portal numbering
  }

  // Delete obsolete faces
  for (i = 0; i < base_rp->num_faces; i++)
    if (base_rp->faces[i].tmap == -1) {
      DeleteRoomFace(base_rp, i);
      i--;
    }

  // Link objects to new room
  while (att_rp->objects != -1)
    ObjRelink(att_rp->objects, ROOMNUM(base_rp));

  // Delete the old room
  DeleteRoomFromMine(att_rp);

  // Get rid of duplicate verts
  RemoveDuplicatePoints(base_rp);

  // Done!
  World_changed = 1;
  return 1;
}

// Creates a an external room and links the specified faces to it
// Parameters:	rp - the room to connect to the new room
//					nfaces - how many faces connect to the new room (this becomes the number of
//portals) 					facenums - the list of faces to connect
void LinkToExternalRoom(room *rp, int nfaces, int *facenums) {
  int vert_xlate[MAX_VERTS_PER_ROOM];
  int v, i, nverts = 0;

  for (i = 0; i < rp->num_verts; i++)
    vert_xlate[i] = -1;

  for (i = 0; i < nfaces; i++) {
    face *fp = &rp->faces[facenums[i]];

    for (v = 0; v < fp->num_verts; v++) {
      int vertnum = fp->face_verts[v];
      if (vert_xlate[vertnum] == -1)
        vert_xlate[vertnum] = nverts++;
    }
  }

  room *newrp = CreateNewRoom(nverts, nfaces);

  newrp->flags |= RF_EXTERNAL;

  for (i = 0; i < rp->num_verts; i++) {
    if (vert_xlate[i] != -1)
      newrp->verts[vert_xlate[i]] = rp->verts[i];
  }

  for (i = 0; i < nfaces; i++) {
    face *newfp = &newrp->faces[i], *fp = &rp->faces[facenums[i]];

    InitRoomFace(newfp, fp->num_verts);

    for (v = 0; v < fp->num_verts; v++)
      newfp->face_verts[v] = vert_xlate[fp->face_verts[fp->num_verts - v - 1]];

#ifndef NEWEDITOR
    newfp->tmap = fp->tmap;
#else
    // Apply texture
    HTextureApplyToRoomFace(newrp, i, newfp->tmap);
#endif

    if (!ComputeFaceNormal(newrp, i))
      Int3();

    LinkRooms(Rooms, ROOMNUM(rp), facenums[i], ROOMNUM(newrp), i);
  }

  AssignDefaultUVsToRoom(newrp);

  World_changed = 1;
}

extern bool Disable_editor_rendering;

// Splits a face into two pieces
// Parameters:	rp,facenum - the face to split
//					v0,v1 - the two verts that will form the new edge
void SplitFace(room *rp, int facenum, int v0, int v1) {
  face *fp = &rp->faces[facenum], *nfp;
  int first_new_face, i;

  if (v0 == v1) {
    OutrageMessageBox("You cannot split a face using the same point twice.");
    return;
  }

  if (v1 < v0) {
    int t = v1;
    v1 = v0;
    v0 = t;
  }

  if (v1 == (v0 + 1) % fp->num_verts) {
    OutrageMessageBox("You cannot split a face using two adjacent points.");
    return;
  }

  if (fp->num_verts == 3) {
    OutrageMessageBox("Face %d has three verts and cannot be split.", facenum);
    return;
  }

  if (fp->portal_num != -1) {
    OutrageMessageBox("You cannot split a face that's part of a portal.");
    return;
  }

  if (fp->flags & (FF_HAS_TRIGGER + FF_FLOATING_TRIG)) {
    OutrageMessageBox("You cannot split a face that has a trigger.");
    return;
  }

  Disable_editor_rendering = 1;

  // Add new faces
  first_new_face = RoomAddFaces(rp, 2);

  // Reset pointer to our old face
  fp = &rp->faces[facenum];

  // Set up each face
  bool ok[2];
  for (i = 0, nfp = &rp->faces[first_new_face]; i < 2; i++, nfp++) {
    int nv, startv;

    if (i == 0) {
      nv = v1 - v0 + 1;
      startv = v0;
    } else {
      nv = fp->num_verts - (v1 - v0) + 1;
      startv = v1;
    }

    InitRoomFace(nfp, nv);

    // Set verts & uvls for this face
    for (int v = 0; v < nv; v++) {
      nfp->face_verts[v] = fp->face_verts[(startv + v) % fp->num_verts];
      nfp->face_uvls[v] = fp->face_uvls[(startv + v) % fp->num_verts];
    }

    // Copy other data for this face
    CopyFaceFlags(nfp, fp);
#ifndef NEWEDITOR
    nfp->tmap = fp->tmap;
#else
    // Apply texture
    HTextureApplyToRoomFace(rp, first_new_face + i, fp->tmap);
#endif
    nfp->light_multiple = fp->light_multiple;

    // Compute the normal for this face
    ok[i] = ComputeFaceNormal(rp, first_new_face + i);
  }

  // Bail if either face is degenerate
  if (!ok[0] || !ok[1]) {
    OutrageMessageBox("Cannot form face here: one new face is degenerate.");
    DeleteRoomFace(rp, first_new_face);
    DeleteRoomFace(rp, first_new_face + 1);
    Disable_editor_rendering = 0;
    return;
  }

  // Delete original face
  DeleteRoomFace(rp, facenum);

  // We're done
  EditorStatus("Face %d replaced by new faces %d & %d", facenum, first_new_face - 1, first_new_face);

  Disable_editor_rendering = 0;

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

// Adds a point to an edge
void SplitEdge(room *rp, int facenum, int edgenum, float position) {
  face *fp = &rp->faces[facenum];
  int vert1 = (edgenum + 1) % fp->num_verts;
  vector *v0, *v1, newv;

  v0 = &rp->verts[fp->face_verts[edgenum]];
  v1 = &rp->verts[fp->face_verts[vert1]];

  newv = *v0 + (*v1 - *v0) * position;

  AddPointToAllEdges(rp, fp->face_verts[edgenum], fp->face_verts[vert1], &newv);

  World_changed = 1;
}

#define MIN_NORMAL_MAG 0.035

int FindConnectedFace(room *rp, int facenum, int edgenum, int startface);

// Deletes a vertex from an face
// Only deletes if the two adjacent edges are colinear, and there isn't a T-joint at this point
void DeleteVert(room *rp, int facenum, int vertnum) {
  face *fp = &rp->faces[facenum];
  vector normal;
  float mag;
  int f0, f1;
  int prev_vertnum = (vertnum + fp->num_verts - 1) % fp->num_verts;

  mag = vm_GetNormal(&normal, &rp->verts[fp->face_verts[prev_vertnum]], &rp->verts[fp->face_verts[vertnum]],
                     &rp->verts[fp->face_verts[(vertnum + 1) % fp->num_verts]]);

  if (mag >= MIN_NORMAL_MAG) {
    OutrageMessageBox("Can't remove point: edges aren't colinear.");
    return;
  }

  // Make sure there isn't a t-joint at this face
  f0 = FindConnectedFace(rp, facenum, prev_vertnum, 0);
  f1 = FindConnectedFace(rp, facenum, vertnum, 0);
  if ((f0 != -1) && (f1 != -1) && (f0 != f1)) {
    OutrageMessageBox("Can't delete vertex: apparent T-joint with faces %d & %d\n", f0, f1);
    return;
  }

  // Delete the point on our passed face
  DeletePointFromFace(rp, facenum, vertnum);

  // Delete the point on the connected face
  face *fp2 = &rp->faces[f0];
  for (int v2 = 0; v2 < fp2->num_verts; v2++)
    if (fp2->face_verts[v2] == fp->face_verts[vertnum])
      break;
  ASSERT(v2 < fp2->num_verts);
  DeletePointFromFace(rp, f0, v2);

#ifndef NEWEDITOR
  World_changed = 1;
#endif
}

// Moves a vertex along its two adjacent edges
// Only moves if the two adjacent edges are colinear
void MoveVert(room *rp, int facenum, int vertnum, float new_position) {
  face *fp = &rp->faces[facenum];
  vector normal;
  float mag;
  int prev_vertnum = (vertnum + fp->num_verts - 1) % fp->num_verts;
  int next_vertnum = (vertnum + 1) % fp->num_verts;
  vector *v0, *v1, newv;

  mag = vm_GetNormal(&normal, &rp->verts[fp->face_verts[prev_vertnum]], &rp->verts[fp->face_verts[vertnum]],
                     &rp->verts[fp->face_verts[next_vertnum]]);

  if (mag >= MIN_NORMAL_MAG) {
    OutrageMessageBox("Can't move point: edges aren't colinear.");
    return;
  }

  v0 = &rp->verts[fp->face_verts[prev_vertnum]];
  v1 = &rp->verts[fp->face_verts[next_vertnum]];

  newv = *v0 + (*v1 - *v0) * new_position;

  rp->verts[fp->face_verts[vertnum]] = newv;

  World_changed = 1;
}

#include "polymodel.h"

// Incorporates the geometry from the specified object into the specified room.  Deletes the object.
// Returns true if worked, false if some error
bool MergeObjectIntoRoom(room *rp, int objnum) {
  object *objp = &Objects[objnum];
  ASSERT(objp->render_type == RT_POLYOBJ);

  poly_model *pm = GetPolymodelPointer(objp->rtype.pobj_info.model_num);

  if (pm->n_models > 1) {
#ifndef NEWEDITOR
    OutrageMessageBox("Cannot merge: Only supported for objects with one submodel.\n\nIf you really need this "
                      "functions for objects with multiple submodles, talk to MattT.");
#else
    OutrageMessageBox("Cannot merge: Only supported for objects with one submodel.");
#endif
    return 0;
  }
  if (!pm->n_ground) {
    OutrageMessageBox("Cannot merge: The object must have a ground plane to merge.");
    return 0;
  }
  if (OBJECT_OUTSIDE(objp)) {
    OutrageMessageBox("Cannot merge: The object is outside.");
    return 0;
  }
  if (objp->roomnum != ROOMNUM(rp)) {
    OutrageMessageBox("Cannot merge: The object is not in the specified room.");
    return 0;
  }

  // Get points to model data
  bsp_info *sm = &pm->submodel[0];

  // Add verts to room
  int first_new_vert = RoomAddVertices(rp, sm->nverts);

  // Rotate the points and copy them to the room
  matrix rotmat = ~objp->orient;
  for (int i = 0; i < sm->nverts; i++) {
    rp->verts[first_new_vert + i] = objp->pos + sm->verts[i] * rotmat;
  }

  // Add faces to the room
  int first_new_face = RoomAddFaces(rp, sm->num_faces);

  // Copy the faces
  for (i = 0; i < sm->num_faces; i++) {
    polyface *pfp = &sm->faces[i];
    face *fp = &rp->faces[first_new_face + i];

    InitRoomFace(fp, pfp->nverts);

    for (int v = 0; v < fp->num_verts; v++) {
      fp->face_verts[v] = first_new_vert + pfp->vertnums[v];
      fp->face_uvls[v].u = pfp->u[v];
      fp->face_uvls[v].v = pfp->v[v];
    }

#ifndef NEWEDITOR
    fp->tmap = pm->textures[pfp->texnum];
#else
    // Apply texture
    HTextureApplyToRoomFace(rp, first_new_face + i, pm->textures[pfp->texnum]);
#endif

    if (!ComputeFaceNormal(rp, first_new_face + i))
      Int3(); // Bad!  Get Matt!
  }

  // Kill the object
  ObjDelete(objnum);

  // Done!
  World_changed = 1;
  return 1;
}

void MarkFaceForDeletion(room *rp, int facenum) {
  face *fp = &rp->faces[facenum];

  // Mark this face
  fp->tmap = -1;

  // Find connect faces
  for (int e = 0; e < fp->num_verts; e++) {
    int t = -1;

    while ((t = FindConnectedFace(rp, facenum, e, t + 1)) != -1) {
      if (rp->faces[t].tmap != -1)
        MarkFaceForDeletion(rp, t);
    }
  }
}

// Delete all the faces connected to the specified face
void DeleteAllConnectedFaces(room *rp, int facenum) {
  // Make sure no faces using tmap of -1
  for (int f = 0; f < rp->num_faces; f++)
    ASSERT(rp->faces[f].tmap != -1);

  // Do recursive marking
  MarkFaceForDeletion(rp, facenum);

  // Now delete the faces
  for (f = 0; f < rp->num_faces;) {

    if (rp->faces[f].tmap == -1)
      DeleteRoomFace(rp, f);
    else
      f++;
  }

  // Done
  World_changed = 1;
}

// returns the number of faces changed
int PropagateToConnectedFacesSub(room *rp, int facenum, bool *face_checked) {
  int n_changed = 0;

  face_checked[facenum] = 1;

  face *fp = &rp->faces[facenum];

  for (int e = 0; e < fp->num_verts; e++) {
    int t = -1;

    do {

      t = FindConnectedFace(rp, facenum, e, t + 1);

      if ((t != -1) && !face_checked[t]) {

        if (NormalsAreSame(&fp->normal, &rp->faces[t].normal)) {

          HTexturePropagateToFace(rp, t, rp, facenum);

          n_changed++;

          n_changed += PropagateToConnectedFacesSub(rp, t, face_checked);
        }
      }

    } while (t != -1);
  }

  return n_changed;
}

void PropagateToConnectedFaces(room *rp, int facenum) {
  bool face_checked[MAX_FACES_PER_ROOM];
  int f, n_changed;

  for (f = 0; f < rp->num_faces; f++)
    face_checked[f] = 0;

  face_checked[facenum] = 1;

  n_changed = PropagateToConnectedFacesSub(rp, facenum, face_checked);

  EditorStatus("%d faces were retextured.", n_changed);

  if (n_changed)
    World_changed = 1;
}
