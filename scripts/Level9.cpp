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
// Filename:	level9.cpp
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

#define ID_CUSTOM_OBJECT_081B 0x001
#define ID_CUSTOM_OBJECT_18D5 0x002
#define ID_CUSTOM_OBJECT_18D6 0x003
#define ID_CUSTOM_OBJECT_1030 0x004
#define ID_CUSTOM_OBJECT_1038 0x005
#define ID_CUSTOM_OBJECT_0869 0x006
#define ID_CUSTOM_OBJECT_086A 0x007
#define ID_CUSTOM_OBJECT_106E 0x008
#define ID_CUSTOM_OBJECT_106F 0x009
#define ID_CUSTOM_OBJECT_106D 0x00a
#define ID_CUSTOM_OBJECT_106C 0x00b
#define ID_CUSTOM_OBJECT_100F 0x00c
#define ID_CUSTOM_OBJECT_0871 0x00d
#define ID_CUSTOM_OBJECT_0811 0x00e
#define ID_CUSTOM_OBJECT_0810 0x00f
#define ID_CUSTOM_OBJECT_080E 0x010
#define ID_CUSTOM_OBJECT_0873 0x011
#define ID_CUSTOM_OBJECT_0872 0x012
#define ID_CUSTOM_OBJECT_2070 0x013
#define ID_CUSTOM_OBJECT_18AA 0x014
#define ID_CUSTOM_OBJECT_18C1 0x015
#define ID_CUSTOM_OBJECT_0948 0x016
#define ID_CUSTOM_OBJECT_0949 0x017
#define ID_CUSTOM_OBJECT_18AC 0x018
#define ID_CUSTOM_OBJECT_094E 0x019

#define ID_TRIGGER_0001 0x01a
#define ID_TRIGGER_0002 0x01b
#define ID_TRIGGER_0003 0x01c
#define ID_TRIGGER_0013 0x01d
#define ID_TRIGGER_0012 0x01e
#define ID_TRIGGER_0010 0x01f
#define ID_TRIGGER_0011 0x020
#define ID_TRIGGER_000F 0x021
#define ID_TRIGGER_000E 0x022
#define ID_TRIGGER_000D 0x023
#define ID_TRIGGER_000C 0x024
#define ID_TRIGGER_000B 0x025
#define ID_TRIGGER_000A 0x026
#define ID_TRIGGER_0009 0x027
#define ID_TRIGGER_0008 0x028
#define ID_TRIGGER_0007 0x029
#define ID_TRIGGER_0006 0x02a
#define ID_TRIGGER_0005 0x02b
#define ID_TRIGGER_0004 0x02c

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

class CustomObjectScript_081B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18D5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18D6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1030 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1038 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0869 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_086A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_106E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_106F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_106D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_106C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_100F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0871 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0811 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0810 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0873 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0872 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2070 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18AA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18C1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0948 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0949 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18AC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_094E : public BaseScript {
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

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
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

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_087 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_087 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Sunburn
2:Storage
3:Factory
4:Assembly
5:Control
$$END
*/

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

#define NUM_OBJECT_NAMES 28
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Recovery-2",
                                                           "Recovery-1",
                                                           "DisruptorPowerup1",
                                                           "Covert",
                                                           "Stabilizer-Store",
                                                           "Stabilizer-Assembl",
                                                           "Stabilizer-Factory",
                                                           "Stabilizer-Control",
                                                           "Component-1",
                                                           "Component-2",
                                                           "Component-3",
                                                           "FF-13",
                                                           "FF-14",
                                                           "FF-23",
                                                           "FF-24",
                                                           "DisruptorPowerup4",
                                                           "DisruptorPowerup3",
                                                           "DisruptorPowerup2",
                                                           "PowerStab-Control",
                                                           "PowerStab-Store",
                                                           "PowerStab-Assembly",
                                                           "PowerStab-Factory",
                                                           "Radar-2",
                                                           "Radar-1",
                                                           "Ant-3",
                                                           "Ant-2",
                                                           "Ant-1",
                                                           "Transmitter"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 2
static const char *const Room_names[NUM_ROOM_NAMES] = {"Forcefield-1", "Forcefield-2"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 19
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "Exit-Factory", "Entrance-Factory", "Entrance-Storage", "MStorage-3",  "MStorage-2",  "MStorage-1",  "MFactory-4",
    "MFactory-3",   "MFactory-2",       "MFactory-1",       "MAssembly-4", "MAssembly-3", "MAssembly-2", "MAssembly-1",
    "MControl-5",   "MControl-4",       "MControl-3",       "MControl-2",  "MControl-1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 6
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "AmbSwitch11", "PupC1", "AmbSirenIntense", "AmbSwitch31", "Earthshaker missile firing", "HudMessage"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 22
static const char *const Path_names[NUM_PATH_NAMES] = {
    "IntroCam",   "IntroShip",       "Covert-1",         "Covert-2",        "Covert-2-Out",     "Covert-3",
    "Covert-3-2", "Covert-3-3",      "Covert-3-Out",     "Covert-4",        "Covert-4-Out",     "Covert-5-Exit",
    "Recovery",   "ExitCam-Factory", "ExitShip-Factory", "ExitCam-Storage", "ExitShip-Storage", "StabControl",
    "StabStore",  "StabAssembly",    "StabFactory",      "EndLevel"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 7
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Escort the Covert Cargo Ship",        "Disrupt Control Seismic Stabilizer", "Disrupt Storage Seismic Stabilizer",
    "Disrupt Assembly Seismic Stabilizer", "Disrupt Factory Seismic Stabilizer", "Disrupt All Four Seismic Stabilizers",
    "Collect Seismic Disruptors"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 32
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "IntroCam",        "TransmitterHave", "CovEntering",       "CovPickup",        "CovDropOff",
    "CovFFHelp",       "CovStillStuckFF", "CovLeaving",        "EndLevel",         "CovThanksFF",
    "Disruptor",       "StabControlDone", "StabControlPower",  "StabStoreDone",    "StabAssemblyDone",
    "StabFactoryDone", "StabStorePower",  "StabAssemblyPower", "StabFactoryPower", "AllStabsDone",
    "CovLeaveMeAlone", "Testing2",        "Testing",           "CovRepaired",      "CovGettingPummeled",
    "CovShutDown",     "CovInClear",      "CovDamaged",        "CovDanger",        "DestroyedRadar",
    "DestroyedAnt",    "Transmitter"};
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
    strcpy(filename, "level9.msg");
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
  case ID_CUSTOM_OBJECT_081B:
    return new CustomObjectScript_081B;
    break;
  case ID_CUSTOM_OBJECT_18D5:
    return new CustomObjectScript_18D5;
    break;
  case ID_CUSTOM_OBJECT_18D6:
    return new CustomObjectScript_18D6;
    break;
  case ID_CUSTOM_OBJECT_1030:
    return new CustomObjectScript_1030;
    break;
  case ID_CUSTOM_OBJECT_1038:
    return new CustomObjectScript_1038;
    break;
  case ID_CUSTOM_OBJECT_0869:
    return new CustomObjectScript_0869;
    break;
  case ID_CUSTOM_OBJECT_086A:
    return new CustomObjectScript_086A;
    break;
  case ID_CUSTOM_OBJECT_106E:
    return new CustomObjectScript_106E;
    break;
  case ID_CUSTOM_OBJECT_106F:
    return new CustomObjectScript_106F;
    break;
  case ID_CUSTOM_OBJECT_106D:
    return new CustomObjectScript_106D;
    break;
  case ID_CUSTOM_OBJECT_106C:
    return new CustomObjectScript_106C;
    break;
  case ID_CUSTOM_OBJECT_100F:
    return new CustomObjectScript_100F;
    break;
  case ID_CUSTOM_OBJECT_0871:
    return new CustomObjectScript_0871;
    break;
  case ID_CUSTOM_OBJECT_0811:
    return new CustomObjectScript_0811;
    break;
  case ID_CUSTOM_OBJECT_0810:
    return new CustomObjectScript_0810;
    break;
  case ID_CUSTOM_OBJECT_080E:
    return new CustomObjectScript_080E;
    break;
  case ID_CUSTOM_OBJECT_0873:
    return new CustomObjectScript_0873;
    break;
  case ID_CUSTOM_OBJECT_0872:
    return new CustomObjectScript_0872;
    break;
  case ID_CUSTOM_OBJECT_2070:
    return new CustomObjectScript_2070;
    break;
  case ID_CUSTOM_OBJECT_18AA:
    return new CustomObjectScript_18AA;
    break;
  case ID_CUSTOM_OBJECT_18C1:
    return new CustomObjectScript_18C1;
    break;
  case ID_CUSTOM_OBJECT_0948:
    return new CustomObjectScript_0948;
    break;
  case ID_CUSTOM_OBJECT_0949:
    return new CustomObjectScript_0949;
    break;
  case ID_CUSTOM_OBJECT_18AC:
    return new CustomObjectScript_18AC;
    break;
  case ID_CUSTOM_OBJECT_094E:
    return new CustomObjectScript_094E;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
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
  case ID_CUSTOM_OBJECT_081B:
    delete ((CustomObjectScript_081B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18D5:
    delete ((CustomObjectScript_18D5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18D6:
    delete ((CustomObjectScript_18D6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1030:
    delete ((CustomObjectScript_1030 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1038:
    delete ((CustomObjectScript_1038 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0869:
    delete ((CustomObjectScript_0869 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_086A:
    delete ((CustomObjectScript_086A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_106E:
    delete ((CustomObjectScript_106E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_106F:
    delete ((CustomObjectScript_106F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_106D:
    delete ((CustomObjectScript_106D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_106C:
    delete ((CustomObjectScript_106C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_100F:
    delete ((CustomObjectScript_100F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0871:
    delete ((CustomObjectScript_0871 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0811:
    delete ((CustomObjectScript_0811 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0810:
    delete ((CustomObjectScript_0810 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080E:
    delete ((CustomObjectScript_080E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0873:
    delete ((CustomObjectScript_0873 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0872:
    delete ((CustomObjectScript_0872 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2070:
    delete ((CustomObjectScript_2070 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18AA:
    delete ((CustomObjectScript_18AA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18C1:
    delete ((CustomObjectScript_18C1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0948:
    delete ((CustomObjectScript_0948 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0949:
    delete ((CustomObjectScript_0949 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18AC:
    delete ((CustomObjectScript_18AC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_094E:
    delete ((CustomObjectScript_094E *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
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
  case ID_CUSTOM_OBJECT_081B:
  case ID_CUSTOM_OBJECT_18D5:
  case ID_CUSTOM_OBJECT_18D6:
  case ID_CUSTOM_OBJECT_1030:
  case ID_CUSTOM_OBJECT_1038:
  case ID_CUSTOM_OBJECT_0869:
  case ID_CUSTOM_OBJECT_086A:
  case ID_CUSTOM_OBJECT_106E:
  case ID_CUSTOM_OBJECT_106F:
  case ID_CUSTOM_OBJECT_106D:
  case ID_CUSTOM_OBJECT_106C:
  case ID_CUSTOM_OBJECT_100F:
  case ID_CUSTOM_OBJECT_0871:
  case ID_CUSTOM_OBJECT_0811:
  case ID_CUSTOM_OBJECT_0810:
  case ID_CUSTOM_OBJECT_080E:
  case ID_CUSTOM_OBJECT_0873:
  case ID_CUSTOM_OBJECT_0872:
  case ID_CUSTOM_OBJECT_2070:
  case ID_CUSTOM_OBJECT_18AA:
  case ID_CUSTOM_OBJECT_18C1:
  case ID_CUSTOM_OBJECT_0948:
  case ID_CUSTOM_OBJECT_0949:
  case ID_CUSTOM_OBJECT_18AC:
  case ID_CUSTOM_OBJECT_094E:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
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
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0004;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[25];
  static int cust_id_list[25] = {
      ID_CUSTOM_OBJECT_081B, ID_CUSTOM_OBJECT_18D5, ID_CUSTOM_OBJECT_18D6, ID_CUSTOM_OBJECT_1030,
      ID_CUSTOM_OBJECT_1038, ID_CUSTOM_OBJECT_0869, ID_CUSTOM_OBJECT_086A, ID_CUSTOM_OBJECT_106E,
      ID_CUSTOM_OBJECT_106F, ID_CUSTOM_OBJECT_106D, ID_CUSTOM_OBJECT_106C, ID_CUSTOM_OBJECT_100F,
      ID_CUSTOM_OBJECT_0871, ID_CUSTOM_OBJECT_0811, ID_CUSTOM_OBJECT_0810, ID_CUSTOM_OBJECT_080E,
      ID_CUSTOM_OBJECT_0873, ID_CUSTOM_OBJECT_0872, ID_CUSTOM_OBJECT_2070, ID_CUSTOM_OBJECT_18AA,
      ID_CUSTOM_OBJECT_18C1, ID_CUSTOM_OBJECT_0948, ID_CUSTOM_OBJECT_0949, ID_CUSTOM_OBJECT_18AC,
      ID_CUSTOM_OBJECT_094E};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[3];
  cust_handle_list[1] = Object_handles[0];
  cust_handle_list[2] = Object_handles[1];
  cust_handle_list[3] = Object_handles[11];
  cust_handle_list[4] = Object_handles[12];
  cust_handle_list[5] = Object_handles[13];
  cust_handle_list[6] = Object_handles[14];
  cust_handle_list[7] = Object_handles[15];
  cust_handle_list[8] = Object_handles[16];
  cust_handle_list[9] = Object_handles[17];
  cust_handle_list[10] = Object_handles[2];
  cust_handle_list[11] = Object_handles[7];
  cust_handle_list[12] = Object_handles[18];
  cust_handle_list[13] = Object_handles[4];
  cust_handle_list[14] = Object_handles[5];
  cust_handle_list[15] = Object_handles[6];
  cust_handle_list[16] = Object_handles[19];
  cust_handle_list[17] = Object_handles[20];
  cust_handle_list[18] = Object_handles[21];
  cust_handle_list[19] = Object_handles[22];
  cust_handle_list[20] = Object_handles[23];
  cust_handle_list[21] = Object_handles[24];
  cust_handle_list[22] = Object_handles[25];
  cust_handle_list[23] = Object_handles[26];
  cust_handle_list[24] = Object_handles[27];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 25;
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
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 036: Level Init
    if (1) {
      aAISetMaxSpeed(Object_handles[0], 40.000000f);
      aAISetMaxSpeed(Object_handles[1], 40.000000f);
      aObjMakeInvuln(Object_handles[1], 999999);
      aObjMakeInvuln(Object_handles[0], 999999);
      aCloakObject(Object_handles[0], 999999.000000f);
      aCloakObject(Object_handles[1], 999999.000000f);
      aUserFlagSet(4, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);
      aSetLevelTimer(5.000000f, 1);
      aUserVarSet(8, 0.000000f);
      aUserVarSet(9, 0.000000f);
      aUserVarSet(10, 0.000000f);
      aUserVarSet(11, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 005: Intro Cam 2
    if ((ScriptActionCtr_005 < 1) && (qUserFlag(2) == false)) {
      aSoundPlaySteaming("VoxL09StartLevel.osf", 1.000000f);
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[2], Path_indexes[1], 15.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 000: Stabilizers Init
    if (1) {
      aUserVarSet(8, 0.000000f);
      aUserVarSet(9, 0.000000f);
      aUserVarSet(10, 0.000000f);
      aUserVarSet(11, 0.000000f);
      aSetLevelTimer(10.000000f, 12);
      aSetObjectTimer(Object_handles[4], 2.000000f, 10);
      aSetObjectTimer(Object_handles[5], 2.000000f, 9);
      aSetObjectTimer(Object_handles[6], 2.000000f, 8);
      aSetObjectTimer(Object_handles[7], 2.000000f, 7);
      aObjSetLightingDist(Object_handles[6], 0.000000f);
      aObjSetLightingDist(Object_handles[7], 0.000000f);
      aObjSetLightingDist(Object_handles[5], 0.000000f);
      aObjSetLightingDist(Object_handles[4], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 013: Start-Music
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 006: Start Covert Path
    if (event_data->id == 1) {
      aAIGoalFollowPathSimple(Object_handles[3], Path_indexes[2], 4352, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 011: Check Stabilizers (for All Four)
    if (event_data->id == 11) {
      if ((qUserVarValue(8) == 2.000000f) && (qUserVarValue(9) == 2.000000f) && (qUserVarValue(10) == 2.000000f) &&
          (qUserVarValue(11) == 2.000000f)) {
        aUserVarAdd(40.000000f, 2);
        aGoalCompleted(Goal_indexes[5], 1);
        aUserFlagSet(3, 1);
        aShowHUDMessage(Message_strings[19]);
      }
      aUserVarAdd(135.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 060: Random Shaking on Disrupted
    if (event_data->id == 12) {
      if (qUserVarValue(8) == 2.000000f) {
        aMiscShakeArea(Object_handles[7], qRandomValue(30.000000f, 70.000000f), 400.000000f);
      }
      if (qUserVarValue(9) == 2.000000f) {
        aMiscShakeArea(Object_handles[6], qRandomValue(30.000000f, 70.000000f), 400.000000f);
      }
      if (qUserVarValue(10) == 2.000000f) {
        aMiscShakeArea(Object_handles[5], qRandomValue(30.000000f, 70.000000f), 400.000000f);
      }
      if (qUserVarValue(11) == 2.000000f) {
        aMiscShakeArea(Object_handles[4], qRandomValue(30.000000f, 70.000000f), 400.000000f);
      }
      aSetLevelTimer(qRandomValue(0.300000f, 2.400000f), 12);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 048: Are you done?
    if (event_data->id == 13) {
      aCinematicSimple(Path_indexes[21], Message_strings[8], Object_handles[3], 10.000000f, 1);
      aEnableShip("Magnum-AHT");

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }

    // Script 057: All 4 Disruptors Collected
    if (event_data->id == 14) {
      if (((ScriptActionCtr_044 > 0) == true) && ((ScriptActionCtr_043 > 0) == true) &&
          ((ScriptActionCtr_042 > 0) == true) && ((ScriptActionCtr_040 > 0) == true)) {
        aUserVarAdd(60.000000f, 2);
        aGoalCompleted(Goal_indexes[6], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 034: Message for Transmitter
    if (1) {
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: MEGA Damage?
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qRandomChance(0.100000f) == true) {
        aSoundPlaySteaming("VoxL09CargoH.osf", 1.000000f);
      }
      aShowHUDMessage(Message_strings[20]);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 080: MEGA Init
    if ((ScriptActionCtr_080 < 1) && (1)) {
      aUserVarSet(5, 2400.000000f);
      aUserVarSet(6, 1600.000000f);
      aUserVarSet(7, 800.000000f);
      aObjSetShields(data->me_handle, qUserVarValue(5));
      aObjMakeInvuln(data->me_handle, 999);
      aSetObjectTimer(data->me_handle, 1.000000f, 15);
      aAISetMaxSpeed(data->me_handle, 35.000000f);
      aAISetTeam(196608, data->me_handle);
      aUserVarSet(4, 1.000000f);
      aUserVarSet(3, qUserVarValue(5));
      aUserVarSet(2, 150.000000f);
      aUserVarSet(1, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 082: Covert Path 3 Call for Help
    if (event_data->id == 16) {
      aSetObjectTimer(data->me_handle, 60.000000f, 16);
      aSoundPlaySteaming("VoxL09CargoM.osf", 1.000000f);
      aShowHUDMessage(Message_strings[6]);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }

    // Script 078: MEGA State Timer Recycle
    if (event_data->id == 15) {
      if (1 == false) {
        aShowHUDMessageF(Message_strings[21], qObjShields(Object_handles[3]));
        aShowHUDMessageF(Message_strings[22], qUserVarValue(2));
      }
      if (qUserVarValue(3) > qObjShields(data->me_handle)) {
        aUserVarSet(1, 0.000000f);
      }
      aUserVarSet(3, qObjShields(data->me_handle));
      aSetObjectTimer(data->me_handle, 1.000000f, 15);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }

    // Script 077: MEGA Cargo State Machine STALLED
    if ((15 == event_data->id) && (qUserVarValue(4) == 4.000000f)) {
      if ((qUserVarValue(2) > 320.000000f) || (qUserVarValue(1) > 30.000000f)) {
        aSoundPlaySteaming("VoxL09CargoK.osf", 1.000000f);
        aShowHUDMessage(Message_strings[23]);
        aObjSetShields(data->me_handle, qUserVarValue(5));
        aUserVarSet(1, 0.000000f);
        aUserVarAdd(45.000000f, 2);
        aAISetTeam(196608, data->me_handle);
        aUserVarSet(4, 1.000000f);
      } else {
        if (qObjShields(data->me_handle) < 10.000000f) {
          aObjSetShields(data->me_handle, qUserVarValue(7));
          aSoundPlaySteaming("VoxL09CargoF.osf", 1.000000f);
          aShowHUDMessage(Message_strings[24]);
        }
        aUserVarInc(1);
      }
      aAISetMaxSpeed(data->me_handle, 0.000000f);
      aObjSpark(data->me_handle, 40.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }

    // Script 076: MEGA Cargo State Machine DAMAGED
    if ((15 == event_data->id) && (qUserVarValue(4) == 3.000000f)) {
      if ((qUserVarValue(2) > 290.000000f) || (qUserVarValue(1) > 45.000000f)) {
        aSoundPlaySteaming("VoxL09CargoK.osf", 1.000000f);
        aShowHUDMessage(Message_strings[23]);
        aObjSetShields(data->me_handle, qUserVarValue(5));
        aUserVarSet(1, 0.000000f);
        aUserVarAdd(40.000000f, 2);
        aAISetTeam(196608, data->me_handle);
        aUserVarSet(4, 1.000000f);
      } else {
        if (qObjShields(data->me_handle) < qUserVarValue(7)) {
          aSoundPlaySteaming("VoxL09CargoL.osf", 1.000000f);
          aShowHUDMessage(Message_strings[25]);
          aUserVarSet(1, 0.000000f);
          aAISetTeam(65536, data->me_handle);
          aUserVarSet(4, 4.000000f);
        } else {
          aUserVarInc(1);
        }
      }
      aAISetMaxSpeed(data->me_handle, 20.000000f);
      aObjSpark(data->me_handle, 15.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }

    // Script 075: MEGA Cargo State Machine REBEL
    if ((15 == event_data->id) && (qUserVarValue(4) == 2.000000f)) {
      if ((qUserVarValue(2) > 200.000000f) || (qUserVarValue(1) > 60.000000f)) {
        aSoundPlaySteaming("VoxL09CargoG.osf", 1.000000f);
        aShowHUDMessage(Message_strings[26]);
        aObjSetShields(data->me_handle, qUserVarValue(5));
        aUserVarSet(1, 0.000000f);
        aUserVarAdd(35.000000f, 2);
        aAISetTeam(196608, data->me_handle);
        aUserVarSet(4, 1.000000f);
      } else {
        if (qObjShields(data->me_handle) < qUserVarValue(6)) {
          aSoundPlaySteaming("VoxL09CargoA.osf", 1.000000f);
          aShowHUDMessage(Message_strings[27]);
          aUserVarSet(1, 0.000000f);
          aAISetTeam(65536, data->me_handle);
          aUserVarSet(4, 3.000000f);
        } else {
          aUserVarInc(1);
        }
      }
      aAISetMaxSpeed(data->me_handle, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }

    // Script 014: MEGA Cargo State Machine SAFE
    if ((15 == event_data->id) && (qUserVarValue(4) == 1.000000f)) {
      if (qUserVarValue(2) < 0.000000f) {
        aSoundPlaySteaming("VoxL09CargoB.osf", 1.000000f);
        aShowHUDMessage(Message_strings[28]);
        aUserVarSet(1, 0.000000f);
        aUserVarSet(2, 0.000000f);
        aAISetTeam(65536, data->me_handle);
        aUserVarSet(4, 2.000000f);
      } else {
        if (qObjShields(data->me_handle) < qUserVarValue(6)) {
          if (qUserVarValue(2) > 200.000000f) {
            aUserVarSet(2, 200.000000f);
          }
          aSoundPlaySteaming("VoxL09CargoA.osf", 1.000000f);
          aShowHUDMessage(Message_strings[27]);
          aUserVarSet(1, 0.000000f);
          aAISetTeam(65536, data->me_handle);
          aUserVarSet(4, 3.000000f);
        } else {
          aUserVarDec(2);
          if ((qObjGetDistance(data->me_handle, qPlayerClosest(data->me_handle, 0)) < 300.000000f) &&
              ((ScriptActionCtr_007 > 0) == true)) {
            aUserVarSub(1.000000f, 2);
          }
          if ((qUserVarValue(0) < 150.000000f) && ((ScriptActionCtr_007 > 0) == true)) {
            aUserVarSub(1.000000f, 2);
          }
        }
      }
      aAISetMaxSpeed(data->me_handle, 35.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 007: Covert Path-2
    if (event_data->goal_uid == 0) {
      aObjMakeVulnerable(data->me_handle);
      aSoundPlaySteaming("VoxL09CargoD.osf", 1.000000f);
      aShowHUDMessage(Message_strings[2]);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[3], 1048832, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 008: Covert Path-2 Pickup
    if (event_data->goal_uid == 1) {
      aSoundPlaySteaming("VoxL09CargoJ.osf", 1.000000f);
      aShowHUDMessage(Message_strings[3]);
      aUserVarSub(3.000000f, 2);
      aAIGoalPickUpObject(data->me_handle, 0, Object_handles[8], 0, 1, 3, 256, 4);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 047: Covert Path-2 Out
    if (event_data->goal_uid == 4) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[4], 1048832, 3, 3);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 061: Covert Path-3
    if (event_data->goal_uid == 3) {
      aSoundPlaySteaming("VoxL09CargoC.osf", 1.000000f);
      aShowHUDMessage(Message_strings[4]);
      aUnCloakObject(Object_handles[0]);
      aAIGoalPickUpObject(Object_handles[0], 0, Object_handles[8], 0, 1, 3, 256, -1);
      aDropObjects(data->me_handle);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[5], 1048832, 2, 3);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }

    // Script 069: Covert Path-3 Part 2
    if (event_data->goal_uid == 2) {
      if (qPortalIsOn(0, Room_indexes[0]) == false) {
        aAIGoalFollowPathSimple(data->me_handle, Path_indexes[6], 1048832, 5, 3);
      } else {
        aSetObjectTimer(data->me_handle, 60.000000f, 16);
        aSoundPlaySteaming("VoxL09CargoE.osf", 1.000000f);
        aUserFlagSet(0, 1);
        aShowHUDMessage(Message_strings[5]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }

    // Script 070: Covert Path-3 Part 3
    if (event_data->goal_uid == 5) {
      if (qPortalIsOn(0, Room_indexes[1]) == false) {
        aAIGoalFollowPathSimple(data->me_handle, Path_indexes[7], 1048832, 6, 3);
      } else {
        aSetObjectTimer(data->me_handle, 60.000000f, 16);
        aUserFlagSet(1, 1);
        aSoundPlaySteaming("VoxL09CargoE.osf", 1.000000f);
        aShowHUDMessage(Message_strings[5]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }

    // Script 068: Covert Path-3 Pickup
    if (event_data->goal_uid == 6) {
      aSoundPlaySteaming("VoxL09CargoJ.osf", 1.000000f);
      aShowHUDMessage(Message_strings[3]);
      aUserVarSub(3.000000f, 2);
      aAIGoalPickUpObject(data->me_handle, 0, Object_handles[9], 0, 1, 3, 256, 7);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }

    // Script 071: Covert Path-3 Out
    if (event_data->goal_uid == 7) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[8], 1048832, 8, 3);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }

    // Script 038: Covert Path-4
    if (event_data->goal_uid == 8) {
      aSoundPlaySteaming("VoxL09CargoC.osf", 1.000000f);
      aShowHUDMessage(Message_strings[4]);
      aUnCloakObject(Object_handles[1]);
      aAIGoalPickUpObject(Object_handles[1], 0, Object_handles[9], 0, 1, 3, 256, -1);
      aDropObjects(data->me_handle);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[9], 1048832, 9, 3);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 072: Covert Path-4 Pickup
    if (event_data->goal_uid == 9) {
      aSoundPlaySteaming("VoxL09CargoJ.osf", 1.000000f);
      aShowHUDMessage(Message_strings[3]);
      aUserVarSub(3.000000f, 2);
      aAIGoalPickUpObject(data->me_handle, 0, Object_handles[10], 0, 1, 3, 256, 10);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }

    // Script 073: Covert Path-4 Out
    if (event_data->goal_uid == 10) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[10], 1048832, 11, 3);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }

    // Script 074: Covert Path-4 Done
    if (event_data->goal_uid == 11) {
      aSoundPlaySteaming("VoxL09CargoI.osf", 1.000000f);
      aShowHUDMessage(Message_strings[7]);
      aGoalCompleted(Goal_indexes[0], 1);
      aUserFlagSet(2, 1);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[11], 1048832, -1, 3);
      aAISetTeam(196608, data->me_handle);
      aCancelTimer(15);
      aEnableShip("Magnum-AHT");
      aAISetMaxSpeed(data->me_handle, 35.000000f);
      aSetLevelTimer(5.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 083: End Level After Camera
    if ((ScriptActionCtr_083 < 1) && (qUserFlag(2) == true)) {
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18D5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 059: Recovery-2 Return
    if ((ScriptActionCtr_059 < 1) && (1)) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[12], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18D6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 058: Recovery-1 Return
    if ((ScriptActionCtr_058 < 1) && (1)) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[12], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1030::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: FF Hit 13
    if ((ScriptActionCtr_009 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aUserVarAdd(5.000000f, 2);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      if ((ScriptActionCtr_039 > 0) == true) {
        if (qUserFlag(0) == true) {
          aAIGoalFollowPathSimple(Object_handles[3], Path_indexes[6], 1048832, 5, 3);
          aCancelTimer(16);
          aSoundPlaySteaming("VoxL09CargoN.osf", 1.000000f);
          aShowHUDMessage(Message_strings[9]);
        }
        aPortalRenderSet(0, 0, Room_indexes[0], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1038::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: FF Hit 14
    if ((ScriptActionCtr_039 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aUserVarAdd(5.000000f, 2);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      if ((ScriptActionCtr_009 > 0) == true) {
        if (qUserFlag(0) == true) {
          aAIGoalFollowPathSimple(Object_handles[3], Path_indexes[6], 1048832, 5, 3);
          aCancelTimer(16);
          aSoundPlaySteaming("VoxL09CargoN.osf", 1.000000f);
          aShowHUDMessage(Message_strings[9]);
        }
        aPortalRenderSet(0, 0, Room_indexes[0], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0869::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: FF Hit 23
    if ((ScriptActionCtr_037 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aUserVarAdd(5.000000f, 2);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      if ((ScriptActionCtr_035 > 0) == true) {
        if (qUserFlag(1) == true) {
          aAIGoalFollowPathSimple(Object_handles[3], Path_indexes[7], 1048832, 6, 3);
          aSoundPlaySteaming("VoxL09CargoN.osf", 1.000000f);
          aCancelTimer(16);
          aShowHUDMessage(Message_strings[9]);
        }
        aPortalRenderSet(0, 0, Room_indexes[1], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_086A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: FF Hit 24
    if ((ScriptActionCtr_035 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aUserVarAdd(5.000000f, 2);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      if ((ScriptActionCtr_037 > 0) == true) {
        if (qUserFlag(1) == true) {
          aAIGoalFollowPathSimple(Object_handles[3], Path_indexes[7], 1048832, 6, 3);
          aCancelTimer(16);
          aSoundPlaySteaming("VoxL09CargoN.osf", 1.000000f);
          aShowHUDMessage(Message_strings[9]);
        }
        aPortalRenderSet(0, 0, Room_indexes[1], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_106E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Disruptor Powerup 4
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aSetLevelTimer(0.000000f, 14);
      aShowHUDMessage(Message_strings[10]);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 050: Disruptor Control-4
    if (1) {
      if ((qObjGetDistance(event_data->it_handle, Object_handles[7]) < 28.000000f) &&
          (qObjAnimFrame(Object_handles[7]) == 5.000000f) && (qUserVarValue(8) == 1.000000f)) {
        aUserVarSet(8, 2.000000f);
        aSetObjectTimer(Object_handles[7], 0.000000f, 3);
      } else {
        if ((qObjGetDistance(event_data->it_handle, Object_handles[6]) < 28.000000f) &&
            (qObjAnimFrame(Object_handles[6]) == 5.000000f) && (qUserVarValue(9) == 1.000000f)) {
          aUserVarSet(9, 2.000000f);
          aSetObjectTimer(Object_handles[6], 0.000000f, 4);
        } else {
          if ((qObjGetDistance(event_data->it_handle, Object_handles[5]) < 28.000000f) &&
              (qObjAnimFrame(Object_handles[5]) == 5.000000f) && (qUserVarValue(10) == 1.000000f)) {
            aUserVarSet(10, 2.000000f);
            aSetObjectTimer(Object_handles[5], 0.000000f, 5);
          } else {
            if ((qObjGetDistance(event_data->it_handle, Object_handles[4]) < 28.000000f) &&
                (qObjAnimFrame(Object_handles[4]) == 5.000000f) && (qUserVarValue(11) == 1.000000f)) {
              aUserVarSet(11, 2.000000f);
              aSetObjectTimer(Object_handles[4], 0.000000f, 6);
            } else {
              aObjGhostSet(0, data->me_handle);
              aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_106F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Disruptor Powerup 3
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[10]);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aSetLevelTimer(0.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 056: Disruptor Control-3
    if (1) {
      if ((qObjGetDistance(event_data->it_handle, Object_handles[7]) < 28.000000f) &&
          (qObjAnimFrame(Object_handles[7]) == 5.000000f) && (qUserVarValue(8) == 1.000000f)) {
        aUserVarSet(8, 2.000000f);
        aSetObjectTimer(Object_handles[7], 0.000000f, 3);
      } else {
        if ((qObjGetDistance(event_data->it_handle, Object_handles[6]) < 28.000000f) &&
            (qObjAnimFrame(Object_handles[6]) == 5.000000f) && (qUserVarValue(9) == 1.000000f)) {
          aUserVarSet(9, 2.000000f);
          aSetObjectTimer(Object_handles[6], 0.000000f, 4);
        } else {
          if ((qObjGetDistance(event_data->it_handle, Object_handles[5]) < 28.000000f) &&
              (qObjAnimFrame(Object_handles[5]) == 5.000000f) && (qUserVarValue(10) == 1.000000f)) {
            aUserVarSet(10, 2.000000f);
            aSetObjectTimer(Object_handles[5], 0.000000f, 5);
          } else {
            if ((qObjGetDistance(event_data->it_handle, Object_handles[4]) < 28.000000f) &&
                (qObjAnimFrame(Object_handles[4]) == 5.000000f) && (qUserVarValue(11) == 1.000000f)) {
              aUserVarSet(11, 2.000000f);
              aSetObjectTimer(Object_handles[4], 0.000000f, 6);
            } else {
              aObjGhostSet(0, data->me_handle);
              aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_106D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Disruptor Powerup 2
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[10]);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aSetLevelTimer(0.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 055: Disruptor Control-2
    if (1) {
      if ((qObjGetDistance(event_data->it_handle, Object_handles[7]) < 28.000000f) &&
          (qObjAnimFrame(Object_handles[7]) == 5.000000f) && (qUserVarValue(8) == 1.000000f)) {
        aUserVarSet(8, 2.000000f);
        aSetObjectTimer(Object_handles[7], 0.000000f, 3);
      } else {
        if ((qObjGetDistance(event_data->it_handle, Object_handles[6]) < 28.000000f) &&
            (qObjAnimFrame(Object_handles[6]) == 5.000000f) && (qUserVarValue(9) == 1.000000f)) {
          aUserVarSet(9, 2.000000f);
          aSetObjectTimer(Object_handles[6], 0.000000f, 4);
        } else {
          if ((qObjGetDistance(event_data->it_handle, Object_handles[5]) < 28.000000f) &&
              (qObjAnimFrame(Object_handles[5]) == 5.000000f) && (qUserVarValue(10) == 1.000000f)) {
            aUserVarSet(10, 2.000000f);
            aSetObjectTimer(Object_handles[5], 0.000000f, 5);
          } else {
            if ((qObjGetDistance(event_data->it_handle, Object_handles[4]) < 28.000000f) &&
                (qObjAnimFrame(Object_handles[4]) == 5.000000f) && (qUserVarValue(11) == 1.000000f)) {
              aUserVarSet(11, 2.000000f);
              aSetObjectTimer(Object_handles[4], 0.000000f, 6);
            } else {
              aObjGhostSet(0, data->me_handle);
              aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_106C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: Disruptor Powerup 1
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[10]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSetLevelTimer(0.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 054: Disruptor Control-1
    if (1) {
      if ((qObjGetDistance(event_data->it_handle, Object_handles[7]) < 28.000000f) &&
          (qObjAnimFrame(Object_handles[7]) == 5.000000f) && (qUserVarValue(8) == 1.000000f)) {
        aUserVarSet(8, 2.000000f);
        aSetObjectTimer(Object_handles[7], 0.000000f, 3);
      } else {
        if ((qObjGetDistance(event_data->it_handle, Object_handles[6]) < 28.000000f) &&
            (qObjAnimFrame(Object_handles[6]) == 5.000000f) && (qUserVarValue(9) == 1.000000f)) {
          aUserVarSet(9, 2.000000f);
          aSetObjectTimer(Object_handles[6], 0.000000f, 4);
        } else {
          if ((qObjGetDistance(event_data->it_handle, Object_handles[5]) < 28.000000f) &&
              (qObjAnimFrame(Object_handles[5]) == 5.000000f) && (qUserVarValue(10) == 1.000000f)) {
            aUserVarSet(10, 2.000000f);
            aSetObjectTimer(Object_handles[5], 0.000000f, 5);
          } else {
            if ((qObjGetDistance(event_data->it_handle, Object_handles[4]) < 28.000000f) &&
                (qObjAnimFrame(Object_handles[4]) == 5.000000f) && (qUserVarValue(11) == 1.000000f)) {
              aUserVarSet(11, 2.000000f);
              aSetObjectTimer(Object_handles[4], 0.000000f, 6);
            } else {
              aObjGhostSet(0, data->me_handle);
              aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_100F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 045: Stabilizer Done Control
    if ((ScriptActionCtr_045 < 1) && (event_data->id == 3)) {
      aGoalCompleted(Goal_indexes[1], 1);
      aSetLevelTimer(0.000000f, 11);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAttachObject("seismicdisruptor", 0, Object_handles[7], 1);
      aObjSpark(data->me_handle, 40.000000f, 999999.000000f);
      aCinematicSimple(Path_indexes[17], Message_strings[11], Object_handles[7], 6.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 041: Pounder Control
    if ((event_data->id == 7) && (qUserVarValue(8) == 0.000000f)) {
      if ((qUserVarValue(8) == 0.000000f) && (1)) {
        aMiscShakeArea(data->me_handle, 100.000000f, 300.000000f);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 2, 6, 2.000000f, 0);
      aSetObjectTimer(data->me_handle, 2.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0871::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: Stabilizer Power Control
    if ((ScriptActionCtr_049 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(50.000000f);
      aUserVarSet(8, 1.000000f);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aObjPlayAnim(Object_handles[7], 2, 5, 2.000000f, 0);
      aShowHUDMessage(Message_strings[12]);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0811::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 064: Stabilizer Done Store
    if ((ScriptActionCtr_064 < 1) && (event_data->id == 6)) {
      aGoalCompleted(Goal_indexes[2], 1);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAttachObject("seismicdisruptor", 0, data->me_handle, 1);
      aObjSpark(data->me_handle, 40.000000f, 999999.000000f);
      aCinematicSimple(Path_indexes[18], Message_strings[13], data->me_handle, 6.000000f, 0);
      aSetLevelTimer(0.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }

    // Script 052: Pounder Store
    if ((event_data->id == 10) && (qUserVarValue(11) == 0.000000f)) {
      if ((qUserVarValue(11) == 0.000000f) && (1)) {
        aMiscShakeArea(data->me_handle, 100.000000f, 300.000000f);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 2, 6, 2.000000f, 0);
      aSetObjectTimer(data->me_handle, 2.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0810::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 063: Stabilizer Done Assembly
    if ((ScriptActionCtr_063 < 1) && (event_data->id == 5)) {
      aGoalCompleted(Goal_indexes[3], 1);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAttachObject("seismicdisruptor", 0, data->me_handle, 1);
      aObjSpark(data->me_handle, 40.000000f, 999999.000000f);
      aCinematicSimple(Path_indexes[19], Message_strings[14], data->me_handle, 6.000000f, 0);
      aSetLevelTimer(0.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }

    // Script 051: Pounder Assembly
    if ((event_data->id == 9) && (qUserVarValue(10) == 0.000000f)) {
      if ((qUserVarValue(10) == 0.000000f) && (1)) {
        aMiscShakeArea(data->me_handle, 100.000000f, 300.000000f);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 2, 6, 2.000000f, 0);
      aSetObjectTimer(data->me_handle, 2.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 062: Stabilizer Done Factory
    if ((ScriptActionCtr_062 < 1) && (event_data->id == 4)) {
      aGoalCompleted(Goal_indexes[4], 1);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAttachObject("seismicdisruptor", 0, data->me_handle, 1);
      aObjSpark(data->me_handle, 40.000000f, 999999.000000f);
      aCinematicSimple(Path_indexes[20], Message_strings[15], data->me_handle, 6.000000f, 0);
      aSetLevelTimer(0.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }

    // Script 046: Pounder Factory
    if ((event_data->id == 8) && (qUserVarValue(9) == 0.000000f)) {
      if ((qUserVarValue(9) == 0.000000f) && (1)) {
        aMiscShakeArea(data->me_handle, 100.000000f, 300.000000f);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 2, 6, 2.000000f, 0);
      aSetObjectTimer(data->me_handle, 2.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0873::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Stabilizer Power Store
    if ((ScriptActionCtr_067 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(50.000000f);
      aUserVarSet(11, 1.000000f);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aObjPlayAnim(Object_handles[4], 2, 5, 2.000000f, 0);
      aShowHUDMessage(Message_strings[16]);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0872::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Stabilizer Power Assembly
    if ((ScriptActionCtr_066 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(50.000000f);
      aUserVarSet(10, 1.000000f);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aObjPlayAnim(Object_handles[5], 2, 5, 2.000000f, 0);
      aShowHUDMessage(Message_strings[17]);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2070::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Stabilizer Power Factory
    if ((ScriptActionCtr_065 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(50.000000f);
      aUserVarSet(9, 1.000000f);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aObjPlayAnim(Object_handles[6], 2, 5, 2.000000f, 0);
      aShowHUDMessage(Message_strings[18]);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18AA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 081: Radar-2 Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[29]);
      aUserVarAdd(25.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18C1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 004: Radar-1 Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[29]);
      aUserVarAdd(25.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0948::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 003: Ant-3 Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[30]);
      aUserVarAdd(20.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0949::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 002: Ant-2 Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[30]);
      aUserVarAdd(20.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18AC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 001: Ant-1 Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[30]);
      aUserVarAdd(20.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_094E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Transmitter Pickup
    if (1) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 084: Transmitter Give
    if ((ScriptActionCtr_084 < 1) && (qObjType(qPlayerClosest(data->me_handle, -1)) == 4)) {
      aAddObjectToInventory(data->me_handle, qPlayerClosest(data->me_handle, -1), 0);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 086: Transmitter USE
    if (1) {
      aShowHUDMessageObj(Message_strings[31], event_data->it_handle);
      aSoundPlay2D(Sound_indexes[5], 1.000000f);
      aCreatePopupView(0, Object_handles[3], 10.000000f, 1.000000f);
      aObjGhostSet(0, data->me_handle);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: EndLevel-Factory
    if ((ScriptActionCtr_010 < 1) && (qUserFlag(4) == true)) {
      aStartEndlevelSequencePath(Path_indexes[13], Path_indexes[14], 12.000000f, Message_strings[8]);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }

    // Script 053: EndLevel-Storage
    if ((ScriptActionCtr_053 < 1) && (qUserFlag(4) == true)) {
      aStartEndlevelSequencePath(Path_indexes[15], Path_indexes[16], 12.000000f, Message_strings[8]);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Music-Outside-3
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 022: Music-Factory-5
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Music-Outside-2
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 017: Music-Storage-4
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Music-Storage-3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Music-Storage-2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 089: Generic Voice-3
    if ((ScriptActionCtr_089 < 1) && (1)) {
      aSoundPlaySteaming("VoxL09GeneralC.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Music-Storage-1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Music-Factory-4
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: Music-Factory-3
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Music-Factory-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Music-Factory-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 090: Generic Voice-4
    if ((ScriptActionCtr_090 < 1) && (1)) {
      aSoundPlaySteaming("VoxL09GeneralD.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Music-Assembly-4
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Music-Assembly-3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Music-Assembly-2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 087: Generic Voice-1
    if ((ScriptActionCtr_087 < 1) && (1)) {
      aSoundPlaySteaming("VoxL09GeneralA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Music-Assembly-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: Music-Control-5
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Music-Control-4
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: Music-Control-3
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 088: Generic Voice-2
    if ((ScriptActionCtr_088 < 1) && (1)) {
      aSoundPlaySteaming("VoxL09GeneralB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Music-Control-2
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Music-Control-1
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
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
NEXT_ID		92

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:CSDistance
1:CSAlone
2:CSDistraction
3:CSDamage
4:CSSTATE
5:HealthFull
6:HealthHalf
7:HealthStopped
8:StabControl
9:StabFactory
10:StabAssembly
11:StabStore
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:FFStuck1
1:FFStuck2
2:CovertDone
3:DisruptorDone
4:LevelDone
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:MusicChange
1:CovertFirstPath
2:CheckFF
3:StabControlDone
4:StabFactoryDone
5:StabAssemblyDone
6:StabStoreDone
7:PoundControl
8:PoundFactory
9:PoundAssembly
10:PoundStore
11:CheckStabDone
12:RandomShake
13:YouAreDone
14:All4Disruptors
15:MegaState
16:StillStuckFF
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:CovertPath1
1:CovertPath2
2:CovertPath3
3:CovertPath2Out
4:CovertPath2Pickup
5:Covert3Part2
6:Covert3Part3
7:Covert3Pickup
8:Covert3Out
9:Covert4
10:Covert4Pickup
11:Covert4Out
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
$$DOOR_LIST_END

$$OBJECT_LIST_START
Recovery-2
Recovery-1
DisruptorPowerup1
Covert
Stabilizer-Store
Stabilizer-Assembl
Stabilizer-Factory
Stabilizer-Control
Component-1
Component-2
Component-3
FF-13
FF-14
FF-23
FF-24
DisruptorPowerup4
DisruptorPowerup3
DisruptorPowerup2
PowerStab-Control
PowerStab-Store
PowerStab-Assembly
PowerStab-Factory
Radar-2
Radar-1
Ant-3
Ant-2
Ant-1
Transmitter
$$OBJECT_LIST_END

$$ROOM_LIST_START
Forcefield-1
Forcefield-2
$$ROOM_LIST_END

$$TRIGGER_LIST_START
Exit-Factory
Entrance-Factory
Entrance-Storage
MStorage-3
MStorage-2
MStorage-1
MFactory-4
MFactory-3
MFactory-2
MFactory-1
MAssembly-4
MAssembly-3
MAssembly-2
MAssembly-1
MControl-5
MControl-4
MControl-3
MControl-2
MControl-1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch11
PupC1
AmbSirenIntense
AmbSwitch31
Earthshaker missile firing
HudMessage
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
Magnum-AHT
seismicdisruptor
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
Covert-1
Covert-2
Covert-2-Out
Covert-3
Covert-3-2
Covert-3-3
Covert-3-Out
Covert-4
Covert-4-Out
Covert-5-Exit
Recovery
ExitCam-Factory
ExitShip-Factory
ExitCam-Storage
ExitShip-Storage
StabControl
StabStore
StabAssembly
StabFactory
EndLevel
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Escort the Covert Cargo Ship
Disrupt Control Seismic Stabilizer
Disrupt Storage Seismic Stabilizer
Disrupt Assembly Seismic Stabilizer
Disrupt Factory Seismic Stabilizer
Disrupt All Four Seismic Stabilizers
Collect Seismic Disruptors
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL09StartLevel.osf
VoxL09CargoD.osf
VoxL09CargoJ.osf
VoxL09CargoC.osf
VoxL09CargoE.osf
VoxL09CargoM.osf
VoxL09CargoI.osf
VoxL09CargoN.osf
VoxL09CargoH.osf
VoxL09CargoK.osf
VoxL09CargoF.osf
VoxL09CargoL.osf
VoxL09CargoG.osf
VoxL09CargoA.osf
VoxL09CargoB.osf
VoxL09GeneralD.osf
VoxL09GeneralC.osf
VoxL09GeneralB.osf
VoxL09GeneralA.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:36:Level Init
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:40.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:999999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:999999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
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
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Intro Cam 2
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:IntroCam:Text
                        10:1:0:2:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Message for Transmitter
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TransmitterHave:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Start Covert Path
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:16:2:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Stabilizers Init
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:2.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:2.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:2.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:6:2.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Covert Path-2
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovEntering:Message
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:3:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Covert Path-2 Pickup
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovPickup:Message
                        $$CHILD_BLOCK_END
                08:aUserVarSub
                        $$CHILD_BLOCK_START
                        10:6:3.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Picker
                        10:4:0:PickerPoint
                        10:1:0:8:Pickee
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:4:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Covert Path-2 Out
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:4:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:4:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Covert Path-3
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:3:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovDropOff:Message
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:0:0:Picker
                        10:4:0:PickerPoint
                        10:1:0:8:Pickee
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aDropObjects
                        $$CHILD_BLOCK_START
                        10:1:2:-1:ParentObject
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:5:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:2:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Covert Path-3 Part 2
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:2:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qPortalIsOn:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:0:PortalNum
                                        10:2:0:Room
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:16:6:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:5:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:60.000000:Time
                                10:10:0:16:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:4:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CovFFHelp:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Covert Path-3 Part 3
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:5:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qPortalIsOn:Bool
                                        $$CHILD_BLOCK_START
                                        10:4:0:PortalNum
                                        10:2:1:Room
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:16:7:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:6:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:60.000000:Time
                                10:10:0:16:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:4:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CovFFHelp:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Covert Path 3 Call for Help
        $$CHILD_BLOCK_START
        01:1:3
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovStillStuckFF:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Covert Path-3 Pickup
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:6:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovPickup:Message
                        $$CHILD_BLOCK_END
                08:aUserVarSub
                        $$CHILD_BLOCK_START
                        10:6:3.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Picker
                        10:4:0:PickerPoint
                        10:1:0:9:Pickee
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:7:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Covert Path-3 Out
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:7:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:8:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Covert Path-4
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:8:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovDropOff:Message
                        $$CHILD_BLOCK_END
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:0:1:Picker
                        10:4:0:PickerPoint
                        10:1:0:9:Pickee
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aDropObjects
                        $$CHILD_BLOCK_START
                        10:1:2:-1:ParentObject
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:9:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:Covert Path-4 Pickup
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:9:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovPickup:Message
                        $$CHILD_BLOCK_END
                08:aUserVarSub
                        $$CHILD_BLOCK_START
                        10:6:3.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Picker
                        10:4:0:PickerPoint
                        10:1:0:10:Pickee
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:10:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Covert Path-4 Out
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:10:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:10:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:11:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Covert Path-4 Done
        $$CHILD_BLOCK_START
        01:1:3
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:11:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovLeaving:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:11:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                08:aEnableShip
                        $$CHILD_BLOCK_START
                        10:13:0:Ship
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:35.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Recovery-2 Return
        $$CHILD_BLOCK_START
        01:1:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:12:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Recovery-1 Return
        $$CHILD_BLOCK_START
        01:1:1
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:12:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:EndLevel-Factory
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:13:CameraPath
                        10:16:14:PlayerPath
                        10:6:12.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:EndLevel-Storage
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:15:CameraPath
                        10:16:16:PlayerPath
                        10:6:12.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Start-Music
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
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Music-Outside-3
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Music-Outside-2
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Music-Storage-4
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Music-Storage-3
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Music-Storage-2
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Music-Storage-1
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Music-Factory-5
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Music-Factory-4
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Music-Factory-3
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Music-Factory-2
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Music-Factory-1
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Music-Assembly-4
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Music-Assembly-3
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Music-Assembly-2
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Music-Assembly-1
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Music-Control-5
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Music-Control-4
        $$CHILD_BLOCK_START
        01:0:15
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Music-Control-3
        $$CHILD_BLOCK_START
        01:0:16
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Music-Control-2
        $$CHILD_BLOCK_START
        01:0:17
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Music-Control-1
        $$CHILD_BLOCK_START
        01:0:18
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:FF Hit 13
        $$CHILD_BLOCK_START
        01:1:11
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:5.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:39:ScriptID
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
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        10:16:6:Path
                                        10:15:1048832:AIGoalFlags
                                        10:10:0:5:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aCancelTimer
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:TimerID
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:7:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovThanksFF:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:FF Hit 14
        $$CHILD_BLOCK_START
        01:1:12
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:5.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
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
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        10:16:6:Path
                                        10:15:1048832:AIGoalFlags
                                        10:10:0:5:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aCancelTimer
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:TimerID
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:7:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovThanksFF:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:FF Hit 23
        $$CHILD_BLOCK_START
        01:1:13
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:5.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:35:ScriptID
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
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        10:16:7:Path
                                        10:15:1048832:AIGoalFlags
                                        10:10:0:6:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:7:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aCancelTimer
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:TimerID
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovThanksFF:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:FF Hit 24
        $$CHILD_BLOCK_START
        01:1:14
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:5.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:37:ScriptID
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
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        10:16:7:Path
                                        10:15:1048832:AIGoalFlags
                                        10:10:0:6:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aCancelTimer
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:TimerID
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:7:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovThanksFF:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Disruptor Powerup 4
        $$CHILD_BLOCK_START
        01:1:15
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Disruptor:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Disruptor Powerup 3
        $$CHILD_BLOCK_START
        01:1:16
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Disruptor:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Disruptor Powerup 2
        $$CHILD_BLOCK_START
        01:1:17
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Disruptor:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Disruptor Powerup 1
        $$CHILD_BLOCK_START
        01:1:2
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Disruptor:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Disruptor Control-4
        $$CHILD_BLOCK_START
        01:1:15
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object1
                                                10:1:0:7:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:28.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:7:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjGetDistance:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object1
                                                        10:1:0:6:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:28.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:6:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:5.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:9:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserVar
                                        10:6:2.000000:value
                                        $$CHILD_BLOCK_END
                                08:aSetObjectTimer
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        10:6:0.000000:Time
                                        10:10:0:4:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjGetDistance:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:1:-1:Object1
                                                                10:1:0:5:Object2
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:28.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:5:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:10:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:1.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserVar
                                                10:6:2.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetObjectTimer
                                                $$CHILD_BLOCK_START
                                                10:1:0:5:Object
                                                10:6:0.000000:Time
                                                10:10:0:5:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                09:0
                                                        $$CHILD_BLOCK_START
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjGetDistance:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:1:-1:Object1
                                                                        10:1:0:4:Object2
                                                                        $$CHILD_BLOCK_END
                                                                07:1:3
                                                                10:6:28.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjAnimFrame:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:0:4:Object
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qUserVarValue:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:11:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:1.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:11:UserVar
                                                        10:6:2.000000:value
                                                        $$CHILD_BLOCK_END
                                                08:aSetObjectTimer
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:4:Object
                                                        10:6:0.000000:Time
                                                        10:10:0:6:TimerID
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
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Disruptor Control-3
        $$CHILD_BLOCK_START
        01:1:16
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object1
                                                10:1:0:7:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:28.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:7:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjGetDistance:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object1
                                                        10:1:0:6:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:28.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:6:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:5.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:9:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserVar
                                        10:6:2.000000:value
                                        $$CHILD_BLOCK_END
                                08:aSetObjectTimer
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        10:6:0.000000:Time
                                        10:10:0:4:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjGetDistance:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:1:-1:Object1
                                                                10:1:0:5:Object2
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:28.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:5:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:10:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:1.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserVar
                                                10:6:2.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetObjectTimer
                                                $$CHILD_BLOCK_START
                                                10:1:0:5:Object
                                                10:6:0.000000:Time
                                                10:10:0:5:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                09:0
                                                        $$CHILD_BLOCK_START
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjGetDistance:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:1:-1:Object1
                                                                        10:1:0:4:Object2
                                                                        $$CHILD_BLOCK_END
                                                                07:1:3
                                                                10:6:28.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjAnimFrame:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:0:4:Object
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qUserVarValue:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:11:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:1.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:11:UserVar
                                                        10:6:2.000000:value
                                                        $$CHILD_BLOCK_END
                                                08:aSetObjectTimer
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:4:Object
                                                        10:6:0.000000:Time
                                                        10:10:0:6:TimerID
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
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Disruptor Control-2
        $$CHILD_BLOCK_START
        01:1:17
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object1
                                                10:1:0:7:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:28.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:7:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjGetDistance:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object1
                                                        10:1:0:6:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:28.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:6:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:5.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:9:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserVar
                                        10:6:2.000000:value
                                        $$CHILD_BLOCK_END
                                08:aSetObjectTimer
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        10:6:0.000000:Time
                                        10:10:0:4:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjGetDistance:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:1:-1:Object1
                                                                10:1:0:5:Object2
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:28.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:5:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:10:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:1.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserVar
                                                10:6:2.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetObjectTimer
                                                $$CHILD_BLOCK_START
                                                10:1:0:5:Object
                                                10:6:0.000000:Time
                                                10:10:0:5:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                09:0
                                                        $$CHILD_BLOCK_START
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjGetDistance:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:1:-1:Object1
                                                                        10:1:0:4:Object2
                                                                        $$CHILD_BLOCK_END
                                                                07:1:3
                                                                10:6:28.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjAnimFrame:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:0:4:Object
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qUserVarValue:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:11:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:1.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:11:UserVar
                                                        10:6:2.000000:value
                                                        $$CHILD_BLOCK_END
                                                08:aSetObjectTimer
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:4:Object
                                                        10:6:0.000000:Time
                                                        10:10:0:6:TimerID
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
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Disruptor Control-1
        $$CHILD_BLOCK_START
        01:1:2
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object1
                                                10:1:0:7:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:28.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:7:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:6:0.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjGetDistance:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object1
                                                        10:1:0:6:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:28.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:6:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:5.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:9:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserVar
                                        10:6:2.000000:value
                                        $$CHILD_BLOCK_END
                                08:aSetObjectTimer
                                        $$CHILD_BLOCK_START
                                        10:1:0:6:Object
                                        10:6:0.000000:Time
                                        10:10:0:4:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjGetDistance:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:1:-1:Object1
                                                                10:1:0:5:Object2
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:28.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:5:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:10:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:1.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserVar
                                                10:6:2.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetObjectTimer
                                                $$CHILD_BLOCK_START
                                                10:1:0:5:Object
                                                10:6:0.000000:Time
                                                10:10:0:5:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                09:0
                                                        $$CHILD_BLOCK_START
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjGetDistance:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:1:-1:Object1
                                                                        10:1:0:4:Object2
                                                                        $$CHILD_BLOCK_END
                                                                07:1:3
                                                                10:6:28.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qObjAnimFrame:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:0:4:Object
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:5.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qUserVarValue:Float
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:11:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:6:1.000000:Literal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:11:UserVar
                                                        10:6:2.000000:value
                                                        $$CHILD_BLOCK_END
                                                08:aSetObjectTimer
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:4:Object
                                                        10:6:0.000000:Time
                                                        10:10:0:6:TimerID
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
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Stabilizer Done Control
        $$CHILD_BLOCK_START
        01:1:7
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAttachObject
                        $$CHILD_BLOCK_START
                        10:13:1:ChildTypeName
                        10:4:0:ChildPoint
                        10:1:0:7:Parent
                        10:4:1:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:17:CameraPath
                        10:8:StabControlDone:Text
                        10:1:0:7:Target
                        10:6:6.000000:Seconds
                        10:5:0:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Stabilizer Power Control
        $$CHILD_BLOCK_START
        01:1:18
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Amount
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:2:StartFrame
                        10:4:5:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:StabControlPower:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Stabilizer Done Store
        $$CHILD_BLOCK_START
        01:1:4
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAttachObject
                        $$CHILD_BLOCK_START
                        10:13:1:ChildTypeName
                        10:4:0:ChildPoint
                        10:1:2:-1:Parent
                        10:4:1:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:18:CameraPath
                        10:8:StabStoreDone:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:0:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Stabilizer Done Assembly
        $$CHILD_BLOCK_START
        01:1:5
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAttachObject
                        $$CHILD_BLOCK_START
                        10:13:1:ChildTypeName
                        10:4:0:ChildPoint
                        10:1:2:-1:Parent
                        10:4:1:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:19:CameraPath
                        10:8:StabAssemblyDone:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:0:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Stabilizer Done Factory
        $$CHILD_BLOCK_START
        01:1:6
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAttachObject
                        $$CHILD_BLOCK_START
                        10:13:1:ChildTypeName
                        10:4:0:ChildPoint
                        10:1:2:-1:Parent
                        10:4:1:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:20:CameraPath
                        10:8:StabFactoryDone:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:0:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Stabilizer Power Store
        $$CHILD_BLOCK_START
        01:1:19
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Amount
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:2:StartFrame
                        10:4:5:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:StabStorePower:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Stabilizer Power Assembly
        $$CHILD_BLOCK_START
        01:1:20
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Amount
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:2:StartFrame
                        10:4:5:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:StabAssemblyPower:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Stabilizer Power Factory
        $$CHILD_BLOCK_START
        01:1:21
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Amount
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:2:StartFrame
                        10:4:5:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:StabFactoryPower:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Pounder Store
        $$CHILD_BLOCK_START
        01:1:4
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:10:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:0
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:100.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:2:StartFrame
                        10:4:6:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Pounder Assembly
        $$CHILD_BLOCK_START
        01:1:5
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:0
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:100.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:2:StartFrame
                        10:4:6:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Pounder Factory
        $$CHILD_BLOCK_START
        01:1:6
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:0
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:100.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:2:StartFrame
                        10:4:6:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Pounder Control
        $$CHILD_BLOCK_START
        01:1:7
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:0
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:100.000000:Amount
                                10:6:300.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:2:StartFrame
                        10:4:6:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Check Stabilizers (for All Four)
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
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarAdd
                                $$CHILD_BLOCK_START
                                10:6:40.000000:value
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:5:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:AllStabsDone:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:135.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Random Shaking on Disrupted
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                06:qRandomValue:Amount
                                        $$CHILD_BLOCK_START
                                        10:6:30.000000:LowerLimit
                                        10:6:70.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:6:400.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                06:qRandomValue:Amount
                                        $$CHILD_BLOCK_START
                                        10:6:30.000000:LowerLimit
                                        10:6:70.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:6:400.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                06:qRandomValue:Amount
                                        $$CHILD_BLOCK_START
                                        10:6:30.000000:LowerLimit
                                        10:6:70.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:6:400.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                06:qRandomValue:Amount
                                        $$CHILD_BLOCK_START
                                        10:6:30.000000:LowerLimit
                                        10:6:70.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:6:400.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:0.300000:LowerLimit
                                10:6:2.400000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:End Level After Camera
        $$CHILD_BLOCK_START
        01:1:3
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Are you done?
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
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:21:CameraPath
                        10:8:EndLevel:Text
                        10:1:0:3:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aEnableShip
                        $$CHILD_BLOCK_START
                        10:13:0:Ship
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:All 4 Disruptors Collected
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
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
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
                                                10:11:43:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:42:ScriptID
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarAdd
                                $$CHILD_BLOCK_START
                                10:6:60.000000:value
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:MEGA Init
        $$CHILD_BLOCK_START
        01:1:3
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:2400.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        10:6:1600.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        10:6:800.000000:value
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qUserVarValue:Shields
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:999:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:1.000000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:35.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        06:qUserVarValue:value
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:150.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:MEGA Damage?
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerWeapon:Bool
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.100000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:8:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CovLeaveMeAlone:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:MEGA State Timer Recycle
        $$CHILD_BLOCK_START
        01:1:3
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
                        05:1
                                $$CHILD_BLOCK_START
                                10:5:1:Literal
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageF
                                $$CHILD_BLOCK_START
                                10:8:Testing2:Message
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessageF
                                $$CHILD_BLOCK_START
                                10:8:Testing:Message
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
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
                                07:1:2
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        06:qObjShields:value
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:1.000000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:MEGA Cargo State Machine STALLED
        $$CHILD_BLOCK_START
        01:1:3
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:15:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:320.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:30.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:9:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CovRepaired:Message
                                $$CHILD_BLOCK_END
                        08:aObjSetShields
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                06:qUserVarValue:Shields
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aUserVarAdd
                                $$CHILD_BLOCK_START
                                10:6:45.000000:value
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:196608:Teams
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSetShields
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        06:qUserVarValue:Shields
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:10:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovGettingPummeled:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:1.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:MEGA Cargo State Machine DAMAGED
        $$CHILD_BLOCK_START
        01:1:3
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:15:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:290.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:45.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:9:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CovRepaired:Message
                                $$CHILD_BLOCK_END
                        08:aObjSetShields
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                06:qUserVarValue:Shields
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aUserVarAdd
                                $$CHILD_BLOCK_START
                                10:6:40.000000:value
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:196608:Teams
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:11:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovShutDown:Message
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        10:6:0.000000:value
                                        $$CHILD_BLOCK_END
                                08:aAISetTeam
                                        $$CHILD_BLOCK_START
                                        10:10:0:65536:Teams
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        10:6:4.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:20.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:15.000000:SparkRate
                        10:6:1.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:MEGA Cargo State Machine REBEL
        $$CHILD_BLOCK_START
        01:1:3
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:15:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:200.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:60.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:12:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CovInClear:Message
                                $$CHILD_BLOCK_END
                        08:aObjSetShields
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                06:qUserVarValue:Shields
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aUserVarAdd
                                $$CHILD_BLOCK_START
                                10:6:35.000000:value
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:196608:Teams
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:13:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovDamaged:Message
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        10:6:0.000000:value
                                        $$CHILD_BLOCK_END
                                08:aAISetTeam
                                        $$CHILD_BLOCK_START
                                        10:10:0:65536:Teams
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        10:6:3.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:MEGA Cargo State Machine SAFE
        $$CHILD_BLOCK_START
        01:1:3
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:15:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
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
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:14:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CovDanger:Message
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:200.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                10:6:200.000000:value
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:13:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CovDamaged:Message
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        10:6:0.000000:value
                                        $$CHILD_BLOCK_END
                                08:aAISetTeam
                                        $$CHILD_BLOCK_START
                                        10:10:0:65536:Teams
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        10:6:3.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aUserVarDec
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjGetDistance:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:2:-1:Object1
                                                                06:qPlayerClosest:Object2
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:2:-1:Object
                                                                        10:10:0:0:UserVar
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:300.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qScriptExecuted_DALLAS:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:11:7:ScriptID
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSub
                                                $$CHILD_BLOCK_START
                                                10:6:1.000000:value
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:150.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qScriptExecuted_DALLAS:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:11:7:ScriptID
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSub
                                                $$CHILD_BLOCK_START
                                                10:6:1.000000:value
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:35.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Radar-2 Destroyed
        $$CHILD_BLOCK_START
        01:1:22
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedRadar:Message
                        $$CHILD_BLOCK_END
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:25.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Radar-1 Destroyed
        $$CHILD_BLOCK_START
        01:1:23
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedRadar:Message
                        $$CHILD_BLOCK_END
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:25.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Ant-3 Destroyed
        $$CHILD_BLOCK_START
        01:1:24
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedAnt:Message
                        $$CHILD_BLOCK_END
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:20.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Ant-2 Destroyed
        $$CHILD_BLOCK_START
        01:1:25
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedAnt:Message
                        $$CHILD_BLOCK_END
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:20.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Ant-1 Destroyed
        $$CHILD_BLOCK_START
        01:1:26
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedAnt:Message
                        $$CHILD_BLOCK_END
                08:aUserVarAdd
                        $$CHILD_BLOCK_START
                        10:6:20.000000:value
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Transmitter Give
        $$CHILD_BLOCK_START
        01:1:27
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjType:ObjectType
                                $$CHILD_BLOCK_START
                                06:qPlayerClosest:Object
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:10:0:-1:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:10:0:4:ObjectType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Transmitter Pickup
        $$CHILD_BLOCK_START
        01:1:27
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Transmitter USE
        $$CHILD_BLOCK_START
        01:1:27
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:Transmitter:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:3:Object
                        10:6:10.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Generic Voice-4
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:15:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Generic Voice-3
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:16:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Generic Voice-2
        $$CHILD_BLOCK_START
        01:0:16
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:17:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Generic Voice-1
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:18:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
