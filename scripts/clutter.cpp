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

// clutter.cpp
// 0.1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osiris_import.h"
#include "osiris_common.h"
#include "osiris_vector.h"

#include "module.h"

#ifdef __cplusplus
extern "C" {
#endif
DLLEXPORT char STDCALL InitializeDLL(tOSIRISModuleInit *func_list);
DLLEXPORT void STDCALL ShutdownDLL(void);
DLLEXPORT int STDCALL GetGOScriptID(const char *name, uint8_t isdoor);
DLLEXPORT void STDCALLPTR CreateInstance(int id);
DLLEXPORT void STDCALL DestroyInstance(int id, void *ptr);
DLLEXPORT int16_t STDCALL CallInstanceEvent(int id, void *ptr, int event, tOSIRISEventInfo *data);
DLLEXPORT int STDCALL SaveRestoreState(void *file_ptr, uint8_t saving_state);
#ifdef __cplusplus
}
#endif

static int String_table_size = 0;
static char **String_table = NULL;
static const char *_Error_string = "!!ERROR MISSING STRING!!";
static const char *_Empty_string = "";
static const char *GetStringFromTable(int index) {
  if ((index < 0) || (index >= String_table_size))
    return _Error_string;
  if (!String_table[index])
    return _Empty_string;
  return String_table[index];
}
#define TXT(x) GetStringFromTable(x)

#define ID_FRAGCRATE 0
#define ID_NAPALMBARREL 1
#define ID_ALIENCUPLINK 2
#define ID_TNTHIGHYIELD 3
#define ID_TNTMEDYIELD 4
#define ID_FALLINGROCK 5
#define ID_LAVAROCK 6

struct tScriptInfo {
  int id;
  const char *name;
};

static tScriptInfo ScriptIDs[] = {{ID_FRAGCRATE, "fragcrate"},
                                  {ID_NAPALMBARREL, "napalmbarrel"},
                                  {ID_ALIENCUPLINK, "Aliencuplink"},
                                  {ID_TNTHIGHYIELD, "TNTCrateHighYield"},
                                  {ID_TNTMEDYIELD, "TNTCrateMediumYield"},
                                  {ID_FALLINGROCK, "FallingRock"},
                                  {ID_LAVAROCK, "LavaRock"}};

static constexpr int NumScriptIDs = sizeof(ScriptIDs) / sizeof(tScriptInfo);

class ClutterScript {
public:
  virtual int16_t CallEvent(int event, tOSIRISEventInfo *data) { return CONTINUE_CHAIN | CONTINUE_DEFAULT; }
};

class FragCrate : public ClutterScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class NapalmBarrel : public ClutterScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class AliencuplinkScript : public ClutterScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

struct tTNTHighYield {
  vector last_vel;
  float lifetime;
};
class TNTHighYield : public ClutterScript {
public:
  TNTHighYield() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
  tTNTHighYield *memory;
};

class TNTMedYield : public ClutterScript {
public:
  TNTMedYield() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
  float *memory;
};

struct tFallingRock {
  float lifeleft;
};
class FallingRock : public ClutterScript {
public:
  FallingRock() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
  tFallingRock *memory;
};
class LavaRock : public ClutterScript {
public:
  LavaRock() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
  tFallingRock *memory;
};

//	InitializeDLL
//	Purpose:
//		This function gets called when the DLL first gets loaded.  It will only be called once (until the
//	DLL is unloaded).  Passed in is a struct of data passed from the game needed for the DLL to interact
//	with D3.  Usually this function will just call osicommon_Initialize(), which sets up the imported
//	functions.  However, you can alloc some memory or whatever in this function, and free it in ShutdownDLL().
//	Note: You cannot call any imported functions until osicommon_Initialize() is called.
//	Returns 1 if initialization went ok, 0 if there was an error and the DLL should not be loaded.
char STDCALL InitializeDLL(tOSIRISModuleInit *func_list) {
  osicommon_Initialize((tOSIRISModuleInit *)func_list);
  String_table_size = func_list->string_count;
  String_table = func_list->string_table;
  if (func_list->game_checksum != CHECKSUM) {
    mprintf(0, "Game-Checksum FAIL!!! (%ul!=%ul)\n", func_list->game_checksum, CHECKSUM);
    mprintf(0, "RECOMPILE YOUR SCRIPTS!!!\n");
    return 0;
  }
  return 1;
}

//	ShutdownDLL
//	Purpose:
//		This function is called right before a DLL is about to be unloaded from memory.  You can free
//	any unfree'd memory, or anything else you need to do.  Don't worry about destroying any instances
//	of scripts, as they will all be automatically destroyed before this function is called.  The
//	same goes for any memory allocated with Scrpt_MemAlloc(), as this will automatically be freed
//	when a scripts instance is destroyed.
void STDCALL ShutdownDLL(void) {}

//	GetGOScriptID
//	Purpose:
//		Given the name of the object (from it's pagename), this function will search through it's
//	list of General Object Scripts for a script with a matching name (to see if there is a script
//	for that type/id of object within this DLL).  If a matching scriptname is found, a UNIQUE ID
//	is to be returned back to Descent 3.  This ID will be used from here on out for all future
//	interaction with the DLL.  Since doors are not part of the generic object's, it's possible
//	for a door to have the same name as a generic object (OBJ_POWERUP, OBJ_BUILDING, OBJ_CLUTTER
//	or OBJ_ROBOT), therefore, a 1 is passed in for isdoor if the given object name refers to a
//	door, else it is a 0.  The return value is the unique identifier, else -1 if the script
//	does not exist in the DLL.
int STDCALL GetGOScriptID(const char *name, uint8_t isdoor) {
  if (!isdoor) {
    for (int i = 0; i < NumScriptIDs; i++) {
      if (!stricmp(name, ScriptIDs[i].name))
        return ScriptIDs[i].id;
    }
  }

  return -1;
}

//	CreateInstance
//	Purpose:
//		Given an ID from a call to GetGOScriptID(), this function will create a new instance for that
//	particular script (by allocating and initializing memory, etc.).  A pointer to this instance
//	is to be returned back to Descent 3.  This pointer will be passed around, along with the ID
//	for CallInstanceEvent() and DestroyInstance().  Return NULL if there was an error.
void STDCALLPTR CreateInstance(int id) {
  switch (id) {
  case ID_FRAGCRATE:
    return new FragCrate;
    break;
  case ID_NAPALMBARREL:
    return new NapalmBarrel;
    break;
  case ID_ALIENCUPLINK:
    return new AliencuplinkScript;
    break;
  case ID_TNTHIGHYIELD:
    return new TNTHighYield;
    break;
  case ID_TNTMEDYIELD:
    return new TNTMedYield;
    break;
  case ID_FALLINGROCK:
    return new FallingRock;
    break;
  case ID_LAVAROCK:
    return new LavaRock;
    break;
  };
  return NULL;
}

//	DestroyInstance
//	Purpose:
//		Given an ID, and a pointer to a particular instance of a script, this function will delete and
//	destruct all information associated with that script, so it will no longer exist.
void STDCALL DestroyInstance(int id, void *ptr) {
  switch (id) {
  case ID_FRAGCRATE:
    delete ((FragCrate *)ptr);
    break;
  case ID_NAPALMBARREL:
    delete ((NapalmBarrel *)ptr);
    break;
  case ID_ALIENCUPLINK:
    delete ((AliencuplinkScript *)ptr);
    break;
  case ID_TNTHIGHYIELD:
    delete ((TNTHighYield *)ptr);
    break;
  case ID_TNTMEDYIELD:
    delete ((TNTMedYield *)ptr);
    break;
  case ID_FALLINGROCK:
    delete ((FallingRock *)ptr);
    break;
  case ID_LAVAROCK:
    delete ((LavaRock *)ptr);
    break;
  };
}

//	CallInstanceEvent
//	Purpose:
//		Given an ID, a pointer to a script instance, an event and a pointer to the struct of
//	information about the event, this function will translate who this event belongs to and
//	passes the event to that instance of the script to be handled.  Return a combination of
//	CONTINUE_CHAIN and CONTINUE_DEFAULT, to give instructions on what to do based on the
//	event. CONTINUE_CHAIN means to continue through the chain of scripts (custom script, level
//	script, mission script, and finally default script).  If CONTINUE_CHAIN is not specified,
//	than the chain is broken and those scripts of lower priority will never get the event.  Return
//	CONTINUE_DEFAULT in order to tell D3 if you want process the normal action that is built into
//	the game for that event.  This only pertains to certain events.  If the chain continues
//	after this script, than the CONTINUE_DEFAULT setting will be overridden by lower priority
//	scripts return value.
int16_t STDCALL CallInstanceEvent(int id, void *ptr, int event, tOSIRISEventInfo *data) {
  return ((ClutterScript *)ptr)->CallEvent(event, data);
}

//	SaveRestoreState
//	Purpose:
//		This function is called when Descent 3 is saving or restoring the game state.  In this function
//	you should save/restore any global data that you want preserved through load/save (which includes
//	demos).  You must be very careful with this function, corrupting the file (reading or writing too
//	much or too little) may be hazardous to the game (possibly making it impossible to restore the
//	state).  It would be best to use version information to keep older versions of saved states still
//	able to be used.  IT IS VERY IMPORTANT WHEN SAVING THE STATE TO RETURN THE NUMBER OF _BYTES_ WROTE
//	TO THE FILE.  When restoring the data, the return value is ignored.  saving_state is 1 when you should
//	write data to the file_ptr, 0 when you should read in the data.
int STDCALL SaveRestoreState(void *file_ptr, uint8_t saving_state) { return 0; }

int GetObjectType(int object) {
  msafe_struct ms;
  ms.objhandle = object;
  MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);

  return ms.type;
}

int GetObjectID(int object) {
  msafe_struct ms;
  ms.objhandle = object;
  MSafe_GetValue(MSAFE_OBJECT_ID, &ms);

  return ms.id;
}

int16_t FragCrate::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY:
    vector pos;
    float mag;
    int weapon_id;
    int handle;
    int i;
    int room;

    Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(data->me_handle, VF_GET, OBJV_V_POS, &pos);
    weapon_id = Wpn_FindID("fragbarrel");

    handle = Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, data->me_handle);

    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t NapalmBarrel::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY:
    vector pos;
    float mag;
    int weapon_id;
    int handle;
    int i;
    int room;
    matrix o, orient;

    Obj_Value(data->me_handle, VF_GET, OBJV_M_ORIENT, &o);
    Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(data->me_handle, VF_GET, OBJV_V_POS, &pos);

    orient.uvec = o.fvec;
    orient.rvec = o.rvec;
    orient.fvec = -o.uvec;

    weapon_id = Wpn_FindID("napalmbarrel");
    // weapon_id = Wpn_FindID("napalmrocket");

    handle = Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, &orient, data->me_handle);

    // Set direction
    vector v;
    float amount_r, amount_u;
    amount_r = (float(rand()) - float(RAND_MAX) / 2.0f) / float(RAND_MAX);
    amount_u = (float(rand()) - float(RAND_MAX) / 2.0f) / float(RAND_MAX);
    v = amount_r * orient.rvec + amount_u * orient.uvec + orient.fvec;
    vm_VectorNormalize(&v);
    v *= 30.0f;
    // v = orient.fvec*30.0f;
    Obj_Value(handle, VF_SET, OBJV_V_VELOCITY, &v);

    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t AliencuplinkScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    int handle, id, room;
    vector pos;
    id = Obj_FindID("Aliencuplinkhousing");

    if (id != -1) {
      Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &room);
      Obj_Value(data->me_handle, VF_GET, OBJV_V_POS, &pos);

      handle = Obj_Create(OBJ_CLUTTER, id, room, &pos, NULL, data->me_handle);

      Obj_AttachObjectAP(data->me_handle, 0, handle, 0, 1);
    }
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

void ObjectDamage(int object, float amount, int killer = OBJECT_HANDLE_NONE);
void ObjectDamage(int object, float amount, int killer) {
  msafe_struct mstruct;

  mstruct.objhandle = object;
  mstruct.killer_handle = killer;
  mstruct.damage_type = GD_SCRIPTED;
  mstruct.amount = amount;

  MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
}

float GetObjectShields(int object) {
  msafe_struct mstruct;

  mstruct.objhandle = object;
  MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &mstruct);

  return mstruct.shields;
}

int16_t TNTMedYield::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    int i;
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(float);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (float *)Scrpt_MemAlloc(&ch);
    *memory = -1.0f;
  } break;

  case EVT_MEMRESTORE: {
    memory = (float *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_INTERVAL: {
    vector vel;
    float vel_val;
    float last_vel;
    float delta_vel;
    float frametime;
    float accel;

    Obj_Value(data->me_handle, VF_GET, OBJV_V_VELOCITY, &vel);
    vel_val = vm_GetMagnitude(&vel);

    frametime = Game_GetFrameTime();
    last_vel = *memory;

    if (last_vel != -1.0f) {
      delta_vel = vel_val - last_vel;
      accel = delta_vel / frametime;

      if (accel <= 0.0002f) {
        // blow him up
        Obj_Kill(data->me_handle, OBJECT_HANDLE_NONE, 1000.0f,
                 DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
                 0.0f, 0.0f);
      }
    }

    *memory = vel_val;
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TNTHighYield::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    int i;
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(tTNTHighYield);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (tTNTHighYield *)Scrpt_MemAlloc(&ch);
    vm_MakeZero(&memory->last_vel);
    memory->lifetime = 0;

  } break;

  case EVT_MEMRESTORE: {
    memory = (tTNTHighYield *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_INTERVAL: {
    vector vel;
    vector diff_vel;
    float vel_val;
    float delta_vel;
    float frametime;
    float accel;

    Obj_Value(data->me_handle, VF_GET, OBJV_V_VELOCITY, &vel);
    vel_val = vm_GetMagnitude(&vel);

    frametime = Game_GetFrameTime();
    diff_vel = vel - (memory->last_vel);
    memory->lifetime += frametime;

    delta_vel = vm_GetMagnitude(&diff_vel);

    accel = fabs(delta_vel / frametime);

    bool case1 = (accel >= 40.0f && vel_val > 35.0f && memory->last_vel.y < -6.0f) ? true : false;
    bool case2 = (accel > 100.0f && vel_val > 50.0f) ? true : false;
    bool case3 = (accel > 1500.0f && memory->last_vel.y < -5.0f) ? true : false;

    if (case1 || case2 || case3) {
      if (case1)
        mprintf(0, "Case 1\n");
      if (case2)
        mprintf(0, "Case 2\n");
      if (case3)
        mprintf(0, "Case 3\n");

      // blow him up
      mprintf(0, "accel: %.2f vel: %.2f\n", accel, vel_val);
      if (memory->lifetime >= 7.0f) {
        Obj_Kill(data->me_handle, OBJECT_HANDLE_NONE, 1000.0f,
                 DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
                 0.0f, 0.0f);
      }
    }

    memory->last_vel = vel;
  } break;

  case EVT_DESTROY: {
    // see if we are within distance of the rock pile to destroy
    int close_obj_list[32];
    int roomnum;
    int rockpile_id;
    float amount;
    vector pos;

    Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &roomnum);
    Obj_Value(data->me_handle, VF_GET, OBJV_V_POS, &pos);
    int num_objects = AI_GetNearbyObjs(&pos, roomnum, 30.0f, close_obj_list, 32, false, false, false, true);

    rockpile_id = Obj_FindID("TNTrockwall");

    for (int i = 0; i < num_objects; i++) {
      int type, id;

      type = GetObjectType(close_obj_list[i]);
      id = GetObjectID(close_obj_list[i]);

      if (type == OBJ_CLUTTER && id == rockpile_id) {
        // destroy the wall
        Obj_Kill(close_obj_list[i], data->me_handle, 1000.0f,
                 DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
                 0.0f, 0.0f);
      }
    }

  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t FallingRock::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    int i;
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(tFallingRock);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (tFallingRock *)Scrpt_MemAlloc(&ch);
    memory->lifeleft = 10.0f;
  } break;

  case EVT_MEMRESTORE: {
    memory = (tFallingRock *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_INTERVAL: {
    if (memory) {
      memory->lifeleft -= data->evt_interval.frame_time;

      if (memory->lifeleft <= 0) {
        // destroy the wall
        Obj_Kill(data->me_handle, OBJECT_HANDLE_NONE, 1000.0f, DF_EXPL_SMALL | DF_FIREBALL | DF_DEBRIS_SMOKES, 0.0f,
                 0.0f);
      }
    }
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t LavaRock::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    int i;
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(tFallingRock);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (tFallingRock *)Scrpt_MemAlloc(&ch);
    memory->lifeleft = 20.0f;

    // Set it on fire!
    msafe_struct mstruct;
    mstruct.objhandle = data->me_handle;
    mstruct.longevity = 25.0f;
    mstruct.interval = 0.0f;
    mstruct.ithandle = OBJECT_HANDLE_NONE;
    MSafe_CallFunction(MSAFE_OBJECT_SETONFIRE, &mstruct);

  } break;

  case EVT_MEMRESTORE: {
    memory = (tFallingRock *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_COLLIDE: {
    // Set it on fire!
    msafe_struct mstruct;
    mstruct.objhandle = data->evt_collide.it_handle;
    mstruct.longevity = 2.0f;
    mstruct.interval = 2.0f;
    mstruct.ithandle = data->me_handle;
    MSafe_CallFunction(MSAFE_OBJECT_SETONFIRE, &mstruct);

  } break;

  case EVT_INTERVAL: {
    if (memory) {
      memory->lifeleft -= data->evt_interval.frame_time;

      if (memory->lifeleft <= 0) {
        // destroy the wall
        Obj_Kill(data->me_handle, OBJECT_HANDLE_NONE, 1000.0f, DF_EXPL_SMALL | DF_FIREBALL | DF_DEBRIS_SMOKES, 0.0f,
                 0.0f);
      }
    }
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}
