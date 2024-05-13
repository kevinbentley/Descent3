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
// Filename:	level8.cpp
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

#define ID_CUSTOM_OBJECT_10FD 0x001
#define ID_CUSTOM_OBJECT_0839 0x002
#define ID_CUSTOM_OBJECT_0838 0x003
#define ID_CUSTOM_OBJECT_3026 0x004
#define ID_CUSTOM_OBJECT_0901 0x005
#define ID_CUSTOM_OBJECT_0900 0x006
#define ID_CUSTOM_OBJECT_08FF 0x007
#define ID_CUSTOM_OBJECT_20FE 0x008
#define ID_CUSTOM_OBJECT_083D 0x009
#define ID_CUSTOM_OBJECT_09E3 0x00a
#define ID_CUSTOM_OBJECT_09FF 0x00b
#define ID_CUSTOM_OBJECT_1904 0x00c
#define ID_CUSTOM_OBJECT_08C1 0x00d
#define ID_CUSTOM_OBJECT_090F 0x00e
#define ID_CUSTOM_OBJECT_090E 0x00f
#define ID_CUSTOM_OBJECT_0910 0x010
#define ID_CUSTOM_OBJECT_090C 0x011
#define ID_CUSTOM_OBJECT_090B 0x012
#define ID_CUSTOM_OBJECT_090A 0x013
#define ID_CUSTOM_OBJECT_2853 0x014
#define ID_CUSTOM_OBJECT_090D 0x015
#define ID_CUSTOM_OBJECT_19E2 0x016
#define ID_CUSTOM_OBJECT_09FB 0x017
#define ID_CUSTOM_OBJECT_09FC 0x018
#define ID_CUSTOM_OBJECT_09FD 0x019
#define ID_CUSTOM_OBJECT_0845 0x01a
#define ID_CUSTOM_OBJECT_0846 0x01b
#define ID_CUSTOM_OBJECT_0844 0x01c
#define ID_CUSTOM_OBJECT_0849 0x01d
#define ID_CUSTOM_OBJECT_0848 0x01e
#define ID_CUSTOM_OBJECT_0847 0x01f
#define ID_CUSTOM_OBJECT_084A 0x020
#define ID_CUSTOM_OBJECT_084D 0x021
#define ID_CUSTOM_OBJECT_084C 0x022
#define ID_CUSTOM_OBJECT_084B 0x023
#define ID_CUSTOM_OBJECT_1088 0x024

#define ID_TRIGGER_0000 0x025
#define ID_TRIGGER_0018 0x026
#define ID_TRIGGER_0016 0x027
#define ID_TRIGGER_0007 0x028
#define ID_TRIGGER_0005 0x029
#define ID_TRIGGER_0004 0x02a
#define ID_TRIGGER_0002 0x02b
#define ID_TRIGGER_0015 0x02c
#define ID_TRIGGER_0013 0x02d
#define ID_TRIGGER_0011 0x02e
#define ID_TRIGGER_000F 0x02f
#define ID_TRIGGER_0001 0x030
#define ID_TRIGGER_0014 0x031
#define ID_TRIGGER_0012 0x032
#define ID_TRIGGER_0010 0x033
#define ID_TRIGGER_000B 0x034
#define ID_TRIGGER_000A 0x035
#define ID_TRIGGER_0009 0x036
#define ID_TRIGGER_000E 0x037
#define ID_TRIGGER_000D 0x038
#define ID_TRIGGER_000C 0x039
#define ID_TRIGGER_0008 0x03a
#define ID_TRIGGER_0006 0x03b
#define ID_TRIGGER_0003 0x03c
#define ID_TRIGGER_0017 0x03d

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

class CustomObjectScript_10FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0839 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0838 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3026 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0901 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0900 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08FF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20FE : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_083D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09E3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09FF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1904 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08C1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0910 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2853 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19E2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09FB : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09FC : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09FD : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0845 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0846 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0844 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0849 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0848 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0847 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1088 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
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

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0001 : public BaseScript {
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

class TriggerScript_0010 : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
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

class TriggerScript_0017 : public BaseScript {
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
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_093 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_091 = 0;
static int ScriptActionCtr_092 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_093 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_091 = 0;
  ScriptActionCtr_092 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_093, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_091, file_ptr);
  File_WriteInt(ScriptActionCtr_092, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_093 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_091 = File_ReadInt(file_ptr);
  ScriptActionCtr_092 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:Intro
1:Outside
2:Primary
3:Secondary
4:Underground
5:HeatSinks
6:Hangar
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

#define NUM_DOOR_NAMES 12
static const char *const Door_names[NUM_DOOR_NAMES] = {"CenterUpperSteamDo", "CenterLowerSteamDo", "RightUpperSteamDoo",
                                                       "RightLowerSteamDoo", "LeftUpperSteamDoor", "LeftLowerSteamDoor",
                                                       "FarHeatSinkDoor",    "CoolingDuctEntranc", "InnerHeatSinkDoor",
                                                       "MiddleHeatSinkDoor", "BetweenDoor",        "SecurityTowerDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 92
static const char *const Object_names[NUM_OBJECT_NAMES] = {"WeaponsPlantData",
                                                           "CenterSteamSpewer",
                                                           "RightSteamSpewer",
                                                           "LeftSteamSpewer",
                                                           "CoolingSystemSwitc",
                                                           "InnerHeatSinkDevic",
                                                           "MiddleHeatSinkDevi",
                                                           "OuterHeatSinkDevic",
                                                           "DuctForcefieldSwit",
                                                           "InnerForcefieldSwi",
                                                           "MiddleForcefieldSw",
                                                           "OuterForcefieldSwi",
                                                           "DeadlyCoolingShaft",
                                                           "FanReverseSwitch",
                                                           "CoolingFanMechanis",
                                                           "SecurityTowerDoorS",
                                                           "SecurityTowerTurre",
                                                           "CenterClampRelease",
                                                           "LeftClampRelease",
                                                           "RightClampRelease",
                                                           "RightClampSwitch",
                                                           "CenterClampSwitch",
                                                           "LeftClampSwitch",
                                                           "MedicalFrigate",
                                                           "ElevatorSwitch",
                                                           "HangarElevator",
                                                           "LeftPurgeButton",
                                                           "FlamePurgeRotator",
                                                           "CenterPurgeButton",
                                                           "RightPurgeButton",
                                                           "CoolingControlLink",
                                                           "CoolingBase",
                                                           "OuterFanA",
                                                           "OuterFanB",
                                                           "OuterFanD",
                                                           "MiddleFanD",
                                                           "MiddleFanC",
                                                           "MiddleFanB",
                                                           "MiddleFanA",
                                                           "InnerFanC",
                                                           "InnerFanB",
                                                           "InnerFanA",
                                                           "CoreFanA",
                                                           "WarningLightA",
                                                           "WarningLightB",
                                                           "WarningLightC",
                                                           "WarningLightD",
                                                           "WarningLightE",
                                                           "WarningLightF",
                                                           "WarningLightG",
                                                           "WarningLightH",
                                                           "WarningLightI",
                                                           "WarningLightJ",
                                                           "WarningLightK",
                                                           "WarningLightL",
                                                           "WarningLightM",
                                                           "WarningLightN",
                                                           "WarningLightO",
                                                           "WarningLightP",
                                                           "WarningLightQ",
                                                           "WarningLightR",
                                                           "WarningLightS",
                                                           "FlameA",
                                                           "FlameD",
                                                           "FlameH",
                                                           "FlameL",
                                                           "FlameN",
                                                           "FlameQ",
                                                           "FlameT",
                                                           "FlameV",
                                                           "FlameX",
                                                           "FlameZ",
                                                           "OverheatingSpewerA",
                                                           "OverheatingSpewerB",
                                                           "OverheatingSpewerC",
                                                           "OverheatingSpewerE",
                                                           "OverheatingSpewerF",
                                                           "OverheatingSpewerG",
                                                           "OverheatingSpewerI",
                                                           "OverheatingSpewerJ",
                                                           "OverheatingSpewerK",
                                                           "OverheatingSpewerL",
                                                           "OverheatingSpewerN",
                                                           "OverheatingSpewerP",
                                                           "OverheatingSpewerQ",
                                                           "OverheatingSpewerR",
                                                           "OverheatingSpewerS",
                                                           "OverheatingSpewerU",
                                                           "OverheatingSpewerV",
                                                           "OverheatingSpewerW",
                                                           "OverheatingSpewerY",
                                                           "OverheatingSpewerZ"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 23
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "CenterUpperSteamTu", "CenterUpperSteamDo", "CenterLowerSteamTu", "CenterLowerSteamDo", "RightUpperSteamTub",
    "RightUpperSteamDoo", "RightLowerSteamTub", "RightLowestSteamTu", "RightLowerSteamDoo", "LeftUpperSteamTube",
    "LeftUpperSteamDoor", "LeftLowerSteamTube", "LeftLowerSteamDoor", "RefineryCore",       "ThermalRegulator",
    "DuctForcefieldInte", "InnerLowerHeatSink", "MiddleLowerHeatSin", "OuterLowerHeatSink", "DeadlyCoolingShaft",
    "SecurityTower",      "HangarControlCente", "MainHangar"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 25
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EndLevelTrigger", "SecurityTowerGoalTr", "MHangar-1",      "MHeatSink-4",    "MHeatSink-3",
    "MHeatSink-2",     "MHeatSink-1",         "MUnderground-5", "MUnderground-4", "MUnderground-3",
    "MUnderground-2",  "MUnderground-1",      "MSecondary-4",   "MSecondary-3",   "MSecondary-2",
    "MPrimary-3",      "MPrimary-2",          "MPrimary-1",     "MOutside-6",     "MOutside-5",
    "MOutside-4",      "MOutside-3",          "MOutside-2",     "MOutside-1",     "InnerHeatSinkDoorSh"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 5
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbExplosionFarI", "AmbExplosionFarD", "AmbExplosionFarG",
                                                         "Powerup pickup", "AmbSirenIntense"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 5
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"P-MonTempBelo", "Bluedatascrollup", "P-MonCoolingEng",
                                                             "P-MonTempAbov", "P-MonTempCrit"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 7
static const char *const Path_names[NUM_PATH_NAMES] = {
    "IntroCameraPath",        "IntroPlayerPath", "EndLevelCameraPath", "EndLevelPlayerPath",
    "FrigateEscapePart2Path", "ElevatorPath",    "FrigateEscapePath"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 1
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"SecurityTowerMatcen"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 7
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Activate the Cooling System",       "Destroy the Outer Heat Sink",  "Make your way through the Refinery Core",
    "Destroy the Inner Heat Sink",       "Destroy the Middle Heat Sink", "Find a way out of the facility",
    "Rescue medical frigate Nightingale"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 21
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroCamera",
                                                             "EndLevel",
                                                             "CoolingSystemEngaged",
                                                             "CoolingSystemClock",
                                                             "ALLHeatSinksDestroyed",
                                                             "ForcefieldDisabled",
                                                             "CoreTempAboveNormal",
                                                             "FanReverseSwitch",
                                                             "CoolFanInvulnerable",
                                                             "CoolFanDestroyed",
                                                             "Mayday",
                                                             "MessageFromFrigate",
                                                             "ElevatorNeedsDown",
                                                             "ClampNotInUse",
                                                             "CenterClampDisengaged",
                                                             "EngagingCenterClamp",
                                                             "ElevatorDOWN",
                                                             "ElevatorAlreadyDown",
                                                             "WeaponsPlantData",
                                                             "FoundSecretData",
                                                             "FrigateSaved"};
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
    strcpy(filename, "level8.msg");
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
  case ID_CUSTOM_OBJECT_10FD:
    return new CustomObjectScript_10FD;
    break;
  case ID_CUSTOM_OBJECT_0839:
    return new CustomObjectScript_0839;
    break;
  case ID_CUSTOM_OBJECT_0838:
    return new CustomObjectScript_0838;
    break;
  case ID_CUSTOM_OBJECT_3026:
    return new CustomObjectScript_3026;
    break;
  case ID_CUSTOM_OBJECT_0901:
    return new CustomObjectScript_0901;
    break;
  case ID_CUSTOM_OBJECT_0900:
    return new CustomObjectScript_0900;
    break;
  case ID_CUSTOM_OBJECT_08FF:
    return new CustomObjectScript_08FF;
    break;
  case ID_CUSTOM_OBJECT_20FE:
    return new CustomObjectScript_20FE;
    break;
  case ID_CUSTOM_OBJECT_083D:
    return new CustomObjectScript_083D;
    break;
  case ID_CUSTOM_OBJECT_09E3:
    return new CustomObjectScript_09E3;
    break;
  case ID_CUSTOM_OBJECT_09FF:
    return new CustomObjectScript_09FF;
    break;
  case ID_CUSTOM_OBJECT_1904:
    return new CustomObjectScript_1904;
    break;
  case ID_CUSTOM_OBJECT_08C1:
    return new CustomObjectScript_08C1;
    break;
  case ID_CUSTOM_OBJECT_090F:
    return new CustomObjectScript_090F;
    break;
  case ID_CUSTOM_OBJECT_090E:
    return new CustomObjectScript_090E;
    break;
  case ID_CUSTOM_OBJECT_0910:
    return new CustomObjectScript_0910;
    break;
  case ID_CUSTOM_OBJECT_090C:
    return new CustomObjectScript_090C;
    break;
  case ID_CUSTOM_OBJECT_090B:
    return new CustomObjectScript_090B;
    break;
  case ID_CUSTOM_OBJECT_090A:
    return new CustomObjectScript_090A;
    break;
  case ID_CUSTOM_OBJECT_2853:
    return new CustomObjectScript_2853;
    break;
  case ID_CUSTOM_OBJECT_090D:
    return new CustomObjectScript_090D;
    break;
  case ID_CUSTOM_OBJECT_19E2:
    return new CustomObjectScript_19E2;
    break;
  case ID_CUSTOM_OBJECT_09FB:
    return new CustomObjectScript_09FB;
    break;
  case ID_CUSTOM_OBJECT_09FC:
    return new CustomObjectScript_09FC;
    break;
  case ID_CUSTOM_OBJECT_09FD:
    return new CustomObjectScript_09FD;
    break;
  case ID_CUSTOM_OBJECT_0845:
    return new CustomObjectScript_0845;
    break;
  case ID_CUSTOM_OBJECT_0846:
    return new CustomObjectScript_0846;
    break;
  case ID_CUSTOM_OBJECT_0844:
    return new CustomObjectScript_0844;
    break;
  case ID_CUSTOM_OBJECT_0849:
    return new CustomObjectScript_0849;
    break;
  case ID_CUSTOM_OBJECT_0848:
    return new CustomObjectScript_0848;
    break;
  case ID_CUSTOM_OBJECT_0847:
    return new CustomObjectScript_0847;
    break;
  case ID_CUSTOM_OBJECT_084A:
    return new CustomObjectScript_084A;
    break;
  case ID_CUSTOM_OBJECT_084D:
    return new CustomObjectScript_084D;
    break;
  case ID_CUSTOM_OBJECT_084C:
    return new CustomObjectScript_084C;
    break;
  case ID_CUSTOM_OBJECT_084B:
    return new CustomObjectScript_084B;
    break;
  case ID_CUSTOM_OBJECT_1088:
    return new CustomObjectScript_1088;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
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
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
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
  case ID_CUSTOM_OBJECT_10FD:
    delete ((CustomObjectScript_10FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0839:
    delete ((CustomObjectScript_0839 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0838:
    delete ((CustomObjectScript_0838 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3026:
    delete ((CustomObjectScript_3026 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0901:
    delete ((CustomObjectScript_0901 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0900:
    delete ((CustomObjectScript_0900 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08FF:
    delete ((CustomObjectScript_08FF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20FE:
    delete ((CustomObjectScript_20FE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_083D:
    delete ((CustomObjectScript_083D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09E3:
    delete ((CustomObjectScript_09E3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09FF:
    delete ((CustomObjectScript_09FF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1904:
    delete ((CustomObjectScript_1904 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08C1:
    delete ((CustomObjectScript_08C1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090F:
    delete ((CustomObjectScript_090F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090E:
    delete ((CustomObjectScript_090E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0910:
    delete ((CustomObjectScript_0910 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090C:
    delete ((CustomObjectScript_090C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090B:
    delete ((CustomObjectScript_090B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090A:
    delete ((CustomObjectScript_090A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2853:
    delete ((CustomObjectScript_2853 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090D:
    delete ((CustomObjectScript_090D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19E2:
    delete ((CustomObjectScript_19E2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09FB:
    delete ((CustomObjectScript_09FB *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09FC:
    delete ((CustomObjectScript_09FC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09FD:
    delete ((CustomObjectScript_09FD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0845:
    delete ((CustomObjectScript_0845 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0846:
    delete ((CustomObjectScript_0846 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0844:
    delete ((CustomObjectScript_0844 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0849:
    delete ((CustomObjectScript_0849 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0848:
    delete ((CustomObjectScript_0848 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0847:
    delete ((CustomObjectScript_0847 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084A:
    delete ((CustomObjectScript_084A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084D:
    delete ((CustomObjectScript_084D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084C:
    delete ((CustomObjectScript_084C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084B:
    delete ((CustomObjectScript_084B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1088:
    delete ((CustomObjectScript_1088 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
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
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
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
  case ID_CUSTOM_OBJECT_10FD:
  case ID_CUSTOM_OBJECT_0839:
  case ID_CUSTOM_OBJECT_0838:
  case ID_CUSTOM_OBJECT_3026:
  case ID_CUSTOM_OBJECT_0901:
  case ID_CUSTOM_OBJECT_0900:
  case ID_CUSTOM_OBJECT_08FF:
  case ID_CUSTOM_OBJECT_20FE:
  case ID_CUSTOM_OBJECT_083D:
  case ID_CUSTOM_OBJECT_09E3:
  case ID_CUSTOM_OBJECT_09FF:
  case ID_CUSTOM_OBJECT_1904:
  case ID_CUSTOM_OBJECT_08C1:
  case ID_CUSTOM_OBJECT_090F:
  case ID_CUSTOM_OBJECT_090E:
  case ID_CUSTOM_OBJECT_0910:
  case ID_CUSTOM_OBJECT_090C:
  case ID_CUSTOM_OBJECT_090B:
  case ID_CUSTOM_OBJECT_090A:
  case ID_CUSTOM_OBJECT_2853:
  case ID_CUSTOM_OBJECT_090D:
  case ID_CUSTOM_OBJECT_19E2:
  case ID_CUSTOM_OBJECT_09FB:
  case ID_CUSTOM_OBJECT_09FC:
  case ID_CUSTOM_OBJECT_09FD:
  case ID_CUSTOM_OBJECT_0845:
  case ID_CUSTOM_OBJECT_0846:
  case ID_CUSTOM_OBJECT_0844:
  case ID_CUSTOM_OBJECT_0849:
  case ID_CUSTOM_OBJECT_0848:
  case ID_CUSTOM_OBJECT_0847:
  case ID_CUSTOM_OBJECT_084A:
  case ID_CUSTOM_OBJECT_084D:
  case ID_CUSTOM_OBJECT_084C:
  case ID_CUSTOM_OBJECT_084B:
  case ID_CUSTOM_OBJECT_1088:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0017:
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
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0017;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[36];
  static int cust_id_list[36] = {
      ID_CUSTOM_OBJECT_10FD, ID_CUSTOM_OBJECT_0839, ID_CUSTOM_OBJECT_0838, ID_CUSTOM_OBJECT_3026, ID_CUSTOM_OBJECT_0901,
      ID_CUSTOM_OBJECT_0900, ID_CUSTOM_OBJECT_08FF, ID_CUSTOM_OBJECT_20FE, ID_CUSTOM_OBJECT_083D, ID_CUSTOM_OBJECT_09E3,
      ID_CUSTOM_OBJECT_09FF, ID_CUSTOM_OBJECT_1904, ID_CUSTOM_OBJECT_08C1, ID_CUSTOM_OBJECT_090F, ID_CUSTOM_OBJECT_090E,
      ID_CUSTOM_OBJECT_0910, ID_CUSTOM_OBJECT_090C, ID_CUSTOM_OBJECT_090B, ID_CUSTOM_OBJECT_090A, ID_CUSTOM_OBJECT_2853,
      ID_CUSTOM_OBJECT_090D, ID_CUSTOM_OBJECT_19E2, ID_CUSTOM_OBJECT_09FB, ID_CUSTOM_OBJECT_09FC, ID_CUSTOM_OBJECT_09FD,
      ID_CUSTOM_OBJECT_0845, ID_CUSTOM_OBJECT_0846, ID_CUSTOM_OBJECT_0844, ID_CUSTOM_OBJECT_0849, ID_CUSTOM_OBJECT_0848,
      ID_CUSTOM_OBJECT_0847, ID_CUSTOM_OBJECT_084A, ID_CUSTOM_OBJECT_084D, ID_CUSTOM_OBJECT_084C, ID_CUSTOM_OBJECT_084B,
      ID_CUSTOM_OBJECT_1088};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[4];
  cust_handle_list[1] = Object_handles[5];
  cust_handle_list[2] = Object_handles[6];
  cust_handle_list[3] = Object_handles[7];
  cust_handle_list[4] = Object_handles[8];
  cust_handle_list[5] = Object_handles[9];
  cust_handle_list[6] = Object_handles[10];
  cust_handle_list[7] = Object_handles[11];
  cust_handle_list[8] = Object_handles[12];
  cust_handle_list[9] = Object_handles[13];
  cust_handle_list[10] = Object_handles[14];
  cust_handle_list[11] = Object_handles[15];
  cust_handle_list[12] = Object_handles[16];
  cust_handle_list[13] = Object_handles[17];
  cust_handle_list[14] = Object_handles[18];
  cust_handle_list[15] = Object_handles[19];
  cust_handle_list[16] = Object_handles[20];
  cust_handle_list[17] = Object_handles[21];
  cust_handle_list[18] = Object_handles[22];
  cust_handle_list[19] = Object_handles[23];
  cust_handle_list[20] = Object_handles[24];
  cust_handle_list[21] = Object_handles[0];
  cust_handle_list[22] = Object_handles[26];
  cust_handle_list[23] = Object_handles[29];
  cust_handle_list[24] = Object_handles[28];
  cust_handle_list[25] = Object_handles[32];
  cust_handle_list[26] = Object_handles[33];
  cust_handle_list[27] = Object_handles[34];
  cust_handle_list[28] = Object_handles[35];
  cust_handle_list[29] = Object_handles[36];
  cust_handle_list[30] = Object_handles[37];
  cust_handle_list[31] = Object_handles[38];
  cust_handle_list[32] = Object_handles[39];
  cust_handle_list[33] = Object_handles[40];
  cust_handle_list[34] = Object_handles[41];
  cust_handle_list[35] = Object_handles[42];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 36;
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

    // Script 029: Medical Frigate Mayday!
    if ((qRoomHasPlayer(Room_indexes[21]) == true) && (qUserFlag(10) == false)) {
      aAddGameMessage(Message_strings[10], Message_strings[11]);
      aUserFlagSet(10, 1);
      aGoalEnableDisable(1, Goal_indexes[6]);
      aSoundPlaySteaming("VoxL08SpecificA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 091: Found Main Hangar, Still Need Passkey
    if (qRoomHasPlayer(Room_indexes[22]) == true) {
      aGoalCompleted(Goal_indexes[5], 1);

      // Increment the script action counter
      if (ScriptActionCtr_091 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_091++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Let It Snow, Let It Snow, Let It Snow...
    if (1) {
      aSnowTurnOn(1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 001: Intro Camera Sequence
    if (1) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[0], Path_indexes[1], 10.000000f);
      aSoundPlaySteaming("VoxL08StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 006: Center Steam Vent Start
    if (1) {
      aUserFlagSet(2, 1);
      aSetLevelTimer(10.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 005: Right Steam Vent Start
    if (1) {
      aUserFlagSet(1, 1);
      aSetLevelTimer(5.000000f, 2);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 004: Left Steam Vent Start
    if (1) {
      aUserFlagSet(0, 1);
      aSetLevelTimer(15.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 031: Center Clamp Switch Start
    if (1) {
      aObjPlayAnim(Object_handles[21], 10, 10, 1.000000f, 0);
      aUserFlagSet(12, 1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 044: Purge Button Attach Starts
    if (1) {
      aAttachExistingObject(Object_handles[26], 0, Object_handles[27], 0);
      aAttachExistingObject(Object_handles[28], 0, Object_handles[27], 1);
      aAttachExistingObject(Object_handles[29], 0, Object_handles[27], 2);
      aObjPlayAnim(Object_handles[27], 1, 32, 40.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 045: Flame Purge Flames
    if (1) {
      aTurnOnSpew(Object_handles[27], 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.080000f, -1.000000f,
                  10.000000f, 80.000000f, 1, 3);
      aTurnOnSpew(Object_handles[27], 1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.080000f, -1.000000f,
                  10.000000f, 80.000000f, 1, 4);
      aTurnOnSpew(Object_handles[27], 2, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.080000f, -1.000000f,
                  10.000000f, 80.000000f, 1, 5);
      aTurnOnSpew(Object_handles[27], 0, 2, 0.000000f, 0.000000f, 0, 1, 1.000000f, 1.000000f, -1.000000f, 10.000000f,
                  80.000000f, 0, 6);
      aTurnOnSpew(Object_handles[27], 1, 2, 0.000000f, 0.000000f, 0, 1, 1.000000f, 1.000000f, -1.000000f, 10.000000f,
                  80.000000f, 0, 7);
      aTurnOnSpew(Object_handles[27], 2, 2, 0.000000f, 0.000000f, 0, 1, 1.000000f, 1.000000f, -1.000000f, 10.000000f,
                  80.000000f, 0, 8);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 049: Music Init
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 075: Cooling Shaft Starts
    if (1) {
      aAttachExistingObject(Object_handles[30], 0, Object_handles[31], 0);
      aAttachExistingObject(Object_handles[14], 0, Object_handles[30], 1);
      aRoomSetWind(Room_indexes[19], 0.000000f, -1.000000f, 0.000000f, 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }

    // Script 088: Warning Lights Start
    if (1) {
      aObjSetLightingDist(Object_handles[43], 0.000000f);
      aObjSetLightingDist(Object_handles[44], 0.000000f);
      aObjSetLightingDist(Object_handles[45], 0.000000f);
      aObjSetLightingDist(Object_handles[46], 0.000000f);
      aObjSetLightingDist(Object_handles[47], 0.000000f);
      aObjSetLightingDist(Object_handles[48], 0.000000f);
      aObjSetLightingDist(Object_handles[49], 0.000000f);
      aObjSetLightingDist(Object_handles[50], 0.000000f);
      aObjSetLightingDist(Object_handles[51], 0.000000f);
      aObjSetLightingDist(Object_handles[52], 0.000000f);
      aObjSetLightingDist(Object_handles[53], 0.000000f);
      aObjSetLightingDist(Object_handles[54], 0.000000f);
      aObjSetLightingDist(Object_handles[55], 0.000000f);
      aObjSetLightingDist(Object_handles[56], 0.000000f);
      aObjSetLightingDist(Object_handles[57], 0.000000f);
      aObjSetLightingDist(Object_handles[58], 0.000000f);
      aObjSetLightingDist(Object_handles[59], 0.000000f);
      aObjSetLightingDist(Object_handles[60], 0.000000f);
      aObjSetLightingDist(Object_handles[61], 0.000000f);
      aObjGhostSet(1, Object_handles[62]);
      aObjGhostSet(1, Object_handles[63]);
      aObjGhostSet(1, Object_handles[64]);
      aObjGhostSet(1, Object_handles[65]);
      aObjGhostSet(1, Object_handles[66]);
      aObjGhostSet(1, Object_handles[67]);
      aObjGhostSet(1, Object_handles[68]);
      aObjGhostSet(1, Object_handles[69]);
      aObjGhostSet(1, Object_handles[70]);
      aObjGhostSet(1, Object_handles[71]);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 014: Center Steam Vent OVERHEATING!
    if (3 == event_data->id) {
      aRoomSetWind(Room_indexes[0], 0.000000f, 1.000000f, 0.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[1], 0.000000f, 1.000000f, 0.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[2], 0.000000f, 1.000000f, 0.000000f, 30.000000f);
      aRoomSetWind(Room_indexes[3], 0.000000f, 1.000000f, 0.000000f, 30.000000f);
      aRoomSetDamage(Room_indexes[1], 18.000000f, 4);
      aRoomSetDamage(Room_indexes[2], 18.000000f, 4);
      aRoomSetDamage(Room_indexes[3], 18.000000f, 4);
      aDoorSetPos(Door_handles[0], 1.000000f);
      aDoorSetPos(Door_handles[1], 1.000000f);
      aTurnOnSpew(Object_handles[1], -1, 2, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.150000f, -1.000000f,
                  20.000000f, 80.000000f, 0, 2);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 008: Center Steam Vent
    if (1 == event_data->id) {
      if (qUserFlag(2) == true) {
        aTurnOnSpew(Object_handles[1], -1, 7, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.150000f, -1.000000f,
                    20.000000f, 80.000000f, 0, 2);
        aUserFlagSet(2, 0);
        aSetLevelTimer(10.000000f, 0);
        aDoorSetPos(Door_handles[1], 1.000000f);
        aDoorSetPos(Door_handles[0], 1.000000f);
        aRoomSetDamage(Room_indexes[3], 6.000000f, 4);
        aRoomSetDamage(Room_indexes[2], 6.000000f, 4);
        aRoomSetDamage(Room_indexes[1], 6.000000f, 4);
        aRoomSetWind(Room_indexes[3], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
        aRoomSetWind(Room_indexes[2], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
        aRoomSetWind(Room_indexes[1], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
        aRoomSetWind(Room_indexes[0], 0.000000f, 1.000000f, 0.000000f, 10.000000f);
      } else {
        aUserFlagSet(2, 1);
        aTurnOffSpew(2);
        aSetLevelTimer(10.000000f, 1);
        aDoorSetPos(Door_handles[1], 0.000000f);
        aDoorSetPos(Door_handles[0], 0.000000f);
        aRoomSetDamage(Room_indexes[3], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[2], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[1], 0.000000f, 0);
        aRoomSetWind(Room_indexes[3], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[1], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[0], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 015: Right Steam Vent OVERHEATING!
    if (3 == event_data->id) {
      aRoomSetWind(Room_indexes[4], 0.000000f, 1.000000f, 0.000000f, 45.000000f);
      aRoomSetWind(Room_indexes[5], 0.000000f, 1.000000f, 0.000000f, 45.000000f);
      aRoomSetWind(Room_indexes[6], 0.000000f, 1.000000f, 0.000000f, 45.000000f);
      aRoomSetWind(Room_indexes[7], 0.000000f, 1.000000f, 0.000000f, 45.000000f);
      aRoomSetWind(Room_indexes[8], 0.000000f, 1.000000f, 0.000000f, 45.000000f);
      aRoomSetDamage(Room_indexes[5], 27.000000f, 4);
      aRoomSetDamage(Room_indexes[6], 27.000000f, 4);
      aRoomSetDamage(Room_indexes[7], 27.000000f, 4);
      aRoomSetDamage(Room_indexes[8], 27.000000f, 4);
      aDoorSetPos(Door_handles[2], 1.000000f);
      aDoorSetPos(Door_handles[3], 1.000000f);
      aTurnOnSpew(Object_handles[2], -1, 2, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.150000f, -1.000000f,
                  20.000000f, 80.000000f, 0, 1);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 007: Right Steam Vent
    if (2 == event_data->id) {
      if (qUserFlag(1) == true) {
        aTurnOnSpew(Object_handles[2], -1, 7, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.150000f, -1.000000f,
                    20.000000f, 80.000000f, 0, 1);
        aUserFlagSet(1, 0);
        aSetLevelTimer(5.000000f, 2);
        aDoorSetPos(Door_handles[3], 1.000000f);
        aDoorSetPos(Door_handles[2], 1.000000f);
        aRoomSetDamage(Room_indexes[8], 9.000000f, 4);
        aRoomSetDamage(Room_indexes[7], 9.000000f, 4);
        aRoomSetDamage(Room_indexes[6], 9.000000f, 4);
        aRoomSetDamage(Room_indexes[5], 9.000000f, 4);
        aRoomSetWind(Room_indexes[8], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
        aRoomSetWind(Room_indexes[7], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
        aRoomSetWind(Room_indexes[6], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
        aRoomSetWind(Room_indexes[5], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
        aRoomSetWind(Room_indexes[4], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      } else {
        aUserFlagSet(1, 1);
        aTurnOffSpew(1);
        aSetLevelTimer(5.000000f, 2);
        aDoorSetPos(Door_handles[3], 0.000000f);
        aDoorSetPos(Door_handles[2], 0.000000f);
        aRoomSetDamage(Room_indexes[8], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[7], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[6], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[5], 0.000000f, 0);
        aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[5], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[4], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 016: Left Steam Vent OVERHEATING!
    if (3 == event_data->id) {
      aRoomSetWind(Room_indexes[9], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      aRoomSetWind(Room_indexes[12], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      aRoomSetDamage(Room_indexes[10], 9.000000f, 4);
      aRoomSetDamage(Room_indexes[11], 9.000000f, 4);
      aRoomSetDamage(Room_indexes[12], 9.000000f, 4);
      aDoorSetPos(Door_handles[4], 1.000000f);
      aDoorSetPos(Door_handles[5], 1.000000f);
      aTurnOnSpew(Object_handles[3], -1, 2, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.150000f, -1.000000f,
                  20.000000f, 80.000000f, 0, 0);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 003: Left Steam Vent
    if (0 == event_data->id) {
      if (qUserFlag(0) == true) {
        aTurnOnSpew(Object_handles[3], -1, 7, 0.000000f, 0.000000f, 65536, 0, 10.000000f, 0.150000f, -1.000000f,
                    20.000000f, 80.000000f, 0, 0);
        aUserFlagSet(0, 0);
        aSetLevelTimer(15.000000f, 0);
        aDoorSetPos(Door_handles[5], 1.000000f);
        aDoorSetPos(Door_handles[4], 1.000000f);
        aRoomSetDamage(Room_indexes[12], 3.000000f, 4);
        aRoomSetDamage(Room_indexes[11], 3.000000f, 4);
        aRoomSetDamage(Room_indexes[10], 3.000000f, 4);
        aRoomSetWind(Room_indexes[12], 0.000000f, 1.000000f, 0.000000f, 5.000000f);
        aRoomSetWind(Room_indexes[11], 0.000000f, 1.000000f, 0.000000f, 5.000000f);
        aRoomSetWind(Room_indexes[10], 0.000000f, 1.000000f, 0.000000f, 5.000000f);
        aRoomSetWind(Room_indexes[9], 0.000000f, 1.000000f, 0.000000f, 5.000000f);
      } else {
        aUserFlagSet(0, 1);
        aTurnOffSpew(0);
        aSetLevelTimer(15.000000f, 0);
        aDoorSetPos(Door_handles[5], 0.000000f);
        aDoorSetPos(Door_handles[4], 0.000000f);
        aRoomSetDamage(Room_indexes[12], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[11], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[10], 0.000000f, 0);
        aRoomSetWind(Room_indexes[12], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[11], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[10], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
        aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 0.000000f, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 020: Core Temperature Above Normal!
    if (3 == event_data->id) {
      aMiscViewerShake(75.000000f);
      aShowHUDMessage(Message_strings[6]);
      aSetLevelTimer(60.000000f, 4);
      aSoundPlay2D(Sound_indexes[0], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 026: Random Tremors due to CRITICAL Heat!
    if (5 == event_data->id) {
      aSetLevelTimer(qRandomValue(30.000000f, 90.000000f), 5);
      aMiscViewerShake(qRandomValue(50.000000f, 100.000000f));
      aSoundPlay2D(Sound_indexes[1], 1.000000f);
      aSetLevelTimer(3.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 021: Random Tremors due to High Heat!
    if (4 == event_data->id) {
      aSetLevelTimer(qRandomValue(10.000000f, 45.000000f), 4);
      aMiscViewerShake(qRandomValue(10.000000f, 50.000000f));
      aSoundPlay2D(Sound_indexes[2], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 077: Frigate Waits For Elevator Timer
    if (6 == event_data->id) {
      aAddGameMessage(Message_strings[20], Message_strings[11]);
      aPortalRenderSet(0, 0, Room_indexes[22], 1);
      aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[6], 131328, 0, 3);
      aGoalCompleted(Goal_indexes[6], 1);
      aMissionSetFlag(28, 1);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }

    // Script 089: Warning Lights & Sirens!!!!!!
    if (3 == event_data->id) {
      aObjSetLightingDist(Object_handles[43], 70.000000f);
      aObjSetLightingDist(Object_handles[44], 70.000000f);
      aObjSetLightingDist(Object_handles[45], 70.000000f);
      aObjSetLightingDist(Object_handles[46], 70.000000f);
      aObjSetLightingDist(Object_handles[47], 70.000000f);
      aObjSetLightingDist(Object_handles[48], 70.000000f);
      aObjSetLightingDist(Object_handles[49], 70.000000f);
      aObjSetLightingDist(Object_handles[50], 70.000000f);
      aObjSetLightingDist(Object_handles[51], 70.000000f);
      aObjSetLightingDist(Object_handles[52], 70.000000f);
      aObjSetLightingDist(Object_handles[53], 70.000000f);
      aObjSetLightingDist(Object_handles[54], 70.000000f);
      aObjSetLightingDist(Object_handles[55], 70.000000f);
      aObjSetLightingDist(Object_handles[56], 70.000000f);
      aObjSetLightingDist(Object_handles[57], 70.000000f);
      aObjSetLightingDist(Object_handles[58], 70.000000f);
      aObjSetLightingDist(Object_handles[59], 70.000000f);
      aObjSetLightingDist(Object_handles[60], 70.000000f);
      aObjSetLightingDist(Object_handles[61], 70.000000f);
      aObjPlayAnim(Object_handles[43], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[44], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[45], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[46], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[47], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[48], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[49], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[50], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[51], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[52], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[53], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[54], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[55], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[56], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[57], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[58], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[59], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[60], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[61], 0, 64, 1.000000f, 1);
      aSoundPlayObject(Sound_indexes[4], Object_handles[43], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[44], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[45], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[46], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[47], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[48], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[49], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[50], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[51], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[52], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[53], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[54], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[55], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[56], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[57], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[58], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[59], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[60], 0.750000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[61], 0.750000f);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }

    // Script 090: High Heat Steam Spewers
    if (3 == event_data->id) {
      aTurnOnSpew(Object_handles[72], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 9);
      aTurnOnSpew(Object_handles[73], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 10);
      aTurnOnSpew(Object_handles[74], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 11);
      aTurnOnSpew(Object_handles[75], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 13);
      aTurnOnSpew(Object_handles[76], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 14);
      aTurnOnSpew(Object_handles[77], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 15);
      aTurnOnSpew(Object_handles[78], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 17);
      aTurnOnSpew(Object_handles[79], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 18);
      aTurnOnSpew(Object_handles[80], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 19);
      aTurnOnSpew(Object_handles[81], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 20);
      aTurnOnSpew(Object_handles[82], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 22);
      aTurnOnSpew(Object_handles[83], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 24);
      aTurnOnSpew(Object_handles[84], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 25);
      aTurnOnSpew(Object_handles[85], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 26);
      aTurnOnSpew(Object_handles[86], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 27);
      aTurnOnSpew(Object_handles[87], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 29);
      aTurnOnSpew(Object_handles[88], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 30);
      aTurnOnSpew(Object_handles[89], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 31);
      aTurnOnSpew(Object_handles[90], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 33);
      aTurnOnSpew(Object_handles[91], -1, 7, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f,
                  5.000000f, 20.000000f, 0, 34);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }

    // Script 009: Critical Heat Flame Spewers REAL!
    if ((ScriptActionCtr_009 < 1) && (9 == event_data->id)) {
      aTurnOnSpew(Object_handles[62], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 35);
      aTurnOnSpew(Object_handles[63], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 36);
      aTurnOnSpew(Object_handles[64], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 37);
      aTurnOnSpew(Object_handles[65], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 38);
      aTurnOnSpew(Object_handles[66], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 39);
      aTurnOnSpew(Object_handles[67], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 40);
      aTurnOnSpew(Object_handles[68], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 41);
      aTurnOnSpew(Object_handles[69], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 42);
      aTurnOnSpew(Object_handles[70], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 43);
      aTurnOnSpew(Object_handles[71], 0, 2, 0.000000f, 0.000000f, 65536, 0, 3.000000f, 0.150000f, -1.000000f, 5.000000f,
                  20.000000f, 0, 44);
      aTurnOnSpew(Object_handles[62], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 45);
      aTurnOnSpew(Object_handles[63], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 46);
      aTurnOnSpew(Object_handles[64], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 47);
      aTurnOnSpew(Object_handles[65], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 48);
      aTurnOnSpew(Object_handles[66], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 12);
      aTurnOnSpew(Object_handles[67], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 16);
      aTurnOnSpew(Object_handles[68], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 21);
      aTurnOnSpew(Object_handles[69], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 23);
      aTurnOnSpew(Object_handles[70], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 28);
      aTurnOnSpew(Object_handles[71], 0, 2, 0.000000f, 0.000000f, 0, 1, 3.000000f, 1.000000f, -1.000000f, 4.000000f,
                  20.000000f, 0, 32);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 092: End Level Secret Level VOX
    if (10 == event_data->id) {
      aSoundPlaySteaming("VoxL08Secret.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_092 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_092++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 050: Music OutsideInit
    if ((ScriptActionCtr_050 < 1) && (1)) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Thermal Regulation Center
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(4) == false) {
        aObjPlayAnim(Object_handles[4], 0, 2, 2.000000f, 0);
        aUserFlagSet(4, 1);
        aShowHUDMessage(Message_strings[2]);
        aRoomSetFaceTexture(Room_indexes[13], 78, Texture_indexes[0]);
        aRoomSetFaceTexture(Room_indexes[13], 101, Texture_indexes[0]);
        aRoomSetFaceTexture(Room_indexes[14], 148, Texture_indexes[0]);
        aRoomSetFaceTexture(Room_indexes[14], 136, Texture_indexes[1]);
        aRoomSetFaceTexture(Room_indexes[14], 157, Texture_indexes[2]);
        aRoomSetDamage(Room_indexes[5], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[1], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[10], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[6], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[7], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[2], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[11], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[12], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[3], 0.000000f, 0);
        aRoomSetDamage(Room_indexes[8], 0.000000f, 0);
        aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[0], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[4], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[5], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[1], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[10], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[6], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[7], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[11], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[12], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[3], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aRoomSetWind(Room_indexes[8], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
        aDoorSetPos(Door_handles[6], 1.000000f);
        aGoalCompleted(Goal_indexes[0], 1);
        aGoalEnableDisable(1, Goal_indexes[1]);
      } else {
        aShowHUDMessage(Message_strings[3]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0839::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 013: Inner Heat Sink Destroyed
    if (1) {
      aDoorLockUnlock(0, Door_handles[7]);
      aRoomSetFaceTexture(Room_indexes[13], 78, Texture_indexes[3]);
      aRoomSetFaceTexture(Room_indexes[13], 101, Texture_indexes[3]);
      aRoomSetFaceTexture(Room_indexes[14], 148, Texture_indexes[3]);
      aSetLevelTimer(20.000000f, 3);
      aRoomChangeFog(Room_indexes[13], 0.250000f, 0.500000f, 1.000000f, 2000.000000f, 120.000000f);
      aShowHUDMessage(Message_strings[4]);
      aGoalEnableDisable(1, Goal_indexes[2]);
      aGoalCompleted(Goal_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0838::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 012: Middle Heat Sink Destroyed
    if (1) {
      aGoalCompleted(Goal_indexes[4], 1);
      aGoalEnableDisable(1, Goal_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3026::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 011: Outer Heat Sink Destroyed
    if (1) {
      aGoalCompleted(Goal_indexes[1], 1);
      aGoalEnableDisable(1, Goal_indexes[4]);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0901::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Cooling Duct Forcefield Disabled
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(8) == false)) {
      aShowHUDMessage(Message_strings[5]);
      aPortalRenderSet(0, 3, Room_indexes[15], 1);
      aUserFlagSet(8, 1);
      aObjPlayAnim(Object_handles[8], 0, 2, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0900::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Inner Heat Sink Forcefield Disabled
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == false)) {
      aShowHUDMessage(Message_strings[5]);
      aPortalRenderSet(0, 1, Room_indexes[16], 1);
      aUserFlagSet(7, 1);
      aObjPlayAnim(Object_handles[9], 0, 2, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08FF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Middle Heat Sink Forcefield Disabled
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == false)) {
      aShowHUDMessage(Message_strings[5]);
      aPortalRenderSet(0, 1, Room_indexes[17], 1);
      aUserFlagSet(6, 1);
      aObjPlayAnim(Object_handles[10], 0, 2, 2.000000f, 0);
      aDoorSetPos(Door_handles[8], 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[3]);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20FE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Outer Heat Sink Forcefield Disabled
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(5) == false)) {
      aShowHUDMessage(Message_strings[5]);
      aPortalRenderSet(0, 1, Room_indexes[18], 1);
      aUserFlagSet(5, 1);
      aObjPlayAnim(Object_handles[11], 0, 2, 2.000000f, 0);
      aDoorSetPos(Door_handles[9], 1.000000f);
      aGoalEnableDisable(1, Goal_indexes[4]);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_083D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Deadly Cooling Shaft Fan Kills Player!
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 50.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 076: Deadly Fan Gets Shot By Player
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aObjSetShields(Object_handles[12], 1000000000.000000f);
      aShowHUDMessage(Message_strings[8]);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }

    // Script 025: Deadly Fan Controller
    if (Object_handles[14] == event_data->it_handle) {
      aObjDestroy(Object_handles[14]);
      aObjDestroy(Object_handles[12]);
      aRoomSetWind(Room_indexes[19], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aSetLevelTimer(120.000000f, 5);
      aCancelTimer(4);
      aRoomSetFaceTexture(Room_indexes[13], 78, Texture_indexes[4]);
      aRoomSetFaceTexture(Room_indexes[13], 101, Texture_indexes[4]);
      aRoomSetFaceTexture(Room_indexes[14], 148, Texture_indexes[4]);
      aDoorLockUnlock(1, Door_handles[7]);
      aDoorLockUnlock(0, Door_handles[10]);
      aUserFlagSet(17, 1);
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09E3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Deadly Cooling Shaft Reverse Switch
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(17) == false)) {
      if (qUserFlag(14) == false) {
        aRoomChangeWind(Room_indexes[19], 0.000000f, 1.000000f, 0.000000f, 15.000000f, 10.000000f);
        aUserFlagSet(14, 1);
        aObjPlayAnim(Object_handles[13], 0, 1, 2.000000f, 0);
        aShowHUDMessage(Message_strings[7]);
      } else {
        aRoomChangeWind(Room_indexes[19], 0.000000f, -1.000000f, 0.000000f, 15.000000f, 10.000000f);
        aUserFlagSet(14, 0);
        aObjPlayAnim(Object_handles[13], 1, 2, 2.000000f, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09FF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 093: Deadly Fan Controller Kills Bots...
    if (qObjIsType(event_data->it_handle, 2) == true) {
      aObjApplyDamage(event_data->it_handle, 1000000000.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_093 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_093++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1904::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Security Tower Door Unlocked
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(9) == false)) {
      aUserFlagSet(7, 1);
      aObjPlayAnim(Object_handles[9], 0, 2, 2.000000f, 0);
      aDoorLockUnlock(0, Door_handles[11]);
      aDoorActivate(Door_handles[11]);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08C1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 027: Security Tower Forcefield
    if (1) {
      aShowHUDMessage(Message_strings[5]);
      aPortalRenderSet(0, 6, Room_indexes[20], 1);
      aMatcenSetState(1, Matcen_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: Center Clamp Release Switch
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(19) == false)) {
      aObjPlayAnim(Object_handles[17], 0, 3, 3.000000f, 0);
      if (qUserFlag(11) == true) {
        aSetLevelTimer(10.000000f, 6);
        aSoundPlaySteaming("VoxL08SpecificC.osf", 1.000000f);
      } else {
        aAddGameMessage(Message_strings[12], Message_strings[11]);
        aUserFlagSet(18, 1);
      }
      aUserFlagSet(19, 1);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: Left Clamp Release Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[13]);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0910::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: Right Clamp Release Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[13]);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Right Docking Clamp Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[13]);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Center Docking Clamp Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(12) == true) {
        aObjPlayAnim(Object_handles[21], 10, 20, 1.000000f, 0);
        aShowHUDMessage(Message_strings[14]);
        aUserFlagSet(12, 0);
        aSoundPlaySteaming("VoxL08SpecificB.osf", 1.000000f);
      } else {
        aObjPlayAnim(Object_handles[21], 0, 10, 1.000000f, 0);
        aUserFlagSet(12, 1);
        aShowHUDMessage(Message_strings[15]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Left Docking Clamp Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[13]);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2853::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 039: Frigate Escape Part 2
    if (0 == event_data->goal_uid) {
      aAIGoalFollowPathSimple(Object_handles[23], Path_indexes[4], 4352, -1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: Hangar Elevator Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(11) == false) {
        aObjPlayAnim(Object_handles[24], 0, 1, 2.000000f, 0);
        aUserFlagSet(11, 1);
        aAIGoalFollowPathSimple(Object_handles[25], Path_indexes[5], 131328, -1, 3);
        aShowHUDMessage(Message_strings[16]);
        if (qUserFlag(18) == true) {
          aSetLevelTimer(10.000000f, 6);
          aSoundPlaySteaming("VoxL08SpecificC.osf", 1.000000f);
        } else {
        }
      } else {
        aShowHUDMessage(Message_strings[17]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19E2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Weapons Plant Secret Level Data
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAddObjectToInventory(Object_handles[0], event_data->it_handle, 0);
      aAddGameMessage(Message_strings[18], Message_strings[19]);
      aSoundPlay2DObj(Sound_indexes[3], event_data->it_handle, 1.000000f);
      aMissionSetSecretFlag(1);
      aUserFlagSet(20, 1);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09FB::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 047: Left Flame Purge Button
    if (1) {
      aTurnOffSpew(3);
      aTurnOffSpew(6);
      aUserVarInc(5);
      if (qUserVarValue(5) > 2.000000f) {
        aObjPlayAnim(Object_handles[27], 1, 32, 40.000000f, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09FC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 048: Right Flame Purge Button
    if (1) {
      aTurnOffSpew(5);
      aTurnOffSpew(8);
      aUserVarInc(5);
      if (qUserVarValue(5) > 2.000000f) {
        aObjPlayAnim(Object_handles[27], 1, 32, 40.000000f, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 046: Center Flame Purge Button
    if (1) {
      aTurnOffSpew(4);
      aTurnOffSpew(7);
      aUserVarInc(5);
      if (qUserVarValue(5) > 2.000000f) {
        aObjPlayAnim(Object_handles[27], 1, 32, 40.000000f, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0845::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: Outer Fan A Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0846::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Outer Fan B Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0844::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Outer Fan C Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 042: Outer Fan D Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0849::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: Middle Fan D Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0848::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: Middle Fan C Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0847::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Middle Fan B Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 079: Middle Fan A Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Inner Fan C Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 084: Inner Fan B Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Inner Fan A Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1088::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: Core Fan A Damage
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

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

    // Script 002: End Level Camera Sequence
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aStartEndlevelSequencePath(Path_indexes[2], Path_indexes[3], 13.000000f, Message_strings[1]);
      if ((qUserFlag(11) == true) && (qUserFlag(19) == true)) {
        aSoundPlaySteaming("VoxL08EndAll.osf", 1.000000f);
        if (qUserFlag(20) == true) {
          aSetLevelTimer(5.000000f, 10);
        }
      } else {
        aSoundPlaySteaming("VoxL08EndPrime.osf", 1.000000f);
        if (qUserFlag(20) == true) {
          aSetLevelTimer(5.000000f, 10);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 087: Security Tower Goal Trigger
    if (1) {
      aGoalCompleted(Goal_indexes[2], 1);
      aGoalEnableDisable(1, Goal_indexes[5]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music Hangar
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

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: Music Heatsink-4
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

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

    // Script 072: Music Heatsink-3
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

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: Music Heatsink-2
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

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Music Heatsink-1
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Music Underground-5
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

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Music Underground-4
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

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Music Underground-3
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Music Underground-2
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Music Underground-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Music Secondary-4
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Music Secondary-3
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Music Secondary-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Music Primary-3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Music Primary-2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Music Primary-1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Music Outside-6
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Music Outside-5
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Music Outside-4
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Music Outside-3
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Music Outside-2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Music Outside-1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 086: Shutting Heat Sink Doors
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[8], 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
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
NEXT_ID		94

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:HeatSinksDestroyed
5:PurgeShutdownCount
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:LeftSteamON
1:RightSteamON
2:CenterSteamON
3:FlamePurgeTorchOFF
4:CoolingSwitchON
5:OuterForcefieldSwitchON
6:MiddleForcefieldSwitchON
7:InnerForcefieldSwitchON
8:DuctForcefieldSwitchON
9:SecurityTowerDoorSwitchON
10:MaydayRecieved
11:ElevatorSwitchON
12:CenterClampSwitchON
13:DeadlyForcefieldSwitchON
14:FanReverseSwitchON
15:RegulatorLockDoorSwitchON
16:RearAccessDoorUnlockSwitchON
17:DeadlyFanDESTROYED
18:FrigateReleased
19:CenterReleaseSwitchON
20:SecretLevelDataFound
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:LeftSteamSpew
1:RightSteamSpew
2:CenterSteamSpew
3:PurgeSpewA
4:PurgeSpewB
5:PurgeSpewC
6:PurgeFlameA
7:PurgeFlameB
8:PurgeFlameC
9:OverheatingSpewerA
10:OverheatingSpewerB
11:OverheatingSpewerC
12:CollisionSpewerN
13:OverheatingSpewerE
14:OverheatingSpewerF
15:OverheatingSpewerG
16:CollisionSpewerQ
17:OverheatingSpewerI
18:OverheatingSpewerJ
19:OverheatingSpewerK
20:OverheatingSpewerL
21:CollisionSpewerT
22:OverheatingSpewerN
23:CollisionSpewerV
24:OverheatingSpewerP
25:OverheatingSpewerQ
26:OverheatingSpewerR
27:OverheatingSpewerS
28:CollisionSpewerX
29:OverheatingSpewerU
30:OverheatingSpewerV
31:OverheatingSpewerW
32:CollisionSpewerZ
33:OverheatingSpewerY
34:OverheatingSpewerZ
35:FlameSpewerA
36:FlameSpewerD
37:FlameSpewerH
38:FlameSpewerL
39:FlameSpewerN
40:FlameSpewerQ
41:FlameSpewerT
42:FlameSpewerV
43:FlameSpewerX
44:FlameSpewerZ
45:CollisionSpewerA
46:CollisionSpewerD
47:CollisionSpewerH
48:CollisionSpewerL
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:LeftSteamVentTimer
1:CenterSteamVentTimer
2:RightSteamVentTimer
3:HeatSinksDestroyedTimer
4:HighHeatTremorsTimer
5:CriticalHeatTremorsTimer
6:FrigateWaitForElevatorTimer
7:ShuttingDownHeatSinks10Timer
8:ShutHeatSinks5Timer
9:FlamesTimer
10:EndSecretVOXtimer
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:FrigateEscapePart1Complete
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
CenterUpperSteamDo
CenterLowerSteamDo
RightUpperSteamDoo
RightLowerSteamDoo
LeftUpperSteamDoor
LeftLowerSteamDoor
FarHeatSinkDoor
CoolingDuctEntranc
InnerHeatSinkDoor
MiddleHeatSinkDoor
BetweenDoor
SecurityTowerDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
WeaponsPlantData
CenterSteamSpewer
RightSteamSpewer
LeftSteamSpewer
CoolingSystemSwitc
InnerHeatSinkDevic
MiddleHeatSinkDevi
OuterHeatSinkDevic
DuctForcefieldSwit
InnerForcefieldSwi
MiddleForcefieldSw
OuterForcefieldSwi
DeadlyCoolingShaft
FanReverseSwitch
CoolingFanMechanis
SecurityTowerDoorS
SecurityTowerTurre
CenterClampRelease
LeftClampRelease
RightClampRelease
RightClampSwitch
CenterClampSwitch
LeftClampSwitch
MedicalFrigate
ElevatorSwitch
HangarElevator
LeftPurgeButton
FlamePurgeRotator
CenterPurgeButton
RightPurgeButton
CoolingControlLink
CoolingBase
OuterFanA
OuterFanB
OuterFanD
MiddleFanD
MiddleFanC
MiddleFanB
MiddleFanA
InnerFanC
InnerFanB
InnerFanA
CoreFanA
WarningLightA
WarningLightB
WarningLightC
WarningLightD
WarningLightE
WarningLightF
WarningLightG
WarningLightH
WarningLightI
WarningLightJ
WarningLightK
WarningLightL
WarningLightM
WarningLightN
WarningLightO
WarningLightP
WarningLightQ
WarningLightR
WarningLightS
FlameA
FlameD
FlameH
FlameL
FlameN
FlameQ
FlameT
FlameV
FlameX
FlameZ
OverheatingSpewerA
OverheatingSpewerB
OverheatingSpewerC
OverheatingSpewerE
OverheatingSpewerF
OverheatingSpewerG
OverheatingSpewerI
OverheatingSpewerJ
OverheatingSpewerK
OverheatingSpewerL
OverheatingSpewerN
OverheatingSpewerP
OverheatingSpewerQ
OverheatingSpewerR
OverheatingSpewerS
OverheatingSpewerU
OverheatingSpewerV
OverheatingSpewerW
OverheatingSpewerY
OverheatingSpewerZ
$$OBJECT_LIST_END

$$ROOM_LIST_START
CenterUpperSteamTu
CenterUpperSteamDo
CenterLowerSteamTu
CenterLowerSteamDo
RightUpperSteamTub
RightUpperSteamDoo
RightLowerSteamTub
RightLowestSteamTu
RightLowerSteamDoo
LeftUpperSteamTube
LeftUpperSteamDoor
LeftLowerSteamTube
LeftLowerSteamDoor
RefineryCore
ThermalRegulator
DuctForcefieldInte
InnerLowerHeatSink
MiddleLowerHeatSin
OuterLowerHeatSink
DeadlyCoolingShaft
SecurityTower
HangarControlCente
MainHangar
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EndLevelTrigger
SecurityTowerGoalTr
MHangar-1
MHeatSink-4
MHeatSink-3
MHeatSink-2
MHeatSink-1
MUnderground-5
MUnderground-4
MUnderground-3
MUnderground-2
MUnderground-1
MSecondary-4
MSecondary-3
MSecondary-2
MPrimary-3
MPrimary-2
MPrimary-1
MOutside-6
MOutside-5
MOutside-4
MOutside-3
MOutside-2
MOutside-1
InnerHeatSinkDoorSh
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbExplosionFarI
AmbExplosionFarD
AmbExplosionFarG
Powerup pickup
AmbSirenIntense
$$SOUND_LIST_END

$$TEXTURE_LIST_START
P-MonTempBelo
Bluedatascrollup
P-MonCoolingEng
P-MonTempAbov
P-MonTempCrit
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCameraPath
IntroPlayerPath
EndLevelCameraPath
EndLevelPlayerPath
FrigateEscapePart2Path
ElevatorPath
FrigateEscapePath
$$PATH_LIST_END

$$MATCEN_LIST_START
SecurityTowerMatcen
$$MATCEN_LIST_END

$$GOAL_LIST_START
Activate the Cooling System
Destroy the Outer Heat Sink
Make your way through the Refinery Core
Destroy the Inner Heat Sink
Destroy the Middle Heat Sink
Find a way out of the facility
Rescue medical frigate Nightingale
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL08StartLevel.osf
VoxL08EndAll.osf
VoxL08EndPrime.osf
VoxL08SpecificA.osf
VoxL08SpecificC.osf
VoxL08SpecificB.osf
VoxL08Secret.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Let It Snow, Let It Snow, Let It Snow...
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSnowTurnOn
                        $$CHILD_BLOCK_START
                        10:9:1.000000:Density
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Intro Camera Sequence
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
                        10:16:0:CameraPath
                        10:8:IntroCamera:Text
                        10:1:0:0:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:End Level Camera Sequence
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
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:16:3:PlayerPath
                        10:6:13.000000:Time
                        10:8:EndLevel:Text
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
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
                                                10:10:0:19:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:1:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:20:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:5.000000:Time
                                        10:10:0:10:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:2:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:20:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:5.000000:Time
                                        10:10:0:10:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Center Steam Vent OVERHEATING!
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
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:30.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:6:18.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:18.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:18.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:10.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Center Steam Vent
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
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:10.000000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:20.000000:BlobSize
                                10:6:80.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:2:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:10.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:6.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:6.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:6.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:10.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:10.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:10.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:10.000000:Speed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:2:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:10.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
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
        $$CHILD_BLOCK_END
00:15:Right Steam Vent OVERHEATING!
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
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:45.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:27.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:27.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:27.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:27.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:2:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:3:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:10.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Right Steam Vent
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
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:2:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:10.000000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:20.000000:BlobSize
                                10:6:80.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:3:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:9.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:9.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:9.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:9.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:4:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:3:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:2:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:4:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Left Steam Vent OVERHEATING!
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
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:9:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:10:Room
                        10:6:9.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:9.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:9.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:4:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:5:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:10.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Left Steam Vent
        $$CHILD_BLOCK_START
        01:2:0
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
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:10.000000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:20.000000:BlobSize
                                10:6:80.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:0:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:15.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:5:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:4:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:6:3.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:6:3.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:6:3.000000:Damage
                                10:10:0:4:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:5.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:5.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:5.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:9:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:5.000000:Speed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aTurnOffSpew
                                $$CHILD_BLOCK_START
                                10:10:0:0:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:15.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:5:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:4:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:9:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Center Steam Vent Start
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
                        10:10:0:2:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Right Steam Vent Start
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
                        10:10:0:1:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Left Steam Vent Start
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
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:15.000000:Time
                        10:10:0:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Thermal Regulation Center
        $$CHILD_BLOCK_START
        01:1:4
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
                                        10:10:0:4:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:4:0:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CoolingSystemEngaged:Message
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:13:Room
                                10:4:78:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:13:Room
                                10:4:101:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:14:Room
                                10:4:148:FaceNum
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:14:Room
                                10:4:136:FaceNum
                                10:14:1:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:14:Room
                                10:4:157:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetDamage
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:Damage
                                10:10:0:0:DamageSoundType
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:9:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:4:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:5:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:12:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:0.000000:Z
                                10:6:1.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:6:Door
                                10:9:1.000000:Position
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:1:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CoolingSystemClock:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Inner Heat Sink Destroyed
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
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:4:78:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:4:101:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:4:148:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:0.250000:Red
                        10:6:0.500000:Green
                        10:6:1.000000:Blue
                        10:6:2000.000000:Depth
                        10:6:120.000000:Time
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ALLHeatSinksDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Middle Heat Sink Destroyed
        $$CHILD_BLOCK_START
        01:1:6
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Outer Heat Sink Destroyed
        $$CHILD_BLOCK_START
        01:1:7
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Cooling Duct Forcefield Disabled
        $$CHILD_BLOCK_START
        01:1:8
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
                                        10:10:0:8:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:3:PortalNum
                        10:2:15:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Inner Heat Sink Forcefield Disabled
        $$CHILD_BLOCK_START
        01:1:9
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
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:16:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Middle Heat Sink Forcefield Disabled
        $$CHILD_BLOCK_START
        01:1:10
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
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:17:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:8:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Outer Heat Sink Forcefield Disabled
        $$CHILD_BLOCK_START
        01:1:11
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
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:1:PortalNum
                        10:2:18:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:9:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Core Temperature Above Normal!
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:75.000000:Amount
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CoreTempAboveNormal:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Random Tremors due to CRITICAL Heat!
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:30.000000:LowerLimit
                                10:6:90.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:50.000000:LowerLimit
                                10:6:100.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Random Tremors due to High Heat!
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:45.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:50.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Deadly Cooling Shaft Fan Kills Player!
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:50.000000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Deadly Cooling Shaft Reverse Switch
        $$CHILD_BLOCK_START
        01:1:13
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
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:0.000000:X
                                10:6:1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                10:6:10.000000:Time
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:13:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FanReverseSwitch:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aRoomChangeWind
                                $$CHILD_BLOCK_START
                                10:2:19:Room
                                10:6:0.000000:X
                                10:6:-1.000000:Y
                                10:6:0.000000:Z
                                10:6:15.000000:Speed
                                10:6:10.000000:Time
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:13:Object
                                10:4:1:StartFrame
                                10:4:2:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Deadly Fan Gets Shot By Player
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:6:1000000000.000000:Shields
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CoolFanInvulnerable:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:93:Deadly Fan Controller Kills Bots...
        $$CHILD_BLOCK_START
        01:1:14
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qObjIsType:Bool
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:10:0:2:ObjectType
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:1000000000.000000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Deadly Fan Controller
        $$CHILD_BLOCK_START
        01:1:12
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        07:1:0
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:120.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:4:78:FaceNum
                        10:14:4:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:4:101:FaceNum
                        10:14:4:Texture
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:4:148:FaceNum
                        10:14:4:Texture
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:1:Lock/Unlock
                        10:0:0:7:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:10:DoorName
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CoolFanDestroyed:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Security Tower Door Unlocked
        $$CHILD_BLOCK_START
        01:1:15
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:0:StartFrame
                        10:4:2:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:11:DoorName
                        $$CHILD_BLOCK_END
                08:aDoorActivate
                        $$CHILD_BLOCK_START
                        10:0:0:11:Door
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Security Tower Goal Trigger
        $$CHILD_BLOCK_START
        01:0:1
        02:1
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
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:5:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Security Tower Forcefield
        $$CHILD_BLOCK_START
        01:1:16
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ForcefieldDisabled:Message
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:6:PortalNum
                        10:2:20:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Medical Frigate Mayday!
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:21:Room
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:Mayday:GameMessage
                        10:8:MessageFromFrigate:HUDMessage
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:6:LevelGoal
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Center Clamp Release Switch
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:19:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:10.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:4:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAddGameMessage
                                $$CHILD_BLOCK_START
                                10:8:ElevatorNeedsDown:GameMessage
                                10:8:MessageFromFrigate:HUDMessage
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:18:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:19:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Left Clamp Release Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ClampNotInUse:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Right Clamp Release Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ClampNotInUse:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Right Docking Clamp Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ClampNotInUse:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Center Docking Clamp Switch
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
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:4:10:StartFrame
                                10:4:20:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CenterClampDisengaged:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:5:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:4:0:StartFrame
                                10:4:10:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:EngagingCenterClamp:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Left Docking Clamp Switch
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ClampNotInUse:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Center Clamp Switch Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:4:10:StartFrame
                        10:4:10:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Frigate Escape Part 2
        $$CHILD_BLOCK_START
        01:1:23
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
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:4:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Hangar Elevator Switch
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
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:24:Object
                                10:4:0:StartFrame
                                10:4:1:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:25:Object
                                10:16:5:Path
                                10:15:131328:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ElevatorDOWN:Message
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:18:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:10.000000:Time
                                        10:10:0:6:TimerID
                                        $$CHILD_BLOCK_END
                                08:aSoundPlaySteaming
                                        $$CHILD_BLOCK_START
                                        10:19:4:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:DO NOTHING
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ElevatorAlreadyDown:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Weapons Plant Secret Level Data
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:WeaponsPlantData:GameMessage
                        10:8:FoundSecretData:HUDMessage
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMissionSetSecretFlag
                        $$CHILD_BLOCK_START
                        10:5:1:State
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:20:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Purge Button Attach Starts
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:26:Child
                        10:4:0:ChildPoint
                        10:1:0:27:Parent
                        10:4:0:ParentPoint
                        $$CHILD_BLOCK_END
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:28:Child
                        10:4:0:ChildPoint
                        10:1:0:27:Parent
                        10:4:1:ParentPoint
                        $$CHILD_BLOCK_END
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:29:Child
                        10:4:0:ChildPoint
                        10:1:0:27:Parent
                        10:4:2:ParentPoint
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:1:StartFrame
                        10:4:32:EndFrame
                        10:6:40.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Flame Purge Flames
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
                        10:1:0:27:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.080000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.080000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:2:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.080000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:2:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:10.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Left Flame Purge Button
        $$CHILD_BLOCK_START
        01:1:26
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
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
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:4:1:StartFrame
                                10:4:32:EndFrame
                                10:6:40.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Right Flame Purge Button
        $$CHILD_BLOCK_START
        01:1:29
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:8:SpewHandle
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
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
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:4:1:StartFrame
                                10:4:32:EndFrame
                                10:6:40.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Center Flame Purge Button
        $$CHILD_BLOCK_START
        01:1:28
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:7:SpewHandle
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
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
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:4:1:StartFrame
                                10:4:32:EndFrame
                                10:6:40.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Music Init
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
00:50:Music OutsideInit
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Music Hangar
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
                        10:10:0:6:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Music Heatsink-4
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
00:72:Music Heatsink-3
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
00:71:Music Heatsink-2
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Music Heatsink-1
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Music Underground-5
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
00:68:Music Underground-4
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
00:67:Music Underground-3
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Music Underground-2
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
00:65:Music Underground-1
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
00:64:Music Secondary-4
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Music Secondary-3
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Music Secondary-2
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Music Primary-3
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Music Primary-2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Music Primary-1
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Music Outside-6
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Music Outside-5
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Music Outside-4
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Music Outside-3
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Music Outside-2
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Music Outside-1
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:Cooling Shaft Starts
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:30:Child
                        10:4:0:ChildPoint
                        10:1:0:31:Parent
                        10:4:0:ParentPoint
                        $$CHILD_BLOCK_END
                08:aAttachExistingObject
                        $$CHILD_BLOCK_START
                        10:1:0:14:Child
                        10:4:0:ChildPoint
                        10:1:0:30:Parent
                        10:4:1:ParentPoint
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:10.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Frigate Waits For Elevator Timer
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:FrigateSaved:GameMessage
                        10:8:MessageFromFrigate:HUDMessage
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:22:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:6:Path
                        10:15:131328:AIGoalFlags
                        10:10:0:0:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aMissionSetFlag
                        $$CHILD_BLOCK_START
                        10:4:28:FlagNum
                        10:5:1:State
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Outer Fan A Damage
        $$CHILD_BLOCK_START
        01:1:32
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Outer Fan B Damage
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Outer Fan C Damage
        $$CHILD_BLOCK_START
        01:1:34
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Outer Fan D Damage
        $$CHILD_BLOCK_START
        01:1:34
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Middle Fan D Damage
        $$CHILD_BLOCK_START
        01:1:35
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Middle Fan C Damage
        $$CHILD_BLOCK_START
        01:1:36
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Middle Fan B Damage
        $$CHILD_BLOCK_START
        01:1:37
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Middle Fan A Damage
        $$CHILD_BLOCK_START
        01:1:38
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Inner Fan C Damage
        $$CHILD_BLOCK_START
        01:1:39
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Inner Fan B Damage
        $$CHILD_BLOCK_START
        01:1:40
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Inner Fan A Damage
        $$CHILD_BLOCK_START
        01:1:41
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Core Fan A Damage
        $$CHILD_BLOCK_START
        01:1:42
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
                08:aObjApplyDamage
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:0.250000:DamageAmount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Shutting Heat Sink Doors
        $$CHILD_BLOCK_START
        01:0:24
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
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:8:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Warning Lights & Sirens!!!!!!
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
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:6:70.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:43:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:44:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:45:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:46:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:47:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:48:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:49:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:50:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:51:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:52:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:53:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:54:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:55:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:56:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:57:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:58:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:59:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:60:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:61:Object
                        10:9:0.750000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Warning Lights Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:61:Object
                        10:6:0.000000:Distance
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
                        10:10:0:1:Ghost/Unghost
                        10:1:0:71:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:High Heat Steam Spewers
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:9:SpewHandle
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
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:10:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:11:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:13:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:14:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:15:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:17:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:18:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:80:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:19:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:81:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:20:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:82:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:22:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:24:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:84:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:25:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:26:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:27:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:29:SpewHandle
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
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:30:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:89:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:31:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:90:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:33:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:91:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:34:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Critical Heat Flame Spewers REAL!
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:35:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:36:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:37:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:38:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:39:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:40:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:41:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:42:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:43:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:44:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:45:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:46:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:47:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:48:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:12:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:16:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:21:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:23:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:28:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:4:0:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:0:PhysicsFlags
                        10:5:1:IsRealObject
                        10:6:3.000000:BlobLifetime
                        10:6:1.000000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:32:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:91:Found Main Hangar, Still Need Passkey
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qRoomHasPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:2:22:Room
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:92:End Level Secret Level VOX
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
                        10:19:6:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
