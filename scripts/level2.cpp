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
// Filename:	Level2.cpp
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

#define ID_CUSTOM_OBJECT_082D 0x001
#define ID_CUSTOM_OBJECT_082E 0x002
#define ID_CUSTOM_OBJECT_082F 0x003
#define ID_CUSTOM_OBJECT_0830 0x004
#define ID_CUSTOM_OBJECT_0831 0x005
#define ID_CUSTOM_OBJECT_2112 0x006
#define ID_CUSTOM_OBJECT_11F2 0x007
#define ID_CUSTOM_OBJECT_11F4 0x008
#define ID_CUSTOM_OBJECT_11F6 0x009
#define ID_CUSTOM_OBJECT_19F7 0x00a
#define ID_CUSTOM_OBJECT_11FB 0x00b
#define ID_CUSTOM_OBJECT_1211 0x00c
#define ID_CUSTOM_OBJECT_0885 0x00d
#define ID_CUSTOM_OBJECT_080D 0x00e
#define ID_CUSTOM_OBJECT_09EC 0x00f
#define ID_CUSTOM_OBJECT_11EB 0x010
#define ID_CUSTOM_OBJECT_19E9 0x011
#define ID_CUSTOM_OBJECT_19E8 0x012
#define ID_CUSTOM_OBJECT_19EA 0x013
#define ID_CUSTOM_OBJECT_09E7 0x014
#define ID_CUSTOM_OBJECT_09E6 0x015
#define ID_CUSTOM_OBJECT_11BB 0x016
#define ID_CUSTOM_OBJECT_09BC 0x017
#define ID_CUSTOM_OBJECT_09BD 0x018
#define ID_CUSTOM_OBJECT_09BE 0x019
#define ID_CUSTOM_OBJECT_11BF 0x01a
#define ID_CUSTOM_OBJECT_09C0 0x01b
#define ID_CUSTOM_OBJECT_11C1 0x01c
#define ID_CUSTOM_OBJECT_11BA 0x01d
#define ID_CUSTOM_OBJECT_09C9 0x01e
#define ID_CUSTOM_OBJECT_09C8 0x01f
#define ID_CUSTOM_OBJECT_09C7 0x020
#define ID_CUSTOM_OBJECT_09C6 0x021
#define ID_CUSTOM_OBJECT_09C5 0x022
#define ID_CUSTOM_OBJECT_09C4 0x023
#define ID_CUSTOM_OBJECT_09C3 0x024
#define ID_CUSTOM_OBJECT_09C2 0x025
#define ID_CUSTOM_OBJECT_094E 0x026

#define ID_TRIGGER_0000 0x027
#define ID_TRIGGER_0001 0x028
#define ID_TRIGGER_0002 0x029
#define ID_TRIGGER_0004 0x02a
#define ID_TRIGGER_0005 0x02b
#define ID_TRIGGER_0003 0x02c
#define ID_TRIGGER_0008 0x02d
#define ID_TRIGGER_0006 0x02e
#define ID_TRIGGER_000C 0x02f
#define ID_TRIGGER_000B 0x030
#define ID_TRIGGER_0007 0x031
#define ID_TRIGGER_000E 0x032
#define ID_TRIGGER_000A 0x033
#define ID_TRIGGER_0009 0x034
#define ID_TRIGGER_0010 0x035
#define ID_TRIGGER_000D 0x036
#define ID_TRIGGER_0014 0x037
#define ID_TRIGGER_0011 0x038
#define ID_TRIGGER_000F 0x039
#define ID_TRIGGER_0016 0x03a
#define ID_TRIGGER_0013 0x03b
#define ID_TRIGGER_0017 0x03c
#define ID_TRIGGER_0018 0x03d
#define ID_TRIGGER_0015 0x03e
#define ID_TRIGGER_0012 0x03f
#define ID_TRIGGER_0020 0x040
#define ID_TRIGGER_001F 0x041
#define ID_TRIGGER_001E 0x042

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

class CustomObjectScript_082D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_082E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_082F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0830 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0831 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2112 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11F2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11F4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11F6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19F7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11FB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1211 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0885 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09EC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11EB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19E9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19E8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19EA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09E7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09E6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11BB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11BF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11C1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11BA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_094E : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
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

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000E : public BaseScript {
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

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0014 : public BaseScript {
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

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_112 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_112 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:IntroCave
1:StartArea
2:Terrain
3:AfterForcefield
4:AcidCaves
5:OutOfCaves
6:Minimum
7:Medium
8:Maximum
9:Final
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

#define NUM_DOOR_NAMES 2
static const char *const Door_names[NUM_DOOR_NAMES] = {"DockingDoor", "MinimumLevelServic"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 90
static const char *const Object_names[NUM_OBJECT_NAMES] = {"RescueShuttle",
                                                           "PerimeterTurretA",
                                                           "PerimeterTurretB",
                                                           "PerimeterTurretC",
                                                           "PerimeterTurretD",
                                                           "PerimeterTurretE",
                                                           "UpperTowerForcefie",
                                                           "InnerTowerForcefie",
                                                           "SweitzerActor",
                                                           "ShuttleFFStartPos",
                                                           "RescueShuttleDocki",
                                                           "SweitzerMIN",
                                                           "ShuttleFFTarget",
                                                           "ShuttleTunnelPos",
                                                           "ShuttleTunnelTarge",
                                                           "ShuttleCellPos",
                                                           "ShuttleCellTarget",
                                                           "ShuttleInCellTarge",
                                                           "ShuttleCellTarget2",
                                                           "EndShuttlePos",
                                                           "DockingDoor",
                                                           "X-1OldSecurityPass",
                                                           "R-1MaximumSecurity",
                                                           "G-1MinimumSecurity",
                                                           "Y-1MediumSecurityP",
                                                           "HangarRASAlarmGuy",
                                                           "CheckpointMinTubbs",
                                                           "CheckpointMedTubbs",
                                                           "CheckpointMaxTubbs",
                                                           "MaxCheckCamA",
                                                           "MaxCheckCamB",
                                                           "MedCheckCamA",
                                                           "MedCheckCamB",
                                                           "MinCheckCamA",
                                                           "MinCheckCamB",
                                                           "ChemicalBotStartSw",
                                                           "ChemicalBotKILLSwi",
                                                           "AcidVatSpewerA",
                                                           "AcidVatSpewerB",
                                                           "AcidVatSpewerC",
                                                           "ChemicalControlCam",
                                                           "AcidVatCamera",
                                                           "SirenCamA",
                                                           "SirenCamB",
                                                           "SirenCamC",
                                                           "SirenCamD",
                                                           "SirenCamE",
                                                           "SirenCamF",
                                                           "SirenCamG",
                                                           "SirenCamH",
                                                           "SirenCamI",
                                                           "SirenCamJ",
                                                           "MinMan1",
                                                           "MinMan2",
                                                           "MinMan3",
                                                           "MinMan4",
                                                           "MinMan5",
                                                           "MinMan6",
                                                           "MinMan7",
                                                           "MinMan8",
                                                           "SweitMaxLocator",
                                                           "SweitMinLocator",
                                                           "SweitzerMAX",
                                                           "MaxMan1",
                                                           "MaxMan2",
                                                           "MaxMan3",
                                                           "MaxMan4",
                                                           "MaxMan5",
                                                           "MaxMan6",
                                                           "MaxMan7",
                                                           "MaxMan8",
                                                           "RecordsNodeH",
                                                           "RecordsNodeG",
                                                           "RecordsNodeF",
                                                           "RecordsNodeE",
                                                           "RecordsNodeD",
                                                           "RecordsNodeC",
                                                           "RecordsNodeB",
                                                           "RecordsNodeA",
                                                           "RecordsNodeP",
                                                           "RecordsNodeO",
                                                           "RecordsNodeN",
                                                           "RecordsNodeM",
                                                           "RecordsNodeL",
                                                           "RecordsNodeK",
                                                           "RecordsNodeJ",
                                                           "RecordsNodeI",
                                                           "PrisonRecordsCompu",
                                                           "TubbsSentryA",
                                                           "TubbsSentryB"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 59
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "SupplyHangarEntran", "InnerTowerForcefie", "PrisonerTransferHa", "R-1MaximumSecurity", "MaximumSecurityChe",
    "Y-1MediumSecurityP", "MediumSecurityChec", "G-1MinimumSecurity", "MinimumSecurityChe", "KILLroom",
    "AcidVatRoom",        "LowerInnerTowerMat", "ChemicalControlCen", "LowerInnerTowerSha", "LowerMainInnerRoom",
    "MaxSecInnerHall",    "MaxSecDoorway",      "MedSecInnerHall",    "MedSecCheckInner",   "ChemContMaintDoor",
    "ChemMaintTube",      "ChemMaintRoom",      "MaxMedMaint2Tube",   "MaxLevMaintRoom",    "MaintenanceDoor",
    "MaxMedMaintTube",    "MedMaintRoom",       "MedMinMaintTube",    "MaxSecRingA",        "MaxSecRingB",
    "MaxSecRingC",        "MaxSecRingD",        "MaxSecRingE",        "MaxSecRingF",        "MaxSecRingG",
    "MaxSecRingH",        "MaxSecRingI",        "MaxSecRingJ",        "MaxSecRingK",        "MaxSecRingL",
    "MaxSecRingM",        "MaxSecRingN",        "MaxSecRingO",        "MaxSecRingP",        "CenterPrisonCell",
    "LeftCellA",          "LeftCellB",          "SweitMaxLeftC",      "LeftCellD",          "RightCellA",
    "RightCellB",         "RightCellC",         "RightCellD",         "MaximumLevelMatCen", "SweitMinCell",
    "RecordsRoomA",       "RecordsRoomB",       "MaxComputerRoom",    "ChemicalBotStart"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 28
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "SupplyHangarAlertTr", "AcidVat",           "EndLevelTrigger",  "MCaveOne",         "MStartArea2", "MStartArea",
    "MTerrain2",           "MTerrain1",         "MAfterFF3",        "MAfterFF2",        "MAfterFF1",   "MAcidCaves3",
    "MAcidCaves2",         "MAcidCaves1",       "MOutOfCaves2",     "MOutOfCaves1",     "MMinimum3",   "MMinimum2",
    "MMinimum1",           "MMedium2",          "MMedium1",         "MFinal1",          "MMaximum4",   "MMaximum2",
    "MMaximum1",           "MaximumVOXtrigger", "MediumVOXtrigger", "MinimumVOXtrigger"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 4
static const char *const Sound_names[NUM_SOUND_NAMES] = {"Powerup pickup", "AmbSirenBRedAcrop", "AmbSirenIntense",
                                                         "AmbSwitch11"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 12
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {
    "PhobMonUNLOCKED", "PhobMonInvWait", "PhobMonInvalidAlert", "PhobMonAccepted",
    "PhobMonCHEMSPIL", "PhobEmerEvac",   "PhobBioWarn",         "Dirty glass",
    "PhobMonEVACOMP",  "MeshGlass1",     "PhobMonInsertPas",    "Staticscrolling"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 19
static const char *const Path_names[NUM_PATH_NAMES] = {
    "RescueShuttleStartPath",   "ShuttleFFCamPath", "RescueShuttleEnterPath", "ShuttleTunnelCam",
    "ShuttleCellCam2",          "ShuttleInCellCam", "SweitzerDest",           "ShuttleInCellCam2",
    "ShuttleCellCam",           "EndShuttlePath",   "EndLevelCamPath",        "EndPlayerPath",
    "SupplyHangarAlertRASPath", "IntroCameraPath",  "TempPlayerIntroPath",    "RescueShuttleImpatientPath",
    "RescueShuttleEndPath",     "EndCameraPath",    "PlayerEndPath"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 13
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {
    "LowerInnerTowerMatC", "Supply Hangar Alert", "MaximumCheckpointMa", "MediumCheckpointMat", "MinimumCheckpointMa",
    "ChemicalBallMaker",   "ChemicalDroidMaker",  "MinimumLevelCenterM", "MinimumLevelLeftMat", "MinimumLevelRightMa",
    "MediumLevelRightMat", "MediumLevelLeftMatC", "MaximumLevelMatCen"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 18
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Gain entry to the Supply Hangar",
                                                       "Eliminate Perimeter Defenses",
                                                       "Deactivate the Main Tower Hangar Forcefield",
                                                       "Find the Rescue Shuttle",
                                                       "Enter the Medium Security Level",
                                                       "Get Security Pass X-1",
                                                       "Get Security Pass R-1",
                                                       "Enter the Minimum Security Level",
                                                       "Infiltrate the Main Prison Tower",
                                                       "Get Security Pass G-1",
                                                       "Get Security Pass Y-1",
                                                       "Enter the Maximum Security Level",
                                                       "Locate Dr. Sweitzer's Cell",
                                                       "Find Sweitzer's Minimum Security Cell",
                                                       "Get Sweitzer transferred to Minimum Security",
                                                       "Rescue Dr. Sweitzer",
                                                       "Exit the Prison",
                                                       "Destroy all Prison Records Databanks"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 35
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"OneTurretDown",
                                                             "IncomingMessage",
                                                             "AnotherTurretGone",
                                                             "InnerTowerForcefields",
                                                             "Empty",
                                                             "EndLevel",
                                                             "X1OldSecurityPassD",
                                                             "R1MaxSecurityPassC",
                                                             "G1MinSecurityPassB",
                                                             "Y1MedSecurityPassA",
                                                             "SupplyAlarm",
                                                             "1stInvalidPassOffense",
                                                             "2ndInvalidPassOffense",
                                                             "SecurityPassNotUsableHere",
                                                             "MaximumSecurityClearance",
                                                             "MediumSecurityClearance",
                                                             "MinimumSecurityClearance",
                                                             "IntroMessage",
                                                             "DontShootMe",
                                                             "SPUDisBorn",
                                                             "ChemicalReactionSwitches",
                                                             "SPUDkilled",
                                                             "SPUDscores",
                                                             "SPUDhasTheBall",
                                                             "ChemicalReactionAlert",
                                                             "WhatTheHell",
                                                             "SweitzerMINLockedOut",
                                                             "SweitzerMAX",
                                                             "ShuttleUnderAttack",
                                                             "LoadingSweitzer",
                                                             "LoadedSweitzer",
                                                             "RecordsNodeDestroyed",
                                                             "ComputerDestroyed",
                                                             "ShuttleMoveToTower",
                                                             "EscortShuttle"};
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
    strcpy(filename, "Level2.msg");
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
  case ID_CUSTOM_OBJECT_082D:
    return new CustomObjectScript_082D;
    break;
  case ID_CUSTOM_OBJECT_082E:
    return new CustomObjectScript_082E;
    break;
  case ID_CUSTOM_OBJECT_082F:
    return new CustomObjectScript_082F;
    break;
  case ID_CUSTOM_OBJECT_0830:
    return new CustomObjectScript_0830;
    break;
  case ID_CUSTOM_OBJECT_0831:
    return new CustomObjectScript_0831;
    break;
  case ID_CUSTOM_OBJECT_2112:
    return new CustomObjectScript_2112;
    break;
  case ID_CUSTOM_OBJECT_11F2:
    return new CustomObjectScript_11F2;
    break;
  case ID_CUSTOM_OBJECT_11F4:
    return new CustomObjectScript_11F4;
    break;
  case ID_CUSTOM_OBJECT_11F6:
    return new CustomObjectScript_11F6;
    break;
  case ID_CUSTOM_OBJECT_19F7:
    return new CustomObjectScript_19F7;
    break;
  case ID_CUSTOM_OBJECT_11FB:
    return new CustomObjectScript_11FB;
    break;
  case ID_CUSTOM_OBJECT_1211:
    return new CustomObjectScript_1211;
    break;
  case ID_CUSTOM_OBJECT_0885:
    return new CustomObjectScript_0885;
    break;
  case ID_CUSTOM_OBJECT_080D:
    return new CustomObjectScript_080D;
    break;
  case ID_CUSTOM_OBJECT_09EC:
    return new CustomObjectScript_09EC;
    break;
  case ID_CUSTOM_OBJECT_11EB:
    return new CustomObjectScript_11EB;
    break;
  case ID_CUSTOM_OBJECT_19E9:
    return new CustomObjectScript_19E9;
    break;
  case ID_CUSTOM_OBJECT_19E8:
    return new CustomObjectScript_19E8;
    break;
  case ID_CUSTOM_OBJECT_19EA:
    return new CustomObjectScript_19EA;
    break;
  case ID_CUSTOM_OBJECT_09E7:
    return new CustomObjectScript_09E7;
    break;
  case ID_CUSTOM_OBJECT_09E6:
    return new CustomObjectScript_09E6;
    break;
  case ID_CUSTOM_OBJECT_11BB:
    return new CustomObjectScript_11BB;
    break;
  case ID_CUSTOM_OBJECT_09BC:
    return new CustomObjectScript_09BC;
    break;
  case ID_CUSTOM_OBJECT_09BD:
    return new CustomObjectScript_09BD;
    break;
  case ID_CUSTOM_OBJECT_09BE:
    return new CustomObjectScript_09BE;
    break;
  case ID_CUSTOM_OBJECT_11BF:
    return new CustomObjectScript_11BF;
    break;
  case ID_CUSTOM_OBJECT_09C0:
    return new CustomObjectScript_09C0;
    break;
  case ID_CUSTOM_OBJECT_11C1:
    return new CustomObjectScript_11C1;
    break;
  case ID_CUSTOM_OBJECT_11BA:
    return new CustomObjectScript_11BA;
    break;
  case ID_CUSTOM_OBJECT_09C9:
    return new CustomObjectScript_09C9;
    break;
  case ID_CUSTOM_OBJECT_09C8:
    return new CustomObjectScript_09C8;
    break;
  case ID_CUSTOM_OBJECT_09C7:
    return new CustomObjectScript_09C7;
    break;
  case ID_CUSTOM_OBJECT_09C6:
    return new CustomObjectScript_09C6;
    break;
  case ID_CUSTOM_OBJECT_09C5:
    return new CustomObjectScript_09C5;
    break;
  case ID_CUSTOM_OBJECT_09C4:
    return new CustomObjectScript_09C4;
    break;
  case ID_CUSTOM_OBJECT_09C3:
    return new CustomObjectScript_09C3;
    break;
  case ID_CUSTOM_OBJECT_09C2:
    return new CustomObjectScript_09C2;
    break;
  case ID_CUSTOM_OBJECT_094E:
    return new CustomObjectScript_094E;
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
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
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
  case ID_CUSTOM_OBJECT_082D:
    delete ((CustomObjectScript_082D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_082E:
    delete ((CustomObjectScript_082E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_082F:
    delete ((CustomObjectScript_082F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0830:
    delete ((CustomObjectScript_0830 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0831:
    delete ((CustomObjectScript_0831 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2112:
    delete ((CustomObjectScript_2112 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11F2:
    delete ((CustomObjectScript_11F2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11F4:
    delete ((CustomObjectScript_11F4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11F6:
    delete ((CustomObjectScript_11F6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19F7:
    delete ((CustomObjectScript_19F7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11FB:
    delete ((CustomObjectScript_11FB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1211:
    delete ((CustomObjectScript_1211 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0885:
    delete ((CustomObjectScript_0885 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080D:
    delete ((CustomObjectScript_080D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09EC:
    delete ((CustomObjectScript_09EC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11EB:
    delete ((CustomObjectScript_11EB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19E9:
    delete ((CustomObjectScript_19E9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19E8:
    delete ((CustomObjectScript_19E8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19EA:
    delete ((CustomObjectScript_19EA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09E7:
    delete ((CustomObjectScript_09E7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09E6:
    delete ((CustomObjectScript_09E6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11BB:
    delete ((CustomObjectScript_11BB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BC:
    delete ((CustomObjectScript_09BC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BD:
    delete ((CustomObjectScript_09BD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BE:
    delete ((CustomObjectScript_09BE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11BF:
    delete ((CustomObjectScript_11BF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C0:
    delete ((CustomObjectScript_09C0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11C1:
    delete ((CustomObjectScript_11C1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11BA:
    delete ((CustomObjectScript_11BA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C9:
    delete ((CustomObjectScript_09C9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C8:
    delete ((CustomObjectScript_09C8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C7:
    delete ((CustomObjectScript_09C7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C6:
    delete ((CustomObjectScript_09C6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C5:
    delete ((CustomObjectScript_09C5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C4:
    delete ((CustomObjectScript_09C4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C3:
    delete ((CustomObjectScript_09C3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C2:
    delete ((CustomObjectScript_09C2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_094E:
    delete ((CustomObjectScript_094E *)ptr);
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
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
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
  case ID_CUSTOM_OBJECT_082D:
  case ID_CUSTOM_OBJECT_082E:
  case ID_CUSTOM_OBJECT_082F:
  case ID_CUSTOM_OBJECT_0830:
  case ID_CUSTOM_OBJECT_0831:
  case ID_CUSTOM_OBJECT_2112:
  case ID_CUSTOM_OBJECT_11F2:
  case ID_CUSTOM_OBJECT_11F4:
  case ID_CUSTOM_OBJECT_11F6:
  case ID_CUSTOM_OBJECT_19F7:
  case ID_CUSTOM_OBJECT_11FB:
  case ID_CUSTOM_OBJECT_1211:
  case ID_CUSTOM_OBJECT_0885:
  case ID_CUSTOM_OBJECT_080D:
  case ID_CUSTOM_OBJECT_09EC:
  case ID_CUSTOM_OBJECT_11EB:
  case ID_CUSTOM_OBJECT_19E9:
  case ID_CUSTOM_OBJECT_19E8:
  case ID_CUSTOM_OBJECT_19EA:
  case ID_CUSTOM_OBJECT_09E7:
  case ID_CUSTOM_OBJECT_09E6:
  case ID_CUSTOM_OBJECT_11BB:
  case ID_CUSTOM_OBJECT_09BC:
  case ID_CUSTOM_OBJECT_09BD:
  case ID_CUSTOM_OBJECT_09BE:
  case ID_CUSTOM_OBJECT_11BF:
  case ID_CUSTOM_OBJECT_09C0:
  case ID_CUSTOM_OBJECT_11C1:
  case ID_CUSTOM_OBJECT_11BA:
  case ID_CUSTOM_OBJECT_09C9:
  case ID_CUSTOM_OBJECT_09C8:
  case ID_CUSTOM_OBJECT_09C7:
  case ID_CUSTOM_OBJECT_09C6:
  case ID_CUSTOM_OBJECT_09C5:
  case ID_CUSTOM_OBJECT_09C4:
  case ID_CUSTOM_OBJECT_09C3:
  case ID_CUSTOM_OBJECT_09C2:
  case ID_CUSTOM_OBJECT_094E:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_001E:
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

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_001E;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[38];
  static int cust_id_list[38] = {
      ID_CUSTOM_OBJECT_082D, ID_CUSTOM_OBJECT_082E, ID_CUSTOM_OBJECT_082F, ID_CUSTOM_OBJECT_0830, ID_CUSTOM_OBJECT_0831,
      ID_CUSTOM_OBJECT_2112, ID_CUSTOM_OBJECT_11F2, ID_CUSTOM_OBJECT_11F4, ID_CUSTOM_OBJECT_11F6, ID_CUSTOM_OBJECT_19F7,
      ID_CUSTOM_OBJECT_11FB, ID_CUSTOM_OBJECT_1211, ID_CUSTOM_OBJECT_0885, ID_CUSTOM_OBJECT_080D, ID_CUSTOM_OBJECT_09EC,
      ID_CUSTOM_OBJECT_11EB, ID_CUSTOM_OBJECT_19E9, ID_CUSTOM_OBJECT_19E8, ID_CUSTOM_OBJECT_19EA, ID_CUSTOM_OBJECT_09E7,
      ID_CUSTOM_OBJECT_09E6, ID_CUSTOM_OBJECT_11BB, ID_CUSTOM_OBJECT_09BC, ID_CUSTOM_OBJECT_09BD, ID_CUSTOM_OBJECT_09BE,
      ID_CUSTOM_OBJECT_11BF, ID_CUSTOM_OBJECT_09C0, ID_CUSTOM_OBJECT_11C1, ID_CUSTOM_OBJECT_11BA, ID_CUSTOM_OBJECT_09C9,
      ID_CUSTOM_OBJECT_09C8, ID_CUSTOM_OBJECT_09C7, ID_CUSTOM_OBJECT_09C6, ID_CUSTOM_OBJECT_09C5, ID_CUSTOM_OBJECT_09C4,
      ID_CUSTOM_OBJECT_09C3, ID_CUSTOM_OBJECT_09C2, ID_CUSTOM_OBJECT_094E};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[1];
  cust_handle_list[1] = Object_handles[2];
  cust_handle_list[2] = Object_handles[3];
  cust_handle_list[3] = Object_handles[4];
  cust_handle_list[4] = Object_handles[5];
  cust_handle_list[5] = Object_handles[6];
  cust_handle_list[6] = Object_handles[12];
  cust_handle_list[7] = Object_handles[14];
  cust_handle_list[8] = Object_handles[16];
  cust_handle_list[9] = Object_handles[17];
  cust_handle_list[10] = Object_handles[8];
  cust_handle_list[11] = Object_handles[18];
  cust_handle_list[12] = Object_handles[0];
  cust_handle_list[13] = Object_handles[20];
  cust_handle_list[14] = Object_handles[7];
  cust_handle_list[15] = Object_handles[21];
  cust_handle_list[16] = Object_handles[22];
  cust_handle_list[17] = Object_handles[23];
  cust_handle_list[18] = Object_handles[24];
  cust_handle_list[19] = Object_handles[35];
  cust_handle_list[20] = Object_handles[36];
  cust_handle_list[21] = Object_handles[71];
  cust_handle_list[22] = Object_handles[72];
  cust_handle_list[23] = Object_handles[73];
  cust_handle_list[24] = Object_handles[74];
  cust_handle_list[25] = Object_handles[75];
  cust_handle_list[26] = Object_handles[76];
  cust_handle_list[27] = Object_handles[77];
  cust_handle_list[28] = Object_handles[78];
  cust_handle_list[29] = Object_handles[79];
  cust_handle_list[30] = Object_handles[80];
  cust_handle_list[31] = Object_handles[81];
  cust_handle_list[32] = Object_handles[82];
  cust_handle_list[33] = Object_handles[83];
  cust_handle_list[34] = Object_handles[84];
  cust_handle_list[35] = Object_handles[85];
  cust_handle_list[36] = Object_handles[86];
  cust_handle_list[37] = Object_handles[87];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 38;
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

    // Script 038: Found Sweitzer in Minimum Security
    if ((ScriptActionCtr_038 < 1) &&
        ((qObjCanSeePlayerAdvancedWithStore(3, 360, Object_handles[61], 80.000000f, 1048585) == true) &&
         (qUserFlag(7) == true) &&
         (qObjCanSeeObjAdvanced(Object_handles[61], 60, qObjSavedHandle(3), 1048585) == true))) {
      aAddGameMessage(Message_strings[26], Message_strings[1]);
      aUserFlagSet(9, 1);
      aRoomSetLightingPulse(Room_indexes[54], 3.000000f, 0.000000f);
      aGoalCompleted(Goal_indexes[13], 1);
      aGoalEnableDisable(1, Goal_indexes[2]);
      aDoorLockUnlock(0, Door_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 034: Found Sweitzer in Maximum Security
    if ((ScriptActionCtr_034 < 1) &&
        ((qObjCanSeePlayerAdvancedWithStore(2, 360, Object_handles[60], 80.000000f, 1048585) == true) &&
         (qUserFlag(5) == true) &&
         (qObjCanSeeObjAdvanced(Object_handles[60], 60, qObjSavedHandle(2), 1048585) == true))) {
      aAddGameMessage(Message_strings[27], Message_strings[1]);
      aRoomSetLightingPulse(Room_indexes[47], 3.000000f, 0.000000f);
      aGoalCompleted(Goal_indexes[12], 1);
      aGoalEnableDisable(1, Goal_indexes[14]);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 051: Maximum Checkpoint Reset Timer
    if (qUserFlag(12) == true) {
      aSetLevelTimer(5.000000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }

    // Script 050: Medium Checkpoint Reset Timer
    if (qUserFlag(11) == true) {
      aSetLevelTimer(5.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }

    // Script 049: Minimum Checkpoint Reset Timer
    if (qUserFlag(10) == true) {
      aSetLevelTimer(5.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 057: End Level Sequence
    if ((ScriptActionCtr_057 < 1) && ((qUserFlag(13) == true) && (qUserFlag(14) == true) && (1 == false))) {
      aStartEndlevelSequencePath(Path_indexes[17], Path_indexes[18], 10.000000f, Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }

    // Script 105: Tubbs Sentry VOX
    if ((ScriptActionCtr_105 < 1) &&
        ((qObjExists(Object_handles[88]) == false) && (qObjExists(Object_handles[89]) == false))) {
      aSoundPlaySteaming("VoxL02GeneralE.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }

    // Script 106: Hazardous Materials VOX
    if ((ScriptActionCtr_106 < 1) && (qRoomHasPlayer(Room_indexes[12]) == true)) {
      aSoundPlaySteaming("VoxL02GeneralD.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Perimeter Defense Turrets & Hangar Forcefield Start
    if (1) {
      aUserVarSet(0, 0.000000f);
      aAISetTeam(196608, Object_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 121: Setup for End Cinematics
    if (1) {
      aObjGhostSet(1, Object_handles[8]);

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }

    // Script 012: MatCen Starts
    if (1) {
      aMatcenSetEnableState(0, Matcen_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 015: Start Checkpoint Tubbs
    if (1) {
      aAISetState(0, Object_handles[26]);
      aAISetState(0, Object_handles[27]);
      aAISetState(0, Object_handles[28]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 020: Intro Camera Sequence
    if (1) {
      aCinematicIntro(Path_indexes[13], Message_strings[17], Object_handles[21], Path_indexes[14], 10.000000f);
      aSetLevelTimer(15.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 035: FOG Start
    if (1) {
      aRoomFogSetState(0, Room_indexes[10]);
      aRoomFogSetState(0, Room_indexes[11]);
      aRoomFogSetState(0, Room_indexes[12]);
      aRoomFogSetState(0, Room_indexes[13]);
      aRoomFogSetState(0, Room_indexes[14]);
      aRoomFogSetState(0, Room_indexes[15]);
      aRoomFogSetState(0, Room_indexes[16]);
      aRoomFogSetState(0, Room_indexes[17]);
      aRoomFogSetState(0, Room_indexes[18]);
      aRoomFogSetState(0, Room_indexes[19]);
      aRoomFogSetState(0, Room_indexes[20]);
      aRoomFogSetState(0, Room_indexes[21]);
      aRoomFogSetState(0, Room_indexes[22]);
      aRoomFogSetState(0, Room_indexes[23]);
      aRoomFogSetState(0, Room_indexes[24]);
      aRoomFogSetState(0, Room_indexes[25]);
      aRoomFogSetState(0, Room_indexes[26]);
      aRoomFogSetState(0, Room_indexes[27]);
      aRoomFogSetState(0, Room_indexes[28]);
      aRoomFogSetState(0, Room_indexes[29]);
      aRoomFogSetState(0, Room_indexes[30]);
      aRoomFogSetState(0, Room_indexes[31]);
      aRoomFogSetState(0, Room_indexes[32]);
      aRoomFogSetState(0, Room_indexes[33]);
      aRoomFogSetState(0, Room_indexes[34]);
      aRoomFogSetState(0, Room_indexes[35]);
      aRoomFogSetState(0, Room_indexes[36]);
      aRoomFogSetState(0, Room_indexes[37]);
      aRoomFogSetState(0, Room_indexes[38]);
      aRoomFogSetState(0, Room_indexes[39]);
      aRoomFogSetState(0, Room_indexes[40]);
      aRoomFogSetState(0, Room_indexes[41]);
      aRoomFogSetState(0, Room_indexes[42]);
      aRoomFogSetState(0, Room_indexes[43]);
      aRoomFogSetState(0, Room_indexes[44]);
      aRoomFogSetState(0, Room_indexes[45]);
      aRoomFogSetState(0, Room_indexes[46]);
      aRoomFogSetState(0, Room_indexes[47]);
      aRoomFogSetState(0, Room_indexes[48]);
      aRoomFogSetState(0, Room_indexes[49]);
      aRoomFogSetState(0, Room_indexes[50]);
      aRoomFogSetState(0, Room_indexes[51]);
      aRoomFogSetState(0, Room_indexes[52]);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }

    // Script 030: Acid Vat Forcefields Start
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[10], 1);
      aPortalRenderSet(0, 2, Room_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }

    // Script 031: Prisoners Start & Ghosted Objects
    if (1) {
      aObjGhostSet(1, Object_handles[11]);
      aObjGhostSet(1, Object_handles[52]);
      aObjGhostSet(1, Object_handles[53]);
      aObjGhostSet(1, Object_handles[54]);
      aObjGhostSet(1, Object_handles[55]);
      aObjGhostSet(1, Object_handles[56]);
      aObjGhostSet(1, Object_handles[57]);
      aObjGhostSet(1, Object_handles[58]);
      aObjGhostSet(1, Object_handles[59]);
      aObjGhostSet(1, Object_handles[60]);
      aObjGhostSet(1, Object_handles[61]);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 033: Chemical Center Breakable Glass Start
    if (1) {
      aRoomSetFaceTexture(Room_indexes[10], 239, Texture_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[10], 238, Texture_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[10], 240, Texture_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[12], 272, Texture_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[12], 270, Texture_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[12], 271, Texture_indexes[9]);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 058: Shuttle Landing Platform HIDE
    if (1) {
      aObjHide(Object_handles[10]);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }

    // Script 059: Music-Intro
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }

    // Script 045: Chemical Drone Birth Room WIND
    if (1) {
      aRoomSetWind(Room_indexes[58], 0.156000f, 0.031000f, 0.988000f, 5.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 113: Start the End Cinematic Sequence
    if (event_data->id == 15) {
      aObjGhostSet(1, Object_handles[0]);
      aStoreObjectInPositionClipboard(Object_handles[9]);
      aMoveObjectToPositionClipboard(Object_handles[0]);
      aObjGhostSet(0, Object_handles[0]);
      aObjSetMovementType(Object_handles[0], 0);
      aDestroyAllRobotsInit();
      aDestroyAllRobotsSpareHandle(Object_handles[0]);
      aDestroyAllRobotsSpareHandle(Object_handles[10]);
      aDestroyAllRobotsSpareHandle(Object_handles[11]);
      aDestroyAllRobotsEnd();
      aCinematicSimple(Path_indexes[1], Message_strings[4], Object_handles[12], 12.000000f, 1);
      aSetLevelTimer(2.000000f, 16);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }

    // Script 114: Disable the Forcefield and Start Shuttle on Path
    if (event_data->id == 16) {
      aDoorActivate(Door_handles[0]);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aSetLevelTimer(0.700000f, 17);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }

    // Script 120: Start Shuttle of Escape Path
    if (17 == event_data->id) {
      aObjSetMovementType(Object_handles[0], 1);
      aAISetMaxSpeed(Object_handles[0], 14.000000f);
      aAIGoalFollowPath(Object_handles[0], Path_indexes[2], 1, 3, 1, 3, 1048832, -1);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }

    // Script 097: Intro VOX
    if (9 == event_data->id) {
      aSoundPlaySteaming("VoxL02StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }

    // Script 032: Prisoner Evacuation
    if (event_data->id == 0) {
      aRoomSetFaceTexture(Room_indexes[53], 319, Texture_indexes[8]);
      aRoomSetFaceTexture(Room_indexes[53], 355, Texture_indexes[8]);
      aRoomSetFaceTexture(Room_indexes[53], 125, Texture_indexes[8]);
      aRoomSetFaceTexture(Room_indexes[53], 165, Texture_indexes[8]);
      aObjGhostSet(1, Object_handles[62]);
      aObjGhostSet(1, Object_handles[63]);
      aObjGhostSet(1, Object_handles[64]);
      aObjGhostSet(1, Object_handles[65]);
      aObjGhostSet(1, Object_handles[66]);
      aObjGhostSet(1, Object_handles[67]);
      aObjGhostSet(1, Object_handles[68]);
      aObjGhostSet(1, Object_handles[69]);
      aObjGhostSet(1, Object_handles[70]);
      aObjGhostSet(0, Object_handles[11]);
      aObjGhostSet(0, Object_handles[52]);
      aObjGhostSet(0, Object_handles[53]);
      aObjGhostSet(0, Object_handles[54]);
      aObjGhostSet(0, Object_handles[55]);
      aObjGhostSet(0, Object_handles[56]);
      aObjGhostSet(0, Object_handles[57]);
      aObjGhostSet(0, Object_handles[58]);
      aObjGhostSet(0, Object_handles[59]);
      aAddGameMessage(Message_strings[25], Message_strings[1]);
      aGoalEnableDisable(1, Goal_indexes[13]);
      aGoalCompleted(Goal_indexes[14], 1);
      aSetLevelTimer(3.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 048: Maximum Checkpoint Monitor RESET
    if (3 == event_data->id) {
      aRoomSetFaceTexture(Room_indexes[3], 30, Texture_indexes[10]);
      aUserFlagSet(12, 0);
      aSoundStopObj(Object_handles[29]);
      aSoundStopObj(Object_handles[30]);
      if (qRoomHasPlayer(Room_indexes[4]) == true) {
        aSoundPlaySteaming("VoxL02SpecificB.osf", 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }

    // Script 047: Medium Checkpoint Monitor RESET
    if (2 == event_data->id) {
      aRoomSetFaceTexture(Room_indexes[5], 30, Texture_indexes[10]);
      aUserFlagSet(11, 0);
      aSoundStopObj(Object_handles[31]);
      aSoundStopObj(Object_handles[32]);
      if (qRoomHasPlayer(Room_indexes[6]) == true) {
        aSoundPlaySteaming("VoxL02SpecificB.osf", 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 046: Minimum Checkpoint Monitor RESET
    if (1 == event_data->id) {
      aRoomSetFaceTexture(Room_indexes[7], 30, Texture_indexes[10]);
      aUserFlagSet(10, 0);
      aSoundStopObj(Object_handles[33]);
      aSoundStopObj(Object_handles[34]);
      if (qRoomHasPlayer(Room_indexes[8]) == true) {
        aSoundPlaySteaming("VoxL02SpecificB.osf", 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }

    // Script 052: Rescue Shuttle Loading Sweitzer
    if (4 == event_data->id) {
      aPortalBreakGlass(0, Room_indexes[54]);
      aSoundPlayObject(Sound_indexes[3], Object_handles[0], 1.000000f);
      aObjPlayAnim(Object_handles[0], 0, 2, 3.000000f, 0);
      aSetLevelTimer(7.300000f, 5);
      aShowHUDMessage(Message_strings[29]);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }

    // Script 053: Rescue Shuttle Loaded
    if (5 == event_data->id) {
      aSoundPlayObject(Sound_indexes[3], Object_handles[0], 1.000000f);
      aObjPlayAnim(Object_handles[0], 2, 4, 3.000000f, 0);
      aShowHUDMessage(Message_strings[30]);
      aSetLevelTimer(3.000000f, 6);
      aObjGhostSet(1, Object_handles[11]);
      aUnAttachObject(Object_handles[0]);
      aGoalCompleted(Goal_indexes[15], 1);
      aGoalEnableDisable(1, Goal_indexes[16]);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 054: Rescue Shuttle Escape
    if (6 == event_data->id) {
      aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[2], 16781312, 5, 3);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 101: Perimeter Secure Forcefield Down
    if (7 == event_data->id) {
      aAddGameMessage(Message_strings[33], Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }

    // Script 102: ESCORT SHUTTLE WARNING!
    if ((qAIIsObjectAware(Object_handles[0]) == false) && (8 == event_data->id)) {
      aShowHUDMessage(Message_strings[34]);
      aSetLevelTimer(5.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }

    // Script 108: Evacuation VOX
    if (11 == event_data->id) {
      aSoundPlaySteaming("VoxL02GeneralC.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }

    // Script 109: Maintenance Emergency VOX
    if (12 == event_data->id) {
      aSoundPlaySteaming("VoxL02GeneralG.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }

    // Script 110: Medical Assistance VOX
    if (13 == event_data->id) {
      aSoundPlaySteaming("VoxL02GeneralF.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }

    // Script 111: Hazardous Substances VOX
    if (14 == event_data->id) {
      aSoundPlaySteaming("VoxL02GeneralD.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }

    // Script 107: Biohazard VOX
    if (10 == event_data->id) {
      aSoundPlaySteaming("VoxL02GeneralB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 014: Supply Hangar Alarm Switch
    if (6 == event_data->goal_uid) {
      aShowHUDMessage(Message_strings[10]);
      aMatcenSetState(1, Matcen_indexes[1]);
      aSetLevelTimer(9.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 027: Chemical Droid KILL Room
    if (1 == event_data->goal_uid) {
      aObjPlayAnim(Object_handles[35], 10, 20, 1.000000f, 0);
      aUserFlagSet(6, 0);
      aMatcenSetState(0, Matcen_indexes[5]);
      aMatcenSetState(0, Matcen_indexes[6]);
      aObjDelete(qObjSavedHandle(1));
      aObjDelete(qObjSavedHandle(0));
      aShowHUDMessage(Message_strings[22]);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 026: Chemical Droid Ball Pickup
    if (0 == event_data->goal_uid) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[9], 3, 4352, 1);
      aShowHUDMessage(Message_strings[23]);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 042: Rescue Shuttle Landing for Sweitzer
    if (3 == event_data->goal_uid) {
      aAISetMaxSpeed(Object_handles[0], 4.000000f);
      aAIGoalLandOnObject(Object_handles[0], 0, Object_handles[10], 0, 3, 256, 4);
      aSetLevelTimer(4.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 055: Rescue Shuttle Exit
    if (5 == event_data->goal_uid) {
      aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[16], 4352, -1, 3);
      aAISetMaxSpeed(Object_handles[0], 75.000000f);
      aUserFlagSet(13, 1);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 025: Chemical Droid Created
    if (event_data->id == Matcen_indexes[6]) {
      aObjSaveHandle(event_data->it_handle, 0);
      aAIGoalPickUpObject(event_data->it_handle, 0, qObjSavedHandle(1), 0, 1, 3, 4352, 0);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 024: Chemical Ball Created
    if (event_data->id == Matcen_indexes[5]) {
      aObjSaveHandle(event_data->it_handle, 1);
      aAIGoalPickUpObject(qObjSavedHandle(0), 0, qObjSavedHandle(1), 0, 1, 3, 4352, 0);
      aSetLevelTimer(1.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  case EVT_LEVEL_GOAL_COMPLETE: {
    tOSIRISEVTLEVELGOALCOMPLETE *event_data = &data->evt_level_goal_complete;

    // Script 037: Tower Infiltrated... Next Goal
    if (event_data->level_goal_index == Goal_indexes[8]) {
      aGoalEnableDisable(1, Goal_indexes[6]);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }

    // Script 036: Hangar Access Gained... Next Goal
    if (event_data->level_goal_index == Goal_indexes[0]) {
      aGoalEnableDisable(1, Goal_indexes[9]);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 099: End Level VOX
    if (Goal_indexes[16] == event_data->level_goal_index) {
      if (qUserFlag(16) == true) {
        aSoundPlaySteaming("VoxL02EndLevelAll.osf", 1.000000f);
      } else {
        aSoundPlaySteaming("VoxL02EndLevelPrimary.osf", 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }

    // Script 100: All Prison Records Destroyed VOX Flag
    if (Goal_indexes[17] == event_data->level_goal_index) {
      aUserFlagSet(16, 1);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }

    // Script 112: Entering the Waste Pipes to Find Passkey R-1
    if (Goal_indexes[8] == event_data->level_goal_index) {
      aGoalEnableDisable(1, Goal_indexes[6]);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_082D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 005: Perimeter Defense Turret A
    if (1) {
      aUserVarInc(0);
      if (qUserVarValue(0) > 4.000000f) {
        aMusicSetRegionAll(3);
        aPortalRenderSet(0, 1, Room_indexes[0], 1);
        aSetLevelTimer(4.000000f, 7);
        aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[0], 4352, 2, 3);
        aGoalEnableDisable(1, Goal_indexes[0]);
        aGoalCompleted(Goal_indexes[1], 1);
      } else {
        if (qUserVarValue(0) == 1.000000f) {
          aAddGameMessage(Message_strings[0], Message_strings[1]);
        } else {
          aShowHUDMessage(Message_strings[2]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_082E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 004: Perimeter Defense Turret B
    if (1) {
      aUserVarInc(0);
      if (qUserVarValue(0) > 4.000000f) {
        aMusicSetRegionAll(3);
        aPortalRenderSet(0, 1, Room_indexes[0], 1);
        aSetLevelTimer(4.000000f, 7);
        aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[0], 4352, 2, 3);
        aGoalEnableDisable(1, Goal_indexes[0]);
        aGoalCompleted(Goal_indexes[1], 1);
      } else {
        if (qUserVarValue(0) == 1.000000f) {
          aAddGameMessage(Message_strings[0], Message_strings[1]);
        } else {
          aShowHUDMessage(Message_strings[2]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_082F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 003: Perimeter Defense Turret C
    if (1) {
      aUserVarInc(0);
      if (qUserVarValue(0) > 4.000000f) {
        aMusicSetRegionAll(3);
        aPortalRenderSet(0, 1, Room_indexes[0], 1);
        aSetLevelTimer(4.000000f, 7);
        aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[0], 4352, 2, 3);
        aGoalEnableDisable(1, Goal_indexes[0]);
        aGoalCompleted(Goal_indexes[1], 1);
      } else {
        if (qUserVarValue(0) == 1.000000f) {
          aAddGameMessage(Message_strings[0], Message_strings[1]);
        } else {
          aShowHUDMessage(Message_strings[2]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0830::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 001: Perimeter Defense Turret D
    if (1) {
      aUserVarInc(0);
      if (qUserVarValue(0) > 4.000000f) {
        aMusicSetRegionAll(3);
        aPortalRenderSet(0, 1, Room_indexes[0], 1);
        aSetLevelTimer(4.000000f, 7);
        aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[0], 4352, 2, 3);
        aGoalEnableDisable(1, Goal_indexes[0]);
        aGoalCompleted(Goal_indexes[1], 1);
      } else {
        if (qUserVarValue(0) == 1.000000f) {
          aAddGameMessage(Message_strings[0], Message_strings[1]);
        } else {
          aShowHUDMessage(Message_strings[2]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0831::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 006: Perimeter Defense Turret E
    if (1) {
      aUserVarInc(0);
      if (qUserVarValue(0) > 4.000000f) {
        aMusicSetRegionAll(3);
        aPortalRenderSet(0, 1, Room_indexes[0], 1);
        aSetLevelTimer(4.000000f, 7);
        aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[0], 4352, 2, 3);
        aGoalEnableDisable(1, Goal_indexes[0]);
        aGoalCompleted(Goal_indexes[1], 1);
      } else {
        if (qUserVarValue(0) == 1.000000f) {
          aAddGameMessage(Message_strings[0], Message_strings[1]);
        } else {
          aShowHUDMessage(Message_strings[2]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2112::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: Upper Tower Forcefield Switch
    if (1) {
      if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(8) == false)) {
        aObjPlayAnim(Object_handles[6], 0, 1, 1.000000f, 0);
        aUserFlagSet(8, 1);
        aGoalCompleted(Goal_indexes[2], 1);
        aGoalEnableDisable(1, Goal_indexes[3]);
        if (qUserFlag(0) == false) {
          aMatcenSetEnableState(1, Matcen_indexes[0]);
          aObjPlayAnim(Object_handles[7], 0, 2, 2.000000f, 0);
          aPortalRenderSet(0, 0, Room_indexes[1], 1);
          aPortalRenderSet(0, 1, Room_indexes[1], 1);
          aShowHUDMessage(Message_strings[3]);
          aUserFlagSet(0, 1);
        }
        aSetLevelTimer(2.000000f, 15);
        aDoorLockUnlock(0, Door_handles[0]);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11F2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 115: Start Shuttle Tunnel Shot
    if (1) {
      aObjGhostSet(1, Object_handles[0]);
      aStoreObjectInPositionClipboard(Object_handles[13]);
      aMoveObjectToPositionClipboard(Object_handles[0]);
      aObjGhostSet(0, Object_handles[0]);
      aAISetMaxSpeed(Object_handles[0], 16.000000f);
      aAIGoalFollowPath(Object_handles[0], Path_indexes[2], 11, 17, 11, 3, 1048832, -1);
      aCinematicSimple(Path_indexes[3], Message_strings[4], Object_handles[14], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11F4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 117: Start Shuttle Arriving at Cell Shot
    if (1) {
      aObjGhostSet(1, Object_handles[0]);
      aStoreObjectInPositionClipboard(Object_handles[15]);
      aMoveObjectToPositionClipboard(Object_handles[0]);
      aObjGhostSet(0, Object_handles[0]);
      aAIGoalFollowPath(Object_handles[0], Path_indexes[2], 32, 34, 32, 3, 1048832, 3);
      aCinematicSimple(Path_indexes[4], Message_strings[4], Object_handles[16], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11F6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 116: Start Shuttle In Cell Shot
    if (1) {
      aObjGhostSet(1, Object_handles[11]);
      aObjGhostSet(0, Object_handles[8]);
      aAISetState(1, Object_handles[8]);
      aObjSetMovementType(Object_handles[8], 0);
      aObjPlayAnim(Object_handles[8], 60, 88, 4.000000f, 0);
      aCinematicSimple(Path_indexes[5], Message_strings[4], Object_handles[17], 6.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19F7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 122: Start Shuttle Cell Shot Part 2
    if (1) {
      aObjSetMovementType(Object_handles[8], 2);
      aObjPlayAnim(Object_handles[8], 0, 9, 2.000000f, 0);
      aAIGoalFollowPathSimple(Object_handles[8], Path_indexes[6], 4352, 7, 3);
      aCinematicSimple(Path_indexes[7], Message_strings[4], Object_handles[18], 3.700000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11FB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 123: Ghost Sweitzer after he walks by
    if (event_data->goal_uid == 7) {
      aObjGhostSet(1, Object_handles[8]);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1211::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 118: Start Shuttle Leaving Cell Shot
    if (1) {
      aObjGhostSet(1, Object_handles[8]);
      aAISetMaxSpeed(Object_handles[0], 10.000000f);
      aCinematicSimple(Path_indexes[8], Message_strings[4], Object_handles[0], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0885::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Rescue Shuttle Don't Shoot Me!
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[18]);
      aObjSetShields(Object_handles[0], 9999999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 040: Shuttle Taking Enemy Fire
    if ((qObjIsType(event_data->it_handle, 5) == true) && (qObjIsType(qObjParent(event_data->it_handle), 2) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aObjSetShields(Object_handles[0], 9999999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 041: Shuttle Going To Sweitzer
    if ((ScriptActionCtr_041 < 1) && ((qUserFlag(9) == true) && (qUserFlag(8) == true) && (1 == false))) {
      aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[2], 4096, 3, 3);
      aSetLevelTimer(5.000000f, 8);
      aAISetMaxSpeed(Object_handles[0], 25.000000f);
      aAISetTeam(65536, Object_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 029: Rescue Shuttle Impatient Path
    if (2 == event_data->goal_uid) {
      aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[15], 4198656, -1, 3);
      aAISetMaxSpeed(Object_handles[0], 35.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 119: Start Player and Shuttle Exit Shot
    if (1) {
      aObjGhostSet(1, Object_handles[0]);
      aStoreObjectInPositionClipboard(Object_handles[19]);
      aMoveObjectToPositionClipboard(Object_handles[0]);
      aObjGhostSet(0, Object_handles[0]);
      aAISetMaxSpeed(Object_handles[0], 44.000000f);
      aAIGoalFollowPath(Object_handles[0], Path_indexes[9], 1, 8, 1, 3, 1048832, -1);
      aStartEndlevelSequencePath(Path_indexes[10], Path_indexes[11], 15.000000f, Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 002: Docking Hatch Door
    if (0 == event_data->id) {
      aDoorLockUnlock(0, Door_handles[0]);
      aRoomSetFaceTexture(Room_indexes[1], 30, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[1], 73, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09EC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Inner Tower Forcefield & MatCen Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(0) == false) {
        aMatcenSetEnableState(1, Matcen_indexes[0]);
        aObjPlayAnim(Object_handles[7], 0, 2, 2.000000f, 0);
        aPortalRenderSet(0, 0, Room_indexes[1], 1);
        aPortalRenderSet(0, 1, Room_indexes[1], 1);
        aShowHUDMessage(Message_strings[3]);
        aUserFlagSet(0, 1);
        aSetLevelTimer(7.000000f, 14);
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11EB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: X-1 Old Security Pass D
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[6]);
      aAddObjectToInventory(Object_handles[21], event_data->it_handle, 0);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[4]);
      aGoalCompleted(Goal_indexes[5], 1);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 019: X-1 Security Pass Useage Matrix
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if ((qObjRoom(event_data->it_handle) == Room_indexes[3]) && (qUserFlag(5) == false)) {
        if (qUserVarValue(3) < 1.000000f) {
          aShowHUDMessage(Message_strings[11]);
          aRoomSetFaceTexture(Room_indexes[3], 30, Texture_indexes[1]);
          aAISetState(1, Object_handles[28]);
          aPortalRenderSet(0, 2, Room_indexes[4], 1);
          aUserVarInc(3);
          aUserFlagSet(12, 1);
          aObjGhostSet(0, Object_handles[21]);
          aAddObjectToInventory(Object_handles[21], event_data->it_handle, 0);
          aSoundPlaySteaming("VoxL02SpecificC.osf", 1.000000f);
        } else {
          aShowHUDMessage(Message_strings[12]);
          aRoomSetFaceTexture(Room_indexes[3], 30, Texture_indexes[2]);
          aMatcenSetState(1, Matcen_indexes[2]);
          aUserFlagSet(12, 1);
          aSoundPlayObject(Sound_indexes[1], Object_handles[29], 1.000000f);
          aSoundPlayObject(Sound_indexes[1], Object_handles[30], 1.000000f);
          aObjGhostSet(0, Object_handles[21]);
          aAddObjectToInventory(Object_handles[21], event_data->it_handle, 0);
        }
      } else {
        if ((qObjRoom(event_data->it_handle) == Room_indexes[5]) && (qUserFlag(4) == false)) {
          if (qUserVarValue(2) < 1.000000f) {
            aShowHUDMessage(Message_strings[11]);
            aRoomSetFaceTexture(Room_indexes[5], 30, Texture_indexes[1]);
            aAISetState(1, Object_handles[27]);
            aPortalRenderSet(0, 2, Room_indexes[6], 1);
            aUserVarInc(2);
            aUserFlagSet(11, 1);
            aObjGhostSet(0, Object_handles[21]);
            aAddObjectToInventory(Object_handles[21], event_data->it_handle, 0);
            aSoundPlaySteaming("VoxL02SpecificC.osf", 1.000000f);
          } else {
            aShowHUDMessage(Message_strings[12]);
            aRoomSetFaceTexture(Room_indexes[5], 30, Texture_indexes[2]);
            aMatcenSetState(1, Matcen_indexes[3]);
            aUserFlagSet(11, 1);
            aSoundPlayObject(Sound_indexes[1], Object_handles[31], 1.000000f);
            aSoundPlayObject(Sound_indexes[1], Object_handles[32], 1.000000f);
            aObjGhostSet(0, Object_handles[21]);
            aAddObjectToInventory(Object_handles[21], event_data->it_handle, 0);
          }
        } else {
          aObjGhostSet(0, Object_handles[21]);
          aAddObjectToInventory(Object_handles[21], event_data->it_handle, 0);
          aShowHUDMessage(Message_strings[13]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19E9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: R-1 Maximum Security Pass C
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[7]);
      aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aGoalCompleted(Goal_indexes[6], 1);
      aGoalEnableDisable(1, Goal_indexes[7]);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 018: R-1 Security Pass Useage Matrix
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qObjRoom(event_data->it_handle) == Room_indexes[3]) {
        aShowHUDMessage(Message_strings[14]);
        aPortalRenderSet(0, 0, Room_indexes[4], 1);
        aRoomSetFaceTexture(Room_indexes[3], 30, Texture_indexes[3]);
        aUserFlagSet(5, 1);
        aGoalCompleted(Goal_indexes[11], 1);
        aGoalEnableDisable(1, Goal_indexes[12]);
        aSoundPlaySteaming("VoxL02SpecificD.osf", 1.000000f);
        aSetLevelTimer(13.000000f, 13);
      } else {
        if ((qObjRoom(event_data->it_handle) == Room_indexes[5]) && (qUserFlag(4) == false)) {
          if (qUserVarValue(2) < 1.000000f) {
            aShowHUDMessage(Message_strings[11]);
            aRoomSetFaceTexture(Room_indexes[5], 30, Texture_indexes[1]);
            aAISetState(1, Object_handles[27]);
            aPortalRenderSet(0, 2, Room_indexes[6], 1);
            aUserVarInc(2);
            aUserFlagSet(11, 1);
            aObjGhostSet(0, Object_handles[22]);
            aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
            aSoundPlaySteaming("VoxL02SpecificC.osf", 1.000000f);
          } else {
            aShowHUDMessage(Message_strings[12]);
            aRoomSetFaceTexture(Room_indexes[5], 30, Texture_indexes[2]);
            aMatcenSetState(1, Matcen_indexes[3]);
            aUserFlagSet(11, 1);
            aSoundPlayObject(Sound_indexes[1], Object_handles[31], 1.000000f);
            aSoundPlayObject(Sound_indexes[1], Object_handles[32], 1.000000f);
            aObjGhostSet(0, Object_handles[22]);
            aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
          }
        } else {
          if ((qObjRoom(event_data->it_handle) == Room_indexes[7]) && (qUserFlag(3) == false)) {
            if (qUserVarValue(1) < 1.000000f) {
              aShowHUDMessage(Message_strings[11]);
              aRoomSetFaceTexture(Room_indexes[7], 30, Texture_indexes[1]);
              aAISetState(1, Object_handles[26]);
              aPortalRenderSet(0, 2, Room_indexes[8], 1);
              aUserVarInc(1);
              aUserFlagSet(10, 1);
              aObjGhostSet(0, Object_handles[22]);
              aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
              aSoundPlaySteaming("VoxL02SpecificC.osf", 1.000000f);
            } else {
              aShowHUDMessage(Message_strings[12]);
              aRoomSetFaceTexture(Room_indexes[7], 30, Texture_indexes[2]);
              aMatcenSetState(1, Matcen_indexes[4]);
              aUserFlagSet(10, 1);
              aSoundPlayObject(Sound_indexes[1], Object_handles[33], 1.000000f);
              aSoundPlayObject(Sound_indexes[1], Object_handles[34], 1.000000f);
              aObjGhostSet(0, Object_handles[22]);
              aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
            }
          } else {
            aObjGhostSet(0, Object_handles[22]);
            aAddObjectToInventory(Object_handles[22], event_data->it_handle, 0);
            aShowHUDMessage(Message_strings[13]);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19E8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: G-1 Minimum Security Pass B
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[8]);
      aAddObjectToInventory(Object_handles[23], event_data->it_handle, 0);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[8]);
      aGoalCompleted(Goal_indexes[9], 1);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 016: G-1 Security Pass Useage Matrix
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qObjRoom(event_data->it_handle) == Room_indexes[7]) {
        aShowHUDMessage(Message_strings[16]);
        aPortalRenderSet(0, 0, Room_indexes[8], 1);
        aRoomSetFaceTexture(Room_indexes[7], 30, Texture_indexes[3]);
        aUserFlagSet(3, 1);
        aGoalCompleted(Goal_indexes[7], 1);
        aGoalEnableDisable(1, Goal_indexes[5]);
        aGoalEnableDisable(1, Goal_indexes[10]);
        aSoundPlaySteaming("VoxL02SpecificD.osf", 1.000000f);
        aSetLevelTimer(13.000000f, 12);
      } else {
        aObjGhostSet(0, Object_handles[23]);
        aAddObjectToInventory(Object_handles[23], event_data->it_handle, 0);
        aShowHUDMessage(Message_strings[13]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19EA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Y-1 Medium Security Pass A
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[9]);
      aAddObjectToInventory(Object_handles[24], event_data->it_handle, 0);
      aSoundPlay2DObj(Sound_indexes[0], event_data->it_handle, 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[4]);
      aGoalCompleted(Goal_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 017: Y-1 Security Pass Useage Matrix
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qObjRoom(event_data->it_handle) == Room_indexes[5]) {
        aShowHUDMessage(Message_strings[15]);
        aPortalRenderSet(0, 0, Room_indexes[6], 1);
        aRoomSetFaceTexture(Room_indexes[5], 30, Texture_indexes[3]);
        aUserFlagSet(4, 1);
        aGoalEnableDisable(1, Goal_indexes[11]);
        aGoalCompleted(Goal_indexes[4], 1);
        aSoundPlaySteaming("VoxL02SpecificD.osf", 1.000000f);
        aSetLevelTimer(16.000000f, 13);
      } else {
        aObjGhostSet(0, Object_handles[24]);
        aAddObjectToInventory(Object_handles[24], event_data->it_handle, 0);
        aShowHUDMessage(Message_strings[13]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09E7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Chemical Droid Start Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if ((qUserFlag(6) == false) && (qUserFlag(7) == false)) {
        aShowHUDMessage(Message_strings[19]);
        aObjPlayAnim(Object_handles[35], 0, 10, 1.000000f, 0);
        aMatcenSetState(1, Matcen_indexes[5]);
        aMatcenSetState(1, Matcen_indexes[6]);
        aUserFlagSet(6, 1);
      } else {
        if (qUserFlag(7) == true) {
          aShowHUDMessage(Message_strings[20]);
        } else {
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09E6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Chemical Droid KILL Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if ((qUserFlag(6) == true) && (qUserFlag(7) == false)) {
        aShowHUDMessage(Message_strings[21]);
        aObjPlayAnim(Object_handles[36], 0, 20, 1.000000f, 0);
        aMatcenSetState(0, Matcen_indexes[5]);
        aMatcenSetState(0, Matcen_indexes[6]);
        aUserFlagSet(6, 0);
        aObjDestroy(qObjSavedHandle(0));
        aObjPlayAnim(Object_handles[35], 10, 20, 1.000000f, 0);
      } else {
        if (qUserFlag(7) == true) {
          aShowHUDMessage(Message_strings[20]);
        } else {
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11BB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 088: Novak Prison Records Node H Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 087: Novak Prison Records Node G Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 086: Novak Prison Records Node F Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 085: Novak Prison Records Node E Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11BF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 084: Novak Prison Records Node D Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 083: Novak Prison Records Node C Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11C1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 082: Novak Prison Records Node B Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11BA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 044: Novak Prison Records Node A Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(5);
      aUserVarInc(4);
      if (qUserVarValue(5) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[55], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[55], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 096: Novak Prison Records Node P Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 095: Novak Prison Records Node O Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 094: Novak Prison Records Node N Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 093: Novak Prison Records Node M Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 092: Novak Prison Records Node L Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 091: Novak Prison Records Node K Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 090: Novak Prison Records Node J Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 089: Novak Prison Records Node I Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[31]);
      aUserVarInc(6);
      aUserVarInc(4);
      if (qUserVarValue(6) > 7.000000f) {
        aRoomSetFaceTexture(Room_indexes[56], 64, Texture_indexes[11]);
        aRoomSetFaceTexture(Room_indexes[56], 65, Texture_indexes[11]);
        if ((qUserVarValue(4) > 15.000000f) && (qUserFlag(15) == true)) {
          aGoalCompleted(Goal_indexes[17], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_094E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 043: Novak Super Computer Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[32]);
      aUserFlagSet(15, 1);
      aRoomSetFaceTexture(Room_indexes[57], 158, Texture_indexes[11]);
      aRoomSetFaceTexture(Room_indexes[57], 157, Texture_indexes[11]);
      aRoomSetFaceTexture(Room_indexes[57], 225, Texture_indexes[11]);
      aRoomSetFaceTexture(Room_indexes[57], 189, Texture_indexes[11]);
      if (qUserVarValue(4) > 15.000000f) {
        aGoalCompleted(Goal_indexes[17], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Supply Hangar Alarm
    if (1) {
      aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[12], 2101504, 6, 3);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: OOPS!  SPUD has dropped the ball!
    if (11 == qObjType(event_data->it_handle)) {
      aUserFlagSet(7, 1);
      aTurnOnSpew(Object_handles[37], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 1.000000f, -1.000000f,
                  8.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[38], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 1.000000f, -1.000000f,
                  8.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[39], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 1.000000f, -1.000000f,
                  8.000000f, 30.000000f, 0, -1);
      aRoomChangeFog(Room_indexes[10], 0.200000f, 1.000000f, 0.000000f, 200.000000f, 10.000000f);
      aRoomChangeFog(Room_indexes[11], 0.200000f, 1.000000f, 0.000000f, 200.000000f, 15.000000f);
      aRoomChangeFog(Room_indexes[14], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 20.000000f);
      aRoomChangeFog(Room_indexes[12], 0.200000f, 1.000000f, 0.000000f, 200.000000f, 15.000000f);
      aRoomChangeFog(Room_indexes[13], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 20.000000f);
      aRoomChangeFog(Room_indexes[15], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 25.000000f);
      aRoomChangeFog(Room_indexes[16], 0.200000f, 1.000000f, 0.000000f, 400.000000f, 30.000000f);
      aRoomChangeFog(Room_indexes[17], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 25.000000f);
      aRoomChangeFog(Room_indexes[18], 0.200000f, 1.000000f, 0.000000f, 400.000000f, 30.000000f);
      aRoomChangeFog(Room_indexes[19], 0.200000f, 1.000000f, 0.000000f, 200.000000f, 15.000000f);
      aRoomChangeFog(Room_indexes[20], 0.200000f, 1.000000f, 0.000000f, 200.000000f, 20.000000f);
      aRoomChangeFog(Room_indexes[21], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 25.000000f);
      aRoomChangeFog(Room_indexes[22], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 30.000000f);
      aRoomChangeFog(Room_indexes[23], 0.200000f, 1.000000f, 0.000000f, 300.000000f, 35.000000f);
      aRoomChangeFog(Room_indexes[24], 0.200000f, 1.000000f, 0.000000f, 400.000000f, 40.000000f);
      aRoomChangeFog(Room_indexes[25], 0.200000f, 1.000000f, 0.000000f, 400.000000f, 40.000000f);
      aRoomChangeFog(Room_indexes[26], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[27], 0.200000f, 1.000000f, 0.000000f, 800.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[28], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[29], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[30], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[31], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[32], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[33], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[34], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[35], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[36], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[37], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[38], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[39], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[40], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[41], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[42], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[43], 0.200000f, 1.000000f, 0.000000f, 500.000000f, 45.000000f);
      aRoomChangeFog(Room_indexes[44], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[45], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[46], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[47], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[48], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[49], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[50], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[51], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aRoomChangeFog(Room_indexes[52], 0.200000f, 1.000000f, 0.000000f, 600.000000f, 50.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[40], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[41], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[42], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[43], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[44], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[45], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[46], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[47], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[48], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[49], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[50], 1.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[51], 1.000000f);
      aRoomSetFaceTexture(Room_indexes[12], 256, Texture_indexes[4]);
      aRoomSetFaceTexture(Room_indexes[12], 269, Texture_indexes[5]);
      aRoomSetFaceTexture(Room_indexes[12], 219, Texture_indexes[6]);
      aRoomSetFaceTexture(Room_indexes[12], 206, Texture_indexes[6]);
      aRoomSetFaceTexture(Room_indexes[12], 188, Texture_indexes[6]);
      aRoomSetFaceTexture(Room_indexes[12], 170, Texture_indexes[6]);
      aRoomSetFaceTexture(Room_indexes[10], 238, Texture_indexes[7]);
      aRoomSetFaceTexture(Room_indexes[10], 240, Texture_indexes[7]);
      aRoomSetFaceTexture(Room_indexes[10], 239, Texture_indexes[7]);
      aMiscViewerShake(100.000000f);
      aPortalBreakGlass(3, Room_indexes[10]);
      aPortalBreakGlass(4, Room_indexes[10]);
      aPortalBreakGlass(5, Room_indexes[10]);
      aPortalRenderSet(1, 1, Room_indexes[10], 1);
      aPortalRenderSet(1, 2, Room_indexes[10], 1);
      aPortalRenderSet(0, 0, Room_indexes[44], 1);
      aPortalRenderSet(0, 0, Room_indexes[45], 1);
      aPortalRenderSet(0, 0, Room_indexes[46], 1);
      aPortalRenderSet(0, 0, Room_indexes[47], 1);
      aPortalRenderSet(0, 0, Room_indexes[48], 1);
      aPortalRenderSet(0, 0, Room_indexes[49], 1);
      aPortalRenderSet(0, 0, Room_indexes[50], 1);
      aPortalRenderSet(0, 0, Room_indexes[51], 1);
      aPortalRenderSet(0, 0, Room_indexes[52], 1);
      aDoorLockUnlock(0, Door_handles[1]);
      aMatcenSetState(1, Matcen_indexes[4]);
      aMatcenSetState(1, Matcen_indexes[3]);
      aMatcenSetState(1, Matcen_indexes[2]);
      aMatcenSetState(1, Matcen_indexes[7]);
      aMatcenSetState(1, Matcen_indexes[8]);
      aMatcenSetState(1, Matcen_indexes[9]);
      aMatcenSetState(1, Matcen_indexes[10]);
      aMatcenSetState(1, Matcen_indexes[11]);
      aMatcenSetState(1, Matcen_indexes[12]);
      aSetLevelTimer(10.000000f, 0);
      aShowHUDMessage(Message_strings[24]);
      aObjMakeVulnerable(Object_handles[40]);
      aSetLevelTimer(3.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: End Level Ready
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aUserFlagSet(14, 1);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Music-Intro 2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Music-Start Area 2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Music-Start Area 1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Music-Terrain 2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Music-Terrain 1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Music-After FF 3
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Music-After FF 2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Music-After FF 1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Music-Acid Caves 3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Music-Acid Caves 2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Music-Acid Caves
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 072: Music-Out of Caves 2
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: Music-Out of Caves 1
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 075: Music-Minimum3
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music-Minimum2
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: Music-Minimum
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Music-Medium 2
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Music-Medium 1
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Music-Final
    if (1) {
      aMusicSetRegion(9, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Music-Maximum 3
    if (1) {
      aMusicSetRegion(8, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: Music-Maximum 2
    if (1) {
      aMusicSetRegion(8, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: Music-Maximum 1
    if (1) {
      aMusicSetRegion(8, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 104: Maximum VOX Trigger
    if (qUserFlag(5) == false) {
      aSoundPlaySteaming("VoxL02SpecificA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 103: Medium VOX Trigger
    if (qUserFlag(4) == false) {
      aSoundPlaySteaming("VoxL02SpecificA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 098: Minimum VOX Trigger
    if (qUserFlag(3) == false) {
      aSoundPlaySteaming("VoxL02SpecificA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
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
NEXT_ID		124

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:Perimeter Defense Turrets
1:G1MinimumSecurityDefCon
2:Y1MediumSecurityDefCon
3:R1MaximumSecurityDefCon
4:TOTALRecordNodesDestroyedSoFar
5:RecordNodesADestroyedSoFar
6:RecordNodesBDestroyedSoFar
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:InnerTowerForcefieldSwitchON
1:DockingDoorSwitchON
2:SupplyHangarAlarmSwitchON
3:G1MinimumSecurityPassReaderOFF
4:Y1MediumSecurityPassReaderOFF
5:R1MaximumSecurityPassReaderOFF
6:ChemicalDroidAlive
7:ChemicalReactionHasOccurred
8:UpperTowerForcefieldSwitchON
9:SweitzerReadyForRescue
10:MinimumCheckpointReset
11:MediumCheckpointReset
12:MaximumCheckpointReset
13:ShuttleEndReady
14:PlayerEndReady
15:RecordsComputerDestroyed
16:AllPrisonRecordsDestroyed
17:MinimumVOXenterON
18:MediumVOXenterON
19:MaximumVOXenterON
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:PrisonerTransferTimer
1:MinimumCheckpointResetTimer
2:MediumCheckpointResetTimer
3:MaximumCheckpointResetTimer
4:RescueShuttleLoading Sweitzer
5:RescueShuttle Loaded
6:RescueShuttleEscapeReady
7:PerimeterSecure
8:EscortShuttleTimer
9:IntroVOXTimer
10:BiohazardVOXtimer
11:EvacuationVOXtimer
12:MaintenanceEmergencyVOXTimer
13:MedicalAssistanceVOXTimer
14:HazardousSubstancesVOXTimer
15:StartEndCinematic
16:DeactivateMainForcefield
17:StartShuttleRescue
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:Chemical Droid
1:Chemical Ball
2:PlayerFindsSweitzerMax
3:PlayerFindsSweitzerMin
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:ChemicalDroidBallPickup
1:ChemicalDroidCompletedKILL
2:RescueShuttleAtHangar
3:RescueShuttleAtSweitzer
4:ShuttleHasLanded
5:RescueShuttleEscaped
6:HangarAlarmReached
7:SweitzerWalkedBy
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
DockingDoor
MinimumLevelServic
$$DOOR_LIST_END

$$OBJECT_LIST_START
RescueShuttle
PerimeterTurretA
PerimeterTurretB
PerimeterTurretC
PerimeterTurretD
PerimeterTurretE
UpperTowerForcefie
InnerTowerForcefie
SweitzerActor
ShuttleFFStartPos
RescueShuttleDocki
SweitzerMIN
ShuttleFFTarget
ShuttleTunnelPos
ShuttleTunnelTarge
ShuttleCellPos
ShuttleCellTarget
ShuttleInCellTarge
ShuttleCellTarget2
EndShuttlePos
DockingDoor
X-1OldSecurityPass
R-1MaximumSecurity
G-1MinimumSecurity
Y-1MediumSecurityP
HangarRASAlarmGuy
CheckpointMinTubbs
CheckpointMedTubbs
CheckpointMaxTubbs
MaxCheckCamA
MaxCheckCamB
MedCheckCamA
MedCheckCamB
MinCheckCamA
MinCheckCamB
ChemicalBotStartSw
ChemicalBotKILLSwi
AcidVatSpewerA
AcidVatSpewerB
AcidVatSpewerC
ChemicalControlCam
AcidVatCamera
SirenCamA
SirenCamB
SirenCamC
SirenCamD
SirenCamE
SirenCamF
SirenCamG
SirenCamH
SirenCamI
SirenCamJ
MinMan1
MinMan2
MinMan3
MinMan4
MinMan5
MinMan6
MinMan7
MinMan8
SweitMaxLocator
SweitMinLocator
SweitzerMAX
MaxMan1
MaxMan2
MaxMan3
MaxMan4
MaxMan5
MaxMan6
MaxMan7
MaxMan8
RecordsNodeH
RecordsNodeG
RecordsNodeF
RecordsNodeE
RecordsNodeD
RecordsNodeC
RecordsNodeB
RecordsNodeA
RecordsNodeP
RecordsNodeO
RecordsNodeN
RecordsNodeM
RecordsNodeL
RecordsNodeK
RecordsNodeJ
RecordsNodeI
PrisonRecordsCompu
TubbsSentryA
TubbsSentryB
$$OBJECT_LIST_END

$$ROOM_LIST_START
SupplyHangarEntran
InnerTowerForcefie
PrisonerTransferHa
R-1MaximumSecurity
MaximumSecurityChe
Y-1MediumSecurityP
MediumSecurityChec
G-1MinimumSecurity
MinimumSecurityChe
KILLroom
AcidVatRoom
LowerInnerTowerMat
ChemicalControlCen
LowerInnerTowerSha
LowerMainInnerRoom
MaxSecInnerHall
MaxSecDoorway
MedSecInnerHall
MedSecCheckInner
ChemContMaintDoor
ChemMaintTube
ChemMaintRoom
MaxMedMaint2Tube
MaxLevMaintRoom
MaintenanceDoor
MaxMedMaintTube
MedMaintRoom
MedMinMaintTube
MaxSecRingA
MaxSecRingB
MaxSecRingC
MaxSecRingD
MaxSecRingE
MaxSecRingF
MaxSecRingG
MaxSecRingH
MaxSecRingI
MaxSecRingJ
MaxSecRingK
MaxSecRingL
MaxSecRingM
MaxSecRingN
MaxSecRingO
MaxSecRingP
CenterPrisonCell
LeftCellA
LeftCellB
SweitMaxLeftC
LeftCellD
RightCellA
RightCellB
RightCellC
RightCellD
MaximumLevelMatCen
SweitMinCell
RecordsRoomA
RecordsRoomB
MaxComputerRoom
ChemicalBotStart
$$ROOM_LIST_END

$$TRIGGER_LIST_START
SupplyHangarAlertTr
AcidVat
EndLevelTrigger
MCaveOne
MStartArea2
MStartArea
MTerrain2
MTerrain1
MAfterFF3
MAfterFF2
MAfterFF1
MAcidCaves3
MAcidCaves2
MAcidCaves1
MOutOfCaves2
MOutOfCaves1
MMinimum3
MMinimum2
MMinimum1
MMedium2
MMedium1
MFinal1
MMaximum4
MMaximum2
MMaximum1
MaximumVOXtrigger
MediumVOXtrigger
MinimumVOXtrigger
$$TRIGGER_LIST_END

$$SOUND_LIST_START
Powerup pickup
AmbSirenBRedAcrop
AmbSirenIntense
AmbSwitch11
$$SOUND_LIST_END

$$TEXTURE_LIST_START
PhobMonUNLOCKED
PhobMonInvWait
PhobMonInvalidAlert
PhobMonAccepted
PhobMonCHEMSPIL
PhobEmerEvac
PhobBioWarn
Dirty glass
PhobMonEVACOMP
MeshGlass1
PhobMonInsertPas
Staticscrolling
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
RescueShuttleStartPath
ShuttleFFCamPath
RescueShuttleEnterPath
ShuttleTunnelCam
ShuttleCellCam2
ShuttleInCellCam
SweitzerDest
ShuttleInCellCam2
ShuttleCellCam
EndShuttlePath
EndLevelCamPath
EndPlayerPath
SupplyHangarAlertRASPath
IntroCameraPath
TempPlayerIntroPath
RescueShuttleImpatientPath
RescueShuttleEndPath
EndCameraPath
PlayerEndPath
$$PATH_LIST_END

$$MATCEN_LIST_START
LowerInnerTowerMatC
Supply Hangar Alert
MaximumCheckpointMa
MediumCheckpointMat
MinimumCheckpointMa
ChemicalBallMaker
ChemicalDroidMaker
MinimumLevelCenterM
MinimumLevelLeftMat
MinimumLevelRightMa
MediumLevelRightMat
MediumLevelLeftMatC
MaximumLevelMatCen
$$MATCEN_LIST_END

$$GOAL_LIST_START
Gain entry to the Supply Hangar
Eliminate Perimeter Defenses
Deactivate the Main Tower Hangar Forcefield
Find the Rescue Shuttle
Enter the Medium Security Level
Get Security Pass X-1
Get Security Pass R-1
Enter the Minimum Security Level
Infiltrate the Main Prison Tower
Get Security Pass G-1
Get Security Pass Y-1
Enter the Maximum Security Level
Locate Dr. Sweitzer's Cell
Find Sweitzer's Minimum Security Cell
Get Sweitzer transferred to Minimum Security
Rescue Dr. Sweitzer
Exit the Prison
Destroy all Prison Records Databanks
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL02SpecificC.osf
VoxL02SpecificD.osf
VoxL02StartLevel.osf
VoxL02SpecificB.osf
VoxL02EndLevelAll.osf
VoxL02EndLevelPrimary.osf
VoxL02SpecificA.osf
VoxL02GeneralE.osf
VoxL02GeneralD.osf
VoxL02GeneralC.osf
VoxL02GeneralG.osf
VoxL02GeneralF.osf
VoxL02GeneralB.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Perimeter Defense Turrets & Hangar Forcefield Start
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
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Perimeter Defense Turret A
        $$CHILD_BLOCK_START
        01:1:1
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:3:Region
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:16:0:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
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
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAddGameMessage
                                        $$CHILD_BLOCK_START
                                        10:8:OneTurretDown:GameMessage
                                        10:8:IncomingMessage:HUDMessage
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AnotherTurretGone:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Perimeter Defense Turret B
        $$CHILD_BLOCK_START
        01:1:2
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:3:Region
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:16:0:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
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
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAddGameMessage
                                        $$CHILD_BLOCK_START
                                        10:8:OneTurretDown:GameMessage
                                        10:8:IncomingMessage:HUDMessage
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AnotherTurretGone:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Perimeter Defense Turret C
        $$CHILD_BLOCK_START
        01:1:3
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:3:Region
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:16:0:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
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
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAddGameMessage
                                        $$CHILD_BLOCK_START
                                        10:8:OneTurretDown:GameMessage
                                        10:8:IncomingMessage:HUDMessage
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AnotherTurretGone:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Perimeter Defense Turret D
        $$CHILD_BLOCK_START
        01:1:4
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:3:Region
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:16:0:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
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
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAddGameMessage
                                        $$CHILD_BLOCK_START
                                        10:8:OneTurretDown:GameMessage
                                        10:8:IncomingMessage:HUDMessage
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AnotherTurretGone:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Perimeter Defense Turret E
        $$CHILD_BLOCK_START
        01:1:5
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:3:Region
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:16:0:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
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
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAddGameMessage
                                        $$CHILD_BLOCK_START
                                        10:8:OneTurretDown:GameMessage
                                        10:8:IncomingMessage:HUDMessage
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:AnotherTurretGone:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Upper Tower Forcefield Switch
        $$CHILD_BLOCK_START
        01:1:6
        02:0
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
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjIsPlayerWeapon:Bool
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:3:LevelGoal
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:17:0:0:Matcen
                                        $$CHILD_BLOCK_END
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:0:7:Object
                                        10:4:0:StartFrame
                                        10:4:2:EndFrame
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
                                08:aPortalRenderSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:4:1:PortalNum
                                        10:2:1:Room
                                        10:5:1:DoublesidedFlag
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:InnerTowerForcefields:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:15:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:Setup for End Cinematics
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:Start the End Cinematic Sequence
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
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aDestroyAllRobotsInit
                08:aDestroyAllRobotsSpareHandle
                        $$CHILD_BLOCK_START
                        10:1:0:0:RobotHandle
                        $$CHILD_BLOCK_END
                08:aDestroyAllRobotsSpareHandle
                        $$CHILD_BLOCK_START
                        10:1:0:10:RobotHandle
                        $$CHILD_BLOCK_END
                08:aDestroyAllRobotsSpareHandle
                        $$CHILD_BLOCK_START
                        10:1:0:11:RobotHandle
                        $$CHILD_BLOCK_END
                08:aDestroyAllRobotsEnd
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:1:CameraPath
                        10:8:Empty:Text
                        10:1:0:12:Target
                        10:6:12.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:Disable the Forcefield and Start Shuttle on Path
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
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.700000:Time
                        10:10:0:17:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:Start Shuttle of Escape Path
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:17:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:14.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:2:Path
                        10:4:1:FirstNode
                        10:4:3:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:Start Shuttle Tunnel Shot
        $$CHILD_BLOCK_START
        01:1:12
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:16.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:2:Path
                        10:4:11:FirstNode
                        10:4:17:LastNode
                        10:4:11:StartNode
                        10:10:0:3:GoalPriority
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:3:CameraPath
                        10:8:Empty:Text
                        10:1:0:14:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:Start Shuttle Arriving at Cell Shot
        $$CHILD_BLOCK_START
        01:1:14
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:2:Path
                        10:4:32:FirstNode
                        10:4:34:LastNode
                        10:4:32:StartNode
                        10:10:0:3:GoalPriority
                        10:15:1048832:AIGoalFlags
                        10:10:0:3:GoalID
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:4:CameraPath
                        10:8:Empty:Text
                        10:1:0:16:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:Start Shuttle In Cell Shot
        $$CHILD_BLOCK_START
        01:1:16
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:60:StartFrame
                        10:4:88:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:5:CameraPath
                        10:8:Empty:Text
                        10:1:0:17:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:Start Shuttle Cell Shot Part 2
        $$CHILD_BLOCK_START
        01:1:17
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:10:0:2:MovementType
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:0:StartFrame
                        10:4:9:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:16:6:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:7:CameraPath
                        10:8:Empty:Text
                        10:1:0:18:Target
                        10:6:3.700000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:Ghost Sweitzer after he walks by
        $$CHILD_BLOCK_START
        01:1:8
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
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:Start Shuttle Leaving Cell Shot
        $$CHILD_BLOCK_START
        01:1:18
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:10.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:8:CameraPath
                        10:8:Empty:Text
                        10:1:0:0:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:Start Player and Shuttle Exit Shot
        $$CHILD_BLOCK_START
        01:1:0
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:44.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:9:Path
                        10:4:1:FirstNode
                        10:4:8:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:1048832:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:10:CameraPath
                        10:16:11:PlayerPath
                        10:6:15.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Docking Hatch Door
        $$CHILD_BLOCK_START
        01:1:20
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:0:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:4:30:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:4:73:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Inner Tower Forcefield & MatCen Switch
        $$CHILD_BLOCK_START
        01:1:7
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:4:0:StartFrame
                                10:4:2:EndFrame
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
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:InnerTowerForcefields:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:7.000000:Time
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:X-1 Old Security Pass D
        $$CHILD_BLOCK_START
        01:1:21
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
                        10:8:X1OldSecurityPassD:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:R-1 Maximum Security Pass C
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:R1MaxSecurityPassC:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:7:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:G-1 Minimum Security Pass B
        $$CHILD_BLOCK_START
        01:1:23
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
                        10:8:G1MinSecurityPassB:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:8:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:9:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Y-1 Medium Security Pass A
        $$CHILD_BLOCK_START
        01:1:24
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
                        10:8:Y1MedSecurityPassA:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:10:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:MatCen Starts
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Supply Hangar Alarm
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:16:12:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Supply Hangar Alarm Switch
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:6:GoalID
                        07:1:0
                        10:10:1:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SupplyAlarm:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:9.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Start Checkpoint Tubbs
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:X-1 Security Pass Useage Matrix
        $$CHILD_BLOCK_START
        01:1:21
        02:25
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjRoom:Room
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:2:3:Room
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
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
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:1stInvalidPassOffense:Message
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:3:Room
                                        10:4:30:FaceNum
                                        10:14:1:Texture
                                        $$CHILD_BLOCK_END
                                08:aAISetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:On/Off
                                        10:1:0:28:Object
                                        $$CHILD_BLOCK_END
                                08:aPortalRenderSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:4:2:PortalNum
                                        10:2:4:Room
                                        10:5:1:DoublesidedFlag
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventory
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        10:1:1:-1:PlayerObject
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:0:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:2ndInvalidPassOffense:Message
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:3:Room
                                        10:4:30:FaceNum
                                        10:14:2:Texture
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:2:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:1:Sound
                                        10:1:0:29:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:1:Sound
                                        10:1:0:30:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventory
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        10:1:1:-1:PlayerObject
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
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
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:2:5:Room
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
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
                                                07:1:3
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:1stInvalidPassOffense:Message
                                                $$CHILD_BLOCK_END
                                        08:aRoomSetFaceTexture
                                                $$CHILD_BLOCK_START
                                                10:2:5:Room
                                                10:4:30:FaceNum
                                                10:14:1:Texture
                                                $$CHILD_BLOCK_END
                                        08:aAISetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:On/Off
                                                10:1:0:27:Object
                                                $$CHILD_BLOCK_END
                                        08:aPortalRenderSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Enable/Disable
                                                10:4:2:PortalNum
                                                10:2:6:Room
                                                10:5:1:DoublesidedFlag
                                                $$CHILD_BLOCK_END
                                        08:aUserVarInc
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:0:21:Object
                                                $$CHILD_BLOCK_END
                                        08:aAddObjectToInventory
                                                $$CHILD_BLOCK_START
                                                10:1:0:21:Object
                                                10:1:1:-1:PlayerObject
                                                10:5:0:Spewable
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlaySteaming
                                                $$CHILD_BLOCK_START
                                                10:19:0:Sound
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:2ndInvalidPassOffense:Message
                                                $$CHILD_BLOCK_END
                                        08:aRoomSetFaceTexture
                                                $$CHILD_BLOCK_START
                                                10:2:5:Room
                                                10:4:30:FaceNum
                                                10:14:2:Texture
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:3:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:31:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:32:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:0:21:Object
                                                $$CHILD_BLOCK_END
                                        08:aAddObjectToInventory
                                                $$CHILD_BLOCK_START
                                                10:1:0:21:Object
                                                10:1:1:-1:PlayerObject
                                                10:5:0:Spewable
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventory
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        10:1:1:-1:PlayerObject
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:SecurityPassNotUsableHere:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:R-1 Security Pass Useage Matrix
        $$CHILD_BLOCK_START
        01:1:22
        02:25
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MaximumSecurityClearance:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:30:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:11:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:12:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:1:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:13.000000:Time
                                10:10:0:13:TimerID
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
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:2:5:Room
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
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
                                                07:1:3
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:1stInvalidPassOffense:Message
                                                $$CHILD_BLOCK_END
                                        08:aRoomSetFaceTexture
                                                $$CHILD_BLOCK_START
                                                10:2:5:Room
                                                10:4:30:FaceNum
                                                10:14:1:Texture
                                                $$CHILD_BLOCK_END
                                        08:aAISetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:On/Off
                                                10:1:0:27:Object
                                                $$CHILD_BLOCK_END
                                        08:aPortalRenderSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Enable/Disable
                                                10:4:2:PortalNum
                                                10:2:6:Room
                                                10:5:1:DoublesidedFlag
                                                $$CHILD_BLOCK_END
                                        08:aUserVarInc
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:0:22:Object
                                                $$CHILD_BLOCK_END
                                        08:aAddObjectToInventory
                                                $$CHILD_BLOCK_START
                                                10:1:0:22:Object
                                                10:1:1:-1:PlayerObject
                                                10:5:0:Spewable
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlaySteaming
                                                $$CHILD_BLOCK_START
                                                10:19:0:Sound
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:2ndInvalidPassOffense:Message
                                                $$CHILD_BLOCK_END
                                        08:aRoomSetFaceTexture
                                                $$CHILD_BLOCK_START
                                                10:2:5:Room
                                                10:4:30:FaceNum
                                                10:14:2:Texture
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:3:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:31:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:1:Sound
                                                10:1:0:32:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:0:22:Object
                                                $$CHILD_BLOCK_END
                                        08:aAddObjectToInventory
                                                $$CHILD_BLOCK_START
                                                10:1:0:22:Object
                                                10:1:1:-1:PlayerObject
                                                10:5:0:Spewable
                                                $$CHILD_BLOCK_END
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
                                                        06:qObjRoom:Room
                                                                $$CHILD_BLOCK_START
                                                                10:1:1:-1:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:2:7:Room
                                                        $$CHILD_BLOCK_END
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qUserFlag:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:7
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
                                                                10:10:0:1:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:1.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:1stInvalidPassOffense:Message
                                                        $$CHILD_BLOCK_END
                                                08:aRoomSetFaceTexture
                                                        $$CHILD_BLOCK_START
                                                        10:2:7:Room
                                                        10:4:30:FaceNum
                                                        10:14:1:Texture
                                                        $$CHILD_BLOCK_END
                                                08:aAISetState
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:On/Off
                                                        10:1:0:26:Object
                                                        $$CHILD_BLOCK_END
                                                08:aPortalRenderSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:Enable/Disable
                                                        10:4:2:PortalNum
                                                        10:2:8:Room
                                                        10:5:1:DoublesidedFlag
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarInc
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:UserVar
                                                        $$CHILD_BLOCK_END
                                                08:aUserFlagSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:10:UserFlag
                                                        10:5:1:True/False
                                                        $$CHILD_BLOCK_END
                                                08:aObjGhostSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:Ghost/Unghost
                                                        10:1:0:22:Object
                                                        $$CHILD_BLOCK_END
                                                08:aAddObjectToInventory
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:22:Object
                                                        10:1:1:-1:PlayerObject
                                                        10:5:0:Spewable
                                                        $$CHILD_BLOCK_END
                                                08:aSoundPlaySteaming
                                                        $$CHILD_BLOCK_START
                                                        10:19:0:Sound
                                                        10:9:1.000000:Volume
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:2ndInvalidPassOffense:Message
                                                        $$CHILD_BLOCK_END
                                                08:aRoomSetFaceTexture
                                                        $$CHILD_BLOCK_START
                                                        10:2:7:Room
                                                        10:4:30:FaceNum
                                                        10:14:2:Texture
                                                        $$CHILD_BLOCK_END
                                                08:aMatcenSetState
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:Activate/Deactivate
                                                        10:17:0:4:Matcen
                                                        $$CHILD_BLOCK_END
                                                08:aUserFlagSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:10:UserFlag
                                                        10:5:1:True/False
                                                        $$CHILD_BLOCK_END
                                                08:aSoundPlayObject
                                                        $$CHILD_BLOCK_START
                                                        10:12:1:Sound
                                                        10:1:0:33:Object
                                                        10:9:1.000000:Volume
                                                        $$CHILD_BLOCK_END
                                                08:aSoundPlayObject
                                                        $$CHILD_BLOCK_START
                                                        10:12:1:Sound
                                                        10:1:0:34:Object
                                                        10:9:1.000000:Volume
                                                        $$CHILD_BLOCK_END
                                                08:aObjGhostSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:0:Ghost/Unghost
                                                        10:1:0:22:Object
                                                        $$CHILD_BLOCK_END
                                                08:aAddObjectToInventory
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:22:Object
                                                        10:1:1:-1:PlayerObject
                                                        10:5:0:Spewable
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:0:22:Object
                                                $$CHILD_BLOCK_END
                                        08:aAddObjectToInventory
                                                $$CHILD_BLOCK_START
                                                10:1:0:22:Object
                                                10:1:1:-1:PlayerObject
                                                10:5:0:Spewable
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:SecurityPassNotUsableHere:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Y-1 Security Pass Useage Matrix
        $$CHILD_BLOCK_START
        01:1:24
        02:25
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:2:5:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MediumSecurityClearance:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:4:30:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:11:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:1:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:16.000000:Time
                                10:10:0:13:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:24:Object
                                $$CHILD_BLOCK_END
                        08:aAddObjectToInventory
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                10:1:1:-1:PlayerObject
                                10:5:0:Spewable
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SecurityPassNotUsableHere:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:G-1 Security Pass Useage Matrix
        $$CHILD_BLOCK_START
        01:1:23
        02:25
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjRoom:Room
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:2:7:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MinimumSecurityClearance:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:8:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:4:30:FaceNum
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
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
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:10:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:1:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:13.000000:Time
                                10:10:0:12:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:23:Object
                                $$CHILD_BLOCK_END
                        08:aAddObjectToInventory
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                10:1:1:-1:PlayerObject
                                10:5:0:Spewable
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SecurityPassNotUsableHere:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Intro Camera Sequence
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:13:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:21:TotallyNotUsedTarget
                        10:16:14:PlayerPath
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:Intro VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:9:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Rescue Shuttle Don't Shoot Me!
        $$CHILD_BLOCK_START
        01:1:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DontShootMe:Message
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:9999999.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Chemical Droid Start Switch
        $$CHILD_BLOCK_START
        01:1:35
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
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SPUDisBorn:Message
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object
                                10:4:0:StartFrame
                                10:4:10:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:5:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:6:Matcen
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ChemicalReactionSwitches:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:DO NOTHING
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Chemical Droid KILL Switch
        $$CHILD_BLOCK_START
        01:1:36
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
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SPUDkilled:Message
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:4:0:StartFrame
                                10:4:20:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:Activate/Deactivate
                                10:17:0:5:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:Activate/Deactivate
                                10:17:0:6:Matcen
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object
                                10:4:10:StartFrame
                                10:4:20:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ChemicalReactionSwitches:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:DO NOTHING
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Chemical Droid Created
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Picker
                        10:4:0:PickerPoint
                        06:qObjSavedHandle:Pickee
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Chemical Ball Created
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObject
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Picker
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:0:PickerPoint
                        06:qObjSavedHandle:Pickee
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:0:PickeePoint
                        10:5:1:Aligned
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Chemical Droid KILL Room
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:1:GoalID
                        07:1:0
                        10:10:1:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:10:StartFrame
                        10:4:20:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SPUDscores:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Chemical Droid Ball Pickup
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:0:GoalID
                        07:1:0
                        10:10:1:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:9:Room
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:1:GoalID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SPUDhasTheBall:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:FOG Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:10:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:11:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:12:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:13:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:14:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:15:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:16:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:17:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:18:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:19:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:20:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:21:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:22:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:23:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:24:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:25:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:26:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:27:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:28:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:29:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:30:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:31:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:32:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:33:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:34:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:35:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:36:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:37:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:38:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:39:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:40:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:41:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:42:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:43:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:44:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:45:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:46:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:47:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:48:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:49:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:50:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:51:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:52:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:OOPS!  SPUD has dropped the ball!
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:11:ObjectType
                        07:1:0
                        06:qObjType:ObjectType
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:200.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:200.000000:Depth
                        10:6:15.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:20.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:200.000000:Depth
                        10:6:15.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:20.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:25.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:400.000000:Depth
                        10:6:30.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:17:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:25.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:18:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:400.000000:Depth
                        10:6:30.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:200.000000:Depth
                        10:6:15.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:20:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:200.000000:Depth
                        10:6:20.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:21:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:25.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:22:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:30.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:23:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:300.000000:Depth
                        10:6:35.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:24:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:400.000000:Depth
                        10:6:40.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:25:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:400.000000:Depth
                        10:6:40.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:26:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:27:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:800.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:28:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:29:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:32:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:33:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:34:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:35:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:36:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:37:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:38:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:39:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:40:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:41:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:42:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:43:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:500.000000:Depth
                        10:6:45.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:44:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:45:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:46:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:47:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:48:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:49:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:50:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:51:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:52:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:0.000000:Blue
                        10:6:600.000000:Depth
                        10:6:50.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:40:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:41:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:42:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:43:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:44:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:45:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:46:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:47:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:48:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:49:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:50:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:51:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:256:FaceNum
                        10:14:4:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:269:FaceNum
                        10:14:5:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:219:FaceNum
                        10:14:6:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:206:FaceNum
                        10:14:6:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:188:FaceNum
                        10:14:6:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:170:FaceNum
                        10:14:6:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:4:238:FaceNum
                        10:14:7:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:4:240:FaceNum
                        10:14:7:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:4:239:FaceNum
                        10:14:7:Texture
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:3:PortalNum
                        10:2:10:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:4:PortalNum
                        10:2:10:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:5:PortalNum
                        10:2:10:Room
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
                        10:4:2:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:44:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:45:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:46:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:47:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:48:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:49:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:50:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:51:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:52:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:7:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:8:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:9:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:10:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:11:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:12:Matcen
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ChemicalReactionAlert:Message
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Rescue Shuttle Impatient Path
        $$CHILD_BLOCK_START
        01:1:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:2:GoalID
                        07:1:0
                        10:10:1:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:15:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:35.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Acid Vat Forcefields Start
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
                        10:4:1:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Prisoners Start & Ghosted Objects
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:55:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:56:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:58:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:59:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:60:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:61:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Prisoner Evacuation
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
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:53:Room
                        10:4:319:FaceNum
                        10:14:8:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:53:Room
                        10:4:355:FaceNum
                        10:14:8:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:53:Room
                        10:4:125:FaceNum
                        10:14:8:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:53:Room
                        10:4:165:FaceNum
                        10:14:8:Texture
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:62:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:63:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:64:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:65:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:66:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:67:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:70:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:55:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:56:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:58:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:59:Object
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:WhatTheHell:GameMessage
                        10:8:IncomingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:13:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:14:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Chemical Center Breakable Glass Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:4:239:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:4:238:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:4:240:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:272:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:270:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:4:271:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Found Sweitzer in Minimum Security
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:0:61:Object
                                        10:6:80.000000:Distance
                                        10:15:1048585:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                                06:qObjCanSeeObjAdvanced:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:61:TargetObject
                                        10:4:60:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:15:1048585:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:SweitzerMINLockedOut:GameMessage
                        10:8:IncomingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:54:Room
                        10:6:3.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:13:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Found Sweitzer in Maximum Security
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:SavedObjectSlot
                                        10:4:360:Cone
                                        10:1:0:60:Object
                                        10:6:80.000000:Distance
                                        10:15:1048585:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                                06:qObjCanSeeObjAdvanced:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:60:TargetObject
                                        10:4:60:Cone
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:15:1048585:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:SweitzerMAX:GameMessage
                        10:8:IncomingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingPulse
                        $$CHILD_BLOCK_START
                        10:2:47:Room
                        10:6:3.000000:PulseTime
                        10:6:0.000000:PulseOffset
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:12:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:14:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Shuttle Taking Enemy Fire
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsType:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:10:0:5:ObjectType
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsType:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjParent:Object
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                $$CHILD_BLOCK_END
                                        10:10:0:2:ObjectType
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ShuttleUnderAttack:Message
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:9999999.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Shuttle Going To Sweitzer
        $$CHILD_BLOCK_START
        01:1:0
        02:5
        03:0
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
                                        10:10:0:8:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                10:5:1:Literal
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:2:Path
                        10:15:4096:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Rescue Shuttle Landing for Sweitzer
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:3:GoalID
                        07:1:0
                        10:10:1:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:4.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalLandOnObject
                        $$CHILD_BLOCK_START
                        10:1:0:0:LandingObject
                        10:4:0:LanderAttachPoint
                        10:1:0:10:ObjectToLandOn
                        10:4:0:LandOnObjectAttachPoint
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:4:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Maximum Checkpoint Monitor RESET
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:3:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:30:FaceNum
                        10:14:10:Texture
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:4:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:3:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Medium Checkpoint Monitor RESET
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:2:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:4:30:FaceNum
                        10:14:10:Texture
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:6:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:3:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Minimum Checkpoint Monitor RESET
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:1:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:4:30:FaceNum
                        10:14:10:Texture
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:8:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:3:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Maximum Checkpoint Reset Timer
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Medium Checkpoint Reset Timer
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Minimum Checkpoint Reset Timer
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:10:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Rescue Shuttle Loading Sweitzer
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:4:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:54:Room
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:7.300000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LoadingSweitzer:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Rescue Shuttle Loaded
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:5:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:2:StartFrame
                        10:4:4:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LoadedSweitzer:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aUnAttachObject
                        $$CHILD_BLOCK_START
                        10:1:0:0:AttachedObject
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:15:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:16:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Rescue Shuttle Escape
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:6:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:2:Path
                        10:15:16781312:AIGoalFlags
                        10:10:0:5:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Rescue Shuttle Exit
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:5:GoalID
                        07:1:0
                        10:10:1:0:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:16:16:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:75.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:13:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:End Level Ready
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:End Level Sequence
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                10:5:1:Literal
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:17:CameraPath
                        10:16:18:PlayerPath
                        10:6:10.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Shuttle Landing Platform HIDE
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Music-Intro
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
00:62:Music-Intro 2
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Music-Start Area 2
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Music-Start Area 1
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Music-Terrain 2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Music-Terrain 1
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Music-After FF 3
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
00:66:Music-After FF 2
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
00:65:Music-After FF 1
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Music-Acid Caves 3
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
00:69:Music-Acid Caves 2
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
00:68:Music-Acid Caves
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
00:72:Music-Out of Caves 2
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
00:71:Music-Out of Caves 1
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
00:75:Music-Minimum3
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Music-Minimum2
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Music-Minimum
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Music-Medium 2
        $$CHILD_BLOCK_START
        01:0:19
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
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Music-Medium 1
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Music-Final
        $$CHILD_BLOCK_START
        01:0:21
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
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Music-Maximum 3
        $$CHILD_BLOCK_START
        01:0:22
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
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Music-Maximum 2
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
                        10:10:0:8:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Music-Maximum 1
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
                        10:10:0:8:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Tower Infiltrated... Next Goal
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:18:1:-1:Level Goal
                        07:1:0
                        10:18:0:8:Level Goal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:6:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Hangar Access Gained... Next Goal
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:18:1:-1:Level Goal
                        07:1:0
                        10:18:0:0:Level Goal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:9:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Novak Prison Records Node H Destroyed
        $$CHILD_BLOCK_START
        01:1:71
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Novak Prison Records Node G Destroyed
        $$CHILD_BLOCK_START
        01:1:72
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Novak Prison Records Node F Destroyed
        $$CHILD_BLOCK_START
        01:1:73
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Novak Prison Records Node E Destroyed
        $$CHILD_BLOCK_START
        01:1:74
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Novak Prison Records Node D Destroyed
        $$CHILD_BLOCK_START
        01:1:75
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Novak Prison Records Node C Destroyed
        $$CHILD_BLOCK_START
        01:1:76
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Novak Prison Records Node B Destroyed
        $$CHILD_BLOCK_START
        01:1:77
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Novak Prison Records Node A Destroyed
        $$CHILD_BLOCK_START
        01:1:78
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:55:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Novak Prison Records Node P Destroyed
        $$CHILD_BLOCK_START
        01:1:79
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:Novak Prison Records Node O Destroyed
        $$CHILD_BLOCK_START
        01:1:80
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Novak Prison Records Node N Destroyed
        $$CHILD_BLOCK_START
        01:1:81
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Novak Prison Records Node M Destroyed
        $$CHILD_BLOCK_START
        01:1:82
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Novak Prison Records Node L Destroyed
        $$CHILD_BLOCK_START
        01:1:83
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Novak Prison Records Node K Destroyed
        $$CHILD_BLOCK_START
        01:1:84
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Novak Prison Records Node J Destroyed
        $$CHILD_BLOCK_START
        01:1:85
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Novak Prison Records Node I Destroyed
        $$CHILD_BLOCK_START
        01:1:86
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RecordsNodeDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:7.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:64:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:56:Room
                                10:4:65:FaceNum
                                10:14:11:Texture
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:15.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:17:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Novak Super Computer Destroyed
        $$CHILD_BLOCK_START
        01:1:87
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ComputerDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:57:Room
                        10:4:158:FaceNum
                        10:14:11:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:57:Room
                        10:4:157:FaceNum
                        10:14:11:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:57:Room
                        10:4:225:FaceNum
                        10:14:11:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:57:Room
                        10:4:189:FaceNum
                        10:14:11:Texture
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:15.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:17:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:Perimeter Secure Forcefield Down
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:7:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:ShuttleMoveToTower:GameMessage
                        10:8:IncomingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:ESCORT SHUTTLE WARNING!
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qAIIsObjectAware:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:0:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:0:8:TimerID
                                07:1:0
                                10:10:2:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EscortShuttle:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Chemical Drone Birth Room WIND
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
                        10:2:58:Room
                        10:6:0.156000:X
                        10:6:0.031000:Y
                        10:6:0.988000:Z
                        10:6:5.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:End Level VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:18:0:16:Level Goal
                        07:1:0
                        10:18:1:1:Level Goal
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
                                        10:10:0:16:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:4:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:5:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:All Prison Records Destroyed VOX Flag
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:18:0:17:Level Goal
                        07:1:0
                        10:18:1:1:Level Goal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:16:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:Maximum VOX Trigger
        $$CHILD_BLOCK_START
        01:0:25
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:Medium VOX Trigger
        $$CHILD_BLOCK_START
        01:0:26
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:Minimum VOX Trigger
        $$CHILD_BLOCK_START
        01:0:27
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:Tubbs Sentry VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:88:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:89:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
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
00:106:Hazardous Materials VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qRoomHasPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
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
00:108:Evacuation VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:11:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:9:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:Maintenance Emergency VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:12:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:10:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Medical Assistance VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:13:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:11:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:Hazardous Substances VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:14:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:8:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:Biohazard VOX
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:10:TimerID
                        07:1:0
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:12:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:Entering the Waste Pipes to Find Passkey R-1
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:18:0:8:Level Goal
                        07:1:0
                        10:18:1:1:Level Goal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:6:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
