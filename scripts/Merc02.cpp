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
// Filename:	Merc02.cpp
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

#define ID_CUSTOM_OBJECT_1119 0x001
#define ID_CUSTOM_OBJECT_10EC 0x002
#define ID_CUSTOM_OBJECT_08F6 0x003
#define ID_CUSTOM_OBJECT_08F8 0x004
#define ID_CUSTOM_OBJECT_08F7 0x005
#define ID_CUSTOM_OBJECT_08FB 0x006
#define ID_CUSTOM_OBJECT_08FC 0x007
#define ID_CUSTOM_OBJECT_08FE 0x008
#define ID_CUSTOM_OBJECT_08FD 0x009
#define ID_CUSTOM_OBJECT_08FF 0x00a
#define ID_CUSTOM_OBJECT_0900 0x00b
#define ID_CUSTOM_OBJECT_0901 0x00c
#define ID_CUSTOM_OBJECT_0902 0x00d
#define ID_CUSTOM_OBJECT_1017 0x00e
#define ID_CUSTOM_OBJECT_0818 0x00f
#define ID_CUSTOM_OBJECT_1019 0x010
#define ID_CUSTOM_OBJECT_10CF 0x011
#define ID_CUSTOM_OBJECT_30B2 0x012
#define ID_CUSTOM_OBJECT_10B1 0x013
#define ID_CUSTOM_OBJECT_1040 0x014
#define ID_CUSTOM_OBJECT_1041 0x015
#define ID_CUSTOM_OBJECT_103F 0x016
#define ID_CUSTOM_OBJECT_08DE 0x017
#define ID_CUSTOM_OBJECT_110E 0x018
#define ID_CUSTOM_OBJECT_10CD 0x019
#define ID_CUSTOM_OBJECT_08A6 0x01a
#define ID_CUSTOM_OBJECT_08A5 0x01b
#define ID_CUSTOM_OBJECT_1112 0x01c
#define ID_CUSTOM_OBJECT_0913 0x01d
#define ID_CUSTOM_OBJECT_083D 0x01e
#define ID_CUSTOM_OBJECT_084A 0x01f
#define ID_CUSTOM_OBJECT_1048 0x020
#define ID_CUSTOM_OBJECT_1111 0x021
#define ID_CUSTOM_OBJECT_1067 0x022
#define ID_CUSTOM_OBJECT_088C 0x023
#define ID_CUSTOM_OBJECT_108B 0x024
#define ID_CUSTOM_OBJECT_0883 0x025
#define ID_CUSTOM_OBJECT_1884 0x026
#define ID_CUSTOM_OBJECT_106F 0x027
#define ID_CUSTOM_OBJECT_1071 0x028
#define ID_CUSTOM_OBJECT_0894 0x029
#define ID_CUSTOM_OBJECT_0893 0x02a
#define ID_CUSTOM_OBJECT_0806 0x02b
#define ID_CUSTOM_OBJECT_1842 0x02c
#define ID_CUSTOM_OBJECT_082F 0x02d

#define ID_TRIGGER_0006 0x02e
#define ID_TRIGGER_0005 0x02f
#define ID_TRIGGER_0004 0x030
#define ID_TRIGGER_0000 0x031
#define ID_TRIGGER_0001 0x032
#define ID_TRIGGER_0002 0x033
#define ID_TRIGGER_0003 0x034
#define ID_TRIGGER_0007 0x035
#define ID_TRIGGER_0008 0x036
#define ID_TRIGGER_0011 0x037
#define ID_TRIGGER_0009 0x038
#define ID_TRIGGER_000A 0x039
#define ID_TRIGGER_000B 0x03a
#define ID_TRIGGER_000C 0x03b
#define ID_TRIGGER_000E 0x03c
#define ID_TRIGGER_000F 0x03d
#define ID_TRIGGER_0010 0x03e

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

class CustomObjectScript_1119 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10EC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08F6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08F8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08F7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0900 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0901 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0902 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0818 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1019 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10CF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_30B2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10B1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1040 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1041 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_103F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08DE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_110E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10CD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1112 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0913 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1048 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1111 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1067 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_088C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_108B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0883 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1884 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_106F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1071 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0894 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0893 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0806 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1842 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_082F : public BaseScript {
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

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0011 : public BaseScript {
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

class TriggerScript_000E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_037 = 0;
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
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_125 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_037 = 0;
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
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_125 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
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
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

#include "AIGame3_External.h"

/*
$$ENUM Region
0:Intro
1:Restricted
2:Assassination
3:Escape
4:Victory
5:Unrestricted
$$END
*/

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

/*
$$ACTION
Custom
Emit [f:Number=20.0] sparks from [o:Object] at [i:Gunpoint]
aEmitSparksFromGunpoint
Make object spark
  Makes an object emit sparks

Parameters:
  Number: the number of sparks to create
  Object: the object to make sparks come out of
  Gunpoint: the gunpoint
$$END
*/
void aEmitSparksFromGunpoint(float num_sparks, int objhandle, int gunpoint) {
  int room;
  vector pos;

  if (!qObjExists(objhandle))
    return;

  Obj_GetGunPos(objhandle, gunpoint, &pos);
  Obj_Value(objhandle, VF_GET, OBJV_I_ROOMNUM, &room);
  Game_CreateRandomSparks((int)num_sparks, &pos, room);
}

/*
$$ACTION
Custom
Set [o:Object] turn rate to [f:Turn Rate]
aSetTurnRate
Set Turn Rate of Object

Parameters:
  Object: the object to make sparks come out of
  Turn Rate: the turn rate
$$END
*/
void aSetTurnRate(int objhandle, float turn_rate) {
  if (!qObjExists(objhandle))
    return;

  AI_Value(objhandle, VF_SET, AIV_F_MAX_TURN_RATE, &turn_rate);
}

/*
$$QUERY
Custom
b:[o:Security Camera] has been alerted
qSecurityCameraAlerted
Security Camera has been alerted
Determines if a security camera has been alerted

Parameters:
  Security Camera: the security camera object to check
$$END
*/
bool qSecurityCameraAlerted(int obj_handle) {
  bool camera_alerted;

  if (!qObjExists(obj_handle))
    return false;

  SendCommand(obj_handle, obj_handle, SC_COM_GET_ALERT_STATUS, &camera_alerted);

  return camera_alerted;
}

/*
$$QUERY
Custom
b:Beam between [o:Beam Source A] and [o:Beam Source B] is hitting a player
qBeamHittingPlayer
Beam Is Hitting a Player
Checks if a security beam is currently colliding with a player

Parameters:
        Beam Source A
        Beam Source B
$$END
*/
bool qBeamHittingPlayer(int beam1_handle, int beam2_handle) {
  // see if anything is in the way
  ray_info ray;
  int flags, fate;
  vector start_pos, end_pos, landing_pos;
  int start_room, landing_room;

  if (!qObjExists(beam1_handle))
    return false;
  if (!qObjExists(beam2_handle))
    return false;

  Obj_Value(beam1_handle, VF_GET, OBJV_V_POS, &start_pos);
  Obj_Value(beam1_handle, VF_GET, OBJV_I_ROOMNUM, &start_room);
  Obj_Value(beam2_handle, VF_GET, OBJV_V_POS, &end_pos);

  flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_ONLY_PLAYER_OBJ | FQ_PLAYERS_AS_SPHERE |
          FQ_IGNORE_WALLS;
  fate = FVI_RayCast(beam1_handle, &start_pos, &end_pos, start_room, 50.0f, flags, &ray);
  if (fate == HIT_OBJECT) {
    int type;
    Obj_Value(ray.hit_object, VF_GET, OBJV_I_TYPE, &type);
    if (type == OBJ_PLAYER) {
      return true;
    }
  }

  return false;
}

/*
$$QUERY
Custom
f:Convert [u:Texture ID] to float
qConvertTextureIDToFloat
Converts Texture ID to float (so it can be stored in user var)

Parameters:
  Texture ID: the texture id
$$END
*/
float qConvertTextureIDToFloat(int texture_id) { return ((float)texture_id); }

/*
$$QUERY
Custom
u:Convert [f:Value] to Texture ID
qConvertFloatToTextureID
Converts float to Texture ID (so user var can be passed to texture id parameter)

Parameters:
  Value: the float texture id
$$END
*/
int qConvertFloatToTextureID(float value) { return ((int)value); }

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

#define NUM_DOOR_NAMES 7
static const char *const Door_names[NUM_DOOR_NAMES] = {"MainGateDoor", "GenHangarDoor", "ResEntDoor", "GeneralDoor",
                                                       "CompDoor",     "LastDoor",      "ArmoryDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 136
static const char *const Object_names[NUM_OBJECT_NAMES] = {"LR1Sound",
                                                           "LR2Sound",
                                                           "RepairRoomWelder",
                                                           "WorkerScrewup",
                                                           "Welder2",
                                                           "Welder3",
                                                           "LR1Light",
                                                           "LR2Light",
                                                           "ResHallALight",
                                                           "ResHallALight2",
                                                           "ArmoryLight",
                                                           "HallCSLight",
                                                           "HallCLight1",
                                                           "HallCLight2",
                                                           "CompEscapeFan",
                                                           "MainGateGuard1",
                                                           "MainGateGuard2",
                                                           "TowerScanner",
                                                           "WeaponCheckPoint",
                                                           "Beam1Source",
                                                           "Beam2Source",
                                                           "BeamSource3",
                                                           "BeamSource4",
                                                           "BeamSource5",
                                                           "BeamSource6",
                                                           "BeamSource7",
                                                           "BeamSource8",
                                                           "BeamSource10",
                                                           "BeamSource11",
                                                           "BeamSource12",
                                                           "BeamSource13",
                                                           "LRSBeam01a",
                                                           "LRSBeam01b",
                                                           "LRSBeam03a",
                                                           "LRSBeam03b",
                                                           "LRSBeam04a",
                                                           "LRSBeam04b",
                                                           "LRSBeam06a",
                                                           "LRSBeam06b",
                                                           "EndBeamA1",
                                                           "EndBeamA2",
                                                           "EndBeamB1",
                                                           "EndBeamB2",
                                                           "EndBeamC1",
                                                           "EndBeamC2",
                                                           "HTrooper01",
                                                           "EndHTrooper01",
                                                           "EndHTrooper02",
                                                           "LaserPickup",
                                                           "GenGuardHeavyT01",
                                                           "GenGuardTrooper01",
                                                           "GenGuardTrooper02",
                                                           "GenGuardTrooper03",
                                                           "GenGuardSwatter01",
                                                           "GenGuardSwatter02",
                                                           "ResHallATurret01",
                                                           "ResHallATurret2",
                                                           "ArmoryTurret",
                                                           "ResHallCTurret",
                                                           "HallCTurret01",
                                                           "HallCTurret02",
                                                           "LR1PipeCam1",
                                                           "CrateStackFloor",
                                                           "BasementCeiling",
                                                           "WorkerScrewupMachi",
                                                           "GeneralsShip",
                                                           "TurretControl",
                                                           "GenLandingPad",
                                                           "HTrooper01Wall",
                                                           "EndTrooper01wall",
                                                           "EndTrooper02wall",
                                                           "GeneralBarrels",
                                                           "GeneralStack",
                                                           "WorkerScrewup2",
                                                           "WorkerScrewup3",
                                                           "Lifter (Hangar)",
                                                           "Welder (cargoship)",
                                                           "FlybyShip",
                                                           "Tracker01",
                                                           "Tracker02",
                                                           "StFactory02Constru",
                                                           "InfectedDataCartri",
                                                           "LR1Pipe",
                                                           "LR1PipeCam2",
                                                           "LaserRoom02Pipe01",
                                                           "L02Pipe1Cam",
                                                           "LaserRoom02Pipe02",
                                                           "L02Pipe2Cam",
                                                           "TowerFT1Cam",
                                                           "TowerFB1Cam",
                                                           "TowerFT2Cam",
                                                           "TowerFB2Cam",
                                                           "TowerFB3Cam",
                                                           "TowerFT3Cam",
                                                           "TowerBT1Cam",
                                                           "TowerBB1Cam",
                                                           "TowerBT2Cam",
                                                           "TowerBB2Cam",
                                                           "TowerBB3Cam",
                                                           "TowerBT3Cam",
                                                           "CrateStack",
                                                           "WorkerScrewupCam",
                                                           "WorkerScrewupCam2",
                                                           "DataCartridge",
                                                           "DataPosition",
                                                           "EndSpew1",
                                                           "EndSpew2",
                                                           "EndSpew3",
                                                           "EndSpew4",
                                                           "EndBeamA1Pos",
                                                           "EndBeamA2Pos",
                                                           "EndBeamB1Pos",
                                                           "EndBeamB2Pos",
                                                           "EndBeamC1Pos",
                                                           "EndBeamC2Pos",
                                                           "HallCTrooper1",
                                                           "HallCTrooper2",
                                                           "RHBPatTroop01",
                                                           "RHBPatTroop02",
                                                           "ArmoryDoorSwitch",
                                                           "CentralFFSwitch",
                                                           "HallCSTrooper",
                                                           "DataCam1",
                                                           "DataCam2",
                                                           "DataCam3",
                                                           "ResEntSecCam01",
                                                           "ResHallASecCam01",
                                                           "ResHallASecCam02",
                                                           "ArmorySecCam",
                                                           "ResHallCSCam",
                                                           "HallCsecCam01",
                                                           "HallCsecCam02",
                                                           "ResEntDoor",
                                                           "SuperDuperLaser",
                                                           "ResHallATrooper",
                                                           "ResHallATrooper2"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 23
static const char *const Room_names[NUM_ROOM_NAMES] = {"Weapon Check",
                                                       "LaserRoom01",
                                                       "LaserRoom01b",
                                                       "LaserRoom02",
                                                       "LaserRoom02b",
                                                       "EscapePipe1",
                                                       "EscapePipe2",
                                                       "ExitFanRoom",
                                                       "Comp01Wind",
                                                       "Comp02Wind",
                                                       "Comp03Wind",
                                                       "Comp04Wind",
                                                       "LaserRoom01BotSpaw",
                                                       "LaserRoom02Spawn01",
                                                       "LaserRoom02Spawn02",
                                                       "ScanTower",
                                                       "MineEntrance",
                                                       "CompHub",
                                                       "Comp01",
                                                       "Comp02",
                                                       "Comp03",
                                                       "Comp04",
                                                       "CentralFFRoom"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 17
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "LR1MonitorHit",     "LR2Monitor1Hit",     "LR2Monitor2Hit",     "GateMonitor1",       "GateMonitor2",
    "EnteredMainGate",   "WeaponCheckEntered", "WorkerScrewup",      "GeneralShipLanding", "LeftHangarArea",
    "HTrooper01Trigger", "EndTrooperTrigger",  "ArmoryGuardTrigger", "EscapeTrigger",      "CrateRoomEntered",
    "ResAreaTrigger",    "LeftResArea"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 7
static const char *const Sound_names[NUM_SOUND_NAMES] = {"Merc2LaserBeam", "Merc2AlertSiren",       "Merc2IGSqueel",
                                                         "Powerup pickup", "Merc2ShortingComputer", "AmbSwitch31",
                                                         "AmbSwitch41"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 12
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {
    "M02MonitorScreen", "Stlaser",    "Stlaser25alpha", "Stlaser50alpha", "Stlaser75alpha",    "M02_Scanning",
    "M02_Cleared",      "Lightning4", "M02_Aborted",    "M02_Ready",      "M02_BreachedNoDes", "FunkyEffect2"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 66
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCamPath",
                                                       "IntroPlayerPath",
                                                       "LifterPath",
                                                       "WelderPathA",
                                                       "FlybyPath",
                                                       "Tracker01Path",
                                                       "Tracker02Path",
                                                       "BeamPath1",
                                                       "BeamPath2",
                                                       "BeamPath3",
                                                       "BeamPath4",
                                                       "BeamPath5",
                                                       "BeamPath6",
                                                       "BeamPath7",
                                                       "BeamPath8",
                                                       "BeamPath10",
                                                       "BeamPath11",
                                                       "BeamPath12",
                                                       "BeamPath13",
                                                       "HTClawAmbientPath",
                                                       "BeamPath1R",
                                                       "BeamPath2R",
                                                       "BeamPath3R",
                                                       "BeamPath4R",
                                                       "BeamPath5R",
                                                       "BeamPath6R",
                                                       "BeamPath7R",
                                                       "BeamPath8R",
                                                       "BeamPath10R",
                                                       "BeamPath11R",
                                                       "BeamPath12R",
                                                       "BeamPath13R",
                                                       "WpnCheckEntryPath",
                                                       "WpnCheckExitPath",
                                                       "WorkerScrewupPath",
                                                       "WorkerScrewup3Path",
                                                       "GeneralCamPath",
                                                       "GeneralLandingPath",
                                                       "GeneralLandingPath2",
                                                       "EndBeamA1Path",
                                                       "EndBeamA2Path",
                                                       "EndBeamB1Path",
                                                       "EndBeamB2Path",
                                                       "EndBeamC1Path",
                                                       "EndBeamC2Path",
                                                       "HTrooper01Path",
                                                       "HallCTrooper1Path",
                                                       "HallCTrooper2Path",
                                                       "EndTrooper2Path",
                                                       "EndTrooper1Path",
                                                       "ArmoryTrooper1Path",
                                                       "ArmoryTrooper2Path",
                                                       "ArmoryGuardPath",
                                                       "ArmoryGuardPath2",
                                                       "ArmoryGuardPath3",
                                                       "HallCSTrooperPath",
                                                       "StormtrooperClawPath",
                                                       "HeavyTrooperClawPath",
                                                       "EndCamPath",
                                                       "PlayerEndPath",
                                                       "ResHallATrooperPath",
                                                       "ResHallATrooper2Path",
                                                       "LR1MatcenPath",
                                                       "LR2Matcen1Path",
                                                       "LR2Matcen2Path",
                                                       "WelderPathB"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 7
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {
    "WpnGuard1Matcen",    "LaserRoom1Matcen",   "LaserRoom2Matcen1", "LaserRoom2Matcen2",
    "STrooperClawMatcen", "HTrooperClawMatcen", "ArmoryGadgetMatcen"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 18
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Disable Forcefields in Laser Room A",
                                                       "Disable Forcefields in Laser Room B",
                                                       "Get Cleared at Scanning Tower",
                                                       "Enter Base",
                                                       "Override Main Gate System",
                                                       "Pass Through Weapon Checkpoint",
                                                       "Bypass Restricted Area Checkpoint",
                                                       "Acquire a Weapon",
                                                       "Enter Restricted Area",
                                                       "Get Inside Restricted Area",
                                                       "Create a Diversion",
                                                       "Assassinate General Morgan",
                                                       "Obtain Failsafe Data",
                                                       "Place Infected Cartridge",
                                                       "Destroy Mainframe Computer",
                                                       "Escape",
                                                       "Destroy Exit Tunnel Guards",
                                                       "Deactivate Central Forcefield"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 31
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroText",
                                                             "InfectedDataCartridgeName",
                                                             "LaserBeamTriggered",
                                                             "ScanTowerEntered",
                                                             "MainGateOpening",
                                                             "ScanStarted",
                                                             "GateSecurityAlerted",
                                                             "WpnCheckEntered",
                                                             "WeaponCheckAborted",
                                                             "WpnCheckStarted",
                                                             "WeaponsRemoved",
                                                             "WeaponsChecked",
                                                             "WeaponGuardHit",
                                                             "FoundBackDoor",
                                                             "TurretControlDown",
                                                             "WorkerMessage",
                                                             "Empty",
                                                             "GeneralDead",
                                                             "DataCartridgeName",
                                                             "DataCartridgeUsed",
                                                             "InfectedDataPlaced",
                                                             "DataCartridgeStillThere",
                                                             "TooFarFromDataPosition",
                                                             "EscapeTime",
                                                             "EndGuards",
                                                             "ExitDoor",
                                                             "ArmoryDoorUnlocked",
                                                             "CentralFFDown",
                                                             "SecCamSpottedUs",
                                                             "ResAreaEntrance",
                                                             "NeedAWeapon"};
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
    strcpy(filename, "Merc02.msg");
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
  case ID_CUSTOM_OBJECT_1119:
    return new CustomObjectScript_1119;
    break;
  case ID_CUSTOM_OBJECT_10EC:
    return new CustomObjectScript_10EC;
    break;
  case ID_CUSTOM_OBJECT_08F6:
    return new CustomObjectScript_08F6;
    break;
  case ID_CUSTOM_OBJECT_08F8:
    return new CustomObjectScript_08F8;
    break;
  case ID_CUSTOM_OBJECT_08F7:
    return new CustomObjectScript_08F7;
    break;
  case ID_CUSTOM_OBJECT_08FB:
    return new CustomObjectScript_08FB;
    break;
  case ID_CUSTOM_OBJECT_08FC:
    return new CustomObjectScript_08FC;
    break;
  case ID_CUSTOM_OBJECT_08FE:
    return new CustomObjectScript_08FE;
    break;
  case ID_CUSTOM_OBJECT_08FD:
    return new CustomObjectScript_08FD;
    break;
  case ID_CUSTOM_OBJECT_08FF:
    return new CustomObjectScript_08FF;
    break;
  case ID_CUSTOM_OBJECT_0900:
    return new CustomObjectScript_0900;
    break;
  case ID_CUSTOM_OBJECT_0901:
    return new CustomObjectScript_0901;
    break;
  case ID_CUSTOM_OBJECT_0902:
    return new CustomObjectScript_0902;
    break;
  case ID_CUSTOM_OBJECT_1017:
    return new CustomObjectScript_1017;
    break;
  case ID_CUSTOM_OBJECT_0818:
    return new CustomObjectScript_0818;
    break;
  case ID_CUSTOM_OBJECT_1019:
    return new CustomObjectScript_1019;
    break;
  case ID_CUSTOM_OBJECT_10CF:
    return new CustomObjectScript_10CF;
    break;
  case ID_CUSTOM_OBJECT_30B2:
    return new CustomObjectScript_30B2;
    break;
  case ID_CUSTOM_OBJECT_10B1:
    return new CustomObjectScript_10B1;
    break;
  case ID_CUSTOM_OBJECT_1040:
    return new CustomObjectScript_1040;
    break;
  case ID_CUSTOM_OBJECT_1041:
    return new CustomObjectScript_1041;
    break;
  case ID_CUSTOM_OBJECT_103F:
    return new CustomObjectScript_103F;
    break;
  case ID_CUSTOM_OBJECT_08DE:
    return new CustomObjectScript_08DE;
    break;
  case ID_CUSTOM_OBJECT_110E:
    return new CustomObjectScript_110E;
    break;
  case ID_CUSTOM_OBJECT_10CD:
    return new CustomObjectScript_10CD;
    break;
  case ID_CUSTOM_OBJECT_08A6:
    return new CustomObjectScript_08A6;
    break;
  case ID_CUSTOM_OBJECT_08A5:
    return new CustomObjectScript_08A5;
    break;
  case ID_CUSTOM_OBJECT_1112:
    return new CustomObjectScript_1112;
    break;
  case ID_CUSTOM_OBJECT_0913:
    return new CustomObjectScript_0913;
    break;
  case ID_CUSTOM_OBJECT_083D:
    return new CustomObjectScript_083D;
    break;
  case ID_CUSTOM_OBJECT_084A:
    return new CustomObjectScript_084A;
    break;
  case ID_CUSTOM_OBJECT_1048:
    return new CustomObjectScript_1048;
    break;
  case ID_CUSTOM_OBJECT_1111:
    return new CustomObjectScript_1111;
    break;
  case ID_CUSTOM_OBJECT_1067:
    return new CustomObjectScript_1067;
    break;
  case ID_CUSTOM_OBJECT_088C:
    return new CustomObjectScript_088C;
    break;
  case ID_CUSTOM_OBJECT_108B:
    return new CustomObjectScript_108B;
    break;
  case ID_CUSTOM_OBJECT_0883:
    return new CustomObjectScript_0883;
    break;
  case ID_CUSTOM_OBJECT_1884:
    return new CustomObjectScript_1884;
    break;
  case ID_CUSTOM_OBJECT_106F:
    return new CustomObjectScript_106F;
    break;
  case ID_CUSTOM_OBJECT_1071:
    return new CustomObjectScript_1071;
    break;
  case ID_CUSTOM_OBJECT_0894:
    return new CustomObjectScript_0894;
    break;
  case ID_CUSTOM_OBJECT_0893:
    return new CustomObjectScript_0893;
    break;
  case ID_CUSTOM_OBJECT_0806:
    return new CustomObjectScript_0806;
    break;
  case ID_CUSTOM_OBJECT_1842:
    return new CustomObjectScript_1842;
    break;
  case ID_CUSTOM_OBJECT_082F:
    return new CustomObjectScript_082F;
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
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
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
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
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
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
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
  case ID_CUSTOM_OBJECT_1119:
    delete ((CustomObjectScript_1119 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10EC:
    delete ((CustomObjectScript_10EC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08F6:
    delete ((CustomObjectScript_08F6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08F8:
    delete ((CustomObjectScript_08F8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08F7:
    delete ((CustomObjectScript_08F7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FB:
    delete ((CustomObjectScript_08FB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FC:
    delete ((CustomObjectScript_08FC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FE:
    delete ((CustomObjectScript_08FE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FD:
    delete ((CustomObjectScript_08FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FF:
    delete ((CustomObjectScript_08FF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0900:
    delete ((CustomObjectScript_0900 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0901:
    delete ((CustomObjectScript_0901 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0902:
    delete ((CustomObjectScript_0902 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1017:
    delete ((CustomObjectScript_1017 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0818:
    delete ((CustomObjectScript_0818 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1019:
    delete ((CustomObjectScript_1019 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10CF:
    delete ((CustomObjectScript_10CF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_30B2:
    delete ((CustomObjectScript_30B2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10B1:
    delete ((CustomObjectScript_10B1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1040:
    delete ((CustomObjectScript_1040 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1041:
    delete ((CustomObjectScript_1041 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_103F:
    delete ((CustomObjectScript_103F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08DE:
    delete ((CustomObjectScript_08DE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_110E:
    delete ((CustomObjectScript_110E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10CD:
    delete ((CustomObjectScript_10CD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A6:
    delete ((CustomObjectScript_08A6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A5:
    delete ((CustomObjectScript_08A5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1112:
    delete ((CustomObjectScript_1112 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0913:
    delete ((CustomObjectScript_0913 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083D:
    delete ((CustomObjectScript_083D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084A:
    delete ((CustomObjectScript_084A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1048:
    delete ((CustomObjectScript_1048 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1111:
    delete ((CustomObjectScript_1111 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1067:
    delete ((CustomObjectScript_1067 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_088C:
    delete ((CustomObjectScript_088C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_108B:
    delete ((CustomObjectScript_108B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0883:
    delete ((CustomObjectScript_0883 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1884:
    delete ((CustomObjectScript_1884 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_106F:
    delete ((CustomObjectScript_106F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1071:
    delete ((CustomObjectScript_1071 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0894:
    delete ((CustomObjectScript_0894 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0893:
    delete ((CustomObjectScript_0893 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0806:
    delete ((CustomObjectScript_0806 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1842:
    delete ((CustomObjectScript_1842 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_082F:
    delete ((CustomObjectScript_082F *)ptr);
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
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
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
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
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
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
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
  case ID_CUSTOM_OBJECT_1119:
  case ID_CUSTOM_OBJECT_10EC:
  case ID_CUSTOM_OBJECT_08F6:
  case ID_CUSTOM_OBJECT_08F8:
  case ID_CUSTOM_OBJECT_08F7:
  case ID_CUSTOM_OBJECT_08FB:
  case ID_CUSTOM_OBJECT_08FC:
  case ID_CUSTOM_OBJECT_08FE:
  case ID_CUSTOM_OBJECT_08FD:
  case ID_CUSTOM_OBJECT_08FF:
  case ID_CUSTOM_OBJECT_0900:
  case ID_CUSTOM_OBJECT_0901:
  case ID_CUSTOM_OBJECT_0902:
  case ID_CUSTOM_OBJECT_1017:
  case ID_CUSTOM_OBJECT_0818:
  case ID_CUSTOM_OBJECT_1019:
  case ID_CUSTOM_OBJECT_10CF:
  case ID_CUSTOM_OBJECT_30B2:
  case ID_CUSTOM_OBJECT_10B1:
  case ID_CUSTOM_OBJECT_1040:
  case ID_CUSTOM_OBJECT_1041:
  case ID_CUSTOM_OBJECT_103F:
  case ID_CUSTOM_OBJECT_08DE:
  case ID_CUSTOM_OBJECT_110E:
  case ID_CUSTOM_OBJECT_10CD:
  case ID_CUSTOM_OBJECT_08A6:
  case ID_CUSTOM_OBJECT_08A5:
  case ID_CUSTOM_OBJECT_1112:
  case ID_CUSTOM_OBJECT_0913:
  case ID_CUSTOM_OBJECT_083D:
  case ID_CUSTOM_OBJECT_084A:
  case ID_CUSTOM_OBJECT_1048:
  case ID_CUSTOM_OBJECT_1111:
  case ID_CUSTOM_OBJECT_1067:
  case ID_CUSTOM_OBJECT_088C:
  case ID_CUSTOM_OBJECT_108B:
  case ID_CUSTOM_OBJECT_0883:
  case ID_CUSTOM_OBJECT_1884:
  case ID_CUSTOM_OBJECT_106F:
  case ID_CUSTOM_OBJECT_1071:
  case ID_CUSTOM_OBJECT_0894:
  case ID_CUSTOM_OBJECT_0893:
  case ID_CUSTOM_OBJECT_0806:
  case ID_CUSTOM_OBJECT_1842:
  case ID_CUSTOM_OBJECT_082F:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0010:
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
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0010;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[45];
  static int cust_id_list[45] = {
      ID_CUSTOM_OBJECT_1119, ID_CUSTOM_OBJECT_10EC, ID_CUSTOM_OBJECT_08F6, ID_CUSTOM_OBJECT_08F8,
      ID_CUSTOM_OBJECT_08F7, ID_CUSTOM_OBJECT_08FB, ID_CUSTOM_OBJECT_08FC, ID_CUSTOM_OBJECT_08FE,
      ID_CUSTOM_OBJECT_08FD, ID_CUSTOM_OBJECT_08FF, ID_CUSTOM_OBJECT_0900, ID_CUSTOM_OBJECT_0901,
      ID_CUSTOM_OBJECT_0902, ID_CUSTOM_OBJECT_1017, ID_CUSTOM_OBJECT_0818, ID_CUSTOM_OBJECT_1019,
      ID_CUSTOM_OBJECT_10CF, ID_CUSTOM_OBJECT_30B2, ID_CUSTOM_OBJECT_10B1, ID_CUSTOM_OBJECT_1040,
      ID_CUSTOM_OBJECT_1041, ID_CUSTOM_OBJECT_103F, ID_CUSTOM_OBJECT_08DE, ID_CUSTOM_OBJECT_110E,
      ID_CUSTOM_OBJECT_10CD, ID_CUSTOM_OBJECT_08A6, ID_CUSTOM_OBJECT_08A5, ID_CUSTOM_OBJECT_1112,
      ID_CUSTOM_OBJECT_0913, ID_CUSTOM_OBJECT_083D, ID_CUSTOM_OBJECT_084A, ID_CUSTOM_OBJECT_1048,
      ID_CUSTOM_OBJECT_1111, ID_CUSTOM_OBJECT_1067, ID_CUSTOM_OBJECT_088C, ID_CUSTOM_OBJECT_108B,
      ID_CUSTOM_OBJECT_0883, ID_CUSTOM_OBJECT_1884, ID_CUSTOM_OBJECT_106F, ID_CUSTOM_OBJECT_1071,
      ID_CUSTOM_OBJECT_0894, ID_CUSTOM_OBJECT_0893, ID_CUSTOM_OBJECT_0806, ID_CUSTOM_OBJECT_1842,
      ID_CUSTOM_OBJECT_082F};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[81];
  cust_handle_list[1] = Object_handles[19];
  cust_handle_list[2] = Object_handles[20];
  cust_handle_list[3] = Object_handles[21];
  cust_handle_list[4] = Object_handles[22];
  cust_handle_list[5] = Object_handles[23];
  cust_handle_list[6] = Object_handles[24];
  cust_handle_list[7] = Object_handles[25];
  cust_handle_list[8] = Object_handles[26];
  cust_handle_list[9] = Object_handles[27];
  cust_handle_list[10] = Object_handles[28];
  cust_handle_list[11] = Object_handles[29];
  cust_handle_list[12] = Object_handles[30];
  cust_handle_list[13] = Object_handles[82];
  cust_handle_list[14] = Object_handles[84];
  cust_handle_list[15] = Object_handles[86];
  cust_handle_list[16] = Object_handles[17];
  cust_handle_list[17] = Object_handles[78];
  cust_handle_list[18] = Object_handles[79];
  cust_handle_list[19] = Object_handles[15];
  cust_handle_list[20] = Object_handles[16];
  cust_handle_list[21] = Object_handles[100];
  cust_handle_list[22] = Object_handles[66];
  cust_handle_list[23] = Object_handles[65];
  cust_handle_list[24] = Object_handles[103];
  cust_handle_list[25] = Object_handles[46];
  cust_handle_list[26] = Object_handles[47];
  cust_handle_list[27] = Object_handles[119];
  cust_handle_list[28] = Object_handles[120];
  cust_handle_list[29] = Object_handles[125];
  cust_handle_list[30] = Object_handles[126];
  cust_handle_list[31] = Object_handles[55];
  cust_handle_list[32] = Object_handles[127];
  cust_handle_list[33] = Object_handles[56];
  cust_handle_list[34] = Object_handles[128];
  cust_handle_list[35] = Object_handles[57];
  cust_handle_list[36] = Object_handles[129];
  cust_handle_list[37] = Object_handles[58];
  cust_handle_list[38] = Object_handles[130];
  cust_handle_list[39] = Object_handles[59];
  cust_handle_list[40] = Object_handles[131];
  cust_handle_list[41] = Object_handles[60];
  cust_handle_list[42] = Object_handles[132];
  cust_handle_list[43] = Object_handles[133];
  cust_handle_list[44] = Object_handles[76];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 45;
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

    // Script 050: Check Laser Room 1's Beams
    if (qUserFlag(14) == false) {
      if ((qBeamHittingPlayer(Object_handles[31], Object_handles[32]) == true) ||
          (qBeamHittingPlayer(Object_handles[27], Object_handles[28]) == true) ||
          (qBeamHittingPlayer(Object_handles[33], Object_handles[34]) == true) ||
          (qBeamHittingPlayer(Object_handles[35], Object_handles[36]) == true) ||
          (qBeamHittingPlayer(Object_handles[29], Object_handles[30]) == true) ||
          (qBeamHittingPlayer(Object_handles[37], Object_handles[38]) == true)) {
        aShowHUDMessage(Message_strings[2]);
        aUserFlagSet(14, 1);
        aPortalRenderSet(1, 0, Room_indexes[1], 0);
        aPortalRenderSet(1, 1, Room_indexes[2], 0);
        aPortalRenderSet(0, 2, Room_indexes[2], 1);
        aRoomSetFaceTexture(Room_indexes[12], 67, Texture_indexes[0]);
        aGoalEnableDisable(1, Goal_indexes[0]);
        aMatcenSetEnableState(1, Matcen_indexes[1]);
        aMatcenSetState(1, Matcen_indexes[1]);
        aObjSetMovementType(Object_handles[6], 1);
        aObjSetLightingDist(Object_handles[6], 70.000000f);
        aSoundPlayObject(Sound_indexes[1], Object_handles[6], 1.000000f);
        aSoundStopObj(Object_handles[0]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }

    // Script 039: Check Laser Room 2's Beams
    if (qUserFlag(13) == false) {
      if ((qBeamHittingPlayer(Object_handles[19], Object_handles[20]) == true) ||
          (qBeamHittingPlayer(Object_handles[21], Object_handles[22]) == true) ||
          (qBeamHittingPlayer(Object_handles[23], Object_handles[24]) == true) ||
          (qBeamHittingPlayer(Object_handles[25], Object_handles[26]) == true)) {
        aShowHUDMessage(Message_strings[2]);
        aUserFlagSet(13, 1);
        aPortalRenderSet(1, 0, Room_indexes[3], 0);
        aPortalRenderSet(1, 1, Room_indexes[4], 0);
        aPortalRenderSet(1, 2, Room_indexes[4], 0);
        aPortalRenderSet(0, 3, Room_indexes[4], 1);
        aPortalRenderSet(0, 4, Room_indexes[4], 1);
        aRoomSetFaceTexture(Room_indexes[13], 67, Texture_indexes[0]);
        aRoomSetFaceTexture(Room_indexes[14], 67, Texture_indexes[0]);
        aGoalEnableDisable(1, Goal_indexes[1]);
        aMatcenSetEnableState(1, Matcen_indexes[2]);
        aMatcenSetState(1, Matcen_indexes[2]);
        aMatcenSetEnableState(1, Matcen_indexes[3]);
        aMatcenSetState(1, Matcen_indexes[3]);
        aObjSetMovementType(Object_handles[7], 1);
        aObjSetLightingDist(Object_handles[7], 70.000000f);
        aSoundPlayObject(Sound_indexes[1], Object_handles[7], 1.000000f);
        aSoundStopObj(Object_handles[1]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Level Start - Init Flags and Variables
    if (1) {
      aUserFlagSet(0, 0);
      aUserFlagSet(0, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aUserFlagSet(6, 0);
      aUserFlagSet(7, 0);
      aUserFlagSet(8, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(11, 0);
      aUserFlagSet(16, 0);
      aUserFlagSet(17, 0);
      aUserFlagSet(18, 0);
      aUserFlagSet(19, 0);
      aUserFlagSet(20, 0);
      aUserFlagSet(21, 0);
      aUserFlagSet(22, 0);
      aUserFlagSet(23, 0);
      aUserFlagSet(12, 0);
      aUserFlagSet(13, 0);
      aUserFlagSet(14, 0);
      aUserFlagSet(15, 0);
      aUserFlagSet(24, 0);
      aUserFlagSet(26, 0);
      aUserVarSet(0, 0.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(4, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aUserVarSet(5, 0.000000f);
      aUserVarSet(7, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 001: Level Start - Misc
    if (1) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[0], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[1], 1.000000f);
      aObjSetMovementType(Object_handles[2], 0);
      aObjSetMovementType(Object_handles[3], 0);
      aObjSetMovementType(Object_handles[4], 0);
      aObjSetMovementType(Object_handles[5], 0);
      aObjSetMovementType(Object_handles[6], 0);
      aObjSetMovementType(Object_handles[7], 0);
      aObjSetMovementType(Object_handles[8], 0);
      aObjSetMovementType(Object_handles[9], 0);
      aObjSetMovementType(Object_handles[10], 0);
      aObjSetMovementType(Object_handles[11], 0);
      aObjSetMovementType(Object_handles[12], 0);
      aObjSetMovementType(Object_handles[13], 0);
      aObjSetLightingDist(Object_handles[6], 0.000000f);
      aObjSetLightingDist(Object_handles[7], 0.000000f);
      aObjSetLightingDist(Object_handles[8], 0.000000f);
      aObjSetLightingDist(Object_handles[9], 0.000000f);
      aObjSetLightingDist(Object_handles[10], 0.000000f);
      aObjSetLightingDist(Object_handles[11], 0.000000f);
      aObjSetLightingDist(Object_handles[12], 0.000000f);
      aObjSetLightingDist(Object_handles[13], 0.000000f);
      aObjPlayAnim(Object_handles[14], 0, 15, 0.500000f, 1);
      aAISetTeam(196608, Object_handles[15]);
      aAISetTeam(196608, Object_handles[16]);
      aObjHide(Object_handles[17]);
      aObjHide(Object_handles[18]);
      aObjHide(Object_handles[19]);
      aObjHide(Object_handles[20]);
      aObjHide(Object_handles[21]);
      aObjHide(Object_handles[22]);
      aObjHide(Object_handles[23]);
      aObjHide(Object_handles[24]);
      aObjHide(Object_handles[25]);
      aObjHide(Object_handles[26]);
      aObjHide(Object_handles[27]);
      aObjHide(Object_handles[28]);
      aObjHide(Object_handles[29]);
      aObjHide(Object_handles[30]);
      aObjHide(Object_handles[31]);
      aObjHide(Object_handles[32]);
      aObjHide(Object_handles[33]);
      aObjHide(Object_handles[34]);
      aObjHide(Object_handles[35]);
      aObjHide(Object_handles[36]);
      aObjHide(Object_handles[37]);
      aObjHide(Object_handles[38]);
      aObjHide(Object_handles[39]);
      aObjHide(Object_handles[40]);
      aObjHide(Object_handles[41]);
      aObjHide(Object_handles[42]);
      aObjHide(Object_handles[43]);
      aObjHide(Object_handles[44]);
      aDoorLockUnlock(1, Door_handles[0]);
      aDoorLockUnlock(1, Door_handles[1]);
      aDoorLockUnlock(1, Door_handles[2]);
      aDoorLockUnlock(1, Door_handles[3]);
      aAISetState(0, Object_handles[45]);
      aAISetState(0, Object_handles[46]);
      aAISetState(0, Object_handles[47]);
      aRoomFogSetState(0, Room_indexes[0]);
      aObjGhostSet(1, Object_handles[48]);
      aObjSetMovementType(Object_handles[49], 0);
      aObjSetMovementType(Object_handles[50], 0);
      aObjSetMovementType(Object_handles[51], 0);
      aObjSetMovementType(Object_handles[52], 0);
      aAISetTeam(196608, Object_handles[50]);
      aAISetTeam(196608, Object_handles[51]);
      aAISetTeam(196608, Object_handles[52]);
      aAISetTeam(196608, Object_handles[49]);
      aAISetTeam(196608, Object_handles[53]);
      aAISetTeam(196608, Object_handles[54]);
      aAISetState(0, Object_handles[55]);
      aAISetState(0, Object_handles[56]);
      aAISetState(0, Object_handles[57]);
      aAISetState(0, Object_handles[58]);
      aAISetState(0, Object_handles[59]);
      aAISetState(0, Object_handles[60]);
      aTurnOnSpew(Object_handles[61], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                  2.000000f, 15.000000f, 1, -1);
      aObjMakeInvuln(Object_handles[62], 1000000);
      aObjMakeInvuln(Object_handles[63], 1000000);
      aObjMakeInvuln(Object_handles[64], 1000000);
      aObjMakeInvuln(Object_handles[65], 1000000);
      aObjMakeInvuln(Object_handles[66], 1000000);
      aObjMakeInvuln(Object_handles[67], 1000000);
      aObjMakeInvuln(Object_handles[68], 1000000);
      aObjMakeInvuln(Object_handles[69], 1000000);
      aObjMakeInvuln(Object_handles[70], 1000000);
      aObjMakeInvuln(Object_handles[71], 1000000);
      aObjMakeInvuln(Object_handles[54], 1000000);
      aObjMakeInvuln(Object_handles[72], 1000000);
      aObjSetMovementType(Object_handles[3], 0);
      aObjSetMovementType(Object_handles[73], 0);
      aObjSetMovementType(Object_handles[74], 0);
      aPortalRenderSet(0, 0, Room_indexes[0], 1);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aPortalRenderSet(0, 1, Room_indexes[2], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aPortalRenderSet(0, 1, Room_indexes[4], 1);
      aPortalRenderSet(0, 2, Room_indexes[4], 1);
      aRoomSetWind(Room_indexes[5], 0.000000f, 1.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 1.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, -1.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[9], 0.000000f, -1.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, -1.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, -1.000000f, 0.000000f, 20.000000f);
      aSetLevelTimer(0.500000f, 23);
      aSetLevelTimer(0.500000f, 0);
      aSetLevelTimer(0.500000f, 20);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 016: Level Start - Matcens
    if (1) {
      aMatcenSetEnableState(0, Matcen_indexes[0]);
      aMatcenSetEnableState(0, Matcen_indexes[1]);
      aMatcenSetEnableState(0, Matcen_indexes[2]);
      aMatcenSetEnableState(0, Matcen_indexes[3]);
      aMatcenSetState(1, Matcen_indexes[4]);
      aMatcenSetState(1, Matcen_indexes[5]);
      aMatcenSetState(0, Matcen_indexes[6]);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 002: Level Start - Intro Cinematic
    if (1 == true) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[17], Path_indexes[1], 15.000000f);
      aMusicSetRegionAll(0);
      aSetLevelTimer(18.000000f, 26);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 128: Play Tower Chatter Voice Over
    if ((ScriptActionCtr_128 < 1) && (event_data->id == 26)) {
      aSoundPlaySteaming("VoxMerc02MPA3.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }

    // Script 003: Level Start + 0.5 sec - Do Init
    if (event_data->id == 0) {
      aMusicSetRegionAll(5);
      aAIGoalFollowPathSimple(Object_handles[75], Path_indexes[2], 4198656, -1, 0);
      aAISetMaxSpeed(Object_handles[76], 25.000000f);
      aAIGoalFollowPathSimple(Object_handles[76], Path_indexes[3], 4352, 37, 3);
      aSetTurnRate(Object_handles[77], 11000.000000f);
      aAISetMaxSpeed(Object_handles[77], 25.000000f);
      aAIGoalFollowPathSimple(Object_handles[77], Path_indexes[4], 8392960, -1, 3);
      aAISetTeam(196608, Object_handles[78]);
      aAISetTeam(196608, Object_handles[79]);
      aObjSaveHandle(qGetAtachedChild(Object_handles[78], 1), 0);
      aObjSaveHandle(qGetAtachedChild(Object_handles[78], 0), 3);
      aObjSaveHandle(qGetAtachedChild(Object_handles[79], 1), 1);
      aObjSaveHandle(qGetAtachedChild(Object_handles[79], 0), 4);
      aAISetTeam(196608, qObjSavedHandle(0));
      aAISetTeam(196608, qObjSavedHandle(1));
      aAIGoalFollowPathSimple(Object_handles[78], Path_indexes[5], 8392960, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[79], Path_indexes[6], 8392960, -1, 3);
      aSetLevelTimer(0.500000f, 4);
      aAISetMaxSpeed(Object_handles[19], 20.000000f);
      aAISetMaxSpeed(Object_handles[20], 20.000000f);
      aAISetMaxSpeed(Object_handles[21], 35.000000f);
      aAISetMaxSpeed(Object_handles[22], 35.000000f);
      aAISetMaxSpeed(Object_handles[23], 30.000000f);
      aAISetMaxSpeed(Object_handles[24], 30.000000f);
      aAISetMaxSpeed(Object_handles[25], 25.000000f);
      aAISetMaxSpeed(Object_handles[26], 25.000000f);
      aAISetMaxSpeed(Object_handles[27], 30.000000f);
      aAISetMaxSpeed(Object_handles[28], 30.000000f);
      aAISetMaxSpeed(Object_handles[29], 30.000000f);
      aAISetMaxSpeed(Object_handles[30], 30.000000f);
      aAIGoalFollowPathSimple(Object_handles[19], Path_indexes[7], 2228480, 2, 3);
      aAIGoalFollowPathSimple(Object_handles[20], Path_indexes[8], 2228480, 4, 3);
      aAIGoalFollowPathSimple(Object_handles[21], Path_indexes[9], 2228480, 6, 3);
      aAIGoalFollowPathSimple(Object_handles[22], Path_indexes[10], 2228480, 8, 3);
      aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[11], 2228480, 10, 3);
      aAIGoalFollowPathSimple(Object_handles[24], Path_indexes[12], 2228480, 12, 3);
      aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[13], 2228480, 14, 3);
      aAIGoalFollowPathSimple(Object_handles[26], Path_indexes[14], 2228480, 16, 3);
      aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[15], 2228480, 18, 3);
      aAIGoalFollowPathSimple(Object_handles[28], Path_indexes[16], 2228480, 20, 3);
      aAIGoalFollowPathSimple(Object_handles[29], Path_indexes[17], 2228480, 22, 3);
      aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[18], 2228480, 24, 3);
      aUserFlagSet(8, 1);
      aUserFlagSet(9, 1);
      aUserFlagSet(10, 1);
      aUserFlagSet(11, 1);
      aUserFlagSet(16, 1);
      aUserFlagSet(17, 1);
      aUserFlagSet(18, 1);
      aUserFlagSet(19, 1);
      aUserFlagSet(20, 1);
      aUserFlagSet(21, 1);
      aUserFlagSet(22, 1);
      aUserFlagSet(23, 1);
      aSetLevelTimer(0.750000f, 11);
      aSetLevelTimer(1.000000f, 12);
      aAIFlags(0, 128, Object_handles[49]);
      aAIFlags(0, 128, Object_handles[50]);
      aAIFlags(0, 128, Object_handles[51]);
      aAIFlags(0, 128, Object_handles[52]);
      aAIGoalFollowPathSimple(Object_handles[80], Path_indexes[19], 8392960, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 061: Update Laser Room 1's Beams
    if (event_data->id == 11) {
      if (qUserFlag(14) == false) {
        aUserVarSet(6, qConvertTextureIDToFloat(Texture_indexes[1]));
        aLightningCreate(Object_handles[31], Object_handles[32], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[27], Object_handles[28], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[33], Object_handles[34], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[35], Object_handles[36], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[29], Object_handles[30], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[37], Object_handles[38], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
      }
      aSetLevelTimer(0.500000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }

    // Script 031: Update Laser Room 2's Beams
    if (event_data->id == 12) {
      if ((qUserFlag(12) == true) && (qUserFlag(13) == false)) {
        if (qUserVarValue(5) < 6.000000f) {
          if (qUserVarValue(5) < 2.000000f) {
            aUserVarSet(6, qConvertTextureIDToFloat(Texture_indexes[2]));
          }
          if ((qUserVarValue(5) >= 2.000000f) && (qUserVarValue(5) < 4.000000f)) {
            aUserVarSet(6, qConvertTextureIDToFloat(Texture_indexes[3]));
          }
          if ((qUserVarValue(5) >= 4.000000f) && (qUserVarValue(5) < 6.000000f)) {
            aUserVarSet(6, qConvertTextureIDToFloat(Texture_indexes[4]));
          }
          aUserVarInc(5);
        } else {
          aUserVarSet(6, qConvertTextureIDToFloat(Texture_indexes[1]));
        }
        aLightningCreate(Object_handles[19], Object_handles[20], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[21], Object_handles[22], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[23], Object_handles[24], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[25], Object_handles[26], 0.500000f, 4.000000f, 1,
                         qConvertFloatToTextureID(qUserVarValue(6)), 0.000000f, 1, 255, 255, 255, 0);
      }
      aSetLevelTimer(0.500000f, 12);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 037: Laser Room 2 Is Fogged Enough to See Lasers
    if (event_data->id == 13) {
      aUserFlagSet(12, 1);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }

    // Script 005: Perform Player Scan
    if ((event_data->id == 1) && (qUserFlag(2) == false)) {
      if (qUserVarValue(0) == 8.000000f) {
        aSoundPlaySteaming("VoxMerc02FCV3.osf", 1.000000f);
        aRoomSetFaceTexture(Room_indexes[15], 45, Texture_indexes[6]);
        aRoomSetFaceTexture(Room_indexes[15], 30, Texture_indexes[6]);
        aUserFlagSet(1, 1);
        aUserFlagSet(0, 0);
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
        aShowHUDMessage(Message_strings[4]);
        aGoalCompleted(Goal_indexes[2], 1);
      } else {
        if (qObjGetDistance(Object_handles[17], qObjSavedHandle(2)) < 20.000000f) {
          aLightningCreate(Object_handles[88], Object_handles[89], 1.000000f, 1.000000f, 3, Texture_indexes[7],
                           0.500000f, 1, 255, 255, 255, 0);
          aLightningCreate(Object_handles[90], Object_handles[91], 1.000000f, 1.000000f, 3, Texture_indexes[7],
                           0.500000f, 1, 255, 255, 255, 0);
          aLightningCreate(Object_handles[92], Object_handles[93], 1.000000f, 1.000000f, 3, Texture_indexes[7],
                           0.500000f, 1, 255, 255, 255, 0);
          aLightningCreate(Object_handles[94], Object_handles[95], 1.000000f, 1.000000f, 3, Texture_indexes[7],
                           0.500000f, 1, 255, 255, 255, 0);
          aLightningCreate(Object_handles[96], Object_handles[97], 1.000000f, 1.000000f, 3, Texture_indexes[7],
                           0.500000f, 1, 255, 255, 255, 0);
          aLightningCreate(Object_handles[98], Object_handles[99], 1.000000f, 1.000000f, 3, Texture_indexes[7],
                           0.500000f, 1, 255, 255, 255, 0);
          aUserVarInc(0);
          aSetLevelTimer(1.000000f, 1);
        } else {
          aSoundPlaySteaming("VoxMerc02FCV2.osf", 1.000000f);
          aRoomSetFaceTexture(Room_indexes[15], 45, Texture_indexes[8]);
          aRoomSetFaceTexture(Room_indexes[15], 30, Texture_indexes[8]);
          aShowHUDMessage(Message_strings[5]);
          aSetLevelTimer(4.000000f, 2);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 006: Reset Scan Process
    if (event_data->id == 2) {
      aRoomSetFaceTexture(Room_indexes[15], 45, Texture_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[15], 30, Texture_indexes[9]);
      aUserFlagSet(0, 0);
      aUserVarSet(0, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 007: Alert Gate Security
    if ((ScriptActionCtr_007 < 1) && (event_data->id == 3)) {
      aRoomSetFaceTexture(Room_indexes[16], 100, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[16], 80, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[15], 45, Texture_indexes[10]);
      aRoomSetFaceTexture(Room_indexes[15], 30, Texture_indexes[10]);
      aAISetTeam(0, Object_handles[15]);
      aAISetTeam(0, Object_handles[16]);
      aAISetTeam(0, Object_handles[78]);
      aAISetTeam(0, Object_handles[79]);
      aAISetTeam(0, qObjSavedHandle(0));
      aAISetTeam(0, qObjSavedHandle(1));
      aDoorSetPos(Door_handles[0], 0.000000f);
      if (qGoalCompleted(Goal_indexes[3]) == false) {
        aDoorLockUnlock(1, Door_handles[0]);
        aShowHUDMessage(Message_strings[6]);
        aGoalEnableDisable(0, Goal_indexes[2]);
        aGoalEnableDisable(1, Goal_indexes[4]);
      }
      aUserFlagSet(2, 1);
      aSoundPlayObject(Sound_indexes[1], Object_handles[17], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 014: Check Tracker Children for Damage
    if ((event_data->id == 4) && (qUserFlag(2) == false)) {
      if (((qObjExists(qObjSavedHandle(0)) == 0) ||
           (qObjShields(qObjSavedHandle(0)) < qObjShieldsOriginal(qObjSavedHandle(0)))) ||
          ((qObjExists(qObjSavedHandle(1)) == 0) ||
           (qObjShields(qObjSavedHandle(1)) < qObjShieldsOriginal(qObjSavedHandle(1)))) ||
          ((qObjExists(qObjSavedHandle(3)) == 0) ||
           (qObjShields(qObjSavedHandle(3)) < qObjShieldsOriginal(qObjSavedHandle(3)))) ||
          ((qObjExists(qObjSavedHandle(4)) == 0) ||
           (qObjShields(qObjSavedHandle(4)) < qObjShieldsOriginal(qObjSavedHandle(4))))) {
        aSetLevelTimer(0.100000f, 3);
      } else {
        aSetLevelTimer(0.500000f, 4);
      }

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 018: Do Weapon Check Sequence
    if ((event_data->id == 5) && (qUserFlag(5) == false)) {
      if (qUserFlag(6) == true) {
        if (qUserFlag(4) == false) {
          aObjSaveHandle(qPlayerClosest(Object_handles[18], 3), 5);
          if (qUserVarValue(3) > 20.000000f) {
            aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[8]);
            aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[8]);
            aSoundPlaySteaming("VoxMerc02FCV2.osf", 1.000000f);
            aShowHUDMessage(Message_strings[8]);
            aUserFlagSet(6, 0);
            aAISetMaxSpeed(qObjSavedHandle(6), 13.000000f);
            aPortalRenderSet(0, 0, Room_indexes[0], 1);
            aSetLevelTimer(0.100000f, 8);
          } else {
            aSetLevelTimer(0.500000f, 5);
          }
        }
      } else {
        aObjSaveHandle(qPlayerClosest(Object_handles[18], 3), 5);
        if (qUserVarValue(3) < 15.000000f) {
          aSoundPlaySteaming("VoxMerc02FCV1.osf", 1.000000f);
          aShowHUDMessage(Message_strings[9]);
          aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[5]);
          aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[5]);
          aMatcenSetEnableState(1, Matcen_indexes[0]);
          aMatcenSetState(1, Matcen_indexes[0]);
          aPortalRenderSet(1, 0, Room_indexes[0], 1);
          aUserFlagSet(6, 1);
          aSetLevelTimer(2.000000f, 5);
        } else {
          aSetLevelTimer(0.500000f, 5);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 021: Send Weapon Guard Home
    if (event_data->id == 8) {
      aObjPlayAnim(qObjSavedHandle(6), 9, 14, 2.000000f, 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(6), Path_indexes[33], 1048832, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 023: Check if Weapon Guard has been Shot
    if ((event_data->id == 9) && (qUserFlag(7) == true) && (qUserFlag(5) == false)) {
      if ((qObjExists(qObjSavedHandle(6)) == false) ||
          (qObjShields(qObjSavedHandle(6)) < qObjShieldsOriginal(qObjSavedHandle(6)))) {
        aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[10]);
        aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[10]);
        aUserFlagSet(5, 1);
        aObjGhostSet(1, Object_handles[48]);
        aObjDestroy(qObjSavedHandle(6));
        aRoomSetFog(Room_indexes[0], 0.000000f, 1.000000f, 0.000000f, 1000.000000f);
        aRoomFogSetState(1, Room_indexes[0]);
        aRoomChangeFog(Room_indexes[0], 0.000000f, 1.000000f, 0.000000f, 200.000000f, 6.000000f);
        aShowHUDMessage(Message_strings[12]);
        aSoundPlayObject(Sound_indexes[1], Object_handles[18], 1.000000f);
        aUserVarSet(2, 0.000000f);
        aSetLevelTimer(6.000000f, 7);
      } else {
        aSetLevelTimer(0.250000f, 9);
      }

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 024: Do Weapon Check Threat Sequence
    if (event_data->id == 7) {
      aUserVarInc(2);
      if (qUserVarValue(2) == 1.000000f) {
        aRoomSetDamage(Room_indexes[0], 20.000000f, 1);
        aSetLevelTimer(10.000000f, 7);
      }
      if (qUserVarValue(2) == 2.000000f) {
        aRemovePowerupsInRoom(Room_indexes[0]);
        aRoomChangeFog(Room_indexes[0], 0.000000f, 1.000000f, 0.000000f, 1000.000000f, 2.500000f);
        aSetLevelTimer(3.000000f, 7);
      }
      if (qUserVarValue(2) == 3.000000f) {
        aRemovePowerupsInRoom(Room_indexes[0]);
        aRoomSetDamage(Room_indexes[0], 0.000000f, 1);
        aRoomFogSetState(0, Room_indexes[0]);
        aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[9]);
        aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[9]);
        aUserFlagSet(6, 0);
        aUserFlagSet(5, 0);
        aUserFlagSet(4, 0);
        aPortalRenderSet(0, 0, Room_indexes[0], 1);
        aSetLevelTimer(2.000000f, 5);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 063: Do Worker Screwup
    if (event_data->id == 14) {
      if (ScriptActionCtr_063 == 0) {
        aEmitSparks(30.000000f, Object_handles[101]);
        aSetLevelTimer(1.500000f, 14);
      }
      if (ScriptActionCtr_063 == 1) {
        aEmitSparks(50.000000f, Object_handles[101]);
        aObjSetMovementType(Object_handles[73], 1);
        aAIGoalFollowPathSimple(Object_handles[73], Path_indexes[34], 4352, -1, 3);
        aSoundPlayObject(Sound_indexes[2], Object_handles[73], 1.000000f);
        aObjSpark(Object_handles[64], 40.000000f, 3.000000f);
        aTurnOnSpew(Object_handles[102], -1, 0, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, 3.500000f,
                    2.000000f, 17.000000f, 0, -1);
        aSetLevelTimer(1.500000f, 14);
      }
      if (ScriptActionCtr_063 == 3) {
        aObjMakeVulnerable(Object_handles[64]);
        aObjMakeVulnerable(Object_handles[63]);
        aObjDestroy(Object_handles[64]);
        aObjDestroy(Object_handles[63]);
        aObjSetMovementType(Object_handles[73], 1);
        aObjDestroy(Object_handles[3]);
        aShowHUDMessage(Message_strings[15]);
      }
      if (ScriptActionCtr_063 == 2) {
        aObjSetMovementType(Object_handles[74], 1);
        aAIGoalFollowPathSimple(Object_handles[74], Path_indexes[35], 4352, -1, 3);
        aSoundPlayObject(Sound_indexes[2], Object_handles[74], 1.000000f);
        aEmitSparks(50.000000f, Object_handles[101]);
        aSetLevelTimer(2.000000f, 14);
      }

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }

    // Script 065: Do General Landing Sequence
    if (event_data->id == 15) {
      if (ScriptActionCtr_065 == 0) {
        aCinematicSimple(Path_indexes[36], Message_strings[16], Object_handles[65], 17.000000f, 1);
        aAISetMaxSpeed(Object_handles[65], 15.000000f);
        aAIGoalFollowPathSimple(Object_handles[65], Path_indexes[37], 1048832, 27, 3);
        aSetLevelTimer(2.000000f, 15);
      }
      if (ScriptActionCtr_065 == 1) {
        aDoorSetPos(Door_handles[3], 1.000000f);
        aSetLevelTimer(3.000000f, 15);
      }

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }

    // Script 068: Destroy General Sequence
    if (event_data->id == 16) {
      if (ScriptActionCtr_068 == 0) {
        aSoundPlaySteaming("VoxMerc02FPA2.osf", 1.000000f);
        aAISetTeam(131072, Object_handles[53]);
        aAISetTeam(131072, Object_handles[54]);
        aAIFlags(0, 1024, Object_handles[54]);
        aAIFlags(1, 536870912, Object_handles[53]);
        aAIFlags(1, 536870912, Object_handles[54]);
        aAISetTarget(Object_handles[54], Object_handles[71]);
        aAISetTarget(Object_handles[53], Object_handles[49]);
        aSetLevelTimer(3.000000f, 16);
        aDoorSetPos(Door_handles[1], 0.500000f);
      }
      if (ScriptActionCtr_068 == 1) {
        aObjSpark(Object_handles[71], 50.000000f, 2.000000f);
        aObjSetMovementType(Object_handles[49], 1);
        aObjSetMovementType(Object_handles[50], 1);
        aObjSetMovementType(Object_handles[51], 1);
        aObjSetMovementType(Object_handles[52], 1);
        aAISetTeam(0, Object_handles[50]);
        aAISetTeam(0, Object_handles[51]);
        aAISetTeam(0, Object_handles[52]);
        aAISetTeam(0, Object_handles[49]);
        aAISetTeam(131072, Object_handles[53]);
        aAISetTeam(131072, Object_handles[54]);
        aAISetTarget(Object_handles[54], Object_handles[65]);
        aAISetTarget(Object_handles[53], Object_handles[49]);
        aAISetTarget(Object_handles[49], Object_handles[54]);
        aAISetTarget(Object_handles[52], Object_handles[54]);
        aAISetTarget(Object_handles[50], Object_handles[53]);
        aAISetTarget(Object_handles[51], Object_handles[53]);
        aAIFlags(1, 128, Object_handles[49]);
        aAIFlags(1, 128, Object_handles[50]);
        aAIFlags(1, 128, Object_handles[51]);
        aAIFlags(1, 128, Object_handles[52]);
        aSetLevelTimer(2.000000f, 16);
      }
      if (ScriptActionCtr_068 == 2) {
        aObjMakeVulnerable(Object_handles[71]);
        aObjDestroy(Object_handles[71]);
        aAIFlags(1, 1024, Object_handles[54]);
        aObjMakeVulnerable(Object_handles[54]);
        aObjSpark(Object_handles[65], 50.000000f, 0.200000f);
        aSetLevelTimer(0.200000f, 16);
      }
      if (ScriptActionCtr_068 == 3) {
        aObjMakeVulnerable(Object_handles[65]);
        aObjMakeVulnerable(Object_handles[67]);
        aObjDestroy(Object_handles[67]);
        aObjDestroy(Object_handles[65]);
        aDoorLockUnlock(0, Door_handles[1]);
        aDoorSetPos(Door_handles[1], 1.000000f);
        aSetLevelTimer(0.400000f, 16);
      }
      if (ScriptActionCtr_068 == 4) {
        aObjMakeVulnerable(Object_handles[72]);
        aObjDestroy(Object_handles[72]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }

    // Script 089: Do Self-Destruct Sequence
    if (event_data->id == 19) {
      if (ScriptActionCtr_089 == 0) {
        aEmitSparks(20.000000f, Object_handles[81]);
        aObjPlayAnim(Object_handles[14], 0, 15, 2.000000f, 0);
        aRoomChangeWind(Room_indexes[8], 0.000000f, -1.000000f, 0.000000f, 0.000000f, 3.000000f);
        aDoorLockUnlock(1, Door_handles[4]);
        aRoomSetFog(Room_indexes[17], 0.250000f, 0.500000f, 0.800000f, 5000.000000f);
        aRoomSetFog(Room_indexes[18], 0.250000f, 0.500000f, 0.800000f, 5000.000000f);
        aRoomSetFog(Room_indexes[19], 0.250000f, 0.500000f, 0.800000f, 5000.000000f);
        aRoomSetFog(Room_indexes[20], 0.250000f, 0.500000f, 0.800000f, 5000.000000f);
        aRoomSetFog(Room_indexes[21], 0.250000f, 0.500000f, 0.800000f, 5000.000000f);
        aRoomSetFog(Room_indexes[8], 0.250000f, 0.500000f, 0.800000f, 5000.000000f);
        aRoomFogSetState(1, Room_indexes[17]);
        aRoomFogSetState(1, Room_indexes[18]);
        aRoomFogSetState(1, Room_indexes[19]);
        aRoomFogSetState(1, Room_indexes[20]);
        aRoomFogSetState(1, Room_indexes[21]);
        aRoomFogSetState(1, Room_indexes[8]);
        aRoomChangeFog(Room_indexes[17], 0.250000f, 0.500000f, 0.800000f, 350.000000f, 3.000000f);
        aRoomChangeFog(Room_indexes[18], 0.250000f, 0.500000f, 0.800000f, 350.000000f, 3.000000f);
        aRoomChangeFog(Room_indexes[19], 0.250000f, 0.500000f, 0.800000f, 350.000000f, 3.000000f);
        aRoomChangeFog(Room_indexes[20], 0.250000f, 0.500000f, 0.800000f, 350.000000f, 3.000000f);
        aRoomChangeFog(Room_indexes[21], 0.250000f, 0.500000f, 0.800000f, 350.000000f, 3.000000f);
        aRoomChangeFog(Room_indexes[8], 0.250000f, 0.500000f, 0.800000f, 350.000000f, 3.000000f);
        aTurnOnSpew(Object_handles[105], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                    6.000000f, 35.000000f, 1, -1);
        aTurnOnSpew(Object_handles[106], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                    6.000000f, 35.000000f, 1, -1);
        aTurnOnSpew(Object_handles[107], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                    6.000000f, 35.000000f, 1, -1);
        aTurnOnSpew(Object_handles[108], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, -1.000000f,
                    6.000000f, 35.000000f, 1, -1);
        aSoundPlaySteaming("VoxMerc02FPA3.osf", 1.000000f);
        aAISetMaxSpeed(Object_handles[39], 77.000000f);
        aAISetMaxSpeed(Object_handles[40], 77.000000f);
        aLightningCreate(Object_handles[39], Object_handles[40], 1000000.000000f, 12.000000f, 3, Texture_indexes[11],
                         0.300000f, 1, 255, 255, 255, 0);
        aPhysFlags(1, 65536, Object_handles[39]);
        aPhysFlags(1, 65536, Object_handles[40]);
        aAIGoalFollowPathSimple(Object_handles[39], Path_indexes[39], 2228480, 31, 3);
        aAIGoalFollowPathSimple(Object_handles[40], Path_indexes[40], 2228480, 31, 3);
        aAIGoalSetCircleDistance(Object_handles[39], 3, 10.000000f);
        aAIGoalSetCircleDistance(Object_handles[40], 3, 10.000000f);
        aSoundPlayObject(Sound_indexes[4], Object_handles[40], 1.000000f);
        aSetLevelTimer(1.000000f, 19);
      }
      if (ScriptActionCtr_089 == 1) {
        aAISetMaxSpeed(Object_handles[41], 71.000000f);
        aAISetMaxSpeed(Object_handles[42], 71.000000f);
        aLightningCreate(Object_handles[41], Object_handles[42], 1000000.000000f, 12.000000f, 3, Texture_indexes[11],
                         0.300000f, 1, 255, 255, 255, 0);
        aPhysFlags(1, 65536, Object_handles[41]);
        aPhysFlags(1, 65536, Object_handles[42]);
        aAIGoalFollowPathSimple(Object_handles[41], Path_indexes[41], 2228480, 32, 3);
        aAIGoalFollowPathSimple(Object_handles[42], Path_indexes[42], 2228480, 32, 3);
        aAIGoalSetCircleDistance(Object_handles[41], 3, 10.000000f);
        aAIGoalSetCircleDistance(Object_handles[42], 3, 10.000000f);
        aSoundPlayObject(Sound_indexes[4], Object_handles[42], 1.000000f);
        aSetLevelTimer(1.000000f, 19);
      }
      if (ScriptActionCtr_089 == 2) {
        aAISetMaxSpeed(Object_handles[43], 65.000000f);
        aAISetMaxSpeed(Object_handles[44], 65.000000f);
        aLightningCreate(Object_handles[43], Object_handles[44], 1000000.000000f, 12.000000f, 3, Texture_indexes[11],
                         0.300000f, 1, 255, 255, 255, 0);
        aPhysFlags(1, 65536, Object_handles[43]);
        aPhysFlags(1, 65536, Object_handles[44]);
        aAIGoalFollowPathSimple(Object_handles[43], Path_indexes[43], 2228480, 33, 3);
        aAIGoalFollowPathSimple(Object_handles[44], Path_indexes[44], 2228480, 33, 3);
        aAIGoalSetCircleDistance(Object_handles[43], 3, 10.000000f);
        aAIGoalSetCircleDistance(Object_handles[44], 3, 10.000000f);
        aSoundPlayObject(Sound_indexes[4], Object_handles[44], 1.000000f);
        aRoomSetDamage(Room_indexes[17], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[18], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[19], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[20], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[21], 1.000000f, 1);
        aRoomSetDamage(Room_indexes[8], 1.000000f, 1);
        aEmitSparks(30.000000f, Object_handles[81]);
        aGoalCompleted(Goal_indexes[14], 1);
        aGoalEnableDisable(1, Goal_indexes[15]);
        aShowHUDMessage(Message_strings[23]);
        aMusicSetRegionAll(3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }

    // Script 073: End Trooper Break Out
    if (event_data->id == 17) {
      aAISetState(1, Object_handles[46]);
      aAIGoalFollowPathSimple(Object_handles[46], Path_indexes[49], 4352, -1, 3);
      aObjMakeVulnerable(Object_handles[69]);
      aObjDestroy(Object_handles[69]);
      aGoalEnableDisable(1, Goal_indexes[16]);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }

    // Script 077: Activate the Armory Guard Matcen
    if (event_data->id == 18) {
      aMatcenSetState(1, Matcen_indexes[6]);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }

    // Script 095: Make Armory Guard Leave
    if (event_data->id == 21) {
      if (qObjExists(qObjSavedHandle(8)) == true) {
        aAIGoalFollowPathSimple(qObjSavedHandle(8), Path_indexes[54], 16781568, 34, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }

    // Script 099: Close Armory Door
    if (event_data->id == 22) {
      aDoorSetPos(Door_handles[6], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }

    // Script 093: Update Data Cartridge Effects
    if (event_data->id == 20) {
      if ((qUserFlag(24) == false) || (qUserFlag(25) == true)) {
        if (qUserFlag(25) == true) {
          aObjSaveHandle(Object_handles[81], 7);
        } else {
          aObjSaveHandle(Object_handles[103], 7);
        }
        aLightningCreate(Object_handles[122], qObjSavedHandle(7), 0.500000f, 3.000000f, 3, Texture_indexes[11],
                         0.500000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[123], qObjSavedHandle(7), 0.500000f, 3.000000f, 3, Texture_indexes[11],
                         0.500000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[124], qObjSavedHandle(7), 0.500000f, 3.000000f, 3, Texture_indexes[11],
                         0.500000f, 1, 255, 255, 255, 0);
      }
      aSetLevelTimer(0.500000f, 20);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }

    // Script 121: Do Welder Sparks
    if (event_data->id == 23) {
      if (qRandomValue(1.000000f, 100.000000f) < 50.000000f) {
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[4], 0);
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[2], 0);
      }
      if (qRandomValue(1.000000f, 100.000000f) < 50.000000f) {
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[5], 0);
      }
      if ((qUserFlag(26) == true) && (qRandomValue(1.000000f, 100.000000f) < 50.000000f)) {
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[76], 0);
      }
      aSetLevelTimer(qRandomValue(0.400000f, 1.200000f), 23);

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }

    // Script 124: Send Welder To Ship A
    if (event_data->id == 24) {
      aUserFlagSet(26, 0);
      aObjSetMovementType(Object_handles[76], 1);
      aAISetMaxSpeed(Object_handles[76], 25.000000f);
      aAIGoalFollowPathSimple(Object_handles[76], Path_indexes[3], 4352, 37, 3);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }

    // Script 125: Send Welder To Ship B
    if (event_data->id == 25) {
      aUserFlagSet(26, 0);
      aObjSetMovementType(Object_handles[76], 1);
      aAISetMaxSpeed(Object_handles[76], 25.000000f);
      aAIGoalFollowPathSimple(Object_handles[76], Path_indexes[65], 4352, 38, 3);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 020: Weapon Guard Entered
    if (event_data->goal_uid == 0) {
      aShowHUDMessage(Message_strings[10]);
      aAttachExistingObject(Object_handles[48], 0, event_data->it_handle, 0);
      aObjGhostSet(0, Object_handles[48]);
      aStripWeaponsEnergyFromAll();
      aRemovePowerupsInRoom(Room_indexes[0]);
      aUserFlagSet(4, 1);
      aObjPlayAnim(event_data->it_handle, 14, 26, 0.800000f, 0);
      aSetLevelTimer(1.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 022: Weapon Guard Left
    if (event_data->goal_uid == 1) {
      aUserFlagSet(7, 0);
      aObjDelete(event_data->it_handle);
      aObjGhostSet(1, Object_handles[48]);
      if (qUserFlag(5) == false) {
        if (qUserFlag(4) == true) {
          aSoundPlaySteaming("VoxMerc02FCV4.osf", 1.000000f);
          aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[6]);
          aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[6]);
          aPortalRenderSet(0, 3, Room_indexes[0], 1);
          aPortalRenderSet(0, 0, Room_indexes[0], 1);
          aPortalRenderSet(1, 0, Room_indexes[0], 0);
          aShowHUDMessage(Message_strings[11]);
          aGoalCompleted(Goal_indexes[5], 1);
        } else {
          aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[9]);
          aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[9]);
          aSetLevelTimer(0.100000f, 5);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 090: Restart End Beam A
    if (event_data->goal_uid == 31) {
      aStoreObjectInPositionClipboard(Object_handles[109]);
      aMoveObjectToPositionClipboard(Object_handles[39]);
      aStoreObjectInPositionClipboard(Object_handles[110]);
      aMoveObjectToPositionClipboard(Object_handles[40]);
      aAIGoalFollowPathSimple(Object_handles[39], Path_indexes[39], 2228480, 31, 3);
      aAIGoalFollowPathSimple(Object_handles[40], Path_indexes[40], 2228480, 31, 3);
      aAIGoalSetCircleDistance(Object_handles[39], 3, 10.000000f);
      aAIGoalSetCircleDistance(Object_handles[40], 3, 10.000000f);
      aEmitSparks(10.000000f, Object_handles[81]);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }

    // Script 091: Restart End Beam B
    if (event_data->goal_uid == 32) {
      aStoreObjectInPositionClipboard(Object_handles[111]);
      aMoveObjectToPositionClipboard(Object_handles[41]);
      aStoreObjectInPositionClipboard(Object_handles[112]);
      aMoveObjectToPositionClipboard(Object_handles[42]);
      aAIGoalFollowPathSimple(Object_handles[41], Path_indexes[41], 2228480, 32, 3);
      aAIGoalFollowPathSimple(Object_handles[42], Path_indexes[42], 2228480, 32, 3);
      aAIGoalSetCircleDistance(Object_handles[41], 3, 10.000000f);
      aAIGoalSetCircleDistance(Object_handles[42], 3, 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }

    // Script 092: Restart End Beam C
    if (event_data->goal_uid == 33) {
      aStoreObjectInPositionClipboard(Object_handles[113]);
      aMoveObjectToPositionClipboard(Object_handles[43]);
      aStoreObjectInPositionClipboard(Object_handles[114]);
      aMoveObjectToPositionClipboard(Object_handles[44]);
      aAIGoalFollowPathSimple(Object_handles[43], Path_indexes[43], 2228480, 33, 3);
      aAIGoalFollowPathSimple(Object_handles[44], Path_indexes[44], 2228480, 33, 3);
      aAIGoalSetCircleDistance(Object_handles[43], 3, 10.000000f);
      aAIGoalSetCircleDistance(Object_handles[44], 3, 10.000000f);
      aEmitSparks(10.000000f, Object_handles[81]);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }

    // Script 078: Armory Guard Got To Door
    if (event_data->goal_uid == 28) {
      aDoorSetPos(Door_handles[6], 1.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[53], 4352, 29, 3);
      aSetLevelTimer(8.000000f, 22);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }

    // Script 079: Armory Guard Went Through Door
    if (event_data->goal_uid == 29) {
      aDoorSetPos(Door_handles[6], 0.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[54], 1048836, -1, 3);
      aObjSaveHandle(event_data->it_handle, 8);
      aSetLevelTimer(qRandomValue(15.000000f, 30.000000f), 21);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }

    // Script 096: Armory Guard Got To Door Again
    if (event_data->goal_uid == 34) {
      aDoorSetPos(Door_handles[6], 1.000000f);
      aSetLevelTimer(8.000000f, 22);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[53], 16781568, 35, 3);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }

    // Script 097: Armory Guard Went Through Door Again
    if (event_data->goal_uid == 35) {
      aDoorSetPos(Door_handles[6], 0.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[52], 16781568, 36, 3);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }

    // Script 098: Delete Armory Guard
    if (event_data->goal_uid == 36) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }

    // Script 083: Delete Stormtrooper and Heavy Trooper w/Claw
    if (event_data->goal_uid == 30) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 019: Matcen Produced Weapon Check Guard
    if (event_data->id == Matcen_indexes[0]) {
      aMatcenSetState(0, Matcen_indexes[0]);
      aMatcenSetEnableState(0, Matcen_indexes[0]);
      aAISetTeam(196608, event_data->it_handle);
      aAISetMode(event_data->it_handle, 6);
      aAISetMaxSpeed(event_data->it_handle, 10.000000f);
      aPhysFlags(1, 58720256, event_data->it_handle);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[32], 1048832, 0, 3);
      aObjSaveHandle(event_data->it_handle, 6);
      aUserFlagSet(7, 1);
      aSetLevelTimer(0.500000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 094: Send Armory Guard To Armory
    if (event_data->id == Matcen_indexes[6]) {
      aAISetMaxSpeed(event_data->it_handle, 30.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[52], 4352, 28, 3);
      aMatcenSetState(0, Matcen_indexes[6]);
      aSetLevelTimer(qRandomValue(120.000000f, 180.000000f), 18);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }

    // Script 082: Stormtrooper w/Claw Produced
    if (event_data->id == Matcen_indexes[4]) {
      aAISetMaxSpeed(event_data->it_handle, 16.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[56], 1048832, 30, 3);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }

    // Script 084: Heavytrooper w/Claw Produced
    if (event_data->id == Matcen_indexes[5]) {
      aAISetMaxSpeed(event_data->it_handle, 16.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[57], 1048832, 30, 3);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }

    // Script 118: Laser Room 1 Matcen Path
    if (event_data->id == Matcen_indexes[1]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[62], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }

    // Script 119: Laser Room 2 Matcen 1 Path
    if (event_data->id == Matcen_indexes[2]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[63], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }

    // Script 120: Laser Room 2 Matcen 2 Path
    if (event_data->id == Matcen_indexes[3]) {
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[64], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1119::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 088: Player picked up Infected Data Cartridge
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qUserFlag(25) == false) {
        aShowHUDMessage(Message_strings[1]);
        aSoundPlayObject(Sound_indexes[3], event_data->it_handle, 1.000000f);
        aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[1], 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 086: Give Closest Player the Infected Data Cartridge
    if ((ScriptActionCtr_086 < 1) && (qObjType(qPlayerClosest(data->me_handle, 8)) == 4)) {
      aAddObjectToInventoryNamed(data->me_handle, qPlayerClosest(data->me_handle, 8), Message_strings[1], 0);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 087: Player Used Infected Data Cartridge
    if (1) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[104]) < 40.000000f) {
        if (qUserFlag(24) == true) {
          aGoalCompleted(Goal_indexes[13], 1);
          aUserFlagSet(25, 1);
          aShowHUDMessage(Message_strings[20]);
          aStoreObjectInPositionClipboard(Object_handles[104]);
          aMoveObjectToPositionClipboard(data->me_handle);
          aObjGhostSet(0, data->me_handle);
          aSetLevelTimer(1.000000f, 19);
        } else {
          aShowHUDMessage(Message_strings[21]);
          aObjGhostSet(0, data->me_handle);
          aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[1], 0);
        }
      } else {
        aShowHUDMessage(Message_strings[22]);
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[1], 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10EC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 027: Beam Path 1 Done
    if (event_data->goal_uid == 2) {
      aAIGoalFollowPathSimple(Object_handles[19], Path_indexes[20], 2228480, 3, 3);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 028: Beam Path 1R Done
    if (event_data->goal_uid == 3) {
      aUserFlagSet(8, 0);
      if (qUserFlag(9) == false) {
        aAIGoalFollowPathSimple(Object_handles[19], Path_indexes[7], 2228480, 2, 3);
        aAIGoalFollowPathSimple(Object_handles[20], Path_indexes[8], 2228480, 4, 3);
        aUserFlagSet(8, 1);
        aUserFlagSet(9, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08F6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 029: Beam Path 2 Done
    if (event_data->goal_uid == 4) {
      aAIGoalFollowPathSimple(Object_handles[20], Path_indexes[21], 2228480, 5, 3);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 030: Beam Path 2R Done
    if (event_data->goal_uid == 5) {
      aUserFlagSet(9, 0);
      if (qUserFlag(8) == false) {
        aAIGoalFollowPathSimple(Object_handles[19], Path_indexes[7], 2228480, 2, 3);
        aAIGoalFollowPathSimple(Object_handles[20], Path_indexes[8], 2228480, 4, 3);
        aUserFlagSet(8, 1);
        aUserFlagSet(9, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08F8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 032: Beam Path 3 Done
    if (event_data->goal_uid == 6) {
      aAIGoalFollowPathSimple(Object_handles[21], Path_indexes[22], 2228480, 7, 3);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 033: Beam Path 3R Done
    if (event_data->goal_uid == 7) {
      aUserFlagSet(10, 0);
      if (qUserFlag(11) == false) {
        aAIGoalFollowPathSimple(Object_handles[21], Path_indexes[9], 2228480, 6, 3);
        aAIGoalFollowPathSimple(Object_handles[22], Path_indexes[10], 2228480, 8, 3);
        aUserFlagSet(10, 1);
        aUserFlagSet(11, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08F7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 034: Beam Path 4 Done
    if (event_data->goal_uid == 8) {
      aAIGoalFollowPathSimple(Object_handles[22], Path_indexes[23], 2228480, 9, 3);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 035: Beam Path 4R Done
    if (event_data->goal_uid == 9) {
      aUserFlagSet(11, 0);
      if (qUserFlag(10) == false) {
        aAIGoalFollowPathSimple(Object_handles[21], Path_indexes[9], 2228480, 6, 3);
        aAIGoalFollowPathSimple(Object_handles[22], Path_indexes[10], 2228480, 8, 3);
        aUserFlagSet(10, 1);
        aUserFlagSet(11, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 042: Beam Path 5 Done
    if (event_data->goal_uid == 10) {
      aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[24], 2228480, 11, 3);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 043: Beam Path 5R Done
    if (event_data->goal_uid == 11) {
      aUserFlagSet(16, 0);
      if (qUserFlag(17) == false) {
        aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[11], 2228480, 10, 3);
        aAIGoalFollowPathSimple(Object_handles[24], Path_indexes[12], 2228480, 12, 3);
        aUserFlagSet(16, 1);
        aUserFlagSet(17, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 044: Beam Path 6 Done
    if (event_data->goal_uid == 12) {
      aAIGoalFollowPathSimple(Object_handles[24], Path_indexes[25], 2228480, 13, 3);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 045: Beam Path 6R Done
    if (event_data->goal_uid == 13) {
      aUserFlagSet(17, 0);
      if (qUserFlag(16) == false) {
        aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[11], 2228480, 10, 3);
        aAIGoalFollowPathSimple(Object_handles[24], Path_indexes[12], 2228480, 12, 3);
        aUserFlagSet(16, 1);
        aUserFlagSet(17, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 046: Beam Path 7 Done
    if (event_data->goal_uid == 14) {
      aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[26], 2228480, 15, 3);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }

    // Script 047: Beam Path 7R Done
    if (event_data->goal_uid == 15) {
      aUserFlagSet(18, 0);
      if (qUserFlag(19) == false) {
        aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[13], 2228480, 14, 3);
        aAIGoalFollowPathSimple(Object_handles[26], Path_indexes[14], 2228480, 16, 3);
        aUserFlagSet(18, 1);
        aUserFlagSet(19, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 048: Beam Path 8 Done
    if (event_data->goal_uid == 16) {
      aAIGoalFollowPathSimple(Object_handles[26], Path_indexes[27], 2228480, 17, 3);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }

    // Script 049: Beam Path 8R Done
    if (event_data->goal_uid == 17) {
      aUserFlagSet(19, 0);
      if (qUserFlag(18) == false) {
        aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[13], 2228480, 14, 3);
        aAIGoalFollowPathSimple(Object_handles[26], Path_indexes[14], 2228480, 16, 3);
        aUserFlagSet(18, 1);
        aUserFlagSet(19, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 053: Beam Path 10 Done
    if (event_data->goal_uid == 18) {
      aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[28], 2228480, 19, 3);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 054: Beam Path 10R Done
    if (event_data->goal_uid == 19) {
      aUserFlagSet(20, 0);
      if (qUserFlag(21) == false) {
        aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[15], 2228480, 18, 3);
        aAIGoalFollowPathSimple(Object_handles[28], Path_indexes[16], 2228480, 20, 3);
        aUserFlagSet(20, 1);
        aUserFlagSet(21, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0900::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 055: Beam Path 11 Done
    if (event_data->goal_uid == 20) {
      aAIGoalFollowPathSimple(Object_handles[28], Path_indexes[29], 2228480, 21, 3);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }

    // Script 056: Beam Path 11R Done
    if (event_data->goal_uid == 21) {
      aUserFlagSet(21, 0);
      if (qUserFlag(20) == false) {
        aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[15], 2228480, 18, 3);
        aAIGoalFollowPathSimple(Object_handles[28], Path_indexes[16], 2228480, 20, 3);
        aUserFlagSet(20, 1);
        aUserFlagSet(21, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0901::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 057: Beam Path 12 Done
    if (event_data->goal_uid == 22) {
      aAIGoalFollowPathSimple(Object_handles[29], Path_indexes[30], 2228480, 23, 3);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }

    // Script 058: Beam Path 12R Done
    if (event_data->goal_uid == 23) {
      aUserFlagSet(22, 0);
      if (qUserFlag(23) == false) {
        aAIGoalFollowPathSimple(Object_handles[29], Path_indexes[17], 2228480, 22, 3);
        aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[18], 2228480, 24, 3);
        aUserFlagSet(22, 1);
        aUserFlagSet(23, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0902::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 059: Beam Path 13 Done
    if (event_data->goal_uid == 24) {
      aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[31], 2228480, 25, 3);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }

    // Script 060: Beam Path 13R Done
    if (event_data->goal_uid == 25) {
      aUserFlagSet(23, 0);
      if (qUserFlag(22) == false) {
        aAIGoalFollowPathSimple(Object_handles[29], Path_indexes[17], 2228480, 22, 3);
        aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[18], 2228480, 24, 3);
        aUserFlagSet(22, 1);
        aUserFlagSet(23, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 052: Laser Room 1 Pipe 1 Destroyed
    if (1) {
      aTurnOnSpew(Object_handles[83], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                  2.000000f, 15.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0818::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 036: Laser Room 2 Pipe 1 Destroyed
    if (1) {
      aTurnOnSpew(Object_handles[85], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                  2.000000f, 15.000000f, 1, -1);
      if (qUserFlag(15) == false) {
        aRoomSetFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 1000.000000f);
        aRoomFogSetState(1, Room_indexes[3]);
        aRoomChangeFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 300.000000f, 4.000000f);
        aUserFlagSet(15, 1);
        aSetLevelTimer(0.500000f, 13);
      }

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 038: Laser Room 2 Pipe 2 Destroyed
    if (1) {
      aTurnOnSpew(Object_handles[87], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                  2.000000f, 15.000000f, 1, -1);
      if (qUserFlag(15) == false) {
        aRoomSetFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 1000.000000f);
        aRoomFogSetState(1, Room_indexes[3]);
        aRoomChangeFog(Room_indexes[3], 0.500000f, 0.500000f, 0.500000f, 300.000000f, 4.000000f);
        aUserFlagSet(15, 1);
        aSetLevelTimer(0.500000f, 13);
      }

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10CF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Player Entered Scan Tower
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(0) == false) && (qUserFlag(1) == false) &&
        (qUserFlag(2) == false)) {
      aSoundPlaySteaming("VoxMerc02FCV1.osf", 1.000000f);
      aObjSaveHandle(event_data->it_handle, 2);
      aRoomSetFaceTexture(Room_indexes[15], 45, Texture_indexes[5]);
      aRoomSetFaceTexture(Room_indexes[15], 30, Texture_indexes[5]);
      aUserFlagSet(0, 1);
      aShowHUDMessage(Message_strings[3]);
      aSetLevelTimer(0.500000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_30B2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Tracker 01 Was Attacked
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aSetLevelTimer(0.100000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10B1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Tracker 02 Was Attacked
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aSetLevelTimer(0.100000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1040::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Main Gate Guard 1 Was Attacked
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aSetLevelTimer(0.100000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1041::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Main Gate Guard 2 Was Attacked
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aSetLevelTimer(0.100000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_103F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 025: Crate Stack Was Destroyed
    if (1) {
      aObjMakeVulnerable(Object_handles[62]);
      aObjDestroy(Object_handles[62]);
      if (qGoalEnabled(Goal_indexes[6]) == true) {
        aShowHUDMessage(Message_strings[13]);
      }
      aGoalCompleted(Goal_indexes[6], 1);
      if (qGoalCompleted(Goal_indexes[7]) == false) {
        aGoalCompleted(Goal_indexes[7], 1);
      }
      aGoalEnableDisable(0, Goal_indexes[8]);
      aGoalEnableDisable(1, Goal_indexes[9]);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08DE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 026: Turret Control Destroyed
    if (1) {
      aShowHUDMessage(Message_strings[14]);
      aSetLevelTimer(2.000000f, 16);
      aGoalCompleted(Goal_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_110E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 107: General is Dead
    if (1) {
      aShowHUDMessage(Message_strings[17]);
      aGoalCompleted(Goal_indexes[11], 1);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 066: General Flew In
    if (event_data->goal_uid == 27) {
      aTurnOnSpew(Object_handles[65], 0, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, -1.000000f, 3.000000f,
                  20.000000f, 0, 0);
      aTurnOnSpew(Object_handles[65], 1, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, -1.000000f, 3.000000f,
                  20.000000f, 0, 1);
      aTurnOnSpew(Object_handles[65], 2, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, -1.000000f, 3.000000f,
                  20.000000f, 0, 2);
      aTurnOnSpew(Object_handles[65], 3, 7, 0.000000f, 0.000000f, 65536, 0, 0.800000f, 0.100000f, -1.000000f, 3.000000f,
                  20.000000f, 0, 3);
      aDoorSetPos(Door_handles[3], 0.000000f);
      aAISetMaxSpeed(Object_handles[65], 5.000000f);
      aAIGoalFollowPathSimple(Object_handles[65], Path_indexes[38], 1048832, 26, 3);
      aAIGoalSetCircleDistance(Object_handles[65], 3, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }

    // Script 067: General Landed
    if (event_data->goal_uid == 26) {
      aTurnOffSpew(0);
      aTurnOffSpew(1);
      aTurnOffSpew(2);
      aTurnOffSpew(3);
      aObjMakeVulnerable(Object_handles[66]);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10CD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Player picked up Data Cartridge
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aUserFlagSet(24, 1);
      aSoundPlayObject(Sound_indexes[3], event_data->it_handle, 1.000000f);
      aShowHUDMessage(Message_strings[18]);
      aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[18], 0);
      aGoalCompleted(Goal_indexes[12], 1);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 070: Player Used Data Cartridge
    if (1) {
      aShowHUDMessage(Message_strings[19]);
      aObjGhostSet(0, data->me_handle);
      aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[18], 0);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 074: End Trooper 1 Killed
    if (1) {
      aGoalItemCompleted(Goal_indexes[16], 1, 1);
      aUserVarInc(7);
      if (qUserVarValue(7) >= 2.000000f) {
        aDoorLockUnlock(0, Door_handles[5]);
        aDoorSetPos(Door_handles[5], 1.000000f);
        aShowHUDMessage(Message_strings[25]);
        aGoalCompleted(Goal_indexes[16], 1);
        aMusicSetRegionAll(4);
      }

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 075: End Trooper 2 Killed
    if (1) {
      aGoalItemCompleted(Goal_indexes[16], 2, 1);
      aUserVarInc(7);
      if (qUserVarValue(7) >= 2.000000f) {
        aDoorLockUnlock(0, Door_handles[5]);
        aDoorSetPos(Door_handles[5], 1.000000f);
        aShowHUDMessage(Message_strings[25]);
        aGoalCompleted(Goal_indexes[16], 1);
        aMusicSetRegionAll(4);
      }

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1112::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Armory Door Switch Hit
    if ((ScriptActionCtr_080 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aDoorLockUnlock(0, Door_handles[6]);
      aShowHUDMessage(Message_strings[26]);
      aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[5], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0913::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Central FF Switch Hit
    if ((ScriptActionCtr_081 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aPortalRenderSet(0, 2, Room_indexes[22], 1);
      aShowHUDMessage(Message_strings[27]);
      aObjPlayAnim(data->me_handle, 0, 3, 4.000000f, 0);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);
      aGoalCompleted(Goal_indexes[17], 1);
      aAIGoalFollowPathSimple(Object_handles[121], Path_indexes[55], 4198656, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 100: Check Restricted Access Entrance Camera
    if ((ScriptActionCtr_100 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aSoundPlaySteaming("VoxMerc02FPA1.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 101: Check Restricted Hall A Camera 1
    if ((ScriptActionCtr_101 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aAISetState(1, Object_handles[55]);
      aObjSetMovementType(Object_handles[8], 1);
      aObjSetLightingDist(Object_handles[8], 70.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[8], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1048::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 112: Res Hall A Turret 1 Hit
    if ((ScriptActionCtr_112 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[55]);
      aObjSetMovementType(Object_handles[8], 1);
      aObjSetLightingDist(Object_handles[8], 70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1111::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 102: Check Restricted Hall A Camera 2
    if ((ScriptActionCtr_102 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aAISetState(1, Object_handles[56]);
      aObjSetMovementType(Object_handles[9], 1);
      aObjSetLightingDist(Object_handles[9], 70.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[9], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1067::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 113: Res Hall A Turret 2 Hit
    if ((ScriptActionCtr_113 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[56]);
      aObjSetMovementType(Object_handles[9], 1);
      aObjSetLightingDist(Object_handles[9], 70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_088C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 103: Check Armory Camera
    if ((ScriptActionCtr_103 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aAISetState(1, Object_handles[57]);
      aObjSetMovementType(Object_handles[10], 1);
      aObjSetLightingDist(Object_handles[10], 70.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[10], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_108B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 114: Armory Turret Hit
    if ((ScriptActionCtr_114 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[57]);
      aObjSetMovementType(Object_handles[10], 1);
      aObjSetLightingDist(Object_handles[10], 70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0883::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 104: Check Res Hall C Camera
    if ((ScriptActionCtr_104 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aAISetState(1, Object_handles[58]);
      aObjSetMovementType(Object_handles[11], 1);
      aObjSetLightingDist(Object_handles[11], 70.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[11], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1884::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 115: Res Hall C Turret Hit
    if ((ScriptActionCtr_115 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[58]);
      aObjSetMovementType(Object_handles[11], 1);
      aObjSetLightingDist(Object_handles[11], 70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_106F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 105: Check Hall C Camera 1
    if ((ScriptActionCtr_105 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aAISetState(1, Object_handles[59]);
      aObjSetMovementType(Object_handles[12], 1);
      aObjSetLightingDist(Object_handles[12], 70.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[12], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1071::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 116: Hall C Turret 1 Hit
    if ((ScriptActionCtr_116 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[59]);
      aObjSetMovementType(Object_handles[12], 1);
      aObjSetLightingDist(Object_handles[12], 70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0894::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 106: Check Hall C Camera 2
    if ((ScriptActionCtr_106 < 1) && (qSecurityCameraAlerted(data->me_handle) == true)) {
      aShowHUDMessage(Message_strings[28]);
      aAISetState(1, Object_handles[60]);
      aObjSetMovementType(Object_handles[13], 1);
      aObjSetLightingDist(Object_handles[13], 70.000000f);
      aSoundPlayObject(Sound_indexes[1], Object_handles[13], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0893::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 117: Hall C Turret 2 Hit
    if ((ScriptActionCtr_117 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[60]);
      aObjSetMovementType(Object_handles[13], 1);
      aObjSetLightingDist(Object_handles[13], 70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0806::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 108: Res Area Entrance Door Hit
    if ((ScriptActionCtr_108 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlaySteaming("VoxMerc02FPA1.osf", 1.000000f);
      if ((qGoalEnabled(Goal_indexes[6]) == false) && (qGoalCompleted(Goal_indexes[6]) == false)) {
        aShowHUDMessage(Message_strings[29]);
        aGoalEnableDisable(1, Goal_indexes[6]);
        aGoalEnableDisable(0, Goal_indexes[8]);
        aGoalEnableDisable(1, Goal_indexes[9]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1842::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 110: Super Laser Picked Up
    if ((ScriptActionCtr_110 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[7], 1);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_082F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 122: Welder Finished Path A
    if (event_data->goal_uid == 37) {
      aUserFlagSet(26, 1);
      aObjSetMovementType(Object_handles[76], 0);
      aSetLevelTimer(qRandomValue(10.000000f, 20.000000f), 25);

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }

    // Script 123: Welder Finished Path B
    if (event_data->goal_uid == 38) {
      aUserFlagSet(26, 1);
      aObjSetMovementType(Object_handles[76], 0);
      aSetLevelTimer(qRandomValue(10.000000f, 20.000000f), 24);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Laser Room 1 Monitor Hit
    if ((ScriptActionCtr_051 < 1) && (qUserFlag(14) == true)) {
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aPortalRenderSet(0, 1, Room_indexes[2], 1);
      aGoalCompleted(Goal_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: Laser Room 2 Monitor 1 Hit
    if ((ScriptActionCtr_040 < 1) && (qUserFlag(13) == true)) {
      aUserVarInc(4);
      if (qUserVarValue(4) == 1.000000f) {
        aGoalItemCompleted(Goal_indexes[1], 1, 1);
      }
      if (qUserVarValue(4) == 2.000000f) {
        aPortalRenderSet(0, 0, Room_indexes[3], 1);
        aPortalRenderSet(0, 1, Room_indexes[4], 1);
        aPortalRenderSet(0, 2, Room_indexes[4], 1);
        aGoalItemCompleted(Goal_indexes[1], 1, 1);
        aGoalCompleted(Goal_indexes[1], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: Laser Room 2 Monitor 2 Hit
    if ((ScriptActionCtr_041 < 1) && (qUserFlag(13) == true)) {
      aUserVarInc(4);
      if (qUserVarValue(4) == 1.000000f) {
        aGoalItemCompleted(Goal_indexes[1], 2, 1);
      }
      if (qUserVarValue(4) == 2.000000f) {
        aPortalRenderSet(0, 0, Room_indexes[3], 1);
        aPortalRenderSet(0, 1, Room_indexes[4], 1);
        aPortalRenderSet(0, 2, Room_indexes[4], 1);
        aGoalItemCompleted(Goal_indexes[1], 2, 1);
        aGoalCompleted(Goal_indexes[1], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Gate Monitor 1 Hit
    if ((ScriptActionCtr_012 < 1) && (qUserFlag(2) == true)) {
      aUserVarInc(1);
      if (qUserVarValue(1) == 1.000000f) {
        aGoalItemCompleted(Goal_indexes[4], 1, 1);
      }
      if (qUserVarValue(1) == 2.000000f) {
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
        aShowHUDMessage(Message_strings[4]);
        aGoalItemCompleted(Goal_indexes[4], 1, 1);
        aGoalCompleted(Goal_indexes[4], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Gate Monitor 2 Hit
    if ((ScriptActionCtr_013 < 1) && (qUserFlag(2) == true)) {
      aUserVarInc(1);
      if (qUserVarValue(1) == 1.000000f) {
        aGoalItemCompleted(Goal_indexes[4], 2, 1);
      }
      if (qUserVarValue(1) == 2.000000f) {
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
        aShowHUDMessage(Message_strings[4]);
        aGoalItemCompleted(Goal_indexes[4], 2, 1);
        aGoalCompleted(Goal_indexes[4], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Entered Main Base
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalCompleted(Goal_indexes[3], 1);
      aDoorLockUnlock(0, Door_handles[0]);
      if ((qGoalEnabled(Goal_indexes[4]) == true) && (qGoalCompleted(Goal_indexes[4]) == false)) {
        aGoalEnableDisable(0, Goal_indexes[4]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Entered Weapon Check Point
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(3) == 0)) {
      aShowHUDMessage(Message_strings[7]);
      aUserFlagSet(3, 1);
      aSetLevelTimer(3.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Worker Screwup Trigger
    if ((ScriptActionCtr_062 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(1.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: General Landing Trigger
    if ((ScriptActionCtr_064 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(2, event_data->it_handle);
      aSetLevelTimer(1.000000f, 15);
      aSoundPlaySteaming("VoxMerc02MPA1.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 127: Left Hangar Area
    if ((ScriptActionCtr_127 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: Heavy Trooper 1 Trigger Hit
    if ((ScriptActionCtr_071 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aAISetState(1, Object_handles[45]);
      aAIGoalFollowPathSimple(Object_handles[45], Path_indexes[45], 4352, -1, 3);
      aObjMakeVulnerable(Object_handles[68]);
      aObjDestroy(Object_handles[68]);
      aAIGoalFollowPathSimple(Object_handles[115], Path_indexes[46], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[116], Path_indexes[47], 8392960, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 072: End Trooper Trigger Hit
    if ((ScriptActionCtr_072 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[24]);
      aAISetState(1, Object_handles[47]);
      aAIGoalFollowPathSimple(Object_handles[47], Path_indexes[48], 4352, -1, 3);
      aObjMakeVulnerable(Object_handles[70]);
      aObjDestroy(Object_handles[70]);
      aSetLevelTimer(4.000000f, 17);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Armory Guard Trigger Hit
    if ((ScriptActionCtr_076 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(0.100000f, 18);
      aAIGoalFollowPathSimple(Object_handles[117], Path_indexes[50], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[118], Path_indexes[51], 4198656, -1, 0);
      aSoundPlaySteaming("VoxMerc02MPA2.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Escape Trigger Hit
    if ((ScriptActionCtr_085 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aEnableShip("Black Pyro");
      aDisableShip("Phoenix");
      aStartEndlevelSequencePath(Path_indexes[58], Path_indexes[59], 5.000000f, Message_strings[16]);
      aGoalCompleted(Goal_indexes[15], 1);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 109: Crate Room Trigger Hit
    if ((ScriptActionCtr_109 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      if ((qGoalEnabled(Goal_indexes[6]) == true) && (qGoalCompleted(Goal_indexes[6]) == false) &&
          (qGoalCompleted(Goal_indexes[7]) == false)) {
        aShowHUDMessage(Message_strings[30]);
        aGoalEnableDisable(1, Goal_indexes[7]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 111: Entered Res Area
    if ((ScriptActionCtr_111 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[9], 1);
      aAIGoalFollowPathSimple(Object_handles[134], Path_indexes[60], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[135], Path_indexes[61], 4198656, -1, 0);
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 126: Left Res Area
    if ((ScriptActionCtr_126 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aMusicSetRegion(0, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
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
NEXT_ID		129

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:NumScansDone
1:NumGateMonitorsFried
2:ThreatState
3:PlayerDist
4:NumLR2MonitorsFried
5:BeamFadeInLevel
6:BeamTextureID
7:EndTroopersKilled
8:TempDist
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:ScanningPlayer
1:PlayerScanned
2:MainGateSecurityAlerted
3:WeaponCheckActive
4:WeaponsChecked
5:WeaponCheckThreatDetected
6:PlayerIsInPosition
7:WeaponGuardIsInTransit
8:Beam1Moving
9:Beam2Moving
10:Beam3Moving
11:Beam4Moving
12:LaserRoom2Fogged
13:LaserRoom2BeamsBroken
14:LaserRoom1BeamsBroken
15:LaserRoom2FogStarted
16:Beam5Moving
17:Beam6Moving
18:Beam7Moving
19:Beam8Moving
20:Beam10Moving
21:Beam11Moving
22:Beam12Moving
23:Beam13Moving
24:PlayerGotDataCartridge
25:InfectedCartridgePlaced
26:WelderIsWelding
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:GenSpew1
1:GenSpew2
2:GenSpew3
3:GenSpew4
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:DoInit
1:DoPlayerScan
2:ResetScanProcess
3:AlertGateSecurity
4:CheckTrackerChildrenForDamage
5:DoWeaponCheckSequence
6:DoLaserRoom2Checks
7:DoWeaponCheckThreatSequence
8:SendWeaponGuardHome
9:CheckIfWeaponGuardHasBeenDamaged
10:DoLaserRoom1Checks
11:UpdateLaserRoom1Beams
12:UpdateLaserRoom2Beams
13:LaserRoom2Fogged
14:WorkerScrewup
15:GeneralLandingNow
16:DestroyGeneralSequence
17:EndTrooper
18:StartArmoryGuard
19:SelfDestructSequence
20:UpdateDataCartridgeEffects
21:MakeArmoryGuardLeave
22:CloseArmoryDoor
23:DoWelderSparks
24:StartWelderOnPathA
25:StartWelderOnPathB
26:PlayTowerVoice
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:Tracker01Turret
1:Tracker02Turret
2:ScannedPlayer
3:Tracker01Hatch
4:Tracker02Hatch
5:WeaponCheckPlayer
6:WeaponGuard
7:CartridgeHandle
8:ArmoryGadgetHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:WpnGuardEntered
1:WpnGuardLeft
2:Beam1Done
3:Beam1RDone
4:Beam2Done
5:Beam2RDone
6:Beam3Done
7:Beam3RDone
8:Beam4Done
9:Beam4RDone
10:Beam5Done
11:Beam5RDone
12:Beam6Done
13:Beam6RDone
14:Beam7Done
15:Beam7RDone
16:Beam8Done
17:Beam8RDone
18:Beam10Done
19:Beam10RDone
20:Beam11Done
21:Beam11RDone
22:Beam12Done
23:Beam12RDone
24:Beam13Done
25:Beam13RDone
26:GeneralsShipLanded
27:GeneralFlewIn
28:ArmoryGuardGotToDoor
29:ArmoryGuardWentThroughDoor
30:STrooperClawDone
31:EndBeamADone
32:EndBeamBDone
33:EndBeamCDone
34:ArmoryGuardGotToDoorAgain
35:ArmoryGuardWentThroughDoorAgain
36:DeleteArmoryGuard
37:WelderGotToShipA
38:WelderGotToShipB
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
MainGateDoor
GenHangarDoor
ResEntDoor
GeneralDoor
CompDoor
LastDoor
ArmoryDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
LR1Sound
LR2Sound
RepairRoomWelder
WorkerScrewup
Welder2
Welder3
LR1Light
LR2Light
ResHallALight
ResHallALight2
ArmoryLight
HallCSLight
HallCLight1
HallCLight2
CompEscapeFan
MainGateGuard1
MainGateGuard2
TowerScanner
WeaponCheckPoint
Beam1Source
Beam2Source
BeamSource3
BeamSource4
BeamSource5
BeamSource6
BeamSource7
BeamSource8
BeamSource10
BeamSource11
BeamSource12
BeamSource13
LRSBeam01a
LRSBeam01b
LRSBeam03a
LRSBeam03b
LRSBeam04a
LRSBeam04b
LRSBeam06a
LRSBeam06b
EndBeamA1
EndBeamA2
EndBeamB1
EndBeamB2
EndBeamC1
EndBeamC2
HTrooper01
EndHTrooper01
EndHTrooper02
LaserPickup
GenGuardHeavyT01
GenGuardTrooper01
GenGuardTrooper02
GenGuardTrooper03
GenGuardSwatter01
GenGuardSwatter02
ResHallATurret01
ResHallATurret2
ArmoryTurret
ResHallCTurret
HallCTurret01
HallCTurret02
LR1PipeCam1
CrateStackFloor
BasementCeiling
WorkerScrewupMachi
GeneralsShip
TurretControl
GenLandingPad
HTrooper01Wall
EndTrooper01wall
EndTrooper02wall
GeneralBarrels
GeneralStack
WorkerScrewup2
WorkerScrewup3
Lifter (Hangar)
Welder (cargoship)
FlybyShip
Tracker01
Tracker02
StFactory02Constru
InfectedDataCartri
LR1Pipe
LR1PipeCam2
LaserRoom02Pipe01
L02Pipe1Cam
LaserRoom02Pipe02
L02Pipe2Cam
TowerFT1Cam
TowerFB1Cam
TowerFT2Cam
TowerFB2Cam
TowerFB3Cam
TowerFT3Cam
TowerBT1Cam
TowerBB1Cam
TowerBT2Cam
TowerBB2Cam
TowerBB3Cam
TowerBT3Cam
CrateStack
WorkerScrewupCam
WorkerScrewupCam2
DataCartridge
DataPosition
EndSpew1
EndSpew2
EndSpew3
EndSpew4
EndBeamA1Pos
EndBeamA2Pos
EndBeamB1Pos
EndBeamB2Pos
EndBeamC1Pos
EndBeamC2Pos
HallCTrooper1
HallCTrooper2
RHBPatTroop01
RHBPatTroop02
ArmoryDoorSwitch
CentralFFSwitch
HallCSTrooper
DataCam1
DataCam2
DataCam3
ResEntSecCam01
ResHallASecCam01
ResHallASecCam02
ArmorySecCam
ResHallCSCam
HallCsecCam01
HallCsecCam02
ResEntDoor
SuperDuperLaser
ResHallATrooper
ResHallATrooper2
$$OBJECT_LIST_END

$$ROOM_LIST_START
Weapon Check
LaserRoom01
LaserRoom01b
LaserRoom02
LaserRoom02b
EscapePipe1
EscapePipe2
ExitFanRoom
Comp01Wind
Comp02Wind
Comp03Wind
Comp04Wind
LaserRoom01BotSpaw
LaserRoom02Spawn01
LaserRoom02Spawn02
ScanTower
MineEntrance
CompHub
Comp01
Comp02
Comp03
Comp04
CentralFFRoom
$$ROOM_LIST_END

$$TRIGGER_LIST_START
LR1MonitorHit
LR2Monitor1Hit
LR2Monitor2Hit
GateMonitor1
GateMonitor2
EnteredMainGate
WeaponCheckEntered
WorkerScrewup
GeneralShipLanding
LeftHangarArea
HTrooper01Trigger
EndTrooperTrigger
ArmoryGuardTrigger
EscapeTrigger
CrateRoomEntered
ResAreaTrigger
LeftResArea
$$TRIGGER_LIST_END

$$SOUND_LIST_START
Merc2LaserBeam
Merc2AlertSiren
Merc2IGSqueel
Powerup pickup
Merc2ShortingComputer
AmbSwitch31
AmbSwitch41
$$SOUND_LIST_END

$$TEXTURE_LIST_START
M02MonitorScreen
Stlaser
Stlaser25alpha
Stlaser50alpha
Stlaser75alpha
M02_Scanning
M02_Cleared
Lightning4
M02_Aborted
M02_Ready
M02_BreachedNoDes
FunkyEffect2
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
Black Pyro
Phoenix
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCamPath
IntroPlayerPath
LifterPath
WelderPathA
FlybyPath
Tracker01Path
Tracker02Path
BeamPath1
BeamPath2
BeamPath3
BeamPath4
BeamPath5
BeamPath6
BeamPath7
BeamPath8
BeamPath10
BeamPath11
BeamPath12
BeamPath13
HTClawAmbientPath
BeamPath1R
BeamPath2R
BeamPath3R
BeamPath4R
BeamPath5R
BeamPath6R
BeamPath7R
BeamPath8R
BeamPath10R
BeamPath11R
BeamPath12R
BeamPath13R
WpnCheckEntryPath
WpnCheckExitPath
WorkerScrewupPath
WorkerScrewup3Path
GeneralCamPath
GeneralLandingPath
GeneralLandingPath2
EndBeamA1Path
EndBeamA2Path
EndBeamB1Path
EndBeamB2Path
EndBeamC1Path
EndBeamC2Path
HTrooper01Path
HallCTrooper1Path
HallCTrooper2Path
EndTrooper2Path
EndTrooper1Path
ArmoryTrooper1Path
ArmoryTrooper2Path
ArmoryGuardPath
ArmoryGuardPath2
ArmoryGuardPath3
HallCSTrooperPath
StormtrooperClawPath
HeavyTrooperClawPath
EndCamPath
PlayerEndPath
ResHallATrooperPath
ResHallATrooper2Path
LR1MatcenPath
LR2Matcen1Path
LR2Matcen2Path
WelderPathB
$$PATH_LIST_END

$$MATCEN_LIST_START
WpnGuard1Matcen
LaserRoom1Matcen
LaserRoom2Matcen1
LaserRoom2Matcen2
STrooperClawMatcen
HTrooperClawMatcen
ArmoryGadgetMatcen
$$MATCEN_LIST_END

$$GOAL_LIST_START
Disable Forcefields in Laser Room A
Disable Forcefields in Laser Room B
Get Cleared at Scanning Tower
Enter Base
Override Main Gate System
Pass Through Weapon Checkpoint
Bypass Restricted Area Checkpoint
Acquire a Weapon
Enter Restricted Area
Get Inside Restricted Area
Create a Diversion
Assassinate General Morgan
Obtain Failsafe Data
Place Infected Cartridge
Destroy Mainframe Computer
Escape
Destroy Exit Tunnel Guards
Deactivate Central Forcefield
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxMerc02MPA3.osf
VoxMerc02FCV1.osf
VoxMerc02FCV3.osf
VoxMerc02FCV2.osf
VoxMerc02FCV4.osf
VoxMerc02MPA1.osf
VoxMerc02FPA2.osf
VoxMerc02FPA3.osf
VoxMerc02MPA2.osf
VoxMerc02FPA1.osf
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
                        10:10:0:0:UserFlag
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
                        10:10:0:8:UserFlag
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:20:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:22:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:23:UserFlag
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
                        10:10:0:24:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
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
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        10:6:0.000000:value
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
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
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:10:0:0:MovementType
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
                        10:1:0:8:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:0:StartFrame
                        10:4:15:EndFrame
                        10:6:0.500000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
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
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:45:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:46:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:53:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:54:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:55:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:56:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:58:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:59:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:60:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
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
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:10.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:23:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:20:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Level Start - Matcens
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Level Start - Intro Cinematic
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
                        10:8:IntroText:Text
                        10:1:0:17:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:18.000000:Time
                        10:10:0:26:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:Play Tower Chatter Voice Over
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Level Start + 0.5 sec - Do Init
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
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:5:Region
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:16:2:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:16:3:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:37:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSetTurnRate
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:6:11000.000000:Turn Rate
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        10:16:4:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:78:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:79:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:78:Object
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:78:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:79:Object
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:79:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:4:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:16:5:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:16:6:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:6:20.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:6:20.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:6:35.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:6:35.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:16:7:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:2:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:16:8:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:4:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:9:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:16:10:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:8:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:11:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:10:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:16:12:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:12:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:16:13:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:14:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:16:14:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:16:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:16:15:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:18:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:16:16:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:20:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:16:17:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:22:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:16:18:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:24:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:16:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:19:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:20:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:22:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:23:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.750000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:0:Set/Clear
                        10:15:128:AIFlags
                        10:1:0:49:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:0:Set/Clear
                        10:15:128:AIFlags
                        10:1:0:50:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:0:Set/Clear
                        10:15:128:AIFlags
                        10:1:0:51:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:0:Set/Clear
                        10:15:128:AIFlags
                        10:1:0:52:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:16:19:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Give Closest Player the Infected Data Cartridge
        $$CHILD_BLOCK_START
        01:1:81
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
                                        10:10:0:8:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:10:0:4:ObjectType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:8:UserVar
                                $$CHILD_BLOCK_END
                        10:8:InfectedDataCartridgeName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Beam Path 1 Done
        $$CHILD_BLOCK_START
        01:1:19
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:16:20:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Beam Path 1R Done
        $$CHILD_BLOCK_START
        01:1:19
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object
                                10:16:7:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object
                                10:16:8:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:4:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Beam Path 2 Done
        $$CHILD_BLOCK_START
        01:1:20
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
                        10:1:0:20:Object
                        10:16:21:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:5:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Beam Path 2R Done
        $$CHILD_BLOCK_START
        01:1:20
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object
                                10:16:7:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:2:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object
                                10:16:8:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:4:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Beam Path 3 Done
        $$CHILD_BLOCK_START
        01:1:21
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:22:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:7:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Beam Path 3R Done
        $$CHILD_BLOCK_START
        01:1:21
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:16:9:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:6:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:22:Object
                                10:16:10:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:8:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:10:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Beam Path 4 Done
        $$CHILD_BLOCK_START
        01:1:22
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:16:23:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:9:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Beam Path 4R Done
        $$CHILD_BLOCK_START
        01:1:22
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:16:9:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:6:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:22:Object
                                10:16:10:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:8:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:10:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Beam Path 5 Done
        $$CHILD_BLOCK_START
        01:1:23
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
                        10:1:0:23:Object
                        10:16:24:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:11:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Beam Path 5R Done
        $$CHILD_BLOCK_START
        01:1:23
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:16:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:17:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                10:16:11:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:10:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                10:16:12:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:12:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:16:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:17:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Beam Path 6 Done
        $$CHILD_BLOCK_START
        01:1:24
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:12:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:16:25:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:13:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Beam Path 6R Done
        $$CHILD_BLOCK_START
        01:1:24
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:13:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object
                                10:16:11:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:10:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                10:16:12:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:12:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:16:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:17:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Beam Path 7 Done
        $$CHILD_BLOCK_START
        01:1:25
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:14:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:16:26:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:15:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Beam Path 7R Done
        $$CHILD_BLOCK_START
        01:1:25
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:15:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:19:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:25:Object
                                10:16:13:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:14:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:26:Object
                                10:16:14:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:16:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:18:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:19:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Beam Path 8 Done
        $$CHILD_BLOCK_START
        01:1:26
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:16:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:16:27:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:17:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Beam Path 8R Done
        $$CHILD_BLOCK_START
        01:1:26
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:17:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:18:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:25:Object
                                10:16:13:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:14:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:26:Object
                                10:16:14:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:16:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:18:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:19:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Beam Path 10 Done
        $$CHILD_BLOCK_START
        01:1:27
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:18:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:16:28:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:19:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Beam Path 10R Done
        $$CHILD_BLOCK_START
        01:1:27
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:19:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:20:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:21:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:16:15:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:18:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                10:16:16:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:20:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:20:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:21:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Beam Path 11 Done
        $$CHILD_BLOCK_START
        01:1:28
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:20:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:16:29:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:21:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Beam Path 11R Done
        $$CHILD_BLOCK_START
        01:1:28
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:21:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:20:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:16:15:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:18:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                10:16:16:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:20:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:20:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:21:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Beam Path 12 Done
        $$CHILD_BLOCK_START
        01:1:29
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:22:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:16:30:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:23:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Beam Path 12R Done
        $$CHILD_BLOCK_START
        01:1:29
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:23:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:22:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:23:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:29:Object
                                10:16:17:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:22:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:30:Object
                                10:16:18:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:24:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:22:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:23:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Beam Path 13 Done
        $$CHILD_BLOCK_START
        01:1:30
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:24:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:16:31:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:25:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Beam Path 13R Done
        $$CHILD_BLOCK_START
        01:1:30
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:25:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:23:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:22:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:29:Object
                                10:16:17:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:22:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:30:Object
                                10:16:18:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:24:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:22:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:23:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Check Laser Room 1's Beams
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:31:Beam Source A
                                                10:1:0:32:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:27:Beam Source A
                                                10:1:0:28:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:33:Beam Source A
                                                10:1:0:34:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:35:Beam Source A
                                                10:1:0:36:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:29:Beam Source A
                                                10:1:0:30:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:37:Beam Source A
                                                10:1:0:38:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LaserBeamTriggered:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:1:Room
                                10:5:0:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:2:Room
                                10:5:0:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:2:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:4:67:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:6:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundStopObj
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Check Laser Room 2's Beams
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:19:Beam Source A
                                                10:1:0:20:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:21:Beam Source A
                                                10:1:0:22:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:23:Beam Source A
                                                10:1:0:24:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qBeamHittingPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:25:Beam Source A
                                                10:1:0:26:Beam Source B
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LaserBeamTriggered:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:0:PortalNum
                                10:2:3:Room
                                10:5:0:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:1:PortalNum
                                10:2:4:Room
                                10:5:0:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:4:2:PortalNum
                                10:2:4:Room
                                10:5:0:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:3:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:4:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:13:Room
                                10:4:67:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:14:Room
                                10:4:67:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:1:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:2:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:2:Matcen
                                $$CHILD_BLOCK_END
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
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:6:70.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:7:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundStopObj
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Laser Room 1 Monitor Hit
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
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
        04:0:0:1
                $$CHILD_BLOCK_START
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
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Laser Room 2 Monitor 1 Hit
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:4:1:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:4:1:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Laser Room 2 Monitor 2 Hit
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:4:2:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:4:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:4:2:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Update Laser Room 1's Beams
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                06:qConvertTextureIDToFloat:value
                                        $$CHILD_BLOCK_START
                                        10:14:1:Texture ID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:31:Object1
                                10:1:0:32:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object1
                                10:1:0:28:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:33:Object1
                                10:1:0:34:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object1
                                10:1:0:36:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:29:Object1
                                10:1:0:30:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:37:Object1
                                10:1:0:38:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Update Laser Room 2's Beams
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
                        09:0
                                $$CHILD_BLOCK_START
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
                                                10:10:0:5:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:6.000000:Literal
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
                                                        10:10:0:5:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:2.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                06:qConvertTextureIDToFloat:value
                                                        $$CHILD_BLOCK_START
                                                        10:14:2:Texture ID
                                                        $$CHILD_BLOCK_END
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
                                                                10:10:0:5:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:4
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:5:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                06:qConvertTextureIDToFloat:value
                                                        $$CHILD_BLOCK_START
                                                        10:14:3:Texture ID
                                                        $$CHILD_BLOCK_END
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
                                                                10:10:0:5:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:4
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:5:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        10:6:6.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                06:qConvertTextureIDToFloat:value
                                                        $$CHILD_BLOCK_START
                                                        10:14:4:Texture ID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        06:qConvertTextureIDToFloat:value
                                                $$CHILD_BLOCK_START
                                                10:14:1:Texture ID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object1
                                10:1:0:20:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object1
                                10:1:0:22:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:23:Object1
                                10:1:0:24:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:25:Object1
                                10:1:0:26:Object2
                                10:6:0.500000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                06:qConvertFloatToTextureID:Texture
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Value
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                10:6:0.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Laser Room 1 Pipe 1 Destroyed
        $$CHILD_BLOCK_START
        01:1:82
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Laser Room 2 Pipe 1 Destroyed
        $$CHILD_BLOCK_START
        01:1:84
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.500000:Red
                                10:6:0.500000:Green
                                10:6:0.500000:Blue
                                10:6:1000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:3:Room
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.500000:Red
                                10:6:0.500000:Green
                                10:6:0.500000:Blue
                                10:6:300.000000:Depth
                                10:6:4.000000:Time
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.500000:Time
                                10:10:0:13:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Laser Room 2 Pipe 2 Destroyed
        $$CHILD_BLOCK_START
        01:1:86
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.500000:Red
                                10:6:0.500000:Green
                                10:6:0.500000:Blue
                                10:6:1000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:3:Room
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.500000:Red
                                10:6:0.500000:Green
                                10:6:0.500000:Blue
                                10:6:300.000000:Depth
                                10:6:4.000000:Time
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.500000:Time
                                10:10:0:13:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Laser Room 2 Is Fogged Enough to See Lasers
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Player Entered Scan Tower
        $$CHILD_BLOCK_START
        01:1:17
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
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:4:45:FaceNum
                        10:14:5:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:4:30:FaceNum
                        10:14:5:Texture
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ScanTowerEntered:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Perform Player Scan
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
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:8.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:2:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:15:Room
                                10:4:45:FaceNum
                                10:14:6:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:15:Room
                                10:4:30:FaceNum
                                10:14:6:Texture
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MainGateOpening:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:17:Object1
                                                06:qObjSavedHandle:Object2
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:20.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:88:Object1
                                        10:1:0:89:Object2
                                        10:6:1.000000:Lifetime
                                        10:6:1.000000:Thickness
                                        10:4:3:NumTiles
                                        10:14:7:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:90:Object1
                                        10:1:0:91:Object2
                                        10:6:1.000000:Lifetime
                                        10:6:1.000000:Thickness
                                        10:4:3:NumTiles
                                        10:14:7:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:92:Object1
                                        10:1:0:93:Object2
                                        10:6:1.000000:Lifetime
                                        10:6:1.000000:Thickness
                                        10:4:3:NumTiles
                                        10:14:7:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:94:Object1
                                        10:1:0:95:Object2
                                        10:6:1.000000:Lifetime
                                        10:6:1.000000:Thickness
                                        10:4:3:NumTiles
                                        10:14:7:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:96:Object1
                                        10:1:0:97:Object2
                                        10:6:1.000000:Lifetime
                                        10:6:1.000000:Thickness
                                        10:4:3:NumTiles
                                        10:14:7:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:98:Object1
                                        10:1:0:99:Object2
                                        10:6:1.000000:Lifetime
                                        10:6:1.000000:Thickness
                                        10:4:3:NumTiles
                                        10:14:7:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:1.000000:Time
                                        10:10:0:1:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:3:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:15:Room
                                        10:4:45:FaceNum
                                        10:14:8:Texture
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:15:Room
                                        10:4:30:FaceNum
                                        10:14:8:Texture
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ScanStarted:Message
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:Time
                                        10:10:0:2:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Reset Scan Process
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
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:4:45:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:4:30:FaceNum
                        10:14:9:Texture
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Alert Gate Security
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
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:4:100:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:4:80:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:4:45:FaceNum
                        10:14:10:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:4:30:FaceNum
                        10:14:10:Texture
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:78:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:79:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalCompleted:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:3:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:GateSecurityAlerted:Message
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:18:0:2:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:4:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:17:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Tracker 01 Was Attacked
        $$CHILD_BLOCK_START
        01:1:78
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Tracker 02 Was Attacked
        $$CHILD_BLOCK_START
        01:1:79
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Main Gate Guard 1 Was Attacked
        $$CHILD_BLOCK_START
        01:1:15
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Main Gate Guard 2 Was Attacked
        $$CHILD_BLOCK_START
        01:1:16
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Gate Monitor 1 Hit
        $$CHILD_BLOCK_START
        01:0:3
        02:1
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
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:4:1:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
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
                                10:6:2.000000:Literal
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MainGateOpening:Message
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:4:1:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Gate Monitor 2 Hit
        $$CHILD_BLOCK_START
        01:0:4
        02:1
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
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:4:2:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
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
                                10:6:2.000000:Literal
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MainGateOpening:Message
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:4:2:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Check Tracker Children for Damage
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:5:0:Bool
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                06:qObjShieldsOriginal:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:0:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:5:0:Bool
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                06:qObjShieldsOriginal:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:5:0:Bool
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                06:qObjShieldsOriginal:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:4:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:5:0:Bool
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:4:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                06:qObjShieldsOriginal:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:4:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.500000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Entered Main Base
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:4:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:4:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:18:0:4:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Entered Weapon Check Point
        $$CHILD_BLOCK_START
        01:0:6
        02:1
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:0:Bool
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:WpnCheckEntered:Message
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Do Weapon Check Sequence
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
                                10:10:0:5:TimerID
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
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
                                                10:10:0:4:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qPlayerClosest:Object
                                                $$CHILD_BLOCK_START
                                                10:1:0:18:Object
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        10:10:0:5:SavedObjectSlot
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
                                                10:6:20.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aRoomSetFaceTexture
                                                $$CHILD_BLOCK_START
                                                10:2:0:Room
                                                10:4:1:FaceNum
                                                10:14:8:Texture
                                                $$CHILD_BLOCK_END
                                        08:aRoomSetFaceTexture
                                                $$CHILD_BLOCK_START
                                                10:2:0:Room
                                                10:4:2:FaceNum
                                                10:14:8:Texture
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlaySteaming
                                                $$CHILD_BLOCK_START
                                                10:19:3:Sound
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:WeaponCheckAborted:Message
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        08:aAISetMaxSpeed
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:6:13.000000:MaxSpeed
                                                $$CHILD_BLOCK_END
                                        08:aPortalRenderSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Enable/Disable
                                                10:4:0:PortalNum
                                                10:2:0:Room
                                                10:5:1:DoublesidedFlag
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.100000:Time
                                                10:10:0:8:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.500000:Time
                                                10:10:0:5:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                06:qPlayerClosest:Object
                                        $$CHILD_BLOCK_START
                                        10:1:0:18:Object
                                        10:10:0:3:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:5:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:15.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:1:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:WpnCheckStarted:Message
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        10:4:1:FaceNum
                                        10:14:5:Texture
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        10:4:2:FaceNum
                                        10:14:5:Texture
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:17:0:0:Matcen
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:0:Matcen
                                        $$CHILD_BLOCK_END
                                08:aPortalRenderSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:4:0:PortalNum
                                        10:2:0:Room
                                        10:5:1:DoublesidedFlag
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:2.000000:Time
                                        10:10:0:5:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:0.500000:Time
                                        10:10:0:5:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Matcen Produced Weapon Check Guard
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:6:AIModeType
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:10.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aPhysFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:58720256:PhysicsFlags
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:32:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:6:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Weapon Guard Entered
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:WeaponsRemoved:Message
                        $$CHILD_BLOCK_END
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:48:Child
                        10:4:0:ChildPoint
                        10:1:1:-1:Parent
                        10:4:0:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                08:aStripWeaponsEnergyFromAll
                08:aRemovePowerupsInRoom
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:4:14:StartFrame
                        10:4:26:EndFrame
                        10:6:0.800000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Send Weapon Guard Home
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:6:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:9:StartFrame
                        10:4:14:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:6:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:33:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Weapon Guard Left
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:48:Object
                        $$CHILD_BLOCK_END
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:4:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        10:4:1:FaceNum
                                        10:14:6:Texture
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        10:4:2:FaceNum
                                        10:14:6:Texture
                                        $$CHILD_BLOCK_END
                                08:aPortalRenderSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:4:3:PortalNum
                                        10:2:0:Room
                                        10:5:1:DoublesidedFlag
                                        $$CHILD_BLOCK_END
                                08:aPortalRenderSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:4:0:PortalNum
                                        10:2:0:Room
                                        10:5:1:DoublesidedFlag
                                        $$CHILD_BLOCK_END
                                08:aPortalRenderSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:4:0:PortalNum
                                        10:2:0:Room
                                        10:5:0:DoublesidedFlag
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:WeaponsChecked:Message
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:5:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        10:4:1:FaceNum
                                        10:14:9:Texture
                                        $$CHILD_BLOCK_END
                                08:aRoomSetFaceTexture
                                        $$CHILD_BLOCK_START
                                        10:2:0:Room
                                        10:4:2:FaceNum
                                        10:14:9:Texture
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:0.100000:Time
                                        10:10:0:5:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Check if Weapon Guard has been Shot
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
                                        10:10:0:5:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        06:qObjShieldsOriginal:Float
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:4:1:FaceNum
                                10:14:10:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:4:2:FaceNum
                                10:14:10:Texture
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:Ghost/Unghost
                                10:1:0:48:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:Red
                                10:6:1.000000:Green
                                10:6:0.000000:Blue
                                10:6:1000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:0:Room
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:Red
                                10:6:1.000000:Green
                                10:6:0.000000:Blue
                                10:6:200.000000:Depth
                                10:6:6.000000:Time
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:WeaponGuardHit:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:18:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.250000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Do Weapon Check Threat Sequence
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
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:20.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:10.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
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
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRemovePowerupsInRoom
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:Red
                                10:6:1.000000:Green
                                10:6:0.000000:Blue
                                10:6:1000.000000:Depth
                                10:6:2.500000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:7:TimerID
                                $$CHILD_BLOCK_END
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
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRemovePowerupsInRoom
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:2:0:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:4:1:FaceNum
                                10:14:9:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:4:2:FaceNum
                                10:14:9:Texture
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:0:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:5:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Crate Stack Was Destroyed
        $$CHILD_BLOCK_START
        01:1:100
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalEnabled:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:6:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundBackDoor:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalCompleted:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:7:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:7:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:8:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:9:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Turret Control Destroyed
        $$CHILD_BLOCK_START
        01:1:66
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TurretControlDown:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:10:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Worker Screwup Trigger
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Do Worker Screwup
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:63:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:30.000000:Number
                                10:1:0:101:Object
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.500000:Time
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:63:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:50.000000:Number
                                10:1:0:101:Object
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:73:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:73:Object
                                10:16:34:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:2:Sound
                                10:1:0:73:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:64:Object
                                10:6:40.000000:SparkRate
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:102:Object
                                10:4:-1:GunNum
                                10:10:0:0:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:3.500000:SpewLife
                                10:6:2.000000:BlobSize
                                10:6:17.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.500000:Time
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:63:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:64:Object
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:63:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:64:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:63:Object
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:73:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:WorkerMessage:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:63:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:74:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:74:Object
                                10:16:35:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:2:Sound
                                10:1:0:74:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:50.000000:Number
                                10:1:0:101:Object
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:General Landing Trigger
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:Left Hangar Area
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Do General Landing Sequence
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
                                        10:11:65:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:36:CameraPath
                                10:8:Empty:Text
                                10:1:0:65:Target
                                10:6:17.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:65:Object
                                10:6:15.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:65:Object
                                10:16:37:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:27:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:15:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:65:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:3:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:15:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:General Flew In
        $$CHILD_BLOCK_START
        01:1:65
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:27:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:2:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:3:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.800000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:3:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:6:5.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:16:38:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:26:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:10:0:3:GoalPriority
                        10:6:0.000000:distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:General Landed
        $$CHILD_BLOCK_START
        01:1:65
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:26:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Destroy General Sequence
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
                                        10:11:68:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:6:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:53:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:54:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:1024:AIFlags
                                10:1:0:54:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:536870912:AIFlags
                                10:1:0:53:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:536870912:AIFlags
                                10:1:0:54:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:54:Object
                                10:1:0:71:Target
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:53:Object
                                10:1:0:49:Target
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:16:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                10:9:0.500000:Position
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
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:71:Object
                                10:6:50.000000:SparkRate
                                10:6:2.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:49:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:51:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:52:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:50:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:51:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:52:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:49:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:53:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:54:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:54:Object
                                10:1:0:65:Target
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:53:Object
                                10:1:0:49:Target
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:49:Object
                                10:1:0:54:Target
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:52:Object
                                10:1:0:54:Target
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object
                                10:1:0:53:Target
                                $$CHILD_BLOCK_END
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:0:51:Object
                                10:1:0:53:Target
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:128:AIFlags
                                10:1:0:49:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:128:AIFlags
                                10:1:0:50:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:128:AIFlags
                                10:1:0:51:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:128:AIFlags
                                10:1:0:52:Object
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:16:TimerID
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
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:71:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:71:Object
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:1024:AIFlags
                                10:1:0:54:Object
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:54:Object
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:65:Object
                                10:6:50.000000:SparkRate
                                10:6:0.200000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.200000:Time
                                10:10:0:16:TimerID
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
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:65:Object
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:67:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:67:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:65:Object
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
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.400000:Time
                                10:10:0:16:TimerID
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
                                10:4:4:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:72:Object
                                $$CHILD_BLOCK_END
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                10:1:0:72:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:General is Dead
        $$CHILD_BLOCK_START
        01:1:65
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GeneralDead:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:11:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Player picked up Data Cartridge
        $$CHILD_BLOCK_START
        01:1:103
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:24:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DataCartridgeName:Message
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:8:DataCartridgeName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:12:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Player picked up Infected Data Cartridge
        $$CHILD_BLOCK_START
        01:1:81
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:25:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:InfectedDataCartridgeName:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:1:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aAddObjectToInventoryNamed
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:1:1:-1:PlayerObject
                                10:8:InfectedDataCartridgeName:ItemName
                                10:5:0:Spewable
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Player Used Data Cartridge
        $$CHILD_BLOCK_START
        01:1:103
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DataCartridgeUsed:Message
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:8:DataCartridgeName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Player Used Infected Data Cartridge
        $$CHILD_BLOCK_START
        01:1:81
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
                                06:qObjGetDistance:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object1
                                        10:1:0:104:Object2
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:40.000000:Literal
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
                                                10:10:0:24:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:13:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:25:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:InfectedDataPlaced:Message
                                        $$CHILD_BLOCK_END
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:104:Object
                                        $$CHILD_BLOCK_END
                                08:aMoveObjectToPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:1.000000:Time
                                        10:10:0:19:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:DataCartridgeStillThere:Message
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventoryNamed
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:1:1:-1:PlayerObject
                                        10:8:InfectedDataCartridgeName:ItemName
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TooFarFromDataPosition:Message
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aAddObjectToInventoryNamed
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:1:1:-1:PlayerObject
                                10:8:InfectedDataCartridgeName:ItemName
                                10:5:0:Spewable
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Do Self-Destruct Sequence
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
                                        10:11:89:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Number
                                10:1:0:81:Object
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:14:Object
                                10:4:0:StartFrame
                                10:4:15:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:X
                                10:6:-1.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:1:Lock/Unlock
                                10:0:0:4:DoorName
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:17:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:5000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:18:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:5000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:5000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:20:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:5000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:21:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:5000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:5000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:17:Room
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:18:Room
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:19:Room
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:20:Room
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:21:Room
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:8:Room
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:17:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:350.000000:Depth
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:18:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:350.000000:Depth
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:350.000000:Depth
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:20:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:350.000000:Depth
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:21:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:350.000000:Depth
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.250000:Red
                                10:6:0.500000:Green
                                10:6:0.800000:Blue
                                10:6:350.000000:Depth
                                10:6:3.000000:Time
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:105:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:6.000000:BlobSize
                                10:6:35.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:106:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:6.000000:BlobSize
                                10:6:35.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:107:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:6.000000:BlobSize
                                10:6:35.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:108:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:6.000000:BlobSize
                                10:6:35.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:7:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:39:Object
                                10:6:77.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:40:Object
                                10:6:77.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:39:Object1
                                10:1:0:40:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:12.000000:Thickness
                                10:4:3:NumTiles
                                10:14:11:Texture
                                10:6:0.300000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:65536:PhysicsFlags
                                10:1:0:39:Object
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:65536:PhysicsFlags
                                10:1:0:40:Object
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:39:Object
                                10:16:39:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:31:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:40:Object
                                10:16:40:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:31:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:39:Object
                                10:10:0:3:GoalPriority
                                10:6:10.000000:distance
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:40:Object
                                10:10:0:3:GoalPriority
                                10:6:10.000000:distance
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:4:Sound
                                10:1:0:40:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:19:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:89:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:41:Object
                                10:6:71.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:42:Object
                                10:6:71.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:41:Object1
                                10:1:0:42:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:12.000000:Thickness
                                10:4:3:NumTiles
                                10:14:11:Texture
                                10:6:0.300000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:65536:PhysicsFlags
                                10:1:0:41:Object
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:65536:PhysicsFlags
                                10:1:0:42:Object
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:41:Object
                                10:16:41:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:32:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:42:Object
                                10:16:42:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:32:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:41:Object
                                10:10:0:3:GoalPriority
                                10:6:10.000000:distance
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:42:Object
                                10:10:0:3:GoalPriority
                                10:6:10.000000:distance
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:4:Sound
                                10:1:0:42:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:19:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:89:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:43:Object
                                10:6:65.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aAISetMaxSpeed
                                $$CHILD_BLOCK_START
                                10:1:0:44:Object
                                10:6:65.000000:MaxSpeed
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:43:Object1
                                10:1:0:44:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:12.000000:Thickness
                                10:4:3:NumTiles
                                10:14:11:Texture
                                10:6:0.300000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:65536:PhysicsFlags
                                10:1:0:43:Object
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:1:Set/Clear
                                10:15:65536:PhysicsFlags
                                10:1:0:44:Object
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:43:Object
                                10:16:43:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:33:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:44:Object
                                10:16:44:Path
                                10:15:2228480:AIGoalFlags
                                10:10:0:33:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:43:Object
                                10:10:0:3:GoalPriority
                                10:6:10.000000:distance
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:44:Object
                                10:10:0:3:GoalPriority
                                10:6:10.000000:distance
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:4:Sound
                                10:1:0:44:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:17:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:18:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:20:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:21:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:1.000000:Damage
                                10:10:0:1:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:30.000000:Number
                                10:1:0:81:Object
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:14:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:15:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EscapeTime:Message
                                $$CHILD_BLOCK_END
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:3:Region
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Restart End Beam A
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:31:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:16:39:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:31:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        10:16:40:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:31:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:10:0:3:GoalPriority
                        10:6:10.000000:distance
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        10:10:0:3:GoalPriority
                        10:6:10.000000:distance
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Number
                        10:1:0:81:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Restart End Beam B
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:32:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:16:41:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:32:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        10:16:42:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:32:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:10:0:3:GoalPriority
                        10:6:10.000000:distance
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        10:10:0:3:GoalPriority
                        10:6:10.000000:distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Restart End Beam C
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:33:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:113:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:16:43:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:33:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:16:44:Path
                        10:15:2228480:AIGoalFlags
                        10:10:0:33:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:10:0:3:GoalPriority
                        10:6:10.000000:distance
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:10:0:3:GoalPriority
                        10:6:10.000000:distance
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Number
                        10:1:0:81:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Heavy Trooper 1 Trigger Hit
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:45:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:16:45:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:16:46:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:16:47:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:End Trooper Trigger Hit
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EndGuards:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:47:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:16:48:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:17:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:End Trooper Break Out
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:46:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:16:49:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:16:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:End Trooper 1 Killed
        $$CHILD_BLOCK_START
        01:1:46
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:16:LevelGoal
                        10:4:1:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:5:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:5:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ExitDoor:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:16:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:4:Region
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:End Trooper 2 Killed
        $$CHILD_BLOCK_START
        01:1:47
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:16:LevelGoal
                        10:4:2:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:5:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:5:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ExitDoor:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:16:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:4:Region
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Armory Guard Trigger Hit
        $$CHILD_BLOCK_START
        01:0:12
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
                        10:6:0.100000:Time
                        10:10:0:18:TimerID
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:117:Object
                        10:16:50:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:118:Object
                        10:16:51:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:8:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Activate the Armory Guard Matcen
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Send Armory Guard To Armory
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:52:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:28:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:120.000000:LowerLimit
                                10:6:180.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:18:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Armory Guard Got To Door
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:28:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:6:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:53:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:29:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:8.000000:Time
                        10:10:0:22:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Armory Guard Went Through Door
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:29:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:6:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:54:Path
                        10:15:1048836:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:15.000000:LowerLimit
                                10:6:30.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:21:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:Make Armory Guard Leave
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:16:54:Path
                                10:15:16781568:AIGoalFlags
                                10:10:0:34:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Armory Guard Got To Door Again
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:34:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:6:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:8.000000:Time
                        10:10:0:22:TimerID
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:53:Path
                        10:15:16781568:AIGoalFlags
                        10:10:0:35:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:Armory Guard Went Through Door Again
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:35:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:6:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:52:Path
                        10:15:16781568:AIGoalFlags
                        10:10:0:36:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:Delete Armory Guard
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:36:GoalID
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
00:99:Close Armory Door
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
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:6:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Armory Door Switch Hit
        $$CHILD_BLOCK_START
        01:1:119
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
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ArmoryDoorUnlocked:Message
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
                        10:12:5:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Central FF Switch Hit
        $$CHILD_BLOCK_START
        01:1:120
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:2:PortalNum
                        10:2:22:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CentralFFDown:Message
                        $$CHILD_BLOCK_END
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
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:17:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:121:Object
                        10:16:55:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Stormtrooper w/Claw Produced
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:16.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:56:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:30:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Heavytrooper w/Claw Produced
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:16.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:57:Path
                        10:15:1048832:AIGoalFlags
                        10:10:0:30:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Delete Stormtrooper and Heavy Trooper w/Claw
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:30:GoalID
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
00:85:Escape Trigger Hit
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
                08:aEnableShip
                        $$CHILD_BLOCK_START
                        10:13:0:Ship
                        $$CHILD_BLOCK_END
                08:aDisableShip
                        $$CHILD_BLOCK_START
                        10:13:1:Ship
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:58:CameraPath
                        10:16:59:PlayerPath
                        10:6:5.000000:Time
                        10:8:Empty:Text
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:15:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Update Data Cartridge Effects
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
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:24:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:25:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
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
                                                10:10:0:25:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        10:1:0:81:Object
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        10:1:0:103:Object
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:122:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.500000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:3:NumTiles
                                10:14:11:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:123:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.500000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:3:NumTiles
                                10:14:11:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:124:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.500000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:3:NumTiles
                                10:14:11:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.500000:Time
                        10:10:0:20:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:Check Restricted Access Entrance Camera
        $$CHILD_BLOCK_START
        01:1:125
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
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
00:101:Check Restricted Hall A Camera 1
        $$CHILD_BLOCK_START
        01:1:126
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SecCamSpottedUs:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:55:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:8:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:Res Hall A Turret 1 Hit
        $$CHILD_BLOCK_START
        01:1:55
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:55:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:Check Restricted Hall A Camera 2
        $$CHILD_BLOCK_START
        01:1:127
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SecCamSpottedUs:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:56:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:9:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:Res Hall A Turret 2 Hit
        $$CHILD_BLOCK_START
        01:1:56
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:56:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:Check Armory Camera
        $$CHILD_BLOCK_START
        01:1:128
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SecCamSpottedUs:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:10:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:Armory Turret Hit
        $$CHILD_BLOCK_START
        01:1:57
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:57:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:Check Res Hall C Camera
        $$CHILD_BLOCK_START
        01:1:129
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SecCamSpottedUs:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:58:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:11:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:Res Hall C Turret Hit
        $$CHILD_BLOCK_START
        01:1:58
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:58:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:Check Hall C Camera 1
        $$CHILD_BLOCK_START
        01:1:130
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SecCamSpottedUs:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:59:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:12:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:Hall C Turret 1 Hit
        $$CHILD_BLOCK_START
        01:1:59
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:59:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:Check Hall C Camera 2
        $$CHILD_BLOCK_START
        01:1:131
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qSecurityCameraAlerted:Bool
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Security Camera
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SecCamSpottedUs:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:60:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:13:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:Hall C Turret 2 Hit
        $$CHILD_BLOCK_START
        01:1:60
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:60:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:Res Area Entrance Door Hit
        $$CHILD_BLOCK_START
        01:1:132
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:9:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:6:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:6:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ResAreaEntrance:Message
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:6:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:18:0:8:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:9:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:Crate Room Trigger Hit
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
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:6:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:6:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:7:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:NeedAWeapon:Message
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:7:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Super Laser Picked Up
        $$CHILD_BLOCK_START
        01:1:133
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
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:Entered Res Area
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:9:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:134:Object
                        10:16:60:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:135:Object
                        10:16:61:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:Left Res Area
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
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:Laser Room 1 Matcen Path
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:62:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:Laser Room 2 Matcen 1 Path
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:63:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:Laser Room 2 Matcen 2 Path
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:0:Matcen
                        07:1:0
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:64:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:Do Welder Sparks
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
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:1.000000:LowerLimit
                                        10:6:100.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:50.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:4:Object
                                10:4:0:Gunpoint
                                $$CHILD_BLOCK_END
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:2:Object
                                10:4:0:Gunpoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Float
                                        $$CHILD_BLOCK_START
                                        10:6:1.000000:LowerLimit
                                        10:6:100.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:50.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:5:Object
                                10:4:0:Gunpoint
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
                                                10:10:0:26:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRandomValue:Float
                                                $$CHILD_BLOCK_START
                                                10:6:1.000000:LowerLimit
                                                10:6:100.000000:UpperLimit
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:50.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:76:Object
                                10:4:0:Gunpoint
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:0.400000:LowerLimit
                                10:6:1.200000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:23:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:Welder Finished Path A
        $$CHILD_BLOCK_START
        01:1:76
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:37:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:20.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:25:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:Welder Finished Path B
        $$CHILD_BLOCK_START
        01:1:76
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:1:0:GoalID
                        07:1:0
                        10:10:0:38:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:20.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:24:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:124:Send Welder To Ship A
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:16:3:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:37:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:Send Welder To Ship B
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:16:65:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:38:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
