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

 * $Logfile: /DescentIII/main/room.cpp $
 * $Revision: 126 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * Functions and data for rooms
 *
 * $Log: /DescentIII/main/room.cpp $
 *
 * 126   4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 125   10/21/99 9:29p Jeff
 * B.A. Macintosh code merge
 *
 * 124   10/12/99 10:19a Gwar
 * adding terrain support to NEWEDITOR
 *
 * 123   8/30/99 1:06p Gwar
 * added a check in ComputeRoomBoundingSphere for no verts in the room
 * (for NEWEDITOR)
 *
 * 122   8/18/99 7:02a Gwar
 * in NEWEDITOR, init light multiplier and ambience in InitRoom
 *
 * 121   8/12/99 12:11a Gwar
 * minor NEWEDITOR stuff
 *
 * 120   7/20/99 1:00p Jason
 * added auto katmai support
 *
 * 119   7/05/99 12:42p Gwar
 * wrapped my last change with an #ifdef NEWEDITOR
 *
 * 118   7/05/99 12:10p Gwar
 * fixed "bug" in ComputeRoomCenter, when there are no verts in the room.
 * but if anyone minds, i can just test for no verts before calling the
 * function
 *
 * 117   7/04/99 4:56p Gwar
 * changes for texture management in NEWEDITOR
 *
 * 116   6/21/99 12:51p Gwar
 * adding texture marking for NEWEDITOR ; kind of in a state of flux right
 * now
 *
 * 115   5/17/99 11:49a Kevin
 * Added the ability to save a level from the new editor
 *
 * 114   5/08/99 8:40a Gwar
 * TONS of fixes
 *
 * 113   4/25/99 9:02p Chris
 * Improving the Bnode system
 *
 * 112   4/23/99 9:44a Gwar
 * had to add a NEWEDITOR #define...sorry.
 *
 * 111   4/18/99 4:35p Matt
 * Changed BNode_FreeRoom() to take a room pointer instead of a room
 * number, since it was being called for rooms in the scrap buffer, which
 * weren't in the room list.  Also added code to InitRoom() to init the
 * bnode data.
 *
 * 110   4/18/99 5:39a Chris
 * Vastly improved the path node system
 *
 * 109   4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 108   4/15/99 5:49p Chris
 * Fixed a bug with rendering the BOAPath nodes
 *
 * 107   4/15/99 12:19p Jason
 * made mirrors more robust and able to have multiple mirrored faces in
 * the same room (as long as they are all on the same plane)
 *
 * 106   4/07/99 4:38p Matt
 * When initializing a new face, set its tmap to 0
 *
 * 105   4/04/99 6:20p Kevin
 * Put in an ifdef for now for the new editor
 *
 * 104   3/24/99 5:53p Jason
 * added per room ambience settings
 *
 * 103   3/10/99 7:13p Jason
 * added smooth specular shading for curved surfaces
 *
 * 102   2/24/99 5:31p Hayes
 * Lowered MIN_NORMAL_MAG from 0.05 to 0.035 to allow for a small triangle
 * in Hayes's geometry for level 3.  (MattT on Hayes's machine)
 *
 * 101   2/19/99 4:28p Jason
 * fixed katmai defines
 *
 * 100   2/19/99 4:26p Jason
 *
 * 99    2/19/99 1:24p Matt
 * Moved ComputerCenterRoomOnFace() from editor to main
 *
 * 98    2/18/99 12:32p Jason
 * added room multiplier
 *
 * 97    2/03/99 5:49p Matt
 * Added room damage system
 *
 * 96    2/03/99 4:26p Jason
 * made multiplayer coop actually work!
 *
 * 95    2/01/99 4:17p Jason
 * more changes for multisafe
 *
 * 94    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 93    1/26/99 2:36p Jason
 * clear out room change flags upon room initting
 *
 * 92    1/24/99 6:35p Matt
 * Init a room's current face to 0 instead of -1
 *
 * 91    1/20/99 6:11p Matt
 * Fixed a couple bugs in the room wind/fog change system, and make the
 * values change from current -> new instead of start -> end.
 *
 * 90    1/19/99 11:25a Jason
 * added room (fog and wind) changing functions
 *
 * 89    1/08/99 5:37p Samir
 * reverb values per room.
 *
 * 88    12/22/98 2:03p Matt
 * Added room names, and made rooms not compress so that room numbers are
 * suitable for persistant uses.
 *
 * 87    12/21/98 2:18p Jason
 * made CheckTrasparency always return false (for now)
 *
 * 86    11/02/98 6:15p Chris
 * Room AABBs get saved with the level and the sort_face and dec_sort_face
 * list s have been removed
 *
 * 85    10/17/98 11:11p Matt
 * Added room memory allocation system
 *
 * 84    10/16/98 2:24p Jason
 * changes for the demo
 *
 * 83    10/14/98 2:48p Kevin
 * Changed memory code to comply with mem lib
 *
 * 82    10/03/98 6:00p Matt
 * Fixed bogus assert
 *
 * 81    9/11/98 4:45p Matt
 * Changed minimum surface normal mag from 0.15 to 0.05, to accomodate
 * some faces in Sean's level 15.
 *
 * 80    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 79    9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 78    8/27/98 5:19p Jason
 * added first rev of reflected surfaces
 *
 * 77    8/19/98 2:17p Jeff
 * made a function to change the texture on a face
 *
 * 76    8/17/98 6:40p Matt
 * Added ambient sound system
 *
 * 75    7/21/98 2:14p Chris
 * Some FVI speedups - not done
 *
 * 74    7/17/98 9:56a Chris
 * Intermediate checkin
 *
 * 73    7/16/98 8:29p Chris
 * Partial implementation of the new collide code
 *
 * 72    6/05/98 5:22p Jason
 * added volumetric fog
 *
 * 71    6/02/98 6:03p Jason
 * added specular lightmaps
 *
 * 70    5/22/98 3:28p Jason
 * added specular lighting
 *
 * 69    5/22/98 12:08p Matt
 * Changed MIN_NORMAL_MAG to 0.15 to accomodate small face in Sean's cave
 * tunnel.
 *
 * 68    5/15/98 5:41p Jason
 * implemented volume lighting system
 *
 * 67    5/06/98 12:55p Jason
 * did some vis effect optimizations
 *
 * 66    4/20/98 6:34p Chris
 * Oops
 *
 * 65    4/20/98 6:24p Chris
 * Bulletproofing collision code
 *
 * 64    4/13/98 2:53p Chris
 *
 * 63    4/13/98 2:21p Chris
 * Fixed some collision problems dealing with AABBs and Polymodel paging
 * in.
 *
 * 62    4/02/98 12:24p Jason
 * trimmed some fat from our structures
 *
 * 61    3/31/98 3:49p Jason
 * added memory lib
 *
 * 60    3/30/98 12:27a Jason
 * fixed memory leaks as reported by BoundsChecker
 *
 * 59    3/18/98 4:31p Chris
 * Speed up fvi and fixed some bugs
 *
 * 58    3/18/98 11:57a Sean
 * Lowered MIN_NORMAL_MAG down to 0.18, since the last change only fixed
 * two of the three small polygons that were giving us trouble.  (MattT on
 * Sean's machine)
 *
 * 57    3/18/98 11:49a Matt
 * Lowered MIN_NORMAL_MAG from 0.24 to 0.20 to not generate warnings for
 * small polygons in Sean's refueling dock antenna.
 *
 * 56    3/16/98 5:50p Chris
 * Added sorted face lists for fvi
 *
 * 55    2/19/98 11:17a Chris
 * Tweaked the BIG_OBJECT system
 *
 * 54    2/18/98 1:39p Jason
 * more changes for lighting
 *
 * 53    2/15/98 3:58p Sean
 * Lowered threshjhold for detecting low-precision normals.  (MattT on
 * Sean's machine)
 *
 * 52    2/13/98 12:57p Jason
 * changes for adjusting light multiples
 *
 * 51    2/11/98 7:01p Chris
 * Started to add wind
 *
 * 50    2/10/98 3:49p Jason
 * added pulsing walls
 *
 * 49    2/04/98 8:25p Jason
 * added light multiplier for faces
 *
 * 48    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 47    2/02/98 5:13p Matt
 * Added more generic function to compute a surface normal for a face
 *
 * 46    1/20/98 6:36p Brent
 * Lowered MIN_NORMAL_MAG (MattT on Brent's machine)
 *
 * 45    1/20/98 2:16p Chris
 * Fixed an init bug
 *
 * 44    1/20/98 1:06p Jason
 * fixed unitialized vis_effect field in room structure
 *
 * 43    1/16/98 11:53a Matt
 * Relaxed low-precision normal check, and added mprintfs with info on
 * problem normals
 *
 * 42    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 41    1/15/98 4:26p Luke
 * Re-added bad normal check. (MattT on Luke's machine)
 *
 * 40    12/23/97 1:35p Samir
 * Took out unused variable Room_viewport.
 *
 * 39    11/24/97 1:30a Jason
 * first attempt at adding shadows
 *
 * 38    11/14/97 11:55p Chris
 * Added support so that external rooms can be BIG_OBJECTs
 *
 * 37    11/14/97 6:39p Jason
 * added ability to do lighting on a single room
 *
 * 36    10/13/97 5:08p Matt
 * Moved ComputeRoomBoundingSphere() & CreateRoomObjects() from editor to
 * main
 *
 *
 * 35    10/08/97 2:28p Jason
 * got external rooms working with terrain lighting
 *
 * 34    10/03/97 3:33p Samir
 * Took out Int3 in ComputeFaceNormal.
 *
 * 33    10/02/97 12:08p Chris
 * Allow FindPointRoom to correctly handle external rooms (ignore them)
 *
 * 32    9/23/97 2:48p Matt
 * Fixed ComputeFaceNormal() to find the best normal for the face
 *
 * 31    9/19/97 2:52p Jason
 * changes to fix lightmap seam problem
 *
 * 30    9/16/97 4:26p Matt
 * Got rid of static_light & changed fields in the room struct
 *
 * 29    9/12/97 6:37p Chris
 * Fixed the FindPointRoom bug.
 *
 * 28    9/12/97 5:38p Jason
 * got doors working
 *
 * 27    9/12/97 2:25p Jason
 * fixed alpha problem
 *
 * 26    9/10/97 3:02p Matt
 * Moved GetIJ() from erooms.cpp to room.cpp
 *
 * 25    9/03/97 2:13p Chris
 * Cleaned a few lines of code
 *
 * 24    8/27/97 5:44p Matt
 * If can't get a normal from the first three points on a face, rotate
 * around and try again
 *
 * 23    8/19/97 1:43p Matt
 * Added code to free room palette on exit
 *
 * 22    8/19/97 1:13p Jason
 * added GetAreaForFace function
 *
 * 21    8/18/97 1:44a Chris
 * Added the SOLID_PORTALS flag for better performance of FindPointRoom
 *
 * 20    8/13/97 11:53a Jason
 * moved ClearAllRoomLightmaps into room.cpp where it belongs
 *
 * 19    8/12/97 3:51p Jason
 * tweaked lightmaps with radiosity
 *
 * 18    8/12/97 1:10a Jason
 * added code to support radiosity lighting
 *
 * 17    8/11/97 3:55p Chris
 * Added a function to compute the rough center of a portal
 *
 * 16    8/04/97 6:55p Chris
 *
 * 15    8/01/97 10:12a Jason
 * implemented FndRoomCenter
 *
 * 14    7/28/97 5:10p Matt
 * Initialize room's current_face field to -1
 *
 * 13    7/18/97 5:36p Jason
 * save changed paletted rooms on exit
 *
 * 12    7/17/97 3:38p Matt
 * Free all rooms at exit (doesn't include palette rooms)
 *
 * $NoKeywords: $
 */

#include "room.h"
#include "mono.h"
#include "vecmat.h"
#include "gametexture.h"
#include "manage.h"
#include "renderer.h"
#include "game.h"
#include "render.h"
#include "grdefs.h"
#include <stdlib.h>
#include <string.h>
#include "terrain.h"
#include "findintersection.h"
#include "lightmap.h"
#include "lightmap_info.h"
#include "special_face.h"
#include "mem.h"
#include "doorway.h"
#include "multi_world_state.h"
#include "damage_external.h"
#include "descent.h"
#ifdef EDITOR
#include "editor\editor_lighting.h"
#endif
#ifdef NEWEDITOR
#include "neweditor\editor_lighting.h"
#endif
#include "bnode.h"

// Global array of rooms
std::array<room, MAX_ROOMS + MAX_PALETTE_ROOMS> Rooms;
std::array<room_changes, MAX_ROOM_CHANGES> Room_changes;

extern int Cur_selected_room, Cur_selected_face;

int Highest_room_index = -1;

void FreePaletteRooms();

// Zeroes out the rooms array
void InitRooms() {
  int i;
  for (i = 0; i < MAX_ROOMS + MAX_PALETTE_ROOMS; i++) {
    memset(&Rooms[i], 0, sizeof(room));
    Rooms[i].objects = -1;     // DAJ
    Rooms[i].vis_effects = -1; // DAJ
  }

  atexit(FreeAllRooms);
  atexit(BNode_ClearBNodeInfo); // DAJ

#ifdef EDITOR
  atexit(FreePaletteRooms);
#endif
}

#if (defined(EDITOR) || defined(NEWEDITOR))
// Figures out how many verts there are in all the faces in a room
int CountRoomFaceVerts(room *rp) {
  int n = 0;

  for (int f = 0; f < rp->num_faces; f++)
    n += rp->faces[f].num_verts;

  return n;
}

#endif

// Vars for the room memory system
uint8_t *Room_mem_buf = NULL; // pointer to the rooms block of memory
uint8_t *Room_mem_ptr = NULL; // pointer to free memory in the rooms block
int Room_mem_size;          // How big our chunk is

// Closes down the room memory system.
void RoomMemClose() {
  if (Room_mem_buf)
    mem_free(Room_mem_buf);

  Room_mem_buf = Room_mem_ptr = NULL;
}

// Initialized the memory buffer for a room
// Parameters:	size - the total amount of memory needed for the room
void RoomMemInit(int nverts, int nfaces, int nfaceverts, int nportals) {
#if (defined(EDITOR) || defined(NEWEDITOR))
  return; // This system is disabled in the editor
#endif

  if (nverts == 0) // We don't know how much mem the room will use, so do the old way
    return;

  int size = (nfaces * (sizeof(*Rooms[0].faces))) + (nverts * sizeof(*Rooms[0].verts)) +
             (nportals * sizeof(*Rooms[0].portals)) +
             (nfaceverts * (sizeof(*Rooms[0].faces[0].face_verts) + sizeof(*Rooms[0].faces[0].face_uvls)));

  if (Room_mem_buf)
    mem_free(Room_mem_buf);

  Room_mem_buf = (uint8_t *)mem_malloc(size);
  Room_mem_size = size;

  Room_mem_ptr = Room_mem_buf;
}

// Allocates memory for a room or face
void *RoomMemAlloc(int size) {
  if (Room_mem_buf) {
    void *p = Room_mem_ptr;
    Room_mem_ptr += size;
    ASSERT(Room_mem_ptr <= (Room_mem_buf + Room_mem_size));
    return p;
  } else
    return mem_malloc(size);
}

// Frees memory in a room
// Doesn't actually do anything
void RoomMemFree(void *buf) {
  if (!buf)
    return;

  if (Room_mem_buf) {
    ASSERT(((buf) >= Room_mem_buf) && ((buf) < (Room_mem_buf + Room_mem_size)));
  } else
    mem_free(buf);
}

// Initalize a room, allocating memory and filling in fields
// Parameters:	rp - the room to be initialized
//					nverts - how many vertices this room will have
//					nfaces - how many faces this room wil have
//					nportals - how many portals this room will have
void InitRoom(room *rp, int nverts, int nfaces, int nportals) {
  // initialize room fields
  rp->flags = 0;
  rp->objects = -1;
  rp->vis_effects = -1;
  rp->volume_lights = NULL;
  rp->mirror_face = -1;
  rp->num_mirror_faces = 0;
  rp->mirror_faces_list = NULL;
  rp->room_change_flags = 0;

#ifndef NEWEDITOR // the new editor must allow users to create a room from scratch
  ASSERT(nverts > 0);
  ASSERT(nfaces > 0);
#endif

  rp->wind = Zero_vector;

  rp->num_faces = nfaces;
  rp->num_verts = nverts;
  rp->num_portals = nportals;
  rp->last_render_time = 0;
  rp->fog_depth = 100.0;
  rp->fog_r = 1.0;
  rp->fog_g = 1.0;
  rp->fog_b = 1.0;

  rp->faces = (face *)RoomMemAlloc(nfaces * sizeof(*rp->faces));
  ASSERT(rp->faces != NULL);

  rp->num_bbf_regions = 0;

  rp->verts = (vector *)RoomMemAlloc(nverts * sizeof(*rp->verts));
  ASSERT(rp->verts != NULL);

  if (Katmai) {
    rp->verts4 = (vector4 *)mem_malloc(nverts * sizeof(*rp->verts4));
    ASSERT(rp->verts4 != NULL);
  }

  rp->pulse_time = 0;
  rp->pulse_offset = 0;

  if (nportals) {
    rp->portals = (portal *)RoomMemAlloc(nportals * sizeof(*rp->portals));
    ASSERT(rp->portals != NULL);
  } else
    rp->portals = NULL;

  // Default to no ambient sound
  rp->ambient_sound = -1;

  rp->name = NULL;
  rp->doorway_data = NULL;

  rp->env_reverb = 0; // reverb for sound system.

  rp->damage = 0.0;          // room damage
  rp->damage_type = PD_NONE; // room damage type

  rp->bn_info.num_nodes = 0;
  rp->bn_info.nodes = NULL;

#if (defined(EDITOR) || defined(NEWEDITOR))
  Room_multiplier[rp - std::data(Rooms)] = 1.0;

  Room_ambience_r[rp - std::data(Rooms)] = 0.0;
  Room_ambience_g[rp - std::data(Rooms)] = 0.0;
  Room_ambience_b[rp - std::data(Rooms)] = 0.0;
#endif

  rp->used = 1; // flag this room as used
}

// Initialize a room face structure.
void InitRoomFace(face *fp, int nverts) {
  fp->flags = 0;
  fp->num_verts = nverts;
  fp->portal_num = -1;
  fp->tmap = 0;

#ifdef NEWEDITOR
  ned_MarkTextureInUse(0, true);
#endif

  fp->lmi_handle = BAD_LMI_INDEX;
  fp->special_handle = BAD_SPECIAL_FACE_INDEX;
  fp->light_multiple = 4;

  fp->face_verts = (short *)RoomMemAlloc(nverts * sizeof(*fp->face_verts));
  ASSERT(fp->face_verts != NULL);
  fp->face_uvls = (roomUVL *)RoomMemAlloc(nverts * sizeof(*fp->face_uvls));
  ASSERT(fp->face_uvls != NULL);

  ASSERT(fp->face_verts);
  ASSERT(fp->face_uvls);
  for (int i = 0; i < nverts; i++)
    fp->face_uvls[i].alpha = 255;
}

// Finds out if we are in a room or outside the mine (-1 if we are outside)
int FindPointRoom(vector *pnt) {
  int i;

  ASSERT(pnt != NULL);

  for (i = 0; i <= Highest_room_index; i++) {
    if ((Rooms[i].used) && !(Rooms[i].flags & RF_EXTERNAL)) {
      bool f_in_room;

      f_in_room = fvi_QuickRoomCheck(pnt, &Rooms[i]);

      if (f_in_room == true)
        return i;
    }
  }

  return -1;
}

// Frees a room, deallocating its memory and marking it as unused
void FreeRoom(room *rp) {
  int i;
  int old_hri = Highest_room_index;

  ASSERT(rp->used != 0); // make sure room is un use

  // Free the faces
  for (i = 0; i < rp->num_faces; i++)
    FreeRoomFace(&rp->faces[i]);

  // Free up mem alloced for this room
  RoomMemFree(rp->faces);
  RoomMemFree(rp->portals);
  RoomMemFree(rp->verts);

  if (Katmai)
    mem_free(rp->verts4);

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

  BNode_FreeRoom(rp);

  if (rp->volume_lights)
    mem_free(rp->volume_lights);

  if (rp->name)
    mem_free(rp->name);

  if (rp->doorway_data)
    mem_free(rp->doorway_data);

  if (rp->mirror_faces_list)
    mem_free(rp->mirror_faces_list);

  rp->used = 0;

  // Update Highest_room_index
  if (ROOMNUM(rp) == Highest_room_index)
    while ((Highest_room_index >= 0) && (!Rooms[Highest_room_index].used))
      Highest_room_index--;

  BNode_RemapTerrainRooms(old_hri, Highest_room_index);
}

// Frees all the rooms currently in use, deallocating their memory and marking them as unused
void FreeAllRooms() {
  int rn;
  room *rp;
  mprintf(1, "Freeing rooms...Higest_room_index %d\n", Highest_room_index);
  for (rn = 0, rp = std::data(Rooms); rn <= Highest_room_index; rn++, rp++) {
    if (rp->used) {
      //			mprintf(2, "rn %d\n", rn);
      FreeRoom(rp);
    }
  }

  ASSERT(Highest_room_index == -1);

  RoomMemClose();

  //	mprintf(2,"Done\n");
}

#ifdef EDITOR
// Frees rooms that are in the room palette
void FreePaletteRooms() {
  int rn;
  room *rp;

  for (rn = MAX_ROOMS, rp = &Rooms[MAX_ROOMS]; rn < MAX_ROOMS + MAX_PALETTE_ROOMS; rn++, rp++)
    if (rp->used)
      FreeRoom(rp);
}
#endif

// Free the memory used by a room face structure
void FreeRoomFace(face *fp) {
  if (fp->lmi_handle != BAD_LMI_INDEX) {
    FreeLightmapInfo(fp->lmi_handle);
    fp->lmi_handle = BAD_LMI_INDEX;
    fp->flags &= ~FF_LIGHTMAP;
  }

  if (fp->special_handle != BAD_SPECIAL_FACE_INDEX) {
    FreeSpecialFace(fp->special_handle);
    fp->special_handle = BAD_SPECIAL_FACE_INDEX;
  }

  RoomMemFree(fp->face_verts);
  RoomMemFree(fp->face_uvls);
}

// Finds the center point of a room
// Parameters:	vp - filled in with the center point
//					rp - the room whose center to find
void ComputeRoomCenter(vector *vp, room *rp) {
  int i;

  vp->x = vp->y = vp->z = 0;

  for (i = 0; i < rp->num_verts; i++)
    *vp += rp->verts[i];

#ifdef NEWEDITOR
  if (rp->num_verts)
#endif
    *vp /= rp->num_verts;
}

// Computes the center point on a face by averaging the points in the face
void ComputeCenterPointOnFace(vector *vp, room *rp, int facenum) {
  face *fp = &rp->faces[facenum];
  int i;

  vp->x = vp->y = vp->z = 0;

  for (i = 0; i < fp->num_verts; i++)
    *vp += rp->verts[fp->face_verts[i]];

  *vp /= fp->num_verts;
}

// the minimum magnitude of a surface normal that we're willing to accept
#define MIN_NORMAL_MAG 0.035

// Computes (fills in) the surface normal of a face.
// Finds the best normal on this face by checking all sets of three vertices
// IMPORTANT:  The caller should really check the return value of this function
// Parameters:	rp,facenum - the room and face to calculate the normal for
// Returns:		true if the normal is ok
//					false if the normal has a very small (pre-normalization) magnitude
bool ComputeFaceNormal(room *rp, int facenum) {
  face *fp = &rp->faces[facenum];
  bool ok;

  ok = ComputeNormal(&fp->normal, fp->num_verts, fp->face_verts, rp->verts);

  if (!ok) {
    mprintf(1, "Warning: Low precision normal for room:face = %d:%d\n", ROOMNUM(rp), facenum);
  }

  return ok;
}

// Compute the surface normal from a list of vertices that determine a face
// Finds the best normal on this face by checking all sets of three vertices
// IMPORTANT:  The caller should really check the return value of this function
// Parameters:	normal - this is filled in with the normal
//					num_verts - how many vertices in the face
//					vertnum_list - a list of vertex numbers for this face.  these index into verts
//					verts - the array of vertices into which the elements of vertnum_list index
// Returns:		true if the normal is ok
//					false if the normal has a very small (pre-normalization) magnitude
bool ComputeNormal(vector *normal, int num_verts, short *vertnum_list, vector *verts) {
  int i;
  float largest_mag;

  i = 0;
  largest_mag = 0.0;

  for (i = 0; i < num_verts; i++) {
    vector tnormal;
    float mag;

    mag = vm_GetNormal(&tnormal, &verts[vertnum_list[i]], &verts[vertnum_list[(i + 1) % num_verts]],
                       &verts[vertnum_list[(i + 2) % num_verts]]);

    if (mag > largest_mag) {
      *normal = tnormal;
      largest_mag = mag;
    }
  }

  if (largest_mag < MIN_NORMAL_MAG) {
    mprintf(1, "Warning: Normal has low precision. mag = %f, norm =  %f,%f,%f\n",
            largest_mag,
            normal->x,
            normal->y,
            normal->z);
    return 0;
  } else
    return 1;
}

// Computes the center point on a face by averaging the points in the portal
void ComputePortalCenter(vector *vp, room *rp, int portal_index) {
  portal *pp = &rp->portals[portal_index];
  face *fp = &rp->faces[pp->portal_face];
  int i;

  vm_MakeZero(vp);

  for (i = 0; i < fp->num_verts; i++)
    *vp += rp->verts[fp->face_verts[i]];

  *vp /= fp->num_verts;
}

// Clears lightmaps for a single room
void ClearRoomLightmaps(int roomnum) {
  int t;

  ASSERT(Rooms[roomnum].used);

  for (t = 0; t < Rooms[roomnum].num_faces; t++) {
    if (Rooms[roomnum].faces[t].lmi_handle != BAD_LMI_INDEX) {
      FreeLightmapInfo(Rooms[roomnum].faces[t].lmi_handle);
      Rooms[roomnum].faces[t].lmi_handle = BAD_LMI_INDEX;
      Rooms[roomnum].faces[t].flags &= ~FF_LIGHTMAP;
    }
  }
}

// Removes all room lightmaps from memory and sets indoor faces accordingly
// External=1 means to perform the operation on external rooms only, 0 means indoor rooms only
void ClearAllRoomLightmaps(int external) {
  int i;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (external && !(Rooms[i].flags & RF_EXTERNAL))
        continue;
      if (!external && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      ClearRoomLightmaps(i);
    }
  }
}

// Clears specmaps for a single room
void ClearRoomSpecmaps(int roomnum) {
  int t;

  ASSERT(Rooms[roomnum].used);

  for (t = 0; t < Rooms[roomnum].num_faces; t++) {
    if (Rooms[roomnum].faces[t].special_handle != BAD_SPECIAL_FACE_INDEX) {
      if (SpecialFaces[Rooms[roomnum].faces[t].special_handle].type == SFT_SPECULAR) {
        FreeSpecialFace(Rooms[roomnum].faces[t].special_handle);
        Rooms[roomnum].faces[t].special_handle = BAD_SPECIAL_FACE_INDEX;
      }
    }
  }
}

// Removes all room specularity maps from memory and sets indoor faces accordingly
// External=1 means to perform the operation on external rooms only, 0 means indoor rooms only
void ClearAllRoomSpecmaps(int external) {
  int i;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if (external && !(Rooms[i].flags & RF_EXTERNAL))
        continue;
      if (!external && (Rooms[i].flags & RF_EXTERNAL))
        continue;

      ClearRoomSpecmaps(i);
    }
  }
}

// Removes all room volume lights from memory
void ClearVolumeLights(int roomnum) {
  ASSERT(Rooms[roomnum].used);

  ASSERT(!(Rooms[roomnum].flags & RF_EXTERNAL));

  if (Rooms[roomnum].volume_lights) {
    mem_free(Rooms[roomnum].volume_lights);
    Rooms[roomnum].volume_lights = NULL;
  }
}

// Removes all room volume lights from memory
void ClearAllVolumeLights() {
  int i;

  for (i = 0; i < MAX_ROOMS; i++) {
    if (Rooms[i].used) {
      if ((Rooms[i].flags & RF_EXTERNAL))
        continue;

      ClearVolumeLights(i);
    }
  }
}

// Returns the area taken up by a face
float GetAreaForFace(room *rp, int facenum) {
  ASSERT(rp->used > 0);
  ASSERT(facenum >= 0 && facenum < rp->num_faces);

  face *fp = &rp->faces[facenum];
  int i;
  vector normal;
  float area = 0;

  vm_GetPerp(&normal, &rp->verts[fp->face_verts[0]], &rp->verts[fp->face_verts[1]], &rp->verts[fp->face_verts[2]]);
  area = (vm_GetMagnitude(&normal) / 2);

  for (i = 2; i < fp->num_verts - 1; i++) {
    vm_GetPerp(&normal, &rp->verts[fp->face_verts[0]], &rp->verts[fp->face_verts[i]],
               &rp->verts[fp->face_verts[i + 1]]);
    area += (vm_GetMagnitude(&normal) / 2);
  }

  return area;
}

// Returns indeces of the two elements of points on a face to use as a 2d projection
// Parameters:	normal - the surface normal of the face
//					ii,jj - filled in with elements numbers (0,1, or 2)
void GetIJ(const vector *normal, int *ii, int *jj) {

  // To project onto 2d, find the largest element of the surface normal
  if (fabs(normal->x) > fabs(normal->y))
    if (fabs(normal->x) > fabs(normal->z)) {
      if (normal->x > 0) {
        *ii = 2;
        *jj = 1; // x > y, x > z
      } else {
        *ii = 1;
        *jj = 2;
      }
    } else {
      if (normal->z > 0) {
        *ii = 1;
        *jj = 0; // z > x > y
      } else {
        *ii = 0;
        *jj = 1;
      }
    }
  else // y > x
    if (fabs(normal->y) > fabs(normal->z)) {
      if (normal->y > 0) {
        *ii = 0;
        *jj = 2; // y > x, y > z
      } else {
        *ii = 2;
        *jj = 0;
      }
    } else {
      if (normal->z > 0) {
        *ii = 1;
        *jj = 0; // z > y > x
      } else {
        *ii = 0;
        *jj = 1;
      }
    }
}

// 2d cross product
#define cross(v0, v1) (((v0)[ii] * (v1)[jj]) - ((v0)[jj] * (v1)[ii]))

// Finds the uv coords of a given point on a room:face.  Fills in u & v.
// Parameters:	u,v - pointers to variables to be filled in
//					pnt - the point we're checking
//					rp - pointer to the room that pnt is in
//					fp - pointer to the face that pnt is on
void FindPointUV(float *u, float *v, const vector *pnt, const room *rp, const face *fp) {
  int roomnum = ROOMNUM(rp);
  int ii, jj;
  vector vec0, vec1;
  float *p1, *checkp, *v0, *v1;
  float k0, k1;
  int t;

  // Make sure we have a valid room
  ASSERT((roomnum >= 0) && (roomnum <= Highest_room_index));

  // Find what plane to project this wall onto to make it a 2d case
  GetIJ(&fp->normal, &ii, &jj);

  // Compute delta vectors
  vec0 = rp->verts[fp->face_verts[0]] - rp->verts[fp->face_verts[1]]; // vec from 1 -> 0
  vec1 = rp->verts[fp->face_verts[2]] - rp->verts[fp->face_verts[1]]; // vec from 1 -> 0

  // Get pointers to referece our vectors as arrays of floats
  p1 = (float *)&rp->verts[fp->face_verts[1]];
  v0 = (float *)&vec0;
  v1 = (float *)&vec1;
  checkp = (float *)pnt;

  // Compute our clipping values along i & j axes
  k1 = -(cross(checkp, v0) + cross(v0, p1)) / cross(v0, v1);
  t = (fabs(v0[ii]) > fabs(v0[jj])) ? ii : jj;
  k0 = ((-k1 * v1[t]) + checkp[t] - p1[t]) / v0[t];

  // Compute u & v values
  *u = fp->face_uvls[1].u + (k0 * (fp->face_uvls[0].u - fp->face_uvls[1].u)) +
       (k1 * (fp->face_uvls[2].u - fp->face_uvls[1].u));
  *v = fp->face_uvls[1].v + (k0 * (fp->face_uvls[0].v - fp->face_uvls[1].v)) +
       (k1 * (fp->face_uvls[2].v - fp->face_uvls[1].v));
}

// Check if a particular point on a wall is a transparent pixel
// Parameters:	pnt - the point we're checking
//					rp - pointer to the room that pnt is in
//					facenum - the face that pnt is on
// Returns:	true if can pass through the given point, else 0
int CheckTransparentPoint(const vector *pnt, const room *rp, const int facenum) {
  int bm_handle;
  face *fp = &rp->faces[facenum];
  float u, v;
  int w, h, x, y;

  return false;

  // Get the UV coordindates of the point we hit
  FindPointUV(&u, &v, pnt, rp, fp);

  // Get pointer to the bitmap data
  bm_handle = GetTextureBitmap(fp->tmap, 0);

  // Get x & y coordindates (in bitmap) of check point
  w = bm_w(bm_handle, 0);
  h = bm_h(bm_handle, 0);
  x = ((int)(u * w)) % w;
  y = ((int)(v * h)) % h;

  // Return true if the check point is transparent
  return bm_pixel_transparent(bm_handle, x, y);
}

// Computes a bounding sphere for the current room
// Parameters: center - filled in with the center point of the sphere
//		rp - the room we’re bounding
// Returns: the radius of the bounding sphere
float ComputeRoomBoundingSphere(vector *center, room *rp) {
  // This algorithm is from Graphics Gems I.  There's a better algorithm in Graphics Gems III that
  // we should probably implement sometime.

  vector *min_x, *max_x, *min_y, *max_y, *min_z, *max_z, *vp;
  float dx, dy, dz;
  float rad, rad2;
  int i;

#ifdef NEWEDITOR
  if (!rp->num_verts) {
    center->x = 0.0f;
    center->y = 0.0f;
    center->z = 0.0f;
    return 0.0f;
  }
#endif

  // Initialize min, max vars
  min_x = max_x = min_y = max_y = min_z = max_z = &rp->verts[0];

  // First, find the points with the min & max x,y, & z coordinates
  for (i = 0, vp = rp->verts; i < rp->num_verts; i++, vp++) {

    if (vp->x < min_x->x)
      min_x = vp;

    if (vp->x > max_x->x)
      max_x = vp;

    if (vp->y < min_y->y)
      min_y = vp;

    if (vp->y > max_y->y)
      max_y = vp;

    if (vp->z < min_z->z)
      min_z = vp;

    if (vp->z > max_z->z)
      max_z = vp;
  }

  // Calculate initial sphere

  dx = vm_VectorDistance(min_x, max_x);
  dy = vm_VectorDistance(min_y, max_y);
  dz = vm_VectorDistance(min_z, max_z);

  if (dx > dy)
    if (dx > dz) {
      *center = (*min_x + *max_x) / 2;
      rad = dx / 2;
    } else {
      *center = (*min_z + *max_z) / 2;
      rad = dz / 2;
    }
  else if (dy > dz) {
    *center = (*min_y + *max_y) / 2;
    rad = dy / 2;
  } else {
    *center = (*min_z + *max_z) / 2;
    rad = dz / 2;
  }

  // Go through all points and look for ones that don't fit
  rad2 = rad * rad;
  for (i = 0, vp = rp->verts; i < rp->num_verts; i++, vp++) {
    vector delta;
    float t2;

    delta = *vp - *center;
    t2 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;

    // If point outside, make the sphere bigger
    if (t2 > rad2) {
      float t;

      t = sqrt(t2);
      rad = (rad + t) / 2;
      rad2 = rad * rad;
      *center += delta * (t - rad) / t;
    }
  }

  // We're done
  return rad;
}

// Create objects for the external rooms
void CreateRoomObjects() {
  int objnum, r;
  room *rp;

  // First delete any old room objects
  for (objnum = 0; objnum <= Highest_object_index; objnum++)
    if (Objects[objnum].type == OBJ_ROOM)
      ObjDelete(objnum);

  // Now go through all rooms & create objects for external ones
  for (r = 0, rp = std::data(Rooms); r <= Highest_room_index; r++, rp++)
    if (rp->used && (rp->flags & RF_EXTERNAL)) {
      vector pos;
      float rad;
      int roomnum, objnum;

      rad = ComputeRoomBoundingSphere(&pos, rp);
      roomnum = GetTerrainRoomFromPos(&pos);

      ASSERT(roomnum != -1);

      objnum = ObjCreate(OBJ_ROOM, r, roomnum, &pos, NULL);
      ASSERT(objnum != -1); // DAJ -1FIX moved up
      Objects[objnum].size = rad;
      Objects[objnum].wall_sphere_offset = Zero_vector;
      Objects[objnum].anim_sphere_offset = Zero_vector;

      if ((rad >= MIN_BIG_OBJ_RAD) && !(Objects[objnum].flags & OF_BIG_OBJECT)) {
        BigObjAdd(objnum);
      }
      // Type specific should have set up the size, so now we can compute the bounding box.
      ObjSetAABB(&Objects[objnum]);
    }
}

// returns the index of the first room that is being used.  Returns -1 if there are none
int FindFirstUsedRoom() {
  int i;

  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used) {
      return i;
    }
  }

  Int3(); // Get Jason or Matt, no rooms in use!
  return -1;
}

// Changes a face's texture within a room
//	returns true on successs
bool ChangeRoomFaceTexture(int room_num, int face_num, int texture) {
  if ((room_num < 0) || (room_num > Highest_room_index) || ROOMNUM_OUTSIDE(room_num) || (!Rooms[room_num].used)) {
    mprintf(0, "Invalid room passed to ChangeRoomFaceTexture\n");
    Int3();
    return false;
  }

  room *rp = &Rooms[room_num];

  if (face_num < 0 || face_num >= rp->num_faces) {
    mprintf(0, "Invalid face number passed to ChangeRoomFaceTexture."
               "  Room=%d, you gave face #%d, there are only %d in the room\n",
             room_num, face_num, rp->num_faces);
    Int3();
    return false;
  }

  if (texture == -1) {
    mprintf(0, "not a valid texture, passed to ChangeRoomFaceTexture\n");
    Int3();
    return false;
  }

  face *fp = &rp->faces[face_num];

  fp->tmap = texture;
  fp->flags |= FF_TEXTURE_CHANGED;
  rp->room_change_flags |= RCF_TEXTURE;
  return true;
}

// Clears the data for room changes
void ClearRoomChanges() {
  for (int i = 0; i < MAX_ROOM_CHANGES; i++) {
    Room_changes[i].used = 0;
  }
}

// Returns index of room change allocatd, else -1 on error
int AllocRoomChange() {
  for (int i = 0; i < MAX_ROOM_CHANGES; i++) {
    if (Room_changes[i].used == 0) {
      memset(&Room_changes[i], 0, sizeof(room_changes));
      Room_changes[i].used = 1;
      return i;
    }
  }

  Int3(); // Couldn't allocate room change!
  return -1;
}

// Does whatever fading/changing of room stuff that needs to be done this frame
void DoRoomChangeFrame() {
  int i;
  for (i = 0; i < MAX_ROOM_CHANGES; i++) {
    if (!Room_changes[i].used)
      continue;

    room *rp = &Rooms[Room_changes[i].roomnum];

    float norm = (Gametime - Room_changes[i].start_time) / Room_changes[i].total_time;

    if (norm > 1)
      norm = 1.0;

    if (Room_changes[i].fog) {

      vector scale_color =
          ((Room_changes[i].end_vector - Room_changes[i].start_vector) * norm) + Room_changes[i].start_vector;
      float scale_depth =
          ((Room_changes[i].end_depth - Room_changes[i].start_depth) * norm) + Room_changes[i].start_depth;

      rp->flags |= RF_FOG;
      rp->room_change_flags |= RCF_CHANGING_WIND_FOG;

      rp->fog_r = scale_color.x;
      rp->fog_g = scale_color.y;
      rp->fog_b = scale_color.z;
      rp->fog_depth = scale_depth;
    } else {
      vector scale_wind =
          ((Room_changes[i].end_vector - Room_changes[i].start_vector) * norm) + Room_changes[i].start_vector;

      rp->room_change_flags |= RCF_CHANGING_WIND_FOG;
      rp->wind = scale_wind;
    }

    // If this room is done changing, take it out of the list and mark it as changed
    if (norm >= 1.0) {
      Room_changes[i].used = 0;
      if (Room_changes[i].fog)
        rp->room_change_flags |= RCF_FOG;
      else
        rp->room_change_flags |= RCF_WIND;

      rp->room_change_flags &= ~RCF_CHANGING_WIND_FOG;

      continue;
    }
  }
}

// Sets up a room to change its fog or wind over time
int SetRoomChangeOverTime(int roomnum, bool fog, vector *end, float depth_end, float time) {
  room *rp = &Rooms[roomnum];
  int index, i;

  // First search to see if there is another with this same roomnum

  int found = 0;
  for (i = 0; i < MAX_ROOM_CHANGES && !found; i++) {
    if (Room_changes[i].used && Room_changes[i].roomnum == roomnum && Room_changes[i].fog == fog) {
      found = 1;
      index = i;
    }
  }

  if (!found) {
    index = AllocRoomChange();
    if (index < 0)
      return -1; // failed get free slot!
  }

  Room_changes[index].roomnum = roomnum;
  Room_changes[index].fog = fog;
  Room_changes[index].end_vector = *end;
  Room_changes[index].start_time = Gametime;
  Room_changes[index].total_time = time;
  rp->room_change_flags |= RCF_CHANGING_WIND_FOG;

  if (fog) {
    Room_changes[index].start_depth = rp->fog_depth;
    Room_changes[index].start_vector.x = rp->fog_r;
    Room_changes[index].start_vector.y = rp->fog_g;
    Room_changes[index].start_vector.z = rp->fog_b;
    Room_changes[index].end_depth = depth_end;
  } else
    Room_changes[index].start_vector = rp->wind;

  return index;
}
