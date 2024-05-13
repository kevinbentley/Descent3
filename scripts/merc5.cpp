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
// Filename:	Merc5.cpp
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

#define ID_CUSTOM_OBJECT_11C4 0x001
#define ID_CUSTOM_OBJECT_1088 0x002
#define ID_CUSTOM_OBJECT_09C6 0x003
#define ID_CUSTOM_OBJECT_11C5 0x004
#define ID_CUSTOM_OBJECT_09C7 0x005
#define ID_CUSTOM_OBJECT_182E 0x006
#define ID_CUSTOM_OBJECT_0A05 0x007
#define ID_CUSTOM_OBJECT_0A04 0x008
#define ID_CUSTOM_OBJECT_0A03 0x009
#define ID_CUSTOM_OBJECT_1A02 0x00a
#define ID_CUSTOM_OBJECT_1033 0x00b
#define ID_CUSTOM_OBJECT_1200 0x00c
#define ID_CUSTOM_OBJECT_1036 0x00d
#define ID_CUSTOM_OBJECT_1035 0x00e
#define ID_CUSTOM_OBJECT_3032 0x00f
#define ID_CUSTOM_OBJECT_1830 0x010
#define ID_CUSTOM_OBJECT_28A2 0x011
#define ID_CUSTOM_OBJECT_0A06 0x012
#define ID_CUSTOM_OBJECT_2885 0x013
#define ID_CUSTOM_OBJECT_107E 0x014
#define ID_CUSTOM_OBJECT_1185 0x015
#define ID_CUSTOM_OBJECT_21B2 0x016
#define ID_CUSTOM_OBJECT_09DE 0x017
#define ID_CUSTOM_OBJECT_09DD 0x018
#define ID_CUSTOM_OBJECT_09DC 0x019
#define ID_CUSTOM_OBJECT_21DA 0x01a
#define ID_CUSTOM_OBJECT_0899 0x01b
#define ID_CUSTOM_OBJECT_089A 0x01c
#define ID_CUSTOM_OBJECT_089B 0x01d
#define ID_CUSTOM_OBJECT_1098 0x01e
#define ID_CUSTOM_OBJECT_09A1 0x01f
#define ID_CUSTOM_OBJECT_19A0 0x020
#define ID_CUSTOM_OBJECT_09C9 0x021
#define ID_CUSTOM_OBJECT_1007 0x022
#define ID_CUSTOM_OBJECT_1016 0x023

#define ID_TRIGGER_000F 0x024
#define ID_TRIGGER_0000 0x025
#define ID_TRIGGER_0010 0x026
#define ID_TRIGGER_000E 0x027
#define ID_TRIGGER_000D 0x028
#define ID_TRIGGER_000B 0x029
#define ID_TRIGGER_0009 0x02a
#define ID_TRIGGER_000C 0x02b
#define ID_TRIGGER_000A 0x02c
#define ID_TRIGGER_0007 0x02d
#define ID_TRIGGER_0008 0x02e

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

class CustomObjectScript_11C4 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1088 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C6 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_11C5 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C7 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_182E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A05 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A04 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A03 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1A02 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1033 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1200 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1036 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1035 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3032 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1830 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_28A2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0A06 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2885 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_107E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1185 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_21B2 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09DE : public BaseScript {
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

class CustomObjectScript_21DA : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0899 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_089A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_089B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1098 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09A1 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_19A0 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_09C9 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1016 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
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

class TriggerScript_000D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
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

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

static int ScriptActionCtr_000 = 0;
static int ScriptActionCtr_005 = 0;
static int ScriptActionCtr_012 = 0;
static int ScriptActionCtr_010 = 0;
static int ScriptActionCtr_017 = 0;
static int ScriptActionCtr_040 = 0;
static int ScriptActionCtr_042 = 0;
static int ScriptActionCtr_043 = 0;
static int ScriptActionCtr_072 = 0;
static int ScriptActionCtr_073 = 0;
static int ScriptActionCtr_077 = 0;
static int ScriptActionCtr_074 = 0;
static int ScriptActionCtr_075 = 0;
static int ScriptActionCtr_076 = 0;
static int ScriptActionCtr_001 = 0;
static int ScriptActionCtr_002 = 0;
static int ScriptActionCtr_008 = 0;
static int ScriptActionCtr_003 = 0;
static int ScriptActionCtr_029 = 0;
static int ScriptActionCtr_004 = 0;
static int ScriptActionCtr_030 = 0;
static int ScriptActionCtr_031 = 0;
static int ScriptActionCtr_033 = 0;
static int ScriptActionCtr_032 = 0;
static int ScriptActionCtr_024 = 0;
static int ScriptActionCtr_006 = 0;
static int ScriptActionCtr_058 = 0;
static int ScriptActionCtr_057 = 0;
static int ScriptActionCtr_048 = 0;
static int ScriptActionCtr_046 = 0;
static int ScriptActionCtr_045 = 0;
static int ScriptActionCtr_044 = 0;
static int ScriptActionCtr_007 = 0;
static int ScriptActionCtr_047 = 0;
static int ScriptActionCtr_037 = 0;
static int ScriptActionCtr_060 = 0;
static int ScriptActionCtr_078 = 0;
static int ScriptActionCtr_059 = 0;
static int ScriptActionCtr_013 = 0;
static int ScriptActionCtr_014 = 0;
static int ScriptActionCtr_036 = 0;
static int ScriptActionCtr_050 = 0;
static int ScriptActionCtr_018 = 0;
static int ScriptActionCtr_051 = 0;
static int ScriptActionCtr_022 = 0;
static int ScriptActionCtr_009 = 0;
static int ScriptActionCtr_011 = 0;
static int ScriptActionCtr_016 = 0;
static int ScriptActionCtr_021 = 0;
static int ScriptActionCtr_023 = 0;
static int ScriptActionCtr_041 = 0;
static int ScriptActionCtr_049 = 0;
static int ScriptActionCtr_028 = 0;
static int ScriptActionCtr_084 = 0;
static int ScriptActionCtr_083 = 0;
static int ScriptActionCtr_082 = 0;
static int ScriptActionCtr_019 = 0;
static int ScriptActionCtr_081 = 0;
static int ScriptActionCtr_080 = 0;
static int ScriptActionCtr_079 = 0;
static int ScriptActionCtr_020 = 0;
static int ScriptActionCtr_088 = 0;
static int ScriptActionCtr_087 = 0;
static int ScriptActionCtr_085 = 0;
static int ScriptActionCtr_086 = 0;
static int ScriptActionCtr_025 = 0;
static int ScriptActionCtr_027 = 0;
static int ScriptActionCtr_026 = 0;
static int ScriptActionCtr_038 = 0;
static int ScriptActionCtr_034 = 0;
static int ScriptActionCtr_035 = 0;
static int ScriptActionCtr_039 = 0;
static int ScriptActionCtr_054 = 0;
static int ScriptActionCtr_063 = 0;
static int ScriptActionCtr_071 = 0;
static int ScriptActionCtr_070 = 0;
static int ScriptActionCtr_069 = 0;
static int ScriptActionCtr_068 = 0;
static int ScriptActionCtr_067 = 0;
static int ScriptActionCtr_066 = 0;
static int ScriptActionCtr_065 = 0;
static int ScriptActionCtr_064 = 0;
static int ScriptActionCtr_015 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_043 = 0;
  ScriptActionCtr_072 = 0;
  ScriptActionCtr_073 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_074 = 0;
  ScriptActionCtr_075 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_057 = 0;
  ScriptActionCtr_048 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_049 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_088 = 0;
  ScriptActionCtr_087 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_086 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_035 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_054 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_071 = 0;
  ScriptActionCtr_070 = 0;
  ScriptActionCtr_069 = 0;
  ScriptActionCtr_068 = 0;
  ScriptActionCtr_067 = 0;
  ScriptActionCtr_066 = 0;
  ScriptActionCtr_065 = 0;
  ScriptActionCtr_064 = 0;
  ScriptActionCtr_015 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_043, file_ptr);
  File_WriteInt(ScriptActionCtr_072, file_ptr);
  File_WriteInt(ScriptActionCtr_073, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_074, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_057, file_ptr);
  File_WriteInt(ScriptActionCtr_048, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_049, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_088, file_ptr);
  File_WriteInt(ScriptActionCtr_087, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_086, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_054, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_071, file_ptr);
  File_WriteInt(ScriptActionCtr_070, file_ptr);
  File_WriteInt(ScriptActionCtr_069, file_ptr);
  File_WriteInt(ScriptActionCtr_068, file_ptr);
  File_WriteInt(ScriptActionCtr_067, file_ptr);
  File_WriteInt(ScriptActionCtr_066, file_ptr);
  File_WriteInt(ScriptActionCtr_065, file_ptr);
  File_WriteInt(ScriptActionCtr_064, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_043 = File_ReadInt(file_ptr);
  ScriptActionCtr_072 = File_ReadInt(file_ptr);
  ScriptActionCtr_073 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_074 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_057 = File_ReadInt(file_ptr);
  ScriptActionCtr_048 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_049 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_088 = File_ReadInt(file_ptr);
  ScriptActionCtr_087 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_086 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_054 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_071 = File_ReadInt(file_ptr);
  ScriptActionCtr_070 = File_ReadInt(file_ptr);
  ScriptActionCtr_069 = File_ReadInt(file_ptr);
  ScriptActionCtr_068 = File_ReadInt(file_ptr);
  ScriptActionCtr_067 = File_ReadInt(file_ptr);
  ScriptActionCtr_066 = File_ReadInt(file_ptr);
  ScriptActionCtr_065 = File_ReadInt(file_ptr);
  ScriptActionCtr_064 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
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
2:Temple
3:Level3
4:Level2
5:Level1
$$END
*/

// Got from Nate

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

#define N_REGIONS 2
const char *RegionList[N_REGIONS] = {"LeftLabR", "RightLabR"};

int level_custom_timer_id = 0;

/*
$$ENUM LevelRegion
0:LeftLab
1:RightLab
$$END
*/

/*
$$ACTION
Custom
Set fog in region [e:LevelRegion] to color = [f:Red=0.5],[f:Green=0.5],[f:Blue=0.5], depth = [f:Depth=500.0]
cFogRegion
Set region fog
  Sets the fog color and depth for a predefined region

Parameters:
  Region: the region to set
  R,G,B: the fog color (0-1)
  Depth:  how deep the fog should be
$$END
*/

void cFogRegion(int region, float r, float g, float b, float depth) {
  //	iterate through all room names starting with region string and set fog region
  int i = 0, ri;

  do {
    char room_name[32];

    snprintf(room_name, sizeof(room_name), "%s%c", RegionList[region], (i <= 9) ? (char)('0' + i) : ('A' + i - 10));
    ri = Scrpt_FindRoomName(room_name);
    if (ri >= 0) {
      aRoomSetFog(ri, r, g, b, depth);
    }
    i++;
  } while (i < 36);
}

/*
$$ACTION
Custom
Change fog in region [e:LevelRegion] to color = [f:Red=0.5],[f:Green=0.5],[f:Blue=0.5], depth = [f:Depth=200.0] over
[f:Time=20.0] seconds cChangeFogRegion Change region fog over time Changes the fog of a predefined region to a color
over a time period

Parameters:
  Region: the region to change
  R,G,B: the fog color (0-1)
  Depth: hoe deep the fog should be.
$$END
*/

void cChangeFogRegion(int region, float r, float g, float b, float depth, float time) {
  //	iterate through all room names starting with region string and set fog region
  int i = 0, ri;

  do {
    char room_name[32];

    snprintf(room_name, sizeof(room_name), "%s%c", RegionList[region], (i <= 9) ? (char)('0' + i) : ('A' + i - 10));
    ri = Scrpt_FindRoomName(room_name);
    if (ri >= 0) {
      aRoomChangeFog(ri, r, g, b, depth, time);
    }
    i++;
  } while (i < 36);
}

/*
$$ACTION
Custom
Turn [e:On/Off] Flicker in region [e:LevelRegion]
cRegionSetLightingFlicker
Turn On/Off flicker in region
  Turns on or off the light flicker in a predefined region

Parameters:
  On/Off: whether the flicker should be on or off
  Region: the region to set
$$END
*/

void cRegionSetLightingFlicker(int state, int region) {
  int i = 0, ri;

  do {
    char room_name[32];

    snprintf(room_name, sizeof(room_name), "%s%c", RegionList[region], (i <= 9) ? (char)('0' + i) : ('A' + i - 10));
    ri = Scrpt_FindRoomName(room_name);
    if (ri >= 0) {
      aRoomSetLightingFlicker(state, ri);
    }
    i++;
  } while (i < 36);
}

/*
$$ACTION
Custom
Malfunction doors in region [e:LevelRegion]
cMalfunctionRegionDoors
Malfunction doors in region.
        Causes doors in region to do some random freakout behavior

Parameters:
  Region: the region to set
$$END
*/
#define N_DOORS_PER_REGION 8
static const char *const Region_door_names[N_REGIONS][N_DOORS_PER_REGION] = {{
                                                                                 "Door-Left01",
                                                                                 "Door-Left02",
                                                                                 "Door-Left12",
                                                                                 "Door-Left11",
                                                                                 "Door-Left21",
                                                                                 "Door-Left22",
                                                                                 "End",
                                                                             },
                                                                             {
                                                                                 "Door-Right01",
                                                                                 "Door-Right02",
                                                                                 "Door-Right12",
                                                                                 "Door-Right11",
                                                                                 "Door-Right21",
                                                                                 "Door-Right22",
                                                                                 "End",
                                                                             }};

void cMalfunctionRegionDoors(int region) {
  int i;

  i = 0;
  while (strcmp(Region_door_names[region][i], "End") != 0) {
    int rnum = rand() % 100;
    if (rnum < 50) {
      int doorref = Scrpt_FindDoorName(Region_door_names[region][i]);
      if (doorref != OBJECT_HANDLE_NONE) {
        if (rnum >= 30 && rnum < 50) {
          aDoorActivate(doorref);
        } else if (rnum >= 10 && rnum < 30) {
          rnum = rand() % 20;
          aDoorSetPos(doorref, 0.55f + (rnum * 0.01f));
        } else {
          aDoorStop(doorref);
        }
      }
    }
    i++;
  }
}

/*
$$ACTION
Custom
Timed breaking of glass in room [r:Room], portal [i:PortalNum=0] in [f:Seconds=0.0]
cTimeGlassBreak
Delay breaking glass for a room
        Delays breaking glass for specified time in a specified room.

Parameters:
        Room: room to break glass
        PortalNum: portal number of glass
        Seconds: Time
$$END
*/

static uint8_t breaking_glass_index = 0;
static struct t_breaking_glass_data {
  int16_t room_number;
  int16_t portal_num;
} breaking_glass_data[64];

#define SPECIAL_TIMER_ID_BASE 1000
#define SPECIAL_TIMER_CLASSES 4
#define SPECIAL_TIMER_MAX 256
#define SPECIAL_TIMER_ID_LIMIT (SPECIAL_TIMER_ID_BASE + SPECIAL_TIMER_MAX * SPECIAL_TIMER_CLASSES - 1)

static inline int LEVEL_TIMER_UID(uint8_t timer_class, uint8_t index) {
  return (SPECIAL_TIMER_ID_BASE + (timer_class % SPECIAL_TIMER_CLASSES) * SPECIAL_TIMER_MAX + index);
}

void cTimeGlassBreak(int room_number, int portal_num, float time) {
  if (breaking_glass_index >= 64)
    breaking_glass_index = 0;
  breaking_glass_data[breaking_glass_index].room_number = room_number;
  breaking_glass_data[breaking_glass_index].portal_num = portal_num;
  aSetLevelTimer(time, LEVEL_TIMER_UID(0, breaking_glass_index++));
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
    if (index < 64 && index >= 0) {
      aPortalBreakGlass(breaking_glass_data[index].portal_num, breaking_glass_data[index].room_number);
    }
    break;
  }
}

// Tell the code to call our functions
#define ENABLE_CUSTOM_SAVE_AND_RESTORE

// Save custom data for this script
void dsCustomSave(void *fileptr) {}

// Restore custom data for this script
void dsCustomRestore(void *fileptr) {}

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
static const char *const Door_names[NUM_DOOR_NAMES] = {"Door-Top1", "Door-Escape"};
static int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 175
static const char *const Object_names[NUM_OBJECT_NAMES] = {"ReceptorNode-01",
                                                           "ReceptorNode-02",
                                                           "ReceptorNode-03",
                                                           "ReceptorNode-04",
                                                           "PowerNode-01",
                                                           "PowerNode-02",
                                                           "PowerNode-03",
                                                           "PowerNode-04",
                                                           "PSGadget0",
                                                           "PSGadget1",
                                                           "Virus Device",
                                                           "PlayerIntroCamera",
                                                           "Virus Device2",
                                                           "BigBoulder",
                                                           "RockWallBoulder",
                                                           "Drop2",
                                                           "TargetExt1",
                                                           "IntroSpark-1",
                                                           "IGIntro2",
                                                           "IntroSmoke2",
                                                           "IntroSmoke1",
                                                           "TargetInt2",
                                                           "IntroSmoke-4",
                                                           "IntroSmoke-3",
                                                           "TargetInt1",
                                                           "Drop1",
                                                           "TargetExt2",
                                                           "BoulderExplosion1",
                                                           "BoulderExplosion2",
                                                           "BHit1",
                                                           "Bhit3",
                                                           "BHit2",
                                                           "FlasherCrystal",
                                                           "CrystalBar1",
                                                           "CrystalBar2",
                                                           "CrystralBar3",
                                                           "CrystalBar4",
                                                           "CrystalBarCenter",
                                                           "CrystalCenter4",
                                                           "CrystalCenter3",
                                                           "CrystalCenter2",
                                                           "CrystalCenter1",
                                                           "BTSmoke3",
                                                           "BTLight",
                                                           "BTSmoke5",
                                                           "BTSmoke4",
                                                           "BTSmoke1",
                                                           "BTSmoke2",
                                                           "CrystalMainTarget",
                                                           "CFX5",
                                                           "CFX4",
                                                           "CFX3",
                                                           "CFX2",
                                                           "CFX1",
                                                           "CBCHit1",
                                                           "CBCHit2",
                                                           "CBCHit6",
                                                           "CBCHit5",
                                                           "CBCHit4",
                                                           "CBCHit3",
                                                           "CrystalCenterBeam",
                                                           "MidBot5",
                                                           "MidBot4",
                                                           "MidBot3",
                                                           "MidBot2",
                                                           "MidBot1",
                                                           "HiBot4",
                                                           "HiBot3",
                                                           "HiBot2",
                                                           "HiBot1",
                                                           "LoBot6",
                                                           "LoBot5",
                                                           "LoBot4",
                                                           "LoBot3",
                                                           "LoBot2",
                                                           "LoBot1",
                                                           "RightTopInter",
                                                           "RightHubBeam",
                                                           "LeftTopInterface",
                                                           "LeftHubBeam",
                                                           "LeftVirusTerminal",
                                                           "RightVirusTerminal",
                                                           "DataArmLeftHub",
                                                           "LeftBottomInterfac",
                                                           "TopDoorSmoke2",
                                                           "LeftTurret-3",
                                                           "LeftTurret-2",
                                                           "LeftTurret-5",
                                                           "LeftTurret-6",
                                                           "LeftTurret-7",
                                                           "LeftTurret-9",
                                                           "LeftTurret-A",
                                                           "LeftTurret-B",
                                                           "LeftTurret-E",
                                                           "LeftTurret-J",
                                                           "LeftTurret-H",
                                                           "LeftTurret-I",
                                                           "LeftTurret-C",
                                                           "SmokeHub2",
                                                           "SmokeHub1",
                                                           "LeftLabHalonSpew0",
                                                           "LeftLabHalonSpew1",
                                                           "LeftLabHalonSpew2",
                                                           "LeftLabHalonSpew3",
                                                           "LeftLabHalonSpew4",
                                                           "LeftLabHalonSpew5",
                                                           "LeftLabHalonSpew6",
                                                           "LeftLabHalonSpew7",
                                                           "LeftLabHalonSpew8",
                                                           "LeftLabHalonSpew9",
                                                           "LeftLabHalonSpewA",
                                                           "RightDataArm",
                                                           "RightBottomInter",
                                                           "TDSmoke1",
                                                           "RightTurret-1",
                                                           "RightTurret-2",
                                                           "RightTurret-3",
                                                           "RightTurret-5",
                                                           "RightTurret-6",
                                                           "RightTurret-7",
                                                           "RightTurret-8",
                                                           "RightTurret-9",
                                                           "RightTurret-B",
                                                           "RightTurret-C",
                                                           "RightTurret-D",
                                                           "SmokeRight2",
                                                           "SmokeRight1",
                                                           "RightLabHalonSpew0",
                                                           "RightLabHalonSpew1",
                                                           "RightLabHalonSpew2",
                                                           "RightLabHalonSpew3",
                                                           "EightLabHalonSpew4",
                                                           "RightLabHalonSpew5",
                                                           "RightLabHalonSpew6",
                                                           "RightLabHalonSpew7",
                                                           "RightLabHalonSpew9",
                                                           "RightLabHalonSpewA",
                                                           "RightLabHalonSpewB",
                                                           "RightLabHalonSpewC",
                                                           "PowerBackup-04",
                                                           "PowerBackup-03",
                                                           "PowerBackup-02",
                                                           "PowerBackup-01",
                                                           "PNodeSmoker4",
                                                           "PNodeSmoker3",
                                                           "PNodeSmoker2",
                                                           "PNodeSmoker1",
                                                           "MainPowerBeam2",
                                                           "MainBeamTarget2",
                                                           "MainBeamTarget1",
                                                           "MainPowerBeam1",
                                                           "RecSwitch4",
                                                           "RecSwitch3",
                                                           "RecSwitch2",
                                                           "RecSwitch1",
                                                           "ReBootSwitch2",
                                                           "ReBootSwitch1",
                                                           "MainPowerWhite1",
                                                           "MainPowerWhite2",
                                                           "PT1",
                                                           "PT2",
                                                           "PT3",
                                                           "PT4",
                                                           "TargetExit1",
                                                           "Door-Escape",
                                                           "ExitSmoke1",
                                                           "ExitSmoke3",
                                                           "ExitSmoke4",
                                                           "ExitSmoke2",
                                                           "Drop2Smoke2",
                                                           "Drop2Smoke1",
                                                           "Turret-Outer13",
                                                           "Turret-Outer12",
                                                           "Turret-Outer11",
                                                           "Door-Bottom2"};
static int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 50
static const char *const Room_names[NUM_ROOM_NAMES] = {
    "Creeper-Mid0",   "Creeper-Mid0A",     "Creeper-Mid0B", "Creeper-Mid0C", "Creeper-Mid0D", "LeftLabRO",
    "Creeper-LLR0A",  "Creeper-LLR0B",     "Creeper-LLR0C", "Creeper-LLR0D", "Creeper-LLR0E", "Creeper-LLROF",
    "Creeper-Mid2",   "Creeper-Mid2A",     "RightLabR3",    "Creeper-RL3-A", "Creeper-RL3-B", "Creeper-RL3-C",
    "Creeper-RL3-D",  "RightLabRJ",        "Creeper-RLJ-A", "Creeper-RLJ-B", "Creeper-RLJ-C", "Creeper-RLJ-D",
    "Creeper-RLJ-E",  "Creeper-RLJ-F",     "Creeper-RLJ-G", "Creeper-RLJ-H", "Creeper-Mid1",  "Creeper-Mid1A",
    "BoulderHitRoom", "CrystalCenterRoom", "NRGCreep",      "LeftLabCreep1", "LeftLabCreep0", "LeftX1",
    "PowerChute2",    "PowerLow8",         "PowerLow7",     "PowerLow6",     "PowerLow5",     "PowerLow4",
    "PowerLow3",      "PowerLow2",         "PowerLow1",     "PowerChute",    "PowerSide2",    "PowerDoor",
    "PowerSide1",     "PowerStation"};
static int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 11
static const char *const Trigger_names[NUM_TRIGGER_NAMES] = {
    "RollingBallWatchout", "RollingBallDetonate", "BeginEndSequence", "MusicLevel1-1", "MusicLevel2-2", "MusicLevel2-1",
    "MusicLevel3-2",       "MusicLevel3-1",       "MusicTemple-2",    "MusicTemple-1", "MusicOutside-1"};
static int Trigger_indexes[NUM_TRIGGER_NAMES];
static int Trigger_faces[NUM_TRIGGER_NAMES];
static int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 11
static const char *const Sound_names[NUM_SOUND_NAMES] = {
    "AmbExplosionFarB",   "RockBreakAway", "WpnEMDFireD",   "AmbSteamHigh", "AmbSirenBRedAcrop", "ExpMissileLarge1",
    "WpnPyroGLOmegaFire", "AmbSwitch21",   "Wall fade ???", "AmbSwitch31",  "AmbSwitch11"};
static int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 5
static const char *const Texture_names[NUM_TEXTURE_NAMES] = {"FunkyEffectGreen", "FunkyEffect3", "HellionBeam",
                                                             "FunkyEffect1", "FunkyEffectAntiV"};
static int Texture_indexes[NUM_TEXTURE_NAMES];

#define NUM_PATH_NAMES 14
static const char *const Path_names[NUM_PATH_NAMES] = {
    "PSGadget0Path", "PSGadget1Path", "IntroCam-Ext1", "IGInt2",    "IntroCam-Int2", "IntroCam-Int1", "IntroCam-Ext2",
    "MidPatrol1",    "LowPatrol2",    "LowPatrol1",    "ExitCam-1", "ExitShip-1",    "ExitCam-2",     "ExitShip-2"};
static int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 0
static const char **Matcen_names = NULL;
static int *Matcen_indexes = NULL;

#define NUM_GOAL_NAMES 7
static const char *const Goal_names[NUM_GOAL_NAMES] = {
    "Blast Into the Laboratory",       "Infect Computer Hub Delta",
    "Infect Computer Hub Gamma",       "Reboot the System",
    "Shut Down the Main Power",        "Infect the Lab System With Virus Data",
    "Escape Before the System Reboots"};
static int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 16
static const char *const Message_names[NUM_MESSAGE_NAMES] = {
    "VirusDeviceName",    "IntroMessage",      "EmptyMessage",    "Watchout",
    "LeftLabInitData",    "LeftLabInfected",   "LeftLabNotReady", "RightLabInfected",
    "LeftLabVirusPlaced", "VirusInfectFail",   "GetToPower",      "RechargeSucceed",
    "RechargeFail",       "DeactivateSucceed", "DeactivateFail",  "10Seconds"};
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
    strcpy(filename, "Merc5.msg");
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
  case ID_CUSTOM_OBJECT_11C4:
    return new CustomObjectScript_11C4;
    break;
  case ID_CUSTOM_OBJECT_1088:
    return new CustomObjectScript_1088;
    break;
  case ID_CUSTOM_OBJECT_09C6:
    return new CustomObjectScript_09C6;
    break;
  case ID_CUSTOM_OBJECT_11C5:
    return new CustomObjectScript_11C5;
    break;
  case ID_CUSTOM_OBJECT_09C7:
    return new CustomObjectScript_09C7;
    break;
  case ID_CUSTOM_OBJECT_182E:
    return new CustomObjectScript_182E;
    break;
  case ID_CUSTOM_OBJECT_0A05:
    return new CustomObjectScript_0A05;
    break;
  case ID_CUSTOM_OBJECT_0A04:
    return new CustomObjectScript_0A04;
    break;
  case ID_CUSTOM_OBJECT_0A03:
    return new CustomObjectScript_0A03;
    break;
  case ID_CUSTOM_OBJECT_1A02:
    return new CustomObjectScript_1A02;
    break;
  case ID_CUSTOM_OBJECT_1033:
    return new CustomObjectScript_1033;
    break;
  case ID_CUSTOM_OBJECT_1200:
    return new CustomObjectScript_1200;
    break;
  case ID_CUSTOM_OBJECT_1036:
    return new CustomObjectScript_1036;
    break;
  case ID_CUSTOM_OBJECT_1035:
    return new CustomObjectScript_1035;
    break;
  case ID_CUSTOM_OBJECT_3032:
    return new CustomObjectScript_3032;
    break;
  case ID_CUSTOM_OBJECT_1830:
    return new CustomObjectScript_1830;
    break;
  case ID_CUSTOM_OBJECT_28A2:
    return new CustomObjectScript_28A2;
    break;
  case ID_CUSTOM_OBJECT_0A06:
    return new CustomObjectScript_0A06;
    break;
  case ID_CUSTOM_OBJECT_2885:
    return new CustomObjectScript_2885;
    break;
  case ID_CUSTOM_OBJECT_107E:
    return new CustomObjectScript_107E;
    break;
  case ID_CUSTOM_OBJECT_1185:
    return new CustomObjectScript_1185;
    break;
  case ID_CUSTOM_OBJECT_21B2:
    return new CustomObjectScript_21B2;
    break;
  case ID_CUSTOM_OBJECT_09DE:
    return new CustomObjectScript_09DE;
    break;
  case ID_CUSTOM_OBJECT_09DD:
    return new CustomObjectScript_09DD;
    break;
  case ID_CUSTOM_OBJECT_09DC:
    return new CustomObjectScript_09DC;
    break;
  case ID_CUSTOM_OBJECT_21DA:
    return new CustomObjectScript_21DA;
    break;
  case ID_CUSTOM_OBJECT_0899:
    return new CustomObjectScript_0899;
    break;
  case ID_CUSTOM_OBJECT_089A:
    return new CustomObjectScript_089A;
    break;
  case ID_CUSTOM_OBJECT_089B:
    return new CustomObjectScript_089B;
    break;
  case ID_CUSTOM_OBJECT_1098:
    return new CustomObjectScript_1098;
    break;
  case ID_CUSTOM_OBJECT_09A1:
    return new CustomObjectScript_09A1;
    break;
  case ID_CUSTOM_OBJECT_19A0:
    return new CustomObjectScript_19A0;
    break;
  case ID_CUSTOM_OBJECT_09C9:
    return new CustomObjectScript_09C9;
    break;
  case ID_CUSTOM_OBJECT_1007:
    return new CustomObjectScript_1007;
    break;
  case ID_CUSTOM_OBJECT_1016:
    return new CustomObjectScript_1016;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_0000:
    return new TriggerScript_0000;
    break;
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_000E:
    return new TriggerScript_000E;
    break;
  case ID_TRIGGER_000D:
    return new TriggerScript_000D;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_000C:
    return new TriggerScript_000C;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
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
  case ID_CUSTOM_OBJECT_11C4:
    delete ((CustomObjectScript_11C4 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1088:
    delete ((CustomObjectScript_1088 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C6:
    delete ((CustomObjectScript_09C6 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_11C5:
    delete ((CustomObjectScript_11C5 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C7:
    delete ((CustomObjectScript_09C7 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_182E:
    delete ((CustomObjectScript_182E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A05:
    delete ((CustomObjectScript_0A05 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A04:
    delete ((CustomObjectScript_0A04 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A03:
    delete ((CustomObjectScript_0A03 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1A02:
    delete ((CustomObjectScript_1A02 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1033:
    delete ((CustomObjectScript_1033 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1200:
    delete ((CustomObjectScript_1200 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1036:
    delete ((CustomObjectScript_1036 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1035:
    delete ((CustomObjectScript_1035 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3032:
    delete ((CustomObjectScript_3032 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1830:
    delete ((CustomObjectScript_1830 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_28A2:
    delete ((CustomObjectScript_28A2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0A06:
    delete ((CustomObjectScript_0A06 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2885:
    delete ((CustomObjectScript_2885 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_107E:
    delete ((CustomObjectScript_107E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1185:
    delete ((CustomObjectScript_1185 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21B2:
    delete ((CustomObjectScript_21B2 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DE:
    delete ((CustomObjectScript_09DE *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DD:
    delete ((CustomObjectScript_09DD *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09DC:
    delete ((CustomObjectScript_09DC *)ptr);
    break;
  case ID_CUSTOM_OBJECT_21DA:
    delete ((CustomObjectScript_21DA *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0899:
    delete ((CustomObjectScript_0899 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_089A:
    delete ((CustomObjectScript_089A *)ptr);
    break;
  case ID_CUSTOM_OBJECT_089B:
    delete ((CustomObjectScript_089B *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1098:
    delete ((CustomObjectScript_1098 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09A1:
    delete ((CustomObjectScript_09A1 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_19A0:
    delete ((CustomObjectScript_19A0 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_09C9:
    delete ((CustomObjectScript_09C9 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1007:
    delete ((CustomObjectScript_1007 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1016:
    delete ((CustomObjectScript_1016 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_0000:
    delete ((TriggerScript_0000 *)ptr);
    break;
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_000E:
    delete ((TriggerScript_000E *)ptr);
    break;
  case ID_TRIGGER_000D:
    delete ((TriggerScript_000D *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_000C:
    delete ((TriggerScript_000C *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
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
  case ID_CUSTOM_OBJECT_11C4:
  case ID_CUSTOM_OBJECT_1088:
  case ID_CUSTOM_OBJECT_09C6:
  case ID_CUSTOM_OBJECT_11C5:
  case ID_CUSTOM_OBJECT_09C7:
  case ID_CUSTOM_OBJECT_182E:
  case ID_CUSTOM_OBJECT_0A05:
  case ID_CUSTOM_OBJECT_0A04:
  case ID_CUSTOM_OBJECT_0A03:
  case ID_CUSTOM_OBJECT_1A02:
  case ID_CUSTOM_OBJECT_1033:
  case ID_CUSTOM_OBJECT_1200:
  case ID_CUSTOM_OBJECT_1036:
  case ID_CUSTOM_OBJECT_1035:
  case ID_CUSTOM_OBJECT_3032:
  case ID_CUSTOM_OBJECT_1830:
  case ID_CUSTOM_OBJECT_28A2:
  case ID_CUSTOM_OBJECT_0A06:
  case ID_CUSTOM_OBJECT_2885:
  case ID_CUSTOM_OBJECT_107E:
  case ID_CUSTOM_OBJECT_1185:
  case ID_CUSTOM_OBJECT_21B2:
  case ID_CUSTOM_OBJECT_09DE:
  case ID_CUSTOM_OBJECT_09DD:
  case ID_CUSTOM_OBJECT_09DC:
  case ID_CUSTOM_OBJECT_21DA:
  case ID_CUSTOM_OBJECT_0899:
  case ID_CUSTOM_OBJECT_089A:
  case ID_CUSTOM_OBJECT_089B:
  case ID_CUSTOM_OBJECT_1098:
  case ID_CUSTOM_OBJECT_09A1:
  case ID_CUSTOM_OBJECT_19A0:
  case ID_CUSTOM_OBJECT_09C9:
  case ID_CUSTOM_OBJECT_1007:
  case ID_CUSTOM_OBJECT_1016:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_000E:
  case ID_TRIGGER_000D:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000C:
  case ID_TRIGGER_000A:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0008:
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
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_000E;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_000D;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_000C;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_000A;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_0008;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[35];
  static int cust_id_list[35] = {
      ID_CUSTOM_OBJECT_11C4, ID_CUSTOM_OBJECT_1088, ID_CUSTOM_OBJECT_09C6, ID_CUSTOM_OBJECT_11C5,
      ID_CUSTOM_OBJECT_09C7, ID_CUSTOM_OBJECT_182E, ID_CUSTOM_OBJECT_0A05, ID_CUSTOM_OBJECT_0A04,
      ID_CUSTOM_OBJECT_0A03, ID_CUSTOM_OBJECT_1A02, ID_CUSTOM_OBJECT_1033, ID_CUSTOM_OBJECT_1200,
      ID_CUSTOM_OBJECT_1036, ID_CUSTOM_OBJECT_1035, ID_CUSTOM_OBJECT_3032, ID_CUSTOM_OBJECT_1830,
      ID_CUSTOM_OBJECT_28A2, ID_CUSTOM_OBJECT_0A06, ID_CUSTOM_OBJECT_2885, ID_CUSTOM_OBJECT_107E,
      ID_CUSTOM_OBJECT_1185, ID_CUSTOM_OBJECT_21B2, ID_CUSTOM_OBJECT_09DE, ID_CUSTOM_OBJECT_09DD,
      ID_CUSTOM_OBJECT_09DC, ID_CUSTOM_OBJECT_21DA, ID_CUSTOM_OBJECT_0899, ID_CUSTOM_OBJECT_089A,
      ID_CUSTOM_OBJECT_089B, ID_CUSTOM_OBJECT_1098, ID_CUSTOM_OBJECT_09A1, ID_CUSTOM_OBJECT_19A0,
      ID_CUSTOM_OBJECT_09C9, ID_CUSTOM_OBJECT_1007, ID_CUSTOM_OBJECT_1016};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[16];
  cust_handle_list[1] = Object_handles[17];
  cust_handle_list[2] = Object_handles[21];
  cust_handle_list[3] = Object_handles[24];
  cust_handle_list[4] = Object_handles[26];
  cust_handle_list[5] = Object_handles[13];
  cust_handle_list[6] = Object_handles[36];
  cust_handle_list[7] = Object_handles[35];
  cust_handle_list[8] = Object_handles[34];
  cust_handle_list[9] = Object_handles[33];
  cust_handle_list[10] = Object_handles[32];
  cust_handle_list[11] = Object_handles[48];
  cust_handle_list[12] = Object_handles[56];
  cust_handle_list[13] = Object_handles[57];
  cust_handle_list[14] = Object_handles[58];
  cust_handle_list[15] = Object_handles[59];
  cust_handle_list[16] = Object_handles[60];
  cust_handle_list[17] = Object_handles[37];
  cust_handle_list[18] = Object_handles[82];
  cust_handle_list[19] = Object_handles[111];
  cust_handle_list[20] = Object_handles[10];
  cust_handle_list[21] = Object_handles[12];
  cust_handle_list[22] = Object_handles[151];
  cust_handle_list[23] = Object_handles[152];
  cust_handle_list[24] = Object_handles[153];
  cust_handle_list[25] = Object_handles[154];
  cust_handle_list[26] = Object_handles[3];
  cust_handle_list[27] = Object_handles[2];
  cust_handle_list[28] = Object_handles[1];
  cust_handle_list[29] = Object_handles[0];
  cust_handle_list[30] = Object_handles[155];
  cust_handle_list[31] = Object_handles[156];
  cust_handle_list[32] = Object_handles[163];
  cust_handle_list[33] = Object_handles[164];
  cust_handle_list[34] = Object_handles[174];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 35;
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

    // Script 042: Level FRAME (Left Creepers)
    if (qUserFlag(0) == true) {
      if ((qRoomHasPlayer(Room_indexes[0]) == 1) && (qUserFlag(8) == 0)) {
        aUserFlagSet(8, 1);
        cTimeGlassBreak(Room_indexes[1], 0, qRandomValue(1.500000f, 5.000000f));
        cTimeGlassBreak(Room_indexes[2], 0, qRandomValue(1.500000f, 5.000000f));
        cTimeGlassBreak(Room_indexes[3], 0, qRandomValue(1.500000f, 5.000000f));
        cTimeGlassBreak(Room_indexes[4], 0, qRandomValue(1.500000f, 5.000000f));
      }
      if ((qRoomHasPlayer(Room_indexes[5]) == 1) && (qUserFlag(12) == 0)) {
        aUserFlagSet(12, 1);
        cTimeGlassBreak(Room_indexes[6], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[7], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[8], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[9], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[10], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[11], 0, qRandomValue(1.500000f, 8.000000f));
      }

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }

    // Script 043: Level FRAME (Right Creepers)
    if (qUserFlag(1) == true) {
      if ((qRoomHasPlayer(Room_indexes[12]) == 1) && (qUserFlag(13) == 0)) {
        aUserFlagSet(13, 1);
        aPortalBreakGlass(0, Room_indexes[13]);
      }
      if ((qRoomHasPlayer(Room_indexes[14]) == 1) && (qUserFlag(19) == 0)) {
        aUserFlagSet(19, 1);
        cTimeGlassBreak(Room_indexes[15], 0, qRandomValue(3.000000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[16], 0, qRandomValue(1.500000f, 5.000000f));
        cTimeGlassBreak(Room_indexes[17], 0, qRandomValue(1.500000f, 6.000000f));
        cTimeGlassBreak(Room_indexes[18], 0, qRandomValue(1.500000f, 4.000000f));
      }
      if ((qRoomHasPlayer(Room_indexes[19]) == 1) && (qUserFlag(20) == 0)) {
        aUserFlagSet(20, 1);
        cTimeGlassBreak(Room_indexes[20], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[21], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[22], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[23], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[24], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[25], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[26], 0, qRandomValue(1.500000f, 8.000000f));
        cTimeGlassBreak(Room_indexes[27], 0, qRandomValue(1.500000f, 8.000000f));
      }
      if ((qRoomHasPlayer(Room_indexes[28]) == 1) && (qUserFlag(9) == 0)) {
        aUserFlagSet(9, 1);
        cTimeGlassBreak(Room_indexes[29], 0, qRandomValue(1.500000f, 8.000000f));
      }

      // Increment the script action counter
      if (ScriptActionCtr_043 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_043++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 000: Level INIT (Weather)
    if (1) {
      aRainTurnOn(0.900000f);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }

    // Script 005: Level INIT (CrystalCenter)
    if (1) {
      aUserFlagSet(15, 0);
      aUserFlagSet(14, 0);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }

    // Script 012: Level INIT (Power Station)
    if (1) {
      aObjPlayAnim(Object_handles[0], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[1], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[2], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[3], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[4], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[5], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[6], 0, 1, 1.000000f, 0);
      aObjPlayAnim(Object_handles[7], 0, 1, 1.000000f, 0);
      aAIGoalFollowPathSimple(Object_handles[8], Path_indexes[0], 8392965, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[9], Path_indexes[1], 8392965, -1, 3);
      aObjSetShields(Object_handles[8], 100.000000f);
      aObjSetShields(Object_handles[9], 100.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 010: Level INIT (Player Inventory)
    if ((ScriptActionCtr_010 < 1) && (1)) {
      aAddObjectToInventoryNamed(Object_handles[10], qPlayerClosest(Object_handles[11], 0), Message_strings[0], 0);
      aAddObjectToInventoryNamed(Object_handles[12], qPlayerClosest(Object_handles[11], 0), Message_strings[0], 0);

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }

    // Script 017: Level INIT (Terminals)
    if (1) {
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }

    // Script 040: Level INIT (Misc)
    if (1) {
      aObjMakeInvuln(Object_handles[13], 99999);
      aObjMakeInvuln(Object_handles[14], 99999);
      aObjSetMovementType(Object_handles[13], 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(11, 0);
      aUserFlagSet(8, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(13, 0);
      aUserFlagSet(12, 0);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 072: IntroCam-1
    if (1 == true) {
      aObjGhostSet(1, Object_handles[15]);
      aLightningTurnOn(0.100000f, 0.080000f);
      aCinematicSimple(Path_indexes[2], Message_strings[1], Object_handles[16], 8.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }

    // Script 031: INIT Crystal Bars
    if (1) {
      aCloakObject(Object_handles[32], 999999.000000f);
      aObjGhostSet(1, Object_handles[32]);
      aObjSetMovementType(Object_handles[32], 0);
      aObjSetMovementType(Object_handles[33], 0);
      aObjSetMovementType(Object_handles[34], 0);
      aObjSetMovementType(Object_handles[35], 0);
      aObjSetMovementType(Object_handles[36], 0);
      aObjSetMovementType(Object_handles[37], 0);
      aLightningCreate(Object_handles[36], Object_handles[38], 99999.000000f, 2.000000f, 1, Texture_indexes[0],
                       0.300000f, 3, 180, 180, 255, 0);
      aLightningCreate(Object_handles[35], Object_handles[39], 99999.000000f, 2.000000f, 1, Texture_indexes[0],
                       0.300000f, 3, 180, 180, 255, 0);
      aLightningCreate(Object_handles[34], Object_handles[40], 99999.000000f, 2.000000f, 1, Texture_indexes[0],
                       0.300000f, 3, 180, 180, 255, 0);
      aLightningCreate(Object_handles[33], Object_handles[41], 99999.000000f, 2.000000f, 1, Texture_indexes[0],
                       0.300000f, 3, 180, 180, 255, 0);

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }

    // Script 037: INIT Patrols
    if ((ScriptActionCtr_037 < 1) && (1)) {
      aAIGoalFollowPathSimple(Object_handles[61], Path_indexes[7], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[62], Path_indexes[7], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[63], Path_indexes[7], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[64], Path_indexes[7], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[65], Path_indexes[7], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[66], Path_indexes[8], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[67], Path_indexes[8], 8392704, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[68], Path_indexes[8], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[69], Path_indexes[8], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[70], Path_indexes[9], 8392960, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[71], Path_indexes[9], 8392704, -1, 3);
      aAIGoalFollowPathSimple(Object_handles[72], Path_indexes[9], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[73], Path_indexes[9], 8392704, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[74], Path_indexes[9], 8392960, -1, 0);
      aAIGoalFollowPathSimple(Object_handles[75], Path_indexes[9], 8392960, -1, 0);

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }

    // Script 060: INIT Hub Terminals
    if (1) {
      aLightningCreate(Object_handles[76], Object_handles[77], 99999.000000f, 5.000000f, 1, Texture_indexes[1],
                       0.400000f, 2, 255, 150, 255, 0);
      aLightningCreate(Object_handles[76], Object_handles[77], 99999.000000f, 3.500000f, 1, Texture_indexes[3],
                       0.800000f, 2, 100, 100, 255, 0);
      aLightningCreate(Object_handles[78], Object_handles[79], 99999.000000f, 5.000000f, 1, Texture_indexes[1],
                       0.400000f, 2, 255, 150, 255, 0);
      aLightningCreate(Object_handles[78], Object_handles[79], 99999.000000f, 3.500000f, 1, Texture_indexes[3],
                       0.800000f, 2, 100, 100, 255, 0);
      aObjGhostSet(1, Object_handles[80]);
      aObjGhostSet(1, Object_handles[81]);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }

    // Script 028: INIT Main Power Array
    if (1) {
      aUserFlagSet(7, 0);
      aUserFlagSet(6, 0);
      aObjMakeInvuln(Object_handles[139], 99999);
      aObjMakeInvuln(Object_handles[140], 99999);
      aObjMakeInvuln(Object_handles[141], 99999);
      aObjMakeInvuln(Object_handles[142], 99999);
      aObjMakeInvuln(Object_handles[3], 99999);
      aObjMakeInvuln(Object_handles[2], 99999);
      aObjMakeInvuln(Object_handles[1], 99999);
      aObjMakeInvuln(Object_handles[0], 99999);
      aObjMakeInvuln(Object_handles[7], 99999);
      aObjMakeInvuln(Object_handles[6], 99999);
      aObjMakeInvuln(Object_handles[5], 99999);
      aObjMakeInvuln(Object_handles[4], 99999);
      aLightningCreate(Object_handles[143], Object_handles[7], 99999.000000f, 3.000000f, 1, Texture_indexes[1],
                       0.500000f, 3, 200, 100, 255, 0);
      aLightningCreate(Object_handles[144], Object_handles[6], 99999.000000f, 3.000000f, 1, Texture_indexes[1],
                       0.500000f, 3, 200, 100, 255, 0);
      aLightningCreate(Object_handles[145], Object_handles[5], 99999.000000f, 3.000000f, 1, Texture_indexes[1],
                       0.500000f, 3, 200, 100, 255, 0);
      aLightningCreate(Object_handles[146], Object_handles[4], 99999.000000f, 3.000000f, 1, Texture_indexes[1],
                       0.500000f, 3, 200, 100, 255, 0);
      aLightningCreate(Object_handles[147], Object_handles[148], 99999.000000f, 4.500000f, 2, Texture_indexes[1],
                       0.400000f, 3, 200, 150, 100, 0);
      aLightningCreate(Object_handles[149], Object_handles[150], 99999.000000f, 3.500000f, 2, Texture_indexes[0],
                       0.500000f, 3, 0, 150, 250, 0);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }

    // Script 063: Music-Level Start (Intro)
    if (1) {
      aMusicSetRegionAll(0);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 002: RockWall Detonation
    if (event_data->id == 13) {
      aTurnOnSpew(Object_handles[27], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.090000f, 0.700000f,
                  14.000000f, 100.000000f, 0, -1);
      aTurnOnSpew(Object_handles[28], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 0.600000f,
                  22.000000f, 60.000000f, 0, -1);
      aObjMakeVulnerable(Object_handles[14]);
      aObjDestroy(Object_handles[14]);
      aSoundPlayObject(Sound_indexes[1], Object_handles[13], 1.000000f);
      aMiscViewerShake(50.000000f);
      aSetObjectTimer(Object_handles[13], 0.350000f, 3);
      aSetObjectTimer(Object_handles[13], 2.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 030: Rolling Ball Hit Part2
    if ((ScriptActionCtr_030 < 1) && (event_data->id == 21)) {
      aRoomSetWind(Room_indexes[30], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aMiscViewerShake(40.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }

    // Script 022: LeftLab Infection-On
    if (event_data->id == 4) {
      cRegionSetLightingFlicker(1, 0);
      aSetLevelTimer(qRandomValue(2.000000f, 4.000000f), 5);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }

    // Script 009: LeftLab Infection-Off
    if (event_data->id == 5) {
      cRegionSetLightingFlicker(0, 0);
      aSetLevelTimer(qRandomValue(3.000000f, 6.000000f), 4);

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }

    // Script 011: LeftLab Infection Door
    if (event_data->id == 8) {
      cMalfunctionRegionDoors(0);
      aSetLevelTimer(qRandomValue(3.000000f, 7.000000f), 8);

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }

    // Script 016: RightLab Infection-On
    if (event_data->id == 6) {
      cRegionSetLightingFlicker(1, 1);
      aSetLevelTimer(qRandomValue(2.000000f, 4.000000f), 7);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }

    // Script 021: RightLab Infection-Off
    if (event_data->id == 7) {
      cRegionSetLightingFlicker(0, 1);
      aSetLevelTimer(qRandomValue(3.000000f, 6.000000f), 6);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }

    // Script 023: RightLab Infection Door
    if (event_data->id == 12) {
      cMalfunctionRegionDoors(1);
      aSetLevelTimer(qRandomValue(3.000000f, 7.000000f), 12);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }

    // Script 049: Creeper Timer Events
    if (1) {
      cExecTimerEvent(event_data->id);

      // Increment the script action counter
      if (ScriptActionCtr_049 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_049++;
    }

    // Script 034: End Level in 10 seconds!
    if (event_data->id == 14) {
      aShowColoredHUDMessage(255, 0, 0, Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 035: Failed
    if ((ScriptActionCtr_035 < 1) && (event_data->id == 23)) {
      aGoalFailed(Goal_indexes[6], 1);
      aFailLevel();

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }

    // Script 039: End Level Failure
    if ((ScriptActionCtr_039 < 1) && (event_data->id == 16)) {
      aSetLevelTimer(3.800000f, 23);
      aFadeWhiteAndEndlevel(4.000000f, Message_strings[2]);

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }

    // Script 054: Exit Shaker
    if (event_data->id == 19) {
      aMiscViewerShake(qRandomValue(40.000000f, 70.000000f));
      aSetLevelTimer(qRandomValue(1.500000f, 3.500000f), 19);

      // Increment the script action counter
      if (ScriptActionCtr_054 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_054++;
    }
  } break;
  case EVT_LEVEL_GOAL_COMPLETE: {
    tOSIRISEVTLEVELGOALCOMPLETE *event_data = &data->evt_level_goal_complete;

    // Script 041: Both Hubs Infected
    if ((ScriptActionCtr_041 < 1) && ((qUserFlag(1) == 1) && (qUserFlag(0) == 1))) {
      aShowHUDMessage(Message_strings[10]);
      aDoorSetPos(Door_handles[0], 0.800000f);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 026: EndMovie-2
    if ((ScriptActionCtr_026 < 1) && (1)) {
      aObjGhostSet(0, Object_handles[15]);
      aLightningTurnOn(0.100000f, 0.080000f);
      aTurnOnSpew(Object_handles[169], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 10.000000f,
                  7.000000f, 50.000000f, 0, -1);
      aTurnOnSpew(Object_handles[170], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 10.000000f,
                  7.000000f, 50.000000f, 0, -1);
      aObjSpark(Object_handles[171], 30.000000f, 10.000000f);
      aObjSpark(Object_handles[172], 30.000000f, 10.000000f);
      aObjSpark(Object_handles[173], 30.000000f, 10.000000f);
      aStartEndlevelSequencePath(Path_indexes[12], Path_indexes[13], 8.000000f, Message_strings[2]);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11C4::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 073: IntroCam-2
    if (1) {
      aMusicSetRegionAll(1);
      aSetObjectTimer(Object_handles[17], 2.000000f, -1);
      aAISetMaxSpeed(Object_handles[18], 16.000000f);
      aAIGoalFollowPathSimple(Object_handles[18], Path_indexes[3], 4352, -1, 3);
      aTurnOnSpew(Object_handles[19], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[20], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, -1);
      aCinematicSimple(Path_indexes[4], Message_strings[2], Object_handles[21], 8.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1088::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 077: Intro2 Spark
    if (1) {
      aTurnOnSpew(Object_handles[22], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 20.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[23], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 20.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aEmitSparks(80.000000f, Object_handles[17]);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C6::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 074: IntroCam-3
    if (1) {
      aCinematicSimple(Path_indexes[5], Message_strings[2], Object_handles[24], 9.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_11C5::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 075: IntroCam-4
    if (1) {
      aLightningTurnOn(0.150000f, 0.080000f);
      aAISetState(0, Object_handles[25]);
      aObjSetVelocity(Object_handles[25], 0.000000f, 0.000000f, -1.000000f, 120.000000f);
      aPhysFlags(1, 58787840, Object_handles[25]);
      aCinematicSimple(Path_indexes[6], Message_strings[2], Object_handles[26], 8.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C7::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_AIN_MOVIE_END: {
    tOSIRISEVTAINOTIFY *event_data = &data->evt_ain_movie_end;

    // Script 076: IntroCam-POST
    if (1) {
      aLightningTurnOn(0.200000f, 0.080000f);
      aObjGhostSet(1, Object_handles[25]);

      // Increment the script action counter
      if (ScriptActionCtr_076 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_076++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_182E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: Rolling Ball Hit Something
    if ((qObjIsPlayer(event_data->it_handle) == true) || (qObjIsType(event_data->it_handle, 2) == true)) {
      aObjMakeVulnerable(event_data->it_handle);
      aObjKill(event_data->it_handle, 0, 1, 196832, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 008: Rolling Ball Drop
    if (event_data->id == 3) {
      aMiscViewerShake(70.000000f);
      aTurnOnSpew(Object_handles[28], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 0.800000f,
                  19.000000f, 80.000000f, 0, -1);
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }

    // Script 003: Rolling Ball Shaker
    if (event_data->id == 1) {
      aMiscShakeArea(data->me_handle, 60.000000f, 400.000000f);
      aSetObjectTimer(data->me_handle, qRandomValue(1.000000f, 2.500000f), 1);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A05::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Crystal Hit 4
    if ((ScriptActionCtr_033 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[37], 0.000000f, -1);
      aEmitSparks(50.000000f, data->me_handle);
      aEmitSparks(30.000000f, Object_handles[37]);
      aLightningCreate(Object_handles[37], data->me_handle, 99999.000000f, 1.500000f, 2, Texture_indexes[0], 0.500000f,
                       3, 180, 180, 255, 0);
      aLightningCreate(data->me_handle, Object_handles[37], 99999.000000f, 1.500000f, 2, Texture_indexes[1], 1.000000f,
                       2, 100, 200, 255, 0);
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A04::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Crystal Hit 3
    if ((ScriptActionCtr_032 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[37], 0.000000f, -1);
      aEmitSparks(50.000000f, data->me_handle);
      aEmitSparks(30.000000f, Object_handles[37]);
      aLightningCreate(Object_handles[37], data->me_handle, 99999.000000f, 2.500000f, 2, Texture_indexes[0], 0.500000f,
                       3, 180, 180, 255, 0);
      aLightningCreate(data->me_handle, Object_handles[37], 99999.000000f, 1.500000f, 2, Texture_indexes[1], 1.000000f,
                       2, 100, 200, 255, 0);
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A03::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Crystal Hit 2
    if ((ScriptActionCtr_024 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[37], 0.000000f, -1);
      aEmitSparks(50.000000f, data->me_handle);
      aEmitSparks(30.000000f, Object_handles[37]);
      aLightningCreate(Object_handles[37], data->me_handle, 99999.000000f, 2.500000f, 2, Texture_indexes[0], 0.500000f,
                       3, 180, 180, 255, 0);
      aLightningCreate(data->me_handle, Object_handles[37], 99999.000000f, 1.500000f, 2, Texture_indexes[1], 1.000000f,
                       2, 100, 200, 255, 0);
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1A02::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: Crystal Hit 1
    if ((ScriptActionCtr_006 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == true)) {
      aSoundPlayObject(Sound_indexes[2], data->me_handle, 1.000000f);
      aSetObjectTimer(Object_handles[37], 0.000000f, -1);
      aEmitSparks(50.000000f, data->me_handle);
      aEmitSparks(30.000000f, Object_handles[37]);
      aLightningCreate(Object_handles[37], data->me_handle, 99999.000000f, 2.500000f, 2, Texture_indexes[0], 0.500000f,
                       3, 180, 180, 255, 0);
      aLightningCreate(data->me_handle, Object_handles[37], 99999.000000f, 1.500000f, 2, Texture_indexes[1], 1.000000f,
                       2, 100, 200, 255, 0);
      aObjSetMovementType(data->me_handle, 1);

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1033::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 058: Crystal Complete8
    if (1) {
      aSoundPlayObject(Sound_indexes[3], Object_handles[42], 1.000000f);
      aSoundPlayObject(Sound_indexes[4], Object_handles[43], 1.000000f);
      aGoalCompleted(Goal_indexes[0], 1);
      aTurnOnSpew(Object_handles[44], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, -1.000000f,
                  3.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[45], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, -1.000000f,
                  3.000000f, 15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[46], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, -1.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[47], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, -1.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[42], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.100000f, -1.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aObjSetLightingDist(Object_handles[43], 250.000000f);
      aObjSetLightingDist(Object_handles[32], 0.000000f);
      aObjGhostSet(1, Object_handles[32]);
      aRoomSetWind(Room_indexes[31], 0.000000f, 0.000000f, 0.000000f, 1.000000f);
      aMiscViewerShake(100.000000f);
      aTurnOnSpew(Object_handles[48], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.140000f, 0.600000f,
                  250.000000f, 50.000000f, 0, -1);
      aPortalRenderToggle(0, Room_indexes[31], 1);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1200::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 057: Crystal Complete7
    if (1) {
      aSoundStopObj(Object_handles[37]);
      aSoundPlayObject(Sound_indexes[5], Object_handles[32], 1.000000f);
      aSetObjectTimer(Object_handles[32], 0.250000f, -1);
      aMiscViewerShake(100.000000f);
      aTurnOnSpew(Object_handles[49], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.140000f, 0.600000f,
                  300.000000f, 200.000000f, 0, -1);
      aTurnOnSpew(Object_handles[50], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.140000f, 0.600000f,
                  300.000000f, 200.000000f, 0, -1);
      aTurnOnSpew(Object_handles[51], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.140000f, 0.600000f,
                  300.000000f, 200.000000f, 0, -1);
      aTurnOnSpew(Object_handles[52], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.000000f, 0.140000f, 0.600000f,
                  300.000000f, 200.000000f, 0, -1);
      aTurnOnSpew(Object_handles[53], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.100000f, 0.140000f, 1.000000f,
                  300.000000f, 200.000000f, 0, -1);
      aTurnOnSpew(Object_handles[54], -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.900000f, 0.120000f, 0.400000f,
                  150.000000f, 200.000000f, 0, -1);
      aTurnOnSpew(Object_handles[55], -1, 2, 0.000000f, 0.000000f, 65536, 0, 0.900000f, 0.120000f, 0.400000f,
                  150.000000f, 200.000000f, 0, -1);
      aRoomSetWind(Room_indexes[31], 0.000000f, -1.000000f, 0.000000f, 40.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_057 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_057++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1036::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 048: Crystal Complete6
    if (1) {
      aRoomSetWind(Room_indexes[31], 0.000000f, 1.000000f, 0.000000f, 0.500000f);
      aSetObjectTimer(Object_handles[48], 1.350000f, -1);
      aMiscViewerShake(80.000000f);
      aObjSetLightingDist(Object_handles[32], 140.000000f);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 1.700000f, 22.000000f,
                  60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_048 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_048++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1035::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 046: Crystal Complete5
    if (1) {
      aSetObjectTimer(Object_handles[56], 1.500000f, -1);
      aMiscViewerShake(80.000000f);
      aObjSetLightingDist(Object_handles[32], 125.000000f);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 3.200000f, 22.000000f,
                  60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3032::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 045: Crystal Complete4
    if (1) {
      aSetObjectTimer(Object_handles[57], 1.500000f, -1);
      aMiscViewerShake(80.000000f);
      aObjSetLightingDist(Object_handles[32], 110.000000f);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 4.700000f, 22.000000f,
                  60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1830::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 044: Crystal Complete3
    if (1) {
      aSetObjectTimer(Object_handles[58], 1.500000f, -1);
      aMiscViewerShake(80.000000f);
      aObjSetLightingDist(Object_handles[32], 95.000000f);
      aTurnOnSpew(data->me_handle, -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 6.200000f, 22.000000f,
                  60.000000f, 0, -1);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_28A2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 007: Crystal Complete2
    if (1) {
      aSoundPlayObject(Sound_indexes[6], Object_handles[37], 1.000000f);
      aSetObjectTimer(Object_handles[59], 2.000000f, -1);
      aObjGhostSet(0, Object_handles[32]);
      aObjSetLightingDist(Object_handles[32], 80.000000f);
      aMiscViewerShake(80.000000f);
      aEmitSparks(50.000000f, data->me_handle);
      aTurnOnSpew(Object_handles[55], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 8.000000f,
                  12.000000f, 80.000000f, 0, -1);
      aTurnOnSpew(Object_handles[54], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 8.000000f,
                  12.000000f, 80.000000f, 0, -1);
      aTurnOnSpew(Object_handles[48], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.100000f, 8.200000f,
                  14.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[48], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, 8.200000f,
                  25.000000f, 50.000000f, 0, -1);
      aLightningCreate(Object_handles[48], Object_handles[60], 8.100000f, 8.000000f, 1, Texture_indexes[2], 0.600000f,
                       3, 200, 255, 150, 0);

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0A06::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 047: Crystal Complete1
    if (((ScriptActionCtr_006 > 0) == true) && ((ScriptActionCtr_024 > 0) == true) &&
        ((ScriptActionCtr_032 > 0) == true) && ((ScriptActionCtr_033 > 0) == true)) {
      aSetObjectTimer(Object_handles[60], 1.000000f, -1);
      aMiscViewerShake(40.000000f);
      aEmitSparks(80.000000f, data->me_handle);
      aLightningCreate(Object_handles[48], Object_handles[37], 9.200000f, 2.000000f, 2, Texture_indexes[1], 0.400000f,
                       3, 100, 200, 255, 0);
      aLightningCreate(Object_handles[60], Object_handles[37], 99999.000000f, 2.000000f, 1, Texture_indexes[1],
                       0.500000f, 3, 100, 200, 255, 0);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2885::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: LeftDataArm Hit-1
    if ((ScriptActionCtr_078 < 1) && ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (1))) {
      aObjSpark(Object_handles[83], 50.000000f, 5.000000f);
      aObjSpark(Object_handles[78], 50.000000f, 5.000000f);
      aTurnOnSpew(Object_handles[83], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f, 3.000000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[78], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f, 3.000000f,
                  15.000000f, 0, -1);
      aObjDelete(Object_handles[79]);
      aShowHUDMessage(Message_strings[4]);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 1, 5, 4.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
    }

    // Script 059: LeftDataArm Hit-2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 5.000000f) &&
        (qGoalCompleted(Goal_indexes[1]) == false)) {
      if ((qUserFlag(0) == false) && (qUserFlag(14) == true)) {
        aTurnOnSpew(Object_handles[84], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                    3.000000f, 15.000000f, 0, -1);
        aPortalBreakGlass(0, Room_indexes[32]);
        aPortalBreakGlass(0, Room_indexes[33]);
        aPortalBreakGlass(0, Room_indexes[34]);
        aAISetTeam(65536, Object_handles[85]);
        aAISetTeam(131072, Object_handles[86]);
        aAISetTeam(131072, Object_handles[87]);
        aAISetTeam(131072, Object_handles[88]);
        aAISetTeam(131072, Object_handles[89]);
        aAISetTeam(131072, Object_handles[90]);
        aAISetTeam(65536, Object_handles[91]);
        aAISetTeam(131072, Object_handles[92]);
        aAISetTeam(196608, Object_handles[93]);
        aAISetTeam(131072, Object_handles[94]);
        aAISetTeam(131072, Object_handles[95]);
        aAISetTeam(65536, Object_handles[96]);
        aAISetTeam(131072, Object_handles[97]);
        aMiscViewerShake(80.000000f);
        aTurnOnSpew(Object_handles[98], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f,
                    5.000000f, 30.000000f, 0, -1);
        aTurnOnSpew(Object_handles[99], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f,
                    5.000000f, 30.000000f, 0, -1);
        aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 5, 9, 4.000000f, 0);
        aUserFlagSet(0, 1);
        aGoalCompleted(Goal_indexes[1], 1);
        aObjSpark(Object_handles[78], 30.000000f, 99999.000000f);
        aObjSpark(Object_handles[83], 30.000000f, 99999.000000f);
        aObjSpark(Object_handles[80], 60.000000f, 99999.000000f);
        aLightningCreate(Object_handles[83], Object_handles[78], 99999.000000f, 5.000000f, 1, Texture_indexes[1],
                         0.400000f, 2, 255, 150, 255, 0);
        aLightningCreate(Object_handles[78], Object_handles[80], 99999.000000f, 3.000000f, 1, Texture_indexes[4],
                         0.600000f, 3, 255, 255, 255, 0);
        aLightningCreate(Object_handles[83], Object_handles[80], 99999.000000f, 3.000000f, 1, Texture_indexes[4],
                         0.600000f, 3, 255, 255, 255, 0);
        aSetLevelTimer(2.000000f, 4);
        aSetLevelTimer(2.000000f, 8);
        aRoomFogSetState(1, Room_indexes[35]);
        aRoomSetFog(Room_indexes[35], 0.250000f, 0.000000f, 0.500000f, 300.000000f);
        cFogRegion(0, 0.250000f, 0.000000f, 0.500000f, 1000.000000f);
        cChangeFogRegion(0, 0.250000f, 0.000000f, 0.500000f, 300.000000f, 20.000000f);
        aTurnOnSpew(Object_handles[100], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 0);
        aTurnOnSpew(Object_handles[101], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 1);
        aTurnOnSpew(Object_handles[102], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 2);
        aTurnOnSpew(Object_handles[103], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 3);
        aTurnOnSpew(Object_handles[104], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 4);
        aTurnOnSpew(Object_handles[105], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 5);
        aTurnOnSpew(Object_handles[106], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 6);
        aTurnOnSpew(Object_handles[107], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 7);
        aTurnOnSpew(Object_handles[108], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 8);
        aTurnOnSpew(Object_handles[109], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 9);
        aTurnOnSpew(Object_handles[110], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 10);
        aShowHUDMessage(Message_strings[5]);
      } else {
        aShowHUDMessage(Message_strings[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_107E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: RightDataArm Hit-1
    if ((ScriptActionCtr_013 < 1) && ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (1))) {
      aObjSpark(Object_handles[76], 50.000000f, 5.000000f);
      aObjSpark(Object_handles[112], 50.000000f, 5.000000f);
      aTurnOnSpew(Object_handles[76], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f, 3.000000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[112], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f, 3.000000f,
                  15.000000f, 0, -1);
      aObjDelete(Object_handles[77]);
      aShowHUDMessage(Message_strings[4]);
      aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 1, 5, 4.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }

    // Script 014: RightDataArm Hit-2
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjAnimFrame(data->me_handle) == 5.000000f) &&
        (qGoalCompleted(Goal_indexes[2]) == false)) {
      if ((qUserFlag(1) == false) && (qUserFlag(15) == true)) {
        aTurnOnSpew(Object_handles[113], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, -1.000000f,
                    3.000000f, 15.000000f, 0, -1);
        aAISetTeam(131072, Object_handles[114]);
        aAISetTeam(131072, Object_handles[115]);
        aAISetTeam(65536, Object_handles[116]);
        aAISetTeam(131072, Object_handles[117]);
        aAISetTeam(65536, Object_handles[118]);
        aAISetTeam(131072, Object_handles[119]);
        aAISetTeam(196608, Object_handles[120]);
        aAISetTeam(131072, Object_handles[121]);
        aAISetTeam(131072, Object_handles[122]);
        aAISetTeam(65536, Object_handles[123]);
        aAISetTeam(131072, Object_handles[124]);
        aAISetTeam(131072, Object_handles[124]);
        aMiscViewerShake(80.000000f);
        aObjPlayAnim(data->me_handle, 5, 9, 4.000000f, 0);
        aSoundPlayObject(Sound_indexes[7], data->me_handle, 1.000000f);
        aObjSpark(Object_handles[81], 60.000000f, 99999.000000f);
        aObjSpark(Object_handles[76], 30.000000f, 99999.000000f);
        aObjSpark(Object_handles[112], 30.000000f, 99999.000000f);
        aLightningCreate(Object_handles[76], Object_handles[81], 99999.000000f, 3.000000f, 1, Texture_indexes[4],
                         0.600000f, 3, 255, 255, 255, 0);
        aLightningCreate(Object_handles[112], Object_handles[81], 99999.000000f, 3.000000f, 1, Texture_indexes[4],
                         0.600000f, 3, 255, 255, 255, 0);
        aLightningCreate(Object_handles[112], Object_handles[76], 99999.000000f, 5.000000f, 1, Texture_indexes[1],
                         0.400000f, 2, 255, 150, 255, 0);
        aUserFlagSet(1, 1);
        aGoalCompleted(Goal_indexes[2], 1);
        aSetLevelTimer(2.000000f, 6);
        aSetLevelTimer(2.000000f, 12);
        cFogRegion(1, 0.500000f, 0.000000f, 0.250000f, 1000.000000f);
        cChangeFogRegion(1, 0.500000f, 0.000000f, 0.250000f, 300.000000f, 20.000000f);
        aTurnOnSpew(Object_handles[125], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f,
                    5.000000f, 30.000000f, 0, -1);
        aTurnOnSpew(Object_handles[126], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f,
                    5.000000f, 30.000000f, 0, -1);
        aTurnOnSpew(Object_handles[127], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 11);
        aTurnOnSpew(Object_handles[128], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 12);
        aTurnOnSpew(Object_handles[129], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 13);
        aTurnOnSpew(Object_handles[130], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 14);
        aTurnOnSpew(Object_handles[131], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 15);
        aTurnOnSpew(Object_handles[132], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 16);
        aTurnOnSpew(Object_handles[133], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 17);
        aTurnOnSpew(Object_handles[134], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 18);
        aTurnOnSpew(Object_handles[135], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 20);
        aTurnOnSpew(Object_handles[136], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 21);
        aTurnOnSpew(Object_handles[137], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 22);
        aTurnOnSpew(Object_handles[138], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.150000f, -1.000000f,
                    4.000000f, 20.000000f, 1, 23);
        aShowHUDMessage(Message_strings[7]);
      } else {
        aShowHUDMessage(Message_strings[6]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1185::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 036: PICKUP Virus
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[0], 0);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 018: Hub Virus Placement
    if (1) {
      if ((qObjGetDistance(event_data->it_handle, Object_handles[80]) < 40.000000f) && (qUserFlag(14) == false) &&
          ((ScriptActionCtr_078 > 0) == true)) {
        aShowHUDMessage(Message_strings[8]);
        aUserFlagSet(14, 1);
        aSoundPlayObject(Sound_indexes[8], Object_handles[80], 1.000000f);
        aObjGhostSet(0, Object_handles[80]);
        aEmitSparks(80.000000f, Object_handles[80]);
      } else {
        if ((qObjGetDistance(event_data->it_handle, Object_handles[81]) < 40.000000f) && (qUserFlag(15) == false) &&
            ((ScriptActionCtr_013 > 0) == true)) {
          aShowHUDMessage(Message_strings[8]);
          aUserFlagSet(15, 1);
          aSoundPlayObject(Sound_indexes[8], Object_handles[81], 1.000000f);
          aObjGhostSet(0, Object_handles[81]);
          aEmitSparks(80.000000f, Object_handles[81]);
        } else {
          aObjGhostSet(0, data->me_handle);
          aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[0], 0);
          aShowColoredHUDMessageObj(255, 0, 0, Message_strings[9], event_data->it_handle);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21B2::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 050: PICKUP Virus 2
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[0], 0);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  case EVT_USE: {
    tOSIRISEVTUSE *event_data = &data->evt_use;

    // Script 051: Hub Virus Placement 2
    if (1) {
      if ((qObjGetDistance(event_data->it_handle, Object_handles[80]) < 40.000000f) && (qUserFlag(14) == false) &&
          ((ScriptActionCtr_078 > 0) == true)) {
        aShowHUDMessage(Message_strings[8]);
        aUserFlagSet(14, 1);
        aSoundPlayObject(Sound_indexes[8], Object_handles[80], 1.000000f);
        aObjGhostSet(0, Object_handles[80]);
        aEmitSparks(80.000000f, Object_handles[80]);
      } else {
        if ((qObjGetDistance(event_data->it_handle, Object_handles[81]) < 40.000000f) && (qUserFlag(15) == false) &&
            ((ScriptActionCtr_013 > 0) == true)) {
          aShowHUDMessage(Message_strings[8]);
          aUserFlagSet(15, 1);
          aSoundPlayObject(Sound_indexes[8], Object_handles[81], 1.000000f);
          aObjGhostSet(0, Object_handles[81]);
          aEmitSparks(80.000000f, Object_handles[81]);
        } else {
          aObjGhostSet(0, data->me_handle);
          aAddObjectToInventoryNamed(data->me_handle, event_data->it_handle, Message_strings[0], 0);
          aShowColoredHUDMessageObj(255, 0, 0, Message_strings[9], event_data->it_handle);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DE::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 084: Receptor Switch4
    if ((ScriptActionCtr_084 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == 1)) {
      aMiscShakeArea(data->me_handle, 40.000000f, 200.000000f);
      aObjDelete(Object_handles[143]);
      aTurnOnSpew(Object_handles[3], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 2.000000f, 2.500000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[7], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f, 2.500000f,
                  15.000000f, 0, 4);
      aSetObjectTimer(Object_handles[3], 2.000000f, -1);
      aSoundPlayObject(Sound_indexes[9], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 083: Receptor Switch3
    if ((ScriptActionCtr_083 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == 1)) {
      aMiscShakeArea(data->me_handle, 40.000000f, 200.000000f);
      aObjDelete(Object_handles[144]);
      aTurnOnSpew(Object_handles[2], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 2.000000f, 2.500000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[6], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f, 2.500000f,
                  15.000000f, 0, 3);
      aSetObjectTimer(Object_handles[2], 2.000000f, -1);
      aSoundPlayObject(Sound_indexes[9], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09DC::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 082: Receptor Switch2
    if ((ScriptActionCtr_082 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == 1)) {
      aObjDelete(Object_handles[145]);
      aTurnOnSpew(Object_handles[1], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 2.000000f, 2.500000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[5], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f, 2.500000f,
                  15.000000f, 0, 2);
      aSetObjectTimer(Object_handles[1], 2.000000f, -1);
      aSoundPlayObject(Sound_indexes[9], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aMiscShakeArea(data->me_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_21DA::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 019: Receptor Switch1
    if ((ScriptActionCtr_019 < 1) && (qObjIsPlayerWeapon(event_data->it_handle) == 1)) {
      aObjDelete(Object_handles[146]);
      aTurnOnSpew(Object_handles[0], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, 2.000000f, 2.500000f,
                  15.000000f, 0, -1);
      aTurnOnSpew(Object_handles[4], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f, 2.500000f,
                  15.000000f, 0, 1);
      aSetObjectTimer(Object_handles[0], 2.000000f, -1);
      aSoundPlayObject(Sound_indexes[9], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 0, 4, 2.000000f, 0);
      aMiscShakeArea(data->me_handle, 40.000000f, 200.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0899::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 081: Receptor NodeShutdown4
    if ((ScriptActionCtr_081 < 1) && (1)) {
      aObjPlayAnim(Object_handles[7], 1, 2, 1.000000f, 0);
      aObjSpark(data->me_handle, 50.000000f, 2.000000f);
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 5, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_089A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 080: Receptor NodeShutdown3
    if ((ScriptActionCtr_080 < 1) && (1)) {
      aObjPlayAnim(Object_handles[6], 1, 2, 1.000000f, 0);
      aObjSpark(data->me_handle, 50.000000f, 2.000000f);
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 5, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_089B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 079: Receptor NodeShutdown2
    if ((ScriptActionCtr_079 < 1) && (1)) {
      aObjPlayAnim(Object_handles[5], 1, 2, 1.000000f, 0);
      aObjSpark(data->me_handle, 50.000000f, 2.000000f);
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 5, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1098::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 020: Receptor NodeShutdown1
    if ((ScriptActionCtr_020 < 1) && (1)) {
      aObjPlayAnim(Object_handles[4], 1, 2, 1.000000f, 0);
      aObjSpark(data->me_handle, 50.000000f, 2.000000f);
      aSoundPlayObject(Sound_indexes[8], data->me_handle, 1.000000f);
      aObjPlayAnim(data->me_handle, 5, 6, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09A1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 085: Restore Power
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == false)) {
      if (((ScriptActionCtr_086 > 0) == true) && (1)) {
        aSetLevelTimer(50.000000f, 14);
        aSetLevelTimer(60.000000f, 16);
        aTimerShow(16);
        aSetObjectTimer(Object_handles[156], 1.000000f, -1);
        aSetObjectTimer(Object_handles[155], 4.000000f, -1);
        aDoorSetPos(Door_handles[0], 0.000000f);
        aObjPlayAnim(Object_handles[7], 2, 3, 1.000000f, 0);
        aObjPlayAnim(Object_handles[6], 2, 3, 1.000000f, 0);
        aObjPlayAnim(Object_handles[5], 2, 3, 1.000000f, 0);
        aObjPlayAnim(Object_handles[4], 2, 3, 1.000000f, 0);
        aGoalCompleted(Goal_indexes[3], 1);
        aUserFlagSet(7, 1);
        aShowHUDMessage(Message_strings[11]);
        aSoundPlayObject(Sound_indexes[10], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      } else {
        if (qUserFlag(7) == false) {
          aShowHUDMessage(Message_strings[12]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 088: RestorePower3
    if (1) {
      aSetLevelTimer(4.000000f, 19);
      aObjSpark(Object_handles[7], 20.000000f, 5.000000f);
      aObjSpark(Object_handles[6], 20.000000f, 5.000000f);
      aObjSpark(Object_handles[5], 20.000000f, 5.000000f);
      aObjSpark(Object_handles[4], 20.000000f, 5.000000f);
      aLightningCreate(Object_handles[5], Object_handles[141], 99999.000000f, 3.000000f, 2, Texture_indexes[4],
                       0.500000f, 2, 255, 255, 255, 0);
      aLightningCreate(Object_handles[6], Object_handles[140], 99999.000000f, 3.000000f, 2, Texture_indexes[4],
                       0.500000f, 2, 255, 255, 255, 0);
      aLightningCreate(Object_handles[4], Object_handles[142], 99999.000000f, 3.000000f, 2, Texture_indexes[4],
                       0.500000f, 2, 255, 255, 255, 0);
      aLightningCreate(Object_handles[7], Object_handles[139], 99999.000000f, 3.000000f, 2, Texture_indexes[4],
                       0.500000f, 2, 255, 255, 255, 0);
      aMiscShakeArea(Object_handles[150], 80.000000f, 500.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_088 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_088++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_19A0::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 086: Shutdown Power
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(6) == false)) {
      if (((ScriptActionCtr_084 > 0) == true) && ((ScriptActionCtr_083 > 0) == true) &&
          ((ScriptActionCtr_082 > 0) == true) && ((ScriptActionCtr_019 > 0) == true)) {
        aObjSetLightingColor(Object_handles[157], 1.000000f, 0.200000f, 0.200000f);
        aObjSetLightingColor(Object_handles[158], 1.000000f, 0.200000f, 0.200000f);
        aRoomSetLightingPulse(Room_indexes[36], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[37], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[38], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[39], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[40], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[41], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[42], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[43], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[44], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[45], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[46], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[47], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[48], 20.000000f, 0.000000f);
        aRoomSetLightingPulse(Room_indexes[49], 20.000000f, 0.000000f);
        aMiscShakeArea(Object_handles[150], 80.000000f, 200.000000f);
        aTurnOnSpew(Object_handles[150], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f,
                    2.500000f, 15.000000f, 0, -1);
        aTurnOnSpew(Object_handles[147], 0, 7, 0.000000f, 0.000000f, 65536, 0, 1.500000f, 0.100000f, -1.000000f,
                    2.500000f, 15.000000f, 0, -1);
        aGoalCompleted(Goal_indexes[4], 1);
        aUserFlagSet(6, 1);
        aAISetState(0, Object_handles[159]);
        aAISetState(0, Object_handles[160]);
        aAISetState(0, Object_handles[161]);
        aAISetState(0, Object_handles[162]);
        aTurnOffSpew(1);
        aTurnOffSpew(2);
        aTurnOffSpew(3);
        aTurnOffSpew(4);
        aObjDelete(Object_handles[149]);
        aObjDelete(Object_handles[148]);
        aObjSpark(Object_handles[150], 30.000000f, 99999.000000f);
        aObjSpark(Object_handles[147], 30.000000f, 99999.000000f);
        aShowHUDMessage(Message_strings[13]);
        aSoundPlayObject(Sound_indexes[4], Object_handles[158], 1.000000f);
        aSoundPlayObject(Sound_indexes[4], Object_handles[157], 1.000000f);
        aSoundPlayObject(Sound_indexes[10], data->me_handle, 1.000000f);
        aObjPlayAnim(data->me_handle, 0, 3, 3.000000f, 0);
      } else {
        if (qUserFlag(6) == false) {
          aShowHUDMessage(Message_strings[14]);
        }
      }

      // Increment the script action counter
      if (ScriptActionCtr_086 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_086++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 087: RestorePower2
    if (1) {
      aObjPlayAnim(Object_handles[139], 0, 3, 3.000000f, 0);
      aObjPlayAnim(Object_handles[140], 0, 3, 3.000000f, 0);
      aObjPlayAnim(Object_handles[141], 0, 3, 3.000000f, 0);
      aObjPlayAnim(Object_handles[142], 0, 3, 3.000000f, 0);
      aObjSpark(Object_handles[139], 25.000000f, 5.000000f);
      aObjSpark(Object_handles[140], 25.000000f, 5.000000f);
      aObjSpark(Object_handles[141], 25.000000f, 5.000000f);
      aObjSpark(Object_handles[142], 25.000000f, 5.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_087 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_087++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_09C9::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 025: EndMovie-1
    if ((ScriptActionCtr_025 < 1) && (1)) {
      aSetObjectTimer(Object_handles[164], 1.200000f, -1);
      aTurnOnSpew(Object_handles[165], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f,
                  3.000000f, 20.000000f, 0, -1);
      aTurnOnSpew(Object_handles[166], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 10.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[167], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.120000f, 10.000000f,
                  4.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[168], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 3.000000f,
                  3.000000f, 20.000000f, 0, -1);
      aCinematicIntro(Path_indexes[10], Message_strings[2], Object_handles[39], Path_indexes[11], 8.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 027: EndMovie-1 Door Open
    if (1) {
      aTurnOnSpew(Object_handles[166], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, -1);
      aTurnOnSpew(Object_handles[167], -1, 7, 0.000000f, 0.000000f, 65536, 0, 1.200000f, 0.100000f, 10.000000f,
                  5.000000f, 30.000000f, 0, -1);
      aDoorSetPos(Door_handles[1], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: BrokenDoor
    if (1) {
      aEmitSparks(qRandomValue(10.000000f, 50.000000f), data->me_handle);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;

      return CONTINUE_DEFAULT;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Rolling Ball Initiator
    if ((ScriptActionCtr_001 < 1) && (1)) {
      aShowHUDMessageObj(Message_strings[3], event_data->it_handle);
      aSoundPlayObject(Sound_indexes[0], Object_handles[14], 1.000000f);
      aMiscViewerShake(60.000000f);
      aSetLevelTimer(1.000000f, 13);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Rolling Ball Detonation
    if ((ScriptActionCtr_004 < 1) && (event_data->it_handle == Object_handles[13])) {
      aTurnOnSpew(Object_handles[29], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.300000f, 0.120000f, 0.800000f,
                  32.000000f, 70.000000f, 0, -1);
      aTurnOnSpew(Object_handles[29], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 0.500000f,
                  20.000000f, 110.000000f, 0, -1);
      aTurnOnSpew(Object_handles[30], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 0.700000f,
                  22.000000f, 100.000000f, 0, -1);
      aTurnOnSpew(Object_handles[31], -1, 2, 0.000000f, 0.000000f, 65536, 0, 1.400000f, 0.100000f, 0.700000f,
                  22.000000f, 100.000000f, 0, -1);
      aSetLevelTimer(0.300000f, 21);
      aRoomSetWind(Room_indexes[30], 0.000000f, 1.000000f, 0.000000f, 15.000000f);
      aObjMakeVulnerable(event_data->it_handle);
      aMiscViewerShake(100.000000f);
      aObjKill(event_data->it_handle, 0, 2, 524384, 0.000000f, 0.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: Exit Level
    if ((ScriptActionCtr_038 < 1) &&
        ((qObjIsPlayer(event_data->it_handle) == 1) && ((ScriptActionCtr_085 > 0) == true))) {
      aCancelTimer(16);
      aGoalCompleted(Goal_indexes[5], 1);
      aGoalCompleted(Goal_indexes[6], 1);
      aSetObjectTimer(Object_handles[163], 0.000000f, -1);

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

    // Script 071: Music-Level11
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

int16_t TriggerScript_000D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 070: Music-Level22
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_070 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_070++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Music-Level21
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

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Music-Level32
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_068 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_068++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Music-Level31
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_067 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_067++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Music-Temple21
    if (1) {
      aMusicSetRegion(2, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_066 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_066++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Music-Temple1
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

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Music-Outside1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
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
NEXT_ID		89

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:TempValue
1:CrystalCenterMainRed
2:CrystalCenterMainBlue
3:CrystalCenterMainGreen
4:GadgetCinematicFrame
5:FinalCountdownTimer
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:LeftTermInfected
1:RightTermInfected
6:PowerDeactivated
7:PowerRecharging
8:CreeperMid0Activated
9:CreeperMid1Activated
10:CreeperRL0Activated
11:CreeperRL1Activated
12:CreeperLLR0Activated
13:CreeperMid2Activated
14:LeftVirusPlaced
15:RightVirusPlaced
19:CreeperRL3Activated
20:CreeperRLJActivated
21:DoomedGadgetHelpless
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:hLeftLabHalonSpew0
1:hLeftLabHalonSpew1
2:hLeftLabHalonSpew2
3:hLeftLabHalonSpew3
4:hLeftLabHalonSpew4
5:hLeftLabHalonSpew5
6:hLeftLabHalonSpew6
7:hLeftLabHalonSpew7
8:hLeftLabHalonSpew8
9:hLeftLabHalonSpew9
10:hLeftLabHalonSpewA
11:hRightLabHalonSpew0
12:hRightLabHalonSpew1
13:hRightLabHalonSpew2
14:hRightLabHalonSpew3
15:hRightLabHalonSpew4
16:hRightLabHalonSpew5
17:hRightLabHalonSpew6
18:hRightLabHalonSpew7
19:hRightLabHalonSpew8
20:hRightLabHalonSpew9
21:hRightLabHalonSpewA
22:hRightLabHalonSpewB
23:hRightLabHalonSpewC
24:hPowerNodeSpewer
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:PowerNodeBeamTimer1
1:BoulderShakeTimer
2:CrystalCenterMainTimer
3:BoulderDropTimer
4:LeftLabInfectTimer
5:LeftLabInfectTimerOff
6:RightLabInfectTimer
7:RightLabInfectTimerOff
8:LeftLabDoorInfectTimer
9:HubCinematicTimer2
10:HubCinematicTimer0
11:HubCinematicTimer1
12:RightLabDoorInfectTimer
13:BoulderWallDetonateTimer
14:PowerStationDeadTimer
15:PowerStationDeadTimer2
16:FinalCountdownTimer
17:CrystalCenterDelayTimer
18:CrystalCenterDelayTimer2
19:FinalShakeTimer
20:CrystalTrapSpewTimer
21:BoulderHitWind
22:StartLowPatrol
23:Failed
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
0:PowerNode4
1:PowerNode1
2:PowerNode2
3:PowerNode3
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
0:DoomedGadgetPathComplete
1:GadgetKillerPathComplete
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
Door-Top1
Door-Escape
$$DOOR_LIST_END

$$OBJECT_LIST_START
ReceptorNode-01
ReceptorNode-02
ReceptorNode-03
ReceptorNode-04
PowerNode-01
PowerNode-02
PowerNode-03
PowerNode-04
PSGadget0
PSGadget1
Virus Device
PlayerIntroCamera
Virus Device2
BigBoulder
RockWallBoulder
Drop2
TargetExt1
IntroSpark-1
IGIntro2
IntroSmoke2
IntroSmoke1
TargetInt2
IntroSmoke-4
IntroSmoke-3
TargetInt1
Drop1
TargetExt2
BoulderExplosion1
BoulderExplosion2
BHit1
Bhit3
BHit2
FlasherCrystal
CrystalBar1
CrystalBar2
CrystralBar3
CrystalBar4
CrystalBarCenter
CrystalCenter4
CrystalCenter3
CrystalCenter2
CrystalCenter1
BTSmoke3
BTLight
BTSmoke5
BTSmoke4
BTSmoke1
BTSmoke2
CrystalMainTarget
CFX5
CFX4
CFX3
CFX2
CFX1
CBCHit1
CBCHit2
CBCHit6
CBCHit5
CBCHit4
CBCHit3
CrystalCenterBeam
MidBot5
MidBot4
MidBot3
MidBot2
MidBot1
HiBot4
HiBot3
HiBot2
HiBot1
LoBot6
LoBot5
LoBot4
LoBot3
LoBot2
LoBot1
RightTopInter
RightHubBeam
LeftTopInterface
LeftHubBeam
LeftVirusTerminal
RightVirusTerminal
DataArmLeftHub
LeftBottomInterfac
TopDoorSmoke2
LeftTurret-3
LeftTurret-2
LeftTurret-5
LeftTurret-6
LeftTurret-7
LeftTurret-9
LeftTurret-A
LeftTurret-B
LeftTurret-E
LeftTurret-J
LeftTurret-H
LeftTurret-I
LeftTurret-C
SmokeHub2
SmokeHub1
LeftLabHalonSpew0
LeftLabHalonSpew1
LeftLabHalonSpew2
LeftLabHalonSpew3
LeftLabHalonSpew4
LeftLabHalonSpew5
LeftLabHalonSpew6
LeftLabHalonSpew7
LeftLabHalonSpew8
LeftLabHalonSpew9
LeftLabHalonSpewA
RightDataArm
RightBottomInter
TDSmoke1
RightTurret-1
RightTurret-2
RightTurret-3
RightTurret-5
RightTurret-6
RightTurret-7
RightTurret-8
RightTurret-9
RightTurret-B
RightTurret-C
RightTurret-D
SmokeRight2
SmokeRight1
RightLabHalonSpew0
RightLabHalonSpew1
RightLabHalonSpew2
RightLabHalonSpew3
EightLabHalonSpew4
RightLabHalonSpew5
RightLabHalonSpew6
RightLabHalonSpew7
RightLabHalonSpew9
RightLabHalonSpewA
RightLabHalonSpewB
RightLabHalonSpewC
PowerBackup-04
PowerBackup-03
PowerBackup-02
PowerBackup-01
PNodeSmoker4
PNodeSmoker3
PNodeSmoker2
PNodeSmoker1
MainPowerBeam2
MainBeamTarget2
MainBeamTarget1
MainPowerBeam1
RecSwitch4
RecSwitch3
RecSwitch2
RecSwitch1
ReBootSwitch2
ReBootSwitch1
MainPowerWhite1
MainPowerWhite2
PT1
PT2
PT3
PT4
TargetExit1
Door-Escape
ExitSmoke1
ExitSmoke3
ExitSmoke4
ExitSmoke2
Drop2Smoke2
Drop2Smoke1
Turret-Outer13
Turret-Outer12
Turret-Outer11
Door-Bottom2
$$OBJECT_LIST_END

$$ROOM_LIST_START
Creeper-Mid0
Creeper-Mid0A
Creeper-Mid0B
Creeper-Mid0C
Creeper-Mid0D
LeftLabRO
Creeper-LLR0A
Creeper-LLR0B
Creeper-LLR0C
Creeper-LLR0D
Creeper-LLR0E
Creeper-LLROF
Creeper-Mid2
Creeper-Mid2A
RightLabR3
Creeper-RL3-A
Creeper-RL3-B
Creeper-RL3-C
Creeper-RL3-D
RightLabRJ
Creeper-RLJ-A
Creeper-RLJ-B
Creeper-RLJ-C
Creeper-RLJ-D
Creeper-RLJ-E
Creeper-RLJ-F
Creeper-RLJ-G
Creeper-RLJ-H
Creeper-Mid1
Creeper-Mid1A
BoulderHitRoom
CrystalCenterRoom
NRGCreep
LeftLabCreep1
LeftLabCreep0
LeftX1
PowerChute2
PowerLow8
PowerLow7
PowerLow6
PowerLow5
PowerLow4
PowerLow3
PowerLow2
PowerLow1
PowerChute
PowerSide2
PowerDoor
PowerSide1
PowerStation
$$ROOM_LIST_END

$$TRIGGER_LIST_START
RollingBallWatchout
RollingBallDetonate
BeginEndSequence
MusicLevel1-1
MusicLevel2-2
MusicLevel2-1
MusicLevel3-2
MusicLevel3-1
MusicTemple-2
MusicTemple-1
MusicOutside-1
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbExplosionFarB
RockBreakAway
WpnEMDFireD
AmbSteamHigh
AmbSirenBRedAcrop
ExpMissileLarge1
WpnPyroGLOmegaFire
AmbSwitch21
Wall fade ???
AmbSwitch31
AmbSwitch11
$$SOUND_LIST_END

$$TEXTURE_LIST_START
FunkyEffectGreen
FunkyEffect3
HellionBeam
FunkyEffect1
FunkyEffectAntiV
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
PSGadget0Path
PSGadget1Path
IntroCam-Ext1
IGInt2
IntroCam-Int2
IntroCam-Int1
IntroCam-Ext2
MidPatrol1
LowPatrol2
LowPatrol1
ExitCam-1
ExitShip-1
ExitCam-2
ExitShip-2
$$PATH_LIST_END

$$MATCEN_LIST_START
$$MATCEN_LIST_END

$$GOAL_LIST_START
Blast Into the Laboratory
Infect Computer Hub Delta
Infect Computer Hub Gamma
Reboot the System
Shut Down the Main Power
Infect the Lab System With Virus Data
Escape Before the System Reboots
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Level INIT (Weather)
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRainTurnOn
                        $$CHILD_BLOCK_START
                        10:9:0.900000:Density
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Level INIT (CrystalCenter)
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
                        10:10:0:15:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:14:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:Level INIT (Power Station)
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
                        10:1:0:0:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:16:0:Path
                        10:15:8392965:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:16:1:Path
                        10:15:8392965:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                08:aObjSetShields
                        $$CHILD_BLOCK_START
                        10:1:0:9:Object
                        10:6:100.000000:Shields
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:Level INIT (Player Inventory)
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:0:10:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:0:11:Object
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:8:VirusDeviceName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:0:12:Object
                        06:qPlayerClosest:PlayerObject
                                $$CHILD_BLOCK_START
                                10:1:0:11:Object
                                10:10:0:0:UserVar
                                $$CHILD_BLOCK_END
                        10:8:VirusDeviceName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Level INIT (Terminals)
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
                        10:10:0:1:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:Level INIT (Misc)
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
                        10:1:0:13:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:10:0:0:MovementType
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
                        10:10:0:13:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Level FRAME (Left Creepers)
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRoomHasPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:2:0:Room
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:8:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:0:Bool
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:8:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:1:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:5.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:2:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:5.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:3:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:5.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:4:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:5.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRoomHasPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:2:5:Room
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:12:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:0:Bool
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:12:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:6:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:7:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:8:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:9:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:10:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:11:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:43:Level FRAME (Right Creepers)
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
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
        04:0:0:0
                $$CHILD_BLOCK_START
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRoomHasPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:2:12:Room
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:13:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:0:Bool
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:13:Room
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRoomHasPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:2:14:Room
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:19:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:0:Bool
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:19:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:15:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:3.000000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:16:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:5.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:17:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:6.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:18:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:4.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRoomHasPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:2:19:Room
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:20:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:0:Bool
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:20:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:20:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:21:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:22:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:23:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:24:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:25:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:26:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:27:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qRoomHasPlayer:Bool
                                                $$CHILD_BLOCK_START
                                                10:2:28:Room
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:1:Bool
                                        $$CHILD_BLOCK_END
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:9:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:1:0
                                        10:5:0:Bool
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
                        08:cTimeGlassBreak
                                $$CHILD_BLOCK_START
                                10:2:29:Room
                                10:4:0:PortalNum
                                06:qRandomValue:Seconds
                                        $$CHILD_BLOCK_START
                                        10:6:1.500000:LowerLimit
                                        10:6:8.000000:UpperLimit
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:72:IntroCam-1
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
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:15:Object
                        $$CHILD_BLOCK_END
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Seconds
                        10:9:0.080000:Probability
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:2:CameraPath
                        10:8:IntroMessage:Text
                        10:1:0:16:Target
                        10:6:8.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:73:IntroCam-2
        $$CHILD_BLOCK_START
        01:1:16
        02:18
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:17:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aAISetMaxSpeed
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:6:16.000000:MaxSpeed
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:16:3:Path
                        10:15:4352:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:4:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:21:Target
                        10:6:8.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Intro2 Spark
        $$CHILD_BLOCK_START
        01:1:17
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:20.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Number
                        10:1:0:17:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:74:IntroCam-3
        $$CHILD_BLOCK_START
        01:1:21
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:5:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:24:Target
                        10:6:9.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:75:IntroCam-4
        $$CHILD_BLOCK_START
        01:1:24
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:0.150000:Seconds
                        10:9:0.080000:Probability
                        $$CHILD_BLOCK_END
                08:aAISetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aObjSetVelocity
                        $$CHILD_BLOCK_START
                        10:1:0:25:Object
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:-1.000000:Z
                        10:6:120.000000:Speed
                        $$CHILD_BLOCK_END
                08:aPhysFlags
                        $$CHILD_BLOCK_START
                        10:10:0:1:Set/Clear
                        10:15:58787840:PhysicsFlags
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:6:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:26:Target
                        10:6:8.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:IntroCam-POST
        $$CHILD_BLOCK_START
        01:1:26
        02:18
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:0.200000:Seconds
                        10:9:0.080000:Probability
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:25:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Rolling Ball Initiator
        $$CHILD_BLOCK_START
        01:0:0
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:Watchout:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:14:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:60.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Time
                        10:10:0:13:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:RockWall Detonation
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
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.090000:BlobInterval
                        10:6:0.700000:SpewLife
                        10:6:14.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.600000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aObjDestroy
                        $$CHILD_BLOCK_START
                        10:1:0:14:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:1:Sound
                        10:1:0:13:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Amount
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:0.350000:Time
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:13:Object
                        10:6:2.000000:Time
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:Rolling Ball Drop
        $$CHILD_BLOCK_START
        01:1:13
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:70.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.800000:SpewLife
                        10:6:19.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Rolling Ball Shaker
        $$CHILD_BLOCK_START
        01:1:13
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:60.000000:Amount
                        10:6:400.000000:Dist
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:1.000000:LowerLimit
                                10:6:2.500000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Rolling Ball Hit Something
        $$CHILD_BLOCK_START
        01:1:13
        02:0
        03:0
                $$CHILD_BLOCK_START
                09:1
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
                                06:qObjIsType:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:1:-1:Object
                                        10:10:0:2:ObjectType
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:1:DeathExplosionSize
                        10:15:196832:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Rolling Ball Detonation
        $$CHILD_BLOCK_START
        01:0:1
        02:1
        03:0
                $$CHILD_BLOCK_START
                05:2
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        07:1:0
                        10:1:0:13:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:0.800000:SpewLife
                        10:6:32.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:29:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.500000:SpewLife
                        10:6:20.000000:BlobSize
                        10:6:110.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:30:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.700000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:31:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:0.700000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:100.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:0.300000:Time
                        10:10:0:21:TimerID
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:15.000000:Speed
                        $$CHILD_BLOCK_END
                08:aObjMakeVulnerable
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aObjKill
                        $$CHILD_BLOCK_START
                        10:1:1:-1:Object
                        10:10:0:0:DeathDelayType
                        10:10:0:2:DeathExplosionSize
                        10:15:524384:DeathFlags
                        10:6:0.000000:MinDelay
                        10:6:0.000000:MaxDelay
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Rolling Ball Hit Part2
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:30:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:INIT Crystal Bars
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aCloakObject
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:999999.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:10:0:0:MovementType
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object1
                        10:1:0:38:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object1
                        10:1:0:39:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object1
                        10:1:0:40:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:33:Object1
                        10:1:0:41:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:0:Texture
                        10:6:0.300000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Crystal Hit 4
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object1
                        10:1:2:-1:Object2
                        10:6:99999.000000:Lifetime
                        10:6:1.500000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:37:Object2
                        10:6:99999.000000:Lifetime
                        10:6:1.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:1.000000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:200:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Crystal Hit 3
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
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object1
                        10:1:2:-1:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.500000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:37:Object2
                        10:6:99999.000000:Lifetime
                        10:6:1.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:1.000000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:200:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Crystal Hit 2
        $$CHILD_BLOCK_START
        01:1:34
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object1
                        10:1:2:-1:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.500000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:37:Object2
                        10:6:99999.000000:Lifetime
                        10:6:1.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:1.000000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:200:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:Crystal Hit 1
        $$CHILD_BLOCK_START
        01:1:33
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
                        10:12:2:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:30.000000:Number
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object1
                        10:1:2:-1:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.500000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:180:Red
                        10:4:180:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object1
                        10:1:0:37:Object2
                        10:6:99999.000000:Lifetime
                        10:6:1.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:1.000000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:200:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjSetMovementType
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:10:0:1:MovementType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Crystal Complete8
        $$CHILD_BLOCK_START
        01:1:32
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:1:0:42:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:4:Sound
                        10:1:0:43:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
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
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:43:Object
                        10:6:250.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:0.000000:Distance
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:0.600000:SpewLife
                        10:6:250.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aPortalRenderToggle
                        $$CHILD_BLOCK_START
                        10:4:0:PortalNum
                        10:2:31:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:57:Crystal Complete7
        $$CHILD_BLOCK_START
        01:1:48
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundStopObj
                        $$CHILD_BLOCK_START
                        10:1:0:37:Object
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:5:Sound
                        10:1:0:32:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:0.250000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:100.000000:Amount
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:49:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:0.600000:SpewLife
                        10:6:300.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
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
                        10:6:1.000000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:0.600000:SpewLife
                        10:6:300.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:51:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:0.600000:SpewLife
                        10:6:300.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:52:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.000000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:0.600000:SpewLife
                        10:6:300.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:53:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.100000:BlobLifetime
                        10:6:0.140000:BlobInterval
                        10:6:1.000000:SpewLife
                        10:6:300.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.900000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:0.400000:SpewLife
                        10:6:150.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:0.900000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:0.400000:SpewLife
                        10:6:150.000000:BlobSize
                        10:6:200.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:40.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:48:Crystal Complete6
        $$CHILD_BLOCK_START
        01:1:56
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:31:Room
                        10:6:0.000000:X
                        10:6:1.000000:Y
                        10:6:0.000000:Z
                        10:6:0.500000:Speed
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:6:1.350000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:140.000000:Distance
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
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:1.700000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:Crystal Complete5
        $$CHILD_BLOCK_START
        01:1:57
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:56:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:125.000000:Distance
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
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.200000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Crystal Complete4
        $$CHILD_BLOCK_START
        01:1:58
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:57:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:110.000000:Distance
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
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:4.700000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Crystal Complete3
        $$CHILD_BLOCK_START
        01:1:59
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:58:Object
                        10:6:1.500000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:95.000000:Distance
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
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:6.200000:SpewLife
                        10:6:22.000000:BlobSize
                        10:6:60.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:Crystal Complete2
        $$CHILD_BLOCK_START
        01:1:60
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:6:Sound
                        10:1:0:37:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:59:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Ghost/Unghost
                        10:1:0:32:Object
                        $$CHILD_BLOCK_END
                08:aObjSetLightingDist
                        $$CHILD_BLOCK_START
                        10:1:0:32:Object
                        10:6:80.000000:Distance
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Amount
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:50.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:55:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:54:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.000000:SpewLife
                        10:6:12.000000:BlobSize
                        10:6:80.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:8.200000:SpewLife
                        10:6:14.000000:BlobSize
                        10:6:70.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object
                        10:4:-1:GunNum
                        10:10:0:2:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.300000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:8.200000:SpewLife
                        10:6:25.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object1
                        10:1:0:60:Object2
                        10:6:8.100000:Lifetime
                        10:6:8.000000:Thickness
                        10:4:1:NumTiles
                        10:14:2:Texture
                        10:6:0.600000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:255:Green
                        10:4:150:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Crystal Complete1
        $$CHILD_BLOCK_START
        01:1:37
        02:9
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:6:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:24:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:32:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:33:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object
                        10:6:1.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        10:6:40.000000:Amount
                        $$CHILD_BLOCK_END
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        10:6:80.000000:Number
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:48:Object1
                        10:1:0:37:Object2
                        10:6:9.200000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:100:Red
                        10:4:200:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:60:Object1
                        10:1:0:37:Object2
                        10:6:99999.000000:Lifetime
                        10:6:2.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:100:Red
                        10:4:200:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:INIT Patrols
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
                        10:1:0:61:Object
                        10:16:7:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:62:Object
                        10:16:7:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:63:Object
                        10:16:7:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:64:Object
                        10:16:7:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:65:Object
                        10:16:7:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:66:Object
                        10:16:8:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:67:Object
                        10:16:8:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:68:Object
                        10:16:8:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:69:Object
                        10:16:8:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:70:Object
                        10:16:9:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:71:Object
                        10:16:9:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:3:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:72:Object
                        10:16:9:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:73:Object
                        10:16:9:Path
                        10:15:8392704:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:74:Object
                        10:16:9:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPathSimple
                        $$CHILD_BLOCK_START
                        10:1:0:75:Object
                        10:16:9:Path
                        10:15:8392960:AIGoalFlags
                        10:10:0:-1:GoalID
                        10:10:0:0:GoalPriority
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:INIT Hub Terminals
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object1
                        10:1:0:77:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:255:Red
                        10:4:150:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object1
                        10:1:0:77:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.800000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object1
                        10:1:0:79:Object2
                        10:6:99999.000000:Lifetime
                        10:6:5.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:255:Red
                        10:4:150:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object1
                        10:1:0:79:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:1:NumTiles
                        10:14:3:Texture
                        10:6:0.800000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:100:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:80:Object
                        $$CHILD_BLOCK_END
                08:aObjGhostSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Ghost/Unghost
                        10:1:0:81:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:78:LeftDataArm Hit-1
        $$CHILD_BLOCK_START
        01:1:82
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:6:50.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:6:50.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:83:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:78:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:79:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeftLabInitData:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:5:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:59:LeftDataArm Hit-2
        $$CHILD_BLOCK_START
        01:1:82
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
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:5.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalCompleted:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:1:LevelGoal
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
                                                10:10:0:0:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:84:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:3.000000:BlobSize
                                10:6:15.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:32:Room
                                $$CHILD_BLOCK_END
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:33:Room
                                $$CHILD_BLOCK_END
                        08:aPortalBreakGlass
                                $$CHILD_BLOCK_START
                                10:4:0:PortalNum
                                10:2:34:Room
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:0:85:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:86:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:87:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:88:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:89:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:90:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:0:91:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:92:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:196608:Teams
                                10:1:0:93:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:94:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:95:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:0:96:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:97:Object
                                $$CHILD_BLOCK_END
                        08:aMiscViewerShake
                                $$CHILD_BLOCK_START
                                10:6:80.000000:Amount
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:98:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:5.000000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:99:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:5.000000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:7:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:5:StartFrame
                                10:4:9:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:1:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:78:Object
                                10:6:30.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:83:Object
                                10:6:30.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:80:Object
                                10:6:60.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:83:Object1
                                10:1:0:78:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:1:NumTiles
                                10:14:1:Texture
                                10:6:0.400000:SlideTime
                                10:4:2:TimesDrawn
                                10:4:255:Red
                                10:4:150:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:78:Object1
                                10:1:0:80:Object2
                                10:6:99999.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.600000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:83:Object1
                                10:1:0:80:Object2
                                10:6:99999.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.600000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:4:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:8:TimerID
                                $$CHILD_BLOCK_END
                        08:aRoomFogSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:On/Off
                                10:2:35:Room
                                $$CHILD_BLOCK_END
                        08:aRoomSetFog
                                $$CHILD_BLOCK_START
                                10:2:35:Room
                                10:6:0.250000:Red
                                10:6:0.000000:Green
                                10:6:0.500000:Blue
                                10:6:300.000000:Depth
                                $$CHILD_BLOCK_END
                        08:cFogRegion
                                $$CHILD_BLOCK_START
                                10:10:0:0:LevelRegion
                                10:6:0.250000:Red
                                10:6:0.000000:Green
                                10:6:0.500000:Blue
                                10:6:1000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:cChangeFogRegion
                                $$CHILD_BLOCK_START
                                10:10:0:0:LevelRegion
                                10:6:0.250000:Red
                                10:6:0.000000:Green
                                10:6:0.500000:Blue
                                10:6:300.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:100:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:0:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:101:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:102:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:2:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:103:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:3:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:104:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:4:SpewHandle
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
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:5:SpewHandle
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
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:6:SpewHandle
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
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:7:SpewHandle
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
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:8:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:109:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:9:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:110:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:10:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LeftLabInfected:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LeftLabNotReady:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:RightDataArm Hit-1
        $$CHILD_BLOCK_START
        01:1:111
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
                        05:0
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:6:50.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        10:6:50.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:76:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:112:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:77:Object
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeftLabInitData:Message
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:7:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:1:StartFrame
                        10:4:5:EndFrame
                        10:6:4.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:RightDataArm Hit-2
        $$CHILD_BLOCK_START
        01:1:111
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
                                06:qObjAnimFrame:Float
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:6:5.000000:Literal
                                $$CHILD_BLOCK_END
                        05:1
                                $$CHILD_BLOCK_START
                                06:qGoalCompleted:Bool
                                        $$CHILD_BLOCK_START
                                        10:18:0:2:LevelGoal
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
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:15:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:113:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.200000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:3.000000:BlobSize
                                10:6:15.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:114:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:115:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:0:116:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:117:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:0:118:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:119:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:196608:Teams
                                10:1:0:120:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:121:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:122:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:65536:Teams
                                10:1:0:123:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:124:Object
                                $$CHILD_BLOCK_END
                        08:aAISetTeam
                                $$CHILD_BLOCK_START
                                10:10:0:131072:Teams
                                10:1:0:124:Object
                                $$CHILD_BLOCK_END
                        08:aMiscViewerShake
                                $$CHILD_BLOCK_START
                                10:6:80.000000:Amount
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:2:-1:Object
                                10:4:5:StartFrame
                                10:4:9:EndFrame
                                10:6:4.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:7:Sound
                                10:1:2:-1:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:81:Object
                                10:6:60.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:76:Object
                                10:6:30.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:112:Object
                                10:6:30.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:76:Object1
                                10:1:0:81:Object2
                                10:6:99999.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.600000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:112:Object1
                                10:1:0:81:Object2
                                10:6:99999.000000:Lifetime
                                10:6:3.000000:Thickness
                                10:4:1:NumTiles
                                10:14:4:Texture
                                10:6:0.600000:SlideTime
                                10:4:3:TimesDrawn
                                10:4:255:Red
                                10:4:255:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aLightningCreate
                                $$CHILD_BLOCK_START
                                10:1:0:112:Object1
                                10:1:0:76:Object2
                                10:6:99999.000000:Lifetime
                                10:6:5.000000:Thickness
                                10:4:1:NumTiles
                                10:14:1:Texture
                                10:6:0.400000:SlideTime
                                10:4:2:TimesDrawn
                                10:4:255:Red
                                10:4:150:Green
                                10:4:255:Blue
                                10:5:0:AutoTile
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:1:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:2:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:6:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:2.000000:Time
                                10:10:0:12:TimerID
                                $$CHILD_BLOCK_END
                        08:cFogRegion
                                $$CHILD_BLOCK_START
                                10:10:0:1:LevelRegion
                                10:6:0.500000:Red
                                10:6:0.000000:Green
                                10:6:0.250000:Blue
                                10:6:1000.000000:Depth
                                $$CHILD_BLOCK_END
                        08:cChangeFogRegion
                                $$CHILD_BLOCK_START
                                10:10:0:1:LevelRegion
                                10:6:0.500000:Red
                                10:6:0.000000:Green
                                10:6:0.250000:Blue
                                10:6:300.000000:Depth
                                10:6:20.000000:Time
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:125:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:5.000000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:126:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:5.000000:BlobSize
                                10:6:30.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:127:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:11:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:128:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:12:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:129:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:13:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:130:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:14:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:131:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:15:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:132:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:16:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:133:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:17:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:134:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:18:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:135:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:20:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:136:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:21:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:137:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:22:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:138:Object
                                10:4:-1:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.150000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:4.000000:BlobSize
                                10:6:20.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:23:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RightLabInfected:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LeftLabNotReady:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:PICKUP Virus
        $$CHILD_BLOCK_START
        01:1:10
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
                        10:8:VirusDeviceName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:PICKUP Virus 2
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
                08:aAddObjectToInventoryNamed
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:1:1:-1:PlayerObject
                        10:8:VirusDeviceName:ItemName
                        10:5:0:Spewable
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Hub Virus Placement
        $$CHILD_BLOCK_START
        01:1:10
        02:25
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object1
                                                10:1:0:80:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:40.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:78:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LeftLabVirusPlaced:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:8:Sound
                                10:1:0:80:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:80:Object
                                $$CHILD_BLOCK_END
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:80.000000:Number
                                10:1:0:80:Object
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
                                                06:qObjGetDistance:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object1
                                                        10:1:0:81:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:40.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qScriptExecuted_DALLAS:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:11:13:ScriptID
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:LeftLabVirusPlaced:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:8:Sound
                                        10:1:0:81:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:81:Object
                                        $$CHILD_BLOCK_END
                                08:aEmitSparks
                                        $$CHILD_BLOCK_START
                                        10:6:80.000000:Number
                                        10:1:0:81:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventoryNamed
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:1:1:-1:PlayerObject
                                        10:8:VirusDeviceName:ItemName
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
                                08:aShowColoredHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:4:255:Red
                                        10:4:0:Green
                                        10:4:0:Blue
                                        10:8:VirusInfectFail:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:51:Hub Virus Placement 2
        $$CHILD_BLOCK_START
        01:1:12
        02:25
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
                                05:2
                                        $$CHILD_BLOCK_START
                                        06:qObjGetDistance:Float
                                                $$CHILD_BLOCK_START
                                                10:1:1:-1:Object1
                                                10:1:0:80:Object2
                                                $$CHILD_BLOCK_END
                                        07:1:3
                                        10:6:40.000000:Literal
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:14:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:78:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:LeftLabVirusPlaced:Message
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:14:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:8:Sound
                                10:1:0:80:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aObjGhostSet
                                $$CHILD_BLOCK_START
                                10:10:0:0:Ghost/Unghost
                                10:1:0:80:Object
                                $$CHILD_BLOCK_END
                        08:aEmitSparks
                                $$CHILD_BLOCK_START
                                10:6:80.000000:Number
                                10:1:0:80:Object
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
                                                06:qObjGetDistance:Float
                                                        $$CHILD_BLOCK_START
                                                        10:1:1:-1:Object1
                                                        10:1:0:81:Object2
                                                        $$CHILD_BLOCK_END
                                                07:1:3
                                                10:6:40.000000:Literal
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qUserFlag:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:10:0:15:UserFlag
                                                        $$CHILD_BLOCK_END
                                                07:0:7
                                                $$CHILD_BLOCK_END
                                        05:1
                                                $$CHILD_BLOCK_START
                                                06:qScriptExecuted_DALLAS:Bool
                                                        $$CHILD_BLOCK_START
                                                        10:11:13:ScriptID
                                                        $$CHILD_BLOCK_END
                                                07:0:6
                                                $$CHILD_BLOCK_END
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:LeftLabVirusPlaced:Message
                                        $$CHILD_BLOCK_END
                                08:aUserFlagSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:15:UserFlag
                                        10:5:1:True/False
                                        $$CHILD_BLOCK_END
                                08:aSoundPlayObject
                                        $$CHILD_BLOCK_START
                                        10:12:8:Sound
                                        10:1:0:81:Object
                                        10:9:1.000000:Volume
                                        $$CHILD_BLOCK_END
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:0:81:Object
                                        $$CHILD_BLOCK_END
                                08:aEmitSparks
                                        $$CHILD_BLOCK_START
                                        10:6:80.000000:Number
                                        10:1:0:81:Object
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:1
                                $$CHILD_BLOCK_START
                                08:aObjGhostSet
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:Ghost/Unghost
                                        10:1:2:-1:Object
                                        $$CHILD_BLOCK_END
                                08:aAddObjectToInventoryNamed
                                        $$CHILD_BLOCK_START
                                        10:1:2:-1:Object
                                        10:1:1:-1:PlayerObject
                                        10:8:VirusDeviceName:ItemName
                                        10:5:0:Spewable
                                        $$CHILD_BLOCK_END
                                08:aShowColoredHUDMessageObj
                                        $$CHILD_BLOCK_START
                                        10:4:255:Red
                                        10:4:0:Green
                                        10:4:0:Blue
                                        10:8:VirusInfectFail:Message
                                        10:1:1:-1:PlayerObject
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:LeftLab Infection-On
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
                08:cRegionSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:10:0:0:LevelRegion
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:2.000000:LowerLimit
                                10:6:4.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:5:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:LeftLab Infection-Off
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
                08:cRegionSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:10:0:0:LevelRegion
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:3.000000:LowerLimit
                                10:6:6.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:LeftLab Infection Door
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
                08:cMalfunctionRegionDoors
                        $$CHILD_BLOCK_START
                        10:10:0:0:LevelRegion
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:3.000000:LowerLimit
                                10:6:7.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:8:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:RightLab Infection-On
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
                08:cRegionSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:10:0:1:LevelRegion
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:2.000000:LowerLimit
                                10:6:4.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:7:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:RightLab Infection-Off
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
                08:cRegionSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:10:0:1:LevelRegion
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:3.000000:LowerLimit
                                10:6:6.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:6:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:RightLab Infection Door
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
                08:cMalfunctionRegionDoors
                        $$CHILD_BLOCK_START
                        10:10:0:1:LevelRegion
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:3.000000:LowerLimit
                                10:6:7.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:12:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:Both Hubs Infected
        $$CHILD_BLOCK_START
        01:2:0
        02:23
        03:0
                $$CHILD_BLOCK_START
                09:0
                        $$CHILD_BLOCK_START
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:1:UserFlag
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        05:2
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:0:UserFlag
                                        $$CHILD_BLOCK_END
                                07:1:0
                                10:5:1:Bool
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:GetToPower:Message
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:0.800000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:49:Creeper Timer Events
        $$CHILD_BLOCK_START
        01:2:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:cExecTimerEvent
                        $$CHILD_BLOCK_START
                        10:10:2:0:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:INIT Main Power Array
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
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:6:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:141:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:142:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aObjMakeInvuln
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:99999:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object1
                        10:1:0:7:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:144:Object1
                        10:1:0:6:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:145:Object1
                        10:1:0:5:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:146:Object1
                        10:1:0:4:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:1:NumTiles
                        10:14:1:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:100:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:147:Object1
                        10:1:0:148:Object2
                        10:6:99999.000000:Lifetime
                        10:6:4.500000:Thickness
                        10:4:2:NumTiles
                        10:14:1:Texture
                        10:6:0.400000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:200:Red
                        10:4:150:Green
                        10:4:100:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:149:Object1
                        10:1:0:150:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.500000:Thickness
                        10:4:2:NumTiles
                        10:14:0:Texture
                        10:6:0.500000:SlideTime
                        10:4:3:TimesDrawn
                        10:4:0:Red
                        10:4:150:Green
                        10:4:250:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Receptor Switch4
        $$CHILD_BLOCK_START
        01:1:151
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:143:Object
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:2.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:4:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
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
00:83:Receptor Switch3
        $$CHILD_BLOCK_START
        01:1:152
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:144:Object
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:2.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:3:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
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
00:82:Receptor Switch2
        $$CHILD_BLOCK_START
        01:1:153
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:145:Object
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
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:2.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:2:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:1:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Receptor Switch1
        $$CHILD_BLOCK_START
        01:1:154
        02:0
        03:0
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
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjDelete
                        $$CHILD_BLOCK_START
                        10:1:0:146:Object
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:2.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:0:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.500000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:2.500000:BlobSize
                        10:6:15.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:0:Object
                        10:6:2.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:9:Sound
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
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:40.000000:Amount
                        10:6:200.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:Receptor NodeShutdown4
        $$CHILD_BLOCK_START
        01:1:3
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:5:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:80:Receptor NodeShutdown3
        $$CHILD_BLOCK_START
        01:1:2
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:5:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Receptor NodeShutdown2
        $$CHILD_BLOCK_START
        01:1:1
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:5:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Receptor NodeShutdown1
        $$CHILD_BLOCK_START
        01:1:0
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:6:50.000000:SparkRate
                        10:6:2.000000:Time
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:8:Sound
                        10:1:2:-1:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:2:-1:Object
                        10:4:5:StartFrame
                        10:4:6:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:88:RestorePower3
        $$CHILD_BLOCK_START
        01:1:155
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:10:0:19:TimerID
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:6:20.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:6:20.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:6:20.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:6:20.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object1
                        10:1:0:141:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:2:NumTiles
                        10:14:4:Texture
                        10:6:0.500000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:255:Red
                        10:4:255:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object1
                        10:1:0:140:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:2:NumTiles
                        10:14:4:Texture
                        10:6:0.500000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:255:Red
                        10:4:255:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object1
                        10:1:0:142:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:2:NumTiles
                        10:14:4:Texture
                        10:6:0.500000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:255:Red
                        10:4:255:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aLightningCreate
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object1
                        10:1:0:139:Object2
                        10:6:99999.000000:Lifetime
                        10:6:3.000000:Thickness
                        10:4:2:NumTiles
                        10:14:4:Texture
                        10:6:0.500000:SlideTime
                        10:4:2:TimesDrawn
                        10:4:255:Red
                        10:4:255:Green
                        10:4:255:Blue
                        10:5:0:AutoTile
                        $$CHILD_BLOCK_END
                08:aMiscShakeArea
                        $$CHILD_BLOCK_START
                        10:1:0:150:Object
                        10:6:80.000000:Amount
                        10:6:500.000000:Dist
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:87:RestorePower2
        $$CHILD_BLOCK_START
        01:1:156
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:141:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:142:Object
                        10:4:0:StartFrame
                        10:4:3:EndFrame
                        10:6:3.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:139:Object
                        10:6:25.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:140:Object
                        10:6:25.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:141:Object
                        10:6:25.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:142:Object
                        10:6:25.000000:SparkRate
                        10:6:5.000000:Time
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Restore Power
        $$CHILD_BLOCK_START
        01:1:155
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
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:86:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:0
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:50.000000:Time
                                10:10:0:14:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetLevelTimer
                                $$CHILD_BLOCK_START
                                10:6:60.000000:Time
                                10:10:0:16:TimerID
                                $$CHILD_BLOCK_END
                        08:aTimerShow
                                $$CHILD_BLOCK_START
                                10:10:0:16:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:156:Object
                                10:6:1.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:155:Object
                                10:6:4.000000:Time
                                10:10:0:-1:TimerID
                                $$CHILD_BLOCK_END
                        08:aDoorSetPos
                                $$CHILD_BLOCK_START
                                10:0:0:0:Door
                                10:9:0.000000:Position
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:7:Object
                                10:4:2:StartFrame
                                10:4:3:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:6:Object
                                10:4:2:StartFrame
                                10:4:3:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:5:Object
                                10:4:2:StartFrame
                                10:4:3:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:4:Object
                                10:4:2:StartFrame
                                10:4:3:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:3:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:7:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:RechargeSucceed:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
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
                04:1:0:1
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
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:RechargeFail:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:86:Shutdown Power
        $$CHILD_BLOCK_START
        01:1:156
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
                03:1
                        $$CHILD_BLOCK_START
                        09:0
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:84:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:83:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:82:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qScriptExecuted_DALLAS:Bool
                                                $$CHILD_BLOCK_START
                                                10:11:19:ScriptID
                                                $$CHILD_BLOCK_END
                                        07:0:6
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjSetLightingColor
                                $$CHILD_BLOCK_START
                                10:1:0:157:Object
                                10:6:1.000000:Red
                                10:6:0.200000:Green
                                10:6:0.200000:Blue
                                $$CHILD_BLOCK_END
                        08:aObjSetLightingColor
                                $$CHILD_BLOCK_START
                                10:1:0:158:Object
                                10:6:1.000000:Red
                                10:6:0.200000:Green
                                10:6:0.200000:Blue
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:36:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:37:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:38:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:39:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:40:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:41:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:42:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:43:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:44:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:45:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:46:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:47:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:48:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aRoomSetLightingPulse
                                $$CHILD_BLOCK_START
                                10:2:49:Room
                                10:6:20.000000:PulseTime
                                10:6:0.000000:PulseOffset
                                $$CHILD_BLOCK_END
                        08:aMiscShakeArea
                                $$CHILD_BLOCK_START
                                10:1:0:150:Object
                                10:6:80.000000:Amount
                                10:6:200.000000:Dist
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:150:Object
                                10:4:0:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:2.500000:BlobSize
                                10:6:15.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:147:Object
                                10:4:0:GunNum
                                10:10:0:7:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:1.500000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:2.500000:BlobSize
                                10:6:15.000000:BlobSpeed
                                10:5:0:Randomize
                                10:10:0:-1:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aGoalCompleted
                                $$CHILD_BLOCK_START
                                10:18:0:4:LevelGoal
                                10:10:0:1:Completed
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:6:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:159:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:160:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:161:Object
                                $$CHILD_BLOCK_END
                        08:aAISetState
                                $$CHILD_BLOCK_START
                                10:10:0:0:On/Off
                                10:1:0:162:Object
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
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:0:149:Object
                                $$CHILD_BLOCK_END
                        08:aObjDelete
                                $$CHILD_BLOCK_START
                                10:1:0:148:Object
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:150:Object
                                10:6:30.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aObjSpark
                                $$CHILD_BLOCK_START
                                10:1:0:147:Object
                                10:6:30.000000:SparkRate
                                10:6:99999.000000:Time
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:DeactivateSucceed:Message
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:4:Sound
                                10:1:0:158:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:4:Sound
                                10:1:0:157:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:10:Sound
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
                04:1:0:1
                        $$CHILD_BLOCK_START
                        03:1
                                $$CHILD_BLOCK_START
                                05:1
                                        $$CHILD_BLOCK_START
                                        06:qUserFlag:Bool
                                                $$CHILD_BLOCK_START
                                                10:10:0:6:UserFlag
                                                $$CHILD_BLOCK_END
                                        07:0:7
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        04:1:0:0
                                $$CHILD_BLOCK_START
                                08:aShowHUDMessage
                                        $$CHILD_BLOCK_START
                                        10:8:DeactivateFail:Message
                                        $$CHILD_BLOCK_END
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:EndMovie-1
        $$CHILD_BLOCK_START
        01:1:163
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:164:Object
                        10:6:1.200000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:165:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:166:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:167:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.120000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:4.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:168:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:3.000000:SpewLife
                        10:6:3.000000:BlobSize
                        10:6:20.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:10:CameraPath
                        10:8:EmptyMessage:Text
                        10:1:0:39:TotallyNotUsedTarget
                        10:16:11:PlayerPath
                        10:6:8.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:EndMovie-1 Door Open
        $$CHILD_BLOCK_START
        01:1:164
        02:9
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:166:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:167:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.200000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:5.000000:BlobSize
                        10:6:30.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:EndMovie-2
        $$CHILD_BLOCK_START
        01:2:0
        02:28
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
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:0.100000:Seconds
                        10:9:0.080000:Probability
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:169:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:7.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:170:Object
                        10:4:-1:GunNum
                        10:10:0:7:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:1.400000:BlobLifetime
                        10:6:0.100000:BlobInterval
                        10:6:10.000000:SpewLife
                        10:6:7.000000:BlobSize
                        10:6:50.000000:BlobSpeed
                        10:5:0:Randomize
                        10:10:0:-1:SpewHandle
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:171:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:172:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aObjSpark
                        $$CHILD_BLOCK_START
                        10:1:0:173:Object
                        10:6:30.000000:SparkRate
                        10:6:10.000000:Time
                        $$CHILD_BLOCK_END
                08:aStartEndlevelSequencePath
                        $$CHILD_BLOCK_START
                        10:16:12:CameraPath
                        10:16:13:PlayerPath
                        10:6:8.000000:Time
                        10:8:EmptyMessage:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Exit Level
        $$CHILD_BLOCK_START
        01:0:2
        02:1
        03:0
                $$CHILD_BLOCK_START
                09:0
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qScriptExecuted_DALLAS:Bool
                                        $$CHILD_BLOCK_START
                                        10:11:85:ScriptID
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aCancelTimer
                        $$CHILD_BLOCK_START
                        10:10:0:16:TimerID
                        $$CHILD_BLOCK_END
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
                08:aSetObjectTimer
                        $$CHILD_BLOCK_START
                        10:1:0:163:Object
                        10:6:0.000000:Time
                        10:10:0:-1:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:End Level in 10 seconds!
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
                08:aShowColoredHUDMessage
                        $$CHILD_BLOCK_START
                        10:4:255:Red
                        10:4:0:Green
                        10:4:0:Blue
                        10:8:10Seconds:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Failed
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
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aGoalFailed
                        $$CHILD_BLOCK_START
                        10:18:0:6:LevelGoal
                        10:10:0:1:Failed
                        $$CHILD_BLOCK_END
                08:aFailLevel
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:End Level Failure
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
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.800000:Time
                        10:10:0:23:TimerID
                        $$CHILD_BLOCK_END
                08:aFadeWhiteAndEndlevel
                        $$CHILD_BLOCK_START
                        10:6:4.000000:Time
                        10:8:EmptyMessage:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:54:Exit Shaker
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:40.000000:LowerLimit
                                10:6:70.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:1.500000:LowerLimit
                                10:6:3.500000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:19:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:63:Music-Level Start (Intro)
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
                        10:10:0:0:Region
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:71:Music-Level11
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
00:70:Music-Level22
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
00:69:Music-Level21
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
00:68:Music-Level32
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:67:Music-Level31
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
                        10:10:0:3:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Music-Temple21
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
00:65:Music-Temple1
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
00:64:Music-Outside1
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:BrokenDoor
        $$CHILD_BLOCK_START
        01:1:174
        02:0
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:1:0
                $$CHILD_BLOCK_START
                08:aEmitSparks
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Number
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:50.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:1:2:-1:Object
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
