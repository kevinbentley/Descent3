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

 * $Logfile: /DescentIII/main/room.h $
 * $Revision: 104 $
 * $Date: 5/05/99 5:03a $
 * $Author: Gwar $
 *
 * Room structures & functions
 *
 * $Log: /DescentIII/main/room.h $
 *
 * 104   5/05/99 5:03a Gwar
 * renamed ned_GameTextures array to GameTextures in new editor to make
 * game code happy; 3D texture view still does not display textures
 *
 * 103   4/30/99 12:56p Kevin
 * Lowered values for MAX_SOUNDS, MAX_ROOMS, MAX_TEXTURES and MAX_OBJIDS.
 * Talk to me before changing any of these again.
 *
 * 102   4/21/99 5:33a Gwar
 * added a NEWEDITOR #define
 *
 * 101   3/24/99 3:27p Matt
 * Increased the max number of room changes from 20 to 100.
 *
 * 100   2/09/99 9:59a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 99    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 98    1/21/99 11:34a Matt
 * Got rid of portal triggers.  Since we don't have multi-face portals, a
 * face trigger works fine for a portal.  Also fixed a few editor/trigger
 * bugs.
 *
 * 97    1/21/99 11:20a Jason
 * added a two new flags: strobe and flicker
 *
 * 96    1/20/99 6:11p Matt
 * Fixed a couple bugs in the room wind/fog change system, and make the
 * values change from current -> new instead of start -> end.
 *
 * 95    1/19/99 11:25a Jason
 * added room (fog and wind) changing functions
 *
 * 94    1/15/99 3:14p Jason
 * added combinable portals
 *
 * 93    1/11/99 11:17a Jason
 * made fog not have that stupid telltale z problem
 *
 * 92    1/08/99 5:37p Samir
 * reverb values per room.
 *
 * 91    12/22/98 2:03p Matt
 * Added room names, and made rooms not compress so that room numbers are
 * suitable for persistant uses.
 *
 * 90    11/30/98 3:59p Jason
 * changed dynamic lighting to be better
 *
 * 89    11/02/98 6:15p Chris
 * Room AABBs get saved with the level and the sort_face and dec_sort_face
 * list s have been removed
 *
 * 88    10/06/98 6:08p Jason
 * added RF_TRIANGULATE so that special rooms (with non-planar UVS) can be
 * drawn correctly
 *
 * 87    10/01/98 10:33a Jason
 * added room_change_flags
 *
 * 86    9/22/98 6:58p Samir
 * Render_floating_triggers is _DEBUG code, so make it so.
 *
 * 85    9/22/98 3:55p Samir
 * ifdef out stuff for non-debug version.
 *
 * 84    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 83    9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 82    8/28/98 4:44p Jason
 * optimized mirror rendering
 *
 * 81    8/27/98 5:19p Jason
 * added first rev of reflected surfaces
 *
 * 80    8/19/98 2:17p Jeff
 * made a function to change the texture on a face
 *
 * 79    8/17/98 6:40p Matt
 * Added ambient sound system
 *
 * 78    7/21/98 2:14p Chris
 * Some FVI speedups - not done
 *
 * 77    7/17/98 9:56a Chris
 * Intermediate checkin
 *
 * 76    7/16/98 8:29p Chris
 * Partial implementation of the new collide code
 *
 * 75    7/16/98 12:06p Jason
 * added special flags to room structure
 *
 * 74    6/08/98 12:28p Matt
 * Removed unused face flag, and changed some commenting.
 *
 * 73    6/05/98 5:22p Jason
 * added volumetric fog
 *
 * 72    6/02/98 6:03p Jason
 * added specular lightmaps
 *
 * 71    5/26/98 5:56p Jason
 * only render coronas which are flagged
 *
 * 70    5/25/98 3:46p Jason
 * added better light glows
 *
 * 69    5/22/98 3:26p Jason
 * added better memory management for specular lighting
 *
 * 68    5/22/98 12:34p Matt
 * Added scorch mark/bullet hole system.
 *
 * 67    5/15/98 5:41p Jason
 * implemented volume lighting system
 *
 * 66    5/06/98 12:55p Jason
 * did some vis effect optimizations
 *
 * 65    4/30/98 5:50p Jason
 * more framerate optimizations
 *
 * 64    4/30/98 12:37p Jason
 * added FF_FACING for non-backfaces
 *
 * 63    4/22/98 12:38p Chris
 * Added path points to portals and rooms.  Improved BOA auto-making
 * process.
 *
 * 62    4/02/98 12:24p Jason
 * trimmed some fat from our structures
 *
 * 61    3/18/98 4:31p Chris
 * Speed up fvi and fixed some bugs
 *
 * 60    3/16/98 6:41p Jason
 * added goal room stuff
 *
 * 59    3/16/98 5:50p Chris
 * Added sorted face lists for fvi
 *
 * 58    3/13/98 12:05p Matt
 * Changed the way we determine whether to render past a closed door to
 * fix a render bug when the viewer is in a door room.
 * Moved FaceIsRenderabl(), GetFaceAlpha(), and RenderPastPortal() from
 * room.h to render.cpp.
 *
 * 57    3/06/98 3:23p Jason
 * added lighting from satellites to indoor rooms
 *
 * 56    2/23/98 6:50p Jason
 * changes to help facilitate fast lighting with shadow volumes
 *
 *
 * 55    2/18/98 1:21p Jason
 * upped max lightmap count
 *
 * 54    2/11/98 7:01p Chris
 * Started to add wind
 *
 * 53    2/11/98 11:48a Matt
 * Fixed alignment in room struct.
 *
 * 52    2/10/98 7:45p Matt
 * Added (probably temporary) flags for goals
 *
 * 51    2/10/98 3:49p Jason
 * added pulsing walls
 *
 * 50    2/10/98 1:12p Jason
 * added forcefields and saturating walls
 *
 * 49    2/04/98 8:25p Jason
 * added light multiplier for faces
 *
 * 48    2/02/98 7:07p Matt
 * Added support for doors that can be seen through even when closed
 *
 * 47    2/02/98 5:13p Matt
 * Added more generic function to compute a surface normal for a face
 *
 * 46    1/20/98 12:10p Jason
 * implemented vis effect system
 *
 * 45    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 44    1/15/98 3:47p Jason
 * sped up room rendering on the terrain
 *
 * 43    1/12/98 3:34p Jason
 * sped up indoor rendering by clipping faces against portals
 *
 * 42    11/24/97 1:30a Jason
 * first attempt at adding shadows
 *
 * 41    11/14/97 9:02p Mark
 * Increased the number of rooms from 100 to 500 (Matt on Mark's machine)
 *
 * 40    11/14/97 6:39p Jason
 * added ability to do lighting on a single room
 *
 * 39    10/13/97 5:08p Matt
 * Moved ComputeRoomBoundingSphere() & CreateRoomObjects() from editor to
 * main
 *
 *
 * 38    10/10/97 11:38a Jason
 * put in better volumetric support
 *
 * 37    10/08/97 2:28p Jason
 * got external rooms working with terrain lighting
 *
 * 36    10/01/97 7:51p Matt
 * Added code for external rooms
 *
 * 35    9/19/97 8:09p Jason
 * optimizations for dynamic lighting
 *
 * 34    9/19/97 2:52p Jason
 * changes to fix lightmap seam problem
 *
 * 33    9/17/97 6:14p Jason
 * did some optimizations due to running vtune
 *
 * 32    9/16/97 4:27p Matt
 * Got rid of static_light & changed fields in the room struct
 *
 * 31    9/16/97 1:07a Matt
 * Fixed rendering past open doors
 *
 * 30    9/15/97 5:33p Jason
 * made portals check for doors
 *
 * 29    9/12/97 5:38p Jason
 * got doors working
 *
 * 28    9/12/97 2:35p Matt
 * Changed face flags to a word, and added destroyed flag
 *
 * 27    9/11/97 3:13p Matt
 * Several more-or-less small changes, mostly with portal triggers
 *
 * 26    9/10/97 5:13p Matt
 * Changed some flags & added a few functions
 *
 * 25    9/09/97 12:21p Matt
 * Added new flags, deleted old ones, renamed others
 * Added new functions
 * Cleaned up structs, fixing alignment
 *
 * 24    9/06/97 10:53p Matt
 * Added portal and face flags
 *
 * 23    9/04/97 11:23a Jason
 * sped up dynamic light computation a bit
 *
 * 22    9/02/97 5:17p Jason
 * changes for dynamic lighting
 *
 * 21    9/02/97 12:55p Jason
 * classify faces as alphaed or not
 *
 * 20    8/28/97 12:31p Jason
 * added hi-res lightmaps for radiosity
 *
 * 19    8/19/97 1:13p Jason
 * added GetAreaForFace function
 *
 * 18    8/13/97 11:53a Jason
 * moved ClearAllRoomLightmaps into room.cpp where it belongs
 *
 * 17    8/12/97 3:51p Jason
 * tweaked lightmaps with radiosity
 *
 * 16    8/12/97 1:13p Chris
 * Added AABBs.
 *
 * 15    8/12/97 1:10a Jason
 * added code to support radiosity lighting
 *
 * 14    8/11/97 3:55p Chris
 * Added a function to compute the rough center of a portal
 *
 * 13    8/04/97 5:35p Chris
 *
 * 12    8/01/97 4:38p Chris
 *
 * 11    7/18/97 5:36p Jason
 * save changed paletted rooms on exit
 *
 * 10    7/17/97 11:50a Jason
 * Upped max_Verts_per_face to 64
 *
 * 9     7/16/97 1:50p Sean
 * from JASON: upped max face limit to 3000
 *
 * 8     6/30/97 1:30p Jason
 * added netherspace stuff
 *
 * 7     6/27/97 4:15p Jason
 * added more room functions
 *
 * 6     6/27/97 3:04p Jason
 * added cool room stuff
 *
 * 5     6/26/97 2:37p Jason
 * added combine_faces function and texturing to rooms
 *
 * 4     6/25/97 5:29p Jason
 * added/modified code to display a room
 *
 * 3     6/24/97 1:51p Jason
 *
 * 2     6/18/97 12:40p Jason
 * added include files
 *
 * 1     6/18/97 12:39p Jason
 *
 * $NoKeywords: $
 */

#ifndef _ROOM_H
#define _ROOM_H

#include "vecmat_external.h"
#include "gametexture.h"
#include "bitmap.h"

#ifdef NEWEDITOR
#include "..\neweditor\ned_GameTexture.h"
#endif

#include "room_external.h"

// Sizes for some global arrays
#define MAX_ROOMS 400 // max number of rooms in the world

// Constants for room palette (editor-specific)
#if (defined(EDITOR) || defined(NEWEDITOR))
#define FIRST_PALETTE_ROOM MAX_ROOMS // start of rooms for palette
#define MAX_PALETTE_ROOMS 50         // max number of loaded rooms
#else
#define MAX_PALETTE_ROOMS 0 // max number of loaded rooms
#endif

// Room change stuff
#define MAX_ROOM_CHANGES 100
struct room_changes {
  int roomnum;
  bool fog;
  vector start_vector, end_vector;
  float start_depth, end_depth;
  float start_time;
  float total_time;
  uint8_t used;
};

//
// Globals
//

extern room Rooms[];           // global sparse array of rooms
extern int Highest_room_index; // index of highest-numbered room

//
// Macros
//

// Handy macro to convert a room ptr to a room number
#define ROOMNUM(r) (r - Rooms)

// See above from RF_MINE_MASK
#define MINE_INDEX(x) ((Rooms[x].flags & RFM_MINE) >> 20)

//
// Functions
//

// Zeroes out the rooms array
void InitRooms();

#ifdef _DEBUG
// Allows a spew'er to find out if he is in a room or external to the mine
// NOTE:  THIS FUNCTION IS NOT FOR IN GAME STUFF.  It is REALLY SLOW and accurate.
// Talk to Chris if you need something like this function.
int FindPointRoom(vector *pnt);

// Put this here so we don't need to include render.h
extern bool Render_floating_triggers;

#endif

// Initalize a room, allocating memory and filling in fields
// Parameters:	rp - the room to be initialized
//					nverts - how many vertices this room will have
//					nfaces - how many faces this room wil have
//					nfaces - how many portals this room wil have
void InitRoom(room *rp, int nverts, int nfaces, int nportals);

// Initialize a room face structure, allocating memory for vertlist and uvls
void InitRoomFace(face *fp, int nverts);

// Frees a room, deallocating its memory and marking it as unused
void FreeRoom(room *rp);

// Frees all the rooms currently in use, deallocating their memory and marking them as unused
void FreeAllRooms();

// Finds the center point of a room
// Parameters:	vp - filled in with the center point
//					rp - the room whose center to find
void ComputeRoomCenter(vector *vp, room *rp);

// Computes (fills in) the surface normal of a face.
// Finds the best normal on this face by checking all sets of three vertices
// IMPORTANT:  The caller should really check the return value of this function
// Parameters:	rp,facenum - the room and face to calculate the normal for
// Returns:		true if the normal is ok
//					false if the normal has a very small (pre-normalization) magnitude
bool ComputeFaceNormal(room *rp, int facenum);

// Compute the surface normal from a list of vertices that determine a face
// Finds the best normal on this face by checking all sets of three vertices
// IMPORTANT:  The caller should really check the return value of this function
// Parameters:	normal - this is filled in with the normal
//					num_verts - how many vertices in the face
//					vertnum_list - a list of vertex numbers for this face.  these index into verts
//					verts - the array of vertices into which the elements of vertnum_list index
// Returns:		true if the normal is ok
//					false if the normal has a very small (pre-normalization) magnitude
bool ComputeNormal(vector *normal, int num_verts, short *vertnum_list, vector *verts);

// Finds the center point of a portal by averaging the points in the portal
// Parameters:	vp           - filled in with the center point
//					rp           - the room
//					portal_index - the index of the portal whose center to find
void ComputePortalCenter(vector *vp, room *rp, int portal_index);

// Computes the center point on a face by averaging the points in the face
void ComputeCenterPointOnFace(vector *vp, room *rp, int facenum);

// Free the memory used by a room face structure
void FreeRoomFace(face *fp);

// Removes all room lightmaps from memory and sets indoor faces accordingly
void ClearAllRoomLightmaps(int external);

// Removes all room volume lights from memory
void ClearAllVolumeLights();

// Returns the area taken up by a face
float GetAreaForFace(room *rp, int facenum);

// Check if a particular point on a wall is a transparent pixel
// Parameters:	pnt - the point we're checking
//					rp - pointer to the room that pnt is in
//					facenum - the face that pnt is on
// Returns:	true if can pass through the given point, else 0
int CheckTransparentPoint(const vector *pnt, const room *rp, const int facenum);

// Face physics flags returned by GetFacePhysicsFlags()
// Note that:
//  it is illegal for a face to have both SOLID and TRANSPARENT
//  it is legal, but probably not of interest, for a face to have SOLID & PORTAL
#define FPF_SOLID 1       // nothing passes through this face
#define FPF_TRANSPARENT 2 // face has transparency, so some things may be able to fly through it
#define FPF_PORTAL 4      // this face is in a portal.
#define FPF_RECORD 8      // take note of when an object passes through this face

// Face physics types.  These are combinations of the above flags
#define FPT_IGNORE 0 // completey ignore this face

// Figure out how the physics should deal with a given face
// Parameters:	rp - pointer to the room the face is in
//					fp - the face we're interested in
// Returns:	bitmask of flags (see above).
static inline int GetFacePhysicsFlags(const room *rp, const face *fp) {
  int ret = 0;

  // If face is a trigger, must record
  if (fp->flags & FF_HAS_TRIGGER)
    ret |= FPF_RECORD;

  // If it's a floating trigger, then we're done
  if (fp->flags & FF_FLOATING_TRIG)
    return ret;

  if (fp->flags & FF_VOLUMETRIC)
    return ret;

  // Deal with faces that are part of a portal
  if (fp->portal_num != -1) {
    portal *pp = &rp->portals[fp->portal_num];

    // Mark as portal
    ret |= FPF_PORTAL;

    // Face is flythrough if we don't render the portal faces, or it's marked rendered flythrough
    if (!(pp->flags & PF_RENDER_FACES) || (pp->flags & PF_RENDERED_FLYTHROUGH))
      return ret;
  }

  // If we're here, it's either a non-portal face, or portal face that gets rendered

  // Check if the face is marked fly-through
  if (GameTextures[fp->tmap].flags & TF_FLY_THRU)
    return ret;

  // Check if the face is solid or transparent
  int bm_handle = GetTextureBitmap(fp->tmap, 0);
  if (GameBitmaps[bm_handle].flags & BF_TRANSPARENT)
    ret |= FPF_TRANSPARENT;
  else
    ret |= FPF_SOLID;

  // We're done
  return ret;
}

// Computes a bounding sphere for the current room
// Parameters: center - filled in with the center point of the sphere
//		rp - the room we’re bounding
// Returns: the radius of the bounding sphere
float ComputeRoomBoundingSphere(vector *center, room *rp);

// Create objects for the external rooms
void CreateRoomObjects();

// Clears lightmaps for a single room
void ClearRoomLightmaps(int roomnum);

// returns the index of the first room that is being used.  Returns -1 if there are none
int FindFirstUsedRoom();

// Clears specmaps for a single room
void ClearRoomSpecmaps(int roomnum);

// Removes all room specularity maps from memory and sets indoor faces accordingly
// External=1 means to perform the operation on external rooms only, 0 means indoor rooms only
void ClearAllRoomSpecmaps(int external);

extern void GetIJ(const vector *normal, int *ii, int *jj);

// Changes a face's texture within a room
//	returns true on successs
bool ChangeRoomFaceTexture(int room_num, int face_num, int texture);

// Clears the data for room changes
void ClearRoomChanges();

// Returns index of room change allocatd, else -1 on error
int AllocRoomChange();

// Does whatever fading/changing of room stuff that needs to be done this frame
void DoRoomChangeFrame();

// Sets up a room to change its fog or wind over time
int SetRoomChangeOverTime(int roomnum, bool fog, vector *end, float depth_end, float time);

#endif
