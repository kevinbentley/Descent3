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
#include <array>
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
#define TXT_GBM_RENAME 0            //"Rename GB Unit"
#define TXT_GBM_REPAIR 1            //"Repair GB"
#define TXT_GBM_EXITSHIP 2          //"Exit ship"
#define TXT_GBM_P0 3                //"P0"
#define TXT_GBM_P1 4                //"P1"
#define TXT_GBM_P2 5                //"P2"
#define TXT_GBM_P3 6                //"P3"
#define TXT_GBM_P4 7                //"P4"
#define TXT_GBM_P5 8                //"P5"
#define TXT_GBM_P6 9                //"P6"
#define TXT_GBM_P7 10               //"P7"
#define TXT_GBM_S0 11               //"S0"
#define TXT_GBM_S1 12               //"S1"
#define TXT_GBM_S2 13               //"S2"
#define TXT_GBM_S3 14               //"S3"
#define TXT_GBM_S4 15               //"S4"
#define TXT_GBM_S5 16               //"S5"
#define TXT_GBM_S6 17               //"S6"
#define TXT_GBM_S7 18               //"S7"
#define TXT_GBM_FINDPOWERUPS 19     //"Find my powerups"
#define TXT_GBM_FINEPOWERUP 20      //"Find powerup"
#define TXT_GBM_FINDENERGY 21       //"Find energy"
#define TXT_GBM_FINDROBOT 22        //"Find robot"
#define TXT_GBM_FINDTHIEF 23        //"Find Thief"
#define TXT_GBM_FINDEXIT 24         //"Find an exit to the mine"
#define TXT_GBM_FINDMINE 25         //"Find a mine"
#define TXT_GBM_FINDCMARK 26        //"Find closest marker"
#define TXT_GBM_M0 27               //"Find Marker 0"
#define TXT_GBM_M1 28               //"Find Marker 1"
#define TXT_GBM_M2 29               //"Find Marker 2"
#define TXT_GBM_M3 30               //"Find Marker 3"
#define TXT_GBM_M4 31               //"Find Marker 4"
#define TXT_GBM_M5 32               //"Find Marker 5"
#define TXT_GBM_M6 33               //"Find Marker 6"
#define TXT_GBM_M7 34               //"Find Marker 7"
#define TXT_GBM_ESCORT 35           //"Escort ship"
#define TXT_GBM_USEEXTIN 36         //"Use fire extinguisher"
#define TXT_GBM_WINGNUT 37          //"Use Go Wingnut Powerup"
#define TXT_GBM_PILOTPOWER 38       //"Use Manual Pilot Powerup"
#define TXT_GBM_GUARDIAN 39         //"Use Guardian Powerup"
#define TXT_GBM_ANTIVIRUS 40        //"Use Anti-Virus Powerup"
#define TXT_GBM_ALLOWCHAT 41        //"Allow GB chatter"
#define TXT_GBM_DISALLOWCHAT 42     //"Disallow GB chatter"
#define TXT_GBM_RETURNTOSHIP 43     //"Return to ship
#define TXT_GB_ENTERINGSHIP TXT(44) //"Entering ship!"
#define TXT_GB_HELPMSG TXT(45)      //"HELP! I am about to die..."
#define TXT_GB_NOTLOCATION TXT(46)  //"This goal is not location based."
#define TXT_GB_NONAV TXT(47)        //"I do not have nav. data on this goal."
#define TXT_GB_ONMYWAY TXT(48)      //"On my way!"
#define TXT_GB_NOTREACH TXT(49)     //"The goal isn't currently reachable."
#define TXT_GB_ENTERSHIP TXT(50)    //"Returning to ship."
#define TXT_GB_ESCORT TXT(51)       //"Escorting ship..."
#define TXT_GB_FINDROBOT TXT(52)    //"Finding a robot."
#define TXT_GB_NOROBOT TXT(53)      //"No robots are reachable."
#define TXT_GB_FINDPOWERUP TXT(54)  //"Finding a powerup."
#define TXT_GB_NOPOWERUP TXT(55)    //"No powerups are reachable."
#define TXT_GB_GOMARKER TXT(56)     //"Going to the '%s' marker."
#define TXT_GB_NOMARKER TXT(57)     //"None of your markers are reachable."
#define TXT_GB_NOMARK TXT(58)       //"The marker is not reachable."
#define TXT_GB_FINDTHIEF TXT(59)    //"Finding the Thief."
#define TXT_GB_FOUNDTHIEF TXT(60)   //"Let's get him!"
#define TXT_GB_NOTHIEF TXT(61)      //"The Thief is not reachable."
#define TXT_GB_FINDPOWERUPS TXT(62) //"Finding your powerups."
#define TXT_GB_NOMESSAGE TXT(63)    //"No spew reachable."
#define TXT_GB_CHATOFF TXT(64)      //"Message Processor off."
#define TXT_GB_CHATON TXT(65)       //"Message Processor On."
#define TXT_GB_FINDENERGY TXT(66)   //"Finding energy."
#define TXT_GB_NOENERGY TXT(67)     //"No energy centers are reachable."
#define TXT_GB_REPAIRED TXT(68)     //"Repaired!"
#define TXT_GB_NOTENSH TXT(69)      //"NOt eNougH shIelDs to do rePAir..."
#define TXT_GB_NEWNAME TXT(70)      //"Thank you for the new name!"
#define TXT_GB_NOWAY TXT(71)        //"No way!"
#define TXT_GB_STRIKE TXT(72)       //"I am on strike!  I won't do task %d"
#define TXT_GB_MENUTITLE TXT(73)    //"GB Command Menu"
#define TXT_GB_FINDMARKMENU TXT(74) //"Find marker: '%s'"
#define TXT_GB_GETTO TXT(75)        //"Get to %s"
#define TXT_GB_SHIELDAMOUNT TXT(76) //" (%d shields)"
#define TXT_GB_ENTERNAME TXT(77)    //"Enter GuideBot name:"
#define TXT_GBHIT1 TXT(78)          //"Stop shooting me!"
#define TXT_GBHIT2 TXT(79)          //"You hit me!"
#define TXT_GBHIT3 TXT(80)          //"Stop it!"
#define TXT_GBHIT4 TXT(81)          //"Im getting attacked!"
#define TXT_GBHIT5 TXT(82)          //"Ouch!"
#define TXT_GBDAMAGED TXT(83)       //"T?o Dama.xgf.ed to exit.  NExfvD rEpair."
#define TXT_GB_OOPS TXT(84)         //"Oops...  Sorry about that!"
#define TXT_GB_SHOOTROBOT TXT(85)   //"Take that!"
#define TXT_GB_GOAL1 TXT(86)        //"I am at the goal, coming back to get you."
#define TXT_GB_GOAL2 TXT(87)        //"Come on!"
#define TXT_GB_GOAL3 TXT(88)        //"Let's go!"
#define TXT_GB_COMINGBACK TXT(89)   //"I am coming back to get you."
#define TXT_THIEFSTEAL TXT(90)      //"The thief stole your %s!"
#define TXT_THIEFSTEAL1 TXT(91)     //"The thief stole a %s!"
#define TXT_THIEFSTEAL2 TXT(92)     //"The thief stole %d of your %ss!"
#define TXT_GB_POWERUP TXT(93)      //"This powerup is for the GuideBot."
#define TXT_STHIEFSTEAL TXT(94)     //"The Super Thief stole a %s!"
#define TXT_STHIEFSTEAL2 TXT(95)    //"The Super Thief stole %d of your %ss!"
#define TXT_GBP_PUTOUTFIRE 96       //"Putting out fires!"
#define TXT_GBP_COWABUNGA 97        //"Cowabunga!"
#define TXT_GBP_BEGENTAL 98         //"Be gental..."
#define TXT_GBP_LETSDOIT 99         //"Let's do it!"
#define TXT_GBP_CONVERTEN 100       //"I will convert the infidal!"
#define TXT_GBP_ACCELERATOR 101     //"Accelerator!!!!!!!"
#define TXT_GBPN_NOFIRE 102         //"No fires to put out!"
#define TXT_GBPN_NOFIGHT 103        //"I don't want to fight!"
#define TXT_GBPN_GOPLAY 104         //"Go play with yourself..."
#define TXT_GBPN_TOODISSY 105       //"Too dissy..."
#define TXT_GBPN_NOENEMY 106        //"No enemies are near!"
#define TXT_GBPN_NOCOFFEE 107       //"I am sick of coffee..."
#define TXT_GBPP_EXTIN 108          //"I got an extinguisher!"
#define TXT_GBPP_WINGNUT 109        //"I got the Wingnut Powerup!
#define TXT_GBPP_MANCON 110         //"I got the Manual Control Powerup!"
#define TXT_GBPP_GUARD 111          //"I got the Guardian Powerup!"
#define TXT_GBPP_ANTIV 112          //"I got a temporary Anti-Virus!"
#define TXT_GBPP_ACCEL 113          //"I got the Accelerator!!!!!!"
#define TXT_WEAP_LASERS 114
#define TXT_WEAP_VAUSS 115
#define TXT_WEAP_MICROWAVE 116
#define TXT_WEAP_PLASMA 117
#define TXT_WEAP_FUSION 118
#define TXT_WEAP_SUPER 119
#define TXT_WEAP_MASS 120
#define TXT_WEAP_NAPALM 121
#define TXT_WEAP_EMD 122
#define TXT_WEAP_OMEGA 123
#define TXT_WEAP_CONCUSSION 124
#define TXT_WEAP_HOMING 125
#define TXT_WEAP_IMPACT 126
#define TXT_WEAP_SMART 127
#define TXT_WEAP_MEGA 128
#define TXT_WEAP_FRAG 129
#define TXT_WEAP_GUIDED 130
#define TXT_WEAP_NAPALMR 131
#define TXT_WEAP_CYCLONE 132
#define TXT_WEAP_BLACKSHARK 133
#define TXT_WEAP_AUTOMAP 134
#define TXT_WEAP_HEADLIGHT 135
#define TXT_WEAP_ETSCONVERTER 136
#define TXT_WEAP_CLOAK 137
#define TXT_WEAP_INVULNERABILITY 138
#define TXT_WEAP_RAPIDFIRE 139
#define TXT_WEAP_QUADLASERS 140
#define TXT_GB_FIFTEEN_SEC_TO_GO TXT(141)
#define TXT_GB_POW_DEPLETED TXT(142)
#define TXT_GB_POW_ACC_ALMOST_DONE TXT(143)
#define TXT_GB_DONT_HAVE_POWERUP TXT(144)
#define TXT_GB_I_FOUND_A_GB_POWERUP TXT(145)

// Returns the new child's handle
static int CreateAndAttach(int me, const char *child_name, uint8_t child_type, char parent_ap, char child_ap,
                           bool f_aligned = true, bool f_set_parent = false);

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
#define NUM_IDS 44 // maximum number of IDs

#define ID_PEST 0            // Pest robot
#define ID_STINGER 1         // Stringer robot
#define ID_DRAGON 2          // Dragon
#define ID_TRACKER 3         // Tracker
#define ID_LANCE 4           // Lance
#define ID_FLAK 5            // Flak
#define ID_SUPERTROOPER 6    // Super Trooper
#define ID_REDSUPERTROOPER 7 // Red Super Trooper
#define ID_JUGG 8            // Juggernaut
#define ID_SIXGUN 9          // Sixgun
#define ID_SICKLE 10         // Sickle
#define ID_GUIDEBOT 11       // GuideBot
#define ID_FIREATDIST 12     // Fire at distance
#define ID_TUBBS 13          // Tubbs
#define ID_THIEF 14          // Thief :)
#define ID_GBPOWERUP 15      // GBPowerup
#define ID_BARNSWALLOW 16    // Barn Shallow
#define ID_SPARKY 17
#define ID_MANTARAY 18
#define ID_SPYHUNTER 19
#define ID_SNIPER 20
#define ID_HUMONCULOUS 21
#define ID_SEEKER 22
#define ID_BETTY 23
#define ID_CHAFF 24
#define ID_CHAFFCHUNK 25
#define ID_PROXMINE 26
#define ID_BETTYBOMB 27 // parent of Bouncing Betty...created to make 3 Bettys
#define ID_JOSHBELL 28
#define ID_SKIFF 29
#define ID_EXPLODEONCONTACT 30
#define ID_EXPLODETIMEOUT 31
#define ID_GUNBOY 32
#define ID_DEATH_TOWER 33
#define ID_DEATH_COLLECTOR 34
#define ID_CHEMICAL_BALL 35
#define ID_HELLION 36
#define ID_SUPERTHIEF 37
#define ID_EVADERMODA 38
#define ID_DESTROYONCONTACT 39
#define ID_HATEPTMC 40
#define ID_SNIPERNORUN 41
#define ID_FLAMERAS 42
#define ID_OLDSCRATCH 43

struct tScriptInfo {
  int id;
  const char *name;
};

static tScriptInfo ScriptInfo[NUM_IDS] = {{ID_PEST, "Pest"},
                                          {ID_STINGER, "Stinger"},
                                          {ID_DRAGON, "Dragontorso"},
                                          {ID_TRACKER, "Tracker"},
                                          {ID_LANCE, "Lance"},
                                          {ID_FLAK, "Flak"},
                                          {ID_SUPERTROOPER, "supertrooper"},
                                          {ID_REDSUPERTROOPER, "red supertrooper"},
                                          {ID_JUGG, "jugg"},
                                          {ID_SIXGUN, "Sixgun"},
                                          {ID_SICKLE, "Sickle"},
                                          {ID_GUIDEBOT, "Guidebot"},
                                          {ID_FIREATDIST, "FireAtDist"},
                                          {ID_TUBBS, "Tubbs"},
                                          {ID_THIEF, "Thief"},
                                          {ID_GBPOWERUP, "GBPowerup"},
                                          {ID_BARNSWALLOW, "BarnSwallow"},
                                          {ID_SPARKY, "Sparky"},
                                          {ID_MANTARAY, "Mantaray"},
                                          {ID_SPYHUNTER, "Spyhunter"},
                                          {ID_SNIPER, "Sniper"},
                                          {ID_HUMONCULOUS, "Humonculous"},
                                          {ID_SEEKER, "Seeker"},
                                          {ID_BETTY, "Betty"},
                                          {ID_CHAFF, "ChaffBomb"},
                                          {ID_CHAFFCHUNK, "ChaffChunk"},
                                          {ID_PROXMINE, "ProxMine"},
                                          {ID_BETTYBOMB, "BettyBomb"},
                                          {ID_JOSHBELL, "JoshBell"},
                                          {ID_SKIFF, "Skiff"},
                                          {ID_EXPLODEONCONTACT, "ExplodeOnContact"},
                                          {ID_EXPLODETIMEOUT, "ExplodeTimeOut"},
                                          {ID_GUNBOY, "Gunboy"},
                                          {ID_DEATH_TOWER, "Ltowerbase"},
                                          {ID_DEATH_COLLECTOR, "Collectorbase"},
                                          {ID_CHEMICAL_BALL, "ChemicalBall"},
                                          {ID_HELLION, "Hellion"},
                                          {ID_SUPERTHIEF, "superthief"},
                                          {ID_EVADERMODA, "EvaderModA"},
                                          {ID_DESTROYONCONTACT, "DestroyOnContact"},
                                          {ID_HATEPTMC, "HatePTMC"},
                                          {ID_SNIPERNORUN, "SniperNoRun"},
                                          {ID_FLAMERAS, "FlameRAS"},
                                          {ID_OLDSCRATCH, "old scratch"}};

static int aigame_mod_id;
// use this macro to create unique timer IDs
#define CREATE_TIMER_ID(id) ((aigame_mod_id << 16) | (id))

static int GetObjectParent(int object);
static int GetObjectType(int object);

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
// Pest class
//------------------
struct pest_data {
  int tail_handle;
  float last_anim_frame;
  int foot_sounds[3];
};

class Pest : public BaseObjScript {
private:
  pest_data *memory;
  void DoInit(int me_handle);

public:
  Pest() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Stinger class
//------------------
#define STINGER_RANGED 0
#define STINGER_MELEE 1

struct stinger_data {
  float next_mode_time;
  float force_melee_shields;
  char mode;
  char f_very_hurt;
};

class Stinger : public BaseObjScript {
private:
  stinger_data *memory;

  void DoInit(int me_handle);
  void DoInterval(int me_handle);

public:
  Stinger() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// SuperThief class
//------------------

#define MAX_STOLEN_WEAPONS 25

struct weapon_item {
  char index;
  int owner;
  char amount;
};

#define SUPERTHIEF_RANGED 0
#define SUPERTHIEF_MELEE 1
#define SUPERTHIEF_DEATH 2
#define SUPERTHIEF_WAIT 3
#define SUPERTHIEF_INTRO 4

struct superthief_data {
  float mode_time;

  float next_mode_time;
  float force_ranged_shields;
  char mode;
  char f_very_hurt;

  float last_frame;
  float time_till_fire_secondary;

  int cur_weapon;

  int num_stolen_weapons;
  weapon_item stolen_weapons[MAX_STOLEN_WEAPONS];

  char weapon[100];
  char sound[100];
  float latency;

  float next_fire_flare_time;
  int flare_fire_index;

  int camera_obj;
  int laser_obj;

  bool laser_on;
};

class SuperThief : public BaseObjScript {
private:
  superthief_data *memory;

  bool DoSteal(int me, int it);
  void SpewEverything(int me);
  bool DoNotify(int me, tOSIRISEVTAINOTIFY *notify);

  void SetMode(int me, char mode);
  void CheckAndFireSecondary(int me);

  void FireFlare(int me);

  void DoInit(int me_handle);
  void DoInterval(int me_handle);

public:
  SuperThief() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Humonculous class
//------------------

struct humonculous_data {
  float next_wall_hit_check_time;
  float mode_time;

  float force_mid_damage_shields;
  float force_wall_hit_shields;
  float force_melee_shields;

  float last_shields;

  uint16_t mode;
  uint16_t next_mode;

  vector land_pos;
  vector land_fvec;
  // Note: land_uvec is always {0.0, 1.0, 0.0}

  float ground_pnt_offset; // This can be computed at start of level

  float max_speed;
  float max_delta_speed;

  float next_mode_time;

  int josh[2];

  int rocks[5];

  int16_t flags;
};

class Humonculous : public BaseObjScript {
private:
  humonculous_data *memory;

  void DetermineDeathPos(int me, vector *dpos, int *droom);
  bool SetMode(int me, uint16_t mode);
  void DoInit(int me);
  void DoInterval(int me);
  bool DoNotify(int me, tOSIRISEventInfo *data);

public:
  Humonculous() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Dragon class
//------------------
#define DRAGON_ARMOR 0
#define DRAGON_SKELETON 1

struct dragon_data {
  int mode;
  int head_object;
  int tail_object;
  int green_turret;
  int t[6];
  int tentacle[6];
};

class Dragon : public BaseObjScript {
private:
  dragon_data *memory;

  void DoInit(int me_handle);

public:
  Dragon() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//----------------
// Tracker
//----------------

struct tracker_data {
  int turret_object;
  int hatch_object;
};

class Tracker : public BaseObjScript {
private:
  tracker_data *memory;

  void DoInit(int me_handle);

public:
  Tracker() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Lance class
//------------------

#define LANCE_PAUSED 0
#define LANCE_MOVING 1

struct lance_data {
  int mode;
};

class Lance : public BaseObjScript {
private:
  void DoInit(int me_handle);
  void DoFrame(int me_handle);
  lance_data *memory;

public:
  Lance() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Flak class
//------------------
struct flak_data {
  int canopy_handle;
  bool f_dead;
  float death_time;
};

class Flak : public BaseObjScript {
private:
  flak_data *memory;
  void DoInit(int me_handle);

public:
  Flak() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Seeker class
//------------------

class Seeker : public BaseObjScript {
private:
  void DoInit(int me);
  void DoCollide(int me);

public:
  Seeker() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// SuperTrooper class
//------------------

struct supertrooper_data {
  int body_handle;
};

class SuperTrooper : public BaseObjScript {
private:
  supertrooper_data *memory;
  void DoInit(int me_handle);

public:
  SuperTrooper() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Sparky class
//------------------

#define MALF_TIME 5.0f
#define MIN_MALF_SPEED 6000.0f

#define DEATH_TIME 5.0f
#define DEATH_ROT_ACC 50000.0f

#define SPARKY_NO_ROT 0
#define SPARKY_ROT_LEFT 1
#define SPARKY_ROT_RIGHT 2

#define SPARKY_NORMAL 0
#define SPARKY_DYING 1

struct sparky_data {
  char mode;
  float mode_time;
  bool f_rotation_death_enabled;
  float drag;

  float last_spark_time;

  int matcen_id;

  matrix orient;

  char spin_dir;
  float spin_time;
};

class Sparky : public BaseObjScript {
private:
  sparky_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  Sparky() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Hellion class
//------------------

#define HELLION_WAIT 0
#define HELLION_INTRO 1
#define HELLION_MATTER 2
#define HELLION_ENERGY 3
#define HELLION_FIRE 4
#define HELLION_SLEEP 5
#define HELLION_BIRTHING 6
#define HELLION_DEATH 7
#define HELLION_BETWEEN_MODE 8

struct hellion_data {
  int flags;
  char mode;
  char next_mode;
  float mode_time;
  int head_object;
  int turret_object;

  float last_frame;

  int laser_sound;

  // Save and restore information
  char weapon[100];
  char sound[100];
  float start;
  float fire;
  float end;
  float time;
  float latency;
  int index;
  char f_mask;

  float alert_start;
  float alert_end;
  float alert_time;
  // End of save and restore information

  float laser_time_left;
  int emitter[2];
  int camera[2];
};

class Hellion : public BaseObjScript {
private:
  hellion_data *memory;
  void DoInit(int me);
  void RemapAlert(int me, float start, float end, float time);
  void RemapWB(int me, float start, float fire, int fire_sound, float end, float time, float latency, int index,
               uint16_t w_id, char f_mask);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  Hellion() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// MantaRay class
//------------------

// Modes
#define MRM_NORMAL 0
#define MRM_ATTACK 1
#define MRM_ATTACK_CIRCLE_BACK 2

// Flags
#define MRF_LEADER 0x01
#define MRF_SQUADIE 0x02
#define MRF_CATCHUP 0x04

// Squad commands
#define MRC_JOIN_ME 11
#define MRC_LEAVE_YOU 12
#define MRC_GET_GOAL_POS 13
#define MRC_GET_GOAL_ROOM 14
#define MRC_GET_GOAL_ORIENT 15

#define MR_MAX_TEAMMATES 4

// Squad offsets
#define MRO_FVEC 10.0f
#define MRO_RVEC 20.0f
#define MRO_UVEC 5.0f

// Squad catchup offset
#define MRO_CATCHUP_DIST 5.0f

struct mantaray_data {
  char mode;
  float mode_time;
  float next_mode_time;

  float base_speed; // We alter this when we are in catchup mode
  float attack_speed;

  int flags;

  uint16_t mantaray_id;

  int leader_handle;
  int num_teammates;
  int teammate[MR_MAX_TEAMMATES];
  float next_update_squad_time;

  vector goal_pos;
  int goal_room;

};

class MantaRay : public BaseObjScript {
private:
  mantaray_data *memory;
  void DoInit(int me);

  void DoSquadieFrame(int me);
  void DoFrame(int me);
  void SetMode(int me, char mode);
  bool DoNotify(int me, tOSIRISEventInfo *data);

  bool SendCommand(int me, int it, char command, void *ptr);
  bool ReceiveCommand(int me, int it, char command, void *ptr);

  void UpdateSquadList(int me);
  void UpdateSquad(int me);

public:
  MantaRay() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Skiff class
//------------------

struct skiff_data {
  char mode;
  float mode_time;
  float next_mode_time;

  float base_speed; // We alter this when we are in catchup mode
  float attack_speed;

  int flags;

  uint16_t skiff_id;

  int leader_handle;
  int num_teammates;
  int teammate[MR_MAX_TEAMMATES];
  float next_update_squad_time;

  vector goal_pos;
  int goal_room;

};

class Skiff : public BaseObjScript {
private:
  skiff_data *memory;
  void DoInit(int me);

  void DoSquadieFrame(int me);
  void DoFrame(int me);
  void SetMode(int me, char mode);
  bool DoNotify(int me, tOSIRISEventInfo *data);

  bool SendCommand(int me, int it, char command, void *ptr);
  bool ReceiveCommand(int me, int it, char command, void *ptr);

  void UpdateSquadList(int me);
  void UpdateSquad(int me);

public:
  Skiff() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// SpyHunter class
//------------------

#define SHM_NORMAL 0
#define SHM_ATTACK 1
#define SHM_BOMB_ATTACK 2

#define SH_MAX_BOMB_TIME 15.0f
#define SH_BOMB_ACCELERATION 8.0f
#define SH_BOMB_ROT_ACC 4000.0f

#define SH_BOMB_TICK_RAMP_TIME 5.0
#define SH_MAX_TICK_INTERVAL 0.5f
#define SH_MIN_TICK_INTERVAL .06f

struct spyhunter_data {
  char mode;
  float next_mode_time;
  float next_summon_time;
  bool f_hit_by_emd;
  float mode_time;
  char last_attack_mode;
  uint16_t emd_id;
  int tick_sound;
  float last_tick_time;

};

class SpyHunter : public BaseObjScript {
private:
  spyhunter_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  void DoSummon(int me);
  bool DoNotify(int me, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  SpyHunter() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Sniper class
//------------------

#define SNIPER_BASE 0
#define SNIPER_SNIPE 1

struct sniper_data {
  char mode;
  float mode_time;
  float time_till_next_mode;

  float base_speed;
  float base_acc;
};

class Sniper : public BaseObjScript {
  sniper_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  Sniper() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// SniperNoRun class
//------------------

#define SNIPER_BASE 0
#define SNIPER_SNIPE 1

struct snipernorun_data {
  char mode;
  float mode_time;
  float time_till_next_mode;

  float base_speed;
  float base_acc;
};

class SniperNoRun : public BaseObjScript {
  snipernorun_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  SniperNoRun() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// EvaderModA class
//------------------

struct evadermoda_data {
  char mode;
  float mode_time;
  float time_till_next_mode;

  float base_speed;
  float base_acc;
};

class EvaderModA : public BaseObjScript {
  evadermoda_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  EvaderModA() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// FlameRAS class
//------------------

struct flameras_data {
  char mode;
  float mode_time;
  float time_till_next_mode;

  float base_speed;
  float base_acc;

  float time_till_fire_toggle;
  bool f_firing_ok;
};

class FlameRAS : public BaseObjScript {
  flameras_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void SetMode(int me, char mode);

public:
  FlameRAS() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Jugg
//-----------------

#define JUGG_NORMAL 0
#define JUGG_DYING 1

#define JUGG_F_BELLY_DEAD 0x01
#define JUGG_F_HEAD_DEAD 0x02
#define JUGG_F_BODY_DEAD 0x04

struct jugg_data {
  float last_frame;
  int foot_sound;

  int head_object;
  int belly_object;
  int turret_object[6];
  int head_turret[2];
  int flame_turret[3];

  float mode_time;
  char mode;
  char flags;
};

class Jugg : public BaseObjScript {
private:
  jugg_data *memory;
  void DoInit(int me_handle);
  void DoFrame(int me_handle);
  void SetMode(int me, char mode);

public:
  Jugg() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Death Tower
//-----------------

struct dtower_data {
  int gun_handle;
  int ball_handle;

  float mode_time;

  bool f_died;
  float last_frame;
};

class DTower : public BaseObjScript {
private:
  dtower_data *memory;
  void DoInit(int me_handle);
  void DoFrame(int me_handle);

public:
  DTower() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Death Collector
//-----------------

struct dcollector_data {
  int ball_handle;
  int rod_handle;
  int target_handle;

  bool f_dead;
};

class DCollector : public BaseObjScript {
private:
  dcollector_data *memory;
  void DoInit(int me_handle);
  void DoFrame(int me_handle);

public:
  DCollector() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Chemical Ball
//-----------------

struct cball_data {
  bool f_picked_up;
  float mode_time;
};

class CBall : public BaseObjScript {
private:
  cball_data *memory;
  void DoInit(int me_handle);
  void DoFrame(int me_handle);

public:
  CBall() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// SixGun
//-----------------

struct sixgun_data {
  int mode;
  float max_speed;
  float circle_dist;
};

class SixGun : public BaseObjScript {
private:
  sixgun_data *memory;
  void DoInit(int me_handle);
  bool DoNotify(int me_handle, tOSIRISEVTAINOTIFY *notify);

public:
  SixGun() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Explode Time Out
//-----------------

struct explodetimeout_data {
  float life_left;
};

class ExplodeTimeOut : public BaseObjScript {
private:
  explodetimeout_data *memory;
  void DoInit(int me_handle);

public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Sickle
//-----------------

#define SICKLE_GOING_HOME 3       // Going home
#define SICKLE_LAND_ON_CEILING 10 // Rotating upsidedown and going to the ceiling
#define SICKLE_LANDED 12          // Stopped on the ceiling
#define SICKLE_MELEE 15           // Melee

struct sickle_data {
  int mode;
  float mode_time;

  vector ceiling_pos;

  float last_fvi_check_time;
  float rot_speed;
  float speed;
  float sleep_speed;
  float sleep_rot_speed;
  bool done_turning;
  bool done_moving;
  vector home_pos;
  int home_room;
  vector home_fvec;

};

class Sickle : public BaseObjScript {
private:
  sickle_data *memory;
  void SetMode(int me, char mode);
  void DoInit(int me_handle);
  void DoFrame(int me_handle);
  bool DoNotify(int me_handle, tOSIRISEVTAINOTIFY *notify);

public:
  Sickle() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Bouncing Betty
//-----------------

struct tBettyBombInfo {
  bool explode;
};

class BettyBomb : public BaseObjScript {
public:
  BettyBomb() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);

private:
  tBettyBombInfo *memory;
};

struct tBettyInfo {
  bool explode;
  float lasttime;
};

class BettyScript : public BaseObjScript {
public:
  BettyScript() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);

protected:
  void DoInit(int me);

private:
  tBettyInfo *memory;
};

//-----------------
// Chaff
//-----------------

struct tChaffInfo {
  bool killme;
};

class ChaffScript : public BaseObjScript {
public:
  ChaffScript() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);

protected:
  void DoInit(int me);
  void DoInterval(int handle);

private:
  tChaffInfo *memory;
};

struct tChaffChunkInfo {
  bool killme;
  float lifeleft;
};

class ChaffChunkScript : public BaseObjScript {
public:
  ChaffChunkScript() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);

protected:
  void DoInit(int me);
  void DoInterval(int handle, float time);
  void DoCollide(tOSIRISEventInfo *data);

private:
  tChaffChunkInfo *memory;
};

//------------------
// ProxMine class
//------------------

class ProxMine : public BaseObjScript {
private:
  void DoInit(int me);
  void DoCollide(int me);

public:
  ProxMine() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//------------------
// Gunboy class
//------------------

class Gunboy : public BaseObjScript {
public:
  Gunboy() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// GBPowerup
//-----------------

struct gbpowerup_data {
  char type; // 0 - 5 matching up with the gb powerups!
  float next_check_time;
  float time_till_next_hud_message;
};

class GBPowerup : public BaseObjScript {
private:
  gbpowerup_data *memory;
  void DoInit(int me);
  void DoFrame(int me);

public:
  GBPowerup() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Josh Bell
//-----------------

struct joshbell_data {
  int me;
  int attach_cage;
  float last_play_time;
  int bell_sound;
};

class JoshBell : public BaseObjScript {
private:
  joshbell_data *memory;
  void DoInit(int me);
  void DoCollide(int me);

public:
  JoshBell() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Explode On Contact
//-----------------

class ExplodeOnContact : public BaseObjScript {
private:
  void DoCollide(int me, int it_handle);

public:
  ExplodeOnContact() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Destroy On Contact
//-----------------

class DestroyOnContact : public BaseObjScript {
private:
  void DoCollide(int me, int it_handle);

public:
  DestroyOnContact() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// GuideBot
//-----------------

// Goal levels:
#define GBL_AMBIENT 0   // Ambient movement and activities
#define GBL_COMMAND 1   // Regular commands (like find powerup)
#define GBL_OVERRIDE 2  // Overriding commands like (return to player) or putting out fires??? --chrishack
#define GBL_MANDITORY 3 // Flying back to ship

#define GB_GUID_RTYPE_SUB_DIR_DONE 0x10010001
#define GB_GUID_RETURNED_TO_PLAYER 0x10010002
#define GB_GUID_AT_GOAL 0x10010003

// Modes
#define GBM_IN_SHIP 0    // In the player ship
#define GBM_AMBIENT 1    // Doing command or idling
#define GBM_DOING_TASK 2 // -- might get rid of this one!!!!!!!!!  I will just add a GBSM_ (doing task)
#define GBM_KIDNAPPED 3
#define GBM_TALKING 4
#define GBM_THIEF 5
#define GBM_ON_FIRE 6
#define GBM_MANUAL 7
#define GBM_RTYPE 8
#define GBM_GO_WINGNUT 9
#define GBM_EXTINGUISH 10
#define GBM_BIRTH 11
#define GBM_ENTER_SHIP 12
#define GBM_RESPAWN_ENTER_SHIP 13

// Sub-modes for normal mode
#define GBSM_NONE 0
#define GBSM_OPEN_DOOR 1
#define GBSM_GET_POWERUP 2
#define GBSM_RETURNING 3
#define GBSM_ANTI_VIRUS 4

#define GBF_VERY_DAMAGED 0x0001
#define GBF_THIEF_REPEL 0x0002
#define GBF_POW_SPEED 0x0004
#define GBF_NO_CHATTER 0x0008
#define GBF_SAW_BOSS 0x0010
#define GBF_WANT_TO_EXTINGUISH 0x0020
#define GBF_EXTINGUISHING 0x0040
#define GBF_IN_CUSTOM_ANIM 0x0080
#define GBF_WANT_TO_USE_ANTI_VIRUS 0x0100
#define GBF_USING_ANTI_VIRUS 0x0200
#define GBF_WANTING_TO_ENTER_PDEAD 0x0400

#define NUM_GB_COMMANDS 44

// Commands
#define GBC_EXIT_SHIP 0
#define GBC_REPAIR_GUIDEBOT 1
#define GBC_RENAME 2
#define GBC_FIND_ACTIVE_GOAL_0 3
#define GBC_FIND_ACTIVE_GOAL_1 4
#define GBC_FIND_ACTIVE_GOAL_2 5
#define GBC_FIND_ACTIVE_GOAL_3 6
#define GBC_FIND_ACTIVE_GOAL_4 7
#define GBC_FIND_ACTIVE_GOAL_5 8
#define GBC_FIND_ACTIVE_GOAL_6 9
#define GBC_FIND_ACTIVE_GOAL_7 10
#define GBC_FIND_ACTIVE_SEC_GOAL_0 11
#define GBC_FIND_ACTIVE_SEC_GOAL_1 12
#define GBC_FIND_ACTIVE_SEC_GOAL_2 13
#define GBC_FIND_ACTIVE_SEC_GOAL_3 14
#define GBC_FIND_ACTIVE_SEC_GOAL_4 15
#define GBC_FIND_ACTIVE_SEC_GOAL_5 16
#define GBC_FIND_ACTIVE_SEC_GOAL_6 17
#define GBC_FIND_ACTIVE_SEC_GOAL_7 18
#define GBC_FIND_SPEW 19
#define GBC_FIND_POWERUP 20
#define GBC_FIND_ENERGY_CENTER 21
#define GBC_FIND_ROBOT 22
#define GBC_FIND_THIEF 23
#define GBC_FIND_OUTSIDE 24
#define GBC_FIND_MINE 25
#define GBC_FIND_CLOSEST_MARKER 26
#define GBC_FIND_MARKER_0 27
#define GBC_FIND_MARKER_1 28
#define GBC_FIND_MARKER_2 29
#define GBC_FIND_MARKER_3 30
#define GBC_FIND_MARKER_4 31
#define GBC_FIND_MARKER_5 32
#define GBC_FIND_MARKER_6 33
#define GBC_FIND_MARKER_7 34
#define GBC_ESCORT_SHIP 35
#define GBC_EXTINGUISH 36
#define GBC_GO_WINGNUT 37
#define GBC_TELEPRESENCE 38
#define GBC_RTYPE 39
#define GBC_ANTI_VIRUS 40
#define GBC_ALLOW_CHATTER 41
#define GBC_NO_CHATTER 42
#define GBC_RETURN_TO_SHIP 43
#define GBC_RENAME_SILENT 44

static int gb_command_text[NUM_GB_COMMANDS] = {
    TXT_GBM_EXITSHIP,    TXT_GBM_REPAIR,     TXT_GBM_RENAME,       TXT_GBM_P0,           TXT_GBM_P1,
    TXT_GBM_P2,          TXT_GBM_P3,         TXT_GBM_P4,           TXT_GBM_P5,           TXT_GBM_P6,
    TXT_GBM_P7,          TXT_GBM_S0,         TXT_GBM_S1,           TXT_GBM_S2,           TXT_GBM_S3,
    TXT_GBM_S4,          TXT_GBM_S5,         TXT_GBM_S6,           TXT_GBM_S7,           TXT_GBM_FINDPOWERUPS,
    TXT_GBM_FINEPOWERUP, TXT_GBM_FINDENERGY, TXT_GBM_FINDROBOT,    TXT_GBM_FINDTHIEF,    TXT_GBM_FINDEXIT,
    TXT_GBM_FINDMINE,    TXT_GBM_FINDCMARK,  TXT_GBM_M0,           TXT_GBM_M1,           TXT_GBM_M2,
    TXT_GBM_M3,          TXT_GBM_M4,         TXT_GBM_M5,           TXT_GBM_M6,           TXT_GBM_M7,
    TXT_GBM_ESCORT,      TXT_GBM_USEEXTIN,   TXT_GBM_WINGNUT,      TXT_GBM_PILOTPOWER,   TXT_GBM_GUARDIAN,
    TXT_GBM_ANTIVIRUS,   TXT_GBM_ALLOWCHAT,  TXT_GBM_DISALLOWCHAT, TXT_GBM_RETURNTOSHIP,
};

// Speed is automatic
#define NUM_GB_USABLE_POWERUPS 5
#define NUM_GB_POWERUPS 6
#define GB_POW_STRING_OFFSET GBC_EXTINGUISH

#define MAX_AV_ROBOTS 100

static int gb_pow_text[NUM_GB_POWERUPS] = {TXT_GBP_PUTOUTFIRE, TXT_GBP_COWABUNGA, TXT_GBP_BEGENTAL,
                                           TXT_GBP_LETSDOIT,   TXT_GBP_CONVERTEN, TXT_GBP_ACCELERATOR};

static int gb_pow_not_text[NUM_GB_POWERUPS] = {TXT_GBPN_NOFIRE,   TXT_GBPN_NOFIGHT, TXT_GBPN_GOPLAY,
                                               TXT_GBPN_TOODISSY, TXT_GBPN_NOENEMY, TXT_GBPN_NOCOFFEE};

static int gb_pow_pickup_text[NUM_GB_POWERUPS] = {TXT_GBPP_EXTIN, TXT_GBPP_WINGNUT, TXT_GBPP_MANCON,
                                                  TXT_GBPP_GUARD, TXT_GBPP_ANTIV,   TXT_GBPP_ACCEL};

#define GB_POW_FIRE 0
#define GB_POW_WINGNUT 1
#define GB_POW_MANUAL 2
#define GB_POW_RTYPE 3
#define GB_POW_ANTIVIRUS 4
#define GB_POW_SPEED 5

#define NUM_GB_SOUNDS 5
#define GBS_VERY_DAMAGED 0
#define GBS_AMBIENT 1

// Extensions to the command interface
#define COM_POWERUP_NOTIFY 4
#define COM_POWERUP_PICKUP 5

struct guidebot_data {
  char name[8];
  char powerups[NUM_GB_USABLE_POWERUPS];

  int sounds[NUM_GB_SOUNDS];

  float mode_time;

  uint16_t mp_slot; // Owner's slot number
  int my_player;          // Owner's object reference

  bool f_parented; // Buddy will not collide with parent until it isn't parented
  bool f_pickup;   // Marked for pickup by the owner

  int mode;     // See above
  int sub_mode; // See above

  char last_rtype_dir;

  int g_powerup;
  int num_pg;
  int num_sg;

  int camera_obj;

  int last_command; // If negative, there is isn't any command
  float last_at_goal_time;
  float next_ambient_time; // Next time the ambient goal changes

  float last_sound_time;

  int flags;

  float last_retreat_time;
  float return_time;

  int me;
  float last_anim;

  int extinguish_spew_id;
  int extinguish_obj_list[5];
  int num_extinguish_objs;
  float extinguish_obj_time;

  float max_acc;
  float max_speed;

  int num_av_robots;
  int av_robot_list[MAX_AV_ROBOTS];
  float av_revert_time[MAX_AV_ROBOTS];

  float speed_time_left;

  float time_till_next_pvis_check;
  float time_till_next_flare;

  int amb_camera_handle;

  float next_powerup_check_time;
  uint16_t powerup_ids[6];
};

class GuideBot : public BaseObjScript {
private:
  guidebot_data *memory;
  void DoMessage(const char *str, bool f_high_priority, const char *sound_name = NULL, bool f_sound_2d = false);
  //	void InitPowerup(int me, char pow_id);
  //	void DoPowerupFrame(int me);
  void DoPowerupCheck(int me);
  void ReInitAmbient(int me);
  bool InitExtinguish(bool f_player_on_fire);
  bool SetMode(int me, char mode);
  bool SetSubMode(int me, char sub_mode, int it = OBJECT_HANDLE_NONE);
  bool DoInit(int me_handle, bool f_reinit);
  void DoCollide(int me, tOSIRISEVTCOLLIDE *evt_collide);
  bool DoUse(int me);
  bool DoNotify(int me_handle, tOSIRISEventInfo *data);
  void DoFrame(int me_handle);
  bool DoExternalCommands(int me, gb_com *command, int it);
  int MakeCommandList(int *gbc_list);
  void AddGetToGoalCommonGoals(int me);

public:
  GuideBot() { memory = NULL; }
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Thief
//-----------------

#define THIEF_AMBIENT 0            // Roaming the mine
#define THIEF_TRACK_PLAYER 1       // Getting to the player
#define THIEF_STEAL 2              // Stealing an item (colliding with player)
#define THIEF_RUN_AWAY 3           // In run-away mode
#define THIEF_SURRENDER 4          // Surrender and then...
#define THIEF_TIME_BOMB 5          // Go into bomb mode
#define THIEF_PLAYER_DEATH_TAUNT 6 // Thief laughing at dead player
#define THIEF_DEATH 7              // Thief dying
#define THIEF_KIDNAP_GB 8          // Kipnapping the GB
#define THIEF_CORNERED 9           // Cornered behavior
#define THIEF_ATTACK 10            // Used by SUPER THIEF

#define THIEF_SUB_NONE 0         // Normal mode of operation
#define THIEF_SUB_SUMMON 1       // Summon other robots
#define THIEF_SUB_CLOAK 2        // Cloak effect
#define THIEF_SUB_THROW_ITEM 3   // Throw an item from your insides(ewww)
#define THIEF_SUB_GET_POWERUP 4  // Pickup a powerup
#define THIEF_SUB_DROP_POWERUP 5 // Quick anim to drop an externally carried item

#define THIEF_F_SURRENDERED 1
#define THIEF_F_GOT_POWERUP 2

// Chrishack make an "occurance" 2D table SUB vs MODE with float for chance per check interval

#define MAX_STOLEN_OBJS 5
#define MAX_STOLEN_INV 10

#define THIEFABLEITEM_PRIMARY 0
#define THIEFABLEITEM_SECONDARY 1
#define THIEFABLEITEM_ACCESSORY 2
struct tThiefItems {
  int index, type;
  float attempt_one, attempt_two, attempt_two_no_one;
  int name_idx;
};

static const std::array<tThiefItems, 27> ThiefableItems = {
    tThiefItems
    {0, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_LASERS},    // Laser
    {1, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_VAUSS},     // Vauss
    {2, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_MICROWAVE}, // Microwave
    {3, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_PLASMA},    // Plasma
    {4, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_FUSION},    // Fusion
    {5, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_SUPER},     // SuperLaser
    {6, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_MASS},      // Mass Driver
    {7, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_NAPALM},    // Napalm
    {8, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_EMD},       // EMD Gun
    {9, THIEFABLEITEM_PRIMARY, 0.70f, 0.50f, 0.70f, TXT_WEAP_OMEGA},     // Omega

    {10, THIEFABLEITEM_SECONDARY, 0.50f, 0.00f, 0.90f, TXT_WEAP_CONCUSSION}, // Concussion
    {11, THIEFABLEITEM_SECONDARY, 0.60f, 0.00f, 0.90f, TXT_WEAP_HOMING},     // Homing
    {12, THIEFABLEITEM_SECONDARY, 0.70f, 0.00f, 0.90f, TXT_WEAP_IMPACT},     // Impact Mortar
    {13, THIEFABLEITEM_SECONDARY, 0.80f, 0.00f, 0.90f, TXT_WEAP_SMART},      // Smart
    {14, THIEFABLEITEM_SECONDARY, 0.90f, 0.00f, 0.90f, TXT_WEAP_MEGA},       // Mega
    {15, THIEFABLEITEM_SECONDARY, 0.50f, 0.00f, 0.90f, TXT_WEAP_FRAG},       // Frag
    {16, THIEFABLEITEM_SECONDARY, 0.60f, 0.00f, 0.90f, TXT_WEAP_GUIDED},     // Guided
    {17, THIEFABLEITEM_SECONDARY, 0.70f, 0.00f, 0.90f, TXT_WEAP_NAPALMR},    // Napalm Rocket
    {18, THIEFABLEITEM_SECONDARY, 0.80f, 0.00f, 0.90f, TXT_WEAP_CYCLONE},    // Cyclone
    {19, THIEFABLEITEM_SECONDARY, 0.90f, 0.00f, 0.90f, TXT_WEAP_BLACKSHARK}, // Black Shark

    {1, THIEFABLEITEM_ACCESSORY, 0.20f, 0.20f, 0.20f, TXT_WEAP_AUTOMAP},         // Automap
    {2, THIEFABLEITEM_ACCESSORY, 0.0f, 0.20f, 0.20f, TXT_WEAP_HEADLIGHT},        // Headlight
    {3, THIEFABLEITEM_ACCESSORY, 0.80f, 0.40f, 0.80f, TXT_WEAP_ETSCONVERTER},    // E2S Converter
    {4, THIEFABLEITEM_ACCESSORY, 1.00f, 0.60f, 1.00f, TXT_WEAP_CLOAK},           // Cloak
    {5, THIEFABLEITEM_ACCESSORY, 1.00f, 0.60f, 1.00f, TXT_WEAP_INVULNERABILITY}, // Invuln
    {6, THIEFABLEITEM_ACCESSORY, 1.00f, 0.60f, 1.00f, TXT_WEAP_RAPIDFIRE},       // RapidFire
    {7, THIEFABLEITEM_ACCESSORY, 1.00f, 0.60f, 1.00f, TXT_WEAP_QUADLASERS},      // Quads
};
const int numThiefableItems = std::size(ThiefableItems);

struct inv_item {
  uint16_t id;
  int owner;
}; // not really inventory items, but items such as quads, automap, headlight, etc (non-weapons)

struct thief_data {
  char mode;
  char sub_mode;
  char last_special_sub_mode;

  char flags;

  char f_cloaked;
  char f_see_player;

  float sub_mode_time;
  float mode_time;
  float next_test_time;
  float last_frame;
  int bomb_handle;
  float last_summon_time;

  float last_shields;

  int num_stolen_objs;
  int stolen_objs[MAX_STOLEN_OBJS];

  int num_stolen_weapons;
  weapon_item stolen_weapons[MAX_STOLEN_WEAPONS];

  int num_stolen_inv;
  inv_item stolen_inv[MAX_STOLEN_INV];

  float fear;
  float agression;

};

class Thief : public BaseObjScript {
private:
  thief_data *memory;
  void DoMessage(const char *str);

  void SetMode(int me, int mode);
  void SetSubMode(int me, int submode);

  void SpewEverything(int me);
  void DoAttack(int me, int it);
  bool DoSteal(int me, int it, int attempt_num, bool f_last_success);
  void DoKidnap(int me, int it);

  void DoInit(int me_handle);
  void DoCollide(int me, tOSIRISEVTCOLLIDE *evt_collide);
  bool DoNotify(int me, tOSIRISEVTAINOTIFY *notify);
  void DoDestroy(int me, tOSIRISEVTDESTROY *evt_destroy);
  void DoFrame(int me);
  void DoSubModeFrame(int me);

public:
  Thief() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// SuperThief
//-----------------

struct tSuperThiefItems {
  int index, autoselect, type;
  float fire_delay;
  int name_idx;
  const char *weapon_name;
  const char *fire_sound;
};

static tSuperThiefItems SuperThiefableItems[] = {
    {0, -1, THIEFABLEITEM_PRIMARY, .25, TXT_WEAP_LASERS, "", ""},                                        // Laser
    {1, 4, THIEFABLEITEM_PRIMARY, .1f, TXT_WEAP_VAUSS, "Vauss", "WpnPyroGLVaussSidefire"},               // Vauss
    {2, 2, THIEFABLEITEM_PRIMARY, .1f, TXT_WEAP_MICROWAVE, "Raygun", "WpnPyroGLMicrowaveSide"},          // Microwave
    {3, 3, THIEFABLEITEM_PRIMARY, .15f, TXT_WEAP_PLASMA, "Plasma", "WpnPyroGLPlasmaFire"},               // Plasma
    {4, 5, THIEFABLEITEM_PRIMARY, .8f, TXT_WEAP_FUSION, "Fusion", "WpnPyroGLFusionFire"},                // Fusion
    {5, 6, THIEFABLEITEM_PRIMARY, .25f, TXT_WEAP_SUPER, "Laser Level 5 -Yellow", "WpnPyroGLSuperLaser"}, // SuperLaser
    {6, 7, THIEFABLEITEM_PRIMARY, 1.0f, TXT_WEAP_MASS, "Mass Driver", "WpnPyroGLMDriverFire"},           // Mass Driver
    {7, -1, THIEFABLEITEM_PRIMARY, 1.0f, TXT_WEAP_NAPALM, "", ""},                                       // Napalm
    {8, 1, THIEFABLEITEM_PRIMARY, .2f, TXT_WEAP_EMD, "EMDblob", "WpnPyroGLEMDfire"},                     // EMD Gun
    {9, -1, THIEFABLEITEM_PRIMARY, 1.0f, TXT_WEAP_OMEGA, "", ""},                                        // Omega

    {10, 1, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_CONCUSSION, "Concussion", "concmissilefire71"}, // Concussion
    {11, 2, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_HOMING, "homing", "HomingfireB1"},              // Homing
    {12, -1, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_IMPACT, "Impact Mortar", "Drop weapon"},       // Impact Mortar
    {13, 3, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_SMART, "Smart", "Smartfire1"},                  // Smart
    {14, 8, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_MEGA, "Mega", "Mega missile fire"},             // Mega
    {15, 6, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_FRAG, "Frag", "WpnFragFire"},                   // Frag
    {16, 4, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_GUIDED, "Guided", "Guided31"},                  // Guided
    {17, 5, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_NAPALMR, "NapalmRocket", "napalmrocket31"},     // Napalm Rocket
    {18, 7, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_CYCLONE, "Cyclone Pack", "CycloneFire1"},       // Cyclone
    {19, -1, THIEFABLEITEM_SECONDARY, .2f, TXT_WEAP_BLACKSHARK, "", ""},                           // Black Shark
};

static int numSuperThiefableItems = sizeof(SuperThiefableItems) / sizeof(tSuperThiefItems);

#define SUPERTHIEF_MELEE_DIST 50.0f

void SuperThief::SetMode(int me, char mode) {
  AI_SetType(me, AIT_AIS);

  switch (mode) {
  case SUPERTHIEF_WAIT: {
  } break;

  case SUPERTHIEF_INTRO: {
  } break;
  case SUPERTHIEF_RANGED:
    AI_SetType(me, AIT_EVADER1);
    break;
  case SUPERTHIEF_MELEE:
    AI_SetType(me, AIT_MELEE1);
    break;
  case SUPERTHIEF_DEATH: {
    int flags = AIF_DODGE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_ORIENT_TARGET | GF_KEEP_AT_COMPLETION, me);

    float temp = 0.0f;
    AI_Value(me, VF_SET, AIV_F_MAX_TURN_RATE, &temp);
    Obj_SetCustomAnim(me, 246.0f, 292.0f, 6.0f, 0, Sound_FindId("RbtThiefDeath"), -1);
  } break;
  }

  memory->time_till_fire_secondary = 1.0f + (float)rand() / (float)RAND_MAX;
  memory->mode = mode;
  memory->mode_time = 0.0f;
}

void SuperThief::SpewEverything(int me) {
  int i;
  int powerup_handle;
  int room;
  vector pos;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

  for (i = 0; i < memory->num_stolen_weapons; i++) {
    uint16_t id;
    int j;

    for (j = 0; j < memory->stolen_weapons[i].amount; j++) {
      float speed = rand() / (float)RAND_MAX * 20.0f + 5.0f;
      vector dir;

      dir.x = rand() / (float)RAND_MAX - 0.5f;
      dir.y = rand() / (float)RAND_MAX - 0.5f;
      dir.z = rand() / (float)RAND_MAX - 0.5f;

      vm_VectorNormalize(&dir);
      dir *= speed;

      Player_Value(memory->stolen_weapons[i].owner, VF_GET, PLYSV_US_WEAPON_POWERUP_ID, &id,
                   memory->stolen_weapons[i].index);
      powerup_handle = Obj_Create(OBJ_POWERUP, id, room, &pos, NULL, OBJECT_HANDLE_NONE, &dir);
    }

    memory->stolen_weapons[i].amount = 0;
  }
}

bool SuperThief::DoNotify(int me, tOSIRISEVTAINOTIFY *notify) {
  if (notify->notify_type == AIN_MELEE_HIT) {
    int target_handle;
    int target_type;

    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target_handle);
    Obj_Value(target_handle, VF_GET, OBJV_I_TYPE, &target_type);

    if (target_type == OBJ_PLAYER) {
      bool f_success;

      memory->time_till_fire_secondary = 1.0f + (float)rand() / (float)RAND_MAX;
      f_success = DoSteal(me, target_handle);
    }
  }

  switch (memory->mode) {
  case SUPERTHIEF_WAIT: {
    if (notify->notify_type == AIN_MOVIE_START) {
      SetMode(me, SUPERTHIEF_INTRO);
    }
  } break;

  case SUPERTHIEF_INTRO: {
    if (notify->notify_type == AIN_MOVIE_END) {
      SetMode(me, SUPERTHIEF_RANGED);
    }
  }
  }

  return true;
}

bool SuperThief::DoSteal(int me, int it) {
  int max_tries = numSuperThiefableItems;
  float gen_perc, perc_chance;
  ;
  int i;
  int count_max, count_num;
  bool *attempted_steals;

  attempted_steals = (bool *)malloc(numSuperThiefableItems * sizeof(bool));
  if (!attempted_steals)
    return false;

  float ftime = Game_GetFrameTime();
  if (ftime == 0)
    ftime = 1.0f;
  srand(Game_GetTime() / ftime);

  for (i = 0; i < numSuperThiefableItems; i++) {
    attempted_steals[i] = false;
  }

  while (max_tries--) {
    i = rand() % numSuperThiefableItems;

    if (attempted_steals[i]) {
      // we already tried this one, try another
      max_tries++;
      continue;
    }

    attempted_steals[i] = true;

    {
      count_max = MAX_STOLEN_WEAPONS;
      count_num = memory->num_stolen_weapons;

      if (count_num >= count_max) {
        mprintf(0, "SUPER THIEF: no mo' room\n");
        continue; // we have no more room
      }

      // mprintf(0,"THIEF: Checking %s\n",TXT(SuperThiefableItems[i].name_idx));

      bool can_take = false;
      int amount = 0;
      char message[256];

      switch (SuperThiefableItems[i].type) {
      case THIEFABLEITEM_PRIMARY:
        // check to see if we can steal the primary
        Player_Value(it, VF_GET, PLYSV_I_WEAPON, &amount, SuperThiefableItems[i].index);
        if (SuperThiefableItems[i].index != 0 && amount) {
          can_take = true;
          snprintf(message, sizeof(message), TXT_THIEFSTEAL, TXT(SuperThiefableItems[i].name_idx));
        }
        break;

      case THIEFABLEITEM_SECONDARY:
        // check to see if we can steal the secondary
        {
          Player_Value(it, VF_GET, PLYSV_I_WEAPON, &amount, SuperThiefableItems[i].index);

          if (amount) {
            int max;

            if (SuperThiefableItems[i].index > 14) {
              // 2nd selection group (black shark, etc)
              max = (19 - SuperThiefableItems[i].index) / 2.5f + 1;
            } else {
              // 1st selection group (mega, etc)
              max = (14 - SuperThiefableItems[i].index) / 2.5f + 1;
            }

            int new_amount = (rand() / (float)(RAND_MAX + 1)) * max + 1;

            if (new_amount < amount)
              amount = new_amount;

            can_take = true;

            if (amount == 1) {
              snprintf(message, sizeof(message), TXT_STHIEFSTEAL, TXT(SuperThiefableItems[i].name_idx));
            } else {
              snprintf(message, sizeof(message), TXT_STHIEFSTEAL2, amount, TXT(SuperThiefableItems[i].name_idx));
            }
          }
        }
        break;
      }

      if (!can_take)
        continue;

      mprintf(0, "Super Thief: Nice %s!\n", TXT(SuperThiefableItems[i].name_idx));

      Player_AddHudMessage(it, message);
      if (rand() % 50) {
        Sound_Play3d(me, Sound_FindId("RbtThiefHehHehHeh"));
      } else {
        Sound_Play3d(me, Sound_FindId("RbtThiefLaugh"));
      }

      memory->stolen_weapons[memory->num_stolen_weapons].index = SuperThiefableItems[i].index;
      memory->stolen_weapons[memory->num_stolen_weapons].owner = it;
      memory->stolen_weapons[memory->num_stolen_weapons].amount = amount;
      memory->num_stolen_weapons++;

      if (SuperThiefableItems[i].type == THIEFABLEITEM_PRIMARY) {
        amount = 0;
        if (SuperThiefableItems[i].autoselect > memory->cur_weapon) {
          uint16_t wpn = Wpn_FindID(SuperThiefableItems[i].weapon_name);
          int snd = Sound_FindId(SuperThiefableItems[i].fire_sound);

          Obj_WBValue(me, 1, VF_SET, WBSV_I_FIRE_SOUND, &snd, 0);
          Obj_WBValue(me, 1, VF_SET, WBSV_F_LATENCY, &SuperThiefableItems[i].fire_delay, 0);
          Obj_WBValue(me, 1, VF_SET, WBSV_US_GUNPT_WEAPON_ID, &wpn, 0);

          strcpy(memory->weapon, SuperThiefableItems[i].weapon_name);
          strcpy(memory->sound, SuperThiefableItems[i].weapon_name);
          memory->latency = SuperThiefableItems[i].fire_delay;
        }
      } else {
        amount *= -1;
      }

      Player_Value(it, VF_SET, PLYSV_I_WEAPON, &amount, SuperThiefableItems[i].index);

      free(attempted_steals);
      return true;
    }
  }

  mprintf(0, "Super Thief: Not taking anything\n");
  free(attempted_steals);
  return false; // we didn't take anything this try
}

void SuperThief::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(superthief_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (superthief_data *)Scrpt_MemAlloc(&ch);

  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &m);

  memory->next_mode_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * 3.0f + 3.0f;
  memory->force_ranged_shields = m.shields / 15.0f;
  memory->mode = SUPERTHIEF_WAIT;
  memory->f_very_hurt = 0;

  memory->num_stolen_weapons = 0;
  memory->cur_weapon = -1;

  memory->mode_time = 0.0f;
  memory->last_frame = 0.0f;
  memory->time_till_fire_secondary = 1.0f + (float)rand() / (float)RAND_MAX;

  memory->laser_obj = CreateAndAttach(me, "STEmitter", OBJ_ROBOT, 2, 0, true, true);

  uint16_t wpn = Wpn_FindID("Laser Level 1 - Red");
  int snd = Sound_FindId("Laser level 1");

  strcpy(memory->weapon, "Laser Level 1 - Red");
  strcpy(memory->sound, "Laser level 1");

  memory->latency = 0.25f;

  memory->laser_on = false;

  memory->next_fire_flare_time = 0.0f;
  memory->flare_fire_index = 0;

  Obj_WBValue(me, 1, VF_SET, WBSV_I_FIRE_SOUND, &snd, 0);
  Obj_WBValue(me, 1, VF_SET, WBSV_F_LATENCY, &memory->latency, 0);
  Obj_WBValue(me, 1, VF_SET, WBSV_US_GUNPT_WEAPON_ID, &wpn, 0);
}

void SuperThief::FireFlare(int me) {
  msafe_struct mstruct;

  mstruct.objhandle = me;
  mstruct.index = Wpn_FindID("Yellow flare");
  if (mstruct.index == -1)
    return;
  mstruct.gunpoint = 1;

  Sound_Play3d(me, Sound_FindId("Flare"));

  MSafe_CallFunction(MSAFE_OBJECT_FIRE_WEAPON, &mstruct);
}

void SuperThief::CheckAndFireSecondary(int me) {
  int i;
  const char *wname;
  const char *sname;
  int best_select = -1;
  int best_index;

  for (i = 0; i < memory->num_stolen_weapons; i++) {
    if (memory->stolen_weapons[i].amount > 0 &&
        SuperThiefableItems[memory->stolen_weapons[i].index].type == THIEFABLEITEM_SECONDARY) {
      if (best_select < SuperThiefableItems[memory->stolen_weapons[i].index].autoselect) {
        wname = SuperThiefableItems[memory->stolen_weapons[i].index].weapon_name;
        sname = SuperThiefableItems[memory->stolen_weapons[i].index].fire_sound;
        best_select = SuperThiefableItems[memory->stolen_weapons[i].index].autoselect;
        best_index = i;
      }
    }
  }

  if (best_select >= 0) {
    memory->stolen_weapons[best_index].amount--;

    msafe_struct mstruct;

    mstruct.objhandle = me;
    mstruct.index = Wpn_FindID(wname);
    if (mstruct.index == -1)
      return;
    mstruct.gunpoint = 1;

    Sound_Play3d(me, Sound_FindId(sname));

    MSafe_CallFunction(MSAFE_OBJECT_FIRE_WEAPON, &mstruct);
  }
}

void SuperThief::DoInterval(int me) {
  bool f_force_ranged = false;
  int target_handle;
  float anim_frame;
  float shields;
  int flags;
  msafe_struct m;
  int room;
  vector pos;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &anim_frame);
  Obj_Value(me, VF_GET, OBJV_F_SHIELDS, &shields);
  Obj_Value(me, VF_GET, OBJV_I_FLAGS, &flags);

  if (memory->laser_on) {
    ray_info ray;

    matrix orient;
    Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

    // Determine real start pos - room
    vector end_pos = pos;
    end_pos += orient.fvec * 2000.0f;

    int fvi_flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS;
    int fate = FVI_RayCast(me, &pos, &end_pos, room, 0.0f, fvi_flags, &ray);

    Obj_Value(memory->camera_obj, VF_SET, OBJV_I_ROOMNUM, &ray.hit_room);
    Obj_Value(memory->camera_obj, VF_SET, OBJV_V_POS, &ray.hit_point);
  }

  memory->f_very_hurt = f_force_ranged = (shields < memory->force_ranged_shields) != 0;

  if ((memory->mode != SUPERTHIEF_DEATH) && (flags & OF_AI_DEATH) && anim_frame >= 0.0f && anim_frame <= 6.0f) {
    mprintf(0, "ST: Dying\n");
    SetMode(me, SUPERTHIEF_DEATH);
  }

  if (memory->mode == SUPERTHIEF_DEATH) {
    // Do dynamic death
    if ((memory->mode_time < 4.0f && memory->mode_time + Game_GetFrameTime() >= 4.0f) ||
        (memory->mode_time < 6.0f && memory->mode_time + Game_GetFrameTime() >= 6.0f)) {
      int weapon_id;

      weapon_id = Wpn_FindID("TubbsHitBlast");
      Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);
    }

    if (memory->mode_time < 3.0f && memory->mode_time + Game_GetFrameTime() >= 3.0f) {
      Obj_Burning(me, 1000000.0f, 1.0f);
    }

    if (memory->mode_time > 6.2f) {
      mprintf(0, "ST: Died\n");
      Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
    }
  } else if (memory->mode == SUPERTHIEF_INTRO) {
    if (memory->mode_time < 6.0f && memory->mode_time + Game_GetFrameTime() >= 6.0f) {
      int flags = AIF_FORCE_AWARENESS | AIF_DETERMINE_TARGET;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      float awareness = AWARE_FULLY;
      AI_Value(me, VF_SET, AIV_F_AWARENESS, &awareness);
    }

    if (memory->last_frame < 234.0f && anim_frame >= 234.0f) {
      msafe_struct mstruct;
      int type;

      memory->laser_on = true;
      memory->camera_obj = Obj_Create(OBJ_POWERUP, Obj_FindID("Invisiblepowerup"), room, &pos, NULL, me);
      mstruct.objhandle = memory->camera_obj;
      MSafe_CallFunction(MSAFE_OBJECT_NO_RENDER, &mstruct);

      Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &mstruct.roomnum);
      Obj_Value(me, VF_GET, OBJV_V_POS, &mstruct.pos);
      Obj_Value(memory->camera_obj, VF_GET, OBJV_V_POS, &mstruct.pos2);

      mstruct.objhandle = memory->laser_obj;
      mstruct.ithandle = memory->camera_obj;
      mstruct.lifetime = 10000000.0f;
      mstruct.size = 1.0f;

      mstruct.interval = 1.0f;
      mstruct.count = 2;
      mstruct.index = 1;
      mstruct.texnum = Scrpt_FindTextureName("Stlaser");
      mstruct.color = ((128 >> 3) << 10) | ((128 >> 3) << 5) | (128 >> 3);

      mstruct.state = 0;
      mstruct.flags = 0;

      MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING_BOLT, &mstruct);
    }
  } else if (memory->mode == SUPERTHIEF_WAIT) {
  } else {
    // Put the mod stuff here!

    if (memory->mode == SUPERTHIEF_RANGED) {
      memory->time_till_fire_secondary -= Game_GetFrameTime();
      float last_see_time;
      float last_hear_time;
      AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_time);
      AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &last_hear_time);

      if (memory->next_fire_flare_time < Game_GetTime() && last_see_time + 7.0f >= Game_GetTime() &&
          last_hear_time + 7.0f >= Game_GetTime()) {
        FireFlare(me);
        memory->flare_fire_index++;

        if (memory->flare_fire_index >= 3) {
          memory->flare_fire_index = 0;
          memory->next_fire_flare_time = Game_GetTime() + (rand() / (float)RAND_MAX) * 10.0f + 5.0f;
        } else {
          memory->next_fire_flare_time = Game_GetTime() + .75f;
        }
      }

      if (memory->time_till_fire_secondary < 0.0f) {
        memory->time_till_fire_secondary = 1.0f + (float)rand() / (float)RAND_MAX;
        CheckAndFireSecondary(me);
      }
    }

    if ((!f_force_ranged) && (memory->next_mode_time < Game_GetTime())) {
      if (memory->mode == SUPERTHIEF_MELEE) {
        AI_SetType(me, AIT_EVADER1);
        memory->mode = SUPERTHIEF_RANGED;
      } else if ((rand() % 150) > 20) {
        AI_SetType(me, AIT_MELEE1);
        memory->mode = SUPERTHIEF_MELEE;
      }

      if (memory->mode == SUPERTHIEF_RANGED)
        memory->next_mode_time = Game_GetTime() + 5.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;
      else
        memory->next_mode_time = Game_GetTime() + 3.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;
    } else if ((f_force_ranged) && (memory->mode != SUPERTHIEF_RANGED)) {
      //		PlaySoundObj3d("RbtStingeattack1", me)
      AI_SetType(me, AIT_EVADER1);
      memory->mode = SUPERTHIEF_RANGED;
    }
  }

  memory->last_frame = anim_frame;
  memory->mode_time += Game_GetFrameTime();
}

int16_t SuperThief::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoInterval(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, &data->evt_ai_notify) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY: {
    SpewEverything(data->me_handle);
    msafe_struct mo;
    mo.objhandle = memory->laser_obj;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
    mo.objhandle = memory->camera_obj;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
  } break;
  case EVT_MEMRESTORE: {
    memory = (superthief_data *)data->evt_memrestore.memory_ptr;

    uint16_t wpn = Wpn_FindID(memory->weapon);
    int snd = Sound_FindId(memory->sound);

    Obj_WBValue(data->me_handle, 1, VF_SET, WBSV_I_FIRE_SOUND, &snd, 0);
    Obj_WBValue(data->me_handle, 1, VF_SET, WBSV_F_LATENCY, &memory->latency, 0);
    Obj_WBValue(data->me_handle, 1, VF_SET, WBSV_US_GUNPT_WEAPON_ID, &wpn, 0);
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//-----------------
// FireAtDist
//-----------------

struct fireatdist_data {
  int me;
  float fire_dist;
  float last_test_time;
  bool last_f_fire;
};

class FireAtDist : public BaseObjScript {
private:
  fireatdist_data *memory;
  void DoInit(int me_handle);
  void DoFrame(int me_handle);

public:
  FireAtDist() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// HatePTMC
//-----------------

struct hateptmc_data {
  int me;
  float time_till_pulse;
};

class HatePTMC : public BaseObjScript {
private:
  hateptmc_data *memory;
  void DoInit(int me_handle);
  void DoFrame(int me_handle);

public:
  HatePTMC() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Tubbs
//-----------------

struct tubbs_data {
  float base_speed;
  float base_acc;
  float max_speed;
  float max_acc;
  float full_anger_time;
};

class Tubbs : public BaseObjScript {
private:
  tubbs_data *memory;
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me, tOSIRISEVTAINOTIFY *notify);

public:
  Tubbs() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// Old Scratch
//-----------------

struct oldscratch_data {
  float base_speed;
  float base_acc;
  float max_speed;
  float max_acc;
  float full_anger_time;
};

class OldScratch : public BaseObjScript {
private:
  oldscratch_data *memory;
  bool DoSteal(int me, int it);
  void DoInit(int me);
  void DoFrame(int me);
  bool DoNotify(int me, tOSIRISEVTAINOTIFY *notify);

public:
  OldScratch() {}
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

//-----------------
// BarnSwallow
//-----------------

#define BSM_NEST 0
#define BSM_FOLLOW 1
#define BSM_GET_POWERUP 2
#define BSM_ATTACK 3
#define BSM_ATTACK_CIRCLE_BACK 4
#define BSM_FLEE 5
#define BSM_RETURN_TO_NEST 6

#define BSCOMM_FOLLOW_ME 0 // send a percent chance so we can have a line sometimes
#define BSCOMM_FOLLOW_CANCEL_FROM_FOLLOWER 1
#define BSCOMM_FOLLOW_CANCEL_FROM_LEADER 2
#define BSCOMM_ATTACK_MY_TARGET 3
#define BSCOMM_ARE_YOU_IN_MODE 4
#define BSCOMM_ARE_YOU_AFTER_POWERUP 5

#define BSF_HAVE_POWERUP 1
#define BSF_ACCEPT_ORDER 2 // clear it before the call...

#define BS_MAX_FRIENDS 20

struct barnswallow_data {
  int home_room;
  vector nest_center;
  float nest_rad;

  int follower;

  char num_friends;
  int friends[BS_MAX_FRIENDS];
  float next_friend_update_time;

  char mode;
  char last_non_attack_mode;

  float mode_time;
  float next_mode_time;
  float next_attack_time;
  float next_powerup_time;
  float max_time_on_road;
  int powerup_id;

  int flags;
};

class BarnSwallow : public BaseObjScript {
private:
  barnswallow_data *memory;
  void DoInit(int me);
  bool SendCommand(int me, int it, char command, int value = 0);
  bool ReceiveCommand(int me, int it, gb_com *command);
  void ComputeNextNestPnt(int me, vector *pos);
  bool DoNotify(int me, tOSIRISEventInfo *data);
  void ComputeNest(int me);
  void UpdateFriendList(int me);
  void DoFrame(int me);
  bool SetMode(int me, char mode, int it = OBJECT_HANDLE_NONE);

public:
  BarnSwallow() {}
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
  case ID_PEST:
    return new Pest;
    break;
  case ID_STINGER:
    return new Stinger;
    break;
  case ID_DRAGON:
    return new Dragon;
    break;
  case ID_TRACKER:
    return new Tracker;
    break;
  case ID_LANCE:
    return new Lance;
    break;
  case ID_FLAK:
    return new Flak;
    break;
  case ID_SUPERTROOPER:
  case ID_REDSUPERTROOPER:
    return new SuperTrooper;
    break;
  case ID_JUGG:
    return new Jugg;
    break;
  case ID_SIXGUN:
    return new SixGun;
    break;
  case ID_SICKLE:
    return new Sickle;
    break;
  case ID_GUIDEBOT:
    return new GuideBot;
    break;
  case ID_FIREATDIST:
    return new FireAtDist;
    break;
  case ID_TUBBS:
    return new Tubbs;
    break;
  case ID_THIEF:
    return new Thief;
    break;
  case ID_GBPOWERUP:
    return new GBPowerup;
    break;
  case ID_BARNSWALLOW:
    return new BarnSwallow;
    break;
  case ID_SPARKY:
    return new Sparky;
    break;
  case ID_MANTARAY:
    return new MantaRay;
    break;
  case ID_SPYHUNTER:
    return new SpyHunter;
    break;
  case ID_SNIPER:
    return new Sniper;
    break;
  case ID_HUMONCULOUS:
    return new Humonculous;
    break;
  case ID_SEEKER:
    return new Seeker;
    break;
  case ID_BETTY:
    return new BettyScript;
    break;
  case ID_CHAFF:
    return new ChaffScript;
    break;
  case ID_CHAFFCHUNK:
    return new ChaffChunkScript;
    break;
  case ID_PROXMINE:
    return new ProxMine;
    break;
  case ID_BETTYBOMB:
    return new BettyBomb;
    break;
  case ID_JOSHBELL:
    return new JoshBell;
    break;
  case ID_SKIFF:
    return new Skiff;
    break;
  case ID_EXPLODEONCONTACT:
    return new ExplodeOnContact;
    break;
  case ID_EXPLODETIMEOUT:
    return new ExplodeTimeOut;
    break;
  case ID_GUNBOY:
    return new Gunboy;
    break;
  case ID_DEATH_TOWER:
    return new DTower;
    break;
  case ID_DEATH_COLLECTOR:
    return new DCollector;
    break;
  case ID_CHEMICAL_BALL:
    return new CBall;
    break;
  case ID_HELLION:
    return new Hellion;
    break;
  case ID_SUPERTHIEF:
    return new SuperThief;
    break;
  case ID_EVADERMODA:
    return new EvaderModA;
    break;
  case ID_DESTROYONCONTACT:
    return new DestroyOnContact;
    break;
  case ID_HATEPTMC:
    return new HatePTMC;
    break;
  case ID_SNIPERNORUN:
    return new SniperNoRun;
    break;
  case ID_FLAMERAS:
    return new FlameRAS;
    break;
  case ID_OLDSCRATCH:
    return new OldScratch;
    break;
  default:
    mprintf(0, "SCRIPT: Illegal ID (%d)\n", id);
    break;
  };
  return NULL;
}

void STDCALL DestroyInstance(int id, void *ptr) {
  switch (id) {
  case ID_PEST:
    delete ((Pest *)ptr);
    break;
  case ID_STINGER:
    delete ((Stinger *)ptr);
    break;
  case ID_DRAGON:
    delete ((Dragon *)ptr);
    break;
  case ID_TRACKER:
    delete ((Tracker *)ptr);
    break;
  case ID_LANCE:
    delete ((Lance *)ptr);
    break;
  case ID_FLAK:
    delete ((Flak *)ptr);
    break;
  case ID_SUPERTROOPER:
  case ID_REDSUPERTROOPER:
    delete ((SuperTrooper *)ptr);
    break;
  case ID_JUGG:
    delete ((Jugg *)ptr);
    break;
  case ID_SIXGUN:
    delete ((SixGun *)ptr);
    break;
  case ID_SICKLE:
    delete ((Sickle *)ptr);
    break;
  case ID_GUIDEBOT:
    delete ((GuideBot *)ptr);
    break;
  case ID_FIREATDIST:
    delete ((FireAtDist *)ptr);
    break;
  case ID_TUBBS:
    delete ((Tubbs *)ptr);
    break;
  case ID_THIEF:
    delete ((Thief *)ptr);
    break;
  case ID_GBPOWERUP:
    delete ((GBPowerup *)ptr);
    break;
  case ID_BARNSWALLOW:
    delete ((BarnSwallow *)ptr);
    break;
  case ID_SPARKY:
    delete ((Sparky *)ptr);
    break;
  case ID_MANTARAY:
    delete ((MantaRay *)ptr);
    break;
  case ID_SPYHUNTER:
    delete ((SpyHunter *)ptr);
    break;
  case ID_SNIPER:
    delete ((Sniper *)ptr);
    break;
  case ID_HUMONCULOUS:
    delete ((Humonculous *)ptr);
    break;
  case ID_SEEKER:
    delete ((Seeker *)ptr);
    break;
  case ID_BETTY:
    delete ((BettyScript *)ptr);
    break;
  case ID_CHAFF:
    delete ((ChaffScript *)ptr);
    break;
  case ID_CHAFFCHUNK:
    delete ((ChaffChunkScript *)ptr);
    break;
  case ID_PROXMINE:
    delete ((ProxMine *)ptr);
    break;
  case ID_BETTYBOMB:
    delete ((BettyBomb *)ptr);
    break;
  case ID_JOSHBELL:
    delete ((JoshBell *)ptr);
    break;
  case ID_SKIFF:
    delete ((Skiff *)ptr);
    break;
  case ID_EXPLODEONCONTACT:
    delete ((ExplodeOnContact *)ptr);
    break;
  case ID_EXPLODETIMEOUT:
    delete ((ExplodeTimeOut *)ptr);
    break;
  case ID_GUNBOY:
    delete ((Gunboy *)ptr);
    break;
  case ID_DEATH_TOWER:
    delete ((DTower *)ptr);
    break;
  case ID_DEATH_COLLECTOR:
    delete ((DCollector *)ptr);
    break;
  case ID_CHEMICAL_BALL:
    delete ((CBall *)ptr);
    break;
  case ID_HELLION:
    delete ((Hellion *)ptr);
    break;
  case ID_SUPERTHIEF:
    delete ((SuperThief *)ptr);
    break;
  case ID_EVADERMODA:
    delete ((EvaderModA *)ptr);
    break;
  case ID_DESTROYONCONTACT:
    delete ((DestroyOnContact *)ptr);
    break;
  case ID_HATEPTMC:
    delete ((HatePTMC *)ptr);
    break;
  case ID_SNIPERNORUN:
    delete ((SniperNoRun *)ptr);
    break;
  case ID_FLAMERAS:
    delete ((FlameRAS *)ptr);
    break;
  case ID_OLDSCRATCH:
    delete ((OldScratch *)ptr);
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

static float Obj_GetObjDist(int me, int it, bool f_sub_rads) {
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

//-----------------
// Josh Bell
//-----------------

void JoshBell::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(joshbell_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (joshbell_data *)Scrpt_MemAlloc(&ch);

  memory->attach_cage = CreateAndAttach(me, "Bellbars", OBJ_CLUTTER, 0, 0);
  memory->bell_sound = Sound_FindId("Bell");
  memory->last_play_time = Game_GetTime();
}

void JoshBell::DoCollide(int me) {
  int child_handle = Obj_GetAttachChildHandle(me, 0);

  if (child_handle == OBJECT_HANDLE_NONE /* && memory->last_play_time + 2.0f < Game_GetTime()*/) {
    memory->last_play_time = Game_GetTime();
    Sound_Play3d(me, memory->bell_sound);
  }
}

int16_t JoshBell::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED:
    DoInit(data->me_handle);
    break;
  case EVT_COLLIDE:
    DoCollide(data->me_handle);
    break;
  case EVT_MEMRESTORE: {
    memory = (joshbell_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//-----------------
// Explode On Contact
//-----------------

void ExplodeOnContact::DoCollide(int me, int it) {
  int type;
  Obj_Value(it, VF_GET, OBJV_I_TYPE, &type);

  if (type == OBJ_PLAYER) {
    msafe_struct mstruct;

    mstruct.objhandle = me;
    mstruct.killer_handle = OBJECT_HANDLE_NONE;
    mstruct.damage_type = GD_SCRIPTED;
    mstruct.amount = 1000.0f;

    MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
  }
}

int16_t ExplodeOnContact::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE:
    DoCollide(data->me_handle, data->evt_collide.it_handle);
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//-----------------
// Destroy On Contact
//-----------------

void DestroyOnContact::DoCollide(int me, int it) {
  int type;
  Obj_Value(it, VF_GET, OBJV_I_TYPE, &type);

  if (type == OBJ_BUILDING || type == OBJ_ROBOT || type == OBJ_CLUTTER || type == OBJ_PLAYER) {
    Obj_Kill(it, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
             0.0f, 0.0f);
  }
}

int16_t DestroyOnContact::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE:
    DoCollide(data->me_handle, data->evt_collide.it_handle);
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// --------------
// Pest
// --------------

void Pest::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(pest_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (pest_data *)Scrpt_MemAlloc(&ch);

  memory->tail_handle = CreateAndAttach(me, "Pesttail", OBJ_ROBOT, 0, 0);
  memory->last_anim_frame = 0;

  memory->foot_sounds[0] = Sound_FindId("RbtPestFoot1");
  memory->foot_sounds[1] = Sound_FindId("RbtPestFoot2");
  memory->foot_sounds[2] = Sound_FindId("RbtPestFoot3");

  AI_SetType(me, AIT_EVADER1);
}

int16_t Pest::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME: {
    float frame;
    Obj_Value(data->me_handle, VF_GET, OBJV_F_ANIM_FRAME, &frame);
    if ((frame > 9 && memory->last_anim_frame <= 9) || (frame > 10 && memory->last_anim_frame <= 10) ||
        (frame > 13 && memory->last_anim_frame <= 13)) {
      int index = rand() % 3;

      Sound_Play3d(data->me_handle, memory->foot_sounds[index]);
    }

    memory->last_anim_frame = frame;
  } break;
  case EVT_DESTROY: {
    msafe_struct mstruct;

    mstruct.objhandle = memory->tail_handle;
    mstruct.killer_handle = OBJECT_HANDLE_NONE;
    mstruct.damage_type = GD_SCRIPTED;
    mstruct.amount = 1000.0f;

    MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
  } break;
    break;
  case EVT_MEMRESTORE: {
    memory = (pest_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// --------------
// Stinger
// --------------

#define STINGER_MELEE_DIST 50.0f

void Stinger::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(stinger_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (stinger_data *)Scrpt_MemAlloc(&ch);

  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &m);

  memory->next_mode_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * 3.0f + 3.0f;
  memory->force_melee_shields = m.shields / 3.0f + ((((float)rand()) / (float)RAND_MAX) * m.shields) / 10.0f;
  memory->mode = STINGER_RANGED;
  memory->f_very_hurt = 0;

  AI_SetType(me, AIT_EVADER1);
}

void Stinger::DoInterval(int me) {
  bool f_force_melee = false;
  int target_handle;

  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &m);

  memory->f_very_hurt = f_force_melee = (m.shields < memory->force_melee_shields) != 0;

  if (!f_force_melee) {
    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target_handle);

    if (target_handle != OBJECT_HANDLE_NONE) {
      float dist;
      AI_Value(me, VF_GET, AIV_F_DIST_TO_TARGET, &dist);

      if (dist < STINGER_MELEE_DIST) {
        f_force_melee = true;
      }
    }
  }

  if ((!f_force_melee) && (memory->next_mode_time < Game_GetTime())) {
    memory->next_mode_time = Game_GetTime() + 7.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;

    if (rand() % 150 > 10) {
      if (memory->mode == STINGER_MELEE) {
        AI_SetType(me, AIT_EVADER1);
        memory->mode = STINGER_RANGED;
      }
    } else {
      if (memory->mode == STINGER_RANGED) {
        AI_SetType(me, AIT_MELEE1);
        memory->mode = STINGER_MELEE;
      }
    }
  } else if ((f_force_melee) && (memory->mode != STINGER_MELEE)) {
    //		PlaySoundObj3d("RbtStingeattack1", me)
    AI_SetType(me, AIT_MELEE1);
    memory->mode = STINGER_MELEE;
  }
}

int16_t Stinger::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoInterval(data->me_handle);
    break;
  case EVT_MEMRESTORE: {
    memory = (stinger_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// --------------
// Humonculous
// --------------

// Humonculous modes are in prescidence order  (lowest to highest)
#define HM_IDLE 0x0001
#define HM_INTRO_CUTSCENE 0x0002
#define HM_RANGED 0x0004
#define HM_MELEE 0x0008
#define HM_WALL_HIT 0x0010
#define HM_MID_DAMAGE_TAUNT 0x0020
#define HM_ABOUT_TO_FAKE_DEATH 0x0040
#define HM_FAKE_DEATH 0x0080
#define HM_DEATH_CHARGE 0x0100
#define HM_ABOUT_TO_DIE 0x0200
#define HM_DEAD 0x0400

#define H_WALL_HIT_INTERVAL 15.0f

#define H_DOOR_WAIT_TIME 8.0f

// Valid next modes from each mode (Humonculous Mode Valid Next)
const int16_t hm_valid_next_modes[11] = {
    (HM_INTRO_CUTSCENE),
    (HM_RANGED | HM_MELEE | HM_WALL_HIT | HM_MID_DAMAGE_TAUNT | HM_ABOUT_TO_FAKE_DEATH),
    (HM_RANGED | HM_MELEE | HM_WALL_HIT | HM_MID_DAMAGE_TAUNT | HM_ABOUT_TO_FAKE_DEATH),
    (HM_RANGED | HM_MELEE | HM_WALL_HIT | HM_MID_DAMAGE_TAUNT | HM_ABOUT_TO_FAKE_DEATH),
    (HM_RANGED | HM_MELEE | HM_MID_DAMAGE_TAUNT | HM_ABOUT_TO_FAKE_DEATH),
    (HM_RANGED | HM_MELEE | HM_WALL_HIT | HM_ABOUT_TO_FAKE_DEATH),
    (HM_FAKE_DEATH),
    (HM_DEATH_CHARGE),
    (HM_ABOUT_TO_DIE),
    (HM_DEAD),
    (0),
};

#define HF_PLAYER_DEAD 0x01
#define HF_VERY_HURT 0x02
#define HF_DID_FINAL_MELEE 0x04
#define HF_LANDED 0x08
#define HF_ORIENTED 0x10
#define HF_HIT_WALL 0x20
#define HF_DID_MID_DAMAGE 0x40
#define HF_HIT_WALL_SHAKED 0x80
#define HF_HIT_WALL_ASSIGNED 0x100
#define HF_MID_DAMAGE_ASSIGNED 0x200
#define HF_AT_FDPOS 0x400
#define HF_AT_RDPOS 0x800

#define H_GUID_LANDED 0x1010002B
#define H_GUID_AT_FDPOS 0x101000BE
#define H_GUID_AT_RDPOS 0x10100022

// chrishack -- NOTE:  Give the player an extra powerup if he kills the boss before he can do his
// final melee attack

#define H_MELEE_DIST 50.0f

void Humonculous::DetermineDeathPos(int me, vector *dpos, int *droom) {
  float best_dist = 100000000.0f;
  int best_dp;
  vector dp[6];
  int dr[6];
  int i;

  vector mpos;
  Obj_Value(me, VF_GET, OBJV_V_POS, &mpos);

  Obj_Value(Scrpt_FindObjectName("SafeDeath01"), VF_GET, OBJV_V_POS, &dp[0]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath01"), VF_GET, OBJV_I_ROOMNUM, &dr[0]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath02"), VF_GET, OBJV_V_POS, &dp[1]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath02"), VF_GET, OBJV_I_ROOMNUM, &dr[1]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath03"), VF_GET, OBJV_V_POS, &dp[2]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath03"), VF_GET, OBJV_I_ROOMNUM, &dr[2]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath04"), VF_GET, OBJV_V_POS, &dp[3]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath04"), VF_GET, OBJV_I_ROOMNUM, &dr[3]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath05"), VF_GET, OBJV_V_POS, &dp[4]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath05"), VF_GET, OBJV_I_ROOMNUM, &dr[4]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath06"), VF_GET, OBJV_V_POS, &dp[5]);
  Obj_Value(Scrpt_FindObjectName("SafeDeath06"), VF_GET, OBJV_I_ROOMNUM, &dr[5]);

  for (i = 0; i < 6; i++) {
    dp[i].y = -440.0f;

    float cur_dist = vm_VectorDistance(&mpos, &dp[i]);

    if (cur_dist < best_dist) {
      *dpos = dp[i];
      *droom = dr[i];
      best_dist = cur_dist;
    }
  }
}

bool Humonculous::DoNotify(int me, tOSIRISEventInfo *data) {
  switch (memory->mode) {
  case HM_IDLE: {
    if (data->evt_ai_notify.notify_type == AIN_MOVIE_START) {
      SetMode(me, HM_INTRO_CUTSCENE);
    }
  } break;

  case HM_INTRO_CUTSCENE: {
    if (data->evt_ai_notify.notify_type == AIN_MOVIE_END) {
      SetMode(me, HM_MELEE);
    }
  } break;

  case HM_WALL_HIT: {
    if (data->evt_ai_notify.notify_type == AIN_GOAL_COMPLETE && data->evt_ai_notify.goal_uid == H_GUID_LANDED) {
      Obj_SetCustomAnim(me, 101.0f, 125.0f, 4.0f, AIAF_NOTIFY, Sound_FindId("RbtHmclIWallHit"), AS_ALERT);
    }
  } break;

  case HM_ABOUT_TO_FAKE_DEATH:
  case HM_ABOUT_TO_DIE: {
    if (data->evt_ai_notify.notify_type == AIN_SCRIPTED_ORIENT) {
      vector uvec = Zero_vector;
      uvec.y = 1.0f;

      if (AI_TurnTowardsVectors(me, &memory->land_fvec, &uvec))
        memory->flags |= HF_ORIENTED;
      else
        memory->flags &= ~HF_ORIENTED;
    }

    if (data->evt_ai_notify.notify_type == AIN_GOAL_COMPLETE && data->evt_ai_notify.goal_uid == H_GUID_LANDED) {
      memory->flags |= HF_LANDED;
    }

    if (data->evt_ai_notify.notify_type == AIN_GOAL_COMPLETE && data->evt_ai_notify.goal_uid == H_GUID_AT_FDPOS) {
      memory->flags |= HF_AT_FDPOS;
      memory->mode_time = 0.0f;

      vector vel = {0.0f, 0.0f, 0.0f};
      Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);

      Obj_SetCustomAnim(me, 167.0f, 210.0f, 6.0f, 0, Sound_FindId("RbtHmclFakeDeath"), -1);
    }

    if (data->evt_ai_notify.notify_type == AIN_GOAL_COMPLETE && data->evt_ai_notify.goal_uid == H_GUID_AT_RDPOS) {
      memory->flags |= HF_AT_RDPOS;
      memory->mode_time = 0.0f;

      vector vel = {0.0f, 0.0f, 0.0f};
      Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);

      Obj_SetCustomAnim(me, 242.0f, 350.0f, 15.0f, 0, Sound_FindId("RbtHmclDeath"), -1);
    }
  } break;
  }

  return true;
}

bool Humonculous::SetMode(int me, uint16_t mode) {
  int new_mode_index = -1;
  int old_mode_index = -1;

  int temp = mode;

  // Determine the index (bit position from 0 to 31) of the mode (they are bit flags)
  do {
    temp >>= 1;
    new_mode_index++;
  } while (temp != 0);

  temp = memory->mode;
  do {
    temp >>= 1;
    old_mode_index++;
  } while (temp != 0);

  // Reactivates firing and melee attacks
  if (memory->mode == HM_WALL_HIT) {
    memory->next_wall_hit_check_time = Game_GetTime() + H_WALL_HIT_INTERVAL;
    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    flags = PF_POINT_COLLIDE_WALLS;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    memory->flags &= ~(HF_HIT_WALL_SHAKED | HF_HIT_WALL);
  } else if (memory->mode == HM_MID_DAMAGE_TAUNT) {
    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
  }

  // Determine if we can goto the next mode
  if (!(hm_valid_next_modes[old_mode_index] & mode))
    return false;

  // Clear out the robot
  AI_SetType(me, AIT_AIS);

  switch (mode) {
  case HM_IDLE: {
  } break;
  case HM_INTRO_CUTSCENE: {
  } break;
  case HM_RANGED: {
    AI_SetType(me, AIT_EVADER1);
  } break;
  case HM_MELEE: {
    AI_SetType(me, AIT_MELEE1);
  } break;
  case HM_WALL_HIT: {
    memory->flags |= HF_HIT_WALL_ASSIGNED;

    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    vector start_pos;
    int start_room;
    vector end_pos;

    ray_info ray;

    matrix orient;
    Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

    memory->land_fvec = orient.fvec;
    memory->land_fvec.y = 0.0f;
    vm_VectorNormalize(&memory->land_fvec);
    orient.fvec = memory->land_fvec;

    vm_VectorNormalize(&orient.rvec);

    Obj_Value(me, VF_GET, OBJV_V_POS, &start_pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &start_room);

    // Determine real start pos - room
    end_pos = start_pos;
    end_pos += orient.rvec * 29.0f;
    end_pos += orient.fvec * 33.215f;

    flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
            FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
    int fate = FVI_RayCast(me, &start_pos, &end_pos, start_room, 0.0f, flags, &ray);

    start_pos = end_pos = ray.hit_point;
    start_room = ray.hit_room;

    end_pos += 5000.0f * orient.rvec;

    flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
            FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
    fate = FVI_RayCast(me, &start_pos, &end_pos, start_room, 0.0f, flags, &ray);

    if (ray.hit_wallnorm * orient.rvec > -0.95) {
      memory->mode = HM_WALL_HIT;
      SetMode(me, HM_MELEE);
      return false;
    }

    memory->land_pos = ray.hit_point - (orient.fvec * 33.215f) - (orient.rvec * 29.0f);

    AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, H_GUID_LANDED, GF_ORIENT_SCRIPTED | GF_USE_BLINE_IF_SEES_GOAL | GF_NOTIFIES,
               &memory->land_pos, ray.hit_room);

    float dist = 0.0f;
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    flags = PF_POINT_COLLIDE_WALLS;
    Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
  } break;
  case HM_MID_DAMAGE_TAUNT: {
    memory->flags |= HF_MID_DAMAGE_ASSIGNED;

    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    Obj_SetCustomAnim(me, 360.0f, 420.0f, 8.0f, AIAF_NOTIFY, Sound_FindId("RbtHmclMidTaunt"), AS_ALERT);
  } break;
  case HM_ABOUT_TO_FAKE_DEATH: {
    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    // Guarentee no wall hits or mid damage stuff after the fake death
    memory->flags |= (HF_HIT_WALL_ASSIGNED | HF_MID_DAMAGE_ASSIGNED);

    vector dpos;
    int droom;
    DetermineDeathPos(me, &dpos, &droom);

    AI_AddGoal(me, AIG_GET_TO_POS, 3, 1.0, H_GUID_AT_FDPOS, GF_USE_BLINE_IF_SEES_GOAL | GF_NOTIFIES, &dpos, droom);
    AI_SetGoalCircleDist(me, 3, 0.0f);
  } break;
  case HM_FAKE_DEATH: {
    Obj_SetCustomAnim(me, 210.0f, 242.0f, 5.0f, AIAF_NOTIFY, Sound_FindId("RbtHmclFakeGetUp"), AS_ALERT);
  } break;
  case HM_DEATH_CHARGE: {
    memory->flags &= ~(HF_LANDED | HF_ORIENTED);

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->max_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->max_delta_speed);

    int flags = PF_POINT_COLLIDE_WALLS;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
    flags = PF_LEVELING;
    Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    flags = AIF_DISABLE_MELEE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    flags = OF_AI_DEATH;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_FLAGS, &flags);

    msafe_struct m;
    m.objhandle = me;
    m.shields = 20.0f;
    MSafe_CallFunction(MSAFE_OBJECT_SHIELDS, &m);

    AI_SetType(me, AIT_MELEE1);
  } break;
  case HM_ABOUT_TO_DIE: {
    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    float circle_dist = -1.0f;
    AI_Value(me, VF_SET, AIV_F_CIRCLE_DIST, &circle_dist);

    vector dpos;
    int droom;
    DetermineDeathPos(me, &dpos, &droom);

    AI_AddGoal(me, AIG_GET_TO_POS, 3, 1.0, H_GUID_AT_RDPOS, GF_USE_BLINE_IF_SEES_GOAL | GF_NOTIFIES, &dpos, droom);
    AI_SetGoalCircleDist(me, 3, 0.0f);
  } break;
  case HM_DEAD: {
  } break;
  default:
    mprintf(0, "WHAT ARE YOU DOING!!!!!!!!!!!!!");
  }

  // Reset the important mode variables
  memory->mode = mode;
  memory->mode_time = 0.0f;

  return true;
}

void Humonculous::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(humonculous_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (humonculous_data *)Scrpt_MemAlloc(&ch);

  char diff = Game_GetDiffLevel();
  float shields;
  float speed;
  int flags;

  Obj_Value(me, VF_GET, OBJV_F_SHIELDS, &shields);
  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &speed);

  if (diff == DIFFICULTY_TRAINEE) {
    shields = shields * 0.7f;
    speed = speed * 0.6f;
  } else if (diff == DIFFICULTY_ROOKIE) {
    shields = shields * 0.85f;
    speed = speed * 0.7f;
  }

  Obj_Value(me, VF_SET, OBJV_F_SHIELDS, &shields);
  AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);

  memory->last_shields = shields;
  memory->next_mode_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * 3.0f + 3.0f;
  memory->force_melee_shields = shields / 3.0f + ((((float)rand()) / (float)RAND_MAX) * shields) / 10.0f;
  memory->force_mid_damage_shields = shields * 0.5f;
  memory->force_wall_hit_shields = shields * 0.80f;
  memory->mode = HM_IDLE;
  memory->flags = 0;
  memory->next_wall_hit_check_time = Game_GetTime() + 25.0f;

  matrix orient;
  vector pos;
  vector g_pos;
  vector g_norm;

  Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);
  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
  Obj_GetGroundPos(me, 0, &g_pos, &g_norm);

  vector from_ground = pos - g_pos;
  memory->ground_pnt_offset = fabs(from_ground * orient.uvec);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->max_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->max_delta_speed);

  memory->josh[0] = CreateAndAttach(me, "Joshbot", OBJ_ROBOT, 2, 0, true, true);
  flags = PF_NO_COLLIDE_PARENT;
  Obj_Value(memory->josh[0], VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
  flags = OF_DESTROYABLE;
  Obj_Value(memory->josh[0], VF_CLEAR_FLAGS, OBJV_I_FLAGS, &flags);

  //	CreateAndAttach(me, "Joshbot", OBJ_ROBOT, 3, 0 ,true, false);
  memory->josh[1] = CreateAndAttach(me, "Joshbot", OBJ_ROBOT, 4, 0, true, true);
  flags = PF_NO_COLLIDE_PARENT;
  Obj_Value(memory->josh[1], VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
  flags = OF_DESTROYABLE;
  Obj_Value(memory->josh[1], VF_CLEAR_FLAGS, OBJV_I_FLAGS, &flags);

  memory->rocks[0] = Scrpt_FindObjectName("BossRock01");
  memory->rocks[1] = Scrpt_FindObjectName("BossRock02");
  memory->rocks[2] = Scrpt_FindObjectName("BossRock03");
  memory->rocks[3] = Scrpt_FindObjectName("BossRock04");
  memory->rocks[4] = Scrpt_FindObjectName("BossRock05");

  CreateAndAttach(me, "Humonbodyarmor", OBJ_ROBOT, 0, 0, true, false);
  CreateAndAttach(me, "Humonwristarmor", OBJ_ROBOT, 1, 0, true, false);

  SetMode(me, HM_IDLE);
}

void Humonculous::DoInterval(int me) {
  int flags;
  Obj_Value(me, VF_GET, OBJV_I_FLAGS, &flags);

  //	float frame;
  //	Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &frame);
  //	mprintf(0, "Anim frame is %f\n", frame);
  float shields;
  Obj_Value(me, VF_GET, OBJV_F_SHIELDS, &shields);

  if (shields < memory->force_mid_damage_shields && !(memory->flags & HF_MID_DAMAGE_ASSIGNED)) {
    char anim_type;
    AI_Value(me, VF_GET, AIV_C_ANIMATION_TYPE, &anim_type);

    if (anim_type != AS_RANGED_ATTACK && anim_type != AS_MELEE1 && anim_type != AS_MELEE2)
      SetMode(me, HM_MID_DAMAGE_TAUNT);
  }

  if (shields < memory->force_wall_hit_shields && !(memory->flags & HF_HIT_WALL_ASSIGNED)) {
    char anim_type;
    AI_Value(me, VF_GET, AIV_C_ANIMATION_TYPE, &anim_type);

    if (anim_type != AS_RANGED_ATTACK && anim_type != AS_MELEE1 && anim_type != AS_MELEE2) {
      mprintf(0, "HEHRE  HERHERHERHERHEHREHRHERHEHREHR\n");
      SetMode(me, HM_WALL_HIT);
    }
  }

  if ((memory->mode < HM_ABOUT_TO_FAKE_DEATH) && (flags & OF_AI_DEATH)) {
    char anim_type;
    AI_Value(me, VF_GET, AIV_C_ANIMATION_TYPE, &anim_type);

    if (anim_type != AS_RANGED_ATTACK && anim_type != AS_MELEE1 && anim_type != AS_MELEE2)
      SetMode(me, HM_ABOUT_TO_FAKE_DEATH);
  }

  if (memory->mode == HM_DEATH_CHARGE && memory->mode_time > 4.0f && (flags & OF_AI_DEATH)) {
    char anim_type;
    AI_Value(me, VF_GET, AIV_C_ANIMATION_TYPE, &anim_type);

    if (anim_type != AS_RANGED_ATTACK && anim_type != AS_MELEE1 && anim_type != AS_MELEE2)
      SetMode(me, HM_ABOUT_TO_DIE);
  }

  switch (memory->mode) {
  case HM_INTRO_CUTSCENE: {
    if (memory->mode_time < H_DOOR_WAIT_TIME && memory->mode_time + Game_GetFrameTime() >= H_DOOR_WAIT_TIME) {
      vector velocity = Zero_vector;
      velocity.y = 65.0f;

      Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &velocity);

      int flags = AIF_FORCE_AWARENESS | AIF_DETERMINE_TARGET;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      float awareness = AWARE_FULLY;
      AI_Value(me, VF_SET, AIV_F_AWARENESS, &awareness);
    }
  } break;
  case HM_RANGED:
  case HM_MELEE: {
    bool f_force_melee;
    int target_handle;

    msafe_struct m;
    m.objhandle = me;
    MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &m);

    f_force_melee = (m.shields < memory->force_melee_shields);

    if (f_force_melee)
      memory->flags |= HF_VERY_HURT;
    else
      memory->flags &= ~HF_VERY_HURT;

    if (!f_force_melee) {
      AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target_handle);

      if (target_handle != OBJECT_HANDLE_NONE) {
        float dist;
        AI_Value(me, VF_GET, AIV_F_DIST_TO_TARGET, &dist);

        if (dist < H_MELEE_DIST) {
          f_force_melee = true;
        }
      }
    }

    if ((!f_force_melee) && (memory->next_mode_time < Game_GetTime())) {
      memory->next_mode_time = Game_GetTime() + 3.0f + ((float)rand() / (float)RAND_MAX) * 2.0f;

      if ((rand() % 150) > 10) {
        SetMode(me, HM_RANGED);
      } else {
        SetMode(me, HM_MELEE);
      }
    } else if ((f_force_melee) && (memory->mode != HM_MELEE)) {
      //		PlaySoundObj3d("RbtStingeattack1", me)
      SetMode(me, HM_MELEE);
    }
  } break;

  case HM_MID_DAMAGE_TAUNT: {
    float frame;
    Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &frame);

    if (frame >= 360.0f && frame <= 420.0f) {
      memory->flags |= HF_DID_MID_DAMAGE;

      if (memory->mode_time < 4.53f && memory->mode_time + Game_GetFrameTime() >= 4.53f) {
        int xxx;
        matrix orient;
        Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

        // Launch joshbots
        for (xxx = 0; xxx < 2; xxx++) {
          int flags = OF_DESTROYABLE;
          vector vel = orient.fvec * 80.0f;

          Obj_UnattachFromParent(memory->josh[xxx]);
          Obj_Value(memory->josh[xxx], VF_SET, OBJV_V_VELOCITY, &vel);

          Obj_Value(memory->josh[xxx], VF_SET_FLAGS, OBJV_I_FLAGS, &flags);
        }
      }
    }

    if ((memory->flags & HF_DID_MID_DAMAGE) && !(frame >= 360.0f && frame <= 420.0f)) {
      SetMode(me, HM_RANGED);
    }
  } break;

  case HM_WALL_HIT: {
    char anim_type;
    char next_anim_type;
    AI_Value(me, VF_GET, AIV_C_ANIMATION_TYPE, &anim_type);
    AI_Value(me, VF_GET, AIV_C_NEXT_ANIMATION_TYPE, &next_anim_type);

    float frame;
    Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &frame);

    if ((memory->flags & HF_HIT_WALL) == 0) {

      if (frame >= 101.0f && frame <= 125.0f) {
        memory->flags |= HF_HIT_WALL;
      }
    } else if (frame >= 110.0f && !(memory->flags & HF_HIT_WALL_SHAKED)) {
      memory->flags |= HF_HIT_WALL_SHAKED;

      // shake players at wall hit
      msafe_struct mstruct;
      mstruct.amount = 65.0f;
      MSafe_CallFunction(MSAFE_OBJECT_VIEWER_SHAKE, &mstruct);

      int i;
      char mtype = MT_PHYSICS;
      for (i = 0; i < 5; i++) {
        Obj_Value(memory->rocks[i], VF_SET, OBJV_C_MOVEMENT_TYPE, &mtype);
      }
    }

    if (memory->mode_time > 4.0f && anim_type != AS_CUSTOM && next_anim_type != AS_CUSTOM &&
        (memory->flags & HF_HIT_WALL)) {
      SetMode(me, HM_RANGED);
    } else if (memory->mode_time > 15.0f &&
               anim_type != AS_CUSTOM) // Safety case - if there is a messup, return to ranged (worked fine)
    {
      SetMode(me, HM_RANGED);
    }
  } break;

  case HM_ABOUT_TO_FAKE_DEATH: {
    if (memory->flags & HF_AT_FDPOS) {
      if (memory->mode_time < 6.0f && memory->mode_time + Game_GetFrameTime() >= 6.0f) {
        vector start_pos;
        int start_room;
        vector end_pos;

        ray_info ray;

        Obj_Value(me, VF_GET, OBJV_V_POS, &start_pos);
        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &start_room);
        end_pos = start_pos;
        end_pos.y -= 2000.0f;

        int flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
                    FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
        int fate = FVI_RayCast(me, &start_pos, &end_pos, start_room, 0.0f, flags, &ray);

        memory->land_pos = ray.hit_point;
        memory->land_pos.y += memory->ground_pnt_offset;

        float max_speed = 20.0f;
        float max_delta_speed = 50.0f;

        AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &max_speed);
        AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &max_delta_speed);

        AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, H_GUID_LANDED,
                   GF_ORIENT_SCRIPTED | GF_USE_BLINE_IF_SEES_GOAL | GF_NOTIFIES, &memory->land_pos, ray.hit_room);

        float dist = 0.0f;
        AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

        flags = PF_POINT_COLLIDE_WALLS;
        Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
        flags = PF_LEVELING;
        Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

        matrix orient;
        Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

        memory->land_fvec = orient.fvec;
        memory->land_fvec.y = 0.0f;
        vm_VectorNormalize(&memory->land_fvec);
      }

      if (memory->mode_time > 15.0f && (memory->flags & HF_LANDED) && (memory->flags & HF_ORIENTED)) {
        SetMode(me, HM_FAKE_DEATH);
      }
    }

    if (memory->mode_time > 60.0f) {
      SetMode(me, HM_FAKE_DEATH);
    }
  } break;

  case HM_FAKE_DEATH: {
    if (memory->mode_time > 4.0f) {
      vector velocity = Zero_vector;
      velocity.y = 40.0f;

      Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &velocity);
      SetMode(me, HM_DEATH_CHARGE);
    }
  } break;

  case HM_ABOUT_TO_DIE: {
    if (memory->flags & HF_AT_RDPOS) {
      if (memory->mode_time < 10.0f && memory->mode_time + Game_GetFrameTime() >= 10.0f) {
        Obj_Burning(me, 1000000.0f, 1.0f);
      }

      if (memory->mode_time < 12.5f && memory->mode_time + Game_GetFrameTime() >= 12.5f) {
        vector start_pos;
        int start_room;
        vector end_pos;

        ray_info ray;

        Obj_Value(me, VF_GET, OBJV_V_POS, &start_pos);
        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &start_room);
        end_pos = start_pos;
        end_pos.y -= 2000.0f;

        int flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
                    FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
        int fate = FVI_RayCast(me, &start_pos, &end_pos, start_room, 0.0f, flags, &ray);

        memory->land_pos = ray.hit_point;
        memory->land_pos.y += memory->ground_pnt_offset;

        float max_speed = 20.0f;
        float max_delta_speed = 50.0f;

        AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &max_speed);
        AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &max_delta_speed);

        AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, H_GUID_LANDED,
                   GF_ORIENT_SCRIPTED | GF_USE_BLINE_IF_SEES_GOAL | GF_NOTIFIES, &memory->land_pos, ray.hit_room);

        float dist = 0.0f;
        AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

        flags = PF_POINT_COLLIDE_WALLS;
        Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
        flags = PF_LEVELING;
        Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

        matrix orient;
        Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

        memory->land_fvec = orient.fvec;
        memory->land_fvec.y = 0.0f;
        vm_VectorNormalize(&memory->land_fvec);
      }
    }

    if (memory->mode_time > 45.0f && !(memory->flags & HF_AT_RDPOS)) {
      memory->flags |= HF_AT_RDPOS;
      memory->mode_time = 0.0f;

      vector vel = {0.0f, 0.0f, 0.0f};
      Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);

      Obj_SetCustomAnim(me, 242.0f, 350.0f, 15.0f, 0, Sound_FindId("RbtHmclDeath"), -1);
    }
  } break;
  }

  memory->last_shields = shields;
  memory->mode_time += Game_GetFrameTime();
}

int16_t Humonculous::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoInterval(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (humonculous_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// --------------
// Dragon
// --------------

void Dragon::DoInit(int me) {
  int i;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(dragon_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (dragon_data *)Scrpt_MemAlloc(&ch);

  memory->head_object = CreateAndAttach(me, "Dragonhead", OBJ_ROBOT, 1, 0);
  memory->tail_object = CreateAndAttach(me, "Dragontail", OBJ_ROBOT, 0, 6);
  memory->green_turret = CreateAndAttach(me, "Dragonturret", OBJ_ROBOT, 2, 0);

  for (i = 0; i < 6; i++) {
    memory->t[i] = CreateAndAttach(memory->tail_object, "Dragontailturret", OBJ_ROBOT, i, 1);
    memory->tentacle[i] = CreateAndAttach(memory->t[i], "Dragontentacle", OBJ_ROBOT, 0, 0);
  }

  memory->mode = DRAGON_ARMOR;

  AI_SetType(me, AIT_EVADER1);
}

int16_t Dragon::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_MEMRESTORE: {
    memory = (dragon_data *)data->evt_memrestore.memory_ptr;
  } break;
  case EVT_DESTROY: {
    int i;

    Obj_Kill(memory->head_object, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
             0.0f, 0.0f);
    Obj_Kill(memory->tail_object, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
             0.0f, 0.0f);
    Obj_Kill(memory->green_turret, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
             0.0f, 0.0f);
    for (i = 0; i < 6; i++) {
      Obj_Kill(memory->t[i], OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
      Obj_Kill(memory->tentacle[i], OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//-----------
// Tracker
//-----------

void Tracker::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(tracker_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (tracker_data *)Scrpt_MemAlloc(&ch);

  memory->turret_object = CreateAndAttach(me, "Trackerturret", OBJ_ROBOT, 1, 0);
  memory->hatch_object = CreateAndAttach(me, "Trackerhatch", OBJ_ROBOT, 0, 0);

  AI_SetType(me, AIT_EVADER1);
}

int16_t Tracker::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_MEMRESTORE: {
    memory = (tracker_data *)data->evt_memrestore.memory_ptr;
  } break;
  case EVT_DESTROY: {
    msafe_struct mstruct;

    mstruct.objhandle = memory->hatch_object;
    mstruct.killer_handle = OBJECT_HANDLE_NONE;
    mstruct.damage_type = GD_SCRIPTED;
    mstruct.amount = 1000.0f;

    MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);

    mstruct.objhandle = memory->turret_object;
    mstruct.killer_handle = OBJECT_HANDLE_NONE;
    mstruct.damage_type = GD_SCRIPTED;
    mstruct.amount = 1000.0f;

    MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// --------------
// Lance
// --------------

void Lance::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(lance_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (lance_data *)Scrpt_MemAlloc(&ch);

  memory->mode = LANCE_MOVING;
}

void Lance::DoFrame(int me) {
  float frame;

  Obj_WBValue(me, 0, VF_GET, WBV_F_ANIM_FRAME, &frame);

  if (frame > 2.0f && frame < 6.0f) {
    if (memory->mode == LANCE_MOVING) {
      int flags = AIF_DISABLE_FIRING;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
      memory->mode = LANCE_PAUSED;
    }
  } else if (memory->mode == LANCE_PAUSED) {
    int flags = AIF_DISABLE_FIRING;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    memory->mode = LANCE_MOVING;
  }
}

int16_t Lance::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_MEMRESTORE: {
    memory = (lance_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// --------------
// Flak
// --------------

void Flak::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(flak_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (flak_data *)Scrpt_MemAlloc(&ch);

  memory->canopy_handle = CreateAndAttach(me, "Flakcanopy", OBJ_ROBOT, 0, 0);
  memory->f_dead = false;

  AI_SetType(me, AIT_EVADER1);
}

int16_t Flak::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_INTERVAL: {
    if (!memory->f_dead) {
      int type;
      Obj_Value(memory->canopy_handle, VF_GET, OBJV_I_TYPE, &type);
      if (type != OBJ_ROBOT) {
        char ctype = CT_NONE;
        Obj_Value(data->me_handle, VF_SET, OBJV_C_CONTROL_TYPE, &ctype);

        vector vel = {0.0f, 0.0f, 0.0f};
        Obj_Value(data->me_handle, VF_SET, OBJV_V_VELOCITY, &vel);

        msafe_struct mstruct;

        mstruct.random = 21;
        mstruct.is_real = 0;
        mstruct.objhandle = data->me_handle;
        mstruct.gunpoint = -2;
        mstruct.effect_type = MED_SMOKE_INDEX;
        mstruct.phys_info = 0;
        mstruct.drag = .001f;
        mstruct.mass = .001f;
        mstruct.interval = .1f;
        mstruct.longevity = 5.0f;
        mstruct.lifetime = 1.0;
        mstruct.size = 6.0f;
        mstruct.speed = 25.0;

        MSafe_CallFunction(MSAFE_OBJECT_START_SPEW, &mstruct);

        memory->f_dead = true;
        memory->death_time = Game_GetTime();
      }
    } else {
      if (Game_GetTime() > memory->death_time + 5.0f) {
        Obj_Kill(data->me_handle, OBJECT_HANDLE_NONE, 1000.0f,
                 DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
                 0.0f, 0.0f);
      }
    }
  } break;
  case EVT_DESTROY:
    Obj_Kill(memory->canopy_handle, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
             0.0f, 0.0f);
    break;
  case EVT_MEMRESTORE: {
    memory = (flak_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
//  Super Trooper
//---------------

void SuperTrooper::DoInit(int me) {
  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_ID, &m);
  int st_id = Obj_FindID("supertrooper");

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(supertrooper_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (supertrooper_data *)Scrpt_MemAlloc(&ch);

  if (m.id == st_id) {
    memory->body_handle = CreateAndAttach(me, "supertorso", OBJ_ROBOT, 0, 0);
  } else {
    memory->body_handle = CreateAndAttach(me, "red supertorso", OBJ_ROBOT, 0, 0);
  }

  AI_SetType(me, AIT_EVADER1);
}

int16_t SuperTrooper::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    int body_handle = Obj_GetAttachChildHandle(data->me_handle, 0);
    if (body_handle != memory->body_handle) {
      msafe_struct mstruct;

      mstruct.objhandle = data->me_handle;
      mstruct.killer_handle = OBJECT_HANDLE_NONE;
      mstruct.damage_type = GD_SCRIPTED;
      mstruct.amount = 1000.0f;

      MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
    }
  } break;
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_DESTROY: {
    msafe_struct mstruct;

    mstruct.objhandle = memory->body_handle;
    mstruct.killer_handle = OBJECT_HANDLE_NONE;
    mstruct.damage_type = GD_SCRIPTED;
    mstruct.amount = 1000.0f;

    MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
  } break;
  case EVT_MEMRESTORE: {
    memory = (supertrooper_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Juggernaut
//---------------

void Jugg::SetMode(int me, char mode) {
  switch (mode) {
  case JUGG_NORMAL:
    break;
  case JUGG_DYING: {
    char type = MT_NONE;
    char aimtype = MC_STANDING;
    Obj_Value(me, VF_SET, OBJV_C_MOVEMENT_TYPE, &type);
    AI_Value(me, VF_SET, AIV_C_MOVEMENT_TYPE, &aimtype);

    Obj_SetCustomAnim(me, 8.0f, 20.0f, 4.0f, 0, -1, -1);
  } break;
  }

  memory->mode = mode;
  memory->mode_time = 0.0f;
}

void Jugg::DoInit(int me) {
  int head_object;
  int belly_object;
  int turret_object;
  int flame_object;
  int i;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(jugg_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (jugg_data *)Scrpt_MemAlloc(&ch);

  memory->head_object = CreateAndAttach(me, "Jugghead", OBJ_ROBOT, 0, 0);

  // Left
  memory->head_turret[0] = CreateAndAttach(memory->head_object, "Juggheadturretright", OBJ_ROBOT, 1, 0);
  // Right
  memory->head_turret[1] = CreateAndAttach(memory->head_object, "Juggheadturretleft", OBJ_ROBOT, 2, 0);

  memory->belly_object = CreateAndAttach(me, "Juggbelly", OBJ_ROBOT, 1, 0);

  for (i = 0; i < 6; i++) {
    memory->turret_object[i] = CreateAndAttach(me, "Jugg main turret", OBJ_ROBOT, i + 2, 0);
  }

  memory->flame_turret[0] = CreateAndAttach(memory->belly_object, "Jugg flame turret", OBJ_ROBOT, 1, 0);
  memory->flame_turret[1] = CreateAndAttach(memory->belly_object, "Jugg flame turret", OBJ_ROBOT, 2, 0);
  memory->flame_turret[2] = CreateAndAttach(me, "Jugg flame turret", OBJ_ROBOT, 8, 0);

  memory->flags = 0;

  SetMode(me, JUGG_NORMAL);

  memory->foot_sound = Sound_FindId("JugFootHit");
  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &memory->last_frame);
}

void Jugg::DoFrame(int me) {
  float current_anim_frame;
  matrix orient;
  int flags;

  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &current_anim_frame);
  Obj_Value(me, VF_GET, OBJV_I_FLAGS, &flags);

  if (!(memory->flags & JUGG_F_HEAD_DEAD)) {
    int h_flags;
    Obj_Value(memory->head_object, VF_GET, OBJV_I_FLAGS, &h_flags);

    if (h_flags & OF_AI_DEATH) {
      memory->flags |= JUGG_F_HEAD_DEAD;
      AI_PowerSwitch(memory->head_object, 0);
      Obj_Burning(memory->head_object, 10.0f, 3.0f);
    }
  }

  if (!(memory->flags & JUGG_F_BODY_DEAD)) {
    if (flags & OF_AI_DEATH) {
      memory->flags |= JUGG_F_BODY_DEAD;
      Obj_Burning(me, 10.0f, 3.0f);
    }
  }

  if (memory->mode == JUGG_NORMAL && (memory->flags & JUGG_F_BODY_DEAD) && (memory->flags & JUGG_F_HEAD_DEAD)) {
    SetMode(me, JUGG_DYING);
  }

  if (memory->mode == JUGG_DYING && current_anim_frame == 20.0f) {
    AI_PowerSwitch(me, 0);
  }

  if (current_anim_frame > 1.0f && memory->last_frame <= 1.0f) {
    Sound_Play3d(me, memory->foot_sound);
  }

  if (current_anim_frame > 3.0f && memory->last_frame <= 3.0f) {
    Sound_Play3d(me, memory->foot_sound);
  }

  if (current_anim_frame > 4.0f && memory->last_frame <= 4.0f) {
    Sound_Play3d(me, memory->foot_sound);
  }

  if (current_anim_frame > 7.0f && memory->last_frame <= 7.0f) {
    Sound_Play3d(me, memory->foot_sound);
  }

  memory->mode_time += Game_GetFrameTime();
  memory->last_frame = current_anim_frame;
}

int16_t Jugg::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_INTERVAL: {
    if (!(memory->flags & JUGG_F_BELLY_DEAD)) {
      int type;
      int i;

      Obj_Value(memory->belly_object, VF_GET, OBJV_I_TYPE, &type);

      if (type == OBJ_NONE) {
        memory->flags |= JUGG_F_BELLY_DEAD;

        for (i = 0; i < 3; i++) {
          Obj_Kill(memory->flame_turret[i], OBJECT_HANDLE_NONE, 1000.0f,
                   DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART |
                       DF_DEBRIS_SMOKES,
                   0.0f, 0.0f);
        }
      }
    }
  }

  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (jugg_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Death Tower
//---------------

void DTower::DoInit(int me) {
  int head_object;
  int belly_object;
  int turret_object;
  int flame_object;
  int i;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(dtower_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (dtower_data *)Scrpt_MemAlloc(&ch);

  memory->gun_handle = CreateAndAttach(me, "Ltowergun", OBJ_CLUTTER, 0, 0);
  memory->ball_handle = CreateAndAttach(me, "Ltowerball", OBJ_CLUTTER, 1, 0);

  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &memory->last_frame);
  memory->f_died = false;
}

void DTower::DoFrame(int me) {
  float current_anim_frame;
  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &current_anim_frame);

  if (!memory->f_died) {
    int flags;
    Obj_Value(me, VF_GET, OBJV_I_FLAGS, &flags);

    if (flags & OF_AI_DEATH) {
      memory->mode_time = 0.0f;
      memory->f_died = true;
    }
  } else if (memory->mode_time < 3.0f && memory->mode_time + Game_GetFrameTime() >= 3.0f) {
    int room;
    vector pos;

    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_GetGunPos(me, 1, &pos);

    int weapon_id = Wpn_FindID("TubbsHitBlast");
    Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);

    Obj_Kill(memory->gun_handle, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES, 0.0f,
             0.0f);
    Obj_Burning(me, 10.0f, 5.0f);

    vector vel = {0.0f, 0.0f, 0.0f};
    vel.y = (float)rand() / (float)RAND_MAX * 30.0f + 90.0f;
    vel.x = (float)rand() / (float)RAND_MAX * 16.0f - 8.0f;
    vel.z = (float)rand() / (float)RAND_MAX * 16.0f - 8.0f;

    Obj_UnattachFromParent(memory->ball_handle);
    Obj_Value(memory->ball_handle, VF_SET, OBJV_V_VELOCITY, &vel);
    Obj_Burning(memory->ball_handle, 15.0f, 3.0f);

    Obj_SetCustomAnim(me, 0.0f, 10.0f, 2.0f, 0, -1, -1);
  }

  if (current_anim_frame == 10.0f) {
    Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES, 0.0f,
             0.0f);
  }

  memory->mode_time += Game_GetFrameTime();
  memory->last_frame = current_anim_frame;
}

int16_t DTower::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (dtower_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Death Collector
//---------------

void DCollector::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(dcollector_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (dcollector_data *)Scrpt_MemAlloc(&ch);

  memory->target_handle = CreateAndAttach(me, "Collectortarget", OBJ_CLUTTER, 0, 1);
  memory->rod_handle = CreateAndAttach(memory->target_handle, "Collectorrod", OBJ_CLUTTER, 0, 0);
  memory->ball_handle = CreateAndAttach(memory->rod_handle, "Collectorball", OBJ_CLUTTER, 1, 0);

  memory->f_dead = false;
}

void DCollector::DoFrame(int me) {
  if (!memory->f_dead) {
    int type;
    Obj_Value(memory->target_handle, VF_GET, OBJV_I_TYPE, &type);

    if (type == OBJ_NONE) {
      memory->f_dead = true;
      Obj_Kill(memory->rod_handle, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);

      Obj_Burning(me, 6.0f, 3.0f);

      vector vel = {0.0f, 0.0f, 0.0f};
      vel.y = (float)rand() / (float)RAND_MAX * 30.0f + 90.0f;
      vel.x = (float)rand() / (float)RAND_MAX * 8.0f - 4.0f;
      vel.z = (float)rand() / (float)RAND_MAX * 8.0f - 4.0f;
      Obj_Value(memory->ball_handle, VF_SET, OBJV_V_VELOCITY, &vel);
      Obj_Burning(memory->ball_handle, 15.0f, 3.0f);
    }
  }
}

int16_t DCollector::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (dcollector_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Chemical Ball
//---------------

void CBall::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(cball_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (cball_data *)Scrpt_MemAlloc(&ch);

  memory->f_picked_up = false;
  memory->mode_time = 0.0f;
}

void CBall::DoFrame(int me) {
  bool f_picked_up;

  f_picked_up = (Obj_GetAttachParent(me) != OBJECT_HANDLE_NONE);

  if (!memory->f_picked_up && f_picked_up) {
    memory->f_picked_up = true;
  } else if (memory->f_picked_up && !f_picked_up) {
    memory->mode_time += Game_GetFrameTime();

    if (memory->mode_time > 12.0f) {
      Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
    }
  }
}

int16_t CBall::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED:
    DoInit(data->me_handle);
    break;
  case EVT_INTERVAL:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (cball_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Sixgun
//---------------

void SixGun::DoInit(int me) {
  msafe_struct m;
  m.objhandle = me;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(sixgun_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (sixgun_data *)Scrpt_MemAlloc(&ch);

  memory->mode = 0;
  int flags = DWBF_ENABLED;
  Obj_WBValue(me, 0, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->max_speed);
  AI_Value(me, VF_GET, AIV_F_CIRCLE_DIST, &memory->circle_dist);

  float temp = 0.0f;
  AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &temp);
  temp = 20.0f;
  AI_Value(me, VF_SET, AIV_F_CIRCLE_DIST, &temp);
}

bool SixGun::DoNotify(int me, tOSIRISEVTAINOTIFY *notify) {
  if (memory->mode == 0) {
    if ((notify->notify_type == AIN_OBJ_FIRED) || (notify->notify_type == AIN_NEAR_TARGET) ||
        (notify->notify_type == AIN_HIT_BY_WEAPON) || (notify->notify_type == AIN_BUMPED_OBJ)) {
      int flags = DWBF_ENABLED;
      Obj_WBValue(me, 0, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &flags);

      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->max_speed);
      AI_Value(me, VF_SET, AIV_F_CIRCLE_DIST, &memory->circle_dist);
      AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ, 0, 1.0f, -1, GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE,
                 OBJECT_HANDLE_NONE);
      memory->mode = 1;
    }
  }

  return true;
}

int16_t SixGun::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, &data->evt_ai_notify) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (sixgun_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Explode Time Out
//---------------

void ExplodeTimeOut::DoInit(int me) {
  msafe_struct m;
  m.objhandle = me;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(explodetimeout_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (explodetimeout_data *)Scrpt_MemAlloc(&ch);
  memory->life_left = 160.0f;
}

int16_t ExplodeTimeOut::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_INTERVAL: {
    memory->life_left -= Game_GetFrameTime();
    if (memory->life_left <= 0.0f) {
      msafe_struct mstruct;

      mstruct.objhandle = data->me_handle;
      mstruct.killer_handle = OBJECT_HANDLE_NONE;
      mstruct.damage_type = GD_SCRIPTED;
      mstruct.amount = 1000.0f;

      MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
    }
  } break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (explodetimeout_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// GuideBot
//---------------

void GuideBot::ReInitAmbient(int me) {
  memory->next_ambient_time = Game_GetTime() + 1.0f;

  // In general, Turn on friend avoidance
  if (memory->last_command != GBC_RETURN_TO_SHIP) {
    int flags = AIF_AUTO_AVOID_FRIENDS;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
  }

  int dir_index = rand() % 6;
  if (dir_index == GST_NEG_UVEC)
    dir_index = GST_NEG_RVEC;
  else if (dir_index == GST_UVEC)
    dir_index = GST_RVEC;

  AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_USE_BLINE_IF_SEES_GOAL,
             memory->amb_camera_handle, dir_index);
  AI_SetGoalCircleDist(me, 0, 4.0);
  // AddGetToGoalCommonGoals(me);
}

void GuideBot::DoMessage(const char *str, bool f_high_priority, const char *sound_name, bool f_sound_2d) {
  if ((memory->flags & GBF_NO_CHATTER) && !f_high_priority)
    return;

  if (memory->last_sound_time + 2.5f < Game_GetTime()) {
    if (sound_name) {
      int s_id = Sound_FindId(sound_name);
      if (f_sound_2d)
        Sound_Play2d(memory->me, s_id);
      else
        Sound_Play3d(memory->me, s_id);
    }

    memory->last_sound_time = Game_GetTime();
  }

  char gb_message[256];
  snprintf(gb_message, sizeof(gb_message), "\1\255\255\1%s:\1\1\255\1 %s", memory->name, str);
  Player_AddHudMessage(memory->my_player, gb_message);
}

bool GuideBot::SetSubMode(int me, char sub_mode, int it) {
  switch (sub_mode) {
  case GBSM_GET_POWERUP: {
    if (memory->sub_mode == GBSM_NONE) {
      float dist = -10000.0f;
      // chrishack -- need a message!
      AI_AddGoal(me, AIG_GET_TO_OBJ, 2, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, it);
      AI_GoalValue(me, 2, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

      if (memory->sub_mode != GBSM_GET_POWERUP) {
        DoMessage(TXT_GB_I_FOUND_A_GB_POWERUP, true, "GBotExcited1");
      }
    }
  } break;
  case GBSM_NONE: {
  } break;
  }

  memory->sub_mode = sub_mode;
  //	mprintf(0, "Sub Mode is %d\n", memory->sub_mode);

  return true;
}

bool GuideBot::SetMode(int me, char mode) {
  AI_SetType(me, AIT_AIS); // Gets rid of all goal BS
  memory->mode_time = 0.0f;

  memory->time_till_next_flare = 3.0f + ((float)rand() / (float)RAND_MAX);
  memory->time_till_next_pvis_check = 0.5f + (0.5f * ((float)rand() / (float)RAND_MAX));
  memory->last_retreat_time = memory->return_time = Game_GetTime();

  if (memory->mode == GBM_RTYPE) {
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->max_acc);
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->max_speed);
  }

  if (memory->camera_obj != OBJECT_HANDLE_NONE) {
    msafe_struct mo;
    mo.objhandle = memory->camera_obj;
    MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);

    memory->camera_obj = OBJECT_HANDLE_NONE;
  }

  float dist = 4.0f;
  int g_index =
      AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1, GF_OBJ_IS_TARGET, OBJECT_HANDLE_NONE);
  AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

  int hack_flags = AIF_GB_MIMIC_PLAYER_FIRING_HACK;
  AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &hack_flags);

  int wbflags = DWBF_ENABLED;
  Obj_WBValue(me, 3, VF_CLEAR_FLAGS, WBV_I_DYNAMIC_FLAGS, &wbflags);

  if (memory->mode == GBM_EXTINGUISH && mode != GBM_EXTINGUISH) {
    msafe_struct mstruct;

    if (memory->flags & GBF_EXTINGUISHING) {
      memory->flags &= ~GBF_EXTINGUISHING;
      mstruct.id = memory->extinguish_spew_id;
      MSafe_CallFunction(MSAFE_OBJECT_STOP_SPEW, &mstruct);
    }

    mstruct.id = memory->extinguish_spew_id;
    MSafe_CallFunction(MSAFE_OBJECT_STOP_SPEW, &mstruct);
    Obj_SetCustomAnim(me, 33.0f, 41.0f, 1.2f, AIAF_NOTIFY, -1, AS_ALERT);
  }

  switch (mode) {
  case GBM_IN_SHIP:
    break;
  case GBM_ENTER_SHIP: {
    DoMessage(TXT_GB_ENTERINGSHIP, true);
  }
  case GBM_RESPAWN_ENTER_SHIP: {
    int i;

    if (mode == GBM_RESPAWN_ENTER_SHIP) {
      float gb_shields = 250;
      int flags = OF_AI_DEATH;

      Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_FLAGS, &flags);
      Obj_Value(me, VF_SET, OBJV_F_SHIELDS, &gb_shields);

      flags = AIF_AUTO_AVOID_FRIENDS;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
      Obj_Burning(me, 0.0f, 0.0f);
    }

    memory->flags &= ~GBF_WANTING_TO_ENTER_PDEAD;

    Obj_Burning(me, 0.0f, 0.0f);
    for (i = 0; i < NUM_GB_SOUNDS; i++) {
      if (memory->sounds[i] != -1) {
        Sound_Stop(memory->sounds[i], true);
        memory->sounds[i] = -1;
      }
    }

    msafe_struct m;
    m.objhandle = memory->my_player;
    m.type = OBJ_ROBOT;
    m.id = ROBOT_GUIDEBOT;
    m.flags = 0;

    MSafe_CallFunction(MSAFE_INVEN_ADD_TYPE_ID, &m);

    Obj_Ghost(me, true);
    mode = GBM_IN_SHIP;
  } break;
  case GBM_BIRTH: {
    int room;
    vector pos;
    matrix orient;
    vector vel;
    int flags;

    flags = AIF_AUTO_AVOID_FRIENDS;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    memory->f_parented = true;
    memory->f_pickup = false;
    memory->last_anim = 0.0f;

    Obj_SetCustomAnim(me, 6.0f, 12.0f, 1.0f, AIAF_NOTIFY | AIAF_IMMEDIATE, -1, AS_ALERT);

    Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(memory->my_player, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(memory->my_player, VF_GET, OBJV_M_ORIENT, &orient);

    Obj_Value(me, VF_SET, OBJV_I_ROOMNUM, &room);
    Obj_Value(me, VF_SET, OBJV_V_POS, &pos);
    Obj_Value(me, VF_SET, OBJV_M_ORIENT, &orient);

    Obj_Value(memory->my_player, VF_GET, OBJV_V_VELOCITY, &vel);

    vel += orient.fvec * 40.0f;

    Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);

    Obj_Ghost(me, false);

    msafe_struct m;
    m.objhandle = memory->my_player;
    m.type = OBJ_ROBOT;
    m.id = ROBOT_GUIDEBOT;
    m.flags = 0;

    MSafe_CallFunction(MSAFE_INVEN_REMOVE, &m);

    float time = Game_GetTime();
    Obj_Value(me, VF_SET, OBJV_F_CREATION_TIME, &time);
    Obj_Value(me, VF_SET, OBJV_I_PARENT_HANDLE, &memory->my_player);

    memory->next_ambient_time = Game_GetTime() + 1.2f;

    //			AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_KEEP_AT_COMPLETION, memory->my_player,
    // GST_FVEC); 			AI_SetGoalCircleDist(me, 0, 40.0f);

    pos += orient.fvec * 200.0f;

    AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, -1, GF_USE_BLINE_IF_SEES_GOAL | GF_NOTIFIES, &pos, room);
    AI_SetGoalCircleDist(me, 1, 1.0f);

    int s_id = Sound_FindId("GBExpulsionA");
    Sound_Play3d(memory->my_player, s_id);

    memory->last_command = -1;
  } break;
  case GBM_AMBIENT: {
    ReInitAmbient(me);
  } break;
  case GBM_DOING_TASK:
    memory->last_retreat_time = memory->return_time = Game_GetTime();
    break;
  case GBM_KIDNAPPED:
    break;
  case GBM_TALKING:
    break;
  case GBM_THIEF:
    break;
  case GBM_ON_FIRE: {
    int flags;

    // In general, Turn on friend avoidance
    flags = AIF_AUTO_AVOID_FRIENDS;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    DoMessage(TXT_GB_HELPMSG, true, "GBotConcern1");

    int s_index = Sound_FindId("GBotHurt1");
    memory->sounds[GBS_VERY_DAMAGED] = Sound_Play3d(me, s_index);

    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->my_player);
    AI_SetGoalCircleDist(me, 1, -1.0f);

    Obj_Burning(me, 1000000.0f, 1.0f);
    memory->flags = GBF_VERY_DAMAGED;

    memory->f_pickup = true;
  } break;
  case GBM_MANUAL:
    break;
  case GBM_RTYPE: {
    // In general, Turn on friend avoidance
    int flags = AIF_AUTO_AVOID_FRIENDS;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    float acc = memory->max_acc * 4.0f;
    float speed = memory->max_speed * 1.6f;
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &acc);
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);

    int room;
    vector pos;
    matrix orient;

    Obj_Value(memory->my_player, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(memory->my_player, VF_GET, OBJV_M_ORIENT, &orient);

    pos += orient.fvec * 3.0f;
    pos -= orient.uvec * 10.0f;

    memory->camera_obj = Obj_Create(OBJ_POWERUP, Obj_FindID("Invisiblepowerup"), room, &pos, &orient, me);
    msafe_struct mstruct;
    mstruct.objhandle = memory->camera_obj;
    MSafe_CallFunction(MSAFE_OBJECT_NO_RENDER, &mstruct);

    AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 3, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_ORIENT_SCRIPTED,
               memory->camera_obj, GST_NEG_FVEC);
    //			AI_SetGoalCircleDist(me, 3, 4.0f);

    int hack_flags = AIF_GB_MIMIC_PLAYER_FIRING_HACK;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &hack_flags);
  } break;
  case GBM_GO_WINGNUT: {
    AI_SetType(me, AIT_EVADER1);
    int flags = GF_ORIENT_TARGET;
    AI_GoalValue(me, 1, VF_SET_FLAGS, AIGV_I_FLAGS, &flags);

    memory->next_ambient_time = Game_GetTime() + 1.0f;

    // In general, Turn on friend avoidance
    flags = AIF_AUTO_AVOID_FRIENDS;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    int dir_index = rand() % 6;
    float interval = 2.0f;
    AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 3, 1.0f, -1, GF_KEEP_AT_COMPLETION, memory->my_player, dir_index);
    AI_GoalAddEnabler(me, 3, AIE_GT_LAST_SEE_TARGET_INTERVAL, 1.0f, 0.0f, &interval);

    Obj_WBValue(me, 3, VF_SET_FLAGS, WBV_I_DYNAMIC_FLAGS, &wbflags);
  } break;
  case GBM_EXTINGUISH:

    AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_ORIENT_GOAL_OBJ,
               memory->extinguish_obj_list[0], 0);

    AI_SetGoalCircleDist(me, 0, 20.0f);
    memory->extinguish_obj_time = 0.0f;
    memory->next_ambient_time = Game_GetTime() + 2.0f;
    break;
  }

  memory->mode = mode;
  memory->sub_mode = GBSM_NONE;

  //	mprintf(0, "Mode is %d\n", memory->mode);

  return true;
}

bool GuideBot::InitExtinguish(bool f_player_on_fire) {
  vector pos;
  int room;
  int scan_objs[25];
  int n_scan;
  int i;

  memory->num_extinguish_objs = 0;
  Obj_Value(memory->me, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &room);

  n_scan = AI_GetNearbyObjs(&pos, room, 1000.0f, scan_objs, 25, false, false, false, true);

  if (f_player_on_fire) {
    memory->extinguish_obj_list[memory->num_extinguish_objs++] = memory->my_player;
  }

  //	mprintf(0, "Scanned %d objects\n", n_scan);
  for (i = 0; i < n_scan; i++) {
    if (memory->num_extinguish_objs >= 5)
      break;

    if (f_player_on_fire && scan_objs[i] == memory->my_player)
      break;

    if (Obj_IsEffect(scan_objs[i], EF_NAPALMED)) {
      //			mprintf(0, "its on fire\n");
      if (scan_objs[i] != memory->me) {
        if (!AI_IsObjEnemy(memory->me, scan_objs[i])) {
          //					mprintf(0, "its not a enemy\n");
          memory->extinguish_obj_list[memory->num_extinguish_objs++] = scan_objs[i];
        }
      }
    }
  }

  if (memory->num_extinguish_objs) {
    SetMode(memory->me, GBM_EXTINGUISH);
    return true;
  } else {
    return false;
  }
}

int GuideBot::MakeCommandList(int *gbc_list) {
  int count = 0;
  int i;

  if (memory->mode == GBM_IN_SHIP) {
    for (i = 0; i <= GBC_RENAME; i++) {
      if (!(memory->flags & GBF_VERY_DAMAGED) && i == GBC_REPAIR_GUIDEBOT)
        continue;

      if ((memory->flags & GBF_VERY_DAMAGED) && i == GBC_EXIT_SHIP)
        continue;

      gbc_list[count++] = i;
    }
  } else if (memory->mode == GBM_AMBIENT) {
    int roomnum;
    Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &roomnum);

    LGoal_Value(VF_GET, LGV_I_NUM_ACTIVE_PRIMARIES, &memory->num_pg);
    LGoal_Value(VF_GET, LGV_I_NUM_ACTIVE_SECONDARIES, &memory->num_sg);

    for (i = GBC_FIND_ACTIVE_GOAL_0; i < NUM_GB_COMMANDS; i++) {
      if (i >= GBC_FIND_ACTIVE_GOAL_0 && i <= GBC_FIND_ACTIVE_GOAL_7) {
        if (!(i - GBC_FIND_ACTIVE_GOAL_0 < memory->num_pg))
          continue;
      } else if (i >= GBC_FIND_ACTIVE_SEC_GOAL_0 && i <= GBC_FIND_ACTIVE_SEC_GOAL_7) {
        if (!(i - GBC_FIND_ACTIVE_SEC_GOAL_0 < memory->num_sg))
          continue;
      } else if (i >= GBC_FIND_MARKER_0 && i <= GBC_FIND_MARKER_7) {
        if (Obj_MakeListOfType(memory->me, OBJ_MARKER, i - GBC_FIND_MARKER_0, false, OBJECT_HANDLE_NONE, 1,
                               &memory->g_powerup) == 0)
          continue;
      } else if (i == GBC_FIND_SPEW) {
        int handle;
        if (Obj_MakeListOfType(memory->me, OBJ_POWERUP, -1, false, memory->my_player, 1, &handle) == 0)
          continue;
      } else if (i == GBC_FIND_POWERUP) {
        int handle;
        if (Obj_MakeListOfType(memory->me, OBJ_POWERUP, -1, false, OBJECT_HANDLE_NONE, 1, &handle) == 0)
          continue;
      } else if (i == GBC_FIND_ROBOT) {
        int handle;
        if (Obj_MakeListOfType(memory->me, OBJ_ROBOT, -1, false, OBJECT_HANDLE_NONE, 1, &handle) == 0)
          continue;
      } else if (i == GBC_FIND_THIEF) {
        int id = Obj_FindID("Thief");
        int handle;

        if (id < 0 || Obj_MakeListOfType(memory->me, OBJ_ROBOT, id, false, OBJECT_HANDLE_NONE, 1, &handle) == 0)
          continue;
      } else if (i == GBC_FIND_CLOSEST_MARKER) {
        int handle;
        if (Obj_MakeListOfType(memory->me, OBJ_MARKER, -1, false, memory->my_player, 1, &handle) == 0)
          continue;
      } else if (i >= GB_POW_STRING_OFFSET && i < GB_POW_STRING_OFFSET + NUM_GB_USABLE_POWERUPS) {
        if (memory->powerups[i - GB_POW_STRING_OFFSET] <= 0)
          continue;
      } else if (i == GBC_FIND_OUTSIDE /*&& (0x80000000 & roomnum)*/)
        continue;
      else if (i == GBC_FIND_MINE /*&& !(0x80000000 & roomnum)*/)
        continue;
      else if (i == GBC_NO_CHATTER && (memory->flags & GBF_NO_CHATTER))
        continue;
      else if (i == GBC_ALLOW_CHATTER && !(memory->flags & GBF_NO_CHATTER))
        continue;

      gbc_list[count++] = i;
    }
  }

  return count;
}

void GuideBot::AddGetToGoalCommonGoals(int me) {
  AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 2, 1.0f, -1, GF_ORIENT_GOAL_OBJ, memory->my_player, GST_NEG_FVEC);
  AI_AddGoal(me, AIG_GET_TO_OBJ, 3, 1.0f, -1, GF_ORIENT_VELOCITY | GF_NOTIFIES, memory->my_player);
  AI_SetGoalCircleDist(me, 3, 20.0f);
}

bool GuideBot::DoExternalCommands(int me, gb_com *command, int it) {
  int g_robot;
  int roomnum;
  vector pos;
  int flags;

  mprintf(0, "Command %d for GB\n", command->action);

  // In general, Turn on friend avoidance
  flags = AIF_AUTO_AVOID_FRIENDS;
  AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

  if (command->action == COM_REINIT) {
    return DoInit(me, true);
  } else if (command->action == COM_DO_ACTION) {
    int param1 = command->index;
    //		mprintf(0, "P is %d\n", param1);

    memory->last_command = param1;

    if ((param1 >= GBC_FIND_ACTIVE_GOAL_0 && param1 <= GBC_FIND_ACTIVE_GOAL_7) ||
        (param1 >= GBC_FIND_ACTIVE_SEC_GOAL_0 && param1 <= GBC_FIND_ACTIVE_SEC_GOAL_7)) {
      int g_id;
      int flags;
      char type;
      int rhandle[32];
      bool rdone[32];
      int handle[32];
      bool done[32];
      int i;
      int rnum_items;
      int num_items;

      if (param1 >= GBC_FIND_ACTIVE_GOAL_0 && param1 <= GBC_FIND_ACTIVE_GOAL_7)
        LGoal_Value(VF_GET, LGSV_I_ACTIVE_PRIMARY_GOAL, &g_id, param1 - GBC_FIND_ACTIVE_GOAL_0);
      else
        LGoal_Value(VF_GET, LGSV_I_ACTIVE_SECONDARY_GOAL, &g_id, param1 - GBC_FIND_ACTIVE_SEC_GOAL_0);

      LGoal_Value(VF_GET, LGSV_I_STATUS, &flags, g_id);
      LGoal_Value(VF_GET, LGSSV_C_ITEM_TYPE, &type, g_id, 0);

      LGoal_Value(VF_GET, LGSV_I_NUM_ITEMS, &rnum_items, g_id);

      for (i = 0; i < rnum_items; i++) {
        LGoal_Value(VF_GET, LGSSV_I_ITEM_HANDLE, &rhandle[i], g_id, i);
        LGoal_Value(VF_GET, LGSSV_B_ITEM_DONE, &rdone[i], g_id, i);
      }

      num_items = 0;
      for (i = 0; i < rnum_items; i++) {
        if (!rdone[i]) {
          handle[num_items++] = rhandle[i];
        }
      }

      if (num_items == 0) {
        num_items = 1;
        handle[0] = rhandle[0];
      }

      if (flags & LGF_NOT_LOC_BASED) {
        DoMessage(TXT_GB_NOTLOCATION, true, "GBotConcern1");
      } else if (flags & LGF_GB_DOESNT_KNOW_LOC) {
        DoMessage(TXT_GB_NONAV, true, "GBotConcern1");
      } else if (type == LIT_OBJECT) {
        bool f_ok = false;

        for (i = 0; i < num_items; i++) // chrishack - do distance check  (should be trial)
        {
          int type;
          Obj_Value(handle[i], VF_GET, OBJV_I_TYPE, &type);

          if (type != OBJ_NONE && AI_IsObjReachable(me, handle[i])) {
            DoMessage(TXT_GB_ONMYWAY, false, "GBotAcceptOrder1");
            AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, handle[i]);
            AI_SetGoalCircleDist(me, 1, 20.0f);
            AddGetToGoalCommonGoals(me);
            f_ok = true;
            break;
          }
        }

        if (!f_ok) {
          DoMessage(TXT_GB_NOTREACH, true, "GBotConcern1");
        }
      } else if (type == LIT_INTERNAL_ROOM) {
        if (AI_IsDestReachable(me, handle[0])) {
          vector pnt;
          Room_Value(handle[0], VF_GET, RMSV_V_PORTAL_PATH_PNT, &pnt);
          AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, &pnt, handle[0]);
          AI_SetGoalCircleDist(me, 1, 20.0f);
          AddGetToGoalCommonGoals(me);

          DoMessage(TXT_GB_ONMYWAY, false, "GBotAcceptOrder1");
        } else {
          DoMessage(TXT_GB_NOTREACH, true, "GBotConcern1");
        }
      } else if (type == LIT_TRIGGER) {

        int room = Scrpt_GetTriggerRoom(handle[0]);
        int face = Scrpt_GetTriggerFace(handle[0]);

        if (AI_IsDestReachable(me, room)) {
          vector pnt;
          vector normal;
          Room_Value(room, VF_GET, RMSV_V_FACE_CENTER_PNT, &pnt, face);
          Room_Value(room, VF_GET, RMSV_V_FACE_NORMAL, &normal, face);

          pnt += (normal * 5.0f);

          AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, &pnt, room);
          AI_SetGoalCircleDist(me, 1, 20.0f);
          AddGetToGoalCommonGoals(me);

          DoMessage(TXT_GB_ONMYWAY, false, "GBotAcceptOrder1");
        } else {
          DoMessage(TXT_GB_NOTREACH, true, "GBotConcern1");
        }
      }
    } else if (param1 == GBC_RETURN_TO_SHIP) {
      int flags;

      // Turn off friend avoidance
      flags = AIF_AUTO_AVOID_FRIENDS;
      AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

      DoMessage(TXT_GB_ENTERSHIP, false, "GBotAcceptOrder1");
      AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->my_player);
      AI_SetGoalCircleDist(me, 1, -10.0f);
      memory->f_pickup = true;
    } else if (param1 == GBC_ESCORT_SHIP) {
      DoMessage(TXT_GB_ESCORT, false, "GBotAcceptOrder1");
      SetMode(me, GBM_AMBIENT);
    } else if (param1 == GBC_FIND_ROBOT) {

      g_robot = AI_FindObjOfType(me, OBJ_ROBOT, -1, false);

      if (g_robot != OBJECT_HANDLE_NONE) {
        DoMessage(TXT_GB_FINDROBOT, false, "GBotAcceptOrder1");
        AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, g_robot);
        AI_SetGoalCircleDist(me, 1, 30.0f);
        AddGetToGoalCommonGoals(me);
      } else {
        DoMessage(TXT_GB_NOROBOT, true, "GBotConcern1");
      }
    } else if (param1 == GBC_FIND_POWERUP) {

      memory->g_powerup = AI_FindObjOfType(me, OBJ_POWERUP, -1, false);

      if (memory->g_powerup != OBJECT_HANDLE_NONE) {
        DoMessage(TXT_GB_FINDPOWERUP, false, "GBotAcceptOrder1");
        AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->g_powerup);
        AI_SetGoalCircleDist(me, 1, 3.0f);
        AddGetToGoalCommonGoals(me);
      } else {
        DoMessage(TXT_GB_NOPOWERUP, true, "GBotConcern1");
      }
    } else if (param1 == GBC_FIND_CLOSEST_MARKER) {

      memory->g_powerup = AI_FindObjOfType(me, OBJ_MARKER, -1, false, memory->my_player);

      if (memory->g_powerup != OBJECT_HANDLE_NONE) {
        char message[256];
        char marker_message[256];

        Obj_Value(memory->g_powerup, VF_GET, OBJV_PC_MARKER_MESSAGE, marker_message);

        if (strlen(marker_message) > 20) {
          marker_message[17] = '\0';

          while (strlen(marker_message) > 0 && marker_message[strlen(marker_message) - 1] == ' ') {
            marker_message[strlen(marker_message) - 1] = '\0';
          }

          strcat(marker_message, "...");
        }

        snprintf(message, sizeof(message), TXT_GB_GOMARKER, marker_message);
        DoMessage(message, false, "GBotAcceptOrder1");

        AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->g_powerup);
        AI_SetGoalCircleDist(me, 1, 3.0f);
        AddGetToGoalCommonGoals(me);
      } else {
        DoMessage(TXT_GB_NOMARKER, true, "GBotConcern1");
      }
    } else if (param1 >= GBC_FIND_MARKER_0 && param1 <= GBC_FIND_MARKER_7) {
      memory->g_powerup = AI_FindObjOfType(me, OBJ_MARKER, param1 - GBC_FIND_MARKER_0, false, memory->my_player);

      if (memory->g_powerup != OBJECT_HANDLE_NONE) {
        char message[256];
        char marker_message[256];

        Obj_Value(memory->g_powerup, VF_GET, OBJV_PC_MARKER_MESSAGE, marker_message);

        if (/*strlen(marker_message) > 20*/ 0) {
          marker_message[17] = '\0';

          while (strlen(marker_message) > 0 && marker_message[strlen(marker_message) - 1] == ' ') {
            marker_message[strlen(marker_message) - 1] = '\0';
          }

          strcat(marker_message, "...");
        }

        snprintf(message, sizeof(message), TXT_GB_GOMARKER, marker_message);
        DoMessage(message, false, "GBotAcceptOrder1");

        AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->g_powerup);
        AI_SetGoalCircleDist(me, 1, 3.0f);
        AddGetToGoalCommonGoals(me);
      } else {
        DoMessage(TXT_GB_NOMARK, true, "GBotConcern1");
      }
    } else if (param1 == GBC_FIND_THIEF) {
      int id = Obj_FindID("Thief");

      memory->g_powerup = AI_FindObjOfType(me, OBJ_ROBOT, id, false);

      if (memory->g_powerup != OBJECT_HANDLE_NONE) {
        if (rand() > RAND_MAX / 2)
          DoMessage(TXT_GB_FINDTHIEF, false, "GBotAcceptOrder1");
        else
          DoMessage(TXT_GB_FOUNDTHIEF, false, "GBotAcceptOrder1");

        AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->g_powerup);
        AI_SetGoalCircleDist(me, 1, 3.0f);
        AddGetToGoalCommonGoals(me);
      } else {
        DoMessage(TXT_GB_NOTHIEF, true, "GBotConcern1");
      }
    } else if (param1 == GBC_FIND_SPEW) {
      memory->g_powerup = AI_FindObjOfType(me, OBJ_POWERUP, -1, false, memory->my_player);

      if (memory->g_powerup != OBJECT_HANDLE_NONE) {
        DoMessage(TXT_GB_FINDPOWERUPS, false, "GBotAcceptOrder1");
        AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, memory->g_powerup);
        AI_SetGoalCircleDist(me, 1, 3.0f);
        AddGetToGoalCommonGoals(me);
      } else {
        DoMessage(TXT_GB_NOMESSAGE, true, "GBotConcern1");
      }
    } else if (param1 == GBC_NO_CHATTER) {
      memory->flags |= GBF_NO_CHATTER;
      DoMessage(TXT_GB_CHATOFF, true, "GBotConcern1");
    } else if (param1 == GBC_ALLOW_CHATTER) {
      memory->flags &= (~GBF_NO_CHATTER);
      DoMessage(TXT_GB_CHATON, false, "GBotAcceptOrder1");
    } else if (param1 == GBC_FIND_ENERGY_CENTER) {
      roomnum = AI_FindEnergyCenter(me);
      char f_used;
      Room_Value(roomnum, VF_GET, RMV_C_USED, &f_used);

      if (f_used != 0) {
        Room_Value(roomnum, VF_GET, RMSV_V_PATH_PNT, &pos, 1);
        AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, -1, GF_KEEP_AT_COMPLETION | GF_NOTIFIES, &pos, roomnum);
        AI_SetGoalCircleDist(me, 1, 20.0f);
        AddGetToGoalCommonGoals(me);

        DoMessage(TXT_GB_FINDENERGY, false, "GBotAcceptOrder1");
      } else {
        DoMessage(TXT_GB_NOENERGY, true, "GBotConcern1");
      }
    } else if (param1 == GBC_REPAIR_GUIDEBOT) {
      float shields;
      Obj_Value(memory->my_player, VF_GET, OBJV_F_SHIELDS, &shields);

      if (shields >= 5 + 5 * Game_GetDiffLevel()) {
        shields -= 5 + 5 * Game_GetDiffLevel();

        memory->flags &= (~GBF_VERY_DAMAGED);
        Obj_Value(memory->my_player, VF_SET, OBJV_F_SHIELDS, &shields);

        DoMessage(TXT_GB_REPAIRED, false, "GBotAcceptOrder1", true);

        float gb_shields = 250;
        int flags = OF_AI_DEATH;

        Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_FLAGS, &flags);
        Obj_Value(me, VF_SET, OBJV_F_SHIELDS, &gb_shields);

        flags = AIF_AUTO_AVOID_FRIENDS;
        AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
        Obj_Burning(me, 0.0f, 0.0f);
      } else {
        DoMessage(TXT_GB_NOTENSH, true, "GBotConcern1", true);
      }
    } else if (param1 == GBC_EXIT_SHIP) {
      tOSIRISEventInfo ei;
      Obj_CallEvent(me, EVT_USE, &ei);
    } else if (param1 >= GB_POW_STRING_OFFSET && param1 < GB_POW_STRING_OFFSET + NUM_GB_USABLE_POWERUPS) {
      char pow_message[50];
      bool f_do = true;

      if (memory->powerups[param1 - GB_POW_STRING_OFFSET] > 0) {
        switch (param1 - GB_POW_STRING_OFFSET) {
        case GB_POW_FIRE: {
          int room;
          float damage = 0.0f;
          Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &room);
          Room_Value(room, VF_GET, RMV_F_DAMAGE, &damage);
          if (damage == 0.0f) {
            f_do = InitExtinguish(false);
          } else {
            int s_id = Sound_FindId("GBotConcern1");
            Sound_Play2d(memory->my_player, s_id);

            return true;
          }
        } break;

        case GB_POW_ANTIVIRUS: {
          vector pos;
          int room;
          int n_scan;
          int scan_objs[25];
          int n_converted = 0;
          int i;

          Obj_Value(memory->me, VF_GET, OBJV_V_POS, &pos);
          Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &room);

          n_scan = AI_GetNearbyObjs(&pos, room, 500.0f, scan_objs, 25, false, false, false, true);

          for (i = 0; i < n_scan; i++) {
            if (n_converted > 2)
              break;

            if (memory->num_av_robots >= MAX_AV_ROBOTS)
              break;

            if (scan_objs[i] != memory->me) {
              if (AI_IsObjEnemy(memory->me, scan_objs[i])) {
                ray_info ray;
                int flags;
                int fate;
                vector end_pos;

                Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &end_pos);

                flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
                        FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
                fate = FVI_RayCast(me, &pos, &end_pos, room, 1.0f, flags, &ray);

                if (fate == HIT_NONE) {
                  msafe_struct mstruct;
                  int type;

                  Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &mstruct.roomnum);
                  Obj_Value(memory->me, VF_GET, OBJV_V_POS, &mstruct.pos);
                  Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &mstruct.pos2);

                  mstruct.objhandle = memory->me;
                  mstruct.ithandle = scan_objs[i];
                  mstruct.lifetime = 3.5f;
                  mstruct.size = 3.0f;

                  mstruct.interval = 0.2f;
                  mstruct.count = 2;
                  mstruct.index = 4;
                  mstruct.texnum = Scrpt_FindTextureName("FunkyEffectAntiV");
                  mstruct.color = ((128 >> 3) << 10) | ((128 >> 3) << 5) | (128 >> 3);

                  mstruct.state = 0;
                  mstruct.flags = 0;

                  MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING_BOLT, &mstruct);

                  Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &mstruct.roomnum);
                  Obj_Value(memory->me, VF_GET, OBJV_V_POS, &mstruct.pos);
                  Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &mstruct.pos2);

                  int flags = AIF_TEAM_MASK;
                  AI_Value(scan_objs[i], VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
                  flags = AIF_TEAM_REBEL;
                  AI_Value(scan_objs[i], VF_SET_FLAGS, AIV_I_FLAGS, &flags);

                  int target_handle = OBJECT_HANDLE_NONE;
                  AI_Value(scan_objs[i], VF_SET, AIV_I_TARGET_HANDLE, &target_handle);

                  memory->av_revert_time[memory->num_av_robots] = Game_GetTime() + 30.0f;
                  memory->av_robot_list[memory->num_av_robots++] = scan_objs[i];

                  n_converted++;
                }
              }
            }
          }

          f_do = (n_converted > 0);
        } break;

        case GB_POW_WINGNUT: {
          SetMode(me, GBM_GO_WINGNUT);
          f_do = true;
        } break;

        case GB_POW_RTYPE: {
          SetMode(me, GBM_RTYPE);
          f_do = true;
        } break;

        case GB_POW_SPEED: {
          float speed;
          float acc;
          AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &acc);
          AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &speed);

          if (acc == memory->max_acc && speed == memory->max_speed) {
            speed *= 3.0f;
            acc *= 6.0f;

            memory->speed_time_left = 30.0f;

            AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &acc);
            AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);

            f_do = true;
          } else {
            f_do = false;
          }

        } break;
        }

        if (f_do) {
          snprintf(pow_message, sizeof(pow_message), "%s", TXT(gb_pow_text[param1 - GB_POW_STRING_OFFSET]));
          DoMessage(pow_message, false, "GBotAcceptOrder1");
          memory->powerups[param1 - GB_POW_STRING_OFFSET]--;
        } else {
          snprintf(pow_message, sizeof(pow_message), "%s", TXT(gb_pow_not_text[param1 - GB_POW_STRING_OFFSET]));
          DoMessage(pow_message, false, "GBotConcern1");
        }
      } else {
        DoMessage(TXT_GB_DONT_HAVE_POWERUP, false, "GBotConcern1");
      }
    } else if (param1 == GBC_RENAME) {
      char str[80];
      if (strlen((char *)command->ptr) > 0) {
        strncpy(memory->name, (char *)command->ptr, 7);
        memory->name[7] = '\0';
        Player_Value(memory->my_player, VF_SET, PLYV_CS_GUIDEBOTNAME, memory->name);

        snprintf(str, sizeof(str), TXT_GB_NEWNAME, (char *)command->ptr);
        DoMessage(str, true, "GBotAcceptOrder1");
      } else {
        snprintf(str, sizeof(str), TXT_GB_NOWAY, (char *)command->ptr);
        DoMessage(str, true, "GBotConcern1");
      }
    } else if (param1 == GBC_RENAME_SILENT) {
      if (strlen((char *)command->ptr) > 0) {
        strncpy(memory->name, (char *)command->ptr, 7);
        memory->name[7] = '\0';
      }
    } else {
      char str[80];
      snprintf(str, sizeof(str), TXT_GB_STRIKE, param1);
      DoMessage(str, true, "GBotConern1", true);
    }
  } else if (command->action == COM_GET_MENU) {
    int i;
    gb_menu *menu = (gb_menu *)command->ptr;
    int cur_command = 0;

    strcpy(menu->title, TXT_GB_MENUTITLE);

    int gbc_list[NUM_GB_COMMANDS];
    menu->num_commands = MakeCommandList(gbc_list);

    for (i = 0; i < menu->num_commands; i++) {
      int c_index = gbc_list[i];

      if (c_index >= GBC_FIND_MARKER_0 && c_index <= GBC_FIND_MARKER_7) {
        memory->g_powerup = AI_FindObjOfType(me, OBJ_MARKER, c_index - GBC_FIND_MARKER_0, false, memory->my_player);

        char message[256];
        char marker_message[256];

        Obj_Value(memory->g_powerup, VF_GET, OBJV_PC_MARKER_MESSAGE, marker_message);

        if (/*strlen(marker_message) > 12*/ 0) {
          marker_message[11] = '\0';

          while (strlen(marker_message) > 0 && marker_message[strlen(marker_message) - 1] == ' ') {
            marker_message[strlen(marker_message) - 1] = '\0';
          }

          strcat(marker_message, "...");
        }

        snprintf(message, sizeof(message), TXT_GB_FINDMARKMENU, marker_message);
        strcpy(menu->command_text[i], message);
      } else if (c_index >= GBC_FIND_ACTIVE_GOAL_0 && c_index <= GBC_FIND_ACTIVE_GOAL_7) {
        int g_id;
        char message[256];

        LGoal_Value(VF_GET, LGSV_I_ACTIVE_PRIMARY_GOAL, &g_id, c_index - GBC_FIND_ACTIVE_GOAL_0);
        LGoal_Value(VF_GET, LGSV_PC_LOCATION_NAME, &message, g_id);

        if (/* strlen(message) > 19 */ 0) {
          message[18] = '\0';

          while (strlen(message) > 0 && message[strlen(message) - 1] == ' ') {
            message[strlen(message) - 1] = '\0';
          }

          strcat(message, "...");
        }
        snprintf(menu->command_text[i], sizeof(menu->command_text[i]), TXT_GB_GETTO, message);
      } else if (c_index >= GBC_FIND_ACTIVE_SEC_GOAL_0 && c_index <= GBC_FIND_ACTIVE_SEC_GOAL_7) {
        int g_id;
        char message[256];

        LGoal_Value(VF_GET, LGSV_I_ACTIVE_SECONDARY_GOAL, &g_id, c_index - GBC_FIND_ACTIVE_SEC_GOAL_0);
        LGoal_Value(VF_GET, LGSV_PC_LOCATION_NAME, &message, g_id);

        if (/*strlen(message) > 19*/ 0) {
          message[18] = '\0';

          while (strlen(message) > 0 && message[strlen(message) - 1] == ' ') {
            message[strlen(message) - 1] = '\0';
          }

          strcat(message, "...");
        }
        snprintf(menu->command_text[i], sizeof(menu->command_text[i]), TXT_GB_GETTO, message);
      } else
        strcpy(menu->command_text[i], TXT(gb_command_text[gbc_list[i]]));

      if (gbc_list[i] == GBC_REPAIR_GUIDEBOT) {
        char message[256];
        snprintf(message, sizeof(message), TXT_GB_SHIELDAMOUNT, 5 + 5 * Game_GetDiffLevel());
        strcat(menu->command_text[i], message);
      }

      menu->command_id[i] = gbc_list[i];
      menu->command_type[i] = GBCT_EXIT_IMMEDIATELY;

      if (gbc_list[i] == GBC_RENAME) {
        menu->command_type[i] = GBCT_STRING_DIALOG;
        strcpy(menu->dialog_text[i], TXT_GB_ENTERNAME);
      }
    }
  } else if (command->action == COM_POWERUP_NOTIFY) {
    SetSubMode(me, GBSM_GET_POWERUP, it);
  } else if (command->action == COM_POWERUP_PICKUP) {
    int type = command->index;

    if (type >= 0 && type <= 5) {
      int s_id = Sound_FindId("Powerup pickup");
      Sound_Play3d(me, s_id);

      if (type == GB_POW_SPEED) {
        float speed;
        float acc;
        AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &acc);
        AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &speed);

        if (acc == memory->max_acc && speed == memory->max_speed) {
          speed *= 3.0f;
          acc *= 6.0f;

          memory->speed_time_left = 30.0f;

          AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &acc);
          AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);
        }
      } else {
        memory->powerups[type]++;
      }

      msafe_struct mo;
      mo.objhandle = it;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);

      DoMessage(TXT(gb_pow_pickup_text[type]), true, "GBotExcited1");
      SetSubMode(me, GBSM_NONE);
    }
  }

  return true;
}

void GuideBot::DoCollide(int me, tOSIRISEVTCOLLIDE *evt_collide) {
  int obj_type;
  int its_parent;
  float rand_val;

  int it_type;
  Obj_Value(evt_collide->it_handle, VF_GET, OBJV_I_TYPE, &it_type);

  rand_val = (float)rand() / (float)RAND_MAX;

  // Add a buddy bot to you inventory  :)
  if (memory->f_pickup == true) {
    if (it_type == OBJ_PLAYER) {
      uint16_t id;
      Obj_Value(evt_collide->it_handle, VF_GET, OBJV_US_ID, &id);

      if (id == memory->mp_slot) {
        SetMode(me, GBM_ENTER_SHIP);
      }
    }
  } else {
    // Run back to the player when you get hit
    if (it_type == OBJ_WEAPON) {
      // 30% of the time - and not within 5 seconds - the buddy will come
      // back to the player for protection

      Obj_Value(evt_collide->it_handle, VF_GET, OBJV_I_PARENT_HANDLE, &its_parent);

      if (its_parent == memory->my_player) {
        if (rand_val > 0.8f) {
          DoMessage(TXT_GBHIT1, false, "GBotConcern1");
        } else if (rand_val > 0.6) {
          DoMessage(TXT_GBHIT2, false, "GBotConcern1");
        } else if (rand_val > 0.4) {
          DoMessage(TXT_GBHIT3, false, "GBotConcern1");
        }
      } else if (memory->last_retreat_time + 5.0 < Game_GetTime())
        ;
      {
        if (rand_val > 0.7) {
          AI_AddGoal(me, AIG_GET_TO_OBJ, 2, 1.0f, -1, 0, memory->my_player);
          AI_SetGoalCircleDist(me, 2, 40.0f);

          memory->last_retreat_time = Game_GetTime();

          DoMessage(TXT_GBHIT4, true, "GBotConcern1");
        } else {
          DoMessage(TXT_GBHIT5, true, "GBotConcern1");
        }
      }
    }
  }
}

bool GuideBot::DoUse(int me) {
  int p_handle;
  int sad_sound;
  int buddy_handle;

  // NOTE: Use is done on the inventory item and/or the real guidebot
  //       don't set and guidebot global variables in here.  Do it in the
  //       EVT_CREATE in the f_valid block

  gb_com command;

  Obj_Value(me, VF_GET, OBJV_I_PARENT_HANDLE, &p_handle);

  if (p_handle == OBJECT_HANDLE_NONE) {
    p_handle = memory->my_player;
  } else {
    memory->my_player = p_handle;
  }

  mprintf(0, "1 Player %d\n", p_handle);
  mprintf(0, "2 Player %d\n", memory->my_player);

  Player_Value(p_handle, VF_GET, PLYV_I_BUDDY_HANDLE, &buddy_handle);

  command.action = COM_REINIT;
  tOSIRISEventInfo ei;
  ei.extra_info = (void *)&command;
  ei.evt_ai_notify.notify_type = AIN_USER_DEFINED;

  return Obj_CallEvent(buddy_handle, EVT_AI_NOTIFY, &ei);
}

bool GuideBot::DoInit(int me, bool f_reinit) {
  vector fvec;
  vector vel;
  bool f_valid;
  matrix orient;
  vector pos;
  int room;
  int i;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(guidebot_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  if (!f_reinit) {
    memory = (guidebot_data *)Scrpt_MemAlloc(&ch);
    memory->flags = 0;

    AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->max_acc);
    AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->max_speed);

    Obj_Value(me, VF_GET, OBJV_I_PARENT_HANDLE, &memory->my_player);
    Obj_Value(memory->my_player, VF_GET, OBJV_US_ID, &memory->mp_slot);

    Player_Value(memory->my_player, VF_GET, PLYV_CS_GUIDEBOTNAME, memory->name);

    // Sets up my invisible helper
    int proom;
    vector ppos;
    matrix porient;

    Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &proom);
    Obj_Value(memory->my_player, VF_GET, OBJV_V_POS, &ppos);
    Obj_Value(memory->my_player, VF_GET, OBJV_M_ORIENT, &porient);

    ppos += porient.fvec * 10.0f;

    memory->amb_camera_handle = Obj_Create(OBJ_POWERUP, Obj_FindID("Invisiblepowerup"), proom, &ppos, &porient, me);
    msafe_struct mstruct;
    mstruct.objhandle = memory->amb_camera_handle;
    MSafe_CallFunction(MSAFE_OBJECT_NO_RENDER, &mstruct);

    // Three fire extinguishers per level
    memory->powerups[0] = 3;
    memory->powerups[1] = 0;
    memory->powerups[2] = 0;
    memory->powerups[3] = 0;
    memory->powerups[4] = 0;

    for (i = 0; i < NUM_GB_SOUNDS; i++) {
      memory->sounds[i] = -1;
    }

    memory->me = me;

    memory->mode = GBM_IN_SHIP;
    AI_SetType(me, AIT_AIS);

    memory->powerup_ids[0] = Obj_FindID("Buddyextinguisher");
    memory->powerup_ids[1] = Obj_FindID("buddywingnut");
    memory->powerup_ids[2] = Obj_FindID("buddycontrol");
    memory->powerup_ids[3] = Obj_FindID("buddyassist");
    memory->powerup_ids[4] = Obj_FindID("buddyantivirus");
    memory->powerup_ids[5] = Obj_FindID("buddyspeed");

    memory->num_av_robots = 0;

    memory->last_sound_time = Game_GetTime();
    memory->last_at_goal_time = Game_GetTime();

    memory->camera_obj = OBJECT_HANDLE_NONE;
    memory->speed_time_left = 0.0f;
  } else {
    // If too damaged to exit
    if (memory->flags & GBF_VERY_DAMAGED) {
      DoMessage(TXT_GBDAMAGED, true, "GBotConcern1", true);
      return false;
    }

    SetMode(me, GBM_BIRTH);
    SetSubMode(me, GBSM_NONE);
  }

  return true;
}

bool GuideBot::DoNotify(int me, tOSIRISEventInfo *data) {
  tOSIRISEVTAINOTIFY *notify = &data->evt_ai_notify;

  if (notify->notify_type == AIN_USER_DEFINED) {
    return DoExternalCommands(me, (gb_com *)data->extra_info, data->evt_ai_notify.it_handle);
  } else if (notify->notify_type == AIN_WHIT_OBJECT) {
    int type;
    Obj_Value(notify->it_handle, VF_GET, OBJV_I_TYPE, &type);

    if (type == OBJ_PLAYER) {
      if (notify->it_handle == memory->my_player) {
        DoMessage(TXT_GB_OOPS, true, "GBotConcern1");
      }
    } else if (type == OBJ_ROBOT) {
      // 35% of the time, the buddy is happy enough to say something when
      // he hits a robot
      if (rand() > static_cast<float>(RAND_MAX) * 0.65f) {
        DoMessage(TXT_GB_SHOOTROBOT, false, "GBotAcceptOrder1");
      }
    }
  } else if (IsGoalFinishedNotify(
                 notify->notify_type)) // Goal complete -- chrishack -- print something else on error cases
  {
    mprintf(0, "Goal %d done\n", notify->goal_num);

    if (notify->goal_num == 1) {
      if (memory->last_at_goal_time + 1.0f > Game_GetTime()) {
        gb_com command;

        command.action = COM_DO_ACTION;
        command.index = GBC_ESCORT_SHIP;
        DoExternalCommands(me, &command, memory->my_player);
        return true;
      }

      DoMessage(TXT_GB_GOAL1, false, "GBotAcceptOrder1");
      memory->last_at_goal_time = Game_GetTime();

      AI_AddGoal(me, AIG_GET_TO_OBJ, 2, 1.0, GB_GUID_RETURNED_TO_PLAYER, GF_NOTIFIES, memory->my_player);
      AI_SetGoalCircleDist(me, 2, 30.0f);
    } else if (notify->goal_num == 2 && notify->goal_uid == GB_GUID_RETURNED_TO_PLAYER) {
      mprintf(0, "HERERWERSEFSDF\n");
      bool f_used;
      AI_GoalValue(me, 1, VF_GET, AIGV_B_USED, &f_used);
      if (f_used) {
        mprintf(0, "FUCKME\n");

        if ((rand() % 100) > 50)
          DoMessage(TXT_GB_GOAL2, false, "GBotGreetB1");
        else
          DoMessage(TXT_GB_GOAL3, false, "GBotGreetB1");
      }

      memory->time_till_next_flare = 3.0f + ((float)rand() / (float)RAND_MAX);
      memory->return_time = Game_GetTime();
    }
  } else if (notify->notify_type == AIN_SCRIPTED_ORIENT) {
    matrix orient;
    Obj_Value(memory->my_player, VF_GET, OBJV_M_ORIENT, &orient);

    AI_TurnTowardsVectors(me, &orient.fvec, &orient.uvec);
  }

  return true;
}

void GuideBot::DoPowerupCheck(int me) {
  if (memory->next_powerup_check_time <= Game_GetTime() && memory->sub_mode == GBSM_NONE) {
    vector pos;
    int room;
    int scan_objs[80];
    int n_scan;
    int i;

    memory->next_powerup_check_time = Game_GetTime() + 2.0f + ((float)rand() / (float)RAND_MAX);

    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

    n_scan = AI_GetNearbyObjs(&pos, room, 200.0f, scan_objs, 80, false, true, false, true);

    for (i = 0; i < n_scan; i++) {
      int type;
      int16_t id;
      Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);
      Obj_Value(scan_objs[i], VF_GET, OBJV_US_ID, &id);

      if (type == OBJ_POWERUP) {
        bool f_for_me = false;
        int j;

        for (j = 0; j < 6; j++) {
          if (memory->powerup_ids[j] == id) {
            f_for_me = true;
            break;
          }
        }

        if (f_for_me) {
          tOSIRISEventInfo data;
          gb_com command;

          command.action = COM_POWERUP_NOTIFY;

          DoExternalCommands(me, &command, scan_objs[i]);

          break;
        }
      }
    }
  }
}

void GuideBot::DoFrame(int me) {
  int dir_index;
  int flags;
  float anim;
  float last_mode_time;

  int proom;
  vector ppos;
  matrix porient;
  Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &proom);
  Obj_Value(memory->my_player, VF_GET, OBJV_V_POS, &ppos);
  Obj_Value(memory->my_player, VF_GET, OBJV_M_ORIENT, &porient);

  ppos += porient.fvec * 40.0f;
  ppos -= porient.uvec * 10.0f;

  Obj_Value(memory->amb_camera_handle, VF_SET, OBJV_I_ROOMNUM, &proom);
  Obj_Value(memory->amb_camera_handle, VF_SET, OBJV_V_POS, &ppos);
  Obj_Value(memory->amb_camera_handle, VF_SET, OBJV_M_ORIENT, &porient);

  if (memory->mode == GBM_AMBIENT)
    DoPowerupCheck(me);

  if (memory->flags & GBF_WANTING_TO_ENTER_PDEAD) {
    int flags;
    Player_Value(memory->my_player, VF_GET, PLYV_I_FLAGS, &flags);
    if (!(flags & PLAYER_FLAGS_DEAD)) {
      SetMode(me, GBM_RESPAWN_ENTER_SHIP);
    }
  } else {
    int flags;
    Player_Value(memory->my_player, VF_GET, PLYV_I_FLAGS, &flags);
    if (flags & PLAYER_FLAGS_DEAD) {
      Obj_Burning(me, 0.0f, 0.0f);
      memory->flags |= GBF_WANTING_TO_ENTER_PDEAD;
    }
  }

  if (memory->speed_time_left > 0.0f) {
    if (memory->speed_time_left > 15.0f && memory->speed_time_left - Game_GetFrameTime() <= 15.0f) {
      DoMessage(TXT_GB_POW_ACC_ALMOST_DONE, true, "GBotExcited1");
    }

    memory->speed_time_left -= Game_GetFrameTime();
    if (memory->speed_time_left <= 0.0f) {
      memory->speed_time_left = 0.0f;

      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->max_speed);
      AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->max_acc);

      DoMessage(TXT_GB_POW_DEPLETED, true, "GBotPlayerKillBot1");
    }
  }

  if (memory->mode == GBM_AMBIENT && Obj_IsEffect(memory->my_player, EF_NAPALMED)) {
    int room;
    float damage = 0.0f;
    Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &room);
    Room_Value(room, VF_GET, RMV_F_DAMAGE, &damage);

    if (damage == 0.0f) {
      InitExtinguish(true);
    }
  }

  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &anim);
  if (anim < 0 || anim > 12) {
    memory->flags |= GBF_IN_CUSTOM_ANIM;
  } else {
    memory->flags &= ~GBF_IN_CUSTOM_ANIM;
  }

  Obj_Value(me, VF_GET, OBJV_I_FLAGS, &flags);

  last_mode_time = memory->mode_time;
  memory->mode_time += Game_GetFrameTime();

  if (memory->mode == GBM_ON_FIRE) {
  } else if ((flags & OF_AI_DEATH)) {
    SetMode(me, GBM_ON_FIRE);
  } else if (memory->mode == GBM_BIRTH) {
    if (memory->mode_time > 1.2f) {
      SetMode(me, GBM_AMBIENT);
    }

    return;
  } else if (memory->mode == GBM_EXTINGUISH) {
    if (!(memory->flags & GBF_IN_CUSTOM_ANIM) && last_mode_time < 0.5f && memory->mode_time >= 0.5f) {
      Obj_SetCustomAnim(me, 12.0f, 23.0f, 1.0f, 0);
    }

    if (Game_GetTime() > memory->next_ambient_time) {
      memory->next_ambient_time = Game_GetTime() + 0.6f;

      int dir_index = rand() % 6;
      AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_ORIENT_GOAL_OBJ | GF_KEEP_AT_COMPLETION,
                 memory->extinguish_obj_list[0], dir_index);
      AI_SetGoalCircleDist(me, 0, 20.0);
    }

    if (memory->mode_time < 25.0f) {
      if (memory->last_anim <= 18 && anim > 18) {
        Obj_SetCustomAnim(me, 23.0f, 33.0f, 1.5f, AIAF_LOOPING);
        memory->flags |= GBF_WANT_TO_EXTINGUISH;
      }

      if ((memory->flags & GBF_WANT_TO_EXTINGUISH) && anim >= 23 && anim <= 33) {
        int s_id = Sound_FindId("GBotEuphoria1");
        Sound_Play3d(me, s_id);

        msafe_struct mstruct;

        mstruct.random = 21;
        mstruct.is_real = 0;
        mstruct.objhandle = me;
        mstruct.gunpoint = 1;
        mstruct.effect_type = MED_SMOKE_INDEX;
        mstruct.phys_info = 0;
        mstruct.drag = .001f;
        mstruct.mass = .001f;
        mstruct.interval = .025f;
        mstruct.longevity = 100000.0f;
        mstruct.lifetime = 1.0;
        mstruct.size = 4.2f;
        mstruct.speed = 120.0;

        MSafe_CallFunction(MSAFE_OBJECT_START_SPEW, &mstruct);

        memory->extinguish_spew_id = mstruct.id;

        memory->flags &= ~GBF_WANT_TO_EXTINGUISH;
        memory->flags |= GBF_EXTINGUISHING;
      }

      if (memory->flags | GBF_EXTINGUISHING) {
        int flags;
        vector me_pos;
        vector it_pos;
        matrix orient;

        AI_GoalValue(me, 0, VF_GET, AIGV_I_STATUS_REG, &flags);
        Obj_Value(me, VF_GET, OBJV_V_POS, &me_pos);
        Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);
        Obj_Value(memory->extinguish_obj_list[0], VF_GET, OBJV_V_POS, &it_pos);

        vector dir_to_goal = it_pos - me_pos;
        vm_VectorNormalize(&dir_to_goal);

        if ((flags & AISR_CIRCLE_DIST) && (dir_to_goal * orient.fvec > 0.4717f) && anim >= 23 && anim <= 33)
          memory->extinguish_obj_time += Game_GetFrameTime();

        if (memory->extinguish_obj_time > 1.5f) {
          // Turns off fire if being sprayed for 2.5 seconds
          Obj_Burning(memory->extinguish_obj_list[0], 0.0f, 0.0f);

          if (memory->num_extinguish_objs > 1) {
            int i;
            for (i = 0; i < memory->num_extinguish_objs - 1; i++) {
              memory->extinguish_obj_list[i] = memory->extinguish_obj_list[i + 1];
            }
            memory->num_extinguish_objs--;

            SetMode(me, GBM_EXTINGUISH);
          } else {
            SetMode(me, GBM_AMBIENT);
          }
        }
      }
    } else {
      SetMode(me, GBM_AMBIENT);
    }
  } else if (memory->mode == GBM_RTYPE) {
    int room;
    vector pos;
    matrix orient;

    Obj_Value(memory->my_player, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(memory->my_player, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(memory->my_player, VF_GET, OBJV_M_ORIENT, &orient);

    pos += orient.fvec * 3.0f;
    pos -= orient.uvec * 10.0f;

    Obj_Value(memory->camera_obj, VF_SET, OBJV_I_ROOMNUM, &room);
    Obj_Value(memory->camera_obj, VF_SET, OBJV_V_POS, &pos);
    Obj_Value(memory->camera_obj, VF_SET, OBJV_M_ORIENT, &orient);

    if (memory->mode_time < 15.0f && memory->mode_time + Game_GetFrameTime() >= 15.0f) {
      DoMessage(TXT_GB_FIFTEEN_SEC_TO_GO, true, "GBotExcited1");
    }

    if (memory->mode_time > 30.0) {
      DoMessage(TXT_GB_POW_DEPLETED, true, "GBotPlayerKillBot1");
      SetMode(me, GBM_AMBIENT);
    }
  } else if (memory->mode == GBM_GO_WINGNUT) {
    if (Game_GetTime() > memory->next_ambient_time) {
      memory->next_ambient_time = Game_GetTime() + 1.0f;

      // In general, Turn on friend avoidance
      int flags = AIF_AUTO_AVOID_FRIENDS;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      int dir_index = rand() % 6;
      float interval = 2.0f;
      AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 3, 1.0f, -1, GF_KEEP_AT_COMPLETION, memory->my_player, dir_index);
      AI_GoalAddEnabler(me, 3, AIE_GT_LAST_SEE_TARGET_INTERVAL, 1.0f, 0.0f, &interval);

      AI_SetGoalCircleDist(me, 3, 27.0);
    }

    if (memory->mode_time < 15.0f && memory->mode_time + Game_GetFrameTime() >= 15.0f) {
      DoMessage(TXT_GB_FIFTEEN_SEC_TO_GO, true, "GBotExcited1");
    }

    if (memory->mode_time > 30.0) {
      DoMessage(TXT_GB_POW_DEPLETED, true, "GBotPlayerKillBot1");
      SetMode(me, GBM_AMBIENT);
    }
  } else {
    if (memory->sounds[GBS_AMBIENT] == -1) {
      int s_index = Sound_FindId("GBotEngineB1");
      memory->sounds[GBS_AMBIENT] = Sound_Play3d(me, s_index);
    }

    if (memory->mode == GBM_AMBIENT) {
      if (Game_GetTime() > memory->next_ambient_time) {
        ReInitAmbient(me);
      }
    }

    // Allow the buddy to collide with his player after 3 seconds
    if (memory->f_parented == true) {
      float time;
      Obj_Value(me, VF_GET, OBJV_F_CREATION_TIME, &time);

      if (Game_GetTime() - time > 3.0f) {
        int parent = OBJECT_HANDLE_NONE;

        Obj_Value(me, VF_SET, OBJV_I_PARENT_HANDLE, &parent);
        memory->f_parented = false;
      }
    }

    memory->time_till_next_pvis_check -= Game_GetFrameTime();
    if (memory->time_till_next_pvis_check <= 0.0f) {
      vector start_pos;
      vector end_pos;

      Obj_Value(me, VF_GET, OBJV_V_POS, &start_pos);
      Obj_Value(memory->my_player, VF_GET, OBJV_V_POS, &end_pos);

      memory->time_till_next_pvis_check = 0.5f + (0.5f * ((float)rand() / (float)RAND_MAX));

      if (vm_VectorDistance(&start_pos, &end_pos) < 200.0f) {
        int start_room;
        ray_info ray;

        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &start_room);

        flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
                FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
        int fate = FVI_RayCast(me, &start_pos, &end_pos, start_room, 0.0f, flags, &ray);

        if (fate == HIT_NONE) {
          memory->return_time = Game_GetTime();
        }
      }
      //			mprintf(0, "Vis check %s\n", (fate==HIT_NONE)?"passed":"failed");
      //			mprintf(0, "Submode %d\n", memory->sub_mode);
    }

    if (memory->mode == GBM_AMBIENT) {
      memory->time_till_next_flare -= Game_GetFrameTime();

      if (memory->time_till_next_flare <= 0.0f) {
        memory->time_till_next_flare = 3.0f + ((float)rand() / (float)RAND_MAX);

        bool f_used;
        AI_GoalValue(me, 1, VF_GET, AIGV_B_USED, &f_used);
        if (f_used) {
          AI_GoalValue(me, 2, VF_GET, AIGV_B_USED, &f_used);
          if (!f_used) {
            AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &f_used);
            if (!f_used) {
              msafe_struct mstruct;

              mstruct.objhandle = me;

              uint16_t id;
              Obj_Value(me, VF_GET, OBJV_US_ID, &id);

              if (Obj_FindID("GuideBot") == id) {
                mstruct.index = Wpn_FindID("Yellow flare");
              } else {
                mstruct.index = Wpn_FindID("GreenFlare");
              }

              if (mstruct.index != -1) {
                mstruct.gunpoint = -1;
                Sound_Play3d(me, Sound_FindId("Flare"));

                MSafe_CallFunction(MSAFE_OBJECT_FIRE_WEAPON, &mstruct);
              }
            }
          }
        }
      }
    }

    // Makes the buddy stay pretty close to his player
    if (memory->return_time + 2.5 < Game_GetTime()) {
      if (Obj_GetObjDist(me, memory->my_player, true) > 10.0f && memory->sub_mode == GBSM_NONE) {
        DoMessage(TXT_GB_COMINGBACK, false, "GBotAcceptOrder1");

        AI_AddGoal(me, AIG_GET_TO_OBJ, 2, 1.0f, GB_GUID_RETURNED_TO_PLAYER, GF_NOTIFIES, memory->my_player);
        AI_SetGoalCircleDist(me, 2, 30.0f);
      }

      memory->return_time = Game_GetTime();
    }
  }

  memory->last_anim = anim;
}

int16_t GuideBot::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    return (DoInit(data->me_handle, false) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_INTERVAL: {
    int i;

    while (memory->num_av_robots > 0 && memory->av_revert_time[0] <= Game_GetTime()) {

      int flags = AIF_TEAM_MASK;
      AI_Value(memory->av_robot_list[0], VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
      flags = AIF_TEAM_PTMC;
      AI_Value(memory->av_robot_list[0], VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      int target_handle = OBJECT_HANDLE_NONE;
      AI_Value(memory->av_robot_list[0], VF_SET, AIV_I_TARGET_HANDLE, &target_handle);

      for (i = 1; i < memory->num_av_robots; i++) {
        memory->av_robot_list[i - 1] = memory->av_robot_list[i];
      }

      memory->num_av_robots--;
    }
  } break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_COLLIDE:
    DoCollide(data->me_handle, &data->evt_collide);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_USE:
    return (DoUse(data->me_handle) != 0) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY:
    if (memory->camera_obj != OBJECT_HANDLE_NONE) {
      msafe_struct mo;
      mo.objhandle = memory->camera_obj;
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);

      memory->camera_obj = OBJECT_HANDLE_NONE;
    }
    break;
  case EVT_MEMRESTORE: {
    memory = (guidebot_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Thief
//---------------

void Thief::DoAttack(int me, int it) {}

bool Thief::DoSteal(int me, int it, int attempt_num, bool f_last_success) {
  int max_tries = numThiefableItems;
  float gen_perc, perc_chance;
  ;
  int i;
  int count_max, count_num;
  bool *attempted_steals;

  attempted_steals = (bool *)malloc(numThiefableItems * sizeof(bool));
  if (!attempted_steals)
    return false;

  float ftime = Game_GetFrameTime();
  if (ftime == 0)
    ftime = 1.0f;
  srand(Game_GetTime() / ftime);

  for (i = 0; i < numThiefableItems; i++) {
    attempted_steals[i] = false;
  }

  while (max_tries--) {
    i = rand() % numThiefableItems;
    gen_perc = ((float)rand()) / ((float)(RAND_MAX));

    perc_chance = (attempt_num == 1) ? ThiefableItems[i].attempt_one
                  : (f_last_success) ? ThiefableItems[i].attempt_two
                                     : ThiefableItems[i].attempt_two_no_one;

    if (attempted_steals[i]) {
      // we already tried this one, try another
      max_tries++;
      continue;
    }

    attempted_steals[i] = true;

    if (gen_perc <= perc_chance) {
      // check to see if we have the index, if so, take it!
      switch (ThiefableItems[i].type) {
      case THIEFABLEITEM_PRIMARY:
      case THIEFABLEITEM_SECONDARY:
        count_max = MAX_STOLEN_WEAPONS;
        count_num = memory->num_stolen_weapons;
        break;
      case THIEFABLEITEM_ACCESSORY:
        count_max = MAX_STOLEN_INV;
        count_num = memory->num_stolen_inv;
        break;
      default:
        mprintf(0, "THIEF: INVALID THIEFABLE TYPE!\n");
        count_max = 0;
        count_num = 0;
        break;
      }

      if (count_num >= count_max) {
        mprintf(0, "THIEF: no mo' room\n");
        continue; // we have no more room
      }

      // mprintf(0,"THIEF: Checking %s\n",TXT(ThiefableItems[i].name_idx));

      bool can_take = false;
      int amount = 0;
      char message[256];

      switch (ThiefableItems[i].type) {
      case THIEFABLEITEM_PRIMARY:
        // check to see if we can steal the primary
        Player_Value(it, VF_GET, PLYSV_I_WEAPON, &amount, ThiefableItems[i].index);
        if (ThiefableItems[i].index != 0 && amount) {
          can_take = true;
          snprintf(message, sizeof(message), TXT_THIEFSTEAL, TXT(ThiefableItems[i].name_idx));
        }
        break;

      case THIEFABLEITEM_SECONDARY:
        // check to see if we can steal the secondary
        if (attempt_num <= 1 || (!f_last_success)) {
          Player_Value(it, VF_GET, PLYSV_I_WEAPON, &amount, ThiefableItems[i].index);

          if (amount) {
            int max;

            if (ThiefableItems[i].index > 14) {
              // 2nd selection group (black shark, etc)
              max = (19 - ThiefableItems[i].index) / 2.5f + 1;
            } else {
              // 1st selection group (mega, etc)
              max = (14 - ThiefableItems[i].index) / 2.5f + 1;
            }

            int new_amount = (rand() / (float)(RAND_MAX + 1)) * max + 1;

            if (new_amount < amount)
              amount = new_amount;

            can_take = true;

            if (amount == 1) {
              snprintf(message, sizeof(message), TXT_THIEFSTEAL1, TXT(ThiefableItems[i].name_idx));
            } else {
              snprintf(message, sizeof(message), TXT_THIEFSTEAL2, amount, TXT(ThiefableItems[i].name_idx));
            }
          }
        }

        break;

      case THIEFABLEITEM_ACCESSORY:
        // check to see if we can steal the accessory
        Player_Value(it, VF_GET, PLYV_B_THIEF_PLAYERHASITEM, &can_take, ThiefableItems[i].index);
        amount = 1;

        if (can_take && ThiefableItems[i].index == THIEFITEM_AUTOMAP) {
          // make sure the thief hasn't taken your automap already
          for (int k = 0; k < memory->num_stolen_inv; k++) {
            if (memory->stolen_inv[k].id == THIEFITEM_AUTOMAP) {
              // he has already taken an automap
              can_take = false;
              break;
            }
          }
        }

        if (can_take) {
          snprintf(message, sizeof(message), TXT_THIEFSTEAL, TXT(ThiefableItems[i].name_idx));
        }
        break;
      }

      if (!can_take)
        continue;

      mprintf(0, "THIEF: Taking %s\n", TXT(ThiefableItems[i].name_idx));

      Player_AddHudMessage(it, message);
      if (rand() % 50) {
        Sound_Play3d(me, Sound_FindId("RbtThiefHehHehHeh"));
      } else {
        Sound_Play3d(me, Sound_FindId("RbtThiefLaugh"));
      }

      switch (ThiefableItems[i].type) {
      case THIEFABLEITEM_PRIMARY:
      case THIEFABLEITEM_SECONDARY:
        memory->stolen_weapons[memory->num_stolen_weapons].index = ThiefableItems[i].index;
        memory->stolen_weapons[memory->num_stolen_weapons].owner = it;
        memory->stolen_weapons[memory->num_stolen_weapons].amount = amount;
        memory->num_stolen_weapons++;

        if (ThiefableItems[i].type == THIEFABLEITEM_PRIMARY) {
          amount = 0;
        } else {
          amount *= -1;
        }

        Player_Value(it, VF_SET, PLYSV_I_WEAPON, &amount, ThiefableItems[i].index);

        break;
      case THIEFABLEITEM_ACCESSORY:
        memory->stolen_inv[memory->num_stolen_inv].id = ThiefableItems[i].index;
        memory->stolen_inv[memory->num_stolen_inv].owner = it;
        memory->num_stolen_inv++;

        Player_Value(it, VF_SET, PLYV_I_THIEF_STEALPLAYERITEM, NULL, ThiefableItems[i].index);
        break;
      }

      free(attempted_steals);
      return true;
    }
  }

  mprintf(0, "THIEF: Not taking anything\n");
  free(attempted_steals);
  return false; // we didn't take anything this try
}

void Thief::DoKidnap(int me, int it) {
  if (memory->num_stolen_objs < MAX_STOLEN_OBJS) {
    Obj_Ghost(it, true);
    memory->stolen_objs[memory->num_stolen_objs++] = it;
  }
}

void Thief::SetSubMode(int me, int submode) {
  if (submode == memory->last_special_sub_mode)
    return;

  if (memory->sub_mode == THIEF_SUB_GET_POWERUP) {
    // Make sure we reset the Alert animation
    Obj_SetCustomAnim(me, 0.0f, 6.0f, 1.0f, AIAF_NOTIFY, -1, AS_ALERT);
  }

  if (submode == THIEF_SUB_GET_POWERUP && (memory->flags & THIEF_F_GOT_POWERUP))
    return;

  if (submode == THIEF_SUB_DROP_POWERUP && !(memory->flags & THIEF_F_GOT_POWERUP))
    return;

  // CHRISHACK - we might want to make sure the thief only does some of stuff during
  if (submode != THIEF_SUB_NONE && submode != THIEF_SUB_CLOAK) {
    float time;
    float last_hear_target_time;
    AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &time);
    AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &last_hear_target_time);

    if (Game_GetTime() > time + 2.0f && Game_GetTime() > last_hear_target_time + 2.0f) {
      return;
    }
  }

  switch (submode) {
  case THIEF_SUB_NONE: {
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, false);
    memory->next_test_time = Game_GetTime() + 10.0f + (float)rand() * (1.0f / (float)RAND_MAX) * 10.0f;
  } break;
  case THIEF_SUB_SUMMON: {
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, false);
    Obj_SetCustomAnim(me, 12.0f, 19.0f, 0.8f, 0, -1, -1);
  } break;
  case THIEF_SUB_CLOAK: {
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, true);
    Obj_SetCustomAnim(me, 50.0f, 64.0f, 3.5f, AIAF_NOTIFY, -1, AS_ALERT);
  } break;
  case THIEF_SUB_THROW_ITEM: {
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, true);
    Obj_SetCustomAnim(me, 29.0f, 50.0f, 3.5f, AIAF_NOTIFY, -1, AS_ALERT);
  } break;
  case THIEF_SUB_GET_POWERUP: {
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, false);
    Obj_SetCustomAnim(me, 29.0f, 29.0f, 0.1f, AIAF_LOOPING);
  } break;
  case THIEF_SUB_DROP_POWERUP: {
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, true);
    Obj_SetCustomAnim(me, 145.0f, 160.0f, 2.3f, AIAF_NOTIFY, -1, AS_ALERT);
  } break;
  }

  if (submode != THIEF_SUB_NONE) {
    memory->last_special_sub_mode = submode;
  }

  memory->sub_mode_time = 0.0f;
  memory->sub_mode = submode;
}

void Thief::DoSubModeFrame(int me) {
  float anim_frame;
  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &anim_frame);

  msafe_struct m;
  m.objhandle = me;

  switch (memory->sub_mode) {
  case THIEF_SUB_NONE: {
    if (Game_GetTime() > memory->next_test_time) {
      int r_val = (rand() % 5) + 1;
      SetSubMode(me, r_val);

      // In case above failed, make sure there is a time gap between submode checks
      memory->next_test_time = Game_GetTime() + 10.0f + (float)rand() * (1.0f / (float)RAND_MAX) * 10.0f;
    }
  } break;
  case THIEF_SUB_SUMMON: {

    if (anim_frame >= 12.0f && anim_frame < 19.0f) {
      Obj_SetCustomAnim(me, 19.0f, 23.0f, 0.8f, AIAF_LOOPING);
    }

    if (anim_frame > 19.0f && anim_frame < 23.0f) {
      if (memory->last_summon_time + 0.25f <= Game_GetTime()) {
        memory->last_summon_time = Game_GetTime();

        // Chrishack - do summon stuff here
      }
    }

    if (memory->sub_mode_time > 6.0f && anim_frame >= 19.0f && anim_frame <= 23.0f) {
      Obj_SetCustomAnim(me, 23.0f, 29.0f, 0.8f, AIAF_NOTIFY, -1, AS_ALERT);
      SetSubMode(me, THIEF_SUB_NONE);
    }

  } break;
  case THIEF_SUB_CLOAK: {
    if (anim_frame > 61.0f && memory->last_frame <= 61.0f) {
      m.lifetime = 15.0f;
      m.state = 1;

      MSafe_CallFunction(MSAFE_OBJECT_CLOAK, &m);

      AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, false);
    }
  } break;
  case THIEF_SUB_THROW_ITEM: {
    if (anim_frame > 41.0f && memory->last_frame <= 41.0f) {
      memory->bomb_handle = CreateAndAttach(me, "PTMCSeeker", OBJ_ROBOT, 1, 0, true, true);
    }

    if (anim_frame > 45.0f && memory->last_frame <= 45.0f) {
      matrix orient;
      Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);
      vector velocity = orient.fvec * 50.0f;

      Obj_UnattachFromParent(memory->bomb_handle);

      Obj_Value(memory->bomb_handle, VF_SET, OBJV_V_VELOCITY, &velocity);

      AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, false);
    }
  } break;
  case THIEF_SUB_GET_POWERUP: {
  } break;
  case THIEF_SUB_DROP_POWERUP: {
  } break;
  default: {
  } break;
  }

  if (memory->sub_mode != THIEF_SUB_NONE && memory->sub_mode_time > 10.0) {
    SetSubMode(me, THIEF_SUB_NONE);
  }
}

void Thief::SetMode(int me, int new_mode) {
  vector pos;
  int room = 0;

  AI_SetType(me, AIT_AIS);

  // Makes sure that the dodge flag is set by default (certain modes turn it off)
  int flags = AIF_DODGE; // Don't dodge while surrendering
  AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

  switch (new_mode) {
  case THIEF_AMBIENT: {
    AI_AddGoal(me, AIG_WANDER_AROUND, 2, 1.0f, -1, GF_ORIENT_VELOCITY | GF_NOTIFIES | GF_KEEP_AT_COMPLETION, &pos,
               room);
    AI_SetGoalFlags(me, 2, GF_ORIENT_TARGET, false);
  } break;
  case THIEF_STEAL: {
    flags = AIF_DODGE; // Don't dodge while stealing
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    AI_SetType(me, AIT_MELEE1);
  } break;
  case THIEF_DEATH: {
    flags = AIF_DODGE; // Don't dodge while dying
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    float temp = 0.0f;
    AI_Value(me, VF_SET, AIV_F_MAX_TURN_RATE, &temp);
    Obj_SetCustomAnim(me, 85.0f, 140.0f, 8.0f, 0, Sound_FindId("RbtThiefDeath"), -1);
  } break;
  case THIEF_SURRENDER: {
    flags = AIF_DODGE; // Don't dodge while surrendering
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_ORIENT_TARGET | GF_KEEP_AT_COMPLETION, me);
    Obj_SetCustomAnim(me, 64.0f, 71.0f, 1.0f, 0, -1, -1);
  } break;
  case THIEF_TRACK_PLAYER: {
  } break;
  case THIEF_RUN_AWAY: {
  } break;
  case THIEF_TIME_BOMB: {
  } break;
  case THIEF_PLAYER_DEATH_TAUNT: {
  } break;
  case THIEF_KIDNAP_GB: {
  } break;
  case THIEF_CORNERED: {
  } break;
  }

  memory->mode_time = 0.0f;
  memory->mode = new_mode;
}

void Thief::DoInit(int me) {

  int room;
  vector pos;
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(thief_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (thief_data *)Scrpt_MemAlloc(&ch);
  memory->next_test_time = Game_GetTime() + 5.0f;
  memory->last_frame = 0;
  memory->last_summon_time = Game_GetTime();

  memory->num_stolen_objs = 0;
  memory->num_stolen_weapons = 0;
  memory->num_stolen_inv = 0;
  Obj_Value(me, VF_GET, OBJV_F_SHIELDS, &memory->last_shields);

  SetMode(me, THIEF_AMBIENT);
  SetSubMode(me, THIEF_SUB_NONE);
}

void Thief::DoCollide(int me, tOSIRISEVTCOLLIDE *evt_collide) {}

bool Thief::DoNotify(int me, tOSIRISEVTAINOTIFY *notify) {
  switch (notify->notify_type) {
  case AIN_MELEE_HIT: {
    int target_handle;
    int target_type;

    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target_handle);
    Obj_Value(target_handle, VF_GET, OBJV_I_TYPE, &target_type);

    if (target_type == OBJ_PLAYER) {
      bool f_success;

      f_success = DoSteal(me, target_handle, 1, false);
      DoSteal(me, target_handle, 2, f_success);
    } else if (target_type == OBJ_ROBOT) {
      uint16_t id;

      Obj_Value(target_handle, VF_GET, OBJV_US_ID, &id);
      if (id == ROBOT_GUIDEBOT || id == ROBOT_GUIDEBOTRED) {
        DoKidnap(me, target_handle);
      } else {
        DoAttack(me, target_handle);
      }
    }

    // If successful or dot to player greater than threshold then -- chrishack
    SetMode(me, THIEF_AMBIENT);
  } break;
  case AIN_HIT_BY_WEAPON: {
    if (memory->mode == THIEF_STEAL) {
      SetMode(me, THIEF_AMBIENT);
    }
  } break;
  }

  return true;
}

void Thief::DoFrame(int me) {
  // Drop bomb:29-50 (4.5 seconds, bomb created at 41 and leaves hand at frame 45)
  // Button push: 50-64 (3.5 seconds)  button presses: 57,59
  // surrender: 64-85 (2.5-3.0 seconds)
  // summon: 12-29 (3.0 seconds)  19-23 (summons)

  float anim_frame;
  float shields;
  int flags;
  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &anim_frame);
  Obj_Value(me, VF_GET, OBJV_F_SHIELDS, &shields);
  Obj_Value(me, VF_GET, OBJV_I_FLAGS, &flags);

  bool f_used;
  AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &f_used);
  if (f_used) {
    return;
  }

  msafe_struct m;
  m.objhandle = me;

  MSafe_GetValue(MSAFE_OBJECT_POS, &m);
  MSafe_GetValue(MSAFE_OBJECT_ROOMNUM, &m);

  if ((flags & OF_AI_DEATH) &&
      !((anim_frame >= 0.0f && anim_frame <= 6.0f) || (anim_frame >= 85.0f && anim_frame <= 140.0f))) {
    int room;
    vector pos;
    int weapon_id;

    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

    weapon_id = Wpn_FindID("TubbsHitBlast");
    Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);

    Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
             0.0f, 0.0f);
  }

  if ((memory->mode != THIEF_DEATH) && (flags & OF_AI_DEATH) && anim_frame >= 0.0f && anim_frame <= 6.0f) {
    SetMode(me, THIEF_DEATH);
  }

  if (memory->last_frame >= 50.0f && memory->last_frame <= 64.0f && memory->last_frame < 57.0f && anim_frame >= 57.0f) {
    Sound_Play3d(me, Sound_FindId("RbtThiefButtonA"));
  }

  if (memory->last_frame >= 50.0f && memory->last_frame <= 64.0f && memory->last_frame < 59.0f && anim_frame >= 59.0f) {
    Sound_Play3d(me, Sound_FindId("RbtThiefButtonB"));
  }

  if (memory->mode == THIEF_DEATH) {
    if (anim_frame > 86 && memory->last_frame <= 86) {
      int room;
      vector pos;
      int weapon_id;

      Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
      Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

      weapon_id = Wpn_FindID("TubbsHitBlast");
      Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);
    }

    if (memory->mode_time < 5.0f && memory->mode_time + Game_GetFrameTime() >= 5.0f) {
      Obj_Burning(me, 1000000.0f, 1.0f);
    }

    if (memory->mode_time > 8.0f) {
      Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
    }
  } else if (memory->mode == THIEF_SURRENDER) {
    if (anim_frame >= 65.0 && anim_frame <= 71.0) {
      Obj_SetCustomAnim(me, 71.0f, 79.0f, 1.0f, AIAF_LOOPING, -1, -1);
    }

    if (memory->mode_time < 2.2f && memory->mode_time + Game_GetFrameTime() >= 2.2f) {
      SpewEverything(me);
    }

    if (memory->mode_time < 3.0f && memory->mode_time + Game_GetFrameTime() >= 3.0f) {
      Obj_SetCustomAnim(me, 79.0f, 85.0f, 1.5f, AIAF_NOTIFY, -1, AS_ALERT);
    }

    if (memory->mode_time > 3.0f && anim_frame >= 0 && anim_frame <= 6) {
      SetMode(me, THIEF_AMBIENT);
    }
  } else if (memory->mode == THIEF_AMBIENT) {
    DoSubModeFrame(me);

    if (memory->mode_time > 10.0f && memory->sub_mode == THIEF_SUB_NONE) {
      SetMode(me, THIEF_STEAL);
    }

    if (shields < 20.0f && memory->last_shields >= 20.0) {
      SetMode(me, THIEF_SURRENDER);
    }
  } else {
    if (memory->mode_time > 10.0 && memory->sub_mode == THIEF_SUB_NONE) {
      SetMode(me, THIEF_AMBIENT);
    }
  }

  // Update the last frame
  memory->mode_time += Game_GetFrameTime();
  memory->sub_mode_time += Game_GetFrameTime();

  memory->last_frame = anim_frame;
  memory->last_shields = shields;
}

void Thief::SpewEverything(int me) {
  int i;
  int powerup_handle;
  int room;
  vector pos;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

  for (i = 0; i < memory->num_stolen_weapons; i++) {
    uint16_t id;
    int j;

    for (j = 0; j < memory->stolen_weapons[i].amount; j++) {
      float speed = rand() / (float)RAND_MAX * 20.0f + 5.0f;
      vector dir;

      dir.x = rand() / (float)RAND_MAX - 0.5f;
      dir.y = rand() / (float)RAND_MAX - 0.5f;
      dir.z = rand() / (float)RAND_MAX - 0.5f;

      vm_VectorNormalize(&dir);
      dir *= speed;

      Player_Value(memory->stolen_weapons[i].owner, VF_GET, PLYSV_US_WEAPON_POWERUP_ID, &id,
                   memory->stolen_weapons[i].index);
      powerup_handle = Obj_Create(OBJ_POWERUP, id, room, &pos, NULL, OBJECT_HANDLE_NONE, &dir);
    }

    memory->stolen_weapons[i].amount = 0;
  }

  for (i = 0; i < memory->num_stolen_objs; i++) {
  }
  memory->num_stolen_objs = 0;

  for (i = 0; i < memory->num_stolen_inv; i++) {
    static int am_id = -2, hl_id = -2, etos_id = -2, cl_id = -2, iv_id = -2, rf_id = -2, qf_id = -2;
    int id;

    switch (memory->stolen_inv[i].id) {
    case THIEFITEM_AUTOMAP:
      if (am_id == -2)
        am_id = Obj_FindID("ThiefAutoMap");
      id = am_id;
      break;
    case THIEFITEM_HEADLIGHT:
      if (hl_id == -2)
        hl_id = Obj_FindID("HeadlightPowerup");
      id = hl_id;
      break;
    case THIEFITEM_ETOSCONV:
      if (etos_id == -2)
        etos_id = Obj_FindID("Converter");
      id = etos_id;
      break;
    case THIEFITEM_CLOAK:
      if (cl_id == -2)
        cl_id = Obj_FindID("Cloak");
      id = cl_id;
      break;
    case THIEFITEM_INVULN:
      if (iv_id == -2)
        iv_id = Obj_FindID("Invulnerability");
      id = iv_id;
      break;
    case THIEFITEM_RAPIDFIRE:
      if (rf_id == -2)
        rf_id = Obj_FindID("Rapidfire");
      id = rf_id;
      break;
    case THIEFITEM_QUADFIRE:
      if (qf_id == -2)
        qf_id = Obj_FindID("QuadLaser");
      id = qf_id;
      break;
    default:
      id = -1;
      break;
    }

    if (id > -1) {
      float speed = rand() / (float)RAND_MAX * 20.0f + 5.0f;
      vector dir;

      dir.x = rand() / (float)RAND_MAX - 0.5f;
      dir.y = rand() / (float)RAND_MAX - 0.5f;
      dir.z = rand() / (float)RAND_MAX - 0.5f;

      vm_VectorNormalize(&dir);
      dir *= speed;

      powerup_handle = Obj_Create(OBJ_POWERUP, id, room, &pos, NULL, OBJECT_HANDLE_NONE, &dir);
    }
  }
  memory->num_stolen_inv = 0;
}

void Thief::DoDestroy(int me, tOSIRISEVTDESTROY *evt_destroy) { SpewEverything(me); }

int16_t Thief::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_COLLIDE:
    DoCollide(data->me_handle, &data->evt_collide);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, &data->evt_ai_notify) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY:
    DoDestroy(data->me_handle, &data->evt_destroy);
    break;
  case EVT_MEMRESTORE: {
    memory = (thief_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Super Thief
//---------------

//---------------
// Sickle
//---------------

void Sickle::SetMode(int me, char mode) {
  if (mode == memory->mode)
    return;

  float fov = -1.0f;
  AI_Value(me, VF_SET, AIV_F_FOV, &fov);

  mprintf(0, "Set mode %d\n", (int)mode);
  memory->done_moving = false;
  memory->done_turning = false;

  AI_SetType(me, AIT_AIS);

  switch (mode) {
  case SICKLE_GOING_HOME: {
    int flags;

    // Turn off friend avoidance
    flags = AIF_AUTO_AVOID_FRIENDS;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    // Orient to vel
    AI_AddGoal(me, AIG_GET_TO_POS, 2, 1.0f, -1, GF_ORIENT_VELOCITY | GF_NOTIFIES, &memory->home_pos, memory->home_room);
    AI_SetGoalCircleDist(me, 2, 8.0f);
  } break;
  case SICKLE_LAND_ON_CEILING: {
    ray_info ray;
    int flags;
    int fate;

    int start_room;
    vector start_pos;
    vector end_pos;

    int ceiling_room;
    //		mprintf(0, "In mode 5\n");

    // Turn off auto-level
    flags = PF_LEVELING;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    Obj_Value(me, VF_GET, OBJV_V_POS, &start_pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &start_room);
    end_pos = start_pos;
    end_pos.y = end_pos.y + 400.0;
    flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
            FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
    fate = FVI_RayCast(me, &start_pos, &end_pos, start_room, 0.0f, flags, &ray);

    memory->ceiling_pos = ray.hit_point;
    memory->ceiling_pos.y -= 3.2f;

    fate = FVI_RayCast(me, &start_pos, &memory->ceiling_pos, start_room, 0.0f, flags, &ray);
    ceiling_room = ray.hit_room;

    AI_AddGoal(me, AIG_GET_TO_POS, 2, 1.0f, -1, /*GF_NONFLUSHABLE | GF_KEEP_AT_COMPLETION |*/ GF_ORIENT_SCRIPTED,
               &memory->ceiling_pos, ceiling_room);
    AI_SetGoalCircleDist(me, 2, 0.0f);

    // Turn on point-collide-walls
    flags = PF_POINT_COLLIDE_WALLS;
    Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    flags = PF_LOCK_MASK;
    Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);
  } break;
  case SICKLE_LANDED: {
    int flags;
    char movement_type;

    // Stop on ceiling
    flags = AIF_FORCE_AWARENESS | AIF_PERSISTANT;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    float awareness = AWARE_BARELY;
    AI_Value(me, VF_SET, AIV_F_AWARENESS, &awareness);

    float sleep_fov = 1.0f;
    AI_Value(me, VF_SET, AIV_F_FOV, &sleep_fov);

    movement_type = MT_NONE;
    Obj_Value(me, VF_SET, OBJV_C_MOVEMENT_TYPE, &movement_type);
  } break;
  case SICKLE_MELEE: {
    int flags;
    vector vel;
    char movement_type;

    if (memory->mode == SICKLE_LANDED) {
      Obj_Value(me, VF_GET, OBJV_V_VELOCITY, &vel);
      vel.y -= (8.0f + ((float)rand() / (float)RAND_MAX) * 15.0f);
      Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);
    }

    // Melee Mode
    flags = PF_LOCK_MASK | PF_POINT_COLLIDE_WALLS;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    flags = PF_LEVELING;
    Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    flags = AIF_FORCE_AWARENESS | AIF_AUTO_AVOID_FRIENDS | AIF_PERSISTANT;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    movement_type = MT_PHYSICS;
    Obj_Value(me, VF_SET, OBJV_C_MOVEMENT_TYPE, &movement_type);

    AI_SetType(me, AIT_MELEE1);
  } break;
  default:
    mprintf(0, "Sickle is all messed up!\n");
  }

  memory->mode = mode;
  memory->mode_time = 0.0f;
}

void Sickle::DoInit(int me) {
  int flags;
  msafe_struct m;
  m.objhandle = me;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(sickle_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (sickle_data *)Scrpt_MemAlloc(&ch);

  AI_SetType(me, AIT_AIS);
  flags = AIF_FORCE_AWARENESS | AIF_AUTO_AVOID_FRIENDS | AIF_PERSISTANT;
  AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

  Obj_Value(me, VF_GET, OBJV_V_POS, &memory->home_pos);
  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &memory->home_room);
  memory->done_turning = false;
  memory->done_moving = false;

  flags = PF_LEVELING;
  Obj_Value(me, VF_SET_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

  flags = PF_POINT_COLLIDE_WALLS;
  Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

  matrix orient;
  Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);
  memory->home_fvec = orient.fvec;
  memory->home_fvec.y = 0.0f;
  vm_VectorNormalize(&memory->home_fvec);

  memory->mode_time = 0.0f;

  SetMode(me, SICKLE_MELEE);
}

void Sickle::DoFrame(int me) {
  vector uvec;
  vector start_pos;
  vector end_pos;
  int flags;
  int fate;
  int start_room;
  int ceiling_room;
  float anim_frame;
  int new_mode;
  vector vel;
  float last_see_time;
  float last_hear_time;
  char movement_type;

  float temp_time;
  float temp_time2;
  AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &temp_time);
  AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &temp_time2);

  last_hear_time = Game_GetTime() - temp_time2;
  last_see_time = Game_GetTime() - temp_time;

  if (last_hear_time < last_see_time || memory->mode == SICKLE_LANDED) {
    last_see_time = last_hear_time;
  }

  memory->mode_time += Game_GetTime();

  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &anim_frame);

  new_mode = memory->mode;

  if ((anim_frame >= 50 && anim_frame <= 55) || (last_see_time > 7.0)) {
    if (memory->mode == SICKLE_MELEE) {
      new_mode = SICKLE_GOING_HOME;
    }
  } else {
    new_mode = SICKLE_MELEE;
  }

  if (memory->mode != new_mode) {
    SetMode(me, new_mode);
  }

  if (memory->mode == SICKLE_GOING_HOME) {
    mprintf(0, "Sickle going home\n");

    if (memory->done_moving == true) {
      SetMode(me, SICKLE_LAND_ON_CEILING);
    }
  } else if (memory->mode == SICKLE_LAND_ON_CEILING) {
    uvec.x = 0.0;
    uvec.y = -1.0;
    uvec.z = 0.0;

    memory->done_turning = AI_TurnTowardsVectors(me, &memory->home_fvec, &uvec) != 0;

    //		mprintf(0, "Sickle Land on Ceiling %d, %d\n", memory->done_moving?1:0, memory->done_turning?1:0);
    vector pos;
    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
    bool f_used;
    AI_GoalValue(me, 2, VF_GET, AIGV_B_USED, &f_used);

    mprintf(0, "%d Sickle Land on Ceiling %f away\n", f_used ? 1 : 0, vm_VectorDistance(&memory->ceiling_pos, &pos));

    //		mprintf(0, "In mode 10\n");
    int flags = PF_LEVELING;
    Obj_Value(me, VF_CLEAR_FLAGS, OBJV_I_PHYSICS_FLAGS, &flags);

    if (memory->done_turning == true && memory->done_moving == true) {
      SetMode(me, SICKLE_LANDED);
    }
  }
}

bool Sickle::DoNotify(int me_handle, tOSIRISEVTAINOTIFY *notify) {
  if ((IsGoalFinishedNotify(notify->notify_type)) &&
      (memory->mode == SICKLE_GOING_HOME || memory->mode == SICKLE_LAND_ON_CEILING) && (notify->goal_num == 2)) {

    memory->done_moving = true;
  }

  return true;
}

int16_t Sickle::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, &data->evt_ai_notify) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (sickle_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// FireAtDist
//---------------

void FireAtDist::DoInit(int me) {
  msafe_struct m;
  m.objhandle = me;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(fireatdist_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (fireatdist_data *)Scrpt_MemAlloc(&ch);

  memory->last_test_time = Game_GetTime();
  memory->last_f_fire = false;
  memory->me = me;

  AI_Value(me, VF_GET, AIV_F_CIRCLE_DIST, &memory->fire_dist);
}

void FireAtDist::DoFrame(int me) {
  if (memory->last_test_time + 3.0f < Game_GetTime()) {
    vector pos;
    int room;
    int scan_objs[200];
    int n_scan;
    int i;

    float dist;

    memory->last_test_time = Game_GetTime();

    Obj_Value(memory->me, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &room);

    AI_Value(memory->me, VF_GET, AIV_F_CIRCLE_DIST, &dist);

    n_scan = AI_GetNearbyObjs(&pos, room, dist, scan_objs, 200, false, true, false, true);

    memory->last_f_fire = false;

    for (i = 0; i < n_scan; i++) {
      int type;

      Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);

      if (type == OBJ_PLAYER) {
        vector p_pos;
        float cur_dist;

        Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &p_pos);

        cur_dist = vm_VectorDistance(&pos, &p_pos);

        if (cur_dist <= memory->fire_dist) {
          memory->last_f_fire = true;
          break;
        }
      }
    }
  }

  int flags = AISR_RANGED_ATTACK;
  if (memory->last_f_fire != false) {
    AI_Value(me, VF_SET_FLAGS, AIV_I_STATUS_REG, &flags);
  } else {
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_STATUS_REG, &flags);
  }
}

int16_t FireAtDist::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (fireatdist_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// HatePTMC
//---------------

void HatePTMC::DoInit(int me) {
  msafe_struct m;
  m.objhandle = me;

  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(hateptmc_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (hateptmc_data *)Scrpt_MemAlloc(&ch);

  memory->time_till_pulse = (float)rand() / (float)RAND_MAX + 2.0f;
  memory->me = me;
}

void HatePTMC::DoFrame(int me) {
  int flags = AIF_TEAM_PTMC;

  AI_Value(me, VF_GET, AIV_I_FLAGS, &flags);

  if ((flags & AIF_TEAM_MASK) == AIF_TEAM_REBEL) {
    memory->time_till_pulse -= Game_GetFrameTime();

    if (memory->time_till_pulse <= 0.0f) {
      memory->time_till_pulse = (float)rand() / (float)RAND_MAX + 2.0f;

      vector pos;
      int room;
      int scan_objs[50];
      int n_scan;
      int i;

      float dist = 200.0f;

      Obj_Value(memory->me, VF_GET, OBJV_V_POS, &pos);
      Obj_Value(memory->me, VF_GET, OBJV_I_ROOMNUM, &room);

      n_scan = AI_GetNearbyObjs(&pos, room, dist, scan_objs, 50, false, true, false, true);

      for (i = 0; i < n_scan; i++) {
        char ctype;
        int num_wbs;

        Obj_Value(scan_objs[i], VF_GET, OBJV_C_CONTROL_TYPE, &ctype);
        Obj_WBValue(scan_objs[i], 0, VF_GET, WBV_C_NUM_WBS, &num_wbs);

        if (num_wbs > 0 && ctype == CT_AI) {
          int flags;
          int target;
          float last_see_target_time;
          int t_type = OBJ_NONE;

          AI_Value(scan_objs[i], VF_GET, AIV_I_FLAGS, &flags);
          AI_Value(scan_objs[i], VF_GET, AIV_I_TARGET_HANDLE, &target);
          AI_Value(scan_objs[i], VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_target_time);

          if (target != OBJECT_HANDLE_NONE) {
            Obj_Value(target, VF_GET, OBJV_I_TYPE, &t_type);
          }

          // If it is a PTMC bot
          if (((flags & AIF_TEAM_MASK) == AIF_TEAM_PTMC) &&
              !(t_type == OBJ_PLAYER && Game_GetTime() - last_see_target_time < 7.0f)) {
            float fov;
            AI_Value(scan_objs[i], VF_GET, AIV_F_FOV, &fov);

            vector p_pos;
            int p_room;
            matrix orient;

            Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &p_pos);
            Obj_Value(scan_objs[i], VF_GET, OBJV_I_ROOMNUM, &p_room);

            vector dir = p_pos - pos;
            float dist = vm_VectorNormalize(&dir);

            Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

            if (p_room == room || dist < 60.0f || orient.fvec * dir >= fov) {
              ray_info ray;
              int flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_IGNORE_MOVING_OBJECTS |
                          FQ_IGNORE_NON_LIGHTMAP_OBJECTS;
              int fate = FVI_RayCast(me, &pos, &p_pos, room, 0.0f, flags, &ray);

              if (fate == HIT_NONE) {
                float awareness;
                AI_Value(scan_objs[i], VF_GET, AIV_F_AWARENESS, &awareness);
                if (awareness < AWARE_MOSTLY) {
                  awareness = AWARE_MOSTLY;
                  AI_Value(scan_objs[i], VF_SET, AIV_F_AWARENESS, &awareness);
                }
                AI_Value(scan_objs[i], VF_SET, AIV_I_TARGET_HANDLE, &me);
              }
            }
          }
        }
      }
    }
  }
}

int16_t HatePTMC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_INTERVAL:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (hateptmc_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Tubbs
//---------------

void Tubbs::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(tubbs_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (tubbs_data *)Scrpt_MemAlloc(&ch);

  int diff = Game_GetDiffLevel();

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

  switch (diff) {
  case DIFFICULTY_TRAINEE:
    memory->max_speed = memory->base_speed * 1.2f;
    memory->max_acc = memory->base_acc * 1.1f;
    memory->full_anger_time = 22.0f;
    break;
  case DIFFICULTY_ROOKIE:
    memory->max_speed = memory->base_speed * 1.3f;
    memory->max_acc = memory->base_acc * 1.5f;
    memory->full_anger_time = 20.0f;
    break;
  case DIFFICULTY_HOTSHOT:
    memory->max_speed = memory->base_speed * 1.7f;
    memory->max_acc = memory->base_acc * 2.5f;
    memory->full_anger_time = 18.0f;
    break;
  case DIFFICULTY_ACE:
    memory->max_speed = memory->base_speed * 1.75f;
    memory->max_acc = memory->base_acc * 2.8f;
    memory->full_anger_time = 15.0f;
    break;
  case DIFFICULTY_INSANE:
    memory->max_speed = memory->base_speed * 1.8f;
    memory->max_acc = memory->base_acc * 3.0f;
    memory->full_anger_time = 12.0f;
    break;
  }
}

void Tubbs::DoFrame(int me) {
  float see_time;
  AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &see_time);

  bool used;
  AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

  if (see_time + 4.0f > Game_GetTime() && !used) {
    float speed;
    float acc;
    float ft;

    ft = Game_GetFrameTime();

    AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &speed);
    AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &acc);

    speed += (memory->max_speed - memory->base_speed) * (ft / memory->full_anger_time);
    acc += (memory->max_acc - memory->base_acc) * (ft / memory->full_anger_time);

    if (speed > memory->max_speed)
      speed = memory->max_speed;
    if (acc > memory->max_acc)
      acc = memory->max_acc;

    //		mprintf(0, "Max Speed is %f\n", speed);

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &acc);
  } else {
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);
  }
}

bool Tubbs::DoNotify(int me, tOSIRISEVTAINOTIFY *notify) {
  int room;
  vector pos;
  int weapon_id;

  if (notify->notify_type == AIN_MELEE_ATTACK_FRAME) {
    if (notify->attack_num == 0) {
      Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
      Obj_GetGunPos(me, 0, &pos);

      weapon_id = Wpn_FindID("TubbsHitBlast");
      Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);
    }
  }

  return true;
}

int16_t Tubbs::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, &data->evt_ai_notify) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (tubbs_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------
// Old Scratch
//---------------

bool OldScratch::DoSteal(int me, int it) {
  int max_tries = numSuperThiefableItems;
  float gen_perc, perc_chance;
  ;
  int i;
  int count_max, count_num;
  bool *attempted_steals;

  attempted_steals = (bool *)malloc(numSuperThiefableItems * sizeof(bool));
  if (!attempted_steals)
    return false;

  float ftime = Game_GetFrameTime();
  if (ftime == 0)
    ftime = 1.0f;
  srand(Game_GetTime() / ftime);

  for (i = 0; i < numSuperThiefableItems; i++) {
    attempted_steals[i] = false;
  }

  while (max_tries--) {
    i = rand() % numSuperThiefableItems;

    if (attempted_steals[i]) {
      // we already tried this one, try another
      max_tries++;
      continue;
    }

    attempted_steals[i] = true;

    {
      count_max = MAX_STOLEN_WEAPONS;

      // mprintf(0,"THIEF: Checking %s\n",TXT(SuperThiefableItems[i].name_idx));

      bool can_take = false;
      int amount = 0;
      char message[256];

      switch (SuperThiefableItems[i].type) {
      case THIEFABLEITEM_PRIMARY:
        // check to see if we can steal the primary
        Player_Value(it, VF_GET, PLYSV_I_WEAPON, &amount, SuperThiefableItems[i].index);
        if (SuperThiefableItems[i].index != 0 && amount) {
          can_take = true;
          snprintf(message, sizeof(message), TXT_THIEFSTEAL, TXT(SuperThiefableItems[i].name_idx));
        }
        break;

      case THIEFABLEITEM_SECONDARY:
        // check to see if we can steal the secondary
        {
          Player_Value(it, VF_GET, PLYSV_I_WEAPON, &amount, SuperThiefableItems[i].index);

          if (amount) {
            int max;

            if (SuperThiefableItems[i].index > 14) {
              // 2nd selection group (black shark, etc)
              max = (19 - SuperThiefableItems[i].index) / 2.5f + 1;
            } else {
              // 1st selection group (mega, etc)
              max = (14 - SuperThiefableItems[i].index) / 2.5f + 1;
            }

            int new_amount = (rand() / (float)(RAND_MAX + 1)) * max + 1;

            if (new_amount < amount)
              amount = new_amount;

            can_take = true;

            if (amount == 1) {
              snprintf(message, sizeof(message), TXT_STHIEFSTEAL, TXT(SuperThiefableItems[i].name_idx));
            } else {
              snprintf(message, sizeof(message), TXT_STHIEFSTEAL2, amount, TXT(SuperThiefableItems[i].name_idx));
            }
          }
        }
        break;
      }

      if (!can_take)
        continue;

      {
        int powerup_handle;
        int room;
        vector pos;
        int j;
        uint16_t id;

        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
        Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

        for (j = 0; j < amount; j++) {
          float speed = rand() / (float)RAND_MAX * 20.0f + 5.0f;
          vector dir;

          dir.x = rand() / (float)RAND_MAX - 0.5f;
          dir.y = rand() / (float)RAND_MAX - 0.5f;
          dir.z = rand() / (float)RAND_MAX - 0.5f;

          vm_VectorNormalize(&dir);
          dir *= speed;

          Player_Value(it, VF_GET, PLYSV_US_WEAPON_POWERUP_ID, &id, SuperThiefableItems[i].index);
          powerup_handle = Obj_Create(OBJ_POWERUP, id, room, &pos, NULL, it, &dir);
        }
      }

      if (SuperThiefableItems[i].type == THIEFABLEITEM_PRIMARY) {
        amount = 0;
      } else {
        amount *= -1;
      }

      Player_Value(it, VF_SET, PLYSV_I_WEAPON, &amount, SuperThiefableItems[i].index);

      free(attempted_steals);
      return true;
    }
  }

  mprintf(0, "Super Thief: Not taking anything\n");
  free(attempted_steals);
  return false; // we didn't take anything this try
}

void OldScratch::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(oldscratch_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (oldscratch_data *)Scrpt_MemAlloc(&ch);

  int diff = Game_GetDiffLevel();

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

  switch (diff) {
  case DIFFICULTY_TRAINEE:
    memory->max_speed = memory->base_speed * 1.05f;
    memory->max_acc = memory->base_acc * 1.05f;
    memory->full_anger_time = 22.0f;
    break;
  case DIFFICULTY_ROOKIE:
    memory->max_speed = memory->base_speed * 1.075f;
    memory->max_acc = memory->base_acc * 1.2f;
    memory->full_anger_time = 20.0f;
    break;
  case DIFFICULTY_HOTSHOT:
    memory->max_speed = memory->base_speed * 1.1f;
    memory->max_acc = memory->base_acc * 1.3f;
    memory->full_anger_time = 18.0f;
    break;
  case DIFFICULTY_ACE:
    memory->max_speed = memory->base_speed * 1.125f;
    memory->max_acc = memory->base_acc * 1.4f;
    memory->full_anger_time = 15.0f;
    break;
  case DIFFICULTY_INSANE:
    memory->max_speed = memory->base_speed * 1.2f;
    memory->max_acc = memory->base_acc * 1.5f;
    memory->full_anger_time = 12.0f;
    break;
  }
}

void OldScratch::DoFrame(int me) {
  float see_time;
  AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &see_time);

  bool used;
  AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

  if (see_time + 4.0f > Game_GetTime() && !used) {
    float speed;
    float acc;
    float ft;

    ft = Game_GetFrameTime();

    AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &speed);
    AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &acc);

    speed += (memory->max_speed - memory->base_speed) * (ft / memory->full_anger_time);
    acc += (memory->max_acc - memory->base_acc) * (ft / memory->full_anger_time);

    if (speed > memory->max_speed)
      speed = memory->max_speed;
    if (acc > memory->max_acc)
      acc = memory->max_acc;

    //		mprintf(0, "Max Speed is %f\n", speed);

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &acc);
  } else {
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);
  }
}

bool OldScratch::DoNotify(int me, tOSIRISEVTAINOTIFY *notify) {
  if (notify->notify_type == AIN_MELEE_HIT) {
    int target_handle;
    int target_type;
    int target_flags;

    AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target_handle);
    Obj_Value(target_handle, VF_GET, OBJV_I_TYPE, &target_type);
    Obj_Value(target_handle, VF_GET, OBJV_I_FLAGS, &target_flags);

    int diff = Game_GetDiffLevel();
    float chance = (float)rand() / (float)RAND_MAX;

    if (diff == 0 && chance < 0.60f)
      return true;

    if (diff == 1 && chance < 0.40f)
      return true;

    if (target_type == OBJ_PLAYER && (target_flags & OF_DESTROYABLE)) {
      bool f_success;
      f_success = DoSteal(me, target_handle);
    }
  }

  return true;
}

int16_t OldScratch::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, &data->evt_ai_notify) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (oldscratch_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//---------------------
// BarnSwallow
//---------------------

void BarnSwallow::ComputeNextNestPnt(int me, vector *pos) {
  pos->x = (0.5f - (float)rand() / (float)RAND_MAX);
  pos->y = (0.5f - (float)rand() / (float)RAND_MAX);
  pos->z = (0.5f - (float)rand() / (float)RAND_MAX);

  pos->y *= 0.3f;

  vm_VectorNormalize(pos);

  *pos = *pos * memory->nest_rad;
  *pos += memory->nest_center;
}

// #define BSCOMM_FOLLOW_ME								0 // send a percent chance so we
// can have a line sometimes #define BSCOMM_FOLLOW_CANCEL_FROM_FOLLOWER		2 #define
// BSCOMM_FOLLOW_CANCEL_FROM_LEADER 3
//  #define BSCOMM_ATTACK_MY_TARGET						4
//  BSCOMM_ARE_YOU_IN_MODE

bool BarnSwallow::ReceiveCommand(int me, int it, gb_com *command) {
  bool f_ok = true;

  switch (command->action) {
  case BSCOMM_FOLLOW_ME:
    SetMode(me, BSM_FOLLOW, it);
    break;
  case BSCOMM_FOLLOW_CANCEL_FROM_FOLLOWER:
    memory->follower = OBJECT_HANDLE_NONE;
    break;
  case BSCOMM_FOLLOW_CANCEL_FROM_LEADER: {
    SetMode(me, BSM_RETURN_TO_NEST);
  } break;
  case BSCOMM_ATTACK_MY_TARGET: {
    int flags;
    int room;
    int me_room;

    Obj_Value(it, VF_GET, OBJV_I_FLAGS, &flags);
    Obj_Value(it, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(me, VF_GET, OBJV_I_FLAGS, &me_room);

    if ((flags & OF_ATTACHED) && rand() % 10 > 3) {
      SetMode(me, BSM_ATTACK, it);
    } else if (me_room == room) {
      SetMode(me, BSM_ATTACK, it);
    } else if (rand() % 10 > 6) {
      SetMode(me, BSM_ATTACK, it);
    } else {
      f_ok = false;
    }
  } break;
  case BSCOMM_ARE_YOU_IN_MODE: {
    f_ok = (memory->mode == command->index);
  } break;
  case BSCOMM_ARE_YOU_AFTER_POWERUP: {
    f_ok = (memory->powerup_id == command->index);
  }
  }

  return f_ok;
}

bool BarnSwallow::SendCommand(int me, int it, char action, int value) {
  bool f_ok;
  tOSIRISEventInfo data;
  gb_com command;

  data.me_handle = it;
  data.evt_ai_notify.it_handle = me;

  command.action = action;
  command.index = value;

  data.extra_info = (void *)&command;
  data.evt_ai_notify.notify_type = AIN_USER_DEFINED;

  f_ok = Obj_CallEvent(it, EVT_AI_NOTIFY, &data);
  if (f_ok || command.action == BSCOMM_FOLLOW_CANCEL_FROM_LEADER) {
    switch (command.action) {
    case BSCOMM_FOLLOW_ME:
      memory->follower = it;
      break;
    case BSCOMM_FOLLOW_CANCEL_FROM_FOLLOWER:
      memory->follower = OBJECT_HANDLE_NONE;
      break;
    case BSCOMM_FOLLOW_CANCEL_FROM_LEADER:
      memory->follower = OBJECT_HANDLE_NONE;
      break;
    }
  }
  return f_ok;
}

void BarnSwallow::DoInit(int me) {
  int i;
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(barnswallow_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (barnswallow_data *)Scrpt_MemAlloc(&ch);

  memory->follower = OBJECT_HANDLE_NONE;

  ComputeNest(me);

  memory->next_friend_update_time = Game_GetTime() + 5.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;
  memory->next_attack_time = Game_GetTime();
  memory->next_powerup_time = Game_GetTime() + 5.0f + ((float)rand() / (float)RAND_MAX) * 2.0f;

  memory->last_non_attack_mode = memory->mode = BSM_NEST;
  memory->mode_time = 0.0f;

  memory->flags = 0;

  SetMode(me, BSM_NEST);
}

bool BarnSwallow::DoNotify(int me, tOSIRISEventInfo *data) {
  if (IsGoalFinishedNotify(data->evt_ai_notify.notify_type)) // chrishack -- handle invalid goal cases if I should
  {
    switch (memory->mode) {
    case BSM_NEST: {
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, BSM_NEST);
        return false;
      }
    } break;
    case BSM_GET_POWERUP: {
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, BSM_RETURN_TO_NEST);
        return false;
      }
    } break;
    case BSM_RETURN_TO_NEST: {
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, BSM_NEST);
        return false;
      }
    } break;
    case BSM_ATTACK:
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, BSM_ATTACK_CIRCLE_BACK);
        return false;
      }
      break;
    }
  } else if (data->evt_ai_notify.notify_type == AIN_USER_DEFINED) {
    return ReceiveCommand(me, data->evt_ai_notify.it_handle, (gb_com *)data->extra_info);
  }

  return true;
}

void BarnSwallow::ComputeNest(int me) {
  memory->num_friends = 0;
  int scan_objs[100];
  int n_scan;
  int i;
  vector pos;
  int room;
  int type;
  uint16_t id;

  memory->num_friends = 0;

  for (i = 0; i < BS_MAX_FRIENDS; i++)
    memory->friends[i] = OBJECT_HANDLE_NONE;

  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(me, VF_GET, OBJV_I_TYPE, &type);
  Obj_Value(me, VF_GET, OBJV_US_ID, &id);

  memory->home_room = room;
  memory->nest_center =
      pos; // Each robot will have a different center point becuase thier initial positions are weighted twice
  memory->nest_rad = 0.0f;

  n_scan = AI_GetNearbyObjs(&pos, room, 1000.0f, scan_objs, 100, false, true, false, true);

  for (i = 0; i < n_scan; i++) {
    if (scan_objs[i] != me) {
      int c_type;
      uint16_t c_id;
      Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &c_type);
      Obj_Value(scan_objs[i], VF_GET, OBJV_US_ID, &c_id);

      // See if we are the same species
      if (type == c_type && id == c_id) {
        vector c_pos;
        Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &c_pos);

        memory->nest_center += c_pos;

        memory->friends[memory->num_friends++] = scan_objs[i];
      }
    }
  }

  if (memory->num_friends)
    memory->nest_center /= memory->num_friends + 1;

  // Determine the farthest distance from the center of the nest
  for (i = 0; i < memory->num_friends; i++) {
    vector c_pos;
    float dist;
    Obj_Value(memory->friends[i], VF_GET, OBJV_V_POS, &c_pos);
    dist = vm_VectorDistance(&memory->nest_center, &c_pos);

    if (dist * 0.9f > memory->nest_rad)
      memory->nest_rad = dist * 0.9f;
  }

  if (memory->nest_rad < 5.0f)
    memory->nest_rad = 5.0f;
}

void BarnSwallow::UpdateFriendList(int me) {
  int i;
  int j;

  for (i = 0; i < memory->num_friends; i++) {
    int type;
    Obj_Value(memory->friends[i], VF_GET, OBJV_I_TYPE, &type);

    if (type == OBJ_NONE) {
      for (j = i; j < memory->num_friends - 1; j++) {
        memory->friends[j] = memory->friends[j + 1];
      }

      i--; // Retest as the slot is now being used by what was the next item
      memory->num_friends--;
    }
  }
}

void BarnSwallow::DoFrame(int me) {
  if (memory->next_friend_update_time < Game_GetTime()) {
    memory->next_friend_update_time = Game_GetTime() + 5.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;

    UpdateFriendList(me);
  }

  switch (memory->mode) {
  case BSM_NEST: {
    if (Game_GetTime() > memory->next_mode_time) {
      int target;
      int room;
      int me_room;

      AI_Value(me, VF_GET, AIV_I_TARGET_HANDLE, &target);

      if (target != OBJECT_HANDLE_NONE) {
        Obj_Value(target, VF_GET, OBJV_I_ROOMNUM, &room);
        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &me_room);
      }

      if (target != OBJECT_HANDLE_NONE && room == me_room)
        SetMode(me, BSM_ATTACK);
      else
        SetMode(me, BSM_NEST);
    }

    if (Game_GetTime() > memory->next_powerup_time) {
      int rand_val = rand() % 100;

      memory->next_powerup_time = Game_GetTime() + 5.0f + ((float)rand() / (float)RAND_MAX) * 2.0f;

      if (rand_val < 20) // Play with local powerups
      {
        int scan_objs[50];
        int n_scan;
        int i;
        int n_powerups = 0;
        int powerups[50];
        int room;
        vector pos;

        Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

        n_scan = AI_GetNearbyObjs(&pos, room, 30.0f, scan_objs, 50, false, false, false, true);

        for (i = 0; i < n_scan; i++) {
          int type;
          Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);
          if (type == OBJ_POWERUP) {
            powerups[n_powerups++] = scan_objs[i];
          }
        }

        if (n_powerups) {
          int index = rand() % n_powerups;
          SetMode(me, BSM_GET_POWERUP, powerups[index]);
        }
      }
      if (rand_val > 95) // Find a remote powerup and go get it
      {
        int i;
        bool f_ok = true;

        //					for(i = 0; i < memory->num_friends; i++)
        //					{
        //						int room = memory->home_room;  // Acounts for dead friends
        //					}

        int p_handle = AI_FindObjOfType(me, OBJ_POWERUP, -1, true);

        for (i = 0; i < memory->num_friends; i++) {
          if (SendCommand(me, memory->friends[i], BSCOMM_ARE_YOU_AFTER_POWERUP, p_handle)) {
            p_handle = OBJECT_HANDLE_NONE;
            break;
          }
        }

        if (p_handle != OBJECT_HANDLE_NONE) {
          SetMode(me, BSM_GET_POWERUP, p_handle);
        }
      }
    }
  } break;
  case BSM_FOLLOW: {
  } break;
  case BSM_GET_POWERUP: {
    if (memory->mode_time > memory->max_time_on_road) {
      SetMode(me, BSM_RETURN_TO_NEST);
    }
  } break;
  case BSM_ATTACK: {
    float last_see_target_time;
    float last_hear_target_time;
    AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_target_time);
    AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &last_hear_target_time);

    if (Game_GetTime() > last_see_target_time + 7.0f && Game_GetTime() > last_hear_target_time + 7.0f)
      SetMode(me, memory->last_non_attack_mode);
    float dist;
    AI_GoalValue(me, 1, VF_GET, AIGV_F_DIST_TO_GOAL, &dist);
  } break;
  case BSM_ATTACK_CIRCLE_BACK: {
    float last_see_target_time;
    float last_hear_target_time;
    AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_target_time);
    AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &last_hear_target_time);

    if (Game_GetTime() > last_see_target_time + 7.0f && Game_GetTime() > last_hear_target_time + 7.0f)
      SetMode(me, memory->last_non_attack_mode);

    if (memory->mode_time > 5.0f)
      SetMode(me, BSM_ATTACK);
  } break;
  case BSM_FLEE: {
  } break;
  case BSM_RETURN_TO_NEST: {

  } break;
  }

  memory->mode_time += Game_GetFrameTime();
}

bool BarnSwallow::SetMode(int me, char mode, int it) {
  //	if(mode == BSM_ATTACK && memory->next_attack_time < Game_GetTime())
  //		return false;
  int f_attack_flags = (AIF_FIRE | AIF_AUTO_AVOID_FRIENDS);

  AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &f_attack_flags);

  if (memory->mode != BSM_ATTACK && memory->mode != BSM_ATTACK_CIRCLE_BACK) {
    memory->last_non_attack_mode = memory->mode;

    if (mode != BSM_ATTACK && mode != BSM_ATTACK_CIRCLE_BACK)
      memory->powerup_id = OBJECT_HANDLE_NONE;
  } else {
    if (mode == BSM_GET_POWERUP)
      it = memory->powerup_id;
  }

  // If we are not just floating around in the nest, then reset the next_powerup_time
  if (mode == BSM_NEST && memory->mode != BSM_NEST)
    memory->next_powerup_time = Game_GetTime() + 5.0f + ((float)rand() / (float)RAND_MAX) * 2.0f;

  if (memory->mode == BSM_RETURN_TO_NEST) {
    Obj_UnattachChildren(me);
    memory->powerup_id = OBJECT_HANDLE_NONE;
  }

  AI_SetType(me, AIT_AIS);

  switch (mode) {
  case BSM_NEST: {
    int room;
    float max_speed;
    vector pos;

    AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &max_speed);
    float update_time = memory->nest_rad / (max_speed) + 0.3f - ((float)rand() / (float)RAND_MAX);
    if (update_time < .6f)
      update_time = .6f;

    memory->next_mode_time = Game_GetTime() + update_time;

    ComputeNextNestPnt(me, &pos);

    AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, -1, GF_ORIENT_VELOCITY | GF_USE_BLINE_IF_SEES_GOAL, &pos, memory->home_room);
    AI_SetGoalCircleDist(me, 1, 10.0f);
  } break;
  case BSM_FOLLOW: {
  } break;
  case BSM_GET_POWERUP: {
    float dist = 20.0f;

    AI_AddGoal(me, AIG_ATTACH_TO_OBJ, 1, 1.0f, -1, GF_ORIENT_VELOCITY, it, 0, 0, 0.9f, 0, 1);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    // Make the barnswallow return home after awhile -- chrishack -- check vis before returning!
    memory->max_time_on_road = 12.0f + (float)rand() / (float)RAND_MAX * 20.0f;
    memory->powerup_id = it;
  } break;
  case BSM_ATTACK: {
    float dist = 40.0f + ((float)rand() / (float)RAND_MAX) * 10.0f;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    memory->next_attack_time = Game_GetTime() + 10.0 * ((float)rand() / (float)RAND_MAX);

    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1,
               GF_SPEED_ATTACK | GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_USE_BLINE_IF_SEES_GOAL, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    dist = 40.0f;
    int g_index = AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1,
                             GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;
  case BSM_ATTACK_CIRCLE_BACK: {
    vector pos;
    int room;

    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

    AI_AddGoal(me, AIG_WANDER_AROUND, 1, 1.0f, -1,
               GF_SPEED_FLEE | GF_ORIENT_VELOCITY | GF_NOTIFIES | GF_KEEP_AT_COMPLETION, &pos, room);

    float dist = 40.0f;
    int g_index = AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1,
                             GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;
  case BSM_FLEE: {
  } break;
  case BSM_RETURN_TO_NEST: {
    AI_AddGoal(me, AIG_GET_TO_POS, 1, 1.0, -1, GF_SPEED_FLEE | GF_ORIENT_VELOCITY | GF_USE_BLINE_IF_SEES_GOAL,
               &memory->nest_center, memory->home_room);
    AI_SetGoalCircleDist(me, 1, 5.0f);
  } break;
  }

  memory->mode = mode;

  memory->mode_time = 0.0f;
  return true;
}

int16_t BarnSwallow::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_DESTROY:
    break;
  case EVT_MEMRESTORE: {
    memory = (barnswallow_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//===================
// GBPowerup
//===================

void GBPowerup::DoInit(int me) {
  int i;
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(gbpowerup_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (gbpowerup_data *)Scrpt_MemAlloc(&ch);
  memory->next_check_time = Game_GetTime() + (float)rand() / (float)RAND_MAX; // Sead the powerups differently  :)
  memory->time_till_next_hud_message = 0.0f;

  uint16_t short_id[6];

  short_id[0] = Obj_FindID("Buddyextinguisher");
  short_id[1] = Obj_FindID("buddywingnut");
  short_id[2] = Obj_FindID("buddycontrol");
  short_id[3] = Obj_FindID("buddyassist");
  short_id[4] = Obj_FindID("buddyantivirus");
  short_id[5] = Obj_FindID("buddyspeed");

  uint16_t id;
  Obj_Value(me, VF_GET, OBJV_US_ID, &id);

  memory->type = 5; // Forces it to the speed powerup if it didn't know what it was...
  for (i = 0; i < 6; i++) {
    if (id == short_id[i]) {
      memory->type = i;
    }
  }
}

void GBPowerup::DoFrame(int me) {
  if (memory->next_check_time <= Game_GetTime()) {
    vector pos;
    int room;
    int scan_objs[25];
    int n_scan;
    int i;

    memory->next_check_time = Game_GetTime() + .2f + ((float)rand() / (float)RAND_MAX) * .3f;

    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

    n_scan = AI_GetNearbyObjs(&pos, room, 5.0f, scan_objs, 25, false, true, false, true);

    for (i = 0; i < n_scan; i++) {
      int type;
      int16_t id;
      Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);
      Obj_Value(scan_objs[i], VF_GET, OBJV_US_ID, &id);

      if (type == OBJ_ROBOT && (id == ROBOT_GUIDEBOT || id == ROBOT_GUIDEBOTRED)) {
        vector g_pos;
        Obj_Value(scan_objs[i], VF_GET, OBJV_V_POS, &g_pos);

        float dist = vm_VectorDistance(&pos, &g_pos);

        if (dist < 5.0f) {
          gb_com command;
          command.action = COM_POWERUP_PICKUP;
          command.index = memory->type;

          tOSIRISEventInfo data;
          data.me_handle = scan_objs[i];
          data.evt_ai_notify.it_handle = me;

          data.extra_info = (void *)&command;
          data.evt_ai_notify.notify_type = AIN_USER_DEFINED;

          Obj_CallEvent(scan_objs[i], EVT_AI_NOTIFY, &data);

          break;
        }
      }
    }
  }
}

int16_t GBPowerup::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL:
    memory->time_till_next_hud_message -= Game_GetFrameTime();
    break;
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_COLLIDE: {
    if (memory->time_till_next_hud_message <= 0.0f) {
      int type;

      memory->time_till_next_hud_message = 1.0f;
      Obj_Value(data->evt_collide.it_handle, VF_GET, OBJV_I_TYPE, &type);

      if (type == OBJ_PLAYER) {
        Player_AddHudMessage(data->evt_collide.it_handle, TXT_GB_POWERUP);
      }
    }
  } break;
  case EVT_MEMRESTORE: {
    memory = (gbpowerup_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Sparky class
//------------------

bool Sparky::DoNotify(int me_handle, tOSIRISEventInfo *data) {
  // NOTE:  I am also doing the rotational stuff here...  So, no need to make a seperate AIN_SCRIPTED_ORIENT event
  if (data->evt_ai_notify.goal_num == 0 && data->evt_ai_notify.notify_type == AIN_SCRIPTED_GOAL) {
    vector rvel;
    Obj_Value(me_handle, VF_GET, OBJV_V_ROTVELOCITY, &rvel);

    if (memory->spin_dir == SPARKY_ROT_LEFT) {
      rvel.y -= DEATH_ROT_ACC * Game_GetFrameTime();
    } else {
      rvel.y += DEATH_ROT_ACC * Game_GetFrameTime();
    }

    Obj_Value(me_handle, VF_SET, OBJV_V_ROTVELOCITY, &rvel);

    vector dir = Zero_vector;
    AI_Value(me_handle, VF_SET, AIV_V_MOVEMENT_DIR, &dir);
  }

  return true;
}

void Sparky::SetMode(int me, char mode) {
  AI_SetType(me, AIT_AIS);

  switch (mode) {
  case SPARKY_NORMAL: {
    Obj_Value(me, VF_SET, OBJV_F_ROTDRAG, &memory->drag);
    AI_SetType(me, AIT_MELEE1);
  } break;
  case SPARKY_DYING: {
    AI_AddGoal(me, AIG_SCRIPTED, 0, 1000.0f, -1, GF_NONFLUSHABLE | GF_ORIENT_SCRIPTED, NULL);

    float drag = 0.0f;
    Obj_Value(me, VF_SET, OBJV_F_ROTDRAG, &drag);
  } break;
  }

  memory->last_spark_time = Game_GetTime();
  memory->spin_time = 0.0f;
  memory->mode_time = 0.0f;
  memory->mode = mode;
}

void Sparky::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(sparky_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (sparky_data *)Scrpt_MemAlloc(&ch);

  memory->f_rotation_death_enabled = true;
  memory->matcen_id = -1;
  memory->mode = SPARKY_NORMAL;
  memory->mode_time = 0.0f;
  memory->spin_dir = SPARKY_NO_ROT;
  memory->spin_time = 0.0f;

  Obj_Value(me, VF_SET, OBJV_F_ROTDRAG, &memory->drag);
  Obj_Value(me, VF_GET, OBJV_M_ORIENT, &memory->orient);

  msafe_struct mstruct;

  mstruct.objhandle = me;
  mstruct.g1 = 0;
  mstruct.g2 = 1;
  mstruct.lifetime = 1000000000.0f;
  mstruct.size = 5.1f;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &mstruct.roomnum);
  Obj_GetGunPos(me, 0, &mstruct.pos);
  Obj_GetGunPos(me, 1, &mstruct.pos2);

  mstruct.state = 0;
  mstruct.interval = 0.5f;
  mstruct.count = 2;
  mstruct.index = 2;
  mstruct.texnum = Scrpt_FindTextureName("FunkyEffect2");
  // rbg
  mstruct.color = ((128 >> 3) << 10) | ((128 >> 3) << 5) | (128 >> 3);
  mstruct.flags = 1;
  MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING_BOLT, &mstruct);

  memory->last_spark_time = Game_GetTime();
  memory->spin_time = 0.0f;
  memory->mode_time = 0.0f;
}

void Sparky::DoFrame(int me) {

  if (memory->mode == SPARKY_NORMAL) {
    char spin_dir;
    matrix orient;
    Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

    float dot = orient.rvec * memory->orient.rvec;
    if (dot < -1.0f)
      dot = -1.0f;
    else if (dot > 1.0f)
      dot = 1.0f;

    float ang = acos(dot);

    float aps = (ang * 65535.0f) / (Game_GetFrameTime() * (2.0f * PI));

    if (aps >= MIN_MALF_SPEED) {
      float tdot = memory->orient.rvec * orient.fvec;
      if (tdot < 0.0f)
        spin_dir = SPARKY_ROT_LEFT;
      else if (tdot > 0.0f)
        spin_dir = SPARKY_ROT_RIGHT;
      else
        spin_dir = SPARKY_NO_ROT;
    } else {
      spin_dir = SPARKY_NO_ROT;
    }

    if (spin_dir == memory->spin_dir) {
      if (spin_dir == SPARKY_NO_ROT)
        memory->spin_time = 0.0f;
      else
        memory->spin_time += Game_GetFrameTime();
    } else {
      memory->spin_dir = spin_dir;
      memory->spin_time = 0.0f;
    }

    memory->spin_dir = spin_dir;
    memory->orient = orient;

    //		mprintf(0, "spin time %f\n", memory->spin_time);

    if (memory->spin_time > MALF_TIME) {
      SetMode(me, SPARKY_DYING);
    }
  } else {
    if (memory->last_spark_time + .1f < Game_GetTime()) {
      memory->last_spark_time = Game_GetTime();

      int room;
      vector pos;

      Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
      Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

      Game_CreateRandomSparks(5, &pos, room);
    }

    if (memory->mode_time < 2.5 && memory->mode_time + Game_GetFrameTime() >= 2.5) {
      msafe_struct mstruct;

      mstruct.random = 21;
      mstruct.is_real = 0;
      mstruct.objhandle = me;
      mstruct.gunpoint = 1;
      mstruct.effect_type = MED_SMOKE_INDEX;
      mstruct.phys_info = 0;
      mstruct.drag = .001f;
      mstruct.mass = .001f;
      mstruct.interval = .05f;
      mstruct.longevity = 100000.0f;
      mstruct.lifetime = 1.0;
      mstruct.size = 8.0f;
      mstruct.speed = 120.0;

      MSafe_CallFunction(MSAFE_OBJECT_START_SPEW, &mstruct);
    }

    if (memory->mode_time > DEATH_TIME) {
      Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_MEDIUM | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES,
               0.0f, 0.0f);
    }
  }

  memory->mode_time += Game_GetFrameTime();
}

int16_t Sparky::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (sparky_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Hellion class
//------------------

bool Hellion::DoNotify(int me, tOSIRISEventInfo *data) {
  switch (memory->mode) {
  case HELLION_WAIT: {
    if (data->evt_ai_notify.notify_type == AIN_MOVIE_START) {
      SetMode(me, HELLION_INTRO);
    }
  } break;
  case HELLION_INTRO: {
    if (data->evt_ai_notify.notify_type == AIN_MOVIE_END) {
      SetMode(me, HELLION_MATTER);
    }
  } break;
  }

  return true;
}

void Hellion::RemapAlert(int me, float start, float end, float time) {
  memory->alert_start = start;
  memory->alert_end = end;
  memory->alert_time = time;

  Obj_Value(me, VF_SET, OBJSV_F_ANIM_START, &start, AS_ALERT);
  Obj_Value(me, VF_SET, OBJSV_F_ANIM_END, &end, AS_ALERT);
  Obj_Value(me, VF_SET, OBJSV_F_ANIM_TIME, &time, AS_ALERT);
}

void Hellion::RemapWB(int me, float start, float fire, int fire_sound, float end, float time, float latency, int index,
                      uint16_t w_id, char f_mask) {
  memory->start = start;
  memory->fire = fire;
  memory->end = end;
  memory->time = time;
  memory->latency = latency;
  memory->index = index;
  memory->f_mask = f_mask;

  Obj_WBValue(me, 0, VF_SET, WBSV_F_ANIM_START, &start, index);
  Obj_WBValue(me, 0, VF_SET, WBSV_F_ANIM_FIRE, &fire, index);
  Obj_WBValue(me, 0, VF_SET, WBSV_I_FIRE_SOUND, &fire_sound, index);
  Obj_WBValue(me, 0, VF_SET, WBSV_F_ANIM_END, &end, index);
  Obj_WBValue(me, 0, VF_SET, WBSV_F_ANIM_TIME, &time, index);
  Obj_WBValue(me, 0, VF_SET, WBSV_F_LATENCY, &latency, index);
  Obj_WBValue(me, 0, VF_SET, WBSV_C_MASK, &f_mask, 0);

  char num_gps;
  Obj_WBValue(me, 0, VF_GET, WBV_C_NUM_GUNPTS, &num_gps);

  int i;
  for (i = 0; i < num_gps; i++) {
    Obj_WBValue(me, 0, VF_SET, WBSV_US_GUNPT_WEAPON_ID, &w_id, i);
  }
}

void Hellion::SetMode(int me, char mode) {
  AI_SetType(me, AIT_EVADER1);

  switch (memory->mode) {
  case HELLION_MATTER:
  case HELLION_ENERGY:
  case HELLION_FIRE:
  case HELLION_SLEEP:
    memory->next_mode = mode;
    mode = HELLION_BETWEEN_MODE;
    break;
  }

  switch (mode) {
  case HELLION_BETWEEN_MODE: {
    RemapAlert(me, 1.0f, 10.0f, 1.0f);

    int flags = AIF_DISABLE_FIRING;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    switch (memory->mode) {
    case HELLION_MATTER:
      Obj_SetCustomAnim(me, 120.0f, 140.0f, 2.5f, AIAF_NOTIFY, Sound_FindId("RbtHellionMatterToAlert"), AS_ALERT);
      break;
    case HELLION_ENERGY:
      Obj_SetCustomAnim(me, 200.0f, 240.0f, 5.0f, AIAF_NOTIFY, Sound_FindId("RbtHellionEnergyToAlert"), AS_ALERT);
      break;
    case HELLION_FIRE:
      Obj_SetCustomAnim(me, 62.0f, 80.0f, 2.3f, AIAF_NOTIFY, Sound_FindId("RbtHellionNapalmToAlert"), AS_ALERT);
      break;
    case HELLION_SLEEP:
      Obj_SetCustomAnim(me, 338.0f, 353.0f, 1.7f, AIAF_NOTIFY, -1, AS_ALERT);
      break;
    }
  } break;

  case HELLION_MATTER:
    RemapAlert(me, 375.0f, 384.0f, 1.0f);
    RemapWB(me, 100.0f, 120.0f, Sound_FindId("fragA2"), 120.0f, 2.5f, 0.5f, 0, Wpn_FindID("HellionFrag"),
            (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4));
    strcpy(memory->sound, "fragA2");
    strcpy(memory->weapon, "HellionFrag");
    Obj_SetCustomAnim(me, 80.0f, 100.0f, 2.7f, AIAF_NOTIFY, Sound_FindId("RbtHellionAlertToMatter"), AS_ALERT);
    break;
  case HELLION_FIRE:
    RemapAlert(me, 360.0f, 369.0f, 1.0f);
    RemapWB(me, 48.0f, 62.0f, -1, 62.0f, 2.0f, 0.1f, 0, -1, 0);
    Obj_SetCustomAnim(me, 10.0f, 48.0f, 5.0f, AIAF_NOTIFY, Sound_FindId("RbtHellionAlertToNapalm"), AS_ALERT);
    break;
  case HELLION_ENERGY:
    RemapAlert(me, 390.0f, 400.0f, 1.0f);
    RemapWB(me, 179.0f, 200.0f, Sound_FindId("Mega missile fire"), 200.0f, 2.7f, 0.9f, 0, Wpn_FindID("HellionMega"),
            (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4));
    strcpy(memory->sound, "Mega missile fire");
    strcpy(memory->weapon, "HellionMega");
    Obj_SetCustomAnim(me, 140.0f, 179.0f, 5.0f, AIAF_NOTIFY, Sound_FindId("RbtHellionAlertToEnergy"), AS_ALERT);
    break;
  case HELLION_SLEEP:
    RemapAlert(me, 271.0f, 289.0f, 2.5);
    Obj_SetCustomAnim(me, 240.0f, 271.0f, 4.0f, AIAF_NOTIFY, -1, AS_ALERT);
    break;
  case HELLION_BIRTHING:
    Obj_SetCustomAnim(me, 289.0f, 338.0f, 6.5f, AIAF_NOTIFY, -1, AS_ALERT);
    break;
  case HELLION_DEATH: {
    int flags = AIF_DISABLE_FIRING | AIF_DISABLE_MELEE;
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
    flags = AIF_FIRE;
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    vector vel = {0.0f, 0.0f, 0.0f};
    Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &vel);

    float circle_dist = -1.0f;
    AI_Value(me, VF_SET, AIV_F_CIRCLE_DIST, &circle_dist);

    Obj_SetCustomAnim(me, 495.0f, 650.0f, 15.0f, 0, Sound_FindId("RbtHellionDeath"), -1);
  } break;
  default:
    break;
  }

  memory->mode_time = 0.0f;
  memory->mode = mode;
}

void Hellion::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(hellion_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;
  int i;

  memory = (hellion_data *)Scrpt_MemAlloc(&ch);
  memory->flags = 0;
  memory->mode = HELLION_WAIT;

  memory->head_object = CreateAndAttach(me, "Hellionhead", OBJ_ROBOT, 0, 0, true, true);
  memory->turret_object = CreateAndAttach(me, "Hellionturret", OBJ_ROBOT, 1, 0, true, true);
  RemapAlert(me, 1.0f, 10.0f, 1.0f);

  int proom;
  vector ppos;
  matrix porient;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &proom);
  Obj_Value(me, VF_GET, OBJV_V_POS, &ppos);
  Obj_Value(me, VF_GET, OBJV_M_ORIENT, &porient);

  for (i = 0; i < 2; i++) {
    memory->camera[i] = Obj_Create(OBJ_POWERUP, Obj_FindID("Invisiblepowerup"), proom, &ppos, &porient, me);
    msafe_struct mstruct;
    mstruct.objhandle = memory->camera[i];
    MSafe_CallFunction(MSAFE_OBJECT_NO_RENDER, &mstruct);

    memory->emitter[i] = CreateAndAttach(me, "STEmitter", OBJ_ROBOT, 2 + i, 0, true, true);
  }

  memory->laser_sound = -1;
  memory->last_frame = 0.0f;
  memory->laser_time_left = 0.0f;

  // Save and restore information
  Obj_Value(me, VF_GET, OBJSV_F_ANIM_START, &memory->alert_start, AS_ALERT);
  Obj_Value(me, VF_GET, OBJSV_F_ANIM_END, &memory->alert_end, AS_ALERT);
  Obj_Value(me, VF_GET, OBJSV_F_ANIM_TIME, &memory->alert_time, AS_ALERT);

  Obj_WBValue(me, 0, VF_GET, WBSV_F_ANIM_START, &memory->start, 0);
  Obj_WBValue(me, 0, VF_GET, WBSV_F_ANIM_FIRE, &memory->fire, 0);
  Obj_WBValue(me, 0, VF_GET, WBSV_F_ANIM_END, &memory->end, 0);
  Obj_WBValue(me, 0, VF_GET, WBSV_F_ANIM_TIME, &memory->time, 0);
  Obj_WBValue(me, 0, VF_GET, WBSV_F_LATENCY, &memory->latency, 0);
  Obj_WBValue(me, 0, VF_GET, WBSV_C_MASK, &memory->f_mask, 0);
  memory->index = 0;

  strcpy(memory->sound, "fragA2");
  strcpy(memory->weapon, "HellionFrag");
  // end of save and restore info

  int flags = AIF_DETERMINE_TARGET;
  AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

  SetMode(me, HELLION_WAIT);
}

void Hellion::DoFrame(int me) {
  int flags;
  float frame;
  float shields;

  char anim_type;
  AI_Value(me, VF_GET, AIV_C_ANIMATION_TYPE, &anim_type);

  bool f_ok_to_animate = (anim_type != AS_RANGED_ATTACK && anim_type != AS_MELEE1 && anim_type != AS_MELEE2);

  Obj_Value(memory->head_object, VF_GET, OBJV_I_FLAGS, &flags);
  Obj_Value(me, VF_GET, OBJV_F_ANIM_FRAME, &frame);
  Obj_Value(memory->head_object, VF_GET, OBJV_F_SHIELDS, &shields);

  // Matter fire animation sound
  if ((memory->last_frame < 100.0f || memory->last_frame > 120.0f) && frame >= 100.0f && frame <= 120.0f) {
    Sound_Play3d(me, Sound_FindId("RbtHellionMatterAttack"));
  }

  if (memory->laser_sound != -1 && (frame < 48.0f || frame > 60.0f)) {
    memory->laser_sound = -1;
  }

  // Laser firing sound
  if (frame >= 48.0f && frame <= 60.0f && memory->laser_sound == -1) {
    memory->laser_sound = Sound_Play3d(me, Sound_FindId("RbtHellionLaser"));
  }

  int cur_mtype;
  Obj_Value(me, VF_GET, OBJV_C_MOVEMENT_TYPE, &cur_mtype);

  if (cur_mtype == MT_PHYSICS && frame >= 140.0 && frame <= 179.0f) {
    char mtype = MT_NONE;
    Obj_Value(me, VF_SET, OBJV_C_MOVEMENT_TYPE, &mtype);
  } else if (cur_mtype == MT_NONE) {
    char mtype = MT_PHYSICS;
    Obj_Value(me, VF_SET, OBJV_C_MOVEMENT_TYPE, &mtype);
  }

  if (memory->last_frame >= 140.0f && memory->last_frame <= 179.0f && memory->last_frame < 146.0f && frame >= 146.0f) {
    matrix orient;
    Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

    int room;
    vector pos;
    int weapon_id;

    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

    pos += orient.uvec * 10.0f;

    matrix new_orient;

    new_orient.fvec = -orient.uvec;
    new_orient.rvec = orient.rvec;
    new_orient.uvec = orient.fvec;

    weapon_id = Wpn_FindID("HellionBShark");
    Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, &new_orient, OBJECT_HANDLE_NONE);
  }

  if (memory->last_frame >= 140.0f && memory->last_frame <= 179.0f && memory->last_frame < 160.0f && frame >= 160.0f) {
    // shake players
    msafe_struct mstruct;
    mstruct.amount = 65.0f;
    MSafe_CallFunction(MSAFE_OBJECT_VIEWER_SHAKE, &mstruct);
  }

  if (memory->laser_time_left > 0.0f) {
    int i;
    ray_info ray;

    memory->laser_time_left -= Game_GetFrameTime();
    if (memory->laser_time_left < 0.0f) {
      memory->laser_time_left = 0.0f;
    }

    vector normal;
    vector pos;
    int room;
    vector end_pos;

    for (i = 0; i < 2; i++) {
      int my_room;
      vector my_pos;

      Obj_Value(me, VF_GET, OBJV_V_POS, &my_pos);
      Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &my_room);
      Obj_GetGunPos(me, i + 1, &pos, &normal);

      int rfate = FVI_RayCast(me, &my_pos, &pos, my_room, 0.0f, 0, &ray);
      room = ray.hit_room;

      matrix orient;
      Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

      // Determine real start pos - room
      vector end_pos = pos;
      end_pos += normal * 2000.0f;

      int fvi_flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS;
      int fate = FVI_RayCast(me, &pos, &end_pos, room, 0.0f, fvi_flags, &ray);

      Obj_Value(memory->camera[i], VF_SET, OBJV_V_POS, &ray.hit_point);
      Obj_Value(memory->camera[i], VF_SET, OBJV_I_ROOMNUM, &ray.hit_room);

      msafe_struct mstruct;

      mstruct.random = 21;
      mstruct.is_real = 0;
      mstruct.objhandle = memory->camera[i];
      mstruct.gunpoint = -1;
      mstruct.effect_type = SNOWFLAKE_INDEX;
      mstruct.phys_info = 0;
      mstruct.drag = .001f;
      mstruct.mass = .001f;
      mstruct.interval = .05f;
      mstruct.longevity = .1f;
      mstruct.lifetime = .1f;
      mstruct.size = 5.0f;
      mstruct.speed = 80.0;

      MSafe_CallFunction(MSAFE_OBJECT_START_SPEW, &mstruct);

      if (fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) {
        int type;

        Obj_Value(ray.hit_object, VF_GET, OBJV_I_TYPE, &type);

        if (type == OBJ_PLAYER) {
          msafe_struct mstruct;

          mstruct.objhandle = ray.hit_object;
          mstruct.killer_handle = me;
          mstruct.damage_type = PD_ENERGY_WEAPON;
          mstruct.amount = 30.0f * Game_GetFrameTime();

          MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
        }
      }
    }
  }

  // Start up the beem!
  if (frame >= 49.0f && frame <= 55.0f && memory->laser_time_left == 0.0f) {
    memory->laser_time_left = 1.8f;
    int i;
    msafe_struct mstruct;

    for (i = 0; i < 2; i++) {
      Obj_Value(memory->emitter[i], VF_GET, OBJV_I_ROOMNUM, &mstruct.roomnum);
      Obj_Value(memory->emitter[i], VF_GET, OBJV_V_POS, &mstruct.pos);
      Obj_Value(memory->camera[i], VF_GET, OBJV_V_POS, &mstruct.pos2);

      mstruct.objhandle = memory->emitter[i];
      mstruct.ithandle = memory->camera[i];
      mstruct.lifetime = memory->laser_time_left;
      mstruct.size = 3.0f;

      mstruct.interval = 1.0f;
      mstruct.count = 2;
      mstruct.index = 1;
      mstruct.texnum = Scrpt_FindTextureName("HellionBeam");
      mstruct.color = ((128 >> 3) << 10) | ((128 >> 3) << 5) | (128 >> 3);

      mstruct.state = 1;
      mstruct.flags = 0;

      MSafe_CallFunction(MSAFE_WEATHER_LIGHTNING_BOLT, &mstruct);

      mstruct.random = 21;
      mstruct.is_real = 0;
      mstruct.objhandle = me;
      mstruct.gunpoint = 1 + i;
      mstruct.effect_type = MED_SMOKE_INDEX;
      mstruct.phys_info = 0;
      mstruct.drag = .001f;
      mstruct.mass = .001f;
      mstruct.interval = .05f;
      mstruct.longevity = memory->laser_time_left;
      mstruct.lifetime = 1.0;
      mstruct.size = 5.0f;
      mstruct.speed = 80.0;

      MSafe_CallFunction(MSAFE_OBJECT_START_SPEW, &mstruct);
    }
  }

  if ((memory->mode != HELLION_DEATH) && (flags & OF_AI_DEATH)) {
    if (f_ok_to_animate) {
      SetMode(me, HELLION_DEATH);
    }
  }

  if (memory->mode == HELLION_WAIT) {
  } else if (memory->mode == HELLION_INTRO) {
    if (memory->mode_time < 0.5f && memory->mode_time + Game_GetFrameTime() >= 0.5f) {
      int flags = AIF_FORCE_AWARENESS;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      float awareness = AWARE_FULLY;
      AI_Value(me, VF_SET, AIV_F_AWARENESS, &awareness);

      aDestroyAllRobotsInit();
      aDestroyAllRobotsSpareHandle(me);
      aDestroyAllRobotsSpareHandle(memory->turret_object);
      aDestroyAllRobotsSpareHandle(memory->head_object);
      aDestroyAllRobotsSpareHandle(memory->emitter[0]);
      aDestroyAllRobotsSpareHandle(memory->emitter[1]);
      aDestroyAllRobotsEnd();
    }
  } else if (memory->mode == HELLION_BETWEEN_MODE) {
    if (frame >= 0.0f && frame <= 10.0f) {
      SetMode(me, memory->next_mode);
    }
  } else if (memory->mode == HELLION_DEATH) {
    if (memory->mode_time < 10.0f && memory->mode_time + Game_GetFrameTime() >= 10.0f) {
      Obj_Burning(me, 1000000.0f, 1.0f);
    }

    if (frame == 650.0f) {
      Obj_Kill(me, OBJECT_HANDLE_NONE, 1000.0f,
               DF_BREAKS_APART | DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_CONTACT_BREAKS_APART |
                   DF_CONTACT_BLAST_RING | DF_DEBRIS_SMOKES | DF_DEBRIS_FIREBALL | DF_DEBRIS_BLAST_RING,
               0.0f, 0.0f);
    }
  } else if (memory->mode == HELLION_MATTER) {
    if (frame >= 375.0f && frame <= 384.0f) {
      int flags = AIF_DETERMINE_TARGET;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      flags = AIF_DISABLE_FIRING;
      AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    }

    if (shields < 4000.0f) {
      if (f_ok_to_animate) {
        SetMode(me, HELLION_FIRE);
      }
    }
  } else if (memory->mode == HELLION_FIRE) {
    if (frame >= 360.0f && frame <= 369.0f) {
      int flags = AIF_DISABLE_FIRING;
      AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
    }

    if (shields < 2100.0f) {
      if (f_ok_to_animate) {
        SetMode(me, HELLION_ENERGY);
      }
    }
  } else if (memory->mode == HELLION_ENERGY) {
    if (frame >= 390.0f && frame <= 400.0f) {
      int test_flags;
      AI_Value(me, VF_GET, AIV_I_FLAGS, &test_flags);

      if (test_flags & AIF_DISABLE_FIRING) {
        int flags = AIF_DISABLE_FIRING;
        AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

        /*				int room;
                                        vector pos;
                                        int weapon_id;

                                        Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
                                        Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

                                        weapon_id = Wpn_FindID("HellionBShark");
                                        Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, NULL);*/
      }
    }
  }
  //	else if(memory->mode == HELLION_SLEEP)
  //	{
  //		int offset = (memory->mode - HELLION_MATTER + 1)%4;
  //		SetMode(me, HELLION_MATTER + offset);
  //	}
  else if (memory->mode_time > 20.0f) {
    if (memory->mode == HELLION_MATTER || memory->mode == HELLION_ENERGY || memory->mode == HELLION_FIRE ||
        memory->mode == HELLION_SLEEP) {
      int offset = (memory->mode - HELLION_MATTER + 1) % 4;
      SetMode(me, HELLION_MATTER + offset);
    }
  }

  memory->mode_time += Game_GetFrameTime();
  memory->last_frame = frame;
}

int16_t Hellion::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
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

    Obj_Kill(memory->head_object, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES, 0.0f,
             0.0f);
    Obj_Kill(memory->turret_object, OBJECT_HANDLE_NONE, 1000.0f,
             DF_BLAST_RING | DF_LOSES_ANTIGRAV | DF_EXPL_LARGE | DF_FIREBALL | DF_BREAKS_APART | DF_DEBRIS_SMOKES, 0.0f,
             0.0f);

    int i;
    msafe_struct mo;

    for (i = 0; i < 2; i++) {
      mo.objhandle = memory->camera[i];
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);

      mo.objhandle = memory->emitter[i];
      MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
    }
  } break;
  case EVT_MEMRESTORE: {
    memory = (hellion_data *)data->evt_memrestore.memory_ptr;

    uint16_t wpn = Wpn_FindID(memory->weapon);
    int snd = Sound_FindId(memory->sound);

    RemapAlert(data->me_handle, memory->alert_start, memory->alert_end, memory->alert_time);
    RemapWB(data->me_handle, memory->start, memory->fire, snd, memory->end, memory->time, memory->latency,
            memory->index, wpn, memory->f_mask);
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// MantaRay class
//------------------

bool MantaRay::SendCommand(int me, int it, char command, void *ptr) {
  gb_com com;

  com.action = command;
  com.ptr = ptr;

  tOSIRISEventInfo ei;

  ei.me_handle = it;
  ei.extra_info = (void *)&com;
  ei.evt_ai_notify.notify_type = AIN_USER_DEFINED;
  ei.evt_ai_notify.it_handle = me;

  return Obj_CallEvent(it, EVT_AI_NOTIFY, &ei);
}

bool MantaRay::ReceiveCommand(int me, int it, char command, void *ptr) {
  switch (command) {
  case MRC_JOIN_ME: {
    if (memory->flags == 0) {
      memory->leader_handle = it;
      memory->flags |= MRF_SQUADIE;

      SetMode(me, memory->mode);

      return true;
    }
  } break;
  case MRC_LEAVE_YOU:
    break;
  case MRC_GET_GOAL_POS: {
    int i;
    for (i = 0; i < memory->num_teammates; i++) {
      if (memory->teammate[i] == it) {
        vector goal_pos;
        matrix orient;
        Obj_Value(me, VF_GET, OBJV_V_POS, &goal_pos);
        Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

        switch (i) {
        case 0:
          goal_pos -= orient.fvec * MRO_FVEC;
          goal_pos -= orient.rvec * MRO_RVEC;
          break;
        case 1:
          goal_pos -= orient.fvec * MRO_FVEC;
          goal_pos += orient.rvec * MRO_RVEC;
          break;
        case 2:
          goal_pos -= orient.fvec * MRO_FVEC * 2.0f;
          goal_pos -= orient.rvec * MRO_RVEC * 2.0f;
          break;
        case 3:
          goal_pos -= orient.fvec * MRO_FVEC * 2.0f;
          goal_pos += orient.rvec * MRO_RVEC * 2.0f;
          break;
        }

        *(vector *)ptr = goal_pos;
        return true;
      }
    }
  } break;
  case MRC_GET_GOAL_ROOM: {
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, (int *)ptr);
    return true;
  } break;
  case MRC_GET_GOAL_ORIENT: {
    return true;
  } break;
  }

  //	mprintf(0, "MantaRay action %d failed\n");
  return false;
}

void MantaRay::UpdateSquadList(int me) {
  int i;

  for (i = 0; i < memory->num_teammates; i++) {
    int type;
    int j;

    Obj_Value(memory->teammate[i], VF_GET, OBJV_I_TYPE, &type);
    if (type == OBJ_NONE) {
      for (j = i; j < memory->num_teammates - 1; j++) {
        memory->teammate[j] = memory->teammate[j + 1];
      }

      memory->num_teammates--;
      i--;
    }
  }
}

void MantaRay::UpdateSquad(int me) {
  if (memory->flags & MRF_SQUADIE)
    return;

  if (memory->flags & MRF_LEADER) {
    UpdateSquadList(me);

    if (memory->num_teammates == 0)
      memory->flags &= ~MRF_LEADER;

    if (memory->num_teammates >= MR_MAX_TEAMMATES)
      return;
  }

  int scan_objs[25];
  int n_scan;
  int room;
  vector pos;
  int i;

  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

  n_scan = AI_GetNearbyObjs(&pos, room, 200.0f, scan_objs, 25, false, true, false, true);

  for (i = 0; i < n_scan; i++) {
    uint16_t id;
    Obj_Value(scan_objs[i], VF_GET, OBJV_US_ID, &id);

    // this is more rare than the types matching; so, do it first
    if (id == memory->mantaray_id) {
      int type;
      Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);
      if (type == OBJ_ROBOT && scan_objs[i] != me) {
        bool f_on_team = false;
        if (memory->flags & MRF_LEADER) {
          int j;
          for (j = 0; j < memory->num_teammates; j++) {
            if (scan_objs[i] == memory->teammate[j]) {
              f_on_team = true;
              break;
            }
          }
        }

        if (!f_on_team) {
          if (SendCommand(me, scan_objs[i], MRC_JOIN_ME, NULL)) {
            memory->flags |= MRF_LEADER;
            memory->teammate[memory->num_teammates++] = scan_objs[i];
          }
        }
      }
    }

    if (memory->num_teammates >= MR_MAX_TEAMMATES)
      return;
  }
}

void MantaRay::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(mantaray_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (mantaray_data *)Scrpt_MemAlloc(&ch);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  memory->attack_speed = 1.8f * memory->base_speed;

  memory->flags = 0;
  memory->leader_handle = OBJECT_HANDLE_NONE;
  memory->num_teammates = 0;

  // .1 to .6 seconds into the level, do the first matching
  memory->next_update_squad_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * .5f + 0.1f;

  memory->mantaray_id = Obj_FindID("Manta Ray");

  SetMode(me, MRM_NORMAL);
}

void MantaRay::SetMode(int me, char mode) {
  int f_attack_flags = (AIF_FIRE | AIF_AUTO_AVOID_FRIENDS);
  AI_SetType(me, AIT_AIS);

  if (memory->flags & MRF_SQUADIE) {
    // The leader is alive; so, get my new goal pos
    SendCommand(me, memory->leader_handle, MRC_GET_GOAL_POS, &memory->goal_pos);
    AI_GoalValue(me, 2, VF_SET, AIGV_V_POS, &memory->goal_pos);
    SendCommand(me, memory->leader_handle, MRC_GET_GOAL_ROOM, &memory->goal_room);
    AI_GoalValue(me, 2, VF_SET, AIGV_I_ROOMNUM, &memory->goal_room);

    AI_AddGoal(me, AIG_GET_TO_POS, 2, 1.0f, -1, GF_ORIENT_VELOCITY | GF_KEEP_AT_COMPLETION, &memory->goal_pos,
               memory->goal_room);
    float cd = .1f;
    AI_GoalValue(me, 2, VF_SET, AIGV_F_CIRCLE_DIST, &cd);
  } else {
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
  }

  switch (mode) {
  case MRM_NORMAL: {
    vector pos;
    int room = 0;
    float dist = 15.0f;

    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &f_attack_flags);
    AI_AddGoal(me, AIG_WANDER_AROUND, 1, 1.0f, -1, GF_ORIENT_VELOCITY | GF_NOTIFIES | GF_KEEP_AT_COMPLETION, &pos,
               room);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;

  case MRM_ATTACK: {
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    //			memory->next_attack_time = Game_GetTime() + 10.0 * ((float)rand()/(float)RAND_MAX);

    float dist = 60.0f + ((float)rand() / (float)RAND_MAX) * 10.0f;
    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1,
               GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_USE_BLINE_IF_SEES_GOAL | GF_KEEP_AT_COMPLETION |
                   GF_NONFLUSHABLE,
               OBJECT_HANDLE_NONE);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    dist = 10.0f;
    int g_index =
        AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1,
                   GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;

  case MRM_ATTACK_CIRCLE_BACK: {
    vector pos;
    int room = 0;

    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    if (!(memory->flags & MRF_SQUADIE)) {
      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->attack_speed);
    }

    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

    float dist = 10.0f;

    AI_AddGoal(me, AIG_WANDER_AROUND, 1, 1.0f, -1,
               GF_NOTIFIES | GF_ORIENT_VELOCITY | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE, &pos, room);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    int g_index =
        AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1,
                   GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;
  }

  memory->mode = mode;
  memory->mode_time = 0.0f;
}

void MantaRay::DoSquadieFrame(int me) {
  int type;
  Obj_Value(memory->leader_handle, VF_GET, OBJV_I_TYPE, &type);

  // Check if the leader is still alive
  if (type == OBJ_NONE) {
    // Reset the speed
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);

    memory->flags = 0;
    memory->leader_handle = OBJECT_HANDLE_NONE;

    SetMode(me, MRM_NORMAL);
    return;
  }

  // The leader is alive; so, get my new goal pos
  SendCommand(me, memory->leader_handle, MRC_GET_GOAL_POS, &memory->goal_pos);
  AI_GoalValue(me, 2, VF_SET, AIGV_V_POS, &memory->goal_pos);
  SendCommand(me, memory->leader_handle, MRC_GET_GOAL_ROOM, &memory->goal_room);
  AI_GoalValue(me, 2, VF_SET, AIGV_I_ROOMNUM, &memory->goal_room);

  AI_AddGoal(me, AIG_GET_TO_POS, 2, 1.0f, -1, GF_ORIENT_VELOCITY | GF_KEEP_AT_COMPLETION, &memory->goal_pos,
             memory->goal_room);
  float cd = .1f;
  AI_GoalValue(me, 2, VF_SET, AIGV_F_CIRCLE_DIST, &cd);

  vector my_pos;
  Obj_Value(me, VF_GET, OBJV_V_POS, &my_pos);

  float dist = vm_VectorDistance(&my_pos, &memory->goal_pos);

  if (dist <= MRO_CATCHUP_DIST) {
    float catchup_speed;
    AI_Value(memory->leader_handle, VF_GET, AIV_F_MAX_SPEED, &catchup_speed);

    float scaled_speed = dist / MRO_CATCHUP_DIST * 0.23f * catchup_speed;
    catchup_speed += scaled_speed;

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &catchup_speed);
  } else if (dist > MRO_CATCHUP_DIST) {
    float catchup_speed;
    AI_Value(memory->leader_handle, VF_GET, AIV_F_MAX_SPEED, &catchup_speed);

    float scaled_speed = 0.23f * catchup_speed;
    catchup_speed += scaled_speed;

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &catchup_speed);
  }

  // Get the leaders mode

  // Set my mode to the leaders mode...  (Modes account for flags)
}

void MantaRay::DoFrame(int me) {
  float last_see_target_time;
  float last_hear_target_time;
  AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_target_time);
  AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &last_hear_target_time);

  // Periodically update the squad information
  if (memory->next_update_squad_time <= Game_GetTime()) {
    // 3 to 6 seconds
    memory->next_update_squad_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * 3.0f + 3.0f;
    UpdateSquad(me);
  }

  // If your a squadie, check for a leader
  if (memory->flags & MRF_SQUADIE) {
    DoSquadieFrame(me);
  }

  //	if(memory->flags & MRF_LEADER)
  //	{
  //		vector pos;
  //		Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
  //		vector gpos;
  //		int groom;

  //		float cd;
  //		AI_GoalValue(me, 1, VF_GET, AIGV_I_ROOMNUM, &groom);
  //		AI_GoalValue(me, 1, VF_GET, AIGV_V_POS, &gpos);
  //		AI_GoalValue(me, 1, VF_GET, AIGV_F_CIRCLE_DIST, &cd);
  //		mprintf(0, "%f,%f,%f-%f,%f,%f-%f\n", XYZ(&gpos), XYZ(&pos), cd);
  //	}

  switch (memory->mode) {
  case MRM_ATTACK: {
    //				mprintf(0, "MODE ATTACK\n");
    if (Game_GetTime() > last_see_target_time + 7.0f && Game_GetTime() > last_hear_target_time + 7.0f)
      SetMode(me, MRM_NORMAL);
    //
    //			float dist;
    //			AI_GoalValue(me, 1, VF_GET, AIGV_F_DIST_TO_GOAL, &dist);
  } break;

  case MRM_ATTACK_CIRCLE_BACK: {
    //				mprintf(0, "MODE CBACK\n");
    if (Game_GetTime() > last_see_target_time + 7.0f && Game_GetTime() > last_hear_target_time + 7.0f)
      SetMode(me, MRM_NORMAL);

    if (memory->mode_time > 5.5f)
      SetMode(me, MRM_ATTACK);
  } break;

  case MRM_NORMAL: {
    //			mprintf(0, "MODE NORMAL\n");
    if (Game_GetTime() < last_see_target_time + 7.0f && Game_GetTime() < last_hear_target_time + 7.0f)
      SetMode(me, MRM_ATTACK);
  } break;
  }

  memory->mode_time += Game_GetFrameTime();
}

bool MantaRay::DoNotify(int me, tOSIRISEventInfo *data) {
  if (IsGoalFinishedNotify(data->evt_ai_notify.notify_type)) {
    switch (memory->mode) {
    case MRM_ATTACK:
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, MRM_ATTACK_CIRCLE_BACK);
        return false;
      }
      break;
    case MRM_ATTACK_CIRCLE_BACK:
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, MRM_ATTACK);
        return false;
      }
      break;
    }
  } else if (data->evt_ai_notify.notify_type == AIN_USER_DEFINED) {
    gb_com *com = (gb_com *)data->extra_info;

    return ReceiveCommand(me, data->evt_ai_notify.it_handle, com->action, com->ptr);
  }

  return true;
}

int16_t MantaRay::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (mantaray_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Skiff class
//------------------

bool Skiff::SendCommand(int me, int it, char command, void *ptr) {
  gb_com com;

  com.action = command;
  com.ptr = ptr;

  tOSIRISEventInfo ei;

  ei.me_handle = it;
  ei.extra_info = (void *)&command;
  ei.evt_ai_notify.notify_type = AIN_USER_DEFINED;
  ei.evt_ai_notify.it_handle = me;

  return Obj_CallEvent(it, EVT_AI_NOTIFY, &ei);
}

bool Skiff::ReceiveCommand(int me, int it, char command, void *ptr) {
  switch (command) {
  case MRC_JOIN_ME: {
    if (memory->flags == 0) {
      memory->leader_handle = it;
      memory->flags |= MRF_SQUADIE;

      SetMode(me, memory->mode);

      return true;
    }
  } break;
  case MRC_LEAVE_YOU:
    break;
  case MRC_GET_GOAL_POS: {
    int i;
    for (i = 0; i < memory->num_teammates; i++) {
      if (memory->teammate[i] == it) {
        vector goal_pos;
        matrix orient;
        Obj_Value(me, VF_GET, OBJV_V_POS, &goal_pos);
        Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

        switch (i) {
        case 0:
          goal_pos -= orient.fvec * MRO_FVEC;
          goal_pos -= orient.rvec * MRO_RVEC;
          break;
        case 1:
          goal_pos -= orient.fvec * MRO_FVEC;
          goal_pos += orient.rvec * MRO_RVEC;
          break;
        case 2:
          goal_pos -= orient.fvec * MRO_FVEC * 2.0f;
          goal_pos -= orient.rvec * MRO_RVEC * 2.0f;
          break;
        case 3:
          goal_pos -= orient.fvec * MRO_FVEC * 2.0f;
          goal_pos += orient.rvec * MRO_RVEC * 2.0f;
          break;
        }

        *(vector *)ptr = goal_pos;
        return true;
      }
    }
  } break;
  case MRC_GET_GOAL_ROOM: {
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, (int *)ptr);
    return true;
  } break;
  case MRC_GET_GOAL_ORIENT: {
    return true;
  } break;
  }

  //	mprintf(0, "Skiff action %d failed\n");
  return false;
}

void Skiff::UpdateSquadList(int me) {
  int i;

  for (i = 0; i < memory->num_teammates; i++) {
    int type;
    int j;

    Obj_Value(memory->teammate[i], VF_GET, OBJV_I_TYPE, &type);
    if (type == OBJ_NONE) {
      for (j = i; j < memory->num_teammates - 1; j++) {
        memory->teammate[j] = memory->teammate[j + 1];
      }

      memory->num_teammates--;
      i--;
    }
  }
}

void Skiff::UpdateSquad(int me) {
  if (memory->flags & MRF_SQUADIE)
    return;

  if (memory->flags & MRF_LEADER) {
    UpdateSquadList(me);

    if (memory->num_teammates == 0)
      memory->flags &= ~MRF_LEADER;

    if (memory->num_teammates >= MR_MAX_TEAMMATES)
      return;
  }

  int scan_objs[25];
  int n_scan;
  int room;
  vector pos;
  int i;

  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

  n_scan = AI_GetNearbyObjs(&pos, room, 200.0f, scan_objs, 25, false, true, false, true);

  for (i = 0; i < n_scan; i++) {
    uint16_t id;
    Obj_Value(scan_objs[i], VF_GET, OBJV_US_ID, &id);

    // this is more rare than the types matching; so, do it first
    if (id == memory->skiff_id) {
      int type;
      Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);
      if (type == OBJ_ROBOT && scan_objs[i] != me) {
        bool f_on_team = false;
        if (memory->flags & MRF_LEADER) {
          int j;
          for (j = 0; j < memory->num_teammates; j++) {
            if (scan_objs[i] == memory->teammate[j]) {
              f_on_team = true;
              break;
            }
          }
        }

        if (!f_on_team) {
          if (SendCommand(me, scan_objs[i], MRC_JOIN_ME, NULL)) {
            memory->flags |= MRF_LEADER;
            memory->teammate[memory->num_teammates++] = scan_objs[i];
          }
        }
      }
    }

    if (memory->num_teammates >= MR_MAX_TEAMMATES)
      return;
  }
}

void Skiff::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(skiff_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (skiff_data *)Scrpt_MemAlloc(&ch);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  memory->attack_speed = 1.6f * memory->base_speed;

  memory->flags = 0;
  memory->leader_handle = OBJECT_HANDLE_NONE;
  memory->num_teammates = 0;

  // .1 to .6 seconds into the level, do the first matching
  memory->next_update_squad_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * .5f + 0.1f;

  memory->skiff_id = Obj_FindID("Skiff");

  SetMode(me, MRM_NORMAL);
}

void Skiff::SetMode(int me, char mode) {
  int f_attack_flags = (AIF_FIRE | AIF_AUTO_AVOID_FRIENDS);
  AI_SetType(me, AIT_AIS);

  AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);

  switch (mode) {
  case MRM_NORMAL: {
    vector pos;
    int room = 0;
    float dist = 15.0f;

    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &f_attack_flags);
    AI_AddGoal(me, AIG_WANDER_AROUND, 1, 1.0f, -1, GF_ORIENT_VELOCITY | GF_NOTIFIES | GF_KEEP_AT_COMPLETION, &pos,
               room);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;

  case MRM_ATTACK: {
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    //			memory->next_attack_time = Game_GetTime() + 10.0 * ((float)rand()/(float)RAND_MAX);

    float dist = 60.0f + ((float)rand() / (float)RAND_MAX) * 10.0f;
    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1,
               GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_USE_BLINE_IF_SEES_GOAL | GF_KEEP_AT_COMPLETION |
                   GF_NONFLUSHABLE,
               OBJECT_HANDLE_NONE);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    dist = 10.0f;
    int g_index =
        AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1,
                   GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;

  case MRM_ATTACK_CIRCLE_BACK: {
    vector pos;
    int room = 0;

    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    Obj_Value(me, VF_GET, OBJV_V_POS, &pos);
    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);

    float dist = 10.0f;

    AI_AddGoal(me, AIG_WANDER_AROUND, 1, 1.0f, -1,
               GF_NOTIFIES | GF_ORIENT_VELOCITY | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE, &pos, room);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    int g_index =
        AI_AddGoal(me, AIG_GET_AROUND_OBJ, ACTIVATION_BLEND_LEVEL, 1.0f, -1,
                   GF_ORIENT_VELOCITY | GF_OBJ_IS_TARGET | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, g_index, VF_SET, AIGV_F_CIRCLE_DIST, &dist);

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->attack_speed);
  } break;
  }

  if (memory->flags & MRF_SQUADIE) {
    // The leader is alive; so, get my new goal pos
    SendCommand(me, memory->leader_handle, MRC_GET_GOAL_POS, &memory->goal_pos);
    AI_GoalValue(me, 2, VF_SET, AIGV_V_POS, &memory->goal_pos);
    SendCommand(me, memory->leader_handle, MRC_GET_GOAL_ROOM, &memory->goal_room);
    AI_GoalValue(me, 2, VF_SET, AIGV_I_ROOMNUM, &memory->goal_room);

    AI_AddGoal(me, AIG_GET_TO_POS, 2, 4.0f, -1, GF_ORIENT_VELOCITY | GF_KEEP_AT_COMPLETION | GF_NONFLUSHABLE,
               &memory->goal_pos, memory->goal_room);
  }

  memory->mode = mode;
  memory->mode_time = 0.0f;
}

void Skiff::DoSquadieFrame(int me) {
  int type;
  Obj_Value(memory->leader_handle, VF_GET, OBJV_I_TYPE, &type);

  // Check if the leader is still alive
  if (type == OBJ_NONE) {
    if (memory->flags & MRF_CATCHUP) {
      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    }

    memory->flags = 0;
    memory->leader_handle = OBJECT_HANDLE_NONE;

    SetMode(me, MRM_NORMAL);
    return;
  }

  // The leader is alive; so, get my new goal pos
  SendCommand(me, memory->leader_handle, MRC_GET_GOAL_POS, &memory->goal_pos);
  AI_GoalValue(me, 2, VF_SET, AIGV_V_POS, &memory->goal_pos);
  SendCommand(me, memory->leader_handle, MRC_GET_GOAL_ROOM, &memory->goal_room);
  AI_GoalValue(me, 2, VF_SET, AIGV_I_ROOMNUM, &memory->goal_room);

  vector my_pos;
  Obj_Value(me, VF_GET, OBJV_V_POS, &my_pos);

  float dist = vm_VectorDistance(&my_pos, &memory->goal_pos);

  if (dist <= MRO_CATCHUP_DIST) {
    float scaled_speed = dist / MRO_CATCHUP_DIST * 0.18f * memory->base_speed;
    float speed;

    AI_Value(memory->leader_handle, VF_GET, AIV_F_MAX_SPEED, &speed);

    speed += scaled_speed;

    memory->flags &= ~MRF_CATCHUP;
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
  } else if (!(memory->flags & MRF_CATCHUP) && dist > MRO_CATCHUP_DIST) {
    // Between 18% and 23% speed up to get into formation
    float catchup_speed;
    AI_Value(memory->leader_handle, VF_GET, AIV_F_MAX_SPEED, &catchup_speed);
    catchup_speed += (catchup_speed * .18f) + (catchup_speed * .05f * ((float)rand() / (float)RAND_MAX));

    memory->flags |= MRF_CATCHUP;
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &catchup_speed);
  }

  // Get the leaders mode

  // Set my mode to the leaders mode...  (Modes account for flags)
}

void Skiff::DoFrame(int me) {
  float last_see_target_time;
  float last_hear_target_time;
  AI_Value(me, VF_GET, AIV_F_LAST_SEE_TARGET_TIME, &last_see_target_time);
  AI_Value(me, VF_GET, AIV_F_LAST_HEAR_TARGET_TIME, &last_hear_target_time);

  // Periodically update the squad information
  if (memory->next_update_squad_time <= Game_GetTime()) {
    // 3 to 6 seconds
    memory->next_update_squad_time = Game_GetTime() + ((float)rand() / (float)RAND_MAX) * 3.0f + 3.0f;
    //		UpdateSquad(me);
  }

  // If your a squadie, check for a leader
  if (memory->flags & MRF_SQUADIE) {
    DoSquadieFrame(me);
  }

  switch (memory->mode) {
  case MRM_ATTACK: {
    //				mprintf(0, "MODE ATTACK\n");
    if (Game_GetTime() > last_see_target_time + 7.0f && Game_GetTime() > last_hear_target_time + 7.0f)
      SetMode(me, MRM_NORMAL);
    //
    //			float dist;
    //			AI_GoalValue(me, 1, VF_GET, AIGV_F_DIST_TO_GOAL, &dist);
  } break;

  case MRM_ATTACK_CIRCLE_BACK: {
    //				mprintf(0, "MODE CBACK\n");
    if (Game_GetTime() > last_see_target_time + 7.0f && Game_GetTime() > last_hear_target_time + 7.0f)
      SetMode(me, MRM_NORMAL);

    if (memory->mode_time > 4.0f)
      SetMode(me, MRM_ATTACK);
  } break;

  case MRM_NORMAL: {
    //			mprintf(0, "MODE NORMAL\n");
    if (Game_GetTime() < last_see_target_time + 7.0f && Game_GetTime() < last_see_target_time + 7.0f)
      SetMode(me, MRM_ATTACK);
  } break;
  }

  memory->mode_time += Game_GetFrameTime();
}

bool Skiff::DoNotify(int me, tOSIRISEventInfo *data) {
  if (IsGoalFinishedNotify(data->evt_ai_notify.notify_type)) {
    switch (memory->mode) {
    case MRM_ATTACK:
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, MRM_ATTACK_CIRCLE_BACK);
        return false;
      }
      break;
    case MRM_ATTACK_CIRCLE_BACK:
      if (data->evt_ai_notify.goal_num == 1) {
        SetMode(me, MRM_ATTACK);
        return false;
      }
      break;
    }
  } else if (data->evt_ai_notify.notify_type == AIN_USER_DEFINED) {
    gb_com *com = (gb_com *)data->extra_info;

    return ReceiveCommand(me, data->evt_ai_notify.it_handle, com->action, com->ptr);
  }

  return true;
}

int16_t Skiff::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (skiff_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// SpyHunter class
//------------------

void SpyHunter::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(spyhunter_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (spyhunter_data *)Scrpt_MemAlloc(&ch);
  memory->last_attack_mode = SHM_ATTACK;
  memory->f_hit_by_emd = false;
  memory->emd_id = Wpn_FindID("EMDblob");
  memory->tick_sound = Sound_FindId("WpnBmbTickElectricalA");
  memory->last_tick_time = Game_GetTime();

  SetMode(me, SHM_NORMAL);
}

void SpyHunter::SetMode(int me, char mode) {
  AI_SetType(me, AIT_AIS);

  int f_attack_flags = (AIF_FIRE | AIF_AUTO_AVOID_FRIENDS);

  if (memory->mode == SHM_ATTACK || memory->mode == SHM_BOMB_ATTACK) {
    memory->last_attack_mode = memory->mode;
  }

  switch (mode) {
  case SHM_NORMAL: {
    vector pos;
    int room = 0;
    float dist = 5.0f;

    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    // If last see target time > 7.0 orient velocity
    AI_AddGoal(me, AIG_WANDER_AROUND, 1, 1.0f, -1,
               GF_ORIENT_TARGET | GF_KEEP_AT_COMPLETION | GF_FORCE_AWARENESS | GF_NOTIFIES, &pos, room);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;
  case SHM_ATTACK: {
    AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &f_attack_flags);
    AI_SetType(me, AIT_EVADER1);
  } break;
  case SHM_BOMB_ATTACK: {
    float dist = -1000.0f;

    f_attack_flags |= AIF_DODGE; // Bombs don't dodge
    AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &f_attack_flags);

    AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1,
               GF_ORIENT_VELOCITY | GF_KEEP_AT_COMPLETION | GF_OBJ_IS_TARGET | GF_FORCE_AWARENESS, OBJECT_HANDLE_NONE);
    AI_GoalValue(me, 1, VF_SET, AIGV_F_CIRCLE_DIST, &dist);
  } break;
  }

  memory->mode = mode;
  memory->mode_time = 0.0f;
  memory->last_tick_time = Game_GetTime();
  memory->next_summon_time = Game_GetTime() + 5.0f + (float)rand() / (float)RAND_MAX;
}

bool SpyHunter::DoNotify(int me, tOSIRISEventInfo *data) {
  tOSIRISEVTAINOTIFY *notify = &data->evt_ai_notify;

  if ((!memory->f_hit_by_emd) && notify->notify_type == AIN_HIT_BY_WEAPON) {
    int type;
    Obj_Value(notify->it_handle, VF_GET, OBJV_I_TYPE, &type);

    if (type == OBJ_WEAPON) {
      uint16_t id;

      Obj_Value(notify->it_handle, VF_GET, OBJV_US_ID, &id);
      if (id == memory->emd_id) {
        memory->f_hit_by_emd = true;
      }
    }
  }

  if (memory->mode == SHM_NORMAL || (memory->mode == SHM_ATTACK && memory->mode_time > 10.0f)) {
    if ((notify->notify_type == AIN_OBJ_FIRED) || (notify->notify_type == AIN_HIT_BY_WEAPON) ||
        (notify->notify_type == AIN_BUMPED_OBJ)) {
      if (memory->mode == SHM_NORMAL) {
        SetMode(me, SHM_ATTACK);
        return true;
      } else {
        SetMode(me, SHM_BOMB_ATTACK);
        return true;
      }
    }
  }

  if (memory->mode == SHM_BOMB_ATTACK && notify->notify_type == AIN_BUMPED_OBJ) {
    int room;
    vector pos;

    Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_GetGunPos(me, 0, &pos);

    if (!memory->f_hit_by_emd) {
      vector velocity;
      Obj_Value(me, VF_GET, OBJV_V_VELOCITY, &velocity);

      int weapon_id = Wpn_FindID("FragBarrel");
      Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me, &velocity);
    }

    msafe_struct mstruct;

    mstruct.objhandle = me;
    mstruct.killer_handle = OBJECT_HANDLE_NONE;
    mstruct.damage_type = GD_SCRIPTED;
    mstruct.amount = 1000.0f;

    MSafe_CallFunction(MSAFE_OBJECT_DAMAGE_OBJECT, &mstruct);
  }

  return true;
}

void SpyHunter::DoFrame(int me) {
  //	mprintf(0, "Current goal is %d and the ", AI_GetCurGoalIndex(me));

  switch (memory->mode) {
  case SHM_NORMAL: {
    //			int gt = -1;
    //
    //			if(AI_GetCurGoalIndex(me) >= 0)
    //				AI_GoalValue(me, AI_GetCurGoalIndex(me), VF_GET, AIGV_I_TYPE, &gt);
    //
    //			mprintf(0, "current Mode is Normal and GT %X\n", gt);
  } break;
  case SHM_ATTACK: {
    //			mprintf(0, "current Mode is Attack\n");
    //			if(memory->mode_time > 10.0f)
    //			{
    //				SetMode(me, SHM_BOMB_ATTACK);
    //			}
  } break;
  case SHM_BOMB_ATTACK: {
    float tick_interval;
    //			mprintf(0, "current Mode is Bomb Attack\n");

    if (memory->mode_time < SH_BOMB_TICK_RAMP_TIME) {
      float p_explode = (SH_BOMB_TICK_RAMP_TIME - memory->mode_time) / SH_BOMB_TICK_RAMP_TIME;

      tick_interval = (SH_MAX_TICK_INTERVAL * p_explode) + (SH_MIN_TICK_INTERVAL * (1.0f - p_explode));
    } else {
      tick_interval = SH_MIN_TICK_INTERVAL;
    }

    if (memory->last_tick_time + tick_interval < Game_GetTime()) {
      Sound_Play3d(me, memory->tick_sound);
      memory->last_tick_time = Game_GetTime();
    }

    if (memory->mode_time < SH_MAX_BOMB_TIME) {
      float max_speed;

      AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &max_speed);
      max_speed += SH_BOMB_ACCELERATION * Game_GetFrameTime();
      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &max_speed);

      AI_Value(me, VF_GET, AIV_F_MAX_TURN_RATE, &max_speed);
      max_speed += SH_BOMB_ROT_ACC * Game_GetFrameTime();
      AI_Value(me, VF_SET, AIV_F_MAX_TURN_RATE, &max_speed);

      AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &max_speed);
      max_speed += SH_BOMB_ACCELERATION * Game_GetFrameTime();
      AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &max_speed);
    }
  } break;
  }

  memory->mode_time += Game_GetFrameTime();
}

int16_t SpyHunter::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (spyhunter_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Sniper class
//------------------

bool Sniper::DoNotify(int me_handle, tOSIRISEventInfo *data) { return true; }

void Sniper::SetMode(int me, char mode) {
  switch (mode) {
  case SNIPER_SNIPE: {
    vector pos;
    int room = 0;

    int flags = GF_NOTIFIES;

    if ((rand() % 100) > 50) {
      flags |= GF_ORIENT_TARGET;
      AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_SPEED_ATTACK | GF_KEEP_AT_COMPLETION | GF_OBJ_IS_TARGET,
                 NULL, GST_NEG_FVEC);
      memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX + 2.0f;
    } else {
      float timescaler = 1.0f;

      if ((rand() % 100) >= 94) {
        flags |= GF_ORIENT_VELOCITY | GF_SPEED_FLEE;
        timescaler = 2.0f;
      } else {
        flags |= GF_SPEED_ATTACK;
      }

      AI_AddGoal(me, AIG_WANDER_AROUND, 3, 1.0f, -1, flags, &pos, room);

      float speed = memory->base_speed + memory->base_speed * (float)rand() / (float)RAND_MAX * .5;
      float delta_vel = memory->base_acc + memory->base_acc * (float)rand() / (float)RAND_MAX * .5;

      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);
      AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &delta_vel);

      memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX + 2.0f;
      memory->time_till_next_mode *= timescaler;
    }

  } break;
  case SNIPER_BASE: {
    bool used;
    AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

    if (used) {
      int flags;
      AI_GoalValue(me, 3, VF_GET, AIGV_I_FLAGS, &flags);

      if (!(flags & GF_NONFLUSHABLE)) {
        AI_ClearGoal(me, 3);
      }
    }

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);
    memory->time_till_next_mode = 5.0f * (float)rand() / (float)RAND_MAX;
    +6.0f;
  } break;
  }

  memory->mode_time = 0.0f;
  memory->mode = mode;
}

void Sniper::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(sniper_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (sniper_data *)Scrpt_MemAlloc(&ch);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

  SetMode(me, SNIPER_BASE);
}

void Sniper::DoFrame(int me) {
  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_ID, &m);
  int orbot_id = Obj_FindID("d3bot20");

  if (m.id != orbot_id) {
    bool used;
    AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

    if (used) {
      return;
    }

    /*		float awareness;
                    AI_Value(me, VF_GET, AIV_F_AWARENESS, &awareness);

                    if(awareness <= AWARE_BARELY)
                    {
                            if(memory->mode != SNIPER_BASE)
                            {
                                    SetMode(me, SNIPER_BASE);
                            }

                            return;
                    }*/
  }

  if (memory->time_till_next_mode < memory->mode_time) {
    if (memory->mode == SNIPER_BASE)
      SetMode(me, SNIPER_SNIPE);
    else
      SetMode(me, SNIPER_BASE);
  }

  memory->mode_time += Game_GetFrameTime();
}

int16_t Sniper::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (sniper_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// SniperNoRun class
//------------------

bool SniperNoRun::DoNotify(int me_handle, tOSIRISEventInfo *data) { return true; }

void SniperNoRun::SetMode(int me, char mode) {
  switch (mode) {
  case SNIPER_SNIPE: {
    vector pos;
    int room = 0;

    int flags = GF_NOTIFIES;

    if ((rand() % 100) > 50) {
      flags |= GF_ORIENT_TARGET;
      AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_SPEED_ATTACK | GF_KEEP_AT_COMPLETION | GF_OBJ_IS_TARGET,
                 NULL, GST_NEG_FVEC);
      memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX + 2.0f;
    } else {
      float timescaler = 1.0f;

      flags |= GF_SPEED_ATTACK;
      AI_AddGoal(me, AIG_WANDER_AROUND, 3, 1.0f, -1, flags, &pos, room);

      float speed = memory->base_speed + memory->base_speed * (float)rand() / (float)RAND_MAX * .5;
      float delta_vel = memory->base_acc + memory->base_acc * (float)rand() / (float)RAND_MAX * .5;

      AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &speed);
      AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &delta_vel);

      memory->time_till_next_mode = 2.0f * (float)rand() / (float)RAND_MAX + 2.0f;
      memory->time_till_next_mode *= timescaler;
    }

  } break;
  case SNIPER_BASE: {
    bool used;
    AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

    if (used) {
      int flags;
      AI_GoalValue(me, 3, VF_GET, AIGV_I_FLAGS, &flags);

      if (!(flags & GF_NONFLUSHABLE)) {
        AI_ClearGoal(me, 3);
      }
    }

    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);
    memory->time_till_next_mode = 5.0f * (float)rand() / (float)RAND_MAX;
    +4.0f;
  } break;
  }

  memory->mode_time = 0.0f;
  memory->mode = mode;
}

void SniperNoRun::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(snipernorun_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (snipernorun_data *)Scrpt_MemAlloc(&ch);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

  SetMode(me, SNIPER_BASE);
}

void SniperNoRun::DoFrame(int me) {
  msafe_struct m;
  m.objhandle = me;
  MSafe_GetValue(MSAFE_OBJECT_ID, &m);
  int orbot_id = Obj_FindID("d3bot20");

  if (m.id != orbot_id) {
    bool used;
    AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

    if (used) {
      return;
    }

    /*		float awareness;
                    AI_Value(me, VF_GET, AIV_F_AWARENESS, &awareness);

                    if(awareness <= AWARE_BARELY)
                    {
                            if(memory->mode != SNIPER_BASE)
                            {
                                    SetMode(me, SNIPER_BASE);
                            }

                            return;
                    }*/
  }

  if (memory->time_till_next_mode < memory->mode_time) {
    if (memory->mode == SNIPER_BASE)
      SetMode(me, SNIPER_SNIPE);
    else
      SetMode(me, SNIPER_BASE);
  }

  memory->mode_time += Game_GetFrameTime();
}

int16_t SniperNoRun::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (snipernorun_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Evader Mod A class
//------------------

#define EMA_NORMAL 0
#define EMA_GET_BEHIND 1

bool EvaderModA::DoNotify(int me_handle, tOSIRISEventInfo *data) { return true; }

void EvaderModA::SetMode(int me, char mode) {
  switch (mode) {
  case EMA_GET_BEHIND: {
    vector pos;
    int vec;

    int flags = GF_NOTIFIES | GF_ORIENT_TARGET;

    if ((rand() % 100) > 50) {
      vec = GST_NEG_FVEC;
      memory->time_till_next_mode = 7.0f * (float)rand() / (float)RAND_MAX + 2.0f;
    } else {
      if ((rand() % 100) > 50) {
        vec = GST_NEG_RVEC;
      } else {
        vec = GST_RVEC;
      }
      memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX + 2.0f;
    }

    AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_SPEED_ATTACK | GF_KEEP_AT_COMPLETION | GF_OBJ_IS_TARGET,
               NULL, vec);
  } break;
  case EMA_NORMAL: {
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

    bool used;
    AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

    if (used) {
      int flags;
      AI_GoalValue(me, 3, VF_GET, AIGV_I_FLAGS, &flags);

      if (!(flags & GF_NONFLUSHABLE)) {
        AI_ClearGoal(me, 3);
      }
    }

    memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX;
    +6.0f;
  } break;
  }

  memory->mode_time = 0.0f;
  memory->mode = mode;
}

void EvaderModA::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(evadermoda_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (evadermoda_data *)Scrpt_MemAlloc(&ch);

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

  SetMode(me, EMA_NORMAL);
}

void EvaderModA::DoFrame(int me) {
  float awareness;
  AI_Value(me, VF_GET, AIV_F_AWARENESS, &awareness);

  bool used;
  AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

  if (used) {
    return;
  }

  if (awareness <= AWARE_BARELY) {
    if (memory->mode != EMA_NORMAL) {
      SetMode(me, EMA_NORMAL);
    }

    return;
  }

  if (memory->time_till_next_mode < memory->mode_time) {
    if (memory->mode == EMA_NORMAL)
      SetMode(me, EMA_GET_BEHIND);
    else
      SetMode(me, EMA_NORMAL);
  }

  memory->mode_time += Game_GetFrameTime();
}

int16_t EvaderModA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (evadermoda_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// FlameRAS
//------------------

// Based off EvaderModA

bool FlameRAS::DoNotify(int me_handle, tOSIRISEventInfo *data) { return true; }

void FlameRAS::SetMode(int me, char mode) {
  switch (mode) {
  case EMA_GET_BEHIND: {
    vector pos;
    int vec;

    int flags = GF_NOTIFIES | GF_ORIENT_TARGET;

    if ((rand() % 100) > 50) {
      vec = GST_NEG_FVEC;
      memory->time_till_next_mode = 7.0f * (float)rand() / (float)RAND_MAX + 2.0f;
    } else {
      if ((rand() % 100) > 50) {
        vec = GST_NEG_RVEC;
      } else {
        vec = GST_RVEC;
      }
      memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX + 2.0f;
    }

    AI_AddGoal(me, AIG_MOVE_RELATIVE_OBJ_VEC, 0, 1.0f, -1, GF_SPEED_ATTACK | GF_KEEP_AT_COMPLETION | GF_OBJ_IS_TARGET,
               NULL, vec);
  } break;
  case EMA_NORMAL: {
    AI_Value(me, VF_SET, AIV_F_MAX_SPEED, &memory->base_speed);
    AI_Value(me, VF_SET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

    bool used;
    AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

    if (used) {
      int flags;
      AI_GoalValue(me, 3, VF_GET, AIGV_I_FLAGS, &flags);

      if (!(flags & GF_NONFLUSHABLE)) {
        AI_ClearGoal(me, 3);
      }
    }

    memory->time_till_next_mode = 4.0f * (float)rand() / (float)RAND_MAX;
    +6.0f;
  } break;
  }

  memory->mode_time = 0.0f;
  memory->mode = mode;
}

void FlameRAS::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(flameras_data);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (flameras_data *)Scrpt_MemAlloc(&ch);

  memory->time_till_fire_toggle = 3.0f + (float)rand() / (float)RAND_MAX + (float)Game_GetDiffLevel();
  memory->f_firing_ok = true;

  AI_Value(me, VF_GET, AIV_F_MAX_SPEED, &memory->base_speed);
  AI_Value(me, VF_GET, AIV_F_MAX_DELTA_SPEED, &memory->base_acc);

  SetMode(me, EMA_NORMAL);
}

void FlameRAS::DoFrame(int me) {
  float awareness;
  AI_Value(me, VF_GET, AIV_F_AWARENESS, &awareness);

  bool used;
  AI_GoalValue(me, 3, VF_GET, AIGV_B_USED, &used);

  if (memory->time_till_fire_toggle <= 0.0f) {
    if (memory->f_firing_ok) {
      int flags = AIF_DISABLE_FIRING;
      AI_Value(me, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

      memory->time_till_fire_toggle = 5.0f + (float)rand() / (float)RAND_MAX + ((float)Game_GetDiffLevel() - 3.0f);
      memory->f_firing_ok = false;
    } else {
      int flags = AIF_DISABLE_FIRING;
      AI_Value(me, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

      memory->time_till_fire_toggle = 4.0f + (float)rand() / (float)RAND_MAX + (float)Game_GetDiffLevel();
      memory->f_firing_ok = true;
    }
  }

  if (used) {
    return;
  }

  if (awareness <= AWARE_BARELY) {
    if (memory->mode != EMA_NORMAL) {
      SetMode(me, EMA_NORMAL);
    }

    return;
  }

  if (memory->time_till_next_mode < memory->mode_time) {
    if (memory->mode == EMA_NORMAL)
      SetMode(me, EMA_GET_BEHIND);
    else
      SetMode(me, EMA_NORMAL);
  }

  memory->time_till_fire_toggle -= Game_GetFrameTime();
  memory->mode_time += Game_GetFrameTime();
}

int16_t FlameRAS::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_AI_FRAME:
    DoFrame(data->me_handle);
    break;
  case EVT_AI_NOTIFY:
    return (DoNotify(data->me_handle, data) != false) ? CONTINUE_CHAIN | CONTINUE_DEFAULT : 0;
    break;
  case EVT_MEMRESTORE: {
    memory = (flameras_data *)data->evt_memrestore.memory_ptr;
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Seeker class
//------------------

void Seeker::DoInit(int me) {
  AI_SetType(me, AIT_AIS);
  AI_AddGoal(me, AIG_GET_TO_OBJ, 1, 1.0f, -1, GF_OBJ_IS_TARGET | GF_USE_BLINE_IF_SEES_GOAL, OBJECT_HANDLE_NONE);

  uint16_t id;
  uint16_t humon_seeker_id;

  Obj_Value(me, VF_GET, OBJV_US_ID, &id);
  humon_seeker_id = Obj_FindID("HumonSeeker");

  if (humon_seeker_id == id) {
    vector velocity;
    matrix orient;
    Obj_Value(me, VF_GET, OBJV_V_VELOCITY, &velocity);
    Obj_Value(me, VF_GET, OBJV_M_ORIENT, &orient);

    velocity += orient.fvec * 50.0f;

    Obj_Value(me, VF_SET, OBJV_V_VELOCITY, &velocity);
  }

  int parent = GetObjectParent(me);
  int sound_id = Sound_FindId("Drop bomb");
  int p_type = GetObjectType(parent);

  if (sound_id >= 0 && p_type == OBJ_PLAYER) {
    Sound_Play3d(parent, sound_id);
  }
}

void Seeker::DoCollide(int me) {
  int room;
  vector pos;
  int weapon_id;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

  weapon_id = Wpn_FindID("SeekerExplosion");
  Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);

  msafe_struct mo;
  mo.objhandle = me;
  mo.playsound = 0;

  MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
}

int16_t Seeker::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_COLLIDE:
    DoCollide(data->me_handle);
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// Old Osiris functions converted to make porting easier
int GetObjectParent(int object) {
  msafe_struct ms;
  ms.objhandle = object;

  MSafe_GetValue(MSAFE_OBJECT_PARENT, &ms);

  return ms.objhandle;
}

int GetObjectType(int object) {
  msafe_struct ms;
  ms.objhandle = object;
  MSafe_GetValue(MSAFE_OBJECT_TYPE, &ms);

  return ms.type;
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

void ObjectRemove(int object) {
  msafe_struct ms;
  ms.objhandle = object;
  ms.playsound = 0;
  MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &ms);
}

//------------------
// Bouncing Betty class
//------------------

int16_t BettyBomb::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_MEMRESTORE: {
    memory = (tBettyBombInfo *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_CREATED: {
    // create our memory
    tOSIRISMEMCHUNK ch;
    ch.id = 4;
    ch.size = sizeof(tBettyBombInfo);
    ch.my_id.type = OBJECT_SCRIPT;
    ch.my_id.objhandle = data->me_handle;

    memory = (tBettyBombInfo *)Scrpt_MemAlloc(&ch);

    memory->explode = false;

    // Create and release our Betty children
    int parent = GetObjectParent(data->me_handle);
    int child_id = Obj_FindID("Betty");

    if (parent != OBJECT_HANDLE_NONE && child_id != -1) {
      int child_handle;
      matrix orient, o, otemp, o1;
      vector vel, pos, v, vtemp;
      int room;

      Obj_Value(parent, VF_GET, OBJV_M_ORIENT, &orient);
      Obj_Value(parent, VF_GET, OBJV_V_VELOCITY, &vel);
      Obj_Value(parent, VF_GET, OBJV_I_ROOMNUM, &room);
      Obj_Value(parent, VF_GET, OBJV_V_POS, &pos);

      // v = -vel;
      /*
      v = vel;
      float mag = vm_GetMagnitude(&v);
      if(mag < 30.0f )
      {
              if(mag==0)
                      mag = 0.001f;

              v /= mag;
              v *= 30.0f;
      }
      */

      v = -orient.fvec + orient.rvec - orient.uvec;
      vm_VectorNormalize(&v);
      v *= 30.0f;

      // give drop bomb sound
      int type = GetObjectType(parent);

      if (type == OBJ_PLAYER || type == OBJ_GHOST) {
        int sound_id = Sound_FindId("Drop bomb");

        if (sound_id >= 0) {
          Sound_Play3d(parent, sound_id);
        }
      }

      // First create middle Betty
      child_handle = Obj_Create(OBJ_ROBOT, child_id, room, &pos, &orient, parent, &v);

      // Now create left Betty
      v = -orient.fvec + (0.3f * orient.rvec) - orient.uvec;
      vm_VectorNormalize(&v);
      v *= 30.0f;
      child_handle = Obj_Create(OBJ_ROBOT, child_id, room, &pos, &orient, parent, &v);

      // Now create right Betty
      v = -orient.fvec - (0.3f * orient.rvec) - orient.uvec;
      vm_VectorNormalize(&v);
      v *= 30.0f;
      child_handle = Obj_Create(OBJ_ROBOT, child_id, room, &pos, &orient, parent, &v);
    }

    memory->explode = true;

  } break;
  case EVT_INTERVAL: {
    if (memory && memory->explode) {
      ObjectRemove(data->me_handle);
    }
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

void BettyScript::DoInit(int me) {
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(tBettyInfo);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = me;

  memory = (tBettyInfo *)Scrpt_MemAlloc(&ch);

  memory->explode = false;
  memory->lasttime = 0;
}

int16_t BettyScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_MEMRESTORE: {
    memory = (tBettyInfo *)data->evt_memrestore.memory_ptr;
  } break;

  case EVT_CREATED: {
    // create our memory
    DoInit(data->me_handle);

    int parent, type;
    vector vel;

    parent = GetObjectParent(data->me_handle);

    if (parent != OBJECT_HANDLE_NONE) {
      // Give it velocity
      Obj_Value(parent, VF_GET, OBJV_V_VELOCITY, &vel);
      vel.x = vel.x * -0.5;
      vel.y = vel.y * -0.5;
      vel.z = vel.z * -0.5;
      Obj_Value(data->me_handle, VF_SET, OBJV_V_VELOCITY, &vel);
    }

    tOSIRISTIMER timer_info;
    timer_info.flags = 0;
    timer_info.repeat_count = 0;
    timer_info.object_handle = data->me_handle;
    timer_info.object_handle_detonator = OBJECT_HANDLE_NONE;
    timer_info.timer_interval = 15.0f;
    timer_info.id = CREATE_TIMER_ID(0x1A);
    Scrpt_CreateTimer(&timer_info);

  } break;
  case EVT_COLLIDE: {
    float velmag;
    vector vel;

    if (GetObjectType(data->evt_collide.it_handle) == OBJ_PLAYER) {

      if (!memory->explode) {
        memory->explode = true;

        matrix orient;
        Obj_Value(data->me_handle, VF_GET, OBJV_M_ORIENT, &orient);

        Obj_Value(data->me_handle, VF_GET, OBJV_V_VELOCITY, &vel);
        velmag = vm_GetMagnitude(&vel);
        velmag = velmag / 4;

        int room;
        vector pos;
        int weapon_id;

        Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &room);
        Obj_Value(data->me_handle, VF_GET, OBJV_V_POS, &pos);

        weapon_id = Wpn_FindID("TubbsHitBlast");
        Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, &orient, GetObjectParent(data->me_handle));

        ObjectDamage(data->evt_collide.it_handle, velmag, data->me_handle);
      }
    }
  } break;
  case EVT_INTERVAL: {
    float time, velmag, scale;
    vector vel;

    time = data->evt_interval.game_time;

    if (time > memory->lasttime + 0.10) {
      // check to see if we need to limit speed
      memory->lasttime = time;
      Obj_Value(data->me_handle, VF_GET, OBJV_V_VELOCITY, &vel);
      velmag = vm_GetMagnitude(&vel);

      if (velmag > 120.0f) {
        // limit the velocity
        scale = 120.0f / velmag;
        vel.x = scale * vel.x;
        vel.y = scale * vel.y;
        vel.z = scale * vel.z;
        Obj_Value(data->me_handle, VF_SET, OBJV_V_VELOCITY, &vel);
      }
    }

    if (memory && memory->explode) {
      ObjectRemove(data->me_handle);
    }
  } break;

  case EVT_TIMER: {
    float amount;
    amount = GetObjectShields(data->me_handle) + 10.0f;
    ObjectDamage(data->me_handle, amount);
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Chaff class
//------------------

void ChaffScript::DoInit(int handle) {
  vector vel, v, pos;

  int count, chaffcount;
  int chunk_id, room;
  int parent, ch, type;

  // Allocate the memory for the script
  tOSIRISMEMCHUNK mem;
  mem.id = 4;
  mem.size = sizeof(tChaffInfo);
  mem.my_id.type = OBJECT_SCRIPT;
  mem.my_id.objhandle = handle;

  memory = (tChaffInfo *)Scrpt_MemAlloc(&mem);
  memory->killme = false;

  parent = GetObjectParent(handle);
  chunk_id = Obj_FindID("ChaffChunk");

  if (parent != OBJECT_HANDLE_NONE && chunk_id != -1) {
    matrix orient;
    Obj_Value(handle, VF_GET, OBJV_M_ORIENT, &orient);

    Obj_Value(parent, VF_GET, OBJV_V_VELOCITY, &vel);
    Obj_Value(handle, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(handle, VF_GET, OBJV_V_POS, &pos);

    chaffcount = 10;
    for (count = 0; count < chaffcount; count++) {
      v = -vel;
      v.x += (rand() % 30) - 15;
      v.y += (rand() % 30) - 15;
      v.z += (rand() % 30) - 15;

      ch = Obj_Create(OBJ_ROBOT, chunk_id, room, &pos, &orient, parent, &v);
    }

    type = GetObjectType(parent);
    if (type == OBJ_PLAYER || type == OBJ_GHOST) {
      int sound_id = Sound_FindId("Drop bomb");
      if (sound_id >= 0) {
        Sound_Play3d(parent, sound_id);
      }
    }
  }

  memory->killme = true;
}

void ChaffScript::DoInterval(int handle) {
  if (memory && memory->killme) {
    ObjectRemove(handle);
  }
}

int16_t ChaffScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_MEMRESTORE: {
    memory = (tChaffInfo *)data->evt_memrestore.memory_ptr;
  } break;
  case EVT_CREATED: {
    DoInit(data->me_handle);
  } break;
  case EVT_INTERVAL: {
    DoInterval(data->me_handle);
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

void ChaffChunkScript::DoInit(int handle) {
  // Allocate the memory for the script
  tOSIRISMEMCHUNK ch;
  ch.id = 4;
  ch.size = sizeof(tChaffChunkInfo);
  ch.my_id.type = OBJECT_SCRIPT;
  ch.my_id.objhandle = handle;

  memory = (tChaffChunkInfo *)Scrpt_MemAlloc(&ch);
  memory->killme = false;
  memory->lifeleft = 30.0f;

  int parent;
  vector vel;
  parent = GetObjectParent(handle);

  if (parent != OBJECT_HANDLE_NONE) {
    Obj_Value(parent, VF_GET, OBJV_V_VELOCITY, &vel);
    Obj_Value(handle, VF_SET, OBJV_V_VELOCITY, &vel);
  }
}

void ChaffChunkScript::DoInterval(int handle, float frametime) {
  if (!memory)
    return;

  memory->lifeleft -= frametime;
  if (!memory->killme && memory->lifeleft < 0) {
    int weapon_id;
    matrix orient;

    memory->killme = true;

    Obj_Value(handle, VF_GET, OBJV_M_ORIENT, &orient);

    int room;
    vector pos;

    Obj_Value(handle, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(handle, VF_GET, OBJV_V_POS, &pos);

    weapon_id = Wpn_FindID("ChaffSpark");

    int parent = GetObjectParent(handle);

    Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, &orient, parent);
  }

  if (memory->killme) {
    ObjectRemove(handle);
  }
}

void ChaffChunkScript::DoCollide(tOSIRISEventInfo *data) {
  int weapon_id;
  matrix orient;

  if (!memory->killme) {
    memory->killme = true;

    Obj_Value(data->me_handle, VF_GET, OBJV_M_ORIENT, &orient);

    int room;
    vector pos;

    Obj_Value(data->me_handle, VF_GET, OBJV_I_ROOMNUM, &room);
    Obj_Value(data->me_handle, VF_GET, OBJV_V_POS, &pos);

    weapon_id = Wpn_FindID("ChaffSpark");

    int parent = GetObjectParent(data->me_handle);

    Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, &orient, parent);
  }
}

int16_t ChaffChunkScript::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_MEMRESTORE: {
    memory = (tChaffChunkInfo *)data->evt_memrestore.memory_ptr;
  } break;
  case EVT_CREATED: {
    DoInit(data->me_handle);
  } break;
  case EVT_INTERVAL: {
    DoInterval(data->me_handle, data->evt_interval.frame_time);
  } break;
  case EVT_COLLIDE: {
    DoCollide(data);
  } break;
  case EVT_AI_INIT: {
    Obj_SetCustomAnim(data->me_handle, 0.0f, 4.0f, 1.0f, 0);
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// ProxMine class
//------------------

void ProxMine::DoInit(int me) {
  int parent = GetObjectParent(me);
  int sound_id = Sound_FindId("Drop bomb");
  if (sound_id >= 0) {
    Sound_Play3d(parent, sound_id);
  }
}

void ProxMine::DoCollide(int me) {
  int room;
  vector pos;
  int weapon_id;

  Obj_Value(me, VF_GET, OBJV_I_ROOMNUM, &room);
  Obj_Value(me, VF_GET, OBJV_V_POS, &pos);

  weapon_id = Wpn_FindID("TubbsHitBlast");
  Obj_Create(OBJ_WEAPON, weapon_id, room, &pos, NULL, me);

  msafe_struct mo;
  mo.objhandle = me;

  MSafe_CallFunction(MSAFE_OBJECT_REMOVE, &mo);
}

int16_t ProxMine::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AI_INIT:
    DoInit(data->me_handle);
    break;
  case EVT_COLLIDE:
    DoCollide(data->me_handle);
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

//------------------
// Gunboy class
//------------------
int16_t Gunboy::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    int parent = GetObjectParent(data->me_handle);
    int sound_id = Sound_FindId("Drop bomb");
    if (sound_id >= 0) {
      Sound_Play3d(parent, sound_id, 1);
    }

    tOSIRISTIMER timer_info;
    timer_info.flags = 0;
    timer_info.repeat_count = 0;
    timer_info.object_handle = data->me_handle;
    timer_info.object_handle_detonator = OBJECT_HANDLE_NONE;
    timer_info.timer_interval = 160.0f;
    timer_info.id = CREATE_TIMER_ID(0x2D);
    Scrpt_CreateTimer(&timer_info);

  } break;

  case EVT_TIMER: {
    float amount;
    amount = GetObjectShields(data->me_handle) + 60.0f;
    ObjectDamage(data->me_handle, amount);
  } break;
  }

  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}
