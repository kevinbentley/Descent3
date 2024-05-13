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

/////////////////////////////////////////////////////////////////////
// D.A.L.L.A.S. Generated Level Script - DLL Source File
//
// Filename:	TrainingMission.cpp
// Version:	3
/////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "osiris_import.h"
#include "osiris_common.h"
#include "DallasFuncs.cpp"

#include "module.h"

#ifdef __cplusplus
extern "C" {
#endif
DLLEXPORT char STDCALL InitializeDLL(tOSIRISModuleInit *func_list);
DLLEXPORT void STDCALL ShutdownDLL(void);
DLLEXPORT int STDCALL GetGOScriptID(const char *name, uint8_t is_door);
DLLEXPORT void STDCALLPTR CreateInstance(int id);
DLLEXPORT void STDCALL DestroyInstance(int id, void *ptr);
DLLEXPORT int16_t STDCALL CallInstanceEvent(int id, void *ptr, int event, tOSIRISEventInfo *data);
DLLEXPORT int STDCALL GetTriggerScriptID(int trigger_room, int trigger_face);
DLLEXPORT int STDCALL GetCOScriptList(int **list, int **id_list);
DLLEXPORT int STDCALL SaveRestoreState(void *file_ptr, uint8_t saving_state);
#ifdef __cplusplus
}
#endif

// ===================
// Function Prototypes
// ===================

static void ClearGlobalActionCtrs(void);
static void SaveGlobalActionCtrs(void *file_ptr);
static void RestoreGlobalActionCtrs(void *file_ptr);
static void InitMessageList(void);
static void ClearMessageList(void);
static int AddMessageToList(char *name, char *msg);
static void RemoveTrailingWhitespace(char *s);
static char *SkipInitialWhitespace(char *s);
static int ReadMessageFile(const char *filename);
static const char *GetMessage(const char *name);

// =================
// Script ID Numbers
// =================
#define ID_LEVEL_0000 0x000

#define ID_CUSTOM_OBJECT_300D 0x001
#define ID_CUSTOM_OBJECT_300C 0x002
#define ID_CUSTOM_OBJECT_300B 0x003
#define ID_CUSTOM_OBJECT_4809 0x004
#define ID_CUSTOM_OBJECT_1803 0x005
#define ID_CUSTOM_OBJECT_1806 0x006
#define ID_CUSTOM_OBJECT_100A 0x007
#define ID_CUSTOM_OBJECT_300E 0x008
#define ID_CUSTOM_OBJECT_2007 0x009
#define ID_CUSTOM_OBJECT_080F 0x00a
#define ID_CUSTOM_OBJECT_2008 0x00b
#define ID_CUSTOM_OBJECT_1011 0x00c
#define ID_CUSTOM_OBJECT_1010 0x00d
#define ID_CUSTOM_OBJECT_1817 0x00e
#define ID_CUSTOM_OBJECT_081A 0x00f
#define ID_CUSTOM_OBJECT_081B 0x010
#define ID_CUSTOM_OBJECT_081D 0x011
#define ID_CUSTOM_OBJECT_081E 0x012
#define ID_CUSTOM_OBJECT_081C 0x013
#define ID_CUSTOM_OBJECT_0819 0x014
#define ID_CUSTOM_OBJECT_101F 0x015
#define ID_CUSTOM_OBJECT_0820 0x016
#define ID_CUSTOM_OBJECT_0821 0x017
#define ID_CUSTOM_OBJECT_0822 0x018
#define ID_CUSTOM_OBJECT_0823 0x019
#define ID_CUSTOM_OBJECT_1824 0x01a

#define ID_TRIGGER_0000 0x01b
#define ID_TRIGGER_0001 0x01c
#define ID_TRIGGER_0002 0x01d

// ========================
// Script Class Definitions
// ========================

class BaseScript {
public:
  BaseScript();
  ~BaseScript();
  virtual int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class LevelScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_300D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_300C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_300B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_4809 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1803 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1806 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_100A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_300E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1817 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0819 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_101F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0820 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0821 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0822 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0823 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1824 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0001 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_058 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_058 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here

/*
$$QUERY
Objects
o:Player's [i:PlayerNum] Buddy Bot object
qGetBuddyObj
GetBuddyObj
  Gets a player's buddy bot object based on a player number

Parameters:
  PlayerNum: the player to get the buddy bot from
$$END
*/
int qGetBuddyObj(int playernum) {
  msafe_struct mstruct;
  mstruct.slot = playernum;
  MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);

  int buddy_handle;
  Player_Value(mstruct.objhandle, VF_GET, PLYV_I_BUDDY_HANDLE, &buddy_handle);

  return buddy_handle;
}

/*
$$QUERY
Objects
o:Player [i:PlayerNum] Object
qGetPlayerObj
GetPlayerObj
  Gets a player object based on a player number

Parameters:
  PlayerNum: the player to get
$$END
*/
int qGetPlayerObj(int playernum) {
  msafe_struct mstruct;
  mstruct.slot = playernum;
  MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);
  return mstruct.objhandle;
}

/*
$$ACTION
Players
[e:Enable/Disable] display of player [i:PlayerNum] controls on hud
aToggleShowPlayerControl
ToggleShowPlayerControl
  Shows one of the players currently active control on the hud

Parameters:
  PlayerNum: Which player this affects, or -1 for all players
  Enable/Disable: Whether to Enable or Disable the specified controls
$$END
*/
void aToggleShowPlayerControl(int enable, int playernum) {
  msafe_struct mstruct;

  mstruct.slot = playernum;

  MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);
  mstruct.state = enable;

  MSafe_CallFunction(MSAFE_SHOW_ENABLED_CONTROLS, &mstruct);
}

/*
$$ACTION
Players
[e:Enable/Disable] player [i:PlayerNum] control for [g:PlayerControl]
aTogglePlayerControl
TogglePlayerControl
  Sets a players control either disabled or enabled

Parameters:
  Object: The player object
  PlayerNum: Which player this affects, or -1 for all players
  Enable/Disable: Whether to Enable or Disable the specified controls
$$END
*/
void aTogglePlayerControl(int enable, int playernum, int controlmask) {
  msafe_struct mstruct;

  mstruct.slot = playernum;

  MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);
  mstruct.control_mask = controlmask;
  mstruct.control_val = enable;

  MSafe_CallFunction(MSAFE_OBJECT_PLAYER_CMASK, &mstruct);
}

/*
$$ACTION
Players
[e:Enable/Disable] player [i:PlayerNum] control for all controls
aToggleAllPlayerControls
ToggleAllPlayerControls
  Sets a players control either disabled or enabled

Parameters:
  Enable/Disable: Enable/Disable the specified control
  PlayerNum: Which player this affects, or -1 for all players
$$END
*/
void aToggleAllPlayerControls(int enable, int playernum) {
  msafe_struct mstruct;
  int controlbit = 0xffffffff;
  mstruct.slot = playernum;

  MSafe_GetValue(MSAFE_OBJECT_PLAYER_HANDLE, &mstruct);

  mstruct.control_mask = controlbit;
  mstruct.control_val = enable ? 1 : 0;

  MSafe_CallFunction(MSAFE_OBJECT_PLAYER_CMASK, &mstruct);
}

/**{CUSTOM_SCRIPT_BLOCK_END}**** DO NOT EDIT! **/
// ============================================================
// End of Custom Script Block - DO NOT EDIT ANYTHING AFTER THIS
// ============================================================

// =================
// Message File Data
// =================

#define MAX_SCRIPT_MESSAGES 256
#define MAX_MSG_FILEBUF_LEN 1024
#define NO_MESSAGE_STRING "*Message Not Found*"
#define INV_MSGNAME_STRING "*Message Name Invalid*"
#define WHITESPACE_CHARS " \t\r\n"

// Structure for storing a script message
struct tScriptMessage {
  char *name;    // the name of the message
  char *message; // the actual message text
};

// Global storage for level script messages
static tScriptMessage *message_list[MAX_SCRIPT_MESSAGES];
static int num_messages;

// ======================
// Message File Functions
// ======================

// Initializes the Message List
void InitMessageList(void) {
  for (int j = 0; j < MAX_SCRIPT_MESSAGES; j++)
    message_list[j] = NULL;
  num_messages = 0;
}

// Clear the Message List
void ClearMessageList(void) {
  for (int j = 0; j < num_messages; j++) {
    free(message_list[j]->name);
    free(message_list[j]->message);
    free(message_list[j]);
    message_list[j] = NULL;
  }
  num_messages = 0;
}

// Adds a message to the list
int AddMessageToList(char *name, char *msg) {
  int pos;

  // Make sure there is room in the list
  if (num_messages >= MAX_SCRIPT_MESSAGES)
    return false;

  // Allocate memory for this message entry
  pos = num_messages;
  message_list[pos] = (tScriptMessage *)malloc(sizeof(tScriptMessage));
  if (message_list[pos] == NULL)
    return false;

  // Allocate memory for the message name
  message_list[pos]->name = (char *)malloc(strlen(name) + 1);
  if (message_list[pos]->name == NULL) {
    free(message_list[pos]);
    return false;
  }
  strcpy(message_list[pos]->name, name);

  // Allocate memory for the message name
  message_list[pos]->message = (char *)malloc(strlen(msg) + 1);
  if (message_list[pos]->message == NULL) {
    free(message_list[pos]->name);
    free(message_list[pos]);
    return false;
  }
  strcpy(message_list[pos]->message, msg);
  num_messages++;

  return true;
}

// Removes any whitespace padding from the end of a string
void RemoveTrailingWhitespace(char *s) {
  int last_char_pos;

  last_char_pos = strlen(s) - 1;
  while (last_char_pos >= 0 && isspace(s[last_char_pos])) {
    s[last_char_pos] = '\0';
    last_char_pos--;
  }
}

// Returns a pointer to the first non-whitespace char in given string
char *SkipInitialWhitespace(char *s) {
  while ((*s) != '\0' && isspace(*s))
    s++;

  return (s);
}

// Read in the Messages
int ReadMessageFile(const char *filename) {
  void *infile;
  char filebuffer[MAX_MSG_FILEBUF_LEN + 1];
  char *line, *msg_start;
  int line_num;
  bool next_msgid_found;

  // Try to open the file for loading
  infile = File_Open(filename, "rt");
  if (!infile)
    return false;

  line_num = 0;
  next_msgid_found = true;

  // Clear the message list
  ClearMessageList();

  // Read in and parse each line of the file
  while (!File_eof(infile)) {

    // Clear the buffer
    strcpy(filebuffer, "");

    // Read in a line from the file
    File_ReadString(filebuffer, MAX_MSG_FILEBUF_LEN, infile);
    line_num++;

    // Remove whitespace padding at start and end of line
    RemoveTrailingWhitespace(filebuffer);
    line = SkipInitialWhitespace(filebuffer);

    // If line is a comment, or empty, discard it
    if (strlen(line) == 0 || strncmp(line, "//", 2) == 0)
      continue;

    if (!next_msgid_found) { // Parse out the last message ID number

      // Grab the first keyword, make sure it's valid
      line = strtok(line, WHITESPACE_CHARS);
      if (line == NULL)
        continue;

      // Grab the second keyword, and assign it as the next message ID
      line = strtok(NULL, WHITESPACE_CHARS);
      if (line == NULL)
        continue;

      next_msgid_found = true;
    } else { // Parse line as a message line

      // Find the start of message, and mark it
      msg_start = strchr(line, '=');
      if (msg_start == NULL)
        continue;
      msg_start[0] = '\0';
      msg_start++;

      // Add the message to the list
      AddMessageToList(line, msg_start);
    }
  }
  File_Close(infile);

  return true;
}

// Find a message
const char *GetMessage(const char *name) {
  // Make sure given name is valid
  if (name == NULL)
    return INV_MSGNAME_STRING;

  // Search message list for name
  for (int j = 0; j < num_messages; j++)
    if (strcmp(message_list[j]->name, name) == 0)
      return (message_list[j]->message);

  // Couldn't find it
  return NO_MESSAGE_STRING;
}

//======================
// Name List Arrays
//======================

#define NUM_DOOR_NAMES 0
static const char **Door_names = NULL;
static int *Door_handles = NULL;

#define NUM_OBJECT_NAMES 35
static const char *const Object_names[NUM_OBJECT_NAMES] = {
    "FlashLight-1", "FlashLight-2", "FlashLight-3",      "FlashLight-4",   "FlashLight-5",  "DoneDodgeingGoal",
    "StartCourse",  "StartDodge",   "FinishCourse",      "UpGoal",         "LeftGoal",      "StartGoal",
    "DodgeTurrett", "FollowBot1",   "ManuverRoomCenter", "DestroyBot2",    "DestroyBot1",   "GalleryEntered",
    "LastRoomGoal", "KillBotGoal",  "FinalGoal",         "ForwardGoal",    "CameraMonitor", "RASBot1",
    "RASBot2",      "RASBot3",      "RASBot4",           "InvulnPowerup2", "CloakPowerup2", "LastBot1",
    "LastBot2",     "LastBot3",     "LastBot4",          "LastBot5",       "SecurityCamera"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 7
static const char *const Room_names[NUM_ROOM_NAMES] = {"PortalRoom1", "PortalRoom2", "PortalRoom3", "PortalRoom4",
                                                       "PortalRoom5", "PortalRoom6", "PortalRoom7"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 3
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {"Portal2", "Portal3", "Portal4"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 2
static const char *const Sound_names[NUM_SOUND_NAMES] = {"MenuBeepEnter", "PupC1"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 2
static const char *const Path_names[NUM_PATH_NAMES] = {"FollowLoop1", "GoToDie"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 0
static const char **Goal_names = NULL;
static int *Goal_indexes = NULL;

#define NUM_MESSAGE_NAMES 36
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"GoodJob",
                                                             "GoBackwards",
                                                             "Welcome",
                                                             "GoForward",
                                                             "GoLeft",
                                                             "GoRight",
                                                             "GoUp",
                                                             "GoDown",
                                                             "Repeat",
                                                             "ContinueToCourse",
                                                             "CourseInstructions",
                                                             "DodgeIntro",
                                                             "Dodge30",
                                                             "LeaveDodge",
                                                             "FollowIntro",
                                                             "FollowInstructions",
                                                             "KeepDodging",
                                                             "KeepMovingOutofDodging",
                                                             "BankIntro",
                                                             "AlmostDoneDodge",
                                                             "ManuverIntro",
                                                             "HeadingIntro",
                                                             "PitchIntro",
                                                             "WeaponsEnabled",
                                                             "DestroyFollowbot",
                                                             "Movingbotintro",
                                                             "ExitManuveur",
                                                             "GBIntro",
                                                             "UseCameraMonitor",
                                                             "KillBotIntro",
                                                             "KillBot2",
                                                             "ProceedtoLastRoom",
                                                             "FinalSessionIntro",
                                                             "AllDone",
                                                             "GBExtra",
                                                             "GetCameraMonitor"};
static const char *Message_strings[NUM_MESSAGE_NAMES];

// ===============
// InitializeDLL()
// ===============
char STDCALL InitializeDLL(tOSIRISModuleInit *func_list) {
  osicommon_Initialize((tOSIRISModuleInit *)func_list);
  if (func_list->game_checksum != CHECKSUM) {
    mprintf(0, "Game-Checksum FAIL!!! (%ul!=%ul)\n", func_list->game_checksum, CHECKSUM);
    mprintf(0, "RECOMPILE YOUR SCRIPTS!!!\n");
    return 0;
  }

  ClearGlobalActionCtrs();
  dfInit();
  InitMessageList();

  // Build the filename of the message file
  char filename[_MAX_PATH + 32];
  int lang_type;
  if (func_list->script_identifier != NULL) {
    _splitpath(func_list->script_identifier, NULL, NULL, filename, NULL);
    lang_type = Game_GetLanguage();
    if (lang_type == LANGUAGE_FRENCH)
      strcat(filename, "_FRN");
    else if (lang_type == LANGUAGE_GERMAN)
      strcat(filename, "_GER");
    else if (lang_type == LANGUAGE_ITALIAN)
      strcat(filename, "_ITN");
    else if (lang_type == LANGUAGE_SPANISH)
      strcat(filename, "_SPN");
    strcat(filename, ".msg");
  } else {
    strcpy(filename, "TrainingMission.msg");
    lang_type = LANGUAGE_ENGLISH;
  }
  if (!ReadMessageFile(filename)) {
    mprintf(0, "ERROR: Could not load message file - %s\n", filename);
  }

  int j;

  // Do Door Index lookups
  for (j = 0; j < NUM_DOOR_NAMES; j++)
    Door_handles[j] = Scrpt_FindDoorName(Door_names[j]);

  // Do Object Index lookups
  for (j = 0; j < NUM_OBJECT_NAMES; j++)
    Object_handles[j] = Scrpt_FindObjectName(Object_names[j]);

  // Do Room Index lookups
  for (j = 0; j < NUM_ROOM_NAMES; j++)
    Room_indexes[j] = Scrpt_FindRoomName(Room_names[j]);

  // Do Trigger Index lookups
  for (j = 0; j < NUM_TRIGGER_NAMES; j++) {
    Trigger_indexes[j] = Scrpt_FindTriggerName(Trigger_names[j]);
    Trigger_faces[j] = Scrpt_GetTriggerFace(Trigger_indexes[j]);
    Trigger_rooms[j] = Scrpt_GetTriggerRoom(Trigger_indexes[j]);
  }

  // Do Sound Index lookups
  for (j = 0; j < NUM_SOUND_NAMES; j++)
    Sound_indexes[j] = Scrpt_FindSoundName(Sound_names[j]);

  // Do Texture Index lookups
  for (j = 0; j < NUM_TEXTURE_NAMES; j++)
    Texture_indexes[j] = Scrpt_FindTextureName(Texture_names[j]);

  // Do Path Index lookups
  for (j = 0; j < NUM_PATH_NAMES; j++)
    Path_indexes[j] = Scrpt_FindPathName(Path_names[j]);

  // Do Matcen Index lookups
  for (j = 0; j < NUM_MATCEN_NAMES; j++)
    Matcen_indexes[j] = Scrpt_FindMatcenName(Matcen_names[j]);

  // Do Goal Index lookups
  for (j = 0; j < NUM_GOAL_NAMES; j++)
    Goal_indexes[j] = Scrpt_FindLevelGoalName(Goal_names[j]);

  // Do Message Name lookups
  for (j = 0; j < NUM_MESSAGE_NAMES; j++)
    Message_strings[j] = GetMessage(Message_names[j]);

  return 1;
}

// =============
// ShutdownDLL()
// =============
void STDCALL ShutdownDLL(void) { ClearMessageList(); }

// ===============
// GetGOScriptID()
// ===============
int STDCALL GetGOScriptID(const char *name, uint8_t isdoor) { return -1; }

// ================
// CreateInstance()
// ================
void STDCALLPTR CreateInstance(int id) {
  switch (id) {
  case ID_LEVEL_0000:
    return new LevelScript_0000;
    break;
  case ID_CUSTOM_OBJECT_300D:
    return new CustomObjectScript_300D;
    break;
  case ID_CUSTOM_OBJECT_300C:
    return new CustomObjectScript_300C;
    break;
  case ID_CUSTOM_OBJECT_300B:
    return new CustomObjectScript_300B;
    break;
  case ID_CUSTOM_OBJECT_4809:
    return new CustomObjectScript_4809;
    break;
  case ID_CUSTOM_OBJECT_1803:
    return new CustomObjectScript_1803;
    break;
  case ID_CUSTOM_OBJECT_1806:
    return new CustomObjectScript_1806;
    break;
  case ID_CUSTOM_OBJECT_100A:
    return new CustomObjectScript_100A;
    break;
  case ID_CUSTOM_OBJECT_300E:
    return new CustomObjectScript_300E;
    break;
  case ID_CUSTOM_OBJECT_2007:
    return new CustomObjectScript_2007;
    break;
  case ID_CUSTOM_OBJECT_080F:
    return new CustomObjectScript_080F;
    break;
  case ID_CUSTOM_OBJECT_2008:
    return new CustomObjectScript_2008;
    break;
  case ID_CUSTOM_OBJECT_1011:
    return new CustomObjectScript_1011;
    break;
  case ID_CUSTOM_OBJECT_1010:
    return new CustomObjectScript_1010;
    break;
  case ID_CUSTOM_OBJECT_1817:
    return new CustomObjectScript_1817;
    break;
  case ID_CUSTOM_OBJECT_081A:
    return new CustomObjectScript_081A;
    break;
  case ID_CUSTOM_OBJECT_081B:
    return new CustomObjectScript_081B;
    break;
  case ID_CUSTOM_OBJECT_081D:
    return new CustomObjectScript_081D;
    break;
  case ID_CUSTOM_OBJECT_081E:
    return new CustomObjectScript_081E;
    break;
  case ID_CUSTOM_OBJECT_081C:
    return new CustomObjectScript_081C;
    break;
  case ID_CUSTOM_OBJECT_0819:
    return new CustomObjectScript_0819;
    break;
  case ID_CUSTOM_OBJECT_101F:
    return new CustomObjectScript_101F;
    break;
  case ID_CUSTOM_OBJECT_0820:
    return new CustomObjectScript_0820;
    break;
  case ID_CUSTOM_OBJECT_0821:
    return new CustomObjectScript_0821;
    break;
  case ID_CUSTOM_OBJECT_0822:
    return new CustomObjectScript_0822;
    break;
  case ID_CUSTOM_OBJECT_0823:
    return new CustomObjectScript_0823;
    break;
  case ID_CUSTOM_OBJECT_1824:
    return new CustomObjectScript_1824;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  default:
    mprintf(0, "SCRIPT: Illegal ID (%d)\n", id);
    break;
  }
  return NULL;
}

// =================
// DestroyInstance()
// =================
void STDCALL DestroyInstance(int id, void *ptr) {
  switch (id) {
  case ID_LEVEL_0000:
    delete ((LevelScript_0000 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_300D:
    delete ((CustomObjectScript_300D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_300C:
    delete ((CustomObjectScript_300C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_300B:
    delete ((CustomObjectScript_300B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_4809:
    delete ((CustomObjectScript_4809 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1803:
    delete ((CustomObjectScript_1803 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1806:
    delete ((CustomObjectScript_1806 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_100A:
    delete ((CustomObjectScript_100A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_300E:
    delete ((CustomObjectScript_300E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2007:
    delete ((CustomObjectScript_2007 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080F:
    delete ((CustomObjectScript_080F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2008:
    delete ((CustomObjectScript_2008 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1011:
    delete ((CustomObjectScript_1011 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1010:
    delete ((CustomObjectScript_1010 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1817:
    delete ((CustomObjectScript_1817 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081A:
    delete ((CustomObjectScript_081A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081B:
    delete ((CustomObjectScript_081B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081D:
    delete ((CustomObjectScript_081D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081E:
    delete ((CustomObjectScript_081E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081C:
    delete ((CustomObjectScript_081C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0819:
    delete ((CustomObjectScript_0819 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_101F:
    delete ((CustomObjectScript_101F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0820:
    delete ((CustomObjectScript_0820 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0821:
    delete ((CustomObjectScript_0821 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0822:
    delete ((CustomObjectScript_0822 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0823:
    delete ((CustomObjectScript_0823 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1824:
    delete ((CustomObjectScript_1824 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  default:
    mprintf(0, "SCRIPT: Illegal ID (%d)\n", id);
    break;
  }
}

// ===================
// CallInstanceEvent()
// ===================
int16_t STDCALL CallInstanceEvent(int id, void *ptr, int event, tOSIRISEventInfo *data) {
  switch (id) {
  case ID_LEVEL_0000:
  case ID_CUSTOM_OBJECT_300D:
  case ID_CUSTOM_OBJECT_300C:
  case ID_CUSTOM_OBJECT_300B:
  case ID_CUSTOM_OBJECT_4809:
  case ID_CUSTOM_OBJECT_1803:
  case ID_CUSTOM_OBJECT_1806:
  case ID_CUSTOM_OBJECT_100A:
  case ID_CUSTOM_OBJECT_300E:
  case ID_CUSTOM_OBJECT_2007:
  case ID_CUSTOM_OBJECT_080F:
  case ID_CUSTOM_OBJECT_2008:
  case ID_CUSTOM_OBJECT_1011:
  case ID_CUSTOM_OBJECT_1010:
  case ID_CUSTOM_OBJECT_1817:
  case ID_CUSTOM_OBJECT_081A:
  case ID_CUSTOM_OBJECT_081B:
  case ID_CUSTOM_OBJECT_081D:
  case ID_CUSTOM_OBJECT_081E:
  case ID_CUSTOM_OBJECT_081C:
  case ID_CUSTOM_OBJECT_0819:
  case ID_CUSTOM_OBJECT_101F:
  case ID_CUSTOM_OBJECT_0820:
  case ID_CUSTOM_OBJECT_0821:
  case ID_CUSTOM_OBJECT_0822:
  case ID_CUSTOM_OBJECT_0823:
  case ID_CUSTOM_OBJECT_1824:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
    return ((BaseScript *)ptr)->CallEvent(event, data);
    break;
  default:
    mprintf(0, "SCRIPT: Illegal ID (%d)\n", id);
    break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

// ==================
// SaveRestoreState()
// ==================
int STDCALL SaveRestoreState(void *file_ptr, uint8_t saving_state) { return 0; }

// ====================
// GetTriggerScriptID()
// ====================
int STDCALL GetTriggerScriptID(int trigger_room, int trigger_face) {
  if (trigger_room == Trigger_rooms[0] && trigger_face == Trigger_faces[0])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0002;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[26];
  static int cust_id_list[26] = {
      ID_CUSTOM_OBJECT_300D, ID_CUSTOM_OBJECT_300C, ID_CUSTOM_OBJECT_300B, ID_CUSTOM_OBJECT_4809, ID_CUSTOM_OBJECT_1803,
      ID_CUSTOM_OBJECT_1806, ID_CUSTOM_OBJECT_100A, ID_CUSTOM_OBJECT_300E, ID_CUSTOM_OBJECT_2007, ID_CUSTOM_OBJECT_080F,
      ID_CUSTOM_OBJECT_2008, ID_CUSTOM_OBJECT_1011, ID_CUSTOM_OBJECT_1010, ID_CUSTOM_OBJECT_1817, ID_CUSTOM_OBJECT_081A,
      ID_CUSTOM_OBJECT_081B, ID_CUSTOM_OBJECT_081D, ID_CUSTOM_OBJECT_081E, ID_CUSTOM_OBJECT_081C, ID_CUSTOM_OBJECT_0819,
      ID_CUSTOM_OBJECT_101F, ID_CUSTOM_OBJECT_0820, ID_CUSTOM_OBJECT_0821, ID_CUSTOM_OBJECT_0822, ID_CUSTOM_OBJECT_0823,
      ID_CUSTOM_OBJECT_1824};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[21];
  cust_handle_list[1] = Object_handles[11];
  cust_handle_list[2] = Object_handles[10];
  cust_handle_list[3] = Object_handles[9];
  cust_handle_list[4] = Object_handles[6];
  cust_handle_list[5] = Object_handles[8];
  cust_handle_list[6] = Object_handles[7];
  cust_handle_list[7] = Object_handles[5];
  cust_handle_list[8] = Object_handles[12];
  cust_handle_list[9] = Object_handles[14];
  cust_handle_list[10] = Object_handles[13];
  cust_handle_list[11] = Object_handles[16];
  cust_handle_list[12] = Object_handles[15];
  cust_handle_list[13] = Object_handles[22];
  cust_handle_list[14] = Object_handles[23];
  cust_handle_list[15] = Object_handles[24];
  cust_handle_list[16] = Object_handles[25];
  cust_handle_list[17] = Object_handles[26];
  cust_handle_list[18] = Object_handles[27];
  cust_handle_list[19] = Object_handles[28];
  cust_handle_list[20] = Object_handles[29];
  cust_handle_list[21] = Object_handles[30];
  cust_handle_list[22] = Object_handles[31];
  cust_handle_list[23] = Object_handles[32];
  cust_handle_list[24] = Object_handles[33];
  cust_handle_list[25] = Object_handles[20];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 26;
}

//=======================
// Script Implementation
//=======================

BaseScript::BaseScript() {}

BaseScript::~BaseScript() {}

int16_t BaseScript::CallEvent(int event, tOSIRISEventInfo *data) {
  mprintf(0, "BaseScript::CallEvent()\n");
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t LevelScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_SAVESTATE: {
    tOSIRISEVTSAVESTATE *event_data = &data->evt_savestate;

    SaveGlobalActionCtrs(event_data->fileptr);
    dfSave(event_data->fileptr);
  } break;
  case EVT_RESTORESTATE: {
    tOSIRISEVTRESTORESTATE *event_data = &data->evt_restorestate;

    RestoreGlobalActionCtrs(event_data->fileptr);
    dfRestore(event_data->fileptr);
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 018: Player Hit, cancel timer & restart
    if ((qObjShields(qGetPlayerObj(0)) < 100.000000f) && ((ScriptActionCtr_016 > 0) == true) &&
        ((ScriptActionCtr_017 > 0) == false)) {
      aCancelTimer(3);
      aCancelTimer(2);
      aSetObjectTimer(Object_handles[12], 14.000000f, 3);
      aSetObjectTimer(Object_handles[5], 20.000000f, 2);
      aShowHUDMessage(Message_strings[16]);
      aObjSetShields(qGetPlayerObj(0), 100.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 025: Follow Test
    if (((ScriptActionCtr_023 > 0) == true) && ((ScriptActionCtr_026 > 0) == false)) {
      if (qObjCanSeeObj(Object_handles[13], 90, qGetPlayerObj(0)) == true) {
      } else {
        aCancelTimer(7);
        aSetObjectTimer(Object_handles[13], 20.000000f, 7);
      }

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 031: Keep Energy up
    if (((ScriptActionCtr_021 > 0) == true) && (qObjEnergy(qGetPlayerObj(0)) < 50.000000f)) {
      aObjSetEnergy(qGetPlayerObj(0), 50.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 030: Keep sheilds up
    if (((ScriptActionCtr_014 > 0) == true) && (qObjShields(qGetPlayerObj(0)) < 50.000000f)) {
      aObjSetShields(qGetPlayerObj(0), 50.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }

    // Script 038: Done Powerups Delay
    if ((ScriptActionCtr_038 < 1) && (((ScriptActionCtr_059 > 0) == true) && ((ScriptActionCtr_040 > 0) == true))) {
      aSetLevelTimer(2.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 034: Ready for last room Delay
    if ((ScriptActionCtr_034 < 1) && (((ScriptActionCtr_043 > 0) == true) && ((ScriptActionCtr_044 > 0) == true) &&
                                      ((ScriptActionCtr_045 > 0) == true) && ((ScriptActionCtr_046 > 0) == true) &&
                                      ((ScriptActionCtr_047 > 0) == true) && ((ScriptActionCtr_048 > 0) == true))) {
      aPortalRenderSet(0, 1, Room_indexes[5], 1);
      aPortalRenderSet(0, 0, Room_indexes[5], 1);
      aObjSetLightingDist(Object_handles[3], 50.000000f);
      aSetLevelTimer(2.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 035: All Bots killed Delay
    if ((ScriptActionCtr_035 < 1) && (((ScriptActionCtr_051 > 0) == true) && ((ScriptActionCtr_052 > 0) == true) &&
                                      ((ScriptActionCtr_053 > 0) == true) && ((ScriptActionCtr_054 > 0) == true) &&
                                      ((ScriptActionCtr_055 > 0) == true))) {
      aSetLevelTimer(2.000000f, 10);
      aObjSetLightingDist(Object_handles[4], 50.000000f);
      aPortalRenderSet(0, 0, Room_indexes[6], 1);
      aPortalRenderSet(0, 1, Room_indexes[6], 1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }

    // Script 060: Is Buddy Out?
    if ((ScriptActionCtr_060 < 1) &&
        ((qObjIsType(qGetBuddyObj(0), 2) == true) && ((ScriptActionCtr_032 > 0) == true))) {
      aSoundPlaySteamingText("GuideBotB.osf", 1.000000f);
      aToggleAllPlayerControls(1, 0);
      aShowHUDMessage(Message_strings[35]);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 058: Buddy Has Returned
    if ((ScriptActionCtr_058 < 1) &&
        ((qObjIsType(qGetBuddyObj(0), 2) == false) && ((ScriptActionCtr_059 > 0) == true))) {
      aObjSetLightingDist(Object_handles[2], 50.000000f);
      aPortalRenderSet(0, 0, Room_indexes[4], 1);
      aPortalRenderSet(0, 1, Room_indexes[4], 1);
      aSoundPlaySteamingText("proceed6.osf", 1.000000f);
      aShowHUDMessage(Message_strings[0]);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Level Start
    if (1) {
      aObjSetLightingDist(Object_handles[0], 0.000000f);
      aObjSetLightingDist(Object_handles[1], 0.000000f);
      aObjSetLightingDist(Object_handles[2], 0.000000f);
      aObjSetLightingDist(Object_handles[3], 0.000000f);
      aObjSetLightingDist(Object_handles[4], 0.000000f);
      aObjSetLightingColor(Object_handles[4], 0.200000f, 1.000000f, 0.200000f);
      aObjSetLightingColor(Object_handles[3], 0.200000f, 1.000000f, 0.200000f);
      aObjSetLightingColor(Object_handles[2], 0.200000f, 1.000000f, 0.200000f);
      aObjSetLightingColor(Object_handles[1], 0.200000f, 1.000000f, 0.200000f);
      aObjSetLightingColor(Object_handles[0], 0.200000f, 1.000000f, 0.200000f);
      aObjMakeInvuln(qGetPlayerObj(0), 0);
      aToggleAllPlayerControls(0, 0);
      aTogglePlayerControl(1, 0, 1);
      aObjHide(Object_handles[5]);
      aObjHide(Object_handles[6]);
      aObjHide(Object_handles[7]);
      aSetLevelTimer(1.000000f, 0);
      aObjHide(Object_handles[8]);
      aObjHide(Object_handles[9]);
      aObjHide(Object_handles[10]);
      aObjHide(Object_handles[11]);
      aAISetState(0, Object_handles[12]);
      aAISetState(0, Object_handles[13]);
      aObjHide(Object_handles[14]);
      aObjGhostSet(1, Object_handles[15]);
      aObjGhostSet(1, Object_handles[16]);
      aObjHide(Object_handles[17]);
      aObjHide(Object_handles[18]);
      aObjHide(Object_handles[19]);
      aObjHide(Object_handles[20]);
      aObjHide(Object_handles[21]);
      aToggleShowPlayerControl(1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 002: First Hud Mesage Timer
    if ((ScriptActionCtr_002 < 1) && ((ScriptActionCtr_002 > 0) == false)) {
      aShowHUDMessage(Message_strings[2]);
      aSoundPlaySteamingText("welcome.osf", 1.000000f);
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 023: Done Bank -- Start Follow
    if ((ScriptActionCtr_023 < 1) && (((ScriptActionCtr_024 > 0) == true) && (4 == event_data->id))) {
      aTogglePlayerControl(1, 0, 4032);
      aShowHUDMessage(Message_strings[14]);
      aShowHUDMessage(Message_strings[15]);
      aAISetState(1, Object_handles[13]);
      aAISetTeam(65536, Object_handles[13]);
      aSetObjectTimer(Object_handles[13], 20.000000f, 7);
      aSoundPlaySteamingText("follow.osf", 1.000000f);
      aAIGoalFollowPathSimple(Object_handles[13], Path_indexes[0], 9437444, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 024: Done Pitch -- Start Bank
    if ((ScriptActionCtr_024 < 1) && ((ScriptActionCtr_022 > 0) == true)) {
      aToggleAllPlayerControls(0, 0);
      aTogglePlayerControl(1, 0, 3072);
      aShowHUDMessage(Message_strings[18]);
      aSoundPlaySteamingText("bank.osf", 1.000000f);
      aSetLevelTimer(15.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 022: Done Heading -- Start Pitch Time
    if ((ScriptActionCtr_022 < 1) && ((ScriptActionCtr_021 > 0) == true)) {
      aShowHUDMessage(Message_strings[0]);
      aToggleAllPlayerControls(0, 0);
      aTogglePlayerControl(1, 0, 192);
      aShowHUDMessage(Message_strings[22]);
      aSoundPlaySteamingText("pitch.osf", 1.000000f);
      aSetLevelTimer(12.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 027: Follow Bot Destroyed
    if ((ScriptActionCtr_027 < 1) && (event_data->id == 11)) {
      aShowHUDMessage(Message_strings[0]);
      aAISetTeam(65536, Object_handles[15]);
      aAISetTeam(65536, Object_handles[16]);
      aObjGhostSet(0, Object_handles[16]);
      aShowHUDMessage(Message_strings[25]);
      aSoundPlaySteamingText("kill1.osf", 1.000000f);
      aAIGoalFollowPathSimple(Object_handles[16], Path_indexes[0], 8392960, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 029: DestroyBot2 Destroyed
    if (event_data->id == 12) {
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[26]);
      aToggleShowPlayerControl(0, 0);
      aSoundPlaySteamingText("proceed5.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 041: Done Powerups
    if ((ScriptActionCtr_041 < 1) && (event_data->id == 13)) {

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }

    // Script 039: Killbot Message 2
    if (event_data->id == 14) {
      aSoundPlaySteamingText("GuidebotF.osf", 1.000000f);
      aShowHUDMessage(Message_strings[30]);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 049: Ready for last room
    if ((ScriptActionCtr_049 < 1) && (event_data->id == 9)) {
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[31]);
      aSoundPlaySteamingText("proceed5.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 056: All Bots killed
    if ((ScriptActionCtr_056 < 1) && (event_data->id == 10)) {
      aShowHUDMessage(Message_strings[33]);
      aSoundPlaySteamingText("done.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_300D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: FirstGoal
    if ((ScriptActionCtr_001 < 1) && (1)) {
      aShowHUDMessage(Message_strings[0]);
      aSoundPlaySteamingText("return1.osf", 1.000000f);
      aShowHUDMessage(Message_strings[1]);
      aTogglePlayerControl(0, 0, 1);
      aTogglePlayerControl(1, 0, 2);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 008: Repeat Forward Goal
    if ((ScriptActionCtr_008 < 1) && ((ScriptActionCtr_007 > 0) == true)) {
      aSoundPlay2D(Sound_indexes[0], 1.000000f);
      aTogglePlayerControl(0, 0, 1);
      aTogglePlayerControl(1, 0, 2);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_300C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Return to Start from Forward Goal
    if ((ScriptActionCtr_003 < 1) && ((ScriptActionCtr_001 > 0) == true)) {
      aShowHUDMessage(Message_strings[4]);
      aTogglePlayerControl(0, 0, 2);
      aSoundPlaySteamingText("left1.osf", 1.000000f);
      aTogglePlayerControl(1, 0, 4);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 005: Return to Start From Left Goal
    if ((ScriptActionCtr_005 < 1) && ((ScriptActionCtr_004 > 0) == true)) {
      aTogglePlayerControl(0, 0, 8);
      aTogglePlayerControl(1, 0, 16);
      aShowHUDMessage(Message_strings[0]);
      aSoundPlaySteamingText("up1.osf", 1.000000f);
      aShowHUDMessage(Message_strings[6]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 007: Return to Start from Up Goal
    if ((ScriptActionCtr_007 < 1) && ((ScriptActionCtr_006 > 0) == true)) {
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[8]);
      aShowHUDMessage(Message_strings[3]);
      aSoundPlaySteamingText("repeat.osf", 1.000000f);
      aTogglePlayerControl(0, 0, 32);
      aTogglePlayerControl(1, 0, 1);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 009: Return to Start from Repeat Forward Goal
    if ((ScriptActionCtr_009 < 1) && ((ScriptActionCtr_008 > 0) == true)) {
      aTogglePlayerControl(0, 0, 2);
      aSoundPlaySteamingText("lright.osf", 1.000000f);
      aTogglePlayerControl(1, 0, 4);
      aShowHUDMessage(Message_strings[4]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 011: Return to Start from Repeat Left Goal
    if ((ScriptActionCtr_011 < 1) && ((ScriptActionCtr_010 > 0) == true)) {
      aTogglePlayerControl(0, 0, 8);
      aTogglePlayerControl(1, 0, 16);
      aSoundPlaySteamingText("udown.osf", 1.000000f);
      aShowHUDMessage(Message_strings[6]);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 013: Return to start from Repeat Up Goal
    if ((ScriptActionCtr_013 < 1) && ((ScriptActionCtr_012 > 0) == true)) {
      aPortalRenderSet(0, 0, Room_indexes[0], 1);
      aPortalRenderSet(0, 1, Room_indexes[0], 1);
      aSoundPlaySteamingText("proceed1.osf", 1.000000f);
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_300B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Left Goal
    if ((ScriptActionCtr_004 < 1) && (1)) {
      aTogglePlayerControl(0, 0, 4);
      aTogglePlayerControl(1, 0, 8);
      aShowHUDMessage(Message_strings[0]);
      aSoundPlaySteamingText("return2.osf", 1.000000f);
      aShowHUDMessage(Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 010: Repeat Left Goal
    if ((ScriptActionCtr_010 < 1) && ((ScriptActionCtr_009 > 0) == true)) {
      aSoundPlay2D(Sound_indexes[0], 1.000000f);
      aTogglePlayerControl(0, 0, 4);
      aTogglePlayerControl(1, 0, 8);
      aShowHUDMessage(Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_4809::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Up Goal
    if ((ScriptActionCtr_006 < 1) && (1)) {
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[7]);
      aTogglePlayerControl(0, 0, 16);
      aSoundPlaySteamingText("return3.osf", 1.000000f);
      aTogglePlayerControl(1, 0, 32);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 012: Repeat Up Goal
    if ((ScriptActionCtr_012 < 1) && ((ScriptActionCtr_011 > 0) == true)) {
      aSoundPlay2D(Sound_indexes[0], 1.000000f);
      aTogglePlayerControl(0, 0, 16);
      aTogglePlayerControl(1, 0, 32);
      aShowHUDMessage(Message_strings[7]);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1803::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Start Course
    if ((ScriptActionCtr_014 < 1) && (1)) {
      aPortalRenderSet(1, 1, Room_indexes[0], 1);
      aShowHUDMessage(Message_strings[10]);
      aSoundPlaySteamingText("Intro1.osf", 1.000000f);
      aTogglePlayerControl(1, 0, 63);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1806::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Finish Course
    if ((ScriptActionCtr_015 < 1) && (1)) {
      aToggleAllPlayerControls(0, 0);
      aTogglePlayerControl(1, 0, 32);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aPortalRenderSet(0, 1, Room_indexes[1], 1);
      aShowHUDMessage(Message_strings[0]);
      aSoundPlaySteamingText("proceed2.osf", 1.000000f);
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_100A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Start Dodge Timer Delay
    if ((ScriptActionCtr_033 < 1) && (1)) {
      aTogglePlayerControl(0, 0, 3);
      aTogglePlayerControl(1, 0, 60);
      aPortalRenderSet(1, 0, Room_indexes[1], 1);
      aPortalRenderSet(1, 1, Room_indexes[1], 1);
      aSoundPlaySteamingText("intro2.osf", 1.000000f);
      aShowHUDMessage(Message_strings[11]);
      aSetObjectTimer(data->me_handle, 10.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 016: Start Dodge
    if ((ScriptActionCtr_016 < 1) && (event_data->id == 8)) {
      aObjSetShields(qGetPlayerObj(0), 100.000000f);
      aShowHUDMessage(Message_strings[12]);
      aSetObjectTimer(Object_handles[5], 20.000000f, 2);
      aSetObjectTimer(Object_handles[12], 14.000000f, 3);
      aAISetState(1, Object_handles[12]);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_300E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Leaving Dodging Room
    if ((ScriptActionCtr_019 < 1) && (1)) {
      aObjSetLightingDist(Object_handles[0], 50.000000f);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aPortalRenderSet(0, 1, Room_indexes[2], 1);
      aTogglePlayerControl(0, 0, 62);
      aSoundPlaySteamingText("proceed4.osf", 1.000000f);
      aShowHUDMessage(Message_strings[17]);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 017: Player Done Dodging
    if ((ScriptActionCtr_017 < 1) && (((ScriptActionCtr_016 > 0) == true) && (event_data->id == 2))) {
      aObjSetLightingDist(Object_handles[0], 50.000000f);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aPortalRenderSet(0, 1, Room_indexes[2], 1);
      aAISetState(0, Object_handles[12]);
      aTogglePlayerControl(1, 0, 3);
      aSoundPlaySteamingText("proceed3.osf", 1.000000f);
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[13]);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 020: Almost Done dodging
    if (event_data->id == 3) {
      aSoundPlaySteamingText("almost.osf", 1.000000f);
      aShowHUDMessage(Message_strings[19]);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Enter Manuver room
    if ((ScriptActionCtr_021 < 1) && ((ScriptActionCtr_020 > 0) == true)) {
      aToggleShowPlayerControl(1, 0);
      aObjSetLightingDist(Object_handles[0], 0.000000f);
      aToggleAllPlayerControls(0, 0);
      aPortalRenderSet(1, 1, Room_indexes[2], 1);
      aPortalRenderSet(1, 0, Room_indexes[2], 1);
      aShowHUDMessage(Message_strings[20]);
      aTogglePlayerControl(1, 0, 768);
      aSetLevelTimer(20.000000f, 4);
      aSoundPlaySteamingText("intro3.osf", 1.000000f);
      aShowHUDMessage(Message_strings[21]);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 037: Follow Bot Destroyed Delay
    if ((ScriptActionCtr_037 < 1) && ((ScriptActionCtr_026 > 0) == true)) {
      aSetLevelTimer(2.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 026: Done Following
    if (((ScriptActionCtr_025 > 0) == true) && (event_data->id == 7)) {
      aTogglePlayerControl(1, 0, 12288);
      aAIGoalFollowPathSimple(Object_handles[13], Path_indexes[1], 4352, 0, 3);
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[23]);
      aSoundPlaySteamingText("intro4.osf", 1.000000f);
      aShowHUDMessage(Message_strings[24]);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 028: DestroyBot1 Destroyed
    if ((ScriptActionCtr_028 < 1) && ((ScriptActionCtr_027 > 0) == true)) {
      aObjGhostSet(0, Object_handles[15]);
      aAIGoalFollowPathSimple(Object_handles[15], Path_indexes[0], 8392960, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 036: DestroyBot2 Destroyed Delay
    if (1) {
      aSetLevelTimer(2.000000f, 12);
      aObjSetLightingDist(Object_handles[1], 50.000000f);
      aPortalRenderSet(0, 1, Room_indexes[3], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aToggleAllPlayerControls(1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1817::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: Got CameraMonitor
    if ((ScriptActionCtr_040 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSoundPlaySteamingText("GuideBotC.osf", 1.000000f);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
      aShowHUDMessage(Message_strings[28]);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 059: Player used camera monitor
    if (1) {
      aSoundPlaySteamingText("GuideBotD.osf", 1.000000f);
      aShowHUDMessage(Message_strings[34]);
      aCreatePopupView(0, Object_handles[34], 10.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 043: RASBot1 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 044: RASBot2 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 045: RASBot 3 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 046: RASBot 4 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: InvulnPowerup2 Picked up
    if ((ScriptActionCtr_047 < 1) && (1)) {

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0819::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: CloakPowerup2 Picked up
    if ((ScriptActionCtr_048 < 1) && (1)) {

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_101F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 051: Lastbot1 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0820::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 052: Lastbot2 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0821::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 053: Lastbot3 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0822::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 054: Lastbot4 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0823::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 055: Lastbot5 Killed
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1824::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Finished!
    if (1) {
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Entered Gallery
    if ((ScriptActionCtr_032 < 1) && (1)) {
      aSoundPlaySteamingText("GuideBotA.osf", 1.000000f);
      aObjSetLightingDist(Object_handles[1], 0.000000f);
      aPortalRenderSet(1, 1, Room_indexes[3], 1);
      aPortalRenderSet(1, 0, Room_indexes[3], 1);
      aShowHUDMessage(Message_strings[0]);
      aShowHUDMessage(Message_strings[27]);
      aToggleAllPlayerControls(0, 0);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Entered KillBot Room
    if ((ScriptActionCtr_042 < 1) && (1)) {
      aSetLevelTimer(13.000000f, 14);
      aObjSetLightingDist(Object_handles[2], 0.000000f);
      aShowHUDMessage(Message_strings[29]);
      aSoundPlaySteamingText("intro6.osf", 1.000000f);
      aPortalRenderSet(1, 1, Room_indexes[4], 1);
      aPortalRenderSet(1, 0, Room_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: Entered Last Room
    if ((ScriptActionCtr_050 < 1) && (1)) {
      aObjSetLightingDist(Object_handles[3], 0.000000f);
      aShowHUDMessage(Message_strings[0]);
      aPortalRenderSet(1, 1, Room_indexes[5], 1);
      aPortalRenderSet(1, 0, Room_indexes[5], 1);
      aSoundPlaySteamingText("intro7.osf", 1.000000f);
      aShowHUDMessage(Message_strings[32]);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

/*********************************************************
Script Save Block: DO NOT TOUCH ANYTHING IN THIS BLOCK!!!
**********************************************************
$$SCRIPT_BLOCK_START

VERSION		3
NEXT_ID		61

// UserType value blocks
$$UTYPE_VALS_START UserVar
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:LevelStartTimer
1:GenericTimer
2:DoneDodging
3:AlmostDoneDodge
4:Bank
5:Pitch
6:Heading
7:FollowTheBot
8:FiringDelay
9:ReadyForLastDelay
10:LastRoomDelay
11:FirstRASDelay
12:SecondTwoDelay
13:PowerupDelay
14:KillbotMessage2
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:GoToDieGoal
1:GoInCircles
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
FlashLight-1
FlashLight-2
FlashLight-3
FlashLight-4
FlashLight-5
DoneDodgeingGoal
StartCourse
StartDodge
FinishCourse
UpGoal
LeftGoal
StartGoal
DodgeTurrett
FollowBot1
ManuverRoomCenter
DestroyBot2
DestroyBot1
GalleryEntered
LastRoomGoal
KillBotGoal
FinalGoal
ForwardGoal
CameraMonitor
RASBot1
RASBot2
RASBot3
RASBot4
InvulnPowerup2
CloakPowerup2
LastBot1
LastBot2
LastBot3
LastBot4
LastBot5
SecurityCamera
$$OBJECT_LIST_END

$$ROOM_LIST_START
PortalRoom1
PortalRoom2
PortalRoom3
PortalRoom4
PortalRoom5
PortalRoom6
PortalRoom7
$$ROOM_LIST_END

$$TRIGGER_LIST_START
Portal2
Portal3
Portal4
$$TRIGGER_LIST_END

$$SOUND_LIST_START
MenuBeepEnter
PupC1
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
return1.osf
welcome.osf
left1.osf
return2.osf
up1.osf
return3.osf
repeat.osf
lright.osf
udown.osf
proceed1.osf
Intro1.osf
proceed2.osf
intro2.osf
proceed3.osf
follow.osf
proceed4.osf
bank.osf
almost.osf
intro3.osf
pitch.osf
intro4.osf
kill1.osf
proceed5.osf
GuideBotA.osf
GuideBotC.osf
intro6.osf
GuidebotF.osf
intro7.osf
done.osf
GuideBotD.osf
GuideBotB.osf
proceed6.osf
$$SPECNAME_LIST_END

$$PATH_LIST_START
FollowLoop1
GoToDie
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Level Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.200000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.200000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.200000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.200000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.200000:Blue
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        06:qGetPlayerObj:Object
                                $$CHILD_BLOCK_START
                                10:4:0:PlayerNum
                                $$CHILD_BLOCK_END
                        10:4:0:Time
                        $$CHILD_BLOCK_END
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:1:PlayerControl
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aToggleShowPlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:FirstGoal
        $$CHILD_BLOCK_START
        01:1:21
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:0:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoBackwards:Message
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:1:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:2:PlayerControl
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:First Hud Mesage Timer
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:2:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Welcome:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:1:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoForward:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Return to Start from Forward Goal
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:1:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoLeft:Message
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:2:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:2:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:4:PlayerControl
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Left Goal
        $$CHILD_BLOCK_START
        01:1:10
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:4:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:8:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:3:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoRight:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Return to Start From Left Goal
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:4:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:8:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:16:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:4:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoUp:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Up Goal
        $$CHILD_BLOCK_START
        01:1:9
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoDown:Message
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:16:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:5:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:32:PlayerControl
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Return to Start from Up Goal
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:6:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Repeat:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoForward:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:6:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:32:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:1:PlayerControl
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Repeat Forward Goal
        $$CHILD_BLOCK_START
        01:1:21
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:7:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:1:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:2:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoBackwards:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Return to Start from Repeat Forward Goal
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:8:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:2:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:7:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:4:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoLeft:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Repeat Left Goal
        $$CHILD_BLOCK_START
        01:1:10
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:9:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:4:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:8:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoRight:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Return to Start from Repeat Left Goal
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:10:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:8:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:16:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:8:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoUp:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Repeat Up Goal
        $$CHILD_BLOCK_START
        01:1:9
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:11:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:16:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:32:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoDown:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Return to start from Repeat Up Goal
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:12:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:9:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ContinueToCourse:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Start Course
        $$CHILD_BLOCK_START
        01:1:6
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CourseInstructions:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:10:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:63:PlayerControl
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Finish Course
        $$CHILD_BLOCK_START
        01:1:8
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:32:PlayerControl
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:11:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ContinueToCourse:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Start Dodge Timer Delay
        $$CHILD_BLOCK_START
        01:1:7
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:3:PlayerControl
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:60:PlayerControl
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:12:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DodgeIntro:Message
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:10.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Start Dodge
        $$CHILD_BLOCK_START
        01:1:7
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        06:qGetPlayerObj:Object
                                $$CHILD_BLOCK_START
                                10:4:0:PlayerNum
                                $$CHILD_BLOCK_END
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Dodge30:Message
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:14.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Player Done Dodging
        $$CHILD_BLOCK_START
        01:1:5
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:16:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:3:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:13:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeaveDodge:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Done Bank -- Start Follow
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:24:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:4:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:4032:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FollowIntro:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FollowInstructions:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:20.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:14:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:16:0:Path
                        10:15:9437444:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Player Hit, cancel timer & restart
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        06:qGetPlayerObj:Object
                                                $$CHILD_BLOCK_START
                                                10:4:0:PlayerNum
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:16:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:17:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:14.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:20.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:KeepDodging:Message
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        06:qGetPlayerObj:Object
                                $$CHILD_BLOCK_START
                                10:4:0:PlayerNum
                                $$CHILD_BLOCK_END
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Leaving Dodging Room
        $$CHILD_BLOCK_START
        01:1:5
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:62:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:15:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:KeepMovingOutofDodging:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Done Pitch -- Start Bank
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:22:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:3072:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BankIntro:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:16:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Almost Done dodging
        $$CHILD_BLOCK_START
        01:1:12
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:17:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:AlmostDoneDodge:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Enter Manuver room
        $$CHILD_BLOCK_START
        01:1:14
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:20:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aToggleShowPlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ManuverIntro:Message
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:768:PlayerControl
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:18:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:HeadingIntro:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Done Heading -- Start Pitch Time
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:21:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:192:PlayerControl
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PitchIntro:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:19:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:12.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Follow Test
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:23:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:26:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeeObj:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:13:TargetObject
                                        10:4:90:Cone
                                        06:qGetPlayerObj:Object
                                                $$CHILD_BLOCK_START
                                                10:4:0:PlayerNum
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aCancelTimer
                                $$CHILD_BLOCK_START
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:13:Object
                                10:6:20.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Done Following
        $$CHILD_BLOCK_START
        01:1:13
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:25:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTogglePlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        10:15:12288:PlayerControl
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:16:1:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:WeaponsEnabled:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:20:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyFollowbot:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Follow Bot Destroyed Delay
        $$CHILD_BLOCK_START
        01:1:13
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:26:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Follow Bot Destroyed
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Movingbotintro:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:21:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:16:0:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:DestroyBot1 Destroyed
        $$CHILD_BLOCK_START
        01:1:16
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:27:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:16:0:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Keep Energy up
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:21:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjEnergy:Float
                                        $$CHILD_BLOCK_START
                                        06:qGetPlayerObj:Object
                                                $$CHILD_BLOCK_START
                                                10:4:0:PlayerNum
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:50.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetEnergy
                        $$CHILD_BLOCK_START
                        06:qGetPlayerObj:Object
                                $$CHILD_BLOCK_START
                                10:4:0:PlayerNum
                                $$CHILD_BLOCK_END
                        10:6:50.000000:Energy
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Keep sheilds up
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:14:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        06:qGetPlayerObj:Object
                                                $$CHILD_BLOCK_START
                                                10:4:0:PlayerNum
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:50.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        06:qGetPlayerObj:Object
                                $$CHILD_BLOCK_START
                                10:4:0:PlayerNum
                                $$CHILD_BLOCK_END
                        10:6:50.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:DestroyBot2 Destroyed Delay
        $$CHILD_BLOCK_START
        01:1:15
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:DestroyBot2 Destroyed
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ExitManuveur:Message
                        $$CHILD_BLOCK_END
                08:aToggleShowPlayerControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:22:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Entered Gallery
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:23:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GBIntro:Message
                        $$CHILD_BLOCK_END
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Got CameraMonitor
        $$CHILD_BLOCK_START
        01:1:22
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:24:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:UseCameraMonitor:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Done Powerups Delay
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:59:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:40:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Done Powerups
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Entered KillBot Room
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:13.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:KillBotIntro:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:25:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Killbot Message 2
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:26:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:KillBot2:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:RASBot1 Killed
        $$CHILD_BLOCK_START
        01:1:23
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:RASBot2 Killed
        $$CHILD_BLOCK_START
        01:1:24
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:RASBot 3 Killed
        $$CHILD_BLOCK_START
        01:1:25
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:RASBot 4 Killed
        $$CHILD_BLOCK_START
        01:1:26
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:InvulnPowerup2 Picked up
        $$CHILD_BLOCK_START
        01:1:27
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:CloakPowerup2 Picked up
        $$CHILD_BLOCK_START
        01:1:28
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Ready for last room Delay
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:43:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:44:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:46:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:47:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:48:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Ready for last room
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ProceedtoLastRoom:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:22:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Entered Last Room
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:27:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FinalSessionIntro:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Lastbot1 Killed
        $$CHILD_BLOCK_START
        01:1:29
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Lastbot2 Killed
        $$CHILD_BLOCK_START
        01:1:30
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Lastbot3 Killed
        $$CHILD_BLOCK_START
        01:1:31
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Lastbot4 Killed
        $$CHILD_BLOCK_START
        01:1:32
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Lastbot5 Killed
        $$CHILD_BLOCK_START
        01:1:33
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:All Bots killed Delay
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:51:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:52:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:53:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:54:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:55:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:6:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:6:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:All Bots killed
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:AllDone:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:28:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Finished!
        $$CHILD_BLOCK_START
        01:1:20
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Player used camera monitor
        $$CHILD_BLOCK_START
        01:1:22
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:29:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GBExtra:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:34:Object
                        10:6:10.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Is Buddy Out?
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsType:Bool
                                        $$CHILD_BLOCK_START
                                        06:qGetBuddyObj:Object
                                                $$CHILD_BLOCK_START
                                                10:4:0:PlayerNum
                                                $$CHILD_BLOCK_END
                                        10:10:0:2:ObjectType
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:32:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:30:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aToggleAllPlayerControls
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PlayerNum
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GetCameraMonitor:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Buddy Has Returned
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsType:Bool
                                        $$CHILD_BLOCK_START
                                        06:qGetBuddyObj:Object
                                                $$CHILD_BLOCK_START
                                                10:4:0:PlayerNum
                                                $$CHILD_BLOCK_END
                                        10:10:0:2:ObjectType
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:59:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingText
                        $$CHILD_BLOCK_START
                        10:13:31:SoundName
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GoodJob:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
