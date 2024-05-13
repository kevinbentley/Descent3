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
// Filename:	level6.cpp
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

#define ID_CUSTOM_OBJECT_208F 0x001
#define ID_CUSTOM_OBJECT_20BE 0x002
#define ID_CUSTOM_OBJECT_206F 0x003
#define ID_CUSTOM_OBJECT_10A5 0x004
#define ID_CUSTOM_OBJECT_081D 0x005
#define ID_CUSTOM_OBJECT_081E 0x006
#define ID_CUSTOM_OBJECT_08F7 0x007
#define ID_CUSTOM_OBJECT_081C 0x008
#define ID_CUSTOM_OBJECT_081B 0x009
#define ID_CUSTOM_OBJECT_10C7 0x00a
#define ID_CUSTOM_OBJECT_18B9 0x00b
#define ID_CUSTOM_OBJECT_2051 0x00c
#define ID_CUSTOM_OBJECT_1826 0x00d
#define ID_CUSTOM_OBJECT_08FD 0x00e
#define ID_CUSTOM_OBJECT_180A 0x00f
#define ID_CUSTOM_OBJECT_216E 0x010
#define ID_CUSTOM_OBJECT_3167 0x011
#define ID_CUSTOM_OBJECT_1964 0x012
#define ID_CUSTOM_OBJECT_316A 0x013
#define ID_CUSTOM_OBJECT_216B 0x014

#define ID_TRIGGER_0015 0x015
#define ID_TRIGGER_0013 0x016
#define ID_TRIGGER_001F 0x017
#define ID_TRIGGER_0020 0x018
#define ID_TRIGGER_001C 0x019
#define ID_TRIGGER_0016 0x01a
#define ID_TRIGGER_0001 0x01b
#define ID_TRIGGER_0002 0x01c
#define ID_TRIGGER_0004 0x01d
#define ID_TRIGGER_0003 0x01e
#define ID_TRIGGER_0005 0x01f
#define ID_TRIGGER_0006 0x020
#define ID_TRIGGER_0008 0x021
#define ID_TRIGGER_0007 0x022
#define ID_TRIGGER_000A 0x023
#define ID_TRIGGER_0009 0x024
#define ID_TRIGGER_000B 0x025
#define ID_TRIGGER_000C 0x026
#define ID_TRIGGER_000E 0x027
#define ID_TRIGGER_000D 0x028
#define ID_TRIGGER_000F 0x029
#define ID_TRIGGER_0011 0x02a
#define ID_TRIGGER_0010 0x02b
#define ID_TRIGGER_001E 0x02c
#define ID_TRIGGER_001B 0x02d
#define ID_TRIGGER_0019 0x02e
#define ID_TRIGGER_001D 0x02f
#define ID_TRIGGER_001A 0x030
#define ID_TRIGGER_0018 0x031
#define ID_TRIGGER_0014 0x032
#define ID_TRIGGER_0012 0x033
#define ID_TRIGGER_0017 0x034
#define ID_TRIGGER_0025 0x035
#define ID_TRIGGER_0024 0x036
#define ID_TRIGGER_0021 0x037
#define ID_TRIGGER_0022 0x038

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

class CustomObjectScript_208F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20BE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_206F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10A5 : public BaseScript {
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

class CustomObjectScript_08F7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_081B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10C7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18B9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2051 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1826 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_180A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_216E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3167 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1964 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_316A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_216B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
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

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000C : public BaseScript {
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

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0019 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
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

class TriggerScript_0017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0025 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0024 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0021 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0022 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_010 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_010 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

/*
$$ENUM Region
0:IntroCam
1:Outside
2:Common
3:Collectors
4:Builders
5:Priests
6:Boss
$$END
*/

struct tPathNode {
  int x, y;
};

struct tForceFieldInfo {
  int room, face;
};

static bool PriestKeyInit = false;
static int PriestKeyRoomMap[5][5];
static int PriestKeySafeRoom;
static tPathNode PriestCorrectPath[17];
static int PriestSoundNodes[17];
static tForceFieldInfo ForceFields[10];
static int PriestClueSound = -1;
static int DummyObject = -1;
static int DummyDefaultPos = -1;

#define Var_ThereIsPlayerInPriestKeyPuzzle (*((int *)(&User_vars[7])))
#define Var_PriestPlayerCurrentRoom (*((int *)(&User_vars[8])))
#define Var_PriestPlayerCurrNode (*((int *)(&User_vars[9])))
#define Var_PriestPuzzleCurrSoundNode (*((int *)(&User_vars[10])))
#define Var_PriestPuzzleCompleted User_vars[11]
#define Var_PriestPuzzleGoofed User_vars[12]
#define Var_SavedObject Saved_object_handles[1]

static void PriestResetPuzzle(void);
static void PriestPlayerScrewsUp(void);
static void PriestPlayerSolvesPuzzle(void);
static void PriestTurnForceFieldOn(bool enable);
static void PriestPlaySoundAtNode(int node);
static void PriestJustEnteredPuzzle(void);
static void PriestJustExitPuzzle(void);
static void PriestInit(void);

void PriestMoveDummy(int pos) {
  if (pos == -1 || pos == -2) {
    aStoreObjectInPositionClipboard(DummyDefaultPos);
    aMoveObjectToPositionClipboard(DummyObject);
    return;
  }

  if (pos >= 0 && pos < 17) {
    aStoreObjectInPositionClipboard(PriestSoundNodes[pos]);
    aMoveObjectToPositionClipboard(DummyObject);
    return;
  }

  aStoreObjectInPositionClipboard(DummyDefaultPos);
  aMoveObjectToPositionClipboard(DummyObject);
}

/*
$$ACTION
Scripts
Call When [o:Player] Enters Priest Puzzle
aPriestKeyEnter
Call When Player Enters Priest Puzzle

$$END
*/
void aPriestKeyEnter(int Player) {
  if (Var_PriestPuzzleCompleted != 1.0f) {
    Var_ThereIsPlayerInPriestKeyPuzzle = 1;
    Var_PriestPlayerCurrentRoom = PriestKeySafeRoom;
    Var_PriestPlayerCurrNode = 0;
    Var_PriestPuzzleGoofed = 0;
    Var_SavedObject = Player;

    PriestPlaySoundAtNode(-1);
    PriestJustEnteredPuzzle();
    PriestResetPuzzle();
    PriestTurnForceFieldOn(true);
  }
}

/*
$$ACTION
Scripts
Call When [o:Player] Exits Priest Puzzle
aPriestKeyExit
Call When Player Exits Priest Puzzle

$$END
*/
void aPriestKeyExit(int Player) {
  if (Player == Var_SavedObject) {
    PriestJustExitPuzzle();
    Var_ThereIsPlayerInPriestKeyPuzzle = 0;
    Var_PriestPlayerCurrentRoom = PriestKeySafeRoom;
    Var_PriestPlayerCurrNode = 0;
    Var_PriestPuzzleGoofed = 0;
    PriestPlaySoundAtNode(-1);
    PriestTurnForceFieldOn(false);
  }
}

/*
$$ACTION
Scripts
Initialize the Priest Key Puzzle
aPriestKeyInit
Initializes the Priest Key Puzzle for the level

$$END
*/
void aPriestKeyInit(void) {
  PriestInit();

  Var_ThereIsPlayerInPriestKeyPuzzle = 0;
  Var_PriestPlayerCurrentRoom = -1;
  Var_PriestPlayerCurrNode = 0;
  Var_PriestPuzzleCompleted = 0;
  Var_PriestPuzzleGoofed = 0;
  Var_PriestPuzzleCurrSoundNode = -1;
  PriestTurnForceFieldOn(false);
}

void PriestInit(void) {
  mprintf(0, "aPriestKeyInit\n");
  PriestKeyInit = true;

  DummyObject = Scrpt_FindObjectName("Dummyflag");
  DummyDefaultPos = Scrpt_FindObjectName("Dummypos");

  // fill in sound nodes
  PriestSoundNodes[0] = Scrpt_FindObjectName("PPath1");
  PriestSoundNodes[1] = Scrpt_FindObjectName("PPath2");
  PriestSoundNodes[2] = Scrpt_FindObjectName("PPath3");
  PriestSoundNodes[3] = Scrpt_FindObjectName("PPath4");
  PriestSoundNodes[4] = Scrpt_FindObjectName("PPath5");
  PriestSoundNodes[5] = Scrpt_FindObjectName("PPath6");
  PriestSoundNodes[6] = Scrpt_FindObjectName("PPath7");
  PriestSoundNodes[7] = Scrpt_FindObjectName("PPath8");
  PriestSoundNodes[8] = Scrpt_FindObjectName("PPath9");
  PriestSoundNodes[9] = Scrpt_FindObjectName("PPath10");
  PriestSoundNodes[10] = Scrpt_FindObjectName("PPath11");
  PriestSoundNodes[11] = Scrpt_FindObjectName("PPath12");
  PriestSoundNodes[12] = Scrpt_FindObjectName("PPath13");
  PriestSoundNodes[13] = Scrpt_FindObjectName("PPath14");
  PriestSoundNodes[14] = Scrpt_FindObjectName("PPath15");
  PriestSoundNodes[15] = Scrpt_FindObjectName("PPath16");
  PriestSoundNodes[16] = Scrpt_FindObjectName("PPath17");

  PriestClueSound = Scrpt_FindSoundName("PriestIconBuzz");

  // fill in the Room Map
  PriestKeyRoomMap[0][0] = Scrpt_FindRoomName("Bad10");
  PriestKeyRoomMap[0][1] = Scrpt_FindRoomName("PPath10");
  PriestKeyRoomMap[0][2] = Scrpt_FindRoomName("PPath9");
  PriestKeyRoomMap[0][3] = Scrpt_FindRoomName("PPath8");
  PriestKeyRoomMap[0][4] = Scrpt_FindRoomName("PPath17");

  PriestKeyRoomMap[1][0] = Scrpt_FindRoomName("Bad8");
  PriestKeyRoomMap[1][1] = Scrpt_FindRoomName("PPath11");
  PriestKeyRoomMap[1][2] = Scrpt_FindRoomName("Bad9");
  PriestKeyRoomMap[1][3] = Scrpt_FindRoomName("PPath7");
  PriestKeyRoomMap[1][4] = Scrpt_FindRoomName("PPath6");

  PriestKeyRoomMap[2][0] = Scrpt_FindRoomName("Bad7");
  PriestKeyRoomMap[2][1] = Scrpt_FindRoomName("PPath12");
  PriestKeyRoomMap[2][2] = Scrpt_FindRoomName("PPath13");
  PriestKeyRoomMap[2][3] = Scrpt_FindRoomName("PPath14");
  PriestKeyRoomMap[2][4] = Scrpt_FindRoomName("PPath5");

  PriestKeyRoomMap[3][0] = Scrpt_FindRoomName("Bad5");
  PriestKeyRoomMap[3][1] = Scrpt_FindRoomName("Bad6");
  PriestKeyRoomMap[3][2] = Scrpt_FindRoomName("PPath2");
  PriestKeyRoomMap[3][3] = Scrpt_FindRoomName("PPath3");
  PriestKeyRoomMap[3][4] = Scrpt_FindRoomName("PPath4");

  PriestKeyRoomMap[4][0] = Scrpt_FindRoomName("Bad1");
  PriestKeyRoomMap[4][1] = Scrpt_FindRoomName("Bad2");
  PriestKeyRoomMap[4][2] = Scrpt_FindRoomName("PPath1");
  PriestKeyRoomMap[4][3] = Scrpt_FindRoomName("Bad3");
  PriestKeyRoomMap[4][4] = Scrpt_FindRoomName("Bad4");

  PriestKeySafeRoom = Scrpt_FindRoomName("PPathOrigin");

  PriestCorrectPath[0].x = 2;
  PriestCorrectPath[0].y = 4;
  PriestCorrectPath[1].x = 2;
  PriestCorrectPath[1].y = 3;
  PriestCorrectPath[2].x = 3;
  PriestCorrectPath[2].y = 3;
  PriestCorrectPath[3].x = 4;
  PriestCorrectPath[3].y = 3;
  PriestCorrectPath[4].x = 4;
  PriestCorrectPath[4].y = 2;
  PriestCorrectPath[5].x = 4;
  PriestCorrectPath[5].y = 1;
  PriestCorrectPath[6].x = 3;
  PriestCorrectPath[6].y = 1;
  PriestCorrectPath[7].x = 3;
  PriestCorrectPath[7].y = 0;
  PriestCorrectPath[8].x = 2;
  PriestCorrectPath[8].y = 0;
  PriestCorrectPath[9].x = 1;
  PriestCorrectPath[9].y = 0;
  PriestCorrectPath[10].x = 1;
  PriestCorrectPath[10].y = 1;
  PriestCorrectPath[11].x = 1;
  PriestCorrectPath[11].y = 2;
  PriestCorrectPath[12].x = 2;
  PriestCorrectPath[12].y = 2;
  PriestCorrectPath[13].x = 3;
  PriestCorrectPath[13].y = 2;
  PriestCorrectPath[14].x = 3;
  PriestCorrectPath[14].y = 1;
  PriestCorrectPath[15].x = 3;
  PriestCorrectPath[15].y = 0;
  PriestCorrectPath[16].x = 4;
  PriestCorrectPath[16].y = 0;

  int p_icon_room = Scrpt_FindRoomName("PriestIconRoom");
  ForceFields[0].room = p_icon_room;
  ForceFields[0].face = 0;
  ForceFields[1].room = p_icon_room;
  ForceFields[1].face = 1;
  ForceFields[2].room = p_icon_room;
  ForceFields[2].face = 2;
  ForceFields[3].room = p_icon_room;
  ForceFields[3].face = 3;
  ForceFields[4].room = p_icon_room;
  ForceFields[4].face = 4;
  ForceFields[5].room = PriestKeyRoomMap[0][0];
  ForceFields[5].face = 2;
  ForceFields[6].room = PriestKeyRoomMap[0][1];
  ForceFields[6].face = 3;
  ForceFields[7].room = PriestKeyRoomMap[0][2];
  ForceFields[7].face = 3;
  ForceFields[8].room = PriestKeyRoomMap[0][3];
  ForceFields[8].face = 3;
  ForceFields[9].room = PriestKeyRoomMap[0][4];
  ForceFields[9].face = 2;
}

/*
$$ACTION
Scripts
Handle Change Room for Priest Key Puzzle
aPriestKeyRoomChange
Call this whenever a player changes rooms

$$END
*/
void aPriestKeyRoomChange(void) {
  if (!PriestKeyInit)
    PriestInit(); // handle the case of load/save hosing us

  // Check to see if we are even doing the Puzzle
  if (Var_ThereIsPlayerInPriestKeyPuzzle == 0) {
    return; // don't even bother processesing
  }

  if (Var_PriestPuzzleCompleted > 0) {
    return; // puzzle solved
  }

  // Check to see if the Player has changed rooms, if not we can bail
  int Player_room;
  Player_room = qObjRoom(Var_SavedObject);

  if (Var_PriestPlayerCurrentRoom == Player_room) {
    return; // hasn't changed room yet
  }

  // Quick hack to see if he moved from PPathOrigin to PPath1
  if (Player_room == PriestKeyRoomMap[4][2] && Var_PriestPlayerCurrentRoom == PriestKeySafeRoom) {
    PriestPlaySoundAtNode(1);
    Var_PriestPlayerCurrNode = 0;
    Var_PriestPlayerCurrentRoom = PriestKeyRoomMap[4][2];
  }

  // What node are we currently at?
  if (Var_PriestPlayerCurrNode == -1) {
    // this means they goofed or just starting
    if (Player_room == PriestKeySafeRoom) {
      // they are back at the safe room, reset the puzzle
      PriestResetPuzzle();
    }
    return;
  }

  if (Var_PriestPlayerCurrNode == 16) {
    // this means the player finished the puzzle
    return;
  }

  if (Var_PriestPlayerCurrNode < 0 || Var_PriestPlayerCurrNode > 15) {
    // invalid
    Var_PriestPlayerCurrNode = -1;
    return;
  }

  // Create list of bad rooms, and the good room
  int BadRooms[3];
  int GoodRoom;
  int num_BadRooms = 0;
  int curr_x, curr_y;
  curr_x = PriestCorrectPath[Var_PriestPlayerCurrNode].x;
  curr_y = PriestCorrectPath[Var_PriestPlayerCurrNode].y;

  GoodRoom = PriestKeyRoomMap[PriestCorrectPath[Var_PriestPlayerCurrNode + 1].y]
                             [PriestCorrectPath[Var_PriestPlayerCurrNode + 1].x];

  // check room to left
  if (curr_x > 0) {
    int room = PriestKeyRoomMap[curr_y][curr_x - 1];
    if (room != GoodRoom) {
      BadRooms[num_BadRooms] = room;
      num_BadRooms++;
    }
  }
  // check room to right
  if (curr_x < 4) {
    int room = PriestKeyRoomMap[curr_y][curr_x + 1];
    if (room != GoodRoom) {
      BadRooms[num_BadRooms] = room;
      num_BadRooms++;
    }
  }
  // check room to top
  if (curr_y > 0) {
    int room = PriestKeyRoomMap[curr_y - 1][curr_x];
    if (room != GoodRoom) {
      BadRooms[num_BadRooms] = room;
      num_BadRooms++;
    }
  }
  // check room to bottom
  if (curr_y < 4) {
    int room = PriestKeyRoomMap[curr_y + 1][curr_x];
    if (room != GoodRoom) {
      BadRooms[num_BadRooms] = room;
      num_BadRooms++;
    }
  }

  // check to what the player moved into
  int Moved_into_good_room = -1;
  for (int i = 0; i < num_BadRooms; i++) {
    if (Player_room == BadRooms[i]) {
      // bad room!!
      mprintf(0, "PLAYER MOVED INTO BAD ROOM!\n");
      Moved_into_good_room = 0;
      break;
    }
  }

  if (Player_room == GoodRoom) {
    Moved_into_good_room = 1;
    mprintf(0, "PLAYER MOVED INTO GOOD ROOM!\n");
  }

  switch (Moved_into_good_room) {
  case -1: {
    // the player is in one of the buffer rooms
    return;
  } break;

  case 0: {
    // the player moved into a bad room
    Var_PriestPlayerCurrNode = -1;
    Var_PriestPlayerCurrentRoom = Player_room;
    PriestPlayerScrewsUp();
  } break;

  case 1: {
    // the player moved into a good room
    Var_PriestPlayerCurrNode += 1;
    Var_PriestPlayerCurrentRoom = Player_room;
    if (Var_PriestPlayerCurrNode == 16) {
      PriestPlayerSolvesPuzzle();
    } else {
      // adjust sound Position
      PriestPlaySoundAtNode(Var_PriestPlayerCurrNode + 1);
    }
  } break;
  }
}

void PriestJustExitPuzzle(void) {
  mprintf(0, "Just exited puzzle\n");
  PriestPlaySoundAtNode(-1);
}

void PriestJustEnteredPuzzle(void) {
  mprintf(0, "Just entered puzzle\n");
  PriestResetPuzzle();
}

void PriestResetPuzzle(void) {
  mprintf(0, "Reseting Priest Key Puzzle\n");
  if (Var_PriestPuzzleCompleted != 1.0f) {
    Var_PriestPlayerCurrNode = 0;
    Var_PriestPuzzleGoofed = 0;
    PriestPlaySoundAtNode(0);
  }
}

void PriestPlayerScrewsUp(void) {
  mprintf(0, "Player screwed up\n");
  PriestPlaySoundAtNode(0);
  Var_PriestPuzzleGoofed = 1.0f;
}

void PriestPlayerSolvesPuzzle(void) {
  mprintf(0, "Player solved puzzle\n");
  PriestTurnForceFieldOn(false);
  PriestPlaySoundAtNode(-1);
  Var_PriestPuzzleCompleted = 1.0f;
}

void PriestTurnForceFieldOn(bool enable) {
  for (int i = 0; i < 10; i++) {
    aPortalRenderSet((enable) ? 1 : 0, ForceFields[i].face, ForceFields[i].room, false);
  }
}

void PriestPlaySoundAtNode(int node) {
  if (node < 0 || node > 16) {
    if (Var_PriestPuzzleCurrSoundNode != -1) {
      mprintf(0, "!!!!!!!!!!!!STOPPING SOUND (%x)!!!!!!!!!!!!!!!\n", DummyObject);
      // OUTaSoundStopObj(DummyObject);
      Var_PriestPuzzleCurrSoundNode = -1;
    }
  } else {
    // not all the time...only when it needs to
    if (Var_PriestPuzzleCurrSoundNode == -1) {
      mprintf(0, "!!!!!!!!!!!!STARTING SOUND(%d,%x)!!!!!!!!!!!!!!!\n", PriestClueSound, DummyObject);
      // OUTaSoundPlayObject(PriestClueSound,DummyObject,1.0f);
    }
    Var_PriestPuzzleCurrSoundNode = node;
  }
  PriestMoveDummy(node);
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

#define NUM_DOOR_NAMES 5
static const char *const Door_names[NUM_DOOR_NAMES] = {"BossDoor", "CollectorsDoor", "BuildersDoor", "PriestHallDoor",
                                                       "PriestGalleryDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 39
static const char *const Object_names[NUM_OBJECT_NAMES] = {"DummyFlag",
                                                           "BossMovieCollider",
                                                           "BossRock01",
                                                           "BossRock02",
                                                           "BossRock03",
                                                           "BossRock04",
                                                           "BossRock05",
                                                           "BuildersKey",
                                                           "ObjectMoveCamera",
                                                           "PriestKey",
                                                           "CollectorsKey",
                                                           "Camera4CollectorsK",
                                                           "Camera4BuildersKey",
                                                           "BuilderSign",
                                                           "CollectorSign",
                                                           "PriestSign",
                                                           "PriestHallDoor",
                                                           "PriestGalleryDoor",
                                                           "FallingPlatform",
                                                           "BuildersDoor",
                                                           "CollectorsDoor",
                                                           "PlatformClutch2",
                                                           "PlatformClutch1",
                                                           "PriestPedestalCame",
                                                           "Boss",
                                                           "BPuzzRespawn",
                                                           "SlagHeap",
                                                           "TugShip",
                                                           "CrashedShip",
                                                           "BuilderPuzzUFO1",
                                                           "BuilderPuzzUFO2",
                                                           "BuilderPuzzUFO3",
                                                           "CollectorNomad2",
                                                           "CollectorsNomad1",
                                                           "VolcanoSpew",
                                                           "VolcanoSpew2",
                                                           "VolcanoSpew3",
                                                           "VolcanoSpew4",
                                                           "BossDoor"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 20
static const char *const Room_names[NUM_ROOM_NAMES] = {"EndWindyRoom",     "PriestPedestal",  "CollectorsPedestal",
                                                       "BuildersPedestal", "PlatformHitRoom", "WindTunnel1",
                                                       "WindTunnel2",      "WindTunnel3",     "BPuzz1",
                                                       "BPuzz2",           "BPuzz3",          "BPuzz4",
                                                       "BPuzz5",           "BPuzz6",          "BPuzz7",
                                                       "BPuzzEnd",         "CrashedShipRoom", "EscapeTunnelStart",
                                                       "NomadCollector2",  "CavernEntrance"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 36
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {"MusicCommon2Coll",
                                                             "MusicCommon2Build",
                                                             "WaypointInBuilders",
                                                             "BuildersHalfWay",
                                                             "MusicUseKeys2Priest",
                                                             "MusicOut2Common",
                                                             "BPuzz1in",
                                                             "BPuzz1out",
                                                             "BPuzz2in",
                                                             "BPuzz2out",
                                                             "BPuzz3in",
                                                             "BPuzz3out",
                                                             "BPuzz4in",
                                                             "BPuzz4out",
                                                             "BPuzz5in",
                                                             "BPuzz5out",
                                                             "BPuzz6in",
                                                             "BPuzz6out",
                                                             "BPuzz7in",
                                                             "BPuzz7out",
                                                             "BuildersPuzzleMessa",
                                                             "ExitPriestPuzzle",
                                                             "EnterPriestPuzzle",
                                                             "MusicPriest2Boss",
                                                             "MusicUseKeys2Build",
                                                             "MusicUseKeys2Coll",
                                                             "MusicPriest2UseKeys",
                                                             "MusicBuild2UseKeys",
                                                             "MusicColl2UseKeys",
                                                             "MusicColl2Common",
                                                             "MusicBuild2Common",
                                                             "MusicCommon2Out",
                                                             "TurnPriestNomadsOn",
                                                             "TurnOffPriestNomads",
                                                             "BuildersPuzzHint",
                                                             "BuildersPuzzHint2"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 8
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "Powerup pickup",         "DoorIsLocked", "expMissileTearing1", "AmbBigUnlock",
    "You don't have it BEEP", "Lev5Goal",     "Lev5GoalFail",       "DefaultBuildingExplode"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 1
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffect1"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 20
static const char *const Path_names[NUM_PATH_NAMES] = {
    "BossCinematicPath", "IntroCameraPath",    "IntroShip",           "TugPathIn",        "TugPathIn2",
    "TugEscapePath",     "TugEscapeCamera1",   "TugShipEscape2",      "TugEscapeCamera2", "PlayerEscapeCamera",
    "PlayerEscapePath",  "NomadPriestHall",    "NomadPriestHallRamp", "NomadMainRoom1",   "NomadMainRoom2",
    "BuildersPuzzPath",  "BuilderPuzzCorrect", "CollectorNomad2",     "CollectorNomad1",  "NomadPriestGallery"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 5
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Boss Room Matcen 1", "Boss Room Matcen 2", "NomadMainRoom1",
                                                           "NomadPriestHall", "NomadPriestGallery"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 7
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Find the Builders' Icon", "Find the Priest's Icon",    "Find the Collectors' Icon", "Use the icons",
    "Use the Priest's Icon",   "Find the crashed CED ship", "Enter the Nomad Caverns"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 38
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"FirstPickupBuilder",
                                                             "FirstPickupPriest",
                                                             "FirstPickupCollector",
                                                             "InvGame",
                                                             "InvHUD",
                                                             "PlaceCollectorsKey",
                                                             "KeyAlreadyThere",
                                                             "YoucantUseKeyHere",
                                                             "PlaceBuildersKey",
                                                             "BuilderCollectorsCorrectlyPlaced",
                                                             "PriestHallDoorLocked",
                                                             "PriestGalleryDoorLocked",
                                                             "BuildersDoorMessage",
                                                             "ThisDoorDoesNotAnswer",
                                                             "CollectorsDoorMessage",
                                                             "PriestKeyCorrectlyPlaced",
                                                             "PlacePriestKey",
                                                             "BossIntroductionText",
                                                             "IntroLevelMessage",
                                                             "XsecsOntheClock",
                                                             "BuildersPuzzMessage",
                                                             "BuildersPuzzMessage2",
                                                             "Builders3secondsleft",
                                                             "BuildersTimerExpired",
                                                             "PriestPuzzleEnter",
                                                             "PriestPuzzleSolved",
                                                             "PriestPuzzleGoofed",
                                                             "TugMessage1",
                                                             "TugMessage2",
                                                             "TugMessageStart",
                                                             "TugStartMessage2",
                                                             "TugMessageShipPickUp",
                                                             "TugMessage5",
                                                             "TugMessage4",
                                                             "TugMessage6",
                                                             "BLANK",
                                                             "Test",
                                                             "BuildersPuzzhint"};
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
    strcpy(filename, "level6.msg");
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
  case ID_CUSTOM_OBJECT_208F:
    return new CustomObjectScript_208F;
    break;
  case ID_CUSTOM_OBJECT_20BE:
    return new CustomObjectScript_20BE;
    break;
  case ID_CUSTOM_OBJECT_206F:
    return new CustomObjectScript_206F;
    break;
  case ID_CUSTOM_OBJECT_10A5:
    return new CustomObjectScript_10A5;
    break;
  case ID_CUSTOM_OBJECT_081D:
    return new CustomObjectScript_081D;
    break;
  case ID_CUSTOM_OBJECT_081E:
    return new CustomObjectScript_081E;
    break;
  case ID_CUSTOM_OBJECT_08F7:
    return new CustomObjectScript_08F7;
    break;
  case ID_CUSTOM_OBJECT_081C:
    return new CustomObjectScript_081C;
    break;
  case ID_CUSTOM_OBJECT_081B:
    return new CustomObjectScript_081B;
    break;
  case ID_CUSTOM_OBJECT_10C7:
    return new CustomObjectScript_10C7;
    break;
  case ID_CUSTOM_OBJECT_18B9:
    return new CustomObjectScript_18B9;
    break;
  case ID_CUSTOM_OBJECT_2051:
    return new CustomObjectScript_2051;
    break;
  case ID_CUSTOM_OBJECT_1826:
    return new CustomObjectScript_1826;
    break;
  case ID_CUSTOM_OBJECT_08FD:
    return new CustomObjectScript_08FD;
    break;
  case ID_CUSTOM_OBJECT_180A:
    return new CustomObjectScript_180A;
    break;
  case ID_CUSTOM_OBJECT_216E:
    return new CustomObjectScript_216E;
    break;
  case ID_CUSTOM_OBJECT_3167:
    return new CustomObjectScript_3167;
    break;
  case ID_CUSTOM_OBJECT_1964:
    return new CustomObjectScript_1964;
    break;
  case ID_CUSTOM_OBJECT_316A:
    return new CustomObjectScript_316A;
    break;
  case ID_CUSTOM_OBJECT_216B:
    return new CustomObjectScript_216B;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_0025:
    return new TriggerScript_0025;
    break;
  case ID_TRIGGER_0024:
    return new TriggerScript_0024;
    break;
  case ID_TRIGGER_0021:
    return new TriggerScript_0021;
    break;
  case ID_TRIGGER_0022:
    return new TriggerScript_0022;
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
  case ID_CUSTOM_OBJECT_208F:
    delete ((CustomObjectScript_208F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20BE:
    delete ((CustomObjectScript_20BE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_206F:
    delete ((CustomObjectScript_206F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10A5:
    delete ((CustomObjectScript_10A5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081D:
    delete ((CustomObjectScript_081D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081E:
    delete ((CustomObjectScript_081E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08F7:
    delete ((CustomObjectScript_08F7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081C:
    delete ((CustomObjectScript_081C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_081B:
    delete ((CustomObjectScript_081B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10C7:
    delete ((CustomObjectScript_10C7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18B9:
    delete ((CustomObjectScript_18B9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2051:
    delete ((CustomObjectScript_2051 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1826:
    delete ((CustomObjectScript_1826 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FD:
    delete ((CustomObjectScript_08FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_180A:
    delete ((CustomObjectScript_180A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_216E:
    delete ((CustomObjectScript_216E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3167:
    delete ((CustomObjectScript_3167 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1964:
    delete ((CustomObjectScript_1964 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_316A:
    delete ((CustomObjectScript_316A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_216B:
    delete ((CustomObjectScript_216B *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_0025:
    delete ((TriggerScript_0025 *)ptr);
    break;
  case ID_TRIGGER_0024:
    delete ((TriggerScript_0024 *)ptr);
    break;
  case ID_TRIGGER_0021:
    delete ((TriggerScript_0021 *)ptr);
    break;
  case ID_TRIGGER_0022:
    delete ((TriggerScript_0022 *)ptr);
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
  case ID_CUSTOM_OBJECT_208F:
  case ID_CUSTOM_OBJECT_20BE:
  case ID_CUSTOM_OBJECT_206F:
  case ID_CUSTOM_OBJECT_10A5:
  case ID_CUSTOM_OBJECT_081D:
  case ID_CUSTOM_OBJECT_081E:
  case ID_CUSTOM_OBJECT_08F7:
  case ID_CUSTOM_OBJECT_081C:
  case ID_CUSTOM_OBJECT_081B:
  case ID_CUSTOM_OBJECT_10C7:
  case ID_CUSTOM_OBJECT_18B9:
  case ID_CUSTOM_OBJECT_2051:
  case ID_CUSTOM_OBJECT_1826:
  case ID_CUSTOM_OBJECT_08FD:
  case ID_CUSTOM_OBJECT_180A:
  case ID_CUSTOM_OBJECT_216E:
  case ID_CUSTOM_OBJECT_3167:
  case ID_CUSTOM_OBJECT_1964:
  case ID_CUSTOM_OBJECT_316A:
  case ID_CUSTOM_OBJECT_216B:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0025:
  case ID_TRIGGER_0024:
  case ID_TRIGGER_0021:
  case ID_TRIGGER_0022:
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
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[29] && trigger_face == Trigger_faces[29])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[30] && trigger_face == Trigger_faces[30])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[31] && trigger_face == Trigger_faces[31])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[32] && trigger_face == Trigger_faces[32])
    return ID_TRIGGER_0025;

  if (trigger_room == Trigger_rooms[33] && trigger_face == Trigger_faces[33])
    return ID_TRIGGER_0024;

  if (trigger_room == Trigger_rooms[34] && trigger_face == Trigger_faces[34])
    return ID_TRIGGER_0021;

  if (trigger_room == Trigger_rooms[35] && trigger_face == Trigger_faces[35])
    return ID_TRIGGER_0022;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[20];
  static int cust_id_list[20] = {
      ID_CUSTOM_OBJECT_208F, ID_CUSTOM_OBJECT_20BE, ID_CUSTOM_OBJECT_206F, ID_CUSTOM_OBJECT_10A5,
      ID_CUSTOM_OBJECT_081D, ID_CUSTOM_OBJECT_081E, ID_CUSTOM_OBJECT_08F7, ID_CUSTOM_OBJECT_081C,
      ID_CUSTOM_OBJECT_081B, ID_CUSTOM_OBJECT_10C7, ID_CUSTOM_OBJECT_18B9, ID_CUSTOM_OBJECT_2051,
      ID_CUSTOM_OBJECT_1826, ID_CUSTOM_OBJECT_08FD, ID_CUSTOM_OBJECT_180A, ID_CUSTOM_OBJECT_216E,
      ID_CUSTOM_OBJECT_3167, ID_CUSTOM_OBJECT_1964, ID_CUSTOM_OBJECT_316A, ID_CUSTOM_OBJECT_216B};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[7];
  cust_handle_list[1] = Object_handles[9];
  cust_handle_list[2] = Object_handles[10];
  cust_handle_list[3] = Object_handles[13];
  cust_handle_list[4] = Object_handles[16];
  cust_handle_list[5] = Object_handles[17];
  cust_handle_list[6] = Object_handles[18];
  cust_handle_list[7] = Object_handles[19];
  cust_handle_list[8] = Object_handles[20];
  cust_handle_list[9] = Object_handles[21];
  cust_handle_list[10] = Object_handles[22];
  cust_handle_list[11] = Object_handles[1];
  cust_handle_list[12] = Object_handles[24];
  cust_handle_list[13] = Object_handles[27];
  cust_handle_list[14] = Object_handles[38];
  cust_handle_list[15] = Object_handles[2];
  cust_handle_list[16] = Object_handles[3];
  cust_handle_list[17] = Object_handles[4];
  cust_handle_list[18] = Object_handles[5];
  cust_handle_list[19] = Object_handles[6];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 20;
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

    // Script 009: Collectors & Builders Key Correctly Placed
    if ((ScriptActionCtr_009 < 1) &&
        ((qObjRoom(Object_handles[10]) == Room_indexes[2]) && (qObjRoom(Object_handles[7]) == Room_indexes[3]))) {
      aShowHUDMessage(Message_strings[9]);
      aUserVarSet(1, 1.000000f);
      aGoalCompleted(Goal_indexes[3], 1);
      aObjSetMovementType(Object_handles[7], 0);
      aObjSetMovementType(Object_handles[10], 0);
      aDoorLockUnlock(0, Door_handles[3]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 014: Priest Key Correctly Placed
    if ((ScriptActionCtr_014 < 1) && (qObjRoom(Object_handles[9]) == Room_indexes[1])) {
      aShowHUDMessage(Message_strings[15]);
      aGoalCompleted(Goal_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 046: Priest Key Room Change Handler
    if (1) {
      aPriestKeyRoomChange();

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }

    // Script 049: PriestPuzzleSolved
    if ((ScriptActionCtr_049 < 1) && (qUserVarValue(11) == 1.000000f)) {
      aShowHUDMessage(Message_strings[25]);
      aSoundPlay2D(Sound_indexes[5], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 050: Priest Puzzle, Player Goofed
    if (qUserVarValue(12) == 1.000000f) {
      aUserVarSet(12, 0.000000f);
      aShowHUDMessage(Message_strings[26]);
      aSoundPlay2D(Sound_indexes[6], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }

    // Script 102: CollectorsNomad2
    if (qRoomHasPlayer(Room_indexes[18]) == 1) {
      aAIGoalFollowPathSimple(Object_handles[32], Path_indexes[17], 1052928, 7, 3);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }

    // Script 101: PlayerEntersTheCaverns
    if (qRoomHasPlayer(Room_indexes[19]) == 1) {
      aGoalCompleted(Goal_indexes[6], 1);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 006: LevelStart
    if (1) {
      aUserVarSet(0, 1.000000f);
      aUserVarSet(14, 0.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aUserVarSet(3, 0.000000f);
      aUserVarSet(4, 0.000000f);
      aUserVarSet(5, 0.000000f);
      aPriestKeyInit();
      aObjGhostSet(1, Object_handles[0]);
      aUserVarSet(13, 0.000000f);
      aRoomSetWind(Room_indexes[0], -0.170000f, -0.966000f, -0.192000f, 30.000000f);
      aObjHide(Object_handles[1]);
      aObjSetMovementType(Object_handles[2], 0);
      aObjSetMovementType(Object_handles[3], 0);
      aObjSetMovementType(Object_handles[4], 0);
      aObjSetMovementType(Object_handles[5], 0);
      aObjSetMovementType(Object_handles[6], 0);
      aMatcenSetEnableState(0, Matcen_indexes[0]);
      aMatcenSetEnableState(0, Matcen_indexes[1]);
      aDoorLockUnlock(1, Door_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 020: InitWindTunnel1
    if (1) {
      aRoomSetWind(Room_indexes[5], 0.633000f, 0.291000f, 0.718000f, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 021: InitWindTunnel2
    if (1) {
      aRoomSetWind(Room_indexes[6], 0.633000f, 0.291000f, 0.718000f, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 022: InitWindTunnel3
    if (1) {
      aRoomSetWind(Room_indexes[7], 0.633000f, 0.291000f, 0.718000f, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 025: IntroCamera
    if (1) {
      aMusicSetRegionAll(1);
      aCinematicIntro(Path_indexes[1], Message_strings[18], Object_handles[18], Path_indexes[2], 15.000000f);
      aSetLevelTimer(40.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 028: BuildersDisableFirstForcefield
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[8], 1);
      aPortalRenderSet(0, 1, Room_indexes[8], 1);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }

    // Script 065: MusicOutsideRegion
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }

    // Script 094: TurnOnSpew
    if ((ScriptActionCtr_094 < 1) && (1)) {
      aTurnOnSpew(Object_handles[34], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 1000000000.000000f,
                  4.000000f, 20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[35], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 1000000000.000000f,
                  4.000000f, 20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[36], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 1000000000.000000f,
                  4.000000f, 20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[37], -1, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 1000000000.000000f,
                  4.000000f, 20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 088: Inventory Reminder Timer Goes Off
    if ((ScriptActionCtr_088 < 1) && (event_data->id == 10)) {
      aAddGameMessage(Message_strings[3], Message_strings[4]);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }

    // Script 007: LevelKeyTimer
    if (event_data->id == 0) {
      aUserVarSet(0, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 091: PlatformTimer
    if ((ScriptActionCtr_091 < 1) && (event_data->id == 11)) {
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aMiscViewerShake(40.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }

    // Script 092: Turn Off Platform
    if ((ScriptActionCtr_092 < 1) && (event_data->id == 12)) {
      aObjSetMovementType(Object_handles[18], 0);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }

    // Script 024: BossCameraMove
    if (event_data->id == 1) {
      aCinematicSimple(Path_indexes[0], Message_strings[17], Object_handles[24], 14.000000f, 1);
      aDoorSetPos(Door_handles[0], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;

      return CONTINUE_DEFAULT;
    }

    // Script 044: BuildersWarningBeep
    if ((event_data->id == 4) && (qUserVarValue(3) != 1.000000f)) {
      aShowHUDMessageObj(Message_strings[22], qObjSavedHandle(0));
      aSoundPlay2DObj(Sound_indexes[4], qObjSavedHandle(0), 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 045: BuildersTimerExpires
    if (event_data->id == 3) {
      aUserVarSet(5, 0.000000f);
      if (qHasObjectInInventory(qObjSavedHandle(0), Object_handles[7]) == 0) {
        aShowHUDMessageObj(Message_strings[23], qObjSavedHandle(0));
        aPortalRenderSet(0, 0, Room_indexes[8], 1);
        aPortalRenderSet(0, 1, Room_indexes[8], 1);
        aPortalRenderSet(1, 0, Room_indexes[9], 1);
        aPortalRenderSet(1, 1, Room_indexes[9], 1);
        aPortalRenderSet(1, 0, Room_indexes[10], 1);
        aPortalRenderSet(1, 1, Room_indexes[10], 1);
        aPortalRenderSet(1, 0, Room_indexes[11], 1);
        aPortalRenderSet(1, 1, Room_indexes[11], 1);
        aPortalRenderSet(1, 0, Room_indexes[12], 1);
        aPortalRenderSet(1, 1, Room_indexes[12], 1);
        aPortalRenderSet(1, 0, Room_indexes[13], 1);
        aPortalRenderSet(1, 1, Room_indexes[13], 1);
        aPortalRenderSet(1, 0, Room_indexes[14], 1);
        aPortalRenderSet(1, 1, Room_indexes[14], 1);
        aPortalRenderSet(1, 0, Room_indexes[15], 1);
        aPortalRenderSet(1, 1, Room_indexes[15], 1);
        aUserVarSet(6, 0.000000f);
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[8]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[9]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[10]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[11]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[12]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[13]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[14]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qObjRoom(qObjSavedHandle(0)) == Room_indexes[15]) {
          aUserVarSet(6, 1.000000f);
        }
        if (qUserVarValueInt(6) == 1) {
          aStoreObjectInPositionClipboard(Object_handles[25]);
          aFadeAndMovePlayer(qObjSavedHandle(0));
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 055: MessageTugWarnsPlayer
    if ((ScriptActionCtr_055 < 1) && (event_data->id == 6)) {
      aSoundPlaySteaming("VoxL06SpecificC.osf", 1.000000f);
      aShowHUDMessage(Message_strings[27]);
      aShowHUDMessage(Message_strings[28]);
      aGoalCompleted(Goal_indexes[5], 1);
      aMatcenSetEnableState(1, Matcen_indexes[0]);
      aMatcenSetEnableState(1, Matcen_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }

    // Script 054: StartTugMessage
    if ((ScriptActionCtr_054 < 1) && (event_data->id == 5)) {
      aSoundPlaySteaming("VoxL06SpecificA.osf", 1.000000f);
      aShowHUDMessage(Message_strings[29]);
      aShowHUDMessage(Message_strings[30]);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 057: DropForcefieldsOnFakeDeath
    if ((ScriptActionCtr_057 < 1) && (event_data->id == 7)) {
      aPortalRenderSet(0, 0, Room_indexes[16], 1);
      aPortalRenderSet(0, 0, Room_indexes[17], 1);
      aSoundPlaySteaming("VoxL06SpecificE.osf", 1.000000f);
      aShowHUDMessage(Message_strings[31]);
      aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[3], 4352, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }

    // Script 067: DoStuffWhenBossDies
    if ((ScriptActionCtr_067 < 1) && ((event_data->id == 9) && ((ScriptActionCtr_085 > 0) == true))) {
      aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[5], 1048832, 3, 3);
      aEnableShip("Phoenix");
      aCinematicSimple(Path_indexes[6], Message_strings[35], Object_handles[27], 18.000000f, 1);
      aRoomSetWind(Room_indexes[0], 0.000000f, 0.000000f, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 104: KillNomadPriestHall
    if (event_data->goal_uid == 6) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }

    // Script 082: KillNomadMainRoom
    if (event_data->goal_uid == 2) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }

    // Script 106: KillNomadCollector2
    if (event_data->goal_uid == 7) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }

    // Script 110: KillNomadPriestGallery
    if (event_data->goal_uid == 8) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 103: NomadPriestHall
    if (event_data->id == Matcen_indexes[3]) {
      if (qRandomValue(0.000000f, 1.000000f) < 0.500000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[11], 4352, 6, 3);
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[12], 4352, 6, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }

    // Script 027: NomadMainRoomMatcen1
    if (event_data->id == Matcen_indexes[2]) {
      if (qRandomValue(0.000000f, 1.000000f) < 0.500000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[13], 4352, 2, 3);
      } else {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[14], 4352, 2, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 109: NomadPriestGallery
    if (event_data->id == Matcen_indexes[4]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[19], 4352, 8, 3);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 010: Voice Over Intro
    if ((ScriptActionCtr_010 < 1) && (1)) {
      aSoundPlaySteaming("VoxL06StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_208F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: CollideWithBuildersKey
    if ((qObjIsPlayer(event_data->it_handle) == 1) &&
        ((qUserVarValue(0) == 1.000000f) && (qUserVarValue(1) != 1.000000f))) {
      if (qUserVarValue(3) == 0.000000f) {
        aShowHUDMessage(Message_strings[0]);
        aGoalCompleted(Goal_indexes[0], 1);
        aCancelTimer(3);
      }
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aStoreObjectInPositionClipboard(Object_handles[8]);
      aMoveObjectToPositionClipboard(data->me_handle);
      aUserVarSet(3, 1.000000f);
      aDoorLockUnlock(0, Door_handles[1]);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aSetWaypoint(2);
      if ((qUserVarValueInt(3) == 1) && (qUserVarValueInt(2) == 1)) {
        aSetLevelTimer(13.000000f, 10);
      }

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 005: UseBuildersKey
    if (1) {
      if ((qObjRoom(event_data->it_handle) == Room_indexes[2]) ||
          (qObjRoom(event_data->it_handle) == Room_indexes[3])) {
        if (qObjRoom(event_data->it_handle) == Room_indexes[2]) {
          if (qObjRoom(Object_handles[10]) != Room_indexes[2]) {
            aObjGhostSet(0, data->me_handle);
            aStoreObjectInPositionClipboard(Object_handles[11]);
            aMoveObjectToPositionClipboard(data->me_handle);
            aUserVarSet(0, 0.000000f);
            aSetLevelTimer(3.000000f, 0);
            aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
          } else {
            aObjGhostSet(0, data->me_handle);
            aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            aShowHUDMessageObj(Message_strings[6], event_data->it_handle);
            aStoreObjectInPositionClipboard(Object_handles[8]);
            aMoveObjectToPositionClipboard(data->me_handle);
          }
        } else {
          if (qObjRoom(Object_handles[10]) != Room_indexes[3]) {
            aObjGhostSet(0, data->me_handle);
            aStoreObjectInPositionClipboard(Object_handles[12]);
            aMoveObjectToPositionClipboard(data->me_handle);
            aUserVarSet(0, 0.000000f);
            aSetLevelTimer(3.000000f, 0);
            aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
          } else {
            aObjGhostSet(0, data->me_handle);
            aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            aShowHUDMessageObj(Message_strings[6], event_data->it_handle);
            aStoreObjectInPositionClipboard(Object_handles[8]);
            aMoveObjectToPositionClipboard(data->me_handle);
          }
        }
      } else {
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
        aShowHUDMessageObj(Message_strings[7], event_data->it_handle);
        aStoreObjectInPositionClipboard(Object_handles[8]);
        aMoveObjectToPositionClipboard(data->me_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20BE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: CollideWithPriestKey
    if ((qObjIsPlayer(event_data->it_handle) == 1) && (qObjRoom(Object_handles[9]) != Room_indexes[1])) {
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aStoreObjectInPositionClipboard(Object_handles[8]);
      aMoveObjectToPositionClipboard(data->me_handle);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aShowHUDMessage(Message_strings[1]);
      aGoalCompleted(Goal_indexes[1], 1);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 019: UsePriestKey
    if (1) {
      if (qObjRoom(event_data->it_handle) == Room_indexes[1]) {
        aObjGhostSet(0, data->me_handle);
        aStoreObjectInPositionClipboard(Object_handles[23]);
        aMoveObjectToPositionClipboard(data->me_handle);
        aShowHUDMessageObj(Message_strings[16], event_data->it_handle);
        aDoorLockUnlock(0, Door_handles[4]);
      } else {
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
        aShowHUDMessageObj(Message_strings[7], event_data->it_handle);
        aStoreObjectInPositionClipboard(Object_handles[8]);
        aMoveObjectToPositionClipboard(data->me_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_206F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 000: CollideWithCollectorsKey
    if ((qObjIsPlayer(event_data->it_handle) == 1) &&
        ((qUserVarValue(0) == 1.000000f) && (qUserVarValue(1) != 1.000000f))) {
      if (qUserVarValueInt(2) == 0) {
        aShowHUDMessage(Message_strings[2]);
        aGoalCompleted(Goal_indexes[2], 1);
      }
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aStoreObjectInPositionClipboard(Object_handles[8]);
      aMoveObjectToPositionClipboard(data->me_handle);
      aUserVarSet(2, 1.000000f);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aDoorLockUnlock(0, Door_handles[2]);
      aSetWaypoint(1);
      if ((qUserVarValueInt(2) == 1) && (qUserVarValueInt(3) == 1)) {
        aSetLevelTimer(13.000000f, 10);
      }

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;

      return CONTINUE_DEFAULT;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 004: UseCollectorsKey
    if (1) {
      if ((qObjRoom(event_data->it_handle) == Room_indexes[2]) ||
          (qObjRoom(event_data->it_handle) == Room_indexes[3])) {
        if (qObjRoom(event_data->it_handle) == Room_indexes[2]) {
          if (qObjRoom(Object_handles[7]) != Room_indexes[2]) {
            aObjGhostSet(0, data->me_handle);
            aStoreObjectInPositionClipboard(Object_handles[11]);
            aMoveObjectToPositionClipboard(data->me_handle);
            aUserVarSet(0, 0.000000f);
            aSetLevelTimer(3.000000f, 0);
            aShowHUDMessageObj(Message_strings[5], event_data->it_handle);
          } else {
            aObjGhostSet(0, data->me_handle);
            aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            aShowHUDMessageObj(Message_strings[6], event_data->it_handle);
            aStoreObjectInPositionClipboard(Object_handles[8]);
            aMoveObjectToPositionClipboard(data->me_handle);
          }
        } else {
          if (qObjRoom(Object_handles[7]) != Room_indexes[3]) {
            aObjGhostSet(0, data->me_handle);
            aStoreObjectInPositionClipboard(Object_handles[12]);
            aMoveObjectToPositionClipboard(data->me_handle);
            aUserVarSet(0, 0.000000f);
            aSetLevelTimer(3.000000f, 0);
            aShowHUDMessageObj(Message_strings[5], event_data->it_handle);
          } else {
            aObjGhostSet(0, data->me_handle);
            aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            aShowHUDMessageObj(Message_strings[6], event_data->it_handle);
            aStoreObjectInPositionClipboard(Object_handles[8]);
            aMoveObjectToPositionClipboard(data->me_handle);
          }
        }
      } else {
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
        aShowHUDMessageObj(Message_strings[7], event_data->it_handle);
        aStoreObjectInPositionClipboard(Object_handles[8]);
        aMoveObjectToPositionClipboard(data->me_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10A5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 087: LightningTest
    if (0 == true) {
      aLightningCreate(Object_handles[14], Object_handles[15], 10.000000f, 4.000000f, 1, Texture_indexes[0], 0.300000f,
                       1, 255, 255, 255, 0);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Player tries to open Priest Hall door
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) {
      if ((qObjRoom(Object_handles[10]) == Room_indexes[2]) && (qObjRoom(Object_handles[7]) == Room_indexes[3])) {
        aDoorActivate(Door_handles[3]);
      } else {
        aShowHUDMessageObj(Message_strings[10], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Player tries to open Priest Gallery door
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) {
      if (qObjRoom(Object_handles[9]) == Room_indexes[1]) {
        aDoorActivate(Door_handles[4]);
      } else {
        aShowHUDMessageObj(Message_strings[11], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08F7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 002: DisablePlatformMovement
    if (1) {
      aObjGravityEnable(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 001: DoStuffWhenPlatformHits
    if ((ScriptActionCtr_001 < 1) && (qObjRoom(data->me_handle) == Room_indexes[4])) {
      aSetLevelTimer(0.150000f, 11);
      aSetLevelTimer(2.000000f, 12);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: BuildersDoorMessage
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) {
      if ((ScriptActionCtr_000 > 0) == 1) {
        aDoorLockUnlock(0, Door_handles[2]);
        aShowHUDMessageObj(Message_strings[12], event_data->it_handle);
        aDoorActivate(data->me_handle);
      } else {
        aShowHUDMessageObj(Message_strings[13], event_data->it_handle);
        aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_081B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: CollectorsDoorMessage
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) {
      if ((ScriptActionCtr_003 > 0) == 1) {
        aDoorLockUnlock(0, Door_handles[1]);
        aShowHUDMessageObj(Message_strings[14], event_data->it_handle);
        aDoorActivate(data->me_handle);
      } else {
        aShowHUDMessageObj(Message_strings[13], event_data->it_handle);
        aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);
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

int16_t CustomObjectScript_10C7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 016: PlatformClutch2Dies
    if ((ScriptActionCtr_016 < 1) && (1)) {
      aUserVarInc(4);
      if (qUserVarValueInt(4) == 2) {
        aObjGravityEnable(1, Object_handles[18]);
        aSoundPlay2D(Sound_indexes[2], 1.000000f);
        aTurnOnSpew(Object_handles[18], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 40.000000f,
                    4.000000f, 20.000000f, 1, -1);
        aTurnOnSpew(Object_handles[18], 1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 40.000000f,
                    4.000000f, 20.000000f, 1, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18B9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 015: PlatformClutch1Dies
    if ((ScriptActionCtr_015 < 1) && (1)) {
      aUserVarInc(4);
      if (qUserVarValueInt(4) == 2) {
        aObjGravityEnable(1, Object_handles[18]);
        aSoundPlay2D(Sound_indexes[2], 1.000000f);
        aTurnOnSpew(Object_handles[18], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                    4.000000f, 20.000000f, 1, -1);
        aTurnOnSpew(Object_handles[18], 1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f,
                    4.000000f, 20.000000f, 1, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2051::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: BossCameraTimer
    if ((ScriptActionCtr_023 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetLevelTimer(1.000000f, 1);
      aSoundPlay2DObj(Sound_indexes[3], event_data->it_handle, 1.000000f);
      aDoorLockUnlock(0, Door_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1826::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 051: BlowUpSlagHeap
    if ((ScriptActionCtr_051 < 1) && (qObjAnimFrame(Object_handles[24]) != 126.000000f)) {
      aObjDestroy(Object_handles[26]);
      aSoundPlay2D(Sound_indexes[7], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }

    // Script 056: BossDoesFakeDeath
    if ((ScriptActionCtr_056 < 1) && (qObjAnimFrame(data->me_handle) == 210.000000f)) {
      aSetLevelTimer(0.500000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }

    // Script 053: BossNoLongerDead
    if ((ScriptActionCtr_053 < 1) && (qObjAnimFrame(data->me_handle) == 210.000000f)) {
      aUserVarSet(13, 1.000000f);
      aMatcenSetEnableState(0, Matcen_indexes[0]);
      aMatcenSetEnableState(0, Matcen_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 066: BossNoLongerDeadPart2
    if ((ScriptActionCtr_066 < 1) &&
        ((qObjAnimFrame(Object_handles[24]) != 210.000000f) && (qUserVarValueInt(13) == 1))) {
      aSoundPlaySteaming("VoxL06SpecificF.osf", 1.000000f);
      aShowHUDMessage(Message_strings[33]);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }

    // Script 058: BossRealDeath
    if ((ScriptActionCtr_058 < 1) && (qObjAnimFrame(Object_handles[24]) == 350.000000f)) {
      aSoundPlaySteaming("VoxL06EndLevel.osf", 1.000000f);
      aSetLevelTimer(4.000000f, 9);
      aShowHUDMessage(Message_strings[34]);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 026: MessagePlayerSeesBoss
    if ((ScriptActionCtr_026 < 1) && (1)) {
      aSetLevelTimer(3.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 084: TugPicksUpShip1
    if ((ScriptActionCtr_084 < 1) && (event_data->goal_uid == 0)) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[4], 1048832, 5, 3);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }

    // Script 085: TugPicksUpShip2
    if ((ScriptActionCtr_085 < 1) && (event_data->goal_uid == 5)) {
      aAIGoalPickUpObject(data->me_handle, 0, Object_handles[28], 0, 1, 3, 4352, 1);
      aSoundPlaySteaming("VoxL06SpecificG.osf", 1.000000f);
      aShowHUDMessage(Message_strings[32]);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }

    // Script 086: TugEscapeCamera2
    if ((ScriptActionCtr_086 < 1) && (event_data->goal_uid == 3)) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[7], 1048832, 4, 3);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 068: Start2ndPartCinematicAlt
    if ((ScriptActionCtr_068 < 2) && (1)) {
      if (ScriptActionCtr_068 == 0) {
        aCinematicSimple(Path_indexes[8], Message_strings[35], data->me_handle, 10.000000f, 1);
      }
      if (ScriptActionCtr_068 == 1) {
        aStartEndlevelSequencePath(Path_indexes[9], Path_indexes[10], 14.000000f, Message_strings[35]);
        aShowHUDMessage(Message_strings[36]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_180A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 095: BossDoorLocked
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1) {
      aShowHUDMessage(Message_strings[35]);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_216E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 097: DroppingRocks01
    if ((ScriptActionCtr_097 < 1) && (qObjectPosition(data->me_handle, 1) < -490.000000f)) {
      aMiscViewerShake(40.000000f);
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aObjFireWeapon("TubbsHitBlast", -1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3167::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 096: DroppingRocks02
    if ((ScriptActionCtr_096 < 1) && (qObjectPosition(data->me_handle, 1) < -490.000000f)) {
      aMiscViewerShake(40.000000f);
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aObjFireWeapon("TubbsHitBlast", -1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1964::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 100: DroppingRocks03
    if ((ScriptActionCtr_100 < 1) && (qObjectPosition(data->me_handle, 1) < -490.000000f)) {
      aMiscViewerShake(40.000000f);
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aObjFireWeapon("TubbsHitBlast", -1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_316A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 099: DroppingRocks04
    if ((ScriptActionCtr_099 < 1) && (qObjectPosition(data->me_handle, 1) < -490.000000f)) {
      aMiscViewerShake(40.000000f);
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aObjFireWeapon("TubbsHitBlast", -1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_216B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 098: DroppingRocks05
    if ((ScriptActionCtr_098 < 1) && (qObjectPosition(data->me_handle, 1) < -490.000000f)) {
      aMiscViewerShake(40.000000f);
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aObjFireWeapon("TubbsHitBlast", -1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: WaypointCollectorsOrigin
    if ((ScriptActionCtr_061 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetWaypoint(6);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }

    // Script 077: Music-Collector2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }

    // Script 093: CollectorsNomad1
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aAIGoalFollowPathSimple(Object_handles[33], Path_indexes[18], 1052928, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: WaypointBuildersOrigin
    if ((ScriptActionCtr_060 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetWaypoint(5);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 078: Music-Builder1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: WaypointInBuilders
    if ((ScriptActionCtr_059 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetWaypoint(4);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: WaypointInBuilders2
    if ((ScriptActionCtr_062 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetWaypoint(4);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: WaypointInPriest
    if ((ScriptActionCtr_063 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetWaypoint(3);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }

    // Script 080: Music-Priests
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }

    // Script 105: CreatePriestHallNomad
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aMatcenSetState(1, Matcen_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: WaypointJustInside
    if ((ScriptActionCtr_064 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aSetWaypoint(7);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }

    // Script 072: Music-Common3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }

    // Script 083: NomadsCreatedOnTrigger
    if ((ScriptActionCtr_083 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aMatcenSetState(1, Matcen_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: BuildersPuzzleSequenceIn1
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[9], 1);
      aPortalRenderSet(0, 1, Room_indexes[9], 1);
      aPortalRenderSet(1, 0, Room_indexes[8], 1);
      aPortalRenderSet(1, 1, Room_indexes[8], 1);
      aUserVarSet(5, 1.000000f);
      aUserVarSet(15, qMathSubFloat(60.000000f, qMathMulFloat(qMathIntToFloat(qGetDifficulty()), 10.000000f)));
      aSetLevelTimer(qUserVarValue(15), 3);
      aTimerShow(3);
      aShowHUDMessageObjF(Message_strings[19], event_data->it_handle, qUserVarValue(15));
      aSetLevelTimer(qMathSubFloat(qUserVarValue(15), 3.000000f), 4);
      aObjSaveHandle(event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: BuildersPuzzleSequenceOut1
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[9], 1);
      aPortalRenderSet(0, 1, Room_indexes[9], 1);
      aPortalRenderSet(1, 0, Room_indexes[8], 1);
      aPortalRenderSet(1, 1, Room_indexes[8], 1);
      aUserVarSet(5, 1.000000f);
      aUserVarSet(15, qMathSubFloat(60.000000f, qMathMulFloat(qMathIntToFloat(qGetDifficulty()), 10.000000f)));
      aSetLevelTimer(qUserVarValue(15), 3);
      aTimerShow(3);
      aShowHUDMessageObjF(Message_strings[19], event_data->it_handle, qUserVarValue(15));
      aSetLevelTimer(qMathSubFloat(qUserVarValue(15), 3.000000f), 4);
      aObjSaveHandle(event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: BuildersPuzzleSequenceIn2
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[10], 1);
      aPortalRenderSet(0, 1, Room_indexes[10], 1);
      aPortalRenderSet(1, 0, Room_indexes[9], 1);
      aPortalRenderSet(1, 1, Room_indexes[9], 1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: BuildersPuzzleSequenceOut2
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[10], 1);
      aPortalRenderSet(0, 1, Room_indexes[10], 1);
      aPortalRenderSet(1, 0, Room_indexes[9], 1);
      aPortalRenderSet(1, 1, Room_indexes[9], 1);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: BuildersPuzzleSequenceIn3
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[11], 1);
      aPortalRenderSet(0, 1, Room_indexes[11], 1);
      aPortalRenderSet(1, 0, Room_indexes[10], 1);
      aPortalRenderSet(1, 1, Room_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: BuildersPuzzleSequenceOut3
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[11], 1);
      aPortalRenderSet(0, 1, Room_indexes[11], 1);
      aPortalRenderSet(1, 0, Room_indexes[10], 1);
      aPortalRenderSet(1, 1, Room_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: BuildersPuzzleSequenceIn4
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[12], 1);
      aPortalRenderSet(0, 1, Room_indexes[12], 1);
      aPortalRenderSet(1, 0, Room_indexes[11], 1);
      aPortalRenderSet(1, 1, Room_indexes[11], 1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: BuildersPuzzleSequenceOut4
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[12], 1);
      aPortalRenderSet(0, 1, Room_indexes[12], 1);
      aPortalRenderSet(1, 0, Room_indexes[11], 1);
      aPortalRenderSet(1, 1, Room_indexes[11], 1);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: BuildersPuzzleSequenceIn5
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[13], 1);
      aPortalRenderSet(0, 1, Room_indexes[13], 1);
      aPortalRenderSet(1, 0, Room_indexes[12], 1);
      aPortalRenderSet(1, 1, Room_indexes[12], 1);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: BuildersPuzzleSequenceOut5
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[13], 1);
      aPortalRenderSet(0, 1, Room_indexes[13], 1);
      aPortalRenderSet(1, 0, Room_indexes[12], 1);
      aPortalRenderSet(1, 1, Room_indexes[12], 1);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: BuildersPuzzleSequenceIn6
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[14], 1);
      aPortalRenderSet(0, 1, Room_indexes[14], 1);
      aPortalRenderSet(1, 0, Room_indexes[13], 1);
      aPortalRenderSet(1, 1, Room_indexes[13], 1);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: BuildersPuzzleSequenceOut6
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[14], 1);
      aPortalRenderSet(0, 1, Room_indexes[14], 1);
      aPortalRenderSet(1, 0, Room_indexes[13], 1);
      aPortalRenderSet(1, 1, Room_indexes[13], 1);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: BuildersPuzzleSequenceIn7
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[15], 1);
      aPortalRenderSet(0, 1, Room_indexes[15], 1);
      aPortalRenderSet(1, 0, Room_indexes[14], 1);
      aPortalRenderSet(1, 1, Room_indexes[14], 1);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: BuildersPuzzleSequenceOut7
    if (qObjSavedHandle(0) == event_data->it_handle) {
      aPortalRenderSet(0, 0, Room_indexes[15], 1);
      aPortalRenderSet(0, 1, Room_indexes[15], 1);
      aPortalRenderSet(1, 0, Room_indexes[14], 1);
      aPortalRenderSet(1, 1, Room_indexes[14], 1);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: BuildersPuzzleMessage
    if ((ScriptActionCtr_003 > 0) != 1) {
      aShowHUDMessageObj(Message_strings[20], event_data->it_handle);
      aShowHUDMessageObj(Message_strings[21], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }

    // Script 052: BuilderUFOonPath
    if ((ScriptActionCtr_052 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aAIGoalFollowPathSimple(Object_handles[29], Path_indexes[15], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[15], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[31], Path_indexes[16], 8392704, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: Exit Priest Puzzle
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aPriestKeyExit(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: Enter Priest Puzzle
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aPriestKeyEnter(event_data->it_handle);
      if (qUserVarValueInt(11) == 0) {
        aShowHUDMessageObj(Message_strings[24], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Music-Boss
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: Music-Builder2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Music-Collector1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 075: Music-UseKeys2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music-UseKeys1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: Music-UseKeys
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: Music-Common2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Music-Common1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Music-Outside
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 107: CreatePriestHallNomad2
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aMatcenSetEnableState(1, Matcen_indexes[3]);
      aMatcenSetState(1, Matcen_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0024::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 108: CreatePriestHallNomad3
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aMatcenSetEnableState(0, Matcen_indexes[3]);
      aMatcenSetState(0, Matcen_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 089: builders puzzle hint
    if ((ScriptActionCtr_089 < 1) && ((qObjIsPlayer(event_data->it_handle) == 1) && (qUserVarValueInt(14) == 0))) {
      aShowHUDMessageObj(Message_strings[37], event_data->it_handle);
      aUserVarSet(14, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 090: builders puzzle hint 2
    if ((ScriptActionCtr_090 < 1) && ((qObjIsPlayer(event_data->it_handle) == 1) && (qUserVarValueInt(14) == 0))) {
      aShowHUDMessageObj(Message_strings[37], event_data->it_handle);
      aUserVarSet(14, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
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
NEXT_ID		111

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:CanPickUpKey
1:BuildersCollectorsKeyPlaced
2:HasPickedUpCollectorOnce
3:HasPickedUpBuildersOnce
4:ClutchIsDestroyed
5:SetBuildersTimer
6:CheckPuzzroom
7:ThereIsPlayerInPriestKeyPuzzle
8:PriestPlayerCurrentRoom
9:PriestPlayerCurrNode
10:PriestPuzzleCurrSoundNode
11:PriestPuzzleCompleted
12:PriestPuzzlePlayerGoofed
13:BossNoLongerDead
14:BuildersPuzzHint
15:BuildersPuzzleTime
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:KeyPickupTimer
1:BossCinematic
2:EndLevelInterval
3:BuildersPuzzTimer
4:BuildersWarningBeep
5:IntroMovieLength
6:NextTugMessage
7:SequenceInterval
8:PlatformFalls
9:BossJustDied
10:InvReminder
11:PlatformEntersRoom
12:TurnOffPlatform
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:PlayerInRooms
1:PlayerInPriestKeyPuzzle
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:EndofTugEnterPath
1:TugPickedUpShip
2:NomadCreatedMainRoom
3:TugEndsFirstOutPath
4:TugEndsSecondOutPath
5:EndofTugEnterPath2
6:NomadCreatedPriestHall
7:NomadReachesCollector2
8:NomadCreatedPriestGallery
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
BossDoor
CollectorsDoor
BuildersDoor
PriestHallDoor
PriestGalleryDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
DummyFlag
BossMovieCollider
BossRock01
BossRock02
BossRock03
BossRock04
BossRock05
BuildersKey
ObjectMoveCamera
PriestKey
CollectorsKey
Camera4CollectorsK
Camera4BuildersKey
BuilderSign
CollectorSign
PriestSign
PriestHallDoor
PriestGalleryDoor
FallingPlatform
BuildersDoor
CollectorsDoor
PlatformClutch2
PlatformClutch1
PriestPedestalCame
Boss
BPuzzRespawn
SlagHeap
TugShip
CrashedShip
BuilderPuzzUFO1
BuilderPuzzUFO2
BuilderPuzzUFO3
CollectorNomad2
CollectorsNomad1
VolcanoSpew
VolcanoSpew2
VolcanoSpew3
VolcanoSpew4
BossDoor
$$OBJECT_LIST_END

$$ROOM_LIST_START
EndWindyRoom
PriestPedestal
CollectorsPedestal
BuildersPedestal
PlatformHitRoom
WindTunnel1
WindTunnel2
WindTunnel3
BPuzz1
BPuzz2
BPuzz3
BPuzz4
BPuzz5
BPuzz6
BPuzz7
BPuzzEnd
CrashedShipRoom
EscapeTunnelStart
NomadCollector2
CavernEntrance
$$ROOM_LIST_END

$$TRIGGER_LIST_START
MusicCommon2Coll
MusicCommon2Build
WaypointInBuilders
BuildersHalfWay
MusicUseKeys2Priest
MusicOut2Common
BPuzz1in
BPuzz1out
BPuzz2in
BPuzz2out
BPuzz3in
BPuzz3out
BPuzz4in
BPuzz4out
BPuzz5in
BPuzz5out
BPuzz6in
BPuzz6out
BPuzz7in
BPuzz7out
BuildersPuzzleMessa
ExitPriestPuzzle
EnterPriestPuzzle
MusicPriest2Boss
MusicUseKeys2Build
MusicUseKeys2Coll
MusicPriest2UseKeys
MusicBuild2UseKeys
MusicColl2UseKeys
MusicColl2Common
MusicBuild2Common
MusicCommon2Out
TurnPriestNomadsOn
TurnOffPriestNomads
BuildersPuzzHint
BuildersPuzzHint2
$$TRIGGER_LIST_END

$$SOUND_LIST_START
Powerup pickup
DoorIsLocked
expMissileTearing1
AmbBigUnlock
You don't have it BEEP
Lev5Goal
Lev5GoalFail
DefaultBuildingExplode
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffect1
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
Phoenix
TubbsHitBlast
$$SPECNAME_LIST_END

$$PATH_LIST_START
BossCinematicPath
IntroCameraPath
IntroShip
TugPathIn
TugPathIn2
TugEscapePath
TugEscapeCamera1
TugShipEscape2
TugEscapeCamera2
PlayerEscapeCamera
PlayerEscapePath
NomadPriestHall
NomadPriestHallRamp
NomadMainRoom1
NomadMainRoom2
BuildersPuzzPath
BuilderPuzzCorrect
CollectorNomad2
CollectorNomad1
NomadPriestGallery
$$PATH_LIST_END

$$MATCEN_LIST_START
Boss Room Matcen 1
Boss Room Matcen 2
NomadMainRoom1
NomadPriestHall
NomadPriestGallery
$$MATCEN_LIST_END

$$GOAL_LIST_START
Find the Builders' Icon
Find the Priest's Icon
Find the Collectors' Icon
Use the icons
Use the Priest's Icon
Find the crashed CED ship
Enter the Nomad Caverns
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL06SpecificC.osf
VoxL06SpecificA.osf
VoxL06SpecificE.osf
VoxL06SpecificG.osf
VoxL06SpecificF.osf
VoxL06EndLevel.osf
VoxL06StartLevel.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:6:LevelStart
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
                        10:10:0:0:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserVar
                        10:6:0.000000:value
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aPriestKeyInit
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:13:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:-0.170000:X
                        10:6:-0.966000:Y
                        10:6:-0.192000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:CollideWithBuildersKey
        $$CHILD_BLOCK_START
        01:1:7
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:1
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
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
                                10:8:FirstPickupBuilder:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aCancelTimer
                                $$CHILD_BLOCK_START
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:2:Number
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:13.000000:Time
                                10:10:0:10:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:CollideWithPriestKey
        $$CHILD_BLOCK_START
        01:1:9
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                07:1:1
                                10:2:1:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FirstPickupPriest:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:CollideWithCollectorsKey
        $$CHILD_BLOCK_START
        01:1:10
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:1
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FirstPickupCollector:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:13.000000:Time
                                10:10:0:10:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Inventory Reminder Timer Goes Off
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:InvGame:GameMessage
                        10:8:InvHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:WaypointCollectorsOrigin
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:6:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:WaypointBuildersOrigin
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:5:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:WaypointInBuilders
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:WaypointInBuilders2
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:WaypointInPriest
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:3:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:WaypointJustInside
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:7:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:UseCollectorsKey
        $$CHILD_BLOCK_START
        01:1:10
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:3:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:7:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:1
                                                10:2:2:Room
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:11:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:0.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:3.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessageObj
                                                $$CHILD_BLOCK_START
                                                10:8:PlaceCollectorsKey:Message
                                                10:1:1:-1:PlayerObject
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
                                                10:8:KeyAlreadyThere:Message
                                                10:1:1:-1:PlayerObject
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:7:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:1
                                                10:2:3:Room
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:12:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:0.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:3.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessageObj
                                                $$CHILD_BLOCK_START
                                                10:8:PlaceCollectorsKey:Message
                                                10:1:1:-1:PlayerObject
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
                                                10:8:KeyAlreadyThere:Message
                                                10:1:1:-1:PlayerObject
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                10:8:YoucantUseKeyHere:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                $$CHILD_BLOCK_END
                        08:aMoveObjectToPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:UseBuildersKey
        $$CHILD_BLOCK_START
        01:1:7
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:3:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:10:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:1
                                                10:2:2:Room
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:11:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:0.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:3.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessageObj
                                                $$CHILD_BLOCK_START
                                                10:8:PlaceBuildersKey:Message
                                                10:1:1:-1:PlayerObject
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
                                                10:8:KeyAlreadyThere:Message
                                                10:1:1:-1:PlayerObject
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:10:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:1
                                                10:2:3:Room
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:12:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                10:6:0.000000:value
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:3.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessageObj
                                                $$CHILD_BLOCK_START
                                                10:8:PlaceBuildersKey:Message
                                                10:1:1:-1:PlayerObject
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
                                                10:8:KeyAlreadyThere:Message
                                                10:1:1:-1:PlayerObject
                                                $$CHILD_BLOCK_END
                                        08:aStoreObjectInPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        08:aMoveObjectToPositionClipboard
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                10:8:YoucantUseKeyHere:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                $$CHILD_BLOCK_END
                        08:aMoveObjectToPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Collectors & Builders Key Correctly Placed
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:0:10:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:2:2:Room
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:0:7:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:2:3:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BuilderCollectorsCorrectlyPlaced:Message
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:LightningTest
        $$CHILD_BLOCK_START
        01:1:13
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:0:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object1
                        10:1:0:15:Object2
                        10:6:10.000000:Lifetime
                        10:6:4.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:255:Red
                        10:4:255:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Player tries to open Priest Hall door
        $$CHILD_BLOCK_START
        01:1:16
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:0:10:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:2:Room
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:0:7:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:3:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:3:Door
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:PriestHallDoorLocked:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Player tries to open Priest Gallery door
        $$CHILD_BLOCK_START
        01:1:17
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:2:1:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:4:Door
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:PriestGalleryDoorLocked:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:LevelKeyTimer
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:DisablePlatformMovement
        $$CHILD_BLOCK_START
        01:1:18
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGravityEnable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:BuildersDoorMessage
        $$CHILD_BLOCK_START
        01:1:19
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:BuildersDoorMessage:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:2:-1:Door
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:ThisDoorDoesNotAnswer:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aSoundPlay2DObj
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:1:-1:PlayerObject
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:CollectorsDoorMessage
        $$CHILD_BLOCK_START
        01:1:20
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:3:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:CollectorsDoorMessage:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:2:-1:Door
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:ThisDoorDoesNotAnswer:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aSoundPlay2DObj
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:1:-1:PlayerObject
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:PlatformClutch2Dies
        $$CHILD_BLOCK_START
        01:1:21
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjGravityEnable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:1:0:18:Object
                                $$CHILD_BLOCK_END
                        08:aSoundPlay2D
                                $$CHILD_BLOCK_START
                                10:12:2:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:0:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:40.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:40.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:PlatformClutch1Dies
        $$CHILD_BLOCK_START
        01:1:22
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjGravityEnable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:1:0:18:Object
                                $$CHILD_BLOCK_END
                        08:aSoundPlay2D
                                $$CHILD_BLOCK_START
                                10:12:2:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:0:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:30.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:4:1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:30.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:DoStuffWhenPlatformHits
        $$CHILD_BLOCK_START
        01:1:18
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjRoom:Room
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:2:4:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.150000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:PlatformTimer
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
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Turn Off Platform
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Priest Key Correctly Placed
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjRoom:Room
                                $$CHILD_BLOCK_START
                                10:1:0:9:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PriestKeyCorrectlyPlaced:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:UsePriestKey
        $$CHILD_BLOCK_START
        01:1:9
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:2:1:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                $$CHILD_BLOCK_END
                        08:aMoveObjectToPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:PlacePriestKey:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:4:DoorName
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
                                10:8:YoucantUseKeyHere:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                $$CHILD_BLOCK_END
                        08:aMoveObjectToPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:InitWindTunnel1
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
                        10:2:5:Room
                        10:6:0.633000:X
                        10:6:0.291000:Y
                        10:6:0.718000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:InitWindTunnel2
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
                        10:2:6:Room
                        10:6:0.633000:X
                        10:6:0.291000:Y
                        10:6:0.718000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:InitWindTunnel3
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
                        10:2:7:Room
                        10:6:0.633000:X
                        10:6:0.291000:Y
                        10:6:0.718000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:BossCameraTimer
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:BossCameraMove
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
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:BossIntroductionText:Text
                        10:1:0:24:Target
                        10:6:14.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:IntroCamera
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
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:1:CameraPath
                        10:8:IntroLevelMessage:Text
                        10:1:0:18:TotallyNotUsedTarget
                        10:16:2:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:BuildersDisableFirstForcefield
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:BuildersPuzzleSequenceIn1
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserVar
                        06:qMathSubFloat:value
                                $$CHILD_BLOCK_START
                                10:6:60.000000:Float1
                                06:qMathMulFloat:Float2
                                        $$CHILD_BLOCK_START
                                        06:qMathIntToFloat:Float1
                                                $$CHILD_BLOCK_START
                                                06:qGetDifficulty:Int
                                                $$CHILD_BLOCK_END
                                        10:6:10.000000:Float2
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Time
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aTimerShow
                        $$CHILD_BLOCK_START
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObjF
                        $$CHILD_BLOCK_START
                        10:8:XsecsOntheClock:Message
                        10:1:1:-1:PlayerObject
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qMathSubFloat:Time
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float1
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:3.000000:Float2
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:BuildersPuzzleSequenceOut1
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserVar
                        06:qMathSubFloat:value
                                $$CHILD_BLOCK_START
                                10:6:60.000000:Float1
                                06:qMathMulFloat:Float2
                                        $$CHILD_BLOCK_START
                                        06:qMathIntToFloat:Float1
                                                $$CHILD_BLOCK_START
                                                06:qGetDifficulty:Int
                                                $$CHILD_BLOCK_END
                                        10:6:10.000000:Float2
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Time
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aTimerShow
                        $$CHILD_BLOCK_START
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObjF
                        $$CHILD_BLOCK_START
                        10:8:XsecsOntheClock:Message
                        10:1:1:-1:PlayerObject
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qMathSubFloat:Time
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float1
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserVar
                                        $$CHILD_BLOCK_END
                                10:6:3.000000:Float2
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:BuildersPuzzleSequenceIn2
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:BuildersPuzzleSequenceOut2
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:BuildersPuzzleSequenceIn3
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
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
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:BuildersPuzzleSequenceOut3
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
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
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:BuildersPuzzleSequenceIn4
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
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
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:BuildersPuzzleSequenceOut4
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
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
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:BuildersPuzzleSequenceIn5
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:BuildersPuzzleSequenceOut5
        $$CHILD_BLOCK_START
        01:0:15
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:BuildersPuzzleSequenceIn6
        $$CHILD_BLOCK_START
        01:0:16
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:BuildersPuzzleSequenceOut6
        $$CHILD_BLOCK_START
        01:0:17
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:13:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:BuildersPuzzleSequenceIn7
        $$CHILD_BLOCK_START
        01:0:18
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:15:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:15:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:BuildersPuzzleSequenceOut7
        $$CHILD_BLOCK_START
        01:0:19
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:15:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:15:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:14:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:BuildersPuzzleMessage
        $$CHILD_BLOCK_START
        01:0:20
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:3:ScriptID
                                $$CHILD_BLOCK_END
                        07:1:1
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:BuildersPuzzMessage:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:BuildersPuzzMessage2:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:BuildersWarningBeep
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:2:0:TimerID
                                07:1:0
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:1
                                10:6:1.000000:Float
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:Builders3secondsleft:Message
                        06:qObjSavedHandle:PlayerObject
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        06:qObjSavedHandle:PlayerObject
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:BuildersTimerExpires
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qHasObjectInInventory:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Player
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:1:0:7:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:0:Bool
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:BuildersTimerExpired:Message
                                06:qObjSavedHandle:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:8:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:8:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:9:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:9:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:10:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:10:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:11:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:11:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:12:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:12:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:13:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:13:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:14:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:14:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:15:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:15:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:8:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:9:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:10:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:11:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:12:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:13:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:14:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:15:Room
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:25:Object
                                        $$CHILD_BLOCK_END
                                08:aFadeAndMovePlayer
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Player
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Priest Key Room Change Handler
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPriestKeyRoomChange
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Exit Priest Puzzle
        $$CHILD_BLOCK_START
        01:0:21
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPriestKeyExit
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Player
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Enter Priest Puzzle
        $$CHILD_BLOCK_START
        01:0:22
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPriestKeyEnter
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Player
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:PriestPuzzleEnter:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:PriestPuzzleSolved
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PriestPuzzleSolved:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Priest Puzzle, Player Goofed
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:1.000000:Float
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PriestPuzzleGoofed:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:BlowUpSlagHeap
        $$CHILD_BLOCK_START
        01:1:24
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjAnimFrame:Float
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                $$CHILD_BLOCK_END
                        07:1:1
                        10:6:126.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:MessagePlayerSeesBoss
        $$CHILD_BLOCK_START
        01:1:24
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:MessageTugWarnsPlayer
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessage1:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessage2:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:StartTugMessage
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessageStart:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugStartMessage2:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:BossDoesFakeDeath
        $$CHILD_BLOCK_START
        01:1:24
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjAnimFrame:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:210.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:DropForcefieldsOnFakeDeath
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:16:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:17:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessageShipPickUp:Message
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:16:3:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:TugPicksUpShip1
        $$CHILD_BLOCK_START
        01:1:27
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:4:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:5:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:TugPicksUpShip2
        $$CHILD_BLOCK_START
        01:1:27
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Picker
                        10:4:0:PickerPoint
                        10:1:0:28:Pickee
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:1:GoalID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessage5:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:BossNoLongerDead
        $$CHILD_BLOCK_START
        01:1:24
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjAnimFrame:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:210.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:13:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:BossNoLongerDeadPart2
        $$CHILD_BLOCK_START
        01:1:24
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:24:Object
                                        $$CHILD_BLOCK_END
                                07:1:1
                                10:6:210.000000:Literal
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessage4:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:BossRealDeath
        $$CHILD_BLOCK_START
        01:1:24
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjAnimFrame:Float
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:350.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TugMessage6:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:DoStuffWhenBossDies
        $$CHILD_BLOCK_START
        01:2:0
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:85:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:16:5:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aEnableShip
                        $$CHILD_BLOCK_START
                        10:13:0:Ship
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:8:BLANK:Text
                        10:1:0:27:Target
                        10:6:18.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:TugEscapeCamera2
        $$CHILD_BLOCK_START
        01:1:27
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:7:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:4:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Start2ndPartCinematicAlt
        $$CHILD_BLOCK_START
        01:1:27
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:2
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:68:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:8:CameraPath
                                10:8:BLANK:Text
                                10:1:2:-1:Target
                                10:6:10.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:68:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aStartEndlevelSequencePath
                                $$CHILD_BLOCK_START
                                10:16:9:CameraPath
                                10:16:10:PlayerPath
                                10:6:14.000000:Time
                                10:8:BLANK:Text
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Test:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Music-Boss
        $$CHILD_BLOCK_START
        01:0:23
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Music-Priests
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Music-Builder2
        $$CHILD_BLOCK_START
        01:0:24
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
00:78:Music-Builder1
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Music-Collector2
        $$CHILD_BLOCK_START
        01:0:0
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
00:76:Music-Collector1
        $$CHILD_BLOCK_START
        01:0:25
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
00:75:Music-UseKeys2
        $$CHILD_BLOCK_START
        01:0:26
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
00:74:Music-UseKeys1
        $$CHILD_BLOCK_START
        01:0:27
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
00:73:Music-UseKeys
        $$CHILD_BLOCK_START
        01:0:28
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
00:72:Music-Common3
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
00:71:Music-Common2
        $$CHILD_BLOCK_START
        01:0:29
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
00:70:Music-Common1
        $$CHILD_BLOCK_START
        01:0:30
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
00:69:Music-Outside
        $$CHILD_BLOCK_START
        01:0:31
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:MusicOutsideRegion
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
00:83:NomadsCreatedOnTrigger
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:NomadPriestHall
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:0.000000:LowerLimit
                                        10:6:1.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:0.500000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:11:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:6:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:12:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:6:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:CreatePriestHallNomad
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:CreatePriestHallNomad2
        $$CHILD_BLOCK_START
        01:0:32
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:CreatePriestHallNomad3
        $$CHILD_BLOCK_START
        01:0:33
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:NomadMainRoomMatcen1
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:0.000000:LowerLimit
                                        10:6:1.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:0.500000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:13:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:14:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:KillNomadPriestHall
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:KillNomadMainRoom
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:BuilderUFOonPath
        $$CHILD_BLOCK_START
        01:0:20
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:16:15:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:16:15:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:16:16:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:builders puzzle hint
        $$CHILD_BLOCK_START
        01:0:34
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:BuildersPuzzhint:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:builders puzzle hint 2
        $$CHILD_BLOCK_START
        01:0:35
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:BuildersPuzzhint:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:CollectorsNomad2
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qRoomHasPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:2:18:Room
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:16:17:Path
                        10:15:1052928:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:KillNomadCollector2
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:CollectorsNomad1
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:16:18:Path
                        10:15:1052928:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:TurnOnSpew
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:1000000000.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:1000000000.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:1000000000.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:1000000000.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:BossDoorLocked
        $$CHILD_BLOCK_START
        01:1:38
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjIsPlayerOrPlayerWeapon:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:BLANK:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:DroppingRocks01
        $$CHILD_BLOCK_START
        01:1:2
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjectPosition:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:1:Axis
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:-490.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:1:WeaponName
                        10:4:-1:GunNum
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:DroppingRocks02
        $$CHILD_BLOCK_START
        01:1:3
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjectPosition:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:1:Axis
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:-490.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:1:WeaponName
                        10:4:-1:GunNum
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:DroppingRocks03
        $$CHILD_BLOCK_START
        01:1:4
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjectPosition:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:1:Axis
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:-490.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:1:WeaponName
                        10:4:-1:GunNum
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:DroppingRocks04
        $$CHILD_BLOCK_START
        01:1:5
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjectPosition:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:1:Axis
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:-490.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:1:WeaponName
                        10:4:-1:GunNum
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:DroppingRocks05
        $$CHILD_BLOCK_START
        01:1:6
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjectPosition:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:1:Axis
                                $$CHILD_BLOCK_END
                        07:1:3
                        10:6:-490.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjFireWeapon
                        $$CHILD_BLOCK_START
                        10:13:1:WeaponName
                        10:4:-1:GunNum
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:PlayerEntersTheCaverns
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qRoomHasPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:5:1:Bool
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:NomadPriestGallery
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:19:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:KillNomadPriestGallery
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Voice Over Intro
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
