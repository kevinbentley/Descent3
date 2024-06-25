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

// AIGame.cpp
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osiris_import.h"
#include "osiris_common.h"
#include "osiris_vector.h"
#include "DallasFuncs.cpp"

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

static void PortalBreakGlass(int portalnum, int roomnum);
// Returns the new child's handle
static int CreateAndAttach(int me, const char *child_name, uint8_t child_type, char parent_ap, char child_ap,
                           bool f_aligned = true, bool f_set_parent = false);
static float Obj_GetObjDist(int me, int it, bool f_sub_rads);

void PortalBreakGlass(int portalnum, int roomnum) {
  msafe_struct mstruct;

  mstruct.roomnum = roomnum;
  mstruct.portalnum = portalnum;

  MSafe_CallFunction(MSAFE_ROOM_BREAK_GLASS, &mstruct);
}

// Returns the new child's handle
int CreateAndAttach(int me, const char *child_name, uint8_t child_type, char parent_ap, char child_ap, bool f_aligned,
                    bool f_set_parent) {
  int child_handle = OBJECT_HANDLE_NONE;
  int child_id = Obj_FindID(child_name);
  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_POS, &m);
  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &m);

  if (child_id >= 0) {
    int parent;
    if (f_set_parent)
      parent = me;
    else
      parent = OBJECT_HANDLE_NONE;

    child_handle = Obj_Create(child_type, child_id, m.roomnum, &m.pos, NULL, parent);
    if (child_handle != OBJECT_HANDLE_NONE) {
      if (!Obj_AttachObjectAP(me, parent_ap, child_handle, child_ap, f_aligned)) {
        // chrishack (we need a way to instantly kill scripted objects)
      }
    }
  }

  return child_handle;
}

// ==========================
// Script class definitions//
// ==========================
#define NUM_IDS 6 // maximum number of IDs

#define ID_MERCENDBOSS 0 // Mercenary End Boss
#define ID_GUN 1         // Mercenary Mino Boss for level 6
#define ID_CASING 2
#define ID_HANGLIGHT 3   // Mercenary Hanging Light
#define ID_COMBWALLHIT 4 // Wall hit for purple big ass gun
#define ID_DROPTARGET 5

struct tScriptInfo {
  int id;
  const char *name;
};

tScriptInfo ScriptInfo[NUM_IDS] = {{ID_MERCENDBOSS, "MercEndBoss"}, {ID_GUN, "Gun"},
                                   {ID_CASING, "Casing"},           {ID_HANGLIGHT, "HangLight"},
                                   {ID_COMBWALLHIT, "CombWallHit"}, {ID_DROPTARGET, "DropTarget"}};

static int aigame_mod_id;
// use this macro to create unique timer IDs
#define CREATE_TIMER_ID(id) ((aigame_mod_id << 16) | (id))

class BaseObjScript {
public:
  BaseObjScript();
  ~BaseObjScript();
  virtual int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

struct tShieldOrbInfo {
  int hitcount;
};

//------------------
// CombWallHit class
//------------------

struct combwallhit_data {
  float time_left;
};

class CombWallHit : public BaseObjScript {
private:
  combwallhit_data *memory;

public:
  CombWallHit() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// DropTarget class
//------------------

struct droptarget_data {
  float time_left;
  float last_set_time;
};

class DropTarget : public BaseObjScript {
private:
  droptarget_data *memory;

public:
  DropTarget() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Gun class
//------------------

struct gun_data {
  int shell_id;
  bool f_fire;
};

class Gun : public BaseObjScript {
  gun_data *memory;

public:
  Gun() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Casing class
//------------------

struct casing_data {
  float time_left;
};

class Casing : public BaseObjScript {
private:
  casing_data *memory;

public:
  Casing() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// MercEndBoss class
//------------------

#define MERCENDBOSS_WAIT 0
#define MERCENDBOSS_INTRO 1
#define MERCENDBOSS_MATTER 2
#define MERCENDBOSS_ENERGY 3
#define MERCENDBOSS_DEATH_BLOSSUM 4
#define MERCENDBOSS_DEATH 5

// Mercenary End Boss Unique Goal IDs
#define MEB_TURN_TOWARDS_CAMERA 0x00010001

struct mercendboss_data {
  int flags;
  char mode;
  char next_mode;
  int turret_object;

  bool f_target_ghost;
  float time_till_fire;

  int wallhit_id;

  bool f_oriented;

  float last_frame;

  int laser_sound;
  float laser_time_left;

  bool f_sub_super;
  float mode_time;
  float sub_mode_time_left;

  float last_spark_time;

  float time_to_next_random_sound;

  int emitter[2];
  int camera;
  int combine_object;
};

class MercEndBoss : public BaseObjScript {
private:
  mercendboss_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);
  void SetSuper(int obj, bool f_super);
  float GetSubModeTime(void);
  void PlayRandomSound(int me);

public:
  MercEndBoss() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// HangLight class
//------------------

class HangLight : public BaseObjScript {
private:
  void DoInit(int me);

public:
  HangLight() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//----------------
// Standard stuff
//----------------

// SaveRestoreState
// Purpose:
//  This function is called when Descent 3 is saving or restoring the game state.  In this function
// you should save/restore any global data that you want preserved through load/save (which includes
// demos).  You must be very careful with this function, corrupting the file (reading or writing too
// much or too little) may be hazardous to the game (possibly making it impossible to restore the
// state).  It would be best to use version information to keep older versions of saved states still
// able to be used.  IT IS VERY IMPORTANT WHEN SAVING THE STATE TO RETURN THE NUMBER OF _BYTES_ WROTE
// TO THE FILE.  When restoring the data, the return value is ignored.  saving_state is 1 when you should
// write data to the file_ptr, 0 when you should read in the data.
int STDCALL SaveRestoreState(void *file_ptr, uint8_t saving_state) { return 0; }

char STDCALL InitializeDLL(tOSIRISModuleInit *func_list) {
  osicommon_Initialize((tOSIRISModuleInit *)func_list);
  if (func_list->game_checksum != CHECKSUM) {
    mprintf(0, "Game-Checksum FAIL!!! (%ul!=%ul)\n", func_list->game_checksum, CHECKSUM);
    mprintf(0, "RECOMPILE YOUR SCRIPTS!!!\n");
    return 0;
  }
  aigame_mod_id = func_list->module_identifier;
  String_table_size = func_list->string_count;
  String_table = func_list->string_table;

  return 1;
}

void STDCALL ShutdownDLL(void) {}

int STDCALL GetGOScriptID(const char *name, uint8_t isdoor) {
  for (int i = 0; i < NUM_IDS; i++) {
    if (!stricmp(name, ScriptInfo[i].name)) {
      return ScriptInfo[i].id;
    }
  }
  return -1;
}

void STDCALLPTR CreateInstance(int id) {
  switch (id) {
  case ID_MERCENDBOSS:
    return new MercEndBoss;
    break;
  case ID_GUN:
    return new Gun;
    break;
  case ID_CASING:
    return new Casing;
    break;
  case ID_HANGLIGHT:
    return new HangLight;
    break;
  case ID_COMBWALLHIT:
    return new CombWallHit;
    break;
  case ID_DROPTARGET:
    return new DropTarget;
    break;
  default:
    mprintf(0, "SCRIPT: Illegal ID (%d)\n", id);
    break;
  };
  return NULL;
}

void STDCALL DestroyInstance(int id, void *ptr) {
  switch (id) {
  case ID_MERCENDBOSS:
    delete ((MercEndBoss *)ptr);
    break;
  case ID_GUN:
    delete ((Gun *)ptr);
    break;
  case ID_CASING:
    delete ((Casing *)ptr);
    break;
  case ID_HANGLIGHT:
    delete ((HangLight *)ptr);
    break;
  case ID_COMBWALLHIT:
    delete ((CombWallHit *)ptr);
    break;
  case ID_DROPTARGET:
    delete ((DropTarget *)ptr);
    break;
  default:
    mprintf(0, "SCRIPT: Illegal ID (%d)\n", id);
    break;
  }
}

int16_t STDCALL CallInstanceEvent(int id, void *ptr, int event, tOSIRISEventInfo *data) {
  return ((BaseObjScript *)ptr)->CallEvent(event, data);
}

//============================================
// Functions
//============================================

float Obj_GetObjDist(int me, int it, bool f_sub_rads) {
  vector me_pos;
  vector it_pos;
  float dist;

  Obj_Value(me, VF_GET, OBJV_V_POS, &me_pos);
  Obj_Value(it, VF_GET, OBJV_V_POS, &it_pos);

  dist = vm_VectorDistance(&me_pos, &it_pos);

  if (f_sub_rads) {
    float size;

    Obj_Value(me, VF_GET, OBJV_F_SIZE, &size);
    dist -= size;
    Obj_Value(it, VF_GET, OBJV_F_SIZE, &size);
    dist -= size;
  }

  return dist;
}

static inline void AIClearNonHPGoals(int handle) {
  int i;

  for (i = 0; i < MAX_GOALS; i++) {
    if (i != 3)
      AI_ClearGoal(handle, i);
  }
}

static inline bool IsGoalFinishedNotify(int index) {
  return (index == AIN_GOAL_COMPLETE || index == AIN_GOAL_INVALID || index == AIN_GOAL_FAIL || index == AIN_GOAL_ERROR);
}

//============================================
// Script Implementation
//============================================
BaseObjScript::BaseObjScript() {}

BaseObjScript::~BaseObjScript() {}

int16_t BaseObjScript::CallEvent(int event, tOSIRISEventInfo *data) { return CONTINUE_CHAIN | CONTINUE_DEFAULT; }

//------------------
// MercEndBoss class
//------------------

#define MATTER_TIME 10.0f
#define MATTER_SUPER_TIME 10.0f
#define ENERGY_TIME 20.0f
#define ENERGY_SUPER_TIME 10.0f

float MercEndBoss::GetSubModeTime(void) {
  if (memory->mode == MERCENDBOSS_MATTER) {
    if (memory->f_sub_super) {
      return MATTER_TIME;
    } else {
      return MATTER_SUPER_TIME;
    }
  } else {
    if (memory->f_sub_super) {
      return ENERGY_SUPER_TIME;
    } else {
      return ENERGY_TIME;
    }
  }
}

void MercEndBoss::SetSuper(int obj, bool f_super) {
  int me = obj;
  memory->f_sub_super = f_super;

  if (memory->mode == MERCENDBOSS_MATTER) {
    if (f_super) {
      Obj_SetCustomAnim(memory->turret_object, 0.0f, 5.0f, 0.5f, AIAF_LOOPING, Sound_FindId("MercFBWinding"), AS_ALERT);

      int flags = AIF_FIRE;
      AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
      AI_Value(memory->turret_object, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      //			flags = DWBF_ENABLED;
      //			Obj_WBValue(me, 0, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
      //			Obj_WBValue(me, 4, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    } else {
      Obj_SetCustomAnim(memory->turret_object, 0.0f, 0.0f, 0.5f, AIAF_NOTIFY, -1, AS_ALERT);

      int flags = AIF_FIRE;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
      AI_Value(memory->turret_object, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

      //			flags = DWBF_ENABLED;
      //			Obj_WBValue(me, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
      //			Obj_WBValue(me, 4, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    }
  } else if (memory->mode == MERCENDBOSS_ENERGY) {
    //		int flags = DWBF_ENABLED;
    //
    //		Obj_WBValue(me, 0, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    //		Obj_WBValue(me, 4, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);

    int flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    if (f_super) {
      aObjGhostSet(0, memory->combine_object);
      aObjGhostSet(0, memory->emitter[0]);
      aObjGhostSet(0, memory->emitter[1]);

      Sound_Play3d(me, Sound_FindId("MercFBBeamCanon"));

      aLightningCreate(memory->emitter[0], memory->combine_object, ENERGY_SUPER_TIME, 3.0f, 1,
                       Scrpt_FindTextureName("endbossbeamweapon2"), 1.0f, 1, 255, 255, 255, true);
      aLightningCreate(memory->emitter[0], memory->combine_object, ENERGY_SUPER_TIME, 2.8f, 1,
                       Scrpt_FindTextureName("endbossbeamweapon2"), 1.95f, 1, 255, 255, 255, true);

      aLightningCreate(memory->emitter[1], memory->combine_object, ENERGY_SUPER_TIME, 3.0f, 1,
                       Scrpt_FindTextureName("endbossbeamweapon2"), 1.0f, 1, 255, 255, 255, true);
      aLightningCreate(memory->emitter[1], memory->combine_object, ENERGY_SUPER_TIME, 2.8f, 1,
                       Scrpt_FindTextureName("endbossbeamweapon2"), 1.96f, 1, 255, 255, 255, true);

      aLightningCreate(memory->turret_object, memory->combine_object, ENERGY_SUPER_TIME, 3.0f, 1,
                       Scrpt_FindTextureName("endbossbeamweapon2"), 1.0f, 1, 255, 255, 255, true);
      aLightningCreate(memory->turret_object, memory->combine_object, ENERGY_SUPER_TIME, 2.8f, 1,
                       Scrpt_FindTextureName("endbossbeamweapon2"), 1.96f, 1, 255, 255, 255, true);

      float max_speed = 8500.0f;
      AI_Value(me, VF_SET, AIV_F_MAX_TURN_RATE, &max_speed);

      int flags = AIF_FIRE;
      AI_Value(memory->turret_object, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    } else {
      aObjGhostSet(1, memory->combine_object);
      aObjGhostSet(1, memory->emitter[0]);
      aObjGhostSet(1, memory->emitter[1]);

      int flags = AIF_FIRE;
      AI_Value(memory->turret_object, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      float max_speed = 10100.0f;
      AI_Value(me, VF_SET, AIV_F_MAX_TURN_RATE, &max_speed);
    }
  }

  memory->sub_mode_time_left = GetSubModeTime();
}

#define DEATH_ROT_ACC 5000.0f

bool MercEndBoss::DoNotify(int me, tOSIRISEventInfo *data) {
  switch (memory->mode) {
  case MERCENDBOSS_WAIT: {
    if (data->evt_ai_notify.notify_type == AIN_MOVIE_START) {
      SetMode(me, MERCENDBOSS_INTRO);
    }
  } break;
  case MERCENDBOSS_INTRO: {
    switch (data->evt_ai_notify.notify_type) {
    case AIN_MOVIE_END:
      SetMode(me, MERCENDBOSS_MATTER);
      break;
    case AIN_SCRIPTED_ORIENT: {
      vector uvec = {0.0f, 1.0f, 0.0f};
      vector fvec = {-1.0f, 0.0f, 0.0f};
      if (AI_TurnTowardsVectors(me, &fvec, &uvec)) {
        memory->f_oriented = true;
      }
    } break;
    case AIN_SCRIPTED_GOAL:
      vector zv = {0.0f, 0.0f, 0.0f};
      AI_Value(me, VF_SET, AIV_V_MOVEMENT_DIR, &zv);
      break;
    }
  } break;
  case MERCENDBOSS_DEATH: {
    // NOTE:  I am also doing the rotational stuff here...  So, no need to make a seperate AIN_SCRIPTED_ORIENT event
    if (data->evt_ai_notify.goal_num == 0 && data->evt_ai_notify.notify_type == AIN_SCRIPTED_GOAL) {
      vector rvel;
      Obj_Value(me, VF_GET, OBJV_V_ROTVELOCITY, &rvel);

      rvel.x -= 0.1f * DEATH_ROT_ACC * Game_GetFrameTime();
      rvel.y -= DEATH_ROT_ACC * Game_GetFrameTime();
      rvel.z += 0.3f * DEATH_ROT_ACC * Game_GetFrameTime();

      Obj_Value(me, VF_SET, OBJV_V_ROTVELOCITY, &rvel);

      vector dir = Zero_vector;
      AI_Value(me, VF_SET, AIV_V_MOVEMENT_DIR, &dir);
    }
  }
  }

  return true;
}

void MercEndBoss::SetMode(int me, char mode) {
  AI_SetType(me, AIT_EVADER1);
  memory->mode_time = 0.0f;

  if (memory->mode == MERCENDBOSS_INTRO) {
    mprintf(0, "Here end of intro\n");
    int flags = DWBF_ENABLED;
    Obj_WBValue(me, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    Obj_WBValue(me, 4, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);

    // The (AIF_DETERMINE_TARGET | AIF_AIM) flags get set here to make absolute sure that no timing issues mess things
    // up
    flags = AIF_FIRE | AIF_DODGE | AIF_DETERMINE_TARGET | AIF_AIM;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    int i;

    for (i = 0; i < 16; i++) {
      PortalBreakGlass(i, 167);
    }
  }

  switch (mode) {
  case MERCENDBOSS_INTRO: {
    mprintf(0, "Here intro begin\n");

    // Make him fire during the cinematics  :)
    int flags = AISR_OK_TO_FIRE_DURING_CINEMATICS;
    AI_Value(me, VF_SET_FLAGS, AIV_I_STATUS_REG, &flags);

    // Make sure he doesn't sleep
    flags = AIF_FORCE_AWARENESS;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    float awareness = AWARE_FULLY;
    AI_Value(me, VF_SET, AIV_F_AWARENESS, &awareness);

    // Destroy all non-boss robots
    aDestroyAllRobotsInit();
    aDestroyAllRobotsSpareHandle(me);
    aDestroyAllRobotsSpareHandle(memory->turret_object);
    aDestroyAllRobotsSpareHandle(memory->emitter[0]);
    aDestroyAllRobotsSpareHandle(memory->emitter[1]);
    aDestroyAllRobotsSpareHandle(memory->combine_object);
    aDestroyAllRobotsEnd();

    // flags = AIF_FIRE;
    // AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
    // AI_Value(memory->turret_object, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    flags = DWBF_ENABLED;
    Obj_WBValue(me, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    Obj_WBValue(me, 4, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
  } break;
  case MERCENDBOSS_MATTER: {
    aShowHUDMessage("GUIDEBOT: We should stay as far away from him as we can.");

    int flags = AIF_DETERMINE_TARGET | AIF_AIM;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    flags = AISR_RANGED_ATTACK;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_STATUS_REG, &flags);
    mprintf(0, "Here matter\n");
  } break;
  case MERCENDBOSS_ENERGY: {
    aShowHUDMessage("GUIDEBOT: Wow!  We better get behind him.");

    Obj_SetCustomAnim(me, 1.0f, 5.0f, 2.0f, 0, Sound_FindId("MercFBServo"), -1);
    Obj_Kill(memory->turret_object, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BREAKS_APART | DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_CONTACT_BREAKS_APART |
                 DF_CONTACT_BLAST_RING | DF_DEBRIS_SMOKES | DF_DEBRIS_FIREBALL | DF_DEBRIS_BLAST_RING,
             0.0f, 0.0f);
    memory->turret_object = CreateAndAttach(me, "FinalbossLITTLETIT", OBJ_BUILDING, 0, 0, true, true);

    aObjSpark(memory->turret_object, 15, 1000000.0f);

    float tl;
    AI_Value(me, VF_GET, AIV_F_LEAD_ACCURACY, &tl);
    tl *= 0.8f;
    AI_Value(me, VF_SET, AIV_F_LEAD_ACCURACY, &tl);

    aTurnOnSpew(memory->turret_object, 0, MED_SMOKE_INDEX, 10.0f, .001f, PF_REVERSE_GRAVITY, 0, 1.0f, .05f, 100000.0f,
                2.0f, 0.0, -1, -1);
  } break;
  case MERCENDBOSS_DEATH_BLOSSUM:
    break;
  case MERCENDBOSS_DEATH: {
    AI_SetType(me, AIT_AIS);

    int flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    AI_Value(memory->turret_object, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    vector vel = {0.0f, 0.0f, 0.0f};
    Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);

    AI_AddGoal(me, AIG_SCRIPTED, 0, 1000.0f, -1, GF_NONFLUSHABLE | GF_ORIENT_SCRIPTED, NULL);

    float drag = 0.0f;
    Obj_Value(me, VF_SET, OBJV_F_ROTDRAG, &drag);

    flags = PF_LEVELING;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
    //			float circle_dist = -1.0f;
    //			AI_Value(me, VF_SET, AIV_F_CIRCLE_DIST, &circle_dist);

    //			Obj_SetCustomAnim(me, 495.0f, 650.0f, 15.0f, 0, Sound_FindId("RbtMercEndBossDeath"), -1);
  } break;
  default:
    break;
  }

  memory->mode = mode;
  SetSuper(me, false);
}

void MercEndBoss::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(mercendboss_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;
  int i;

  memory = (mercendboss_data *)Scrpt_MemAlloc(&ch);
  memory->flags = 0;
  memory->mode = MERCENDBOSS_WAIT;

  memory->turret_object = CreateAndAttach(me, "FinalbossBIGGUN", OBJ_BUILDING, 0, 0, true, true);

  int proom;
  vector ppos;
  matrix porient;
  msafe_struct mstruct;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &proom);
  Obj_Value(me, VF_GET, OBJV_V_POS, &ppos);
  Obj_Value(me, VF_GET, OBJV_M_ORIENT, &porient);

  memory->wallhit_id = Obj_FindID("Finalbosswallhit");

  memory->combine_object = Obj_Create(OBJ_POWERUP, Obj_FindID("FinalbossBEAMCOMBINE"), proom, &ppos, &porient, me);
  mprintf(0, "OBJECT COMB is %d\n", memory->combine_object);
  aObjGhostSet(1, memory->combine_object);

  memory->camera = Obj_Create(OBJ_POWERUP, Obj_FindID("Invisiblepowerup"), proom, &ppos, &porient, me);
  mstruct.objhandle = memory->camera;
  MSafe_CallFunction(MSAFE_OBJECT_NO_RENDER, &mstruct);

  for (i = 0; i < 2; i++) {
    if (i == 0)
      memory->emitter[i] = CreateAndAttach(me, "Finalbossemitter", OBJ_BUILDING, 1 + i, 0, true, true);
    else
      memory->emitter[i] = CreateAndAttach(me, "Finalbossemitterleft", OBJ_BUILDING, 1 + i, 0, true, true);

    aObjGhostSet(1, memory->emitter[i]);
  }

  memory->laser_sound = -1;
  memory->last_frame = 0.0f;
  memory->laser_time_left = 0.0f;

  memory->f_oriented = false;

  memory->f_target_ghost = false;
  memory->time_till_fire = 0.0f;

  int flags = AIF_DETERMINE_TARGET;
  AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

  memory->last_spark_time = Game_GetTime();
  memory->time_to_next_random_sound = 0.0f;

  SetMode(me, MERCENDBOSS_WAIT);
}

void MercEndBoss::PlayRandomSound(int me) {
  memory->time_to_next_random_sound -= Game_GetFrameTime();
  if (memory->time_to_next_random_sound < 0.0f) {
    switch (rand() % 9) {
    case 0:
      Sound_Play3d(me, Sound_FindId("MercFBDanger1"));
      break;
    case 1:
      Sound_Play3d(me, Sound_FindId("MercFBDanger2"));
      break;
    case 2:
      Sound_Play3d(me, Sound_FindId("MercFBDanger3"));
      break;
    case 3:
      Sound_Play3d(me, Sound_FindId("MercFBDanger4"));
      break;
    case 4:
      Sound_Play3d(me, Sound_FindId("MercFBIntruder1"));
      break;
    case 5:
      Sound_Play3d(me, Sound_FindId("MercFBIntruder2"));
      break;
    case 6:
      Sound_Play3d(me, Sound_FindId("MercFBIntruder3"));
      break;
    case 7:
      Sound_Play3d(me, Sound_FindId("MercFBIntruder4"));
      break;
    case 8:
      Sound_Play3d(me, Sound_FindId("MercFBIntruder5"));
      break;
    }

    memory->time_to_next_random_sound = (((float)rand() / (float)RAND_MAX) * 3.0f) + 3.0f;
  }
}

void MercEndBoss::DoFrame(int me) {
  float frame;
  float shields;

  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &frame);
  Obj_Value(memory->turret_object, VF_GET, OBJV_F_SHIELDS, &shields);

  if (memory->mode == MERCENDBOSS_MATTER || memory->mode == MERCENDBOSS_ENERGY) {
    int target;
    int type;
    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target);
    Obj_Value(target, VF_GET, OBJV_I_TYPE, &type);
    int flags = 0;

    if (type == OBJ_PLAYER) {
      Player_Value(target, VF_GET, PLYV_I_FLAGS, &flags);
    }

    if (type == OBJ_PLAYER && (flags & PLAYER_FLAGS_DEAD)) {
      memory->f_target_ghost = true;
      memory->time_till_fire = 3.0f;

      int flags = DWBF_ENABLED;
      Obj_WBValue(me, 0, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
      Obj_WBValue(me, 4, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
      Obj_WBValue(memory->turret_object, 0, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
      Obj_WBValue(memory->turret_object, 1, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    } else if (memory->f_target_ghost) {
      memory->time_till_fire -= Game_GetFrameTime();
      if (memory->time_till_fire <= 0.0f) {
        memory->time_till_fire = 0.0f;
        memory->f_target_ghost = false;

        int flags = DWBF_ENABLED;
        Obj_WBValue(me, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
        Obj_WBValue(me, 4, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
        Obj_WBValue(memory->turret_object, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
        Obj_WBValue(memory->turret_object, 1, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
      }
    }
  } else if (memory->f_target_ghost) {
    memory->time_till_fire = 0.0f;
    memory->f_target_ghost = false;

    int flags = DWBF_ENABLED;
    Obj_WBValue(me, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    Obj_WBValue(me, 4, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    Obj_WBValue(memory->turret_object, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
    Obj_WBValue(memory->turret_object, 1, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);
  }

  if (memory->mode == MERCENDBOSS_WAIT) {
  } else if (memory->mode == MERCENDBOSS_INTRO) {
    if (memory->mode_time > 4.0f && memory->mode_time < 9.0f) {
      if (!memory->f_oriented) {
        int flags = AISR_RANGED_ATTACK;
        AI_Value(me, VF_SET_FLAGS, AIV_I_STATUS_REG, &flags);
      } else {
        int flags = AIF_DETERMINE_TARGET | AIF_AIM;
        AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

        flags = AISR_RANGED_ATTACK;
        AI_Value(me, VF_CLEAR_FLAGS, AIV_I_STATUS_REG, &flags);
      }
    } else if (memory->mode_time < 5.0f && memory->mode_time + Game_GetFrameTime() >= 4.0f) {
      AI_AddGoal(me, AIG_SCRIPTED, 3, 1.0f, MEB_TURN_TOWARDS_CAMERA, GF_ORIENT_SCRIPTED, NULL);
    }

  } else if (memory->mode == MERCENDBOSS_DEATH) {
    int flags = AISR_RANGED_ATTACK;
    AI_Value(me, VF_SET_FLAGS, AIV_I_STATUS_REG, &flags);
    AI_Value(memory->turret_object, VF_SET_FLAGS, AIV_I_STATUS_REG, &flags);

    if (memory->last_spark_time + .1f < Game_GetTime()) {
      memory->last_spark_time = Game_GetTime();

      int room;
      vector pos;

      Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
      Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

      Game_CreateRandomSparks(15, &pos, room);
    }

    if (memory->mode_time < 5.0f && memory->mode_time + Game_GetFrameTime() >= 5.0f) {
      Sound_Play3d(me, Sound_FindId("MercFBError1"));
    }
    if (memory->mode_time < 10.0f && memory->mode_time + Game_GetFrameTime() >= 10.0f) {
      Sound_Play3d(me, Sound_FindId("MercFBError2"));
    }
    if (memory->mode_time < 15.0f && memory->mode_time + Game_GetFrameTime() >= 15.0f) {
      Sound_Play3d(me, Sound_FindId("MercFBError3"));
    }

    if (memory->mode_time < 3.0f && memory->mode_time + Game_GetFrameTime() >= 3.0f) {
      Obj_Burning(me, 1000000.0f, 1.0f);
    }

    if (memory->mode_time > 20.0f) {
      Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
      //			Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
      // DF_BREAKS_APART|DF_BLAST_RING|DF_LOSES_ANTIGRAV|DF_EXPL_LARGE|DF_CONTACT_BREAKS_APART|DF_CONTACT_BLAST_RING|DF_DEBRIS_SMOKES|DF_DEBRIS_FIREBALL|DF_DEBRIS_BLAST_RING,
      // 0.0f, 0.0f);
      Obj_Kill(memory->turret_object, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BREAKS_APART | DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_CONTACT_BREAKS_APART |
                   DF_CONTACT_BLAST_RING | DF_DEBRIS_SMOKES | DF_DEBRIS_FIREBALL | DF_DEBRIS_BLAST_RING,
               0.0f, 0.0f);

      aShowHUDMessage("GUIDEBOT: I love this job.");
    }
  } else if (memory->mode == MERCENDBOSS_MATTER) {
    int flags;
    Obj_Value(memory->turret_object, VF_GET, OBJV_I_FLAGS, &flags);

    if (flags & OF_AI_DEATH) {
      SetMode(me, MERCENDBOSS_ENERGY);
    }

    PlayRandomSound(me);
  } else if (memory->mode == MERCENDBOSS_ENERGY) {
    if (memory->f_sub_super) {
      if (memory->sub_mode_time_left > ENERGY_SUPER_TIME - 1.5f &&
          memory->sub_mode_time_left - Game_GetFrameTime() <= ENERGY_SUPER_TIME - 1.5f) {
        aLightningCreate(memory->combine_object, memory->camera, ENERGY_SUPER_TIME - 1.5f, 6.0f, 1,
                         Scrpt_FindTextureName("endbossbeamweapon2"), 1.0f, 1, 255, 255, 255, true);
        aLightningCreate(memory->combine_object, memory->camera, ENERGY_SUPER_TIME - 1.5f, 6.0f, 1,
                         Scrpt_FindTextureName("endbossbeamweapon2"), 3.1111f, 1, 255, 255, 255, true);
      }

      vector pos;
      matrix orient;
      vector start_pos;
      vector end_pos;
      vector collision_pos;
      vector collision_normal;
      int num_iterations = 0;
      int num_ignore = 0;
      int ignore_list[100];
      int fate;
      ray_info ray;

      int room = 76;
      Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);
      Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

      pos += (orient.fvec * 50.0f) + (orient.uvec * 2.0f);
      Obj_Value(memory->combine_object, VF_SET, OBJV_V_POS, &pos);
      Obj_Value(memory->combine_object, VF_SET, OBJV_I_ROOMNUM, &room);
      start_pos = pos;

      pos += (orient.fvec * 1200.0f);
      Obj_Value(memory->camera, VF_SET, OBJV_V_POS, &pos);
      Obj_Value(memory->camera, VF_SET, OBJV_I_ROOMNUM, &room);
      end_pos = pos;

      if (memory->sub_mode_time_left <= 8.5f) {
        ignore_list[num_ignore++] = memory->camera;
        ignore_list[num_ignore++] = memory->emitter[0];
        ignore_list[num_ignore++] = memory->emitter[1];
        ignore_list[num_ignore++] = me;
        ignore_list[num_ignore++] = memory->turret_object;
        ignore_list[num_ignore++] = memory->combine_object;
        ignore_list[num_ignore++] = -1;

        vector saved_start = start_pos;

        do {
          Obj_Value(me, VF_SET, OBJV_PI_HACK_FVI_IGNORE_LIST, ignore_list);
          fate = FVI_RayCast(OBJECT_HANDLE_NONE, &start_pos, &end_pos, 76, 13.0f,
                             (FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_OBJ_BACKFACE | FQ_BACKFACE |
                              FQ_PLAYERS_AS_SPHERE | FQ_IGNORE_WALLS | FQ_NO_RELINK),
                             &ray);
          Obj_Value(me, VF_SET, OBJV_PI_HACK_FVI_IGNORE_LIST, NULL);

          if (fate != HIT_NONE) {
            start_pos = ray.hit_point + (orient.fvec * 13.0f);
          }

          if (fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) {
            int type;

            Obj_Value(ray.hit_object, VF_GET, OBJV_I_TYPE, &type);

            if (type == OBJ_PLAYER || type == OBJ_ROBOT) {
              msafe_struct mstruct;

              mstruct.objhandle = ray.hit_object;
              mstruct.killer_handle = me;
              mstruct.damage_type = PD_ENERGY_WEAPON;
              mstruct.amount = 10.0f * Game_GetFrameTime();

              MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);

              //						if(ray.hit_wallnorm * orient.fvec <= 0.0f)
              //						{
              vector bf_pos = ray.hit_point + (orient.fvec * 3.0f);
              //							vector bf_pos = ray.hit_point + (orient.fvec *
              //-9.0f);
              Obj_Create(OBJ_POWERUP, memory->wallhit_id, 76, &bf_pos);
              //							//mprintf(0, "HERE X\n");
              //						}
              //						else
              //						{
              //							vector bf_pos = ray.hit_point + (orient.fvec
              //* 9.0f); 							Obj_Create(OBJ_POWERUP,
              // memory->wallhit_id, 76, &bf_pos);
              ///							//mprintf(0, "HERE X\n");
              //						}
            }

            ignore_list[num_ignore++] = ray.hit_object;
          }
          ignore_list[num_ignore] = -1;

          num_iterations++;
        } while (fate != HIT_NONE && num_iterations < 10);

        start_pos = saved_start;
        num_iterations = 0;

        // CHECK THE WALLS
        do {
          fate = FVI_RayCast(OBJECT_HANDLE_NONE, &start_pos, &end_pos, 76, 0.0f, FQ_NO_RELINK, &ray);

          if (fate != HIT_NONE) {
            start_pos = ray.hit_point + (orient.fvec * 5.0f);

            if (ray.hit_wallnorm * orient.fvec <= 0.0f) {
              vector bf_pos = ray.hit_point + (orient.fvec * -9.0f);
              Obj_Create(OBJ_POWERUP, memory->wallhit_id, 76, &bf_pos);
              // mprintf(0, "HERE X\n");
            } else {
              vector bf_pos = ray.hit_point + (orient.fvec * 9.0f);
              Obj_Create(OBJ_POWERUP, memory->wallhit_id, 76, &bf_pos);
              // mprintf(0, "HERE X\n");
            }
          }

          num_iterations++;
        } while (fate != HIT_NONE && num_iterations < 10);

        start_pos = saved_start;
        num_iterations = 0;

        // CHECK THE WALLS
        do {
          fate = FVI_RayCast(OBJECT_HANDLE_NONE, &end_pos, &start_pos, 76, 0.0f, FQ_NO_RELINK, &ray);

          if (fate != HIT_NONE) {
            end_pos = ray.hit_point - (orient.fvec * 5.0f);

            if (ray.hit_wallnorm * orient.fvec <= 0.0f) {
              vector bf_pos = ray.hit_point + (orient.fvec * -9.0f);
              Obj_Create(OBJ_POWERUP, memory->wallhit_id, 76, &bf_pos);
              // mprintf(0, "HERE X\n");
            } else {
              vector bf_pos = ray.hit_point + (orient.fvec * 9.0f);
              Obj_Create(OBJ_POWERUP, memory->wallhit_id, 76, &bf_pos);
              // mprintf(0, "HERE X\n");
            }
          }

          num_iterations++;
        } while (fate != HIT_NONE && num_iterations < 10);

        float last_see_game_time = Game_GetTime();
        AI_Value(me, VF_SET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_game_time);
        AI_Value(memory->turret_object, VF_SET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_game_time);
      }
    } else {
      int flags;
      Obj_Value(memory->turret_object, VF_GET, OBJV_I_FLAGS, &flags);

      if (flags & OF_AI_DEATH) {
        SetMode(me, MERCENDBOSS_DEATH);
      }
    }

    PlayRandomSound(me);
  }

  memory->sub_mode_time_left -= Game_GetFrameTime();
  if (memory->sub_mode_time_left <= 0.0f) {
    SetSuper(me, !memory->f_sub_super);
  }

  memory->mode_time += Game_GetFrameTime();
  memory->last_frame = frame;
}

int16_t MercEndBoss::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    int type;
    Obj_Value(data->evt_collide.it_handle, VF_GET, OBJV_I_TYPE, &type);

    if (type == OBJ_PLAYER || type == OBJ_ROBOT) {
      msafe_struct mstruct;

      mstruct.objhandle = data->evt_collide.it_handle;
      mstruct.killer_handle = data->me_handle;
      mstruct.damage_type = PD_ENERGY_WEAPON;
      mstruct.amount = 50.0f * Game_GetFrameTime();

      MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
    }
  } break;
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY: {
    // shake players
    msafe_struct mstruct;
    mstruct.amount = 90.0f;
    MSafe_CallFunction(MSAFE_OBJECT_VIEWER_SHAKE, &mstruct);

    Obj_Kill(memory->turret_object, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES, 0.0f,
             0.0f);

    int i;
    msafe_struct mo;

    mo.objhandle = memory->camera;
    mo.playsound = 0;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);

    for (i = 0; i < 2; i++) {
      mo.objhandle = memory->emitter[i];
      mo.playsound = 0;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
    }

    mo.objhandle = memory->combine_object;
    mo.playsound = 0;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
  } break;
  case EVT_MEMRESTORE: {
    memory = (mercendboss_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Gun class
//------------------

int16_t Gun::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT: {
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(gun_data);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (gun_data *)Scrpt_MemAlloc(&ch);
    memory->shell_id = Obj_FindID("finalbossshellcasing");
    memory->f_fire = true;
  } break;
  case EVT_COLLIDE: {
    int type;
    Obj_Value(data->evt_collide.it_handle, VF_GET, OBJV_I_TYPE, &type);

    if (type == OBJ_PLAYER || type == OBJ_ROBOT) {
      msafe_struct mstruct;

      mstruct.objhandle = data->evt_collide.it_handle;
      mstruct.killer_handle = data->me_handle;
      mstruct.damage_type = PD_ENERGY_WEAPON;
      mstruct.amount = 50.0f * Game_GetFrameTime();

      MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
    }
  } break;
  case EVT_AI_NOTIFY:
    if (data->evt_ai_notify.notify_type == AIN_FIRED_WEAPON) {
      memory->f_fire = !memory->f_fire;

      if (memory->f_fire)
        ;
      {
        int room;
        vector pos;
        vector dir;
        matrix orient;
        vector velocity;

        Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &room);

        Obj_GetGunPos(data->me_handle, 5, &pos, &dir);
        dir *= -1.0f;
        vm_VectorToMatrix(&orient, &dir, NULL, NULL);

        velocity = dir * qRandomValue(30.0f, 35.0f);

        Obj_Create(OBJ_BUILDING, memory->shell_id, room, &pos, &orient, data->me_handle, &velocity);
      }
    }
    return CONTINUE_CHAIN;
    break;
  case EVT_DESTROY: {
  } break;
  case EVT_MEMRESTORE: {
    memory = (gun_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Casing class
//------------------

int16_t Casing::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(casing_data);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (casing_data *)Scrpt_MemAlloc(&ch);
    memory->time_left = qRandomValue(5.0f, 10.0f);
  } break;
  case EVT_INTERVAL:
    memory->time_left -= Game_GetFrameTime();
    if (memory->time_left < 0.0f) {
      msafe_struct mo;
      mo.objhandle = data->me_handle;
      mo.playsound = 0;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
    }
    break;
  case EVT_AI_NOTIFY:
    return CONTINUE_CHAIN;
    break;
  case EVT_DESTROY: {
  } break;
  case EVT_MEMRESTORE: {
    memory = (casing_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// CombWallHit class
//------------------

int16_t CombWallHit::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(combwallhit_data);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (combwallhit_data *)Scrpt_MemAlloc(&ch);
    memory->time_left = Game_GetFrameTime() * 1.05f;
    // mprintf(0, "HERE\n");
  } break;
  case EVT_INTERVAL:
    memory->time_left -= Game_GetFrameTime();
    if (memory->time_left < 0.0f) {
      msafe_struct mo;
      mo.objhandle = data->me_handle;
      mo.playsound = 0;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
    }
    break;
  case EVT_AI_NOTIFY:
    return CONTINUE_CHAIN;
    break;
  case EVT_DESTROY: {
  } break;
  case EVT_MEMRESTORE: {
    memory = (combwallhit_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// DropTarget class
//------------------

int16_t DropTarget::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(droptarget_data);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (droptarget_data *)Scrpt_MemAlloc(&ch);
    memory->time_left = 5.0f;
    memory->last_set_time = Game_GetTime();
    // mprintf(0, "HERE\n");
  } break;
  case EVT_INTERVAL: {
    float frame;
    Obj_Value(data->me_handle, VF_GET, OBJV_F_ANIM_FRAME, &frame);

    if (frame == 5.0f) {
      memory->time_left -= Game_GetFrameTime();
      if (memory->time_left < 0.0f) {
        memory->time_left = 5.0f;
        Obj_SetCustomAnim(data->me_handle, 5.0f, 10.0f, 0.5f, 0, Sound_FindId("DorPTMCCovertDOpenB"), -1);
      }
    }
  } break;
  case EVT_COLLIDE: {
    float frame;
    char type;

    Obj_Value(data->me_handle, VF_GET, OBJV_F_ANIM_FRAME, &frame);
    AI_Value(data->me_handle, VF_GET, AIV_C_NEXT_ANIMATION_TYPE, &type);

    if ((frame == 0.0f || frame == 10.0f) && type != AS_CUSTOM && memory->last_set_time + 5.0f < Game_GetTime()) {
      memory->last_set_time = Game_GetTime();
      Obj_SetCustomAnim(data->me_handle, 0.0f, 5.0f, 0.5f, 0, Sound_FindId("DorPTMCCovertDOpenB"), -1);
    }
  } break;
  case EVT_DESTROY: {
  } break;
  case EVT_MEMRESTORE: {
    memory = (droptarget_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Hanging Light
//------------------

void HangLight::DoInit(int me) { CreateAndAttach(me, "MERC3_danglinglightbulb", OBJ_CLUTTER, 0, 0, true, true); }

int16_t HangLight::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED:
    DoInit(data->me_handle);
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}
