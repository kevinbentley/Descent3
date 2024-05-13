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
// Filename:	level7.cpp
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

#define ID_CUSTOM_OBJECT_1097 0x001
#define ID_CUSTOM_OBJECT_08B5 0x002
#define ID_CUSTOM_OBJECT_0895 0x003
#define ID_CUSTOM_OBJECT_08A1 0x004
#define ID_CUSTOM_OBJECT_08A2 0x005
#define ID_CUSTOM_OBJECT_08AF 0x006
#define ID_CUSTOM_OBJECT_1901 0x007
#define ID_CUSTOM_OBJECT_090A 0x008
#define ID_CUSTOM_OBJECT_1109 0x009
#define ID_CUSTOM_OBJECT_0908 0x00a
#define ID_CUSTOM_OBJECT_0907 0x00b
#define ID_CUSTOM_OBJECT_090C 0x00c
#define ID_CUSTOM_OBJECT_110D 0x00d
#define ID_CUSTOM_OBJECT_090B 0x00e
#define ID_CUSTOM_OBJECT_30A8 0x00f
#define ID_CUSTOM_OBJECT_0940 0x010
#define ID_CUSTOM_OBJECT_0941 0x011
#define ID_CUSTOM_OBJECT_0944 0x012
#define ID_CUSTOM_OBJECT_08B4 0x013
#define ID_CUSTOM_OBJECT_08B3 0x014
#define ID_CUSTOM_OBJECT_0943 0x015
#define ID_CUSTOM_OBJECT_0942 0x016
#define ID_CUSTOM_OBJECT_18B8 0x017
#define ID_CUSTOM_OBJECT_20B1 0x018
#define ID_CUSTOM_OBJECT_089A 0x019
#define ID_CUSTOM_OBJECT_0945 0x01a
#define ID_CUSTOM_OBJECT_192A 0x01b
#define ID_CUSTOM_OBJECT_092B 0x01c
#define ID_CUSTOM_OBJECT_1021 0x01d
#define ID_CUSTOM_OBJECT_092C 0x01e
#define ID_CUSTOM_OBJECT_112D 0x01f
#define ID_CUSTOM_OBJECT_0861 0x020
#define ID_CUSTOM_OBJECT_0862 0x021
#define ID_CUSTOM_OBJECT_186B 0x022
#define ID_CUSTOM_OBJECT_2071 0x023
#define ID_CUSTOM_OBJECT_2148 0x024
#define ID_CUSTOM_OBJECT_2059 0x025
#define ID_CUSTOM_OBJECT_205B 0x026
#define ID_CUSTOM_OBJECT_1947 0x027
#define ID_CUSTOM_OBJECT_2146 0x028
#define ID_CUSTOM_OBJECT_205A 0x029
#define ID_CUSTOM_OBJECT_0923 0x02a

#define ID_TRIGGER_0003 0x02b
#define ID_TRIGGER_0005 0x02c
#define ID_TRIGGER_0007 0x02d
#define ID_TRIGGER_0006 0x02e
#define ID_TRIGGER_001E 0x02f
#define ID_TRIGGER_0019 0x030
#define ID_TRIGGER_0016 0x031
#define ID_TRIGGER_000E 0x032
#define ID_TRIGGER_000B 0x033
#define ID_TRIGGER_001C 0x034
#define ID_TRIGGER_001A 0x035
#define ID_TRIGGER_000C 0x036
#define ID_TRIGGER_0009 0x037
#define ID_TRIGGER_001B 0x038
#define ID_TRIGGER_0015 0x039
#define ID_TRIGGER_001D 0x03a
#define ID_TRIGGER_001F 0x03b
#define ID_TRIGGER_000F 0x03c
#define ID_TRIGGER_000D 0x03d
#define ID_TRIGGER_0010 0x03e
#define ID_TRIGGER_000A 0x03f
#define ID_TRIGGER_0000 0x040
#define ID_TRIGGER_0020 0x041

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

class CustomObjectScript_1097 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0895 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08AF : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1901 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1109 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0908 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0907 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_110D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_090B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_30A8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0940 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0941 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0944 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08B3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0943 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0942 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_18B8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_20B1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_089A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0945 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_192A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_092B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1021 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_092C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_112D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0861 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0862 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_186B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2071 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2148 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2059 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_205B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1947 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2146 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_205A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0923 : public BaseScript {
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

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0019 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000E : public BaseScript {
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

class TriggerScript_001A : public BaseScript {
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

class TriggerScript_001B : public BaseScript {
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

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_008 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_008 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Enter your custom script code here
/*
$$ENUM Region
0:IntroCam
1:Outside
2:DefenseDisabled
3:RedMainMine
4:GreenMainMine
5:TechMine
6:Research
7:VirusContainment
8:Escape
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
static const char *const Door_names[NUM_DOOR_NAMES] = {"MagnetControlDoor", "MagnetTubeDoor", "VirusDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 60
static const char *const Object_names[NUM_OBJECT_NAMES] = {"TurretControlSwitch",
                                                           "Repeater-6",
                                                           "Repeater-2",
                                                           "Repeater-5",
                                                           "Repeater-3",
                                                           "Repeater-4",
                                                           "Repeater-1",
                                                           "MiniTurret-1",
                                                           "MiniTurret-2",
                                                           "MiniTurret-3",
                                                           "MiniTurret-4",
                                                           "CoolSpewer-2",
                                                           "CoolSpewer-1",
                                                           "MagnetSpewer-2",
                                                           "MagnetSpewer-1",
                                                           "VirusSpewer",
                                                           "CoolerMain",
                                                           "CoolingView",
                                                           "VirusView",
                                                           "CoolControl-1",
                                                           "CoolControl-2",
                                                           "CoolControl-3",
                                                           "CoolControl-4",
                                                           "MagnetSwitch-2",
                                                           "MagnetSwitch-1",
                                                           "MagnetController",
                                                           "MTubeSpewer-1",
                                                           "MTubeSpewer-2",
                                                           "MTubeView",
                                                           "FFKey",
                                                           "FFSwitch-1",
                                                           "FFSwitch-2",
                                                           "LowerSwitch-1",
                                                           "FireSpewer-1",
                                                           "FireSpewer-2",
                                                           "LowerSwitch-2",
                                                           "LowerSwitch-3",
                                                           "Virus-2",
                                                           "Virus-1",
                                                           "MidSpewer-4",
                                                           "MidSpewer-1",
                                                           "MidSpewer-2",
                                                           "MidSpewer-3",
                                                           "SteamSwitch",
                                                           "SteamSpewer",
                                                           "BlastPipe-1",
                                                           "BlastPipe-2",
                                                           "SwitchCamera-Cooler",
                                                           "CameraCooler",
                                                           "SwitchCamera-Magnet",
                                                           "Camera-Magnet",
                                                           "CSwitch-Virus",
                                                           "Camera-Virus",
                                                           "EndCam",
                                                           "Controller-4",
                                                           "Controller-3",
                                                           "Controller-2",
                                                           "Controller-1",
                                                           "BoxBottom1",
                                                           "BoxPhysics"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 20
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "Entrance-4", "Entrance-1",   "Entrance-2", "Entrance-3", "CoolerRoom", "MagnetRoom", "FireRoom-1",
    "FireRoom-2", "SteamingRoom", "UpTube-1",   "UpTube-2",   "UpTube-3",   "UpTube-4",   "UpTube-5",
    "UpTube-6",   "UpTube-7",     "UpTube-8",   "DownTube-4", "DownTube-3", "DownTube-2"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 23
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "EndLevelStart",  "EnteringBottom", "VirusEnter2",    "VirusEnter1",       "Music-Green8", "Music-Green7",
    "Music-Green5",   "Music-Green2",   "Music-Green1",   "Music-Red4",        "Music-Red3",   "Music-Red2",
    "Music-Red1",     "Music-Tech5",    "Music-Tech3",    "Music-Bunker",      "Music-Escape", "Music-Defense4",
    "Music-Defense3", "Music-Defense2", "Music-Defense1", "DownTube-WayPoint", "MagnetStart-1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 8
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSwitch41",        "AmbSwitch31",     "AmbSwitch21",
                                                         "Powerup pickup",     "AmbSwitch11",     "PupC1",
                                                         "LevSecAccelRelease", "LevSecAccelStart"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
static const char **Texture_names = NULL;
static int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 3
static const char *const Path_names[NUM_PATH_NAMES] = {"EndLevel", "IntroCam", "IntroShip"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 5
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Enable descending accelerator", "Disable containment forcefields", "Activate the Ascending Elevator",
    "Steal the Virus Samples", "Get both virus samples"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 22
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "ControlVulnerable",   "TurretsDeactivated", "CoolersAllGone",    "MagnetTubeDoorUnlock",
    "ManualActivation",    "MagnetActivated",    "FFKeyPickup",       "FFDisabled",
    "FFDisable1",          "NeedFFKey",          "UpperTubeActivate", "ContainmentDoorUnlocked",
    "SuperHeaterShutdown", "Virus2Collected",    "Virus1Collected",   "SteamRelease",
    "CameraActivation",    "Finished",           "IntroMessage",      "VirusDescription",
    "Controller",          "TurretsInvuln"};
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
    strcpy(filename, "level7.msg");
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
  case ID_CUSTOM_OBJECT_1097:
    return new CustomObjectScript_1097;
    break;
  case ID_CUSTOM_OBJECT_08B5:
    return new CustomObjectScript_08B5;
    break;
  case ID_CUSTOM_OBJECT_0895:
    return new CustomObjectScript_0895;
    break;
  case ID_CUSTOM_OBJECT_08A1:
    return new CustomObjectScript_08A1;
    break;
  case ID_CUSTOM_OBJECT_08A2:
    return new CustomObjectScript_08A2;
    break;
  case ID_CUSTOM_OBJECT_08AF:
    return new CustomObjectScript_08AF;
    break;
  case ID_CUSTOM_OBJECT_1901:
    return new CustomObjectScript_1901;
    break;
  case ID_CUSTOM_OBJECT_090A:
    return new CustomObjectScript_090A;
    break;
  case ID_CUSTOM_OBJECT_1109:
    return new CustomObjectScript_1109;
    break;
  case ID_CUSTOM_OBJECT_0908:
    return new CustomObjectScript_0908;
    break;
  case ID_CUSTOM_OBJECT_0907:
    return new CustomObjectScript_0907;
    break;
  case ID_CUSTOM_OBJECT_090C:
    return new CustomObjectScript_090C;
    break;
  case ID_CUSTOM_OBJECT_110D:
    return new CustomObjectScript_110D;
    break;
  case ID_CUSTOM_OBJECT_090B:
    return new CustomObjectScript_090B;
    break;
  case ID_CUSTOM_OBJECT_30A8:
    return new CustomObjectScript_30A8;
    break;
  case ID_CUSTOM_OBJECT_0940:
    return new CustomObjectScript_0940;
    break;
  case ID_CUSTOM_OBJECT_0941:
    return new CustomObjectScript_0941;
    break;
  case ID_CUSTOM_OBJECT_0944:
    return new CustomObjectScript_0944;
    break;
  case ID_CUSTOM_OBJECT_08B4:
    return new CustomObjectScript_08B4;
    break;
  case ID_CUSTOM_OBJECT_08B3:
    return new CustomObjectScript_08B3;
    break;
  case ID_CUSTOM_OBJECT_0943:
    return new CustomObjectScript_0943;
    break;
  case ID_CUSTOM_OBJECT_0942:
    return new CustomObjectScript_0942;
    break;
  case ID_CUSTOM_OBJECT_18B8:
    return new CustomObjectScript_18B8;
    break;
  case ID_CUSTOM_OBJECT_20B1:
    return new CustomObjectScript_20B1;
    break;
  case ID_CUSTOM_OBJECT_089A:
    return new CustomObjectScript_089A;
    break;
  case ID_CUSTOM_OBJECT_0945:
    return new CustomObjectScript_0945;
    break;
  case ID_CUSTOM_OBJECT_192A:
    return new CustomObjectScript_192A;
    break;
  case ID_CUSTOM_OBJECT_092B:
    return new CustomObjectScript_092B;
    break;
  case ID_CUSTOM_OBJECT_1021:
    return new CustomObjectScript_1021;
    break;
  case ID_CUSTOM_OBJECT_092C:
    return new CustomObjectScript_092C;
    break;
  case ID_CUSTOM_OBJECT_112D:
    return new CustomObjectScript_112D;
    break;
  case ID_CUSTOM_OBJECT_0861:
    return new CustomObjectScript_0861;
    break;
  case ID_CUSTOM_OBJECT_0862:
    return new CustomObjectScript_0862;
    break;
  case ID_CUSTOM_OBJECT_186B:
    return new CustomObjectScript_186B;
    break;
  case ID_CUSTOM_OBJECT_2071:
    return new CustomObjectScript_2071;
    break;
  case ID_CUSTOM_OBJECT_2148:
    return new CustomObjectScript_2148;
    break;
  case ID_CUSTOM_OBJECT_2059:
    return new CustomObjectScript_2059;
    break;
  case ID_CUSTOM_OBJECT_205B:
    return new CustomObjectScript_205B;
    break;
  case ID_CUSTOM_OBJECT_1947:
    return new CustomObjectScript_1947;
    break;
  case ID_CUSTOM_OBJECT_2146:
    return new CustomObjectScript_2146;
    break;
  case ID_CUSTOM_OBJECT_205A:
    return new CustomObjectScript_205A;
    break;
  case ID_CUSTOM_OBJECT_0923:
    return new CustomObjectScript_0923;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
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
  case ID_CUSTOM_OBJECT_1097:
    delete ((CustomObjectScript_1097 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B5:
    delete ((CustomObjectScript_08B5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0895:
    delete ((CustomObjectScript_0895 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A1:
    delete ((CustomObjectScript_08A1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A2:
    delete ((CustomObjectScript_08A2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08AF:
    delete ((CustomObjectScript_08AF *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1901:
    delete ((CustomObjectScript_1901 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090A:
    delete ((CustomObjectScript_090A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1109:
    delete ((CustomObjectScript_1109 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0908:
    delete ((CustomObjectScript_0908 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0907:
    delete ((CustomObjectScript_0907 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090C:
    delete ((CustomObjectScript_090C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_110D:
    delete ((CustomObjectScript_110D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_090B:
    delete ((CustomObjectScript_090B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_30A8:
    delete ((CustomObjectScript_30A8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0940:
    delete ((CustomObjectScript_0940 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0941:
    delete ((CustomObjectScript_0941 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0944:
    delete ((CustomObjectScript_0944 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B4:
    delete ((CustomObjectScript_08B4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08B3:
    delete ((CustomObjectScript_08B3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0943:
    delete ((CustomObjectScript_0943 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0942:
    delete ((CustomObjectScript_0942 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_18B8:
    delete ((CustomObjectScript_18B8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_20B1:
    delete ((CustomObjectScript_20B1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_089A:
    delete ((CustomObjectScript_089A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0945:
    delete ((CustomObjectScript_0945 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_192A:
    delete ((CustomObjectScript_192A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_092B:
    delete ((CustomObjectScript_092B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1021:
    delete ((CustomObjectScript_1021 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_092C:
    delete ((CustomObjectScript_092C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_112D:
    delete ((CustomObjectScript_112D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0861:
    delete ((CustomObjectScript_0861 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0862:
    delete ((CustomObjectScript_0862 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_186B:
    delete ((CustomObjectScript_186B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2071:
    delete ((CustomObjectScript_2071 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2148:
    delete ((CustomObjectScript_2148 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2059:
    delete ((CustomObjectScript_2059 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_205B:
    delete ((CustomObjectScript_205B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1947:
    delete ((CustomObjectScript_1947 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2146:
    delete ((CustomObjectScript_2146 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_205A:
    delete ((CustomObjectScript_205A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0923:
    delete ((CustomObjectScript_0923 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
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
  case ID_CUSTOM_OBJECT_1097:
  case ID_CUSTOM_OBJECT_08B5:
  case ID_CUSTOM_OBJECT_0895:
  case ID_CUSTOM_OBJECT_08A1:
  case ID_CUSTOM_OBJECT_08A2:
  case ID_CUSTOM_OBJECT_08AF:
  case ID_CUSTOM_OBJECT_1901:
  case ID_CUSTOM_OBJECT_090A:
  case ID_CUSTOM_OBJECT_1109:
  case ID_CUSTOM_OBJECT_0908:
  case ID_CUSTOM_OBJECT_0907:
  case ID_CUSTOM_OBJECT_090C:
  case ID_CUSTOM_OBJECT_110D:
  case ID_CUSTOM_OBJECT_090B:
  case ID_CUSTOM_OBJECT_30A8:
  case ID_CUSTOM_OBJECT_0940:
  case ID_CUSTOM_OBJECT_0941:
  case ID_CUSTOM_OBJECT_0944:
  case ID_CUSTOM_OBJECT_08B4:
  case ID_CUSTOM_OBJECT_08B3:
  case ID_CUSTOM_OBJECT_0943:
  case ID_CUSTOM_OBJECT_0942:
  case ID_CUSTOM_OBJECT_18B8:
  case ID_CUSTOM_OBJECT_20B1:
  case ID_CUSTOM_OBJECT_089A:
  case ID_CUSTOM_OBJECT_0945:
  case ID_CUSTOM_OBJECT_192A:
  case ID_CUSTOM_OBJECT_092B:
  case ID_CUSTOM_OBJECT_1021:
  case ID_CUSTOM_OBJECT_092C:
  case ID_CUSTOM_OBJECT_112D:
  case ID_CUSTOM_OBJECT_0861:
  case ID_CUSTOM_OBJECT_0862:
  case ID_CUSTOM_OBJECT_186B:
  case ID_CUSTOM_OBJECT_2071:
  case ID_CUSTOM_OBJECT_2148:
  case ID_CUSTOM_OBJECT_2059:
  case ID_CUSTOM_OBJECT_205B:
  case ID_CUSTOM_OBJECT_1947:
  case ID_CUSTOM_OBJECT_2146:
  case ID_CUSTOM_OBJECT_205A:
  case ID_CUSTOM_OBJECT_0923:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0020:
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
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0020;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[42];
  static int cust_id_list[42] = {
      ID_CUSTOM_OBJECT_1097, ID_CUSTOM_OBJECT_08B5, ID_CUSTOM_OBJECT_0895, ID_CUSTOM_OBJECT_08A1, ID_CUSTOM_OBJECT_08A2,
      ID_CUSTOM_OBJECT_08AF, ID_CUSTOM_OBJECT_1901, ID_CUSTOM_OBJECT_090A, ID_CUSTOM_OBJECT_1109, ID_CUSTOM_OBJECT_0908,
      ID_CUSTOM_OBJECT_0907, ID_CUSTOM_OBJECT_090C, ID_CUSTOM_OBJECT_110D, ID_CUSTOM_OBJECT_090B, ID_CUSTOM_OBJECT_30A8,
      ID_CUSTOM_OBJECT_0940, ID_CUSTOM_OBJECT_0941, ID_CUSTOM_OBJECT_0944, ID_CUSTOM_OBJECT_08B4, ID_CUSTOM_OBJECT_08B3,
      ID_CUSTOM_OBJECT_0943, ID_CUSTOM_OBJECT_0942, ID_CUSTOM_OBJECT_18B8, ID_CUSTOM_OBJECT_20B1, ID_CUSTOM_OBJECT_089A,
      ID_CUSTOM_OBJECT_0945, ID_CUSTOM_OBJECT_192A, ID_CUSTOM_OBJECT_092B, ID_CUSTOM_OBJECT_1021, ID_CUSTOM_OBJECT_092C,
      ID_CUSTOM_OBJECT_112D, ID_CUSTOM_OBJECT_0861, ID_CUSTOM_OBJECT_0862, ID_CUSTOM_OBJECT_186B, ID_CUSTOM_OBJECT_2071,
      ID_CUSTOM_OBJECT_2148, ID_CUSTOM_OBJECT_2059, ID_CUSTOM_OBJECT_205B, ID_CUSTOM_OBJECT_1947, ID_CUSTOM_OBJECT_2146,
      ID_CUSTOM_OBJECT_205A, ID_CUSTOM_OBJECT_0923};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
  cust_handle_list[1] = Object_handles[11];
  cust_handle_list[2] = Object_handles[12];
  cust_handle_list[3] = Object_handles[13];
  cust_handle_list[4] = Object_handles[14];
  cust_handle_list[5] = Object_handles[15];
  cust_handle_list[6] = Object_handles[16];
  cust_handle_list[7] = Object_handles[19];
  cust_handle_list[8] = Object_handles[22];
  cust_handle_list[9] = Object_handles[21];
  cust_handle_list[10] = Object_handles[20];
  cust_handle_list[11] = Object_handles[23];
  cust_handle_list[12] = Object_handles[24];
  cust_handle_list[13] = Object_handles[25];
  cust_handle_list[14] = Object_handles[29];
  cust_handle_list[15] = Object_handles[30];
  cust_handle_list[16] = Object_handles[31];
  cust_handle_list[17] = Object_handles[32];
  cust_handle_list[18] = Object_handles[33];
  cust_handle_list[19] = Object_handles[34];
  cust_handle_list[20] = Object_handles[35];
  cust_handle_list[21] = Object_handles[36];
  cust_handle_list[22] = Object_handles[37];
  cust_handle_list[23] = Object_handles[38];
  cust_handle_list[24] = Object_handles[39];
  cust_handle_list[25] = Object_handles[43];
  cust_handle_list[26] = Object_handles[45];
  cust_handle_list[27] = Object_handles[46];
  cust_handle_list[28] = Object_handles[47];
  cust_handle_list[29] = Object_handles[49];
  cust_handle_list[30] = Object_handles[51];
  cust_handle_list[31] = Object_handles[54];
  cust_handle_list[32] = Object_handles[55];
  cust_handle_list[33] = Object_handles[56];
  cust_handle_list[34] = Object_handles[57];
  cust_handle_list[35] = Object_handles[6];
  cust_handle_list[36] = Object_handles[1];
  cust_handle_list[37] = Object_handles[3];
  cust_handle_list[38] = Object_handles[5];
  cust_handle_list[39] = Object_handles[4];
  cust_handle_list[40] = Object_handles[2];
  cust_handle_list[41] = Object_handles[58];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 42;
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

    // Script 028: Level Begin (set wind, etc)
    if (1) {
      aObjSetLightingDist(Object_handles[16], 0.000000f);
      aMusicSetRegionAll(1);
      aUserVarSet(2, 0.000000f);
      aObjMakeInvuln(Object_handles[0], 999999);
      aObjMakeInvuln(Object_handles[6], 999999);
      aObjMakeInvuln(Object_handles[2], 999999);
      aObjMakeInvuln(Object_handles[4], 999999);
      aObjMakeInvuln(Object_handles[5], 999999);
      aObjMakeInvuln(Object_handles[3], 999999);
      aObjMakeInvuln(Object_handles[1], 999999);
      aRoomSetDamage(Room_indexes[6], 1.000000f, 4);
      aRoomSetDamage(Room_indexes[7], 1.000000f, 4);
      aRoomSetDamage(Room_indexes[5], 1.000000f, 4);
      aRoomSetWind(Room_indexes[9], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[10], 0.000000f, 3.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[11], 0.000000f, 2.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[12], 0.000000f, 1.500000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[13], 0.000000f, 1.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[14], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[15], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[16], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[17], 0.000000f, -20.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[18], 0.000000f, -30.000000f, 0.000000f, 1.000000f);
      aRoomSetWind(Room_indexes[19], 0.000000f, -20.000000f, 0.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }

    // Script 045: IntroCam
    if (1 == true) {
      aCinematicIntro(Path_indexes[1], Message_strings[18], Object_handles[29], Path_indexes[2], 20.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 036: Voice Over (Destroy)
    if (event_data->id == 2) {
      aSoundPlaySteaming("VoxL07SpecificB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }

    // Script 046: Voice Over (Magnet)
    if (event_data->id == 3) {
      aSoundPlaySteaming("VoxL07SpecificC.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 035: Movie Done--Play Sounds
    if ((ScriptActionCtr_035 < 1) && (1)) {
      aSetLevelTimer(30.000000f, 2);
      aSoundPlaySteaming("VoxL07StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1097::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 000: Turn off Turrets
    if ((ScriptActionCtr_000 < 1) && (1)) {
      aMusicSetRegionAll(2);
      aShowHUDMessage(Message_strings[1]);
      aPortalRenderSet(0, 0, Room_indexes[0], 1);
      aPortalRenderSet(0, 0, Room_indexes[1], 1);
      aPortalRenderSet(0, 0, Room_indexes[2], 1);
      aPortalRenderSet(0, 0, Room_indexes[3], 1);
      aObjSpark(Object_handles[1], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[2], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[3], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[4], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[5], 5.000000f, 99999.000000f);
      aObjSpark(Object_handles[6], 5.000000f, 99999.000000f);
      aAISetState(0, Object_handles[1]);
      aAISetState(0, Object_handles[2]);
      aAISetState(0, Object_handles[3]);
      aAISetState(0, Object_handles[4]);
      aAISetState(0, Object_handles[5]);
      aAISetState(0, Object_handles[6]);
      aObjDestroy(Object_handles[7]);
      aObjDestroy(Object_handles[8]);
      aObjDestroy(Object_handles[9]);
      aObjDestroy(Object_handles[10]);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 054: Primary Control
    if ((ScriptActionCtr_054 < 1) && (1)) {
      aShowHUDMessage(Message_strings[0]);
      aObjSetLightingDist(data->me_handle, 50.000000f);
      aObjMakeVulnerable(data->me_handle);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 4.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 027: SmokeSpewer (2)
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.150000f, -1.000000f, 4.000000f,
                  25.000000f, 1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0895::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 026: SmokeSpewer (1)
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.150000f, -1.000000f, 4.000000f,
                  25.000000f, 1, 1);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 023: FireSpewer (1)
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f, 5.000000f,
                  30.000000f, 1, 2);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 025: FireSpewer (2)
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f, 5.000000f,
                  30.000000f, 1, 3);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08AF::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 024: FireSpewer (3)
    if (1) {
      aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f, 5.000000f,
                  30.000000f, 1, 4);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1901::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 047: Do Cooler Actions
    if ((ScriptActionCtr_047 < 1) && (1)) {
      aCreatePopupView(0, Object_handles[17], 10.000000f, 1.000000f);
      if ((ScriptActionCtr_007 > 0) == true) {
        aCreatePopupView(0, Object_handles[18], 10.000000f, 1.000000f);
      } else {
        aCreatePopupView(0, Object_handles[17], 10.000000f, 1.000000f);
      }
      aTurnOffSpew(0);
      aTurnOffSpew(1);
      aTurnOffSpew(2);
      aTurnOffSpew(3);
      aTurnOffSpew(4);
      aObjSpark(Object_handles[16], 30.000000f, 999999.000000f);
      aSoundPlaySteaming("VoxL07SpecificA.osf", 1.000000f);
      aObjSetLightingDist(Object_handles[16], 0.000000f);
      aShowHUDMessage(Message_strings[2]);
      aTurnOnSpew(Object_handles[12], 0, 8, 1.000000f, 0.100000f, 65664, 0, 1.000000f, 0.100000f, 0.000000f, 3.000000f,
                  20.000000f, 0, 0);
      aTurnOnSpew(Object_handles[11], 0, 8, 1.000000f, 0.100000f, 65664, 0, 1.000000f, 0.100000f, 0.000000f, 3.000000f,
                  20.000000f, 0, 1);
      aTurnOnSpew(Object_handles[13], 0, 8, 1.000000f, 0.100000f, 65664, 0, 1.000000f, 0.100000f, 0.000000f, 3.000000f,
                  20.000000f, 0, 2);
      aTurnOnSpew(Object_handles[14], 0, 8, 1.000000f, 0.100000f, 65664, 0, 1.000000f, 0.100000f, 0.000000f, 3.000000f,
                  20.000000f, 0, 3);
      aTurnOnSpew(Object_handles[15], 0, 8, 1.000000f, 0.100000f, 65664, 0, 1.000000f, 0.100000f, 0.000000f, 3.000000f,
                  20.000000f, 0, 4);
      aRoomFogSetState(1, Room_indexes[4]);
      aRoomSetFog(Room_indexes[4], 0.100000f, 0.100000f, 0.100000f, 2000.000000f);
      aRoomChangeFog(Room_indexes[4], 0.100000f, 0.100000f, 0.100000f, 300.000000f, 30.000000f);
      aRoomChangeFog(Room_indexes[5], 0.100000f, 0.100000f, 0.100000f, 200.000000f, 10.000000f);
      aRoomChangeFog(Room_indexes[6], 0.100000f, 0.100000f, 0.100000f, 200.000000f, 10.000000f);
      aRoomChangeFog(Room_indexes[7], 0.100000f, 0.100000f, 0.100000f, 180.000000f, 10.000000f);
      aSetWaypoint(1);
      aRoomSetDamage(Room_indexes[5], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[7], 0.000000f, 4);
      aRoomSetDamage(Room_indexes[6], 0.000000f, 4);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 002: Four Coolers Destroyed (1)
    if ((qObjExists(Object_handles[20]) == false) && (qObjExists(Object_handles[21]) == false) &&
        (qObjExists(Object_handles[22]) == false)) {
      aSetObjectTimer(Object_handles[16], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1109::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 031: Four Coolers Destroyed (4)
    if ((qObjExists(Object_handles[20]) == false) && (qObjExists(Object_handles[21]) == false) &&
        (qObjExists(Object_handles[19]) == false)) {
      aSetObjectTimer(Object_handles[16], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0908::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 030: Four Coolers Destroyed (3)
    if ((qObjExists(Object_handles[20]) == false) && (qObjExists(Object_handles[19]) == false) &&
        (qObjExists(Object_handles[22]) == false)) {
      aSetObjectTimer(Object_handles[16], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0907::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 029: Four Coolers Destroyed (2)
    if ((qObjExists(Object_handles[19]) == false) && (qObjExists(Object_handles[21]) == false) &&
        (qObjExists(Object_handles[22]) == false)) {
      aSetObjectTimer(Object_handles[16], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Unlock Magnet Control Door (2)
    if ((ScriptActionCtr_004 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_003 > 0) == true) {
        aShowHUDMessage(Message_strings[3]);
        aDoorLockUnlock(0, Door_handles[0]);
      }
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_110D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Unlock Magnet Control Door (1)
    if ((ScriptActionCtr_003 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_004 > 0) == true) {
        aShowHUDMessage(Message_strings[3]);
        aDoorLockUnlock(0, Door_handles[0]);
      }
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_090B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Manual Activation Message (Magnet)
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_007 > 0) == false)) {
      aShowHUDMessage(Message_strings[4]);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 007: Magnet Controller
    if ((ScriptActionCtr_007 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSetLevelTimer(10.000000f, 3);
      aGoalCompleted(Goal_indexes[0], 1);
      aSetWaypoint(2);
      aShowHUDMessage(Message_strings[5]);
      aObjPlayAnim(data->me_handle, 0, 36, 5.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aTurnOnSpew(Object_handles[26], 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.150000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);
      aTurnOnSpew(Object_handles[27], 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.150000f, -1.000000f, 4.000000f,
                  25.000000f, 1, -1);
      aCreatePopupView(0, Object_handles[28], 8.000000f, 1.000000f);
      aDoorLockUnlock(0, Door_handles[1]);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_30A8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: Key Card Pickup
    if ((ScriptActionCtr_009 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
      aObjDelete(data->me_handle);
      aShowHUDMessage(Message_strings[6]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0940::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: Double FF Switch (1)
    if ((ScriptActionCtr_010 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_009 > 0) == true))) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      if ((ScriptActionCtr_011 > 0) == true) {
        aGoalCompleted(Goal_indexes[1], 1);
        aShowHUDMessage(Message_strings[7]);
        aPortalRenderSet(0, 2, Room_indexes[6], 1);
        aPortalRenderSet(0, 1, Room_indexes[6], 1);
      } else {
        aShowHUDMessage(Message_strings[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }

    // Script 012: Need Key FF Switch (1)
    if (((ScriptActionCtr_009 > 0) == false) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0941::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Double FF Switch (2)
    if ((ScriptActionCtr_011 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && ((ScriptActionCtr_009 > 0) == true))) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
      if ((ScriptActionCtr_010 > 0) == true) {
        aGoalCompleted(Goal_indexes[1], 1);
        aShowHUDMessage(Message_strings[7]);
        aPortalRenderSet(0, 1, Room_indexes[6], 1);
        aPortalRenderSet(0, 2, Room_indexes[6], 1);
      } else {
        aShowHUDMessage(Message_strings[8]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 013: Need Key FF Switch (2)
    if (((ScriptActionCtr_009 > 0) == false) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0944::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: Upper Magnet Tube Activation
    if ((ScriptActionCtr_014 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aGoalCompleted(Goal_indexes[2], 1);
      aShowHUDMessage(Message_strings[10]);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      if (((ScriptActionCtr_034 > 0) == true) && ((ScriptActionCtr_016 > 0) == true)) {
        aDoorLockUnlock(0, Door_handles[2]);
        aShowHUDMessage(Message_strings[11]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 033: Superheater begin (1)
    if ((ScriptActionCtr_033 < 1) && (1)) {
      aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.100000f, -1.000000f, 6.000000f,
                  70.000000f, 0, 5);
      aAISetState(1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08B3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 005: Superheater begin (2)
    if ((ScriptActionCtr_005 < 1) && (1)) {
      aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.100000f, -1.000000f, 6.000000f,
                  70.000000f, 0, 6);
      aAISetState(1, data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0943::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Shut off superheater (1)
    if ((ScriptActionCtr_032 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(60.000000f);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aTurnOffSpew(5);
      aAISetState(0, Object_handles[33]);
      aTurnOnSpew(Object_handles[33], 0, 8, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.100000f, 8.000000f, 5.000000f,
                  40.000000f, 0, -1);
      aShowHUDMessage(Message_strings[12]);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0942::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Shut off superheater (2)
    if ((ScriptActionCtr_015 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(60.000000f);
      aSoundPlayObject(Sound_indexes[4], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      aTurnOffSpew(6);
      aAISetState(0, Object_handles[34]);
      aTurnOnSpew(Object_handles[34], 0, 8, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.100000f, 8.000000f, 5.000000f,
                  40.000000f, 0, -1);
      aShowHUDMessage(Message_strings[12]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_18B8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 034: Virus Pickup (2)
    if ((ScriptActionCtr_034 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_016 > 0) == true) {
        aSoundPlaySteaming("VoxL07EndLevel.osf", 1.000000f);
        aGoalCompleted(Goal_indexes[3], 1);
        aGoalCompleted(Goal_indexes[4], 1);
        aShowHUDMessage(Message_strings[13]);
        if ((ScriptActionCtr_014 > 0) == true) {
          aDoorLockUnlock(0, Door_handles[2]);
          aShowHUDMessage(Message_strings[11]);
        }
      } else {
        aShowHUDMessage(Message_strings[14]);
      }
      aSoundPlayObject(Sound_indexes[5], data->me_handle, 1.000000f);
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_20B1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Virus Pickup (1)
    if ((ScriptActionCtr_016 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      if ((ScriptActionCtr_034 > 0) == true) {
        aSoundPlaySteaming("VoxL07EndLevel.osf", 1.000000f);
        aGoalCompleted(Goal_indexes[3], 1);
        aGoalCompleted(Goal_indexes[4], 1);
        aShowHUDMessage(Message_strings[13]);
        if ((ScriptActionCtr_014 > 0) == true) {
          aDoorLockUnlock(0, Door_handles[2]);
          aShowHUDMessage(Message_strings[11]);
        }
      } else {
        aShowHUDMessage(Message_strings[14]);
      }
      aSoundPlayObject(Sound_indexes[5], data->me_handle, 1.000000f);
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_089A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 037: Generic Smoke Spewer 4
    if (1) {
      aTurnOnSpew(Object_handles[40], 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.120000f, -1.000000f, 6.500000f,
                  40.000000f, 1, -1);
      aTurnOnSpew(Object_handles[41], 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.120000f, -1.000000f, 6.500000f,
                  40.000000f, 1, -1);
      aTurnOnSpew(Object_handles[42], 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.120000f, -1.000000f, 6.500000f,
                  40.000000f, 1, -1);
      aTurnOnSpew(data->me_handle, 0, 7, 1.000000f, 0.100000f, 65664, 0, 1.500000f, 0.120000f, -1.000000f, 6.500000f,
                  40.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0945::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Steam Release Switch
    if ((ScriptActionCtr_018 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aMiscViewerShake(40.000000f);
      aTurnOnSpew(Object_handles[44], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, 30.000000f, 5.000000f,
                  20.000000f, 0, -1);
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aShowHUDMessage(Message_strings[15]);
      aRoomSetFog(Room_indexes[8], 0.600000f, 0.600000f, 0.600000f, 3000.000000f);
      aRoomFogSetState(1, Room_indexes[8]);
      aRoomChangeFog(Room_indexes[8], 0.600000f, 0.600000f, 0.600000f, 400.000000f, 30.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_192A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Broken Pipe Part III (1)
    if (qUserVarValue(0) == 1.000000f) {
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 019: Broken Pipe Part I (1)
    if (1) {
      aUserVarSet(0, 0.000000f);
      aSetObjectTimer(data->me_handle, 5.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 020: Broken Pipe Part II (1)
    if (1) {
      if (qUserVarValue(0) == 0.000000f) {
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f, 3.000000f,
                    25.000000f, 1, -1);
        aSetObjectTimer(data->me_handle, 10.000000f, -1);
        aUserVarSet(0, 1.000000f);
      } else {
        aSetObjectTimer(data->me_handle, 20.000000f, -1);
        aUserVarSet(0, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_092B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: Broken Pipe Part III (2)
    if (qUserVarValue(1) == 1.000000f) {
      aObjDestroy(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 039: Broken Pipe Part I (2)
    if (1) {
      aUserVarSet(1, 0.000000f);
      aSetObjectTimer(data->me_handle, 5.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 040: Broken Pipe Part II (2)
    if (1) {
      if (qUserVarValue(1) == 0.000000f) {
        aTurnOnSpew(data->me_handle, 0, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 10.000000f, 3.000000f,
                    25.000000f, 1, -1);
        aSetObjectTimer(data->me_handle, 10.000000f, -1);
        aUserVarSet(1, 1.000000f);
      } else {
        aSetObjectTimer(data->me_handle, 20.000000f, -1);
        aUserVarSet(1, 0.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1021::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Camera Switch (1)
    if ((ScriptActionCtr_022 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qObjExists(Object_handles[48]) == true))) {
      aShowHUDMessage(Message_strings[16]);
      aCreatePopupView(0, Object_handles[48], 10.000000f, 1.800000f);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_092C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Camera Switch (3)
    if ((ScriptActionCtr_042 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qObjExists(Object_handles[50]) == true))) {
      aShowHUDMessage(Message_strings[16]);
      aCreatePopupView(0, Object_handles[50], 10.000000f, 1.800000f);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_112D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: Camera Switch (2)
    if ((ScriptActionCtr_041 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == true) && (qObjExists(Object_handles[52]) == true))) {
      aShowHUDMessage(Message_strings[16]);
      aCreatePopupView(0, Object_handles[52], 10.000000f, 1.800000f);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0861::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Controller-4
    if ((ScriptActionCtr_053 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aShowHUDMessage(Message_strings[20]);
      aUserVarInc(2);
      if (qUserVarValue(2) == 4.000000f) {
        aSetObjectTimer(Object_handles[0], 0.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0862::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Controller-3
    if ((ScriptActionCtr_052 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aShowHUDMessage(Message_strings[20]);
      aUserVarInc(2);
      if (qUserVarValue(2) == 4.000000f) {
        aSetObjectTimer(Object_handles[0], 0.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_186B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Controller-2
    if ((ScriptActionCtr_051 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aShowHUDMessage(Message_strings[20]);
      aUserVarInc(2);
      if (qUserVarValue(2) == 4.000000f) {
        aSetObjectTimer(Object_handles[0], 0.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2071::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Controller-1
    if ((ScriptActionCtr_001 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[1], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aShowHUDMessage(Message_strings[20]);
      aUserVarInc(2);
      if (qUserVarValue(2) == 4.000000f) {
        aSetObjectTimer(Object_handles[0], 0.000000f, 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2148::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 080: Turret Invuln1
    if ((ScriptActionCtr_080 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == 1) && ((ScriptActionCtr_000 > 0) == false))) {
      aSetObjectTimer(Object_handles[6], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 081: TurretMessage
    if ((ScriptActionCtr_081 < 3) && (1)) {
      aShowHUDMessage(Message_strings[21]);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2059::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 086: Turret Invuln6
    if ((ScriptActionCtr_086 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == 1) && ((ScriptActionCtr_000 > 0) == false))) {
      aSetObjectTimer(Object_handles[6], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_205B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Turret Invuln5
    if ((ScriptActionCtr_085 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == 1) && ((ScriptActionCtr_000 > 0) == false))) {
      aSetObjectTimer(Object_handles[6], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1947::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 084: Turret Invuln4
    if ((ScriptActionCtr_084 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == 1) && ((ScriptActionCtr_000 > 0) == false))) {
      aSetObjectTimer(Object_handles[6], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2146::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Turret Invuln3
    if ((ScriptActionCtr_083 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == 1) && ((ScriptActionCtr_000 > 0) == false))) {
      aSetObjectTimer(Object_handles[6], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_205A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: Turret Invuln2
    if ((ScriptActionCtr_082 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == 1) && ((ScriptActionCtr_000 > 0) == false))) {
      aSetObjectTimer(Object_handles[6], 0.000000f, -1);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0923::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 087: Boxes
    if (1) {
      aObjDestroy(Object_handles[59]);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: EndLevel!!!
    if ((ScriptActionCtr_043 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);
      aStartEndlevelSequence(Object_handles[53], Path_indexes[0], 5.000000f, Message_strings[17]);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Waypoint 3
    if (1) {
      aSetWaypoint(3);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: VirusCam(2)
    if ((ScriptActionCtr_049 < 1) && (((ScriptActionCtr_048 > 0) == false) && ((ScriptActionCtr_011 > 0) == true) &&
                                      ((ScriptActionCtr_010 > 0) == true))) {
      aShowHUDMessage(Message_strings[19]);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 079: Music-Virus2
    if (((ScriptActionCtr_010 > 0) == true) && ((ScriptActionCtr_011 > 0) == true)) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: VirusCam(1)
    if ((ScriptActionCtr_048 < 1) && (((ScriptActionCtr_010 > 0) == true) && ((ScriptActionCtr_011 > 0) == true) &&
                                      ((ScriptActionCtr_049 > 0) == false))) {
      aShowHUDMessage(Message_strings[19]);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }

    // Script 078: Music-Virus1
    if (((ScriptActionCtr_010 > 0) == true) && ((ScriptActionCtr_011 > 0) == true)) {
      aMusicSetRegion(7, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Music-Green8
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Music-Green7
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Music-Green5
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Music-Green2(Tech)
    if ((ScriptActionCtr_000 > 0) == true) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Music-Green1
    if ((ScriptActionCtr_000 > 0) == true) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Music-Red4
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

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Music-Red3
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

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Music-Red2
    if ((ScriptActionCtr_000 > 0) == true) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Music-Red1
    if ((ScriptActionCtr_000 > 0) == true) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Music-Tech5
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music-Tech3
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: Music-Research
    if (1) {
      aMusicSetRegion(6, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_071 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_071++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Music-Escape
    if (1) {
      aMusicSetRegion(8, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Music-Defense4
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

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Music-Defense3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Music-Defense2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Music-Defense1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: MagnetTubeStop-1
    if (1) {
      aSoundPlayObject(Sound_indexes[6], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 30.000000f, 50.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: MagnetTubeStart-1
    if (1) {
      aSoundPlayObject(Sound_indexes[7], event_data->it_handle, 1.000000f);
      aMiscShakeArea(event_data->it_handle, 40.000000f, 50.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
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
NEXT_ID		88

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:BrokenPipe 1
1:BrokenPipe 2
2:Controls
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:SmokeSpew1
1:SmokeSpew2
2:FireSpew1
3:FireSpew2
4:FireSpew3
5:SuperSpew1
6:SuperSpew2
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:MissionMessage
1:ControlActivate
2:VoiceOver1
3:VoiceOver2
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
MagnetControlDoor
MagnetTubeDoor
VirusDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
TurretControlSwitch
Repeater-6
Repeater-2
Repeater-5
Repeater-3
Repeater-4
Repeater-1
MiniTurret-1
MiniTurret-2
MiniTurret-3
MiniTurret-4
CoolSpewer-2
CoolSpewer-1
MagnetSpewer-2
MagnetSpewer-1
VirusSpewer
CoolerMain
CoolingView
VirusView
CoolControl-1
CoolControl-2
CoolControl-3
CoolControl-4
MagnetSwitch-2
MagnetSwitch-1
MagnetController
MTubeSpewer-1
MTubeSpewer-2
MTubeView
FFKey
FFSwitch-1
FFSwitch-2
LowerSwitch-1
FireSpewer-1
FireSpewer-2
LowerSwitch-2
LowerSwitch-3
Virus-2
Virus-1
MidSpewer-4
MidSpewer-1
MidSpewer-2
MidSpewer-3
SteamSwitch
SteamSpewer
BlastPipe-1
BlastPipe-2
SwitchCamera-Cooler
CameraCooler
SwitchCamera-Magnet
Camera-Magnet
CSwitch-Virus
Camera-Virus
EndCam
Controller-4
Controller-3
Controller-2
Controller-1
BoxBottom1
BoxPhysics
$$OBJECT_LIST_END

$$ROOM_LIST_START
Entrance-4
Entrance-1
Entrance-2
Entrance-3
CoolerRoom
MagnetRoom
FireRoom-1
FireRoom-2
SteamingRoom
UpTube-1
UpTube-2
UpTube-3
UpTube-4
UpTube-5
UpTube-6
UpTube-7
UpTube-8
DownTube-4
DownTube-3
DownTube-2
$$ROOM_LIST_END

$$TRIGGER_LIST_START
EndLevelStart
EnteringBottom
VirusEnter2
VirusEnter1
Music-Green8
Music-Green7
Music-Green5
Music-Green2
Music-Green1
Music-Red4
Music-Red3
Music-Red2
Music-Red1
Music-Tech5
Music-Tech3
Music-Bunker
Music-Escape
Music-Defense4
Music-Defense3
Music-Defense2
Music-Defense1
DownTube-WayPoint
MagnetStart-1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch41
AmbSwitch31
AmbSwitch21
Powerup pickup
AmbSwitch11
PupC1
LevSecAccelRelease
LevSecAccelStart
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
EndLevel
IntroCam
IntroShip
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Enable descending accelerator
Disable containment forcefields
Activate the Ascending Elevator
Steal the Virus Samples
Get both virus samples
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL07SpecificA.osf
VoxL07EndLevel.osf
VoxL07StartLevel.osf
VoxL07SpecificB.osf
VoxL07SpecificC.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:54:Primary Control
        $$CHILD_BLOCK_START
        01:1:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ControlVulnerable:Message
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
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
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:0:Turn off Turrets
        $$CHILD_BLOCK_START
        01:1:0
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:2:Region
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TurretsDeactivated:Message
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
                        10:4:0:PortalNum
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
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:5.000000:SparkRate
                        10:6:99999.000000:Time
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
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:SmokeSpewer (2)
        $$CHILD_BLOCK_START
        01:1:11
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:SmokeSpewer (1)
        $$CHILD_BLOCK_START
        01:1:12
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:FireSpewer (1)
        $$CHILD_BLOCK_START
        01:1:13
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:FireSpewer (2)
        $$CHILD_BLOCK_START
        01:1:14
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:FireSpewer (3)
        $$CHILD_BLOCK_START
        01:1:15
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Do Cooler Actions
        $$CHILD_BLOCK_START
        01:1:16
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:17:Object
                        10:6:10.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:7:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:18:Object
                                10:6:10.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aCreatePopupView
                                $$CHILD_BLOCK_START
                                10:4:0:GunPoint
                                10:1:0:17:Object
                                10:6:10.000000:Time
                                10:6:1.000000:Zoom
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
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
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:30.000000:SparkRate
                        10:6:999999.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CoolersAllGone:Message
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:15:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:4:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.100000:Red
                        10:6:0.100000:Green
                        10:6:0.100000:Blue
                        10:6:2000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:0.100000:Red
                        10:6:0.100000:Green
                        10:6:0.100000:Blue
                        10:6:300.000000:Depth
                        10:6:30.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.100000:Red
                        10:6:0.100000:Green
                        10:6:0.100000:Blue
                        10:6:200.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.100000:Red
                        10:6:0.100000:Green
                        10:6:0.100000:Blue
                        10:6:200.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.100000:Red
                        10:6:0.100000:Green
                        10:6:0.100000:Blue
                        10:6:180.000000:Depth
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:1:Number
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:0.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Four Coolers Destroyed (1)
        $$CHILD_BLOCK_START
        01:1:19
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:22:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Four Coolers Destroyed (4)
        $$CHILD_BLOCK_START
        01:1:22
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Four Coolers Destroyed (3)
        $$CHILD_BLOCK_START
        01:1:21
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:20:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:22:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Four Coolers Destroyed (2)
        $$CHILD_BLOCK_START
        01:1:20
        02:4
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:22:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:16:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Unlock Magnet Control Door (2)
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:3:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MagnetTubeDoorUnlock:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
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
00:3:Unlock Magnet Control Door (1)
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:4:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:MagnetTubeDoorUnlock:Message
                                $$CHILD_BLOCK_END
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:0:DoorName
                                $$CHILD_BLOCK_END
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
00:6:Manual Activation Message (Magnet)
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:7:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ManualActivation:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Magnet Controller
        $$CHILD_BLOCK_START
        01:1:25
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetWaypoint
                        $$CHILD_BLOCK_START
                        10:4:2:Number
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:MagnetActivated:Message
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:StartFrame
                        10:4:36:EndFrame
                        10:6:5.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:26:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:25.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:28:Object
                        10:6:8.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aDoorLockUnlock
                        $$CHILD_BLOCK_START
                        10:10:0:0:Lock/Unlock
                        10:0:0:1:DoorName
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Key Card Pickup
        $$CHILD_BLOCK_START
        01:1:29
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
                        10:12:3:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FFKeyPickup:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Double FF Switch (1)
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FFDisabled:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FFDisable1:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Double FF Switch (2)
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FFDisabled:Message
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:1:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:2:PortalNum
                                10:2:6:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FFDisable1:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Need Key FF Switch (1)
        $$CHILD_BLOCK_START
        01:1:30
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:NeedFFKey:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Need Key FF Switch (2)
        $$CHILD_BLOCK_START
        01:1:31
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:NeedFFKey:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Upper Magnet Tube Activation
        $$CHILD_BLOCK_START
        01:1:32
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:UpperTubeActivate:Message
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
                03:1
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
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:16:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aDoorLockUnlock
                                $$CHILD_BLOCK_START
                                10:10:0:0:Lock/Unlock
                                10:0:0:2:DoorName
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ContainmentDoorUnlocked:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Superheater begin (1)
        $$CHILD_BLOCK_START
        01:1:33
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
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
                        10:6:2.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Superheater begin (2)
        $$CHILD_BLOCK_START
        01:1:34
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
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
                        10:6:2.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Shut off superheater (1)
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Amount
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
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:5:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:33:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SuperHeaterShutdown:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Shut off superheater (2)
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Amount
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
                08:aTurnOffSpew
                        $$CHILD_BLOCK_START
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:34:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:2.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SuperHeaterShutdown:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Virus Pickup (2)
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
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:1:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:3:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Virus2Collected:Message
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:14:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aDoorLockUnlock
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Lock/Unlock
                                        10:0:0:2:DoorName
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ContainmentDoorUnlocked:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Virus1Collected:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Virus Pickup (1)
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
        04:0:0:1
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:34:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlaySteaming
                                $$CHILD_BLOCK_START
                                10:19:1:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:3:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Virus2Collected:Message
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:14:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aDoorLockUnlock
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Lock/Unlock
                                        10:0:0:2:DoorName
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ContainmentDoorUnlocked:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:Virus1Collected:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Generic Smoke Spewer 4
        $$CHILD_BLOCK_START
        01:1:39
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:40:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.500000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.500000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.500000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:1.000000:Mass
                        10:6:0.100000:Drag
                        10:15:65664:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:6.500000:BlobSize
                        10:6:40.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Steam Release Switch
        $$CHILD_BLOCK_START
        01:1:43
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:30.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:SteamRelease:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.600000:Red
                        10:6:0.600000:Green
                        10:6:0.600000:Blue
                        10:6:3000.000000:Depth
                        $$CHILD_BLOCK_END
                08:aRoomFogSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:8:Room
                        $$CHILD_BLOCK_END
                08:aRoomChangeFog
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:0.600000:Red
                        10:6:0.600000:Green
                        10:6:0.600000:Blue
                        10:6:400.000000:Depth
                        10:6:30.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Broken Pipe Part I (1)
        $$CHILD_BLOCK_START
        01:1:45
        02:2
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Broken Pipe Part II (1)
        $$CHILD_BLOCK_START
        01:1:45
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
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.300000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:10.000000:SpewLife
                                10:6:3.000000:BlobSize
                                10:6:25.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:10.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:20.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Broken Pipe Part III (1)
        $$CHILD_BLOCK_START
        01:1:45
        02:0
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Broken Pipe Part I (2)
        $$CHILD_BLOCK_START
        01:1:46
        02:2
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:5.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Broken Pipe Part II (2)
        $$CHILD_BLOCK_START
        01:1:46
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
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:GunNum
                                10:10:0:2:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.300000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:10.000000:SpewLife
                                10:6:3.000000:BlobSize
                                10:6:25.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:10.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:6:20.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserVar
                                10:6:0.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Broken Pipe Part III (2)
        $$CHILD_BLOCK_START
        01:1:46
        02:0
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Camera Switch (1)
        $$CHILD_BLOCK_START
        01:1:47
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
                                        10:1:0:48:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CameraActivation:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:48:Object
                        10:6:10.000000:Time
                        10:6:1.800000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Camera Switch (3)
        $$CHILD_BLOCK_START
        01:1:49
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
                                        10:1:0:50:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CameraActivation:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:50:Object
                        10:6:10.000000:Time
                        10:6:1.800000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Camera Switch (2)
        $$CHILD_BLOCK_START
        01:1:51
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
                                        10:1:0:52:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CameraActivation:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:52:Object
                        10:6:10.000000:Time
                        10:6:1.800000:Zoom
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Level Begin (set wind, etc)
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
                        10:1:0:16:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aMusicSetRegionAll
                        $$CHILD_BLOCK_START
                        10:10:0:1:Region
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:2:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
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
                        10:1:0:3:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:999999:Time
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:1.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:1.000000:Damage
                        10:10:0:4:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:1.000000:Damage
                        10:10:0:4:DamageSoundType
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
                        10:2:10:Room
                        10:6:0.000000:X
                        10:6:3.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:2.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:12:Room
                        10:6:0.000000:X
                        10:6:1.500000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:13:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:14:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:15:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:16:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:17:Room
                        10:6:0.000000:X
                        10:6:-20.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:18:Room
                        10:6:0.000000:X
                        10:6:-30.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:19:Room
                        10:6:0.000000:X
                        10:6:-20.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:EndLevel!!!
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequence
                        $$CHILD_BLOCK_START
                        10:1:0:53:Camera
                        10:16:0:PlayerPath
                        10:6:5.000000:Time
                        10:8:Finished:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Waypoint 3
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
                        10:4:3:Number
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:IntroCam
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
                        10:16:1:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:29:TotallyNotUsedTarget
                        10:16:2:PlayerPath
                        10:6:20.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Movie Done--Play Sounds
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Voice Over (Destroy)
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Voice Over (Magnet)
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:VirusCam(2)
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:48:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:VirusDescription:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:VirusCam(1)
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:49:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:VirusDescription:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Controller-4
        $$CHILD_BLOCK_START
        01:1:54
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Controller:Message
                        $$CHILD_BLOCK_END
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:6:0.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Controller-3
        $$CHILD_BLOCK_START
        01:1:55
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Controller:Message
                        $$CHILD_BLOCK_END
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:6:0.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Controller-2
        $$CHILD_BLOCK_START
        01:1:56
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Controller:Message
                        $$CHILD_BLOCK_END
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:6:0.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Controller-1
        $$CHILD_BLOCK_START
        01:1:57
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Controller:Message
                        $$CHILD_BLOCK_END
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
                                10:6:4.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:0:Object
                                10:6:0.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Music-Green8
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Music-Green7
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
00:59:Music-Green5
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
00:56:Music-Green2(Tech)
        $$CHILD_BLOCK_START
        01:0:7
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:0:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
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
00:63:Music-Green1
        $$CHILD_BLOCK_START
        01:0:8
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:0:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
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
00:66:Music-Red4
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
00:65:Music-Red3
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
00:64:Music-Red2
        $$CHILD_BLOCK_START
        01:0:11
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:0:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
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
00:55:Music-Red1
        $$CHILD_BLOCK_START
        01:0:12
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qScriptExecuted_DALLAS:Bool
                                $$CHILD_BLOCK_START
                                10:11:0:ScriptID
                                $$CHILD_BLOCK_END
                        07:0:6
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
00:76:Music-Tech5
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:Music-Tech3
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
00:71:Music-Research
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
00:77:Music-Escape
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
                        10:10:0:8:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:70:Music-Defense4
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
00:69:Music-Defense3
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Music-Defense2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:Music-Virus1
        $$CHILD_BLOCK_START
        01:0:3
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
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
00:79:Music-Virus2
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
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
00:67:Music-Defense1
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:TurretMessage
        $$CHILD_BLOCK_START
        01:1:6
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:3
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TurretsInvuln:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Turret Invuln6
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Turret Invuln5
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Turret Invuln4
        $$CHILD_BLOCK_START
        01:1:5
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Turret Invuln3
        $$CHILD_BLOCK_START
        01:1:4
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:Turret Invuln2
        $$CHILD_BLOCK_START
        01:1:2
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Turret Invuln1
        $$CHILD_BLOCK_START
        01:1:6
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjIsPlayerWeapon:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:0:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Boxes
        $$CHILD_BLOCK_START
        01:1:58
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:MagnetTubeStop-1
        $$CHILD_BLOCK_START
        01:0:21
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:30.000000:Amount
                        10:6:50.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:MagnetTubeStart-1
        $$CHILD_BLOCK_START
        01:0:22
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:40.000000:Amount
                        10:6:50.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
