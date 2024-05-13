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
// Filename:	level14.cpp
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

#define ID_CUSTOM_OBJECT_10B8 0x001
#define ID_CUSTOM_OBJECT_0892 0x002
#define ID_CUSTOM_OBJECT_0891 0x003
#define ID_CUSTOM_OBJECT_0890 0x004
#define ID_CUSTOM_OBJECT_08A8 0x005
#define ID_CUSTOM_OBJECT_08A7 0x006
#define ID_CUSTOM_OBJECT_180F 0x007
#define ID_CUSTOM_OBJECT_1081 0x008
#define ID_CUSTOM_OBJECT_186D 0x009
#define ID_CUSTOM_OBJECT_08D3 0x00a
#define ID_CUSTOM_OBJECT_188F 0x00b
#define ID_CUSTOM_OBJECT_0888 0x00c
#define ID_CUSTOM_OBJECT_204F 0x00d
#define ID_CUSTOM_OBJECT_2870 0x00e
#define ID_CUSTOM_OBJECT_1025 0x00f
#define ID_CUSTOM_OBJECT_08A0 0x010
#define ID_CUSTOM_OBJECT_189E 0x011
#define ID_CUSTOM_OBJECT_109B 0x012
#define ID_CUSTOM_OBJECT_109D 0x013
#define ID_CUSTOM_OBJECT_409A 0x014
#define ID_CUSTOM_OBJECT_309C 0x015
#define ID_CUSTOM_OBJECT_1083 0x016
#define ID_CUSTOM_OBJECT_088A 0x017
#define ID_CUSTOM_OBJECT_188B 0x018
#define ID_CUSTOM_OBJECT_088C 0x019
#define ID_CUSTOM_OBJECT_088D 0x01a
#define ID_CUSTOM_OBJECT_088E 0x01b
#define ID_CUSTOM_OBJECT_2880 0x01c
#define ID_CUSTOM_OBJECT_10C3 0x01d
#define ID_CUSTOM_OBJECT_4089 0x01e
#define ID_CUSTOM_OBJECT_406F 0x01f
#define ID_CUSTOM_OBJECT_1082 0x020
#define ID_CUSTOM_OBJECT_10D5 0x021
#define ID_CUSTOM_OBJECT_10D4 0x022
#define ID_CUSTOM_OBJECT_10D6 0x023
#define ID_CUSTOM_OBJECT_0917 0x024
#define ID_CUSTOM_OBJECT_10D7 0x025

#define ID_TRIGGER_0009 0x026
#define ID_TRIGGER_0007 0x027
#define ID_TRIGGER_0001 0x028
#define ID_TRIGGER_0005 0x029
#define ID_TRIGGER_0003 0x02a
#define ID_TRIGGER_0008 0x02b
#define ID_TRIGGER_0006 0x02c
#define ID_TRIGGER_0004 0x02d
#define ID_TRIGGER_0002 0x02e

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

class CustomObjectScript_10B8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0892 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0891 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0890 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A8 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_180F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1081 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_186D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08D3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_188F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0888 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_204F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2870 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1025 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_08A0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_189E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_109B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_109D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_409A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_309C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1083 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_088A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_188B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_088C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_088D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_088E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2880 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10C3 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_4089 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_406F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1082 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0917 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_10D7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_066 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_066 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

/*
$$ENUM Region
0:Intro
1:Top
2:Mid
3:Bottom
4:Wing
$$END
*/

// Enter your custom script code here
struct tTextureInfo {
  const char *room_name;
  int room_id;
  int face_num;
};

#define NUM_MONITORS 11

static bool TextureInfoInitialized = false;

static tTextureInfo texture_info[NUM_MONITORS] = {
    {"Beam Emitter Rm", 0, 1775}, {"EmitterRm DataTerm", 0, 50}, {"Room 51", 0, 2},
    {"SubObs DataTerm", 0, 50},   {"SubObs Console2", 0, 50},    {"Emitter Generator", 0, 286},
    {"Dock Console", 0, 50},      {"West Dock Console", 0, 50},  {"Room 69", 0, 125},
    {"Room 82", 0, 125},          {"Control DataTerm", 0, 50}};

struct tMatcenInfo {
  const char *matcen_name;
  int matcen_id;
};

#define NUM_MATCENS 14

static bool MatcenInfoInitialized = false;

static tMatcenInfo matcen_info[NUM_MATCENS] = {{"StartingDock Matcen", 0}, {"West Dock", 0},      {"Parts Room", 0},
                                               {"Con Room Matcen1", 0},    {"Powerup Rm1", 0},    {"Powerup Rm2", 0},
                                               {"Powerup Rm3", 0},         {"Powerup Rm4", 0},    {"Powerup Rm5", 0},
                                               {"SubObs Matcen1", 0},      {"SubObs Matcen2", 0}, {"SubObs Matcen3", 0},
                                               {"Emitter Room Matcen", 0}, {"Radio Rm", 0}};

/*
$$CATEGORIES
Custom
$$END

$$ACTION
Custom
Set texture on monitors to [u:Texture]
aSetTextureForMonitors
Sets all the monitors to a given texture

Parameters:
  TextureName: the texture to assign
$$END
*/
void aSetTextureForMonitors(int texture_id) {
  int j;

  if (!TextureInfoInitialized) {
    for (j = 0; j < NUM_MONITORS; j++)
      texture_info[j].room_id = Scrpt_FindRoomName(texture_info[j].room_name);
    TextureInfoInitialized = true;
  }

  for (j = 0; j < NUM_MONITORS; j++)
    aRoomSetFaceTexture(texture_info[j].room_id, texture_info[j].face_num, texture_id);
}

/*
$$ACTION
Custom
[e:Enable/Disable] level matcen group A
aMatcenGroupASetEnableState
Enable/disable matcen
Enable or disable a matcen group, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
$$END
*/
void aMatcenGroupASetEnableState(int state) {
  int j;

  if (!MatcenInfoInitialized) {
    for (j = 0; j < NUM_MATCENS; j++)
      matcen_info[j].matcen_id = Scrpt_FindMatcenName(matcen_info[j].matcen_name);
    MatcenInfoInitialized = true;
  }

  for (j = 0; j < 4; j++)
    aMatcenSetEnableState(state, matcen_info[j].matcen_id);
}

/*
$$ACTION
Custom
[e:Enable/Disable] level matcen group B
aMatcenGroupBSetEnableState
Enable/disable matcen
Enable or disable a matcen group, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
$$END
*/
void aMatcenGroupBSetEnableState(int state) {
  int j;

  if (!MatcenInfoInitialized) {
    for (j = 0; j < NUM_MATCENS; j++)
      matcen_info[j].matcen_id = Scrpt_FindMatcenName(matcen_info[j].matcen_name);
    MatcenInfoInitialized = true;
  }

  for (j = 4; j < 9; j++)
    aMatcenSetEnableState(state, matcen_info[j].matcen_id);
}

/*
$$ACTION
Custom
[e:Enable/Disable] level matcen group C
aMatcenGroupCSetEnableState
Enable/disable matcen
Enable or disable a matcen group, so it's capable of producing

Parameters:
  Enable/Disable: whether the matcen is cabable of producing
$$END
*/
void aMatcenGroupCSetEnableState(int state) {
  int j;

  if (!MatcenInfoInitialized) {
    for (j = 0; j < NUM_MATCENS; j++)
      matcen_info[j].matcen_id = Scrpt_FindMatcenName(matcen_info[j].matcen_name);
    MatcenInfoInitialized = true;
  }

  for (j = 9; j < NUM_MATCENS; j++)
    aMatcenSetEnableState(state, matcen_info[j].matcen_id);
}

/*
$$ACTION
Custom
Initialize Bypass Connector display
aInitBypassConnDisplay
Intialize Bypass Connector display
  Initializes the HUD bypass connector display

$$END
*/
void aInitBypassConnDisplay() {}

/*
$$ACTION
Custom
Update Bypass Connector display with [s:Message] at [i:Number]
aUpdateBypassConnDisplay
Update Bypass Connector display
  Updates the HUD Bypass Connector display

$$END
*/
void aUpdateBypassConnDisplay(const char *text, int level) {
  msafe_struct mstruct;

  mstruct.color = GR_RGB(0, 255, 0);
  snprintf(mstruct.message, sizeof(mstruct.message), text, level);
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

#define NUM_DOOR_NAMES 1
static const char *const Door_names[NUM_DOOR_NAMES] = {"EquipRm Door"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 63
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Power Conduit1",
                                                           "Power Conduit2",
                                                           "Power Conduit3",
                                                           "AntiVirus Program",
                                                           "Power SW1",
                                                           "Power SW2",
                                                           "Power SW3",
                                                           "Bypass Conn1",
                                                           "Bypass Conn2",
                                                           "Bypass Conn3",
                                                           "Equip Door Key",
                                                           "Emitter Rm Link",
                                                           "West Dock Link",
                                                           "Control Rm Link",
                                                           "Emitter Output Dia",
                                                           "Override Switch",
                                                           "Shield Tog1",
                                                           "Shield Tog2",
                                                           "Shield Tog3",
                                                           "Shield Tog4",
                                                           "Shielding Bump SW",
                                                           "Node1",
                                                           "Node2",
                                                           "Node3",
                                                           "Node4",
                                                           "Node5",
                                                           "Node6",
                                                           "Escape Shuttle",
                                                           "ShuttleSwitch",
                                                           "ShuttleReleaseClaw",
                                                           "Emitter Igniter",
                                                           "Destroyable Lens",
                                                           "Spare Emitter Lens",
                                                           "Lens Position",
                                                           "EmitterBeamDest",
                                                           "Beam Journal",
                                                           "Shield Journal",
                                                           "Virus Journal",
                                                           "Power Journal",
                                                           "Robot Journal",
                                                           "Dial Journal",
                                                           "Spew1",
                                                           "Spewer2",
                                                           "Spewer3",
                                                           "Spewer4",
                                                           "Spewer6",
                                                           "Spewer7",
                                                           "Spewer8",
                                                           "Spew9",
                                                           "Spew11",
                                                           "Spew12",
                                                           "Spew13",
                                                           "Spew14",
                                                           "Spew15",
                                                           "Spew16",
                                                           "Spew19",
                                                           "Spew20",
                                                           "Spew22",
                                                           "Spew23",
                                                           "Spew24",
                                                           "Spew25",
                                                           "Spew26",
                                                           "Spew27"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 3
static const char *const Room_names[NUM_ROOM_NAMES] = {"Terrarium Room", "Beam Emitter Rm", "Shuttle Bay"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 9
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "AudioStream3", "MWing-1", "MTop-1", "MBottom-2", "MBottom-1", "MMiddle-4", "MMiddle-3", "MMiddle-2", "MMiddle-1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 5
static const char *const Sound_names[NUM_SOUND_NAMES] = {"AmbSwitch31", "Powerup pickup", "AmbSwitch11", "AmbSwitch21",
                                                         "AmbExplosionFarC"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 16
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"DataLogon",
                                                             "DataScroll",
                                                             "CEDSignSilverLogo",
                                                             "CEDUploadAnti",
                                                             "NanoStat",
                                                             "Nano1",
                                                             "Nano2",
                                                             "Nano3",
                                                             "Nano4",
                                                             "CEDUpSucOn",
                                                             "C-SS Omnicron",
                                                             "Ed",
                                                             "Korea_Matcen_Shield",
                                                             "CED-Forcefield",
                                                             "Lightning3",
                                                             "ThickLineLightning"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 7
static const char *const Path_names[NUM_PATH_NAMES] = {"IntroCamPath",       "IntroPlayerPath", "EscapeShuttlePathA",
                                                       "EscapeShuttlePathB", "LensRobotPath",   "EndCamPath",
                                                       "EndPlayerPath"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 1
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Emitter Rm Matcen2"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 14
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Find Three Bypass Connectors",
                                                       "Find Equipment Room Key",
                                                       "Start Transmitter Control System",
                                                       "Upload Anti-Virus Program",
                                                       "Enable Defense Network Output",
                                                       "Deactivate Beam Emitter Shield",
                                                       "Align Mirror Nodes",
                                                       "Free Escape Shuttle",
                                                       "Ignite Beam Emitter",
                                                       "Supply Power to Beam Igniter",
                                                       "Find Spare Emitter Lens",
                                                       "Replace Emitter Lens",
                                                       "Ensure Success of Transmission",
                                                       "Broadcast the Anti-Virus Program"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 55
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroText",
                                                             "Empty",
                                                             "BypassConnDisplay",
                                                             "PowerOffline",
                                                             "PowerOnline",
                                                             "FoundAllBypassConns",
                                                             "FoundBypassConn",
                                                             "FoundEquipRmKey",
                                                             "DataLinkAlreadyActive",
                                                             "DataLinkFixed",
                                                             "SystemStarting",
                                                             "DataLinkError",
                                                             "GotCoreMaterial",
                                                             "UploadStarted",
                                                             "UploadError",
                                                             "UseCoreMaterialFailed",
                                                             "SystemStarted",
                                                             "OmnicronDisplayed",
                                                             "BumpDialError",
                                                             "DialCodeEntered",
                                                             "DialCodeIncorrect",
                                                             "DialSwitchError",
                                                             "ShieldCodeSeqStart",
                                                             "ShieldCodeSeqReset",
                                                             "ShieldDeactivated",
                                                             "ShieldCodeIncorrect",
                                                             "ShuttleFreed",
                                                             "BeamIgnited",
                                                             "BeamIgniteError6",
                                                             "BeamIgniteError5",
                                                             "BeamIgniteError4",
                                                             "BeamIgniteError3",
                                                             "BeamIgniteError2",
                                                             "BeamIgniteError1",
                                                             "LensRobotWarning",
                                                             "LensDestroyed",
                                                             "GotSpareLens",
                                                             "UseLensCompleted",
                                                             "UseLensFailed2",
                                                             "UseLensFailed1",
                                                             "MirrorNodesUnaligned",
                                                             "PowerInsufficient",
                                                             "TransmissionComplete",
                                                             "JournalBeamGame",
                                                             "JournalBeamHUD",
                                                             "JournalShieldGame",
                                                             "JournalShieldHUD",
                                                             "JournalVirusGame",
                                                             "JournalVirusHUD",
                                                             "JournalPowerGame",
                                                             "JournalPowerHUD",
                                                             "JournalRobotGame",
                                                             "JournalRobotHUD",
                                                             "JournalDialGame",
                                                             "JournalDialHUD"};
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
    strcpy(filename, "level14.msg");
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
  case ID_CUSTOM_OBJECT_10B8:
    return new CustomObjectScript_10B8;
    break;
  case ID_CUSTOM_OBJECT_0892:
    return new CustomObjectScript_0892;
    break;
  case ID_CUSTOM_OBJECT_0891:
    return new CustomObjectScript_0891;
    break;
  case ID_CUSTOM_OBJECT_0890:
    return new CustomObjectScript_0890;
    break;
  case ID_CUSTOM_OBJECT_08A8:
    return new CustomObjectScript_08A8;
    break;
  case ID_CUSTOM_OBJECT_08A7:
    return new CustomObjectScript_08A7;
    break;
  case ID_CUSTOM_OBJECT_180F:
    return new CustomObjectScript_180F;
    break;
  case ID_CUSTOM_OBJECT_1081:
    return new CustomObjectScript_1081;
    break;
  case ID_CUSTOM_OBJECT_186D:
    return new CustomObjectScript_186D;
    break;
  case ID_CUSTOM_OBJECT_08D3:
    return new CustomObjectScript_08D3;
    break;
  case ID_CUSTOM_OBJECT_188F:
    return new CustomObjectScript_188F;
    break;
  case ID_CUSTOM_OBJECT_0888:
    return new CustomObjectScript_0888;
    break;
  case ID_CUSTOM_OBJECT_204F:
    return new CustomObjectScript_204F;
    break;
  case ID_CUSTOM_OBJECT_2870:
    return new CustomObjectScript_2870;
    break;
  case ID_CUSTOM_OBJECT_1025:
    return new CustomObjectScript_1025;
    break;
  case ID_CUSTOM_OBJECT_08A0:
    return new CustomObjectScript_08A0;
    break;
  case ID_CUSTOM_OBJECT_189E:
    return new CustomObjectScript_189E;
    break;
  case ID_CUSTOM_OBJECT_109B:
    return new CustomObjectScript_109B;
    break;
  case ID_CUSTOM_OBJECT_109D:
    return new CustomObjectScript_109D;
    break;
  case ID_CUSTOM_OBJECT_409A:
    return new CustomObjectScript_409A;
    break;
  case ID_CUSTOM_OBJECT_309C:
    return new CustomObjectScript_309C;
    break;
  case ID_CUSTOM_OBJECT_1083:
    return new CustomObjectScript_1083;
    break;
  case ID_CUSTOM_OBJECT_088A:
    return new CustomObjectScript_088A;
    break;
  case ID_CUSTOM_OBJECT_188B:
    return new CustomObjectScript_188B;
    break;
  case ID_CUSTOM_OBJECT_088C:
    return new CustomObjectScript_088C;
    break;
  case ID_CUSTOM_OBJECT_088D:
    return new CustomObjectScript_088D;
    break;
  case ID_CUSTOM_OBJECT_088E:
    return new CustomObjectScript_088E;
    break;
  case ID_CUSTOM_OBJECT_2880:
    return new CustomObjectScript_2880;
    break;
  case ID_CUSTOM_OBJECT_10C3:
    return new CustomObjectScript_10C3;
    break;
  case ID_CUSTOM_OBJECT_4089:
    return new CustomObjectScript_4089;
    break;
  case ID_CUSTOM_OBJECT_406F:
    return new CustomObjectScript_406F;
    break;
  case ID_CUSTOM_OBJECT_1082:
    return new CustomObjectScript_1082;
    break;
  case ID_CUSTOM_OBJECT_10D5:
    return new CustomObjectScript_10D5;
    break;
  case ID_CUSTOM_OBJECT_10D4:
    return new CustomObjectScript_10D4;
    break;
  case ID_CUSTOM_OBJECT_10D6:
    return new CustomObjectScript_10D6;
    break;
  case ID_CUSTOM_OBJECT_0917:
    return new CustomObjectScript_0917;
    break;
  case ID_CUSTOM_OBJECT_10D7:
    return new CustomObjectScript_10D7;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
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
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
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
  case ID_CUSTOM_OBJECT_10B8:
    delete ((CustomObjectScript_10B8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0892:
    delete ((CustomObjectScript_0892 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0891:
    delete ((CustomObjectScript_0891 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0890:
    delete ((CustomObjectScript_0890 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A8:
    delete ((CustomObjectScript_08A8 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A7:
    delete ((CustomObjectScript_08A7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_180F:
    delete ((CustomObjectScript_180F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1081:
    delete ((CustomObjectScript_1081 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_186D:
    delete ((CustomObjectScript_186D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08D3:
    delete ((CustomObjectScript_08D3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_188F:
    delete ((CustomObjectScript_188F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0888:
    delete ((CustomObjectScript_0888 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_204F:
    delete ((CustomObjectScript_204F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2870:
    delete ((CustomObjectScript_2870 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1025:
    delete ((CustomObjectScript_1025 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_08A0:
    delete ((CustomObjectScript_08A0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_189E:
    delete ((CustomObjectScript_189E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_109B:
    delete ((CustomObjectScript_109B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_109D:
    delete ((CustomObjectScript_109D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_409A:
    delete ((CustomObjectScript_409A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_309C:
    delete ((CustomObjectScript_309C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1083:
    delete ((CustomObjectScript_1083 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_088A:
    delete ((CustomObjectScript_088A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_188B:
    delete ((CustomObjectScript_188B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_088C:
    delete ((CustomObjectScript_088C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_088D:
    delete ((CustomObjectScript_088D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_088E:
    delete ((CustomObjectScript_088E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2880:
    delete ((CustomObjectScript_2880 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10C3:
    delete ((CustomObjectScript_10C3 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_4089:
    delete ((CustomObjectScript_4089 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_406F:
    delete ((CustomObjectScript_406F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1082:
    delete ((CustomObjectScript_1082 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D5:
    delete ((CustomObjectScript_10D5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D4:
    delete ((CustomObjectScript_10D4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D6:
    delete ((CustomObjectScript_10D6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0917:
    delete ((CustomObjectScript_0917 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_10D7:
    delete ((CustomObjectScript_10D7 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
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
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
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
  case ID_CUSTOM_OBJECT_10B8:
  case ID_CUSTOM_OBJECT_0892:
  case ID_CUSTOM_OBJECT_0891:
  case ID_CUSTOM_OBJECT_0890:
  case ID_CUSTOM_OBJECT_08A8:
  case ID_CUSTOM_OBJECT_08A7:
  case ID_CUSTOM_OBJECT_180F:
  case ID_CUSTOM_OBJECT_1081:
  case ID_CUSTOM_OBJECT_186D:
  case ID_CUSTOM_OBJECT_08D3:
  case ID_CUSTOM_OBJECT_188F:
  case ID_CUSTOM_OBJECT_0888:
  case ID_CUSTOM_OBJECT_204F:
  case ID_CUSTOM_OBJECT_2870:
  case ID_CUSTOM_OBJECT_1025:
  case ID_CUSTOM_OBJECT_08A0:
  case ID_CUSTOM_OBJECT_189E:
  case ID_CUSTOM_OBJECT_109B:
  case ID_CUSTOM_OBJECT_109D:
  case ID_CUSTOM_OBJECT_409A:
  case ID_CUSTOM_OBJECT_309C:
  case ID_CUSTOM_OBJECT_1083:
  case ID_CUSTOM_OBJECT_088A:
  case ID_CUSTOM_OBJECT_188B:
  case ID_CUSTOM_OBJECT_088C:
  case ID_CUSTOM_OBJECT_088D:
  case ID_CUSTOM_OBJECT_088E:
  case ID_CUSTOM_OBJECT_2880:
  case ID_CUSTOM_OBJECT_10C3:
  case ID_CUSTOM_OBJECT_4089:
  case ID_CUSTOM_OBJECT_406F:
  case ID_CUSTOM_OBJECT_1082:
  case ID_CUSTOM_OBJECT_10D5:
  case ID_CUSTOM_OBJECT_10D4:
  case ID_CUSTOM_OBJECT_10D6:
  case ID_CUSTOM_OBJECT_0917:
  case ID_CUSTOM_OBJECT_10D7:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0002:
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
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0002;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[37];
  static int cust_id_list[37] = {
      ID_CUSTOM_OBJECT_10B8, ID_CUSTOM_OBJECT_0892, ID_CUSTOM_OBJECT_0891, ID_CUSTOM_OBJECT_0890, ID_CUSTOM_OBJECT_08A8,
      ID_CUSTOM_OBJECT_08A7, ID_CUSTOM_OBJECT_180F, ID_CUSTOM_OBJECT_1081, ID_CUSTOM_OBJECT_186D, ID_CUSTOM_OBJECT_08D3,
      ID_CUSTOM_OBJECT_188F, ID_CUSTOM_OBJECT_0888, ID_CUSTOM_OBJECT_204F, ID_CUSTOM_OBJECT_2870, ID_CUSTOM_OBJECT_1025,
      ID_CUSTOM_OBJECT_08A0, ID_CUSTOM_OBJECT_189E, ID_CUSTOM_OBJECT_109B, ID_CUSTOM_OBJECT_109D, ID_CUSTOM_OBJECT_409A,
      ID_CUSTOM_OBJECT_309C, ID_CUSTOM_OBJECT_1083, ID_CUSTOM_OBJECT_088A, ID_CUSTOM_OBJECT_188B, ID_CUSTOM_OBJECT_088C,
      ID_CUSTOM_OBJECT_088D, ID_CUSTOM_OBJECT_088E, ID_CUSTOM_OBJECT_2880, ID_CUSTOM_OBJECT_10C3, ID_CUSTOM_OBJECT_4089,
      ID_CUSTOM_OBJECT_406F, ID_CUSTOM_OBJECT_1082, ID_CUSTOM_OBJECT_10D5, ID_CUSTOM_OBJECT_10D4, ID_CUSTOM_OBJECT_10D6,
      ID_CUSTOM_OBJECT_0917, ID_CUSTOM_OBJECT_10D7};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[3];
  cust_handle_list[1] = Object_handles[0];
  cust_handle_list[2] = Object_handles[1];
  cust_handle_list[3] = Object_handles[2];
  cust_handle_list[4] = Object_handles[4];
  cust_handle_list[5] = Object_handles[5];
  cust_handle_list[6] = Object_handles[6];
  cust_handle_list[7] = Object_handles[7];
  cust_handle_list[8] = Object_handles[8];
  cust_handle_list[9] = Object_handles[9];
  cust_handle_list[10] = Object_handles[10];
  cust_handle_list[11] = Object_handles[11];
  cust_handle_list[12] = Object_handles[12];
  cust_handle_list[13] = Object_handles[13];
  cust_handle_list[14] = Object_handles[14];
  cust_handle_list[15] = Object_handles[15];
  cust_handle_list[16] = Object_handles[16];
  cust_handle_list[17] = Object_handles[17];
  cust_handle_list[18] = Object_handles[18];
  cust_handle_list[19] = Object_handles[19];
  cust_handle_list[20] = Object_handles[20];
  cust_handle_list[21] = Object_handles[21];
  cust_handle_list[22] = Object_handles[22];
  cust_handle_list[23] = Object_handles[23];
  cust_handle_list[24] = Object_handles[24];
  cust_handle_list[25] = Object_handles[25];
  cust_handle_list[26] = Object_handles[26];
  cust_handle_list[27] = Object_handles[27];
  cust_handle_list[28] = Object_handles[28];
  cust_handle_list[29] = Object_handles[30];
  cust_handle_list[30] = Object_handles[32];
  cust_handle_list[31] = Object_handles[35];
  cust_handle_list[32] = Object_handles[36];
  cust_handle_list[33] = Object_handles[37];
  cust_handle_list[34] = Object_handles[38];
  cust_handle_list[35] = Object_handles[39];
  cust_handle_list[36] = Object_handles[40];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 37;
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

    // Script 067: Update Bypass Connector Display
    if (qUserVarValue(0) != qUserVarValue(12)) {
      aUserVarSet(12, qUserVarValue(0));
      if (qUserVarValue(12) == 0.000000f) {
        aUpdateBypassConnDisplay(Message_strings[1], 0);
      } else {
        aUpdateBypassConnDisplay(Message_strings[2], qUserVarValueInt(12));
      }

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Level Start - Init Flags and Variables
    if (1) {
      aUserVarSet(0, 0.000000f);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(2, 1.000000f);
      aUserVarSet(3, 1.000000f);
      aUserVarSet(4, 1.000000f);
      aUserVarSet(5, 1.000000f);
      aUserVarSet(6, 1.000000f);
      aUserVarSet(7, 1.000000f);
      aUserVarSet(8, 1.000000f);
      aUserVarSet(9, 1.000000f);
      aUserFlagSet(11, 0);
      aUserFlagSet(12, 0);
      aUserFlagSet(13, 0);
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 1);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aUserFlagSet(6, 0);
      aUserFlagSet(7, 0);
      aUserFlagSet(8, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(14, 0);
      aUserFlagSet(15, 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(16, 0);
      aUserFlagSet(17, 0);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 020: Level Start - Misc
    if (1) {
      aObjMakeInvuln(Object_handles[0], -1);
      aObjMakeInvuln(Object_handles[1], -1);
      aObjMakeInvuln(Object_handles[2], -1);
      aSetLevelTimer(0.200000f, 5);
      aMatcenSetState(0, Matcen_indexes[0]);
      aRoomSetFog(Room_indexes[0], 0.500000f, 0.500000f, 0.500000f, 300.000000f);
      aSetLevelTimer(20.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 038: Level Start - Intro Cinematic
    if (1 == true) {
      aCinematicIntro(Path_indexes[0], Message_strings[0], Object_handles[3], Path_indexes[1], 20.000000f);
      aSoundPlaySteaming("VoxLev14StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }

    // Script 049: Level Start - Init Bypass Connector Display
    if (1) {
      aInitBypassConnDisplay();
      aUserVarSet(12, 999.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 048: Music Init
    if (1) {
      aMusicSetRegionAll(2);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 008: Process System Init Sequence
    if (event_data->id == 1) {
      if (ScriptActionCtr_008 == 0) {
        aSetTextureForMonitors(Texture_indexes[0]);
        aSetLevelTimer(3.000000f, 1);
      }
      if (ScriptActionCtr_008 == 1) {
        aSetTextureForMonitors(Texture_indexes[1]);
        aSetLevelTimer(2.000000f, 1);
      }
      if (ScriptActionCtr_008 == 2) {
        aSetTextureForMonitors(Texture_indexes[2]);
        aShowHUDMessage(Message_strings[16]);
        aUserFlagSet(14, 1);
        aGoalCompleted(Goal_indexes[2], 1);
      }

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 009: Process System Upload Sequence
    if (event_data->id == 2) {
      if (ScriptActionCtr_009 == 0) {
        aSetTextureForMonitors(Texture_indexes[3]);
        aSetLevelTimer(2.000000f, 2);
      }
      if (ScriptActionCtr_009 == 1) {
        aSetTextureForMonitors(Texture_indexes[4]);
        aSetLevelTimer(3.000000f, 2);
      }
      if (ScriptActionCtr_009 == 2) {
        aSetTextureForMonitors(Texture_indexes[5]);
        aSetLevelTimer(4.000000f, 2);
      }
      if (ScriptActionCtr_009 == 3) {
        aSetTextureForMonitors(Texture_indexes[6]);
        aSetLevelTimer(5.000000f, 2);
      }
      if (ScriptActionCtr_009 == 4) {
        aSetTextureForMonitors(Texture_indexes[7]);
        aSetLevelTimer(6.000000f, 2);
      }
      if (ScriptActionCtr_009 == 5) {
        aSetTextureForMonitors(Texture_indexes[8]);
        aSetLevelTimer(5.000000f, 2);
      }
      if (ScriptActionCtr_009 == 6) {
        aSetTextureForMonitors(Texture_indexes[9]);
        aSetLevelTimer(5.000000f, 3);
      }

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 010: Process System Omnicron Sequence
    if (event_data->id == 3) {
      aSetTextureForMonitors(Texture_indexes[10]);
      aShowHUDMessage(Message_strings[17]);
      aUserFlagSet(15, 1);
      aGoalCompleted(Goal_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }

    // Script 014: Reset Shield Code Sequence
    if (event_data->id == 0) {
      if (qUserFlag(2) == false) {
        aUserFlagSet(0, 0);
        aUserFlagSet(1, 1);
        aUserVarSet(2, 1.000000f);
        if (qUserFlag(3) == true) {
          aObjPlayAnim(Object_handles[16], 10, 20, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], Object_handles[16], 1.000000f);
          aUserFlagSet(3, 0);
        }
        if (qUserFlag(4) == true) {
          aObjPlayAnim(Object_handles[17], 10, 20, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], Object_handles[17], 1.000000f);
          aUserFlagSet(4, 0);
        }
        if (qUserFlag(5) == true) {
          aObjPlayAnim(Object_handles[18], 10, 20, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], Object_handles[18], 1.000000f);
          aUserFlagSet(5, 0);
        }
        if (qUserFlag(6) == true) {
          aObjPlayAnim(Object_handles[19], 10, 20, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], Object_handles[19], 1.000000f);
          aUserFlagSet(6, 0);
        }
        aShowHUDMessage(Message_strings[23]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 032: Free Shuttle Sequence
    if ((ScriptActionCtr_032 < 1) && (event_data->id == 4)) {
      if (ScriptActionCtr_032 == 0) {
        aRoomSetFaceTexture(Room_indexes[2], 87, Texture_indexes[12]);
        aAIGoalFollowPath(Object_handles[27], Path_indexes[2], 1, 2, 1, 3, 131328, 0);
        aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, -1.000000f, 0.000000f);
        aMiscShakeArea(Object_handles[27], 80.000000f, 200.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 041: Create the Lens-Destroyer Robot
    if (event_data->id == 7) {
      aMatcenSetState(1, Matcen_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }

    // Script 039: Handle Beam Generation (and check power supplies)
    if (event_data->id == 5) {
      aUserVarSet(11, 0.000000f);
      if (((qObjExists(Object_handles[31]) == true) || (qUserFlag(16) == true)) && (qUserFlag(17) == true)) {
        aLightningCreate(Object_handles[33], Object_handles[34], 0.200000f, 1.000000f, 5, Texture_indexes[14],
                         0.500000f, 1, 255, 255, 255, 0);
      }
      if (qObjAnimFrame(Object_handles[21]) == 6.000000f) {
        aLightningCreateGunpoints(0, 1, Object_handles[21], 0.200000f, 10.000000f, 1, Texture_indexes[15], 0.500000f, 1,
                                  0, 255, 255, 0);
        aUserVarInc(11);
      }
      if (qObjAnimFrame(Object_handles[22]) == 6.000000f) {
        aLightningCreateGunpoints(0, 1, Object_handles[22], 0.200000f, 10.000000f, 1, Texture_indexes[15], 0.500000f, 1,
                                  0, 255, 255, 0);
        aUserVarInc(11);
      }
      if (qObjAnimFrame(Object_handles[23]) == 6.000000f) {
        aLightningCreateGunpoints(0, 1, Object_handles[23], 0.200000f, 10.000000f, 1, Texture_indexes[15], 0.500000f, 1,
                                  0, 255, 255, 0);
        aUserVarInc(11);
      }
      if (qObjAnimFrame(Object_handles[24]) == 6.000000f) {
        aLightningCreateGunpoints(0, 1, Object_handles[24], 0.200000f, 10.000000f, 1, Texture_indexes[15], 0.500000f, 1,
                                  0, 255, 255, 0);
        aUserVarInc(11);
      }
      if (qObjAnimFrame(Object_handles[25]) == 6.000000f) {
        aLightningCreateGunpoints(0, 1, Object_handles[25], 0.200000f, 10.000000f, 1, Texture_indexes[15], 0.500000f, 1,
                                  0, 255, 255, 0);
        aUserVarInc(11);
      }
      if (qObjAnimFrame(Object_handles[26]) == 6.000000f) {
        aLightningCreateGunpoints(0, 1, Object_handles[26], 0.200000f, 10.000000f, 1, Texture_indexes[15], 0.500000f, 1,
                                  0, 255, 255, 0);
        aUserVarInc(11);
      }
      aSetLevelTimer(0.200000f, 5);
      if (qUserVarValue(11) == 6.000000f) {
        if (qGoalCompleted(Goal_indexes[6]) == false) {
          aGoalCompleted(Goal_indexes[6], 1);
        }
      } else {
        if ((qGoalCompleted(Goal_indexes[6]) == true) && (qUserFlag(17) == false)) {
          aShowHUDMessage(Message_strings[40]);
          aGoalCompleted(Goal_indexes[6], 0);
        }
      }
      if ((qUserFlag(11) == false) && (qUserFlag(12) == false) && (qUserFlag(13) == false)) {
        if ((qGoalEnabled(Goal_indexes[9]) == true) && (qGoalCompleted(Goal_indexes[9]) == false)) {
          aGoalCompleted(Goal_indexes[9], 1);
        }
      } else {
        if ((qGoalEnabled(Goal_indexes[9]) == true) && (qGoalCompleted(Goal_indexes[9]) == true) &&
            (qUserFlag(17) == false)) {
          aShowHUDMessage(Message_strings[41]);
          aGoalCompleted(Goal_indexes[9], 0);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 040: Transmission Completed
    if (event_data->id == 6) {
      if (qObjExists(Object_handles[31]) == true) {
        aShowHUDMessage(Message_strings[42]);
        aGoalCompleted(Goal_indexes[12], 1);
        aSetLevelTimer(5.000000f, 9);
      }

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 046: New Transmission Completed
    if (event_data->id == 8) {
      aShowHUDMessage(Message_strings[42]);
      aGoalCompleted(Goal_indexes[12], 1);
      aSetLevelTimer(5.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }

    // Script 047: Start End Level Sequence
    if (event_data->id == 9) {
      aGoalCompleted(Goal_indexes[13], 1);
      aStartEndlevelSequencePath(Path_indexes[5], Path_indexes[6], 20.000000f, Message_strings[1]);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 066: Dan's Spewer System
    if (event_data->id == 10) {
      aSoundPlay2D(Sound_indexes[4], 1.000000f);
      aTurnOnSpew(Object_handles[41], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[42], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[43], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[44], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[45], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[46], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[47], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[48], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[49], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[50], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[51], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[52], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[53], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[54], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[55], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[56], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[57], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[58], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[59], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[60], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[61], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aTurnOnSpew(Object_handles[62], -1, 7, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.020000f, 1.250000f, 1.250000f,
                  36.000000f, 1, 0);
      aSetLevelTimer(20.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 043: Robot Reached Lens
    if (event_data->goal_uid == 1) {
      aObjKill(qObjSavedHandle(3), 0, 1, 65760, 0.000000f, 0.000000f);
      aObjDestroy(Object_handles[31]);
      aShowHUDMessage(Message_strings[35]);
      aGoalEnableDisable(1, Goal_indexes[10]);
      aGoalEnableDisable(1, Goal_indexes[11]);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 042: Tell Lens Robot to Destroy Lens
    if (event_data->id == Matcen_indexes[0]) {
      aObjSaveHandle(event_data->it_handle, 3);
      aAIFlags(0, 33554432, event_data->it_handle);
      aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[4], 4352, 1, 3);
      aShowHUDMessage(Message_strings[34]);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10B8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Picked up Anti-Virus Program
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aShowHUDMessageObj(Message_strings[12], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  case EVT_INTERVAL: {
    tOSIRISEVTINTERVAL *event_data = &data->evt_interval;

    // Script 064: Give Closest Player the Anti-Virus Program
    if ((ScriptActionCtr_064 < 1) && (qObjType(qPlayerClosest(data->me_handle, 10)) == 4)) {
      aAddObjectToInventory(data->me_handle, qPlayerClosest(data->me_handle, 10), 0);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 007: Used Anti-Virus Program
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(15) == false)) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[11]) < 25.000000f) {
        if (qUserFlag(14) == true) {
          aShowHUDMessage(Message_strings[13]);
          aSetLevelTimer(0.100000f, 2);
        } else {
          aObjGhostSet(0, data->me_handle);
          aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
          aShowHUDMessage(Message_strings[14]);
        }
      } else {
        if (qObjGetDistance(event_data->it_handle, Object_handles[12]) < 25.000000f) {
          if (qUserFlag(14) == true) {
            aShowHUDMessage(Message_strings[13]);
            aSetLevelTimer(0.100000f, 2);
          } else {
            aObjGhostSet(0, data->me_handle);
            aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            aShowHUDMessage(Message_strings[14]);
          }
        } else {
          if (qObjGetDistance(event_data->it_handle, Object_handles[13]) < 25.000000f) {
            if (qUserFlag(14) == true) {
              aShowHUDMessage(Message_strings[13]);
              aSetLevelTimer(0.100000f, 2);
            } else {
              aObjGhostSet(0, data->me_handle);
              aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
              aShowHUDMessage(Message_strings[14]);
            }
          } else {
            aObjGhostSet(0, data->me_handle);
            aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
            aShowHUDMessageObj(Message_strings[15], event_data->it_handle);
          }
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

int16_t CustomObjectScript_0892::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 029: Power Conduit1 Created
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[0], 0), 0);
      aObjMakeInvuln(qObjSavedHandle(0), -1);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0891::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 030: Power Conduit2 Created
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[1], 0), 1);
      aObjMakeInvuln(qObjSavedHandle(1), -1);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0890::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_CREATED: {
    tOSIRISEVTCREATED *event_data = &data->evt_created;

    // Script 031: Power Conduit3 Created
    if (1) {
      aObjSaveHandle(qGetAtachedChild(Object_handles[2], 0), 2);
      aObjMakeInvuln(qObjSavedHandle(2), -1);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A8::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Toggle Power Switch 1
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(17) == false)) {
      if (qUserFlag(11) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(11, 1);
          aObjGhostSet(1, qObjSavedHandle(0));
          aMatcenGroupASetEnableState(0);
          aShowHUDMessageI(Message_strings[3], 1);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(11, 0);
          aObjGhostSet(0, qObjSavedHandle(0));
          aMatcenGroupASetEnableState(1);
          aShowHUDMessageI(Message_strings[4], 1);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Toggle Power Switch 2
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(17) == false)) {
      if (qUserFlag(12) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(12, 1);
          aObjGhostSet(1, qObjSavedHandle(1));
          aMatcenGroupBSetEnableState(0);
          aShowHUDMessageI(Message_strings[3], 2);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(12, 0);
          aObjGhostSet(0, qObjSavedHandle(1));
          aMatcenGroupBSetEnableState(1);
          aShowHUDMessageI(Message_strings[4], 2);
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

int16_t CustomObjectScript_180F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Toggle Power Switch 3
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(17) == false)) {
      if (qUserFlag(13) == false) {
        if ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(13, 1);
          aObjGhostSet(1, qObjSavedHandle(2));
          aMatcenGroupCSetEnableState(0);
          aShowHUDMessageI(Message_strings[3], 3);
        }
      } else {
        if (qObjAnimFrame(data->me_handle) == 1.000000f) {
          aObjPlayAnim(data->me_handle, 1, 2, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aUserFlagSet(13, 0);
          aObjGhostSet(0, qObjSavedHandle(2));
          aMatcenGroupCSetEnableState(1);
          aShowHUDMessageI(Message_strings[4], 3);
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

int16_t CustomObjectScript_1081::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 002: Player obtains Bypass Connector #1
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      if (qMathAddInt(qUserVarValueInt(0), qUserVarValueInt(1)) >= 3) {
        aShowHUDMessage(Message_strings[5]);
        aGoalCompleted(Goal_indexes[0], 1);
      } else {
        aShowHUDMessage(Message_strings[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_186D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Player obtains Bypass Connector #2
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      if (qMathAddInt(qUserVarValueInt(0), qUserVarValueInt(1)) >= 3) {
        aShowHUDMessage(Message_strings[5]);
        aGoalCompleted(Goal_indexes[0], 1);
      } else {
        aShowHUDMessage(Message_strings[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08D3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Player obtains Bypass Connector #3
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aUserVarInc(0);
      if (qMathAddInt(qUserVarValueInt(0), qUserVarValueInt(1)) >= 3) {
        aShowHUDMessage(Message_strings[5]);
        aGoalCompleted(Goal_indexes[0], 1);
      } else {
        aShowHUDMessage(Message_strings[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_188F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Player picks up Equipment Room key
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aDoorLockUnlock(0, Door_handles[0]);
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aShowHUDMessage(Message_strings[7]);
      aGoalCompleted(Goal_indexes[1], 1);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0888::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Bumped Emitter Room Data Link
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qUserFlag(7) == true) {
        aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
      } else {
        if (qUserVarValue(0) > 0.000000f) {
          aGoalItemCompleted(Goal_indexes[2], 3, 1);
          aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aShowHUDMessageObj(Message_strings[9], event_data->it_handle);
          aUserVarInc(1);
          aUserVarDec(0);
          aUserFlagSet(7, 1);
          if (qUserVarValue(1) == 3.000000f) {
            aShowHUDMessage(Message_strings[10]);
            aSetLevelTimer(0.100000f, 1);
          }
        } else {
          aShowHUDMessageObj(Message_strings[11], event_data->it_handle);
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

int16_t CustomObjectScript_204F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: Bumped West Dock Data Link
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qUserFlag(8) == true) {
        aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
      } else {
        if (qUserVarValue(0) > 0.000000f) {
          aGoalItemCompleted(Goal_indexes[2], 1, 1);
          aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aShowHUDMessageObj(Message_strings[9], event_data->it_handle);
          aUserVarInc(1);
          aUserVarDec(0);
          aUserFlagSet(8, 1);
          if (qUserVarValue(1) == 3.000000f) {
            aShowHUDMessage(Message_strings[10]);
            aSetLevelTimer(0.100000f, 1);
          }
        } else {
          aShowHUDMessageObj(Message_strings[11], event_data->it_handle);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2870::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: Bumped Control Room Data Link
    if (qObjIsPlayer(event_data->it_handle) == true) {
      if (qUserFlag(9) == true) {
        aShowHUDMessageObj(Message_strings[8], event_data->it_handle);
      } else {
        if (qUserVarValue(0) > 0.000000f) {
          aGoalItemCompleted(Goal_indexes[2], 2, 1);
          aObjPlayAnim(data->me_handle, 0, 10, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aShowHUDMessageObj(Message_strings[9], event_data->it_handle);
          aUserVarInc(1);
          aUserVarDec(0);
          aUserFlagSet(9, 1);
          if (qUserVarValue(1) == 3.000000f) {
            aShowHUDMessage(Message_strings[10]);
            aSetLevelTimer(0.100000f, 1);
          }
        } else {
          aShowHUDMessageObj(Message_strings[11], event_data->it_handle);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1025::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: Bumped Dial
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(10) == false)) {
      if ((ScriptActionCtr_010 > 0) == true) {
        if ((qUserVarValueInt(3) == 1) &&
            ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 5.000000f))) {
          aObjPlayAnim(data->me_handle, 0, 1, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aUserVarSet(3, 2.000000f);
        }
        if ((qUserVarValueInt(3) == 2) && (qObjAnimFrame(data->me_handle) == 1.000000f)) {
          aObjPlayAnim(data->me_handle, 1, 2, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aUserVarSet(3, 3.000000f);
        }
        if ((qUserVarValueInt(3) == 3) && (qObjAnimFrame(data->me_handle) == 2.000000f)) {
          aObjPlayAnim(data->me_handle, 2, 3, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aUserVarSet(3, 4.000000f);
        }
        if ((qUserVarValueInt(3) == 4) && (qObjAnimFrame(data->me_handle) == 3.000000f)) {
          aObjPlayAnim(data->me_handle, 3, 4, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aUserVarSet(3, 5.000000f);
        }
        if ((qUserVarValueInt(3) == 5) && (qObjAnimFrame(data->me_handle) == 4.000000f)) {
          aObjPlayAnim(data->me_handle, 4, 5, 3.000000f, 0);
          aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
          aUserVarSet(3, 1.000000f);
        }
      } else {
        aShowHUDMessageObj(Message_strings[18], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_08A0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 012: Dial Switch Hit
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(15) == true) {
        if ((qUserVarValueInt(3) == 4) && (qObjAnimFrame(Object_handles[14]) == 3.000000f) &&
            (qUserFlag(10) == false)) {
          aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
          aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
          aShowHUDMessage(Message_strings[19]);
          aSetTextureForMonitors(Texture_indexes[11]);
          aUserFlagSet(10, 1);
          aGoalCompleted(Goal_indexes[4], 1);
        } else {
          aShowHUDMessageObj(Message_strings[20], event_data->it_handle);
        }
      } else {
        aShowHUDMessageObj(Message_strings[21], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_189E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: Shield Toggle Switch #1 Hit
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if ((qUserFlag(2) == false) && (qUserFlag(3) == false) &&
          ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 20.000000f))) {
        if (qUserFlag(0) == 0) {
          aUserFlagSet(0, 1);
          aShowHUDMessage(Message_strings[22]);
          aSetLevelTimer(15.000000f, 0);
        }
        aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserFlagSet(3, 1);
        if (qUserVarValue(2) != 1.000000f) {
          aUserFlagSet(1, 0);
        }
        aUserVarInc(2);
      }

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_109B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: Shield Toggle Switch #2 Hit
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if ((qUserFlag(2) == false) && (qUserFlag(4) == false) &&
          ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 20.000000f))) {
        if (qUserFlag(0) == 0) {
          aUserFlagSet(0, 1);
          aShowHUDMessage(Message_strings[22]);
          aSetLevelTimer(15.000000f, 0);
        }
        aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserFlagSet(4, 1);
        if (qUserVarValue(2) != 2.000000f) {
          aUserFlagSet(1, 0);
        }
        aUserVarInc(2);
      }

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_109D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Shield Toggle Switch #3 Hit
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if ((qUserFlag(2) == false) && (qUserFlag(5) == false) &&
          ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 20.000000f))) {
        if (qUserFlag(0) == 0) {
          aUserFlagSet(0, 1);
          aShowHUDMessage(Message_strings[22]);
          aSetLevelTimer(15.000000f, 0);
        }
        aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserFlagSet(5, 1);
        if (qUserVarValue(2) != 3.000000f) {
          aUserFlagSet(1, 0);
        }
        aUserVarInc(2);
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_409A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 018: Shield Toggle Switch #4 Hit
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      if ((qUserFlag(2) == false) && (qUserFlag(6) == false) &&
          ((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 20.000000f))) {
        if (qUserFlag(0) == 0) {
          aUserFlagSet(0, 1);
          aShowHUDMessage(Message_strings[22]);
          aSetLevelTimer(15.000000f, 0);
        }
        aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserFlagSet(6, 1);
        if (qUserVarValue(2) != 4.000000f) {
          aUserFlagSet(1, 0);
        }
        aUserVarInc(2);
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_309C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Shield Code Completion Switch Hit
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(2) == false)) {
      if ((qUserFlag(1) == true) && (qUserVarValue(2) == 5.000000f)) {
        aPortalRenderSet(0, 19, Room_indexes[1], 1);
        aObjPlayAnim(data->me_handle, 0, 4, 3.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserFlagSet(2, 1);
        aUserFlagSet(0, 0);
        aShowHUDMessage(Message_strings[24]);
        aGoalCompleted(Goal_indexes[5], 1);
      } else {
        aShowHUDMessageObj(Message_strings[25], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1083::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Mirror Node #1 Hit
    if (qUserFlag(17) == false) {
      if (((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 12.000000f)) &&
          (qUserVarValue(4) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(4, 2.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 2.000000f) && (qUserVarValue(4) == 2.000000f)) {
        aObjPlayAnim(data->me_handle, 2, 4, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(4, 3.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 4.000000f) && (qUserVarValue(4) == 3.000000f)) {
        aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(4, 4.000000f);
        aGoalItemCompleted(Goal_indexes[6], 1, 1);
      }
      if ((qObjAnimFrame(data->me_handle) == 6.000000f) && (qUserVarValue(4) == 4.000000f)) {
        aObjPlayAnim(data->me_handle, 6, 8, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(4, 5.000000f);
        aGoalItemCompleted(Goal_indexes[6], 1, 0);
      }
      if ((qObjAnimFrame(data->me_handle) == 8.000000f) && (qUserVarValue(4) == 5.000000f)) {
        aObjPlayAnim(data->me_handle, 8, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(4, 6.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 10.000000f) && (qUserVarValue(4) == 6.000000f)) {
        aObjPlayAnim(data->me_handle, 10, 12, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(4, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_088A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Mirror Node #2 Hit
    if (qUserFlag(17) == false) {
      if (((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 12.000000f)) &&
          (qUserVarValue(5) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(5, 2.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 2.000000f) && (qUserVarValue(5) == 2.000000f)) {
        aObjPlayAnim(data->me_handle, 2, 4, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(5, 3.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 4.000000f) && (qUserVarValue(5) == 3.000000f)) {
        aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(5, 4.000000f);
        aGoalItemCompleted(Goal_indexes[6], 2, 1);
      }
      if ((qObjAnimFrame(data->me_handle) == 6.000000f) && (qUserVarValue(5) == 4.000000f)) {
        aObjPlayAnim(data->me_handle, 6, 8, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(5, 5.000000f);
        aGoalItemCompleted(Goal_indexes[6], 2, 0);
      }
      if ((qObjAnimFrame(data->me_handle) == 8.000000f) && (qUserVarValue(5) == 5.000000f)) {
        aObjPlayAnim(data->me_handle, 8, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(5, 6.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 10.000000f) && (qUserVarValue(5) == 6.000000f)) {
        aObjPlayAnim(data->me_handle, 10, 12, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(5, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_188B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Mirror Node #3 Hit
    if (qUserFlag(17) == false) {
      if (((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 12.000000f)) &&
          (qUserVarValue(6) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(6, 2.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 2.000000f) && (qUserVarValue(6) == 2.000000f)) {
        aObjPlayAnim(data->me_handle, 2, 4, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(6, 3.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 4.000000f) && (qUserVarValue(6) == 3.000000f)) {
        aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(6, 4.000000f);
        aGoalItemCompleted(Goal_indexes[6], 3, 1);
      }
      if ((qObjAnimFrame(data->me_handle) == 6.000000f) && (qUserVarValue(6) == 4.000000f)) {
        aObjPlayAnim(data->me_handle, 6, 8, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(6, 5.000000f);
        aGoalItemCompleted(Goal_indexes[6], 3, 0);
      }
      if ((qObjAnimFrame(data->me_handle) == 8.000000f) && (qUserVarValue(6) == 5.000000f)) {
        aObjPlayAnim(data->me_handle, 8, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(6, 6.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 10.000000f) && (qUserVarValue(6) == 6.000000f)) {
        aObjPlayAnim(data->me_handle, 10, 12, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(6, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_088C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Mirror Node #4 Hit
    if (qUserFlag(17) == false) {
      if (((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 12.000000f)) &&
          (qUserVarValue(7) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(7, 2.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 2.000000f) && (qUserVarValue(7) == 2.000000f)) {
        aObjPlayAnim(data->me_handle, 2, 4, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(7, 3.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 4.000000f) && (qUserVarValue(7) == 3.000000f)) {
        aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(7, 4.000000f);
        aGoalItemCompleted(Goal_indexes[6], 4, 1);
      }
      if ((qObjAnimFrame(data->me_handle) == 6.000000f) && (qUserVarValue(7) == 4.000000f)) {
        aObjPlayAnim(data->me_handle, 6, 8, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(7, 5.000000f);
        aGoalItemCompleted(Goal_indexes[6], 4, 0);
      }
      if ((qObjAnimFrame(data->me_handle) == 8.000000f) && (qUserVarValue(7) == 5.000000f)) {
        aObjPlayAnim(data->me_handle, 8, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(7, 6.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 10.000000f) && (qUserVarValue(7) == 6.000000f)) {
        aObjPlayAnim(data->me_handle, 10, 12, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(7, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_088D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Mirror Node #5 Hit
    if (qUserFlag(17) == false) {
      if (((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 12.000000f)) &&
          (qUserVarValue(8) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(8, 2.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 2.000000f) && (qUserVarValue(8) == 2.000000f)) {
        aObjPlayAnim(data->me_handle, 2, 4, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(8, 3.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 4.000000f) && (qUserVarValue(8) == 3.000000f)) {
        aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(8, 4.000000f);
        aGoalItemCompleted(Goal_indexes[6], 5, 1);
      }
      if ((qObjAnimFrame(data->me_handle) == 6.000000f) && (qUserVarValue(8) == 4.000000f)) {
        aObjPlayAnim(data->me_handle, 6, 8, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(8, 5.000000f);
        aGoalItemCompleted(Goal_indexes[6], 5, 0);
      }
      if ((qObjAnimFrame(data->me_handle) == 8.000000f) && (qUserVarValue(8) == 5.000000f)) {
        aObjPlayAnim(data->me_handle, 8, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(8, 6.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 10.000000f) && (qUserVarValue(8) == 6.000000f)) {
        aObjPlayAnim(data->me_handle, 10, 12, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(8, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_088E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Mirror Node #6 Hit
    if (qUserFlag(17) == false) {
      if (((qObjAnimFrame(data->me_handle) == 0.000000f) || (qObjAnimFrame(data->me_handle) == 12.000000f)) &&
          (qUserVarValue(9) == 1.000000f)) {
        aObjPlayAnim(data->me_handle, 0, 2, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(9, 2.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 2.000000f) && (qUserVarValue(9) == 2.000000f)) {
        aObjPlayAnim(data->me_handle, 2, 4, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(9, 3.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 4.000000f) && (qUserVarValue(9) == 3.000000f)) {
        aObjPlayAnim(data->me_handle, 4, 6, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(9, 4.000000f);
        aGoalItemCompleted(Goal_indexes[6], 6, 1);
      }
      if ((qObjAnimFrame(data->me_handle) == 6.000000f) && (qUserVarValue(9) == 4.000000f)) {
        aObjPlayAnim(data->me_handle, 6, 8, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(9, 5.000000f);
        aGoalItemCompleted(Goal_indexes[6], 6, 0);
      }
      if ((qObjAnimFrame(data->me_handle) == 8.000000f) && (qUserVarValue(9) == 5.000000f)) {
        aObjPlayAnim(data->me_handle, 8, 10, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(9, 6.000000f);
      }
      if ((qObjAnimFrame(data->me_handle) == 10.000000f) && (qUserVarValue(9) == 6.000000f)) {
        aObjPlayAnim(data->me_handle, 10, 12, 2.000000f, 0);
        aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
        aUserVarSet(9, 1.000000f);
      }

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2880::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_GOALCOMPLETE: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_goalcomplete;

    // Script 034: Start Escape Shuttle on Path B
    if (event_data->goal_uid == 0) {
      aRoomSetFaceTexture(Room_indexes[2], 87, Texture_indexes[13]);
      aTurnOnSpew(Object_handles[27], 0, 0, 0.000000f, 0.000000f, 65536, 0, 0.500000f, 0.050000f, 25.000000f, 8.000000f,
                  100.000000f, 1, -1);
      aRoomSetWind(Room_indexes[2], 0.000000f, 0.000000f, -1.000000f, 0.000000f);
      aAIGoalFollowPath(Object_handles[27], Path_indexes[3], 1, 4, 1, 3, 131332, 2);
      aAISetMaxSpeed(Object_handles[27], 100.000000f);
      aShowHUDMessage(Message_strings[26]);
      aMiscShakeArea(Object_handles[27], 100.000000f, 500.000000f);
      aGoalCompleted(Goal_indexes[7], 1);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 065: Remove Escape Shuttle
    if (event_data->goal_uid == 2) {
      aObjDelete(data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10C3::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Start the Shuttle Sequence
    if ((ScriptActionCtr_033 < 1) && (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true)) {
      aObjPlayAnim(data->me_handle, 0, 10, 2.000000f, 0);
      aSoundPlayObject(Sound_indexes[0], data->me_handle, 1.000000f);
      aSetLevelTimer(3.000000f, 4);
      aObjPlayAnim(Object_handles[29], 0, 5, 3.000000f, 0);
      aSoundPlayObject(Sound_indexes[2], Object_handles[29], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_4089::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 035: Beam Ignition Panel Bumped
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(17) == false)) {
      if (qUserFlag(14) == true) {
        if (qUserFlag(15) == true) {
          if ((qUserFlag(11) == false) && (qUserFlag(12) == false) && (qUserFlag(13) == false)) {
            if (qUserFlag(10) == true) {
              if (qUserFlag(2) == true) {
                if ((qObjAnimFrame(Object_handles[21]) == 6.000000f) &&
                    (qObjAnimFrame(Object_handles[22]) == 6.000000f) &&
                    (qObjAnimFrame(Object_handles[23]) == 6.000000f) &&
                    (qObjAnimFrame(Object_handles[24]) == 6.000000f) &&
                    (qObjAnimFrame(Object_handles[25]) == 6.000000f) &&
                    (qObjAnimFrame(Object_handles[26]) == 6.000000f)) {
                  aObjPlayAnim(data->me_handle, 0, 1, 2.000000f, 0);
                  aSoundPlayObject(Sound_indexes[3], data->me_handle, 1.000000f);
                  aGoalCompleted(Goal_indexes[8], 1);
                  aSetLevelTimer(60.000000f, 6);
                  aSetLevelTimer(10.000000f, 7);
                  aShowHUDMessage(Message_strings[27]);
                  aUserFlagSet(17, 1);
                } else {
                  aShowHUDMessage(Message_strings[28]);
                }
              } else {
                aShowHUDMessage(Message_strings[29]);
              }
            } else {
              aShowHUDMessage(Message_strings[30]);
            }
          } else {
            aShowHUDMessage(Message_strings[31]);
            aGoalCompleted(Goal_indexes[9], 0);
            aGoalEnableDisable(1, Goal_indexes[9]);
          }
        } else {
          aShowHUDMessage(Message_strings[32]);
        }
      } else {
        aShowHUDMessage(Message_strings[33]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_406F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Picked up Spare Emitter Lens
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(16) == false)) {
      aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aShowHUDMessageObj(Message_strings[36], event_data->it_handle);
      aGoalCompleted(Goal_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 045: Used Spare Emitter Lens Program
    if ((qObjIsPlayer(event_data->it_handle) == true) && (qUserFlag(16) == false)) {
      if (qObjGetDistance(event_data->it_handle, Object_handles[33]) < 40.000000f) {
        if (qObjExists(Object_handles[31]) == false) {
          aStoreObjectInPositionClipboard(Object_handles[33]);
          aMoveObjectToPositionClipboard(data->me_handle);
          aObjGhostSet(0, data->me_handle);
          aSetLevelTimer(15.000000f, 8);
          aShowHUDMessage(Message_strings[37]);
          aUserFlagSet(16, 1);
          aGoalCompleted(Goal_indexes[11], 1);
        } else {
          aObjGhostSet(0, data->me_handle);
          aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
          aShowHUDMessageObj(Message_strings[38], event_data->it_handle);
        }
      } else {
        aObjGhostSet(0, data->me_handle);
        aAddObjectToInventory(data->me_handle, event_data->it_handle, 0);
        aShowHUDMessageObj(Message_strings[39], event_data->it_handle);
      }

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1082::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Picked up Beam Journal
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[43], Message_strings[44]);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Picked up Shield Journal
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[45], Message_strings[46]);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Picked up Virus Journal
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[47], Message_strings[48]);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Picked up Power Journal
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[49], Message_strings[50]);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0917::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Picked up Robot Journal
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[51], Message_strings[52]);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10D7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Picked up Dial Journal
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(data->me_handle);
      aSoundPlayObject(Sound_indexes[1], event_data->it_handle, 1.000000f);
      aAddGameMessage(Message_strings[53], Message_strings[54]);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Play General Streaming Audio Sample
    if ((ScriptActionCtr_068 < 1) && (qObjIsPlayer(event_data->it_handle) == true)) {
      aSoundPlaySteaming("VoxLev14GeneralA.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Music Wing-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Music Top-1
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

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Music Bottom-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Music Bottom-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

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

    // Script 053: Music Middle-4
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

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

    // Script 052: Music Middle-3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

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

    // Script 051: Music Middle-2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: Music Middle-1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
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
NEXT_ID		69

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:NumBypassConnectors
1:NumDatalinksBypassed
2:CodeSeqPos
3:OutputDialPosition
4:MirrorNode1Pos
5:MirrorNode2Pos
6:MirrorNode3Pos
7:MirrorNode4Pos
8:MirrorNode5Pos
9:MirrorNode6Pos
10:TempValue
11:NumNodesAligned
12:NumBypassConnDisplayed
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:CodeSeqActive
1:CodeSeqCorrect
2:CodeSeqCompleted
3:ShieldSW1Down
4:ShieldSW2Down
5:ShieldSW3Down
6:ShieldSW4Down
7:EmitterRoomLinkActive
8:WestDockLinkActive
9:ControlRoomLinkActive
10:DialCodeEntered
11:PowerSwitch1Down
12:PowerSwitch2Down
13:PowerSwitch3Down
14:SystemStarted
15:AntiVirusUploaded
16:NewLensPlaced
17:BeamIgnited
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:Breathers
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:CodeSeqReset
1:ProcessSysInitSeq
2:ProcessSysUploadSeq
3:ProcessSysOmnicronSeq
4:StartShuttleSeq
5:GenerateBeam
6:TransmissionComplete
7:CreateLensRobot
8:NewTransmissionComplete
9:StartEndLevelSeq
10:StartSpewers
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:Power1
1:Power2
2:Power3
3:LensRobot
4:ClosestPlayer
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:ShuttleFinishedPathA
1:LensRobotDone
2:ShuttleDone
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
EquipRm Door
$$DOOR_LIST_END

$$OBJECT_LIST_START
Power Conduit1
Power Conduit2
Power Conduit3
AntiVirus Program
Power SW1
Power SW2
Power SW3
Bypass Conn1
Bypass Conn2
Bypass Conn3
Equip Door Key
Emitter Rm Link
West Dock Link
Control Rm Link
Emitter Output Dia
Override Switch
Shield Tog1
Shield Tog2
Shield Tog3
Shield Tog4
Shielding Bump SW
Node1
Node2
Node3
Node4
Node5
Node6
Escape Shuttle
ShuttleSwitch
ShuttleReleaseClaw
Emitter Igniter
Destroyable Lens
Spare Emitter Lens
Lens Position
EmitterBeamDest
Beam Journal
Shield Journal
Virus Journal
Power Journal
Robot Journal
Dial Journal
Spew1
Spewer2
Spewer3
Spewer4
Spewer6
Spewer7
Spewer8
Spew9
Spew11
Spew12
Spew13
Spew14
Spew15
Spew16
Spew19
Spew20
Spew22
Spew23
Spew24
Spew25
Spew26
Spew27
$$OBJECT_LIST_END

$$ROOM_LIST_START
Terrarium Room
Beam Emitter Rm
Shuttle Bay
$$ROOM_LIST_END

$$TRIGGER_LIST_START
AudioStream3
MWing-1
MTop-1
MBottom-2
MBottom-1
MMiddle-4
MMiddle-3
MMiddle-2
MMiddle-1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbSwitch31
Powerup pickup
AmbSwitch11
AmbSwitch21
AmbExplosionFarC
$$SOUND_LIST_END

$$TEXTURE_LIST_START
DataLogon
DataScroll
CEDSignSilverLogo
CEDUploadAnti
NanoStat
Nano1
Nano2
Nano3
Nano4
CEDUpSucOn
C-SS Omnicron
Ed
Korea_Matcen_Shield
CED-Forcefield
Lightning3
ThickLineLightning
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
IntroCamPath
IntroPlayerPath
EscapeShuttlePathA
EscapeShuttlePathB
LensRobotPath
EndCamPath
EndPlayerPath
$$PATH_LIST_END

$$MATCEN_LIST_START
Emitter Rm Matcen2
$$MATCEN_LIST_END

$$GOAL_LIST_START
Find Three Bypass Connectors
Find Equipment Room Key
Start Transmitter Control System
Upload Anti-Virus Program
Enable Defense Network Output
Deactivate Beam Emitter Shield
Align Mirror Nodes
Free Escape Shuttle
Ignite Beam Emitter
Supply Power to Beam Igniter
Find Spare Emitter Lens
Replace Emitter Lens
Ensure Success of Transmission
Broadcast the Anti-Virus Program
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxLev14StartLevel.osf
VoxLev14GeneralA.osf
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
                        10:10:0:2:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:3:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:4:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:5:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserVar
                        10:6:1.000000:value
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserVar
                        10:6:1.000000:value
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
                        10:10:0:0:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserFlag
                        10:5:1:True/False
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
                        10:10:0:10:UserFlag
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Level Start - Misc
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:-1:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:-1:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:-1:Time
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.200000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aRoomSetFog
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:6:0.500000:Red
                        10:6:0.500000:Green
                        10:6:0.500000:Blue
                        10:6:300.000000:Depth
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Level Start - Intro Cinematic
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
                        10:1:0:3:TotallyNotUsedTarget
                        10:16:1:PlayerPath
                        10:6:20.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Level Start - Init Bypass Connector Display
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aInitBypassConnDisplay
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserVar
                        10:6:999.000000:value
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Update Bypass Connector Display
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        07:1:1
                        06:qUserVarValue:Float
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserVar
                        06:qUserVarValue:value
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUpdateBypassConnDisplay
                                $$CHILD_BLOCK_START
                                10:8:Empty:Message
                                10:4:0:Number
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aUpdateBypassConnDisplay
                                $$CHILD_BLOCK_START
                                10:8:BypassConnDisplay:Message
                                06:qUserVarValueInt:Number
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Give Closest Player the Anti-Virus Program
        $$CHILD_BLOCK_START
        01:1:3
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
                                        10:10:0:10:UserVar
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        07:1:0
                        10:10:0:4:ObjectType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:10:0:10:UserVar
                                $$CHILD_BLOCK_END
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Play General Streaming Audio Sample
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Power Conduit1 Created
        $$CHILD_BLOCK_START
        01:1:0
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
                                10:1:0:0:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:0:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:0:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:-1:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Power Conduit2 Created
        $$CHILD_BLOCK_START
        01:1:1
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
                                10:1:0:1:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:1:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:1:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:-1:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Power Conduit3 Created
        $$CHILD_BLOCK_START
        01:1:2
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
                                10:1:0:2:Object
                                10:4:0:AttachPoint
                                $$CHILD_BLOCK_END
                        10:10:0:2:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:2:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:4:-1:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Toggle Power Switch 1
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Ghost/Unghost
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMatcenGroupASetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageI
                                        $$CHILD_BLOCK_START
                                        10:8:PowerOffline:Message
                                        10:4:1:Integer
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:11:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMatcenGroupASetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageI
                                        $$CHILD_BLOCK_START
                                        10:8:PowerOnline:Message
                                        10:4:1:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Toggle Power Switch 2
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Ghost/Unghost
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMatcenGroupBSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageI
                                        $$CHILD_BLOCK_START
                                        10:8:PowerOffline:Message
                                        10:4:2:Integer
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMatcenGroupBSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageI
                                        $$CHILD_BLOCK_START
                                        10:8:PowerOnline:Message
                                        10:4:2:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Toggle Power Switch 3
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Ghost/Unghost
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMatcenGroupCSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Enable/Disable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageI
                                        $$CHILD_BLOCK_START
                                        10:8:PowerOffline:Message
                                        10:4:3:Integer
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:13:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        06:qObjSavedHandle:Object
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:SavedObjectSlot
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                08:aMatcenGroupCSetEnableState
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:Enable/Disable
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessageI
                                        $$CHILD_BLOCK_START
                                        10:8:PowerOnline:Message
                                        10:4:3:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Player obtains Bypass Connector #1
        $$CHILD_BLOCK_START
        01:1:7
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
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qMathAddInt:Integer
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer1
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qUserVarValueInt:Integer2
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundAllBypassConns:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundBypassConn:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Player obtains Bypass Connector #2
        $$CHILD_BLOCK_START
        01:1:8
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
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qMathAddInt:Integer
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer1
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qUserVarValueInt:Integer2
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundAllBypassConns:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundBypassConn:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Player obtains Bypass Connector #3
        $$CHILD_BLOCK_START
        01:1:9
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
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:0:UserVar
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qMathAddInt:Integer
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer1
                                                $$CHILD_BLOCK_START
                                                10:10:0:0:UserVar
                                                $$CHILD_BLOCK_END
                                        06:qUserVarValueInt:Integer2
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:UserVar
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundAllBypassConns:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:0:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:FoundBypassConn:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Player picks up Equipment Room key
        $$CHILD_BLOCK_START
        01:1:10
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
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FoundEquipRmKey:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Bumped Emitter Room Data Link
        $$CHILD_BLOCK_START
        01:1:11
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
                                        10:10:0:7:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:DataLinkAlreadyActive:Message
                                10:1:1:-1:PlayerObject
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
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalItemCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
                                        10:4:3:ItemIndex
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
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
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DataLinkFixed:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserVarDec
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserFlag
                                        10:5:1:True/False
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
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:SystemStarting:Message
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.100000:Time
                                                10:10:0:1:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DataLinkError:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Bumped West Dock Data Link
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:DataLinkAlreadyActive:Message
                                10:1:1:-1:PlayerObject
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
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalItemCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
                                        10:4:1:ItemIndex
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
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
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DataLinkFixed:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserVarDec
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserFlag
                                        10:5:1:True/False
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
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:SystemStarting:Message
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.100000:Time
                                                10:10:0:1:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DataLinkError:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Bumped Control Room Data Link
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:DataLinkAlreadyActive:Message
                                10:1:1:-1:PlayerObject
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
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalItemCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
                                        10:4:2:ItemIndex
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
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
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DataLinkFixed:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                08:aUserVarInc
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserVarDec
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserVar
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:9:UserFlag
                                        10:5:1:True/False
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
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:SystemStarting:Message
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.100000:Time
                                                10:10:0:1:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DataLinkError:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Picked up Anti-Virus Program
        $$CHILD_BLOCK_START
        01:1:3
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
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:GotCoreMaterial:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Used Anti-Virus Program
        $$CHILD_BLOCK_START
        01:1:3
        02:25
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
                                        10:10:0:15:UserFlag
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
                                06:qObjGetDistance:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object1
                                        10:1:0:11:Object2
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:25.000000:Literal
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
                                                10:10:0:14:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:UploadStarted:Message
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:0.100000:Time
                                        10:10:0:2:TimerID
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
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
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:UploadError:Message
                                        $$CHILD_BLOCK_END
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
                                                10:1:1:-1:Object1
                                                10:1:0:12:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:25.000000:Literal
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
                                                        10:10:0:14:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:UploadStarted:Message
                                                $$CHILD_BLOCK_END
                                        08:aSetLevelTimer
                                                $$CHILD_BLOCK_START
                                                10:6:0.100000:Time
                                                10:10:0:2:TimerID
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
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
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:UploadError:Message
                                                $$CHILD_BLOCK_END
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
                                                        10:1:1:-1:Object1
                                                        10:1:0:13:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:25.000000:Literal
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
                                                                10:10:0:14:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:6
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:UploadStarted:Message
                                                        $$CHILD_BLOCK_END
                                                08:aSetLevelTimer
                                                        $$CHILD_BLOCK_START
                                                        10:6:0.100000:Time
                                                        10:10:0:2:TimerID
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
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
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:UploadError:Message
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
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
                                        08:aShowHUDMessageObj
                                                $$CHILD_BLOCK_START
                                                10:8:UseCoreMaterialFailed:Message
                                                10:1:1:-1:PlayerObject
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Process System Init Sequence
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:8:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:0:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:8:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:1:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:8:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:2:Texture
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:SystemStarted:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:Process System Upload Sequence
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
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:3:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:4:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:3.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:2:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:5:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:4.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:6:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:4:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:7:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:6.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:5:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:8:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:2:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:9:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:6:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetTextureForMonitors
                                $$CHILD_BLOCK_START
                                10:14:9:Texture
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Process System Omnicron Sequence
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
                08:aSetTextureForMonitors
                        $$CHILD_BLOCK_START
                        10:14:10:Texture
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:OmnicronDisplayed:Message
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:15:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:Bumped Dial
        $$CHILD_BLOCK_START
        01:1:14
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
                                        10:10:0:10:UserFlag
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
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:10:ScriptID
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
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:1:Integer
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
                                                        10:6:5.000000:Literal
                                                        $$CHILD_BLOCK_END
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
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        10:6:2.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:2:Integer
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:1:StartFrame
                                        10:4:2:EndFrame
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        10:6:3.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:3:Integer
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
                                        10:4:2:StartFrame
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
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        10:6:4.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:4:Integer
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:2:-1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:3.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:3:StartFrame
                                        10:4:4:EndFrame
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        10:6:5.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:5:Integer
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:2:-1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:4.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:4:4:StartFrame
                                        10:4:5:EndFrame
                                        10:6:3.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:2:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserVarSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserVar
                                        10:6:1.000000:value
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:BumpDialError:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Dial Switch Hit
        $$CHILD_BLOCK_START
        01:1:15
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
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:3:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:4:Integer
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjAnimFrame:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:14:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:6:3.000000:Literal
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
                        04:1:0:0
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
                                        10:12:0:Sound
                                        10:1:2:-1:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:DialCodeEntered:Message
                                        $$CHILD_BLOCK_END
                                08:aSetTextureForMonitors
                                        $$CHILD_BLOCK_START
                                        10:14:11:Texture
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:10:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:4:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:DialCodeIncorrect:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:DialSwitchError:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Shield Toggle Switch #1 Hit
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
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:3:UserFlag
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ShieldCodeSeqStart:Message
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:15.000000:Time
                                        10:10:0:0:TimerID
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
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:3:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:1
                                        10:6:1.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Shield Toggle Switch #2 Hit
        $$CHILD_BLOCK_START
        01:1:17
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
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserFlag
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ShieldCodeSeqStart:Message
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:15.000000:Time
                                        10:10:0:0:TimerID
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
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:1
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Shield Toggle Switch #3 Hit
        $$CHILD_BLOCK_START
        01:1:18
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
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserFlag
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ShieldCodeSeqStart:Message
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:15.000000:Time
                                        10:10:0:0:TimerID
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
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:1
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Shield Toggle Switch #4 Hit
        $$CHILD_BLOCK_START
        01:1:19
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
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserFlag
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
                04:1:0:0
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:ShieldCodeSeqStart:Message
                                        $$CHILD_BLOCK_END
                                08:aSetLevelTimer
                                        $$CHILD_BLOCK_START
                                        10:6:15.000000:Time
                                        10:10:0:0:TimerID
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
                                10:12:0:Sound
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
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:1
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Reset Shield Code Sequence
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
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:2:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
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
                                        10:1:0:16:Object
                                        10:4:10:StartFrame
                                        10:4:20:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:0:Sound
                                        10:1:0:16:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:3:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
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
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:0:17:Object
                                        10:4:10:StartFrame
                                        10:4:20:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:0:Sound
                                        10:1:0:17:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:4:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
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
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:0:18:Object
                                        10:4:10:StartFrame
                                        10:4:20:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:0:Sound
                                        10:1:0:18:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:5:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
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
                                08:aObjPlayAnim
                                        $$CHILD_BLOCK_START
                                        10:1:0:19:Object
                                        10:4:10:StartFrame
                                        10:4:20:EndFrame
                                        10:6:2.000000:CycleTime
                                        10:5:0:Looping
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:0:Sound
                                        10:1:0:19:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:6:UserFlag
                                        10:5:0:True/False
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ShieldCodeSeqReset:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Shield Code Completion Switch Hit
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
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:2:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aPortalRenderSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Enable/Disable
                                10:4:19:PortalNum
                                10:2:1:Room
                                10:5:1:DoublesidedFlag
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:0:StartFrame
                                10:4:4:EndFrame
                                10:6:3.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:2:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:0:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:ShieldDeactivated:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:5:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:ShieldCodeIncorrect:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Mirror Node #1 Hit
        $$CHILD_BLOCK_START
        01:1:21
        02:0
        03:0
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
                                                10:6:12.000000:Literal
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
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
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
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:2:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:4:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:4.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:1:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:6:StartFrame
                                10:4:8:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:5.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:1:ItemIndex
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:8.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:8:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:6.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:4:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:10:StartFrame
                                10:4:12:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:4:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Mirror Node #2 Hit
        $$CHILD_BLOCK_START
        01:1:22
        02:0
        03:0
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
                                                10:6:12.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                        $$CHILD_BLOCK_END
                04:1:0:0
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
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
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:2:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
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
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:4:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:4.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:2:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:6:StartFrame
                                10:4:8:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:5.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:2:ItemIndex
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:8.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:8:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:6.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:5:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:10:StartFrame
                                10:4:12:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:5:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Mirror Node #3 Hit
        $$CHILD_BLOCK_START
        01:1:23
        02:0
        03:0
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
                                                10:6:12.000000:Literal
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
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
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
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:2:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:4:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:4.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:3:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:6:StartFrame
                                10:4:8:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:5.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:3:ItemIndex
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:8.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:8:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:6.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:10:StartFrame
                                10:4:12:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Mirror Node #4 Hit
        $$CHILD_BLOCK_START
        01:1:24
        02:0
        03:0
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
                                                10:6:12.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
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
                        $$CHILD_BLOCK_END
                04:1:0:0
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
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
                                10:4:2:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:4:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:4.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:4:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:6:StartFrame
                                10:4:8:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:5.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:4:ItemIndex
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:8.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:8:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:6.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:10:StartFrame
                                10:4:12:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Mirror Node #5 Hit
        $$CHILD_BLOCK_START
        01:1:25
        02:0
        03:0
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
                                                10:6:12.000000:Literal
                                                $$CHILD_BLOCK_END
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
                04:1:0:0
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
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
                                10:4:2:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:4:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:4.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:5:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:6:StartFrame
                                10:4:8:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:5.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:5:ItemIndex
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:8.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:8:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:6.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:10:StartFrame
                                10:4:12:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Mirror Node #6 Hit
        $$CHILD_BLOCK_START
        01:1:26
        02:0
        03:0
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
                                                10:6:12.000000:Literal
                                                $$CHILD_BLOCK_END
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
                04:1:0:0
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
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserVar
                                10:6:2.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:2.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
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
                                10:4:2:StartFrame
                                10:4:4:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserVar
                                10:6:3.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:3.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:4:StartFrame
                                10:4:6:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserVar
                                10:6:4.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:6:ItemIndex
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:4.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:6:StartFrame
                                10:4:8:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserVar
                                10:6:5.000000:value
                                $$CHILD_BLOCK_END
                        08:aGoalItemCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:6:LevelGoal
                                10:4:6:ItemIndex
                                10:10:0:0:Completed
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:8.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:5.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:8:StartFrame
                                10:4:10:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserVar
                                10:6:6.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjAnimFrame:Float
                                                $$CHILD_BLOCK_START
                                                10:1:2:-1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:10.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValue:Float
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:6:6.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:10:StartFrame
                                10:4:12:EndFrame
                                10:6:2.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:0:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aUserVarSet
                                $$CHILD_BLOCK_START
                                10:10:0:9:UserVar
                                10:6:1.000000:value
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Free Shuttle Sequence
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qTimesScriptExecuted_DALLAS:Integer
                                        $$CHILD_BLOCK_START
                                        10:11:32:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:0:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aRoomSetFaceTexture
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:4:87:FaceNum
                                10:14:12:Texture
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPath
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:16:2:Path
                                10:4:1:FirstNode
                                10:4:2:LastNode
                                10:4:1:StartNode
                                10:10:0:3:GoalPriority
                                10:15:131328:AIGoalFlags
                                10:10:0:0:GoalID
                                $$CHILD_BLOCK_END
                        08:aRoomSetWind
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:6:0.000000:X
                                10:6:0.000000:Y
                                10:6:-1.000000:Z
                                10:6:0.000000:Speed
                                $$CHILD_BLOCK_END
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:6:80.000000:Amount
                                10:6:200.000000:Dist
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Start Escape Shuttle on Path B
        $$CHILD_BLOCK_START
        01:1:27
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
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:4:87:FaceNum
                        10:14:13:Texture
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:0:GunNum
                        10:10:0:0:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.500000:BlobLifetime
                        10:6:0.050000:BlobInterval
                        10:6:25.000000:SpewLife
                        10:6:8.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:0.000000:Speed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:16:3:Path
                        10:4:1:FirstNode
                        10:4:4:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:131332:AIGoalFlags
                        10:10:0:2:GoalID
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:100.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ShuttleFreed:Message
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:6:100.000000:Amount
                        10:6:500.000000:Dist
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Remove Escape Shuttle
        $$CHILD_BLOCK_START
        01:1:27
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
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Start the Shuttle Sequence
        $$CHILD_BLOCK_START
        01:1:28
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
                        10:4:10:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:0:StartFrame
                        10:4:5:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:0:29:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Beam Ignition Panel Bumped
        $$CHILD_BLOCK_START
        01:1:30
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
                                                10:10:0:15:UserFlag
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
                                                                10:10:0:11:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:7
                                                        $$CHILD_BLOCK_END
                                                05:1
                                                        $$CHILD_BLOCK_START
                                                        06:qUserFlag:Bool
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:12:UserFlag
                                                                $$CHILD_BLOCK_END
                                                        07:0:7
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
                                                                09:0
                                                                        $$CHILD_BLOCK_START
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjAnimFrame:Float
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:21:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:6:6.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjAnimFrame:Float
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:22:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:6:6.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjAnimFrame:Float
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:23:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:6:6.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjAnimFrame:Float
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:24:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:6:6.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjAnimFrame:Float
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:25:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:6:6.000000:Literal
                                                                                $$CHILD_BLOCK_END
                                                                        05:2
                                                                                $$CHILD_BLOCK_START
                                                                                06:qObjAnimFrame:Float
                                                                                        $$CHILD_BLOCK_START
                                                                                        10:1:0:26:Object
                                                                                        $$CHILD_BLOCK_END
                                                                                07:1:0
                                                                                10:6:6.000000:Literal
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
                                                                        10:12:3:Sound
                                                                        10:1:2:-1:Object
                                                                        10:9:1.000000:Volume
                                                                        $$CHILD_BLOCK_END
                                                                08:aGoalCompleted
                                                                        $$CHILD_BLOCK_START
                                                                        10:18:0:8:LevelGoal
                                                                        10:10:0:1:Completed
                                                                        $$CHILD_BLOCK_END
                                                                08:aSetLevelTimer
                                                                        $$CHILD_BLOCK_START
                                                                        10:6:60.000000:Time
                                                                        10:10:0:6:TimerID
                                                                        $$CHILD_BLOCK_END
                                                                08:aSetLevelTimer
                                                                        $$CHILD_BLOCK_START
                                                                        10:6:10.000000:Time
                                                                        10:10:0:7:TimerID
                                                                        $$CHILD_BLOCK_END
                                                                08:aShowHUDMessage
                                                                        $$CHILD_BLOCK_START
                                                                        10:8:BeamIgnited:Message
                                                                        $$CHILD_BLOCK_END
                                                                08:aUserFlagSet
                                                                        $$CHILD_BLOCK_START
                                                                        10:10:0:17:UserFlag
                                                                        10:5:1:True/False
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        04:1:0:1
                                                                $$CHILD_BLOCK_START
                                                                08:aShowHUDMessage
                                                                        $$CHILD_BLOCK_START
                                                                        10:8:BeamIgniteError6:Message
                                                                        $$CHILD_BLOCK_END
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                04:1:0:1
                                                        $$CHILD_BLOCK_START
                                                        08:aShowHUDMessage
                                                                $$CHILD_BLOCK_START
                                                                10:8:BeamIgniteError5:Message
                                                                $$CHILD_BLOCK_END
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aShowHUDMessage
                                                        $$CHILD_BLOCK_START
                                                        10:8:BeamIgniteError4:Message
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        08:aShowHUDMessage
                                                $$CHILD_BLOCK_START
                                                10:8:BeamIgniteError3:Message
                                                $$CHILD_BLOCK_END
                                        08:aGoalCompleted
                                                $$CHILD_BLOCK_START
                                                10:18:0:9:LevelGoal
                                                10:10:0:0:Completed
                                                $$CHILD_BLOCK_END
                                        08:aGoalEnableDisable
                                                $$CHILD_BLOCK_START
                                                10:10:0:1:Enable/Disable
                                                10:18:0:9:LevelGoal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:BeamIgniteError2:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:BeamIgniteError1:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Create the Lens-Destroyer Robot
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Tell Lens Robot to Destroy Lens
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
                        10:10:0:3:SavedObjectSlot
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:0:Set/Clear
                        10:15:33554432:AIFlags
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:16:4:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LensRobotWarning:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Robot Reached Lens
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
                08:aObjKill
                        $$CHILD_BLOCK_START
                        06:qObjSavedHandle:Object
                                $$CHILD_BLOCK_START
                                10:10:0:3:SavedObjectSlot
                                $$CHILD_BLOCK_END
                        10:10:0:0:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:65760:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LensDestroyed:Message
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:10:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:11:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Picked up Spare Emitter Lens
        $$CHILD_BLOCK_START
        01:1:32
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
                                        10:10:0:16:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aAddObjectToInventory
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:GotSpareLens:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:10:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Used Spare Emitter Lens Program
        $$CHILD_BLOCK_START
        01:1:32
        02:25
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
                                        10:10:0:16:UserFlag
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
                                06:qObjGetDistance:Float
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object1
                                        10:1:0:33:Object2
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
                                        06:qObjExists:Bool
                                                $$CHILD_BLOCK_START
                                                10:1:0:31:Object
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aStoreObjectInPositionClipboard
                                        $$CHILD_BLOCK_START
                                        10:1:0:33:Object
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
                                        10:6:15.000000:Time
                                        10:10:0:8:TimerID
                                        $$CHILD_BLOCK_END
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:UseLensCompleted:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:16:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:11:LevelGoal
                                        10:10:0:1:Completed
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
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
                                08:aShowHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:8:UseLensFailed2:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
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
                        08:aShowHUDMessageObj
                                $$CHILD_BLOCK_START
                                10:8:UseLensFailed1:Message
                                10:1:1:-1:PlayerObject
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Handle Beam Generation (and check power supplies)
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
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
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
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:16:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:17:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:33:Object1
                                10:1:0:34:Object2
                                10:6:0.200000:Lifetime
                                10:6:1.000000:Thickness
                                10:4:5:NumTiles
                                10:14:14:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:21:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreateGunpoints
                                $$CHILD_BLOCK_START
                                10:4:0:Gunpoint1
                                10:4:1:Gunpoint2
                                10:1:0:21:Object
                                10:6:0.200000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:15:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:0:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:22:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreateGunpoints
                                $$CHILD_BLOCK_START
                                10:4:0:Gunpoint1
                                10:4:1:Gunpoint2
                                10:1:0:22:Object
                                10:6:0.200000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:15:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:0:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:23:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreateGunpoints
                                $$CHILD_BLOCK_START
                                10:4:0:Gunpoint1
                                10:4:1:Gunpoint2
                                10:1:0:23:Object
                                10:6:0.200000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:15:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:0:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:24:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreateGunpoints
                                $$CHILD_BLOCK_START
                                10:4:0:Gunpoint1
                                10:4:1:Gunpoint2
                                10:1:0:24:Object
                                10:6:0.200000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:15:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:0:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:25:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreateGunpoints
                                $$CHILD_BLOCK_START
                                10:4:0:Gunpoint1
                                10:4:1:Gunpoint2
                                10:1:0:25:Object
                                10:6:0.200000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:15:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:0:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:26:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:6.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aLightningCreateGunpoints
                                $$CHILD_BLOCK_START
                                10:4:0:Gunpoint1
                                10:4:1:Gunpoint2
                                10:1:0:26:Object
                                10:6:0.200000:Lifetime
                                10:6:10.000000:Thickness
                                10:4:1:NumTiles
                                10:14:15:Texture
                                10:6:0.500000:SlideTime
                                10:4:1:TimesDrawn
                                10:4:0:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserVarInc
                                $$CHILD_BLOCK_START
                                10:10:0:11:UserVar
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.200000:Time
                        10:10:0:5:TimerID
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
                                10:6:6.000000:Literal
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
                                                10:18:0:6:LevelGoal
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:6:LevelGoal
                                        10:10:0:1:Completed
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
                                                06:qGoalCompleted:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:6:LevelGoal
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:MirrorNodesUnaligned:Message
                                        $$CHILD_BLOCK_END
                                08:aGoalCompleted
                                        $$CHILD_BLOCK_START
                                        10:18:0:6:LevelGoal
                                        10:10:0:0:Completed
                                        $$CHILD_BLOCK_END
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
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
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
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qGoalEnabled:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:9:LevelGoal
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qGoalCompleted:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:9:LevelGoal
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
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
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qGoalEnabled:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:9:LevelGoal
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qGoalCompleted:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:18:0:9:LevelGoal
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
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:PowerInsufficient:Message
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
00:40:Transmission Completed
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:31:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TransmissionComplete:Message
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:12:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:5.000000:Time
                                10:10:0:9:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:New Transmission Completed
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TransmissionComplete:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:12:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:5.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Start End Level Sequence
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
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:13:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:5:CameraPath
                        10:16:6:PlayerPath
                        10:6:20.000000:Time
                        10:8:Empty:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Music Init
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
                        10:10:0:2:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Music Wing-1
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:56:Music Top-1
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
00:55:Music Bottom-2
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Music Bottom-1
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Music Middle-4
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
00:52:Music Middle-3
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
00:51:Music Middle-2
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
00:50:Music Middle-1
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
00:58:Picked up Beam Journal
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:JournalBeamGame:GameMessage
                        10:8:JournalBeamHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Picked up Shield Journal
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:JournalShieldGame:GameMessage
                        10:8:JournalShieldHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Picked up Virus Journal
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:JournalVirusGame:GameMessage
                        10:8:JournalVirusHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Picked up Power Journal
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:JournalPowerGame:GameMessage
                        10:8:JournalPowerHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Picked up Robot Journal
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:JournalRobotGame:GameMessage
                        10:8:JournalRobotHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Picked up Dial Journal
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
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:JournalDialGame:GameMessage
                        10:8:JournalDialHUD:HUDMessage
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Dan's Spewer System
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
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:41:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:42:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:44:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:45:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:46:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:47:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:50:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
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
                        10:6:0.750000:BlobLifetime
                        10:6:0.020000:BlobInterval
                        10:6:1.250000:SpewLife
                        10:6:1.250000:BlobSize
                        10:6:36.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:0:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:20.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
