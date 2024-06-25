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
// Filename:	level3.cpp
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
#define ID_CUSTOM_OBJECT_1AE9 0x002
#define ID_CUSTOM_OBJECT_206D 0x003
#define ID_CUSTOM_OBJECT_117F 0x004
#define ID_CUSTOM_OBJECT_184A 0x005
#define ID_CUSTOM_OBJECT_4049 0x006
#define ID_CUSTOM_OBJECT_0961 0x007
#define ID_CUSTOM_OBJECT_0960 0x008
#define ID_CUSTOM_OBJECT_095F 0x009
#define ID_CUSTOM_OBJECT_095E 0x00a
#define ID_CUSTOM_OBJECT_28D9 0x00b
#define ID_CUSTOM_OBJECT_38E0 0x00c
#define ID_CUSTOM_OBJECT_1995 0x00d
#define ID_CUSTOM_OBJECT_11CB 0x00e
#define ID_CUSTOM_OBJECT_20D7 0x00f
#define ID_CUSTOM_OBJECT_30D8 0x010
#define ID_CUSTOM_OBJECT_20DC 0x011
#define ID_CUSTOM_OBJECT_28DA 0x012
#define ID_CUSTOM_OBJECT_11B7 0x013
#define ID_CUSTOM_OBJECT_21A7 0x014
#define ID_CUSTOM_OBJECT_11C9 0x015
#define ID_CUSTOM_OBJECT_21CA 0x016
#define ID_CUSTOM_OBJECT_202B 0x017
#define ID_CUSTOM_OBJECT_18D6 0x018
#define ID_CUSTOM_OBJECT_202D 0x019
#define ID_CUSTOM_OBJECT_21CD 0x01a
#define ID_CUSTOM_OBJECT_182E 0x01b
#define ID_CUSTOM_OBJECT_31CC 0x01c
#define ID_CUSTOM_OBJECT_431E 0x01d
#define ID_CUSTOM_OBJECT_1320 0x01e
#define ID_CUSTOM_OBJECT_131F 0x01f
#define ID_CUSTOM_OBJECT_131D 0x020
#define ID_CUSTOM_OBJECT_100C 0x021
#define ID_CUSTOM_OBJECT_18AD 0x022

#define ID_TRIGGER_0003 0x023
#define ID_TRIGGER_0002 0x024
#define ID_TRIGGER_000A 0x025
#define ID_TRIGGER_0001 0x026
#define ID_TRIGGER_0000 0x027
#define ID_TRIGGER_000B 0x028
#define ID_TRIGGER_000E 0x029
#define ID_TRIGGER_000D 0x02a
#define ID_TRIGGER_000C 0x02b
#define ID_TRIGGER_0009 0x02c
#define ID_TRIGGER_0006 0x02d
#define ID_TRIGGER_0007 0x02e
#define ID_TRIGGER_0004 0x02f
#define ID_TRIGGER_0008 0x030
#define ID_TRIGGER_0019 0x031
#define ID_TRIGGER_0018 0x032
#define ID_TRIGGER_0017 0x033
#define ID_TRIGGER_0016 0x034
#define ID_TRIGGER_0014 0x035
#define ID_TRIGGER_0015 0x036
#define ID_TRIGGER_0005 0x037
#define ID_TRIGGER_0013 0x038
#define ID_TRIGGER_0022 0x039
#define ID_TRIGGER_0012 0x03a
#define ID_TRIGGER_0011 0x03b
#define ID_TRIGGER_001A 0x03c
#define ID_TRIGGER_001D 0x03d
#define ID_TRIGGER_001C 0x03e
#define ID_TRIGGER_001E 0x03f

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

class CustomObjectScript_1AE9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_206D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_117F : public BaseScript {
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

class CustomObjectScript_28D9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_38E0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1995 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11CB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20D7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_30D8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20DC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_28DA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11B7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21A7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11C9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21CA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_202B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18D6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_202D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21CD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_182E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_31CC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_431E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1320 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_131F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_131D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_100C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18AD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0001 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
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

class TriggerScript_0009 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0008 : public BaseScript {
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

class TriggerScript_0017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0013 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0022 : public BaseScript {
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

class TriggerScript_001A : public BaseScript {
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

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_016 = 0;
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
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_002 = 0;
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
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_096 = 0;
static int ScriptActionCtr_097 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_098 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_094 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_099 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_101 = 0;
static int ScriptActionCtr_100 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_103 = 0;
static int ScriptActionCtr_102 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_109 = 0;
static int ScriptActionCtr_104 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_108 = 0;
static int ScriptActionCtr_107 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_111 = 0;
static int ScriptActionCtr_092 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_095 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_105 = 0;
static int ScriptActionCtr_106 = 0;
static int ScriptActionCtr_110 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_016 = 0;
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
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_002 = 0;
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
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_096 = 0;
  ScriptActionCtr_097 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_098 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_094 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_099 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_101 = 0;
  ScriptActionCtr_100 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_103 = 0;
  ScriptActionCtr_102 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_109 = 0;
  ScriptActionCtr_104 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_108 = 0;
  ScriptActionCtr_107 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_111 = 0;
  ScriptActionCtr_092 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_095 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_105 = 0;
  ScriptActionCtr_106 = 0;
  ScriptActionCtr_110 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
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
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
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
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_096, file_ptr);
  File_WriteInt(ScriptActionCtr_097, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_098, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_094, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_099, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_101, file_ptr);
  File_WriteInt(ScriptActionCtr_100, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_103, file_ptr);
  File_WriteInt(ScriptActionCtr_102, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_109, file_ptr);
  File_WriteInt(ScriptActionCtr_104, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_108, file_ptr);
  File_WriteInt(ScriptActionCtr_107, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_111, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_095, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_105, file_ptr);
  File_WriteInt(ScriptActionCtr_106, file_ptr);
  File_WriteInt(ScriptActionCtr_110, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_096 = File_ReadInt(file_ptr);
  ScriptActionCtr_097 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_098 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_094 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_099 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_101 = File_ReadInt(file_ptr);
  ScriptActionCtr_100 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_103 = File_ReadInt(file_ptr);
  ScriptActionCtr_102 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_109 = File_ReadInt(file_ptr);
  ScriptActionCtr_104 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_108 = File_ReadInt(file_ptr);
  ScriptActionCtr_107 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_111 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_095 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_105 = File_ReadInt(file_ptr);
  ScriptActionCtr_106 = File_ReadInt(file_ptr);
  ScriptActionCtr_110 = File_ReadInt(file_ptr);
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

#define NUM_DOOR_NAMES 9
static const char *const Door_names[NUM_DOOR_NAMES] = {"RadioDoor",        "OctaDoorMainWest", "OctaDoorMainNorth",
                                                       "OctaDoorControl",  "OctaDoorTrans",    "OctaDoorMainSouth",
                                                       "OctaDoorMainEast", "OctaDoorStore",    "OctaDoorLab"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 55
static const char *const Object_names[NUM_OBJECT_NAMES] = {"ThiefCarrier",
                                                           "DataHolder",
                                                           "SuperThief",
                                                           "Final Cartridge",
                                                           "Original Cartridge",
                                                           "RescueShip1",
                                                           "RescueShip2",
                                                           "RescueShip3",
                                                           "MainKey",
                                                           "GoodieRoomSwitch",
                                                           "LT",
                                                           "LTdeadspew",
                                                           "FirstOutsideDoorSw",
                                                           "RadioDoorSwitch2",
                                                           "RadioCam",
                                                           "RadioDoorSwitch1",
                                                           "RadioToggle4",
                                                           "RadioToggle3",
                                                           "RadioToggle2",
                                                           "RadioToggle1",
                                                           "SBlackSmall",
                                                           "BottomSpewer",
                                                           "SWhite2",
                                                           "SWhite1",
                                                           "SWhiteGravity2",
                                                           "SWhiteGravity1",
                                                           "DTubbs1",
                                                           "OctaSwitchTrans",
                                                           "OctaSwitchLab-1",
                                                           "OctaSwitchLab-2",
                                                           "OctaSwitchStore-2",
                                                           "OctaSwitchStore-1",
                                                           "OctaSwitchControl",
                                                           "OctaSwitchMN",
                                                           "OctaSwitchME-2",
                                                           "OctaSwitchME-1",
                                                           "OctaSwitchMW",
                                                           "OctaSwitchMS-1",
                                                           "OctaSwitchMS-2",
                                                           "OctaDoorStore",
                                                           "DataTransfer-1",
                                                           "DataTransfer-2",
                                                           "DataTransferSwitch",
                                                           "UploadCamera",
                                                           "LTCbase1",
                                                           "LTCbase2",
                                                           "LTCbase3",
                                                           "LTCbase4",
                                                           "LTSkyCamera",
                                                           "LTCdiscaharge1",
                                                           "LTCdischarge2",
                                                           "LTCdischarge3",
                                                           "LTCdischarge4",
                                                           "KeyDoor",
                                                           "SecretRocks"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 7
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "GoodiePortalRoom", "ReturnInsideRoom", "FirstOutdoorPortal", "RadioRoom", "RadioArmory", "GlassDome", "RockBlock"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 29
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "Waypoint7",   "Waypoint6",     "Waypoint5",      "Waypoint4",      "Waypoint2",   "Waypoint1",
    "Voice10",     "Voice8",        "Voice7",         "Voice-Computer", "Voice5",      "Voice3",
    "Voice2",      "Voice1",        "Music-Ancient",  "Music-2Out2",    "Music-2Out1", "Music-Cave2",
    "Music-Cave1", "Music-2InPt22", "Music-2InPart2", "Music-2In2",     "Music-2In4",  "Music-1Out2",
    "Music-1In",   "Music-2InDat",  "ExitLab",        "EnterLab",       "UploadNode"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 7
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSwitch31", "PupC1",     "Cloak on", "Cloak off",
                                                         "AmbSwitch11", "Lightning", "HitEnergy"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 6
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"Reddataup",       "Ready1", "Notready",
                                                             "Staticscrolling", "Online", "FunkyEffect5"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 8
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCam", "IntroShip", "SuperIntro",  "Rescuer1",
                                                       "Rescuer2", "Rescuer3",  "EndLevelCam", "EndLevelShip"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 2
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"DatlinkMatcen", "ThiefDenMatcen"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 11
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Disable Access Forcefield",
                                                       "Get Security Key",
                                                       "Activate Datlink",
                                                       "Activate Data Upload",
                                                       "Reacquire the Data Cartridge",
                                                       "Place the Cartridge between Upload Nodes",
                                                       "Acquire the Data Cartridge",
                                                       "Find Sweitzer's Lab",
                                                       "Return to Surface",
                                                       "Retrieve the Data Cartridge",
                                                       "Destroy Lightning Control Tower"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 23
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroMessage",   "ForceFieldDeactivated",
                                                             "MainKeyCard",    "RadioRoomUnlock",
                                                             "RadioRoomFirst", "All4Radio",
                                                             "All4Radio2",     "ThiefGotIt",
                                                             "SuperIntro",     "KillSuper",
                                                             "DestroyedSuper", "FalseTransfer",
                                                             "Uploading",      "DestroyedThief",
                                                             "DataFinal",      "DataOriginal",
                                                             "PlaceCartridge", "DataNodes",
                                                             "TempGetData",    "EndLevel",
                                                             "LTSelfDestruct", "UploadNode",
                                                             "SecurityDoor"};
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
    strcpy(filename, "level3.msg");
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
  case ID_CUSTOM_OBJECT_2109:
    return new CustomObjectScript_2109;
    break;
  case ID_CUSTOM_OBJECT_1AE9:
    return new CustomObjectScript_1AE9;
    break;
  case ID_CUSTOM_OBJECT_206D:
    return new CustomObjectScript_206D;
    break;
  case ID_CUSTOM_OBJECT_117F:
    return new CustomObjectScript_117F;
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
  case ID_CUSTOM_OBJECT_28D9:
    return new CustomObjectScript_28D9;
    break;
  case ID_CUSTOM_OBJECT_38E0:
    return new CustomObjectScript_38E0;
    break;
  case ID_CUSTOM_OBJECT_1995:
    return new CustomObjectScript_1995;
    break;
  case ID_CUSTOM_OBJECT_11CB:
    return new CustomObjectScript_11CB;
    break;
  case ID_CUSTOM_OBJECT_20D7:
    return new CustomObjectScript_20D7;
    break;
  case ID_CUSTOM_OBJECT_30D8:
    return new CustomObjectScript_30D8;
    break;
  case ID_CUSTOM_OBJECT_20DC:
    return new CustomObjectScript_20DC;
    break;
  case ID_CUSTOM_OBJECT_28DA:
    return new CustomObjectScript_28DA;
    break;
  case ID_CUSTOM_OBJECT_11B7:
    return new CustomObjectScript_11B7;
    break;
  case ID_CUSTOM_OBJECT_21A7:
    return new CustomObjectScript_21A7;
    break;
  case ID_CUSTOM_OBJECT_11C9:
    return new CustomObjectScript_11C9;
    break;
  case ID_CUSTOM_OBJECT_21CA:
    return new CustomObjectScript_21CA;
    break;
  case ID_CUSTOM_OBJECT_202B:
    return new CustomObjectScript_202B;
    break;
  case ID_CUSTOM_OBJECT_18D6:
    return new CustomObjectScript_18D6;
    break;
  case ID_CUSTOM_OBJECT_202D:
    return new CustomObjectScript_202D;
    break;
  case ID_CUSTOM_OBJECT_21CD:
    return new CustomObjectScript_21CD;
    break;
  case ID_CUSTOM_OBJECT_182E:
    return new CustomObjectScript_182E;
    break;
  case ID_CUSTOM_OBJECT_31CC:
    return new CustomObjectScript_31CC;
    break;
  case ID_CUSTOM_OBJECT_431E:
    return new CustomObjectScript_431E;
    break;
  case ID_CUSTOM_OBJECT_1320:
    return new CustomObjectScript_1320;
    break;
  case ID_CUSTOM_OBJECT_131F:
    return new CustomObjectScript_131F;
    break;
  case ID_CUSTOM_OBJECT_131D:
    return new CustomObjectScript_131D;
    break;
  case ID_CUSTOM_OBJECT_100C:
    return new CustomObjectScript_100C;
    break;
  case ID_CUSTOM_OBJECT_18AD:
    return new CustomObjectScript_18AD;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
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
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
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
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0022:
    return new TriggerScript_0022;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
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
  case ID_CUSTOM_OBJECT_2109:
    delete ((CustomObjectScript_2109 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1AE9:
    delete ((CustomObjectScript_1AE9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_206D:
    delete ((CustomObjectScript_206D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_117F:
    delete ((CustomObjectScript_117F *)ptr);
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
  case ID_CUSTOM_OBJECT_28D9:
    delete ((CustomObjectScript_28D9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_38E0:
    delete ((CustomObjectScript_38E0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1995:
    delete ((CustomObjectScript_1995 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11CB:
    delete ((CustomObjectScript_11CB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20D7:
    delete ((CustomObjectScript_20D7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_30D8:
    delete ((CustomObjectScript_30D8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20DC:
    delete ((CustomObjectScript_20DC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_28DA:
    delete ((CustomObjectScript_28DA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11B7:
    delete ((CustomObjectScript_11B7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21A7:
    delete ((CustomObjectScript_21A7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11C9:
    delete ((CustomObjectScript_11C9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21CA:
    delete ((CustomObjectScript_21CA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_202B:
    delete ((CustomObjectScript_202B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18D6:
    delete ((CustomObjectScript_18D6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_202D:
    delete ((CustomObjectScript_202D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21CD:
    delete ((CustomObjectScript_21CD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_182E:
    delete ((CustomObjectScript_182E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_31CC:
    delete ((CustomObjectScript_31CC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_431E:
    delete ((CustomObjectScript_431E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1320:
    delete ((CustomObjectScript_1320 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_131F:
    delete ((CustomObjectScript_131F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_131D:
    delete ((CustomObjectScript_131D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_100C:
    delete ((CustomObjectScript_100C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18AD:
    delete ((CustomObjectScript_18AD *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
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
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
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
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0022:
    delete ((TriggerScript_0022 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
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
  case ID_CUSTOM_OBJECT_2109:
  case ID_CUSTOM_OBJECT_1AE9:
  case ID_CUSTOM_OBJECT_206D:
  case ID_CUSTOM_OBJECT_117F:
  case ID_CUSTOM_OBJECT_184A:
  case ID_CUSTOM_OBJECT_4049:
  case ID_CUSTOM_OBJECT_0961:
  case ID_CUSTOM_OBJECT_0960:
  case ID_CUSTOM_OBJECT_095F:
  case ID_CUSTOM_OBJECT_095E:
  case ID_CUSTOM_OBJECT_28D9:
  case ID_CUSTOM_OBJECT_38E0:
  case ID_CUSTOM_OBJECT_1995:
  case ID_CUSTOM_OBJECT_11CB:
  case ID_CUSTOM_OBJECT_20D7:
  case ID_CUSTOM_OBJECT_30D8:
  case ID_CUSTOM_OBJECT_20DC:
  case ID_CUSTOM_OBJECT_28DA:
  case ID_CUSTOM_OBJECT_11B7:
  case ID_CUSTOM_OBJECT_21A7:
  case ID_CUSTOM_OBJECT_11C9:
  case ID_CUSTOM_OBJECT_21CA:
  case ID_CUSTOM_OBJECT_202B:
  case ID_CUSTOM_OBJECT_18D6:
  case ID_CUSTOM_OBJECT_202D:
  case ID_CUSTOM_OBJECT_21CD:
  case ID_CUSTOM_OBJECT_182E:
  case ID_CUSTOM_OBJECT_31CC:
  case ID_CUSTOM_OBJECT_431E:
  case ID_CUSTOM_OBJECT_1320:
  case ID_CUSTOM_OBJECT_131F:
  case ID_CUSTOM_OBJECT_131D:
  case ID_CUSTOM_OBJECT_100C:
  case ID_CUSTOM_OBJECT_18AD:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0022:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_001C:
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
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0022;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_001E;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[34];
  static int cust_id_list[34] = {
      ID_CUSTOM_OBJECT_2109, ID_CUSTOM_OBJECT_1AE9, ID_CUSTOM_OBJECT_206D, ID_CUSTOM_OBJECT_117F, ID_CUSTOM_OBJECT_184A,
      ID_CUSTOM_OBJECT_4049, ID_CUSTOM_OBJECT_0961, ID_CUSTOM_OBJECT_0960, ID_CUSTOM_OBJECT_095F, ID_CUSTOM_OBJECT_095E,
      ID_CUSTOM_OBJECT_28D9, ID_CUSTOM_OBJECT_38E0, ID_CUSTOM_OBJECT_1995, ID_CUSTOM_OBJECT_11CB, ID_CUSTOM_OBJECT_20D7,
      ID_CUSTOM_OBJECT_30D8, ID_CUSTOM_OBJECT_20DC, ID_CUSTOM_OBJECT_28DA, ID_CUSTOM_OBJECT_11B7, ID_CUSTOM_OBJECT_21A7,
      ID_CUSTOM_OBJECT_11C9, ID_CUSTOM_OBJECT_21CA, ID_CUSTOM_OBJECT_202B, ID_CUSTOM_OBJECT_18D6, ID_CUSTOM_OBJECT_202D,
      ID_CUSTOM_OBJECT_21CD, ID_CUSTOM_OBJECT_182E, ID_CUSTOM_OBJECT_31CC, ID_CUSTOM_OBJECT_431E, ID_CUSTOM_OBJECT_1320,
      ID_CUSTOM_OBJECT_131F, ID_CUSTOM_OBJECT_131D, ID_CUSTOM_OBJECT_100C, ID_CUSTOM_OBJECT_18AD};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[9];
  cust_handle_list[1] = Object_handles[10];
  cust_handle_list[2] = Object_handles[12];
  cust_handle_list[3] = Object_handles[8];
  cust_handle_list[4] = Object_handles[13];
  cust_handle_list[5] = Object_handles[15];
  cust_handle_list[6] = Object_handles[16];
  cust_handle_list[7] = Object_handles[17];
  cust_handle_list[8] = Object_handles[18];
  cust_handle_list[9] = Object_handles[19];
  cust_handle_list[10] = Object_handles[36];
  cust_handle_list[11] = Object_handles[33];
  cust_handle_list[12] = Object_handles[32];
  cust_handle_list[13] = Object_handles[27];
  cust_handle_list[14] = Object_handles[38];
  cust_handle_list[15] = Object_handles[37];
  cust_handle_list[16] = Object_handles[34];
  cust_handle_list[17] = Object_handles[35];
  cust_handle_list[18] = Object_handles[30];
  cust_handle_list[19] = Object_handles[31];
  cust_handle_list[20] = Object_handles[29];
  cust_handle_list[21] = Object_handles[28];
  cust_handle_list[22] = Object_handles[0];
  cust_handle_list[23] = Object_handles[39];
  cust_handle_list[24] = Object_handles[2];
  cust_handle_list[25] = Object_handles[42];
  cust_handle_list[26] = Object_handles[3];
  cust_handle_list[27] = Object_handles[4];
  cust_handle_list[28] = Object_handles[44];
  cust_handle_list[29] = Object_handles[45];
  cust_handle_list[30] = Object_handles[46];
  cust_handle_list[31] = Object_handles[47];
  cust_handle_list[32] = Object_handles[53];
  cust_handle_list[33] = Object_handles[54];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 34;
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

    // Script 095: Returned to Outside
    if ((ScriptActionCtr_095 < 1) &&
        (((ScriptActionCtr_049 > 0) == true) && (qObjOnTerrain(qObjSavedHandle(17)) == true))) {
      aSetLevelTimer(0.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_095 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_095++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Level Start
    if (1 == true) {
      aAISetMaxSpeed(Object_handles[0], 0.000000f);
      aUserFlagSet(9, 0);
      aObjHide(Object_handles[1]);
      aObjGhostSet(1, Object_handles[2]);
      aObjGhostSet(1, Object_handles[3]);
      aObjGhostSet(1, Object_handles[4]);
      aMusicSetRegionAll(1);
      aUserVarSet(5, 0.000000f);
      aUserVarSet(6, 0.000000f);
      aObjGhostSet(1, Object_handles[5]);
      aObjGhostSet(1, Object_handles[6]);
      aObjGhostSet(1, Object_handles[7]);
      aSetLevelTimer(15.000000f, 1);
      aRainTurnOn(0.900000f);
      aLightningTurnOn(2.000000f, 0.100000f);
      aSoundPlaySteaming("VoxL03StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 071: IntroCam
    if (1 == true) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[8], Path_indexes[1], 15.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }

    // Script 002: Start Spewers!
    if (1) {
      aTurnOnSpew(Object_handles[20], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f, 2.400000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[21], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f, 3.000000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[22], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[23], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.140000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[24], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[25], 0, 7, 1.000000f, 0.010000f, 65664, 0, 1.400000f, 0.130000f, -1.000000f, 3.000000f,
                  20.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 098: DeadRobotStuff
    if (1) {
      aObjSetShields(Object_handles[26], 45.000000f);
      aTurnOnSpew(Object_handles[26], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, -1.000000f, 2.000000f,
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
      aGoalCompleted(Goal_indexes[2], 1);
      aRoomSetFaceTexture(Room_indexes[3], 42, Texture_indexes[4]);
      aPortalRenderSet(0, 0, Room_indexes[4], 1);
      aShowHUDMessage(Message_strings[5]);
      aShowHUDMessage(Message_strings[6]);
      aUserVarSet(4, 1.000000f);
      aSoundPlaySteaming("VoxDispatcher.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 027: Toggle INIT
    if (event_data->id == 1) {
      aUserVarSet(3, 0.000000f);
      aUserVarSet(2, 1.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(0, 0.000000f);
      aObjPlayAnim(Object_handles[16], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[19], 0, 1, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 072: SuperThief Intro Part I
    if (event_data->id == 10) {
      aCloakObject(Object_handles[2], 20.000000f);
      aObjGhostSet(0, Object_handles[2]);
      aObjSpark(Object_handles[2], 20.000000f, 5.000000f);
      aMoveObjectToPositionClipboard(Object_handles[2]);
      aTurnOnSpew(Object_handles[40], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.090000f, 8.000000f,
                  3.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[41], -1, 16, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.090000f, 8.000000f,
                  3.000000f, 30.000000f, 0, -1);
      aObjSpark(Object_handles[3], 50.000000f, 5.000000f);
      aCinematicSimple(Path_indexes[2], Message_strings[8], Object_handles[2], 17.500000f, 1);
      aSetLevelTimer(5.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }

    // Script 091: SuperThief Intro Part II
    if (event_data->id == 11) {
      aUnCloakObject(Object_handles[2]);
      aObjSpark(Object_handles[3], 100.000000f, 2.000000f);
      aSoundPlayObject(Sound_indexes[2], Object_handles[1], 1.000000f);
      aObjGhostSet(1, Object_handles[3]);
      aSetLevelTimer(2.000000f, 12);
      aObjSpark(Object_handles[2], 70.000000f, 2.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }

    // Script 047: SuperThief Intro Part III
    if (event_data->id == 12) {
      aObjSpark(Object_handles[3], 30.000000f, 2.000000f);
      aSoundPlayObject(Sound_indexes[3], Object_handles[1], 1.000000f);
      aObjSpark(Object_handles[2], 20.000000f, 4.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 005: EndLevelTest
    if ((ScriptActionCtr_005 < 1) && (event_data->id == 4)) {
      if ((ScriptActionCtr_020 > 0) == true) {
        aObjGhostSet(0, Object_handles[5]);
        aObjGhostSet(0, Object_handles[6]);
        aObjGhostSet(0, Object_handles[7]);
        aAIGoalFollowPathSimple(Object_handles[5], Path_indexes[3], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[6], Path_indexes[4], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[7], Path_indexes[5], 4352, -1, 3);
      } else {
      }
      aGoalCompleted(Goal_indexes[8], 1);
      aGoalCompleted(Goal_indexes[9], 1);
      aPortalBreakGlass(0, Room_indexes[5]);
      aPortalBreakGlass(1, Room_indexes[5]);
      aPortalBreakGlass(2, Room_indexes[5]);
      aPortalBreakGlass(3, Room_indexes[5]);
      aPortalBreakGlass(4, Room_indexes[5]);
      aPortalBreakGlass(5, Room_indexes[5]);
      aPortalBreakGlass(6, Room_indexes[5]);
      aPortalBreakGlass(7, Room_indexes[5]);
      aPortalBreakGlass(8, Room_indexes[5]);
      aPortalBreakGlass(9, Room_indexes[5]);
      aPortalBreakGlass(10, Room_indexes[5]);
      aPortalBreakGlass(11, Room_indexes[5]);
      aStartEndlevelSequencePath(Path_indexes[6], Path_indexes[7], 10.000000f, Message_strings[19]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 058: LT - Create Sky Lightning
    if (event_data->id == 7) {
      if (qObjExists(qObjSavedHandle(16)) == true) {
        aSoundPlayObject(Sound_indexes[5], Object_handles[10], 1.000000f);
        aLightningCreate(Object_handles[48], qObjSavedHandle(16), 0.600000f, 4.000000f, 5, Texture_indexes[5],
                         0.300000f, 3, 150, 200, 255, 0);
        aObjSpark(qObjSavedHandle(16), 100.000000f, 2.000000f);
        aObjSpark(qObjSavedHandle(9), 100.000000f, 2.000000f);
      }
      aSetLevelTimer(2.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }

    // Script 063: LT - Create Base Lighting
    if (event_data->id == 8) {
      if ((qObjExists(qObjSavedHandle(5)) == false) && (qObjExists(qObjSavedHandle(6)) == false) &&
          (qObjExists(qObjSavedHandle(7)) == false) && (qObjExists(qObjSavedHandle(8)) == false)) {
        aGoalCompleted(Goal_indexes[10], 1);
        aShowHUDMessage(Message_strings[20]);
        aObjSpark(Object_handles[10], 50.000000f, 20.000000f);
        aSetScriptedDeath(Object_handles[10], 1);
      } else {
        aSoundPlayObject(Sound_indexes[5], Object_handles[10], 1.000000f);
        aUserFlagSet(8, 1);
        if (qObjExists(qObjSavedHandle(5)) == true) {
          aObjSaveHandle(qPlayerClosest(qObjSavedHandle(1), 7), 14);
          aObjSaveHandle(qObjSavedHandle(1), 11);
          aObjSaveHandle(qObjSavedHandle(5), 13);
          aObjSaveHandle(Object_handles[49], 12);
          aUserFlagSet(8, 0);
        }
        if (qObjExists(qObjSavedHandle(6)) == true) {
          aObjSaveHandle(qPlayerClosest(qObjSavedHandle(2), 8), 10);
          if ((qUserFlag(8) == true) || (qUserVarValue(8) < qUserVarValue(7))) {
            aUserVarSet(7, qUserVarValue(8));
            aObjSaveHandle(qObjSavedHandle(10), 14);
            aObjSaveHandle(qObjSavedHandle(2), 11);
            aObjSaveHandle(qObjSavedHandle(6), 13);
            aObjSaveHandle(Object_handles[50], 12);
            aUserFlagSet(8, 0);
          }
        }
        if (qObjExists(qObjSavedHandle(7)) == true) {
          aObjSaveHandle(qPlayerClosest(qObjSavedHandle(3), 8), 10);
          if ((qUserFlag(8) == true) || (qUserVarValue(8) < qUserVarValue(7))) {
            aUserVarSet(7, qUserVarValue(8));
            aObjSaveHandle(qObjSavedHandle(10), 14);
            aObjSaveHandle(qObjSavedHandle(3), 11);
            aObjSaveHandle(qObjSavedHandle(7), 13);
            aObjSaveHandle(Object_handles[51], 12);
            aUserFlagSet(8, 0);
          }
        }
        if (qObjExists(qObjSavedHandle(8)) == true) {
          aObjSaveHandle(qPlayerClosest(qObjSavedHandle(4), 8), 10);
          if ((qUserFlag(8) == true) || (qUserVarValue(8) < qUserVarValue(7))) {
            aUserVarSet(7, qUserVarValue(8));
            aObjSaveHandle(qObjSavedHandle(10), 14);
            aObjSaveHandle(qObjSavedHandle(4), 11);
            aObjSaveHandle(qObjSavedHandle(8), 13);
            aObjSaveHandle(Object_handles[52], 12);
            aUserFlagSet(8, 0);
          }
        }
        aLightningCreate(qObjSavedHandle(9), qObjSavedHandle(11), 0.600000f, 4.000000f, 2, Texture_indexes[5],
                         0.300000f, 3, 150, 200, 255, 0);
        aObjSpark(qObjSavedHandle(11), 100.000000f, 2.000000f);
        aSetLevelTimer(2.000000f, 9);
      }

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }

    // Script 064: LT - Create Discharge Lightning
    if (event_data->id == 9) {
      if (qObjExists(qObjSavedHandle(13)) == true) {
        aSoundPlayObject(Sound_indexes[5], qObjSavedHandle(11), 1.000000f);
        aObjSaveHandle(qPlayerClosest(qObjSavedHandle(11), 7), 14);
        if ((qUserVarValue(7) < 200.000000f) && (qObjShields(qObjSavedHandle(14)) > 0.000000f)) {
          aSoundPlayObject(Sound_indexes[6], qObjSavedHandle(14), 1.000000f);
          aLightningCreate(qObjSavedHandle(11), qObjSavedHandle(14), 0.600000f, 4.000000f, 2, Texture_indexes[5],
                           0.300000f, 3, 150, 200, 255, 0);
          aObjSpark(qObjSavedHandle(14), 40.000000f, 2.000000f);
          aObjApplyDamage(qObjSavedHandle(14), 10.000000f);
        } else {
          aObjSpark(qObjSavedHandle(12), 40.000000f, 1.000000f);
          aLightningCreate(qObjSavedHandle(11), qObjSavedHandle(12), 0.600000f, 4.000000f, 2, Texture_indexes[5],
                           0.300000f, 3, 150, 200, 255, 0);
        }
      }
      aSetLevelTimer(qRandomValue(5.000000f, 10.000000f), 7);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 003: LabDoors Init
    if ((ScriptActionCtr_003 < 1) && (1)) {
      aObjPlayAnim(Object_handles[27], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[28], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[29], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[30], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[31], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[32], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[33], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[34], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[35], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[36], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[37], 0, 2, 1.000000f, 0);
      aObjPlayAnim(Object_handles[38], 0, 2, 1.000000f, 0);
      aUserFlagSet(0, 1);
      aUserFlagSet(1, 1);
      aUserFlagSet(2, 1);
      aUserFlagSet(3, 1);
      aUserFlagSet(4, 1);
      aUserFlagSet(5, 1);
      aUserFlagSet(6, 1);
      aUserFlagSet(7, 1);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
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
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
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

int16_t CustomObjectScript_1AE9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 069: Get LT's children
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[10], 0), 9);
      aObjSaveHandle(qGetAtachedChild(Object_handles[10], 1), 16);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 015: Second Outdoor FF Tower
    if ((ScriptActionCtr_015 < 1) && (1)) {
      aMusicSetRegionAll(3);
      aTurnOnSpew(Object_handles[11], 1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.130000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[11], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.130000f, -1.000000f, 3.000000f,
                  25.000000f, 0, -1);
      aTurnOnSpew(Object_handles[11], 0, 8, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.130000f, -1.000000f, 4.000000f,
                  20.000000f, 0, -1);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
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
      aGoalCompleted(Goal_indexes[0], 1);
      aSetLevelTimer(qRandomValue(10.000000f, 15.000000f), 7);
      aLightningTurnOn(0.300000f, 0.080000f);
      aRainTurnOn(0.900000f);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_117F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: KeyCard2
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjectPlayerGiveKey(event_data->it_handle, data->me_handle, 1, Message_strings[2], 0);
      aGoalCompleted(Goal_indexes[1], 1);
      aShowHUDMessage(Message_strings[2]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
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
    if ((ScriptActionCtr_009 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      if ((ScriptActionCtr_017 > 0) == true) {
        aMatcenSetState(1, Matcen_indexes[0]);
        aCreatePopupView(0, Object_handles[14], 8.000000f, 1.000000f);
        aShowHUDMessage(Message_strings[3]);
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[4]);
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
    if ((ScriptActionCtr_017 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      if ((ScriptActionCtr_009 > 0) == true) {
        aMatcenSetState(1, Matcen_indexes[0]);
        aCreatePopupView(0, Object_handles[14], 8.000000f, 1.000000f);
        aShowHUDMessage(Message_strings[3]);
        aDoorLockUnlock(0, Door_handles[0]);
        aDoorSetPos(Door_handles[0], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[4]);
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
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
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
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
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
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
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
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
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

int16_t CustomObjectScript_28D9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: OctaSwitchWestUN
    if ((qUserFlag(4) == true) && (qObjIsPlayerWeapon(event_data->it_handle) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[36], 1.000000f);
      aObjPlayAnim(Object_handles[36], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[1]);
      aUserFlagSet(4, 0);
      aSetObjectTimer(Object_handles[36], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 037: OctaSwitchWest
    if ((qUserFlag(4) == true) && (qObjIsPlayerWeapon(event_data->it_handle) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[36], 1.000000f);
      aObjPlayAnim(Object_handles[36], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[1]);
      aUserFlagSet(4, 0);
      aSetObjectTimer(Object_handles[36], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 088: OctaWest Timer
    if (1) {
      aUserFlagSet(4, 1);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_38E0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 093: OctaSwitchNorthUN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(5) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[33], 1.000000f);
      aObjPlayAnim(Object_handles[33], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[2]);
      aUserFlagSet(5, 0);
      aSetObjectTimer(Object_handles[33], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }

    // Script 036: OctaSwitchNorth
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(5) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[33], 1.000000f);
      aObjPlayAnim(Object_handles[33], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[2]);
      aUserFlagSet(5, 0);
      aSetObjectTimer(Object_handles[33], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 046: OctaNorth Timer
    if (1) {
      aUserFlagSet(5, 1);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1995::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 094: OctaSwitchControlUN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(3) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[32], 1.000000f);
      aObjPlayAnim(Object_handles[32], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[3]);
      aUserFlagSet(3, 0);
      aSetObjectTimer(Object_handles[32], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_094 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_094++;
    }

    // Script 035: OctaSwitchControl
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(3) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[32], 1.000000f);
      aObjPlayAnim(Object_handles[32], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[3]);
      aUserFlagSet(3, 0);
      aSetObjectTimer(Object_handles[32], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 045: OctaControl Timer
    if (1) {
      aUserFlagSet(3, 1);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11CB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 099: OctaSwitchTransUN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(2) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[27], 1.000000f);
      aObjPlayAnim(Object_handles[27], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[4]);
      aUserFlagSet(2, 0);
      aSetObjectTimer(Object_handles[27], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_099 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_099++;
    }

    // Script 034: OctaSwitchTrans
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(2) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[27], 1.000000f);
      aObjPlayAnim(Object_handles[27], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[4]);
      aUserFlagSet(2, 0);
      aSetObjectTimer(Object_handles[27], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 044: OctaTrans Timer
    if (1) {
      aUserFlagSet(2, 1);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20D7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: OctaSwitchSouth-2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[37], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[38], 1.000000f);
      aObjPlayAnim(Object_handles[37], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[38], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[5]);
      aUserFlagSet(7, 0);
      aSetObjectTimer(Object_handles[37], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 101: OctaSwitchSouth-2UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[37], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[38], 1.000000f);
      aObjPlayAnim(Object_handles[37], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[38], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[5]);
      aUserFlagSet(7, 0);
      aSetObjectTimer(Object_handles[37], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_101 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_101++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_30D8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 100: OctaSwitchSouth-1UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[37], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[38], 1.000000f);
      aObjPlayAnim(Object_handles[37], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[38], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[5]);
      aUserFlagSet(7, 0);
      aSetObjectTimer(Object_handles[37], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_100 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_100++;
    }

    // Script 040: OctaSwitchSouth-1
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[37], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[38], 1.000000f);
      aObjPlayAnim(Object_handles[37], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[38], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[5]);
      aUserFlagSet(7, 0);
      aSetObjectTimer(Object_handles[37], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 043: OctaSouth Timer
    if (1) {
      aUserFlagSet(7, 1);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20DC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: OctaSwitchEast-2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[35], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[34], 1.000000f);
      aObjPlayAnim(Object_handles[35], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[34], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[6]);
      aUserFlagSet(6, 0);
      aSetObjectTimer(Object_handles[35], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }

    // Script 103: OctaSwitchEast-2UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[35], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[34], 1.000000f);
      aObjPlayAnim(Object_handles[35], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[34], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[6]);
      aUserFlagSet(6, 0);
      aSetObjectTimer(Object_handles[35], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_103 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_103++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_28DA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 102: OctaSwitchEast-1UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[35], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[34], 1.000000f);
      aObjPlayAnim(Object_handles[35], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[34], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[6]);
      aUserFlagSet(6, 0);
      aSetObjectTimer(Object_handles[35], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_102 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_102++;
    }

    // Script 038: OctaSwitchEast-1
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[35], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[34], 1.000000f);
      aObjPlayAnim(Object_handles[35], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[34], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[6]);
      aUserFlagSet(6, 0);
      aSetObjectTimer(Object_handles[35], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 042: OctaEast Timer
    if (1) {
      aUserFlagSet(6, 1);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11B7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: OctaSwitchStore-2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[31], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[30], 1.000000f);
      aObjPlayAnim(Object_handles[31], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[30], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[7]);
      aUserFlagSet(0, 0);
      aSetObjectTimer(Object_handles[31], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }

    // Script 109: OctaSwitchStore-2UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[31], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[30], 1.000000f);
      aObjPlayAnim(Object_handles[31], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[30], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[7]);
      aUserFlagSet(0, 0);
      aSetObjectTimer(Object_handles[31], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_109 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_109++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21A7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 104: OctaSwitchStore-1UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[31], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[30], 1.000000f);
      aObjPlayAnim(Object_handles[31], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[30], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[7]);
      aUserFlagSet(0, 0);
      aSetObjectTimer(Object_handles[31], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_104 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_104++;
    }

    // Script 006: OctaSwitchStore-1
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[31], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[30], 1.000000f);
      aObjPlayAnim(Object_handles[31], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[30], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[7]);
      aUserFlagSet(0, 0);
      aSetObjectTimer(Object_handles[31], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 014: OctaStore Timer
    if (1) {
      aUserFlagSet(0, 1);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11C9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: OctaSwitchLab-2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(1) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[28], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[29], 1.000000f);
      aObjPlayAnim(Object_handles[28], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[29], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[8]);
      aUserFlagSet(1, 0);
      aSetObjectTimer(Object_handles[28], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 108: OctaSwitchLab-2UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(1) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[28], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[29], 1.000000f);
      aObjPlayAnim(Object_handles[28], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[29], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[8]);
      aUserFlagSet(1, 0);
      aSetObjectTimer(Object_handles[28], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_108 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_108++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21CA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 107: OctaSwitchLab-1UN
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(1) == true) &&
        (qObjAnimFrame(data->me_handle) == 1.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[28], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[29], 1.000000f);
      aObjPlayAnim(Object_handles[28], 1, 2, 2.000000f, 0);
      aObjPlayAnim(Object_handles[29], 1, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[8]);
      aUserFlagSet(1, 0);
      aSetObjectTimer(Object_handles[28], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_107 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_107++;
    }

    // Script 041: OctaSwitchLab-1
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(1) == true) &&
        (qObjAnimFrame(data->me_handle) == 2.000000f)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[28], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[29], 1.000000f);
      aObjPlayAnim(Object_handles[28], 0, 1, 2.000000f, 0);
      aObjPlayAnim(Object_handles[29], 0, 1, 2.000000f, 0);
      aDoorLockUnlock(1, Door_handles[8]);
      aUserFlagSet(1, 0);
      aSetObjectTimer(Object_handles[28], 2.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 033: OctaLab Timer
    if (1) {
      aUserFlagSet(1, 1);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_202B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 111: OctaStore (First Time) (THIEF BACKUP)
    if ((ScriptActionCtr_111 < 1) &&
        (((ScriptActionCtr_092 > 0) == false) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true))) {
      aShowHUDMessage(Message_strings[7]);
      aAISetMaxSpeed(Object_handles[0], 55.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_111 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_111++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 061: ThiefDestroyed
    if (1) {
      aShowHUDMessage(Message_strings[13]);
      aStoreObjectInPositionClipboard(data->me_handle);
      aMoveObjectToPositionClipboard(Object_handles[4]);
      aObjGhostSet(0, Object_handles[4]);
      aMatcenSetState(1, Matcen_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18D6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 092: OctaStore (First Time)
    if ((ScriptActionCtr_092 < 1) &&
        ((qDoorLocked(data->me_handle) == false) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) &&
         ((ScriptActionCtr_111 > 0) == false))) {
      aShowHUDMessage(Message_strings[7]);
      aAISetMaxSpeed(Object_handles[0], 55.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_202D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 087: SuperThiefDestroyed
    if (1) {
      aShowHUDMessage(Message_strings[10]);
      aStoreObjectInPositionClipboard(data->me_handle);
      aMoveObjectToPositionClipboard(Object_handles[3]);
      aObjGhostSet(0, Object_handles[3]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 089: ThiefIntro Done
    if ((ScriptActionCtr_089 < 1) && (1)) {
      aSoundPlaySteaming("VoxL03SpecificD.osf", 1.000000f);
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21CD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 090: False Data Transfer
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(9) == false)) {
      aShowHUDMessage(Message_strings[11]);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }

    // Script 060: Get Data Into cartridge
    if ((ScriptActionCtr_060 < 1) && ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(9) == true))) {
      aGoalCompleted(Goal_indexes[3], 1);
      aGoalEnableDisable(1, Goal_indexes[4]);
      aShowHUDMessage(Message_strings[12]);
      aSetLevelTimer(3.000000f, 10);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_182E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: Collect Data Final
    if ((ScriptActionCtr_049 < 1) && ((qObjIsPlayer(event_data->it_handle) == true) &&
                                      (qObjExists(Object_handles[2]) == false) && (qUserFlag(9) == true))) {
      aGoalCompleted(Goal_indexes[4], 1);
      aShowHUDMessage(Message_strings[14]);
      aSoundPlaySteamingObj("VoxL03EndLevel.osf", event_data->it_handle, 1.000000f);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjSaveHandle(event_data->it_handle, 17);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 062: Final Cartridge Don't Use
    if (1) {
      aObjGhostSet(0, data->me_handle);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_31CC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Collect Data
    if ((ScriptActionCtr_028 < 1) && ((qObjIsPlayer(event_data->it_handle) == true) &&
                                      (qObjExists(Object_handles[0]) == false) && (qUserFlag(9) == false))) {
      aSoundPlaySteamingObj("VoxL03SpecificC.osf", event_data->it_handle, 1.000000f);
      aCreatePopupView(0, Object_handles[43], 7.000000f, 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[3]);
      aGoalEnableDisable(1, Goal_indexes[5]);
      aGoalCompleted(Goal_indexes[6], 1);
      aShowHUDMessage(Message_strings[15]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 048: Original Cartridge Use
    if (1) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[3]) < 30.000000f) {
        aGoalCompleted(Goal_indexes[5], 1);
        aShowHUDMessage(Message_strings[16]);
        aUserFlagSet(9, 1);
        aStoreObjectInPositionClipboard(Object_handles[3]);
        aObjGhostSet(0, Object_handles[3]);
      } else {
        aShowHUDMessage(Message_strings[17]);
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_431E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 065: Get LTCbase1's children
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[44], 0), 5);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(5), 0), 15);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(15), 1), 1);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1320::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 066: Get LTCbase2's children
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[45], 0), 6);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(6), 0), 15);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(15), 1), 2);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_131F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 067: Get LTCbase3's children
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[46], 0), 7);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(7), 0), 15);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(15), 1), 3);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_131D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 068: Get LTCbase4's children
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[47], 0), 8);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(8), 0), 15);
      aObjSaveHandle(qGetAtachedChild(qObjSavedHandle(15), 1), 4);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_100C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 106: SecurityDoor
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_016 > 0) == false)) {
      if (qObjIsPlayer(event_data->it_handle) == true) {
        aShowHUDMessageObj(Message_strings[22], event_data->it_handle);
      } else {
        aShowHUDMessageObj(Message_strings[22], qObjParent(event_data->it_handle));
      }

      // Increment the script action counter
      if (ScriptActionCtr_106 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_106++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18AD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 110: Rocks Blew Up
    if ((ScriptActionCtr_110 < 1) && (1)) {
      aPortalBlockageSet(0, 1, Room_indexes[6]);

      // Increment the script action counter
      if (ScriptActionCtr_110 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_110++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
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
      aMusicSetRegion(8, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
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
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
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

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
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

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
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

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Voice Trigger 10
    if ((ScriptActionCtr_059 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompIntruderB.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Voice Trigger 8
    if ((ScriptActionCtr_057 < 1) && (1)) {

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Voice Trigger 7
    if ((ScriptActionCtr_056 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompPowerDamage.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Voice Computer
    if ((ScriptActionCtr_055 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompComDatalink.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Voice Trigger 5
    if ((ScriptActionCtr_054 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompIrreguler.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 096: Music-Datlink
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_096 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_096++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Voice Trigger 3
    if ((ScriptActionCtr_052 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompEmergencyA.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Voice Trigger 2
    if ((ScriptActionCtr_051 < 1) && (1)) {
      aSoundPlaySteaming("VoxCompSecurityLockdown.osf", 0.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: Voice Trigger 1
    if ((ScriptActionCtr_050 < 1) && (1)) {

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Music-Ancient2
    if (1) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Music-2Out2
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: Music-2Out
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Music-Cave2
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Music-Cave
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

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

    // Script 079: Music-2InPt22
    if (1) {
      aMusicSetRegion(10, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: Music-2InPt2
    if (1) {
      aMusicSetRegion(10, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Music-2In2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0022::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Music-2In1
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

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 075: Music-1Out2
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

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: Music-1In
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 097: Music-2InDat
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_097 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_097++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Music-3OutPt2
    if (1) {
      aMusicSetRegion(8, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Music-Alien
    if (1) {
      aMusicSetRegion(9, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 029: EnterLab
    if ((ScriptActionCtr_029 < 1) && (1)) {
      aSoundPlaySteaming("VoxL03SpecificB.osf", 1.000000f);
      aGoalCompleted(Goal_indexes[7], 1);
      aSetWaypoint(8);
      aShowHUDMessage(Message_strings[18]);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 105: Upload Node Description
    if ((ScriptActionCtr_105 < 1) && (1)) {
      aShowHUDMessage(Message_strings[21]);

      // Increment the script action counter
      if (ScriptActionCtr_105 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_105++;
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
NEXT_ID		112

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:RadioToggle1
1:RadioToggle2
2:RadioToggle3
3:RadioToggle4
4:RadioAll
5:Bunks
6:BlewItUp
7:LTTargetDist
8:LTTempDist
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:OctaStore
1:OctaLab
2:OctaTrans
3:OctaControl
4:OctaWest
5:OctaNorth
6:OctaEast
7:OctaSouth
8:LTFirstCheck
9:CartridgePlaced
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
7:LTCreateSkyLightning
8:LTCreateBaseLightning
9:LTCreateDischargeLightning
10:SuperThiefIntro
11:SuperThiefIntro2
12:SuperThiefIntro3
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:NewThief
1:LTBaseBall1
2:LTBaseBall2
3:LTBaseBall3
4:LTBaseBall4
5:LTBaseMid1
6:LTBaseMid2
7:LTBaseMid3
8:LTBaseMid4
9:LTNode
10:LTPlayerTemp
11:LTBallTarget
12:LTDishchargeTarget
13:LTMidTarget
14:LTPlayerTarget
15:LTTempObject
16:LTBall
17:PlayerWithCart
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
RadioDoor
OctaDoorMainWest
OctaDoorMainNorth
OctaDoorControl
OctaDoorTrans
OctaDoorMainSouth
OctaDoorMainEast
OctaDoorStore
OctaDoorLab
$$DOOR_LIST_END

$$OBJECT_LIST_START
ThiefCarrier
DataHolder
SuperThief
Final Cartridge
Original Cartridge
RescueShip1
RescueShip2
RescueShip3
MainKey
GoodieRoomSwitch
LT
LTdeadspew
FirstOutsideDoorSw
RadioDoorSwitch2
RadioCam
RadioDoorSwitch1
RadioToggle4
RadioToggle3
RadioToggle2
RadioToggle1
SBlackSmall
BottomSpewer
SWhite2
SWhite1
SWhiteGravity2
SWhiteGravity1
DTubbs1
OctaSwitchTrans
OctaSwitchLab-1
OctaSwitchLab-2
OctaSwitchStore-2
OctaSwitchStore-1
OctaSwitchControl
OctaSwitchMN
OctaSwitchME-2
OctaSwitchME-1
OctaSwitchMW
OctaSwitchMS-1
OctaSwitchMS-2
OctaDoorStore
DataTransfer-1
DataTransfer-2
DataTransferSwitch
UploadCamera
LTCbase1
LTCbase2
LTCbase3
LTCbase4
LTSkyCamera
LTCdiscaharge1
LTCdischarge2
LTCdischarge3
LTCdischarge4
KeyDoor
SecretRocks
$$OBJECT_LIST_END

$$ROOM_LIST_START
GoodiePortalRoom
ReturnInsideRoom
FirstOutdoorPortal
RadioRoom
RadioArmory
GlassDome
RockBlock
$$ROOM_LIST_END

$$TRIGGER_LIST_START
Waypoint7
Waypoint6
Waypoint5
Waypoint4
Waypoint2
Waypoint1
Voice10
Voice8
Voice7
Voice-Computer
Voice5
Voice3
Voice2
Voice1
Music-Ancient
Music-2Out2
Music-2Out1
Music-Cave2
Music-Cave1
Music-2InPt22
Music-2InPart2
Music-2In2
Music-2In4
Music-1Out2
Music-1In
Music-2InDat
ExitLab
EnterLab
UploadNode
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch31
PupC1
Cloak on
Cloak off
AmbSwitch11
Lightning
HitEnergy
$$SOUND_LIST_END

$$TEXTURE_LIST_START
Reddataup
Ready1
Notready
Staticscrolling
Online
FunkyEffect5
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCam
IntroShip
SuperIntro
Rescuer1
Rescuer2
Rescuer3
EndLevelCam
EndLevelShip
$$PATH_LIST_END

$$MATCEN_LIST_START
DatlinkMatcen
ThiefDenMatcen
$$MATCEN_LIST_END

$$GOAL_LIST_START
Disable Access Forcefield
Get Security Key
Activate Datlink
Activate Data Upload
Reacquire the Data Cartridge
Place the Cartridge between Upload Nodes
Acquire the Data Cartridge
Find Sweitzer's Lab
Return to Surface
Retrieve the Data Cartridge
Destroy Lightning Control Tower
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL03StartLevel.osf
VoxDispatcher.osf
VoxCompIntruderB.osf
VoxCompPowerDamage.osf
VoxCompComDatalink.osf
VoxCompIrreguler.osf
VoxCompEmergencyA.osf
VoxCompSecurityLockdown.osf
VoxL03SpecificD.osf
VoxL03EndLevel.osf
VoxL03SpecificC.osf
VoxL03SpecificB.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
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
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:0.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjHide
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:1:TimerID
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
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
                        10:1:0:8:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Goodie Switch hit
        $$CHILD_BLOCK_START
        01:1:9
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
                        10:12:0:Sound
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
00:15:Second Outdoor FF Tower
        $$CHILD_BLOCK_START
        01:1:10
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.130000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
00:4:First Outdoor ForceField Switch
        $$CHILD_BLOCK_START
        01:1:12
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:15.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
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
                        10:12:0:Sound
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
                        10:2:2:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForceFieldDeactivated:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Waypoint7
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
                        10:4:7:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Waypoint6
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
                        10:4:6:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Waypoint5
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
                        10:4:5:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Waypoint4
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
                        10:4:4:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Waypoint2
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
                        10:4:2:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Waypoint1
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
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:KeyCard2
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
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:2:-1:KeyObject
                        10:4:1:KeyNum
                        10:8:MainKeyCard:KeyName
                        10:10:0:0:Yes/No
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MainKeyCard:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:RadioDoorLock2
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
                        10:12:0:Sound
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
                                10:1:0:14:Object
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
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
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
        04:0:0:1
                $$CHILD_BLOCK_START
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
                        10:12:0:Sound
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
                                10:1:0:14:Object
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
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
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
        01:1:16
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
                        10:12:0:Sound
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
        01:1:17
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
                        10:12:0:Sound
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
        01:1:18
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
                        10:12:0:Sound
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
        01:1:19
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
                        10:12:0:Sound
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
        01:1:17
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
        01:1:18
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
        01:1:19
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
                        10:18:0:2:LevelGoal
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
                        10:9:0.500000:Volume
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
                        10:1:0:16:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Voice Trigger 10
        $$CHILD_BLOCK_START
        01:0:6
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Voice Trigger 8
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Voice Trigger 7
        $$CHILD_BLOCK_START
        01:0:8
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
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Voice Computer
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
                        10:19:4:Sound
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Voice Trigger 5
        $$CHILD_BLOCK_START
        01:0:10
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
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Voice Trigger 3
        $$CHILD_BLOCK_START
        01:0:11
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
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Voice Trigger 2
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
                        10:19:7:Sound
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Voice Trigger 1
        $$CHILD_BLOCK_START
        01:0:13
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:DO NOTHING
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
                        10:1:0:20:Object
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
                        10:1:0:21:Object
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
                        10:1:0:22:Object
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
                        10:1:0:23:Object
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
                        10:1:0:24:Object
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
                        10:1:0:25:Object
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Music-3Out
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
                        10:10:0:8:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Music-Ancient2
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Music-Ancient1
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
                        10:10:0:7:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Music-2Out2
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Music-2Out
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
00:81:Music-Cave2
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
00:80:Music-Cave
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
00:79:Music-2InPt22
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
                        10:10:0:10:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Music-2InPt2
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
                        10:10:0:10:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Music-2In2
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Music-2In1
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
00:75:Music-1Out2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Music-1In
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:96:Music-Datlink
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
00:97:Music-2InDat
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
00:70:Music-3OutPt2
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
                        10:10:0:8:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Music-Alien
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
                        10:10:0:9:Region
                        10:1:1:-1:PlayerObject
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
                        10:1:0:26:Object
                        10:6:45.000000:Shields
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:LabDoors Init
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:1:True/False
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
                        10:10:0:6:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:OctaSwitchWestUN
        $$CHILD_BLOCK_START
        01:1:36
        02:0
        03:0
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
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:36:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:OctaSwitchWest
        $$CHILD_BLOCK_START
        01:1:36
        02:0
        03:0
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
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:36:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:OctaSwitchNorthUN
        $$CHILD_BLOCK_START
        01:1:33
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:33:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:OctaSwitchNorth
        $$CHILD_BLOCK_START
        01:1:33
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:33:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:2:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:94:OctaSwitchControlUN
        $$CHILD_BLOCK_START
        01:1:32
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:32:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:OctaSwitchControl
        $$CHILD_BLOCK_START
        01:1:32
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:32:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:3:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:99:OctaSwitchTransUN
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:27:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:OctaSwitchTrans
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:27:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:4:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:OctaSwitchSouth-2
        $$CHILD_BLOCK_START
        01:1:38
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:37:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:38:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:101:OctaSwitchSouth-2UN
        $$CHILD_BLOCK_START
        01:1:38
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:37:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:38:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:100:OctaSwitchSouth-1UN
        $$CHILD_BLOCK_START
        01:1:37
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:37:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:38:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:OctaSwitchSouth-1
        $$CHILD_BLOCK_START
        01:1:37
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:37:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:38:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:38:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:5:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:OctaSwitchEast-2
        $$CHILD_BLOCK_START
        01:1:34
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:35:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:34:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:103:OctaSwitchEast-2UN
        $$CHILD_BLOCK_START
        01:1:34
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:35:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:34:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:102:OctaSwitchEast-1UN
        $$CHILD_BLOCK_START
        01:1:35
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:35:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:34:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:OctaSwitchEast-1
        $$CHILD_BLOCK_START
        01:1:35
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:35:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:34:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:6:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:OctaSwitchStore-2
        $$CHILD_BLOCK_START
        01:1:30
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:31:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:30:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:109:OctaSwitchStore-2UN
        $$CHILD_BLOCK_START
        01:1:30
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:31:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:30:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:104:OctaSwitchStore-1UN
        $$CHILD_BLOCK_START
        01:1:31
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:31:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:30:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:OctaSwitchStore-1
        $$CHILD_BLOCK_START
        01:1:31
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:31:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:30:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:OctaSwitchLab-2
        $$CHILD_BLOCK_START
        01:1:29
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:28:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:29:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:108:OctaSwitchLab-2UN
        $$CHILD_BLOCK_START
        01:1:29
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:28:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:29:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:107:OctaSwitchLab-1UN
        $$CHILD_BLOCK_START
        01:1:28
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
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
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:28:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:29:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:OctaSwitchLab-1
        $$CHILD_BLOCK_START
        01:1:28
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:28:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:29:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:8:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:OctaWest Timer
        $$CHILD_BLOCK_START
        01:1:36
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:OctaNorth Timer
        $$CHILD_BLOCK_START
        01:1:33
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:OctaControl Timer
        $$CHILD_BLOCK_START
        01:1:32
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:OctaTrans Timer
        $$CHILD_BLOCK_START
        01:1:27
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:OctaSouth Timer
        $$CHILD_BLOCK_START
        01:1:37
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:OctaEast Timer
        $$CHILD_BLOCK_START
        01:1:35
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:111:OctaStore (First Time) (THIEF BACKUP)
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:92:ScriptID
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ThiefGotIt:Message
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:55.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:OctaStore (First Time)
        $$CHILD_BLOCK_START
        01:1:39
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qDoorLocked:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:2:-1:Door
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:111:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ThiefGotIt:Message
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:55.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:OctaStore Timer
        $$CHILD_BLOCK_START
        01:1:31
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:OctaLab Timer
        $$CHILD_BLOCK_START
        01:1:28
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:SuperThief Intro Part I
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
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:20.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:20.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:4:-1:GunNum
                        10:10:0:16:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:50.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:SuperIntro:Text
                        10:1:0:2:Target
                        10:6:17.500000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:SuperThief Intro Part II
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
                08:aUnCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:100.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:70.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:SuperThief Intro Part III
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:30.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:20.000000:SparkRate
                        10:6:4.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:ThiefIntro Done
        $$CHILD_BLOCK_START
        01:1:2
        02:18
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:KillSuper:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:SuperThiefDestroyed
        $$CHILD_BLOCK_START
        01:1:2
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedSuper:Message
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:False Data Transfer
        $$CHILD_BLOCK_START
        01:1:42
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FalseTransfer:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Get Data Into cartridge
        $$CHILD_BLOCK_START
        01:1:42
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
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Uploading:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:10:TimerID
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
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:ThiefDestroyed
        $$CHILD_BLOCK_START
        01:1:0
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DestroyedThief:Message
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Collect Data Final
        $$CHILD_BLOCK_START
        01:1:3
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
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:2:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserFlag
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DataFinal:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:9:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:17:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:95:Returned to Outside
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
                                        10:11:49:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjOnTerrain:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:17:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Final Cartridge Don't Use
        $$CHILD_BLOCK_START
        01:1:3
        02:25
        03:0
                $$CHILD_BLOCK_START
                05:0
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Collect Data
        $$CHILD_BLOCK_START
        01:1:4
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
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:0:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteamingObj
                        $$CHILD_BLOCK_START
                        10:19:10:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:43:Object
                        10:6:7.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:5:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DataOriginal:Message
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Original Cartridge Use
        $$CHILD_BLOCK_START
        01:1:4
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
                                        10:1:0:3:Object2
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:30.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:5:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:PlaceCartridge:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aStoreObjectInPositionClipboard
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:3:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:DataNodes:Message
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
        $$CHILD_BLOCK_END
00:29:EnterLab
        $$CHILD_BLOCK_START
        01:0:27
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:8:Number
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TempGetData:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:EndLevelTest
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
                                10:1:0:5:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:6:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:7:Object
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:16:3:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:16:4:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:16:5:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:8:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:9:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:1:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:2:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:3:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:4:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:5:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:6:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:7:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:8:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:9:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:10:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aPortalBreakGlass
                        $$CHILD_BLOCK_START
                        10:4:11:PortalNum
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:16:7:PlayerPath
                        10:6:10.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Get LT's children
        $$CHILD_BLOCK_START
        01:1:10
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:9:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:16:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Get LTCbase1's children
        $$CHILD_BLOCK_START
        01:1:44
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:44:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:5:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:15:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Get LTCbase2's children
        $$CHILD_BLOCK_START
        01:1:45
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:45:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:6:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:15:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Get LTCbase3's children
        $$CHILD_BLOCK_START
        01:1:46
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:46:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:7:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:15:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Get LTCbase4's children
        $$CHILD_BLOCK_START
        01:1:47
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                10:1:0:47:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:8:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:15:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjSaveHandle
                        $$CHILD_BLOCK_START
                        06:qGetAtachedChild:Object
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:4:1:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:4:SavedObjectSlot
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:LT - Create Sky Lightning
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:16:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:0:6
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
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:48:Object1
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.600000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:5:NumTiles
                                10:14:5:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:150:Red
                                10:4:200:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:100.000000:SparkRate
                                10:6:2.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:100.000000:SparkRate
                                10:6:2.000000:Time
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:LT - Create Base Lighting
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
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:5:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
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
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:10:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LTSelfDestruct:Message
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                10:6:50.000000:SparkRate
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetScriptedDeath
                                $$CHILD_BLOCK_START
                                10:1:0:10:Object
                                10:10:0:1:On/Off
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:1:0:10:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:5:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qPlayerClosest:Object
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:1:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        10:10:0:14:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:11:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:13:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        10:1:0:49:Object
                                        10:10:0:12:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
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
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qPlayerClosest:Object
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        10:10:0:10:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qUserFlag:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:7:UserVar
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                06:qUserVarValue:value
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:UserVar
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:10:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:2:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:6:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:13:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                10:1:0:50:Object
                                                10:10:0:12:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qPlayerClosest:Object
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        10:10:0:10:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qUserFlag:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:7:UserVar
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                06:qUserVarValue:value
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:UserVar
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:10:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:7:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:13:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                10:1:0:51:Object
                                                10:10:0:12:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
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
                                08:aObjSaveHandle
                                        $$CHILD_BLOCK_START
                                        06:qPlayerClosest:Object
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        10:10:0:10:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                03:1
                                        $$CHILD_BLOCK_START
                                        09:1
                                                $$CHILD_BLOCK_START
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qUserFlag:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:8:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:3
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:7:UserVar
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aUserVarSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                06:qUserVarValue:value
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:UserVar
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:10:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:4:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                06:qObjSavedHandle:Object
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:8:SavedObjectSlot
                                                        $$CHILD_BLOCK_END
                                                10:10:0:13:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aObjSaveHandle
                                                $$CHILD_BLOCK_START
                                                10:1:0:52:Object
                                                10:10:0:12:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserFlag
                                                10:5:0:True/False
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object1
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                06:qObjSavedHandle:Object2
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:0.600000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:2:NumTiles
                                10:14:5:Texture
                                10:6:0.300000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:150:Red
                                10:4:200:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:6:100.000000:SparkRate
                                10:6:2.000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:LT - Create Discharge Lightning
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:13:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                06:qObjSavedHandle:Object
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:SavedObjectSlot
                                        $$CHILD_BLOCK_END
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSaveHandle
                                $$CHILD_BLOCK_START
                                06:qPlayerClosest:Object
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:10:0:7:UserVar
                                        $$CHILD_BLOCK_END
                                10:10:0:14:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValue:Float
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:7:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:200.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        06:qObjSavedHandle:Object
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:14:SavedObjectSlot
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:6:Sound
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object1
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        06:qObjSavedHandle:Object2
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:0.600000:Lifetime
                                        10:6:4.000000:Thickness
                                        10:4:2:NumTiles
                                        10:14:5:Texture
                                        10:6:0.300000:SlideTime
                                        10:4:3:TimesDrawn
                                        10:4:150:Red
                                        10:4:200:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                08:aObjSpark
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:40.000000:SparkRate
                                        10:6:2.000000:Time
                                        $$CHILD_BLOCK_END
                                08:aObjApplyDamage
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:10.000000:DamageAmount
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aObjSpark
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:40.000000:SparkRate
                                        10:6:1.000000:Time
                                        $$CHILD_BLOCK_END
                                08:aLightningCreate
                                        $$CHILD_BLOCK_START
                                        06:qObjSavedHandle:Object1
                                                $$CHILD_BLOCK_START
                                                10:10:0:11:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        06:qObjSavedHandle:Object2
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        10:6:0.600000:Lifetime
                                        10:6:4.000000:Thickness
                                        10:4:2:NumTiles
                                        10:14:5:Texture
                                        10:6:0.300000:SlideTime
                                        10:4:3:TimesDrawn
                                        10:4:150:Red
                                        10:4:200:Green
                                        10:4:255:Blue
                                        10:5:0:AutoTile
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:5.000000:LowerLimit
                                10:6:10.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:105:Upload Node Description
        $$CHILD_BLOCK_START
        01:0:28
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:UploadNode:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:106:SecurityDoor
        $$CHILD_BLOCK_START
        01:1:53
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
                                        10:11:16:ScriptID
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
                                10:8:SecurityDoor:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:SecurityDoor:Message
                                06:qObjParent:PlayerObject
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:110:Rocks Blew Up
        $$CHILD_BLOCK_START
        01:1:54
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalBlockageSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:6:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
