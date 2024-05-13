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
// Filename:	Merc6.cpp
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

#define ID_CUSTOM_OBJECT_1006 0x001
#define ID_CUSTOM_OBJECT_0841 0x002
#define ID_CUSTOM_OBJECT_0840 0x003
#define ID_CUSTOM_OBJECT_0864 0x004
#define ID_CUSTOM_OBJECT_186D 0x005
#define ID_CUSTOM_OBJECT_20A3 0x006
#define ID_CUSTOM_OBJECT_08A5 0x007
#define ID_CUSTOM_OBJECT_08A6 0x008
#define ID_CUSTOM_OBJECT_08A7 0x009
#define ID_CUSTOM_OBJECT_403E 0x00a
#define ID_CUSTOM_OBJECT_783F 0x00b
#define ID_CUSTOM_OBJECT_1084 0x00c
#define ID_CUSTOM_OBJECT_0885 0x00d
#define ID_CUSTOM_OBJECT_1086 0x00e
#define ID_CUSTOM_OBJECT_2046 0x00f
#define ID_CUSTOM_OBJECT_08A8 0x010
#define ID_CUSTOM_OBJECT_08A9 0x011
#define ID_CUSTOM_OBJECT_08B9 0x012
#define ID_CUSTOM_OBJECT_5847 0x013
#define ID_CUSTOM_OBJECT_1048 0x014
#define ID_CUSTOM_OBJECT_104A 0x015
#define ID_CUSTOM_OBJECT_108E 0x016
#define ID_CUSTOM_OBJECT_1827 0x017

#define ID_TRIGGER_001A 0x018
#define ID_TRIGGER_0007 0x019
#define ID_TRIGGER_0000 0x01a
#define ID_TRIGGER_0001 0x01b
#define ID_TRIGGER_0002 0x01c
#define ID_TRIGGER_0003 0x01d
#define ID_TRIGGER_0004 0x01e
#define ID_TRIGGER_0005 0x01f
#define ID_TRIGGER_0006 0x020
#define ID_TRIGGER_0008 0x021
#define ID_TRIGGER_0009 0x022
#define ID_TRIGGER_000A 0x023
#define ID_TRIGGER_000B 0x024
#define ID_TRIGGER_000C 0x025
#define ID_TRIGGER_000D 0x026
#define ID_TRIGGER_000E 0x027
#define ID_TRIGGER_000F 0x028
#define ID_TRIGGER_0010 0x029
#define ID_TRIGGER_0011 0x02a
#define ID_TRIGGER_0018 0x02b
#define ID_TRIGGER_0019 0x02c
#define ID_TRIGGER_0014 0x02d
#define ID_TRIGGER_0015 0x02e
#define ID_TRIGGER_0016 0x02f
#define ID_TRIGGER_0017 0x030

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

class CustomObjectScript_1006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0841 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0840 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0864 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_186D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20A3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_403E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_783F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1084 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0885 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1086 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2046 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_5847 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1048 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_104A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_108E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1827 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
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

class TriggerScript_000D : public BaseScript {
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

class TriggerScript_0011 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0019 : public BaseScript {
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

class TriggerScript_0016 : public BaseScript {
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

static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_027 = 0;
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
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_027 = 0;
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
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
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
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

#include "AIGame3_External.h"

/*
$$ENUM Region
0:PTMCmine
1:PTMChangar
2:TerrainOne
3:TerrainTwo
4:CEDBase
$$END
*/

/*
$$ACTION
Custom
For [o:Barge], set [o:Follow Handle], [f:Stop Distance], [f:Slowdown Offset]
aCCSetData
Sets Crowd Control Data

Parameters:
        Barge: the barge object
        Follow Handle: the object to follow and not crowd
        Stop Distance: the distance to stop completely at
        Slowdown Offset: the added distance to start slowing down at
$$END
*/
void aCCSetData(int obj_handle, int follow_handle, float stop_dist, float slowdown_offset) {
  cc_packet data;

  if (!qObjExists(obj_handle))
    return;

  data.follow_handle = follow_handle;
  data.stop_dist = stop_dist;
  data.slowdown_offset = slowdown_offset;

  SendCommand(obj_handle, obj_handle, CC_COM_SET_DATA, &data);
}

/*
$$ACTION
Custom
For [o:Barge], disable crowd control
aCCDisable
Disables Crowd Control

Parameters:
        Barge: the barge object
$$END
*/
void aCCDisable(int obj_handle) {
  bool disable = true;

  if (!qObjExists(obj_handle))
    return;

  SendCommand(obj_handle, obj_handle, CC_COM_DISABLE_CHECK, &disable);
}

/*
$$ACTION
Custom
For [o:Barge], enable crowd control
aCCEnable
Disables Crowd Control

Parameters:
        Barge: the barge object
$$END
*/
void aCCEnable(int obj_handle) {
  bool disable = false;

  if (!qObjExists(obj_handle))
    return;

  SendCommand(obj_handle, obj_handle, CC_COM_DISABLE_CHECK, &disable);
}

/*
$$ACTION
Custom
Display room that [o:Object] is in
aDisplayObjRoom
Displays Room object is in

Parameters:
  Object: the object
$$END
*/
void aDisplayObjRoom(int objhandle) {
  int room;

  if (!qObjExists(objhandle))
    return;

  Obj_Value(objhandle, VF_GET, OBJV_I_ROOMNUM, &room);

  mprintf(0, "Object is in room %d\n", room);
}

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
Make [o:Object] target [o:Target] or [o:Alternate1] or [o:Alternate2]
aSetTargeting
Make Object target something

Parameters:
  Object: the object to assign a target to
$$END
*/
void aSetTargeting(int objhandle, int target, int alternate1, int alternate2) {
  int flags;
  int target_handle = OBJECT_HANDLE_NONE;

  // Make sure the object in question exists
  if (!qObjExists(objhandle))
    return;

  // See if any of the targets are available
  if (qObjExists(target)) {
    target_handle = target;
  } else if (qObjExists(alternate1)) {
    target_handle = alternate1;
  } else if (qObjExists(alternate2)) {
    target_handle = alternate2;
  }

  // If we have a valid target, use it
  if (target_handle != OBJECT_HANDLE_NONE) {
    // Set the target handle
    aAISetTarget(objhandle, target_handle);

    // Disable auto-targeting
    flags = AIF_DETERMINE_TARGET;
    AI_Value(objhandle, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);

    // Enable Force awareness
    flags = AIF_FORCE_AWARENESS;
    AI_Value(objhandle, VF_SET_FLAGS, AIV_I_FLAGS, &flags);
  } else {
    // Re-enable auto-targeting
    flags = AIF_DETERMINE_TARGET;
    AI_Value(objhandle, VF_SET_FLAGS, AIV_I_FLAGS, &flags);

    // Turn off Force awareness
    flags = AIF_FORCE_AWARENESS;
    AI_Value(objhandle, VF_CLEAR_FLAGS, AIV_I_FLAGS, &flags);
  }
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

#define NUM_DOOR_NAMES 3
static const char *const Door_names[NUM_DOOR_NAMES] = {"PTMCminedoor", "MainBaseDoor", "ReactorDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 58
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Ambusher1A",
                                                           "Ambusher1B",
                                                           "Ambusher2A",
                                                           "Ambusher2B",
                                                           "Ambusher2C",
                                                           "Ambusher4A",
                                                           "Ambusher4B",
                                                           "Ambusher4C",
                                                           "HoodAmbusher",
                                                           "MiniBoss1",
                                                           "MiniBoss2",
                                                           "MiniBoss3",
                                                           "Data 01",
                                                           "Data 02",
                                                           "Data 03",
                                                           "Data 04",
                                                           "Backup1",
                                                           "Backup2",
                                                           "Ambusher5",
                                                           "Boss Crate 01",
                                                           "Boss Crate 02",
                                                           "Boss Crate 03",
                                                           "Welder 01",
                                                           "Welder 02",
                                                           "Welder 03",
                                                           "Welder 04",
                                                           "CED Reactor",
                                                           "EndBlastCam",
                                                           "Gadget 01",
                                                           "Gadget 02",
                                                           "Gadget03",
                                                           "Dravis Door",
                                                           "PTMChangarcontrol",
                                                           "HangarMatcenContro",
                                                           "Barge 01",
                                                           "Barge 02",
                                                           "Barge 03",
                                                           "HangarFFControl",
                                                           "Ambush1Trigger",
                                                           "Ambush2Trigger",
                                                           "Ambush4Trigger",
                                                           "Ambush5Trigger",
                                                           "FailsafeTerminal",
                                                           "GreenOrb",
                                                           "CEDfoyer",
                                                           "TTLoadSwitch",
                                                           "Big Wheel",
                                                           "TTTurnSwitch",
                                                           "TTUnloadSwitch",
                                                           "ReactorDoorSwitch",
                                                           "TopCam",
                                                           "BottomCam",
                                                           "SideCam1",
                                                           "SideCam2",
                                                           "SideCam3",
                                                           "ReactorDeathCamA",
                                                           "ReactorDeathCamB",
                                                           "MonitorSpew"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 13
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "PTMC control room",  "PTMC Loading Force", "TTLoadFFRoom",      "CEDBaseEntrance", "Wheel Control Room",
    "TTUnloadFFRoom",     "CED reactor room",   "FlashRoom1",        "Failsafe Room",   "CED fight room mai",
    "CED fight room lef", "CED fight room rig", "CED fight room top"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 25
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EnteredLoadingArea", "PTMCminemusic",      "PTMChangarmusic",    "PTMC2terrain01",     "PTMC2terrain02",
    "PTMC2terrain03",     "PTMC2terrain04",     "PTMC2terrain05",     "PTMC2terrain06",     "terrain to PTMC 01",
    "terrain to PTMC 02", "terrain to PTMC 03", "terrain to PTMC 04", "terrain to PTMC 05", "terrain to PTMC 06",
    "CEDbase 01",         "CEDbase 02",         "CEDbase03",          "CEDbase 04",         "CED to terrain 05",
    "CED to terrain 06",  "CED to terrain 01",  "CED to terrain 02",  "CED to terrain 03",  "CED to terrain 04"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 7
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbDroneReactor", "Powerup pickup",   "AmbMonitorProcessing",
                                                         "AmbSwitch31",     "AmbInVolcanoLava", "AmbDroneHallway",
                                                         "Merc4Rumble"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 5
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"PTMClogoON", "M06_ForcefieldDisabled", "PTMClogooff",
                                                             "FunkyEffect7", "FunkyEffect4"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 27
static const char *const Path_names[NUM_PATH_NAMES] = {
    "IntroCamPath",   "IntroPlayerPath", "LifterToBox1",   "LifterToBarge1", "LifterToBox2Dest", "LifterToBox3Dest",
    "LifterToBox2",   "LifterToBox3",    "LifterFinished", "PTMCbargepath",  "CEDbargepath",     "Ambusher1Path",
    "Ambusher1BPath", "Ambusher2Path",   "Ambusher2B",     "Ambusher2C",     "Ambusher4Path",    "Ambusher4BPath",
    "Ambusher4CPath", "HoodAmbushPath",  "MiniBoss1Path",  "MiniBoss3Path",  "MiniBoss2Path",    "Backup1Path",
    "Backup2Path",    "EndCamPath",      "EndPlayerPath"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 10
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {
    "CED fight left 01",  "CED fight left 02",   "CED fight left 03", "CED fight right 01", "CED fight right 02",
    "CED fight top left", "CED fight top right", "Matcen 2",          "CED fight right 03", "Matcen 3"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 14
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Destroy Welder Bots",
                                                       "Obtain Maintenance Access Cards",
                                                       "Enter PTMC Loading Area",
                                                       "Load Cargo onto Barges",
                                                       "Disable Cargo Hold Forcefield",
                                                       "Load Cargo onto Turn Table",
                                                       "Protect Cargo Enroute to Base",
                                                       "Destroy Tower Operators",
                                                       "Unload Cargo from Turn Table",
                                                       "Align Turn Table with Base",
                                                       "Force Open Outer Reactor Door",
                                                       "Engage Reactor Diagnostics",
                                                       "Destroy Reactor",
                                                       "Escape"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 40
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroText",
                                                             "Killwelders",
                                                             "DravisDoor",
                                                             "PTMCminedoor",
                                                             "Maintenance",
                                                             "HangarMatcen",
                                                             "CargoLoaded",
                                                             "PTMCforcefiledDown",
                                                             "CargoNotLoaded",
                                                             "ProtectCargo",
                                                             "CargoAtTT",
                                                             "CargoOnTT",
                                                             "CargoAtBase",
                                                             "ProtectCargo2",
                                                             "ProtectCargo3",
                                                             "CargoDestroyed",
                                                             "CargoDestroyed2",
                                                             "CargoDestroyed3",
                                                             "Ambush2",
                                                             "Ambush1",
                                                             "CEDBaseFFDown",
                                                             "ControlFFDown",
                                                             "Ambush3",
                                                             "TTLoading",
                                                             "NoTTCargo",
                                                             "SwitchHitFromOutside",
                                                             "NoCargoOnTT",
                                                             "OutOfAlign",
                                                             "TTUnloading",
                                                             "WrongWheelPos",
                                                             "LetsRock",
                                                             "BackupDeployed",
                                                             "Backup1",
                                                             "Backup2",
                                                             "Backup3",
                                                             "Backup4",
                                                             "ReactorSwitchHit",
                                                             "ReactorDoorOpening",
                                                             "ReactorBlownMessage",
                                                             "Empty"};
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
    strcpy(filename, "Merc6.msg");
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
  case ID_CUSTOM_OBJECT_1006:
    return new CustomObjectScript_1006;
    break;
  case ID_CUSTOM_OBJECT_0841:
    return new CustomObjectScript_0841;
    break;
  case ID_CUSTOM_OBJECT_0840:
    return new CustomObjectScript_0840;
    break;
  case ID_CUSTOM_OBJECT_0864:
    return new CustomObjectScript_0864;
    break;
  case ID_CUSTOM_OBJECT_186D:
    return new CustomObjectScript_186D;
    break;
  case ID_CUSTOM_OBJECT_20A3:
    return new CustomObjectScript_20A3;
    break;
  case ID_CUSTOM_OBJECT_08A5:
    return new CustomObjectScript_08A5;
    break;
  case ID_CUSTOM_OBJECT_08A6:
    return new CustomObjectScript_08A6;
    break;
  case ID_CUSTOM_OBJECT_08A7:
    return new CustomObjectScript_08A7;
    break;
  case ID_CUSTOM_OBJECT_403E:
    return new CustomObjectScript_403E;
    break;
  case ID_CUSTOM_OBJECT_783F:
    return new CustomObjectScript_783F;
    break;
  case ID_CUSTOM_OBJECT_1084:
    return new CustomObjectScript_1084;
    break;
  case ID_CUSTOM_OBJECT_0885:
    return new CustomObjectScript_0885;
    break;
  case ID_CUSTOM_OBJECT_1086:
    return new CustomObjectScript_1086;
    break;
  case ID_CUSTOM_OBJECT_2046:
    return new CustomObjectScript_2046;
    break;
  case ID_CUSTOM_OBJECT_08A8:
    return new CustomObjectScript_08A8;
    break;
  case ID_CUSTOM_OBJECT_08A9:
    return new CustomObjectScript_08A9;
    break;
  case ID_CUSTOM_OBJECT_08B9:
    return new CustomObjectScript_08B9;
    break;
  case ID_CUSTOM_OBJECT_5847:
    return new CustomObjectScript_5847;
    break;
  case ID_CUSTOM_OBJECT_1048:
    return new CustomObjectScript_1048;
    break;
  case ID_CUSTOM_OBJECT_104A:
    return new CustomObjectScript_104A;
    break;
  case ID_CUSTOM_OBJECT_108E:
    return new CustomObjectScript_108E;
    break;
  case ID_CUSTOM_OBJECT_1827:
    return new CustomObjectScript_1827;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
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
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
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
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
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
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
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
  case ID_CUSTOM_OBJECT_1006:
    delete ((CustomObjectScript_1006 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0841:
    delete ((CustomObjectScript_0841 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0840:
    delete ((CustomObjectScript_0840 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0864:
    delete ((CustomObjectScript_0864 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_186D:
    delete ((CustomObjectScript_186D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20A3:
    delete ((CustomObjectScript_20A3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A5:
    delete ((CustomObjectScript_08A5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A6:
    delete ((CustomObjectScript_08A6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A7:
    delete ((CustomObjectScript_08A7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_403E:
    delete ((CustomObjectScript_403E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_783F:
    delete ((CustomObjectScript_783F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1084:
    delete ((CustomObjectScript_1084 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0885:
    delete ((CustomObjectScript_0885 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1086:
    delete ((CustomObjectScript_1086 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2046:
    delete ((CustomObjectScript_2046 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A8:
    delete ((CustomObjectScript_08A8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A9:
    delete ((CustomObjectScript_08A9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B9:
    delete ((CustomObjectScript_08B9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_5847:
    delete ((CustomObjectScript_5847 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1048:
    delete ((CustomObjectScript_1048 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_104A:
    delete ((CustomObjectScript_104A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_108E:
    delete ((CustomObjectScript_108E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1827:
    delete ((CustomObjectScript_1827 *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
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
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
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
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
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
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
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
  case ID_CUSTOM_OBJECT_1006:
  case ID_CUSTOM_OBJECT_0841:
  case ID_CUSTOM_OBJECT_0840:
  case ID_CUSTOM_OBJECT_0864:
  case ID_CUSTOM_OBJECT_186D:
  case ID_CUSTOM_OBJECT_20A3:
  case ID_CUSTOM_OBJECT_08A5:
  case ID_CUSTOM_OBJECT_08A6:
  case ID_CUSTOM_OBJECT_08A7:
  case ID_CUSTOM_OBJECT_403E:
  case ID_CUSTOM_OBJECT_783F:
  case ID_CUSTOM_OBJECT_1084:
  case ID_CUSTOM_OBJECT_0885:
  case ID_CUSTOM_OBJECT_1086:
  case ID_CUSTOM_OBJECT_2046:
  case ID_CUSTOM_OBJECT_08A8:
  case ID_CUSTOM_OBJECT_08A9:
  case ID_CUSTOM_OBJECT_08B9:
  case ID_CUSTOM_OBJECT_5847:
  case ID_CUSTOM_OBJECT_1048:
  case ID_CUSTOM_OBJECT_104A:
  case ID_CUSTOM_OBJECT_108E:
  case ID_CUSTOM_OBJECT_1827:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0016:
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
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0017;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[23];
  static int cust_id_list[23] = {
      ID_CUSTOM_OBJECT_1006, ID_CUSTOM_OBJECT_0841, ID_CUSTOM_OBJECT_0840, ID_CUSTOM_OBJECT_0864, ID_CUSTOM_OBJECT_186D,
      ID_CUSTOM_OBJECT_20A3, ID_CUSTOM_OBJECT_08A5, ID_CUSTOM_OBJECT_08A6, ID_CUSTOM_OBJECT_08A7, ID_CUSTOM_OBJECT_403E,
      ID_CUSTOM_OBJECT_783F, ID_CUSTOM_OBJECT_1084, ID_CUSTOM_OBJECT_0885, ID_CUSTOM_OBJECT_1086, ID_CUSTOM_OBJECT_2046,
      ID_CUSTOM_OBJECT_08A8, ID_CUSTOM_OBJECT_08A9, ID_CUSTOM_OBJECT_08B9, ID_CUSTOM_OBJECT_5847, ID_CUSTOM_OBJECT_1048,
      ID_CUSTOM_OBJECT_104A, ID_CUSTOM_OBJECT_108E, ID_CUSTOM_OBJECT_1827};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[31];
  cust_handle_list[1] = Object_handles[22];
  cust_handle_list[2] = Object_handles[23];
  cust_handle_list[3] = Object_handles[24];
  cust_handle_list[4] = Object_handles[25];
  cust_handle_list[5] = Object_handles[12];
  cust_handle_list[6] = Object_handles[13];
  cust_handle_list[7] = Object_handles[14];
  cust_handle_list[8] = Object_handles[15];
  cust_handle_list[9] = Object_handles[33];
  cust_handle_list[10] = Object_handles[37];
  cust_handle_list[11] = Object_handles[19];
  cust_handle_list[12] = Object_handles[20];
  cust_handle_list[13] = Object_handles[21];
  cust_handle_list[14] = Object_handles[28];
  cust_handle_list[15] = Object_handles[29];
  cust_handle_list[16] = Object_handles[30];
  cust_handle_list[17] = Object_handles[8];
  cust_handle_list[18] = Object_handles[45];
  cust_handle_list[19] = Object_handles[47];
  cust_handle_list[20] = Object_handles[48];
  cust_handle_list[21] = Object_handles[49];
  cust_handle_list[22] = Object_handles[26];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 23;
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

    // Script 066: Check Number of Welders Killed
    if ((ScriptActionCtr_066 < 1) && (qUserVarValueInt(4) == 4)) {
      aGoalCompleted(Goal_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }

    // Script 005: Check Number of Cards Picked Up
    if ((ScriptActionCtr_005 < 1) && (qUserVarValueInt(0) == 4)) {
      aDoorLockUnlock(0, Door_handles[0]);
      aShowHUDMessage(Message_strings[3]);
      aGoalCompleted(Goal_indexes[1], 1);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 023: All gadgets dead so drop forcefield
    if ((ScriptActionCtr_023 < 1) && (qUserVarValue(2) == 3.000000f)) {
      aPortalRenderSet(0, 0, Room_indexes[4], 1);
      aGoalCompleted(Goal_indexes[7], 1);
      aShowHUDMessage(Message_strings[21]);
      aSoundPlayObject(Sound_indexes[2], Object_handles[42], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[43], 1.000000f);
      aSoundPlayObject(Sound_indexes[5], Object_handles[44], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 068: Check if Turn Table is Aligned
    if (qGoalCompleted(Goal_indexes[8]) == false) {
      if ((qUserVarValue(3) == 4.000000f) && (qObjAnimFrame(Object_handles[46]) == 3.000000f)) {
        if (qGoalCompleted(Goal_indexes[9]) == false) {
          aGoalCompleted(Goal_indexes[9], 1);
        }
      } else {
        if (qGoalCompleted(Goal_indexes[9]) == true) {
          aShowHUDMessage(Message_strings[27]);
          aGoalCompleted(Goal_indexes[9], 0);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 001: Level Start - Init Flags and Variables
    if ((ScriptActionCtr_001 < 1) && (1)) {
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aUserFlagSet(6, 0);
      aUserFlagSet(7, 0);
      aUserFlagSet(8, 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(11, 0);
      aUserFlagSet(12, 0);
      aUserFlagSet(16, 0);
      aUserFlagSet(13, 0);
      aUserFlagSet(14, 0);
      aUserFlagSet(17, 0);
      aUserFlagSet(15, 1);
      aUserVarSet(4, 0.000000f);
      aUserVarSet(0, 0.000000f);
      aUserVarSet(1, 1.000000f);
      aUserVarSet(2, 0.000000f);
      aUserVarSet(3, 1.000000f);
      aUserVarSet(5, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 052: Level Start - Misc
    if ((ScriptActionCtr_052 < 1) && (1)) {
      aMatcenSetEnableState(0, Matcen_indexes[0]);
      aMatcenSetEnableState(0, Matcen_indexes[1]);
      aMatcenSetEnableState(0, Matcen_indexes[2]);
      aMatcenSetEnableState(0, Matcen_indexes[3]);
      aMatcenSetEnableState(0, Matcen_indexes[4]);
      aMatcenSetEnableState(0, Matcen_indexes[4]);
      aMatcenSetEnableState(0, Matcen_indexes[5]);
      aMatcenSetEnableState(0, Matcen_indexes[6]);
      aObjGhostSet(1, Object_handles[0]);
      aObjGhostSet(1, Object_handles[1]);
      aObjGhostSet(1, Object_handles[2]);
      aObjGhostSet(1, Object_handles[3]);
      aObjGhostSet(1, Object_handles[4]);
      aObjGhostSet(1, Object_handles[5]);
      aObjGhostSet(1, Object_handles[6]);
      aObjGhostSet(1, Object_handles[7]);
      aObjGhostSet(1, Object_handles[8]);
      aObjGhostSet(1, Object_handles[9]);
      aObjGhostSet(1, Object_handles[10]);
      aObjGhostSet(1, Object_handles[11]);
      aObjGhostSet(1, Object_handles[12]);
      aObjGhostSet(1, Object_handles[13]);
      aObjGhostSet(1, Object_handles[14]);
      aObjGhostSet(1, Object_handles[15]);
      aAISetState(0, Object_handles[16]);
      aAISetState(0, Object_handles[17]);
      aAISetTeam(196608, Object_handles[18]);
      aObjSetMovementType(Object_handles[18], 0);
      aObjMakeInvuln(Object_handles[19], 1000000);
      aObjMakeInvuln(Object_handles[20], 1000000);
      aObjMakeInvuln(Object_handles[21], 1000000);
      aObjSetMovementType(Object_handles[22], 0);
      aObjSetMovementType(Object_handles[23], 0);
      aObjSetMovementType(Object_handles[24], 0);
      aObjSetMovementType(Object_handles[25], 0);
      aSoundPlayObject(Sound_indexes[0], Object_handles[26], 1.000000f);
      aObjPlayAnim(Object_handles[26], 0, 32, 4.000000f, 1);
      aSetLevelTimer(3.000000f, 1);
      aSetLevelTimer(18.000000f, 16);
      aSetLevelTimer(1.000000f, 3);
      aSetLevelTimer(2.000000f, 12);
      aSetLevelTimer(3.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }

    // Script 086: Level Start - Intro Cinematic
    if (1) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[27], Path_indexes[1], 15.000000f);
      aMusicSetRegionAll(0);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 087: Level Start - Show Welder Hint
    if ((ScriptActionCtr_087 < 1) && (event_data->id == 16)) {
      aShowHUDMessage(Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }

    // Script 013: Level Start - Init after 1.0 sec
    if ((ScriptActionCtr_013 < 1) && (event_data->id == 1)) {
      aAISetMode(Object_handles[28], 6);
      aAISetMode(Object_handles[29], 6);
      aAISetMode(Object_handles[30], 6);
      aObjSetMovementType(Object_handles[28], 0);
      aObjSetMovementType(Object_handles[29], 0);
      aObjSetMovementType(Object_handles[30], 0);
      aMusicSetRegionAll(3);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }

    // Script 053: Do Welder Sparks
    if (event_data->id == 3) {
      if (qRandomValue(1.000000f, 100.000000f) < 50.000000f) {
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[22], 0);
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[23], 0);
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[24], 0);
        aEmitSparksFromGunpoint(qRandomValue(4.000000f, 8.000000f), Object_handles[25], 0);
      }
      aSetLevelTimer(qRandomValue(0.400000f, 1.200000f), 3);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 057: Send Off Cargo
    if (event_data->id == 4) {
      if (ScriptActionCtr_057 == 0) {
        aAIGoalFollowPath(Object_handles[34], Path_indexes[9], 1, 60, 1, 3, 3145984, 0);
        aAIGoalSetCircleDistance(Object_handles[34], 3, 0.000000f);
        aSetLevelTimer(3.000000f, 4);
      }
      if (ScriptActionCtr_057 == 1) {
        aAIGoalFollowPath(Object_handles[35], Path_indexes[9], 1, 59, 1, 3, 3145984, 1);
        aAIGoalSetCircleDistance(Object_handles[35], 3, 0.000000f);
        aCCSetData(Object_handles[35], Object_handles[34], 80.000000f, 20.000000f);
        aSetLevelTimer(3.000000f, 4);
      }
      if (ScriptActionCtr_057 == 2) {
        aAIGoalFollowPath(Object_handles[36], Path_indexes[9], 1, 58, 1, 3, 3145984, 2);
        aAIGoalSetCircleDistance(Object_handles[36], 3, 0.000000f);
        aCCSetData(Object_handles[36], Object_handles[35], 80.000000f, 20.000000f);
        aShowHUDMessage(Message_strings[9]);
        aObjMakeVulnerable(Object_handles[19]);
        aObjMakeVulnerable(Object_handles[20]);
        aObjMakeVulnerable(Object_handles[21]);
      }
      if (ScriptActionCtr_057 == 3) {
        aUnAttachObject(Object_handles[34]);
        aAIGoalFollowPath(Object_handles[34], Path_indexes[10], 1, 32, 1, 3, 3145984, 8);
        aAIGoalSetCircleDistance(Object_handles[34], 3, 0.000000f);
        aSetLevelTimer(3.000000f, 4);
        aMusicSetRegionAll(0);
      }
      if (ScriptActionCtr_057 == 4) {
        aUnAttachObject(Object_handles[35]);
        aAIGoalFollowPath(Object_handles[35], Path_indexes[10], 1, 30, 1, 3, 3145984, 8);
        aAIGoalSetCircleDistance(Object_handles[35], 3, 0.000000f);
        aCCEnable(Object_handles[35]);
        aSetLevelTimer(3.000000f, 4);
      }
      if (ScriptActionCtr_057 == 5) {
        aUnAttachObject(Object_handles[36]);
        aAIGoalFollowPath(Object_handles[36], Path_indexes[10], 1, 27, 1, 3, 3145984, 8);
        aAIGoalSetCircleDistance(Object_handles[36], 3, 0.000000f);
        aCCEnable(Object_handles[36]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }

    // Script 078: Reset the Crate Status Flag
    if (event_data->id == 14) {
      aUserFlagSet(15, 1);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }

    // Script 070: A Crate Was Destroyed
    if (event_data->id == 9) {
      if (qUserVarValue(5) == 1.000000f) {
        aShowHUDMessage(Message_strings[15]);
      }
      if (qUserVarValue(5) == 2.000000f) {
        aShowHUDMessage(Message_strings[16]);
      }
      if (qUserVarValue(5) == 3.000000f) {
        aShowHUDMessage(Message_strings[17]);
        aSetLevelTimer(8.000000f, 10);
      }

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }

    // Script 071: Mission Failed - All Crates Destroyed
    if (event_data->id == 10) {
      aFailLevel();

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }

    // Script 075: Do Ambush Checks
    if (event_data->id == 12) {
      if ((qUserFlag(11) == false) && (qObjGetDistance(Object_handles[34], Object_handles[38]) < 100.000000f)) {
        aShowHUDMessage(Message_strings[18]);
        aObjGhostSet(0, Object_handles[0]);
        aObjGhostSet(0, Object_handles[1]);
        aSetTargeting(Object_handles[0], Object_handles[19], Object_handles[20], Object_handles[21]);
        aSetTargeting(Object_handles[1], Object_handles[20], Object_handles[21], Object_handles[19]);
        aAIGoalFollowPathSimple(Object_handles[0], Path_indexes[11], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[1], Path_indexes[12], 4352, -1, 3);
        aUserFlagSet(11, 1);
        aSetWaypoint(1);
      }
      if ((qUserFlag(11) == true) && (qUserFlag(12) == false) &&
          (qObjGetDistance(Object_handles[34], Object_handles[39]) < 100.000000f)) {
        aShowHUDMessage(Message_strings[19]);
        aObjGhostSet(0, Object_handles[2]);
        aObjGhostSet(0, Object_handles[3]);
        aObjGhostSet(0, Object_handles[4]);
        aSetTargeting(Object_handles[2], Object_handles[19], Object_handles[20], Object_handles[21]);
        aSetTargeting(Object_handles[3], Object_handles[20], Object_handles[21], Object_handles[19]);
        aSetTargeting(Object_handles[4], Object_handles[21], Object_handles[19], Object_handles[20]);
        aAIGoalFollowPathSimple(Object_handles[2], Path_indexes[13], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[3], Path_indexes[14], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[4], Path_indexes[15], 4352, -1, 3);
        aUserFlagSet(12, 1);
        aSetWaypoint(2);
      }
      if ((qUserFlag(16) == true) && (qUserFlag(13) == false) &&
          (qObjGetDistance(Object_handles[34], Object_handles[40]) < 100.000000f)) {
        aShowHUDMessage(Message_strings[19]);
        aObjGhostSet(0, Object_handles[5]);
        aObjGhostSet(0, Object_handles[6]);
        aObjGhostSet(0, Object_handles[7]);
        aSetTargeting(Object_handles[5], Object_handles[19], Object_handles[20], Object_handles[21]);
        aSetTargeting(Object_handles[6], Object_handles[20], Object_handles[21], Object_handles[19]);
        aSetTargeting(Object_handles[7], Object_handles[21], Object_handles[19], Object_handles[20]);
        aAIGoalFollowPathSimple(Object_handles[5], Path_indexes[16], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[6], Path_indexes[17], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[7], Path_indexes[18], 4352, -1, 3);
        aUserFlagSet(13, 1);
        aSetWaypoint(3);
      }
      if ((qUserFlag(13) == true) && (qUserFlag(14) == false) &&
          (qObjGetDistance(Object_handles[34], Object_handles[41]) < 100.000000f)) {
        aShowHUDMessage(Message_strings[20]);
        aPortalRenderSet(0, 0, Room_indexes[3], 1);
        aPortalRenderSet(0, 1, Room_indexes[3], 1);
        aPortalRenderSet(0, 2, Room_indexes[3], 1);
        aPortalRenderSet(0, 3, Room_indexes[3], 1);
        aPortalRenderSet(0, 4, Room_indexes[3], 1);
        aPortalRenderSet(0, 5, Room_indexes[3], 1);
        aAISetTeam(0, Object_handles[18]);
        aObjSetMovementType(Object_handles[18], 1);
        aSetTargeting(Object_handles[18], Object_handles[19], Object_handles[20], Object_handles[21]);
        aUserFlagSet(14, 1);
        aSetWaypoint(4);
      }
      aSetLevelTimer(qRandomValue(1.000000f, 2.000000f), 12);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }

    // Script 076: Do Ambush Targetting
    if ((event_data->id == 13) && (qUserFlag(8) == false)) {
      if (qUserFlag(11) == true) {
        aSetTargeting(Object_handles[0], Object_handles[19], Object_handles[20], Object_handles[21]);
        aSetTargeting(Object_handles[1], Object_handles[20], Object_handles[21], Object_handles[19]);
      }
      if (qUserFlag(12) == true) {
        aSetTargeting(Object_handles[2], Object_handles[19], Object_handles[20], Object_handles[21]);
        aSetTargeting(Object_handles[3], Object_handles[20], Object_handles[21], Object_handles[19]);
        aSetTargeting(Object_handles[4], Object_handles[21], Object_handles[19], Object_handles[20]);
      }
      if (qUserFlag(17) == true) {
        aSetTargeting(Object_handles[8], Object_handles[19], Object_handles[20], Object_handles[21]);
      }
      if (qUserFlag(13) == true) {
        aSetTargeting(Object_handles[5], Object_handles[19], Object_handles[20], Object_handles[21]);
        aSetTargeting(Object_handles[6], Object_handles[20], Object_handles[21], Object_handles[19]);
        aSetTargeting(Object_handles[7], Object_handles[21], Object_handles[19], Object_handles[20]);
      }
      if (qUserFlag(14) == true) {
        aSetTargeting(Object_handles[18], Object_handles[19], Object_handles[20], Object_handles[21]);
      }
      aSetLevelTimer(qRandomValue(1.000000f, 4.000000f), 13);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }

    // Script 090: Fighter Spotted Message
    if ((ScriptActionCtr_090 < 1) && (event_data->id == 19)) {
      aShowHUDMessage(Message_strings[22]);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }

    // Script 060: Reset Turn Table Switch
    if (event_data->id == 5) {
      aObjPlayAnim(Object_handles[47], 10, 20, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], Object_handles[47], 1.000000f);
      aUserFlagSet(6, 0);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 019: Unleash Mini-Bosses
    if (event_data->id == 6) {
      if (ScriptActionCtr_019 == 0) {
        if (qObjExists(Object_handles[19]) == true) {
          aStoreObjectInPositionClipboard(Object_handles[19]);
          aMoveObjectToPositionClipboard(Object_handles[9]);
          aObjMakeVulnerable(Object_handles[19]);
          aObjDestroy(Object_handles[19]);
          aObjGhostSet(0, Object_handles[9]);
          aEnableVirusInfection(1, Object_handles[9]);
          aObjSetShields(Object_handles[9], 2500.000000f);
          aAIGoalFollowPathSimple(Object_handles[9], Path_indexes[20], 4101, -1, 0);
          aAIGoalSetCircleDistance(Object_handles[9], 0, 0.000000f);
          aAIFlags(1, 536870912, Object_handles[9]);
        }
        aSetLevelTimer(1.000000f, 6);
      }
      if (ScriptActionCtr_019 == 1) {
        if (qObjExists(Object_handles[21]) == true) {
          aStoreObjectInPositionClipboard(Object_handles[21]);
          aMoveObjectToPositionClipboard(Object_handles[11]);
          aObjMakeVulnerable(Object_handles[21]);
          aObjDestroy(Object_handles[21]);
          aObjGhostSet(0, Object_handles[11]);
          aEnableVirusInfection(1, Object_handles[11]);
          aObjSetShields(Object_handles[11], 2500.000000f);
          aAIGoalFollowPathSimple(Object_handles[11], Path_indexes[21], 4101, -1, 0);
          aAIGoalSetCircleDistance(Object_handles[11], 0, 0.000000f);
          aAIFlags(1, 536870912, Object_handles[11]);
        }
        aSetLevelTimer(1.500000f, 6);
      }
      if (ScriptActionCtr_019 == 2) {
        if (qObjExists(Object_handles[20]) == true) {
          aStoreObjectInPositionClipboard(Object_handles[20]);
          aMoveObjectToPositionClipboard(Object_handles[10]);
          aObjMakeVulnerable(Object_handles[20]);
          aObjDestroy(Object_handles[20]);
          aObjGhostSet(0, Object_handles[10]);
          aEnableVirusInfection(1, Object_handles[10]);
          aObjSetShields(Object_handles[10], 2500.000000f);
          aAIGoalFollowPathSimple(Object_handles[10], Path_indexes[22], 4101, -1, 0);
          aAIGoalSetCircleDistance(Object_handles[10], 0, 0.000000f);
          aAIFlags(1, 536870912, Object_handles[10]);
        }
        aSetLevelTimer(1.000000f, 6);
        aSetLevelTimer(40.000000f, 18);
      }
      if (ScriptActionCtr_019 == 3) {
        aShowHUDMessage(Message_strings[30]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 065: Do CED Backup Sequence
    if (event_data->id == 8) {
      if (ScriptActionCtr_065 == 0) {
        aSetLevelTimer(2.000000f, 8);
      }
      if (ScriptActionCtr_065 == 1) {
        aDoorLockUnlock(0, Door_handles[1]);
        aDoorActivate(Door_handles[1]);
        aSetLevelTimer(1.000000f, 8);
        aShowHUDMessage(Message_strings[31]);
      }
      if (ScriptActionCtr_065 == 2) {
        aAISetState(1, Object_handles[16]);
        aAISetState(1, Object_handles[17]);
        aAIGoalFollowPathSimple(Object_handles[16], Path_indexes[23], 4352, -1, 3);
        aAIGoalFollowPathSimple(Object_handles[17], Path_indexes[24], 4352, -1, 3);
        aGoalCompleted(Goal_indexes[10], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }

    // Script 089: Turn On Fight Matcens Sequence
    if (event_data->id == 18) {
      if (ScriptActionCtr_089 == 0) {
        aShowHUDMessage(Message_strings[32]);
        aMatcenSetEnableState(1, Matcen_indexes[0]);
        aMatcenSetEnableState(1, Matcen_indexes[3]);
        aMatcenSetState(1, Matcen_indexes[0]);
        aMatcenSetState(1, Matcen_indexes[3]);
        aSetLevelTimer(20.000000f, 18);
      }
      if (ScriptActionCtr_089 == 1) {
        aShowHUDMessage(Message_strings[33]);
        aMatcenSetEnableState(1, Matcen_indexes[1]);
        aMatcenSetEnableState(1, Matcen_indexes[4]);
        aMatcenSetState(1, Matcen_indexes[1]);
        aMatcenSetState(1, Matcen_indexes[4]);
        aSetLevelTimer(20.000000f, 18);
      }
      if (ScriptActionCtr_089 == 2) {
        aShowHUDMessage(Message_strings[34]);
        aMatcenSetEnableState(1, Matcen_indexes[2]);
        aMatcenSetEnableState(1, Matcen_indexes[8]);
        aMatcenSetState(1, Matcen_indexes[2]);
        aMatcenSetState(1, Matcen_indexes[8]);
        aSetLevelTimer(20.000000f, 18);
      }
      if (ScriptActionCtr_089 == 3) {
        aShowHUDMessage(Message_strings[35]);
        aMatcenSetEnableState(1, Matcen_indexes[5]);
        aMatcenSetEnableState(1, Matcen_indexes[6]);
        aMatcenSetState(1, Matcen_indexes[5]);
        aMatcenSetState(1, Matcen_indexes[6]);
        aSetLevelTimer(40.000000f, 8);
      }

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }

    // Script 064: Do Reactor Diagnostics Sequence
    if (event_data->id == 7) {
      if (ScriptActionCtr_064 == 0) {
        aLightningCreate(Object_handles[50], Object_handles[51], 1000000.000000f, 2.000000f, 2, Texture_indexes[3],
                         0.400000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(3.000000f, 7);
      }
      if (ScriptActionCtr_064 == 1) {
        aLightningCreate(Object_handles[50], Object_handles[52], 1000000.000000f, 4.000000f, 1, Texture_indexes[4],
                         0.400000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[50], Object_handles[53], 1000000.000000f, 4.000000f, 1, Texture_indexes[4],
                         0.400000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[50], Object_handles[54], 1000000.000000f, 4.000000f, 1, Texture_indexes[4],
                         0.400000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[51], Object_handles[52], 1000000.000000f, 4.000000f, 1, Texture_indexes[4],
                         0.400000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[51], Object_handles[53], 1000000.000000f, 4.000000f, 1, Texture_indexes[4],
                         0.400000f, 1, 255, 255, 255, 0);
        aLightningCreate(Object_handles[51], Object_handles[54], 1000000.000000f, 4.000000f, 1, Texture_indexes[4],
                         0.400000f, 1, 255, 255, 255, 0);
        aSetLevelTimer(3.000000f, 7);
      }
      if (ScriptActionCtr_064 == 2) {
        aDoorLockUnlock(0, Door_handles[2]);
        aDoorSetPos(Door_handles[2], 1.000000f);
        aShowHUDMessage(Message_strings[37]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }

    // Script 088: Do Reactor Death Sequence
    if (event_data->id == 17) {
      if (ScriptActionCtr_088 == 0) {
        aTurnOnSpew(Object_handles[55], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.600000f, 0.100000f, 1000000.000000f,
                    15.000000f, 50.000000f, 0, -1);
        aSetLevelTimer(2.000000f, 17);
      }
      if (ScriptActionCtr_088 == 1) {
        aTurnOnSpew(Object_handles[56], -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.900000f, 0.100000f, 1000000.000000f,
                    10.000000f, 90.000000f, 0, -1);
        aSetLevelTimer(1.000000f, 17);
      }
      if (ScriptActionCtr_088 == 2) {
        aRoomSetLightingFlicker(1, Room_indexes[6]);
        aRoomSetLightingFlicker(1, Room_indexes[7]);
        aRoomSetLightingFlicker(1, Room_indexes[8]);
        aRoomSetLightingFlicker(1, Room_indexes[9]);
        aRoomSetLightingFlicker(1, Room_indexes[10]);
        aRoomSetLightingFlicker(1, Room_indexes[11]);
        aRoomSetLightingFlicker(1, Room_indexes[12]);
        aTurnOnSpew(Object_handles[50], -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.600000f, 0.100000f, 1000000.000000f,
                    13.000000f, 50.000000f, 0, -1);
        aTurnOnSpew(Object_handles[57], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.200000f, 1000000.000000f,
                    3.000000f, 10.000000f, 0, -1);
        aGoalCompleted(Goal_indexes[12], 1);
        aGoalEnableDisable(1, Goal_indexes[13]);
        aShowHUDMessage(Message_strings[38]);
        aUserFlagSet(10, 1);
        aMatcenSetEnableState(1, Matcen_indexes[9]);
        aMatcenSetState(1, Matcen_indexes[9]);
        aSetLevelTimer(60.000000f, 0);
        aTimerShow(0);
        aSetLevelTimer(0.200000f, 17);
      }
      if (ScriptActionCtr_088 >= 3) {
        aMiscShakeArea(Object_handles[26], qRandomValue(80.000000f, 100.000000f), 10000.000000f);
        aSoundPlay2D(Sound_indexes[6], 1.000000f);
        aSetLevelTimer(qRandomValue(3.000000f, 8.000000f), 17);
      }

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }

    // Script 012: Time Ran Out - End Level
    if ((ScriptActionCtr_012 < 1) && ((event_data->id == 0) && (qUserFlag(9) == false))) {
      aEndLevel();

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 011: Player Escaped - End Level
    if ((ScriptActionCtr_011 < 1) && (event_data->id == 11)) {
      aGoalCompleted(Goal_indexes[13], 1);
      aStartEndlevelSequencePath(Path_indexes[25], Path_indexes[26], 6.000000f, Message_strings[39]);
      aSetLevelTimer(1.500000f, 15);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 084: Do End Sequence
    if (event_data->id == 15) {
      if (ScriptActionCtr_084 == 0) {
        aTurnOnSpew(Object_handles[27], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.200000f, 2.000000f,
                    33.000000f, 200.000000f, 1, -1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 024: Lifter Got To Box
    if (event_data->goal_uid == 3) {
      if (qUserVarValue(1) == 1.000000f) {
        aAIGoalPickUpObject(event_data->it_handle, 0, Object_handles[19], 0, 1, 3, 256, 5);
      }
      if (qUserVarValue(1) == 2.000000f) {
        aAIGoalPickUpObject(event_data->it_handle, 0, Object_handles[20], 0, 1, 3, 256, 5);
      }
      if (qUserVarValue(1) == 3.000000f) {
        aAIGoalPickUpObject(event_data->it_handle, 0, Object_handles[21], 0, 1, 3, 256, 5);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 054: Lifter Picked Up Box
    if (event_data->goal_uid == 5) {
      if (qUserVarValue(1) == 1.000000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[3], 1048832, 4, 3);
      }
      if (qUserVarValue(1) == 2.000000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[4], 1048832, 4, 3);
      }
      if (qUserVarValue(1) == 3.000000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[5], 1048832, 4, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }

    // Script 055: Lifter Got To Box Dest
    if (event_data->goal_uid == 4) {
      if (qUserVarValue(1) == 1.000000f) {
        aAIGoalSetObjectOnObject(event_data->it_handle, 1, Object_handles[34], 0, 3, 131328, 6);
      }
      if (qUserVarValue(1) == 2.000000f) {
        aAIGoalSetObjectOnObject(event_data->it_handle, 1, Object_handles[35], 0, 3, 131328, 6);
      }
      if (qUserVarValue(1) == 3.000000f) {
        aAIGoalSetObjectOnObject(event_data->it_handle, 1, Object_handles[36], 0, 3, 131328, 6);
      }

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }

    // Script 056: Lifter Dropped Off Box
    if (event_data->goal_uid == 6) {
      if (qUserVarValue(1) == 1.000000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[6], 4352, 3, 3);
      }
      if (qUserVarValue(1) == 2.000000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[7], 4352, 3, 3);
      }
      if (qUserVarValue(1) == 3.000000f) {
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[8], 1048832, -1, 3);
        aShowHUDMessage(Message_strings[6]);
        aUserFlagSet(1, 1);
        aGoalCompleted(Goal_indexes[3], 1);
      }
      aUserVarInc(1);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }

    // Script 018: Barge Got To Turn Table
    if ((event_data->goal_uid == 0) || (event_data->goal_uid == 1) || (event_data->goal_uid == 2)) {
      if (event_data->it_handle == Object_handles[34]) {
        aCCDisable(Object_handles[35]);
      }
      if (event_data->it_handle == Object_handles[35]) {
        aCCDisable(Object_handles[36]);
      }
      if (ScriptActionCtr_018 == 2) {
        aShowHUDMessage(Message_strings[10]);
        aUserFlagSet(2, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 059: Barge Landed On Turn Table
    if (event_data->goal_uid == 7) {
      if (event_data->it_handle == Object_handles[34]) {
        aCCDisable(Object_handles[35]);
      }
      if (event_data->it_handle == Object_handles[35]) {
        aCCDisable(Object_handles[36]);
      }
      if (ScriptActionCtr_059 == 2) {
        aPortalRenderSet(1, 0, Room_indexes[2], 1);
        aPortalRenderSet(1, 1, Room_indexes[2], 1);
        aShowHUDMessage(Message_strings[11]);
        aUserFlagSet(3, 1);
        aGoalCompleted(Goal_indexes[5], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }

    // Script 062: Barge Got To Base
    if (event_data->goal_uid == 8) {
      if (event_data->it_handle == Object_handles[34]) {
        aCCDisable(Object_handles[35]);
      }
      if (event_data->it_handle == Object_handles[35]) {
        aCCDisable(Object_handles[36]);
      }
      if ((ScriptActionCtr_062 == 2) && (qUserVarValue(5) < 3.000000f)) {
        aShowHUDMessage(Message_strings[12]);
        aUserFlagSet(8, 1);
        aGoalCompleted(Goal_indexes[6], 1);
        aObjMakeInvuln(Object_handles[19], 1000000);
        aObjMakeInvuln(Object_handles[20], 1000000);
        aObjMakeInvuln(Object_handles[21], 1000000);
        aSetLevelTimer(2.000000f, 6);
      }

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 015: Lifter Created By Matcen
    if (event_data->id == Matcen_indexes[7]) {
      aObjMakeInvuln(event_data->it_handle, 1000000);
      aPhysFlags(1, 60817408, event_data->it_handle);
      aAISetMaxSpeed(event_data->it_handle, 32.000000f);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[2], 4352, 3, 3);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Start Door Message
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[2]);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;

      return CONTINUE_DEFAULT;
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

    // Script 000: Welder Drops Data 01
    if ((ScriptActionCtr_000 < 1) && (1)) {
      aObjGhostSet(0, Object_handles[12]);
      aStoreObjectInPositionClipboard(data->me_handle);
      aMoveObjectToPositionClipboard(Object_handles[12]);
      aGoalItemCompleted(Goal_indexes[0], 1, 1);
      aUserVarInc(4);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0840::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 002: Welder Drops Data 02
    if ((ScriptActionCtr_002 < 1) && (1)) {
      aObjGhostSet(0, Object_handles[13]);
      aStoreObjectInPositionClipboard(data->me_handle);
      aMoveObjectToPositionClipboard(Object_handles[13]);
      aGoalItemCompleted(Goal_indexes[0], 2, 1);
      aUserVarInc(4);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0864::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 003: Welder Drops Data 03
    if ((ScriptActionCtr_003 < 1) && (1)) {
      aObjGhostSet(0, Object_handles[14]);
      aStoreObjectInPositionClipboard(data->me_handle);
      aMoveObjectToPositionClipboard(Object_handles[14]);
      aGoalItemCompleted(Goal_indexes[0], 3, 1);
      aUserVarInc(4);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_186D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 004: Welder Drops Data 04
    if ((ScriptActionCtr_004 < 1) && (1)) {
      aObjGhostSet(0, Object_handles[15]);
      aStoreObjectInPositionClipboard(data->me_handle);
      aMoveObjectToPositionClipboard(Object_handles[15]);
      aGoalItemCompleted(Goal_indexes[0], 4, 1);
      aUserVarInc(4);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20A3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Pickup Data 01
    if ((ScriptActionCtr_006 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      aShowHUDMessage(Message_strings[4]);
      aGoalItemCompleted(Goal_indexes[1], 1, 1);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: Pickup Data 02
    if ((ScriptActionCtr_007 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      aShowHUDMessage(Message_strings[4]);
      aGoalItemCompleted(Goal_indexes[1], 2, 1);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: Pickup Data 03
    if ((ScriptActionCtr_008 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      aShowHUDMessage(Message_strings[4]);
      aGoalItemCompleted(Goal_indexes[1], 3, 1);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Pickup Data 04
    if ((ScriptActionCtr_009 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      aShowHUDMessage(Message_strings[4]);
      aGoalItemCompleted(Goal_indexes[1], 4, 1);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_403E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Load Cargo Switch Hit
    if ((ScriptActionCtr_017 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aMatcenSetState(1, Matcen_indexes[7]);
      aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[5]);
      aRoomSetFaceTexture(Room_indexes[0], 35, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_783F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Cargo Forcefield Switch Hit
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(0) == 0)) {
      if (qUserFlag(1) == true) {
        aObjPlayAnim(data->me_handle, 0, 2, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
        aShowHUDMessage(Message_strings[7]);
        aPortalRenderSet(0, 8, Room_indexes[1], 1);
        aPortalRenderSet(0, 9, Room_indexes[1], 1);
        aPortalRenderSet(0, 10, Room_indexes[1], 1);
        aPortalRenderSet(0, 11, Room_indexes[1], 1);
        aPortalRenderSet(0, 12, Room_indexes[1], 1);
        aPortalRenderSet(0, 13, Room_indexes[1], 1);
        aUserFlagSet(0, 1);
        aSetLevelTimer(1.000000f, 4);
        aGoalCompleted(Goal_indexes[4], 1);
        aRoomSetFaceTexture(Room_indexes[0], 93, Texture_indexes[1]);
        aRoomSetFaceTexture(Room_indexes[0], 35, Texture_indexes[2]);
      } else {
        aShowHUDMessage(Message_strings[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1084::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DAMAGED: {
    tOSIRISEVTDAMAGED *event_data = &data->evt_damaged;

    // Script 077: Crate #1 Damaged
    if (qUserFlag(15) == true) {
      if (qRandomValue(1.000000f, 100.000000f) < 50.000000f) {
        aShowHUDMessage(Message_strings[13]);
      } else {
        aShowHUDMessage(Message_strings[14]);
      }
      aUserFlagSet(15, 0);
      aSetLevelTimer(qRandomValue(8.000000f, 16.000000f), 14);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 069: Cargo Crate #1 Destroyed
    if (qUserFlag(8) == false) {
      aUserVarInc(5);
      aSetLevelTimer(1.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0885::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DAMAGED: {
    tOSIRISEVTDAMAGED *event_data = &data->evt_damaged;

    // Script 079: Crate #2 Damaged
    if (qUserFlag(15) == true) {
      if (qRandomValue(1.000000f, 100.000000f) < 50.000000f) {
        aShowHUDMessage(Message_strings[13]);
      } else {
        aShowHUDMessage(Message_strings[14]);
      }
      aUserFlagSet(15, 0);
      aSetLevelTimer(qRandomValue(8.000000f, 16.000000f), 14);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 072: Cargo Crate #2 Destroyed
    if (qUserFlag(8) == false) {
      aUserVarInc(5);
      aSetLevelTimer(1.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1086::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DAMAGED: {
    tOSIRISEVTDAMAGED *event_data = &data->evt_damaged;

    // Script 080: Crate #3 Damaged
    if (qUserFlag(15) == true) {
      if (qRandomValue(1.000000f, 100.000000f) < 50.000000f) {
        aShowHUDMessage(Message_strings[13]);
      } else {
        aShowHUDMessage(Message_strings[14]);
      }
      aUserFlagSet(15, 0);
      aSetLevelTimer(qRandomValue(8.000000f, 16.000000f), 14);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 073: Cargo Crate #3 Destroyed
    if (qUserFlag(8) == false) {
      aUserVarInc(5);
      aSetLevelTimer(1.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2046::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 022: Kill 3 Gadgets part 1
    if ((ScriptActionCtr_022 < 1) && (1)) {
      aUserVarInc(2);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 021: Kill 3 Gadgets part 2
    if ((ScriptActionCtr_021 < 1) && (1)) {
      aUserVarInc(2);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 020: Kill 3 Gadgets part 3
    if ((ScriptActionCtr_020 < 1) && (1)) {
      aUserVarInc(2);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Hood Hit While Doing Fly By
    if ((ScriptActionCtr_083 < 1) &&
        ((qUserFlag(17) == false) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true))) {
      aUserFlagSet(17, 1);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 074: Hood Finished Fly By
    if (event_data->goal_uid == 9) {
      aAISetTeam(0, Object_handles[8]);
      aSetTargeting(Object_handles[8], Object_handles[19], Object_handles[20], Object_handles[21]);
      aUserFlagSet(17, 1);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_5847::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Turn Table Load Switch Hit
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(5) == false)) {
      if (qRoomHasPlayer(Room_indexes[4]) == 1) {
        if (qUserFlag(2) == true) {
          aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
          aShowHUDMessage(Message_strings[23]);
          aPortalRenderSet(0, 0, Room_indexes[2], 1);
          aPortalRenderSet(0, 1, Room_indexes[2], 1);
          aAIGoalLandOnObject(Object_handles[34], 1, Object_handles[46], 2, 3, 131328, 7);
          aAIGoalLandOnObject(Object_handles[35], 1, Object_handles[46], 1, 3, 131328, 7);
          aAIGoalLandOnObject(Object_handles[36], 1, Object_handles[46], 0, 3, 131328, 7);
          aAIGoalSetCircleDistance(Object_handles[34], 3, 500.000000f);
          aAIGoalSetCircleDistance(Object_handles[35], 3, 500.000000f);
          aAIGoalSetCircleDistance(Object_handles[36], 3, 500.000000f);
          aCCEnable(Object_handles[35]);
          aCCEnable(Object_handles[36]);
          aUserFlagSet(5, 1);
        } else {
          aShowHUDMessage(Message_strings[24]);
        }
      } else {
        aShowHUDMessage(Message_strings[25]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1048::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Turn Table Turning Switch Hit
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == false) &&
        (qUserFlag(7) == false) &&
        ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 20.000000f))) {
      if (qRoomHasPlayer(Room_indexes[4]) == 1) {
        if (qUserFlag(3) == true) {
          aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
          aUserFlagSet(6, 1);
          if (qUserVarValue(3) == 1.000000f) {
            aObjPlayAnim(Object_handles[46], 0, 1, 4.000000f, 0);
          }
          if (qUserVarValue(3) == 2.000000f) {
            aObjPlayAnim(Object_handles[46], 1, 2, 4.000000f, 0);
          }
          if (qUserVarValue(3) == 3.000000f) {
            aObjPlayAnim(Object_handles[46], 2, 3, 4.000000f, 0);
          }
          if (qUserVarValue(3) == 4.000000f) {
            aObjPlayAnim(Object_handles[46], 3, 4, 4.000000f, 0);
          }
          aUserVarInc(3);
          if (qUserVarValue(3) > 4.000000f) {
            aUserVarSet(3, 1.000000f);
          }
          aSetLevelTimer(4.000000f, 5);
          if (qUserFlag(16) == false) {
            aObjGhostSet(0, Object_handles[8]);
            aAISetTeam(196608, Object_handles[8]);
            aAIGoalFollowPathSimple(Object_handles[8], Path_indexes[19], 1048832, 9, 3);
            aUserFlagSet(16, 1);
            aSetLevelTimer(5.000000f, 19);
          }
        } else {
          aShowHUDMessage(Message_strings[26]);
        }
      } else {
        aShowHUDMessage(Message_strings[25]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_104A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Turn Table Unload Switch Hit
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == false)) {
      if (qRoomHasPlayer(Room_indexes[4]) == 1) {
        if (qUserFlag(3) == true) {
          if ((qUserVarValue(3) == 4.000000f) && (qObjAnimFrame(Object_handles[46]) == 3.000000f)) {
            if (qGoalCompleted(Goal_indexes[9]) == false) {
              aGoalCompleted(Goal_indexes[9], 1);
            }
            aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
            aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
            aShowHUDMessage(Message_strings[28]);
            aPortalRenderSet(0, 0, Room_indexes[5], 1);
            aPortalRenderSet(0, 1, Room_indexes[5], 1);
            aUserFlagSet(7, 1);
            aUserFlagSet(4, 1);
            aSetLevelTimer(1.000000f, 4);
            aGoalCompleted(Goal_indexes[8], 1);
          } else {
            aShowHUDMessage(Message_strings[29]);
          }
        } else {
          aShowHUDMessage(Message_strings[26]);
        }
      } else {
        aShowHUDMessage(Message_strings[25]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_108E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Reactor Door Switch Hit
    if ((ScriptActionCtr_063 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aShowHUDMessage(Message_strings[36]);
      aSetLevelTimer(1.000000f, 7);
      aGoalCompleted(Goal_indexes[11], 1);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1827::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: Reactor dies
    if ((ScriptActionCtr_039 < 1) && (qObjShields(data->me_handle) <= 0.000000f)) {
      aObjPlayAnim(data->me_handle, 0, 0, 1.000000f, 0);
      aObjSpark(data->me_handle, 40.000000f, 99999.000000f);
      aSetObjectOnFire(Object_handles[26], 1000000.000000f, 0.000000f);
      aSoundStopObj(data->me_handle);
      aSetLevelTimer(1.000000f, 17);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  case EVT_DAMAGED: {
    tOSIRISEVTDAMAGED *event_data = &data->evt_damaged;

    // Script 081: Reactor Attacked
    if ((ScriptActionCtr_081 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aMatcenSetState(1, Matcen_indexes[9]);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Player Entered Loading Area
    if ((ScriptActionCtr_067 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[2], 1);
      aSoundPlayObject(Sound_indexes[2], Object_handles[32], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: hangar to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: mine to hangar Music Region change
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: mine to terrain Music Region change
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: mine to terrain Music Region change
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: mine to terrain Music Region change
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: mine to terrain Music Region change
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: mine to terrain Music Region change
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: mine to terrain Music Region change
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: terrain to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: terrain to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: terrain to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: terrain to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: terrain to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: terrain to mine Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: terrain to CED Music Region change
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: terrain to CED Music Region change
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: terrain to CED Music Region change
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: terrain to CED Music Region change
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: terrain to CED Music Region change
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 050: CED to terrain 2 Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      if (qUserFlag(10) == true) {
        aUserFlagSet(9, 1);
        aSetLevelTimer(0.100000f, 11);
      }

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

    // Script 045: terrain to CED Music Region change
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }

    // Script 051: CED to terrain 2 Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      if (qUserFlag(10) == true) {
        aUserFlagSet(9, 1);
        aSetLevelTimer(0.100000f, 11);
      }

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: CED to terrain 2 Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      if (qUserFlag(10) == true) {
        aUserFlagSet(9, 1);
        aSetLevelTimer(0.100000f, 11);
      }

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 047: CED to terrain 2 Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      if (qUserFlag(10) == true) {
        aUserFlagSet(9, 1);
        aSetLevelTimer(0.100000f, 11);
      }

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: CED to terrain 2 Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      if (qUserFlag(10) == true) {
        aUserFlagSet(9, 1);
        aSetLevelTimer(0.100000f, 11);
      }

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: CED to terrain 2 Music Region change
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);
      if (qUserFlag(10) == true) {
        aUserFlagSet(9, 1);
        aSetLevelTimer(0.100000f, 11);
      }

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
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
NEXT_ID		91

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:DataCartsPickedUp
1:CurrentBox
2:DeadGadget
3:WheelPosition
4:WeldersKilled
5:CratesDestroyed
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:FFcontrolActive
1:CargoLoaded
2:CargoAtTT
3:CargoOnTT
4:CargoLeftTT
5:LoadTTSwitchDown
6:TurnTTSwitchDown
7:LeaveTTSwitchDown
8:CargoAtBase
9:PlayerEscaped
10:ReactorDestroyed
11:Ambush1Sprung
12:Ambush2Sprung
13:Ambush4Sprung
14:Ambush5Sprung
15:OkToDisplayCrateStatus
16:Ambush3Sprung
17:Ambush3Attacking
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:ReactorTimer
1:LevelStartMessage
2:ForcefieldControlTimer
3:SparkTimer
4:SendOffCargo
5:ResetTTSwitch
6:UnleashMiniBoss
7:DoDiagnosticSequence
8:DeployBackup
9:CrateDestroyed
10:MissionFailed
11:DoEscapeSequence
12:DoAmbushChecks
13:DoAmbushTargetting
14:ResetCrateStatusFlag
15:DoEndSequence
16:WelderHint
17:DoReactorDeathSequence
18:TurnOnFightMatcens
19:FighterSpotted
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:Barge1Path1Done
1:Barge2Path1Done
2:Barge3Path1Done
3:LifterGotToBox
4:LifterGotToBoxDest
5:LifterPickedUpBox
6:LifterDroppedOffBox
7:LandedOnWheel
8:BargePath2Done
9:FinishedFlyby
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
PTMCminedoor
MainBaseDoor
ReactorDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
Ambusher1A
Ambusher1B
Ambusher2A
Ambusher2B
Ambusher2C
Ambusher4A
Ambusher4B
Ambusher4C
HoodAmbusher
MiniBoss1
MiniBoss2
MiniBoss3
Data 01
Data 02
Data 03
Data 04
Backup1
Backup2
Ambusher5
Boss Crate 01
Boss Crate 02
Boss Crate 03
Welder 01
Welder 02
Welder 03
Welder 04
CED Reactor
EndBlastCam
Gadget 01
Gadget 02
Gadget03
Dravis Door
PTMChangarcontrol
HangarMatcenContro
Barge 01
Barge 02
Barge 03
HangarFFControl
Ambush1Trigger
Ambush2Trigger
Ambush4Trigger
Ambush5Trigger
FailsafeTerminal
GreenOrb
CEDfoyer
TTLoadSwitch
Big Wheel
TTTurnSwitch
TTUnloadSwitch
ReactorDoorSwitch
TopCam
BottomCam
SideCam1
SideCam2
SideCam3
ReactorDeathCamA
ReactorDeathCamB
MonitorSpew
$$OBJECT_LIST_END

$$ROOM_LIST_START
PTMC control room
PTMC Loading Force
TTLoadFFRoom
CEDBaseEntrance
Wheel Control Room
TTUnloadFFRoom
CED reactor room
FlashRoom1
Failsafe Room
CED fight room mai
CED fight room lef
CED fight room rig
CED fight room top
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EnteredLoadingArea
PTMCminemusic
PTMChangarmusic
PTMC2terrain01
PTMC2terrain02
PTMC2terrain03
PTMC2terrain04
PTMC2terrain05
PTMC2terrain06
terrain to PTMC 01
terrain to PTMC 02
terrain to PTMC 03
terrain to PTMC 04
terrain to PTMC 05
terrain to PTMC 06
CEDbase 01
CEDbase 02
CEDbase03
CEDbase 04
CED to terrain 05
CED to terrain 06
CED to terrain 01
CED to terrain 02
CED to terrain 03
CED to terrain 04
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbDroneReactor
Powerup pickup
AmbMonitorProcessing
AmbSwitch31
AmbInVolcanoLava
AmbDroneHallway
Merc4Rumble
$$SOUND_LIST_END

$$TEXTURE_LIST_START
PTMClogoON
M06_ForcefieldDisabled
PTMClogooff
FunkyEffect7
FunkyEffect4
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCamPath
IntroPlayerPath
LifterToBox1
LifterToBarge1
LifterToBox2Dest
LifterToBox3Dest
LifterToBox2
LifterToBox3
LifterFinished
PTMCbargepath
CEDbargepath
Ambusher1Path
Ambusher1BPath
Ambusher2Path
Ambusher2B
Ambusher2C
Ambusher4Path
Ambusher4BPath
Ambusher4CPath
HoodAmbushPath
MiniBoss1Path
MiniBoss3Path
MiniBoss2Path
Backup1Path
Backup2Path
EndCamPath
EndPlayerPath
$$PATH_LIST_END

$$MATCEN_LIST_START
CED fight left 01
CED fight left 02
CED fight left 03
CED fight right 01
CED fight right 02
CED fight top left
CED fight top right
Matcen 2
CED fight right 03
Matcen 3
$$MATCEN_LIST_END

$$GOAL_LIST_START
Destroy Welder Bots
Obtain Maintenance Access Cards
Enter PTMC Loading Area
Load Cargo onto Barges
Disable Cargo Hold Forcefield
Load Cargo onto Turn Table
Protect Cargo Enroute to Base
Destroy Tower Operators
Unload Cargo from Turn Table
Align Turn Table with Base
Force Open Outer Reactor Door
Engage Reactor Diagnostics
Destroy Reactor
Escape
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:1:Level Start - Init Flags and Variables
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
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
                        10:10:0:10:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
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
                        10:10:0:16:UserFlag
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
                        10:10:0:17:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Level Start - Misc
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
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
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:4:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:5:Matcen
                        $$CHILD_BLOCK_END
                08:aMatcenSetEnableState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:17:0:6:Matcen
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
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
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:8:Object
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
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:0:18:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:24:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:26:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:4:0:StartFrame
                        10:4:32:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:18.000000:Time
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Level Start - Intro Cinematic
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
                        10:8:IntroText:Text
                        10:1:0:27:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:0:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Level Start - Show Welder Hint
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Killwelders:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Level Start - Init after 1.0 sec
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
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:10:0:6:AIModeType
                        $$CHILD_BLOCK_END
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:10:0:6:AIModeType
                        $$CHILD_BLOCK_END
                08:aAISetMode
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:10:0:6:AIModeType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:3:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Start Door Message
        $$CHILD_BLOCK_START
        01:1:31
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
                        10:8:DravisDoor:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Do Welder Sparks
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
                                10:1:0:22:Object
                                10:4:0:Gunpoint
                                $$CHILD_BLOCK_END
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:23:Object
                                10:4:0:Gunpoint
                                $$CHILD_BLOCK_END
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:24:Object
                                10:4:0:Gunpoint
                                $$CHILD_BLOCK_END
                        08:aEmitSparksFromGunpoint
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Number
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:1:0:25:Object
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
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Welder Drops Data 01
        $$CHILD_BLOCK_START
        01:1:22
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:4:1:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Welder Drops Data 02
        $$CHILD_BLOCK_START
        01:1:23
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:4:2:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Welder Drops Data 03
        $$CHILD_BLOCK_START
        01:1:24
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:4:3:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Welder Drops Data 04
        $$CHILD_BLOCK_START
        01:1:25
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aStoreObjectInPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aMoveObjectToPositionClipboard
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:4:4:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Check Number of Welders Killed
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValueInt:Integer
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:4:4:Integer
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Check Number of Cards Picked Up
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValueInt:Integer
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:4:4:Integer
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:0:DoorName
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PTMCminedoor:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Pickup Data 01
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Maintenance:Message
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:4:1:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Pickup Data 02
        $$CHILD_BLOCK_START
        01:1:13
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Maintenance:Message
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:4:2:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Pickup Data 03
        $$CHILD_BLOCK_START
        01:1:14
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Maintenance:Message
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:4:3:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Pickup Data 04
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Maintenance:Message
                        $$CHILD_BLOCK_END
                08:aGoalItemCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:4:4:ItemIndex
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Player Entered Loading Area
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
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:32:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Load Cargo Switch Hit
        $$CHILD_BLOCK_START
        01:1:33
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:7:Matcen
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
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:HangarMatcen:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:35:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Lifter Created By Matcen
        $$CHILD_BLOCK_START
        01:2:0
        02:21
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:17:1:-1:Matcen
                        07:1:0
                        10:17:0:7:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:4:1000000:Time
                        $$CHILD_BLOCK_END
                08:aPhysFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:60817408:PhysicsFlags
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:32.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:2:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:3:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Lifter Got To Box
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
                        08:aAIGoalPickUpObject
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:0:PickerPoint
                                10:1:0:19:Pickee
                                10:4:0:PickeePoint
                                10:5:1:Aligned
                                10:10:0:3:GoalPriority
                                10:15:256:AIGoalFlags
                                10:10:0:5:GoalID
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
                        08:aAIGoalPickUpObject
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:0:PickerPoint
                                10:1:0:20:Pickee
                                10:4:0:PickeePoint
                                10:5:1:Aligned
                                10:10:0:3:GoalPriority
                                10:15:256:AIGoalFlags
                                10:10:0:5:GoalID
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
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalPickUpObject
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:0:PickerPoint
                                10:1:0:21:Pickee
                                10:4:0:PickeePoint
                                10:5:1:Aligned
                                10:10:0:3:GoalPriority
                                10:15:256:AIGoalFlags
                                10:10:0:5:GoalID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Lifter Picked Up Box
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
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:3:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:4:GoalID
                                10:10:0:3:GoalPriority
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
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:4:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:4:GoalID
                                10:10:0:3:GoalPriority
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
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:5:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:4:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:55:Lifter Got To Box Dest
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
                        08:aAIGoalSetObjectOnObject
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:1:CarriedObjectPoint
                                10:1:0:34:LandOnObject
                                10:4:0:LandOnPoint
                                10:10:0:3:GoalPriority
                                10:15:131328:AIGoalFlags
                                10:10:0:6:GoalID
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
                        08:aAIGoalSetObjectOnObject
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:1:CarriedObjectPoint
                                10:1:0:35:LandOnObject
                                10:4:0:LandOnPoint
                                10:10:0:3:GoalPriority
                                10:15:131328:AIGoalFlags
                                10:10:0:6:GoalID
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
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalSetObjectOnObject
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Picker
                                10:4:1:CarriedObjectPoint
                                10:1:0:36:LandOnObject
                                10:4:0:LandOnPoint
                                10:10:0:3:GoalPriority
                                10:15:131328:AIGoalFlags
                                10:10:0:6:GoalID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Lifter Dropped Off Box
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
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:6:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:3:GoalID
                                10:10:0:3:GoalPriority
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
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:7:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:3:GoalID
                                10:10:0:3:GoalPriority
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
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:8:Path
                                10:15:1048832:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoLoaded:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:3:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Cargo Forcefield Switch Hit
        $$CHILD_BLOCK_START
        01:1:37
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:0:Bool
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
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:2:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:3:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:PTMCforcefiledDown:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:8:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:9:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:10:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:11:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:12:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:13:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:4:93:FaceNum
                                10:14:1:Texture
                                $$CHILD_BLOCK_END
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:0:Room
                                10:4:35:FaceNum
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoNotLoaded:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Send Off Cargo
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:34:Object
                                10:16:9:Path
                                10:4:1:FirstNode
                                10:4:60:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:3145984:AIGoalFlags
                                10:10:0:0:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:34:Object
                                10:10:0:3:GoalPriority
                                10:6:0.000000:distance
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object
                                10:16:9:Path
                                10:4:1:FirstNode
                                10:4:59:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:3145984:AIGoalFlags
                                10:10:0:1:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object
                                10:10:0:3:GoalPriority
                                10:6:0.000000:distance
                                $$CHILD_BLOCK_END
                        08:aCCSetData
                                $$CHILD_BLOCK_START
                                10:1:0:35:Barge
                                10:1:0:34:Follow Handle
                                10:6:80.000000:Stop Distance
                                10:6:20.000000:Slowdown Offset
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:16:9:Path
                                10:4:1:FirstNode
                                10:4:58:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:3145984:AIGoalFlags
                                10:10:0:2:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:10:0:3:GoalPriority
                                10:6:0.000000:distance
                                $$CHILD_BLOCK_END
                        08:aCCSetData
                                $$CHILD_BLOCK_START
                                10:1:0:36:Barge
                                10:1:0:35:Follow Handle
                                10:6:80.000000:Stop Distance
                                10:6:20.000000:Slowdown Offset
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo:Message
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object
                                $$CHILD_BLOCK_END
                        08:aObjMakeVulnerable
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUnAttachObject
                                $$CHILD_BLOCK_START
                                10:1:0:34:AttachedObject
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:34:Object
                                10:16:10:Path
                                10:4:1:FirstNode
                                10:4:32:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:3145984:AIGoalFlags
                                10:10:0:8:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:34:Object
                                10:10:0:3:GoalPriority
                                10:6:0.000000:distance
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        08:aMusicSetRegionAll
                                $$CHILD_BLOCK_START
                                10:10:0:0:Region
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:4:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUnAttachObject
                                $$CHILD_BLOCK_START
                                10:1:0:35:AttachedObject
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object
                                10:16:10:Path
                                10:4:1:FirstNode
                                10:4:30:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:3145984:AIGoalFlags
                                10:10:0:8:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:35:Object
                                10:10:0:3:GoalPriority
                                10:6:0.000000:distance
                                $$CHILD_BLOCK_END
                        08:aCCEnable
                                $$CHILD_BLOCK_START
                                10:1:0:35:Barge
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:57:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:5:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUnAttachObject
                                $$CHILD_BLOCK_START
                                10:1:0:36:AttachedObject
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:16:10:Path
                                10:4:1:FirstNode
                                10:4:27:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:3145984:AIGoalFlags
                                10:10:0:8:GoalID
                                $$CHILD_BLOCK_END
                        08:aAIGoalSetCircleDistance
                                $$CHILD_BLOCK_START
                                10:1:0:36:Object
                                10:10:0:3:GoalPriority
                                10:6:0.000000:distance
                                $$CHILD_BLOCK_END
                        08:aCCEnable
                                $$CHILD_BLOCK_START
                                10:1:0:36:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Barge Got To Turn Table
        $$CHILD_BLOCK_START
        01:2:0
        02:13
        03:0
                $$CHILD_BLOCK_START
                09:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:1:0:GoalID
                                07:1:0
                                10:10:0:0:GoalID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:1:0:GoalID
                                07:1:0
                                10:10:0:1:GoalID
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                10:10:1:0:GoalID
                                07:1:0
                                10:10:0:2:GoalID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                10:1:0:34:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCCDisable
                                $$CHILD_BLOCK_START
                                10:1:0:35:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                10:1:0:35:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCCDisable
                                $$CHILD_BLOCK_START
                                10:1:0:36:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:18:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoAtTT:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Barge Landed On Turn Table
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
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                10:1:0:34:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCCDisable
                                $$CHILD_BLOCK_START
                                10:1:0:35:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                10:1:0:35:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCCDisable
                                $$CHILD_BLOCK_START
                                10:1:0:36:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:59:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoOnTT:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:5:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Barge Got To Base
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                10:1:0:34:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCCDisable
                                $$CHILD_BLOCK_START
                                10:1:0:35:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                07:1:0
                                10:1:0:35:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCCDisable
                                $$CHILD_BLOCK_START
                                10:1:0:36:Barge
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qTimesScriptExecuted_DALLAS:Integer
                                                $$CHILD_BLOCK_START
                                                10:11:62:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:2:Integer
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoAtBase:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:0:19:Object
                                10:4:1000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:0:20:Object
                                10:4:1000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjMakeInvuln
                                $$CHILD_BLOCK_START
                                10:1:0:21:Object
                                10:4:1000000:Time
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Cargo Crate #1 Destroyed
        $$CHILD_BLOCK_START
        01:1:19
        02:4
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:Cargo Crate #2 Destroyed
        $$CHILD_BLOCK_START
        01:1:20
        02:4
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:Cargo Crate #3 Destroyed
        $$CHILD_BLOCK_START
        01:1:21
        02:4
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Crate #1 Damaged
        $$CHILD_BLOCK_START
        01:1:19
        02:3
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserFlag
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo2:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo3:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:8.000000:LowerLimit
                                10:6:16.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Crate #2 Damaged
        $$CHILD_BLOCK_START
        01:1:20
        02:3
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserFlag
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo2:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo3:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:8.000000:LowerLimit
                                10:6:16.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Crate #3 Damaged
        $$CHILD_BLOCK_START
        01:1:21
        02:3
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserFlag
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo2:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ProtectCargo3:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:8.000000:LowerLimit
                                10:6:16.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:14:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Reset the Crate Status Flag
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:A Crate Was Destroyed
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
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:1.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoDestroyed:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:2.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoDestroyed2:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:3.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CargoDestroyed3:Message
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:8.000000:Time
                                10:10:0:10:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Mission Failed - All Crates Destroyed
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
                08:aFailLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:Do Ambush Checks
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
                                                10:10:0:11:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:34:Object1
                                                10:1:0:38:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:100.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Ambush2:Message
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:0:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:1:Object
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                10:1:0:20:Target
                                10:1:0:21:Alternate1
                                10:1:0:19:Alternate2
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:16:11:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                10:16:12:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetWaypoint
                                $$CHILD_BLOCK_START
                                10:4:1:Number
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
                                                10:10:0:11:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:34:Object1
                                                10:1:0:39:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:100.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Ambush1:Message
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:2:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:3:Object
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:4:Object
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:2:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:1:0:20:Target
                                10:1:0:21:Alternate1
                                10:1:0:19:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:1:0:21:Target
                                10:1:0:19:Alternate1
                                10:1:0:20:Alternate2
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:2:Object
                                10:16:13:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:16:14:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:16:15:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetWaypoint
                                $$CHILD_BLOCK_START
                                10:4:2:Number
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
                                                10:10:0:16:UserFlag
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:34:Object1
                                                10:1:0:40:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:100.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Ambush1:Message
                                $$CHILD_BLOCK_END
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
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:1:0:20:Target
                                10:1:0:21:Alternate1
                                10:1:0:19:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:1:0:21:Target
                                10:1:0:19:Alternate1
                                10:1:0:20:Alternate2
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:16:16:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:16:17:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:16:18:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetWaypoint
                                $$CHILD_BLOCK_START
                                10:4:3:Number
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
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:34:Object1
                                                10:1:0:41:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:100.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:CEDBaseFFDown:Message
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
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:3:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:4:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:5:PortalNum
                                10:2:3:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:0:Teams
                                10:1:0:18:Object
                                $$CHILD_BLOCK_END
                        08:aObjSetMovementType
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:10:0:1:MovementType
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetWaypoint
                                $$CHILD_BLOCK_START
                                10:4:4:Number
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:1.000000:LowerLimit
                                10:6:2.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Do Ambush Targetting
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
                                10:10:0:13:TimerID
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
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:1:Object
                                10:1:0:20:Target
                                10:1:0:21:Alternate1
                                10:1:0:19:Alternate2
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
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:2:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:3:Object
                                10:1:0:20:Target
                                10:1:0:21:Alternate1
                                10:1:0:19:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:1:0:21:Target
                                10:1:0:19:Alternate1
                                10:1:0:20:Alternate2
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
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:8:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
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
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:1:0:20:Target
                                10:1:0:21:Alternate1
                                10:1:0:19:Alternate2
                                $$CHILD_BLOCK_END
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:1:0:21:Target
                                10:1:0:19:Alternate1
                                10:1:0:20:Alternate2
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
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTargeting
                                $$CHILD_BLOCK_START
                                10:1:0:18:Object
                                10:1:0:19:Target
                                10:1:0:20:Alternate1
                                10:1:0:21:Alternate2
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:1.000000:LowerLimit
                                10:6:4.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Kill 3 Gadgets part 1
        $$CHILD_BLOCK_START
        01:1:28
        02:4
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
00:21:Kill 3 Gadgets part 2
        $$CHILD_BLOCK_START
        01:1:29
        02:4
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
00:20:Kill 3 Gadgets part 3
        $$CHILD_BLOCK_START
        01:1:30
        02:4
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
00:23:All gadgets dead so drop forcefield
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:4:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ControlFFDown:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:42:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:43:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:44:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Fighter Spotted Message
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Ambush3:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Hood Hit While Doing Fly By
        $$CHILD_BLOCK_START
        01:1:8
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:17:UserFlag
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Hood Finished Fly By
        $$CHILD_BLOCK_START
        01:1:8
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
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:0:Teams
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aSetTargeting
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:1:0:19:Target
                        10:1:0:20:Alternate1
                        10:1:0:21:Alternate2
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Turn Table Load Switch Hit
        $$CHILD_BLOCK_START
        01:1:45
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:4:Room
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
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
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:0:StartFrame
                                        10:4:10:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:3:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:TTLoading:Message
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
                                08:aAIGoalLandOnObject
                                        $$CHILD_BLOCK_START
                                        10:1:0:34:LandingObject
                                        10:4:1:LanderAttachPoint
                                        10:1:0:46:ObjectToLandOn
                                        10:4:2:LandOnObjectAttachPoint
                                        10:10:0:3:GoalPriority
                                        10:15:131328:AIGoalFlags
                                        10:10:0:7:GoalID
                                        $$CHILD_BLOCK_END
                                08:aAIGoalLandOnObject
                                        $$CHILD_BLOCK_START
                                        10:1:0:35:LandingObject
                                        10:4:1:LanderAttachPoint
                                        10:1:0:46:ObjectToLandOn
                                        10:4:1:LandOnObjectAttachPoint
                                        10:10:0:3:GoalPriority
                                        10:15:131328:AIGoalFlags
                                        10:10:0:7:GoalID
                                        $$CHILD_BLOCK_END
                                08:aAIGoalLandOnObject
                                        $$CHILD_BLOCK_START
                                        10:1:0:36:LandingObject
                                        10:4:1:LanderAttachPoint
                                        10:1:0:46:ObjectToLandOn
                                        10:4:0:LandOnObjectAttachPoint
                                        10:10:0:3:GoalPriority
                                        10:15:131328:AIGoalFlags
                                        10:10:0:7:GoalID
                                        $$CHILD_BLOCK_END
                                08:aAIGoalSetCircleDistance
                                        $$CHILD_BLOCK_START
                                        10:1:0:34:Object
                                        10:10:0:3:GoalPriority
                                        10:6:500.000000:distance
                                        $$CHILD_BLOCK_END
                                08:aAIGoalSetCircleDistance
                                        $$CHILD_BLOCK_START
                                        10:1:0:35:Object
                                        10:10:0:3:GoalPriority
                                        10:6:500.000000:distance
                                        $$CHILD_BLOCK_END
                                08:aAIGoalSetCircleDistance
                                        $$CHILD_BLOCK_START
                                        10:1:0:36:Object
                                        10:10:0:3:GoalPriority
                                        10:6:500.000000:distance
                                        $$CHILD_BLOCK_END
                                08:aCCEnable
                                        $$CHILD_BLOCK_START
                                        10:1:0:35:Barge
                                        $$CHILD_BLOCK_END
                                08:aCCEnable
                                        $$CHILD_BLOCK_START
                                        10:1:0:36:Barge
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:NoTTCargo:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SwitchHitFromOutside:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Turn Table Turning Switch Hit
        $$CHILD_BLOCK_START
        01:1:47
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
                                        10:6:20.000000:Literal
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
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:4:Room
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
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
                                                10:10:0:3:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:0:StartFrame
                                        10:4:10:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:3:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        10:5:1:True/False
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
                                                10:6:1.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:46:Object
                                                10:4:0:StartFrame
                                                10:4:1:EndFrame
                                                10:6:4.000000:CycleTime
                                                10:5:0:Looping
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
                                                07:1:0
                                                10:6:2.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:46:Object
                                                10:4:1:StartFrame
                                                10:4:2:EndFrame
                                                10:6:4.000000:CycleTime
                                                10:5:0:Looping
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
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:46:Object
                                                10:4:2:StartFrame
                                                10:4:3:EndFrame
                                                10:6:4.000000:CycleTime
                                                10:5:0:Looping
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
                                                07:1:0
                                                10:6:4.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:0:46:Object
                                                10:4:3:StartFrame
                                                10:4:4:EndFrame
                                                10:6:4.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
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
                                                10:6:4.000000:Literal
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
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:4.000000:Time
                                        10:10:0:5:TimerID
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
                                        08:aObjGhostSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:Ghost/Unghost
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        08:aAISetTeam
                                                $$CHILD_BLOCK_START
                                                10:10:0:196608:Teams
                                                10:1:0:8:Object
                                                $$CHILD_BLOCK_END
                                        08:aAIGoalFollowPathSimple
                                                $$CHILD_BLOCK_START
                                                10:1:0:8:Object
                                                10:16:19:Path
                                                10:15:1048832:AIGoalFlags
                                                10:10:0:9:GoalID
                                                10:10:0:3:GoalPriority
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:16:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:5.000000:Time
                                                10:10:0:19:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:NoCargoOnTT:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SwitchHitFromOutside:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Check if Turn Table is Aligned
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qGoalCompleted:Bool
                                $$CHILD_BLOCK_START
                                10:18:0:8:LevelGoal
                                $$CHILD_BLOCK_END
                        07:0:7
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
                                                10:10:0:3:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:46:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:9:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:9:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qGoalCompleted:Bool
                                                $$CHILD_BLOCK_START
                                                10:18:0:9:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:OutOfAlign:Message
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:9:LevelGoal
                                        10:10:0:0:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Reset Turn Table Switch
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
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:4:10:StartFrame
                        10:4:20:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:47:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Turn Table Unload Switch Hit
        $$CHILD_BLOCK_START
        01:1:48
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qRoomHasPlayer:Bool
                                        $$CHILD_BLOCK_START
                                        10:2:4:Room
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
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
                                                10:10:0:3:UserFlag
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
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValue:Float
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:3:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:4.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qObjAnimFrame:Float
                                                                $$CHILD_BLOCK_START
                                                                10:1:0:46:Object
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:6:3.000000:Literal
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qGoalCompleted:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:18:0:9:LevelGoal
                                                                $$CHILD_BLOCK_END
                                                        07:0:7
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aGoalCompleted
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:9:LevelGoal
                                                        10:10:0:1:Completed
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        08:aObjPlayAnim
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                10:4:0:StartFrame
                                                10:4:10:EndFrame
                                                10:6:2.000000:CycleTime
                                                10:5:0:Looping
                                                $$CHILD_BLOCK_END
                                        08:aSoundPlayObject
                                                $$CHILD_BLOCK_START
                                                10:12:3:Sound
                                                10:1:2:-1:Object
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:TTUnloading:Message
                                                $$CHILD_BLOCK_END
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
                                                10:4:1:PortalNum
                                                10:2:5:Room
                                                10:5:1:DoublesidedFlag
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aUserFlagSet
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserFlag
                                                10:5:1:True/False
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:1.000000:Time
                                                10:10:0:4:TimerID
                                                $$CHILD_BLOCK_END
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:8:LevelGoal
                                                10:10:0:1:Completed
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:WrongWheelPos:Message
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:NoCargoOnTT:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SwitchHitFromOutside:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Unleash Mini-Bosses
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:19:ScriptID
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
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:19:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        $$CHILD_BLOCK_END
                                08:aMoveObjectToPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                08:aObjMakeVulnerable
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        $$CHILD_BLOCK_END
                                08:aObjDestroy
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                08:aEnableVirusInfection
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                08:aObjSetShields
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        10:6:2500.000000:Shields
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        10:16:20:Path
                                        10:15:4101:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aAIGoalSetCircleDistance
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        10:10:0:0:GoalPriority
                                        10:6:0.000000:distance
                                        $$CHILD_BLOCK_END
                                08:aAIFlags
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Set/Clear
                                        10:15:536870912:AIFlags
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:19:ScriptID
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
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:21:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                08:aMoveObjectToPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:11:Object
                                        $$CHILD_BLOCK_END
                                08:aObjMakeVulnerable
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                08:aObjDestroy
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:11:Object
                                        $$CHILD_BLOCK_END
                                08:aEnableVirusInfection
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:1:0:11:Object
                                        $$CHILD_BLOCK_END
                                08:aObjSetShields
                                        $$CHILD_BLOCK_START
                                        10:1:0:11:Object
                                        10:6:2500.000000:Shields
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:11:Object
                                        10:16:21:Path
                                        10:15:4101:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aAIGoalSetCircleDistance
                                        $$CHILD_BLOCK_START
                                        10:1:0:11:Object
                                        10:10:0:0:GoalPriority
                                        10:6:0.000000:distance
                                        $$CHILD_BLOCK_END
                                08:aAIFlags
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Set/Clear
                                        10:15:536870912:AIFlags
                                        10:1:0:11:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.500000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:19:ScriptID
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
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:20:Object
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                08:aMoveObjectToPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:10:Object
                                        $$CHILD_BLOCK_END
                                08:aObjMakeVulnerable
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                08:aObjDestroy
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:10:Object
                                        $$CHILD_BLOCK_END
                                08:aEnableVirusInfection
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        10:1:0:10:Object
                                        $$CHILD_BLOCK_END
                                08:aObjSetShields
                                        $$CHILD_BLOCK_START
                                        10:1:0:10:Object
                                        10:6:2500.000000:Shields
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:0:10:Object
                                        10:16:22:Path
                                        10:15:4101:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                08:aAIGoalSetCircleDistance
                                        $$CHILD_BLOCK_START
                                        10:1:0:10:Object
                                        10:10:0:0:GoalPriority
                                        10:6:0.000000:distance
                                        $$CHILD_BLOCK_END
                                08:aAIFlags
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Set/Clear
                                        10:15:536870912:AIFlags
                                        10:1:0:10:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Time
                                10:10:0:18:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:19:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LetsRock:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Do CED Backup Sequence
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
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:8:TimerID
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
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:1:DoorName
                                $$CHILD_BLOCK_END
                        08:aDoorActivate
                                $$CHILD_BLOCK_START
                                10:0:0:1:Door
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:BackupDeployed:Message
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
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:1:0:16:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:1:0:17:Object
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:16:Object
                                10:16:23:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:0:17:Object
                                10:16:24:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:10:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Turn On Fight Matcens Sequence
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Backup1:Message
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:3:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:3:Matcen
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Time
                                10:10:0:18:TimerID
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Backup2:Message
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:4:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:4:Matcen
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Time
                                10:10:0:18:TimerID
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Backup3:Message
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:2:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:8:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:2:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:8:Matcen
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:20.000000:Time
                                10:10:0:18:TimerID
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
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Backup4:Message
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:5:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:6:Matcen
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
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Time
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Reactor Door Switch Hit
        $$CHILD_BLOCK_START
        01:1:49
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
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ReactorSwitchHit:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:11:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Do Reactor Diagnostics Sequence
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:64:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object1
                                10:1:0:51:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:2.000000:Thickness
                                10:4:2:NumTiles
                                10:14:3:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
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
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:64:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object1
                                10:1:0:52:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object1
                                10:1:0:53:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object1
                                10:1:0:54:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:51:Object1
                                10:1:0:52:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:51:Object1
                                10:1:0:53:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:51:Object1
                                10:1:0:54:Object2
                                10:6:1000000.000000:Lifetime
                                10:6:4.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.400000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
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
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:64:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
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
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ReactorDoorOpening:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Reactor Attacked
        $$CHILD_BLOCK_START
        01:1:26
        02:3
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:9:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Reactor dies
        $$CHILD_BLOCK_START
        01:1:26
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qObjShields:Float
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                $$CHILD_BLOCK_END
                        07:1:5
                        10:6:0.000000:Literal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:0:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aSetObjectOnFire
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:6:1000000.000000:Seconds
                        10:6:0.000000:Damage
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:17:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Do Reactor Death Sequence
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:88:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:55:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.600000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:1000000.000000:SpewLife
                                10:6:15.000000:BlobSize
                                10:6:50.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:17:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:88:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:56:Object
                                10:4:-1:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.900000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:1000000.000000:SpewLife
                                10:6:10.000000:BlobSize
                                10:6:90.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:1.000000:Time
                                10:10:0:17:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:88:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:6:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:7:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:8:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:9:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:10:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:11:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingFlicker
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:12:Room
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:50:Object
                                10:4:-1:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.600000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:1000000.000000:SpewLife
                                10:6:13.000000:BlobSize
                                10:6:50.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
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
                                10:6:0.500000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:1000000.000000:SpewLife
                                10:6:3.000000:BlobSize
                                10:6:10.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:12:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:13:LevelGoal
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ReactorBlownMessage:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:10:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aMatcenSetEnableState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:17:0:9:Matcen
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:9:Matcen
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:60.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        08:aTimerShow
                                $$CHILD_BLOCK_START
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.200000:Time
                                10:10:0:17:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:88:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:26:Object
                                06:qRandomValue:Amount
                                        $$CHILD_BLOCK_START
                                        10:6:80.000000:LowerLimit
                                        10:6:100.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:6:10000.000000:Dist
                                $$CHILD_BLOCK_END
                        08:aSoundPlay2D
                                $$CHILD_BLOCK_START
                                10:12:6:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                06:qRandomValue:Time
                                        $$CHILD_BLOCK_START
                                        10:6:3.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                10:10:0:17:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Time Ran Out - End Level
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
                                10:10:0:0:TimerID
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
                08:aEndLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Player Escaped - End Level
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:13:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:25:CameraPath
                        10:16:26:PlayerPath
                        10:6:6.000000:Time
                        10:8:Empty:Text
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.500000:Time
                        10:10:0:15:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Do End Sequence
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
                                        10:11:84:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:4:-1:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.000000:BlobLifetime
                                10:6:0.200000:BlobInterval
                                10:6:2.000000:SpewLife
                                10:6:33.000000:BlobSize
                                10:6:200.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:hangar to mine Music Region change
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
00:26:mine to hangar Music Region change
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
00:27:mine to terrain Music Region change
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
00:28:mine to terrain Music Region change
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
00:29:mine to terrain Music Region change
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
00:30:mine to terrain Music Region change
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
00:31:mine to terrain Music Region change
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
00:32:mine to terrain Music Region change
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:terrain to mine Music Region change
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
00:34:terrain to mine Music Region change
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
00:35:terrain to mine Music Region change
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:terrain to mine Music Region change
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
00:37:terrain to mine Music Region change
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
00:38:terrain to mine Music Region change
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
00:40:terrain to CED Music Region change
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:terrain to CED Music Region change
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:terrain to CED Music Region change
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:terrain to CED Music Region change
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:terrain to CED Music Region change
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:terrain to CED Music Region change
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
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:CED to terrain 2 Music Region change
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
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:CED to terrain 2 Music Region change
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
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:CED to terrain 2 Music Region change
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
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:CED to terrain 2 Music Region change
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:CED to terrain 2 Music Region change
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:CED to terrain 2 Music Region change
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                03:1
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:0.100000:Time
                                10:10:0:11:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
