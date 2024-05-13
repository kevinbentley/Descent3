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
// Filename:	Merc4.cpp
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

#define ID_CUSTOM_OBJECT_0811 0x001
#define ID_CUSTOM_OBJECT_0804 0x002
#define ID_CUSTOM_OBJECT_0803 0x003
#define ID_CUSTOM_OBJECT_3198 0x004
#define ID_CUSTOM_OBJECT_099A 0x005
#define ID_CUSTOM_OBJECT_099E 0x006
#define ID_CUSTOM_OBJECT_09A0 0x007
#define ID_CUSTOM_OBJECT_080A 0x008
#define ID_CUSTOM_OBJECT_09AC 0x009
#define ID_CUSTOM_OBJECT_1138 0x00a
#define ID_CUSTOM_OBJECT_11B2 0x00b
#define ID_CUSTOM_OBJECT_31B7 0x00c
#define ID_CUSTOM_OBJECT_11D1 0x00d
#define ID_CUSTOM_OBJECT_09D2 0x00e

#define ID_TRIGGER_0003 0x00f
#define ID_TRIGGER_0010 0x010
#define ID_TRIGGER_0011 0x011
#define ID_TRIGGER_0013 0x012
#define ID_TRIGGER_0014 0x013
#define ID_TRIGGER_0012 0x014
#define ID_TRIGGER_0015 0x015
#define ID_TRIGGER_0016 0x016
#define ID_TRIGGER_0004 0x017
#define ID_TRIGGER_0005 0x018
#define ID_TRIGGER_0006 0x019
#define ID_TRIGGER_0007 0x01a
#define ID_TRIGGER_0002 0x01b
#define ID_TRIGGER_0000 0x01c
#define ID_TRIGGER_0001 0x01d
#define ID_TRIGGER_000D 0x01e
#define ID_TRIGGER_000E 0x01f
#define ID_TRIGGER_0008 0x020
#define ID_TRIGGER_000F 0x021
#define ID_TRIGGER_0009 0x022
#define ID_TRIGGER_000A 0x023
#define ID_TRIGGER_000B 0x024
#define ID_TRIGGER_000C 0x025

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

class CustomObjectScript_0811 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0804 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0803 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3198 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_099A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_099E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09AC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1138 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11B2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_31B7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11D1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09D2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
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

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000C : public BaseScript {
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
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_062 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_062 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

#include "AIGame3_External.h"

/*
$$ENUM Region
0:Intro
1:OuterShell
2:Hive
3:Boss
$$END
*/

/*
$$ACTION
Custom
Play imediate object [o:Object] animation from frame [i:StartFrame] to [i:EndFrame=1], cycle time = [f:CycleTime=1.0],
looping = [b:Looping=FALSE] aObjPlayImmAnim Play object animation Plays an animation for an object

Parameters:
  Object: the object to animate
  StartFrame: the frame number of the start of the animation
  EndFrame: the frame number of the end of the animation
  CycleTime: how long the entire animation takes
  Looping: if true, animation repeats.  If false, animation plays once
$$END
*/
void aObjPlayImmAnim(int objref, int startframe, int endframe, float cycletime, bool looping) {
  int flags = 0;

  if (!qObjExists(objref))
    return;

  if (looping)
    flags |= AIAF_LOOPING;

  Obj_SetCustomAnim(objref, (float)startframe, (float)endframe, cycletime, flags | AIAF_IMMEDIATE, -1, -1);
}

/*
$$ACTION
Custom
For [o:Alien Boss], set [o:Nest], [r:Left Hide Room], [r:Right Hide Room]
aABSetScenarioIDs
Sets Alien Boss' Scenario IDs

Parameters:
  Alien Boss: the alien boss
  Nest: the nest object
  Left Hide Room: room to hide from thruster on left
  Right Hide Room: room to hide from thruster on the right
$$END
*/
void aABSetScenarioIDs(int obj_handle, int nest_handle, int left_hide_room, int right_hide_room) {
  ab_scenario_ids ids;

  if (!qObjExists(obj_handle))
    return;

  ids.nest_handle = nest_handle;
  ids.left_hide_room = left_hide_room;
  ids.right_hide_room = right_hide_room;

  SendCommand(obj_handle, obj_handle, AB_COM_SET_SCENARIO_IDS, &ids);
}

/*
$$QUERY
Custom
b:[o:Alien Boss] is healing
qIsAlienBossHealing
Alien Boss is healing
Checks to see if Alien Boss is healing at the nest

Parameters:
  Alien Boss: the alien boss
$$END
*/
bool qIsAlienBossHealing(int obj_handle) {
  bool boss_healing;

  if (!qObjExists(obj_handle))
    return false;

  SendCommand(obj_handle, obj_handle, AB_COM_IS_NESTING, &boss_healing);

  return boss_healing;
}

/*
$$QUERY
Custom
b:[o:Alien Boss] is healing (tells it thruster fired)
qAlienBossHealing
Alien Boss is healing
Checks to see if Alien Boss is healing at the nest when thruster is fired.

Parameters:
  Alien Boss: the alien boss
$$END
*/
bool qAlienBossHealing(int obj_handle) {
  bool boss_healing;

  if (!qObjExists(obj_handle))
    return false;

  SendCommand(obj_handle, obj_handle, AB_COM_THRUSTER_IS_FIRING, &boss_healing);

  return boss_healing;
}

/*
$$ACTION
Custom
Tell [o:Alien Boss] that thruster misfired
aABThrusterMisfired
Tells Alien Boss that thruster misfired

Parameters:
  Alien Boss: the alien boss
$$END
*/
void aABThrusterMisfired(int obj_handle) {
  if (!qObjExists(obj_handle))
    return;

  SendCommand(obj_handle, obj_handle, AB_COM_THRUSTER_MISFIRED, NULL);
}

/*
$$ACTION
Custom
Tell [o:Alien Boss] that thruster was ignited
aABThrusterIgnited
Tells Alien Boss that thruster was ignited

Parameters:
  Alien Boss: the alien boss
$$END
*/
void aABThrusterIgnited(int obj_handle) {
  if (!qObjExists(obj_handle))
    return;

  SendCommand(obj_handle, obj_handle, AB_COM_THRUSTER_IGNITED, NULL);
}

/*
$$ACTION
Custom
Tell [o:Alien Boss] that it's showtime for [f:Time] seconds
aABItsShowtime
Tells Alien Boss that it is showtime

Parameters:
  Alien Boss: the alien boss
  Time: seconds to do "intro" wandering
$$END
*/
void aABItsShowtime(int obj_handle, float time) {
  if (!qObjExists(obj_handle))
    return;

  SendCommand(obj_handle, obj_handle, AB_COM_ITS_SHOWTIME, &time);
}

/*
$$ACTION
Custom
Tell [o:Alien Boss] to start waiting effect
aABStartWaitEffect
Tells Alien Boss to start waiting effect
Parameters:
  Alien Boss: the alien boss
$$END
*/
void aABStartWaitEffect(int obj_handle) {
  if (!qObjExists(obj_handle))
    return;

  SendCommand(obj_handle, obj_handle, AB_COM_START_WAITING_EFFECT, NULL);
}

/*
$$ACTION
Custom
Tell [o:Alien Organism] to hunt to [o:Destination Object]
aAlienOrganismHunt
Tell Alien Organism to hunt to Destination Object
Causes an alien organism (and possibly its squad) to go hunting toward a particular object.

Parameters:
  Alien Organism: the alien that should go hunting
  Destination Object: the object to hunt towards
$$END
*/
void aAlienOrganismHunt(int alien_handle, int dest_handle) {
  if (!qObjExists(alien_handle))
    return;
  if (!qObjExists(dest_handle))
    return;

  SendCommand(alien_handle, alien_handle, ALIEN_COM_HUNT_TO_OBJ, &dest_handle);
}

/*
$$ACTION
Custom
Emit [f:Number=20.0] sparks from [o:Object]
aEmitSparks
Make object spark
  Makes an object emit sparks

Parameters:
  Number: the number of sparks to create
  Object: the object to make sparks come out of
$$END
*/
void aEmitSparks(float num_sparks, int objhandle) {
  int room;
  vector pos;

  if (!qObjExists(objhandle))
    return;

  Obj_Value(objhandle, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(objhandle, VF_GET, OBJV_I_ROOMNUM, &room);
  Game_CreateRandomSparks((int)num_sparks, &pos, room);
}

bool names_looked_up = false;
uint16_t guidebot_id;

#define MAX_SCAN_OBJECTS 20

/*
$$ACTION
Custom
Kill robots and players near [o:Object]
aKillBotsNearObj
Kill robots and players near object
  Kills robots and players near an object

Parameters:
  Object: the object to search from
$$END
*/
void aKillBotsNearObj(int objhandle) {
  int room;
  vector pos;
  float radius;
  int type;
  int scan_objs[MAX_SCAN_OBJECTS];
  int n_scan;
  int n, i;
  uint16_t id;

  if (!qObjExists(objhandle))
    return;

  // Look up names if we haven't already
  if (!names_looked_up) {
    guidebot_id = Obj_FindID("GuideBot");
    names_looked_up = true;
  }

  // Make sure this object still exists
  Obj_Value(objhandle, VF_GET, OBJV_I_TYPE, &type);
  if (type == OBJ_NONE)
    return;

  // Get the size and position of the object
  Obj_Value(objhandle, VF_GET, OBJV_F_SIZE, &radius);
  Obj_Value(objhandle, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(objhandle, VF_GET, OBJV_I_ROOMNUM, &room);

  // Scan for any nearby objects
  // NOTE: check the func below to see what other params do!!!
  n_scan = AI_GetNearbyObjs(&pos, room, radius, scan_objs, MAX_SCAN_OBJECTS, false, true, false, true);

  // Go through the objects that have been found and kill any robots or players
  for (i = 0; i < n_scan; i++) {
    Obj_Value(scan_objs[i], VF_GET, OBJV_I_TYPE, &type);
    if (type == OBJ_ROBOT || type == OBJ_PLAYER) {
      // Make sure it's not the guidebot
      if (type == OBJ_ROBOT) {
        Obj_Value(scan_objs[i], VF_GET, OBJV_US_ID, &id);
        if (id == ROBOT_GUIDEBOT || id == ROBOT_GUIDEBOTRED)
          continue;
      }

      // Just do damage to players, but destroy robots on contact
      if (type == OBJ_PLAYER) {
        aObjApplyDamage(scan_objs[i], 5.0f);
      } else {
        aObjDestroy(scan_objs[i]);
      }
    }
  }
}

int teleport_effect_id = -1;

/*
$$ACTION
Custom
Clear teleporter area at [o:Destination] for [o:Teleportee]
aClearTeleporterArea
Clears teleporter destination area of robots
  Kills robots and players near teleport destination

Parameters:
  Destination: the destination object
  Teleportee: the object being teleported
$$END
*/
void aClearTeleporterArea(int desthandle, int objhandle) {
  int room;
  vector pos;
  matrix orient;
  int type;
  int n, i;

  if (!qObjExists(objhandle))
    return;
  if (!qObjExists(desthandle))
    return;

  // Make sure this object still exists
  Obj_Value(desthandle, VF_GET, OBJV_I_TYPE, &type);
  if (type == OBJ_NONE)
    return;

  Obj_Value(objhandle, VF_GET, OBJV_I_TYPE, &type);
  if (type == OBJ_NONE)
    return;

  // Get the position of the dest object
  Obj_Value(desthandle, VF_GET, OBJV_V_POS, &pos);
  Obj_Value(desthandle, VF_GET, OBJV_M_ORIENT, &orient);
  Obj_Value(desthandle, VF_GET, OBJV_I_ROOMNUM, &room);

  // Create the teleport-in effect just below the destination
  pos.y -= 1.0f;

  // Look up the weapon effect
  if (teleport_effect_id < 0)
    teleport_effect_id = Wpn_FindID("TeleportEffect");

  Obj_Create(OBJ_WEAPON, teleport_effect_id, room, &pos, &orient, desthandle);
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

#define NUM_DOOR_NAMES 3
static const char *const Door_names[NUM_DOOR_NAMES] = {"AirlockInnerDoor", "AirlockOuterDoor", "DoorWon'tOpenFar"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 79
static const char *const Object_names[NUM_OBJECT_NAMES] = {"TeleporterA1",
                                                           "TeleporterA2",
                                                           "TeleporterB1",
                                                           "TeleporterC1",
                                                           "TeleporterC2",
                                                           "EscapeTrigger",
                                                           "Maw1",
                                                           "Maw2",
                                                           "Maw3",
                                                           "Maw4",
                                                           "Maw5",
                                                           "WallShuttle",
                                                           "DataArm1",
                                                           "DataArm2",
                                                           "BossMinion1",
                                                           "BossMinion2",
                                                           "Greenbot1",
                                                           "Greenbot2",
                                                           "SharkAmbush1",
                                                           "Greenbot3",
                                                           "Greenbot4",
                                                           "Greenbot5",
                                                           "Greenbot6",
                                                           "Greenbot7",
                                                           "Greenbot8",
                                                           "Greenbot9",
                                                           "Greenbot10",
                                                           "Greenbot11",
                                                           "Greenbot12",
                                                           "Greenbot13",
                                                           "Greenbot14",
                                                           "Greenbot15",
                                                           "Greenbot16",
                                                           "Greenbot17",
                                                           "Greenbot18",
                                                           "Greenbot19",
                                                           "BossDeathCamTarget",
                                                           "AlienBoss",
                                                           "AlienBossNest",
                                                           "AirlockDoorSwitch",
                                                           "AirlockOuterDoor",
                                                           "AirlockOuterCam1",
                                                           "AirlockOuterCam2",
                                                           "AirlockInnerDoor",
                                                           "AirlockInnerCam1",
                                                           "AirlockInnerCam2",
                                                           "AirlockSound",
                                                           "TeleporterA1Dest",
                                                           "TeleporterA1Cam2",
                                                           "TeleporterA2Cam2",
                                                           "TeleporterA2Dest",
                                                           "TeleporterC1Dest",
                                                           "TeleporterC2Dest",
                                                           "TeleporterA1Cam",
                                                           "TeleporterA2Cam",
                                                           "DoorWon'tOpenFar",
                                                           "BadDoorCam1",
                                                           "BadDoorCam2",
                                                           "CruiserFuse",
                                                           "FusePosition",
                                                           "FuseBeamB",
                                                           "FuseBeamA",
                                                           "ThrusterSwitch",
                                                           "ThrusterCam",
                                                           "Cocoon1Ambusher1",
                                                           "Ambush1HuntDest",
                                                           "Cocoon1Ambusher2",
                                                           "Cocoon1Ambusher3",
                                                           "Cocoon2Ambusher1",
                                                           "AlienAmbush1",
                                                           "AlienAmbush2A",
                                                           "AlienAmbush2B",
                                                           "AlienBossPosition",
                                                           "RoomASteamer1",
                                                           "RoomASteamer2",
                                                           "RoomBSteamer",
                                                           "RoomCSteamer",
                                                           "RoomDSteamer",
                                                           "RoomESteamer"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 31
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "AirlockRoom",     "AirlockIDRoom", "AirlockODRoom",      "BossRoomA",        "BossRoomB",         "BossRoomC",
    "BossRoomD",       "BossRoomE",     "ThrusterSwitchRoom", "BossLeftHideRoom", "BossRightHideRoom", "TeleporterA2",
    "TeleporterA1",    "Maw1EntryRoom", "Maw1Room",           "Maw2EntryRoom",    "Maw2Room",          "Maw3EntryRoom",
    "Maw3Room",        "Maw4EntryRoom", "Maw4Room",           "Maw5EntryRoom",    "Maw5Room",          "ForcefieldRoom",
    "CocoonAmb1Cell1", "Coc1AmbCell2",  "CocAmb2Cell1",       "SharkAmbush1",     "AlienAmbush2",      "CaveinRoom",
    "CaveinRoom2"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 23
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "AirlockTrigger",      "LeftOuterShell",    "EnteredHiveArea1", "EnteredHive2",
    "EnteredHive3",        "LeftHiveArea1",     "LeftHive2",        "LeftHive3",
    "ForcefieldRoomTrigg", "LowerQuadTrigger",  "NestTrigger1",     "NestTrigger2",
    "ThrusterTrigger",     "Ambush1",           "Ambush2",          "SharkAmbush1",
    "AlienAmbush2",        "BossIntroTrigger",  "LeftBossArea",     "BossIntroTrigger2",
    "BossIntroTrigger3",   "BossIntroTrigger4", "BossIntroTrigger5"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 16
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "AmbSwitch41",   "EnvSteamEmitG",    "DoorIsLocked", "EnvSlowCreakD",  "EnvSlowCreakE", "Merc4Vortex",
    "Wall fade ???", "AmbMatCenProduce", "EnvElectricE", "Powerup pickup", "EnvElectricA",  "AmbSwitch31",
    "Merc4Thruster", "Merc4BossDeath",   "Merc4Rumble",  "AmbSwitch11"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 4
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"CC_JetEngine", "Alien_Forcefield02", "FunkyEffect3",
                                                             "CC_JetEngineLit"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 7
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCamPath",  "IntroPlayerPath", "BossDeathCam",
                                                       "BossDeathPath", "Escape2CamPath",  "EscapePath2",
                                                       "BossIntroCam2"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 13
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Engage Airlock Power",
                                                       "Enter Outer Shell through Airlock",
                                                       "Teleport into Planetoid's Core",
                                                       "Disable Alien Forcefield Generators",
                                                       "Enter Sealed Quadrant of Alien Hive",
                                                       "Activate Main Thruster",
                                                       "Acquire Spare Fuse",
                                                       "Restore Power to Derelict Ship",
                                                       "Force Alien Queen to Nest",
                                                       "Manually Ignite Thruster Burn",
                                                       "Destroy Alien Planetoid",
                                                       "Escape",
                                                       "Investigate and Destroy Alien Planetoid"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 30
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroText",
                                                             "AirlockPowerOn",
                                                             "AirlockDecompStarted",
                                                             "AirlockActive",
                                                             "AirlockPowerNotOn",
                                                             "AirlockCompStarted",
                                                             "AirlockMalfunction",
                                                             "BadDoorBumped",
                                                             "FFMessage",
                                                             "UseThruster",
                                                             "CruiserFuseAcquired",
                                                             "CruiserFusePlaced",
                                                             "CruiserFuseNoUse",
                                                             "QueenLeft",
                                                             "NoBurnIgnited",
                                                             "NoPowerAvail",
                                                             "IgniterFailed1",
                                                             "IgniterFailed2",
                                                             "BurnIgnited",
                                                             "ThrusterBurnFailed",
                                                             "RechargeThruster1",
                                                             "RechargeThruster2",
                                                             "Empty",
                                                             "GetOuttaHere",
                                                             "FuseRoom",
                                                             "BossIntro",
                                                             "DA1Game",
                                                             "DA1Hud",
                                                             "DA2Game",
                                                             "DA2Hud"};
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
  char english_filename[(_MAX_PATH + 32) * 2];
  int lang_type;
  if (func_list->script_identifier != NULL) {
    _splitpath(func_list->script_identifier, NULL, NULL, filename, NULL);
    snprintf(english_filename, sizeof(english_filename), "%s.msg", filename);
    lang_type = Game_GetLanguage();
    if (lang_type == LANGUAGE_FRENCH)
      strcat(filename, "_FRN");
    else if (lang_type == LANGUAGE_GERMAN)
      strcat(filename, "_GER");
    else if (lang_type == LANGUAGE_ITALIAN)
      strcat(filename, "_ITN");
    else if (lang_type == LANGUAGE_SPANISH)
      strcat(filename, "_SPN");
    else if (lang_type == LANGUAGE_POLISH)
      strcat(filename, "_POL");
    strcat(filename, ".msg");
  } else {
    strcpy(filename, "Merc4.msg");
    lang_type = LANGUAGE_ENGLISH;
  }
  if (!ReadMessageFile(filename)) {
    if (lang_type == LANGUAGE_ENGLISH) {
      mprintf(0, "ERROR: Could not load message file - %s\n", filename);
    } else if (!ReadMessageFile(english_filename)) {
      mprintf(0, "ERROR: Could not load message file - %s\n", english_filename);
    }
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
  case ID_CUSTOM_OBJECT_0811:
    return new CustomObjectScript_0811;
    break;
  case ID_CUSTOM_OBJECT_0804:
    return new CustomObjectScript_0804;
    break;
  case ID_CUSTOM_OBJECT_0803:
    return new CustomObjectScript_0803;
    break;
  case ID_CUSTOM_OBJECT_3198:
    return new CustomObjectScript_3198;
    break;
  case ID_CUSTOM_OBJECT_099A:
    return new CustomObjectScript_099A;
    break;
  case ID_CUSTOM_OBJECT_099E:
    return new CustomObjectScript_099E;
    break;
  case ID_CUSTOM_OBJECT_09A0:
    return new CustomObjectScript_09A0;
    break;
  case ID_CUSTOM_OBJECT_080A:
    return new CustomObjectScript_080A;
    break;
  case ID_CUSTOM_OBJECT_09AC:
    return new CustomObjectScript_09AC;
    break;
  case ID_CUSTOM_OBJECT_1138:
    return new CustomObjectScript_1138;
    break;
  case ID_CUSTOM_OBJECT_11B2:
    return new CustomObjectScript_11B2;
    break;
  case ID_CUSTOM_OBJECT_31B7:
    return new CustomObjectScript_31B7;
    break;
  case ID_CUSTOM_OBJECT_11D1:
    return new CustomObjectScript_11D1;
    break;
  case ID_CUSTOM_OBJECT_09D2:
    return new CustomObjectScript_09D2;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
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
  case ID_CUSTOM_OBJECT_0811:
    delete ((CustomObjectScript_0811 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0804:
    delete ((CustomObjectScript_0804 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0803:
    delete ((CustomObjectScript_0803 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3198:
    delete ((CustomObjectScript_3198 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_099A:
    delete ((CustomObjectScript_099A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_099E:
    delete ((CustomObjectScript_099E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A0:
    delete ((CustomObjectScript_09A0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080A:
    delete ((CustomObjectScript_080A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09AC:
    delete ((CustomObjectScript_09AC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1138:
    delete ((CustomObjectScript_1138 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11B2:
    delete ((CustomObjectScript_11B2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_31B7:
    delete ((CustomObjectScript_31B7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11D1:
    delete ((CustomObjectScript_11D1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09D2:
    delete ((CustomObjectScript_09D2 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
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
  case ID_CUSTOM_OBJECT_0811:
  case ID_CUSTOM_OBJECT_0804:
  case ID_CUSTOM_OBJECT_0803:
  case ID_CUSTOM_OBJECT_3198:
  case ID_CUSTOM_OBJECT_099A:
  case ID_CUSTOM_OBJECT_099E:
  case ID_CUSTOM_OBJECT_09A0:
  case ID_CUSTOM_OBJECT_080A:
  case ID_CUSTOM_OBJECT_09AC:
  case ID_CUSTOM_OBJECT_1138:
  case ID_CUSTOM_OBJECT_11B2:
  case ID_CUSTOM_OBJECT_31B7:
  case ID_CUSTOM_OBJECT_11D1:
  case ID_CUSTOM_OBJECT_09D2:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000C:
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
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_000C;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[14];
  static int cust_id_list[14] = {
      ID_CUSTOM_OBJECT_0811, ID_CUSTOM_OBJECT_0804, ID_CUSTOM_OBJECT_0803, ID_CUSTOM_OBJECT_3198, ID_CUSTOM_OBJECT_099A,
      ID_CUSTOM_OBJECT_099E, ID_CUSTOM_OBJECT_09A0, ID_CUSTOM_OBJECT_080A, ID_CUSTOM_OBJECT_09AC, ID_CUSTOM_OBJECT_1138,
      ID_CUSTOM_OBJECT_11B2, ID_CUSTOM_OBJECT_31B7, ID_CUSTOM_OBJECT_11D1, ID_CUSTOM_OBJECT_09D2};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[39];
  cust_handle_list[1] = Object_handles[40];
  cust_handle_list[2] = Object_handles[43];
  cust_handle_list[3] = Object_handles[0];
  cust_handle_list[4] = Object_handles[1];
  cust_handle_list[5] = Object_handles[3];
  cust_handle_list[6] = Object_handles[4];
  cust_handle_list[7] = Object_handles[55];
  cust_handle_list[8] = Object_handles[58];
  cust_handle_list[9] = Object_handles[62];
  cust_handle_list[10] = Object_handles[37];
  cust_handle_list[11] = Object_handles[5];
  cust_handle_list[12] = Object_handles[12];
  cust_handle_list[13] = Object_handles[13];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 14;
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
#ifdef ENABLE_CUSTOM_SAVE_AND_RESTORE
    dsCustomSave(event_data->fileptr);
#endif
  } break;
  case EVT_RESTORESTATE: {
    tOSIRISEVTRESTORESTATE *event_data = &data->evt_restorestate;

    RestoreGlobalActionCtrs(event_data->fileptr);
    dfRestore(event_data->fileptr);
#ifdef ENABLE_CUSTOM_SAVE_AND_RESTORE
    dsCustomRestore(event_data->fileptr);
#endif
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 018: Check if any Maws have been broken
    if (qUserFlag(18) == false) {
      if ((qUserFlag(3) == false) && (qPortalIsOn(1, Room_indexes[13]) == false)) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[6], 1.000000f);
        aRoomSetWind(Room_indexes[13], 0.469000f, 0.000000f, 0.883000f, qUserVarValue(2));
        aRoomChangeWind(Room_indexes[13], 0.469000f, 0.000000f, 0.883000f, 0.500000f, qUserVarValue(1));
        aRoomChangeFog(Room_indexes[14], 0.000000f, 0.000000f, 0.000000f, 40.000000f, qUserVarValue(1));
        aSetLevelTimer(qUserVarValue(1), 10);
        aUserFlagSet(3, 1);
      }
      if ((qUserFlag(4) == false) && (qPortalIsOn(0, Room_indexes[15]) == false)) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[7], 1.000000f);
        aRoomSetWind(Room_indexes[15], 0.707000f, 0.000000f, 0.707000f, qUserVarValue(2));
        aRoomChangeWind(Room_indexes[15], 0.707000f, 0.000000f, 0.707000f, 0.500000f, qUserVarValue(1));
        aRoomChangeFog(Room_indexes[16], 0.000000f, 0.000000f, 0.000000f, 40.000000f, qUserVarValue(1));
        aSetLevelTimer(qUserVarValue(1), 11);
        aUserFlagSet(4, 1);
      }
      if ((qUserFlag(5) == false) && (qPortalIsOn(0, Room_indexes[17]) == false)) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[8], 1.000000f);
        aRoomSetWind(Room_indexes[17], -0.866000f, 0.000000f, 0.500000f, qUserVarValue(2));
        aRoomChangeWind(Room_indexes[17], -0.870000f, 0.000000f, 0.500000f, 0.500000f, qUserVarValue(1));
        aRoomChangeFog(Room_indexes[18], 0.000000f, 0.000000f, 0.000000f, 40.000000f, qUserVarValue(1));
        aSetLevelTimer(qUserVarValue(1), 12);
        aUserFlagSet(5, 1);
      }
      if ((qUserFlag(6) == false) && (qPortalIsOn(0, Room_indexes[19]) == false)) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[9], 1.000000f);
        aRoomSetWind(Room_indexes[19], -0.743000f, 0.000000f, 0.669000f, qUserVarValue(2));
        aRoomChangeWind(Room_indexes[19], -0.740000f, 0.000000f, 0.670000f, 0.500000f, qUserVarValue(1));
        aRoomChangeFog(Room_indexes[20], 0.000000f, 0.000000f, 0.000000f, 40.000000f, qUserVarValue(1));
        aSetLevelTimer(qUserVarValue(1), 13);
        aUserFlagSet(6, 1);
      }
      if ((qUserFlag(7) == false) && (qPortalIsOn(0, Room_indexes[21]) == false)) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[10], 1.000000f);
        aRoomSetWind(Room_indexes[21], 0.574000f, 0.000000f, -0.819000f, qUserVarValue(2));
        aRoomChangeWind(Room_indexes[21], 0.574000f, 0.000000f, -0.819000f, 0.500000f, qUserVarValue(1));
        aRoomChangeFog(Room_indexes[22], 0.000000f, 0.000000f, 0.000000f, 40.000000f, qUserVarValue(1));
        aSetLevelTimer(qUserVarValue(1), 14);
        aUserFlagSet(7, 1);
      }
      if ((qUserFlag(9) == true) && (qUserFlag(10) == true) && (qUserFlag(11) == true) && (qUserFlag(12) == true) &&
          (qUserFlag(13) == true)) {
        aPortalRenderSet(0, 1, Room_indexes[23], 1);
        aPortalRenderSet(0, 2, Room_indexes[23], 1);
        aPortalRenderSet(0, 3, Room_indexes[23], 1);
        aPortalRenderSet(0, 4, Room_indexes[23], 1);
        aPortalRenderSet(0, 5, Room_indexes[23], 1);
        aUserFlagSet(18, 1);
        aGoalCompleted(Goal_indexes[3], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Level Start - Init Flags and Variables
    if (1) {
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aUserFlagSet(6, 0);
      aUserFlagSet(7, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(11, 0);
      aUserFlagSet(12, 0);
      aUserFlagSet(13, 0);
      aUserFlagSet(8, 0);
      aUserFlagSet(14, 0);
      aUserFlagSet(15, 0);
      aUserFlagSet(16, 0);
      aUserFlagSet(17, 0);
      aUserFlagSet(18, 0);
      aUserFlagSet(19, 0);
      aUserVarSet(0, 0.000000f);
      aUserVarSet(1, 10.000000f);
      aUserVarSet(2, 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 001: Level Start - Misc
    if (1) {
      aRoomSetWind(Room_indexes[0], 0.985000f, 0.000000f, -0.174000f, 0.000000f);
      aRoomSetWind(Room_indexes[1], 0.985000f, 0.000000f, -0.174000f, 0.000000f);
      aRoomSetWind(Room_indexes[2], 0.985000f, 0.000000f, -0.174000f, 0.000000f);
      aObjHide(Object_handles[0]);
      aObjHide(Object_handles[1]);
      aObjHide(Object_handles[2]);
      aObjHide(Object_handles[3]);
      aObjHide(Object_handles[4]);
      aObjHide(Object_handles[5]);
      aObjGhostSet(1, Object_handles[6]);
      aObjGhostSet(1, Object_handles[7]);
      aObjGhostSet(1, Object_handles[8]);
      aObjGhostSet(1, Object_handles[9]);
      aObjGhostSet(1, Object_handles[10]);
      aObjMakeInvuln(Object_handles[11], 1000000);
      aObjMakeInvuln(Object_handles[12], 1000000);
      aObjMakeInvuln(Object_handles[13], 1000000);
      aSetLevelTimer(0.400000f, 9);
      aSetLevelTimer(2.000000f, 21);
      aRoomSetFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 20000.000000f);
      aRoomSetFog(Room_indexes[4], 0.500000f, 0.500000f, 0.500000f, 20000.000000f);
      aRoomSetFog(Room_indexes[5], 0.500000f, 0.500000f, 0.500000f, 20000.000000f);
      aRoomSetFog(Room_indexes[6], 0.500000f, 0.500000f, 0.500000f, 20000.000000f);
      aRoomSetFog(Room_indexes[7], 0.500000f, 0.500000f, 0.500000f, 20000.000000f);
      aRoomSetFog(Room_indexes[8], 0.500000f, 0.500000f, 0.500000f, 20000.000000f);
      aSetLevelTimer(1.000000f, 27);
      aAISetState(0, Object_handles[14]);
      aAISetState(0, Object_handles[15]);
      aObjGhostSet(1, Object_handles[14]);
      aObjGhostSet(1, Object_handles[15]);
      aRoomSetFaceTexture(Room_indexes[3], 472, Texture_indexes[0]);
      aEnableVirusInfection(1, Object_handles[16]);
      aEnableVirusInfection(1, Object_handles[17]);
      aEnableVirusInfection(1, Object_handles[18]);
      aEnableVirusInfection(1, Object_handles[19]);
      aEnableVirusInfection(1, Object_handles[20]);
      aEnableVirusInfection(1, Object_handles[21]);
      aEnableVirusInfection(1, Object_handles[22]);
      aEnableVirusInfection(1, Object_handles[23]);
      aEnableVirusInfection(1, Object_handles[24]);
      aEnableVirusInfection(1, Object_handles[25]);
      aEnableVirusInfection(1, Object_handles[26]);
      aEnableVirusInfection(1, Object_handles[27]);
      aEnableVirusInfection(1, Object_handles[28]);
      aEnableVirusInfection(1, Object_handles[29]);
      aEnableVirusInfection(1, Object_handles[30]);
      aEnableVirusInfection(1, Object_handles[31]);
      aEnableVirusInfection(1, Object_handles[32]);
      aEnableVirusInfection(1, Object_handles[33]);
      aEnableVirusInfection(1, Object_handles[34]);
      aEnableVirusInfection(1, Object_handles[35]);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 002: Level Start - Into Movie
    if (1) {
      aMusicSetRegionAll(0);
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[36], Path_indexes[1], 12.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 037: Initialize Boss Scenario
    if (event_data->id == 21) {
      aABSetScenarioIDs(Object_handles[37], Object_handles[38], Room_indexes[9], Room_indexes[10]);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }

    // Script 005: Do Airlock Decompression Check
    if (event_data->id == 0) {
      aUserVarInc(0);
      if (((qDoorGetPos(Door_handles[1]) == 0.000000f) && (qDoorGetPos(Door_handles[0]) == 0.000000f)) ||
          (qUserVarValue(0) == 12.000000f)) {
        aTurnOnSpew(Object_handles[44], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                    2.000000f, 8.000000f, 1, -1);
        aTurnOnSpew(Object_handles[45], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                    2.000000f, 8.000000f, 1, -1);
        aSoundPlayObject(Sound_indexes[1], Object_handles[44], 1.000000f);
        aSoundPlayObject(Sound_indexes[1], Object_handles[45], 1.000000f);
        aDoorActivate(Door_handles[0]);
        if (qUserVarValue(0) == 12.000000f) {
          aShowHUDMessage(Message_strings[6]);
        }
        aSetLevelTimer(2.000000f, 1);
      } else {
        if (qUserVarValue(0) == 3.000000f) {
          aSoundPlayObject(Sound_indexes[3], Object_handles[44], 1.000000f);
        }
        aSetLevelTimer(2.000000f, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 012: Do Airlock Compression Check
    if (event_data->id == 4) {
      aUserVarInc(0);
      if (((qDoorGetPos(Door_handles[1]) == 0.000000f) && (qDoorGetPos(Door_handles[0]) == 0.000000f)) ||
          (qUserVarValue(0) == 12.000000f)) {
        aTurnOnSpew(Object_handles[41], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                    2.000000f, 8.000000f, 1, -1);
        aTurnOnSpew(Object_handles[42], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                    2.000000f, 8.000000f, 1, -1);
        aSoundPlayObject(Sound_indexes[1], Object_handles[41], 1.000000f);
        aSoundPlayObject(Sound_indexes[1], Object_handles[42], 1.000000f);
        aDoorActivate(Door_handles[1]);
        if (qUserVarValue(0) == 12.000000f) {
          aShowHUDMessage(Message_strings[6]);
        }
        aSetLevelTimer(2.000000f, 5);
      } else {
        if (qUserVarValue(0) == 3.000000f) {
          aSoundPlayObject(Sound_indexes[4], Object_handles[41], 1.000000f);
        }
        aSetLevelTimer(2.000000f, 4);
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 006: Open Inner Airlock Door
    if (event_data->id == 1) {
      if (qDoorGetPos(Door_handles[1]) != 0.000000f) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[46], 1.000000f);
        aRoomChangeWind(Room_indexes[0], -0.985000f, 0.000000f, 0.174000f, 10.000000f, 1.000000f);
        aRoomChangeWind(Room_indexes[1], -0.985000f, 0.000000f, 0.174000f, 10.000000f, 1.000000f);
        aRoomChangeWind(Room_indexes[2], -0.985000f, 0.000000f, 0.174000f, 10.000000f, 1.000000f);
        aSetLevelTimer(1.000000f, 3);
      }
      aSetLevelTimer(15.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 009: Open Outer Airlock Door
    if (event_data->id == 5) {
      if (qDoorGetPos(Door_handles[0]) != 0.000000f) {
        aRoomChangeWind(Room_indexes[0], 0.985000f, 0.000000f, -0.174000f, 10.000000f, 1.000000f);
        aRoomChangeWind(Room_indexes[1], 0.985000f, 0.000000f, -0.174000f, 10.000000f, 1.000000f);
        aRoomChangeWind(Room_indexes[2], 0.985000f, 0.000000f, -0.174000f, 10.000000f, 1.000000f);
        aSetLevelTimer(1.000000f, 3);
      }
      aSetLevelTimer(15.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 007: Complete Airlock Decompression
    if ((event_data->id == 2) || (event_data->id == 6)) {
      aUserFlagSet(1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 008: Stop Airlock Wind
    if (event_data->id == 3) {
      aRoomChangeWind(Room_indexes[0], 0.985000f, 0.000000f, -0.174000f, 0.000000f, 2.000000f);
      aRoomChangeWind(Room_indexes[1], 0.985000f, 0.000000f, -0.174000f, 0.000000f, 2.000000f);
      aRoomChangeWind(Room_indexes[2], 0.985000f, 0.000000f, -0.174000f, 0.000000f, 2.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 015: Make Teleporter A Spark
    if (event_data->id == 7) {
      aEmitSparks(qRandomValue(10.000000f, 25.000000f), Object_handles[53]);
      aEmitSparks(qRandomValue(10.000000f, 25.000000f), Object_handles[54]);
      aSetLevelTimer(qRandomValue(0.250000f, 1.500000f), 7);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 017: Make Bad Door Stutter
    if (event_data->id == 8) {
      if (ScriptActionCtr_017 == 0) {
        aEmitSparks(35.000000f, Object_handles[57]);
        aDoorSetPos(Door_handles[2], 0.550000f);
        aSetLevelTimer(0.500000f, 8);
      }
      if (ScriptActionCtr_017 == 1) {
        aEmitSparks(40.000000f, Object_handles[56]);
        aDoorSetPos(Door_handles[2], 0.650000f);
        aSoundPlayObject(Sound_indexes[8], Object_handles[55], 1.000000f);
        aShowHUDMessage(Message_strings[7]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 026: Do Maw Robot/Player Check
    if (event_data->id == 9) {
      if ((qUserFlag(3) == true) && (qUserFlag(9) == false)) {
        aKillBotsNearObj(Object_handles[6]);
      }
      if ((qUserFlag(4) == true) && (qUserFlag(10) == false)) {
        aKillBotsNearObj(Object_handles[7]);
      }
      if ((qUserFlag(5) == true) && (qUserFlag(11) == false)) {
        aKillBotsNearObj(Object_handles[8]);
      }
      if ((qUserFlag(6) == true) && (qUserFlag(12) == false)) {
        aKillBotsNearObj(Object_handles[9]);
      }
      if ((qUserFlag(7) == true) && (qUserFlag(13) == false)) {
        aKillBotsNearObj(Object_handles[10]);
      }
      aSetLevelTimer(0.250000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 019: Maw 1 is Dead
    if (event_data->id == 10) {
      aUserFlagSet(9, 1);
      aGoalItemCompleted(Goal_indexes[3], 1, 1);
      aRoomSetFaceTexture(Room_indexes[23], 273, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 020: Maw 2 is Dead
    if (event_data->id == 11) {
      aUserFlagSet(10, 1);
      aGoalItemCompleted(Goal_indexes[3], 2, 1);
      aRoomSetFaceTexture(Room_indexes[23], 271, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 021: Maw 3 is Dead
    if (event_data->id == 12) {
      aUserFlagSet(11, 1);
      aGoalItemCompleted(Goal_indexes[3], 3, 1);
      aRoomSetFaceTexture(Room_indexes[23], 269, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 022: Maw 4 is Dead
    if (event_data->id == 13) {
      aUserFlagSet(12, 1);
      aGoalItemCompleted(Goal_indexes[3], 4, 1);
      aRoomSetFaceTexture(Room_indexes[23], 270, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 023: Maw 5 is Dead
    if (event_data->id == 14) {
      aUserFlagSet(13, 1);
      aGoalItemCompleted(Goal_indexes[3], 5, 1);
      aRoomSetFaceTexture(Room_indexes[23], 268, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 049: Do Nest Trigger
    if ((ScriptActionCtr_049 < 1) && (event_data->id == 26)) {
      aShowHUDMessage(Message_strings[9]);
      aGoalEnableDisable(1, Goal_indexes[5]);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 036: Power Restored
    if (event_data->id == 20) {
      aUserFlagSet(14, 1);
      aGoalCompleted(Goal_indexes[7], 1);
      aGoalEnableDisable(1, Goal_indexes[5]);
      aSoundPlayObject(Sound_indexes[0], Object_handles[59], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 050: Do Boss At Nest Check
    if (event_data->id == 27) {
      if (qUserFlag(19) == true) {
        if (qIsAlienBossHealing(Object_handles[37]) == true) {
          if (qGoalCompleted(Goal_indexes[8]) == false) {
            aGoalCompleted(Goal_indexes[8], 1);
          }
        } else {
          if (qGoalCompleted(Goal_indexes[8]) == true) {
            aGoalCompleted(Goal_indexes[8], 0);
            aShowHUDMessage(Message_strings[13]);
          }
        }
      }
      aSetLevelTimer(0.500000f, 27);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }

    // Script 033: Igniter Failed Sequence
    if (event_data->id == 19) {
      if (ScriptActionCtr_033 == 0) {
        aTurnOnSpew(Object_handles[63], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.300000f, -1.000000f,
                    12.000000f, 60.000000f, 0, 0);
        aShowHUDMessage(Message_strings[16]);
        aRoomChangeFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 5000.000000f, 20.000000f);
        aSetLevelTimer(6.000000f, 19);
      }
      if (ScriptActionCtr_033 == 1) {
        aShowHUDMessage(Message_strings[17]);
        aGoalEnableDisable(1, Goal_indexes[9]);
        aSetLevelTimer(2.000000f, 18);
      }

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 034: Recharge Thruster Sequence
    if (event_data->id == 17) {
      if (qUserVarValue(3) == 0.000000f) {
        aShowHUDMessage(Message_strings[19]);
        aSetLevelTimer(6.000000f, 17);
        aGoalEnableDisable(1, Goal_indexes[8]);
        aUserFlagSet(19, 1);
      }
      if (qUserVarValue(3) == 1.000000f) {
        aShowHUDMessage(Message_strings[20]);
        aSetLevelTimer(10.000000f, 17);
      }
      if (qUserVarValue(3) == 2.000000f) {
        aShowHUDMessage(Message_strings[21]);
        aSetLevelTimer(1.000000f, 18);
      }
      aUserVarInc(3);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 032: Reset the Thruster Switch
    if (event_data->id == 18) {
      aObjPlayAnim(Object_handles[62], 1, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[11], Object_handles[62], 1.000000f);
      aUserFlagSet(17, 0);
      aGoalCompleted(Goal_indexes[5], 0);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 029: Do Cocoon 1's Ambushes
    if (event_data->id == 15) {
      if (ScriptActionCtr_029 == 0) {
        aPortalBreakGlass(0, Room_indexes[24]);
        aSetLevelTimer(2.000000f, 15);
        aAlienOrganismHunt(Object_handles[64], Object_handles[65]);
      }
      if (ScriptActionCtr_029 == 1) {
        aPortalBreakGlass(0, Room_indexes[25]);
        aAlienOrganismHunt(Object_handles[66], Object_handles[65]);
        aAlienOrganismHunt(Object_handles[67], Object_handles[65]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 031: Do Cocoon 2's Ambushes
    if (event_data->id == 16) {
      if (ScriptActionCtr_031 == 0) {
        aPortalBreakGlass(0, Room_indexes[26]);
        aAlienOrganismHunt(Object_handles[68], Object_handles[65]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 038: Boss Death Sequence
    if (event_data->id == 22) {
      if (ScriptActionCtr_038 == 0) {
        aCinematicSimple(Path_indexes[2], Message_strings[22], Object_handles[36], 15.000000f, 1);
        aStoreObjectInPositionClipboard(Object_handles[72]);
        aMoveObjectToPositionClipboard(Object_handles[37]);
        aObjPlayImmAnim(Object_handles[37], 1, 10, 2.000000f, 0);
        aSetLevelTimer(2.000000f, 22);
      }
      if (ScriptActionCtr_038 == 1) {
        aObjPlayAnim(Object_handles[37], 10, 25, 1.000000f, 0);
        aMiscShakeArea(Object_handles[36], 20.000000f, 200.000000f);
        aTurnOnSpew(Object_handles[63], -1, 1, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 5.000000f,
                    23.000000f, 170.000000f, 0, -1);
        aSoundPlayObject(Sound_indexes[12], Object_handles[63], 1.000000f);
        aSetLevelTimer(1.000000f, 22);
      }
      if (ScriptActionCtr_038 == 2) {
        aObjPlayAnim(Object_handles[37], 25, 36, 0.600000f, 1);
        aSetObjectOnFire(Object_handles[37], 8.000000f, 0.000000f);
        aObjSpark(Object_handles[37], 40.000000f, 10.000000f);
        aEmitSparks(30.000000f, Object_handles[37]);
        aAISetMaxSpeed(Object_handles[37], 6.000000f);
        aObjSetMovementType(Object_handles[37], 1);
        aAIGoalFollowPathSimple(Object_handles[37], Path_indexes[3], 131076, -1, 3);
        aSoundPlayObject(Sound_indexes[13], Object_handles[37], 1.000000f);
        aSetLevelTimer(3.000000f, 22);
      }
      if (ScriptActionCtr_038 == 3) {
        aEmitSparks(20.000000f, Object_handles[37]);
        aObjPlayAnim(Object_handles[37], 25, 36, 0.500000f, 1);
        aSetLevelTimer(2.000000f, 22);
        aSoundPlayObject(Sound_indexes[13], Object_handles[37], 1.000000f);
      }
      if (ScriptActionCtr_038 == 4) {
        aEmitSparks(40.000000f, Object_handles[37]);
        aSetLevelTimer(1.500000f, 22);
      }
      if (ScriptActionCtr_038 == 5) {
        aEmitSparks(50.000000f, Object_handles[37]);
        aObjPlayAnim(Object_handles[37], 25, 36, 0.400000f, 1);
        aSetLevelTimer(1.500000f, 22);
        aSoundPlayObject(Sound_indexes[13], Object_handles[37], 1.000000f);
      }
      if (ScriptActionCtr_038 == 6) {
        aMiscShakeArea(Object_handles[36], 40.000000f, 200.000000f);
        aObjKill(Object_handles[37], 0, 2, 131296, 0.000000f, 0.000000f);
        aObjSpark(Object_handles[11], 50.000000f, 3.000000f);
        aSetLevelTimer(0.200000f, 22);
      }
      if (ScriptActionCtr_038 == 7) {
        aObjMakeVulnerable(Object_handles[11]);
        aObjKill(Object_handles[11], 0, 2, 131296, 0.000000f, 0.000000f);
        aPortalRenderSet(0, 3, Room_indexes[3], 1);
        aPortalRenderSet(0, 4, Room_indexes[3], 1);
        aPortalRenderSet(0, 5, Room_indexes[3], 1);
        aPortalRenderSet(0, 6, Room_indexes[3], 1);
        aPortalRenderSet(0, 7, Room_indexes[3], 1);
        aPortalRenderSet(0, 8, Room_indexes[3], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 039: Escape Sequence
    if (event_data->id == 23) {
      if (ScriptActionCtr_039 == 0) {
        aPortalBreakGlass(1, Room_indexes[8]);
        aRoomChangeFog(Room_indexes[8], 0.000000f, 1.000000f, 0.000000f, 800.000000f, 5.000000f);
        aRoomSetDamage(Room_indexes[3], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[4], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[5], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[6], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[7], 1.000000f, 1);
        aSetLevelTimer(3.000000f, 23);
        aGoalCompleted(Goal_indexes[10], 1);
        aGoalEnableDisable(1, Goal_indexes[11]);
      }
      if (ScriptActionCtr_039 == 1) {
        aShowHUDMessage(Message_strings[23]);
        aRoomSetDamage(Room_indexes[8], 1.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 042: Do Level Shakes
    if (event_data->id == 25) {
      aMiscShakeArea(Object_handles[36], qRandomValue(50.000000f, 90.000000f), 5000.000000f);
      aSoundPlay2D(Sound_indexes[14], 1.000000f);
      aSetLevelTimer(qRandomValue(2.000000f, 4.000000f), 25);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 040: End Level Escape Movie
    if ((ScriptActionCtr_040 < 1) && (event_data->id == 24)) {
      aGoalCompleted(Goal_indexes[12], 1);
      aStartEndlevelSequencePath(Path_indexes[4], Path_indexes[5], 3.500000f, Message_strings[22]);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 053: Boss Intro Cinematic
    if ((ScriptActionCtr_053 < 1) && (event_data->id == 28)) {
      aCinematicSimple(Path_indexes[6], Message_strings[25], Object_handles[37], 13.000000f, 1);
      aSetLevelTimer(9.000000f, 29);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 051: Start Boss Wandering
    if ((ScriptActionCtr_051 < 1) && (event_data->id == 29)) {
      aABItsShowtime(Object_handles[37], 4.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0811::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Airlock Power Switch Hit
    if ((ScriptActionCtr_004 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aUserFlagSet(0, 1);
      aShowHUDMessage(Message_strings[1]);
      aGoalCompleted(Goal_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0804::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Airlock Outer Door Hit
    if (1) {
      if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
        if (qUserFlag(0) == true) {
          if (qUserFlag(1) == false) {
            aUserFlagSet(1, 1);
            aDoorActivate(data->me_handle);
            aTurnOnSpew(Object_handles[41], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                        2.000000f, 8.000000f, 1, -1);
            aTurnOnSpew(Object_handles[42], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                        2.000000f, 8.000000f, 1, -1);
            aSoundPlayObject(Sound_indexes[1], Object_handles[41], 1.000000f);
            aSoundPlayObject(Sound_indexes[1], Object_handles[42], 1.000000f);
            if (qDoorGetPos(Door_handles[0]) == 0.000000f) {
              aShowHUDMessage(Message_strings[2]);
              aUserVarSet(0, 0.000000f);
              aSetLevelTimer(2.000000f, 0);
            } else {
              aSetLevelTimer(2.000000f, 5);
            }
          } else {
            aShowHUDMessage(Message_strings[3]);
            aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          }
        } else {
          aShowHUDMessage(Message_strings[4]);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aGoalEnableDisable(1, Goal_indexes[0]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0803::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Airlock Inner Door Hit
    if (1) {
      if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
        if (qUserFlag(0) == true) {
          if (qUserFlag(1) == false) {
            aUserFlagSet(1, 1);
            aDoorActivate(data->me_handle);
            aTurnOnSpew(Object_handles[44], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                        2.000000f, 8.000000f, 1, -1);
            aTurnOnSpew(Object_handles[45], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.200000f, 3.000000f,
                        2.000000f, 8.000000f, 1, -1);
            aSoundPlayObject(Sound_indexes[1], Object_handles[44], 1.000000f);
            aSoundPlayObject(Sound_indexes[1], Object_handles[45], 1.000000f);
            if (qDoorGetPos(Door_handles[1]) == 0.000000f) {
              aShowHUDMessage(Message_strings[5]);
              aUserVarSet(0, 0.000000f);
              aSetLevelTimer(2.000000f, 4);
            } else {
              aSetLevelTimer(2.000000f, 1);
            }
          } else {
            aShowHUDMessage(Message_strings[3]);
            aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          }
        } else {
          aShowHUDMessage(Message_strings[4]);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3198::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Teleporter A1 Hit
    if ((ScriptActionCtr_010 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_060 > 0) == false))) {
      aStoreObjectInPositionClipboard(Object_handles[47]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aClearTeleporterArea(Object_handles[47], event_data->it_handle);
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);
      aSoundPlayObject(Sound_indexes[7], event_data->it_handle, 1.000000f);
      aPortalRenderSet(0, 0, Room_indexes[11], 1);
      aPortalRenderSet(0, 1, Room_indexes[11], 1);
      aPortalRenderSet(0, 2, Room_indexes[11], 1);
      aPortalRenderSet(0, 3, Room_indexes[11], 1);
      aPortalRenderSet(0, 4, Room_indexes[11], 1);
      aPortalRenderSet(0, 5, Room_indexes[11], 1);
      aPortalRenderSet(0, 6, Room_indexes[11], 1);
      aPortalRenderSet(0, 7, Room_indexes[11], 1);
      aPortalRenderSet(0, 8, Room_indexes[11], 1);
      aPortalRenderSet(0, 9, Room_indexes[11], 1);
      aPortalRenderSet(0, 10, Room_indexes[11], 1);
      aPortalRenderSet(0, 11, Room_indexes[11], 1);
      aPortalRenderSet(0, 0, Room_indexes[12], 1);
      aPortalRenderSet(0, 1, Room_indexes[12], 1);
      aPortalRenderSet(0, 2, Room_indexes[12], 1);
      aPortalRenderSet(0, 3, Room_indexes[12], 1);
      aPortalRenderSet(0, 4, Room_indexes[12], 1);
      aPortalRenderSet(0, 5, Room_indexes[12], 1);
      aPortalRenderSet(0, 6, Room_indexes[12], 1);
      aPortalRenderSet(0, 7, Room_indexes[12], 1);
      aPortalRenderSet(0, 8, Room_indexes[12], 1);
      aPortalRenderSet(0, 9, Room_indexes[12], 1);
      aPortalRenderSet(0, 10, Room_indexes[12], 1);
      aPortalRenderSet(0, 11, Room_indexes[12], 1);
      aSetLevelTimer(1.000000f, 7);
      aTurnOnSpew(Object_handles[48], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[49], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aGoalCompleted(Goal_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_099A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Teleporter A2 Hit
    if ((ScriptActionCtr_060 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_010 > 0) == false))) {
      aStoreObjectInPositionClipboard(Object_handles[50]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aClearTeleporterArea(Object_handles[50], event_data->it_handle);
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);
      aSoundPlayObject(Sound_indexes[7], event_data->it_handle, 1.000000f);
      aPortalRenderSet(0, 0, Room_indexes[11], 1);
      aPortalRenderSet(0, 1, Room_indexes[11], 1);
      aPortalRenderSet(0, 2, Room_indexes[11], 1);
      aPortalRenderSet(0, 3, Room_indexes[11], 1);
      aPortalRenderSet(0, 4, Room_indexes[11], 1);
      aPortalRenderSet(0, 5, Room_indexes[11], 1);
      aPortalRenderSet(0, 6, Room_indexes[11], 1);
      aPortalRenderSet(0, 7, Room_indexes[11], 1);
      aPortalRenderSet(0, 8, Room_indexes[11], 1);
      aPortalRenderSet(0, 9, Room_indexes[11], 1);
      aPortalRenderSet(0, 10, Room_indexes[11], 1);
      aPortalRenderSet(0, 11, Room_indexes[11], 1);
      aPortalRenderSet(0, 0, Room_indexes[12], 1);
      aPortalRenderSet(0, 1, Room_indexes[12], 1);
      aPortalRenderSet(0, 2, Room_indexes[12], 1);
      aPortalRenderSet(0, 3, Room_indexes[12], 1);
      aPortalRenderSet(0, 4, Room_indexes[12], 1);
      aPortalRenderSet(0, 5, Room_indexes[12], 1);
      aPortalRenderSet(0, 6, Room_indexes[12], 1);
      aPortalRenderSet(0, 7, Room_indexes[12], 1);
      aPortalRenderSet(0, 8, Room_indexes[12], 1);
      aPortalRenderSet(0, 9, Room_indexes[12], 1);
      aPortalRenderSet(0, 10, Room_indexes[12], 1);
      aPortalRenderSet(0, 11, Room_indexes[12], 1);
      aSetLevelTimer(1.000000f, 7);
      aTurnOnSpew(Object_handles[48], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aTurnOnSpew(Object_handles[49], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                  2.000000f, 8.000000f, 1, -1);
      aGoalCompleted(Goal_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_099E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Teleporter C1 Hit
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aStoreObjectInPositionClipboard(Object_handles[51]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aClearTeleporterArea(Object_handles[51], event_data->it_handle);
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);
      aGoalCompleted(Goal_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Teleporter C2 Hit
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aStoreObjectInPositionClipboard(Object_handles[52]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aClearTeleporterArea(Object_handles[52], event_data->it_handle);
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Bad Door Hit
    if (1) {
      if ((qUserFlag(2) == false) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
        aEmitSparks(20.000000f, Object_handles[56]);
        aDoorSetPos(Door_handles[2], 0.600000f);
        aSetLevelTimer(1.500000f, 8);
        aUserFlagSet(2, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09AC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Player Picks Up Cruiser Fuse
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(8) == false)) {
      aSoundPlayObject(Sound_indexes[9], event_data->it_handle, 1.000000f);
      aShowHUDMessageObj(Message_strings[10], event_data->it_handle);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aGoalCompleted(Goal_indexes[6], 1);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 025: Used Cruiser Fuse
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(8) == false)) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[59]) < 40.000000f) {
        aStoreObjectInPositionClipboard(Object_handles[59]);
        aMoveObjectToPositionClipboard(data->me_handle);
        aObjGhostSet(1, data->me_handle);
        aSoundPlayObject(Sound_indexes[10], Object_handles[59], 1.000000f);
        aShowHUDMessage(Message_strings[11]);
        aUserFlagSet(8, 1);
        aLightningCreate(Object_handles[60], Object_handles[61], 10000.000000f, 2.000000f, 3, Texture_indexes[2],
                         0.600000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(2.000000f, 20);
      } else {
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
        aShowHUDMessageObj(Message_strings[12], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1138::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Thruster Switch Hit
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(17) == false)) {
      if (qUserFlag(14) == true) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          if (qUserFlag(15) == true) {
            if (qUserFlag(16) == true) {
              aMiscShakeArea(Object_handles[63], 40.000000f, 5000.000000f);
              aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
              aSoundPlayObject(Sound_indexes[11], data->me_handle, 1.000000f);
              aGoalCompleted(Goal_indexes[5], 1);
              if (qAlienBossHealing(Object_handles[37]) == true) {
                aUserFlagSet(19, 0);
                if (qGoalCompleted(Goal_indexes[8]) == false) {
                  aGoalCompleted(Goal_indexes[8], 1);
                }
                aUserFlagSet(17, 1);
                aSetLevelTimer(2.000000f, 22);
              } else {
                aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
                aSoundPlayObject(Sound_indexes[11], data->me_handle, 1.000000f);
                aTurnOnSpew(Object_handles[63], -1, 1, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f,
                            23.000000f, 145.000000f, 0, -1);
                aSoundPlayObject(Sound_indexes[12], Object_handles[63], 1.000000f);
                aUserVarSet(3, 0.000000f);
                aUserFlagSet(17, 1);
                aSetLevelTimer(5.000000f, 17);
              }
            } else {
              aShowHUDMessage(Message_strings[14]);
            }
          } else {
            aMiscShakeArea(Object_handles[63], 20.000000f, 5000.000000f);
            aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[11], data->me_handle, 1.000000f);
            aUserFlagSet(15, 1);
            aABThrusterMisfired(Object_handles[37]);
            aUserFlagSet(17, 1);
            aTurnOnSpew(Object_handles[63], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f,
                        16.000000f, 130.000000f, 0, -1);
            aRoomChangeFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 400.000000f, 2.500000f);
            aSetLevelTimer(3.000000f, 19);
          }
        }
      } else {
        aShowHUDMessage(Message_strings[15]);
        aGoalEnableDisable(1, Goal_indexes[6]);
        aGoalEnableDisable(1, Goal_indexes[7]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11B2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 041: Alien Boss Died
    if (1) {
      aRoomSetFog(Room_indexes[29], 0.500000f, 0.500000f, 0.500000f, 100.000000f);
      aRoomSetFog(Room_indexes[30], 0.500000f, 0.500000f, 0.500000f, 300.000000f);
      aPortalRenderSet(1, 0, Room_indexes[29], 0);
      aRoomChangeFog(Room_indexes[3], 0.000000f, 1.000000f, 0.000000f, 1000.000000f, 8.000000f);
      aRoomChangeFog(Room_indexes[4], 0.000000f, 1.000000f, 0.000000f, 1000.000000f, 8.000000f);
      aRoomChangeFog(Room_indexes[5], 0.000000f, 1.000000f, 0.000000f, 1000.000000f, 8.000000f);
      aRoomChangeFog(Room_indexes[6], 0.000000f, 1.000000f, 0.000000f, 1000.000000f, 8.000000f);
      aRoomChangeFog(Room_indexes[7], 0.000000f, 1.000000f, 0.000000f, 1000.000000f, 8.000000f);
      aTurnOnSpew(Object_handles[73], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.400000f, -1.000000f,
                  6.000000f, 10.000000f, 1, -1);
      aTurnOnSpew(Object_handles[74], -1, 7, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.400000f, -1.000000f,
                  6.000000f, 10.000000f, 1, -1);
      aTurnOnSpew(Object_handles[75], -1, 7, 0.000000f, 0.000000f, 65536, 0, 6.000000f, 0.400000f, -1.000000f,
                  6.000000f, 10.000000f, 1, -1);
      aTurnOnSpew(Object_handles[76], -1, 7, 0.000000f, 0.000000f, 65536, 0, 5.000000f, 0.400000f, -1.000000f,
                  6.000000f, 10.000000f, 1, -1);
      aTurnOnSpew(Object_handles[77], -1, 7, 0.000000f, 0.000000f, 65536, 0, 5.000000f, 0.400000f, -1.000000f,
                  6.000000f, 10.000000f, 1, -1);
      aTurnOnSpew(Object_handles[78], -1, 7, 0.000000f, 0.000000f, 65536, 0, 6.000000f, 0.400000f, -1.000000f,
                  6.000000f, 10.000000f, 1, -1);
      aSetLevelTimer(6.000000f, 23);
      aSetLevelTimer(6.000000f, 25);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_31B7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Escape Trigger Hit
    if ((ScriptActionCtr_043 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[11], 1);
      aSetLevelTimer(0.100000f, 24);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11D1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Data Arm #1 Bumped
    if ((ScriptActionCtr_061 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[15], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[26], Message_strings[27]);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09D2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Data Arm #2 Bumped
    if ((ScriptActionCtr_062 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[15], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[28], Message_strings[29]);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Player passed through Airlock
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalCompleted(Goal_indexes[1], 1);
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Player Left Outer Shell
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aMusicSetRegion(0, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Entered Hive Area 1 Trigger Hit
    if ((ScriptActionCtr_065 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Entered Hive Area 2 Trigger Hit
    if ((ScriptActionCtr_066 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Entered Hive Area 3 Trigger Hit
    if ((ScriptActionCtr_067 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Left Hive Area 1 Trigger Hit
    if ((ScriptActionCtr_068 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Left Hive Area 2 Trigger Hit
    if ((ScriptActionCtr_069 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Left Hive Area 3 Trigger Hit
    if ((ScriptActionCtr_070 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: Player Flew into Forcefield Room
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if ((qGoalCompleted(Goal_indexes[3]) == false) && (qGoalEnabled(Goal_indexes[3]) == false)) {
        aGoalEnableDisable(1, Goal_indexes[3]);
        aShowHUDMessage(Message_strings[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: Player Entered Lower Hive Quadrant
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalCompleted(Goal_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: Nest Trigger 1 Hit
    if ((ScriptActionCtr_047 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 26);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: Nest Trigger 2 Hit
    if ((ScriptActionCtr_048 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 26);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: Ignite Burn Manually
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((qUserFlag(15) == true) && (qUserFlag(16) == false))) {
      aUserFlagSet(16, 1);
      aTurnOnSpew(Object_handles[63], -1, 1, 0.000000f, 0.000000f, 65536, 0, 0.700000f, 0.100000f, 0.500000f,
                  22.000000f, 120.000000f, 0, -1);
      aTurnOnSpew(Object_handles[63], -1, 1, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, 1.000000f,
                  16.000000f, 70.000000f, 0, -1);
      aTurnOffSpew(0);
      aShowHUDMessage(Message_strings[18]);
      aGoalCompleted(Goal_indexes[9], 1);
      aABThrusterIgnited(Object_handles[37]);
      aRoomSetFaceTexture(Room_indexes[3], 472, Texture_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Cocoon Ambush 1
    if ((ScriptActionCtr_028 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(0.500000f, 15);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Cocoon Ambush 2
    if ((ScriptActionCtr_030 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(2.000000f, 16);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Shark Ambush 1
    if ((ScriptActionCtr_058 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aPortalBreakGlass(0, Room_indexes[27]);
      aAlienOrganismHunt(Object_handles[69], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Alien Ambush 2
    if ((ScriptActionCtr_059 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aPortalBreakGlass(0, Room_indexes[28]);
      aAlienOrganismHunt(Object_handles[70], event_data->it_handle);
      aAlienOrganismHunt(Object_handles[71], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Boss Intro Trigger #1 Hit
    if ((ScriptActionCtr_056 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[24]);
      aABStartWaitEffect(Object_handles[37]);
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Left Boss Area Trigger Hit
    if ((ScriptActionCtr_064 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Boss Intro Trigger #2 Hit
    if ((ScriptActionCtr_055 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 28);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Boss Intro Trigger #3 Hit
    if ((ScriptActionCtr_054 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 28);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Boss Intro Trigger #4 Hit
    if ((ScriptActionCtr_052 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 28);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Boss Intro Trigger #5 Hit
    if ((ScriptActionCtr_057 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 28);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
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
NEXT_ID		72

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:NumAirlockChecks
1:MawDecayTime
2:MawWindSpeed
3:ThrusterRechargeLevel
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:AirlockPowerOn
1:AirlockActive
2:BadDoorRuined
3:Maw1Active
4:Maw2Active
5:Maw3Active
6:Maw4Active
7:Maw5Active
8:FuseSet
9:Maw1Dead
10:Maw2Dead
11:Maw3Dead
12:Maw4Dead
13:Maw5Dead
14:PowerRestored
15:BurnStarted
16:BurnIgnited
17:ThrusterSwitchActive
18:ForcefieldsDown
19:DoNestingBossCheck
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:IgniterFailedSpew
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:AirlockDecomCheck
1:OpenInnerAirlockDoor
2:CompleteAirlockDecompression
3:StopAirlockWind
4:AirlockCompCheck
5:OpenOuterAirlockDoor
6:CompleteAirlockCompression
7:NextSparkTime
8:BadDoorProcedure
9:MawRobotCheck
10:Maw1Dead
11:Maw2Dead
12:Maw3Dead
13:Maw4Dead
14:Maw5Dead
15:Cocoon1Ambush
16:Cocoon2Ambush
17:RechargeThrusterSequence
18:ResetThrusterSwitch
19:IgniterFailedSequence
20:PowerRestored
21:InitializeBossScenario
22:EndLevelSequence
23:EscapeSequence
24:EndLevelMovie
25:LevelShakes
26:NestTriggerHit
27:DoBossAtNestCheck
28:BossIntro
29:StartBoss
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
AirlockInnerDoor
AirlockOuterDoor
DoorWon'tOpenFar
$$DOOR_LIST_END

$$OBJECT_LIST_START
TeleporterA1
TeleporterA2
TeleporterB1
TeleporterC1
TeleporterC2
EscapeTrigger
Maw1
Maw2
Maw3
Maw4
Maw5
WallShuttle
DataArm1
DataArm2
BossMinion1
BossMinion2
Greenbot1
Greenbot2
SharkAmbush1
Greenbot3
Greenbot4
Greenbot5
Greenbot6
Greenbot7
Greenbot8
Greenbot9
Greenbot10
Greenbot11
Greenbot12
Greenbot13
Greenbot14
Greenbot15
Greenbot16
Greenbot17
Greenbot18
Greenbot19
BossDeathCamTarget
AlienBoss
AlienBossNest
AirlockDoorSwitch
AirlockOuterDoor
AirlockOuterCam1
AirlockOuterCam2
AirlockInnerDoor
AirlockInnerCam1
AirlockInnerCam2
AirlockSound
TeleporterA1Dest
TeleporterA1Cam2
TeleporterA2Cam2
TeleporterA2Dest
TeleporterC1Dest
TeleporterC2Dest
TeleporterA1Cam
TeleporterA2Cam
DoorWon'tOpenFar
BadDoorCam1
BadDoorCam2
CruiserFuse
FusePosition
FuseBeamB
FuseBeamA
ThrusterSwitch
ThrusterCam
Cocoon1Ambusher1
Ambush1HuntDest
Cocoon1Ambusher2
Cocoon1Ambusher3
Cocoon2Ambusher1
AlienAmbush1
AlienAmbush2A
AlienAmbush2B
AlienBossPosition
RoomASteamer1
RoomASteamer2
RoomBSteamer
RoomCSteamer
RoomDSteamer
RoomESteamer
$$OBJECT_LIST_END

$$ROOM_LIST_START
AirlockRoom
AirlockIDRoom
AirlockODRoom
BossRoomA
BossRoomB
BossRoomC
BossRoomD
BossRoomE
ThrusterSwitchRoom
BossLeftHideRoom
BossRightHideRoom
TeleporterA2
TeleporterA1
Maw1EntryRoom
Maw1Room
Maw2EntryRoom
Maw2Room
Maw3EntryRoom
Maw3Room
Maw4EntryRoom
Maw4Room
Maw5EntryRoom
Maw5Room
ForcefieldRoom
CocoonAmb1Cell1
Coc1AmbCell2
CocAmb2Cell1
SharkAmbush1
AlienAmbush2
CaveinRoom
CaveinRoom2
$$ROOM_LIST_END

$$TRIGGER_LIST_START
AirlockTrigger
LeftOuterShell
EnteredHiveArea1
EnteredHive2
EnteredHive3
LeftHiveArea1
LeftHive2
LeftHive3
ForcefieldRoomTrigg
LowerQuadTrigger
NestTrigger1
NestTrigger2
ThrusterTrigger
Ambush1
Ambush2
SharkAmbush1
AlienAmbush2
BossIntroTrigger
LeftBossArea
BossIntroTrigger2
BossIntroTrigger3
BossIntroTrigger4
BossIntroTrigger5
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch41
EnvSteamEmitG
DoorIsLocked
EnvSlowCreakD
EnvSlowCreakE
Merc4Vortex
Wall fade ???
AmbMatCenProduce
EnvElectricE
Powerup pickup
EnvElectricA
AmbSwitch31
Merc4Thruster
Merc4BossDeath
Merc4Rumble
AmbSwitch11
$$SOUND_LIST_END

$$TEXTURE_LIST_START
CC_JetEngine
Alien_Forcefield02
FunkyEffect3
CC_JetEngineLit
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCamPath
IntroPlayerPath
BossDeathCam
BossDeathPath
Escape2CamPath
EscapePath2
BossIntroCam2
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Engage Airlock Power
Enter Outer Shell through Airlock
Teleport into Planetoid's Core
Disable Alien Forcefield Generators
Enter Sealed Quadrant of Alien Hive
Activate Main Thruster
Acquire Spare Fuse
Restore Power to Derelict Ship
Force Alien Queen to Nest
Manually Ignite Thruster Burn
Destroy Alien Planetoid
Escape
Investigate and Destroy Alien Planetoid
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Level Start - Init Flags and Variables
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:13:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:16:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:19:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:10.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:8.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Level Start - Misc
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.985000:X
                        10:6:0.000000:Y
                        10:6:-0.174000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.985000:X
                        10:6:0.000000:Y
                        10:6:-0.174000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.985000:X
                        10:6:0.000000:Y
                        10:6:-0.174000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.400000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:21:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:20000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:20000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:20000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:20000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:20000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:20000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:27:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:472:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aEnableVirusInfection
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Level Start - Into Movie
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:IntroText:Text
                        10:1:0:36:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:12.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Initialize Boss Scenario
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:21:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aABSetScenarioIDs
                        $$CHILD_BLOCK_START
                        10:1:0:37:Alien Boss
                        10:1:0:38:Nest
                        10:2:9:Left Hide Room
                        10:2:10:Right Hide Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Airlock Power Switch Hit
        $$CHILD_BLOCK_START
        01:1:39
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:AirlockPowerOn:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Airlock Outer Door Hit
        $$CHILD_BLOCK_START
        01:1:40
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerOrPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aDoorActivate
                                                $$CHILD_BLOCK_START
                                                10:0:2:-1:Door
                                                $$CHILD_BLOCK_END
                                        08:aTurnOnSpew
                                                $$CHILD_BLOCK_START
                                                10:1:0:41:Object
                                                10:4:-1:GunNum
                                                10:10:0:7:SpewType
                                                10:6:0.000000:Mass
                                                10:6:0.000000:Drag
                                                10:15:65536:PhysicsFlags
                                                10:5:0:IsRealObject
                                                10:6:1.500000:BlobLifetime
                                                10:6:0.200000:BlobInterval
                                                10:6:3.000000:SpewLife
                                                10:6:2.000000:BlobSize
                                                10:6:8.000000:BlobSpeed
                                                10:5:1:Randomize
                                                10:10:0:-1:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aTurnOnSpew
                                                $$CHILD_BLOCK_START
                                                10:1:0:42:Object
                                                10:4:-1:GunNum
                                                10:10:0:7:SpewType
                                                10:6:0.000000:Mass
                                                10:6:0.000000:Drag
                                                10:15:65536:PhysicsFlags
                                                10:5:0:IsRealObject
                                                10:6:1.500000:BlobLifetime
                                                10:6:0.200000:BlobInterval
                                                10:6:3.000000:SpewLife
                                                10:6:2.000000:BlobSize
                                                10:6:8.000000:BlobSpeed
                                                10:5:1:Randomize
                                                10:10:0:-1:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:41:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:42:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        03:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qDoorGetPos:Percentage
                                                                $$CHILD_BLOCK_START
                                                                10:0:0:0:Door
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:9:0.000000:Percentage
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:AirlockDecompStarted:Message
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:UserVar
                                                        10:6:0.000000:value
                                                        $$CHILD_BLOCK_END
                                                08:aSetLevelTimer
                                                        $$CHILD_BLOCK_START
                                                        10:6:2.000000:Time
                                                        10:10:0:0:TimerID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aSetLevelTimer
                                                        $$CHILD_BLOCK_START
                                                        10:6:2.000000:Time
                                                        10:10:0:5:TimerID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:AirlockActive:Message
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:2:Sound
                                                10:1:2:-1:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AirlockPowerNotOn:Message
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aGoalEnableDisable
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:18:0:0:LevelGoal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Airlock Inner Door Hit
        $$CHILD_BLOCK_START
        01:1:43
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerOrPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aDoorActivate
                                                $$CHILD_BLOCK_START
                                                10:0:2:-1:Door
                                                $$CHILD_BLOCK_END
                                        08:aTurnOnSpew
                                                $$CHILD_BLOCK_START
                                                10:1:0:44:Object
                                                10:4:-1:GunNum
                                                10:10:0:7:SpewType
                                                10:6:0.000000:Mass
                                                10:6:0.000000:Drag
                                                10:15:65536:PhysicsFlags
                                                10:5:0:IsRealObject
                                                10:6:1.500000:BlobLifetime
                                                10:6:0.200000:BlobInterval
                                                10:6:3.000000:SpewLife
                                                10:6:2.000000:BlobSize
                                                10:6:8.000000:BlobSpeed
                                                10:5:1:Randomize
                                                10:10:0:-1:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aTurnOnSpew
                                                $$CHILD_BLOCK_START
                                                10:1:0:45:Object
                                                10:4:-1:GunNum
                                                10:10:0:7:SpewType
                                                10:6:0.000000:Mass
                                                10:6:0.000000:Drag
                                                10:15:65536:PhysicsFlags
                                                10:5:0:IsRealObject
                                                10:6:1.500000:BlobLifetime
                                                10:6:0.200000:BlobInterval
                                                10:6:3.000000:SpewLife
                                                10:6:2.000000:BlobSize
                                                10:6:8.000000:BlobSpeed
                                                10:5:1:Randomize
                                                10:10:0:-1:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:44:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:45:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        03:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qDoorGetPos:Percentage
                                                                $$CHILD_BLOCK_START
                                                                10:0:0:1:Door
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:9:0.000000:Percentage
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:AirlockCompStarted:Message
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:UserVar
                                                        10:6:0.000000:value
                                                        $$CHILD_BLOCK_END
                                                08:aSetLevelTimer
                                                        $$CHILD_BLOCK_START
                                                        10:6:2.000000:Time
                                                        10:10:0:4:TimerID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aSetLevelTimer
                                                        $$CHILD_BLOCK_START
                                                        10:6:2.000000:Time
                                                        10:10:0:1:TimerID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:AirlockActive:Message
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:2:Sound
                                                10:1:2:-1:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AirlockPowerNotOn:Message
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Do Airlock Decompression Check
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qDoorGetPos:Percentage
                                                        $$CHILD_BLOCK_START
                                                        10:0:0:1:Door
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:9:0.000000:Percentage
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qDoorGetPos:Percentage
                                                        $$CHILD_BLOCK_START
                                                        10:0:0:0:Door
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:9:0.000000:Percentage
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:12.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:44:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:3.000000:SpewLife
                                10:6:2.000000:BlobSize
                                10:6:8.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:45:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:3.000000:SpewLife
                                10:6:2.000000:BlobSize
                                10:6:8.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:44:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:45:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:12.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AirlockMalfunction:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:3:Sound
                                        10:1:0:44:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Do Airlock Compression Check
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qDoorGetPos:Percentage
                                                        $$CHILD_BLOCK_START
                                                        10:0:0:1:Door
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:9:0.000000:Percentage
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qDoorGetPos:Percentage
                                                        $$CHILD_BLOCK_START
                                                        10:0:0:0:Door
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:9:0.000000:Percentage
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:12.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:41:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:3.000000:SpewLife
                                10:6:2.000000:BlobSize
                                10:6:8.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:42:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:3.000000:SpewLife
                                10:6:2.000000:BlobSize
                                10:6:8.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:41:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:42:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:12.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AirlockMalfunction:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:5:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:0:41:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Open Inner Airlock Door
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qDoorGetPos:Percentage
                                        $$CHILD_BLOCK_START
                                        10:0:0:1:Door
                                        $$CHILD_BLOCK_END
                                07:1:1
                                10:9:0.000000:Percentage
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:46:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:-0.985000:X
                                10:6:0.000000:Y
                                10:6:0.174000:Z
                                10:6:10.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:-0.985000:X
                                10:6:0.000000:Y
                                10:6:0.174000:Z
                                10:6:10.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:-0.985000:X
                                10:6:0.000000:Y
                                10:6:0.174000:Z
                                10:6:10.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Open Outer Airlock Door
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qDoorGetPos:Percentage
                                        $$CHILD_BLOCK_START
                                        10:0:0:0:Door
                                        $$CHILD_BLOCK_END
                                07:1:1
                                10:9:0.000000:Percentage
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.985000:X
                                10:6:0.000000:Y
                                10:6:-0.174000:Z
                                10:6:10.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:0.985000:X
                                10:6:0.000000:Y
                                10:6:-0.174000:Z
                                10:6:10.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.985000:X
                                10:6:0.000000:Y
                                10:6:-0.174000:Z
                                10:6:10.000000:Speed
                                10:6:1.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Complete Airlock Decompression
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Stop Airlock Wind
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.985000:X
                        10:6:0.000000:Y
                        10:6:-0.174000:Z
                        10:6:0.000000:Speed
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.985000:X
                        10:6:0.000000:Y
                        10:6:-0.174000:Z
                        10:6:0.000000:Speed
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.985000:X
                        10:6:0.000000:Y
                        10:6:-0.174000:Z
                        10:6:0.000000:Speed
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Player passed through Airlock
        $$CHILD_BLOCK_START
        01:0:0
        02:1
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Player Left Outer Shell
        $$CHILD_BLOCK_START
        01:0:1
        02:1
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Teleporter A1 Hit
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:60:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aClearTeleporterArea
                        $$CHILD_BLOCK_START
                        10:1:0:47:Destination
                        10:1:1:-1:Teleportee
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:5:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:6:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:7:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:8:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:9:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:10:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:11:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:5:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:6:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:7:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:8:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:9:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:10:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:11:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Teleporter A2 Hit
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aClearTeleporterArea
                        $$CHILD_BLOCK_START
                        10:1:0:50:Destination
                        10:1:1:-1:Teleportee
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:5:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:6:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:7:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:8:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:9:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:10:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:11:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:5:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:6:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:7:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:8:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:9:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:10:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:11:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.200000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:8.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Teleporter C1 Hit
        $$CHILD_BLOCK_START
        01:1:3
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aClearTeleporterArea
                        $$CHILD_BLOCK_START
                        10:1:0:51:Destination
                        10:1:1:-1:Teleportee
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Teleporter C2 Hit
        $$CHILD_BLOCK_START
        01:1:4
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aClearTeleporterArea
                        $$CHILD_BLOCK_START
                        10:1:0:52:Destination
                        10:1:1:-1:Teleportee
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Make Teleporter A Spark
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Number
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:25.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Number
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:25.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:0.250000:LowerLimit
                                10:6:1.500000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Bad Door Hit
        $$CHILD_BLOCK_START
        01:1:55
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Number
                                10:1:0:56:Object
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:0.600000:Position
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.500000:Time
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Make Bad Door Stutter
        $$CHILD_BLOCK_START
        01:2:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:17:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:35.000000:Number
                                10:1:0:57:Object
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:0.550000:Position
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.500000:Time
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:17:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Number
                                10:1:0:56:Object
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:0.650000:Position
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:8:Sound
                                10:1:0:55:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:BadDoorBumped:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Entered Hive Area 1 Trigger Hit
        $$CHILD_BLOCK_START
        01:0:2
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Entered Hive Area 2 Trigger Hit
        $$CHILD_BLOCK_START
        01:0:3
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Entered Hive Area 3 Trigger Hit
        $$CHILD_BLOCK_START
        01:0:4
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Left Hive Area 1 Trigger Hit
        $$CHILD_BLOCK_START
        01:0:5
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Left Hive Area 2 Trigger Hit
        $$CHILD_BLOCK_START
        01:0:6
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Left Hive Area 3 Trigger Hit
        $$CHILD_BLOCK_START
        01:0:7
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Check if any Maws have been broken
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:18:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qPortalIsOn:Bool
                                                $$CHILD_BLOCK_START
                                                10:4:1:PortalNum
                                                10:2:13:Room
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:6:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:13:Room
                                10:6:0.469000:X
                                10:6:0.000000:Y
                                10:6:0.883000:Z
                                06:qUserVarValue:Speed
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:13:Room
                                10:6:0.469000:X
                                10:6:0.000000:Y
                                10:6:0.883000:Z
                                10:6:0.500000:Speed
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:14:Room
                                10:6:0.000000:Red
                                10:6:0.000000:Green
                                10:6:0.000000:Blue
                                10:6:40.000000:Depth
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:10:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qPortalIsOn:Bool
                                                $$CHILD_BLOCK_START
                                                10:4:0:PortalNum
                                                10:2:15:Room
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:7:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:15:Room
                                10:6:0.707000:X
                                10:6:0.000000:Y
                                10:6:0.707000:Z
                                06:qUserVarValue:Speed
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:15:Room
                                10:6:0.707000:X
                                10:6:0.000000:Y
                                10:6:0.707000:Z
                                10:6:0.500000:Speed
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:16:Room
                                10:6:0.000000:Red
                                10:6:0.000000:Green
                                10:6:0.000000:Blue
                                10:6:40.000000:Depth
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qPortalIsOn:Bool
                                                $$CHILD_BLOCK_START
                                                10:4:0:PortalNum
                                                10:2:17:Room
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:8:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:17:Room
                                10:6:-0.866000:X
                                10:6:0.000000:Y
                                10:6:0.500000:Z
                                06:qUserVarValue:Speed
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:17:Room
                                10:6:-0.870000:X
                                10:6:0.000000:Y
                                10:6:0.500000:Z
                                10:6:0.500000:Speed
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:18:Room
                                10:6:0.000000:Red
                                10:6:0.000000:Green
                                10:6:0.000000:Blue
                                10:6:40.000000:Depth
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:12:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qPortalIsOn:Bool
                                                $$CHILD_BLOCK_START
                                                10:4:0:PortalNum
                                                10:2:19:Room
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:9:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:-0.743000:X
                                10:6:0.000000:Y
                                10:6:0.669000:Z
                                06:qUserVarValue:Speed
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:-0.740000:X
                                10:6:0.000000:Y
                                10:6:0.670000:Z
                                10:6:0.500000:Speed
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:20:Room
                                10:6:0.000000:Red
                                10:6:0.000000:Green
                                10:6:0.000000:Blue
                                10:6:40.000000:Depth
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:13:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qPortalIsOn:Bool
                                                $$CHILD_BLOCK_START
                                                10:4:0:PortalNum
                                                10:2:21:Room
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:10:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:21:Room
                                10:6:0.574000:X
                                10:6:0.000000:Y
                                10:6:-0.819000:Z
                                06:qUserVarValue:Speed
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:21:Room
                                10:6:0.574000:X
                                10:6:0.000000:Y
                                10:6:-0.819000:Z
                                10:6:0.500000:Speed
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:22:Room
                                10:6:0.000000:Red
                                10:6:0.000000:Green
                                10:6:0.000000:Blue
                                10:6:40.000000:Depth
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Time
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:13:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:23:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:23:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:3:PortalNum
                                10:2:23:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:4:PortalNum
                                10:2:23:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:5:PortalNum
                                10:2:23:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:18:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:3:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Do Maw Robot/Player Check
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aKillBotsNearObj
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aKillBotsNearObj
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aKillBotsNearObj
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aKillBotsNearObj
                                $$CHILD_BLOCK_START
                                10:1:0:9:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:13:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aKillBotsNearObj
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.250000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Maw 1 is Dead
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:4:1:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:4:273:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Maw 2 is Dead
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:4:2:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:4:271:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Maw 3 is Dead
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:4:3:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:4:269:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Maw 4 is Dead
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:4:4:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:4:270:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Maw 5 is Dead
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:13:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:4:5:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:4:268:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Player Flew into Forcefield Room
        $$CHILD_BLOCK_START
        01:0:8
        02:1
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:3:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:3:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:3:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FFMessage:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Player Entered Lower Hive Quadrant
        $$CHILD_BLOCK_START
        01:0:9
        02:1
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Nest Trigger 1 Hit
        $$CHILD_BLOCK_START
        01:0:10
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:26:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Nest Trigger 2 Hit
        $$CHILD_BLOCK_START
        01:0:11
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:26:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Do Nest Trigger
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:26:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:UseThruster:Message
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:5:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Player Picks Up Cruiser Fuse
        $$CHILD_BLOCK_START
        01:1:58
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:CruiserFuseAcquired:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Used Cruiser Fuse
        $$CHILD_BLOCK_START
        01:1:58
        02:25
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjGetDistance:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object1
                                        10:1:0:59:Object2
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:40.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:59:Object
                                $$CHILD_BLOCK_END
                        08:aMoveObjectToPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Ghost/Unghost
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
                                10:1:0:59:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CruiserFusePlaced:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:60:Object1
                                10:1:0:61:Object2
                                10:6:10000.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:0.600000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:20:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aAddObjectToInventory
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:1:1:-1:PlayerObject
                                10:5:0:Spewable
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:CruiserFuseNoUse:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Power Restored
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:20:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:5:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:59:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Do Boss At Nest Check
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:27:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:19:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qIsAlienBossHealing:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:37:Alien Boss
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qGoalCompleted:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:8:LevelGoal
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:8:LevelGoal
                                                10:10:0:1:Completed
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qGoalCompleted:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:8:LevelGoal
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:8:LevelGoal
                                                10:10:0:0:Completed
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:QueenLeft:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:27:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Thruster Switch Hit
        $$CHILD_BLOCK_START
        01:1:62
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerOrPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:17:UserFlag
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:2:-1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:2:-1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:2.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qUserFlag:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:16:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aMiscShakeArea
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:63:Object
                                                        10:6:40.000000:Amount
                                                        10:6:5000.000000:Dist
                                                        $$CHILD_BLOCK_END
                                                08:aObjPlayAnim
                                                        $$CHILD_BLOCK_START
                                                        10:1:2:-1:Object
                                                        10:4:0:StartFrame
                                                        10:4:1:EndFrame
                                                        10:6:2.000000:CycleTime
                                                        10:5:0:Looping
                                                        $$CHILD_BLOCK_END
                                                08:aSoundPlayObject
                                                        $$CHILD_BLOCK_START
                                                        10:12:11:Sound
                                                        10:1:2:-1:Object
                                                        10:9:1.000000:Volume
                                                        $$CHILD_BLOCK_END
                                                08:aGoalCompleted
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:5:LevelGoal
                                                        10:10:0:1:Completed
                                                        $$CHILD_BLOCK_END
                                                03:1
                                                        $$CHILD_BLOCK_START
                                                        05:1
                                                                $$CHILD_BLOCK_START
                                                                06:qAlienBossHealing:Bool
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:0:37:Alien Boss
                                                                        $$CHILD_BLOCK_END
                                                                07:0:6
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aUserFlagSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:19:UserFlag
                                                                10:5:0:True/False
                                                                $$CHILD_BLOCK_END
                                                        03:1
                                                                $$CHILD_BLOCK_START
                                                                05:1
                                                                        $$CHILD_BLOCK_START
                                                                        06:qGoalCompleted:Bool
                                                                                $$CHILD_BLOCK_START
                                                                                10:18:0:8:LevelGoal
                                                                                $$CHILD_BLOCK_END
                                                                        07:0:7
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aGoalCompleted
                                                                        $$CHILD_BLOCK_START
                                                                        10:18:0:8:LevelGoal
                                                                        10:10:0:1:Completed
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        08:aUserFlagSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:17:UserFlag
                                                                10:5:1:True/False
                                                                $$CHILD_BLOCK_END
                                                        08:aSetLevelTimer
                                                                $$CHILD_BLOCK_START
                                                                10:6:2.000000:Time
                                                                10:10:0:22:TimerID
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:1
                                                        $$CHILD_BLOCK_START
                                                        08:aObjPlayAnim
                                                                $$CHILD_BLOCK_START
                                                                10:1:2:-1:Object
                                                                10:4:0:StartFrame
                                                                10:4:1:EndFrame
                                                                10:6:2.000000:CycleTime
                                                                10:5:0:Looping
                                                                $$CHILD_BLOCK_END
                                                        08:aSoundPlayObject
                                                                $$CHILD_BLOCK_START
                                                                10:12:11:Sound
                                                                10:1:2:-1:Object
                                                                10:9:1.000000:Volume
                                                                $$CHILD_BLOCK_END
                                                        08:aTurnOnSpew
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:63:Object
                                                                10:4:-1:GunNum
                                                                10:10:0:1:SpewType
                                                                10:6:0.000000:Mass
                                                                10:6:0.000000:Drag
                                                                10:15:65536:PhysicsFlags
                                                                10:5:0:IsRealObject
                                                                10:6:1.200000:BlobLifetime
                                                                10:6:0.100000:BlobInterval
                                                                10:6:3.000000:SpewLife
                                                                10:6:23.000000:BlobSize
                                                                10:6:145.000000:BlobSpeed
                                                                10:5:0:Randomize
                                                                10:10:0:-1:SpewHandle
                                                                $$CHILD_BLOCK_END
                                                        08:aSoundPlayObject
                                                                $$CHILD_BLOCK_START
                                                                10:12:12:Sound
                                                                10:1:0:63:Object
                                                                10:9:1.000000:Volume
                                                                $$CHILD_BLOCK_END
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:UserVar
                                                                10:6:0.000000:value
                                                                $$CHILD_BLOCK_END
                                                        08:aUserFlagSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:17:UserFlag
                                                                10:5:1:True/False
                                                                $$CHILD_BLOCK_END
                                                        08:aSetLevelTimer
                                                                $$CHILD_BLOCK_START
                                                                10:6:5.000000:Time
                                                                10:10:0:17:TimerID
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:NoBurnIgnited:Message
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aMiscShakeArea
                                                $$CHILD_BLOCK_START
                                                10:1:0:63:Object
                                                10:6:20.000000:Amount
                                                10:6:5000.000000:Dist
                                                $$CHILD_BLOCK_END
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:11:Sound
                                                10:1:2:-1:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:15:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aABThrusterMisfired
                                                $$CHILD_BLOCK_START
                                                10:1:0:37:Alien Boss
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:17:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aTurnOnSpew
                                                $$CHILD_BLOCK_START
                                                10:1:0:63:Object
                                                10:4:-1:GunNum
                                                10:10:0:8:SpewType
                                                10:6:0.000000:Mass
                                                10:6:0.000000:Drag
                                                10:15:65536:PhysicsFlags
                                                10:5:0:IsRealObject
                                                10:6:1.200000:BlobLifetime
                                                10:6:0.100000:BlobInterval
                                                10:6:3.000000:SpewLife
                                                10:6:16.000000:BlobSize
                                                10:6:130.000000:BlobSpeed
                                                10:5:0:Randomize
                                                10:10:0:-1:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aRoomChangeFog
                                                $$CHILD_BLOCK_START
                                                10:2:3:Room
                                                10:6:0.500000:Red
                                                10:6:0.500000:Green
                                                10:6:0.500000:Blue
                                                10:6:400.000000:Depth
                                                10:6:2.500000:Time
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:3.000000:Time
                                                10:10:0:19:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:NoPowerAvail:Message
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:6:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:7:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Igniter Failed Sequence
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:19:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:33:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:63:Object
                                10:4:-1:GunNum
                                10:10:0:8:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.300000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:12.000000:BlobSize
                                10:6:60.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:0:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:IgniterFailed1:Message
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.500000:Red
                                10:6:0.500000:Green
                                10:6:0.500000:Blue
                                10:6:5000.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:19:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:33:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:IgniterFailed2:Message
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:9:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:18:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Ignite Burn Manually
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:15:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:16:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:16:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:-1:GunNum
                        10:10:0:1:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.700000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.500000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:120.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:-1:GunNum
                        10:10:0:1:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:1.000000:SpewLife
                        10:6:16.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BurnIgnited:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:9:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aABThrusterIgnited
                        $$CHILD_BLOCK_START
                        10:1:0:37:Alien Boss
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:472:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Recharge Thruster Sequence
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:17:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ThrusterBurnFailed:Message
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:17:TimerID
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:8:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:19:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RechargeThruster1:Message
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:10.000000:Time
                                10:10:0:17:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RechargeThruster2:Message
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:18:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Reset the Thruster Switch
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:18:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:11:Sound
                        10:1:0:62:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:0:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Cocoon Ambush 1
        $$CHILD_BLOCK_START
        01:0:13
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Do Cocoon 1's Ambushes
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:29:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:24:Room
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:15:TimerID
                                $$CHILD_BLOCK_END
                        08:aAlienOrganismHunt
                                $$CHILD_BLOCK_START
                                10:1:0:64:Alien Organism
                                10:1:0:65:Destination Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:29:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:25:Room
                                $$CHILD_BLOCK_END
                        08:aAlienOrganismHunt
                                $$CHILD_BLOCK_START
                                10:1:0:66:Alien Organism
                                10:1:0:65:Destination Object
                                $$CHILD_BLOCK_END
                        08:aAlienOrganismHunt
                                $$CHILD_BLOCK_START
                                10:1:0:67:Alien Organism
                                10:1:0:65:Destination Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Cocoon Ambush 2
        $$CHILD_BLOCK_START
        01:0:14
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Do Cocoon 2's Ambushes
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:31:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:26:Room
                                $$CHILD_BLOCK_END
                        08:aAlienOrganismHunt
                                $$CHILD_BLOCK_START
                                10:1:0:68:Alien Organism
                                10:1:0:65:Destination Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Shark Ambush 1
        $$CHILD_BLOCK_START
        01:0:15
        02:1
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
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:27:Room
                        $$CHILD_BLOCK_END
                08:aAlienOrganismHunt
                        $$CHILD_BLOCK_START
                        10:1:0:69:Alien Organism
                        10:1:1:-1:Destination Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Alien Ambush 2
        $$CHILD_BLOCK_START
        01:0:16
        02:1
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
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:28:Room
                        $$CHILD_BLOCK_END
                08:aAlienOrganismHunt
                        $$CHILD_BLOCK_START
                        10:1:0:70:Alien Organism
                        10:1:1:-1:Destination Object
                        $$CHILD_BLOCK_END
                08:aAlienOrganismHunt
                        $$CHILD_BLOCK_START
                        10:1:0:71:Alien Organism
                        10:1:1:-1:Destination Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Boss Death Sequence
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:22:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:2:CameraPath
                                10:8:Empty:Text
                                10:1:0:36:Target
                                10:6:15.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:72:Object
                                $$CHILD_BLOCK_END
                        08:aMoveObjectToPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                $$CHILD_BLOCK_END
                        08:aObjPlayImmAnim
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:4:1:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:4:10:StartFrame
                                10:4:25:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:6:20.000000:Amount
                                10:6:200.000000:Dist
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:63:Object
                                10:4:-1:GunNum
                                10:10:0:1:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:5.000000:SpewLife
                                10:6:23.000000:BlobSize
                                10:6:170.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:12:Sound
                                10:1:0:63:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:4:25:StartFrame
                                10:4:36:EndFrame
                                10:6:0.600000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aSetObjectOnFire
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:6:8.000000:Seconds
                                10:6:0.000000:Damage
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:6:40.000000:SparkRate
                                10:6:10.000000:Time
                                $$CHILD_BLOCK_END
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:30.000000:Number
                                10:1:0:37:Object
                                $$CHILD_BLOCK_END
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:6:6.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:16:3:Path
                                10:15:131076:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:13:Sound
                                10:1:0:37:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Number
                                10:1:0:37:Object
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:4:25:StartFrame
                                10:4:36:EndFrame
                                10:6:0.500000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:13:Sound
                                10:1:0:37:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:4:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Number
                                10:1:0:37:Object
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.500000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:5:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:50.000000:Number
                                10:1:0:37:Object
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:4:25:StartFrame
                                10:4:36:EndFrame
                                10:6:0.400000:CycleTime
                                10:5:1:Looping
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.500000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:13:Sound
                                10:1:0:37:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:6:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:6:40.000000:Amount
                                10:6:200.000000:Dist
                                $$CHILD_BLOCK_END
                        08:aObjKill
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object
                                10:10:0:0:DeathDelayType
                                10:10:0:2:DeathExplosionSize
                                10:15:131296:DeathFlags
                                10:6:0.000000:MinDelay
                                10:6:0.000000:MaxDelay
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:11:Object
                                10:6:50.000000:SparkRate
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.200000:Time
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:38:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:7:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:11:Object
                                $$CHILD_BLOCK_END
                        08:aObjKill
                                $$CHILD_BLOCK_START
                                10:1:0:11:Object
                                10:10:0:0:DeathDelayType
                                10:10:0:2:DeathExplosionSize
                                10:15:131296:DeathFlags
                                10:6:0.000000:MinDelay
                                10:6:0.000000:MaxDelay
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:3:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:4:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:5:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:6:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:7:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:8:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Alien Boss Died
        $$CHILD_BLOCK_START
        01:1:37
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:29:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:100.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:300.000000:Depth
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:29:Room
                        10:5:0:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:1000.000000:Depth
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:1000.000000:Depth
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:1000.000000:Depth
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:1000.000000:Depth
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:1000.000000:Depth
                        10:6:8.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.400000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.400000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:6.000000:BlobLifetime
                        10:6:0.400000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:5.000000:BlobLifetime
                        10:6:0.400000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:5.000000:BlobLifetime
                        10:6:0.400000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:6.000000:BlobLifetime
                        10:6:0.400000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:10.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:6.000000:Time
                        10:10:0:23:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:6.000000:Time
                        10:10:0:25:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Escape Sequence
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:23:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:39:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:1:PortalNum
                                10:2:8:Room
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:Red
                                10:6:1.000000:Green
                                10:6:0.000000:Blue
                                10:6:800.000000:Depth
                                10:6:5.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:4:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:23:TimerID
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:10:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:11:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:39:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:GetOuttaHere:Message
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Do Level Shakes
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:25:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:50.000000:LowerLimit
                                10:6:90.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:6:5000.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:14:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:2.000000:LowerLimit
                                10:6:4.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:25:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Escape Trigger Hit
        $$CHILD_BLOCK_START
        01:1:5
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:11:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:24:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:End Level Escape Movie
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:24:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:12:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:4:CameraPath
                        10:16:5:PlayerPath
                        10:6:3.500000:Time
                        10:8:Empty:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Boss Intro Trigger #1 Hit
        $$CHILD_BLOCK_START
        01:0:17
        02:1
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FuseRoom:Message
                        $$CHILD_BLOCK_END
                08:aABStartWaitEffect
                        $$CHILD_BLOCK_START
                        10:1:0:37:Alien Boss
                        $$CHILD_BLOCK_END
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Left Boss Area Trigger Hit
        $$CHILD_BLOCK_START
        01:0:18
        02:1
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Boss Intro Trigger #2 Hit
        $$CHILD_BLOCK_START
        01:0:19
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:28:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Boss Intro Trigger #3 Hit
        $$CHILD_BLOCK_START
        01:0:20
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:28:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Boss Intro Trigger #4 Hit
        $$CHILD_BLOCK_START
        01:0:21
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:28:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Boss Intro Trigger #5 Hit
        $$CHILD_BLOCK_START
        01:0:22
        02:1
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:28:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Boss Intro Cinematic
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:28:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:8:BossIntro:Text
                        10:1:0:37:Target
                        10:6:13.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:9.000000:Time
                        10:10:0:29:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Start Boss Wandering
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:29:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aABItsShowtime
                        $$CHILD_BLOCK_START
                        10:1:0:37:Alien Boss
                        10:6:4.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Data Arm #1 Bumped
        $$CHILD_BLOCK_START
        01:1:12
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:15:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:DA1Game:GameMessage
                        10:8:DA1Hud:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Data Arm #2 Bumped
        $$CHILD_BLOCK_START
        01:1:13
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:10:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:15:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:DA2Game:GameMessage
                        10:8:DA2Hud:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
