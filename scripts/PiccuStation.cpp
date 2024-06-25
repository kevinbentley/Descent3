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
// Filename:	piccustation.cpp
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

#define ID_CUSTOM_OBJECT_2109 0x001
#define ID_CUSTOM_OBJECT_206D 0x002
#define ID_CUSTOM_OBJECT_306C 0x003
#define ID_CUSTOM_OBJECT_1869 0x004
#define ID_CUSTOM_OBJECT_186A 0x005
#define ID_CUSTOM_OBJECT_184A 0x006
#define ID_CUSTOM_OBJECT_4049 0x007
#define ID_CUSTOM_OBJECT_0961 0x008
#define ID_CUSTOM_OBJECT_0960 0x009
#define ID_CUSTOM_OBJECT_095F 0x00a
#define ID_CUSTOM_OBJECT_095E 0x00b
#define ID_CUSTOM_OBJECT_3072 0x00c
#define ID_CUSTOM_OBJECT_406F 0x00d
#define ID_CUSTOM_OBJECT_0B3C 0x00e
#define ID_CUSTOM_OBJECT_1338 0x00f
#define ID_CUSTOM_OBJECT_1337 0x010
#define ID_CUSTOM_OBJECT_1339 0x011
#define ID_CUSTOM_OBJECT_133A 0x012
#define ID_CUSTOM_OBJECT_1B35 0x013
#define ID_CUSTOM_OBJECT_1B34 0x014
#define ID_CUSTOM_OBJECT_1B41 0x015
#define ID_CUSTOM_OBJECT_1336 0x016
#define ID_CUSTOM_OBJECT_6856 0x017
#define ID_CUSTOM_OBJECT_0B40 0x018
#define ID_CUSTOM_OBJECT_0B30 0x019
#define ID_CUSTOM_OBJECT_0B31 0x01a
#define ID_CUSTOM_OBJECT_1B2E 0x01b
#define ID_CUSTOM_OBJECT_0B2F 0x01c
#define ID_CUSTOM_OBJECT_0B32 0x01d
#define ID_CUSTOM_OBJECT_232D 0x01e
#define ID_CUSTOM_OBJECT_0B3F 0x01f
#define ID_CUSTOM_OBJECT_0B3B 0x020
#define ID_CUSTOM_OBJECT_0B3D 0x021
#define ID_CUSTOM_OBJECT_0B3E 0x022
#define ID_CUSTOM_OBJECT_1195 0x023

#define ID_TRIGGER_0005 0x024
#define ID_TRIGGER_0004 0x025
#define ID_TRIGGER_0003 0x026
#define ID_TRIGGER_0012 0x027
#define ID_TRIGGER_0002 0x028
#define ID_TRIGGER_0000 0x029
#define ID_TRIGGER_0013 0x02a
#define ID_TRIGGER_0014 0x02b
#define ID_TRIGGER_0016 0x02c
#define ID_TRIGGER_0017 0x02d
#define ID_TRIGGER_0015 0x02e
#define ID_TRIGGER_001B 0x02f
#define ID_TRIGGER_001A 0x030
#define ID_TRIGGER_0019 0x031
#define ID_TRIGGER_0018 0x032
#define ID_TRIGGER_001F 0x033
#define ID_TRIGGER_0009 0x034
#define ID_TRIGGER_001E 0x035
#define ID_TRIGGER_001D 0x036
#define ID_TRIGGER_000F 0x037
#define ID_TRIGGER_000B 0x038
#define ID_TRIGGER_001C 0x039
#define ID_TRIGGER_000D 0x03a
#define ID_TRIGGER_0007 0x03b
#define ID_TRIGGER_000E 0x03c
#define ID_TRIGGER_002B 0x03d
#define ID_TRIGGER_002A 0x03e
#define ID_TRIGGER_0029 0x03f
#define ID_TRIGGER_0028 0x040
#define ID_TRIGGER_0027 0x041
#define ID_TRIGGER_0025 0x042
#define ID_TRIGGER_0026 0x043
#define ID_TRIGGER_000A 0x044
#define ID_TRIGGER_0024 0x045
#define ID_TRIGGER_0021 0x046
#define ID_TRIGGER_0023 0x047
#define ID_TRIGGER_0020 0x048
#define ID_TRIGGER_0022 0x049
#define ID_TRIGGER_002C 0x04a

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

class CustomObjectScript_2109 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_206D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_306C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1869 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_186A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_184A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_4049 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0961 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0960 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_095F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_095E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3072 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_406F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B3C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1338 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1337 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1339 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_133A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1B35 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1B34 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1B41 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1336 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_6856 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B40 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B30 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B31 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1B2E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B2F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B32 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_232D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B3F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B3B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B3D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0B3E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1195 : public BaseScript {
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

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
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

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0019 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0029 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0028 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0027 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0025 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0026 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
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

class TriggerScript_0023 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0022 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_002C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_098 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_098 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:IntroCam
1:FirstIndoor
2:FirstOutdoor
3:SecondIndoor
4:DatlinkVariation
5:Cave
6:SecondOutdoor
7:Ancients
8:ThirdOutdoor
9:AlienCraft
10:SecondIndoorPart2
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

#define NUM_DOOR_NAMES 3
static const char *const Door_names[NUM_DOOR_NAMES] = {"KeyDoor", "RadioDoor", "MatcenDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 80
static const char *const Object_names[NUM_OBJECT_NAMES] = {"AlienVirusStand",
                                                           "BigPipeKey2",
                                                           "DatlinkCenter",
                                                           "ComputerPole2",
                                                           "ComputerPole1",
                                                           "GiantPipeRoom",
                                                           "LavaPlane",
                                                           "YellowBlueTurbine",
                                                           "FirstBigMachine",
                                                           "PlayerShip",
                                                           "Virus",
                                                           "Virushouse",
                                                           "RescueShip1",
                                                           "RescueShip2",
                                                           "RescueShip3",
                                                           "GoodieRoomSwitch",
                                                           "FirstOutsideDoorSw",
                                                           "OutdoorKillTank",
                                                           "KeyCard2",
                                                           "SecurityDoor",
                                                           "KeyCard1",
                                                           "RadioDoorSwitch2",
                                                           "RadioCam",
                                                           "RadioDoorSwitch1",
                                                           "RadioToggle4",
                                                           "RadioToggle3",
                                                           "RadioToggle2",
                                                           "RadioToggle1",
                                                           "MatcenSwitch2",
                                                           "MatcenCam",
                                                           "MatcenSwitch1",
                                                           "BunkBed1",
                                                           "Exp1",
                                                           "Exp2",
                                                           "Exp3",
                                                           "Exp4",
                                                           "Exp5",
                                                           "Exp6",
                                                           "Exp7",
                                                           "Exp8",
                                                           "UFODestroy4",
                                                           "UFOSmoke4",
                                                           "UFODestroy3",
                                                           "UFOSmoke3",
                                                           "UFODestroy2",
                                                           "UFOSmoke2",
                                                           "UFODestroy1",
                                                           "UFOSmoke1",
                                                           "VirusTerminal",
                                                           "VirusCamTarget",
                                                           "DontAttackTail",
                                                           "BunkBed5",
                                                           "Lava7",
                                                           "Lava5",
                                                           "Lava3",
                                                           "Lava1",
                                                           "SBlackSmall",
                                                           "BottomSpewer",
                                                           "SWhite2",
                                                           "SWhite1",
                                                           "SBlackGravity4",
                                                           "SBlackGravity3",
                                                           "SBlackGravity2",
                                                           "SBlackGravity1",
                                                           "SWhiteGravity2",
                                                           "SWhiteGravity1",
                                                           "BunkBed12",
                                                           "BunkBed11",
                                                           "BunkBed10",
                                                           "BunkBed9",
                                                           "BunkBed8",
                                                           "BunkBed7",
                                                           "BunkBed6",
                                                           "BunkBed4",
                                                           "BunkBed3",
                                                           "BunkBed2",
                                                           "DStringer1",
                                                           "DTubbs3",
                                                           "DTubbs2",
                                                           "DTubbs1"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 13
static const char *const Room_names[NUM_ROOM_NAMES] = {"GoodiePortalRoom", "FirstOutdoorPortal",
                                                       "ReturnInsideRoom", "RadioRoom",
                                                       "RadioArmory",      "Alien1",
                                                       "Alien2",           "Alien3",
                                                       "Alien4",           "Alien5",
                                                       "Alien6",           "Alien7",
                                                       "VirusRoom"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 39
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "Waypoint8",   "Waypoint7",   "Waypoint6",   "Waypoint5",     "Waypoint4",      "Waypoint2",      "Waypoint1",
    "VirusEnter",  "CuplinkCam2", "CuplinkCam3", "CuplinkCam1",   "Exit4",          "Exit3",          "Exit2",
    "Exit1",       "Voice10",     "Voice9",      "Voice8",        "Voice7",         "Voice-Computer", "Voice5",
    "Voice6",      "Voice3",      "Voice2",      "Voice1",        "Music-Alien",    "Music-Ancient",  "Music-2Out2",
    "Music-2Out1", "Music-Cave2", "Music-Cave1", "Music-2InPt22", "Music-2InPart2", "Music-2In2",     "Music-2In",
    "Music-1Out2", "Music-1Out",  "Music-1In",   "Music-2InDat"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 10
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbDroneP",    "AmbDroneE",     "AmbDroneD", "AmbDroneX",
                                                         "AmbLavaLoop1", "AmbDroneN",     "AmbDroneK", "AmbSwitch31",
                                                         "PupC1",        "AmbVirusSwitch"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 5
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"Reddataup", "Ready1", "Notready", "Staticscrolling",
                                                             "Online"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 9
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCam", "IntroShip", "VirusCam", "CupLinkCam", "Rescuer3",
                                                       "Rescuer2", "Rescuer1",  "EndCam",   "EndLevelCam"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 2
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"DatlinkMatcen", "TwoSwitchMatcen"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 3
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Activate Datlink", "Acquire the alien virus",
                                                       "Retrieve the Alien Virus"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 16
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "IntroMessage",    "ForceFieldDeactivated", "2KeyCards",     "1KeyCard",
    "RadioRoomUnlock", "RadioRoomFirst",        "All4Radio",     "All4Radio2",
    "TwoSwitchUnlock", "TwoSwitchFirst",        "AlienCuplinks", "HeresVirus",
    "Virus",           "DestroyThese",          "EndLevel",      "PowerCupLink"};
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
  if (func_list->script_identifier != NULL) {
    _splitpath(func_list->script_identifier, NULL, NULL, filename, NULL);
    strcat(filename, ".msg");
  } else {
    strcpy(filename, "piccustation.msg");
  }
  ReadMessageFile(filename);

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
  case ID_CUSTOM_OBJECT_2109:
    return new CustomObjectScript_2109;
    break;
  case ID_CUSTOM_OBJECT_206D:
    return new CustomObjectScript_206D;
    break;
  case ID_CUSTOM_OBJECT_306C:
    return new CustomObjectScript_306C;
    break;
  case ID_CUSTOM_OBJECT_1869:
    return new CustomObjectScript_1869;
    break;
  case ID_CUSTOM_OBJECT_186A:
    return new CustomObjectScript_186A;
    break;
  case ID_CUSTOM_OBJECT_184A:
    return new CustomObjectScript_184A;
    break;
  case ID_CUSTOM_OBJECT_4049:
    return new CustomObjectScript_4049;
    break;
  case ID_CUSTOM_OBJECT_0961:
    return new CustomObjectScript_0961;
    break;
  case ID_CUSTOM_OBJECT_0960:
    return new CustomObjectScript_0960;
    break;
  case ID_CUSTOM_OBJECT_095F:
    return new CustomObjectScript_095F;
    break;
  case ID_CUSTOM_OBJECT_095E:
    return new CustomObjectScript_095E;
    break;
  case ID_CUSTOM_OBJECT_3072:
    return new CustomObjectScript_3072;
    break;
  case ID_CUSTOM_OBJECT_406F:
    return new CustomObjectScript_406F;
    break;
  case ID_CUSTOM_OBJECT_0B3C:
    return new CustomObjectScript_0B3C;
    break;
  case ID_CUSTOM_OBJECT_1338:
    return new CustomObjectScript_1338;
    break;
  case ID_CUSTOM_OBJECT_1337:
    return new CustomObjectScript_1337;
    break;
  case ID_CUSTOM_OBJECT_1339:
    return new CustomObjectScript_1339;
    break;
  case ID_CUSTOM_OBJECT_133A:
    return new CustomObjectScript_133A;
    break;
  case ID_CUSTOM_OBJECT_1B35:
    return new CustomObjectScript_1B35;
    break;
  case ID_CUSTOM_OBJECT_1B34:
    return new CustomObjectScript_1B34;
    break;
  case ID_CUSTOM_OBJECT_1B41:
    return new CustomObjectScript_1B41;
    break;
  case ID_CUSTOM_OBJECT_1336:
    return new CustomObjectScript_1336;
    break;
  case ID_CUSTOM_OBJECT_6856:
    return new CustomObjectScript_6856;
    break;
  case ID_CUSTOM_OBJECT_0B40:
    return new CustomObjectScript_0B40;
    break;
  case ID_CUSTOM_OBJECT_0B30:
    return new CustomObjectScript_0B30;
    break;
  case ID_CUSTOM_OBJECT_0B31:
    return new CustomObjectScript_0B31;
    break;
  case ID_CUSTOM_OBJECT_1B2E:
    return new CustomObjectScript_1B2E;
    break;
  case ID_CUSTOM_OBJECT_0B2F:
    return new CustomObjectScript_0B2F;
    break;
  case ID_CUSTOM_OBJECT_0B32:
    return new CustomObjectScript_0B32;
    break;
  case ID_CUSTOM_OBJECT_232D:
    return new CustomObjectScript_232D;
    break;
  case ID_CUSTOM_OBJECT_0B3F:
    return new CustomObjectScript_0B3F;
    break;
  case ID_CUSTOM_OBJECT_0B3B:
    return new CustomObjectScript_0B3B;
    break;
  case ID_CUSTOM_OBJECT_0B3D:
    return new CustomObjectScript_0B3D;
    break;
  case ID_CUSTOM_OBJECT_0B3E:
    return new CustomObjectScript_0B3E;
    break;
  case ID_CUSTOM_OBJECT_1195:
    return new CustomObjectScript_1195;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_002B:
    return new TriggerScript_002B;
    break;
  case ID_TRIGGER_002A:
    return new TriggerScript_002A;
    break;
  case ID_TRIGGER_0029:
    return new TriggerScript_0029;
    break;
  case ID_TRIGGER_0028:
    return new TriggerScript_0028;
    break;
  case ID_TRIGGER_0027:
    return new TriggerScript_0027;
    break;
  case ID_TRIGGER_0025:
    return new TriggerScript_0025;
    break;
  case ID_TRIGGER_0026:
    return new TriggerScript_0026;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0024:
    return new TriggerScript_0024;
    break;
  case ID_TRIGGER_0021:
    return new TriggerScript_0021;
    break;
  case ID_TRIGGER_0023:
    return new TriggerScript_0023;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_0022:
    return new TriggerScript_0022;
    break;
  case ID_TRIGGER_002C:
    return new TriggerScript_002C;
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
  case ID_CUSTOM_OBJECT_2109:
    delete ((CustomObjectScript_2109 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_206D:
    delete ((CustomObjectScript_206D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_306C:
    delete ((CustomObjectScript_306C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1869:
    delete ((CustomObjectScript_1869 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_186A:
    delete ((CustomObjectScript_186A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_184A:
    delete ((CustomObjectScript_184A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_4049:
    delete ((CustomObjectScript_4049 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0961:
    delete ((CustomObjectScript_0961 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0960:
    delete ((CustomObjectScript_0960 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_095F:
    delete ((CustomObjectScript_095F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_095E:
    delete ((CustomObjectScript_095E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3072:
    delete ((CustomObjectScript_3072 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_406F:
    delete ((CustomObjectScript_406F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B3C:
    delete ((CustomObjectScript_0B3C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1338:
    delete ((CustomObjectScript_1338 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1337:
    delete ((CustomObjectScript_1337 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1339:
    delete ((CustomObjectScript_1339 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_133A:
    delete ((CustomObjectScript_133A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1B35:
    delete ((CustomObjectScript_1B35 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1B34:
    delete ((CustomObjectScript_1B34 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1B41:
    delete ((CustomObjectScript_1B41 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1336:
    delete ((CustomObjectScript_1336 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_6856:
    delete ((CustomObjectScript_6856 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B40:
    delete ((CustomObjectScript_0B40 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B30:
    delete ((CustomObjectScript_0B30 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B31:
    delete ((CustomObjectScript_0B31 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1B2E:
    delete ((CustomObjectScript_1B2E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B2F:
    delete ((CustomObjectScript_0B2F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B32:
    delete ((CustomObjectScript_0B32 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_232D:
    delete ((CustomObjectScript_232D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B3F:
    delete ((CustomObjectScript_0B3F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B3B:
    delete ((CustomObjectScript_0B3B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B3D:
    delete ((CustomObjectScript_0B3D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0B3E:
    delete ((CustomObjectScript_0B3E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1195:
    delete ((CustomObjectScript_1195 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_002B:
    delete ((TriggerScript_002B *)ptr);
    break;
  case ID_TRIGGER_002A:
    delete ((TriggerScript_002A *)ptr);
    break;
  case ID_TRIGGER_0029:
    delete ((TriggerScript_0029 *)ptr);
    break;
  case ID_TRIGGER_0028:
    delete ((TriggerScript_0028 *)ptr);
    break;
  case ID_TRIGGER_0027:
    delete ((TriggerScript_0027 *)ptr);
    break;
  case ID_TRIGGER_0025:
    delete ((TriggerScript_0025 *)ptr);
    break;
  case ID_TRIGGER_0026:
    delete ((TriggerScript_0026 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0024:
    delete ((TriggerScript_0024 *)ptr);
    break;
  case ID_TRIGGER_0021:
    delete ((TriggerScript_0021 *)ptr);
    break;
  case ID_TRIGGER_0023:
    delete ((TriggerScript_0023 *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_0022:
    delete ((TriggerScript_0022 *)ptr);
    break;
  case ID_TRIGGER_002C:
    delete ((TriggerScript_002C *)ptr);
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
  case ID_CUSTOM_OBJECT_2109:
  case ID_CUSTOM_OBJECT_206D:
  case ID_CUSTOM_OBJECT_306C:
  case ID_CUSTOM_OBJECT_1869:
  case ID_CUSTOM_OBJECT_186A:
  case ID_CUSTOM_OBJECT_184A:
  case ID_CUSTOM_OBJECT_4049:
  case ID_CUSTOM_OBJECT_0961:
  case ID_CUSTOM_OBJECT_0960:
  case ID_CUSTOM_OBJECT_095F:
  case ID_CUSTOM_OBJECT_095E:
  case ID_CUSTOM_OBJECT_3072:
  case ID_CUSTOM_OBJECT_406F:
  case ID_CUSTOM_OBJECT_0B3C:
  case ID_CUSTOM_OBJECT_1338:
  case ID_CUSTOM_OBJECT_1337:
  case ID_CUSTOM_OBJECT_1339:
  case ID_CUSTOM_OBJECT_133A:
  case ID_CUSTOM_OBJECT_1B35:
  case ID_CUSTOM_OBJECT_1B34:
  case ID_CUSTOM_OBJECT_1B41:
  case ID_CUSTOM_OBJECT_1336:
  case ID_CUSTOM_OBJECT_6856:
  case ID_CUSTOM_OBJECT_0B40:
  case ID_CUSTOM_OBJECT_0B30:
  case ID_CUSTOM_OBJECT_0B31:
  case ID_CUSTOM_OBJECT_1B2E:
  case ID_CUSTOM_OBJECT_0B2F:
  case ID_CUSTOM_OBJECT_0B32:
  case ID_CUSTOM_OBJECT_232D:
  case ID_CUSTOM_OBJECT_0B3F:
  case ID_CUSTOM_OBJECT_0B3B:
  case ID_CUSTOM_OBJECT_0B3D:
  case ID_CUSTOM_OBJECT_0B3E:
  case ID_CUSTOM_OBJECT_1195:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_002B:
  case ID_TRIGGER_002A:
  case ID_TRIGGER_0029:
  case ID_TRIGGER_0028:
  case ID_TRIGGER_0027:
  case ID_TRIGGER_0025:
  case ID_TRIGGER_0026:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0024:
  case ID_TRIGGER_0021:
  case ID_TRIGGER_0023:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_0022:
  case ID_TRIGGER_002C:
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
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_002B;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_002A;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_0029;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_0028;

  if (trigger_room == Trigger_rooms[29] && trigger_face == Trigger_faces[29])
    return ID_TRIGGER_0027;

  if (trigger_room == Trigger_rooms[30] && trigger_face == Trigger_faces[30])
    return ID_TRIGGER_0025;

  if (trigger_room == Trigger_rooms[31] && trigger_face == Trigger_faces[31])
    return ID_TRIGGER_0026;

  if (trigger_room == Trigger_rooms[32] && trigger_face == Trigger_faces[32])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[33] && trigger_face == Trigger_faces[33])
    return ID_TRIGGER_0024;

  if (trigger_room == Trigger_rooms[34] && trigger_face == Trigger_faces[34])
    return ID_TRIGGER_0021;

  if (trigger_room == Trigger_rooms[35] && trigger_face == Trigger_faces[35])
    return ID_TRIGGER_0023;

  if (trigger_room == Trigger_rooms[36] && trigger_face == Trigger_faces[36])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[37] && trigger_face == Trigger_faces[37])
    return ID_TRIGGER_0022;

  if (trigger_room == Trigger_rooms[38] && trigger_face == Trigger_faces[38])
    return ID_TRIGGER_002C;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[35];
  static int cust_id_list[35] = {
      ID_CUSTOM_OBJECT_2109, ID_CUSTOM_OBJECT_206D, ID_CUSTOM_OBJECT_306C, ID_CUSTOM_OBJECT_1869,
      ID_CUSTOM_OBJECT_186A, ID_CUSTOM_OBJECT_184A, ID_CUSTOM_OBJECT_4049, ID_CUSTOM_OBJECT_0961,
      ID_CUSTOM_OBJECT_0960, ID_CUSTOM_OBJECT_095F, ID_CUSTOM_OBJECT_095E, ID_CUSTOM_OBJECT_3072,
      ID_CUSTOM_OBJECT_406F, ID_CUSTOM_OBJECT_0B3C, ID_CUSTOM_OBJECT_1338, ID_CUSTOM_OBJECT_1337,
      ID_CUSTOM_OBJECT_1339, ID_CUSTOM_OBJECT_133A, ID_CUSTOM_OBJECT_1B35, ID_CUSTOM_OBJECT_1B34,
      ID_CUSTOM_OBJECT_1B41, ID_CUSTOM_OBJECT_1336, ID_CUSTOM_OBJECT_6856, ID_CUSTOM_OBJECT_0B40,
      ID_CUSTOM_OBJECT_0B30, ID_CUSTOM_OBJECT_0B31, ID_CUSTOM_OBJECT_1B2E, ID_CUSTOM_OBJECT_0B2F,
      ID_CUSTOM_OBJECT_0B32, ID_CUSTOM_OBJECT_232D, ID_CUSTOM_OBJECT_0B3F, ID_CUSTOM_OBJECT_0B3B,
      ID_CUSTOM_OBJECT_0B3D, ID_CUSTOM_OBJECT_0B3E, ID_CUSTOM_OBJECT_1195};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[15];
  cust_handle_list[1] = Object_handles[16];
  cust_handle_list[2] = Object_handles[17];
  cust_handle_list[3] = Object_handles[18];
  cust_handle_list[4] = Object_handles[20];
  cust_handle_list[5] = Object_handles[21];
  cust_handle_list[6] = Object_handles[23];
  cust_handle_list[7] = Object_handles[24];
  cust_handle_list[8] = Object_handles[25];
  cust_handle_list[9] = Object_handles[26];
  cust_handle_list[10] = Object_handles[27];
  cust_handle_list[11] = Object_handles[28];
  cust_handle_list[12] = Object_handles[30];
  cust_handle_list[13] = Object_handles[31];
  cust_handle_list[14] = Object_handles[39];
  cust_handle_list[15] = Object_handles[38];
  cust_handle_list[16] = Object_handles[37];
  cust_handle_list[17] = Object_handles[36];
  cust_handle_list[18] = Object_handles[35];
  cust_handle_list[19] = Object_handles[34];
  cust_handle_list[20] = Object_handles[33];
  cust_handle_list[21] = Object_handles[32];
  cust_handle_list[22] = Object_handles[10];
  cust_handle_list[23] = Object_handles[51];
  cust_handle_list[24] = Object_handles[66];
  cust_handle_list[25] = Object_handles[67];
  cust_handle_list[26] = Object_handles[68];
  cust_handle_list[27] = Object_handles[69];
  cust_handle_list[28] = Object_handles[70];
  cust_handle_list[29] = Object_handles[71];
  cust_handle_list[30] = Object_handles[72];
  cust_handle_list[31] = Object_handles[73];
  cust_handle_list[32] = Object_handles[74];
  cust_handle_list[33] = Object_handles[75];
  cust_handle_list[34] = Object_handles[11];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 35;
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

    // Script 095: Sounds Start
    if (1) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[0], 1.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[1], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[2], 1.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[3], 1.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[4], 1.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[5], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[6], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[7], 1.000000f);
      aSoundPlayObject(Sound_indexes[6], Object_handles[8], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }

    // Script 000: Level Start
    if (1 == true) {
      aMusicSetRegion(0, Object_handles[9]);
      aUserVarSet(5, 0.000000f);
      aUserVarSet(6, 0.000000f);
      aObjGhostSet(1, Object_handles[10]);
      aObjGhostSet(1, Object_handles[11]);
      aObjGhostSet(1, Object_handles[12]);
      aObjGhostSet(1, Object_handles[13]);
      aObjGhostSet(1, Object_handles[14]);
      aSetLevelTimer(15.000000f, 1);
      aSoundPlaySteaming("VoxIntroPilotSeanC.osf", 1.000000f);
      aRainTurnOn(0.900000f);
      aLightningTurnOn(2.000000f, 0.100000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 071: IntroCam
    if (1 == true) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[9], Path_indexes[1], 15.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }

    // Script 002: Start Spewers!
    if (1) {
      aTurnOnSpew(Object_handles[52], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f,
                  2.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[53], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f,
                  4.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[54], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f,
                  5.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[55], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f,
                  3.000000f, 20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[56], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f, 2.400000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[57], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f, 3.000000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[58], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[59], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[60], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[61], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[62], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[63], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[64], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[65], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 098: DeadRobotStuff
    if (1) {
      aObjSetShields(Object_handles[76], 35.000000f);
      aObjSetShields(Object_handles[77], 45.000000f);
      aObjSetShields(Object_handles[78], 55.000000f);
      aObjSetShields(Object_handles[79], 45.000000f);
      aTurnOnSpew(Object_handles[78], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f, 2.000000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[79], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f, 2.000000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[77], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f, 2.000000f,
                  15.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 020: RadioAll
    if (event_data->id == 0) {
      aGoalCompleted(Goal_indexes[0], 1);
      aRoomSetFaceTexture(Room_indexes[3], 42, Texture_indexes[4]);
      aPortalRenderSet(0, 0, Room_indexes[4], 1);
      aShowHUDMessage(Message_strings[6]);
      aShowHUDMessage(Message_strings[7]);
      aUserVarSet(4, 1.000000f);
      aSoundPlaySteaming("VoxDispatcher.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 027: Toggle INIT
    if (event_data->id == 1) {
      aMusicSetRegion(1, Object_handles[9]);
      aUserVarSet(3, 0.000000f);
      aUserVarSet(2, 1.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(0, 0.000000f);
      aObjPlayAnim(Object_handles[24], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[27], 0, 1, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 031: All 12 Cuplinks
    if (event_data->id == 2) {
      aShowHUDMessage(Message_strings[10]);
      aObjSetLightingDist(Object_handles[32], 25.000000f);
      aObjSetLightingDist(Object_handles[33], 25.000000f);
      aObjSetLightingDist(Object_handles[34], 25.000000f);
      aObjSetLightingDist(Object_handles[35], 25.000000f);
      aObjSetLightingDist(Object_handles[36], 25.000000f);
      aObjSetLightingDist(Object_handles[37], 25.000000f);
      aObjSetLightingDist(Object_handles[38], 25.000000f);
      aObjSetLightingDist(Object_handles[39], 25.000000f);
      aRoomSetLightingPulse(Room_indexes[5], 12.000000f, 0.000000f);
      aRoomSetLightingPulse(Room_indexes[6], 12.000000f, 0.000000f);
      aRoomSetLightingPulse(Room_indexes[7], 12.000000f, 0.000000f);
      aRoomSetLightingPulse(Room_indexes[8], 12.000000f, 0.000000f);
      aRoomSetLightingPulse(Room_indexes[9], 12.000000f, 0.000000f);
      aRoomSetLightingPulse(Room_indexes[10], 12.000000f, 0.000000f);
      aRoomSetLightingPulse(Room_indexes[11], 12.000000f, 0.000000f);
      aPortalRenderSet(0, 2, Room_indexes[5], 1);
      aPortalRenderSet(0, 3, Room_indexes[5], 1);
      aPortalRenderSet(0, 8, Room_indexes[12], 1);
      aSetObjectTimer(Object_handles[32], 5.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 072: Virus Housing
    if ((ScriptActionCtr_072 < 1) && (event_data->id == 5)) {
      aObjMakeVulnerable(Object_handles[11]);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }

    // Script 039: VirusRoomEnter Timer
    if ((ScriptActionCtr_039 < 1) && (event_data->id == 3)) {
      aSoundPlayObject(Sound_indexes[9], Object_handles[48], 1.000000f);
      aObjPlayAnim(Object_handles[48], 0, 2, 5.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 044: CuplinkCamTimer
    if ((ScriptActionCtr_044 < 1) && (event_data->id == 6)) {
      aAISetTeam(196608, Object_handles[50]);
      aCinematicSimple(Path_indexes[3], Message_strings[13], Object_handles[51], 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 046: EndTimer
    if ((ScriptActionCtr_046 < 1) && (event_data->id == 4)) {
      if ((ScriptActionCtr_020 > 0) == true) {
        aObjGhostSet(0, Object_handles[12]);
        aObjGhostSet(0, Object_handles[13]);
        aObjGhostSet(0, Object_handles[14]);
        aAIGoalFollowPathSimple(Object_handles[14], Path_indexes[4], 4352, -1);
        aAIGoalFollowPathSimple(Object_handles[13], Path_indexes[5], 4352, -1);
        aAIGoalFollowPathSimple(Object_handles[12], Path_indexes[6], 4352, -1);
      }
      aStartEndlevelSequencePath(Path_indexes[7], Path_indexes[8], 8.000000f, Message_strings[14]);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2109::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Goodie Switch hit
    if ((ScriptActionCtr_001 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == 1)) {
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aPortalRenderSet(0, 1, Room_indexes[0], 1);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_206D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: First Outdoor ForceField Switch
    if ((ScriptActionCtr_004 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aLightningTurnOn(0.300000f, 0.080000f);
      aRainTurnOn(0.900000f);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_306C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 005: Outdoor Tank Killed
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1869::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: KeyCard2
    if ((ScriptActionCtr_016 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_015 > 0) == true) {
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
        aCreatePopupView(0, Object_handles[19], 8.000000f, 1.000000f);
        aShowHUDMessage(Message_strings[2]);
      } else {
        aShowHUDMessage(Message_strings[3]);
      }
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_186A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: KeyCard1
    if ((ScriptActionCtr_015 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_016 > 0) == true) {
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
        aCreatePopupView(0, Object_handles[19], 8.000000f, 1.000000f);
        aShowHUDMessage(Message_strings[2]);
      } else {
        aShowHUDMessage(Message_strings[3]);
      }
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_184A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: RadioDoorLock2
    if ((ScriptActionCtr_009 < 1) && (1)) {
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      if ((ScriptActionCtr_017 > 0) == true) {
        aMatcenSetState(1, Matcen_indexes[0]);
        aCreatePopupView(0, Object_handles[22], 8.000000f, 1.000000f);
        aShowHUDMessage(Message_strings[4]);
        aDoorLockUnlock(0, Door_handles[1]);
        aDoorSetPos(Door_handles[1], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[5]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_4049::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: RadioDoorLock1
    if ((ScriptActionCtr_017 < 1) && (1)) {
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      if ((ScriptActionCtr_009 > 0) == true) {
        aMatcenSetState(1, Matcen_indexes[0]);
        aCreatePopupView(0, Object_handles[22], 8.000000f, 1.000000f);
        aShowHUDMessage(Message_strings[4]);
        aDoorLockUnlock(0, Door_handles[1]);
        aDoorSetPos(Door_handles[1], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[5]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0961::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Toggle4
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) &&
        ((qUserVarValue(3) == 0.000000f) || (qUserVarValue(3) == 1.000000f)) && (qUserVarValue(4) == 0.000000f)) {
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      if (qUserVarValue(3) == 0.000000f) {
        aRoomSetFaceTexture(Room_indexes[3], 212, Texture_indexes[0]);
        aUserVarSet(3, 2.000000f);
        aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
        if (qUserVarValue(2) > 0.000000f) {
          if ((qUserVarValue(0) > 0.000000f) && (qUserVarValue(1) > 0.000000f)) {
            aSetLevelTimer(0.000000f, 0);
          }
          aRoomSetFaceTexture(Room_indexes[3], 22, Texture_indexes[1]);
        }
      } else {
        aRoomSetFaceTexture(Room_indexes[3], 22, Texture_indexes[2]);
        aRoomSetFaceTexture(Room_indexes[3], 212, Texture_indexes[3]);
        aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
        aUserVarSet(3, -1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 026: Toggle4Timer
    if (1) {
      if (qUserVarValue(3) == 2.000000f) {
        aUserVarSet(3, 1.000000f);
      } else {
        aUserVarSet(3, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0960::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Toggle3
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) &&
        ((qUserVarValue(2) == 0.000000f) || (qUserVarValue(2) == 1.000000f)) && (qUserVarValue(4) == 0.000000f)) {
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      if (qUserVarValue(2) == 0.000000f) {
        aRoomSetFaceTexture(Room_indexes[3], 223, Texture_indexes[0]);
        aUserVarSet(2, 2.000000f);
        aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
        if (qUserVarValue(3) > 0.000000f) {
          if ((qUserVarValue(0) > 0.000000f) && (qUserVarValue(1) > 0.000000f)) {
            aSetLevelTimer(0.000000f, 0);
          }
          aRoomSetFaceTexture(Room_indexes[3], 22, Texture_indexes[1]);
        }
      } else {
        aRoomSetFaceTexture(Room_indexes[3], 22, Texture_indexes[2]);
        aRoomSetFaceTexture(Room_indexes[3], 223, Texture_indexes[3]);
        aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
        aUserVarSet(2, -1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 025: Toggle3Timer
    if (1) {
      if (qUserVarValue(2) == 2.000000f) {
        aUserVarSet(2, 1.000000f);
      } else {
        aUserVarSet(2, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_095F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Toggle2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) &&
        ((qUserVarValue(1) == 0.000000f) || (qUserVarValue(1) == 1.000000f)) && (qUserVarValue(4) == 0.000000f)) {
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      if (qUserVarValue(1) == 0.000000f) {
        aRoomSetFaceTexture(Room_indexes[3], 201, Texture_indexes[3]);
        aUserVarSet(1, 2.000000f);
        aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
        if (qUserVarValue(0) > 0.000000f) {
          if ((qUserVarValue(2) > 0.000000f) && (qUserVarValue(3) > 0.000000f)) {
            aSetLevelTimer(0.000000f, 0);
          }
          aRoomSetFaceTexture(Room_indexes[3], 9, Texture_indexes[1]);
        }
      } else {
        aRoomSetFaceTexture(Room_indexes[3], 9, Texture_indexes[2]);
        aRoomSetFaceTexture(Room_indexes[3], 201, Texture_indexes[0]);
        aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
        aUserVarSet(1, -1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 024: Toggle2Timer
    if (1) {
      if (qUserVarValue(1) == 2.000000f) {
        aUserVarSet(1, 1.000000f);
      } else {
        aUserVarSet(1, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_095E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Toggle1
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) &&
        ((qUserVarValue(0) == 0.000000f) || (qUserVarValue(0) == 1.000000f)) && (qUserVarValue(4) == 0.000000f)) {
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      if (qUserVarValue(0) == 0.000000f) {
        aRoomSetFaceTexture(Room_indexes[3], 190, Texture_indexes[0]);
        aUserVarSet(0, 2.000000f);
        aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
        if (qUserVarValue(1) > 0.000000f) {
          if ((qUserVarValue(2) > 0.000000f) && (qUserVarValue(3) > 0.000000f)) {
            aSetLevelTimer(0.000000f, 0);
          }
          aRoomSetFaceTexture(Room_indexes[3], 9, Texture_indexes[1]);
        }
      } else {
        aRoomSetFaceTexture(Room_indexes[3], 9, Texture_indexes[2]);
        aRoomSetFaceTexture(Room_indexes[3], 190, Texture_indexes[3]);
        aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
        aUserVarSet(0, -1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 019: Toggle1Timer
    if (1) {
      if (qUserVarValue(0) == 2.000000f) {
        aUserVarSet(0, 1.000000f);
      } else {
        aUserVarSet(0, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3072::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: MatcenDoorSwitch2
    if ((ScriptActionCtr_028 < 1) && (1)) {
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      if ((ScriptActionCtr_029 > 0) == true) {
        aCreatePopupView(0, Object_handles[29], 8.000000f, 1.000000f);
        aMatcenSetState(1, Matcen_indexes[1]);
        aShowHUDMessage(Message_strings[8]);
        aDoorLockUnlock(0, Door_handles[2]);
        aDoorSetPos(Door_handles[2], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[9]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_406F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: MatcenDoorSwitch1
    if ((ScriptActionCtr_029 < 1) && (1)) {
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      if ((ScriptActionCtr_028 > 0) == true) {
        aCreatePopupView(0, Object_handles[29], 8.000000f, 1.000000f);
        aMatcenSetState(1, Matcen_indexes[1]);
        aShowHUDMessage(Message_strings[8]);
        aDoorLockUnlock(0, Door_handles[2]);
        aDoorSetPos(Door_handles[2], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[9]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B3C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 040: TempDestroy
    if ((ScriptActionCtr_040 < 1) && (qUserVarValue(5) == 12.000000f)) {
      aSetLevelTimer(0.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 003: BunkChildDestroyed1
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1338::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 038: Exp8
    if (1) {
      aTurnOnSpew(Object_handles[40], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1337::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 037: Exp7
    if (1) {
      aTurnOnSpew(Object_handles[41], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[39], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1339::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 036: Exp6
    if (1) {
      aTurnOnSpew(Object_handles[42], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[38], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_133A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 035: Exp5
    if (1) {
      aTurnOnSpew(Object_handles[43], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[37], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1B35::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 034: Exp4
    if (1) {
      aTurnOnSpew(Object_handles[44], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[36], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1B34::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 033: Exp3
    if (1) {
      aTurnOnSpew(Object_handles[45], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[35], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1B41::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 032: Exp2
    if (1) {
      aTurnOnSpew(Object_handles[46], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[34], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1336::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 030: Exp1
    if (1) {
      aTurnOnSpew(Object_handles[47], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  2.500000f, 18.000000f, 0, -1);
      aSetObjectTimer(Object_handles[33], 5.000000f, -1);
      aObjSetShields(data->me_handle, 500.000000f);
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_6856::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: VirusPickup
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if ((ScriptActionCtr_020 > 0) == true) {
        aSoundPlaySteaming("VoxCGCaptain.osf", 1.000000f);
      }
      aGoalCompleted(Goal_indexes[1], 1);
      aGoalCompleted(Goal_indexes[2], 1);
      aShowHUDMessage(Message_strings[12]);
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B40::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 043: NowAttack
    if (1) {
      aAISetTeam(0, Object_handles[50]);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 062: BunkChildDestroyed5
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B30::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 069: BunkChildDestroyed12
    if (1) {
      aShowHUDMessage(Message_strings[15]);
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B31::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 068: BunkChildDestroyed11
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1B2E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 067: BunkChildDestroyed10
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B2F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 066: BunkChildDestroyed9
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B32::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 065: BunkChildDestroyed8
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_232D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 064: BunkChildDestroyed7
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B3F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 063: BunkChildDestroyed6
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B3B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 061: BunkChildDestroyed4
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B3D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 060: BunkChildDestroyed3
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0B3E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 006: BunkChildDestroyed2
    if (1) {
      aUserVarInc(5);
      aSetObjectTimer(Object_handles[31], 0.000000f, -1);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1195::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 070: AttachVirus
    if ((ScriptActionCtr_070 < 1) && (1)) {
      aAttachExistingObject(Object_handles[10], 0, Object_handles[48], 0);
      aObjGhostSet(0, Object_handles[10]);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Waypoint8
    if (1) {
      aSetWaypoint(8);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Waypoint7
    if (1) {
      aSetWaypoint(7);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }

    // Script 086: Music-3Out
    if (1) {
      aMusicSetRegion(8, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Waypoint6
    if (1) {
      aSetWaypoint(6);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 084: Music-Ancient1
    if (1) {
      aMusicSetRegion(7, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Waypoint5
    if (1) {
      aSetWaypoint(5);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Waypoint4
    if (1) {
      aSetWaypoint(4);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Waypoint2
    if (1) {
      aSetWaypoint(2);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Waypoint1
    if (1) {
      aSetWaypoint(1);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: VirusRoomEnter Trigger
    if ((ScriptActionCtr_042 < 1) && ((ScriptActionCtr_031 > 0) == true)) {
      aObjMakeInvuln(Object_handles[11], 10);
      aAttachExistingObject(Object_handles[11], 0, Object_handles[48], 0);
      aObjGhostSet(0, Object_handles[11]);
      aCinematicSimple(Path_indexes[2], Message_strings[11], Object_handles[49], 10.000000f);
      aSetLevelTimer(3.000000f, 3);
      aSetLevelTimer(10.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 101: CuplinkCam2
    if ((ScriptActionCtr_101 < 1) && (1)) {
      aSetLevelTimer(0.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }

    // Script 093: Music-Alien2
    if (1) {
      aMusicSetRegion(9, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 100: CuplinkCam3
    if ((ScriptActionCtr_100 < 1) && (1)) {
      aSetLevelTimer(0.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }

    // Script 094: Music-Alien3
    if (1) {
      aMusicSetRegion(9, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 099: CuplinkCam1
    if ((ScriptActionCtr_099 < 1) && (1)) {
      aSetLevelTimer(0.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }

    // Script 092: Music-Alien1
    if (1) {
      aMusicSetRegion(9, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: EndExit4
    if ((ScriptActionCtr_041 > 0) == true) {
      aSetLevelTimer(0.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 090: Music-3Out4
    if (1) {
      aMusicSetRegion(8, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: EndExit3
    if ((ScriptActionCtr_041 > 0) == true) {
      aSetLevelTimer(0.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }

    // Script 089: Music-3Out3
    if (1) {
      aMusicSetRegion(8, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: EndExit2
    if ((ScriptActionCtr_041 > 0) == true) {
      aSetLevelTimer(0.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 088: Music-3Out2
    if (1) {
      aMusicSetRegion(8, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: EndExit1
    if ((ScriptActionCtr_041 > 0) == true) {
      aSetLevelTimer(0.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 087: Music-3Out1
    if (1) {
      aMusicSetRegion(8, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Voice Trigger 10
    if ((ScriptActionCtr_059 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompIntruderB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Voice Trigger 9
    if ((ScriptActionCtr_058 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompIntruderA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Voice Trigger 8
    if ((ScriptActionCtr_057 < 1) && (1)) {
      aSoundPlaySteaming("VoxMaleAnnouncementB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Voice Trigger 7
    if ((ScriptActionCtr_056 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompPowerDamage.osf", 1.000000f);

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

    // Script 055: Voice Computer
    if ((ScriptActionCtr_055 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompComDatalink.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Voice Trigger 5
    if ((ScriptActionCtr_054 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompIrreguler.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 096: Music-Datlink
    if (1) {
      aMusicSetRegion(4, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Voice Trigger 6
    if ((ScriptActionCtr_053 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompEmergencyB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Voice Trigger 3
    if ((ScriptActionCtr_052 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompEmergencyA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Voice Trigger 2
    if ((ScriptActionCtr_051 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompSecurityLockdown.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: Voice Trigger 1
    if ((ScriptActionCtr_050 < 1) && (1)) {
      aSoundPlaySteaming("VoxMaleAnnouncementA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 091: Music-Alien
    if (1) {
      aMusicSetRegion(9, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Music-Ancient2
    if (1) {
      aMusicSetRegion(7, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0029::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Music-2Out2
    if (1) {
      aMusicSetRegion(6, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0028::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: Music-2Out
    if (1) {
      aMusicSetRegion(6, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0027::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Music-Cave2
    if (1) {
      aMusicSetRegion(5, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Music-Cave
    if (1) {
      aMusicSetRegion(5, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0026::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: Music-2InPt22
    if (1) {
      aMusicSetRegion(10, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: Music-2InPt2
    if (1) {
      aMusicSetRegion(10, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0024::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Music-2In2
    if (1) {
      aMusicSetRegion(3, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Music-2In1
    if (1) {
      aMusicSetRegion(3, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0023::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 075: Music-1Out2
    if (1) {
      aMusicSetRegion(2, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music-1Out
    if (1) {
      aMusicSetRegion(2, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: Music-1In
    if (1) {
      aMusicSetRegion(1, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_002C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 097: Music-2InDat
    if (1) {
      aMusicSetRegion(3, Object_handles[9]);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
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
NEXT_ID		102

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:RadioToggle1
1:RadioToggle2
2:RadioToggle3
3:RadioToggle4
4:RadioAll
5:Bunks
6:BlewItUp
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:All4Radio
1:RadioINIT
2:12Cuplinks
3:VirusTerminal
4:EndLevel
5:MakeHousing
6:Cuplinkcam
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
KeyDoor
RadioDoor
MatcenDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
AlienVirusStand
BigPipeKey2
DatlinkCenter
ComputerPole2
ComputerPole1
GiantPipeRoom
LavaPlane
YellowBlueTurbine
FirstBigMachine
PlayerShip
Virus
Virushouse
RescueShip1
RescueShip2
RescueShip3
GoodieRoomSwitch
FirstOutsideDoorSw
OutdoorKillTank
KeyCard2
SecurityDoor
KeyCard1
RadioDoorSwitch2
RadioCam
RadioDoorSwitch1
RadioToggle4
RadioToggle3
RadioToggle2
RadioToggle1
MatcenSwitch2
MatcenCam
MatcenSwitch1
BunkBed1
Exp1
Exp2
Exp3
Exp4
Exp5
Exp6
Exp7
Exp8
UFODestroy4
UFOSmoke4
UFODestroy3
UFOSmoke3
UFODestroy2
UFOSmoke2
UFODestroy1
UFOSmoke1
VirusTerminal
VirusCamTarget
DontAttackTail
BunkBed5
Lava7
Lava5
Lava3
Lava1
SBlackSmall
BottomSpewer
SWhite2
SWhite1
SBlackGravity4
SBlackGravity3
SBlackGravity2
SBlackGravity1
SWhiteGravity2
SWhiteGravity1
BunkBed12
BunkBed11
BunkBed10
BunkBed9
BunkBed8
BunkBed7
BunkBed6
BunkBed4
BunkBed3
BunkBed2
DStringer1
DTubbs3
DTubbs2
DTubbs1
$$OBJECT_LIST_END

$$ROOM_LIST_START
GoodiePortalRoom
FirstOutdoorPortal
ReturnInsideRoom
RadioRoom
RadioArmory
Alien1
Alien2
Alien3
Alien4
Alien5
Alien6
Alien7
VirusRoom
$$ROOM_LIST_END

$$TRIGGER_LIST_START
Waypoint8
Waypoint7
Waypoint6
Waypoint5
Waypoint4
Waypoint2
Waypoint1
VirusEnter
CuplinkCam2
CuplinkCam3
CuplinkCam1
Exit4
Exit3
Exit2
Exit1
Voice10
Voice9
Voice8
Voice7
Voice-Computer
Voice5
Voice6
Voice3
Voice2
Voice1
Music-Alien
Music-Ancient
Music-2Out2
Music-2Out1
Music-Cave2
Music-Cave1
Music-2InPt22
Music-2InPart2
Music-2In2
Music-2In
Music-1Out2
Music-1Out
Music-1In
Music-2InDat
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbDroneP
AmbDroneE
AmbDroneD
AmbDroneX
AmbLavaLoop1
AmbDroneN
AmbDroneK
AmbSwitch31
PupC1
AmbVirusSwitch
$$SOUND_LIST_END

$$TEXTURE_LIST_START
Reddataup
Ready1
Notready
Staticscrolling
Online
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
VirusCam
CupLinkCam
Rescuer3
Rescuer2
Rescuer1
EndCam
EndLevelCam
$$PATH_LIST_END

$$MATCEN_LIST_START
DatlinkMatcen
TwoSwitchMatcen
$$MATCEN_LIST_END

$$GOAL_LIST_START
Activate Datlink
Acquire the alien virus
Retrieve the Alien Virus
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxIntroPilotSeanC.osf
VoxDispatcher.osf
VoxCGCaptain.osf
VoxCompIntruderB.osf
VoxCompIntruderA.osf
VoxMaleAnnouncementB.osf
VoxCompPowerDamage.osf
VoxCompComDatalink.osf
VoxCompIrreguler.osf
VoxCompEmergencyB.osf
VoxCompEmergencyA.osf
VoxCompSecurityLockdown.osf
VoxMaleAnnouncementA.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:95:Sounds Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:2:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:3:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:4:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:5:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:6:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:7:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:8:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Level Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aRainTurnOn
                        $$CHILD_BLOCK_START
                        10:9:0.900000:Density
                        $$CHILD_BLOCK_END
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Seconds
                        10:9:0.100000:Probability
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:IntroCam
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:9:Target
                        10:16:1:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Goodie Switch hit
        $$CHILD_BLOCK_START
        01:1:15
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForceFieldDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:First Outdoor ForceField Switch
        $$CHILD_BLOCK_START
        01:1:16
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
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:0.300000:Seconds
                        10:9:0.080000:Probability
                        $$CHILD_BLOCK_END
                08:aRainTurnOn
                        $$CHILD_BLOCK_START
                        10:9:0.900000:Density
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForceFieldDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Outdoor Tank Killed
        $$CHILD_BLOCK_START
        01:1:17
        02:4
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
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForceFieldDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Waypoint8
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:8:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Waypoint7
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:7:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Waypoint6
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:6:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Waypoint5
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:5:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Waypoint4
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Waypoint2
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:2:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Waypoint1
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:KeyCard2
        $$CHILD_BLOCK_START
        01:1:18
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:15:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:19:Object
                                10:6:8.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:2KeyCards:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:1KeyCard:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:KeyCard1
        $$CHILD_BLOCK_START
        01:1:20
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:16:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:19:Object
                                10:6:8.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:2KeyCards:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:1KeyCard:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:RadioDoorLock2
        $$CHILD_BLOCK_START
        01:1:21
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:17:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:22:Object
                                10:6:8.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RadioRoomUnlock:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RadioRoomFirst:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:RadioDoorLock1
        $$CHILD_BLOCK_START
        01:1:23
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
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
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:22:Object
                                10:6:8.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RadioRoomUnlock:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RadioRoomFirst:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Toggle4
        $$CHILD_BLOCK_START
        01:1:24
        02:0
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
                        09:1
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
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
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:212:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
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
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:3:Room
                                        10:4:22:FaceNum
                                        10:14:1:Texture
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:22:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:212:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                10:6:-1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Toggle3
        $$CHILD_BLOCK_START
        01:1:25
        02:0
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
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:223:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
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
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
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
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:3:Room
                                        10:4:22:FaceNum
                                        10:14:1:Texture
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:22:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:223:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:-1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Toggle2
        $$CHILD_BLOCK_START
        01:1:26
        02:0
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
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:201:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:2:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:3:Room
                                        10:4:9:FaceNum
                                        10:14:1:Texture
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:9:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:201:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:-1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Toggle1
        $$CHILD_BLOCK_START
        01:1:27
        02:0
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
                        09:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
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
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:190:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:2:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:2
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.000000:Time
                                                10:10:0:0:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:3:Room
                                        10:4:9:FaceNum
                                        10:14:1:Texture
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:9:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:190:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:-1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Toggle4Timer
        $$CHILD_BLOCK_START
        01:1:24
        02:9
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Toggle3Timer
        $$CHILD_BLOCK_START
        01:1:25
        02:9
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Toggle2Timer
        $$CHILD_BLOCK_START
        01:1:26
        02:9
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Toggle1Timer
        $$CHILD_BLOCK_START
        01:1:27
        02:9
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:RadioAll
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:42:FaceNum
                        10:14:4:Texture
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:All4Radio:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:All4Radio2:Message
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Toggle INIT
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:MatcenDoorSwitch2
        $$CHILD_BLOCK_START
        01:1:28
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:29:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:29:Object
                                10:6:8.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TwoSwitchUnlock:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TwoSwitchFirst:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:MatcenDoorSwitch1
        $$CHILD_BLOCK_START
        01:1:30
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:28:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:29:Object
                                10:6:8.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TwoSwitchUnlock:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TwoSwitchFirst:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:TempDestroy
        $$CHILD_BLOCK_START
        01:1:31
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:6:12.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:All 12 Cuplinks
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        07:1:0
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:AlienCuplinks:Message
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:6:25.000000:Distance
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:12.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:8:PortalNum
                        10:2:12:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Exp8
        $$CHILD_BLOCK_START
        01:1:39
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Exp7
        $$CHILD_BLOCK_START
        01:1:38
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
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
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Exp6
        $$CHILD_BLOCK_START
        01:1:37
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Exp5
        $$CHILD_BLOCK_START
        01:1:36
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Exp4
        $$CHILD_BLOCK_START
        01:1:35
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
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
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Exp3
        $$CHILD_BLOCK_START
        01:1:34
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Exp2
        $$CHILD_BLOCK_START
        01:1:33
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Exp1
        $$CHILD_BLOCK_START
        01:1:32
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:18.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:500.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:VirusRoomEnter Trigger
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:31:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:10:Time
                        $$CHILD_BLOCK_END
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:11:Child
                        10:4:0:ChildPoint
                        10:1:0:48:Parent
                        10:4:0:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:HeresVirus:Text
                        10:1:0:49:Target
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:Virus Housing
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
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:VirusRoomEnter Timer
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
                        10:1:0:48:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:VirusPickup
        $$CHILD_BLOCK_START
        01:1:10
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
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:2:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Virus:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:CuplinkCam2
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:CuplinkCam3
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:CuplinkCam1
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:CuplinkCamTimer
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
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:3:CameraPath
                        10:8:DestroyThese:Text
                        10:1:0:51:Target
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:NowAttack
        $$CHILD_BLOCK_START
        01:1:51
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:EndExit4
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:41:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:EndExit3
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:41:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:EndExit2
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:41:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:EndExit1
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:41:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:EndTimer
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
        04:0:0:1
                $$CHILD_BLOCK_START
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:12:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:13:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:14:Object
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:14:Object
                                10:16:4:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:13:Object
                                10:16:5:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:12:Object
                                10:16:6:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:7:CameraPath
                        10:16:8:PlayerPath
                        10:6:8.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Voice Trigger 10
        $$CHILD_BLOCK_START
        01:0:15
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Voice Trigger 9
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
                        10:19:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Voice Trigger 8
        $$CHILD_BLOCK_START
        01:0:17
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Voice Trigger 7
        $$CHILD_BLOCK_START
        01:0:18
        02:1
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
00:55:Voice Computer
        $$CHILD_BLOCK_START
        01:0:19
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:7:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Voice Trigger 5
        $$CHILD_BLOCK_START
        01:0:20
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:8:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Voice Trigger 6
        $$CHILD_BLOCK_START
        01:0:21
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:9:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Voice Trigger 3
        $$CHILD_BLOCK_START
        01:0:22
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:10:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Voice Trigger 2
        $$CHILD_BLOCK_START
        01:0:23
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:11:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Voice Trigger 1
        $$CHILD_BLOCK_START
        01:0:24
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:12:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Start Spewers!
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.400000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:BunkChildDestroyed12
        $$CHILD_BLOCK_START
        01:1:66
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:BunkChildDestroyed11
        $$CHILD_BLOCK_START
        01:1:67
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:BunkChildDestroyed10
        $$CHILD_BLOCK_START
        01:1:68
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:BunkChildDestroyed9
        $$CHILD_BLOCK_START
        01:1:69
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:BunkChildDestroyed8
        $$CHILD_BLOCK_START
        01:1:70
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:BunkChildDestroyed7
        $$CHILD_BLOCK_START
        01:1:71
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:BunkChildDestroyed6
        $$CHILD_BLOCK_START
        01:1:72
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:BunkChildDestroyed5
        $$CHILD_BLOCK_START
        01:1:51
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:BunkChildDestroyed4
        $$CHILD_BLOCK_START
        01:1:73
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:BunkChildDestroyed3
        $$CHILD_BLOCK_START
        01:1:74
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:BunkChildDestroyed2
        $$CHILD_BLOCK_START
        01:1:75
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:BunkChildDestroyed1
        $$CHILD_BLOCK_START
        01:1:31
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerCupLink:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:AttachVirus
        $$CHILD_BLOCK_START
        01:1:11
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:10:Child
                        10:4:0:ChildPoint
                        10:1:0:48:Parent
                        10:4:0:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Music-Alien3
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
                        10:10:0:9:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Music-Alien2
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
                        10:10:0:9:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Music-Alien1
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
                        10:10:0:9:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Music-Alien
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
                        10:10:0:9:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Music-3Out4
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
                        10:10:0:8:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Music-3Out3
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
                        10:10:0:8:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Music-3Out2
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
                        10:10:0:8:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Music-3Out1
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
                        10:10:0:8:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Music-3Out
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
                        10:10:0:8:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Music-Ancient2
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
                        10:10:0:7:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Music-Ancient1
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
                        10:10:0:7:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Music-2Out2
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
                        10:10:0:6:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Music-2Out
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
                        10:10:0:6:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Music-Cave2
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
                        10:10:0:5:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Music-Cave
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
                        10:10:0:5:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Music-2InPt22
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
                        10:10:0:10:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Music-2InPt2
        $$CHILD_BLOCK_START
        01:0:32
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:10:Region
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Music-2In2
        $$CHILD_BLOCK_START
        01:0:33
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Music-2In1
        $$CHILD_BLOCK_START
        01:0:34
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:Music-1Out2
        $$CHILD_BLOCK_START
        01:0:35
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Music-1Out
        $$CHILD_BLOCK_START
        01:0:36
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Music-1In
        $$CHILD_BLOCK_START
        01:0:37
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Music-Datlink
        $$CHILD_BLOCK_START
        01:0:20
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:Music-2InDat
        $$CHILD_BLOCK_START
        01:0:38
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
                        10:1:0:9:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:DeadRobotStuff
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:6:35.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:6:45.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:6:55.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:6:45.000000:Shields
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
