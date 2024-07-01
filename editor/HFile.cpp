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

 * $Logfile: /DescentIII/Main/editor/HFile.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Handler funcs for File menu
 *
 * $Log: not supported by cvs2svn $
 *
 * 81    10/13/99 2:19p Chris
 * Added the ability to disable wind for powerups on a level
 *
 * 80    10/13/99 10:40a Chris
 * Added 'special forcefields' that have custom bounce factors
 *
 * 79    10/08/99 4:29p Chris
 * Added the forcefield and glass breaking override options
 *
 * 78    5/18/99 11:10a Matt
 * Added variable ceiling height.
 *
 * 77    4/27/99 3:24p Jeff
 * showlevelstats shows information about goals and special flags
 *
 * 76    4/21/99 1:08p Chris
 * Fixed new mines from having the always check ceiling  flag
 *
 * 75    4/20/99 8:14p Chris
 * Added support for object's that hit the ceiling and for making the
 * level always check for the ceiling (inside and outside the mine)
 *
 * 74    4/18/99 5:42a Chris
 * Added the FQ_IGNORE_RENDER_THROUGH_PORTALS flag
 *
 * 73    3/22/99 6:26p Matt
 * Cleaned up error handling in cfile and editor level loads.
 *
 * 72    3/02/99 4:54p Matt
 * Fixed another stupid bug
 *
 * 71    3/02/99 4:07p Matt
 * Fixed stupid bug in duplicate room name check
 *
 * 70    3/01/99 10:39a Matt
 * Strip leading and trailing spaces from object, trigger, and room names
 * on level load and when the names are entered.
 *
 * 69    2/28/99 10:41p Matt
 * After a level is loaded, check for duplicate trigger, room, & object
 * names.
 *
 * 68    2/28/99 9:28p Matt
 * Cleaned up load level error handing and version checking.
 *
 * 67    2/21/99 12:28p Matt
 * Added terrain sound system
 *
 * 66    2/17/99 3:06p Matt
 * Updated copyrights.
 *
 * 65    2/16/99 3:47p Jason
 * added marker updates to multiplayer server stream
 *
 * 64    2/02/99 10:46a Matt
 * Only reset the wireframe view radius when loading an actual new level,
 * and not whenever a level is loading, which incudes going from the game
 * to the editor.
 *
 * 63    1/29/99 12:48p Matt
 * Rewrote the doorway system
 *
 * 62    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 61    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 60    1/04/99 6:19p Jason
 * counts number of specular faces in mine
 *
 * 59    12/18/98 5:40p Chris
 * Ambient life is now all sequenced up
 *
 * 58    10/08/98 8:14p Matt
 * Fixed stupid bug that's just started causing problems.
 *
 * 57    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 56    10/05/98 2:42a Chris
 * Level goals are relatively functional
 *
 * 55    9/24/98 5:00p Matt
 * Improved error checking for running out of rooms.
 *
 * 54    9/16/98 12:07p Chris
 * Improved BOA AABB computation with room checksums
 *
 * 53    9/10/98 3:07p Chris
 * Improved matcen sequencing code and test effect1
 *
 * 52    9/08/98 12:05p Jason
 * moved doorway.h out of room.h
 *
 * 51    8/17/98 2:16p Jason
 * fixed erroneous reporting of specular lightmap bytes
 *
 * 50    8/10/98 11:25a Jason
 * added better specular lighting
 *
 * 49    8/03/98 5:47p Chris
 * Improved the partial AABB computation
 *
 * 48    5/15/98 5:41p Jason
 * implemented volume lighting system
 *
 * 47    5/13/98 3:06p Jason
 * got rid of square-power-of-two lightmap limitations
 *
 * 46    5/13/98 12:06p Jason
 * trimmed some memory usage
 *
 * 45    4/21/98 2:40p Matt
 * Added option to show level stats
 *
 * 44    4/14/98 7:50p Matt
 * Added system to keep info for each level
 *
 * 43    2/18/98 8:43p Chris
 * Made BOA get saved with the level.  It should only get built when it
 * needs to be updated.
 *
 * 42    2/04/98 1:26p Matt
 * Got rid of compile warning
 *
 * 41    2/03/98 5:01p Chris
 * UPdated the path system
 *
 * 40    1/27/98 12:01p Chris
 * Game path system now works with new, load, and save in the editor.
 * Also, the game path system is further bug proved.
 *
 * 39    1/21/98 12:32p Matt
 * Revamped viewer system
 *
 * 38    1/20/98 1:36p Matt
 * Moved mine origin to the center of the terrain
 *
 * 37    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 36    1/15/98 7:34p Matt
 * Revamped error checking when computing face normals
 *
 * 35    1/02/98 12:00p Jason
 * got rid of redundant rebuilding of min/max terrain
 *
 * 34    10/08/97 5:20p Jason
 * clear object memory when "New" is selected
 *
 * 33    10/01/97 7:49p Matt
 * Fixed bug w/ script memory freeing (as per Samir's instructions)
 *
 * 32    10/01/97 4:49p Samir
 * Free level script after loading it, since the editor doesn't need the
 * compiled program.
 *
 * 31    9/25/97 5:28p Samir
 * Even newer script code due to more changes in ObjCScript.cpp
 *
 * 30    9/24/97 2:57p Samir
 * Modified NewScript for level function.
 *
 * 29    9/22/97 5:59p Samir
 * Changed ObjCScript system, so everything is broken, but it shouldn't
 * crash the game.
 *
 * 28    9/17/97 1:24p Matt
 * Ripped out segment code
 *
 * 27    9/17/97 12:53p Samir
 * BIG SEGMENT RIPOUT
 *
 * 26    9/10/97 1:55p Samir
 * Create a default level script for a new mine.
 *
 * 25    9/09/97 2:38p Samir
 * Added include for string.h
 *
 * 24    9/09/97 1:04p Samir
 * Added code to create new script and save level script name.
 *
 * 23    9/09/97 10:44a Matt
 * Fixed a small bug, & ripped out some segment engine code
 *
 * 22    9/06/97 3:35p Matt
 * Reset cur porral when room changes
 * Ripped out some old segment engine code
 *
 * 21    8/29/97 5:21p Matt
 * Made CreateNewMine() clear the room (not segment) selected list, and
 * clear Placed_group
 *
 * 20    8/21/97 2:06p Matt
 * Clear marked room when creating a new level
 *
 * 19    8/18/97 6:59p Matt
 * Implemented Place Room/Attach room system
 *
 * 18    8/15/97 6:32p Samir
 * Took out references to default/level scripts due to newer system.
 *
 * 17    8/12/97 3:22p Samir
 * D3XReallocProgram now has two more args.
 *
 * 16    8/06/97 10:36a Samir
 * Fixed D3XReallocProgram calls.
 *
 * 15    8/04/97 4:12p Samir
 * Reset level script code every new mine.
 *
 * 14    7/24/97 2:58p Matt
 * Reset editor viewer variables when creating a new mine
 *
 * 13    7/22/97 7:07p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 12    7/18/97 5:42p Matt
 * Changed default level script to use CR/LF pair instead of Newline
 *
 * 11    7/17/97 7:22p Matt
 * Initialize level script when create new level
 *
 * 26    6/30/97 1:30p Jason
 * added netherspace stuff
 *
 * 25    6/24/97 3:50p Jason
 * changes for y only terrain positions
 *
 * 24    5/13/97 10:29p Matt
 * Deleted some unused code
 *
 * 23    5/13/97 12:01p Matt
 * Added support for floating segments
 *
 * 22    5/08/97 7:29p Matt
 * Made seperate viewers for mine & terrain, and cleaned up code the
 * switched between modes
 *
 * 21    5/06/97 2:30p Jason
 * added check for terrain viewer
 *
 * 20    4/25/97 2:31p Jason
 * implemented game event system
 *
 * 19    4/04/97 2:57p Matt
 * Added code to initialize all the type-specific data for an object from
 * the page for that object type.  This means that we need to pass less
 * info to ObjCreate(), and that we save less info in the level save file.
 * It also makes it easy to reset all the objects when an object page has
 * changed.
 *
 * 18    4/01/97 11:00p Matt
 * Changed editor to keep a viewer object (type camera) seperate from the
 * player object.  This camera, and not the player, is now moved by
 * slewing, the C key, etc.  When going into the game, the viewer position
 * & orientation are copied to the player.  When going back to the editor,
 * the player position is copied to the viewer, and the player object is
 * reset to its start location.
 *
 * 17    3/31/97 5:58p Matt
 * Revamped mine update flags
 *
 * 16    3/31/97 3:47p Matt
 * Added code to keep track of, render, and display current vertex.
 *
 * 15    3/21/97 5:01p Jason
 * incremental terrain improvments
 *
 *
 * 14    3/18/97 11:27a Samir
 * Reset current trigger and doorway to 0 when loading a level in.
 *
 * 13    3/17/97 2:54p Samir
 * Dont initialize initial doorways or triggers.
 *
 * 12    3/17/97 12:00p Matt
 * Reset warning segments when creating new level and loading
 * level.
 *
 * 11    3/12/97 1:14p Matt
 * Clear selected list when creating a new mine
 *
 * 10    3/12/97 12:37p Samir
 * Initialized doorways
 *
 * 9     3/05/97 3:33p Samir
 * Define initial default Doorway for mine.
 *
 * 8     3/04/97 7:12p Samir
 * Initialized a default trigger when new level
 *
 * 7     2/26/97 12:23p Matt
 * Use real funcs to create segment sides & assign uvs.
 * Deleted temp func that did the same.
 *
 * 6     2/24/97 6:00p Matt
 * Added code to set marked segment.
 * Changed code to not say that mine has changed when curside or curside
 * has changed.
 *
 * 5     2/21/97 5:23p Matt
 * Added new ResetVertices() to set Vertex_active array after level
 * loaded.  Renamed old ResetVertices() to InitVertices();
 *
 * 4     2/20/97 9:56a Matt
 * Moved some general-purpose segment code from HFile.cpp to ESegments.cpp
 *
 * 3     2/11/97 6:44p Matt
 * Reset player when do a new level
 * Added new function: ResetFreeSegList()
 *
 * 2     2/10/97 5:40p Matt
 * Code to handle several File menu options
 *
 * 1     2/10/97 12:16a Matt
 *
 * $NoKeywords: $
 */

#include <string.h>

#include "descent.h"
#include "HFile.h"
#include "d3edit.h"
#include "room.h"
#include "object.h"
#include "game.h"
#include "LoadLevel.h"
#include "MoveWorld.h"
#include "ERooms.h"
#include "trigger.h"
#include "door.h"
#include "selectedroom.h"
#include "terrain.h"
#include "player.h"
#include "gameevent.h"
#include "HView.h"
#include "gamepath.h"
#include "boa.h"
#include "mission.h"
#include "lighting.h"
#include "lightmap_info.h"
#include "lightmap.h"
#include "special_face.h"
#include "doorway.h"
#include "matcen.h"
#include "levelgoal.h"
#include "aiambient.h"
#include "polymodel.h"
#include "bnode.h"
#include "findintersection.h"

//	Scripting stuff
// #include "d3x.h"
// #include "ObjScript.h"

// vertices for the default room created by CreateNewMine()
vector default_room_verts[] = {{-10, 8, 20},  {-5, 10, 20},  {5, 10, 20},    {10, 8, 20},   {10, -8, 20}, {5, -10, 20},
                               {-5, -10, 20}, {-10, -8, 20}, {-10, 8, -20},  {-5, 10, -20}, {5, 10, -20}, {10, 8, -20},
                               {10, -8, -20}, {5, -10, -20}, {-5, -10, -20}, {-10, -8, -20}};

extern void AssignDefaultUVsToRoom(room *rp);

// Where the center of the (mine's) world is
vector Mine_origin = {TERRAIN_WIDTH * (TERRAIN_SIZE / 2), -100, TERRAIN_DEPTH *(TERRAIN_SIZE / 2)};

// Create a default room for a new mine
room *CreateDefaultRoom() {
  room *rp;
  int i;

  // Get a pointer to our room
  rp = CreateNewRoom(16, 10, 0); // 16 verts, 10 faces, normal room
  ASSERT(rp != NULL);

  // Set the vertices for the room
  for (i = 0; i < 16; i++)
    rp->verts[i] = default_room_verts[i] + Mine_origin;

  // Set the faces for the room
  InitRoomFace(&rp->faces[0], 8);
  for (i = 0; i < 8; i++)
    rp->faces[0].face_verts[i] = i;

  InitRoomFace(&rp->faces[1], 8);
  for (i = 0; i < 8; i++)
    rp->faces[1].face_verts[i] = 15 - i;

  for (i = 0; i < 8; i++) {
    InitRoomFace(&rp->faces[i + 2], 4);
    rp->faces[i + 2].face_verts[0] = i;
    rp->faces[i + 2].face_verts[1] = i + 8;
    rp->faces[i + 2].face_verts[2] = ((i + 1) % 8) + 8;
    rp->faces[i + 2].face_verts[3] = (i + 1) % 8;
  }

  // Set normals, textures and UVLs for face
  for (i = 0; i < 10; i++) {
    if (!ComputeFaceNormal(rp, i))
      Int3(); // this is odd.  Get Matt!
    rp->faces[i].tmap = i + 1;
    AssignDefaultUVsToRoomFace(rp, i);
  }

  return rp;
}

#define DEFAULT_SCRIPT "//Empty script\xd\xa"

// Create a new mine with one segment
void CreateNewMine() {
  // Get rid of old mine
  FreeAllRooms();
  FreeAllObjects();

  // Create a new room
  Curroomp = CreateDefaultRoom();
  ASSERT(Curroomp != NULL);

  // Reset misc. vars
  Curface = Curedge = Curvert = 0;
  Curportal = -1;

  // Say that this is a new mine
  New_mine = 1;

  // Reset the view position, etc. for the wireframe view
  ResetWireframeView();

  // Reintialize the objects
  ResetObjectList();

  // Create the player and put him in the center of the fa
  CreatePlayerObject(ROOMNUM(Curroomp));

  // Initialize editor viewer
  Editor_view_mode = VM_MINE;
  Editor_viewer_id = -1;

  // Create a camera for this level
  SetEditorViewer();

  // Look for player objects & set player starts
  FindPlayerStarts();

  // Clear the marked room
  Markedroomp = NULL;

  // Clear the selected segments
  ClearRoomSelectedList();

  // Clear the placed room & group
  Placed_room = -1;
  Placed_group = NULL;

  // Reset the triggers
  Num_triggers = 0;
  Current_trigger = -1;

  // Reset the terrain
  ResetTerrain(1);

  // Reset terrain sound
  ClearTerrainSound();

  // Clear game events
  ClearAllEvents();

  int i;
  BOA_AABB_checksum = BOA_mine_checksum = 0;
  for (i = 0; i < MAX_ROOMS; i++) {
    BOA_AABB_ROOM_checksum[i] = 0;
  }
  InitGamePaths();
  DestroyAllMatcens();
  // Resets the ambient life controller
  a_life.ALReset();
  Level_goals.CleanupAfterLevel();

  BNode_ClearBNodeInfo();
  FVI_always_check_ceiling = false;
  Ceiling_height = MAX_TERRAIN_HEIGHT;

  sound_override_force_field = -1;
  sound_override_glass_breaking = -1;

  for (i = 0; i < MAX_FORCE_FIELD_BOUNCE_TEXTURES; i++) {
    force_field_bounce_texture[i] = -1;
    force_field_bounce_multiplier[i] = 1.0f;
  }

  Level_powerups_ignore_wind = false;

  // Init level info
  strcpy(Level_info.name, "Unnamed");
  strcpy(Level_info.designer, "Anonymous");
  strcpy(Level_info.copyright, "Copyright (c) 1999 Outrage Entertainment, Inc.");
  strcpy(Level_info.notes, "");
}

#include "osiris_predefs.h"

// Strips leading and trailing spaces from a string
// Returns true if spaces were stripped
bool StripLeadingTrailingSpaces(char *s) {
  char *t;
  bool stripped = 0;

  // Look for leading spaces
  t = s;
  while (*t == ' ')
    t++;

  // Leading spaces found, so copy string over spaces
  if (t != s) {
    strcpy(s, t);
    stripped = 1;
  }

  // Strip any trailing spaces
  for (t = s + strlen(s) - 1; (t >= s) && (*t == ' '); t--) {
    *t = 0;
    stripped = 1;
  }

  return stripped;
}

// Check for duplicate names in the level
void CheckLevelNames() {
  int i;

  // Check objects
  object *objp;
  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++) {
    if ((objp->type != OBJ_NONE) && objp->name) {
      int handle = osipf_FindObjectName(objp->name);
      if (handle != objp->handle)
        EditorMessageBox("Error: Objects %d and %d are both named \"%s\"", i, OBJNUM(ObjGet(handle)), objp->name);
      if (StripLeadingTrailingSpaces(objp->name))
        EditorMessageBox(
            "Note: Object %d (\"%s\") had leading and/or trailing spaces in its name that have been removed.", i,
            objp->name);
    }
  }

  // Check triggers
  trigger *tp;
  for (i = 0, tp = Triggers; i < Num_triggers; i++, tp++) {
    if (tp->name) {
      int n = osipf_FindTriggerName(tp->name);
      if (n != i)
        EditorMessageBox("Error: Triggers %d and %d are both named \"%s\"", i, n, tp->name);
      if (StripLeadingTrailingSpaces(tp->name))
        EditorMessageBox(
            "Note: Trigger %d (\"%s\") had leading and/or trailing spaces in its name that have been removed.", i,
            tp->name);
    }
  }

  // Check rooms
  room *rp;
  for (i = 0, rp = Rooms; i <= Highest_room_index; i++, rp++) {
    if (rp->used && rp->name) {
      int n = osipf_FindRoomName(rp->name);
      if (n != i)
        EditorMessageBox("Error: Rooms %d and %d are both named \"%s\"", i, n, rp->name);
      if (StripLeadingTrailingSpaces(rp->name))
        EditorMessageBox(
            "Note: Room %d (\"%s\") had leading and/or trailing spaces in its name that have been removed.", i,
            rp->name);
    }
  }
}

// Load a new level
bool EditorLoadLevel(char *filename) {
  if (LoadLevel(filename)) {

    // Check for duplicate names in the level
    CheckLevelNames();

    New_mine = 1; // say that this is a new mine

    // Set viewer object
    SetEditorViewer();

    // Reset view radius
    ResetWireframeViewRad();

    // Done
    return TRUE;
  } else
    return FALSE;
}

// Save the current level
// Returns 1 if level saved sucessfully
int EditorSaveLevel(char *filename) {
  int sucess;

  sucess = SaveLevel(filename);

  if (sucess)
    Mine_changed = 0;

  return sucess;
}

// Returns a pointer to enough spaces to right-justify a number that's printed after the spaces
char *IntSpacing(int i) {
  static char *spaces = "               ";

  i = abs(i);

  int n;
  for (n = 1; i >= 10; n++)
    i /= 10;

  ASSERT(n <= 20);

  return spaces + n * 2 + n / 2;
}

extern void dump_text_to_clipboard(char *text);

// Shows the stats for a level in a messagebox, and copies to the clipboard
void ShowLevelStats() {
  int n_rooms, n_rooms_external, n_faces, n_verts, n_objects, n_portals, n_doors, n_objects_outside;
  int n_object_faces, n_object_lightmap_faces;
  int i;
  room *rp;
  int bytes_wasted = 0, spec_faces = 0, lm_bytes = 0;
  int total_volume_bytes = 0;
  int num_redgoals = 0, num_bluegoals = 0, num_greengoals = 0, num_yellowgoals = 0;
  int num_sp1 = 0, num_sp2 = 0, num_sp3 = 0, num_sp4 = 0, num_sp5 = 0, num_sp6 = 0;

  uint8_t lightmaps_used[MAX_LIGHTMAPS];

  object *objp;
#define BUF_LEN 5000
  char text_buf[BUF_LEN];

  // Count the number of rooms, and the number of faces & points per room
  n_rooms = n_rooms_external = n_faces = n_verts = n_doors = n_portals = 0;
  for (i = 0, rp = Rooms; i <= Highest_room_index; i++, rp++)
    if (rp->used) {
      n_rooms++;
      n_verts += rp->num_verts;
      n_faces += rp->num_faces;
      n_portals += rp->num_portals;
      if (rp->flags & RF_EXTERNAL)
        n_rooms_external++;
      else {
        // Get volume size of room
        total_volume_bytes += GetVolumeSizeOfRoom(rp);
      }

      for (int t = 0; t < rp->num_faces; t++) {
        face *fp = &rp->faces[t];
        if (fp->special_handle != BAD_SPECIAL_FACE_INDEX && GameTextures[fp->tmap].flags & TF_SPECULAR &&
            fp->lmi_handle != BAD_LMI_INDEX)
          spec_faces++;
      }

      if (rp->flags & RF_DOOR)
        n_doors++;

      if (rp->flags & RF_SPECIAL1)
        num_sp1++;

      if (rp->flags & RF_SPECIAL2)
        num_sp2++;

      if (rp->flags & RF_SPECIAL3)
        num_sp3++;

      if (rp->flags & RF_SPECIAL4)
        num_sp4++;

      if (rp->flags & RF_SPECIAL5)
        num_sp5++;

      if (rp->flags & RF_SPECIAL6)
        num_sp6++;

      if (rp->flags & RF_GOAL1)
        num_redgoals++;

      if (rp->flags & RF_GOAL2)
        num_bluegoals++;

      if (rp->flags & RF_GOAL3)
        num_greengoals++;

      if (rp->flags & RF_GOAL4)
        num_yellowgoals++;
    }

  // Count the number of objects
  n_objects = n_object_faces = n_object_lightmap_faces = n_objects_outside = 0;
  for (i = 0, objp = Objects; i <= Highest_object_index; i++, objp++)
    if ((objp->type != OBJ_NONE) && (objp->type != OBJ_ROOM) && (objp->render_type == RT_POLYOBJ)) {
      n_objects++;
      if (OBJECT_OUTSIDE(objp))
        n_objects_outside++;
      // Count the number of faces in this object
      poly_model *pm;
      pm = GetPolymodelPointer(objp->rtype.pobj_info.model_num);
      for (int m = 0; m < pm->n_models; m++) {
        n_object_faces += pm->submodel[m].num_faces;
        if (objp->lighting_render_type == LRT_LIGHTMAPS)
          n_object_lightmap_faces += pm->submodel[m].num_faces;
      }
    }

  memset(lightmaps_used, 0, MAX_LIGHTMAPS);
  for (i = 0; i < MAX_LIGHTMAP_INFOS; i++) {
    if (!LightmapInfo[i].used)
      continue;
    if (LightmapInfo[i].type == LMI_DYNAMIC || LightmapInfo[i].type == LMI_TERRAIN)
      continue;

    lightmaps_used[LightmapInfo[i].lm_handle] = 1;
  }

  for (i = 0; i < MAX_LIGHTMAPS; i++) {
    if (lightmaps_used[i]) {
      uint16_t *data = lm_data(i);
      int w = lm_w(i);
      int h = lm_h(i);

      for (int j = 0; j < w * h; j++) {
        if (!(data[j] & OPAQUE_FLAG)) {
          bytes_wasted += 2;
        } else {
          lm_bytes += 2;
        }
      }
    }
  }

  i = sprintf(text_buf,
              "Level Stats:\n"
              "\n"
              "%s%d   Rooms (%d external)\n"
              "%s%d   Faces\n"
              "%s%d   Vertices\n"
              "\n"
              "%s%d   Portals\n"
              "%s%d   Doors\n"
              "\n"
              "%s%d   Polygon Objects (%d inside, %d outside)\n"
              "%s%d   Object Faces (%d with lightmaps)\n"
              "\n"
              "%s%d   Total lightmap faces\n"
              "%d	Total volume bytes\n"
              "%d   Total bytes in lightmaps\n"
              "%d   Total specular faces\n"
              "%d   Bytes wasted in lightmaps\n"
              "\n"
              "%d Red Goals\n"
              "%d Blue Goals\n"
              "%d Green Goals\n"
              "%d Yellow Goals\n"
              "%d Special 1 Rooms\n"
              "%d Special 2 Rooms\n"
              "%d Special 3 Rooms\n"
              "%d Special 4 Rooms\n"
              "%d Special 5 Rooms\n"
              "%d Special 6 Rooms\n",
              IntSpacing(n_rooms), n_rooms, n_rooms_external, IntSpacing(n_faces), n_faces, IntSpacing(n_verts),
              n_verts, IntSpacing(n_portals / 2), n_portals / 2, IntSpacing(n_doors), n_doors, IntSpacing(n_objects),
              n_objects, n_objects - n_objects_outside, n_objects_outside, IntSpacing(n_object_faces), n_object_faces,
              n_object_lightmap_faces, IntSpacing(n_faces + n_object_lightmap_faces), n_faces + n_object_lightmap_faces,
              total_volume_bytes, lm_bytes, spec_faces, bytes_wasted, num_redgoals, num_bluegoals, num_greengoals,
              num_yellowgoals, num_sp1, num_sp2, num_sp3, num_sp4, num_sp5, num_sp6);

  ASSERT(i < BUF_LEN);

  dump_text_to_clipboard(text_buf);
  OutrageMessageBox(
      "%s\n\nThis info has also been posted to the clipboard.\n\nWhat other info would you like here?  Let MattT know.",
      text_buf);
}
