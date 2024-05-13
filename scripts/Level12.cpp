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
// Filename:	level12.cpp
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

#define ID_CUSTOM_OBJECT_09DF 0x001
#define ID_CUSTOM_OBJECT_09DD 0x002
#define ID_CUSTOM_OBJECT_09DC 0x003
#define ID_CUSTOM_OBJECT_09DE 0x004
#define ID_CUSTOM_OBJECT_09DB 0x005
#define ID_CUSTOM_OBJECT_1090 0x006
#define ID_CUSTOM_OBJECT_1173 0x007
#define ID_CUSTOM_OBJECT_087C 0x008
#define ID_CUSTOM_OBJECT_087B 0x009
#define ID_CUSTOM_OBJECT_087A 0x00a
#define ID_CUSTOM_OBJECT_0879 0x00b
#define ID_CUSTOM_OBJECT_0878 0x00c
#define ID_CUSTOM_OBJECT_204D 0x00d
#define ID_CUSTOM_OBJECT_0880 0x00e
#define ID_CUSTOM_OBJECT_1077 0x00f
#define ID_CUSTOM_OBJECT_1871 0x010
#define ID_CUSTOM_OBJECT_08AF 0x011
#define ID_CUSTOM_OBJECT_08B0 0x012
#define ID_CUSTOM_OBJECT_08B1 0x013
#define ID_CUSTOM_OBJECT_107D 0x014
#define ID_CUSTOM_OBJECT_117F 0x015
#define ID_CUSTOM_OBJECT_1180 0x016
#define ID_CUSTOM_OBJECT_1168 0x017
#define ID_CUSTOM_OBJECT_1081 0x018
#define ID_CUSTOM_OBJECT_08B5 0x019
#define ID_CUSTOM_OBJECT_08FD 0x01a
#define ID_CUSTOM_OBJECT_0949 0x01b
#define ID_CUSTOM_OBJECT_0846 0x01c
#define ID_CUSTOM_OBJECT_0954 0x01d
#define ID_CUSTOM_OBJECT_0955 0x01e
#define ID_CUSTOM_OBJECT_0956 0x01f
#define ID_CUSTOM_OBJECT_0957 0x020
#define ID_CUSTOM_OBJECT_08C2 0x021
#define ID_CUSTOM_OBJECT_18C3 0x022
#define ID_CUSTOM_OBJECT_0952 0x023
#define ID_CUSTOM_OBJECT_0953 0x024
#define ID_CUSTOM_OBJECT_0950 0x025
#define ID_CUSTOM_OBJECT_0951 0x026
#define ID_CUSTOM_OBJECT_104E 0x027
#define ID_CUSTOM_OBJECT_1969 0x028
#define ID_CUSTOM_OBJECT_216B 0x029
#define ID_CUSTOM_OBJECT_096C 0x02a
#define ID_CUSTOM_OBJECT_096E 0x02b
#define ID_CUSTOM_OBJECT_096D 0x02c
#define ID_CUSTOM_OBJECT_0977 0x02d
#define ID_CUSTOM_OBJECT_08E2 0x02e
#define ID_CUSTOM_OBJECT_097C 0x02f
#define ID_CUSTOM_OBJECT_097B 0x030
#define ID_CUSTOM_OBJECT_097A 0x031
#define ID_CUSTOM_OBJECT_08E9 0x032
#define ID_CUSTOM_OBJECT_08E8 0x033
#define ID_CUSTOM_OBJECT_105A 0x034
#define ID_CUSTOM_OBJECT_097D 0x035
#define ID_CUSTOM_OBJECT_1801 0x036
#define ID_CUSTOM_OBJECT_103C 0x037
#define ID_CUSTOM_OBJECT_0984 0x038
#define ID_CUSTOM_OBJECT_098C 0x039
#define ID_CUSTOM_OBJECT_0992 0x03a
#define ID_CUSTOM_OBJECT_20BC 0x03b
#define ID_CUSTOM_OBJECT_09C6 0x03c
#define ID_CUSTOM_OBJECT_09C7 0x03d
#define ID_CUSTOM_OBJECT_09C8 0x03e
#define ID_CUSTOM_OBJECT_11C5 0x03f
#define ID_CUSTOM_OBJECT_11C4 0x040
#define ID_CUSTOM_OBJECT_21BC 0x041
#define ID_CUSTOM_OBJECT_11B5 0x042
#define ID_CUSTOM_OBJECT_2886 0x043
#define ID_CUSTOM_OBJECT_11B4 0x044
#define ID_CUSTOM_OBJECT_1885 0x045
#define ID_CUSTOM_OBJECT_28BB 0x046
#define ID_CUSTOM_OBJECT_186E 0x047
#define ID_CUSTOM_OBJECT_18F0 0x048
#define ID_CUSTOM_OBJECT_19BE 0x049
#define ID_CUSTOM_OBJECT_18F1 0x04a
#define ID_CUSTOM_OBJECT_19C0 0x04b
#define ID_CUSTOM_OBJECT_18EE 0x04c
#define ID_CUSTOM_OBJECT_20CD 0x04d
#define ID_CUSTOM_OBJECT_28CC 0x04e
#define ID_CUSTOM_OBJECT_10B2 0x04f
#define ID_CUSTOM_OBJECT_18C1 0x050
#define ID_CUSTOM_OBJECT_21B8 0x051
#define ID_CUSTOM_OBJECT_21B9 0x052
#define ID_CUSTOM_OBJECT_080A 0x053
#define ID_CUSTOM_OBJECT_080C 0x054
#define ID_CUSTOM_OBJECT_0811 0x055

#define ID_TRIGGER_0012 0x056
#define ID_TRIGGER_0013 0x057
#define ID_TRIGGER_0007 0x058
#define ID_TRIGGER_0005 0x059
#define ID_TRIGGER_0003 0x05a
#define ID_TRIGGER_0008 0x05b
#define ID_TRIGGER_001E 0x05c
#define ID_TRIGGER_001F 0x05d
#define ID_TRIGGER_0001 0x05e
#define ID_TRIGGER_000B 0x05f
#define ID_TRIGGER_000A 0x060
#define ID_TRIGGER_000C 0x061
#define ID_TRIGGER_000D 0x062
#define ID_TRIGGER_0021 0x063
#define ID_TRIGGER_0020 0x064
#define ID_TRIGGER_0000 0x065
#define ID_TRIGGER_001A 0x066
#define ID_TRIGGER_0019 0x067
#define ID_TRIGGER_000E 0x068
#define ID_TRIGGER_001B 0x069
#define ID_TRIGGER_0018 0x06a
#define ID_TRIGGER_0017 0x06b
#define ID_TRIGGER_0016 0x06c
#define ID_TRIGGER_0015 0x06d
#define ID_TRIGGER_001D 0x06e
#define ID_TRIGGER_001C 0x06f
#define ID_TRIGGER_000F 0x070
#define ID_TRIGGER_0010 0x071

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

class CustomObjectScript_09DF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09DD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09DC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09DE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09DB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1090 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1173 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_087A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0879 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0878 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_204D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0880 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1077 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1871 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08AF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_107D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_117F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1180 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1168 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1081 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0949 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0846 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0954 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0955 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0956 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0957 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08C2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18C3 : public BaseScript {
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

class CustomObjectScript_0950 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0951 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_104E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1969 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_216B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_096D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0977 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08E2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08E9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08E8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_105A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_097D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1801 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_103C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0984 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_098C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0992 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20BC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11C5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11C4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21BC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11B5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2886 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11B4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1885 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_28BB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_186E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18F0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19BE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18F1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19C0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18EE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20CD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_28CC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10B2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18C1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21B8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21B9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_080C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0811 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
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

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0001 : public BaseScript {
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

class TriggerScript_000C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0021 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
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

class TriggerScript_000E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001C : public BaseScript {
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

static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_112 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_149 = 0;
static int ScriptActionCtr_148 = 0;
static int ScriptActionCtr_147 = 0;
static int ScriptActionCtr_146 = 0;
static int ScriptActionCtr_150 = 0;
static int ScriptActionCtr_151 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_152 = 0;
static int ScriptActionCtr_153 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_117 = 0;
static int ScriptActionCtr_115 = 0;
static int ScriptActionCtr_110 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_118 = 0;
static int ScriptActionCtr_116 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_170 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_173 = 0;
static int ScriptActionCtr_172 = 0;
static int ScriptActionCtr_171 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_113 = 0;
static int ScriptActionCtr_114 = 0;
static int ScriptActionCtr_133 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_142 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_119 = 0;
static int ScriptActionCtr_132 = 0;
static int ScriptActionCtr_131 = 0;
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
static int ScriptActionCtr_120 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_154 = 0;
static int ScriptActionCtr_167 = 0;
static int ScriptActionCtr_166 = 0;
static int ScriptActionCtr_165 = 0;
static int ScriptActionCtr_143 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_164 = 0;
static int ScriptActionCtr_163 = 0;
static int ScriptActionCtr_162 = 0;
static int ScriptActionCtr_161 = 0;
static int ScriptActionCtr_160 = 0;
static int ScriptActionCtr_145 = 0;
static int ScriptActionCtr_144 = 0;
static int ScriptActionCtr_159 = 0;
static int ScriptActionCtr_158 = 0;
static int ScriptActionCtr_157 = 0;
static int ScriptActionCtr_156 = 0;
static int ScriptActionCtr_155 = 0;
static int ScriptActionCtr_141 = 0;
static int ScriptActionCtr_140 = 0;
static int ScriptActionCtr_139 = 0;
static int ScriptActionCtr_138 = 0;
static int ScriptActionCtr_137 = 0;
static int ScriptActionCtr_136 = 0;
static int ScriptActionCtr_135 = 0;
static int ScriptActionCtr_134 = 0;
static int ScriptActionCtr_168 = 0;
static int ScriptActionCtr_169 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_010 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_112 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_149 = 0;
  ScriptActionCtr_148 = 0;
  ScriptActionCtr_147 = 0;
  ScriptActionCtr_146 = 0;
  ScriptActionCtr_150 = 0;
  ScriptActionCtr_151 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_152 = 0;
  ScriptActionCtr_153 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_117 = 0;
  ScriptActionCtr_115 = 0;
  ScriptActionCtr_110 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_118 = 0;
  ScriptActionCtr_116 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_170 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_173 = 0;
  ScriptActionCtr_172 = 0;
  ScriptActionCtr_171 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_113 = 0;
  ScriptActionCtr_114 = 0;
  ScriptActionCtr_133 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_142 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_119 = 0;
  ScriptActionCtr_132 = 0;
  ScriptActionCtr_131 = 0;
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
  ScriptActionCtr_120 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_154 = 0;
  ScriptActionCtr_167 = 0;
  ScriptActionCtr_166 = 0;
  ScriptActionCtr_165 = 0;
  ScriptActionCtr_143 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_164 = 0;
  ScriptActionCtr_163 = 0;
  ScriptActionCtr_162 = 0;
  ScriptActionCtr_161 = 0;
  ScriptActionCtr_160 = 0;
  ScriptActionCtr_145 = 0;
  ScriptActionCtr_144 = 0;
  ScriptActionCtr_159 = 0;
  ScriptActionCtr_158 = 0;
  ScriptActionCtr_157 = 0;
  ScriptActionCtr_156 = 0;
  ScriptActionCtr_155 = 0;
  ScriptActionCtr_141 = 0;
  ScriptActionCtr_140 = 0;
  ScriptActionCtr_139 = 0;
  ScriptActionCtr_138 = 0;
  ScriptActionCtr_137 = 0;
  ScriptActionCtr_136 = 0;
  ScriptActionCtr_135 = 0;
  ScriptActionCtr_134 = 0;
  ScriptActionCtr_168 = 0;
  ScriptActionCtr_169 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_010 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_112, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_149, file_ptr);
  File_WriteInt(ScriptActionCtr_148, file_ptr);
  File_WriteInt(ScriptActionCtr_147, file_ptr);
  File_WriteInt(ScriptActionCtr_146, file_ptr);
  File_WriteInt(ScriptActionCtr_150, file_ptr);
  File_WriteInt(ScriptActionCtr_151, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_152, file_ptr);
  File_WriteInt(ScriptActionCtr_153, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_117, file_ptr);
  File_WriteInt(ScriptActionCtr_115, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_118, file_ptr);
  File_WriteInt(ScriptActionCtr_116, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_170, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_173, file_ptr);
  File_WriteInt(ScriptActionCtr_172, file_ptr);
  File_WriteInt(ScriptActionCtr_171, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_113, file_ptr);
  File_WriteInt(ScriptActionCtr_114, file_ptr);
  File_WriteInt(ScriptActionCtr_133, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_142, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_119, file_ptr);
  File_WriteInt(ScriptActionCtr_132, file_ptr);
  File_WriteInt(ScriptActionCtr_131, file_ptr);
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
  File_WriteInt(ScriptActionCtr_120, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_154, file_ptr);
  File_WriteInt(ScriptActionCtr_167, file_ptr);
  File_WriteInt(ScriptActionCtr_166, file_ptr);
  File_WriteInt(ScriptActionCtr_165, file_ptr);
  File_WriteInt(ScriptActionCtr_143, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_164, file_ptr);
  File_WriteInt(ScriptActionCtr_163, file_ptr);
  File_WriteInt(ScriptActionCtr_162, file_ptr);
  File_WriteInt(ScriptActionCtr_161, file_ptr);
  File_WriteInt(ScriptActionCtr_160, file_ptr);
  File_WriteInt(ScriptActionCtr_145, file_ptr);
  File_WriteInt(ScriptActionCtr_144, file_ptr);
  File_WriteInt(ScriptActionCtr_159, file_ptr);
  File_WriteInt(ScriptActionCtr_158, file_ptr);
  File_WriteInt(ScriptActionCtr_157, file_ptr);
  File_WriteInt(ScriptActionCtr_156, file_ptr);
  File_WriteInt(ScriptActionCtr_155, file_ptr);
  File_WriteInt(ScriptActionCtr_141, file_ptr);
  File_WriteInt(ScriptActionCtr_140, file_ptr);
  File_WriteInt(ScriptActionCtr_139, file_ptr);
  File_WriteInt(ScriptActionCtr_138, file_ptr);
  File_WriteInt(ScriptActionCtr_137, file_ptr);
  File_WriteInt(ScriptActionCtr_136, file_ptr);
  File_WriteInt(ScriptActionCtr_135, file_ptr);
  File_WriteInt(ScriptActionCtr_134, file_ptr);
  File_WriteInt(ScriptActionCtr_168, file_ptr);
  File_WriteInt(ScriptActionCtr_169, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_112 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_149 = File_ReadInt(file_ptr);
  ScriptActionCtr_148 = File_ReadInt(file_ptr);
  ScriptActionCtr_147 = File_ReadInt(file_ptr);
  ScriptActionCtr_146 = File_ReadInt(file_ptr);
  ScriptActionCtr_150 = File_ReadInt(file_ptr);
  ScriptActionCtr_151 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_152 = File_ReadInt(file_ptr);
  ScriptActionCtr_153 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_117 = File_ReadInt(file_ptr);
  ScriptActionCtr_115 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_118 = File_ReadInt(file_ptr);
  ScriptActionCtr_116 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_170 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_173 = File_ReadInt(file_ptr);
  ScriptActionCtr_172 = File_ReadInt(file_ptr);
  ScriptActionCtr_171 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_113 = File_ReadInt(file_ptr);
  ScriptActionCtr_114 = File_ReadInt(file_ptr);
  ScriptActionCtr_133 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_142 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_119 = File_ReadInt(file_ptr);
  ScriptActionCtr_132 = File_ReadInt(file_ptr);
  ScriptActionCtr_131 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_120 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_154 = File_ReadInt(file_ptr);
  ScriptActionCtr_167 = File_ReadInt(file_ptr);
  ScriptActionCtr_166 = File_ReadInt(file_ptr);
  ScriptActionCtr_165 = File_ReadInt(file_ptr);
  ScriptActionCtr_143 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_164 = File_ReadInt(file_ptr);
  ScriptActionCtr_163 = File_ReadInt(file_ptr);
  ScriptActionCtr_162 = File_ReadInt(file_ptr);
  ScriptActionCtr_161 = File_ReadInt(file_ptr);
  ScriptActionCtr_160 = File_ReadInt(file_ptr);
  ScriptActionCtr_145 = File_ReadInt(file_ptr);
  ScriptActionCtr_144 = File_ReadInt(file_ptr);
  ScriptActionCtr_159 = File_ReadInt(file_ptr);
  ScriptActionCtr_158 = File_ReadInt(file_ptr);
  ScriptActionCtr_157 = File_ReadInt(file_ptr);
  ScriptActionCtr_156 = File_ReadInt(file_ptr);
  ScriptActionCtr_155 = File_ReadInt(file_ptr);
  ScriptActionCtr_141 = File_ReadInt(file_ptr);
  ScriptActionCtr_140 = File_ReadInt(file_ptr);
  ScriptActionCtr_139 = File_ReadInt(file_ptr);
  ScriptActionCtr_138 = File_ReadInt(file_ptr);
  ScriptActionCtr_137 = File_ReadInt(file_ptr);
  ScriptActionCtr_136 = File_ReadInt(file_ptr);
  ScriptActionCtr_135 = File_ReadInt(file_ptr);
  ScriptActionCtr_134 = File_ReadInt(file_ptr);
  ScriptActionCtr_168 = File_ReadInt(file_ptr);
  ScriptActionCtr_169 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Security
2:Level1
3:Level2
4:Level3
5:Level4
6:Arena
7:Repair
8:EndBoss
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

#define NUM_DOOR_NAMES 14
static const char *const Door_names[NUM_DOOR_NAMES] = {
    "Security Door",     "ArenaEntrance-3", "ArenaEntrance-2", "ArenaEntrance-1", "Arena 42 Entrance",
    "Arena 41 Entrance", "ProducerDoor",    "ArenaExit-3",     "ArenaExit-2",     "ArenaExit-1",
    "FinalExit-1",       "FinalExit-2",     "FinalExit-3",     "FinalExit-4"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 181
static const char *const Object_names[NUM_OBJECT_NAMES] = {"AMWaiter-4",
                                                           "AMWaiter-3",
                                                           "AMWaiter-2",
                                                           "AMWaiter-1",
                                                           "ArenaBot4-2",
                                                           "ArenaBot4-1",
                                                           "ArenaBot-3",
                                                           "ArenaBot-2",
                                                           "ArenaBot 1",
                                                           "StartInvis",
                                                           "TrapPower-2",
                                                           "TrapPower-1",
                                                           "Flamer1",
                                                           "Flamer2",
                                                           "Flamer3",
                                                           "Flamer4",
                                                           "FlamerMain",
                                                           "BeginFFSpew1",
                                                           "BeginFFSpew2",
                                                           "SRCollide-2",
                                                           "MCSwitch 1",
                                                           "Level1Orbot1",
                                                           "MCSwitch 6",
                                                           "MCSwitch 5",
                                                           "MCSwitch 4",
                                                           "MCSwitch 3",
                                                           "MCSwitch 2",
                                                           "EndBoss",
                                                           "SmokeSpew-8",
                                                           "SmokeSpew-7",
                                                           "SmokeSpew-6",
                                                           "SmokeSpew-5",
                                                           "SmokeSpew-4",
                                                           "SmokeSpew-3",
                                                           "SmokeSpew-1",
                                                           "SmokeSpew-2",
                                                           "ForceFieldSwitch 1",
                                                           "Compactor-2",
                                                           "CompactedBot-2",
                                                           "Compactor-1",
                                                           "CompactedBot-1",
                                                           "Flick-Control-2",
                                                           "Flick-Control-12",
                                                           "Flick-Control-11",
                                                           "Bell42",
                                                           "Bell41",
                                                           "Bell3",
                                                           "Bell2",
                                                           "Bell1",
                                                           "RandomSwitch-3",
                                                           "RandomSpew-2",
                                                           "SingleSpew-1",
                                                           "SingleSpew-2",
                                                           "SingleSpew-3",
                                                           "SingleSpew-4",
                                                           "SingleSpew-5",
                                                           "RedSpewer",
                                                           "RandomSpew-1",
                                                           "ArenaSpew-1",
                                                           "ArenaSpew-4",
                                                           "ArenaSpew-3",
                                                           "ArenaSpew-2",
                                                           "Repair 1",
                                                           "RCollide-1",
                                                           "RCollide-2",
                                                           "RCollide-3",
                                                           "RCollide-4",
                                                           "Repair 4",
                                                           "Repair 3",
                                                           "Repair 2",
                                                           "RBot-1",
                                                           "RBot-2",
                                                           "RBot-3",
                                                           "RBot-4",
                                                           "ToggleRepair-2",
                                                           "ToggleRepair-1",
                                                           "CowFF-2",
                                                           "CowFF-1",
                                                           "CowPipe-1",
                                                           "FlameCleanser-4",
                                                           "FlameCleanser-3",
                                                           "FlameCleanser-2",
                                                           "FlameCleanser-1",
                                                           "CowPipe-4",
                                                           "CowPipe-3",
                                                           "CowPipe-2",
                                                           "CowH-4",
                                                           "CowH-5",
                                                           "CowT-4",
                                                           "CowT-5",
                                                           "CowT-3",
                                                           "CowB-4",
                                                           "CowB-1",
                                                           "CowB-3",
                                                           "CowB-2",
                                                           "CowH-1",
                                                           "CowH-3",
                                                           "CowH-2",
                                                           "CowT-2",
                                                           "CowT-1",
                                                           "CowS-1",
                                                           "CowS-2",
                                                           "CowS-3",
                                                           "CowS-4",
                                                           "A3Gasser",
                                                           "RedSwitch-1",
                                                           "RedDummy-1",
                                                           "RedDummy-2",
                                                           "RedDummy-3",
                                                           "SRSwitch-1",
                                                           "SRepair-1",
                                                           "SRepair-2",
                                                           "SRCollide-1",
                                                           "SRSwitch-2",
                                                           "Level4Thresher1",
                                                           "Level3Tailbot1",
                                                           "Level2Squid1",
                                                           "Level1Sparky4",
                                                           "Level1Sparky3",
                                                           "Level1Sparky2",
                                                           "Level1Sparky1",
                                                           "Level1Orbot4",
                                                           "Level1Orbot3",
                                                           "Level1Orbot2",
                                                           "Level2Squid41",
                                                           "Level2Squid12",
                                                           "Level2Squid11",
                                                           "Level2Sixgun41",
                                                           "Level2Sixgun32",
                                                           "Level2Sixgun31",
                                                           "Level2Sixgun4",
                                                           "Level2Sixgun3",
                                                           "Level2Sixgun2",
                                                           "Level2Sixgun1",
                                                           "Level2Squid4",
                                                           "Level2Squid3",
                                                           "Level2Squid2",
                                                           "L2Migrate4",
                                                           "L2Migrate3",
                                                           "L2Migrate2",
                                                           "L2Migrate1",
                                                           "L2Surprise1",
                                                           "L2Surprise2",
                                                           "L2Surprise3",
                                                           "Level3Tailbot2",
                                                           "Level3Tailbot3",
                                                           "Level3Tailbot4",
                                                           "Level3Tubbs1",
                                                           "Level3Tubbs2",
                                                           "Level4Thresher3",
                                                           "Level4Thresher2",
                                                           "BellMain",
                                                           "A1Waiter1",
                                                           "A4Waiter-6",
                                                           "A4Waiter-5",
                                                           "A4Waiter-4",
                                                           "A4Waiter3",
                                                           "A4Waiter2",
                                                           "A4Waiter1",
                                                           "A3Waiter4",
                                                           "A3Waiter3",
                                                           "A3Waiter2",
                                                           "A3Waiter1",
                                                           "A2Waiter4",
                                                           "A2Waiter3",
                                                           "A2Waiter2",
                                                           "A2Waiter1",
                                                           "A1Waiter2",
                                                           "A1Waiter4",
                                                           "A1Waiter3",
                                                           "A1Waiter5",
                                                           "Secret Data",
                                                           "Level4Key",
                                                           "Level3Key",
                                                           "Level2Key",
                                                           "Level1Key",
                                                           "Arena 42 Entrance",
                                                           "Arena 41 Entrance",
                                                           "ArenaEntrance-3",
                                                           "ArenaEntrance-2",
                                                           "ArenaEntrance-1"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 12
static const char *const Room_names[NUM_ROOM_NAMES] = {"FireRoom",    "EntryForceField", "Flicker-2-1", "Flicker-1-3",
                                                       "Flicker-1-1", "Cow-1",           "Cow-2",       "EscapeCow",
                                                       "Arena3",      "Arena4-2",        "Arena4-1",    "MainEntrance"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 28
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EscapingBegin",    "EscapingEnd",        "Arena4Entrance",
    "Arena3Entrance",   "Arena2Entrance",     "Arena1Entrance",
    "Arena42Entrance",  "Arena41Entrance",    "ExitSequenceStart",
    "L2Migrate2",       "L2Migrate1",         "L2Surprise1",
    "SmashIt!",         "ChampCompetitors-2", "ChampCompetitors-1",
    "EndArenaManualFF", "MRepair-3",          "MRepair-2",
    "RepairEnter",      "MLevel4-3",          "MLevel4-2",
    "MLevel3",          "MLevel2-2",          "MLevel2",
    "MArena-2",         "MArena-1",           "Arena42Enter",
    "Arena41Enter"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 9
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSwitch11", "AmbSwitch31",     "AmbFurn11",
                                                         "JugFootHit",  "AmbPlasma21",     "Bell",
                                                         "AmbSwitch21", "AmbSirenIntense", "PupC1"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 1
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffect5"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 31
static const char *const Path_names[NUM_PATH_NAMES] = {
    "IntroCam",    "IntroShip",     "Arena42",        "Arena41",        "Arena3",      "Arena2",      "Arena1",
    "ExitCam",     "ExitSequence2", "Repair4",        "Repair3",        "Repair2",     "Repair1",     "SRepair1",
    "SRepair2",    "Level1Path1",   "Level1Path4",    "Level1Path3",    "Level1Path2", "Level2Path4", "Level2Path3",
    "Level2Path2", "Level2Path1",   "Level2Migrate1", "Level2Surprise", "Level3Path3", "Level3Path1", "Level3Path2",
    "Level4Path1", "Level4Path2",   "EndBoss"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 9
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Matcen 8", "Matcen 9", "Matcen 6", "Matcen 5", "Matcen 4",
                                                           "Matcen 3", "Matcen 2", "Matcen 1", "Matcen 7"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 9
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Escape from the firetrap",
                                                       "Disable the security forcefield",
                                                       "Escape from the Proving Grounds",
                                                       "Defeat Level 4 Arena",
                                                       "Defeat Level 3 Arena",
                                                       "Defeat Level 2 Arena",
                                                       "Defeat Level 1 Arena",
                                                       "Defeat the Proving Grounds Champion",
                                                       "Eliminate Championship Competitors"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 44
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroMessage",
                                                             "EscapedTorture",
                                                             "EscapeTorture2",
                                                             "EscapedDestroyed2",
                                                             "EscapedDestroyed",
                                                             "LevelStarted",
                                                             "ActivatedMatcen",
                                                             "EmergencyOverride",
                                                             "Arena4Enter",
                                                             "Arena4Enter2",
                                                             "Arena3Enter",
                                                             "Arena2Enter",
                                                             "Arena1Enter",
                                                             "EndLevel",
                                                             "DoorUnlocked",
                                                             "RepairActivated",
                                                             "RepairDeactivated",
                                                             "RepairingShip",
                                                             "CowFFDisable",
                                                             "GonnaClean",
                                                             "RedUnitsArmed",
                                                             "SRepairInit",
                                                             "Arena4Defeated2",
                                                             "Arena4Defeated",
                                                             "Arena3Defeated",
                                                             "Arena2Defeated",
                                                             "Arena1Defeated",
                                                             "ArenaChamp",
                                                             "MainGuards",
                                                             "MainFFDeactivated",
                                                             "EndBossBegin",
                                                             "Guards1",
                                                             "Guards2",
                                                             "Guards3",
                                                             "SecretData",
                                                             "RecoveredSecret",
                                                             "Level4Key",
                                                             "Level3Key",
                                                             "Level2Key",
                                                             "Level1Key",
                                                             "L4Door",
                                                             "L3Door",
                                                             "L2Door",
                                                             "L1Door"};
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
    strcpy(filename, "level12.msg");
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
  case ID_CUSTOM_OBJECT_09DF:
    return new CustomObjectScript_09DF;
    break;
  case ID_CUSTOM_OBJECT_09DD:
    return new CustomObjectScript_09DD;
    break;
  case ID_CUSTOM_OBJECT_09DC:
    return new CustomObjectScript_09DC;
    break;
  case ID_CUSTOM_OBJECT_09DE:
    return new CustomObjectScript_09DE;
    break;
  case ID_CUSTOM_OBJECT_09DB:
    return new CustomObjectScript_09DB;
    break;
  case ID_CUSTOM_OBJECT_1090:
    return new CustomObjectScript_1090;
    break;
  case ID_CUSTOM_OBJECT_1173:
    return new CustomObjectScript_1173;
    break;
  case ID_CUSTOM_OBJECT_087C:
    return new CustomObjectScript_087C;
    break;
  case ID_CUSTOM_OBJECT_087B:
    return new CustomObjectScript_087B;
    break;
  case ID_CUSTOM_OBJECT_087A:
    return new CustomObjectScript_087A;
    break;
  case ID_CUSTOM_OBJECT_0879:
    return new CustomObjectScript_0879;
    break;
  case ID_CUSTOM_OBJECT_0878:
    return new CustomObjectScript_0878;
    break;
  case ID_CUSTOM_OBJECT_204D:
    return new CustomObjectScript_204D;
    break;
  case ID_CUSTOM_OBJECT_0880:
    return new CustomObjectScript_0880;
    break;
  case ID_CUSTOM_OBJECT_1077:
    return new CustomObjectScript_1077;
    break;
  case ID_CUSTOM_OBJECT_1871:
    return new CustomObjectScript_1871;
    break;
  case ID_CUSTOM_OBJECT_08AF:
    return new CustomObjectScript_08AF;
    break;
  case ID_CUSTOM_OBJECT_08B0:
    return new CustomObjectScript_08B0;
    break;
  case ID_CUSTOM_OBJECT_08B1:
    return new CustomObjectScript_08B1;
    break;
  case ID_CUSTOM_OBJECT_107D:
    return new CustomObjectScript_107D;
    break;
  case ID_CUSTOM_OBJECT_117F:
    return new CustomObjectScript_117F;
    break;
  case ID_CUSTOM_OBJECT_1180:
    return new CustomObjectScript_1180;
    break;
  case ID_CUSTOM_OBJECT_1168:
    return new CustomObjectScript_1168;
    break;
  case ID_CUSTOM_OBJECT_1081:
    return new CustomObjectScript_1081;
    break;
  case ID_CUSTOM_OBJECT_08B5:
    return new CustomObjectScript_08B5;
    break;
  case ID_CUSTOM_OBJECT_08FD:
    return new CustomObjectScript_08FD;
    break;
  case ID_CUSTOM_OBJECT_0949:
    return new CustomObjectScript_0949;
    break;
  case ID_CUSTOM_OBJECT_0846:
    return new CustomObjectScript_0846;
    break;
  case ID_CUSTOM_OBJECT_0954:
    return new CustomObjectScript_0954;
    break;
  case ID_CUSTOM_OBJECT_0955:
    return new CustomObjectScript_0955;
    break;
  case ID_CUSTOM_OBJECT_0956:
    return new CustomObjectScript_0956;
    break;
  case ID_CUSTOM_OBJECT_0957:
    return new CustomObjectScript_0957;
    break;
  case ID_CUSTOM_OBJECT_08C2:
    return new CustomObjectScript_08C2;
    break;
  case ID_CUSTOM_OBJECT_18C3:
    return new CustomObjectScript_18C3;
    break;
  case ID_CUSTOM_OBJECT_0952:
    return new CustomObjectScript_0952;
    break;
  case ID_CUSTOM_OBJECT_0953:
    return new CustomObjectScript_0953;
    break;
  case ID_CUSTOM_OBJECT_0950:
    return new CustomObjectScript_0950;
    break;
  case ID_CUSTOM_OBJECT_0951:
    return new CustomObjectScript_0951;
    break;
  case ID_CUSTOM_OBJECT_104E:
    return new CustomObjectScript_104E;
    break;
  case ID_CUSTOM_OBJECT_1969:
    return new CustomObjectScript_1969;
    break;
  case ID_CUSTOM_OBJECT_216B:
    return new CustomObjectScript_216B;
    break;
  case ID_CUSTOM_OBJECT_096C:
    return new CustomObjectScript_096C;
    break;
  case ID_CUSTOM_OBJECT_096E:
    return new CustomObjectScript_096E;
    break;
  case ID_CUSTOM_OBJECT_096D:
    return new CustomObjectScript_096D;
    break;
  case ID_CUSTOM_OBJECT_0977:
    return new CustomObjectScript_0977;
    break;
  case ID_CUSTOM_OBJECT_08E2:
    return new CustomObjectScript_08E2;
    break;
  case ID_CUSTOM_OBJECT_097C:
    return new CustomObjectScript_097C;
    break;
  case ID_CUSTOM_OBJECT_097B:
    return new CustomObjectScript_097B;
    break;
  case ID_CUSTOM_OBJECT_097A:
    return new CustomObjectScript_097A;
    break;
  case ID_CUSTOM_OBJECT_08E9:
    return new CustomObjectScript_08E9;
    break;
  case ID_CUSTOM_OBJECT_08E8:
    return new CustomObjectScript_08E8;
    break;
  case ID_CUSTOM_OBJECT_105A:
    return new CustomObjectScript_105A;
    break;
  case ID_CUSTOM_OBJECT_097D:
    return new CustomObjectScript_097D;
    break;
  case ID_CUSTOM_OBJECT_1801:
    return new CustomObjectScript_1801;
    break;
  case ID_CUSTOM_OBJECT_103C:
    return new CustomObjectScript_103C;
    break;
  case ID_CUSTOM_OBJECT_0984:
    return new CustomObjectScript_0984;
    break;
  case ID_CUSTOM_OBJECT_098C:
    return new CustomObjectScript_098C;
    break;
  case ID_CUSTOM_OBJECT_0992:
    return new CustomObjectScript_0992;
    break;
  case ID_CUSTOM_OBJECT_20BC:
    return new CustomObjectScript_20BC;
    break;
  case ID_CUSTOM_OBJECT_09C6:
    return new CustomObjectScript_09C6;
    break;
  case ID_CUSTOM_OBJECT_09C7:
    return new CustomObjectScript_09C7;
    break;
  case ID_CUSTOM_OBJECT_09C8:
    return new CustomObjectScript_09C8;
    break;
  case ID_CUSTOM_OBJECT_11C5:
    return new CustomObjectScript_11C5;
    break;
  case ID_CUSTOM_OBJECT_11C4:
    return new CustomObjectScript_11C4;
    break;
  case ID_CUSTOM_OBJECT_21BC:
    return new CustomObjectScript_21BC;
    break;
  case ID_CUSTOM_OBJECT_11B5:
    return new CustomObjectScript_11B5;
    break;
  case ID_CUSTOM_OBJECT_2886:
    return new CustomObjectScript_2886;
    break;
  case ID_CUSTOM_OBJECT_11B4:
    return new CustomObjectScript_11B4;
    break;
  case ID_CUSTOM_OBJECT_1885:
    return new CustomObjectScript_1885;
    break;
  case ID_CUSTOM_OBJECT_28BB:
    return new CustomObjectScript_28BB;
    break;
  case ID_CUSTOM_OBJECT_186E:
    return new CustomObjectScript_186E;
    break;
  case ID_CUSTOM_OBJECT_18F0:
    return new CustomObjectScript_18F0;
    break;
  case ID_CUSTOM_OBJECT_19BE:
    return new CustomObjectScript_19BE;
    break;
  case ID_CUSTOM_OBJECT_18F1:
    return new CustomObjectScript_18F1;
    break;
  case ID_CUSTOM_OBJECT_19C0:
    return new CustomObjectScript_19C0;
    break;
  case ID_CUSTOM_OBJECT_18EE:
    return new CustomObjectScript_18EE;
    break;
  case ID_CUSTOM_OBJECT_20CD:
    return new CustomObjectScript_20CD;
    break;
  case ID_CUSTOM_OBJECT_28CC:
    return new CustomObjectScript_28CC;
    break;
  case ID_CUSTOM_OBJECT_10B2:
    return new CustomObjectScript_10B2;
    break;
  case ID_CUSTOM_OBJECT_18C1:
    return new CustomObjectScript_18C1;
    break;
  case ID_CUSTOM_OBJECT_21B8:
    return new CustomObjectScript_21B8;
    break;
  case ID_CUSTOM_OBJECT_21B9:
    return new CustomObjectScript_21B9;
    break;
  case ID_CUSTOM_OBJECT_080A:
    return new CustomObjectScript_080A;
    break;
  case ID_CUSTOM_OBJECT_080C:
    return new CustomObjectScript_080C;
    break;
  case ID_CUSTOM_OBJECT_0811:
    return new CustomObjectScript_0811;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
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
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_0021:
    return new TriggerScript_0021;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
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
  case ID_CUSTOM_OBJECT_09DF:
    delete ((CustomObjectScript_09DF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DD:
    delete ((CustomObjectScript_09DD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DC:
    delete ((CustomObjectScript_09DC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DE:
    delete ((CustomObjectScript_09DE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DB:
    delete ((CustomObjectScript_09DB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1090:
    delete ((CustomObjectScript_1090 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1173:
    delete ((CustomObjectScript_1173 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087C:
    delete ((CustomObjectScript_087C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087B:
    delete ((CustomObjectScript_087B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_087A:
    delete ((CustomObjectScript_087A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0879:
    delete ((CustomObjectScript_0879 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0878:
    delete ((CustomObjectScript_0878 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_204D:
    delete ((CustomObjectScript_204D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0880:
    delete ((CustomObjectScript_0880 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1077:
    delete ((CustomObjectScript_1077 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1871:
    delete ((CustomObjectScript_1871 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08AF:
    delete ((CustomObjectScript_08AF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B0:
    delete ((CustomObjectScript_08B0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B1:
    delete ((CustomObjectScript_08B1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_107D:
    delete ((CustomObjectScript_107D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_117F:
    delete ((CustomObjectScript_117F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1180:
    delete ((CustomObjectScript_1180 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1168:
    delete ((CustomObjectScript_1168 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1081:
    delete ((CustomObjectScript_1081 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B5:
    delete ((CustomObjectScript_08B5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FD:
    delete ((CustomObjectScript_08FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0949:
    delete ((CustomObjectScript_0949 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0846:
    delete ((CustomObjectScript_0846 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0954:
    delete ((CustomObjectScript_0954 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0955:
    delete ((CustomObjectScript_0955 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0956:
    delete ((CustomObjectScript_0956 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0957:
    delete ((CustomObjectScript_0957 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08C2:
    delete ((CustomObjectScript_08C2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18C3:
    delete ((CustomObjectScript_18C3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0952:
    delete ((CustomObjectScript_0952 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0953:
    delete ((CustomObjectScript_0953 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0950:
    delete ((CustomObjectScript_0950 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0951:
    delete ((CustomObjectScript_0951 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_104E:
    delete ((CustomObjectScript_104E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1969:
    delete ((CustomObjectScript_1969 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_216B:
    delete ((CustomObjectScript_216B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096C:
    delete ((CustomObjectScript_096C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096E:
    delete ((CustomObjectScript_096E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_096D:
    delete ((CustomObjectScript_096D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0977:
    delete ((CustomObjectScript_0977 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08E2:
    delete ((CustomObjectScript_08E2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097C:
    delete ((CustomObjectScript_097C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097B:
    delete ((CustomObjectScript_097B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097A:
    delete ((CustomObjectScript_097A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08E9:
    delete ((CustomObjectScript_08E9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08E8:
    delete ((CustomObjectScript_08E8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_105A:
    delete ((CustomObjectScript_105A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_097D:
    delete ((CustomObjectScript_097D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1801:
    delete ((CustomObjectScript_1801 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_103C:
    delete ((CustomObjectScript_103C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0984:
    delete ((CustomObjectScript_0984 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_098C:
    delete ((CustomObjectScript_098C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0992:
    delete ((CustomObjectScript_0992 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20BC:
    delete ((CustomObjectScript_20BC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C6:
    delete ((CustomObjectScript_09C6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C7:
    delete ((CustomObjectScript_09C7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C8:
    delete ((CustomObjectScript_09C8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11C5:
    delete ((CustomObjectScript_11C5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11C4:
    delete ((CustomObjectScript_11C4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21BC:
    delete ((CustomObjectScript_21BC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11B5:
    delete ((CustomObjectScript_11B5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2886:
    delete ((CustomObjectScript_2886 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11B4:
    delete ((CustomObjectScript_11B4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1885:
    delete ((CustomObjectScript_1885 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_28BB:
    delete ((CustomObjectScript_28BB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_186E:
    delete ((CustomObjectScript_186E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18F0:
    delete ((CustomObjectScript_18F0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19BE:
    delete ((CustomObjectScript_19BE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18F1:
    delete ((CustomObjectScript_18F1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19C0:
    delete ((CustomObjectScript_19C0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18EE:
    delete ((CustomObjectScript_18EE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20CD:
    delete ((CustomObjectScript_20CD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_28CC:
    delete ((CustomObjectScript_28CC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10B2:
    delete ((CustomObjectScript_10B2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18C1:
    delete ((CustomObjectScript_18C1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21B8:
    delete ((CustomObjectScript_21B8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21B9:
    delete ((CustomObjectScript_21B9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080A:
    delete ((CustomObjectScript_080A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_080C:
    delete ((CustomObjectScript_080C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0811:
    delete ((CustomObjectScript_0811 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
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
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_0021:
    delete ((TriggerScript_0021 *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
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
  case ID_CUSTOM_OBJECT_09DF:
  case ID_CUSTOM_OBJECT_09DD:
  case ID_CUSTOM_OBJECT_09DC:
  case ID_CUSTOM_OBJECT_09DE:
  case ID_CUSTOM_OBJECT_09DB:
  case ID_CUSTOM_OBJECT_1090:
  case ID_CUSTOM_OBJECT_1173:
  case ID_CUSTOM_OBJECT_087C:
  case ID_CUSTOM_OBJECT_087B:
  case ID_CUSTOM_OBJECT_087A:
  case ID_CUSTOM_OBJECT_0879:
  case ID_CUSTOM_OBJECT_0878:
  case ID_CUSTOM_OBJECT_204D:
  case ID_CUSTOM_OBJECT_0880:
  case ID_CUSTOM_OBJECT_1077:
  case ID_CUSTOM_OBJECT_1871:
  case ID_CUSTOM_OBJECT_08AF:
  case ID_CUSTOM_OBJECT_08B0:
  case ID_CUSTOM_OBJECT_08B1:
  case ID_CUSTOM_OBJECT_107D:
  case ID_CUSTOM_OBJECT_117F:
  case ID_CUSTOM_OBJECT_1180:
  case ID_CUSTOM_OBJECT_1168:
  case ID_CUSTOM_OBJECT_1081:
  case ID_CUSTOM_OBJECT_08B5:
  case ID_CUSTOM_OBJECT_08FD:
  case ID_CUSTOM_OBJECT_0949:
  case ID_CUSTOM_OBJECT_0846:
  case ID_CUSTOM_OBJECT_0954:
  case ID_CUSTOM_OBJECT_0955:
  case ID_CUSTOM_OBJECT_0956:
  case ID_CUSTOM_OBJECT_0957:
  case ID_CUSTOM_OBJECT_08C2:
  case ID_CUSTOM_OBJECT_18C3:
  case ID_CUSTOM_OBJECT_0952:
  case ID_CUSTOM_OBJECT_0953:
  case ID_CUSTOM_OBJECT_0950:
  case ID_CUSTOM_OBJECT_0951:
  case ID_CUSTOM_OBJECT_104E:
  case ID_CUSTOM_OBJECT_1969:
  case ID_CUSTOM_OBJECT_216B:
  case ID_CUSTOM_OBJECT_096C:
  case ID_CUSTOM_OBJECT_096E:
  case ID_CUSTOM_OBJECT_096D:
  case ID_CUSTOM_OBJECT_0977:
  case ID_CUSTOM_OBJECT_08E2:
  case ID_CUSTOM_OBJECT_097C:
  case ID_CUSTOM_OBJECT_097B:
  case ID_CUSTOM_OBJECT_097A:
  case ID_CUSTOM_OBJECT_08E9:
  case ID_CUSTOM_OBJECT_08E8:
  case ID_CUSTOM_OBJECT_105A:
  case ID_CUSTOM_OBJECT_097D:
  case ID_CUSTOM_OBJECT_1801:
  case ID_CUSTOM_OBJECT_103C:
  case ID_CUSTOM_OBJECT_0984:
  case ID_CUSTOM_OBJECT_098C:
  case ID_CUSTOM_OBJECT_0992:
  case ID_CUSTOM_OBJECT_20BC:
  case ID_CUSTOM_OBJECT_09C6:
  case ID_CUSTOM_OBJECT_09C7:
  case ID_CUSTOM_OBJECT_09C8:
  case ID_CUSTOM_OBJECT_11C5:
  case ID_CUSTOM_OBJECT_11C4:
  case ID_CUSTOM_OBJECT_21BC:
  case ID_CUSTOM_OBJECT_11B5:
  case ID_CUSTOM_OBJECT_2886:
  case ID_CUSTOM_OBJECT_11B4:
  case ID_CUSTOM_OBJECT_1885:
  case ID_CUSTOM_OBJECT_28BB:
  case ID_CUSTOM_OBJECT_186E:
  case ID_CUSTOM_OBJECT_18F0:
  case ID_CUSTOM_OBJECT_19BE:
  case ID_CUSTOM_OBJECT_18F1:
  case ID_CUSTOM_OBJECT_19C0:
  case ID_CUSTOM_OBJECT_18EE:
  case ID_CUSTOM_OBJECT_20CD:
  case ID_CUSTOM_OBJECT_28CC:
  case ID_CUSTOM_OBJECT_10B2:
  case ID_CUSTOM_OBJECT_18C1:
  case ID_CUSTOM_OBJECT_21B8:
  case ID_CUSTOM_OBJECT_21B9:
  case ID_CUSTOM_OBJECT_080A:
  case ID_CUSTOM_OBJECT_080C:
  case ID_CUSTOM_OBJECT_0811:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_0021:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_001C:
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
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0021;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_0010;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[85];
  static int cust_id_list[85] = {
      ID_CUSTOM_OBJECT_09DF, ID_CUSTOM_OBJECT_09DD, ID_CUSTOM_OBJECT_09DC, ID_CUSTOM_OBJECT_09DE,
      ID_CUSTOM_OBJECT_09DB, ID_CUSTOM_OBJECT_1090, ID_CUSTOM_OBJECT_1173, ID_CUSTOM_OBJECT_087C,
      ID_CUSTOM_OBJECT_087B, ID_CUSTOM_OBJECT_087A, ID_CUSTOM_OBJECT_0879, ID_CUSTOM_OBJECT_0878,
      ID_CUSTOM_OBJECT_204D, ID_CUSTOM_OBJECT_0880, ID_CUSTOM_OBJECT_1077, ID_CUSTOM_OBJECT_1871,
      ID_CUSTOM_OBJECT_08AF, ID_CUSTOM_OBJECT_08B0, ID_CUSTOM_OBJECT_08B1, ID_CUSTOM_OBJECT_107D,
      ID_CUSTOM_OBJECT_117F, ID_CUSTOM_OBJECT_1180, ID_CUSTOM_OBJECT_1168, ID_CUSTOM_OBJECT_1081,
      ID_CUSTOM_OBJECT_08B5, ID_CUSTOM_OBJECT_08FD, ID_CUSTOM_OBJECT_0949, ID_CUSTOM_OBJECT_0846,
      ID_CUSTOM_OBJECT_0954, ID_CUSTOM_OBJECT_0955, ID_CUSTOM_OBJECT_0956, ID_CUSTOM_OBJECT_0957,
      ID_CUSTOM_OBJECT_08C2, ID_CUSTOM_OBJECT_18C3, ID_CUSTOM_OBJECT_0952, ID_CUSTOM_OBJECT_0953,
      ID_CUSTOM_OBJECT_0950, ID_CUSTOM_OBJECT_0951, ID_CUSTOM_OBJECT_104E, ID_CUSTOM_OBJECT_1969,
      ID_CUSTOM_OBJECT_216B, ID_CUSTOM_OBJECT_096C, ID_CUSTOM_OBJECT_096E, ID_CUSTOM_OBJECT_096D,
      ID_CUSTOM_OBJECT_0977, ID_CUSTOM_OBJECT_08E2, ID_CUSTOM_OBJECT_097C, ID_CUSTOM_OBJECT_097B,
      ID_CUSTOM_OBJECT_097A, ID_CUSTOM_OBJECT_08E9, ID_CUSTOM_OBJECT_08E8, ID_CUSTOM_OBJECT_105A,
      ID_CUSTOM_OBJECT_097D, ID_CUSTOM_OBJECT_1801, ID_CUSTOM_OBJECT_103C, ID_CUSTOM_OBJECT_0984,
      ID_CUSTOM_OBJECT_098C, ID_CUSTOM_OBJECT_0992, ID_CUSTOM_OBJECT_20BC, ID_CUSTOM_OBJECT_09C6,
      ID_CUSTOM_OBJECT_09C7, ID_CUSTOM_OBJECT_09C8, ID_CUSTOM_OBJECT_11C5, ID_CUSTOM_OBJECT_11C4,
      ID_CUSTOM_OBJECT_21BC, ID_CUSTOM_OBJECT_11B5, ID_CUSTOM_OBJECT_2886, ID_CUSTOM_OBJECT_11B4,
      ID_CUSTOM_OBJECT_1885, ID_CUSTOM_OBJECT_28BB, ID_CUSTOM_OBJECT_186E, ID_CUSTOM_OBJECT_18F0,
      ID_CUSTOM_OBJECT_19BE, ID_CUSTOM_OBJECT_18F1, ID_CUSTOM_OBJECT_19C0, ID_CUSTOM_OBJECT_18EE,
      ID_CUSTOM_OBJECT_20CD, ID_CUSTOM_OBJECT_28CC, ID_CUSTOM_OBJECT_10B2, ID_CUSTOM_OBJECT_18C1,
      ID_CUSTOM_OBJECT_21B8, ID_CUSTOM_OBJECT_21B9, ID_CUSTOM_OBJECT_080A, ID_CUSTOM_OBJECT_080C,
      ID_CUSTOM_OBJECT_0811};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[15];
  cust_handle_list[1] = Object_handles[14];
  cust_handle_list[2] = Object_handles[13];
  cust_handle_list[3] = Object_handles[12];
  cust_handle_list[4] = Object_handles[16];
  cust_handle_list[5] = Object_handles[10];
  cust_handle_list[6] = Object_handles[11];
  cust_handle_list[7] = Object_handles[22];
  cust_handle_list[8] = Object_handles[23];
  cust_handle_list[9] = Object_handles[24];
  cust_handle_list[10] = Object_handles[25];
  cust_handle_list[11] = Object_handles[26];
  cust_handle_list[12] = Object_handles[20];
  cust_handle_list[13] = Object_handles[36];
  cust_handle_list[14] = Object_handles[37];
  cust_handle_list[15] = Object_handles[39];
  cust_handle_list[16] = Object_handles[41];
  cust_handle_list[17] = Object_handles[42];
  cust_handle_list[18] = Object_handles[43];
  cust_handle_list[19] = Object_handles[4];
  cust_handle_list[20] = Object_handles[5];
  cust_handle_list[21] = Object_handles[6];
  cust_handle_list[22] = Object_handles[7];
  cust_handle_list[23] = Object_handles[8];
  cust_handle_list[24] = Object_handles[49];
  cust_handle_list[25] = Object_handles[50];
  cust_handle_list[26] = Object_handles[58];
  cust_handle_list[27] = Object_handles[62];
  cust_handle_list[28] = Object_handles[73];
  cust_handle_list[29] = Object_handles[72];
  cust_handle_list[30] = Object_handles[71];
  cust_handle_list[31] = Object_handles[70];
  cust_handle_list[32] = Object_handles[74];
  cust_handle_list[33] = Object_handles[75];
  cust_handle_list[34] = Object_handles[66];
  cust_handle_list[35] = Object_handles[65];
  cust_handle_list[36] = Object_handles[64];
  cust_handle_list[37] = Object_handles[63];
  cust_handle_list[38] = Object_handles[76];
  cust_handle_list[39] = Object_handles[77];
  cust_handle_list[40] = Object_handles[78];
  cust_handle_list[41] = Object_handles[85];
  cust_handle_list[42] = Object_handles[84];
  cust_handle_list[43] = Object_handles[83];
  cust_handle_list[44] = Object_handles[104];
  cust_handle_list[45] = Object_handles[105];
  cust_handle_list[46] = Object_handles[108];
  cust_handle_list[47] = Object_handles[107];
  cust_handle_list[48] = Object_handles[106];
  cust_handle_list[49] = Object_handles[109];
  cust_handle_list[50] = Object_handles[113];
  cust_handle_list[51] = Object_handles[19];
  cust_handle_list[52] = Object_handles[112];
  cust_handle_list[53] = Object_handles[27];
  cust_handle_list[54] = Object_handles[21];
  cust_handle_list[55] = Object_handles[116];
  cust_handle_list[56] = Object_handles[115];
  cust_handle_list[57] = Object_handles[114];
  cust_handle_list[58] = Object_handles[152];
  cust_handle_list[59] = Object_handles[159];
  cust_handle_list[60] = Object_handles[160];
  cust_handle_list[61] = Object_handles[161];
  cust_handle_list[62] = Object_handles[162];
  cust_handle_list[63] = Object_handles[163];
  cust_handle_list[64] = Object_handles[164];
  cust_handle_list[65] = Object_handles[165];
  cust_handle_list[66] = Object_handles[166];
  cust_handle_list[67] = Object_handles[170];
  cust_handle_list[68] = Object_handles[168];
  cust_handle_list[69] = Object_handles[169];
  cust_handle_list[70] = Object_handles[167];
  cust_handle_list[71] = Object_handles[0];
  cust_handle_list[72] = Object_handles[1];
  cust_handle_list[73] = Object_handles[2];
  cust_handle_list[74] = Object_handles[3];
  cust_handle_list[75] = Object_handles[171];
  cust_handle_list[76] = Object_handles[172];
  cust_handle_list[77] = Object_handles[173];
  cust_handle_list[78] = Object_handles[174];
  cust_handle_list[79] = Object_handles[175];
  cust_handle_list[80] = Object_handles[176];
  cust_handle_list[81] = Object_handles[177];
  cust_handle_list[82] = Object_handles[178];
  cust_handle_list[83] = Object_handles[179];
  cust_handle_list[84] = Object_handles[180];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 85;
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

    // Script 101: ArenaBots SpecialFX (DISABLED)
    if (1 == false) {
      aObjSpark(Object_handles[0], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[1], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[2], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[3], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[4], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[5], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[6], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[7], 20.000000f, 999999.000000f);
      aObjSpark(Object_handles[8], 20.000000f, 999999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }

    // Script 061: Beginning (Trapped)
    if (1) {
      aObjHide(Object_handles[9]);
      aObjPlayAnim(Object_handles[10], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[11], 1, 3, 2.000000f, 1);
      aObjMakeInvuln(Object_handles[10], 999999);
      aObjMakeInvuln(Object_handles[11], 999999);
      aObjMakeInvuln(Object_handles[12], 90);
      aObjMakeInvuln(Object_handles[13], 90);
      aObjMakeInvuln(Object_handles[14], 90);
      aObjMakeInvuln(Object_handles[15], 90);
      aObjMakeInvuln(Object_handles[16], 90);
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aTurnOnSpew(Object_handles[17], 0, 16, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  3.800000f, 19.000000f, 0, 1);
      aTurnOnSpew(Object_handles[18], 0, 16, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                  3.800000f, 19.000000f, 0, 0);
      aSetLevelTimer(10.500000f, 6);
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[19], Path_indexes[1], 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }

    // Script 002: Level Begin
    if (1) {
      aUserVarSet(11, 0.000000f);
      aUserVarSet(10, 0.000000f);
      aAISetTeam(196608, Object_handles[27]);
      aTurnOnSpew(Object_handles[28], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[29], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[30], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[31], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[32], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[33], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[34], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aTurnOnSpew(Object_handles[35], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  16.000000f, 0, -1);
      aPortalRenderSet(1, 0, Room_indexes[1], 1);
      aDoorLockUnlock(0, Door_handles[0]);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 154: Music-Intro
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_154 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_154++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 064: DisableControls (Start Fires, Etc)
    if (event_data->id == 6) {
      aSoundPlaySteaming("VoxL12StartLevel.osf", 1.000000f);
      aSetObjectTimer(Object_handles[16], 23.000000f, -1);
      aSetObjectTimer(Object_handles[12], 0.000000f, -1);
      aSetObjectTimer(Object_handles[13], 5.000000f, -1);
      aSetObjectTimer(Object_handles[14], 10.000000f, -1);
      aSetObjectTimer(Object_handles[15], 15.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }

    // Script 170: CowPipe Actions
    if ((ScriptActionCtr_170 < 1) && (event_data->id == 8)) {
      aRoomSetFog(Room_indexes[6], 0.750000f, 0.500000f, 0.100000f, 1000.000000f);
      aRoomSetFog(Room_indexes[5], 0.750000f, 0.500000f, 0.100000f, 1000.000000f);
      aRoomFogSetState(1, Room_indexes[6]);
      aRoomFogSetState(1, Room_indexes[5]);
      aRoomChangeFog(Room_indexes[5], 0.750000f, 0.500000f, 0.100000f, 200.000000f, 5.000000f);
      aRoomChangeFog(Room_indexes[6], 0.750000f, 0.500000f, 0.100000f, 200.000000f, 5.000000f);
      aSetLevelTimer(3.000000f, 9);
      aShowHUDMessage(Message_strings[19]);
      aSoundPlayObject(Sound_indexes[0], Object_handles[79], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[80], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[81], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[82], 1.000000f);
      aObjPlayAnim(Object_handles[79], 0, 3, 3.000000f, 0);
      aObjPlayAnim(Object_handles[80], 0, 3, 3.000000f, 0);
      aObjPlayAnim(Object_handles[81], 0, 3, 3.000000f, 0);
      aObjPlayAnim(Object_handles[82], 0, 3, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_170 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_170++;
    }

    // Script 053: CowPipe Burn
    if ((ScriptActionCtr_053 < 1) && (event_data->id == 9)) {
      aSetLevelTimer(20.000000f, 10);
      aTurnOnSpew(Object_handles[79], 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.140000f, 20.000000f, 5.000000f,
                  45.000000f, 0, -1);
      aTurnOnSpew(Object_handles[80], 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.140000f, 20.000000f, 5.000000f,
                  45.000000f, 0, -1);
      aTurnOnSpew(Object_handles[81], 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.140000f, 20.000000f, 5.000000f,
                  45.000000f, 0, -1);
      aTurnOnSpew(Object_handles[82], 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.140000f, 20.000000f, 5.000000f,
                  45.000000f, 0, -1);
      aRoomSetDamage(Room_indexes[5], 5.000000f, 4);
      aRoomSetDamage(Room_indexes[6], 5.000000f, 4);
      aAIGoalGotoRoom(Object_handles[86], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[87], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[88], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[89], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[90], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[91], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[92], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[93], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[94], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[95], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[96], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[97], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[98], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[99], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[100], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[101], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[102], Room_indexes[7], 0, 4352, -1);
      aAIGoalGotoRoom(Object_handles[103], Room_indexes[7], 0, 4352, -1);
      aSetObjectOnFire(Object_handles[86], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[87], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[88], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[89], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[90], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[91], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[93], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[94], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[92], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[95], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[96], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[97], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[98], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[99], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[100], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[101], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[102], 20.000000f, 4.000000f);
      aSetObjectOnFire(Object_handles[103], 20.000000f, 4.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 054: Cow Cleansing Done
    if ((ScriptActionCtr_054 < 1) && (event_data->id == 10)) {
      aObjPlayAnim(Object_handles[79], 3, 6, 3.000000f, 0);
      aObjPlayAnim(Object_handles[80], 3, 6, 3.000000f, 0);
      aObjPlayAnim(Object_handles[81], 3, 6, 3.000000f, 0);
      aObjPlayAnim(Object_handles[82], 3, 6, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], Object_handles[79], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[81], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[80], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[82], 1.000000f);
      aRoomSetDamage(Room_indexes[5], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[6], 0.000000f, 4);
      aRoomChangeFog(Room_indexes[5], 0.750000f, 0.500000f, 0.100000f, 1500.000000f, 15.000000f);
      aRoomChangeFog(Room_indexes[6], 0.750000f, 0.500000f, 0.100000f, 1500.000000f, 15.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 142: Main Guards Gone
    if (event_data->id == 7) {
      aGoalCompleted(Goal_indexes[8], 1);
      aPortalRenderSet(0, 4, Room_indexes[11], 1);
      aShowHUDMessage(Message_strings[29]);

      // Increment the script action counter
      if (ScriptActionCtr_142 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_142++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 003: Disable Player
    if ((ScriptActionCtr_003 < 1) && (1)) {
      aObjSaveHandle(qPlayerClosest(Object_handles[9], -1), 0);
      aPhysFlags(1, 58720256, qObjSavedHandle(0));
      aTogglePlayerObjControl(0, 16447, qObjSavedHandle(0));

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  case EVT_PLAYER_RESPAWN: {
    tOSIRISEVTPLAYERRESPAWN *event_data = &data->evt_player_respawn;

    // Script 112: Disable Player After Death
    if (((ScriptActionCtr_063 > 0) == false) && ((ScriptActionCtr_062 > 0) == false) &&
        (event_data->it_handle == qObjSavedHandle(0))) {
      aPhysFlags(1, 58720256, qObjSavedHandle(0));
      aTogglePlayerObjControl(0, 16447, qObjSavedHandle(0));

      // Increment the script action counter
      if (ScriptActionCtr_112 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_112++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 149: Flamer-4
    if (1) {
      if (qUserFlag(3) == true) {
        aObjMakeInvuln(data->me_handle, 60);
        aSetObjectTimer(data->me_handle, 25.000000f, -1);
        aUserFlagSet(3, 0);
        aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.140000f, 5.000000f, 3.500000f,
                    30.000000f, 0, -1);
        aObjMakeVulnerable(data->me_handle);
        aSetObjectTimer(data->me_handle, 5.000000f, -1);
        aUserFlagSet(3, 1);
        aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_149 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_149++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 148: Flamer-3
    if (1) {
      if (qUserFlag(2) == true) {
        aObjMakeInvuln(data->me_handle, 60);
        aSetObjectTimer(data->me_handle, 20.000000f, -1);
        aUserFlagSet(2, 0);
        aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.140000f, 10.000000f, 3.500000f,
                    30.000000f, 0, -1);
        aObjMakeVulnerable(data->me_handle);
        aSetObjectTimer(data->me_handle, 10.000000f, -1);
        aUserFlagSet(2, 1);
        aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_148 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_148++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 147: Flamer-2
    if (1) {
      if (qUserFlag(1) == true) {
        aObjMakeInvuln(data->me_handle, 60);
        aSetObjectTimer(data->me_handle, 15.000000f, -1);
        aUserFlagSet(1, 0);
        aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.140000f, 15.000000f, 3.500000f,
                    30.000000f, 0, -1);
        aObjMakeVulnerable(data->me_handle);
        aSetObjectTimer(data->me_handle, 15.000000f, -1);
        aUserFlagSet(1, 1);
        aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_147 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_147++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 146: Flamer-1
    if (1) {
      if (qUserFlag(0) == true) {
        aObjMakeInvuln(data->me_handle, 60);
        aSetObjectTimer(data->me_handle, 10.000000f, -1);
        aUserFlagSet(0, 0);
        aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      } else {
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.140000f, 20.000000f, 3.500000f,
                    30.000000f, 0, -1);
        aObjMakeVulnerable(data->me_handle);
        aSetObjectTimer(data->me_handle, 20.000000f, -1);
        aUserFlagSet(0, 1);
        aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_146 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_146++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 151: FlameMain Destroyed
    if (1) {
      aRoomSetDamage(Room_indexes[0], 0.000000f, 4);
      aShowHUDMessage(Message_strings[1]);
      aShowHUDMessage(Message_strings[2]);
      aObjSetLightingDist(Object_handles[10], 45.000000f);
      aObjSetLightingDist(Object_handles[11], 45.000000f);
      aObjMakeVulnerable(Object_handles[10]);
      aObjMakeVulnerable(Object_handles[11]);

      // Increment the script action counter
      if (ScriptActionCtr_151 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_151++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 150: Flamer-Main
    if (1) {
      if (qUserFlag(4) == true) {
        aObjMakeInvuln(data->me_handle, 60);
        aRoomSetDamage(Room_indexes[0], 0.000000f, 4);
        aUserFlagSet(4, 0);
        if (qUserFlag(5) == true) {
          aSetObjectTimer(data->me_handle, 10.000000f, -1);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        } else {
          aSetObjectTimer(data->me_handle, 25.000000f, -1);
          aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
          aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        }
      } else {
        if ((qObjExists(Object_handles[12]) == false) && (qObjExists(Object_handles[13]) == false) &&
            (qObjExists(Object_handles[14]) == false) && (qObjExists(Object_handles[15]) == false)) {
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(5, 1);
          aObjMakeVulnerable(data->me_handle);
          aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
        } else {
          aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
          aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        }
        aRoomSetDamage(Room_indexes[0], 3.000000f, 4);
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.130000f, 5.000000f, 5.000000f,
                    55.000000f, 0, -1);
        aSetObjectTimer(data->me_handle, 5.000000f, -1);
        aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
        aUserFlagSet(4, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_150 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_150++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1090::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 063: Freedom!!! (2)
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[0], 1);
      aTurnOffSpew(0);
      if (qObjExists(Object_handles[11]) == false) {
        aGoalCompleted(Goal_indexes[0], 1);
        aMusicSetRegionAll(1);
        aShowHUDMessage(Message_strings[3]);
        aPhysFlags(0, 58720256, qObjSavedHandle(0));
        aTogglePlayerObjAllControls(1, qObjSavedHandle(0));
      } else {
        aShowHUDMessage(Message_strings[4]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1173::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 062: Freedom!!!
    if (1) {
      aPortalRenderSet(0, 0, Room_indexes[0], 1);
      aTurnOffSpew(1);
      if (qObjExists(Object_handles[10]) == false) {
        aGoalCompleted(Goal_indexes[0], 1);
        aMusicSetRegionAll(1);
        aShowHUDMessage(Message_strings[3]);
        aPhysFlags(0, 58720256, qObjSavedHandle(0));
        aTogglePlayerObjAllControls(1, qObjSavedHandle(0));
      } else {
        aShowHUDMessage(Message_strings[4]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Switch Enables Matcen (6)
    if ((ScriptActionCtr_030 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[6]);
      aMatcenSetState(1, Matcen_indexes[2]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: Switch Enables Matcen (5)
    if ((ScriptActionCtr_029 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[6]);
      aMatcenSetState(1, Matcen_indexes[3]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_087A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Switch Enables Matcen (4)
    if ((ScriptActionCtr_028 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[6]);
      aMatcenSetState(1, Matcen_indexes[4]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0879::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Switch Enables Matcen (3)
    if ((ScriptActionCtr_027 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[6]);
      aMatcenSetState(1, Matcen_indexes[5]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0878::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Switch Enables Matcen (2)
    if ((ScriptActionCtr_026 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[6]);
      aMatcenSetState(1, Matcen_indexes[6]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_204D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Switch Enables Matcen (1)
    if ((ScriptActionCtr_001 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aShowHUDMessage(Message_strings[6]);
      aMatcenSetState(1, Matcen_indexes[7]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0880::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Security Forcefield Switch
    if ((ScriptActionCtr_004 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMatcenSetState(0, Matcen_indexes[1]);
      aMatcenSetState(0, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[8]);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aShowHUDMessage(Message_strings[7]);
      aGoalCompleted(Goal_indexes[1], 1);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1077::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 046: Compactor 2 Slamming
    if ((ScriptActionCtr_046 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjDestroy(Object_handles[38]);
      aObjPlayAnim(data->me_handle, 0, 5, 1.000000f, 0);
      aMiscViewerShake(80.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1871::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 005: Compactor 1 Slamming
    if ((ScriptActionCtr_005 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjDestroy(Object_handles[40]);
      aObjPlayAnim(data->me_handle, 0, 5, 1.000000f, 0);
      aMiscViewerShake(80.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08AF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 019: FlickerForcefield-1 (3)
    if (1) {
      aObjGhostSet(1, data->me_handle);
      aSetObjectTimer(data->me_handle, 5.000000f, -1);
      aUserVarSet(0, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 021: FlickerForcefield-2 (3)
    if (1) {
      if (qUserVarValue(5) == 0.000000f) {
        aUserVarSet(5, 1.000000f);
        aSetObjectTimer(data->me_handle, 3.000000f, -1);
      } else {
        aUserVarSet(5, 0.000000f);
        aSetObjectTimer(data->me_handle, 0.800000f, -1);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aPortalRenderToggle(0, Room_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 018: FlickerForcefield-1 (2)
    if (1) {
      aObjGhostSet(1, data->me_handle);
      aSetObjectTimer(data->me_handle, 3.000000f, -1);
      aUserVarSet(5, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 020: FlickerForcefield-2 (2)
    if (1) {
      if (qUserVarValue(1) == 0.000000f) {
        aUserVarSet(1, 1.000000f);
        aSetObjectTimer(data->me_handle, 2.500000f, -1);
      } else {
        aUserVarSet(1, 0.000000f);
        aSetObjectTimer(data->me_handle, 0.750000f, -1);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aPortalRenderToggle(1, Room_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 007: FlickerForcefield-1 (1)
    if (1) {
      aObjGhostSet(1, data->me_handle);
      aSetObjectTimer(data->me_handle, 4.000000f, -1);
      aUserVarSet(1, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 008: FlickerForcefield-2 (1)
    if (1) {
      if (qUserVarValue(0) == 0.000000f) {
        aUserVarSet(0, 1.000000f);
        aSetObjectTimer(data->me_handle, 2.000000f, -1);
      } else {
        aUserVarSet(0, 0.000000f);
        aSetObjectTimer(data->me_handle, 0.700000f, -1);
      }
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aPortalRenderToggle(0, Room_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_107D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 087: Arena4-2 Bot
    if (1) {
      aDoorLockUnlock(0, Door_handles[4]);
      aSoundPlaySteaming("VoxL12SpecificA.osf", 1.000000f);
      aGoalCompleted(Goal_indexes[3], 1);
      aPortalRenderToggle(0, Room_indexes[9], 1);
      if (qObjExists(Object_handles[5]) == false) {
        aShowHUDMessage(Message_strings[22]);
        aPortalRenderSet(0, 2, Room_indexes[10], 1);
        aPortalRenderSet(0, 2, Room_indexes[9], 1);
      } else {
        aShowHUDMessage(Message_strings[23]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 118: Arena 42 Special Timer
    if ((ScriptActionCtr_118 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[44], 1.000000f);
      aObjMakeVulnerable(data->me_handle);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_118 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_118++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_117F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 086: Arena4-1 Bot
    if (1) {
      aDoorLockUnlock(0, Door_handles[5]);
      aSoundPlaySteaming("VoxL12SpecificA.osf", 1.000000f);
      aGoalCompleted(Goal_indexes[3], 1);
      aPortalRenderToggle(0, Room_indexes[10], 1);
      if (qObjExists(Object_handles[4]) == false) {
        aShowHUDMessage(Message_strings[22]);
        aPortalRenderSet(0, 2, Room_indexes[10], 1);
        aPortalRenderSet(0, 2, Room_indexes[9], 1);
      } else {
        aShowHUDMessage(Message_strings[23]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 116: Arena 41 Special Timer
    if ((ScriptActionCtr_116 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[45], 1.000000f);
      aObjMakeVulnerable(data->me_handle);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_116 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_116++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1180::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 089: Arena3 Bot
    if (1) {
      aDoorLockUnlock(0, Door_handles[1]);
      aDoorLockUnlock(0, Door_handles[7]);
      aSoundPlaySteaming("VoxL12SpecificB.osf", 1.000000f);
      aShowHUDMessage(Message_strings[24]);
      aSetObjectTimer(Object_handles[114], 2.000000f, -1);
      aGoalCompleted(Goal_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 111: Arena 3 Special Timer
    if ((ScriptActionCtr_111 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[46], 1.000000f);
      aObjMakeVulnerable(data->me_handle);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1168::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 000: Arena2 Bot
    if (1) {
      aDoorLockUnlock(0, Door_handles[2]);
      aDoorLockUnlock(0, Door_handles[8]);
      aSoundPlaySteaming("VoxL12SpecificA.osf", 1.000000f);
      aShowHUDMessage(Message_strings[25]);
      aSetObjectTimer(Object_handles[115], 2.000000f, -1);
      aGoalCompleted(Goal_indexes[5], 1);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 109: Arena 2 Special Timer
    if ((ScriptActionCtr_109 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[47], 1.000000f);
      aObjMakeVulnerable(data->me_handle);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1081::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 105: ArenaBotsINIT
    if (1) {
      aObjMakeInvuln(Object_handles[27], 999999);
      aObjMakeInvuln(Object_handles[4], 999999);
      aObjMakeInvuln(Object_handles[5], 999999);
      aObjMakeInvuln(Object_handles[6], 999999);
      aObjMakeInvuln(Object_handles[7], 999999);
      aObjMakeInvuln(Object_handles[8], 999999);
      aAISetState(0, Object_handles[4]);
      aAISetState(0, Object_handles[5]);
      aAISetState(0, Object_handles[6]);
      aAISetState(0, Object_handles[7]);
      aAISetState(0, Object_handles[8]);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 088: Arena1 Bot
    if (1) {
      aGoalCompleted(Goal_indexes[6], 1);
      aDoorLockUnlock(0, Door_handles[9]);
      aDoorLockUnlock(0, Door_handles[3]);
      aSoundPlaySteaming("VoxL12SpecificB.osf", 1.000000f);
      aSetObjectTimer(Object_handles[116], 2.000000f, -1);
      aShowHUDMessage(Message_strings[26]);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }

    // Script 169: Cowards Hostility
    if ((ScriptActionCtr_169 < 1) && (1)) {
      aAIFlags(1, 131104, Object_handles[99]);
      aAIFlags(1, 131104, Object_handles[98]);
      aAIFlags(1, 131104, Object_handles[97]);
      aAIFlags(1, 131104, Object_handles[96]);
      aAIFlags(1, 131104, Object_handles[95]);
      aAIFlags(1, 131104, Object_handles[94]);
      aAIFlags(1, 131104, Object_handles[93]);
      aAIFlags(1, 131104, Object_handles[92]);
      aAIFlags(1, 131104, Object_handles[91]);
      aAIFlags(1, 131104, Object_handles[90]);
      aAIFlags(1, 131104, Object_handles[88]);
      aAIFlags(1, 131104, Object_handles[89]);
      aAIFlags(1, 131104, Object_handles[87]);
      aAIFlags(1, 131104, Object_handles[86]);
      aAIFlags(1, 131104, Object_handles[100]);
      aAIFlags(1, 131104, Object_handles[101]);
      aAIFlags(1, 131104, Object_handles[102]);
      aAIFlags(1, 131104, Object_handles[103]);

      // Increment the script action counter
      if (ScriptActionCtr_169 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_169++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 106: Arena 1 Special Timer
    if ((ScriptActionCtr_106 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[48], 1.000000f);
      aObjMakeVulnerable(data->me_handle);
      aAISetTeam(0, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: RandomSwitch-3
    if ((ScriptActionCtr_024 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aDoorLockUnlock(0, Door_handles[6]);
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[14]);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 025: RandomRedExtraSpew
    if (1) {
      aTurnOnSpew(Object_handles[51], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[52], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[53], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[54], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[55], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[56], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[57], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);
      aTurnOnSpew(Object_handles[50], 0, 7, 1.000000f, 0.010000f, 98304, 0, 1.200000f, 0.150000f, -1.000000f, 4.000000f,
                  20.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0949::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 031: ArenaSpewers
    if (1) {
      aTurnOnSpew(Object_handles[59], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.140000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);
      aTurnOnSpew(Object_handles[60], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.140000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);
      aTurnOnSpew(Object_handles[61], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.140000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);
      aTurnOnSpew(Object_handles[58], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.140000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0846::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 006: Repair INIT
    if (1) {
      aUserVarSet(3, 0.000000f);
      aUserVarSet(2, 0.000000f);
      aObjHide(Object_handles[63]);
      aObjHide(Object_handles[64]);
      aObjHide(Object_handles[65]);
      aObjHide(Object_handles[66]);
      aObjPlayAnim(Object_handles[67], 0, 14, 5.000000f, 1);
      aObjPlayAnim(Object_handles[68], 0, 14, 5.000000f, 1);
      aObjPlayAnim(Object_handles[69], 0, 14, 5.000000f, 1);
      aObjPlayAnim(Object_handles[62], 0, 14, 5.000000f, 1);
      aAISetState(0, Object_handles[70]);
      aAISetState(0, Object_handles[71]);
      aAISetState(0, Object_handles[72]);
      aAISetState(0, Object_handles[73]);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0954::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: RBot Destruct...4
    if ((ScriptActionCtr_041 < 1) &&
        (((ScriptActionCtr_036 > 0) == false) && (qObjIsPlayerWeapon(event_data->it_handle) == true))) {
      aObjDestroy(data->me_handle);
      aObjDestroy(Object_handles[67]);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0955::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: RBot Destruct...3
    if ((ScriptActionCtr_040 < 1) &&
        (((ScriptActionCtr_036 > 0) == false) && (qObjIsPlayerWeapon(event_data->it_handle) == true))) {
      aObjDestroy(data->me_handle);
      aObjDestroy(Object_handles[68]);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0956::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: RBot Destruct...2
    if ((ScriptActionCtr_039 < 1) &&
        (((ScriptActionCtr_033 > 0) == false) && (qObjIsPlayerWeapon(event_data->it_handle) == true))) {
      aObjDestroy(data->me_handle);
      aObjDestroy(Object_handles[69]);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0957::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: RBot Destruct...1
    if ((ScriptActionCtr_032 < 1) &&
        (((ScriptActionCtr_033 > 0) == false) && (qObjIsPlayerWeapon(event_data->it_handle) == true))) {
      aObjDestroy(data->me_handle);
      aObjDestroy(Object_handles[62]);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08C2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: ToggleRepar-22
    if ((ScriptActionCtr_037 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(3) == 1.000000f))) {
      aShowHUDMessage(Message_strings[15]);
      aObjPlayAnim(Object_handles[68], 0, 1, 0.100000f, 0);
      aObjPlayAnim(Object_handles[67], 0, 1, 0.100000f, 0);
      aObjSetLightingDist(Object_handles[68], 40.000000f);
      aObjSetLightingDist(Object_handles[67], 40.000000f);
      aAISetState(1, Object_handles[68]);
      aAISetState(1, Object_handles[67]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }

    // Script 036: ToggleRepair-21
    if ((ScriptActionCtr_036 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      if (qUserVarValue(3) == 0.000000f) {
        aShowHUDMessage(Message_strings[16]);
        aObjSetLightingDist(Object_handles[68], 0.000000f);
        aObjSetLightingDist(Object_handles[67], 0.000000f);
        aAISetState(0, Object_handles[68]);
        aAISetState(0, Object_handles[67]);
        aAISetState(1, Object_handles[72]);
        aAISetState(1, Object_handles[73]);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
        aSetObjectTimer(data->me_handle, 2.000000f, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 038: ToggleRepair-23
    if ((ScriptActionCtr_038 < 1) && (1)) {
      aUserVarInc(3);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18C3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: ToggleRepar-12
    if ((ScriptActionCtr_034 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(2) == 1.000000f))) {
      aShowHUDMessage(Message_strings[15]);
      aObjPlayAnim(Object_handles[62], 0, 1, 0.100000f, 0);
      aObjPlayAnim(Object_handles[69], 0, 1, 0.100000f, 0);
      aObjSetLightingDist(Object_handles[62], 40.000000f);
      aObjSetLightingDist(Object_handles[69], 40.000000f);
      aAISetState(1, Object_handles[62]);
      aAISetState(1, Object_handles[69]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 033: ToggleRepair-11
    if ((ScriptActionCtr_033 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      if (qUserVarValue(2) == 0.000000f) {
        aShowHUDMessage(Message_strings[16]);
        aObjSetLightingDist(Object_handles[62], 0.000000f);
        aObjSetLightingDist(Object_handles[69], 0.000000f);
        aAISetState(0, Object_handles[62]);
        aAISetState(0, Object_handles[69]);
        aAISetState(1, Object_handles[70]);
        aAISetState(1, Object_handles[71]);
        aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
        aSetObjectTimer(data->me_handle, 2.000000f, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 035: ToggleRepair-13
    if ((ScriptActionCtr_035 < 1) && (1)) {
      aUserVarInc(2);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0952::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: Repair Ship-4
    if ((ScriptActionCtr_045 < 1) &&
        (((ScriptActionCtr_037 > 0) == true) && (qObjIsPlayer(event_data->it_handle) == true) &&
         (qObjShields(event_data->it_handle) < 100.000000f) && (qObjExists(Object_handles[67]) == true))) {
      aObjSetLightingDist(Object_handles[67], 20.000000f);
      aObjSetShields(event_data->it_handle, 100.000000f);
      aObjPlayAnim(Object_handles[67], 0, 14, 5.000000f, 0);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);
      aCinematicSimple(Path_indexes[9], Message_strings[17], data->me_handle, 6.000000f, 1);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aLightningCreate(event_data->it_handle, data->me_handle, 6.000000f, 3.000000f, 1, Texture_indexes[0], 0.400000f,
                       1, 100, 255, 50, 0);
      aSoundPlaySteamingObj("VoxL12GeneralC.osf", event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0953::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Repair Ship-3
    if ((ScriptActionCtr_044 < 1) &&
        (((ScriptActionCtr_037 > 0) == true) && (qObjIsPlayer(event_data->it_handle) == true) &&
         (qObjShields(event_data->it_handle) < 100.000000f) && (qObjExists(Object_handles[68]) == true))) {
      aObjSetLightingDist(Object_handles[68], 20.000000f);
      aObjSetShields(event_data->it_handle, 100.000000f);
      aObjPlayAnim(Object_handles[68], 0, 14, 5.000000f, 0);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);
      aCinematicSimple(Path_indexes[10], Message_strings[17], data->me_handle, 6.000000f, 1);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aLightningCreate(event_data->it_handle, data->me_handle, 6.000000f, 3.000000f, 1, Texture_indexes[0], 0.400000f,
                       1, 100, 255, 50, 0);
      aSoundPlaySteamingObj("VoxL12GeneralC.osf", event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0950::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Repair Ship-2
    if ((ScriptActionCtr_043 < 1) &&
        (((ScriptActionCtr_034 > 0) == true) && (qObjIsPlayer(event_data->it_handle) == true) &&
         (qObjShields(event_data->it_handle) < 100.000000f) && (qObjExists(Object_handles[69]) == true))) {
      aObjSetLightingDist(Object_handles[69], 20.000000f);
      aObjSetShields(event_data->it_handle, 100.000000f);
      aObjPlayAnim(Object_handles[69], 0, 14, 5.000000f, 0);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);
      aCinematicSimple(Path_indexes[11], Message_strings[17], data->me_handle, 6.000000f, 1);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aLightningCreate(event_data->it_handle, data->me_handle, 6.000000f, 3.000000f, 1, Texture_indexes[0], 0.400000f,
                       1, 100, 255, 50, 0);
      aSoundPlaySteamingObj("VoxL12GeneralC.osf", event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0951::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Repair Ship-1
    if ((ScriptActionCtr_042 < 1) &&
        (((ScriptActionCtr_034 > 0) == true) && (qObjIsPlayer(event_data->it_handle) == true) &&
         (qObjShields(event_data->it_handle) < 100.000000f) && (qObjExists(Object_handles[62]) == true))) {
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aLightningCreate(event_data->it_handle, data->me_handle, 6.000000f, 3.000000f, 1, Texture_indexes[0], 0.400000f,
                       1, 100, 255, 50, 0);
      aObjSetLightingDist(Object_handles[62], 20.000000f);
      aObjSetShields(event_data->it_handle, 100.000000f);
      aObjPlayAnim(Object_handles[62], 0, 14, 5.000000f, 0);
      aSoundPlayObject(Sound_indexes[6], data->me_handle, 1.000000f);
      aSoundPlaySteamingObj("VoxL12GeneralC.osf", event_data->it_handle, 1.000000f);
      aCinematicSimple(Path_indexes[12], Message_strings[17], data->me_handle, 6.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_104E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: CowardFF-21
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(6) == 0.000000f)) {
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aSetObjectTimer(data->me_handle, 6.000000f, -1);
      aUserVarSet(6, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 049: CowardFF-22
    if (1) {
      if (((qUserVarValue(4) == 0.000000f) || (qUserVarValue(4) == 2.000000f)) && (qUserVarValue(6) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aSetObjectTimer(data->me_handle, 3.000000f, -1);
        aUserVarSet(6, 2.000000f);
      }
      if ((qUserVarValue(6) == 1.000000f) && (qUserVarValue(4) == 1.000000f)) {
        aPortalRenderSet(0, 0, Room_indexes[5], 1);
        aPortalRenderSet(0, 0, Room_indexes[6], 1);
        aShowHUDMessage(Message_strings[18]);
      }
      if (qUserVarValue(6) == 2.000000f) {
        aUserVarSet(6, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1969::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: CowardFF-11
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(4) == 0.000000f)) {
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aSetObjectTimer(data->me_handle, 6.000000f, -1);
      aUserVarSet(4, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 051: CowFF-INIT
    if (1) {
      aUserVarSet(4, 0.000000f);
      aUserVarSet(6, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 048: CowardFF-12
    if (1) {
      if (((qUserVarValue(6) == 0.000000f) || (qUserVarValue(6) == 2.000000f)) && (qUserVarValue(4) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 3, 6, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aSetObjectTimer(data->me_handle, 3.000000f, -1);
        aUserVarSet(4, 2.000000f);
      }
      if ((qUserVarValue(4) == 1.000000f) && (qUserVarValue(6) == 1.000000f)) {
        aPortalRenderSet(0, 0, Room_indexes[5], 1);
        aPortalRenderSet(0, 0, Room_indexes[6], 1);
        aShowHUDMessage(Message_strings[18]);
      }
      if (qUserVarValue(4) == 2.000000f) {
        aUserVarSet(4, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_216B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 052: CowPipe-INIT
    if (1) {
      aObjMakeInvuln(Object_handles[79], 999999);
      aObjMakeInvuln(Object_handles[80], 999999);
      aObjMakeInvuln(Object_handles[81], 999999);
      aObjMakeInvuln(Object_handles[82], 999999);
      aObjPlayAnim(Object_handles[83], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[84], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[85], 1, 3, 2.000000f, 1);
      aObjPlayAnim(Object_handles[78], 1, 3, 2.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 173: CowPipeHit 1
    if ((ScriptActionCtr_173 < 1) &&
        ((qObjExists(Object_handles[83]) == false) && (qObjExists(Object_handles[85]) == false) &&
         (qObjExists(Object_handles[84]) == false))) {
      aSetLevelTimer(0.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_173 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_173++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 172: CowPipeHit 2
    if ((ScriptActionCtr_172 < 1) &&
        ((qObjExists(Object_handles[78]) == false) && (qObjExists(Object_handles[83]) == false) &&
         (qObjExists(Object_handles[84]) == false))) {
      aSetLevelTimer(0.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_172 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_172++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 171: CowPipeHit 3
    if ((ScriptActionCtr_171 < 1) &&
        ((qObjExists(Object_handles[78]) == false) && (qObjExists(Object_handles[85]) == false) &&
         (qObjExists(Object_handles[83]) == false))) {
      aSetLevelTimer(0.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_171 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_171++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_096D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 060: CowPipeHit 4
    if ((ScriptActionCtr_060 < 1) &&
        ((qObjExists(Object_handles[78]) == false) && (qObjExists(Object_handles[85]) == false) &&
         (qObjExists(Object_handles[84]) == false))) {
      aSetLevelTimer(0.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0977::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 066: Gasser INIT
    if (1) {
      aUserVarSet(7, 0.000000f);
      aRoomSetFog(Room_indexes[8], 0.600000f, 0.700000f, 0.500000f, 1500.000000f);
      aRoomFogSetState(1, Room_indexes[8]);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 065: Gasser (Arena3)
    if (1) {
      if (qUserVarValue(7) == 1.000000f) {
        aRoomChangeFog(Room_indexes[8], 0.600000f, 0.700000f, 0.500000f, 200.000000f, 20.000000f);
      } else {
        aTurnOnSpew(data->me_handle, 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, 40.000000f, 4.000000f,
                    25.000000f, 0, -1);
        aRoomChangeFog(Room_indexes[8], 0.600000f, 0.700000f, 0.500000f, 450.000000f, 20.000000f);
        aUserVarSet(7, 1.000000f);
        aSetObjectTimer(data->me_handle, 20.000000f, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08E2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: RedSwitch
    if ((ScriptActionCtr_068 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjSetLightingDist(Object_handles[106], 30.000000f);
      aObjSetLightingDist(Object_handles[107], 30.000000f);
      aObjSetLightingDist(Object_handles[108], 30.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[20]);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 072: RedDummy-3 Hit
    if ((ScriptActionCtr_072 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_068 > 0) == true))) {
      aSetObjectTimer(data->me_handle, 5.000000f, -1);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aObjSetShields(data->me_handle, 5000.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 074: RedDummy-3 Explode
    if (1) {
      if (((ScriptActionCtr_073 > 0) == true) && ((ScriptActionCtr_070 > 0) == true)) {
      }
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: RedDummy-2 Hit
    if ((ScriptActionCtr_071 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_068 > 0) == true))) {
      aSetObjectTimer(data->me_handle, 5.000000f, -1);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aObjSetShields(data->me_handle, 5000.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 073: RedDummy-2 Explode
    if (1) {
      if (((ScriptActionCtr_074 > 0) == true) && ((ScriptActionCtr_070 > 0) == true)) {
      }
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: RedDummy-1 Hit
    if ((ScriptActionCtr_069 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_068 > 0) == true))) {
      aObjSetShields(data->me_handle, 5000.000000f);
      aSetObjectTimer(data->me_handle, 5.000000f, -1);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 070: RedDummy-1 Explode
    if (1) {
      if (((ScriptActionCtr_073 > 0) == true) && ((ScriptActionCtr_074 > 0) == true)) {
      }
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08E9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: SRSwitch-1
    if ((ScriptActionCtr_076 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(Object_handles[110], 0, 0, 1.000000f, 0);
      aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjSetLightingDist(Object_handles[110], 0.000000f);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      aShowHUDMessage(Message_strings[16]);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }

    // Script 079: SRSwitch-1 Second
    if ((ScriptActionCtr_079 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(8) == 1.000000f))) {
      aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjSetLightingDist(Object_handles[110], 40.000000f);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 075: SRepair-INIT
    if (1) {
      aUserVarSet(8, 0.000000f);
      aUserVarSet(9, 0.000000f);
      aObjSetLightingDist(Object_handles[110], 40.000000f);
      aObjSetLightingDist(Object_handles[111], 40.000000f);
      aObjPlayAnim(Object_handles[111], 0, 14, 5.000000f, 1);
      aObjPlayAnim(Object_handles[110], 0, 14, 5.000000f, 1);
      aObjHide(Object_handles[112]);
      aObjHide(Object_handles[19]);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 077: SRSwitch-1 Timer
    if (1) {
      aUserVarSet(8, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08E8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: SRSwitch-2
    if ((ScriptActionCtr_078 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(Object_handles[111], 0, 0, 1.000000f, 0);
      aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjSetLightingDist(Object_handles[111], 0.000000f);
      aSetObjectTimer(data->me_handle, 2.000000f, -1);
      aShowHUDMessage(Message_strings[16]);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }

    // Script 081: SRSwitch-2 Second
    if ((ScriptActionCtr_081 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserVarValue(9) == 1.000000f))) {
      aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjSetLightingDist(Object_handles[111], 40.000000f);
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 080: SRSwitch-2 Timer
    if (1) {
      aUserVarSet(9, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_105A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: SRCollide-2 Damage
    if ((ScriptActionCtr_085 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_078 > 0) == false) &&
         (qObjExists(Object_handles[111]) == true))) {
      aShowHUDMessage(Message_strings[21]);
      aMiscViewerShake(70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }

    // Script 084: SRCollide-2 Repair
    if ((ScriptActionCtr_084 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_081 > 0) == true) &&
         (qObjExists(Object_handles[111]) == true) && (qObjShields(event_data->it_handle) < 100.000000f))) {
      aLightningCreate(event_data->it_handle, data->me_handle, 6.000000f, 3.000000f, 1, Texture_indexes[0], 0.400000f,
                       1, 100, 255, 50, 0);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aObjSetShields(event_data->it_handle, 100.000000f);
      aSoundPlayObject(Sound_indexes[6], Object_handles[111], 1.000000f);
      aObjSetLightingDist(Object_handles[111], 20.000000f);
      aObjPlayAnim(Object_handles[111], 0, 14, 5.000000f, 0);
      aCinematicSimple(Path_indexes[13], Message_strings[17], data->me_handle, 6.000000f, 1);
      aSoundPlaySteamingObj("VoxL12GeneralC.osf", event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_097D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: SRCollide-1 Damage
    if ((ScriptActionCtr_082 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_076 > 0) == false) &&
         (qObjExists(Object_handles[110]) == true))) {
      aShowHUDMessage(Message_strings[21]);
      aMiscViewerShake(70.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }

    // Script 083: SRCollide-1 Repair
    if ((ScriptActionCtr_083 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && ((ScriptActionCtr_079 > 0) == true) &&
         (qObjExists(Object_handles[110]) == true) && (qObjShields(event_data->it_handle) < 100.000000f))) {
      aLightningCreate(event_data->it_handle, data->me_handle, 6.000000f, 3.000000f, 1, Texture_indexes[0], 0.400000f,
                       1, 100, 255, 50, 0);
      aObjSetVelocity(event_data->it_handle, 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aObjSetShields(event_data->it_handle, 100.000000f);
      aSoundPlayObject(Sound_indexes[6], Object_handles[110], 1.000000f);
      aObjSetLightingDist(Object_handles[110], 20.000000f);
      aObjPlayAnim(Object_handles[110], 0, 14, 5.000000f, 0);
      aCinematicSimple(Path_indexes[14], Message_strings[17], data->me_handle, 6.000000f, 1);
      aSoundPlaySteamingObj("VoxL12GeneralC.osf", event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1801::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 096: EndBossDestroyed
    if (1) {
      aSoundPlaySteaming("VoxL12EndLevel.osf", 1.000000f);
      aGoalCompleted(Goal_indexes[7], 1);
      aDoorLockUnlock(0, Door_handles[10]);
      aDoorLockUnlock(0, Door_handles[11]);
      aDoorLockUnlock(0, Door_handles[12]);
      aDoorLockUnlock(0, Door_handles[13]);
      aShowHUDMessage(Message_strings[27]);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 104: EBHostile
    if (1) {
      aSoundPlayObject(Sound_indexes[5], Object_handles[151], 1.000000f);
      aObjMakeVulnerable(Object_handles[27]);
      aAISetTeam(0, Object_handles[27]);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_103C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 011: Level1Paths
    if (1) {
      aAIFlags(1, 32800, Object_handles[117]);
      aAIFlags(1, 32800, Object_handles[118]);
      aAIFlags(1, 32800, Object_handles[119]);
      aAIFlags(1, 32800, Object_handles[120]);
      aAIFlags(1, 32800, Object_handles[121]);
      aAIFlags(1, 32800, Object_handles[122]);
      aAIFlags(1, 32800, Object_handles[123]);
      aAIFlags(1, 32800, Object_handles[21]);
      aAIGoalFollowPathSimple(Object_handles[21], Path_indexes[15], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[117], Path_indexes[16], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[118], Path_indexes[17], 20975872, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[119], Path_indexes[18], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[120], Path_indexes[15], 25170176, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[121], Path_indexes[16], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[122], Path_indexes[17], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[123], Path_indexes[18], 8392960, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0984::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 012: Level2Paths
    if (1) {
      aAIFlags(1, 32800, Object_handles[124]);
      aAIFlags(1, 32800, Object_handles[125]);
      aAIFlags(1, 32800, Object_handles[126]);
      aAIFlags(1, 32800, Object_handles[127]);
      aAIFlags(1, 32800, Object_handles[128]);
      aAIFlags(1, 32800, Object_handles[129]);
      aAIFlags(1, 32800, Object_handles[130]);
      aAIFlags(1, 32800, Object_handles[131]);
      aAIFlags(1, 32800, Object_handles[132]);
      aAIFlags(1, 32800, Object_handles[133]);
      aAIFlags(1, 32800, Object_handles[134]);
      aAIFlags(1, 32800, Object_handles[135]);
      aAIFlags(1, 32800, Object_handles[136]);
      aAIFlags(1, 32800, Object_handles[116]);
      aAIGoalFollowPathSimple(Object_handles[130], Path_indexes[19], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[127], Path_indexes[19], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[128], Path_indexes[20], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[129], Path_indexes[20], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[131], Path_indexes[20], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[132], Path_indexes[21], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[133], Path_indexes[22], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[124], Path_indexes[19], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[134], Path_indexes[19], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[135], Path_indexes[20], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[136], Path_indexes[21], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[125], Path_indexes[22], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[126], Path_indexes[22], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[116], Path_indexes[22], 8392960, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_098C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 113: Level3Paths
    if (1) {
      aAIFlags(1, 32800, Object_handles[115]);
      aAIFlags(1, 32800, Object_handles[144]);
      aAIFlags(1, 32800, Object_handles[145]);
      aAIFlags(1, 32800, Object_handles[146]);
      aAIFlags(1, 32800, Object_handles[147]);
      aAIFlags(1, 32800, Object_handles[148]);
      aAIGoalFollowPathSimple(Object_handles[148], Path_indexes[25], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[147], Path_indexes[25], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[115], Path_indexes[26], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[144], Path_indexes[26], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[145], Path_indexes[26], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[130], Path_indexes[27], 8392960, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_113 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_113++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0992::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 114: Level4Paths
    if (1) {
      aAIFlags(1, 32800, Object_handles[149]);
      aAIFlags(1, 32800, Object_handles[150]);
      aAIFlags(1, 32800, Object_handles[114]);
      aAIGoalFollowPathSimple(Object_handles[114], Path_indexes[28], 4198656, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[150], Path_indexes[28], 20975872, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[149], Path_indexes[29], 8392960, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_114 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_114++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20BC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 120: A1Waiter1
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_120 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_120++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 119: Arena Waiters INIT
    if (1) {
      aAIFlags(1, 131104, Object_handles[153]);
      aAIFlags(1, 131104, Object_handles[154]);
      aAIFlags(1, 131104, Object_handles[155]);
      aAIFlags(1, 131104, Object_handles[156]);
      aAIFlags(1, 131104, Object_handles[157]);
      aAIFlags(1, 131104, Object_handles[158]);
      aAISetTeam(196608, Object_handles[0]);
      aAISetTeam(196608, Object_handles[1]);
      aAISetTeam(196608, Object_handles[2]);
      aAISetTeam(196608, Object_handles[3]);
      aAISetTeam(196608, Object_handles[159]);
      aAISetTeam(196608, Object_handles[160]);
      aAISetTeam(196608, Object_handles[161]);
      aAISetTeam(196608, Object_handles[162]);
      aAISetTeam(196608, Object_handles[163]);
      aAISetTeam(196608, Object_handles[164]);
      aAISetTeam(196608, Object_handles[165]);
      aAISetTeam(196608, Object_handles[166]);
      aAISetTeam(196608, Object_handles[167]);
      aAISetTeam(196608, Object_handles[168]);
      aAISetTeam(196608, Object_handles[169]);
      aAISetTeam(196608, Object_handles[152]);
      aAISetTeam(196608, Object_handles[170]);

      // Increment the script action counter
      if (ScriptActionCtr_119 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_119++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 132: A3Waiter4
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_132 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_132++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 131: A3Waiter3
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_131 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_131++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 130: A3Waiter2
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_130 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_130++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11C5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 129: A3Waiter1
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_129 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_129++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11C4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 128: A2Waiter4
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_128 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_128++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21BC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 127: A2Waiter3
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_127 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_127++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11B5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 126: A2Waiter2
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_126 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_126++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2886::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 125: A2Waiter1
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_125 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_125++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11B4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 124: A1Waiter5
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_124 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_124++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1885::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 123: A1Waiter4
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_123 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_123++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_28BB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 122: A1Waiter3
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_122 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_122++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_186E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 121: A1Waiter2
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_121 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_121++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18F0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: AMWaiter-4
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 141: Arena Main Forcefield Open4
    if ((ScriptActionCtr_141 < 1) &&
        ((qObjExists(Object_handles[1]) == false) && (qObjExists(Object_handles[2]) == false) &&
         (qObjExists(Object_handles[3]) == false))) {
      aSetLevelTimer(0.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_141 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_141++;
    }

    // Script 137: Arena Main Guard Gone-4
    if ((ScriptActionCtr_137 < 1) && (1)) {
      aUserVarInc(11);
      if (qUserVarValue(11) == 1.000000f) {
        aShowHUDMessage(Message_strings[31]);
      } else {
        if (qUserVarValue(11) == 2.000000f) {
          aShowHUDMessage(Message_strings[32]);
        } else {
          if (qUserVarValue(11) == 3.000000f) {
            aShowHUDMessage(Message_strings[33]);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_137 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_137++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19BE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: AMWaiter-3
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 140: Arena Main Forcefield Open3
    if ((ScriptActionCtr_140 < 1) &&
        ((qObjExists(Object_handles[0]) == false) && (qObjExists(Object_handles[2]) == false) &&
         (qObjExists(Object_handles[3]) == false))) {
      aSetLevelTimer(0.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_140 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_140++;
    }

    // Script 136: Arena Main Guard Gone-3
    if ((ScriptActionCtr_136 < 1) && (1)) {
      aUserVarInc(11);
      if (qUserVarValue(11) == 1.000000f) {
        aShowHUDMessage(Message_strings[31]);
      } else {
        if (qUserVarValue(11) == 2.000000f) {
          aShowHUDMessage(Message_strings[32]);
        } else {
          if (qUserVarValue(11) == 3.000000f) {
            aShowHUDMessage(Message_strings[33]);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_136 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_136++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18F1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: AMWaiter-2
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 139: Arena Main Forcefield Open2
    if ((ScriptActionCtr_139 < 1) &&
        ((qObjExists(Object_handles[0]) == false) && (qObjExists(Object_handles[1]) == false) &&
         (qObjExists(Object_handles[3]) == false))) {
      aSetLevelTimer(0.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_139 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_139++;
    }

    // Script 135: Arena Main Guard Gone-2
    if ((ScriptActionCtr_135 < 1) && (1)) {
      aUserVarInc(11);
      if (qUserVarValue(11) == 1.000000f) {
        aShowHUDMessage(Message_strings[31]);
      } else {
        if (qUserVarValue(11) == 2.000000f) {
          aShowHUDMessage(Message_strings[32]);
        } else {
          if (qUserVarValue(11) == 3.000000f) {
            aShowHUDMessage(Message_strings[33]);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_135 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_135++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19C0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: AMWaiter-1
    if (qObjIsType(event_data->it_handle, 5) == true) {
      aAISetTeam(131072, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 138: Arena Main Forcefield Open
    if ((ScriptActionCtr_138 < 1) &&
        ((qObjExists(Object_handles[0]) == false) && (qObjExists(Object_handles[1]) == false) &&
         (qObjExists(Object_handles[2]) == false))) {
      aSetLevelTimer(0.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_138 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_138++;
    }

    // Script 134: Arena Main Guard Gone-1
    if ((ScriptActionCtr_134 < 1) && (1)) {
      aUserVarInc(11);
      if (qUserVarValue(11) == 1.000000f) {
        aShowHUDMessage(Message_strings[31]);
      } else {
        if (qUserVarValue(11) == 2.000000f) {
          aShowHUDMessage(Message_strings[32]);
        } else {
          if (qUserVarValue(11) == 3.000000f) {
            aShowHUDMessage(Message_strings[33]);
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_134 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_134++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18EE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 168: Secret Data Cartridge
    if ((ScriptActionCtr_168 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aAddGameMessage(Message_strings[34], Message_strings[35]);
      aMissionSetSecretFlag(1);
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_168 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_168++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20CD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Level 4 Key
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalEnableDisable(1, Goal_indexes[3]);
      aSoundPlayObject(Sound_indexes[8], event_data->it_handle, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 4, Message_strings[36], 0);
      aAddGameMessage(Message_strings[36], Message_strings[36]);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_28CC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Level 3 Key
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalEnableDisable(1, Goal_indexes[4]);
      aSoundPlayObject(Sound_indexes[8], event_data->it_handle, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 3, Message_strings[37], 0);
      aAddGameMessage(Message_strings[37], Message_strings[37]);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10B2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Level 2 Key
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalEnableDisable(1, Goal_indexes[5]);
      aSoundPlayObject(Sound_indexes[8], event_data->it_handle, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 2, Message_strings[38], 0);
      aAddGameMessage(Message_strings[38], Message_strings[38]);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18C1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Level 1 Key
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aGoalEnableDisable(1, Goal_indexes[6]);
      aSoundPlayObject(Sound_indexes[8], event_data->it_handle, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 1, Message_strings[39], 0);
      aAddGameMessage(Message_strings[39], Message_strings[39]);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21B8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 093: Arena Door 42
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_058 > 0) == false)) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[40], event_data->it_handle);
      } else {
        aShowHUDMessageObj(Message_strings[40], qObjParent(event_data->it_handle));
      }

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21B9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 092: Arena Door 41
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_058 > 0) == false)) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[40], event_data->it_handle);
      } else {
        aShowHUDMessageObj(Message_strings[40], qObjParent(event_data->it_handle));
      }

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Arena Door 3
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_057 > 0) == false)) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[41], event_data->it_handle);
      } else {
        aShowHUDMessageObj(Message_strings[41], qObjParent(event_data->it_handle));
      }

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_080C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Arena Door 2
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_056 > 0) == false)) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[42], event_data->it_handle);
      } else {
        aShowHUDMessageObj(Message_strings[42], qObjParent(event_data->it_handle));
      }

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0811::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Arena Door 1
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_055 > 0) == false)) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[43], event_data->it_handle);
      } else {
        aShowHUDMessageObj(Message_strings[43], qObjParent(event_data->it_handle));
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 152: Escaping Begin
    if ((ScriptActionCtr_152 < 1) && (1)) {
      aSoundPlaySteaming("VoxL12SpecificD.osf", 1.000000f);
      aSetWaypoint(10);
      aSetObjectTimer(Object_handles[20], 12.000000f, -1);
      aSetObjectTimer(Object_handles[21], 12.000000f, -1);
      aShowHUDMessage(Message_strings[5]);
      aMatcenSetState(1, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_152 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_152++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 153: Escaping End
    if ((ScriptActionCtr_153 < 1) && (1)) {
      aPortalRenderSet(1, 0, Room_indexes[1], 1);
      aSetWaypoint(11);

      // Increment the script action counter
      if (ScriptActionCtr_153 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_153++;
    }

    // Script 160: Music-Level 1 Main
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_160 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_160++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 094: Arena 4 PreEntrance
    if (1) {
      aSetWaypoint(7);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }

    // Script 164: Music-Level 4 Main
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_164 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_164++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 091: Arena 3 Entrance
    if ((ScriptActionCtr_091 < 1) && (1)) {
      aSetWaypoint(5);
      aDoorLockUnlock(1, Door_handles[1]);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }

    // Script 110: Arena 3 Special Enter
    if ((ScriptActionCtr_110 < 1) && (1)) {
      aAISetState(1, Object_handles[6]);
      aAISetTeam(196608, Object_handles[6]);
      aCinematicSimple(Path_indexes[4], Message_strings[10], Object_handles[6], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }

    // Script 067: A3Entrance Special
    if ((ScriptActionCtr_067 < 1) && (1)) {
      aSetObjectTimer(Object_handles[104], 0.500000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }

    // Script 157: Music-Level3Arena
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_157 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_157++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 090: Arena 2 Entrance
    if ((ScriptActionCtr_090 < 1) && (1)) {
      aSetWaypoint(4);
      aDoorLockUnlock(1, Door_handles[2]);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }

    // Script 108: Arena 2 Special Enter
    if ((ScriptActionCtr_108 < 1) && (1)) {
      aAISetState(1, Object_handles[7]);
      aAISetTeam(196608, Object_handles[7]);
      aCinematicSimple(Path_indexes[5], Message_strings[11], Object_handles[7], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }

    // Script 156: Music-Level2Arena
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_156 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_156++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Arena 1 Entrance
    if ((ScriptActionCtr_009 < 1) && (1)) {
      aSetWaypoint(1);
      aDoorLockUnlock(1, Door_handles[3]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 107: Arena 1 Special Enter
    if ((ScriptActionCtr_107 < 1) && (1)) {
      aAISetState(1, Object_handles[8]);
      aAISetTeam(196608, Object_handles[8]);
      aCinematicSimple(Path_indexes[6], Message_strings[12], Object_handles[8], 10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }

    // Script 155: Music-Level1Arena
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_155 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_155++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 117: Arena 42 Special Enter
    if ((ScriptActionCtr_117 < 1) && (1)) {
      aDoorLockUnlock(1, Door_handles[4]);
      aSetWaypoint(9);
      aAISetState(1, Object_handles[4]);
      aAISetTeam(196608, Object_handles[4]);
      if (qObjExists(Object_handles[5]) == true) {
        aCinematicSimple(Path_indexes[2], Message_strings[8], Object_handles[4], 10.000000f, 1);
      } else {
        aCinematicSimple(Path_indexes[2], Message_strings[9], Object_handles[4], 10.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_117 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_117++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 115: Arena 41 Special Enter
    if ((ScriptActionCtr_115 < 1) && (1)) {
      aDoorLockUnlock(1, Door_handles[5]);
      aSetWaypoint(8);
      aAISetState(1, Object_handles[5]);
      aAISetTeam(196608, Object_handles[5]);
      if (qObjExists(Object_handles[4]) == true) {
        aCinematicSimple(Path_indexes[3], Message_strings[8], Object_handles[5], 10.000000f, 1);
      } else {
        aCinematicSimple(Path_indexes[3], Message_strings[9], Object_handles[5], 10.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_115 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_115++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: ExitSequenceTest
    if (1) {
      aGoalCompleted(Goal_indexes[2], 1);
      aStartEndlevelSequencePath(Path_indexes[7], Path_indexes[8], 7.000000f, Message_strings[13]);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 098: L2Migration-2
    if ((ScriptActionCtr_098 < 1) && ((ScriptActionCtr_097 > 0) == false)) {
      aAIGoalFollowPathSimple(Object_handles[137], Path_indexes[23], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[138], Path_indexes[23], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[139], Path_indexes[23], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[140], Path_indexes[23], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_098 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_098++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 097: L2Migration-1
    if ((ScriptActionCtr_097 < 1) && ((ScriptActionCtr_098 > 0) == false)) {
      aAIGoalFollowPathSimple(Object_handles[137], Path_indexes[23], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[138], Path_indexes[23], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[139], Path_indexes[23], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[140], Path_indexes[23], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 099: L2Surprise
    if ((ScriptActionCtr_099 < 1) && (1)) {
      aAIGoalFollowPathSimple(Object_handles[141], Path_indexes[24], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[142], Path_indexes[24], 4352, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[143], Path_indexes[24], 4352, -1, 3);
      aSetObjectTimer(Object_handles[37], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 100: L2GenericRoomEnter
    if ((ScriptActionCtr_100 < 1) && (1)) {
      aSetObjectTimer(Object_handles[39], 5.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 133: MainGuardMessage-2
    if ((ScriptActionCtr_133 < 1) && ((ScriptActionCtr_095 > 0) == false)) {
      aDoorLockUnlock(1, Door_handles[4]);
      aDoorLockUnlock(1, Door_handles[5]);
      aShowHUDMessage(Message_strings[28]);

      // Increment the script action counter
      if (ScriptActionCtr_133 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_133++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 095: MainGuardMessage-1
    if ((ScriptActionCtr_095 < 1) && ((ScriptActionCtr_133 > 0) == false)) {
      aDoorLockUnlock(1, Door_handles[4]);
      aDoorLockUnlock(1, Door_handles[5]);
      aShowHUDMessage(Message_strings[28]);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 102: MainArenaEntrance
    if ((ScriptActionCtr_102 < 1) && ((ScriptActionCtr_142 > 0) == true)) {
      aSetWaypoint(12);
      aMusicSetRegion(8, event_data->it_handle);
      aCinematicSimple(Path_indexes[30], Message_strings[30], Object_handles[27], 15.000000f, 1);
      aPortalRenderSet(1, 0, Room_indexes[9], 1);
      aPortalRenderSet(1, 0, Room_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 167: Music-Repair-3
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_167 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_167++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 166: Music-Repair-2
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_166 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_166++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 165: Music-Repair-1
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_165 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_165++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 143: Music-Level 4 Main-3
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_143 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_143++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 103: Music-Level 4 Main-2
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 163: Music-Level 3 Main
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_163 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_163++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 162: Music-Level 2 Main-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_162 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_162++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 161: Music-Level 2 Main
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_161 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_161++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 145: Music-Level4Arena 4
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_145 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_145++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 144: Music-Level4Arena 3
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_144 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_144++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 159: Music-Level4Arena 2
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_159 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_159++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 158: Music-Level4Arena 1
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_158 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_158++;
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
NEXT_ID		174

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:Flicker1
1:Flicker2
2:RepairLeft
3:RepairRight
4:CowFF1
5:Flicker3
6:CowFF2
7:Gaseous
8:SRepair1
9:SRepair2
10:MainEXP
11:Guards
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:Flame1
1:Flame2
2:Flame3
3:Flame4
4:FlameMain
5:FlamersGone
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:FF1
1:FF2
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:EBCameraTimer
1:EBHostileTimer
2:EBFakeyTimer
3:A2Sacrifice1
4:A2Sacrfice2
5:A2Sacrfice3
6:IntroCamOver
7:MainGuardsGone
8:CowPipeDone
9:CowPipeCleaning
10:CowCleansingComplete
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:PlayerSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
Security Door
ArenaEntrance-3
ArenaEntrance-2
ArenaEntrance-1
Arena 42 Entrance
Arena 41 Entrance
ProducerDoor
ArenaExit-3
ArenaExit-2
ArenaExit-1
FinalExit-1
FinalExit-2
FinalExit-3
FinalExit-4
$$DOOR_LIST_END

$$OBJECT_LIST_START
AMWaiter-4
AMWaiter-3
AMWaiter-2
AMWaiter-1
ArenaBot4-2
ArenaBot4-1
ArenaBot-3
ArenaBot-2
ArenaBot 1
StartInvis
TrapPower-2
TrapPower-1
Flamer1
Flamer2
Flamer3
Flamer4
FlamerMain
BeginFFSpew1
BeginFFSpew2
SRCollide-2
MCSwitch 1
Level1Orbot1
MCSwitch 6
MCSwitch 5
MCSwitch 4
MCSwitch 3
MCSwitch 2
EndBoss
SmokeSpew-8
SmokeSpew-7
SmokeSpew-6
SmokeSpew-5
SmokeSpew-4
SmokeSpew-3
SmokeSpew-1
SmokeSpew-2
ForceFieldSwitch 1
Compactor-2
CompactedBot-2
Compactor-1
CompactedBot-1
Flick-Control-2
Flick-Control-12
Flick-Control-11
Bell42
Bell41
Bell3
Bell2
Bell1
RandomSwitch-3
RandomSpew-2
SingleSpew-1
SingleSpew-2
SingleSpew-3
SingleSpew-4
SingleSpew-5
RedSpewer
RandomSpew-1
ArenaSpew-1
ArenaSpew-4
ArenaSpew-3
ArenaSpew-2
Repair 1
RCollide-1
RCollide-2
RCollide-3
RCollide-4
Repair 4
Repair 3
Repair 2
RBot-1
RBot-2
RBot-3
RBot-4
ToggleRepair-2
ToggleRepair-1
CowFF-2
CowFF-1
CowPipe-1
FlameCleanser-4
FlameCleanser-3
FlameCleanser-2
FlameCleanser-1
CowPipe-4
CowPipe-3
CowPipe-2
CowH-4
CowH-5
CowT-4
CowT-5
CowT-3
CowB-4
CowB-1
CowB-3
CowB-2
CowH-1
CowH-3
CowH-2
CowT-2
CowT-1
CowS-1
CowS-2
CowS-3
CowS-4
A3Gasser
RedSwitch-1
RedDummy-1
RedDummy-2
RedDummy-3
SRSwitch-1
SRepair-1
SRepair-2
SRCollide-1
SRSwitch-2
Level4Thresher1
Level3Tailbot1
Level2Squid1
Level1Sparky4
Level1Sparky3
Level1Sparky2
Level1Sparky1
Level1Orbot4
Level1Orbot3
Level1Orbot2
Level2Squid41
Level2Squid12
Level2Squid11
Level2Sixgun41
Level2Sixgun32
Level2Sixgun31
Level2Sixgun4
Level2Sixgun3
Level2Sixgun2
Level2Sixgun1
Level2Squid4
Level2Squid3
Level2Squid2
L2Migrate4
L2Migrate3
L2Migrate2
L2Migrate1
L2Surprise1
L2Surprise2
L2Surprise3
Level3Tailbot2
Level3Tailbot3
Level3Tailbot4
Level3Tubbs1
Level3Tubbs2
Level4Thresher3
Level4Thresher2
BellMain
A1Waiter1
A4Waiter-6
A4Waiter-5
A4Waiter-4
A4Waiter3
A4Waiter2
A4Waiter1
A3Waiter4
A3Waiter3
A3Waiter2
A3Waiter1
A2Waiter4
A2Waiter3
A2Waiter2
A2Waiter1
A1Waiter2
A1Waiter4
A1Waiter3
A1Waiter5
Secret Data
Level4Key
Level3Key
Level2Key
Level1Key
Arena 42 Entrance
Arena 41 Entrance
ArenaEntrance-3
ArenaEntrance-2
ArenaEntrance-1
$$OBJECT_LIST_END

$$ROOM_LIST_START
FireRoom
EntryForceField
Flicker-2-1
Flicker-1-3
Flicker-1-1
Cow-1
Cow-2
EscapeCow
Arena3
Arena4-2
Arena4-1
MainEntrance
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EscapingBegin
EscapingEnd
Arena4Entrance
Arena3Entrance
Arena2Entrance
Arena1Entrance
Arena42Entrance
Arena41Entrance
ExitSequenceStart
L2Migrate2
L2Migrate1
L2Surprise1
SmashIt!
ChampCompetitors-2
ChampCompetitors-1
EndArenaManualFF
MRepair-3
MRepair-2
RepairEnter
MLevel4-3
MLevel4-2
MLevel3
MLevel2-2
MLevel2
MArena-2
MArena-1
Arena42Enter
Arena41Enter
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch11
AmbSwitch31
AmbFurn11
JugFootHit
AmbPlasma21
Bell
AmbSwitch21
AmbSirenIntense
PupC1
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffect5
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
Arena42
Arena41
Arena3
Arena2
Arena1
ExitCam
ExitSequence2
Repair4
Repair3
Repair2
Repair1
SRepair1
SRepair2
Level1Path1
Level1Path4
Level1Path3
Level1Path2
Level2Path4
Level2Path3
Level2Path2
Level2Path1
Level2Migrate1
Level2Surprise
Level3Path3
Level3Path1
Level3Path2
Level4Path1
Level4Path2
EndBoss
$$PATH_LIST_END

$$MATCEN_LIST_START
Matcen 8
Matcen 9
Matcen 6
Matcen 5
Matcen 4
Matcen 3
Matcen 2
Matcen 1
Matcen 7
$$MATCEN_LIST_END

$$GOAL_LIST_START
Escape from the firetrap
Disable the security forcefield
Escape from the Proving Grounds
Defeat Level 4 Arena
Defeat Level 3 Arena
Defeat Level 2 Arena
Defeat Level 1 Arena
Defeat the Proving Grounds Champion
Eliminate Championship Competitors
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL12StartLevel.osf
VoxL12SpecificD.osf
VoxL12GeneralC.osf
VoxL12SpecificA.osf
VoxL12SpecificB.osf
VoxL12EndLevel.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:101:ArenaBots SpecialFX (DISABLED)
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:1:Literal
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:6:20.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Beginning (Trapped)
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
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:90:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:90:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:90:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:4:90:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:4:90:Time
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:4:0:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.800000:BlobSize
                        10:6:19.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:4:0:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.800000:BlobSize
                        10:6:19.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.500000:Time
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:0:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:19:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:112:Disable Player After Death
        $$CHILD_BLOCK_START
        01:2:0
        02:30
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:63:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:62:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aPhysFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:58720256:PhysicsFlags
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aTogglePlayerObjControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:15:16447:PlayerControl
                        06:qObjSavedHandle:PlayerObject
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Disable Player
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qPlayerClosest:Object
                                $$CHILD_BLOCK_START
                                10:1:0:9:Object
                                10:10:0:-1:UserVar
                                $$CHILD_BLOCK_END
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aPhysFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:58720256:PhysicsFlags
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aTogglePlayerObjControl
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:15:16447:PlayerControl
                        06:qObjSavedHandle:PlayerObject
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:DisableControls (Start Fires, Etc)
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:23.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:6:10.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:6:15.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:149:Flamer-4
        $$CHILD_BLOCK_START
        01:1:15
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:60:Time
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:25.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.140000:BlobInterval
                                10:6:5.000000:SpewLife
                                10:6:3.500000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:5.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:3:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:148:Flamer-3
        $$CHILD_BLOCK_START
        01:1:14
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:60:Time
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:20.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.140000:BlobInterval
                                10:6:10.000000:SpewLife
                                10:6:3.500000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:10.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:3:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:147:Flamer-2
        $$CHILD_BLOCK_START
        01:1:13
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:60:Time
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:15.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.140000:BlobInterval
                                10:6:15.000000:SpewLife
                                10:6:3.500000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:15.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:3:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:146:Flamer-1
        $$CHILD_BLOCK_START
        01:1:12
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:60:Time
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:10.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.140000:BlobInterval
                                10:6:20.000000:SpewLife
                                10:6:3.500000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:20.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:3:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:150:Flamer-Main
        $$CHILD_BLOCK_START
        01:1:16
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:60:Time
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
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
                                08:aSetObjectTimer
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:6:10.000000:Time
                                        10:10:0:-1:TimerID
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
                                        10:4:3:StartFrame
                                        10:4:6:EndFrame
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aSetObjectTimer
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:6:25.000000:Time
                                        10:10:0:-1:TimerID
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:1:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:4:StartFrame
                                        10:4:6:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:12:Object
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:13:Object
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:14:Object
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qObjExists:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:15:Object
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjMakeVulnerable
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:0:StartFrame
                                        10:4:3:EndFrame
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:1:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:0:StartFrame
                                        10:4:2:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:3.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.130000:BlobInterval
                                10:6:5.000000:SpewLife
                                10:6:5.000000:BlobSize
                                10:6:55.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:5.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:2:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:151:FlameMain Destroyed
        $$CHILD_BLOCK_START
        01:1:16
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EscapedTorture:Message
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EscapeTorture2:Message
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:6:45.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:6:45.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Freedom!!! (2)
        $$CHILD_BLOCK_START
        01:1:10
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
                        10:4:1:PortalNum
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:11:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:1:Region
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EscapedDestroyed2:Message
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:58720256:PhysicsFlags
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aTogglePlayerObjAllControls
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                06:qObjSavedHandle:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EscapedDestroyed:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Freedom!!!
        $$CHILD_BLOCK_START
        01:1:11
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
                        10:2:0:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:10:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:1:Region
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EscapedDestroyed2:Message
                                $$CHILD_BLOCK_END
                        08:aPhysFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:58720256:PhysicsFlags
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aTogglePlayerObjAllControls
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                06:qObjSavedHandle:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EscapedDestroyed:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:152:Escaping Begin
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:10:Number
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:6:12.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:6:12.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LevelStarted:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:153:Escaping End
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:11:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Switch Enables Matcen (6)
        $$CHILD_BLOCK_START
        01:1:22
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivatedMatcen:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Switch Enables Matcen (5)
        $$CHILD_BLOCK_START
        01:1:23
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivatedMatcen:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:3:Matcen
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Switch Enables Matcen (4)
        $$CHILD_BLOCK_START
        01:1:24
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivatedMatcen:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Switch Enables Matcen (3)
        $$CHILD_BLOCK_START
        01:1:25
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivatedMatcen:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Switch Enables Matcen (2)
        $$CHILD_BLOCK_START
        01:1:26
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivatedMatcen:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Switch Enables Matcen (1)
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:4:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ActivatedMatcen:Message
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:7:Matcen
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Level Begin
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
                        10:10:0:11:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:16.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:0:PortalNum
                        10:2:1:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Security Forcefield Switch
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:8:Matcen
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
                        10:8:EmergencyOverride:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Compactor 2 Slamming
        $$CHILD_BLOCK_START
        01:1:37
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:5:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Compactor 1 Slamming
        $$CHILD_BLOCK_START
        01:1:39
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:5:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:FlickerForcefield-1 (3)
        $$CHILD_BLOCK_START
        01:1:41
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:FlickerForcefield-1 (2)
        $$CHILD_BLOCK_START
        01:1:42
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:3.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:FlickerForcefield-1 (1)
        $$CHILD_BLOCK_START
        01:1:43
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:4.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:FlickerForcefield-2 (3)
        $$CHILD_BLOCK_START
        01:1:41
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
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:3.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:0.800000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aPortalRenderToggle
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:FlickerForcefield-2 (2)
        $$CHILD_BLOCK_START
        01:1:42
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
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.500000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:0.750000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aPortalRenderToggle
                        $$CHILD_BLOCK_START
                        10:4:1:PortalNum
                        10:2:3:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:FlickerForcefield-2 (1)
        $$CHILD_BLOCK_START
        01:1:43
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
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:0.700000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aPortalRenderToggle
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:Arena 4 PreEntrance
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
                        10:4:7:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Arena 3 Entrance
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:5:Number
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Arena 2 Entrance
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Arena 1 Entrance
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:117:Arena 42 Special Enter
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:9:Number
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:5:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:2:CameraPath
                                10:8:Arena4Enter:Text
                                10:1:0:4:Target
                                10:6:10.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:2:CameraPath
                                10:8:Arena4Enter2:Text
                                10:1:0:4:Target
                                10:6:10.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:115:Arena 41 Special Enter
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:8:Number
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:5:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:4:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:3:CameraPath
                                10:8:Arena4Enter:Text
                                10:1:0:5:Target
                                10:6:10.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aCinematicSimple
                                $$CHILD_BLOCK_START
                                10:16:3:CameraPath
                                10:8:Arena4Enter2:Text
                                10:1:0:5:Target
                                10:6:10.000000:Seconds
                                10:5:1:FadeIn
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Arena 3 Special Enter
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:6:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:4:CameraPath
                        10:8:Arena3Enter:Text
                        10:1:0:6:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:Arena 2 Special Enter
        $$CHILD_BLOCK_START
        01:0:4
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:5:CameraPath
                        10:8:Arena2Enter:Text
                        10:1:0:7:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:Arena 1 Special Enter
        $$CHILD_BLOCK_START
        01:0:5
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:8:Arena1Enter:Text
                        10:1:0:8:Target
                        10:6:10.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:118:Arena 42 Special Timer
        $$CHILD_BLOCK_START
        01:1:4
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:44:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:116:Arena 41 Special Timer
        $$CHILD_BLOCK_START
        01:1:5
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:45:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:Arena 3 Special Timer
        $$CHILD_BLOCK_START
        01:1:6
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:46:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:Arena 2 Special Timer
        $$CHILD_BLOCK_START
        01:1:7
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:47:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:Arena 1 Special Timer
        $$CHILD_BLOCK_START
        01:1:8
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:48:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:ExitSequenceTest
        $$CHILD_BLOCK_START
        01:0:8
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:7:CameraPath
                        10:16:8:PlayerPath
                        10:6:7.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:RandomSwitch-3
        $$CHILD_BLOCK_START
        01:1:49
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
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DoorUnlocked:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:RandomRedExtraSpew
        $$CHILD_BLOCK_START
        01:1:50
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.010000:Drag
                        10:15:98304:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:ArenaSpewers
        $$CHILD_BLOCK_START
        01:1:58
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Repair INIT
        $$CHILD_BLOCK_START
        01:1:62
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:70:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:71:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:72:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:73:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:RBot Destruct...4
        $$CHILD_BLOCK_START
        01:1:73
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:RBot Destruct...3
        $$CHILD_BLOCK_START
        01:1:72
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:36:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:RBot Destruct...2
        $$CHILD_BLOCK_START
        01:1:71
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:33:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:RBot Destruct...1
        $$CHILD_BLOCK_START
        01:1:70
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:33:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:ToggleRepar-22
        $$CHILD_BLOCK_START
        01:1:74
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RepairActivated:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:0.100000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:0.100000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:68:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:67:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:ToggleRepar-12
        $$CHILD_BLOCK_START
        01:1:75
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RepairActivated:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:0.100000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:0.100000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:62:Object
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:0:69:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:ToggleRepair-21
        $$CHILD_BLOCK_START
        01:1:74
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
                                10:8:RepairDeactivated:Message
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:68:Object
                                10:6:0.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:67:Object
                                10:6:0.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:68:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:67:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:1:0:72:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:1:0:73:Object
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:ToggleRepair-11
        $$CHILD_BLOCK_START
        01:1:75
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RepairDeactivated:Message
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:62:Object
                                10:6:0.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingDist
                                $$CHILD_BLOCK_START
                                10:1:0:69:Object
                                10:6:0.000000:Distance
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:62:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:69:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:1:0:70:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:1:0:71:Object
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:2.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:ToggleRepair-23
        $$CHILD_BLOCK_START
        01:1:74
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:ToggleRepair-13
        $$CHILD_BLOCK_START
        01:1:75
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Repair Ship-4
        $$CHILD_BLOCK_START
        01:1:66
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:37:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:67:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:6:20.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:9:CameraPath
                        10:8:RepairingShip:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:2:-1:Object2
                        10:6:6.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:100:Red
                        10:4:255:Green
                        10:4:50:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Repair Ship-3
        $$CHILD_BLOCK_START
        01:1:65
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:37:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:68:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:6:20.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:10:CameraPath
                        10:8:RepairingShip:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:2:-1:Object2
                        10:6:6.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:100:Red
                        10:4:255:Green
                        10:4:50:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Repair Ship-2
        $$CHILD_BLOCK_START
        01:1:64
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:34:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:69:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:6:20.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:11:CameraPath
                        10:8:RepairingShip:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:2:-1:Object2
                        10:6:6.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:100:Red
                        10:4:255:Green
                        10:4:50:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Repair Ship-1
        $$CHILD_BLOCK_START
        01:1:63
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:34:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:62:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:2:-1:Object2
                        10:6:6.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:100:Red
                        10:4:255:Green
                        10:4:50:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:6:20.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:12:CameraPath
                        10:8:RepairingShip:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:CowardFF-21
        $$CHILD_BLOCK_START
        01:1:76
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:CowardFF-11
        $$CHILD_BLOCK_START
        01:1:77
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:6.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:CowardFF-22
        $$CHILD_BLOCK_START
        01:1:76
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
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:0.000000:Literal
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:3.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:2.000000:value
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
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:5:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CowFFDisable:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:CowardFF-12
        $$CHILD_BLOCK_START
        01:1:77
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
                                09:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:2.000000:Literal
                                                $$CHILD_BLOCK_END
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:3:StartFrame
                                10:4:6:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:3.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:2.000000:value
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
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:5:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:0:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CowFFDisable:Message
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:CowFF-INIT
        $$CHILD_BLOCK_START
        01:1:77
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:CowPipe-INIT
        $$CHILD_BLOCK_START
        01:1:78
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:85:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:4:1:StartFrame
                        10:4:3:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:170:CowPipe Actions
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.750000:Red
                        10:6:0.500000:Green
                        10:6:0.100000:Blue
                        10:6:1000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.750000:Red
                        10:6:0.500000:Green
                        10:6:0.100000:Blue
                        10:6:1000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:6:Room
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.750000:Red
                        10:6:0.500000:Green
                        10:6:0.100000:Blue
                        10:6:200.000000:Depth
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.750000:Red
                        10:6:0.500000:Green
                        10:6:0.100000:Blue
                        10:6:200.000000:Depth
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GonnaClean:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:79:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:80:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:81:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:82:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:CowPipe Burn
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:5.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:5.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:86:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:90:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:92:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:93:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:94:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:95:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:96:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:97:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:98:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:99:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:100:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:101:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:102:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalGotoRoom
                        $$CHILD_BLOCK_START
                        10:1:0:103:Object
                        10:2:7:Room
                        10:10:0:0:GoalPriority
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:86:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:87:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:88:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:90:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:93:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:94:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:92:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:95:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:96:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:97:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:98:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:99:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:100:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:101:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:102:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:103:Object
                        10:6:20.000000:Seconds
                        10:6:4.000000:Damage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Cow Cleansing Done
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:3:StartFrame
                        10:4:6:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:79:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:81:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:80:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:82:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.750000:Red
                        10:6:0.500000:Green
                        10:6:0.100000:Blue
                        10:6:1500.000000:Depth
                        10:6:15.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.750000:Red
                        10:6:0.500000:Green
                        10:6:0.100000:Blue
                        10:6:1500.000000:Depth
                        10:6:15.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:173:CowPipeHit 1
        $$CHILD_BLOCK_START
        01:1:78
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:83:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:85:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:84:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:172:CowPipeHit 2
        $$CHILD_BLOCK_START
        01:1:85
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:78:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:83:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:84:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:171:CowPipeHit 3
        $$CHILD_BLOCK_START
        01:1:84
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:78:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:85:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:83:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:CowPipeHit 4
        $$CHILD_BLOCK_START
        01:1:83
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:78:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:85:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:84:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Gasser (Arena3)
        $$CHILD_BLOCK_START
        01:1:104
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
                                        10:10:0:7:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.600000:Red
                                10:6:0.700000:Green
                                10:6:0.500000:Blue
                                10:6:200.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.400000:BlobLifetime
                                10:6:0.140000:BlobInterval
                                10:6:40.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:25.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aRoomChangeFog
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.600000:Red
                                10:6:0.700000:Green
                                10:6:0.500000:Blue
                                10:6:450.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:20.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Gasser INIT
        $$CHILD_BLOCK_START
        01:1:104
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.600000:Red
                        10:6:0.700000:Green
                        10:6:0.500000:Blue
                        10:6:1500.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:8:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:A3Entrance Special
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:104:Object
                        10:6:0.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:RedSwitch
        $$CHILD_BLOCK_START
        01:1:105
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
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:106:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:107:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:108:Object
                        10:6:30.000000:Distance
                        $$CHILD_BLOCK_END
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
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RedUnitsArmed:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:RedDummy-3 Hit
        $$CHILD_BLOCK_START
        01:1:108
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:68:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5000.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:RedDummy-2 Hit
        $$CHILD_BLOCK_START
        01:1:107
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:68:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5000.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:RedDummy-1 Hit
        $$CHILD_BLOCK_START
        01:1:106
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:68:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5000.000000:Shields
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:RedDummy-3 Explode
        $$CHILD_BLOCK_START
        01:1:108
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
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:73:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:70:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:RedDummy-2 Explode
        $$CHILD_BLOCK_START
        01:1:107
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
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:74:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:70:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:RedDummy-1 Explode
        $$CHILD_BLOCK_START
        01:1:106
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
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:73:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:74:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:SRepair-INIT
        $$CHILD_BLOCK_START
        01:1:109
        02:2
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
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:SRSwitch-2
        $$CHILD_BLOCK_START
        01:1:113
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:4:0:StartFrame
                        10:4:0:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
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
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RepairDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:SRSwitch-1
        $$CHILD_BLOCK_START
        01:1:109
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:4:0:StartFrame
                        10:4:0:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
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
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RepairDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:SRSwitch-2 Timer
        $$CHILD_BLOCK_START
        01:1:113
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:SRSwitch-1 Timer
        $$CHILD_BLOCK_START
        01:1:109
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:SRSwitch-2 Second
        $$CHILD_BLOCK_START
        01:1:113
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
        04:0:0:1
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
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RepairActivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:SRSwitch-1 Second
        $$CHILD_BLOCK_START
        01:1:109
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
        04:0:0:1
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
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:6:40.000000:Distance
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RepairActivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:SRCollide-2 Damage
        $$CHILD_BLOCK_START
        01:1:19
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
                                        10:11:78:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:111:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SRepairInit:Message
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:SRCollide-1 Damage
        $$CHILD_BLOCK_START
        01:1:112
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
                                        10:11:76:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:110:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SRepairInit:Message
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:SRCollide-2 Repair
        $$CHILD_BLOCK_START
        01:1:19
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
                                        10:11:81:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:111:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:2:-1:Object2
                        10:6:6.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:100:Red
                        10:4:255:Green
                        10:4:50:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:111:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:6:20.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:111:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:13:CameraPath
                        10:8:RepairingShip:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:SRCollide-1 Repair
        $$CHILD_BLOCK_START
        01:1:112
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
                                        10:11:79:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:110:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:100.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object1
                        10:1:2:-1:Object2
                        10:6:6.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.400000:SlideTime
                        10:4:1:TimesDrawn
                        10:4:100:Red
                        10:4:255:Green
                        10:4:50:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:110:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:6:20.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:110:Object
                        10:4:0:StartFrame
                        10:4:14:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:14:CameraPath
                        10:8:RepairingShip:Text
                        10:1:2:-1:Target
                        10:6:6.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Arena4-2 Bot
        $$CHILD_BLOCK_START
        01:1:4
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderToggle
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:5:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Arena4Defeated2:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:10:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:9:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Arena4Defeated:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Arena4-1 Bot
        $$CHILD_BLOCK_START
        01:1:5
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderToggle
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:4:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Arena4Defeated2:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:10:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:9:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Arena4Defeated:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Arena3 Bot
        $$CHILD_BLOCK_START
        01:1:6
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Arena3Defeated:Message
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Arena2 Bot
        $$CHILD_BLOCK_START
        01:1:7
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Arena2Defeated:Message
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Arena1 Bot
        $$CHILD_BLOCK_START
        01:1:8
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:9:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Arena1Defeated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:EndBossDestroyed
        $$CHILD_BLOCK_START
        01:1:27
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:5:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:10:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:11:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:12:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:13:DoorName
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ArenaChamp:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Level1Paths
        $$CHILD_BLOCK_START
        01:1:21
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:117:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:118:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:119:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:120:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:121:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:122:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:123:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:21:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:15:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:117:Object
                        10:16:16:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:118:Object
                        10:16:17:Path
                        10:15:20975872:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:119:Object
                        10:16:18:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:120:Object
                        10:16:15:Path
                        10:15:25170176:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:121:Object
                        10:16:16:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:122:Object
                        10:16:17:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:123:Object
                        10:16:18:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Level2Paths
        $$CHILD_BLOCK_START
        01:1:116
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:124:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:125:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:126:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:127:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:128:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:129:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:130:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:131:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:132:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:133:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:134:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:135:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:136:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:116:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:16:19:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:127:Object
                        10:16:19:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:128:Object
                        10:16:20:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:129:Object
                        10:16:20:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:131:Object
                        10:16:20:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:132:Object
                        10:16:21:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:133:Object
                        10:16:22:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:124:Object
                        10:16:19:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:134:Object
                        10:16:19:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:135:Object
                        10:16:20:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:136:Object
                        10:16:21:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:125:Object
                        10:16:22:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:126:Object
                        10:16:22:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:116:Object
                        10:16:22:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:98:L2Migration-2
        $$CHILD_BLOCK_START
        01:0:9
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:97:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:138:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:97:L2Migration-1
        $$CHILD_BLOCK_START
        01:0:10
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:98:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:137:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:138:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:16:23:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:L2Surprise
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:141:Object
                        10:16:24:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:142:Object
                        10:16:24:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object
                        10:16:24:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:L2GenericRoomEnter
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:113:Level3Paths
        $$CHILD_BLOCK_START
        01:1:115
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:115:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:144:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:145:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:146:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:147:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:148:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:148:Object
                        10:16:25:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:147:Object
                        10:16:25:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:115:Object
                        10:16:26:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:144:Object
                        10:16:26:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:145:Object
                        10:16:26:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:130:Object
                        10:16:27:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:114:Level4Paths
        $$CHILD_BLOCK_START
        01:1:114
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:149:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:150:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:32800:AIFlags
                        10:1:0:114:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:114:Object
                        10:16:28:Path
                        10:15:4198656:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object
                        10:16:28:Path
                        10:15:20975872:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object
                        10:16:29:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:133:MainGuardMessage-2
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:95:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainGuards:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:MainGuardMessage-1
        $$CHILD_BLOCK_START
        01:0:14
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:133:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:7
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainGuards:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:142:Main Guards Gone
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:8:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:4:PortalNum
                        10:2:11:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainFFDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:MainArenaEntrance
        $$CHILD_BLOCK_START
        01:0:15
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:142:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:12:Number
                        $$CHILD_BLOCK_END
                08:aMusicSetRegion
                        $$CHILD_BLOCK_START
                        10:10:0:8:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:30:CameraPath
                        10:8:EndBossBegin:Text
                        10:1:0:27:Target
                        10:6:15.000000:Seconds
                        10:5:1:FadeIn
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
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:EBHostile
        $$CHILD_BLOCK_START
        01:1:27
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:151:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:27:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:ArenaBotsINIT
        $$CHILD_BLOCK_START
        01:1:8
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:999999:Time
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:119:Arena Waiters INIT
        $$CHILD_BLOCK_START
        01:1:152
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
                        10:15:131104:AIFlags
                        10:1:0:153:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:154:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:155:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:156:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:157:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:158:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:159:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:160:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:161:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:162:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:163:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:164:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:165:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:166:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:167:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:168:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:169:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:152:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:170:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:132:A3Waiter4
        $$CHILD_BLOCK_START
        01:1:159
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:131:A3Waiter3
        $$CHILD_BLOCK_START
        01:1:160
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:130:A3Waiter2
        $$CHILD_BLOCK_START
        01:1:161
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:129:A3Waiter1
        $$CHILD_BLOCK_START
        01:1:162
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:128:A2Waiter4
        $$CHILD_BLOCK_START
        01:1:163
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:127:A2Waiter3
        $$CHILD_BLOCK_START
        01:1:164
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:126:A2Waiter2
        $$CHILD_BLOCK_START
        01:1:165
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:125:A2Waiter1
        $$CHILD_BLOCK_START
        01:1:166
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:124:A1Waiter5
        $$CHILD_BLOCK_START
        01:1:170
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:123:A1Waiter4
        $$CHILD_BLOCK_START
        01:1:168
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:122:A1Waiter3
        $$CHILD_BLOCK_START
        01:1:169
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:121:A1Waiter2
        $$CHILD_BLOCK_START
        01:1:167
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:120:A1Waiter1
        $$CHILD_BLOCK_START
        01:1:152
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:AMWaiter-4
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:AMWaiter-3
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:AMWaiter-2
        $$CHILD_BLOCK_START
        01:1:2
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:AMWaiter-1
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:131072:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:154:Music-Intro
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
00:167:Music-Repair-3
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:166:Music-Repair-2
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:165:Music-Repair-1
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:143:Music-Level 4 Main-3
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:Music-Level 4 Main-2
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:164:Music-Level 4 Main
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:163:Music-Level 3 Main
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:162:Music-Level 2 Main-2
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:161:Music-Level 2 Main
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:160:Music-Level 1 Main
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:145:Music-Level4Arena 4
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:144:Music-Level4Arena 3
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:159:Music-Level4Arena 2
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:158:Music-Level4Arena 1
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
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:157:Music-Level3Arena
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:156:Music-Level2Arena
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:155:Music-Level1Arena
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:141:Arena Main Forcefield Open4
        $$CHILD_BLOCK_START
        01:1:0
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:1:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:2:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:140:Arena Main Forcefield Open3
        $$CHILD_BLOCK_START
        01:1:1
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:0:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:2:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:139:Arena Main Forcefield Open2
        $$CHILD_BLOCK_START
        01:1:2
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:0:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:1:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:3:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:138:Arena Main Forcefield Open
        $$CHILD_BLOCK_START
        01:1:3
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:0:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:1:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:2:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:137:Arena Main Guard Gone-4
        $$CHILD_BLOCK_START
        01:1:0
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Guards1:Message
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
                                                10:10:0:11:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:Guards2:Message
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
                                                        10:10:0:11:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:Guards3:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:136:Arena Main Guard Gone-3
        $$CHILD_BLOCK_START
        01:1:1
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Guards1:Message
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
                                                10:10:0:11:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:Guards2:Message
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
                                                        10:10:0:11:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:Guards3:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:135:Arena Main Guard Gone-2
        $$CHILD_BLOCK_START
        01:1:2
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Guards1:Message
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
                                                10:10:0:11:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:Guards2:Message
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
                                                        10:10:0:11:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:Guards3:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:134:Arena Main Guard Gone-1
        $$CHILD_BLOCK_START
        01:1:3
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
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
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Guards1:Message
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
                                                10:10:0:11:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:Guards2:Message
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
                                                        10:10:0:11:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:Guards3:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:168:Secret Data Cartridge
        $$CHILD_BLOCK_START
        01:1:171
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:SecretData:GameMessage
                        10:8:RecoveredSecret:HUDMessage
                        $$CHILD_BLOCK_END
                08:aMissionSetSecretFlag
                        $$CHILD_BLOCK_START
                        10:5:1:State
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:169:Cowards Hostility
        $$CHILD_BLOCK_START
        01:1:8
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:99:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:98:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:97:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:96:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:95:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:94:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:93:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:92:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:91:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:90:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:88:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:89:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:87:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:86:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:100:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:101:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:102:Object
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:131104:AIFlags
                        10:1:0:103:Object
                        $$CHILD_BLOCK_END
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Level 4 Key
        $$CHILD_BLOCK_START
        01:1:172
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
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:4:KeyNum
                        10:8:Level4Key:KeyName
                        10:10:0:0:Yes/No
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:Level4Key:GameMessage
                        10:8:Level4Key:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Level 3 Key
        $$CHILD_BLOCK_START
        01:1:173
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
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:3:KeyNum
                        10:8:Level3Key:KeyName
                        10:10:0:0:Yes/No
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:Level3Key:GameMessage
                        10:8:Level3Key:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Level 2 Key
        $$CHILD_BLOCK_START
        01:1:174
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
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:5:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:2:KeyNum
                        10:8:Level2Key:KeyName
                        10:10:0:0:Yes/No
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:Level2Key:GameMessage
                        10:8:Level2Key:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Level 1 Key
        $$CHILD_BLOCK_START
        01:1:175
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
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:6:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:1:KeyNum
                        10:8:Level1Key:KeyName
                        10:10:0:0:Yes/No
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:Level1Key:GameMessage
                        10:8:Level1Key:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Arena Door 42
        $$CHILD_BLOCK_START
        01:1:176
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:58:ScriptID
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
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L4Door:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L4Door:Message
                                06:qObjParent:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:Arena Door 41
        $$CHILD_BLOCK_START
        01:1:177
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:58:ScriptID
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
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L4Door:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L4Door:Message
                                06:qObjParent:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Arena Door 3
        $$CHILD_BLOCK_START
        01:1:178
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
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
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L3Door:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L3Door:Message
                                06:qObjParent:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Arena Door 2
        $$CHILD_BLOCK_START
        01:1:179
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:56:ScriptID
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
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L2Door:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L2Door:Message
                                06:qObjParent:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Arena Door 1
        $$CHILD_BLOCK_START
        01:1:180
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:55:ScriptID
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
                                06:qObjIsPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L1Door:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:L1Door:Message
                                06:qObjParent:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
