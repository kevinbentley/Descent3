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

 * $Logfile: /DescentIII/Main/editor/Group.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Functions for copying, pasting, etc. of groups
 *
 * $Log: not supported by cvs2svn $
 *
 * 35    9/15/99 1:56p Matt
 * Added the option to allow rooms or groups placed on the terrain to
 * either align with the terrain or with gravity.
 *
 * 34    8/30/99 1:01p Gwar
 * use the "true" center of faces for determining place position of a
 * group
 *
 * 33    8/17/99 6:12p Gwar
 * handle NEWEDITOR generic object management in AttachGroup
 *
 * 32    8/17/99 6:46a Gwar
 * added group support to NEWEDITOR
 *
 * 31    5/08/99 1:39a Matt
 * Added a function to delete all objects of a certain type, and support
 * for placing and attaching groups to the terrain.
 *
 * 30    4/21/99 10:19p Matt
 * DeleteGroup() wasn't setting the world changed flag
 *
 * 29    3/15/99 1:29p Matt
 * Added objects & triggers to save/load for groups.
 *
 * 28    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 27    1/26/99 6:02p Matt
 * Fixed (I hope) a problem with pasted object having the wrong
 * orientation.
 *
 * 26    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 25    1/21/99 11:34a Matt
 * Got rid of portal triggers.  Since we don't have multi-face portals, a
 * face trigger works fine for a portal.  Also fixed a few editor/trigger
 * bugs.
 *
 * 24    1/14/99 11:06a Matt
 * Added names to triggers
 *
 * 23    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 22    12/01/98 11:17p Matt
 * Made copy/paste work with doors.
 *
 * 21    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 20    9/24/98 5:00p Matt
 * Improved error checking for running out of rooms.
 *
 * 19    9/02/98 5:57p Matt
 * Added code to make faces match exactly when forming a portal.  This
 * should get rid of all remaining cracking problems.
 *
 * 18    9/01/98 12:04p Matt
 * Ripped out multi-face portal code
 *
 * 17    8/15/98 10:50p Matt
 * When copying a portal, copy its flags
 *
 * 16    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 15    4/21/98 2:43p Matt
 * Added system to disable render updates while deleting large numbers of
 * rooms, since the mine is not stable until this operation is done.
 *
 * 14    2/09/98 1:38p Matt
 * When pasting a group, ask the user if he also wants to paste objects
 * and triggers
 *
 * 13    2/04/98 6:23p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 12    1/29/98 5:50p Matt
 * Changed old camera object type to be viewer object (for editor), and
 * now camera objects will just be for game cameras.
 *
 * 11    1/20/98 4:12p Samir
 * New script housekeeping system.
 *
 * 10    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 9     12/23/97 11:06a Samir
 * Added pserror.h
 *
 * 8     10/13/97 6:20p Matt
 * Fixed stupid bug copying objects in group
 *
 * 7     10/03/97 3:37p Matt
 * Fixed bug copying multiple objects in a room, and changed code to not
 * copy viewer or player objects
 *
 * 6     9/24/97 6:18p Samir
 * Use script names instead of script id values to identify scripts.
 *
 * 5     9/22/97 2:31p Matt
 * Made group code copy & paste objects & triggers
 *
 * 4     9/08/97 4:05p Samir
 * Fixed some warnings and took out extranneous includes to windows.h in
 * important headers.
 *
 * 3     9/02/97 6:42p Matt
 * Got paste & group save/load working
 *
 * 2     8/29/97 5:45p Matt
 * Converted group code to work with rooms (unfinished)
 *
 * 11    6/16/97 6:40p Matt
 * Fixed bug caused when Selected_segments[] was changed while
 * DeleteGroup() was indexing through it.
 *
 * 10    6/12/97 7:17p Matt
 * Deleted now-unused RotateWorld() function
 *
 * 9     5/23/97 5:46p Matt
 * Added SetMatrixBasedOnSide() functionality to ExtractMatrixFromSeg().
 *
 * 8     5/13/97 11:58a Matt
 * Made group file code save & load the level file version number to use
 * when reading segments
 *
 * 7     5/08/97 5:07p Matt
 * When rotating world, rotate the editor's wireframe window view vars
 *
 * 6     5/08/97 4:43p Matt
 * Fixed bug when rotating objects in RotateWorld()
 *
 * 5     5/06/97 2:26p Jason
 * fixed bug in rotate world
 *
 * 4     5/05/97 3:57p Matt
 * Added code to rotate the mine (& the objects in it) to join with the
 * terrain.
 *
 * 3     3/31/97 5:58p Matt
 * Revamped mine update flags
 *
 * 2     3/12/97 3:25p Matt
 * Added funcs for cut, copy, paste, & delete, and to save and load
 * groups.
 *
 * 1     3/11/97 9:34p Matt
 *
 * $NoKeywords: $
 */

#include "group.h"

#ifndef NEWEDITOR
#include "d3edit.h"
#else
#include "globals.h"
#endif

#include "selectedroom.h"
#include "room.h"
#include "hroom.h"
#include "erooms.h"
#include "loadlevel.h"

#ifndef NEWEDITOR
#include "moveworld.h"
#endif

#include "object.h"
#include "trigger.h"
#include "pserror.h"
#include "doorway.h"
#include "mem.h"
#include <string.h>
#include "door.h"

// Free a group.
// Parameters:	g - the group to be freed
void FreeGroup(group *g) {
  for (int r = 0; r < g->nrooms; r++)
    FreeRoom(&g->rooms[r]);

  mem_free(g->rooms);

  if (g->nobjects)
    mem_free(g->objects);

  if (g->ntriggers)
    mem_free(g->triggers);

  mem_free(g);
}

// Copy the given list of rooms to a group
// Parameters:	nrooms - the number of rooms in list
//					roomnums - pointer to list of room numbers
//					attachroom, attachface - where group attaches when pasted
// Returns:		pointer to group
group *CopyGroup(int nrooms, int *roomnums, int attachroom, int attachface) {
  group *g;
  int r;
  int room_xlate[MAX_ROOMS];
  int n_objects = 0, n_triggers = 0, n_doors = 0;

  // Allocate group & room arrays
  g = (group *)mem_malloc(sizeof(*g));
  ASSERT(g != NULL);
  g->nrooms = nrooms;
  g->rooms = (room *)mem_malloc(sizeof(*g->rooms) * nrooms);
  ASSERT(g->rooms != NULL);

  // Initialize xlate list
  for (r = 0; r < MAX_ROOMS; r++)
    room_xlate[r] = -1;

  // Copy the rooms & build xlate list.  Count objects while we're at it
  for (r = 0; r < nrooms; r++) {

    CopyRoom(&g->rooms[r], &Rooms[roomnums[r]]);
    room_xlate[roomnums[r]] = r;

    for (int o = Rooms[roomnums[r]].objects; o != -1; o = Objects[o].next)
      if ((Objects[o].type != OBJ_VIEWER) && (Objects[o].type != OBJ_CAMERA) && (Objects[o].type != OBJ_PLAYER)) {
        n_objects++;
        if (Objects[o].type == OBJ_DOOR)
          n_doors++;
      }
  }

  // Add portals for rooms in the group
  for (r = 0; r < nrooms; r++)
    for (int p = 0; p < Rooms[roomnums[r]].num_portals; p++) {
      portal *pp = &Rooms[roomnums[r]].portals[p];
      if ((pp->croom != -1) && IsRoomSelected(pp->croom)) {

        // link the two rooms
        if (r < room_xlate[pp->croom]) // only link lower to higher, so we don't double link
          LinkRoomsSimple(g->rooms, r, pp->portal_face, room_xlate[pp->croom],
                          Rooms[pp->croom].portals[pp->cportal].portal_face);

        // Copy the portal flags
        int new_portal_num = g->rooms[r].faces[pp->portal_face].portal_num;
        g->rooms[r].portals[new_portal_num].flags = pp->flags;
      }
    }

  // Fill in attach fields
  g->attachroom = room_xlate[attachroom];
  g->attachface = attachface;

  // Copy objects
  g->nobjects = n_objects;
  g->ndoors = n_doors;
  if (n_objects == 0)
    g->objects = NULL;
  else {
    int objnum = 0;

    // Get memory for objects
    g->objects = (object *)mem_malloc(sizeof(*g->objects) * n_objects);

    // Go through list of rooms & copy the objects
    for (r = 0; r < nrooms; r++) {
      for (int o = Rooms[roomnums[r]].objects; o != -1; o = Objects[o].next) {
        object *dest = &g->objects[objnum], *src = &Objects[o];

        if ((src->type == OBJ_VIEWER) || (src->type == OBJ_CAMERA) || (src->type == OBJ_PLAYER))
          continue; // don't copy cameras

        // Copy some selected data
        dest->type = src->type;
        dest->id = src->id;
        dest->flags = src->flags;
        dest->pos = src->pos;
        dest->orient = src->orient;
        dest->lifeleft = src->lifeleft;

        dest->contains_type = src->contains_type;
        dest->contains_id = src->contains_id;
        dest->contains_count = src->contains_count;

        if (src->control_type == CT_POWERUP)
          dest->ctype.powerup_info.count = src->ctype.powerup_info.count;

        if (src->type == OBJ_DOOR)
          dest->shields = src->shields;

        dest->roomnum = r;

        objnum++;
      }
    }
  }

  // Count the triggers in the group
  for (int t = 0; t < Num_triggers; t++)
    if (room_xlate[Triggers[t].roomnum] != -1)
      n_triggers++;

  // Copy triggers
  g->ntriggers = n_triggers;
  if (n_triggers == 0)
    g->triggers = NULL;
  else {
    int trignum = 0;

    // Get memory for triggers
    g->triggers = (trigger *)mem_malloc(sizeof(*g->triggers) * n_triggers);

    for (int t = 0; t < Num_triggers; t++)
      if (room_xlate[Triggers[t].roomnum] != -1) {
        g->triggers[trignum] = Triggers[t];
        g->triggers[trignum].roomnum = room_xlate[Triggers[t].roomnum];
        trignum++;
      }
  }

  // Return the new group
  return g;
}

extern bool Disable_editor_rendering;

// Delete the given list of rooms
// Parameters:	nrooms - the number of rooms in list
//					roomnums - pointer to list of room numbers
void DeleteGroup(int nrooms, int *roomnums) {
  int i;
  int *troomnums;
  bool save_disable_flag = Disable_editor_rendering;

  Disable_editor_rendering = 1;

  // Make copy of list of rooms to delete.  We must do this because roomnums may be a pointer
  // to the global Selected_list, the contents of which may be changed by DeleteRoomFromMine()
  troomnums = (int *)mem_malloc(sizeof(*troomnums) * nrooms);
  for (i = 0; i < nrooms; i++)
    troomnums[i] = roomnums[i];

  // Now delete the rooms
  for (i = 0; i < nrooms; i++)
    DeleteRoomFromMine(&Rooms[troomnums[i]]);

  // Free up our array
  mem_free(troomnums);

  // Regenerate external object rooms
  CreateRoomObjects();

  // Restore old flag
  Disable_editor_rendering = save_disable_flag;

  // We're done!  Update flags and leave
  World_changed = 1;
}

// Place the given group at the specified room face
// The function merely causes the group to be drawn in the editor, allowing the user to line it up
// before attaching it.  The function AttachGroup() must be called to do the actual attachment.
// Parameters:	destroomp, destside - where to place the group
//					g - the group to place
void PlaceGroup(room *destroomp, int destface, group *g) {
  // Clear the placed room, if one exists
  Placed_room = -1;

  ASSERT(destroomp->faces[destface].portal_num == -1);

  // Set globals
  Placed_group = g;
  Placed_room_orient.fvec = destroomp->faces[destface].normal;
  Placed_room_angle = 0;
  Placed_baseroomp = destroomp;
  Placed_baseface = destface;

  // Compute attach points on each face
#ifndef NEWEDITOR
  ComputeCenterPointOnFace(&Placed_room_attachpoint, destroomp, destface);
  ComputeCenterPointOnFace(&Placed_room_origin, &g->rooms[g->attachroom], g->attachface);
#else
  float ComputeFaceBoundingCircle(vector * center, room * rp, int facenum);
  ComputeFaceBoundingCircle(&Placed_room_attachpoint, destroomp, destface);
  ComputeFaceBoundingCircle(&Placed_room_origin, &g->rooms[g->attachroom], g->attachface);
#endif

  // Compute initial orientation matrix
  ComputePlacedRoomMatrix();

  // Set the flag
  State_changed = 1;
}

#include "terrain.h"

// Place the given group at the specified terrain cell
// The function merely causes the group to be drawn in the editor, allowing the user to line it up
// before attaching it.  The function AttachGroup() must be called to do the actual attachment.
// Parameters:	cellnum - where to place the group
//					g - the group to place
void PlaceGroupTerrain(int cellnum, group *g, bool align_to_terrain) {
  // Clear the placed room, if one exists
  Placed_room = -1;

  // Set globals
  Placed_group = g;
  Placed_room_angle = 0;
  Placed_baseroomp = NULL;

  if (align_to_terrain)
    Placed_room_orient.fvec = TerrainNormals[MAX_TERRAIN_LOD - 1][cellnum].normal1;
  else
    Placed_room_orient.fvec = Identity_matrix.uvec;

  // Compute attach point on terrain
  ComputeTerrainSegmentCenter(&Placed_room_attachpoint, cellnum);

  // Compute attach points on face
  ComputeCenterPointOnFace(&Placed_room_origin, &g->rooms[g->attachroom], g->attachface);

  // Compute initial orientation matrix
  ComputePlacedRoomMatrix();

  // Set the flag
  State_changed = 1;
}

// Attach the already-placed group
void AttachGroup() {
  vector basecenter, attcenter;
  room *baseroomp, *attroomp;
  int baseface, attface;
  int room_xlate[MAX_ROOMS];
  int r;

  ASSERT(Placed_group != NULL);

  // Set some vars
  baseroomp = Placed_baseroomp;
  baseface = Placed_baseface;
  attroomp = &Placed_group->rooms[Placed_group->attachroom];
  attface = Placed_group->attachface;
  attcenter = Placed_room_origin;
  basecenter = Placed_room_attachpoint;

  // Copy the rooms into the main room list, build the xlate table, and rotate the verts
  for (r = 0; r < Placed_group->nrooms; r++) {
    int roomnum;
    room *newroomp;

    // Get a new room & copy into it
    roomnum = GetFreeRoom(0);
    if (roomnum == -1) {
      OutrageMessageBox("Cannot attach group: Not enough free rooms.");
      for (int t = 0; t < r; t++) // delete the rooms we just created
        DeleteRoomFromMine(&Rooms[room_xlate[t]]);
      return;
    }
    newroomp = &Rooms[roomnum];
    CopyRoom(newroomp, &Placed_group->rooms[r]);
    room_xlate[r] = roomnum;

    // Rotate verts in the new rooms
    for (int i = 0; i < newroomp->num_verts; i++)
      newroomp->verts[i] = ((newroomp->verts[i] - attcenter) * Placed_room_rotmat) + basecenter;

    // Recompute normals for the faces
    if (!ResetRoomFaceNormals(newroomp))
      Int3(); // Get Matt
  }

  // Add portals for new rooms
  for (r = 0; r < Placed_group->nrooms; r++)
    for (int p = 0; p < Placed_group->rooms[r].num_portals; p++) {
      portal *pp = &Placed_group->rooms[r].portals[p];
      if (r < pp->croom) // only link lower to higher, so we don't double link
        LinkRoomsSimple(Rooms, room_xlate[r], pp->portal_face, room_xlate[pp->croom],
                        Placed_group->rooms[pp->croom].portals[pp->cportal].portal_face);

      // Copy the portal flags
      int new_portal_num = Rooms[room_xlate[r]].faces[pp->portal_face].portal_num;
      Rooms[room_xlate[r]].portals[new_portal_num].flags = pp->flags;
    }

  // Get pointer to the placed attachroom
  room *newroomp = &Rooms[room_xlate[Placed_group->attachroom]];

  if (baseroomp) {
    // Clip the connecting faces against each other
    if (!ClipFacePair(newroomp, attface, baseroomp, baseface)) {
      OutrageMessageBox("Error making portal -- faces probably don't overlap.");
      for (r = 0; r < Placed_group->nrooms; r++)
        FreeRoom(&Rooms[room_xlate[r]]);
      return;
    }

    // Make the two faces match exactly
    MatchPortalFaces(baseroomp, baseface, newroomp, attface);

    // Link the attach room to the base room
    LinkRoomsSimple(Rooms, ROOMNUM(baseroomp), baseface, ROOMNUM(newroomp), attface);
  }

  // Paste objects
  if (Placed_group->nobjects) {
    bool place_all = 0;

    // Ask if the user wants the objects pasted
    if (Placed_group->nobjects > Placed_group->ndoors)
      place_all =
          (OutrageMessageBox(MBOX_YESNO,
                             "The group you are pasting has %d (non-door) object(s).  Do you wish to paste it/them?",
                             Placed_group->nobjects - Placed_group->ndoors) == IDYES);

    // Add the objects (either just doors or all objects)
    for (int o = 0; o < Placed_group->nobjects; o++) {
      object *src = &Placed_group->objects[o], *dest;

      if (place_all || (src->type == OBJ_DOOR)) {
        vector pos;
        matrix orient;
        int objnum;

        pos = ((src->pos - attcenter) * Placed_room_rotmat) + basecenter;
        orient = ~Placed_room_rotmat * src->orient;

        objnum = ObjCreate(src->type, src->id, room_xlate[src->roomnum], &pos, &orient);

#ifdef NEWEDITOR
        if (IS_GENERIC(src->type))
          LevelObjIncrementObject(src->id);
#endif

        dest = &Objects[objnum];

        dest->flags = src->flags;
        dest->lifeleft = src->lifeleft;

        dest->contains_type = src->contains_type;
        dest->contains_id = src->contains_id;
        dest->contains_count = src->contains_count;

        if (dest->control_type == CT_POWERUP)
          dest->ctype.powerup_info.count = src->ctype.powerup_info.count;

        if (src->type == OBJ_DOOR)
          dest->shields = src->shields;
      }
    }
  }

  // Paste triggers
  if (Placed_group->ntriggers) {

    // Ask if the user wants the triggers
    if (OutrageMessageBox(MBOX_YESNO, "The group you are pasting has %d trigger(s).  Do you wish to paste it/them?",
                          Placed_group->ntriggers) == IDYES) {

      // Add the triggers
      for (int t = 0; t < Placed_group->ntriggers; t++) {
        trigger *tp = &Placed_group->triggers[t];
        int trignum;

        trignum = AddTrigger("", room_xlate[tp->roomnum], tp->facenum, tp->activator, NULL);
        ASSERT(trignum != -1);

        Triggers[trignum].flags = tp->flags;
      }
    } else { // Triggers not being pasted, so must delete any floating trigger faces
      for (r = 0; r < Placed_group->nrooms; r++) {
        room *rp = &Rooms[room_xlate[r]];
        for (int f = 0; f < rp->num_faces; f++) {
          if (rp->faces[f].flags & FF_FLOATING_TRIG)
            DeleteRoomFace(rp, f);
        }
      }
    }
  }

  // Un-place the now-attached group
  Placed_group = NULL;

  // We're done!  Update flags and leave
  World_changed = 1;
}

#define GROUP_FILE_TAG "D3GP"
#define GROUP_FILE_VERSION 3
// Version number changes:
// 0 -> 1  Save the level file version to use when reading objects, rooms, etc.
// 1 -> 2  Now works for room engine
// 2 -> 3  Save objects, doors, & triggers

#define cf_ReadVector(f, v)                                                                                            \
  do {                                                                                                                 \
    (v)->x = cf_ReadFloat(f);                                                                                          \
    (v)->y = cf_ReadFloat(f);                                                                                          \
    (v)->z = cf_ReadFloat(f);                                                                                          \
  } while (0)
#define cf_WriteVector(f, v)                                                                                           \
  do {                                                                                                                 \
    cf_WriteFloat((f), (v)->x);                                                                                        \
    cf_WriteFloat((f), (v)->y);                                                                                        \
    cf_WriteFloat((f), (v)->z);                                                                                        \
  } while (0)
#define cf_WriteMatrix(f, m)                                                                                           \
  do {                                                                                                                 \
    cf_WriteVector((f), &(m)->rvec);                                                                                   \
    cf_WriteVector((f), &(m)->uvec);                                                                                   \
    cf_WriteVector((f), &(m)->fvec);                                                                                   \
  } while (0)
#define cf_ReadMatrix(f, m)                                                                                            \
  do {                                                                                                                 \
    cf_ReadVector((f), &(m)->rvec);                                                                                    \
    cf_ReadVector((f), &(m)->uvec);                                                                                    \
    cf_ReadVector((f), &(m)->fvec);                                                                                    \
  } while (0)

// Saves an object for a group
void WriteGroupObject(CFILE *ofile, object *objp) {
  cf_WriteByte(ofile, objp->type);
  cf_WriteShort(ofile, objp->id);
  cf_WriteInt(ofile, objp->flags);

  if (objp->type == OBJ_DOOR)
    cf_WriteShort(ofile, objp->shields);

  cf_WriteInt(ofile, objp->roomnum);
  cf_WriteVector(ofile, &objp->pos);
  cf_WriteMatrix(ofile, &objp->orient);

  cf_WriteByte(ofile, objp->contains_type);
  cf_WriteByte(ofile, objp->contains_id);
  cf_WriteByte(ofile, objp->contains_count);

  cf_WriteFloat(ofile, objp->lifeleft);
}

void WriteGroupTrigger(CFILE *ofile, trigger *tp) {
  cf_WriteShort(ofile, tp->roomnum);
  cf_WriteShort(ofile, tp->facenum);
  cf_WriteShort(ofile, tp->flags);
  cf_WriteShort(ofile, tp->activator);
}

// Saves a group to disk in the given filename
void SaveGroup(char *filename, group *g) {
  CFILE *ifile;
  int i;

  ifile = cfopen(filename, "wb");

  if (!ifile)
    return;

  // Write tag & version number
  cf_WriteBytes((uint8_t *)GROUP_FILE_TAG, 4, ifile);
  cf_WriteInt(ifile, GROUP_FILE_VERSION);
  cf_WriteInt(ifile, LEVEL_FILE_VERSION);

  // Write the current list of textures
  WriteTextureList(ifile);

  // Write group info
  cf_WriteInt(ifile, g->nrooms);
  cf_WriteInt(ifile, g->attachroom);
  cf_WriteInt(ifile, g->attachface);
  cf_WriteInt(ifile, g->nobjects);
  cf_WriteInt(ifile, g->ndoors);
  cf_WriteInt(ifile, g->ntriggers);

  // Write rooms
  for (i = 0; i < g->nrooms; i++)
    WriteRoom(ifile, &g->rooms[i]);

  // Write objects
  for (i = 0; i < g->nobjects; i++)
    WriteGroupObject(ifile, &g->objects[i]);

  // Write triggers
  for (i = 0; i < g->ntriggers; i++)
    WriteGroupTrigger(ifile, &g->triggers[i]);

  // Close the file
  cfclose(ifile);
}

// Reads an object for a group
void ReadGroupObject(CFILE *ifile, object *objp) {
  objp->type = cf_ReadByte(ifile);
  objp->id = cf_ReadShort(ifile);
  objp->flags = cf_ReadInt(ifile);

  if (objp->type == OBJ_DOOR)
    objp->shields = cf_ReadShort(ifile);

  objp->roomnum = cf_ReadInt(ifile);
  cf_ReadVector(ifile, &objp->pos);
  cf_ReadMatrix(ifile, &objp->orient);

  objp->contains_type = cf_ReadByte(ifile);
  objp->contains_id = cf_ReadByte(ifile);
  objp->contains_count = cf_ReadByte(ifile);

  objp->lifeleft = cf_ReadFloat(ifile);
}

void ReadGroupTrigger(CFILE *ifile, trigger *tp) {
  tp->roomnum = cf_ReadShort(ifile);
  tp->facenum = cf_ReadShort(ifile);
  tp->flags = cf_ReadShort(ifile);
  tp->activator = cf_ReadShort(ifile);
}

// Loads a group from disk
group *LoadGroup(char *filename) {
  CFILE *ifile;
  char tag[4];
  int version, level_version;
  group *g;
  int i;

  ifile = cfopen(filename, "rb");

  if (!ifile)
    return NULL;

  // Read & check tag
  cf_ReadBytes((uint8_t *)tag, 4, ifile);
  if (strncmp(tag, GROUP_FILE_TAG, 4)) {
    cfclose(ifile);
    return NULL;
  }

  // Read & check version number
  version = cf_ReadInt(ifile);
  if (version > GROUP_FILE_VERSION) {
    cfclose(ifile);
    return NULL;
  }

  // Check for out-of-date groups
  if (version < 2) {
    OutrageMessageBox("Sorry - segment groups no longer supported.");
    cfclose(ifile);
    return NULL;
  }

  // Read & check level file version number
  level_version = cf_ReadInt(ifile);
  if (level_version > LEVEL_FILE_VERSION) {
    cfclose(ifile);
    return NULL;
  }

  // Read the textures & build xlate table
  ReadTextureList(ifile);

  // Allocate group
  g = (group *)mem_malloc(sizeof(*g));

  // Read group info
  g->nrooms = cf_ReadInt(ifile);
  g->attachroom = cf_ReadInt(ifile);
  g->attachface = cf_ReadInt(ifile);

  // Read object, door, & trigger info
  if (version >= 3) {
    g->nobjects = cf_ReadInt(ifile);
    g->ndoors = cf_ReadInt(ifile);
    g->ntriggers = cf_ReadInt(ifile);
  } else
    g->nobjects = g->ndoors = g->ntriggers = 0;

  // Allocate room and vertex arrays
  g->rooms = (room *)mem_malloc(sizeof(*g->rooms) * g->nrooms);

  // Read rooms
  for (i = 0; i < g->nrooms; i++) {
    g->rooms[i].used = 0; // ReadRoom() wants the used flag to be clear
    ReadRoom(ifile, &g->rooms[i], level_version);
  }

  // Read objects & triggers
  g->triggers = NULL;
  g->objects = NULL;
  if (version >= 3) {

    // Allocate objects array
    if (g->nobjects)
      g->objects = (object *)mem_malloc(sizeof(*g->objects) * g->nobjects);

    // Allocate triggers array
    if (g->ntriggers)
      g->triggers = (trigger *)mem_malloc(sizeof(*g->triggers) * g->ntriggers);

    // Read objects
    for (i = 0; i < g->nobjects; i++)
      ReadGroupObject(ifile, &g->objects[i]);

    // Read triggers
    for (i = 0; i < g->ntriggers; i++)
      ReadGroupTrigger(ifile, &g->triggers[i]);
  }

  // Close the file
  cfclose(ifile);

  return g;
}
