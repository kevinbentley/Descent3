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

 * $Logfile: /DescentIII/main/objinfo.cpp $
 * $Revision: 64 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * Code to handle objects in the big list of robots,powerups,etc.
 *
 * $NoKeywords: $
 */

#include "pstypes.h"
#include "pserror.h"
#include "object.h"
#include "objinfo.h"
#include "3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "polymodel.h"
#include "robotfire.h"
#include "AIMain.h"
#include "sounds.h"
#include "stringtable.h"
#include "mem.h"

// The array with information for robots, powerups, buildings, etc.
std::array<object_info, MAX_OBJECT_IDS> Object_info;

// The number of ids of each type in the list
int Num_object_ids[MAX_OBJECT_TYPES];

// Objects that must be remapped so we can reference by index
// If you change this array then you must change the defines in the header file
// #ifdef _WIN32
// char *Static_object_names[]={TBL_GENERIC("GuideBot"),TBL_GENERIC("ChaffChunk"),TBL_GENERIC("GuideBotRed")};
// #else
const char *Static_object_names[] = {TBL_GENERIC("GuideBot"), TBL_GENERIC("ChaffChunk"),TBL_GENERIC("GuideBotRed")};
// #endif

#define NUM_STATIC_OBJECTS (sizeof(Static_object_names) / sizeof(*Static_object_names))

#ifdef EDITOR
const char * const Movement_class_names[] = {"Standing", "Flying", "Rolling", "Walking", "Jumping"};
const char * const Anim_state_names[] = {"Alert",
                            "Death",
                            "Fire Missile 1",
                            "Missile Recoil 1",
                            "Fire Missile 2",
                            "Missile Recoil 2",
                            "Melee 1",
                            "Melee Recoil 1",
                            "Melee 2",
                            "Melee Recoil 2",
                            "Idle",
                            "Quirk",
                            "Flinch",
                            "Taunt",
                            "To Standing Idle",
                            "To Flying Idle",
                            "To Rolling Idle",
                            ";To Walking Idle",
                            "To Jumping Idle",
                            "Goto standing",
                            "Goto flying",
                            "Goto rolling",
                            "Goto walking",
                            "Goto jumping"};
#endif

// Sets all objects to unused
void InitObjectInfo() {
  int i;

  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    Object_info[i].type = OBJ_NONE;
    Object_info[i].name[0] = 0;
    // Object_info[i].script_name[0] = 0;
    Object_info[i].script_name_override[0] = 0;
    Object_info[i].multi_allowed = 1;
    Object_info[i].module_name[0] = 0;
  }

  for (i = 0; i < MAX_OBJECT_TYPES; i++)
    Num_object_ids[i] = 0;

  atexit(FreeObjectInfo);
}

#define DEFAULT_OBJECT_SIZE 4.0f
#define DEFAULT_OBJECT_MASS 1.0f
#define DEFAULT_OBJECT_DRAG 0.1f
#define DEFAULT_OBJECT_ROTDRAG 0.01f

// Allocs a object for use, returns -1 if error, else index on success
int AllocObjectID(int type, bool f_anim, bool f_weapons, bool f_ai) {
  int j, k;

  for (int i = NUM_STATIC_OBJECTS; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type == OBJ_NONE) {
      mprintf(1, "%d ", type);
      memset(&Object_info[i], 0, sizeof(object_info));

      extern void AISetDefault(t_ai_info * ai_info_ptr);
      if (f_ai) {
        Object_info[i].ai_info = (t_ai_info *)mem_malloc(sizeof(t_ai_info));
        memset(Object_info[i].ai_info, 0, sizeof(t_ai_info));
        AISetDefault(Object_info[i].ai_info);
      }
      // Make sure the weapon battery info is cleared for a new object
      if (f_weapons) {
        Object_info[i].static_wb = (otype_wb_info *)mem_malloc(sizeof(otype_wb_info) * MAX_WBS_PER_OBJ);
        memset(Object_info[i].static_wb, 0, sizeof(otype_wb_info) * MAX_WBS_PER_OBJ);
        WBClearInfo(Object_info[i].static_wb);
      }

      if (f_anim) {
        Object_info[i].anim = (anim_elem *)mem_malloc(sizeof(anim_elem) * NUM_MOVEMENT_CLASSES);
        memset(Object_info[i].anim, 0, sizeof(anim_elem) * NUM_MOVEMENT_CLASSES);
        for (j = 0; j < NUM_MOVEMENT_CLASSES; j++)
          for (k = 0; k < NUM_ANIMS_PER_CLASS; k++) {
            Object_info[i].anim[j].elem[k].spc = 1.0f;
            Object_info[i].anim[j].elem[k].anim_sound_index = SOUND_NONE_INDEX;
          }
      }

      Object_info[i].type = type;
      Object_info[i].size = DEFAULT_OBJECT_SIZE;
      Object_info[i].phys_info.mass = DEFAULT_OBJECT_MASS;
      Object_info[i].phys_info.drag = DEFAULT_OBJECT_DRAG;
      Object_info[i].phys_info.rotdrag = DEFAULT_OBJECT_ROTDRAG;

      Object_info[i].phys_info.flags = PF_BOUNCE;
      Object_info[i].phys_info.num_bounces = -1;
      Object_info[i].phys_info.coeff_restitution = 1.0;
      Object_info[i].phys_info.hit_die_dot = -1; //-1 mean doesn't apply

      Object_info[i].med_render_handle = -1;
      Object_info[i].lo_render_handle = -1;
      Object_info[i].med_lod_distance = DEFAULT_MED_LOD_DISTANCE;
      Object_info[i].lo_lod_distance = DEFAULT_LO_LOD_DISTANCE;
      Object_info[i].respawn_scalar = 1.0;

      if (type == OBJ_CLUTTER || type == OBJ_ROBOT) {
        Object_info[i].med_lod_distance *= 10;
        Object_info[i].lo_lod_distance *= 10;
      }

      // Object_info[i].script_name[0] = 0;
      Object_info[i].icon_name[0] = 0;
      Object_info[i].description = NULL;
      Object_info[i].flags |= OIF_INVEN_SELECTABLE;

      // init spew types
      for (j = 0; j < MAX_DSPEW_TYPES; j++) {
        Object_info[i].dspew[j] = -1;
        Object_info[i].dspew_number[j] = 0;
      }

      // init ammo count
      Object_info[i].ammo_count = 0;
      Object_info[i].multi_allowed = 1;
      Num_object_ids[type]++;
      return i;
    }
  }

  Int3(); // No slots free!
  return -1;
}

// Frees object index n
void FreeObjectID(int n) {
  ASSERT(Object_info[n].type != OBJ_NONE);

  Num_object_ids[Object_info[n].type]--;
  Object_info[n].type = OBJ_NONE;
  Object_info[n].name[0] = 0;
  Object_info[n].icon_name[0] = 0;
  Object_info[n].script_name_override[0] = 0;
  Object_info[n].module_name[0] = 0;
  if (Object_info[n].description) {
    mem_free(Object_info[n].description);
    Object_info[n].description = NULL;
  }
  if (Object_info[n].anim) // DAJ LEAK FIX
  {
    mem_free(Object_info[n].anim);
    Object_info[n].anim = NULL;
  }
  if (Object_info[n].ai_info) // DAJ LEAK FIX
  {
    mem_free(Object_info[n].ai_info);
    Object_info[n].ai_info = NULL;
  }
  if (Object_info[n].description) // DAJ LEAK FIX
  {
    mem_free(Object_info[n].description);
    Object_info[n].description = NULL;
  }
  if (Object_info[n].static_wb) // DAJ LEAK FIX
  {
    mem_free(Object_info[n].static_wb);
    Object_info[n].static_wb = NULL;
  }
}

// Frees up all the Objects and any memory allocated
void FreeObjectInfo(void) {
  for (int i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE)
      FreeObjectID(i);
  }
}

// Find an object with the given type.  Returns -1 if none found.
int GetObjectID(int type) {
  int i;

  for (i = 0; i < MAX_OBJECT_IDS; i++)
    if (Object_info[i].type == type)
      return i;

  return -1;
}

#ifdef EDITOR

// Gets next object from n of the same type as n
int GetNextObjectID(int n) {
  int i;
  int type = Object_info[n].type;

  ASSERT(n >= 0 && n < MAX_OBJECT_IDS);

  if (Num_object_ids[type] == 0)
    return -1;

  for (i = n + 1; i < MAX_OBJECT_IDS; i++)
    if (Object_info[i].type == Object_info[n].type)
      return i;

  for (i = 0; i <= n; i++)
    if (Object_info[i].type == Object_info[n].type)
      return i;

  Int3(); // shouldn't be here
  return n;
}

// Gets previous object from n that has the same type
int GetPrevObjectID(int n) {
  int i;
  int type = Object_info[n].type;

  ASSERT(n >= 0 && n < MAX_OBJECT_IDS);

  if (Num_object_ids[type] == 0)
    return -1;

  for (i = n - 1; i >= 0; i--) {
    if (Object_info[i].type == Object_info[n].type)
      return i;
  }

  for (i = MAX_OBJECT_IDS - 1; i >= n; i--) {
    if (Object_info[i].type == Object_info[n].type)
      return i;
  }

  Int3(); // shouldn't get here
  return n;
}
#endif

// Searches thru all object ids for a specific name
// Returns the found id, or -1 if not found
int FindObjectIDName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_OBJECT_IDS; i++)
    if ((Object_info[i].type != OBJ_NONE) && !stricmp(name, Object_info[i].name))
      return i;

  return -1;
}

// Given an object handle, returns an index to that object's model
int GetObjectImage(int handle) {
  if (Object_info[handle].type == OBJ_NONE)
    return -1;
  else
    return (Object_info[handle].render_handle);
}

// Given an object, renders the representation of this object
void DrawObject(object *obj) {
  ASSERT(Object_info[obj->id].type != OBJ_NONE);

  if (obj->render_type == RT_POLYOBJ)
    DrawPolygonModel(&obj->pos, &obj->orient, Object_info[obj->id].render_handle, NULL, 0, 1.0, 1.0, 1.0,
                     obj->rtype.pobj_info.subobj_flags);
  else
    Int3();
}

// Go through the object list and update an ID which has changed
void RemapObjects(int old_id, int new_id) {
  int i;

  for (i = 0; i < MAX_OBJECTS; i++)
    if ((Objects[i].type == Object_info[new_id].type) && (Objects[i].id == old_id))
      Objects[i].id = new_id;

  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type != OBJ_NONE) {
      int j;

      for (j = 0; j < MAX_DSPEW_TYPES; j++)
        if (Object_info[i].dspew[j] == old_id)
          Object_info[i].dspew[j] = new_id;
    }
  }
}

// Remap all the static object ids (objects that must have a specific index) into their assigned slots.
void RemapStaticIDs() {
  bool f_anim = false;
  bool f_weapons = false;
  bool f_ai = false;

  for (int i = 0; i < NUM_STATIC_OBJECTS; i++) {

    int cur_index = FindObjectIDName(IGNORE_TABLE(Static_object_names[i]));

    if (cur_index == -1) {
      // The object we are trying to find is not loaded or doesn't exist
      Error("Cannot find object <%s>", Static_object_names[i]);
      continue;
    }

    if (cur_index == i)
      continue; // hurray, we're already matched up!

    // If our slot is already used, move the ID somewhere else
    if (Object_info[i].type != OBJ_NONE) {
      //			int new_index = AllocObjectID(Object_info[i].type, Object_info[i].flags);
      if (Object_info[i].anim)
        f_anim = true;
      if (Object_info[i].static_wb)
        f_weapons = true;
      if (Object_info[i].ai_info)
        f_ai = true;
      int new_index = AllocObjectID(Object_info[i].type, f_anim, f_weapons, f_ai);
      if (new_index >= 0) { // DAJ -1FIX
        Object_info[new_index] = Object_info[i];
        RemapObjects(i, new_index);
      }
    }

    // Copy static ID into new slot
    Object_info[i] = Object_info[cur_index];

    // Free up the old slot
    Object_info[cur_index].type = OBJ_NONE;

    // Remap the objects that used this ID
    RemapObjects(cur_index, i);
  }
}

// Changes all existing objects model_nums to a new model num
void ChangeOldModelsForObjects(int old_handle, int new_handle) {
  int i;

  for (i = 0; i <= Highest_object_index; i++) {
    if (Objects[i].render_type == RT_POLYOBJ && Objects[i].rtype.pobj_info.model_num == old_handle) {
      Objects[i].rtype.pobj_info.model_num = new_handle;
    }
  }
}

void RemapObjects() { RemapStaticIDs(); };
