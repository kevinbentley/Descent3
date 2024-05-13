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
// Filename:	Merc7.cpp
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

#define ID_CUSTOM_OBJECT_0885 0x001
#define ID_CUSTOM_OBJECT_0884 0x002
#define ID_CUSTOM_OBJECT_0903 0x003
#define ID_CUSTOM_OBJECT_0902 0x004
#define ID_CUSTOM_OBJECT_0901 0x005
#define ID_CUSTOM_OBJECT_1025 0x006
#define ID_CUSTOM_OBJECT_103B 0x007
#define ID_CUSTOM_OBJECT_1038 0x008
#define ID_CUSTOM_OBJECT_2022 0x009
#define ID_CUSTOM_OBJECT_10AF 0x00a
#define ID_CUSTOM_OBJECT_20AA 0x00b
#define ID_CUSTOM_OBJECT_1031 0x00c
#define ID_CUSTOM_OBJECT_0833 0x00d
#define ID_CUSTOM_OBJECT_0951 0x00e
#define ID_CUSTOM_OBJECT_0952 0x00f
#define ID_CUSTOM_OBJECT_0953 0x010
#define ID_CUSTOM_OBJECT_0954 0x011
#define ID_CUSTOM_OBJECT_095F 0x012
#define ID_CUSTOM_OBJECT_0960 0x013
#define ID_CUSTOM_OBJECT_0961 0x014
#define ID_CUSTOM_OBJECT_0962 0x015
#define ID_CUSTOM_OBJECT_0869 0x016
#define ID_CUSTOM_OBJECT_0963 0x017
#define ID_CUSTOM_OBJECT_0964 0x018
#define ID_CUSTOM_OBJECT_0965 0x019
#define ID_CUSTOM_OBJECT_0966 0x01a
#define ID_CUSTOM_OBJECT_0995 0x01b
#define ID_CUSTOM_OBJECT_0994 0x01c
#define ID_CUSTOM_OBJECT_0993 0x01d
#define ID_CUSTOM_OBJECT_0992 0x01e
#define ID_CUSTOM_OBJECT_1191 0x01f
#define ID_CUSTOM_OBJECT_083D 0x020
#define ID_CUSTOM_OBJECT_103C 0x021
#define ID_CUSTOM_OBJECT_103E 0x022
#define ID_CUSTOM_OBJECT_0841 0x023
#define ID_CUSTOM_OBJECT_097A 0x024
#define ID_CUSTOM_OBJECT_0997 0x025
#define ID_CUSTOM_OBJECT_0996 0x026
#define ID_CUSTOM_OBJECT_0805 0x027
#define ID_CUSTOM_OBJECT_0804 0x028
#define ID_CUSTOM_OBJECT_0998 0x029
#define ID_CUSTOM_OBJECT_087E 0x02a
#define ID_CUSTOM_OBJECT_1834 0x02b
#define ID_CUSTOM_OBJECT_1877 0x02c
#define ID_CUSTOM_OBJECT_1078 0x02d
#define ID_CUSTOM_OBJECT_1070 0x02e
#define ID_CUSTOM_OBJECT_2075 0x02f
#define ID_CUSTOM_OBJECT_2076 0x030
#define ID_CUSTOM_OBJECT_2863 0x031
#define ID_CUSTOM_OBJECT_207A 0x032
#define ID_CUSTOM_OBJECT_206D 0x033
#define ID_CUSTOM_OBJECT_1079 0x034
#define ID_CUSTOM_OBJECT_09BF 0x035
#define ID_CUSTOM_OBJECT_09BE 0x036
#define ID_CUSTOM_OBJECT_09BD 0x037
#define ID_CUSTOM_OBJECT_09BC 0x038
#define ID_CUSTOM_OBJECT_1071 0x039
#define ID_CUSTOM_OBJECT_09CA 0x03a
#define ID_CUSTOM_OBJECT_09C9 0x03b
#define ID_CUSTOM_OBJECT_09C8 0x03c
#define ID_CUSTOM_OBJECT_09C7 0x03d
#define ID_CUSTOM_OBJECT_09C6 0x03e
#define ID_CUSTOM_OBJECT_09C5 0x03f
#define ID_CUSTOM_OBJECT_09C4 0x040
#define ID_CUSTOM_OBJECT_09C3 0x041
#define ID_CUSTOM_OBJECT_09C2 0x042
#define ID_CUSTOM_OBJECT_286E 0x043

#define ID_TRIGGER_0005 0x044
#define ID_TRIGGER_0000 0x045
#define ID_TRIGGER_0006 0x046
#define ID_TRIGGER_0004 0x047
#define ID_TRIGGER_0008 0x048
#define ID_TRIGGER_0009 0x049
#define ID_TRIGGER_000F 0x04a
#define ID_TRIGGER_0013 0x04b
#define ID_TRIGGER_0012 0x04c
#define ID_TRIGGER_0011 0x04d
#define ID_TRIGGER_0010 0x04e
#define ID_TRIGGER_000E 0x04f
#define ID_TRIGGER_000C 0x050
#define ID_TRIGGER_000D 0x051
#define ID_TRIGGER_000A 0x052
#define ID_TRIGGER_000B 0x053

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

class CustomObjectScript_0885 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0884 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0903 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0902 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0901 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1025 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_103B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1038 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2022 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10AF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20AA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1031 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0833 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0951 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0952 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0953 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0954 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_095F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0960 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0961 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0962 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0869 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0963 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0964 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0965 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0966 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0995 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0994 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0993 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0992 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1191 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_103C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_103E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0841 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0997 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0996 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0805 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0804 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0998 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1834 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1877 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1078 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1070 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2075 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2076 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2863 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_207A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_206D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1079 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09BC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1071 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09CA : public BaseScript {
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

class CustomObjectScript_286E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
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

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000D : public BaseScript {
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

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_131 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_130 = 0;
static int ScriptActionCtr_129 = 0;
static int ScriptActionCtr_128 = 0;
static int ScriptActionCtr_127 = 0;
static int ScriptActionCtr_126 = 0;
static int ScriptActionCtr_125 = 0;
static int ScriptActionCtr_124 = 0;
static int ScriptActionCtr_123 = 0;
static int ScriptActionCtr_122 = 0;
static int ScriptActionCtr_121 = 0;
static int ScriptActionCtr_021 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_131 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_130 = 0;
  ScriptActionCtr_129 = 0;
  ScriptActionCtr_128 = 0;
  ScriptActionCtr_127 = 0;
  ScriptActionCtr_126 = 0;
  ScriptActionCtr_125 = 0;
  ScriptActionCtr_124 = 0;
  ScriptActionCtr_123 = 0;
  ScriptActionCtr_122 = 0;
  ScriptActionCtr_121 = 0;
  ScriptActionCtr_021 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_130, file_ptr);
  File_WriteInt(ScriptActionCtr_129, file_ptr);
  File_WriteInt(ScriptActionCtr_128, file_ptr);
  File_WriteInt(ScriptActionCtr_127, file_ptr);
  File_WriteInt(ScriptActionCtr_126, file_ptr);
  File_WriteInt(ScriptActionCtr_125, file_ptr);
  File_WriteInt(ScriptActionCtr_124, file_ptr);
  File_WriteInt(ScriptActionCtr_123, file_ptr);
  File_WriteInt(ScriptActionCtr_122, file_ptr);
  File_WriteInt(ScriptActionCtr_121, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_130 = File_ReadInt(file_ptr);
  ScriptActionCtr_129 = File_ReadInt(file_ptr);
  ScriptActionCtr_128 = File_ReadInt(file_ptr);
  ScriptActionCtr_127 = File_ReadInt(file_ptr);
  ScriptActionCtr_126 = File_ReadInt(file_ptr);
  ScriptActionCtr_125 = File_ReadInt(file_ptr);
  ScriptActionCtr_124 = File_ReadInt(file_ptr);
  ScriptActionCtr_123 = File_ReadInt(file_ptr);
  ScriptActionCtr_122 = File_ReadInt(file_ptr);
  ScriptActionCtr_121 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

/*
$$ENUM Region
0:Intro
1:Sewer
2:Maintenence
3:MidSection
4:Tower
5:Bomb
6:Boss
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

#define SPECIAL_TIMER_ID_BASE 1000
#define SPECIAL_TIMER_CLASSES 4
#define SPECIAL_TIMER_MAX 256
#define SPECIAL_TIMER_ID_LIMIT (SPECIAL_TIMER_ID_BASE + SPECIAL_TIMER_MAX * SPECIAL_TIMER_CLASSES - 1)

static inline int LEVEL_TIMER_UID(uint8_t timer_class, uint8_t index) {
  return (SPECIAL_TIMER_ID_BASE + (timer_class % SPECIAL_TIMER_CLASSES) * SPECIAL_TIMER_MAX + index);
}

/*
$$ACTION
Custom
Timer [e:Enable/Disable] forcefield at portal [i:PortalNum] in room [r:Room]; Double-sided = [b:DoublesidedFlag=1], time
= [f:Time] cTimedEnableForcefield Delayed enabling/disabling of forcefield. Delays enabling/disabling of forcefield for
a specified time

Parameters:
        Enable/Disable: Forcefield state
        PortalNum: portal number of forcefield
        Room: room number
        Double-sided: do on both sides of portal
        Time: In seconds
$$END
*/

static uint8_t ff_index = 0;
static struct t_ff_enable_data {
  int16_t room_number;
  int16_t portal_num;
  bool state;
  bool double_sided;
} ff_enable_data[8];

void cTimedEnableForcefield(int state, int portal_num, int room_number, bool double_sided, float time) {
  mprintf(0, "hello....\n");
  if (ff_index >= 8)
    ff_index = 0;
  ff_enable_data[ff_index].room_number = room_number;
  ff_enable_data[ff_index].portal_num = portal_num;
  ff_enable_data[ff_index].state = (bool)(state ? true : false);
  ff_enable_data[ff_index].double_sided = double_sided;

  aSetLevelTimer(time, LEVEL_TIMER_UID(0, ff_index++));
}

/*
$$ACTION
Custom
Timer delay of wind in room [r:Room], direction = <[f:X],[f:Y],[f:Z]>, speed = [f:Speed=1.0], time = [f:Time]
cTimedRoomSetWind
Set wind in room after delay
  Sets the wind after specified delay.

Parameters:
  Room: the room in which to set the wind
  X,Y,Z: the direction vector for the wind
  Speed: the speed of the wind (10.0 is faster than the player ship)
  Time: delay time.
$$END
*/

static uint8_t wind_fx_index = 0;
static struct t_wind_fx_data {
  int room_number;
  float x, y, z;
  float speed;
} wind_fx_data[8];

void cTimedRoomSetWind(int room_number, float x, float y, float z, float speed, float time) {
  if (wind_fx_index >= 8)
    wind_fx_index = 0;
  wind_fx_data[wind_fx_index].room_number = room_number;
  wind_fx_data[wind_fx_index].x = x;
  wind_fx_data[wind_fx_index].y = y;
  wind_fx_data[wind_fx_index].z = z;
  wind_fx_data[wind_fx_index].speed = speed;

  aSetLevelTimer(time, LEVEL_TIMER_UID(1, wind_fx_index++));
}

/*
$$ACTION
Custom
Query and execute custom timer event with timer id [e:TimerID]
cExecTimerEvent
Executes a custom timer event.
        Runs a specific function initialized by a custom timer event function (i.e. glass break)

Parameters:
        TimerID: Timer id of event.
$$END
*/

void cExecTimerEvent(int timerid) {
  if (timerid < SPECIAL_TIMER_ID_BASE || timerid > SPECIAL_TIMER_ID_LIMIT) {
    return;
  }

  int index = (timerid - SPECIAL_TIMER_ID_BASE);
  int timer_class = index / SPECIAL_TIMER_MAX;
  index = index % SPECIAL_TIMER_MAX;

  switch (timer_class) {
  case 0: // break glass!
    if (index < 8 && index >= 0) {
      aPortalRenderSet(ff_enable_data[index].state, ff_enable_data[index].portal_num, ff_enable_data[index].room_number,
                       ff_enable_data[index].double_sided);
    }
    break;

  case 1: // timed wind delay
    if (index < 8 && index >= 0) {
      aRoomSetWind(wind_fx_data[index].room_number, wind_fx_data[index].x, wind_fx_data[index].y, wind_fx_data[index].z,
                   wind_fx_data[index].speed);
    }
    break;
  }
}

//	DROID CENTRAL AI
//		Essentially, lifters will be scurrying around droid central exiting, forming, etc.
//		stopping at terminals.
//
//		X is a value from 1 to ???
//		EQC is equilibrium counter
//
//		DALLAS SCRIPT
//
//		To switch to a terminal, choose one object DCPath-X
//			tell lifter to go to DCPath-X, custom goal
//			call custom goal handler for custom goal when reached from DALLAS
//				query every so often to switch to either exit or new terminal
//
//		To exit, choose one object DCExit-X
//			let DALLAS handle DCExit-X triggers X1-XN
//				call custom trigger handler for trigger
//					this handler will tell bot to go to object DCDead-X, custom goal
//					call custom goal handler for custom goal when reached from DALLAS
//						when goal is reached, kill object, adjust equilibrium counter EQC

//	custom goal id base number
#define SPECIAL_GOAL_ID_BASE 1000
#define SPECIAL_GOAL_CLASSES 1
#define SPECIAL_GOAL_MAX 256

#define GOAL_PRIORITY_HIGH 3
#define GOAL_PRIORITY_LOW 0

static inline int LEVEL_GOAL_UID(uint8_t goal_class, uint8_t index) {
  return (SPECIAL_TIMER_ID_BASE + (goal_class % SPECIAL_GOAL_CLASSES) * SPECIAL_GOAL_MAX + index);
}

static uint8_t DC_Goal_Index = 0;

#define DC_N_DROIDS 32
#define DC_EXIT_GOAL 0
#define DC_TERM_GOAL 1
#define DC_END_GOAL 2
static struct t_dc_node {
  int handle;     // OBJECT_HANDLE_NONE = free node.
  int type;       // -1 = free goal.
  int type_index; // data value for goal type (term = terminal number)
  int goalid;
  float timer;
  float orig_maxspeed; // original maxspeed.
} dc_nodes[DC_N_DROIDS];

static float DC_Time_Since_Last_Create = 0.0f;
static float DC_Last_Game_Time = 0.0f;

#define DC_N_VALID_EXITS 4
static const char *DC_Valid_Exits[DC_N_VALID_EXITS] = {"DCExit-1", "DCExit-2", "DCExit-3", "DCExit-2"};
static int DC_Valid_Exit_Handles[DC_N_VALID_EXITS];
static int DC_Valid_Exit_RoomHandles[DC_N_VALID_EXITS];

static unsigned DC_Exit_Mask = 0; // used to exclude slots to prevent conflicts

const char *DC_Valid_Ends[DC_N_VALID_EXITS] = {"DCEnd-1", "DCEnd-2", "DCEnd-3", "DCEnd-4"};
static int DC_Valid_End_Handles[DC_N_VALID_EXITS];

#define DC_N_VALID_TERMS 5
const char *DC_Valid_Terms[DC_N_VALID_TERMS] = {"DCPath-1", "DCPath-2", "DCPath-3", "DCPath-4", "DCPath-5"};
static int DC_Valid_Term_Handles[DC_N_VALID_TERMS];
static unsigned DC_Term_Mask = 0; // used to exclude slots to prevent conflicts

#define DC_N_VALID_MATCENS 4
const char *DC_Valid_Matcens[DC_N_VALID_MATCENS] = {"DCMatcen-1", "DCMatcen-2", "DCMatcen-3", "DCMatcen-4"};
static int DC_Valid_Matcen_Handles[DC_N_VALID_MATCENS];
static unsigned DC_Matcen_Mask = 0; // used to exclude slots to prevent conflicts

static int DC_EQR = -5; // droid equilibrium register.
                        // if < 0, that's how many droids we're int16_t
                        // if > 0, this means we must tell some droids to leave!

static void DCDetermineObjFate(int objhandle, bool new_droid);

// this function will return a random free index in a max (bit must be 0)
// if there are none, then return a random index??
inline int FIND_FREE_INDEX(unsigned mask, unsigned max_items, bool allow_duplicates) {
  int i;
  int8_t indices[32];
  int8_t nindices = 0;

  for (i = 0; i < max_items; i++) {
    if ((mask & (1 << i)) == 0) {
      indices[nindices++] = i;
    }
  }

  if (nindices == 0) {
    if (allow_duplicates) {
      return (rand() % max_items);
    } else {
      return -1;
    }
  } else {
    return (int)(indices[rand() % nindices]);
  }
}

/*
$$ACTION
Custom
Reset Droid Central
cResetDroidCentral
Resets droid central
        resets droid central

Parameters:
        None
$$END
*/
void cResetDroidCentral() {
  int i;
  for (i = 0; i < DC_N_DROIDS; i++) {
    dc_nodes[i].handle = OBJECT_HANDLE_NONE;
    dc_nodes[i].type = -1;
    dc_nodes[i].goalid = -1;
    dc_nodes[i].timer = 0.0f;
  }

  for (i = 0; i < DC_N_VALID_EXITS; i++) {
    DC_Valid_Exit_Handles[i] = Scrpt_FindObjectName(DC_Valid_Exits[i]);
    DC_Valid_Exit_RoomHandles[i] = Scrpt_FindRoomName(DC_Valid_Exits[i]);
    DC_Valid_End_Handles[i] = Scrpt_FindObjectName(DC_Valid_Ends[i]);
  }
  for (i = 0; i < DC_N_VALID_TERMS; i++) {
    DC_Valid_Term_Handles[i] = Scrpt_FindObjectName(DC_Valid_Terms[i]);
  }
  for (i = 0; i < DC_N_VALID_MATCENS; i++) {
    DC_Valid_Matcen_Handles[i] = Scrpt_FindMatcenName(DC_Valid_Matcens[i]);
  }

  DC_EQR = -5;
  DC_Time_Since_Last_Create = 0.0f;
  DC_Last_Game_Time = Game_GetTime();

  mprintf(0, "DC: RESETTING DROID MANAGER\n");
}

/*
$$ACTION
Custom
Destroy Droid Central
cDestroyDroidCentral
Destroys Droid Central
        stops and destroys all active droids.

Parameters:
        None
$$END
*/
void cDestroyDroidCentral() {
  int i;
  for (i = 0; i < DC_N_DROIDS; i++) {
    if (dc_nodes[i].handle != OBJECT_HANDLE_NONE) {
      aObjDestroy(dc_nodes[i].handle);
    }
  }
  cResetDroidCentral();
  DC_EQR = -100;
}

/*
$$ACTION
Custom
Add [o:Object] to Droid Manager
cAddObjToDroidManager
Adds an object (robot) to droid manager.
        manually adds an object to the droid manager, usually matcened so that manager can send it events.
Parameters:
        Object: A robot (usually lifter matcened)
$$END
*/
void cAddObjToDroidManager(int objhandle) {
  int i;
  if (DC_EQR == -100) {
    return;
  }

  for (i = 0; i < DC_N_DROIDS; i++) {
    if (dc_nodes[i].handle == OBJECT_HANDLE_NONE) {
      dc_nodes[i].handle = objhandle;
      dc_nodes[i].type = -1;
      dc_nodes[i].goalid = -1;
      dc_nodes[i].timer = 0.0f;
      dc_nodes[i].orig_maxspeed = qAIQueryMaxSpeed(objhandle);
      aAISetMaxSpeed(objhandle, dc_nodes[i].orig_maxspeed * 1.5f); // set new max speed
      DC_EQR++;                                                    // increment droid register
      break;
    }
  }

  if (i == DC_N_DROIDS) {
    mprintf(0, "DC:TOO MANY DROIDS!!!\n");
  }
}

/*
$$ACTION
Custom
Remove [o:Object] from Droid Manager
cRemoveObjFromDroidManager
Remove an object (robot) from droid manager.
        manually removes an object to the droid manager.
Parameters:
        Object: A robot (usually lifter matcened)
$$END
*/
void cRemoveObjFromDroidManager(int objhandle) {
  int i;
  if (DC_EQR == -100) {
    return;
  }

  for (i = 0; i < DC_N_DROIDS; i++) {
    if (dc_nodes[i].handle == objhandle) {
      dc_nodes[i].handle = OBJECT_HANDLE_NONE;
      dc_nodes[i].type = -1;
      dc_nodes[i].goalid = -1;
      aAISetMaxSpeed(objhandle, dc_nodes[i].orig_maxspeed); // restore speed
      DC_EQR--;                                             // decrement droid register
      break;
    }
  }
  if (i == DC_N_DROIDS) {
    mprintf(0, "DC:OBJECT NOT MANAGED, CAN'T DELETE IT!!\n");
  }
}

/*
$$ACTION
Custom
Create new droid at a Matcen
cDroidManagerCreateNew
Forces droid manager to create a new droid itself.
        Droid manager will create a new droid and assign it a task.

Parameters:
        None
$$END
*/
void cDroidManagerCreateNew() {
  if (DC_EQR == -100) {
    return;
  }

  // activates a chosen matcen
  int matc = FIND_FREE_INDEX(DC_Matcen_Mask, DC_N_VALID_MATCENS, true);
  int matcenid = DC_Valid_Matcen_Handles[matc];

  aMatcenSetState(1, matcenid); // activate matcen.
  DC_Matcen_Mask |= (1 << matc);
  DC_Time_Since_Last_Create = 0.0f;

  mprintf(0, "DC: CREATING NEW DROID\n");
}

/*
$$ACTION
Custom
Droid Manager Handle Matcen [m:Matcen] Generate of Object [o:Object].
cDroidManagerHandleMatcen
Handles all droid matcen events
        should be called whenever a matcen event is generated.  this call will determine if it's a managed matcen

Parameters:
        Matcen: Matcen ID
        Object: Object to add to droid manager.
$$END
*/
void cDroidManagerHandleMatcen(int matcenid, int objhandle) {
  int i;

  for (i = 0; i < DC_N_VALID_MATCENS; i++) {
    if (matcenid == DC_Valid_Matcen_Handles[i]) {
      cAddObjToDroidManager(objhandle);    // add object to manager
      DCDetermineObjFate(objhandle, true); // supplementary AI for droid
      aMatcenSetState(0, matcenid);        // deactivate matcen.
      DC_Matcen_Mask &= ~(1 << i);
      break;
    }
  }

  if (i == DC_N_VALID_MATCENS) {
    mprintf(0, "DC: MATCEN NOT IN LIST!!!\n");
  }
}

/*
$$ACTION
Custom
Droid Manager Handle GoalID [e:GoalID=-1] for Droid [o:Object].
cDroidManagerHandleGoals
Handles all droid goal events.
        function is the complement for Droid Manager Frame Interval,
        handles goals like exit, terminal and end goals.

Parameters:
        GoalID: Goal ID
        Object: Object that triggered the goal.
$$END
*/
void cDroidManagerHandleGoals(int goalid, int objhandle) {
  int i, goalid2;

  if (DC_EQR == -100) {
    return;
  }

  for (i = 0; i < DC_N_DROIDS; i++) {
    //	alright, check if object is in list.  then check if the goal is there too.
    if (dc_nodes[i].handle == objhandle && dc_nodes[i].goalid == goalid && dc_nodes[i].type != -1) {
      switch (dc_nodes[i].type) {
      case DC_EXIT_GOAL:
        //	deactivate forcefield (should be portal 1 of room)
        // send object to the end goal, if there is one.  otherwise just kill it now (BAD design)
        // end and exit and exit room handle indices should match up always
        aPortalRenderSet(0, 1, DC_Valid_Exit_RoomHandles[dc_nodes[i].type_index], true);

        DC_Exit_Mask &= ~(1 << dc_nodes[i].type_index);

        goalid2 = LEVEL_GOAL_UID(0, DC_Goal_Index++);

        aAIGoalGotoObject(objhandle, DC_Valid_End_Handles[dc_nodes[i].type_index], GOAL_PRIORITY_LOW,
                          GF_FORCE_AWARENESS | GF_ORIENT_VELOCITY, goalid2);

        dc_nodes[i].type = DC_END_GOAL; // specify end to be allocated.
        dc_nodes[i].goalid = goalid2;
        dc_nodes[i].timer = 0.0f;
        mprintf(0, "DC: DROID [%d] REACHES EXIT %d\n", i, dc_nodes[i].type_index);
        break;

      case DC_END_GOAL:
        // reactivate forcefield
        //	kill droid, it has met its end.
        aPortalRenderSet(1, 1, DC_Valid_Exit_RoomHandles[dc_nodes[i].type_index], true);
        aObjDelete(dc_nodes[i].handle);
        cRemoveObjFromDroidManager(dc_nodes[i].handle);
        mprintf(0, "DC: DROID [%d] REACHES ITS END\n", i);
        break;

      case DC_TERM_GOAL:
        // if i can think of anything nice, i'll put it here, but this should be unnecessary.
        mprintf(0, "DC: DROID [%d] REACHES TERMINAL %d\n", i, dc_nodes[i].type_index);
        dc_nodes[i].goalid = -1;
        dc_nodes[i].timer = 0.0f;
        break;
      }
    }
  }
}

/*
$$ACTION
Custom
Tell droid [o:Object] to find an exit from Droid Central.
cSendDroidObjToExit
Sends a message to a droid to find an exit.
        Sends droid out of Droid Central. If object is not a member of droid central, it adds it.

Parameters:
        Object: A robot
$$END
*/
void cSendDroidObjToExit(int objhandle) {
  int i;
  bool free_slot = false;

  if (DC_EQR == -100) {
    return;
  }

  for (i = 0; i < DC_N_DROIDS; i++) {
    if (dc_nodes[i].handle == objhandle) {
      // okay, find a free exit
      int exit = FIND_FREE_INDEX(DC_Exit_Mask, DC_N_VALID_EXITS, true);
      int goalid = LEVEL_GOAL_UID(0, DC_Goal_Index++);

      // deallocate terminal if this droid was working at one!!
      if (dc_nodes[i].type == DC_TERM_GOAL) {
        DC_Term_Mask &= ~(1 << dc_nodes[i].type_index);
      }

      mprintf(0, "DC: SENDING DROID [%d] to exit %d (%x)\n", i, exit, DC_Valid_Exit_Handles[exit]);

      aAIGoalGotoObject(objhandle, DC_Valid_Exit_Handles[exit], GOAL_PRIORITY_LOW,
                        GF_FORCE_AWARENESS | GF_ORIENT_VELOCITY, goalid);
      dc_nodes[i].type = DC_EXIT_GOAL;
      dc_nodes[i].type_index = exit;
      dc_nodes[i].goalid = goalid;
      dc_nodes[i].timer = 0.0f;
      DC_Exit_Mask |= (1 << exit); // reserve index

      break;
    }
    if (dc_nodes[i].handle == OBJECT_HANDLE_NONE) {
      free_slot = true;
    }
  }

  if (i == DC_N_DROIDS) {
    if (free_slot) {
      mprintf(0, "DC: Sending an unmanaged droid to exit.  Adding...\n");
      cAddObjToDroidManager(objhandle);
      cSendDroidObjToExit(objhandle); // recursive... safeguards should be already implemented above
    } else {
      // THING TO DO: should be force an object to leave here??
      mprintf(0, "DC: Droid Manager is Full!! We should force a droid to exit.\n");
    }
  }
}

/*
$$ACTION
Custom
Tell droid [o:Object] to find a computer terminal in Droid Central.
cSendDroidObjToTerm
Sends a message to a droid to find an exit.
        Sends droid out of Droid Central. If object is not a member of droid central, it adds it.

Parameters:
        Object: A robot
$$END
*/
void cSendDroidObjToTerm(int objhandle) {
  int i;
  bool free_slot = false;

  if (DC_EQR == -100) {
    return;
  }

  for (i = 0; i < DC_N_DROIDS; i++) {
    int j;

    if (dc_nodes[i].handle == objhandle) {
      // okay, find a free terminal
      int term = FIND_FREE_INDEX(DC_Term_Mask, DC_N_VALID_TERMS, false);
      int goalid = LEVEL_GOAL_UID(0, DC_Goal_Index++);

      if (term == -1) {
        // the terminals are full.  tell a droid to take a break (exit)
        // and put this droid in its place.
        for (j = 0; j < DC_N_DROIDS; j++) {
          if (dc_nodes[i].handle != OBJECT_HANDLE_NONE && dc_nodes[i].type == DC_TERM_GOAL) {
            cSendDroidObjToExit(dc_nodes[i].handle);
            term = dc_nodes[i].type_index;
            break;
          }
        }
        if (j == DC_N_DROIDS) {
          // this is IMPOSSIBLE if the sequencing and logic i have is right.
          // if there was no terminal, the above code checks for a full terminal and deallocates it.
          //	but just in case...
          term = rand() % DC_N_VALID_TERMS;
        }
      }

      // just in case, deallocate exit if this droid was leaving before...
      if (dc_nodes[i].type == DC_EXIT_GOAL) {
        DC_Exit_Mask &= ~(1 << dc_nodes[i].type_index);
      }

      mprintf(0, "DC: SENDING DROID [%d] to term %d (%x)\n", i, term, DC_Valid_Term_Handles[term]);

      aAIGoalGotoObject(objhandle, DC_Valid_Term_Handles[term], GOAL_PRIORITY_LOW,
                        GF_FORCE_AWARENESS | GF_ORIENT_VELOCITY, goalid);
      dc_nodes[i].type = DC_TERM_GOAL; // specify terminal to be allocated.
      dc_nodes[i].type_index = term;
      dc_nodes[i].goalid = goalid;
      dc_nodes[i].timer = 0.0f;
      DC_Term_Mask |= (1 << term);
      break;
    }
    if (dc_nodes[i].handle == OBJECT_HANDLE_NONE) {
      free_slot = true;
    }
  }

  if (i == DC_N_DROIDS) {
    if (free_slot) {
      mprintf(0, "DC: Sending an unmanaged droid to term.  Adding...\n");
      cAddObjToDroidManager(objhandle);
      cSendDroidObjToTerm(objhandle); // recursive... safeguards should be already implemented above
    } else {
      // THING TO DO: should be force an object to leave here??
      mprintf(0, "DC: Droid Manager is Full!! We should force a droid to exit.\n");
    }
  }
}

/*
$$ACTION
Custom
Droid Manager Frame Interval
cDroidManagerInterval
Manages the droid center
        This will 'intelligently' assign, create and destroy droids.

Parameters:
        None
$$END
*/
void cDroidManagerInterval() {
  // we should check if any object in our list still exists
  //		if not, and we didn't free it, then the player did
  //		and we should update DC_EQR to reflect this.
  int i;
  float roll;
  float saving_throw;
  float gametime = Game_GetTime();

  if (DC_EQR == -100) {
    return;
  }

  for (i = 0; i < DC_N_DROIDS; i++) {
    if (dc_nodes[i].handle != OBJECT_HANDLE_NONE) {
      if (!qObjExists(dc_nodes[i].handle)) {
        cRemoveObjFromDroidManager(dc_nodes[i].handle);
      } else {
        dc_nodes[i].timer += (gametime - DC_Last_Game_Time);
      }
    }
  }

  // okay, sometimes we need to create droids, and other times kill them.
  if (DC_EQR < 0) {
    //	tell a matcen to create a droid.
    cDroidManagerCreateNew();
  } else if (DC_EQR >= 0) {
    int ndroids = 0;
    int droids[DC_N_DROIDS];

    for (i = 0; i < DC_N_DROIDS; i++) {
      if (dc_nodes[i].handle != OBJECT_HANDLE_NONE) {
        droids[ndroids++] = i;
      }
    }

    if (ndroids) {
      //	if we have droids, do a random fate choice roll for them
      DCDetermineObjFate(dc_nodes[droids[rand() % ndroids]].handle, false);
      // randomly decide whether to add another bot.
      roll = (float)(rand() / (float)(RAND_MAX));
      saving_throw = (DC_Time_Since_Last_Create / 60.0f) * 0.5f;

      if (roll < saving_throw && DC_EQR == 0) {
        cDroidManagerCreateNew();
        mprintf(0, "DC: RANDOMLY CREATING NEW DROID.\n");
      }
    }
  }

  mprintf(0, "DC: Frame Interval DC_EQR = %d\n", DC_EQR);

  DC_Time_Since_Last_Create += (gametime - DC_Last_Game_Time);
  DC_Last_Game_Time = gametime;
}

//	given an object, check if on list, then determine whether it should be assigned a goal
// and WHICH goal to assign it.
// new droids should be put to work preferably instead of exiting, but add a little randomness to
// this.  also take into account the current DC_EQR!!!
void DCDetermineObjFate(int objhandle, bool new_droid) {
  int idx;

  for (idx = 0; idx < DC_N_DROIDS; idx++) {
    if (objhandle == dc_nodes[idx].handle) {
      if (dc_nodes[idx].type == -1) {
        float roll = (float)(rand() / (float)(RAND_MAX));
        float saving_throw = 0.30f + (DC_EQR * 0.15f);

        mprintf(0, "DC: Determining fate of DROID [%d] that has no goal.\n", idx);

        if (roll < saving_throw && !new_droid) {
          // droid will leave droid central
          cSendDroidObjToExit(objhandle);
        } else {
          // droid will go to a free terminal and bump someone off if there are none.
          cSendDroidObjToTerm(objhandle);
        }
      } else if (dc_nodes[idx].goalid == -1) {
        // robots already at goal.
        float roll = (float)(rand() / (float)(RAND_MAX));
        float saving_throw = (dc_nodes[idx].timer / 45.0f) * 0.40f;

        mprintf(0, "DC: Determining fate of DROID [%d] after %.2f seconds!\n", idx, dc_nodes[idx].timer);

        if (dc_nodes[idx].type == DC_TERM_GOAL) {
          if (roll < saving_throw) {
            // droid will leave droid central
            cSendDroidObjToExit(objhandle);
          } else {
            // droid will go to a free terminal and bump someone off if there are none.
            cSendDroidObjToTerm(objhandle);
          }
        }
      }
      // else {
      //	mprintf(0, "DC: DROID FATE IS ALREADY SEALED.  NO CHANGE.\n");
      //}
      break;
    }
  }

  if (idx == DC_N_DROIDS) {
    mprintf(0, "DC: DROID NOT IN LIST!!!\n");
  }
}

// Tell the code to call our functions
#define ENABLE_CUSTOM_SAVE_AND_RESTORE

// Save custom data for this script
void dsCustomSave(void *fileptr) {
  int i;

  //	write out timed events
  File_WriteByte(ff_index, fileptr);
  for (i = 0; i < 8; i++) {
    File_WriteShort(ff_enable_data[i].room_number, fileptr);
    File_WriteShort(ff_enable_data[i].portal_num, fileptr);
    File_WriteByte((int8_t)(ff_enable_data[i].state), fileptr);
    File_WriteByte((int8_t)(ff_enable_data[i].double_sided), fileptr);
  }

  File_WriteByte(wind_fx_index, fileptr);
  for (i = 0; i < 8; i++) {
    File_WriteInt(wind_fx_data[i].room_number, fileptr);
    File_WriteFloat(wind_fx_data[i].x, fileptr);
    File_WriteFloat(wind_fx_data[i].y, fileptr);
    File_WriteFloat(wind_fx_data[i].z, fileptr);
    File_WriteFloat(wind_fx_data[i].speed, fileptr);
  }

  // write DC_EQR
  File_WriteInt(DC_EQR, fileptr);

  //	write all nodes
  File_WriteByte(DC_Goal_Index, fileptr);
  for (i = 0; i < DC_N_DROIDS; i++) {
    File_WriteInt(dc_nodes[i].handle, fileptr);
    File_WriteInt(dc_nodes[i].type, fileptr);
    File_WriteInt(dc_nodes[i].type_index, fileptr);
    File_WriteInt(dc_nodes[i].goalid, fileptr);
    File_WriteFloat(dc_nodes[i].timer, fileptr);
    File_WriteFloat(dc_nodes[i].orig_maxspeed, fileptr);
  }

  File_WriteFloat(DC_Time_Since_Last_Create, fileptr);
  File_WriteFloat(DC_Last_Game_Time, fileptr);

  File_WriteInt(DC_Exit_Mask, fileptr);
  File_WriteInt(DC_Term_Mask, fileptr);
  File_WriteInt(DC_Matcen_Mask, fileptr);
}

// Restore custom data for this script
void dsCustomRestore(void *fileptr) {
  int i;

  //	read in timed events
  ff_index = File_ReadByte(fileptr);
  for (i = 0; i < 8; i++) {
    ff_enable_data[i].room_number = File_ReadShort(fileptr);
    ff_enable_data[i].portal_num = File_ReadShort(fileptr);
    ff_enable_data[i].state = (bool)File_ReadByte(fileptr);
    ff_enable_data[i].double_sided = (bool)File_ReadByte(fileptr);
  }

  wind_fx_index = File_ReadByte(fileptr);

  for (i = 0; i < 8; i++) {
    wind_fx_data[i].room_number = File_ReadInt(fileptr);
    wind_fx_data[i].x = File_ReadFloat(fileptr);
    wind_fx_data[i].y = File_ReadFloat(fileptr);
    wind_fx_data[i].z = File_ReadFloat(fileptr);
    wind_fx_data[i].speed = File_ReadFloat(fileptr);
  }

  // dc
  cResetDroidCentral();

  // read in DC_EQR
  DC_EQR = File_ReadInt(fileptr);

  //	read in all nodes
  DC_Goal_Index = File_ReadByte(fileptr);

  for (i = 0; i < DC_N_DROIDS; i++) {
    dc_nodes[i].handle = File_ReadInt(fileptr);
    dc_nodes[i].type = File_ReadInt(fileptr);
    dc_nodes[i].type_index = File_ReadInt(fileptr);
    dc_nodes[i].goalid = File_ReadInt(fileptr);
    dc_nodes[i].timer = File_ReadFloat(fileptr);
    dc_nodes[i].orig_maxspeed = File_ReadFloat(fileptr);
  }

  DC_Time_Since_Last_Create = File_ReadFloat(fileptr);
  DC_Last_Game_Time = File_ReadFloat(fileptr);

  DC_Exit_Mask = File_ReadInt(fileptr);
  DC_Term_Mask = File_ReadInt(fileptr);
  DC_Matcen_Mask = File_ReadInt(fileptr);
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
static const char *const Door_names[NUM_DOOR_NAMES] = {"BossDoor", "DroidDoor2"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 152
static const char *const Object_names[NUM_OBJECT_NAMES] = {"ParkSpew1",
                                                           "ParkSpew2",
                                                           "ParkSpew3",
                                                           "ParkSpew4",
                                                           "TargetIntro2",
                                                           "TargetIntro1",
                                                           "IntroSpew1",
                                                           "IntroSpew2",
                                                           "TheBomb",
                                                           "BST-1",
                                                           "BST-2",
                                                           "BST-3",
                                                           "BST-C6",
                                                           "BST-C5",
                                                           "BST-C4",
                                                           "BST-C3",
                                                           "BST-C2",
                                                           "BST-C1",
                                                           "BST-A-A",
                                                           "BST-A-B",
                                                           "BST-A-C",
                                                           "BST-B-A",
                                                           "BST-B-B",
                                                           "IG3C",
                                                           "IG3B",
                                                           "IG3A",
                                                           "IG2D",
                                                           "IG2C",
                                                           "IG2B",
                                                           "IG2A",
                                                           "IG1B",
                                                           "IG1A",
                                                           "TPower10",
                                                           "TGun10",
                                                           "TPower9",
                                                           "TGun9",
                                                           "TPower8",
                                                           "TGun8",
                                                           "TPower7",
                                                           "TGun7",
                                                           "TPower6",
                                                           "TGun6",
                                                           "TPower5",
                                                           "TGun5",
                                                           "TPower4",
                                                           "TGun4",
                                                           "TPower3",
                                                           "TGun3",
                                                           "TPower2",
                                                           "TGun2",
                                                           "TPower1",
                                                           "TGun1",
                                                           "MntLifterMatcenA",
                                                           "LoEnter1",
                                                           "LoEnter2",
                                                           "LoExit1",
                                                           "LoExit2",
                                                           "HiUpEntry1",
                                                           "HiUpEntry2",
                                                           "HiUpExit1",
                                                           "HiUpExit2",
                                                           "TopLifterMatcen",
                                                           "HiDnEntry1",
                                                           "HiDnEntry2",
                                                           "HiDnExit1",
                                                           "HiDnExit2",
                                                           "FireMan1",
                                                           "FireMan2",
                                                           "FireLight",
                                                           "BoxFire2B",
                                                           "BoxFire2A",
                                                           "BoxFire1B",
                                                           "BoxFire1A",
                                                           "NFire2B",
                                                           "NFire2A",
                                                           "NFire1B",
                                                           "NFire1A",
                                                           "Napalm2B",
                                                           "Napalm2A",
                                                           "Napalm1B",
                                                           "Napalm1A",
                                                           "FireSpew1",
                                                           "FireSpew2",
                                                           "FireHandle2",
                                                           "FireHandle1",
                                                           "HalonSpewer1",
                                                           "HalonSpewer-2",
                                                           "HalonSpewer3",
                                                           "HalonSpewer4",
                                                           "DroidDoor2",
                                                           "DroidFireDoor1",
                                                           "MGuard6",
                                                           "MGuard5",
                                                           "MGuard-4",
                                                           "MGuard-3",
                                                           "MGuard-2",
                                                           "MGuard-1",
                                                           "TPowerX",
                                                           "TGunX4",
                                                           "TGunX3",
                                                           "TGunX2",
                                                           "TGunX1",
                                                           "TGunX",
                                                           "EBarPlace",
                                                           "DaBomb",
                                                           "EndBoss",
                                                           "Julian",
                                                           "ShowBomb",
                                                           "PBomb",
                                                           "RedFlashBar",
                                                           "PNode3",
                                                           "PBar3",
                                                           "PNode2",
                                                           "PBar2",
                                                           "PNode1",
                                                           "PBar1",
                                                           "Suzuki",
                                                           "SZTarget1",
                                                           "SZTarget3",
                                                           "SZTarget2",
                                                           "SZSpot1",
                                                           "SZSpot2",
                                                           "PNode4",
                                                           "SZTarget4",
                                                           "PX1",
                                                           "PX2",
                                                           "PX3",
                                                           "PX4",
                                                           "PExplode1",
                                                           "PExplode2",
                                                           "PExplode3",
                                                           "SZ5Fire4",
                                                           "SZ5Fire3",
                                                           "SZ5Fire2",
                                                           "SZ5Fire1",
                                                           "SZTarget5",
                                                           "SZ5Fire2A",
                                                           "SZF1",
                                                           "SZF2",
                                                           "SZF3",
                                                           "SZF4",
                                                           "SZF5",
                                                           "SZF6",
                                                           "SZF7",
                                                           "SZF8",
                                                           "SZF9",
                                                           "SZF10",
                                                           "SZTarget6",
                                                           "SZF15",
                                                           "SZF13",
                                                           "SZF14",
                                                           "Start End Boss Cin"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 18
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "BossRoom",     "HiDnShaft",     "HiUpShaft",      "LoShaft",      "LoEntrance",   "LoExit",
    "HiUpEntrance", "HiUpExit",      "HiDnEntrance",   "HiDnExit",     "FireRoom",     "PreBoss",
    "SuzukiOffice", "DroidExplode1", "DroidExplosion", "DroidCommand", "ElevatorRoom", "PreFireRoom"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 16
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EnterMaintenence", "MntLifterInit", "StartUpperLifters", "BossRoomEntrance", "RoboDestroy", "DestroyMe",
    "MusicBoss",        "MusicSuzuki2",  "MusicSuzuki1",      "MusicMid4",        "MusicMid3",   "MusicMid2",
    "MusicMid1",        "MusicMaint2",   "MusicMaint1",       "MusicSewer1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 2
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSirenIntense", "AmbSwitch31"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 3
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"MeshGlass1", "FunkyEffectGreen", "FunkyEffect3"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 57
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCam-2",    "IntroCam-1",
                                                       "IntroCam-Ship", "IntroPlayerPath",
                                                       "BST-1",         "BST-2",
                                                       "BST-3",         "BST-C6",
                                                       "BST-C5",        "BST-C4",
                                                       "BST-C3",        "BST-C2",
                                                       "BST-C1",        "BST-A-1",
                                                       "BST-A-2",       "BST-A-3",
                                                       "BST-B-1",       "BST-B-2",
                                                       "IG-3",          "IG-2",
                                                       "IG-1",          "LoLeft1",
                                                       "LoRight1",      "LoEntry",
                                                       "LoExit",        "HiUp1",
                                                       "HiUpEntry",     "HiUpExit",
                                                       "HiRight1",      "HiLeft1",
                                                       "DnEntry",       "DnExit",
                                                       "FirePathIn",    "Fire2",
                                                       "Fire1",         "FirePathOut",
                                                       "Guards",        "BombPickup2",
                                                       "BombPickup1",   "BombTake",
                                                       "BossCam",       "SZCam1",
                                                       "SZCam2",        "BombDelivery",
                                                       "SZCam3",        "BombAfterDevlier",
                                                       "SZCam4",        "SuzukiFinalPath",
                                                       "SZCam6",        "DBorn1",
                                                       "DBorn2",        "DBorn3",
                                                       "DBorn4",        "DDie1",
                                                       "DDie2",         "DDie3",
                                                       "DDie4"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 10
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {
    "MntMatcenA",     "MntMatcenB", "TopLifterMatcen", "BombMatcen", "BomberMatcen-2",
    "BomberMatcen-1", "DCMatcen-1", "DCMatcen-2",      "DCMatcen-3", "DCMatcen-4"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 6
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Destroy the PTMC Assault Bot", "Create a Disturbance to Summon Droids", "Wait for Droids to Open Central Command",
    "Place Bomb on Delivery Pad",   "Get a Safe Distance from Bomb",         "Assasinate President Suzuki of PTMC"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 14
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "IntroMessage",  "EmptyMessage",  "BombInventory", "FiremenSummoning", "FiremenDone",
    "DroidOnlyDoor", "DeliveryReady", "BombPadFull",   "BombDropSuccess",  "BombDropFail",
    "BossName",      "SafeFromBomb",  "ActivateBomb",  "SuzukiDead"};
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
    strcpy(filename, "Merc7.msg");
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
  case ID_CUSTOM_OBJECT_0885:
    return new CustomObjectScript_0885;
    break;
  case ID_CUSTOM_OBJECT_0884:
    return new CustomObjectScript_0884;
    break;
  case ID_CUSTOM_OBJECT_0903:
    return new CustomObjectScript_0903;
    break;
  case ID_CUSTOM_OBJECT_0902:
    return new CustomObjectScript_0902;
    break;
  case ID_CUSTOM_OBJECT_0901:
    return new CustomObjectScript_0901;
    break;
  case ID_CUSTOM_OBJECT_1025:
    return new CustomObjectScript_1025;
    break;
  case ID_CUSTOM_OBJECT_103B:
    return new CustomObjectScript_103B;
    break;
  case ID_CUSTOM_OBJECT_1038:
    return new CustomObjectScript_1038;
    break;
  case ID_CUSTOM_OBJECT_2022:
    return new CustomObjectScript_2022;
    break;
  case ID_CUSTOM_OBJECT_10AF:
    return new CustomObjectScript_10AF;
    break;
  case ID_CUSTOM_OBJECT_20AA:
    return new CustomObjectScript_20AA;
    break;
  case ID_CUSTOM_OBJECT_1031:
    return new CustomObjectScript_1031;
    break;
  case ID_CUSTOM_OBJECT_0833:
    return new CustomObjectScript_0833;
    break;
  case ID_CUSTOM_OBJECT_0951:
    return new CustomObjectScript_0951;
    break;
  case ID_CUSTOM_OBJECT_0952:
    return new CustomObjectScript_0952;
    break;
  case ID_CUSTOM_OBJECT_0953:
    return new CustomObjectScript_0953;
    break;
  case ID_CUSTOM_OBJECT_0954:
    return new CustomObjectScript_0954;
    break;
  case ID_CUSTOM_OBJECT_095F:
    return new CustomObjectScript_095F;
    break;
  case ID_CUSTOM_OBJECT_0960:
    return new CustomObjectScript_0960;
    break;
  case ID_CUSTOM_OBJECT_0961:
    return new CustomObjectScript_0961;
    break;
  case ID_CUSTOM_OBJECT_0962:
    return new CustomObjectScript_0962;
    break;
  case ID_CUSTOM_OBJECT_0869:
    return new CustomObjectScript_0869;
    break;
  case ID_CUSTOM_OBJECT_0963:
    return new CustomObjectScript_0963;
    break;
  case ID_CUSTOM_OBJECT_0964:
    return new CustomObjectScript_0964;
    break;
  case ID_CUSTOM_OBJECT_0965:
    return new CustomObjectScript_0965;
    break;
  case ID_CUSTOM_OBJECT_0966:
    return new CustomObjectScript_0966;
    break;
  case ID_CUSTOM_OBJECT_0995:
    return new CustomObjectScript_0995;
    break;
  case ID_CUSTOM_OBJECT_0994:
    return new CustomObjectScript_0994;
    break;
  case ID_CUSTOM_OBJECT_0993:
    return new CustomObjectScript_0993;
    break;
  case ID_CUSTOM_OBJECT_0992:
    return new CustomObjectScript_0992;
    break;
  case ID_CUSTOM_OBJECT_1191:
    return new CustomObjectScript_1191;
    break;
  case ID_CUSTOM_OBJECT_083D:
    return new CustomObjectScript_083D;
    break;
  case ID_CUSTOM_OBJECT_103C:
    return new CustomObjectScript_103C;
    break;
  case ID_CUSTOM_OBJECT_103E:
    return new CustomObjectScript_103E;
    break;
  case ID_CUSTOM_OBJECT_0841:
    return new CustomObjectScript_0841;
    break;
  case ID_CUSTOM_OBJECT_097A:
    return new CustomObjectScript_097A;
    break;
  case ID_CUSTOM_OBJECT_0997:
    return new CustomObjectScript_0997;
    break;
  case ID_CUSTOM_OBJECT_0996:
    return new CustomObjectScript_0996;
    break;
  case ID_CUSTOM_OBJECT_0805:
    return new CustomObjectScript_0805;
    break;
  case ID_CUSTOM_OBJECT_0804:
    return new CustomObjectScript_0804;
    break;
  case ID_CUSTOM_OBJECT_0998:
    return new CustomObjectScript_0998;
    break;
  case ID_CUSTOM_OBJECT_087E:
    return new CustomObjectScript_087E;
    break;
  case ID_CUSTOM_OBJECT_1834:
    return new CustomObjectScript_1834;
    break;
  case ID_CUSTOM_OBJECT_1877:
    return new CustomObjectScript_1877;
    break;
  case ID_CUSTOM_OBJECT_1078:
    return new CustomObjectScript_1078;
    break;
  case ID_CUSTOM_OBJECT_1070:
    return new CustomObjectScript_1070;
    break;
  case ID_CUSTOM_OBJECT_2075:
    return new CustomObjectScript_2075;
    break;
  case ID_CUSTOM_OBJECT_2076:
    return new CustomObjectScript_2076;
    break;
  case ID_CUSTOM_OBJECT_2863:
    return new CustomObjectScript_2863;
    break;
  case ID_CUSTOM_OBJECT_207A:
    return new CustomObjectScript_207A;
    break;
  case ID_CUSTOM_OBJECT_206D:
    return new CustomObjectScript_206D;
    break;
  case ID_CUSTOM_OBJECT_1079:
    return new CustomObjectScript_1079;
    break;
  case ID_CUSTOM_OBJECT_09BF:
    return new CustomObjectScript_09BF;
    break;
  case ID_CUSTOM_OBJECT_09BE:
    return new CustomObjectScript_09BE;
    break;
  case ID_CUSTOM_OBJECT_09BD:
    return new CustomObjectScript_09BD;
    break;
  case ID_CUSTOM_OBJECT_09BC:
    return new CustomObjectScript_09BC;
    break;
  case ID_CUSTOM_OBJECT_1071:
    return new CustomObjectScript_1071;
    break;
  case ID_CUSTOM_OBJECT_09CA:
    return new CustomObjectScript_09CA;
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
  case ID_CUSTOM_OBJECT_286E:
    return new CustomObjectScript_286E;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
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
  case ID_CUSTOM_OBJECT_0885:
    delete ((CustomObjectScript_0885 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0884:
    delete ((CustomObjectScript_0884 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0903:
    delete ((CustomObjectScript_0903 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0902:
    delete ((CustomObjectScript_0902 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0901:
    delete ((CustomObjectScript_0901 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1025:
    delete ((CustomObjectScript_1025 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_103B:
    delete ((CustomObjectScript_103B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1038:
    delete ((CustomObjectScript_1038 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2022:
    delete ((CustomObjectScript_2022 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10AF:
    delete ((CustomObjectScript_10AF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20AA:
    delete ((CustomObjectScript_20AA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1031:
    delete ((CustomObjectScript_1031 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0833:
    delete ((CustomObjectScript_0833 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0951:
    delete ((CustomObjectScript_0951 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0952:
    delete ((CustomObjectScript_0952 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0953:
    delete ((CustomObjectScript_0953 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0954:
    delete ((CustomObjectScript_0954 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_095F:
    delete ((CustomObjectScript_095F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0960:
    delete ((CustomObjectScript_0960 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0961:
    delete ((CustomObjectScript_0961 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0962:
    delete ((CustomObjectScript_0962 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0869:
    delete ((CustomObjectScript_0869 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0963:
    delete ((CustomObjectScript_0963 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0964:
    delete ((CustomObjectScript_0964 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0965:
    delete ((CustomObjectScript_0965 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0966:
    delete ((CustomObjectScript_0966 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0995:
    delete ((CustomObjectScript_0995 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0994:
    delete ((CustomObjectScript_0994 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0993:
    delete ((CustomObjectScript_0993 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0992:
    delete ((CustomObjectScript_0992 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1191:
    delete ((CustomObjectScript_1191 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083D:
    delete ((CustomObjectScript_083D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_103C:
    delete ((CustomObjectScript_103C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_103E:
    delete ((CustomObjectScript_103E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0841:
    delete ((CustomObjectScript_0841 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097A:
    delete ((CustomObjectScript_097A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0997:
    delete ((CustomObjectScript_0997 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0996:
    delete ((CustomObjectScript_0996 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0805:
    delete ((CustomObjectScript_0805 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0804:
    delete ((CustomObjectScript_0804 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0998:
    delete ((CustomObjectScript_0998 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087E:
    delete ((CustomObjectScript_087E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1834:
    delete ((CustomObjectScript_1834 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1877:
    delete ((CustomObjectScript_1877 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1078:
    delete ((CustomObjectScript_1078 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1070:
    delete ((CustomObjectScript_1070 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2075:
    delete ((CustomObjectScript_2075 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2076:
    delete ((CustomObjectScript_2076 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2863:
    delete ((CustomObjectScript_2863 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_207A:
    delete ((CustomObjectScript_207A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_206D:
    delete ((CustomObjectScript_206D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1079:
    delete ((CustomObjectScript_1079 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BF:
    delete ((CustomObjectScript_09BF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BE:
    delete ((CustomObjectScript_09BE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BD:
    delete ((CustomObjectScript_09BD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09BC:
    delete ((CustomObjectScript_09BC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1071:
    delete ((CustomObjectScript_1071 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09CA:
    delete ((CustomObjectScript_09CA *)ptr);
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
  case ID_CUSTOM_OBJECT_286E:
    delete ((CustomObjectScript_286E *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
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
  case ID_CUSTOM_OBJECT_0885:
  case ID_CUSTOM_OBJECT_0884:
  case ID_CUSTOM_OBJECT_0903:
  case ID_CUSTOM_OBJECT_0902:
  case ID_CUSTOM_OBJECT_0901:
  case ID_CUSTOM_OBJECT_1025:
  case ID_CUSTOM_OBJECT_103B:
  case ID_CUSTOM_OBJECT_1038:
  case ID_CUSTOM_OBJECT_2022:
  case ID_CUSTOM_OBJECT_10AF:
  case ID_CUSTOM_OBJECT_20AA:
  case ID_CUSTOM_OBJECT_1031:
  case ID_CUSTOM_OBJECT_0833:
  case ID_CUSTOM_OBJECT_0951:
  case ID_CUSTOM_OBJECT_0952:
  case ID_CUSTOM_OBJECT_0953:
  case ID_CUSTOM_OBJECT_0954:
  case ID_CUSTOM_OBJECT_095F:
  case ID_CUSTOM_OBJECT_0960:
  case ID_CUSTOM_OBJECT_0961:
  case ID_CUSTOM_OBJECT_0962:
  case ID_CUSTOM_OBJECT_0869:
  case ID_CUSTOM_OBJECT_0963:
  case ID_CUSTOM_OBJECT_0964:
  case ID_CUSTOM_OBJECT_0965:
  case ID_CUSTOM_OBJECT_0966:
  case ID_CUSTOM_OBJECT_0995:
  case ID_CUSTOM_OBJECT_0994:
  case ID_CUSTOM_OBJECT_0993:
  case ID_CUSTOM_OBJECT_0992:
  case ID_CUSTOM_OBJECT_1191:
  case ID_CUSTOM_OBJECT_083D:
  case ID_CUSTOM_OBJECT_103C:
  case ID_CUSTOM_OBJECT_103E:
  case ID_CUSTOM_OBJECT_0841:
  case ID_CUSTOM_OBJECT_097A:
  case ID_CUSTOM_OBJECT_0997:
  case ID_CUSTOM_OBJECT_0996:
  case ID_CUSTOM_OBJECT_0805:
  case ID_CUSTOM_OBJECT_0804:
  case ID_CUSTOM_OBJECT_0998:
  case ID_CUSTOM_OBJECT_087E:
  case ID_CUSTOM_OBJECT_1834:
  case ID_CUSTOM_OBJECT_1877:
  case ID_CUSTOM_OBJECT_1078:
  case ID_CUSTOM_OBJECT_1070:
  case ID_CUSTOM_OBJECT_2075:
  case ID_CUSTOM_OBJECT_2076:
  case ID_CUSTOM_OBJECT_2863:
  case ID_CUSTOM_OBJECT_207A:
  case ID_CUSTOM_OBJECT_206D:
  case ID_CUSTOM_OBJECT_1079:
  case ID_CUSTOM_OBJECT_09BF:
  case ID_CUSTOM_OBJECT_09BE:
  case ID_CUSTOM_OBJECT_09BD:
  case ID_CUSTOM_OBJECT_09BC:
  case ID_CUSTOM_OBJECT_1071:
  case ID_CUSTOM_OBJECT_09CA:
  case ID_CUSTOM_OBJECT_09C9:
  case ID_CUSTOM_OBJECT_09C8:
  case ID_CUSTOM_OBJECT_09C7:
  case ID_CUSTOM_OBJECT_09C6:
  case ID_CUSTOM_OBJECT_09C5:
  case ID_CUSTOM_OBJECT_09C4:
  case ID_CUSTOM_OBJECT_09C3:
  case ID_CUSTOM_OBJECT_09C2:
  case ID_CUSTOM_OBJECT_286E:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_000B:
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
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_000B;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[67];
  static int cust_id_list[67] = {
      ID_CUSTOM_OBJECT_0885, ID_CUSTOM_OBJECT_0884, ID_CUSTOM_OBJECT_0903, ID_CUSTOM_OBJECT_0902, ID_CUSTOM_OBJECT_0901,
      ID_CUSTOM_OBJECT_1025, ID_CUSTOM_OBJECT_103B, ID_CUSTOM_OBJECT_1038, ID_CUSTOM_OBJECT_2022, ID_CUSTOM_OBJECT_10AF,
      ID_CUSTOM_OBJECT_20AA, ID_CUSTOM_OBJECT_1031, ID_CUSTOM_OBJECT_0833, ID_CUSTOM_OBJECT_0951, ID_CUSTOM_OBJECT_0952,
      ID_CUSTOM_OBJECT_0953, ID_CUSTOM_OBJECT_0954, ID_CUSTOM_OBJECT_095F, ID_CUSTOM_OBJECT_0960, ID_CUSTOM_OBJECT_0961,
      ID_CUSTOM_OBJECT_0962, ID_CUSTOM_OBJECT_0869, ID_CUSTOM_OBJECT_0963, ID_CUSTOM_OBJECT_0964, ID_CUSTOM_OBJECT_0965,
      ID_CUSTOM_OBJECT_0966, ID_CUSTOM_OBJECT_0995, ID_CUSTOM_OBJECT_0994, ID_CUSTOM_OBJECT_0993, ID_CUSTOM_OBJECT_0992,
      ID_CUSTOM_OBJECT_1191, ID_CUSTOM_OBJECT_083D, ID_CUSTOM_OBJECT_103C, ID_CUSTOM_OBJECT_103E, ID_CUSTOM_OBJECT_0841,
      ID_CUSTOM_OBJECT_097A, ID_CUSTOM_OBJECT_0997, ID_CUSTOM_OBJECT_0996, ID_CUSTOM_OBJECT_0805, ID_CUSTOM_OBJECT_0804,
      ID_CUSTOM_OBJECT_0998, ID_CUSTOM_OBJECT_087E, ID_CUSTOM_OBJECT_1834, ID_CUSTOM_OBJECT_1877, ID_CUSTOM_OBJECT_1078,
      ID_CUSTOM_OBJECT_1070, ID_CUSTOM_OBJECT_2075, ID_CUSTOM_OBJECT_2076, ID_CUSTOM_OBJECT_2863, ID_CUSTOM_OBJECT_207A,
      ID_CUSTOM_OBJECT_206D, ID_CUSTOM_OBJECT_1079, ID_CUSTOM_OBJECT_09BF, ID_CUSTOM_OBJECT_09BE, ID_CUSTOM_OBJECT_09BD,
      ID_CUSTOM_OBJECT_09BC, ID_CUSTOM_OBJECT_1071, ID_CUSTOM_OBJECT_09CA, ID_CUSTOM_OBJECT_09C9, ID_CUSTOM_OBJECT_09C8,
      ID_CUSTOM_OBJECT_09C7, ID_CUSTOM_OBJECT_09C6, ID_CUSTOM_OBJECT_09C5, ID_CUSTOM_OBJECT_09C4, ID_CUSTOM_OBJECT_09C3,
      ID_CUSTOM_OBJECT_09C2, ID_CUSTOM_OBJECT_286E};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[4];
  cust_handle_list[1] = Object_handles[5];
  cust_handle_list[2] = Object_handles[32];
  cust_handle_list[3] = Object_handles[34];
  cust_handle_list[4] = Object_handles[36];
  cust_handle_list[5] = Object_handles[38];
  cust_handle_list[6] = Object_handles[40];
  cust_handle_list[7] = Object_handles[42];
  cust_handle_list[8] = Object_handles[44];
  cust_handle_list[9] = Object_handles[46];
  cust_handle_list[10] = Object_handles[48];
  cust_handle_list[11] = Object_handles[50];
  cust_handle_list[12] = Object_handles[52];
  cust_handle_list[13] = Object_handles[53];
  cust_handle_list[14] = Object_handles[54];
  cust_handle_list[15] = Object_handles[55];
  cust_handle_list[16] = Object_handles[56];
  cust_handle_list[17] = Object_handles[57];
  cust_handle_list[18] = Object_handles[58];
  cust_handle_list[19] = Object_handles[59];
  cust_handle_list[20] = Object_handles[60];
  cust_handle_list[21] = Object_handles[61];
  cust_handle_list[22] = Object_handles[62];
  cust_handle_list[23] = Object_handles[63];
  cust_handle_list[24] = Object_handles[64];
  cust_handle_list[25] = Object_handles[65];
  cust_handle_list[26] = Object_handles[68];
  cust_handle_list[27] = Object_handles[69];
  cust_handle_list[28] = Object_handles[70];
  cust_handle_list[29] = Object_handles[71];
  cust_handle_list[30] = Object_handles[72];
  cust_handle_list[31] = Object_handles[77];
  cust_handle_list[32] = Object_handles[78];
  cust_handle_list[33] = Object_handles[79];
  cust_handle_list[34] = Object_handles[80];
  cust_handle_list[35] = Object_handles[81];
  cust_handle_list[36] = Object_handles[67];
  cust_handle_list[37] = Object_handles[66];
  cust_handle_list[38] = Object_handles[89];
  cust_handle_list[39] = Object_handles[90];
  cust_handle_list[40] = Object_handles[97];
  cust_handle_list[41] = Object_handles[8];
  cust_handle_list[42] = Object_handles[105];
  cust_handle_list[43] = Object_handles[118];
  cust_handle_list[44] = Object_handles[117];
  cust_handle_list[45] = Object_handles[119];
  cust_handle_list[46] = Object_handles[108];
  cust_handle_list[47] = Object_handles[122];
  cust_handle_list[48] = Object_handles[114];
  cust_handle_list[49] = Object_handles[112];
  cust_handle_list[50] = Object_handles[110];
  cust_handle_list[51] = Object_handles[123];
  cust_handle_list[52] = Object_handles[131];
  cust_handle_list[53] = Object_handles[132];
  cust_handle_list[54] = Object_handles[133];
  cust_handle_list[55] = Object_handles[134];
  cust_handle_list[56] = Object_handles[135];
  cust_handle_list[57] = Object_handles[146];
  cust_handle_list[58] = Object_handles[145];
  cust_handle_list[59] = Object_handles[144];
  cust_handle_list[60] = Object_handles[143];
  cust_handle_list[61] = Object_handles[142];
  cust_handle_list[62] = Object_handles[141];
  cust_handle_list[63] = Object_handles[140];
  cust_handle_list[64] = Object_handles[139];
  cust_handle_list[65] = Object_handles[138];
  cust_handle_list[66] = Object_handles[147];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 67;
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

    // Script 037: Start Bomb Sequence
    if ((ScriptActionCtr_037 < 1) && ((qUserFlag(7) == true) && (qRoomHasPlayer(Room_indexes[11]) == true))) {
      aGoalCompleted(Goal_indexes[4], 1);
      aDoorSetPos(Door_handles[1], 0.000000f);
      aShowHUDMessage(Message_strings[12]);
      aSetLevelTimer(3.000000f, 12);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 074: IntroCam-1
    if (1 == true) {
      aTurnOnSpew(Object_handles[0], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, -1.000000f, 5.000000f,
                  30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[1], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, -1.000000f, 5.000000f,
                  30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[2], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, -1.000000f, 5.000000f,
                  30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[3], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, -1.000000f, 5.000000f,
                  30.000000f, 0, -1);
      aCinematicSimple(Path_indexes[0], Message_strings[0], Object_handles[4], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }

    // Script 087: INIT GlassWindows
    if (1) {
      aRoomSetFaceTexture(Room_indexes[0], 15, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 14, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 13, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 12, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 11, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 10, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 9, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 8, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 7, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 6, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 5, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 4, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 3, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 2, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 1, Texture_indexes[0]);
      aRoomSetFaceTexture(Room_indexes[0], 0, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }

    // Script 019: INIT Variables/Flags
    if (1) {
      aGoalEnableDisable(0, Goal_indexes[0]);
      aUserFlagSet(7, 0);
      aUserFlagSet(0, 0);
      aUserVarSet(0, 0.000000f);
      aAddObjectToInventoryNamed(Object_handles[8], qPlayerClosest(Object_handles[8], -1), Message_strings[2], 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aUserFlagSet(6, 0);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 105: BST Patrols (Sewer)
    if ((ScriptActionCtr_105 < 1) && (1)) {
      aAIGoalFollowPathSimple(Object_handles[9], Path_indexes[4], 10490113, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[10], Path_indexes[5], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[11], Path_indexes[6], 10490113, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }

    // Script 002: INIT ElevDroids
    if ((ScriptActionCtr_002 < 1) && (1)) {
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aPortalRenderSet(0, 1, Room_indexes[1], 1);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aPortalRenderSet(0, 1, Room_indexes[2], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aPortalRenderSet(0, 1, Room_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 003: INIT Fire
    if (1) {
      aAISetMaxSpeed(Object_handles[66], 25.000000f);
      aAISetMaxSpeed(Object_handles[67], 25.000000f);
      aObjSetMovementType(Object_handles[68], 0);
      aObjSetLightingColor(Object_handles[68], 1.000000f, 0.250000f, 0.000000f);
      aObjSetLightingDist(Object_handles[68], 0.000000f);
      aObjMakeInvuln(Object_handles[66], 99999);
      aObjMakeInvuln(Object_handles[67], 99999);
      aObjMakeInvuln(Object_handles[69], 99999);
      aObjMakeInvuln(Object_handles[70], 99999);
      aObjMakeInvuln(Object_handles[71], 99999);
      aObjMakeInvuln(Object_handles[72], 99999);
      aObjGhostSet(1, Object_handles[69]);
      aObjGhostSet(1, Object_handles[70]);
      aObjGhostSet(1, Object_handles[71]);
      aObjGhostSet(1, Object_handles[72]);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 038: INIT Bomb Delivery
    if (1) {
      aUserFlagSet(8, 0);
      aMatcenSetState(1, Matcen_indexes[3]);
      aObjGhostSet(1, Object_handles[103]);
      aObjGhostSet(1, Object_handles[104]);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 020: INIT Suzuki's Death
    if (1) {
      aObjSaveHandle(Object_handles[106], 11);
      aAIGoalPickUpObjectRad(Object_handles[106], 0, Object_handles[107], 0.600000f, 3, 256, -1);
      aAISetMaxSpeed(qObjSavedHandle(11), 20.000000f);
      aObjGhostSet(1, Object_handles[108]);
      aObjGhostSet(1, Object_handles[109]);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 004: INIT Droid Central
    if (1) {
      aSetLevelTimer(2.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 119: Hide the end boss cinematic inv. powerup
    if (1) {
      aObjHide(Object_handles[151]);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }

    // Script 000: MusicIntro
    if (1) {
      aSetLevelTimer(2.000000f, 1);
      aMusicSetRegionAll(0);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 045: Suzuki Cam 1
    if ((ScriptActionCtr_045 < 1) && (event_data->id == 12)) {
      aLightningCreate(Object_handles[110], Object_handles[111], 99999.000000f, 2.000000f, 1, Texture_indexes[1],
                       0.400000f, 3, 200, 255, 150, 0);
      aLightningCreate(Object_handles[112], Object_handles[113], 99999.000000f, 2.000000f, 1, Texture_indexes[1],
                       0.400000f, 3, 200, 255, 150, 0);
      aLightningCreate(Object_handles[114], Object_handles[115], 99999.000000f, 2.000000f, 1, Texture_indexes[1],
                       0.400000f, 3, 200, 255, 150, 0);
      aObjPlayAnim(Object_handles[116], 0, 54, 6.000000f, 0);
      aCinematicSimple(Path_indexes[41], Message_strings[1], Object_handles[117], 6.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 007: Create A New Droid
    if (event_data->id == 13) {
      aSetLevelTimer(qRandomValue(2.000000f, 12.000000f), 13);
      if (qRandomChance(0.250000f) == true) {
        aMatcenSetState(1, Matcen_indexes[6]);
      } else {
        if (qRandomChance(0.333333f) == true) {
          aMatcenSetState(1, Matcen_indexes[7]);
        } else {
          if (qRandomChance(0.500000f) == true) {
            aMatcenSetState(1, Matcen_indexes[8]);
          } else {
            aMatcenSetState(1, Matcen_indexes[9]);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 120: MusicSewer (Intro2)
    if ((ScriptActionCtr_120 < 1) && (event_data->id == 1)) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }

    // Script 021: End Level
    if (event_data->id == 14) {
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 008: ElevDroids Reached OutsideLo
    if (event_data->goal_uid == 0) {
      aSetObjectTimer(Object_handles[53], 5.000000f, -1);
      aTurnOnSpew(Object_handles[53], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[54], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aPortalRenderSet(0, 0, Room_indexes[4], 1);
      aPortalRenderSet(1, 0, Room_indexes[3], 1);
      aPortalRenderSet(1, 1, Room_indexes[3], 1);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[23], 4352, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 106: ElevDroids Reached InsideHiDn
    if (event_data->goal_uid == 6) {
      aObjSaveHandle(event_data->it_handle, 9);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }

    // Script 059: ElevDroids Reached InsideHiUp
    if (event_data->goal_uid == 3) {
      aObjSaveHandle(event_data->it_handle, 7);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }

    // Script 016: ElevDroids Reached InsideLo
    if (event_data->goal_uid == 1) {
      aObjSaveHandle(event_data->it_handle, 6);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 017: ElevDroids Reached End Of Line
    if (event_data->goal_uid == 4) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 058: ElevDroids Reached OutsideHiUp
    if (event_data->goal_uid == 2) {
      aSetObjectTimer(Object_handles[57], 5.000000f, -1);
      aTurnOnSpew(Object_handles[57], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[58], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aPortalRenderSet(0, 0, Room_indexes[6], 1);
      aPortalRenderSet(1, 0, Room_indexes[2], 1);
      aPortalRenderSet(1, 1, Room_indexes[2], 1);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[26], 2101504, 3, 3);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }

    // Script 068: ElevDroids Reached OutsideHiDn
    if (event_data->goal_uid == 5) {
      aSetObjectTimer(Object_handles[62], 5.000000f, -1);
      aTurnOnSpew(Object_handles[62], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[63], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aPortalRenderSet(0, 0, Room_indexes[8], 1);
      aPortalRenderSet(1, 0, Room_indexes[1], 1);
      aPortalRenderSet(1, 1, Room_indexes[1], 1);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[30], 4352, 6, 3);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }

    // Script 041: BomberReadyToPickup
    if (event_data->goal_uid == 21) {
      if (qObjExists(qObjSavedHandle(4)) == true) {
        aAIGoalPickUpObjectRad(event_data->it_handle, 0, qObjSavedHandle(4), 1.000000f, 3, 256, 20);
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[39], 4352, 22, 0);
      } else {
        if (qUserFlag(4) == true) {
          aUserFlagSet(7, 1);
          aShowHUDMessage(Message_strings[6]);
          aAIGoalPickUpObjectRad(event_data->it_handle, 0, Object_handles[104], 0.600000f, 3, 256, 20);
        } else {
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[39], 4352, 22, 3);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }

    // Script 042: BomberPickedUp
    if (event_data->goal_uid == 20) {
      if (qUserFlag(4) == true) {
        aUserFlagSet(3, 1);
        aUserFlagSet(4, 0);
      }
      aUserFlagSet(2, 1);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[39], 4352, 22, 3);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 043: BomberDoneRun
    if (event_data->goal_uid == 22) {
      if (qUserFlag(4) == false) {
        aUserFlagSet(8, 1);
        aMatcenSetState(1, Matcen_indexes[3]);
      } else {
        aMatcenSetState(1, Matcen_indexes[5]);
      }
      if (qUserFlag(3) == false) {
        if (qObjExists(qGetAtachedChild(event_data->it_handle, 0)) == true) {
          aObjDelete(qGetAtachedChild(event_data->it_handle, 0));
        }
        aObjDelete(event_data->it_handle);
      } else {
        aUserFlagSet(3, 0);
      }
      aUserFlagSet(2, 0);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }

    // Script 012: Droid Choose A Death
    if (event_data->goal_uid == 7) {
      if (qRandomChance(0.250000f) == true) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[53], 4352, 8, 0);
      } else {
        if (qRandomChance(0.333333f) == true) {
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[54], 4352, 8, 0);
        } else {
          if (qRandomChance(0.500000f) == true) {
            aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[55], 4352, 8, 0);
          } else {
            aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[56], 4352, 8, 0);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 013: Droid Die
    if (event_data->goal_uid == 8) {
      aObjDelete(event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 065: ElevDroids Created Left
    if (event_data->id == Matcen_indexes[1]) {
      aObjSaveHandle(event_data->it_handle, 10);
      aMatcenSetState(0, event_data->id);
      aAIGoalSetCircleDistance(event_data->it_handle, 3, 5.000000f);
      aAISetMaxSpeed(event_data->it_handle, 25.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[21], 4352, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }

    // Script 006: ElevDroids Created Right
    if (event_data->id == Matcen_indexes[0]) {
      aObjSaveHandle(event_data->it_handle, 10);
      aMatcenSetState(0, event_data->id);
      aAIGoalSetCircleDistance(event_data->it_handle, 3, 5.000000f);
      aAISetMaxSpeed(event_data->it_handle, 25.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[22], 4352, 0, 3);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 066: ElevDroids Created Tower
    if (event_data->id == Matcen_indexes[2]) {
      aMatcenSetState(0, event_data->id);
      aAIGoalSetCircleDistance(event_data->it_handle, 3, 5.000000f);
      aAISetMaxSpeed(event_data->it_handle, 25.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[29], 4352, 5, 3);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }

    // Script 039: Created New Bomb
    if (event_data->id == Matcen_indexes[3]) {
      aMatcenSetState(0, Matcen_indexes[3]);
      aUserFlagSet(8, 0);
      aStoreObjectInPositionClipboard(Object_handles[103]);
      aMoveObjectToPositionClipboard(event_data->it_handle);
      aObjSaveHandle(event_data->it_handle, 4);
      if (qRandomChance(0.550000f) == true) {
        aMatcenSetState(1, Matcen_indexes[4]);
      } else {
        aMatcenSetState(1, Matcen_indexes[5]);
      }
      aObjSpark(event_data->it_handle, 30.000000f, 3.000000f);
      aEmitSparks(50.000000f, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 044: Bomber Created-2
    if (event_data->id == Matcen_indexes[4]) {
      aObjSaveHandle(event_data->it_handle, 3);
      aMatcenSetState(0, event_data->id);
      aObjMakeInvuln(event_data->it_handle, 99999);
      aAISetMaxSpeed(event_data->it_handle, 25.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[37], 2101504, 21, 3);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 040: Bomber Created-1
    if (event_data->id == Matcen_indexes[5]) {
      aObjSaveHandle(event_data->it_handle, 3);
      aMatcenSetState(0, event_data->id);
      aObjMakeInvuln(event_data->it_handle, 99999);
      aAISetMaxSpeed(event_data->it_handle, 25.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[38], 2101504, 21, 3);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 009: Send New Droid To Command
    if ((event_data->id == Matcen_indexes[6]) || (event_data->id == Matcen_indexes[7]) ||
        (event_data->id == Matcen_indexes[8]) || (event_data->id == Matcen_indexes[9])) {
      if (event_data->id == Matcen_indexes[6]) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[49], 4352, 7, 0);
      }
      if (event_data->id == Matcen_indexes[7]) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[50], 4352, 7, 0);
      }
      if (event_data->id == Matcen_indexes[8]) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[51], 4352, 7, 0);
      }
      if (event_data->id == Matcen_indexes[9]) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[52], 4352, 7, 0);
      }
      aMatcenSetState(0, event_data->id);
      aAISetMaxSpeed(event_data->it_handle, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  case EVT_LEVEL_GOAL_COMPLETE: {
    tOSIRISEVTLEVELGOALCOMPLETE *event_data = &data->evt_level_goal_complete;

    // Script 113: IntruderAlert!
    if ((ScriptActionCtr_113 < 1) && (event_data->level_goal_index == Goal_indexes[2])) {
      aAIGoalFollowPathSimple(Object_handles[91], Path_indexes[36], 4353, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[92], Path_indexes[36], 4353, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[93], Path_indexes[36], 4353, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[94], Path_indexes[36], 4353, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[95], Path_indexes[36], 4353, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[96], Path_indexes[36], 4353, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0885::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 088: IntroCam-2
    if ((ScriptActionCtr_088 < 1) && (1)) {
      aCinematicSimple(Path_indexes[1], Message_strings[1], Object_handles[5], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0884::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 089: IntroCam-3
    if ((ScriptActionCtr_089 < 1) && (1)) {
      aTurnOnSpew(Object_handles[6], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[7], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aCinematicIntro(Path_indexes[2], Message_strings[1], data->me_handle, Path_indexes[3], 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0903::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 099: Turret Power-10
    if (1) {
      aObjSaveHandle(Object_handles[33], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0902::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 098: Turret Power-9
    if (1) {
      aObjSaveHandle(Object_handles[35], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0901::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 097: Turret Power-8
    if (1) {
      aObjSaveHandle(Object_handles[37], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 096: Turret Power-7
    if (1) {
      aObjSaveHandle(Object_handles[39], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_103B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 095: Turret Power-6
    if (1) {
      aObjSaveHandle(Object_handles[41], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1038::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 094: Turret Power-5
    if (1) {
      aObjSaveHandle(Object_handles[43], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 093: Turret Power-4
    if (1) {
      aObjSaveHandle(Object_handles[45], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10AF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 092: Turret Power-3
    if (1) {
      aObjSaveHandle(Object_handles[47], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20AA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 091: Turret Power-2
    if (1) {
      aObjSaveHandle(Object_handles[49], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));
      aAISetFOV(qObjSavedHandle(8), 360.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1031::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 090: Turret Power-1
    if (1) {
      aObjSaveHandle(Object_handles[51], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetFOV(qObjSavedHandle(8), 360.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0833::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 018: ElevDroids MakeNew
    if (1) {
      if (qRandomChance(0.500000f) == true) {
        aMatcenSetState(1, Matcen_indexes[0]);
      } else {
        aMatcenSetState(1, Matcen_indexes[1]);
      }
      aSetObjectTimer(Object_handles[52], 40.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0951::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 010: ElevLoPart2
    if (1) {
      aMiscShakeArea(data->me_handle, 30.000000f, 300.000000f);
      aSetObjectTimer(Object_handles[54], 3.000000f, -1);
      aPortalRenderSet(1, 1, Room_indexes[5], 1);
      aPortalRenderSet(1, 0, Room_indexes[4], 1);
      aRoomChangeFog(Room_indexes[5], 0.200000f, 1.000000f, 1.000000f, 80.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[3], 0.200000f, 1.000000f, 1.000000f, 160.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[4], 0.200000f, 1.000000f, 1.000000f, 80.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0952::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 011: ElevLoPart3
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[3], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(6), Path_indexes[24], 131328, -1, 3);
      aMiscShakeArea(data->me_handle, 50.000000f, 300.000000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, 1.000000f, 0.000000f, 40.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, 1.000000f, 0.000000f, 20.000000f);
      aSetObjectTimer(Object_handles[55], 8.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0953::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 014: ElevLoPart4
    if (1) {
      aTurnOnSpew(Object_handles[56], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[55], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aMiscShakeArea(data->me_handle, 30.000000f, 300.000000f);
      aSetObjectTimer(Object_handles[56], 3.000000f, -1);
      aPortalRenderSet(1, 1, Room_indexes[3], 1);
      aPortalRenderSet(1, 0, Room_indexes[3], 1);
      aRoomSetWind(Room_indexes[5], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[4], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomChangeFog(Room_indexes[5], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[3], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[4], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0954::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 015: ElevLoPart5
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[5], 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(6), Path_indexes[25], 4352, 2, 3);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_095F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 060: ElevHiUpPart2
    if (1) {
      aMiscShakeArea(data->me_handle, 30.000000f, 300.000000f);
      aSetObjectTimer(Object_handles[58], 3.000000f, -1);
      aPortalRenderSet(1, 0, Room_indexes[7], 1);
      aPortalRenderSet(1, 0, Room_indexes[6], 1);
      aRoomChangeFog(Room_indexes[7], 0.200000f, 1.000000f, 1.000000f, 80.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[2], 0.200000f, 1.000000f, 1.000000f, 160.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[7], 0.200000f, 1.000000f, 1.000000f, 80.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0960::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 061: ElevHiUpPart3
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[2], 1);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(7), Path_indexes[27], 131328, -1, 3);
      aMiscShakeArea(data->me_handle, 50.000000f, 300.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 1.000000f, 0.000000f, 40.000000f);
      aRoomSetWind(Room_indexes[2], 0.000000f, 1.000000f, 0.000000f, 20.000000f);
      aSetObjectTimer(Object_handles[59], 10.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0961::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 062: ElevHiUpPart4
    if (1) {
      aTurnOnSpew(Object_handles[59], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[60], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aMiscShakeArea(data->me_handle, 30.000000f, 300.000000f);
      aSetObjectTimer(Object_handles[60], 3.000000f, -1);
      aPortalRenderSet(1, 1, Room_indexes[2], 1);
      aPortalRenderSet(1, 0, Room_indexes[2], 1);
      aRoomSetWind(Room_indexes[7], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[2], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomChangeFog(Room_indexes[7], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[2], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[6], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0962::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 063: ElevHiUpPart5
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[7], 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(7), Path_indexes[28], 4352, 4, 3);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0869::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 067: ElevDroids Make AnotherTower
    if (1) {
      aSetObjectTimer(Object_handles[61], 40.000000f, -1);
      aMatcenSetState(1, Matcen_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0963::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 101: ElevHiDnPart2
    if (1) {
      aMiscShakeArea(data->me_handle, 30.000000f, 300.000000f);
      aSetObjectTimer(Object_handles[63], 3.000000f, -1);
      aPortalRenderSet(1, 0, Room_indexes[9], 1);
      aPortalRenderSet(1, 0, Room_indexes[8], 1);
      aRoomChangeFog(Room_indexes[8], 0.200000f, 1.000000f, 1.000000f, 80.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[1], 0.200000f, 1.000000f, 1.000000f, 160.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[9], 0.200000f, 1.000000f, 1.000000f, 80.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0964::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 102: ElevHiDnPart3
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[1], 1);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(9), Path_indexes[31], 131328, -1, 3);
      aMiscShakeArea(data->me_handle, 50.000000f, 300.000000f);
      aRoomSetWind(Room_indexes[9], 0.000000f, -1.000000f, 0.000000f, 10.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, -1.000000f, 0.000000f, 40.000000f);
      aRoomSetWind(Room_indexes[1], 0.000000f, -1.000000f, 0.000000f, 20.000000f);
      aSetObjectTimer(Object_handles[64], 10.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0965::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 103: ElevHiDnPart4
    if (1) {
      aTurnOnSpew(Object_handles[64], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[65], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 8.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aMiscShakeArea(data->me_handle, 30.000000f, 300.000000f);
      aSetObjectTimer(Object_handles[65], 3.000000f, -1);
      aPortalRenderSet(1, 1, Room_indexes[1], 1);
      aPortalRenderSet(1, 0, Room_indexes[1], 1);
      aRoomSetWind(Room_indexes[9], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[1], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, 1.000000f, 0.000000f, 0.000000f);
      aRoomChangeFog(Room_indexes[9], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[1], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);
      aRoomChangeFog(Room_indexes[8], 0.200000f, 1.000000f, 1.000000f, 2000.000000f, 3.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0966::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 104: ElevHiDnPart5
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[9], 1);
      aAIGoalFollowPathSimple(qObjSavedHandle(9), Path_indexes[25], 4352, 2, 3);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0995::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 031: FIRE!
    if (((ScriptActionCtr_027 > 0) == true) && ((ScriptActionCtr_026 > 0) == true) &&
        ((ScriptActionCtr_025 > 0) == true) && ((ScriptActionCtr_023 > 0) == true)) {
      aGoalCompleted(Goal_indexes[1], 1);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[3]);
      aAIGoalFollowPathSimple(Object_handles[66], Path_indexes[32], 4352, 11, 3);
      aAIGoalFollowPathSimple(Object_handles[67], Path_indexes[32], 4352, 12, 3);
      aObjSetMovementType(data->me_handle, 1);
      aObjSetLightingDist(Object_handles[68], 120.000000f);
      aRoomSetFog(Room_indexes[10], 0.500000f, 0.200000f, 0.100000f, 1100.000000f);
      aRoomFogSetState(1, Room_indexes[10]);
      aRoomChangeFog(Room_indexes[10], 0.500000f, 0.200000f, 0.100000f, 300.000000f, 20.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0994::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 030: Napalm Box Fire 2B
    if (1) {
      aSetObjectOnFire(data->me_handle, 99999.000000f, 0.000000f);
      aTurnOnSpew(Object_handles[73], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  8.000000f, 45.000000f, 0, 7);
      aTurnOnSpew(Object_handles[73], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, -1.000000f,
                  15.000000f, 15.000000f, 0, 11);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0993::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 029: Napalm Box Fire 2A
    if (1) {
      aSetObjectOnFire(data->me_handle, 99999.000000f, 0.000000f);
      aTurnOnSpew(Object_handles[74], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  8.000000f, 45.000000f, 0, 6);
      aTurnOnSpew(Object_handles[74], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, -1.000000f,
                  15.000000f, 15.000000f, 0, 10);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0992::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 028: Napalm Box Fire 1B
    if (1) {
      aSetObjectOnFire(data->me_handle, 99999.000000f, 0.000000f);
      aTurnOnSpew(Object_handles[75], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  8.000000f, 45.000000f, 0, 5);
      aTurnOnSpew(Object_handles[75], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, -1.000000f,
                  15.000000f, 15.000000f, 0, 9);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1191::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 024: Napalm Box Fire 1A
    if (1) {
      aSetObjectOnFire(data->me_handle, 99999.000000f, 0.000000f);
      aTurnOnSpew(Object_handles[76], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f,
                  8.000000f, 45.000000f, 0, 4);
      aTurnOnSpew(Object_handles[76], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, -1.000000f,
                  15.000000f, 15.000000f, 0, 8);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 027: Napalm Destroyed 2B
    if (1) {
      aSetObjectTimer(Object_handles[68], 0.000000f, -1);
      aSetObjectTimer(Object_handles[69], 5.000000f, -1);
      aTurnOnSpew(Object_handles[73], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 6.000000f, 5.000000f,
                  25.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_103C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 026: Napalm Destroyed 2A
    if (1) {
      aSetObjectTimer(Object_handles[68], 0.000000f, -1);
      aSetObjectTimer(Object_handles[70], 5.000000f, -1);
      aTurnOnSpew(Object_handles[74], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 6.000000f, 5.000000f,
                  25.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_103E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 025: Napalm Destroyed 1B
    if (1) {
      aSetObjectTimer(Object_handles[68], 0.000000f, -1);
      aSetObjectTimer(Object_handles[71], 5.000000f, -1);
      aTurnOnSpew(Object_handles[75], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 6.000000f, 5.000000f,
                  25.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0841::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 023: Napalm Destroyed 1A
    if (1) {
      aSetObjectTimer(Object_handles[68], 0.000000f, -1);
      aSetObjectTimer(Object_handles[72], 5.000000f, -1);
      aTurnOnSpew(Object_handles[76], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 6.000000f, 5.000000f,
                  25.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 112: FireOut!
    if (1) {
      aSoundStopObj(Object_handles[68]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[4]);
      aRoomChangeFog(Room_indexes[10], 0.300000f, 0.300000f, 0.300000f, 300.000000f, 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0997::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 109: DroidsFoughtFireGoHome 2
    if ((ScriptActionCtr_109 < 1) && (1)) {
      aSetObjectTimer(Object_handles[81], 3.000000f, -1);
      aTurnOnSpew(Object_handles[85], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 25.000000f, 1, -1);
      aTurnOnSpew(Object_handles[86], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 25.000000f, 1, -1);
      aTurnOffSpew(10);
      aTurnOffSpew(11);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[35], 4352, 18, 3);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 107: DroidsAtFireRoom 2
    if ((ScriptActionCtr_107 < 1) && (event_data->goal_uid == 12)) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[33], 4352, 15, 3);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }

    // Script 108: DroidsAtFireTurnOnGas 2
    if ((ScriptActionCtr_108 < 1) && (event_data->goal_uid == 15)) {
      aObjDelete(Object_handles[70]);
      aObjDelete(Object_handles[69]);
      aTurnOffSpew(6);
      aTurnOffSpew(7);
      aTurnOnSpew(Object_handles[82], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, -1.000000f, 6.000000f,
                  30.000000f, 1, -1);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      aSoundPlayObject(Sound_indexes[1], Object_handles[83], 1.000000f);
      aObjPlayAnim(Object_handles[83], 0, 1, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }

    // Script 111: DroidsGotHome2
    if ((ScriptActionCtr_111 < 1) && (event_data->goal_uid == 18)) {
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0996::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 035: DroidsFoughtFireGoHome 1
    if ((ScriptActionCtr_035 < 1) && (1)) {
      aSetObjectTimer(Object_handles[81], 3.000000f, -1);
      aTurnOnSpew(Object_handles[87], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 25.000000f, 1, -1);
      aTurnOnSpew(Object_handles[88], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  4.000000f, 25.000000f, 1, -1);
      aTurnOffSpew(9);
      aTurnOffSpew(8);
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[35], 4352, 17, 3);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 033: DroidsAtFireRoom 1
    if ((ScriptActionCtr_033 < 1) && (event_data->goal_uid == 11)) {
      aAIGoalFollowPathSimple(data->me_handle, Path_indexes[34], 4352, 14, 3);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 034: DroidsAtFireTurnOnGas 1
    if ((ScriptActionCtr_034 < 1) && (event_data->goal_uid == 14)) {
      aObjDelete(Object_handles[72]);
      aObjDelete(Object_handles[71]);
      aTurnOffSpew(4);
      aTurnOffSpew(5);
      aTurnOnSpew(Object_handles[81], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, -1.000000f, 6.000000f,
                  30.000000f, 1, -1);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      aSoundPlayObject(Sound_indexes[1], Object_handles[84], 1.000000f);
      aObjPlayAnim(Object_handles[84], 0, 1, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 110: DroidsGotHome
    if ((ScriptActionCtr_110 < 1) && (event_data->goal_uid == 17)) {
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0805::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: FireDoor2
    if (1) {
      if (((event_data->it_handle == Object_handles[66]) || (event_data->it_handle == Object_handles[67])) &&
          ((ScriptActionCtr_031 > 0) == true)) {
        aGoalCompleted(Goal_indexes[2], 1);
        aDoorSetPos(data->me_handle, 1.000000f);
      } else {
        aShowHUDMessageObj(Message_strings[5], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0804::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: FireDoor
    if (1) {
      if (((event_data->it_handle == Object_handles[66]) || (event_data->it_handle == Object_handles[67])) &&
          ((ScriptActionCtr_031 > 0) == true)) {
        aDoorSetPos(data->me_handle, 1.000000f);
      } else {
        aShowHUDMessageObj(Message_strings[5], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0998::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 118: Turret Power-X4
    if (1) {
      aObjSaveHandle(Object_handles[98], 8);
      aObjSpark(qObjSavedHandle(8), 10.000000f, 10.000000f);
      aAISetFOV(qObjSavedHandle(8), 360.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }

    // Script 117: Turret Power-X3
    if (1) {
      aObjSaveHandle(Object_handles[99], 8);
      aObjSpark(qObjSavedHandle(8), 10.000000f, 10.000000f);
      aAISetFOV(qObjSavedHandle(8), 360.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }

    // Script 116: Turret Power-X2
    if (1) {
      aObjSaveHandle(Object_handles[100], 8);
      aObjSpark(qObjSavedHandle(8), 10.000000f, 10.000000f);
      aAISetFOV(qObjSavedHandle(8), 360.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }

    // Script 115: Turret Power-X1
    if (1) {
      aObjSaveHandle(Object_handles[101], 8);
      aObjSpark(qObjSavedHandle(8), 10.000000f, 10.000000f);
      aAISetFOV(qObjSavedHandle(8), 360.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }

    // Script 114: Turret Power-X
    if (1) {
      aObjSaveHandle(Object_handles[102], 8);
      aObjSpark(qObjSavedHandle(8), 50.000000f, 10.000000f);
      aAISetFOV(qObjSavedHandle(8), 360.000000f);
      aAISetTeam(65536, qObjSavedHandle(8));

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 131: PICKUP Bomb
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[2], 0);

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 050: USED Bomb
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[104]) <= 50.000000f) {
        if (((qObjExists(qObjSavedHandle(4)) == true) && (qUserFlag(2) == false)) || (qUserFlag(8) == true)) {
          aShowHUDMessageObj(Message_strings[7], event_data->it_handle);
          aAddObjectToInventoryNamed(Object_handles[8], event_data->it_handle, Message_strings[2], 0);
        } else {
          aGoalCompleted(Goal_indexes[3], 1);
          aMusicSetRegionAll(5);
          aObjSaveHandle(event_data->it_handle, 12);
          aObjGhostSet(0, Object_handles[104]);
          aObjSpark(Object_handles[104], 50.000000f, 3.000000f);
          aEmitSparks(70.000000f, Object_handles[104]);
          aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
          aUserFlagSet(4, 1);
        }
      } else {
        aShowHUDMessageObj(Message_strings[9], event_data->it_handle);
        aAddObjectToInventoryNamed(Object_handles[8], event_data->it_handle, Message_strings[2], 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1834::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 075: End Boss - Died
    if (1) {
      aSetLevelTimer(10.000000f, 14);
      aGoalCompleted(Goal_indexes[0], 1);
      aObjMakeInvuln(qPlayerClosest(Object_handles[105], -1), 1000);
      aMiscViewerShake(90.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 022: End Boss - Cinematic End
    if ((ScriptActionCtr_022 < 1) && (1)) {
      aShowHUDMessage(Message_strings[11]);
      aRoomFogSetState(0, Room_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1877::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 046: Suzuki Cam 3
    if ((ScriptActionCtr_046 < 1) && (1)) {
      aObjPlayAnim(Object_handles[116], 0, 54, 6.000000f, 0);
      aCinematicSimple(Path_indexes[42], Message_strings[1], Object_handles[119], 5.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1078::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 049: Suzuki Cam 2
    if ((ScriptActionCtr_049 < 1) && (1)) {
      aStoreObjectInPositionClipboard(Object_handles[120]);
      aMoveObjectToPositionClipboard(qObjSavedHandle(11));
      aAIGoalFollowPathSimple(qObjSavedHandle(11), Path_indexes[43], 4352, -1, 3);
      aCinematicSimple(Path_indexes[44], Message_strings[1], Object_handles[118], 7.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1070::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 048: Suzuki Cam 4
    if ((ScriptActionCtr_048 < 1) && (1)) {
      aObjGhostSet(0, Object_handles[108]);
      aObjDelete(Object_handles[107]);
      aRoomSetFog(Room_indexes[12], 0.600000f, 0.200000f, 0.100000f, 2000.000000f);
      aStoreObjectInPositionClipboard(Object_handles[121]);
      aMoveObjectToPositionClipboard(qObjSavedHandle(11));
      aAIGoalFollowPathSimple(qObjSavedHandle(11), Path_indexes[45], 4352, -1, 3);
      aSetObjectTimer(Object_handles[108], 2.500000f, -1);
      aSetObjectTimer(Object_handles[110], 4.000000f, -1);
      aSetObjectTimer(Object_handles[112], 5.500000f, -1);
      aSetObjectTimer(Object_handles[114], 7.000000f, -1);
      aSetObjectTimer(Object_handles[122], 8.500000f, -1);
      aObjPlayAnim(Object_handles[116], 54, 55, 1.000000f, 0);
      aCinematicSimple(Path_indexes[46], Message_strings[1], Object_handles[123], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2075::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 077: Suzuki Cam 4 Part0
    if (1) {
      aEmitSparks(50.000000f, data->me_handle);
      aEmitSparks(50.000000f, Object_handles[122]);
      aRoomChangeFog(Room_indexes[12], 0.600000f, 0.200000f, 0.100000f, 500.000000f, 7.500000f);
      aLightningCreate(Object_handles[122], Object_handles[108], 10.000000f, 3.000000f, 1, Texture_indexes[2],
                       0.400000f, 3, 50, 255, 255, 0);
      aObjSpark(Object_handles[114], 30.000000f, 10.000000f);
      aObjSpark(Object_handles[112], 30.000000f, 10.000000f);
      aObjSpark(Object_handles[110], 30.000000f, 10.000000f);
      aObjSpark(Object_handles[122], 30.000000f, 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2076::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 057: Suzuki Cam 4 Part4
    if (1) {
      aTurnOnSpew(Object_handles[124], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  20.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[125], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  20.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[126], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  20.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[127], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  20.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[128], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 10.000000f,
                  20.000000f, 25.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2863::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 056: Suzuki Cam 4 Part3
    if (1) {
      aObjKill(data->me_handle, 1, 2, 2293876, 1.900000f, 1.900000f);
      aObjSetLightingDist(Object_handles[115], 80.000000f);
      aObjSetLightingColor(Object_handles[115], 1.000000f, 0.500000f, 0.250000f);
      aTurnOnSpew(Object_handles[128], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  10.000000f, 80.000000f, 0, -1);
      aTurnOnSpew(Object_handles[124], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 2.000000f,
                  12.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[127], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 2.000000f,
                  12.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[129], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 10.000000f,
                  20.000000f, 25.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_207A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 055: Suzuki Cam 4 Part2
    if (1) {
      aObjKill(data->me_handle, 1, 2, 2293876, 1.900000f, 1.900000f);
      aObjSetLightingDist(Object_handles[113], 80.000000f);
      aObjSetLightingColor(Object_handles[113], 1.000000f, 0.500000f, 0.250000f);
      aTurnOnSpew(Object_handles[130], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.130000f, 10.000000f,
                  20.000000f, 25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[129], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  10.000000f, 80.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_206D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 054: Suzuki Cam 4 Part1
    if (1) {
      aObjSetLightingDist(Object_handles[111], 80.000000f);
      aObjSetLightingColor(Object_handles[111], 1.000000f, 0.500000f, 0.250000f);
      aObjKill(data->me_handle, 1, 2, 2293876, 1.900000f, 1.900000f);
      aTurnOnSpew(Object_handles[130], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f,
                  10.000000f, 80.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1079::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 047: Suzuki Cam 5
    if ((ScriptActionCtr_047 < 1) && (1)) {
      aSetObjectTimer(Object_handles[131], 2.500000f, -1);
      aSetObjectTimer(Object_handles[132], 1.500000f, -1);
      aSetObjectTimer(Object_handles[133], 0.000000f, -1);
      aSetObjectTimer(Object_handles[134], 3.500000f, -1);
      aRoomChangeFog(Room_indexes[12], 0.800000f, 0.400000f, 0.100000f, 60.000000f, 5.000000f);
      aObjGhostSet(0, Object_handles[109]);
      aObjSetLightingDist(Object_handles[109], 200.000000f);
      aObjSetLightingColor(Object_handles[109], 1.000000f, 0.500000f, 0.250000f);
      aObjPlayAnim(Object_handles[116], 55, 74, 3.500000f, 0);
      aCinematicSimple(Path_indexes[47], Message_strings[1], Object_handles[135], 5.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 076: Suzuki Cam 5 Part4
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 5.000000f, 8.000000f,
                  60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 071: Suzuki Cam 5 Part3
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 5.000000f, 10.000000f,
                  90.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 070: Suzuki Cam 5 Part2
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 5.000000f, 30.000000f,
                  100.000000f, 0, -1);
      aTurnOnSpew(Object_handles[136], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.130000f, 5.000000f,
                  50.000000f, 120.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09BC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 069: Suzuki Cam 5 Part1
    if (1) {
      aObjSetMovementType(Object_handles[116], 1);
      aObjKill(Object_handles[116], 1, 2, 2294000, 1.000000f, 1.000000f);
      aObjSetVelocity(Object_handles[116], 0.700000f, 0.000000f, 0.700000f, 40.000000f);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.100000f, 5.000000f, 8.000000f,
                  100.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 5.000000f, 12.000000f,
                  60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1071::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 051: Suzuki Cam 6
    if ((ScriptActionCtr_051 < 1) && (1)) {
      aMiscViewerShake(100.000000f);
      aTurnOnSpew(Object_handles[137], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, 4.000000f,
                  30.000000f, 100.000000f, 0, -1);
      aTurnOnSpew(Object_handles[137], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, 4.000000f,
                  15.000000f, 160.000000f, 0, -1);
      aSetObjectTimer(Object_handles[138], 1.500000f, -1);
      aSetObjectTimer(Object_handles[139], 3.000000f, -1);
      aSetObjectTimer(Object_handles[140], 6.500000f, -1);
      aSetObjectTimer(Object_handles[141], 4.000000f, -1);
      aSetObjectTimer(Object_handles[142], 4.500000f, -1);
      aSetObjectTimer(Object_handles[143], 5.500000f, -1);
      aSetObjectTimer(Object_handles[144], 6.000000f, -1);
      aSetObjectTimer(Object_handles[145], 7.000000f, -1);
      aSetObjectTimer(Object_handles[146], 7.500000f, -1);
      aRoomSetWind(Room_indexes[13], 1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[14], 1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetWind(Room_indexes[15], 1.000000f, 0.000000f, 0.000000f, 20.000000f);
      aRoomSetFog(Room_indexes[15], 0.600000f, 0.200000f, 0.100000f, 2000.000000f);
      aRoomSetFog(Room_indexes[14], 0.600000f, 0.200000f, 0.100000f, 2000.000000f);
      aRoomChangeFog(Room_indexes[14], 0.800000f, 0.400000f, 0.100000f, 150.000000f, 9.000000f);
      aRoomChangeFog(Room_indexes[15], 0.800000f, 0.400000f, 0.100000f, 150.000000f, 9.000000f);
      aObjDelete(Object_handles[109]);
      aCinematicSimple(Path_indexes[48], Message_strings[1], Object_handles[147], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09CA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 086: Suzuki Cam 6 Part10
    if (1) {
      aTurnOnSpew(Object_handles[148], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 5.000000f,
                  40.000000f, 180.000000f, 0, -1);
      aTurnOnSpew(Object_handles[140], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.140000f, 5.000000f,
                  60.000000f, 150.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.090000f, 3.000000f, 18.000000f,
                  300.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.160000f, 5.000000f, 30.000000f,
                  160.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 085: Suzuki Cam 6 Part9
    if (1) {
      aTurnOnSpew(Object_handles[149], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, 5.000000f,
                  60.000000f, 150.000000f, 0, -1);
      aTurnOnSpew(Object_handles[150], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, 5.000000f,
                  60.000000f, 150.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.160000f, 5.000000f, 30.000000f,
                  160.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.090000f, 3.000000f, 18.000000f,
                  300.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 084: Suzuki Cam 6 Part8
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.090000f, 3.000000f, 18.000000f,
                  300.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.160000f, 6.000000f, 30.000000f,
                  160.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 083: Suzuki Cam 6 Part7
    if (1) {
      aTurnOnSpew(Object_handles[139], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.140000f, 4.000000f,
                  60.000000f, 150.000000f, 0, -1);
      aTurnOnSpew(Object_handles[149], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, 3.000000f,
                  40.000000f, 120.000000f, 0, -1);
      aTurnOnSpew(Object_handles[150], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, 3.000000f,
                  40.000000f, 120.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.090000f, 3.000000f, 18.000000f,
                  300.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.160000f, 6.000000f, 30.000000f,
                  160.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 082: Suzuki Cam 6 Part6
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.090000f, 3.000000f, 18.000000f,
                  300.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.160000f, 6.000000f, 30.000000f,
                  160.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 081: Suzuki Cam 6 Part5
    if (1) {
      if ((qObjExists(qObjSavedHandle(4)) == true) && (1)) {
        aObjDestroy(qObjSavedHandle(4));
      }
      aTurnOnSpew(Object_handles[139], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.120000f, 3.000000f,
                  30.000000f, 120.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.090000f, 3.000000f, 18.000000f,
                  300.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.160000f, 5.000000f, 30.000000f,
                  160.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 080: Suzuki Cam 6 Part3
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f, 20.000000f,
                  130.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.120000f, 3.000000f, 35.000000f,
                  80.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 079: Suzuki Cam 6 Part2
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 3.000000f, 12.000000f,
                  130.000000f, 0, -1);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.140000f, 3.000000f, 30.000000f,
                  80.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 078: Suzuki Cam 6 Part1
    if (1) {
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, 4.000000f, 25.000000f,
                  80.000000f, 0, -1);
      aTurnOnSpew(Object_handles[139], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, 4.000000f,
                  10.000000f, 120.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_286E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 073: Suzuki Post Production
    if (1) {
      aGoalCompleted(Goal_indexes[5], 1);
      aDoorLockUnlock(0, Door_handles[0]);
      aShowHUDMessage(Message_strings[13]);
      aRoomSetFog(Room_indexes[16], 0.200000f, 0.150000f, 0.100000f, 400.000000f);
      aRoomSetFog(Room_indexes[10], 0.200000f, 0.150000f, 0.100000f, 400.000000f);
      aRoomSetFog(Room_indexes[17], 0.200000f, 0.150000f, 0.100000f, 400.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: BST Patrols (Mnt)
    if ((ScriptActionCtr_001 < 1) && (1)) {
      aAIGoalFollowPathSimple(Object_handles[12], Path_indexes[7], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[13], Path_indexes[8], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[14], Path_indexes[9], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[15], Path_indexes[10], 8392961, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[16], Path_indexes[11], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[17], Path_indexes[12], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[18], Path_indexes[13], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[19], Path_indexes[14], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[20], Path_indexes[15], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[21], Path_indexes[16], 6295809, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[22], Path_indexes[17], 6295809, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 100: IG Patrols
    if ((ScriptActionCtr_100 < 1) && (1)) {
      aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[18], 4198400, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[24], Path_indexes[18], 4198400, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[18], 4198400, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[26], Path_indexes[19], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[27], Path_indexes[19], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[28], Path_indexes[19], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[29], Path_indexes[19], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[30], Path_indexes[20], 4198400, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[31], Path_indexes[20], 4198400, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: ElevDroids PlayerIsHere
    if ((ScriptActionCtr_005 < 1) && (1)) {
      aSetObjectTimer(Object_handles[52], 40.000000f, 0);
      aMatcenSetState(1, Matcen_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: ElevDroids PlayerInTower
    if ((ScriptActionCtr_064 < 1) && (1)) {
      aObjDelete(qObjSavedHandle(6));
      aObjDelete(qObjSavedHandle(10));
      aCancelTimer(0);
      aSetObjectTimer(Object_handles[61], 40.000000f, -1);
      aMatcenSetState(1, Matcen_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 072: End Boss - Start Cinematic
    if ((ScriptActionCtr_072 < 1) && (4 == qObjType(event_data->it_handle))) {
      aGoalEnableDisable(1, Goal_indexes[0]);
      aCancelTimer(0);
      aRoomChangeFog(Room_indexes[0], 0.000000f, 0.000000f, 0.000000f, 800.000000f, 9.000000f);
      aCinematicSimple(Path_indexes[40], Message_strings[10], Object_handles[105], 8.000000f, 1);
      aDoorSetPos(Door_handles[0], 0.000000f);
      aDoorLockUnlock(1, Door_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Destroy Bots2
    if ((ScriptActionCtr_047 > 0) == true) {
      aObjKill(qGetAtachedChild(event_data->it_handle, 0), 1, 1, 2293872, 1.000000f, 1.400000f);
      aObjKill(event_data->it_handle, 1, 1, 2293872, 1.400000f, 1.800000f);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Destroy Bots1
    if ((ScriptActionCtr_047 > 0) == true) {
      aObjKill(event_data->it_handle, 1, 1, 2302192, 0.000000f, 0.100000f);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 130: MusicBoss
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 129: MusicTower2
    if ((ScriptActionCtr_050 > 0) == false) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 128: MusicTower1
    if ((ScriptActionCtr_050 > 0) == false) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 127: MusicMid4
    if ((ScriptActionCtr_050 > 0) == false) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 126: MusicMid3
    if ((ScriptActionCtr_050 > 0) == false) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 125: MusicMid2
    if ((ScriptActionCtr_050 > 0) == false) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 124: MusicMid1
    if ((ScriptActionCtr_050 > 0) == false) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 123: MusicMaint2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 122: MusicMaint1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 121: MusicSewer1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
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
NEXT_ID		132

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:FireRoomCounter
1:CurFireRoomNapalm
2:LifterMaxSpeed
3:BombDropRadius
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:TopLevelTriggered
1:FireRoomTriggered
2:BomberHasSomething
3:BomberHasRealBomb
4:BombDroppedOntoMatcen
5:PackageMatcened
6:BombIsPlanted
7:SpecialDelivery
8:BombMatActive
9:TopAmbientLifterMatcened
11:PlayerEscapedBomb
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:HalonSpewer1
1:HalonSpewer2
2:HalonSpewer3
3:HalonSpewer4
4:FireSpewer1A
5:FireSpewer1B
6:FireSpewer2A
7:FireSpewer2B
8:BigFire1A
9:BigFire1B
10:BigFire2A
11:BigFire2B
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:LowDroids
1:Music
2:LifterFiremenTimer
3:FireroomTimer
4:FiremanHalon1
5:FiremanHalon2
6:FiremanHalon3
7:DroidManagerUpdate
8:BombMatcenInit
9:BomberPickupDelay
10:SuzukiCinematicTimer
11:BomberMakeTimer
12:BombDetonationTimer
13:Droid Central
14:EndLevelTimer
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:Fireman1
1:Fireman2
2:Fireman3
3:Bomber
4:Package
5:Bomb
6:LoDroid
7:HiUpDroid
8:CurrentTurret
9:HiDnDroid
10:PreLoDroid
11:RealBomber
12:GuyWhoDroppedBomb
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:DroidPreLo
1:DroidInLo
2:DroidPreUp
3:DroidInUp
4:DroidExitUp
5:DroidPreDn
6:DroidInDn
7:DroidBorn
8:DroidDie
11:Fireman1
12:Fireman2
14:Fireman1AtFire
15:Fireman2AtFire
17:Fireman1AtDoor
18:Fireman2AtDoor
20:PackagePickedup
21:BomberAtPickup
22:BomberFinishedRun
23:BomberFinishedRealRun
24:SuzukiPreForceField
25:SuzukiPostForceField
26:SuzukiBombPlanted
27:AtBombDropoff
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
BossDoor
DroidDoor2
$$DOOR_LIST_END

$$OBJECT_LIST_START
ParkSpew1
ParkSpew2
ParkSpew3
ParkSpew4
TargetIntro2
TargetIntro1
IntroSpew1
IntroSpew2
TheBomb
BST-1
BST-2
BST-3
BST-C6
BST-C5
BST-C4
BST-C3
BST-C2
BST-C1
BST-A-A
BST-A-B
BST-A-C
BST-B-A
BST-B-B
IG3C
IG3B
IG3A
IG2D
IG2C
IG2B
IG2A
IG1B
IG1A
TPower10
TGun10
TPower9
TGun9
TPower8
TGun8
TPower7
TGun7
TPower6
TGun6
TPower5
TGun5
TPower4
TGun4
TPower3
TGun3
TPower2
TGun2
TPower1
TGun1
MntLifterMatcenA
LoEnter1
LoEnter2
LoExit1
LoExit2
HiUpEntry1
HiUpEntry2
HiUpExit1
HiUpExit2
TopLifterMatcen
HiDnEntry1
HiDnEntry2
HiDnExit1
HiDnExit2
FireMan1
FireMan2
FireLight
BoxFire2B
BoxFire2A
BoxFire1B
BoxFire1A
NFire2B
NFire2A
NFire1B
NFire1A
Napalm2B
Napalm2A
Napalm1B
Napalm1A
FireSpew1
FireSpew2
FireHandle2
FireHandle1
HalonSpewer1
HalonSpewer-2
HalonSpewer3
HalonSpewer4
DroidDoor2
DroidFireDoor1
MGuard6
MGuard5
MGuard-4
MGuard-3
MGuard-2
MGuard-1
TPowerX
TGunX4
TGunX3
TGunX2
TGunX1
TGunX
EBarPlace
DaBomb
EndBoss
Julian
ShowBomb
PBomb
RedFlashBar
PNode3
PBar3
PNode2
PBar2
PNode1
PBar1
Suzuki
SZTarget1
SZTarget3
SZTarget2
SZSpot1
SZSpot2
PNode4
SZTarget4
PX1
PX2
PX3
PX4
PExplode1
PExplode2
PExplode3
SZ5Fire4
SZ5Fire3
SZ5Fire2
SZ5Fire1
SZTarget5
SZ5Fire2A
SZF1
SZF2
SZF3
SZF4
SZF5
SZF6
SZF7
SZF8
SZF9
SZF10
SZTarget6
SZF15
SZF13
SZF14
Start End Boss Cin
$$OBJECT_LIST_END

$$ROOM_LIST_START
BossRoom
HiDnShaft
HiUpShaft
LoShaft
LoEntrance
LoExit
HiUpEntrance
HiUpExit
HiDnEntrance
HiDnExit
FireRoom
PreBoss
SuzukiOffice
DroidExplode1
DroidExplosion
DroidCommand
ElevatorRoom
PreFireRoom
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EnterMaintenence
MntLifterInit
StartUpperLifters
BossRoomEntrance
RoboDestroy
DestroyMe
MusicBoss
MusicSuzuki2
MusicSuzuki1
MusicMid4
MusicMid3
MusicMid2
MusicMid1
MusicMaint2
MusicMaint1
MusicSewer1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSirenIntense
AmbSwitch31
$$SOUND_LIST_END

$$TEXTURE_LIST_START
MeshGlass1
FunkyEffectGreen
FunkyEffect3
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam-2
IntroCam-1
IntroCam-Ship
IntroPlayerPath
BST-1
BST-2
BST-3
BST-C6
BST-C5
BST-C4
BST-C3
BST-C2
BST-C1
BST-A-1
BST-A-2
BST-A-3
BST-B-1
BST-B-2
IG-3
IG-2
IG-1
LoLeft1
LoRight1
LoEntry
LoExit
HiUp1
HiUpEntry
HiUpExit
HiRight1
HiLeft1
DnEntry
DnExit
FirePathIn
Fire2
Fire1
FirePathOut
Guards
BombPickup2
BombPickup1
BombTake
BossCam
SZCam1
SZCam2
BombDelivery
SZCam3
BombAfterDevlier
SZCam4
SuzukiFinalPath
SZCam6
DBorn1
DBorn2
DBorn3
DBorn4
DDie1
DDie2
DDie3
DDie4
$$PATH_LIST_END

$$MATCEN_LIST_START
MntMatcenA
MntMatcenB
TopLifterMatcen
BombMatcen
BomberMatcen-2
BomberMatcen-1
DCMatcen-1
DCMatcen-2
DCMatcen-3
DCMatcen-4
$$MATCEN_LIST_END

$$GOAL_LIST_START
Destroy the PTMC Assault Bot
Create a Disturbance to Summon Droids
Wait for Droids to Open Central Command
Place Bomb on Delivery Pad
Get a Safe Distance from Bomb
Assasinate President Suzuki of PTMC
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:74:IntroCam-1
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:4:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:IntroCam-2
        $$CHILD_BLOCK_START
        01:1:4
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:1:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:5:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:IntroCam-3
        $$CHILD_BLOCK_START
        01:1:5
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:2:-1:TotallyNotUsedTarget
                        10:16:3:PlayerPath
                        10:6:8.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:INIT GlassWindows
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
                        10:2:0:Room
                        10:4:15:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:14:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:13:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:12:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:11:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:10:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:9:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:8:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:7:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:6:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:5:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:4:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:3:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:2:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:1:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:0:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:INIT Variables/Flags
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:0:LevelGoal
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
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
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:8:BombInventory:ItemName
                        10:5:0:Spewable
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:BST Patrols (Sewer)
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:16:4:Path
                        10:15:10490113:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:16:5:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:16:6:Path
                        10:15:10490113:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:BST Patrols (Mnt)
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:16:7:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:16:8:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:16:9:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:16:10:Path
                        10:15:8392961:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:16:11:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:16:12:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:16:13:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:16:14:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:16:15:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:16:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:16:17:Path
                        10:15:6295809:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:IG Patrols
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:18:Path
                        10:15:4198400:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:16:18:Path
                        10:15:4198400:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:16:18:Path
                        10:15:4198400:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:16:19:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:16:19:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:16:19:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:16:19:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:16:20:Path
                        10:15:4198400:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:16:20:Path
                        10:15:4198400:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:Turret Power-10
        $$CHILD_BLOCK_START
        01:1:32
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:Turret Power-9
        $$CHILD_BLOCK_START
        01:1:34
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:Turret Power-8
        $$CHILD_BLOCK_START
        01:1:36
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Turret Power-7
        $$CHILD_BLOCK_START
        01:1:38
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:Turret Power-6
        $$CHILD_BLOCK_START
        01:1:40
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Turret Power-5
        $$CHILD_BLOCK_START
        01:1:42
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Turret Power-4
        $$CHILD_BLOCK_START
        01:1:44
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Turret Power-3
        $$CHILD_BLOCK_START
        01:1:46
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Turret Power-2
        $$CHILD_BLOCK_START
        01:1:48
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Turret Power-1
        $$CHILD_BLOCK_START
        01:1:50
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:INIT ElevDroids
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
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
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
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
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:ElevDroids MakeNew
        $$CHILD_BLOCK_START
        01:1:52
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.500000:Probability
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
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:6:40.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:ElevDroids PlayerIsHere
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:6:40.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:ElevDroids Created Left
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
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:10:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:1:-1:Matcen
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:3:GoalPriority
                        10:6:5.000000:distance
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:21:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:ElevDroids Created Right
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
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:10:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:1:-1:Matcen
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:3:GoalPriority
                        10:6:5.000000:distance
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:22:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:ElevDroids Reached OutsideLo
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:ElevDroids Reached InsideHiDn
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
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:9:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:ElevDroids Reached InsideHiUp
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:7:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:ElevDroids Reached InsideLo
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
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:6:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:ElevLoPart2
        $$CHILD_BLOCK_START
        01:1:53
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
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
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:80.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:160.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:80.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:ElevLoPart3
        $$CHILD_BLOCK_START
        01:1:54
        02:9
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:6:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:24:Path
                        10:15:131328:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:10.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:40.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:6:8.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:ElevLoPart4
        $$CHILD_BLOCK_START
        01:1:55
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
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
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:ElevLoPart5
        $$CHILD_BLOCK_START
        01:1:56
        02:9
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
                        10:2:5:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:6:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:25:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:2:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:ElevDroids Reached End Of Line
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:ElevDroids Reached OutsideHiUp
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:26:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:ElevHiUpPart2
        $$CHILD_BLOCK_START
        01:1:57
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:7:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:6:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:80.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:160.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:80.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:ElevHiUpPart3
        $$CHILD_BLOCK_START
        01:1:58
        02:9
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
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:7:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:27:Path
                        10:15:131328:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:Amount
                        10:6:300.000000:Dist
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
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:40.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:6:10.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:ElevHiUpPart4
        $$CHILD_BLOCK_START
        01:1:59
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
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
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:ElevHiUpPart5
        $$CHILD_BLOCK_START
        01:1:60
        02:9
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
                        10:2:7:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:7:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:28:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:4:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:ElevDroids Make AnotherTower
        $$CHILD_BLOCK_START
        01:1:61
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:6:40.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:ElevDroids PlayerInTower
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:6:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:10:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:6:40.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:ElevDroids Created Tower
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:1:-1:Matcen
                        $$CHILD_BLOCK_END
                08:aAIGoalSetCircleDistance
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:3:GoalPriority
                        10:6:5.000000:distance
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:29:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:5:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:ElevDroids Reached OutsideHiDn
        $$CHILD_BLOCK_START
        01:2:0
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:30:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:6:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:ElevHiDnPart2
        $$CHILD_BLOCK_START
        01:1:62
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
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
                        10:4:0:PortalNum
                        10:2:8:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:80.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:160.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:80.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:ElevHiDnPart3
        $$CHILD_BLOCK_START
        01:1:63
        02:9
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
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:9:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:31:Path
                        10:15:131328:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:10.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:40.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:6:10.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:ElevHiDnPart4
        $$CHILD_BLOCK_START
        01:1:64
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:30.000000:Amount
                        10:6:300.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.200000:Red
                        10:6:1.000000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:ElevHiDnPart5
        $$CHILD_BLOCK_START
        01:1:65
        02:9
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:9:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:25:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:2:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:INIT Fire
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
                        10:1:0:66:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:1.000000:Red
                        10:6:0.250000:Green
                        10:6:0.000000:Blue
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:4:99999:Time
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
                        10:10:0:1:Ghost/Unghost
                        10:1:0:71:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:72:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:FIRE!
        $$CHILD_BLOCK_START
        01:1:68
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:27:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:26:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:25:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:23:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:FiremenSummoning:Message
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:16:32:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:11:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:16:32:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:12:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:120.000000:Distance
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.500000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:1100.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:10:Room
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.500000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:300.000000:Depth
                        10:6:20.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Napalm Box Fire 2B
        $$CHILD_BLOCK_START
        01:1:69
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        10:6:0.000000:Damage
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:11:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Napalm Box Fire 2A
        $$CHILD_BLOCK_START
        01:1:70
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        10:6:0.000000:Damage
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Napalm Box Fire 1B
        $$CHILD_BLOCK_START
        01:1:71
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        10:6:0.000000:Damage
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Napalm Box Fire 1A
        $$CHILD_BLOCK_START
        01:1:72
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:99999.000000:Seconds
                        10:6:0.000000:Damage
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Napalm Destroyed 2B
        $$CHILD_BLOCK_START
        01:1:77
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Napalm Destroyed 2A
        $$CHILD_BLOCK_START
        01:1:78
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Napalm Destroyed 1B
        $$CHILD_BLOCK_START
        01:1:79
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Napalm Destroyed 1A
        $$CHILD_BLOCK_START
        01:1:80
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:FireOut!
        $$CHILD_BLOCK_START
        01:1:81
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:FiremenDone:Message
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.300000:Red
                        10:6:0.300000:Green
                        10:6:0.300000:Blue
                        10:6:300.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:DroidsAtFireRoom 2
        $$CHILD_BLOCK_START
        01:1:67
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:33:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:15:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:DroidsAtFireRoom 1
        $$CHILD_BLOCK_START
        01:1:66
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:34:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:14:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:DroidsAtFireTurnOnGas 2
        $$CHILD_BLOCK_START
        01:1:67
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:83:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:DroidsAtFireTurnOnGas 1
        $$CHILD_BLOCK_START
        01:1:66
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:84:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:DroidsFoughtFireGoHome 2
        $$CHILD_BLOCK_START
        01:1:67
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:86:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:10:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:11:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:35:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:18:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:DroidsFoughtFireGoHome 1
        $$CHILD_BLOCK_START
        01:1:66
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:9:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:16:35:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:17:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:DroidsGotHome2
        $$CHILD_BLOCK_START
        01:1:67
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:DroidsGotHome
        $$CHILD_BLOCK_START
        01:1:66
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:FireDoor2
        $$CHILD_BLOCK_START
        01:1:89
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
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                07:1:0
                                                10:1:0:66:Object
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                07:1:0
                                                10:1:0:67:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:31:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:2:-1:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:DroidOnlyDoor:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:FireDoor
        $$CHILD_BLOCK_START
        01:1:90
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
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                07:1:0
                                                10:1:0:66:Object
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                07:1:0
                                                10:1:0:67:Object
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:31:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:2:-1:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:DroidOnlyDoor:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:IntruderAlert!
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:18:1:-1:Level Goal
                        07:1:0
                        10:18:0:2:Level Goal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object
                        10:16:36:Path
                        10:15:4353:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:92:Object
                        10:16:36:Path
                        10:15:4353:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:93:Object
                        10:16:36:Path
                        10:15:4353:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:94:Object
                        10:16:36:Path
                        10:15:4353:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:95:Object
                        10:16:36:Path
                        10:15:4353:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:96:Object
                        10:16:36:Path
                        10:15:4353:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:Turret Power-X4
        $$CHILD_BLOCK_START
        01:1:97
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:98:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:10.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:Turret Power-X3
        $$CHILD_BLOCK_START
        01:1:97
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:99:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:10.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:Turret Power-X2
        $$CHILD_BLOCK_START
        01:1:97
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:100:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:10.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:Turret Power-X1
        $$CHILD_BLOCK_START
        01:1:97
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:101:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:10.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:Turret Power-X
        $$CHILD_BLOCK_START
        01:1:97
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:0:102:Object
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:50.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:8:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:INIT Bomb Delivery
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
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:103:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:104:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Created New Bomb
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:103:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:4:SavedObjectSlot
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.550000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:4:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:5:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:30.000000:SparkRate
                        10:6:3.000000:Time
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Bomber Created-2
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
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:1:2:Matcen
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:37:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:21:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Bomber Created-1
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
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:1:2:Matcen
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:25.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:38:Path
                        10:15:2101504:AIGoalFlags
                        10:10:0:21:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:BomberReadyToPickup
        $$CHILD_BLOCK_START
        01:2:0
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalPickUpObjectRad
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:0:PickerPoint
                                06:qObjSavedHandle:Pickee
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:RadiusRatio
                                10:10:0:3:GoalPriority
                                10:15:256:AIGoalFlags
                                10:10:0:20:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:39:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:22:GoalID
                                10:10:0:0:GoalPriority
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
                                                10:10:0:4:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:DeliveryReady:Message
                                        $$CHILD_BLOCK_END
                                08:aAIGoalPickUpObjectRad
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Picker
                                        10:4:0:PickerPoint
                                        10:1:0:104:Pickee
                                        10:9:0.600000:RadiusRatio
                                        10:10:0:3:GoalPriority
                                        10:15:256:AIGoalFlags
                                        10:10:0:20:GoalID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:39:Path
                                        10:15:4352:AIGoalFlags
                                        10:10:0:22:GoalID
                                        10:10:0:3:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:BomberPickedUp
        $$CHILD_BLOCK_START
        01:2:0
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:39:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:22:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:BomberDoneRun
        $$CHILD_BLOCK_START
        01:2:0
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:3:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:5:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
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
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qGetAtachedChild:Object
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object
                                                        10:4:0:AttachPoint
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjDelete
                                        $$CHILD_BLOCK_START
                                        06:qGetAtachedChild:Object
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                10:4:0:AttachPoint
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:131:PICKUP Bomb
        $$CHILD_BLOCK_START
        01:1:8
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
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:8:BombInventory:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:USED Bomb
        $$CHILD_BLOCK_START
        01:1:8
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
                                06:qObjGetDistance:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object1
                                        10:1:0:104:Object2
                                        $$CHILD_BLOCK_END
                                07:1:5
                                10:6:50.000000:Float
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:1
                                        $$CHILD_BLOCK_START
                                        09:0
                                                $$CHILD_BLOCK_START
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qObjExists:Bool
                                                                $$CHILD_BLOCK_START
                                                                06:qObjSavedHandle:Object
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:4:SavedObjectSlot
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
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
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:BombPadFull:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventoryNamed
                                        $$CHILD_BLOCK_START
                                        10:1:0:8:Object
                                        10:1:1:-1:PlayerObject
                                        10:8:BombInventory:ItemName
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:3:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                08:aMusicSetRegionAll
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:Region
                                        $$CHILD_BLOCK_END
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:10:0:12:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:104:Object
                                        $$CHILD_BLOCK_END
                                08:aObjSpark
                                        $$CHILD_BLOCK_START
                                        10:1:0:104:Object
                                        10:6:50.000000:SparkRate
                                        10:6:3.000000:Time
                                        $$CHILD_BLOCK_END
                                08:aEmitSparks
                                        $$CHILD_BLOCK_START
                                        10:6:70.000000:Number
                                        10:1:0:104:Object
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:BombDropSuccess:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:BombDropFail:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        08:aAddObjectToInventoryNamed
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                10:1:1:-1:PlayerObject
                                10:8:BombInventory:ItemName
                                10:5:0:Spewable
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:End Boss - Start Cinematic
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:10:0:4:ObjectType
                        07:1:0
                        06:qObjType:ObjectType
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:0:LevelGoal
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:Red
                        10:6:0.000000:Green
                        10:6:0.000000:Blue
                        10:6:800.000000:Depth
                        10:6:9.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:40:CameraPath
                        10:8:BossName:Text
                        10:1:0:105:Target
                        10:6:8.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:End Boss - Cinematic End
        $$CHILD_BLOCK_START
        01:1:105
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SafeFromBomb:Message
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:End Boss - Died
        $$CHILD_BLOCK_START
        01:1:105
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        06:qPlayerClosest:Object
                                $$CHILD_BLOCK_START
                                10:1:0:105:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:4:1000:Time
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:90.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Start Bomb Sequence
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
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:11:Room
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivateBomb:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:INIT Suzuki's Death
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
                        10:1:0:106:Object
                        10:10:0:11:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAIGoalPickUpObjectRad
                        $$CHILD_BLOCK_START
                        10:1:0:106:Picker
                        10:4:0:PickerPoint
                        10:1:0:107:Pickee
                        10:9:0.600000:RadiusRatio
                        10:10:0:3:GoalPriority
                        10:15:256:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:11:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:6:20.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:108:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:109:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Suzuki Cam 1
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
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object1
                        10:1:0:111:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:255:Green
                        10:4:150:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object1
                        10:1:0:113:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:255:Green
                        10:4:150:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object1
                        10:1:0:115:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:255:Green
                        10:4:150:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:4:0:StartFrame
                        10:4:54:EndFrame
                        10:6:6.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:41:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:117:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Suzuki Cam 3
        $$CHILD_BLOCK_START
        01:1:118
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:4:0:StartFrame
                        10:4:54:EndFrame
                        10:6:6.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:42:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:119:Target
                        10:6:5.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Suzuki Cam 2
        $$CHILD_BLOCK_START
        01:1:117
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:120:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:11:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:11:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:43:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:44:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:118:Target
                        10:6:7.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Suzuki Cam 4
        $$CHILD_BLOCK_START
        01:1:119
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:108:Object
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:107:Object
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.600000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:2000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:121:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:11:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:11:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:16:45:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:108:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        10:6:5.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object
                        10:6:7.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        10:6:8.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:4:54:StartFrame
                        10:4:55:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:46:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:123:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Suzuki Cam 4 Part0
        $$CHILD_BLOCK_START
        01:1:108
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:0:122:Object
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.600000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:500.000000:Depth
                        10:6:7.500000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object1
                        10:1:0:108:Object2
                        10:6:10.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:2:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:50:Red
                        10:4:255:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Suzuki Cam 4 Part4
        $$CHILD_BLOCK_START
        01:1:122
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:124:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:125:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:126:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:127:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:128:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Suzuki Cam 4 Part3
        $$CHILD_BLOCK_START
        01:1:114
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2293876:DeathFlags
                        10:6:1.900000:MinDelay
                        10:6:1.900000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:6:80.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:6:1.000000:Red
                        10:6:0.500000:Green
                        10:6:0.250000:Blue
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:128:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:124:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:2.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:127:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:2.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:129:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Suzuki Cam 4 Part2
        $$CHILD_BLOCK_START
        01:1:112
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2293876:DeathFlags
                        10:6:1.900000:MinDelay
                        10:6:1.900000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:113:Object
                        10:6:80.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:113:Object
                        10:6:1.000000:Red
                        10:6:0.500000:Green
                        10:6:0.250000:Blue
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:129:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Suzuki Cam 4 Part1
        $$CHILD_BLOCK_START
        01:1:110
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:6:80.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:6:1.000000:Red
                        10:6:0.500000:Green
                        10:6:0.250000:Blue
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2293876:DeathFlags
                        10:6:1.900000:MinDelay
                        10:6:1.900000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Suzuki Cam 5
        $$CHILD_BLOCK_START
        01:1:123
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:131:Object
                        10:6:2.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:132:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:133:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:134:Object
                        10:6:3.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.800000:Red
                        10:6:0.400000:Green
                        10:6:0.100000:Blue
                        10:6:60.000000:Depth
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:109:Object
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        10:6:200.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingColor
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        10:6:1.000000:Red
                        10:6:0.500000:Green
                        10:6:0.250000:Blue
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:4:55:StartFrame
                        10:4:74:EndFrame
                        10:6:3.500000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:47:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:135:Target
                        10:6:5.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Suzuki Cam 5 Part4
        $$CHILD_BLOCK_START
        01:1:131
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Suzuki Cam 5 Part3
        $$CHILD_BLOCK_START
        01:1:132
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:90.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Suzuki Cam 5 Part2
        $$CHILD_BLOCK_START
        01:1:133
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:136:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:50.000000:BlobSize
                        10:6:120.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Suzuki Cam 5 Part1
        $$CHILD_BLOCK_START
        01:1:134
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:2294000:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:6:0.700000:X
                        10:6:0.000000:Y
                        10:6:0.700000:Z
                        10:6:40.000000:Speed
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.100000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Suzuki Cam 6
        $$CHILD_BLOCK_START
        01:1:135
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:4.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:4.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:138:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:6:6.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:141:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:142:Object
                        10:6:4.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object
                        10:6:5.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:144:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:145:Object
                        10:6:7.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:146:Object
                        10:6:7.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:1.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:20.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.600000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:2000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.600000:Red
                        10:6:0.200000:Green
                        10:6:0.100000:Blue
                        10:6:2000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.800000:Red
                        10:6:0.400000:Green
                        10:6:0.100000:Blue
                        10:6:150.000000:Depth
                        10:6:9.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.800000:Red
                        10:6:0.400000:Green
                        10:6:0.100000:Blue
                        10:6:150.000000:Depth
                        10:6:9.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:109:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:48:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:147:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Suzuki Cam 6 Part10
        $$CHILD_BLOCK_START
        01:1:146
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:148:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:40.000000:BlobSize
                        10:6:180.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:18.000000:BlobSize
                        10:6:300.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Suzuki Cam 6 Part9
        $$CHILD_BLOCK_START
        01:1:145
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:18.000000:BlobSize
                        10:6:300.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Suzuki Cam 6 Part8
        $$CHILD_BLOCK_START
        01:1:144
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:18.000000:BlobSize
                        10:6:300.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Suzuki Cam 6 Part7
        $$CHILD_BLOCK_START
        01:1:143
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:4.000000:SpewLife
                        10:6:60.000000:BlobSize
                        10:6:150.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:40.000000:BlobSize
                        10:6:120.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:40.000000:BlobSize
                        10:6:120.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:18.000000:BlobSize
                        10:6:300.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Suzuki Cam 6 Part6
        $$CHILD_BLOCK_START
        01:1:142
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:18.000000:BlobSize
                        10:6:300.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:6.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Suzuki Cam 6 Part5
        $$CHILD_BLOCK_START
        01:1:141
        02:9
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
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:0
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjDestroy
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:120.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:18.000000:BlobSize
                        10:6:300.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.160000:BlobInterval
                        10:6:5.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:160.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Suzuki Cam 6 Part3
        $$CHILD_BLOCK_START
        01:1:140
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:130.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:35.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Suzuki Cam 6 Part2
        $$CHILD_BLOCK_START
        01:1:139
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:130.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:30.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Suzuki Cam 6 Part1
        $$CHILD_BLOCK_START
        01:1:138
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:4.000000:SpewLife
                        10:6:25.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:4.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:120.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Suzuki Post Production
        $$CHILD_BLOCK_START
        01:1:147
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SuzukiDead:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.200000:Red
                        10:6:0.150000:Green
                        10:6:0.100000:Blue
                        10:6:400.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.200000:Red
                        10:6:0.150000:Green
                        10:6:0.100000:Blue
                        10:6:400.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:17:Room
                        10:6:0.200000:Red
                        10:6:0.150000:Green
                        10:6:0.100000:Blue
                        10:6:400.000000:Depth
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Destroy Bots2
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:47:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2293872:DeathFlags
                        10:6:1.000000:MinDelay
                        10:6:1.400000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2293872:DeathFlags
                        10:6:1.400000:MinDelay
                        10:6:1.800000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Destroy Bots1
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:47:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:1:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:2302192:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.100000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:INIT Droid Central
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
                        10:6:2.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Create A New Droid
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:2.000000:LowerLimit
                                10:6:12.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.250000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:6:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qRandomChance:Bool
                                                $$CHILD_BLOCK_START
                                                10:9:0.333333:Probability
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aMatcenSetState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Activate/Deactivate
                                        10:17:0:7:Matcen
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qRandomChance:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:9:0.500000:Probability
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:8:Matcen
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aMatcenSetState
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Activate/Deactivate
                                                10:17:0:9:Matcen
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Send New Droid To Command
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                09:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:6:Matcen
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:7:Matcen
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:8:Matcen
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:9:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:6:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:49:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:7:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:7:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:50:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:7:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:8:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:51:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:7:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:17:1:6:Matcen
                                07:1:0
                                10:17:0:9:Matcen
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:52:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:7:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:1:6:Matcen
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:30.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Droid Choose A Death
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.250000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:53:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:8:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qRandomChance:Bool
                                                $$CHILD_BLOCK_START
                                                10:9:0.333333:Probability
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:54:Path
                                        10:15:4352:AIGoalFlags
                                        10:10:0:8:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qRandomChance:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:9:0.500000:Probability
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aAIGoalFollowPathSimple
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                10:16:55:Path
                                                10:15:4352:AIGoalFlags
                                                10:10:0:8:GoalID
                                                10:10:0:0:GoalPriority
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aAIGoalFollowPathSimple
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object
                                                10:16:56:Path
                                                10:15:4352:AIGoalFlags
                                                10:10:0:8:GoalID
                                                10:10:0:0:GoalPriority
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Droid Die
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
00:119:Hide the end boss cinematic inv. powerup
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
                        10:1:0:151:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:MusicIntro
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
                        10:6:2.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:MusicSewer (Intro2)
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:MusicBoss
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:MusicTower2
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:50:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:128:MusicTower1
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:50:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:127:MusicMid4
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:50:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:126:MusicMid3
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:50:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:125:MusicMid2
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:50:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:124:MusicMid1
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:50:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
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
00:123:MusicMaint2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:MusicMaint1
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:MusicSewer1
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:End Level
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
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
