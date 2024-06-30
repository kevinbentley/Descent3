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
// Filename:	Level15.cpp
// Version:	3
/////////////////////////////////////////////////////////////////////

#include <array>
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

// =================
// Script ID Numbers
// =================
#define ID_LEVEL_0000 0x000

#define ID_CUSTOM_OBJECT_10FD 0x001
#define ID_CUSTOM_OBJECT_084D 0x002
#define ID_CUSTOM_OBJECT_084E 0x003
#define ID_CUSTOM_OBJECT_084F 0x004
#define ID_CUSTOM_OBJECT_084C 0x005
#define ID_CUSTOM_OBJECT_1913 0x006
#define ID_CUSTOM_OBJECT_0851 0x007
#define ID_CUSTOM_OBJECT_0850 0x008
#define ID_CUSTOM_OBJECT_0852 0x009
#define ID_CUSTOM_OBJECT_0858 0x00a
#define ID_CUSTOM_OBJECT_0857 0x00b
#define ID_CUSTOM_OBJECT_0856 0x00c
#define ID_CUSTOM_OBJECT_0855 0x00d
#define ID_CUSTOM_OBJECT_399D 0x00e
#define ID_CUSTOM_OBJECT_210D 0x00f
#define ID_CUSTOM_OBJECT_210E 0x010
#define ID_CUSTOM_OBJECT_190F 0x011
#define ID_CUSTOM_OBJECT_2801 0x012
#define ID_CUSTOM_OBJECT_1828 0x013
#define ID_CUSTOM_OBJECT_1015 0x014
#define ID_CUSTOM_OBJECT_0848 0x015
#define ID_CUSTOM_OBJECT_0849 0x016
#define ID_CUSTOM_OBJECT_0847 0x017
#define ID_CUSTOM_OBJECT_3831 0x018
#define ID_CUSTOM_OBJECT_2111 0x019
#define ID_CUSTOM_OBJECT_0AB1 0x01a

#define ID_TRIGGER_0000 0x01b
#define ID_TRIGGER_0001 0x01c
#define ID_TRIGGER_0002 0x01d
#define ID_TRIGGER_0005 0x01e
#define ID_TRIGGER_0004 0x01f
#define ID_TRIGGER_0003 0x020
#define ID_TRIGGER_0008 0x021
#define ID_TRIGGER_0007 0x022
#define ID_TRIGGER_0006 0x023
#define ID_TRIGGER_0009 0x024
#define ID_TRIGGER_000B 0x025
#define ID_TRIGGER_0020 0x026
#define ID_TRIGGER_001E 0x027
#define ID_TRIGGER_001C 0x028
#define ID_TRIGGER_001A 0x029
#define ID_TRIGGER_0017 0x02a
#define ID_TRIGGER_001B 0x02b
#define ID_TRIGGER_0018 0x02c
#define ID_TRIGGER_0015 0x02d
#define ID_TRIGGER_0013 0x02e
#define ID_TRIGGER_0011 0x02f
#define ID_TRIGGER_0010 0x030
#define ID_TRIGGER_001F 0x031
#define ID_TRIGGER_001D 0x032
#define ID_TRIGGER_0016 0x033
#define ID_TRIGGER_0014 0x034
#define ID_TRIGGER_0012 0x035
#define ID_TRIGGER_0019 0x036
#define ID_TRIGGER_000F 0x037
#define ID_TRIGGER_000A 0x038

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

class CustomObjectScript_084D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_084C : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1913 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0851 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0850 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0852 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0858 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0857 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0856 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0855 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_399D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_210D : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_210E : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_190F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2801 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1828 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1015 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0848 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0849 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0847 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_3831 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_2111 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_0AB1 : public BaseScript {
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

class TriggerScript_0005 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0004 : public BaseScript {
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

class TriggerScript_0007 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0006 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0009 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000B : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0020 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001E : public BaseScript {
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

class TriggerScript_0017 : public BaseScript {
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

class TriggerScript_0010 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_001D : public BaseScript {
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

class TriggerScript_0012 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0019 : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000F : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_000A : public BaseScript {
public:
  int16_t CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE 100000

int ScriptActionCtr_000 = 0;
int ScriptActionCtr_034 = 0;
int ScriptActionCtr_001 = 0;
int ScriptActionCtr_020 = 0;
int ScriptActionCtr_021 = 0;
int ScriptActionCtr_002 = 0;
int ScriptActionCtr_053 = 0;
int ScriptActionCtr_003 = 0;
int ScriptActionCtr_004 = 0;
int ScriptActionCtr_005 = 0;
int ScriptActionCtr_006 = 0;
int ScriptActionCtr_008 = 0;
int ScriptActionCtr_009 = 0;
int ScriptActionCtr_010 = 0;
int ScriptActionCtr_011 = 0;
int ScriptActionCtr_013 = 0;
int ScriptActionCtr_014 = 0;
int ScriptActionCtr_012 = 0;
int ScriptActionCtr_007 = 0;
int ScriptActionCtr_015 = 0;
int ScriptActionCtr_016 = 0;
int ScriptActionCtr_017 = 0;
int ScriptActionCtr_026 = 0;
int ScriptActionCtr_022 = 0;
int ScriptActionCtr_023 = 0;
int ScriptActionCtr_028 = 0;
int ScriptActionCtr_027 = 0;
int ScriptActionCtr_024 = 0;
int ScriptActionCtr_030 = 0;
int ScriptActionCtr_029 = 0;
int ScriptActionCtr_025 = 0;
int ScriptActionCtr_018 = 0;
int ScriptActionCtr_019 = 0;
int ScriptActionCtr_033 = 0;
int ScriptActionCtr_032 = 0;
int ScriptActionCtr_031 = 0;
int ScriptActionCtr_038 = 0;
int ScriptActionCtr_039 = 0;
int ScriptActionCtr_050 = 0;
int ScriptActionCtr_036 = 0;
int ScriptActionCtr_037 = 0;
int ScriptActionCtr_040 = 0;
int ScriptActionCtr_051 = 0;
int ScriptActionCtr_041 = 0;
int ScriptActionCtr_042 = 0;
int ScriptActionCtr_044 = 0;
int ScriptActionCtr_045 = 0;
int ScriptActionCtr_046 = 0;
int ScriptActionCtr_047 = 0;
int ScriptActionCtr_052 = 0;
int ScriptActionCtr_058 = 0;
int ScriptActionCtr_059 = 0;
int ScriptActionCtr_063 = 0;
int ScriptActionCtr_062 = 0;
int ScriptActionCtr_061 = 0;
int ScriptActionCtr_060 = 0;
int ScriptActionCtr_077 = 0;
int ScriptActionCtr_076 = 0;
int ScriptActionCtr_075 = 0;
int ScriptActionCtr_074 = 0;
int ScriptActionCtr_073 = 0;
int ScriptActionCtr_072 = 0;
int ScriptActionCtr_071 = 0;
int ScriptActionCtr_070 = 0;
int ScriptActionCtr_069 = 0;
int ScriptActionCtr_068 = 0;
int ScriptActionCtr_067 = 0;
int ScriptActionCtr_066 = 0;
int ScriptActionCtr_065 = 0;
int ScriptActionCtr_064 = 0;
int ScriptActionCtr_078 = 0;
int ScriptActionCtr_079 = 0;
int ScriptActionCtr_082 = 0;
int ScriptActionCtr_081 = 0;
int ScriptActionCtr_080 = 0;
int ScriptActionCtr_083 = 0;
int ScriptActionCtr_085 = 0;
int ScriptActionCtr_084 = 0;
int ScriptActionCtr_090 = 0;
int ScriptActionCtr_035 = 0;

// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void) {
  ScriptActionCtr_000 = 0;
  ScriptActionCtr_034 = 0;
  ScriptActionCtr_001 = 0;
  ScriptActionCtr_020 = 0;
  ScriptActionCtr_021 = 0;
  ScriptActionCtr_002 = 0;
  ScriptActionCtr_053 = 0;
  ScriptActionCtr_003 = 0;
  ScriptActionCtr_004 = 0;
  ScriptActionCtr_005 = 0;
  ScriptActionCtr_006 = 0;
  ScriptActionCtr_008 = 0;
  ScriptActionCtr_009 = 0;
  ScriptActionCtr_010 = 0;
  ScriptActionCtr_011 = 0;
  ScriptActionCtr_013 = 0;
  ScriptActionCtr_014 = 0;
  ScriptActionCtr_012 = 0;
  ScriptActionCtr_007 = 0;
  ScriptActionCtr_015 = 0;
  ScriptActionCtr_016 = 0;
  ScriptActionCtr_017 = 0;
  ScriptActionCtr_026 = 0;
  ScriptActionCtr_022 = 0;
  ScriptActionCtr_023 = 0;
  ScriptActionCtr_028 = 0;
  ScriptActionCtr_027 = 0;
  ScriptActionCtr_024 = 0;
  ScriptActionCtr_030 = 0;
  ScriptActionCtr_029 = 0;
  ScriptActionCtr_025 = 0;
  ScriptActionCtr_018 = 0;
  ScriptActionCtr_019 = 0;
  ScriptActionCtr_033 = 0;
  ScriptActionCtr_032 = 0;
  ScriptActionCtr_031 = 0;
  ScriptActionCtr_038 = 0;
  ScriptActionCtr_039 = 0;
  ScriptActionCtr_050 = 0;
  ScriptActionCtr_036 = 0;
  ScriptActionCtr_037 = 0;
  ScriptActionCtr_040 = 0;
  ScriptActionCtr_051 = 0;
  ScriptActionCtr_041 = 0;
  ScriptActionCtr_042 = 0;
  ScriptActionCtr_044 = 0;
  ScriptActionCtr_045 = 0;
  ScriptActionCtr_046 = 0;
  ScriptActionCtr_047 = 0;
  ScriptActionCtr_052 = 0;
  ScriptActionCtr_058 = 0;
  ScriptActionCtr_059 = 0;
  ScriptActionCtr_063 = 0;
  ScriptActionCtr_062 = 0;
  ScriptActionCtr_061 = 0;
  ScriptActionCtr_060 = 0;
  ScriptActionCtr_077 = 0;
  ScriptActionCtr_076 = 0;
  ScriptActionCtr_075 = 0;
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
  ScriptActionCtr_078 = 0;
  ScriptActionCtr_079 = 0;
  ScriptActionCtr_082 = 0;
  ScriptActionCtr_081 = 0;
  ScriptActionCtr_080 = 0;
  ScriptActionCtr_083 = 0;
  ScriptActionCtr_085 = 0;
  ScriptActionCtr_084 = 0;
  ScriptActionCtr_090 = 0;
  ScriptActionCtr_035 = 0;
}

// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr) {
  File_WriteInt(ScriptActionCtr_000, file_ptr);
  File_WriteInt(ScriptActionCtr_034, file_ptr);
  File_WriteInt(ScriptActionCtr_001, file_ptr);
  File_WriteInt(ScriptActionCtr_020, file_ptr);
  File_WriteInt(ScriptActionCtr_021, file_ptr);
  File_WriteInt(ScriptActionCtr_002, file_ptr);
  File_WriteInt(ScriptActionCtr_053, file_ptr);
  File_WriteInt(ScriptActionCtr_003, file_ptr);
  File_WriteInt(ScriptActionCtr_004, file_ptr);
  File_WriteInt(ScriptActionCtr_005, file_ptr);
  File_WriteInt(ScriptActionCtr_006, file_ptr);
  File_WriteInt(ScriptActionCtr_008, file_ptr);
  File_WriteInt(ScriptActionCtr_009, file_ptr);
  File_WriteInt(ScriptActionCtr_010, file_ptr);
  File_WriteInt(ScriptActionCtr_011, file_ptr);
  File_WriteInt(ScriptActionCtr_013, file_ptr);
  File_WriteInt(ScriptActionCtr_014, file_ptr);
  File_WriteInt(ScriptActionCtr_012, file_ptr);
  File_WriteInt(ScriptActionCtr_007, file_ptr);
  File_WriteInt(ScriptActionCtr_015, file_ptr);
  File_WriteInt(ScriptActionCtr_016, file_ptr);
  File_WriteInt(ScriptActionCtr_017, file_ptr);
  File_WriteInt(ScriptActionCtr_026, file_ptr);
  File_WriteInt(ScriptActionCtr_022, file_ptr);
  File_WriteInt(ScriptActionCtr_023, file_ptr);
  File_WriteInt(ScriptActionCtr_028, file_ptr);
  File_WriteInt(ScriptActionCtr_027, file_ptr);
  File_WriteInt(ScriptActionCtr_024, file_ptr);
  File_WriteInt(ScriptActionCtr_030, file_ptr);
  File_WriteInt(ScriptActionCtr_029, file_ptr);
  File_WriteInt(ScriptActionCtr_025, file_ptr);
  File_WriteInt(ScriptActionCtr_018, file_ptr);
  File_WriteInt(ScriptActionCtr_019, file_ptr);
  File_WriteInt(ScriptActionCtr_033, file_ptr);
  File_WriteInt(ScriptActionCtr_032, file_ptr);
  File_WriteInt(ScriptActionCtr_031, file_ptr);
  File_WriteInt(ScriptActionCtr_038, file_ptr);
  File_WriteInt(ScriptActionCtr_039, file_ptr);
  File_WriteInt(ScriptActionCtr_050, file_ptr);
  File_WriteInt(ScriptActionCtr_036, file_ptr);
  File_WriteInt(ScriptActionCtr_037, file_ptr);
  File_WriteInt(ScriptActionCtr_040, file_ptr);
  File_WriteInt(ScriptActionCtr_051, file_ptr);
  File_WriteInt(ScriptActionCtr_041, file_ptr);
  File_WriteInt(ScriptActionCtr_042, file_ptr);
  File_WriteInt(ScriptActionCtr_044, file_ptr);
  File_WriteInt(ScriptActionCtr_045, file_ptr);
  File_WriteInt(ScriptActionCtr_046, file_ptr);
  File_WriteInt(ScriptActionCtr_047, file_ptr);
  File_WriteInt(ScriptActionCtr_052, file_ptr);
  File_WriteInt(ScriptActionCtr_058, file_ptr);
  File_WriteInt(ScriptActionCtr_059, file_ptr);
  File_WriteInt(ScriptActionCtr_063, file_ptr);
  File_WriteInt(ScriptActionCtr_062, file_ptr);
  File_WriteInt(ScriptActionCtr_061, file_ptr);
  File_WriteInt(ScriptActionCtr_060, file_ptr);
  File_WriteInt(ScriptActionCtr_077, file_ptr);
  File_WriteInt(ScriptActionCtr_076, file_ptr);
  File_WriteInt(ScriptActionCtr_075, file_ptr);
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
  File_WriteInt(ScriptActionCtr_078, file_ptr);
  File_WriteInt(ScriptActionCtr_079, file_ptr);
  File_WriteInt(ScriptActionCtr_082, file_ptr);
  File_WriteInt(ScriptActionCtr_081, file_ptr);
  File_WriteInt(ScriptActionCtr_080, file_ptr);
  File_WriteInt(ScriptActionCtr_083, file_ptr);
  File_WriteInt(ScriptActionCtr_085, file_ptr);
  File_WriteInt(ScriptActionCtr_084, file_ptr);
  File_WriteInt(ScriptActionCtr_090, file_ptr);
  File_WriteInt(ScriptActionCtr_035, file_ptr);
}

// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr) {
  ScriptActionCtr_000 = File_ReadInt(file_ptr);
  ScriptActionCtr_034 = File_ReadInt(file_ptr);
  ScriptActionCtr_001 = File_ReadInt(file_ptr);
  ScriptActionCtr_020 = File_ReadInt(file_ptr);
  ScriptActionCtr_021 = File_ReadInt(file_ptr);
  ScriptActionCtr_002 = File_ReadInt(file_ptr);
  ScriptActionCtr_053 = File_ReadInt(file_ptr);
  ScriptActionCtr_003 = File_ReadInt(file_ptr);
  ScriptActionCtr_004 = File_ReadInt(file_ptr);
  ScriptActionCtr_005 = File_ReadInt(file_ptr);
  ScriptActionCtr_006 = File_ReadInt(file_ptr);
  ScriptActionCtr_008 = File_ReadInt(file_ptr);
  ScriptActionCtr_009 = File_ReadInt(file_ptr);
  ScriptActionCtr_010 = File_ReadInt(file_ptr);
  ScriptActionCtr_011 = File_ReadInt(file_ptr);
  ScriptActionCtr_013 = File_ReadInt(file_ptr);
  ScriptActionCtr_014 = File_ReadInt(file_ptr);
  ScriptActionCtr_012 = File_ReadInt(file_ptr);
  ScriptActionCtr_007 = File_ReadInt(file_ptr);
  ScriptActionCtr_015 = File_ReadInt(file_ptr);
  ScriptActionCtr_016 = File_ReadInt(file_ptr);
  ScriptActionCtr_017 = File_ReadInt(file_ptr);
  ScriptActionCtr_026 = File_ReadInt(file_ptr);
  ScriptActionCtr_022 = File_ReadInt(file_ptr);
  ScriptActionCtr_023 = File_ReadInt(file_ptr);
  ScriptActionCtr_028 = File_ReadInt(file_ptr);
  ScriptActionCtr_027 = File_ReadInt(file_ptr);
  ScriptActionCtr_024 = File_ReadInt(file_ptr);
  ScriptActionCtr_030 = File_ReadInt(file_ptr);
  ScriptActionCtr_029 = File_ReadInt(file_ptr);
  ScriptActionCtr_025 = File_ReadInt(file_ptr);
  ScriptActionCtr_018 = File_ReadInt(file_ptr);
  ScriptActionCtr_019 = File_ReadInt(file_ptr);
  ScriptActionCtr_033 = File_ReadInt(file_ptr);
  ScriptActionCtr_032 = File_ReadInt(file_ptr);
  ScriptActionCtr_031 = File_ReadInt(file_ptr);
  ScriptActionCtr_038 = File_ReadInt(file_ptr);
  ScriptActionCtr_039 = File_ReadInt(file_ptr);
  ScriptActionCtr_050 = File_ReadInt(file_ptr);
  ScriptActionCtr_036 = File_ReadInt(file_ptr);
  ScriptActionCtr_037 = File_ReadInt(file_ptr);
  ScriptActionCtr_040 = File_ReadInt(file_ptr);
  ScriptActionCtr_051 = File_ReadInt(file_ptr);
  ScriptActionCtr_041 = File_ReadInt(file_ptr);
  ScriptActionCtr_042 = File_ReadInt(file_ptr);
  ScriptActionCtr_044 = File_ReadInt(file_ptr);
  ScriptActionCtr_045 = File_ReadInt(file_ptr);
  ScriptActionCtr_046 = File_ReadInt(file_ptr);
  ScriptActionCtr_047 = File_ReadInt(file_ptr);
  ScriptActionCtr_052 = File_ReadInt(file_ptr);
  ScriptActionCtr_058 = File_ReadInt(file_ptr);
  ScriptActionCtr_059 = File_ReadInt(file_ptr);
  ScriptActionCtr_063 = File_ReadInt(file_ptr);
  ScriptActionCtr_062 = File_ReadInt(file_ptr);
  ScriptActionCtr_061 = File_ReadInt(file_ptr);
  ScriptActionCtr_060 = File_ReadInt(file_ptr);
  ScriptActionCtr_077 = File_ReadInt(file_ptr);
  ScriptActionCtr_076 = File_ReadInt(file_ptr);
  ScriptActionCtr_075 = File_ReadInt(file_ptr);
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
  ScriptActionCtr_078 = File_ReadInt(file_ptr);
  ScriptActionCtr_079 = File_ReadInt(file_ptr);
  ScriptActionCtr_082 = File_ReadInt(file_ptr);
  ScriptActionCtr_081 = File_ReadInt(file_ptr);
  ScriptActionCtr_080 = File_ReadInt(file_ptr);
  ScriptActionCtr_083 = File_ReadInt(file_ptr);
  ScriptActionCtr_085 = File_ReadInt(file_ptr);
  ScriptActionCtr_084 = File_ReadInt(file_ptr);
  ScriptActionCtr_090 = File_ReadInt(file_ptr);
  ScriptActionCtr_035 = File_ReadInt(file_ptr);
}

// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/

// Music Regions
/*
$$ENUM Region
0:Intro
1:Outside
2:East
3:Central
4:West
5:Endboss
$$END
*/

void aUserFlagSet(int flagnum, bool state);
bool qUserFlag(int flagnum);
const char *GetMessage(const char *name);

#define MatCenSwitchAON 0
#define MatCenSwitchBON 1
#define MatCenSwitchCON 2
#define MatCenSwitchDON 3
#define MatCenSwitchEON 4
#define MatCenSwitchFON 5
#define MatCenSwitchGON 6

// Matcens
#define MatCen5 0
#define MatCen4 1
#define MatCen2 2
#define MatCen3 3
#define MatCen1 4

// Objects
#define MatCen5Peg 4
#define MatCen4Peg 3
#define MatCen3Peg 2
#define MatCen2Peg 1
#define MatCen1Peg 0

#define MatCenSwitchA 5
#define MatCenSwitchB 6
#define MatCenSwitchC 7
#define MatCenSwitchD 8
#define MatCenSwitchE 9
#define MatCenSwitchF 10
#define MatCenSwitchG 11

#define MatCenResetSwitch 12
#define MatCenSpewer1 13
#define MatCenSpewer2 14
#define MatCenSpewer3 15
#define MatCenSpewer4 16
#define MatCenSpewer5 17

// Rooms
#define MatCenPuzzleArmoryRoom 0

// Messages
#define MagicMatCenSwitches 0
#define MatCenSwitchDOn 1
#define MatCenSwitchDOff 2
#define MatCenSwitchGOn 3
#define MatCenSwitchGOff 4
#define MatCenSwitchCOn 5
#define MatCenSwitchCOff 6
#define MatCenSwitchEOn 7
#define MatCenSwitchEOff 8
#define MatCenSwitchBOn 9
#define MatCenSwitchBOff 10
#define MatCenSwitchFOn 11
#define MatCenSwitchFOff 12
#define MatCenSwitchAOn 13
#define MatCenSwitchAOff 14

#define MagicMatCenSwitchSequence (*((int *)(&User_vars[17])))
#define MatCenStateA (*((int *)(&User_vars[0])))
#define MatCenStateB (*((int *)(&User_vars[1])))
#define MatCenStateC (*((int *)(&User_vars[2])))
#define MatCenStateD (*((int *)(&User_vars[3])))
#define MatCenStateE (*((int *)(&User_vars[4])))

struct tMyHandle {
  const char *name;
  int handle;
};

std::array<tMyHandle, 18> MyObjects = {
    tMyHandle
    {"MatCen1Peg", -1},        {"MatCen2Peg", -1},    {"MatCen3Peg", -1},    {"MatCen4Peg", -1},
    {"MatCen5Peg", -1},        {"MatCenSwitchA", -1}, {"MatCenSwitchB", -1}, {"MatCenSwitchC", -1},
    {"MatCenSwitchD", -1},     {"MatCenSwitchE", -1}, {"MatCenSwitchF", -1}, {"MatCenSwitchG", -1},
    {"MatCenPuzzleRESET", -1}, {"MatCen1Spewer", -1}, {"MatCen2Spewer", -1}, {"MatCen3Spewer", -1},
    {"MatCen4Spewer", -1},     {"MatCen5Spewer", -1},
};

std::array<tMyHandle, 5> MyMatcens = {
    tMyHandle
    {"MatCen5", -1},
    {"MatCen4", -1},
    {"MatCen2", -1},
    {"MatCen3", -1},
    {"MatCen1", -1}};

std::array<tMyHandle, 1> MyRooms = {{"MagicMatCenArmory", -1}};

struct tMyMessage {
  const char *name;
  const char *mem;
};

std::array<tMyMessage,16> MyMessages = {
        tMyMessage
        {"MagicMatCenSwitches", NULL}, {"MatCenSwitchDOn", NULL},  {"MatCenSwitchDOff", NULL},
        {"MatCenSwitchGOn", NULL},     {"MatCenSwitchGOff", NULL}, {"MatCenSwitchCOn", NULL},
        {"MatCenSwitchCOff", NULL},    {"MatCenSwitchEOn", NULL},  {"MatCenSwitchEOff", NULL},
        {"MatCenSwitchBOn", NULL},     {"MatCenSwitchBOff", NULL}, {"MatCenSwitchFOn", NULL},
        {"MatCenSwitchFOff", NULL},    {"MatCenSwitchAOn", NULL},  {"MatCenSwitchAOff", NULL}
    };

int GetMyMatCen(int id) {
  if (MyMatcens[id].handle == -1)
    MyMatcens[id].handle = Scrpt_FindMatcenName(MyMatcens[id].name);

  return MyMatcens[id].handle;
}

int GetMyObject(int id) {
  if (MyObjects[id].handle == -1)
    MyObjects[id].handle = Scrpt_FindObjectName(MyObjects[id].name);

  return MyObjects[id].handle;
}

int GetMyRoom(int id) {
  if (MyRooms[id].handle == -1)
    MyRooms[id].handle = Scrpt_FindRoomName(MyRooms[id].name);

  return MyRooms[id].handle;
}

const char *GetMyMessage(int id) {
  if (MyMessages[id].mem == NULL)
    MyMessages[id].mem = GetMessage(MyMessages[id].name);

  return MyMessages[id].mem;
}

// Turns a MatCen off
void SetMatCenToLevel0(int id) {
  aMatcenSetEnableState(0, GetMyMatCen(id));

  int spew_handle;
  int obj_handle;
  switch (id) {
  case 0:
    spew_handle = 4;
    obj_handle = GetMyObject(MatCenSpewer5);
    break;
  case 1:
    spew_handle = 3;
    obj_handle = GetMyObject(MatCenSpewer4);
    break;
  case 2:
    spew_handle = 2;
    obj_handle = GetMyObject(MatCenSpewer3);
    break;
  case 3:
    spew_handle = 1;
    obj_handle = GetMyObject(MatCenSpewer2);
    break;
  case 4:
    spew_handle = 0;
    obj_handle = GetMyObject(MatCenSpewer1);
    break;
  };

  // Make it spew!
  aTurnOnSpew(obj_handle, -1, 7, 0.000000f, 0.000000f, 65536, 0, 2.000000f, 0.100000f, -1.000000f, 4.000000f,
              20.000000f, 0, spew_handle);
}

// Turns a MatCen to normal production
void SetMatCenToLevel1(int id) {
  int matcen_id = GetMyMatCen(id);

  aMatcenSetEnableState(1, matcen_id);

  aMatcenSetValues(matcen_id, -1, 1, 3);

  int spew_handle;
  switch (id) {
  case 0:
    spew_handle = 4;
    break;
  case 1:
    spew_handle = 3;
    break;
  case 2:
    spew_handle = 2;
    break;
  case 3:
    spew_handle = 1;
    break;
  case 4:
    spew_handle = 0;
    break;
  };

  aTurnOffSpew(spew_handle);
  Spew_handles[spew_handle] = -1;
}

//	Turns a MatCen to high production
void SetMatCenToLevel2(int id) {
  int matcen_id = GetMyMatCen(id);

  aMatcenSetEnableState(1, matcen_id);
  aMatcenSetValues(matcen_id, -1, 1.5, 4);

  int spew_handle;
  switch (id) {
  case 0:
    spew_handle = 4;
    break;
  case 1:
    spew_handle = 3;
    break;
  case 2:
    spew_handle = 2;
    break;
  case 3:
    spew_handle = 1;
    break;
  case 4:
    spew_handle = 0;
    break;
  };

  aTurnOffSpew(spew_handle);
  Spew_handles[spew_handle] = -1;
}

//	Turns a lighting peg to Level 0
void SetMatCenPegToLevel0(int peg) {
  int obj_handle = GetMyObject(peg);
  aObjSetLightingDist(obj_handle, 0.000000f);
}

//	Turns a lighting peg to Level 1
void SetMatCenPegToLevel1(int peg) {
  int obj_handle = GetMyObject(peg);

  aObjSetLightingDist(obj_handle, 10.000000f);
  aObjSetLightingColor(obj_handle, 0.750000f, 0.000000f, 1.000000f);
}

//	Turns a lighting peg to Level 2
void SetMatCenPegToLevel2(int peg) {
  int obj_handle = GetMyObject(peg);

  aObjSetLightingColor(obj_handle, 1.000000f, 0.000000f, 0.000000f);
  aObjSetLightingDist(obj_handle, 10.000000f);
}

void PlayOnAnimation(int obj) { aObjPlayAnim(GetMyObject(obj), 20, 40, 2.000000f, 0); }

void PlayOffAnimation(int obj) { aObjPlayAnim(GetMyObject(obj), 0, 20, 2.000000f, 0); }

/*
$$ACTION
Scripts
MatCen Puzzle: Init
aMatCenPuzzleInit
Init MatCen Puzzle
  Inits the MatCen Puzzle

$$END
*/
void aMatCenPuzzleInit(void) {
  aUserFlagSet(MatCenSwitchAON, false);
  aUserFlagSet(MatCenSwitchBON, false);
  aUserFlagSet(MatCenSwitchCON, false);
  aUserFlagSet(MatCenSwitchDON, false);
  aUserFlagSet(MatCenSwitchEON, false);
  aUserFlagSet(MatCenSwitchFON, false);
  aUserFlagSet(MatCenSwitchGON, false);

  Spew_handles[0] = Spew_handles[1] = Spew_handles[2] = Spew_handles[3] = Spew_handles[4] = -1;

  SetMatCenPegToLevel1(MatCen1Peg);
  SetMatCenToLevel1(MatCen1);
  SetMatCenPegToLevel1(MatCen2Peg);
  SetMatCenToLevel1(MatCen2);
  SetMatCenPegToLevel1(MatCen3Peg);
  SetMatCenToLevel1(MatCen3);
  SetMatCenPegToLevel1(MatCen4Peg);
  SetMatCenToLevel1(MatCen4);
  SetMatCenPegToLevel1(MatCen5Peg);
  SetMatCenToLevel1(MatCen5);

  PlayOffAnimation(MatCenSwitchA);
  PlayOffAnimation(MatCenSwitchB);
  PlayOffAnimation(MatCenSwitchC);
  PlayOffAnimation(MatCenSwitchD);
  PlayOffAnimation(MatCenSwitchE);
  PlayOffAnimation(MatCenSwitchF);
  PlayOffAnimation(MatCenSwitchG);

  MagicMatCenSwitchSequence = 0;
  MatCenStateA = MatCenStateB = MatCenStateC = MatCenStateD = MatCenStateE = 1;

  aObjPlayAnim(GetMyObject(MatCenResetSwitch), 0, 4, 4.000000f, 0);
}

/*
$$ACTION
Scripts
MatCen Puzzle: Reset
aMatCenPuzzleReset
Reset MatCen Puzzle
  Resets the MatCen Puzzle

$$END
*/
void aMatCenPuzzleReset(void) {
  if (MagicMatCenSwitchSequence == 5 || MagicMatCenSwitchSequence == 0)
    return;

  if (qUserFlag(MatCenSwitchAON)) {
    PlayOffAnimation(MatCenSwitchA);
    aUserFlagSet(MatCenSwitchAON, false);
  }

  if (qUserFlag(MatCenSwitchBON)) {
    PlayOffAnimation(MatCenSwitchB);
    aUserFlagSet(MatCenSwitchBON, false);
  }

  if (qUserFlag(MatCenSwitchCON)) {
    PlayOffAnimation(MatCenSwitchC);
    aUserFlagSet(MatCenSwitchCON, false);
  }

  if (qUserFlag(MatCenSwitchDON)) {
    PlayOffAnimation(MatCenSwitchD);
    aUserFlagSet(MatCenSwitchDON, false);
  }

  if (qUserFlag(MatCenSwitchEON)) {
    PlayOffAnimation(MatCenSwitchE);
    aUserFlagSet(MatCenSwitchEON, false);
  }

  if (qUserFlag(MatCenSwitchFON)) {
    PlayOffAnimation(MatCenSwitchF);
    aUserFlagSet(MatCenSwitchFON, false);
  }

  if (qUserFlag(MatCenSwitchGON)) {
    PlayOffAnimation(MatCenSwitchG);
    aUserFlagSet(MatCenSwitchGON, false);
  }

  SetMatCenPegToLevel1(MatCen1Peg);
  SetMatCenToLevel1(MatCen1);
  SetMatCenPegToLevel1(MatCen2Peg);
  SetMatCenToLevel1(MatCen2);
  SetMatCenPegToLevel1(MatCen3Peg);
  SetMatCenToLevel1(MatCen3);
  SetMatCenPegToLevel1(MatCen4Peg);
  SetMatCenToLevel1(MatCen4);
  SetMatCenPegToLevel1(MatCen5Peg);
  SetMatCenToLevel1(MatCen5);

  MagicMatCenSwitchSequence = 0;
  MatCenStateA = MatCenStateB = MatCenStateC = MatCenStateD = MatCenStateE = 1;

  aObjPlayAnim(GetMyObject(MatCenResetSwitch), 0, 4, 4.000000f, 0);
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch A by [o:Player]
aMatCenPuzzleSwitchA
The Player has shot switch A
  The Player has shot switch A

$$END
*/
void aMatCenPuzzleSwitchA(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchAON)) {
    PlayOnAnimation(MatCenSwitchA);
    aUserFlagSet(MatCenSwitchAON, true);

    if (MatCenStateA == 0) {
      SetMatCenPegToLevel1(MatCen1Peg);
      SetMatCenToLevel1(MatCen1);
      MatCenStateA = 1;
    } else {
      SetMatCenPegToLevel2(MatCen1Peg);
      SetMatCenToLevel2(MatCen1);
      MatCenStateA = 2;
    }

    if (MatCenStateE == 0) {
      SetMatCenPegToLevel1(MatCen5Peg);
      SetMatCenToLevel1(MatCen5);
      MatCenStateE = 1;
    } else {
      SetMatCenPegToLevel2(MatCen5Peg);
      SetMatCenToLevel2(MatCen5);
      MatCenStateE = 2;
    }

    MagicMatCenSwitchSequence = -1;

    aShowHUDMessage(GetMyMessage(MatCenSwitchAOn));
  }
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch B by [o:Player]
aMatCenPuzzleSwitchB
The Player has shot switch B
  The Player has shot switch B

$$END
*/
void aMatCenPuzzleSwitchB(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchBON)) {
    PlayOnAnimation(MatCenSwitchB);
    aUserFlagSet(MatCenSwitchBON, true);

    SetMatCenPegToLevel0(MatCen3Peg);
    SetMatCenToLevel0(MatCen3);
    MatCenStateC = 0;

    if (MatCenStateD == 0) {
      SetMatCenPegToLevel1(MatCen4Peg);
      SetMatCenToLevel1(MatCen4);
      MatCenStateD = 1;
    } else {
      SetMatCenPegToLevel2(MatCen4Peg);
      SetMatCenToLevel2(MatCen4);
      MatCenStateD = 2;
    }

    if (MatCenStateE == 0) {
      SetMatCenPegToLevel1(MatCen5Peg);
      SetMatCenToLevel1(MatCen5);
      MatCenStateE = 1;
    } else {
      SetMatCenPegToLevel2(MatCen5Peg);
      SetMatCenToLevel2(MatCen5);
      MatCenStateE = 2;
    }

    if (MagicMatCenSwitchSequence == 2)
      MagicMatCenSwitchSequence = 3;
    else
      MagicMatCenSwitchSequence = -1;

    aShowHUDMessage(GetMyMessage(MatCenSwitchBOn));
  }
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch C by [o:Player]
aMatCenPuzzleSwitchC
The Player has shot switch C
  The Player has shot switch C

$$END
*/
void aMatCenPuzzleSwitchC(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchCON)) {
    PlayOnAnimation(MatCenSwitchC);
    aUserFlagSet(MatCenSwitchCON, true);

    SetMatCenPegToLevel0(MatCen2Peg);
    SetMatCenToLevel0(MatCen2);
    MatCenStateB = 0;

    if (MatCenStateC == 0) {
      SetMatCenPegToLevel1(MatCen3Peg);
      SetMatCenToLevel1(MatCen3);
      MatCenStateC = 1;
    } else {
      SetMatCenPegToLevel2(MatCen3Peg);
      SetMatCenToLevel2(MatCen3);
      MatCenStateC = 2;
    }

    if (MagicMatCenSwitchSequence == 1)
      MagicMatCenSwitchSequence = 2;
    else
      MagicMatCenSwitchSequence = -1;

    aShowHUDMessage(GetMyMessage(MatCenSwitchCOn));
  }
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch D by [o:Player]
aMatCenPuzzleSwitchD
The Player has shot switch D
  The Player has shot switch D

$$END
*/
void aMatCenPuzzleSwitchD(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchDON)) {
    PlayOnAnimation(MatCenSwitchD);
    aUserFlagSet(MatCenSwitchDON, true);

    SetMatCenPegToLevel0(MatCen5Peg);
    SetMatCenToLevel0(MatCen5);
    MatCenStateE = 0;

    aShowHUDMessage(GetMyMessage(MatCenSwitchDOn));

    if (MagicMatCenSwitchSequence == 4) {
      MagicMatCenSwitchSequence = 5;

      // Puzzle Solved!
      mprintf(0, "Puzzle solved\n");
      aShowHUDMessage(GetMyMessage(MagicMatCenSwitches));
      aPortalRenderSet(0, 0, GetMyRoom(MatCenPuzzleArmoryRoom), 1);

    } else {
      MagicMatCenSwitchSequence = -1;
    }
  }
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch E by [o:Player]
aMatCenPuzzleSwitchE
The Player has shot switch E
  The Player has shot switch E

$$END
*/
void aMatCenPuzzleSwitchE(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchEON)) {
    PlayOnAnimation(MatCenSwitchE);
    aUserFlagSet(MatCenSwitchEON, true);

    SetMatCenPegToLevel0(MatCen1Peg);
    SetMatCenToLevel0(MatCen1);
    MatCenStateA = 0;

    if (MatCenStateB == 0) {
      SetMatCenPegToLevel1(MatCen2Peg);
      SetMatCenToLevel1(MatCen2);
      MatCenStateB = 1;
    } else {
      SetMatCenPegToLevel2(MatCen2Peg);
      SetMatCenToLevel2(MatCen2);
      MatCenStateB = 2;
    }

    if (MatCenStateC == 0) {
      SetMatCenPegToLevel1(MatCen3Peg);
      SetMatCenToLevel1(MatCen3);
      MatCenStateC = 1;
    } else {
      SetMatCenPegToLevel2(MatCen3Peg);
      SetMatCenToLevel2(MatCen3);
      MatCenStateC = 2;
    }

    if (MagicMatCenSwitchSequence == 0)
      MagicMatCenSwitchSequence = 1;
    else
      MagicMatCenSwitchSequence = -1;

    aShowHUDMessage(GetMyMessage(MatCenSwitchEOn));
  }
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch F by [o:Player]
aMatCenPuzzleSwitchF
The Player has shot switch F
  The Player has shot switch F

$$END
*/
void aMatCenPuzzleSwitchF(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchFON)) {
    PlayOnAnimation(MatCenSwitchF);
    aUserFlagSet(MatCenSwitchFON, true);

    if (MatCenStateB == 0) {
      SetMatCenPegToLevel1(MatCen2Peg);
      SetMatCenToLevel1(MatCen2);
      MatCenStateB = 1;
    } else {
      SetMatCenPegToLevel2(MatCen2Peg);
      SetMatCenToLevel2(MatCen2);
      MatCenStateB = 2;
    }

    if (MatCenStateD == 0) {
      SetMatCenPegToLevel1(MatCen4Peg);
      SetMatCenToLevel1(MatCen4);
      MatCenStateD = 1;
    } else {
      SetMatCenPegToLevel2(MatCen4Peg);
      SetMatCenToLevel2(MatCen4);
      MatCenStateD = 2;
    }

    MagicMatCenSwitchSequence = -1;

    aShowHUDMessage(GetMyMessage(MatCenSwitchFOn));
  }
}

/*
$$ACTION
Scripts
MatCen Puzzle: Hit Switch G by [o:Player]
aMatCenPuzzleSwitchG
The Player has shot switch G
  The Player has shot switch G

$$END
*/
void aMatCenPuzzleSwitchG(int Player) {
  if (MagicMatCenSwitchSequence == 5)
    return;

  if (!qUserFlag(MatCenSwitchGON)) {
    PlayOnAnimation(MatCenSwitchG);
    aUserFlagSet(MatCenSwitchGON, true);

    SetMatCenPegToLevel0(MatCen4Peg);
    SetMatCenToLevel0(MatCen4);
    MatCenStateD = 0;

    if (MatCenStateE == 0) {
      SetMatCenPegToLevel1(MatCen5Peg);
      SetMatCenToLevel1(MatCen5);
      MatCenStateE = 1;
    } else {
      SetMatCenPegToLevel2(MatCen5Peg);
      SetMatCenToLevel2(MatCen5);
      MatCenStateE = 2;
    }

    if (MagicMatCenSwitchSequence == 3)
      MagicMatCenSwitchSequence = 4;
    else
      MagicMatCenSwitchSequence = -1;

    aShowHUDMessage(GetMyMessage(MatCenSwitchGOn));
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
tScriptMessage *message_list[MAX_SCRIPT_MESSAGES];
int num_messages;

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

#define NUM_DOOR_NAMES 10
const char *Door_names[NUM_DOOR_NAMES] = {
    "RightLowerGeoPitDo", "LeftLowerGeoPitDoo", "CenterLowerGeoPitD", "RightGeoTubeNookDo", "RightUpperGeoPitDo",
    "CenterGeoTubeNookD", "CenterUpperGeoPitD", "LeftGeoTubeNookDoo", "LeftUpperGeoPitDoo", "DravisDoor"};
int Door_handles[NUM_DOOR_NAMES];

#define NUM_OBJECT_NAMES 40
const char *Object_names[NUM_OBJECT_NAMES] = {"InnerStrongholdPas", "Inner Door View Ca",
                                        "LeftGeoPitLava",     "RightGeoPitLava",
                                        "CenterGeoPitLava",   "LeftLavaCrank",
                                        "CenterLavaCrank",    "RightLavaCrank",
                                        "BackupReactorPower", "BackupReactorFuse",
                                        "MatCenSwitchA",      "MatCenSwitchB",
                                        "MatCenSwitchC",      "MatCenSwitchD",
                                        "MatCenSwitchE",      "MatCenSwitchF",
                                        "MatCenSwitchG",      "MatCenPuzzleRESET",
                                        "RightGeoTubeSwitch", "RightGeoTubeLava",
                                        "CenterGeoTubeSwitc", "CenterGeoTubeLava",
                                        "LeftGeoTubeSwitch",  "LeftGeoTubeLava",
                                        "Inner Door E",       "Inner Door D",
                                        "Inner Door C",       "CenterTNTDispenser",
                                        "RightTNTDispenserS", "LeftTNTDispenserSw",
                                        "LeftTNTDispenserBr", "TNTRockWall",
                                        "HellionFinalBoss",   "EndLevelCamera",
                                        "MediumVolcanoPlane", "SmallestVolcanoPla",
                                        "LargeVolcanoPlane",  "TheFan",
                                        "RotatingLightA",     "RotatingLightB"};
int Object_handles[NUM_OBJECT_NAMES];

#define NUM_ROOM_NAMES 13
const char *Room_names[NUM_ROOM_NAMES] = {
    "BackupReactorEnerg", "CShapedEnergyCente", "SecretDoorEnergyCe", "LeftGeoPitRoom",   "CenterGeoPitRoom",
    "RightGeoPitRoom",    "LeftGeoTubeRoom",    "CenterGeoTubeRoom",  "RightGeoTubeRoom", "PreBossChamberForc",
    "PreBossForcefieldR", "UpperFanRoom",       "TNT Puzzle Room"};
int Room_indexes[NUM_ROOM_NAMES];

#define NUM_TRIGGER_NAMES 30
const char *Trigger_names[NUM_TRIGGER_NAMES] = {"CshapedEnergyCenter",
                                          "SecretEnergyCenterB",
                                          "BackupEnergyCenterB",
                                          "RightGeoNookExit",
                                          "CenterGeoNookExit",
                                          "LeftGeoNookExit",
                                          "RightUpperGeoPitDoo",
                                          "CenterUpperGeoPitDo",
                                          "LeftUpperGeoPitDoor",
                                          "BossEnergyForcefiel",
                                          "EndLevelTrigger",
                                          "MOutside-4",
                                          "MOutside-3",
                                          "MOutside-2",
                                          "MOutside-1",
                                          "MBoss-1",
                                          "MCentral-6",
                                          "MCentral-5",
                                          "MCentral-4",
                                          "MCentral-3",
                                          "MCentral-2",
                                          "MCentral-1",
                                          "MEast-5",
                                          "MEast-4",
                                          "MEast-3",
                                          "MEast-2",
                                          "MEast-1",
                                          "MWest-2",
                                          "MWest-1",
                                          "PreBossTrigger"};
int Trigger_indexes[NUM_TRIGGER_NAMES];
int Trigger_faces[NUM_TRIGGER_NAMES];
int Trigger_rooms[NUM_TRIGGER_NAMES];

#define NUM_SOUND_NAMES 4
const char *Sound_names[NUM_SOUND_NAMES] = {"AmbDroneReactor", "DebrisExplosion", "AmbExplosionFarB", "AmbExplosionFarG"};
int Sound_indexes[NUM_SOUND_NAMES];

#define NUM_TEXTURE_NAMES 0
const char **Texture_names = NULL;
int *Texture_indexes = NULL;

#define NUM_PATH_NAMES 12
const char *Path_names[NUM_PATH_NAMES] = {"LeftGeoPitLavaPath",     "RightGeoPitLavaPath",    "CenterGeoPitLavaPath",
                                    "RightGeoTubeLavaPath",   "CenterGeoTubeLavaPath",  "LeftGeoTubeLavaPath",
                                    "EndLevelPath",           "IntroCamPath",           "PlayerIntroPath",
                                    "CameraBossEntrancePath", "PlayerBossEntrancePath", "BossIntroCameraPath"};
int Path_indexes[NUM_PATH_NAMES];

#define NUM_MATCEN_NAMES 2
const char *Matcen_names[NUM_MATCEN_NAMES] = {"Center TNT Dispense", "Right TNT Dispenser"};
int Matcen_indexes[NUM_MATCEN_NAMES];

#define NUM_GOAL_NAMES 5
const char *Goal_names[NUM_GOAL_NAMES] = {"Locate the Inner Stronghold Passkey", "Repair the Reactor",
                                    "Locate the Back-up Reactor", "Find the reactor's replacement fuse",
                                    "Locate Dravis' secret stronghold"};
int Goal_indexes[NUM_GOAL_NAMES];

#define NUM_MESSAGE_NAMES 22
const char *Message_names[NUM_MESSAGE_NAMES] = {"InnerDoorsUnlock",
                                          "InnerStrongholdKey",
                                          "LeftLavaCrank",
                                          "CenterLavaCrank",
                                          "RightLavaCrank",
                                          "EnergyCentersOnline",
                                          "PowerRestored",
                                          "FuseFound",
                                          "ReactorBroken",
                                          "EnergyCenterBroken",
                                          "InnerDoorsDenied",
                                          "TNTDispenserCenter",
                                          "TNTDispenserRight",
                                          "TNTDispenserLeft",
                                          "TNTDispenserLeftBroken",
                                          "TNTRockwalldestroyed",
                                          "TNTRockWall",
                                          "DravisDoor",
                                          "End",
                                          "IntroCameraText",
                                          "BLANK",
                                          "HellionIntroduction"};
const char *Message_strings[NUM_MESSAGE_NAMES];

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
    strcpy(filename, "Level15.msg");
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
  case ID_CUSTOM_OBJECT_084D:
    return new CustomObjectScript_084D;
    break;
  case ID_CUSTOM_OBJECT_084E:
    return new CustomObjectScript_084E;
    break;
  case ID_CUSTOM_OBJECT_084F:
    return new CustomObjectScript_084F;
    break;
  case ID_CUSTOM_OBJECT_084C:
    return new CustomObjectScript_084C;
    break;
  case ID_CUSTOM_OBJECT_1913:
    return new CustomObjectScript_1913;
    break;
  case ID_CUSTOM_OBJECT_0851:
    return new CustomObjectScript_0851;
    break;
  case ID_CUSTOM_OBJECT_0850:
    return new CustomObjectScript_0850;
    break;
  case ID_CUSTOM_OBJECT_0852:
    return new CustomObjectScript_0852;
    break;
  case ID_CUSTOM_OBJECT_0858:
    return new CustomObjectScript_0858;
    break;
  case ID_CUSTOM_OBJECT_0857:
    return new CustomObjectScript_0857;
    break;
  case ID_CUSTOM_OBJECT_0856:
    return new CustomObjectScript_0856;
    break;
  case ID_CUSTOM_OBJECT_0855:
    return new CustomObjectScript_0855;
    break;
  case ID_CUSTOM_OBJECT_399D:
    return new CustomObjectScript_399D;
    break;
  case ID_CUSTOM_OBJECT_210D:
    return new CustomObjectScript_210D;
    break;
  case ID_CUSTOM_OBJECT_210E:
    return new CustomObjectScript_210E;
    break;
  case ID_CUSTOM_OBJECT_190F:
    return new CustomObjectScript_190F;
    break;
  case ID_CUSTOM_OBJECT_2801:
    return new CustomObjectScript_2801;
    break;
  case ID_CUSTOM_OBJECT_1828:
    return new CustomObjectScript_1828;
    break;
  case ID_CUSTOM_OBJECT_1015:
    return new CustomObjectScript_1015;
    break;
  case ID_CUSTOM_OBJECT_0848:
    return new CustomObjectScript_0848;
    break;
  case ID_CUSTOM_OBJECT_0849:
    return new CustomObjectScript_0849;
    break;
  case ID_CUSTOM_OBJECT_0847:
    return new CustomObjectScript_0847;
    break;
  case ID_CUSTOM_OBJECT_3831:
    return new CustomObjectScript_3831;
    break;
  case ID_CUSTOM_OBJECT_2111:
    return new CustomObjectScript_2111;
    break;
  case ID_CUSTOM_OBJECT_0AB1:
    return new CustomObjectScript_0AB1;
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
  case ID_TRIGGER_0005:
    return new TriggerScript_0005;
    break;
  case ID_TRIGGER_0004:
    return new TriggerScript_0004;
    break;
  case ID_TRIGGER_0003:
    return new TriggerScript_0003;
    break;
  case ID_TRIGGER_0008:
    return new TriggerScript_0008;
    break;
  case ID_TRIGGER_0007:
    return new TriggerScript_0007;
    break;
  case ID_TRIGGER_0006:
    return new TriggerScript_0006;
    break;
  case ID_TRIGGER_0009:
    return new TriggerScript_0009;
    break;
  case ID_TRIGGER_000B:
    return new TriggerScript_000B;
    break;
  case ID_TRIGGER_0020:
    return new TriggerScript_0020;
    break;
  case ID_TRIGGER_001E:
    return new TriggerScript_001E;
    break;
  case ID_TRIGGER_001C:
    return new TriggerScript_001C;
    break;
  case ID_TRIGGER_001A:
    return new TriggerScript_001A;
    break;
  case ID_TRIGGER_0017:
    return new TriggerScript_0017;
    break;
  case ID_TRIGGER_001B:
    return new TriggerScript_001B;
    break;
  case ID_TRIGGER_0018:
    return new TriggerScript_0018;
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
  case ID_TRIGGER_0010:
    return new TriggerScript_0010;
    break;
  case ID_TRIGGER_001F:
    return new TriggerScript_001F;
    break;
  case ID_TRIGGER_001D:
    return new TriggerScript_001D;
    break;
  case ID_TRIGGER_0016:
    return new TriggerScript_0016;
    break;
  case ID_TRIGGER_0014:
    return new TriggerScript_0014;
    break;
  case ID_TRIGGER_0012:
    return new TriggerScript_0012;
    break;
  case ID_TRIGGER_0019:
    return new TriggerScript_0019;
    break;
  case ID_TRIGGER_000F:
    return new TriggerScript_000F;
    break;
  case ID_TRIGGER_000A:
    return new TriggerScript_000A;
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
  case ID_CUSTOM_OBJECT_084D:
    delete ((CustomObjectScript_084D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084E:
    delete ((CustomObjectScript_084E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084F:
    delete ((CustomObjectScript_084F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_084C:
    delete ((CustomObjectScript_084C *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1913:
    delete ((CustomObjectScript_1913 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0851:
    delete ((CustomObjectScript_0851 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0850:
    delete ((CustomObjectScript_0850 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0852:
    delete ((CustomObjectScript_0852 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0858:
    delete ((CustomObjectScript_0858 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0857:
    delete ((CustomObjectScript_0857 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0856:
    delete ((CustomObjectScript_0856 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0855:
    delete ((CustomObjectScript_0855 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_399D:
    delete ((CustomObjectScript_399D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_210D:
    delete ((CustomObjectScript_210D *)ptr);
    break;
  case ID_CUSTOM_OBJECT_210E:
    delete ((CustomObjectScript_210E *)ptr);
    break;
  case ID_CUSTOM_OBJECT_190F:
    delete ((CustomObjectScript_190F *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2801:
    delete ((CustomObjectScript_2801 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1828:
    delete ((CustomObjectScript_1828 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_1015:
    delete ((CustomObjectScript_1015 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0848:
    delete ((CustomObjectScript_0848 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0849:
    delete ((CustomObjectScript_0849 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0847:
    delete ((CustomObjectScript_0847 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_3831:
    delete ((CustomObjectScript_3831 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_2111:
    delete ((CustomObjectScript_2111 *)ptr);
    break;
  case ID_CUSTOM_OBJECT_0AB1:
    delete ((CustomObjectScript_0AB1 *)ptr);
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
  case ID_TRIGGER_0005:
    delete ((TriggerScript_0005 *)ptr);
    break;
  case ID_TRIGGER_0004:
    delete ((TriggerScript_0004 *)ptr);
    break;
  case ID_TRIGGER_0003:
    delete ((TriggerScript_0003 *)ptr);
    break;
  case ID_TRIGGER_0008:
    delete ((TriggerScript_0008 *)ptr);
    break;
  case ID_TRIGGER_0007:
    delete ((TriggerScript_0007 *)ptr);
    break;
  case ID_TRIGGER_0006:
    delete ((TriggerScript_0006 *)ptr);
    break;
  case ID_TRIGGER_0009:
    delete ((TriggerScript_0009 *)ptr);
    break;
  case ID_TRIGGER_000B:
    delete ((TriggerScript_000B *)ptr);
    break;
  case ID_TRIGGER_0020:
    delete ((TriggerScript_0020 *)ptr);
    break;
  case ID_TRIGGER_001E:
    delete ((TriggerScript_001E *)ptr);
    break;
  case ID_TRIGGER_001C:
    delete ((TriggerScript_001C *)ptr);
    break;
  case ID_TRIGGER_001A:
    delete ((TriggerScript_001A *)ptr);
    break;
  case ID_TRIGGER_0017:
    delete ((TriggerScript_0017 *)ptr);
    break;
  case ID_TRIGGER_001B:
    delete ((TriggerScript_001B *)ptr);
    break;
  case ID_TRIGGER_0018:
    delete ((TriggerScript_0018 *)ptr);
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
  case ID_TRIGGER_0010:
    delete ((TriggerScript_0010 *)ptr);
    break;
  case ID_TRIGGER_001F:
    delete ((TriggerScript_001F *)ptr);
    break;
  case ID_TRIGGER_001D:
    delete ((TriggerScript_001D *)ptr);
    break;
  case ID_TRIGGER_0016:
    delete ((TriggerScript_0016 *)ptr);
    break;
  case ID_TRIGGER_0014:
    delete ((TriggerScript_0014 *)ptr);
    break;
  case ID_TRIGGER_0012:
    delete ((TriggerScript_0012 *)ptr);
    break;
  case ID_TRIGGER_0019:
    delete ((TriggerScript_0019 *)ptr);
    break;
  case ID_TRIGGER_000F:
    delete ((TriggerScript_000F *)ptr);
    break;
  case ID_TRIGGER_000A:
    delete ((TriggerScript_000A *)ptr);
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
  case ID_CUSTOM_OBJECT_084D:
  case ID_CUSTOM_OBJECT_084E:
  case ID_CUSTOM_OBJECT_084F:
  case ID_CUSTOM_OBJECT_084C:
  case ID_CUSTOM_OBJECT_1913:
  case ID_CUSTOM_OBJECT_0851:
  case ID_CUSTOM_OBJECT_0850:
  case ID_CUSTOM_OBJECT_0852:
  case ID_CUSTOM_OBJECT_0858:
  case ID_CUSTOM_OBJECT_0857:
  case ID_CUSTOM_OBJECT_0856:
  case ID_CUSTOM_OBJECT_0855:
  case ID_CUSTOM_OBJECT_399D:
  case ID_CUSTOM_OBJECT_210D:
  case ID_CUSTOM_OBJECT_210E:
  case ID_CUSTOM_OBJECT_190F:
  case ID_CUSTOM_OBJECT_2801:
  case ID_CUSTOM_OBJECT_1828:
  case ID_CUSTOM_OBJECT_1015:
  case ID_CUSTOM_OBJECT_0848:
  case ID_CUSTOM_OBJECT_0849:
  case ID_CUSTOM_OBJECT_0847:
  case ID_CUSTOM_OBJECT_3831:
  case ID_CUSTOM_OBJECT_2111:
  case ID_CUSTOM_OBJECT_0AB1:
  case ID_TRIGGER_0000:
  case ID_TRIGGER_0001:
  case ID_TRIGGER_0002:
  case ID_TRIGGER_0005:
  case ID_TRIGGER_0004:
  case ID_TRIGGER_0003:
  case ID_TRIGGER_0008:
  case ID_TRIGGER_0007:
  case ID_TRIGGER_0006:
  case ID_TRIGGER_0009:
  case ID_TRIGGER_000B:
  case ID_TRIGGER_0020:
  case ID_TRIGGER_001E:
  case ID_TRIGGER_001C:
  case ID_TRIGGER_001A:
  case ID_TRIGGER_0017:
  case ID_TRIGGER_001B:
  case ID_TRIGGER_0018:
  case ID_TRIGGER_0015:
  case ID_TRIGGER_0013:
  case ID_TRIGGER_0011:
  case ID_TRIGGER_0010:
  case ID_TRIGGER_001F:
  case ID_TRIGGER_001D:
  case ID_TRIGGER_0016:
  case ID_TRIGGER_0014:
  case ID_TRIGGER_0012:
  case ID_TRIGGER_0019:
  case ID_TRIGGER_000F:
  case ID_TRIGGER_000A:
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
  if (trigger_room == Trigger_rooms[2] && trigger_face == Trigger_faces[2])
    return ID_TRIGGER_0000;

  if (trigger_room == Trigger_rooms[0] && trigger_face == Trigger_faces[0])
    return ID_TRIGGER_0001;

  if (trigger_room == Trigger_rooms[1] && trigger_face == Trigger_faces[1])
    return ID_TRIGGER_0002;

  if (trigger_room == Trigger_rooms[3] && trigger_face == Trigger_faces[3])
    return ID_TRIGGER_0005;

  if (trigger_room == Trigger_rooms[4] && trigger_face == Trigger_faces[4])
    return ID_TRIGGER_0004;

  if (trigger_room == Trigger_rooms[5] && trigger_face == Trigger_faces[5])
    return ID_TRIGGER_0003;

  if (trigger_room == Trigger_rooms[6] && trigger_face == Trigger_faces[6])
    return ID_TRIGGER_0008;

  if (trigger_room == Trigger_rooms[7] && trigger_face == Trigger_faces[7])
    return ID_TRIGGER_0007;

  if (trigger_room == Trigger_rooms[8] && trigger_face == Trigger_faces[8])
    return ID_TRIGGER_0006;

  if (trigger_room == Trigger_rooms[9] && trigger_face == Trigger_faces[9])
    return ID_TRIGGER_0009;

  if (trigger_room == Trigger_rooms[10] && trigger_face == Trigger_faces[10])
    return ID_TRIGGER_000B;

  if (trigger_room == Trigger_rooms[11] && trigger_face == Trigger_faces[11])
    return ID_TRIGGER_0020;

  if (trigger_room == Trigger_rooms[12] && trigger_face == Trigger_faces[12])
    return ID_TRIGGER_001E;

  if (trigger_room == Trigger_rooms[13] && trigger_face == Trigger_faces[13])
    return ID_TRIGGER_001C;

  if (trigger_room == Trigger_rooms[14] && trigger_face == Trigger_faces[14])
    return ID_TRIGGER_001A;

  if (trigger_room == Trigger_rooms[15] && trigger_face == Trigger_faces[15])
    return ID_TRIGGER_0017;

  if (trigger_room == Trigger_rooms[16] && trigger_face == Trigger_faces[16])
    return ID_TRIGGER_001B;

  if (trigger_room == Trigger_rooms[17] && trigger_face == Trigger_faces[17])
    return ID_TRIGGER_0018;

  if (trigger_room == Trigger_rooms[18] && trigger_face == Trigger_faces[18])
    return ID_TRIGGER_0015;

  if (trigger_room == Trigger_rooms[19] && trigger_face == Trigger_faces[19])
    return ID_TRIGGER_0013;

  if (trigger_room == Trigger_rooms[20] && trigger_face == Trigger_faces[20])
    return ID_TRIGGER_0011;

  if (trigger_room == Trigger_rooms[21] && trigger_face == Trigger_faces[21])
    return ID_TRIGGER_0010;

  if (trigger_room == Trigger_rooms[22] && trigger_face == Trigger_faces[22])
    return ID_TRIGGER_001F;

  if (trigger_room == Trigger_rooms[23] && trigger_face == Trigger_faces[23])
    return ID_TRIGGER_001D;

  if (trigger_room == Trigger_rooms[24] && trigger_face == Trigger_faces[24])
    return ID_TRIGGER_0016;

  if (trigger_room == Trigger_rooms[25] && trigger_face == Trigger_faces[25])
    return ID_TRIGGER_0014;

  if (trigger_room == Trigger_rooms[26] && trigger_face == Trigger_faces[26])
    return ID_TRIGGER_0012;

  if (trigger_room == Trigger_rooms[27] && trigger_face == Trigger_faces[27])
    return ID_TRIGGER_0019;

  if (trigger_room == Trigger_rooms[28] && trigger_face == Trigger_faces[28])
    return ID_TRIGGER_000F;

  if (trigger_room == Trigger_rooms[29] && trigger_face == Trigger_faces[29])
    return ID_TRIGGER_000A;

  return -1;
}

// =================
// GetCOScriptList()
// =================
int STDCALL GetCOScriptList(int **list, int **id_list) {
  static int cust_handle_list[26];
  static int cust_id_list[26] = {
      ID_CUSTOM_OBJECT_10FD, ID_CUSTOM_OBJECT_084D, ID_CUSTOM_OBJECT_084E, ID_CUSTOM_OBJECT_084F, ID_CUSTOM_OBJECT_084C,
      ID_CUSTOM_OBJECT_1913, ID_CUSTOM_OBJECT_0851, ID_CUSTOM_OBJECT_0850, ID_CUSTOM_OBJECT_0852, ID_CUSTOM_OBJECT_0858,
      ID_CUSTOM_OBJECT_0857, ID_CUSTOM_OBJECT_0856, ID_CUSTOM_OBJECT_0855, ID_CUSTOM_OBJECT_399D, ID_CUSTOM_OBJECT_210D,
      ID_CUSTOM_OBJECT_210E, ID_CUSTOM_OBJECT_190F, ID_CUSTOM_OBJECT_2801, ID_CUSTOM_OBJECT_1828, ID_CUSTOM_OBJECT_1015,
      ID_CUSTOM_OBJECT_0848, ID_CUSTOM_OBJECT_0849, ID_CUSTOM_OBJECT_0847, ID_CUSTOM_OBJECT_3831, ID_CUSTOM_OBJECT_2111,
      ID_CUSTOM_OBJECT_0AB1};

  // Fill in the custom handle list
  cust_handle_list[0] = Object_handles[0];
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
  cust_handle_list[15] = Object_handles[20];
  cust_handle_list[16] = Object_handles[22];
  cust_handle_list[17] = Object_handles[24];
  cust_handle_list[18] = Object_handles[25];
  cust_handle_list[19] = Object_handles[26];
  cust_handle_list[20] = Object_handles[27];
  cust_handle_list[21] = Object_handles[28];
  cust_handle_list[22] = Object_handles[29];
  cust_handle_list[23] = Object_handles[31];
  cust_handle_list[24] = Object_handles[32];
  cust_handle_list[25] = Object_handles[37];

  *list = cust_handle_list;
  *id_list = cust_id_list;

  return 26;
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

    // Script 035: Locate Back-up Reactor Goal Completed
    if ((ScriptActionCtr_035 < 1) && (qRoomHasPlayer(Room_indexes[12]) == true)) {
      aGoalCompleted(Goal_indexes[2], 1);

      // Increment the script action counter
      if (ScriptActionCtr_035 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_035++;
    }
  } break;
  case EVT_LEVELSTART: {
    tOSIRISEVTLEVELSTART *event_data = &data->evt_levelstart;

    ClearGlobalActionCtrs();
    dfInit();

    // Script 034: Level Start Initialization
    if (1) {
      aUserFlagSet(7, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(8, 0);
      aDoorSetPos(Door_handles[0], 0.000000f);
      aDoorSetPos(Door_handles[1], 0.000000f);
      aDoorSetPos(Door_handles[2], 0.000000f);
      aAIGoalFollowPath(Object_handles[2], Path_indexes[0], 1, 2, 1, 3, 2228480, -1);
      aAIGoalFollowPath(Object_handles[3], Path_indexes[1], 1, 2, 1, 3, 2228480, -1);
      aAIGoalFollowPath(Object_handles[4], Path_indexes[2], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(13, 0);
      aUserFlagSet(18, 0);

      // Increment the script action counter
      if (ScriptActionCtr_034 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_034++;
    }

    // Script 002: Powerless Energy Centers
    if (1) {
      aRoomSetFuelcen(0, Room_indexes[0]);
      aRoomSetFuelcen(0, Room_indexes[1]);
      aRoomSetFuelcen(0, Room_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_002++;
    }

    // Script 012: MatCen Puzzle Init
    if (1) {
      aUserFlagSet(0, 0);
      aUserFlagSet(1, 0);
      aUserFlagSet(2, 0);
      aUserFlagSet(3, 0);
      aUserFlagSet(4, 0);
      aUserFlagSet(5, 0);
      aUserFlagSet(6, 0);
      aMatCenPuzzleInit();

      // Increment the script action counter
      if (ScriptActionCtr_012 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_012++;
    }

    // Script 018: Lava Puzzle Switch Starts
    if (1) {
      aUserFlagSet(7, 0);
      aUserFlagSet(8, 0);
      aUserFlagSet(9, 0);
      aUserFlagSet(10, 0);
      aUserFlagSet(11, 0);
      aUserFlagSet(12, 0);
      aUserFlagSet(19, 0);

      // Increment the script action counter
      if (ScriptActionCtr_018 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_018++;
    }

    // Script 019: Geo Lava Room Damage
    if (1) {
      aRoomSetDamage(Room_indexes[3], 6.000000f, 0);
      aRoomSetDamage(Room_indexes[4], 6.000000f, 0);
      aRoomSetDamage(Room_indexes[5], 6.000000f, 0);
      aRoomSetDamage(Room_indexes[6], 6.000000f, 0);
      aRoomSetDamage(Room_indexes[7], 6.000000f, 0);
      aRoomSetDamage(Room_indexes[8], 6.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_019 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_019++;
    }

    // Script 040: TNT Dispensers Start
    if (1) {
      aUserFlagSet(15, 0);
      aUserFlagSet(16, 0);
      aUserFlagSet(17, 0);

      // Increment the script action counter
      if (ScriptActionCtr_040 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_040++;
    }

    // Script 044: Boss Chamber Entrance Forcefield Start
    if (1) {
      aPortalRenderSet(0, 1, Room_indexes[9], 1);

      // Increment the script action counter
      if (ScriptActionCtr_044 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_044++;
    }

    // Script 047: Volcanoes Smoking
    if (1) {
      aTurnOnSpew(Object_handles[34], 0, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[34], 1, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[34], 2, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[34], 3, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[34], 4, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[35], 0, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[35], 1, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[35], 2, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[36], 0, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[36], 1, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[36], 2, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[36], 3, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[36], 4, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);
      aTurnOnSpew(Object_handles[36], 5, 8, 0.000000f, 0.000000f, 65536, 0, 14.000000f, 0.300000f, -1.000000f,
                  200.000000f, 45.000000f, 1, 6);

      // Increment the script action counter
      if (ScriptActionCtr_047 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_047++;
    }

    // Script 052: Intro Camera
    if (1) {
      aCinematicIntro(Path_indexes[7], Message_strings[19], Object_handles[32], Path_indexes[8], 8.000000f);
      aSoundPlaySteaming("VoxL15StartLevel.osf", 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_052 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_052++;
    }

    // Script 058: Music Start Intro
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_058 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_058++;
    }

    // Script 080: The Fan Start
    if (1) {
      aRoomSetWind(Room_indexes[11], 0.000000f, -1.000000f, 0.000000f, 10.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_080 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_080++;
    }

    // Script 083: Weather Start
    if (1) {
      aLightningTurnOn(1.000000f, 0.500000f);
      aRainTurnOn(0.500000f);
      aSetLevelTimer(qRandomValue(2.000000f, 15.000000f), 3);

      // Increment the script action counter
      if (ScriptActionCtr_083 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_083++;
    }

    // Script 090: Rotating Lights
    if (1) {
      aObjPlayAnim(Object_handles[38], 0, 64, 1.000000f, 1);
      aObjPlayAnim(Object_handles[39], 0, 64, 1.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_090 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_090++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 053: Energy Centers Repaired Timer
    if (event_data->id == 2) {
      aShowHUDMessage(Message_strings[5]);

      // Increment the script action counter
      if (ScriptActionCtr_053 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_053++;
    }

    // Script 085: Major Eruption Tremor
    if (4 == event_data->id) {
      aMiscViewerShake(qRandomValue(40.000000f, 100.000000f));
      aSoundPlay2D(Sound_indexes[2], 1.000000f);
      aSetLevelTimer(qRandomValue(5.000000f, 15.000000f), 3);

      // Increment the script action counter
      if (ScriptActionCtr_085 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_085++;
    }

    // Script 084: Minor Eruption Tremor
    if (3 == event_data->id) {
      aMiscViewerShake(qRandomValue(10.000000f, 50.000000f));
      aSoundPlay2D(Sound_indexes[3], 0.500000f);
      aSetLevelTimer(qRandomValue(10.000000f, 30.000000f), 4);

      // Increment the script action counter
      if (ScriptActionCtr_084 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_084++;
    }
  } break;
  case EVT_PLAYER_MOVIE_END: {
    tOSIRISEVTPLAYERMOVIEEND *event_data = &data->evt_player_movie_end;

    // Script 059: Music Outside Init
    if (1) {
      aMusicSetRegionAll(1);

      // Increment the script action counter
      if (ScriptActionCtr_059 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_059++;
    }

    // Script 079: Pre-Boss Cinematic Finished
    if (qUserFlag(19) == true) {
      aUserFlagSet(19, 0);
      aCinematicSimple(Path_indexes[11], Message_strings[21], Object_handles[32], 12.000000f, 1);

      // Increment the script action counter
      if (ScriptActionCtr_079 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_079++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_10FD::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 000: Inner Stronghold Passkey
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[0]);
      aCreatePopupView(0, Object_handles[1], 10.000000f, 1.000000f);
      aObjectPlayerGiveKey(event_data->it_handle, Object_handles[0], 1, Message_strings[1], 0);
      aGoalCompleted(Goal_indexes[0], 1);

      // Increment the script action counter
      if (ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_000++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 001: Left Lava Crank
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(7) == false)) {
      aAIGoalFollowPath(Object_handles[2], Path_indexes[0], 1, 2, 1, 3, 19005696, -1);
      aObjPlayAnim(Object_handles[5], 0, 20, 2.000000f, 0);
      aShowHUDMessage(Message_strings[2]);
      aUserFlagSet(7, 1);
      aDoorSetPos(Door_handles[1], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_001++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 020: Center Lava Crank
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(8) == false)) {
      aAIGoalFollowPath(Object_handles[4], Path_indexes[2], 1, 2, 1, 3, 19005696, -1);
      aObjPlayAnim(Object_handles[6], 0, 20, 2.000000f, 0);
      aShowHUDMessage(Message_strings[3]);
      aUserFlagSet(8, 1);
      aDoorSetPos(Door_handles[2], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_020 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_020++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 021: Right Lava Crank
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(9) == false)) {
      aAIGoalFollowPath(Object_handles[3], Path_indexes[1], 1, 2, 1, 3, 19005696, -1);
      aObjPlayAnim(Object_handles[7], 0, 20, 2.000000f, 0);
      aShowHUDMessage(Message_strings[4]);
      aUserFlagSet(9, 1);
      aDoorSetPos(Door_handles[0], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_021 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_021++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_084C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 003: Old Backup Reactor
    if ((ScriptActionCtr_003 < 1) &&
        ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjExists(Object_handles[9]) == false))) {
      aObjPlayAnim(Object_handles[8], 0, 20, 2.000000f, 0);
      aShowHUDMessage(Message_strings[6]);
      aRoomSetLightingStrobe(0, Room_indexes[0]);
      aRoomSetFuelcen(1, Room_indexes[0]);
      aRoomSetLightingFlicker(0, Room_indexes[1]);
      aRoomSetFuelcen(1, Room_indexes[1]);
      aRoomSetLightingStrobe(0, Room_indexes[2]);
      aRoomSetLightingFlicker(0, Room_indexes[2]);
      aRoomSetFuelcen(1, Room_indexes[2]);
      aRoomSetLightingStrobe(0, Room_indexes[1]);
      aRoomSetLightingFlicker(0, Room_indexes[0]);
      aTriggerSetState(0, Trigger_indexes[0]);
      aTriggerSetState(0, Trigger_indexes[1]);
      aTriggerSetState(0, Trigger_indexes[2]);
      aGoalCompleted(Goal_indexes[1], 1);
      aSetLevelTimer(3.000000f, 2);
      aSoundPlayObject(Sound_indexes[0], Object_handles[8], 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_003++;
    }

    // Script 005: Backup Reactor Broken
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qObjExists(Object_handles[9]) == true)) {
      aShowHUDMessage(Message_strings[8]);
      aGoalEnableDisable(1, Goal_indexes[3]);
      aGoalEnableDisable(1, Goal_indexes[1]);

      // Increment the script action counter
      if (ScriptActionCtr_005 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_005++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1913::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 004: Old Backup Reactor Fuse
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjDelete(Object_handles[9]);
      aGoalEnableDisable(1, Goal_indexes[2]);
      aShowHUDMessage(Message_strings[7]);
      aGoalCompleted(Goal_indexes[3], 1);

      // Increment the script action counter
      if (ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_004++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0851::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 006: MatCen Control Switch A
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchA(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_006++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0850::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 008: MatCen Control Switch B
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchB(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_008 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_008++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0852::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 009: MatCen Control Switch C
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchC(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_009++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0858::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 010: MatCen Control Switch D
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchD(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_010++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0857::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 011: MatCen Control Switch E
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchE(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_011 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_011++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0856::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 013: MatCen Control Switch F
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchF(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_013 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_013++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0855::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 014: MatCen Control Switch G
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aMatCenPuzzleSwitchG(qObjParent(event_data->it_handle));

      // Increment the script action counter
      if (ScriptActionCtr_014 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_014++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_399D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 007: MatCen Puzzle Reset
    if (qObjIsPlayerWeapon(event_data->it_handle) == 1) {
      aMatCenPuzzleReset();

      // Increment the script action counter
      if (ScriptActionCtr_007 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_007++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_210D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 026: Right Geo Tube Switch
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(12) == false)) {
      aObjPlayAnim(Object_handles[18], 0, 1, 2.000000f, 0);
      aDoorSetPos(Door_handles[0], 0.000000f);
      aDoorSetPos(Door_handles[3], 1.000000f);
      aDoorSetPos(Door_handles[4], 1.000000f);
      aAIGoalFollowPath(Object_handles[3], Path_indexes[1], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(9, 0);
      aObjPlayAnim(Object_handles[7], 20, 40, 1.000000f, 0);
      aAIGoalFollowPath(Object_handles[19], Path_indexes[3], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(12, 1);

      // Increment the script action counter
      if (ScriptActionCtr_026 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_026++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_210E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 022: Center Geo Tube Switch
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(11) == false)) {
      aObjPlayAnim(Object_handles[20], 0, 1, 2.000000f, 0);
      aDoorSetPos(Door_handles[2], 0.000000f);
      aDoorSetPos(Door_handles[5], 1.000000f);
      aDoorSetPos(Door_handles[6], 1.000000f);
      aAIGoalFollowPath(Object_handles[4], Path_indexes[2], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(8, 0);
      aObjPlayAnim(Object_handles[6], 20, 40, 1.000000f, 0);
      aAIGoalFollowPath(Object_handles[21], Path_indexes[4], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(11, 1);

      // Increment the script action counter
      if (ScriptActionCtr_022 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_022++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_190F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 023: Left Geo Tube Switch
    if ((qObjIsPlayerWeapon(event_data->it_handle) == true) && (qUserFlag(10) == false)) {
      aObjPlayAnim(Object_handles[22], 0, 1, 2.000000f, 0);
      aDoorSetPos(Door_handles[1], 0.000000f);
      aDoorSetPos(Door_handles[7], 1.000000f);
      aDoorSetPos(Door_handles[8], 1.000000f);
      aAIGoalFollowPath(Object_handles[2], Path_indexes[0], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(7, 0);
      aObjPlayAnim(Object_handles[5], 20, 40, 1.000000f, 0);
      aAIGoalFollowPath(Object_handles[23], Path_indexes[5], 1, 2, 1, 3, 2228480, -1);
      aUserFlagSet(10, 1);

      // Increment the script action counter
      if (ScriptActionCtr_023 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_023++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2801::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 033: Inner Stronghold Door E
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) &&
        (qDoorOpenable(data->me_handle, event_data->it_handle) == false)) {
      aShowHUDMessage(Message_strings[10]);
      if (qUserFlag(13) == false) {
        aUserFlagSet(13, 1);
        aGoalEnableDisable(1, Goal_indexes[0]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_033 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_033++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1828::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 032: Inner Stronghold Door D
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) &&
        (qDoorOpenable(data->me_handle, event_data->it_handle) == false)) {
      aShowHUDMessage(Message_strings[10]);
      if (qUserFlag(13) == false) {
        aUserFlagSet(13, 1);
        aGoalEnableDisable(1, Goal_indexes[0]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_032 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_032++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_1015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 031: Inner Stronghold Door C
    if ((qObjIsPlayerOrPlayerWeapon(event_data->it_handle) == true) &&
        (qDoorOpenable(data->me_handle, event_data->it_handle) == false)) {
      aShowHUDMessage(Message_strings[10]);
      if (qUserFlag(13) == false) {
        aUserFlagSet(13, 1);
        aGoalEnableDisable(1, Goal_indexes[0]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_031 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_031++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0848::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 038: Center TNT Dispenser Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(16) == false) {
        aObjPlayAnim(Object_handles[27], 0, 10, 1.000000f, 0);
        aShowHUDMessage(Message_strings[11]);
        aMatcenSetState(1, Matcen_indexes[0]);
        aUserFlagSet(16, 1);
        aSetObjectTimer(Object_handles[27], 1.000000f, 1);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_038 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_038++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 050: Center TNT Dispenser Reset
    if (event_data->id == 1) {
      aMatcenSetState(0, Matcen_indexes[0]);
      aUserFlagSet(16, 0);
      aObjPlayAnim(Object_handles[27], 10, 20, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_050 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_050++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0849::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 039: Right TNT Dispenser Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(17) == false) {
        aObjPlayAnim(Object_handles[28], 0, 10, 1.000000f, 0);
        aShowHUDMessage(Message_strings[12]);
        aMatcenSetState(1, Matcen_indexes[1]);
        aUserFlagSet(17, 1);
        aSetObjectTimer(Object_handles[28], 1.000000f, 0);
      } else {
      }

      // Increment the script action counter
      if (ScriptActionCtr_039 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_039++;
    }
  } break;
  case EVT_TIMER: {
    tOSIRISEVTTIMER *event_data = &data->evt_timer;

    // Script 036: Right TNT Dispenser Reset
    if (event_data->id == 0) {
      aMatcenSetState(0, Matcen_indexes[1]);
      aUserFlagSet(17, 0);
      aObjPlayAnim(Object_handles[28], 10, 20, 1.000000f, 0);

      // Increment the script action counter
      if (ScriptActionCtr_036 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_036++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0847::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 037: Left TNT Dispenser Switch
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      if (qUserFlag(15) == false) {
        aShowHUDMessage(Message_strings[13]);
        aTurnOnSpew(Object_handles[30], -1, 8, 0.000000f, 0.000000f, 65536, 0, 0.750000f, 0.100000f, -1.000000f,
                    2.000000f, 10.000000f, 1, 5);
        aUserFlagSet(15, 1);
        aObjPlayAnim(Object_handles[29], 0, 10, 1.000000f, 0);
        aMiscViewerShake(40.000000f);
        aSoundPlayObject(Sound_indexes[1], Object_handles[30], 1.000000f);
      } else {
        aShowHUDMessage(Message_strings[14]);
      }

      // Increment the script action counter
      if (ScriptActionCtr_037 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_037++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_3831::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 041: TNT Rock Wall hit with player weapon
    if (qObjIsPlayerWeapon(event_data->it_handle) == true) {
      aShowHUDMessageObj(Message_strings[16], event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_041 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_041++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 051: TNT Rock wall destroyed
    if (1) {
      aShowHUDMessage(Message_strings[15]);

      // Increment the script action counter
      if (ScriptActionCtr_051 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_051++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_2111::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 045: Boss Death Dravis Door
    if (1) {
      aDoorSetPos(Door_handles[9], 1.000000f);
      aShowHUDMessage(Message_strings[17]);
      aGoalCompleted(Goal_indexes[4], 1);

      // Increment the script action counter
      if (ScriptActionCtr_045 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_045++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t CustomObjectScript_0AB1::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 081: The Fan Kill
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aObjApplyDamage(event_data->it_handle, 0.250000f);

      // Increment the script action counter
      if (ScriptActionCtr_081 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_081++;
    }
  } break;
  case EVT_DESTROY: {
    tOSIRISEVTDESTROY *event_data = &data->evt_destroy;

    // If destroy event is due to level ending, don't run scripts
    if (!event_data->is_dying)
      break;

    // Script 082: The Fan Destroyed
    if (1) {
      aRoomSetWind(Room_indexes[11], 0.000000f, 0.000000f, 0.000000f, 1.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_082 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_082++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0000::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 015: Backup Energy Center Broken
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[9]);

      // Increment the script action counter
      if (ScriptActionCtr_015 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_015++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0001::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 016: C Shaped Energy Center Broken
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[9]);
      aGoalEnableDisable(1, Goal_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_016 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_016++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0002::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 017: Secret Energy Center Broken
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aShowHUDMessage(Message_strings[9]);
      aGoalEnableDisable(1, Goal_indexes[2]);

      // Increment the script action counter
      if (ScriptActionCtr_017 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_017++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0005::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 028: Right Geo Tube Nook Exit
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[3], 0.000000f);
      aAIGoalFollowPath(Object_handles[19], Path_indexes[3], 2, 3, 2, 3, 2228480, -1);

      // Increment the script action counter
      if (ScriptActionCtr_028 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_028++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0004::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 027: Center Geo Tube Nook Exit
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[5], 0.000000f);
      aAIGoalFollowPath(Object_handles[21], Path_indexes[4], 2, 3, 2, 3, 2228480, -1);

      // Increment the script action counter
      if (ScriptActionCtr_027 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_027++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0003::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 024: Left Geo Tube Nook Exit
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[7], 0.000000f);
      aAIGoalFollowPath(Object_handles[23], Path_indexes[5], 2, 3, 2, 3, 2228480, -1);

      // Increment the script action counter
      if (ScriptActionCtr_024 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_024++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0008::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 030: Right Upper Geo Pit Door Escape
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[4], 0.000000f);
      aAIGoalFollowPath(Object_handles[19], Path_indexes[3], 1, 3, 3, 3, 19005696, -1);
      aObjPlayAnim(Object_handles[18], 1, 2, 1.000000f, 0);
      aUserFlagSet(12, 0);

      // Increment the script action counter
      if (ScriptActionCtr_030 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_030++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0007::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 029: Center Upper Geo Pit Door Escape
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[6], 0.000000f);
      aAIGoalFollowPath(Object_handles[21], Path_indexes[4], 1, 3, 3, 3, 19005696, -1);
      aObjPlayAnim(Object_handles[20], 1, 2, 1.000000f, 0);
      aUserFlagSet(11, 0);

      // Increment the script action counter
      if (ScriptActionCtr_029 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_029++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0006::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 025: Left Upper Geo Pit Door Escape
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aDoorSetPos(Door_handles[8], 0.000000f);
      aAIGoalFollowPath(Object_handles[23], Path_indexes[5], 1, 3, 3, 3, 19005696, -1);
      aObjPlayAnim(Object_handles[22], 1, 2, 1.000000f, 0);
      aUserFlagSet(10, 0);

      // Increment the script action counter
      if (ScriptActionCtr_025 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_025++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0009::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 042: Boss Chamber Forcefield
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aPortalRenderSet(1, 1, Room_indexes[9], 1);
      aPortalRenderSet(0, 0, Room_indexes[10], 1);

      // Increment the script action counter
      if (ScriptActionCtr_042 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_042++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 046: End Level Sequence
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aStartEndlevelSequence(Object_handles[33], Path_indexes[6], 10.000000f, Message_strings[18]);

      // Increment the script action counter
      if (ScriptActionCtr_046 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_046++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0020::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 063: Music-Outside-4
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_063 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_063++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001E::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 062: Music-Outside-3
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_062 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_062++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001C::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 061: Music-Outside-2
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_061 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_061++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 060: Music-Outside-1
    if (1) {
      aMusicSetRegion(1, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_060 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_060++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0017::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 077: Music-Boss-1
    if (1) {
      aMusicSetRegion(5, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_077 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_077++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_001B::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 076: Music-Central-6
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

int16_t TriggerScript_0018::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 075: Music-Central-5
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_075 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_075++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0015::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 074: Music-Central-4
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_074 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_074++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0013::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 073: Music-Central-3
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_073 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_073++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0011::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 072: Music-Central-2
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_072 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_072++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_0010::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 071: Music-Central-1
    if (1) {
      aMusicSetRegion(3, event_data->it_handle);

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

    // Script 070: Music-East-5
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

int16_t TriggerScript_001D::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 069: Music-East-4
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

int16_t TriggerScript_0016::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 068: Music-East-3
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

int16_t TriggerScript_0014::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 067: Music-East-2
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

int16_t TriggerScript_0012::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 066: Music-East-1
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

int16_t TriggerScript_0019::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 065: Music-West-2
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

int16_t TriggerScript_000F::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 064: Music-West-1
    if (1) {
      aMusicSetRegion(4, event_data->it_handle);

      // Increment the script action counter
      if (ScriptActionCtr_064 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_064++;
    }
  } break;
  }
  return CONTINUE_CHAIN | CONTINUE_DEFAULT;
}

int16_t TriggerScript_000A::CallEvent(int event, tOSIRISEventInfo *data) {
  switch (event) {
  case EVT_COLLIDE: {
    tOSIRISEVTCOLLIDE *event_data = &data->evt_collide;

    // Script 078: Pre-Boss Player Cinematic
    if (qObjIsPlayer(event_data->it_handle) == true) {
      aUserFlagSet(19, 1);
      aCinematicIntro(Path_indexes[9], Message_strings[20], Object_handles[0], Path_indexes[10], 15.000000f);

      // Increment the script action counter
      if (ScriptActionCtr_078 < MAX_ACTION_CTR_VALUE)
        ScriptActionCtr_078++;
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
NEXT_ID		92

// UserType value blocks
$$UTYPE_VALS_START UserVar
0:MatCenStateA
1:MatCenStateB
2:MatCenStateC
3:MatCenStateD
4:MatCenStateE
17:MagicMatCenSwitchSequence
$$UTYPE_VALS_END

$$UTYPE_VALS_START UserFlag
0:MatCenSwitchAON
1:MatCenSwitchBON
2:MatCenSwitchCON
3:MatCenSwitchDON
4:MatCenSwitchEON
5:MatCenSwitchFON
6:MatCenSwitchGON
7:LeftLavaCrankON
8:CenterLavaCrankON
9:RightLavaCrankON
10:LeftGeoTubeSwitchON
11:CenterGeoTubeSwitchON
12:RightGeoTubeSwitchON
13:FoundInnerDoor
14:TNTElevatorSwitchLowON
15:LeftTNTDispenserBroken
16:CenterTNTDispenserON
17:RightTNTDispenserON
18:PlayedBossIntro
19:PreBossCinematic
20:TheFanON
21:PowerSourceFound
$$UTYPE_VALS_END

$$UTYPE_VALS_START SpewHandle
0:MatCen1Spewer
1:MatCen2Spewer
2:MatCen3Spewer
3:MatCen4Spewer
4:MatCen5Spewer
5:LeftTNTDispenserSpewer
6:MediumA
7:MediumB
8:MediumC
9:MediumD
10:MediumE
11:LavaSpewA
12:LavaSpewB
13:LavaSpewC
14:LavaSpewD
15:LavaSpewE
16:LavaSpewF
17:LavaSpewG
18:LavaSpewH
19:LavaSpewI
20:LavaSpewJ
21:LavaSpewK
22:LavaSpewL
23:LavaSpewM
24:LavaSpewN
25:LavaSpewO
26:LavaSpewP
27:LavaSpewQ
28:LavaSpewR
29:LavaSpewS
30:LavaSpewT
31:LavaSpewU
32:LavaSpewV
33:LavaSpewW
34:LavaSpewX
35:LavaSpewY
36:LavaSpewZ
37:SmallA
38:SmallB
39:SmallC
40:LargeA
41:LargeB
42:LargeC
43:LargeD
44:LargeE
45:LargeF
$$UTYPE_VALS_END

$$UTYPE_VALS_START TimerID
0:TNTDispRight
1:TNTDispCenter
2:EnergyCentersRepaired
3:MinorEruption
4:MajorEruption
5:MediumVolcanoFlames
6:LargeVolcanoFlames
$$UTYPE_VALS_END

$$UTYPE_VALS_START SavedObjectSlot
$$UTYPE_VALS_END

$$UTYPE_VALS_START GoalID
$$UTYPE_VALS_END


// Name Lists
$$DOOR_LIST_START
RightLowerGeoPitDo
LeftLowerGeoPitDoo
CenterLowerGeoPitD
RightGeoTubeNookDo
RightUpperGeoPitDo
CenterGeoTubeNookD
CenterUpperGeoPitD
LeftGeoTubeNookDoo
LeftUpperGeoPitDoo
DravisDoor
$$DOOR_LIST_END

$$OBJECT_LIST_START
InnerStrongholdPas
Inner Door View Ca
LeftGeoPitLava
RightGeoPitLava
CenterGeoPitLava
LeftLavaCrank
CenterLavaCrank
RightLavaCrank
BackupReactorPower
BackupReactorFuse
MatCenSwitchA
MatCenSwitchB
MatCenSwitchC
MatCenSwitchD
MatCenSwitchE
MatCenSwitchF
MatCenSwitchG
MatCenPuzzleRESET
RightGeoTubeSwitch
RightGeoTubeLava
CenterGeoTubeSwitc
CenterGeoTubeLava
LeftGeoTubeSwitch
LeftGeoTubeLava
Inner Door E
Inner Door D
Inner Door C
CenterTNTDispenser
RightTNTDispenserS
LeftTNTDispenserSw
LeftTNTDispenserBr
TNTRockWall
HellionFinalBoss
EndLevelCamera
MediumVolcanoPlane
SmallestVolcanoPla
LargeVolcanoPlane
TheFan
RotatingLightA
RotatingLightB
$$OBJECT_LIST_END

$$ROOM_LIST_START
BackupReactorEnerg
CShapedEnergyCente
SecretDoorEnergyCe
LeftGeoPitRoom
CenterGeoPitRoom
RightGeoPitRoom
LeftGeoTubeRoom
CenterGeoTubeRoom
RightGeoTubeRoom
PreBossChamberForc
PreBossForcefieldR
UpperFanRoom
TNT Puzzle Room
$$ROOM_LIST_END

$$TRIGGER_LIST_START
CshapedEnergyCenter
SecretEnergyCenterB
BackupEnergyCenterB
RightGeoNookExit
CenterGeoNookExit
LeftGeoNookExit
RightUpperGeoPitDoo
CenterUpperGeoPitDo
LeftUpperGeoPitDoor
BossEnergyForcefiel
EndLevelTrigger
MOutside-4
MOutside-3
MOutside-2
MOutside-1
MBoss-1
MCentral-6
MCentral-5
MCentral-4
MCentral-3
MCentral-2
MCentral-1
MEast-5
MEast-4
MEast-3
MEast-2
MEast-1
MWest-2
MWest-1
PreBossTrigger
$$TRIGGER_LIST_END

$$SOUND_LIST_START
AmbDroneReactor
DebrisExplosion
AmbExplosionFarB
AmbExplosionFarG
$$SOUND_LIST_END

$$TEXTURE_LIST_START
$$TEXTURE_LIST_END

$$SPECNAME_LIST_START
$$SPECNAME_LIST_END

$$PATH_LIST_START
LeftGeoPitLavaPath
RightGeoPitLavaPath
CenterGeoPitLavaPath
RightGeoTubeLavaPath
CenterGeoTubeLavaPath
LeftGeoTubeLavaPath
EndLevelPath
IntroCamPath
PlayerIntroPath
CameraBossEntrancePath
PlayerBossEntrancePath
BossIntroCameraPath
$$PATH_LIST_END

$$MATCEN_LIST_START
Center TNT Dispense
Right TNT Dispenser
$$MATCEN_LIST_END

$$GOAL_LIST_START
Locate the Inner Stronghold Passkey
Repair the Reactor
Locate the Back-up Reactor
Find the reactor's replacement fuse
Locate Dravis' secret stronghold
$$GOAL_LIST_END

$$STRM_AUDIO_LIST_START
VoxL15StartLevel.osf
$$STRM_AUDIO_LIST_END


// Script Tree Dump
00:0:Inner Stronghold Passkey
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:InnerDoorsUnlock:Message
                        $$CHILD_BLOCK_END
                08:aCreatePopupView
                        $$CHILD_BLOCK_START
                        10:4:0:GunPoint
                        10:1:0:1:Object
                        10:6:10.000000:Time
                        10:6:1.000000:Zoom
                        $$CHILD_BLOCK_END
                08:aObjectPlayerGiveKey
                        $$CHILD_BLOCK_START
                        10:1:1:-1:PlayerObject
                        10:1:0:0:KeyObject
                        10:4:1:KeyNum
                        10:8:InnerStrongholdKey:KeyName
                        10:10:0:0:Yes/No
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:0:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:34:Level Start Initialization
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
                        10:10:0:9:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:2:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:16:0:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:16:1:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:16:2:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:13:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:18:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:1:Left Lava Crank
        $$CHILD_BLOCK_START
        01:1:5
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:16:0:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:19005696:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:LeftLavaCrank:Message
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:20:Center Lava Crank
        $$CHILD_BLOCK_START
        01:1:6
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:16:2:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:19005696:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:CenterLavaCrank:Message
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:2:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:21:Right Lava Crank
        $$CHILD_BLOCK_START
        01:1:7
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:16:1:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:19005696:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:RightLavaCrank:Message
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:2:Powerless Energy Centers
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetFuelcen
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFuelcen
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFuelcen
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:2:Room
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:53:Energy Centers Repaired Timer
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EnergyCentersOnline:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:3:Old Backup Reactor
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
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:1
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:8:Object
                        10:4:0:StartFrame
                        10:4:20:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:PowerRestored:Message
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingStrobe
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFuelcen
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFuelcen
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingStrobe
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:2:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:2:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetFuelcen
                        $$CHILD_BLOCK_START
                        10:10:0:1:On/Off
                        10:2:2:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingStrobe
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:1:Room
                        $$CHILD_BLOCK_END
                08:aRoomSetLightingFlicker
                        $$CHILD_BLOCK_START
                        10:10:0:0:On/Off
                        10:2:0:Room
                        $$CHILD_BLOCK_END
                08:aTriggerSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:3:0:Trigger
                        $$CHILD_BLOCK_END
                08:aTriggerSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:3:1:Trigger
                        $$CHILD_BLOCK_END
                08:aTriggerSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:3:2:Trigger
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:1:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        10:6:3.000000:Time
                        10:10:0:2:TimerID
                        $$CHILD_BLOCK_END
                08:aSoundPlayObject
                        $$CHILD_BLOCK_START
                        10:12:0:Sound
                        10:1:0:8:Object
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:4:Old Backup Reactor Fuse
        $$CHILD_BLOCK_START
        01:1:9
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
                        10:1:0:9:Object
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:FuseFound:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:3:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:5:Backup Reactor Broken
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
                                06:qObjExists:Bool
                                        $$CHILD_BLOCK_START
                                        10:1:0:9:Object
                                        $$CHILD_BLOCK_END
                                07:0:6
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:ReactorBroken:Message
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:3:LevelGoal
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:1:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:6:MatCen Control Switch A
        $$CHILD_BLOCK_START
        01:1:10
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
                08:aMatCenPuzzleSwitchA
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:8:MatCen Control Switch B
        $$CHILD_BLOCK_START
        01:1:11
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
                08:aMatCenPuzzleSwitchB
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:9:MatCen Control Switch C
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
                08:aMatCenPuzzleSwitchC
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:10:MatCen Control Switch D
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatCenPuzzleSwitchD
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:11:MatCen Control Switch E
        $$CHILD_BLOCK_START
        01:1:14
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
                08:aMatCenPuzzleSwitchE
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:13:MatCen Control Switch F
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatCenPuzzleSwitchF
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:14:MatCen Control Switch G
        $$CHILD_BLOCK_START
        01:1:16
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
                08:aMatCenPuzzleSwitchG
                        $$CHILD_BLOCK_START
                        06:qObjParent:Player
                                $$CHILD_BLOCK_START
                                10:1:1:-1:Object
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:12:MatCen Puzzle Init
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
                08:aMatCenPuzzleInit
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:7:MatCen Puzzle Reset
        $$CHILD_BLOCK_START
        01:1:17
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
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aMatCenPuzzleReset
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:15:Backup Energy Center Broken
        $$CHILD_BLOCK_START
        01:0:2
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EnergyCenterBroken:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:16:C Shaped Energy Center Broken
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EnergyCenterBroken:Message
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:17:Secret Energy Center Broken
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
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:EnergyCenterBroken:Message
                        $$CHILD_BLOCK_END
                08:aGoalEnableDisable
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:18:0:2:LevelGoal
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:26:Right Geo Tube Switch
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
                        05:1
                                $$CHILD_BLOCK_START
                                06:qUserFlag:Bool
                                        $$CHILD_BLOCK_START
                                        10:10:0:12:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:0:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:3:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:4:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:3:Object
                        10:16:1:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:9:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:7:Object
                        10:4:20:StartFrame
                        10:4:40:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:16:3:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:22:Center Geo Tube Switch
        $$CHILD_BLOCK_START
        01:1:20
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
                                        10:10:0:11:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:2:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:5:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:6:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:4:Object
                        10:16:2:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:8:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:6:Object
                        10:4:20:StartFrame
                        10:4:40:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:4:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:23:Left Geo Tube Switch
        $$CHILD_BLOCK_START
        01:1:22
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
                                        10:10:0:10:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:4:0:StartFrame
                        10:4:1:EndFrame
                        10:6:2.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:1:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:7:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:8:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:2:Object
                        10:16:0:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:7:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:5:Object
                        10:4:20:StartFrame
                        10:4:40:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:5:Path
                        10:4:1:FirstNode
                        10:4:2:LastNode
                        10:4:1:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:28:Right Geo Tube Nook Exit
        $$CHILD_BLOCK_START
        01:0:3
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
                        10:0:0:3:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:16:3:Path
                        10:4:2:FirstNode
                        10:4:3:LastNode
                        10:4:2:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:27:Center Geo Tube Nook Exit
        $$CHILD_BLOCK_START
        01:0:4
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
                        10:0:0:5:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:4:Path
                        10:4:2:FirstNode
                        10:4:3:LastNode
                        10:4:2:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:24:Left Geo Tube Nook Exit
        $$CHILD_BLOCK_START
        01:0:5
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
                        10:0:0:7:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:5:Path
                        10:4:2:FirstNode
                        10:4:3:LastNode
                        10:4:2:StartNode
                        10:10:0:3:GoalPriority
                        10:15:2228480:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:30:Right Upper Geo Pit Door Escape
        $$CHILD_BLOCK_START
        01:0:6
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
                        10:0:0:4:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:19:Object
                        10:16:3:Path
                        10:4:1:FirstNode
                        10:4:3:LastNode
                        10:4:3:StartNode
                        10:10:0:3:GoalPriority
                        10:15:19005696:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:18:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:12:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:29:Center Upper Geo Pit Door Escape
        $$CHILD_BLOCK_START
        01:0:7
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
                        10:0:0:6:Door
                        10:9:0.000000:Position
                        $$CHILD_BLOCK_END
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:21:Object
                        10:16:4:Path
                        10:4:1:FirstNode
                        10:4:3:LastNode
                        10:4:3:StartNode
                        10:10:0:3:GoalPriority
                        10:15:19005696:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:20:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:11:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:25:Left Upper Geo Pit Door Escape
        $$CHILD_BLOCK_START
        01:0:8
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
                08:aAIGoalFollowPath
                        $$CHILD_BLOCK_START
                        10:1:0:23:Object
                        10:16:5:Path
                        10:4:1:FirstNode
                        10:4:3:LastNode
                        10:4:3:StartNode
                        10:10:0:3:GoalPriority
                        10:15:19005696:AIGoalFlags
                        10:10:0:-1:GoalID
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:22:Object
                        10:4:1:StartFrame
                        10:4:2:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:10:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:18:Lava Puzzle Switch Starts
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
                        10:10:0:19:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:19:Geo Lava Room Damage
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:3:Room
                        10:6:6.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:4:Room
                        10:6:6.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:5:Room
                        10:6:6.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:6:Room
                        10:6:6.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:7:Room
                        10:6:6.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                08:aRoomSetDamage
                        $$CHILD_BLOCK_START
                        10:2:8:Room
                        10:6:6.000000:Damage
                        10:10:0:0:DamageSoundType
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:33:Inner Stronghold Door E
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
                                06:qDoorOpenable:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:2:-1:Door
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:InnerDoorsDenied:Message
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:32:Inner Stronghold Door D
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
                                06:qDoorOpenable:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:2:-1:Door
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:InnerDoorsDenied:Message
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:31:Inner Stronghold Door C
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
                                06:qDoorOpenable:Bool
                                        $$CHILD_BLOCK_START
                                        10:0:2:-1:Door
                                        10:1:1:-1:Object
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:InnerDoorsDenied:Message
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
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:13:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aGoalEnableDisable
                                $$CHILD_BLOCK_START
                                10:10:0:1:Enable/Disable
                                10:18:0:0:LevelGoal
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:38:Center TNT Dispenser Switch
        $$CHILD_BLOCK_START
        01:1:27
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
                                        10:10:0:16:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:4:0:StartFrame
                                10:4:10:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TNTDispenserCenter:Message
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:0:Matcen
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:16:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:27:Object
                                10:6:1.000000:Time
                                10:10:0:1:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:39:Right TNT Dispenser Switch
        $$CHILD_BLOCK_START
        01:1:28
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
                                        10:10:0:17:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                10:4:0:StartFrame
                                10:4:10:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TNTDispenserRight:Message
                                $$CHILD_BLOCK_END
                        08:aMatcenSetState
                                $$CHILD_BLOCK_START
                                10:10:0:1:Activate/Deactivate
                                10:17:0:1:Matcen
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:17:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aSetObjectTimer
                                $$CHILD_BLOCK_START
                                10:1:0:28:Object
                                10:6:1.000000:Time
                                10:10:0:0:TimerID
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:DO NOTHING
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:50:Center TNT Dispenser Reset
        $$CHILD_BLOCK_START
        01:1:27
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:0:Matcen
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:16:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:27:Object
                        10:4:10:StartFrame
                        10:4:20:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:36:Right TNT Dispenser Reset
        $$CHILD_BLOCK_START
        01:1:28
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
                08:aMatcenSetState
                        $$CHILD_BLOCK_START
                        10:10:0:0:Activate/Deactivate
                        10:17:0:1:Matcen
                        $$CHILD_BLOCK_END
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:17:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:28:Object
                        10:4:10:StartFrame
                        10:4:20:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:0:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:37:Left TNT Dispenser Switch
        $$CHILD_BLOCK_START
        01:1:29
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
                                        10:10:0:15:UserFlag
                                        $$CHILD_BLOCK_END
                                07:0:7
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:0
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TNTDispenserLeft:Message
                                $$CHILD_BLOCK_END
                        08:aTurnOnSpew
                                $$CHILD_BLOCK_START
                                10:1:0:30:Object
                                10:4:-1:GunNum
                                10:10:0:8:SpewType
                                10:6:0.000000:Mass
                                10:6:0.000000:Drag
                                10:15:65536:PhysicsFlags
                                10:5:0:IsRealObject
                                10:6:0.750000:BlobLifetime
                                10:6:0.100000:BlobInterval
                                10:6:-1.000000:SpewLife
                                10:6:2.000000:BlobSize
                                10:6:10.000000:BlobSpeed
                                10:5:1:Randomize
                                10:10:0:5:SpewHandle
                                $$CHILD_BLOCK_END
                        08:aUserFlagSet
                                $$CHILD_BLOCK_START
                                10:10:0:15:UserFlag
                                10:5:1:True/False
                                $$CHILD_BLOCK_END
                        08:aObjPlayAnim
                                $$CHILD_BLOCK_START
                                10:1:0:29:Object
                                10:4:0:StartFrame
                                10:4:10:EndFrame
                                10:6:1.000000:CycleTime
                                10:5:0:Looping
                                $$CHILD_BLOCK_END
                        08:aMiscViewerShake
                                $$CHILD_BLOCK_START
                                10:6:40.000000:Amount
                                $$CHILD_BLOCK_END
                        08:aSoundPlayObject
                                $$CHILD_BLOCK_START
                                10:12:1:Sound
                                10:1:0:30:Object
                                10:9:1.000000:Volume
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                04:1:0:1
                        $$CHILD_BLOCK_START
                        08:aShowHUDMessage
                                $$CHILD_BLOCK_START
                                10:8:TNTDispenserLeftBroken:Message
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:40:TNT Dispensers Start
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
00:51:TNT Rock wall destroyed
        $$CHILD_BLOCK_START
        01:1:31
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:TNTRockwalldestroyed:Message
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:41:TNT Rock Wall hit with player weapon
        $$CHILD_BLOCK_START
        01:1:31
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
                08:aShowHUDMessageObj
                        $$CHILD_BLOCK_START
                        10:8:TNTRockWall:Message
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:42:Boss Chamber Forcefield
        $$CHILD_BLOCK_START
        01:0:9
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
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:1:Enable/Disable
                        10:4:1:PortalNum
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                08:aPortalRenderSet
                        $$CHILD_BLOCK_START
                        10:10:0:0:Enable/Disable
                        10:4:0:PortalNum
                        10:2:10:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:44:Boss Chamber Entrance Forcefield Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
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
                        10:2:9:Room
                        10:5:1:DoublesidedFlag
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:45:Boss Death Dravis Door
        $$CHILD_BLOCK_START
        01:1:32
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aDoorSetPos
                        $$CHILD_BLOCK_START
                        10:0:0:9:Door
                        10:9:1.000000:Position
                        $$CHILD_BLOCK_END
                08:aShowHUDMessage
                        $$CHILD_BLOCK_START
                        10:8:DravisDoor:Message
                        $$CHILD_BLOCK_END
                08:aGoalCompleted
                        $$CHILD_BLOCK_START
                        10:18:0:4:LevelGoal
                        10:10:0:1:Completed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:46:End Level Sequence
        $$CHILD_BLOCK_START
        01:0:10
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
                08:aStartEndlevelSequence
                        $$CHILD_BLOCK_START
                        10:1:0:33:Camera
                        10:16:6:PlayerPath
                        10:6:10.000000:Time
                        10:8:End:Text
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:47:Volcanoes Smoking
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
                        10:1:0:34:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:2:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:3:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:34:Object
                        10:4:4:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:35:Object
                        10:4:2:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:0:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:1:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:2:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:3:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:4:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                08:aTurnOnSpew
                        $$CHILD_BLOCK_START
                        10:1:0:36:Object
                        10:4:5:GunNum
                        10:10:0:8:SpewType
                        10:6:0.000000:Mass
                        10:6:0.000000:Drag
                        10:15:65536:PhysicsFlags
                        10:5:0:IsRealObject
                        10:6:14.000000:BlobLifetime
                        10:6:0.300000:BlobInterval
                        10:6:-1.000000:SpewLife
                        10:6:200.000000:BlobSize
                        10:6:45.000000:BlobSpeed
                        10:5:1:Randomize
                        10:10:0:6:SpewHandle
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:52:Intro Camera
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
                        10:16:7:CameraPath
                        10:8:IntroCameraText:Text
                        10:1:0:32:TotallyNotUsedTarget
                        10:16:8:PlayerPath
                        10:6:8.000000:Seconds
                        $$CHILD_BLOCK_END
                08:aSoundPlaySteaming
                        $$CHILD_BLOCK_START
                        10:19:0:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:58:Music Start Intro
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
00:59:Music Outside Init
        $$CHILD_BLOCK_START
        01:2:0
        02:28
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
00:63:Music-Outside-4
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:62:Music-Outside-3
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:61:Music-Outside-2
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:60:Music-Outside-1
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
                        10:10:0:1:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:77:Music-Boss-1
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
                        10:10:0:5:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:76:Music-Central-6
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
00:75:Music-Central-5
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
00:74:Music-Central-4
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
00:73:Music-Central-3
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
00:72:Music-Central-2
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
00:71:Music-Central-1
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
00:70:Music-East-5
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:69:Music-East-4
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
00:68:Music-East-3
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
00:67:Music-East-2
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:66:Music-East-1
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
                        10:10:0:2:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:65:Music-West-2
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
                        10:10:0:4:Region
                        10:1:1:-1:PlayerObject
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:64:Music-West-1
        $$CHILD_BLOCK_START
        01:0:28
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
00:78:Pre-Boss Player Cinematic
        $$CHILD_BLOCK_START
        01:0:29
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
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:19:UserFlag
                        10:5:1:True/False
                        $$CHILD_BLOCK_END
                08:aCinematicIntro
                        $$CHILD_BLOCK_START
                        10:16:9:CameraPath
                        10:8:BLANK:Text
                        10:1:0:0:TotallyNotUsedTarget
                        10:16:10:PlayerPath
                        10:6:15.000000:Seconds
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:79:Pre-Boss Cinematic Finished
        $$CHILD_BLOCK_START
        01:2:0
        02:28
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qUserFlag:Bool
                                $$CHILD_BLOCK_START
                                10:10:0:19:UserFlag
                                $$CHILD_BLOCK_END
                        07:0:6
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aUserFlagSet
                        $$CHILD_BLOCK_START
                        10:10:0:19:UserFlag
                        10:5:0:True/False
                        $$CHILD_BLOCK_END
                08:aCinematicSimple
                        $$CHILD_BLOCK_START
                        10:16:11:CameraPath
                        10:8:HellionIntroduction:Text
                        10:1:0:32:Target
                        10:6:12.000000:Seconds
                        10:5:1:FadeIn
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:82:The Fan Destroyed
        $$CHILD_BLOCK_START
        01:1:37
        02:4
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:0.000000:Y
                        10:6:0.000000:Z
                        10:6:1.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:81:The Fan Kill
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
00:80:The Fan Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aRoomSetWind
                        $$CHILD_BLOCK_START
                        10:2:11:Room
                        10:6:0.000000:X
                        10:6:-1.000000:Y
                        10:6:0.000000:Z
                        10:6:10.000000:Speed
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:83:Weather Start
        $$CHILD_BLOCK_START
        01:2:0
        02:6
        03:0
                $$CHILD_BLOCK_START
                05:0
                $$CHILD_BLOCK_END
        04:0:0:0
                $$CHILD_BLOCK_START
                08:aLightningTurnOn
                        $$CHILD_BLOCK_START
                        10:6:1.000000:Seconds
                        10:9:0.500000:Probability
                        $$CHILD_BLOCK_END
                08:aRainTurnOn
                        $$CHILD_BLOCK_START
                        10:9:0.500000:Density
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:2.000000:LowerLimit
                                10:6:15.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:85:Major Eruption Tremor
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
                08:aMiscViewerShake
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:40.000000:LowerLimit
                                10:6:100.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:2:Sound
                        10:9:1.000000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:5.000000:LowerLimit
                                10:6:15.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:3:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:84:Minor Eruption Tremor
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
                        06:qRandomValue:Amount
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:50.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        $$CHILD_BLOCK_END
                08:aSoundPlay2D
                        $$CHILD_BLOCK_START
                        10:12:3:Sound
                        10:9:0.500000:Volume
                        $$CHILD_BLOCK_END
                08:aSetLevelTimer
                        $$CHILD_BLOCK_START
                        06:qRandomValue:Time
                                $$CHILD_BLOCK_START
                                10:6:10.000000:LowerLimit
                                10:6:30.000000:UpperLimit
                                $$CHILD_BLOCK_END
                        10:10:0:4:TimerID
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:90:Rotating Lights
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
                        10:1:0:38:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                08:aObjPlayAnim
                        $$CHILD_BLOCK_START
                        10:1:0:39:Object
                        10:4:0:StartFrame
                        10:4:64:EndFrame
                        10:6:1.000000:CycleTime
                        10:5:1:Looping
                        $$CHILD_BLOCK_END
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END
00:35:Locate Back-up Reactor Goal Completed
        $$CHILD_BLOCK_START
        01:2:0
        02:5
        03:0
                $$CHILD_BLOCK_START
                05:1
                        $$CHILD_BLOCK_START
                        06:qRoomHasPlayer:Bool
                                $$CHILD_BLOCK_START
                                10:2:12:Room
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
                $$CHILD_BLOCK_END
        $$CHILD_BLOCK_END

$$SCRIPT_BLOCK_END
*********************************************************/
