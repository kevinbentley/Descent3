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
// Filename:	level5.cpp
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
static void aCustomReactorDisplayInit();
static void aCustomReactorDisplayUpdate();
static void dsCustomSave(void *fileptr);
static void dsCustomRestore(void *fileptr);

// =================
// Script ID Numbers
// =================
#define ID_LEVEL_0000 0x000

#define ID_CUSTOM_OBJECT_200D 0x001
#define ID_CUSTOM_OBJECT_281B 0x002
#define ID_CUSTOM_OBJECT_3816 0x003
#define ID_CUSTOM_OBJECT_1012 0x004
#define ID_CUSTOM_OBJECT_181C 0x005
#define ID_CUSTOM_OBJECT_0820 0x006
#define ID_CUSTOM_OBJECT_1044 0x007

#define ID_TRIGGER_0000 0x008
#define ID_TRIGGER_0005 0x009
#define ID_TRIGGER_0006 0x00a
#define ID_TRIGGER_0004 0x00b
#define ID_TRIGGER_0009 0x00c
#define ID_TRIGGER_0002 0x00d
#define ID_TRIGGER_0007 0x00e
#define ID_TRIGGER_0003 0x00f
#define ID_TRIGGER_000A 0x010
#define ID_TRIGGER_0001 0x011
#define ID_TRIGGER_0008 0x012
#define ID_TRIGGER_0010 0x013
#define ID_TRIGGER_000E 0x014
#define ID_TRIGGER_000C 0x015
#define ID_TRIGGER_0014 0x016
#define ID_TRIGGER_0012 0x017
#define ID_TRIGGER_000F 0x018
#define ID_TRIGGER_000D 0x019
#define ID_TRIGGER_000B 0x01a
#define ID_TRIGGER_0013 0x01b
#define ID_TRIGGER_0011 0x01c
#define ID_TRIGGER_0016 0x01d
#define ID_TRIGGER_0017 0x01e
#define ID_TRIGGER_0015 0x01f
#define ID_TRIGGER_0018 0x020

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

class CustomObjectScript_200D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_281B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3816 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1012 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_181C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0820 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1044 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
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

class TriggerScript_0004 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0002 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0003 : public BaseScript {
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

class TriggerScript_0008 : public BaseScript {
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

class TriggerScript_0014 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0012 : public BaseScript {
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

class TriggerScript_000B : public BaseScript {
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

class TriggerScript_0016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0017 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0018 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_090 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_015 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_052 = 0;
static int ScriptActionCtr_053 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_055 = 0;
static int ScriptActionCtr_056 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_061 = 0;
static int ScriptActionCtr_062 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_089 = 0;
static int ScriptActionCtr_030 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_055 = 0;
  ScriptActionCtr_056 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_089 = 0;
  ScriptActionCtr_030 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_055, file_ptr);
  File_WriteInt(ScriptActionCtr_056, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_089, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_055 = File_ReadInt(file_ptr);
  ScriptActionCtr_056 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_089 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

/*
$$ENUM Region
0:Intro
1:MainHub
2:Tunnels
3:Reactor
4:EscapeSequence
$$END
*/

#define NUM_REACTORS 5

static const char *const Reactor_names[NUM_REACTORS] = {"Reactor1", "Reactor2", "Reactor3", "Reactor4", "Reactor5"};
static int Reactor_handles[NUM_REACTORS];
static float Reactor_initial_shields[NUM_REACTORS];
static int Reactor_shields_percent[NUM_REACTORS];
static const char *Reactor_text;

static const char *GetMessage(const char *name);

/*
$$ACTION
Custom
Intialize reactor display
aCustomReactorDisplayInit
Intialize reactor display
  Initializes the HUD display for the reactors

$$END
*/
void aCustomReactorDisplayInit() {
  msafe_struct mstruct;

  // Get handles for each reactor & init shields
  for (int i = 0; i < NUM_REACTORS; i++) {
    Reactor_handles[i] = Scrpt_FindObjectName(Reactor_names[i]);

    mstruct.objhandle = Reactor_handles[i];
    MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &mstruct);
    Reactor_initial_shields[i] = mstruct.shields;

    Reactor_shields_percent[i] = -1; // Force update first time
  }

  Reactor_text = GetMessage("ReactorHUDLabel");
}

/*
$$ACTION
Custom
Update reactor display
aCustomReactorDisplayUpdate
Update reactor display
  Updates the HUD display for the reactors

$$END
*/
void aCustomReactorDisplayUpdate() {
  msafe_struct mstruct;
  bool update = 0;
  int i;

  // Update shields for each reactor
  for (i = 0; i < NUM_REACTORS; i++) {
    mstruct.objhandle = Reactor_handles[i];
    MSafe_GetValue(MSAFE_OBJECT_SHIELDS, &mstruct);

    int percent = (int)ceil(mstruct.shields / Reactor_initial_shields[i] * 100);

    if (Reactor_shields_percent[i] != percent) {
      Reactor_shields_percent[i] = percent;
      update = 1;
    }
  }

  if (update) {
    mstruct.color = GR_RGB(255, 0, 0);
    snprintf(mstruct.message, sizeof(mstruct.message), "%s", Reactor_text);
    char *t = mstruct.message + strlen(mstruct.message);
    for (i = 0; i < NUM_REACTORS; i++)
      t += sprintf(t, "\n  %d: %d%%", i + 1, Reactor_shields_percent[i]);
    MSafe_CallFunction(MSAFE_MISC_UPDATE_HUD_ITEM, &mstruct);
  }
}

// Tell the code to call our functions
#define ENABLE_CUSTOM_SAVE_AND_RESTORE

// Save custom data for this script
void dsCustomSave(void *fileptr) {
  for (int i = 0; i < NUM_REACTORS; i++) {
    File_WriteInt(Reactor_handles[i], fileptr);
    File_WriteFloat(Reactor_initial_shields[i], fileptr);
    File_WriteInt(Reactor_shields_percent[i], fileptr);
  }
}

// Restore custom data for this script
void dsCustomRestore(void *fileptr) {
  for (int i = 0; i < NUM_REACTORS; i++) {
    Reactor_handles[i] = File_ReadInt(fileptr);
    Reactor_initial_shields[i] = File_ReadFloat(fileptr);
    Reactor_shields_percent[i] = File_ReadInt(fileptr);
  }

  Reactor_text = GetMessage("ReactorHUDLabel");
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
static const char *const Door_names[NUM_DOOR_NAMES] = {"ExitDoor"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 15
static const char *const Object_names[NUM_OBJECT_NAMES] = {"Reactor1",  "Reactor2", "Reactor3", "Reactor4", "Reactor5",
                                                           "StartDoor", "Flame01",  "Flame03",  "Flame04",  "Flame05",
                                                           "Flame06",   "Flame07",  "Flame08",  "Flame09",  "ExitDoor"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 10
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "Reactor5Screen", "Reactor4Screen", "Reactor3Screen", "Reactor2Screen", "Reactor1Screen",
    "Reactor5Room",   "Reactor4Room",   "Reactor3Room",   "Reactor2Room",   "Reactor1Room"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 25
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {"ExitSequenceTrigger",
                                                             "IntoTunnel1",
                                                             "MainHub1",
                                                             "MainHub2",
                                                             "MainHub3",
                                                             "MainHub4",
                                                             "MainHub5",
                                                             "IntoTunnel2",
                                                             "IntoTunnel3",
                                                             "IntoTunnel4",
                                                             "IntoTunnel5",
                                                             "OutReactor1",
                                                             "OutReactor2",
                                                             "OutReactor3",
                                                             "OutReactor4",
                                                             "OutReactor5",
                                                             "IntoReactor1",
                                                             "IntoReactor2",
                                                             "IntoReactor3",
                                                             "IntoReactor4",
                                                             "IntoReactor5",
                                                             "IntoReactor4Mainten",
                                                             "IntoReactor3Mainten",
                                                             "OutReactor3Maintena",
                                                             "OutReactor4Maintena"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 10
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "AmbDroneReactor",  "DoorIsLocked",     "ExpMissileLarge1", "ExpMissileMed1",   "Lightning",
    "AmbExplosionFarA", "AmbExplosionFarG", "AmbExplosionFarI", "AmbExplosionFarD", "AmbExplosionFarE"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 4
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"RedAMon75", "RedAMon50", "RedAMon25", "Staticscrolling"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 14
static const char *const Path_names[NUM_PATH_NAMES] = {
    "Matcen12To1", "Matcen12To2", "Matcen12To3",      "Matcen34To3",   "Matcen34To4",
    "Mat5To5",     "Matcen5To4",  "Matcen5To2",       "IntroCamera",   "IntroPlayerPath",
    "ExitCamera2", "PlayerExit3", "ExitCameraTunnel", "PlayerExit1Alt"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 3
static const char *const Matcen_names[NUM_MATCEN_NAMES] = {"Matcen34", "Matcen5", "Matcen12"};
static int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 8
static const char *const Goal_names[NUM_GOAL_NAMES] = {"Keep Reactor 5 Alive",      "Keep Reactor 4 Alive",
                                                       "Keep Reactor 3 Alive",      "Keep Reactor 2 Alive",
                                                       "Keep Reactor 1 Alive",      "Defend Red Acropolis and Escape",
                                                       "Escape from Red Acropolis", "Keep 3 of the 5 reactors alive"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 21
static const char *const Message_names[NUM_MESSAGE_NAMES] = {"IntroMessage",    "DefendThoseReactors2",
                                                             "IncomingMessage", "DefendReactorsShort",
                                                             "Reactor5Status",  "Health75",
                                                             "Reactor4Status",  "Reactor3Status",
                                                             "Reactor2Status",  "Reactor1Status",
                                                             "Health50",        "Health25",
                                                             "Destroyed",       "HITPOINTS",
                                                             "BLANK",           "OOPS",
                                                             "WereGettinOut",   "SelfDestruct",
                                                             "ExitOnly",        "EntranceDoorMessage",
                                                             "30SecondsLeft"};
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
    strcpy(filename, "level5.msg");
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
  case ID_CUSTOM_OBJECT_200D:
    return new CustomObjectScript_200D;
    break;
  case ID_CUSTOM_OBJECT_281B:
    return new CustomObjectScript_281B;
    break;
  case ID_CUSTOM_OBJECT_3816:
    return new CustomObjectScript_3816;
    break;
  case ID_CUSTOM_OBJECT_1012:
    return new CustomObjectScript_1012;
    break;
  case ID_CUSTOM_OBJECT_181C:
    return new CustomObjectScript_181C;
    break;
  case ID_CUSTOM_OBJECT_0820:
    return new CustomObjectScript_0820;
    break;
  case ID_CUSTOM_OBJECT_1044:
    return new CustomObjectScript_1044;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_0002:
    return new TriggerScript_0002;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0001:
    return new TriggerScript_0001;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
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
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0013:
    return new TriggerScript_0013;
    break;
  case ID_TRIGGER_0011:
    return new TriggerScript_0011;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_0015:
    return new TriggerScript_0015;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
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
  case ID_CUSTOM_OBJECT_200D:
    delete ((CustomObjectScript_200D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_281B:
    delete ((CustomObjectScript_281B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3816:
    delete ((CustomObjectScript_3816 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1012:
    delete ((CustomObjectScript_1012 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_181C:
    delete ((CustomObjectScript_181C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0820:
    delete ((CustomObjectScript_0820 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1044:
    delete ((CustomObjectScript_1044 *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_0002:
    delete ((TriggerScript_0002 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0001:
    delete ((TriggerScript_0001 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
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
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0013:
    delete ((TriggerScript_0013 *)ptr);
    break;
  case ID_TRIGGER_0011:
    delete ((TriggerScript_0011 *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_0015:
    delete ((TriggerScript_0015 *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
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
  case ID_CUSTOM_OBJECT_200D:
  case ID_CUSTOM_OBJECT_281B:
  case ID_CUSTOM_OBJECT_3816:
  case ID_CUSTOM_OBJECT_1012:
  case ID_CUSTOM_OBJECT_181C:
  case ID_CUSTOM_OBJECT_0820:
  case ID_CUSTOM_OBJECT_1044:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0018:
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
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0018;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[7];
  static int cust_id_list[7] = {ID_CUSTOM_OBJECT_200D, ID_CUSTOM_OBJECT_281B, ID_CUSTOM_OBJECT_3816,
                                ID_CUSTOM_OBJECT_1012, ID_CUSTOM_OBJECT_181C, ID_CUSTOM_OBJECT_0820,
                                ID_CUSTOM_OBJECT_1044};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[4];
  cust_handle_list[1] = Object_handles[3];
  cust_handle_list[2] = Object_handles[2];
  cust_handle_list[3] = Object_handles[1];
  cust_handle_list[4] = Object_handles[0];
  cust_handle_list[5] = Object_handles[14];
  cust_handle_list[6] = Object_handles[5];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 7;
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

    // Script 028: Update Reactor Display
    if (1) {
      aCustomReactorDisplayUpdate();

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }

    // Script 036: 3 Reactors Dead
    if ((ScriptActionCtr_036 < 1) && ((qUserVarValueInt(1) >= 3) && ((ScriptActionCtr_069 > 0) == false))) {
      aAddGameMessage(Message_strings[15], Message_strings[2]);
      aGoalFailed(Goal_indexes[7], 1);
      aSetLevelTimer(3.000000f, 5);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: LevelStartInits
    if (1) {
      aCustomReactorDisplayInit();
      aMatcenSetState(1, Matcen_indexes[0]);
      aMatcenSetState(1, Matcen_indexes[1]);
      aMatcenSetState(1, Matcen_indexes[2]);
      aSetLevelTimer(qRandomValue(30.000000f, 45.000000f), 4);
      aUserVarSet(1, 0.000000f);
      aUserVarSet(8, 0.000000f);
      aUserVarSet(9, 0.000000f);
      aSetLevelTimer(12.000000f, 7);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 001: StartIntroMovie
    if (1) {
      aCinematicIntro(Path_indexes[8], Message_strings[0], Object_handles[5], Path_indexes[9], 10.000000f);
      aSetLevelTimer(2.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }

    // Script 004: All Reactors are on
    if ((ScriptActionCtr_004 < 1) && (1)) {
      aAISetTeam(65536, Object_handles[0]);
      aAISetTeam(65536, Object_handles[1]);
      aAISetTeam(65536, Object_handles[2]);
      aAISetTeam(65536, Object_handles[3]);
      aAISetTeam(65536, Object_handles[4]);
      aSetLevelTimer(720.000000f, 2);
      aTimerShow(2);
      aSetLevelTimer(2.000000f, 12);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }

    // Script 041: Music-Intro
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }

    // Script 086: Second General Voice
    if ((ScriptActionCtr_086 < 1) && (1)) {
      aSetLevelTimer(60.000000f, 8);

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 074: RestartLevel
    if ((ScriptActionCtr_074 < 1) && (event_data->id == 5)) {
      aFailLevel();

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }

    // Script 069: ReactorsLive
    if ((event_data->id == 2) && (qUserVarValueInt(1) < 3)) {
      aGoalCompleted(Goal_indexes[7], 1);
      aGoalEnableDisable(0, Goal_indexes[0]);
      aGoalEnableDisable(0, Goal_indexes[1]);
      aGoalEnableDisable(0, Goal_indexes[2]);
      aGoalEnableDisable(0, Goal_indexes[3]);
      aGoalEnableDisable(0, Goal_indexes[4]);
      aAddGameMessage(Message_strings[16], Message_strings[2]);
      aDoorLockUnlock(0, Door_handles[0]);
      aDoorSetPos(Door_handles[0], 1.000000f);
      aShowHUDMessage(Message_strings[17]);
      aSetLevelTimer(60.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_069 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_069++;
    }

    // Script 066: ReactorAlive-5
    if ((event_data->id == 2) && (qUserVarValueInt(1) < 3) && (qGoalFailed(Goal_indexes[0]) == false)) {
      aObjMakeInvuln(Object_handles[4], 99999);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }

    // Script 035: ReactorAlive-4
    if ((event_data->id == 2) && (qUserVarValueInt(1) < 3) && (qGoalFailed(Goal_indexes[1]) == false)) {
      aObjMakeInvuln(Object_handles[3], 99999);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }

    // Script 034: ReactorAlive-3
    if ((event_data->id == 2) && (qUserVarValueInt(1) < 3) && (qGoalFailed(Goal_indexes[2]) == false)) {
      aObjMakeInvuln(Object_handles[2], 99999);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 033: ReactorAlive-2
    if ((event_data->id == 2) && (qUserVarValueInt(1) < 3) && (qGoalFailed(Goal_indexes[3]) == false)) {
      aObjMakeInvuln(Object_handles[1], 99999);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }

    // Script 032: ReactorAlive-1
    if ((event_data->id == 2) && (qUserVarValueInt(1) < 3) && (qGoalFailed(Goal_indexes[4]) == false)) {
      aObjMakeInvuln(Object_handles[0], 99999);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }

    // Script 029: 30Seconds Left
    if ((event_data->id == 13) && (qUserVarValue(8) == 0.000000f)) {
      aShowHUDMessage(Message_strings[20]);
      aSetLevelTimer(30.000000f, 3);
      aTimerShow(3);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }

    // Script 039: Exit clock goes off
    if ((ScriptActionCtr_039 < 1) && ((event_data->id == 3) && ((ScriptActionCtr_011 > 0) == false))) {
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aSoundPlay2D(Sound_indexes[3], 1.000000f);
      aSoundPlay2D(Sound_indexes[4], 1.000000f);
      aFadeWhiteAndEndlevel(3.000000f, Message_strings[14]);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 068: Random Level Shake
    if ((event_data->id == 4) && ((ScriptActionCtr_011 > 0) == 0)) {
      aSetLevelTimer(qRandomValue(30.000000f, 45.000000f), 4);
      aMiscViewerShake(qRandomValue(70.000000f, 100.000000f));
      aUserVarSet(7, qRandomValue(1.000000f, 5.000000f));
      if (qUserVarValueInt(7) == 1) {
        aSoundPlay2D(Sound_indexes[5], 1.000000f);
      } else {
        if (qUserVarValueInt(7) == 2) {
          aSoundPlay2D(Sound_indexes[6], 1.000000f);
        } else {
          if (qUserVarValueInt(7) == 3) {
            aSoundPlay2D(Sound_indexes[7], 1.000000f);
          } else {
            if (qUserVarValueInt(7) == 4) {
              aSoundPlay2D(Sound_indexes[8], 1.000000f);
            } else {
              aSoundPlay2D(Sound_indexes[9], 1.000000f);
            }
          }
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }

    // Script 083: First Voice Message
    if ((ScriptActionCtr_083 < 1) && (event_data->id == 7)) {
      aSoundPlaySteaming("VoxL05StartLev.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }

    // Script 087: Second General Voice Part 2
    if ((ScriptActionCtr_087 < 1) && (event_data->id == 8)) {
      aSoundPlaySteaming("VoxL05GeneralA.osf", 1.000000f);
      aSetLevelTimer(180.000000f, 9);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }

    // Script 088: Third VO shuttle C
    if ((ScriptActionCtr_088 < 1) && (event_data->id == 9)) {
      aSoundPlaySteaming("VoxL05GeneralC.osf", 1.000000f);
      aSetLevelTimer(10.000000f, 10);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }

    // Script 089: Fourth VO shuttle C response
    if ((ScriptActionCtr_089 < 1) && (event_data->id == 10)) {
      aSoundPlaySteaming("VoxL05GeneralD.osf", 1.000000f);
      aSetLevelTimer(60.000000f, 11);

      // Increment the script action counter
      if (ScriptActionCtr_089 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_089++;
    }

    // Script 030: Fifth VO shuttle C response
    if ((ScriptActionCtr_030 < 1) && (event_data->id == 11)) {
      aSoundPlaySteaming("VoxL05GeneralB.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  case EVT_MATCEN_CREATE: {
    tOSIRISEVTMATCENCREATE *event_data = &data->evt_matcen_create;

    // Script 017: Send Matcen12 Guy to Reactor
    if (event_data->id == Matcen_indexes[2]) {
      aAISetFOV(event_data->it_handle, 360.000000f);
      aAIFlags(1, 64, event_data->it_handle);
      if (qRandomChance(0.010000f) == true) {
        aAIFlags(0, 1024, event_data->it_handle);
      }
      if (((qRandomChance(0.500000f) == true) && (qObjShields(Object_handles[0]) > 0.000000f)) ||
          ((qObjShields(Object_handles[1]) <= 0.000000f) && (qObjShields(Object_handles[2]) <= 0.000000f))) {
        aAISetTarget(event_data->it_handle, Object_handles[0]);
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[0], 4352, -1, 0);
      } else {
        if (qObjShields(Object_handles[1]) > 0.000000f) {
          aAISetTarget(event_data->it_handle, Object_handles[1]);
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[1], 4352, -1, 0);
        } else {
          aAISetTarget(event_data->it_handle, Object_handles[2]);
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[2], 4352, -1, 0);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 003: Send Matcen34 Guy to Reactor
    if (event_data->id == Matcen_indexes[0]) {
      aAISetFOV(event_data->it_handle, 360.000000f);
      aAIFlags(1, 64, event_data->it_handle);
      if (qRandomChance(0.010000f) == true) {
        aAIFlags(0, 1024, event_data->it_handle);
      }
      if (((qRandomChance(0.500000f) == true) && (qObjShields(Object_handles[3]) > 0.000000f)) ||
          (qObjShields(Object_handles[2]) <= 0.000000f)) {
        aAISetTarget(event_data->it_handle, Object_handles[3]);
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[3], 4352, -1, 0);
      } else {
        aAISetTarget(event_data->it_handle, Object_handles[2]);
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[4], 4352, -1, 0);
      }

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 090: Send Matcen5 Guy to Reactor
    if (event_data->id == Matcen_indexes[1]) {
      aAISetFOV(event_data->it_handle, 360.000000f);
      aAIFlags(1, 64, event_data->it_handle);
      if (qRandomChance(0.010000f) == true) {
        aAIFlags(0, 1024, event_data->it_handle);
      }
      if (qObjShields(Object_handles[4]) > 0.000000f) {
        aAISetTarget(event_data->it_handle, Object_handles[4]);
        aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[5], 4352, 0, 3);
      } else {
        if (qObjShields(Object_handles[3]) > 0.000000f) {
          aAISetTarget(event_data->it_handle, Object_handles[3]);
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[6], 4352, -1, 0);
        } else {
          aAISetTarget(event_data->it_handle, Object_handles[1]);
          aAIGoalFollowPathSimple(event_data->it_handle, Path_indexes[7], 4352, -1, 0);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 009: GiveStartMessage
    if ((ScriptActionCtr_009 < 1) && (1)) {
      aSoundPlayObject(Sound_indexes[0], Object_handles[4], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[3], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[2], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[1], 1.000000f);
      aSoundPlayObject(Sound_indexes[0], Object_handles[0], 1.000000f);
      aObjPlayAnim(Object_handles[4], 0, 32, 4.000000f, 1);
      aObjPlayAnim(Object_handles[3], 0, 32, 4.000000f, 1);
      aObjPlayAnim(Object_handles[2], 0, 32, 4.000000f, 1);
      aObjPlayAnim(Object_handles[1], 0, 32, 4.000000f, 1);
      aObjPlayAnim(Object_handles[0], 0, 32, 4.000000f, 1);
      aAddGameMessage(Message_strings[1], Message_strings[2]);
      aShowHUDMessage(Message_strings[3]);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 031: Exit Sequence Part 2
    if ((ScriptActionCtr_011 > 0) == true) {
      aStartEndlevelSequencePath(Path_indexes[10], Path_indexes[11], 9.000000f, Message_strings[14]);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_200D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Reactor5Status75percent
    if ((ScriptActionCtr_027 < 1) && ((qObjShields(data->me_handle) < 22500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[4]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[5]);
      aRoomSetFaceTexture(Room_indexes[0], 3, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }

    // Script 023: Reactor5Status50percent
    if ((ScriptActionCtr_023 < 1) && ((qObjShields(data->me_handle) < 15000.000000f) && (1))) {
      aShowHUDMessage(Message_strings[4]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[10]);
      aRoomSetFaceTexture(Room_indexes[0], 3, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 019: Reactor5Status25percent
    if ((ScriptActionCtr_019 < 1) && ((qObjShields(data->me_handle) < 7500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[4]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[11]);
      aRoomSetFaceTexture(Room_indexes[0], 3, Texture_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 014: Reactor5StatusDestroyed
    if ((ScriptActionCtr_014 < 1) && ((qObjShields(data->me_handle) <= 0.000000f) && (1))) {
      aAISetTeam(196608, data->me_handle);
      aShowHUDMessage(Message_strings[4]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[12]);
      aUserVarInc(1);
      aObjPlayAnim(data->me_handle, 0, 0, 1.000000f, 0);
      aObjSpark(data->me_handle, 40.000000f, 99999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[5]);
      aRoomSetFaceTexture(Room_indexes[0], 3, Texture_indexes[3]);
      aSoundStopObj(data->me_handle);
      aGoalFailed(Goal_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }

    // Script 002: Debug Script for Reactor 1
    if (0 == true) {
      aShowHUDMessageF(Message_strings[13], qObjShields(Object_handles[4]));

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_281B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Reactor4Status75percent
    if ((ScriptActionCtr_026 < 1) && ((qObjShields(data->me_handle) < 22500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[6]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[5]);
      aRoomSetFaceTexture(Room_indexes[1], 3, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }

    // Script 022: Reactor4Status50percent
    if ((ScriptActionCtr_022 < 1) && ((qObjShields(data->me_handle) < 15000.000000f) && (1))) {
      aShowHUDMessage(Message_strings[6]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[10]);
      aRoomSetFaceTexture(Room_indexes[1], 3, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 018: Reactor4Status25percent
    if ((ScriptActionCtr_018 < 1) && ((qObjShields(data->me_handle) < 7500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[6]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[11]);
      aRoomSetFaceTexture(Room_indexes[1], 3, Texture_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 013: Reactor4StatusDestroyed
    if ((ScriptActionCtr_013 < 1) && ((qObjShields(data->me_handle) <= 0.000000f) && (1))) {
      aAISetTeam(196608, data->me_handle);
      aShowHUDMessage(Message_strings[6]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[12]);
      aUserVarInc(1);
      aObjPlayAnim(data->me_handle, 0, 0, 1.000000f, 0);
      aObjSpark(data->me_handle, 40.000000f, 99999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[6]);
      aRoomSetFaceTexture(Room_indexes[1], 3, Texture_indexes[3]);
      aSoundStopObj(data->me_handle);
      aGoalFailed(Goal_indexes[1], 1);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3816::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Reactor3Status75percent
    if ((ScriptActionCtr_025 < 1) && ((qObjShields(data->me_handle) < 22500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[7]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[5]);
      aRoomSetFaceTexture(Room_indexes[2], 3, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }

    // Script 021: Reactor3Status50percent
    if ((ScriptActionCtr_021 < 1) && ((qObjShields(data->me_handle) < 15000.000000f) && (1))) {
      aShowHUDMessage(Message_strings[7]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[10]);
      aRoomSetFaceTexture(Room_indexes[2], 3, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 016: Reactor3Status25percent
    if ((ScriptActionCtr_016 < 1) && ((qObjShields(data->me_handle) < 7500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[7]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[11]);
      aRoomSetFaceTexture(Room_indexes[2], 3, Texture_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 012: Reactor3StatusDestroyed
    if ((ScriptActionCtr_012 < 1) && ((qObjShields(data->me_handle) <= 0.000000f) && (1))) {
      aAISetTeam(196608, data->me_handle);
      aShowHUDMessage(Message_strings[7]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[12]);
      aUserVarInc(1);
      aObjPlayAnim(data->me_handle, 0, 0, 1.000000f, 0);
      aObjSpark(data->me_handle, 40.000000f, 99999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[7]);
      aRoomSetFaceTexture(Room_indexes[2], 3, Texture_indexes[3]);
      aSoundStopObj(data->me_handle);
      aGoalFailed(Goal_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Reactor2Status75percent
    if ((ScriptActionCtr_024 < 1) && ((qObjShields(data->me_handle) < 22500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[8]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[5]);
      aRoomSetFaceTexture(Room_indexes[3], 3, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }

    // Script 020: Reactor2Status50percent
    if ((ScriptActionCtr_020 < 1) && ((qObjShields(data->me_handle) < 15000.000000f) && (1))) {
      aShowHUDMessage(Message_strings[8]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[10]);
      aRoomSetFaceTexture(Room_indexes[3], 3, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }

    // Script 015: Reactor2Status25percent
    if ((ScriptActionCtr_015 < 1) && ((qObjShields(data->me_handle) < 7500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[8]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[11]);
      aRoomSetFaceTexture(Room_indexes[3], 3, Texture_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }

    // Script 008: Reactor2StatusDestroyed
    if ((ScriptActionCtr_008 < 1) && ((qObjShields(data->me_handle) <= 0.000000f) && (1))) {
      aAISetTeam(196608, data->me_handle);
      aShowHUDMessage(Message_strings[8]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[12]);
      aUserVarInc(1);
      aObjPlayAnim(data->me_handle, 0, 0, 1.000000f, 0);
      aObjSpark(data->me_handle, 40.000000f, 99999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[8]);
      aRoomSetFaceTexture(Room_indexes[3], 3, Texture_indexes[3]);
      aSoundStopObj(data->me_handle);
      aGoalFailed(Goal_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_181C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 005: Reactor1Status75percent
    if ((ScriptActionCtr_005 < 1) && ((qObjShields(data->me_handle) < 22500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[9]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[5]);
      aRoomSetFaceTexture(Room_indexes[4], 3, Texture_indexes[0]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 006: Reactor1Status50percent
    if ((ScriptActionCtr_006 < 1) && ((qObjShields(data->me_handle) < 15000.000000f) && (1))) {
      aShowHUDMessage(Message_strings[9]);
      aShowColoredHUDMessage(255, 255, 0, Message_strings[10]);
      aRoomSetFaceTexture(Room_indexes[4], 3, Texture_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }

    // Script 007: Reactor1Status25percent
    if ((ScriptActionCtr_007 < 1) && ((qObjShields(data->me_handle) < 7500.000000f) && (1))) {
      aShowHUDMessage(Message_strings[9]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[11]);
      aRoomSetFaceTexture(Room_indexes[4], 3, Texture_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }

    // Script 010: Reactor1StatusDestroyed
    if ((ScriptActionCtr_010 < 1) && ((qObjShields(data->me_handle) <= 0.000000f) && (1))) {
      aAISetTeam(196608, data->me_handle);
      aShowHUDMessage(Message_strings[9]);
      aShowColoredHUDMessage(255, 0, 0, Message_strings[12]);
      aUserVarInc(1);
      aObjPlayAnim(data->me_handle, 0, 0, 1.000000f, 0);
      aObjSpark(data->me_handle, 40.000000f, 99999.000000f);
      aRoomSetLightingFlicker(1, Room_indexes[9]);
      aRoomSetFaceTexture(Room_indexes[4], 3, Texture_indexes[3]);
      aSoundStopObj(data->me_handle);
      aGoalFailed(Goal_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0820::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: ExitDoorMessage
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[18]);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1044::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: EntranceDoorMessage
    if (qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[19]);
      aSoundPlay2DObj(Sound_indexes[1], event_data->it_handle, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: ExitCameraSequence
    if ((ScriptActionCtr_011 < 1) && (qObjIsPlayer(event_data->it_handle) == 1)) {
      aGoalCompleted(Goal_indexes[5], 1);
      aGoalCompleted(Goal_indexes[6], 1);
      aCinematicIntro(Path_indexes[12], Message_strings[14], Object_handles[6], Path_indexes[13], 6.500000f);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 082: FlamesTest
    if (qObjIsPlayer(event_data->it_handle) == 1) {
      aTurnOnSpew(Object_handles[6], -1, 2, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[7], -1, 8, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[7], -1, 2, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[8], -1, 2, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[9], -1, 2, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[10], -1, 2, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[11], -1, 2, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[12], -1, 4, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);
      aTurnOnSpew(Object_handles[13], -1, 3, 0.000000f, 0.000000f, 65536, 0, 4.000000f, 0.150000f, -1.000000f,
                  15.000000f, 60.000000f, 1, -1);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 040: IntoTunnel1
    if (qObjIsPlayer(event_data->it_handle) == true) {

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 047: Music-enter Tunnel1
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Music-MainHub1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 043: Music-MainHub2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 045: Music-MainHub3
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 044: Music-MainHub4
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

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

    // Script 046: Music-MainHub5
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 048: Music-enter Tunnel2
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 049: Music-enter Tunnel3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: Music-enter Tunnel4
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

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 051: Music-enter Tunnel5
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

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 052: Music-Tunnel1 from Reactor1
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

int16_t TriggerScript_000E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 053: Music-Tunnel2 from Reactor2
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

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 054: Music-Tunnel3 from Reactor3
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 055: Music-Tunnel4 from Reactor4
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_055 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_055++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 056: Music-Tunnel5 from Reactor5
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_056 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_056++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 057: Reactor1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Reactor2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 059: Reactor3
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 058: Reactor4
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Reactor5
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

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

    // Script 062: Enter reactor 4 from maintenance tube
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

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Enter reactor 3 from maintenance tube
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

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Leave reactor 3 into maintenance tube
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

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Leave reactor 4 into maintenance tube
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_065 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_065++;
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
0:Reactors are on
1:ReactorsDestroyed
2:Reactor1Damage
3:Reactor2Damage
4:Reactor3Damage
5:Reactor4Damage
6:Reactor5Damage
7:RandomSound
8:PlayerExitted
9:ExitMovieSequences
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:EndMovieplayed
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:IntroCameraTimer
1:IntroMovieDone
2:MaintainReactors
3:XsecondCountdown
4:ShakeTimer
5:FailedTimer
6:ReactorTimer
7:FirstVoiceOverMessage
8:SecondVoiceOverMessage
9:ThirdVOshuttleC
10:VOShuttleRescueResponse
11:FifthVO
12:MatcenTimer
13:ShortCountdown
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:Reactor5
1:Reactor4
2:Reactor3
3:Reactor2
4:Reactor1
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
ExitDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
Reactor1
Reactor2
Reactor3
Reactor4
Reactor5
StartDoor
Flame01
Flame03
Flame04
Flame05
Flame06
Flame07
Flame08
Flame09
ExitDoor
$$OBJECT_LIST_END

$$ROOM_LIST_START
Reactor5Screen
Reactor4Screen
Reactor3Screen
Reactor2Screen
Reactor1Screen
Reactor5Room
Reactor4Room
Reactor3Room
Reactor2Room
Reactor1Room
$$ROOM_LIST_END

$$TRIGGER_LIST_START
ExitSequenceTrigger
IntoTunnel1
MainHub1
MainHub2
MainHub3
MainHub4
MainHub5
IntoTunnel2
IntoTunnel3
IntoTunnel4
IntoTunnel5
OutReactor1
OutReactor2
OutReactor3
OutReactor4
OutReactor5
IntoReactor1
IntoReactor2
IntoReactor3
IntoReactor4
IntoReactor5
IntoReactor4Mainten
IntoReactor3Mainten
OutReactor3Maintena
OutReactor4Maintena
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbDroneReactor
DoorIsLocked
ExpMissileLarge1
ExpMissileMed1
Lightning
AmbExplosionFarA
AmbExplosionFarG
AmbExplosionFarI
AmbExplosionFarD
AmbExplosionFarE
$$SOUND_LIST_END

$$TEXTURE_LIST_START
RedAMon75
RedAMon50
RedAMon25
Staticscrolling
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
Matcen12To1
Matcen12To2
Matcen12To3
Matcen34To3
Matcen34To4
Mat5To5
Matcen5To4
Matcen5To2
IntroCamera
IntroPlayerPath
ExitCamera2
PlayerExit3
ExitCameraTunnel
PlayerExit1Alt
$$PATH_LIST_END

$$MATCEN_LIST_START
Matcen34
Matcen5
Matcen12
$$MATCEN_LIST_END

$$GOAL_LIST_START
Keep Reactor 5 Alive
Keep Reactor 4 Alive
Keep Reactor 3 Alive
Keep Reactor 2 Alive
Keep Reactor 1 Alive
Defend Red Acropolis and Escape
Escape from Red Acropolis
Keep 3 of the 5 reactors alive
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL05StartLev.osf
VoxL05GeneralA.osf
VoxL05GeneralC.osf
VoxL05GeneralD.osf
VoxL05GeneralB.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:LevelStartInits
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCustomReactorDisplayInit
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:1:Activate/Deactivate
                        10:17:0:2:Matcen
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:30.000000:LowerLimit
                                10:6:45.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        10:6:0.000000:value
                        $$CHILD_BLOCK_END
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:12.000000:Time
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Update Reactor Display
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCustomReactorDisplayUpdate
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Send Matcen12 Guy to Reactor
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
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:64:AIFlags
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.010000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:1024:AIFlags
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qRandomChance:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:9:0.500000:Probability
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:0:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:1:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:5
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:2:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:5
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:1:0:0:Target
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:0:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:1:Object
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAISetTarget
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:1:0:1:Target
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:1:Path
                                        10:15:4352:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aAISetTarget
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:1:0:2:Target
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:2:Path
                                        10:15:4352:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Send Matcen34 Guy to Reactor
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
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:64:AIFlags
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.010000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:1024:AIFlags
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:1
                                $$CHILD_BLOCK_START
                                09:0
                                        $$CHILD_BLOCK_START
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qRandomChance:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:9:0.500000:Probability
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qObjShields:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:0:3:Object
                                                        $$CHILD_BLOCK_END
                                                07:1:2
                                                10:6:0.000000:Literal
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:2:Object
                                                $$CHILD_BLOCK_END
                                        07:1:5
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:1:0:3:Target
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:3:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:1:0:2:Target
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:4:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:-1:GoalID
                                10:10:0:0:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Send Matcen5 Guy to Reactor
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
                08:aAISetFOV
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:6:360.000000:FOV
                        $$CHILD_BLOCK_END
                08:aAIFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:64:AIFlags
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qRandomChance:Bool
                                        $$CHILD_BLOCK_START
                                        10:9:0.010000:Probability
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAIFlags
                                $$CHILD_BLOCK_START
                                10:10:0:0:Set/Clear
                                10:15:1024:AIFlags
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:0:4:Object
                                        $$CHILD_BLOCK_END
                                07:1:2
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aAISetTarget
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:1:0:4:Target
                                $$CHILD_BLOCK_END
                        08:aAIGoalFollowPathSimple
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                10:16:5:Path
                                10:15:4352:AIGoalFlags
                                10:10:0:0:GoalID
                                10:10:0:3:GoalPriority
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjShields:Float
                                                $$CHILD_BLOCK_START
                                                10:1:0:3:Object
                                                $$CHILD_BLOCK_END
                                        07:1:2
                                        10:6:0.000000:Literal
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aAISetTarget
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:1:0:3:Target
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:6:Path
                                        10:15:4352:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aAISetTarget
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:1:0:1:Target
                                        $$CHILD_BLOCK_END
                                08:aAIGoalFollowPathSimple
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:16:7:Path
                                        10:15:4352:AIGoalFlags
                                        10:10:0:-1:GoalID
                                        10:10:0:0:GoalPriority
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:StartIntroMovie
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
                        10:16:8:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:5:TotallyNotUsedTarget
                        10:16:9:PlayerPath
                        10:6:10.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:GiveStartMessage
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:4:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:3:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:2:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:0:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:0:StartFrame
                        10:4:32:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:0:StartFrame
                        10:4:32:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:0:StartFrame
                        10:4:32:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:0:StartFrame
                        10:4:32:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:0:StartFrame
                        10:4:32:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:DefendThoseReactors2:GameMessage
                        10:8:IncomingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DefendReactorsShort:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:All Reactors are on
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:0:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:1:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:2:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:3:Object
                        $$CHILD_BLOCK_END
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:65536:Teams
                        10:1:0:4:Object
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:720.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aTimerShow
                        $$CHILD_BLOCK_START
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:2.000000:Time
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Reactor5Status75percent
        $$CHILD_BLOCK_START
        01:1:4
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:22500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor5Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health75:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:3:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Reactor4Status75percent
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:22500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor4Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health75:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:4:3:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Reactor3Status75percent
        $$CHILD_BLOCK_START
        01:1:2
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:22500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor3Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health75:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:4:3:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Reactor2Status75percent
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:22500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor2Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health75:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:3:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Reactor1Status75percent
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:22500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor1Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health75:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:4:3:FaceNum
                        10:14:0:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Reactor5Status50percent
        $$CHILD_BLOCK_START
        01:1:4
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:15000.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor5Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health50:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:3:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Reactor4Status50percent
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:15000.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor4Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health50:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:4:3:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Reactor3Status50percent
        $$CHILD_BLOCK_START
        01:1:2
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:15000.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor3Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health50:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:4:3:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Reactor2Status50percent
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:15000.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor2Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health50:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:3:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Reactor1Status50percent
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:15000.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor1Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:255:Green
                        10:4:0:Blue
                        10:8:Health50:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:4:3:FaceNum
                        10:14:1:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Reactor5Status25percent
        $$CHILD_BLOCK_START
        01:1:4
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:7500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor5Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Health25:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:3:FaceNum
                        10:14:2:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Reactor4Status25percent
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:7500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor4Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Health25:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:4:3:FaceNum
                        10:14:2:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:Reactor3Status25percent
        $$CHILD_BLOCK_START
        01:1:2
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:7500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor3Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Health25:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:4:3:FaceNum
                        10:14:2:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Reactor2Status25percent
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:7500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor2Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Health25:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:3:FaceNum
                        10:14:2:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Reactor1Status25percent
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qObjShields:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:6:7500.000000:Literal
                                $$CHILD_BLOCK_END
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor1Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Health25:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:4:3:FaceNum
                        10:14:2:Texture
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:Reactor5StatusDestroyed
        $$CHILD_BLOCK_START
        01:1:4
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor5Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Destroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        $$CHILD_BLOCK_END
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
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:5:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:0:Room
                        10:4:3:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:Reactor4StatusDestroyed
        $$CHILD_BLOCK_START
        01:1:3
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor4Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Destroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        $$CHILD_BLOCK_END
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
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:6:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:1:Room
                        10:4:3:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Reactor3StatusDestroyed
        $$CHILD_BLOCK_START
        01:1:2
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor3Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Destroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        $$CHILD_BLOCK_END
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
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:7:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:2:Room
                        10:4:3:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:2:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Reactor2StatusDestroyed
        $$CHILD_BLOCK_START
        01:1:1
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor2Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Destroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        $$CHILD_BLOCK_END
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
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:8:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:4:3:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Reactor1StatusDestroyed
        $$CHILD_BLOCK_START
        01:1:0
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:0
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAISetTeam
                        $$CHILD_BLOCK_START
                        10:10:0:196608:Teams
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:Reactor1Status:Message
                        $$CHILD_BLOCK_END
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:Destroyed:Message
                        $$CHILD_BLOCK_END
                08:aUserVarInc
                        $$CHILD_BLOCK_START
                        10:10:0:1:UserVar
                        $$CHILD_BLOCK_END
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
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:9:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFaceTexture
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:4:3:FaceNum
                        10:14:3:Texture
                        $$CHILD_BLOCK_END
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Debug Script for Reactor 1
        $$CHILD_BLOCK_START
        01:1:4
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        10:5:0:Literal
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessageF
                        $$CHILD_BLOCK_START
                        10:8:HITPOINTS:Message
                        06:qObjShields:Float
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Exit Sequence Part 2
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:10:CameraPath
                        10:16:11:PlayerPath
                        10:6:9.000000:Time
                        10:8:BLANK:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:ExitCameraSequence
        $$CHILD_BLOCK_START
        01:0:0
        02:1
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:5:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:12:CameraPath
                        10:8:BLANK:Text
                        10:1:0:6:TotallyNotUsedTarget
                        10:16:13:PlayerPath
                        10:6:6.500000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:FlamesTest
        $$CHILD_BLOCK_START
        01:0:0
        02:1
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:-1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:11:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        10:4:-1:GunNum
                        10:10:0:4:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:4:-1:GunNum
                        10:10:0:3:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:4.000000:BlobLifetime
                        10:6:0.150000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:15.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:3 Reactors Dead
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:4
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:69:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:OOPS:GameMessage
                        10:8:IncomingMessage:HUDMessage
                        $$CHILD_BLOCK_END
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:RestartLevel
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aFailLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:ReactorsLive
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:7:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:0:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:1:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:18:0:4:LevelGoal
                        $$CHILD_BLOCK_END
                08:aAddGameMessage
                        $$CHILD_BLOCK_START
                        10:8:WereGettinOut:GameMessage
                        10:8:IncomingMessage:HUDMessage
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
                        10:8:SelfDestruct:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:ReactorAlive-5
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalFailed:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:0:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:ReactorAlive-4
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalFailed:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:1:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:ReactorAlive-3
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalFailed:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:ReactorAlive-2
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalFailed:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:3:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:ReactorAlive-1
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:3
                                10:4:3:Integer
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalFailed:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:4:LevelGoal
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:ExitDoorMessage
        $$CHILD_BLOCK_START
        01:1:14
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
                        10:8:ExitOnly:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:EntranceDoorMessage
        $$CHILD_BLOCK_START
        01:1:5
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
                        10:8:EntranceDoorMessage:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlay2DObj
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:1:-1:PlayerObject
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:30Seconds Left
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValue:Float
                                        $$CHILD_BLOCK_START
                                        10:10:0:8:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:0.000000:Literal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:30SecondsLeft:Message
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aTimerShow
                        $$CHILD_BLOCK_START
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Exit clock goes off
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
                                10:10:0:3:TimerID
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aFadeWhiteAndEndlevel
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:8:BLANK:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:IntoTunnel1
        $$CHILD_BLOCK_START
        01:0:1
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
                08:DO NOTHING
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Music-Intro
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
00:42:Music-MainHub1
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
00:43:Music-MainHub2
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
00:45:Music-MainHub3
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
00:44:Music-MainHub4
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
00:46:Music-MainHub5
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Music-enter Tunnel1
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
00:48:Music-enter Tunnel2
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
00:49:Music-enter Tunnel3
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
00:50:Music-enter Tunnel4
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Music-enter Tunnel5
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
00:52:Music-Tunnel1 from Reactor1
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
00:53:Music-Tunnel2 from Reactor2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Music-Tunnel3 from Reactor3
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
00:55:Music-Tunnel4 from Reactor4
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
00:56:Music-Tunnel5 from Reactor5
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
00:57:Reactor1
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Reactor2
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:Reactor3
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Reactor4
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Reactor5
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Enter reactor 4 from maintenance tube
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
00:63:Enter reactor 3 from maintenance tube
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
00:64:Leave reactor 3 into maintenance tube
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
00:65:Leave reactor 4 into maintenance tube
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:68:Random Level Shake
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
                        05:2
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:11:ScriptID
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:0:Bool
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:30.000000:LowerLimit
                                10:6:45.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:70.000000:LowerLimit
                                10:6:100.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aUserVarSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserVar
                        06:qRandomValue:value
                                $$CHILD_BLOCK_START
                                10:6:1.000000:LowerLimit
                                10:6:5.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserVarValueInt:Integer
                                        $$CHILD_BLOCK_START
                                        10:10:0:7:UserVar
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:4:1:Integer
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSoundPlay2D
                                $$CHILD_BLOCK_START
                                10:12:5:Sound
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserVarValueInt:Integer
                                                $$CHILD_BLOCK_START
                                                10:10:0:7:UserVar
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:4:2:Integer
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aSoundPlay2D
                                        $$CHILD_BLOCK_START
                                        10:12:6:Sound
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                03:1
                                        $$CHILD_BLOCK_START
                                        05:2
                                                $$CHILD_BLOCK_START
                                                06:qUserVarValueInt:Integer
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:7:UserVar
                                                        $$CHILD_BLOCK_END
                                                07:1:0
                                                10:4:3:Integer
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:0
                                        $$CHILD_BLOCK_START
                                        08:aSoundPlay2D
                                                $$CHILD_BLOCK_START
                                                10:12:7:Sound
                                                10:9:1.000000:Volume
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                04:1:0:1
                                        $$CHILD_BLOCK_START
                                        03:1
                                                $$CHILD_BLOCK_START
                                                05:2
                                                        $$CHILD_BLOCK_START
                                                        06:qUserVarValueInt:Integer
                                                                $$CHILD_BLOCK_START
                                                                10:10:0:7:UserVar
                                                                $$CHILD_BLOCK_END
                                                        07:1:0
                                                        10:4:4:Integer
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:0
                                                $$CHILD_BLOCK_START
                                                08:aSoundPlay2D
                                                        $$CHILD_BLOCK_START
                                                        10:12:8:Sound
                                                        10:9:1.000000:Volume
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        04:1:0:1
                                                $$CHILD_BLOCK_START
                                                08:aSoundPlay2D
                                                        $$CHILD_BLOCK_START
                                                        10:12:9:Sound
                                                        10:9:1.000000:Volume
                                                        $$CHILD_BLOCK_END
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:First Voice Message
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Second General Voice
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Time
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:Second General Voice Part 2
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:1:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:180.000000:Time
                        10:10:0:9:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:Third VO shuttle C
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:10.000000:Time
                        10:10:0:10:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:89:Fourth VO shuttle C response
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:3:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Time
                        10:10:0:11:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Fifth VO shuttle C response
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
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:4:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
