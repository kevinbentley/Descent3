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
// Filename:	Level10.cpp
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

#define ID_CUSTOM_OBJECT_2042 0x001
#define ID_CUSTOM_OBJECT_10A3 0x002
#define ID_CUSTOM_OBJECT_094B 0x003
#define ID_CUSTOM_OBJECT_0945 0x004
#define ID_CUSTOM_OBJECT_113E 0x005
#define ID_CUSTOM_OBJECT_193F 0x006
#define ID_CUSTOM_OBJECT_2140 0x007
#define ID_CUSTOM_OBJECT_0875 0x008
#define ID_CUSTOM_OBJECT_0877 0x009
#define ID_CUSTOM_OBJECT_105C 0x00a
#define ID_CUSTOM_OBJECT_0878 0x00b
#define ID_CUSTOM_OBJECT_28BA 0x00c
#define ID_CUSTOM_OBJECT_2133 0x00d
#define ID_CUSTOM_OBJECT_1139 0x00e
#define ID_CUSTOM_OBJECT_098A 0x00f
#define ID_CUSTOM_OBJECT_08AA 0x010
#define ID_CUSTOM_OBJECT_18BF 0x011
#define ID_CUSTOM_OBJECT_10C0 0x012
#define ID_CUSTOM_OBJECT_2904 0x013
#define ID_CUSTOM_OBJECT_3088 0x014
#define ID_CUSTOM_OBJECT_2105 0x015
#define ID_CUSTOM_OBJECT_3092 0x016
#define ID_CUSTOM_OBJECT_187C 0x017
#define ID_CUSTOM_OBJECT_10FA 0x018
#define ID_CUSTOM_OBJECT_0903 0x019
#define ID_CUSTOM_OBJECT_1902 0x01a
#define ID_CUSTOM_OBJECT_4047 0x01b
#define ID_CUSTOM_OBJECT_289B 0x01c
#define ID_CUSTOM_OBJECT_3849 0x01d
#define ID_CUSTOM_OBJECT_184B 0x01e
#define ID_CUSTOM_OBJECT_204A 0x01f
#define ID_CUSTOM_OBJECT_2064 0x020
#define ID_CUSTOM_OBJECT_1065 0x021
#define ID_CUSTOM_OBJECT_2063 0x022
#define ID_CUSTOM_OBJECT_5843 0x023
#define ID_CUSTOM_OBJECT_1095 0x024
#define ID_CUSTOM_OBJECT_1094 0x025
#define ID_CUSTOM_OBJECT_1080 0x026
#define ID_CUSTOM_OBJECT_187F 0x027
#define ID_CUSTOM_OBJECT_501A 0x028
#define ID_CUSTOM_OBJECT_D80D 0x029
#define ID_CUSTOM_OBJECT_18A1 0x02a
#define ID_CUSTOM_OBJECT_208B 0x02b
#define ID_CUSTOM_OBJECT_2074 0x02c
#define ID_CUSTOM_OBJECT_203D 0x02d
#define ID_CUSTOM_OBJECT_11B1 0x02e
#define ID_CUSTOM_OBJECT_3898 0x02f
#define ID_CUSTOM_OBJECT_303C 0x030
#define ID_CUSTOM_OBJECT_2090 0x031
#define ID_CUSTOM_OBJECT_09D4 0x032
#define ID_CUSTOM_OBJECT_1050 0x033
#define ID_CUSTOM_OBJECT_2044 0x034
#define ID_CUSTOM_OBJECT_1845 0x035
#define ID_CUSTOM_OBJECT_1058 0x036
#define ID_CUSTOM_OBJECT_09A3 0x037
#define ID_CUSTOM_OBJECT_11AF 0x038
#define ID_CUSTOM_OBJECT_49B0 0x039
#define ID_CUSTOM_OBJECT_11D2 0x03a
#define ID_CUSTOM_OBJECT_09D5 0x03b
#define ID_CUSTOM_OBJECT_18A5 0x03c
#define ID_CUSTOM_OBJECT_10FB 0x03d
#define ID_CUSTOM_OBJECT_19A2 0x03e
#define ID_CUSTOM_OBJECT_09A4 0x03f
#define ID_CUSTOM_OBJECT_09A5 0x040
#define ID_CUSTOM_OBJECT_09A6 0x041
#define ID_CUSTOM_OBJECT_09A1 0x042
#define ID_CUSTOM_OBJECT_20FD 0x043
#define ID_CUSTOM_OBJECT_187E 0x044
#define ID_CUSTOM_OBJECT_987D 0x045
#define ID_CUSTOM_OBJECT_09AA 0x046
#define ID_CUSTOM_OBJECT_0816 0x047

#define ID_TRIGGER_0007 0x048
#define ID_TRIGGER_000B 0x049
#define ID_TRIGGER_0008 0x04a
#define ID_TRIGGER_0004 0x04b
#define ID_TRIGGER_0002 0x04c
#define ID_TRIGGER_0009 0x04d
#define ID_TRIGGER_0006 0x04e
#define ID_TRIGGER_0003 0x04f
#define ID_TRIGGER_0001 0x050
#define ID_TRIGGER_0005 0x051
#define ID_TRIGGER_000A 0x052
#define ID_TRIGGER_0013 0x053

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

class CustomObjectScript_2042 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10A3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_094B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0945 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_113E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_193F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2140 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0875 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0877 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_105C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0878 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_28BA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2133 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1139 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_098A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08AA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18BF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10C0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2904 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3088 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2105 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3092 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_187C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0903 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1902 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_4047 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_289B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3849 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_184B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_204A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2064 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1065 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2063 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_5843 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1095 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1094 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1080 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_187F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_501A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_D80D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_208B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2074 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_203D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11B1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3898 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_303C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2090 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09D4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1050 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2044 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1845 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1058 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11AF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_49B0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11D2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09D5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18A5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10FB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19A2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_187E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_987D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09AA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0816 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0001 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_148 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_143 = 0;
static int ScriptActionCtr_144 = 0;
static int ScriptActionCtr_145 = 0;
static int ScriptActionCtr_146 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_125 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_074 = 0;
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
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_129 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_130 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_131 = 0;
static int ScriptActionCtr_132 = 0;
static int ScriptActionCtr_133 = 0;
static int ScriptActionCtr_134 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_135 = 0;
static int ScriptActionCtr_136 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_137 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_138 = 0;
static int ScriptActionCtr_139 = 0;
static int ScriptActionCtr_140 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_141 = 0;
static int ScriptActionCtr_142 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_147 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_148 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_143 = 0;
  ScriptActionCtr_144 = 0;
  ScriptActionCtr_145 = 0;
  ScriptActionCtr_146 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_125 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_074 = 0;
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
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_129 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_130 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_131 = 0;
  ScriptActionCtr_132 = 0;
  ScriptActionCtr_133 = 0;
  ScriptActionCtr_134 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_135 = 0;
  ScriptActionCtr_136 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_137 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_138 = 0;
  ScriptActionCtr_139 = 0;
  ScriptActionCtr_140 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_141 = 0;
  ScriptActionCtr_142 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_147 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_148, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_143, file_ptr);
  File_WriteInt(ScriptActionCtr_144, file_ptr);
  File_WriteInt(ScriptActionCtr_145, file_ptr);
  File_WriteInt(ScriptActionCtr_146, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
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
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_129, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_130, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
  File_WriteInt(ScriptActionCtr_132, file_ptr);
  File_WriteInt(ScriptActionCtr_133, file_ptr);
  File_WriteInt(ScriptActionCtr_134, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_135, file_ptr);
  File_WriteInt(ScriptActionCtr_136, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_137, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_138, file_ptr);
  File_WriteInt(ScriptActionCtr_139, file_ptr);
  File_WriteInt(ScriptActionCtr_140, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_141, file_ptr);
  File_WriteInt(ScriptActionCtr_142, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_147, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_148 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_143 = File_ReadInt(file_ptr);
  ScriptActionCtr_144 = File_ReadInt(file_ptr);
  ScriptActionCtr_145 = File_ReadInt(file_ptr);
  ScriptActionCtr_146 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_129 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_130 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
  ScriptActionCtr_132 = File_ReadInt(file_ptr);
  ScriptActionCtr_133 = File_ReadInt(file_ptr);
  ScriptActionCtr_134 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_135 = File_ReadInt(file_ptr);
  ScriptActionCtr_136 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_137 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_138 = File_ReadInt(file_ptr);
  ScriptActionCtr_139 = File_ReadInt(file_ptr);
  ScriptActionCtr_140 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_141 = File_ReadInt(file_ptr);
  ScriptActionCtr_142 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_147 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:RightArm
2:Outside
3:MainHub
4:MidSection
5:LowerEnd
$$END
*/

/*
$$ACTION
Custom
Initialize base alert display
aInitBaseAlertDisplay
Intialize base alert display
  Initializes the HUD base alert display

$$END
*/
void aInitBaseAlertDisplay() {}

/*
$$ACTION
Custom
Update base alert display with [s:Message] at [i:AlertLevel]
aUpdateBaseAlertDisplay
Update base alert display
  Updates the HUD base alert display

$$END
*/
void aUpdateBaseAlertDisplay(const char *text, int level) {
  msafe_struct mstruct;

  mstruct.color = GR_RGB(0, 255, 0);
  sprintf(mstruct.message, text, level);
  MSafe_CallFunction(MSAFE_MISC_UPDATE_HUD_ITEM, &mstruct);
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

#define NUM_DOOR_NAMES 2
static const char *const Door_names[NUM_DOOR_NAMES] = {"Datavault Door", "Base Access Door"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 111
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Memory Plasma Blob",
                                                           "Vault HangTurr1",
                                                           "Vault HangTurr2",
                                                           "Vault Turr3",
                                                           "Vault Turr4",
                                                           "Hanger Swatter1",
                                                           "Hanger Swatter2",
                                                           "Hanger Swatter3",
                                                           "Hanger Swatter4",
                                                           "HoodReinforcementA",
                                                           "HoodReinforcementB",
                                                           "HoodAmbushGT",
                                                           "HoodAmbushCB",
                                                           "HoodAmbushDV",
                                                           "CanyonAmbushA",
                                                           "CanyonAmbushB",
                                                           "CanyonAmbushC",
                                                           "PitAmbushA",
                                                           "PitAmbushB",
                                                           "PitAmbushC",
                                                           "PrepRoomTurret1",
                                                           "MemPlasmaTurret1",
                                                           "MemPlasmaTurret2",
                                                           "MemPlasmaTurret3",
                                                           "MemPlasmaTurret4",
                                                           "CorridorTurret1",
                                                           "CorridorTurret2",
                                                           "Substation1Turret1",
                                                           "AuxillaryTurret1",
                                                           "AuxillaryTurret2",
                                                           "AuxillaryTurret3",
                                                           "ControlTurret1",
                                                           "ControlTurret2",
                                                           "InitializationHub",
                                                           "DataUplinkCenter",
                                                           "TankerLandPoint",
                                                           "Nano Cooker Spew",
                                                           "Memory Spew",
                                                           "Interface Spew",
                                                           "Interface Dongle",
                                                           "Fuel Tanker",
                                                           "Hood Patrol1",
                                                           "SkyPatrol2",
                                                           "TrappedMega",
                                                           "DVPatrolA",
                                                           "DVPatrolB",
                                                           "DVGuard",
                                                           "DVGuardBeacon",
                                                           "HoodAmbushDVDest",
                                                           "BigGunCam",
                                                           "BigGunTargetCam",
                                                           "JuggGuard",
                                                           "JuggAlertBeacon",
                                                           "HoodReinforceADest",
                                                           "CanyonGuard",
                                                           "CmdBaseGuard",
                                                           "BaseAmbushA",
                                                           "BaseAmbushB",
                                                           "CmdBaseBeacon",
                                                           "HoodAmbushCBDest",
                                                           "TankPatrol",
                                                           "D1 Patrol Leader",
                                                           "D1 Ground Guard",
                                                           "MineGuardBeacon",
                                                           "Hanger Guard",
                                                           "HangarGuardBeacon",
                                                           "HoodReinforceBDest",
                                                           "Interface Power Sw",
                                                           "Foyer Matcen1 Sw",
                                                           "Prep Matcen1 Sw",
                                                           "Memory Plasma Swit",
                                                           "Aux Matcen1 Sw",
                                                           "HD Matcen1 Sw",
                                                           "Uplink Plasma Swit",
                                                           "HD Matcen2 Sw",
                                                           "Aux Matcen2 Sw",
                                                           "Foyer Matcen2 Sw",
                                                           "Prep Matcen2 Sw",
                                                           "CrashedCargoShip",
                                                           "Vault Key",
                                                           "Hanger Door Switch",
                                                           "Hanger Data Link",
                                                           "MemPlasmaDataArm",
                                                           "UplinkControlDataA",
                                                           "UplinkCenterDataAr",
                                                           "Prep Room DataArm",
                                                           "PrepInitCamA",
                                                           "PrepInitCamB",
                                                           "PrepInitCamC",
                                                           "PrepInitCamD",
                                                           "Nano Plasma Switch",
                                                           "Interface Switch",
                                                           "Waypoint2Cam",
                                                           "Uplink Upper Cam",
                                                           "Uplink Lower Cam",
                                                           "UplinkCamA",
                                                           "UplinkCamB",
                                                           "UplinkCamC",
                                                           "UplinkCamD",
                                                           "Hanger Wall Cam",
                                                           "Prep Room Cam",
                                                           "Mem Plasma Cam",
                                                           "Corridor Cam",
                                                           "Substation 1 Cam",
                                                           "Auxillary Cam",
                                                           "Control Cam",
                                                           "Camera Monitor",
                                                           "Crashed Ship Log",
                                                           "Meteor1",
                                                           "Meteor1Explosion",
                                                           "A Door FoyerMatcen"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 19
static const char *const Room_names[NUM_ROOM_NAMES] = {"Hanger Portal",      "Foyer",
                                                       "DataStow Room",      "Interface Obs Acce",
                                                       "Main Hall",          "Main Hanger",
                                                       "Prep Room",          "Mem Plasma Room",
                                                       "Mem Plasma Room 2",  "Maintenance Room",
                                                       "Mem Plasma Doorway", "Differential Room",
                                                       "Corridor Cam Room",  "Substation1",
                                                       "Workstation Access", "Auxillary Control",
                                                       "Interface Control",  "Data Uplink Room",
                                                       "Control Door Room"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 12
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "MMainHub-2",    "MRightArm-2",   "MRightArm-1",   "MLowerEnd-2", "MLowerEnd-1", "MMidSection-4",
    "MMidSection-3", "MMidSection-2", "MMidSection-1", "MMainHub-1",  "MOutside-2",  "MOutside1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 9
static const char *const Sound_names[NUM_SOUND_NAMES] = {"PlayerSpotted",     "BaseAlertedSiren",   "AmbSwitch11",
                                                         "Lev10Laser",        "AmbSwitch31",        "Powerup pickup",
                                                         "MemPlasmaChargeOn", "MemPlasmaChargeOff", "HudMessage"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 6
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffect7", "FunkyEffect4", "FunkyEffect3",
                                                             "FunkyEffect2", "FunkyEffect5", "Lightning3"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 28
static const char *const Path_names[NUM_PATH_NAMES] = {
    "LandingCamPathA",    "LandingCamPathB",    "NewPlayerIntroCamPath", "NewPlayerIntroPath",
    "IntroLandingPath",   "IntroLandingPathB",  "Space Patrol",          "SkyPatrol2",
    "DVPatrolA",          "DVPatrolB",          "DVGuardPath",           "Jugg Alerted Path",
    "CanyonGuardStation", "CanyonGuardPath",    "CmdBaseGuardPath",      "CmdBaseDestPath",
    "TankPatrol",         "D1PatrolPath",       "D1 Ground Path A",      "D1 Ground Path B",
    "D1 Ground Path C",   "Hanger Patrol Path", "Hanger Patrol Path 2",  "PrepInitCam",
    "PlayerInitPath",     "NewUplinkCamPath",   "UplinkPlayerPath",      "Meteor1"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 20
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {
    "Central Matcen", "MemPlasmaMatcen", "Foyer Matcen1",    "Foyer Matcen2",      "HD Matcen1",
    "HD Matcen2",     "Aux Matcen1",     "Aux Matcen2",      "Prep Matcen1",       "Prep Matcen2",
    "Nano Matcen1",   "Nano Matcen2",    "Nano Matcen3",     "StorageRoomXMatcen", "BigRoomXMatcen1",
    "FoyerXMatcen",   "FoyerXMatcen2",   "MainHallXMatcen1", "MainHallXMatcen2",   "Temp Bolt"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 13
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Enable Uplink Control Power",     "Enable Memory Plasma Generation", "Activate Uplink Plasma Supply",
    "Obtain a Data Vault Key",         "Enter through the Data Vault",    "Infiltrate the Lunar Command Center",
    "Acquire a Data Interface",        "Initialize Data Interface",       "Disable Nano Plasma Defenses",
    "Activate Uplink Docking Control", "Connect to Data Uplink",          "Acquire Memory Plasma Charge",
    "Upload Virus Information"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 65
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"Empty",
                                                             "IntroText",
                                                             "ZMegaTrap",
                                                             "ZDVSpotted",
                                                             "ZDVAlerted",
                                                             "ZTurretHit",
                                                             "CannonHitPlayer",
                                                             "JuggSawPlayer",
                                                             "JuggAlertedBase",
                                                             "JuggAlertWarning",
                                                             "ZCanyonRun",
                                                             "ZCanyonAmbush",
                                                             "ZCBNoticed",
                                                             "ZCBAlerted",
                                                             "D1GuardSpotted",
                                                             "HangerGuardSpotted",
                                                             "GuardTowerAlertedHG",
                                                             "GuardTowerAlertedGG",
                                                             "BaseAlertStatus",
                                                             "BaseAlertDisplay",
                                                             "VaultKeyAcquired",
                                                             "InterfaceAcquired",
                                                             "HangerDoorUnlocked",
                                                             "HangerMsgGame",
                                                             "HangerMsgHUD",
                                                             "MemPlasmaGame",
                                                             "MemPlasmaHUD",
                                                             "UplinkControlGame",
                                                             "UplinkControlHUD",
                                                             "UplinkCenterGame",
                                                             "UplinkCenterHUD",
                                                             "InterfacePrepInstrGame",
                                                             "InterfacePrepInstHUD",
                                                             "InterfaceInitialized",
                                                             "InitInterfaceCin",
                                                             "InterfacePrepDenied",
                                                             "UplinkPlasmaOff",
                                                             "UplinkPlasmaOn",
                                                             "MemPlasmaOff",
                                                             "MemPlasmaOn",
                                                             "NanoPlasmaDefOff",
                                                             "NanoPlasmaDefOn",
                                                             "MatcenActivated",
                                                             "MatcenDeactivated",
                                                             "InterfacePowerOff",
                                                             "InterfacePowerOn",
                                                             "DataUplinkActivated",
                                                             "InterfaceHasNoPower",
                                                             "UplinkDocking",
                                                             "UplinkErrorNoChg",
                                                             "UplinkErrorNoPlasma",
                                                             "UplinkErrorNotAct",
                                                             "UplinkErrorNoInit",
                                                             "UplinkErrorNoInt",
                                                             "UplinkErrorNano",
                                                             "MemPlasmaObtained",
                                                             "MemPlasmaLost",
                                                             "UploadingVirus",
                                                             "ZCamSpotted",
                                                             "ZGotCamMonitor",
                                                             "ZCamMonitorOff",
                                                             "ZCamMonitorOn",
                                                             "CrashedShipGame",
                                                             "CrashedShipHud",
                                                             "NoEntry"};
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
    strcpy(filename, "Level10.msg");
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
  case ID_CUSTOM_OBJECT_2042:
    return new CustomObjectScript_2042;
    break;
  case ID_CUSTOM_OBJECT_10A3:
    return new CustomObjectScript_10A3;
    break;
  case ID_CUSTOM_OBJECT_094B:
    return new CustomObjectScript_094B;
    break;
  case ID_CUSTOM_OBJECT_0945:
    return new CustomObjectScript_0945;
    break;
  case ID_CUSTOM_OBJECT_113E:
    return new CustomObjectScript_113E;
    break;
  case ID_CUSTOM_OBJECT_193F:
    return new CustomObjectScript_193F;
    break;
  case ID_CUSTOM_OBJECT_2140:
    return new CustomObjectScript_2140;
    break;
  case ID_CUSTOM_OBJECT_0875:
    return new CustomObjectScript_0875;
    break;
  case ID_CUSTOM_OBJECT_0877:
    return new CustomObjectScript_0877;
    break;
  case ID_CUSTOM_OBJECT_105C:
    return new CustomObjectScript_105C;
    break;
  case ID_CUSTOM_OBJECT_0878:
    return new CustomObjectScript_0878;
    break;
  case ID_CUSTOM_OBJECT_28BA:
    return new CustomObjectScript_28BA;
    break;
  case ID_CUSTOM_OBJECT_2133:
    return new CustomObjectScript_2133;
    break;
  case ID_CUSTOM_OBJECT_1139:
    return new CustomObjectScript_1139;
    break;
  case ID_CUSTOM_OBJECT_098A:
    return new CustomObjectScript_098A;
    break;
  case ID_CUSTOM_OBJECT_08AA:
    return new CustomObjectScript_08AA;
    break;
  case ID_CUSTOM_OBJECT_18BF:
    return new CustomObjectScript_18BF;
    break;
  case ID_CUSTOM_OBJECT_10C0:
    return new CustomObjectScript_10C0;
    break;
  case ID_CUSTOM_OBJECT_2904:
    return new CustomObjectScript_2904;
    break;
  case ID_CUSTOM_OBJECT_3088:
    return new CustomObjectScript_3088;
    break;
  case ID_CUSTOM_OBJECT_2105:
    return new CustomObjectScript_2105;
    break;
  case ID_CUSTOM_OBJECT_3092:
    return new CustomObjectScript_3092;
    break;
  case ID_CUSTOM_OBJECT_187C:
    return new CustomObjectScript_187C;
    break;
  case ID_CUSTOM_OBJECT_10FA:
    return new CustomObjectScript_10FA;
    break;
  case ID_CUSTOM_OBJECT_0903:
    return new CustomObjectScript_0903;
    break;
  case ID_CUSTOM_OBJECT_1902:
    return new CustomObjectScript_1902;
    break;
  case ID_CUSTOM_OBJECT_4047:
    return new CustomObjectScript_4047;
    break;
  case ID_CUSTOM_OBJECT_289B:
    return new CustomObjectScript_289B;
    break;
  case ID_CUSTOM_OBJECT_3849:
    return new CustomObjectScript_3849;
    break;
  case ID_CUSTOM_OBJECT_184B:
    return new CustomObjectScript_184B;
    break;
  case ID_CUSTOM_OBJECT_204A:
    return new CustomObjectScript_204A;
    break;
  case ID_CUSTOM_OBJECT_2064:
    return new CustomObjectScript_2064;
    break;
  case ID_CUSTOM_OBJECT_1065:
    return new CustomObjectScript_1065;
    break;
  case ID_CUSTOM_OBJECT_2063:
    return new CustomObjectScript_2063;
    break;
  case ID_CUSTOM_OBJECT_5843:
    return new CustomObjectScript_5843;
    break;
  case ID_CUSTOM_OBJECT_1095:
    return new CustomObjectScript_1095;
    break;
  case ID_CUSTOM_OBJECT_1094:
    return new CustomObjectScript_1094;
    break;
  case ID_CUSTOM_OBJECT_1080:
    return new CustomObjectScript_1080;
    break;
  case ID_CUSTOM_OBJECT_187F:
    return new CustomObjectScript_187F;
    break;
  case ID_CUSTOM_OBJECT_501A:
    return new CustomObjectScript_501A;
    break;
  case ID_CUSTOM_OBJECT_D80D:
    return new CustomObjectScript_D80D;
    break;
  case ID_CUSTOM_OBJECT_18A1:
    return new CustomObjectScript_18A1;
    break;
  case ID_CUSTOM_OBJECT_208B:
    return new CustomObjectScript_208B;
    break;
  case ID_CUSTOM_OBJECT_2074:
    return new CustomObjectScript_2074;
    break;
  case ID_CUSTOM_OBJECT_203D:
    return new CustomObjectScript_203D;
    break;
  case ID_CUSTOM_OBJECT_11B1:
    return new CustomObjectScript_11B1;
    break;
  case ID_CUSTOM_OBJECT_3898:
    return new CustomObjectScript_3898;
    break;
  case ID_CUSTOM_OBJECT_303C:
    return new CustomObjectScript_303C;
    break;
  case ID_CUSTOM_OBJECT_2090:
    return new CustomObjectScript_2090;
    break;
  case ID_CUSTOM_OBJECT_09D4:
    return new CustomObjectScript_09D4;
    break;
  case ID_CUSTOM_OBJECT_1050:
    return new CustomObjectScript_1050;
    break;
  case ID_CUSTOM_OBJECT_2044:
    return new CustomObjectScript_2044;
    break;
  case ID_CUSTOM_OBJECT_1845:
    return new CustomObjectScript_1845;
    break;
  case ID_CUSTOM_OBJECT_1058:
    return new CustomObjectScript_1058;
    break;
  case ID_CUSTOM_OBJECT_09A3:
    return new CustomObjectScript_09A3;
    break;
  case ID_CUSTOM_OBJECT_11AF:
    return new CustomObjectScript_11AF;
    break;
  case ID_CUSTOM_OBJECT_49B0:
    return new CustomObjectScript_49B0;
    break;
  case ID_CUSTOM_OBJECT_11D2:
    return new CustomObjectScript_11D2;
    break;
  case ID_CUSTOM_OBJECT_09D5:
    return new CustomObjectScript_09D5;
    break;
  case ID_CUSTOM_OBJECT_18A5:
    return new CustomObjectScript_18A5;
    break;
  case ID_CUSTOM_OBJECT_10FB:
    return new CustomObjectScript_10FB;
    break;
  case ID_CUSTOM_OBJECT_19A2:
    return new CustomObjectScript_19A2;
    break;
  case ID_CUSTOM_OBJECT_09A4:
    return new CustomObjectScript_09A4;
    break;
  case ID_CUSTOM_OBJECT_09A5:
    return new CustomObjectScript_09A5;
    break;
  case ID_CUSTOM_OBJECT_09A6:
    return new CustomObjectScript_09A6;
    break;
  case ID_CUSTOM_OBJECT_09A1:
    return new CustomObjectScript_09A1;
    break;
  case ID_CUSTOM_OBJECT_20FD:
    return new CustomObjectScript_20FD;
    break;
  case ID_CUSTOM_OBJECT_187E:
    return new CustomObjectScript_187E;
    break;
  case ID_CUSTOM_OBJECT_987D:
    return new CustomObjectScript_987D;
    break;
  case ID_CUSTOM_OBJECT_09AA:
    return new CustomObjectScript_09AA;
    break;
  case ID_CUSTOM_OBJECT_0816:
    return new CustomObjectScript_0816;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
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
  case ID_CUSTOM_OBJECT_2042:
    delete ((CustomObjectScript_2042 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10A3:
    delete ((CustomObjectScript_10A3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_094B:
    delete ((CustomObjectScript_094B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0945:
    delete ((CustomObjectScript_0945 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_113E:
    delete ((CustomObjectScript_113E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_193F:
    delete ((CustomObjectScript_193F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2140:
    delete ((CustomObjectScript_2140 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0875:
    delete ((CustomObjectScript_0875 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0877:
    delete ((CustomObjectScript_0877 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_105C:
    delete ((CustomObjectScript_105C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0878:
    delete ((CustomObjectScript_0878 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_28BA:
    delete ((CustomObjectScript_28BA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2133:
    delete ((CustomObjectScript_2133 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1139:
    delete ((CustomObjectScript_1139 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_098A:
    delete ((CustomObjectScript_098A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08AA:
    delete ((CustomObjectScript_08AA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18BF:
    delete ((CustomObjectScript_18BF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10C0:
    delete ((CustomObjectScript_10C0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2904:
    delete ((CustomObjectScript_2904 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3088:
    delete ((CustomObjectScript_3088 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2105:
    delete ((CustomObjectScript_2105 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3092:
    delete ((CustomObjectScript_3092 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_187C:
    delete ((CustomObjectScript_187C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FA:
    delete ((CustomObjectScript_10FA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0903:
    delete ((CustomObjectScript_0903 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1902:
    delete ((CustomObjectScript_1902 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_4047:
    delete ((CustomObjectScript_4047 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_289B:
    delete ((CustomObjectScript_289B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3849:
    delete ((CustomObjectScript_3849 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_184B:
    delete ((CustomObjectScript_184B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_204A:
    delete ((CustomObjectScript_204A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2064:
    delete ((CustomObjectScript_2064 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1065:
    delete ((CustomObjectScript_1065 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2063:
    delete ((CustomObjectScript_2063 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_5843:
    delete ((CustomObjectScript_5843 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1095:
    delete ((CustomObjectScript_1095 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1094:
    delete ((CustomObjectScript_1094 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1080:
    delete ((CustomObjectScript_1080 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_187F:
    delete ((CustomObjectScript_187F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_501A:
    delete ((CustomObjectScript_501A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_D80D:
    delete ((CustomObjectScript_D80D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A1:
    delete ((CustomObjectScript_18A1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_208B:
    delete ((CustomObjectScript_208B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2074:
    delete ((CustomObjectScript_2074 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_203D:
    delete ((CustomObjectScript_203D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11B1:
    delete ((CustomObjectScript_11B1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3898:
    delete ((CustomObjectScript_3898 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_303C:
    delete ((CustomObjectScript_303C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2090:
    delete ((CustomObjectScript_2090 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09D4:
    delete ((CustomObjectScript_09D4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1050:
    delete ((CustomObjectScript_1050 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2044:
    delete ((CustomObjectScript_2044 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1845:
    delete ((CustomObjectScript_1845 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1058:
    delete ((CustomObjectScript_1058 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A3:
    delete ((CustomObjectScript_09A3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11AF:
    delete ((CustomObjectScript_11AF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_49B0:
    delete ((CustomObjectScript_49B0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11D2:
    delete ((CustomObjectScript_11D2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09D5:
    delete ((CustomObjectScript_09D5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18A5:
    delete ((CustomObjectScript_18A5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10FB:
    delete ((CustomObjectScript_10FB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19A2:
    delete ((CustomObjectScript_19A2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A4:
    delete ((CustomObjectScript_09A4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A5:
    delete ((CustomObjectScript_09A5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A6:
    delete ((CustomObjectScript_09A6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A1:
    delete ((CustomObjectScript_09A1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20FD:
    delete ((CustomObjectScript_20FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_187E:
    delete ((CustomObjectScript_187E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_987D:
    delete ((CustomObjectScript_987D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09AA:
    delete ((CustomObjectScript_09AA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0816:
    delete ((CustomObjectScript_0816 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
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
  case ID_CUSTOM_OBJECT_2042:
  case ID_CUSTOM_OBJECT_10A3:
  case ID_CUSTOM_OBJECT_094B:
  case ID_CUSTOM_OBJECT_0945:
  case ID_CUSTOM_OBJECT_113E:
  case ID_CUSTOM_OBJECT_193F:
  case ID_CUSTOM_OBJECT_2140:
  case ID_CUSTOM_OBJECT_0875:
  case ID_CUSTOM_OBJECT_0877:
  case ID_CUSTOM_OBJECT_105C:
  case ID_CUSTOM_OBJECT_0878:
  case ID_CUSTOM_OBJECT_28BA:
  case ID_CUSTOM_OBJECT_2133:
  case ID_CUSTOM_OBJECT_1139:
  case ID_CUSTOM_OBJECT_098A:
  case ID_CUSTOM_OBJECT_08AA:
  case ID_CUSTOM_OBJECT_18BF:
  case ID_CUSTOM_OBJECT_10C0:
  case ID_CUSTOM_OBJECT_2904:
  case ID_CUSTOM_OBJECT_3088:
  case ID_CUSTOM_OBJECT_2105:
  case ID_CUSTOM_OBJECT_3092:
  case ID_CUSTOM_OBJECT_187C:
  case ID_CUSTOM_OBJECT_10FA:
  case ID_CUSTOM_OBJECT_0903:
  case ID_CUSTOM_OBJECT_1902:
  case ID_CUSTOM_OBJECT_4047:
  case ID_CUSTOM_OBJECT_289B:
  case ID_CUSTOM_OBJECT_3849:
  case ID_CUSTOM_OBJECT_184B:
  case ID_CUSTOM_OBJECT_204A:
  case ID_CUSTOM_OBJECT_2064:
  case ID_CUSTOM_OBJECT_1065:
  case ID_CUSTOM_OBJECT_2063:
  case ID_CUSTOM_OBJECT_5843:
  case ID_CUSTOM_OBJECT_1095:
  case ID_CUSTOM_OBJECT_1094:
  case ID_CUSTOM_OBJECT_1080:
  case ID_CUSTOM_OBJECT_187F:
  case ID_CUSTOM_OBJECT_501A:
  case ID_CUSTOM_OBJECT_D80D:
  case ID_CUSTOM_OBJECT_18A1:
  case ID_CUSTOM_OBJECT_208B:
  case ID_CUSTOM_OBJECT_2074:
  case ID_CUSTOM_OBJECT_203D:
  case ID_CUSTOM_OBJECT_11B1:
  case ID_CUSTOM_OBJECT_3898:
  case ID_CUSTOM_OBJECT_303C:
  case ID_CUSTOM_OBJECT_2090:
  case ID_CUSTOM_OBJECT_09D4:
  case ID_CUSTOM_OBJECT_1050:
  case ID_CUSTOM_OBJECT_2044:
  case ID_CUSTOM_OBJECT_1845:
  case ID_CUSTOM_OBJECT_1058:
  case ID_CUSTOM_OBJECT_09A3:
  case ID_CUSTOM_OBJECT_11AF:
  case ID_CUSTOM_OBJECT_49B0:
  case ID_CUSTOM_OBJECT_11D2:
  case ID_CUSTOM_OBJECT_09D5:
  case ID_CUSTOM_OBJECT_18A5:
  case ID_CUSTOM_OBJECT_10FB:
  case ID_CUSTOM_OBJECT_19A2:
  case ID_CUSTOM_OBJECT_09A4:
  case ID_CUSTOM_OBJECT_09A5:
  case ID_CUSTOM_OBJECT_09A6:
  case ID_CUSTOM_OBJECT_09A1:
  case ID_CUSTOM_OBJECT_20FD:
  case ID_CUSTOM_OBJECT_187E:
  case ID_CUSTOM_OBJECT_987D:
  case ID_CUSTOM_OBJECT_09AA:
  case ID_CUSTOM_OBJECT_0816:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0013:
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
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0013;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[71];
  static int cust_id_list[71] = {
      ID_CUSTOM_OBJECT_2042, ID_CUSTOM_OBJECT_10A3, ID_CUSTOM_OBJECT_094B, ID_CUSTOM_OBJECT_0945, ID_CUSTOM_OBJECT_113E,
      ID_CUSTOM_OBJECT_193F, ID_CUSTOM_OBJECT_2140, ID_CUSTOM_OBJECT_0875, ID_CUSTOM_OBJECT_0877, ID_CUSTOM_OBJECT_105C,
      ID_CUSTOM_OBJECT_0878, ID_CUSTOM_OBJECT_28BA, ID_CUSTOM_OBJECT_2133, ID_CUSTOM_OBJECT_1139, ID_CUSTOM_OBJECT_098A,
      ID_CUSTOM_OBJECT_08AA, ID_CUSTOM_OBJECT_18BF, ID_CUSTOM_OBJECT_10C0, ID_CUSTOM_OBJECT_2904, ID_CUSTOM_OBJECT_3088,
      ID_CUSTOM_OBJECT_2105, ID_CUSTOM_OBJECT_3092, ID_CUSTOM_OBJECT_187C, ID_CUSTOM_OBJECT_10FA, ID_CUSTOM_OBJECT_0903,
      ID_CUSTOM_OBJECT_1902, ID_CUSTOM_OBJECT_4047, ID_CUSTOM_OBJECT_289B, ID_CUSTOM_OBJECT_3849, ID_CUSTOM_OBJECT_184B,
      ID_CUSTOM_OBJECT_204A, ID_CUSTOM_OBJECT_2064, ID_CUSTOM_OBJECT_1065, ID_CUSTOM_OBJECT_2063, ID_CUSTOM_OBJECT_5843,
      ID_CUSTOM_OBJECT_1095, ID_CUSTOM_OBJECT_1094, ID_CUSTOM_OBJECT_1080, ID_CUSTOM_OBJECT_187F, ID_CUSTOM_OBJECT_501A,
      ID_CUSTOM_OBJECT_D80D, ID_CUSTOM_OBJECT_18A1, ID_CUSTOM_OBJECT_208B, ID_CUSTOM_OBJECT_2074, ID_CUSTOM_OBJECT_203D,
      ID_CUSTOM_OBJECT_11B1, ID_CUSTOM_OBJECT_3898, ID_CUSTOM_OBJECT_303C, ID_CUSTOM_OBJECT_2090, ID_CUSTOM_OBJECT_09D4,
      ID_CUSTOM_OBJECT_1050, ID_CUSTOM_OBJECT_2044, ID_CUSTOM_OBJECT_1845, ID_CUSTOM_OBJECT_1058, ID_CUSTOM_OBJECT_09A3,
      ID_CUSTOM_OBJECT_11AF, ID_CUSTOM_OBJECT_49B0, ID_CUSTOM_OBJECT_11D2, ID_CUSTOM_OBJECT_09D5, ID_CUSTOM_OBJECT_18A5,
      ID_CUSTOM_OBJECT_10FB, ID_CUSTOM_OBJECT_19A2, ID_CUSTOM_OBJECT_09A4, ID_CUSTOM_OBJECT_09A5, ID_CUSTOM_OBJECT_09A6,
      ID_CUSTOM_OBJECT_09A1, ID_CUSTOM_OBJECT_20FD, ID_CUSTOM_OBJECT_187E, ID_CUSTOM_OBJECT_987D, ID_CUSTOM_OBJECT_09AA,
      ID_CUSTOM_OBJECT_0816};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[40];
  cust_handle_list[1] = Object_handles[41];
  cust_handle_list[2] = Object_handles[42];
  cust_handle_list[3] = Object_handles[43];
  cust_handle_list[4] = Object_handles[44];
  cust_handle_list[5] = Object_handles[45];
  cust_handle_list[6] = Object_handles[46];
  cust_handle_list[7] = Object_handles[1];
  cust_handle_list[8] = Object_handles[2];
  cust_handle_list[9] = Object_handles[3];
  cust_handle_list[10] = Object_handles[4];
  cust_handle_list[11] = Object_handles[51];
  cust_handle_list[12] = Object_handles[54];
  cust_handle_list[13] = Object_handles[55];
  cust_handle_list[14] = Object_handles[60];
  cust_handle_list[15] = Object_handles[61];
  cust_handle_list[16] = Object_handles[62];
  cust_handle_list[17] = Object_handles[64];
  cust_handle_list[18] = Object_handles[78];
  cust_handle_list[19] = Object_handles[79];
  cust_handle_list[20] = Object_handles[39];
  cust_handle_list[21] = Object_handles[80];
  cust_handle_list[22] = Object_handles[81];
  cust_handle_list[23] = Object_handles[82];
  cust_handle_list[24] = Object_handles[83];
  cust_handle_list[25] = Object_handles[84];
  cust_handle_list[26] = Object_handles[85];
  cust_handle_list[27] = Object_handles[33];
  cust_handle_list[28] = Object_handles[73];
  cust_handle_list[29] = Object_handles[70];
  cust_handle_list[30] = Object_handles[90];
  cust_handle_list[31] = Object_handles[68];
  cust_handle_list[32] = Object_handles[76];
  cust_handle_list[33] = Object_handles[72];
  cust_handle_list[34] = Object_handles[74];
  cust_handle_list[35] = Object_handles[71];
  cust_handle_list[36] = Object_handles[75];
  cust_handle_list[37] = Object_handles[69];
  cust_handle_list[38] = Object_handles[77];
  cust_handle_list[39] = Object_handles[67];
  cust_handle_list[40] = Object_handles[91];
  cust_handle_list[41] = Object_handles[34];
  cust_handle_list[42] = Object_handles[0];
  cust_handle_list[43] = Object_handles[99];
  cust_handle_list[44] = Object_handles[100];
  cust_handle_list[45] = Object_handles[101];
  cust_handle_list[46] = Object_handles[102];
  cust_handle_list[47] = Object_handles[103];
  cust_handle_list[48] = Object_handles[104];
  cust_handle_list[49] = Object_handles[105];
  cust_handle_list[50] = Object_handles[5];
  cust_handle_list[51] = Object_handles[6];
  cust_handle_list[52] = Object_handles[7];
  cust_handle_list[53] = Object_handles[8];
  cust_handle_list[54] = Object_handles[20];
  cust_handle_list[55] = Object_handles[21];
  cust_handle_list[56] = Object_handles[22];
  cust_handle_list[57] = Object_handles[23];
  cust_handle_list[58] = Object_handles[24];
  cust_handle_list[59] = Object_handles[25];
  cust_handle_list[60] = Object_handles[26];
  cust_handle_list[61] = Object_handles[27];
  cust_handle_list[62] = Object_handles[28];
  cust_handle_list[63] = Object_handles[29];
  cust_handle_list[64] = Object_handles[30];
  cust_handle_list[65] = Object_handles[31];
  cust_handle_list[66] = Object_handles[32];
  cust_handle_list[67] = Object_handles[106];
  cust_handle_list[68] = Object_handles[107];
  cust_handle_list[69] = Object_handles[108];
  cust_handle_list[70] = Object_handles[110];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 71;
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

    // Script 000: Level Start - Init Variables/Flags
    if (1) {
      aObjSaveHandle(Object_handles[0], 2);
      aUserVarSet(0, 0.000000f);
      aUserVarSet(4, qMathSubFloat(40.000000f, qMathMulFloat(5.000000f, qMathIntToFloat(qGetDifficulty()))));
      aUserVarSet(2, 0.000000f);
      aUserFlagSet(1, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(0, 0);
      aUserFlagSet(3, 1);
      aUserFlagSet(4, 1);
      aUserFlagSet(5, 1);
      aUserFlagSet(7, 0);
      aUserFlagSet(6, 1);
      aUserFlagSet(9, 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(11, 0);
      aUserFlagSet(12, 0);
      aUserFlagSet(13, 0);
      aUserFlagSet(14, 0);
      aUserFlagSet(15, 0);
      aUserFlagSet(16, 0);
      aUserFlagSet(17, 0);
      aUserFlagSet(19, 0);
      aUserFlagSet(26, 0);
      aUserFlagSet(27, 0);
      aUserFlagSet(18, 0);
      aUserFlagSet(20, 0);
      aUserFlagSet(21, 0);
      aUserFlagSet(22, 0);
      aUserFlagSet(23, 0);
      aUserFlagSet(24, 0);
      aUserFlagSet(25, 0);
      aUserFlagSet(28, 0);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 050: Level Start - Init Matcens
    if (1) {
      aMatcenSetState(0, Matcen_indexes[0]);
      aMatcenSetState(0, Matcen_indexes[1]);
      aMatcenSetState(0, Matcen_indexes[2]);
      aMatcenSetState(0, Matcen_indexes[3]);
      aMatcenSetState(0, Matcen_indexes[4]);
      aMatcenSetState(0, Matcen_indexes[5]);
      aMatcenSetState(0, Matcen_indexes[6]);
      aMatcenSetState(0, Matcen_indexes[7]);
      aMatcenSetState(0, Matcen_indexes[8]);
      aMatcenSetState(0, Matcen_indexes[9]);
      aMatcenSetEnableState(1, Matcen_indexes[10]);
      aMatcenSetEnableState(1, Matcen_indexes[11]);
      aMatcenSetEnableState(1, Matcen_indexes[12]);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }

    // Script 051: Level Start - Init AI
    if (1) {
      aSetLevelTimer(10.000000f, 4);
      aSetLevelTimer(10.000000f, 7);
      aAISetState(0, Object_handles[1]);
      aAISetState(0, Object_handles[2]);
      aAISetState(0, Object_handles[3]);
      aAISetState(0, Object_handles[4]);
      aAISetState(0, Object_handles[5]);
      aAISetState(0, Object_handles[6]);
      aAISetState(0, Object_handles[7]);
      aAISetState(0, Object_handles[8]);
      aAISetState(0, Object_handles[9]);
      aAISetState(0, Object_handles[10]);
      aAISetState(0, Object_handles[11]);
      aAISetState(0, Object_handles[12]);
      aAISetState(0, Object_handles[13]);
      aObjGhostSet(1, Object_handles[9]);
      aObjGhostSet(1, Object_handles[10]);
      aObjGhostSet(1, Object_handles[11]);
      aObjGhostSet(1, Object_handles[12]);
      aObjGhostSet(1, Object_handles[13]);
      aAISetState(0, Object_handles[14]);
      aAISetState(0, Object_handles[15]);
      aAISetState(0, Object_handles[16]);
      aAISetState(0, Object_handles[17]);
      aAISetState(0, Object_handles[18]);
      aAISetState(0, Object_handles[19]);
      aObjGhostSet(1, Object_handles[14]);
      aObjGhostSet(1, Object_handles[15]);
      aObjGhostSet(1, Object_handles[16]);
      aObjGhostSet(1, Object_handles[17]);
      aObjGhostSet(1, Object_handles[18]);
      aObjGhostSet(1, Object_handles[19]);
      aAISetState(0, Object_handles[20]);
      aAISetState(0, Object_handles[21]);
      aAISetState(0, Object_handles[22]);
      aAISetState(0, Object_handles[23]);
      aAISetState(0, Object_handles[24]);
      aAISetState(0, Object_handles[25]);
      aAISetState(0, Object_handles[26]);
      aAISetState(0, Object_handles[27]);
      aAISetState(0, Object_handles[28]);
      aAISetState(0, Object_handles[29]);
      aAISetState(0, Object_handles[30]);
      aAISetState(0, Object_handles[31]);
      aAISetState(0, Object_handles[32]);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }

    // Script 052: Level Start - Init Misc
    if (1) {
      aDoorLockUnlock(1, Door_handles[0]);
      aObjHide(Object_handles[33]);
      aObjHide(Object_handles[34]);
      aObjHide(Object_handles[35]);
      aTurnOnSpew(Object_handles[36], -1, 1, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.150000f, -1.000000f,
                  4.000000f, 20.000000f, 1, 1);
      aTurnOnSpew(Object_handles[37], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f,
                  4.000000f, 20.000000f, 1, 0);
      aTurnOnSpew(Object_handles[38], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.150000f, -1.000000f,
                  4.000000f, 20.000000f, 1, 2);
      aSetLevelTimer(5.000000f, 15);
      aSetLevelTimer(1.000000f, 16);
      aSetLevelTimer(0.400000f, 17);
      aObjGhostSet(1, Object_handles[39]);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }

    // Script 148: Level Start - Init Base Alert Display
    if (1) {
      aInitBaseAlertDisplay();

      // Increment the script action counter
      if (ScriptActionCtr_148 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_148++;
    }

    // Script 039: Level Start - Intro Cinematic
    if (1) {
      aCloakAllPlayers(25.000000f);
      aComplexCinematicStart();
      aComplexCinematicTrack(Object_handles[40], 0.000000f, 1.000000f);
      aComplexCinematicStartTrans(1);
      aComplexCinematicCameraOnPath(Path_indexes[0]);
      aComplexCinematicEnd(Message_strings[0], 9.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 072: Music-Intro Init
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 121: Show Data Vault Guard Spotted Msg
    if ((ScriptActionCtr_121 < 1) && ((event_data->id == 21) && (qObjShields(Object_handles[46]) > 0.000000f) &&
                                      ((ScriptActionCtr_094 > 0) == false))) {
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }

    // Script 061: Check Big Gun's Sights
    if (event_data->id == 15) {
      if (qObjCanSeePlayerAdvancedWithStore(3, 45, Object_handles[49], 500.000000f, 1048585) == true) {
        if (qObjShields(qObjSavedHandle(3)) > 0.000000f) {
          aShowHUDMessage(Message_strings[6]);
          aStoreObjectInPositionClipboard(qObjSavedHandle(3));
          aMoveObjectToPositionClipboard(Object_handles[50]);
          aObjApplyDamage(qObjSavedHandle(3), 80.000000f);
          aLightningCreate(Object_handles[49], Object_handles[50], 0.200000f, 3.000000f, 8, Texture_indexes[0],
                           0.800000f, 1, 255, 255, 255, 0);
          aLightningCreate(Object_handles[49], Object_handles[50], 0.300000f, 2.000000f, 6, Texture_indexes[1],
                           0.500000f, 1, 255, 255, 255, 0);
          aSoundPlayObject(Sound_indexes[3], Object_handles[49], 1.000000f);
          aSetLevelTimer(5.000000f, 15);
        }
      } else {
        aSetLevelTimer(3.000000f, 15);
      }

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }

    // Script 122: Show Jugg Guard Spotted Msg
    if ((ScriptActionCtr_122 < 1) && ((event_data->id == 22) && (qObjShields(Object_handles[51]) > 0.000000f) &&
                                      ((ScriptActionCtr_019 > 0) == false))) {
      aShowHUDMessage(Message_strings[7]);
      aSetLevelTimer(4.000000f, 3);

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }

    // Script 020: Show Juggernaut Alert Warning
    if (event_data->id == 3) {
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 123: Show Canyon Guard Spotted Msg
    if ((ScriptActionCtr_123 < 1) && ((event_data->id == 19) && (qObjShields(Object_handles[54]) > 0.000000f) &&
                                      ((ScriptActionCtr_087 > 0) == false))) {
      aShowHUDMessage(Message_strings[10]);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }

    // Script 124: Show Command Base Guard Spotted Msg
    if ((ScriptActionCtr_124 < 1) && ((event_data->id == 20) && (qObjShields(Object_handles[55]) > 0.000000f) &&
                                      ((ScriptActionCtr_089 > 0) == false))) {
      aShowHUDMessage(Message_strings[12]);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }

    // Script 073: Show D1 Ground Guard Spotted Msg
    if ((ScriptActionCtr_073 < 1) && ((event_data->id == 12) && (qObjShields(Object_handles[62]) > 0.000000f) &&
                                      ((ScriptActionCtr_035 > 0) == false))) {
      aShowHUDMessage(Message_strings[14]);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }

    // Script 120: Show Hanger Guard Spotted Msg
    if ((ScriptActionCtr_120 < 1) && ((event_data->id == 18) && (qObjShields(Object_handles[64]) > 0.000000f) &&
                                      ((ScriptActionCtr_034 > 0) == false))) {
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }

    // Script 045: Alert the Base
    if (event_data->id == 13) {
      if (ScriptActionCtr_045 == 0) {
        if (qUserFlag(6) == true) {
          if ((qObjAnimFrame(Object_handles[67]) == 0.000000f) || (qObjAnimFrame(Object_handles[67]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[67], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[67], 1.000000f);
            aUserFlagSet(6, 0);
            aGoalCompleted(Goal_indexes[0], 0);
          }
        }
        if (qUserFlag(10) == false) {
          if ((qObjAnimFrame(Object_handles[68]) == 0.000000f) || (qObjAnimFrame(Object_handles[68]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[68], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[68], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[2]);
            aUserFlagSet(10, 1);
          }
        }
        if (qUserFlag(16) == false) {
          if ((qObjAnimFrame(Object_handles[69]) == 0.000000f) || (qObjAnimFrame(Object_handles[69]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[69], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[69], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[8]);
            aUserFlagSet(16, 1);
          }
        }
        aMatcenSetState(1, Matcen_indexes[13]);
      }
      if (ScriptActionCtr_045 == 1) {
        if (qUserFlag(4) == true) {
          if ((qObjAnimFrame(Object_handles[70]) == 0.000000f) || (qObjAnimFrame(Object_handles[70]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[70], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[70], 1.000000f);
            aMatcenSetState(0, Matcen_indexes[1]);
            aUserFlagSet(4, 0);
            aTurnOffSpew(0);
            aGoalCompleted(Goal_indexes[1], 0);
          }
        }
        if (qUserFlag(14) == false) {
          if ((qObjAnimFrame(Object_handles[71]) == 0.000000f) || (qObjAnimFrame(Object_handles[71]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[71], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[71], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[6]);
            aUserFlagSet(14, 1);
          }
        }
        if (qUserFlag(12) == false) {
          if ((qObjAnimFrame(Object_handles[72]) == 0.000000f) || (qObjAnimFrame(Object_handles[72]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[72], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[72], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[4]);
            aUserFlagSet(12, 1);
          }
        }
        aMatcenSetState(1, Matcen_indexes[14]);
        aMatcenSetState(1, Matcen_indexes[15]);
        aAIFlags(0, 32, Object_handles[41]);
        aAISetTeam(0, Object_handles[41]);
      }
      if (ScriptActionCtr_045 == 3) {
        if (qUserFlag(5) == true) {
          if ((qObjAnimFrame(Object_handles[73]) == 0.000000f) || (qObjAnimFrame(Object_handles[73]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[73], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[73], 1.000000f);
            aUserFlagSet(5, 0);
            aTurnOffSpew(2);
            aGoalCompleted(Goal_indexes[2], 0);
          }
        }
        if (qUserFlag(13) == false) {
          if ((qObjAnimFrame(Object_handles[74]) == 0.000000f) || (qObjAnimFrame(Object_handles[74]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[74], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[74], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[5]);
            aUserFlagSet(13, 1);
          }
        }
        if (qUserFlag(15) == false) {
          if ((qObjAnimFrame(Object_handles[75]) == 0.000000f) || (qObjAnimFrame(Object_handles[75]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[75], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[75], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[7]);
            aUserFlagSet(15, 1);
          }
        }
        aMatcenSetState(1, Matcen_indexes[16]);
      }
      if (ScriptActionCtr_045 == 2) {
        if (qUserFlag(11) == false) {
          if ((qObjAnimFrame(Object_handles[76]) == 0.000000f) || (qObjAnimFrame(Object_handles[76]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[76], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[76], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[3]);
            aUserFlagSet(11, 1);
          }
        }
        if (qUserFlag(17) == false) {
          if ((qObjAnimFrame(Object_handles[77]) == 0.000000f) || (qObjAnimFrame(Object_handles[77]) == 2.000000f)) {
            aObjPlayAnim(Object_handles[77], 0, 1, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[4], Object_handles[77], 1.000000f);
            aMatcenSetState(1, Matcen_indexes[9]);
            aUserFlagSet(17, 1);
          }
        }
        aAIFlags(0, 32, Object_handles[42]);
        aAISetTeam(0, Object_handles[42]);
        aMatcenSetState(1, Matcen_indexes[0]);
      }
      if (ScriptActionCtr_045 == 4) {
        aMatcenSetState(1, Matcen_indexes[17]);
        aMatcenSetState(1, Matcen_indexes[18]);
      }
      aShowHUDMessageI(Message_strings[18], qMathAddInt(ScriptActionCtr_045, 1));
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aUpdateBaseAlertDisplay(Message_strings[19], qMathAddInt(ScriptActionCtr_045, 1));

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 022: Start D1 Ground Guard on Path A
    if (event_data->id == 4) {
      aAIGoalFollowPath(Object_handles[62], Path_indexes[18], 1, 7, 1, 0, 4352, 1);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 024: Start D1 Ground Guard on Path B
    if (event_data->id == 5) {
      aAIGoalFollowPath(Object_handles[62], Path_indexes[19], 1, 7, 1, 0, 4352, 2);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 026: Start D1 Ground Guard on Path C
    if (event_data->id == 6) {
      aAIGoalFollowPath(Object_handles[62], Path_indexes[20], 1, 7, 1, 0, 4352, 3);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 028: Start Hanger Guard on Forward Path
    if (event_data->id == 7) {
      aAIGoalFollowPath(Object_handles[64], Path_indexes[21], 1, 5, 1, 0, 4352, 4);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }

    // Script 030: Start Hanger Guard on Reverse Path
    if (event_data->id == 8) {
      aAIGoalFollowPath(Object_handles[64], Path_indexes[22], 1, 10, 1, 0, 4352, 5);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }

    // Script 047: Mark Base Infiltration Objective as Complete
    if ((ScriptActionCtr_047 < 1) && (event_data->id == 14)) {
      aGoalCompleted(Goal_indexes[5], 1);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 036: Create Prep Room Initialization Lightning
    if (event_data->id == 9) {
      if (ScriptActionCtr_036 == 0) {
        aLightningCreate(Object_handles[86], Object_handles[87], 6.000000f, 2.000000f, 3, Texture_indexes[2], 1.000000f,
                         1, 255, 255, 255, 0);
        aSetLevelTimer(0.100000f, 9);
      }
      if (ScriptActionCtr_036 == 1) {
        aLightningCreate(Object_handles[87], qObjSavedHandle(0), 6.000000f, 2.000000f, 3, Texture_indexes[2], 1.000000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(qObjSavedHandle(0), Object_handles[88], 6.000000f, 2.000000f, 3, Texture_indexes[2], 1.000000f,
                         1, 255, 255, 255, 0);
        aSetLevelTimer(0.100000f, 9);
      }
      if (ScriptActionCtr_036 == 2) {
        aLightningCreate(Object_handles[88], Object_handles[89], 6.000000f, 2.000000f, 3, Texture_indexes[2], 1.000000f,
                         1, 255, 255, 255, 0);
        aSetLevelTimer(0.100000f, 9);
      }
      if (ScriptActionCtr_036 == 3) {
        aLightningCreate(qObjSavedHandle(0), Object_handles[86], 6.000000f, 2.000000f, 3, Texture_indexes[2], 1.000000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[89], qObjSavedHandle(0), 6.000000f, 2.000000f, 3, Texture_indexes[2], 1.000000f,
                         1, 255, 255, 255, 0);
        aSetLevelTimer(0.200000f, 9);
      }
      if (ScriptActionCtr_036 == 4) {
        aLightningCreate(Object_handles[86], Object_handles[87], 5.500000f, 2.000000f, 3, Texture_indexes[3], 0.500000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[87], qObjSavedHandle(0), 5.500000f, 2.000000f, 3, Texture_indexes[3], 0.500000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(qObjSavedHandle(0), Object_handles[88], 5.500000f, 2.000000f, 3, Texture_indexes[3], 0.500000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[88], Object_handles[89], 5.500000f, 2.000000f, 3, Texture_indexes[3], 0.500000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(qObjSavedHandle(0), Object_handles[86], 5.500000f, 2.000000f, 3, Texture_indexes[3], 0.500000f,
                         1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[89], qObjSavedHandle(0), 5.500000f, 2.000000f, 3, Texture_indexes[3], 0.500000f,
                         1, 255, 255, 255, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 037: Clear Message Delay Flag
    if (event_data->id == 10) {
      aUserFlagSet(8, 0);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }

    // Script 017: Memory Plasma Charge Expires
    if ((event_data->id == 2) && (qUserFlag(9) == false)) {
      aUserVarDec(0);
      if (qUserVarValue(0) <= 0.000000f) {
        aShowHUDMessage(Message_strings[56]);
        aSoundPlayObject(Sound_indexes[7], qObjSavedHandle(2), 1.000000f);
        aUserFlagSet(1, 0);
        aUserVarSet(0, 0.000000f);
        aObjSaveHandle(Object_handles[0], 2);
        aGoalCompleted(Goal_indexes[11], 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 065: Set Waypoint 2 check (terrain canyon)
    if (event_data->id == 16) {
      if (qUserFlag(19) == false) {
        if (qObjCanSeePlayerAdvanced(90, Object_handles[92], 400.000000f, 1048585) == true) {
          aSetWaypoint(2);
          aUserFlagSet(19, 1);
        } else {
          aSetLevelTimer(1.000000f, 16);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }

    // Script 038: Create Virus Uploading Effects
    if (event_data->id == 11) {
      if (ScriptActionCtr_038 == 0) {
        aLightningCreate(Object_handles[93], qObjSavedHandle(1), 15.000000f, 5.000000f, 3, Texture_indexes[4],
                         1.000000f, 1, 255, 255, 255, 0);
        aLightningCreate(qObjSavedHandle(1), Object_handles[94], 15.000000f, 5.000000f, 3, Texture_indexes[4],
                         1.000000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(2.000000f, 11);
      }
      if (ScriptActionCtr_038 == 2) {
        aLightningCreate(Object_handles[95], qObjSavedHandle(1), 15.000000f, 2.000000f, 6, Texture_indexes[2],
                         1.000000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(1.000000f, 11);
      }
      if (ScriptActionCtr_038 == 2) {
        aLightningCreate(Object_handles[96], qObjSavedHandle(1), 15.000000f, 2.000000f, 6, Texture_indexes[2],
                         1.000000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(1.000000f, 11);
      }
      if (ScriptActionCtr_038 == 3) {
        aLightningCreate(Object_handles[97], qObjSavedHandle(1), 15.000000f, 2.000000f, 6, Texture_indexes[2],
                         1.000000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(1.000000f, 11);
      }
      if (ScriptActionCtr_038 == 4) {
        aLightningCreate(Object_handles[98], qObjSavedHandle(1), 15.000000f, 2.000000f, 6, Texture_indexes[2],
                         1.000000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(1.000000f, 11);
      }
      if (ScriptActionCtr_038 == 1) {
        aLightningCreate(qObjSavedHandle(1), Object_handles[93], 15.000000f, 1.000000f, 3, Texture_indexes[5],
                         0.250000f, 2, 255, 255, 255, 0);
        aLightningCreate(Object_handles[94], qObjSavedHandle(1), 15.000000f, 1.000000f, 3, Texture_indexes[5],
                         0.250000f, 2, 255, 255, 255, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 009: End Level
    if (event_data->id == 1) {
      aGoalCompleted(Goal_indexes[12], 1);
      aSetLevelTimer(1.000000f, 11);
      aStartEndlevelSequencePath(Path_indexes[25], Path_indexes[26], 15.000000f, Message_strings[57]);
      aSoundPlaySteaming("VoxLev10EndLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 101: Monitor Camera Group A
    if (event_data->id == 17) {
      aUserVarSet(2, 0.000000f);
      if ((qUserFlag(26) == true) && (qUserFlag(27) == true) && (qObjExists(qObjSavedHandle(5)) == 1)) {
        if ((qObjRoom(qObjSavedHandle(5)) == Room_indexes[5]) && (qObjExists(Object_handles[99]) == true)) {
          aCreatePopupView(0, Object_handles[99], 0.000000f, 1.000000f);
          aUserVarSet(2, 1.000000f);
        } else {
          if ((qObjRoom(qObjSavedHandle(5)) == Room_indexes[6]) && (qObjExists(Object_handles[100]) == true)) {
            aCreatePopupView(0, Object_handles[100], 0.000000f, 1.000000f);
            aUserVarSet(2, 2.000000f);
          } else {
            if (((qObjRoom(qObjSavedHandle(5)) == Room_indexes[7]) ||
                 (qObjRoom(qObjSavedHandle(5)) == Room_indexes[8]) ||
                 (qObjRoom(qObjSavedHandle(5)) == Room_indexes[9]) ||
                 (qObjRoom(qObjSavedHandle(5)) == Room_indexes[10]) ||
                 (qObjRoom(qObjSavedHandle(5)) == Room_indexes[11])) &&
                (qObjExists(Object_handles[101]) == true)) {
              aCreatePopupView(0, Object_handles[101], 0.000000f, 1.000000f);
              aUserVarSet(2, 3.000000f);
            } else {
              if ((qObjRoom(qObjSavedHandle(5)) == Room_indexes[12]) && (qObjExists(Object_handles[102]) == true)) {
                aCreatePopupView(0, Object_handles[102], 0.000000f, 1.000000f);
                aUserVarSet(2, 4.000000f);
              } else {
                if (((qObjRoom(qObjSavedHandle(5)) == Room_indexes[13]) ||
                     (qObjRoom(qObjSavedHandle(5)) == Room_indexes[14])) &&
                    (qObjExists(Object_handles[103]) == true)) {
                  aCreatePopupView(0, Object_handles[103], 0.000000f, 1.000000f);
                  aUserVarSet(2, 5.000000f);
                } else {
                  if ((qObjRoom(qObjSavedHandle(5)) == Room_indexes[15]) && (qObjExists(Object_handles[104]) == true)) {
                    aCreatePopupView(0, Object_handles[104], 0.000000f, 1.000000f);
                    aUserVarSet(2, 6.000000f);
                  } else {
                    if (((qObjRoom(qObjSavedHandle(5)) == Room_indexes[16]) ||
                         (qObjRoom(qObjSavedHandle(5)) == Room_indexes[3]) ||
                         (qObjRoom(qObjSavedHandle(5)) == Room_indexes[17]) ||
                         (qObjRoom(qObjSavedHandle(5)) == Room_indexes[18])) &&
                        (qObjExists(Object_handles[105]) == true)) {
                      aCreatePopupView(0, Object_handles[105], 0.000000f, 1.000000f);
                      aUserVarSet(2, 7.000000f);
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (qUserVarValue(2) == 0.000000f) {
        aClosePopupView();
      }
      aSetLevelTimer(0.400000f, 17);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 015: Memory Plasma Blob generated
    if (event_data->id == Matcen_indexes[1]) {
      aObjDelete(event_data->it_handle);
      aMatcenSetState(0, Matcen_indexes[1]);
      aObjGhostSet(0, Object_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 066: Foyer Matcen1 Produced Robot
    if (event_data->id == Matcen_indexes[2]) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[1], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }

    // Script 067: Foyer Matcen2 Produced Robot
    if (event_data->id == Matcen_indexes[3]) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[1], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }

    // Script 068: HD Matcen1 Produced Robot
    if (event_data->id == Matcen_indexes[4]) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[2], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }

    // Script 069: HD Matcen2 Produced Robot
    if (event_data->id == Matcen_indexes[5]) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[2], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }

    // Script 070: Aux Matcen1 Produced Robot
    if (event_data->id == Matcen_indexes[6]) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[3], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }

    // Script 071: Central Matcen Produced Robot
    if (event_data->id == Matcen_indexes[0]) {
      aAIGoalGotoRoom(event_data->it_handle, Room_indexes[4], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2042::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 021: Intro Landing Path
    if (1) {
      aPortalRenderSet(1, 0, Room_indexes[0], 1);
      aAIGoalFollowPath(data->me_handle, Path_indexes[4], 1, 4, 1, 3, 131328, 8);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 048: Set Fuel Tanker Landing Path B
    if (event_data->goal_uid == 8) {
      aPortalRenderSet(0, 0, Room_indexes[0], 1);
      aAIGoalFollowPath(data->me_handle, Path_indexes[5], 1, 2, 1, 3, 131328, 10);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }

    // Script 042: Land the Fuel Tanker
    if (event_data->goal_uid == 10) {
      aPortalRenderSet(1, 0, Room_indexes[0], 1);
      aAIGoalLandOnObject(Object_handles[40], 0, Object_handles[35], 0, 3, 131328, 9);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 043: Fuel Tanker has Landed
    if (event_data->goal_uid == 9) {

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 040: Intro Cinematic - Parts II and III
    if (1) {
      if (ScriptActionCtr_040 == 0) {
        aComplexCinematicStart();
        aComplexCinematicTrack(Object_handles[40], 0.000000f, 1.000000f);
        aComplexCinematicStartTrans(1);
        aComplexCinematicCameraOnPath(Path_indexes[1]);
        aComplexCinematicEnd(Message_strings[0], 9.000000f);
      }
      if (ScriptActionCtr_040 == 1) {
        aCinematicIntro(Path_indexes[2], Message_strings[1], data->me_handle, Path_indexes[3], 12.000000f);
        aSoundPlaySteaming("VoxLev10StartLevel.osf", 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10A3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 002: Space Patrol
    if (1) {
      aAIFlags(1, 32, data->me_handle);
      aAIGoalFollowPath(data->me_handle, Path_indexes[6], 1, 11, 1, 3, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_094B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 095: Sky Patrol 2
    if (1) {
      aAIFlags(1, 32, data->me_handle);
      aAIGoalFollowPath(data->me_handle, Path_indexes[7], 1, 14, 1, 3, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0945::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 096: Mega Trap Setoff
    if ((ScriptActionCtr_096 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[2]);
      aSoundPlay2D(Sound_indexes[0], 1.000000f);
      aObjGhostSet(0, Object_handles[17]);
      aAISetState(1, Object_handles[17]);
      aAIGoalGotoObject(Object_handles[17], event_data->it_handle, 0, 4352, -1);
      aObjGhostSet(0, Object_handles[18]);
      aAISetState(1, Object_handles[18]);
      aAIGoalGotoObject(Object_handles[18], event_data->it_handle, 0, 4352, -1);
      aObjGhostSet(0, Object_handles[19]);
      aAISetState(1, Object_handles[19]);
      aAIGoalGotoObject(Object_handles[19], event_data->it_handle, 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_113E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 090: Data Vault Patrol A
    if (1) {
      aAISetFOV(data->me_handle, 70.000000f);
      aAIGoalFollowPath(data->me_handle, Path_indexes[8], 1, 4, 1, 0, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_193F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 091: Data Vault Patrol B
    if (1) {
      aAISetFOV(data->me_handle, 70.000000f);
      aAIGoalFollowPath(data->me_handle, Path_indexes[9], 1, 8, 1, 0, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2140::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 092: Data Vault Guard Patrol
    if (1) {
      aAIGoalFollowPath(data->me_handle, Path_indexes[10], 1, 4, 1, 0, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 093: Data Vault Guard Spotted Player
    if ((ScriptActionCtr_093 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aAIGoalGotoObject(data->me_handle, Object_handles[47], 3, 4352, 13);
      aSetLevelTimer(1.000000f, 21);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 094: Data Vault Alerted
    if ((ScriptActionCtr_094 < 1) && (event_data->goal_uid == 13)) {
      aShowHUDMessage(Message_strings[4]);
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aObjPlayAnim(Object_handles[47], 0, 25, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], Object_handles[47], 1.000000f);
      aAISetState(1, Object_handles[1]);
      aAISetState(1, Object_handles[2]);
      aAISetState(1, Object_handles[3]);
      aAISetState(1, Object_handles[4]);
      aUserFlagSet(28, 1);
      aSetLevelTimer(4.000000f, 13);
      aObjGhostSet(0, Object_handles[13]);
      aAISetState(1, Object_handles[13]);
      aAIGoalGotoObject(Object_handles[13], Object_handles[48], 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0875::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 143: Data Vault Turret 1 Hit by Player
    if ((ScriptActionCtr_143 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(28) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[1]);
      aAISetState(1, Object_handles[2]);
      aAISetState(1, Object_handles[3]);
      aAISetState(1, Object_handles[4]);
      aUserFlagSet(28, 1);

      // Increment the script action counter
      if (ScriptActionCtr_143 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_143++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0877::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 144: Data Vault Turret 2 Hit by Player
    if ((ScriptActionCtr_144 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(28) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[1]);
      aAISetState(1, Object_handles[2]);
      aAISetState(1, Object_handles[3]);
      aAISetState(1, Object_handles[4]);
      aUserFlagSet(28, 1);

      // Increment the script action counter
      if (ScriptActionCtr_144 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_144++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_105C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 145: Data Vault Turret 3 Hit by Player
    if ((ScriptActionCtr_145 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(28) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[1]);
      aAISetState(1, Object_handles[2]);
      aAISetState(1, Object_handles[3]);
      aAISetState(1, Object_handles[4]);
      aUserFlagSet(28, 1);

      // Increment the script action counter
      if (ScriptActionCtr_145 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_145++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0878::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 146: Data Vault Turret 4 Hit by Player
    if ((ScriptActionCtr_146 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(28) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[1]);
      aAISetState(1, Object_handles[2]);
      aAISetState(1, Object_handles[3]);
      aAISetState(1, Object_handles[4]);
      aUserFlagSet(28, 1);

      // Increment the script action counter
      if (ScriptActionCtr_146 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_146++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_28BA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 018: Jugg Alerted Path
    if ((ScriptActionCtr_018 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aAIGoalFollowPath(data->me_handle, Path_indexes[11], 1, 4, 1, 3, 4356, 0);
      aSetLevelTimer(1.000000f, 22);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 019: Jugg Has Alerted the Base
    if ((ScriptActionCtr_019 < 1) && (event_data->goal_uid == 0)) {
      aShowHUDMessage(Message_strings[8]);
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aObjPlayAnim(Object_handles[52], 0, 25, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], Object_handles[52], 1.000000f);
      aObjGhostSet(0, Object_handles[9]);
      aAISetState(1, Object_handles[9]);
      aAIGoalGotoObject(Object_handles[9], Object_handles[53], 3, 4352, -1);
      aSetLevelTimer(4.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2133::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 125: Canyon Guard Patrol
    if (1) {
      aAIGoalFollowPath(data->me_handle, Path_indexes[12], 1, 9, 1, 0, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  case EVT_DAMAGED: {
    tOSIRISEVTDAMAGED *event_data = &data->evt_damaged;

    // Script 086: Canyon Guard Damaged
    if ((ScriptActionCtr_086 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) &&
         (qObjShields(data->me_handle) < qMathPercentage(0.800000f, qObjShieldsOriginal(data->me_handle))) &&
         (qObjShields(data->me_handle) > 0.000000f))) {
      aAISetMaxSpeed(data->me_handle, 65.000000f);
      aAIGoalFollowPath(data->me_handle, Path_indexes[13], 1, 9, 1, 3, 4352, 11);
      aSetLevelTimer(1.000000f, 19);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 087: Canyon Guard Retreated
    if ((ScriptActionCtr_087 < 1) && (event_data->goal_uid == 11)) {
      aObjSaveHandle(qPlayerClosest(data->me_handle, 1), 4);
      if (qUserVarValue(1) < 500.000000f) {
        aShowHUDMessage(Message_strings[11]);
        aSoundPlay2D(Sound_indexes[0], 1.000000f);
      }
      aAISetMaxSpeed(data->me_handle, 50.000000f);
      aObjGhostSet(0, Object_handles[14]);
      aAISetState(1, Object_handles[14]);
      aObjGhostSet(0, Object_handles[15]);
      aAISetState(1, Object_handles[15]);
      aObjGhostSet(0, Object_handles[16]);
      aAISetState(1, Object_handles[16]);
      aAIGoalGotoObject(Object_handles[14], Object_handles[54], 0, 4352, -1);
      aAIGoalGotoObject(Object_handles[15], Object_handles[54], 0, 4352, -1);
      aAIGoalGotoObject(Object_handles[16], Object_handles[54], 0, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1139::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 098: Setup Command Base Guard
    if (1) {
      aAIFlags(0, 33554432, data->me_handle);
      aAIGoalFollowPath(data->me_handle, Path_indexes[14], 1, 9, 1, 0, 8392960, -1);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 088: Command Base Guard Spotted Player
    if ((ScriptActionCtr_088 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aAIGoalGotoObject(Object_handles[56], event_data->it_handle, 0, 4352, -1);
      aAIGoalGotoObject(Object_handles[57], event_data->it_handle, 0, 4352, -1);
      aAIGoalFollowPath(data->me_handle, Path_indexes[15], 1, 8, 1, 3, 4352, 12);
      aSetLevelTimer(1.000000f, 20);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 089: Command Base Alerted
    if ((ScriptActionCtr_089 < 1) && (event_data->goal_uid == 12)) {
      aShowHUDMessage(Message_strings[13]);
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aObjPlayAnim(Object_handles[58], 0, 25, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], Object_handles[58], 1.000000f);
      aSetLevelTimer(4.000000f, 13);
      aObjGhostSet(0, Object_handles[12]);
      aAISetState(1, Object_handles[12]);
      aAIGoalGotoObject(Object_handles[12], Object_handles[59], 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_098A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 097: Tank Patrol
    if (1) {
      aAIGoalFollowPath(data->me_handle, Path_indexes[16], 1, 11, 1, 0, 8392704, -1);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08AA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 003: D1 Patrol
    if (1) {
      aAIGoalFollowPath(Object_handles[61], Path_indexes[17], 1, 7, 1, 3, 8392704, -1);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18BF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 099: Setup D1 Ground Guard
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }

    // Script 100: Setup Hangar Guard
    if (1) {

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 032: D1 Ground Guard Spotted Player
    if ((ScriptActionCtr_032 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aAIGoalGotoObject(data->me_handle, Object_handles[63], 3, 4352, 7);
      aSetLevelTimer(1.000000f, 12);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 035: D1 Ground Guard Has Alerted Guard Tower
    if ((ScriptActionCtr_035 < 1) && (event_data->goal_uid == 7)) {
      aShowHUDMessage(Message_strings[17]);
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aObjPlayAnim(Object_handles[63], 0, 25, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], Object_handles[63], 1.000000f);
      aSetLevelTimer(4.000000f, 13);
      aObjGhostSet(0, Object_handles[11]);
      aAISetState(1, Object_handles[11]);
      aAIGoalGotoObject(Object_handles[11], Object_handles[66], 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }

    // Script 023: D1 Ground Guard Finished Path A
    if (event_data->goal_uid == 1) {
      aSetLevelTimer(10.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 025: D1 Ground Guard Finished Path B
    if (event_data->goal_uid == 2) {
      aSetLevelTimer(8.000000f, 6);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 027: D1 Ground Guard Finished Path C
    if (event_data->goal_uid == 3) {
      aSetLevelTimer(10.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10C0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 033: Hanger Guard Spotted Player
    if ((ScriptActionCtr_033 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aAIGoalGotoObject(data->me_handle, Object_handles[65], 3, 4352, 6);
      aSetLevelTimer(1.000000f, 18);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 034: Hanger Guard Has Alerted Guard Tower
    if ((ScriptActionCtr_034 < 1) && (event_data->goal_uid == 6)) {
      aShowHUDMessage(Message_strings[16]);
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aObjPlayAnim(Object_handles[65], 0, 25, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], Object_handles[65], 1.000000f);
      aSetLevelTimer(4.000000f, 13);
      aObjGhostSet(0, Object_handles[10]);
      aAISetState(1, Object_handles[10]);
      aAIGoalGotoObject(Object_handles[10], Object_handles[66], 3, 4352, -1);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 029: Hanger Guard Finished Forward Path
    if (event_data->goal_uid == 4) {
      aSetLevelTimer(5.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 031: Hanger Guard Finished Reverse Path
    if (event_data->goal_uid == 5) {
      aSetLevelTimer(10.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2904::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 059: Crashed Cargo Ship Destroyed
    if (1) {
      aObjGhostSet(0, Object_handles[39]);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3088::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Player picks up Data Vault key
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aDoorLockUnlock(0, Door_handles[0]);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[5], event_data->it_handle, 1.000000f);
      aShowHUDMessage(Message_strings[20]);
      aGoalCompleted(Goal_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2105::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Player obtains Data Interface Dongle
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aUserFlagSet(2, 1);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[5], event_data->it_handle, 1.000000f);
      aShowHUDMessage(Message_strings[21]);
      aGoalCompleted(Goal_indexes[6], 1);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3092::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Player unlocks Hanger Door
    if ((ScriptActionCtr_014 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[4], Object_handles[80], 1.000000f);
      aShowHUDMessage(Message_strings[22]);
      aDoorLockUnlock(0, Door_handles[1]);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_187C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Security Log obtained from Data Arm
    if ((ScriptActionCtr_060 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[23], Message_strings[24]);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: Mem Plasma Info obtained from Data Arm
    if ((ScriptActionCtr_041 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[25], Message_strings[26]);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0903::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Uplink Control Directives obtained from Data Arm
    if ((ScriptActionCtr_063 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[27], Message_strings[28]);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1902::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Uplink Center Instructions obtained from Data Arm
    if ((ScriptActionCtr_062 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[29], Message_strings[30]);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_4047::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Prep Instructions obtained from Data Arm
    if ((ScriptActionCtr_004 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[31], Message_strings[32]);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_289B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Player Entered Initialization Hub
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qUserFlag(2) == true) {
        if (qUserFlag(0) == false) {
          aObjSaveHandle(event_data->it_handle, 0);
          aUserFlagSet(0, 1);
          aShowHUDMessage(Message_strings[33]);
          aGoalCompleted(Goal_indexes[7], 1);
          aSetLevelTimer(1.000000f, 9);
          aCinematicIntro(Path_indexes[23], Message_strings[34], Object_handles[33], Path_indexes[24], 9.000000f);
        }
      } else {
        if (qUserFlag(8) == false) {
          aShowHUDMessage(Message_strings[35]);
          aUserFlagSet(8, 1);
          aSetLevelTimer(3.000000f, 10);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3849::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Toggle Uplink Plasma Supply
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(5) == true) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aUserFlagSet(5, 0);
          aShowHUDMessage(Message_strings[36]);
          aTurnOffSpew(2);
          aGoalCompleted(Goal_indexes[2], 0);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aUserFlagSet(5, 1);
          aShowHUDMessage(Message_strings[37]);
          aTurnOnSpew(Object_handles[38], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.150000f, -1.000000f,
                      4.000000f, 20.000000f, 1, 2);
          aGoalCompleted(Goal_indexes[2], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_184B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Toggle Memory Plasma Generation
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(4) == true) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[1]);
          aUserFlagSet(4, 0);
          aShowHUDMessage(Message_strings[38]);
          aTurnOffSpew(0);
          aGoalCompleted(Goal_indexes[1], 0);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[1]);
          aUserFlagSet(4, 1);
          aShowHUDMessage(Message_strings[39]);
          aTurnOnSpew(Object_handles[37], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.150000f, -1.000000f,
                      4.000000f, 20.000000f, 1, 0);
          aGoalCompleted(Goal_indexes[1], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_204A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Toggle Nano Plasma Defenses
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(3) == true) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aUserFlagSet(3, 0);
          aShowHUDMessage(Message_strings[40]);
          aMatcenSetEnableState(0, Matcen_indexes[10]);
          aMatcenSetEnableState(0, Matcen_indexes[11]);
          aMatcenSetEnableState(0, Matcen_indexes[12]);
          aTurnOffSpew(1);
          aGoalCompleted(Goal_indexes[8], 1);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aUserFlagSet(3, 1);
          aShowHUDMessage(Message_strings[41]);
          aMatcenSetEnableState(1, Matcen_indexes[10]);
          aMatcenSetEnableState(1, Matcen_indexes[11]);
          aMatcenSetEnableState(1, Matcen_indexes[12]);
          aTurnOnSpew(Object_handles[36], -1, 1, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.150000f, -1.000000f,
                      4.000000f, 20.000000f, 1, 1);
          aGoalCompleted(Goal_indexes[8], 0);
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

int16_t CustomObjectScript_2064::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Toggle Foyer Matcen1 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(10) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[2]);
          aUserFlagSet(10, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[2]);
          aUserFlagSet(10, 0);
          aShowHUDMessage(Message_strings[43]);
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

int16_t CustomObjectScript_1065::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: Toggle Foyer Matcen2 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(11) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[3]);
          aUserFlagSet(11, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[3]);
          aUserFlagSet(11, 0);
          aShowHUDMessage(Message_strings[43]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2063::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Toggle HD Matcen1 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(12) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[4]);
          aUserFlagSet(12, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[4]);
          aUserFlagSet(12, 0);
          aShowHUDMessage(Message_strings[43]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_5843::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Toggle HD Matcen2 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(13) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[5]);
          aUserFlagSet(13, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[5]);
          aUserFlagSet(13, 0);
          aShowHUDMessage(Message_strings[43]);
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

int16_t CustomObjectScript_1095::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Toggle Aux Matcen1 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(14) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[6]);
          aUserFlagSet(14, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[6]);
          aUserFlagSet(14, 0);
          aShowHUDMessage(Message_strings[43]);
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

int16_t CustomObjectScript_1094::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Toggle Aux Matcen2 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(15) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[7]);
          aUserFlagSet(15, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[7]);
          aUserFlagSet(15, 0);
          aShowHUDMessage(Message_strings[43]);
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

int16_t CustomObjectScript_1080::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Toggle Prep Matcen1 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(16) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[8]);
          aUserFlagSet(16, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[8]);
          aUserFlagSet(16, 0);
          aShowHUDMessage(Message_strings[43]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_187F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Toggle Prep Matcen2 Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(17) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(1, Matcen_indexes[9]);
          aUserFlagSet(17, 1);
          aShowHUDMessage(Message_strings[42]);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aMatcenSetState(0, Matcen_indexes[9]);
          aUserFlagSet(17, 0);
          aShowHUDMessage(Message_strings[43]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_501A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Toggle Uplink Power
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == false)) {
      if (qUserFlag(6) == true) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aUserFlagSet(6, 0);
          aShowHUDMessage(Message_strings[44]);
          aGoalCompleted(Goal_indexes[0], 0);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
          aUserFlagSet(6, 1);
          aShowHUDMessage(Message_strings[45]);
          aGoalCompleted(Goal_indexes[0], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_D80D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Uplink Activation Switch
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(6) == true) {
        if (qUserFlag(7) == false) {
          aObjPlayAnim(Object_handles[91], 0, 3, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aShowHUDMessage(Message_strings[46]);
          aUserFlagSet(7, 1);
          aGoalCompleted(Goal_indexes[9], 1);
        }
      } else {
        aShowHUDMessage(Message_strings[47]);
        if (qGoalEnabled(Goal_indexes[0]) == false) {
          aGoalEnableDisable(1, Goal_indexes[0]);
        }
        if (qGoalEnabled(Goal_indexes[9]) == false) {
          aGoalEnableDisable(1, Goal_indexes[9]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Player Entered Data Uplink Center
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(9) == false)) {
      if (qUserFlag(3) == false) {
        if (qUserFlag(2) == true) {
          if (qUserFlag(0) == true) {
            if (qUserFlag(7) == true) {
              if (qUserFlag(5) == true) {
                if ((qUserFlag(1) == true) && (event_data->it_handle == qObjSavedHandle(2))) {
                  aUserFlagSet(9, 1);
                  aMatcenSetEnableState(0, Matcen_indexes[19]);
                  aTogglePlayerObjAllControls(0, event_data->it_handle);
                  aObjSaveHandle(event_data->it_handle, 1);
                  aShowHUDMessage(Message_strings[48]);
                  aGoalCompleted(Goal_indexes[10], 1);
                  aSetLevelTimer(2.000000f, 1);
                } else {
                  if (qUserFlag(8) == false) {
                    aShowHUDMessage(Message_strings[49]);
                    aUserFlagSet(8, 1);
                    aSetLevelTimer(3.000000f, 10);
                  }
                  if (qGoalEnabled(Goal_indexes[1]) == false) {
                    aGoalEnableDisable(1, Goal_indexes[1]);
                  }
                  if (qGoalEnabled(Goal_indexes[11]) == 0) {
                    aGoalEnableDisable(1, Goal_indexes[11]);
                  }
                }
              } else {
                if (qUserFlag(8) == false) {
                  aShowHUDMessage(Message_strings[50]);
                  aUserFlagSet(8, 1);
                  aSetLevelTimer(3.000000f, 10);
                }
                if (qGoalEnabled(Goal_indexes[2]) == false) {
                  aGoalEnableDisable(1, Goal_indexes[2]);
                }
              }
            } else {
              if (qUserFlag(8) == false) {
                aShowHUDMessage(Message_strings[51]);
                aUserFlagSet(8, 1);
                aSetLevelTimer(3.000000f, 10);
              }
              if (qGoalEnabled(Goal_indexes[9]) == 0) {
                aGoalEnableDisable(1, Goal_indexes[9]);
              }
            }
          } else {
            if (qUserFlag(8) == false) {
              aShowHUDMessage(Message_strings[52]);
              aUserFlagSet(8, 1);
              aSetLevelTimer(3.000000f, 10);
            }
          }
        } else {
          if (qUserFlag(8) == false) {
            aShowHUDMessage(Message_strings[53]);
            aUserFlagSet(8, 1);
            aSetLevelTimer(3.000000f, 10);
          }
        }
      } else {
        if (qUserFlag(8) == false) {
          aShowHUDMessage(Message_strings[54]);
          aUserFlagSet(8, 1);
          aSetLevelTimer(3.000000f, 10);
        }
        if (qGoalEnabled(Goal_indexes[8]) == false) {
          aGoalEnableDisable(1, Goal_indexes[8]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_208B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Player picks up Memory Plasma Blob
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjGhostSet(1, Object_handles[0]);
      if (qUserFlag(4) == true) {
        aMatcenSetState(1, Matcen_indexes[1]);
      }
      aUserVarSet(4, qMathSubFloat(40.000000f, qMathMulFloat(5.000000f, qMathIntToFloat(qGetDifficulty()))));
      aShowHUDMessageI(Message_strings[55], qUserVarValueInt(4));
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);
      aUserFlagSet(1, 1);
      aUserVarInc(0);
      aObjSaveHandle(event_data->it_handle, 2);
      aSetLevelTimer(qUserVarValue(4), 2);
      aGoalCompleted(Goal_indexes[11], 1);
      aTimerShow(2);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2074::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 102: Setup Hangar Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 110: Hangar Cam Saw Player
    if ((ScriptActionCtr_110 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(18) == false) &&
         ((qObjExists(Object_handles[5]) == true) || (qObjExists(Object_handles[6]) == true) ||
          (qObjExists(Object_handles[7]) == true) || (qObjExists(Object_handles[8]) == true)))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[5]);
      aAISetState(1, Object_handles[6]);
      aAISetState(1, Object_handles[7]);
      aAISetState(1, Object_handles[8]);
      aUserFlagSet(18, 1);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_203D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 103: Setup Prep Room Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 111: Prep Room Cam Saw Player
    if ((ScriptActionCtr_111 < 1) && ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(20) == false) &&
                                      (qObjExists(Object_handles[20]) == true))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[20]);
      aUserFlagSet(20, 1);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11B1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 104: Setup Mem Plasma Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 112: Mem Plasma Cam Saw Player
    if ((ScriptActionCtr_112 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(21) == false) &&
         ((qObjExists(Object_handles[21]) == true) || (qObjExists(Object_handles[22]) == true) ||
          (qObjExists(Object_handles[23]) == true) || (qObjExists(Object_handles[24]) == true)))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[22]);
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[24]);
      aUserFlagSet(21, 1);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3898::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 106: Setup Corridor Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 113: Corridor Cam Saw Player
    if ((ScriptActionCtr_113 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(22) == false) &&
         ((qObjExists(Object_handles[25]) == true) || (qObjExists(Object_handles[26]) == true)))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[26]);
      aUserFlagSet(22, 1);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_303C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 107: Setup Substation 1 Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 114: Substation 1 Cam Saw Player
    if ((ScriptActionCtr_114 < 1) && ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(23) == false) &&
                                      (qObjExists(Object_handles[27]) == true))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[27]);
      aUserFlagSet(23, 1);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2090::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 108: Setup Auxillary Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 115: Auxillary Cam Saw Player
    if ((ScriptActionCtr_115 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(24) == false) &&
         ((qObjExists(Object_handles[28]) == true) || (qObjExists(Object_handles[29]) == true) ||
          (qObjExists(Object_handles[30]) == true)))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[28]);
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[30]);
      aUserFlagSet(24, 1);

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09D4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 109: Setup Control Cam
    if (1) {
      aObjPlayAnim(data->me_handle, 0, 20, 14.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  case EVT_AIN_SEEPLAYER: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_seeplayer;

    // Script 116: Control Cam Saw Player
    if ((ScriptActionCtr_116 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(25) == false) &&
         ((qObjExists(Object_handles[31]) == true) || (qObjExists(Object_handles[32]) == true)))) {
      aShowHUDMessageObj(Message_strings[58], event_data->it_handle);
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aUserFlagSet(25, 1);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1050::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 126: Hangar Turret 1 Hit by Player
    if ((ScriptActionCtr_126 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(18) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[5]);
      aAISetState(1, Object_handles[6]);
      aAISetState(1, Object_handles[7]);
      aAISetState(1, Object_handles[8]);
      aUserFlagSet(18, 1);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2044::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 127: Hangar Turret 2 Hit by Player
    if ((ScriptActionCtr_127 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(18) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[5]);
      aAISetState(1, Object_handles[6]);
      aAISetState(1, Object_handles[7]);
      aAISetState(1, Object_handles[8]);
      aUserFlagSet(18, 1);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1845::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 128: Hangar Turret 3 Hit by Player
    if ((ScriptActionCtr_128 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(18) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[5]);
      aAISetState(1, Object_handles[6]);
      aAISetState(1, Object_handles[7]);
      aAISetState(1, Object_handles[8]);
      aUserFlagSet(18, 1);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1058::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 129: Hangar Turret 4 Hit by Player
    if ((ScriptActionCtr_129 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(18) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[5]);
      aAISetState(1, Object_handles[6]);
      aAISetState(1, Object_handles[7]);
      aAISetState(1, Object_handles[8]);
      aUserFlagSet(18, 1);

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 130: Prep Room Turret Hit by Player
    if ((ScriptActionCtr_130 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(20) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[20]);
      aUserFlagSet(18, 1);

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11AF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 131: Mem Plasma Turret 1 Hit by Player
    if ((ScriptActionCtr_131 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(21) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[22]);
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[24]);
      aUserFlagSet(21, 1);

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_49B0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 132: Mem Plasma Turret 2 Hit by Player
    if ((ScriptActionCtr_132 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(21) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[22]);
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[24]);
      aUserFlagSet(21, 1);

      // Increment the script action counter
      if (ScriptActionCtr_132 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_132++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11D2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 133: Mem Plasma Turret 3 Hit by Player
    if ((ScriptActionCtr_133 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(21) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[22]);
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[24]);
      aUserFlagSet(21, 1);

      // Increment the script action counter
      if (ScriptActionCtr_133 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_133++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09D5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 134: Mem Plasma Turret 4 Hit by Player
    if ((ScriptActionCtr_134 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(21) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[21]);
      aAISetState(1, Object_handles[22]);
      aAISetState(1, Object_handles[23]);
      aAISetState(1, Object_handles[24]);
      aUserFlagSet(21, 1);

      // Increment the script action counter
      if (ScriptActionCtr_134 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_134++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18A5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 135: Corridor Turret 1 Hit by Player
    if ((ScriptActionCtr_135 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(22) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[26]);
      aUserFlagSet(22, 1);

      // Increment the script action counter
      if (ScriptActionCtr_135 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_135++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 136: Corridor Turret 2 Hit by Player
    if ((ScriptActionCtr_136 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(22) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[25]);
      aAISetState(1, Object_handles[26]);
      aUserFlagSet(22, 1);

      // Increment the script action counter
      if (ScriptActionCtr_136 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_136++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19A2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 137: Substation 1 Turret Hit by Player
    if ((ScriptActionCtr_137 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(23) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[27]);
      aUserFlagSet(23, 1);

      // Increment the script action counter
      if (ScriptActionCtr_137 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_137++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 138: Auxillary Turret 1 Hit by Player
    if ((ScriptActionCtr_138 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(24) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[28]);
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[30]);
      aUserFlagSet(24, 1);

      // Increment the script action counter
      if (ScriptActionCtr_138 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_138++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 139: Auxillary Turret 2 Hit by Player
    if ((ScriptActionCtr_139 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(24) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[28]);
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[30]);
      aUserFlagSet(24, 1);

      // Increment the script action counter
      if (ScriptActionCtr_139 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_139++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 140: Auxillary Turret 3 Hit by Player
    if ((ScriptActionCtr_140 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(24) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[28]);
      aAISetState(1, Object_handles[29]);
      aAISetState(1, Object_handles[30]);
      aUserFlagSet(24, 1);

      // Increment the script action counter
      if (ScriptActionCtr_140 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_140++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 141: Control Turret 1 Hit by Player
    if ((ScriptActionCtr_141 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(25) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aUserFlagSet(25, 1);

      // Increment the script action counter
      if (ScriptActionCtr_141 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_141++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 142: Control Turret 2 Hit by Player
    if ((ScriptActionCtr_142 < 1) &&
        ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(25) == false))) {
      aShowHUDMessage(Message_strings[5]);
      aAISetState(1, Object_handles[31]);
      aAISetState(1, Object_handles[32]);
      aUserFlagSet(25, 1);

      // Increment the script action counter
      if (ScriptActionCtr_142 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_142++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_187E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: Player Picks Up Camera Monitor
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aSoundPlayObject(Sound_indexes[5], event_data->it_handle, 1.000000f);
      aShowHUDMessageObj(Message_strings[59], event_data->it_handle);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aObjSaveHandle(event_data->it_handle, 5);
      aUserFlagSet(26, 1);
      aUserFlagSet(27, 1);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 064: Player Used Camera Monitor
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjGhostSet(0, data->me_handle);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      if (qUserFlag(27) == true) {
        aShowHUDMessageObj(Message_strings[60], event_data->it_handle);
        aUserFlagSet(27, 0);
      } else {
        aShowHUDMessageObj(Message_strings[61], event_data->it_handle);
        aUserFlagSet(27, 1);
      }
      aSoundPlay2DObj(Sound_indexes[8], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_987D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 118: Player picks up Crashed Ship Log
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[5], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[62], Message_strings[63]);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09AA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 119: Meteor1 - GoalID Explosion
    if (1) {
      aTurnOnSpew(Object_handles[109], -1, 0, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.040000f, 1.000000f,
                  30.000000f, 80.000000f, 1, -1);
      aTurnOffSpew(3);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }
  } break;
  case EVT_CHILD_DIED: {
    tOSIRISEVTCHILDDIED *event_data = &data->evt_child_died;

    // Script 117: Meteor1 - Path
    if (qObjIsType(Object_handles[61], 2) == false) {
      aAISetMaxSpeed(data->me_handle, 400.000000f);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[27], 4096, 14, 3);
      aTurnOnSpew(data->me_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 4.500000f, 0.010000f, 30.000000f, 4.500000f,
                  60.000000f, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0816::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 147: Locked Door - No Entry Message
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[64]);

      // Increment the script action counter
      if (ScriptActionCtr_147 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_147++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 105: Player Enters Data Vault - Trigger Vault1
    if ((ScriptActionCtr_105 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[4], 1);
      aSetLevelTimer(4.000000f, 14);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }

    // Script 079: Music-MainHub-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 075: Music-RightArm-2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music-RightArm-1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Music-LowerEnd-2
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 084: Music-LowerEnd-1
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Music-MidSection-4
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: Music-MidSection-3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Music-MidSection-2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Music-MidSection-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: Music-MainHub-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Music-Outside-2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

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

    // Script 076: Music-Outside-1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
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
NEXT_ID		150

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:NumMemPlasmaCharges
1:TempValue
2:CameraPopupViewDisplayed
3:BaseAlertLevel
4:MemPlasmaChargeTime
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:InterfaceInitialized
1:MemoryPlasmaChargeActive
2:InterfaceObtained
3:NanoPlasmaDefensesOn
4:MemoryPlasmaGenerationOn
5:UplinkPlasmaSupplyOn
6:UplinkControlPowerOn
7:UplinkActivated
8:MessageDelayActive
9:DockedWithUplink
10:FoyerMatcen1Active
11:FoyerMatcen2Active
12:HDMatcen1Active
13:HDMatcen2Active
14:AuxMatcen1Active
15:AuxMatcen2Active
16:PrepMatcen1Active
17:PrepMatcen2Active
18:HangarTurretsActive
19:Waypoint2Set
20:PrepRoomTurretsActive
21:MemPlasmaTurretsActive
22:CorridorTurretsActive
23:Substation1TurretsActive
24:AuxillaryTurretsActive
25:ControlTurretsActive
26:CamMonitorObtained
27:CamMonitorOn
28:DataVaultTurretsActive
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:Memory Plasma Spew
1:Nano Plasma Spew
2:Uplink Plasma Spew
3:Meteor1
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:JuggPatrol1
1:EndLevel
2:MemPlasmaChargeExpired
3:ShowJuggWarning
4:StartD1GroundPathA
5:StartD1GroundPathB
6:StartD1GroundPathC
7:StartHangerFwdPath
8:StartHangerRevPath
9:PrepInitLightning
10:ClearMessageDelay
11:DoUploadingEffect
12:ShowMineGuardMsg
13:AlertTheBase
14:CompleteEnterBaseObj
15:CheckIfPlayerIsInBigGunSights
16:CheckWaypoint2Cam
17:MonitorCamGroupA
18:ShowHangerGuardMsg
19:ShowCanyonGuardMsg
20:ShowCmdBaseGuardMsg
21:ShowDVGuardMsg
22:ShowJuggGuardMsg
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:PrepInitObject
1:UploadObject
2:MemPlasmaChargedObject
3:BigGunTarget
4:ClosestPlayer
5:PlayerWithCamMonitor
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:JuggAlertBase
1:D1GuardFinishedPathA
2:D1GuardFinishedPathB
3:D1GuardFinishedPathC
4:HangerGuardFinishedFwdPath
5:HangerGuardFinishedRevPath
6:GuardTowerAlertedByHG
7:GuardTowerAlertedByGG
8:TankerFinishedLandingPathA
9:TankerHasLandedCompletely
10:TankerFinishedLandingPathB
11:CanyonGuardRetreated
12:CmdBaseAlerted
13:DVTowerAlerted
14:Meteor1End
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
Datavault Door
Base Access Door
$$DOOR_LIST_END

$$OBJECT_LIST_START
Memory Plasma Blob
Vault HangTurr1
Vault HangTurr2
Vault Turr3
Vault Turr4
Hanger Swatter1
Hanger Swatter2
Hanger Swatter3
Hanger Swatter4
HoodReinforcementA
HoodReinforcementB
HoodAmbushGT
HoodAmbushCB
HoodAmbushDV
CanyonAmbushA
CanyonAmbushB
CanyonAmbushC
PitAmbushA
PitAmbushB
PitAmbushC
PrepRoomTurret1
MemPlasmaTurret1
MemPlasmaTurret2
MemPlasmaTurret3
MemPlasmaTurret4
CorridorTurret1
CorridorTurret2
Substation1Turret1
AuxillaryTurret1
AuxillaryTurret2
AuxillaryTurret3
ControlTurret1
ControlTurret2
InitializationHub
DataUplinkCenter
TankerLandPoint
Nano Cooker Spew
Memory Spew
Interface Spew
Interface Dongle
Fuel Tanker
Hood Patrol1
SkyPatrol2
TrappedMega
DVPatrolA
DVPatrolB
DVGuard
DVGuardBeacon
HoodAmbushDVDest
BigGunCam
BigGunTargetCam
JuggGuard
JuggAlertBeacon
HoodReinforceADest
CanyonGuard
CmdBaseGuard
BaseAmbushA
BaseAmbushB
CmdBaseBeacon
HoodAmbushCBDest
TankPatrol
D1 Patrol Leader
D1 Ground Guard
MineGuardBeacon
Hanger Guard
HangarGuardBeacon
HoodReinforceBDest
Interface Power Sw
Foyer Matcen1 Sw
Prep Matcen1 Sw
Memory Plasma Swit
Aux Matcen1 Sw
HD Matcen1 Sw
Uplink Plasma Swit
HD Matcen2 Sw
Aux Matcen2 Sw
Foyer Matcen2 Sw
Prep Matcen2 Sw
CrashedCargoShip
Vault Key
Hanger Door Switch
Hanger Data Link
MemPlasmaDataArm
UplinkControlDataA
UplinkCenterDataAr
Prep Room DataArm
PrepInitCamA
PrepInitCamB
PrepInitCamC
PrepInitCamD
Nano Plasma Switch
Interface Switch
Waypoint2Cam
Uplink Upper Cam
Uplink Lower Cam
UplinkCamA
UplinkCamB
UplinkCamC
UplinkCamD
Hanger Wall Cam
Prep Room Cam
Mem Plasma Cam
Corridor Cam
Substation 1 Cam
Auxillary Cam
Control Cam
Camera Monitor
Crashed Ship Log
Meteor1
Meteor1Explosion
A Door FoyerMatcen
$$OBJECT_LIST_END

$$ROOM_LIST_START
Hanger Portal
Foyer
DataStow Room
Interface Obs Acce
Main Hall
Main Hanger
Prep Room
Mem Plasma Room
Mem Plasma Room 2
Maintenance Room
Mem Plasma Doorway
Differential Room
Corridor Cam Room
Substation1
Workstation Access
Auxillary Control
Interface Control
Data Uplink Room
Control Door Room
$$ROOM_LIST_END

$$TRIGGER_LIST_START
MMainHub-2
MRightArm-2
MRightArm-1
MLowerEnd-2
MLowerEnd-1
MMidSection-4
MMidSection-3
MMidSection-2
MMidSection-1
MMainHub-1
MOutside-2
MOutside1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
PlayerSpotted
BaseAlertedSiren
AmbSwitch11
Lev10Laser
AmbSwitch31
Powerup pickup
MemPlasmaChargeOn
MemPlasmaChargeOff
HudMessage
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffect7
FunkyEffect4
FunkyEffect3
FunkyEffect2
FunkyEffect5
Lightning3
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
LandingCamPathA
LandingCamPathB
NewPlayerIntroCamPath
NewPlayerIntroPath
IntroLandingPath
IntroLandingPathB
Space Patrol
SkyPatrol2
DVPatrolA
DVPatrolB
DVGuardPath
Jugg Alerted Path
CanyonGuardStation
CanyonGuardPath
CmdBaseGuardPath
CmdBaseDestPath
TankPatrol
D1PatrolPath
D1 Ground Path A
D1 Ground Path B
D1 Ground Path C
Hanger Patrol Path
Hanger Patrol Path 2
PrepInitCam
PlayerInitPath
NewUplinkCamPath
UplinkPlayerPath
Meteor1
$$PATH_LIST_END

$$MATCEN_LIST_START
Central Matcen
MemPlasmaMatcen
Foyer Matcen1
Foyer Matcen2
HD Matcen1
HD Matcen2
Aux Matcen1
Aux Matcen2
Prep Matcen1
Prep Matcen2
Nano Matcen1
Nano Matcen2
Nano Matcen3
StorageRoomXMatcen
BigRoomXMatcen1
FoyerXMatcen
FoyerXMatcen2
MainHallXMatcen1
MainHallXMatcen2
Temp Bolt
$$MATCEN_LIST_END

$$GOAL_LIST_START
Enable Uplink Control Power
Enable Memory Plasma Generation
Activate Uplink Plasma Supply
Obtain a Data Vault Key
Enter through the Data Vault
Infiltrate the Lunar Command Center
Acquire a Data Interface
Initialize Data Interface
Disable Nano Plasma Defenses
Activate Uplink Docking Control
Connect to Data Uplink
Acquire Memory Plasma Charge
Upload Virus Information
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxLev10StartLevel.osf
VoxLev10EndLevel.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Level Start - Init Variables/Flags
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        06:qMathSubFloat:value
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Float1
                                06:qMathMulFloat:Float2
                                        $$CHILD_BLOCK_START
                                        10:6:5.000000:Float1
                                        06:qMathIntToFloat:Float2
                                                $$CHILD_BLOCK_START
                                                06:qGetDifficulty:Int
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
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
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:1:True/False
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
                        10:10:0:19:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:27:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
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
                        10:10:0:24:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:25:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:28:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Level Start - Init Matcens
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:4:Matcen
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:7:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:8:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:9:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:10:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:11:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:17:0:12:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Level Start - Init AI
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:19:Object
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
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
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
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Level Start - Init Misc
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:0:DoorName
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:-1:GunNum
                        10:10:0:1:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:1.400000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.400000:Time
                        10:10:0:17:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:148:Level Start - Init Base Alert Display
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aInitBaseAlertDisplay
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Level Start - Intro Cinematic
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCloakAllPlayers
                        $$CHILD_BLOCK_START
                        10:6:25.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aComplexCinematicStart
                08:aComplexCinematicTrack
                        $$CHILD_BLOCK_START
                        10:1:0:40:Target
                        10:9:0.000000:Start
                        10:9:1.000000:End
                        $$CHILD_BLOCK_END
                08:aComplexCinematicStartTrans
                        $$CHILD_BLOCK_START
                        10:5:1:Enable
                        $$CHILD_BLOCK_END
                08:aComplexCinematicCameraOnPath
                        $$CHILD_BLOCK_START
                        10:16:0:Path
                        $$CHILD_BLOCK_END
                08:aComplexCinematicEnd
                        $$CHILD_BLOCK_START
                        10:8:Empty:Text
                        10:6:9.500000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Intro Cinematic - Parts II and III
        $$CHILD_BLOCK_START
        01:1:40
        02:18
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
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:40:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aComplexCinematicStart
                        08:aComplexCinematicTrack
                                $$CHILD_BLOCK_START
                                10:1:0:40:Target
                                10:9:0.000000:Start
                                10:9:1.000000:End
                                $$CHILD_BLOCK_END
                        08:aComplexCinematicStartTrans
                                $$CHILD_BLOCK_START
                                10:5:1:Enable
                                $$CHILD_BLOCK_END
                        08:aComplexCinematicCameraOnPath
                                $$CHILD_BLOCK_START
                                10:16:1:Path
                                $$CHILD_BLOCK_END
                        08:aComplexCinematicEnd
                                $$CHILD_BLOCK_START
                                10:8:Empty:Text
                                10:6:9.000000:Seconds
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:40:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicIntro
                                $$CHILD_BLOCK_START
                                10:16:2:CameraPath
                                10:8:IntroText:Text
                                10:1:2:-1:TotallyNotUsedTarget
                                10:16:3:PlayerPath
                                10:6:12.000000:Seconds
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:0:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Intro Landing Path
        $$CHILD_BLOCK_START
        01:1:40
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:4:Path
                        10:4:1:FirstNode
                        10:4:4:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:131328:AIGoalFlags
                        10:10:0:8:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Set Fuel Tanker Landing Path B
        $$CHILD_BLOCK_START
        01:1:40
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:5:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:131328:AIGoalFlags
                        10:10:0:10:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Land the Fuel Tanker
        $$CHILD_BLOCK_START
        01:1:40
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalLandOnObject
                        $$CHILD_BLOCK_START
                        10:1:0:40:LandingObject
                        10:4:0:LanderAttachPoint
                        10:1:0:35:ObjectToLandOn
                        10:4:0:LandOnObjectAttachPoint
                        10:10:0:3:GoalPriority
                        10:15:131328:AIGoalFlags
                        10:10:0:9:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Fuel Tanker has Landed
        $$CHILD_BLOCK_START
        01:1:40
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
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Space Patrol
        $$CHILD_BLOCK_START
        01:1:41
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32:AIFlags
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:6:Path
                        10:4:1:FirstNode
                        10:4:11:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:Sky Patrol 2
        $$CHILD_BLOCK_START
        01:1:42
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32:AIFlags
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:7:Path
                        10:4:1:FirstNode
                        10:4:14:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Mega Trap Setoff
        $$CHILD_BLOCK_START
        01:1:43
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZMegaTrap:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:1:1:-1:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:1:1:-1:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:1:1:-1:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Data Vault Patrol A
        $$CHILD_BLOCK_START
        01:1:44
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:70.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:8:Path
                        10:4:1:FirstNode
                        10:4:4:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Data Vault Patrol B
        $$CHILD_BLOCK_START
        01:1:45
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:70.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:9:Path
                        10:4:1:FirstNode
                        10:4:8:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Data Vault Guard Patrol
        $$CHILD_BLOCK_START
        01:1:46
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:10:Path
                        10:4:1:FirstNode
                        10:4:4:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Data Vault Guard Spotted Player
        $$CHILD_BLOCK_START
        01:1:46
        02:11
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
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:0:47:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:13:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:21:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:Show Data Vault Guard Spotted Msg
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
                                10:10:0:21:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:46:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:94:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZDVSpotted:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Data Vault Alerted
        $$CHILD_BLOCK_START
        01:1:46
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZDVAlerted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:4:0:StartFrame
                        10:4:25:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:47:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:28:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:1:0:48:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:143:Data Vault Turret 1 Hit by Player
        $$CHILD_BLOCK_START
        01:1:1
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
                                        10:10:0:28:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:28:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:144:Data Vault Turret 2 Hit by Player
        $$CHILD_BLOCK_START
        01:1:2
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
                                        10:10:0:28:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:28:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:145:Data Vault Turret 3 Hit by Player
        $$CHILD_BLOCK_START
        01:1:3
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
                                        10:10:0:28:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:28:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:146:Data Vault Turret 4 Hit by Player
        $$CHILD_BLOCK_START
        01:1:4
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
                                        10:10:0:28:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:28:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Check Big Gun's Sights
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjCanSeePlayerAdvancedWithStore:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:SavedObjectSlot
                                        10:4:45:Cone
                                        10:1:0:49:Object
                                        10:6:500.000000:Distance
                                        10:15:1048585:FVIHitFlags
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:CannonHitPlayer:Message
                                        $$CHILD_BLOCK_END
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMoveObjectToPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:50:Object
                                        $$CHILD_BLOCK_END
                                08:aObjApplyDamage
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:80.000000:DamageAmount
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:49:Object1
                                        10:1:0:50:Object2
                                        10:6:0.200000:Lifetime
                                        10:6:3.000000:Thickness
                                        10:4:8:NumTiles
                                        10:14:0:Texture
                                        10:6:0.800000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        10:1:0:49:Object1
                                        10:1:0:50:Object2
                                        10:6:0.300000:Lifetime
                                        10:6:2.000000:Thickness
                                        10:4:6:NumTiles
                                        10:14:1:Texture
                                        10:6:0.500000:SlideTime
                                        10:4:1:TimesDrawn
                                        10:4:255:Red
                                        10:4:255:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:3:Sound
                                        10:1:0:49:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:5.000000:Time
                                        10:10:0:15:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:15:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Jugg Alerted Path
        $$CHILD_BLOCK_START
        01:1:51
        02:11
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:11:Path
                        10:4:1:FirstNode
                        10:4:4:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:4356:AIGoalFlags
                        10:10:0:0:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:22:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:Show Jugg Guard Spotted Msg
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
                                10:10:0:22:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:51:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:19:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:JuggSawPlayer:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Jugg Has Alerted the Base
        $$CHILD_BLOCK_START
        01:1:51
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:JuggAlertedBase:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:4:0:StartFrame
                        10:4:25:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:52:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:1:0:53:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Show Juggernaut Alert Warning
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:JuggAlertWarning:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:Canyon Guard Patrol
        $$CHILD_BLOCK_START
        01:1:54
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:12:Path
                        10:4:1:FirstNode
                        10:4:9:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Canyon Guard Damaged
        $$CHILD_BLOCK_START
        01:1:54
        02:3
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                06:qMathPercentage:Float
                                        $$CHILD_BLOCK_START
                                        10:9:0.800000:Percent
                                        06:qObjShieldsOriginal:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:65.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:13:Path
                        10:4:1:FirstNode
                        10:4:9:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:11:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:19:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:Show Canyon Guard Spotted Msg
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
                                10:10:0:19:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:54:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:87:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZCanyonRun:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Canyon Guard Retreated
        $$CHILD_BLOCK_START
        01:1:54
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qPlayerClosest:Object
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:1:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:4:SavedObjectSlot
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:500.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ZCanyonAmbush:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlay2D
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:16:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:1:0:54:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:1:0:54:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:1:0:54:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:Setup Command Base Guard
        $$CHILD_BLOCK_START
        01:1:55
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:0:Set/Clear
                        10:15:33554432:AIFlags
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:14:Path
                        10:4:1:FirstNode
                        10:4:9:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Command Base Guard Spotted Player
        $$CHILD_BLOCK_START
        01:1:55
        02:11
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
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:1:1:-1:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:1:1:-1:Target
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:15:Path
                        10:4:1:FirstNode
                        10:4:8:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:12:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:20:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:124:Show Command Base Guard Spotted Msg
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
                                10:10:0:20:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:55:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:89:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZCBNoticed:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Command Base Alerted
        $$CHILD_BLOCK_START
        01:1:55
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZCBAlerted:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:4:0:StartFrame
                        10:4:25:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:58:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:1:0:59:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:Tank Patrol
        $$CHILD_BLOCK_START
        01:1:60
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:16:Path
                        10:4:1:FirstNode
                        10:4:11:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:D1 Patrol
        $$CHILD_BLOCK_START
        01:1:61
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:16:17:Path
                        10:4:1:FirstNode
                        10:4:7:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:Setup D1 Ground Guard
        $$CHILD_BLOCK_START
        01:1:62
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:Setup Hangar Guard
        $$CHILD_BLOCK_START
        01:1:62
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:D1 Ground Guard Spotted Player
        $$CHILD_BLOCK_START
        01:1:62
        02:11
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
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:0:63:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:7:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Show D1 Ground Guard Spotted Msg
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
                                10:10:0:12:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:62:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:35:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:D1GuardSpotted:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Hanger Guard Spotted Player
        $$CHILD_BLOCK_START
        01:1:64
        02:11
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
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:0:65:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:18:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:Show Hanger Guard Spotted Msg
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
                                10:10:0:18:TimerID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:64:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:34:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:HangerGuardSpotted:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Hanger Guard Has Alerted Guard Tower
        $$CHILD_BLOCK_START
        01:1:64
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GuardTowerAlertedHG:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:0:StartFrame
                        10:4:25:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:65:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:1:0:66:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:D1 Ground Guard Has Alerted Guard Tower
        $$CHILD_BLOCK_START
        01:1:62
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GuardTowerAlertedGG:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:0:StartFrame
                        10:4:25:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:63:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoObject
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:1:0:66:Target
                        10:10:0:3:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Alert the Base
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
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
                                                10:10:0:6:UserFlag
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
                                                                10:1:0:67:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:67:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:67:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:67:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:0:LevelGoal
                                                10:10:0:0:Completed
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:68:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:68:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:68:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:68:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:2:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:10:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:69:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:69:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:69:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:69:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:8:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:16:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:13:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
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
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:70:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:70:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:70:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:70:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Activate/Deactivate
                                                10:17:0:1:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        08:aTurnOffSpew
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:1:LevelGoal
                                                10:10:0:0:Completed
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
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
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:71:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:71:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:71:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:71:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:6:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
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
                                                                10:1:0:72:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:72:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:72:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:72:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:4:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:14:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:15:Matcen
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:32:AIFlags
                                10:1:0:41:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:41:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
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
                                                10:10:0:5:UserFlag
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
                                                                10:1:0:73:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:73:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:73:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:73:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        08:aTurnOffSpew
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:SpewHandle
                                                $$CHILD_BLOCK_END
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:2:LevelGoal
                                                10:10:0:0:Completed
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
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
                                                                10:1:0:74:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:74:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:74:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:74:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:5:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:13:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:75:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:75:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:75:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:75:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:7:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:15:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:16:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
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
                                                10:10:0:11:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
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
                                                                10:1:0:76:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:76:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:76:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:76:Object
                                                10:9:1.000000:Volume
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
                                        $$CHILD_BLOCK_END
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
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:77:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:0.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:77:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:2.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:77:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:4:Sound
                                                10:1:0:77:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:9:Matcen
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:17:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:32:AIFlags
                                10:1:0:42:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:42:Object
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:4:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:17:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:18:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageI
                        $$CHILD_BLOCK_START
                        10:8:BaseAlertStatus:Message
                        06:qMathAddInt:Integer
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer1
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                10:4:1:Integer2
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUpdateBaseAlertDisplay
                        $$CHILD_BLOCK_START
                        10:8:BaseAlertDisplay:Message
                        06:qMathAddInt:AlertLevel
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer1
                                        $$CHILD_BLOCK_START
                                        10:11:45:ScriptID
                                        $$CHILD_BLOCK_END
                                10:4:1:Integer2
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Start D1 Ground Guard on Path A
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:16:18:Path
                        10:4:1:FirstNode
                        10:4:7:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:D1 Ground Guard Finished Path A
        $$CHILD_BLOCK_START
        01:1:62
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Start D1 Ground Guard on Path B
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:16:19:Path
                        10:4:1:FirstNode
                        10:4:7:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:2:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:D1 Ground Guard Finished Path B
        $$CHILD_BLOCK_START
        01:1:62
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:8.000000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Start D1 Ground Guard on Path C
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:16:20:Path
                        10:4:1:FirstNode
                        10:4:7:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:3:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:D1 Ground Guard Finished Path C
        $$CHILD_BLOCK_START
        01:1:62
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Start Hanger Guard on Forward Path
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:16:21:Path
                        10:4:1:FirstNode
                        10:4:5:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:4:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Hanger Guard Finished Forward Path
        $$CHILD_BLOCK_START
        01:1:64
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Start Hanger Guard on Reverse Path
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:16:22:Path
                        10:4:1:FirstNode
                        10:4:10:LastNode
                        10:4:1:StartNode
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:5:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Hanger Guard Finished Reverse Path
        $$CHILD_BLOCK_START
        01:1:64
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Crashed Cargo Ship Destroyed
        $$CHILD_BLOCK_START
        01:1:78
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:39:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Player picks up Data Vault key
        $$CHILD_BLOCK_START
        01:1:79
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:VaultKeyAcquired:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:Player Enters Data Vault - Trigger Vault1
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Mark Base Infiltration Objective as Complete
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Player obtains Data Interface Dongle
        $$CHILD_BLOCK_START
        01:1:39
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:InterfaceAcquired:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Player unlocks Hanger Door
        $$CHILD_BLOCK_START
        01:1:80
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
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:80:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:HangerDoorUnlocked:Message
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Security Log obtained from Data Arm
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:HangerMsgGame:GameMessage
                        10:8:HangerMsgHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Mem Plasma Info obtained from Data Arm
        $$CHILD_BLOCK_START
        01:1:82
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:MemPlasmaGame:GameMessage
                        10:8:MemPlasmaHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Uplink Control Directives obtained from Data Arm
        $$CHILD_BLOCK_START
        01:1:83
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:UplinkControlGame:GameMessage
                        10:8:UplinkControlHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Uplink Center Instructions obtained from Data Arm
        $$CHILD_BLOCK_START
        01:1:84
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:UplinkCenterGame:GameMessage
                        10:8:UplinkCenterHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Prep Instructions obtained from Data Arm
        $$CHILD_BLOCK_START
        01:1:85
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:InterfacePrepInstrGame:GameMessage
                        10:8:InterfacePrepInstHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Player Entered Initialization Hub
        $$CHILD_BLOCK_START
        01:1:33
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
                                        10:10:0:2:UserFlag
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
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:InterfaceInitialized:Message
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:7:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:1.000000:Time
                                        10:10:0:9:TimerID
                                        $$CHILD_BLOCK_END
                                08:aCinematicIntro
                                        $$CHILD_BLOCK_START
                                        10:16:23:CameraPath
                                        10:8:InitInterfaceCin:Text
                                        10:1:0:33:TotallyNotUsedTarget
                                        10:16:24:PlayerPath
                                        10:6:9.000000:Seconds
                                        $$CHILD_BLOCK_END
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
                                                10:10:0:8:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:InterfacePrepDenied:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:3.000000:Time
                                        10:10:0:10:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Create Prep Room Initialization Lightning
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:86:Object1
                                10:1:0:87:Object2
                                10:6:6.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:87:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:6.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:0:88:Object2
                                10:6:6.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:88:Object1
                                10:1:0:89:Object2
                                10:6:6.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:0:86:Object2
                                10:6:6.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:89:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:6.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.200000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:4:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:86:Object1
                                10:1:0:87:Object2
                                10:6:5.500000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:3:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:87:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:5.500000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:3:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:0:88:Object2
                                10:6:5.500000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:3:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:88:Object1
                                10:1:0:89:Object2
                                10:6:5.500000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:3:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:0:86:Object2
                                10:6:5.500000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:3:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:89:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:5.500000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:3:NumTiles
                                10:14:3:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Toggle Uplink Plasma Supply
        $$CHILD_BLOCK_START
        01:1:73
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:UplinkPlasmaOff:Message
                                        $$CHILD_BLOCK_END
                                08:aTurnOffSpew
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:SpewHandle
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
                                        10:10:0:0:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:UplinkPlasmaOn:Message
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
                                        10:6:1.400000:BlobLifetime
                                        10:6:0.150000:BlobInterval
                                        10:6:-1.000000:SpewLife
                                        10:6:4.000000:BlobSize
                                        10:6:20.000000:BlobSpeed
                                        10:5:1:Randomize
                                        10:10:0:2:SpewHandle
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Toggle Memory Plasma Generation
        $$CHILD_BLOCK_START
        01:1:70
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:1:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MemPlasmaOff:Message
                                        $$CHILD_BLOCK_END
                                08:aTurnOffSpew
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SpewHandle
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:1:LevelGoal
                                        10:10:0:0:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:1:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MemPlasmaOn:Message
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
                                        10:6:1.000000:BlobLifetime
                                        10:6:0.150000:BlobInterval
                                        10:6:-1.000000:SpewLife
                                        10:6:4.000000:BlobSize
                                        10:6:20.000000:BlobSpeed
                                        10:5:1:Randomize
                                        10:10:0:0:SpewHandle
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:1:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Toggle Nano Plasma Defenses
        $$CHILD_BLOCK_START
        01:1:90
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:NanoPlasmaDefOff:Message
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:17:0:10:Matcen
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:17:0:11:Matcen
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        10:17:0:12:Matcen
                                        $$CHILD_BLOCK_END
                                08:aTurnOffSpew
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SpewHandle
                                        $$CHILD_BLOCK_END
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:NanoPlasmaDefOn:Message
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:17:0:10:Matcen
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:17:0:11:Matcen
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:17:0:12:Matcen
                                        $$CHILD_BLOCK_END
                                08:aTurnOnSpew
                                        $$CHILD_BLOCK_START
                                        10:1:0:36:Object
                                        10:4:-1:GunNum
                                        10:10:0:1:SpewType
                                        10:6:0.000000:Mass
                                        10:6:0.000000:Drag
                                        10:15:65536:PhysicsFlags
                                        10:5:0:IsRealObject
                                        10:6:1.400000:BlobLifetime
                                        10:6:0.150000:BlobInterval
                                        10:6:-1.000000:SpewLife
                                        10:6:4.000000:BlobSize
                                        10:6:20.000000:BlobSpeed
                                        10:5:1:Randomize
                                        10:10:0:1:SpewHandle
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:8:LevelGoal
                                        10:10:0:0:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Toggle Foyer Matcen1 Switch
        $$CHILD_BLOCK_START
        01:1:68
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:2:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:2:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Toggle Foyer Matcen2 Switch
        $$CHILD_BLOCK_START
        01:1:76
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
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
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:3:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Toggle HD Matcen1 Switch
        $$CHILD_BLOCK_START
        01:1:72
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:4:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:4:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Toggle HD Matcen2 Switch
        $$CHILD_BLOCK_START
        01:1:74
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
                03:1
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:5:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:5:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Toggle Aux Matcen1 Switch
        $$CHILD_BLOCK_START
        01:1:71
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:6:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:6:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:14:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Toggle Aux Matcen2 Switch
        $$CHILD_BLOCK_START
        01:1:75
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:7:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:7:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Toggle Prep Matcen1 Switch
        $$CHILD_BLOCK_START
        01:1:69
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:8:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:8:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Toggle Prep Matcen2 Switch
        $$CHILD_BLOCK_START
        01:1:77
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:9:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:17:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenActivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Activate/Deactivate
                                        10:17:0:9:Matcen
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:17:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MatcenDeactivated:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Toggle Uplink Power
        $$CHILD_BLOCK_START
        01:1:67
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
                                        10:10:0:7:UserFlag
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
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:InterfacePowerOff:Message
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:0:LevelGoal
                                        10:10:0:0:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:4:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:InterfacePowerOn:Message
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:0:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Uplink Activation Switch
        $$CHILD_BLOCK_START
        01:1:91
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
                                                10:10:0:7:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:0:91:Object
                                        10:4:0:StartFrame
                                        10:4:3:EndFrame
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:DataUplinkActivated:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:9:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:InterfaceHasNoPower:Message
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:0:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalEnableDisable
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:18:0:0:LevelGoal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:9:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalEnableDisable
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:18:0:9:LevelGoal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Player Entered Data Uplink Center
        $$CHILD_BLOCK_START
        01:1:34
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
                                        10:10:0:9:UserFlag
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
                                        10:10:0:3:UserFlag
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
                                                10:10:0:2:UserFlag
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
                                                                10:10:0:7:UserFlag
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
                                                                        10:10:0:5:UserFlag
                                                                        $$CHILD_BLOCK_END
                                                                07:0:6
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        03:1
                                                                $$CHILD_BLOCK_START
                                                                09:0
                                                                        $$CHILD_BLOCK_START
                                                                        05:1
                                                                                $$CHILD_BLOCK_START
                                                                                06:qUserFlag:Bool
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:1:UserFlag
                                                                                        $$CHILD_BLOCK_END
                                                                                07:0:6
                                                                                $$CHILD_BLOCK_END
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                10:1:1:-1:Object
                                                                                07:1:0
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:2:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aUserFlagSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:9:UserFlag
                                                                        10:5:1:True/False
                                                                        $$CHILD_BLOCK_END
                                                                08:aMatcenSetEnableState
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:Enable/Disable
                                                                        10:17:0:19:Matcen
                                                                        $$CHILD_BLOCK_END
                                                                08:aTogglePlayerObjAllControls
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:0:Enable/Disable
                                                                        10:1:1:-1:PlayerObject
                                                                        $$CHILD_BLOCK_END
                                                                08:aObjSaveHandle
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:1:-1:Object
                                                                        10:10:0:1:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                08:aShowHUDMessage
                                                                        $$CHILD_BLOCK_START
                                                                        10:8:UplinkDocking:Message
                                                                        $$CHILD_BLOCK_END
                                                                08:aGoalCompleted
                                                                        $$CHILD_BLOCK_START
                                                                        10:18:0:10:LevelGoal
                                                                        10:10:0:1:Completed
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
                                                                        08:aShowHUDMessage
                                                                                $$CHILD_BLOCK_START
                                                                                10:8:UplinkErrorNoChg:Message
                                                                                $$CHILD_BLOCK_END
                                                                        08:aUserFlagSet
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:8:UserFlag
                                                                                10:5:1:True/False
                                                                                $$CHILD_BLOCK_END
                                                                        08:aSetLevelTimer
                                                                                $$CHILD_BLOCK_START
                                                                                10:6:3.000000:Time
                                                                                10:10:0:10:TimerID
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                03:1
                                                                        $$CHILD_BLOCK_START
                                                                        05:1
                                                                                $$CHILD_BLOCK_START
                                                                                06:qGoalEnabled:Bool
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:18:0:1:LevelGoal
                                                                                        $$CHILD_BLOCK_END
                                                                                07:0:7
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aGoalEnableDisable
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:1:Enable/Disable
                                                                                10:18:0:1:LevelGoal
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                03:1
                                                                        $$CHILD_BLOCK_START
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qGoalEnabled:Bool
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:18:0:11:LevelGoal
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:5:0:Bool
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aGoalEnableDisable
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:1:Enable/Disable
                                                                                10:18:0:11:LevelGoal
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
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
                                                                                10:10:0:8:UserFlag
                                                                                $$CHILD_BLOCK_END
                                                                        07:0:7
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aShowHUDMessage
                                                                        $$CHILD_BLOCK_START
                                                                        10:8:UplinkErrorNoPlasma:Message
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserFlagSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:8:UserFlag
                                                                        10:5:1:True/False
                                                                        $$CHILD_BLOCK_END
                                                                08:aSetLevelTimer
                                                                        $$CHILD_BLOCK_START
                                                                        10:6:3.000000:Time
                                                                        10:10:0:10:TimerID
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        03:1
                                                                $$CHILD_BLOCK_START
                                                                05:1
                                                                        $$CHILD_BLOCK_START
                                                                        06:qGoalEnabled:Bool
                                                                                $$CHILD_BLOCK_START
                                                                                10:18:0:2:LevelGoal
                                                                                $$CHILD_BLOCK_END
                                                                        07:0:7
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aGoalEnableDisable
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:1:Enable/Disable
                                                                        10:18:0:2:LevelGoal
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
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
                                                                        10:10:0:8:UserFlag
                                                                        $$CHILD_BLOCK_END
                                                                07:0:7
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aShowHUDMessage
                                                                $$CHILD_BLOCK_START
                                                                10:8:UplinkErrorNotAct:Message
                                                                $$CHILD_BLOCK_END
                                                        08:aUserFlagSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserFlag
                                                                10:5:1:True/False
                                                                $$CHILD_BLOCK_END
                                                        08:aSetLevelTimer
                                                                $$CHILD_BLOCK_START
                                                                10:6:3.000000:Time
                                                                10:10:0:10:TimerID
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                03:1
                                                        $$CHILD_BLOCK_START
                                                        05:2
                                                                $$CHILD_BLOCK_START
                                                                06:qGoalEnabled:Bool
                                                                        $$CHILD_BLOCK_START
                                                                        10:18:0:9:LevelGoal
                                                                        $$CHILD_BLOCK_END
                                                                07:1:0
                                                                10:5:0:Bool
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aGoalEnableDisable
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:1:Enable/Disable
                                                                10:18:0:9:LevelGoal
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
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
                                                                10:10:0:8:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:7
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:UplinkErrorNoInit:Message
                                                        $$CHILD_BLOCK_END
                                                08:aUserFlagSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:UserFlag
                                                        10:5:1:True/False
                                                        $$CHILD_BLOCK_END
                                                08:aSetLevelTimer
                                                        $$CHILD_BLOCK_START
                                                        10:6:3.000000:Time
                                                        10:10:0:10:TimerID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
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
                                                        10:10:0:8:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:UplinkErrorNoInt:Message
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:3.000000:Time
                                                10:10:0:10:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                                10:10:0:8:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:UplinkErrorNano:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:3.000000:Time
                                        10:10:0:10:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalEnabled:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:8:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalEnableDisable
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:18:0:8:LevelGoal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Clear Message Delay Flag
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
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Memory Plasma Blob generated
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Player picks up Memory Plasma Blob
        $$CHILD_BLOCK_START
        01:1:0
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
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
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
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        06:qMathSubFloat:value
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Float1
                                06:qMathMulFloat:Float2
                                        $$CHILD_BLOCK_START
                                        10:6:5.000000:Float1
                                        06:qMathIntToFloat:Float2
                                                $$CHILD_BLOCK_START
                                                06:qGetDifficulty:Int
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageI
                        $$CHILD_BLOCK_START
                        10:8:MemPlasmaObtained:Message
                        06:qUserVarValueInt:Integer
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Time
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:11:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aTimerShow
                        $$CHILD_BLOCK_START
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Memory Plasma Charge Expires
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
                                10:10:0:2:TimerID
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarDec
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
                                07:1:5
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MemPlasmaLost:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:7:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:11:LevelGoal
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Set Waypoint 2 check (terrain canyon)
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
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjCanSeePlayerAdvanced:Bool
                                                $$CHILD_BLOCK_START
                                                10:4:90:Cone
                                                10:1:0:92:Object
                                                10:6:400.000000:Distance
                                                10:15:1048585:FVIHitFlags
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSetWaypoint
                                        $$CHILD_BLOCK_START
                                        10:4:2:Number
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:19:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:1.000000:Time
                                        10:10:0:16:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Foyer Matcen1 Produced Robot
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
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:1:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Foyer Matcen2 Produced Robot
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
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:1:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:HD Matcen1 Produced Robot
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
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:2:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:HD Matcen2 Produced Robot
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
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:2:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Aux Matcen1 Produced Robot
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
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:3:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Central Matcen Produced Robot
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:2:4:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Create Virus Uploading Effects
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:93:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:15.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:3:NumTiles
                                10:14:4:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:0:94:Object2
                                10:6:15.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:3:NumTiles
                                10:14:4:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:11:TimerID
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:95:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:15.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:6:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:11:TimerID
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:96:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:15.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:6:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:11:TimerID
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:97:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:15.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:6:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:11:TimerID
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:98:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:15.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:6:NumTiles
                                10:14:2:Texture
                                10:6:1.000000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:11:TimerID
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:1:0:93:Object2
                                10:6:15.000000:Lifetime
                                10:6:1.000000:Thickness
                                10:4:3:NumTiles
                                10:14:5:Texture
                                10:6:0.250000:SlideTime
                                10:4:2:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:94:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:15.000000:Lifetime
                                10:6:1.000000:Thickness
                                10:4:3:NumTiles
                                10:14:5:Texture
                                10:6:0.250000:SlideTime
                                10:4:2:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:End Level
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:12:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:25:CameraPath
                        10:16:26:PlayerPath
                        10:6:15.000000:Time
                        10:8:UploadingVirus:Text
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:Music-Intro Init
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
00:75:Music-RightArm-2
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Music-RightArm-1
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Music-LowerEnd-2
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Music-LowerEnd-1
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
00:83:Music-MidSection-4
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Music-MidSection-3
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Music-MidSection-2
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Music-MidSection-1
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Music-MainHub-2
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
00:78:Music-MainHub-1
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
00:77:Music-Outside-2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Music-Outside-1
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:Setup Hangar Cam
        $$CHILD_BLOCK_START
        01:1:99
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:Setup Prep Room Cam
        $$CHILD_BLOCK_START
        01:1:100
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:Setup Mem Plasma Cam
        $$CHILD_BLOCK_START
        01:1:101
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:Setup Corridor Cam
        $$CHILD_BLOCK_START
        01:1:102
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:Setup Substation 1 Cam
        $$CHILD_BLOCK_START
        01:1:103
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:Setup Auxillary Cam
        $$CHILD_BLOCK_START
        01:1:104
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:Setup Control Cam
        $$CHILD_BLOCK_START
        01:1:105
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:14.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Hangar Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:99
        02:11
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
                                        10:10:0:18:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:5:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:6:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:7:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:Hangar Turret 1 Hit by Player
        $$CHILD_BLOCK_START
        01:1:5
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
                                        10:10:0:18:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:Hangar Turret 2 Hit by Player
        $$CHILD_BLOCK_START
        01:1:6
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
                                        10:10:0:18:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:Hangar Turret 3 Hit by Player
        $$CHILD_BLOCK_START
        01:1:7
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
                                        10:10:0:18:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:Hangar Turret 4 Hit by Player
        $$CHILD_BLOCK_START
        01:1:8
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
                                        10:10:0:18:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:Prep Room Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:100
        02:11
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
                                        10:10:0:20:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:20:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:Prep Room Turret Hit by Player
        $$CHILD_BLOCK_START
        01:1:20
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
                                        10:10:0:20:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:20:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:Mem Plasma Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:101
        02:11
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
                                        10:10:0:21:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:21:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:22:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:23:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:24:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:131:Mem Plasma Turret 1 Hit by Player
        $$CHILD_BLOCK_START
        01:1:21
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
                                        10:10:0:21:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:132:Mem Plasma Turret 2 Hit by Player
        $$CHILD_BLOCK_START
        01:1:22
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
                                        10:10:0:21:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:133:Mem Plasma Turret 3 Hit by Player
        $$CHILD_BLOCK_START
        01:1:23
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
                                        10:10:0:21:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:134:Mem Plasma Turret 4 Hit by Player
        $$CHILD_BLOCK_START
        01:1:24
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
                                        10:10:0:21:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:22:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:23:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:24:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:21:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:Corridor Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:102
        02:11
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
                                        10:10:0:22:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:25:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:26:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:22:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:135:Corridor Turret 1 Hit by Player
        $$CHILD_BLOCK_START
        01:1:25
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
                                        10:10:0:22:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:22:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:136:Corridor Turret 2 Hit by Player
        $$CHILD_BLOCK_START
        01:1:26
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
                                        10:10:0:22:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:26:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:22:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:Substation 1 Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:103
        02:11
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
                                        10:10:0:23:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:27:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:23:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:137:Substation 1 Turret Hit by Player
        $$CHILD_BLOCK_START
        01:1:27
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
                                        10:10:0:23:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:23:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:Auxillary Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:104
        02:11
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
                                        10:10:0:24:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:28:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:29:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:30:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:24:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:138:Auxillary Turret 1 Hit by Player
        $$CHILD_BLOCK_START
        01:1:28
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
                                        10:10:0:24:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:24:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:139:Auxillary Turret 2 Hit by Player
        $$CHILD_BLOCK_START
        01:1:29
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
                                        10:10:0:24:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:24:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:140:Auxillary Turret 3 Hit by Player
        $$CHILD_BLOCK_START
        01:1:30
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
                                        10:10:0:24:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:28:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:29:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:30:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:24:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:Control Cam Saw Player
        $$CHILD_BLOCK_START
        01:1:105
        02:11
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
                                        10:10:0:25:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        09:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:31:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:32:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZCamSpotted:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:25:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:141:Control Turret 1 Hit by Player
        $$CHILD_BLOCK_START
        01:1:31
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
                                        10:10:0:25:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:25:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:142:Control Turret 2 Hit by Player
        $$CHILD_BLOCK_START
        01:1:32
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
                                        10:10:0:25:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ZTurretHit:Message
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:25:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Player Picks Up Camera Monitor
        $$CHILD_BLOCK_START
        01:1:106
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:ZGotCamMonitor:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:5:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:26:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:27:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Player Used Camera Monitor
        $$CHILD_BLOCK_START
        01:1:106
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:27:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:ZCamMonitorOff:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:27:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:ZCamMonitorOn:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:27:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:Monitor Camera Group A
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
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
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:27:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:5:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
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
                                                06:qObjRoom:Room
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:5:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:2:5:Room
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:99:Object
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aCreatePopupView
                                        $$CHILD_BLOCK_START
                                        10:4:0:GunPoint
                                        10:1:0:99:Object
                                        10:6:0.000000:Time
                                        10:6:1.000000:Zoom
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserVar
                                        10:6:1.000000:value
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
                                                                06:qObjSavedHandle:Object
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:5:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:2:6:Room
                                                        $$CHILD_BLOCK_END
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qObjExists:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:100:Object
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aCreatePopupView
                                                $$CHILD_BLOCK_START
                                                10:4:0:GunPoint
                                                10:1:0:100:Object
                                                10:6:0.000000:Time
                                                10:6:1.000000:Zoom
                                                $$CHILD_BLOCK_END
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                10:6:2.000000:value
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                09:0
                                                        $$CHILD_BLOCK_START
                                                        09:1
                                                                $$CHILD_BLOCK_START
                                                                05:2
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjRoom:Room
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:5:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:2:7:Room
                                                                        $$CHILD_BLOCK_END
                                                                05:2
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjRoom:Room
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:5:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:2:8:Room
                                                                        $$CHILD_BLOCK_END
                                                                05:2
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjRoom:Room
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:5:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:2:9:Room
                                                                        $$CHILD_BLOCK_END
                                                                05:2
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjRoom:Room
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:5:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:2:10:Room
                                                                        $$CHILD_BLOCK_END
                                                                05:2
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjRoom:Room
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:5:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:2:11:Room
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        05:1
                                                                $$CHILD_BLOCK_START
                                                                06:qObjExists:Bool
                                                                        $$CHILD_BLOCK_START
                                                                        10:1:0:101:Object
                                                                        $$CHILD_BLOCK_END
                                                                07:0:6
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aCreatePopupView
                                                        $$CHILD_BLOCK_START
                                                        10:4:0:GunPoint
                                                        10:1:0:101:Object
                                                        10:6:0.000000:Time
                                                        10:6:1.000000:Zoom
                                                        $$CHILD_BLOCK_END
                                                08:aUserVarSet
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:UserVar
                                                        10:6:3.000000:value
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
                                                                                06:qObjSavedHandle:Object
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:5:SavedObjectSlot
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        07:1:0
                                                                        10:2:12:Room
                                                                        $$CHILD_BLOCK_END
                                                                05:1
                                                                        $$CHILD_BLOCK_START
                                                                        06:qObjExists:Bool
                                                                                $$CHILD_BLOCK_START
                                                                                10:1:0:102:Object
                                                                                $$CHILD_BLOCK_END
                                                                        07:0:6
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:0
                                                        $$CHILD_BLOCK_START
                                                        08:aCreatePopupView
                                                                $$CHILD_BLOCK_START
                                                                10:4:0:GunPoint
                                                                10:1:0:102:Object
                                                                10:6:0.000000:Time
                                                                10:6:1.000000:Zoom
                                                                $$CHILD_BLOCK_END
                                                        08:aUserVarSet
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:2:UserVar
                                                                10:6:4.000000:value
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:1
                                                        $$CHILD_BLOCK_START
                                                        03:1
                                                                $$CHILD_BLOCK_START
                                                                09:0
                                                                        $$CHILD_BLOCK_START
                                                                        09:1
                                                                                $$CHILD_BLOCK_START
                                                                                05:2
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjRoom:Room
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        07:1:0
                                                                                        10:2:13:Room
                                                                                        $$CHILD_BLOCK_END
                                                                                05:2
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjRoom:Room
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        07:1:0
                                                                                        10:2:14:Room
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        05:1
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjExists:Bool
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:103:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:0:6
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:0
                                                                $$CHILD_BLOCK_START
                                                                08:aCreatePopupView
                                                                        $$CHILD_BLOCK_START
                                                                        10:4:0:GunPoint
                                                                        10:1:0:103:Object
                                                                        10:6:0.000000:Time
                                                                        10:6:1.000000:Zoom
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserVarSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:2:UserVar
                                                                        10:6:5.000000:value
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
                                                                                                06:qObjSavedHandle:Object
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        07:1:0
                                                                                        10:2:15:Room
                                                                                        $$CHILD_BLOCK_END
                                                                                05:1
                                                                                        $$CHILD_BLOCK_START
                                                                                        06:qObjExists:Bool
                                                                                                $$CHILD_BLOCK_START
                                                                                                10:1:0:104:Object
                                                                                                $$CHILD_BLOCK_END
                                                                                        07:0:6
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:0
                                                                        $$CHILD_BLOCK_START
                                                                        08:aCreatePopupView
                                                                                $$CHILD_BLOCK_START
                                                                                10:4:0:GunPoint
                                                                                10:1:0:104:Object
                                                                                10:6:0.000000:Time
                                                                                10:6:1.000000:Zoom
                                                                                $$CHILD_BLOCK_END
                                                                        08:aUserVarSet
                                                                                $$CHILD_BLOCK_START
                                                                                10:10:0:2:UserVar
                                                                                10:6:6.000000:value
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                04:1:0:1
                                                                        $$CHILD_BLOCK_START
                                                                        03:1
                                                                                $$CHILD_BLOCK_START
                                                                                09:0
                                                                                        $$CHILD_BLOCK_START
                                                                                        09:1
                                                                                                $$CHILD_BLOCK_START
                                                                                                05:2
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjRoom:Room
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                06:qObjSavedHandle:Object
                                                                                                                        $$CHILD_BLOCK_START
                                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                                        $$CHILD_BLOCK_END
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        07:1:0
                                                                                                        10:2:16:Room
                                                                                                        $$CHILD_BLOCK_END
                                                                                                05:2
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjRoom:Room
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                06:qObjSavedHandle:Object
                                                                                                                        $$CHILD_BLOCK_START
                                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                                        $$CHILD_BLOCK_END
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        07:1:0
                                                                                                        10:2:3:Room
                                                                                                        $$CHILD_BLOCK_END
                                                                                                05:2
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjRoom:Room
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                06:qObjSavedHandle:Object
                                                                                                                        $$CHILD_BLOCK_START
                                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                                        $$CHILD_BLOCK_END
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        07:1:0
                                                                                                        10:2:17:Room
                                                                                                        $$CHILD_BLOCK_END
                                                                                                05:2
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        06:qObjRoom:Room
                                                                                                                $$CHILD_BLOCK_START
                                                                                                                06:qObjSavedHandle:Object
                                                                                                                        $$CHILD_BLOCK_START
                                                                                                                        10:10:0:5:SavedObjectSlot
                                                                                                                        $$CHILD_BLOCK_END
                                                                                                                $$CHILD_BLOCK_END
                                                                                                        07:1:0
                                                                                                        10:2:18:Room
                                                                                                        $$CHILD_BLOCK_END
                                                                                                $$CHILD_BLOCK_END
                                                                                        05:1
                                                                                                $$CHILD_BLOCK_START
                                                                                                06:qObjExists:Bool
                                                                                                        $$CHILD_BLOCK_START
                                                                                                        10:1:0:105:Object
                                                                                                        $$CHILD_BLOCK_END
                                                                                                07:0:6
                                                                                                $$CHILD_BLOCK_END
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        04:1:0:0
                                                                                $$CHILD_BLOCK_START
                                                                                08:aCreatePopupView
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:4:0:GunPoint
                                                                                        10:1:0:105:Object
                                                                                        10:6:0.000000:Time
                                                                                        10:6:1.000000:Zoom
                                                                                        $$CHILD_BLOCK_END
                                                                                08:aUserVarSet
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:10:0:2:UserVar
                                                                                        10:6:7.000000:value
                                                                                        $$CHILD_BLOCK_END
                                                                                $$CHILD_BLOCK_END
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aClosePopupView
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.400000:Time
                        10:10:0:17:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:Player picks up Crashed Ship Log
        $$CHILD_BLOCK_START
        01:1:107
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:CrashedShipGame:GameMessage
                        10:8:CrashedShipHud:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:Meteor1 - Path
        $$CHILD_BLOCK_START
        01:1:108
        02:22
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsType:Bool
                                $$CHILD_BLOCK_START
                                10:1:0:61:Object
                                10:10:0:2:ObjectType
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:400.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:27:Path
                        10:15:4096:AIGoalFlags
                        10:10:0:14:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.500000:BlobLifetime
                        10:6:0.010000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:4.500000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:Meteor1 - GoalID Explosion
        $$CHILD_BLOCK_START
        01:1:108
        02:13
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        10:4:-1:GunNum
                        10:10:0:0:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.040000:BlobInterval
                        10:6:1.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:147:Locked Door - No Entry Message
        $$CHILD_BLOCK_START
        01:1:110
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
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:NoEntry:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
