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

// generic.cpp
// 0.1
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "osiris_import.h"
#include "osiris_common.h"

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
const char *GetStringFromTable(int index) {
  if ((index < 0) || (index >= String_table_size))
    return _Error_string;
  if (!String_table[index])
    return _Empty_string;
  return String_table[index];
}
#define TXT(x) GetStringFromTable(x)
#define TXT_DOORLOCKED TXT(0)     //"Door Locked!"
#define TXT_RAPIDFIRE TXT(1)      //"Rapid Fire!"
#define TXT_FORCEWALL TXT(2)      //"Force Wall!"
#define TXT_FORCEWALLEJECT TXT(3) //"Force Wall Ejected!"
#define TXT_FORCEWALLDONE TXT(4)  //"Force Wall Done!"
#define TXT_WINGNUT TXT(5)        //"WingNut!"
#define TXT_RAPIDFIREOFF TXT(6)   //"Rapid Fire Off!"
// ================
// Helper Functions
// ================
void AddHudMessage(int player_objhandle, int color, const char *format, ...);

#define ID_RAPIDFIRE 0
#define ID_FORCEWALL 1
#define ID_WINGNUT 2
#define NUM_IDS 3

// Common Powerups
// Weapon Powerups
// Ammo Powerups
#define GENERIC_POWERUP_SCRIPTID NUM_IDS
//	Generic Door Script
#define GENERIC_DOOR_SCRIPTID NUM_IDS + 1

struct tScriptIDInfo {
  int id;
  const char *name;
};

static tScriptIDInfo ScriptIDInfo[NUM_IDS] = {
    {ID_RAPIDFIRE, "RapidFire"}, {ID_FORCEWALL, "Forcewall"}, {ID_WINGNUT, "GoWingNut"}};

class GenericScript {
public:
  GenericScript() {}
  virtual int16_t CallEvent(int event, tOSIRISEventInfo *data);

protected:
};

class GenericDoor : public GenericScript {
public:
  GenericDoor() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

struct forcewallmemory {
  int object_handle;
};

class ForceWallScript : public GenericScript {
public:
  ForceWallScript();
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
  forcewallmemory *memory;
};

class WingNutScript : public GenericScript {
public:
  WingNutScript() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

struct tPlayerTimerInfo {
  int timer_handle;
};
tPlayerTimerInfo RapidFirePlayerTimers[MAX_PLAYERS];

struct rapidfirememory {
  int collided_object;
  uint8_t collided_pnum;
};

class RapidFireScript : public GenericScript {
public:
  RapidFireScript();

  int16_t CallEvent(int event, tOSIRISEventInfo *data);
  rapidfirememory *memory;
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
  if (func_list->game_checksum != CHECKSUM) {
    mprintf(0, "Game-Checksum FAIL!!! (%ul!=%ul)\n", func_list->game_checksum, CHECKSUM);
    mprintf(0, "RECOMPILE YOUR SCRIPTS!!!\n");
    return 0;
  }

  String_table_size = func_list->string_count;
  String_table = func_list->string_table;

  int i;

  // initialize rapid fire script data
  for (i = 0; i < MAX_PLAYERS; i++) {
    RapidFirePlayerTimers[i].timer_handle = -1;
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
    for (int i = 0; i < NUM_IDS; i++) {
      if (!stricmp(ScriptIDInfo[i].name, name))
        return ScriptIDInfo[i].id;
    }
  }

  return (isdoor) ? GENERIC_DOOR_SCRIPTID : GENERIC_POWERUP_SCRIPTID;
}

//	CreateInstance
//	Purpose:
//		Given an ID from a call to GetGOScriptID(), this function will create a new instance for that
//	particular script (by allocating and initializing memory, etc.).  A pointer to this instance
//	is to be returned back to Descent 3.  This pointer will be passed around, along with the ID
//	for CallInstanceEvent() and DestroyInstance().  Return NULL if there was an error.
void STDCALLPTR CreateInstance(int id) {
  switch (id) {
  case GENERIC_POWERUP_SCRIPTID:
    return new GenericScript;
    break;
  case GENERIC_DOOR_SCRIPTID:
    return new GenericDoor;
    break;
  case ID_RAPIDFIRE:
    return new RapidFireScript;
    break;
  case ID_WINGNUT:
    return new WingNutScript;
    break;
  case ID_FORCEWALL:
    return new ForceWallScript;
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
  case GENERIC_POWERUP_SCRIPTID:
    delete ((GenericScript *)ptr);
    break;
  case GENERIC_DOOR_SCRIPTID:
    delete ((GenericDoor *)ptr);
    break;
  case ID_RAPIDFIRE:
    delete ((RapidFireScript *)ptr);
    break;
  case ID_WINGNUT:
    delete ((WingNutScript *)ptr);
    break;
  case ID_FORCEWALL:
    delete ((ForceWallScript *)ptr);
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
  switch (id) {
  case GENERIC_POWERUP_SCRIPTID:
  case GENERIC_DOOR_SCRIPTID:
  case ID_RAPIDFIRE:
  case ID_FORCEWALL:
  case ID_WINGNUT:
    return ((GenericScript *)ptr)->CallEvent(event, data);
    break;
  };

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
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
#define VERSION 0x01
int STDCALL SaveRestoreState(void *file_ptr, uint8_t saving_state) {
  int size = 0;

  int i;
  int version = VERSION;

  if (saving_state) {
    File_WriteByte(VERSION, file_ptr);
    size++;

    // save out rapid fire data
    for (i = 0; i < MAX_PLAYERS; i++) {
      File_WriteInt(RapidFirePlayerTimers[i].timer_handle, file_ptr);
      size += sizeof(int);
    }
  } else {
    version = File_ReadByte(file_ptr);
    size++;

    // restore rapid fire data
    for (i = 0; i < MAX_PLAYERS; i++) {
      RapidFirePlayerTimers[i].timer_handle = File_ReadInt(file_ptr);
      size += sizeof(int);
    }
  }

  return size;
}

int16_t GenericScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    msafe_struct ms;
    ms.objhandle = data->evt_collide.it_handle;
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);
    if (ms.type == OBJ_PLAYER) {
      ms.objhandle = data->me_handle;
      ms.ithandle = data->evt_collide.it_handle;
      ms.playsound = 1;
      MSafe_DoPowerup(&ms);
      return CONTINUE_CHAIN | CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t GenericDoor::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    msafe_struct ms;
    ms.objhandle = data->me_handle;
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);
    if (ms.type == OBJ_DOOR) {
      msafe_struct mit;

      mit.objhandle = data->evt_collide.it_handle;
      MSafe_GetValue(MSAFE_OBJECT_TYPE, &mit);

      if (mit.type == OBJ_CLUTTER) {
        break;
      }

      // See if door is openable
      ms.ithandle = data->evt_collide.it_handle;
      MSafe_GetValue(MSAFE_DOOR_OPENABLE, &ms);

      if (ms.state) {
        // openable door
        MSafe_CallFunction(MSAFE_DOOR_ACTIVATE, &ms);
      } else {
        // non-openable door.  If locked, give a message
        MSafe_GetValue(MSAFE_DOOR_LOCK_STATE, &ms);
        if (ms.state) { // locked!
          ms.objhandle = data->evt_collide.it_handle;

          MSafe_GetValue(MSAFE_OBJECT_PARENT, &ms);
          MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);

          if (ms.type == OBJ_PLAYER) {
            strcpy(ms.message, TXT_DOORLOCKED);
            ms.color = GR_RGB(0, 255, 0);
            MSafe_CallFunction(MSAFE_MISC_FILTERED_HUD_MESSAGE, &ms);

            ms.state = 1; // specific player
            ms.index = Scrpt_FindSoundName("DoorIsLocked");
            ms.volume = 0.80f;
            if (ms.index != -1)
              MSafe_CallFunction(MSAFE_SOUND_2D, &ms);
          }
        }
      }
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

RapidFireScript::RapidFireScript() { memory = NULL; }

#define RAPIDFIRE_RECHARGE 0.7f
int16_t RapidFireScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(rapidfirememory);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (rapidfirememory *)Scrpt_MemAlloc(&ch);
    memory->collided_pnum = 255;
    memory->collided_object = OBJECT_HANDLE_NONE;

  } break;

  case EVT_MEMRESTORE: {
    memory = (rapidfirememory *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_COLLIDE: {
    if (!memory)
      break;

    msafe_struct ms;
    ms.objhandle = data->evt_collide.it_handle;
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);

    if (ms.type == OBJ_PLAYER) {

      AddHudMessage(data->evt_collide.it_handle, GR_RGB(0, 255, 0), TXT_RAPIDFIRE);
      int sound_id = Sound_FindId("RapidFireOn");
      Sound_Play3d(data->me_handle, sound_id);

      MSafe_GetValue(MSAFE_OBJECT_ID, &ms);
      memory->collided_pnum = ms.id;
      memory->collided_object = data->evt_collide.it_handle;

      if (RapidFirePlayerTimers[memory->collided_pnum].timer_handle != -1) {

        // check to see if the player currently has rapid fire
        MSafe_GetValue(MSAFE_OBJECT_RECHARGE_SCALAR, &ms);
        if (ms.scalar == RAPIDFIRE_RECHARGE) {
          // the player currently has rapid fire
          // the player possibly has rapid fire set, check to make sure
          if (Scrpt_TimerExists(RapidFirePlayerTimers[memory->collided_pnum].timer_handle)) {
            // cancel the old timer so we can create a new timer (give them more time)
            Scrpt_CancelTimer(RapidFirePlayerTimers[memory->collided_pnum].timer_handle);
          }

          RapidFirePlayerTimers[memory->collided_pnum].timer_handle = -1;
        } else {
          // rapid fire was stolen from the player
        }
      }

      memory->collided_pnum = ms.id;
      tOSIRISTIMER ti;
      ti.flags = OTF_CANCELONDEAD;
      ti.id = 31;
      ti.object_handle = data->me_handle;
      ti.object_handle_detonator = data->evt_collide.it_handle;
      ti.timer_interval = 30;
      RapidFirePlayerTimers[memory->collided_pnum].timer_handle = Scrpt_CreateTimer(&ti);

      // ghost the object
      ms.objhandle = data->me_handle;
      MSafe_CallFunction(MSAFE_OBJECT_GHOST, &ms);

      // set player scalar
      ms.objhandle = data->evt_collide.it_handle;
      ms.scalar = RAPIDFIRE_RECHARGE;
      MSafe_CallFunction(MSAFE_OBJECT_RECHARGE_SCALAR, &ms);
    }

  } break;
  case EVT_TIMER: {
    if (!memory)
      break;

    msafe_struct ms;
    ms.objhandle = memory->collided_object;
    MSafe_GetValue(MSAFE_OBJECT_RECHARGE_SCALAR, &ms);

    if (ms.scalar == RAPIDFIRE_RECHARGE) {
      // reset recharge scalar
      ms.objhandle = memory->collided_object;
      ms.scalar = 1.0f;
      MSafe_CallFunction(MSAFE_OBJECT_RECHARGE_SCALAR, &ms);
      RapidFirePlayerTimers[memory->collided_pnum].timer_handle = -1;
    }

    AddHudMessage(memory->collided_object, GR_RGB(0, 255, 0), TXT_RAPIDFIREOFF);
    int sound_id = Sound_FindId("RapidFireOff");
    Sound_Play3d(memory->collided_object, sound_id);

    // destroy the powerup
    ms.objhandle = data->me_handle;
    ms.playsound = 0;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &ms);

  } break;
  case EVT_TIMERCANCEL: {
    msafe_struct ms;

    // destroy the powerup
    ms.playsound = 0;
    ms.objhandle = data->me_handle;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &ms);
  } break;
  case EVT_INTERVAL: {
    // check (if we are ghosted...meaning picked up) if the player
    // that picked us up still has rapid fire
    if (memory && memory->collided_pnum != 255) {
      // check the player to make sure he is still charged up
      msafe_struct ms;
      ms.objhandle = memory->collided_object;
      MSafe_GetValue(MSAFE_OBJECT_RECHARGE_SCALAR, &ms);

      if (ms.scalar != RAPIDFIRE_RECHARGE) {
        // player no longer recharged! cancel timer
        if (Scrpt_TimerExists(RapidFirePlayerTimers[memory->collided_pnum].timer_handle)) {
          // cancel the timer
          mprintf(0, "CANCELING RAPID FIRE TIMER FOR PLAYER %d\n", memory->collided_pnum);
          Scrpt_CancelTimer(RapidFirePlayerTimers[memory->collided_pnum].timer_handle);

          AddHudMessage(memory->collided_object, GR_RGB(0, 255, 0), TXT_RAPIDFIREOFF);
          int sound_id = Sound_FindId("RapidFireOff");
          Sound_Play3d(memory->collided_object, sound_id);
        }

        RapidFirePlayerTimers[memory->collided_pnum].timer_handle = -1;
        memory->collided_pnum = 255;
        memory->collided_object = OBJECT_HANDLE_NONE;
      }
    }

  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

ForceWallScript::ForceWallScript() { memory = NULL; }

int16_t ForceWallScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {

  case EVT_CREATED: {
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(forcewallmemory);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (forcewallmemory *)Scrpt_MemAlloc(&ch);
    memory->object_handle = OBJECT_HANDLE_NONE;

  } break;

  case EVT_MEMRESTORE: {
    memory = (forcewallmemory *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_COLLIDE: {
    if (!memory)
      break;

    msafe_struct ms;
    ms.objhandle = data->evt_collide.it_handle;
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);
    int pnum;

    if (ms.type == OBJ_PLAYER) {
      MSafe_GetValue(MSAFE_OBJECT_ID, &ms);
      pnum = ms.id;

      AddHudMessage(data->evt_collide.it_handle, GR_RGB(0, 255, 0), TXT_FORCEWALL);

      // add a force wall to the inventory
      ms.objhandle = data->me_handle;
      MSafe_GetValue(MSAFE_OBJECT_ID, &ms);
      ms.slot = pnum;
      ms.type = OBJ_POWERUP;
      ms.flags = INVAF_TIMEOUTONSPEW;
      MSafe_CallFunction(MSAFE_INVEN_ADD_TYPE_ID, &ms);

      // pickit up
      ms.playsound = 1;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &ms);
    }
  } break;
  case EVT_USE: {
    if (!memory)
      break;

    msafe_struct ms;

    // Eject a ForceWall and make it last for 60 seconds
    memory->object_handle = data->evt_use.it_handle; // save the player for when the timer is up

    AddHudMessage(memory->object_handle, GR_RGB(0, 255, 0), TXT_FORCEWALLEJECT);

    // ghost the object and set a timer
    tOSIRISTIMER ti;
    ti.flags = 0; // not a volatile object when dropped
    ti.id = 32;
    ti.object_handle = data->me_handle;
    ti.timer_interval = 60;
    Scrpt_CreateTimer(&ti);

    // ghost the object
    ms.objhandle = data->me_handle;
    MSafe_CallFunction(MSAFE_OBJECT_GHOST, &ms);

    // Do the Force Wall stuff here

  } break;
  case EVT_TIMER: {
    if (!memory)
      break;

    msafe_struct ms;

    // End Force Wall stuff here

    AddHudMessage(memory->object_handle, GR_RGB(0, 255, 0), TXT_FORCEWALLDONE);

    // UnGhost the object
    ms.objhandle = data->me_handle;
    //@@MSafe_CallFunction(MSAFE_OBJECT_UNGHOST,&ms);

    // destroy the powerup
    ms.playsound = 0;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &ms);

  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t WingNutScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    msafe_struct ms;
    ms.objhandle = data->evt_collide.it_handle;
    MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);
    int pnum;

    if (ms.type == OBJ_PLAYER) {
      MSafe_GetValue(MSAFE_OBJECT_ID, &ms);
      pnum = ms.id;

      AddHudMessage(data->evt_collide.it_handle, GR_RGB(0, 255, 0), TXT_WINGNUT);

      // add a wing nut to the inventory
      ms.objhandle = data->me_handle;
      MSafe_GetValue(MSAFE_OBJECT_ID, &ms);
      ms.slot = pnum;
      ms.type = OBJ_POWERUP;
      ms.flags = INVAF_TIMEOUTONSPEW;
      MSafe_CallFunction(MSAFE_INVEN_ADD_TYPE_ID, &ms);

      // pickit up
      ms.playsound = 1;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &ms);
    }
  } break;
  case EVT_USE: {
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

void AddHudMessage(int player_objhandle, int color, const char *format, ...) {
  msafe_struct ms;
  ms.objhandle = player_objhandle;
  MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);
  if (ms.type == OBJ_PLAYER) {
    MSafe_GetValue(MSAFE_OBJECT_ID, &ms);
    ms.slot = ms.id;
    ms.color = color;
    char big_buffer[1024];
    va_list marker;
    va_start(marker, format);
    std::vsnprintf(big_buffer, sizeof(big_buffer), format, marker);
    va_end(marker);
    strncpy(ms.message, big_buffer, MSAFE_MESSAGE_LENGTH - 1);
    ms.message[MSAFE_MESSAGE_LENGTH - 1] = '\0';

    MSafe_CallFunction(MSAFE_MISC_FILTERED_HUD_MESSAGE, &ms);
  }
}
